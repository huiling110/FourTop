import ROOT

# Create an RDataFrame for the dataset
input = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/output/2022preEE/tree_1.root'
df = ROOT.RDataFrame('tree', input)

mediumTauSel = df.Filter('tausT_pt.size()>0')
hardronicTriggerSel = mediumTauSel.Filter('HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_ ||HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_||HLT_PFJet500_')
mediumTauSelCount = mediumTauSel.Count()
hardronicTriggerSelCount = hardronicTriggerSel.Count()

tightTauSel = df.Filter('tausTT_pt.size()>0')
hardonicTriggerSelTT = tightTauSel.Filter('HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ || HLT_PFJet500_')

initial = df.Count()
print('Initial: ', initial.GetValue(), ' mediumTauSel: ', mediumTauSelCount.GetValue(), ' hardronicTriggerSel: ', hardronicTriggerSelCount.GetValue())

print('Initial=', initial.GetValue(), ' tightTauSel=', tightTauSel.Count().GetValue(), ' hardonicTriggerSelTT=', hardonicTriggerSelTT.Count().GetValue())

df.Report().Print()
print('done\n')



