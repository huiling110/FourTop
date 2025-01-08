#include "../include/triggerSFCal.h"

TriggerScaleFactorCalculator::TriggerScaleFactorCalculator(const std::string& filename) {
    file_ = TFile::Open(filename.c_str(), "READ");

    if (!file_ || file_->IsZombie()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    hist_mm_ = dynamic_cast<TH2D*>(file_->Get("scalefactors_2018_mm"));
    hist_me_ = dynamic_cast<TH2D*>(file_->Get("scalefactors_2018_me"));
    hist_em_ = dynamic_cast<TH2D*>(file_->Get("scalefactors_2018_em"));
    hist_ee_ = dynamic_cast<TH2D*>(file_->Get("scalefactors_2018_ee"));
}

TriggerScaleFactorCalculator::~TriggerScaleFactorCalculator() {
    if (file_) {
        file_->Close();
        delete file_;
    }
}

double TriggerScaleFactorCalculator::getScaleFactor(const std::string& channel, double ptLeading, double ptSubleading) {
    TH2D* hist = nullptr;

    if (channel == "mm") hist = hist_mm_;
    else if (channel == "me") hist = hist_me_;
    else if (channel == "em") hist = hist_em_;
    else if (channel == "ee") hist = hist_ee_;
    else {
        std::cerr << "Error: Invalid channel specified (must be 'mm', 'me', 'em', or 'ee')." << std::endl;
        return 1.0;
    }

    if (!hist) {
        std::cerr << "Error: Histogram for channel " << channel << " is not loaded." << std::endl;
        return 1.0;
    }

    // Find the corresponding bin
    int binX = hist->GetXaxis()->FindBin(ptLeading);
    int binY = hist->GetYaxis()->FindBin(ptSubleading);

    // Check if bin exists
    if (binX <= 0 || binY <= 0 || binX > hist->GetNbinsX() || binY > hist->GetNbinsY()) {
        std::cerr << "Warning: pt values are out of histogram range." << std::endl;
        return 1.0;
    }

    // Retrieve the scale factor
    return hist->GetBinContent(binX, binY);
}
