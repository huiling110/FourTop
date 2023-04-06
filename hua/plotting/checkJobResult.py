import csv
import os

import ROOT
import ttttGlobleQuantity as gq
import usefulFunc as uf


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v2FR_vetoPOGMuLEleV/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v2FR_vetoPOGlepL/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v52noHLTButPreSelection/mc/variableHists_v2HLTweight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v45newLepBugFixed/mc/variableHists_v1FR_vetoNewLepL_repeat/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v45newLepBugFixed/mc/variableHists_v0FR_newLep/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v1FR_applicationNewTitle/'

    # inputDirDic = uf.getDirDic(inputDir) 
    # era = uf.getEraFromDir(inputDir)
    # checkJobStatus(inputDirDic)
    
    #check object selection jobs 
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD//UL2016_preVFP/v46addPOGIDL/'
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD//UL2016_preVFP/v45newLepBugFixed/'
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD//UL2016_preVFP/v52noHLTButPreSelection/'
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v52noHLTButPreSelection/'
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v52noHLTButPreSelection/'
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD//UL2016_postVFP/v54noHLTButPreMetFixed/'
    obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v56NoHLTButPre/'
    era = uf.getEraFromDir(obDir)
    checkOSJobs(obDir, era)
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD//UL2016_postVFP/v46addPOGIDL/'
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v45newLepBugFixed/'
    # obDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v49FixedPileUpJERAndTES/'
    # checkOSJobs(obDir, '2016postVFP')
    
    # mvDir = inputDir[:inputDir.find('variableHist')]
    # mvDir = inputDir[:inputDir.find('mc')]
    # mvDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0LepLAdded_v46addPOGIDL/'
    # mvDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0LepLAdded_v46addPOGIDL/'
    # mvDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0LepLAdded_v45newLepBugFixed/'
    # mvDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0LepLAdded_v45newLepBugFixed/'\
    # mvDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v52noHLTButPreSelection/'
    # checkMVJobs(mvDir)
    
    
    
    
    
    
    
def checkOSJobs(obDir, era='2016preVFP'):
    nanoDirDic = {
        '2016postVFP': '/publicfs/cms/data/TopQuark/nanoAOD/2016/',
        '2016preVFP': '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/',
        '2017': '/publicfs/cms/data/TopQuark/nanoAOD/2017/',
        '2018': '/publicfs/cms/data/TopQuark/nanoAOD/2018/',
    }
    nanoDir = nanoDirDic[era]
    print('inputNano dir: ', nanoDir)
    fileDic = getProcessFileDic(nanoDir, era)
    print(fileDic)
    print('\n')
    
    OSfileDic = getProcessFileDic(obDir, era, True)
    print(OSfileDic)
    print('\n')
    
    if not fileDic==OSfileDic:
        print('os file not the same with nanofile')
    else:
        print('os file the same with nanofile')
    check2Dic( fileDic['mc'], OSfileDic['mc'])
    check2Dic( fileDic['data'], OSfileDic['data'])

    # checkLogOB(obDir)

def check2Dic( dict1, dict2):
    # get the keys that are in dict1 but not in dict2
    diff_keys_dict1 = set(dict1.keys()) - set(dict2.keys())
    # get the keys that are in dict2 but not in dict1
    diff_keys_dict2 = set(dict2.keys()) - set(dict1.keys())
    # get the keys that are in both dict1 and dict2
    common_keys = set(dict1.keys()) & set(dict2.keys())
    # get the keys that have different values in dict1 and dict2
    # diff_values = set(k for k in common_keys if dict1[k] != dict2[k])
    # diff_values = set(k for k in common_keys if list(set(dict2[k])-set( dict2[k]))
    diff_values = []
    for k in common_keys:
        if len(list(set(dict1[k])-set(dict2[k])))>0 or len( list(set(dict2[k])-set(dict1[k])) )>0:
            diff_values.append(k)
    # combine the differences into a single dictionary
    diff_dict = {}
    for k in diff_keys_dict1:
        diff_dict[k] = dict1[k]
    for k in diff_keys_dict2:
        diff_dict[k] = dict2[k]
    for k in diff_values:
        diff_dict[k] = (dict1[k], dict2[k])
    print('different: ', diff_dict)
    # for i in diff_dict:
    if len(diff_values)>0: 
        
        print('different outTree files in processes', diff_values)
        for k in diff_values:
            print( list(set(dict2[k])-set(dict1[k])))
            print( list(set(dict1[k])-set(dict2[k])))
        
        
    
    
