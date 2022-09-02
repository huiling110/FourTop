import pandas as pd

# obCSV = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v19HLTSelection/mc/results/cutFlow_objectSelection.csv'
# R1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v19HLTSelection/mc/variableHists_v2baseline/results/1tau0lEYinRegions.csv'
# obCSV = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v24noJER/mc/results/cutFlow_objectSelection.csv'
# R1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v24noJER/mc/variableHists_v0/results/cutflow.csv'
# obCSV = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v24noJER/mc/results/cutFlowRawEntries_objectSelection.csv'
# R1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v24noJER/mc/variableHists_v0/results/cutflow_rawEntries.csv'
# obCSV = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v25noJERNOTES//mc/results/cutFlow_objectSelection.csv'
# R1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v25noJERNOTES/mc/variableHists_v2cutflow1tau0l/results/cutflow.csv'
# obCSV = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v27noJERnoTESWithObjectRemoval/mc/results/cutFlowRawEntries_objectSelection.csv'
# R1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v27noJERnoTESWithObjectRemoval/mc/variableHists_v0forCutFlow/results/cutflow_rawEntries.csv'
# obCSV = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v27noJERnoTESWithObjectRemoval/mc/results/cutFlow_objectSelection.csv'
# R1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v27noJERnoTESWithObjectRemoval/mc/variableHists_v0forCutFlow/results/cutflow.csv'
obCSV = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v27noJERnoTESWithObjectRemoval/mc/results/cutFlowRawEntries_objectSelection.csv'
R1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v27noJERnoTESWithObjectRemoval/mc/variableHists_v0forCutFlow/results/cutflow_rawEntries.csv'

df1 = pd.read_csv( obCSV )
df2 = pd.read_csv( R1tau0l )

df2 = df2.join( df1['OBinitial'] )
df2 = df2.join( df1['OBHLT'])
# df2 = df2.join( df1['preSelection'])
# df2 = df2.join( df1['HLTeff'])

# df2['baselineEff'] = df2['baseline']/df2['HLTeff']

print( df1 )
print( df2 )

df2.to_csv( R1tau0l )

