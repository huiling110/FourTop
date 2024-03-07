import os
import subprocess

import ttttGlobleQuantity as GQ
import usefulFunc as uf


#???make the makeJobs code some functions and stuff to make it reusable
#???make this job submisssion and checking and resubmit and addHist automatized
#todo add git co after job submission for version control

def main():
    # year = '2022'
    # year = '2016'
    # year = '2018'
    # year = '2017'
    # year = '2022postEE'
    # inVersion = 'v0Testing'
    # inVersion = 'v1newCrab'
    # inVersion = 'v59newOScode'
    # inVersion = 'v60fixeJetBtagBug'
    # inVersion = 'v61fixesLepRemovalBug'
    # inVersion = 'v62addTauJetVars'
    # inVersion = 'v63smallFixJER'
    # inVersion = 'v64noHLTSel'
    # inVersion = 'v64PreAndHLTSel'
    # inVersion = 'v64PreAndHLTSel_JERUp'
    # inVersion = 'v64PreAndHLTSel_JERDown'
    # inVersion = 'v64PreAndHLTSel_JESUp'
    # inVersion = 'v64PreAndHLTSel_JESDown'
    # inVersion = 'v64PreAndHLTSel_TESDown'
    # inVersion = 'v64PreAndHLTSel_TESUp'
    # inVersion = 'v65TheoryWeightAdded'
    # inVersion = 'v67TheoryWeightAdded'
    # outVersion = 'v0NewMV'
    # outVersion = 'v2btagShapeWeightCorrected'
    # outVersion = 'v3btagWPWeightGood'
    # outVersion = 'v5newBtagEff'
    # outVersion = 'v6updatedBtagR'
    # outVersion = 'v8tau1elCut'
    # outVersion = 'v0baseline_addTauGenNum'
    # outVersion = 'v1btagWP:w
    # andRUpdated'
    # outVersion = 'v2eraBugFixed'
    # outVersion = 'v3btagWeightGood'
    # outVersion = 'v4forBDT1tau1lCut'
    # outVersion = 'v0baseline'
    # outVersion = 'v0NewHLTSF'
    # outVersion = 'v0NewHLTSFBinA'
    # outVersion = 'v0NewHLTSFBinD'
    # outVersion = 'v0NewHLTSFBinE'
    # outVersion = 'v0NewHLTSFHT500BinE'
    # outVersion = 'v0NewHLTSFHT550BinF'
    # outVersion = 'v1NewHLTSF1tau1lCut'
    # outVersion = 'v2cut1tau1l'
    
    #2022
    # year = '2022postEE'
    year = '2022preEE'
    # inVersion = 'v0preSel'
    # inVersion = 'v1for2022preSel'
    # inVersion = 'v2leptonsNameChange'
    # inVersion = 'v0for2022baseline'
    inVersion = 'v3EnergyScaleDone'
    outVersion = 'v0baseline'
   
    
    
    isRun3 = uf.isRun3Era(year)
    justMC = False
    
    
    
    #all the parameters you need to change is in this part , better not change the rest of the code.
    inOutDirMap = getInOutDic( year, inVersion, outVersion, justMC )

    jobDir = os.path.dirname(os.path.abspath(__file__)) 

    subAllName = year+'subAllofAll.sh'
    subAllofAllName = jobDir+ '/'+ subAllName
    subAllofAll = open( subAllofAllName, 'w')
    print('creating subAllofAll: ', subAllofAllName )
    subAllofAll.write( '#!/bin/bash\n')
    subAllofAll.write('cd '+jobDir + '\n')

    for iera in inOutDirMap.keys():
        # if iera=='2016preVFP' : continue
        # if iera=='2016postVFP' : continue#
        print('era: ', iera)
        
        for key in inOutDirMap[iera].keys():
            iDir = inOutDirMap[iera][key]
            print( 'inputOutDir: ', iDir )
            generateJobsForDir( iDir, iera+'_'+key,  jobDir , isRun3)
            subAllofAll.write('bash '+ iera+'_'+key + '_subAll.sh\n' )
    print( 'sub all jobs using: ' + jobDir +'/' + subAllName)
    subAllofAll.close()

    #change mod
    subprocess.run( 'chmod 777 '+ subAllofAllName, shell=True )


    uf.sumbitJobs(  subAllofAllName )




