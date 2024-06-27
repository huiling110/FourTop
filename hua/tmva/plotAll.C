#include "variables.C"
// #include "correlations.C"
#include "efficiencies.C"
#include "mvas.C"
// #include "mutransform.C"
#include "correlations_less20Inputs.C"
#include "significance_usingPDF.C"

void plotAll(
    // TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/2tau2l_varibleList_23.root",
    // TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2l_v1/1tau2l_varibleList_10.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v1/variableList_check/1tau1l.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3correctBjetsvariable_fromV9/1tau1l_v1/trainWith40Cutbin/1tau1lvaribleList_10.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/1tau1lvaribleList_11.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/1tau1l_v1/1tau1lvaribleList_15.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/mc/tmvaTraining/btagWP/variableList_15.csv.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1NewHLTSF1tau1lCut_v64PreAndHLTSel/mc/BDTTrain/varibleList_16.csv.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau1l_v64PreAndHLTSel/mc/BDTTrain/varibleList_16.csv.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1l_v74AddMETPhi/mc/BDTTrain/branch_names.csv.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1l_v74AddMETPhi/mc/BDTTrain/v1_noTauTT/inputList_noTauTT.csv.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1l_v75AddTauTTTTNoHTCut/mc/BDTTrain/v0/inputList_tauTT.csv.root",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2tau1l1CutHT4006jetpt30_v75OverlapRemovalFTau/mc/BDTTrain/v0/inputList_tauTT.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2tau1l1CutHT4006jetpt30_v75OverlapRemovalFTau/mc/BDTTrain/v0/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Cut1tau1l_v75OverlapRemovalFTau/mc/BDTTrain/v1AllCorrection/inputList_tauTT.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Cut1tau1l_v75OverlapRemovalFTau/mc/BDTTrain/v1AllCorrection/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Cut1tau1l_v75OverlapRemovalFTau/mc/BDTTrain/v2NoBtag/inputList_noBtagShape.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Cut1tau1l_v75OverlapRemovalFTau/mc/BDTTrain/v2NoBtag/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau0l_v75OverlapRemovalFTau/mc/BDTTrain/v0/inputList_1tau0l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau0l_v75OverlapRemovalFTau/mc/BDTTrain/v0/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau2l_v76For1tau2l/mc/BDTTrain/v0/inputList_1tau2l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau2l_v76For1tau2l/mc/BDTTrain/v0/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v5cut1tau1lSR_v75OverlapRemovalFTau/mc/BDTTrain/v0/inputList_1tau1l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v5cut1tau1lSR_v75OverlapRemovalFTau/mc/BDTTrain/v0/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v1withBtag/inputList_1tau1l_btag.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v1withBtag/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v0/inputList_1tau1l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v0/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v3TrainingB/inputList_1tau1l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v3TrainingB/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLSample/mc/BDTTrain/v0allVar/inputList_1tau1l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLSample/mc/BDTTrain/v0allVar/results/",
    TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v76WithVLLAllMass/mc/BDTTrain/v1final26Var/inputList_1tau0l_final26.csv.root",
    TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v76WithVLLAllMass/mc/BDTTrain/v1final26Var/results/",
    Bool_t plotSigOnly = false
)
{
  cout << "=== execute: variables()" << endl;
  cout << "\n";

  if (plotSigOnly == false)
  {
    cout << "=== execute: correlations()" << endl;
    correlations_less20Inputs(fin);
  cout<<"\n";

    cout << "=== execute: mvas()" << endl;
  cout<<"\n";
    mvas(fin);
  }

  cout << "=== execute: significance_usingPDF()" << endl;
  significance_usingPDF(fin);
  cout<<"\n";

  cout << "=== execute: efficiencies()" << endl;
  efficiencies(fin, outDir);
  cout<<"\n";
}
