#ifndef USEFULFUNC_H
#define USEFULFUNC_H
#include <map>

#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <TROOT.h>
#include <vector>

#include "TFormula.h"
#include <TRandom3.h>
#include "TLorentzVector.h"
#include <Math/Vector4D.h>
#include </cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/include/xgboost/c_api.h>
#include <TString.h>

#include "TTreeReaderValueDerived.h"

namespace OS
{
    void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis);

    Double_t TopLeptonEvaluate(std::map<TString, Float_t> &inputFeatures, const BoosterHandle &booster);

    Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2);
    Double_t deltRmin(const Double_t eta1, const Double_t phi1, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec);

    Bool_t overlapRemove(Double_t tauEta, Double_t tauPhi, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec);

    Bool_t descendingComparator(const Double_t &a, const Double_t &b);
    void addTwoObjs(const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &eleEtaVec, std::vector<Double_t> &lepEtaVec);
    // void getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec, EleTopMVASel &eleTopMVATSel, MuTopMVASel &muTopMVATSel);
    Int_t genMatchForJER(Double_t recoEta, Double_t recoPhi, Double_t recoPt, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, TTreeReaderArray<Float_t> &genPt, Double_t jet_resolution);

    template <typename T>
    void copy_TTreeReaderArray_toVector(const TTreeReaderArray<T> &array, std::vector<T> &vec)
    {
        for (UInt_t i = 0; i < array.GetSize(); i++)
        {
            vec.push_back(array.At(i));
        }
    };

    Bool_t isRun3(TString era);
    Double_t quadraticSum(TTreeReaderArray<Float_t> &vec, const Float_t nominal, Int_t eleNum);

    template <typename T>
    void readPointerArray(TTreeReaderArray<T> *&branchPointer, TTreeReader &reader, TString branchName)
    {
        if (reader.GetTree()->FindBranch(branchName))
        {
            branchPointer = new TTreeReaderArray<T>(reader, branchName);
        }
        else
        {
            std::cout << "WARNINIG!!! " << branchName << " not exsit in input nano file\n";
        };
    };
    template <typename A>
    void readPointer(TTreeReaderValue<A> *&branchPointer, TTreeReader &reader, TString branchName)
    {
        if (reader.GetTree()->FindBranch(branchName))
        {
            branchPointer = new TTreeReaderValue<A>(reader, branchName);
        }
        else
        {
            std::cout << "WARNINIG!!! " << branchName << " not exsit in input nano file\n";
        };
    };

};

std::unique_ptr<AbstractTTreeReaderValue> CreateTTreeReaderValue(TTreeReader &reader, const char *branchName);

#endif
