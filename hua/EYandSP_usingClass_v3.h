/**
 * File              : EYandSP_usingClass_v3.h
 * Author            : Huiling Hua <huahl@ihep.ac.cn>
 * Date              : 03.10.2021
 * Last Modified Date: 03.10.2021
 * Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>
 */

#ifndef EYANDSP_USINGCLASS_V3
#define EYANDSP_USINGCLASS_V3

#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TCut.h"
#include "TPRegexp.h"

// #include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/src_cpp/lumiAndCrossSection.h"
#include "../src_cpp/lumiAndCrossSection.h"
#include "Process_Class.C"
// #include "Process_Class.h"

// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0preselection_fromV14/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1fixedTauVariables_v40addTauJetEtau/mc/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3extra1tau1lCut_v41addVertexSelection/mc/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3extra1tau1lCut_v41addVertexSelection/mc/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3extra1tau1lCut_v42fixedChargeType/mc/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6Cut1tau1lVariableFixed_v42fixedChargeType/mc/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v6Cut1tau1lVariableFixed_v42fixedChargeType/mc/";
// const TString baseDir2016 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v6Cut1tau1lVariableFixed_v42fixedChargeType/mc/";
// const TString baseDir2017 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6Cut1tau1lVariableFixed_v42fixedChargeType/mc/";
// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v8Cut1tau1l_v42fixedChargeType/mc/";
// const TString baseDir2016 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v8Cut1tau1l_v42fixedChargeType/mc/";
// const TString baseDir2017 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8Cut1tau1l_v42fixedChargeType/mc/";
const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/mc/";
// const TString baseDir2016 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/mc/";
const TString baseDir2016 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5extra1tau1lCut_v56preselection/mc/";
// const TString baseDir2017 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/mc/";
// const TString baseDir2017 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5extra1tau1lCut_v56NoHLTButPre/mc/";
const TString baseDir2017 = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/";
// const TString era_g = "2016";
const TString era_g = "2017";
// const TString era_g = "2018";

// const TCut g_weight = "EVENT_genWeight *EVENT_prefireWeight *PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR ";
// const TCut g_weight = "EVENT_genWeight *EVENT_prefireWeight *PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR ";
const TCut g_weight = "EVENT_genWeight *EVENT_prefireWeight *PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight * musTopMVAT_weight * btagWPMedium_weight "; //for btag WP


const TCut MetFilters = "Flag_goodVertices==1 && Flag_globalSuperTightHalo2016Filter==1 && Flag_HBHENoiseFilter==1 && Flag_HBHENoiseIsoFilter==1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_BadPFMuonFilter==1";
const TCut HLT_2016 = "HLT_PFHT450_SixJet40_BTagCSV_p056 || HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 ||HLT_PFJet450";

// /*
// const TCut baselineSelection = "jets_HT>500  && jets_6pt>40 ";
const TCut baselineSelection = "jets_HT>500  && jets_6pt>40 && jets_number>=6 ";

const TCut ES1tau0l = "tausT_number==1 && leptonsMVAT_number==0 &&  jets_number>=8 && bjetsM_num>=2 " && baselineSelection;
const TCut ES1tau1e = "tausT_number==1 && elesMVAT_number==1 && leptonsMVAT_number==1 &&  jets_number>=7 && bjetsM_num>=2" && baselineSelection;
const TCut ES1tau1m = "tausT_number==1 && muonsT_number==1 && leptonsMVAT_number==1&& jets_number>=7 && bjetsM_num>=2" && baselineSelection;
const TCut ES1tau2os = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  && jets_number>=6 && bjetsM_num>=2" && baselineSelection;
const TCut ES1tau2ss = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 && jets_number>=6 && bjetsM_num>=2 " && baselineSelection;
const TCut ES1tau3l = "tausT_number==1 && leptonsMVAT_number==3 &&  jets_number>=2 && bjetsM_num>=2 " && baselineSelection;
const TCut ES2tau0l = "tausT_number==2 && leptonsMVAT_number==0 &&  jets_number>=7 && bjetsM_num>=2 " && baselineSelection;
const TCut ES2tau1e = "tausT_number==2 && elesMVAT_number==1 && leptonsMVAT_number==1 && jets_number>=6 && bjetsM_num>=2 ";
const TCut ES2tau1m = "tausT_number==2 && muonsT_number==1 && leptonsMVAT_number==1 &&  jets_number>=6 && bjetsM_num>=2 " && baselineSelection;
const TCut ES2tau2os = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  && jets_number>=2 && bjetsM_num>=2 " && baselineSelection;
const TCut ES2tau2ss = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jets_number>=2 && bjetsM_num>=2 " && baselineSelection;

