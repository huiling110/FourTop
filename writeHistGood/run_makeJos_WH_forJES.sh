#!/bin/bash

INPUT_DIR_BASE="/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/"
# IN_VERSION="v94HadroPreJetVetoHemOnly"
IN_VERSION='v94LepPreJetVetoHemOnlyV2'
OUT_VERSION="v1baselineHadroBtagWeightAdded"
# CHANNEL="1tau0l"
CHANNEL="1tau2l"
# VERSION="v5BDT1tau0l_tauFMorphFix"
VERSION="v5BDT1tau2l_tauFMorphFix"

# nohup python3 jobs/makeJob_WH_forJES.py \
#     --inputDirBase "${INPUT_DIR_BASE}" \
#     --inVersion "${IN_VERSION}" \
#     --outVersion "${OUT_VERSION}" \
#     --channel "${CHANNEL}" \
#     --version "${VERSION}" \
#     > log_2018_1tau2l.log 2>&1 &

nohup python3 jobs/makeJob_WH_forJES.py --inputDirBase "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/" --inVersion "v94LepPreJetVetoHemOnlyV2"  --outVersion "v1baselineHadroBtagWeightAdded" --channel "1tau2l" --version "v5BDT1tau2l_tauFMorphFix" > log_2017_1tau2l.log 2>&1 &
