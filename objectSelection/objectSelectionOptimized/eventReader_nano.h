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
                                        Muon_tightCharge(reader, "Muon_tightCharge"),

                                        HLT_PFHT450_SixJet40_BTagCSV_p056(reader, "HLT_PFHT450_SixJet40_BTagCSV_p056")
    {
    }

    // eventForNano(TTreeReader &reader)
    // {
    //     nElectron = new TTreeReaderValue<UInt_t>(reader, "nElectron");
    //     //!!! the pointer initialization is okay but too lengthy to access
    // }

    ~eventForNano(){
        // delete m_reader;
    };

    // TTreeReader m_reader;
    //???how to solve the challange that some branches only exist in some files?
    // TTreeReaderValue<UInt_t> nElectron = {m_reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work
    // TTreeReaderValue<UInt_t> *nElectron;
    TTreeReaderValue<UInt_t> nElectron;
    //???can TTreeReaderValue<> be decalred but not initialized?
    // TTreeReaderArray<Float_t> Electron_dxy;//must be initialized when definiing!

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
    TTreeReaderValue<Bool_t> HLT_PFHT450_SixJet40_BTagCSV_p056;
};

#endif