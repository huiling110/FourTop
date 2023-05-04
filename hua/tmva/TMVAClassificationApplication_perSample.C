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
#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/writeVariableHist/histsForRegionsMap_class.C"

void TMVAClassificationApplication_perSample(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5baselineExtraTauLepCut_v41addVertexSelection/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5baselineExtraTauLepCut_v41addVertexSelection/data/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v51TESNewLepFoLepForrObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1cut1tau1l_v51TESNewLepFoLepForrObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1cut1tau1l_v51TESNewLepFoLepForrObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v6baseline_v56preselection/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6baseline_v56NoHLTButPre/mc/",
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
    TString era = "2016",
    // TString era = "2017"
    Bool_t ifSys = kTRUE)
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
            if (ivariable.Contains("number") || ivariable.Contains("num") || ivariable.Contains("charge"))
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
    // TH1D *histBdt = new TH1D(channel + "_" + processName + "_BDT", "BDT score", binNum, -0.28, 0.12); //
    TH1D *histBdt = new TH1D("1tau1lSR_" + processName + "_BDT", "BDT score", 30, -0.28, 0.4);          //
    TH1D *histBdt_CR0 = new TH1D("1tau1lCR0_" + processName + "_BDT", "BDT score", binNum, -0.28, 0.4); //
    TH1D *histBdt_CR2 = new TH1D("1tau1lCR2_" + processName + "_BDT", "BDT score", binNum, -0.28, 0.4); //
    TH1D *histBdt_pileup_up = new TH1D(channel + "_" + processName + "_BDT_CMS_pileup_2016postVFP_up", "BDT score", binNum, -0.22, 0.48);
    TH1D *histBdt_pileup_down = new TH1D(channel + "_" + processName + "_BDT_CMS_pileup_2016postVFP_down", "BDT score", binNum, -0.22, 0.48);
    TH1D *histBdt_prefiring_up = new TH1D(channel + "_" + processName + "_BDT_CMS_prefiring_2016postVFP_up", "BDT score", binNum, -0.22, 0.48);
    TH1D *histBdt_prefiring_down = new TH1D(channel + "_" + processName + "_BDT_CMS_prefiring_2016postVFP_down", "BDT score", binNum, -0.22, 0.48);

    std::vector<TString> sysRegions = {"1tau1lSR", "1tau1lPileupUp", "1tau1lPileupDown"};
    histsForRegionsMap SR1tau1lSys{"BDT", "BDT score", processName, 20, -0.28, 0.4, sysRegions};

    TFile *input = new TFile(inputDir + inputProcess + ".root", "READ");
    TTree *theTree = (TTree *)input->Get("newtree");
    for (UInt_t i = 0; i < variableNum; i++)
    {
        if (variablesName[i].Contains("number") || variablesName[i].Contains("num") || variablesName[i].Contains("charge"))
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
    theTree->SetBranchAddress("elesTopMVAT_number", &elesTopMVAT_number);
    theTree->SetBranchAddress("muonsTopMVAT_number", &muonsTopMVAT_number);
    theTree->SetBranchAddress("jets_number", &jets_number);
    theTree->SetBranchAddress("bjetsM_num", &bjetsM_num);
    theTree->SetBranchAddress("leptonsMVAT_2OS", &leptonsMVAT_2OS);
    theTree->SetBranchAddress("jets_HT", &jets_HT);
    theTree->SetBranchAddress("jets_6pt", &jets_6pt);
    Double_t EVENT_genWeight, EVENT_prefireWeight, EVENT_prefireWeight_up, EVENT_prefireWeight_down, PUweight_, PUweight_up_, PUweight_down_, HLT_weight, tauT_IDSF_weight_new, elesTopMVAT_weight, musTopMVAT_weight, btagShape_weight, btagShapeR;
    theTree->SetBranchAddress("EVENT_genWeight", &EVENT_genWeight);
    theTree->SetBranchAddress("EVENT_prefireWeight", &EVENT_prefireWeight);
    theTree->SetBranchAddress("EVENT_prefireWeight_up", &EVENT_prefireWeight_up);
    theTree->SetBranchAddress("EVENT_prefireWeight_down", &EVENT_prefireWeight_down);
    theTree->SetBranchAddress("PUweight_", &PUweight_);
    theTree->SetBranchAddress("PUweight_up_", &PUweight_up_);
    theTree->SetBranchAddress("PUweight_down_", &PUweight_down_);
    theTree->SetBranchAddress("HLT_weight", &HLT_weight);
    theTree->SetBranchAddress("tauT_IDSF_weight_new", &tauT_IDSF_weight_new);
    theTree->SetBranchAddress("elesTopMVAT_weight", &elesTopMVAT_weight);
    theTree->SetBranchAddress("musTopMVAT_weight", &musTopMVAT_weight);
    theTree->SetBranchAddress("btagShape_weight", &btagShape_weight);
    theTree->SetBranchAddress("btagShapeR", &btagShapeR);

    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();
    // for (Long64_t ievt = 0; ievt < theTree->GetEntries(); ievt++)
    // {
    for (Long64_t ievt = 0; ievt < 1000; ievt++)
    {

        theTree->GetEntry(ievt);
        // baseline selection
        if (!(jets_number >= 6 && jets_6pt > 40.0 && jets_HT > 500.0 && bjetsM_num >= 1))
        {
            return kFALSE;
        }

        // jets_bScore = jets_bScore_origin;
        for (UInt_t j = 0; j < variableNum; j++)
        {
            // variablesForReader[j] = variablesOrigin[j];
            variablesForReader.at(j) = variablesOrigin.at(j);
        }
        // cout<<"\n";
        // channel selection
        leptonsMVAT_number = elesTopMVAT_number + muonsTopMVAT_number;

        // Return the MVA outputs and fill into histograms
        // Double_t basicWeight = EVENT_genWeight * EVENT_prefireWeight * PUweight_;
        Double_t basicWeight = EVENT_prefireWeight * EVENT_genWeight * PUweight_ * HLT_weight * tauT_IDSF_weight_new * elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR;

        // if (Use["BDT"])
        // {
        Double_t bdtScore = reader->EvaluateMVA("BDT method");
        // }
        Bool_t SR1tau1l = tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 7 && bjetsM_num >= 2;
        // if (tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 7 && bjetsM_num >= 2)
        // {
        // histFill(SR1tau1l, isdata, basicWeight, bdtScore, histBdt);
        // if (!isdata)
        // {

        //     histBdt->Fill(bdtScore, basicWeight);
        // }
        // else
        // {
        //     histBdt->Fill(bdtScore);
        // }
        // }
        SR1tau1lSys.fillHistVec("1tau1lSR", bdtScore, basicWeight, SR1tau1l, isdata);

        if (tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 6 && bjetsM_num == 1)
        {
            if (!isdata)
            {
                histBdt_CR0->Fill(bdtScore, basicWeight);
            }
            else
            {
                histBdt_CR0->Fill(bdtScore);
            }
        }
        if (tausT_number == 1 && leptonsMVAT_number == 1 && jets_number == 6 && bjetsM_num >= 2)
        {
            if (!isdata)
            {
                histBdt_CR2->Fill(bdtScore, basicWeight);
            }
            else
            {
                histBdt_CR2->Fill(bdtScore);
            }
        }
        // histBdt->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight * PUweight_);
        histBdt_pileup_up->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight * PUweight_up_);
        histBdt_pileup_down->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight * PUweight_down_);
        histBdt_prefiring_up->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight_up * PUweight_);
        histBdt_prefiring_down->Fill(bdtScore, EVENT_genWeight * EVENT_prefireWeight_down * PUweight_);
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
        histBdt_CR0->Scale(processScale);
        histBdt_CR2->Scale(processScale);
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