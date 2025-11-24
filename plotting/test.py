import uproot

input = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/templatesForCombine1tau1l_new_smoothed.root'


with uproot.open(input) as f:
    # keys = f.keys()
    # print(keys)
    #get 'data_obs_1tau1lCR12_BDT' 
    hist = f['data_obs_1tau1lCR12_BDT']
    hist.Print()