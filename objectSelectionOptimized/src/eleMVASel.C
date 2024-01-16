#include "../include/eleMVASel.h"

EleMVASel::EleMVASel(TTree *outTree, const TString era, const Bool_t isData, Bool_t isRun3,const Int_t type, const UChar_t sysScale, const UChar_t sysSmear) : m_type{type}, m_era{era}, m_isData{isData},m_isRun3{isRun3}, m_Sys_scale{sysScale}, m_Sys_smear{sysSmear}
{ // m_type for different electrons
    std::cout << "Initializing EleMVASel......\n";
    std::cout << "m_era=" << m_era << " m_isRun3=" << m_isRun3 << " m_type=" << m_type << " m_Sys_scale=" << static_cast<unsigned int>(m_Sys_scale) << " m_Sys_smear=" << static_cast<unsigned int>(m_Sys_smear) << "\n";

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
    cset_eleScale = correction::CorrectionSet::from_file((jsonBase + eleScaleSmear.at(m_era).at(0)).Data());
    std::cout<<"electron scale and smearing files: "<<jsonBase + eleScaleSmear.at(m_era).at(0)<<"\n";
    for (auto const& corr : *cset_eleScale) {
        std::cout << "eleScale: " << corr.first << "\n";
    }

    std::cout << "Done EleMVASel initialization......\n\n";
};

EleMVASel::~EleMVASel()
{
};

Double_t EleMVASel::getEleScale(UChar_t gain, UInt_t run, Double_t eta, Double_t r9, Double_t et , Bool_t isScale){
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammSFandSSRun3#Scale_And_Smearings_Example
    if(!m_isRun3 ||m_isData){
        return 1.0;
    }else{
        Double_t sf = 1.0;
        Double_t uncer = 0.0;
        UChar_t sysScale = 0;
        if (isScale)
        {//!!!data
            auto corr_eleScale = cset_eleScale->at(eleScaleSmear.at(m_era).at(1).Data());//!!!no need to call for every electron
            // auto corr_eleSmear = cset_eleScale->at(eleScaleSmear.at(m_era).at(2).Data());
            //scale: gain, run,eta,r9,et//can use pt for et
            //smearring: gain, eta,r9
            sf = corr_eleScale->evaluate({"total_correction", gain, static_cast<Float_t>(run), eta, r9, et});
            uncer = corr_eleScale->evaluate({"total_uncertainty", gain, static_cast<Float_t>(run), eta, r9, et});
            sysScale = m_Sys_scale;
        }
        else
        {
            auto corr_eleSmear = cset_eleScale->at(eleScaleSmear.at(m_era).at(2).Data());
            sf = corr_eleSmear->evaluate({"rho",  eta, r9});
            uncer = corr_eleSmear->evaluate({"err_rho",  eta, r9});
            sysScale = m_Sys_smear;
        }
        switch(sysScale){
            case 0:
                return sf;
                break;
            case 1:
                return sf+uncer;
                break;
            case 2:
                return sf-uncer;
                break;
            default:
                return 1.0;
                break;
        }
    }
};

// void EleMVASel::Select(const eventForNano *e)
void EleMVASel::Select( eventForNano *e)
{
    if(m_entry==0){
        std::cout << "running EleMVASel::Select()\n";
    }
    clearBranch();
    // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight // 2016 - MVANoIso94XV2, from SUSY
    for (UInt_t j = 0; j < e->Electron_pt.GetSize(); ++j)
    {
        // Double_t eleScale = getEleScale(e->Electron_seedGain.At(j), *e->run, e->Electron_eta.At(j), e->Electron_r9.At(j), e->Electron_pt.At(j), kTRUE);//sys variation taken care of in getEleScale
        // Double_t eleSmear = getEleScale(e->Electron_seedGain.At(j), *e->run, e->Electron_eta.At(j), e->Electron_r9.At(j), e->Electron_pt.At(j), kFALSE);
        // Double_t pt = e->Electron_pt.At(j)*eleScale*eleSmear;
        // std::cout<<"eleScale="<<eleScale<<" eleSmear="<<eleSmear<<" pt="<<pt<<"\n";
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
        if (!m_isRun3){
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
        }
        muonsTopMVAT_pt.push_back(pt);
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