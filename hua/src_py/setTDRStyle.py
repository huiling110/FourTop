import ROOT

from ttttGlobleQuantity import lumiMap
import usefulFunc as uf

#https://twiki.cern.ch/twiki/bin/view/CMS/Internal/FigGuidelines

#https://twiki.cern.ch/twiki/pub/CMS/Internal/FigGuidelines/tdrstyle.py.txt

def setTDRStyle() :
  tdrStyle = ROOT.TStyle("tdrStyle","Style for P-TDR")

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

 # //Axis titles:
  tdrStyle.SetTitleColor(1,"XYZ")
  tdrStyle.SetTitleFont(42,"XYZ")
  tdrStyle.SetTitleSize(0.06,"XYZ")
  tdrStyle.SetTitleXOffset(0.9)
  tdrStyle.SetTitleYOffset(1.25)
 
#  // For the axis labels:

  tdrStyle.SetLabelColor(1, "XYZ")
  tdrStyle.SetLabelFont(42,"XYZ")
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

  tdrStyle.SetPaperSize(20.,20.)
  

  tdrStyle.cd()
  return tdrStyle

def addCMSTextToCan(canvas, x1=0.23, x2=0.35,x3=0.7, y=0.96, era = '2016'):
    can = canvas
     
    cmsTextFont = 61
    extraTextFont = 52
    cmsText = "CMS"
    extraText = "Preliminary " + era
    
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextAlign(31)
    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatex(x1, y, cmsText )
    latex.SetTextFont(extraTextFont)
    latex.SetTextSize(0.04*0.76)
    latex.DrawLatex(x2, y , extraText )
  
    lumiText = lumiMap[era] /1000
    lumiText_s = '{0:.1f}'.format(lumiText)
    isRun3 = uf.isRun3Era(era)
    energy = '13'
    if isRun3:
        energy = '13.6'
    lumiText_s = lumiText_s + ' fb^{-1}('+ energy +'TeV)'
    # print(lumiText)
    latex2 = ROOT.TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.04)
    latex2.SetTextAlign(31)
    latex2.SetTextFont(42)  
    # latex2.DrawLatex(x2+0.6, y, lumiText_s )
    latex2.DrawLatex( x3, y, lumiText_s )
    
def addCMSTextToPad(canvas,  era = '2016'):
    # can = canvas
    canvas.Update()
   
    # x1 = ROOT.gPad.GetUxmin()
    # y =  ROOT.gPad.GetUymax()
    x1 = canvas.GetLeftMargin() + 0.06
    y = 1- canvas.GetTopMargin() + 0.01
    x2 = x1+0.17
    x3 = x1+0.69
    
    cmsTextFont = 61
    extraTextFont = 52
    cmsText = "CMS"
    extraText = "Preliminary " + era
    
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextAlign(31)
    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatex(x1, y, cmsText )
    latex.SetTextFont(extraTextFont)
    latex.SetTextSize(0.04*0.76)
    latex.DrawLatex(x2, y , extraText )
  
    lumiText = lumiMap[era] /1000
    lumiText_s = '{0:.1f}'.format(lumiText)
    isRun3 = uf.isRun3Era(era)
    energy = '13'
    if isRun3:
        energy = '13.6'
    lumiText_s = lumiText_s + ' fb^{-1}('+ energy +'TeV)'
    latex2 = ROOT.TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.04)
    latex2.SetTextAlign(31)
    latex2.SetTextFont(42)  
    latex2.DrawLatex( x3, y, lumiText_s )
    
    canvas.Update()


def setMyStyle():
  myStyle = ROOT.TStyle("tdrStyle","Style for P-TDR")

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
#   myStyle.SetPadBottomMargin(0.13)
  myStyle.SetPadBottomMargin(0.16)
  myStyle.SetPadLeftMargin(0.15)
  myStyle.SetPadRightMargin(0.1)
  
    #hist settings
  myStyle.SetHistLineColor(ROOT.kBlack)
#   myStyle.SetHistLineStyle(0)
  myStyle.SetHistLineWidth(2)
  myStyle.SetEndErrorSize(2)
#   myStyle.SetErrorX(0.) #error bar no x 
  myStyle.SetMarkerStyle(20)
  myStyle.SetMarkerSize(2)

#   myStyle.SetOptFit(1)
#   myStyle.SetFitFormat("5.4g")
#   myStyle.SetFuncColor(2)
#   myStyle.SetFuncStyle(1)
#   myStyle.SetFuncWidth(1)

#   myStyle.SetOptDate(0)

#   myStyle.SetOptFile(0)
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

#  # //Axis titles:
#   myStyle.SetTitleColor(1,"XYZ")
#   myStyle.SetTitleFont(42,"XYZ")
  myStyle.SetTitleSize(0.06,"XYZ")
#   myStyle.SetTitleXOffset(0.9)
  myStyle.SetTitleYOffset(.9)
 

  myStyle.SetLabelColor(1, "XYZ")
  myStyle.SetLabelFont(42,"XYZ")
  myStyle.SetLabelOffset(0.007, "XYZ")
  myStyle.SetLabelSize(0.04, "XYZ")

#   myStyle.SetAxisColor(1, "XYZ")
#   myStyle.SetStripDecimals(ROOT.kTRUE)
#   myStyle.SetTickLength(0.03, "XYZ")
#   myStyle.SetNdivisions(510, "XYZ")
#   myStyle.SetPadTickX(1)  
#   myStyle.SetPadTickY(1)


#   myStyle.SetOptLogx(0)
#   myStyle.SetOptLogy(0)
#   myStyle.SetOptLogz(0)

#   myStyle.SetPaperSize(20.,20.)
  
#   myStyle.cd()
  return myStyle


def getMyLegend(x1, x2, y1, y2):
    legend = ROOT.TLegend(x1, x2, y1, y2)
    legend.SetFillColor(0)  # transparent
    # legend.SetBorderSize(1)  # border size
    legend.SetBorderSize(0)  # border size
    # legend.SetTextSize(0.07)  # text size
    legend.SetTextFont(42)  # font style
    # legend.SetTextFont(82)  # font style
    legend.SetFillColor(0)
    legend.SetFillStyle(0) 
    return legend
    