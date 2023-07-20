#ifndef INPUTMAP_MV_H
#define INPUTMAP_MV_H

namespace MV{


// top lepton mva
inline const std::map<TString, std::array<TString, 2>> topLeptonSF_files = {
    {"2016preVFP", {"./input/topMVASF/ele/2016APV/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2016HIPM/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
    {"2016postVFP", {"./input/topMVASF/ele/2016/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2016/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
    {"2017", {"./input/topMVASF/ele/2017/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2017/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
    {"2018", {"./input/topMVASF/ele/2018/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
};

};
#endif