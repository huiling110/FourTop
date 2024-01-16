#include "../include/muMVASel.h"

MuSel::MuSel(TTree *outTree, const TString era, const Bool_t isRun3, const Int_t m_type) : m_era{era}, m_isRun3{isRun3}, m_type{m_type}
{ // m_type for different electrons
    std::cout << "Initializing MuSel......\n";
    std::cout<<"m_era="<<m_era<<"; m_isRun3="<<m_isRun3<<"\n";
    std::cout << "m_type=" << m_type << "\n";

    std::map<Int_t, TString> muonMap = {
        {0, "L"},
        {1, "F"},
        {2, "T"},//!!!maybe I want to keep the same name for run 2 and run 3
        {3, "TRun3"},
    };

    outTree->Branch("muons" + muonMap.at(m_type)+"_pt", &muonsTopMVAT_pt);
    outTree->Branch("muons" + muonMap.at(m_type)+"_eta", &muonsTopMVAT_eta);
    outTree->Branch("muons" + muonMap.at(m_type)+"_phi", &muonsTopMVAT_phi);
    outTree->Branch("muons" + muonMap.at(m_type)+"_mass", &muonsTopMVAT_mass);
    outTree->Branch("muons" + muonMap.at(m_type)+"_index", &muonsTopMVAT_index);
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
        Int_t iMu_tightCharge = 0;
        if(m_isRun3){
            iMu_tightCharge = std::any_cast<UChar_t>(e->Muon_tightCharge.at(j));
        }else{
            iMu_tightCharge = std::any_cast<Int_t>(e->Muon_tightCharge.at(j));
        }

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
            // if (!(e->Muon_tightCharge.At(j) == 2))//!!!
            if (!(iMu_tightCharge == 2))
                continue;
        }
        if (m_type == 2)
        {
            if(!m_isRun3){
                if (!e->Muon_mediumId.At(j)) //!!!maybe switch to tightId
                    continue;
                if (!(int(e->Muon_miniIsoId.At(j)) >= 3))
                    continue;
                if (!(fabs(e->Muon_ip3d.At(j)) < 4))
                    continue;
                if (!(iMu_tightCharge == 2))
                    continue;
            }else{
                if (!e->Muon_tightId.At(j))
                    continue;
                if (!(int(e->Muon_miniIsoId.At(j)) >= 3))//MiniIso ID from miniAOD selector (1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight)
                    continue;
            }
        }
        // if(m_type == 3){//!!! for run3
        //     if (!e->Muon_tightId.At(j))
        //         continue;
        //     if (!(int(e->Muon_miniIsoId.At(j)) >= 3))//MiniIso ID from miniAOD selector (1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight)
        //         continue;
        // }
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