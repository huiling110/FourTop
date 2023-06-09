# Todo list for 4top(2023.05)

## Big things
- [ ] BTV workshop (7.24-7,26)
- [ ] Run3 analysis


## Object
- [ ] Apply new tau ID SF 
- New Tau ID SF: https://cms-talk.web.cern.ch/t/new-tau-id-scale-factors-for-ul-mc/21688
- [Physics/TAU POG] Data/MC disagreement at high tau pT with new pt-dm-dependent scale factors
- [ ] jet ID: maybe switch to tight

## MC correction
- [ ] B tag r measure in 1tau lep=>0 rather than lep>=1(2016)
- [ ] B tag R systematic correlation in final fit?
- [ ] JER problem
- [ ] Pileup reweighting, why? should we ensure sum of weights the same?
- [x] B tag R measurement of a 2017
- [x] B tag R measurement of a 2018


## HLT 
- [ ] Optimize trigger SF binning
- [ ] Trigger efficiency unsymetric error to ensure less than 1
- [ ] How to assign trigger SF uncertainty?
- [ ] Graceful error handling of reading HLT branches in OS code
- [x] HLT SF 2017
- [x] HLT SF 2018




## Fake rate
- [ ] Maybe do b jet number selection after the b tag shape SF?
- [ ] FR, the fakeable tau pt impact
- [ ] Check the correlation of tau pt and jet b score sum in FR 


## BDT
- [ ] Hyper parameter optimization
- [x] BDT training, veto training data?

## Systematic study

## Results
- [ ] **Investigate the effect of moving bscore but use both medium b jets and tight b jet**
- [ ] **Investigate the effect of HT of bjets**
- [ ] Other channels
- [ ] Further divide 1tau1l into SS and OS 
- [ ] **E/mu spliting**
- [ ] SR in to b jets bins
- [ ] Check significance of 1tau3l, 2tau0l and 2tau1l channels

## AN
- [ ] Object selection
- [ ] Introduction



## Misc 
- [ ] Check download of nanoAOD files with DAS
- [ ] Investigate the impact of some missing data files
- [ ] Change to filling sumedHist instead add hist for templates
- [ ] Use the json from cmfs /
- [ ] Group subprocess for combine or not? no besause of the haddling the error
- [ ] Check why 2016B_v1 data, none passing METFilters 
- [ ] Overlap check with single lepton channel in 1tau1l


## Coding 
- [ ] Script for removing .root file in forMVA/
- [ ] Check for all sub processes in ploting
- [ ] Fix the double free bug in MV
- [ ] Add check for all samples in writecsv 
- [ ] Modulize code: cut flow critical!!
- [ ] Job checking and resubitting feature!!!


