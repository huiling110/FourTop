
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

        for (UInt_t i = 0; i < e->jets_pt_->size(); i++)
        {
            Int_t jetFlavour = e->jets_flavour_->at(i);
            Double_t jetPt = e->jets_pt_->at(i);
            Double_t jetEta = std::abs(e->jets_eta_->at(i));
            Double_t jetBtag = e->jets_btags_->at(i);
            Bool_t ifPassBtagM = jetBtag > TTTT::DeepJetM.at(m_era);
            Bool_t ifEta1 = jetEta <= 1.5;
            Bool_t ifEta2 = jetEta > 1.5;

            // switch (jetFlavour)
            // {
            // case 5: // b jet
            //     fillDeNu(ifPassBtagM, m_h2D_jets_ptEta_b, m_h2D_jets_ptEta_b_nu, jetPt, jetEta, eventWeight);
            //     fillDeNu(ifPassBtagM, ifEta1, de_jetsPt_eta1_b, nu_jetsPt_eta1_b, jetPt, eventWeight);
            //     fillDeNu(ifPassBtagM, ifEta2, de_jetsPt_eta2_b, nu_jetsPt_eta2_b, jetPt, eventWeight);
            //     break;
            // case 4: // c jet
            //     fillDeNu(ifPassBtagM, m_h2D_jets_ptEta_c, m_h2D_jets_ptEta_c_nu, jetPt, jetEta, eventWeight);
            //     fillDeNu(ifPassBtagM, ifEta1, de_jetsPt_eta1_c, nu_jetsPt_eta1_c, jetPt, eventWeight);
            //     fillDeNu(ifPassBtagM, ifEta2, de_jetsPt_eta2_c, nu_jetsPt_eta2_c, jetPt, eventWeight);
            //     break;
            // case 0: // c jet
            //     fillDeNu(ifPassBtagM, m_h2D_jets_ptEta_l, m_h2D_jets_ptEta_l_nu, jetPt, jetEta, eventWeight);
            //     fillDeNu(ifPassBtagM, ifEta1, de_jetsPt_eta1_l, nu_jetsPt_eta1_l, jetPt, eventWeight);
            //     fillDeNu(ifPassBtagM, ifEta2, de_jetsPt_eta2_l, nu_jetsPt_eta2_l, jetPt, eventWeight);
            //     break;
            // default:
            //     break;
            // }
        }
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