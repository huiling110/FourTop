#ifndef JESVariation_h
#define JESVariation_h

#include <iostream>
#include <cmath>
#include <correction.h>
#include <TTreeReaderArray.h>
#include "TLorentzVector.h"
#include <Math/Vector4D.h>

class JESVariation {
public:
    JESVariation(TString era, const UChar_t variation=0, const UChar_t JESSysUncerType=0);
    void applyJESVariation( std::vector<ROOT::Math::PtEtaPhiMVector>& particleVec);
    std::pair<Double_t, Double_t> applyJESVariation(std::vector<ROOT::Math::PtEtaPhiMVector>& particleVec, std::vector<UInt_t>& removedIndices);

private:
    const    UChar_t m_JESVariation =0; //ordering of the variation array
    const UChar_t m_JESSysUncerType = 0; //0: nominal, >=1: variation
    const TString m_era = "2017";
    TString m_JESTtring="";
    std::unique_ptr<correction::CorrectionSet> cset_jerSF;
};

#endif