#!/bin/bash
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/objectSelection/
root -l -b -q 'run_objectTSelectorForNanoAOD.C(false,"/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/singleMu_2016B_v2/","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v6_noHLTSelection_addedMulitjetForSingleMu/data/singleMu_2016B_v2/","outTree_50.root","5",true)'
