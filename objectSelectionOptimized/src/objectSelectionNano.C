#include "../include/objectSelectionNano.h"
#include "../include/usefulFunc.h"
#include "../../src_cpp/lumiAndCrossSection.h"

void objectSelection::EventLoop(const Bool_t preSelection, const Bool_t ifHLT, ULong_t numEntries, const Int_t tauTES, const Int_t ifJER, const Int_t sysJEC)
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
            std::cout << "tauTES=" << tauTES << ";  JER=" << ifJER << "; JES="<<sysJEC<<";  preSelection="<< preSelection << "; ifHLT="<<ifHLT<< "\n";
        }

        Double_t genWeight = 1.0;
        if(!m_isData){
            genWeight = **e->genWeight;
        }
        m_cutflow->Fill(0);
        CF_initial->Fill(0., genWeight);

        // good lumi and good PV selection
        if (!(lumiAndPVSelection.Select(m_isData, e)))
        {
            continue;
        };

        // MET filters
        if (!(metFilter.Select(m_era, e)))
        {
            continue;
        }
        m_cutflow->Fill(1);
        CF_met->Fill(0., genWeight);

        // // HLT selection and HLT branch filling
        Bool_t passHLT = HLTselection.Select(e, m_era, m_isData, ifHLT);
        // // if (ifHLT && (!passHLT))
        if(!passHLT)
        {
            continue; // pass on this event 
        }
        m_cutflow->Fill(2);
        CF_HLT->Fill(0., genWeight);

        muSel.Select(e);
        eleMVASel.Select(e);

        // TOPMVA lepton selection
        eleTopMVATSel.Select(e);
        muTopMVATSel.Select(e);


        // // tau selection
        tauSel.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tauTES);
        tauSelF.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tauTES);
        tauSelL.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tauTES);
        const std::vector<Double_t> tausFEtaVec = tauSelF.getEtaVec();
        const std::vector<Double_t> tausFPhiVec = tauSelF.getPhiVec();
        m_tausTotal += tauSel.getSize();
        m_tausFTotal += tauSelF.getSize();
        m_tausLTotal += tauSelL.getSize();

        // // jet and bjet selection
        // // const Int_t sysJEC = 0;
        jetSel.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        jetTSel.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetMSel.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetLSel.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        bjetTSel.Select(e, m_isData, muTopMVATSel.getEtaVec(), muTopMVATSel.getPhiVec(),  eleTopMVATSel.getEtaVec(), eleTopMVATSel.getPhiVec(), tausFEtaVec, tausFPhiVec, kTRUE, ifJER, sysJEC);
        m_jetsTotal += jetSel.getSize();
        m_bjetsM += bjetMSel.getSize();

        // copy some nanoAOD branches
        copyBranch.Select(e, m_isData);

        // pile up weight cal
        puWeightCal.Select(e, m_isData);

        //systematic Weight cal
        systWeightCal.Select(e, m_isData);

        // pre selection
        if (preSelection)
        {
            if (!(jetSel.getSize() > 5 && bjetMSel.getSize() > 0))
                continue;
        }

        m_cutflow->Fill(3);
        CF_pre->Fill(0., genWeight);

        m_outTree->Fill();
    };
    std::cout << "End of event loop...................................................\n\n";
};

void objectSelection::Terminate()
{
    std::cout << "Terminate phase.......................................................\n";
    std::cout << "outFile here: " << m_output->GetName() << "\n";
    std::cout << "initial events:" << m_cutflow->GetBinContent(1) << ";   HLT: " << m_cutflow->GetBinContent(3) << " preSelection: " << m_cutflow->GetBinContent(4) << "\n";
    ";   HLT: " << m_cutflow->GetEntries(3) << " preSelection: " << m_cutflow->GetEntries(4) << "\n";
    std::cout << "elesTotal=" << eleMVASel.getTotal() << ";   musTotal=" << muSel.getTotal() << ";   tausTotal=" << m_tausTotal << "; tausF=" << m_tausFTotal << "; tausL=" << m_tausLTotal << ";  jets=" << m_jetsTotal << ";  bjetsM=" << m_bjetsM << "\n";

    // get Runs tree
    if (!m_isData)
    {
        std::cout << "copy Runs tree\n";
        TTree *runs = (TTree *)m_input->Get("Runs");
        runs->SetBranchStatus("*", 0);
        runs->SetBranchStatus("genEventSumw", 1);

        TTree *runsForOut = runs->CloneTree();
        runsForOut->SetDirectory(m_output);
    }

    //scale cutflow hist
    //!!!I don't think we can scale individial tree like this


    m_output->Write();
    m_output->Close();

    std::cout << "Termination done .....................................................\n";
};

objectSelection::~objectSelection()
{
    delete m_input;
    delete e;
    // delete m_output;
};

// void objectSelection::getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec)
// {
//     std::vector<Double_t> &muEtaVec = muTopMVATSel.getEtaVec();
//     std::vector<Double_t> &muPhiVec = muTopMVATSel.getPhiVec();
//     std::vector<Double_t> &eleEtaVec = eleTopMVATSel.getEtaVec();
//     std::vector<Double_t> &elePhiVec = eleTopMVATSel.getPhiVec();
//     if(m_isRun3){
//         muEtaVec = muSel.getEtaVec();
//         muPhiVec = muSel.getPhiVec();
//         eleEtaVec = eleMVASel.getEtaVec();
//         elePhiVec = eleMVASel.getPhiVec();
//         }
//     OS::addTwoObjs(muEtaVec, eleEtaVec, lepEtaVec);
//     OS::addTwoObjs(muPhiVec, elePhiVec, lepPhiVec);
//     // std::cout<<"lepEtaVec = "<< lepEtaVec.size()<<"\n";
// };