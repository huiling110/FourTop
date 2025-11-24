import ROOT

# Enable implicit multi-threading to speed up processing
ROOT.ROOT.EnableImplicitMT()

inputFile = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/outTree_11.root'
df = ROOT.RDataFrame('Events', inputFile)




def plotGenTaupt():
    # Define the histogram parameters: name, title, number of bins, lower edge, upper edge
    histo = df.Histo1D(("hist", "GenVisTau pT distribution; pT (GeV); Events", 100, 0, 200), "GenVisTau_pt")

    # Use the RCanvas interface (ROOT 6.24+) or TCanvas for older versions
    canvas = ROOT.TCanvas("canvas", "", 800, 600)
    histo.Draw()

    bin_threshold = histo.FindBin(20)
    entries_below_threshold = histo.Integral(1, bin_threshold)
    total_entries = histo.GetEntries()
    portion_below_threshold = entries_below_threshold / total_entries

    # Prepare the text you want to display on the plot
    text = f"Entries < 20: {entries_below_threshold}\nPortion: {portion_below_threshold*100:.2f}%"

    # Create a TPaveText object to display the text
    # Parameters are the coordinates of the lower left and upper right corners in NDC (Normalized Device Coordinates)
    info_text = ROOT.TPaveText(0.6, 0.7, 0.9, 0.8, "NDC")
    info_text.AddText(text)
    info_text.SetFillColor(0)
    info_text.SetTextColor(ROOT.kBlack)
    info_text.SetTextAlign(12)  # Align left and center vertically
    info_text.Draw()

    # Save the plot
    canvas.SaveAs("GenVisTau_pt_distribution.png")

    # Optionally, keep the application running to view the plot interactively
    canvas.WaitPrimitive()
