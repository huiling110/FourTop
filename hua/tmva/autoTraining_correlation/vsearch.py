
import os, subprocess, sys
from datetime import datetime
import time
import ROOT
from vSearchHelper import *
from vSearchStrategy import *
import array



#in all var list csv files everything after the ampersand line is ignored
#Variable list filename format: vlistitle-"generation"-"parent id"-"no. of var"-"id in this generation"
#For example, itrAd-0-0-0-1 means that this is a variable list for iterative addition, used in 0th generation (initial list), has 0 variable in it (initial list for iterative addition) and is the 1st variable list in its generation


#hyperparameters

#Directory for variable lists
vlistdir = "vsearch-varlist/"
#Directory for result output
resultlistdir = "vsearch-result/"
#Directory for log files from training
#If changed, you'll also need to change the output dir for TMVA defined in vsearch-runtest.sh
loglistdir = "vsearch-log/"	
#Directory for TMVA output
outputdir="/out/MVA/"
#Name of output root file in each folder
rootfilename="reg7_EvenOdd.root"
#NB: The TMVA Wrapper used (in run_test()) must output in this format:
#outputdir + variablelistname + rootfilename
#For Example: "/out/MVA/" + "itrAd-0-0-0-1/" + "reg7_EvenOdd.root"


#Define title of this search. Will be part of the name for output files.
vlisttitle = "itrAd"

#Define filename of the initial variable list. This file needs to be placed under "vlsitdir".
vlistlist_curr = ["itrAd-0-0-0-1"] #vlistitle-"generation"-"parent id"-"no. of var"-"id in this generation"
#Defile filename of the variable list that contains all variables the program might use. Place in the same dir as the programme.
mother_list="mva-variables-list-all.csv"

#Define variable list generation method and selection strategy.
#These functions are defined in vSearchStrategy.py
#Out-of-the-box methods:
	#itrRm - Greedy Iterative Removal
	#itrAd - Greedy Iterative Addition
	#beamSearch - Beam Search (extra parameters need to be defined in vSearchStrategy.py)
	#rdmWalk - Random Walk (extra parameters need to be defined in vSearchStrategy.py)
#vSearchStrategy.py contains instructions for creating and using your own search strategy
gen_method = genvlist_itrAd	#generation method; def genvlist_itrAd(vlist_lines, checkedvlist, vlist_all) in vSearchStrategy.py
choose_method = choose_next_vlistlist_itrAd	#selection method

#Define which function to use to check performance benchmark
#Currently only support AUROC (default) but you can substitute your own function here
check_benchmark = check_benchmark_roc

#Define starting generation, default 0
gen = 0
#Define end generation
endgen = 2
#Define max No. of resubmission if SGE (DESY BIRD) returns corrupted files
maxattempts = 10

#Toggle extra header/generation information in variable lists
#If false, variable list files should contain only lines of variable definition
varlistextraformat = True


#Initialisation
checkedvlist = set()

def main():

	#initialisation
	global vlistlist_curr, resultlistdir, mother_list, vlisttitle, choose_method, gen, endgen, maxattempts, varlistextraformat
	vlist_all=file2list(mother_list) #function in vSearchHelper.py, seems to exlude first line in the file
	f = open(mother_list, "r")
	headerline = f.readline()
	f.close()
	overallresult = []
	joblist = []
	errorcount = 0
	

	print "vSearch : vSearch started " + str(datetime.now())
	print "vSearch : Search title = " + vlisttitle
	print "vSearch : Start generation = " + str(gen) + " ;End generation = " + str(endgen)
	print "vSearch : Initial vlist = " + str(vlistlist_curr) #vlistlist_curr = ["itrAd-0-0-0-1"]
	print "vSearch : Initialising..."

	gen +=1
	while(gen <=endgen):
		#next-gen vlist generation
		print "vSearch Generation " + str(gen) +" : Current parent vlist: " + str(vlistlist_curr)
		print "vSearch Generation " + str(gen) +" : Generating vlist"
		joblist=spawnvlist(headerline, vlist_all) #return a list of string names of child vlist file
		print "vSearch Generation " + str(gen) +" : vlist generation complete"
		result = []

		while joblist:	#still some jobs to run, either for the first time or for reattempt

			n_job = len(joblist)
			f = open("tmp_vsearch_runtest_list", "w")
			for line in joblist:
				f.write(line + '\n')
			f.close()

			#run job
			print "vSearch Generation " + str(gen) +" : Running with " + str(n_job) + " jobs"
			run_jobs(n_job) #submit multiple jobs here
			#this will wait for jobs to complete
			print "vSearch Generation " + str(gen) +" : Run complete"


			#check for integrity of results
			culprit = []
			retryjoblist = []
			for eachfile in joblist:
				thisvlistname = eachfile.split("/")[-1]
				(integrityFlag, benchmark) = integrity_check(eachfile, thisvlistname)				
				if integrityFlag:	
					result.append((thisvlistname, benchmark))
				else:
					culprit.append(thisvlistname)
					retryjoblist.append(eachfile)

			joblist = retryjoblist					
			if retryjoblist:	#retry list not empty, some jobs failed
				print "vSearch Generation " + str(gen) +" : File Integrity Error! "
				print "vSearch Generation " + str(gen) +" : Corrupted file: " + str(culprit)
				errorcount += 1
				if errorcount >= maxattempts:	#too many reattempts, something seriously wrong
					print "vSearch Generation " + str(gen) +" : Critical Error - reached upper limit of attempts"
					print "vSearch Generation " + str(gen) +" : Check filesystem and hyperparameter!"
					exit(1)
				print "vSearch Generation " + str(gen) +" : Redoing generation " + str(gen) + " attempt " + str(errorcount)	

				continue #redo batch
			else:	#everything is done :)
				write_result(result, resultlistdir + vlisttitle + '-' + str(gen))
				(vlistlist_curr, printlines) = choose_method(result, resultlistdir, vlistdir)
				for pl in printlines: print "vSearch Generation " + str(gen) + " : " + pl
				errorcount = 0
				gen += 1

	print "vSearch : vSearch complete! " + str(datetime.now())





