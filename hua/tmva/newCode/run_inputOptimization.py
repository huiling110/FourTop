import ROOT
import re
import os 

import usefulFunc as uf


def main():
    
    generateVarList()
    # submitTrainingJobs()
    # plotAUC()

def generateVarList():
    # inputRoot = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLAllMass/mc/BDTTrain/v0allVar/inputList_1tau1l.csv.root'
    # inputLog = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLAllMass/mc/BDTTrain/v0allVar/training.log'
    inputRoot = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1lSRBjet2_v76WithVLLAllMass/mc/BDTTrain/v0allVar/inputList_1tau1l.csv.root'
    inputLog = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1lSRBjet2_v76WithVLLAllMass/mc/BDTTrain/v0allVar/training.log'

    variables = get_variable_separations(inputLog)
    variables = {var: sep for var, sep in variables.items() if sep >= 0.001}
    variables = {var: sep for var, sep in variables.items() if not 'tausTT' in var}

    for i, sep in variables.items():
        print(i, sep)

    outDir = os.path.dirname(inputRoot)
    vListDir = outDir + '/variableList/'
    uf.checkMakeDir(vListDir)
    vListList = createNextVariableList_correlation(variables, inputRoot)
    writeListListToFile( vListList, vListDir)




def createNextVariableList_correlation( vlist, TMVAroot):
    #only stores variable in vlist
    #  inputFile = ROOT.TFile("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l_forvariables_variables.root")
    inputFile = ROOT.TFile( TMVAroot )
    inputFile.Print()
    h2 = inputFile.Get("dataset/CorrelationMatrixS"); #TH2F
    #  h2.Print()

    #getting the correlaiton list out of root TH2F
    #  print( h2.GetXaxis().GetBinLabel(1))
    binNum = h2.GetNbinsX()
    print( 'variable number in TH2F: ', binNum)
    ibinX = 1
    #  ibinY = 1
    correlation_list = [] #list of sets
    while ibinX<binNum+1:
        #  print(ibinX)
        ibinY = 1
        while ibinY<ibinX:
            #  print(ibinY)
            xBinLabel = h2.GetXaxis().GetBinLabel(ibinX)
            yBinLabel = h2.GetYaxis().GetBinLabel(ibinY)
            # if xBinLabel in vlist and yBinLabel in vlist:
            if xBinLabel in vlist.keys() and yBinLabel in vlist.keys():
                icorrelation = abs( h2.GetBinContent( ibinX, ibinY) )
                correlation_list.append( [xBinLabel, yBinLabel, icorrelation] )
            ibinY+=1
        ibinX+=1

    #  print( 'correlaition list: ', correlation_list)
    correlation_list.sort( key=takeThird, reverse = True )
    print('\n')
    print( 'list after sorting: ', correlation_list)
    print('\n')

    #for simplisity, not taking multiple same correlation into account for now
    tempList = list(vlist.keys())
    listLenth = len(vlist)
    variableListList = []
    for correlationPair in correlation_list:
        if len(tempList)==listLenth:
            variableListList.append(tempList[:])# The notation list[:] creates a copy of the list.
            listLenth = listLenth-1
        firstVariable = correlationPair[0]
        secondVariable = correlationPair[1]
        #  print( 'tempList: ', len(tempList), tempList)
        if firstVariable in tempList and secondVariable in tempList:
            # if vlist.index( firstVariable) > vlist.index( secondVariable ):
            if vlist[ firstVariable ] < vlist[ secondVariable ]:
                tempList.remove( firstVariable)
                #  print( 'removed: ', secondVariable )
            else:
                tempList.remove( secondVariable)
                #  print( 'removed: ', firstVariable )
    return variableListList 

def takeThird( elem ):
    return elem[2]

def writeListListToFile( listList, fileDir ):
    for iList in listList:
        writeListToFile( iList, fileDir )


def writeListToFile( iList, fileDir ):
    iFileName = fileDir + 'varibleList_'+str(len(iList)) + '.csv'
    print( 'writing file: ', iFileName )
    output = open(iFileName,'wt')
    for ele in iList:
        output.write(ele+'\n')
    output.close()

def get_variable_separations(log_file):
    variable_separations = {}
    start_copying = False
    with open(log_file, 'r') as f:
        lines = f.readlines()
        for line in lines:
            if 'IdTransformation         : Ranking result (top variable is best ranked)' in line:
                start_copying = True
                continue  # Skip the current line and start from the next one
            
            if start_copying:
                # Look for lines that contain separation information
                match = re.match(r'\s*:\s+\d+\s+:\s+(\S+)\s+:\s+([\d\.eE\+\-]+)', line)
                if match:
                    variable = match.group(1)
                    separation = float(match.group(2))
                    variable_separations[variable] = separation
    return variable_separations



if __name__=='__main__':
    main()
