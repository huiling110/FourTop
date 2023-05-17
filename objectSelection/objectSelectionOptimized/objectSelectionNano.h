#ifndef OBJECTSELECTIONNANO_H
#define OBJECTSELECTIONNANO_H

#include "TTreeReader.h"
#include "TTreeReaderArray.h"

#include "eventReader_nano.C"

class objectSelection
{
public:
    objectSelection(TString inputFile, TString outputDir)
    {
        m_input = new TTFile(inputFile, "READ");
        m_reader = TTreeReader("Events", m_input);
        e = new eventForNano{m_reader};
    };
    ~objectSelection();
    osBase muonSelection(e, m_outTree);

    Init();

    EventLoop();
    Terminate();

private:
    TFile *m_input;
    TTreeReader *m_reader;
    eventForNana *e;
    TFile *m_output;
}

#endif