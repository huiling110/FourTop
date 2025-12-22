/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2023-06-06 21:01:27
 * @modify date 2023-06-06 21:01:27
 * @desc [description]
 */
#include <iostream>

#include "../include/treeAnalyzer.h"
#include "../include/inputFileMap.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/commenSelectionAndWeight.h"
#include "../include/AnalysisLogger.h"

void treeAnalyzer::Init()
{
    LOG_INFO << "Starting initialization for channel: " << m_channel << ", isRun3: " << m_isRun3;
    cutFlowHist->SetDirectory(m_outFile);

    std::vector<TString> sysRegions;
    sysRegions.clear();

    TString variableList; 
    TString weightfile;
    if(m_channel=="1tau1l"){
        std::cout << "initializing for 1tau1l\n";

        WH::getChannelSys(sysRegions, "1tau1lSR", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau1lCR12", m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);

        // v0 BDT binning (original, without TTBB training)
        std::vector<Double_t> bins1tau1l = {-0.25, -0.067, -0.024, 0.018, 0.06, 0.1, 0.145, 0.36};
        SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, bins1tau1l, sysRegions);
        // SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 100, -0.25, 0.36, sysRegions);//!For optimization binnning

        if(!(m_isData || m_isFakeLepton || m_isFakeTau) && m_ifMCFakeTau){
            SR1tau1lSys_MCFT = histForRegionsBase("BDT", "BDT score", m_processName+"_MCFT", bins1tau1l, sysRegions);
            SR1tau1lSys_NotMCFT = histForRegionsBase("BDT", "BDT score", m_processName+"_NotMCFT", bins1tau1l, sysRegions);
        }

        // Use original v0 BDT (without TTBB training)
        variableList = WH::BDTTrainingMap.at(m_era).at(0);
        weightfile = WH::BDTTrainingMap.at(m_era).at(1);

        std::cout << "training input: " << weightfile << "\n";
    }else if(m_channel=="1tau0l"){
        std::cout << "1tau0l \n";
        WH::getChannelSys(sysRegions, "1tau0lSR",  m_era, m_isFakeTau,  m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau0lVR",  m_era, m_isFakeTau,  m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau0lCRMR",  m_era, m_isFakeTau,  m_isFakeLepton, m_processName, m_ifSys);

        std::vector<Double_t> bins1tau0l = {-0.35, -0.16, -0.12, -0.105, -0.084, -0.063, -0.042, -0.021, 0.0, 0.021, 0.049, 0.091, 0.35} ; //Bin C, optimized,
        SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, bins1tau0l, sysRegions);//1tau0l
        // SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 100, -0.35, 0.35, sysRegions);//!For optimization binnning
        // Use original v0 BDT (without TTBB training)
        variableList = WH::BDT1tau0l.at(m_era).at(0);
        weightfile = WH::BDT1tau0l.at(m_era).at(1); 

    }else if(m_channel=="1tau2l"){
        std::cout<<"1tau2l\n";
        WH::getChannelSys(sysRegions, "1tau2lSR",  m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);
        WH::getChannelSys(sysRegions, "1tau2lCR3",  m_era, m_isFakeTau, m_isFakeLepton, m_processName, m_ifSys);

        std::vector<Double_t> bins1tau2l = { -0.25,  -0.15, -0.12, -0.093, -0.068, -0.042, -0.009, 0.04, 0.12, 0.4 }; //BinC
        SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, bins1tau2l, sysRegions);//1tau2l

        if(!(m_isData || m_isFakeLepton || m_isFakeTau) && m_ifMCFakeTau){
            SR1tau1lSys_MCFT = histForRegionsBase("BDT", "BDT score", m_processName+"_MCFT", bins1tau2l, sysRegions);
            SR1tau1lSys_NotMCFT = histForRegionsBase("BDT", "BDT score", m_processName+"_NotMCFT", bins1tau2l, sysRegions);
        }


        // variableList = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l.csv";
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau2l_v76For1tau2l/mc/BDTTrain/v0/dataset/weight/TMVAClassification_BDT.weights.xml";
        variableList = "/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l_final.csv";
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau2lSR_v84Pre1tau2lLepF2/mc/BDTTrain/v1finalVar/inputList_1tau2l_final.csv/dataset/weight/TMVAClassification_BDT.weights.xml";
        weightfile = "/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l_final/dataset/weight/TMVAClassification_BDT.weights.xml";
    }else{
        std::cout << "WARNING!! channel not spefified\n";
    }
    std::cout<<"weightfile="<<weightfile<<"\n";

    WH::readVariableList(variableList, variablesName, variablesForReader, varForReaderMap, variablesOriginAll);
    std::cout << "out of function\n";
    if (variablesName.size() == variablesForReader.size())
    {
        std::cout<<"variablesName.size(): "<<variablesName.size()<<"\n";

        for (UInt_t i = 0; i < variablesName.size(); i++)
        {
            reader->AddVariable(variablesName[i], &varForReaderMap[variablesName[i]]);
            // std::cout<<"reader add variable: "<<variablesName[i]<<"\n";
        }
    }
    else
    {
        std::cout << "BAD!!! variableName vector not same size of varForReaderMap\n ";
    }
    // for map, the variables will be reordered according to their keys, not safe to add with map

    std::cout<<"after adding reader\n";
    TString methodName = "BDT" + TString(" method");
    reader->BookMVA(methodName, weightfile);
    std::cout<<"booked MVA\n";

    SR1tau1lSys.setDir(m_outFile);

    if(m_isFakeLepton || m_isFakeTau || m_isData){
        m_scaleRe_normUp_SF = 1;
        m_scaleRe_normDown_SF = 1;
        m_scaleFa_normUp_SF = 1;
        m_scaleFa_normDown_SF = 1;
        m_pdfAlphaS_normUp_SF = 1;
        m_pdfAlphaS_normDown_SF = 1;
    }else{
        // Use TFile* overloads to avoid ROOT file caching issues
        m_scaleRe_normUp_SF = WH::calQCDScaleNor(m_file.get(), 7);
        m_scaleRe_normDown_SF = WH::calQCDScaleNor(m_file.get(), 1);
        m_scaleFa_normUp_SF = WH::calQCDScaleNor(m_file.get(), 5);
        m_scaleFa_normDown_SF = WH::calQCDScaleNor(m_file.get(), 3);
        m_pdfAlphaS_normUp_SF = WH::calPDFScaleNor(m_file.get(), 0);//!inf big for singleTop process
        m_pdfAlphaS_normDown_SF = WH::calPDFScaleNor(m_file.get(), 1);
        m_pdf_normUp_SF = WH::calPDFScaleNor(m_file.get(), 2);
        m_pdf_normDown_SF = WH::calPDFScaleNor(m_file.get(), 3);
        m_PSWeightISR_normUp_SF = WH::calPDFScaleNor(m_file.get(), 4);
        m_PSWeightISR_normDown_SF = WH::calPDFScaleNor(m_file.get(), 5);
        m_PSWeightFSR_normUp_SF = WH::calPDFScaleNor(m_file.get(), 6);
        m_PSWeightFSR_normDown_SF = WH::calPDFScaleNor(m_file.get(), 7);
    }
    std::cout<<"m_scaleRe_normDown_SF="<<m_scaleRe_normDown_SF<<"\n";
    std::cout<<"m_scaleRe_normUp_SF="<<m_scaleRe_normUp_SF<<"\n";
    std::cout<<"m_scaleFa_normDown_SF="<<m_scaleFa_normDown_SF<<"\n";
    std::cout<<"m_scaleFa_normUp_SF="<<m_scaleFa_normUp_SF<<"\n";
    std::cout<<"m_pdfAlphaS_normUp_SF="<<m_pdfAlphaS_normUp_SF<<"\n";//!could be inf for some samples for example st_tZq
    std::cout<<"m_pdfAlphaS_normDown_SF="<<m_pdfAlphaS_normDown_SF<<"\n";
    std::cout<<"m_pdf_normUp_SF="<<m_pdf_normUp_SF<<"\n";
    std::cout<<"m_pdf_normDown_SF="<<m_pdf_normDown_SF<<"\n";
    std::cout<<"m_PSWeightISR_normUp_SF="<<m_PSWeightISR_normUp_SF<<" m_PSWeightISR_normDown_SF="<<m_PSWeightISR_normDown_SF<<"\n";
    std::cout<<"m_PSWeightFSR_normUp_SF="<<m_PSWeightFSR_normUp_SF<<" m_PSWeightFSR_normDown_SF="<<m_PSWeightFSR_normDown_SF<<"\n";

    std::cout << "done initializing\n";
    std::cout << "\n";
}

