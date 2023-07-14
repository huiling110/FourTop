
import usefulFunc as uf
from makeplot_fromAnshual import makeplot
from ttttGlobleQuantity import lumiMap


def plotYieldComparison(
    # year = '2018',
    # year = '2016',
    # year = '2016postVFP'

    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline_v36TESandJERByHuiling/mc/variableHists_v3pileUpAndNewRange/results/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v36TESandJERByHuiling/mc/variableHists_v2addingPileupWeight/results/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baseline_v37TauPt30AndPreselection/mc/variableHists_v3pileUpAndNewRange/results/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baseline_v36TESandJERByHuiling/mc/variableHists_v2addingPileupWeight/results/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v36TESandJERByHuiling/mc/variableHists_v4forFakeRate/results/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0addMoreVariables_v39addTauBranches/mc/variableHists_v0forFakeRate/results/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v1forFREtaRegionCorrected/results/',
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1AddTOPLepVariables_v49FixedPileUpNoJERTES/mc/variableHists_v2_newLepPileUp/results/',
    csvName = '1tau1lCRs_withUncertInverted.csv' 
    # csvName = '1tau0lCRs_withUncertInverted.csv'
    # csvName = '1tau0lFakeRate.csv'
): 


    year = uf.getEraFromDir(inputDir)
    lumi = lumiMap[year]/1000
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


if __name__=='__main__':
    plotYieldComparison()
