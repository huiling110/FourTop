double * evalEventSF( vector<TLorentzVector> * AK4Jets, vector<int> * AK4JetFlavor, vector<double> * AK4JetBtag, BTagCalibrationReader CSVReader) {
    
        double * output;
        output = new double[19]; //returned by evalEventSF
        
        double csv_weight_BF_ak4 = 1.0;
        double csv_weight_CF_ak4 = 1.0;
        double csv_weight_LF_ak4 = 1.0;
        double csv_weight_total_ak4 = 1.0;
        
        //jes up and down
        double csv_weight_BF_ak4jesUp = 1.0;
        double csv_weight_CF_ak4jesUp = 1.0;
        double csv_weight_LF_ak4jesUp = 1.0;
        double csv_weight_total_ak4jesUp = 1.0;
        double csv_weight_total_jesUp = 1.0;
        double csv_weight_BF_ak4jesDown = 1.0;
        double csv_weight_CF_ak4jesDown = 1.0;
        double csv_weight_LF_ak4jesDown = 1.0;
        double csv_weight_total_ak4jesDown = 1.0;
        /*double csv_weight_BF_ak4jesEC2_2016Up = 1.0;
        double csv_weight_CF_ak4jesEC2_2016Up = 1.0;
        double csv_weight_LF_ak4jesEC2_2016Up = 1.0;
        double csv_weight_total_ak4jesEC2_2016Up = 1.0;
        double csv_weight_total_jesEC2_2016Up = 1.0;
        double csv_weight_BF_ak4jesEC2_2016Down = 1.0;
        double csv_weight_CF_ak4jesEC2_2016Down = 1.0;
        double csv_weight_LF_ak4jesEC2_2016Down = 1.0;
        double csv_weight_total_ak4jesEC2_2016Down = 1.0;
        double csv_weight_BF_ak4jesEC2Up = 1.0;
        double csv_weight_CF_ak4jesEC2Up = 1.0;
        double csv_weight_LF_ak4jesEC2Up = 1.0;
        double csv_weight_total_ak4jesEC2Up = 1.0;
        double csv_weight_total_jesEC2Up = 1.0;
        double csv_weight_BF_ak4jesEC2Down = 1.0;
        double csv_weight_CF_ak4jesEC2Down = 1.0;
        double csv_weight_LF_ak4jesEC2Down = 1.0;
        double csv_weight_total_ak4jesEC2Down = 1.0;
        double csv_weight_BF_ak4jesBBEC1Up = 1.0;
        double csv_weight_CF_ak4jesBBEC1Up = 1.0;
        double csv_weight_LF_ak4jesBBEC1Up = 1.0;
        double csv_weight_total_ak4jesBBEC1Up = 1.0;
        double csv_weight_total_jesBBEC1Up = 1.0;
        double csv_weight_BF_ak4jesBBEC1Down = 1.0;
        double csv_weight_CF_ak4jesBBEC1Down = 1.0;
        double csv_weight_LF_ak4jesBBEC1Down = 1.0;
        double csv_weight_total_ak4jesBBEC1Down = 1.0;
        double csv_weight_BF_ak4jesAbsoluteUp = 1.0;
        double csv_weight_CF_ak4jesAbsoluteUp = 1.0;
        double csv_weight_LF_ak4jesAbsoluteUp = 1.0;
        double csv_weight_total_ak4jesAbsoluteUp = 1.0;
        double csv_weight_total_jesAbsoluteUp = 1.0;
        double csv_weight_BF_ak4jesAbsoluteDown = 1.0;
        double csv_weight_CF_ak4jesAbsoluteDown = 1.0;
        double csv_weight_LF_ak4jesAbsoluteDown = 1.0;
        double csv_weight_total_ak4jesAbsoluteDown = 1.0;
        double csv_weight_BF_ak4jesAbsolute_2016Up = 1.0;
        double csv_weight_CF_ak4jesAbsolute_2016Up = 1.0;
        double csv_weight_LF_ak4jesAbsolute_2016Up = 1.0;
        double csv_weight_total_ak4jesAbsolute_2016Up = 1.0;
        double csv_weight_total_jesAbsolute_2016Up = 1.0;
        double csv_weight_BF_ak4jesAbsolute_2016Down = 1.0;
        double csv_weight_CF_ak4jesAbsolute_2016Down = 1.0;
        double csv_weight_LF_ak4jesAbsolute_2016Down = 1.0;
        double csv_weight_total_ak4jesAbsolute_2016Down = 1.0;
        double csv_weight_BF_ak4jesHFUp = 1.0;
        double csv_weight_CF_ak4jesHFUp = 1.0;
        double csv_weight_LF_ak4jesHFUp = 1.0;
        double csv_weight_total_ak4jesHFUp = 1.0;
        double csv_weight_total_jesHFUp = 1.0;
        double csv_weight_BF_ak4jesHFDown = 1.0;
        double csv_weight_CF_ak4jesHFDown = 1.0;
        double csv_weight_LF_ak4jesHFDown = 1.0;
        double csv_weight_total_ak4jesHFDown = 1.0;
        double csv_weight_BF_ak4jesFlavorQCDUp = 1.0;
        double csv_weight_CF_ak4jesFlavorQCDUp = 1.0;
        double csv_weight_LF_ak4jesFlavorQCDUp = 1.0;
        double csv_weight_total_ak4jesFlavorQCDUp = 1.0;
        double csv_weight_total_jesFlavorQCDUp = 1.0;
        double csv_weight_BF_ak4jesFlavorQCDDown = 1.0;
        double csv_weight_CF_ak4jesFlavorQCDDown = 1.0;
        double csv_weight_LF_ak4jesFlavorQCDDown = 1.0;
        double csv_weight_total_ak4jesFlavorQCDDown = 1.0;
        double csv_weight_BF_ak4jesBBEC1_2016Up = 1.0;
        double csv_weight_CF_ak4jesBBEC1_2016Up = 1.0;
        double csv_weight_LF_ak4jesBBEC1_2016Up = 1.0;
        double csv_weight_total_ak4jesBBEC1_2016Up = 1.0;
        double csv_weight_total_jesBBEC1_2016Up = 1.0;
        double csv_weight_BF_ak4jesBBEC1_2016Down = 1.0;
        double csv_weight_CF_ak4jesBBEC1_2016Down = 1.0;
        double csv_weight_LF_ak4jesBBEC1_2016Down = 1.0;
        double csv_weight_total_ak4jesBBEC1_2016Down = 1.0;
        double csv_weight_BF_ak4jesRelativeBalUp = 1.0;
        double csv_weight_CF_ak4jesRelativeBalUp = 1.0;
        double csv_weight_LF_ak4jesRelativeBalUp = 1.0;
        double csv_weight_total_ak4jesRelativeBalUp = 1.0;
        double csv_weight_total_jesRelativeBalUp = 1.0;
        double csv_weight_BF_ak4jesRelativeBalDown = 1.0;
        double csv_weight_CF_ak4jesRelativeBalDown = 1.0;
        double csv_weight_LF_ak4jesRelativeBalDown = 1.0;
        double csv_weight_total_ak4jesRelativeBalDown = 1.0;
        double csv_weight_BF_ak4jesHF_2016Up = 1.0;
        double csv_weight_CF_ak4jesHF_2016Up = 1.0;
        double csv_weight_LF_ak4jesHF_2016Up = 1.0;
        double csv_weight_total_ak4jesHF_2016Up = 1.0;
        double csv_weight_total_jesHF_2016Up = 1.0;
        double csv_weight_BF_ak4jesHF_2016Down = 1.0;
        double csv_weight_CF_ak4jesHF_2016Down = 1.0;
        double csv_weight_LF_ak4jesHF_2016Down = 1.0;
        double csv_weight_total_ak4jesHF_2016Down = 1.0;
        double csv_weight_BF_ak4jesRelativeSample_2016Up = 1.0;
        double csv_weight_CF_ak4jesRelativeSample_2016Up = 1.0;
        double csv_weight_LF_ak4jesRelativeSample_2016Up = 1.0;
        double csv_weight_total_ak4jesRelativeSample_2016Up = 1.0;
        double csv_weight_total_jesRelativeSample_2016Up = 1.0;
        double csv_weight_BF_ak4jesRelativeSample_2016Down = 1.0;
        double csv_weight_CF_ak4jesRelativeSample_2016Down = 1.0;
        double csv_weight_LF_ak4jesRelativeSample_2016Down = 1.0;
        double csv_weight_total_ak4jesRelativeSample_2016Down = 1.0;
        */
        //HF purity up and down
        double csv_weight_BF_ak4HFUp = 1.0;
        double csv_weight_CF_ak4HFUp = 1.0;
        double csv_weight_LF_ak4HFUp = 1.0;
        double csv_weight_total_ak4HFUp = 1.0;
        double csv_weight_BF_ak4HFDown = 1.0;
        double csv_weight_CF_ak4HFDown = 1.0;
        double csv_weight_LF_ak4HFDown = 1.0;
        double csv_weight_total_ak4HFDown = 1.0;
        
        //LF purity up and down
        double csv_weight_BF_ak4LFUp = 1.0;
        double csv_weight_CF_ak4LFUp = 1.0;
        double csv_weight_LF_ak4LFUp = 1.0;
        double csv_weight_total_ak4LFUp = 1.0;
        double csv_weight_BF_ak4LFDown = 1.0;
        double csv_weight_CF_ak4LFDown = 1.0;
        double csv_weight_LF_ak4LFDown = 1.0;
        double csv_weight_total_ak4LFDown = 1.0;
        
        //HF linear and quadratic statistics up and down
        double csv_weight_BF_ak4hfstats1Up = 1.0;
        double csv_weight_CF_ak4hfstats1Up = 1.0;
        double csv_weight_LF_ak4hfstats1Up = 1.0;
        double csv_weight_total_ak4hfstats1Up = 1.0;
        double csv_weight_BF_ak4hfstats1Down = 1.0;
        double csv_weight_CF_ak4hfstats1Down = 1.0;
        double csv_weight_LF_ak4hfstats1Down = 1.0;
        double csv_weight_total_ak4hfstats1Down = 1.0;
        double csv_weight_BF_ak4hfstats2Up = 1.0;
        double csv_weight_CF_ak4hfstats2Up = 1.0;
        double csv_weight_LF_ak4hfstats2Up = 1.0;
        double csv_weight_total_ak4hfstats2Up = 1.0;
        double csv_weight_BF_ak4hfstats2Down = 1.0;
        double csv_weight_CF_ak4hfstats2Down = 1.0;
        double csv_weight_LF_ak4hfstats2Down = 1.0;
        double csv_weight_total_ak4hfstats2Down = 1.0;
        
        //LF linear and quadratic statistics up and down
        double csv_weight_BF_ak4lfstats1Up = 1.0;
        double csv_weight_CF_ak4lfstats1Up = 1.0;
        double csv_weight_LF_ak4lfstats1Up = 1.0;
        double csv_weight_total_ak4lfstats1Up = 1.0;
        double csv_weight_BF_ak4lfstats1Down = 1.0;
        double csv_weight_CF_ak4lfstats1Down = 1.0;
        double csv_weight_LF_ak4lfstats1Down = 1.0;
        double csv_weight_total_ak4lfstats1Down = 1.0;
        double csv_weight_BF_ak4lfstats2Up = 1.0;
        double csv_weight_CF_ak4lfstats2Up = 1.0;
        double csv_weight_LF_ak4lfstats2Up = 1.0;
        double csv_weight_total_ak4lfstats2Up = 1.0;
        double csv_weight_BF_ak4lfstats2Down = 1.0;
        double csv_weight_CF_ak4lfstats2Down = 1.0;
        double csv_weight_LF_ak4lfstats2Down = 1.0;
        double csv_weight_total_ak4lfstats2Down = 1.0;
        
        //CF linear and quadratic statistics up and down
        double csv_weight_BF_ak4cfErr1Up = 1.0;
        double csv_weight_CF_ak4cfErr1Up = 1.0;
        double csv_weight_LF_ak4cfErr1Up = 1.0;
        double csv_weight_total_ak4cfErr1Up = 1.0;
        double csv_weight_BF_ak4cfErr1Down = 1.0;
        double csv_weight_CF_ak4cfErr1Down = 1.0;
        double csv_weight_LF_ak4cfErr1Down = 1.0;
        double csv_weight_total_ak4cfErr1Down = 1.0;
        double csv_weight_BF_ak4cfErr2Up = 1.0;
        double csv_weight_CF_ak4cfErr2Up = 1.0;
        double csv_weight_LF_ak4cfErr2Up = 1.0;
        double csv_weight_total_ak4cfErr2Up = 1.0;
        double csv_weight_BF_ak4cfErr2Down = 1.0;
        double csv_weight_CF_ak4cfErr2Down = 1.0;
        double csv_weight_LF_ak4cfErr2Down = 1.0;
        double csv_weight_total_ak4cfErr2Down = 1.0;
        
        double nL = 0;
        double nC = 0;
        double nB = 0;
         
            //loop over AK4 jets and compute scale factors depending on jet flavor, absolute value of jet eta, jet pt, jet CSV score
         
        if ( AK4Jets->size() > 0 ) { 
        
            for (int i = 0; i < AK4Jets->size(); i++) {
                
                if ( fabs(AK4JetFlavor->at(i)) == 5) { //b flavor
                    
                    double mycsv_weight_BF_ak4 = CSVReader.eval_auto_bounds("central", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesUp = CSVReader.eval_auto_bounds("up_jes", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesDown = CSVReader.eval_auto_bounds("down_jes", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    /*
                    double mycsv_weight_BF_ak4jesEC2_2016Up = CSVReader.eval_auto_bounds("up_jesEC2_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesEC2_2016Down = CSVReader.eval_auto_bounds("down_jesEC2_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesEC2Up = CSVReader.eval_auto_bounds("up_jesEC2", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesEC2Down = CSVReader.eval_auto_bounds("down_jesEC2", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesBBEC1Up = CSVReader.eval_auto_bounds("up_jesBBEC1", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesBBEC1Down = CSVReader.eval_auto_bounds("down_jesBBEC1", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesAbsoluteUp = CSVReader.eval_auto_bounds("up_jesAbsolute", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesAbsoluteDown = CSVReader.eval_auto_bounds("down_jesAbsolute", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesAbsolute_2016Up = CSVReader.eval_auto_bounds("up_jesAbsolute_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesAbsolute_2016Down = CSVReader.eval_auto_bounds("down_jesAbsolute_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesHFUp = CSVReader.eval_auto_bounds("up_jesHF", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesHFDown = CSVReader.eval_auto_bounds("down_jesHF", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesFlavorQCDUp = CSVReader.eval_auto_bounds("up_jesFlavorQCD", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesFlavorQCDDown = CSVReader.eval_auto_bounds("down_jesFlavorQCD", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesBBEC1_2016Up = CSVReader.eval_auto_bounds("up_jesBBEC1_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesBBEC1_2016Down = CSVReader.eval_auto_bounds("down_jesBBEC1_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesRelativeBalUp = CSVReader.eval_auto_bounds("up_jesRelativeBal", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesRelativeBalDown = CSVReader.eval_auto_bounds("down_jesRelativeBal", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesHF_2016Up = CSVReader.eval_auto_bounds("up_jesHF_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesHF_2016Down = CSVReader.eval_auto_bounds("down_jesHF_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesRelativeSample_2016Up = CSVReader.eval_auto_bounds("up_jesRelativeSample_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4jesRelativeSample_2016Down = CSVReader.eval_auto_bounds("down_jesRelativeSample_2016", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    */
                    //no uncertainty on contamination from HF sample when computing HF scale factors
					double mycsv_weight_BF_ak4LFUp = CSVReader.eval_auto_bounds("up_lf", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4LFDown = CSVReader.eval_auto_bounds("down_lf", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4hfstats1Up = CSVReader.eval_auto_bounds("up_hfstats1", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4hfstats1Down = CSVReader.eval_auto_bounds("down_hfstats1", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4hfstats2Up = CSVReader.eval_auto_bounds("up_hfstats2", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_BF_ak4hfstats2Down = CSVReader.eval_auto_bounds("down_hfstats2", BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    //no uncertainty on statistics of LF sample when computing HF scale factors
                    
                    if (mycsv_weight_BF_ak4 == 0) cout << "!!!!!!!!!!!!!!!!!!!!!!" << endl;
                    
                    if (mycsv_weight_BF_ak4 != 0) csv_weight_BF_ak4 *= mycsv_weight_BF_ak4;
                    if (mycsv_weight_BF_ak4jesUp != 0) csv_weight_BF_ak4jesUp *= mycsv_weight_BF_ak4jesUp;
                    if (mycsv_weight_BF_ak4jesDown != 0) csv_weight_BF_ak4jesDown *= mycsv_weight_BF_ak4jesDown;
                    /*
                    if (mycsv_weight_BF_ak4jesEC2_2016Up != 0) csv_weight_BF_ak4jesEC2_2016Up *= mycsv_weight_BF_ak4jesEC2_2016Up;
                    if (mycsv_weight_BF_ak4jesEC2_2016Down != 0) csv_weight_BF_ak4jesEC2_2016Down *= mycsv_weight_BF_ak4jesEC2_2016Down;
                    if (mycsv_weight_BF_ak4jesEC2Up != 0) csv_weight_BF_ak4jesEC2Up *= mycsv_weight_BF_ak4jesEC2Up;
                    if (mycsv_weight_BF_ak4jesEC2Down != 0) csv_weight_BF_ak4jesEC2Down *= mycsv_weight_BF_ak4jesEC2Down;
                    if (mycsv_weight_BF_ak4jesBBEC1Up != 0) csv_weight_BF_ak4jesBBEC1Up *= mycsv_weight_BF_ak4jesBBEC1Up;
                    if (mycsv_weight_BF_ak4jesBBEC1Down != 0) csv_weight_BF_ak4jesBBEC1Down *= mycsv_weight_BF_ak4jesBBEC1Down;
                    if (mycsv_weight_BF_ak4jesAbsoluteUp != 0) csv_weight_BF_ak4jesAbsoluteUp *= mycsv_weight_BF_ak4jesAbsoluteUp;
                    if (mycsv_weight_BF_ak4jesAbsoluteDown != 0) csv_weight_BF_ak4jesAbsoluteDown *= mycsv_weight_BF_ak4jesAbsoluteDown;
                    if (mycsv_weight_BF_ak4jesAbsolute_2016Up != 0) csv_weight_BF_ak4jesAbsolute_2016Up *= mycsv_weight_BF_ak4jesAbsolute_2016Up;
                    if (mycsv_weight_BF_ak4jesAbsolute_2016Down != 0) csv_weight_BF_ak4jesAbsolute_2016Down *= mycsv_weight_BF_ak4jesAbsolute_2016Down;
                    if (mycsv_weight_BF_ak4jesHFUp != 0) csv_weight_BF_ak4jesHFUp *= mycsv_weight_BF_ak4jesHFUp;
                    if (mycsv_weight_BF_ak4jesHFDown != 0) csv_weight_BF_ak4jesHFDown *= mycsv_weight_BF_ak4jesHFDown;
                    if (mycsv_weight_BF_ak4jesFlavorQCDUp != 0) csv_weight_BF_ak4jesFlavorQCDUp *= mycsv_weight_BF_ak4jesFlavorQCDUp;
                    if (mycsv_weight_BF_ak4jesFlavorQCDDown != 0) csv_weight_BF_ak4jesFlavorQCDDown *= mycsv_weight_BF_ak4jesFlavorQCDDown;
                    if (mycsv_weight_BF_ak4jesBBEC1_2016Up != 0) csv_weight_BF_ak4jesBBEC1_2016Up *= mycsv_weight_BF_ak4jesBBEC1_2016Up;
                    if (mycsv_weight_BF_ak4jesBBEC1_2016Down != 0) csv_weight_BF_ak4jesBBEC1_2016Down *= mycsv_weight_BF_ak4jesBBEC1_2016Down;
                    if (mycsv_weight_BF_ak4jesRelativeBalUp != 0) csv_weight_BF_ak4jesRelativeBalUp *= mycsv_weight_BF_ak4jesRelativeBalUp;
                    if (mycsv_weight_BF_ak4jesRelativeBalDown != 0) csv_weight_BF_ak4jesRelativeBalDown *= mycsv_weight_BF_ak4jesRelativeBalDown;
                    if (mycsv_weight_BF_ak4jesHF_2016Up != 0) csv_weight_BF_ak4jesHF_2016Up *= mycsv_weight_BF_ak4jesHF_2016Up;
                    if (mycsv_weight_BF_ak4jesHF_2016Down != 0) csv_weight_BF_ak4jesHF_2016Down *= mycsv_weight_BF_ak4jesHF_2016Down;
                    if (mycsv_weight_BF_ak4jesRelativeSample_2016Up != 0) csv_weight_BF_ak4jesRelativeSample_2016Up *= mycsv_weight_BF_ak4jesRelativeSample_2016Up;
                    if (mycsv_weight_BF_ak4jesRelativeSample_2016Down != 0) csv_weight_BF_ak4jesRelativeSample_2016Down *= mycsv_weight_BF_ak4jesRelativeSample_2016Down;
                    */
                    if (mycsv_weight_BF_ak4LFUp != 0) csv_weight_BF_ak4LFUp *= mycsv_weight_BF_ak4LFUp;
                    if (mycsv_weight_BF_ak4LFDown != 0) csv_weight_BF_ak4LFDown *= mycsv_weight_BF_ak4LFDown;
                    if (mycsv_weight_BF_ak4hfstats1Up != 0) csv_weight_BF_ak4hfstats1Up *= mycsv_weight_BF_ak4hfstats1Up;
                    if (mycsv_weight_BF_ak4hfstats1Down != 0) csv_weight_BF_ak4hfstats1Down *= mycsv_weight_BF_ak4hfstats1Down;
                    if (mycsv_weight_BF_ak4hfstats2Up != 0) csv_weight_BF_ak4hfstats2Up *= mycsv_weight_BF_ak4hfstats2Up;
                    if (mycsv_weight_BF_ak4hfstats2Down != 0) csv_weight_BF_ak4hfstats2Down *= mycsv_weight_BF_ak4hfstats2Down;
                }
                
                else if ( fabs(AK4JetFlavor->at(i)) == 4) { //c flavor
                    
                    double mycsv_weight_CF_ak4 = CSVReader.eval_auto_bounds("central", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i)); //always 1, checked
					double mycsv_weight_CF_ak4jesUp = CSVReader.eval_auto_bounds("up_jes", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesDown = CSVReader.eval_auto_bounds("down_jes", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    /*
                    double mycsv_weight_CF_ak4jesEC2_2016Up = CSVReader.eval_auto_bounds("up_jesEC2_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesEC2_2016Down = CSVReader.eval_auto_bounds("down_jesEC2_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesEC2Up = CSVReader.eval_auto_bounds("up_jesEC2", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesEC2Down = CSVReader.eval_auto_bounds("down_jesEC2", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesBBEC1Up = CSVReader.eval_auto_bounds("up_jesBBEC1", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesBBEC1Down = CSVReader.eval_auto_bounds("down_jesBBEC1", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesAbsoluteUp = CSVReader.eval_auto_bounds("up_jesAbsolute", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesAbsoluteDown = CSVReader.eval_auto_bounds("down_jesAbsolute", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesAbsolute_2016Up = CSVReader.eval_auto_bounds("up_jesAbsolute_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesAbsolute_2016Down = CSVReader.eval_auto_bounds("down_jesAbsolute_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesHFUp = CSVReader.eval_auto_bounds("up_jesHF", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesHFDown = CSVReader.eval_auto_bounds("down_jesHF", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesFlavorQCDUp = CSVReader.eval_auto_bounds("up_jesFlavorQCD", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesFlavorQCDDown = CSVReader.eval_auto_bounds("down_jesFlavorQCD", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesBBEC1_2016Up = CSVReader.eval_auto_bounds("up_jesBBEC1_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesBBEC1_2016Down = CSVReader.eval_auto_bounds("down_jesBBEC1_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesRelativeBalUp = CSVReader.eval_auto_bounds("up_jesRelativeBal", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesRelativeBalDown = CSVReader.eval_auto_bounds("down_jesRelativeBal", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesHF_2016Up = CSVReader.eval_auto_bounds("up_jesHF_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesHF_2016Down = CSVReader.eval_auto_bounds("down_jesHF_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesRelativeSample_2016Up = CSVReader.eval_auto_bounds("up_jesRelativeSample_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4jesRelativeSample_2016Down = CSVReader.eval_auto_bounds("down_jesRelativeSample_2016", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    */
                    double mycsv_weight_CF_ak4cfErr1Up = CSVReader.eval_auto_bounds("up_cferr1", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4cfErr1Down = CSVReader.eval_auto_bounds("down_cferr1", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4cfErr2Up = CSVReader.eval_auto_bounds("up_cferr2", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_CF_ak4cfErr2Down = CSVReader.eval_auto_bounds("down_cferr2", BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    //for c-flavored jets only the cfErr uncertainty is applied
                    
                    if (mycsv_weight_CF_ak4 != 0) csv_weight_CF_ak4 *= mycsv_weight_CF_ak4;
                    if (mycsv_weight_CF_ak4jesUp != 0) csv_weight_CF_ak4jesUp *= mycsv_weight_CF_ak4jesUp;
                    if (mycsv_weight_CF_ak4jesDown != 0) csv_weight_CF_ak4jesDown *= mycsv_weight_CF_ak4jesDown;
                    /*
                    if (mycsv_weight_CF_ak4jesEC2_2016Up != 0) csv_weight_CF_ak4jesEC2_2016Up *= mycsv_weight_CF_ak4jesEC2_2016Up;
                    if (mycsv_weight_CF_ak4jesEC2_2016Down != 0) csv_weight_CF_ak4jesEC2_2016Down *= mycsv_weight_CF_ak4jesEC2_2016Down;
                    if (mycsv_weight_CF_ak4jesEC2Up != 0) csv_weight_CF_ak4jesEC2Up *= mycsv_weight_CF_ak4jesEC2Up;
                    if (mycsv_weight_CF_ak4jesEC2Down != 0) csv_weight_CF_ak4jesEC2Down *= mycsv_weight_CF_ak4jesEC2Down;
                    if (mycsv_weight_CF_ak4jesBBEC1Up != 0) csv_weight_CF_ak4jesBBEC1Up *= mycsv_weight_CF_ak4jesBBEC1Up;
                    if (mycsv_weight_CF_ak4jesBBEC1Down != 0) csv_weight_CF_ak4jesBBEC1Down *= mycsv_weight_CF_ak4jesBBEC1Down;
                    if (mycsv_weight_CF_ak4jesAbsoluteUp != 0) csv_weight_CF_ak4jesAbsoluteUp *= mycsv_weight_CF_ak4jesAbsoluteUp;
                    if (mycsv_weight_CF_ak4jesAbsoluteDown != 0) csv_weight_CF_ak4jesAbsoluteDown *= mycsv_weight_CF_ak4jesAbsoluteDown;
                    if (mycsv_weight_CF_ak4jesAbsolute_2016Up != 0) csv_weight_CF_ak4jesAbsolute_2016Up *= mycsv_weight_CF_ak4jesAbsolute_2016Up;
                    if (mycsv_weight_CF_ak4jesAbsolute_2016Down != 0) csv_weight_CF_ak4jesAbsolute_2016Down *= mycsv_weight_CF_ak4jesAbsolute_2016Down;
                    if (mycsv_weight_CF_ak4jesHFUp != 0) csv_weight_CF_ak4jesHFUp *= mycsv_weight_CF_ak4jesHFUp;
                    if (mycsv_weight_CF_ak4jesHFDown != 0) csv_weight_CF_ak4jesHFDown *= mycsv_weight_CF_ak4jesHFDown;
                    if (mycsv_weight_CF_ak4jesFlavorQCDUp != 0) csv_weight_CF_ak4jesFlavorQCDUp *= mycsv_weight_CF_ak4jesFlavorQCDUp;
                    if (mycsv_weight_CF_ak4jesFlavorQCDDown != 0) csv_weight_CF_ak4jesFlavorQCDDown *= mycsv_weight_CF_ak4jesFlavorQCDDown;
                    if (mycsv_weight_CF_ak4jesBBEC1_2016Up != 0) csv_weight_CF_ak4jesBBEC1_2016Up *= mycsv_weight_CF_ak4jesBBEC1_2016Up;
                    if (mycsv_weight_CF_ak4jesBBEC1_2016Down != 0) csv_weight_CF_ak4jesBBEC1_2016Down *= mycsv_weight_CF_ak4jesBBEC1_2016Down;
                    if (mycsv_weight_CF_ak4jesRelativeBalUp != 0) csv_weight_CF_ak4jesRelativeBalUp *= mycsv_weight_CF_ak4jesRelativeBalUp;
                    if (mycsv_weight_CF_ak4jesRelativeBalDown != 0) csv_weight_CF_ak4jesRelativeBalDown *= mycsv_weight_CF_ak4jesRelativeBalDown;
                    if (mycsv_weight_CF_ak4jesHF_2016Up != 0) csv_weight_CF_ak4jesHF_2016Up *= mycsv_weight_CF_ak4jesHF_2016Up;
                    if (mycsv_weight_CF_ak4jesHF_2016Down != 0) csv_weight_CF_ak4jesHF_2016Down *= mycsv_weight_CF_ak4jesHF_2016Down;
                    if (mycsv_weight_CF_ak4jesRelativeSample_2016Up != 0) csv_weight_CF_ak4jesRelativeSample_2016Up *= mycsv_weight_CF_ak4jesRelativeSample_2016Up;
                    if (mycsv_weight_CF_ak4jesRelativeSample_2016Down != 0) csv_weight_CF_ak4jesRelativeSample_2016Down *= mycsv_weight_CF_ak4jesRelativeSample_2016Down;
                    */
                    if (mycsv_weight_CF_ak4cfErr1Up != 0) csv_weight_CF_ak4cfErr1Up *= mycsv_weight_CF_ak4cfErr1Up;
                    if (mycsv_weight_CF_ak4cfErr1Down != 0) csv_weight_CF_ak4cfErr1Down *= mycsv_weight_CF_ak4cfErr1Down;
                    if (mycsv_weight_CF_ak4cfErr2Up != 0) csv_weight_CF_ak4cfErr2Up *= mycsv_weight_CF_ak4cfErr2Up;
                    if (mycsv_weight_CF_ak4cfErr2Down != 0) csv_weight_CF_ak4cfErr2Down *= mycsv_weight_CF_ak4cfErr2Down;
                
                }
                
                else  { //light flavor
                
                    double mycsv_weight_LF_ak4 = CSVReader.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesUp = CSVReader.eval_auto_bounds("up_jes", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesDown = CSVReader.eval_auto_bounds("down_jes", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    /*
                    double mycsv_weight_LF_ak4jesEC2_2016Up = CSVReader.eval_auto_bounds("up_jesEC2_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesEC2_2016Down = CSVReader.eval_auto_bounds("down_jesEC2_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesEC2Up = CSVReader.eval_auto_bounds("up_jesEC2", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesEC2Down = CSVReader.eval_auto_bounds("down_jesEC2", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesBBEC1Up = CSVReader.eval_auto_bounds("up_jesBBEC1", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesBBEC1Down = CSVReader.eval_auto_bounds("down_jesBBEC1", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesAbsoluteUp = CSVReader.eval_auto_bounds("up_jesAbsolute", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesAbsoluteDown = CSVReader.eval_auto_bounds("down_jesAbsolute", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesAbsolute_2016Up = CSVReader.eval_auto_bounds("up_jesAbsolute_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesAbsolute_2016Down = CSVReader.eval_auto_bounds("down_jesAbsolute_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesHFUp = CSVReader.eval_auto_bounds("up_jesHF", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesHFDown = CSVReader.eval_auto_bounds("down_jesHF", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesFlavorQCDUp = CSVReader.eval_auto_bounds("up_jesFlavorQCD", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesFlavorQCDDown = CSVReader.eval_auto_bounds("down_jesFlavorQCD", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesBBEC1_2016Up = CSVReader.eval_auto_bounds("up_jesBBEC1_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesBBEC1_2016Down = CSVReader.eval_auto_bounds("down_jesBBEC1_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesRelativeBalUp = CSVReader.eval_auto_bounds("up_jesRelativeBal", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesRelativeBalDown = CSVReader.eval_auto_bounds("down_jesRelativeBal", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesHF_2016Up = CSVReader.eval_auto_bounds("up_jesHF_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesHF_2016Down = CSVReader.eval_auto_bounds("down_jesHF_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesRelativeSample_2016Up = CSVReader.eval_auto_bounds("up_jesRelativeSample_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4jesRelativeSample_2016Down = CSVReader.eval_auto_bounds("down_jesRelativeSample_2016", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    */
                    double mycsv_weight_LF_ak4HFUp = CSVReader.eval_auto_bounds("up_hf", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4HFDown = CSVReader.eval_auto_bounds("down_hf", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    //no uncertainty on contamination from LF sample when computing LF scale factors
					double mycsv_weight_LF_ak4lfstats1Up = CSVReader.eval_auto_bounds("up_lfstats1", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4lfstats1Down = CSVReader.eval_auto_bounds("down_lfstats1", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4lfstats2Up = CSVReader.eval_auto_bounds("up_lfstats2", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                    double mycsv_weight_LF_ak4lfstats2Down = CSVReader.eval_auto_bounds("down_lfstats2", BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
					//no uncertainty on statistics of HF sample when computing LF scale factors
                    //no cfErr is computed for light-flavored jets
                    
                    
                    if (mycsv_weight_LF_ak4 != 0) csv_weight_LF_ak4 *= mycsv_weight_LF_ak4;
                    if (mycsv_weight_LF_ak4jesUp != 0) csv_weight_LF_ak4jesUp *= mycsv_weight_LF_ak4jesUp;
                    if (mycsv_weight_LF_ak4jesDown != 0) csv_weight_LF_ak4jesDown *= mycsv_weight_LF_ak4jesDown;
                    /*
                    if (mycsv_weight_LF_ak4jesEC2_2016Up != 0) csv_weight_LF_ak4jesEC2_2016Up *= mycsv_weight_LF_ak4jesEC2_2016Up;
                    if (mycsv_weight_LF_ak4jesEC2_2016Down != 0) csv_weight_LF_ak4jesEC2_2016Down *= mycsv_weight_LF_ak4jesEC2_2016Down;
                    if (mycsv_weight_LF_ak4jesEC2Up != 0) csv_weight_LF_ak4jesEC2Up *= mycsv_weight_LF_ak4jesEC2Up;
                    if (mycsv_weight_LF_ak4jesEC2Down != 0) csv_weight_LF_ak4jesEC2Down *= mycsv_weight_LF_ak4jesEC2Down;
                    if (mycsv_weight_LF_ak4jesBBEC1Up != 0) csv_weight_LF_ak4jesBBEC1Up *= mycsv_weight_LF_ak4jesBBEC1Up;
                    if (mycsv_weight_LF_ak4jesBBEC1Down != 0) csv_weight_LF_ak4jesBBEC1Down *= mycsv_weight_LF_ak4jesBBEC1Down;
                    if (mycsv_weight_LF_ak4jesAbsoluteUp != 0) csv_weight_LF_ak4jesAbsoluteUp *= mycsv_weight_LF_ak4jesAbsoluteUp;
                    if (mycsv_weight_LF_ak4jesAbsoluteDown != 0) csv_weight_LF_ak4jesAbsoluteDown *= mycsv_weight_LF_ak4jesAbsoluteDown;
                    if (mycsv_weight_LF_ak4jesAbsolute_2016Up != 0) csv_weight_LF_ak4jesAbsolute_2016Up *= mycsv_weight_LF_ak4jesAbsolute_2016Up;
                    if (mycsv_weight_LF_ak4jesAbsolute_2016Down != 0) csv_weight_LF_ak4jesAbsolute_2016Down *= mycsv_weight_LF_ak4jesAbsolute_2016Down;
                    if (mycsv_weight_LF_ak4jesHFUp != 0) csv_weight_LF_ak4jesHFUp *= mycsv_weight_LF_ak4jesHFUp;
                    if (mycsv_weight_LF_ak4jesHFDown != 0) csv_weight_LF_ak4jesHFDown *= mycsv_weight_LF_ak4jesHFDown;
                    if (mycsv_weight_LF_ak4jesFlavorQCDUp != 0) csv_weight_LF_ak4jesFlavorQCDUp *= mycsv_weight_LF_ak4jesFlavorQCDUp;
                    if (mycsv_weight_LF_ak4jesFlavorQCDDown != 0) csv_weight_LF_ak4jesFlavorQCDDown *= mycsv_weight_LF_ak4jesFlavorQCDDown;
                    if (mycsv_weight_LF_ak4jesBBEC1_2016Up != 0) csv_weight_LF_ak4jesBBEC1_2016Up *= mycsv_weight_LF_ak4jesBBEC1_2016Up;
                    if (mycsv_weight_LF_ak4jesBBEC1_2016Down != 0) csv_weight_LF_ak4jesBBEC1_2016Down *= mycsv_weight_LF_ak4jesBBEC1_2016Down;
                    if (mycsv_weight_LF_ak4jesRelativeBalUp != 0) csv_weight_LF_ak4jesRelativeBalUp *= mycsv_weight_LF_ak4jesRelativeBalUp;
                    if (mycsv_weight_LF_ak4jesRelativeBalDown != 0) csv_weight_LF_ak4jesRelativeBalDown *= mycsv_weight_LF_ak4jesRelativeBalDown;
                    if (mycsv_weight_LF_ak4jesHF_2016Up != 0) csv_weight_LF_ak4jesHF_2016Up *= mycsv_weight_LF_ak4jesHF_2016Up;
                    if (mycsv_weight_LF_ak4jesHF_2016Down != 0) csv_weight_LF_ak4jesHF_2016Down *= mycsv_weight_LF_ak4jesHF_2016Down;
                    if (mycsv_weight_LF_ak4jesRelativeSample_2016Up != 0) csv_weight_LF_ak4jesRelativeSample_2016Up *= mycsv_weight_LF_ak4jesRelativeSample_2016Up;
                    if (mycsv_weight_LF_ak4jesRelativeSample_2016Down != 0) csv_weight_LF_ak4jesRelativeSample_2016Down *= mycsv_weight_LF_ak4jesRelativeSample_2016Down;
                    */
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
            csv_weight_total_ak4jesUp = csv_weight_BF_ak4jesUp * csv_weight_CF_ak4jesUp * csv_weight_LF_ak4jesUp;
            csv_weight_total_ak4jesDown = csv_weight_BF_ak4jesDown * csv_weight_CF_ak4jesDown * csv_weight_LF_ak4jesDown;
            /*
            csv_weight_total_ak4jesEC2_2016Up = csv_weight_BF_ak4jesEC2_2016Up * csv_weight_CF_ak4jesEC2_2016Up * csv_weight_LF_ak4jesEC2_2016Up;
            csv_weight_total_ak4jesEC2_2016Down = csv_weight_BF_ak4jesEC2_2016Down * csv_weight_CF_ak4jesEC2_2016Down * csv_weight_LF_ak4jesEC2_2016Down;
            csv_weight_total_ak4jesEC2Up = csv_weight_BF_ak4jesEC2Up * csv_weight_CF_ak4jesEC2Up * csv_weight_LF_ak4jesEC2Up;
            csv_weight_total_ak4jesEC2Down = csv_weight_BF_ak4jesEC2Down * csv_weight_CF_ak4jesEC2Down * csv_weight_LF_ak4jesEC2Down;
            csv_weight_total_ak4jesBBEC1Up = csv_weight_BF_ak4jesBBEC1Up * csv_weight_CF_ak4jesBBEC1Up * csv_weight_LF_ak4jesBBEC1Up;
            csv_weight_total_ak4jesBBEC1Down = csv_weight_BF_ak4jesBBEC1Down * csv_weight_CF_ak4jesBBEC1Down * csv_weight_LF_ak4jesBBEC1Down;
            csv_weight_total_ak4jesAbsoluteUp = csv_weight_BF_ak4jesAbsoluteUp * csv_weight_CF_ak4jesAbsoluteUp * csv_weight_LF_ak4jesAbsoluteUp;
            csv_weight_total_ak4jesAbsoluteDown = csv_weight_BF_ak4jesAbsoluteDown * csv_weight_CF_ak4jesAbsoluteDown * csv_weight_LF_ak4jesAbsoluteDown;
            csv_weight_total_ak4jesAbsolute_2016Up = csv_weight_BF_ak4jesAbsolute_2016Up * csv_weight_CF_ak4jesAbsolute_2016Up * csv_weight_LF_ak4jesAbsolute_2016Up;
            csv_weight_total_ak4jesAbsolute_2016Down = csv_weight_BF_ak4jesAbsolute_2016Down * csv_weight_CF_ak4jesAbsolute_2016Down * csv_weight_LF_ak4jesAbsolute_2016Down;
            csv_weight_total_ak4jesHFUp = csv_weight_BF_ak4jesHFUp * csv_weight_CF_ak4jesHFUp * csv_weight_LF_ak4jesHFUp;
            csv_weight_total_ak4jesHFDown = csv_weight_BF_ak4jesHFDown * csv_weight_CF_ak4jesHFDown * csv_weight_LF_ak4jesHFDown;
            csv_weight_total_ak4jesFlavorQCDUp = csv_weight_BF_ak4jesFlavorQCDUp * csv_weight_CF_ak4jesFlavorQCDUp * csv_weight_LF_ak4jesFlavorQCDUp;
            csv_weight_total_ak4jesFlavorQCDDown = csv_weight_BF_ak4jesFlavorQCDDown * csv_weight_CF_ak4jesFlavorQCDDown * csv_weight_LF_ak4jesFlavorQCDDown;
            csv_weight_total_ak4jesBBEC1_2016Up = csv_weight_BF_ak4jesBBEC1_2016Up * csv_weight_CF_ak4jesBBEC1_2016Up * csv_weight_LF_ak4jesBBEC1_2016Up;
            csv_weight_total_ak4jesBBEC1_2016Down = csv_weight_BF_ak4jesBBEC1_2016Down * csv_weight_CF_ak4jesBBEC1_2016Down * csv_weight_LF_ak4jesBBEC1_2016Down;
            csv_weight_total_ak4jesRelativeBalUp = csv_weight_BF_ak4jesRelativeBalUp * csv_weight_CF_ak4jesRelativeBalUp * csv_weight_LF_ak4jesRelativeBalUp;
            csv_weight_total_ak4jesRelativeBalDown = csv_weight_BF_ak4jesRelativeBalDown * csv_weight_CF_ak4jesRelativeBalDown * csv_weight_LF_ak4jesRelativeBalDown;
            csv_weight_total_ak4jesHF_2016Up = csv_weight_BF_ak4jesHF_2016Up * csv_weight_CF_ak4jesHF_2016Up * csv_weight_LF_ak4jesHF_2016Up;
            csv_weight_total_ak4jesHF_2016Down = csv_weight_BF_ak4jesHF_2016Down * csv_weight_CF_ak4jesHF_2016Down * csv_weight_LF_ak4jesHF_2016Down;
            csv_weight_total_ak4jesRelativeSample_2016Up = csv_weight_BF_ak4jesRelativeSample_2016Up * csv_weight_CF_ak4jesRelativeSample_2016Up * csv_weight_LF_ak4jesRelativeSample_2016Up;
            csv_weight_total_ak4jesRelativeSample_2016Down = csv_weight_BF_ak4jesRelativeSample_2016Down * csv_weight_CF_ak4jesRelativeSample_2016Down * csv_weight_LF_ak4jesRelativeSample_2016Down;
            */
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
            output[1] = csv_weight_total_ak4jesUp;
            output[2] = csv_weight_total_ak4jesDown;
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
            
            /*
            output[0] = csv_weight_total_ak4;
            output[1] = csv_weight_total_ak4jesUp;
            output[2] = csv_weight_total_ak4jesDown;
            output[3] = csv_weight_total_ak4jesEC2_2016Up;
            output[4] = csv_weight_total_ak4jesEC2_2016Down;
            output[5] = csv_weight_total_ak4jesEC2Up;
            output[6] = csv_weight_total_ak4jesEC2Down;
            output[7] = csv_weight_total_ak4jesBBEC1Up;
            output[8] = csv_weight_total_ak4jesBBEC1Down;
            output[9] = csv_weight_total_ak4jesAbsoluteUp;
            output[10] = csv_weight_total_ak4jesAbsoluteDown;
            output[11] = csv_weight_total_ak4jesAbsolute_2016Up;
            output[12] = csv_weight_total_ak4jesAbsolute_2016Down;
            output[12] = csv_weight_total_ak4jesHFUp;
            output[14] = csv_weight_total_ak4jesHFDown;
            output[15] = csv_weight_total_ak4jesFlavorQCDUp;
            output[16] = csv_weight_total_ak4jesFlavorQCDDown;
            output[17] = csv_weight_total_ak4jesBBEC1_2016Up;
            output[18] = csv_weight_total_ak4jesBBEC1_2016Down;
            output[19] = csv_weight_total_ak4jesRelativeBalUp;
            output[20] = csv_weight_total_ak4jesRelativeBalDown;
            output[21] = csv_weight_total_ak4jesHF_2016Up;
            output[22] = csv_weight_total_ak4jesHF_2016Down;
            output[23] = csv_weight_total_ak4jesRelativeSample_2016Up;
            output[24] = csv_weight_total_ak4jesRelativeSample_2016Down;
            output[25] = csv_weight_total_ak4HFUp;
            output[26] = csv_weight_total_ak4HFDown;
            output[27] = csv_weight_total_ak4LFUp;
            output[28] = csv_weight_total_ak4LFDown;
            output[29] = csv_weight_total_ak4hfstats1Up;
            output[30] = csv_weight_total_ak4hfstats1Down;
            output[31] = csv_weight_total_ak4hfstats2Up;
            output[32] = csv_weight_total_ak4hfstats2Down;
            output[33] = csv_weight_total_ak4lfstats1Up;
            output[34] = csv_weight_total_ak4lfstats1Down;
            output[35] = csv_weight_total_ak4lfstats2Up;
            output[36] = csv_weight_total_ak4lfstats2Down;
            output[37] = csv_weight_total_ak4cfErr1Up;
            output[38] = csv_weight_total_ak4cfErr1Down;
            output[39] = csv_weight_total_ak4cfErr2Up;
            output[40] = csv_weight_total_ak4cfErr2Down;
            */
            return output;
            delete output;
            delete AK4Jets;
            delete AK4JetBtag;
            delete AK4JetFlavor;
} 
