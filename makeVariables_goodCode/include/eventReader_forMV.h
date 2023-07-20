#ifndef EVENTREADDER_FORMV_H
#define EVENTREADDER_FORMV_H

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

class EventForMV
{
public:
    EventForMV(TTreeReader &reader) : // HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_(reader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_"),
                                      //   HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_(reader, "HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_")
                                      muonsT_pt(reader, "muonsT_pt"),
                                      muonsT_eta(reader, "muonsT_eta"),
                                      muonsT_phi(reader, "muonsT_phi"),
                                      muonsT_mass(reader, "muonsT_mass"),
                                      muonsTopMVAT_pt(reader, "muonsTopMVAT_pt"),
                                      muonsTopMVAT_eta(reader, "muonsTopMVAT_eta"),
                                      muonsTopMVAT_phi(reader, "muonsTopMVAT_phi"),
                                      muonsTopMVAT_mass(reader, "muonsTopMVAT_mass"),
                                      elesMVAT_pt(reader, "elesMVAT_pt"),
                                      elesMVAT_eta(reader, "elesMVAT_eta"),
                                      elesMVAT_phi(reader, "elesMVAT_phi"),
                                      elesMVAT_mass(reader, "elesMVAT_mass"),
                                      elesTopMVAT_pt(reader, "elesTopMVAT_pt"),
                                      elesTopMVAT_eta(reader, "elesTopMVAT_eta"),
                                      elesTopMVAT_phi(reader, "elesTopMVAT_phi"),
                                      elesTopMVAT_mass(reader, "elesTopMVAT_mass"),

                                      tausT_pt(reader, "tausT_pt"),
                                      tausT_eta(reader, "tausT_eta"),
                                      tausT_phi(reader, "tausT_phi"),
                                      tausT_mass(reader, "tausT_mass"),
                                      tausT_genPartFlav(reader, "tausT_genPartFlav"),
                                      tausF_pt(reader, "tausF_pt"),
                                      tausF_eta(reader, "tausF_eta"),
                                      tausF_phi(reader, "tausF_phi"),
                                      tausF_mass(reader, "tausF_mass"),
                                      tausF_genPartFlav(reader, "tausF_genPartFlav"),
                                      tausL_pt(reader, "tausL_pt"),
                                      tausL_eta(reader, "tausL_eta"),
                                      tausL_phi(reader, "tausL_phi"),
                                      tausL_mass(reader, "tausL_mass"),
                                      tausL_genPartFlav(reader, "tausL_genPartFlav"),

                                      jets_pt(reader, "jets_pt"),
                                      jets_eta(reader, "jets_eta"),
                                      jets_phi(reader, "jets_phi"),
                                      jets_mass(reader, "jets_mass"),
                                      jets_btags(reader, "jets_btags"),
                                      jets_flavour(reader, "jets_flavour"),
                                      jetsT_pt(reader, "jetsT_pt"),
                                      jetsT_eta(reader, "jetsT_eta"),
                                      jetsT_phi(reader, "jetsT_phi"),
                                      jetsT_mass(reader, "jetsT_mass"),
                                      jetsT_btags(reader, "jetsT_btags"),
                                      bjetsM_pt(reader, "bjetsM_pt"),
                                      bjetsM_eta(reader, "bjetsM_eta"),
                                      bjetsM_phi(reader, "bjetsM_phi"),
                                      bjetsM_mass(reader, "bjetsM_mass"),
                                      bjetsL_pt(reader, "bjetsL_pt"),
                                      bjetsL_eta(reader, "bjetsL_eta"),
                                      bjetsL_phi(reader, "bjetsL_phi"),
                                      bjetsL_mass(reader, "bjetsL_mass"),
                                      bjetsT_pt(reader, "bjetsT_pt"),
                                      bjetsT_eta(reader, "bjetsT_eta"),
                                      bjetsT_phi(reader, "bjetsT_phi"),
                                      bjetsT_mass(reader, "bjetsT_mass"),

                                      PV_npvsGood_(reader, "PV_npvsGood_"),
                                      EVENT_genWeight_(reader, "EVENT_genWeight_"),
                                      EVENT_prefireWeight_(reader, "EVENT_prefireWeight_")


