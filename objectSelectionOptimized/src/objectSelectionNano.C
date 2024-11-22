#include "../include/objectSelectionNano.h"
#include "../include/usefulFunc.h"
#include "../../src_cpp/lumiAndCrossSection.h"

void objectSelection::EventLoop(const Bool_t iftauSel, const Bool_t preSelection, const Bool_t ifHLT, ULong_t numEntries)
{
    ULong_t entryCount = 0;
    if (numEntries <= 0)
    {
        numEntries = m_reader.GetEntries();
    }
    std::cout << "Start event loop for " << numEntries << " ................................\n";
    while (m_reader.Next() && entryCount < numEntries)
    {
        entryCount++;
        if(entryCount==1){
            std::cout <<"ifTauSel="<<iftauSel<< " preSelection="<< preSelection << "; ifHLT="<<ifHLT<< "\n";
        }


        Double_t genWeight = 1.0;
        if(!m_isData){
            genWeight = **e->genWeight;
            //calculate pdf up sum and down sum for later scaling 
            if (e->LHEPdfWeight != nullptr)
            {//!!!some files like wz don't have LHE branches, assign nominal 1 to them
                Double_t pdfUnc = OS::quadraticSum(*(e->LHEPdfWeight), 1., 100);
                m_pdfSumwUp += (1.+pdfUnc)*genWeight;
                m_pdfSumwDown += (1.-pdfUnc)*genWeight;
            }
            if(e->PSWeight!=nullptr){//PS weights (w_var / w_nominal); [0] is ISR=2 FSR=1; [1] is ISR=1 FSR=2[2] is ISR=0.5 FSR=1; [3] is ISR=1 FSR=0.5;
                m_PSWeightISRSumwUp += e->PSWeight->At(0)*genWeight;
                m_PSWeightISRSumwDown += e->PSWeight->At(2)*genWeight;
                m_PSWeightFSRSumwUp += e->PSWeight->At(1)*genWeight;
                m_PSWeightFSRSumwDown += e->PSWeight->At(3)*genWeight;
            }
        }
        m_cutflow->Fill(0., genWeight);

        // good lumi and good PV selection
        if (!(lumiAndPVSelection.Select(m_isData, e)))//!!!turn off temperorilly
        {
            continue;
        };

        // MET filters
        if (!(metFilter.Select(m_era, e)))
        {
            continue;
        }
        m_cutflow->Fill(1., genWeight);

        // HLT selection and HLT branch filling
        Bool_t passHLT = HLTselection.Select(e,  ifHLT);
        Bool_t passLepTri = HLTselection.SelectLepTri(e);//!!!for 1tau2l
        Bool_t ifPassHLT = m_if1tau2l? passLepTri: passHLT;
        if(!(OS::ifEventPass(ifHLT, ifPassHLT, m_cutflow, 2, genWeight))){
            continue;
        }

        // CF_HLT->Fill(0., genWeight);

        muSel.Select(e); //muons tight for run 3
        eleMVASel.Select(e);

        // TOPMVA lepton selection
        muTopMVATSel.Select(e);
        muTopMVAFSel.Select(e);
        eleTopMVATSel.Select(e, muTopMVAFSel.getEtaVec(), muTopMVAFSel.getPhiVec());
        eleTopMVAFSel.Select(e, muTopMVAFSel.getEtaVec(), muTopMVAFSel.getPhiVec());//!need overlap removal with fakeable muon

        //leptons for overlap removal
        std::vector<Double_t> muEtaVec = m_isRun3 ? muSel.getEtaVec(): muTopMVAFSel.getEtaVec();
        std::vector<Double_t> muPhiVec = m_isRun3 ? muSel.getPhiVec(): muTopMVAFSel.getPhiVec();
        std::vector<Double_t> eleEtaVec = m_isRun3 ? eleMVASel.getEtaVec(): eleTopMVAFSel.getEtaVec();
        std::vector<Double_t> elePhiVec = m_isRun3 ? eleMVASel.getPhiVec(): eleTopMVAFSel.getPhiVec();

        // tau selection
        tauSel.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec);
        tauSelF.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec);
        tauSelL.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec);
        tauSelTT.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec);
        tauSelTTT.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec);
        tauSelM.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec);
        tauSelTTTT.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec);

        const std::vector<Double_t> tausFEtaVec = tauSelF.getEtaVec();
        const std::vector<Double_t> tausFPhiVec = tauSelF.getPhiVec();
        m_tausTotal += tauSel.getSize();
        m_tausFTotal += tauSelF.getSize();
        m_tausLTotal += tauSelL.getSize();

        // jet and bjet selection
        jetSel.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec, tausFEtaVec, tausFPhiVec, kTRUE);
        bjetMSel.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec, tausFEtaVec, tausFPhiVec, kTRUE);
        bjetLSel.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec, tausFEtaVec, tausFPhiVec, kTRUE);
        bjetTSel.Select(e, m_isData, muEtaVec, muPhiVec, eleEtaVec, elePhiVec, tausFEtaVec, tausFPhiVec, kTRUE);
        m_jetsTotal += jetSel.getSize();
        m_bjetsM += bjetMSel.getSize();

        // pile up weight cal
        puWeightCal.Select(e, m_isData);

        //systematic Weight cal
        systWeightCal.Select(e, m_isData);

        // if(!(OS::ifEventPass(iftauSel, tauSel.getSize()>0, m_cutflow, 3))){ //!for b-tag efficiency measurement
        const Bool_t tauLepCut = m_if1tau2l? (eleTopMVAFSel.getSize()+muTopMVAFSel.getSize())==2 && tauSelF.getSize()>0: tauSelF.getSize()>0;
        if(!(OS::ifEventPass(iftauSel, tauLepCut, m_cutflow, 3, genWeight))){//!use tauF so that fakeTau bg can be estimated later
            continue;
        }

        Bool_t jetCut = m_if1tau2l? jetSel.getSize()>1: jetSel.getSize()>5;
        if(!(OS::ifEventPass(preSelection, jetCut, m_cutflow, 4, genWeight))){
            continue;
        }
        Bool_t bjetCut = m_if1tau2l? bjetMSel.getSize()>0: bjetMSel.getSize()>1;
        if(!(OS::ifEventPass(preSelection, bjetCut, m_cutflow, 5, genWeight))){//baseline for 1tau2l
            continue;
        }//!No b-tag ,for b-tag efficiency measurement!
        Bool_t HTCut = m_if1tau2l? jetSel.getHT()>200.: (jetSel.getHT()>480.&& jetSel.get6thPt()>38.);
        if(!OS::ifEventPass(preSelection, HTCut , m_cutflow, 6, genWeight)){
            continue;
        }

        // copy some nanoAOD branches
        Bool_t ifRemoveEvent = copyBranch.Select(e, m_isData);
        if (ifRemoveEvent)
        {
            continue;
        }
        m_cutflow->Fill(7, genWeight);//!gamma sample overlap removal

        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n\n";
};

