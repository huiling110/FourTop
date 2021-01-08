
void getGenNum( const string inputfile="TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root" ){

    string file  = "/publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/"+ inputfile;
    const char *tfile = file.c_str();
    TFile *file_ = TFile::Open(tfile);
    TTree* tree = (TTree*)file_->Get("TNT/BOOM");
    TBranch *b_EVENT_genWeight; double_t EVENT_genWeight_;
    tree->SetBranchAddress("EVENT_genWeight",   &EVENT_genWeight_,   &b_EVENT_genWeight);

    Long64_t nentries =   (Int_t)tree->GetEntries();
    double sum = 0;
    for (Long64_t i = 0; i < nentries; i++) {
        Long64_t tentry = tree->LoadTree(i);
        b_EVENT_genWeight->GetEntry(tentry);
        sum = sum + EVENT_genWeight_;
    }
    std::cout<<"gen number for "<<inputfile<<" : "<<sum<<endl;

}
