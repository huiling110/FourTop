// 
#include "../include/commenSelectionAndWeight.h"

Bool_t baselineSelection(event *event, const Bool_t isRun3, Bool_t is1tau2l)
{
    // Bool_t pass = event->jets_num.v() >= 6 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 500. && event->jets_6pt.v() > 40.;
    Bool_t pass = kFALSE;
    if (!isRun3){
        if(!is1tau2l){
            // pass = event->jets_num.v() >= 5 && event->bjetsM_num.v() >= 2 && event->jets_HT.v() > 450. && event->jets_6pt.v()>32.;//!this is it
            pass = event->jets_num.v() >= 6 && event->bjetsM_num.v() >= 2 && event->jets_HT.v() > 450. && event->jets_6pt.v()>34.;//!this is it
        }else{
            pass = event->jets_num.v() >= 4 && event->bjetsM_num.v() >= 2 && event->jets_HT.v() > 200. ;//!test for 1tau2l
        }
    }else{
        // std::cout << "not run 3\n";
        // pass = event->jets_num.v() >= 6 && event->bjetsPTM_num.v() >= 1 && event->jets_HT.v() > 550. && event->jets_6pt.v() > 40.;
        // pass = event->jets_num.v() >= 6 && event->bjetsPTM_num.v() >= 1 && event->jets_HT.v() > 550. && event->jets_6pt.v() > 30.;
        pass = event->jets_num.v() >= 5 && event->bjetsPTM_num.v() >= 2 && event->jets_HT.v() > 400. && event->tausM_num.v();//!testing
        // pass = event->jets_num.v() >= 5 && event->bjetsPTM_num.v() >= 1 && event->jets_HT.v() > 450. && event->tausM_num.v();//!testing
        // pass = event->jets_num.v() >= 5 && event->bjetsPTM_num.v() >= 1 && event->jets_HT.v() > 500. && event->tausM_num.v();//!testing
        // pass = event->jets_num.v() >= 6 && event->bjetsPTM_num.v() >= 1 && event->jets_HT.v() > 500. && event->tausM_num.v();//!testing
    }
    return pass;
}


Bool_t HLTSel(event *e, const TString m_era){
        // Bool_t is1muon = kTRUE;
        Bool_t ifHLT = kTRUE;
        if (m_era.CompareTo("2016") == 0)
        {
            // if (i == 0)
            // {
            //     std::cout << "HLT selection for 2016\n";
            // }
            ifHLT = e->HLT_PFHT450_SixJet40_BTagCSV_p056.v() == 1 || e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056.v() == 1 || e->HLT_PFJet450.v() == 1; // 2016
        }
        else if (m_era.CompareTo("2018") == 0)
        {
            ifHLT = e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() || e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2.v() || e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5.v() || e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59.v() || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94.v()|| e->HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5.v() ;
            // ifHLT = e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() || e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2.v()  || e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5.v() || e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59.v() || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94.v() ;
        }
        else if (m_era.CompareTo("2017") == 0)
        {
            // if (i == 0)
            // {
            //     std::cout << "HLT selection for 2017\n";
            // }
            ifHLT = e->HLT_PFHT430_SixJet40_BTagCSV_p080.v() == 1 || e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075.v() == 1 || e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() == 1 || e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2.v() == 1 || e->HLT_PFJet500.v() == 1;
        }else if(m_era.Contains("2022")){
            ifHLT = e->HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59.v() || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94.v()|| e->HLT_PFJet500.v();
        }else{
            std::cout<<"!!! no HLT selection\n";
        }

    return ifHLT;
}

