#include "printYields_v2.h"

void printYields_v2(string cat) {

  TFile *inputfile  = new TFile( "Histograms_4bjets.root", "READ" );
  
  //scale the histograms for all the processes to the 2016 luminosity
  map<string, float>::iterator xsec_it = xsec.begin();
  while (xsec_it != xsec.end()) {
    TH1D* genEvts = (TH1D*)inputfile->Get( (xsec_it->first + "_GenEventWeight").c_str() );
    TH1F* h = (TH1F*)inputfile->Get( (xsec_it->first + "_" + cat).c_str() );
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
  //cout << "0" << endl;
  total_bkg.Add(&ttX);
  //cout << "1" << endl;
  total_bkg.Add(&VV);
  //cout << "2" << endl;
  total_bkg.Add(&VVV);
  //cout << "3" << endl;
  total_bkg.Add(&WJets);
  //cout << "4" << endl;
  total_bkg.Add(&DY);
  //cout << "5" << endl;
  total_bkg.Add(&ST);
  //cout << "6" << endl;
  total_bkg.Add(&H);
  //cout << "7" << endl;

  cout << " " << endl << " ~~~ 2016 expected yields for category " + cat +" ~~~" << endl << " " << endl;
  cout << setw(12) << left << "tttt =" << setw(12) << left << tttt.Integral() << endl;
  cout << setw(12) << left << "tt =" << setw(12) << left << tt.Integral() << endl;
  cout << setw(12) << left << "ttX =" << setw(12) << left << ttX.Integral() << endl;
  cout << setw(12) << left << "VV =" << setw(12) << left << VV.Integral() << endl;
  cout << setw(12) << left << "VVV =" << setw(12) << left << VVV.Integral() << endl;
  cout << setw(12) << left << "WJets =" << setw(12) << left << WJets.Integral() << endl;
  cout << setw(12) << left << "DY =" << setw(12) << left << DY.Integral() << endl;
  cout << setw(12) << left << "ST =" << setw(12) << left << ST.Integral() << endl;
  cout << setw(12) << left << "H =" << setw(12) << left << H.Integral() << endl;
  cout << setw(12) << left << "total bkg =" << setw(12) << left << total_bkg.Integral() << endl;
  cout << " " << endl;

  cout << " " << endl << " ~~~ 2016 expected statistics for category " + cat +" ~~~" << endl << " " << endl;
  cout << setw(12) << left << "tttt =" << setw(12) << left << tttt.GetEntries() << endl;
  cout << setw(12) << left << "tt =" << setw(12) << left << tt.GetEntries() << endl;
  cout << setw(12) << left << "ttX =" << setw(12) << left << ttX.GetEntries() << endl;
  cout << setw(12) << left << "VV =" << setw(12) << left << VV.GetEntries() << endl;
  cout << setw(12) << left << "VVV =" << setw(12) << left << VVV.GetEntries() << endl;
  cout << setw(12) << left << "WJets =" << setw(12) << left << WJets.GetEntries() << endl;
  cout << setw(12) << left << "DY =" << setw(12) << left << DY.GetEntries() << endl;
  cout << setw(12) << left << "ST =" << setw(12) << left << ST.GetEntries() << endl;
  cout << setw(12) << left << "H =" << setw(12) << left << H.GetEntries() << endl;
  cout << setw(12) << left << "total bkg =" << setw(12) << left << total_bkg.GetEntries() << endl;
  cout << " " << endl;
}

 
