import math
from tabulate import tabulate
import ROOT
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-c', type=str, default='gen1tau0L', help = 'category')

FLAGS = parser.parse_args()
cat = FLAGS.c

inputfile  = ROOT.TFile.Open("gen_efficiencies_output.root")

LUMI2016 = 35900.0

files = {

    "tttt": 0.01197
   
}

yields_recoeff_bef = {}
yields_recoeff_1m_aft = {}
yields_recoeff_2m_aft = {}

for i in range(8) :
    yields_recoeff_bef[i] = {}
    yields_recoeff_1m_aft[i] = {}
    yields_recoeff_2m_aft[i] = {}

for file in files :
    for wp in range(8) :
        if ('1tau' in cat):
            h_recoeff_bef = inputfile.Get("h_recoeff_"+cat+"_bef_"+str(wp)+"_"+file)
            h_recoeff_aft = inputfile.Get("h_recoeff_"+cat+"_aft_"+str(wp)+"_"+file)
        if ('2tau' in cat):
            h_recoeff_bef = inputfile.Get("h_recoeff_"+cat+"_bef_"+str(wp)+"_"+file)
            h_recoeff_1m_aft = inputfile.Get("h_recoeff_"+cat+"_1m_aft_"+str(wp)+"_"+file)
            h_recoeff_2m_aft = inputfile.Get("h_recoeff_"+cat+"_2m_aft_"+str(wp)+"_"+file)
        if ('1tau' in cat):
            yields_recoeff_bef[wp][file] = h_recoeff_bef.Integral(-1,-1)
            yields_recoeff_1m_aft[wp][file] = h_recoeff_aft.Integral(-1,-1)
        if ('2tau' in cat):
            yields_recoeff_bef[wp][file] = h_recoeff_bef.Integral(-1,-1)
            yields_recoeff_1m_aft[wp][file] = h_recoeff_1m_aft.Integral(-1,-1)
            yields_recoeff_2m_aft[wp][file] = h_recoeff_2m_aft.Integral(-1,-1)

eff_1m = []
eff_2m= []
compl = []

for i in range (8) :
    if ('1tau' in cat):
        eff_1m.append(yields_recoeff_1m_aft[i]["tttt"]/yields_recoeff_bef[i]["tttt"])
        eff_2m.append(float("nan"))
        compl.append(1 - eff_1m[i])
    if ('2tau' in cat):
        eff_1m.append(yields_recoeff_1m_aft[i]["tttt"]/yields_recoeff_bef[i]["tttt"])
        eff_2m.append(yields_recoeff_2m_aft[i]["tttt"]/yields_recoeff_bef[i]["tttt"])
        compl.append(1 - eff_1m[i] - eff_2m[i])
    
to_print = []
to_print.append(eff_1m)
to_print.append(eff_2m)
to_print.append(compl)

print(tabulate(to_print, tablefmt="latex", floatfmt=".4f"))
