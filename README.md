# Instructon for implemention
* install 
  * export SCRAM_ARCH=slc7_amd64_gcc700
  * cmsrel CMSSW_10_2_20_UL
  * cd CMSSW_10_2_20_UL/src
  * git clone git@github.com:huiling110/FourTop.git 
  * cd FourTop
  * git checkout  TauOfTTTT_SimplifyPlotter
  * cmsenv
 * run
   * cmsenv
   * cd objectSelection
   * make clean
   * make  (complie objectTSelectorForNano )
   * root -b -q run_objectTSelectorForNanoAOD.C
 * tips
   * modify Linkdef.h and Makefile to use classes and functions from other source file(.C). never #inlude .C source code! only #include .h
   * only member functions of objectTSelector class should be in the class file, other functions go to utilityFunctions.C( keep things clean and code modulized)
   * only need to recompile if modifying source code, don't need to if only modifying run_objectTSelectorForNanoAOD.C


 * submit jobs in IHEP cluster
    * cd FourTop/objectSelection
    * open makeJob_objectTSelectorForNanoAOD.py, change the parameters to your setting in the file in the first few lines.
      * all the modification you should do it in the makeJob script
    * python3 makeJob_objectTSelector_forSeperate.py
    * . subAllJobs.sh

 * set up combine
    * cd $CMSSW_BASE/src
    * git clone git@github.com:cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
    * cd HiggsAnalysis/CombinedLimit
    * cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
    * git fetch origin
    * git checkout v8.1.0
    * cd $CMSSW_BASE/src
    * curl -s https://raw.githubusercontent.com/cms-analysis/CombineHarvester/master/CombineTools/scripts/sparse-checkout-https.sh
    * scramv1 b clean; scramv1 b

 * tips for Fabio to uptade his branch with master
    * before Huiling's merge:
       * git push origin --delete fabio_developing
       * git push origin fabio_developing
    * after Huiling has merged:
       * git checkout master
       * git pull origin master
       * git branch -D fabio_developing
       * git checkout -b fabio_developing

       
    * if you want to change the shared code and expriment you'd better make another branch out of it and do it in the expriment branch.
    * if you want to submit jobs and git tag of the job version you should definitely do it in Fabio's branch and later merge Fabio branch to master.
  
      
     
