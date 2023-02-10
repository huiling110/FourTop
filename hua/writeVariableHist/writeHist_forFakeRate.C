#define writeHist_forFakeRate_cxx
// The class definition in writeHist_forFakeRate.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived

#include <TH2.h>
#include <TStyle.h>

#include <assert.h>
#include <cmath>
// #include <filesystem>

#include "../src_cpp/lumiAndCrossSection.h"
#include "../src_cpp/usefulFuction.h"
#include "writeHist_forFakeRate.h"

void writeHist_forFakeRate::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
	if (isRegion)
	{
		eventCount_hists[vectorIndex]->Fill(.0, weight);
	}
}

template <typename T>
void FillHistsVecorMyClassGenearal(Bool_t isRegion, UInt_t vectorIndex, Double_t weight, std::vector<histsForRegions<T>> &vectorOfVariableRegionsDouble)
{
	for (UInt_t i = 0; i < vectorOfVariableRegionsDouble.size(); i++)
	{
		vectorOfVariableRegionsDouble[i].fillHistVec(vectorIndex, weight, isRegion);
	}
}

void push_backHists(TString variable, Int_t binNum, Double_t minBin, Double_t maxBin, std::vector<TH1D *> &histsVariable, TString m_processName, std::vector<TString> &regions)
{
	for (UInt_t i = 0; i < regions.size(); i++)
	{
		TString iHistName = regions[i] + "_" + m_processName + "_" + variable;
		TH1D *temp = new TH1D(iHistName.Data(), iHistName.Data(), binNum, minBin, maxBin);
		histsVariable.push_back(temp);
	}
}

Double_t calFRWeight(const Double_t taus_1pt, const Double_t taus_1eta, const Double_t taus_1prongNum, TH2D *FR_TH2D_1prong, TH2D *FR_TH2D_3prong, Double_t &FRWeight_up, Double_t &FRWeight_down)
{
	// might need error handling for this
	// Double_t FRWeight = 1.0; // the defaul t value for FRWeight should not be 1!!!
	// set the default FRWeight to the last bin
	TH2D *FR_TH2D;
	if (taus_1prongNum == 1)
	{
		FR_TH2D = FR_TH2D_1prong;
	}
	else
	{
		FR_TH2D = FR_TH2D_3prong;
	}
	Int_t binxNum = FR_TH2D->GetNbinsX();
	Int_t binyNum = FR_TH2D->GetNbinsY();
	Double_t FR = FR_TH2D->GetBinContent(binxNum, binyNum);
	Double_t FR_sigma = FR_TH2D->GetBinError(binxNum, binyNum);
	if (taus_1pt > 20.0 && taus_1pt <= 300.0)
	{

		Int_t binx = FR_TH2D->GetXaxis()->FindBin(taus_1pt);
		Int_t biny = FR_TH2D->GetYaxis()->FindBin(std::abs(taus_1eta)); // FineBin: If x is underflow or overflow, attempt to extend the axis if TAxis::kCanExtend is true. Otherwise, return 0 or fNbins+1.
		FR = FR_TH2D->GetBinContent(binx, biny);						// not clear for underflow or overflow bin which binContent retrieves from ROOT documentation
		FR_sigma = FR_TH2D->GetBinError(binx, biny);
		//???need better error handling
		// if (FR < 0.000001)
		// {
		// std::cout << "taupt=" << taus_1pt << "; tauEta=" << taus_1eta << "\n";
		// std::exit(1);
		// }
	}
	Double_t FRWeight = FR / (1 - FR);
	FRWeight_up = FRWeight + FR_sigma / std::pow((1 - FR), 2);
	FRWeight_down = FRWeight - FR_sigma / std::pow((1 - FR), 2);
	return FRWeight;
}

template <typename TEM>
void vectorInitializeReigions(std::vector<histsForRegions<TEM>> &vectorOfVariableRegionsDouble, std::vector<TString> &regionsForEventCount, TString m_processName)
{
	for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegionsDouble.size(); ihistvec++)
	{
		vectorOfVariableRegionsDouble[ihistvec].initializeRegions(regionsForEventCount, m_processName);
	}
};

template <typename TEMP>
void scaleVectorHistRegions(std::vector<histsForRegions<TEMP>> &vectorOfVariableRegionsDouble, Double_t scale)
{
	for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegionsDouble.size(); ihistvec++)
	{
		vectorOfVariableRegionsDouble[ihistvec].histsScale(scale);
	}
};

void writeHist_forFakeRate::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
}

