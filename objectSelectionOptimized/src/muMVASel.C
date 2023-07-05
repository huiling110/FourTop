#include "../include/muMVASel.h"

MuSel::MuSel(TTree *outTree, const TString era, const Int_t m_type) : m_type{m_type}
{ // m_type for different electrons
    std::cout << "Initializing MuSel......\n";
    outTree->Branch("muonsT_pt", &muonsTopMVAT_pt);
    outTree->Branch("muonsT_eta", &muonsTopMVAT_eta);
    outTree->Branch("muonsT_phi", &muonsTopMVAT_phi);
    outTree->Branch("muonsT_mass", &muonsTopMVAT_mass);
    outTree->Branch("muonsT_index", &muonsTopMVAT_index);
    // outTree->Branch("muonsTopMVAT_", &muonsTopMVAT_);

    std::cout << "Done MuSel initialization......\n";
    std::cout << "\n";
};

MuSel::~MuSel()
{
};

void MuSel::Select(const eventForNano *e)
{
    clearBranch();
    // changed ISO to ss of TTTT
    // 0 for Loose; 1 fakeble; 2 tight
    for (UInt_t j = 0; j < e->Muon_pt.GetSize(); ++j)
    {
        // in objectSelection.h e->Muon_pt_ is global variable

        if (!(e->Muon_pt.At(j) > 10))
            continue;
        if (!(fabs(e->Muon_eta.At(j)) < 2.4))
            continue;
        if (!(fabs(e->Muon_dz.At(j)) < 0.1))
            continue;
        if (!(fabs(e->Muon_dxy.At(j)) < 0.05))
            continue;
        // ID
        if (m_type == 0)
        {
            if (!e->Muon_looseId.At(j))
                continue;
            if (!(int(e->Muon_miniIsoId.At(j)) >= 1))
                //???do we need to int() the unsigned char here?
                continue;
        }
        if (m_type == 1)
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
        if (m_type == 2)
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
        muonsTopMVAT_pt.push_back(e->Muon_pt.At(j));
        muonsTopMVAT_eta.push_back(e->Muon_eta.At(j));
        muonsTopMVAT_phi.push_back(e->Muon_phi.At(j));
        muonsTopMVAT_mass.push_back(e->Muon_mass.At(j));
        muonsTopMVAT_index.push_back(j);
    }
    m_muTotal+=muonsTopMVAT_pt.size();
};

void MuSel::clearBranch()
{
    muonsTopMVAT_pt.clear();
    muonsTopMVAT_eta.clear();
    muonsTopMVAT_phi.clear();
    muonsTopMVAT_mass.clear();
    muonsTopMVAT_index.clear();
};

std::vector<Double_t> &MuSel::getEtaVec()
{
    return muonsTopMVAT_eta;
};
std::vector<Double_t> &MuSel::getPhiVec()
{
    return muonsTopMVAT_phi;
};

ULong_t MuSel::getTotal(){
    return m_muTotal;
}