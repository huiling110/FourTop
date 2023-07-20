#ifndef CREATEHIST_H
#define CREATEHIST_H

#include <TFile.h>
#include <TH2D.h>

#include "eventReader_forMV.h"

class CreateHist
{
public: 
    CreateHist(TFile* outFile);
    CreateHist(){
        std::cout << "Default constructor for CreateHist\n";
    }
    ~CreateHist();
    void fillHist(const EventForMV *e);

private:
    TH2D* m_h2D_jets_ptEta_b = new TH2D("jets_ptEta_genB", "jets_ptEta_genB", 10, 40., 700., 10, -2.3, 2.3);//maybe should have the same binnig as that of SF provided by BTV
};

#endif