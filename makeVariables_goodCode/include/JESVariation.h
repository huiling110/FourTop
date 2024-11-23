
#include <iostream>
#include <cmath>
#include <correction.h>
#include <TTreeReaderArray.h>

class JESVariation {
public:
    JESVariation(TString era, const UChar_t variation=0);
    void applyJESVariation(const TTreeReaderArray<Double_t> &jets_pt, const TTreeReaderArray<Double_t> &jets_mass);

private:
    const    UChar_t m_JESVariation =0;
    const TString m_era = "2017";
    std::unique_ptr<correction::CorrectionSet> cset_jerSF;
};