// 
#include "../include/commenSelectionAndWeight.h"

Bool_t baselineSelection(event *event, const Bool_t isRun3)
{
    // Bool_t pass = event->jets_num.v() >= 6 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 500. && event->jets_6pt.v() > 40.;
    Bool_t pass = kFALSE;
    if (!isRun3){
        pass = event->jets_num.v() >= 6 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 550. && event->jets_6pt.v() > 40.;
    }else{
        // std::cout << "not run 3\n";
        // pass = event->jets_num.v() >= 6 && event->bjetsPNM_num.v() >= 1 && event->jets_HT.v() > 500. && event->jets_6pt.v() > 40.;
        pass = event->jets_num.v() >= 6 && event->bjetsPTM_num.v() >= 1 && event->jets_HT.v() > 550. && event->jets_6pt.v() > 40.;
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
            // if (i == 0)
            // {
            //     std::cout << "HLT selection for 2018\n";
            // }
            ifHLT = e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() == 1 || e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2.v() == 1 || e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5.v() == 1 || e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59.v() == 1 || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94.v() == 1 || e->HLT_PFJet500.v() == 1;
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

Bool_t SR1tau1lSel(event *e, const Int_t channel, Bool_t isRun3 )
{
    Int_t lepNum= 1;
    Int_t bjetsMNum = 0;
    if (!isRun3)
    {
        lepNum = e->elesTopMVAT_num.v() + e->muonsTopMVAT_num.v();
        bjetsMNum = e->bjetsM_num.v();
    }
    else
    {
        lepNum = e->elesMVAT_num.v() + e->muonsT_num.v();
        // bjetsMNum = e->bjetsPNM_num.v();
        bjetsMNum = e->bjetsPTM_num.v();
    }
    Bool_t isPass = kFALSE;
    switch (channel)
    {
    case 0: // 1tau1lSR
        isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 7 && bjetsMNum >= 2;
        break;
    case 1: // 1tau0lSR
        isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum >= 2;
        break;
    case 2: // 1tau1lCR1
        // Bool_t is1tau1lCR0 = *tausT_num == 1 && lepNum == 1 && *jets_num >= 6 && *bjetsM_num == 1; // CR1 in slides
        isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 6 && bjetsMNum == 1;
        break;
    case 3: // 1tau1lCR1 old
        // Bool_t is1tau1lCR1 = *tausT_num == 1 && lepNum == 1 && *jets_num >= 7 && *bjetsM_num == 0;
        isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() >= 7 && bjetsMNum == 0;
        break;
    case 4: // 1tau1lCR2
        // Bool_t is1tau1lCR2 = *tausT_num == 1 && lepNum == 1 && *jets_num == 6 && *bjetsM_num >= 2;
        isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() == 6 && bjetsMNum >= 2;
        break;
    case 5: // 1tau1lCR3
        // Bool_t is1tau1lCR3 = *tausT_num == 1 && lepNum == 1 && *jets_num == 6 && *bjetsM_num == 1;
        isPass = e->tausT_num.v() == 1 && lepNum == 1 && e->jets_num.v() == 6 && bjetsMNum == 1;
        break;
    case 6: // 1tau0lCR
        // Bool_t is1tau0lCR = *tausT_num == 1 && lepNum == 0 && *jets_num >= 8 && *bjetsM_num == 0;
        isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum == 0;
        break;
    case 7: // 1tau0lVR
        // Bool_t is1tau0lVR = *tausT_num == 1 && lepNum == 0 && *jets_num >= 8 && *bjetsM_num == 1;
        isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum == 1;
        break;
    case 8: // 1tau0lCRc
        // Bool_t is1tau0lCRc = *tausT_num == 1 && lepNum == 0 && *jets_num < 8 && *bjetsM_num >= 2;
        isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum >= 2;
        break;
    case 9: // 1tau0lCRb
        // Bool_t is1tau0lCRb = *tausT_num == 1 && lepNum == 0 && *jets_num < 8 && *bjetsM_num == 1;
        isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum == 1;
        break;
    case 10: // 1tau0lCRa
        // Bool_t is1tau0lCRa = *tausT_num == 1 && lepNum == 0 && *jets_num < 8 && *bjetsM_num= 0;
        isPass = e->tausT_num.v() == 1 && lepNum == 0 && e->jets_num.v() < 8 && bjetsMNum == 0;
        break;

    default:
        break;
    }
    return isPass;
}

Double_t baseWeightCal(event *e, UInt_t entry, const Bool_t isRun3, Bool_t isData, Bool_t is1tau1l )
{
    Double_t basicWeight = 1.0;
    if(!isData){
        if (!isRun3)
        {
            // Double_t basicWeight = EVENT_prefireWeight * EVENT_genWeight * PUweight_ * HLT_weight * tauT_IDSF_weight_new * elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR;
            // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v() * e->btagShape_weight.v() * e->btagShapeR.v();
            Double_t btagWeight = 1.0;
            TString btagName = "";
            if (is1tau1l)
            {
                btagWeight = e->btagWPMedium_weight.v();
                btagName = e->btagWPMedium_weight.n();
            }   
            else
            {
                btagWeight = e->btagShape_weight.v() * e->btagShapeR.v();
                btagName = e->btagShape_weight.n() + "*" + e->btagShapeR.n();
            }
            // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v()* e->btagWPMedium_weight.v();
            basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v()* btagWeight;
            if(entry==0){
                // std::cout<<"event weight: "<<e->EVENT_genWeight.n() <<"*"<< e->EVENT_prefireWeight.n() <<"*"<< e->PUweight_.n() <<"*"<< e->HLT_weight.n() <<"*"<< e->tauT_IDSF_weight_new.n() <<"*"<< e->elesTopMVAT_weight.n() <<"*"<< e->musTopMVAT_weight.n()<<"*"<< e->btagWPMedium_weight.n()<<"\n";
                std::cout<<"event weight: "<<e->EVENT_genWeight.n() <<"*"<< e->EVENT_prefireWeight.n() <<"*"<< e->PUweight_.n() <<"*"<< e->HLT_weight.n() <<"*"<< e->tauT_IDSF_weight_new.n() <<"*"<< e->elesTopMVAT_weight.n() <<"*"<< e->musTopMVAT_weight.n()<<"*"<< btagName<<"\n";
            }
        }
        else
        {
            basicWeight = e->EVENT_genWeight.v();
        }
    }
    return basicWeight;
}