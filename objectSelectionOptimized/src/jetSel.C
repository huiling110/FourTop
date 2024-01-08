#include "../include/jetSel.h"
#include <map>

JetSel::JetSel(TTree *outTree, const TString era, const Bool_t isRun3, const Int_t jetType) : m_jetType{jetType}, m_era{era}, m_isRun3{isRun3}
{ // m_type for different electrons
    // 1:loose;2:fakeble;3:tight
    std::cout << "Initializing JetSel: m_jetType=" << m_jetType << "......\n";

    TString jsonBase = "../../jsonpog-integration/POG/";
    cset_jerSF = correction::CorrectionSet::from_file((jsonBase + json_map[era].at(0)).Data());
    std::cout << "JEC sf file: " << (jsonBase + json_map[era].at(0)).Data() << "\n";
    for (auto &corr : *cset_jerSF)  
    {
        printf("Correction: %s\n", corr.first.c_str());
    }

    std::map<Int_t, TString> jetTypeMap = {
        {0, "jets"},
        {1, "jetsT"},
        {11, "bjetsL"},
        {12, "bjetsM"},
        {13, "bjetsT"},
        {2, "forward"},
        {15, "bjetsPNM"},
        {16, "bjetsPNT"},
    };

    ULong64_t seed = 37428479;
    m_random_generator = std::mt19937(seed); //

    outTree->Branch(jetTypeMap[m_jetType] + "_pt", &jets_pt);
    outTree->Branch(jetTypeMap[m_jetType] + "_eta", &jets_eta);
    outTree->Branch(jetTypeMap[m_jetType] + "_phi", &jets_phi);
    outTree->Branch(jetTypeMap[m_jetType] + "_mass", &jets_mass);
    outTree->Branch(jetTypeMap[m_jetType] + "_flavour", &jets_flavour);
    outTree->Branch(jetTypeMap[m_jetType] + "_btags", &jets_btags);

    std::cout << "Done JetSel initialization......\n";
    std::cout << "\n";
};

JetSel::~JetSel(){};

