#include <iostream>

#include "treeAnalyzer.h"

void treeAnalyzer::Init()
{
    std::cout << "start to initilation\n";
}

void treeAnalyzer::LoopTree()
{
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 1000;
    }
    std::cout << "looping over trees of " << allEvent << "\n";
}

void treeAnalyzer::Terminate()
{
    delete m_tree;
    m_file->Close();
}

treeAnalyzer::~treeAnalyzer()
{
    // code to free any dynamically allocated resources
}