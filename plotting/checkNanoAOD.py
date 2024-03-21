
import os
#check IHEP local nanoAOD data file with that of GRID

def main():
    # nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/JetMET2022E/'
    # nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/JetMET2022F/'
    nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/JetMET2022G/'
    
    fileNum = getNumFiles(nanoDir)
    print(nanoDir)
    print('fileNum=: ', fileNum)

def getNumFiles(nanoDir):
    files = os.listdir(nanoDir)
    #get the number of files end with ',root'
    numFiles = 0
    if files:
        for file in files:
            if file.endswith('.root'):
                numFiles += 1
    return numFiles
    
if __name__ == '__main__':
    main() 