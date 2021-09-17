//Compute shifted TFs taking into account the correlation matrix between the fitted parameters. 1st step: diagonalize the covariance matrix to put ourselves in an auxiliary space in which the parameters are uncorrelated; 2nd step: shift all the parameters up (down) to obtain the up (down) TF in this auxiliary space; 3rd step: move back to the real parameter space using the matrix that diagonalize the covariance matrix to take into account correlation

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <TLatex.h>
#include <TStyle.h>
#include <sstream>
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include <Math/Math.h>
#include <TLorentzVector.h>
#include <Math/Vector3D.h>
#include <Math/DisplacementVector3D.h>
#include <Math/Vector3Dfwd.h>
#include <TBenchmark.h>
#include <TMatrixDSymEigen.h>

#include <iostream>

#define loosetag 0.5426
#define mediumtag 0.8484


using namespace std;

void doCalculations (TString input, TString CAT) {

cout << "~~~~~~~ COMPUTING SHIFTS FOR " << CAT << " ~~~~~~~" << endl;
    
TFile *inputfile  = new TFile( input, "READ" );
//get covariance matrix from input file
TMatrixDSym* cov = (TMatrixDSym*)inputfile->Get("CovarianceMatrix"+CAT);
//get transition function from input file
TF1 *TransitionFunction= (TF1*)inputfile->Get("TransitionFunction"+CAT);
cov->Print("CovarianceMatrix"+CAT);

//FIND EIGENVALUES AND EIGENVECTORS OF THE COVARIANCE MATRIX
TMatrixD eigvec(cov->GetNrows(),cov->GetNcols());
TVectorD eigval(cov->GetNrows());
//initialize a TMatrixDSymEigen object used to compute eigenvectors and eigenvalues
TMatrixDSymEigen eigen(*cov);
//use it to get the TMatrixD of eigenvectors (i.e. the diagonalizing matrix)
eigvec = eigen.GetEigenVectors();
//eigvec.Print("diagonalizing matrix");
//use it also to obtain the eigenvalues, stored in a TVectorD
eigval = eigen.GetEigenValues();
//transpose the diagonalizing matrix
TMatrixD eigvecT(TMatrixD::kTransposed,eigvec);
//DIAGONALIZE THE COVARIACE MATRIX
TMatrixD B(cov->GetNrows(),cov->GetNcols());
B.Mult(eigvecT, *cov);
TMatrixD D(cov->GetNrows(),cov->GetNcols());
D.Mult(B,eigvec); //as you can verify by printing, the matrix D is diagonal and has the eigenvalues as diagonal elements
D.Print("diagonalized matrix");
//COMPUTE THE PARAMETERS IN THE AUXILIARY SPACE
TVectorD realParameters(cov->GetNrows());
for (int i = 0; i < cov->GetNrows(); i++) {
    
    realParameters(i) = TransitionFunction->GetParameter(i);
    
}

TVectorD auxiliaryParameters(cov->GetNrows());
auxiliaryParameters = eigvec * realParameters;
realParameters.Print("realParameters");
//auxiliaryParameters.Print("auxiliaryParameters");

//now use the inverse of the transformation matrix to obtain the shifted parameters in the real parameter space starting from the ones shifted up and down in the auxiliary space
//since the covariance matrix in the auxiliary space has the eigenvalues as diagonal elements, the variances of the auxiliary parameters are simply the eigenvalues

TVectorD shiftedUpAuxiliaryParameters(cov->GetNrows());
TVectorD shiftedDownAuxiliaryParameters(cov->GetNrows());
for (int i = 0; i < cov->GetNrows(); i++) {
    
    shiftedUpAuxiliaryParameters(i) = auxiliaryParameters(i) + sqrt(eigval(i));
    shiftedDownAuxiliaryParameters(i) = auxiliaryParameters(i) - sqrt(eigval(i));
    
}
//shiftedUpAuxiliaryParameters.Print("shiftedUpAuxiliaryParameters");
//invert the transformation matrix
TMatrixD inverseEigvec(cov->GetNrows(),cov->GetNcols());
inverseEigvec = eigvec.Invert();

TVectorD shiftedUpRealParameters(cov->GetNrows());
TVectorD shiftedDownRealParameters(cov->GetNrows());
shiftedUpRealParameters = inverseEigvec*shiftedUpAuxiliaryParameters;
shiftedDownRealParameters = inverseEigvec*shiftedDownAuxiliaryParameters;

shiftedUpRealParameters.Print("shiftedUpRealParameters");
shiftedDownRealParameters.Print("shiftedDownRealParameters");

TF1 *TransitionFunctionUp = (TF1*)TransitionFunction->Clone();
TF1 *TransitionFunctionDown = (TF1*)TransitionFunction->Clone();

for (int i = 0; i < cov->GetNrows(); i++) {
    
    TransitionFunctionUp->SetParameter(i, shiftedUpRealParameters(i));    
    TransitionFunctionDown->SetParameter(i, shiftedDownRealParameters(i));
}


TFile *outputfile = new TFile( "QCDshiftedTransitionfunctions.root", "UPDATE" );
TransitionFunction->Write("TransitionFunction"+CAT+"nominal");
TransitionFunctionUp->Write("TransitionFunction"+CAT+"Up");
TransitionFunctionDown->Write("TransitionFunction"+CAT+"Down");

outputfile->Close();
delete outputfile;

delete TransitionFunction;
delete TransitionFunctionUp;
delete TransitionFunctionDown;
inputfile->Close();
delete inputfile;

    
}





void computeShiftedTFs () {

gBenchmark->Start("running time");

 doCalculations("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/fabio/fake_rate/QCDTransitionFunctions.root", "VR");
 doCalculations("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/fabio/fake_rate/QCDTransitionFunctions.root", "SR");
 
gBenchmark->Show("running time");



}
         
