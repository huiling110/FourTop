#include "variablesFunctions.h"

#include <TMatrixDSymEigen.h>

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2) {
  Double_t deltaPhi = TMath::Abs(phi1 - phi2);
  Double_t deltaEta = eta1 - eta2;
  if (deltaPhi > TMath::Pi())
    deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}

Double_t deltRmin(const Double_t eta1, const Double_t phi1, const TTreeReaderArray<TLorentzVector>& LeptonsMVAF){
    Double_t deltaR = 0;
    Double_t minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.GetSize(); lep++){
        deltaR =  DeltaR( LeptonsMVAF[lep].Eta(), eta1, LeptonsMVAF[lep].Phi(), phi1);
        if ( deltaR < minDeltaR ) minDeltaR = deltaR ;//The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    return minDeltaR; 
}

void copy_TTreeReaderArray_toVector( const TTreeReaderArray<double> &array, std::vector<Double_t> & vec){
    for( UInt_t i=0; i< array.GetSize(); i++){
        vec.push_back( array.At(i));
    }
}
Double_t HTcalculator( const TTreeReaderArray<TLorentzVector> &SelectedJets) {
    /*{{{*/
  Double_t HTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    HTprov =
        HTprov + SelectedJets[j].Pt(); //.Pt: the 3 vertor component, scalar
  }
  return HTprov;
} /*}}}*/

Double_t HTcalculator( const std::vector<TLorentzVector> &SelectedJets) {
    /*{{{*/
  Double_t HTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    HTprov =
        HTprov + SelectedJets[j].Pt(); //.Pt: the 3 vertor component, scalar
  }
  return HTprov;
} /*}}}*/
Double_t MHTcalculator(const std::vector<TLorentzVector> & SelectedJets) {
    /*{{{*/
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  Double_t MHTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    SumJets = SumJets + SelectedJets[j];
  }
  MHTprov = SumJets.Pt();
  return MHTprov;
} /*}}}*/
Double_t energyCal( const TTreeReaderArray<TLorentzVector> &SelectedJets ) {
    Double_t sumE = 0;
    for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
        sumE = sumE + SelectedJets[j].E();
    }
    return sumE;
}
Double_t pzCal( const TTreeReaderArray<TLorentzVector> &SelectedJets ) {
    Double_t sumE = 0;
    for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
        sumE = sumE + SelectedJets[j].Pz();
    }
    return sumE;
}


///it seems we cant not use TTreeReaderArray as input parameter
//yes we can , just have to pass by address
Double_t MHTcalculator(const TTreeReaderArray<TLorentzVector> &SelectedJets) {
    /*{{{*/
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  Double_t MHTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    SumJets = SumJets + SelectedJets[j];
  }
  MHTprov = SumJets.Pt();
  return MHTprov;
} /*}}}*/
Double_t rationHT_4toRestCal(const TTreeReaderArray<TLorentzVector>& SelectedJets){
    std::vector<TLorentzVector> leading4 ;
    std::vector<TLorentzVector> rest;
    for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
        if ( j < 4 ) leading4.push_back(SelectedJets[j]);
        if ( j >= 4) rest.push_back(SelectedJets[j]);
    }
    if ( SelectedJets.GetSize() > 4){
        return HTcalculator(leading4)/HTcalculator(rest);
    }
    else return -99;
}


// Double_t InvariantMassCalculator(std::vector<TLorentzVector> SelectedJets) {
Double_t InvariantMassCalculator(const TTreeReaderArray<TLorentzVector>&  SelectedJets) {
  TLorentzVector jet_sum = { 0, 0, 0, 0 };
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    jet_sum = jet_sum + SelectedJets[j];
  }
  Double_t InMass = jet_sum.M();
  return InMass;
}
Double_t InvariantMassCalculator(std::vector<TLorentzVector> SelectedJets) {
  TLorentzVector jet_sum = { 0, 0, 0, 0 };
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    jet_sum = jet_sum + SelectedJets[j];
  }
  Double_t InMass = jet_sum.M();
  return InMass;
}


