#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include "leptonRecoEff.h"

void leptonRecoEff() {

gBenchmark->Start("running time");

map<string, string>::iterator file_it = file.begin();

while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

  cout << "Opening file " << file_it->second << "..." << endl;
  TFile *inputfile  = new TFile( file_it->second.c_str(), "READ" );

  file_it++;

}


}
