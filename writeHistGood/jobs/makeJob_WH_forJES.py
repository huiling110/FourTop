import makeJob_forWriteHist as mj 


# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/'
# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/'
inVersion = 'v89HadroPre_JESPt22'#!!!for JES variation only
outVersion = 'v0baselineHadro'
# channel = '1tau1l'
channel = '1tau0l'


for i in range(0, 27):
# for i in range(0, 1):
   inputVersionUp = f'{inputDirBase}{outVersion}_JESup_{i}_{inVersion}/'
   inputVersionDown = f'{inputDirBase}{outVersion}_JESDown_{i}_{inVersion}/'
   
   mj.main(inputVersionUp, channel )
   print('submitted WH JES up i: ', i) 
   mj.main(inputVersionDown, channel)
   print('submitted WH JES down i: ', i)
     