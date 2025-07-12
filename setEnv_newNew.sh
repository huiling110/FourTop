source /scratchfs/cms/huahuil/myenv/bin/activate
# python3 -m venv /scratchfs/cms/huahuil/myenv
# pip install statsmodels

current_dir=$(pwd)

#Set up ROOT 
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9ded8fcd995/lib:/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9ded8fcd995/lib64:$LD_LIBRARY_PATH #root needs correct gcc version
export TBB=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/tbb/v2022.0.0-343819c0b5b8954dc26b2f24bfd56a37/lib #ROOT needs TBB 
export LD_LIBRARY_PATH=$TBB:$LD_LIBRARY_PATH
source /cvmfs/cms.cern.ch/el9_amd64_gcc14/lcg/root/6.36.01-fd214bf9b7a010bf699f6444925c3f56/bin/thisroot.sh
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/lcg/root/6.36.01-fd214bf9b7a010bf699f6444925c3f56/lib:$LD_LIBRARY_PATH # for linking: TMVA



#Correction
#!!!Install with pip install correctionlib
#Install: python3 -m pip install --no-binary=correctionlib  correctionlib 
export LD_LIBRARY_PATH=/scratchfs/cms/huahuil/myenv/lib64/python3.9/site-packages/correctionlib/lib:$LD_LIBRARY_PATH #For run time 

#TMVA: problem during linking
# ROOTSYS: set up by thhisroot.sh

#libcommenFunction 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${current_dir}/myLibrary/ #For run time

#Gcc
export PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9ded8fcd995/bin:$PATH

#Set up python
export PYTHONPATH=$PYTHONPATH:${current_dir}/hua/src_py/ #Python can find the custom modules: usefulFunc....