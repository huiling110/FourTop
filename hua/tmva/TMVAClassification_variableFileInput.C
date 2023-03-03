/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2022-03-03 21:36:07
 * @modify date 2022-03-03 21:36:07
 * @desc [description]
 */
/// \ingroup tutorial_tmva
/// \file
/// \notebook -nodraw
/// This macro provides examples for the training and testing of the
/// TMVA classifiers.
///
/// As input data is used a toy-MC sample consisting of four Gaussian-distributed
/// and linearly correlated input variables.
/// The methods to be used can be switched on and off by means of booleans, or
/// via the prompt command, for example:
///
///     root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)
///
/// (note that the backslashes are mandatory)
/// If no method given, a default set of classifiers is used.
/// The output file "TMVA.root" can be analysed with the use of dedicated
/// macros (simply say: root -l <macro.C>), which can be conveniently
/// invoked through a GUI that will appear at the end of the run of this macro.
/// Launch the GUI via the command:
///
///     root -l ./TMVAGui.C
///
/// You can also compile and run the example with the following commands
///
///     make
///     ./TMVAClassification <Methods>
///
/// where: `<Methods> = "method1 method2"` are the TMVA classifier names
/// example:
///
///     ./TMVAClassification Fisher LikelihoodPCA BDT
///
/// If no method given, a default set is of classifiers is used
///
/// - Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis
/// - Package   : TMVA
/// - Root Macro: TMVAClassification
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <typeinfo>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

#include "../EYandSP_usingClass_v3.h"

