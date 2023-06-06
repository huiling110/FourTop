#include "../include/PUWeightCal.h"
#include "../include/inputMap.h"
#include <TFile.h>

PUWeightCal::PUWeightCal(TTree *outTree, Bool_t isData, TString era)
{
    std::cout << "Initializing PUWeightCal...........\n";

    if (!isData)
    { // https://twiki.cern.ch/twiki/bin/view/CMS/PileupJSONFileforData#Recommended_cross_section
        TFile *inputPUFile_data = new TFile(pileUpFileMap[era].at(0).Data(), "READ");
        TFile *inputPUFile_dataUp = new TFile(pileUpFileMap[era].at(1).Data(), "READ");
        TFile *inputPUFile_dataDown = new TFile(pileUpFileMap[era].at(2).Data(), "READ");
        TFile *inputPUFile_mc = new TFile(pileUpFileMap[era].at(3).Data(), "READ");
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

    outTree->Branch("PUWeight", &PUWeight);
    outTree->Branch("PUWeight_up", &PUWeight_up);
    outTree->Branch("PUWeight_down", &PUWeight_down);
    std::cout << "Done initializing ...............\n";
    std::cout << "\n";
};

void PUWeightCal::Select(eventForNano *e, Bool_t isData)
{
    clearBranch();
    if (!isData)
    {
        if (MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt)) > 0)
        { //???why do it this way???
            PUWeight = dataPileupProfile->GetBinContent(dataPileupProfile->FindBin(**e->Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt));
            PUWeight_up = dataPileupProfileUp->GetBinContent(dataPileupProfileUp->FindBin(**e->Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt));
            PUWeight_down = dataPileupProfileDown->GetBinContent(dataPileupProfileDown->FindBin(**e->Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(**e->Pileup_nTrueInt));
        }
    }
};

void PUWeightCal::clearBranch()
{
    PUWeight = 1.0;
    PUWeight_up = 1.0;
    PUWeight_down = 1.0;
};
