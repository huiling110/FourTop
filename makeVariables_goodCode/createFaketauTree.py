#!/usr/bin/env python3
"""
Create fake tau background estimation files.

Standalone usage:
    python3 createFaketauTree.py --config config/analysis_config.yaml --era 2018
    python3 createFaketauTree.py --config config/analysis_config.yaml  # all eras

Via workflow runner:
    python3 run_workflow.py --stage 2.4 --config config/analysis_config.yaml

Historical paths preserved in: config/historical_paths_backup.txt
"""
import argparse
import usefulFunc as uf
import ttttGlobleQuantity as gq
import ROOT
import pandas as pd
import os

# Import workflow utilities for config-based path building
try:
    from workflow_utils import load_config, build_stage2_path, get_channel, get_eras
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False


def create_parser():
    """Create argument parser."""
    parser = argparse.ArgumentParser(
        description='Create fake tau background estimation files',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument('--config', '-c', required=True,
                        help='Path to YAML config file (required)')
    parser.add_argument('--era', '-e',
                        help='Era to process (default: all from config)')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Reduce output verbosity')
    parser.add_argument('--no-morph', action='store_true',
                        help='Disable tau pT morphing (default: enabled)')
    parser.add_argument('--is-1tau2l', action='store_true',
                        help='Process for 1tau2l channel (default: 1tau0l/1tau1l)')
    return parser


def run_for_era(inputDir: str, era: str, is1tau2l: bool, ifMorphTauPt: bool, quiet: bool = False):
    """Run fake tau tree creation for a single era."""
    if not quiet:
        print(f"\n{'='*60}")
        print(f"Processing era: {era}")
        print(f"Input: {inputDir}")
        print(f"{'='*60}")

    inputDirDic = uf.getDirDic(inputDir)
    if not quiet:
        print(f"Era detected: {uf.getEraFromDir(inputDir)}")

    postFix = '_ptMorphed' if ifMorphTauPt else ''
    createFakeTauTree(inputDirDic, era, is1tau2l, '', postFix, ifMorphTauPt)
    createFakeTauTree_mc(inputDirDic, era, is1tau2l, '', postFix, ifMorphTauPt)

    if not quiet:
        print(f"Completed era: {era}")


def main():
    parser = create_parser()
    args = parser.parse_args()

    if not WORKFLOW_UTILS_AVAILABLE:
        parser.error("workflow_utils not available. Install pyyaml: pip install pyyaml")

    # Load config
    config = load_config(args.config)

    # Determine eras to process
    eras = [args.era] if args.era else get_eras(config)

    # Determine channel settings
    channel = get_channel(config)
    is1tau2l = args.is_1tau2l or ('1tau2l' in channel)
    ifMorphTauPt = not args.no_morph

    if not args.quiet:
        print(f"Config: {args.config}")
        print(f"Channel: {channel}")
        print(f"Eras: {eras}")
        print(f"1tau2l mode: {is1tau2l}")
        print(f"Tau pT morphing: {ifMorphTauPt}")

    # Process each era
    for era in eras:
        inputDir = build_stage2_path(config, era)
        run_for_era(inputDir, era, is1tau2l, ifMorphTauPt, args.quiet)

    if not args.quiet:
        print(f"\nAll eras completed successfully!")


def makeOtherMCGen(inputDirDic, era):
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt','VLLm500', 'VLLm550','VLLm600','VLLm650','VLLm700','VLLm750','VLLm800','VLLm850','VLLm900','VLLm950','VLLm1000']
    for iPro in MCSum:
        isubPros = uf.getAllSubPro(era, iPro, False)
        print(isubPros)
        for isubPro in isubPros:
            ifile = inputDirDic['mc']+ isubPro + '.root'
            iDF = ROOT.RDataFrame('newtree', ifile)
            # cut = iDF.Filter('tausT_genTauNum==1&&tausT_num==1')
            cut = iDF.Filter('tausF_num==1 && tausF_1isTight && tausF_1genFlavour!=0')
            cut = cut.Define('event_allWeight_1tau0l', 'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new* btagShape_weight * btagShapeR')#!1tau0l
            
            cut.Snapshot('newtree', inputDirDic['mc']+ isubPro + '_tauGen.root')
            print('cut on tauTgen done on file: ',  inputDirDic['mc']+ isubPro + '_tauGen.root', '\n')


def createFakeTauTree(inputDirDic, era, is1tau2l = False, extraSel='', extraPostfix = '', ifMorphTauPt = False):
    sumData='leptonSum' if is1tau2l else 'jetHT' 
    print('sumData: ', sumData)
    allDataFiles = uf.getAllSubPro(era, [sumData])
    print('all data files: ', allDataFiles)
    allDataFiles = [inputDirDic['data']+ ipro + '.root' for ipro in allDataFiles]
    print('all data files: ', allDataFiles)
    
    dataDF = ROOT.RDataFrame('newtree', allDataFiles)
    dataAR  = dataDF.Filter(f'tausF_num==1 && !tausF_1isTight{extraSel}') 
    print('extra selection: ', extraSel)
    
    print('AR entries: ', dataAR.Count().GetValue())
    
    # all_columns = dataAR.GetColumnNames() 
    dataAR = dataAR.Define('FR_weight_final', 'FR_weight')
    dataAR = dataAR.Define('FR_weight_final_up', 'FR_weight_up')
    dataAR = dataAR.Define('FR_weight_final_down', 'FR_weight_down')
    #!!!Reweight fake tau based on tau pt to account for the residual dependance of tau pt
    #create a new branch depending on tau pt, and reweight the fake tau based on this branch
    
    outFile = inputDirDic['mc'] + f'fakeTau_data{extraPostfix}.root' 
    dataAR.Snapshot('newtree', outFile)
    
    if ifMorphTauPt:
        # correctTausF_1pt(outFile)
        replaceTauTVar(outFile)
    print('fakeTau_data file: ', outFile, ' done')
     
  
def createFakeTauTree_mc(inputDirDic, era, is1tau2l=False, extraSel='', extraPostfix = '', ifMorphTauPt = False): 
    #creat MC fake tau tree
    #!Should probably add tttt to be subtracted too
    # MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'Minor']#!not subtracting qcd here, it is okay because we only estimate fake tau in 0 lepton channel
    MCSum = ['tt', 'ttbb', 'tttt', 'ttX', 'WJets', 'singleTop', 'Minor']#!not subtracting qcd here, it is okay because we only estimate fake tau in 0 lepton channel
    # if is1tau2l:
        # MCSum.append('Minor')
    allMC = []
    allMC += uf.getAllSubPro(era, MCSum, False)
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMC]
    print(allMCFiles)
    
    df = ROOT.RDataFrame('newtree', allMCFiles)
    tauFCut = f'tausF_num==1 && !tausF_1isTight && tausF_1genFlavour!=0' #not prompt tau and prompt e or mu 
    df_tauF = df.Filter(tauFCut)
    
    print('all entries: ', df.Count().GetValue())
    print('tauF entries: ', df_tauF.Count().GetValue())
    
    
    btagHLTWeight = 'triggerSFLep_weight*btagWPMT_weight*elesTopMVAT_weight_new*musTopMVAT_weight_new' if is1tau2l else  'btagShape_weight*btagShapeR*HLT_weight'
    # df_tauF_new = df_tauF_new.Define('FR_weight_final', '-1.*FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    # df_tauF_new = df_tauF_new.Define('FR_weight_final_up', '-1.*FR_weight_up*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    # df_tauF_new = df_tauF_new.Define('FR_weight_final_down', '-1.*FR_weight_down*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    df_tauF = df_tauF.Define('FR_weight_final', f'-1.*FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*tauT_IDSF_weight_new*{btagHLTWeight}')
    df_tauF = df_tauF.Define('FR_weight_final_up', f'-1.*FR_weight_up*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*tauT_IDSF_weight_new*{btagHLTWeight}')
    df_tauF = df_tauF.Define('FR_weight_final_down', f'-1.*FR_weight_down*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*tauT_IDSF_weight_new*{btagHLTWeight}')
     
    df_tauF = df_tauF.Define('event_allWeight_1tau0l', 'FR_weight_final')#for later BDT training
    
    outFile = inputDirDic['mc'] + f'fakeTau_MC{extraPostfix}.root'
    df_tauF.Snapshot('newtree', outFile)
    
    if ifMorphTauPt:
        # correctTausF_1pt(outFile)
        replaceTauTVar(outFile)
    print(inputDirDic['mc']+ outFile) 
    
    
