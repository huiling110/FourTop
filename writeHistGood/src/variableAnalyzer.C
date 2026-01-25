/**
 * @file variableAnalyzer.C
 * @brief Generates input variable histograms with full systematics
 *
 * Based on treeAnalyzer pattern but outputs variable histograms instead of BDT.
 * OUTPUT: inputVarHists_{version}/ (NOT variableHists_ to avoid BDT conflict!)
 *
 * @author Huiling Hua
 * @date 2025-01-25
 */
#include <iostream>

#include "../include/variableAnalyzer.h"
#include "../include/inputFileMap.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/commenSelectionAndWeight.h"
#include "../include/AnalysisLogger.h"

variableAnalyzer::variableAnalyzer(
    const TString inputDir,
    const TString process,
    TString outVersion,
    TString channel,
    Bool_t isTest,
    Bool_t ifSys
) : m_inputDir{inputDir}, m_processName{process}, m_histVersion{outVersion},
    m_channel{channel}, m_isTest{isTest}, m_ifSys{ifSys}
{
    m_file = std::make_unique<TFile>(m_inputDir + m_processName + ".root", "READ");
    if (!m_file || m_file->IsZombie()) {
        throw std::runtime_error("Error: could not open file: " + std::string(m_inputDir + m_processName + ".root"));
    }

    std::cout << "input file: " << m_file->GetName() << "\n";
    m_tree = (TTree*)m_file->Get("newtree");

    if (!m_tree) {
        throw std::runtime_error("Error: could not get tree 'newtree' from file");
    }

    m_era = TTTT::getEra2(m_inputDir);
    m_isData = TTTT::getIsData(m_inputDir);
    m_isRun3 = TTTT::isRun3(m_era);
    std::cout << "m_era=" << m_era << " m_isRun3=" << m_isRun3 << " m_isData=" << m_isData << " m_isTest=" << m_isTest << "\n";

    m_isFakeLepton = m_processName.Contains("fakeLepton");
    m_isFakeTau = m_processName.Contains("fakeTau");
    std::cout << "m_isFakeLepton=" << m_isFakeLepton << " m_isFakeTau=" << m_isFakeTau << "\n";
    std::cout << "m_ifSys=" << m_ifSys << "\n";

    if (m_channel == "1tau0l") {
        m_ifFakeTau = kTRUE;  // Use data-driven fake tau for 1tau0l
    }

    std::cout << "m_processName: " << m_processName << "  m_channel: " << m_channel << "\n";

    // OUTPUT DIRECTORY: inputVarHists_{version}/ (NOT variableHists_ to avoid BDT conflict!)
    m_outFile = new TFile(m_inputDir + "inputVarHists_" + outVersion + "/" + m_processName + ".root", "RECREATE");
    if (!m_outFile || m_outFile->IsZombie()) {
        throw std::runtime_error("Error: could not create output file");
    }

    e = std::make_unique<event>(m_tree);
    m_systematicManager = std::make_unique<SystematicManager>(m_era);
}

variableAnalyzer::~variableAnalyzer() {
    // m_outFile is owned by ROOT and closed in Terminate()
}

