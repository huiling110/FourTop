#include "../include/jetSel.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include <map>

JetSel::JetSel(TTree *outTree, const TString era, const TString processName, const Bool_t isRun3, const Bool_t isData, const Int_t jetType, const UChar_t JESSys, const UChar_t JERSys) : m_jetType{jetType}, m_era{era}, m_processName{processName}, m_isRun3{isRun3}, m_isData{isData}, m_JESSys{JESSys}, m_JERSys{JERSys}
{ // m_type for different electrons
    // 1:loose;2:fakeble;3:tight
    std::cout << "Initializing JetSel: m_jetType=" << m_jetType <<"m_era"<<m_era<<" m_isRun3="<<m_isRun3<<" m_isData="<<m_isData<<" m_processName="<<m_processName<<" m_JESSys="<<static_cast<unsigned int>(m_JESSys)<< " m_JERSys="<<static_cast<unsigned int>(m_JERSys) <<"......\n";

    TString jsonBase = "../../jsonpog-integration/POG/";
    cset_jerSF = correction::CorrectionSet::from_file((jsonBase + TTTT::json_map.at(era).at(0)).Data());
    cset_jetVeto = correction::CorrectionSet::from_file((jsonBase + TTTT::json_map.at(era).at(4)).Data());
    // auto cset_jerSF_com = cset_jerSF->compound();
    std::cout << "JEC sf file: " << (jsonBase + TTTT::json_map.at(era).at(0)).Data() << "\n";
    std::cout << "Jet veto file: " << (jsonBase + TTTT::json_map.at(era).at(4)).Data() << "\n";
    // for (auto &corr : *cset_jerSF)  
    // {
    //     printf("Correction: %s\n", corr.first.c_str());
    // }

    std::map<Int_t, TString> jetTypeMap = {
        {0, "jets"},
        {1, "jetsT"},
        {11, "bjetsL"},
        {12, "bjetsM"},
        {13, "bjetsT"},
        {2, "forward"},
        {15, "bjetsPNM"},//particleNet
        {16, "bjetsPNT"},
        {17, "bjetsPTM"},//robustParticleTransformer
        {18, "bjetsPTT"},
    };

    ULong64_t seed = 37428479;
    m_random_generator = std::mt19937(seed); //

    outTree->Branch(jetTypeMap[m_jetType] + "_pt", &jets_pt);
    outTree->Branch(jetTypeMap[m_jetType] + "_eta", &jets_eta);
    outTree->Branch(jetTypeMap[m_jetType] + "_phi", &jets_phi);
    outTree->Branch(jetTypeMap[m_jetType] + "_mass", &jets_mass);
    outTree->Branch(jetTypeMap[m_jetType] + "_flavour", &jets_flavour);
    outTree->Branch(jetTypeMap[m_jetType] + "_btags", &jets_btags);
    // if(m_isRun3){
    //     outTree->Branch(jetTypeMap[m_jetType] + "_btagsPN", &jets_btagsPN);
    //     outTree->Branch(jetTypeMap[m_jetType] + "_btagsPT", &jets_btagsPT);
    // }
    
    //Maybe this will help with memory management
    jets_pt.reserve(4);
    jets_eta.reserve(4);
    jets_phi.reserve(4);
    jets_mass.reserve(4);
    jets_flavour.reserve(4);
    jets_btags.reserve(4);


    std::cout << "Done JetSel initialization......\n";
    std::cout << "\n";
};

JetSel::~JetSel(){};

