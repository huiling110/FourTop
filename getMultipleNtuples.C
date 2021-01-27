
void getMultipleNtuples(){
    TString baseDir = "/publicfs/cms/data/TopQuark/FourTop_hua/v2/mc/2016/";
    // TString inputDir = "/publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/Legacy16V2_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8HLTToptaggerAdded_EJetMetUpdated_oldEIDBack/200902_082739/0000/";
    TString sample  = "TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8HLTToptaggerAdded_EJetMetUpdated_oldEIDBack/201216_122412/0000/";//110,000,000
    // TString sample = "JetHT/Legacy16V2_JetHTBlockCHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060426/0000/";
    // TString sample = "JetHT/Legacy16V2_JetHTBlockDHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060636/0000/";
    // TString sample = "TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/Legacy16V2_TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8v2_checkforv2/210121_152453/0000/";
    // TString sample = "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8HLTToptaggerAdded_EJetMetUpdated_oldEIDBack/201216_122623/0000/";
    TString inputDir = baseDir + sample;

    // TChain chain("TNT/BOOM");
    TChain chain("TNT/evtree");
    // chain.Add(inputDir+"TauOfTTTT_Toptagger_oldEID_1-1.root");
    chain.Add(inputDir+"TauOfTTTT_Toptagger_oldEID*.root");
    // chain.Add(inputDir+"TauOfTTTT_TopTagger_oldEID*.root");
    // chain.Add(inputDir+"smalltest*.root");
    // double_t entry = chain.GetEntries();
    // Long64_t entry = chain.GetEntries();
    ULong64_t entry = chain.GetEntries();
    // chain.Print();
    cout<<sample<<": "<<endl;
    cout<<entry<<endl;

}