void objectSelection::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    std::cout << "outFile here: " << m_output->GetName() << "\n";
    std::cout << "initial events:" << m_cutflow->GetBinContent(1) << ";   HLT: " << m_cutflow->GetBinContent(3) <<"; >=tauF:"<<m_cutflow->GetBinContent(4) <<" preSelection: " << m_cutflow->GetBinContent(7) << "\n";
    std::cout<<"gammaSampleRemoval: "<<m_cutflow->GetBinContent(8)<<"\n";

    std::cout << "elesTotal=" << eleMVASel.getTotal() << ";   musTotal=" << muSel.getTotal() << ";   tausTotal=" << m_tausTotal << "; tausF=" << m_tausFTotal << "; tausL=" << m_tausLTotal << ";  jets=" << m_jetsTotal << ";  bjetsM=" << m_bjetsM << "\n";//includes entries not passing selection

    // get Runs tree
    if (!m_isData)
    {
        std::cout << "copy Runs tree\n";
        TTree *runs = (TTree *)m_input->Get("Runs");
        runs->SetBranchStatus("*", 0);
        runs->SetBranchStatus("genEventSumw", 1);
        runs->SetBranchStatus("LHEPdfSumw", 1);//Sum of genEventWeight * LHEPdfWeight[i], divided by genEventSumw
        runs->SetBranchStatus("LHEScaleSumw", 1);//Sum of genEventWeight * LHEScaleWeight[i], divided by genEventSumw

        TTree *runsForOut = runs->CloneTree();
        //add branch LHEPdfSumwUp, LHEPdfSumwDown
        std::cout<<"m_pdfSumwUp="<<m_pdfSumwUp<<"; m_pdfSumwDown="<<m_pdfSumwDown<<"\n";
        // std::cout<<"m_PSWeightUp="<<m_PSWeightSumwUp<<"; m_PSWeightDown="<<m_PSWeightSumwDown<<"\n";
        TBranch *newBranch = runsForOut->Branch("LHEPdfSumwUp", &m_pdfSumwUp);
        TBranch *newBranch2 = runsForOut->Branch("LHEPdfSumwDown", &m_pdfSumwDown);
        TBranch *newBranch3 = runsForOut->Branch("m_PSWeightISRSumwUp", &m_PSWeightISRSumwUp);
        TBranch *newBranch4 = runsForOut->Branch("m_PSWeightISRSumwDown", &m_PSWeightISRSumwDown);
        TBranch *newBranch5 = runsForOut->Branch("m_PSWeightFSRSumwUp", &m_PSWeightFSRSumwUp);
        TBranch *newBranch6 = runsForOut->Branch("m_PSWeightFSRSumwDown", &m_PSWeightFSRSumwDown);

        for(UInt_t i=0; i<runsForOut->GetEntries(); i++){
            runsForOut->GetEntry(i);
            // runsForOut->Fill();
            newBranch->Fill();
            newBranch2->Fill();
            newBranch3->Fill();
            newBranch4->Fill();
            newBranch5->Fill();
            newBranch6->Fill();
        }

        runsForOut->SetDirectory(m_output);
    }

    m_output->Write();
    m_output->Close();

    std::cout << "Termination done .....................................................\n";
};

objectSelection::~objectSelection()
{
    delete m_input;
    delete e;
};
