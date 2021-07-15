import math
import ROOT
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-r', type=str, default='CR', help = 'region where to apply the fake rate method (AR or CR for debugging)')
parser.add_argument('-s', type=str, default='QCD', help = 'sample in which you want to apply the fake rate method (QCD or DATA)')

FLAGS = parser.parse_args()
region = FLAGS.r
sample = FLAGS.s

inputfile  = ROOT.TFile.Open("tauF_Pt_"+sample+".root")

LUMI2016 = 35900.0

if sample == "QCD" :
    
    files = {

        "QCD_HT200to300": 1721000.0,
        "QCD_HT300to500": 347700.0,
        "QCD_HT500to700": 32100.0,
        "QCD_HT700to1000": 6831.0,
        "QCD_HT1000to1500": 1207.0,
        "QCD_HT1500to2000": 119.9,
        "QCD_HT2000toInf": 25.24,
        
    }

else: 
    
    files = {

        "JetHT_B0": 1,
        "JetHT_B1": 1,
        "JetHT_C": 1,
        "JetHT_D": 1,
        "JetHT_E": 1,
        "JetHT_F": 1,
        "JetHT_G0": 1,
        "JetHT_G1": 1,
        "JetHT_H0": 1,
        "JetHT_H1": 1,

        
    }

for i, file_ in enumerate(files) :
    if i == 0 :
        if sample == "QCD" :
            genEvts = inputfile.Get("totalWeight_"+file_)
        if region == "CR" :
            #get the total QCD yield in CR, this has already been scaled for the cross sections of each QCD slices, so leave it untouched in the following
            h_QCD_yield = inputfile.Get("h_QCD_yield")
        h_nTaus_FnotT_eta0to1p5 = inputfile.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
        h_nTaus_FnotT_eta1p5to2p3 = inputfile.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
        #h_tauF_pt_eta0to1p5_aft = inputfile.Get("h_tauF_pt_eta0to1p5_aft_"+file_)
        #h_tauF_pt_eta1p5to2p3_aft = inputfile.Get("h_tauF_pt_eta1p5to2p3_aft_"+file_)
        #deltaR_FT_eta0to1p5 = inputfile.Get("deltaR_FT_eta0to1p5_"+file_)
        #deltaR_FT_eta1p5to2p3 = inputfile.Get("deltaR_FT_eta1p5to2p3_"+file_)
        FR_eta0to1p5 = inputfile.Get("FR_eta0to1p5_"+file_)
        FR_eta1p5to2p3 = inputfile.Get("FR_eta1p5to2p3_"+file_)
        
        if sample == "QCD" : 
            h_nTaus_FnotT_eta0to1p5.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            h_nTaus_FnotT_eta1p5to2p3.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            
            #h_tauF_pt_eta0to1p5_aft.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            #h_tauF_pt_eta1p5to2p3_aft.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            #deltaR_FT_eta0to1p5.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            #deltaR_FT_eta1p5to2p3.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            
            FR_eta0to1p5.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            FR_eta1p5to2p3.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())

    else :
        if sample == "QCD" :
            genEvts = inputfile.Get("totalWeight_"+file_)
        h_nTaus_FnotT_eta0to1p5_ = inputfile.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
        h_nTaus_FnotT_eta1p5to2p3_ = inputfile.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
        #h_tauF_pt_eta0to1p5_aft_ = inputfile.Get("h_tauF_pt_eta0to1p5_aft_"+file_)
        #h_tauF_pt_eta1p5to2p3_aft_ = inputfile.Get("h_tauF_pt_eta1p5to2p3_aft_"+file_)
        #deltaR_FT_eta0to1p5_ = inputfile.Get("deltaR_FT_eta0to1p5_"+file_)
        #deltaR_FT_eta1p5to2p3_ = inputfile.Get("deltaR_FT_eta1p5to2p3_"+file_)
        FR_eta0to1p5_ = inputfile.Get("FR_eta0to1p5_"+file_)
        FR_eta1p5to2p3_ = inputfile.Get("FR_eta1p5to2p3_"+file_)

        if sample == "QCD" :
            h_nTaus_FnotT_eta0to1p5_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            h_nTaus_FnotT_eta1p5to2p3_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            
            #h_tauF_pt_eta0to1p5_aft_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            #h_tauF_pt_eta1p5to2p3_aft_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            #deltaR_FT_eta0to1p5_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            #deltaR_FT_eta1p5to2p3_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            
            FR_eta0to1p5_.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            FR_eta1p5to2p3_.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
       
        h_nTaus_FnotT_eta0to1p5.Add(h_nTaus_FnotT_eta0to1p5_)
        h_nTaus_FnotT_eta1p5to2p3.Add(h_nTaus_FnotT_eta1p5to2p3_)
        #h_tauF_pt_eta0to1p5_aft.Add(h_tauF_pt_eta0to1p5_aft_)
        #h_tauF_pt_eta1p5to2p3_aft.Add(h_tauF_pt_eta1p5to2p3_aft_)
        #deltaR_FT_eta0to1p5.Add(deltaR_FT_eta0to1p5_)
        #deltaR_FT_eta1p5to2p3.Add(deltaR_FT_eta1p5to2p3_)
        FR_eta0to1p5.Add(FR_eta0to1p5_)
        FR_eta1p5to2p3.Add(FR_eta1p5to2p3_)

