#Script used to Perform Data/MC comparsion 
#
###########################################################################
from ROOT import *
#import ROOT 
from setTDRStyle import setTDRStyle
from random import *
from array import *
import math
import sys,os
#A bunch of global variables that are used in the drawing

gROOT.SetBatch()
setTDRStyle()

region =str(sys.argv[1])


gStyle.SetOptStat(0)
latex = TLatex()
latex.SetNDC()
latex.SetTextAlign(31)
plotname=""
cmsTextFont = 61
#extraTextFont = 52
extraTextFont = 70
LumiText = ""


latex2 = TLatex();
latex2.SetNDC();
latex2.SetTextSize(0.05);
#latex2.SetTextSize(0.04);
latex2.SetTextAlign(31);

if "2016" in region:
	LumiText=  "36.3 fb^{-1} (13TeV)"
elif "2017" in region and "Muon" in region:
	LumiText= "41.5 fb^{-1} (13TeV)"
elif "2017" in region and "Ele" in region:
        LumiText= "36.7 fb^{-1} (13TeV)"
elif "2018" in region:
        LumiText= "59.8 fb^{-1} (13TeV)"
elif "RunII" in region and "Muon" in region:
	LumiText= "137.6 fb^{-1} (13TeV)"
elif "RunII" in region and "Ele" in region:
	LumiText= "132.8 fb^{-1} (13TeV)"

text2=""
if "Mu" in region:
	text2 = TLatex(0.45,0.98, "#mu channel")
elif "Ele" in region:
	text2 = TLatex(0.45,0.98, "e channel")
else:
	text2 = TLatex(0.45,0.98, "#mu+e channel")
text2.SetNDC()
text2.SetTextAlign(13)
text2.SetX(0.18)
text2.SetY(0.92)
text2.SetTextFont(42)
#text2.SetTextSize(0.035)
text2.SetTextSize(0.05)


#leggy = TLegend(0.75,0.75,0.9,0.9)
leggy = TLegend(0.5,0.75,0.9,0.9)


cmsText = "CMS"
#extraText = "Preliminary"
extraText = ""


allFileDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/"+region+"/"
#allsamples =["ZZ","WW","WZ","WJetsHT","ST","SaT","QCD","TT","RH_1200","RH_2000","RH_2600","Data"]
#allMCsamples =["ZZ","WW","WZ","WJetsHT","ST","SaT","QCD","TT","RH_1200","RH_2000","RH_2600"]
allsamples =["ZZ","WW","WZ","WJetsHT","SingleTop","QCD","TT","RH_1200","RH_2000","RH_2600","Data"]
allMCsamples =["ZZ","WW","WZ","WJetsHT","SingleTop","QCD","TT","RH_1200","RH_2000","RH_2600"]
#allsamples =["ZZ","WW","WZ","WJetsHT","ST","SaT","QCD","ttbar","RH_1400","RH_2000","RH_2600","Data"]
#vartodrawsys=["M_Mass_bstar","M_softdropmass_BoostedJet","M_Pt_BoostedJet","M_Pt_Top"]
#vartodrawsys=["M_Mass_bstar","M_softdropmass_BoostedJet","met"]
#vartodrawsys=["M_Mass_bstar","M_softdropmass_BoostedJet"]
vartodrawsys=["M_Mass_bstar"]
#vartodrawsys=["M_Pt_Top"]
sampletodrawsys=["TT","RH_2000","QCD","RH_1200","RH_3000","allbkg"]
#sampletodrawsys=["TT"]

