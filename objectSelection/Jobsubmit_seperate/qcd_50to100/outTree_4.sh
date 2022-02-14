#!/bin/bash
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/objectSelection/
root -l -b -q 'run_objectTSelectorForNanoAOD.C(false,"/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/qcd_50to100/","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/2016postVFP/v0_testing/qcd_50to100/","outTree_4.root")'
