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

    if(m_type ==0){
        outTree->Branch("lepTopMVAT_2ifZVeto", &lepTopMVAT_2ifZVeto);
    }

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
        outTree->Branch("lepTopMVAF_isAR", &lepTopMVAF_isAR);//only for data
        outTree->Branch("elesTopMVAF_1ptCorrected", &elesTopMVAF_1ptCorrected);
        outTree->Branch("elesTopMVAF_2ptCorrected", &elesTopMVAF_2ptCorrected);
        outTree->Branch("muonsTopMVAF_1ptCorrected", &muonsTopMVAF_1ptCorrected);
        outTree->Branch("muonsTopMVAF_2ptCorrected", &muonsTopMVAF_2ptCorrected);
        outTree->Branch("lepTopMVAF_1ptCorrected", &lepTopMVAF_1ptCorrected);
        outTree->Branch("lepTopMVAF_2ptCorrected", &lepTopMVAF_2ptCorrected);
        outTree->Branch("elesTopMVAF_num", &elesTopMVAF_num);
        outTree->Branch("muonsTopMVAF_num", &muonsTopMVAF_num);

        outTree->Branch("triggerSFLep_weight", &triggerSFLep_weight);
        outTree->Branch("triggerSFLep_weight_up", &triggerSFLep_weight_up);
        outTree->Branch("triggerSFLep_weight_down", &triggerSFLep_weight_down);


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

    triggerCal = new TriggerScaleFactorCalculator(m_era);

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


    if(m_type==0) {
        lepTopMVAT_2ifZVeto = kFALSE ; //OSSF
        if(e->elesTopMVAT_pt.GetSize() == 2){
           if(e->elesTopMVAT_charge.At(0) *e->elesTopMVAT_charge.At(1)==-1){
                if(TMath::Abs(InvariantMassCalculator(eles)) > 76 && TMath::Abs(InvariantMassCalculator(eles)) < 106){//Zmass=91
                    lepTopMVAT_2ifZVeto = kTRUE; // should veto this event if it's true
                }
            }
        }else if(e->muonsTopMVAT_pt.GetSize() == 2){
            if( (e->muonsTopMVAT_charge.At(0) *e->muonsTopMVAT_charge.At(1)==-1)){
                if(TMath::Abs(InvariantMassCalculator(mus)) > 76 && TMath::Abs(InvariantMassCalculator(mus)) < 106){//Zmass=91
                    lepTopMVAT_2ifZVeto = kTRUE;
                }
            }
        }
    };

    if(m_type==1){//fakeble lepton
        const UInt_t muonSize = e->muonsTopMVAF_isTight.GetSize(); 
        const UInt_t eleSize = e->elesTopMVAF_isTight.GetSize();
        elesTopMVAF_1isTight = eleSize > 0 ? e->elesTopMVAF_isTight.At(0) : kFALSE;
        elesTopMVAF_2isTight = eleSize > 1 ? e->elesTopMVAF_isTight.At(1) : kFALSE;
        muonsTopMVAF_1isTight = muonSize > 0 ? e->muonsTopMVAF_isTight.At(0) : kFALSE;
        muonsTopMVAF_2isTight = muonSize > 1 ? e->muonsTopMVAF_isTight.At(1) : kFALSE;
        elesTopMVAF_num = eleSize;
        muonsTopMVAF_num = muonSize;

        if (!m_isData)
        {
            elesTopMVAF_1isTightPrompt = eleSize > 0 ? e->elesTopMVAF_isTight.At(0)&& (e->elesTopMVAF_genPartFlav.At(0)==1||e->elesTopMVAF_genPartFlav.At(0)==15) : kFALSE;  //???bug here for ttbar_2l; strange thing with eleSize=1 genSize=0 for ttbar_2l
            elesTopMVAF_2isTightPrompt = eleSize > 1 ? e->elesTopMVAF_isTight.At(1)&& (e->elesTopMVAF_genPartFlav.At(1)==1||e->elesTopMVAF_genPartFlav.At(1)==15) : kFALSE;
            muonsTopMVAF_1isTightPrompt = muonSize > 0 ? e->muonsTopMVAF_isTight.At(0)&& (e->muonsTopMVAF_genPartFlav.At(0)==1||e->muonsTopMVAF_genPartFlav.At(0)==15) : kFALSE;
            muonsTopMVAF_2isTightPrompt = muonSize > 1 ? e->muonsTopMVAF_isTight.At(1)&& (e->muonsTopMVAF_genPartFlav.At(1)==1||e->muonsTopMVAF_genPartFlav.At(1)==15) : kFALSE;
        }

        if (muonSize + eleSize == 1)
        { // lepMVATopF=1
            processSingleLep(e, muonSize, eleSize);
        }
        else if (muonSize + eleSize == 2)
        {
            processingDoubleLep(e, muonSize, eleSize);
        }
    }//m_type==1
}



