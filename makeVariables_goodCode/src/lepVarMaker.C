#include "../include/lepVarMaker.h"
#include "../include/inputMap_MV.h"
#include "../include/variablesFunctions.h"
#include "../../myLibrary/commenFunction.h"

LepVarMaker::LepVarMaker(TTree* outTree, TString era, const Bool_t isData, TString objName, const UInt_t type):ObjVarMaker(outTree, objName, type), m_era{era}, m_isData{isData}{
   std::cout<<"Initializing LepVarMaker"<<std::endl;

    outTree->Branch(objName+ "_2invariantMass", &lepTopMVAT_2invariantMass);
    outTree->Branch(objName+ "_2pt", &lepTopMVAT_2pt);
    outTree->Branch(objName+ "_2eta", &lepTopMVAT_2eta);
    outTree->Branch(objName+ "_2phi", &lepTopMVAT_2phi);
    outTree->Branch(objName+ "_2charge", &lepTopMVAT_2charge);

    if(type==1){
        outTree->Branch(  "elesTopMVAF_1isTight", &elesTopMVAF_1isTight);
        outTree->Branch(  "elesTopMVAF_2isTight", &elesTopMVAF_2isTight);
        outTree->Branch(  "elesTopMVAF_1isTightPrompt", &elesTopMVAF_1isTightPrompt);
        outTree->Branch(  "elesTopMVAF_2isTightPrompt", &elesTopMVAF_2isTightPrompt);
        outTree->Branch(  "muonsTopMVAF_1isTight", &muonsTopMVAF_1isTight);
        outTree->Branch(  "muonsTopMVAF_2isTight", &muonsTopMVAF_2isTight);
        outTree->Branch(  "muonsTopMVAF_1isTightPrompt", &muonsTopMVAF_1isTightPrompt);
        outTree->Branch(  "muonsTopMVAF_2isTightPrompt", &muonsTopMVAF_2isTightPrompt);
        outTree->Branch(  "lepTopMVAF_FRweight", &lepTopMVAF_FRweight);
        outTree->Branch(  "lepTopMVAF_1ptConeCorreted", &lepTopMVAF_1ptConeCorreted);
        outTree->Branch(  "lepTopMVAF_2ptConeCorreted", &lepTopMVAF_2ptConeCorreted);
        outTree->Branch("lepTopMVAF_isAR", &lepTopMVAF_isAR);//only for data
        // outTree->Branch("lepTopMVAF_isTightPrompt", &lepTopMVAF_isTightPrompt);//only for mc


        std::map<TString, TString> eraHistMap = {
            {"2016preVFP", "2016Merged"},
            {"2016postVFP", "2016Merged"},
            {"2017", "2017"},
            {"2018", "2018"},
        };
        eleFR_h = TTTT::getHistogramFromFile<TH2D>(MV::lepFR_map.at(m_era).at(0), "fakeRate_electron_"+eraHistMap.at(m_era));
        muFR_h = TTTT::getHistogramFromFile<TH2D>(MV::lepFR_map.at(m_era).at(1), "fakeRate_muon_"+eraHistMap.at(m_era));
        std::cout<<"electron FR file used: "<<MV::lepFR_map.at(m_era).at(0)<<"\n";
        std::cout<<"muon FR file used: "<<MV::lepFR_map.at(m_era).at(1)<<"\n";
    }

   std::cout<<"Initialization done\n\n";
}

