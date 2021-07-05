
import ROOT
#  from ROOT import *
#  import array
#  import math

import csv



def main(  TMVAlog = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l_forvariables.log"):
    
    #the first line identifies each piece of datain other words, the name of a data column
    
    initialVariableList = [] #Buffer list

    #  with open(TMVAlog) as csv_file:
    with open(TMVAlog) as csv_file, open("variableList.csv", "w+") as to_file2:
        csv_reader = csv.reader(csv_file, delimiter=':')
        writer2 = csv.writer(to_file2, delimiter=":")
        linecount = 0
        SPline = 0
        for irow in csv_reader: 
            #Each row returned by the reader is a list of String elements containing the data found by removing the delimiters.
            #  if linecount<300:
                #  print(irow[0])
            #  if irow[0] == "number of branches":
                #  print(irow[1])

            #get the SP part
            if irow[0] == "IdTransformation         ":
                print(irow[1])
                SPline = linecount+2
            if (linecount == SPline and not(linecount == 0) ):
                #  print(irow)
                if len(irow)>3:
                    if not(irow[2] == ' -----------------------------------------------------') or not(irow[1]=='Factory                  ') :
                        print(irow)
                        print(irow[2])
                        #  writer2.writerow(irow[2])
                        writer2.writerow([irow[2]])
                        initialVariableList.append(irow[2])


                if not irow[0] == 'Factory                  ':
                    SPline += 1
                    #  print(irow[2])
                    #  data.append(irow[2])

            linecount +=1


    print( 'initialVariableList: ', initialVariableList)


    #  with open("the_new_csv.csv", "w+") as to_file:
        #  writer = csv.writer(to_file, delimiter=":")
        #  for new_row in data:
            #  writer.writerow(new_row)


#  def removeBjetTL( vlist) :


def createNextVariableList_correlation( vlist):
    inputFile = TFile("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l_forvariables_variables.root")
    inputFile.print()






if __name__ == '__main__':
	main()
