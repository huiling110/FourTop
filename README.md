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
   * root -b -q EventSelection_4top_v1.cpp+
     * use the default parameters
     * add a + would speed up
   * root -b -q 'EventSelection_4top_v1.cpp+(false,"TauOfTTTT_Toptagger_oldEID_2.root", "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/NewNtupleAfterEventSelection_test/")'
   * root -q PlotterPreselection_PlayWithMC.cpp+
 * tips
    * git pull origin
      * use this command to get the most recent version from Huiling's repositary
 * notes
    * EventSelection_4top_v1.cpp : take ntuples(poduced from crab job) as input, and produce a corresponding root file with new branches of our interest in it 
    * GetEntry.cpp : get the positive and negative event in MC ntuples
    * HLTstudy_v1.cpp: calculate the efficiency of HLT, take root file produced by HLTstudy_v1.cpp as input
    * PlotterPreselection_PlayWithMC.cpp : look at the root files produced by PlotterPreselection_PlayWithMC.cpp, calculate separation power and make some plots of variables
    * makeIHEPjob.py: make IHEP job script and submission shell script .

 * submit jobs in IHEP cluster
    * cd FourTop/objectSelection
    * open makeJob_objectTSelector_forSeperate.py, change the parameters to your setting in the file in the first few lines.
    * python makeJob_objectTSelector_forSeperate.py
    * . subAllProcess_seperate.sh
      
  
      
     
