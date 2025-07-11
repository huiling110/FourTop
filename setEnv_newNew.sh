source /scratchfs/cms/huahuil/myenv/bin/activate
# python3 -m venv /scratchfs/cms/huahuil/myenv
# pip install statsmodels

current_dir=$(pwd)

#Set up ROOT 
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9ded8fcd995/lib:/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9ded8fcd995/lib64:$LD_LIBRARY_PATH #root needs correct gcc version
export TBB=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/tbb/v2022.0.0-343819c0b5b8954dc26b2f24bfd56a37/lib #ROOT needs TBB 
export LD_LIBRARY_PATH=$TBB:$LD_LIBRARY_PATH
source /cvmfs/cms.cern.ch/el9_amd64_gcc14/lcg/root/6.36.01-fd214bf9b7a010bf699f6444925c3f56/bin/thisroot.sh


#Set up python
export PYTHONPATH=$PYTHONPATH:${current_dir}/hua/src_py/