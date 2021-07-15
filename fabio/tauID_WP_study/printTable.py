import math
from tabulate import tabulate
import ROOT
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-c', type=str, default='1tau0L', help = 'category')

FLAGS = parser.parse_args()
cat = FLAGS.c

#inputfile  = ROOT.TFile.Open("tauID_WP_study_output.root")
inputfile  = ROOT.TFile.Open("tauID_WP_study_output_gencatwithNlep.root")
#inputfile  = ROOT.TFile.Open("tauID_WP_study_saving_hBefcorrected_output.root")

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

yields_significance = {}
yields_recoeff_bef = {}
yields_recoeff_aft = {}
"""
yields_sig = {}
yields_ttbar = {}
yields_QCD = {}
yields_ttX = {}
"""
if cat != 'nocat':
    yields_recoeff_gen_bef = {}
    yields_recoeff_gen_aft = {}
yields_recopurity_bef = {}
yields_recopurity_aft = {}

for i in range(8) :
    yields_significance[i] = {}
    yields_recoeff_bef[i] = {}
    yields_recoeff_aft[i] = {}
    """ 
    yields_sig[i] = {}
    yields_ttbar[i] = {}
    yields_QCD[i] = {}
    yields_ttX[i] = {}
    """
    if cat != 'nocat':
        yields_recoeff_gen_bef[i] = {}
        yields_recoeff_gen_aft[i] = {}
    yields_recopurity_bef[i] = {}
    yields_recopurity_aft[i] = {}

for file in files :
    for wp in range(8) :
        genEvts = inputfile.Get("totalWeight_"+file)
        h_significance = inputfile.Get("h_significance_"+cat+"_"+str(wp)+"_"+file)
        h_recoeff_bef = inputfile.Get("h_recoeff_"+cat+"_bef_"+str(wp)+"_"+file)
        h_recoeff_aft = inputfile.Get("h_recoeff_"+cat+"_aft_"+str(wp)+"_"+file)
        if cat != 'nocat':
            h_recoeff_gen_bef = inputfile.Get("h_recoeff_gen"+cat+"_bef_"+str(wp)+"_"+file)
            h_recoeff_gen_aft = inputfile.Get("h_recoeff_gen"+cat+"_aft_"+str(wp)+"_"+file)
        h_recopurity_bef = inputfile.Get("h_recopurity_"+cat+"_bef_"+str(wp)+"_"+file)
        h_recopurity_aft = inputfile.Get("h_recopurity_"+cat+"_aft_"+str(wp)+"_"+file)

        h_significance.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
        h_recoeff_bef.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
        h_recoeff_aft.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
        if cat != 'nocat':
            h_recoeff_gen_bef.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
            h_recoeff_gen_aft.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
        h_recopurity_bef.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())
        h_recopurity_aft.Scale(files[file] * LUMI2016 / genEvts.GetSumOfWeights())

        yields_significance[wp][file] = h_significance.Integral(-1,-1)
        yields_recoeff_bef[wp][file] = h_recoeff_bef.Integral(-1,-1)
        yields_recoeff_aft[wp][file] = h_recoeff_aft.Integral(-1,-1)
        if cat != 'nocat':
            yields_recoeff_gen_bef[wp][file] = h_recoeff_gen_bef.Integral(-1,-1)
            yields_recoeff_gen_aft[wp][file] = h_recoeff_gen_aft.Integral(-1,-1)
        yields_recopurity_bef[wp][file] = h_recopurity_bef.Integral(-1,-1)
        yields_recopurity_aft[wp][file] = h_recopurity_aft.Integral(-1,-1)
        
tttt = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
ttbar = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
QCD = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
ttX = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
B_sig = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
B_recoeff_bef = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
B_recoeff_aft = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
if cat != 'nocat':
    B_recoeff_gen_bef = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    B_recoeff_gen_aft = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
B_recopurity_bef = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
B_recopurity_aft = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
S_significance = []
B_significance = []