void LepVarMaker::makeVariables(const EventForMV* e){
    clearBranch();
    setupLorentzObjs(e);
    basicVariables();

    lepTopMVAT_2invariantMass =  muons_num>1? InvariantMassCalculator(objsLorentz): -99;
    lepTopMVAT_2pt = muons_num > 1 ? objsLorentz[1].Pt() : -99;
    lepTopMVAT_2eta = muons_num > 1 ? objsLorentz[1].Eta() : -99;
    lepTopMVAT_2phi = muons_num > 1 ? objsLorentz[1].Phi() : -99;

    if(m_type==1){//fakeble lepton
        UInt_t muonSize = e->muonsTopMVAF_isTight.GetSize(); 
        UInt_t eleSize = e->elesTopMVAF_isTight.GetSize();
        elesTopMVAF_1isTight = eleSize > 0 ? e->elesTopMVAF_isTight.At(0) : kFALSE;
        elesTopMVAF_2isTight = eleSize > 1 ? e->elesTopMVAF_isTight.At(1) : kFALSE;
        muonsTopMVAF_1isTight = muonSize > 0 ? e->muonsTopMVAF_isTight.At(0) : kFALSE;
        muonsTopMVAF_2isTight = muonSize > 1 ? e->muonsTopMVAF_isTight.At(1) : kFALSE;

        lep_ptConeCorrected.clear();
        for (UInt_t i = 0; i < muonSize; i++)
        {
            lep_ptConeCorrected.push_back(e->muonsTopMVAF_ptConeCorreted.At(i));
        }
        for(UInt_t i=0; i<eleSize; i++){
            lep_ptConeCorrected.push_back(e->elesTopMVAF_ptConeCorreted.At(i));
        }
        std::sort(lep_ptConeCorrected.begin(), lep_ptConeCorrected.end(), std::greater<Double_t>());
        lepTopMVAF_1ptConeCorreted = lep_ptConeCorrected.size()>0? lep_ptConeCorrected.at(0): -99;
        lepTopMVAF_2ptConeCorreted = lep_ptConeCorrected.size()>1? lep_ptConeCorrected.at(1): -99;

        if (!m_isData)
        {
            elesTopMVAF_1isTightPrompt = eleSize > 0 ? e->elesTopMVAF_isTight.At(0)&& (e->elesTopMVAF_genPartFlav.At(0)==1||e->elesTopMVAF_genPartFlav.At(0)==15) : kFALSE;  
            elesTopMVAF_2isTightPrompt = eleSize > 1 ? e->elesTopMVAF_isTight.At(1)&& (e->elesTopMVAF_genPartFlav.At(1)==1||e->elesTopMVAF_genPartFlav.At(1)==15) : kFALSE;
            muonsTopMVAF_1isTightPrompt = muonSize > 0 ? e->muonsTopMVAF_isTight.At(0)&& (e->muonsTopMVAF_genPartFlav.At(0)==1||e->muonsTopMVAF_genPartFlav.At(0)==15) : kFALSE;
            muonsTopMVAF_2isTightPrompt = muonSize > 1 ? e->muonsTopMVAF_isTight.At(1)&& (e->muonsTopMVAF_genPartFlav.At(1)==1||e->muonsTopMVAF_genPartFlav.At(1)==15) : kFALSE;
        }
            UInt_t FR = -99.;
            if (muonSize + eleSize == 1)
            { // lepMVATopF=1
                if (muonSize == 1)
                {
                    if (e->muonsTopMVAF_isTight.At(0))
                    {
                        lepTopMVAF_FRweight = 1.0;
                        lepTopMVAF_isAR = kFALSE;
                    }
                    else
                    {
                        lepTopMVAF_isAR = kTRUE;
                        if(m_isData){
                            FR = TTTT::get2DSF(e->muonsTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->muonsTopMVAF_eta.At(0)), muFR_h, 0);
                        lepTopMVAF_FRweight = FR / (1. - FR); //! dangerous
                        }
                    }
                }
                else
                {
                    if (e->elesTopMVAF_isTight.At(0))
                    {
                        lepTopMVAF_FRweight = 1.0;
                        lepTopMVAF_isAR = kFALSE;
                        // lepTopMVAF_isTightPrompt =m_isData? kFALSE; e->elesTopMVAF_isTightPrompt.At(0);
                    }
                    else
                    {
                        lepTopMVAF_isAR = kTRUE;
                        if(m_isData){
                            FR = TTTT::get2DSF(e->elesTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->elesTopMVAF_eta.At(0)), eleFR_h, 0);
                            lepTopMVAF_FRweight = FR / (1. - FR); //! dangerous
                        }
                    }
                }
            }
            else if (muonSize + eleSize == 2)
            {
                if (muonSize == 1)
                {
                    if (e->muonsTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(0))
                    {
                        lepTopMVAF_FRweight = 1.0;
                        lepTopMVAF_isAR = kFALSE;
                        // lepTopMVAF_isTightPrompt = m_isData? kFALSE: e->muonsTopMVAF_isTightPrompt.At(0) || e->elesTopMVAF_isTightPrompt.At(0);
                    }
                    else
                    {
                        lepTopMVAF_isAR = kTRUE;
                        if(m_isData){
                            Double_t FR1 = TTTT::get2DSF(e->muonsTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->muonsTopMVAF_eta.At(0)), muFR_h, 0);
                            Double_t FR2 = TTTT::get2DSF(e->elesTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->elesTopMVAF_eta.At(0)), eleFR_h, 0);
                            if (e->muonsTopMVAF_isTight.At(0) && !e->elesTopMVAF_isTight.At(0))
                            {
                                lepTopMVAF_FRweight = FR2 / (1. - FR2);
                            }
                            else if (!e->muonsTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(0))
                            {
                                lepTopMVAF_FRweight = FR1 / (1. - FR1);
                            }
                            else
                            {
                                lepTopMVAF_FRweight = -(FR1 * FR2 / (1. - FR1) / (1. - FR2));
                            }
                        }
                    }
                }
                else if (muonSize == 2)
                {
                    if (e->muonsTopMVAF_isTight.At(0) && e->muonsTopMVAF_isTight.At(1))
                    {
                        lepTopMVAF_FRweight = 1.0;
                        lepTopMVAF_isAR = kFALSE;
                    }
                    else{
                        lepTopMVAF_isAR = kTRUE;
                        if(m_isData){
                            Double_t FR1 = TTTT::get2DSF(e->muonsTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->muonsTopMVAF_eta.At(0)), muFR_h, 0);
                            Double_t FR2 = TTTT::get2DSF(e->muonsTopMVAF_ptConeCorreted.At(1), TMath::Abs(e->muonsTopMVAF_eta.At(1)), muFR_h, 0);
                            if (e->muonsTopMVAF_isTight.At(0) && !e->muonsTopMVAF_isTight.At(1))
                            {
                                lepTopMVAF_FRweight = FR2 / (1. - FR2);
                            }
                            else if (!e->muonsTopMVAF_isTight.At(0) && e->muonsTopMVAF_isTight.At(1))
                            {
                                lepTopMVAF_FRweight = FR1 / (1. - FR1);
                            }
                            else
                            {
                                lepTopMVAF_FRweight = -(FR1 * FR2 / (1. - FR1) / (1. - FR2));
                            }
                        }
                    }
                }
                else
                { // muonSize==0
                    if (e->elesTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(1))
                    {
                        lepTopMVAF_FRweight = 1.0;
                        lepTopMVAF_isAR = kFALSE;
                    }else{
                        lepTopMVAF_isAR = kTRUE;
                        if(m_isData){
                            Double_t FR1 = TTTT::get2DSF(e->elesTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->elesTopMVAF_eta.At(0)), eleFR_h, 0);
                            Double_t FR2 = TTTT::get2DSF(e->elesTopMVAF_ptConeCorreted.At(1), TMath::Abs(e->elesTopMVAF_eta.At(1)), eleFR_h, 0);
                            if (e->elesTopMVAF_isTight.At(0) && !e->elesTopMVAF_isTight.At(1))
                            {
                                lepTopMVAF_FRweight = FR2 / (1. - FR2);
                            }
                            else if (!e->elesTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(1))
                            {
                                lepTopMVAF_FRweight = FR1 / (1. - FR1);
                                lepTopMVAF_isAR = kTRUE;
                            }
                            else
                            {
                                lepTopMVAF_FRweight = -(FR1 * FR2 / (1. - FR1) / (1. - FR2));
                                lepTopMVAF_isAR = kTRUE;
                            }
                        }
                    }
                }
            }
            // std::cout << "lepTopMVAF_FRweight=" << lepTopMVAF_FRweight << "\n";
        // } // m_isData
    }//m_type==1
}

