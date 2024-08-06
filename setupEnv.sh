
#PYTHONPATH is an environment variable that tells Python where to look for modules and packages when you import them in your code.
# export  PYTHONPATH=/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20_20_UL/src/FourTop/hua/src_py/
export PYTHONPATH=$PYTHONPATH:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw-tool-conf/52.0/lib/python2.7/site-packages:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/external/slc7_amd64_gcc900/lib:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw-tool-conf/52.0-58e45b466f32005301749a5b48d2bb69/lib/python2.7/site-packages
# export PYTHONPATH=$PYTHONPATH:/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20_20_UL/src/FourTop/hua/src_py/
# export PYTHONPATH=$PYTHONPATH:/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/hua/src_py/
export PYTHONPATH=$PYTHONPATH:/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/src_py/
export PYTHON3PATH=/cvmfs/cms.cern.ch/share/overrides/python:/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/python:/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/lib/slc7_amd64_gcc900:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/python:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/lib/slc7_amd64_gcc900:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/coral/CORAL_2_3_21-7f3a02ad5513229377635b0d5f14c5db/slc7_amd64_gcc900/python:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/coral/CORAL_2_3_21-7f3a02ad5513229377635b0d5f14c5db/slc7_amd64_gcc900/lib:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw-tool-conf/52.0-58e45b466f32005301749a5b48d2bb69/lib/python3.9/site-packages




export PATH=/cvmfs/common.ihep.ac.cn/software/hepjob/bin:$PATH # to run OS7 on IHEP

#for ROOT executebles
export PATH=$PATH:/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/

export PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/bin/:$PATH
#setup ROOT
export ROOTSYS=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f
export PATH=$ROOTSYS/bin/:$PATH

export LD_LIBRARY_PATH=/usr/lib/:/usr/lib64/:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=$ROOTSYS/lib/:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/lib64/:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/lib/:$LD_LIBRARY_PATH

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/lib/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/external/slc7_amd64_gcc900/lib/  #this means the latets the xgboost lib that doesn't work # but it's essential for python3.9 to work
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/myLibrary/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/myLibrary/
export LIBRARY_PATH=$LD_LIBRARY_PATH:/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/myLibrary/ #complile time

#for xgboost
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/xgboost/1.3.3/lib64/
export PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/external/slc7_amd64_gcc900/bin/:$PATH
# export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-correctionlib/2.0.0-0c4f44c8dd5561d8c0660135feeb81f4/lib/python3.9/site-packages/correctionlib/lib/:$LD_LIBRARY_PATH

#for cmake
export PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/cmake/3.18.2/bin/:$PATH

#might need in futu
# source /afs/ihep.ac.cn/soft/CMS/64bit/root/rootenv-6 #this and next line should be used together
# export PYTHONPATH=$ROOTSYS/bin/:PYTHONPATH
#export CMSSW_GIT_REFERENCE=/cvmfs/cms.cern.ch/cmssw.git.daily
# export PYTHONUSERBASE=/scratchfs/cms/huahuil/python
# export PATH=$PYTHONUSERBASE/bin:$PATH

#for the vscode to run python due to limited process in IHEP cluster
 export OPENBLAS_NUM_THREADS=10

#
export VALGRIND_LIB=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/valgrind/3.15.0/lib/valgrind


# export FOURTOPSHOME="/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop"