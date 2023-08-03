#include "../include/objectSelectionNano.h"
#include "../include/usefulFunc.h"
#include "../../src_cpp/lumiAndCrossSection.h"

void objectSelection::EventLoop(Bool_t preSelection, ULong_t numEntries, const Int_t tauTES)
{
    ULong_t entryCount = 0;
    if (numEntries <= 0)
    {
        numEntries = m_reader.GetEntries();
    }
    std::cout << "Start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        entryCount++;
        Double_t genWeight = 1.0;
        if(!m_isData){
            genWeight = **e->genWeight;
        }
        m_cutflow->Fill(0);

        // good lumi and good PV selection
        if (!(lumiAndPVSelection.Select(m_isData, e)))
        {
            continue;
        };

        // MET filters
        if (!(metFilter.Select(m_era, e)))
        {
            continue;
        }
        m_cutflow->Fill(1);

        // HLT selection and HLT branch filling
        if (!(HLTselection.Select(e, m_era, m_isData, kTRUE)))
        {
            continue; // contains event selection!!!
        }
        m_cutflow->Fill(2);

        muSel.Select(e);
        eleMVASel.Select(e);
        std::vector<Double_t> lepEtaVec;
        std::vector<Double_t> lepPhiVec;
        getLepEtaPhi(lepEtaVec, lepPhiVec);

        // TOPMVA lepton selection
        eleTopMVATSel.Select(e);
        muTopMVATSel.Select(e);

        // tau selection
        // Int_t tauTES = 0;
        // Int_t tauTES = 4; // no tau energy correction
        tauSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tauTES);
        tauSelF.Select(e, m_isData, lepEtaVec, lepPhiVec, tauTES);
        tauSelL.Select(e, m_isData, lepEtaVec, lepPhiVec, tauTES);
        const std::vector<Double_t> tausFEtaVec = tauSelF.getEtaVec();
        const std::vector<Double_t> tausFPhiVec = tauSelF.getPhiVec();
        m_tausTotal += tauSel.getSize();
        m_tausFTotal += tauSelF.getSize();
        m_tausLTotal += tauSelL.getSize();

        // jet and bjet selection
        const Bool_t ifJER = kFALSE;
        // const Bool_t ifJER = kTRUE;
        const Int_t sysJEC = 0;
        jetSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        jetTSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetMSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetLSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetTSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        m_jetsTotal += jetSel.getSize();
        m_bjetsM += bjetMSel.getSize();

        // copy some nanoAOD branches
        copyBranch.Select(e, m_isData);

        // pile up weight cal
        puWeightCal.Select(e, m_isData);//!!!to do

        // pre selection
        if (preSelection)
        {
            if (!(jetSel.getSize() > 5 && bjetMSel.getSize() > 0))
                continue;
        }
        m_cutflow->Fill(3);

        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n";
};

void objectSelection::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    std::cout << "outFile here: " << m_output->GetName() << "\n";
    std::cout << "initial events:" << m_cutflow->GetBinContent(1) << ";   HLT: " << m_cutflow->GetBinContent(3) << " preSelection: " << m_cutflow->GetBinContent(4) << "\n";
    //";   HLT: " << m_cutflow->GetEntries(3) << " preSelection: " << m_cutflow->GetEntries(4) << "\n";
    std::cout << "elesTotal=" << eleMVASel.getTotal() << ";   musTotal=" << muSel.getTotal() << ";   tausTotal=" << m_tausTotal << "; tausF=" << m_tausFTotal << "; tausL=" << m_tausLTotal << ";  jets=" << m_jetsTotal << ";  bjetsM=" << m_bjetsM << "\n";

    // get Runs tree
    if (!m_isData)
    {
        std::cout << "copy Runs tree\n";
        TTree *runs = (TTree *)m_input->Get("Runs");
        runs->SetBranchStatus("*", 0);
        runs->SetBranchStatus("genEventSumw", 1);

        TTree *runsForOut = runs->CloneTree();
        runsForOut->SetDirectory(m_output);
    }

    //scale cutflow hist
    //!!!I don't think we can scale individial tree like this


    m_output->Write();
    m_output->Close();

    std::cout << "Termination done .....................................................\n";
};

objectSelection::~objectSelection()
{
    delete m_input;
    delete e;
    // delete m_output;
};

void objectSelection::getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec)
{
    std::vector<Double_t> &muEtaVec = muTopMVATSel.getEtaVec();
    std::vector<Double_t> &muPhiVec = muTopMVATSel.getPhiVec();
    std::vector<Double_t> &eleEtaVec = eleTopMVATSel.getEtaVec();
    std::vector<Double_t> &elePhiVec = eleTopMVATSel.getPhiVec();
    if(m_isRun3){
        muEtaVec = muSel.getEtaVec();
        muPhiVec = muSel.getPhiVec();
        eleEtaVec = eleMVASel.getEtaVec();
        elePhiVec = eleMVASel.getPhiVec();
        }
    OS::addTwoObjs(muEtaVec, eleEtaVec, lepEtaVec);
    OS::addTwoObjs(muPhiVec, elePhiVec, lepPhiVec);
    // std::cout<<"lepEtaVec = "<< lepEtaVec.size()<<"\n";
};