void JetSel::Select(eventForNano *e, const Bool_t isData, const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &muPhiVec, const std::vector<Double_t> &eEtaVec, const std::vector<Double_t> &ePhiVec, const std::vector<Double_t> &tauEtaVec, const std::vector<Double_t> &tauPhiVec, const Bool_t deepJet, const Int_t JER, const Int_t sysJEC)
{
    // jetType=0  -> usual jets; we use loose ID; jetType = 1: tight ID
    // jetType=11 -> b-jets L, jetType=12 -> b-jets M, jetType=13 -> b-jets T, jetType=2  -> forward jets
    //jetType 15: b-jetPNM, 16: b-jetPNT
    //jetType: 0: normal jet is tight jetID
    // JER: 0: nominal, 1: up, 2: down; 3: no JER
    // JES: 0: nominal; 1:up; 2: down; 
    clearBranch();
    calJER_SF(e, isData, JER);

    for (UInt_t j = 0; j < e->Jet_pt.GetSize(); ++j)
    {
        Int_t ijet_jetID = OS::getValForDynamicReader<UChar_t>(m_isRun3, e->Jet_jetId, j);
        Int_t ijet_hadronFlavour = OS::getValForDynamicReader<UChar_t>(m_isRun3, e->Jet_hadronFlavour, j);

        Double_t jetpt = e->Jet_pt.At(j);
        Double_t ijetMass = e->Jet_mass.At(j);
        Double_t ijetEta = e->Jet_eta.At(j);
        Double_t ijetPhi = e->Jet_phi.At(j);
        // maybe scaling only changes pt and mass? yes!
        switch (sysJEC)
        {
        case 0:
            break;
        case 1:
            jetpt = jetpt * (1 + jets_JESuncer[j]);
            ijetMass *= (1 + jets_JESuncer[j]);
            break;
        case 2:
            jetpt *= (1 - jets_JESuncer[j]);
            ijetMass *= (1 - jets_JESuncer[j]);
            break;
        default:
            break;
        }
        //first JES and then JER
        if (JER<3)
        {
            jetpt = jetpt * JER_SF_new.at(j);
            ijetMass = ijetMass * JER_SF_new.at(j);
        }

        // here SF_up or SF_down should also be apllied.
        if (!(jetpt > 25))
            continue;
        // if (!(fabs(ijetEta) < 5.0))
        if (!(fabs(ijetEta) < 2.4))
            continue;
        // if (!(ijet_jetID > 0))
        if (!(ijet_jetID > 2))
            continue; // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        // Jet ID flags bit1 is loose (always ：wfalse in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        // passlooseID*1+passtightID*2+passtightLepVetoID*4
        if (m_jetType == 1)
        {
            if (!(ijet_jetID > 2))
                continue; // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        }

             // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
        if (m_jetType == 11)
        {
            if (!(e->Jet_btagDeepFlavB.At(j) > DeepJetL[m_era]))
                continue;
        }else if (m_jetType == 12)
        {
            if (!(e->Jet_btagDeepFlavB.At(j) > DeepJetM[m_era]))
                continue;
        }else if (m_jetType == 13 )
        {
            if (!(e->Jet_btagDeepFlavB.At(j) > DeepJetT[m_era]))
                continue;
        }else if(m_jetType == 15 && m_isRun3){
            if (!(e->Jet_btagPNetB->At(j) > particleNetBMT.at(m_era).at(0)))
                continue;
        }else if(m_jetType == 16 && m_isRun3){
            if (!(e->Jet_btagPNetB->At(j) > particleNetBMT.at(m_era).at(1)))
                continue;
        }
        // overlap removal
        Bool_t removeMu = OS::overlapRemove(e->Jet_eta.At(j), e->Jet_phi.At(j), muEtaVec, muPhiVec);
        Bool_t removeE = OS::overlapRemove(e->Jet_eta.At(j), e->Jet_phi.At(j), eEtaVec, ePhiVec);
        Bool_t removeTau = OS::overlapRemove(e->Jet_eta.At(j), e->Jet_phi.At(j), tauEtaVec, tauPhiVec);
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
        else
        {
            jets_flavour.push_back(-99);
        }
        // if (deepJet)
        // {
        if (m_isRun3){
            jets_btags.push_back(e->Jet_btagPNetB->At(j));
        }else{
            jets_btags.push_back(e->Jet_btagDeepFlavB.At(j));
        }
        // }
        // else
        // {
            // jets_btags.push_back(e->Jet_btagDeepB.At(j));
        // }
    }
};

void JetSel::calJER_SF(eventForNano *e, const Bool_t isData, const Int_t sys)
{
    // https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/jercExample.py
    // https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Uncertai
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
    // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h
    //https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetSmearer.py
    auto corr_jerSF = cset_jerSF->at(corr_SF_map[m_era].at(0).Data());
    auto corr_jerResolution = cset_jerSF->at(corr_SF_map[m_era].at(2).Data());

    // https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetmetHelperRun2.py
    auto corr_jesUncer = cset_jerSF->at(corr_SF_map[m_era].at(1).Data());
    //???does the MC_Total include the JER uncertainty?
    //!!!not sure how to get the JEC uncertainty for data yet?

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
        // std::cout << "Jet_rawFactor=" << Jet_rawFactor[i] << "\n";
        // Double_t rawJetPt = ipt * (1 - Jet_rawFactor[i]);

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
        // jer_sf_up.push_back(iSF_up);
        // jer_sf_down.push_back(iSF_down);
        jets_JESuncer.push_back(iSF_JESuncer);
    }
};

void JetSel::clearBranch()
{
    jets_pt.clear();
    jets_eta.clear();
    jets_phi.clear();
    jets_mass.clear();
    jets_flavour.clear();
    jets_btags.clear();
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