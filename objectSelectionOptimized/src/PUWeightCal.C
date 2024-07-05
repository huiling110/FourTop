#include "../include/PUWeightCal.h"
#include "../include/inputMap.h"
#include <TFile.h>

PUWeightCal::PUWeightCal(TTree *outTree, Bool_t isData, TString era, Bool_t isRun3): m_isRun3{isRun3}, m_era{era}
{
    //!!!don't understand this pileup correction and not sure if it's correct
    //https://cms-talk.web.cern.ch/t/pileup-reweighting-questions/30405
    std::cout << "Initializing PUWeightCal...........\n";
    std::cout << "m_isRun3=" << m_isRun3 <<"m_era="<<m_era<< "\n";
    // if (!isData )
    if ((!isData) && (!m_isRun3) )
    { // https://twiki.cern.ch/twiki/bin/view/CMS/PileupJSONFileforData#Recommended_cross_section
        //???what's the best way to provide input file path? relative path or abosolute path?
        // TString baseDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/";
        TString baseDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/";
        TFile *inputPUFile_data = new TFile((baseDir+pileUpFileMap[era].at(0)).Data(), "READ");
        TFile *inputPUFile_dataUp = new TFile((baseDir+pileUpFileMap[era].at(1)).Data(), "READ");
        TFile *inputPUFile_dataDown = new TFile((baseDir+pileUpFileMap[era].at(2)).Data(), "READ");
        TFile *inputPUFile_mc = new TFile((baseDir+pileUpFileMap[era].at(3)).Data(), "READ");
        std::cout << "pileup file used : " << inputPUFile_data->GetName() << "\n";
        // Get needed histograms
        dataPileupProfile = (TH1F *)inputPUFile_data->Get("pileup");
        dataPileupProfileUp = (TH1F *)inputPUFile_dataUp->Get("pileup");
        dataPileupProfileDown = (TH1F *)inputPUFile_dataDown->Get("pileup");
        MCPileupProfile = (TH1F *)inputPUFile_mc->Get("pileup");
        // Scale to unit area for a fair comparison
        dataPileupProfile->Scale(1.0 / dataPileupProfile->Integral());
        dataPileupProfileUp->Scale(1.0 / dataPileupProfileUp->Integral());
        dataPileupProfileDown->Scale(1.0 / dataPileupProfileDown->Integral());
        MCPileupProfile->Scale(1.0 / MCPileupProfile->Integral());
    }
    if(m_isRun3){
        TString jsonBase = "../../jsonpog-integration/POG/";
        cset_puWeight = correction::CorrectionSet::from_file((jsonBase + json_map[era].at(3)).Data());
        std::cout<<"PUWeightCal: json file used: "<<jsonBase + json_map[era].at(3)<<"\n";
    }

    outTree->Branch("PUWeight", &PUWeight);
    outTree->Branch("PUWeight_up", &PUWeight_up);
    outTree->Branch("PUWeight_down", &PUWeight_down);
    std::cout << "Done initializing ...............\n";
    std::cout << "\n";
};

void PUWeightCal::Select(eventForNano *e, Bool_t isData)
{
    //https://github.com/cms-jet/JMEDAS/blob/ea2e4d7234aec2b0bdf82f4d573db2855bfe1593/notebooks/master/Pileup.ipynb#L197
    clearBranch();
    if ((!isData) && (!m_isRun3))
    {
        if (MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt)) > 0)
        { //???why do it this way???
            PUWeight = dataPileupProfile->GetBinContent(dataPileupProfile->FindBin(**e->Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt));
            PUWeight_up = dataPileupProfileUp->GetBinContent(dataPileupProfileUp->FindBin(**e->Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt));
            PUWeight_down = dataPileupProfileDown->GetBinContent(dataPileupProfileDown->FindBin(**e->Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt));
        }
    }

    if(!isData && m_isRun3){
        auto key = m_era.Contains("2022post") ? "Collisions2022_359022_362760_eraEFG_GoldenJson" : "Collisions2022_355100_357900_eraBCD_GoldenJson";
        auto corr_puWeight = cset_puWeight->at(key);

        PUWeight = corr_puWeight->evaluate({**e->Pileup_nTrueInt, "nominal"});
        PUWeight_up = corr_puWeight->evaluate({**e->Pileup_nTrueInt, "up"});
        PUWeight_down = corr_puWeight->evaluate({**e->Pileup_nTrueInt, "down"});
    }
};

void PUWeightCal::clearBranch()
{
    PUWeight = 1.0;
    PUWeight_up = 1.0;
    PUWeight_down = 1.0;
};
