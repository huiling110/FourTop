
from ttttGlobleQuantity import lumiMap

from makeplot_fromAnshual import makeplot

# year = 2018
# year = 2016
year = '2016postVFP'
# lumi = lumiMap[str(year)]/1000
lumi = lumiMap[year]/1000

inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline_v36TESandJERByHuiling/mc/variableHists_v3pileUpAndNewRange/results/'
# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v36TESandJERByHuiling/mc/variableHists_v2addingPileupWeight/results/'

# csvName = '1tau1lCRs_withUncertInverted.csv' 
csvName = '1tau0lCRs_withUncertInverted.csv' 
csv= inputDir + csvName
bkg_unc=['ttUncert','ttXUncert','VVUncert','qcdUncert','singleTopUncert']
bkg=['tt','ttX','VV','qcd','singleTop']
bkgcolor={'tt':'red',
         'ttX':'lightcoral',
         'VV':'green',
         'qcd':'yellow',
         'singleTop':'lime'}
sig=['tttt']
sigcolor=['pink']
scalesignal=50

plotname= inputDir + csvName.replace('.csv', '_comparisonPlot') 
cmslabel="WIP"
data=True
makeplot(csv,bkg,bkg_unc,bkgcolor,sig,sigcolor,scalesignal,plotname,cmslabel, data, lumi, year)
