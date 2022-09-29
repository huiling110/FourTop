

from writeCSVforEY import getSummedHist


def main():
    inputDirDic ={
        'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/mc/',
        'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/data/'
    } 

    sumProcessPerVar = {}
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDir, regionList, ivar )
    print( sumProcessPerVar )
