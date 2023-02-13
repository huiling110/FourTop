import csv
import os

import usefulFunc as uf
import ttttGlobleQuantity as gq

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v2FR_vetoPOGMuLEleV/'

    inputDirDic = uf.getDirDic(inputDir) 
    try:
        checkJobStatus(inputDirDic)
    except ValueError as e:
        print(e)


def checkJobStatus(inputDirDic):
    #check if any input file missing
    inputList = os.listdir(inputDirDic['mc']  ) + os.listdir(inputDirDic['data']) 
    for i, ipro in enumerate(inputList):
        inputList[i] = ipro.replace('.root', '')
    
    allSubPros = list(gq.histoGramPerSample.keys())[:] #copy
    era = uf.getEraFromDir(inputDirDic['mc']) 
    allSubProsNew = []
    for isub in allSubPros:
        if 'jetHT' in isub and (not era in isub): continue
        allSubProsNew.append(isub)    
            # print('remove data: ', isub)
   
    print('subProcess from inputDir:              ', inputList)
    print('\n')
    print('all subProcess removing non year data :', allSubProsNew) 
    print('\n')
    
    missingPro = []
    for iPro in allSubProsNew :
        if not iPro in inputList:
            missingPro.append(iPro)
    if len(missingPro) >0 :
        raise ValueError('missing some sub processes: ', missingPro)
        
    for ifile in os.listdir(inputDirDic['mc'] +'/log/'):
        if not 'err' in ifile: continue
        if not checkWordInFile( inputDirDic['mc'] +'log/' + ifile ):
            print('job not successful: ', ifile)
                    
def checkWordInFile( file, word='Terminate' ):
    inFile = False
    print('file read: ', file)
    with open(file, 'r') as file:
        reader = csv.reader(file )
        for row in reader:
            # print(row)
            if word in row[0]:
                   inFile = True
    print(inFile)
    return inFile


if __name__=='__main__':
    main()
    