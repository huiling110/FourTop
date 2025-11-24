import ROOT
import usefulFunc as uf
import setTDRStyle as st

def hist_to_graph(histo):
    n_bins = histo.GetNbinsX()
    graph = ROOT.TGraphErrors(n_bins)  # 创建 TGraphErrors 对象
    for i in range(1, n_bins + 1):
        x = histo.GetBinCenter(i)
        y = histo.GetBinContent(i)
        y_error = histo.GetBinError(i)  # 获取 bin 的误差

        graph.SetPoint(i - 1, x, y)
        graph.SetPointError(i - 1, 0, y_error)  # 在 y 方向上设置误差
    graph.SetTitle(histo.GetTitle())
    graph.GetXaxis().SetTitle(histo.GetXaxis().GetTitle())
    graph.GetYaxis().SetTitle(histo.GetYaxis().GetTitle())
    return graph

def hist_to_histStyle(histo):
    histo.SetLineWidth(2)
    histo.SetMarkerSize(0)  # 禁用点标记
    histo.SetFillStyle(0)   # 禁用填充
    return histo

  
def main():
    # basePath_rtu = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/"
    # basePath_rtu = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/mc/'
    basePath_rtu = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/mc/'
    # _range = '1tau1lAllRegion'
    _range = '1tau0lMRHTCut500'
    # _range = '1tau2lSR'
    # _range = '1tau2lCR2'
    name = 'normalize'

    DataDriven_file_list = [
        f"fakeTau_data_{_range}.root",
        f"fakeTau_MC_{_range}.root"
    ]

    MC_file_list = [
        f"fakeTau_fromGen_{_range}.root"
    ]
    # plotName  = '1tau0lMR'
    
    plotName = f"{basePath_rtu}results/{_range}_"
    plotName = f"{plotName}{name}_"


    chainDataDriven = ROOT.TChain("newtree")
    for _file in DataDriven_file_list:
        chainDataDriven.Add(basePath_rtu + _file)
    chainMC = ROOT.TChain("newtree")
    for _file in MC_file_list:
        chainMC.Add(basePath_rtu + _file)
    
    

    # variables = ["jets_num", "bjetsM_num", "jets_1pt", "jets_6pt", "bjetsT_1pt", "jets_HT", "tausT_1pt", "tausT_1eta", "tausT_1decayMode", "lepTopMVAT_1pt", "tausT_num"]
    # variables = ['jets_num']
    variables = ['tausT_1pt']
    # variables = ['tausF_1prongNum'] 
    
    dict_for_hist_set = {"jets_num": ["jets_num", "n^{jet}", 12, 1.5, 13.5], 
                            "bjetsM_num": ["bjetsM_num", "n^{M b-jet}", 8, -0.5, 7.5], 
                            "jets_1pt": ["jets_1pt", "p_{T}^{1st jet}(GeV)", 10, 25, 700], 
                            "jets_6pt": ["jets_6pt", "p_{T}^{6th jet}(GeV)", 10, 25, 700], 
                            "bjetsT_1pt": ["bjetsT_1pt", "p_{T}^{1st T b-jet}", 10, 0, 200],
                            "jets_HT" : ["jets_MHT", "HT(GeV)", 10, 200, 1800],
                            # "tausT_1pt" : ["tausT_1pt", "p_{T}^{1st #tau}", 10, 20, 200,],
                            "tausT_1pt" : ["tausT_1pt", "p_{T}^{1st #tau}", 10, 20, 150,],
                            "tausF_1pt" : ["tausF_1pt", "p_{T}^{1st #tau}", 10, 20, 150,],
                            "tausT_1eta" : ["tausT_1eta", "#eta_{#tau}", 10, 0, 3],
                            "tausT_1decayMode" : ["tausT_1decayMode", "decay mode^{T#tau}", 12, -0.5, 11.5],
                            "lepTopMVAT_1pt" : ["lepTopMVAT_1pt", "p_{T}^{1st l}(GeV)", 10, 0, 200],
                            "tausT_num" : ["tausT_num", "n^{T#tau}", 5, -0.5, 4.5],
                            'tausF_1prongNum': ["tausF_1prongNum", "n^{#tau}_{1 prong}", 5, -0.5, 4.5],
                            }

    histograms_DataDriven = {}
    histograms_MC = {}

    for var in variables:
        hist1 = ROOT.TH1F(dict_for_hist_set[var][0], dict_for_hist_set[var][1], dict_for_hist_set[var][2], dict_for_hist_set[var][3], dict_for_hist_set[var][4])
        #normalize hist 1
        integral = hist1.Integral()
        if integral != 0:  # Avoid division by zero
            hist1.Scale(1.0 / integral) 
            
        chainDataDriven.Draw(var + ">>" + var,"FR_weight_final", "goff")
        histograms_DataDriven[var] = hist1
        graph1 = hist_to_graph(hist1)
        histograms_DataDriven[var] = graph1
        
    for var in variables:
        hist2 = ROOT.TH1F(dict_for_hist_set[var][0]+'_', dict_for_hist_set[var][1], dict_for_hist_set[var][2], dict_for_hist_set[var][3], dict_for_hist_set[var][4])
        
        integral = hist2.Integral()
        if integral != 0:  # Avoid division by zero
            hist2.Scale(1.0 / integral)
        
        chainMC.Draw(var + ">>" + var+'_', "event_allWeight_1tau1l", "goff")
        histograms_MC[var] = hist2
        graph2 = hist_to_graph(hist2)
        histograms_MC[var] = graph2
    # legendList = ["MC", "DataDriven"]
    legendList = ["DataDriven", "MC"]
    for var in variables:
        # plotOverlay_new_1([histograms_MC[var], histograms_DataDriven[var]], legendList, "2018" , '', f"{plotName}{var}_{_range}", '', [0.65, 0.72, 0.95,0.93], [] )
        plotOverlay_new_1( [histograms_DataDriven[var], histograms_MC[var]], legendList, "2018" , '', f"{plotName}{var}_{_range}", '', [0.65, 0.72, 0.95,0.93], [] )


