#include "objectSelectionNano.h"

void objectSelection::EventLoop()
{
    ULong_t entryCount = 0;
    // ULong_t numEntries = 1000;
    ULong_t numEntries = 10;
    std::cout << "start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        // std::cout << *(*(e->nElectron)) << "\n";
        std::cout << *e->nElectron << "\n";
        // for (UInt_t j = 0; e->Electron_dxy->size(); j++)
        // for (UInt_t j = 0; sizeof(e->Electron_dxy); j++)
        // {
        //     std::cout << "dxy: " << e->Electron_dxy[j] << " ";
        // };
        muonSelection.Select(e);
        // HLTselection.Select(e);
        // Increment the entry count
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
