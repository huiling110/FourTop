#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <vector>

#include "TFormula.h"
#include <TRandom3.h>
#include "TLorentzVector.h"

void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Float_t> &array, std::vector<Double_t> & vec);
void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Int_t> &array, std::vector<Double_t> & vec);
void printElements(const std::vector<Double_t>& jets_btags, const std::vector<TLorentzVector>& jets );

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2) ;


Double_t deltRmin(const Double_t eta1, const Double_t phi1, const std::vector<TLorentzVector> LeptonsMVAF);

bool compEle(const TLorentzVector a, const TLorentzVector b) ;
//test
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

void jetsSubstructBjets(std::vector<TLorentzVector>& nonbjets,   const std::vector<TLorentzVector>& jets, const std::vector<TLorentzVector>& bjets );

    // SelectJets(0, deepJet, jets, jets_btags, jets_index, jets_flavour, SysJes, SysJer, leptonsMVAL, tausL);
void sortJetAndFlavorAndBcore( std::vector<TLorentzVector>& jets, std::vector<Double_t>& jets_btags, std::vector<Int_t> jets_flavour );

void readSmearingFile(TString _path, std::vector<std::vector<std::string>> & _resolution, std::string & _resFormula) ;
void getMatchingToGen (TTreeReaderArray<Float_t> &recoEta, TTreeReaderArray<Float_t> &recoPhi, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, std::vector<int>* & matchingIdx);// why do I need to pass the TTreeReaderArray by reference? If not, errors are prompted 


Float_t GetJerFromFile(Float_t eta, std::vector<std::vector<std::string>>  resSFs, int central);

Float_t GetStochasticFactor(Float_t pt, Float_t eta, Float_t rho, std::vector<std::vector<std::string> >  resolution, TString  resFormula);

Float_t GetSmearFactor(Float_t pt, Float_t genPt, Float_t eta, Float_t rho, Float_t jer_sf, std::vector<std::vector<std::string> > resolution, TString resFormula, TRandom3 ran);
void readJSON( const Bool_t isdata, const TString jsonInFile, std::map<Int_t,std::vector<Int_t> >&  _goodLumis );
    

/////////////////////////