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
                                      tausL_genPartFlav(reader, "tausL_genPartFlav")

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
};

#endif