def plotOverlay_new_1(graphList, legenList, era, yTitle, plotName, drawOp='', legendPos=[0.65, 0.8, 0.9, 0.93], yRange=[]):
    print('start to plot overlay plot')
    import ctypes
    mySty = st.setMyStyle()
    mySty.cd()
    can = ROOT.TCanvas('overlay', 'overlay', 1000, 800)
    
    legend = st.getMyLegend(legendPos[0], legendPos[1], legendPos[2], legendPos[3])
    
    # plot style
    LineColorDic = {
        0: [ROOT.TColor.GetColor("#f03b20"), 8],  # red
        2: [ROOT.TColor.GetColor("#fd8d3c"), 41], # orange
        1: [ROOT.TColor.GetColor("#2ca25f"), 41],  # green
    }

    yRange = getGraphLimit(graphList)
    for i, graph in enumerate(graphList):

        if i == 0:
            graph.Draw(drawOp + " APE")
        else:
            graph.Draw('PE same')

        graph.SetLineColor(LineColorDic[i][0])
        graph.SetMarkerColor(LineColorDic[i][0])
        graph.SetLineWidth(3)
        graph.SetMarkerSize(1.5)
        graph.SetMarkerStyle(LineColorDic[i][1])
        graph.GetXaxis().SetTitle(graph.GetTitle())
        graph.GetYaxis().SetTitle(yTitle)
        graph.GetXaxis().SetTitleSize(0.05)
        graph.GetYaxis().SetTitleSize(0.06)
        if len(yRange) > 1:
            graph.GetYaxis().SetRangeUser(yRange[0], yRange[1])
        
        legend.AddEntry(graph, legenList[i], "lep")  # Add an entry to the legend
        legend.Draw()

    st.addCMSTextToPad(can, era)
        
    can.SaveAs(plotName + '.png')
    #can.SaveAs(plotName + '.pdf')
    print('Done overlay plotting\n\n')

def getGraphLimit(graphList):
    # Initialize variables to store the global y-min and y-max
    global_y_min = float('inf')
    global_y_max = float('-inf')

    # Calculate the global y-min and y-max across all graphs
    for graph in graphList:
        n_points = graph.GetN()  # Number of points in the graph
        for j in range(n_points):
            # Get the y value at each point
            y_value = graph.GetY()[j]
            # Update global extrema if necessary
            if y_value < global_y_min:
                global_y_min = y_value
            if y_value > global_y_max:
                global_y_max = y_value
    return [global_y_min, global_y_max]
    
    
if __name__ == "__main__":
    main()