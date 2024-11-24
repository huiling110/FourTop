import os
import subprocess

import ttttGlobleQuantity as GQ
import usefulFunc as uf


#???make the makeJobs code some functions and stuff to make it reusable
#???make this job submisssion and checking and resubmit and addHist automatized
#todo add git co after job submission for version control

def main(
    # year = '2016'
    year = '2018',
    # year = '2017'
    inVersion = 'v89HadroPre_JESPt22',#!!!for JES variation only
    # outVersion = 'v0baselineLep',
    outVersion = 'v0baselineHadro',
    # MVParameters = [1, 0, 0] ,# if1tau2l, JESVariationType, JESVariation
    if1tau2l = 0, # 0 false, 1 True
    JESVariationType = 0,
    JESVariation = 0,
):
    # inVersion = 'v86LepPreSel'
    # inVersion = 'v87LepPreSel_GammaRemovalBugFixed'
    # inVersion = 'v87addPdfPSWeightSum'
    # inVersion = 'v88PSWeightFixedLepPre'
    # inVersion = 'v88PSWeightFixedHadroPre'

    
    # outVersion = 'v1baselineHardroFRUpdated' 
    # outVersion = 'v1cut1tau1lSR'
    # outVersion = 'v2cut1tau2lSR'
   
    
    
    isRun3 = uf.isRun3Era(year)
    justMC = False
    
    print('jobVersion:', outVersion + '_'+ inVersion) 
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
            generateJobsForDir( iDir, iera+'_'+key,  jobDir , isRun3, if1tau2l, JESVariationType, JESVariation)
            subAllofAll.write('bash '+ iera+'_'+key + '_subAll.sh\n' )
    print( 'sub all jobs using: ' + jobDir +'/' + subAllName)
    subAllofAll.close()

    #change mod
    subprocess.run( 'chmod 777 '+ subAllofAllName, shell=True )
    
    uf.sumbitJobs(  subAllofAllName )




def getInOutDic( year, inVersion, outVersion, justMC ):
    inputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    # outputBase = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/'
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

         



def generateJobsForDir( inOutList, dirKind, jobDir , isRun3=False, if1tau2l=False, JESVariationType=0, JESVariation=0):
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
        print( 'loop over: ', entry )
        if not uf.checkIfInputDic(entry, isRun3): continue
        
        processJob = jobsDir + 'MV_' + dirKind +'_'+ entry + ".sh"
        iParametersList = [ inOutList[0], entry, inOutList[1], 0, if1tau2l, JESVariationType, JESVariation]
        writeIjob( iParametersList, processJob )

        uf.checkMakeDir(inOutList[1] +"log/")
        logFile = inOutList[1] +   "log/" + entry + ".log"
        errFile = inOutList[1] +  "log/" + entry +".err"
        subDirJobs.write( 'hep_sub -os CentOS7 -mem 6000 '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )

    subprocess.run( 'chmod 777 '+jobsDir +'*.sh', shell = True )
    subprocess.run( 'chmod 777 ' + subDirName, shell = True)


            
    

def writeIjob( parameterList, processJob ):
    subFile  = open ( processJob ,"w")
    subFile.write( "#!/bin/bash\n")
    subFile.write("/bin/hostname\n")
    codeDir = os.path.dirname(os.path.abspath(__file__))
    codeDir = codeDir.rsplit('/',1)[0]
    subFile.write("cd {}\n".format(codeDir))
    # command = './apps/run_makeVariables.out {}  {} {} {}    '.format( parameterList[0], parameterList[1], parameterList[2], parameterList[3]  )
    # command = './apps/run_makeVariables.out {}  {} {} {} {} {} {}     '.format( parameterList[0], parameterList[1], parameterList[2], parameterList[3]  )
    command = f'./apps/run_makeVariables.out {parameterList[0]} {parameterList[1]} {parameterList[2]} {parameterList[3]} {parameterList[4]} {parameterList[5]} {parameterList[6]}'
    subFile.write(command )
    subFile.close()







if __name__=="__main__":
    main() 