def integrity_check(eachfile,thisvlistname):
	try:
		global loglistdir, check_benchmark
		pwd = os.path.dirname(os.path.realpath(__file__))
		#Check log file for success indication
		logdir = loglistdir + thisvlistname + ".log"
		f = open(logdir,"r")
		logokFlag = False
		for logline in f:
			if "TMVAClassification is done!" in logline: logokFlag = True
		f.close()
		if not logokFlag: 
			return (False, 0)

		#check output file for integrity
		filedir = pwd + outputdir + thisvlistname + "/" +  rootfilename #path of output file of TMVA
		rf = ROOT.TFile(filedir,'READ')
		if rf.IsZombie():
			return (False, 0)
		benchmark = check_benchmark(rf)		#####DEFINE BENCHMARK FUNCTION
		if benchmark == -1:
			return (False, 0)
		rf.Close()
		return (True, benchmark)	#integrity check success
	except:
		return (False, 0)

def write_result(result, fdir):
	f = open(fdir, "w")
	for (i,j) in result:
		f.write(i + "," + str(j) + "\n")
	f.close()
		


def run_jobs(n_nextgen):
	#n_nextgen defines no. of jobs to be sent to SGE in this batch
	command =  "qsub -sync y -t 1-" + str(n_nextgen) + " vsearch-runtest.sh tmp_vsearch_runtest_list"
	process1 = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        #subprocess.Popen:
	(output, err) = process1.communicate()	


def spawnvlist(headerline, vlist_all):
	global vlistdir, vlistlist_curr, vlisttitle, gen_method, gen, checkedvlist, varlistextraformat
	nextfileid = 1
	nextgenvlistlist = []
	for vlist_curr in vlistlist_curr: #vlistlist_curr = ["itrAd-0-0-0-1"];  curr stands for current I guess

                #produce the next gen list of vlist
		vlist_lines = file2list(vlistdir + vlist_curr)
		parentid = vlist_curr.split("-")[4] 
                # the last value, which should be the id in this generation for vlist_curr
		(out, curr_strategy) = gen_method(vlist_lines, checkedvlist, vlist_all)
                #out is a list of vlist, vlist is vlist_lines add 1 variable in vlist_all
		if not out: continue	#this vlist genereates no children, skip

		fm = open(vlistdir + vlist_curr, "a")
		if varlistextraformat:
			#metadata
			fm.write("&\nChildren list = " + vlisttitle + "-" + str(gen) + "-" + str(parentid) + "-nvar-id" + "\n")
			fm.write("Generation Strategy = " + curr_strategy + "\n")
			fm.write("No. of Children = " + str(len(out)) + "\n")

    
                #write the next gen vlist files
		for idx, eachfile in enumerate(out): #Get the element and index from a list
			checkedvlist.add(list2vec(eachfile, vlist_all))	#mark this varlist as checked in set checkedvlist
                        #list2vec: a vector of length vlist_all, all 0 value, the one in eachfile is set to 1
			nvarthisvlist = len(eachfile)

			if varlistextraformat:
				eachfile.insert(0, headerline)	#Insert header line on top of varlist
				eachfile.append("&\n")	#append ampersand symbol at the end
				#metadata
				eachfile.append("Generation = " + str(gen) + "\n")
				eachfile.append("Parent = " + vlist_curr + "\n")
				eachfile.append("Spawn from strategy = " + curr_strategy + "\n")
				timenow = str(datetime.now())
				eachfile.append("Spawn time = " + timenow + "\n")

			childname = vlisttitle + "-" + str(gen) + "-" + str(parentid) + "-" + str(nvarthisvlist) + "-" + str(nextfileid + idx)
			f = open(vlistdir + childname, "w")
			nextgenvlistlist.append(vlistdir + childname)
			for line in eachfile:
				f.write(line)
			f.close()
			if varlistextraformat: fm.write(childname + "\t" + timenow + "\n")
		if varlistextraformat: fm.write("===End of Children list\n")
		fm.close()
		nextfileid += len(out)
	return nextgenvlistlist


if __name__ == '__main__':
	main()
