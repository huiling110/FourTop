
from makeplot_fromAnshual import *

inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline_v36TESandJERByHuiling/mc/variableHists_v3pileUpAndNewRange/results/'

csv= inputDir +'1tau1lCRs_withUncertInverted.csv'
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

plotname= '/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/' +'myplot'
cmslabel="WIP"
data=True
lumi=16
year=2016
makeplot(csv,bkg,bkg_unc,bkgcolor,sig,sigcolor,scalesignal,plotname,cmslabel, data, lumi, year)
