/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2023-06-06 21:01:27
 * @modify date 2023-06-23 23:19:32
 * @desc [description]
 */
#include <iostream>

#include "../include/writeHist_forDataMC.h"
// #include "../SFfileMap.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/commenSelectionAndWeight.h"

void WH_forDataMC::Init()
{
    std::cout << "Start to initilation....................................................\n";

    // regions for hists
    std::vector<TString> regionsForVariables = {"1tau0lSR",  "1tau0lVR", "1tau0lCR", "1tau0lMR", "1tau1lCR1", "1tau1lCR2", "1tau1lSR", "baseline"};

    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;

    std::shared_ptr<histsForRegionsMap<Double_t>> jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_bScore_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 4.5, regionsForVariables, &(e->jets_bScore));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_HT));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 10, 40, 140, regionsForVariables, &(e->jets_6pt));
    // SP_d jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2pt", "p_{T}^{2nd jet}(GeV)", m_processName, 10, 40, 600, regionsForVariables, &(e->jets_2pt));
    SP_d jets_3pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3pt", "p_{T}^{3th jet}(GeV)", m_processName, 10, 40, 140, regionsForVariables, &(e->jets_3pt));
    SP_d jets_4pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4pt", "p_{T}^{4th jet}(GeV)", m_processName, 10, 40, 300, regionsForVariables, &(e->jets_4pt));
    SP_d jets_5pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5pt", "p_{T}^{5th jet}(GeV)", m_processName, 10, 40, 160, regionsForVariables, &(e->jets_5pt));
    SP_d jets_7pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_7pt", "p_{T}^{7th jet}(GeV)", m_processName, 10, 40, 145, regionsForVariables, &(e->jets_7pt));

    SP_d jets_rationHT_4toRest_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_rationHT_4toRest", "HT^{4 leaading jets}/HT^{rest of jets}", m_processName, 10, 0, 12, regionsForVariables, &(e->jets_rationHT_4toRest));
    // SP_d jets_leading2invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_leading2invariantMass", "m^{2 leading jets}", m_processName, 10, 100, 1000, regionsForVariables, &(e->jets_leading2invariantMass));
    SP_d jets_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_transMass", "m_{T}^{jets}", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_transMass));
    SP_d jets_avaregeDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_average_deltaR", "average(#Delta R)^{jets}", m_processName, 10, 1.2, 3.2, regionsForVariables, &(e->jets_average_deltaR));
    // SP_d jets_4largestBscoreMulti_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreMulti", "#sqrt{#prod_{i=4 highest} bscore_{i}^{jet}}", m_processName, 10, 0, 0.3, regionsForVariables, &(e->jets_4largestBscoreMulti));
    SP_d jets_1btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1btag", "btag^{1st jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_1btag));
    SP_d jets_2btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2btag", "btag^{2nd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_2btag));
    SP_d jets_3btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3btag", " btag^{3rd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_3btag));
    SP_d jets_4btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4btag", "btag^{4th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_4btag));
    SP_d jets_5btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5btag", "btag^{5th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_5btag));
    SP_d jets_6btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6btag", "6th jet btag",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_6btag));
    // SP_d = std::make_shared<histsForRegionsMap<Double_t>>("", 10));

    SP_d MET_pt_class = std::make_shared<histsForRegionsMap<Double_t>>("MET_pt", "MET", m_processName, 10, 0, 500, regionsForVariables, &(e->MET_pt));
    SP_d bjetsM_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_HT", "HT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_MHT", "MHT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_invariantMass", "m^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_invariantMass));
    SP_d bjetsM_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_1pt", "p_{T}^{1st bjet}", m_processName, 10, 25, 600, regionsForVariables, &(e->bjetsM_1pt));
    SP_d bjetsM_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2pt", "p_{T}^{2nd bjet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsM_2pt));
    SP_d bjetsM_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_minDeltaR", "min(#Delta R_{b jets})", m_processName, 6, 0, 5, regionsForVariables, &(e->bjetsM_minDeltaR));
    SP_d tausT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1pt", "p_{T}^{1st #tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausT_1pt));
    SP_d tausT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1eta", "#eta_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1eta));
    SP_d tausT_1phi_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1phi", "#phi_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1phi));
    SP_d tausT_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_HT", "HT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_HT));
    SP_d tausT_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_MHT", "MHT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_MHT));
    SP_d tausT_leptonsT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_leptonsT_invariantMass", "m_{#tau and lep}(GeV)", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_leptonsT_invariantMass));

    SP_d muonsTopMVAT_1t_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_1pt", "p_{T}^{#mu}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->muonsTopMVAT_1pt));
    SP_d elesTopMVAT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_1pt", "p_{T}^{e}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->elesTopMVAT_1pt));


    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 7, 5.5, 12.5, regionsForVariables, &(e->jets_num));
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsM_num));
    SP_i bjetsPTM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsPTM_num", "n^{b jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsPTM_num));
    SP_i tausT_leptonsTopMVA_chargeMulti_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_leptonsTopMVA_chargeMulti", "charge^{#tau}*charge^{lep}",m_processName, 3, -1.5, 1.5, regionsForVariables,  &(e->tausT_leptonsTopMVA_chargeMulti));
    SP_i PV_npvsGood_class = std::make_shared<histsForRegionsMap<Int_t>>("PV_npvsGood", "n^{PV}", m_processName, 10, 0, 60, regionsForVariables, &(e->PV_npvsGood));
    SP_i tausT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_num", "n^{#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausT_num));
    SP_i tausTT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_num", "n^{TT#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausTT_num));
    SP_i tausF_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_num", "n^{F#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausF_num));
    SP_i tausT_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_1genFlavour", "gen flavour^{T#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausT_1genFlavour));
    SP_i tausF_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1genFlavour", "gen flavour^{F#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausF_1genFlavour));
    SP_i tausTT_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_1genFlavour", "gen flavour^{TT#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausTT_1genFlavour));
    SP_i tausT_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_1decayMode", "gen flavour^{T#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausT_1decayMode));
    SP_i tausF_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1decayMode", "gen flavour^{F#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausF_1decayMode));
    SP_i tausTT_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_1decayMode", "gen flavour^{TT#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausTT_1decayMode));

    //I guess jets_1pt_class goes out range and destroyed after this function
    histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_bScore_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_6pt_class);
    // histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_2pt_class);
    histsForRegion_vec.push_back(jets_3pt_class);
    histsForRegion_vec.push_back(jets_4pt_class);
    histsForRegion_vec.push_back(jets_5pt_class);
    histsForRegion_vec.push_back(jets_7pt_class);
    histsForRegion_vec.push_back(jets_rationHT_4toRest_class);
    // histsForRegion_vec.push_back(jets_leading2invariantMass_class);
    histsForRegion_vec.push_back(jets_transMass_class);
    histsForRegion_vec.push_back(jets_avaregeDeltaR_class);
    // histsForRegion_vec.push_back(jets_4largestBscoreMulti_class);
    histsForRegion_vec.push_back(jets_1btag_class);
    histsForRegion_vec.push_back(jets_2btag_class);
    histsForRegion_vec.push_back(jets_3btag_class);
    histsForRegion_vec.push_back(jets_4btag_class);
    histsForRegion_vec.push_back(jets_5btag_class);
    histsForRegion_vec.push_back(jets_6btag_class);
    histsForRegion_vec.push_back(MET_pt_class);
    histsForRegion_vec.push_back(bjetsM_HT_class);
    histsForRegion_vec.push_back(bjetsM_MHT_class);
    histsForRegion_vec.push_back(bjetsM_invariantMass_class);
    histsForRegion_vec.push_back(bjetsM_1pt_class);
    histsForRegion_vec.push_back(bjetsM_2pt_class);
    histsForRegion_vec.push_back(bjetsM_minDeltaR_class);
    histsForRegion_vec.push_back(tausT_1pt_class);
    histsForRegion_vec.push_back(tausT_1eta_class);
    histsForRegion_vec.push_back(tausT_1phi_class);
    histsForRegion_vec.push_back(tausT_HT_class);
    histsForRegion_vec.push_back(tausT_MHT_class);
    histsForRegion_vec.push_back(tausT_leptonsT_invariantMass_class);
    histsForRegion_vec.push_back(muonsTopMVAT_1t_class);
    histsForRegion_vec.push_back(elesTopMVAT_1pt_class);
    // histsForRegion_vec.push_back();


    histsForRegion_vec.push_back(bjetsM_num_class);
    histsForRegion_vec.push_back(bjetsPTM_num_class);
    histsForRegion_vec.push_back(tausT_leptonsTopMVA_chargeMulti_class);
    histsForRegion_vec.push_back(PV_npvsGood_class);
    histsForRegion_vec.push_back(tausT_num_class);
    histsForRegion_vec.push_back(tausTT_num_class);
    histsForRegion_vec.push_back(tausF_num_class);
    histsForRegion_vec.push_back(tausT_1genFlavour_class);
    histsForRegion_vec.push_back(tausF_1genFlavour_class);
    histsForRegion_vec.push_back(tausTT_1genFlavour_class);
    histsForRegion_vec.push_back(tausT_1decayMode_class);
    histsForRegion_vec.push_back(tausF_1decayMode_class);
    histsForRegion_vec.push_back(tausTT_1decayMode_class);


    // jets_HT_class.print();
    // jets_HT_class.setDir(m_outFile);
    WH::histRegionsVectSetDir(histsForRegion_vec, m_outFile);

    std::cout << "Done initializing\n";
    std::cout << "\n";
}






void WH_forDataMC::LoopTree(UInt_t entry)
{
    Long64_t allEvent = m_tree->GetEntries();
    std::cout << "Start to loop tree of entries: "<<allEvent<<"\n";
    if (entry > 0)
    {
        allEvent = entry;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        const Bool_t ifBaseline = baselineSelection(e, m_isRun3);
        if (!ifBaseline)
        {
            continue;
        }

        //!!!Testing corrections
        // Double_t basicWeight = e->EVENT_genWeight.v();
        // Double_t basicWeight = e->EVENT_genWeight.v()* e->PUweight_.v();
        // Double_t basicWeight = e->EVENT_genWeight.v() * e->PUweight_.v() * e->tauT_IDSF_weight_new.v();
        Double_t basicWeight = e->EVENT_genWeight.v() * e->PUweight_.v() * e->tauT_IDSF_weight_new.v() * e->btagWPMedium_weight.v();
        // Double_t basicWeight = e->EVENT_genWeight.v()* e->PUweight_.v() * e->btagWPMedium_weight.v();
        // Double_t basicWeight = e->EVENT_genWeight.v()* e->PUweight_.v() * e->btagWPMedium_weight.v() * e->HLT_weight.v();
        // Double_t basicWeight = e->EVENT_genWeight.v() * e->eleMVAT_IDSF_weight.v(); //!!! run 3 
        // Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData);
        // std::cout << "HLT_weight=" << e->HLT_weight.v() << "\n";
        // std::cout << "basicWeight=" << basicWeight << "\n";
        // Double_t basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v()* e->btagWPMedium_weight.v(); //!!!without HLT weight
        // experimenting
        // Double_t basicWeight = 1.0;
        // if (!m_isData){
        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v();//HLT weight should be used together with b tag weight
        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v();
        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v();
        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v()* e->btagWPMedium_weight.v();
        // basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v();

        // try b tag R from previous measurement
        //  basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v() * e->btagShape_weight.v() * e->btagShapeR.v();
        // }

        // Bool_t ifbaseline = baselineSelection(e, m_isRun3);

        Int_t lepNum = e->elesMVAT_num.v() + e->muonsT_num.v() ;
        // Bool_t if1tau = e->tausT_num.v() == 1 ; 
        // Bool_t if1tau = e->tausT_num.v() == 1 && (e->bjetsPTM_num.v()>=2); 
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline&&lepNum &&(e->bjetsPTM_num.v()>=2), "baseline", basicWeight, m_isData);

        // SR
        if (!m_isData)
        {
            Bool_t is1tau0lSR = SR1tau1lSel(e, 1, m_isRun3);
            Bool_t is1tau1lSR = SR1tau1lSel(e, 0, m_isRun3);
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lSR, "1tau0lSR", basicWeight, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau1lSR, "1tau1lSR", basicWeight, m_isData);
        }

        // 1tau0l CR
        Bool_t is1tau0lVR = SR1tau1lSel(e, 7, m_isRun3);
        Bool_t is1tau0lCRc = SR1tau1lSel(e, 8, m_isRun3);
        Bool_t is1tau0lCRb = SR1tau1lSel(e, 9, m_isRun3);
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lVR, "1tau0lMR", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lCRc, "1tau0lVR", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lCRb, "1tau0lCR", basicWeight, m_isData);

        // 1tau1lCR
        Bool_t is1tau1lCR0 = SR1tau1lSel(e, 2, m_isRun3); // CR1 in slides
        Bool_t is1tau1lCR2 = SR1tau1lSel(e, 4, m_isRun3);
        WH::histRegionVectFill(histsForRegion_vec, is1tau1lCR0, "1tau1lCR1", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, is1tau1lCR2, "1tau1lCR2", basicWeight, m_isData);
    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void WH_forDataMC::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    if (!m_isData)
    {
        //???Problme of summing same process with extra extension!!!
        //for now merge input tree of same process before running this code
        Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
        TString processName = WH::getProcessName(m_processName, m_isRun3);
        std::cout<<"newProcessName="<<processName<<"\n";

        //
        if(std::find(WH::processWithExt.begin(), WH::processWithExt.end(), processName) != WH::processWithExt.end()){
            genWeightSum = TTTT::getGenSum(m_inputDir + processName + "1.root") + TTTT::getGenSum(m_inputDir+processName+".root");
        }
        std::cout << "genWeightSum=" << genWeightSum << "\n";

        Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at( processName)) / genWeightSum);
        std::cout<<"processScale="<<processScale<<"\n";
        std::cout<<"m_processName="<<m_processName<<" lumi="<<TTTT::lumiMap.at(m_era)<<" crossSection="<<TTTT::crossSectionMap.at(processName)<<"\n";
        WH::histRegionsVectScale(histsForRegion_vec, processScale);
    };
    for(UInt_t i=0; i<histsForRegion_vec.size(); i++){
        if(i>0){
            continue;
        }
        histsForRegion_vec.at(i)->print();
    }

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}

WH_forDataMC::~WH_forDataMC()
{
    // code to free any dynamically allocated resources
    m_file->Close();
    m_outFile->Close();
    // delete m_tree;
    // delete m_file;
    // delete m_outFile;
}