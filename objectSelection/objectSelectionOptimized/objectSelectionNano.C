#include "objectSelectionNano.h"

void objectSelection::EventLoop()
{
    ULong_t entryCount = 0;
    ULong_t numEntries = 1000;
    // ULong_t numEntries = 10;
    std::cout << "start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        if (!(HLTselection.Select(e, m_era, m_isData, kTRUE)))
            continue; // contains event selection!!!

        muonSelection.Select(e);
        // Increment the entry count
        m_outTree->Fill();
        entryCount++;
    };
    std::cout << "end of event loop...................................................\n";
};

void objectSelection::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    m_output->Write();
    std::cout << "outFile here: " << m_output->GetName() << "\n";
    m_output->Close();
};

objectSelection::~objectSelection(){
    // delete m_input;
    // delete e;
    // delete m_output;
};
