#!/bin/bash
# CentOS7 environment setup for XGBoost 0.80 verification test
# Created: 2025-12-20
# Purpose: Run OS step with XGBoost 0.80 to verify yield difference root cause

# Get the directory where this script is located
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
current_dir="${script_dir}"

# IMPORTANT: Reset environment to avoid contamination from existing CMSSW
# Keep only essential system paths
export PATH=/usr/local/bin:/usr/bin:/bin
export LD_LIBRARY_PATH=""
export PYTHONPATH=""

# Python path for custom modules
export PYTHONPATH=${current_dir}/hua/src_py/

# GCC 9.3.0 for CentOS7 (slc7_amd64_gcc900)
export PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/bin/:$PATH
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/lib64/:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/lib/

# ROOT 6.22.08 for CentOS7
export ROOTSYS=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f
export PATH=$ROOTSYS/bin/:$PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib/:$LD_LIBRARY_PATH

# TBB (Threading Building Blocks) - required by ROOT's libImt.so
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/tbb/v2021.2.0-cms/lib/:$LD_LIBRARY_PATH

# XGBoost 0.80 (slc7_amd64_gcc700) - the key difference from setEnv_newNew.sh
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/lib/:$LD_LIBRARY_PATH

# correctionlib 2.0.0 for CentOS7 (slc7_amd64_gcc900)
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-correctionlib/2.0.0-0c4f44c8dd5561d8c0660135feeb81f4/lib/python3.9/site-packages/correctionlib/lib:$LD_LIBRARY_PATH

# Custom libraries
export LD_LIBRARY_PATH=${current_dir}/myLibrary/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/roccor/:$LD_LIBRARY_PATH

# Note: Do NOT add /usr/lib64 to LD_LIBRARY_PATH - it would override the GCC 9.3.0 libstdc++

# For matplotlib cache
export MPLCONFIGDIR=/scratchfs/cms/huahuil/matplotlib_cache

# For OpenBLAS threads (avoid cluster issues)
export OPENBLAS_NUM_THREADS=10

echo "CentOS7 environment loaded (XGBoost 0.80)"
echo "  GCC: 9.3.0"
echo "  ROOT: 6.22.08"
echo "  XGBoost: 0.80 (slc7_amd64_gcc700)"
echo "  correctionlib: 2.0.0 (slc7_amd64_gcc900)"