// const TCut ES1tau1l = ES1tau1e || ES1tau1m;
// const TCut ES1tau1l = "tausT_number==1 && (elesTopMVAT_number+muonsTopMVAT_numbe==1)  &&  jets_number>=7 && bjetsM_num>=2";
const TCut ES1tau1l = "tausT_number==1 && (elesTopMVATop_number+muonsTopMVATop_number==1)  &&  jets_number>=7 && bjetsM_num>=2";
const TCut ES1tau2l = ES1tau2os || ES1tau2ss;
const TCut ES2tau1l = ES2tau1e || ES2tau1m;
const TCut ES2tau2l = ES2tau2os || ES2tau2ss;
const TCut ES2tauXl = ES2tau0l || ES2tau1l || ES2tau2l;
const TCut ES2tau1_2l = ES2tau1l || ES2tau2l;
// */
// const TCut weight = "EVENT_genWeight*EVENT_prefireWeight*PUweight*btagEfficiency_weight*HLTefficiency_weight";
const TCut basicWeight = "EVENT_genWeight*EVENT_prefireWeight*PUweight";

std::map<TString, TCut> channelCutMap = {
    {"1tau0l", ES1tau0l},
    {"1tau1e", ES1tau1e},
    {"1tau1m", ES1tau1m},
    {"1tau1l", ES1tau1l},
    {"1tau2os", ES1tau2os},
    {"1tau2ss", ES1tau2ss},
    {"1tau2l", ES1tau2l},
    {"1tau3l", ES1tau3l},
    {"2tau0l", ES2tau0l},
    {"2tau1e", ES2tau1e},
    {"2tau1m", ES2tau1m},
    {"2tau1l", ES2tau1l},
    {"2tau2l", ES2tau2l},
    {"2tauXl", ES2tauXl},
    {"2tau1_2l", ES2tau1_2l},
};

// control region study for 1tau0l
const TCut CR_1tau0l = "tausT_number==1 && leptonsMVAT_number==0 && jets_number>=8 && bjetsM_num==0 ";
const TCut VR_1tau0l = "tausT_number==1 && leptonsMVAT_number==0 && jets_number>=8 && bjetsM_num==1 ";
const TCut CR2_1tau0l = "tausT_number==1 && leptonsMVAT_number==0 && jets_number<8 && bjetsM_num>=2";
const TCut CR3_1tau0l = "tausT_number==1 && leptonsMVAT_number==0 &&  jets_number<7 && bjetsM_num>=2 ";
const TCut CR4_1tau0l = "tausT_number==1 && leptonsMVAT_number==0 &&  jets_number==7 && bjetsM_num>=2 ";
std::map<TString, TCut> regions_1tau0l = {
    {"SR1tau0l", ES1tau0l},
    {"CR1tau0l", CR_1tau0l},
    {"VR1tau0l", VR_1tau0l},
    {"CR21tau0l", CR2_1tau0l},
    {"CR31tau0l", CR3_1tau0l},
    {"CR41tau0l", CR4_1tau0l},
};

