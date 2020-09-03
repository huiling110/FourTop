# Instructon for implemention
* install 
  * export SCRAM_ARCH=slc7_amd64_gcc700
  * cmsrel CMSSW_10_2_20_UL
  * cd CMSSW_10_2_20_UL/src
  * git clone git@github.com:huiling110/FourTop.git 
  * git checkout TauOfTTTT_102
  * cmsenv
 * run
   * root -b -q EventSelection_4top_v1.cpp
     * use the default parameters, you can change to what you need
   * .x EventSelection_4top_v1.cpp+
     * this would speed up 
     
