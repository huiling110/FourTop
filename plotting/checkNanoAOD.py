
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
    nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/data/singleMu_2018a/'
    
    # fileNum = getNumFiles(nanoDir)
    # print(nanoDir)
    # print('fileNum=: ', fileNum)
    # total = get_total_events(nanoDir)
    # print(f"Total events: {total}")

    checkDASEntry()




def get_dataset_names(query):
    """Get dataset names matching the query."""
    query = f"dataset dataset={query}"
    command = ['dasgoclient', '--query', query]
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    print(result.stdout)
    datasets = result.stdout.strip().split('\n')
    return datasets 


def checkDASEntry(dataset = 'SingleMuon'):
    data2018Post = '/Run2018*02Dec2019*-v*/NANOAOD'
    data = '/SingleMuon'
    # datasets = 
    # data = '/SingleMuon/Run2018A-Nano02Dec2019-v1/NANOAOD'
    # command = f'dasgoclient -query="summary dataset={data+data2018Post}"'
    # command = f'dasgoclient -query="summary dataset={data}"'
    # uf.runCommand(command)
    datasets = get_dataset_names(data+data2018Post)
    print(datasets)

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