// 2018
Process tttt{baseDir + "tttt.root", TTTT::crossSectionMap.at("tttt")};
Process TTTo2L2Nu{baseDir + "ttbar_2l.root", TTTT::crossSectionMap.at("ttbar_2l")};
Process TTToHadronic{baseDir + "ttbar_0l.root", TTTT::crossSectionMap.at("ttbar_0l")};
Process TTToSemiLeptonic{baseDir + "ttbar_1l.root", TTTT::crossSectionMap.at("ttbar_1l")};
Process TTGJets{baseDir + "ttG.root", 4.62};          // 3.773
Process ttZJets{baseDir + "ttZ.root", 0.783};         // 0.6559
Process ttWJets{baseDir + "ttW.root", 0.611};         // 0.2014 changed to 611
Process ttH_bb{baseDir + "ttH_bb.root", 0.2897};      // 0.2897
Process ttH_nonbb{baseDir + "ttH_nonbb.root", 0.209}; // 0.209
// VV
Process WZ{baseDir + "wz.root", 2.343};
Process WW{baseDir + "ww.root", 6.430};
Process ZZ{baseDir + "zz.root", 1.016}; // ZZ
// Process WGJets{baseDir+".root", 1.269 };//???
// Process ZGJetsToLLG{baseDir+".root", 0.1319 };//???
// VVV
// Process WWW{baseDir+".root", 0.2086 };//???
// Process WWZ{baseDir+".root", 0.1651 };//???
// Process WWG{baseDir+".root", 0.0435  };//???
// Process ZZZ{baseDir+".root", 0.01398 };//???
// Process WZZ{baseDir+".root", 0.05565 };//???
// Process WZG{baseDir+".root", 0.04123 };//???
// Process WGG{baseDir+".root", 1.819 };//???
// Process ZGGJets{baseDir+".root", 0.3717 };//???
//
// Process WJetsToLNu{baseDir+".root", 50300 };//???
// Process DYJetsToTauTau{baseDir+".root", 1983 };//???
// Single Top
Process tZq_ll{baseDir + "st_tZq.root", 0.07358};
// Process tZq_nunu{baseDir+".root", 0.1379 };//???
Process ST_tW_antitop{baseDir + "st_tW_antitop.root", 35.85}; // 38.06
Process ST_tW_top{baseDir + "st_tW_top.root", 35.85};         // 38.09
// TX
//  Process TGJets{baseDir+".root", 2.967 };//???
//  // Process THW{baseDir+".root", 0.1467 };//???
//  Process THQ{baseDir+".root", 0.8816 };//???

// QCD
Process QCD_HT50to100{baseDir + "qcd_50to100.root", 2.466e+08};       // 50-100  //2.466e+08 +- 2.190e+05 pb
Process QCD_HT100to200{baseDir + "qcd_100to200.root", 2.801e+07};     // 100to200  //2.801e+07 +- 2.608e+04 pb
Process QCD_HT200to300{baseDir + "qcd_200to300.root", 1.721e+6};      // 1.710e+06 +- 1.626e+03 pb
Process QCD_HT300to500{baseDir + "qcd_300to500.root", 3.479e+05};     // 3.473e+05 +- 3.327e+02 pb
Process QCD_HT500to700{baseDir + "qcd_500to700.root", 3.206e+04};     // 3.220e+04 +- 3.100e+01 pb
Process QCD_HT700to1000{baseDir + "qcd_700to1000.root", 6.827e+03};   // 6.839e+03 +- 6.602e+00 pb
Process QCD_HT1000to1500{baseDir + "qcd_1000to1500.root", 1.207e+03}; // 1.207e+03 +- 1.167e+00 pb
Process QCD_HT1500to2000{baseDir + "qcd_1500to2000.root", 1.20e+02};  // 1.201e+02 +- 1.160e-01 pb
Process QCD_HT2000toInf{baseDir + "qcd_2000toInf.root", 2.525e+01};   // 2.524e+01 +- 2.436e-02 pb

std::vector<Process> allProcesses = {
    tttt,                                         // 0
    TTTo2L2Nu, TTToHadronic, TTToSemiLeptonic,    // 3
    TTGJets, ttZJets, ttWJets, ttH_bb, ttH_nonbb, // 8
    WZ, WW, ZZ,                                   // 11
    tZq_ll, ST_tW_antitop, ST_tW_top,             // 14
    // QCD_HT50to100, QCD_HT100to200, QCD_HT200to300, QCD_HT300to500, QCD_HT500to700, QCD_HT700to1000, QCD_HT1000to1500, QCD_HT1500to2000, QCD_HT2000toInf, // 23
    //???WJets not added yet
};

