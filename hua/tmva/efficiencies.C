// #include "tmvaglob.C"
#include "tmvaglob.h"
#include "TH2F.h"
#include "TFile.h"
#include "TIterator.h"
#include "TKey.h"

// void plot_efficiencies(TFile *file, Int_t type = 2, TDirectory *BinDir = 0, TString variablenum = "", TString fileDir = "")
void plot_efficiencies(TFile *file, Int_t type = 2, TDirectory *BinDir = 0, TString fileDir = "")
{
	// input:   - Input file (result from TMVA),
	//          - type = 1 --> plot efficiency(B) versus eff(S)
	//                 = 2 --> plot rejection (B) versus efficiency (S)
	//                 = 3 --> plot 1/eff(B) versus efficiency (S)

	Bool_t __PLOT_LOGO__ = kTRUE;
	Bool_t __SAVE_IMAGE__ = kTRUE;

	// the coordinates
	Float_t x1 = 0;
	Float_t x2 = 1;
	Float_t y1 = 0;
	Float_t y2 = 0.8;

	// reverse order if "rejection"
	if (type == 2)
	{
		Float_t z = y1;
		y1 = 1 - y2;
		y2 = 1 - z;
		//      cout << "--- type==2: plot background rejection versus signal efficiency" << endl;
	}
	else if (type == 3)
	{
		y1 = 0;
		y2 = -1; // will be set to the max found in the histograms
	}
	else
	{
		//  cout << "--- type==1: plot background efficiency versus signal efficiency" << endl;
	}
	// create canvas
	TCanvas *c = new TCanvas("c", "the canvas", 200, 0, 650, 500);

	// global style settings
	c->SetGrid();
	c->SetTicks();

	// legend
	Float_t x0L = 0.107, y0H = 0.899;
	Float_t dxL = 0.457 - x0L, dyH = 0.22;
	if (type == 2)
	{
		x0L = 0.15;
		y0H = 1 - y0H + dyH + 0.07;
	}
	TLegend *legend = new TLegend(x0L, y0H - dyH, x0L + dxL, y0H);
	// legend->SetTextSize( 0.05 );
	legend->SetHeader("MVA Method:");
	legend->SetMargin(0.4);

	TString xtit = "Signal efficiency";
	TString ytit = "Background efficiency";
	if (type == 2)
		ytit = "Background rejection";
	if (type == 3)
		ytit = "1/(Background eff.)";
	// TString ftit = ytit + " versus " + xtit + "(" + variablenum + " variables)";
	TString ftit = ytit + " versus " + xtit + " variables)";


	TString hNameRef = "effBvsS";
	if (type == 2)
		hNameRef = "rejBvsS";
	if (type == 3)
		hNameRef = "invBeffvsSeff";

	if (TString(BinDir->GetName()).Contains("multicut"))
	{
		ftit += "  Bin: ";
		ftit += (BinDir->GetTitle());
	}

	TList xhists;
	TList xmethods;
	UInt_t xnm = TMVAGlob::GetListOfMethods(xmethods);
	TIter xnext(&xmethods);
	// loop over all methods
	TKey *xkey;
	while ((xkey = (TKey *)xnext()))
	{
		TDirectory *mDir = (TDirectory *)xkey->ReadObj();
		TList titles;
		UInt_t ninst = TMVAGlob::GetListOfTitles(mDir, titles);
		TIter nextTitle(&titles);
		TKey *titkey;
		TDirectory *titDir;
		while ((titkey = TMVAGlob::NextKey(nextTitle, "TDirectory")))
		{
			titDir = (TDirectory *)titkey->ReadObj();
			TString methodTitle;
			TMVAGlob::GetMethodTitle(methodTitle, titDir);
			TIter nextKey(titDir->GetListOfKeys());
			TKey *hkey2;
			while ((hkey2 = TMVAGlob::NextKey(nextKey, "TH1")))
			{
				TH1 *h = (TH1 *)hkey2->ReadObj();
				TString hname = h->GetName();
				if (hname.Contains(hNameRef) && hname.BeginsWith("MVA_"))
				{
					if (type == 3 && h->GetMaximum() > y2)
						y2 = h->GetMaximum() * 1.1;
				}
			}
		}
	}

	// draw empty frame
	if (gROOT->FindObject("frame") != 0)
		gROOT->FindObject("frame")->Delete();
	TH2F *frame = new TH2F("frame", ftit, 500, x1, x2, 500, y1, y2);
	frame->GetXaxis()->SetTitle(xtit);
	frame->GetYaxis()->SetTitle(ytit);
	TMVAGlob::SetFrameStyle(frame, 1.0);

	frame->Draw();

	Int_t color = 1;
	Int_t nmva = 0;
	TKey *key;

	TList hists;
	TList methods;
	UInt_t nm = TMVAGlob::GetListOfMethods(methods);
	//   TIter next(file->GetListOfKeys());
	TIter next(&methods);

	// loop over all methods
	while ((key = (TKey *)next()))
	{
		TDirectory *mDir = (TDirectory *)key->ReadObj();
		TList titles;
		UInt_t ninst = TMVAGlob::GetListOfTitles(mDir, titles);
		TIter nextTitle(&titles);
		TKey *titkey;
		TDirectory *titDir;
		while ((titkey = TMVAGlob::NextKey(nextTitle, "TDirectory")))
		{
			titDir = (TDirectory *)titkey->ReadObj();
			TString methodTitle;
			TMVAGlob::GetMethodTitle(methodTitle, titDir);
			TIter nextKey(titDir->GetListOfKeys());
			TKey *hkey2;
			while ((hkey2 = TMVAGlob::NextKey(nextKey, "TH1")))
			{
				TH1 *h = (TH1 *)hkey2->ReadObj();
				TString hname = h->GetName();
				if (hname.Contains(hNameRef) && hname.BeginsWith("MVA_"))
				{
					h->SetLineWidth(3);
					h->SetLineColor(color);
					color++;
					if (color == 5 || color == 10 || color == 11)
						color++;
					h->Draw("csame");
					hists.Add(h);
					nmva++;
				}
			}
		}
	}

	while (hists.GetSize())
	{
		TListIter hIt(&hists);
		TH1 *hist(0);
		Double_t largestInt = -1;
		TH1 *histWithLargestInt(0);
		while ((hist = (TH1 *)hIt()) != 0)
		{
			Double_t integral = hist->Integral(1, hist->FindBin(0.9999));
			if (integral > largestInt)
			{
				largestInt = integral;
				histWithLargestInt = hist;
			}
		}
		if (histWithLargestInt == 0)
		{
			cout << "ERROR - unknown hist \"histWithLargestInt\" --> serious problem in ROOT file" << endl;
			break;
		}
		legend->AddEntry(histWithLargestInt, TString(histWithLargestInt->GetTitle()).ReplaceAll("MVA_", ""), "l");
		hists.Remove(histWithLargestInt);
	}

	// rescale legend box size
	// current box size has been tuned for 3 MVAs + 1 title
	if (type == 1)
	{
		dyH *= (1.0 + Float_t(nmva - 3.0) / 4.0);
		legend->SetY1(y0H - dyH);
	}
	else
	{
		dyH *= (Float_t(TMath::Min(10, nmva) - 3.0) / 4.0);
		legend->SetY2(y0H + dyH);
	}

	// redraw axes
	frame->Draw("sameaxis");
	legend->Draw("same");

	// ============================================================

	if (__PLOT_LOGO__)
		TMVAGlob::plot_logo();

	// ============================================================

	c->Update();

	// TString fname = fileDir + "results/" + hNameRef + "_" + variablenum;
	TString fname = fileDir +  + hNameRef ;
	if (TString(BinDir->GetName()).Contains("multicut"))
	{
		TString fprepend(BinDir->GetName());
		fprepend.ReplaceAll("multicutMVA_", "");
		fname = "plots/" + fprepend + "_" + hNameRef;
	}
	if (__SAVE_IMAGE__)
		TMVAGlob::imgconv(c, fname);

	return;
}

