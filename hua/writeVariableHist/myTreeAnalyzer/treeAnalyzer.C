#include <iostream>

#include "treeAnalyzer.h"

void treeAnalyzer::Init()
{
    std::cout << "start to initilation\n";
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