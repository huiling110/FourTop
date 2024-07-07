

import os
import re

def extract_gen_weight_sum(directory):
    # Dictionary to store results
    gen_weight_sums = {}
    
    # Regex pattern to match the line and extract the number
    # pattern = re.compile(r'genWeightSumInitial: (\d+(\.\d+)?)')
    pattern = re.compile(r'genWeightSumInitial: (\d+(\.\d+)?([eE][+-]?\d+)?)')
    
    # Iterate through all files in the directory
    for filename in os.listdir(directory):
        # Check if the file is a .log file
        if filename.endswith(".log"):
            # Construct the full file path
            filepath = os.path.join(directory, filename)
            
            # Open and read the file
            with open(filepath, 'r') as file:
                for line in file:
                    # Search for the pattern in the current line
                    match = pattern.search(line)
                    if match:
                        # Extract the number from the matched pattern
                        number = float(match.group(1))
                        # Store the result in the dictionary
                        # gen_weight_sums[filename] = number
                        gen_weight_sums[os.path.splitext(filename)[0]] = number
                        break  # Assuming only one such line per file, exit the loop early
                        
    return gen_weight_sums

# Specify the directory to search
# directory = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_allCorrection/log/"
directory = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHardro_FRweightSys_v79HadroPresel/mc/variableHists_v1dataMC_allCorrectionFakeTau/log/'
gen_weight_sums = extract_gen_weight_sum(directory)
# print(gen_weight_sums)
for filename, weight_sum in gen_weight_sums.items():
    print(f"'{filename}': {weight_sum}")
