#ifndef COMMENFUNCTION_H
#define COMMENFUNCTION_H


#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <TGraphAsymmErrors.h>

namespace TTTT{



Bool_t getIsData(TString inputDir);
TString getEra(TString inputDir);
TString getEra2(TString inputDir);
Bool_t isBG(TString processName, Bool_t ifVLL=kFALSE);

Bool_t isRun3(TString era);
void fillHist(TH1D *&hist, Double_t value, Double_t weight, Bool_t isData);

    Double_t getGenSum(TString inputFile);

    Double_t get2DSF(Double_t x, Double_t y, TH2D *hist, UInt_t sys);

    // TH1D *getHistogramFromFile(TString filename, const char *histname);
    template <typename T>
    T *getHistogramFromFile(TString filename, const char *histname)
    {
        TFile *file = TFile::Open(filename);
        if (!file || file->IsZombie())
        {
            std::cerr << "Error: could not open file " << filename << std::endl;
            return nullptr;
        }
        T *hist = (T *)(file->Get(histname));
        if (!hist)
        {
            std::cerr << "Error: could not retrieve histogram " << histname << " from file " << filename << std::endl;
            file->Close();
            return nullptr;
        }
        hist->SetDirectory(nullptr); // detach histogram from file to prevent it from being deleted
        std::cout << "Getting hist: " << hist->GetName() << " from: " << file->GetName() << "\n";
        file->Close();
        return hist;
}

void getVarFromFile(TString variableListCsv, std::vector<TString> &variablesName);

template <typename T>
void copyVecToVec(const std::vector<T> &inVec, std::vector<T> &outVec  ){
    outVec.clear();
    for (UInt_t i=0; i<inVec.size(); i++){
        outVec.push_back(inVec.at(i));
    }
}




// Define a struct to hold the graph, its eta boundaries, and tau prong
struct EtaProngGraph {
    Double_t etaMin;
    Double_t etaMax;
    int tauProng;
    TGraphAsymmErrors* graph;
    
    EtaProngGraph(Double_t min, Double_t max, int prong, TGraphAsymmErrors* g)
        : etaMin(min), etaMax(max), tauProng(prong), graph(g) {}
    
    // Check if an eta value falls within this graph's eta range
    Bool_t isInEtaRange(Double_t eta) const {
        return eta >= etaMin && eta < etaMax;
    }
};
Bool_t getFRandError(const std::vector<EtaProngGraph>& graphs, Double_t eta, int tauProng, Double_t pt, Double_t& fr, Double_t& errLow, Double_t& errHigh);


};
#endif