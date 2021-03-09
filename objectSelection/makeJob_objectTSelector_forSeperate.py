import sys
import os
import glob
import string
import subprocess
 #



#all the parameters you need to change is in this part , better not change the rest of the code.
#  isdata = True
isdata = False
outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v31_fixedLeptonBug/"
#  outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/"
inputDir = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/"
#  inputDir = "/publicfs/cms/data/TopQuark/FourTop_hua/v2/mc/2016/"

Jobsubmitpath = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/objectSelection/"
rootplizer = "run_objectTSelector.C"
subAllFile = Jobsubmitpath+"/subAllProcess_seperate.sh"
if os.path.exists(subAllFile):
    os.popen('rm -fr '+subAllFile)
if not os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate"):
    os.mkdir('Jobsubmit_seperate/')

sample = {
        #  "JetHT/Legacy16V2_JetHTBlockCHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060426/0000/": "C_0",
        #  "JetHT/Legacy16V2_JetHTBlockDHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060636/0000/": "D_0",
        #  "JetHT/Legacy16V2_JetHTBlockEHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060843/0000/": "E_0",
        #  "JetHT/Legacy16V2_JetHTBlockFHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_061048/0000/": "F_0",
        #  "JetHT/Legacy16V2_JetHTBlockGHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_061254/0000/": "G_0",
        #  "JetHT/Legacy16V2_JetHTBlockGHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_061254/0001/": "G_1",
        #  "JetHT/Legacy16V2_JetHTBlockHHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_061458/0000/": "H_0",
        #  "JetHT/Legacy16V2_JetHTBlockHHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_061458/0001/": "H_1",
        #  "JetHT/Legacy16V2_v2_JetHTBlockBHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060219/0000/": "B_0",
        #  "JetHT/Legacy16V2_v2_JetHTBlockBHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060219/0001/": "B_1",

   #  "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_023641/0000/":"0",
  # {{{
##tt
    #  "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024446/0000/":"1_0",
    #  "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024239/0000/":"1_1",
    #  "TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024040/0000/":"1_2",

    #  "ttZJets_13TeV_madgraphMLM-pythia8/Legacy16V2_ttZJets_13TeV_madgraphMLM-pythia8addGenWeight/210201_025644/0000":"3",
    #  "ttWJets_13TeV_madgraphMLM/Legacy16V2_ttWJets_13TeV_madgraphMLMaddGenWeight/210201_030246/0000/":"4",
    #  "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/Legacy16V2_ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8addGenWeight/210201_050201/0000/":"5",

    #  "WZ_TuneCUETP8M1_13TeV-pythia8/Legacy16V2_WZ_TuneCUETP8M1_13TeV-pythia8addGenWeight/210201_031735/0000/":"6",
    #  "WW_TuneCUETP8M1_13TeV-pythia8/Legacy16V2_WW_TuneCUETP8M1_13TeV-pythia8addGenWeight/210201_032142/0000/":"7",
    #  "ZZ_TuneCUETP8M1_13TeV-pythia8/Legacy16V2_ZZ_TuneCUETP8M1_13TeV-pythia8addGenWeight/210201_032809/0000/": "8",
#
    #  "WGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8/Legacy16V2_WGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8addGenWeight/210201_040503/0000/": "9",
    #  "ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8/Legacy16V2_ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8addGenWeight/210201_040904/0000/": "10",
#
    "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_054840/0000/": "12",
    "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055050/0000/": "13",
    "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055306/0000/": "14",
    "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055508/0000/": "15",
    "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055716/0000/": "16",
    "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055930/0000/": "17",
    "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055930/0000/": "18",
    "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_060130/0000/": "19",
#
#  WJets "20,
    "DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1/Legacy16V2_DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1addGenWeight/210201_041715/0000/": "21",

    "tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/Legacy16V2_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_042138/0000/": "22",
    "tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/Legacy16V2_tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1addGenWeight/210201_042338/0000/": "23",
    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/Legacy16V2_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4addGenWeight/210201_042748/0000/": "24",
    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/Legacy16V2_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4addGenWeight/210201_042947/0000/": "25",
    "TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/Legacy16V2_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8addGenWeight/210201_042537/0000/": "26",

    "THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8/Legacy16V2_THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8addGenWeight/210201_053954/0000/": "27",
    "THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/Legacy16V2_THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1addGenWeight/210201_054208/0000/": "28",
     #  /publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/
# }}}

}
#better not change code after this line

def prepareCshJob(inputFile,shFile, singleFile):
    subFile  = file(shFile,"w")
    print >> subFile, "#!/bin/bash"
    print >> subFile, "/bin/hostname"
    #  print >> subFile, "gcc -v"
    #  print >> subFile, "pwd"
    print >> subFile, "cd "+Jobsubmitpath
    print >> subFile, "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputFile+"\","+"\""+outputDir+"\"," + "\""+singleFile+ "\""   + ")"+ "\'"
    print shFile


subAllProcessName = file(subAllFile,"w")
print >> subAllProcessName, "#!/bin/bash"
print >> subAllProcessName, "cd "+Jobsubmitpath+"Jobsubmit_seperate"

for k in sample:
    print k
    #  print sample[k]
    sample_k = k
    #  sampleNumber = sample[k]
    sampleName = sample_k.split("/")[0]
    if  isdata:
        sampleName = sampleName + sample[k]
    print sampleName
   
    if not os.path.exists(outputDir +sampleName):
        os.mkdir(outputDir + sampleName)
    if not os.path.exists(outputDir +sampleName +"/log/" ):
        os.mkdir( outputDir + sampleName +"/log/")

    oneProcess =  Jobsubmitpath + "Jobsubmit_seperate/"+  sampleName + ".sh"
    if os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/"):
       os.popen('rm -fr '+Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/")
    os.popen('mkdir -p '+Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/")
    if os.path.exists(oneProcess):
        os.popen('rm -fr '+ oneProcess)
    sub_oneProcess = file( oneProcess, "w")
    print >> sub_oneProcess , "cd "+Jobsubmitpath+"Jobsubmit_seperate/" + sampleName + "/"

    sampleDir = inputDir + sample_k
    for entry in os.listdir( sampleDir):
        if os.path.isfile(os.path.join(sampleDir, entry)):

            smallFile = entry.replace( ".root", "")
            smallFilejob = "Jobsubmit_seperate/" +sampleName + "/" + smallFile + ".sh"  
            prepareCshJob( sample_k, smallFilejob, entry)
            
            logFile = outputDir +  sampleName + "/log/" + smallFile + ".log"
            errFile = outputDir +  sampleName + "/log/" + smallFile + ".err"
            print >> sub_oneProcess, "hep_sub "+  smallFile + ".sh" + " -o " + logFile + " -e " + errFile

    #  print >> subAllProcessName, "cd " + sampleName
    print >> subAllProcessName, "sh  " + oneProcess
    os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/" + sampleName + "/*sh")
    os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/*sh")


os.popen('chmod 777 '+Jobsubmitpath+"/subAllProcess_seperate.sh")





