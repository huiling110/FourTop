import subprocess

def query_das(dataset):
    # Use dasgoclient to query the dataset
    command = f"dasgoclient -query='file dataset={dataset}'"
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    stdout, stderr = process.communicate()
    
    # Check if the command was successful
    if process.returncode != 0:
        print(f"Error querying DAS: {stderr}")
        return []

    # Split the output into lines and return as a list
    file_list = stdout.strip().split('\n')
    return file_list

def main():
    # Specify the dataset you want to query
    dataset_list = [f"/VLferm_m{500+mass*50}GeV_{channel}_to_4b_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM" for mass in range(11) for channel in ["EE", "EN" , "NN"]]
    #dcjdcsj = f"/VLferm_m{500+mass*50}GeV_{channel}_to_4b_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM"
    # Query DAS and get the list of files
    # file_list = query_das(dataset)
    # Print the list of files
    with open('VLL_Charis.py', 'w') as f:
        f.write('''redirector = "root://cmsxrootd.fnal.gov/"''' + '\n')
        f.write('''filesetSignal = {''' + '\n')
        for mass in range(11):
            for channel in ["EE", "EN" , "NN"]:
                dataset = f"/VLferm_m{500+mass*50}GeV_{channel}_to_4b_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM"
                print(dataset)
                file_list = query_das(dataset)
                f.write(f'''"VLL_{channel}_M-{500+mass*50}GeV" : [''' + '\n')
                for file in file_list[:-1]:
                    f.write(f'''redirector+"{file}",''' + '\n')
                f.write(f'''redirector+"{file_list[-1]}"''' + '\n')
                f.write("]," + '\n')
                print("DONE!!!")
        f.write("}" + '\n')
if __name__ == "__main__":
    main()
