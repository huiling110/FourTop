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
    dataset_list = [
    "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
    "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
    "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
    "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
    "/TTZToQQ_TuneCP5_13TeV_amcatnlo-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
    "/TTZToQQ_TuneCP5_13TeV_amcatnlo-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
    "/TTZToQQ_TuneCP5_13TeV_amcatnlo-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v3/NANOAODSIM",
    "/TTZToQQ_TuneCP5_13TeV_amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v3/NANOAODSIM",
    "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
    "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
    "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
    "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
    "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
    "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
    "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
    "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM"
    ]
    Process_name = [
        "TTZToLLNuNu",
        "TTZToQQ",
        "TTWJetsToLNu",
        "TTWJetsToQQ"
    ]

    #dcjdcsj = f"/VLferm_m{500+mass*50}GeV_{channel}_to_4b_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM"
    # Query DAS and get the list of files
    # file_list = query_das(dataset)
    # Print the list of files
    with open('ttX_Charis_2018.py', 'w') as f:
        f.write('''redirector = "root://cmsxrootd.fnal.gov/"''' + '\n')
        f.write('''filesetSignal = {''' + '\n')
        for mass in range(16):
            year = mass%4
            if year == 3:
                dataset = dataset_list[mass]
                print(dataset)
                file_list = query_das(dataset)
                f.write(f'''"{Process_name[int(mass/4)]}" : [''' + '\n')
                for file in file_list[:-1]:
                    f.write(f'''redirector+"{file}",''' + '\n')
                f.write(f'''redirector+"{file_list[-1]}"''' + '\n')
                f.write("]," + '\n')
                print("DONE!!!")
        f.write("}" + '\n')
if __name__ == "__main__":
    main()