void LepVarMaker::processSingleLep(const EventForMV* e, const UInt_t muonSize, const UInt_t eleSize){
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
                Double_t FR = TTTT::get2DSF(e->muonsTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->muonsTopMVAF_eta.At(0)), muFR_h, 0);
                lepTopMVAF_FRweight = FR / (1. - FR); //! dangerous
                muonsTopMVAF_1ptCorrected = e->muonsTopMVAF_ptConeCorreted.At(0);
                lepTopMVAF_1ptCorrected = muonsTopMVAF_1ptCorrected;
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
                Double_t FR = TTTT::get2DSF(e->elesTopMVAF_ptConeCorreted.At(0), TMath::Abs(e->elesTopMVAF_eta.At(0)), eleFR_h, 0);
                lepTopMVAF_FRweight = FR / (1. - FR); //! dangerous
                elesTopMVAF_1ptCorrected = e->elesTopMVAF_ptConeCorreted.At(0);
                lepTopMVAF_1ptCorrected = elesTopMVAF_1ptCorrected;

            }
        }
    }

};

void LepVarMaker::processingDoubleLep(const EventForMV* e, const UInt_t muonSize, const UInt_t eleSize){
    if (muonSize == 1)
    {
        if (e->muonsTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(0))
        {
            lepTopMVAF_FRweight = 1.0;
            lepTopMVAF_isAR = kFALSE;
            triggerSFLep_weight = triggerCal->getScaleFactor("me", e->muonsTopMVAF_pt.At(0), e->elesTopMVAF_pt.At(0), m_isData, 0);
            // std::cout<<"triggerSFLep_weight: "<<triggerSFLep_weight<<std::endl;
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
                    // lepTopMVAF_1ptConeCorreted = lep_ptConeCorrected.size()>0? lep_ptConeCorrected.at(0): -99;//!Correct pt based on if the lepton is Fake notT
                    muonsTopMVAF_1ptCorrected = e->muonsTopMVAT_pt.At(0);//!do not correct pt if it is tight
                    elesTopMVAF_1ptCorrected = e->elesTopMVAF_ptConeCorreted.At(0);//! only correct if it's not tight

                }
                else if (!e->muonsTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(0))
                {
                    lepTopMVAF_FRweight = FR1 / (1. - FR1);
                    muonsTopMVAF_1ptCorrected = e->muonsTopMVAF_ptConeCorreted.At(0);
                    elesTopMVAF_1ptCorrected = e->elesTopMVAT_pt.At(0);

                }
                else
                {
                    lepTopMVAF_FRweight = -(FR1 * FR2 / (1. - FR1) / (1. - FR2));
                    muonsTopMVAF_1ptCorrected = e->muonsTopMVAF_ptConeCorreted.At(0);
                    elesTopMVAF_1ptCorrected = e->elesTopMVAF_ptConeCorreted.At(0);
                }
                lepTopMVAF_1ptCorrected = muonsTopMVAF_1ptCorrected>elesTopMVAF_1ptCorrected? muonsTopMVAF_1ptCorrected: elesTopMVAF_1ptCorrected;
                lepTopMVAF_2ptCorrected = muonsTopMVAF_1ptCorrected<elesTopMVAF_1ptCorrected? muonsTopMVAF_1ptCorrected: elesTopMVAF_1ptCorrected;
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
                    muonsTopMVAF_1ptCorrected = e->muonsTopMVAT_pt.At(0);
                    muonsTopMVAF_2ptCorrected = e->muonsTopMVAF_ptConeCorreted.At(1);
                }
                else if (!e->muonsTopMVAF_isTight.At(0) && e->muonsTopMVAF_isTight.At(1))
                {
                    lepTopMVAF_FRweight = FR1 / (1. - FR1);
                    muonsTopMVAF_1ptCorrected = e->muonsTopMVAF_ptConeCorreted.At(0);
                    muonsTopMVAF_2ptCorrected = e->muonsTopMVAT_pt.At(1);
                }
                else
                {
                    lepTopMVAF_FRweight = -(FR1 * FR2 / (1. - FR1) / (1. - FR2));
                    muonsTopMVAF_1ptCorrected = e->muonsTopMVAF_ptConeCorreted.At(0);
                    muonsTopMVAF_2ptCorrected = e->muonsTopMVAF_ptConeCorreted.At(1);
                }
                lepTopMVAF_1ptCorrected = muonsTopMVAF_1ptCorrected>muonsTopMVAF_2ptCorrected? muonsTopMVAF_1ptCorrected: muonsTopMVAF_2ptCorrected;
                lepTopMVAF_2ptCorrected = muonsTopMVAF_1ptCorrected<muonsTopMVAF_2ptCorrected? muonsTopMVAF_1ptCorrected: muonsTopMVAF_2ptCorrected;
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
                    elesTopMVAF_1ptCorrected = e->elesTopMVAT_pt.At(0);
                    elesTopMVAF_2ptCorrected = e->elesTopMVAF_ptConeCorreted.At(1);
                }
                else if (!e->elesTopMVAF_isTight.At(0) && e->elesTopMVAF_isTight.At(1))
                {
                    lepTopMVAF_FRweight = FR1 / (1. - FR1);
                    lepTopMVAF_isAR = kTRUE;
                    elesTopMVAF_1ptCorrected = e->elesTopMVAF_ptConeCorreted.At(0);
                    elesTopMVAF_2ptCorrected = e->elesTopMVAT_pt.At(1);
                }
                else
                {
                    lepTopMVAF_FRweight = -(FR1 * FR2 / (1. - FR1) / (1. - FR2));
                    lepTopMVAF_isAR = kTRUE;
                    elesTopMVAF_1ptCorrected = e->elesTopMVAF_ptConeCorreted.At(0);
                    elesTopMVAF_2ptCorrected = e->elesTopMVAF_ptConeCorreted.At(1);
                }
                lepTopMVAF_1ptCorrected = elesTopMVAF_1ptCorrected>elesTopMVAF_2ptCorrected? elesTopMVAF_1ptCorrected: elesTopMVAF_2ptCorrected;
                lepTopMVAF_2ptCorrected = elesTopMVAF_1ptCorrected<elesTopMVAF_2ptCorrected? elesTopMVAF_1ptCorrected: elesTopMVAF_2ptCorrected;
            }
        }
    }
}//lepF_num==2



