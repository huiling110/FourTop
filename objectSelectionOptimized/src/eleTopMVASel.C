#include "../include/eleTopMVASel.h"
#include "../myLibrary/commenFunction.h"
#include "../include/inputMap.h"

EleTopMVASel::EleTopMVASel(TTree *outTree, const TString era, const Bool_t isData, const Bool_t isRun3, const Int_t type, const UChar_t eleScale, const UChar_t eleSmear) : m_type{type}, m_era{era}, m_isData{isData}, m_isRun3{isRun3}, m_eleScale{eleScale}, m_eleSmear{eleSmear}
{ // type for different electrons
    std::cout << "Initializing EleTopMVASel......\n";
    std::cout << "m_era=" << m_era << "  ;m_isRun3=" << m_isRun3 << "  ;m_type=" << m_type << "\n";
    std::cout<< "m_eleScale="<<static_cast<Int_t>(m_eleScale)<<"  ;m_eleSmear="<<static_cast<Int_t>(m_eleSmear)<<"\n";

    outTree->Branch("elesTopMVA" +WPMap.at(m_type)+ "_pt", &elesTopMVAT_pt);
    outTree->Branch("elesTopMVA" +WPMap.at(m_type)+ "_eta", &elesTopMVAT_eta);
    outTree->Branch("elesTopMVA" +WPMap.at(m_type)+ "_phi", &elesTopMVAT_phi);
    outTree->Branch("elesTopMVA" +WPMap.at(m_type)+ "_mass", &elesTopMVAT_mass);
    outTree->Branch("elesTopMVA" +WPMap.at(m_type)+ "_charge", &elesTopMVAT_charge);
    outTree->Branch("elesTopMVA" +WPMap.at(m_type)+ "_topMVAScore", &elesTopMVAT_topMVAScore);
    outTree->Branch("elesTopMVA" +WPMap.at(m_type)+ "_genPartFlav", &elesTopMVAT_genPartFlav);

    if(m_type == 1){
        outTree->Branch("elesTopMVAF_isTight", &elesTopMVAF_isTight);
        outTree->Branch("elesTopMVAF_jetIdx", &elesTopMVAF_jetIdx);
        outTree->Branch("elesTopMVAF_ptConeCorreted", &elesTopMVAF_ptConeCorreted);
    }


    // set up xgboost booster
    TString baseDir = "./";
    TString eleWeight = baseDir+ TopMVALeptonMap[m_era].at(0);
    std::cout << "eleWeight: " << eleWeight << "\n";
    // BoosterHandle booster;
    XGBoosterCreate(NULL, 0, &m_booster[0]);
    XGBoosterLoadModel(m_booster[0], eleWeight.Data());

    //energy scale and smearing for run 2:
    //https://github.com/cms-egamma/ScaleFactorsJSON/tree/master
    // TString jsonBase = "../../jsonpog-integration/POG/";
    cset_eleScale = correction::CorrectionSet::from_file(eleScaleSmear.at(m_era).at(0).Data());
    std::cout << "eleScale: " <<eleScaleSmear.at(m_era).at(0).Data() << "\n";
    // cset_eleScale = correction::CorrectionSet::from_file((jsonBase + eleScaleSmear.at(m_era).at(0)).Data());



    std::cout << "Done EleTopMVASel initialization......\n";
    std::cout << "\n";
};

EleTopMVASel::~EleTopMVASel()
{
    XGBoosterFree(m_booster[0]);
};

