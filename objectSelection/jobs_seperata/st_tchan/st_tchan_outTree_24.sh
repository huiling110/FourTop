#!/bin/bash
cd /publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/objectSelection/
root -l -b -q 'run_objectTSelectorForNanoAOD.C(false,"/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/st_tchan/","/publicfs/cms/user/fabioiemmi/TauOfTTTT_NanoAOD/UL2016_preVFP/v8_METfiltersAndPresel_fixJSONmask/mc/st_tchan/","outTree_24.root","5",false)'
