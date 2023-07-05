#include "../include/eleMVASel.h"

EleMVASel::EleMVASel(TTree *outTree, const TString era, const Int_t type) : m_type{type}, m_era{era}
{ // m_type for different electrons
    std::cout << "Initializing EleMVASel......\n";
    outTree->Branch("elesMVAT_pt", &muonsTopMVAT_pt);
    outTree->Branch("elesMVAT_eta", &muonsTopMVAT_eta);
    outTree->Branch("elesMVAT_phi", &muonsTopMVAT_phi);
    outTree->Branch("elesMVAT_mass", &muonsTopMVAT_mass);
    outTree->Branch("elesMVAT_index", &muonsTopMVAT_index);
    // outTree->Branch("muonsTopMVAT_", &muonsTopMVAT_);

    std::cout << "Done EleMVASel initialization......\n\n";
};

EleMVASel::~EleMVASel()
{
};

void EleMVASel::Select(const eventForNano *e)
{
    clearBranch();
    // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
    // 2016 - MVANoIso94XV2, from SUSY
    for (UInt_t j = 0; j < e->Electron_pt.GetSize(); ++j)
    { 
        Double_t pt = e->Electron_pt.At(j);
        Double_t eta = e->Electron_eta.At(j);
        if (!(fabs(eta) < 2.5))
            continue;
        if (!(pt > 10))
            continue;
        Bool_t mvaIso;
        if(m_era.CompareTo("2022")==0){
          mvaIso = e->Electron_mvaIso_Fall17V2_WP90->At(j);
        }else{
          mvaIso = e->Electron_mvaFall17V2Iso_WP90->At(j);
        }
        // if (!e->Electron_mvaFall17V2Iso_WP90.At(j))//run2
        if (!mvaIso)//???  2022: Electron_mvaIso_Fall17V2_WP90
            continue; // note: after switching from SUSY ID to EGamma ID, there's no difference in ID between loose, fakeable and tight electrons
        // note bis: use *Iso* MVA discriminator, it comes from a MVA method trained with iso variables as input features. A WP on this discriminator implies ISO requirements
        if (!e->Electron_convVeto.At(j))
            continue;
        // the number of missing pixel hits and a conversion veto based on the vertex fit probability. To reject electrons originating from photon conversion

        // IP
        if (!(fabs(e->Electron_dxy.At(j)) < 0.05))
            continue;
        if (!(fabs(e->Electron_dz.At(j)) < 0.1))
            continue;
        if (m_type == 0)
        {
            if (!(int(e->Electron_lostHits.At(j)) <= 1))
                continue;
        }
        if (m_type == 1 || m_type == 2)
        {
            if (!(int(e->Electron_lostHits.At(j)) == 0))
                continue;
            if (!((e->Electron_ip3d.At(j)) < 4))
                continue;
        }
        muonsTopMVAT_pt.push_back(e->Electron_pt.At(j));
        muonsTopMVAT_eta.push_back(e->Electron_eta.At(j));
        muonsTopMVAT_phi.push_back(e->Electron_phi.At(j));
        muonsTopMVAT_mass.push_back(e->Electron_mass.At(j));
        muonsTopMVAT_index.push_back(j);
    }
    m_objTotal+=muonsTopMVAT_pt.size();
};

void EleMVASel::clearBranch()
{
    muonsTopMVAT_pt.clear();
    muonsTopMVAT_eta.clear();
    muonsTopMVAT_phi.clear();
    muonsTopMVAT_mass.clear();
    muonsTopMVAT_index.clear();
};

std::vector<Double_t> &EleMVASel::getEtaVec()
{
    return muonsTopMVAT_eta;
};
std::vector<Double_t> &EleMVASel::getPhiVec()
{
    return muonsTopMVAT_phi;
};

ULong_t EleMVASel::getTotal(){
    return m_objTotal;
}