def checkLogOB(obDir):
    print('start to check log dir')
    obDirDic={}
    obDirDic['mc']=obDir+'mc/'
    obDirDic['data']=obDir+'data/'
    for ikey in obDirDic.keys():
        for isub in os.listdir(obDirDic[ikey]):
            checkLogDir(obDirDic[ikey]+isub+'/log/')
                
         
    
    
def getProcessFileDic(nanoDir, era, isOB=False):
    fileDir = {}
    fileDir['mc']={}
    fileDir['data']={}
    subProList = getAllSub(era)
    print('all subProcess considered: \n', subProList)
    mcDir = nanoDir+'mc/'
    for ipro in subProList:
        if 'jetHT' in ipro or 'singleMu' in ipro:
            fileDir['data'][ipro] = []
            fileDir['data'][ipro] = getCheckNanoFile(nanoDir+'data/'+ipro+ '/', isOB)
        else:
            fileDir['mc'][ipro] = []
            fileDir['mc'][ipro] = getCheckNanoFile(mcDir+ipro+ '/', isOB)
    # print( fileDir)
    return fileDir
        
def getCheckNanoFile(dir, isOB=False, ifCheckNano=False):
    fileList = []
    for ifile in os.listdir(dir):
        if not '.root' in ifile: continue
        fileList.append(ifile)
        if ifCheckNano:
            rootF = ROOT.TFile(dir+ifile, 'READ')
            if rootF.IsZombie():
                print('BAD!!! file corrupt!!! ', ifile )
            rootF.Close()
    sorted(fileList)
    return fileList        
    
    
    
def checkMVJobs(mvDir):
    mvDic = expandDirDic(mvDir)
    for idir in mvDic.keys():
        logDir = mvDic[idir] + 'log/'
        checkLogDir(logDir)
       
def expandDirDic( dir):
    dirDic={}
    dirDic['mc'] = dir+'mc/'
    dirDic['data'] = dir+'data/'
    return dirDic

        
def getAllSub(era):
    #get the all sub processes removing the other year data sub processes
    #era can be 2016 or '2016preVPF'
    dic={
        '2016postVFP': ['jetHT_2016F',  'jetHT_2016G', 'jetHT_2016H', 'singleMu_2016F',  'singleMu_2016G', 'singleMu_2016H'],
        '2016preVFP': ['jetHT_2016B_v1', 'jetHT_2016B_v2','jetHT_2016C', 'jetHT_2016D', 'jetHT_2016E', 'jetHT_2016F_hipm',
                       'singleMu_2016B_v1', 'singleMu_2016B_v2','singleMu_2016C', 'singleMu_2016D', 'singleMu_2016E', 'singleMu_2016F_hipm'],
    }
    allSubPros = list(gq.histoGramPerSample.keys())[:] #copy
    allSubProsNew = []
    for isub in allSubPros:
        if era=='2016preVFP' or era=='2016postVFP':
            if 'jetHT' in isub and not ( isub in dic[era] ): continue
            if 'singleMu' in isub and not ( isub in dic[era] ): continue
        else: 
            if 'jetHT' in isub and (not era in isub): continue
            if 'singleMu' in isub and (not era in isub): continue
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
    allSubProsNew = getAllSub(era) 
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
    print('checking log dir: ', logDir)
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
            if len(row) <1: continue
            if word in row[0]:
                   inFile = True
    # print(inFile)
    return inFile


if __name__=='__main__':
    main()
    