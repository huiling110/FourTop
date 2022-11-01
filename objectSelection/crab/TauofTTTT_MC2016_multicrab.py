import CRABClient

if __name__ == '__main__':
#change baseDir to your BSM code location
#change config.General.workArea to where you want to put your crab output directory
#change config.Data.outLFNDirBase to your T2 site
#change the datasetnames and datasetinputs to sample you want to run
#do not change anything else

 #####
 ##   Multicrab configuration
 #####
 import sys
 from multiprocessing import Process

 from CRABClient.UserUtilities import config  # , getUsernameFromSiteDB

 #?
 config = config()
 from CRABAPI.RawCommand import crabCommand
 from CRABClient.ClientExceptions import ClientException
 from httplib import HTTPException
 config.General.workArea = 'Crab_projects'

 def submit(config):
    try:
    crabCommand('submit', config = config)
    except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
    except ClientException as cle:
    print "Failed submitting task: %s" % (cle)
 #####
 ##   Crab configuration
 #####
 datasetnames  = [#{{{
    # signal
    'Legacy16V2_TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8',#S 
    #'Legacy16V2_TTTT_TuneCUETP8M2T4_PSweights_13TeV',#S
    #'Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8',#S 

]

 datasetinputs = [
    #signal
    #'/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
    #'/TTTT_TuneCUETP8M2T4_PSweights_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
    #'/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
    #'/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
]

# samples also used in tW or bstar
# minimum lepton are set to 1 instead of 2 
tWLists = [
]
#?nothing in twLists?

#baseDir = "/workfs/cms/huahuil/BSM_UpdateVersion/CMSSW_10_2_20_UL/src/BSMFramework/"
baseDir = "/workfs/cms/huahuil/BSM_UpdateVersion/add_toptagger/CMSSW_10_2_20_UL/src/BSMFramework/"

for d in range(0,len(datasetnames)):
#for d in range(0,1):
    print 'multicrab.py: Running datasetname: ', datasetnames[d]
#    lepFilt = 2
    lepFilt = 0
    if datasetnames[d] in tWLists:
        lepFilt = 1
        print 'multicrab_MC2016.py: Run ', datasetnames[d], ' lepFilt 1 for tW samples '
    
    if "ctcvcp" in datasetnames[d]:
        lepFilt = 0
        print 'multicrab_MC2016.py: Run ', datasetnames[d], ' lepFilt 0 for ctcvcp samples '
    
    nameLepFilt = 'optionlepfilt={}'.format(lepFilt) #The format() method formats the specified value(s) and insert them inside the string's placeholder.
    
    config.section_('General')
    config.General.requestName = datasetnames[d]#it is used by CRAB to create a project directory (named crab_<requestName>) where files corresponding to this particular task will be stored.
 #   config.General.workArea    = datasetnames[d]#The area (full or relative path) where to create the CRAB project directory
    config.General.workArea    = '/workfs/cms/huahuil/BSM_UpdateVersion/add_toptagger/CMSSW_10_2_20_UL/src/BSMFramework/BSM3G_TNT_Maker/crab/crab_results_1216/'  #do not write to workfs anymore because the output log file could be more than 2G
    config.General.transferLogs = True  #Whether or not to copy the jobs log files to the storage site

    config.section_('JobType')
    config.JobType.pluginName  = 'Analysis'
    # List of parameters to pass to CMSSW parameter-set configuration file:
    config.JobType.psetName    = baseDir+'BSM3G_TNT_Maker/python/miniAOD_MC2016_Study.py'
    config.JobType.inputFiles = [(baseDir+'BSM3G_TNT_Maker/data/QG/QGL_AK4chs_94X.db')]
    config.JobType.sendExternalFolder = True
    config.JobType.maxMemoryMB = 2000 # Default == 2Gb : maximum guaranteed to run on all sites
#    config.JobType.maxMemoryMB = 200 # try a lower value to see if works with 50660 . not working:w
    #config.JobType.allowUndistributedCMSSW = True
    ofParam = 'ofName=' + datasetnames[d]
    config.JobType.pyCfgParams = [nameLepFilt,
                                    ofParam]
    config.section_('Data')
    config.Data.allowNonValidInputDataset = True
    config.Data.inputDataset   = datasetinputs[d]
    config.Data.inputDBS       = 'global'
    #  config.Data.splitting      = 'FileBased'
    config.Data.splitting      = 'Automatic'
    #  config.Data.totalUnits     = 40000 #With 'FileBased' splitting tells how many files to analyse
    config.Data.unitsPerJob    = 2000
    #  config.Data.unitsPerJob    = 200 #changed to
    config.Data.outLFNDirBase = '/store/user/hhua/'# First part of LFN for output files (must be /store/user/<username>/ or /store/group/<username>/  )
    config.Data.outputDatasetTag = datasetnames[d]+"HLTToptaggerAdded_EJetMetUpdated_oldEIDBack"

#    print 'multicrab.py: outLFNDirBase = /store/user/binghuan/'
    print 'multicrab.py: outLFNDirBase = /store/user/hhua/'
    #config.Data.publication = True

    config.section_('Site')
    config.Site.storageSite    = 'T2_CN_Beijing'#'T2_CH_CERN' # Site to which output is permenantly copied by crab3
    print 'multicrab.py: Submitting Jobs'
    #submit(config)
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()
    #?
