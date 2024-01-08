import os
import glob
import usefulFunc as uf

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0for2022baseline/mc/'
    outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0for2022baseline/mcNew/'
    # outputDir = '/path/to/output/directory/'  # Specify the output directory for the merged file
   
   
    
    uf.checkMakeDir(outputDir)
    # Get a list of all .root files in the input directory
    rootFiles = glob.glob(os.path.join(inputDir, '*.root'))
    
    # Create a dictionary to store the files with the same name except for the last digit
    fileDict = {}
    
    # Iterate over the root files
    for rootFile in rootFiles:
        # Get the base name of the file (without the extension)
        baseName = os.path.splitext(os.path.basename(rootFile))[0]
        # print(baseName)
                
        # Remove the last digit from the base name
        if baseName.endswith('1'):
            baseNameWithoutLastDigit = baseName[:-1]
        else: 
            baseNameWithoutLastDigit = baseName
        
        # Add the file to the dictionary based on the base name without the last digit
        if baseNameWithoutLastDigit in fileDict:
            fileDict[baseNameWithoutLastDigit].append(rootFile)
        else:
            fileDict[baseNameWithoutLastDigit] = [rootFile]
            
    # print(fileDict)
    
    haddFiles(fileDict, outputDir)
       
        
  
def haddFiles(fileDict, outputDir):
    for ifilePair in fileDict:
        ifileList = fileDict[ifilePair]
        if not len(ifileList) > 1:
            continue
        mergeFile = outputDir + ifilePair + '.root'
        mergeCommand = 'hadd '+mergeFile + ' '+ ifileList[0]+ ' ' + ifileList[1]
        # uf.runCommand(mergeCommand, True)
        uf.runCommand(mergeCommand, False)
      
   
if __name__ == '__main__':
    main() 