// #include "../include/usefulFunc.h"
#include "../include/makeVariablesMain.h"

void MakeVariablesMain::EventLoop(Bool_t preSelection, ULong_t numEntries )
{
    ULong_t entryCount = 0;
    std::cout << "Start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        entryCount++;
        // h_forEY_initial->Fill(0);

    };
    std::cout << "End of event loop...................................................\n";
};

void MakeVariablesMain::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    std::cout<<"Termination done .....................................................\n";
};

MakeVariablesMain::~MakeVariablesMain(){
    // delete m_input;
    // delete e;
    // delete m_output;
};
