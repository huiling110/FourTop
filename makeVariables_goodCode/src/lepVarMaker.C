#include "../include/lepVarMaker.h"
#include "../include/inputMap_MV.h"
#include "../include/variablesFunctions.h"
#include "../../myLibrary/commenFunction.h"

LepVarMaker::LepVarMaker(TTree* outTree, TString era, TString objName, const UInt_t type):ObjVarMaker(outTree, objName, type), m_era{era}{
   std::cout<<"Initializing LepVarMaker"<<std::endl;

    outTree->Branch(objName+ "_2invariantMass", &lepTopMVAT_2invariantMass);
    outTree->Branch(objName+ "_2pt", &lepTopMVAT_2pt);
    outTree->Branch(objName+ "_2eta", &lepTopMVAT_2eta);
    outTree->Branch(objName+ "_2phi", &lepTopMVAT_2phi);
    outTree->Branch(objName+ "_2charge", &lepTopMVAT_2charge);

    if(type==1){
        std::map<TString, TString> eraHistMap = {
            {"2016preVFP", "2016Merged"},
            {"2016postVFP", "2016Merged"},
            {"2017", "2017"},
            {"2018", "2018"},
        };
        outTree->Branch(objName + "_FRweight", &lepTopMVAF_FRweight);
        eleFR_h = TTTT::getHistogramFromFile<TH2D>(MV::lepFR_map.at(m_era).at(0), "fakeRate_electron_"+eraHistMap.at(m_era));
        muFR_h = TTTT::getHistogramFromFile<TH2D>(MV::lepFR_map.at(m_era).at(1), "fakeRate_muon_"+eraHistMap.at(m_era));
        std::cout<<"electron FR file used: "<<MV::lepFR_map.at(m_era).at(0)<<"\n";
        std::cout<<"muon FR file used: "<<MV::lepFR_map.at(m_era).at(1)<<"\n";
    }

   std::cout<<"Initialization done\n\n";
}

