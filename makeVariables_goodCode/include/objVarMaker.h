#ifndef OBJVARMAKER_H
#define OBJVARMAKER_H

#include "TLorentzVector.h"
#include <Math/Vector4D.h>
#include "eventReader_forMV.h"

class ObjVarMaker
{
public:
    ObjVarMaker(TTree *outTree, TString objName, Int_t type = 0);
    ~ObjVarMaker();
    void makeVariables(const EventForMV *e);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);
    void basicVariables();
    Int_t getNum();
    void reportEntry(TString className);

    // private:
protected:
    Int_t m_type = 0;
    ULong_t m_entry = 0;
    // output branches
    Int_t muons_num = -99;
    Double_t muons_1pt = -99;
    Double_t muons_1eta = -99;
    Double_t muons_1phi = -99;
    std::vector<ROOT::Math::PtEtaPhiMVector> objsLorentz;
};

#endif