import ROOT
import numpy as np
import ttttGlobleQuantity as gq
import usefulFunc as uf
import os

def getContextForBin(histogram, n_bins):
    bin_content = np.array([])
    bin_error = np.array([])
    for i in range(1, n_bins + 1):
        bin_content = np.append(bin_content, histogram.GetBinContent(i))
        bin_error = np.append(bin_error, histogram.GetBinError(i))
    return bin_content, bin_error

def StartPlotiing(file_path, base_name, up_name, down_name):
    root_file = ROOT.TFile.Open(file_path)
    title = f'{up_name[:-6]}_BDT'

    hist_base = root_file.Get(base_name)

    nbins = hist_base.GetNbinsX()
    bin_edges = [hist_base.GetBinLowEdge(i) for i in range(1, nbins + 2)]
    print(bin_edges)
    hist_up = root_file.Get(up_name)
    hist_down = root_file.Get(down_name)
    for i in range(1, hist_base.GetNbinsX() + 1):
        hist_up.SetBinError(i, 0)
        hist_down.SetBinError(i, 0)

    c1 = ROOT.TCanvas("c1", "Canvas", 800, 800)
    c1.Divide(1, 2)

    c1.cd(1)
    ROOT.gPad.SetPad(0, 0.3, 1, 1)
    ROOT.gPad.SetBottomMargin(0.02)
    hist_base.SetTitle(title)
    hist_base.SetMarkerStyle(1)
    hist_base.GetXaxis().SetLabelSize(0)
    hist_base.GetXaxis().SetTitleSize(0)
    hist_base.SetMarkerColor(ROOT.kBlack)
    hist_base.SetLineColor(ROOT.kBlack)
    hist_base.Draw("E1")

    hist_up.SetMarkerStyle(1)
    hist_up.SetMarkerColor(ROOT.kRed)
    hist_up.SetLineColor(ROOT.kRed)
    hist_up.Draw("E1 SAME")

    hist_down.SetMarkerStyle(1)
    hist_down.SetMarkerColor(ROOT.kBlue)
    hist_down.SetLineColor(ROOT.kBlue)
    hist_down.Draw("E1 SAME")

    legend = ROOT.TLegend(0.1, 0.7, 0.3, 0.9)
    legend.AddEntry(hist_base, "Nominal", "lep")
    legend.AddEntry(hist_up, "Up variation", "lep")
    legend.AddEntry(hist_down, "Down variation", "lep")
    legend.Draw()

    c1.cd(2)
    ROOT.gPad.SetPad(0, 0, 1, 0.3)
    ROOT.gPad.SetTopMargin(0.02)
    ROOT.gPad.SetBottomMargin(0.3)

    ratio_up = hist_up.Clone("ratio_up")
    ratio_down = hist_down.Clone("ratio_down")
    #ratio_up.Divide(hist_base)
    #ratio_down.Divide(hist_base)
    for i in range(1, hist_base.GetNbinsX() + 1):
        base_content = hist_base.GetBinContent(i)
        up_content = hist_up.GetBinContent(i)
        down_content = hist_down.GetBinContent(i)
        ratio_up.SetBinError(i, 0)
        ratio_down.SetBinError(i, 0)
        
        if base_content != 0 and base_content > 0.01:
            ratio_up.SetBinContent(i, up_content / base_content)
            ratio_down.SetBinContent(i, down_content / base_content)
        else:
            ratio_up.SetBinContent(i, 1)
            ratio_down.SetBinContent(i, 1)

    ratio_up.SetTitle("")
    ratio_down.SetTitle("")
    ratio_up.SetMinimum(0.67)
    ratio_up.SetMaximum(1.5)
    ratio_up.SetStats(0)
    ratio_down.SetStats(0)

    ratio_up.SetMarkerStyle(1)
    ratio_up.SetMarkerColor(ROOT.kRed)
    ratio_up.SetLineColor(ROOT.kRed)
    ratio_up.GetYaxis().SetTitle("Ratio")
    ratio_up.GetYaxis().SetNdivisions(505)
    ratio_up.GetYaxis().SetTitleSize(20)
    ratio_up.GetYaxis().SetTitleFont(43)
    ratio_up.GetYaxis().SetTitleOffset(1.55)
    ratio_up.GetYaxis().SetLabelFont(43)
    ratio_up.GetYaxis().SetLabelSize(15)
    ratio_up.GetXaxis().SetTitle("BDT Score")
    ratio_up.GetXaxis().SetTitleSize(20)
    ratio_up.GetXaxis().SetTitleFont(43)
    ratio_up.GetXaxis().SetTitleOffset(4.0)
    ratio_up.GetXaxis().SetLabelFont(43)
    ratio_up.GetXaxis().SetLabelSize(15)
    ratio_up.Draw("E1")

    ratio_down.SetMarkerStyle(1)
    ratio_down.SetMarkerColor(ROOT.kBlue)
    ratio_down.SetLineColor(ROOT.kBlue)
    ratio_down.Draw("E1 SAME")

    line = ROOT.TLine(bin_edges[0], 1, bin_edges[-1], 1)
    line.SetLineStyle(2)
    line.Draw()
    dir_path = os.path.dirname(file_path)
    outDir = f"{dir_path}/results/"
    uf.checkMakeDir(outDir)
    # png_path = f"{dir_path
    c1.SaveAs(outDir + f"{title}.png")
    print(f"success created {outDir}{title}.png")

def main():
    # file_path = "/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2018/v0baselineHardroSR_v81addSysSum/mc/variableHists_v0Basictraining1tau1l_VLLm600_6/combine/templatesForCombine1tau1l.root"
    # file_path = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/variableHists_v2BDT1tau0lBinC/combine/templatesForCombine1tau0l.root"
    # file_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v87LepPreSel_GammaRemovalBugFixed/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
    # file_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v87addPdfPSWeightSum/mc/variableHists_v0BDT1tau2l_newMCSample/combine/templatesForCombine1tau2l.root'
    file_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l_newMCSample/combine/templatesForCombine1tau2l.root'

    channel = "1tau2l"
    # channel = "1tau0l"
    
    ProcessNames = gq.proChannelDic[channel][:-1]
    SystematicsNames = [
        # 'QCDscale_Re_normalised',
        # 'QCDscale_Fa_normalised',
        # 'pdfAlphaS_normalised',
        'pdf_normalised',
        'ISR_normalised',
        'FSR_normalised',
    ]
    year = '2018'
    for ProcessName in ProcessNames:
        for SystematicsName in SystematicsNames:
            base_name = f"{ProcessName}_{channel}SR_BDT"
            up_name = f'{ProcessName}_{channel}SR_{SystematicsName}Up_BDT'
            down_name = f'{ProcessName}_{channel}SR_{SystematicsName}Down_BDT'
            print(base_name, up_name, down_name)
            StartPlotiing(file_path, base_name, up_name, down_name)

if __name__ == "__main__":
    main()