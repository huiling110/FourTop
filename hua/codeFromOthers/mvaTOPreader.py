import os
import xgboost as xgb
import numpy as np
from math import log, log10
import logging
logger = logging.getLogger(__name__)

class mvaTOPreader:
    def __init__(self, year, versions = [ "v1", "v2"]):
        yearstring = 'UL18'
        if year == "UL2016":
            yearstring = 'UL16'
        elif year == "UL2016_preVFP": 
            yearstring = 'UL16APV'
        elif year == "UL2017":
            yearstring = 'UL17'
        elif year == "UL2018":
            yearstring = 'UL18'

        self.versions = versions

        # Working points
        
        self.WPs = {'v1': [0.20, 0.41, 0.64, 0.81], 
                    'v2': [0.59, 0.81, 0.90, 0.94] }
            
        cmsswbase=os.environ["CMSSW_BASE"]
        directory = cmsswbase+"/src/Analysis/Tools/data/mvaWeights/"

        # Load Electron weights
        self.bst_el = {}
        self.bst_mu = {}
        if "v1" in self.versions:        
            self.bst_el['v1'] = xgb.Booster() 
            self.bst_el['v1'].load_model(directory+'el_TOP'+yearstring+'_XGB.weights.bin') 
        if "v2" in self.versions: 
            self.bst_el['v2'] = xgb.Booster() 
            self.bst_el['v2'].load_model(directory+'el_TOPv2'+yearstring+'_XGB.weights.bin') 
        
        # Load Muon weights
        if "v1" in self.versions:        
            self.bst_mu['v1'] = xgb.Booster() 
            self.bst_mu['v1'].load_model(directory+'mu_TOP'+yearstring+'_XGB.weights.bin') 
        if "v2" in self.versions:        
            self.bst_mu['v2'] = xgb.Booster() 
            self.bst_mu['v2'].load_model(directory+'mu_TOPv2'+yearstring+'_XGB.weights.bin')         
        
    def getmvaTOPScore(self, lep):
        results = []
        if abs(lep['pdgId']) == 11:
            features = np.array([[
                lep['pt'], 
                lep['eta'], 
                ord(lep['jetNDauCharged']), # jetNDauChargedMVASel
                lep['miniPFRelIso_chg'], # miniRelIsoCharged
                lep['miniPFRelIso_all']-lep['miniPFRelIso_chg'], # miniRelIsoNeutralVanilla
                lep['jetPtRelv2'],
                lep['jetPtRatio'], # jetPtRatioVanilla 
                lep['pfRelIso03_all'], # relIso0p3Vanilla
                lep['jetBTag'],
            	lep['sip3d'],
            	log(abs(lep['dxy'])),
            	log(abs(lep['dz'])),
                lep['mvaFall17V2noIso'], # eleMvaFall17v2
                ord(lep['lostHits']), # eleMissingHits
            ]])
            dtest = xgb.DMatrix(features)
            for v in self.versions:
                mvaScore = self.bst_el[v].predict(dtest)[0]
                WP = 0
                for wp in self.WPs[v]:
                    if mvaScore > wp:
                        WP += 1
                results.append(mvaScore)
                results.append(WP)
        elif abs(lep['pdgId']) == 13:
            features = np.array([[
                lep['pt'], 
                lep['eta'], 
                ord(lep['jetNDauCharged']), # jetNDauChargedMVASel
                lep['miniPFRelIso_chg'], # miniRelIsoCharged
                lep['miniPFRelIso_all']-lep['miniPFRelIso_chg'], # miniRelIsoNeutralVanilla
                lep['jetPtRelv2'],
                lep['jetPtRatio'], # jetPtRatioVanilla
                lep['pfRelIso03_all'], # relIso0p3DBVanilla
                lep['jetBTag'],
            	lep['sip3d'],
            	log(abs(lep['dxy'])), 
            	log(abs(lep['dz'])), 
                lep['segmentComp'], # segComp
            ]])
            dtest = xgb.DMatrix(features)
            for v in self.versions:
                mvaScore = self.bst_mu[v].predict(dtest)[0]
                WP = 0
                for wp in self.WPs[v]:
                    if mvaScore > wp:
                        WP += 1
                results.append(mvaScore)
                results.append(WP)
        return tuple(results)

