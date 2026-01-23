"""
ROOT TDR Style Configuration
============================

Set up CMS TDR-compliant plotting style and add CMS labels.

Functions:
    setTDRStyle - Set TDR style for ROOT plots
    setMyStyle - Set custom style with grid
    addCMSTextToPad - Add CMS preliminary label to pad
    addCMSTextToCan - Add CMS preliminary label to canvas
    getMyLegend - Create styled legend

Usage:
    from fourtop.plotting.style import setTDRStyle, addCMSTextToPad, getMyLegend

    setTDRStyle()
    # ... create plots ...
    addCMSTextToPad(canvas, era='2018')
"""

from typing import Optional
import ROOT

from fourtop.constants.physics import lumiMap
from fourtop.utils.process import isRun3


def setTDRStyle() -> ROOT.TStyle:
    """
    Set TDR (Technical Design Report) style for ROOT plots.

    Reference: https://twiki.cern.ch/twiki/bin/view/CMS/Internal/FigGuidelines

    Returns:
        ROOT.TStyle configured with TDR settings
    """
    tdrStyle = ROOT.TStyle("tdrStyle", "Style for P-TDR")

    tdrStyle.SetCanvasBorderMode(0)
    tdrStyle.SetCanvasColor(ROOT.kWhite)
    tdrStyle.SetCanvasDefH(600)
    tdrStyle.SetCanvasDefW(600)
    tdrStyle.SetCanvasDefX(0)
    tdrStyle.SetCanvasDefY(0)

    tdrStyle.SetPadBorderMode(0)
    tdrStyle.SetPadColor(ROOT.kWhite)

    tdrStyle.SetFrameBorderMode(0)
    tdrStyle.SetFrameBorderSize(1)
    tdrStyle.SetFrameFillColor(0)
    tdrStyle.SetFrameFillStyle(0)
    tdrStyle.SetFrameLineColor(1)
    tdrStyle.SetFrameLineStyle(1)
    tdrStyle.SetFrameLineWidth(1)

    tdrStyle.SetHistLineColor(ROOT.kBlack)
    tdrStyle.SetHistLineStyle(0)
    tdrStyle.SetHistLineWidth(2)

    tdrStyle.SetEndErrorSize(2)
    tdrStyle.SetErrorX(0.)

    tdrStyle.SetMarkerStyle(20)
    tdrStyle.SetMarkerSize(2)

    tdrStyle.SetOptFit(1)
    tdrStyle.SetFitFormat("5.4g")
    tdrStyle.SetFuncColor(2)
    tdrStyle.SetFuncStyle(1)
    tdrStyle.SetFuncWidth(1)

    tdrStyle.SetOptDate(0)

    tdrStyle.SetOptFile(0)
    tdrStyle.SetOptStat(0)
    tdrStyle.SetStatColor(ROOT.kWhite)
    tdrStyle.SetStatFont(42)
    tdrStyle.SetStatFontSize(0.025)
    tdrStyle.SetStatTextColor(1)
    tdrStyle.SetStatFormat("6.4g")
    tdrStyle.SetStatBorderSize(1)
    tdrStyle.SetStatH(0.1)
    tdrStyle.SetStatW(0.15)

    tdrStyle.SetPadTopMargin(0.07)
    tdrStyle.SetPadBottomMargin(0.13)
    tdrStyle.SetPadLeftMargin(0.16)
    tdrStyle.SetPadRightMargin(0.03)

    tdrStyle.SetOptTitle(0)
    tdrStyle.SetTitleFont(42)
    tdrStyle.SetTitleColor(1)
    tdrStyle.SetTitleTextColor(1)
    tdrStyle.SetTitleFillColor(10)
    tdrStyle.SetTitleFontSize(0.05)

    # Axis titles
    tdrStyle.SetTitleColor(1, "XYZ")
    tdrStyle.SetTitleFont(42, "XYZ")
    tdrStyle.SetTitleSize(0.06, "XYZ")
    tdrStyle.SetTitleXOffset(0.9)
    tdrStyle.SetTitleYOffset(1.25)

    # Axis labels
    tdrStyle.SetLabelColor(1, "XYZ")
    tdrStyle.SetLabelFont(42, "XYZ")
    tdrStyle.SetLabelOffset(0.007, "XYZ")
    tdrStyle.SetLabelSize(0.05, "XYZ")

    tdrStyle.SetAxisColor(1, "XYZ")
    tdrStyle.SetStripDecimals(ROOT.kTRUE)
    tdrStyle.SetTickLength(0.03, "XYZ")
    tdrStyle.SetNdivisions(510, "XYZ")
    tdrStyle.SetPadTickX(1)
    tdrStyle.SetPadTickY(1)

    tdrStyle.SetOptLogx(0)
    tdrStyle.SetOptLogy(0)
    tdrStyle.SetOptLogz(0)

    tdrStyle.SetPaperSize(20., 20.)

    tdrStyle.cd()
    return tdrStyle


