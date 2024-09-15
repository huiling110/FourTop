#include <map>

#include "../include/eleVarMaker.h"
#include "../include/variablesFunctions.h"

EleVarMaker::EleVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker{outTree, objName, type}
{
    std::cout << "Initialzing the derived EleVarMaker........\n";


    std::cout << "Done initialization.............\n";
    std::cout << "\n";
};

void EleVarMaker::makeVariables(const EventForMV *e)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()

    clearBranch();

    setupLorentzObjs(e); //!!! crucial to overide base class!!!



    ObjVarMaker::basicVariables();
}

void EleVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
}

void EleVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // overide base ObjValMaker
    //!!! it means for every event we need to evaluate m_type
    UInt_t objNum = 0;
    switch (m_type)
    {
    case 0:
        objNum = e->elesMVAT_pt.GetSize();
        break;
    case 1:
        objNum = e->elesTopMVAT_pt.GetSize();
        break;
    }
    for (UInt_t i = 0; i < objNum; i++)
    {
        Double_t objPt = -99;
        Double_t objEta = -99;
        Double_t objPhi = -99;
        Double_t objMass = -99;
        switch (m_type)
        {
        case 0:
            objPt = e->elesMVAT_pt[i];
            objEta = e->elesMVAT_eta[i];
            objPhi = e->elesMVAT_phi[i];
            objMass = e->elesMVAT_mass[i];
            break;
        case 1:
            objPt = e->elesTopMVAT_pt[i];
            objEta = e->elesTopMVAT_eta[i];
            objPhi = e->elesTopMVAT_phi[i];
            objMass = e->elesTopMVAT_mass[i];
            break;
            // case 2:
            //     objPt = e->muonsL_pt[i];
            //     objEta = e->muonsL_eta[i];
            //     objPhi = e->muonsL_phi[i];
            //     objMass = e->muonsL_mass[i];
            //     break;
        }
        ROOT::Math::PtEtaPhiMVector muLorentz{objPt, objEta, objPhi, objMass};
        objsLorentz.push_back(muLorentz);
    }
};

EleVarMaker::~EleVarMaker(){};