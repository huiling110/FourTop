#!/bin/bash
/bin/hostname
source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/
root -b -l -q 'TMVAClassification_variableFileInput.C("","/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l/variableList/varibleList_49.csv",1)'