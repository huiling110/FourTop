
// #include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/tmvaglob.C"
#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/tmvaglob.h"

using std::cout;
using std::endl;

void signigicance(
             TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v13etaPhiAbs_v42_addNonBjets/1tauol_inputLeading20.root", 
              Bool_t useTMVAStyle = kTRUE, TString formula="S/sqrt(S+B)" )
{

   TFile* file = TMVAGlob::OpenFile( fin );
   cout<<file->GetName()<<endl;

}
