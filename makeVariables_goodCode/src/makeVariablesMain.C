#include "../include/makeVariablesMain.h"
#include "../include/variablesFunctions.h"

void MakeVariablesMain::EventLoop(Bool_t baselineSel, Bool_t  tau1e1Sel, ULong_t numEntries)
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
        m_cutflow->Fill(0);
        if(entryCount==1){
            std::cout << "baselineSel=" << baselineSel << "  tau1e1Sel=" << tau1e1Sel << "\n";
        }
        // if (entryCount % (numEntries / 10) == 0)//!causing running time issue in jobs
        // {
        //     std::cout << "Processing: " << (100 * entryCount / numEntries) << "%\r" << std::flush;
        // }

        muVarMaker.makeVariables(e);
        muTopTVarMaker.makeVariables(e);
        eleVarMaker.makeVariables(e);
        eleTopVarMaker.makeVariables(e);

        lepVarMaker.makeVariables(e);
        lepVarFMaker.makeVariables(e);

        std::vector<ROOT::Math::PtEtaPhiMVector> leptonsMVAT;
        addLorentzVector(muTopTVarMaker.getLorentzObjs(), eleTopVarMaker.getLorentzObjs(), leptonsMVAT);//Pt already sorted
        tauVarMaker.makeVariables(e, leptonsMVAT); // !tight tau
        tauFVarMaker.makeVariables(e, leptonsMVAT);
        tauLVarMaker.makeVariables(e, leptonsMVAT);
        tauTTVarMaker.makeVariables(e, leptonsMVAT);
        tauTTTVarMaker.makeVariables(e, leptonsMVAT);
        tauTTTTVarMaker.makeVariables(e, leptonsMVAT);
        tauMVarMaker.makeVariables(e, leptonsMVAT);

        jetVarMaker.makeVariables(e, tauVarMaker.getLorentzObjs(), jesVariation);
        //bjet variables
        bjetMVarMaker.makeVariables(e, tauVarMaker.getLorentzObjs(), tauFVarMaker.getLorentzObjs(), leptonsMVAT, jesVariation);
        bjetLVarMaker.makeVariables(e, tauVarMaker.getLorentzObjs(), tauFVarMaker.getLorentzObjs(), leptonsMVAT, jesVariation);
        bjetTVarMaker.makeVariables(e, tauVarMaker.getLorentzObjs(), tauFVarMaker.getLorentzObjs(), leptonsMVAT, jesVariation);
        // bjetPNMVarMaker.makeVariables(e, tauVarMaker.getLorentzObjs(), tauFVarMaker.getLorentzObjs(), leptonsMVAT);
        // bjetPTMVarMaker.makeVariables(e, tauVarMaker.getLorentzObjs(), tauFVarMaker.getLorentzObjs(), leptonsMVAT);
        // bjetPTTVarMaker.makeVariables(e, tauVarMaker.getLorentzObjs(), tauFVarMaker.getLorentzObjs(), leptonsMVAT);

        topVarMaker.makeVariables(e, jetVarMaker.getLorentzObjs(), bjetMVarMaker.getLorentzObjs(), leptonsMVAT, tauVarMaker.getLorentzObjs());

        // baseline selection
        // Int_t bjetM_num = m_isRun3? bjetPTMVarMaker.getJet_num(): bjetMVarMaker.getJet_num();
        Int_t bjetM_num =  bjetMVarMaker.getJet_num();
        Bool_t ifPass = kFALSE;
        if(m_is1tau2l){
            ifPass = jetVarMaker.getHT() > 200. && jetVarMaker.getJet_num() >=2 && bjetM_num >= 1 && tauVarMaker.getNum()==1; 
        }else{
            if(bjetM_num<4){
                ifPass = jetVarMaker.getHT() > 500. && jetVarMaker.getJet_6pt() > 40. && jetVarMaker.getJet_num() >= 6;
            }else{
                ifPass = jetVarMaker.getHT() > 480. && jetVarMaker.getJet_6pt() > 38. && jetVarMaker.getJet_num() >= 6;
            }
            ifPass = ifPass && bjetM_num >= 2;
        }
        if (baselineSel&&!ifPass)
        {
            // if (!(jetVarMaker.getHT() > 550 && jetVarMaker.getJet_6pt() > 40 && jetVarMaker.getJet_num() >=6 )) //!!!for btag-efficiency measurement
            continue;
        }
        if(tau1e1Sel){
            // if(!(jetVarMaker.getJet_num()>= 7 && bjetM_num >= 3 && tauVarMaker.getNum()==1 && (eleTopVarMaker.getNum()+muTopTVarMaker.getNum())==1 )){//!1tau1l SR
            if(!(jetVarMaker.getJet_num()>= 8 && bjetM_num >= 3 && tauFVarMaker.getNum()==1 && (eleTopVarMaker.getNum()+muTopTVarMaker.getNum())==0  )){ //!1tau0lSR, can not add tauT cut, for fake tau estimation later
            // if(!(jetVarMaker.getJet_num()>= 4 && bjetM_num >= 2 && tauVarMaker.getNum()==1 && lepVarMaker.getNum()==2 && lepVarMaker.get1pt()>25. && lepVarMaker.get2pt()>13. )){ //!1tau2lSR, for BDTraining, not including fakeLepton
                continue;
            }
        }

        //create hists for b tag efficiency measurement
        createHist.fillHist(e);
        // copy some branches
        copyBranches.makeVariables(e);
        // SF and systematic calculation
        weightVarMaker.makeVariables(e, jetVarMaker.getHT() , jetVarMaker.getJet_6pt(), bjetM_num);

        m_cutflow->Fill(1);

        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n";
    std::cout << "\n";
};

void MakeVariablesMain::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";

    // add Runs tree
    if (!(m_isData))
    {
        std::cout << "--------\n";
        std::cout << "now comes to add Runs tree stage\n";
        TChain chain2("Runs");
        chain2.Add(m_inputDir +"*.root");
        TTree *Runs = chain2.CloneTree();
        Runs->SetDirectory(m_output);
        std::cout
            << "done merging Runs trees\n";
        std::cout << "\n";
    }

    std::cout << "MV initial=" << m_cutflow->GetBinContent(1) << "  baseline=" << m_cutflow->GetBinContent(2) << "\n";

    //add the cutflow hists from OS rootfile
    //???when you add 2 histograms, will both the entries and bin content and bin error be dealt with correctly? 


    m_output->Write();
    m_output->Close();
    std::cout << "output file here: " << m_output->GetName() << "\n";
    std::cout << "Termination done .....................................................\n";
};

MakeVariablesMain::~MakeVariablesMain(){};
