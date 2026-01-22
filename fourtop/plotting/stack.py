"""
Stack Plot Builder
==================

Functions for building stacked histogram plots for data/MC comparison.

Usage:
    from fourtop.plotting.stack import getHists, makeStackPlot, getErrorPlot
"""

import math
from array import array
from typing import Dict, List, Tuple, Optional
import ROOT

from fourtop.utils.process import isData, isBG

# =============================================================================
# Color Scheme
# =============================================================================

#: Standard color scheme for physics processes
COLOUR_PER_SAMPLE: Dict[str, int] = {
    'tttt': ROOT.kBlue,
    'VLLm600': ROOT.TColor.GetColor("#D10363"),
    'VLLm800': ROOT.TColor.GetColor("#D10363"),
    'VLLm700': ROOT.TColor.GetColor("#D10363"),
    'tt': ROOT.TColor.GetColor("#f03b20"),
    'ttbb': ROOT.TColor.GetColor("#e6550d"),  # TTBB: darker orange
    'qcd': ROOT.TColor.GetColor("#ffeda0"),
    'ttX': ROOT.TColor.GetColor("#fc9272"),
    'singleTop': ROOT.TColor.GetColor("#91bfdb"),
    'VV': ROOT.TColor.GetColor("#edf8b1"),
    'WJets': ROOT.TColor.GetColor("#998ec3"),
    'fakeTau': ROOT.TColor.GetColor("#fec44f"),
    'XGamma': ROOT.TColor.GetColor("#d73027"),
    'VVV': ROOT.TColor.GetColor("#4575b4"),
    'Higgs': ROOT.TColor.GetColor("#313695"),
    'DY': ROOT.TColor.GetColor("#313695"),
    'fakeLepton': ROOT.TColor.GetColor("#fec44f"),
    'Minor': ROOT.TColor.GetColor("#edf8b1"),
    'ttH': ROOT.TColor.GetColor("#f03b20"),
    'ttW': ROOT.TColor.GetColor("#f03b20"),
    'ttZ': ROOT.TColor.GetColor("#f03b20"),
    'ttG': ROOT.TColor.GetColor("#f03b20"),
    'fakeTauMC': ROOT.TColor.GetColor("#ffeda0"),
}


# =============================================================================
# Core Functions
# =============================================================================

def getHists(
    nominal: Dict[str, ROOT.TH1],
    legendOrder: List[str],
    ifBlind: bool,
    doSystmatic: bool = False,
    ifStackSignal: bool = False,
    ifVLL: str = '',
    sysHists: Dict = {},
    if1tau2l: bool = False
) -> Tuple[ROOT.TH1, ROOT.TH1, ROOT.TH1, ROOT.TH1, ROOT.THStack, ROOT.TH1]:
    """
    Build stacked histograms from nominal process histograms.

    Args:
        nominal: Dictionary of histograms by process
        legendOrder: Order of processes in legend/stack
        ifBlind: If True, hide data in SR
        doSystmatic: If True, process systematic variations
        ifStackSignal: If True, include signal in stack
        ifVLL: VLL signal name (if VLL analysis)
        sysHists: Systematic variation histograms
        if1tau2l: If True, use leptonSum instead of jetHT for data

    Returns:
        Tuple of (dataHist, systsUp, systsDown, sumHist, stack, signal)
    """
    keyList = list(nominal.keys())

    sumHist = nominal[keyList[0]].Clone()
    sumHist.Reset()
    systsUp = nominal[keyList[0]].Clone("systsUp")
    systsUp.Reset()
    systsDown = nominal[keyList[0]].Clone("systsDown")
    systsDown.Reset()
    dataHist = None
    stack = ROOT.THStack('stack', 'stack')

    # Process in reverse order for stack
    legendOrder.reverse()
    for i in legendOrder:
        if isData(i):
            if not ifBlind:
                data_key = 'leptonSum' if if1tau2l else 'jetHT'
                if data_key in nominal:
                    dataHist = nominal[data_key].Clone()
                    dataHist.SetMarkerStyle(20)
                    dataHist.SetMarkerSize(1.2)
                    dataHist.SetMarkerColor(ROOT.kBlack)
                    dataHist.SetLineColor(ROOT.kBlack)
                    dataHist.SetTitleSize(0.0)
            continue

        if isBG(i, ifVLL) == 3:
            continue
        if isBG(i, ifVLL) == 1 and (not ifStackSignal):
            continue

        color = COLOUR_PER_SAMPLE.get(i, ROOT.kGray)
        nominal[i].SetFillColor(color)
        nominal[i].SetLineColor(ROOT.kBlack)
        nominal[i].SetLineWidth(1)
        nominal[i].GetXaxis().SetTitleSize(0.01)
        nominal[i].GetXaxis().SetLabelSize(0.0)
        nominal[i].GetYaxis().SetTitle('Events')
        sumHist.Add(nominal[i])
        stack.Add(nominal[i])

        if sysHists and i in sysHists:
            print('Calculating systematics for:', i)
            tempUp, tempDown = getSystVariation(nominal[i], sysHists[i])
            systsUp.Add(tempUp)
            systsDown.Add(tempDown)

    legendOrder.reverse()

    # Create signal histogram
    if 'tttt' in nominal or ifVLL:
        signal_key = ifVLL if ifVLL else 'tttt'
        if signal_key in nominal:
            signal = nominal[signal_key].Clone()
            signal.SetLineColor(COLOUR_PER_SAMPLE.get(signal_key, ROOT.kBlue))
        else:
            signal = nominal['tt'].Clone()
            signal.Reset()
    else:
        signal = nominal['tt'].Clone()
        signal.Reset()

    return dataHist, systsUp, systsDown, sumHist, stack, signal


