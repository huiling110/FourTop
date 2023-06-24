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

    jets_HT_class = histsForRegionsMap("jets_HT", "HT(GeV)", m_processName,  10, 500, 1800, regionsForVariables, &(e->jets_HT));

    // jets_HT_class.print();
    jets_HT_class.setDir(m_outFile);

    std::cout << "Done initializing\n";
    std::cout << "\n";
}

void WH_forDataMC::LoopTree()
{
    std::cout << "Start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 100000;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        if (!(baselineSelection(e)))
        {
            continue;
        }

        Double_t basicWeight = baseWeightCal(e);

        //SR
        if(!m_isData){
            Bool_t is1tau0lSR = SR1tau1lSel(e, 1) ;
            Bool_t is1tau1lSR = SR1tau1lSel(e, 0);
            jets_HT_class.fillHistVec("1tau0lSR", basicWeight, is1tau0lSR, m_isData);
            jets_HT_class.fillHistVec("1tau1lSR", basicWeight, is1tau1lSR, m_isData);
        }

        // 1tau0l CR
        Bool_t is1tau0lCR = SR1tau1lSel(e, 6);
        Bool_t is1tau0lVR = SR1tau1lSel(e, 7);
        Bool_t is1tau0lCRc = SR1tau1lSel(e, 8);
        Bool_t is1tau0lCRb = SR1tau1lSel(e, 9);
        Bool_t is1tau0lCRa = SR1tau1lSel(e, 10);
        jets_HT_class.fillHistVec("1tau0lCR", basicWeight, is1tau0lCR, m_isData);
        jets_HT_class.fillHistVec("1tau0lVR", basicWeight, is1tau0lVR, m_isData);
        jets_HT_class.fillHistVec("1tau0lCRc", basicWeight, is1tau0lCRc, m_isData);
        jets_HT_class.fillHistVec("1tau0lCRb", basicWeight, is1tau0lCRb, m_isData);
        jets_HT_class.fillHistVec("1tau0lCRa", basicWeight, is1tau0lCRa, m_isData);

    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void WH_forDataMC::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    Double_t genWeightSum = getGenSum(m_inputDir + m_processName + ".root");
    Double_t processScale = ((TTTT::lumiMap.at(m_era)* TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
    if (!m_isData)
    {
        jets_HT_class.scale(processScale);
    };
    jets_HT_class.print();

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