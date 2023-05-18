#include "objectSelectionNano.h"

void objectSelection::EventLoop()
{
    ULong_t entryCount = 0;
    ULong_t numEntries = 1000;
    std::cout << "start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        std::cout << *(e->nElectron) << "\n";
        // muonSelection.select(e, m_outTree);
        // Increment the entry count
        entryCount++;
    }
    std::cout << "end of event loop...................................................\n";
};

void objectSelection::Terminate(){

};

objectSelection::~objectSelection()
{
    // delete m_input;
    delete e;
    // delete m_output;
};
