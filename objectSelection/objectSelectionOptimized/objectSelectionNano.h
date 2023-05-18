#ifndef OBJECTSELECTIONNANO_H
#define OBJECTSELECTIONNANO_H
// #include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"

#include "eventReader_nano.C"

class objectSelection
{
public:
    objectSelection(TString inputFile, TString outputDir)
    {
        std::cout << "initialize objectSelection class\n";
        m_input = new TFile(inputFile, "READ");
        if (!m_input->IsZombie())
        {
            std::cout<<"input file: "<<m_input->GetName()<<"\n";
            m_reader = TTreeReader("Events", m_input);
            e = new eventForNano{m_reader};
        }
        else
        {
            std::cout << "BAD!!! file not correctly open\n";
        }
        std::cout << "done initializing objectSelection class\n";
    };
    ~objectSelection();
    // osBase muonSelection(e, m_outTree);

    void Init();

    void EventLoop();
    void Terminate();

private:
    TFile *m_input;
    TTreeReader m_reader;
    eventForNano *e;
    TFile *m_output;
};

#endif