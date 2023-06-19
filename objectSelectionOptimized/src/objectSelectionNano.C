#include "../include/objectSelectionNano.h"
#include "../include/usefulFunc.h"

void objectSelection::EventLoop(Bool_t preSelection, ULong_t numEntries )
{
    ULong_t entryCount = 0;
    // ULong_t numEntries = 5000;
    // ULong_t numEntries = 10000;
    std::cout << "Start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        entryCount++;
        h_forEY_initial->Fill(0);
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
        h_forEY_HLT->Fill(0);
        m_cutflow->Fill(2);

        muSel.Select(e);
        eleMVASel.Select(e);

        // // TOPMVA lepton selection
        // eleTopMVATSel.Select(e);
        // muTopMVATSel.Select(e);
        std::vector<Double_t> lepEtaVec;
        std::vector<Double_t> lepPhiVec;
        getLepEtaPhi(lepEtaVec, lepPhiVec);

        // // tau selection
        // Int_t sysTES = 0;
        Int_t sysTES = 4; //no tau energy correction
        tauSel.Select(e, m_isData, lepEtaVec, lepPhiVec, sysTES);
        tauSelF.Select(e, m_isData, lepEtaVec, lepPhiVec, sysTES);
        tauSelL.Select(e, m_isData, lepEtaVec, lepPhiVec, sysTES);
        const std::vector<Double_t> tausFEtaVec = tauSelF.getEtaVec();
        const std::vector<Double_t> tausFPhiVec = tauSelF.getPhiVec();
        m_tausTotal+=tauSel.getSize();
        m_tausFTotal+=tauSelF.getSize();
        m_tausLTotal+=tauSelL.getSize();

        // // jet and bjet selection
        const Bool_t ifJER = kFALSE;
        const Int_t sysJEC = 0;
        jetSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        jetTSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetMSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetLSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetTSel.Select(e, m_isData, lepEtaVec, lepPhiVec, tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        m_jetsTotal += jetSel.getSize();
        m_bjetsM+=bjetMSel.getSize();

        // // copy some nanoAOD branches
        copyBranch.Select(e, m_isData);

        // // pile up weight cal
        // puWeightCal.Select(e, m_isData);

        // //pre selection
        // if (preSelection)
        // {
        //     if (!(jetSel.getSize() > 5 && bjetMSel.getSize() > 0))
        //         continue;;
        // }
        h_forEY_preSelection->Fill(0);
        m_cutflow->Fill(3);

        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n";
};

void objectSelection::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    m_output->Write();
    std::cout << "outFile here: " << m_output->GetName() << "\n";
    std::cout << "initial events:" << h_forEY_initial->GetEntries() << ";   HLT: " << h_forEY_HLT->GetEntries() << " preSelection: "<<h_forEY_preSelection->GetEntries()<<"\n";
    m_output->Close();
    std::cout<<"elesTotal="<<eleMVASel.getTotal()<<";   musTotal="<<muSel.getTotal()<<";   tausTotal="<<m_tausTotal<<"; tausF="<<m_tausFTotal<<"; tausL="<<m_tausLTotal<<";  jets="<<m_jetsTotal<<";  bjetsM="<<m_bjetsM<<"\n";
    std::cout<<"Termination done .....................................................\n";
};

objectSelection::~objectSelection(){
    // delete m_input;
    // delete e;
    // delete m_output;
};

void objectSelection::getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec)
{
    const std::vector<Double_t> &muEtaVec = muSel.getEtaVec();
    const std::vector<Double_t> &muPhiVec = muSel.getPhiVec();
    // std::cout<<"muEtaVec = "<< muEtaVec.size()<<"\n";
    const std::vector<Double_t> &eleEtaVec = eleMVASel.getEtaVec();
    const std::vector<Double_t> &elePhiVec = eleMVASel.getPhiVec();
    // std::cout<<"eleEtaVec = "<< eleEtaVec.size()<<"\n";
    addTwoObjs(muEtaVec, eleEtaVec, lepEtaVec);
    addTwoObjs(muPhiVec, elePhiVec, lepPhiVec);
    // std::cout<<"lepEtaVec = "<< lepEtaVec.size()<<"\n";
};