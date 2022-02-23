#!/bin/bash
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/objectSelection/
root -l -b -q 'run_objectTSelectorForNanoAOD.C(false,"/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/ttbar_0l/","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v5_preselectionHLTMet/mc/ttbar_0l/","outTree_58.root","7",true)'
