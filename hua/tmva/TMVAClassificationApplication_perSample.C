#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
// #include "../EYandSP_usingClass_v3.h"

#include "lumiAndCrossSection.h"

#include "../src_cpp/usefulFuction.h"

void TMVAClassificationApplication_perSample(
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5baselineExtraTauLepCut_v41addVertexSelection/mc/",
    TString inputProcess = "tttt.root",
    TString version = "test",
    TString channel = "1tau1lCR0",
    const Int_t binNum = 30,
    TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/variableList/varibleList_10.csv",
    TString weightDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/dataset/1tau1lvaribleList_10_weight/",
    TString outputDir = "output/TMVAApp_10var_1tau1lCR0/",
    TString era = "2016",
    Bool_t isTest = kTRUE
){
    
    // This loads the library
    TMVA::Tools::Instance();
    std::map<std::string, int> Use;
    Use["BDT"]=1;

    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");

    std::cout << "reading varibleList: " << variableListCsv << "\n";
    ifstream fin(variableListCsv);
    string line;
    TString ivariable;
    vector<TString> variablesName{};
    vector<Float_t> variablesForReader;
    vector<Double_t> variablesOrigin;
    vector<TString> variablesName_int{};
    vector<Int_t> variablesOrigin_int;
    while (getline(fin, line))
    {
        ivariable = line;
        if (line.size() > 0)
        {
            std::cout <<"reading ivariable =" <<ivariable << "\n";
            variablesName.push_back(ivariable);
            variablesForReader.push_back(0.0);
            variablesOrigin.push_back(0.0);
            if (ivariable.Contains("number") || ivariable.Contains("num")){
                std::cout <<"reading int ivariable =" <<ivariable << "\n";
                variablesName_int.push_back(ivariable);
                variablesOrigin_int.push_back(0);
            }
        }
    }
    fin.close();


    UInt_t variableNum = variablesName.size();
    for (UInt_t v = 0; v < variableNum; v++)
    {
        reader->AddVariable(variablesName[v], &variablesForReader[v]);
        //???it seems even for int type we have to add as float
    }
    // Book the MVA methods
    TString prefix = "TMVAClassification";
    // Book method(s)
    for (std::map<std::string, int>::iterator it = Use.begin(); it != Use.end(); it++)
    {
        if (it->second)
        {
            TString methodName = TString(it->first) + TString(" method");
            TString weightfile = weightDir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
            reader->BookMVA(methodName, weightfile);
        }
    }

    // Book output histograms
    TString processName = inputProcess( 0, inputProcess.Length()-inputProcess.Index(".root")-1 );
    std::cout<<"processName="<<processName<<"\n";
    // TH1D* histBdt = new TH1D(processName + "_MVA_BDT", "MVA_BDT", binNum, -0.18, 0.34);
    TH1D* histBdt = new TH1D( channel +"_"+ processName + "_BDT", "BDT score", binNum, -0.18, 0.34);

    
    TFile* input = new TFile(inputDir+inputProcess, "READ");
    TTree* theTree = (TTree*)input->Get("newtree");
    for (UInt_t i = 0; i < variableNum; i++)
    {
        if( variablesName[i].Contains("number") || variablesName[i].Contains("num")) continue;
        theTree->SetBranchAddress(variablesName[i], &variablesOrigin[i]);
    }
    for (UInt_t v = 0; v < variablesName_int.size(); v++)
    {
        theTree->SetBranchAddress(variablesName_int[v], &variablesOrigin_int[v]);
    }

    // for selection
    //  Float_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num, jets_HT;
    Int_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num, leptonsMVAT_2OS;
    Double_t jets_HT, jets_6pt;
    theTree->SetBranchAddress("tausT_number", &tausT_number);
    theTree->SetBranchAddress("leptonsMVAT_number", &leptonsMVAT_number);
    theTree->SetBranchAddress("jets_number", &jets_number);
    theTree->SetBranchAddress("bjetsM_num", &bjetsM_num);
    theTree->SetBranchAddress("leptonsMVAT_2OS", &leptonsMVAT_2OS);
    theTree->SetBranchAddress("jets_HT", &jets_HT);
    theTree->SetBranchAddress("jets_6pt", &jets_6pt);
    Double_t EVENT_genWeight, EVENT_prefireWeight, PUweight; // btagEfficiency_weight, HLTefficiency_weight;
    theTree->SetBranchAddress("EVENT_genWeight", &EVENT_genWeight);
    theTree->SetBranchAddress("EVENT_prefireWeight", &EVENT_prefireWeight);
    theTree->SetBranchAddress("PUweight", &PUweight);


    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();
    for (Long64_t ievt = 0; ievt < theTree->GetEntries(); ievt++)
    {
        // for (Long64_t ievt=0; ievt<1000;ievt++) {

        theTree->GetEntry(ievt);
        // baseline selection
        if (!(jets_number >= 6 && jets_6pt > 40.0 && jets_HT > 500.0))
        {
            return kFALSE;
        }

        // jets_bScore = jets_bScore_origin;
        // toptagger_MHT = toptagger_MHT_origin;
        for (UInt_t j = 0; j < variableNum; j++)
        {
            // variablesForReader[j] = variablesOrigin[j];
            variablesForReader.at(j) = variablesOrigin.at(j);
        }
        // cout<<"\n";
        // channel selection
        if (channel.CompareTo("1tau1l") == 0)
        {
            // Returns returns zero if the two strings are identical, otherwise returns the difference between the first two differing bytes
            if (!(tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 7 && bjetsM_num >= 2))
                continue;
        }
        else if (channel.CompareTo("1tau1lCR0") == 0)
        {
            if (!(tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 7 && bjetsM_num == 1))
                continue;
        }
        else if (channel.CompareTo("1tau2l") == 0)
        {
            if (!(tausT_number == 1 && leptonsMVAT_number == 2 && jets_number >= 6 && bjetsM_num >= 2))
                continue;
        }
        else
        {
            std::cout << "no event selection for channel\n";
        }

        // Return the MVA outputs and fill into histograms
        // Double_t eventWeight = EVENT_genWeight * EVENT_prefireWeight * PUweight * btagEfficiency_weight * HLTefficiency_weight;
        Double_t basicWeight = EVENT_genWeight * EVENT_prefireWeight * PUweight;

        if (Use["BDT"])
            histBdt->Fill(reader->EvaluateMVA("BDT method"), basicWeight);
    }
    delete reader;
    // Get elapsed time
    sw.Stop();

    //scale hist
    Bool_t isdata = kFALSE;
    if processName.Contains("jetHT") {
        isdata = kTRUE;
    }
    if (!isdata){

		processScale = ((lumiMap[era] * crossSectionMap[processName]) / m_genWeightSum);
        histBdt->Scale(processScale);
    }

    TString s_variableNum = std::to_string(variableNum);
    // TString outFileName = outputDir + "TMVApp_" + channel + "_" + s_variableNum + "var_forCombine.root";
    TString outFileName = outputDir + processName +".root";
    TFile* out = new TFile(outFileName, "RECREATE");
    histBdt->SetDirectory(out);
    histBdt->Write();
    std::cout<<"output file here: "<<out->GetName()<<"\n";
    out->Close();
    

};