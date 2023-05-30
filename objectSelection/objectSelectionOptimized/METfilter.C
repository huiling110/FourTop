#include "METfilter.h"

METFilter::METFilter(){
    std::cout<<"initialize METFilter ......\n";
}


Bool_t METFilter::Select(const TString era, eventForNano *e){
        // recommendations from here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#MET_Filter_Recommendations_for_R
    Bool_t isPass =    *e->Flag_goodVertices && *e->Flag_globalSuperTightHalo2016Filter && *e->Flag_HBHENoiseFilter && *e->Flag_HBHENoiseIsoFilter && *e->Flag_EcalDeadCellTriggerPrimitiveFilter && *e->Flag_BadPFMuonFilter && *e->Flag_BadPFMuonDzFilter && *e->Flag_eeBadScFilter;
    if (era.CompareTo("2017") == 0 || era.CompareTo("2018") == 0)
    {
        isPass = *e->Flag_ecalBadCalibFilter&&isPass;
    }
    return isPass;

}