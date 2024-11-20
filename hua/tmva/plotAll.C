#include "variables.C"
// #include "correlations.C"
#include "efficiencies.C"
#include "mvas.C"
// #include "mutransform.C"
#include "correlations_less20Inputs.C"
#include "significance_usingPDF.C"

void plotAll(
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v1withBtag/inputList_1tau1l_btag.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v1withBtag/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v0/inputList_1tau1l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v0/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v3TrainingB/inputList_1tau1l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v3TrainingB/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLSample/mc/BDTTrain/v0allVar/inputList_1tau1l.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLSample/mc/BDTTrain/v0allVar/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v76WithVLLAllMass/mc/BDTTrain/v1final26Var/inputList_1tau0l_final26.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v76WithVLLAllMass/mc/BDTTrain/v1final26Var/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v79HadroPresel/mc/BDTTrain/v1final26Var/inputList_1tau0l_final26.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v79HadroPresel/mc/BDTTrain/v1final26Var/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v80addTauJetVar/mc/BDTTrain/v5finalFinal25Var/inputList_finalFinal25.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v80addTauJetVar/mc/BDTTrain/v5finalFinal25Var/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v80addTauJetVar/mc/BDTTrain/v5finalFinal25Var/inputList_finalFinal25.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v80addTauJetVar/mc/BDTTrain/v5finalFinal25Var/results/",
    // TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v80addTTExtra1/mc/BDTTrain/v1finalVar27/inputList_1tau1l_final.csv.root",
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v80addTTExtra1/mc/BDTTrain/v1finalVar27/results/",
    TString fin = "/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2018/v0baselineHardro_1tau1l_BDTSR_v86HadroPreSelWithGammaRemoval/mc/BDTTrain/tttt_GBDT_1tau1l/inputList_1tau1l_final.csv.root",
    TString outDir = "/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2018/v0baselineHardro_1tau1l_BDTSR_v86HadroPreSelWithGammaRemoval/mc/BDTTrain/tttt_GBDT_1tau1l/results/",
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
