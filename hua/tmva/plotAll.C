// #include "variables.C"
// #include "correlations.C"
// #include "efficiencies.C"
#include "mvas.C"
// #include "mutransform.C"
#include "correlations_less20Inputs.C"

void plotAll(
        // TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/1tau1l_varibleList_17.root",
        TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/2tau2l_varibleList_23.root"

        )
{
  // cout << "=== execute: variables()" << endl;
  // variables( fin );

  cout << "=== execute: correlations()" << endl;
  correlations_less20Inputs( fin );

  cout << "=== execute: mvas()" << endl;
  mvas( fin );

  // cout << "=== execute: efficiencies()" << endl;
  // efficiencies( fin );
//
  // cout << "=== execute: ztransform()" << endl;
  // mutransform( fin );
}
