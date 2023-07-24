
#include "../include/writeHist_btagShapeR.h"
#include "../../myLibrary/commenFunction.h"
#include "../include/commenSelectionAndWeight.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/functions.h"

WriteHist_btagShapeR::WriteHist_btagShapeR(const TString inputDir, const TString process, TString outVersion, Bool_t isTest) : m_inputDir{inputDir}, m_processName{process}, m_isTest{isTest}
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

void WriteHist_btagShapeR::Init()
{
    std::cout << "Initializing WriteHist_btagShapeR........\n";
    jets_num_de->SetDirectory(m_outFile);
    jets_num_nu->SetDirectory(m_outFile);
    std::cout << "Done initialization........\n";
}

void WriteHist_btagShapeR::LoopTree()
{
    std::cout << "Start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 10000;
    }

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        Bool_t pass = e->jets_num.v() >= 6  && e->jets_HT.v() > 500. && e->jets_6pt.v() > 40. && e->tausT_num.v()>=0;

        // if (!(baselineSelection(e)))
        if (!(pass))
        {
            continue;
        }
        // Double_t eventWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v();
        Double_t eventWeight = e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v()*e->tauT_IDSF_weight_new.v();
        // std::cout << eventWeight << "\n";
        Int_t jetNum = e->jets_num.v();
        jets_num_de->Fill(jetNum, eventWeight);
        jets_num_nu->Fill(jetNum, eventWeight*(e->btagShape_weight.v()));

    }
    std::cout << "Done event loop..........\n";
}

void WriteHist_btagShapeR::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}

WriteHist_btagShapeR::~WriteHist_btagShapeR()
{
}