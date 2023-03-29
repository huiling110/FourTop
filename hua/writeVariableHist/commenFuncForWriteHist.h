

#include "TH1D.h"

TH2D *getHistFromFile(TString fileName, TString histName)
{
    file = new TFile(fileName, "READ");
    // if (file.IsZombie()){

    // }
    TH2D *hist = (TH2D *)file->Get(histName)->Clone();
    file.Close();
    delete file;
    return hist;
}
