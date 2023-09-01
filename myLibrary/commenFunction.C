#include "commenFunction.h"

#include <iostream>
#include <TFile.h>
#include <TTree.h>

namespace TTTT
{

    Bool_t getIsData(TString inputDir)
    {
        Bool_t isData;
        if (inputDir.Contains("mc"))
        {
            isData = kFALSE;
        }
        else
        {
            isData = kTRUE;
        }
        return isData;
    }

    TString getEra(TString inputDir)
    {
        //for 2016 this only works for nanoaod input DIr
        TString era;
        if (inputDir.Contains("2017"))
        {
            era = "2017";
        }
        else if (inputDir.Contains("2018"))
        {
            era = "2018";
        }
        else if (inputDir.Contains("2016APV"))
        {
            era = "2016preVFP";
        }
        else if (inputDir.Contains("2016"))
        {
            era = "2016postVFP";
        }
        else if (inputDir.Contains("2022preEE"))
        {
            era = "2022preEE";
        }
        else if (inputDir.Contains("2022postEE"))
        {
            era = "2022postEE";
        }
        else if (inputDir.Contains("2022"))
        {
            era = "2022";
        }
        else
        {
            std::cout << "ERROR!!! get era not success!!!\n";
        }
        return era;
    }
    TString getEra2(TString inputDir)
    {
        //for 2016 this only works for nanoaod input DIr
        TString era;
        if (inputDir.Contains("2017"))
        {
            era = "2017";
        }
        else if (inputDir.Contains("2018"))
        {
            era = "2018";
        }
        else if (inputDir.Contains("2016") && inputDir.Contains("preVFP"))
        {
            era = "2016preVFP";
        }
        else if (inputDir.Contains("2016") && inputDir.Contains("postVFP"))
        {
            era = "2016postVFP";
        }
        else if (inputDir.Contains("2016"))
        {
            era = "2016";
        }
        else if (inputDir.Contains("2022"))
        {
            if(inputDir.Contains("2022preEE")){
                era = "2022preEE";
            }
            else if (inputDir.Contains("2022postEE"))
            {
                era = "2022postEE";
            }else{
            era = "2022";
            }
        }
        else
        {
            std::cout << "ERROR!!! get era not success!!!\n";
        }
        return era;
    }

    Bool_t isRun3(TString era)
    {
        Bool_t isRun3 = kFALSE;
        // if (era.CompareTo("2022") == 0)
        if (era.Contains("2022"))
        {
            isRun3 = kTRUE;
        }
        return isRun3;
    }

    void fillHist(TH1D*& hist, Double_t value, Double_t weight, Bool_t isData){
        if( !isData){
            hist->Fill(value, weight);
        }else{
            hist->Fill(value);
        }
    }


    Double_t getGenSum(TString inputFile)
    {
        Double_t genWeightSumInitial = 1.0;
        TFile *m_file = new TFile(inputFile, "READ");
        TTree *Runs = (TTree *)m_file->Get("Runs");
        Double_t igen;
        Runs->SetBranchAddress("genEventSumw", &igen);
        genWeightSumInitial = 0.0;
        for (int iEntry = 0; Runs->LoadTree(iEntry) >= 0; ++iEntry)
        {
            Runs->GetEntry(iEntry);
            genWeightSumInitial += igen;
        }
        m_file->Close();
        std::cout << "genWeightSumInitial: " << genWeightSumInitial << "\n";
        return genWeightSumInitial;
    }



// TH1D *getHistogramFromFile(TString filename, const char *histname)
// {
//     TFile *file = TFile::Open(filename);
//     if (!file || file->IsZombie())
//     {
//         std::cerr << "Error: could not open file " << filename << std::endl;
//         return nullptr;
//     }
//     TH1D *hist = (TH1D *)(file->Get(histname));
//     if (!hist)
//     {
//         std::cerr << "Error: could not retrieve histogram " << histname << " from file " << filename << std::endl;
//         file->Close();
//         return nullptr;
//     }
//     hist->SetDirectory(nullptr); // detach histogram from file to prevent it from being deleted
//     file->Close();
//     return hist;
// }


Double_t get2DSF(Double_t x, Double_t y, TH2D *hist, UInt_t sys)
{ // sys =0: normal; sys=1: up; sys=2: down
    Double_t sf = 1.0;
    Int_t xbins = hist->GetXaxis()->GetNbins();
    Double_t xmin = hist->GetXaxis()->GetBinLowEdge(1);
    Double_t xmax = hist->GetXaxis()->GetBinUpEdge(xbins);
    Int_t ybins = hist->GetYaxis()->GetNbins();
    Double_t ymin = hist->GetYaxis()->GetBinLowEdge(1);
    Double_t ymax = hist->GetYaxis()->GetBinUpEdge(ybins);
    if (x >= xmin && x < xmax && y >= ymin && y < ymax)
    {
        Int_t binx = hist->GetXaxis()->FindBin(x);
        Int_t biny = hist->GetYaxis()->FindBin(y);
        sf = hist->GetBinContent(binx, biny);
        Double_t err = hist->GetBinError(binx, biny);
        if (sys == 1)
        {
            sf = sf + err;
        }
        if (sys == 2)
        {
            sf = sf - err;
        }
        if(sys==5){
            sf = err;
        }
    }
    return sf;
}











};