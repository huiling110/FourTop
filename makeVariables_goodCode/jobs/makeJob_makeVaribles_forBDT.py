import os
import subprocess
import sys

import ttttGlobleQuantity as GQ
import usefulFunc as uf

# import glob
# import string

 #

#???make the makeJobs code some functions and stuff to make it reusable
#???make this job submisssion and checking and resubmit and addHist automatized
#todo add git co after job submission for version control

# inVersion = 'v51TESNewLepObjectRemovalCorrected'
# inVersion =  'v52noHLTSelection'
# inVersion = 'v52noHLTButPreSelection'
# inVersion = 'v54noHLTButPre'
# inVersion = 'v54noHLTButPreMetFixed'
# inVersion = 'v55ojectRemovalwithTight'
# inVersion = 'v55ojectRemovalwithTightNoHLT'
# inVersion = 'v56NoHLTButPre'
# inVersion = 'v56preselection'
# inVersion = 'v57ovelapWithTausF'
# inVersion = 'v58addGenBranches'

# outVersion = 'v4baselineBtagRUpdated'
# outVersion = 'v5extra1tau1lCut'
# outVersion = 'v4baseline'
# outVersion = 'v5updateHLTSF'
# outVersion = 'v5baselineExtraTauLepCut'
# outVersion = 'v6Cut1tau1lVariableFixed'
# outVersion = 'v7baselineExtraTauCut'
# outVersion = 'v8Cut1tau1l'
# outVersion = 'v9addBtagWeight'
# outVersion = 'v10addPV_npvsGood_baseline'
# outVersion = 'v0LepLAdded'
# outVersion = 'v1AddTOPLepVariables'
# outVersion = 'v2aadTopLepWeight'
# outVersion = 'v3addjetBtagVar'
# selectionBit = '0'
# selectionBit = '4'
# selectionBit = '6' # no metfilters
# selectionBit = '2' # no metfilters
# print('version: {}_{},  selection:{}'.format(outVersion, inVersion, selectionBit))
# justMC = False


def main():
    # year = '2022'
    # year = '2016'
    year = '2018'
    # year = '2017'
    # inVersion = 'v0Testing'
    # inVersion = 'v1newCrab'
    # inVersion = 'v59newOScode'
    # inVersion = 'v60fixeJetBtagBug'
    inVersion = 'v61fixesLepRemovalBug'
    # outVersion = 'v0NewMV'
    # outVersion = 'v2btagShapeWeightCorrected'
    # outVersion = 'v3btagWPWeightGood'
    # outVersion = 'v4repeatv3'
    # outVersion = 'v5newBtagEff'
    # outVersion = 'v6updatedBtagR'
    # outVersion = 'v7forBDT'
    # outVersion = 'v8tau1elCut'
    # outVersion = 'v0baseline'
    outVersion = 'v1btagWPandRUpdated'
    # outVersion = 'v2eraBugFixed'
    # outVersion = 'v3btagWeightGood'
    # outVersion = 'v4forBDT1tau1lCut'
    
    # isRun3 = True
    isRun3 = False
    justMC = False
    
    
    
    #all the parameters you need to change is in this part , better not change the rest of the code.
    inOutDirMap = getInOutDic( year, inVersion, outVersion, justMC )

    jobDir = os.path.dirname(os.path.abspath(__file__)) 

    # subAllName = 'subAllofAll.sh'
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
        '2022': 'ReReco2022PreEE'
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










