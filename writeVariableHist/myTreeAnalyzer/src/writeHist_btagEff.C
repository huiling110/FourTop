
#include "../include/writeHist_btagEff.h"
#include "../../myLibrary/commenFunction.h"
#include "../include/commenSelectionAndWeight.h"
#include "../../src_cpp/lumiAndCrossSection.h"

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

void WriteHist_btagEff::Init(){
    std::cout<<"Initializing WriteHist_btagEff........\n";
    m_h2D_jets_ptEta_b->SetDirectory(m_outFile);
    m_h2D_jets_ptEta_c->SetDirectory(m_outFile);
    m_h2D_jets_ptEta_l->SetDirectory(m_outFile);
    m_h2D_jets_ptEta_b_nu->SetDirectory(m_outFile);
    m_h2D_jets_ptEta_c_nu->SetDirectory(m_outFile);
    m_h2D_jets_ptEta_l_nu->SetDirectory(m_outFile);
    std::cout<<"Done initialization........\n";

}

void WriteHist_btagEff::LoopTree(){
    std::cout << "Start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 10000;
    }

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        if (!(baselineSelection(e)))
        {
            continue;
        }
        // Double_t eventWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v();
        Double_t eventWeight =  e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v();
        // std::cout << eventWeight << "\n";

        for(UInt_t i=0; i<e->jets_pt_->size(); i++){
            Int_t jetFlavour = e->jets_flavour_->at(i); 
            Double_t jetPt = e->jets_pt_->at(i);
            Double_t jetEta = std::abs(e->jets_eta_->at(i));
            Double_t jetBtag = e->jets_btags_->at(i);
            Bool_t ifPassBtagM = jetBtag > TTTT::DeepJetM.at(m_era);

            switch (jetFlavour)
            {
            case 5: // b jet
                m_h2D_jets_ptEta_b->Fill( jetPt, jetEta, eventWeight );
                if(ifPassBtagM){
                    m_h2D_jets_ptEta_b_nu->Fill( jetPt, jetEta, eventWeight );
                }
                break;
            case 4: //c jet
                m_h2D_jets_ptEta_c->Fill( jetPt, jetEta, eventWeight );
                if(ifPassBtagM){
                    m_h2D_jets_ptEta_c_nu->Fill( jetPt, jetEta, eventWeight );
                }
                break;
            case 0: //c jet
                m_h2D_jets_ptEta_l->Fill( jetPt, jetEta, eventWeight );
                if(ifPassBtagM){
                    m_h2D_jets_ptEta_l_nu->Fill( jetPt, jetEta, eventWeight );
                }
                break;
            default:
                break;
            }
        }
    }
}

void WriteHist_btagEff::Terminate(){
    std::cout << "Termintate: ..........................................\n";
    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";

}

WriteHist_btagEff::~WriteHist_btagEff()
{
}