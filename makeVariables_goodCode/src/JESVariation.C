#include "../include/JESVariation.h"
#include "../../src_cpp/lumiAndCrossSection.h"

//write a class to appply JES variation to the jet_pt and jet_mass
//the class should have a method to apply the variation to the jet_pt and jet_mass

JESVariation::JESVariation(TString era, const UChar_t JESVariation) : m_JESVariation{JESVariation}, m_era{era} {
    std::cout<<"Initialzing JESVariation........\n";
    TString jsonBase = "../../jsonpog-integration/POG/";
    cset_jerSF = correction::CorrectionSet::from_file((jsonBase + TTTT::json_map.at(m_era).at(0)).Data());
    std::cout<<"JEC sf file: "<<(jsonBase + TTTT::json_map.at(m_era).at(0)).Data()<<"\n";

    std::cout<<"Done JESVariation initialization......\n";
}

// void JESVariation::applyJESVariation(const TTreeReaderArray<Double_t> &jets_pt, const TTreeReaderArray<Double_t> &jets_mass){
//     for(UInt_t i=0; i<e->jets_pt.GetSize(); i++){
//         auto corr_jesUncer = cset_jerSF->at(corr_Uncer_JES_map[m_era].at(m_JESSysUncerType).Data());
//         JES_uncer = corr_jesUncer->evaluate({eta, pt}); // do you need the pt to be raw? no
//     }
// }