Float_t evalEventSF_fixedWP( string syst, vector<TLorentzVector> * AK4Jets, vector<int> * AK4JetFlavor, vector<double> * AK4JetBtag, Double_t btagWP, BTagCalibrationReader CSVReader, TEfficiency * btagEff_b, TEfficiency * btagEff_c, TEfficiency * btagEff_udsg) {
    
    Double_t num = 1.0;
    Double_t den = 1.0;
    //loop over AK4 jets and compute scale factors depending on jet flavor, absolute value of jet eta, jet pt, jet CSV score
    if ( AK4Jets->size() > 0 ) { 
        
        for (int i = 0; i < AK4Jets->size(); i++) {
                
            if ( fabs(AK4JetFlavor->at(i)) == 5) { //b flavor
                    
                Int_t bin = btagEff_b->FindFixBin(fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt());
                Float_t eff = btagEff_b->GetEfficiency(bin); //get efficiency
                double weight_BF_ak4 = CSVReader.eval_auto_bounds(syst, BTagEntry::FLAV_B, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i)); //get SF
                if (eff != 0 && weight_BF_ak4 != 0) {

                    if (AK4JetBtag->at(i) > btagWP) { // if jet is b tagged

                        num *= eff;
                        den *= eff*weight_BF_ak4;

                    }
                    else {

                        num *= (1-eff);
                        den *= (1-eff*weight_BF_ak4);

                    }

                }
                    
            }
                
            else if ( fabs(AK4JetFlavor->at(i)) == 4) { //c flavor
                    
                Int_t bin = btagEff_b->FindFixBin(fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt());
                Float_t eff = btagEff_c->GetEfficiency(bin); //get efficiency
                double weight_CF_ak4 = CSVReader.eval_auto_bounds(syst, BTagEntry::FLAV_C, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                if (eff != 0 && weight_CF_ak4 != 0) {

                    if (AK4JetBtag->at(i) > btagWP) { // if jet is b tagged

                        num *= eff;
                        den *= eff*weight_CF_ak4;

                    }
                    else {

                        num *= (1-eff);
                        den *= (1-eff*weight_CF_ak4);

                    }

                }               
            }
                
            else  { //light flavor
                Int_t bin = btagEff_b->FindFixBin(fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt());
                Float_t eff = btagEff_udsg->GetEfficiency(bin); //get efficiency
                double weight_LF_ak4 = CSVReader.eval_auto_bounds(syst, BTagEntry::FLAV_UDSG, fabs(AK4Jets->at(i).Eta()), AK4Jets->at(i).Pt(), AK4JetBtag->at(i));
                if (eff != 0 && weight_LF_ak4 != 0) {

                    if (AK4JetBtag->at(i) > btagWP) { // if jet is b tagged

                        num *= eff;
                        den *= eff*weight_LF_ak4;

                    }
                    else {

                        num *= (1-eff);
                        den *= (1-eff*weight_LF_ak4);

                    }

                }
            }
        } // end loop over jets
    }//end at least 1 jet
    
    Double_t output = num/den;
    return output;
    delete AK4Jets;
    delete AK4JetBtag;
    delete AK4JetFlavor;
    delete btagEff_b;
    delete btagEff_c;
    delete btagEff_udsg;
    
} 