def setMyStyle() -> ROOT.TStyle:
    """
    Set custom style with grid enabled.

    Returns:
        ROOT.TStyle configured with custom settings
    """
    myStyle = ROOT.TStyle("tdrStyle", "Style for P-TDR")

    myStyle.SetCanvasBorderMode(0)
    myStyle.SetCanvasColor(ROOT.kWhite)
    myStyle.SetCanvasDefH(600)
    myStyle.SetCanvasDefW(600)
    myStyle.SetCanvasDefX(0)
    myStyle.SetCanvasDefY(0)

    myStyle.SetPadBorderMode(0)
    myStyle.SetPadColor(ROOT.kWhite)
    myStyle.SetPadGridX(ROOT.kFALSE)
    myStyle.SetPadGridY(ROOT.kTRUE)

    myStyle.SetFrameBorderMode(0)
    myStyle.SetFrameBorderSize(1)
    myStyle.SetFrameFillColor(0)
    myStyle.SetFrameFillStyle(0)
    myStyle.SetFrameLineColor(1)
    myStyle.SetFrameLineStyle(1)
    myStyle.SetFrameLineWidth(1)

    myStyle.SetPadTopMargin(0.07)
    myStyle.SetPadBottomMargin(0.16)
    myStyle.SetPadLeftMargin(0.15)
    myStyle.SetPadRightMargin(0.1)

    # Hist settings
    myStyle.SetHistLineColor(ROOT.kBlack)
    myStyle.SetHistLineWidth(2)
    myStyle.SetEndErrorSize(2)
    myStyle.SetMarkerStyle(20)
    myStyle.SetMarkerSize(2)

    myStyle.SetOptStat(0)
    myStyle.SetStatColor(ROOT.kWhite)
    myStyle.SetStatFont(42)
    myStyle.SetStatFontSize(0.025)
    myStyle.SetStatTextColor(1)
    myStyle.SetStatFormat("6.4g")
    myStyle.SetStatBorderSize(1)
    myStyle.SetStatH(0.1)
    myStyle.SetStatW(0.15)

    myStyle.SetOptTitle(0)
    myStyle.SetTitleFont(42)
    myStyle.SetTitleColor(1)
    myStyle.SetTitleTextColor(1)
    myStyle.SetTitleFillColor(10)
    myStyle.SetTitleFontSize(0.05)

    myStyle.SetTitleSize(0.06, "XYZ")
    myStyle.SetTitleYOffset(.9)

    myStyle.SetLabelColor(1, "XYZ")
    myStyle.SetLabelFont(42, "XYZ")
    myStyle.SetLabelOffset(0.007, "XYZ")
    myStyle.SetLabelSize(0.04, "XYZ")

    return myStyle


def addCMSTextToCan(
    canvas: ROOT.TCanvas,
    x1: float = 0.23,
    x2: float = 0.35,
    x3: float = 0.7,
    y: float = 0.96,
    era: str = '2016'
) -> None:
    """
    Add CMS preliminary label to canvas with luminosity.

    Args:
        canvas: ROOT canvas
        x1: x position of "CMS" text
        x2: x position of "Preliminary" text
        x3: x position of luminosity text
        y: y position of all text
        era: Era string (e.g., '2018', '2022')
    """
    cmsTextFont = 61
    extraTextFont = 52
    cmsText = "CMS"
    extraText = "Preliminary " + era

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextAlign(31)
    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatex(x1, y, cmsText)
    latex.SetTextFont(extraTextFont)
    latex.SetTextSize(0.04 * 0.76)
    latex.DrawLatex(x2, y, extraText)

    lumiText = lumiMap[era] / 1000
    lumiText_s = '{0:.0f}'.format(lumiText)
    is_run3 = isRun3(era)
    energy = '13.6' if is_run3 else '13'
    lumiText_s = lumiText_s + ' fb^{-1}(' + energy + 'TeV)'

    latex2 = ROOT.TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.04)
    latex2.SetTextAlign(31)
    latex2.SetTextFont(42)
    latex2.DrawLatex(x3, y, lumiText_s)


