import math
import ROOT
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-r', type=str, default='CR', help = 'region where to apply the fake rate method (AR or CR for debugging)')
parser.add_argument('-s', type=str, default='QCD', help = 'sample in which you want to apply the fake rate method (QCD or DATA)')
parser.add_argument('--SF', default=False, action="store_true", help = 'read QCD file where SF are applied')
parser.add_argument('--no_bkgsub', default=False, action="store_true", help = 'do not apply bkg subtraction when applying method in data')

FLAGS = parser.parse_args()
region = FLAGS.r
sample = FLAGS.s
SF = FLAGS.SF
no_bkgsub = FLAGS.no_bkgsub

if not SF :
    if sample == "QCD" :
        inputfile  = ROOT.TFile.Open("tauF_Pt_"+sample+".root")
    else :
        inputfile  = ROOT.TFile.Open("tauF_Pt_"+sample+".root")
        inputfile_topBkg  = ROOT.TFile.Open("tauF_Pt_TOPBKG.root")
else :
    inputfile  = ROOT.TFile.Open("tauF_Pt_"+sample+"_withSF.root")
    
str_ = "Opening file " + inputfile.GetName()
edge = "=" * len(str_)
print(edge)
print(edge)
print(str_)
print(edge)
print(edge)

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
    
    files_data = {

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

    files_MC = {
   
        "ttbar-FH": 373.0,
        "ttbar-SL": 367.0,
        "ttbar-DL": 90.6,

        "ttW+jets": 0.2014,
        "ttZ+jets": 0.6559,
        "ttG+jets": 3.697,
        "ttH": 0.3372,
        
    }

##################################################
##################################################
########### MONTE CARLO QCD ######################
##################################################
##################################################

if sample == "QCD" :
    for i, file_ in enumerate(files) :
        genEvts = inputfile.Get("totalWeight_"+file_)
        if i == 0 :
            if region == "CR" :
            #get the total QCD yield in CR, this has already been scaled for the cross sections of each QCD slices, so leave it untouched in the following
                h_QCD_yield = inputfile.Get("h_QCD_yield_CR")
            if region == "AR" :
                h_QCD_yield = inputfile.Get("h_QCD_yield_SR")
            h_nTaus_FnotT_eta0to1p5 = inputfile.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
            h_nTaus_FnotT_eta1p5to2p3 = inputfile.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
            FR_eta0to1p5 = inputfile.Get("FR_eta0to1p5_"+file_)
            FR_eta1p5to2p3 = inputfile.Get("FR_eta1p5to2p3_"+file_)
 
            h_nTaus_FnotT_eta0to1p5.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            h_nTaus_FnotT_eta1p5to2p3.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            FR_eta0to1p5.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            FR_eta1p5to2p3.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
 
        else : #not 1st file
            h_nTaus_FnotT_eta0to1p5_ = inputfile.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
            h_nTaus_FnotT_eta1p5to2p3_ = inputfile.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
            FR_eta0to1p5_ = inputfile.Get("FR_eta0to1p5_"+file_)
            FR_eta1p5to2p3_ = inputfile.Get("FR_eta1p5to2p3_"+file_)
        
            h_nTaus_FnotT_eta0to1p5_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            h_nTaus_FnotT_eta1p5to2p3_.Scale(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            FR_eta0to1p5_.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            FR_eta1p5to2p3_.SetWeight(files[file_] * LUMI2016 / genEvts.GetSumOfWeights())
        
            h_nTaus_FnotT_eta0to1p5.Add(h_nTaus_FnotT_eta0to1p5_)
            h_nTaus_FnotT_eta1p5to2p3.Add(h_nTaus_FnotT_eta1p5to2p3_)
            FR_eta0to1p5.Add(FR_eta0to1p5_)
            FR_eta1p5to2p3.Add(FR_eta1p5to2p3_)

##################################################
##################################################
################### DATA #########################
##################################################
##################################################
if sample == "DATA" :
    for i, file_ in enumerate(files_data) :
        if i == 0 :
            if region == "CR" :
                h_QCD_yield = inputfile.Get("h_QCD_yield_CR")
            h_nTaus_FnotT_eta0to1p5 = inputfile.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
            h_nTaus_FnotT_eta1p5to2p3 = inputfile.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
            FR_eta0to1p5 = inputfile.Get("FR_eta0to1p5_"+file_)
            FR_eta1p5to2p3 = inputfile.Get("FR_eta1p5to2p3_"+file_)
        else : #not 1st file
            h_nTaus_FnotT_eta0to1p5_ = inputfile.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
            h_nTaus_FnotT_eta1p5to2p3_ = inputfile.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
            FR_eta0to1p5_ = inputfile.Get("FR_eta0to1p5_"+file_)
            FR_eta1p5to2p3_ = inputfile.Get("FR_eta1p5to2p3_"+file_)
            h_nTaus_FnotT_eta0to1p5.Add(h_nTaus_FnotT_eta0to1p5_)
            h_nTaus_FnotT_eta1p5to2p3.Add(h_nTaus_FnotT_eta1p5to2p3_)
            FR_eta0to1p5.Add(FR_eta0to1p5_)
            FR_eta1p5to2p3.Add(FR_eta1p5to2p3_)
    
    for i, file_ in enumerate(files_MC) :
        genEvts = inputfile_topBkg.Get("totalWeight_"+file_)
        if i == 0 :
            h_nTaus_FnotT_eta0to1p5_topBkg = inputfile_topBkg.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
            h_nTaus_FnotT_eta1p5to2p3_topBkg = inputfile_topBkg.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
            h_nTaus_FnotT_eta0to1p5_topBkg.Scale(files_MC[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            h_nTaus_FnotT_eta1p5to2p3_topBkg.Scale(files_MC[file_] * LUMI2016 / genEvts.GetSumOfWeights())
        else : #not 1st file
            h_nTaus_FnotT_eta0to1p5_topBkg_ = inputfile_topBkg.Get("h_nTaus_FnotT_eta0to1p5_"+region+"_"+file_)
            h_nTaus_FnotT_eta1p5to2p3_topBkg_ = inputfile_topBkg.Get("h_nTaus_FnotT_eta1p5to2p3_"+region+"_"+file_)
            h_nTaus_FnotT_eta0to1p5_topBkg_.Scale(files_MC[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            h_nTaus_FnotT_eta1p5to2p3_topBkg_.Scale(files_MC[file_] * LUMI2016 / genEvts.GetSumOfWeights())
            h_nTaus_FnotT_eta0to1p5_topBkg.Add(h_nTaus_FnotT_eta0to1p5_topBkg_)
            h_nTaus_FnotT_eta1p5to2p3_topBkg.Add(h_nTaus_FnotT_eta1p5to2p3_topBkg_)
            
    if (region == "AR" or region == "VR") and not no_bkgsub :
        h_nTaus_FnotT_eta0to1p5.Add(h_nTaus_FnotT_eta0to1p5_topBkg, -1)
        h_nTaus_FnotT_eta1p5to2p3.Add(h_nTaus_FnotT_eta1p5to2p3_topBkg, -1)

QCD_yield = 0.0
QCD_yield_error = 0.0
for bin_ in range(5) :
    if h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1) >= 0:
        QCD_yield += h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1) * FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))
    if h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1) >= 0:
        QCD_yield += h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1) * FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1))
    QCD_yield_error += (h_nTaus_FnotT_eta0to1p5.GetBinError(bin_+1)/h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1) + max(FR_eta0to1p5.GetEfficiencyErrorLow(bin_+1), FR_eta0to1p5.GetEfficiencyErrorUp(bin_+1))/FR_eta0to1p5.GetEfficiency(bin_+1) + max(FR_eta0to1p5.GetEfficiencyErrorLow(bin_+1), FR_eta0to1p5.GetEfficiencyErrorUp(bin_+1))/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))) * h_nTaus_FnotT_eta0to1p5.GetBinContent(bin_+1) * FR_eta0to1p5.GetEfficiency(bin_+1)/(1 - FR_eta0to1p5.GetEfficiency(bin_+1))
    QCD_yield_error += (h_nTaus_FnotT_eta1p5to2p3.GetBinError(bin_+1)/h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1) + max(FR_eta1p5to2p3.GetEfficiencyErrorLow(bin_+1), FR_eta1p5to2p3.GetEfficiencyErrorUp(bin_+1))/FR_eta1p5to2p3.GetEfficiency(bin_+1) + max(FR_eta1p5to2p3.GetEfficiencyErrorLow(bin_+1), FR_eta1p5to2p3.GetEfficiencyErrorUp(bin_+1))/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1)))*h_nTaus_FnotT_eta1p5to2p3.GetBinContent(bin_+1) * FR_eta1p5to2p3.GetEfficiency(bin_+1)/(1 - FR_eta1p5to2p3.GetEfficiency(bin_+1))

