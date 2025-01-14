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
    inVersion = 'v91TESAddedHadroPre_JESPt20'
    # inVersion = 'v91TESAddedLepPre_JETPt22'
    # outVersion = 'v0baselineLep'
    # outVersion = 'v0baselineLepV2'
    # outVersion = 'v1baselineLepMETFixed'
    outVersion = 'v0baselineHadro'
    # outVersion = 'v1FixedBtagWeightWhenJES'
    if1tau2l = 0
    # if1tau2l = 1
   
    
    for i in gq.JESVariationList:
        print('i JESVariation: ', i)
        ioutVersionUp = f'{outVersion}_JESup_{i}'
        ioutVersionDown = f'{outVersion}_JESDown_{i}'
        # ioutVersionUp = f'{outVersion}_JESup_{JESVariationList[i]}'
        # ioutVersionDown = f'{outVersion}_JESDown_{JESVariationList[i]}'
        # print('ioutVersionUp: ', ioutVersionUp) 
        #get i = JESVariationList index
        i = gq.JESVariationList.index(i)
        mj.main(year, inVersion, ioutVersionUp, if1tau2l, 1, i)
        print('submitted JES up\n')
        mj.main(year, inVersion, ioutVersionDown, if1tau2l, 2, i)
        print('submitted JES down\n\n\n')
        
   
   
if __name__=='__main__':
    main() 