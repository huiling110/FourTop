// #include "../include/usefulFunc.h"
#include "../include/makeVariablesMain.h"

void MakeVariablesMain::EventLoop(Bool_t preSelection, ULong_t numEntries)
{
    ULong_t entryCount = 0;
    std::cout << "Start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        entryCount++;

        // muVarMaker.makeVariables(e);
        muVarMaker.makeVariables(e);

        tauVarMaker.makeVariables(e);//tight tau
        tauFVarMaker.makeVariables(e);
        tauLVarMaker.makeVariables(e);

        //jet
        jetVarMaker.makeVariables(e);
        jetTVarMaker.makeVariables(e);
        bjetMVarMaker.makeVariables(e);
        bjetLVarMaker.makeVariables(e);
        bjetTVarMaker.makeVariables(e);

        //
        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n";
    std::cout << "\n";
};

void MakeVariablesMain::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    m_output->Write();
    m_output->Close();
    std::cout << "output file here: " << m_output->GetName() << "\n";
    std::cout << "Termination done .....................................................\n";
};

MakeVariablesMain::~MakeVariablesMain(){
    // delete m_input;
    // delete e;
    // delete m_output;
};