void LepVarMaker::clearBranch(){
    ObjVarMaker::clearBranch();
    lepTopMVAT_2invariantMass = -99;
    lepTopMVAT_2pt = -99;
    lepTopMVAT_2eta = -99;
    lepTopMVAT_2phi = -99;
    lepTopMVAF_1ptConeCorreted = -99.;
    lepTopMVAF_2ptConeCorreted = -99;
    lepTopMVAF_isAR = kFALSE;

    lepTopMVAF_FRweight = 1.0;
    elesTopMVAF_1isTight = kFALSE;
    elesTopMVAF_2isTight = kFALSE;
    muonsTopMVAF_1isTight = kFALSE;
    muonsTopMVAF_2isTight = kFALSE;
    elesTopMVAF_1isTightPrompt = kFALSE;
    elesTopMVAF_2isTightPrompt = kFALSE;
    muonsTopMVAF_1isTightPrompt = kFALSE;
    muonsTopMVAF_2isTightPrompt = kFALSE;
}

// void LepVarMaker::setupLorentzObjs(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT){
void LepVarMaker::setupLorentzObjs(const EventForMV *e){
    // objsLorentz.clear();
    // for (UInt_t i = 0; i < leptonsMVAT.size(); i++){
    //     objsLorentz.push_back(leptonsMVAT[i]);
    // }
    switch(m_type){
        case 0:
            getLorentzVec(e->elesTopMVAT_pt, e->elesTopMVAT_eta, e->elesTopMVAT_phi, e->elesTopMVAT_mass, eles);
            getLorentzVec(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, e->muonsTopMVAT_phi, e->muonsTopMVAT_mass, mus);
        // std::vector<ROOT::Math::PtEtaPhiMVector> leptonsMVAT;
        // addLorentzVector(muonTopTVarMaker.getLorentzObjs(), eleTopVarMaker.getLorentzObjs(), leptonsMVAT);//Pt already sorted
            addLorentzVector(mus, eles, objsLorentz);
            break;
        case 1:
            getLorentzVec(e->elesTopMVAF_pt, e->elesTopMVAF_eta, e->elesTopMVAF_phi, e->elesTopMVAF_mass, eles);
            getLorentzVec(e->muonsTopMVAF_pt, e->muonsTopMVAF_eta, e->muonsTopMVAF_phi, e->muonsTopMVAF_mass, mus);
            addLorentzVector(mus, eles, objsLorentz);
            break;
        default:
            break;
    }
}

LepVarMaker::~LepVarMaker(){
    std::cout<<"Deleting LepVarMaker"<<std::endl;
}