void JetSel::Select(eventForNano *e, const Bool_t isData, const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &muPhiVec, const std::vector<Double_t> &eEtaVec, const std::vector<Double_t> &ePhiVec, const std::vector<Double_t> &tauEtaVec, const std::vector<Double_t> &tauPhiVec, const Bool_t deepJet)
{
    // jetType=0  -> usual jets; we use loose ID; jetType = 1: tight ID
    // jetType=11 -> b-jets L, jetType=12 -> b-jets M, jetType=13 -> b-jets T, jetType=2  -> forward jets
    //jetType 15: b-jetPNM, 16: b-jetPNT
    //jetType: 0: normal jet is tight jetID
    // JER: 0: nominal, 1: up, 2: down; 3: no JER
    // JES: 0: nominal; 1:up; 2: down; 
    clearBranch();

    for (UInt_t j = 0; j < e->Jet_pt.GetSize(); ++j)
    {
        Int_t ijet_jetID = OS::getValForDynamicReader<UChar_t>(m_isRun3, e->Jet_jetId, j);
        Int_t ijet_hadronFlavour = OS::getValForDynamicReader<UChar_t>(m_isRun3, e->Jet_hadronFlavour, j);

        Double_t JESSF = 1.0; //JES already applied in the nanoAODv9 for run2
        //!for run 2 need to handling the JES uncertainty variation
        if(m_isRun3){
            JESSF = calJES_SF(e->Jet_area.At(j), e->Jet_eta.At(j), e->Jet_pt.At(j), **e->Rho_fixedGridRhoFastjetAll);
        }

        Double_t jetpt = e->Jet_pt.At(j)*JESSF;
        Double_t ijetMass = e->Jet_mass.At(j)*JESSF;
        // std::cout << "JESSF: " << JESSF << "\n";
        Double_t ijetEta = e->Jet_eta.At(j);
        Double_t ijetPhi = e->Jet_phi.At(j);
        // maybe scaling only changes pt and mass? yes!

        //JER
        Double_t JERSF = 1.0;
        if(!m_isData){
            Double_t fixedGridRhoFastjetAll = m_isRun3? **e->Rho_fixedGridRhoFastjetAll:**e->fixedGridRhoFastjetAll;
            JERSF = calJER_SF_new(jetpt, ijetEta, ijetPhi, ijetMass, fixedGridRhoFastjetAll, *e->GenJet_eta, *e->GenJet_phi, *e->GenJet_pt);
        }
        // std::cout << "JERSF=" << JERSF << "\n";
        jetpt *= JERSF;
        ijetMass *= JERSF;

        // here SF_up or SF_down should also be apllied.
        Double_t jetPtCut = (m_JESSys== 0)? 25. : 22.; //!!!preserve lower pt cut for JES systematic varaition
        if (!(jetpt > jetPtCut))
            continue;
        if (!(fabs(ijetEta) < 2.4))
            continue;
        if (!(ijet_jetID >= 2)) // run2: jetID=0; 2=tight;6; //run3:bit2 is tight, bit3 is tightLepVeto
            continue;          // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        //pileup ID: https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetIDUL
        if(jetpt<50.){
            if (!(e->Jet_puId.At(j) > 0))
                continue;
        }

        // passlooseID*1+passtightID*2+passtightLepVetoID*4
        if (m_jetType == 1)
        {
            if (!(ijet_jetID > 2))
                continue; // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        }

        Bool_t ifveto = jetVetoMap(ijetEta, ijetPhi);
        if(ifveto){
            continue;
        }

        // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
        if (m_jetType == 11)
        {
            if (!(e->Jet_btagDeepFlavB.At(j) > TTTT::DeepJetL.at(m_era)))
                continue;
        }else if (m_jetType == 12)
        {
            if (!(e->Jet_btagDeepFlavB.At(j) > TTTT::DeepJetM.at(m_era)))
                continue;
        }else if (m_jetType == 13 )
        {
            if (!(e->Jet_btagDeepFlavB.At(j) > TTTT::DeepJetT.at(m_era)))
                continue;
        }else if(m_jetType == 15 && m_isRun3){
            if (!(e->Jet_btagPNetB->At(j) > particleNetBMT.at(m_era).at(0)))
                continue;
        }else if(m_jetType == 16 && m_isRun3){
            if (!(e->Jet_btagPNetB->At(j) > particleNetBMT.at(m_era).at(1)))
                continue;
        }else if(m_jetType == 17 && m_isRun3){
            if(!(e->Jet_btagRobustParTAK4B->At(j) > robustParticleTransformerMT.at(m_era).at(0)))
                continue;
        }else if(m_jetType == 18 && m_isRun3){
            if(!(e->Jet_btagRobustParTAK4B->At(j) > robustParticleTransformerMT.at(m_era).at(1)))
                continue;
        }
            

        // overlap removal
        Bool_t removeMu = OS::overlapRemove(e->Jet_eta.At(j), e->Jet_phi.At(j), muEtaVec, muPhiVec);
        Bool_t removeE = OS::overlapRemove(e->Jet_eta.At(j), e->Jet_phi.At(j), eEtaVec, ePhiVec);
        // Bool_t removeTau = OS::overlapRemove(e->Jet_eta.At(j), e->Jet_phi.At(j), tauEtaVec, tauPhiVec);
        Bool_t removeTau = OS::overlapRemove(e->Jet_eta.At(j), e->Jet_phi.At(j), tauEtaVec, tauPhiVec, 0.5);//!!!
        if(removeE||removeMu|| removeTau){
            continue;
        }

        jets_pt.push_back(jetpt);
        jets_eta.push_back(ijetEta);
        jets_phi.push_back(ijetPhi);
        jets_mass.push_back(ijetMass);
        if (!isData)
        {
            jets_flavour.push_back(ijet_hadronFlavour);
        }
        else{
            jets_flavour.push_back(-99);
        }
        jets_btags.push_back(e->Jet_btagDeepFlavB.At(j));
        // if (m_isRun3){
        //     jets_btagsPN.push_back(e->Jet_btagPNetB->At(j));
        //     jets_btagsPT.push_back(e->Jet_btagRobustParTAK4B->At(j));//???small portions of value -3???
        // }else{
        //     jets_btagsPN.push_back(-99);
        //     jets_btagsPT.push_back(-99);
        // }
    }
};

void JetSel::calJER_SF(eventForNano *e, const Bool_t isData, const Int_t sys)
{
    // https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/jercExample.py
    // https://twiki.cern.ch/twi:162,ki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Uncertai
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
    // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h
    //https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetSmearer.py
    auto corr_jerSF = cset_jerSF->at(corr_SF_map[m_era].at(0).Data());
    auto corr_jerResolution = cset_jerSF->at(corr_SF_map[m_era].at(2).Data());

    // https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetmetHelperRun2.py
    auto corr_jesUncer = cset_jerSF->at(corr_SF_map[m_era].at(1).Data());
    //???does the MC_Total include the JER uncertainty?
    //not sure how to get the JEC uncertainty for data yet? the uncertainty in data is abored in MC

    JER_SF_new.clear();

    Double_t iSF = 1.0; //SF for JER, I think JER is derived on top of JES
    Double_t iSF_JESuncer = 0.0;
    const Double_t MIN_JET_ENERGY = 1e-2;
        Double_t rho = 0.0;
        if(!m_isRun3){
            rho = **e->fixedGridRhoFastjetAll;
        }else{
            rho = **e->Rho_fixedGridRhoFastjetAll;
        }
    for (UInt_t i = 0; i < e->Jet_pt.GetSize(); i++)
    {
        Double_t ieta = e->Jet_eta.At(i);
        Double_t iphi = e->Jet_phi.At(i);
        Double_t ipt = e->Jet_pt.At(i);
        ROOT::Math::PtEtaPhiMVector ijetVec(ipt, ieta, iphi, e->Jet_mass.At(i));
        Double_t ienergy = ijetVec.energy();

        // Double_t ijet_sf = corr_jerSF->evaluate({ieta, "nom"}); // JER_SF_new
        Double_t ijet_sf = 1.0; // JER_SF_new
        // not in a pT-dependent format, strong pT dependency at high eta is however observed to be reduced in UL
        switch (sys)
        {
        case 0:
            ijet_sf = corr_jerSF->evaluate({ieta, "nom"});
            break;
        case 1:
            ijet_sf = corr_jerSF->evaluate({ieta, "up"});
            break;
        case 2:
            ijet_sf = corr_jerSF->evaluate({ieta, "down"});
            break;
        default:
            std::cout << "!!!JER sf not getting correctly\n";
            break;
        }

        Double_t ijet_res = corr_jerResolution->evaluate({{ipt, ieta, rho}}); // !!!jet_resolution, there are fixedGridRhoFastjetCentral and others, not sure which rho to use?
        // what is this rho? average energy density , for a event

        // find gen matching
        if (!isData)
        {
            Int_t genMatchIndex = OS::genMatchForJER(ieta, iphi, ipt, *e->GenJet_eta, *e->GenJet_phi, *e->GenJet_pt, ijet_res);
            if (genMatchIndex > 0)
            {
                // Case 1: we have a "good" generator level jet matched to the reconstructed jet
                Double_t dPt = ipt - (*e->GenJet_pt)[genMatchIndex];
                iSF = 1 + (ijet_sf - 1.) * dPt / ipt;
            }
            else
            { // Case 2: we don't have a gen jet. Smear jet pt using a random gaussian variation
                Double_t sigma = ijet_res * std::sqrt(ijet_sf * ijet_sf - 1);
                std::normal_distribution<> d(0, sigma);
                iSF = 1. + d(m_random_generator); // m_random_generator = std::mt19937(seed) //std::uint32_t>("seed", 37428479);
            }
            if (ienergy * iSF < MIN_JET_ENERGY)
            {
                // Negative or too small smearFactor. We would change direction of the jet
                // and this is not what we want.
                // Recompute the smearing factor in order to have jet.energy() == MIN_JET_ENERGY
                Double_t newSmearFactor = MIN_JET_ENERGY / ienergy;
                iSF = newSmearFactor;
            }

            iSF_JESuncer = corr_jesUncer->evaluate({ieta, ipt}); //!!! do you need the pt to be raw?
        }
        // std::cout << "iJERSF: " << iSF << "\n";
        // std::cout<<"iSF_JES"<<iSF_JESuncer<<"\n";
        JER_SF_new.push_back(iSF);
        // jets_JESuncer.push_back(iSF_JESuncer);
    }
};

Double_t JetSel::calJER_SF_new(Double_t pt, Double_t eta, Double_t phi, Double_t mass, Double_t rho, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, TTreeReaderArray<Float_t> &genPt){
    // https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/jercExample.py
    // https://twiki.cern.ch/twi:162,ki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Uncertai
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
    // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h
    //https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetSmearer.py
    if(m_isData){
        return 1.0;
    }
    //run 3: Summer22EE_22Sep2023_JRV1_MC_ScaleFactor_AK4PFPuppi
    auto corr_jerSF = cset_jerSF->at(corr_SF_map[m_era].at(0).Data());
    auto corr_jerResolution = cset_jerSF->at(corr_SF_map[m_era].at(2).Data());
    ROOT::Math::PtEtaPhiMVector ijetVec(pt, eta, phi, mass);
    Double_t ienergy = ijetVec.energy();
    Double_t iSF = 1.0; // JER_SF_new
    // not in a pT-dependent format, strong pT dependency at high eta is however observed to be reduced in UL

    Double_t ijet_sf = 1.0;
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution#Run2_JER_uncertainty_correlation
    //- in region |eta| < 1.93 use one pT bin: (0,Inf); - in region 1.93 < |eta| < 2.5 use one pT bin: (0,Inf) 
    switch (m_JERSys)
    {
    case 0:
        if(m_isRun3){
            ijet_sf = corr_jerSF->evaluate({eta, pt, "nom"});
        }else{
            ijet_sf = corr_jerSF->evaluate({eta, "nom"});
        }
        break;
    case 1:
        if(m_isRun3){
            ijet_sf = corr_jerSF->evaluate({eta, pt, "up"});
        }else{
            ijet_sf = corr_jerSF->evaluate({eta, "up"});
        }
        break;
    case 2:
        if(m_isRun3){
            ijet_sf = corr_jerSF->evaluate({eta, pt, "down"});
        }else{
            ijet_sf = corr_jerSF->evaluate({eta, "down"});
        }
        break;
    default:
        // std::cout << "!!!JER sf not getting correctly\n";
        return 1.0;
        break;
    }

    // Int_t genMatchIndex = OS::genMatchForJER(ieta, iphi, ipt, *e->GenJet_eta, *e->GenJet_phi, *e->GenJet_pt, ijet_res);
    // Double_t ijet_res = corr_jerResolution->evaluate({{pt, eta, rho}}); // !!!jet_resolution, there are fixedGridRhoFastjetCentral and others, not sure which rho to use?
    Double_t ijet_res = corr_jerResolution->evaluate({{ eta, pt, rho}}); // !!!jet_resolution, there are fixedGridRhoFastjetCentral and others, not sure which rho to use?
    Int_t genMatchIndex = OS::genMatchForJER(eta, phi, pt, genEta, genPhi, genPt, ijet_res);

    if (genMatchIndex > 0)
    {
        // Case 1: we have a "good" generator level jet matched to the reconstructed jet
        // Double_t dPt = ipt - (*e->GenJet_pt)[genMatchIndex];
        Double_t dPt = pt - genPt[genMatchIndex];
        iSF = 1 + (ijet_sf - 1.) * dPt / pt;
    }
    else
    { // Case 2: we don't have a gen jet. Smear jet pt using a random gaussian variation
        Double_t sigma = ijet_res * std::sqrt(ijet_sf * ijet_sf - 1);
        std::normal_distribution<> d(0, sigma);
        iSF = 1. + d(m_random_generator); // m_random_generator = std::mt19937(seed) //std::uint32_t>("seed", 37428479);
    }
    const Double_t MIN_JET_ENERGY = 1e-2;
    if (ienergy * iSF < MIN_JET_ENERGY)
    {
        // Negative or too small smearFactor. We would change direction of the jet
        // and this is not what we want.
        // Recompute the smearing factor in order to have jet.energy() == MIN_JET_ENERGY
        Double_t newSmearFactor = MIN_JET_ENERGY / ienergy;
        iSF = newSmearFactor;
    }

    return iSF;
}

//!!!no need, do it in Later steps
// void pushBackJESSF(Double_t eta, Double_t pt){
//     if(m_JESSys==0){
//         return;
//     };

//     Double_t JES_uncer = 0.;
//     std::array<Double_t, 27> ijets_JES_uncer;
//    for(UInt_t i =0; i<OS::JES_uncer.size(); i++){
//         auto corr_jesUncer = cset_jerSF->at(corr_Uncer_JES_map[m_era].at(m_JESSysUncerType).Data());
//         JES_uncer = corr_jesUncer->evaluate({eta, pt}); // do you need the pt to be raw? no
//         //std::cout << JES_uncer << " JES_uncerValue" << std::endl;
//         ijets_JES_uncer[i] = JES_uncer;
//     }
//     jets_JES_uncer.push_back(ijets_JES_uncer);

// }

Double_t JetSel::calJES_SF(Double_t area, Double_t eta, Double_t pt, Double_t pho){
    Double_t JES_SF = 1.0;
    Double_t JES_uncer = 0.;
    if (!m_isRun3)
    {//https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jecUncertainties.py
        auto corr_jesUncer = cset_jerSF->at(corr_SF_map[m_era].at(1).Data());
        // auto corr_jesUncer = cset_jerSF->at(corr_Uncer_JES_map[m_era].at(m_JESSysUncerType).Data());
        JES_uncer = corr_jesUncer->evaluate({eta, pt}); // do you need the pt to be raw? no
        //std::cout << JES_uncer << " JES_uncerValue" << std::endl;
    }else{
        TString L1Tag;
        TString L2Tag;
        TString L3Tag;
        TString L2L3Re;
        TString compound;//???compound not working
        if (m_isData)
        {
            // L1Tag = jesTagData.at(m_era).at(0) + jesTagDataRuns.at(m_processName) + jesTagData.at(m_era).at(2);
            // L2Tag = jesTagData.at(m_era).at(0) + jesTagDataRuns.at(m_processName) + jesTagData.at(m_era).at(3);
            // L3Tag = jesTagData.at(m_era).at(0) + jesTagDataRuns.at(m_processName) + jesTagData.at(m_era).at(4);
            // L2L3Re= jesTagData.at(m_era).at(0) + jesTagDataRuns.at(m_processName) + jesTagData.at(m_era).at(5);
            compound = jesTagData.at(m_era).at(0) + jesTagDataRuns.at(m_processName) + "_V2_DATA_L1L2L3Res_AK4PFPuppi";//Summer22_22Sep2023_RunCD_V2_DATA_L1L2L3Res_AK4PFPuppi
        }
        else
        {
            // L1Tag = jesTagMC.at(m_era).at(0);
            // L2Tag = jesTagMC.at(m_era).at(1);
            // L3Tag = jesTagMC.at(m_era).at(2);
            compound = jesTagMC.at(m_era).at(3); // Summer22_22Sep2023_V2_MC_L1L2L3Res_AK4PFPuppi
            auto corr_jesUncer = cset_jerSF->at(jesTagMC.at(m_era).at(4).Data());
            JES_uncer = corr_jesUncer->evaluate({eta, pt}); 
        }
        // auto corr_JESSF_L1 = cset_jerSF->at(L1Tag.Data()); // L1FastJet
        // auto corr_JESSF_L2 = cset_jerSF->at(L2Tag.Data()); // L2Relative
        // auto corr_JESSF_L3 = cset_jerSF->at(L3Tag.Data());
        // std::cout << compound << "\n";
        auto corr_JESSF_compound = cset_jerSF->compound().at(compound.Data());//!!!
        JES_SF = corr_JESSF_compound->evaluate({area, eta, pt, pho});

    }

    switch(m_JESSys){
        case 0:
            return JES_SF;
            break;
        case 1: //up
            return JES_SF * (1 + JES_uncer);
            break;
        case 2:
            return JES_SF * (1 - JES_uncer);
            break;
        default:
            return 1.0;
            break;
    }
}

void JetSel::clearBranch()
{
    jets_pt.clear();
    jets_eta.clear();
    jets_phi.clear();
    jets_mass.clear();
    jets_flavour.clear();
    jets_btags.clear();
    // jets_btagsPN.clear();
    // jets_btagsPT.clear();
};

std::vector<Double_t> &JetSel::getEtaVec()
{
    return jets_eta;
};
std::vector<Double_t> &JetSel::getPhiVec()
{
    return jets_phi;
};

Int_t JetSel::getSize()
{
    return jets_pt.size();
}

Double_t JetSel::getHT(){
    Double_t HT = 0;
    for (UInt_t i = 0; i < jets_pt.size(); i++)
    {
        HT += jets_pt[i];
    }
    return HT;
};

Double_t JetSel::get6thPt(){
    return jets_pt.size()>5?jets_pt[5]:-99;
}

Bool_t JetSel::jetVetoMap(Double_t eta, Double_t phi){
//    https://cms-jerc.web.cern.ch/Recommendations/#jet-veto-maps
    // if(!m_isRun3){
    //     return kFALSE;
    // }
    if(m_era!="2018"){
        return kFALSE;
    }

    //!json file can not handle |phi|>3.14159; veto it mannually
    if(TMath::Abs(phi)>3.14159){
        return kTRUE;
    }

    auto corr_jetVeto = cset_jetVeto->at(corr_SF_map[m_era].at(3).Data());
    // Double_t veto = corr_jetVeto->evaluate({"jetvetomap", eta, phi}); //"Non-zero value for (eta, phi) indicates that the region is vetoed."
    Double_t veto = corr_jetVeto->evaluate({"jetvetomap_hem1516", eta, phi}); //"Non-zero value for (eta, phi) indicates that the region is vetoed."
    //compare veto with 0.
    if(TMath::Abs(veto)>1e-9){
        return kTRUE;
    }else{
        return kFALSE;
    }
}
