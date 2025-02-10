import makeJob_forWriteHist as mj 
import ttttGlobleQuantity as gq


inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/'
# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/'
# inVersion = 'v89HadroPre_JESPt22'#!!!for JES variation only
# inVersion = 'v90MuonESHadroPre_JESPt22'
# inVersion = 'v91TESAddedHadroPre_JESPt20'
# inVersion = 'v93HadroPreJetVetoPileupID_JESPt22'
inVersion = 'v94HadroPreJetVetoHemOnly_JESPt22'
# inVersion = 'v91TESAddedLepPre_JETPt22'
outVersion = 'v0baselineHadro'
# outVersion = 'v0baselineLep'
# outVersion = 'v0baselineLepV2'
# outVersion = 'v1baselineLepMETFixed'
# channel = '1tau1l'
channel = '1tau0l'
# channel = '1tau2l'
version = f'v0BDT{channel}'
# version = f'v0DataMC_sys'
version = f'v0DataMC_sysV2'
exe = './apps/run_WH_forDataMC.out'
# exe = './apps/run_treeAnalyzer.out' 



# for i in range(0, 27):
for i in gq.JESVariationList:
   inputVersionUp = f'{inputDirBase}{outVersion}_JESup_{i}_{inVersion}/'
   inputVersionDown = f'{inputDirBase}{outVersion}_JESDown_{i}_{inVersion}/'
   print('inputVersionUp: ', inputVersionUp)
   print('inputVersionDown: ', inputVersionDown)
   
   mj.main(inputVersionUp, channel , version, exe)
   print('submitted WH JES up i: ', i) 
   mj.main(inputVersionDown, channel, version, exe)
   print('submitted WH JES down i: ', i)
     