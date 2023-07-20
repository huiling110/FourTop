#include "../include/createHists.h"
#include <cmath>

CreateHist::CreateHist(TFile * outFile){
    std::cout << "Initializing CreateHist class..........\n";
    m_h2D_jets_ptEta_b->SetDirectory(outFile);
    m_h2D_jets_ptEta_c->SetDirectory(outFile);
    m_h2D_jets_ptEta_l->SetDirectory(outFile);
    std::cout<<"Done initialization...................\n\n";
}


void CreateHist::fillHist(const EventForMV* e){
    for(UInt_t i=0; i<e->jets_pt.GetSize(); i++){
        Int_t jetFlavour = e->jets_flavour.At(i); 
        Double_t jetPt = e->jets_pt.At(i);
        Double_t jetEta = std::abs(e->jets_eta.At(i));
        switch (jetFlavour)
        {
        case 5: // b jet
            m_h2D_jets_ptEta_b->Fill( jetPt, jetEta);
            break;
        case 4: //c jet
            m_h2D_jets_ptEta_c->Fill( jetPt, jetEta);
            break;
        case 0: //c jet
            m_h2D_jets_ptEta_l->Fill( jetPt, jetEta);
            break;
        default:
            break;
        }
    }
}

CreateHist::~CreateHist(){
    // delete m_h2D_jets_ptEta_b;
}