#include "../include/eleMVASel.h"

EleMVASel::EleMVASel(TTree *outTree, const TString era, Bool_t isRun3,const Int_t type) : m_type{type}, m_era{era}, m_isRun3{isRun3}
{ // m_type for different electrons
    std::cout << "Initializing EleMVASel......\n";
    std::cout << "m_era=" << m_era << " m_isRun3=" << m_isRun3 << " m_type=" << m_type << "\n";

    std::map<Int_t, TString> typeMap = {
        {0, "L"},
        {1, "F"},
        {2, "T"},
        {3, "TRun3"},
    };

    outTree->Branch("elesMVA"+typeMap.at(m_type)+"_pt", &muonsTopMVAT_pt);
    outTree->Branch("elesMVA"+typeMap.at(m_type)+"_eta", &muonsTopMVAT_eta);
    outTree->Branch("elesMVA"+typeMap.at(m_type)+"_phi", &muonsTopMVAT_phi);
    outTree->Branch("elesMVA"+typeMap.at(m_type)+"_mass", &muonsTopMVAT_mass);
    outTree->Branch("elesMVA"+typeMap.at(m_type)+"_index", &muonsTopMVAT_index);

    //
    TString jsonBase = "../../jsonpog-integration/POG/";
    cset_eleScale = correction::CorrectionSet::from_file((jsonBase + json_map[era].at(0)).Data());
    std::cout<<"electron scale and smearing files: "<<jsonBase + json_map[era].at(0)<<"\n";

    std::cout << "Done EleMVASel initialization......\n\n";
};

EleMVASel::~EleMVASel()
{
};

// Double_t getEleScale();

void EleMVASel::Select(const eventForNano *e)
{
    if(m_entry==0){
        std::cout << "running EleMVASel::Select()\n";
    }
    clearBranch();
    // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
    // 2016 - MVANoIso94XV2, from SUSY
    for (UInt_t j = 0; j < e->Electron_pt.GetSize(); ++j)
    {
        // Double_t eleScale = getEleScale();
        Double_t pt = e->Electron_pt.At(j);
        Double_t eta = e->Electron_eta.At(j);
        if (!(fabs(eta) < 2.5))
            continue;
        if (!(pt > 10))
            continue;
        Bool_t mvaIso = kFALSE;
        if(m_isRun3){
            // mvaIso = e->Electron_mvaIso_Fall17V2_WP90->At(j);
            mvaIso = e->Electron_mvaIso_WP90->At(j); //!!!
        }else{
            mvaIso = e->Electron_mvaFall17V2Iso_WP90->At(j);
        }
        if (!mvaIso)//???  2022: Electron_mvaIso_Fall17V2_WP90
            continue; // note: after switching from SUSY ID to EGamma ID, there's no difference in ID between loose, fakeable and tight electrons
        // note bis: use *Iso* MVA discriminator, it comes from a MVA method trained with iso variables as input features. A WP on this discriminator implies ISO requirements
        // if (!e->Electron_convVeto.At(j))//!!!
            // continue;
        // the number of missing pixel hits and a conversion veto based on the vertex fit probability. To reject electrons originating from photon conversion

        // IP//!!!comment for run3
        // if (!(fabs(e->Electron_dxy.At(j)) < 0.05))
        //     continue;
        // if (!(fabs(e->Electron_dz.At(j)) < 0.1))
        //     continue;
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

    m_entry ++ ;
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