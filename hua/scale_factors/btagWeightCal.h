#include "BTagCalibrationStandalone.h"
#include "BTagCalibrationStandalone.cpp"
#include "TH2D.h"

Double_t * evalEventSF( const TTreeReaderArray<TLorentzVector> & AK4Jets, const TTreeReaderArray<Int_t>& AK4JetFlavor, TTreeReaderArray<Double_t> & AK4JetBtag, BTagCalibrationReader CSV_nominal) {
		// mychain.SetBranchAddress("jets_flavour", &myjets_flavor);
    
        Double_t * output;
        output = new Double_t[22]; //returned by evalEventSF
        
        Double_t csv_weight_BF_ak4 = 1.0;
        Double_t csv_weight_CF_ak4 = 1.0;
        Double_t csv_weight_LF_ak4 = 1.0;
        Double_t csv_weight_total_ak4 = 1.0;
        
        //JES up and down
        Double_t csv_weight_BF_ak4JESUp = 1.0;
        Double_t csv_weight_CF_ak4JESUp = 1.0;
        Double_t csv_weight_LF_ak4JESUp = 1.0;
        Double_t csv_weight_total_ak4JESUp = 1.0;
        Double_t csv_weight_total_ak8JESUp = 1.0;
        Double_t csv_weight_total_JESUp = 1.0;
        Double_t csv_weight_BF_ak4JESDown = 1.0;
        Double_t csv_weight_CF_ak4JESDown = 1.0;
        Double_t csv_weight_LF_ak4JESDown = 1.0;
        Double_t csv_weight_total_ak4JESDown = 1.0;
        
        //HF purity up and down
        Double_t csv_weight_BF_ak4HFUp = 1.0;
        Double_t csv_weight_CF_ak4HFUp = 1.0;
        Double_t csv_weight_LF_ak4HFUp = 1.0;
        Double_t csv_weight_total_ak4HFUp = 1.0;
        Double_t csv_weight_BF_ak4HFDown = 1.0;
        Double_t csv_weight_CF_ak4HFDown = 1.0;
        Double_t csv_weight_LF_ak4HFDown = 1.0;
        Double_t csv_weight_total_ak4HFDown = 1.0;
        
        //LF purity up and down
        Double_t csv_weight_BF_ak4LFUp = 1.0;
        Double_t csv_weight_CF_ak4LFUp = 1.0;
        Double_t csv_weight_LF_ak4LFUp = 1.0;
        Double_t csv_weight_total_ak4LFUp = 1.0;
        Double_t csv_weight_BF_ak4LFDown = 1.0;
        Double_t csv_weight_CF_ak4LFDown = 1.0;
        Double_t csv_weight_LF_ak4LFDown = 1.0;
        Double_t csv_weight_total_ak4LFDown = 1.0;
        
        //HF linear and quadratic statistics up and down
        Double_t csv_weight_BF_ak4hfstats1Up = 1.0;
        Double_t csv_weight_CF_ak4hfstats1Up = 1.0;
        Double_t csv_weight_LF_ak4hfstats1Up = 1.0;
        Double_t csv_weight_total_ak4hfstats1Up = 1.0;
        Double_t csv_weight_BF_ak4hfstats1Down = 1.0;
        Double_t csv_weight_CF_ak4hfstats1Down = 1.0;
        Double_t csv_weight_LF_ak4hfstats1Down = 1.0;
        Double_t csv_weight_total_ak4hfstats1Down = 1.0;
        Double_t csv_weight_BF_ak4hfstats2Up = 1.0;
        Double_t csv_weight_CF_ak4hfstats2Up = 1.0;
        Double_t csv_weight_LF_ak4hfstats2Up = 1.0;
        Double_t csv_weight_total_ak4hfstats2Up = 1.0;
        Double_t csv_weight_BF_ak4hfstats2Down = 1.0;
        Double_t csv_weight_CF_ak4hfstats2Down = 1.0;
        Double_t csv_weight_LF_ak4hfstats2Down = 1.0;
        Double_t csv_weight_total_ak4hfstats2Down = 1.0;
        
        //LF linear and quadratic statistics up and down
        Double_t csv_weight_BF_ak4lfstats1Up = 1.0;
        Double_t csv_weight_CF_ak4lfstats1Up = 1.0;
        Double_t csv_weight_LF_ak4lfstats1Up = 1.0;
        Double_t csv_weight_total_ak4lfstats1Up = 1.0;
        Double_t csv_weight_BF_ak4lfstats1Down = 1.0;
        Double_t csv_weight_CF_ak4lfstats1Down = 1.0;
        Double_t csv_weight_LF_ak4lfstats1Down = 1.0;
        Double_t csv_weight_total_ak4lfstats1Down = 1.0;
        Double_t csv_weight_BF_ak4lfstats2Up = 1.0;
        Double_t csv_weight_CF_ak4lfstats2Up = 1.0;
        Double_t csv_weight_LF_ak4lfstats2Up = 1.0;
        Double_t csv_weight_total_ak4lfstats2Up = 1.0;
        Double_t csv_weight_BF_ak4lfstats2Down = 1.0;
        Double_t csv_weight_CF_ak4lfstats2Down = 1.0;
        Double_t csv_weight_LF_ak4lfstats2Down = 1.0;
        Double_t csv_weight_total_ak4lfstats2Down = 1.0;
        
        //CF linear and quadratic statistics up and down
        Double_t csv_weight_BF_ak4cfErr1Up = 1.0;
        Double_t csv_weight_CF_ak4cfErr1Up = 1.0;
        Double_t csv_weight_LF_ak4cfErr1Up = 1.0;
        Double_t csv_weight_total_ak4cfErr1Up = 1.0;
        Double_t csv_weight_BF_ak4cfErr1Down = 1.0;
        Double_t csv_weight_CF_ak4cfErr1Down = 1.0;
        Double_t csv_weight_LF_ak4cfErr1Down = 1.0;
        Double_t csv_weight_total_ak4cfErr1Down = 1.0;
        Double_t csv_weight_BF_ak4cfErr2Up = 1.0;
        Double_t csv_weight_CF_ak4cfErr2Up = 1.0;
        Double_t csv_weight_LF_ak4cfErr2Up = 1.0;
        Double_t csv_weight_total_ak4cfErr2Up = 1.0;
        Double_t csv_weight_BF_ak4cfErr2Down = 1.0;
        Double_t csv_weight_CF_ak4cfErr2Down = 1.0;
        Double_t csv_weight_LF_ak4cfErr2Down = 1.0;
        Double_t csv_weight_total_ak4cfErr2Down = 1.0;
        
        Double_t nL = 0;
        Double_t nC = 0;
        Double_t nB = 0;
         
            //loop over AK4 jets and compute scale factors depending on jet flavor, absolute value of jet eta, jet pt, jet CSV score
         
        if ( AK4Jets.GetSize() > 0 ) { 
        
            for (UInt_t i = 0; i < AK4Jets.GetSize(); i++) {
                
                if ( fabs(AK4JetFlavor.At(i)) == 5) { //b flavor
                    
                    nB++;
					
                    Double_t mycsv_weight_BF_ak4 = CSV_nominal.eval_auto_bounds("central", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_BF_ak4JESUp = CSV_nominal.eval_auto_bounds("up_jes", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_BF_ak4JESDown = CSV_nominal.eval_auto_bounds("down_jes", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    //no uncertainty on contamination from HF sample when computing HF scale factors
					Double_t mycsv_weight_BF_ak4LFUp = CSV_nominal.eval_auto_bounds("up_lf", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_BF_ak4LFDown = CSV_nominal.eval_auto_bounds("down_lf", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_BF_ak4hfstats1Up = CSV_nominal.eval_auto_bounds("up_hfstats1", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_BF_ak4hfstats1Down = CSV_nominal.eval_auto_bounds("down_hfstats1", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_BF_ak4hfstats2Up = CSV_nominal.eval_auto_bounds("up_hfstats2", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_BF_ak4hfstats2Down = CSV_nominal.eval_auto_bounds("down_hfstats2", BTagEntry::FLAV_B, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
					//no uncertainty on statistics of LF sample when computing HF scale factors
                    
                    if (mycsv_weight_BF_ak4 == 0) cout << "!!!!!!!!!!!!!!!!!!!!!!" << endl;
                    
                    if (mycsv_weight_BF_ak4 != 0) csv_weight_BF_ak4 *= mycsv_weight_BF_ak4;
                    if (mycsv_weight_BF_ak4JESUp != 0) csv_weight_BF_ak4JESUp *= mycsv_weight_BF_ak4JESUp;
                    if (mycsv_weight_BF_ak4JESDown != 0) csv_weight_BF_ak4JESDown *= mycsv_weight_BF_ak4JESDown;
                    if (mycsv_weight_BF_ak4LFUp != 0) csv_weight_BF_ak4LFUp *= mycsv_weight_BF_ak4LFUp;
                    if (mycsv_weight_BF_ak4LFDown != 0) csv_weight_BF_ak4LFDown *= mycsv_weight_BF_ak4LFDown;
                    if (mycsv_weight_BF_ak4hfstats1Up != 0) csv_weight_BF_ak4hfstats1Up *= mycsv_weight_BF_ak4hfstats1Up;
                    if (mycsv_weight_BF_ak4hfstats1Down != 0) csv_weight_BF_ak4hfstats1Down *= mycsv_weight_BF_ak4hfstats1Down;
                    if (mycsv_weight_BF_ak4hfstats2Up != 0) csv_weight_BF_ak4hfstats2Up *= mycsv_weight_BF_ak4hfstats2Up;
                    if (mycsv_weight_BF_ak4hfstats2Down != 0) csv_weight_BF_ak4hfstats2Down *= mycsv_weight_BF_ak4hfstats2Down;
                }
                
                else if ( fabs(AK4JetFlavor.At(i)) == 4) { //c flavor
                    
                    nC++;
                
                    Double_t mycsv_weight_CF_ak4 = CSV_nominal.eval_auto_bounds("central", BTagEntry::FLAV_C, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i)); //always 1, checked
					Double_t mycsv_weight_CF_ak4JESUp = CSV_nominal.eval_auto_bounds("up_jes", BTagEntry::FLAV_C, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_CF_ak4JESDown = CSV_nominal.eval_auto_bounds("down_jes", BTagEntry::FLAV_C, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_CF_ak4cfErr1Up = CSV_nominal.eval_auto_bounds("up_cferr1", BTagEntry::FLAV_C, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_CF_ak4cfErr1Down = CSV_nominal.eval_auto_bounds("down_cferr1", BTagEntry::FLAV_C, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_CF_ak4cfErr2Up = CSV_nominal.eval_auto_bounds("up_cferr2", BTagEntry::FLAV_C, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_CF_ak4cfErr2Down = CSV_nominal.eval_auto_bounds("down_cferr2", BTagEntry::FLAV_C, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    //for c-flavored jets only the cfErr uncertainty is applied
                    
                    if (mycsv_weight_CF_ak4 != 0) csv_weight_CF_ak4 *= mycsv_weight_CF_ak4;
                    if (mycsv_weight_CF_ak4JESUp != 0) csv_weight_CF_ak4JESUp *= mycsv_weight_CF_ak4JESUp; 
                    if (mycsv_weight_CF_ak4JESDown != 0) csv_weight_CF_ak4JESDown *= mycsv_weight_CF_ak4JESDown;
					if (mycsv_weight_CF_ak4cfErr1Up != 0) csv_weight_CF_ak4cfErr1Up *= mycsv_weight_CF_ak4cfErr1Up;
                    if (mycsv_weight_CF_ak4cfErr1Down != 0) csv_weight_CF_ak4cfErr1Down *= mycsv_weight_CF_ak4cfErr1Down;
                    if (mycsv_weight_CF_ak4cfErr2Up != 0) csv_weight_CF_ak4cfErr2Up *= mycsv_weight_CF_ak4cfErr2Up;
                    if (mycsv_weight_CF_ak4cfErr2Down != 0) csv_weight_CF_ak4cfErr2Down *= mycsv_weight_CF_ak4cfErr2Down;
                
                }
                
                else  { //light flavor
					
                    nL++;
                
                    Double_t mycsv_weight_LF_ak4 = CSV_nominal.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_LF_ak4JESUp = CSV_nominal.eval_auto_bounds("up_jes", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_LF_ak4JESDown = CSV_nominal.eval_auto_bounds("down_jes", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_LF_ak4HFUp = CSV_nominal.eval_auto_bounds("up_hf", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_LF_ak4HFDown = CSV_nominal.eval_auto_bounds("down_hf", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    //no uncertainty on contamination from LF sample when computing LF scale factors
					Double_t mycsv_weight_LF_ak4lfstats1Up = CSV_nominal.eval_auto_bounds("up_lfstats1", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_LF_ak4lfstats1Down = CSV_nominal.eval_auto_bounds("down_lfstats1", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_LF_ak4lfstats2Up = CSV_nominal.eval_auto_bounds("up_lfstats2", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
                    Double_t mycsv_weight_LF_ak4lfstats2Down = CSV_nominal.eval_auto_bounds("down_lfstats2", BTagEntry::FLAV_UDSG, fabs(AK4Jets.At(i).Eta()), AK4Jets.At(i).Pt(), AK4JetBtag.At(i));
					//no uncertainty on statistics of HF sample when computing LF scale factors
                    //no cfErr is computed for light-flavored jets
                    
                    
                    if (mycsv_weight_LF_ak4 != 0) csv_weight_LF_ak4 *= mycsv_weight_LF_ak4;
                    if (mycsv_weight_LF_ak4JESUp != 0) csv_weight_LF_ak4JESUp *= mycsv_weight_LF_ak4JESUp;
                    if (mycsv_weight_LF_ak4JESDown != 0) csv_weight_LF_ak4JESDown *= mycsv_weight_LF_ak4JESDown;
                    if (mycsv_weight_LF_ak4HFUp != 0) csv_weight_LF_ak4HFUp *= mycsv_weight_LF_ak4HFUp;
                    if (mycsv_weight_LF_ak4HFDown != 0) csv_weight_LF_ak4HFDown *= mycsv_weight_LF_ak4HFDown;
					if (mycsv_weight_LF_ak4lfstats1Up != 0) csv_weight_LF_ak4lfstats1Up *= mycsv_weight_LF_ak4lfstats1Up;
                    if (mycsv_weight_LF_ak4lfstats1Down != 0) csv_weight_LF_ak4lfstats1Down *= mycsv_weight_LF_ak4lfstats1Down;
                    if (mycsv_weight_LF_ak4lfstats2Up != 0) csv_weight_LF_ak4lfstats2Up *= mycsv_weight_LF_ak4lfstats2Up;
                    if (mycsv_weight_LF_ak4lfstats2Down != 0) csv_weight_LF_ak4lfstats2Down *= mycsv_weight_LF_ak4lfstats2Down;
                
                }
            } // end loop over jets
        }
            
            //compute total ak4 weight
            //NOTE: all the weights from all the systematics are included. Some of them may be 1.0 if no uncertainty is present (e.g. csv_weight_BF_ak4cfErr2Down = 1.0)
            csv_weight_total_ak4 = csv_weight_BF_ak4 * csv_weight_CF_ak4 * csv_weight_LF_ak4;
            csv_weight_total_ak4JESUp = csv_weight_BF_ak4JESUp * csv_weight_CF_ak4JESUp * csv_weight_LF_ak4JESUp;
            csv_weight_total_ak4JESDown = csv_weight_BF_ak4JESDown * csv_weight_CF_ak4JESDown * csv_weight_LF_ak4JESDown;
            csv_weight_total_ak4HFUp = csv_weight_BF_ak4HFUp * csv_weight_CF_ak4HFUp * csv_weight_LF_ak4HFUp;
			csv_weight_total_ak4HFDown = csv_weight_BF_ak4HFDown * csv_weight_CF_ak4HFDown * csv_weight_LF_ak4HFDown;
            csv_weight_total_ak4LFUp = csv_weight_BF_ak4LFUp * csv_weight_CF_ak4LFUp * csv_weight_LF_ak4LFUp;
            csv_weight_total_ak4LFDown = csv_weight_BF_ak4LFDown * csv_weight_CF_ak4LFDown * csv_weight_LF_ak4LFDown;
            csv_weight_total_ak4hfstats1Up = csv_weight_BF_ak4hfstats1Up * csv_weight_CF_ak4hfstats1Up * csv_weight_LF_ak4hfstats1Up;
            csv_weight_total_ak4hfstats1Down = csv_weight_BF_ak4hfstats1Down * csv_weight_CF_ak4hfstats1Down * csv_weight_LF_ak4hfstats1Down;
            csv_weight_total_ak4hfstats2Up = csv_weight_BF_ak4hfstats2Up * csv_weight_CF_ak4hfstats2Up * csv_weight_LF_ak4hfstats2Up;
            csv_weight_total_ak4hfstats2Down = csv_weight_BF_ak4hfstats2Down * csv_weight_CF_ak4hfstats2Down * csv_weight_LF_ak4hfstats2Down;
            csv_weight_total_ak4lfstats1Up = csv_weight_BF_ak4lfstats1Up * csv_weight_CF_ak4lfstats1Up * csv_weight_LF_ak4lfstats1Up;
            csv_weight_total_ak4lfstats1Down = csv_weight_BF_ak4lfstats1Down * csv_weight_CF_ak4lfstats1Down * csv_weight_LF_ak4lfstats1Down;
            csv_weight_total_ak4lfstats2Up = csv_weight_BF_ak4lfstats2Up * csv_weight_CF_ak4lfstats2Up * csv_weight_LF_ak4lfstats2Up;
            csv_weight_total_ak4lfstats2Down = csv_weight_BF_ak4lfstats2Down * csv_weight_CF_ak4lfstats2Down * csv_weight_LF_ak4lfstats2Down;
            csv_weight_total_ak4cfErr1Up = csv_weight_BF_ak4cfErr1Up * csv_weight_CF_ak4cfErr1Up * csv_weight_LF_ak4cfErr1Up;
            csv_weight_total_ak4cfErr1Down = csv_weight_BF_ak4cfErr1Down * csv_weight_CF_ak4cfErr1Down * csv_weight_LF_ak4cfErr1Down;
            csv_weight_total_ak4cfErr2Up = csv_weight_BF_ak4cfErr2Up * csv_weight_CF_ak4cfErr2Up * csv_weight_LF_ak4cfErr2Up;
            csv_weight_total_ak4cfErr2Down = csv_weight_BF_ak4cfErr2Down * csv_weight_CF_ak4cfErr2Down * csv_weight_LF_ak4cfErr2Down;
           

            output[0] = csv_weight_total_ak4;
            output[1] = csv_weight_total_ak4JESUp;
            output[2] = csv_weight_total_ak4JESDown;
            output[3] = csv_weight_total_ak4HFUp;
            output[4] = csv_weight_total_ak4HFDown;
            output[5] = csv_weight_total_ak4LFUp;
            output[6] = csv_weight_total_ak4LFDown;
            output[7] = csv_weight_total_ak4hfstats1Up;
            output[8] = csv_weight_total_ak4hfstats1Down;
            output[9] = csv_weight_total_ak4hfstats2Up;
            output[10] = csv_weight_total_ak4hfstats2Down;
            output[11] = csv_weight_total_ak4lfstats1Up;
            output[12] = csv_weight_total_ak4lfstats1Down;
            output[13] = csv_weight_total_ak4lfstats2Up;
            output[14] = csv_weight_total_ak4lfstats2Down;
            output[15] = csv_weight_total_ak4cfErr1Up;
            output[16] = csv_weight_total_ak4cfErr1Down;
            output[17] = csv_weight_total_ak4cfErr2Up;
            output[18] = csv_weight_total_ak4cfErr2Down;
            output[19] = nL;
            output[20] = nC;
            output[21] = nB;
            
            return output;
            delete output;
            // delete AK4Jets;
            // delete AK4JetBtag;
            
}


Double_t getHLTweight( const Double_t HT, const Int_t jets_number ){
	static  TFile * input_TriggerSF = new TFile( "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/scale_factors/TriggerSF_2D_2jetsinpresel.root", "READ" );
	static TH2D * triggerSF = (TH2D*)input_TriggerSF->Get("SF_njetsVsHT");
    Double_t mytriggerWeight = triggerSF->GetBinContent(triggerSF->FindBin(HT, jets_number ));
    return mytriggerWeight;

}
