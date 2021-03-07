void skimNtuple{

    TFile *oldfile = new TFile ("/publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root");
    TTree *oldTree = (TTree*)oldfile->Get("TNT/tree");

    TFile newfile = new TFile("TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_skimmed.root")
    TTree *newTree = oldTree->CopyTree("track<595");
    newfile->Write();
    delete oldfile;
    delete newfile;
}
