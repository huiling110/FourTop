import ROOT
from ROOT import RooFit, RooRealVar, RooDataHist, RooHistPdf, RooArgList, RooArgSet, RooRealSumPdf

# Define a function to perform morphing and save the result
def perform_morphing(input_file, data_hist_name, fakeTau_hist_name, output_workspace):

    # Open the file and get the histograms
    file = ROOT.TFile(input_file)
    hist_data = file.Get(data_hist_name)
    hist_fakeTau = file.Get(fakeTau_hist_name)

    # Define the pT variable
    pt = RooRealVar("pt", "p_{T}^{1st fake #tau}", 0, 200)

    # Create RooDataHist objects
    data_hist = RooDataHist("data_hist", "Data Histogram", RooArgList(pt), hist_data)
    fakeTau_hist = RooDataHist("fakeTau_hist", "FakeTau Histogram", RooArgList(pt), hist_fakeTau)

    # Convert histograms to PDFs
    data_pdf = ROOT.RooHistPdf("data_pdf", "Data PDF", RooArgSet(pt), data_hist)
    fakeTau_pdf = ROOT.RooHistPdf("fakeTau_pdf", "FakeTau PDF", RooArgSet(pt), fakeTau_hist)

    # Define morphing parameter
    alpha = RooRealVar("alpha", "morphing parameter", 0, -10, 10)

    # Create morphed PDF
    morphed_fakeTau_pdf = RooRealSumPdf("morphed_fakeTau_pdf", "Morphed FakeTau",
                                        RooArgList(data_pdf, fakeTau_pdf), RooArgList(alpha))

    # Fit the morphed PDF to the data
    morphed_fakeTau_pdf.fitTo(data_hist)

    # Save the workspace
    workspace = ROOT.RooWorkspace("workspace")
    getattr(workspace, 'import')(morphed_fakeTau_pdf)

    # Export to file
    workspace.writeToFile(output_workspace)

# Usage
input_filename = "your_file.root"
data_hist_name = "hist_data"
fakeTau_hist_name = "hist_fakeTau"
output_workspace_filename = "morphed_workspace.root"

# inputDir = 
inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_newCR/'

perform_morphing(input_filename, data_hist_name, fakeTau_hist_name, output_workspace_filename)

print("Morphing complete and saved in workspace.")