def getSystVariation(
    nominalHist: ROOT.TH1,
    systHists: Dict[str, ROOT.TH1]
) -> Tuple[ROOT.TH1, ROOT.TH1]:
    """
    Calculate total systematic up/down variations.

    Computes quadrature sum of systematic uncertainties from all sources.

    Args:
        nominalHist: Nominal histogram for one process
        systHists: Dictionary of systematic histograms (keys like 'CMS_pileup_up')

    Returns:
        Tuple of (systHistUp, systHistDown) with total uncertainties
    """
    systHistUp = nominalHist.Clone("up")
    systHistDown = nominalHist.Clone("down")
    systHistUp.Reset()
    systHistDown.Reset()

    for systHi in systHists.keys():
        syst = systHists[systHi].Clone()
        syst.Add(nominalHist, -1)
        for i in range(1, syst.GetXaxis().GetNbins() + 1):
            if nominalHist.GetBinContent(i) <= 0.:
                continue
            if "Up" in syst.GetName():
                systHistUp.SetBinContent(
                    i, systHistUp.GetBinContent(i) + syst.GetBinContent(i) ** 2
                )
            else:
                systHistDown.SetBinContent(
                    i, systHistDown.GetBinContent(i) + syst.GetBinContent(i) ** 2
                )
            # Warn for large variations
            if abs(syst.GetBinContent(i) / nominalHist.GetBinContent(i)) > 0.9:
                print(f'WARNING: systematic variation > 90% for {syst.GetName()} bin {i}')

    return systHistUp, systHistDown


def addStatisticUncer(
    sumHist: ROOT.TH1,
    systsUp: ROOT.TH1,
    systsDown: ROOT.TH1
) -> Tuple[ROOT.TH1, ROOT.TH1]:
    """
    Add statistical uncertainty to systematic uncertainty.

    Args:
        sumHist: Summed MC histogram
        systsUp: Systematic up variation
        systsDown: Systematic down variation

    Returns:
        Updated (systsUp, systsDown)
    """
    for i in range(1, sumHist.GetXaxis().GetNbins() + 1):
        stat_err_sq = sumHist.GetBinError(i) ** 2
        systsUp.SetBinContent(
            i, math.sqrt(systsUp.GetBinContent(i) + stat_err_sq)
        )
        systsDown.SetBinContent(
            i, math.sqrt(systsDown.GetBinContent(i) + stat_err_sq)
        )
    return systsUp, systsDown


