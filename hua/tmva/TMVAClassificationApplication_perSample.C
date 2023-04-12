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

#include "../src_cpp/lumiAndCrossSection.h"
#include "../src_cpp/usefulFuction.h"

void TMVAClassificationApplication_perSample(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5baselineExtraTauLepCut_v41addVertexSelection/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5baselineExtraTauLepCut_v41addVertexSelection/data/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v51TESNewLepFoLepForrObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1cut1tau1l_v51TESNewLepFoLepForrObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1cut1tau1l_v51TESNewLepFoLepForrObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5extra1tau1lCut_v56preselection/mc/",
    TString inputProcess = "tttt",
    // TString inputProcess = "jetHT_2016F",
    TString version = "test",
    // TString channel = "1tau1lCR0",
    TString channel = "1tau1lSR",
    const Int_t binNum = 10,
    // TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v8Cut1tau1l_v42fixedChargeType/1tau1l_v0/variableList/varibleList_12.csv",
    // TString weightDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v8Cut1tau1l_v42fixedChargeType/1tau1l_v0/dataset/1tau1lvaribleList_12_weight/",
    TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/variableList/varibleList_17.csv",
    TString weightDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/dataset/1tau1lvaribleList_17_weight/",
    TString outputDir = "output/",
    // TString era = "2016"
    TString era = "2017"
    // Bool_t isTest = kTRUE
)
{

    // This loads the library
    TMVA::Tools::Instance();
    std::map<std::string, int> Use;
    Use["BDT"] = 1;

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
            std::cout << "reading ivariable =" << ivariable << "\n";
            variablesName.push_back(ivariable);
            variablesForReader.push_back(0.0);
            variablesOrigin.push_back(0.0);
            if (ivariable.Contains("number") || ivariable.Contains("num") || ivariable.Contains("chargeMulti"))
            {
                std::cout << "reading int ivariable =" << ivariable << "\n";
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
    TString processName = inputProcess;
    // TString processName = inputProcess( 0, inputProcess.Length()-inputProcess.Index(".root")-1 );
    std::cout << "processName=" << processName << "\n";
    Bool_t isdata = kFALSE;
    if (processName.Contains("jetHT"))
    {
        isdata = kTRUE;
    }

    // TString s_variableNum = std::to_string(variableNum);
    TString outFileName = outputDir + processName + ".root";
    TFile *out = new TFile(outFileName, "RECREATE");
    TH1D *histBdt = new TH1D(channel + "_" + processName + "_BDT", "BDT score", binNum, -0.28, 0.12); // 2017 CR0
    TH1D *histBdt_pileup_up = new TH1D(channel + "_" + processName + "_BDT_CMS_pileup_2016postVFP_up", "BDT score", binNum, -0.22, 0.48);
    TH1D *histBdt_pileup_down = new TH1D(channel + "_" + processName + "_BDT_CMS_pileup_2016postVFP_down", "BDT score", binNum, -0.22, 0.48);
    TH1D *histBdt_prefiring_up = new TH1D(channel + "_" + processName + "_BDT_CMS_prefiring_2016postVFP_up", "BDT score", binNum, -0.22, 0.48);
    TH1D *histBdt_prefiring_down = new TH1D(channel + "_" + processName + "_BDT_CMS_prefiring_2016postVFP_down", "BDT score", binNum, -0.22, 0.48);

    TFile *input = new TFile(inputDir + inputProcess + ".root", "READ");
    TTree *theTree = (TTree *)input->Get("newtree");
    for (UInt_t i = 0; i < variableNum; i++)
    {
        if (variablesName[i].Contains("number") || variablesName[i].Contains("num") || variablesName[i].Contains("chargeMulti"))
            continue;
        theTree->SetBranchAddress(variablesName[i], &variablesOrigin[i]);
    }
    for (UInt_t v = 0; v < variablesName_int.size(); v++)
    {
        theTree->SetBranchAddress(variablesName_int[v], &variablesOrigin_int[v]);
    }

    // for selection
    Int_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num, leptonsMVAT_2OS, elesTopMVAT_number, muonsTopMVAT_number;
    Double_t jets_HT, jets_6pt;
    theTree->SetBranchAddress("tausT_number", &tausT_number);
    // theTree->SetBranchAddress("leptonsMVAT_number", &leptonsMVAT_number);
    theTree->SetBranchAddress("elesTopMVAT_number", &elesTopMVAT_number);
    theTree->SetBranchAddress("muonsTopMVAT_number", &muonsTopMVAT_number);
    theTree->SetBranchAddress("jets_number", &jets_number);
    theTree->SetBranchAddress("bjetsM_num", &bjetsM_num);
    theTree->SetBranchAddress("leptonsMVAT_2OS", &leptonsMVAT_2OS);
    theTree->SetBranchAddress("jets_HT", &jets_HT);
    theTree->SetBranchAddress("jets_6pt", &jets_6pt);
    Double_t EVENT_genWeight, EVENT_prefireWeight, EVENT_prefireWeight_up, EVENT_prefireWeight_down, PUweight_, PUweight_up_, PUweight_down_; // btagEfficiency_weight, HLTefficiency_weight;
    theTree->SetBranchAddress("EVENT_genWeight", &EVENT_genWeight);
    theTree->SetBranchAddress("EVENT_prefireWeight", &EVENT_prefireWeight);
    theTree->SetBranchAddress("EVENT_prefireWeight_up", &EVENT_prefireWeight_up);
    theTree->SetBranchAddress("EVENT_prefireWeight_down", &EVENT_prefireWeight_down);
    theTree->SetBranchAddress("PUweight_", &PUweight_);
    theTree->SetBranchAddress("PUweight_up_", &PUweight_up_);
    theTree->SetBranchAddress("PUweight_down_", &PUweight_down_);

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
        leptonsMVAT_number = elesTopMVAT_number + muonsTopMVAT_number;
        if (channel.CompareTo("1tau1lSR") == 0)
        {
            // Returns returns zero if the two strings are identical, otherwise returns the difference between the first two differing bytes
            if (!(tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 7 && bjetsM_num >= 2))
                continue;
        }
        else if (channel.CompareTo("1tau1lCR0") == 0)
        {
            // if (!(tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 7 && bjetsM_num == 1))
            if (!(tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 6 && bjetsM_num == 1))
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
        // Double_t basicWeight = EVENT_genWeight * EVENT_prefireWeight * PUweight_;

        if (Use["BDT"])
        {
            Double_t bdtScore = reader->EvaluateMVA("BDT method");
            if (!isdata)
            {
                // histBdt->Fill(bdtScore, basicWeight);
                histBdt->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight * PUweight_);
                histBdt_pileup_up->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight * PUweight_up_);
                histBdt_pileup_down->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight * PUweight_down_);
                histBdt_prefiring_up->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight_up * PUweight_);
                histBdt_prefiring_down->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight_down * PUweight_);
            }
            else
            {
                histBdt->Fill(bdtScore);
            }
        }
    }
    delete reader;
    // Get elapsed time
    sw.Stop();

    // scale hist
    if (!isdata)
    {
        Double_t genWeightSum = getGenSum(inputDir + inputProcess + ".root");
        Double_t processScale = ((lumiMap[era] * crossSectionMap[processName]) / genWeightSum);
        std::cout << processName << ": " << processScale << "\n";

        histBdt->Scale(processScale);
        histBdt_pileup_up->Scale(processScale);
        histBdt_pileup_down->Scale(processScale);
        histBdt_prefiring_up->Scale(processScale);
        histBdt_prefiring_down->Scale(processScale);
    }
    else
    {
        std::cout << processName << ": not MC, no scaling of hist\n";
    }

    histBdt->SetDirectory(out);
    // histBdt->SetDirectory(out);
    out->Write();
    // histBdt->Write();
    std::cout << "output file here: " << out->GetName() << "\n";
    out->Close();
};