DoJetSys=True
DoJetmassSys=True
#DoJetSys=False
#DoJetmassSys=False
#vartodraw=["M_Mass_bstar""M_softdropmasscorr_BoostedJet","WOverTop_pT","M_relpt_Jet","M_DeltaRLeptonClostJet"]
vartodraw=["M_Mass_bstar"]
#vartodraw=["M_Pt_Top"]
#vartodraw=["M_softdropmasscorr_BoostedJet","M_Phi_BoostedJet","M_Phi_Lepton","M_Phi_BJet","Met_type1PF_phi","HT","ST","DeltaRPhivboostedjet","DeltaRPhitW","DeltaRPhilv","M_nBJet","M_DeltaRChosedBJetLepton","M_softdropmass_BoostedJet","M_Mass_BJet","M_Mass_LeadBJet","M_Mass_BoostedJet","M_Mass_W","M_Pt_Top","M_Pt_Topleadjet","M_prunedmass_BoostedJet","M_tau21_BoostedJet","M_tau32_BoostedJet","met","mTW","M_Pt_BoostedJet","M_Pt_BJet","M_Pt_LeadBJet","M_Pt_Lepton","M_Mass_Top","M_Mass_Topleadjet","M_Pt_W","M_Mass_bstar","M_Mass_bstarleadjet","M_Eta_BoostedJet","M_Eta_BJet","M_Eta_LeadBJet","M_Eta_Lepton"]
xtitlepervar={"WOverTop_pT":"p_{T}^{(W)}/p_{T}^{(Top)}[GeV]","Met_type1PF_phi": "met_Phi","M_relpt_Jet":"p_{Tmin}^{rel}(l,jet)","M_DeltaRLeptonClostJet":"#DeltaR_{min}(lepton,jet)","HT":"H_{T}[GeV]","ST":"S_{T}[GeV]","DeltaRPhivboostedjet":"DeltaPhi(v,Wqq)","DeltaRPhitW":"DeltaPhi(top,Wqq)","DeltaRPhilv":"DeltaPhi(lepton,v)","M_nBJet":"Nbjet","M_DeltaRChosedBJetLepton":"#DeltaR(lepton,jet)","M_softdropmasscorr_BoostedJet":"boostedjet_softdrop_mass(Wtag)[GeV]","M_softdropmass_BoostedJet":"boostedjet_softdrop_mass[GeV]","M_Mass_BJet":"Bjet_mass[GeV]","M_Mass_LeadBJet":"LeadBjet_mass[GeV]","M_Mass_BoostedJet":"boostedjet_mass[GeV]","M_Mass_W":"M_{W}[GeV]","M_Pt_Top":"p_{T}^{(top)}[GeV]","M_Pt_Topleadjet":"p_{T}^{(topleading)}[GeV]","M_prunedmass_BoostedJet":"boostedjet_pruned_mass[GeV]","M_tau21_BoostedJet":"boostedjet_#tau_{21}","M_tau32_BoostedJet":"boostedjet_#tau_{32}","met":"E_{T}^{miss}[GeV]","mTW":"mTW","M_Phi_BoostedJet":"#phi^{(ak8_jet)}[GeV]","M_Pt_BoostedJet":"p_{T}^{(ak8_jet)}[GeV]","M_Pt_BJet":"p_{T}^{(ak4_jet)}[GeV]","M_Phi_BJet":"#phi^{(ak4_jet)}[GeV]","M_Pt_LeadBJet":"p_{T}^{(Leadak4_jet)}[GeV]","M_Pt_Lepton":"p_{T}^{(lepton)}[GeV]","M_Phi_Lepton":"#phi^{(lepton)}[GeV]","M_Mass_Top":"M_{top}[GeV]","M_Mass_Topleadjet":"M_{topwithleadjet}[GeV]","M_Pt_W":"p_{T}(W)[GeV]","M_Mass_bstar":"M_{tW}[GeV]","M_Mass_bstarleadjet":"M_{tW_withleadjet}[GeV]","M_Eta_BoostedJet":"#eta^{(ak8_jet)}","M_Eta_BJet":"#eta^{(ak4_jet)}","M_Eta_LeadBJet":"#eta^{(Leadak4_jet)}","M_Eta_Lepton":"#eta^{(lepton)}","M_Pt_bstar":"p_{T}^{(tW)}[GeV]"}
legendOrder=["ZZ","WW","WZ","WJetsHT","SingleTop","QCD","TT"]
#systs = ["Toppt","bTag","PU","LSF","mistag","Trig","PDF","WSF","JES","JER"]
#systs = ["bTag","PU","LSF","mistag","Trig","PDF","WSF","Toppt_a","Toppt_b","Toptag"]
#systs = ["bTag_bc","bTag_udsg","PU","LSF","Trig","PDFHess","Toppt_a","Toppt_b","topsfsemimerged","topsfunmerged","topsfmerged"]
systs = ["bTag_bc","bTag_udsg","PU","LepIDSF","LepRecoSF","Trig","PDFHess","WSF","Toppt_b","topsfsemimerged","topsfunmerged","topsfmerged"]
#colourPerSample = {"WJetsHT":kPink+1,"WJets":kPink+1,"QCD":kGreen+2,"TT":kRed,"WW":kOrange+7,"WZ":kOrange,"ZZ":kOrange-7,"ST":kGray,"SaT":kGray+2,"WJetsToQQ_HT-600ToInf":kPink,"RH_1200":kTeal,"RH_2000":kRed+1,"RH_2600":kBlue,"Data":kBlack,"ttbar":kRed}
colourPerSample = {"TT":kRed,"QCD":kGreen,"othbkg_lept":kOrange,"ST":kGray,"SaT":kGray+1,"RH_1200":kBlue,"RH_2000":kMagenta,"RH_2600":kRed,"Data":kBlack,"WJetsHT":kOrange,"WW":kOrange+1,"WZ":kOrange+2,"ZZ":kOrange-1,"SingleTop":kGray}
includeDataInStack=True
#includeDataInStack= False
#includesignalInStack=False
includesignalInStack=True
includeDatadrivenQCDInStack=False
#includeDatadrivenQCDInStack=True
#includeDatadrivenTTInStack=True
includeDatadrivenTTInStack=False
PlotBlind = False
#PlotBlind = True
#TTBeforeToppTscale =1
#scalename=""

if "Muon" in region and "2016" in region :                  
    QCDscale = 0.76 
    TTscale = 1.0
  #  TTscale = 0.94
elif "Muon" in region and "2017" in region :
    QCDscale= 1.1
    TTscale=  0.87
   # TTscale=  0.9
elif "Muon" in region and "2018" in region :
    QCDscale =  0.92
    TTscale = 0.81
   # TTscale = 0.92

elif "Electron" in region and "2016" in region :
    QCDscale =  0.92
    TTscale =   0.95
    #TTscale =   0.93
elif "Electron" in region and "2017" in region :
    QCDscale=  1.6
    TTscale= 0.92
    #TTscale= 0.93
elif "Electron" in region and "2018" in region :
    QCDscale =  2.8
    TTscale =  0.99
    #TTscale =  1.11
elif "Combine" in region or "FullRunII" in region:
    TTscale = 1.04
    QCDscale = 1.04
else : 
    print ("wrong data year information")
#





