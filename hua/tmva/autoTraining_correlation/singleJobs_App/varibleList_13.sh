#!/bin/bash
/bin/hostname
source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/hua/tmva/
root -b -l -q 'TMVAClassificationApplication_multipleSamples.C("","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV8/1tau1l_v1/AppResults_11bins/","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV8/1tau1l_v1/variableList/varibleList_13.csv","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV8/1tau1l_v1/dataset/1tau1lvaribleList_13_weight/",1,11)'