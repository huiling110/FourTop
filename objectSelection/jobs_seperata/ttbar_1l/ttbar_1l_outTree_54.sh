#!/bin/bash
cd /publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/objectSelection/
root -l -b -q 'run_objectTSelectorForNanoAOD.C(false,"/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/ttbar_1l/","/publicfs/cms/user/fabioiemmi/TauOfTTTT_NanoAOD/UL2016_preVFP/v8_METfiltersAndPresel_fixJSONmask/mc/ttbar_1l/","outTree_54.root","5",false)'