def makeSystHist(nominalHist,upHist,downHist,sysName,outDir,var,samplename):
#    canvasName = upHist.GetName().split("Up")[0]
    if var=="M_Mass_bstar":
	titlename="M_{tW}"
    elif var=="M_softdropmass_BoostedJet":
	 titlename="Softdropmass"
    canvasName=samplename+"_"+var+"_"+sysName
    PlotName=samplename+"_"+sysName
    canvy = TCanvas(canvasName,canvasName,1000,800)
    leggy = TLegend(0.2,0.8,0.8,0.9)
 #   leggy = TLegend(0.7,0.7,0.9,0.9)
    leggy.SetNColumns(3)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(0)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)
    gStyle.SetOptTitle(0)
    gStyle.SetOptStat(0000)
    gStyle.SetOptFit(1111)
    gStyle.SetFitFormat("6.7f")


    canvy.cd()
    canvy.SetBottomMargin(0.3)
    nominalHist.SetLineColor(kBlack)
    nominalHist.SetLineWidth(2)
    histMax = 0.
    if upHist.GetMaximum() > histMax: histMax = upHist.GetMaximum() 
    if downHist.GetMaximum() > histMax: histMax = downHist.GetMaximum()
    nominalHist.SetMaximum(histMax*1.3)
    #nominalHist.SetMaximum(histMax*100)
    leggy.AddEntry(nominalHist,"nominal","l")
    nominalHist.SetStats(0)
    nominalHist.Draw("hist")
    upHist.SetLineColor(kRed)
    upHist.SetLineWidth(2)
    leggy.AddEntry(upHist,"up","l")
    upHist.Draw("hist same")
    downHist.SetLineColor(kBlue)
    downHist.SetLineWidth(2)
    downHist.Draw("hist same")
    leggy.AddEntry(downHist,"down","l")
    leggy.Draw()

    #latex.SetTextSize(0.07)
    latex.SetTextSize(0.08)
    latex.SetTextFont(cmsTextFont)
    #latex.DrawLatex(0.23, 0.95, "CMS")
    #latex.DrawLatex(0.46, 1.6, "CMS")
    
    latex.SetTextFont(extraTextFont)
    #latex.SetTextSize(0.04*0.76)
    latex.SetTextSize(0.06*0.76)
    #latex.DrawLatex(0.35, 0.95 , extraText )
   # latex.DrawLatex(0.55, 0.95 , extraText )
    
    latex2.DrawLatex(0.95, 0.95, PlotName);
    
    ratioCanvy = TPad("sys_ratio","sys_ratio",0.0,0.0,1.0,1.0)
    ratioCanvy.SetTopMargin(0.7)
    ratioCanvy.SetFillColor(0)
    ratioCanvy.SetFillStyle(0)
    ratioCanvy.SetGridy(1)
    ratioCanvy.Draw()
    ratioCanvy.cd(0)
    SetOwnership(ratioCanvy,False)
    


    upHistRatio = upHist.Clone()
    upHistRatio.Divide(nominalHist)
    upHistRatio.SetMaximum(1.3)
    upHistRatio.SetMinimum(0.7)
#    if(canvasName.find("JE")>0):
#	    upHistRatio.SetMaximum(1.1)
#    	    upHistRatio.SetMinimum(0.9)
 
    upHistRatio.GetXaxis().SetTitle(titlename)
    upHistRatio.Draw("hist same")
    downHistRatio = downHist.Clone()
    downHistRatio.Divide(nominalHist)
    downHistRatio.Draw("hist same")

    canvy.SaveAs(outDir+canvasName+".pdf")
    #canvy.SaveAs(outDir+canvasName+".png")

def makeStackPlot(nominal,outDir,vardraw,sysuphist,sysdownhist,JESUphist,JESDownhist,JERDownhist,JERUphist,JMSUphist,JMSDownhist,JMRDownhist,JMRUphist):
    stack = THStack(vardraw,vardraw)
    canvy = TCanvas(vardraw,vardraw,1000,800)
    #leggy = TLegend(0.6,0.65,1.2,0.9)
    leggy = TLegend(0.3,0.75,1.0,0.9)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)
    leggy.SetTextSize(0.035); 
    leggy.SetNColumns(3); 
    canvy.cd()
    if includeDataInStack: canvy.SetBottomMargin(0.3)
    dataHist = 0
    QCDHist=0
    TTHist=0
    signalHist1200=0
    signalHist2000=0
    signalHist2600=0
    print (nominal.keys()[0])
    print (sysuphist.keys()[0])
    print (sysdownhist.keys()[0])
    sumHist = nominal[nominal.keys()[0]].Clone()
    #print nominal.keys()
    print sysdownhist[sysdownhist.keys()[0]].keys()
    sumSysUpHist={}
    sumSysDownHist={}
    for sys in systs:
	sumSysUpHist[sys]=sysuphist["TT"]["topsfsemimerged"].Clone()
	sumSysDownHist[sys]=sysdownhist["TT"]["topsfsemimerged"].Clone()
	sumSysUpHist[sys].Reset()
	sumSysDownHist[sys].Reset()
    #sumSysUpHist = sysuphist[sysuphist.keys()[0]].Clone()
    #sumSysDownHist = sysdownhist[sysdownhist.keys()[0]].Clone()
    sumJESUpHist 	= JESUphist[JESUphist.keys()[0]].Clone()
    sumJESDownHist 	= JESDownhist[JESDownhist.keys()[0]].Clone()
    sumJERUpHist 	= JERUphist[JERUphist.keys()[0]].Clone()
    sumJERDownHist 	= JERDownhist[JERDownhist.keys()[0]].Clone()
    sumJMSUpHist 	= JMSUphist[JMSUphist.keys()[0]].Clone()
    sumJMSDownHist 	= JMSDownhist[JMSDownhist.keys()[0]].Clone()
    sumJMRUpHist 	= JMRUphist[JMRUphist.keys()[0]].Clone()
    sumJMRDownHist 	= JMRDownhist[JMRDownhist.keys()[0]].Clone()

    sumHist.Reset()
    #sumSysUpHist.Reset()
    #sumSysDownHist.Reset()
    sumJESUpHist.Reset() 	
    sumJESDownHist.Reset() 	
    sumJERUpHist.Reset() 	
    sumJERDownHist.Reset() 	
    sumJMSUpHist.Reset() 	
    sumJMSDownHist.Reset() 	
    sumJMRUpHist.Reset() 	
    sumJMRDownHist.Reset() 	
    



    for i in nominal.keys():
        if i == "Data":
            dataHist = nominal["Data"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            continue
        if i == "RH_1200":
            signalHist1200=nominal["RH_1200"]
            signalHist1200.SetLineColor(colourPerSample["RH_1200"])
            signalHist1200.SetLineWidth(4)
            continue

        if i == "RH_2000":
           signalHist2000=nominal["RH_2000"]
           #signalHist2000.Scale(10)
         #  signalHist.SetFillColor(colourPerSample["RH_2000"])
           signalHist2000.SetLineColor(colourPerSample["RH_2000"])
           signalHist2000.SetLineWidth(4)
           continue


        if i == "RH_2600":
           signalHist2600=nominal["RH_2600"]
          # signalHist2600.Scale(100)
           signalHist2600.SetLineColor(colourPerSample["RH_2600"])
           signalHist2600.SetLineWidth(4)
           continue


        if includeDatadrivenTTInStack and i =="TT":
		nominal[i].Scale(TTscale)	
		sysuphist[i].Scale(TTscale)
		sysdownhist[i].Scale(TTscale)

	if includeDatadrivenQCDInStack and i =="QCD":	
         	nominal[i].Scale(QCDscale)	
         	sysuphist[i].Scale(QCDscale)
         	sysdownhist[i].Scale(QCDscale)



        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        sumHist.Sumw2()
        sumHist.Add(nominal[i])
	#sumSysUpHist.Sumw2()
        #sumSysUpHist.Add(sysuphist[i])
	#sumSysDownHist.Sumw2()
        #sumSysDownHist.Add(sysdownhist[i])
	sumJESUpHist.Sumw2() 	
        sumJESDownHist.Sumw2() 	
        sumJERUpHist.Sumw2() 	
        sumJERDownHist.Sumw2() 	
        sumJMSUpHist.Sumw2() 	
        sumJMSDownHist.Sumw2() 	
        sumJMRUpHist.Sumw2() 	
        sumJMRDownHist.Sumw2() 	
	sumJESUpHist.Add(JESUphist[i]) 	
        sumJESDownHist.Add(JESDownhist[i]) 	
        sumJERUpHist.Add(JERUphist[i]) 	
        sumJERDownHist.Add(JERDownhist[i]) 	
        sumJMSUpHist.Add(JMSUphist[i]) 	
        sumJMSDownHist.Add(JMSDownhist[i]) 	
        sumJMRUpHist.Add(JMRUphist[i]) 	
        sumJMRDownHist.Add(JMRDownhist[i]) 
   	for sys in systs:
		sumSysDownHist[sys].Sumw2()
		sumSysUpHist[sys].Sumw2()
		sumSysUpHist[sys].Add(sysuphist[i][sys])
		sumSysDownHist[sys].Add(sysdownhist[i][sys])
		     




        #Do systematic estimation here when I get aorund to it)

    if "Data" in nominal.keys():
        leggy.AddEntry(nominal['Data'],"Data","pe")
    if"RH_1200" in nominal.keys():
        leggy.AddEntry(nominal['RH_1200'],"RH_1200","l")
    if"RH_2000" in nominal.keys():
        #leggy.AddEntry(nominal['RH_2000'],"RH_2000*10","l")
        leggy.AddEntry(nominal['RH_2000'],"RH_2000","l")
    if"RH_2600" in nominal.keys():
        #leggy.AddEntry(nominal['RH_2600'],"RH_2600*100","l")
        leggy.AddEntry(nominal['RH_2600'],"RH_2600","l")
    for entry in legendOrder:
        leggy.AddEntry(nominal[entry],entry,"f")
 #
   # legendOrder.reverse()
    for entry in legendOrder:
        stack.Add(nominal[entry])

    maxi = stack.GetMaximum()
    if dataHist.GetMaximum() > stack.GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi*100)
    #stack.SetMaximum(maxi*1.5)
    stack.SetMinimum(1)
    stack.Draw("hist")
