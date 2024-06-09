import ROOT
import re
import os
import array 

import usefulFunc as uf


def main():
    inputRoot = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1lSRBjet2_v76WithVLLAllMass/mc/BDTTrain/v0allVar/inputList_1tau1l.csv.root'
    inputLog = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1lSRBjet2_v76WithVLLAllMass/mc/BDTTrain/v0allVar/training.log'

    outDir = os.path.dirname(inputRoot)
    
    # vListDir = generateVarList(inputRoot, inputLog)
    # submitTrainingJobs(vListDir, inputRoot)

    plot_auc_vs_num_variables(outDir+ '/variableList/' +'BDTTrain/')


def get_auc_and_num_variables(root_file):
    file = ROOT.TFile.Open(root_file)
    if not file or file.IsZombie():
        print(f"Error opening file: {root_file}")
        return None, None

    # Assuming the ROC curve is stored in a TGraph or similar object
    roc_curve = file.Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS")
    if not roc_curve:
        print(f"Could not find ROC curve in file: {root_file}")
        file.Close()
        return None, None

    # Calculate the AUC
    # auc = roc_curve.Integral() / roc_curve.GetN()
    auc = roc_curve.Integral() /  roc_curve.GetNbinsX()

    # Assuming the number of input variables is stored in a specific location in the file
    # This may need to be adjusted based on the actual structure of your ROOT files
    input_variables = file.Get("dataset/TrainTree")
    if not input_variables:
        print(f"Could not find input variables in file: {root_file}")
        file.Close()
        return None, None

    num_variables = input_variables.GetListOfBranches().GetEntries()

    file.Close()
    return auc, num_variables

def plot_auc_vs_num_variables(input_dir):
    aucs = []
    num_vars = []

    # Loop over all ROOT files in the input directory
    for root_file in os.listdir(input_dir):
        if root_file.endswith(".root"):
            full_path = os.path.join(input_dir, root_file)
            auc, num_variables = get_auc_and_num_variables(full_path)
            if auc is not None and num_variables is not None:
                aucs.append(auc)
                num_vars.append(num_variables)

     # Combine the AUCs and num_vars into tuples and sort them
    combined = list(zip(num_vars, aucs))
    combined_sorted = sorted(combined)
    # Unpack the sorted tuples back into separate lists
    num_vars_sorted, aucs_sorted = zip(*combined_sorted)
    num_vars_array = array.array('d', num_vars_sorted)
    aucs_array = array.array('d', aucs_sorted)
    graph = ROOT.TGraph(len(num_vars), num_vars_array, aucs_array)

    graph.SetTitle("AUC as a Function of Number of Input Variables;Number of Input Variables;AUC")
    graph.SetMarkerStyle(20)
    graph.SetMarkerColor(ROOT.kBlue)
    graph.SetLineColor(ROOT.kBlue)

    # Create a canvas and draw the graph
    canvas = ROOT.TCanvas("canvas", "AUC vs. Number of Input Variables", 800, 600)
    graph.Draw("APL")
    canvas.Update()

    # Save the plot as a PNG file
    canvas.SaveAs("auc_vs_num_variables.png")

def submitTrainingJobs(vListDir, inputRoot):
    jobDir = vListDir + 'jobs/'
    uf.checkMakeDir(jobDir)
    exeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/'
    subScript = jobDir + 'submitJobs.sh'

    inputDir = inputRoot.split('/mc/')[0] + '/mc/'
    outDir = vListDir + 'BDTTrain/'
    uf.checkMakeDir(outDir)
    g_weight = 'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight*btagWPMedium_weight'
    channel = '1tau1l'
    ifVLL = ''

    logDir = outDir + 'log/'
    uf.checkMakeDir(logDir)
    with open(subScript, 'w') as sub_script:
        sub_script.write('#!/bin/bash\n')
        for iList in os.listdir(vListDir):
            if not iList.endswith('.csv'): continue
            iListPath = vListDir + iList
            command = './my_program {} {} 0 {} {} {} {}'.format(inputDir, outDir, iListPath, g_weight, channel, ifVLL)
            makeIjob(command, exeDir, jobDir + iList + '.sh')

            sub_script.write('hep_sub {} -o {} -e {}\n'.format(jobDir + iList + '.sh', logDir+iList+'.log', logDir+iList+'.err'))

    os.system('chmod 777 {}'.format(subScript))
    print('subjobs: ', subScript)

    # uf.submitJobs(subScript) 
    os.system('bash {}'.format(subScript))


def makeIjob(run, exeDir, jobName):
    with open(jobName, 'w') as job_script:
        job_script.write("#!/bin/bash\n")
        job_script.write("cd {}\n".format(exeDir))
        job_script.write(run)
    os.system('chmod 777 {}'.format(jobName))
    print('done writing job: ', jobName)


def generateVarList(inputRoot, inputLog):
    # inputRoot = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLAllMass/mc/BDTTrain/v0allVar/inputList_1tau1l.csv.root'
    # inputLog = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLAllMass/mc/BDTTrain/v0allVar/training.log'

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

    return vListDir




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
