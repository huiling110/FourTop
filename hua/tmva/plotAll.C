// #include "variables.C"
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
    TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v1/trainWith40Cutbin/1tau1lvaribleList_10.root",
    Bool_t plotSigOnly = false

)
{
  // cout << "=== execute: variables()" << endl;
  // variables( fin );

  if (plotSigOnly == false)
  {
    cout << "=== execute: correlations()" << endl;
    correlations_less20Inputs(fin);

    cout << "=== execute: mvas()" << endl;
    mvas(fin);
  }

  cout << "=== execute: significance_usingPDF()" << endl;
  significance_usingPDF(fin);

  // cout << "=== execute: efficiencies()" << endl;
  // efficiencies( fin );
  //
  // cout << "=== execute: ztransform()" << endl;
  // mutransform( fin );
}
