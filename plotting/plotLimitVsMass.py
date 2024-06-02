import ROOT
import ttttGlobleQuantity as gq
import setTDRStyle as st
import usefulFunc as uf

def main():
    inputFile = {
        600: '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_newTriSFBinD_v76WithVLLSample/mc/variableHists_v0Basictraining1tau1l_VLL/combine/datacard_noSys/combineResults/higgsCombine_datacard_1tau1lSys.AsymptoticLimits.mH120.root',
        700: '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baselineHardro_FRweightSys_v76WithVLLAllMass/mc/variableHists_v0Basictraining1tau1l_VLLm700_DifBin/combine/datacard_mainSys/combineResults/higgsCombine_datacard_1tau1lSys.AsymptoticLimits.mH120.root',
        800: '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baselineHardro_FRweightSys_v76WithVLLAllMass/mc/variableHists_v0Basictraining1tau1l_VLLm800/combine/datacard_mainSys/combineResults/higgsCombine_datacard_1tau1lSys.AsymptoticLimits.mH120.root',
    }
    
    # outDir = 
   
    # Initialize lists to store the limits
    mass_points = []
    observed_limits = []
    expected_limits = []
    expected_limits_1sigma_up = []
    expected_limits_1sigma_down = []
    expected_limits_2sigma_up = []
    expected_limits_2sigma_down = []

    # Read the limits from each file
    for mass, filename in inputFile.items():
        (observed_limit, expected_limit, 
        expected_limit_1sigma_up, expected_limit_1sigma_down, 
        expected_limit_2sigma_up, expected_limit_2sigma_down) = read_limits_from_file(filename)
        
        mass_points.append(mass)
        observed_limits.append(observed_limit)
        expected_limits.append(expected_limit)
        expected_limits_1sigma_up.append(expected_limit_1sigma_up)
        expected_limits_1sigma_down.append(expected_limit_1sigma_down)
        expected_limits_2sigma_up.append(expected_limit_2sigma_up)
        expected_limits_2sigma_down.append(expected_limit_2sigma_down)

    theoretical_cross_sections = getCrossSection(mass_points)
    print(theoretical_cross_sections)
    
    # Create TGraphs for the observed and expected limits
    graph_observed = ROOT.TGraph(len(mass_points))
    graph_expected = ROOT.TGraph(len(mass_points))
    graph_1sigma = ROOT.TGraphAsymmErrors(len(mass_points))
    graph_2sigma = ROOT.TGraphAsymmErrors(len(mass_points))
    graph_theory = ROOT.TGraph()

    # Fill the TGraphs with the limits
    for i, mass in enumerate(mass_points):
        theory_xs = theoretical_cross_sections[mass]
        
        if observed_limits[i] is not None:
            graph_observed.SetPoint(graph_observed.GetN(), mass, observed_limits[i] * theory_xs)
        if expected_limits[i] is not None:
            graph_expected.SetPoint(graph_expected.GetN(), mass, expected_limits[i] * theory_xs)
            graph_1sigma.SetPoint(graph_1sigma.GetN(), mass, expected_limits[i] * theory_xs)
            graph_1sigma.SetPointError(graph_1sigma.GetN()-1, 0, 0, (expected_limits[i] - expected_limits_1sigma_down[i]) * theory_xs, (expected_limits_1sigma_up[i] - expected_limits[i]) * theory_xs)
            graph_2sigma.SetPoint(graph_2sigma.GetN(), mass, expected_limits[i] * theory_xs)
            graph_2sigma.SetPointError(graph_2sigma.GetN()-1, 0, 0, (expected_limits[i] - expected_limits_2sigma_down[i]) * theory_xs, (expected_limits_2sigma_up[i] - expected_limits[i]) * theory_xs)
        graph_theory.SetPoint(graph_theory.GetN(), mass, theory_xs)

        

    mySty =  st.setMyStyle()
    mySty.cd()
    # Create a canvas to draw the graphs
    # canvas = ROOT.TCanvas("canvas", "Limits as a function of mass points", 800, 600)
    canvas = ROOT.TCanvas("canvas", "Limits as a function of mass points", 1000, 1000)
    canvas.SetLogy()

    # Draw the 2 sigma band
    # graph_2sigma.SetFillColor(ROOT.kYellow)
    graph_2sigma.SetFillColor(ROOT.TColor.GetColor("#FFDB00"))
    graph_2sigma.Draw("A3")
    
    # if y_min < float('inf') and y_max > float('-inf'):
    y_min = 0.001 
    y_max = 0.1
    # graph_2sigma.SetMinimum(y_min * 0.8)  # Add some padding to the minimum
    # graph_2sigma.SetMaximum(y_max * 1.2)  
    graph_2sigma.GetYaxis().SetRangeUser(y_min, y_max*5)
    

    # Draw the 1 sigma band
    # graph_1sigma.SetFillColor(ROOT.kGreen)
    graph_1sigma.SetFillColor(ROOT.TColor.GetColor("#90D26D"))
    graph_1sigma.Draw("3 same")

    # Draw the expected limits
    graph_expected.SetLineStyle(2)
    graph_expected.SetLineWidth(2)
    graph_expected.SetLineColor(ROOT.kBlack)
    graph_expected.Draw("L same")

    # Draw the observed limits
    graph_observed.SetMarkerStyle(20)
    graph_observed.SetMarkerSize(1)
    graph_observed.SetMarkerColor(ROOT.kBlack)
    graph_observed.Draw("P same")

    # Set titles and labels
    graph_2sigma.SetTitle("Limits as a function of mass points;Mass [GeV];95% CL Limit")
    graph_2sigma.GetXaxis().SetTitle("VLL mass [GeV]")
    graph_2sigma.GetYaxis().SetTitle("95% CL limit on #sigma [pb]")
    
    # Draw the theoretical cross section line
    graph_theory.SetLineColor(ROOT.kRed)
    graph_theory.SetLineWidth(3)
    graph_theory.SetLineStyle(1)
    graph_theory.Draw("L same")
    
    if mass_points:
        min_mass = min(mass_points)
        max_mass = max(mass_points)
        graph_2sigma.GetXaxis().SetLimits(min_mass, max_mass)


    # Add a legend
    # legend = st.getMyLegend(0.6, 0.6, 0.9, 0.9)
    legend = st.getMyLegend(0.4, 0.7, 0.9, 0.9)
    legend.AddEntry(graph_observed, "Observed", "P")
    legend.AddEntry(graph_expected, "Expected", "L")
    legend.AddEntry(graph_1sigma, "Expected #pm 1 #sigma", "F")
    legend.AddEntry(graph_2sigma, "Expected #pm 2 #sigma", "F")
    legend.AddEntry(graph_theory, "Theoretical prediction", "L")
    legend.Draw()

    era = uf.getEraFromDir(inputFile[600])
    st.addCMSTextToPad(canvas, era)

    # Keep the canvas open
    canvas.Update()
    canvas.Draw()

    canvas.SaveAs("limits_vs_mass.png")