def createFakeTauTree_Gen(inputDirDic, era, is1tau2l=False, extraSel='lepTopMVAT_num==0', postfix = '_1tau1l'):
    MCSum = ['tt', 'ttX', 'qcd', 'WJets', 'singleTop'] 
    # MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt', 'Minor']
    # MCSum = ['qcd']
    allMCList = uf.getAllSubPro(era, MCSum, False)
    #remove qcd low HT files
    allMCList.remove('qcd_50to100')
    allMCList.remove('qcd_100to200')
    allMCList.remove('qcd_200to300')
    allMCList.remove('qcd_300to500')
        
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMCList] 
    print(allMCFiles)
   
    df = ROOT.RDataFrame('newtree', allMCFiles)
    tauFCut = f'tausF_num==1 && tausF_1isTight && tausF_1genFlavour==0 {extraSel}' #prompt tau and prompt e or mu  
    # tauFCut = f'tausF_num==1 && tausF_1isTight && !(tausF_1genFlavour==5 || tausF_1genFlavour==1 ||tausF_1genFlavour==3) {extraSel}' #not prompt tau and prompt e or mu  
    df_tauF = df.Filter(tauFCut)
    
    if is1tau2l:
        btagHLTWeight = 'triggerSFLep_weight'
    else:
        btagHLTWeight = 'HLT_weight'
    df_tauF = df_tauF.Define('event_allWeight_1tau1l', f'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*{btagHLTWeight}*tauT_IDSF_weight_new*elesTopMVAT_weight_new*musTopMVAT_weight_new*btagWPMT_weight*elesTopMVAT_reoSF_weight')#!1tau1l
    print('eventWeight: ', f'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*{btagHLTWeight}*tauT_IDSF_weight_new*elesTopMVAT_weight_new*musTopMVAT_weight_new*btagWPMT_weight*elesTopMVAT_reoSF_weight')
     
                        
    outFile = inputDirDic['mc']+ f'fakeTau_fromGen{postfix}.root'
    df_tauF.Snapshot('newtree', outFile)
    print(inputDirDic['mc']+ outFile)    
    
     

    
    
