#include "../include/tauSel.h"
#include <map>

TauSel::TauSel(TTree *outTree, const TString era, Bool_t isRun3, const Int_t tauWP) : m_tauWP{tauWP}, m_era{era}, m_isRun3{isRun3}
{ // m_type for different electrons
    // 1:loose;2:fakeble;3:tight
    std::cout << "Initializing TauSel......\n";
    std::cout << "m_tauWP=" << m_tauWP<<" m_era="<<m_era<<" m_isRun3="<<m_isRun3 << "\n";

    TString jsonBase = "../../jsonpog-integration/POG/";
    cset_tauSF = correction::CorrectionSet::from_file((jsonBase + json_map[era].at(1)).Data());
    std::cout << "tau energy sf file: " << (jsonBase + json_map[era].at(1)).Data() << "\n";

    std::map<Int_t, TString> tauWPMap = {
        {1, "L"},
        {2, "F"},
        {3, "T"},
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

    std::cout << "Done TauSel initialization......\n\n";
};

TauSel::~TauSel(){};

// void TauSel::Select(const eventForNano *e, const Bool_t isData, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec, const Int_t sysTES)
void TauSel::Select(const eventForNano *e, const Bool_t isData, const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &muPhiVec, const std::vector<Double_t> &eEtaVec, const std::vector<Double_t> &ePhiVec,  const Int_t sysTES)
{
    // this is tau ID in ttH
    // 1:loose;2:fakeble;3:tight
    clearBranch();
    calTauSF_new(e, isData);//!!!for 2022???
    for (UInt_t j = 0; j < e->Tau_pt.GetSize(); ++j)
    {
        Double_t itau_pt = e->Tau_pt.At(j);
        Double_t itau_mass = e->Tau_mass.At(j);
        switch (sysTES)
        {
        case 0:
            itau_pt *= taus_TES[j];
            itau_mass *= taus_TES[j];
            break;
        case 1:
            itau_pt *= taus_TES_up[j];
            itau_mass *= taus_TES_up[j];
            break;
        case 2:
            itau_pt *= taus_TES_down[j];
            itau_mass *= taus_TES_down[j];
            break;
        default:
            // std::cout << "tau pt and mass not corrected!!!"
            //           << "\n";
            break;
        }

        if (!(itau_pt > 20))
            // if (!(itau_pt > 30))
            continue;
        if (!(e->Tau_eta.At(j) < 2.3 && e->Tau_eta.At(j) > -2.3))
            continue;
        if (!(TMath::Abs(e->Tau_dz.At(j)) < 0.2))
            continue;
        //???why no dxy requirement?
        // if (!(e->Tau_idDecayModeOldDMs.At(j) == 0))      continue;//already in NANOAOD
        UChar_t tauID_vsJet;
        UChar_t tauID_vsEle;
        UChar_t tauID_vsMu;
        // if(m_era.CompareTo("2022")==0){
        //  tauID_vsJet =  e->Tau_idDeepTau2018v2p5VSjet->At(j);
        //  tauID_vsEle =  e->Tau_idDeepTau2018v2p5VSe->At(j);
        //  tauID_vsMu =  e->Tau_idDeepTau2018v2p5VSmu->At(j);
        // }else{
        tauID_vsJet = e->Tau_idDeepTau2017v2p1VSjet.At(j);
        tauID_vsEle = e->Tau_idDeepTau2017v2p1VSe.At(j);
        tauID_vsMu = e->Tau_idDeepTau2017v2p1VSmu.At(j);
        //!!! for nanoAOD v11, tau id has no bit mast!!!
        // byDeepTau2017v2p1VSe ID working points (deepTau2017v2p1): 1 = VVVLoose, 2 = VVLoose, 3 = VLoose, 4 = Loose, 5 = Medium, 6 = Tight, 7 = VTight, 8 = VVTight
        // }

        Bool_t isVSjetVVLoose = kFALSE;
        Bool_t isVSeVVVLoose = kFALSE;
        Bool_t isVSmuVLoose = kFALSE;
        Bool_t isVSjetM = kFALSE;
        if (m_tauWP == 1)
        {
            if (m_isRun3)
            {
                isVSjetVVLoose = tauID_vsJet >= 2; // check if the 2nd bit (VVLoose WP) is 1
            }
            else
            {
                isVSjetVVLoose = tauID_vsJet & (1 << 1); // check if the 2nd bit (VVLoose WP) is 1
            }
            // bitwise shift operators are the right-shift operator (>>
            //&: bitwise and operator; only 1&1=1; 0&anything = 0
            // 1<<1 = 2 = 00000010
            // converting unsigned char to Bool_t: uchar_t ->int->Bool_t; if 2nd bit is 1 isVSjetVVLoose=true; if 2nd bit is 0 isVSjetVVLoose = false
            if (!isVSjetVVLoose)
                continue;
            // bitmask 1 = VVVLoose, 2 = VVLoose, 4 = VLoose, 8 = Loose, 16 = Medium, 32 = Tight, 64 = VTight, 128 = VVTight
        }
        if (m_tauWP == 2)
        {
            if (m_isRun3)
            {
                isVSjetVVLoose = tauID_vsJet >= 2; // check if the 2nd bit (VVLoose WP) is 1
                isVSeVVVLoose = tauID_vsEle >= 1;  // check if the 1st bit (VVVLoose WP) is 1
                isVSmuVLoose = tauID_vsMu >= 3;    // check if the 1st bit (VLoose WP) is 1
            }
            else
            {
                isVSjetVVLoose = tauID_vsJet & (1 << 1); // check if the 2nd bit (VVLoose WP) is 1
                isVSeVVVLoose = tauID_vsEle & (1 << 0);  // check if the 1st bit (VVVLoose WP) is 1
                isVSmuVLoose = tauID_vsMu & (1 << 0);    // check if the 1st bit (VLoose WP) is 1
            }
            if (!(isVSjetVVLoose && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (e->Tau_decayMode.At(j) == 5 || e->Tau_decayMode.At(j) == 6)
                continue;
        }
        if (m_tauWP == 3)
        { // channel specific in ttH. use the tight from 1t 1l
            if (m_isRun3)
            {
                isVSjetM = tauID_vsJet >= 5;      // check if the 5th bit (Medium WP) is 1
                isVSeVVVLoose = tauID_vsEle >= 1; // check if the 1st bit (VVVLoose WP) is 1
                isVSmuVLoose = tauID_vsMu >= 3;   // check if the 1st bit (VLoose WP) is 1
            }
            else
            {
                isVSjetM = tauID_vsJet & (1 << 4);      // check if the 5th bit (Medium WP) is 1
                isVSeVVVLoose = tauID_vsEle & (1 << 0); // check if the 1st bit (VVVLoose WP) is 1
                isVSmuVLoose = tauID_vsMu & (1 << 0);   // check if the 1st bit (VLoose WP) is 1
            }
            if (!(isVSjetM && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (e->Tau_decayMode.At(j) == 5 || e->Tau_decayMode.At(j) == 6)
                continue;
        }
        // overlap removal
        Bool_t removeTau = OS::overlapRemove(e->Tau_eta.At(j), e->Tau_phi.At(j), muEtaVec, muPhiVec);
        Bool_t removeTauWithE = OS::overlapRemove(e->Tau_eta.At(j), e->Tau_phi.At(j), eEtaVec, ePhiVec);
        // Double_t minDeltaR_lep;
        // std::cout<<"lepSize="<<lepEtaVec.size()<<"\n";
        // if (lepEtaVec.size() > 0)
        // {
        //     minDeltaR_lep = OS::deltRmin(e->Tau_eta.At(j), e->Tau_phi.At(j), lepEtaVec, lepPhiVec);
        //     if (!(minDeltaR_lep >= 0.4))
        //     {
        //         continue;
        //     }
        // }
        if(removeTau || removeTauWithE){
            continue;
        }

        taus_pt.push_back(itau_pt);
        taus_eta.push_back(e->Tau_eta.At(j));
        taus_phi.push_back(e->Tau_phi.At(j));
        taus_mass.push_back(itau_mass);
        taus_decayMode.push_back(e->Tau_decayMode.At(j));
        if (!isData)
        {
            taus_genPartFlav.push_back(e->Tau_genPartFlav->At(j));
        }
        else
        {
            taus_genPartFlav.push_back(-99);
        }
        taus_jetIdx.push_back(e->Tau_jetIdx.At(j));
        taus_charge.push_back(e->Tau_charge.At(j));
        taus_neutralIso.push_back(e->Tau_neutralIso.At(j));
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
            if (!(e->Tau_decayMode.At(i) == 5 || e->Tau_decayMode.At(i) == 6))
            {
                iTES_sf = corr_tauES->evaluate({e->Tau_pt.At(i), e->Tau_eta.At(i), e->Tau_decayMode.At(i), e->Tau_genPartFlav->At(i), "DeepTau2017v2p1", "nom"});
                iTES_sf_up = corr_tauES->evaluate({e->Tau_pt.At(i), e->Tau_eta.At(i), e->Tau_decayMode.At(i), e->Tau_genPartFlav->At(i), "DeepTau2017v2p1", "up"});
                iTES_sf_down = corr_tauES->evaluate({e->Tau_pt.At(i), e->Tau_eta.At(i), e->Tau_decayMode.At(i), e->Tau_genPartFlav->At(i), "DeepTau2017v2p1", "down"});
            }
            // std::cout << "iTES_sf: " << iTES_sf << "\n";
            // std::cout << "iTES_sf_up: " << iTES_sf_up << "\n";
            // std::cout << "iTES_sf_down: " << iTES_sf_down << "\n";
        }
        taus_TES.push_back(iTES_sf);
        taus_TES_up.push_back(iTES_sf_up);
        taus_TES_down.push_back(iTES_sf_down);
    }
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