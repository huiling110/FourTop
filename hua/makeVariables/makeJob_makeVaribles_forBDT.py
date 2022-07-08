import sys
import os
import glob
import string
import subprocess
 #


#???make the makeJobs code some functions and stuff to make it reusable


def main():


    #all the parameters you need to change is in this part , better not change the rest of the code.
    inVersion = 'v17NoSelection'
    outVersion = 'v1baselineCorrectedDataBug'
    justMC = False
    year = '2016'
    selectionBit = '7'


    inputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'

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

    subAllofAll = open( 'subAllofAll.sh', 'w')
    for iera in inOutDirMap.keys():
        if iera=='2016preVFP' : continue
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
        # processJob = 'Jobsubmit_seperate/'+  entry + ".sh"
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

#     subAllFile = Jobsubmitpath+"/subAllProcess.sh"
#     if os.path.exists(subAllFile):
#         os.popen('rm -fr '+subAllFile)
#     if not os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate"):
#         os.mkdir('Jobsubmit_seperate/')
#     if not os.path.exists( outputDir):
#         os.mkdir( outputDir )

#     #better not change code after this line
#     subAllProcessName = file(subAllFile,"w")
#     print >> subAllProcessName, "#!/bin/bash"
#     print >> subAllProcessName, "cd "+Jobsubmitpath



# os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/*sh")
# os.popen('chmod 777 '+Jobsubmitpath+"/subAllProcess.sh")






if __name__=="__main__":
    main() 










