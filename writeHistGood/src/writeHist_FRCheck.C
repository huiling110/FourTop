#include "../include/writeHist_FRCheck.h"
#include "../include/inputFileMap.h"
#include "../include/commenSelectionAndWeight.h"
#include "../../myLibrary/commenFunction.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"

#include <vector>




void getRegions1(std::vector<TString>& allRegions, TString baseRegion = "1tau0lMR", TString prongNum="1prong", TString jetEta="Eta1"){
    allRegions.push_back(baseRegion + "_" +jetEta+"_"+prongNum);
    allRegions.push_back(baseRegion + "Gen_" +jetEta+"_"+prongNum);
    allRegions.push_back(baseRegion + "LTau_" +jetEta+"_"+prongNum);
    allRegions.push_back(baseRegion + "LTauGen_" +jetEta+"_"+prongNum);
    
}

void WH_FRCheck::Init()
{
    std::cout << "Start to initilation....................................................\n";
    //regions for measuring FR
    // if(m_ifMeasure){
        std::vector<TString> regionsEtaDivided;
        getRegions1(regionsEtaDivided, "1tau0lMR", "1prong", "Eta1");
        getRegions1(regionsEtaDivided, "1tau0lMR", "1prong", "Eta2");
        getRegions1(regionsEtaDivided, "1tau0lMR", "1prong", "Eta3");
        getRegions1(regionsEtaDivided, "1tau0lMR", "3prong", "EtaAll");
        getRegions1(regionsEtaDivided, "1tau0lMRCR", "1prong", "Eta1");
        getRegions1(regionsEtaDivided, "1tau0lMRCR", "1prong", "Eta2");
        getRegions1(regionsEtaDivided, "1tau0lMRCR", "1prong", "Eta3");
        getRegions1(regionsEtaDivided, "1tau0lMRCR", "3prong", "EtaAll");
        getRegions1(regionsEtaDivided, "1tau0lVR", "1prong", "Eta1");
        getRegions1(regionsEtaDivided, "1tau0lVR", "1prong", "Eta2");
        getRegions1(regionsEtaDivided, "1tau0lVR", "1prong", "Eta3");
        getRegions1(regionsEtaDivided, "1tau0lVR", "3prong", "EtaAll");

        getRegions1(regionsEtaDivided, "1tau0lMRCR", "allProng", "allEta");

        std::vector<Double_t> bins = {25., 30, 35, 40., 50., 70., 100., 300.};
        tausF_1jetPt_class = histsForRegionsMap<Double_t>("tausT_1pt", "pT^{#tau}(GeV)", m_processName, bins, regionsEtaDivided, &(e->tausT_1pt));
        tausF_1jetPt_class.setDir(m_outFile);


     std::cout<< "Initialization done\n\n";
}