void writeHist_forFakeRate::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	std::cout << "option in writeHist_forFakeRate: " << option << "\n";

	// this part could be in a function for multiple uses
	// better structure my project so that these commen functionality go to one include dir
	std::vector<TString> optionVect;
	getOption(option, optionVect);
	m_genWeightSum = std::stod(optionVect[0].Data());
	std::cout << "m_genWeightSum: " << m_genWeightSum << "\n";
	//???maybe there is lose of accuracy due to convertion
	m_outputFolder = optionVect[1];
	m_processName = optionVect[2];
	m_isData = std::stoi(optionVect[3].Data());
	std::cout << "m_isData: " << m_isData << "\n";
	m_version = optionVect[4];
	std::cout << "m_verion: " << m_version << "\n";
	m_era = optionVect[5];
	std::cout << "m_era: " << m_era << "\n";

	outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + ".root", "RECREATE");

	std::vector<TString> regionsForEventCount = {
		"1tau0lSR", // 0
		"1tau0lCR",
		"1tau0lCRLTau",
		"1tau0lVR", // 3
		"1tau0lVRLTau",
		"1tau0lVRLTauNotT", // 5
		"1tau0lSRGen",
		"1tau0lCRGen",
		"1tau0lCRLTauGen",
		"1tau0lVRGen",	   // 9
		"1tau0lVRLTauGen", // 10
		"1tau0lVRLTauNotTGen",
		"1tau0lCRNotGen", // 12
		"1tau0lVRNotGen",
		// FR CRc and CRa and CR3
		"1tau0lCRc", // 14
		"1tau0lCRa",
		"1tau0lCRb",
		// for fakeTau estimation
		"1tau0lCRcGen", // 17
		"1tau0lCRaGen",
		"1tau0lCRbGen",
		"1tau0lCRcLTauNotT_Weighted", // 20
		"1tau0lCRcLTauNotTGen_Weighted",
		"1tau0lCRaLTauNotT_Weighted", // 22
		"1tau0lCRaLTauNotTGen_Weighted",
		"1tau0lCRbLTauNotT_Weighted", // 24
		"1tau0lCRbLTauNotTGen_Weighted",
		//
		"1tau0lSRLTauNotT_Weighted", // 26
		"1tau0lSRLTauNotTGen_Weighted",
		"1tau0lCRLTauNotT_Weighted", // 28
		"1tau0lCRLTauNotTGen_Weighted",
		"1tau0lVRLTauNotT_Weighted", // 30
		"1tau0lVRLTauNotTGen_Weighted",

	};
	push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsForEventCount);

	// FR weighted
	//???make this not vector index but clear name for regions
	std::vector<TString> regionsForFRWeighting = {
		// regions nessary for plotting data/MC
		"1tau0lCR", // 0
		"1tau0lCRGen",
		"1tau0lCRNotGen", // 2
		// for FakeRate weighting
		"1tau0lVRLTauNotT_Weighted",	// 3
		"1tau0lCRLTauNotT_Weighted",	// 4
		"1tau0lVRLTauNotTGen_Weighted", // 5
		"1tau0lCRLTauNotTGen_Weighted", // 6
		//
		"1tau0lVR", // 7
		"1tau0lVRGen",
		"1tau0lVRNotGen",
		//
		"1tau0lSR", // 10
		"1tau0lSRGen",
		"1tau0lSRNotGen",
		"1tau0lSRLTauNotT_Weighted",	// 13
		"1tau0lSRLTauNotTGen_Weighted", // 14
		// FR uncertainty variation
		"1tau0lCRLTauNotT_Weighted_up",		 // 15
		"1tau0lCRLTauNotT_Weighted_down",	 // 16
		"1tau0lCRLTauNotTGen_Weighted_up",	 //
		"1tau0lCRLTauNotTGen_Weighted_down", //
		"1tau0lVRLTauNotT_Weighted_up",		 // 19
		"1tau0lVRLTauNotT_Weighted_down",	 //
		"1tau0lVRLTauNotTGen_Weighted_up",	 //
		"1tau0lVRLTauNotTGen_Weighted_down", //
		"1tau0lSRLTauNotT_Weighted_up",		 // 23
		"1tau0lSRLTauNotT_Weighted_down",	 // 24
		"1tau0lSRLTauNotTGen_Weighted_up",	 // 25
		"1tau0lSRLTauNotTGen_Weighted_down", // 26
		//
		"1tau0lCRc", // 27
		"1tau0lCRcGen",
		"1tau0lCRcLTauNotT_Weighted",	 // 29
		"1tau0lCRcLTauNotTGen_Weighted", // 30

	};
	// systematic regions
	// how the pileup weighting impact?, only impact MC, don't concern fake tau
	histsForRegions<Double_t> jets_HT_class{"jets_HT", "HT of jets", 30, 500, 1500, jets_HT};
	histsForRegions<Double_t> jets_bScore_class{"jets_bScore", "b score sum of jets", 30, 1, 5, jets_bScore};
	histsForRegions<Double_t> jets_1pt_class{"jets_1pt", "leading jet pt", 10, 40, 500, jets_1pt};
	histsForRegions<Double_t> jets_2pt_class{"jets_2pt", "second jet pt", 10, 40, 600, jets_2pt};
	histsForRegions<Double_t> jets_3pt_class{"jets_3pt", "third jet pt", 10, 40, 500, jets_3pt};
	histsForRegions<Double_t> jets_4pt_class{"jets_4pt", "fourth jet pt", 10, 40, 300, jets_4pt};
	histsForRegions<Double_t> jets_5pt_class{"jets_5pt", "fifth jet pt", 10, 40, 250, jets_5pt};
	histsForRegions<Double_t> jets_6pt_class{"jets_6pt", "sixth jet pt", 10, 40, 180, jets_6pt};
	histsForRegions<Double_t> jets_bScoreMultiply_class{"jets_bScoreMultiply", "square root of b score multiplicity", 30, 0, 1, jets_bScoreMultiply};
	histsForRegions<Double_t> jets_4largestBscoreSum_class{"jets_4largestBscoreSum", "sum of 4 largest jets b score", 30, 0.6, 4, jets_4largestBscoreSum};
	histsForRegions<Double_t> jets_4largestBscoreMulti_class{"jets_4largestBscoreMulti", "jets_4largestBscoreMulti", 30, 0, 1, jets_4largestBscoreMulti};
	histsForRegions<Double_t> bjetsM_invariantMass_class{"bjetsM_invariantMass", "invariantMass of b jets", 30, 0, 800, bjetsM_invariantMass};
	histsForRegions<Double_t> bjetsM_1pt_class{"bjetsM_1pt", "leading b jet pt", 10, 25, 300, bjetsM_1pt};
	histsForRegions<Double_t> tausT_1pt_class{"tausT_1pt", "leading tight tau pt", 20, 20, 200, tausT_1pt};
	histsForRegions<Double_t> tausL_1ptFR_class{"tausL_1ptFRWeight", "leading loose tau pt", 28, 20, 300, tausL_1pt};
	histsForRegions<Double_t> tausL_1etaAbsFR_class{"tausL_1etaAbsFRWeight", "leading fake tau #eta", 10, 0, 2.3, tausL_1etaAbs};
	// histsForRegions<Double_t> Met_pt_class{"MET_pt", "Met", 10, 0, 200, MET_pt};
	histsForRegions<Double_t> tausF_1jetPtFR_class{"tausF_1jetPtFRWeight", "leading pt of mother jet of fake tau", 28, 20, 300, tausF_1jetPt};
	// histsForRegions<Double_t>{};
	histsForRegions<Int_t> tausF_prongNum_class{"tausF_prongNum", "number of prongs of tau", 3, 1, 4, tausF_prongNum};
	histsForRegions<Int_t> tausF_charge_class{"tausF_charge", "charge of leading tau", 2, -2, 2, tausF_1charge};
	histsForRegions<Int_t> tausF_1decayMode_class{"tausF_1decayMode", "decay mode of leading fake tau", 11, 0, 11, tausF_1decayMode};
	histsForRegions<Int_t> jets_num_class{"jets_num", "number of jets", 6, 6, 12, jets_number};
	histsForRegions<Int_t> bjetsM_num_class{"bjetsM_num", "number of bjets", 5, 0, 5, bjetsM_num};
	histsForRegions<Int_t> PV_npvs_class{"PV_npvs", "number of primary vertex", 50, 0, 50, PV_npvs};
	vectorOfVariblesRegions_FRweighted.clear();
	vectorOfVariblesRegions_FRweighted.push_back(jets_HT_class); //!!!no need to scale to lumilosity! only data regions!
	vectorOfVariblesRegions_FRweighted.push_back(jets_1pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_2pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_3pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_4pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_5pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_6pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(bjetsM_1pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(tausT_1pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(tausL_1ptFR_class);
	vectorOfVariblesRegions_FRweighted.push_back(tausL_1etaAbsFR_class);
	// vectorOfVariblesRegions_FRweighted.push_back(Met_pt_class);
	vectorOfVariblesRegions_FRweighted.push_back(tausF_1jetPtFR_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_bScore_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_bScoreMultiply_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_4largestBscoreSum_class);
	vectorOfVariblesRegions_FRweighted.push_back(jets_4largestBscoreMulti_class);
	vectorOfVariblesRegions_FRweighted.push_back(bjetsM_invariantMass_class);
	// vectorOfVariblesRegions_FRweighted.push_back();
	vectorOfVariblesRegions_FRweightedInt.clear();
	vectorOfVariblesRegions_FRweightedInt.push_back(tausF_prongNum_class); //!!!no need to scale to lumilosity! only data regions!
	vectorOfVariblesRegions_FRweightedInt.push_back(jets_num_class);
	vectorOfVariblesRegions_FRweightedInt.push_back(bjetsM_num_class);
	vectorOfVariblesRegions_FRweightedInt.push_back(tausF_charge_class);
	vectorOfVariblesRegions_FRweightedInt.push_back(tausF_1decayMode_class);
	vectorOfVariblesRegions_FRweightedInt.push_back(PV_npvs_class);
	// vectorOfVariblesRegions_FRweightedInt.push_back();
	vectorInitializeReigions(vectorOfVariblesRegions_FRweighted, regionsForFRWeighting, m_processName);
	vectorInitializeReigions(vectorOfVariblesRegions_FRweightedInt, regionsForFRWeighting, m_processName);

	std::vector<TString> regionsEtaDivided = {
		"1tau0lCRLTau_Eta1",
		"1tau0lCRLTau_Eta2",
		"1tau0lCRLTau_Eta3",
		"1tau0lCRLTauGen_Eta1",
		"1tau0lCRLTauGen_Eta2",
		"1tau0lCRLTauGen_Eta3",

		"1tau0lCR_Eta1", // 6
		"1tau0lCR_Eta2",
		"1tau0lCR_Eta3",
		"1tau0lCRGen_Eta1", // 9
		"1tau0lCRGen_Eta2",
		"1tau0lCRGen_Eta3",

		"1tau0lVRLTauNotT_Eta1", // 12
		"1tau0lVRLTauNotT_Eta2",
		"1tau0lVRLTauNotT_Eta3",
		"1tau0lVRLTauNotTGen_Eta1",
		"1tau0lVRLTauNotTGen_Eta2",
		"1tau0lVRLTauNotTGen_Eta3",
		// CR LNotT
		"1tau0lCRLTauNotT_Eta1", // 18
		"1tau0lCRLTauNotT_Eta2",
		"1tau0lCRLTauNotT_Eta3",
		"1tau0lCRLTauNotTGen_Eta1", // 21
		"1tau0lCRLTauNotTGen_Eta2",
		"1tau0lCRLTauNotTGen_Eta3", // 23

		// FR measurment CRc and CRa
		"1tau0lCRcLTau_Eta1", // 24 2b
		"1tau0lCRcLTau_Eta2",
		"1tau0lCRcLTau_Eta3",
		"1tau0lCRcLTauGen_Eta1", // 27
		"1tau0lCRcLTauGen_Eta2",
		"1tau0lCRcLTauGen_Eta3",
		"1tau0lCRc_Eta1", // 30
		"1tau0lCRc_Eta2",
		"1tau0lCRc_Eta3",
		"1tau0lCRcGen_Eta1", // 33
		"1tau0lCRcGen_Eta2",
		"1tau0lCRcGen_Eta3",
		// CRa
		"1tau0lCRaLTau_Eta1", // 36
		"1tau0lCRaLTau_Eta2",
		"1tau0lCRaLTau_Eta3",
		"1tau0lCRaLTauGen_Eta1", // 39
		"1tau0lCRaLTauGen_Eta2",
		"1tau0lCRaLTauGen_Eta3",
		"1tau0lCRa_Eta1", // 42
		"1tau0lCRa_Eta2",
		"1tau0lCRa_Eta3",
		"1tau0lCRaGen_Eta1", // 45
		"1tau0lCRaGen_Eta2",
		"1tau0lCRaGen_Eta3",
		// CRb
		"1tau0lCRbLTau_Eta1", // 48
		"1tau0lCRbLTau_Eta2",
		"1tau0lCRbLTau_Eta3",
		"1tau0lCRbLTauGen_Eta1", // 51
		"1tau0lCRbLTauGen_Eta2",
		"1tau0lCRbLTauGen_Eta3",
		"1tau0lCRb_Eta1", // 54
		"1tau0lCRb_Eta2",
		"1tau0lCRb_Eta3",
		"1tau0lCRbGen_Eta1", // 57
		"1tau0lCRbGen_Eta2",
		"1tau0lCRbGen_Eta3",

	};
	tausL_1pt_eta_class.initializeRegions(regionsEtaDivided, m_processName);

	//
	std::map<TString, std::array<TString, 2>> FRfileMap = {
		{"2016", {"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v1forFREtaRegionCorrected_1prong/results/fakeRateInPtEta_sumGenBG_newBin.root", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v1forFREtaRegionCorrected_3prong/results/fakeRateInPtEta_sumGenBG_newBin.root"}},

		{"2018", {"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v1forFREtaRegionCorrected_1prong/results/fakeRateInPtEta_sumGenBG_newBin.root", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v1forFREtaRegionCorrected_3prong/results/fakeRateInPtEta_sumGenBG_newBin.root"}},

		{"2017", {"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v1forFREtaRegionCorrected_1prong/results/fakeRateInPtEta_sumGenBG_newBin.root", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v1forFREtaRegionCorrected_3prong/results/fakeRateInPtEta_sumGenBG_newBin.root"}},
	};
	TFile *FRFile = new TFile(FRfileMap[m_era].at(0).Data(), "READ");
	FR_hist = (TH2D *)FRFile->Get("fakeRate2D");
	TFile *FRFile_3prong = new TFile(FRfileMap[m_era].at(1).Data(), "READ");
	FR_hist_3prong = (TH2D *)FRFile_3prong->Get("fakeRate2D");
	printf("Reading FR file:%s \n", FRFile->GetName());
}

Bool_t writeHist_forFakeRate::Process(Long64_t entry)
{
	fReader.SetLocalEntry(entry);
	// baseline selection
	Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0;
	if (!baseline)
	{
		return kFALSE;
	}

	// swich to new SS lepton
	// Int_t lepNum = *elesTopMVAT_number + *muonsTopMVAT_number;
	// Int_t lepNum = *elesTopMVAL_number + *muonsTopMVAL_number;
	Int_t lepNum = *elesTopMVALPOG_number + *muonsTopMVALPOG_number;
	// leptonsMVAT_number
	if (!(*tausF_number == 1 && lepNum == 0))
	{
		return kFALSE;
	};

	// for prong division
	// if (!(*tausF_prongNum == 1))
	// if (!(*tausF_prongNum == 2 || *tausF_prongNum == 3))
	// {
	// 	return kFALSE;
	// }

	Double_t basicWeight = 1.0;
	if (!m_isData)
	{
		basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight);
	}

	Double_t FRWeight_up, FRWeight_down;
	Double_t FRWeight = 1.0;
	if (!m_ifMeasurement)
	{
		FRWeight = calFRWeight(*tausF_1jetPt, *tausF_1eta, *tausF_prongNum, FR_hist, FR_hist_3prong, FRWeight_up, FRWeight_down);
	}
	// std::cout << "FRWeight=" << FRWeight << "; FR_up=" << FRWeight_up << " FR_down=" << FRWeight_down << "\n";

	Bool_t isTauLNum = (*tausF_number == 1);
	Bool_t isTauLNumGen = (*tausF_genTauNum == 1);
	Bool_t noTauT = (*tausT_number == 0);
	// 1tau0l
	Bool_t is1tau0lCR = *tausT_number == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 0;
	Bool_t is1tau0lCRLTau = isTauLNum && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 0;
	Bool_t is1tau0lVR = *tausT_number == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	Bool_t is1tau0lVRLTau = isTauLNum && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	Bool_t is1tau0lVRLTauNotT = isTauLNum && *tausT_number == 0 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	Bool_t is1tau0lCRLTauNotT = isTauLNum && *tausT_number == 0 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 0;
	// SR
	Bool_t is1tau0lSR = *tausT_number == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
	Bool_t is1tau0lSRLTauNotT = isTauLNum && *tausT_number == 0 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 2;
	// CRc and CRa
	Bool_t is1tau0lCRc = *tausT_number == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num >= 2;
	Bool_t is1tau0lCRcLTau = isTauLNum && lepNum == 0 && *jets_number < 8 && *bjetsM_num >= 2;
	Bool_t is1tau0lCRa = *tausT_number == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 0;
	Bool_t is1tau0lCRaLTau = isTauLNum && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 0;
	Bool_t is1tau0lCRb = *tausT_number == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 1;
	Bool_t is1tau0lCRbLTau = isTauLNum && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 1;

	fillHistsVector(is1tau0lCR, 1, basicWeight);
	fillHistsVector(is1tau0lCRLTau, 2, basicWeight);
	fillHistsVector(is1tau0lVR, 3, basicWeight);
	fillHistsVector(is1tau0lVRLTau, 4, basicWeight);
	fillHistsVector(is1tau0lVRLTauNotT, 5, basicWeight);
	// CRc CRa CR3
	fillHistsVector(is1tau0lCRc, 14, basicWeight);
	fillHistsVector(is1tau0lCRa, 15, basicWeight);
	fillHistsVector(is1tau0lCRb, 16, basicWeight);
	// fakeTau
	fillHistsVector(is1tau0lCRb, 17, basicWeight * FRWeight);

	Bool_t isEta1 = 0 < *tausF_1jetEtaAbs && *tausF_1jetEtaAbs <= 0.8;
	Bool_t isEta2 = 0.8 < *tausF_1jetEtaAbs && *tausF_1jetEtaAbs <= 1.6;
	Bool_t isEta3 = 1.8 < *tausF_1jetEtaAbs && *tausF_1jetEtaAbs <= 2.4;

	if (!m_isData)
	{
		// be blind for data in signal region
		fillHistsVector(is1tau0lSR, 0, basicWeight);

		Bool_t is1tau0lSRGen = *tausT_number == 1 && *tausT_genTauNum == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
		Bool_t is1tau0lCRGen = *tausT_number == 1 && *tausT_genTauNum == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 0;
		Bool_t is1tau0lCRLTauGen = isTauLNum && isTauLNumGen && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 0;
		Bool_t is1tau0lVRGen = *tausT_number == 1 && *tausT_genTauNum == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 1;
		Bool_t is1tau0lVRLTauGen = isTauLNum && isTauLNumGen && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 1;
		Bool_t is1tau0lVRLTauNotTGen = isTauLNum && *tausT_number == 0 && isTauLNumGen && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 1;
		Bool_t is1tau0lCRLTauNotTGen = isTauLNum && *tausT_number == 0 && isTauLNumGen && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 0;
		// SR
		Bool_t is1tau0lSRLTauNotTGen = isTauLNum && *tausT_number == 0 && isTauLNumGen && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 2;
		// CRc and CRa
		Bool_t is1tau0lCRcGen = *tausT_number == 1 && *tausT_genTauNum == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num >= 2;
		Bool_t is1tau0lCRcLTauGen = isTauLNum && isTauLNumGen && lepNum == 0 && *jets_number < 8 && *bjetsM_num >= 2;
		Bool_t is1tau0lCRaGen = *tausT_number == 1 && *tausT_genTauNum == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 0;
		Bool_t is1tau0lCRaLTauGen = isTauLNum && isTauLNumGen && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 0;
		Bool_t is1tau0lCRbGen = *tausT_number == 1 && *tausT_genTauNum == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 1;
		Bool_t is1tau0lCRbLTauGen = isTauLNum && isTauLNumGen && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 1;

		fillHistsVector(is1tau0lSRGen, 6, basicWeight);
		fillHistsVector(is1tau0lCRGen, 7, basicWeight);
		fillHistsVector(is1tau0lCRLTauGen, 8, basicWeight);
		fillHistsVector(is1tau0lVRGen, 9, basicWeight);
		fillHistsVector(is1tau0lVRLTauGen, 10, basicWeight);
		//
		fillHistsVector(is1tau0lCRcGen, 17, basicWeight);
		fillHistsVector(is1tau0lCRaGen, 18, basicWeight);
		fillHistsVector(is1tau0lCRbGen, 19, basicWeight);
		fillHistsVector(is1tau0lCRcLTauGen && noTauT, 21, basicWeight * FRWeight);
		fillHistsVector(is1tau0lCRaLTauGen && noTauT, 23, basicWeight * FRWeight);
		fillHistsVector(is1tau0lCRbLTauGen && noTauT, 25, basicWeight * FRWeight);
		//
		fillHistsVector(is1tau0lSRLTauNotTGen, 27, basicWeight * FRWeight);
		fillHistsVector(is1tau0lCRLTauNotTGen, 29, basicWeight * FRWeight);
		fillHistsVector(is1tau0lVRLTauNotTGen, 31, basicWeight * FRWeight);

		if (!m_ifMeasurement)
		{

			// AR FR weighted
			FillHistsVecorMyClassGenearal(is1tau0lCRGen, 1, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCR && (!is1tau0lCRGen), 2, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotTGen, 5, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotTGen, 6, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVRGen, 8, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVR && (!is1tau0lVRGen), 9, basicWeight, vectorOfVariblesRegions_FRweighted);
			// FR uncertainty variation
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotTGen, 17, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotTGen, 18, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotTGen, 21, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotTGen, 22, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweighted);

			FillHistsVecorMyClassGenearal(is1tau0lCRGen, 1, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lCR && (!is1tau0lCRGen), 2, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotTGen, 5, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotTGen, 6, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVRGen, 8, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVR && (!is1tau0lVRGen), 9, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			// FR uncertainty variation
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotTGen, 17, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotTGen, 18, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotTGen, 21, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotTGen, 22, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweightedInt);

			// SR
			FillHistsVecorMyClassGenearal(is1tau0lSRGen, 11, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lSR && (!is1tau0lSRGen), 12, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotTGen, 14, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			// FR uncertainty
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotTGen, 24, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotTGen, 25, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweighted);
			// Int
			FillHistsVecorMyClassGenearal(is1tau0lSRGen, 11, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lSR && (!is1tau0lSRGen), 12, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotTGen, 14, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
			// FR uncertainty
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotTGen, 24, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotTGen, 25, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweightedInt);
			// CRc
			FillHistsVecorMyClassGenearal(is1tau0lCRcGen, 28, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRcLTauGen && noTauT, 30, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRcGen, 28, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lCRcLTauGen && noTauT, 30, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
		}

		tausL_1pt_eta_class.fillHistVec(3, basicWeight, is1tau0lCRLTauGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(4, basicWeight, is1tau0lCRLTauGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(5, basicWeight, is1tau0lCRLTauGen && isEta3);
		tausL_1pt_eta_class.fillHistVec(9, basicWeight, is1tau0lCRGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(10, basicWeight, is1tau0lCRGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(11, basicWeight, is1tau0lCRGen && isEta3);
		// VR
		tausL_1pt_eta_class.fillHistVec(15, basicWeight, is1tau0lVRLTauNotTGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(16, basicWeight, is1tau0lVRLTauNotTGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(17, basicWeight, is1tau0lVRLTauNotTGen && isEta3);
		// CRLNotT
		tausL_1pt_eta_class.fillHistVec(18, basicWeight, is1tau0lCRLTauNotTGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(19, basicWeight, is1tau0lCRLTauNotTGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(20, basicWeight, is1tau0lCRLTauNotTGen && isEta3);
		// for mearure FR with MC
		tausL_1pt_eta_class.fillHistVec(0, basicWeight, is1tau0lCRLTau && isEta1);
		tausL_1pt_eta_class.fillHistVec(1, basicWeight, is1tau0lCRLTau && isEta2);
		tausL_1pt_eta_class.fillHistVec(2, basicWeight, is1tau0lCRLTau && isEta3);
		tausL_1pt_eta_class.fillHistVec(6, basicWeight, is1tau0lCR && isEta1);
		tausL_1pt_eta_class.fillHistVec(7, basicWeight, is1tau0lCR && isEta2);
		tausL_1pt_eta_class.fillHistVec(8, basicWeight, is1tau0lCR && isEta3);
		// VR
		//  tausL_1pt_eta_class.fillHistVec(24, basicWeight, is1tau0lVRLTau && isEta1);
		//  tausL_1pt_eta_class.fillHistVec(25, basicWeight, is1tau0lVRLTau && isEta2);
		//  tausL_1pt_eta_class.fillHistVec(26, basicWeight, is1tau0lVRLTau && isEta3);
		//  tausL_1pt_eta_class.fillHistVec(27, basicWeight, is1tau0lVR && isEta1);
		//  tausL_1pt_eta_class.fillHistVec(28, basicWeight, is1tau0lVR && isEta2);
		//  tausL_1pt_eta_class.fillHistVec(29, basicWeight, is1tau0lVR && isEta3);
		tausL_1pt_eta_class.fillHistVec(27, basicWeight, is1tau0lCRcLTauGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(28, basicWeight, is1tau0lCRcLTauGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(29, basicWeight, is1tau0lCRcLTauGen && isEta3);
		tausL_1pt_eta_class.fillHistVec(33, basicWeight, is1tau0lCRcGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(34, basicWeight, is1tau0lCRcGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(35, basicWeight, is1tau0lCRcGen && isEta3);
		// CRa
		tausL_1pt_eta_class.fillHistVec(39, basicWeight, is1tau0lCRaLTauGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(40, basicWeight, is1tau0lCRaLTauGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(41, basicWeight, is1tau0lCRaLTauGen && isEta3);
		tausL_1pt_eta_class.fillHistVec(45, basicWeight, is1tau0lCRaGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(46, basicWeight, is1tau0lCRaGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(47, basicWeight, is1tau0lCRaGen && isEta3);
		// CRb
		tausL_1pt_eta_class.fillHistVec(51, basicWeight, is1tau0lCRbLTauGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(52, basicWeight, is1tau0lCRbLTauGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(53, basicWeight, is1tau0lCRbLTauGen && isEta3);
		tausL_1pt_eta_class.fillHistVec(57, basicWeight, is1tau0lCRbGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(58, basicWeight, is1tau0lCRbGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(59, basicWeight, is1tau0lCRbGen && isEta3);
	}
	else
	{

		fillHistsVector(is1tau0lCRcLTau && noTauT, 20, basicWeight * FRWeight);
		fillHistsVector(is1tau0lCRaLTau && noTauT, 22, basicWeight * FRWeight);
		fillHistsVector(is1tau0lCRbLTau && noTauT, 24, basicWeight * FRWeight);
		//
		fillHistsVector(is1tau0lSRLTauNotT, 26, basicWeight * FRWeight);
		fillHistsVector(is1tau0lCRLTauNotT, 28, basicWeight * FRWeight);
		fillHistsVector(is1tau0lVRLTauNotT, 30, basicWeight * FRWeight);

		if (!m_ifMeasurement)
		{

			// AR FR weighted
			FillHistsVecorMyClassGenearal(is1tau0lCR, 0, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVR, 7, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotT, 4, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotT, 3, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			// FR variation
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotT, 15, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotT, 16, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotT, 19, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotT, 20, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweighted);
			// Int
			FillHistsVecorMyClassGenearal(is1tau0lCR, 0, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVR, 7, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotT, 4, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotT, 3, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
			// FR variation
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotT, 15, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lCRLTauNotT, 16, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotT, 19, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lVRLTauNotT, 20, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweightedInt);

			// SR not for data in SR
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotT, 13, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotT, 23, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotT, 24, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweighted);
			//
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotT, 13, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotT, 23, basicWeight * FRWeight_up, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lSRLTauNotT, 24, basicWeight * FRWeight_down, vectorOfVariblesRegions_FRweightedInt);
			// CRc
			FillHistsVecorMyClassGenearal(is1tau0lCRc, 27, basicWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRcLTau && noTauT, 29, basicWeight * FRWeight, vectorOfVariblesRegions_FRweighted);
			FillHistsVecorMyClassGenearal(is1tau0lCRc, 27, basicWeight, vectorOfVariblesRegions_FRweightedInt);
			FillHistsVecorMyClassGenearal(is1tau0lCRcLTau && noTauT, 29, basicWeight * FRWeight, vectorOfVariblesRegions_FRweightedInt);
		}

		tausL_1pt_eta_class.fillHistVec(0, basicWeight, is1tau0lCRLTau && isEta1);
		tausL_1pt_eta_class.fillHistVec(1, basicWeight, is1tau0lCRLTau && isEta2);
		tausL_1pt_eta_class.fillHistVec(2, basicWeight, is1tau0lCRLTau && isEta3);
		tausL_1pt_eta_class.fillHistVec(6, basicWeight, is1tau0lCR && isEta1);
		tausL_1pt_eta_class.fillHistVec(7, basicWeight, is1tau0lCR && isEta2);
		tausL_1pt_eta_class.fillHistVec(8, basicWeight, is1tau0lCR && isEta3);
		// VR
		tausL_1pt_eta_class.fillHistVec(12, basicWeight, is1tau0lVRLTauNotT && isEta1);
		tausL_1pt_eta_class.fillHistVec(13, basicWeight, is1tau0lVRLTauNotT && isEta2);
		tausL_1pt_eta_class.fillHistVec(14, basicWeight, is1tau0lVRLTauNotT && isEta3);
		// CRLNotT
		tausL_1pt_eta_class.fillHistVec(18, basicWeight, is1tau0lCRLTauNotT && isEta1);
		tausL_1pt_eta_class.fillHistVec(19, basicWeight, is1tau0lCRLTauNotT && isEta2);
		tausL_1pt_eta_class.fillHistVec(20, basicWeight, is1tau0lCRLTauNotT && isEta3);
		// CRc and CRa
		tausL_1pt_eta_class.fillHistVec(24, basicWeight, is1tau0lCRcLTau && isEta1);
		tausL_1pt_eta_class.fillHistVec(25, basicWeight, is1tau0lCRcLTau && isEta2);
		tausL_1pt_eta_class.fillHistVec(26, basicWeight, is1tau0lCRcLTau && isEta3);
		tausL_1pt_eta_class.fillHistVec(30, basicWeight, is1tau0lCRc && isEta1);
		tausL_1pt_eta_class.fillHistVec(31, basicWeight, is1tau0lCRc && isEta2);
		tausL_1pt_eta_class.fillHistVec(32, basicWeight, is1tau0lCRc && isEta3);
		// CRa
		tausL_1pt_eta_class.fillHistVec(36, basicWeight, is1tau0lCRaLTau && isEta1);
		tausL_1pt_eta_class.fillHistVec(37, basicWeight, is1tau0lCRaLTau && isEta2);
		tausL_1pt_eta_class.fillHistVec(38, basicWeight, is1tau0lCRaLTau && isEta3);
		tausL_1pt_eta_class.fillHistVec(42, basicWeight, is1tau0lCRa && isEta1);
		tausL_1pt_eta_class.fillHistVec(43, basicWeight, is1tau0lCRa && isEta2);
		tausL_1pt_eta_class.fillHistVec(44, basicWeight, is1tau0lCRa && isEta3);
		// CRb
		tausL_1pt_eta_class.fillHistVec(48, basicWeight, is1tau0lCRbLTau && isEta1);
		tausL_1pt_eta_class.fillHistVec(49, basicWeight, is1tau0lCRbLTau && isEta2);
		tausL_1pt_eta_class.fillHistVec(50, basicWeight, is1tau0lCRbLTau && isEta3);
		tausL_1pt_eta_class.fillHistVec(54, basicWeight, is1tau0lCRb && isEta1);
		tausL_1pt_eta_class.fillHistVec(55, basicWeight, is1tau0lCRb && isEta2);
		tausL_1pt_eta_class.fillHistVec(56, basicWeight, is1tau0lCRb && isEta3);
	}

	return kTRUE;
}

void writeHist_forFakeRate::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
}

void writeHist_forFakeRate::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.
	// #include "lumiAndCrossSection.h"
	Double_t processScale = 1.0;
	if (!m_isData)
	{
		std::cout << m_processName << ": " << lumiMap[m_era] << " " << crossSectionMap[m_processName] << " " << m_genWeightSum << "\n";
		processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / m_genWeightSum);
	};

	for (UInt_t j = 0; j < eventCount_hists.size(); j++)
	{
		std::cout << j << "\n";
		eventCount_hists[j]->Scale(processScale);
		eventCount_hists[j]->Print();
	};

	scaleVectorHistRegions(vectorOfVariblesRegions_FRweighted, processScale);
	scaleVectorHistRegions(vectorOfVariblesRegions_FRweightedInt, processScale);

	tausL_1pt_eta_class.histsScale(processScale);
	Info("Terminate", "outputFile here: %s", outputFile->GetName());
	outputFile->Write();
	outputFile->Close();
}