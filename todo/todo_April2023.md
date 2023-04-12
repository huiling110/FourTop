# Todo list for 4top(2023.04)

## Object 
- [ ] New Tau ID SF: https://cms-talk.web.cern.ch/t/new-tau-id-scale-factors-for-ul-mc/21688

## MC correction
- [ ] B tag r measure in 1tau lep=>0 rather than lep>=1(2016)
- [ ] B tag R measurement of a 2018
- [ ] B tag R systematic correlation in final fit?
- [ ] JER problem
- [ ] Pileup reweighting, why? should we ensure sum of weights the same?
- [x] B tag R measurement of a 2017


## HLT 
- [ ] HLT SF 2018
- [ ] Trigger efficiency unsymetric error to ensure less than 1
- [ ] How to assign trigger SF uncertainty?
- [ ] Graceful error handling of reading HLT branches in OS code
- [x] HLT SF 2017




## Fake rate
- [ ] Maybe do b jet number selection after the b tag shape SF?
- [ ] FR, the fakeable tau pt impact
- [ ] Check the correlation of tau pt and jet b score sum in FR 


## BDT
- [ ] BDT training, veto training data?
- [ ] Hyper parameter optimization



## Results
- [ ] Further divide 1tau1l into SS and OS 
- [ ] SR in to b jets bins



## Misc 
- [ ] Check download of nanoAOD files with DAS
- [ ] Change to filling sumedHist instead add hist for templates
- [ ] Use the json from cmfs /
- [ ] Group subprocess for combine or not? no besause of the haddling the error
- [ ] Check why 2016B_v1 data, none passing METFilters 


## Coding 
- [ ] Script for removing .root file in forMVA/
- [ ] Check for all sub processes in ploting
- [ ] Fix the double free bug in MV
- [ ] Add check for all samples in writecsv 
- [ ] Modulize code: cut flow critical!!
- [ ] Job checking and resubitting feature!!!

