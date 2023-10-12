#include "../include/writeHist_HLTeff.h"
#include "../include/inputFileMap.h"
#include "../include/commenSelectionAndWeight.h"
#include "../../myLibrary/commenFunction.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"

WH_HLTeff::WH_HLTeff(const TString inputDir, const TString process, TString outVersion, Bool_t isTest) : m_inputDir{inputDir}, m_processName{process}, m_isTest{isTest}
{
    m_file = new TFile(m_inputDir + m_processName + ".root", "READ");
    if (!m_file || m_file->IsZombie())
    {
        std::cout << "Error: could not open file!" << m_file->GetName() << std::endl;
    }
    else
    {
        std::cout << "input file: " << m_file->GetName() << "\n";
        m_tree = (TTree *)m_file->Get("newtree");
    }

    m_era = TTTT::getEra(m_inputDir);
    m_isData = TTTT::getIsData(m_inputDir);
    m_isRun3 = TTTT::isRun3(m_era);
    std::cout << "m_era=" << m_era << " m_isData=" << m_isData << "  m_isTest=" << m_isTest << "  m_isRun3=" << m_isRun3 << "\n";

    std::cout << "m_processName: " << m_processName << "\n";
    m_outFile = new TFile(m_inputDir + "variableHists" + "_" + outVersion + "/" + m_processName + ".root", "RECREATE");

    e = new event(m_tree);
}

void WH_HLTeff::Init()
{
    std::cout << "Start to initilation....................................................\n";

    std::vector<TString>
        regionsForVariables = {
            "baseline1Muon",
            "baseline1MuonAndHLT",
            "baseline",       // for MC true efficiency
            "baselineAndHLT", // for MC true efficiency
        };


    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;
    SP_d jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 40, 25, 625, regionsForVariables, &(e->jets_1pt));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 8, 25, 145, regionsForVariables, &(e->jets_6pt));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 40, 500, 2500, regionsForVariables, &(e->jets_HT));
    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 13, -0.5, 12.5, regionsForVariables, &(e->jets_num));
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables,  &(e->bjetsM_num));

    histsForRegion_vec.clear();
    histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_6pt_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(bjetsM_num_class);

    // 2D for SF
    Double_t xbins[] = {500, 550, 600, 750, 800, 900, 1000, 1200, 1400, 1800, 2500}; // HT
    Double_t ybins[] = {40, 55, 70, 85, 115, 145};                                   // 6th jet pt
    // Double_t xbins[] = {500, 600, 700, 800, 900, 1000, 1200, 1600, 2500}; // HT
    // Double_t ybins[] = {40, 55, 80, 145};                                 // 6th jet pt
    b1HT6pt_de = new TH2D("baseline1Muon1b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b1HT6pt_nu = new TH2D("baseline1MuonAndHLT1b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b2HT6pt_de = new TH2D("baseline1Muon2b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b2HT6pt_nu = new TH2D("baseline1MuonAndHLT2b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b3HT6pt_de = new TH2D("baseline1Muon3b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b3HT6pt_nu = new TH2D("baseline1MuonAndHLT3b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
}

void WH_HLTeff::LoopTree(UInt_t entry)
{
    Long64_t allEvent = m_tree->GetEntries();
    if (entry > 0)
    {
        allEvent = entry;
    }
    std::cout << "looping over trees of " << allEvent << "\n";
    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        const Bool_t baseline = baselineSelection(e);
        // if (!(baselineSelection(e)))
        if (!(baseline))
        {
            continue;
        }

        Bool_t is1muon = kTRUE;
        Bool_t ifHLT = kTRUE;
        if (m_era.CompareTo("2016") == 0)
        {
            if (i == 0)
            {
                std::cout << "HLT selection for 2016\n";
            }
            is1muon = e->HLT_IsoMu24.v() == 1 && e->muonsTopMVAT_num.v() == 1 && e->muonsTopMVAT_1pt.v() >= 30.;                                   // 2016
            ifHLT = e->HLT_PFHT450_SixJet40_BTagCSV_p056.v() == 1 || e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056.v() == 1 || e->HLT_PFJet450.v() == 1; // 2016
        }
        else if (m_era.CompareTo("2018") == 0)
        {
            if (i == 0)
            {
                std::cout << "HLT selection for 2018\n";
            }
            is1muon = e->HLT_IsoMu27.v() == 1 && e->muonsTopMVAT_num.v() == 1 && e->muonsTopMVAT_1pt.v() >= 30.;
            // ifHLT = e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() == 1 || e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2.v() == 1 || e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5.v() == 1 || e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59.v() == 1 || e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94.v() == 1 || e->HLT_PFJet500.v() == 1;
        }
        else if (m_era.CompareTo("2017") == 0)
        {
            if (i == 0)
            {
                std::cout << "HLT selection for 2017\n";
            }
            is1muon = e->HLT_IsoMu27.v() == 1 && e->muonsTopMVAT_num.v() == 1 && e->muonsTopMVAT_1pt.v() >= 30.;
            ifHLT = e->HLT_PFHT430_SixJet40_BTagCSV_p080.v() == 1 || e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075.v() == 1 || e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.v() == 1 || e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2.v() == 1 || e->HLT_PFJet500.v() == 1;
        }

        Double_t basicWeight = 1.0;
        if (!m_isData)
        {
            basicWeight = (e->EVENT_prefireWeight.v()) * (e->EVENT_genWeight.v()) * (e->PUweight_.v()) * (e->musTopMVAT_weight.v()) * (e->btagWPMedium_weight.v());
        }

        histRegionVectFill(histsForRegion_vec, baseline && is1muon, "baseline1Muon", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, baseline && is1muon && ifHLT, "baseline1MuonAndHLT", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, baseline , "baseline", basicWeight, m_isData);
        histRegionVectFill(histsForRegion_vec, baseline && ifHLT, "baselineAndHLT", basicWeight, m_isData);
    }

    std::cout << "end of event loop\n\n";
};

void WH_HLTeff::Terminate(){
    std::cout << "Termintate: ..........................................\n";
    if (!m_isData)
    {
        Double_t genWeightSum = getGenSum(m_inputDir + m_processName + ".root");
        Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
        std::cout << "m_processName=" << m_processName << " lumi=" << TTTT::lumiMap.at(m_era) << " crossSection=" << TTTT::crossSectionMap.at(m_processName) << "\n";
        histRegionsVectScale(histsForRegion_vec, processScale);
    };
    for (UInt_t i = 0; i < histsForRegion_vec.size(); i++)
    {
        if (i > 0)
        {
            continue;
        }
        histsForRegion_vec.at(i)->print();
    }

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";

};


WH_HLTeff::~WH_HLTeff()
{
    m_file->Close();
    m_outFile->Close();
}