#    gStyle.SetOptStat(111111)
    errorGraph = getErrorPlot(sumHist,sumSysUpHist,sumSysDownHist,sumJESUpHist,sumJESDownHist,sumJERUpHist,sumJERDownHist,sumJMSUpHist,sumJMSDownHist,sumJMRUpHist,sumJMRDownHist,False)
    #errorGraph.SetFillStyle(3013)
    errorGraph.SetFillStyle(3002)
    errorGraph.SetFillColor(12)
    errorGraph.Draw("same e2")
    leggy.AddEntry(errorGraph,"Unc.","f") 

    stack.GetXaxis().SetLabelSize(0.0)
    stack.GetYaxis().SetTitleOffset(1.)
    #stack.GetYaxis().SetLabelSize(0.03)
    stack.GetYaxis().SetLabelSize(0.05)
    #stack.GetYaxis().SetTitleSize(0.04)
    stack.GetYaxis().SetTitleSize(0.05)
    stack.GetXaxis().SetTitleSize(0.055)
    #stack.GetXaxis().SetTitleSize(0.045)
    stack.GetYaxis().SetTitle("Events") 
    

    if includesignalInStack :
	signalHist1200.Draw("same Histo")
	signalHist2000.Draw("same Histo")
	signalHist2600.Draw("same Histo")
    #dataHist.SetStats(0)
    dataHist.GetYaxis().SetTitle("Events")
    dataHistbackup=dataHist.Clone()
    if includeDataInStack:
	if PlotBlind: 
		if vardraw=="M_Mass_bstar":
			dataHist.GetXaxis().SetRangeUser(0,1200)		
		#	dataHist.Draw("e1 same")
	else: 
		dataHist.Draw("e1 same")
    leggy.Draw()


    #latex.SetTextSize(0.04)
    latex.SetTextSize(0.05)
    latex.SetTextFont(cmsTextFont)
    #latex.DrawLatex(0.23, 0.95, cmsText )
    latex.DrawLatex(0.23, 0.95, "CMS")

    latex.SetTextFont(extraTextFont)
    #latex.SetTextSize(0.04*0.76)
    latex.SetTextSize(0.05*0.76)
    latex.DrawLatex(0.35, 0.95 , extraText )
    
    #latex2.DrawLatex(0.95, 0.95 , "35.9 fb^{-1} (13TeV)");
    #latex2.DrawLatex(0.95, 0.95 , "41.5 fb^{-1} (13TeV)");
    #latex2.DrawLatex(0.95, 0.95 , "59.7 fb^{-1} (13TeV)");
    latex2.DrawLatex(0.95, 0.95 , LumiText);
    text2.Draw()
    if includeDataInStack:
        ratioCanvy = TPad("mva_ratio","mva_ratio",0.0,0.0,1.0,1.0)
        gPad.SetLogy(1)
        #gPad.SetLogy(0)
        ratioCanvy.SetTopMargin(0.7)
        ratioCanvy.SetFillColor(0)
        ratioCanvy.SetFillStyle(0)
        ratioCanvy.SetGridy(1)
        ratioCanvy.Draw()
        ratioCanvy.cd(0)
        SetOwnership(ratioCanvy,False)

        sumHistoData = dataHistbackup.Clone(dataHistbackup.GetName()+"_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)
	sumHistoDatabackup=sumHistoData.Clone()
	sumHistoDatabackup2=sumHistoData.Clone()



        sumHistoDatabackup.GetYaxis().SetTitle("Data/MC")
        sumHistoDatabackup.GetXaxis().SetTitle(xtitlepervar[vardraw])
        sumHistoDatabackup.GetYaxis().SetTitleOffset(1.3)
        ratioCanvy.cd()
        SetOwnership(sumHistoDatabackup,False)
        sumHistoDatabackup.SetMinimum(0)
        sumHistoDatabackup.SetMaximum(2)
        sumHistoDatabackup.GetXaxis().SetTitleOffset(1.2)
        #sumHistoDatabackup.GetXaxis().SetLabelSize(0.04)
        sumHistoDatabackup.GetXaxis().SetLabelSize(0.05)
        sumHistoDatabackup.GetYaxis().SetLabelSize(0.05)
        sumHistoDatabackup.GetYaxis().SetNdivisions(6)
        #sumHistoDatabackup.GetYaxis().SetTitleSize(0.03)
        sumHistoDatabackup.GetYaxis().SetTitleSize(0.05)
        sumHistoDatabackup.GetXaxis().SetTitleSize(0.05)
	sumHistoDatabackup.SetLineColor(kWhite)
	sumHistoDatabackup.SetFillColor(kWhite)
	if PlotBlind:
		if vardraw=="M_Mass_bstar":
	                sumHistoData.GetXaxis().SetRangeUser(0,1200)
		sumHistoDatabackup.Draw("AXIS")
        	sumHistoDatabackup2.Draw("AXIG same")
		#sumHistoData.Draw("E1X0 same")	
	else:
        	sumHistoDatabackup.Draw("AXIS")
       		sumHistoDatabackup2.Draw("AXIG same")
        	sumHistoData.Draw("E1X0 same")
	ratioerrorGraph = getErrorPlot(sumHist,sumSysUpHist,sumSysDownHist,sumJESUpHist,sumJESDownHist,sumJERUpHist,sumJERDownHist,sumJMSUpHist,sumJMSDownHist,sumJMRUpHist,sumJMRDownHist,True)
        #ratioerrorGraph.SetFillStyle(3013)
        ratioerrorGraph.SetFillStyle(3002)
        ratioerrorGraph.SetFillColor(12)
        ratioerrorGraph.Draw(" same e2")
    canvy.SaveAs(outDir+vardraw+"_log_y.pdf")
    #canvy.SaveAs(outDir+vardraw+".pdf")




###########################################################################
#Use to plot background and signal sepration 
################################################################  

#    canvy2 = TCanvas(vardraw+".QCD",vardraw+".QCD",1000,800)	
#    canvy3 = TCanvas(vardraw+".TT",vardraw+".TT",1000,800)	
#    #leggy2 = TLegend(0.8,0.75,0.9,0.9)
#    leggy2 = TLegend(0.65,0.75,0.9,0.9)
#    leggy2.SetFillStyle(1001)
#    leggy2.SetBorderSize(1)
#    leggy2.SetFillColor(0)
#    leggy2.SetLineColor(0)
#    leggy2.SetShadowColor(0)
#    leggy2.SetFillColor(kWhite)
#    
#    leggy3 = TLegend(0.65,0.75,0.9,0.9)
#    leggy3.SetFillStyle(1001)
#    leggy3.SetBorderSize(1)
#    leggy3.SetFillColor(0)
#    leggy3.SetLineColor(0)
#    leggy3.SetShadowColor(0)
#    leggy3.SetFillColor(kWhite)
#
#
#
#
#
#    gStyle.SetOptTitle(0);
#    QCDHist=nominal["QCD"].Clone()
#    TTHist=nominal["TT"].Clone()
#    signalHist_2000=signalHist2000.Clone()
#    if QCDHist.Integral()==0: QCDnorscale=1
#    else:QCDnorscale=1.0/QCDHist.Integral()
#    QCDHist.Scale(QCDnorscale)
#    QCDHist.SetLineColor(kBlack)
#    QCDHist.GetYaxis().SetTitle("Events")
#    QCDHist.GetXaxis().SetTitleSize(0.05)
#    QCDHist.GetXaxis().SetLabelSize(0.05)
#    QCDHist.GetYaxis().SetLabelSize(0.05)
#    QCDHist.GetYaxis().SetTitleSize(0.05)
#    QCDHist.GetXaxis().SetTitle(xtitlepervar[vardraw])
#   
#    if TTHist.Integral()==0: TTnorscale=1
#    else:TTnorscale=1.0/TTHist.Integral()
#    TTHist.Scale(TTnorscale)
#    TTHist.SetLineColor(kBlack)
#    TTHist.GetYaxis().SetTitle("Events")
#    TTHist.GetXaxis().SetTitleSize(0.05)
#    TTHist.GetXaxis().SetLabelSize(0.05)
#    TTHist.GetYaxis().SetLabelSize(0.05)
#    TTHist.GetYaxis().SetTitleSize(0.05)
#    TTHist.GetXaxis().SetTitle(xtitlepervar[vardraw])
#
#
#    if signalHist_2000.Integral()==0: signalscale2000=1
#    else: signalscale2000=1.0/signalHist_2000.Integral() 
#    signalHist_2000.Scale(signalscale2000)
#    if signalHist2600.Integral()==0: signalscale2600=1
#    else: signalscale2600=1.0/signalHist2600.Integral() 
#    signalHist2600.Scale(signalscale2600)
#    signalHist_2000.SetLineColor(kRed)
#    signalHist2600.SetLineColor(kBlue)
#    maximum=QCDHist.GetMaximum()
#    if signalHist2600.GetMaximum()>maximum: maximum=signalHist2600.GetMaximum()
#    elif  signalHist_2000.GetMaximum()>maximum: maximum=signalHist_2000.GetMaximum() 
#    maximumTT=TTHist.GetMaximum()
#    QCDHist.SetMaximum(maximum*1.2)
#    TTHist.SetMaximum(maximumTT*1.2)
#    canvy2.cd()
#    canvy2.SetBottomMargin(0.3)
#    QCDHist.Draw("Histo")
#    signalHist_2000.Draw("same Histo")
#    signalHist2600.Draw("same Histo")
#    leggy2.AddEntry(signalHist_2000,"RH_2000","l")
#    leggy2.AddEntry(signalHist2600,"RH_2600","l")
#    leggy2.AddEntry(QCDHist,"QCD","f")
#  #  leggy2.AddEntry(QCDHist,"allbkg","f")
#    leggy2.Draw()
#    canvy2.SaveAs(outDir+vardraw+"_QCDOptim.pdf")
#
#    canvy3.cd()
#    canvy3.SetBottomMargin(0.3)
#    TTHist.Draw("Histo")
#    signalHist_2000.Draw("same Histo")
#    signalHist2600.Draw("same Histo")
#    leggy3.AddEntry(signalHist_2000,"RH_2000","l")
#    leggy3.AddEntry(signalHist2600,"RH_2600","l")
#    leggy3.AddEntry(TTHist,"TT","f")
#    leggy3.Draw()
#    canvy3.SaveAs(outDir+vardraw+"_TTOptim.pdf")
#







def getErrorPlot(totalMC,systUp,systDown,sumJESUpHist,sumJESDownHist,sumJERUpHist,sumJERDownHist,sumJMSUpHist,sumJMSDownHist,sumJMRUpHist,sumJMRDownHist,isRatio = False):
    x = array('d',[])
    y = array('d',[])
    exl = array('d',[])
    exh = array('d',[])
    eyl = array('d',[])
    eyh = array('d',[])
    xAxis = totalMC.GetXaxis()
    for i in range(1,xAxis.GetNbins()+1):
	totalsysyl=0
        totalstayl=0
        totalsysallyl=0
        totalsysyh=0
        totalstayh=0
        totalsysallyh=0
        x.append(xAxis.GetBinCenter(i))
	if totalMC.GetBinContent(i) == 0:
                totalsysyl=0
                totalstayl=0
                totalsysallyl=0
                totalsysyh=0
                totalstayh=0
                totalsysallyh=0
#                continue
	else: 
		totalstayl= pow(totalMC.GetBinError(i),2)
		totalstayh= pow(totalMC.GetBinError(i),2)
		for sys in systs:
			totalsysyl=pow(systDown[sys].GetBinContent(i)-totalMC.GetBinContent(i),2)+totalsysyl	
			totalsysyh=pow(systUp[sys].GetBinContent(i)-totalMC.GetBinContent(i),2)+totalsysyh
		#	print i,sys,systUp[sys].GetBinContent(i)-totalMC.GetBinContent(i),totalMC.GetBinContent(i),totalsysyl
		totalsysyl = totalsysyl+pow((sumJMRDownHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)+pow((sumJMSDownHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)+pow((sumJERDownHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)+pow((sumJESDownHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)
	#	print "sumJMRDownHist.GetBinContent(i)-totalMC.GetBinContent(i)",sumJMRDownHist.GetBinContent(i)-totalMC.GetBinContent(i),sumJMSDownHist.GetBinContent(i)-totalMC.GetBinContent(i),sumJERDownHist.GetBinContent(i)-totalMC.GetBinContent(i),sumJESDownHist.GetBinContent(i)-totalMC.GetBinContent(i),totalsysyl	
		totalsysyh = totalsysyh+pow((sumJMRUpHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)+pow((sumJMSUpHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)+pow((sumJERUpHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)+pow((sumJESUpHist.GetBinContent(i)-totalMC.GetBinContent(i)),2)
	#	print "After include Jet uncertaitny:",totalsysyl
		totalsysallyl=math.sqrt(totalsysyl+totalstayl)
	#	print "Low uncertainty is ",totalsysallyl
		totalsysallyh=math.sqrt(totalsysyh+totalstayh)
#	print totalMC.GetBinError(i)/totalMC.GetBinContent(i)
#	print totalsysyl
        if not isRatio: y.append(totalMC.GetBinContent(i))
        else: y.append(1.)
        exl.append(xAxis.GetBinCenter(i) - xAxis.GetBinLowEdge(i))
        exh.append(xAxis.GetBinLowEdge(i)+xAxis.GetBinWidth(i)-xAxis.GetBinCenter(i))
        if not isRatio:
	    if totalMC.GetBinContent(i) == 0:
            	eyl.append(0.)
            	eyh.append(0.)
            	#continue
	    else:
            	eyl.append(totalsysallyl)
            	eyh.append(totalsysallyh)

        else:
            if totalMC.GetBinContent(i) == 0:
                eyl.append(0.)
                eyh.append(0.)
                #continue
            else:
	    #eyl.append(systDown[i-1]/totalMC.GetBinContent(i))
	    	eyl.append(totalsysallyl/totalMC.GetBinContent(i))
            #eyh.append(systUp[i-1]/totalMC.GetBinContent(i))
            	eyh.append(totalsysallyh/totalMC.GetBinContent(i))
    errors = TGraphAsymmErrors(xAxis.GetNbins(),x,y,exl,exh,eyl,eyh)
    return errors


def GetJESR(jesrname,sample,var):
	JetsysFilename=allFileDir+jesrname+"/output_"+sample+".root"
	JetsysFile = TFile(JetsysFilename,"READ")
	systJESRhist=JetsysFile.Get(var).Clone()
	systJESRhist.SetDirectory(0)
	JetsysFile.Delete()
	return systJESRhist






def makeEventable(outDir,nominal,sysuphist,sysdownhist,JESUphist,JESDownhist,JERDownhist,JERUphist,JMSUphist,JMSDownhist,JMRDownhist,JMRUphist):
    Eventyieldtable= 0
    Eventyieldtable = open(outDir+"Eventable.txt","w")
    sumyield=0.0
    sumstats=0.0
    sumsysup=0.0
    sumsysdown=0.0
    
    Otherbkgyield=0.0
    Otherbkgstats=0.0
    Otherbkgsysup=0.0
    Otherbkgsysdown=0.0

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    for i in nominal.keys():
        nominal[i].Sumw2()

	signalyieldstats=0.0
        signalyieldsysup=0.0
        signalyieldsysdown=0.0
        signalsysup=0.0
        signalsysdown=0.0
        eventyieldstats=0.0
        signalyield=Double(0) 
        eventyield=Double(0) 
        signalyieldstats=Double(0) 
        eventyieldstats=Double(0)
        eventyieldsysup=0
        eventyieldsysdown=0
        eventsysup=0
        eventsysdown=0 

	
	
        if i=="RH_2600" or i=="RH_2000" or i=="RH_1200":
                signalyield=nominal[i].IntegralAndError(1,1000,signalyieldstats)
                if(signalyield==0):
			signalyieldsysup=0
			signalyieldsysdown=0
		else:
			for sys in systs:
				signalyieldsysup =  pow(sysuphist[i][sys].Integral()-signalyield,2)+signalyieldsysup
				signalyieldsysdown =  pow(sysdownhist[i][sys].Integral()-signalyield,2)+signalyieldsysdown
			signalyieldsysup=signalyieldsysup+pow(JESUphist[i].Integral()-signalyield,2)+pow(JERUphist[i].Integral()-signalyield,2)+pow(JMSUphist[i].Integral()-signalyield,2)+pow(JMRUphist[i].Integral()-signalyield,2)
			signalyieldsysdown=signalyieldsysdown+pow(JESDownhist[i].Integral()-signalyield,2)+pow(JERDownhist[i].Integral()-signalyield,2)+pow(JMSDownhist[i].Integral()-signalyield,2)+pow(JMRDownhist[i].Integral()-signalyield,2)
		signalsysup=math.sqrt(signalyieldsysup)
		signalsysdown=math.sqrt(signalyieldsysdown)
                print >>Eventyieldtable,i+" =  "+str(round(signalyield, 1))+" \pm "+str(round(signalyieldstats, 1))+"^{+"+str(round(signalsysup, 1))+"}"+"_{-"+str(round(signalsysdown, 1))+"}"
                continue
        if i=="Data":
                datayield=nominal["Data"].Integral()
                #print >>Eventyieldtable,i+"=",datayield
                print >>Eventyieldtable,i+"=",int(datayield)
                continue
	if i=="RH_1200" or i=="RH_2600" or i=="RH_2000":continue
        eventyield=nominal[i].IntegralAndError(1,1000,eventyieldstats,"")
        if(eventyield==0):
                eventyieldsysup=0
                eventyieldsysdown=0
        else:
                for sys in systs:
                        eventyieldsysup =  pow(sysuphist[i][sys].Integral()-eventyield,2)+eventyieldsysup
                        eventyieldsysdown =  pow(sysdownhist[i][sys].Integral()-eventyield,2)+eventyieldsysdown
                eventyieldsysup=eventyieldsysup+pow(JESUphist[i].Integral()-eventyield,2)+pow(JERUphist[i].Integral()-eventyield,2)+pow(JMSUphist[i].Integral()-eventyield,2)+pow(JMRUphist[i].Integral()-eventyield,2)
                eventyieldsysdown=eventyieldsysdown+pow(JESDownhist[i].Integral()-eventyield,2)+pow(JERDownhist[i].Integral()-eventyield,2)+pow(JMSDownhist[i].Integral()-eventyield,2)+pow(JMRDownhist[i].Integral()-eventyield,2)
                eventsysup=math.sqrt(eventyieldsysup)
                eventsysdown=math.sqrt(eventyieldsysdown)



	#print >>Eventyieldtable,i+"=",eventyield,"or ",eventyield1,"(stat)\pm",eventyieldstats,"(sys)+",eventyiledsysup,"/-",eventyiledsysdown
        print >>Eventyieldtable,i+" = "+str(round(eventyield, 1))+" \pm "+str(round(eventyieldstats, 1))+"^{+"+str(round(eventsysup, 1))+"}"+"_{-"+str(round(eventsysdown, 1))+"}"
        sumyield=sumyield+eventyield
        sumstats=sumstats+eventyieldstats
        sumsysup=sumsysup+eventsysup
        sumsysdown=sumsysdown+eventsysdown 
	if i=="QCD" or i=="TT": continue
	Otherbkgyield=Otherbkgyield+eventyield
	Otherbkgstats=Otherbkgstats+eventyieldstats
	Otherbkgsysup = Otherbkgsysup +eventsysup
	Otherbkgsysdown = Otherbkgsysdown +eventsysdown

    print >>Eventyieldtable,"allMC = "+str(round(sumyield, 1))+" \pm "+str(round(sumstats, 1))+"^{+"+str(round(sumsysup, 1))+"}"+"_{-"+str(round(sumsysdown, 1))+"}"
    print >>Eventyieldtable,"OtherBkg = "+str(round(Otherbkgyield, 1))+" \pm "+str(round(Otherbkgstats, 2))+"^{+"+str(round(Otherbkgsysup, 1))+"}"+"_{-"+str(round(Otherbkgsysdown, 1))+"}"






if __name__ == "__main__":
    #Do something to get your nominal and systUp/Down plots here
     #outDir = "plots/"+region+ifscale+"/"   
     if includeDatadrivenTTInStack : outDir = "plots/"+region+"_scaled/"
     else :  outDir = "plots/"+region+"/"   
     #if includeDatadrivenTTInStack : outDir = "plots/WJets/"+region+"_scaled/"
     #else :  outDir = "plots/WJets/"+region+"/"   
     os.popen('mkdir -p '+ outDir)   
     print allFileDir       
     for sample in sampletodrawsys:
     	print sample 
    #    print allFileDir       
        inFileName=allFileDir+"Systs/output_"+sample+".root"
        allFileDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/"+region+"/"
        inFile = TFile(inFileName,"READ")
        for var in vartodrawsys:
		print var
                nominalHist = inFile.Get(var).Clone()
		if DoJetSys:
			systJESUp= GetJESR("JESUp",sample,var)
			systJESDown=GetJESR("JESDown",sample,var)
			JESname = "JES"
			makeSystHist(nominalHist,systJESUp,systJESDown,JESname,outDir,var,sample)
			systJERUp= GetJESR("JERUp",sample,var)
			systJERDown=GetJESR("JERDown",sample,var)
			JERname = "JER"
			makeSystHist(nominalHist,systJERUp,systJERDown,JERname,outDir,var,sample)
		if DoJetmassSys:
			systJMSUp= GetJESR("JMSUp",sample,var)
			systJMSDown=GetJESR("JMSDown",sample,var)
			JMSname = "JMS"
			makeSystHist(nominalHist,systJMSUp,systJMSDown,JMSname,outDir,var,sample)
			systJMRUp= GetJESR("JMRUp",sample,var)
			systJMRDown=GetJESR("JMRDown",sample,var)
			JMRname = "JMR"
			makeSystHist(nominalHist,systJMRUp,systJMRDown,JMRname,outDir,var,sample)







 
                for sys in systs: 
                        systUp = inFile.Get(var+"_"+sys+"_up").Clone() 
                        systDown = inFile.Get(var+"_"+sys+"_down").Clone()
                        makeSystHist(nominalHist,systUp,systDown,sys,outDir,var,sample)
#	allFileDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/"+region+"/"
        inFile.Delete()



     for var in vartodraw:
        nominal = {}
        sysuphist = {}
        sysdownhist = {}
        JESUphist = {}
        JESDownhist = {}
        JERDownhist = {}
        JERUphist = {}
	JMSUphist = {}          
        JMSDownhist = {}
        JMRDownhist = {}
        JMRUphist = {}


	print (var)
        for sample in allsamples:
		sysuphist[sample] = {}
        	sysdownhist[sample] = {}
                print (sample)
                InFileName=allFileDir+"Systs/output_"+sample+".root"
                InFile = TFile(InFileName,"READ")
   	 	nominal[sample] = InFile.Get(var).Clone()
                nominal[sample].SetDirectory(0)
		JESUphist[sample]=  InFile.Get(var).Clone() 
                JESDownhist[sample]= InFile.Get(var).Clone()
                JERUphist[sample]=   InFile.Get(var).Clone()
                JERDownhist[sample]= InFile.Get(var).Clone()
   		JMSUphist[sample]=   InFile.Get(var).Clone()
                JMSDownhist[sample]= InFile.Get(var).Clone()
                JMRUphist[sample]=   InFile.Get(var).Clone()
                JMRDownhist[sample]= InFile.Get(var).Clone()
		JESUphist[sample].SetDirectory(0)
                JESDownhist[sample].SetDirectory(0)
                JERUphist[sample].SetDirectory(0)
                JERDownhist[sample].SetDirectory(0)
		JMSUphist[sample].SetDirectory(0)
                JMSDownhist[sample].SetDirectory(0)
                JMRUphist[sample].SetDirectory(0)
                JMRDownhist[sample].SetDirectory(0)
                if sample=="Data":
                      continue	
                #sysuphist[sample] = InFile.Get(var+"_Sys_up").Clone()
                #sysdownhist[sample] = InFile.Get(var+"_Sys_down").Clone()
                #sysuphist[sample].SetDirectory(0) 
                #sysdownhist[sample].SetDirectory(0)
		for sys in systs:
			sysuphist[sample][sys] = InFile.Get(var+"_"+sys+"_up").Clone()
                	sysdownhist[sample][sys] = InFile.Get(var+"_"+sys+"_down").Clone()
                	sysuphist[sample][sys].SetDirectory(0) 
                	sysdownhist[sample][sys].SetDirectory(0) 
		if DoJetSys: 
			JESUphist[sample]=GetJESR("JESUp",sample,var)
			JESDownhist[sample]=GetJESR("JESDown",sample,var)
			JERUphist[sample]=GetJESR("JERUp",sample,var)
			JERDownhist[sample]=GetJESR("JERDown",sample,var)
			JESUphist[sample].SetDirectory(0)
			JESDownhist[sample].SetDirectory(0)
			JERUphist[sample].SetDirectory(0)
			JERDownhist[sample].SetDirectory(0)
		if DoJetmassSys:	
			JMSUphist[sample]=GetJESR("JMSUp",sample,var)
			JMSDownhist[sample]=GetJESR("JMSDown",sample,var)
			JMRUphist[sample]=GetJESR("JMRUp",sample,var)
			JMRDownhist[sample]=GetJESR("JMRDown",sample,var)
			JMSUphist[sample].SetDirectory(0)
			JMSDownhist[sample].SetDirectory(0)
			JMRUphist[sample].SetDirectory(0)
			JMRDownhist[sample].SetDirectory(0)
		#else:
		#	JMSUphist[sample]=InFile.Get(var).Clone()
                 #       JMSDownhist[sample]=InFile.Get(var).Clone()
                  #      JMRUphist[sample]=InFile.Get(var).Clone()
                  #      JMRDownhist[sample]=InFile.Get(var).Clone()
                  #      JMSUphist[sample].SetDirectory(0)
                  #      JMSDownhist[sample].SetDirectory(0)
                  #      JMRUphist[sample].SetDirectory(0)
                  #      JMRDownhist[sample].SetDirectory(0)


		
	makeStackPlot(nominal,outDir,var,sysuphist,sysdownhist,JESUphist,JESDownhist,JERDownhist,JERUphist,JMSUphist,JMSDownhist,JMRDownhist,JMRUphist)
        #if var=="M_Eta_Lepton" :makeEventable(outDir,nominal,sysuphist,sysdownhist)
        #if var=="M_Mass_bstar" :makeEventable(outDir,nominal,sysuphist,sysdownhist,JESUphist,JESDownhist,JERDownhist,JERUphist,JMSUphist,JMSDownhist,JMRDownhist,JMRUphist)
        if var=="M_Mass_bstar" :makeEventable(outDir,nominal,sysuphist,sysdownhist,JESUphist,JESDownhist,JERDownhist,JERUphist,JMSUphist,JMSDownhist,JMRDownhist,JMRUphist)