// void LepVarMaker::makeVariables(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT){
void LepVarMaker::makeVariables(const EventForMV* e){
    clearBranch();
    setupLorentzObjs(e);
    basicVariables();

    lepTopMVAT_2invariantMass =  muons_num>1? InvariantMassCalculator(objsLorentz): -99;
    lepTopMVAT_2pt = muons_num > 1 ? objsLorentz[1].Pt() : -99;
    lepTopMVAT_2eta = muons_num > 1 ? objsLorentz[1].Eta() : -99;
    lepTopMVAT_2phi = muons_num > 1 ? objsLorentz[1].Phi() : -99;

    //
    // lepTopMVAF_1isTight = muons_num > 0 ? e->muonsTopMVAF_isTight->at(0) : kFALSE;
    // lepTopMVAF_2isTight = ;
    // lepTopMVAF_1isTightPrompt = ;
    // lepTopMVAF_2isTightPrompt = ;
    
    // lepTopMVAF_FRweight = 1.0;
    // if(lepTopMVAF_1isTight && !lepTopMVAF_2isTight){
    //     lepTopMVAF_FRweight = 1.0; //FR2/1-FR2
    // }
    if(m_type==1){//fakeble lepton
        //for 1tau1l
        UInt_t muonSize = e->muonsTopMVAF_isTight.GetSize(); 
        UInt_t eleSize = e->elesTopMVAF_isTight.GetSize();
        UInt_t FR = 0;
        if(muonSize+eleSize ==1){//lepMVATopF=1
            if(muonSize==1){
                if(e->muonsTopMVAF_isTight.At(0)){
                    lepTopMVAF_FRweight = 1.0;
                }else{
                     FR = TTTT::get2DSF(e->muonsTopMVAF_pt.At(0), TMath::Abs(e->muonsTopMVAF_eta.At(0)), muFR_h, 0);
                    lepTopMVAF_FRweight = FR/(1.-FR);//!dangerous
                }
            }else{
                if(e->elesTopMVAF_isTight.At(0)){
                    lepTopMVAF_FRweight = 1.0;
                }else{
                    FR = TTTT::get2DSF(e->elesTopMVAF_pt.At(0), TMath::Abs(e->elesTopMVAF_eta.At(0)), eleFR_h, 0);
                    lepTopMVAF_FRweight = FR/(1.-FR);//!dangerous
                }
            }
        }else if(muonSize+eleSize==2){
            if(muonSize==1){
                if(e->muonsTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(0)){
                    lepTopMVAF_FRweight = 1.0;
                }else{
                    Double_t FR1 = TTTT::get2DSF(e->muonsTopMVAF_pt.At(0), TMath::Abs(e->muonsTopMVAF_eta.At(0)), muFR_h, 0);
                    Double_t FR2 = TTTT::get2DSF(e->elesTopMVAF_pt.At(0), TMath::Abs(e->elesTopMVAF_eta.At(0)), eleFR_h, 0);
                    if(e->muonsTopMVAF_isTight.At(0) && !e->elesTopMVAF_isTight.At(0)){
                        lepTopMVAF_FRweight = FR2/(1.-FR2);
                    }else if(!e->muonsTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(0)){
                        lepTopMVAF_FRweight = FR1/(1.-FR1);
                    }else{
                        lepTopMVAF_FRweight = -(FR1*FR2/(1.-FR1)/(1.-FR2));
                    }
                }
            }else if(muonSize==2){
                Double_t FR1 = TTTT::get2DSF(e->muonsTopMVAF_pt.At(0), TMath::Abs(e->muonsTopMVAF_eta.At(0)), muFR_h, 0);
                Double_t FR2 = TTTT::get2DSF(e->muonsTopMVAF_pt.At(1), TMath::Abs(e->muonsTopMVAF_eta.At(1)), muFR_h, 0);
                if(e->muonsTopMVAF_isTight.At(0) && e->muonsTopMVAF_isTight.At(1)){
                    lepTopMVAF_FRweight = 1.0;
                }else if(e->muonsTopMVAF_isTight.At(0) && !e->muonsTopMVAF_isTight.At(1)){
                    lepTopMVAF_FRweight = FR2/(1.-FR2);
                }else if(!e->muonsTopMVAF_isTight.At(0) && e->muonsTopMVAF_isTight.At(1)){
                    lepTopMVAF_FRweight = FR1/(1.-FR1);
                }else{
                    lepTopMVAF_FRweight = -(FR1*FR2/(1.-FR1)/(1.-FR2));
                }
            }else{//muonSize==0
                Double_t FR1 = TTTT::get2DSF(e->elesTopMVAF_pt.At(0), TMath::Abs(e->elesTopMVAF_eta.At(0)), eleFR_h, 0);
                Double_t FR2 = TTTT::get2DSF(e->elesTopMVAF_pt.At(1), TMath::Abs(e->elesTopMVAF_eta.At(1)), eleFR_h, 0);
                if(e->elesTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(1)){
                    lepTopMVAF_FRweight = 1.0;
                }else if(e->elesTopMVAF_isTight.At(0) && !e->elesTopMVAF_isTight.At(1)){
                    lepTopMVAF_FRweight = FR2/(1.-FR2);
                }else if(!e->elesTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(1)){
                    lepTopMVAF_FRweight = FR1/(1.-FR1);
                }else{
                    lepTopMVAF_FRweight = -(FR1*FR2/(1.-FR1)/(1.-FR2));
                }
            }
        }
        std::cout<<"lepTopMVAF_FRweight="<<lepTopMVAF_FRweight<<"\n";
    }
}

void LepVarMaker::clearBranch(){
    ObjVarMaker::clearBranch();
    lepTopMVAT_2invariantMass = -99;
    lepTopMVAT_2pt = -99;
    lepTopMVAT_2eta = -99;
    lepTopMVAT_2phi = -99;
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