Double_t InvariantMass2SysCal(const TTreeReaderArray<TLorentzVector>& a,
                            const TTreeReaderArray<TLorentzVector>& b) {
  std::vector<TLorentzVector> vector_sum(a.begin(), a.end());
  vector_sum.insert(vector_sum.end(), b.begin(), b.end());
  /*    TLorentzVector jet_sum = {0,0,0,0};
      for (UInt_t j = 0; j < a.GetSize(); ++j){
          jet_sum = jet_sum + a[j];
      }
      TLorentzVector b_sum = {0,0,0,0};
      for (UInt_t k = 0; k < b.GetSize(); ++k){
          b_sum = b_sum + b[k];
      }*/
  Double_t invariantMass = InvariantMassCalculator(vector_sum);
  return invariantMass;
}

// Int_t ChargeSum(const std::vector<Int_t> SelectedElectronsMVATIndex, Int_t type) {
  // Int_t charge_sum = 0;
  // for (UInt_t j = 0; j < SelectedElectronsMVATIndex.size(); ++j) {
    // if (type == 0)
      // charge_sum += patElectron_charge_->at(j);
      // charge_sum += patElectron_charge_->at(SelectedElectronsMVATIndex[j]);
    // if (type == 1)
      // charge_sum += Tau_charge_->at(SelectedElectronsMVATIndex[j]);
    // if (type == 2)
      // charge_sum += Muon_charge_->at(SelectedElectronsMVATIndex[j]);
  // }
  // return charge_sum;
// }

Double_t TransEnergyCal(const TLorentzVector SelectedJets) {
  //    TVector3 p =  SelectedJets.Vect();
  Double_t pt = SelectedJets.Pt();
  Double_t trans_energy = sqrt(SelectedJets.M() * SelectedJets.M() + pt * pt);
  return trans_energy;
}

Double_t TransEnergySysCal(const TTreeReaderArray<TLorentzVector>& SelectedJets) {
  Double_t transE = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  return transE;
}
Double_t TransEnergySysCal(const std::vector<TLorentzVector>& SelectedJets) {
  Double_t transE = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  return transE;
}

Double_t TransMassCal(const TTreeReaderArray<TLorentzVector>& SelectedJets) {
  Double_t MHT = MHTcalculator(SelectedJets);
  Double_t transE = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  Double_t trans_mass = sqrt(MHT * MHT + transE * transE);
  return trans_mass;
}

Double_t TransMassSysCal(const TTreeReaderArray<TLorentzVector>& Jets,   const TTreeReaderArray<TLorentzVector>& Leptons) {
  Double_t transE1 = TransEnergySysCal(Jets);
  Double_t transE2 = TransEnergySysCal(Leptons);
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  TLorentzVector SumLeptons;
  SumLeptons.SetPtEtaPhiE(0, 0, 0, 0);
  for (UInt_t j = 0; j < Jets.GetSize(); ++j) {
    SumJets = SumJets + Jets[j];
  }
  for (UInt_t k = 0; k < Leptons.GetSize(); ++k) {
    SumLeptons = SumLeptons + Leptons[k];
  }
  TVector3 MHTsum = (SumJets + SumLeptons).Vect();
  Double_t transMass =
      sqrt((transE1 + transE2) * (transE1 + transE2) - MHTsum * MHTsum);
  return transMass;
}

Double_t MinDeltaRCal(const TTreeReaderArray<TLorentzVector>& Jets,
                    const TTreeReaderArray<TLorentzVector>& Leptons) {
  Double_t deltaR_init = 10;
  Double_t min_deltar = 10;
  Double_t min_deltaR = 10;
  for (UInt_t j = 0; j < Jets.GetSize(); ++j) {
    for (UInt_t k = 0; k < Leptons.GetSize(); ++k) {
      deltaR_init = Jets[j].DeltaR(Leptons[k]);
      if (min_deltar > deltaR_init)
        min_deltar = deltaR_init;
    }
    if (min_deltar < min_deltaR)
      min_deltaR = min_deltar;
  }
  return min_deltaR;
}
Double_t MinDeltaRSingleCal(const TTreeReaderArray<TLorentzVector>& Jets) {
  Double_t min = 10;
  Double_t min_2 = 10;
  Double_t min_3 = 10;
  Double_t min_1 = 10;
  for (UInt_t j = 0; j < Jets.GetSize(); ++j) {
    for (UInt_t k = j + 1; k < Jets.GetSize(); ++k) {
      min_1 = Jets[j].DeltaR(Jets[k]);
      if (min_1 < min)
        min = min_1;
    }
    min_2 = min;
    if (min_2 < min_3)
      min_3 = min_2;
  }
  return min_3;
}

