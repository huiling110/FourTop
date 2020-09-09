import sys
import os
import glob
import string
import subprocess

Jobsubmitpath = "/afs/ihep.ac.cn/users/y/yutz/CMSSW_7_4_14/src/Tprime_2016"
rootplizer = "EventSelection_dineutrino_Resolved_v3.cpp"
allJobFileName = Jobsubmitpath+"/hepsub.sh"
if os.path.exists(allJobFileName):
        os.popen('rm -fr '+allJobFileName)
if os.path.exists(Jobsubmitpath+"/Jobsubmit"):
        os.popen('rm -fr '+Jobsubmitpath+"/Jobsubmit")
os.popen('mkdir -p '+Jobsubmitpath+"/Jobsubmit")
sample = {
"Tprime_0600":"0",
"Tprime_0700":"1",
"Tprime_0700_10p":"1_1",
"Tprime_0800":"2",
"Tprime_0800_10p":"2_1",
"Tprime_0800_20p":"2_2",
"Tprime_0800_30p":"2_3",
"Tprime_0900":"3",
"Tprime_0900_10p":"3_1",
"Tprime_1000":"4",
"Tprime_1000_10p":"4_1",
"Tprime_1000_20p":"4_2",
"Tprime_1000_30p":"4_3",
"Tprime_1100":"5",
"Tprime_1100_10p":"5_1",
"Tprime_1200":"6",
"Tprime_1200_10p":"6_1",
"Tprime_1200_20p":"6_2",
"Tprime_1200_30p":"6_3",
"Tprime_1300":"7",
"Tprime_1300_10p":"7_1",
"Tprime_1400":"8",
"Tprime_1400_10p":"8_1",
"Tprime_1400_20p":"8_2",
"Tprime_1400_30p":"8_3",
"Tprime_1500":"9",
"Tprime_1500_10p":"9_1",
"Tprime_1600":"10",
"Tprime_1600_10p":"10_1",
"Tprime_1600_20p":"10_2",
"Tprime_1600_30p":"10_3",
"Tprime_1700":"11",
"Tprime_1700_10p":"11_1",
"Tprime_1800":"12",
"ZToNuNu_HT100to200":"13",
"ZToNuNu_HT200to400":"14",
"ZToNuNu_HT400to600":"15",
"ZToNuNu_HT600to800":"16", 
"ZToNuNu_HT800to1200":"17",
"ZToNuNu_HT1200to2500":"18",
"ZToNuNu_HT2500toInf":"19", 
"QCD_HT200to300":"20",  
"QCD_HT300to500":"21",  
"QCD_HT500to700":"22",  
"QCD_HT700to1000":"23", 
"QCD_HT1000to1500":"24",
"QCD_HT1500to2000":"25",
"QCD_HT2000toInf":"26", 
"WToLNu_HT100to200":"27",  
"WToLNu_HT200to400":"28",  
"WToLNu_HT400to600":"29",  
"WToLNu_HT600to800":"30",  
"WToLNu_HT800to1200":"31", 
"WToLNu_HT1200to2500":"32",
"WToLNu_HT2500toInf":"33", 
"TT":"34", 
"TTToSemiLeptonic":"35", 
"ST_t-channel_antitop":"36",  
"ST_t-channel_top":"37",  
"ST_tW_antitop":"38",  
"ST_tW_top":"39",  
"ZZTo4L":"40",   
"ZZTo2L2Nu":"41",  
"ZZTo2Q2Nu":"42",
"ZZTo2L2Q":"43",
"WWTo2L2Nu":"44",
"WWToLNuQQ":"45",
"WZTo1L1Nu2Q":"46",
"WZTo1L3Nu":"47",
"WZTo2L2Q":"48",
"WZTo3LNu":"49", 
"TTWToLNu":"50",
"TTZToLLNuNu":"51",
"tZq":"52",
"Aug17V1_METB":"53",
"Aug17V1_METC":"54",
"Aug17V1_METD":"55",
"Aug17V1_METE":"56",
"Aug17V1_METF":"57",
"Aug17V1_METG":"58",
"Aug17V1_METH":"59",
}

allJobFile = file(allJobFileName,"w")
print >> allJobFile, "cd "+Jobsubmitpath+"/Jobsubmit"

def prepareCshJob(inputFile,shFile):
        subFile      = file(shFile,"w")
        print >> subFile, "#!/bin/bash"
        print >> subFile, "/bin/hostname"
        print >> subFile, "gcc -v"
        print >> subFile, "pwd"
        print >> subFile, "cd "+Jobsubmitpath
        print >> subFile, "root -l -b -q "+rootplizer+"\'(\""+inputFile+"\")\'"
#	subprocess.call("chmod 777 "+shFile, shell=True)
for k in sample:
        print k
        print sample[k]
        sampleName = k
        sampleNumber = sample[k]
	shFile = "EventSelection_dineutrino_Resolved_2016"+"_"+sampleNumber+".sh"
	shFileName = "Jobsubmit/"+shFile
	inputFile = sampleName+".root"
	prepareCshJob(inputFile,shFileName)	
   	logFileName = "/publicfs/cms/user/yutz/Tprime/Jobs_data/log/"+"Event_"+sampleNumber+".log"
   	errorFileName = "/publicfs/cms/user/yutz/Tprime/Jobs_data/log/"+"Event_"+sampleNumber+".err"
	print >> allJobFile, "hep_sub "+ shFile + " -o "+logFileName+ " -e "+errorFileName	 


os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit/*sh")
os.popen('chmod 777 '+Jobsubmitpath+"/hepsub.sh")





