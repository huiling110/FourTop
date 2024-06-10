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

    m_era = TTTT::getEra2(m_inputDir);
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
            //1b
            "baseline1Muon1b",
            "baseline1MuonAndHLT1b",
            "baseline1b",       // for MC true efficiency
            "baselineAndHLT1b", // for MC true efficiency
            "baseline1Muon2b",
            "baseline1MuonAndHLT2b",
            "baseline2b",       // for MC true efficiency
            "baselineAndHLT2b", // for MC true efficiency
            "baseline1Muon3b",
            "baseline1MuonAndHLT3b",
            "baseline3b",       // for MC true efficiency
            "baselineAndHLT3b", // for MC true efficiency
        };


    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;
    SP_d jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 40, 25, 625, regionsForVariables, &(e->jets_1pt));
    // SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 22, 25, 150, regionsForVariables, &(e->jets_6pt));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 150, 25, 175, regionsForVariables, &(e->jets_6pt));
    // SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 100, 400, 2800, regionsForVariables, &(e->jets_HT));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 240, 400, 2800, regionsForVariables, &(e->jets_HT));
    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 8, 4.5, 12.5, regionsForVariables, &(e->jets_num));
    // if(!m_isRun3){
    //     SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b-jet}", m_processName, 7, 0.5, 7.5, regionsForVariables,  &(e->bjetsM_num));
    // }else{
    // }
    auto adressBjets = m_isRun3? &(e->bjetsPTM_num): &(e->bjetsM_num);
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b-jet}", m_processName, 7, 0.5, 7.5, regionsForVariables,  adressBjets);

    histsForRegion_vec.clear();
    histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_6pt_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(bjetsM_num_class);

    // 2D for SF
    // Double_t xbins[] = {500, 550, 600, 750, 800, 900, 1000, 1200, 1400, 1800, 2500}; // HT
    // Double_t ybins[] = {40, 55, 70, 85, 115, 145};                                   // 6th jet pt
    // Double_t xbins[] = {500, 550, 650, 800, 950, 1200,  2500}; // HT
    // Double_t xbins[] = {500, 600, 700, 950, 1200,  2500}; // HT
    // Double_t ybins[] = {40, 55, 75, 100, 150};                                   // 6th jet pt
    // Double_t ybins[] = {40, 60, 90, 150};                                   // 6th jet pt
    //BinA
    // Double_t ybins[] = {40, 45., 80,  150};                                   // 6th jet pt
    // Double_t xbins[] = {500, 600, 800, 1200,  2500}; // HT
    //BinB
    // Double_t ybins[] = {40, 45., 60, 80,  150};                                   // 6th jet pt
    // Double_t xbins[] = {500, 600, 800, 1200,  2500}; // HT
    //BinC
    // Double_t ybins[] = {40, 45., 55, 80,  150};                                   // 6th jet pt
    // Double_t xbins[] = {500, 600, 800, 1200,  2500}; // HT
    //BinD
    // Double_t ybins[] = {40, 45., 55,  150};                                   // 6th jet pt
    // Double_t xbins[] = {500, 600, 800, 1200,  2500}; // HT
    //BinE
    // Double_t ybins[] = {40, 45., 50.,  150};                                   // 6th jet pt
    // Double_t xbins[] = {500, 600, 800, 1200,  2500}; // HT
    //BinF
    // Double_t ybins[] = {40, 45., 50.,  150};                                   // 6th jet pt
    // Double_t xbins[] = {500, 700, 1200,  2500}; // HT
 
    //BinG
    // Double_t ybins[] = {25., 30, 35., 40, 45., 50.,  150};                                   // 6th jet pt
    // Double_t xbins[] = {350, 500, 700, 1200,  2500}; // HT
    // Double_t ybins[] = {30, 35., 40, 45., 50.,  150};                                   // 6th jet pt
    // Double_t xbins[] = {400, 500, 700, 1200,  2500}; // HT
    // Double_t ybins[] = {32, 36., 40, 45., 50.,  150};                                   // 6th jet pt
    // Double_t xbins[] = {450, 500, 700, 1200,  2500}; // HT
    // Double_t ybins[] = {34, 36., 38, 40, 45., 50.,  150};                                   // 6th jet pt
    // Double_t xbins[] = {450, 500, 600, 700, 1200,  2500}; // BinH
    // Double_t xbins[] = {450, 500, 700, 1200,  2500}; // HT
    // Double_t ybins[] = {34, 36., 38, 40, 45., 50., 60, 80,  200}; //BinI                                
    // Double_t ybins[] = {34,  38, 40, 45., 50., 60, 80,  200}; //BinJ                                
    // Double_t ybins[] = {34,  38, 40, 45., 50., 60,  200}; //BinK                                
    // Double_t xbins[] = {450, 500, 550, 650, 750, 1000,  2500}; //BinL
    // Double_t xbins[] = {450, 500, 550, 700, 1000,  2500}; //BinM
    // Double_t ybins[] = {34,  38, 42 , 50., 60,  200}; //BinN                                
    // Double_t xbins[] = {450, 490, 530, 700, 1000,  2500}; //BinN
    // Double_t xbins[] = {450, 500, 550,  900,  2500}; //BinZ
    // Double_t ybins[] = {34,  40, 48,  200}; //BinZ                           

    //different binning for different b jet multiplicity
    // Double_t xbins[] = {450, 490, 530, 700, 1000,  2500}; //2b
    // Double_t ybins[] = {34,  38, 42, 46, 50,  60,  200}; //2b; BinX                              
    // Double_t xbins3b[] = {450, 490, 530, 700, 1000,  2500}; //3b BinA
    // Double_t ybins3b[] = {34,  38, 42,  50,   200}; //3b; BinA                              
    // Double_t xbins4b[] = {450, 500,  800,  2500}; //4b
    // Double_t ybins4b[] = {34,  40, 48,  200}; //4b                         

    //BinB
    // Double_t xbins[] = {450, 480, 510, 550, 600, 900,  2500}; //3b
    // Double_t ybins[] = {34,  37, 40, 45, 50,  60,  200}; //2b                              
    // Double_t xbins3b[] = {450, 480, 510, 550, 600, 900,  2500}; //3b
    // Double_t ybins3b[] = {34,  37, 40, 45, 50,  200};                              
    // Double_t xbins4b[] = {450, 500,  800,  2500}; //4b
    // Double_t ybins4b[] = {34,  40, 48,  200}; //4b                         

    //BinD 
    Double_t xbins[] = { 500, 540, 600, 900,  2500}; //3b
    Double_t ybins[] = {40, 45, 50,  60,  200}; //2b                              
    Double_t xbins3b[] = { 500, 550, 600,  2500}; 
    Double_t ybins3b[] = {40, 50,  60,  200};                               
    Double_t xbins4b[] = {480, 550,  2500}; //4b
    Double_t ybins4b[] = {38,  45,  200}; //4b                         



    b1HT6pt_de = new TH2D(m_processName + "_baseline1Muon4b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins4b) / sizeof(Double_t) - 1, xbins4b, sizeof(ybins4b) / sizeof(Double_t) - 1, ybins4b);
    b1HT6pt_nu = new TH2D(m_processName + "_baseline1MuonAndHLT4b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins4b) / sizeof(Double_t) - 1, xbins4b, sizeof(ybins4b) / sizeof(Double_t) - 1, ybins4b);

    b2HT6pt_de = new TH2D(m_processName + "_baseline1Muon2b" + "_jetsHTAnd6pt", "H(GeV)Tpt_{6th jet}t", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b2HT6pt_nu = new TH2D(m_processName + "_baseline1MuonAndHLT2b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);

    b3HT6pt_de = new TH2D(m_processName + "_baseline1Muon3b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins3b) / sizeof(Double_t) - 1, xbins3b, sizeof(ybins3b) / sizeof(Double_t) - 1, ybins3b);
    b3HT6pt_nu = new TH2D(m_processName + "_baseline1MuonAndHLT3b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins3b) / sizeof(Double_t) - 1, xbins3b, sizeof(ybins3b) / sizeof(Double_t) - 1, ybins3b);
    //noMuon
    b1HT6ptNoMu_de = new TH2D(m_processName + "_baseline4b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins4b) / sizeof(Double_t) - 1, xbins4b, sizeof(ybins4b) / sizeof(Double_t) - 1, ybins4b);
    b1HT6ptNoMu_nu = new TH2D(m_processName + "_baselineAndHLT4b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins4b) / sizeof(Double_t) - 1, xbins4b, sizeof(ybins4b) / sizeof(Double_t) - 1, ybins4b);

    b2HT6ptNoMu_de = new TH2D(m_processName + "_baseline2b" + "_jetsHTAnd6pt", "H(GeV)Tpt_{6th jet}t", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b2HT6ptNoMu_nu = new TH2D(m_processName + "_baselineAndHLT2b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);

    b3HT6ptNoMu_de = new TH2D(m_processName + "_baseline3b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins3b) / sizeof(Double_t) - 1, xbins3b, sizeof(ybins3b) / sizeof(Double_t) - 1, ybins3b);
    b3HT6ptNoMu_nu = new TH2D(m_processName + "_baselineAndHLT3b" + "_jetsHTAnd6pt", "HT(GeV):p_{T}^{6th jet}", sizeof(xbins3b) / sizeof(Double_t) - 1, xbins3b, sizeof(ybins3b) / sizeof(Double_t) - 1, ybins3b);
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

        Bool_t baseline = baselineSelection(e, m_isRun3, kFALSE);
        baseline = baseline && e->jets_6pt.v()>34.;
        if (!(baseline))
        {
            continue;
        }

        Bool_t is1muon = kTRUE;
        Bool_t ifHLT = HLTSel(e, m_era);//!!!
        Int_t bjetsNum = m_isRun3? e->bjetsPTM_num.v(): e->bjetsM_num.v();
        const Bool_t is4b = (bjetsNum > 3); //!change to >=4b
        const Bool_t is2b = (bjetsNum == 2);
        // const Bool_t is3b = (bjetsNum > 2);
        const Bool_t is3b = (bjetsNum == 3);

        if (m_era.CompareTo("2016") == 0)
        {
            if (i == 0)
            {
                std::cout << "HLT selection for 2016\n";
            }
            // is1muon = e->HLT_IsoMu24.v() == 1 && e->muonsTopMVAT_num.v() == 1 && e->muonsTopMVAT_1pt.v() >= 30.;                                   // 2016
            is1muon = e->HLT_IsoMu24.v() == 1 && e->muonsTopMVAT_num.v() >= 1 && e->muonsTopMVAT_1pt.v() >= 30.;                                   // 2016
        }
        else if (m_era.CompareTo("2018") == 0)
        {
            if (i == 0)
            {
                std::cout << "HLT selection for 2018\n";
            }
            is1muon = e->HLT_IsoMu24.v() == 1 && e->muonsTopMVAT_num.v() >= 1 && e->muonsTopMVAT_1pt.v() >= 30.;
        }
        else if (m_era.CompareTo("2017") == 0)
        {
            if (i == 0)
            {
                std::cout << "HLT selection for 2017\n";
            }
            is1muon = e->HLT_IsoMu27.v() == 1 && e->muonsTopMVAT_num.v() >= 1 && e->muonsTopMVAT_1pt.v() >= 30.;
        }else if(m_era.Contains("2022")){
            is1muon = e->HLT_IsoMu24.v() && e->muonsT_num.v() >= 1 && e->muonsT_1pt.v() >= 30.;
        }
        else
        {
            std::cout << "!!! no HLT selection\n";
        }


        Double_t basicWeight = 1.0;
        if (!m_isData)
        {
            if(!m_isRun3){
                basicWeight = (e->EVENT_prefireWeight.v()) * (e->EVENT_genWeight.v()) * (e->PUweight_.v()) * (e->btagWPMedium_weight.v()) * e->musTopMVAT_weight.v() * e->elesTopMVAT_weight.v();
            }else{
                basicWeight = (e->EVENT_genWeight.v()) * (e->PUweight_.v()) * (e->btagWPMedium_weight.v());
            }
        }

        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon, "baseline1Muon", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon && ifHLT, "baseline1MuonAndHLT", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline , "baseline", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && ifHLT, "baselineAndHLT", basicWeight, m_isData);
        //seperate by b-jets
        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon && is4b, "baseline1Muon1b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon && ifHLT && is4b, "baseline1MuonAndHLT1b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && is4b , "baseline1b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && ifHLT && is4b, "baselineAndHLT1b", basicWeight, m_isData);
        //2b
        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon && is2b, "baseline1Muon2b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon && ifHLT && is2b, "baseline1MuonAndHLT2b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && is2b , "baseline2b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && ifHLT && is2b, "baselineAndHLT2b", basicWeight, m_isData);
        //>=3bs
        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon && is3b, "baseline1Muon3b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && is1muon && ifHLT && is3b, "baseline1MuonAndHLT3b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && is3b , "baseline3b", basicWeight, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, baseline && ifHLT && is3b, "baselineAndHLT3b", basicWeight, m_isData);

        // 2D
        // if (baseline && is1muon)
        if (baseline)
        {
            if (is4b)
            {
                WH::fillDeNu(ifHLT, b1HT6ptNoMu_de, b1HT6ptNoMu_nu, e->jets_HT.v(), e->jets_6pt.v(), basicWeight, m_isData);
                if(is1muon){
                    WH::fillDeNu(ifHLT, b1HT6pt_de, b1HT6pt_nu, e->jets_HT.v(), e->jets_6pt.v(), basicWeight, m_isData);
                }
            }
            if (is2b)
            {
                WH::fillDeNu(ifHLT, b2HT6ptNoMu_de, b2HT6ptNoMu_nu, e->jets_HT.v(), e->jets_6pt.v(), basicWeight, m_isData);
                if(is1muon){
                    WH::fillDeNu(ifHLT, b2HT6pt_de, b2HT6pt_nu, e->jets_HT.v(), e->jets_6pt.v(), basicWeight, m_isData);
                }
            }    
            if (is3b)
            {
                WH::fillDeNu(ifHLT, b3HT6ptNoMu_de, b3HT6ptNoMu_nu, e->jets_HT.v(), e->jets_6pt.v(), basicWeight, m_isData);
                if(is1muon){
                    WH::fillDeNu(ifHLT, b3HT6pt_de, b3HT6pt_nu, e->jets_HT.v(), e->jets_6pt.v(), basicWeight, m_isData);
                }
            }
        }

    }
    std::cout << "end of event loop\n\n";
};

void WH_HLTeff::Terminate(){
    std::cout << "Termintate: ..........................................\n";
    if (!m_isData)
    {
        Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
        Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
        std::cout << "m_processName=" << m_processName << " lumi=" << TTTT::lumiMap.at(m_era) << " crossSection=" << TTTT::crossSectionMap.at(m_processName) << "\n";
        WH::histRegionsVectScale(histsForRegion_vec, processScale);

        b1HT6pt_de->Scale(processScale);
        b1HT6pt_nu->Scale(processScale);
        b2HT6pt_de->Scale(processScale);
        b2HT6pt_nu->Scale(processScale);
        b3HT6pt_de->Scale(processScale);
        b3HT6pt_nu->Scale(processScale);

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