    {
        std::cout << "Initializing EventForMV..\n";
        std::cout << "Done initialization.......\n";
        std::cout << "\n";
    };

    ~EventForMV(){};

    // event branches reading
    // TTreeReaderValue<Bool_t> HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_;//!!!add in OS
    // TTreeReaderValue<Bool_t> HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_;
    TTreeReaderArray<Double_t> muonsT_pt;
    TTreeReaderArray<Double_t> muonsT_eta;
    TTreeReaderArray<Double_t> muonsT_phi;
    TTreeReaderArray<Double_t> muonsT_mass;
    TTreeReaderArray<Double_t> muonsTopMVAT_pt;
    TTreeReaderArray<Double_t> muonsTopMVAT_eta;
    TTreeReaderArray<Double_t> muonsTopMVAT_phi;
    TTreeReaderArray<Double_t> muonsTopMVAT_mass;
    TTreeReaderArray<Double_t> elesMVAT_pt;
    TTreeReaderArray<Double_t> elesMVAT_eta;
    TTreeReaderArray<Double_t> elesMVAT_phi;
    TTreeReaderArray<Double_t> elesMVAT_mass;
    TTreeReaderArray<Double_t> elesTopMVAT_pt;
    TTreeReaderArray<Double_t> elesTopMVAT_eta;
    TTreeReaderArray<Double_t> elesTopMVAT_phi;
    TTreeReaderArray<Double_t> elesTopMVAT_mass;

    TTreeReaderArray<Double_t> tausT_pt;
    TTreeReaderArray<Double_t> tausT_eta;
    TTreeReaderArray<Double_t> tausT_phi;
    TTreeReaderArray<Double_t> tausT_mass;
    TTreeReaderArray<UChar_t> tausT_genPartFlav;
    TTreeReaderArray<Double_t> tausF_pt;
    TTreeReaderArray<Double_t> tausF_eta;
    TTreeReaderArray<Double_t> tausF_phi;
    TTreeReaderArray<Double_t> tausF_mass;
    TTreeReaderArray<UChar_t> tausF_genPartFlav;
    TTreeReaderArray<Double_t> tausL_pt;
    TTreeReaderArray<Double_t> tausL_eta;
    TTreeReaderArray<Double_t> tausL_phi;
    TTreeReaderArray<Double_t> tausL_mass;
    TTreeReaderArray<UChar_t> tausL_genPartFlav;

    TTreeReaderArray<Double_t> jets_pt;
    TTreeReaderArray<Double_t> jets_eta;
    TTreeReaderArray<Double_t> jets_phi;
    TTreeReaderArray<Double_t> jets_mass;
    TTreeReaderArray<Double_t> jets_btags;
    TTreeReaderArray<Int_t> jets_flavour;
    TTreeReaderArray<Double_t> jetsT_pt;
    TTreeReaderArray<Double_t> jetsT_eta;
    TTreeReaderArray<Double_t> jetsT_phi;
    TTreeReaderArray<Double_t> jetsT_mass;
    TTreeReaderArray<Double_t> jetsT_btags;
    TTreeReaderArray<Double_t> bjetsM_pt;
    TTreeReaderArray<Double_t> bjetsM_eta;
    TTreeReaderArray<Double_t> bjetsM_phi;
    TTreeReaderArray<Double_t> bjetsM_mass;
    TTreeReaderArray<Double_t> bjetsL_pt;
    TTreeReaderArray<Double_t> bjetsL_eta;
    TTreeReaderArray<Double_t> bjetsL_phi;
    TTreeReaderArray<Double_t> bjetsL_mass;
    TTreeReaderArray<Double_t> bjetsT_pt;
    TTreeReaderArray<Double_t> bjetsT_eta;
    TTreeReaderArray<Double_t> bjetsT_phi;
    TTreeReaderArray<Double_t> bjetsT_mass;

    TTreeReaderValue<Int_t> PV_npvsGood_;

    TTreeReaderValue<Double_t> EVENT_genWeight_;
    TTreeReaderValue<Double_t> EVENT_prefireWeight_;
    // TTreeReaderValue<Double_t> ;
};

#endif