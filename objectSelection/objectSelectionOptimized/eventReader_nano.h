#ifndef EVENTREADER_NANO_H
#define EVENTREADER_NANO_H

// #include <vector>
class eventForNano
{
public:
    // eventForNano(TTreeReader reader) : nElectron{reader, "nElectron"}
    // eventForNano(TTreeReader *reader)
    // eventForNano(TTreeReader reader) : m_reader{reader}
    eventForNano(TTreeReader &reader) : nElectron(reader, "nElectron"),
                                        Muon_pt(reader, "Muon_pt"),
                                        Muon_eta(reader, "Muon_eta"),
                                        Muon_dz(reader, "Muon_dz"),
                                        Muon_dxy(reader, "Muon_dxy"),
                                        Muon_looseId(reader, "Muon_looseId"),
                                        Muon_miniIsoId(reader, "Muon_miniIsoId"),
                                        Muon_mediumId(reader, "Muon_mediumId"),
                                        Muon_ip3d(reader, "Muon_ip3d"),
                                        Muon_tightCharge(reader, "Muon_tightCharge")

    // HLT_PFHT450_SixJet40_BTagCSV_p056(reader, "HLT_PFHT450_SixJet40_BTagCSV_p056")
    {
        // dealing with case: HLT branch not existing in this nanofile;
        // assing the reader branch 0 if the branch not existing
        // it seems to reader can not run at all if assosiated with not existing branch
        // if (!(HLT_PFHT450_SixJet40_BTagCSV_p056.IsValid()))
        // {
        //     std::cout << "branch not existing in input\n ";
        // }
        readPointer(HLT_PFHT450_SixJet40_BTagCSV_p056, reader, "HLT_PFHT450_SixJet40_BTagCSV_p056");
        readPointer(HLT_PFHT400_SixJet30_DoubleBTagCSV_p056, reader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056");
        readPointer(HLT_PFJet450, reader, "HLT_PFJet450");

        readPointer(HLT_PFJet500, reader, "HLT_PFJet500");
        readPointer(HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94, reader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94");
        readPointer(HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59, reader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59");
        readPointer(HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2, reader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2");
        readPointer(HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5, reader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5");
        readPointer(HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5, reader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5");
    };

    // eventForNano(TTreeReader &reader)
    // {
    //     nElectron = new TTreeReaderValue<UInt_t>(reader, "nElectron");
    //     //!!! the pointer initialization is okay but too lengthy to access

    // }

    ~eventForNano()
    {
        // delete m_reader;
        delete HLT_PFHT450_SixJet40_BTagCSV_p056;
    };

    void readPointer(TTreeReaderValue<Bool_t> *&branchPointer, TTreeReader &reader, TString branchName)
    {
        // if (reader.GetTree()->FindBranch("HLT_PFHT450_SixJet40_BTagCSV_p056"))
        if (reader.GetTree()->FindBranch(branchName))
        {
            // HLT_PFHT450_SixJet40_BTagCSV_p056 = new TTreeReaderValue<Bool_t>(reader, "HLT_PFHT450_SixJet40_BTagCSV_p056");
            branchPointer = new TTreeReaderValue<Bool_t>(reader, branchName);
        }
        else
        {
            std::cout << "WARNINIG!!! " << branchName << " not exsit in input nano file\n";
        };
    }
    // TTreeReader m_reader;
    //???how to solve the challange that some branches only exist in some files?
    // TTreeReaderValue<UInt_t> nElectron = {m_reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work
    TTreeReaderValue<UInt_t> nElectron;

    TTreeReaderArray<Float_t> Muon_pt;
    TTreeReaderArray<Float_t> Muon_eta;
    TTreeReaderArray<Float_t> Muon_dz;
    TTreeReaderArray<Float_t> Muon_dxy;
    TTreeReaderArray<Bool_t> Muon_looseId;
    TTreeReaderArray<UChar_t> Muon_miniIsoId;
    TTreeReaderArray<Bool_t> Muon_mediumId;
    TTreeReaderArray<Float_t> Muon_ip3d;
    TTreeReaderArray<Int_t> Muon_tightCharge;

    // HLT reading: tricky!!!
    // for some files the trigger not present, trigger branch not exsit
    // for some files cross the run range of trigger validity, trigger branch exsit but the subset invalid range is set to 0. need to further check this through
    // 2016 trigger
    // TTreeReaderValue<Bool_t> HLT_PFHT450_SixJet40_BTagCSV_p056;
    TTreeReaderValue<Bool_t> *HLT_PFHT450_SixJet40_BTagCSV_p056 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFJet450 = nullptr;
    // TTreeReaderValue<Bool_t> * = nullptr;
    // 2018
    TTreeReaderValue<Bool_t> *HLT_PFJet500 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = nullptr;
    // TRIGGERS FOR 2018 data A
    TTreeReaderValue<Bool_t> *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = nullptr;
    // 2018 for only some small slices of 2018 A (CSV b tag instead of DeepCSV btag)
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = nullptr;
    // TTreeReaderValue<Bool_t> *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = nullptr;
};

#endif