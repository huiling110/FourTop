#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// includes all headrefiles
#include "TLorentzVector.h"
#include <vector>
#include "makeVaribles_forBDT.h"
#include "variablesFunctions.h"

// All classes
// #pragma link C++ class vector<TLorentzVector>+;
#pragma link C++ class vector < ROOT::Math::PtEtaPhiMVector> + ;
#pragma link C++ class makeVaribles_forBDT+;
// #pragma link C++ function utilityFunctions+;
// #pragma link C++ class TauIDSFTool+; 


#endif