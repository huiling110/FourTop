#include "printPurity.h"

void printPurity(string cat) {

  const int N = 3;

  float S[N] = {0.0, 0.0, 0.0};
  float B[N] = {0.0, 0.0, 0.0};
  float P[N] = {0.0, 0.0, 0.0};

  TString inputfile[N] = {

    "Histograms.root",
    "Histograms_3bjets.root",
    "Histograms_4bjets.root",

  };


  for (int i = 0; i < N; i++) {//loop over files
    
    TFile * inf;
    cout << "Opening file " << inputfile[i] << "..." << endl;
    inf = TFile::Open(inputfile[i]);
  
  //scale the histograms for all the processes to the 2016 luminosity
  map<string, float>::iterator xsec_it = xsec.begin();
  while (xsec_it != xsec.end()) {
    TH1D* genEvts = (TH1D*)inf->Get( (xsec_it->first + "_GenEventWeight").c_str() );
    TH1F* h = (TH1F*)inf->Get( (xsec_it->first + "_" + cat).c_str() );
    h->Scale(xsec_it->second * LUMI2016 / genEvts->GetSumOfWeights());
    scaledYield.insert( {xsec_it->first, *h} );
    //cout << xsec_it->first << endl;
    delete h;
    xsec_it++;
  }

  tttt = scaledYield["tttt"];
  
  tt = scaledYield["tt"];
 
  ttX = scaledYield["ttG+jets"];
  ttX.Add(&scaledYield["ttW+jets"]);
  ttX.Add(&scaledYield["ttZ+jets"]);
  ttX.Add(&scaledYield["ttH"]);

  VV = scaledYield["WZ"];
  VV.Add(&scaledYield["WWTo2L2Nu"]);
  VV.Add(&scaledYield["WpWpJJ"]);
  VV.Add(&scaledYield["ZZ"]);
  VV.Add(&scaledYield["WG+jets"]);
  VV.Add(&scaledYield["ZG+jets"]);

  VVV = scaledYield["WWW"];
  VVV.Add(&scaledYield["WWZ"]);
  VVV.Add(&scaledYield["WWG"]);
  VVV.Add(&scaledYield["ZZZ"]);
  VVV.Add(&scaledYield["WZG"]);
  VVV.Add(&scaledYield["WGG"]);
  VVV.Add(&scaledYield["ZGG+jets"]);

  WJets = scaledYield["W+jets"];

  DY = scaledYield["DY"];

  ST = scaledYield["tZq"];
  ST.Add(&scaledYield["tW_antitop"]);
  ST.Add(&scaledYield["tW_top"]);
  ST.Add(&scaledYield["tG+jets"]);
  ST.Add(&scaledYield["tHW"]);
  ST.Add(&scaledYield["THq"]);

  H = scaledYield["VHToNonbb"];
  H.Add(&scaledYield["ZHToTauTau"]);
  H.Add(&scaledYield["ZHTobb"]);
  H.Add(&scaledYield["GluGluHTo4L"]);
  H.Add(&scaledYield["GluGluHTobb"]);
  H.Add(&scaledYield["GluGluHToGG"]);
  H.Add(&scaledYield["GluGluHToMuMu"]);
  H.Add(&scaledYield["GluGluHToTauTau"]);
  H.Add(&scaledYield["GluGluHTo2L2Nu"]);
  H.Add(&scaledYield["GluGluHToLNuqq"]);
  H.Add(&scaledYield["VBFHTo2L2Nu"]);
  H.Add(&scaledYield["VBFHToMuMu"]);
  H.Add(&scaledYield["VBFHToGG"]);
  

  total_bkg = tt;
  total_bkg.Add(&ttX);
  total_bkg.Add(&VV);
  total_bkg.Add(&VVV);
  total_bkg.Add(&WJets);
  total_bkg.Add(&DY);
  total_bkg.Add(&ST);
  total_bkg.Add(&H);

  S[i] = tttt.Integral();
  B[i] = total_bkg.Integral();
  P[i] = tttt.Integral()/(tttt.Integral() + total_bkg.Integral());
  
  scaledYield.clear();
  inf->Close();
  delete inf;
  
  }//end loop over files
  cout << " " << endl;
  cout << "~~~ Evolution of purity with number of b jets for category " << cat << " ~~~" << endl;
  cout << " " << endl;
  cout << setw(12) << left << "" << setw(12) << left << "2 b tagged" << setw(12) << left << "2 3 tagged" << setw(12) << left << "4 b tagged" << endl;
  cout << setw(12) << left << "S" << setw(12) << left << S[0] << setw(12) << left << S[1] << setw(12) << left << S[2] << endl;
  cout << setw(12) << left << "B" << setw(12) << left << B[0] << setw(12) << left << B[1] << setw(12) << left << B[2] << endl;
  cout << setw(12) << left << "S/(S+B)" << setw(12) << left << P[0] << setw(12) << left << P[1] << setw(12) << left << P[2] << endl;


}
