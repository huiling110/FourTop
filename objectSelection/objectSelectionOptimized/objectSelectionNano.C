#include "objectSelectionNano.h"
#include "usefulFunc.h"

void objectSelection::EventLoop()
{
    ULong_t entryCount = 0;
    ULong_t numEntries = 1000;
    // ULong_t numEntries = 10;
    std::cout << "Start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        entryCount++;
        h_forEY_initial->Fill(0);

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

        // HLT selection and HLT branch filling
        if (!(HLTselection.Select(e, m_era, m_isData, kTRUE)))
        {
            continue; // contains event selection!!!
        }
        h_forEY_HLT->Fill(0);

        // pile up weight cal

        // TOPMVA lepton selection
        eleTopMVATSel.Select(e);
        muTopMVATSel.Select(e);
        std::vector<Double_t> lepEtaVec;
        std::vector<Double_t> lepPhiVec;
        getLepEtaPhi(lepEtaVec, lepPhiVec);

        // tau selection
        Int_t sysTES = 0;
        tauSel.Select(e, m_isData, lepEtaVec, lepPhiVec, sysTES);

        // jet and bjet selection:w

        // copy some nanoAOD branches

        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n";
};

void objectSelection::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    m_output->Write();
    std::cout << "outFile here: " << m_output->GetName() << "\n";
    std::cout << "initial events:" << h_forEY_initial->GetEntries() << ";   HLT: " << h_forEY_HLT->GetEntries() << "\n";
    m_output->Close();
};

objectSelection::~objectSelection(){
    // delete m_input;
    // delete e;
    // delete m_output;
};

void objectSelection::getLepEtaPhi(std::vector<Double_t>& lepEtaVec, std::vector<Double_t>& lepPhiVec ){
    const std::vector<Double_t>& muEtaVec= muTopMVATSel.getEtaVec();
    const std::vector<Double_t>& muPhiVec= muTopMVATSel.getPhiVec();
    // std::cout<<"muEtaVec = "<< muEtaVec.size()<<"\n";
    const std::vector<Double_t>& eleEtaVec= eleTopMVATSel.getEtaVec();
    const std::vector<Double_t>& elePhiVec= eleTopMVATSel.getPhiVec();
    // std::cout<<"eleEtaVec = "<< eleEtaVec.size()<<"\n";
    addTwoObjs( muEtaVec, eleEtaVec, lepEtaVec);
    addTwoObjs( muPhiVec, elePhiVec, lepPhiVec);
    // std::cout<<"lepEtaVec = "<< lepEtaVec.size()<<"\n";
};