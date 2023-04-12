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

# inVersion = 'v49FixedPileUpOnlyJER'
# inVersion = 'v49FixedPileUpJERAndTES'
# inVersion = 'v50switchRawPtJERNoTES'
# inVersion = 'v51TESNoJER'
# inVersion = 'v51TESNewLepFoLepForrObjectRemoval
# inVersion = 'v51TESNewLepObjectRemovalCorrected'
# inVersion =  'v52noHLTSelection'
# inVersion = 'v52noHLTButPreSelection'
# inVersion = 'v54noHLTButPre'
# inVersion = 'v54noHLTButPreMetFixed'
# inVersion = 'v55ojectRemovalwithTight'
# inVersion = 'v55ojectRemovalwithTightNoHLT'
inVersion = 'v56NoHLTButPre'
# inVersion = 'v56preselection'

# outVersion = 'v0noBaseline'
# outVersion = 'v0baseline'
# outVersion = 'v0noCut'
# outVersion = 'v1cut1tau1l'
# outVersion = 'v2baslineNoHLTBugFixed'
# outVersion = 'v4HLTWeightUpdatedNewSFRange'
# outVersion = 'v5extra1tau1lCut'
outVersion = 'v6baseline'
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
# year = '2016'
# year = '2018'
year = '2017'
# selectionBit = '0'
# selectionBit = '4'
selectionBit = '6' # no metfilters
# selectionBit = '2' # no metfilters
print('version: {}_{},  selection:{}'.format(outVersion, inVersion, selectionBit))
justMC = False




inputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'
# outputBase = '/scratchfs/cms/huahuil/forMVA/'







def main():
    #all the parameters you need to change is in this part , better not change the rest of the code.
    inOutDirMap = getInOutDic( year, inputBase, outputBase, inVersion, outVersion, justMC )

    # print(__file__)
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
        uf.checkMakeDir(outputBase+iera+'/')
        uf.checkMakeDir(outputBase+iera+'/'+ outVersion+'_'+inVersion)
        for key in inOutDirMap[iera].keys():
            iDir = inOutDirMap[iera][key]
            print( 'inputOutDir: ', iDir )
            generateJobsForDir( iDir, iera+'_'+key, selectionBit, jobDir )
            subAllofAll.write('bash '+ iera+'_'+key + '_subAll.sh\n' )
    print( 'sub all jobs using: ' + jobDir +'/' + subAllName)
    subAllofAll.close()

    #change mod
    subprocess.run( 'chmod 777 '+ subAllofAllName, shell=True )


    uf.sumbitJobs(  subAllofAllName )




def getInOutDic( year, inputBase, outBase, inVersion, outVersion, justMC ):
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
        inOutDirMap[year]['mc']= [ inputBase + 'UL'+year+'/'+ inVersion + '/mc/' , outputBase +year+ '/'+ outVersion+'_'+inVersion + '/mc/' ]
        if not justMC:
            inOutDirMap[year]['data']= [ inputBase + 'UL'+year+'/'+ inVersion + '/data/' , outputBase +year+ '/'+ outVersion+'_'+inVersion + '/data/' ]
    return inOutDirMap





def generateJobsForDir( inOutList, dirKind, selectionBit, jobDir ):
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
        if not entry in GQ.samples: continue
        print( 'loop over: ', entry )
        
        # processJob = jobsDir + 'MV_'+ entry + ".sh"
        # processJob = jobsDir + 'MV_' + year + entry + ".sh"
        processJob = jobsDir + 'MV_' + dirKind +'_'+ entry + ".sh"
        iParametersList = [ inOutList[0], entry, inOutList[1], selectionBit ]
        writeIjob( iParametersList, processJob )

        uf.checkMakeDir(inOutList[1] +"log/")
        logFile = inOutList[1] +   "log/" + entry + ".log"
        errFile = inOutList[1] +  "log/" + entry +".err"
        subDirJobs.write( 'hep_sub  '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )

    subprocess.run( 'chmod 777 '+jobsDir +'*.sh', shell = True )
    subprocess.run( 'chmod 777 ' + subDirName, shell = True)


def writeIjob( parameterList, processJob ):
    subFile  = open ( processJob ,"w")
    # subFile  = open ( 'MV_'+ processJob ,"w")
    subFile.write( "#!/bin/bash\n")
    subFile.write("/bin/hostname\n")
    codeDir = os.path.dirname(os.path.abspath(__file__))
    subFile.write("cd {}\n".format(codeDir))
    # command = 'root -b -l -q \'run_makeVaribles_forBDT.C(false, \"{}\", \"{}\", \"{}\", \"{}\"   )\' '.format( parameterList[0], parameterList[1], parameterList[2], parameterList[3]  )
    command = './run_makeVaribles_forBDT.out 0  {}  {} {} {}    '.format( parameterList[0], parameterList[1], parameterList[2], parameterList[3]  )
    subFile.write(command )
    subFile.close()







if __name__=="__main__":
    main() 