def countFR(tauF_data):    
    df_pd = tauF_data.AsNumpy()
    pd_tauF = pd.DataFrame(df_pd) 
    
    bins = [0, 0.8, 1.5, 3]
    labels = ['0-0.8', '0.8-1.5', '1.5-2.4']
    # pd_tauF['TauF_eta_region'] = pd.cut(pd_tauF['tausF_1jetEtaAbs'], bins=bins, labels=labels, right=False)
    pd_tauF['TauF_eta_region'] = pd.cut(abs(pd_tauF['tausF_1jetEtaAbs']), bins=bins, labels=labels, right=False)
    
    tauJetPtBins = [20.0, 30, 40.0, 50, 70.0, 90.0, 120.0,  1000.] 
    labels = ['20-30', '30-40', '40-50', '50-70', '70-90', '90-120', '120-1000']
    pd_tauF['TauF_jetPt_region'] = pd.cut(pd_tauF['tausF_1jetPt'], bins=tauJetPtBins, labels=labels, right=False)
    
    
    # grouped_counts = pd_tauF.groupby(['TauF_jetPt_region', 'TauF_eta_region'])['tausF_prongNum'].count().reset_index(name='FRCount')
    # grouped_counts = pd_tauF.groupby(['TauF_jetPt_region', 'TauF_eta_region', 'tauF_prongNum'])['tausF_prongNum'].count().reset_index(name='FRCount')
    #Grouping by multiple columns means that for each unique combination of values in these two columns, pandas will treat all rows with that combination as a single group.
    pd_tauF['FRCount'] = pd_tauF.groupby(['TauF_jetPt_region', 'TauF_eta_region', 'tausF_prongNum'])['tausF_prongNum'].transform('count')
    
    pd_tauF['combination_code'] = pd_tauF['TauF_jetPt_region'].astype(str) + '_' + pd_tauF['TauF_eta_region'].astype(str) + '_' + pd_tauF['tausF_prongNum'].astype(str)

    # df['tauCount'] = df['eta_region'].map(region_counts)
    # pd_tauF = pd.merge(pd_tauF, grouped_counts, on=['TauF_jetPt_region', 'TauF_eta_region'], how='left')
     
    # print(pd_tauF)
    pd.set_option('display.max_rows', 50)
    print(pd_tauF.head(30)[['tausF_1jetEtaAbs', 'tausF_1jetPt', 'TauF_eta_region', 'TauF_jetPt_region', 'tausF_prongNum', 'FRCount', 'combination_code']])
    
    return pd_tauF