def getErrorPlot(
    totalMC: ROOT.TH1,
    systUp: ROOT.TH1,
    systDown: ROOT.TH1,
    isRatio: bool = False
) -> ROOT.TGraphAsymmErrors:
    """
    Create asymmetric error plot for uncertainty band.

    Args:
        totalMC: Total MC histogram
        systUp: Upper systematic variation
        systDown: Lower systematic variation
        isRatio: If True, create ratio plot (centered at 1)

    Returns:
        TGraphAsymmErrors for uncertainty band
    """
    x = array('d', [])
    y = array('d', [])
    exl = array('d', [])
    exh = array('d', [])
    eyl = array('d', [])
    eyh = array('d', [])

    xAxis = systUp.GetXaxis()
    for i in range(1, xAxis.GetNbins() + 1):
        x.append(xAxis.GetBinCenter(i))
        y.append(1. if isRatio else totalMC.GetBinContent(i))
        exl.append(xAxis.GetBinCenter(i) - xAxis.GetBinLowEdge(i))
        exh.append(xAxis.GetBinLowEdge(i) + xAxis.GetBinWidth(i) - xAxis.GetBinCenter(i))

        if not isRatio:
            eyl.append(systDown.GetBinContent(i))
            eyh.append(systUp.GetBinContent(i))
        else:
            mc_content = totalMC.GetBinContent(i)
            if mc_content != 0:
                eyl.append(systDown.GetBinContent(i) / mc_content)
                eyh.append(systUp.GetBinContent(i) / mc_content)
            else:
                eyl.append(0)
                eyh.append(0)

    errors = ROOT.TGraphAsymmErrors(xAxis.GetNbins(), x, y, exl, exh, eyl, eyh)
    errors.SetFillStyle(3013)
    errors.SetFillColor(14)
    errors.GetXaxis().SetLabelSize(0.0)

    return errors


def getHistToData(
    dataHist: Optional[ROOT.TH1],
    sumHist: ROOT.TH1
) -> ROOT.TH1:
    """
    Create data/MC ratio histogram.

    Args:
        dataHist: Data histogram (or None if blinded)
        sumHist: MC sum histogram

    Returns:
        Ratio histogram
    """
    if dataHist:
        sumHistoData = dataHist.Clone(dataHist.GetName() + "_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)
    else:
        sumHistoData = sumHist.Clone()
        sumHistoData.Reset()

    sumHistoData.GetYaxis().SetTitle("Data/pred.")
    sumHistoData.SetMinimum(0.45)
    sumHistoData.SetMaximum(1.55)
    sumHistoData.GetXaxis().SetTitle(sumHist.GetTitle())
    sumHistoData.GetXaxis().SetTitleSize(0.05)
    sumHistoData.GetYaxis().SetNdivisions(6)
    sumHistoData.SetTitle("")

    return sumHistoData


def getIntegral(histogram: ROOT.TH1) -> float:
    """
    Get total integral including overflow.

    Args:
        histogram: ROOT histogram

    Returns:
        Integral value
    """
    return histogram.Integral(0, histogram.GetNbinsX() + 1, "overflow")


def setUpStack(
    canvy: ROOT.TCanvas,
    stack: ROOT.THStack,
    sumMax: float,
    signalMax: float,
    ifLogy: bool = False
) -> None:
    """
    Configure stack plot axes and range.

    Args:
        canvy: ROOT canvas
        stack: THStack to configure
        sumMax: Maximum of summed MC
        signalMax: Maximum of scaled signal
        ifLogy: If True, use log scale
    """
    maxi = 1.7 * max(sumMax, signalMax)
    if maxi <= 0:
        return
    if ifLogy:
        maxi = 10 * maxi

    stack.SetMaximum(maxi)
    if ifLogy:
        stack.SetMinimum(0.5)

    stack.Draw("hist")
    stack.GetXaxis().SetLabelSize(0.0)
    stack.GetYaxis().SetTitle('Events')
    stack.GetYaxis().SetTitleOffset(1.2)
    stack.GetYaxis().SetTitleSize(0.05)

    canvy.Modified()
    canvy.Update()
