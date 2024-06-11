
import os
import ROOT
import subprocess
import json
import usefulFunc as uf
#check IHEP local nanoAOD data file with that of GRID

def main():
    # nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/JetMET2022E/'
    # nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/JetMET2022F/'
    # nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/JetMET2022G/'
    # nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/data/singleMu_2018a/'
    nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/data/'
    
    # fileNum = getNumFiles(nanoDir)
    # print(nanoDir)
    # print('fileNum=: ', fileNum)
    # total = get_total_events(nanoDir)
    # print(f"Total events: {total}")

    # checkT3Entry(nanoDir, 'singleMu')
    # checkT3Entry(nanoDir, 'jetHT')

    # checkDASEntry()# SingleMuon all matches
    checkDASEntry('/JetHT')# JetHT A B C matches 

def checkT3Entry(directory, sample=''):
    for isample in os.listdir(directory):
        if sample and (not sample in isample): continue
        sampleDir = os.path.join(directory, isample)
        if not os.path.isdir(sampleDir):
            continue
        total = get_total_events(sampleDir)
        print(f"Sample {isample} has {total} events")


def get_dataset_names(query):
    """Get dataset names matching the query."""
    query = f"dataset dataset={query}"
    command = ['dasgoclient', '--query', query]
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    print(result.stdout)
    datasets = result.stdout.strip().split('\n')
    return datasets 


def checkDASEntry(dataset = '/SingleMuon'):
    # data2018Post = '/Run2018*02Dec2019*-v*/NANOAOD'
    data2018Post = '/*UL2018_MiniAODv2_NanoAODv9_v*/NANOAOD'
    datasets = get_dataset_names(dataset+data2018Post)
    print(datasets)

    for idata in datasets:
        query = f"summary dataset={idata}"
        command = ['dasgoclient', '--query', query, '--format', 'json']
        # print(command)
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        if result.returncode != 0:
            print(f"Error running dasgoclient for dataset {idata}: {result.stderr}")
            return None

        try:
            summary = json.loads(result.stdout)
            # print(f"Summary for dataset {idata}: {summary}")
            if 'summary' in summary['data'][0] and summary['data'][0]['summary']:
                events =  summary['data'][0]['summary'][0]['nevents']
            else:
                print(f"No event information found for dataset {dataset}")
                return None

        except json.JSONDecodeError as e:
            print(f"Error parsing JSON output for idata {idata}: {e}")
            return None

        print(f"Dataset {idata} has {events} events")

        

def get_root_files(directory):
    """Get a list of all ROOT files in the given directory."""
    return [os.path.join(directory, f) for f in os.listdir(directory) if f.endswith('.root')]

# def get_total_events(files):
#     """Get the total number of events in the 'Event' tree across all ROOT files."""
#     total_events = 0
#     for file in files:
#         root_file = ROOT.TFile.Open(file)
#         if not root_file or root_file.IsZombie():
#             print(f"Failed to open {file}")
#             continue
#         tree = root_file.Get('Events')
#         if not tree:
#             print(f"No 'Event' tree in {file}")
#             continue
#         total_events += tree.GetEntries()
#         root_file.Close()
#     return total_events

def get_total_events(directory, tree_name='Events'):
    """Get the total number of events in the specified tree across all ROOT files in the directory."""
    chain = ROOT.TChain(tree_name)
    root_files = get_root_files(directory)
    
    for file in root_files:
        chain.Add(file)
    
    total_events = chain.GetEntries()
    return total_events
    
if __name__ == '__main__':
    main() 