def correctTausF_1pt(fakeTauFile):
    # mapping_expression = (
    # f"tausF_1pt * (TMath::Exp({0.00034} + {0.00172}*tausF_1pt) + {0.00172}) + {0.00172}"
    # )
    # mapping_expression = (
    # f"tausF_1pt * (TMath::Exp({-0.00036} + {0.00105}*tausF_1pt) + {0.00105}) + {0.00105}"
    # )
    # mapping_expression = (
    # f"tausF_1pt *((-{33.24302} * TMath::Exp(-{0.30112} * tausF_1pt)) + {1.08058})"
    # )# tausF pt and related variables morphed in MV step 

    df_tauF = ROOT.RDataFrame('newtree', fakeTauFile)
    # df_tauF = df_tauF.Define('tausF_1pt_corrected', mapping_expression)
    
    # ['tausT_1lepton1_charge', 'tausT_leptons_charge', 'tausT_1lepton1_deltaR', 'tausT_1phi']
    # all_columns = list(df_tauF.GetColumnNames()) + ['tausF_1pt_corrected']
    # df_tauF_new = df_tauF_new.Define('tausF_1pt', 'tausF_1pt_corrected')
    
    
    #!replace tausT variables with tausFMorphed variabels too, so that fakeTau can be used in BDT application
    
    

    # df_tauF_data = ROOT.RDataFrame('newtree', inputDataFile)
    # all_columns = list(df_tauF_data.GetColumnNames()) + ['tausF_1pt_corrected']
    # df_tauF_data_new = df_tauF_data_new.Define('tausF_1pt_corrected', mapping_expression)
    # print('tausF_1pt morphed!!!' )


def replaceTauTVar(fakeTauFile):
    df_tauF = ROOT.RDataFrame('newtree', fakeTauFile)
    #!replace tauT pt related variables with tausFMophed relatec variables
    all_columns = df_tauF.GetColumnNames() 
    VarToTausFMorph = [ 'tausT_leptonsT_invariantMass', 'tausT_invariantMass', 'tausT_1Met_transMass', 'tausT_1lepton1Met1_stransMass', 'tausT_1pt', 'jets_tausT_invariantMass', 'tausT_MHT', 'tausT_HT', 'tausT_jet1_Met_transMass', 'tausT_jet_invariantMass', 'tausT_leptonsT_transMass']#rariables to be replaced with tausFMorphed variables
    
    extraVarsFromF = ['tausT_1lepton1_deltaR', 'tausT_leptons_charge', 'tausT_1phi', 'tausT_1lepton1_charge', 'tausT_1jetEtaAbs' , 'bjetsM_tausT_minDeltaR'] #Variables to be replaced with tausF variables
    exex = [  'tausT_1eta',  'tausT_leptonsTMVA_minDeltaR', 'tausT_leptonsTopMVA_chargeMulti',  'tausT_1decayMode', 'tausT_1prongNum',   'tausT_1jetPt',  'tausT_1charge', 'tausT_1neutralIso']
    extraVarsFromF = extraVarsFromF + exex
    
    tausF_features = ["tausF_1pt", "tausF_MHT", "tausF_HT", "tausF_invariantMass", "tausF_1Met_transMass"]#!!!for 1tau0l BDT
    # tausF_features=[]#!testing
    columns_to_remove = VarToTausFMorph + extraVarsFromF + tausF_features
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]
    # print('all columns now: ', df_tauF.GetColumnNames())
    df_tauF.Snapshot('newtree', fakeTauFile, columns_to_keep)
    
    df_tauF_new = ROOT.RDataFrame('newtree', fakeTauFile)
    for itauV in VarToTausFMorph:
        newBranch = itauV.replace('tausT', 'tausFMorph')
        df_tauF_new = df_tauF_new.Define(itauV, newBranch)
    for ivar in extraVarsFromF:
        newBranch = ivar.replace('tausT', 'tausF')
        df_tauF_new = df_tauF_new.Define(ivar, newBranch)
        
    for iVar in tausF_features:
        newBranch = iVar.replace('tausF', 'tausFMorph')
        df_tauF_new = df_tauF_new.Define(iVar, newBranch)
        
        
    df_tauF_new.Snapshot('newtree', fakeTauFile)
    print('tausT variables replaced with tausFMorphed variables!!!')
    print('tausT variables replaced with tausF variables!!!')
    print('tauF variables replaced with tauFMorphed variables!!!')
    print('file: ', fakeTauFile)
    


 
if __name__=='__main__':
    main()