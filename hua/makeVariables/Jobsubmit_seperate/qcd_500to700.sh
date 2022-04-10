#!/bin/bash
/bin/hostname
cd /workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/hua/makeVariables
root -l -b -q 'run_makeVaribles_forBDT.C(false,"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v9_allSelection/mc/","qcd_500to700","/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v2Add2Variables_fromV9/")'