Double_t AverageDeltaRCal(const TTreeReaderArray<TLorentzVector>&  SelectedJets) {
  Double_t eta_1;
  Double_t phi_1;
  Double_t eta_2;
  Double_t phi_2;
  Double_t sum_delta_R = 0.0;
  const Int_t num = SelectedJets.GetSize();
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    eta_1 = SelectedJets[j].Eta();
    phi_1 = SelectedJets[j].Phi();
    for (UInt_t k = 0; k < SelectedJets.GetSize(); ++k) {
      if (k != j) {
        eta_2 = SelectedJets[k].Eta();
        phi_2 = SelectedJets[k].Phi();
        sum_delta_R = sum_delta_R + DeltaR(eta_1, eta_2, phi_1, phi_2);
      }
    }
  }
  sum_delta_R = sum_delta_R / ((num - 1) * num);
  return sum_delta_R;
}
Double_t bscoreSumOf4largestCal(const TTreeReaderArray<Double_t>& SelectedJetsBTags) {
    std::vector<Double_t> jetsBtags;
    copy_TTreeReaderArray_toVector( SelectedJetsBTags, jetsBtags );
    sort(jetsBtags.begin(),jetsBtags.end());
    reverse(jetsBtags.begin(),jetsBtags.end());
    Double_t sum = -99;
    if(SelectedJetsBTags.GetSize()>3) {
        sum = jetsBtags[0]+jetsBtags[1]+jetsBtags[2]+jetsBtags[3];
    }
    else{
        sum =  -99;
    }
    return sum;
}
Double_t BScoreAllJetsCal(const TTreeReaderArray<Double_t>& SelectedJetsBTags) {
  Double_t initB = 0;
  for (UInt_t j = 0; j < SelectedJetsBTags.GetSize(); ++j) {
    initB = initB + SelectedJetsBTags[j];
  }
  return initB;
}

Double_t bScoreMultiCal(const TTreeReaderArray<Double_t>& SelectedJetsBTags) {
  Double_t initB = 0;
  for (UInt_t j = 0; j < SelectedJetsBTags.GetSize(); ++j) {
    initB = initB*SelectedJetsBTags[j];
  }
  return initB;

}

