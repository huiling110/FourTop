#include "DrawVariable.h"
#include "CMS_lumi.C"

void DrawVariable(string YEAR, TString VAR, TString CAT, bool LOG, int REBIN, int SCALESIG, float XMIN, float XMAX, TString XTITLE, bool isINT, int XNDIV, bool PRINT) {
    gROOT->ForceStyle();  
    gROOT->SetBatch(kTRUE); //kTRUE ---> histos are not showed while drawn
    
    TFile *inf[file.size()];
    TH1F  *h[file.size()];

    TCanvas *can = new TCanvas("DataVsMC_"+VAR+" "+CAT,"DataVsMC_"+VAR+" "+CAT,900,600);
    can->SetRightMargin(0.15);

    map<string, string>::iterator file_it = file[YEAR].begin();
    map<string, float>::iterator  xsec_it = xsec[YEAR].begin();
    int i = 0;
    
    string data = "JetHT";
    bool data_found, signal_found, ttbar_found, QCD_found, ttX_found, singleTop_found/*, Higgs_found*/;
    data_found = ttbar_found = QCD_found = ttX_found = singleTop_found /*= Higgs_found*/ = signal_found = false;
    TH1F *h_signal = new TH1F; 
    TH1F *h_ttbar = new TH1F;
    TH1F *h_QCD = new TH1F;
    TH1F *h_ttX = new TH1F;
    TH1F *h_singleTop = new TH1F;
    //TH1F *h_Higgs  = new TH1F;
    TH1F *h_DATA = new TH1F;

    while (file_it != file[YEAR].end()) {//loop over processes and get all the needed histograms

        TString openname = "../rootFiles/Histos_" + file_it->second + "_" + TString(YEAR) + ".root";
        inf[i] = TFile::Open( openname );
        TString getHisto = "h_" + VAR + "_" + CAT + "_" + TString(file_it->first);
        h[i] = (TH1F*)inf[i]->Get( getHisto );
        
        if (!h[i]) {
            
            if (file_it->first.find(data) !=std::string::npos && VAR.Contains("jets_HT") && !(CAT.Contains("VR"))) { //do not pick data histograms if it's jets_HT variable and not in the VR
                
                h[i] = new TH1F("","", 1,0,1); // just a toy histogram
                i++;
                file_it++;
                xsec_it++;
                continue;
                
            }
            
            else {
             
                cout<<"Histogram does not exist !!!"<<endl;
                break;
            
            }
      
        }
        
        
        h[i]->SetDirectory(0);
        h[i]->Rebin(REBIN);
        h[i]->SetLineWidth(1);
        h[i]->SetLineColor(kBlack);
        
        //cout << "PROCESS: " << xsec_it->first << endl;
        //cout << "NUMBER OF BINS: " << h[i]->GetSize() << endl;    

        if ( !(file_it->first.find(data) !=std::string::npos) ) {
            
            float norm = ((TH1F*)inf[i]->Get("totalWeight_"+TString(file_it->first)))->GetSumOfWeights();  
        
            if (norm == 0) {
            
                cout<<"Process " << file_it->first << " is empty !!! Skipping" << endl;
                continue;
      
            }
            
            //cout << "NORM FACTOR: " << norm << endl;
            
            h[i]->Scale(lumi[YEAR]*xsec_it->second/norm);

        }
        
        inf[i]->Close();
        i++;
        file_it++;
        xsec_it++;
        
    } //end importing histograms
    
    i = 0;
    file_it = file[YEAR].begin();   
    xsec_it = xsec[YEAR].begin();   
    while (file_it != file[YEAR].end()) {
        
        //AFTER IMPORTING AND SCALING HISTOGRAMS, CHECK WHICH PROCESS YOU ARE READING AND PROPERLY ADD PROCESSES TOGETHER
        if ( file_it->first.find("tttt") !=std::string::npos ) h_signal = (TH1F*)h[i]->Clone("h_signal");

        if ( file_it->first.find("ttbar") !=std::string::npos ) {      

            if (!ttbar_found) {
                
             h_ttbar = (TH1F*)h[i]->Clone("h_ttbar");
             ttbar_found = true;
                
            }
            
            else h_ttbar->Add(h[i]);
            
        } //end it's ttbar

        if ( file_it->first.find("QCD") !=std::string::npos ) {      
            
            if (!QCD_found) {
                
             h_QCD = (TH1F*)h[i]->Clone("h_QCD");
             QCD_found = true;
                
            }
            
            else h_QCD->Add(h[i]);
            
        } //end it's QCD

        if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) {      
            
            if (!ttX_found) {
                
             h_ttX = (TH1F*)h[i]->Clone("h_ttX");
             ttX_found = true;
                
            }
            
            else h_ttX->Add(h[i]);
            
        } //end it's ttX

        if ( file_it->first.find("ST_") !=std::string::npos || file_it->first.find("tZq") !=std::string::npos ) {      
            
            if (!singleTop_found) {
                
             h_singleTop = (TH1F*)h[i]->Clone("h_singleTop");
             singleTop_found = true;
                
            }
            
            else h_singleTop->Add(h[i]);
            
        } //end it's single top
        
        /*
        if ( file_it->first.find("ggH") !=std::string::npos || file_it->first.find("VBF") !=std::string::npos ) {      
            
            if (!Higgs_found) {
                
             h_Higgs = (TH1F*)h[i]->Clone("h_Higgs");
             Higgs_found = true;
                
            }
            
            else h_Higgs->Add(h[i]);
                
        } //end it's Higgs
        */

        if ( file_it->first.find(data) !=std::string::npos && !(VAR.Contains("jets_HT") && !(CAT.Contains("VR"))) ) {      

            if (!data_found) {
                
             h_DATA = (TH1F*)h[i]->Clone("h_DATA");
             data_found = true;
                
            }
            
            else h_DATA->Add(h[i]);
            
        } //end it's data

        i++;
        file_it++;
        xsec_it++;
        
    }// end adding histograms
    
    //add 4tops to tt+X in order for it not to appear in the stack. Will then plot scaled signal in the canvas as a separate histogram
    h_ttX->Add(h_signal); 
    
    if (CAT == "1tau0L") {
        
        h_QCD->Scale(FR_yield[YEAR]/h_QCD->Integral(-1,-1));
        cout << "QCD histogram has been scaled to expected yield from fake rate method" << endl;
        
    }
    
    TFile * inputDATAfile;
    TH1F * h_QCD_DATA;
    
    if (CAT == "1tau0L_VR") {
        
        inputDATAfile = TFile::Open("/home/fabio/transition_factors/QCDshapes_corrected.root");
        h_QCD_DATA = (TH1F*)inputDATAfile->Get( "h_QCD_HT_VR_DATAcorrected" );
        h_QCD->Scale(12392/h_QCD->Integral(-1,-1));
        h_QCD_DATA->Scale(12392/h_QCD_DATA->Integral(-1,-1));
        cout << "QCD histogram has been taken from data" << endl;
        cout << "QCD histogram has been scaled to expected yield from fake rate method" << endl;
        
    }
    
    if (CAT == "1tau0L_SR") {
        
        inputDATAfile = TFile::Open("/home/fabio/transition_factors/QCDshapes_corrected.root");
        h_QCD_DATA = (TH1F*)inputDATAfile->Get( "h_QCD_HT_SR_DATAcorrected" );
        h_QCD->Scale(7679/h_QCD->Integral(-1,-1));
        h_QCD_DATA->Scale(7679/h_QCD_DATA->Integral(-1,-1));
        cout << "QCD histogram has been taken from data" << endl;
        cout << "QCD histogram has been scaled to expected yield from fake rate method" << endl;
        
    }
    
    
    //Translate data histogram to a TGraph. This is needed in order to plot it withouth x-error bars (i.e., binwidth) as prescribed by the CMS publication guidelines 
    //(https://twiki.cern.ch/twiki/bin/viewauth/CMS/Internal/PubGuidelines)
    TGraphAsymmErrors* gDATA;
    if ( !(VAR.Contains("jets_HT") && !(CAT.Contains("VR"))) ) {  //look at data
        
        Float_t px[h_DATA->GetSize() - 2];
        Float_t py[h_DATA->GetSize() - 2];
        Float_t exl[h_DATA->GetSize() - 2];
        Float_t exr[h_DATA->GetSize() - 2];
        Float_t eyl[h_DATA->GetSize() - 2];
        Float_t eyh[h_DATA->GetSize() - 2];
        
        for (int i = 0; i < h_DATA->GetSize() -2; i++) {

            px[i] = h_DATA->GetBinCenter(i+1);
            py[i] = h_DATA->GetBinContent(i+1);
            exl[i] = 0; //set x error to 0, see comment about CMS PUB guidelines
            exr[i] = 0; //set x error to 0, see comment about CMS PUB guidelines
            eyl[i] = h_DATA->GetBinError(i+1);
            eyh[i] = h_DATA->GetBinError(i+1);
        
        }
    
        gDATA = new TGraphAsymmErrors(h_DATA->GetSize() - 2, px, py, exl, exr, eyl, eyh); 
        gDATA->SetLineWidth(2);
        gDATA->SetMarkerColor(kBlack);

    }
    
    else {  //if you don't want to look at data, just fill TGraph with zeros
        
        Float_t px[h_DATA->GetSize() - 2];
        Float_t py[h_DATA->GetSize() - 2];
        Float_t exl[h_DATA->GetSize() - 2];
        Float_t exr[h_DATA->GetSize() - 2];
        Float_t eyl[h_DATA->GetSize() - 2];
        Float_t eyh[h_DATA->GetSize() - 2];
        
        for (int i = 0; i < h_DATA->GetSize() -2; i++) {

            px[i] = h_DATA->GetBinCenter(i+1);
            py[i] = 0;
            exl[i] = 0; //set x error to 0, see comment about CMS PUB guidelines
            exr[i] = 0; //set x error to 0, see comment about CMS PUB guidelines
            eyl[i] = h_DATA->GetBinError(i+1);
            eyh[i] = h_DATA->GetBinError(i+1);
        
        }
    
        gDATA = new TGraphAsymmErrors(h_DATA->GetSize() - 2, px, py, exl, exr, eyl, eyh); 
        gDATA->SetLineWidth(2);
        gDATA->SetMarkerColor(kBlack);

    }
    
    //scale signal to make it visible on the canvas
    TH1F * h_signal_scaled = (TH1F*)h_signal->Clone("h_signal_scaled");
    h_signal_scaled->Scale(SCALESIG);
    h_signal_scaled->SetLineWidth(2);
    h_signal_scaled->SetLineColor(kRed);
    h_signal_scaled->SetLineStyle(9);
    h_signal_scaled->SetMarkerSize(0);
    
    h_QCD->SetFillColor(kRed-3);
    if (CAT == "1tau0L_VR" || CAT == "1tau0L_SR") h_QCD_DATA->SetFillColor(kRed-3);
    h_ttbar->SetFillColor(kBlue-9);
    h_ttX->SetFillColor(kBlue-8);
    h_singleTop->SetFillColor(kBlue-5);
    //h_Higgs->SetFillColor(kOrange-3);
    
    //histogram for the sum of all background simulated processes
    TH1F *hBkg = (TH1F*)h_ttbar->Clone("hBkg");
    if (CAT == "1tau0L_VR" || CAT == "1tau0L_SR") hBkg->Add(h_QCD_DATA);
    else hBkg->Add(h_QCD);
    hBkg->Add(h_ttX);
    hBkg->Add(h_singleTop);
    //hBkg->Add(h_Higgs);
    
    //histogram to show the uncertainty on the sum of MC processes
    TH1F* htotal = (TH1F*)hBkg->Clone("htotal");
    htotal->SetLineWidth(1);
    htotal->SetFillColor(kGray+3);
    htotal->SetFillStyle(3013);
    htotal->SetMarkerSize(0);
    
    cout<<"======== "<<VAR+" "+CAT<<" ====================="<<endl;
    cout<<"Data events:  "<<h_DATA->Integral(-1,-1)<<endl;
    cout<<"signal events: "<<h_signal->Integral(-1,-1)<<endl;
    cout<<"ttbar events: "<<h_ttbar->Integral(-1,-1)<<endl;
    cout<<"QCD events: "<<h_QCD->Integral(-1,-1)<<endl;
    cout<<"tt+X events:   "<<h_ttX->Integral(-1,-1)<<endl;
    cout<<"single top events:   "<<h_singleTop->Integral(-1,-1)<<endl;
    //cout<<"single Higgs events: "<<h_Higgs->Integral(-1,-1) << endl;
    cout<<"total MC events: "<<hBkg->Integral(-1,-1)<<endl;
    cout<<"data/MC agreement: "<<(h_DATA->Integral(-1,-1) - hBkg->Integral(-1,-1))/hBkg->Integral(-1,-1) * 100.0 << "%" << endl;
    
    //stacked plot of all backgrounds
    THStack *hs = new THStack("hs","hs");
    if (LOG) {  
        
        //hs->Add(h_Higgs);
        if (CAT == "1tau0L_VR" || CAT == "1tau0L_SR") hs->Add(h_QCD_DATA);
        else hs->Add(h_QCD);
        hs->Add(h_singleTop);
        hs->Add(h_ttX);
        hs->Add(h_ttbar);
        
    }
    else {//reverse order if not log scale
    
        hs->Add(h_ttbar);
        if (CAT == "1tau0L_VR" || CAT == "1tau0L_SR") hs->Add(h_QCD_DATA);
        else hs->Add(h_QCD);
        hs->Add(h_ttX);
        hs->Add(h_singleTop);
        //hs->Add(h_Higgs);
        
    }
    
    //data/MC ratio histogram
    TH1F *hRatio;
    if ( !(VAR.Contains("jets_HT") && !(CAT.Contains("VR"))) ) hRatio = (TH1F*)h_DATA->Clone("Ratio");
    else hRatio = (TH1F*)hBkg->Clone("Ratio");
    hRatio->SetLineWidth(2);
    hRatio->Divide(hBkg);
    
    //translate it to a TGraph to comply with the CMS PUB guidelines (see comment above)
    Float_t Px[hRatio->GetSize() - 2];
    Float_t Py[hRatio->GetSize() - 2];
    Float_t Exl[hRatio->GetSize() - 2];
    Float_t Exr[hRatio->GetSize() - 2];
    Float_t Eyl[hRatio->GetSize() - 2];
    Float_t Eyh[hRatio->GetSize() - 2];
    
    for (int i = 0; i < hRatio->GetSize() - 2; i++) {
        
        Px[i] = hRatio->GetBinCenter(i+1);
        Py[i] = hRatio->GetBinContent(i+1);
        Exl[i] = 0;
        Exr[i] = 0;
        Eyl[i] = hRatio->GetBinError(i+1);
        Eyh[i] = hRatio->GetBinError(i+1);
        
    }
    
    TGraphAsymmErrors* gRatio = new TGraphAsymmErrors(hRatio->GetSize() - 2, Px, Py, Exl, Exr, Eyl, Eyh);
    gRatio->SetLineWidth(2);
    gRatio->SetMarkerColor(kBlack);
    
    TLegend *leg = new TLegend(0.86,0.5,0.99,0.9);
    if (CAT != "noC") leg->SetHeader(CAT);
    leg->SetFillColor(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.03);
    leg->AddEntry(gDATA,"2016 data","pe");
    std::string scale = to_string(SCALESIG);
    TString scalesig = scale;
    leg->AddEntry(h_signal_scaled,"t#bar{t}t#bar{t} x "+scalesig,"l");
    if (CAT == "1tau0L_VR") leg->AddEntry(h_QCD_DATA,"QCD","F");
    else leg->AddEntry(h_QCD,"QCD","F");
    leg->AddEntry(h_ttbar,"t#bar{t}","F");
    leg->AddEntry(h_ttX,"t#bar{t}+X","F");
    leg->AddEntry(h_singleTop,"Single Top","F");
    //leg->AddEntry(h_Higgs,"Single Higgs","F");
    leg->AddEntry(htotal, "stat. unc.", "F");
    
    can->SetBottomMargin(0.25);
    TH1F *hAux;
    if ( !(VAR.Contains("jets_HT") && !(CAT.Contains("VR"))) ) hAux= (TH1F*)h_DATA->Clone("aux");
    else hAux= (TH1F*)hBkg->Clone("aux");
    hAux->Reset();
    hAux->GetXaxis()->SetNdivisions(XNDIV);
    if (isINT) {
        hAux->GetXaxis()->CenterLabels();
    } 
    hAux->GetYaxis()->SetRangeUser(0.5,1.1*TMath::Max(hBkg->GetBinContent(hBkg->GetMaximumBin()),h_DATA->GetBinContent(h_DATA->GetMaximumBin())));  
    if (LOG) {
        gPad->SetLogy(); 
        hAux->GetYaxis()->SetRangeUser(0.5,2*TMath::Max(hBkg->GetBinContent(hBkg->GetMaximumBin()),h_DATA->GetBinContent(h_DATA->GetMaximumBin())));
    }
    hAux->GetXaxis()->SetRangeUser(XMIN,XMAX);
    //make sure that a proper maximum is set in the canvas so all the histograms are visible
    float max = std::max(hBkg->GetMaximum(), h_DATA->GetMaximum());
    hAux->SetMaximum(1.3*max);
    hAux->SetMinimum(0.1);
    hAux->GetYaxis()->SetTitle(TString::Format("Number of events / %1.2f fb^{-1}",lumi[YEAR]/1000));
    hAux->GetXaxis()->SetTitle("");
    hAux->GetXaxis()->SetLabelSize(0.0);
    hAux->Draw();
    hs->Draw("hist same");
    htotal->Draw("same E2");
    h_DATA->SetLineWidth(0);
    h_DATA->SetMarkerSize(0);
    if ( !(VAR.Contains("jets_HT") && !(CAT.Contains("VR"))) ) gDATA->Draw("same p");
    h_signal_scaled->Draw("hist same");
    
    leg->Draw();
    gPad->RedrawAxis();
    
    //histogram for relative uncertainty on total MC yield
    TH1F * hunc = new TH1F("hunc"+VAR+CAT, "hunc"+VAR+CAT, hBkg->GetSize() - 2, hBkg->GetXaxis()->GetXmin(), hBkg->GetXaxis()->GetXmax());
    hunc->SetLineWidth(0);
    hunc->SetFillColor(kGray+3);
    hunc->SetFillStyle(3013);
    hunc->SetMarkerSize(0);
    
    for (int i = 0; i < hunc->GetSize() - 2; i++) {
        hunc->SetBinContent(i+1, 1);
        if (hBkg->GetBinContent(i+1) > 0) hunc->SetBinError(i+1, htotal->GetBinError(i+1)/hBkg->GetBinContent(i+1));
        else hunc->SetBinError(i+1, 0);
    }
    
    TPad *pad = new TPad("pad","pad",0.,0.,1.,1.);
    pad->SetTopMargin(0.77);
    pad->SetRightMargin(0.15);
    pad->SetFillColor(0);
    pad->SetFillStyle(0);
    pad->Draw();
    pad->cd(0);
    pad->SetGridy();
    
    //empty histogram to help drawing the TGraph
    TH1F * h_empty = new TH1F("h_empty"+VAR+CAT, "h_empty"+VAR+CAT, hRatio->GetSize() - 2, hRatio->GetXaxis()->GetXmin(), hRatio->GetXaxis()->GetXmax());
    h_empty->GetXaxis()->SetTitleOffset(0.95);
    h_empty->GetYaxis()->SetTitleOffset(1.5);
    h_empty->GetYaxis()->SetTickLength(0.06);
    h_empty->GetYaxis()->SetTitleSize(0.03);
    h_empty->GetYaxis()->SetLabelSize(0.04);
    h_empty->GetYaxis()->SetTitle("data/MC");
    h_empty->GetXaxis()->SetTitle(XTITLE);
    h_empty->GetXaxis()->SetRangeUser(XMIN,XMAX);
    h_empty->GetYaxis()->SetRangeUser(0.4,1.6);
    h_empty->GetYaxis()->SetNdivisions(505);
    h_empty->GetXaxis()->SetNdivisions(XNDIV);
    if (isINT) {
        h_empty->GetXaxis()->CenterLabels();
    }

    h_empty->Draw();
    gRatio->Draw("same p");
    hunc->Draw("same E2");
    gPad->Update();
    
    CMS_lumi(can, 4, 0);

    
    if (PRINT) {//save plots
        can->SaveAs("plots/"+TString(YEAR)+"/"+CAT+"/"+VAR+"_"+CAT+".pdf"); 
    }
    
    
    for (int i = 0; i < file.size(); i++) delete h[i];
    
}
