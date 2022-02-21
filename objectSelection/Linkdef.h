#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// includes all headrefiles
#include "TLorentzVector.h"
#include <vector>
#include "objectTSelectorForNanoAOD.h"
#include "utilityFunctions.h"
#include "../TauPOG/TauIDSFs/interface/TauIDSFTool.h"

// All classes
#pragma link C++ class vector<TLorentzVector>+;
#pragma link C++ class objectTSelectorForNanoAOD+;
// #pragma link C++ class utilityFunctions+;
#pragma link C++ function utilityFunctions+;
#pragma link C++ class TauIDSFTool+; 


#endif