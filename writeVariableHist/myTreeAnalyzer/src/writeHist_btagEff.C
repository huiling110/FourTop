
#include "../include/writeHist_btagEff.h"
#include "../../myLibrary/commenFunction.h"

WriteHist_btagEff::WriteHist_btagEff(const TString inputDir, const TString process, TString outVersion , Bool_t isTest ) : m_inputDir{inputDir}, m_processName{process},  m_isTest{isTest}
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
    std::cout << "m_era=" << m_era << " m_isData=" << m_isData << "  m_isTest=" << m_isTest <<"  m_isRun3="<<m_isRun3<< "\n";

    std::cout << "m_processName: " << m_processName  << "\n";
    m_outFile = new TFile(m_inputDir + "variableHists" + "_" + outVersion + "/" + m_processName + ".root", "RECREATE");

    e = new event(m_tree);
}

WriteHist_btagEff::~WriteHist_btagEff()
{
}