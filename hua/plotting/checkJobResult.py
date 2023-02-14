import csv
import os

import usefulFunc as uf
import ttttGlobleQuantity as gq

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v2FR_vetoPOGMuLEleV/'

    inputDirDic = uf.getDirDic(inputDir) 
    era = uf.getEraFromDir(inputDir)
    # try:
    # checkJobStatus(inputDirDic)
    # except ValueError as e:
        # print(e)
    
    # mvDir = inputDir[:inputDir.find('variableHist')]
    # print(mvDir)
    # checkMVJobs(mvDir)
   
    obDir = inputDir[:inputDir.find('forMVA')] 
    checkOSJobs(obDir, '2016preVFP')
    
def checkOSJobs(obDir, era='2016preVFP'):
    nanoDirDic = {
        '2016postVFP': '/publicfs/cms/data/TopQuark/nanoAOD/2016/',
        '2016preVFP': '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/',
        '2017': '/publicfs/cms/data/TopQuark/nanoAOD/2017/',
        '2018': '/publicfs/cms/data/TopQuark/nanoAOD/2018/',
    }
    # if era=='2016':
    #     dirDic = {
    #         '2016preVFP': obDir+'UL2016_preVFP/',
    #         '2016postVFP': obDir+'UL2016_postVFP/',
    #     }
    # for idir in dirDic.keys():
        # print(dirDic[idir])
    nanoDir = nanoDirDic[era]
    print('inputNano dir: ', nanoDir)
    getProcessFileDic(nanoDir, era)
    
def getProcessFileDic(nanoDir, era):
    fileDir = {}
    fileDir['mc']={}
    fileDir['data']={}
    subProList = getAllSub(era)
    print('all subProcess considered: \n', subProList)
    mcDir = nanoDir+'mc/'
    for ipro in subProList:
        fileDir['mc'][ipro] = []
        # for ifile in os.listdir(mcDir+ipro+'/'):
            # print(ifile)
        
        
    
    
    
def checkMVJobs(mvDir):
    era = uf.getEraFromDir(mvDir)
    if era=='2016':
        dirPre = mvDir.replace('2016', '2016preVFP')
        print(dirPre)
        
def getAllSub(era):
    #era can be 2016 or '2016preVPF'
    dic={
        '2016postVFP': ['jetHT_2016F', 'jetHT_2016F_hipm', 'jetHT_2016G', 'jetHT_2016H'],
        '2016preVFP': ['jetHT_2016B_v1', 'jetHT_2016B_v2','jetHT_2016C', 'jetHT_2016D', 'jetHT_2016E'],
    }
    allSubPros = list(gq.histoGramPerSample.keys())[:] #copy
    allSubProsNew = []
    for isub in allSubPros:
        if era=='2016preVFP' or era=='2016postVFP':
            if 'jetHT' in isub and not ( isub in dic[era] ): continue
        else: 
            if 'jetHT' in isub and (not era in isub): continue
        allSubProsNew.append(isub)    
        # print('remove data: ', isub)
    return allSubProsNew
        

def checkJobStatus(inputDirDic):
    #check if any input file missing
    inputList = os.listdir(inputDirDic['mc']  ) + os.listdir(inputDirDic['data']) 
    for i, ipro in enumerate(inputList):
        inputList[i] = ipro.replace('.root', '')
    inputList.remove('log') 
    inputList.remove('log') 
    inputList.remove('results')
    inputList = sorted(inputList)
   
    era = uf.getEraFromDir(inputDirDic['mc']) 
    getAllSub(era) 
    allSubProsNew = sorted(allSubProsNew)
   
    print('subProcess from inputDir:\n', inputList)
    print('\n')
    print('all subProcess removing non year data :\n', allSubProsNew) 
    print('\n')
    
    missingPro = list(filter(lambda x: x not in inputList, allSubProsNew))
    print( 'in allSub not in dir:\n' , missingPro)  
    print( 'in allSub not in dir:\n' ,list(filter(lambda x: x not in allSubProsNew, inputList))  )
    if len(missingPro) >0 :
        # raise ValueError('missing some sub processes: ', missingPro)
        print('WARNING!!! sub process file not exist!!!\n')
    
    
    checkLogDir( inputDirDic['mc'] +'/log/')    
    checkLogDir( inputDirDic['data'] +'/log/')    
            
def checkLogDir(logDir):            
    for ifile in os.listdir(logDir):
        if not 'err' in ifile: continue
        if not checkWordInFile( logDir + ifile ):
            print('job not successful: ', ifile)
            
                    
def checkWordInFile( file, word='Terminate' ):
    inFile = False
    # print('file read: ', file)
    with open(file, 'r') as file:
        reader = csv.reader(file )
        for row in reader:
            # print(row)
            if word in row[0]:
                   inFile = True
    # print(inFile)
    return inFile


if __name__=='__main__':
    main()
    