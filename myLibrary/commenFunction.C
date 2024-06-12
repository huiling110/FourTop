#include "commenFunction.h"

#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TGraphAsymmErrors.h>

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

   Bool_t isBG(TString processName, Bool_t ifVLL){
       Bool_t isbg = kFALSE;
    //    if(processName.Contains("tttt") || processName.Contains("VLL")){
    //           isbg = kFALSE;
    //    }
        if (ifVLL){
            isbg = !( processName.Contains("VLL"));
        }else{
            isbg =!( processName.Contains("tttt") );
        }
       return isbg;
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

    x = std::min(x, xmax-0.01);
    x = std::max(x, xmin+0.01);
    y = std::min(y, ymax-0.01);
    y = std::max(y, ymin+0.01);

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
    }
    // if(std::abs(sf-1.)<1e-6){
    // std::cout << "x=" << x << " y=" << y << " sf=" << sf << "\n";
    // std::cout<<"xmin="<<xmin<<" xmax="<<xmax<<" ymin="<<ymin<<" ymax="<<ymax<<"\n";
    // }
    
    return sf;
}

void getVarFromFile(TString variableListCsv, std::vector<TString> &variablesName)
{
    std::cout << "reading varibleList: " << variableListCsv << "\n";
    std::ifstream fin(variableListCsv);
    std::string line;
    TString ivariable;
    variablesName.clear();
    while (getline(fin, line))
    {
        ivariable = line;
        if (line.size() > 0)
        {
            std::cout << "ivariable =" << ivariable << "\n";
            variablesName.push_back(ivariable);
        }
    }
    fin.close();
};




Bool_t getFRandError(const std::vector<EtaProngGraph>& graphs, Double_t eta, int tauProng, Double_t pt, Double_t& fr, Double_t& errLow, Double_t& errHigh) {
    for (const auto& graph : graphs) {
        if (graph.isInEtaRange(eta) && graph.tauProng == tauProng) {
            int n = graph.graph->GetN();
            Double_t x, y;
            graph.graph->GetPoint(0, x, y); // Get the first point
            Double_t minX = x - graph.graph->GetErrorXlow(0);
            graph.graph->GetPoint(n-1, x, y); // Get the last point
            Double_t maxX = x + graph.graph->GetErrorXhigh(n-1);

            int index = -1; // Index of the point to use

            // Check if pt is out of range
            if (pt < minX) {
                // Use the first bin
                index = 0;
            } else if (pt > maxX) {
                // Use the last bin
                index = n - 1;
            } else {
                // pt is within range, find the correct bin
                for (int i = 0; i < n; ++i) {
                    graph.graph->GetPoint(i, x, y);
                    if (pt >= x - graph.graph->GetErrorXlow(i) && pt <= x + graph.graph->GetErrorXhigh(i)) {
                        index = i; // Correct bin found
                        break;
                    }
                }
            }

            if (index != -1) {
                // Retrieve the FR and its errors for the determined bin
                graph.graph->GetPoint(index, x, y);
                fr = y;
                errLow = graph.graph->GetErrorYlow(index);
                errHigh = graph.graph->GetErrorYhigh(index);
                return kTRUE;
            } else {
                // This else part is technically not needed as index will always be set
                // but is kept for logical completeness and future-proofing.
                return kFALSE;
            }
        }
    }
    return kFALSE;
}

// void printTag(std::unique_ptr<correction::CorrectionSet> cset){
//     for (auto &corr : *cset)  
//     {
//         printf("Correction: %s\n", corr.first.c_str());
//     }
//     std::cout << "\n";
// }
};