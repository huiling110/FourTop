#!/bin/bash
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/objectSelection/
root -l -b -q 'run_objectTSelectorForNanoAOD.C(false,"/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/qcd_200to300/","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v6_noHLTSelection_addedMulitjetForSingleMu/mc/qcd_200to300/","outTree_15.root","5",true)'