void WH_FRCheck::LoopTree(UInt_t entry)
{
    Long64_t allEvent = m_tree->GetEntries();
    if (entry > 0)
    {
        allEvent = entry;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        if (!(baselineSelection(e, m_isRun3, kFALSE)))
        {
            continue;
        }
        if(!(e->tausF_num.v()==1)){//!maybe critcal for the FR application, ensure no tauF=2 events
            continue;
        }

        Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData,  1, kFALSE, kFALSE); //!!!MC correction for 1tau0l

        const Bool_t isTauLNum = (e->tausF_num.v() == 1);
        const Bool_t isTauFT = (e->tausF_num.v() == 1) && e->tausF_1isTight.v();
        const Bool_t isTauTNumGen = e->tausF_1genFlavour.v() != 0  ; //Flavour of genParticle for MC matching to status==2 taus: 1 = prompt electron, 2 = prompt muon, 3 = tau->e decay, 4 = tau->mu decay, 5 = hadronic tau decay, 0 = unknown or unmatched
        const Bool_t isTauLNumGen = e->tausF_1genFlavour.v() != 0;
        Int_t jetsNum = e->jets_num.v();
        Int_t bjetsNum = e->bjetsM_num.v();
        Int_t lepNum = e->elesTopMVAT_num.v() + e->muonsTopMVAT_num.v();

        // 1tau0lMR
        Bool_t is1tau0lMR = isTauFT  && jetsNum >= 8 && bjetsNum == 2; 
        Bool_t is1tau0lMRLTau = isTauLNum && jetsNum >= 8 && bjetsNum == 2;
        //1tau0lVR
        Bool_t is1tau0lVR = isTauFT && lepNum == 0 && jetsNum < 8 && bjetsNum >=3;
        Bool_t is1tau0lVRLTau = isTauLNum && lepNum == 0 && jetsNum < 8 && bjetsNum >=3;
        //1tau0lCR
        Bool_t is1tau0lCR = isTauFT && lepNum == 0 && jetsNum < 8 && bjetsNum ==2;
        Bool_t is1tau0lCRLTau = isTauLNum && lepNum == 0 && jetsNum < 8 && bjetsNum ==2;
        //1tau0lSR
        Bool_t is1tau0lSR = SR1tau1lSel(e, 1, m_isRun3);
        Bool_t is1tau0lSRLTau = isTauLNum && lepNum == 0 && jetsNum >= 8 && bjetsNum >=3;

        // Double_t tausF_1jetEtaAbs = std::abs(e->tausF_1jetEtaAbs.v()); //!tausF_1jetEtaAbs should be more accurate!
        Double_t tausF_1jetEtaAbs = std::abs(e->tausF_1jetEta.v()); //!tausF_1jetEtaAbs should be more accurate!
        // std::cout<<"tausF_1jetEtaAbs: "<<tausF_1jetEtaAbs<<"\n";
        // if(m_ifMeasure){
            const Bool_t isProng1 = (e->tausF_1prongNum.v() == 1);
            Bool_t isEta1 = 0 < tausF_1jetEtaAbs && tausF_1jetEtaAbs <= 0.8;
            Bool_t isEta2 = 0.8 < tausF_1jetEtaAbs && tausF_1jetEtaAbs <= 1.5;
            Bool_t isEta3 = 1.5 < tausF_1jetEtaAbs && tausF_1jetEtaAbs <= 2.4; //!consider the jet eta cut instead of tau eta
            if(m_isData){
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTau_Eta1_1prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  isEta1 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTau_Eta2_1prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  isEta2 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTau_Eta3_1prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  isEta3 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTau_EtaAll_3prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  (!isProng1), m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCR_Eta1_1prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  isEta1 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCR_Eta2_1prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  isEta2 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCR_Eta3_1prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  isEta3 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCR_EtaAll_3prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  (!isProng1), m_isData);

                tausF_1jetPt_class.fillHistVec("1tau0lMRCR_allEta_allProng", basicWeight, (is1tau0lMR || is1tau0lCR), m_isData);

                tausF_1jetPt_class.fillHistVec("1tau0lVRLTau_Eta1_1prong", basicWeight, (is1tau0lVRLTau) &&  isEta1 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTau_Eta2_1prong", basicWeight, (is1tau0lVRLTau) &&  isEta2 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTau_Eta3_1prong", basicWeight, (is1tau0lVRLTau) &&  isEta3 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTau_EtaAll_3prong", basicWeight, (is1tau0lVRLTau) &&  (!isProng1), m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVR_Eta1_1prong", basicWeight, (is1tau0lVR) &&  isEta1 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVR_Eta2_1prong", basicWeight, (is1tau0lVR) &&  isEta2 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVR_Eta3_1prong", basicWeight, (is1tau0lVR) &&  isEta3 && isProng1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVR_EtaAll_3prong", basicWeight, (is1tau0lVR) &&  (!isProng1), m_isData);

            }else{
                //gen
                //MRCR
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTauGen_Eta1_1prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  isEta1&& isProng1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTauGen_Eta2_1prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  isEta2&& isProng1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTauGen_Eta3_1prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  isEta3&& isProng1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRLTauGen_EtaAll_3prong", basicWeight, (is1tau0lMRLTau || is1tau0lCRLTau) &&  (!isProng1) && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRGen_Eta1_1prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  isEta1 && isProng1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRGen_Eta2_1prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  isEta2 && isProng1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRGen_Eta3_1prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  isEta3 && isProng1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRCRGen_EtaAll_3prong", basicWeight, (is1tau0lMR || is1tau0lCR) &&  (!isProng1) && isTauTNumGen, m_isData);

                tausF_1jetPt_class.fillHistVec("1tau0lMRCRGen_allEta_allProng", basicWeight, (is1tau0lMR || is1tau0lCR) &&  isTauTNumGen, m_isData);

                tausF_1jetPt_class.fillHistVec("1tau0lVRLTauGen_Eta1_1prong", basicWeight, (is1tau0lVRLTau) &&  isEta1 && isProng1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTauGen_Eta2_1prong", basicWeight, (is1tau0lVRLTau) &&  isEta2 && isProng1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTauGen_Eta3_1prong", basicWeight, (is1tau0lVRLTau) &&  isEta3 && isProng1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTauGen_EtaAll_3prong", basicWeight, (is1tau0lVRLTau) &&  (!isProng1) && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRGen_Eta1_1prong", basicWeight, (is1tau0lVR) &&  isEta1 && isProng1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRGen_Eta2_1prong", basicWeight, (is1tau0lVR) &&  isEta2 && isProng1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRGen_Eta3_1prong", basicWeight, (is1tau0lVR) &&  isEta3 && isProng1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRGen_EtaAll_3prong", basicWeight, (is1tau0lVR) &&  (!isProng1) && isTauTNumGen, m_isData);
            }


    }
    std::cout << "end of event loop\n\n";
}

void WH_FRCheck::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    if (!m_isData)
    {
        Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
        Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
        std::cout << "m_processName=" << m_processName << " lumi=" << TTTT::lumiMap.at(m_era) << " crossSection=" << TTTT::crossSectionMap.at(m_processName) << "\n";
        // WH::histRegionsVectScale(histsForRegion_vec, processScale);
        tausF_1jetPt_class.scale(processScale);
        tausF_1jetPt_class.print();

        // WH::histRegionsVectScale(histsForRegion_vec, processScale);
    };
    // for (UInt_t i = 0; i < histsForRegion_vec.size(); i++)
    // {
    //     if (i > 0)
    //     {
    //         continue;
    //     }
    //     histsForRegion_vec.at(i)->print();
    // }

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}

WH_FRCheck::~WH_FRCheck()
{
    m_file->Close();
    m_outFile->Close();
}