def getInOutDic( year, inVersion, outVersion, justMC ):
    inputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'
    # outputBase = '/scratchfs/cms/huahuil/forMVA/'
    inputOutputDic={
        '2016postVFP': 'UL2016_postVFP',
        '2016preVFP': 'UL2016_preVFP',
        '2017': 'UL2017',
        '2018': 'UL2018',
        # '2022': 'Prompt2022',
        '2022': 'ReReco2022PreEE',
        '2022preEE': '2022preEE',
        '2022postEE': '2022postEE',
    }
    inOutDirMap = {}
#python dict
    if year=='2016':
        inOutDirMap ['2016postVFP'] = {}
        inOutDirMap ['2016preVFP'] = {}
        inOutDirMap['2016preVFP']['mc']= [ inputBase + 'UL2016_preVFP/'+ inVersion + '/mc/' , outputBase + '2016preVFP/'+ outVersion+'_'+inVersion + '/mc/' ]  
        inOutDirMap['2016postVFP']['mc'] = [ inputBase + 'UL2016_postVFP/' + inVersion + '/mc/', outputBase + '2016postVFP/'+ outVersion+'_'+inVersion + '/mc/']
        if not justMC:
            inOutDirMap['2016preVFP'] ['data']= [ inputBase + 'UL2016_preVFP/'+ inVersion + '/data/',   outputBase + '2016preVFP/'+ outVersion+'_'+inVersion + '/data/']
            inOutDirMap['2016postVFP']['data'] = [ inputBase + 'UL2016_postVFP/' + inVersion + '/data/', outputBase + '2016postVFP/'+ outVersion+'_'+inVersion + '/data/']
    else:
        inOutDirMap[year]={}
        inOutDirMap[year]['mc']= [ inputBase + inputOutputDic[year]+'/'+ inVersion + '/mc/' , outputBase +year+ '/'+ outVersion+'_'+inVersion + '/mc/' ]
        if not justMC:
            inOutDirMap[year]['data']= [ inputBase + inputOutputDic[year]+'/'+ inVersion + '/data/' , outputBase +year+ '/'+ outVersion+'_'+inVersion + '/data/' ]
            
    for iera in inOutDirMap.keys():
        uf.checkMakeDir(outputBase+iera+'/')
        uf.checkMakeDir(outputBase+iera+'/'+ outVersion+'_'+inVersion)
            
    return inOutDirMap

         



def generateJobsForDir( inOutList, dirKind, jobDir , isRun3=False):
    subDirName = jobDir+ '/'+ dirKind+'_subAll.sh'
    print('creating: ', subDirName )
    subDirJobs = open( subDirName, 'w' )
    subDirJobs.write( '#!/bin/bash\n' )
    subDirJobs.write( 'cd ' + jobDir +'\n')
    jobsDir =  jobDir + '/'+dirKind + '_jobs/'
     
    if os.path.exists( jobsDir ):
        subprocess.run('rm -fr '+ jobsDir , shell=True)
    uf.checkMakeDir(jobsDir)
    uf.checkMakeDir(inOutList[1])

    for entry in os.listdir(inOutList[0] ):
        if not isRun3:
            if not entry in GQ.samples: continue
        else:
            if not entry in GQ.Run3Samples.keys(): continue
        print( 'loop over: ', entry )
        
        processJob = jobsDir + 'MV_' + dirKind +'_'+ entry + ".sh"
        iParametersList = [ inOutList[0], entry, inOutList[1], 0]
        writeIjob( iParametersList, processJob )

        uf.checkMakeDir(inOutList[1] +"log/")
        logFile = inOutList[1] +   "log/" + entry + ".log"
        errFile = inOutList[1] +  "log/" + entry +".err"
        subDirJobs.write( 'hep_sub  '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )

    subprocess.run( 'chmod 777 '+jobsDir +'*.sh', shell = True )
    subprocess.run( 'chmod 777 ' + subDirName, shell = True)


def writeIjob( parameterList, processJob ):
    subFile  = open ( processJob ,"w")
    subFile.write( "#!/bin/bash\n")
    subFile.write("/bin/hostname\n")
    codeDir = os.path.dirname(os.path.abspath(__file__))
    codeDir = codeDir.rsplit('/',1)[0]
    subFile.write("cd {}\n".format(codeDir))
    command = './apps/run_makeVariables.out {}  {} {} {}    '.format( parameterList[0], parameterList[1], parameterList[2], parameterList[3]  )
    subFile.write(command )
    subFile.close()







if __name__=="__main__":
    main() 