void EleTopMVASel::Select(const eventForNano *e, const std::vector<Double_t>& muEtaVec, const std::vector<Double_t>& muPhiVec)
{
    clearBranch();
    // 0: loose, 2: tight; 1: fake
    // POG: 4: veto; 5:POG loose
    for (UInt_t j = 0; j < e->Electron_pt.GetSize(); ++j)
    {
        Double_t pt = e->Electron_pt.At(j);
        Double_t eta = e->Electron_eta.At(j);
        Double_t topMVAScore = -99.;
        //branches different between run2 and run3
        Int_t iE_cutBased = m_isRun3? std::any_cast<UChar_t>(e->Electron_cutBased.at(j)): std::any_cast<Int_t>(e->Electron_cutBased.at(j));
        Int_t iE_tightCharge = m_isRun3? std::any_cast<UChar_t>(e->Electron_tightCharge.at(j)): std::any_cast<Int_t>(e->Electron_tightCharge.at(j));
        Int_t iE_jetIdx = m_isRun3? std::any_cast<Short_t>(e->Electron_jetIdx.at(j)): std::any_cast<Int_t>(e->Electron_jetIdx.at(j));
        Double_t mvaFall17V2noIso = m_isRun3? e->Electron_mvaNoIso->At(j): e->Electron_mvaFall17V2noIso->At(j);

        //Energy scale and resolution corrections
        //Up to NanoAOD10, residual energy scale and resolution corrections are applied to the stored electrons to match the data

        if (!(fabs(eta) < 2.5 && !(fabs(eta)>1.442&&fabs(eta)<1.566)))// 1.4442 and 1.566 are the transition region between the barrel and the endcap
            continue;
        if (!(pt > 10))
            continue;
        //Overlap removal with fakeable muons 
        Bool_t removeMu = OS::overlapRemove(eta, e->Electron_phi.At(j), muEtaVec, muPhiVec, 0.05);// for electrons the cone size is 0.05//???maybe too small the the cone size for muon is 0.3
        if(removeMu){
            continue;
        }

        if (m_type == 5)
        {
            if(!(iE_cutBased >= 2))// cut-based ID Fall17 V2 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
                continue;
        }
        if (m_type == 4)
        {
            if (!(iE_cutBased >= 1))
                continue;
        }
        if (m_type == 0 || m_type == 2 || m_type == 1)
        {
            // IP
            if (!(fabs(e->Electron_dxy.At(j)) < 0.05))
                continue;
            if (!(fabs(e->Electron_dz.At(j)) < 0.1))
                continue;
            if (!((e->Electron_ip3d.At(j)) < 8))
                continue;
            // Iso
            if (!(e->Electron_miniPFRelIso_all.At(j) < 0.4)) // mini PF relative isolation, total (with scaled rho*EA PU corrections)
                continue;

            if (!(int(e->Electron_lostHits.At(j)) < 1))
                continue;
        }
        if (m_type == 2|| m_type == 1)
        {
            if (!e->Electron_convVeto.At(j))
                continue;                             // the number of missing pixel hits and a conversion veto based on the vertex fit probability. To reject electrons originating from photon conversion
            if (!(iE_tightCharge > 0)) //??? Tight charge criteria (0:none, 1:isGsfScPixChargeConsistent, 2:isGsfCtfScPixChargeConsistent)
                continue;
            // TOP UL Lepton MVA
            Float_t jetPtRatio = 1. / (e->Electron_jetRelIso[j] + 1.);
            Float_t jetBTag = e->Jet_btagDeepFlavB[iE_jetIdx];
            std::map<TString, Float_t> inputFeatures = {
                {"pt", e->Electron_pt[j]},
                {"eta", e->Electron_eta[j]},
                {"jetNDauCharged", e->Electron_jetNDauCharged.At(j)},
                {"miniPFRelIso_chg", e->Electron_miniPFRelIso_chg[j]},
                {"miniPFRelIso_all", e->Electron_miniPFRelIso_all[j]},
                {"jetPtRelv2", e->Electron_jetPtRelv2[j]},//Relative momentum of the lepton with respect to the closest jet after subtracting the lepton
                {"jetPtRatio", jetPtRatio},
                {"pfRelIso03_all", e->Electron_pfRelIso03_all[j]},
                {"jetBTag", jetBTag},
                {"sip3d", e->Electron_sip3d[j]},
                {"dxy", e->Electron_dxy[j]},
                {"dz", e->Electron_dz[j]},
                {"mvaFall17V2noIso", mvaFall17V2noIso},
            }; // only for 2022
            topMVAScore = OS::TopLeptonEvaluate(inputFeatures, m_booster[0]);
            Bool_t isTight = topMVAScore > 0.81;

            if(m_type ==2){
                if (!isTight) continue;
            }else if(m_type ==1){//Fakeable electron same as SS of 4tops
                // Bool_t ifFake = e->Electron_mvaFall17V2noIso_WPL[j] && jetBTag<0.1 && jetPtRatio>0.5;
                Bool_t ifFake = e->Electron_mvaFall17V2noIso_WPL[j] && jetBTag<0.1 && jetPtRatio>m_ptRatioCutF.at(m_era);
                if (!(isTight || ifFake )) continue;
                elesTopMVAF_isTight.push_back(isTight);
                elesTopMVAF_jetIdx.push_back(iE_jetIdx); // Electron_jetIdx
                elesTopMVAF_ptConeCorreted.push_back(pt*jetPtRatio);
            }
        }

        elesTopMVAT_pt.push_back(e->Electron_pt.At(j));
        elesTopMVAT_eta.push_back(e->Electron_eta.At(j));
        elesTopMVAT_phi.push_back(e->Electron_phi.At(j));
        elesTopMVAT_mass.push_back(e->Electron_mass.At(j));
        elesTopMVAT_charge.push_back(e->Electron_charge.At(j));
        // elesTopMVAT_index.push_back(j);
        elesTopMVAT_topMVAScore.push_back(topMVAScore);
        if(!m_isData){
            elesTopMVAT_genPartFlav.push_back(e->Electron_genPartFlav->At(j));
        }
    } //
    m_eleTotal = elesTopMVAT_pt.size();
};

void EleTopMVASel::clearBranch()
{
    elesTopMVAT_pt.clear();
    elesTopMVAT_eta.clear();
    elesTopMVAT_phi.clear();
    elesTopMVAT_mass.clear();
    elesTopMVAT_charge.clear();
    elesTopMVAT_topMVAScore.clear();
    elesTopMVAT_genPartFlav.clear();
    elesTopMVAF_jetIdx.clear();
    elesTopMVAF_ptConeCorreted.clear();
    elesTopMVAF_isTight.clear();
};

std::vector<Double_t> &EleTopMVASel::getEtaVec()
{
    return elesTopMVAT_eta;
};
std::vector<Double_t> &EleTopMVASel::getPhiVec()
{
    return elesTopMVAT_phi;
};

Int_t EleTopMVASel::getSize()
{
    return elesTopMVAT_pt.size();
};
ULong_t EleTopMVASel::getTotal()
{
    return m_eleTotal;
};