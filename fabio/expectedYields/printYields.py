import math
from tabulate import tabulate
import ROOT
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-c', type=str, default='1tau0L', help = 'category')

FLAGS = parser.parse_args()
cat = FLAGS.c

inputfile  = ROOT.TFile.Open("expectedYields_output.root")

LUMI2016 = 35900.0

files = {

    "tttt": 0.01197,

    "ttbar-FH": 373.0,
    "ttbar-SL": 367.0,
    "ttbar-DL": 90.6,

    "QCD_HT300to500": 347700.0,
    "QCD_HT500to700": 32100.0,
    "QCD_HT700to1000": 6831.0,
    "QCD_HT1000to1500": 1207.0,
    "QCD_HT1500to2000": 119.9,
    "QCD_HT2000toInf": 25.24,

    "ttW+jets": 0.2014,
    "ttZ+jets": 0.6559,
    "ttG+jets": 3.697,
    "ttH": 0.3372,

}

categories = ["1tau0L", "1tau1L", "1tau2L", "1tau3L", "2tau0L", "2tau1L", "2tau2L"]

yields = {}
for i in range(7) :
    yields[i] = {}

for idx, cat in enumerate(categories):
    for file in files :
        genEvts = inputfile.Get("totalWeight_"+file)
        h = inputfile.Get("h_"+cat+file)
        h.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
        #print(h.GetName(), end=',')
        yields[idx][file] = h.Integral(-1,-1)

yields_to_print = []
#yields_to_print.append(["", "tttt", "ttbar", "QCD", "tt+X"])
for i in range (7):
    yields_to_print.append([categories[i], 
                            yields[i]["tttt"], 
                            yields[i]["ttbar-FH"]+yields[i]["ttbar-SL"]+yields[i]["ttbar-DL"], yields[i]["QCD_HT300to500"]+yields[i]["QCD_HT500to700"]+yields[i]["QCD_HT700to1000"]+yields[i]["QCD_HT1000to1500"]+yields[i]["QCD_HT1500to2000"]+yields[i]["QCD_HT2000toInf"],
                            yields[i]["ttW+jets"]+yields[i]["ttZ+jets"]+yields[i]["ttG+jets"]+yields[i]["ttH"]])

print(tabulate(yields_to_print, tablefmt="latex", floatfmt=".3f"))
