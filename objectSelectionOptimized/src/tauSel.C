#include "../include/tauSel.h"
#include <map>
#include "../include/usefulFunc.h"
#include "../../src_cpp/lumiAndCrossSection.h"  

TauSel::TauSel(TTree *outTree, const TString era, Bool_t isData, Bool_t isRun3, const Int_t tauWP, const UChar_t TES) : m_tauWP{tauWP}, m_era{era}, m_isData{isData}, m_isRun3{isRun3}, m_TES{TES}
{ // m_type for different electrons
    // 1:loose;2:fakeble;3:tight
    std::cout << "Initializing TauSel......\n";
    std::cout << "m_tauWP=" << m_tauWP<<" m_era="<<m_era<<" m_isRun3="<<m_isRun3 << " m_TES="<<static_cast<unsigned int>(m_TES)<<"\n";

    TString jsonBase = "../../jsonpog-integration/POG/";
    cset_tauSF = correction::CorrectionSet::from_file((jsonBase + TTTT::json_map.at(era).at(1)).Data());
    std::cout << "tau energy sf file: " << (jsonBase + TTTT::json_map.at(era).at(1)).Data() << "\n";

    std::map<Int_t, TString> tauWPMap = {
        {1, "L"},
        {2, "F"}, //
        {3, "T"}, //Medium WP 
        {4, "TT"}, //tight tauVsJet ID
        {5, "TTT"},
        {6, "M"} ,//Loose
        {7, "TTTT"},
    };

    outTree->Branch("taus" + tauWPMap[tauWP] + "_pt", &taus_pt);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_eta", &taus_eta);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_phi", &taus_phi);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_mass", &taus_mass);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_decayMode", &taus_decayMode);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_genPartFlav", &taus_genPartFlav);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_jetIdx", &taus_jetIdx);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_charge", &taus_charge);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_neutralIso", &taus_neutralIso);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_jetPt", &taus_jetPt);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_jetEta", &taus_jetEta);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_jetMass", &taus_jetMass);
    outTree->Branch("taus" + tauWPMap[tauWP] + "_jetPhi", &taus_jetPhi);
    if(m_tauWP==2){
        outTree->Branch("tausF_isTight", &taus_isTight);
    }

    std::cout << "Done TauSel initialization......\n\n";
};

TauSel::~TauSel(){};

