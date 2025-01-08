#ifndef TriggerScaleFactorCalculator_h
#define TriggerScaleFactorCalculator_h

#include <iostream>
#include <string>
#include <TFile.h>
#include <TH2D.h>


class TriggerScaleFactorCalculator {
public:
    TriggerScaleFactorCalculator(const std::string& filename);
    TriggerScaleFactorCalculator(const TString era){
        file_ = TFile::Open(sfMap[era]);
        hist_mm_ = (TH2D*)file_->Get("mm_trigeff");
        hist_me_ = (TH2D*)file_->Get("me_trigeff");
        hist_em_ = (TH2D*)file_->Get("em_trigeff");
        hist_ee_ = (TH2D*)file_->Get("ee_trigeff");
        std::cout << "TriggerScaleFactorCalculator: Using file " << sfMap[era] << std::endl;
    };
    ~TriggerScaleFactorCalculator();
    double getScaleFactor(const std::string& channel, double ptLeading, double ptSubleading);

private:
    TFile* file_;
    TH2D* hist_mm_;
    TH2D* hist_me_;
    TH2D* hist_em_;
    TH2D* hist_ee_;

    std::map<TString, TString> sfMap = {
        {"2018", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2018.root"},
        {"2017", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2017.root"},
        {"2016preVFP", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2016PreVFP.root"},
        {"2016postVFP", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2016PostVFP.root"}

    };
};




#endif