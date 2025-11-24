import ROOT

def main():
    # root_file_name = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/makeVariables_goodCode/output/tttt.root"  # Update this with the path to your ROOT file
    root_file_name = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v76WithVLLAllMass/mc/tttt.root'
    csv_file_name = "branch_names.csv" # Desired output CSV file name

    write_branch_names_to_csv(root_file_name,  csv_file_name)



def write_branch_names_to_csv(root_file_name,  csv_file_name, tree_name='newtree'):
    # Open the ROOT file
    file = ROOT.TFile.Open(root_file_name, "READ")
    
    if not file:
        print(f"Failed to open file {root_file_name}")
        return
    
    # Access the tree
    tree = file.Get(tree_name)
    
    if not tree:
        print(f"Tree {tree_name} not found")
        return
    
    # Open a CSV file for writing
    with open(csv_file_name, 'w') as csv_file:
        # Write the header
        # csv_file.write("BranchName\n")
                # Loop over the branches and write their names to the CSV file
        branches = tree.GetListOfBranches()
        for branch in branches:
            branch_name = branch.GetName()
            if 'eta' in branch_name or 'phi' in branch_name: continue
            # if 'elesMVT' in branch_name or 'elesTopMVAT' in branch_name: continue
            # if 'tausF_' in branch_name or 'tausL_' in branch_name or 'tausM_' in branch_name: continue
            if 'gen' in branch_name: continue
            if 'bjetsPN' in branch_name or 'bjetsPT' in branch_name: continue
            if 'HLT' in branch_name: continue
            if 'Weight' in branch_name or 'weight' in branch_name: continue
            csv_file.write(f"{branch_name}\n")
    
    print(f"Branch names written to {csv_file_name}")
    
    
if __name__=='__main__':
    main()

