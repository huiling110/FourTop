
void getMultipleNtuples(){
    // TString inputDir = "/publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/Legacy16V2_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8HLTToptaggerAdded_EJetMetUpdated_oldEIDBack/200902_082739/0000/";
    TString inputDir = "/publicfs/cms/data/TopQuark/FourTop_hua/v2/mc/2016/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8HLTToptaggerAdded_EJetMetUpdated_oldEIDBack/201216_122412/0000/";//110,000,000

    // TChain chain("TNT/BOOM");
    TChain chain("TNT/evtree");
    // chain.Add(inputDir+"TauOfTTTT_Toptagger_oldEID_1-1.root");
    // chain.Add(inputDir+"TauOfTTTT_Toptagger_oldEID_1-20.root");
    chain.Add(inputDir+"TauOfTTTT_Toptagger_oldEID*.root");
    // double_t entry = chain.GetEntries();
    // Long64_t entry = chain.GetEntries();
    ULong64_t entry = chain.GetEntries();
    cout<<entry<<endl;

}