void efficiencies(
	// TString fin = "TMVA.root",
	// TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/1tau1lvaribleList_11.root",
    // TString outDir = "./output/",
    TString fin = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Cut1tau1l_v75OverlapRemovalFTau/mc/BDTTrain/v1AllCorrection/inputList_tauTT.csv.root",
    TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Cut1tau1l_v75OverlapRemovalFTau/mc/BDTTrain/v1AllCorrection/results/",
	Int_t type = 2, Bool_t useTMVAStyle = kTRUE)
{
	// argument: type = 1 --> plot efficiency(B) versus eff(S)
	//           type = 2 --> plot rejection (B) versus efficiency (S)

	// set style and remove existing canvas'
	TMVAGlob::Initialize(useTMVAStyle);

	// checks if file with name "fin" is already open, and if not opens one
	TFile *file = (TFile *)gROOT->GetListOfFiles()->FindObject(fin);
	if (!file || !file->IsOpen())
	{
		file = new TFile(fin);
	}

	// check if multi-cut MVA or only one set of MVAs
	//   Bool_t multiMVA=kFALSE;
	// TIter nextDir(file->GetListOfKeys());
	TString dataset = "dataset";
	TIter nextDir(file->GetDirectory(dataset.Data())->GetListOfKeys());
	TKey *key;
	// loop over all directories and check if
	// one contains the key word 'multicutMVA'
	while ((key = (TKey *)nextDir()))
	{
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if (!cl->InheritsFrom("TDirectory"))
			continue;
		TDirectory *d = (TDirectory *)key->ReadObj();
		TString path(d->GetPath());
		if (path.Contains("multicutMVA"))
		{
			//         multiMVA=kTRUE;
			plot_efficiencies(file, type, d);
		}
	}

	// get input variable number
	// TString variableNum = fin(fin.Index("varibleList") + 12, fin.Index(".root") - fin.Index("varibleList") - 12);
	// std::cout << "plotting ROC for variablse: " << variableNum << "\n";
	// TString fileDir = fin(0, fin.Index("1tau1lvaribleList"));
	// std::cout << fileDir << "\n";

	file->cd("dataset");
	plot_efficiencies(file, type, gDirectory, outDir);

	return;
}
