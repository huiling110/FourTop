import os
import subprocess
import sys

import ttttGlobleQuantity as GQ

# import glob
# import string

 #

#???make the makeJobs code some functions and stuff to make it reusable
#???make this job submisssion and checking and resubmit and addHist automatized


# inVersion = 'v17NoSelection'
# inVersion = 'v19HLTSelection'
# inVersion = 'v20FixedSelectJetsBug'
# inVersion = 'v22addedRuinsTree'
# inVersion = 'v23basicWeight'
# inVersion = 'v24noJER'
# inVersion = 'v26noJERNOTESwithSorting'
# inVersion = 'v27noJERnoTESWithObjectRemoval'
inVersion = 'v29LorentzProblemSolvedNoJERnoTES'
# inVersion = 'v28JERTESBack'
# outVersion = 'v0noBaseline'
outVersion = 'v1baseline'
# outVersion = 'v1noBaselineModifiedDouble_t'
justMC = False
year = '2016'
selectionBit = '7'


inputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'
# outputBase = '/scratchfs/cms/huahuil/forMVA/'







def main():
    #all the parameters you need to change is in this part , better not change the rest of the code.
    inOutDirMap = getInOutDic( year, inputBase, outputBase, inVersion, outVersion, justMC )

    subAllofAll = open( 'subAllofAll.sh', 'w')
    for iera in inOutDirMap.keys():
        # if iera=='2016preVFP' : continue
        # if iera=='2016postVFP' : continue#???
        print(iera)
        if not os.path.exists( outputBase + iera +'/' ):
            os.mkdir( outputBase + iera +'/'  )
        if not os.path.exists( outputBase+iera+'/'+ outVersion+'_'+inVersion):
            os.mkdir( outputBase+iera+'/' +outVersion+'_'+inVersion)
        for key in inOutDirMap[iera].keys():
            iDir = inOutDirMap[iera][key]
            print( iDir )
            generateJobsForDir( iDir, iera+'_'+key, selectionBit )
            subAllofAll.write('bash '+ iera+'_'+key + '_subAll.sh\n' )
    print( 'sub all jobs using: subAllofAll.sh')
    subAllofAll.close()

    #change mod
    subprocess.run( 'chmod 777 subAllofAll.sh', shell=True )


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
    return inOutDirMap





def generateJobsForDir( inOutList, dirKind, selectionBit ):
    subDirJobs = open( dirKind+'_subAll.sh', 'w' )
    subDirJobs.write( '#!/bin/bash\n' )
    subDirJobs.write( 'cd /workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/makeVariables/\n')
    jobsDir = dirKind + '_jobs/'
    if not os.path.exists( jobsDir ):
        os.mkdir( jobsDir )
    if not os.path.exists( inOutList[1] ):
        os.mkdir ( inOutList[1] )

    for entry in os.listdir(inOutList[0] ):
        if not entry in GQ.samples: continue
        print( 'loop over: ', entry )
        
        processJob = jobsDir +  entry + ".sh"
        iParametersList = [ inOutList[0], entry, inOutList[1], selectionBit ]
        writeIjob( iParametersList, processJob )

        if not os.path.exists(inOutList[1] +"log/" ):
            os.mkdir( inOutList[1]  +"log/")
        logFile = inOutList[1] +   "log/" + entry + ".log"
        errFile = inOutList[1] +  "log/" + entry +".err"
        subDirJobs.write( 'hep_sub -mem 6000 '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )
        # subDirJobs.write( 'hep_sub  '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )

    subprocess.run( 'chmod 777 '+jobsDir +'*.sh', shell = True )
    subprocess.run( 'chmod 777 ' + dirKind+'_subAll.sh', shell = True)


def writeIjob( parameterList, processJob ):
    subFile  = open ( processJob ,"w")
    subFile.write( "#!/bin/bash\n")
    subFile.write("/bin/hostname\n")
    subFile.write("cd /workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/makeVariables\n")
    command = 'root -b -l -q \'run_makeVaribles_forBDT.C(false, \"{}\", \"{}\", \"{}\", \"{}\"   )\' '.format( parameterList[0], parameterList[1], parameterList[2], parameterList[3]  )
    subFile.write(command )
    subFile.close()







if __name__=="__main__":
    main() 










