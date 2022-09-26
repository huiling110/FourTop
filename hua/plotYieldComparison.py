
from ttttGlobleQuantity import lumiMap

from makeplot_fromAnshual import makeplot

year = 2018
lumi = lumiMap[str(year)]/1000

inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline_v36TESandJERByHuiling/mc/variableHists_v3pileUpAndNewRange/results/'

csvName = '1tau1lCRs_withUncertInverted.csv' 
csv= inputDir + csvName
# bkg_unc=['tt_uncert','ttX_uncert','VV_uncert','qcd_uncert','singleTop_uncert']
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
# lumi=16
# year=2016
makeplot(csv,bkg,bkg_unc,bkgcolor,sig,sigcolor,scalesignal,plotname,cmslabel, data, lumi, year)
