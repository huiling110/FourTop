import math
from tabulate import tabulate
import ROOT
import argparse
import numpy as np

inputfile  = ROOT.TFile.Open("scaledYields_output.root")
#inputfile  = ROOT.TFile.Open("scaledYields_output_toptaggerScenario1.root")
#inputfile  = ROOT.TFile.Open("scaledYields_output_toptaggerScenario2.root")
#inputfile  = ROOT.TFile.Open("scaledYields_output_toptaggerScenario3.root")

parser = argparse.ArgumentParser()
parser.add_argument('--no_w', default=False, action='store_true',
                    help='Run the script on histograms with no SF (for debugging purposes)')
parser.add_argument('--raw_entries', default=False, action='store_true',
                    help='Print raw entries (h->GetEntries) instead of yields (h->Integral(-1,-1))')

FLAGS = parser.parse_args()
no_w = FLAGS.no_w
raw_entries = FLAGS.raw_entries

LUMI2016 = 35900.0

files = {

    "tttt": 0.01197,

    "ttbar-FH": 373.0,
    "ttbar-SL": 367.0,
    "ttbar-DL": 90.6,
    
    "QCD_HT200to300": 1721000.0,
    "QCD_HT300to500": 347900.0,
    "QCD_HT500to700": 32000.0,
    "QCD_HT700to1000": 6827.0,
    "QCD_HT1000to1500": 1207.0,
    "QCD_HT1500to2000": 119.9,
    "QCD_HT2000toInf": 25.24,

    "ttW+jets": 0.2014,
    "ttZ+jets": 0.6559,
    "ttG+jets": 3.697,
    "ttH": 0.3372,

    "JetHT_B0": 1.0,
    "JetHT_B1": 1.0,
    "JetHT_C": 1.0,
    "JetHT_D": 1.0,
    "JetHT_E": 1.0,
    "JetHT_F": 1.0,
    "JetHT_G0": 1.0,
    "JetHT_G1": 1.0,
    "JetHT_H0": 1.0,
    "JetHT_H1": 1.0,


}

categories = ["1tau0L", "1tau0L_CR", "1tau0L_VR", "1tau1L", "1tau2L", "1tau3L", "2tau0L", "2tau1L", "2tau2L"]

yields = {}
for category in categories :
    yields[category] = {}

for category in categories :
    for file_ in files :
        if no_w :
            if not "JetHT" in file_ :
                genEvts = inputfile.Get("totalWeight_"+file_)
                h_yield = inputfile.Get("h_"+category+"_noW_"+file_)
                #print("h_"+category+"_"+file_)
                h_yield.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
                if raw_entries:
                    yields[category][file_] = h_yield.GetEntries()
                else:
                    yields[category][file_] = h_yield.Integral(-1,-1)
                    #print(h_yield.Integral(-1,-1))

            else :
                h_yield = inputfile.Get("h_"+category+"_noW_"+file_)
                if raw_entries:
                    yields[category][file_] = h_yield.GetEntries()
                else:
                    yields[category][file_] = h_yield.Integral(-1,-1)
        else :
            if not "JetHT" in file_ :
                genEvts = inputfile.Get("totalWeight_"+file_)
                h_yield = inputfile.Get("h_"+category+"_"+file_)
                print("h_"+category+"_"+file_)
                print(h_yield.Integral(-1,-1))
                h_yield.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
                if raw_entries:
                    yields[category][file_] = h_yield.GetEntries()
                else:
                    yields[category][file_] = h_yield.Integral(-1,-1)
                    #print(h_yield.Integral(-1,-1))

            else :
                h_yield = inputfile.Get("h_"+category+"_"+file_)
                if raw_entries:
                    yields[category][file_] = h_yield.GetEntries()
                else:
                    yields[category][file_] = h_yield.Integral(-1,-1)

dict_to_print = {}
to_print = []

for category in categories :
    dict_to_print[category] = []
    tttt = yields[category]["tttt"]
    dict_to_print[category].append(tttt)
    ttbar = yields[category]["ttbar-FH"] + yields[category]["ttbar-SL"] + yields[category]["ttbar-DL"]
    dict_to_print[category].append(ttbar)
    QCD = yields[category]["QCD_HT200to300"] + yields[category]["QCD_HT300to500"] + yields[category]["QCD_HT500to700"] + yields[category]["QCD_HT700to1000"] + yields[category]["QCD_HT1000to1500"] + yields[category]["QCD_HT1500to2000"] + yields[category]["QCD_HT2000toInf"]
    dict_to_print[category].append(QCD)
    ttX = yields[category]["ttW+jets"] + yields[category]["ttZ+jets"] + yields[category]["ttG+jets"] + yields[category]["ttH"]
    dict_to_print[category].append(ttX)
    total_MC = tttt + ttbar + QCD + ttX
    total_background = total_MC - tttt
    dict_to_print[category].append(total_MC)
    data = yields[category]["JetHT_B0"] + yields[category]["JetHT_B1"] + yields[category]["JetHT_C"] + yields[category]["JetHT_D"] + yields[category]["JetHT_E"] + yields[category]["JetHT_F"] + yields[category]["JetHT_G0"] + yields[category]["JetHT_G1"] + yields[category]["JetHT_H0"] + yields[category]["JetHT_H1"]
    dict_to_print[category].append(data)
    if data !=0 : 
        dict_to_print[category].append((data - total_MC)/data)
    else :
        dict_to_print[category].append(np.nan)
    Z = (2 * ( (tttt + total_background) * math.log(1 + tttt/total_background) - tttt) )**0.5
    dict_to_print[category].append(Z)
    to_print.append(dict_to_print[category])
    
print(tabulate(to_print, tablefmt="latex", floatfmt=".2f"))
