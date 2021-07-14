
import ROOT
import os
import csv


def getAUCfromLog( logDir, histo):
    for entry in os.listdir( logDir ):
        if '.err' in entry:
            continue # The continue statement is used to skip the rest of the code inside a loop for the current iteration only. 
        #  print( entry)
        vListNum = entry[:-4]
        vListNum = vListNum[12:]
        #  print( vListNum )

        AUC_BDT, AUC_BDTG = getROC( logDir+entry)
        print( AUC_BDT, AUC_BDTG)


        #  getROC( logDir+entry)



def getROC( logFile):
    print( 'reading ', logFile, '\n')
    #  with open( logFile , "rb") as csv_file:
    with open( logFile ) as csv_file:
        csv_reader = csv.reader( csv_file, delimiter=':')
        ROCline = 0
        line = 0
        AUC_BDT = 0
        AUC_BDTG = 0
        for irow in csv_reader: # is seems log can contain strange char
            #  print( irow)
            #  print( len(irow))
            line+=1
            if len(irow) > 3:
                if 'ROC-integ' in irow[3]:
                    print( irow)
                    ROCline = line
            if line == ROCline +1:
                #  print( line )
                #  print( irow)
                if len(irow)>2:
                    AUC_BDT = irow[2]
            if line == ROCline+ 2:
                if len(irow)>2:
                    AUC_BDTG = irow[2]
    return AUC_BDT, AUC_BDTG



if __name__ == '__main__':
    logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l/log/'
    h_BDT = ROOT.TH1F("AUC", "AUC", 50, 0, 50 )
    getAUCfromLog( logDir, h_BDT )
