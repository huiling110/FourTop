
void compareCutflow()
{
    // TString myFile = "/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/makeVariables/output/variableHists_vtest/tttt.root";
    // TString XiaonanFile = "/cms/user/houxiaonan/4top/check/2016/outTree_4_Skim.root";
    TString myFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/cutflowCheck/variableHists_forCutflow/tttt.root";
    TString XiaonanFile = "/cms/user/houxiaonan/4top/checkAPV/2016APV/tttt/outTree_5_Skim.root";

    // TString myFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0noBaseline_v27noJERnoTESWithObjectRemoval/mc/variableHists_v4add1tau1lCutflow/tttt.root";
    // TString XiaonanFile = "/cms/user/houxiaonan/4top/checkAPV/2016APV/tttt/outTree_*.root";

    // TChain *huaTree = new TChain("cutFlowTree");
    // huaTree->Add(myFile);

    TFile *huaFile = new TFile(myFile, "READ");
    TTree *huaTree = (TTree *)huaFile->Get("cutFlowTree");
    // huaTree->BuildIndex("event_", "ifPassJets_6pt");
    huaTree->Print();
    ULong64_t huaEvent;
    Bool_t huaPassJet6, houPassJet6;
    Double_t huajet6pt;
    Double_t houjet6pt;
    huaTree->SetBranchAddress("event_", &huaEvent);
    huaTree->SetBranchAddress("ifPassJets_6pt", &huaPassJet6);
    huaTree->SetBranchAddress("jets_6pt_", &huajet6pt);

    // TChain *houTree = new TChain("Events");
    // houTree->Add(XiaonanFile);
    TFile *houFile = new TFile(XiaonanFile, "READ");
    TTree *houTree = (TTree *)houFile->Get("Events");
    ULong64_t houEvent;

    TTree *newhou = houTree->CopyTree("passHLT==1");
    newhou->AddFriend(huaTree);
    newhou->SetBranchAddress("event", &houEvent);
    newhou->SetBranchAddress("passjet6", &houPassJet6);
    newhou->SetBranchAddress("jet6_pt", &houjet6pt);
    newhou->Print();

    // houTree->Scan("cutFlowTree.event_:Events.event");

    // for (UInt_t en = 0; en < newhou->GetEntries(); en++)
    for (UInt_t en = 0; en < newhou->GetEntries(); en++)
    {
        newhou->GetEntry(en);
        // if (en < 20)
        // {

        if (!(huaEvent == houEvent && huaPassJet6 == houPassJet6))
        {
            printf("huaEvent=%lli houEvent=%lli  huaPassjet6=%i houPass=%i hua6jetpt=%lf hou6jetpt=%lf \n", huaEvent, houEvent, huaPassJet6, houPassJet6, huajet6pt, houjet6pt);
            std::cout << std::setprecision(15);
            std::cout << huajet6pt << " \n";
            std::cout << std::setprecision(15);
            std::cout << houjet6pt << "\n";
            // cout << "good\n";
        }
        // else
        // {

        //     cout << "everything the same!\n";
        // }
        // else
        // {
        // cout << "wrong\n";
        // }
        // }

        // printf("%")
    }
}