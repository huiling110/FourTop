import logging
import os
from math import log, log10

import numpy as np
import xgboost as xgb

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
            
        # cmsswbase=os.environ["CMSSW_BASE"]
        # directory = cmsswbase+"/src/Analysis/Tools/data/mvaWeights/"
        # directory = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/mvaWeights/'
        directory = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/mvaWeights_new/'

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
        # features = self.bst_el['v1'].feature_names
        # print(features)
        if abs(lep['pdgId']) == 11: #electron
            features = np.array([[
                lep['pt'], #0 
                lep['eta'], #1
                # ord(lep['jetNDauCharged']), #???
                lep['jetNDauCharged'], #2 jetNDauChargedMVASel
                lep['miniPFRelIso_chg'], # 3 miniRelIsoCharged
                lep['miniPFRelIso_all']-lep['miniPFRelIso_chg'], # 4miniRelIsoNeutralVanilla
                lep['jetPtRelv2'],#5
                lep['jetPtRatio'], # 6 jetPtRatioVanilla 
                lep['pfRelIso03_all'], # 7 relIso0p3Vanilla
                lep['jetBTag'], #8
            	lep['sip3d'], #9
            	log(abs(lep['dxy'])), #10
            	log(abs(lep['dz'])), #11
                lep['mvaFall17V2noIso'], # 12 eleMvaFall17v2
                # ord(lep['lostHits']), # eleMissingHits
            ]])
            # for i in features[0]:
            #     print(i)

            dtest = xgb.DMatrix(features)
            for v in self.versions:
                # print( self.bst_el[v].feature_names)
                mvaScore = self.bst_el[v].predict(dtest)[0]
                WP = 0
                for wp in self.WPs[v]:
                    if mvaScore > wp:
                        WP += 1
                results.append(mvaScore)
                results.append(WP)
        elif abs(lep['pdgId']) == 13: #muon
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
                #different than electron from below
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
    
    
def main():
    # top = mvaTOPreader('UL2018')
    # top = mvaTOPreader('UL2017')
    top = mvaTOPreader('UL2016')
    lep = {}
    lep['pdgId'] = 11
    # lep['pdgId'] = 13
    lep['pt'] = 50 
    lep['eta'] = 1.5 
    lep['jetNDauCharged'] = 5 # jetNDauChargedMVASel
    lep['miniPFRelIso_chg'] = 1.2 # miniRelIsoCharged
    lep['miniPFRelIso_all'] = 1.4
    lep['jetPtRelv2'] = 2.3
    lep['jetPtRatio'] = 2.4 # jetPtRatioVanilla
    lep['pfRelIso03_all'] = 1.3 # relIso0p3DBVanilla
    lep['jetBTag'] = 0.5
    lep['sip3d'] =  0.004
    lep['dxy'] =0.004
    lep['dz'] = 0.005
    lep['segmentComp'] = 2.2
    lep['mvaFall17V2noIso'] = 0.8
    lep['lostHits']= '0'
    # lep['pt'] = 15.9296 
    # lep['eta'] = 0.309631
    # lep['jetNDauCharged'] = '5' 
    # lep['miniPFRelIso_chg'] = 2.18302
    # lep['miniPFRelIso_all'] = 4.42647
    # lep['jetPtRelv2'] = 2.07031
    # lep['jetPtRatio'] = 0.157248
    # lep['pfRelIso03_all'] = 4.40528
    # lep['jetBTag'] = 0.657227
    # lep['sip3d'] =  3.61133
    # lep['dxy'] = -0.0020504
    # lep['dz'] = 0.0186615
    # lep['mvaFall17V2noIso'] = 0.363446
    # lep['lostHits']= '0'
    # lep['segmentComp'] = 2.2
    
    # mvaWeightDirNew = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/mvaWeights_new/'
    # mvaWeightDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/mvaWeights/'
    # bst = xgb.Booster(model_file=mvaWeightDirNew+'el_TOPv2UL18_XGB.weights.bin')
    # feature_names = bst.feature_names
    # print(feature_names)
    print(top.getmvaTOPScore(lep))
   
    # resaveModel(input, outDir) :
    # for ifile in os.listdir(mvaWeightDir):
    #     # if not '.bin' in ifile: continue
    #     if not '.bin' in ifile: continue
    #     bst = xgb.Booster( model_file= mvaWeightDir+ifile)
    #     bst.save_model(mvaWeightDirNew+ifile)
        
    
    
    
    
    
if __name__=='__main__':
    main()

