#ifndef EVENTREADER_NANO_H
#define EVENTREADER_NANO_H

// #include <vector>
class eventForNano
{
public:
    // eventForNano(TTreeReader reader) : nElectron{reader, "nElectron"}
    // eventForNano(TTreeReader *reader)
    // eventForNano(TTreeReader reader) : m_reader{reader}
    eventForNano(TTreeReader &reader) : nElectron(reader, "nElectron")
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
    // TTreeReaderArray<Float_t> Electron_dxy;
    /*
    std::vector<Float_t> Electron_dxyErr = {m_reader, "Electron_dxyErr"};
    std::vector<Float_t> Electron_dz = {m_reader, "Electron_dz"};
    */
};

#endif