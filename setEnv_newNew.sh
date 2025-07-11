source /scratchfs/cms/huahuil/myenv/bin/activate
# python3 -m venv /scratchfs/cms/huahuil/myenv
# pip install statsmodels

current_dir=$(pwd)

#Set up ROOT 
export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9ded8fcd995/lib:/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9ded8fcd995/lib64:$LD_LIBRARY_PATH #root needs correct gcc version
export TBB=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/tbb/v2022.0.0-343819c0b5b8954dc26b2f24bfd56a37/lib #ROOT needs TBB 
export LD_LIBRARY_PATH=$TBB:$LD_LIBRARY_PATH
source /cvmfs/cms.cern.ch/el9_amd64_gcc14/lcg/root/6.36.01-fd214bf9b7a010bf699f6444925c3f56/bin/thisroot.sh



#Correction 
#/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/py3-correctionlib/2.7.0-9912d66ec994fb1e89c22fe7b5d17bf5/lib/python3.9/site-packages/correctionlib/include/correction.h
# export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/py3-correctionlib/2.7.0-9912d66ec994fb1e89c22fe7b5d17bf5/lib/python3.9/site-packages/correctionlib/include:$LD_LIBRARY_PATH
# export PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/py3-correctionlib/2.7.0-9912d66ec994fb1e89c22fe7b5d17bf5/bin:$PATH #for correction executable
# export LIBRARY_PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/py3-correctionlib/2.7.0-9912d66ec994fb1e89c22fe7b5d17bf5/lib/python3.9/site-packages/correctionlib/include:$LD_LIBRARY_PATH
# export PYTHONPATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/py3-correctionlib/2.7.0-9912d66ec994fb1e89c22fe7b5d17bf5/lib/python3.9/site-packages:$PYTHONPATH #for correction python module; 
# export PYTHONPATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/cms/cmssw-tool-conf/100.0/lib/python3.9/site-packages:$PYTHONPATH # still 
#!!!Install with pip install correctionlib

#Gcc
# export PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc14/external/gcc/14.3.1-724da22786638848892aa9

#Set up python
export PYTHONPATH=$PYTHONPATH:${current_dir}/hua/src_py/ #Python can find the custom modules: usefulFunc....