void TauSel::Select( const eventForNano *e, const Bool_t isData, const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &muPhiVec, const std::vector<Double_t> &eEtaVec, const std::vector<Double_t> &ePhiVec)
{
    // this is tau ID in ttH
    // 1:loose;2:fakeble;3:tight
    //https://twiki.cern.ch/twiki/bin/view/CMS/TauIDRecommendationForRun3#Choice_of_the_tau_ID_algorithm
    clearBranch();
    //!!Here looping throug tau collection multiple times for different WP, not very efficient
    // but then there's chanllenge of replicates of tau variables for different WP

    for (UInt_t j = 0; j < e->Tau_pt.GetSize(); ++j)
    {
        //branches different in nanoAODv9 and nanoAODv12
        Int_t itau_decayMode = OS::getValForDynamicReader<UChar_t>(m_isRun3, e->Tau_decayMode, j);
        Int_t itau_jetIdx = OS::getValForDynamicReader<Short_t>(m_isRun3, e->Tau_jetIdx, j);//Short_t for Tau_jetIdx
        Int_t itau_charge = OS::getValForDynamicReader<Short_t>(m_isRun3, e->Tau_charge, j);

        Double_t itau_pt = e->Tau_pt.At(j);
        Double_t iTES = 1.0;
        if(!m_isData){
            calTES(itau_decayMode, itau_pt, e->Tau_eta.At(j), e->Tau_genPartFlav->At(j), tauVsJetWP.at(m_tauWP)); // TES handled inside the function
        }
        // std::cout<<"iTES="<<iTES<<"\n";
        itau_pt *= iTES;
        Double_t itau_mass = e->Tau_mass.At(j)*iTES;

        if (!(itau_pt > 20))
            continue;
        if (m_isRun3){
            if(!(TMath::Abs(e->Tau_eta.At(j)) < 2.5))
                continue;
        }else{
            if (!(TMath::Abs(e->Tau_eta.At(j)) < 2.3))
                continue;
        }
        if (!(TMath::Abs(e->Tau_dz.At(j)) < 0.2))
            continue;
        // if (m_isRun3){
        //     if (!(e->Tau_idDecayModeNewDMs->At(j))) //already applied in nanoAOD
        //         continue; // for 2022
        // }
        Int_t tauID_vsJet = m_isRun3 ? e->Tau_idDeepTau2018v2p5VSjet->At(j) : e->Tau_idDeepTau2017v2p1VSjet.At(j);////!!! for nanoAOD v12, tau id has no bit mast!!!
        Int_t tauID_vsEle = m_isRun3 ? e->Tau_idDeepTau2018v2p5VSe->At(j) : e->Tau_idDeepTau2017v2p1VSe.At(j);
        Int_t tauID_vsMu = m_isRun3 ? e->Tau_idDeepTau2018v2p5VSmu->At(j) : e->Tau_idDeepTau2017v2p1VSmu.At(j);


        Bool_t isVSjetVVLoose = m_isRun3 ? (tauID_vsJet >= 2) : (tauID_vsJet & (1 << 1)); // check if the 2nd bit (VVLoose WP) is 1
            //1 = VVVLoose, 2 = VVLoose, 3 = VLoose, 4 = Loose, 5 = Medium, 6 = Tight, 7 = VTight, 8 = VVTight
        Bool_t isVSjetM = m_isRun3 ? (tauID_vsJet >= 5) : (tauID_vsJet & (1 << 4)); // check if the 4th bit (Medium WP) is 1
        Bool_t isVSjetT = m_isRun3 ? (tauID_vsJet >= 6) : (tauID_vsJet & (1 << 5)); // check if the 5th bit (Tight WP) is 1
        Bool_t isVSjetTT = m_isRun3 ? (tauID_vsJet >= 7) : (tauID_vsJet & (1 << 6)); // check if the 6th bit (TTight WP) is 1
        Bool_t isVSjetTTT = m_isRun3 ? (tauID_vsJet >= 8) : (tauID_vsJet & (1 << 7)); // check if the 7th bit (TTight WP) is 1
        Bool_t isVSjetTTTT = m_isRun3 ? (tauID_vsJet >= 9) : (tauID_vsJet & (1 << 8)); // check if the 8th bit (TTight WP) is 1


        Bool_t isVSeVVVLoose = m_isRun3 ? (tauID_vsEle >= 2) : (tauID_vsEle & (1 << 0));  // check if the 1st bit (VVVLoose WP) is 1
        Bool_t isVSmuVLoose = m_isRun3 ? (tauID_vsMu >= 3) : (tauID_vsMu & (1 << 0));    // check if the 1st bit (VLoose WP) is 1

        switch (m_tauWP)
        {
        case 1:
            if (!isVSjetVVLoose)
                continue;
            break;
        case 2:
            if (!(isVSjetVVLoose && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (itau_decayMode == 5 || itau_decayMode == 6)
                continue;
            break;
        case 3:
            if (!(isVSjetM && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (itau_decayMode == 5 || itau_decayMode == 6)
                continue;
            break;
        case 4:
            if (!(isVSjetT && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (itau_decayMode == 5 || itau_decayMode == 6)
                continue;
            break;
        case 5:
            if (!(isVSjetTT && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (itau_decayMode == 5 || itau_decayMode == 6)
                continue;
            break;
        case 6:
            if (!(isVSjetTTT && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (itau_decayMode == 5 || itau_decayMode == 6)
                continue;
            break;
        case 7:
            if (!(isVSjetTTTT && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (itau_decayMode == 5 || itau_decayMode == 6)
                continue;
            break; 
        default:
            break;
        }



        // overlap removal
        Bool_t removeTau = OS::overlapRemove(e->Tau_eta.At(j), e->Tau_phi.At(j), muEtaVec, muPhiVec);
        Bool_t removeTauWithE = OS::overlapRemove(e->Tau_eta.At(j), e->Tau_phi.At(j), eEtaVec, ePhiVec);
        if(removeTau || removeTauWithE){
            continue;
        }

        taus_pt.push_back(itau_pt);
        taus_eta.push_back(e->Tau_eta.At(j));
        taus_phi.push_back(e->Tau_phi.At(j));
        taus_mass.push_back(itau_mass);
        // taus_decayMode.push_back(e->Tau_decayMode.At(j));//!!!
        taus_decayMode.push_back(itau_decayMode);
        if (!isData)
        {
            taus_genPartFlav.push_back(e->Tau_genPartFlav->At(j));
        }
        else
        {
            taus_genPartFlav.push_back(-99);
        }
        taus_jetIdx.push_back(itau_jetIdx);
        taus_charge.push_back(itau_charge);
        taus_neutralIso.push_back(e->Tau_neutralIso.At(j));
        taus_jetPt.push_back(e->Jet_pt.At(itau_jetIdx)); //! jet pt here not corrected, should be corrected
        taus_jetEta.push_back(e->Jet_eta.At(itau_jetIdx));
        taus_jetMass.push_back(e->Jet_mass.At(itau_jetIdx));
        taus_jetPhi.push_back(e->Jet_phi.At(itau_jetIdx));
        //
        if(m_tauWP==2){
            taus_isTight = isVSjetM && isVSeVVVLoose && isVSmuVLoose && !(itau_decayMode == 5 || itau_decayMode == 6);
        } 
    }
};

void TauSel::calTauSF_new(const eventForNano *e, const Bool_t isData)
{
    // https://gitlab.cern.ch/cms-tau-pog/jsonpog-integration/-/blob/master/examples/tauExample.py
    auto corr_tauES = cset_tauSF->at("tau_energy_scale");
    //???i assume it contains the correction to genuine tau and genuine electrons?
    taus_TES.clear();
    taus_TES_up.clear();
    taus_TES_down.clear();

    Double_t iTES_sf = 1.0;
    Double_t iTES_sf_up = 1.0;
    Double_t iTES_sf_down = 1.0;
    for (UInt_t i = 0; i < e->Tau_pt.GetSize(); i++)
    {
        if (!isData)
        {
            // corr4.evaluate(pt,eta,dm,5,"DeepTau2017v2p1",syst)
            // no sf for decaymode 5 and 6
            // Int_t itau_decayMode = OS::getValForDynamicReader(m_isRun3, e->Tau_decayMode, i);
            Int_t itau_decayMode = OS::getValForDynamicReader<UChar_t>(m_isRun3, e->Tau_decayMode, i);

            if (!(itau_decayMode == 5 || itau_decayMode == 6))//!!!
            {
                // iTES_sf = corr_tauES->evaluate({e->Tau_pt.At(i), e->Tau_eta.At(i), itau_decayMode, e->Tau_genPartFlav->At(i), "DeepTau2017v2p1", "nom"});
                // iTES_sf_up = corr_tauES->evaluate({e->Tau_pt.At(i), e->Tau_eta.At(i), itau_decayMode, e->Tau_genPartFlav->At(i), "DeepTau2017v2p1", "up"});
                // iTES_sf_down = corr_tauES->evaluate({e->Tau_pt.At(i), e->Tau_eta.At(i), itau_decayMode, e->Tau_genPartFlav->At(i), "DeepTau2017v2p1", "down"});
                //!!!2022, diffrent format, input: pt, eta, dm, genmatch, id, wp, wp_VSe, syst
                iTES_sf = corr_tauES->evaluate({e->Tau_pt.At(i), e->Tau_eta.At(i), itau_decayMode, e->Tau_genPartFlav->At(i), "DeepTau2018v2p5", "Medium", "VVLoose", "nom"}); 
                //??? "DeepTau2018v2p5VSjet working point: Loose-VTight"; "DeepTau2018v2p5VSe working point: VVLoose-Tight"
                //!what does this mean?
                //no VVVLoose vsEle
                std::cout<<"pass tau_decayMode\n";
            }
            std::cout << "iTES_sf: " << iTES_sf << "\n";
            // std::cout << "iTES_sf_up: " << iTES_sf_up << "\n";
            // std::cout << "iTES_sf_down: " << iTES_sf_down << "\n";
        }
        taus_TES.push_back(iTES_sf);
        taus_TES_up.push_back(iTES_sf_up);
        taus_TES_down.push_back(iTES_sf_down);
    }
};


Double_t TauSel::calTES(Int_t itau_decayMode, Double_t itau_pt, Double_t itau_eta, Int_t itau_genPartFlav, std::string tauVsJetWP)
{
    //
    auto corr_tauES = cset_tauSF->at("tau_energy_scale");
    Double_t iTES_sf = 1.0;
    if(!m_isData && !(itau_decayMode == 5 || itau_decayMode == 6)){
        switch (m_TES)
        {
        case 0:
            if (m_isRun3){
                iTES_sf = corr_tauES->evaluate({itau_pt, itau_eta, itau_decayMode, itau_genPartFlav, "DeepTau2018v2p5", tauVsJetWP, "VVLoose", "nom"}); 
            }else{
                iTES_sf = corr_tauES->evaluate({itau_pt, itau_eta, itau_decayMode, itau_genPartFlav, "DeepTau2017v2p1", "nom"});
            }
            break;
        case 1:
            if (m_isRun3){
                iTES_sf = corr_tauES->evaluate({itau_pt, itau_eta, itau_decayMode, itau_genPartFlav, "DeepTau2018v2p5", tauVsJetWP, "VVLoose", "up"}); 
            }else{
                iTES_sf = corr_tauES->evaluate({itau_pt, itau_eta, itau_decayMode, itau_genPartFlav, "DeepTau2017v2p1", "up"});
            }
            break;
        case 2:
            if(m_isRun3){
                iTES_sf = corr_tauES->evaluate({itau_pt, itau_eta, itau_decayMode, itau_genPartFlav, "DeepTau2018v2p5", tauVsJetWP, "VVLoose", "down"}); 
            }else{
                iTES_sf = corr_tauES->evaluate({itau_pt, itau_eta, itau_decayMode, itau_genPartFlav, "DeepTau2017v2p1", "down"});
            }
            break;
        default:
            break;
        }
    }
    // if(itau_genPartFlav==0){
    //     std::cout<<"TES_sf: "<<iTES_sf<<"\n";
    // }
    // std::cout<<"itau_genPartFlav="<<itau_genPartFlav<<" iTES_sf="<<iTES_sf<<"\n";

    return iTES_sf;
};


void TauSel::clearBranch()
{
    taus_pt.clear();
    taus_eta.clear();
    taus_phi.clear();
    taus_mass.clear();
    taus_decayMode.clear();
    taus_genPartFlav.clear();
    taus_jetIdx.clear();
    taus_charge.clear();
    taus_neutralIso.clear();
    taus_jetPt.clear();
    taus_jetEta.clear();
    taus_jetMass.clear();
    taus_jetPhi.clear();
    taus_isTight = kFALSE;
};

std::vector<Double_t> &TauSel::getEtaVec()
{
    return taus_eta;
};
std::vector<Double_t> &TauSel::getPhiVec()
{
    return taus_phi;
};
//!!!this could all be put in a base class
Int_t TauSel::getSize()
{
    return taus_pt.size();
};