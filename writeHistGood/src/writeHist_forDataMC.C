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
    std::vector<TString> regionsForVariables = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCRc", "1tau0lCRb", "1tau0lCRa", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3", "baseline"};

    // jets_HT_class = histsForRegionsMap<Double_t>("jets_HT", "HT(GeV)", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_HT));

    // histsForRegionsMap<Double_t> jets_1pt_class{"jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt)};
    // std::make_shared<histsForRegionsMap<Double_t>> jets_1pt_class{"jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt)};
    // histsForRegionsMap<Double_t> jets_bScore_class{"jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 4.5, regionsForVariables, &(e->jets_bScore)};
    // histsForRegionsMap<Int_t> jets_num_class{"jets_number", "n^{jet}", m_processName, 7, 5.5, 12.5, regionsForVariables, &(e->jets_num)};

    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;
    std::shared_ptr<histsForRegionsMap<Double_t>> jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_bScore_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 4.5, regionsForVariables, &(e->jets_bScore));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_HT));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 10, 40, 140, regionsForVariables, &(e->jets_6pt));

    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 7, 5.5, 12.5, regionsForVariables, &(e->jets_num));
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsM_num));

    //I guess jets_1pt_class goes out range and destroyed after this function
    histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_bScore_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_6pt_class);
    histsForRegion_vec.push_back(bjetsM_num_class);


    // jets_HT_class.print();
    // jets_HT_class.setDir(m_outFile);
    histRegionsVectSetDir(histsForRegion_vec, m_outFile);

    std::cout << "Done initializing\n";
    std::cout << "\n";
}

void WH_forDataMC::LoopTree()
{
    std::cout << "Start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 10000;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        if (!(baselineSelection(e)))
        {
            continue;
        }

        // Double_t basicWeight = baseWeightCal(e, m_isRun3);
        // std::cout <<e->tausT_num.v() <<e->jets_num.v()  << e->bjetsM_num.v()<<"\n";
        Double_t basicWeight = 1.0;
        if (!m_isData){
            basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v();
        }

        // SR
        if (!m_isData)
        {
            Bool_t is1tau0lSR = SR1tau1lSel(e, 1, m_isRun3);
            Bool_t is1tau1lSR = SR1tau1lSel(e, 0, m_isRun3);
            histRegionVectFill(histsForRegion_vec, is1tau0lSR, "1tau0lSR", basicWeight, m_isData);
            histRegionVectFill(histsForRegion_vec, is1tau1lSR, "1tau1lSR", basicWeight, m_isData);
        }

        // 1tau0l CR
        Bool_t is1tau0lCR = SR1tau1lSel(e, 6, m_isRun3);
        Bool_t is1tau0lVR = SR1tau1lSel(e, 7, m_isRun3);
        Bool_t is1tau0lCRc = SR1tau1lSel(e, 8, m_isRun3);
        Bool_t is1tau0lCRb = SR1tau1lSel(e, 9, m_isRun3);
        Bool_t is1tau0lCRa = SR1tau1lSel(e, 10, m_isRun3);
        histRegionVectFill(histsForRegion_vec, is1tau0lCR, "1tau0lCR", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, is1tau0lVR, "1tau0lVR", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, is1tau0lCRc, "1tau0lCRc", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, is1tau0lCRa, "1tau0lCRa", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, is1tau0lCRb, "1tau0lCRb", basicWeight, m_isData);

        // 1tau1lCR
        Bool_t is1tau1lCR0 = SR1tau1lSel(e, 2, m_isRun3); // CR1 in slides
        Bool_t is1tau1lCR1 = SR1tau1lSel(e, 3, m_isRun3);
        Bool_t is1tau1lCR2 = SR1tau1lSel(e, 4, m_isRun3);
        Bool_t is1tau1lCR3 = SR1tau1lSel(e, 5, m_isRun3);
        histRegionVectFill(histsForRegion_vec, is1tau1lCR0, "1tau1lCR0", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, is1tau1lCR1, "1tau1lCR1", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, is1tau1lCR2, "1tau1lCR2", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, is1tau1lCR3, "1tau1lCR3", basicWeight, m_isData);
    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void WH_forDataMC::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    if (!m_isData)
    {
        Double_t genWeightSum = getGenSum(m_inputDir + m_processName + ".root");
        Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
        std::cout<<"m_processName="<<m_processName<<" lumi="<<TTTT::lumiMap.at(m_era)<<" crossSection="<<TTTT::crossSectionMap.at(m_processName)<<"\n";
        histRegionsVectScale(histsForRegion_vec, processScale);
    };
    for(auto & histRe: histsForRegion_vec){
        histRe->print();
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