void SpheriltyAplanarityCal( const TTreeReaderArray<TLorentzVector>&  SelectedJets, Double_t& Spher, Double_t& Apla ){
    
    //AK8 jets
    TVector3 Bst; 
    TLorentzVector momAK8J;
    UInt_t mynJets = SelectedJets.GetSize();
    float  momAK8JB[mynJets][4];//matrix?
   
    Double_t sume = energyCal( SelectedJets );
    Double_t sumpz = pzCal( SelectedJets );
    if(sume !=0.){ //sume = sum of jet energy
        Bst.SetZ(-sumpz/sume);
        for(UInt_t idx=0; idx < mynJets; idx++){
            // momAK8J.SetPx(ak8Jet[idx].Px());
            // momAK8J.SetPy(ak8Jet[idx].Py());
            // momAK8J.SetPz(ak8Jet[idx].Pz());
            // momAK8J.SetE(ak8Jet[idx].E());
            momAK8J = SelectedJets[idx];
            // now do the boost
            momAK8J.Boost(Bst); 

            momAK8JB[idx][0] = momAK8J.Px(); 
            momAK8JB[idx][1] = momAK8J.Py(); 
            momAK8JB[idx][2] = momAK8J.Pz(); 
            momAK8JB[idx][3] = momAK8J.E(); 
        }
    }
    
    //AK4 jets
    // TLorentzVector momAK4J;
    // float  momAK4JB[myak4jet_nJets][4];
//
    // if(sume !=0.){
        // for(int idx=0; idx < myak4jet_nJets; idx++){
            // momAK4J.SetPx(ak4Jet[idx].Px());
            // momAK4J.SetPy(ak4Jet[idx].Py());
            // momAK4J.SetPz(ak4Jet[idx].Pz());
            // momAK4J.SetE(ak4Jet[idx].E());
            // momAK4J.Boost(Bst);
//
            // momAK4JB[idx][0] = momAK4J.Px();
            // momAK4JB[idx][1] = momAK4J.Py();
            // momAK4JB[idx][2] = momAK4J.Pz();
            // momAK4JB[idx][3] = momAK4J.E();
        // }
    // }
    
    // prepare the momentum tensor

    TMatrixDSym momten2(3); //Instantation of TMatrixTSym<Double_t>     
    momten2(0,0)=0; 
    momten2(1,1)=0;  
    momten2(2,2)=0;  
    momten2(0,1)=0; 
    momten2(0,2)=0; 
    momten2(1,2)=0;  

    Float_t sump2=0.;
    
    //AK8 jets
    for(UInt_t idx = 0; idx < mynJets; idx++){
        momten2(0,0) += momAK8JB[idx][0] * momAK8JB[idx][0];
        momten2(1,1) += momAK8JB[idx][1] * momAK8JB[idx][1];
        momten2(2,2) += momAK8JB[idx][2] * momAK8JB[idx][2];
        momten2(0,1) += momAK8JB[idx][0] * momAK8JB[idx][1];
        momten2(0,2) += momAK8JB[idx][0] * momAK8JB[idx][2];
        momten2(1,2) += momAK8JB[idx][1] * momAK8JB[idx][2];
        
        sump2 +=   momAK8JB[idx][3] * momAK8JB[idx][3];
    }
    
    //AK4 jets
    //???why does it feel like double counting AK8 and AK4 JETS
    // for(int idx = 0; idx < myak4jet_nJets; idx++){
        // momten2(0,0) += momAK4JB[idx][0] * momAK4JB[idx][0];
        // momten2(1,1) += momAK4JB[idx][1] * momAK4JB[idx][1];
        // momten2(2,2) += momAK4JB[idx][2] * momAK4JB[idx][2];
        // momten2(0,1) += momAK4JB[idx][0] * momAK4JB[idx][1];
        // momten2(0,2) += momAK4JB[idx][0] * momAK4JB[idx][2];
        // momten2(1,2) += momAK4JB[idx][1] * momAK4JB[idx][2];
//
        // sump2 +=   momAK4JB[idx][3] * momAK4JB[idx][3];
    // }
    
    if( sump2 != 0) {
        momten2(0,0) = momten2(0,0)/sump2;
        momten2(1,1) = momten2(1,1)/sump2;
        momten2(2,2) = momten2(2,2)/sump2;
        momten2(0,1) = momten2(0,1)/sump2;
        momten2(0,2) = momten2(0,2)/sump2;
        momten2(1,2) = momten2(1,2)/sump2;
        momten2(1,0) = momten2(0,1);
        momten2(2,0) = momten2(0,2);
        momten2(2,1) = momten2(1,2);
    }
    else {
        momten2(0,0) = 0;
        momten2(1,1) = 0;
        momten2(2,2) = 0;
        momten2(0,1) = momten2(1,0) = 0;
        momten2(0,2) = momten2(2,0) = 0;
        momten2(1,2) = momten2(2,1) = 0;
    }
    
    // find the eigenvalues

    TVectorD eigval(3);
    
    TMatrixDSymEigen eigen(momten2);
    eigval  = eigen.GetEigenValues();
    
    Spher = 3./2.*(eigval(2)+eigval(1));
    Apla = 3./2.*eigval(2);
}





// Double_t TopScoreAllTopsCal(const TTreeReaderArray<TLorentzVector>& SelectedTops) {
  // Double_t init = 0;
  // for (UInt_t j = 0; j < SelectedTops.GetSize(); ++j) {
    // init = init + TopTagger_discriminator_->at(j);
  // }
  // return init;
// }
