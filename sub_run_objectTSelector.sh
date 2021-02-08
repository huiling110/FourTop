#!/bin/bash
/bin/hostname

cd /publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/
root -q "run_objectTSelector.C( false)"

