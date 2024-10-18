#include "../include/commenSelectionAndWeight.h"

Bool_t baselineSelection(event *event, const Bool_t isRun3, Bool_t is1tau2l)
{
    // Bool_t pass = event->jets_num.v() >= 6 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 500. && event->jets_6pt.v() > 40.;
    Bool_t pass = kFALSE;
    if (!isRun3){
        if(!is1tau2l){
            if(event->bjetsM_num.v()<4){
                pass = event->jets_num.v() >= 6 && event->bjetsM_num.v() >= 2 && event->jets_HT.v() > 500. && event->jets_6pt.v()>40.;//
            }else{
                pass = event->jets_num.v() >= 6 && event->bjetsM_num.v() >= 2 && event->jets_HT.v() > 480. && event->jets_6pt.v()>38.;//
            }
        }else{
            pass = event->jets_num.v() >= 2 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 200. && event->lepTopMVAT_1pt.v()>25. && event->lepTopMVAT_2pt.v()>13.  && !event->lepTopMVAT_2ifZVeto.v();//leptonPt selection should be weighed lepton cone corrected pt for fakeLepton; done in createFakeLepton.py
            // pass = event->jets_num.v() >= 2 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 200. &&  (event->elesTopMVAT_num.v() + event->muonsTopMVAT_num.v())>0 && !event->lepTopMVAT_2ifZVeto.v()  ;//!testing
        }
    }else{
        // std::cout << "not run 3\n";
        pass = event->jets_num.v() >= 5 && event->bjetsPTM_num.v() >= 2 && event->jets_HT.v() > 400. && event->tausM_num.v();//!testing
    }
    return pass;
}


Bool_t HLTSel(event *e, const TString m_era){
        // Bool_t is1muon = kTRUE;
        Bool_t ifHLT = kTRUE;
        if (m_era.Contains("2016") )
        {
            // ifHLT = e->HLT_PFHT450_SixJet40_BTagCSV_p056.v() == 1 || e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056.v() == 1 || e->HLT_PFJet450.v() == 1; // 2016
            ifHLT = e->HLT_PFHT450_SixJet40_BTagCSV_p056.v() || e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056.v() || e->HLT_PFJet450.v(); // 2016
        }
        else if (m_era.CompareTo("2018") == 0)
        {
            ifHLT = e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() || e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2.v() || e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5.v() || e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59.v() || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94.v()|| e->HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5.v() ;
            // ifHLT = e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() || e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2.v()  || e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5.v() || e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59.v() || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94.v() ;
        }
        else if (m_era.CompareTo("2017") == 0)
        {
            // ifHLT = e->HLT_PFHT430_SixJet40_BTagCSV_p080.v() == 1 || e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075.v() == 1 || e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() == 1 || e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2.v() == 1 || e->HLT_PFJet500.v() == 1;
            ifHLT = e->HLT_PFHT430_SixJet40_BTagCSV_p080.v() || e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075.v()  || e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() || e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2.v()  || e->HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0.v() || e->HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07.v() || e->HLT_PFHT1050.v();
            // std::cout<<"HLT_PFHT1050="<<e->HLT_PFHT1050.v()<<"\n";
        }else if(m_era.Contains("2022")){
            ifHLT = e->HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59.v() || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94.v()|| e->HLT_PFJet500.v();
        }else{
            std::cout<<"!!! no HLT selection\n";
        }

    return ifHLT;
}

