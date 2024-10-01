import ROOT
import csv

def get_branch_names(root_file, tree_name, output_csv):
    # Open the root file
    file = ROOT.TFile(root_file, "READ")
    if file.IsZombie():
        print("Error: Could not open file!")
        return
    
    # Get the tree
    tree = file.Get(tree_name)
    if not tree:
        print(f"Error: Could not find tree '{tree_name}' in file!")
        return

    # Get branch names
    branches = tree.GetListOfBranches()
    branch_names = [branch.GetName() for branch in branches]

    # Write branch names to csv
    with open(output_csv, mode='w', newline='') as file:
        writer = csv.writer(file)
        # writer.writerow(["Branch Names"])  # Optional: add header
        for branch_name in branch_names:
            if 'Weight' in branch_name or 'weight' in branch_name: continue
            if 'HLT' in branch_name: continue
            if 'muonsT' in branch_name or 'eleMVAT' in branch_name: continue
            if 'tausTT' in branch_name or 'tausTTT' in branch_name or 'tausTTTT' in branch_name or 'tausM' in branch_name: continue
            if 'bjetsPN' in branch_name or 'bjetsPT' in branch_name: continue
            writer.writerow([branch_name])

    # Close the root file
    file.Close()

# Example usage:
root_file_path = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau2lSR_v84Pre1tau2lLepF2/mc/tttt.root"
tree_name = "newtree"
output_csv_path = "branch_names.csv"

get_branch_names(root_file_path, tree_name, output_csv_path)