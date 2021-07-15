import math
from tabulate import tabulate
import ROOT
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-c', type=str, default='1tau0L', help = 'category')

FLAGS = parser.parse_args()
cat = FLAGS.c

inputfile  = ROOT.TFile.Open("QCD_CR_output.root")

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

yields = {}
yields_ctl = {}
for i in range(8) :
    yields[i] = {}
    yields_ctl[i] = {}
for file in files :
    for wp in range(8) :
        genEvts = inputfile.Get("totalWeight_"+file)
        h_yield = inputfile.Get("h_yield_"+cat+"_"+str(wp)+"_"+file)
        h_yield_ctl = inputfile.Get("h_yield_"+cat+"_ctl_"+str(wp)+"_"+file)
        h_yield.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
        h_yield_ctl.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
       
        yields[wp][file] = h_yield.Integral(-1,-1)
        yields_ctl[wp][file] = h_yield_ctl.Integral(-1,-1)
        
tttt = []
ttbar = []
QCD = []
ttX = []
tttt_ctl = []
ttbar_ctl = []
QCD_ctl = []
ttX_ctl = []
tttt.append("tttt")
ttbar.append("tt")
QCD.append("QCD")
ttX.append("tt+X")
tttt_ctl.append("tttt")
ttbar_ctl.append("tt")
QCD_ctl.append("QCD")
ttX_ctl.append("tt+X")
for i in range (8) :
    tttt.append(yields[i]["tttt"])
    ttbar.append(yields[i]["ttbar-FH"] + yields[i]["ttbar-SL"] + yields[i]["ttbar-DL"])
    QCD.append(yields[i]["QCD_HT300to500"] + yields[i]["QCD_HT500to700"] + yields[i]["QCD_HT700to1000"] + yields[i]["QCD_HT1000to1500"] + yields[i]["QCD_HT1500to2000"] + yields[i]["QCD_HT2000toInf"])
    ttX.append(yields[i]["ttW+jets"] + yields[i]["ttZ+jets"] + yields[i]["ttG+jets"] + yields[i]["ttH"])
    tttt_ctl.append(yields_ctl[i]["tttt"])
    ttbar_ctl.append(yields_ctl[i]["ttbar-FH"] + yields_ctl[i]["ttbar-SL"] + yields_ctl[i]["ttbar-DL"])
    QCD_ctl.append(yields_ctl[i]["QCD_HT300to500"] + yields_ctl[i]["QCD_HT500to700"] + yields_ctl[i]["QCD_HT700to1000"] + yields_ctl[i]["QCD_HT1000to1500"] + yields_ctl[i]["QCD_HT1500to2000"] + yields_ctl[i]["QCD_HT2000toInf"])
    ttX_ctl.append(yields_ctl[i]["ttW+jets"] + yields_ctl[i]["ttZ+jets"] + yields_ctl[i]["ttG+jets"] + yields_ctl[i]["ttH"])
yields_to_print = []
yields_to_print_ctl = []
yields_to_print.append(tttt)
yields_to_print.append(ttbar)
yields_to_print.append(QCD)
yields_to_print.append(ttX)
yields_to_print_ctl.append(tttt_ctl)
yields_to_print_ctl.append(ttbar_ctl)
yields_to_print_ctl.append(QCD_ctl)
yields_to_print_ctl.append(ttX_ctl)

print(tabulate(yields_to_print, tablefmt="latex", floatfmt=".0f"))
print(tabulate(yields_to_print_ctl, tablefmt="latex", floatfmt=".0f"))
#print(tabulate(yields_to_print, floatfmt=".2f"))
#print(tabulate(yields_to_print_ctl, floatfmt=".2f"))
