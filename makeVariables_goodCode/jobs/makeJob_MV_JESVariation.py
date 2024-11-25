import makeJob_makeVaribles_forBDT as mj
#generate all 54 up and down JES variation job version for  MV  

def main():
    # year = '2018'
    year = '2017'
    inVersion = 'v89HadroPre_JESPt22'#!!!for JES variation only
    # outVersion = 'v0baselineLep',
    outVersion = 'v0baselineHadro'
    if1tau2l = 0
   
    
    for i in range(0, 27):
    # for i in range(0, 1):
        print('i JESVariation: ', i)
        ioutVersionUp = f'{outVersion}_JESup_{i}'
        ioutVersionDown = f'{outVersion}_JESDown_{i}'
        mj.main(year, inVersion, ioutVersionUp, if1tau2l, 1, i)
        print('submitted JES up\n')
        mj.main(year, inVersion, ioutVersionDown, if1tau2l, 2, i)
        print('submitted JES down\n\n\n')
        
   
   
if __name__=='__main__':
    main() 