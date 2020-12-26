#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

#include <iostream>

void HLTstudy_v1(){

    TFile *file_TTTT  = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forHLT_v1/NoJEC/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
    TTree *Tree_TTTT = (TTree*)file_TTTT->Get("tree");








}
