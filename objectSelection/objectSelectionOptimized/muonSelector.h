#ifndef MUONSELECTOR_H
#define MUONSELECTOR_H

// #include <vector.h>

#include "eventReader_nano.h"

class osBase
{
public:
    osBase(TTree *outTree) : m_outTree{outTree}
    {
        std::cout << "Initializing muonSelector\n";
        m_outTree->Branch("Muon_pt_", &Muon_pt_);
        std::cout << "muonSelector initialization done\n";
    };
    ~osBase(){

    };
    // init(){

    // };
    void Select(const eventForNano *e, const Int_t type = 0)
    {
        clearBranch();
        for (UInt_t j = 0; j < e->Muon_pt.GetSize(); ++j)
        {
            if (!(e->Muon_pt.At(j) > 10))
                continue;
            if (!(fabs(e->Muon_eta.At(j)) < 2.4))
                continue;
            if (!(fabs(e->Muon_dz.At(j)) < 0.1))
                continue;
            if (!(fabs(e->Muon_dxy.At(j)) < 0.05))
                continue;
            // ID
            if (type == 0)
            {
                if (!e->Muon_looseId.At(j))
                    continue;
                if (!(int(e->Muon_miniIsoId.At(j)) >= 1))
                    //???do we need to int() the unsigned char here?
                    continue;
            }
            if (type == 1)
            {
                if (!e->Muon_mediumId.At(j))
                    continue;
                if (!(int(e->Muon_miniIsoId.At(j)) >= 1))
                    //???do we need to int() the unsigned char here?
                    continue;
                if (!(fabs(e->Muon_ip3d.At(j)) < 4))
                    continue;
                if (!(e->Muon_tightCharge.At(j) == 2))
                    continue;
            }
            if (type == 2)
            {
                if (!e->Muon_mediumId.At(j))
                    continue;
                if (!(int(e->Muon_miniIsoId.At(j)) >= 3))
                    continue;
                if (!(fabs(e->Muon_ip3d.At(j)) < 4))
                    continue;
                if (!(e->Muon_tightCharge.At(j) == 2))
                    continue;
            }

            Muon_pt_.push_back(e->Muon_pt.At(j));
        }
        // m_outTree->Fill();
    };
    void clearBranch()
    {
        Muon_pt_.clear();
    }
    // void

private:
    TTree *m_outTree;
    // output branches
    std::vector<Double_t> Muon_pt_;
    std::vector<Double_t> Muon_eta_;
    std::vector<Double_t> Muon_phi_;
    std::vector<Double_t> Muon_mass_;
};

#endif
