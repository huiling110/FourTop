
from makeplot_fromAnshual import *

csv='1tau1lCRs_withUncertInverted.csv'
bkg_unc=['tt_uncert','ttX_uncert','VV_uncert','qcd_uncert','singleTop_uncert']
bkg=['tt','ttX','VV','qcd','singleTop']
bkgcolor={'tt':'red',
         'ttX':'lightcoral',
         'VV':'green',
         'qcd':'yellow',
         'singleTop':'lime'}
sig=['tttt']
sigcolor=['pink']
scalesignal=50
plotname="myplot"
cmslabel="WIP"
data=True
lumi=16
year=2016
makeplot(csv,bkg,bkg_unc,bkgcolor,sig,sigcolor,scalesignal,plotname,cmslabel, data, lumi, year)
