#include "../include/JESVariation.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/inputMap_MV.h"

//write a class to appply JES variation to the jet_pt and jet_mass
//the class should have a method to apply the variation to the jet_pt and jet_mass

JESVariation::JESVariation(TString era, const UChar_t JESVariation, const UChar_t JEStype) : m_JESVariation{JESVariation}, m_JESSysUncerType{JEStype}, m_era{era} {
    std::cout<<"Initialzing JESVariation........\n";
    TString jsonBase = "../../jsonpog-integration/POG/";
    cset_jerSF = correction::CorrectionSet::from_file((jsonBase + TTTT::json_map.at(m_era).at(0)).Data());
    std::cout<<"JEC sf file: "<<(jsonBase + TTTT::json_map.at(m_era).at(0)).Data()<<"\n";

    std::map<TString, TString> m_JESMap = {
        {"2018", "Summer19UL18_V5_MC_"},
        {"2017", "Summer19UL17_V5_MC_"},
        {"2016preVFP", "Summer19UL16APV_V7_MC_"},
        {"2016postVFP", "Summer19UL16_V7_MC_"},
    };
    m_JESTtring = m_JESMap.at(m_era)+ MV::JES_uncer.at(m_JESVariation);
    std::cout<<"JES string: "<<m_JESTtring<<"\n";
    std::cout<<"!!!m_JESVariationType: "<<static_cast<int>(m_JESSysUncerType)<<"\n";

    std::cout<<"Done JESVariation initialization......\n";
}

// void JESVariation::applyJESVariation(std::vector<ROOT::Math::PtEtaPhiMVector>& particleVec){
void JESVariation::applyJESVariation(std::vector<ROOT::Math::PtEtaPhiMVector>& particleVec, std::vector<UInt_t>& removedIndices){
    if(m_JESSysUncerType==0){
        return;
    };

    removedIndices.clear(); 
    auto corr_jesUncer = cset_jerSF->at(m_JESTtring.Data());
    for(UInt_t i=0; i<particleVec.size(); i++){
        // auto corr_jesUncer = cset_jerSF->at(corr_Uncer_JES_map[m_era].at(m_JESSysUncerType).Data());
        Double_t JES_uncer = corr_jesUncer->evaluate({particleVec.at(i).Eta(), particleVec.at(i).Pt()}); // do you need the pt to be raw? no
        // std::cout << JES_uncer << " JES_uncerValue" << std::endl;
        switch (m_JESSysUncerType)
        {
        case 1:
            particleVec[i] = particleVec[i] * (1 + JES_uncer);
            break;
        case 2:
            particleVec[i] = particleVec[i] * (1 - JES_uncer);
            break;
        default:
            break;
        }

        //!do the jet pt cut after JES variation
        if(particleVec[i].Pt()<25.){
            removedIndices.push_back(i);
            particleVec.erase(particleVec.begin()+i);
            i--;// Decrement the index to account for the removed element
        }//explain: 

    }
};

void JESVariation::applyJESVariation(std::vector<ROOT::Math::PtEtaPhiMVector>& particleVec) {
    std::vector<UInt_t> dummyRemovedIndices;
    applyJESVariation(particleVec, dummyRemovedIndices);
}