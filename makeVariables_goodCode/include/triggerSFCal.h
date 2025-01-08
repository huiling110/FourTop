#ifndef TriggerScaleFactorCalculator_h
#define TriggerScaleFactorCalculator_h

#include <iostream>
#include <string>
#include <TFile.h>
#include <TH2D.h>


class TriggerScaleFactorCalculator {
public:
    // TriggerScaleFactorCalculator(const std::string& filename);
    TriggerScaleFactorCalculator(const TString era){
        std::map<TString, TString> sfMap = {
            {"2018", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2018.root"},
            {"2017", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2017.root"},
            {"2016preVFP", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2016PreVFP.root"},
            {"2016postVFP", "../inputFiles/lepTriggerSF_fromSS/scalefactors_2016PostVFP.root"}
        };
        file_ = TFile::Open(sfMap[era]);
        if(!file_){
            std::cerr << "TriggerScaleFactorCalculator: File " << sfMap[era] << " not found!" << std::endl;
            exit(1);
        } 
        //if era = 2016preVFP or 2016postVFP, change era to 2016PostVFP and 2016PreVFP when accessing the histograms
        TString era_ = era;
        if(era == "2016preVFP") era_ = "2016PreVFP";
        if(era == "2016postVFP") era_ = "2016PostVFP"; 
        hist_mm_ = (TH2D*)file_->Get("scalefactors_"+era_+"_mm");
        hist_me_ = (TH2D*)file_->Get("scalefactors_"+era_+"_me");
        hist_em_ = (TH2D*)file_->Get("scalefactors_"+era_+"_em");
        hist_ee_ = (TH2D*)file_->Get("scalefactors_"+era_+"_ee");
        if(!hist_mm_ || !hist_me_ || !hist_em_ || !hist_ee_){
            std::cerr << "TriggerScaleFactorCalculator: Histograms not found in file " << sfMap[era] << std::endl;
            exit(1);
        }


        std::cout << "TriggerScaleFactorCalculator: Using file " << sfMap[era] << std::endl;
    };
    ~TriggerScaleFactorCalculator();
    double getScaleFactor(const std::string& channel, double ptLeading, double ptSubleading, const Bool_t isData=kFALSE, const UChar_t sysType=0);

private:
    TFile* file_;
    TH2D* hist_mm_;
    TH2D* hist_me_;
    TH2D* hist_em_;
    TH2D* hist_ee_;

};




#endif