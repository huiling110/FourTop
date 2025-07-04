import makeJob_makeVaribles_forBDT as mj
import ttttGlobleQuantity as gq
# import addJESTemplatesToHistFile as aj
#generate all 54 up and down JES variation job version for  MV  

def main():
    year = '2018'
    # year = '2017'
    # year = '2016'
    # inVersion = 'v89HadroPre_JESPt22'#!!!for JES variation only
    # inVersion = 'v90MuonESHadroPre_JESPt22'
    # inVersion = 'v91TESAddedHadroPre_JESPt20'
    # inVersion = 'v93HadroPreJetVetoPileupID_JESPt22'
    # inVersion = 'v91TESAddedLepPre_JETPt22'
    # inVersion = 'v94HadroPreJetVetoHemOnly_JESPt22'
    # inVersion = 'v94LepPreJetVetoHemOnly_JESPt22'
    inVersion = 'v94HadroPreJetVetoHemOnly'
    # inVersion = 'v94LepPreJetVetoHemOnly'
    # outVersion = 'v0baselineLep'
    # outVersion = 'v0baselineHadro'
    outVersion = 'v1baselineHadroBtagWeightAdded'
    if1tau2l = 0
    # if1tau2l = 1
  
  
    # MV_TES(year, inVersion, outVersion, if1tau2l)
    # MV_EES(year, inVersion, outVersion, if1tau2l)
    # MV_MET(year, inVersion, outVersion, if1tau2l)
    MV_JES(year, inVersion, outVersion, if1tau2l)

def MV_MET(year, inVersion, outVersion, if1tau2l):
    inVersionUp = f'{inVersion}_METUp'
    inVersionDown = f'{inVersion}_METDown'
    mj.main(year, inVersionUp, outVersion, if1tau2l, 0, 0)
    mj.main(year, inVersionDown, outVersion, if1tau2l, 0, 0) 

def MV_EES(year, inVersion, outVersion, if1tau2l):
    inVersionUp = f'{inVersion}_EleScaleUp'
    inVersionDown = f'{inVersion}_EleScaleDown'
    mj.main(year, inVersionUp, outVersion, if1tau2l, 0, 0)
    mj.main(year, inVersionDown, outVersion, if1tau2l, 0, 0)

    
    
def MV_TES(year, inVersion, outVersion, if1tau2l):
    for i in (0, 1, 10, 11):
        iInVersionUp = f'{inVersion}_TESdm{i}Up'
        iInVersionDown = f'{inVersion}_TESdm{i}Down'
        mj.main(year, iInVersionUp, outVersion, if1tau2l, 0, 0)
        mj.main(year, iInVersionDown, outVersion, if1tau2l, 0, 0)

def MV_JES(year, inVersion, outVersion, if1tau2l):    
    for i in gq.JESVariationList:
        print('i JESVariation: ', i)
        ioutVersionUp = f'{outVersion}_JESup_{i}'
        ioutVersionDown = f'{outVersion}_JESDown_{i}'
        # print('ioutVersionUp: ', ioutVersionUp) 
        i = gq.JESVariationList.index(i)
        mj.main(year, inVersion, ioutVersionUp, if1tau2l, 1, i)
        print('submitted JES up\n')
        mj.main(year, inVersion, ioutVersionDown, if1tau2l, 2, i)
        print('submitted JES down\n\n\n')
        
   
   
if __name__=='__main__':
    main() 