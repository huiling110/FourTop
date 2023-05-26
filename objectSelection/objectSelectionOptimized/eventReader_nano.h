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
                                        Muon_pt(reader, "Muon_pt")
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
    // TTreeReaderArray<Float_t> Moun_eta;
    // TTreeReaderArray<Float_t> Moun_dz;
    // TTreeReaderArray<Float_t> Moun_dxy;
    // TTreeReaderArray<Float_t> Moun_looseId;
    // TTreeReaderArray<Float_t> Moun_miniIsoId;
    // TTreeReaderArray<Float_t> Moun_mediumId;
    // TTreeReaderArray<Float_t> Moun_ip3d;
    // TTreeReaderArray<Float_t> Moun_tightCharge;
};

#endif