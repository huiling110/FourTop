// #include "../include/usefulFunc.h"
#include "../include/makeVariablesMain.h"

void MakeVariablesMain::EventLoop(Bool_t baselineSel, ULong_t numEntries)
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

        // muVarMaker.makeVariables(e);
        muVarMaker.makeVariables(e);

        tauVarMaker.makeVariables(e); // tight tau
        tauFVarMaker.makeVariables(e);
        tauLVarMaker.makeVariables(e);

        // jet
        jetVarMaker.makeVariables(e);
        jetTVarMaker.makeVariables(e);
        bjetMVarMaker.makeVariables(e);
        bjetLVarMaker.makeVariables(e);
        bjetTVarMaker.makeVariables(e);

        // copy some branches
        copyBranches.makeVariables(e);

        // SF and systematic calculation

        // baseline selection
        //  if (!(jets_HT > 500 && jets_6pt > 40.0 && jets_number >= 6 && bjetsM_num >= 1))

        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n";
    std::cout << "\n";
};

void MakeVariablesMain::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";

    // add Runs tree
    if (!(m_isData))
    {
        std::cout << "--------\n";
        std::cout << "now comes to add Runs tree stage\n";
        TChain chain2("Runs");
        chain2.Add(m_inputDir + "outTree*.root");
        // chain2.Merge(m_output, 2000);
        TTree *Runs = chain2.CloneTree();
        Runs->SetDirectory(m_output);
        std::cout
            << "done merging Runs trees\n";
        std::cout << "\n";
    }

    m_output->Write();
    m_output->Close();
    std::cout << "output file here: " << m_output->GetName() << "\n";
    std::cout << "Termination done .....................................................\n";
};

MakeVariablesMain::~MakeVariablesMain(){};