void treeAnalyzer::LoopTree()
{
    std::cout << "start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 10000;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);
        cutFlowHist->Fill(0);

        if (!(baselineSelection(e.get(), m_isRun3, (m_channel=="1tau2l"))))
        {
            continue;
        }
        cutFlowHist->Fill(1);
        cutFlowHist->Fill(2);
        // convert branch value to float for reader
        for (auto it = varForReaderMap.begin(); it != varForReaderMap.end(); ++it)
        {
            Float_t ivar;
            // std::cout<<"ivar: "<<it->first<<"\n";
            std::variant<Int_t, Double_t, Bool_t> branch = e->getByName(it->first);
            if (std::holds_alternative<Int_t>(branch))
            {
                ivar = static_cast<Float_t>(std::get<Int_t>(branch));
            }
            else if (std::holds_alternative<Double_t>(branch))
            {
                ivar = static_cast<Float_t>(std::get<Double_t>(branch));
            }
            varForReaderMap[it->first] = ivar;
        }

        Double_t bdtScore = reader->EvaluateMVA("BDT method");



        Double_t basicWeight = baseWeightCal(e.get(), i, m_isRun3, m_isData, WH::channelMap.at(m_channel), m_isFakeTau, m_isFakeLepton);
        // Check for invalid weights (NaN or Inf can occur in fake rate calculations)
        if (std::isnan(basicWeight) || std::isinf(basicWeight)){
            LOG_WARNING << "Invalid weight (" << basicWeight << ") at event " << i << " - skipping";
            continue;
        }
        //!!!testing 
        if(m_isFakeTau){
            if(e->jets_num.v()<4){
                basicWeight*= 1.2;
            }
        }

        Bool_t isMCFT = e->tausT_1genFlavour.v() == 0;

        if(m_channel=="1tau0l"){
            Bool_t SR1tau0l = SR1tau1lSel(e.get(), 1, m_isRun3, m_isFakeTau);
            Bool_t CR1tau0l = SR1tau1lSel(e.get(), 9, m_isRun3, m_isFakeTau);
            Bool_t MR1tau0l = SR1tau1lSel(e.get(), 7, m_isRun3, m_isFakeTau);
            Bool_t VR1tau0l = SR1tau1lSel(e.get(), 8, m_isRun3, m_isFakeTau);
            sysRegionsFill(bdtScore, basicWeight, SR1tau0l, "1tau0lSR", SR1tau1lSys);
            sysRegionsFill(bdtScore, basicWeight, VR1tau0l, "1tau0lVR", SR1tau1lSys);
            sysRegionsFill(bdtScore, basicWeight, CR1tau0l||MR1tau0l, "1tau0lCRMR", SR1tau1lSys);
        }else if(m_channel=="1tau1l"){
            Bool_t SR1tau1l = SR1tau1lSel(e.get(), WH::channelMap.at(m_channel), m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t CR11tau1l = SR1tau1lSel(e.get(), 5, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t CR21tau1l = SR1tau1lSel(e.get(), 4, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            sysRegionsFill(bdtScore, basicWeight, SR1tau1l, "1tau1lSR", SR1tau1lSys);
            sysRegionsFill(bdtScore, basicWeight, CR11tau1l||CR21tau1l, "1tau1lCR12", SR1tau1lSys);

            //m_isMCFake
            //for combine, both MCFTau and NotMCFTau need the shape uncertaity
            if(!(m_isFakeLepton || m_isFakeTau||m_isData)){
                sysRegionsFill(bdtScore, basicWeight, SR1tau1l&&isMCFT, "1tau1lSR", SR1tau1lSys_MCFT);
                sysRegionsFill(bdtScore, basicWeight, SR1tau1l&&!isMCFT, "1tau1lSR", SR1tau1lSys_NotMCFT);
                sysRegionsFill(bdtScore, basicWeight,  (CR11tau1l||CR21tau1l)&&isMCFT, "1tau1lCR12", SR1tau1lSys_MCFT);
                sysRegionsFill(bdtScore, basicWeight,  (CR11tau1l||CR21tau1l)&&!isMCFT, "1tau1lCR12", SR1tau1lSys_NotMCFT);
            }



        }else if (m_channel=="1tau2l"){
            Bool_t SR1tau2l = SR1tau1lSel(e.get(), 2, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t CR31tau2l = SR1tau1lSel(e.get(), 12, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            sysRegionsFill(bdtScore, basicWeight, SR1tau2l, "1tau2lSR", SR1tau1lSys);
            sysRegionsFill(bdtScore, basicWeight, CR31tau2l, "1tau2lCR3", SR1tau1lSys);

            if(!(m_isFakeLepton || m_isFakeTau||m_isData)){
                sysRegionsFill(bdtScore, basicWeight, SR1tau2l&&isMCFT, "1tau2lSR", SR1tau1lSys_MCFT);
                sysRegionsFill(bdtScore, basicWeight, SR1tau2l&&!isMCFT, "1tau2lSR", SR1tau1lSys_NotMCFT);
                sysRegionsFill(bdtScore, basicWeight, CR31tau2l&&isMCFT, "1tau2lCR3", SR1tau1lSys_MCFT);
                sysRegionsFill(bdtScore, basicWeight, CR31tau2l&&!isMCFT, "1tau2lCR3", SR1tau1lSys_NotMCFT);
            }
        }

    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};


//!!!put it into functions
void treeAnalyzer::sysRegionsFill(Double_t bdtScore, Double_t basicWeight, Bool_t SR1tau1l, TString region, histForRegionsBase &SR1tau1lSysF)
{
    // Fill nominal histogram
    SR1tau1lSysF.fillHistVec(region, bdtScore, basicWeight, SR1tau1l, m_isData);

    if(!m_ifSys){
        return;  // Skip systematics if not requested
    }

    // MC samples (not fake lepton/tau or data) get detector systematics
    if(!(m_isFakeLepton || m_isFakeTau || m_isData)){
        // Apply all detector systematics via SystematicManager
        m_systematicManager->fillSystematics(region, bdtScore, basicWeight, SR1tau1l, e.get(), SR1tau1lSysF, m_isData);

        // Theory systematics (require normalization factors)
        m_systematicManager->fillTheorySystematics(
            region, bdtScore, basicWeight, SR1tau1l, e.get(), SR1tau1lSysF, m_isData,
            m_scaleRe_normUp_SF, m_scaleRe_normDown_SF,
            m_scaleFa_normUp_SF, m_scaleFa_normDown_SF,
            m_pdfAlphaS_normUp_SF, m_pdfAlphaS_normDown_SF,
            m_pdf_normUp_SF, m_pdf_normDown_SF,
            m_PSWeightISR_normUp_SF, m_PSWeightISR_normDown_SF,
            m_PSWeightFSR_normUp_SF, m_PSWeightFSR_normDown_SF
        );

        // MC fake tau systematic (pt-dependent)
        m_systematicManager->fillMCFakeTauSystematic(region, bdtScore, basicWeight, SR1tau1l, e.get(), SR1tau1lSysF, m_isData);
    }
    else if(m_isFakeTau){
        // Data-driven fake tau systematic
        m_systematicManager->fillDataDrivenFakeTauSystematic(region, bdtScore, e.get(), SR1tau1lSysF, SR1tau1l, m_isData);
    }
}


void treeAnalyzer::Terminate()
{
    std::cout << "Termintate: ..........................................\n";

    if(!(m_isFakeTau || m_isFakeLepton || m_isData)){
            // Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
            Double_t genWeightSum = TTTT::getGenSum(m_file.get());
            const Double_t processScale = ((TTTT::lumiMap.at(m_era)* TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
            SR1tau1lSys.scale(processScale);
            std::cout<<"processScale: "<<processScale<<"\n";
        if(m_ifMCFakeTau){
            SR1tau1lSys_MCFT.scale(processScale);
            SR1tau1lSys_NotMCFT.scale(processScale);
        }
    }
    SR1tau1lSys.print();

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}



treeAnalyzer::~treeAnalyzer()
{
    // Smart pointers automatically clean up
    // m_file will be automatically closed
    // m_outFile is owned by ROOT and will be handled by ROOT's cleanup
}  