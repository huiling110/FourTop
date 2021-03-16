

void checkEntriesT2T3(){

    TString T3dir = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/Legacy16V2_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8addGenWeight/210201_023840/0000/";
    TChain chainT3("TNT/BOOM");   
    chainT3.Add( T3dir + "v3*root");
    cout<<chainT3.GetEntries()<<endl;

    TString T2dir = "root://ccsrm.ihep.ac.cn/dpm/ihep.ac.cn/home/cms/store/user/hhua/v3/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/Legacy16V2_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8addGenWeight/210201_023840/0000/";
    TChain chainT2("TNT/BOOM");
    chainT2.Add( T2dir + "v3*root");
    cout<<chainT2.GetEntries();



}
