#include "objectSelectionNano.h"

void objectSelection::EventLoop()
{
    ULong_t entryCount = 0;
    ULong_t numEntries = 1000;
    // ULong_t numEntries = 10;
    std::cout << "start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        entryCount++;
        h_forEY_initial->Fill(0);

        // good lumi and good PV selection

        // HLT selection and HLT branch filling
        if (!(HLTselection.Select(e, m_era, m_isData, kTRUE)))
        {
            continue; // contains event selection!!!
        }
        h_forEY_HLT->Fill(0);

        // pile up weight cal

        // TOPMVA lepton selection

        muonSelection.Select(e);
        // Increment the entry count
        m_outTree->Fill();
    };
    std::cout << "end of event loop...................................................\n";
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