// 2016
Process TTTT2016{baseDir2016 + "tttt.root", TTTT::crossSectionMap.at("tttt")};
Process TTTo2L2Nu2016{baseDir2016 + "ttbar_2l.root", TTTT::crossSectionMap.at("ttbar_2l")};
Process TTToHadronic2016{baseDir2016 + "ttbar_0l.root", TTTT::crossSectionMap.at("ttbar_0l")};
Process TTToSemiLeptonic2016{baseDir2016 + "ttbar_1l.root", TTTT::crossSectionMap.at("ttbar_1l")};
Process TTGJets2016{baseDir2016 + "ttG.root", 4.62};          // 3.773
Process ttZJets2016{baseDir2016 + "ttZ.root", 0.783};         // 0.6559
Process ttWJets2016{baseDir2016 + "ttW.root", 0.611};         // 0.2014 changed to 611
Process ttH_bb2016{baseDir2016 + "ttH_bb.root", 0.2897};      // 0.2897
Process ttH_nonbb2016{baseDir2016 + "ttH_nonbb.root", 0.209}; // 0.209
// VV
Process WZ2016{baseDir2016 + "wz.root", 2.343};
Process WW2016{baseDir2016 + "ww.root", 6.430};
Process ZZ2016{baseDir2016 + "zz.root", 1.016}; // ZZ
// Single Top
Process tZq_ll2016{baseDir2016 + "st_tZq.root", 0.07358};
// Process tZq_nunu2016{baseDir2016+".root", 0.1379 };//???
Process ST_tW_antitop2016{baseDir2016 + "st_tW_antitop.root", 35.85}; // 38.06
Process ST_tW_top2016{baseDir2016 + "st_tW_top.root", 35.85};         // 38.09

std::vector<Process> allProcesses2016 = {
    TTTT2016,                                                         // 0
    TTTo2L2Nu2016, TTToHadronic2016, TTToSemiLeptonic2016,            // 3
    TTGJets2016, ttZJets2016, ttWJets2016, ttH_bb2016, ttH_nonbb2016, // 8
    WZ2016, WW2016, ZZ2016,                                           // 11
    tZq_ll2016, ST_tW_antitop2016, ST_tW_top2016,                     // 14
};

// 2017
Process TTTT2017{baseDir2017 + "tttt.root", TTTT::crossSectionMap.at("tttt")};
Process TTTo2L2Nu2017{baseDir2017 + "ttbar_2l.root", TTTT::crossSectionMap.at("ttbar_2l")};
Process TTToHadronic2017{baseDir2017 + "ttbar_0l.root", TTTT::crossSectionMap.at("ttbar_0l")};
Process TTToSemiLeptonic2017{baseDir2017 + "ttbar_1l.root", TTTT::crossSectionMap.at("ttbar_1l")};
Process TTGJets2017{baseDir2017 + "ttG.root", 4.62};          // 3.773
Process ttZJets2017{baseDir2017 + "ttZ.root", 0.783};         // 0.6559
Process ttWJets2017{baseDir2017 + "ttW.root", 0.611};         // 0.2014 changed to 611
Process ttH_bb2017{baseDir2017 + "ttH_bb.root", 0.2897};      // 0.2897
Process ttH_nonbb2017{baseDir2017 + "ttH_nonbb.root", 0.209}; // 0.209
// VV
Process WZ2017{baseDir2017 + "wz.root", 2.343};
Process WW2017{baseDir2017 + "ww.root", 6.430};
Process ZZ2017{baseDir2017 + "zz.root", 1.016}; // ZZ
// Single Top
Process tZq_ll2017{baseDir2017 + "st_tZq.root", 0.07358};
// Process tZq_nunu2017{baseDir2017+".root", 0.1379 };//???
Process ST_tW_antitop2017{baseDir2017 + "st_tW_antitop.root", 35.85}; // 38.06
Process ST_tW_top2017{baseDir2017 + "st_tW_top.root", 35.85};         // 38.09

std::vector<Process> allProcesses2017 = {
    TTTT2017,                                                         // 0
    TTTo2L2Nu2017, TTToHadronic2017, TTToSemiLeptonic2017,            // 3
    TTGJets2017, ttZJets2017, ttWJets2017, ttH_bb2017, ttH_nonbb2017, // 8
    WZ2017, WW2017, ZZ2017,                                           // 11
    tZq_ll2017, ST_tW_antitop2017, ST_tW_top2017,                     // 14
};

std::map<TString, std::vector<Process>> eraProcess_Map = {
    {"2016", allProcesses2016},
    {"2017", allProcesses2017},
    {"2018", allProcesses},
};

// TH1D *
// getBackHist(std::vector<Process> &allProcesses, const TCut cut, const TCut weight, TString era)
// {
//     TH1D *bg = new TH1D("bg", "bg", 40, 0, 40);
//     for (UInt_t j = 1; j < allProcesses.size(); j++)
//     {
//         // if(j > 0) bg->Add( allProcesses[j].getChannelHist( cut, weight) , LUMI*allProcesses[j].getScale() );
//         if (j > 0)
//             bg->Add(allProcesses[j].getChannelHist(cut, weight), lumiMap[era] * allProcesses[j].getScale());
//     }
//     return bg;
// }

