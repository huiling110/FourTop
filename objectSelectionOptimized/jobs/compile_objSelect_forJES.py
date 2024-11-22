import os
import subprocess


# def makeJES_OS_e:
# for JESSysType in range(1,27):
for JESSysType in range(0, 1):
    for JESSys in ['1', '2']:
        # file_path = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/apps/run_objectSelection.C"
        file_path = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/apps/run_objectSelection.C'
        line_of_JESSys = f"    const UChar_t JESSys = {JESSys}; //norminal\n"
        line_of_JESSysType = f'''    const Int_t JESSysUncerType = {JESSysType}; // In range 0-26\n'''
        print(line_of_JESSysType)

        
        with open(file_path, 'r') as file:
            lines = file.readlines()

        if len(lines) >= 80:
            #lines[35] = new_line
            lines[62] = line_of_JESSys
            lines[65] = line_of_JESSysType

            with open(file_path, 'w') as file:
                file.writelines(lines)
            print(f"Replaced line 61 and 63 in {file_path}")
        else:
            print(f"File {file_path} does not have 36 lines")

        # compile_dir = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/"
        compile_dir = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/'

        commands = [
            # ["make", "clean"],
            ["make"]
        ]
        for command in commands:
            subprocess.run(command, cwd=compile_dir, check=True)
        print("Compilation finished")

        original_file = os.path.join(compile_dir, "apps/run_objectSelection.out")
        renamed_file = os.path.join(compile_dir, f"apps/run_objectSelection_{JESSysType}_{JESSys}.out")

        if os.path.exists(original_file):
            os.rename(original_file, renamed_file)
            print(f"Renamed {original_file} to {renamed_file}")
        else:
            print(f"Compiled file {original_file} does not exist")
