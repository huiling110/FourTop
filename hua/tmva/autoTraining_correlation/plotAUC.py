
import ROOT
import os
import csv
#  import array
from array import array


def getAUCfromLog( logDir, histo):
    for entry in os.listdir( logDir ):
        if '.err' in entry:
            continue # The continue statement is used to skip the rest of the code inside a loop for the current iteration only. 
        #  print( entry)
        vListNum = entry[:-4]
        vListNum = vListNum[12:]
        vListNum = int(vListNum)
        print( vListNum )

        AUC_BDT, AUC_BDTG = getROC( logDir+entry)
        print( AUC_BDT, AUC_BDTG)

        histo.SetBinContent( vListNum, AUC_BDT)


def getAUCToTGragh( logDir):
    x, y = array( 'd' ), array( 'd' )
 
#  for i in range( n ):
   #  x.append( 0.1*i )
   #  y.append( 10*sin( x[i]+0.2 ) )
   #  print(' i %i %f %f ' % (i,x[i],y[i]))

    n = 0
    for entry in os.listdir( logDir ):
        
        if '.err' in entry:
            continue # The continue statement is used to skip the rest of the code inside a loop for the current iteration only. 
        #  print( entry)
        vListNum = entry[:-4]
        vListNum = vListNum[12:]
        vListNum = int(vListNum)
        print( vListNum )

        AUC_BDT, AUC_BDTG = getROC( logDir+entry)
        print( AUC_BDT, AUC_BDTG)
        x.append( vListNum )
        y.append( AUC_BDT )
        print(' i %i %f %f ' % ( n,x[n],y[n]))

        n = n+1


    c1 = ROOT.TCanvas( 'c1', 'A Simple Graph Example', 200, 10, 700, 500 )
    #  c1.SetFillColor( 42 )
    c1.SetGrid()
 
    gr = ROOT.TGraph( n, x, y )
    gr.SetLineColor( 2 )
    gr.SetLineWidth( 4 )
    gr.SetMarkerColor( 4 )
    gr.SetMarkerStyle( 21 )
    gr.SetTitle( 'AUC vs No. of Variables ' )
    gr.GetXaxis().SetTitle( 'number of variables' )
    gr.GetYaxis().SetTitle( 'AUC' )
    #  gr.Draw( 'ACP' )
    #  gr.Draw('AP')
    gr.Draw('APL')
    
    c1.SaveAs("/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/output/AUC_test2.png")
    #  return gr

    


#


def getROC( logFile):
    print( 'reading ', logFile, '\n')
    #  with open( logFile , "rb") as csv_file:
    with open( logFile ) as csv_file:
        csv_reader = csv.reader( csv_file, delimiter=':')
        ROCline = 0
        line = 0
        AUC_BDT = 0.0
        AUC_BDTG = 0.0
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
        csv_file.close()
    return float(AUC_BDT), float(AUC_BDTG)



if __name__ == '__main__':
    logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l/log/'
    #  h_BDT = ROOT.TH1F("AUC", "AUC", 50, 0, 50 )
    #  getAUCfromLog( logDir, h_BDT )
    getAUCToTGragh( logDir )