Bool_t SR1tau1lSel(event *e, const Int_t channel, Bool_t isRun3, Bool_t isFakeTau, Bool_t isFakeLepton, Bool_t isMC )
{
    Int_t lepNum = isRun3? e->elesMVAT_num.v() + e->muonsT_num.v() : e->elesTopMVAT_num.v() + e->muonsTopMVAT_num.v();
    Int_t bjetsMNum = isRun3? e->bjetsPTM_num.v() : e->bjetsM_num.v();
    Int_t tausTNum = isFakeTau ? e->tausF_num.v() : e->tausT_num.v();

    //
    const Bool_t tauCut = isFakeTau? e->tausF_num.v()==1 && !e->tausF_1isTight.v() : e->tausF_num.v()==1 && e->tausF_1isTight.v(); //!for 1tau0l, fake tau bg estimation 

    // const Int_t lepF_num = e->elesTopMVAF_num.v() + e->muonsTopMVAF_num.v();
    const Int_t lepF_num = e->lepTopMVAF_num.v();//lepTopMVAF_num
    Bool_t isTightPrompt_1L = e->elesTopMVAF_1isTightPrompt.v() || e->muonsTopMVAF_1isTightPrompt.v();
    Bool_t isTightPrompt_2L = (e->elesTopMVAF_1isTightPrompt.v() && e->elesTopMVAF_2isTightPrompt.v()) || (e->muonsTopMVAF_1isTightPrompt.v() && e->muonsTopMVAF_2isTightPrompt.v()) || (e->elesTopMVAF_1isTightPrompt.v() && e->muonsTopMVAF_1isTightPrompt.v()) || (e->elesTopMVAF_2isTightPrompt.v() && e->muonsTopMVAF_2isTightPrompt.v());
    Bool_t isTight_1L = e->elesTopMVAF_1isTight.v() || e->muonsTopMVAF_1isTight.v();
    Bool_t isTight_2L = (e->elesTopMVAF_1isTight.v() && e->elesTopMVAF_2isTight.v()) || (e->muonsTopMVAF_1isTight.v() && e->muonsTopMVAF_2isTight.v()) || (e->elesTopMVAF_1isTight.v() && e->muonsTopMVAF_1isTight.v()) || (e->elesTopMVAF_2isTight.v() && e->muonsTopMVAF_2isTight.v());

    Bool_t lepCut = kFALSE;
    Bool_t lepCut2L = kFALSE;
    Bool_t eleCut = kFALSE;//testing, l electron region
    Bool_t muonCut = kFALSE;
    if(isMC){
        if(isFakeLepton){
            lepCut = e->lepTopMVAF_isAR.v() && lepF_num == 1; 
            lepCut2L = e->lepTopMVAF_isAR.v() && lepF_num == 2;
            eleCut = !e->elesTopMVAF_1isTight.v() && e->elesTopMVAF_num.v() == 1;
            muonCut = !e->muonsTopMVAF_1isTight.v() && e->muonsTopMVAF_num.v() == 1;
        }else{
            lepCut = (lepF_num == 1) && isTightPrompt_1L;
            lepCut2L = (lepF_num == 2) && isTightPrompt_2L;
            eleCut = e->elesTopMVAF_num.v() == 1 && e->elesTopMVAF_1isTightPrompt.v();
            muonCut = e->muonsTopMVAF_num.v() == 1 && e->muonsTopMVAF_1isTightPrompt.v();
        }
    }else{//data
        lepCut = (lepF_num == 1) && isTight_1L;
        lepCut2L = (lepF_num == 2) && isTight_2L;
        eleCut = e->elesTopMVAF_num.v() == 1 && e->elesTopMVAF_1isTight.v();
        muonCut = e->muonsTopMVAF_num.v() == 1 && e->muonsTopMVAF_1isTight.v();
    } 

    Bool_t isPass = kFALSE;
    switch (channel)
    {
    case 0: // 1tau1lSR
        // isPass = tausTNum == 1 && lepNum == 1 && e->jets_num.v() >= 7 && bjetsMNum >= 3 ;
        // isPass = tausTNum == 1 && (eleCut||muonCut) && e->jets_num.v() >= 7 && bjetsMNum >= 3 ;
        isPass = tausTNum == 1 && lepCut && e->jets_num.v() >= 7 && bjetsMNum >= 3 ;
        break;
    case 1: // 1tau0lSR
        // isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum >= 3 &&e->tausF_num.v()==1;
        isPass = tauCut && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum >= 3 &&e->tausF_num.v()==1;
        break;
    case 2: // !1tau2lSR
        // isPass = tausTNum == 1 && lepNum == 2 && e->jets_num.v() >= 4 && bjetsMNum >= 2;//SR, MC: (FTPromp, FTPrompt)
        isPass = tausTNum == 1 && lepCut2L && e->jets_num.v() >= 4 && bjetsMNum >= 2;//SR, MC: (FTPromp, FTPrompt)
        break;
    case 3: // 1tau1lCR12
        // isPass = tausTNum == 1 && lepNum == 1 &&( (e->jets_num.v() >= 6 && bjetsMNum == 2) || (e->jets_num.v() == 6 && bjetsMNum >= 3));
        isPass = tausTNum == 1 && lepCut &&( (e->jets_num.v() >= 6 && bjetsMNum == 2) || (e->jets_num.v() == 6 && bjetsMNum >= 3));
        break;
    case 4: // 1tau1lCR2
        // isPass = tausTNum == 1 && lepNum == 1 && e->jets_num.v() == 6 && bjetsMNum >= 3;
        isPass = tausTNum == 1 && lepCut && e->jets_num.v() == 6 && bjetsMNum >= 3;
        break;
    case 5: // 1tau1lCR1
        isPass = tausTNum == 1 && lepCut && e->jets_num.v() >=6 && bjetsMNum ==2 ;
        break;
    case 6: // 1tau0lCR
        isPass = tauCut && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum == 0 ;
        break;
    case 7: // 1tau0lMR
        isPass = tauCut && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum == 2 &&e->tausF_num.v()==1 ;
        break;
    case 8: //1tau0lVR
        isPass = tauCut && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum >= 3 &&e->tausF_num.v()==1 ;
        break;
    case 9: // 1tau0lCR
        isPass = tauCut && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum == 2 &&e->tausF_num.v()==1 ;
        break;
    case 10: // 1tau0lCRa
        isPass = tausTNum == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum == 0;
        break;
    case 11://1tau1lCR3
        isPass = e->tausM_num.v() == 1 && lepNum == 1 && e->jets_num.v() == 7 && bjetsMNum >= 3;
        break;
    case 12: //1tau2lCR3 
        isPass = tausTNum == 1 && lepCut2L && e->jets_num.v() < 4 && bjetsMNum < 2 ;
        break;
    case 13: //1tau2lCR3+ele
        isPass = tausTNum == 1 && eleCut && e->jets_num.v() < 4 && bjetsMNum < 2 ;
        break;
    case 14://1tau2lCR3+muon    
        isPass = tausTNum == 1 && muonCut && e->jets_num.v() < 4 && bjetsMNum < 2 ;
        break;

    default:
        std::cout << "channel wrong!\n";
        break;
    }
    return isPass;
}