void variableAnalyzer::Init() {
    LOG_INFO << "Starting initialization for channel: " << m_channel << ", isRun3: " << m_isRun3;

    std::vector<TString> sysRegions;
    sysRegions.clear();

    // Get regions based on channel (same logic as treeAnalyzer)
    if (m_channel == "1tau1l") {
        std::cout << "initializing for 1tau1l\n";
        WH::getChannelSys(sysRegions, "1tau1lSR", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau1lCR12", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
    } else if (m_channel == "1tau0l") {
        std::cout << "initializing for 1tau0l\n";
        WH::getChannelSys(sysRegions, "1tau0lSR", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau0lVR", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau0lCRMR", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
    } else if (m_channel == "1tau2l") {
        std::cout << "initializing for 1tau2l\n";
        WH::getChannelSys(sysRegions, "1tau2lSR", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau2lCR3", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
    } else {
        std::cout << "WARNING!! channel not specified\n";
    }

    // Initialize variable histograms using functions.C binning
    WH::initializeHistVec(sysRegions, histsForRegion_vec, m_processName, e.get());
    WH::histRegionsVectSetDir(histsForRegion_vec, m_outFile);

    std::cout << "Initialized " << histsForRegion_vec.size() << " variable histograms\n";

    // Calculate theory SF factors (same as treeAnalyzer)
    if (m_isFakeLepton || m_isFakeTau || m_isData) {
        m_scaleRe_normUp_SF = 1;
        m_scaleRe_normDown_SF = 1;
        m_scaleFa_normUp_SF = 1;
        m_scaleFa_normDown_SF = 1;
        m_pdfAlphaS_normUp_SF = 1;
        m_pdfAlphaS_normDown_SF = 1;
    } else {
        m_scaleRe_normUp_SF = WH::calQCDScaleNor(m_file.get(), 7);
        m_scaleRe_normDown_SF = WH::calQCDScaleNor(m_file.get(), 1);
        m_scaleFa_normUp_SF = WH::calQCDScaleNor(m_file.get(), 5);
        m_scaleFa_normDown_SF = WH::calQCDScaleNor(m_file.get(), 3);
        m_pdfAlphaS_normUp_SF = WH::calPDFScaleNor(m_file.get(), 0);
        m_pdfAlphaS_normDown_SF = WH::calPDFScaleNor(m_file.get(), 1);
        m_pdf_normUp_SF = WH::calPDFScaleNor(m_file.get(), 2);
        m_pdf_normDown_SF = WH::calPDFScaleNor(m_file.get(), 3);
        m_PSWeightISR_normUp_SF = WH::calPDFScaleNor(m_file.get(), 4);
        m_PSWeightISR_normDown_SF = WH::calPDFScaleNor(m_file.get(), 5);
        m_PSWeightFSR_normUp_SF = WH::calPDFScaleNor(m_file.get(), 6);
        m_PSWeightFSR_normDown_SF = WH::calPDFScaleNor(m_file.get(), 7);
    }

    std::cout << "m_scaleRe_normDown_SF=" << m_scaleRe_normDown_SF << "\n";
    std::cout << "m_scaleRe_normUp_SF=" << m_scaleRe_normUp_SF << "\n";

    std::cout << "done initializing\n\n";
}

void variableAnalyzer::LoopTree() {
    std::cout << "start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest) {
        allEvent = 10000;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++) {
        m_tree->GetEntry(i);

        if (!(baselineSelection(e.get(), m_isRun3, (m_channel == "1tau2l")))) {
            continue;
        }

        Double_t basicWeight = baseWeightCal(e.get(), i, m_isRun3, m_isData, WH::channelMap.at(m_channel), m_isFakeTau, m_isFakeLepton);

        // Check for invalid weights
        if (std::isnan(basicWeight) || std::isinf(basicWeight)) {
            LOG_WARNING << "Invalid weight (" << basicWeight << ") at event " << i << " - skipping";
            continue;
        }

        // Fake tau weight correction (same as treeAnalyzer)
        if (m_isFakeTau) {
            if (e->jets_num.v() < 4) {
                basicWeight *= 1.2;
            }
        }

        // Fill histograms based on channel
        if (m_channel == "1tau0l") {
            Bool_t SR1tau0l = SR1tau1lSel(e.get(), 1, m_isRun3, m_isFakeTau);
            Bool_t CR1tau0l = SR1tau1lSel(e.get(), 9, m_isRun3, m_isFakeTau);
            Bool_t MR1tau0l = SR1tau1lSel(e.get(), 7, m_isRun3, m_isFakeTau);
            Bool_t VR1tau0l = SR1tau1lSel(e.get(), 8, m_isRun3, m_isFakeTau);

            fillHistVec("1tau0lSR", SR1tau0l, basicWeight);
            fillHistVec("1tau0lVR", VR1tau0l, basicWeight);
            fillHistVec("1tau0lCRMR", CR1tau0l || MR1tau0l, basicWeight);

        } else if (m_channel == "1tau1l") {
            Bool_t SR1tau1l = SR1tau1lSel(e.get(), WH::channelMap.at(m_channel), m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t CR11tau1l = SR1tau1lSel(e.get(), 5, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t CR21tau1l = SR1tau1lSel(e.get(), 4, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);

            fillHistVec("1tau1lSR", SR1tau1l, basicWeight);
            fillHistVec("1tau1lCR12", CR11tau1l || CR21tau1l, basicWeight);

        } else if (m_channel == "1tau2l") {
            Bool_t SR1tau2l = SR1tau1lSel(e.get(), 2, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t CR31tau2l = SR1tau1lSel(e.get(), 12, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);

            fillHistVec("1tau2lSR", SR1tau2l, basicWeight);
            fillHistVec("1tau2lCR3", CR31tau2l, basicWeight);
        }
    }
    std::cout << "end of event loop\n\n";
}

void variableAnalyzer::fillHistVec(const TString& region, Bool_t ifBaseline, Double_t basicWeight) {
    // Fill nominal for all variables
    for (auto& hist : histsForRegion_vec) {
        hist->fillHistVec(region, basicWeight, ifBaseline, m_isData);
    }

    if (!m_ifSys) {
        return;  // Skip systematics if not requested
    }

    // MC samples (not fake lepton/tau or data) get detector and theory systematics
    if (!(m_isFakeLepton || m_isFakeTau || m_isData)) {
        // Apply all detector systematics via SystematicManager
        m_systematicManager->fillSystematicsForVariables(region, basicWeight, ifBaseline, e.get(), histsForRegion_vec, m_isData);

        // Theory systematics
        m_systematicManager->fillTheorySystematicsForVariables(
            region, basicWeight, ifBaseline, e.get(), histsForRegion_vec, m_isData,
            m_scaleRe_normUp_SF, m_scaleRe_normDown_SF,
            m_scaleFa_normUp_SF, m_scaleFa_normDown_SF,
            m_pdfAlphaS_normUp_SF, m_pdfAlphaS_normDown_SF,
            m_pdf_normUp_SF, m_pdf_normDown_SF,
            m_PSWeightISR_normUp_SF, m_PSWeightISR_normDown_SF,
            m_PSWeightFSR_normUp_SF, m_PSWeightFSR_normDown_SF
        );
    } else if (m_isFakeTau) {
        // Data-driven fake tau systematic
        m_systematicManager->fillDataDrivenFakeTauSystematicForVariables(region, e.get(), histsForRegion_vec, ifBaseline, m_isData);
    }
}

void variableAnalyzer::Terminate() {
    std::cout << "Terminate: ..........................................\n";

    if (!(m_isFakeTau || m_isFakeLepton || m_isData)) {
        Double_t genWeightSum = TTTT::getGenSum(m_file.get());
        const Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
        std::cout << "processScale: " << processScale << "\n";

        // Scale all variable histograms
        WH::histRegionsVectScale(histsForRegion_vec, processScale);
    }

    // Print first histogram for debugging
    if (histsForRegion_vec.size() > 0) {
        histsForRegion_vec.at(0)->print();
    }

    m_outFile->Write();
    std::cout << "outputFile: " << m_outFile->GetName() << "\n";
}
