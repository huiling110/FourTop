import subprocess

# runMacro = 'run_objectTSelectorForNano.C'
runMacro = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/objectSelection/run_objectTSelectorForNanoAOD.C'

inputDir = [
    
    '/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/',
    '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/tttt/',
    '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/jetHT_2016D/',
    '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/jetHT_2016C/',
    '/publicfs/cms/data/TopQuark/nanoAOD/2016/data/singleMu_2016G/',
    #
    '/publicfs/cms/data/TopQuark/nanoAOD/2018/data/jetHT_2018b/',
    '/publicfs/cms/data/TopQuark/nanoAOD/2018/data/jetHT_2018c/',
    '/publicfs/cms/data/TopQuark/nanoAOD/2018/data/jetHT_2018a/',
    '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/',
]
outputDir = 'output/'
singleFileName = 'outTree_1.root'
for iDir in inputDir:
    print(iDir)

    command = 'root -l -b -q \'' + runMacro + '(' + 'true,' +  '\"'+iDir+'\",'   +  '\"'+outputDir+'\",'  +  '\"'+singleFileName+'\",'  +  '\"5\", '  + 'true' + ' )\''
    print(command)
    process = subprocess.run( [command], 
            shell=True,
            # capture_output=True,
            # text=True,
                #  stdout=subprocess.PIPE,
            bufsize=1,
            # universal_newlines=True
            )
    # we’re invoking a shell at the start of the execution of our subprocess, and the command argument is interpreted directly by the shell
    output = process.stdout
    print( output)
    print('\n')