print("Fake rate method has been applied to {0} in the {1}".format(sample, region))
if (sample == "QCD" and (region == "CR" or region == "AR")) or (sample == "DATA" and region == "CR") :
    print("Number of raw QCD entries: {0}".format( h_QCD_yield.GetEntries() ) )
    print("Number of events by counting: {0} +/- {1}".format( h_QCD_yield.Integral(), h_QCD_yield.GetBinError(1) ) )
if region == "AR" and sample == "QCD" :
    print("Number of events counted in the signal region: {0} +/- {1}".format( h_QCD_yield.Integral(), h_QCD_yield.GetBinError(1) ) )
print("Number of events from fake rate method: {0} +/- {1}".format( QCD_yield, QCD_yield_error ) )

#save numbers of fake-not-tight taus and fake rates to an output root file
if not SF :
    if no_bkgsub :
        outputfile = ROOT.TFile( "printYields_output_"+sample+"_"+region+".root", "RECREATE" )
    else :
        outputfile = ROOT.TFile( "printYields_output_"+sample+"_"+region+"_bkgsubtraction.root", "RECREATE" )
else :
    outputfile = ROOT.TFile( "printYields_output_"+sample+"_"+region+"_bkgsubtraction_withSF.root", "RECREATE" )
h_nTaus_FnotT_eta0to1p5.Write()
h_nTaus_FnotT_eta1p5to2p3.Write()
if sample == "DATA" and no_bkgsub :
    h_nTaus_FnotT_eta0to1p5_topBkg.Write("h_nTaus_FnotT_eta0to1p5_topBkg")
    h_nTaus_FnotT_eta1p5to2p3_topBkg.Write("h_nTaus_FnotT_eta1p5to2p3_topBkg")
FR_eta0to1p5.Write()
FR_eta1p5to2p3.Write()
    
