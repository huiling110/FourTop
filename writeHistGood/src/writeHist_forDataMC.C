/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2023-06-06 21:01:27
 * @modify date 2023-06-23 23:19:32
 * @desc [description]
 */
#include <iostream>

#include "../include/writeHist_forDataMC.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/commenSelectionAndWeight.h"
// #include "../include/histsForRegionsMap_value.h"

void WH_forDataMC::Init()
{
    std::cout << "Start to initilation....................................................\n";

    // regions for hists
    std::vector<TString> regionsForVariables = {"1tau0lSR",  "1tau0lVR", "1tau0lCR", "1tau0lMR",  "1tau0lCRMR","1tau1lCR1", "1tau1lCR2", "1tau1lSR", "baseline", "1tau1lCR3", "1tau1lCR12", "1tau2lSR", "1tau2lCR3"};

    //regions for FR uncertainty for 1tau0l
    if(m_isFakeTau){
        // region + "_CMS_tau_FR_" + era + "Up"
        regionsForVariables.push_back("1tau0lCRMR_CMS_tau_FR_" + m_era + "Up");
        regionsForVariables.push_back("1tau0lCRMR_CMS_tau_FR_" + m_era + "Down");
        regionsForVariables.push_back("1tau0lVR_CMS_tau_FR_" + m_era + "Up");
        regionsForVariables.push_back("1tau0lVR_CMS_tau_FR_" + m_era + "Down");
    }

    WH::initializeHistVec(regionsForVariables, histsForRegion_vec, m_processName, e);

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

        const Bool_t ifBaseline = baselineSelection(e, m_isRun3, m_is1tau2l); 
        if (!ifBaseline)
        {
            continue;
        }

        // const Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData, 0, m_isFakeTau, m_isFakeLepton);//!1tau1l
        const Double_t eventWeight_1tau2l = baseWeightCal(e, i, m_isRun3, m_isData, 2, m_isFakeTau, m_isFakeLepton);
        const Double_t eventWeight_1tau0l = baseWeightCal(e, i, m_isRun3, m_isData, 1, m_isFakeTau, m_isFakeLepton);//!1tau0l
        //!!!Some FR_weight_final == inf for fakeTau_MC, temporary fix here
        if (std::isnan(eventWeight_1tau0l)|| std::isinf(eventWeight_1tau0l)){
            std::cout<<"!!!! FR_weight_final is NAN\n";
            continue;
        }

        if(std::isinf(e->btagWPMT_weight.v()) || std::isnan(e->btagWPMT_weight.v())){
            std::cout<<"btagWPMT_weight="<<e->btagWPMT_weight.v()<<"\n";
        }//!!!todo: handle this in MV

        Double_t basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight_new.v() * e->musTopMVAT_weight_new.v()* e->btagWPMT_weight.v(); //!!!without HLT weight

        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, "baseline", basicWeight, m_isData);

        // SR
        if (!m_isData)
        {
            // Bool_t is1tau0lSR = SR1tau1lSel(e, 1, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kTRUE);
            Bool_t is1tau0lSR = SR1tau1lSel(e, 1, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t is1tau1lSR = SR1tau1lSel(e, 0, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE); //!m_isData = isMC
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lSR, "1tau0lSR", eventWeight_1tau0l, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau1lSR, "1tau1lSR", basicWeight, m_isData);

            Bool_t is1tau2lSRTest = SR1tau1lSel(e, 2, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau2lSRTest, "1tau2lSR", eventWeight_1tau2l, m_isData);
        }

        // 1tau0l CR
        Bool_t is1tau0lMR = SR1tau1lSel(e, 7, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
        Bool_t is1tau0lVR = SR1tau1lSel(e, 8, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
        Bool_t is1tau0lCR = SR1tau1lSel(e, 9, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lMR, "1tau0lMR", eventWeight_1tau0l, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lVR, "1tau0lVR", eventWeight_1tau0l, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR, "1tau0lCR", eventWeight_1tau0l, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR||is1tau0lMR, "1tau0lCRMR", eventWeight_1tau0l, m_isData);
        if(m_isFakeTau){
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR||is1tau0lMR, "1tau0lCRMR_CMS_tau_FR_" + m_era + "Down", e->FR_weight_final_down, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR||is1tau0lMR, "1tau0lCRMR_CMS_tau_FR_" + m_era + "Up", e->FR_weight_final_up, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lVR, "1tau0lVR_CMS_tau_FR_" + m_era + "Down", e->FR_weight_final_down, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lVR, "1tau0lVR_CMS_tau_FR_" + m_era + "Up", e->FR_weight_final_up, m_isData);
        }

        // 1tau1lCR
        Bool_t is1tau1lCR1 = SR1tau1lSel(e, 5, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData); 
        Bool_t is1tau1lCR2 = SR1tau1lSel(e, 4, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData); 
        WH::histRegionVectFill(histsForRegion_vec, is1tau1lCR1, "1tau1lCR1", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, is1tau1lCR2, "1tau1lCR2", basicWeight, m_isData);
        //1tau1lCR1+CR2
        // Bool_t is1tau0lSRTest = SR1tau1lSel(e, 3, m_isRun3, m_isFakeTau); //!might be buggy here
        Bool_t is1tau0lSRTest = SR1tau1lSel(e, 3, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE); 
        WH::histRegionVectFill(histsForRegion_vec, is1tau0lSRTest, "1tau1lCR12", basicWeight, m_isData);
        Bool_t is1tau1lSRL = SR1tau1lSel(e, 11, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE);
        WH::histRegionVectFill(histsForRegion_vec, is1tau1lSRL, "1tau1lCR3", basicWeight, m_isData);

        //1tau2l CR3
        Bool_t is1tau2lCR3 = SR1tau1lSel(e, 12, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE);
        WH::histRegionVectFill(histsForRegion_vec, is1tau2lCR3, "1tau2lCR3", eventWeight_1tau2l, m_isData);

    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void WH_forDataMC::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    if(!m_isData && !m_isFakeTau && !m_isFakeLepton){
            Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
            TString processName = WH::getProcessName(m_processName, m_isRun3);
            std::cout<<"newProcessName="<<processName<<"\n";

            if(std::find(WH::processWithExt.begin(), WH::processWithExt.end(), processName) != WH::processWithExt.end()){
                genWeightSum = TTTT::getGenSum(m_inputDir + processName + "1.root") + TTTT::getGenSum(m_inputDir+processName+".root");
            }
            std::cout << "genWeightSum=" << genWeightSum << "\n";

            Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at( processName)) / genWeightSum);
            std::cout<<"processScale="<<processScale<<"\n";
            std::cout<<"m_processName="<<m_processName<<" lumi="<<TTTT::lumiMap.at(m_era)<<" crossSection="<<TTTT::crossSectionMap.at(processName)<<"\n";
            WH::histRegionsVectScale(histsForRegion_vec, processScale);
        // }
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
}