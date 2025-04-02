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

void treeAnalyzer::Init()
{
    std::cout << "Start to initilation....................................................\n";
    std::cout << "m_channel: " << m_channel << "; m_isRun3: " << m_isRun3 << "\n";
    cutFlowHist->SetDirectory(m_outFile);

    std::vector<TString> sysRegions;
    sysRegions.clear();

    TString variableList; 
    TString weightfile;
    if(m_channel=="1tau1l"){
        std::cout << "initializing for 1tau1l\n";

        WH::getChannelSys(sysRegions, "1tau1lSR", m_era);
        WH::getChannelSys(sysRegions, "1tau1lCR1", m_era);
        WH::getChannelSys(sysRegions, "1tau1lCR2", m_era);
        WH::getChannelSys(sysRegions, "1tau1lCR12", m_era);

        // std::vector<Double_t> bins1tau1l =  {-0.25, -0.1036, -0.0731, -0.0487, -0.030, -0.012, 0.013, 0.037, 0.06, 0.122, 0.36}; //roughly 15 bg in each bin
        // std::vector<Double_t> bins1tau1l = {-0.25, -0.0914, -0.0548, -0.0243, 0.0062, 0.0367, 0.0855, 0.135, 0.36}; //roughly 22 bg in each bin
        // std::vector<Double_t> bins1tau1l = {-0.25, -0.067, -0.024, 0.018, 0.06, 0.14, 0.36 }; //BinF; roughly 30 bg in each bin
        std::vector<Double_t> bins1tau1l = {-0.25, -0.067, -0.024, 0.018, 0.06, 0.1 ,0.145, 0.36 }; //BinF; roughly 30 bg in each bin
        SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, bins1tau1l, sysRegions); 
        // SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 100, -0.25, 0.36, sysRegions);//!For optimization binnning

        // variableList = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l.csv"; 
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/BDTTrain/v0/dataset/weight/TMVAClassification_BDT.weights.xml";
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLSample/mc/BDTTrain/v0allVar/dataset/weight/TMVAClassification_BDT.weights.xml";//!weight file for VLL in 1tau1l
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLAllMass/mc/BDTTrain/v1VLLM800/dataset/weight/TMVAClassification_BDT.weights.xml";//!VLL 800
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLAllMass/mc/BDTTrain/v1VLLM700/dataset/weight/TMVAClassification_BDT.weights.xml";//!VLL700
        variableList = "/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l_final.csv";
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v80addTTExtra1/mc/BDTTrain/v1finalVar27/inputList_1tau1l_final.csv/dataset/weight/TMVAClassification_BDT.weights.xml";
        // weightfile = "./input/BDTTraining_1tau1l_27Var/TMVAClassification_BDT.weights.xml";
        weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v84HadroPresel/mc/BDTTrain/v1finalVar27/inputList_1tau1l_final.csv/dataset/weight/TMVAClassification_BDT.weights.xml";
        std::cout << "training input: " << weightfile << "\n";
    }else if(m_channel=="1tau0l"){
        std::cout << "1tau0l \n";
        WH::getChannelSys(sysRegions, "1tau0lSR", m_era);
        WH::getChannelSys(sysRegions, "1tau0lCR", m_era);
        WH::getChannelSys(sysRegions, "1tau0lMR", m_era);
        WH::getChannelSys(sysRegions, "1tau0lVR", m_era);
        WH::getChannelSys(sysRegions, "1tau0lCRMR", m_era);

        // std::vector<Double_t> bins1tau0l = {-0.35, -0.25, -0.23, -0.21, -0.19, -0.17, -0.15, -0.13, -0.11, -0.09, -0.07, -0.05, -0.03, -0.01, 0.01, 0.03, 0.05, 0.07, 0.09, 0.11,  0.15,  0.19,  0.23,  0.35};
        // std::vector<Double_t> bins1tau0l = {-0.35, -0.25, -0.23, -0.21, -0.19, -0.17, -0.15, -0.13, -0.11, -0.09, -0.07, -0.05, -0.03, -0.01, 0.01, 0.03, 0.05, 0.07, 0.09, 0.11,  0.13,  0.18,  0.35};
        // std::vector<Double_t> bins1tau0l = {-0.35, -0.28, -0.25, -0.23, -0.21, -0.19, -0.17, -0.15, -0.13, -0.11, -0.09, -0.07, -0.05, -0.03, -0.01, 0.01, 0.03, 0.05, 0.07, 0.09, 0.11,  0.13,  0.18,  0.35};//Bin B
        std::vector<Double_t> bins1tau0l = {-0.35, -0.16, -0.12, -0.105, -0.084, -0.063, -0.042, -0.021, 0.0, 0.021, 0.049, 0.091, 0.35} ; //Bin C, optimized,
        SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, bins1tau0l, sysRegions);//1tau0l 
        // SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 100, -0.35, 0.35, sysRegions);//!For optimization binnning
        // variableList = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l.csv";
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau0l_v75OverlapRemovalFTau/mc/BDTTrain/v0/dataset/weight/TMVAClassification_BDT.weights.xml";
        variableList = WH::BDT1tau0l.at(m_era).at(0);
        weightfile = WH::BDT1tau0l.at(m_era).at(1); 

        // variableList = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l.csv";
        // weightfile = "/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2018/v0baselineHardro_1tau0l_BDTSR_v86HadroPreSelWithGammaRemoval/mc/BDTTrain/VLLm600_ABDT_1tau0l/inputList_1tau0l.csv/dataset/weight/TMVAClassification_BDT.weights.xml";
        // variableList = WH::BDT1tau0l.at(m_era).at(0);
        // weightfile = WH::BDT1tau0l.at(m_era).at(1);

    }else if(m_channel=="1tau2l"){
        std::cout<<"1tau2l\n";
        WH::getChannelSys(sysRegions, "1tau2lSR", m_era);
        WH::getChannelSys(sysRegions, "1tau2lCR3", m_era);

        // SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 3, -0.3, 0.4, sysRegions);//1tau2l
        // SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 100, -0.25, 0.4, sysRegions);//!For optimization binnning
        // std::vector<Double_t> bins1tau2l = {-0.25, -0.094, -0.068, -0.049, -0.035, -0.022, -0.003, 0.01, 0.03, 0.05, 0.07, 0.11, 0.4 }; //binA
        // std::vector<Double_t> bins1tau2l = {-0.25, -0.094, -0.068, -0.049, -0.035, -0.022, -0.003, 0.01, 0.03, 0.05, 0.07, 0.11, 0.15, 0.4 }; //binA
        // std::vector<Double_t> bins1tau2l = {-0.25, -0.068, -0.049,  -0.022,  0.01,  0.05,  0.11, 0.15, 0.4 }; //binA
        // std::vector<Double_t> bins1tau2l = {-0.25, -0.068, -0.049,  -0.022,  0.01,  0.05,  0.11, 0.155, 0.4 }; //binB
        std::vector<Double_t> bins1tau2l = { -0.25,  -0.15, -0.12, -0.093, -0.068, -0.042, -0.009, 0.04, 0.12, 0.4 }; //BinC
        SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, bins1tau2l, sysRegions);//1tau2l
        // variableList = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l.csv";
        // weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau2l_v76For1tau2l/mc/BDTTrain/v0/dataset/weight/TMVAClassification_BDT.weights.xml";
        variableList = "/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l_final.csv";
        weightfile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau2lSR_v84Pre1tau2lLepF2/mc/BDTTrain/v1finalVar/inputList_1tau2l_final.csv/dataset/weight/TMVAClassification_BDT.weights.xml";
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
        m_scaleRe_normUp_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 7);
        m_scaleRe_normDown_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 1);
        m_scaleFa_normUp_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 5);
        m_scaleFa_normDown_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 3);
        m_pdfAlphaS_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 0);//!inf big for singleTop process
        m_pdfAlphaS_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 1);
        m_pdf_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 2);
        m_pdf_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 3);
        m_PSWeightISR_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 4);
        m_PSWeightISR_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 5);
        m_PSWeightFSR_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 6);
        m_PSWeightFSR_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 7);
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

        if (!(baselineSelection(e, m_isRun3, (m_channel=="1tau2l"))))
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



        Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData, WH::channelMap.at(m_channel), m_isFakeTau, m_isFakeLepton);
        //!!!Some FR_weight_final == inf for fakeTau_MC, temporary fix here
        if (std::isnan(basicWeight)|| std::isinf(basicWeight)){
            std::cout<<"!!!! FR_weight_final is NAN\n";
            continue;
        }
        //!!!testing 
        if(m_isFakeTau){
            if(e->jets_num.v()<4){
                basicWeight*= 1.2;
            }
        }


        if(m_channel=="1tau0l"){
            Bool_t SR1tau0l = SR1tau1lSel(e, 1, m_isRun3, m_isFakeTau);
            Bool_t CR1tau0l = SR1tau1lSel(e, 9, m_isRun3, m_isFakeTau);
            Bool_t MR1tau0l = SR1tau1lSel(e, 7, m_isRun3, m_isFakeTau);
            Bool_t VR1tau0l = SR1tau1lSel(e, 8, m_isRun3, m_isFakeTau);
            sysRegionsFill(bdtScore, basicWeight, SR1tau0l, "1tau0lSR");
            sysRegionsFill(bdtScore, basicWeight, CR1tau0l, "1tau0lCR");
            sysRegionsFill(bdtScore, basicWeight, MR1tau0l, "1tau0lMR");
            sysRegionsFill(bdtScore, basicWeight, VR1tau0l, "1tau0lVR");
            sysRegionsFill(bdtScore, basicWeight, CR1tau0l||MR1tau0l, "1tau0lCRMR");
        }else if(m_channel=="1tau1l"){
            Bool_t SR1tau1l = SR1tau1lSel(e, WH::channelMap.at(m_channel), m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData);
            Bool_t CR11tau1l = SR1tau1lSel(e, 5, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData);
            Bool_t CR21tau1l = SR1tau1lSel(e, 4, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData);
            sysRegionsFill(bdtScore, basicWeight, SR1tau1l, "1tau1lSR");
            sysRegionsFill(bdtScore, basicWeight, CR11tau1l, "1tau1lCR1");
            sysRegionsFill(bdtScore, basicWeight, CR21tau1l, "1tau1lCR2");
            sysRegionsFill(bdtScore, basicWeight, CR11tau1l||CR21tau1l, "1tau1lCR12");
        }else if (m_channel=="1tau2l"){
            Bool_t SR1tau2l = SR1tau1lSel(e, 2, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            Bool_t CR31tau2l = SR1tau1lSel(e, 12, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
            sysRegionsFill(bdtScore, basicWeight, SR1tau2l, "1tau2lSR");
            sysRegionsFill(bdtScore, basicWeight, CR31tau2l, "1tau2lCR3");
        }

    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};


//!!!put it into functions
void treeAnalyzer::sysRegionsFill(Double_t bdtScore, Double_t basicWeight, Bool_t SR1tau1l, TString region){
//!correlated uncertainties are the same NP for 3 years, no need to add era in the name
    SR1tau1lSys.fillHistVec(region, bdtScore, basicWeight, SR1tau1l, m_isData);
    if(!(m_isFakeLepton || m_isFakeTau||m_isData)){

        SR1tau1lSys.fillHistVec(region + "_CMS_pileupUp", bdtScore, (basicWeight / e->PUweight_.v()) * e->PUweight_up_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_pileupDown", bdtScore, (basicWeight / e->PUweight_.v()) * e->PUweight_down_.v(), SR1tau1l, m_isData);

        SR1tau1lSys.fillHistVec(region + "_CMS_l1_ecal_prefiring_" + m_era +"Up", bdtScore, (basicWeight / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_l1_ecal_prefiring_" + m_era +"Down", bdtScore, (basicWeight / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_down.v(), SR1tau1l, m_isData);

        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsMu_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsMu_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsEle_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsEle_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm0_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm0_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm0_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm0_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm1_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm1_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm10_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm10_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm10_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm10_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm11_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm11_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat1_dm11_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat1_dm11_down.v(), SR1tau1l, m_isData);

        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm0_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm0_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm0_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm0_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm1_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm1_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm10_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm10_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm10_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm10_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm11_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm11_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_stat2_dm11_" + m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_stat2_dm11_down.v(), SR1tau1l, m_isData);

        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_allerasUp", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_alleras_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_allerasDown", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_alleras_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_"+m_era + "Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_"+m_era + "Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_down.v(), SR1tau1l, m_isData);

        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm0_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm0_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm0_"+ m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm0_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm1_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm1_"+ m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm10_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm10_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm10_"+ m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm10_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm11_" + m_era +"Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm11_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_t_vsJet_syst_dm11_"+ m_era +"Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_dm11_down.v(), SR1tau1l, m_isData);

        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_e_systUp", bdtScore, (basicWeight / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_sys_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_e_systDown", bdtScore, (basicWeight / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_sys_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_m_systUp", bdtScore, (basicWeight / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_sys_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_m_systDown", bdtScore, (basicWeight / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_sys_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_m_stat_" + m_era +"Up", bdtScore, (basicWeight / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_stat_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_m_stat_" + m_era +"Down", bdtScore, (basicWeight / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_stat_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_e_stat_" + m_era +"Up", bdtScore, (basicWeight / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_stat_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_e_stat_" + m_era +"Down", bdtScore, (basicWeight / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_stat_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_e_reco_" + m_era +"Up", bdtScore, (basicWeight / e->elesTopMVAT_reoSF_weight.v()) * e->elesTopMVAT_reoSF_weight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_eff_e_reco_" + m_era +"Down", bdtScore, (basicWeight / e->elesTopMVAT_reoSF_weight.v()) * e->elesTopMVAT_reoSF_weight_down.v(), SR1tau1l, m_isData);


        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_jesUp", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_jes_up.v(), SR1tau1l, m_isData);//!JES part should only be considered with the corresponding JES variation
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_jesDown", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_jes_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_hfUp", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hf_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_hfDown", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hf_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_lfUp", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lf_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_lfDown", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lf_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_hfstats1_" + m_era +"Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_hfstats1_" + m_era +"Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_hfstats2_" + m_era +"Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_hfstats2_" + m_era +"Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_lfstats1_" + m_era +"Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_lfstats1_" + m_era +"Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_lfstats2_" + m_era +"Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_lfstats2_" + m_era +"Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_cferr1Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_cferr1Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_cferr2Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_shape_cferr2Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_down.v(), SR1tau1l, m_isData);

        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPM_" + m_era +"Up", bdtScore, (basicWeight / e->btagWPMedium_weight.v()) * e->btagWPMedium_weight_up.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPM_" + m_era +"Down", bdtScore, (basicWeight / e->btagWPMedium_weight.v()) * e->btagWPMedium_weight_down.v(), SR1tau1l, m_isData);
        // //Btag WP medium and tight uncertainty
        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPMT_" + m_era +"Up", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_up.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPMT_" + m_era +"Down", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_down.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPMT_correlatedUp", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_correlated_up.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPMT_correlatedDown", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_correlated_down.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPMT_uncorrelated_"+ m_era +"Up", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_uncorrelated_up.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_CMS_eff_bWPMT_uncorrelated_"+ m_era +"Down", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_uncorrelated_down.v(), SR1tau1l, m_isData); 
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_comb_bc_correlatedUp", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_correlated_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_comb_bc_correlatedDown", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_correlated_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_comb_bc_uncorrelated_" + m_era +"Up", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_uncorrelated_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_comb_bc_uncorrelated_" + m_era +"Down", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_uncorrelated_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_incl_light_correlatedUp", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_correlated_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_incl_light_correlatedDown", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_correlated_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_incl_light_uncorrelated_" + m_era +"Up", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_uncorrelated_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_btag_fixedWP_incl_light_uncorrelated_" + m_era +"Down", bdtScore, (basicWeight / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_uncorrelated_down.v(), SR1tau1l, m_isData); 

        

        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(tau)_eff_hlt_stats_" + m_era +"Up", bdtScore, (basicWeight / e->HLT_weight.v()) * e->HLT_weight_stats_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(tau)_eff_hlt_stats_" + m_era +"Down", bdtScore, (basicWeight / e->HLT_weight.v()) * e->HLT_weight_stats_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_hltLep_" + m_era +"Up", bdtScore, (basicWeight /  e->triggerSFLep_weight.v()) * e->triggerSFLep_weight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_CMS_tttt(SS)_eff_hltLep_" + m_era +"Down", bdtScore, (basicWeight /  e->triggerSFLep_weight.v()) * e->triggerSFLep_weight_down.v(), SR1tau1l, m_isData);

        //theorectical uncertainties
        // SR1tau1lSys.fillHistVec(region + "_pdfUp", bdtScore, basicWeight* e->pdfWeight_up_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_pdfDown", bdtScore, basicWeight* e->pdfWeight_down_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_pdf_alphasUp", bdtScore, basicWeight* e->pdfWeightAlphaS_up_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_pdf_alphasDown", bdtScore, basicWeight* e->pdfWeightAlphaS_down_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_QCDscale_renUp", bdtScore, basicWeight* e->scaleWeightRe_up_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_QCDscale_renDown", bdtScore, basicWeight* e->scaleWeightRe_down_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_QCDscale_facUp", bdtScore, basicWeight* e->scaleWeightFa_up_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_QCDscale_facDown", bdtScore, basicWeight* e->scaleWeightFa_down_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_QCDscale_renUp", bdtScore, basicWeight* e->scaleWeightRe_up_.v()*m_scaleRe_normUp_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_QCDscale_renDown", bdtScore, basicWeight* e->scaleWeightRe_down_.v()*m_scaleRe_normDown_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_QCDscale_facUp", bdtScore, basicWeight* e->scaleWeightFa_up_.v()*m_scaleFa_normUp_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_QCDscale_facDown", bdtScore, basicWeight* e->scaleWeightFa_down_.v()*m_scaleFa_normDown_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_pdf_alphasUp", bdtScore, basicWeight* e->pdfWeightAlphaS_up_.v()*m_pdfAlphaS_normUp_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_pdf_alphasDown", bdtScore, basicWeight* e->pdfWeightAlphaS_down_.v()*m_pdfAlphaS_normDown_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_pdfUp", bdtScore, basicWeight* e->pdfWeight_up_.v()*m_pdf_normUp_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_pdfDown", bdtScore, basicWeight* e->pdfWeight_down_.v()*m_pdf_normDown_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_ps_isrUp", bdtScore, basicWeight* e->PSWeightISR_up_.v()*m_PSWeightISR_normUp_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_ps_isrDown", bdtScore, basicWeight* e->PSWeightISR_down_.v()*m_PSWeightISR_normDown_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_ps_fsrUp", bdtScore, basicWeight* e->PSWeightFSR_up_.v()*m_PSWeightFSR_normUp_SF, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec(region + "_ps_fsrDown", bdtScore, basicWeight* e->PSWeightFSR_down_.v()*m_PSWeightFSR_normDown_SF, SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_ISRUp", bdtScore, basicWeight* e->PSWeightISR_up_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_ISRDown", bdtScore, basicWeight* e->PSWeightISR_down_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_FSRUp", bdtScore, basicWeight* e->PSWeightFSR_up_.v(), SR1tau1l, m_isData);
        // SR1tau1lSys.fillHistVec(region + "_FSRDown", bdtScore, basicWeight* e->PSWeightFSR_down_.v(), SR1tau1l, m_isData);
        
        }else if(m_isFakeTau){
            SR1tau1lSys.fillHistVec(region + "_CMS_fake_t_"+m_era +"Up", bdtScore, e->FR_weight_final_up, SR1tau1l, m_isData);
            SR1tau1lSys.fillHistVec(region + "_CMS_fake_t_"+m_era +"Down", bdtScore, e->FR_weight_final_down, SR1tau1l, m_isData);
        }

}


void treeAnalyzer::Terminate()
{
    std::cout << "Termintate: ..........................................\n";

    if(!(m_isFakeTau || m_isFakeLepton || m_isData)){
            Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
            const Double_t processScale = ((TTTT::lumiMap.at(m_era)* TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
            SR1tau1lSys.scale(processScale);
            std::cout<<"processScale: "<<processScale<<"\n";
    }
    SR1tau1lSys.print();

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}



treeAnalyzer::~treeAnalyzer()
{
    // code to free any dynamically allocated resources
    m_file->Close();
    m_outFile->Close();
}  