QCD_yield = 0.0
QCD_yield_error = 0.0
#set up two contributions to the erroron QCD_yield: one coming from uncertainty on nTaus_FnotT and one coming from uncertainty on FR
#err_nTaus_FnotT = 0.0
#err_FR = 0.0
for bin_ in range(5) :
    QCD_yield += h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1) * FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))
    QCD_yield += h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1) * FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1))
    QCD_yield_error += (h_nTaus_FnotT_eta0to1p5.GetBinError(bin_+1)/h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1) + max(FR_eta0to1p5.GetEfficiencyErrorLow(bin_+1), FR_eta0to1p5.GetEfficiencyErrorUp(bin_+1))/FR_eta0to1p5.GetEfficiency(bin_+1) + max(FR_eta0to1p5.GetEfficiencyErrorLow(bin_+1), FR_eta0to1p5.GetEfficiencyErrorUp(bin_+1))/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))) * h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1) * FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))
    QCD_yield_error += (h_nTaus_FnotT_eta1p5to2p3.GetBinError(bin_+1)/h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1) + max(FR_eta1p5to2p3.GetEfficiencyErrorLow(bin_+1), FR_eta1p5to2p3.GetEfficiencyErrorUp(bin_+1))/FR_eta1p5to2p3.GetEfficiency(bin_+1) + max(FR_eta1p5to2p3.GetEfficiencyErrorLow(bin_+1), FR_eta1p5to2p3.GetEfficiencyErrorUp(bin_+1))/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1)))*h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1) * FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1))

print("Fake rate method has been applied to {0} in the {1}".format(sample, region))
#print("Number of events by counting: {0} +/- {1}".format( (h_tauF_pt_eta0to1p5_aft.Integral(-1,-1) + h_tauF_pt_eta1p5to2p3_aft.Integral(-1,-1)), (h_tauF_pt_eta0to1p5_aft.Rebin(4).GetBinError(1) + h_tauF_pt_eta1p5to2p3_aft.Rebin(4).GetBinError(1))) )
if region == "CR" :
    print("Number of raw QCD entries: {0}".format( h_QCD_yield.GetEntries() ) )
    print("Number of events by counting: {0} +/- {1}".format( h_QCD_yield.Integral(), h_QCD_yield.GetBinError(1) ) )
print("Number of events from fake rate method: {0} +/- {1}".format( QCD_yield, QCD_yield_error ) )




















"""
#QCD_yield_error += (FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1)) * h_nTaus_FnotT_eta0to1p5.GetBinError(bin_+1))**2 + ( h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1)*(1/(1 - FR_eta0to1p5.GetEfficiency(bin_+1)) + FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))**2) * max(FR_eta0to1p5.GetEfficiencyErrorLow(bin_+1), FR_eta0to1p5.GetEfficiencyErrorUp(bin_+1)))**2
#QCD_yield_error += (FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1)) * h_nTaus_FnotT_eta1p5to2p3.GetBinError(bin_+1))**2 + ( h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1)*(1/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1)) + FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1))**2) * max(FR_eta1p5to2p3.GetEfficiencyErrorLow(bin_+1), FR_eta1p5to2p3.GetEfficiencyErrorUp(bin_+1)))**2

err_nTaus_FnotT += FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1)) * h_nTaus_FnotT_eta0to1p5.GetBinError(bin_+1)
    err_nTaus_FnotT += FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1)) * h_nTaus_FnotT_eta1p5to2p3.GetBinError(bin_+1)
    err_FR = h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1)*(1/(1 - FR_eta0to1p5.GetEfficiency(bin_+1)) + FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))**2) * max(FR_eta0to1p5.GetEfficiencyErrorLow(bin_+1), FR_eta0to1p5.GetEfficiencyErrorUp(bin_+1))
    err_FR = h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1)*(1/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1)) + FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1))**2) * max(FR_eta1p5to2p3.GetEfficiencyErrorLow(bin_+1), FR_eta1p5to2p3.GetEfficiencyErrorUp(bin_+1))

err_nTaus_FnotT = err_nTaus_FnotT**2
err_FR = err_FR**2
QCD_yield_error = math.sqrt(err_nTaus_FnotT + err_FR)
"""