def getCrossSection(mass_points):
    # sumPros = ['VLLm{}'.format(mass) for mass in mass_points]
    crossSections = {} 
    # for isum in sumPros:
    for imass in mass_points:
        isum = 'VLLm{}'.format(imass)
        subPros = [key for key, val in gq.histoGramPerSample.items() if val==isum]
        crossSections[imass] = 0
        for isub in subPros:
            # crossSections[isum] += gq.crossSectionMap[isub]
            crossSections[imass] += gq.crossSectionMap[isub]
    
    return crossSections

# Function to read limits from a ROOT file
def read_limits_from_file(filename):
    file = ROOT.TFile(filename, "READ")
    tree = file.Get("limit")
    if not tree:
        raise ValueError(f"TTree 'limit' not found in file {filename}")
    
    observed_limit = None
    expected_limit = None
    expected_limit_1sigma_up = None
    expected_limit_1sigma_down = None
    expected_limit_2sigma_up = None
    expected_limit_2sigma_down = None
    
    for entry in tree:
        if entry.quantileExpected == -1:
            observed_limit = entry.limit
        elif abs(entry.quantileExpected - 0.5) < 1e-5:
            expected_limit = entry.limit
        elif abs(entry.quantileExpected - 0.84) < 1e-5:
            expected_limit_1sigma_up = entry.limit
        elif abs(entry.quantileExpected - 0.16) < 1e-5:
            expected_limit_1sigma_down = entry.limit
        elif abs(entry.quantileExpected - 0.975) < 1e-5:
            expected_limit_2sigma_up = entry.limit
        elif abs(entry.quantileExpected - 0.025) < 1e-5:
            expected_limit_2sigma_down = entry.limit
    
    return (observed_limit, expected_limit, expected_limit_1sigma_up, expected_limit_1sigma_down, expected_limit_2sigma_up, expected_limit_2sigma_down)


if __name__ == "__main__":
    main()
    
    