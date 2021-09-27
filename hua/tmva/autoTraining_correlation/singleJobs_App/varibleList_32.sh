#!/bin/bash
/bin/hostname
source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/
root -b -l -q 'TMVAClassificationApplication_multipleSamples.C("","/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tauXl_v1/AppResults/","/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tauXl_v1/variableList/varibleList_32.csv","/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tauXl_v1/dataset/2tauXl_varibleList_32_weight/",5)'