
#ifndef EVENTREADER_NANO_H
#define EVENTREADER_NANO_H

// #include <vector>
class eventForNano
{
public:
    // eventForNano(TTreeReader reader) : nElectron{reader, "nElectron"}
    // eventForNano(TTreeReader *reader)
    eventForNano(TTreeReader reader) : m_reader{reader}
    {
        // m_reader = reader;
        // m_reader = new TTreeReader(tree);
        // nElectron = {reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work
        // nElectron = {reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work

        // Electron_dxy = (m_reader, "Electron_dxy");
    }
    ~eventForNano(){
        // delete m_reader;
    };

    // public:
    TTreeReader m_reader;
    //???how to solve the challange that some branches only exist in some files?
    TTreeReaderValue<UInt_t> nElectron = {m_reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work
    //???can TTreeReaderValue<> be decalred but not initialized?
    // TTreeReaderArray<Float_t> Electron_dxy;
    /*
    std::vector<Float_t> Electron_dxyErr = {m_reader, "Electron_dxyErr"};
    std::vector<Float_t> Electron_dz = {m_reader, "Electron_dz"};
    */
    // private:
    //     TTree *m_tree;
};

#endif