Bool_t vectorInBranch(TString branchName, std::vector<TRegexp> &variableList)
{
    Bool_t anyIn = false;
    for (UInt_t i = 0; i < variableList.size(); i++)
    {
        if (branchName.Contains(variableList[i]))
        {
            anyIn = true;
            break;
        }
    }
    return anyIn;
}
///???root interpretation running locally a bit slow
int TMVAClassification_variableFileInput(TString myMethodList = "",
                                         TString outDir = "output/",
                                         // TString outputDir  = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v1/trainWith40Cutbin/",
                                         // TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v1/variableList_check/varibleList_10-3.csv",
                                         TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v1/variableList/varibleList_10.csv",
                                         const TString channel = "1tau1l",
                                         //  const TString channel = "1tau2l",
                                         //   const TString channel = "2tau0l",
                                         Bool_t forVariables = true,
                                         // Bool_t forVariables = false,
                                         Bool_t istest = true
                                         //   Bool_t istest = false
)
{
    std::cout << "baseDir : " << baseDir << "\n";

    // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
    // if you use your private .rootrc, or run from a different directory, please copy the
    // corresponding lines from .rootrc

    // Methods to be processed can be given as an argument; use format:
    //
    //     mylinux~> root -l TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)

    //---------------------------------------------------------------
    TString outfile;
    // Apply additional cuts on the signal and background samples (can be different)
    TString csvListName;
    if (forVariables)
    {
        csvListName = "";
    }
    else
    {
        TPRegexp r1("\\bvaribleList(\\w+).csv\\b");
        csvListName = variableListCsv(r1);
        csvListName.Remove(csvListName.First("."), csvListName.Length());
    }
    cout << "csvListName: " << csvListName << "\n";

    TCut cutForSandB = channelCutMap[channel];
    outfile = channel + csvListName;
    std::cout << channel << ": " << cutForSandB << endl;

    // Double_t allSignal = allProcesses[0].getChannelHist(cutForSandB, basicWeight)->GetEntries();
    Double_t allSignal = allProcesses[0].getEventTree()->GetEntries() + allProcesses2016[0].getEventTree()->GetEntries() + allProcesses2017[0].getEventTree()->GetEntries();
    //???using jets_number for projecting for now
    std::cout << "allSignalEvents: " << allSignal << "\n";
    // Double_t allBg = getAllBgEntries(cutForSandB, basicWeight);
    Double_t allBg = 0;
    for (UInt_t i = 1; i < allProcesses.size(); i++)
    {
        allBg = allBg + allProcesses[i].getEventTree()->GetEntries() + allProcesses2016[i].getEventTree()->GetEntries() + allProcesses2017[i].getEventTree()->GetEntries();
    }
    std::cout << "allBgEvents: " << allBg << "\n";

    TMVA::Tools::Instance();

    //???optimize code here. too many lines
    // Default MVA methods to be trained + tested
    std::map<std::string, int> Use;
    // Cut optimisation
    if (forVariables)
    {
        Use["Cuts"] = 1;
        Use["CutsSA"] = 0;
    }
    else
    {
        Use["Cuts"] = 0;
        // Use["CutsSA"]          = 1;
        Use["CutsSA"] = 0;
    }
    //
    // Boosted Decision Trees
    if (forVariables)
    {
        Use["BDT"] = 0;
        Use["BDTG"] = 0;
        Use["BDTB"] = 0; // uses Bagging
        Use["BDTD"] = 0; // decorrelation + Adaptive Boost
        Use["BDTF"] = 0; // allow usage of fisher discriminant for node splitting
    }
    else
    {
        Use["BDT"] = 1;
        Use["BDTG"] = 0;
        Use["BDTB"] = 0; // uses Bagging
        Use["BDTD"] = 0; // decorrelation + Adaptive Boost
        // Use["BDTF"]            = 1; // allow usage of fisher discriminant for node splitting
        Use["BDTF"] = 0; // allow usage of fisher discriminant for node splitting
    }
    //
    // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
    Use["RuleFit"] = 0;
    // ---------------------------------------------------------------

    std::cout << std::endl;
    std::cout << "==> Start TMVAClassification" << std::endl;

    // Select methods (don't look at this code - not of interest)
    if (myMethodList != "")
    {
        for (std::map<std::string, int>::iterator it = Use.begin(); it != Use.end(); it++)
            it->second = 0;

        std::vector<TString> mlist = TMVA::gTools().SplitString(myMethodList, ',');
        for (UInt_t i = 0; i < mlist.size(); i++)
        {
            std::string regMethod(mlist[i]);

            if (Use.find(regMethod) == Use.end())
            {
                std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
                for (std::map<std::string, int>::iterator it = Use.begin(); it != Use.end(); it++)
                    std::cout << it->first << " ";
                std::cout << std::endl;
                return 1;
            }
            Use[regMethod] = 1;
        }
    }

    // --------------------------------------------------------------------------------------------------

    // Here the preparation phase begins
    // Register the training and test trees

    // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
    TString outfileName;
    if (istest)
    {
        //  outDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/test/";
        outDir = "output/";
        outfile = "TMVA_test";
        outfileName = outDir + outfile + ".root";
    }
    else
    {
        if (forVariables)
            outfileName = outDir + outfile + "_variables.root";
        else
            outfileName = outDir + outfile + ".root";
    }
    TFile *outputFile = TFile::Open(outfileName, "RECREATE");

    // Create the factory object. Later you can choose the methods
    // whose performance you'd like to investigate. The factory is
    // the only TMVA object you have to interact with
    //
    // The first argument is the base of the name of all the
    // weightfiles in the directory weight/
    //
    // The second argument is the output file for the training results
    // All TMVA output can be suppressed by removing the "!" (not) in
    // front of the "Silent" argument in the option string
    // TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");
    //!!!factory parameters
    // The first argument is the user-defined job name that will reappear in the names of the weight files containing the training results.
    //???test the different options of Transformations can do to training

    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
    // TMVA::DataLoader *dataloader=new TMVA::DataLoader( outDir );
    // If you wish to modify default settings
    //!!!tuning here
    // (please check "src/Config.h" to see all available global options)
    //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
    // (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 20;
    (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 30;
    // (TMVA::gConfig().GetVariablePlotting()).fNbins1D  = 40;
    // TMVA::gConfig().GetVariablePlotting().fNbinsMVAoutput = 100 ;
    TMVA::gConfig().GetVariablePlotting().fNbinsMVAoutput = 30;
    (TMVA::gConfig().GetIONames()).fWeightFileDir = outfile + "_weight/";
    TMVA::gConfig().GetIONames().fWeightFileDirPrefix = outDir; // If a non-nul prefix is set in TMVA::gConfig().GetIONames().fWeightFileDirPrefix the weights will be stored in weightfile_prefix/dataset_name/weight_file_name

    // Define the input variables that shall be used for the MVA training
    // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
    // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
    // dataloader->AddVariable( "myvar1 := var1+var2", 'F' );//’F’ indicates any floating point type, i.e., float and double
    // variableListCsv
    if (!forVariables)
    {
        ifstream fin(variableListCsv);
        string line;
        TString ivariable;
        vector<TString> variables{};
        Int_t num = 1;
        while (getline(fin, line))
        {
            if (num > 1)
            {
                ivariable = line;
                // cout<<"line: "<<line;
                if (line.size() > 0)
                {
                    variables.push_back(ivariable);
                }
                // cout<<"ivariable:"<<ivariable<<endl;
            }
            TString ivar = line;
            if (ivar.Contains("num") || ivar.Contains("number") || ivar.Contains("charge"))
            {
                dataloader->AddVariable(line, 'I');
            }
            else
            {
                dataloader->AddVariable(line, 'F');
            }
            num = num + 1;
        }
        fin.close();
    }
    else
    {
        // for generating initial variable list
        std::vector<TString> branchNames;
        TString branchName;
        UInt_t nbr = TTTT.getEventTree()->GetListOfBranches()->GetEntries();
        cout << "number of branches: " << nbr << endl;
        Int_t chosenVariable = 0;
        for (UInt_t i = 0; i < nbr; i++)
        {
            branchName = TTTT.getEventTree()->GetListOfBranches()->At(i)->GetName();

            std::vector<TRegexp> commanVarToAvoid = {
                "Flag",
                "HLT",
                "Weight",
                "weight",
                "event",
                "PV_npvs",
                "toptagger",
                "muons",
                "elesMVA",
                "leptonsMVAT_2OS",
                "leptonsMVAT_2SS",
                "leptonsMVAT_number",
                "bjets._3",
                "bjets._4",
                // "bjetsM_number",
                "nonbjetsM_4",
                "tausT_number",
                "gen",
                "tausL",
                "tausF",
                // "jets_4largestBscoreMulti",
                // "jets_bScoreMultiply",
            };
            if (vectorInBranch(branchName, commanVarToAvoid))
                continue;

            if (channel.CompareTo("1tau1l") == 0)
            {
                if (branchName.Contains("tausT_leptonsT_transMass") || branchName.Contains("jets_spherilty") || branchName.Contains("tausF_leptonsT_chargeSum") || branchName.Contains("tausT_3") || branchName.Contains("tausT_2") || branchName.Contains("leptonsMVAT_2") || branchName.Contains("leptonsMVAT_3") || branchName.Contains("tausT_minDeltaR") || branchName.Contains("jets_aplanarity"))
                    continue; //???

                //???might miss some combination channels???
                if (branchName.Contains("jets_9") || branchName.Contains("jets_10") || branchName.Contains("jets_11"))
                    continue; //>=7 jets
            }
            else if (channel.CompareTo("1tau2l") == 0)
            {
                std::vector<TRegexp> tauVariablesToAvoid = {"taus._MHT", "taus._HT", "taus._invariantMass", "taus._minDeltaR", "tau._2", "tau._3"};
                if (vectorInBranch(branchName, tauVariablesToAvoid))
                    continue;

                std::vector<TRegexp> leptonVarToAvoid = {"leptonsMVAT_2OS", "leptonsMVAT_3"};
                if (vectorInBranch(branchName, leptonVarToAvoid))
                    continue;

                std::vector<TRegexp> jetsVarToAvoid = {"jets_7", "jets_8", "jets_9", "jets_10", "jets_11"};
                if (vectorInBranch(branchName, jetsVarToAvoid))
                    continue;

                std::vector<TRegexp> mismodeled = {"phi", "eta", "minDeltaR"};
                if (vectorInBranch(branchName, mismodeled))
                    continue;
            }

            // probematic branches

            chosenVariable = chosenVariable + 1;
            cout << "variables forvaribles training: " << branchName << endl;
            branchNames.push_back(branchName);
            if (branchName.Contains("num") || branchName.Contains("number") || branchName.Contains("charge"))
            {
                dataloader->AddVariable(branchName, 'I');
            }
            else
            {
                dataloader->AddVariable(branchName, 'F');
                // Note that ’F’ indicates any floating point type, i.e., float and double
                // In addition, two more arguments may be inserted into the AddVariable call, allowing the user to specify titles and units for the input variables for displaying purposes
            }
        }
        std::cout << "chosenVariable: " << chosenVariable << "\n";
    }

    // You can add so-called "Spectator variables", which are not used in the MVA training,
    // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
    // input variables, the response values of all trained MVAs, and the spectator variables
    // dataloader->AddSpectator( "spec1 := var1*2",  "Spectator 1", "units", 'F' );
    // dataloader->AddSpectator( "spec2 := var1*3",  "Spectator 2", "units", 'F' );

    // global event weights per tree (see below for setting event-wise weights)
    // You can add an arbitrary number of signal or background trees
    // dataloader->AddSignalTree      ( TTTT.getEventTree() , LUMI* TTTT.getScale() );
    dataloader->AddSignalTree(TTTT.getEventTree(), lumiMap["2018"] * TTTT.getScale());
    dataloader->AddSignalTree(allProcesses2016[0].getEventTree(), lumiMap["2016"] * allProcesses2016[0].getScale());
    dataloader->AddSignalTree(allProcesses2017[0].getEventTree(), lumiMap["2017"] * allProcesses2017[0].getScale());
    for (UInt_t p = 1; p < allProcesses.size(); p++)
    {
        if (allProcesses[p].getEventTree()->GetEntries() == 0)
        {
            std::cout << "empty process: " << allProcesses[p].getProcessName() << "\n";
            continue;
        }
        std::cout << "adding background for training: " << allProcesses[p].getProcessName() << "\n";
        dataloader->AddBackgroundTree(allProcesses[p].getEventTree(), lumiMap["2018"] * allProcesses[p].getScale());
    }
    for (UInt_t p = 1; p < allProcesses2016.size(); p++)
    {
        if (allProcesses2016[p].getEventTree()->GetEntries() == 0)
        {
            std::cout << "empty process: " << allProcesses2016[p].getProcessName() << "\n";
            continue;
        }
        std::cout << "adding background for training: " << allProcesses2016[p].getProcessName() << "\n";
        dataloader->AddBackgroundTree(allProcesses2016[p].getEventTree(), lumiMap["2016"] * allProcesses2016[p].getScale());
    }
    for (UInt_t p = 1; p < allProcesses2017.size(); p++)
    {
        if (allProcesses2017[p].getEventTree()->GetEntries() == 0)
        {
            std::cout << "empty process: " << allProcesses2017[p].getProcessName() << "\n";
            continue;
        }
        std::cout << "adding background for training: " << allProcesses2017[p].getProcessName() << "\n";
        dataloader->AddBackgroundTree(allProcesses2017[p].getEventTree(), lumiMap["2017"] * allProcesses2017[p].getScale());
    }
    // Set individual event weights (the variables must exist in the original TTree)
    // -  for background: `dataloader->SetBackgroundWeightExpression("weight1*weight2");`
    // const TCut weight = "EVENT_genWeight*EVENT_prefireWeight*PUWeight";
    // dataloader->SetSignalWeightExpression("EVENT_genWeight*EVENT_prefireWeight*PUweight_");
    // dataloader->SetBackgroundWeightExpression("EVENT_genWeight*EVENT_prefireWeight*PUweight_");
    dataloader->SetSignalWeightExpression("EVENT_prefireWeight*EVENT_genWeight*PUweight_*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight");
    dataloader->SetBackgroundWeightExpression("EVENT_prefireWeight*EVENT_genWeight*PUweight_*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight");

    // Tell the dataloader how to use the training and testing events. If no numbers of events are given, half of the events in the tree are used
    // for training, and the other half for testing:
    char trainingSetup[100];
    //???tuning here too
    sprintf(trainingSetup, "nTrain_Signal=%f:nTrain_Background=%f:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=EqualNumEvents:!V", allSignal * 0.6, allBg * 0.6);
    if (istest)
    {
        dataloader->PrepareTrainingAndTestTree(
            // cutForSandB, cutForSandB,
            "", "",
            "nTrain_Signal=1000:nTrain_Background=1000:nTest_Signal=1000:nTest_Background=1000:SplitMode=Random:NormMode=NumEvents:!V");
        // "nTrain_Signal=0:nTrain_Background=0:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );
    }
    else
    {
        // dataloader->PrepareTrainingAndTestTree(cutForSandB, cutForSandB, trainingSetup); // 60% goes to training, 1tau1l
        dataloader->PrepareTrainingAndTestTree("", "", trainingSetup); // 60% goes to training, 1tau1l
                                                                       // means raw entries
                                                                       // dataloader->PrepareTrainingAndTestTree( cutForSandB, cutForSandB, trainingSetup );
    }
    // In case the user has provided a ROOT tree, the event copy can (and should) be accelerated by disabling all branches not used by the input variables
    //??? Note that the preselection cuts are applied before the training and test samples are created, i.e., the tree sizes apply to numbers of selected events

    // ### Book MVA methods
    //
    // Please lookup the various method configuration options in the corresponding cxx files, eg:
    // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
    // it is possible to preset ranges in the option string in which the cut optimisation should be done:
    // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

    // Cut optimisation
    if (Use["Cuts"])
        factory->BookMethod(dataloader, TMVA::Types::kCuts, "Cuts",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");

    if (Use["CutsD"])
        factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsD",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate");

    if (Use["CutsPCA"])
        factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsPCA",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA");

    if (Use["CutsGA"])
        factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsGA",
                            "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95");

    if (Use["CutsSA"])
        factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsSA",
                            "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale");

    // Likelihood ("naive Bayes estimator")
    if (Use["Likelihood"])
        factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "Likelihood",
                            "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50");

    // Decorrelated likelihood
    if (Use["LikelihoodD"])
        factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
                            "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate");

    // PCA-transformed likelihood
    if (Use["LikelihoodPCA"])
        factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                            "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA");

    // Use a kernel density estimator to approximate the PDFs
    if (Use["LikelihoodKDE"])
        factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                            "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50");

    // Use a variable-dependent mix of splines and kernel density estimator
    if (Use["LikelihoodMIX"])
        factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                            "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50");

    // Test the multi-dimensional probability density estimator
    // here are the options strings for the MinMax and RMS methods, respectively:
    //
    //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
    //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
    if (Use["PDERS"])
        factory->BookMethod(dataloader, TMVA::Types::kPDERS, "PDERS",
                            "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600");

    if (Use["PDERSD"])
        factory->BookMethod(dataloader, TMVA::Types::kPDERS, "PDERSD",
                            "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate");

    if (Use["PDERSPCA"])
        factory->BookMethod(dataloader, TMVA::Types::kPDERS, "PDERSPCA",
                            "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA");

    // Multi-dimensional likelihood estimator using self-adapting phase-space binning
    if (Use["PDEFoam"])
        factory->BookMethod(dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
                            "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T");

    if (Use["PDEFoamBoost"])
        factory->BookMethod(dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
                            "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T");

    // K-Nearest Neighbour classifier (KNN)
    if (Use["KNN"])
        factory->BookMethod(dataloader, TMVA::Types::kKNN, "KNN",
                            "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim");

    // H-Matrix (chi2-squared) method
    if (Use["HMatrix"])
        factory->BookMethod(dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None");

    // Linear discriminant (same as Fisher discriminant)
    if (Use["LD"])
        factory->BookMethod(dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10");

    // Fisher discriminant (same as LD)
    if (Use["Fisher"])
        factory->BookMethod(dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10");

    // Fisher with Gauss-transformed input variables
    if (Use["FisherG"])
        factory->BookMethod(dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss");

    // Composite classifier: ensemble (tree) of boosted Fisher classifiers
    if (Use["BoostedFisher"])
        factory->BookMethod(dataloader, TMVA::Types::kFisher, "BoostedFisher",
                            "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring");

    // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
    if (Use["FDA_MC"])
        factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_MC",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1");

    if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
        factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_GA",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=100:Cycles=2:Steps=5:Trim=True:SaveBestGen=1");

    if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
        factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_SA",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale");

    if (Use["FDA_MT"])
        factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_MT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch");

    if (Use["FDA_GAMT"])
        factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_GAMT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim");

    if (Use["FDA_MCMT"])
        factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_MCMT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20");

    // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
    if (Use["MLP"])
        factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator");

    if (Use["MLPBFGS"])
        factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator");

    if (Use["MLPBNN"])
        factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator"); // BFGS training with bayesian regulators

    // Multi-architecture DNN implementation.
    if (Use["DNN_CPU"] or Use["DNN_GPU"])
    {
        // General layout.
        TString layoutString("Layout=TANH|128,TANH|128,TANH|128,LINEAR");

        // Training strategies.
        TString training0("LearningRate=1e-1,Momentum=0.9,Repetitions=1,"
                          "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                          "WeightDecay=1e-4,Regularization=L2,"
                          "DropConfig=0.0+0.5+0.5+0.5, Multithreading=True");
        TString training1("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                          "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                          "WeightDecay=1e-4,Regularization=L2,"
                          "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
        TString training2("LearningRate=1e-3,Momentum=0.0,Repetitions=1,"
                          "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                          "WeightDecay=1e-4,Regularization=L2,"
                          "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
        TString trainingStrategyString("TrainingStrategy=");
        trainingStrategyString += training0 + "|" + training1 + "|" + training2;

        // General Options.
        TString dnnOptions("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
                           "WeightInitialization=XAVIERUNIFORM");
        dnnOptions.Append(":");
        dnnOptions.Append(layoutString);
        dnnOptions.Append(":");
        dnnOptions.Append(trainingStrategyString);

        // Cuda implementation.
        if (Use["DNN_GPU"])
        {
            TString gpuOptions = dnnOptions + ":Architecture=GPU";
            factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_GPU", gpuOptions);
        }
        // Multi-core CPU implementation.
        if (Use["DNN_CPU"])
        {
            TString cpuOptions = dnnOptions + ":Architecture=CPU";
            factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_CPU", cpuOptions);
        }
    }

    // CF(Clermont-Ferrand)ANN
    if (Use["CFMlpANN"])
        factory->BookMethod(dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"); // n_cycles:#nodes:#nodes:...

    // Tmlp(Root)ANN
    if (Use["TMlpANN"])
        factory->BookMethod(dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"); // n_cycles:#nodes:#nodes:...

    // Support Vector Machine
    if (Use["SVM"])
        factory->BookMethod(dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm");

    // Boosted Decision Trees
    if (Use["BDTG"]) // Gradient Boost
        factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTG",
                            "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2");

    if (Use["BDT"]) // Adaptive Boost
                    //???hyperparameter optimization here
        factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
                            // "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
                            "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30");
    // "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=40" );
    // "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining" );
    //???IgnoreNegWeightsInTraining=False, default

    if (Use["BDTB"]) // Bagging
        factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTB",
                            "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20");

    if (Use["BDTD"]) // Decorrelation + Adaptive Boost
        factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTD",
                            "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate");

    if (Use["BDTF"]) // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
        factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTF",
                            "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20");

    // RuleFit -- TMVA implementation of Friedman's method
    if (Use["RuleFit"])
        factory->BookMethod(dataloader, TMVA::Types::kRuleFit, "RuleFit",
                            "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02");

    // For an example of the category classifier usage, see: TMVAClassificationCategory
    //
    // --------------------------------------------------------------------------------------------------
    //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
    // STILL EXPERIMENTAL and only implemented for BDT's !
    //
    //     factory->OptimizeAllMethods("SigEffAt001","Scan");
    //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
    //
    // --------------------------------------------------------------------------------------------------

    // Now you can tell the factory to train, test, and evaluate the MVAs
    //
    // Train MVAs using the set of training events
    factory->TrainAllMethods();

    // Evaluate all MVAs using the set of test events
    factory->TestAllMethods();

    // Evaluate and compare performance of all configured MVAs
    factory->EvaluateAllMethods();

    // --------------------------------------------------------------

    // Save the output
    outputFile->Close();
    std::cout << "input dir: " << baseDir << endl;
    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "==> TMVAClassification is done!" << std::endl;

    delete factory;
    delete dataloader;
    // Launch the GUI for the root macros
    if (!gROOT->IsBatch())
        TMVA::TMVAGui(outfileName);

    return 0;
}

int main(int argc, char **argv)
{
    // Select methods (don't look at this code - not of interest)
    TString methodList;
    for (int i = 1; i < argc; i++)
    {
        TString regMethod(argv[i]);
        if (regMethod == "-b" || regMethod == "--batch")
            continue;
        if (!methodList.IsNull())
            methodList += TString(",");
        methodList += regMethod;
    }
    return TMVAClassification_variableFileInput(methodList);
}
