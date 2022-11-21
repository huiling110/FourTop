#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <TROOT.h>
#include <vector>

#include "TFormula.h"
#include <TRandom3.h>
#include "TLorentzVector.h"
#include <Math/Vector4D.h>

void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Float_t> &array, std::vector<Double_t> &vec);
void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Int_t> &array, std::vector<Int_t> &vec);
void printElements(const std::vector<Double_t> &jets_btags, const std::vector<ROOT::Math::PtEtaPhiMVector> &jets);

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2);

Double_t deltRmin(const Double_t eta1, const Double_t phi1, const std::vector<ROOT::Math::PtEtaPhiMVector> LeptonsMVAF);

bool compEle(const ROOT::Math::PtEtaPhiMVector a, const ROOT::Math::PtEtaPhiMVector b);
// test
/*
void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Float_t> &array, std::vector<Double_t> & vec);
    for( UInt_t i=0; i< array.GetSize(); i++);
        vec.push_back( array.At(i));
    }
}
void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Int_t> &array, std::vector<Double_t> & vec);
    for( UInt_t i=0; i< array.GetSize(); i++);
        vec.push_back( array.At(i));
    }
}
*/

void jetsSubstructBjets(std::vector<ROOT::Math::PtEtaPhiMVector> &nonbjets, const std::vector<ROOT::Math::PtEtaPhiMVector> &jets, const std::vector<ROOT::Math::PtEtaPhiMVector> &bjets);

// SelectJets(0, deepJet, jets, jets_btags, jets_index, jets_flavour, SysJes, SysJer, leptonsMVAL, tausL);
void sortJetAndFlavorAndBcore(std::vector<ROOT::Math::PtEtaPhiMVector> &jets, std::vector<Double_t> &jets_btags, std::vector<Int_t> jets_flavour);
Int_t genMatchForJER(Double_t recoEta, Double_t recoPhi, Double_t recoPt, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, TTreeReaderArray<Float_t> &genPt, Double_t jet_resolution);

void readSmearingFile(TString _path, std::vector<std::vector<std::string>> &_resolution, std::string &_resFormula);
void getMatchingToGen(TTreeReaderArray<Float_t> &recoEta, TTreeReaderArray<Float_t> &recoPhi, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, std::vector<int> &matchingIdx); // why do I need to pass the TTreeReaderArray by reference? If not, errors are prompted

Double_t GetJerFromFile(Double_t eta, std::vector<std::vector<std::string>> resSFs, int central);

Double_t GetStochasticFactor(Double_t pt, Double_t eta, Double_t rho, std::vector<std::vector<std::string>> resolution, TString resFormula);

Double_t GetSmearFactor(Double_t pt, Double_t genPt, Double_t eta, Double_t rho, Double_t jer_sf, std::vector<std::vector<std::string>> resolution, TString resFormula, TRandom3 ran);
void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis);

/////////////////////////