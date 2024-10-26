import os
import subprocess
import time

import argparse

def main():
    parser = argparse.ArgumentParser(description='Process two numbers.')
    
    parser.add_argument('num1', type=int, help='The first number')
    parser.add_argument('num2', type=str, help='The second number')
    
    # 解析参数
    args = parser.parse_args()
    
    num1 = args.num1
    num2 = args.num2
    
    for mass in [num1]:
        for i in [num2]:
            file_path = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/writeHistGood/jobs/makeJob_forWriteHist_BDT.py"
            line_version_name = f"    version = 'v0Basictraining1tau1l_VLLm{mass}0_{i}_GBDT'\n"
            print(line_version_name)
            line_treeAnalyzer_version = f'''            run = './run_treeAnalyzer_{mass}0_{i}_GBDT.out {{}} {{}} {{}} {{}} {{}}'.format(inputDir, iProcess, version, channel, isTest)\n'''
            print(line_treeAnalyzer_version)
            # rename the script of submitJob to make it possible to sumbit condor_jobs for each masspoint.
            new_line_78 = f'''    subAllProcess = open( Jobsubmitpath+'subAllProcess_{mass}0_{i}.sh', 'w')\n'''
            new_line_91 = f'''    uf.sumbitJobs(  Jobsubmitpath+'subAllProcess_{mass}0_{i}.sh')\n'''
            new_line_98 = f'''    jobDir = Jobsubmitpath +'jobSH_{mass}0_{i}/'\n'''
            new_line_122 = f'''    subprocess.run('chmod 777 ' + Jobsubmitpath+ 'subAllProcess_{mass}0_{i}.sh', shell=True)\n'''

            with open(file_path, 'r') as file:
                lines = file.readlines()

            if len(lines) >= 110:
                lines[58] = line_version_name
                lines[114] = line_treeAnalyzer_version
                lines[79] = new_line_78
                lines[92] = new_line_91
                lines[99] = new_line_98
                lines[123] = new_line_122

                with open(file_path, 'w') as file:
                    file.writelines(lines)
                print(f"Replaced line 36 and 50 in {file_path}")
            else:
                print(f"File {file_path} does not have 36 lines")
    

if __name__ == "__main__":
    main()

