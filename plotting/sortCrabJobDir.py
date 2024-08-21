import os
import fnmatch

import usefulFunc as uf

def find_directories(base_dir, pattern):
    matching_dirs = []
    for root, dirs, files in os.walk(base_dir):
        for dir_name in dirs:
            if fnmatch.fnmatch(dir_name, pattern):
                matching_dirs.append(os.path.join(root, dir_name))
    return matching_dirs

def mvTTDir(ttlist, outBase):
    num = 0
    for i in ttlist:
        print('i: ', i)
        iproName = i.split('/')[-1]
        # outName = iproName.split('_')[0] + num 
        
        preFix = iproName.split('_')[0]
        outName = f'{preFix}{num}'
        print('iproName: ', iproName)
        print('outName: ', outName)
        
        outDir = outBase + outName
        uf.checkMakeDir(outDir)
        
        mvCommand = f'mv {i}/crab_*/*/*/*.root {outDir}/'
        print('mvCommand: ', mvCommand)   
        uf.runCommand(mvCommand)
        print('done mv ', iproName, ' \n')
       
        num += 1
        print('\n')

toSortDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tt/mc/'

# subDir = 'TTTo2L2Nu'
# subDir = 'TTToSemiLeptonic'
subDir = 'TTToHadronic'

subProsList = find_directories(toSortDir, subDir+'*')
for i in subProsList:
    print(i, '\n')
    
outBase = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/'    
mvTTDir(subProsList, outBase) 
    
    