TH1D *addHistChannel(const TCut cut, const TCut weight, TString branchName, const Int_t binNum, const Double_t binMin, const Double_t binMax, Int_t fromProcess, UInt_t toProcess, TString histName)
{
    TH1D *addedHist = new TH1D(histName, branchName, binNum, binMin, binMax);
    // addedHist->ResetStats();
    TH1D::SetDefaultSumw2();
    for (UInt_t j = fromProcess; j < toProcess; j++)
    {
        // addedHist->Add( allProcesses[j].getChannelHist(cut,weight, branchName, binNum, binMin, binMax),  allProcesses[j].getScale() );
        //???
        TH1D *temp = allProcesses[j].getChannelHist(cut, weight, branchName, binNum, binMin, binMax);
        temp->Scale(allProcesses[j].getScale());
        addedHist->Add(temp, 1);
        delete temp;
    }
    // addedHist->Print();
    return addedHist;
}

void getBgsAndSignalHist(std::vector<TH1D *> &groupedBGsAndSignal, const TCut channelCut, const TCut weight, const TString branch, const Int_t binNum, const Double_t binMin, const Double_t binMax)
{

    TH1D *TTTT = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 0, 1, "TTTT_" + branch);
    TH1D *TT = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 1, 4, "TT_" + branch);
    TH1D *TTX = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 4, 8, "TTX_" + branch);
    TH1D *VV = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 8, 13, "VV_" + branch);
    TH1D *VVV = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 13, 21, "VVV_" + branch);
    TH1D *WJets = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 21, 22, "WJets_" + branch);
    TH1D *DYJets = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 22, 23, "DYJets_" + branch);
    TH1D *SingleTop = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 23, 27, "SingleTop_" + branch);
    TH1D *TX = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 27, 30, "TX_" + branch);
    TH1D *QCD = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 30, 36, "QCD_" + branch);

    TH1D *allBg = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 1, 36, "allBg_" + branch);

    groupedBGsAndSignal.push_back(TTTT);
    groupedBGsAndSignal.push_back(TT);
    groupedBGsAndSignal.push_back(TTX);
    groupedBGsAndSignal.push_back(VV);
    groupedBGsAndSignal.push_back(VVV);
    groupedBGsAndSignal.push_back(WJets);
    groupedBGsAndSignal.push_back(DYJets);
    groupedBGsAndSignal.push_back(SingleTop);
    groupedBGsAndSignal.push_back(TX);
    groupedBGsAndSignal.push_back(QCD);
    groupedBGsAndSignal.push_back(allBg);

    // delete TTTT, TT;
}
void getBgsAndSignalHist_Nano(std::vector<TH1D *> &groupedBGsAndSignal, const TCut channelCut, const TString channelName, const TCut weight, const TString branch, const Int_t binNum, const Double_t binMin, const Double_t binMax)
{

    TH1D *TTTT = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 0, 1, channelName + "_TTTT_" + branch);
    TH1D *TT = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 1, 4, channelName + "_TT_" + branch);
    TH1D *TTX = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 4, 9, channelName + "_TTX_" + branch);
    TH1D *VV = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 9, 12, channelName + "_VV_" + branch);
    TH1D *SingleTop = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 12, 15, channelName + "_SingleTop_" + branch);
    TH1D *QCD = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 15, 24, channelName + "_QCD_" + branch);

    TH1D *allBg = addHistChannel(channelCut, weight, branch, binNum, binMin, binMax, 1, 24, channelName + "_allBg_" + branch);

    groupedBGsAndSignal.push_back(TTTT);
    groupedBGsAndSignal.push_back(TT);
    groupedBGsAndSignal.push_back(TTX);
    groupedBGsAndSignal.push_back(VV);
    groupedBGsAndSignal.push_back(SingleTop);
    groupedBGsAndSignal.push_back(QCD);
    groupedBGsAndSignal.push_back(allBg);
}

Double_t getAllBgEntries(const TCut cut, const TCut weight)
{
    Double_t bgEntries = 0.0;
    for (UInt_t j = 1; j < allProcesses.size(); j++)
    {
        bgEntries += allProcesses[j].getChannelHist(cut, weight)->GetEntries();
    }
    return bgEntries;
}

#endif