#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <iostream>

void checkBranchType(
    const char* filename="/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/2022postEE_v3/tttt/tree_1.root", 
    const char* treename= "Events", 
    const char* branchname="Electron_pt"
    ) {
    // Open the ROOT file
    TFile *f = TFile::Open(filename);
    if (!f || f->IsZombie()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Retrieve the TTree object
    TTree *tree;
    f->GetObject(treename, tree);
    if (!tree) {
        std::cerr << "Tree '" << treename << "' not found in file: " << filename << std::endl;
        f->Close();
        return;
    }

    // Get the TBranch object
    TBranch *branch = tree->GetBranch(branchname);
    if (!branch) {
        std::cerr << "Branch '" << branchname << "' not found in tree: " << treename << std::endl;
        f->Close();
        return;
    }

    // Check if the branch is an array
    bool isArray = false;
    TIter next(branch->GetListOfLeaves());
    TLeaf *leaf;
    while ((leaf = (TLeaf*)next())) {
        if (leaf->GetLeafCount() != nullptr || leaf->IsOnTerminalBranch() == kFALSE) {
            isArray = true;
            break;
        }
    }

    //get branch type
    TClass* branchClass;
    EDataType branchType;
    branch->GetExpectedType(branchClass, branchType);
    std::cout<<"branchType: "<<branchType<<"\n";

    // Print the result
    if (isArray) {
        std::cout << "The branch '" << branchname << "' is an array." << std::endl;
    } else {
        std::cout << "The branch '" << branchname << "' is not an array." << std::endl;
    }

    // Close the file
    f->Close();
}

// To execute the macro automatically when running ROOT, include the following lines:
#ifndef __CINT__
int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <treename> <branchname>" << std::endl;
        return 1;
    }
    checkBranchType(argv[1], argv[2], argv[3]);
    return 0;
}
#endif