Double_t baseWeightCal(event *e, UInt_t entry, const Bool_t isRun3, Bool_t isData, Int_t channel, const Bool_t isFakeTau, const Bool_t isFakeLepton)
{//todo: would be very nice to be able to print the weight calculation
    Double_t basicWeight = 1.0;
    if(isData || isRun3){
        return basicWeight;
    }
    if(isFakeTau){
        return e->FR_weight_final;  
    }
    if(isFakeLepton){
        return e->lepTopMVAF_FRweight.v();
    }
        // Double_t basicWeight = EVENT_prefireWeight * EVENT_genWeight * PUweight_ * HLT_weight * tauT_IDSF_weight_new * elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR;
        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v() * e->btagShape_weight.v() * e->btagShapeR.v();
        Double_t btagWeight = 1.0;
        Double_t HLTWeight = 1.0;
        TString btagName = "";
        switch (channel)
        {
        case 0: // 1tau1lSR
            HLTWeight = e->HLT_weight.v();
            btagWeight = e->btagWPMT_weight.v();
            btagName = e->btagWPMT_weight.n();
            break;
        case 1: //1tau0l 
            HLTWeight = e->HLT_weight.v();
            btagWeight = e->btagShape_weight.v() * e->btagShapeR.v();
            btagName = e->btagShape_weight.n() + "*" + e->btagShapeR.n();
            break;
        case 2: //1tau2l
            HLTWeight = 1.0;//!for now
            btagWeight = e->btagWPMT_weight.v();
            btagName = e->btagWPMT_weight.n();
            break; 
        default:
            std::cout<<"channel wrong!\n";
            break;
        }

        basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * HLTWeight * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v()* btagWeight;
        if(entry==100){
            std::cout<<"event weight: "<<e->EVENT_genWeight.n() <<"*"<< e->EVENT_prefireWeight.n() <<"*"<< e->PUweight_.n() <<"*"<< e->HLT_weight.n() <<"*"<< e->tauT_IDSF_weight_new.n() <<"*"<< e->elesTopMVAT_weight.n() <<"*"<< e->musTopMVAT_weight.n()<<"*"<< btagName<<"\n";
        }
    return basicWeight;
}