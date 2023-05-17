#ifndef MUONSELECTOR_H
#def MUONSELECTOR_H

#include "eventReader_nano.C"

class osBase
{
public:
    osBase(const eventForNano *e, TTree *outTree)
    {
        m_outTree->Branch("Muon_pt", &Muon_pt);
    };
    // output branches
    std::vector Muon_pt_;
    std::vector Muon_eta_;
    std::vector Muon_phi_;
    std::vector Muon_mass_;
    init(){

    };
    Select()
    {
        for (UInt_t j = 0; j < e->Muon_pt.GetSize(); ++j)
        {
            if (!(Muon_pt.At(j) > 10))
                continue;
        }
        m_outTree->Fill();
    };

private:
    TTree *m_outTree;
};

#endif