for i in range (8) :
    #print(i)
    tttt[i] = yields_significance[i]["tttt"]
    ttbar[i] = yields_significance[i]["ttbar-FH"] + yields_significance[i]["ttbar-SL"] + yields_significance[i]["ttbar-DL"]
    QCD[i] = yields_significance[i]["QCD_HT300to500"] + yields_significance[i]["QCD_HT500to700"] + yields_significance[i]["QCD_HT700to1000"] + yields_significance[i]["QCD_HT1000to1500"] + yields_significance[i]["QCD_HT1500to2000"] + yields_significance[i]["QCD_HT2000toInf"]
    ttX[i] = yields_significance[i]["ttW+jets"] + yields_significance[i]["ttZ+jets"] + yields_significance[i]["ttG+jets"] + yields_significance[i]["ttH"]
    S_significance.append(yields_significance[i]["tttt"])
    for file in files :
        B_sig[i] += yields_significance[i][file]
        B_recoeff_bef[i] += yields_recoeff_bef[i][file]
        B_recoeff_aft[i] += yields_recoeff_aft[i][file]
        if cat != 'nocat':
            B_recoeff_gen_bef[i] += yields_recoeff_gen_bef[i][file]
            B_recoeff_gen_aft[i] += yields_recoeff_gen_aft[i][file]
        B_recopurity_bef[i] += yields_recopurity_bef[i][file]
        B_recopurity_aft[i] += yields_recopurity_aft[i][file]
        
    B_sig[i] = B_sig[i] - yields_significance[i]["tttt"]
    B_recoeff_bef[i] = B_recoeff_bef[i] - yields_recoeff_bef[i]["tttt"]
    B_recoeff_aft[i] = B_recoeff_aft[i] - yields_recoeff_aft[i]["tttt"]
    if cat != 'nocat':
        B_recoeff_gen_bef[i] = B_recoeff_gen_bef[i] - yields_recoeff_gen_bef[i]["tttt"]
        B_recoeff_gen_aft[i] = B_recoeff_gen_aft[i] - yields_recoeff_gen_aft[i]["tttt"]
    B_recopurity_bef[i] = B_recopurity_bef[i] - yields_recopurity_bef[i]["tttt"]
    B_recopurity_aft[i] = B_recopurity_aft[i] - yields_recopurity_aft[i]["tttt"]
    B_significance.append(B_sig[i])

S = []
B = []
Z = []
Z_syst = []
Esig = []
Ebkg = []
if cat != 'nocat':
    Esig_gen = []
    Ebkg_gen = []
Psig = []
Pbkg = []
for i in range (8) :
    S.append(S_significance[i])
    B.append(B_significance[i])
    Z.append( (2 * ( (S_significance[i] + B_significance[i]) * math.log(1 + S_significance[i]/B_significance[i]) - S_significance[i]) )**0.5)
    Z_syst.append(ROOT.RooStats.NumberCountingUtils.BinomialExpZ(S_significance[i]*50.0, B_significance[i], 0.2))
    Esig.append(yields_recoeff_aft[i]["tttt"]/yields_recoeff_bef[i]["tttt"])
    Ebkg.append(B_recoeff_aft[i]/B_recoeff_bef[i])
    if cat != 'nocat':
        Esig_gen.append(yields_recoeff_gen_aft[i]["tttt"]/yields_recoeff_gen_bef[i]["tttt"])
        Ebkg_gen.append(B_recoeff_gen_aft[i]/B_recoeff_gen_bef[i])
    Psig.append(yields_recopurity_aft[i]["tttt"]/yields_recopurity_bef[i]["tttt"])
    Pbkg.append(B_recopurity_aft[i]/B_recopurity_bef[i])
yields_to_print = []
yields_to_print.append(tttt)
yields_to_print.append(ttbar)
yields_to_print.append(QCD)
yields_to_print.append(ttX)
to_print = []
to_print.append(S)
to_print.append(B)
to_print.append(Z)
to_print.append(Z_syst)
to_print.append(Esig)
#if cat != 'nocat':
 #   to_print.append(Esig_gen)
to_print.append(Ebkg)
#if cat != 'nocat':
 #   to_print.append(Ebkg_gen)
to_print.append(Psig)
to_print.append(Pbkg)

print(tabulate(yields_to_print, tablefmt="latex", floatfmt=".3f"))
print(tabulate(to_print, tablefmt="latex", floatfmt=".3f"))
