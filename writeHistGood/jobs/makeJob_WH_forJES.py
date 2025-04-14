import makeJob_forWriteHist as mj 
import ttttGlobleQuantity as gq


# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/'
# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
# inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/'
# inVersion = 'v89HadroPre_JESPt22'#!!!for JES variation only
# inVersion = 'v90MuonESHadroPre_JESPt22'
# inVersion = 'v91TESAddedHadroPre_JESPt20'
# inVersion = 'v93HadroPreJetVetoPileupID_JESPt22'
# inVersion = 'v91TESAddedLepPre_JETPt22'
inVersion = 'v94HadroPreJetVetoHemOnly'
# inVersion = 'v94HadroPreJetVetoHemOnly_JESPt22'
# inVersion = 'v94LepPreJetVetoHemOnly_JESPt22'
# inVersion = 'v94LepPreJetVetoHemOnly'
# outVersion = 'v0baselineHadro'
# outVersion = 'v0baselineLep'
outVersion = 'v1baselineHadroBtagWeightAdded'
channel = '1tau1l'
# channel = '1tau0l'
# channel = '1tau2l'
# version = f'v0BDT{channel}'
# version = f'v0BDT{channel}NewCR'
# version = f'v0BDT{channel}FakeTau'
# version = f'v0DataMC_sys'
# version = f'v0DataMC_sysV2'
# version = 'v0BDT1tau1lAddMCFakeTV2'
version = 'v0BDT1tau1lAddMCFakeTV3'
# version = 'v0BDT1tau0lV2'
# exe = './apps/run_WH_forDataMC.out'
exe = './apps/run_treeAnalyzer.out' 
justMC = True # for energy scale variation, only need to run MC


def main():
    subJES(inputDirBase, inVersion, outVersion, channel, version, exe, justMC)
    # subJER(inputDirBase, inVersion, outVersion, channel, version, exe, justMC)
    # subMET(inputDirBase, inVersion, outVersion, channel, version, exe, justMC)
    # subEleES(inputDirBase, inVersion, outVersion, channel, version, exe, justMC)
    # subTES(inputDirBase, inVersion, outVersion, channel, version, exe, justMC)
    
def subTES(inputDirBase, inVersion, outVersion, channel, version, exe, justMC):
    for i in (0, 1, 10, 11):
        inputVersionUp = f'{inputDirBase}{outVersion}_{inVersion}_TESdm{i}Up/'
        inputVersionDown = f'{inputDirBase}{outVersion}_{inVersion}_TESdm{i}Down/'
        mj.main(inputVersionUp, channel , version, exe, 0, justMC)
        print('submitted WH TES up i: ', i)
        mj.main(inputVersionDown, channel, version, exe, 0, justMC)
        print('submitted WH TES down i: ', i)    
    
def subEleES(inputDirBase, inVersion, outVersion, channel, version, exe, justMC):
    inputVersionUp = f'{inputDirBase}{outVersion}_{inVersion}_EleScaleUp/'
    inputVersionDown = f'{inputDirBase}{outVersion}_{inVersion}_EleScaleDown/'
    mj.main(inputVersionUp, channel , version, exe, 0, justMC)
    mj.main(inputVersionDown, channel, version, exe, 0, justMC)
    print('submitted WH EleScale up')
    print('submitted WH EleScale down')
    
def subMET(inputDirBase, inVersion, outVersion, channel, version, exe, justMC):
    inputVersionUp = f'{inputDirBase}{outVersion}_{inVersion}_METUp/' 
    inputVersionDown = f'{inputDirBase}{outVersion}_{inVersion}_METDown/'
    mj.main(inputVersionUp, channel , version, exe, 0, justMC)
    mj.main(inputVersionDown, channel, version, exe,  0, justMC)
    print('submitted WH MET up')
    print('submitted WH MET down')
    
def subJER(inputDirBase, inVersion, outVersion, channel, version, exe, justMC):
   inputVersionUp = f'{inputDirBase}{outVersion}_{inVersion}_JERUp/' 
   inputVersionDown = f'{inputDirBase}{outVersion}_{inVersion}_JERDown/'
   mj.main(inputVersionUp, channel , version, exe, 0, justMC)
   mj.main(inputVersionDown, channel, version, exe, 0, justMC)
   print('submitted WH JER up')
   print('submitted WH JER down')

def subJES(inputDirBase, inVersion, outVersion, channel, version, exe, justMC):
    inVersionJES = inVersion + '_JESPt22'
    for i in gq.JESVariationList:
        # inputVersionUp = f'{inputDirBase}{outVersion}_JESup_{i}_{inVersion}/'
        # inputVersionDown = f'{inputDirBase}{outVersion}_JESDown_{i}_{inVersion}/'
        inputVersionUp = f'{inputDirBase}{outVersion}_JESup_{i}_{inVersionJES}/'
        inputVersionDown = f'{inputDirBase}{outVersion}_JESDown_{i}_{inVersionJES}/'
        print('inputVersionUp: ', inputVersionUp)
        print('inputVersionDown: ', inputVersionDown)
        
        mj.main(inputVersionUp, channel , version, exe, 0, justMC)
        print('submitted WH JES up i: ', i) 
        mj.main(inputVersionDown, channel, version,  exe, 0, justMC)
        print('submitted WH JES down i: ', i)

if __name__ == '__main__':
    main()     