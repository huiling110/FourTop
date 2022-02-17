import pandas as pd
import argparse
import sys

parser = argparse.ArgumentParser()

parser.add_argument('--year', type=str, default='UL2016_preVFP', help='Year of data taking')

FLAGS = parser.parse_args()
year = FLAGS.year

file_dict = {
    
    "UL2016_preVFP" : "reshaping_deepJet_106XUL16preVFP_v2",
    "UL2016_postVFP" : "reshaping_deepJet_106XUL16postVFP_v3",
    "UL2017" : "reshaping_deepJet_106XUL17_v3",
    "UL2018" : "reshaping_deepJet_106XUL18_v2",

}

if year not in file_dict: sys.exit("Specified year is invalid. Please pick one of the following: UL2016_preVFP, UL2016_postVFP, UL2017, UL2018")

outputfile = file_dict[year] + "_dropLines.csv"
with open(outputfile, "w"):
    df = pd.read_csv(file_dict[year] + ".csv")
    print(df.head(10))
    #get a list of all systematic sources available in the .csv file
    syst_to_remove = df.sysType.unique().tolist()
    #only consider jes-related sources
    for element in syst_to_remove:
        if "jes" not in element: syst_to_remove.remove(element)
    #remove from list up_jes and down_jes: you want to save tham
    syst_to_remove.remove("up_jes")
    syst_to_remove.remove("down_jes")
    for syst in syst_to_remove:
        df = df[df.sysType != syst]
    print(df.shape)
    df.to_csv(outputfile, index=False)