def addCMSTextToPad(
    canvas: ROOT.TCanvas,
    era: str = '2016',
    preliminary: bool = True,
    show_era_in_label: bool = True
) -> None:
    """
    Add CMS label to pad with luminosity.

    Automatically positions text based on pad margins.

    Args:
        canvas: ROOT canvas/pad
        era: Era string (e.g., '2018', '2022', 'Run2')
        preliminary: If True, show "Preliminary"; if False, CMS only (for publication)
        show_era_in_label: If True, show era after "Preliminary"
    """
    canvas.Update()

    x1 = canvas.GetLeftMargin() + 0.06
    y = 1 - canvas.GetTopMargin() + 0.01
    x2 = x1 + 0.17
    x3 = x1 + 0.69

    cmsTextFont = 61
    extraTextFont = 52
    cmsText = "CMS"

    # Build extra text based on options
    if preliminary:
        if show_era_in_label:
            extraText = "Preliminary " + era
        else:
            extraText = "Preliminary"
    else:
        extraText = ""  # No extra text for publication

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextAlign(11)  # Align the text to the top-left
    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatexNDC(0.15, y, cmsText)

    if extraText:
        latex1 = ROOT.TLatex()
        latex1.SetTextFont(extraTextFont)
        latex1.SetTextSize(0.04 * 0.76)
        latex1.DrawLatexNDC(0.15 + 0.10, y, extraText)

    lumiText = lumiMap[era] / 1000
    lumiText_s = '{0:.0f}'.format(lumiText)
    is_run3 = isRun3(era)
    energy = '13.6' if is_run3 else '13'
    lumiText_s = lumiText_s + ' fb^{-1}(' + energy + 'TeV)'

    latex2 = ROOT.TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.04)
    latex2.SetTextAlign(31)
    latex2.SetTextFont(42)
    latex2.DrawLatex(x3, y, lumiText_s)

    canvas.Update()


def getMyLegend(x1: float, x2: float, y1: float, y2: float) -> ROOT.TLegend:
    """
    Create a styled legend with transparent background.

    Args:
        x1: Left edge (NDC)
        x2: Right edge (NDC)
        y1: Bottom edge (NDC)
        y2: Top edge (NDC)

    Returns:
        Configured ROOT.TLegend
    """
    legend = ROOT.TLegend(x1, x2, y1, y2)
    legend.SetFillColor(0)  # transparent
    legend.SetBorderSize(0)  # border size
    legend.SetTextFont(42)  # font style
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    return legend


def addRegionLabel(
    canvas: ROOT.TCanvas,
    region: str,
    x: float = 0.20,
    y: float = 0.68
) -> None:
    """
    Add region label to plot (e.g., "SR 1τ_h0ℓ").

    Args:
        canvas: ROOT canvas/pad
        region: Region code (e.g., 'SR1tau0l') - will be formatted
        x: x position (NDC)
        y: y position (NDC)
    """
    from fourtop.plotting.labels import get_region_label

    canvas.cd()
    region_text = get_region_label(region)

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextAlign(11)  # Left-aligned
    latex.SetTextSize(0.035)
    latex.SetTextFont(42)
    latex.DrawLatexNDC(x, y, region_text)

    canvas.Update()


def addFitTypeLabel(
    canvas: ROOT.TCanvas,
    is_postfit: bool,
    x: float = 0.20,
    y: float = 0.53
) -> None:
    """
    Add fit type label to plot ("Pre-fit" or "Post-fit").

    Args:
        canvas: ROOT canvas/pad
        is_postfit: True for post-fit, False for pre-fit
        x: x position (NDC)
        y: y position (NDC)
    """
    from fourtop.plotting.labels import get_fit_type_label

    canvas.cd()
    fit_text = get_fit_type_label(is_postfit)

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextAlign(11)  # Left-aligned
    latex.SetTextSize(0.035)
    latex.SetTextFont(42)
    latex.DrawLatexNDC(x, y, fit_text)

    canvas.Update()
