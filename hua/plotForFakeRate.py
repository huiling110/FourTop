from ROOT import TCanvas
from ttttGlobleQuantity import summedProcessList

from writeCSVforEY import getSummedHists


def main():
    inputDirDic ={
        'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/mc/variableHists_v4forFakeRate/',
        'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/data/variableHists_v4forFakeRate/'
    } 

    variableList = ['tausL_1pt']
    regionList = ["1tau0lCRGen", '1tau0lCR', '1tau0lCRLTauGen', "1tau0lCRLTau", "1tau0lVRGen", "1tau0lVRLTau"]
    sumProcessPerVar = {}
    #sumProcessPerVar[var][region][sumedProcess] = hist
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )



    h_CR_data = sumProcessPerVar['tausL_1pt']['1tau0lCR']['data'] 
    h_CR_bgGenTau = addBGHist(sumProcessPerVar, 'tausL_1pt', '1tau0lCRGen')
    h_CR_bgGenTau.Print() 
    h_CR_data.Print()
    h_CR_dataSubBG = h_CR_data - h_CR_bgGenTau
    h_CR_dataSubBG.Print()

    h_CRLTau_data = sumProcessPerVar['tausL_1pt']['1tau0lCRLTau']['data'] 
    h_CRLTau_bgGenTau = addBGHist(sumProcessPerVar, 'tausL_1pt', '1tau0lCRLTauGen')
    h_CRLTau_dataSubBG = h_CRLTau_data - h_CRLTau_bgGenTau


    can = TCanvas('numeritor')
    h_CRLTau_dataSubBG.Draw('hist')
    h_CR_dataSubBG.Draw('histsame')
    can.SaveAs(inputDirDic['mc'] + 'test.png')



def addBGHist(sumProcessPerVar, var, region):
    sumHist = sumProcessPerVar[var][region][summedProcessList[0]]
    sumHist.Reset()
    for ipro in summedProcessList:
        if ipro=='data' or ipro=='tttt': continue
        sumHist.Add( sumProcessPerVar[var][region][ipro])
    return sumHist




if __name__=='__main__':
    main()