Bool_t SR1tau1lSel(event *e, const Int_t channel, Bool_t isRun3, Bool_t isFakeTau )
{
    Int_t lepNum= 0;
    Int_t bjetsMNum = 0;
    Int_t tausTNum = 0;
    if (!isRun3)
    {
        lepNum = e->elesTopMVAT_num.v() + e->muonsTopMVAT_num.v();
        bjetsMNum = e->bjetsM_num.v();
        // tausTNum = e->tausT_num.v();
        tausTNum = isFakeTau ? e->tausF_num.v() : e->tausT_num.v();
    }
    else
    {
        lepNum = e->elesMVAT_num.v() + e->muonsT_num.v();
        // bjetsMNum = e->bjetsPNM_num.v();
        bjetsMNum = e->bjetsPTM_num.v();
        tausTNum = e->tausTT_num.v();
        // tausTNum = e->tausM_num.v();//!testing
    }
    Bool_t isPass = kFALSE;
    switch (channel)
    {
    case 0: // 1tau1lSR
        isPass = tausTNum == 1 && lepNum == 1 && e->jets_num.v() >= 7 && bjetsMNum >= 3 && e->jets_6pt.v()>34.;
        break;
    case 1: //!NEW 1tau0lSR
        isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum >= 3 && e->jets_6pt.v()>34.;
        // isPass = e->tausTT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum >= 3;
        break;
    case 2: // !1tau2lSR
        isPass = tausTNum == 1 && lepNum == 2 && e->jets_num.v() >= 4 && bjetsMNum >= 2;
        break;
    case 3: //!!! 1tau0l testing
        // isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() >= 9 && bjetsMNum>=3;
        // isPass = e->tausTT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum>=3;
        // isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum>=3;
        isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum>=3 && e->jets_HT.v()>550;
        break;
    case 4: //! 1tau1lCR2
        isPass = tausTNum == 1 && lepNum == 1 && e->jets_num.v() == 6 && bjetsMNum >= 3;
        break;
    case 5: // !1tau1lCR1
        isPass = tausTNum == 1 && lepNum == 1 && e->jets_num.v() >=6 && bjetsMNum ==2 ;
        break;
    case 6: // 1tau0lCR
        isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum == 0 ;
        break;
    case 7: // ! NEW 1tau0lMR
        isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum == 2 ;
        // isPass = e->tausTT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum == 2;
        break;
    case 8: //!new 1tau0lVR
        isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum >= 3 ;
        // isPass = e->tausTT_num.v() == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum >= 3;
        break;
    case 9: //!new 1tau0lCR
        isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum == 2 ;
        // isPass = e->tausTT_num.v() == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum == 2;
        break;
    case 10: // 1tau0lCRa
        isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum == 0;
        break;
    case 11://!!!1tau1lSRTest
        // isPass = e->tausM_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 5 && bjetsMNum >= 2;
        // isPass = e->tausM_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 6 && bjetsMNum >= 2;
        // isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 6 && bjetsMNum >= 3;
        isPass = e->tausM_num.v() == 1 && lepNum == 1 && e->jets_num.v() == 7 && bjetsMNum >= 3;
        // isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 5 && bjetsMNum >= 2;
        // isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 6 && bjetsMNum >= 2;
        // isPass = e->tausTT_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 5 && bjetsMNum >= 2;
        break;

    default:
        break;
    }
    return isPass;
}

Double_t baseWeightCal(event *e, UInt_t entry, const Bool_t isRun3, Bool_t isData, Int_t channel )
{
    Double_t basicWeight = 1.0;
    if(isData){
        return basicWeight;
    }
    if (!isRun3)
    {
        // Double_t basicWeight = EVENT_prefireWeight * EVENT_genWeight * PUweight_ * HLT_weight * tauT_IDSF_weight_new * elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR;
        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v() * e->btagShape_weight.v() * e->btagShapeR.v();
        Double_t btagWeight = 1.0;
        Double_t HLTWeight = 1.0;
        TString btagName = "";
        switch (channel)
        {
        case 0: // 1tau1lSR
            HLTWeight = e->HLT_weight.v();
            btagWeight = e->btagWPMedium_weight.v();
            btagName = e->btagWPMedium_weight.n();
            break;
        case 1: //1tau0l 
            HLTWeight = e->HLT_weight.v();
            btagWeight = e->btagShape_weight.v() * e->btagShapeR.v();
            btagName = e->btagShape_weight.n() + "*" + e->btagShapeR.n();
            break;
        case 2: //1tau2l
            HLTWeight = 1.0;//!for now
            btagWeight = e->btagWPMedium_weight.v();
            btagName = e->btagWPMedium_weight.n();
            break; 
        default:
            std::cout<<"channel wrong!\n";
            break;
        }

        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v()* e->btagWPMedium_weight.v();
        basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * HLTWeight * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v()* btagWeight;
        if(entry==10){
            std::cout<<"event weight: "<<e->EVENT_genWeight.n() <<"*"<< e->EVENT_prefireWeight.n() <<"*"<< e->PUweight_.n() <<"*"<< e->HLT_weight.n() <<"*"<< e->tauT_IDSF_weight_new.n() <<"*"<< e->elesTopMVAT_weight.n() <<"*"<< e->musTopMVAT_weight.n()<<"*"<< btagName<<"\n";
        }
    }
    else
    {
        basicWeight = e->EVENT_genWeight.v();
    }
    return basicWeight;
}