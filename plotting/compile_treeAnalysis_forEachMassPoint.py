import os
import subprocess
# 4: [500,550,650,750,950]
# 5: [700,800,850,900,1000]
# 6: [600]
for mass in [60]:
#for mass in [70,80,85,90,100]:
#for mass in [50,55,65,75,95]:
    #for i in ["06","07","08","09","10","11","12","13","14","15","16","17"]:
    for i in ["13"]:
        file_path = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/writeHistGood/src/treeAnalyzer.C"
        line_of_binning = f"        std::vector<Double_t> bins1tau0l = {{-0.45, -0.32, -0.30, -0.28, -0.26, -0.24, -0.22, -0.20, -0.18, -0.16, -0.14, -0.11, -0.07,  -0.02, 0.{i} ,0.26}};//Bin B\n"
        #print(new_line)
        line_of_BDT_Weight = f'''        weightfile = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/BDTTrain/v1finalVar_m{mass}0_GBDT/inputList_1tau0l.csv/dataset/weight/TMVAClassification_BDT.weights.xml";\n'''
        print(line_of_BDT_Weight)
        # 读取文件并替换第36行
        with open(file_path, 'r') as file:
            lines = file.readlines()

        if len(lines) >= 49:
            #lines[35] = new_line
            lines[69] = line_of_BDT_Weight
            lines[65] = line_of_binning

            with open(file_path, 'w') as file:
                file.writelines(lines)
            print(f"Replaced line 36 and 50 in {file_path}")
        else:
            print(f"File {file_path} does not have 36 lines")

        # 指定编译目录
        compile_dir = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/writeHistGood"

        # 编译命令
        commands = [
            ["make", "clean"],
            ["make"]
        ]
        for command in commands:
            subprocess.run(command, cwd=compile_dir, check=True)
        print("Compilation finished")

        # 重命名编译后的文件
        original_file = os.path.join(compile_dir, "apps/run_treeAnalyzer.out")
        renamed_file = os.path.join(compile_dir, f"apps/run_treeAnalyzer_{mass}0_{i}_GBDT.out")

        if os.path.exists(original_file):
            os.rename(original_file, renamed_file)
            print(f"Renamed {original_file} to {renamed_file}")
        else:
            print(f"Compiled file {original_file} does not exist")
