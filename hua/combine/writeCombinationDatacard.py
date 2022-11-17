import subprocess

# combineCards.py SR_1tau1l=/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_11bins/datacard/sumDC_10/TMVApp_1tau1l_10var_Sum_datacard.txt SR_1tau2l=/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau2l_v1/AppResults_11bins/datacard/sumDC_10/TMVApp_1tau2l_8var_Sum_datacard.txt SR_2tau0l=/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau0l_v1/AppResults_11bins/datacard/sumDC_10/TMVApp_2tau0l_25var_Sum_datacard.txt SR_1tau0l=/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau0l_HT/datacard/1tau0l_datacard.txt SR_2tau1l=/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/datacard/2tau1l_datacard.txt > 2016_datacard.txt 

# 1tau1l and 1tau0l combine
SR1tau1l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/TMVApp_1tau1l_10var_Sum_datacard.txt'
SR1tau0l = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v41addVertexSelection/mc/variableHists_v1HT30bins1tau0l/1tau0l_templatesForCombine/datacard/sumDC_10/1tau0ltemplates_Sum_datacard.txt'

command = 'combineCards.py SR1tau1l={} SR1tau0l={} > 2016_1tau1lAnd1tau0l_datacard.txt'.format(SR1tau1l, SR1tau0l)
print(command)
# process = subprocess.Popen( command, shell=True)
# out = process.communicate()