void LepVarMaker::clearBranch(){
    ObjVarMaker::clearBranch();
    lepTopMVAT_2invariantMass = -99;
    lepTopMVAT_2pt = -99;
    lepTopMVAT_2eta = -99;
    lepTopMVAT_2phi = -99;
    lepTopMVAF_isAR = kFALSE;

    lepTopMVAF_1ptCorrected = -99;
    lepTopMVAF_2ptCorrected = -99;
    muonsTopMVAF_1ptCorrected = -99;
    muonsTopMVAF_2ptCorrected = -99;
    elesTopMVAF_1ptCorrected = -99;
    elesTopMVAF_2ptCorrected = -99;

    lepTopMVAF_FRweight = 1.0;
    elesTopMVAF_1isTight = kFALSE;
    elesTopMVAF_2isTight = kFALSE;
    muonsTopMVAF_1isTight = kFALSE;
    muonsTopMVAF_2isTight = kFALSE;
    elesTopMVAF_1isTightPrompt = kFALSE;
    elesTopMVAF_2isTightPrompt = kFALSE;
    muonsTopMVAF_1isTightPrompt = kFALSE;
    muonsTopMVAF_2isTightPrompt = kFALSE;

    elesTopMVAF_num = -99;
    muonsTopMVAF_num = -99;
}

void LepVarMaker::setupLorentzObjs(const EventForMV *e){
    switch(m_type){
        case 0:
            getLorentzVec(e->elesTopMVAT_pt, e->elesTopMVAT_eta, e->elesTopMVAT_phi, e->elesTopMVAT_mass, eles);
            getLorentzVec(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, e->muonsTopMVAT_phi, e->muonsTopMVAT_mass, mus);
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
    delete triggerCal;
    std::cout<<"Deleting LepVarMaker"<<std::endl;
}

Double_t LepVarMaker::get1pt(){
    return muons_1pt;
};
Double_t LepVarMaker::get2pt(){
    return lepTopMVAT_2pt;
}

