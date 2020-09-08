#/bin/bash
/bin/hostname
gcc -v
pwd
#cd /afs/ihep.ac.cn/users/h/huahuil/fourtop1/CMSSW_7_4_14/src/FourTop/
cd /workfs/cms/huahuil/TauOfTTTT/CMSSW_10_2_20_UL/src/FourTop/
cmsenv
#root -b -q EventSelection_4top_v1.cpp
#root -b -q EventSelection_4top_v1_830.cpp+'(false,"/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection")'
#root -b -q EventSelection_4top_v1_830.cpp'(false,"/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection")'
#.x EventSelection_4top_v1.cpp+'(false,"/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection")'
#.x EventSelection_4top_v1.cpp+(false,"/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection")

#root -b -q 'EventSelection_4top_v1.cpp+(false,"TTTT.root","/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/")'
root -b -q 'EventSelection_4top_v1.cpp+(false,"TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root","/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/")'
