
#include "correction.h"
#include <TMatrixDSymEigen.h>
#include <limits>
#include "../include/lester_mt2_bisect.h"

#include "../include/variablesFunctions.h"
#include "../src_cpp/lumiAndCrossSection.h"
#include "../../myLibrary/commenFunction.h"

void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Int_t> &array, std::vector<Int_t> &vec)
{
    vec.clear();
    for (UInt_t i = 0; i < array.GetSize(); i++)
    {
        vec.push_back(array.At(i));
    }
};
void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Double_t> &array, std::vector<Double_t> &vec)
{
    vec.clear();
    for (UInt_t i = 0; i < array.GetSize(); i++)
    {
        vec.push_back(array.At(i));
    }
};

Double_t deltaPhi(const Double_t phi1, const Double_t phi2)
{
    Double_t deltaPhi = TMath::Abs(phi1 - phi2);
    if (deltaPhi > TMath::Pi())
        deltaPhi = TMath::TwoPi() - deltaPhi;
    return deltaPhi;
}

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2)
{
    Double_t deltaPhi = TMath::Abs(phi1 - phi2);
    Double_t deltaEta = eta1 - eta2;
    if (deltaPhi > TMath::Pi())
        deltaPhi = TMath::TwoPi() - deltaPhi;
    return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}

Double_t deltRmin(const Double_t eta1, const Double_t phi1, const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &LeptonsMVAF)
{
    Double_t deltaR = 0;
    Double_t minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.GetSize(); lep++)
    {
        deltaR = DeltaR(LeptonsMVAF[lep].Eta(), eta1, LeptonsMVAF[lep].Phi(), phi1);
        if (deltaR < minDeltaR)
            minDeltaR = deltaR; // The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    return minDeltaR;
}

Double_t HTcalculator(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    /*{{{*/
    Double_t HTprov = 0;
    for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j)
    {
        HTprov =
            HTprov + SelectedJets[j].Pt(); //.Pt: the 3 vertor component, scalar
    }
    return HTprov;
} /*}}}*/

Double_t HTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    /*{{{*/
    Double_t HTprov = 0;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        HTprov =
            HTprov + SelectedJets[j].Pt(); //.Pt: the 3 vertor component, scalar
    }
    return HTprov;
} 
// Double_t MHTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
// {
//     /*{{{*/
//     ROOT::Math::PtEtaPhiMVector SumJets(0, 0, 0, 0);
//     Double_t MHTprov = 0;
//     for (UInt_t j = 0; j < SelectedJets.size(); ++j)
//     {
//         SumJets = SumJets + SelectedJets[j];
//     }
//     MHTprov = SumJets.Pt();
//     return MHTprov;
// }
Double_t energyCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    Double_t sumE = 0;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        sumE = sumE + SelectedJets[j].E();
    }
    return sumE;
}
Double_t pzCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    Double_t sumE = 0;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        sumE = sumE + SelectedJets[j].Pz();
    }
    return sumE;
}

/// it seems we cant not use std::vector as input parameter
// yes we can , just have to pass by address
Double_t MHTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    /*{{{*/
    ROOT::Math::PtEtaPhiMVector SumJets(0, 0, 0, 0);
    Double_t MHTprov = 0;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        SumJets = SumJets + SelectedJets[j];
    }
    MHTprov = SumJets.Pt();
    return MHTprov;
} /*}}}*/
Double_t rationHT_4toRestCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    std::vector<ROOT::Math::PtEtaPhiMVector> leading4;
    std::vector<ROOT::Math::PtEtaPhiMVector> rest;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        if (j < 4)
            leading4.push_back(SelectedJets[j]);
        if (j >= 4)
            rest.push_back(SelectedJets[j]);
    }
    if (SelectedJets.size() > 4)
    {
        return HTcalculator(leading4) / HTcalculator(rest);
    }
    else
        return -99;
}

Double_t InvariantMassCalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    ROOT::Math::PtEtaPhiMVector jet_sum{0, 0, 0, 0};
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        jet_sum = jet_sum + SelectedJets[j];
    }
    Double_t InMass = jet_sum.M();
    return InMass;
}

Double_t InvariantMass2SysCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &a,
                              const std::vector<ROOT::Math::PtEtaPhiMVector> &b)
{
    std::vector<ROOT::Math::PtEtaPhiMVector> vector_sum(a.begin(), a.end());
    vector_sum.insert(vector_sum.end(), b.begin(), b.end());
    /*    ROOT::Math::PtEtaPhiMVector jet_sum = {0,0,0,0};
        for (UInt_t j = 0; j < a.GetSize(); ++j){
            jet_sum = jet_sum + a[j];
        }
        ROOT::Math::PtEtaPhiMVector b_sum = {0,0,0,0};
        for (UInt_t k = 0; k < b.GetSize(); ++k){
            b_sum = b_sum + b[k];
        }*/
    Double_t invariantMass = InvariantMassCalculator(vector_sum);
    return invariantMass;
}


Double_t TransEnergyCal(const ROOT::Math::PtEtaPhiMVector &SelectedJets)
{
    //    TVector3 p =  SelectedJets.Vect();
    Double_t pt = SelectedJets.Pt();
    Double_t trans_energy = sqrt(SelectedJets.M() * SelectedJets.M() + pt * pt);
    return trans_energy;
}

Double_t TransEnergySysCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    Double_t transE = 0;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        transE += TransEnergyCal(SelectedJets[j]);
    }
    return transE;
}



// Function to calculate the transverse mass (mT) given a particle's Lorentz vector and MET
Double_t calculateTransverseMass(const ROOT::Math::PtEtaPhiMVector& particleVec, Double_t Met_pt, Double_t Met_phi) {
    // double pt = particleVec.Pt(); // Magnitude of the particle's transverse momentum
    // double met = metVec.Pt(); // Magnitude of the missing transverse energy (MET)
    
    // Calculate the azimuthal angle difference
    // double deltaPhi = std::fabs(particleVec.DeltaPhi(metVec));
    Double_t delta_phi = deltaPhi(particleVec.Phi(), Met_phi);
    
    // Calculate and return the transverse mass
    // return std::sqrt(2 * pt * met * (1 - std::cos(deltaPhi)));
    return std::sqrt(2 * particleVec.Pt() * Met_pt * (1 - std::cos(delta_phi)));
}

Double_t TransMassCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    Double_t MHT = MHTcalculator(SelectedJets);
    Double_t transE = 0;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        transE += TransEnergyCal(SelectedJets[j]);
    }
    Double_t trans_mass = sqrt(MHT * MHT + transE * transE);
    return trans_mass;
}

Double_t TransMassSysCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &Jets, const std::vector<ROOT::Math::PtEtaPhiMVector> &Leptons)
{
    Double_t transE1 = TransEnergySysCal(Jets);
    Double_t transE2 = TransEnergySysCal(Leptons);
    ROOT::Math::PtEtaPhiMVector SumJets(0, 0, 0, 0);
    ROOT::Math::PtEtaPhiMVector SumLeptons(0, 0, 0, 0);
    for (UInt_t j = 0; j < Jets.size(); ++j)
    {
        SumJets = SumJets + Jets[j];
    }
    for (UInt_t k = 0; k < Leptons.size(); ++k)
    {
        SumLeptons = SumLeptons + Leptons[k];
    }
    // TVector3 MHTsum = (SumJets + SumLeptons).Vect(); //???
    auto MHTsum = (SumJets + SumLeptons).Vect(); //???
    // Double_t transMass = std::sqrt((transE1 + transE2) * (transE1 + transE2) - MHTsum * MHTsum);
    Double_t transMass = std::sqrt((transE1 + transE2) * (transE1 + transE2) - MHTsum.Mag2());
    return transMass;
}

Double_t calculateTransverseMass(const ROOT::Math::PtEtaPhiMVector& vec1, const ROOT::Math::PtEtaPhiMVector& vec2) {
    // Calculate the magnitudes of the transverse momentum vectors
    Double_t pt1 = vec1.Pt();
    Double_t pt2 = vec2.Pt();
    
    // Calculate the squared masses
    Double_t m1_squared = vec1.M2(); // M2() returns the squared mass
    Double_t m2_squared = vec2.M2();
    
    // Calculate the sum of the magnitudes of the transverse momenta
    Double_t et1 = std::sqrt(m1_squared + pt1 * pt1);
    Double_t et2 = std::sqrt(m2_squared + pt2 * pt2);
    Double_t etSum = et1 + et2;
    
    // Calculate the transverse momentum of the system (vec1 + vec2)
    ROOT::Math::PtEtaPhiMVector systemVec = vec1 + vec2;
    Double_t ptSystem = systemVec.Pt();
    
    // Calculate the squared transverse mass
    Double_t mt_squared = etSum * etSum - ptSystem * ptSystem;

    return std::sqrt(mt_squared); // Return the transverse mass
}



Double_t MinDeltaRCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &Jets,
                      const std::vector<ROOT::Math::PtEtaPhiMVector> &Leptons)
{
    Double_t deltaR_init = 10;
    Double_t min_deltar = 10;
    Double_t min_deltaR = 10;
    for (UInt_t j = 0; j < Jets.size(); ++j)
    {
        for (UInt_t k = 0; k < Leptons.size(); ++k)
        {
            deltaR_init = DeltaR(Jets[j].Eta(), Leptons[k].Eta(), Jets[j].Phi(), Leptons[k].Phi());

            if (min_deltar > deltaR_init)
                min_deltar = deltaR_init;
        }
        if (min_deltar < min_deltaR)
            min_deltaR = min_deltar;
    }
    return min_deltaR;
}



Double_t MinDeltaRSingleCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &Jets)
{
    Double_t min = 10;
    // Double_t min_2 = 10;
    Double_t min_3 = 10;
    Double_t min_1 = 10;
    for (UInt_t j = 0; j < Jets.size(); ++j)
    {
        if (Jets.size() < 2)
        {
            min_3 = 0.;
            break;
        }
        for (UInt_t k = j + 1; k < Jets.size(); ++k)
        {
            // min_1 = Jets[j].DeltaR(Jets[k]);
            min_1 = DeltaR(Jets[j].Eta(), Jets[k].Eta(), Jets[j].Phi(), Jets[k].Phi());
            if (min_1 < min)
            {
                min = min_1;
            }
        }
        if (min < min_3)
        {
            min_3 = min;
        }
    }
    return min_3;
}

Double_t deltaR_Leading(const std::vector<ROOT::Math::PtEtaPhiMVector> &taus, const std::vector<ROOT::Math::PtEtaPhiMVector> &Jets)
{
    Double_t deltaR = 0;
    if(taus.size() > 0 && Jets.size() > 0)
    {
        deltaR = DeltaR(taus[0].Eta(), Jets[0].Eta(), taus[0].Phi(), Jets[0].Phi());
    }
    return deltaR;
}


Double_t AverageDeltaRCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets)
{
    Double_t eta_1;
    Double_t phi_1;
    Double_t eta_2;
    Double_t phi_2;
    Double_t sum_delta_R = 0.0;
    const Int_t num = SelectedJets.size();
    for (UInt_t j = 0; j < SelectedJets.size(); ++j)
    {
        eta_1 = SelectedJets[j].Eta();
        phi_1 = SelectedJets[j].Phi();
        for (UInt_t k = 0; k < SelectedJets.size(); ++k)
        {
            if (k != j)
            {
                eta_2 = SelectedJets[k].Eta();
                phi_2 = SelectedJets[k].Phi();
                sum_delta_R = sum_delta_R + DeltaR(eta_1, eta_2, phi_1, phi_2);
            }
        }
    }
    sum_delta_R = sum_delta_R / ((num - 1) * num);
    return sum_delta_R;
}
// Double_t bscoreSumOf4largestCal(const std::vector<Double_t> &SelectedJetsBTags)
Double_t bscoreSumOf4largestCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags)
{
    std::vector<Double_t> jetsBtags;
    copy_TTreeReaderArray_toVector(SelectedJetsBTags, jetsBtags);
    // TTTT::copyVecToVec(SelectedJetsBTags, jetsBtags);
    sort(jetsBtags.begin(), jetsBtags.end());
    reverse(jetsBtags.begin(), jetsBtags.end());
    Double_t sum = -99;
    if (SelectedJetsBTags.GetSize() > 3)
    {
        sum = jetsBtags[0] + jetsBtags[1] + jetsBtags[2] + jetsBtags[3];
    }
    else
    {
        sum = -99;
    }
    return sum;
}

Double_t bscoreMultiOf4largestCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags)
{
    std::vector<Double_t> jetsBtags;
    copy_TTreeReaderArray_toVector(SelectedJetsBTags, jetsBtags);
    // TTTT::copyVecToVec(SelectedJetsBTags, jetsBtags);
    sort(jetsBtags.begin(), jetsBtags.end());
    reverse(jetsBtags.begin(), jetsBtags.end());
    Double_t sum = 1;
    if (SelectedJetsBTags.GetSize() > 3)
    {
        // sum = jetsBtags[0]*jetsBtags[1]*jetsBtags[2]*jetsBtags[3];
        sum = TMath::Sqrt(jetsBtags[0] * jetsBtags[1] * jetsBtags[2] * jetsBtags[3]);
    }
    else
    {
        sum = 0;
    }
    return sum;
}

Double_t BScoreAllJetsCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags)
{
    Double_t initB = 0;
    for (UInt_t j = 0; j < SelectedJetsBTags.GetSize(); ++j)
    {
        initB = initB + SelectedJetsBTags[j];
    }
    return initB;
}

Double_t bScoreMultiCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags)
{
    Double_t initB = 1;
    for (UInt_t j = 0; j < SelectedJetsBTags.GetSize(); ++j)
    {
        initB = initB * SelectedJetsBTags[j];
    }
    if (SelectedJetsBTags.GetSize() < 1)
    {
        initB = 0;
    }
    else
    {
        initB = TMath::Sqrt(initB);
    }
    return initB;
}

// Int_t calGenTauNum(const TTreeReaderArray<Int_t> &tausT_genPartFlav)
Int_t calGenTauNum(const TTreeReaderArray<UChar_t> &tausT_genPartFlav)
{
    Int_t genNum = 0;
    for (UInt_t i = 0; i < tausT_genPartFlav.GetSize(); ++i)
    {
        Int_t itau = static_cast<int>(tausT_genPartFlav.At(i));
        // if (tausT_genPartFlav[i] == 5)
        if (itau == 5)
        // Flavour of genParticle for MC matching to status==2 taus: 1 = prompt electron, 2 = prompt muon, 3 = tau->e decay, 4 = tau->mu decay, 5 = hadronic tau decay, 0 = unknown or unmatched
        {
            genNum++;
        }
    }
    return genNum;
}

Int_t getTauProng(const TTreeReaderArray<Int_t> &tausT_decayMode)
{
    // DM = 5*(Nc-1)+Np,
    Int_t prongNum = 0;
    for (UInt_t i = 0; i < tausT_decayMode.GetSize(); ++i)
    {
        Int_t iProng = (tausT_decayMode[i] / 5) + 1;
        // std::cout << i << "tau Prong=" << iProng << "; "
        //   << "tauDecayMode=" << tausT_decayMode[i] << "  ";
        prongNum += iProng;
    }
    return prongNum;
}

Int_t chargeMulCalSingle(const TTreeReaderArray<Int_t> &Muon_charge_, const TTreeReaderArray<Int_t> &muonsT_index)
{
    Int_t chargeMul = 1;
    for (UInt_t i = 0; i < muonsT_index.GetSize(); ++i)
    {
        chargeMul = Muon_charge_.At(muonsT_index[i]) * chargeMul;
    }
    return chargeMul;
}

Int_t chargeMulCal(const TTreeReaderArray<Int_t> &tausT_charge, const TTreeReaderArray<Int_t> &Muon_charge_, const TTreeReaderArray<Int_t> &muonsT_index, const TTreeReaderArray<Int_t> &patElectron_charge_, const TTreeReaderArray<Int_t> &eleMVAT_index)
{
    Int_t muonsCharge = chargeMulCalSingle(Muon_charge_, muonsT_index);
    Int_t eleCharge = chargeMulCalSingle(patElectron_charge_, eleMVAT_index);
    Int_t charge = 1;
    for (UInt_t ch = 0; ch < tausT_charge.GetSize(); ch++)
    {
        charge = charge * tausT_charge[ch];
    }
    charge = charge * muonsCharge * eleCharge;
    return charge;
};

Int_t chargeMulCalNew(const TTreeReaderArray<Int_t>& taus_charge, const TTreeReaderArray<Int_t>& muons_charge, const TTreeReaderArray<Int_t> &eles_charge){
    Int_t charge = 1;
    if(taus_charge.GetSize() == 0 && muons_charge.GetSize() == 0 && eles_charge.GetSize() == 0){
        return -99;
    }
    for(UInt_t i = 0; i < taus_charge.GetSize(); i++){
        charge = taus_charge.At(i);
    }
    for(UInt_t j = 0; j < muons_charge.GetSize(); j++){
        charge = charge * muons_charge.At(j);
    }
    for(UInt_t k = 0; k < eles_charge.GetSize(); k++){
        charge = charge * eles_charge.At(k);
    }
    return charge;
};

Double_t calculateSphericity(const std::vector<ROOT::Math::PtEtaPhiMVector>& particles) {
    // Initialize the momentum tensor
    TMatrixDSym S_ij(3);
    Double_t pSum2 = 0.0;

    // Fill the momentum tensor
    for (const auto& p : particles) {
        Double_t px = p.Px();
        Double_t py = p.Py();
        Double_t pz = p.Pz();
        Double_t p2 = px*px + py*py + pz*pz;
        pSum2 += p2;

        S_ij(0,0) += px*px;
        S_ij(0,1) += px*py;
        S_ij(0,2) += px*pz;
        S_ij(1,0) += py*px;
        S_ij(1,1) += py*py;
        S_ij(1,2) += py*pz;
        S_ij(2,0) += pz*px;
        S_ij(2,1) += pz*py;
        S_ij(2,2) += pz*pz;
    }

    if (pSum2 > 0) {
        // Normalize the momentum tensor
        S_ij *= (1.0 / pSum2);

        // Find the eigenvalues of the normalized tensor
        TVectorD eigenValues(3);
        S_ij.EigenVectors(eigenValues);

        // Sphericity calculation
        Double_t sphericity = 1.5 * (eigenValues(1) + eigenValues(2)); // λ2 + λ3, since λ1 ≥ λ2 ≥ λ3 by convention
        return sphericity;
    }

    return 0.0; // Return 0 if there are no particles or all particles have no momentum
}


TVectorD calculateEigenvalues(const std::vector<ROOT::Math::PtEtaPhiMVector>& particles) {
    TMatrixDSym S_ij(3);
    Double_t pSum2 = 0.0;

    for (const auto& p : particles) {
        Double_t px = p.Px(), py = p.Py(), pz = p.Pz();
        pSum2 += px*px + py*py + pz*pz;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                S_ij(i, j) += (i == 0 ? px : (i == 1 ? py : pz)) * (j == 0 ? px : (j == 1 ? py : pz));
            }
        }
    }

    if (pSum2 > 0) {
        S_ij *= (1.0 / pSum2);
        TVectorD eigenValues(3);
        S_ij.EigenVectors(eigenValues);
        return eigenValues;
    }

    return TVectorD(3); // Return a vector filled with zeros if no particles or all particles have no momentum
}
Double_t calculateSphericityFromEigenvalues(const TVectorD& eigenValues) {
    // Assuming eigenValues are sorted, which they are by the EigenVectors method
    Double_t sphericity = 1.5 * (eigenValues(1) + eigenValues(2)); // λ2 + λ3
    return sphericity;
}

Double_t calculateAplanarityFromEigenvalues(const TVectorD& eigenValues) {
    Double_t aplanarity = 1.5 * eigenValues(2); // 3/2 * λ3
    return aplanarity;
}




/*
void SpheriltyAplanarityCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets, Double_t &Spher, Double_t &Apla)
{

  // AK8 jets
  TVector3 Bst;
  ROOT::Math::PtEtaPhiMVector momAK8J;
  UInt_t mynJets = SelectedJets.GetSize();
  float momAK8JB[mynJets][4]; // matrix?

  Double_t sume = energyCal(SelectedJets);
  Double_t sumpz = pzCal(SelectedJets);
  if (sume != 0.)
  { // sume = sum of jet energy
    Bst.SetZ(-sumpz / sume);
    for (UInt_t idx = 0; idx < mynJets; idx++)
    {
      // momAK8J.SetPx(ak8Jet[idx].Px());
      // momAK8J.SetPy(ak8Jet[idx].Py());
      // momAK8J.SetPz(ak8Jet[idx].Pz());
      // momAK8J.SetE(ak8Jet[idx].E());
      momAK8J = SelectedJets[idx];
      // now do the boost
      // momAK8J.Boost(Bst);
      momAK8J.BoostToCM(Bst);

      momAK8JB[idx][0] = momAK8J.Px();
      momAK8JB[idx][1] = momAK8J.Py();
      momAK8JB[idx][2] = momAK8J.Pz();
      momAK8JB[idx][3] = momAK8J.E();
    }
  }

  // AK4 jets
  //  ROOT::Math::PtEtaPhiMVector momAK4J;
  //  float  momAK4JB[myak4jet_nJets][4];
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

  TMatrixDSym momten2(3); // Instantation of TMatrixTSym<Double_t>
  momten2(0, 0) = 0;
  momten2(1, 1) = 0;
  momten2(2, 2) = 0;
  momten2(0, 1) = 0;
  momten2(0, 2) = 0;
  momten2(1, 2) = 0;

  Float_t sump2 = 0.;

  // AK8 jets
  for (UInt_t idx = 0; idx < mynJets; idx++)
  {
    momten2(0, 0) += momAK8JB[idx][0] * momAK8JB[idx][0];
    momten2(1, 1) += momAK8JB[idx][1] * momAK8JB[idx][1];
    momten2(2, 2) += momAK8JB[idx][2] * momAK8JB[idx][2];
    momten2(0, 1) += momAK8JB[idx][0] * momAK8JB[idx][1];
    momten2(0, 2) += momAK8JB[idx][0] * momAK8JB[idx][2];
    momten2(1, 2) += momAK8JB[idx][1] * momAK8JB[idx][2];

    sump2 += momAK8JB[idx][3] * momAK8JB[idx][3];
  }

  // AK4 jets
  //???why does it feel like double counting AK8 and AK4 JETS
  //  for(int idx = 0; idx < myak4jet_nJets; idx++){
  //  momten2(0,0) += momAK4JB[idx][0] * momAK4JB[idx][0];
  //  momten2(1,1) += momAK4JB[idx][1] * momAK4JB[idx][1];
  //  momten2(2,2) += momAK4JB[idx][2] * momAK4JB[idx][2];
  //  momten2(0,1) += momAK4JB[idx][0] * momAK4JB[idx][1];
  //  momten2(0,2) += momAK4JB[idx][0] * momAK4JB[idx][2];
  //  momten2(1,2) += momAK4JB[idx][1] * momAK4JB[idx][2];
  //
  // sump2 +=   momAK4JB[idx][3] * momAK4JB[idx][3];
  // }

  if (sump2 != 0)
  {
    momten2(0, 0) = momten2(0, 0) / sump2;
    momten2(1, 1) = momten2(1, 1) / sump2;
    momten2(2, 2) = momten2(2, 2) / sump2;
    momten2(0, 1) = momten2(0, 1) / sump2;
    momten2(0, 2) = momten2(0, 2) / sump2;
    momten2(1, 2) = momten2(1, 2) / sump2;
    momten2(1, 0) = momten2(0, 1);
    momten2(2, 0) = momten2(0, 2);
    momten2(2, 1) = momten2(1, 2);
  }
  else
  {
    momten2(0, 0) = 0;
    momten2(1, 1) = 0;
    momten2(2, 2) = 0;
    momten2(0, 1) = momten2(1, 0) = 0;
    momten2(0, 2) = momten2(2, 0) = 0;
    momten2(1, 2) = momten2(2, 1) = 0;
  }

  // find the eigenvalues

  TVectorD eigval(3);

  TMatrixDSymEigen eigen(momten2);
  eigval = eigen.GetEigenValues();

  Spher = 3. / 2. * (eigval(2) + eigval(1));
  Apla = 3. / 2. * eigval(2);
}
*/
// Double_t TopScoreAllTopsCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector>& SelectedTops) {
// Double_t init = 0;
// for (UInt_t j = 0; j < SelectedTops.GetSize(); ++j) {
// init = init + TopTagger_discriminator_->at(j);
// }
// return init;
// }

Double_t calMuonIDSF(const TTreeReaderArray<Double_t> &muons_pt, const TTreeReaderArray<Double_t> &muons_eta, const TH2D *MuonIDSF, const Int_t type, Bool_t isMuon, Bool_t isData)
{
    Double_t muonIDSF = 1.0;
    // std::cout<<"muonSize="<<muons_pt.GetSize()<<"\n";
    if (!isData)
    {
        for (UInt_t i = 0; i < muons_pt.GetSize(); i++)
        {
            Int_t binx;
            if (isMuon)
            {
                binx = MuonIDSF->GetXaxis()->FindBin(fabs(muons_eta.At(i))); // fabs for muons, no abs for electron
            }
            else
            {
                binx = MuonIDSF->GetXaxis()->FindBin((muons_eta.At(i))); // fabs for muons, no abs for electron
            }
            Int_t biny = MuonIDSF->GetYaxis()->FindBin(muons_pt.At(i));
            Double_t iMuonSF = MuonIDSF->GetBinContent(binx, biny);
            Double_t iMuonSF_up = iMuonSF + MuonIDSF->GetBinError(binx, biny);
            Double_t iMuonSF_down = iMuonSF - MuonIDSF->GetBinError(binx, biny);
            if (type == 0)
            {
                muonIDSF *= iMuonSF;
            }
            else if (type == 1)
            {
                muonIDSF *= iMuonSF_up;
            }
            else if (type == 2)
            {
                muonIDSF *= iMuonSF_down;
            }
        }
        if (muonIDSF == 0)
            muonIDSF = 1.0;
    }
    return muonIDSF;
}

Double_t calMuonIDSF_json(const TTreeReaderArray<Double_t>& muon_eta, const TTreeReaderArray<Double_t>& muon_pt, correction::CorrectionSet *csetLPt, correction::CorrectionSet *csetMPt, correction::CorrectionSet *csetHPt, Int_t sysMuon, Bool_t isData){
    Double_t sf = 1.0;
    if(isData){
        return sf;
    }else{
        auto corrLPtID = csetLPt->at("NUM_TightID_DEN_TrackerMuons");//!!!no Isof for low pt
        auto corrMPtID = csetMPt->at("NUM_TightPFIso_DEN_TightID"); //!!! for tight ID+tightIso
        auto corrHPtID = csetHPt->at("NUM_TightID_DEN_GlobalMuonProbes");//!!!no Isof for high pt
        for (UInt_t i = 0; i < muon_eta.GetSize(); i++)
        {
            Double_t ipt = muon_pt.At(i);
            // Double_t ieta = muon_eta.At(i);
            Double_t sfLID = 1.0;
            Double_t sfLID_syst = 1.0;
            Double_t sfLID_stat = 1.0;
            if (ipt<15){
                sfLID = corrLPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "nominal"});
                sfLID_syst = corrLPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "syst"});
                sfLID_stat = corrLPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "stat"});
            }else if(ipt<200){
                sfLID = corrMPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "nominal"});
                sfLID_syst = corrMPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "syst"});
                sfLID_stat = corrMPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "stat"});
            }else{
                sfLID = corrHPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "nominal"});
                sfLID_syst = corrHPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "syst"});
                sfLID_stat = corrHPtID->evaluate({std::abs(muon_eta.At(i)), muon_pt.At(i), "stat"});
            }

            switch (sysMuon)
            {
            case 1://up
                sfLID = sfLID +TMath::Sqrt(sfLID_syst*sfLID_syst+sfLID_stat*sfLID_stat);
                break;
            case 2://down
                sfLID = sfLID -TMath::Sqrt(sfLID_syst*sfLID_syst+sfLID_stat*sfLID_stat);
            default:
                break;
            }
            sf = sf*sfLID;
        }
    }
    return sf;
}

Double_t calTau_IDSF_new(const TTreeReaderArray<Double_t> &taus_pt, const TTreeReaderArray<Double_t> &taus_eta, const TTreeReaderArray<Int_t> &tausT_decayMode, const TTreeReaderArray<UChar_t> &tausT_genPartFlav, correction::CorrectionSet *cset, std::string syst_vsjet, std::string syst_vsmu, std::string syst_vsele, std::string VsJetWP, Bool_t isData, Bool_t isRun3)
{
    // read from official json file
    // syst='nom', 'up' or  'down'.
    //https://gitlab.cern.ch/cms-tau-pog/jsonpog-integration/-/tree/TauPOG_v2_deepTauV2p5/POG/TAU/2022_postEE?ref_type=heads
    Double_t sf = 1.0;
    if (!isData)
    {
        TString tauVsJet = "DeepTau2017v2p1VSjet";
        TString tauVsMu = "DeepTau2017v2p1VSmu";
        TString tauVsEle = "DeepTau2017v2p1VSe";
        if(isRun3){
            tauVsJet = "DeepTau2018v2p5VSjet";
            tauVsMu = "DeepTau2018v2p5VSmu";
            tauVsEle = "DeepTau2018v2p5VSe";
        }
        auto corr_vsjet = cset->at(tauVsJet.Data());
        auto corr_vsmu = cset->at(tauVsMu.Data());
        auto corr_vsele = cset->at(tauVsEle.Data());
        for (UInt_t i = 0; i < taus_pt.GetSize(); i++)
        {
            Double_t ipt = taus_pt.At(i);
            Int_t idecayMode = tausT_decayMode.At(i);
            Int_t igenMatch = tausT_genPartFlav.At(i);
            Double_t ieta = taus_eta.At(i);
            Double_t sf_vsJet = 1.0;
            Double_t sf_vsele = 1.0;
            Double_t sf_vsmu = 1.0;
            if(isRun3){
                // sf_vsJet = corr_vsjet->evaluate({ipt, idecayMode, igenMatch, "Medium", "VVLoose", syst_vsjet, "dm"}); //!why need WPVSEle?
                sf_vsJet = corr_vsjet->evaluate({ipt, idecayMode, igenMatch, VsJetWP, "VVLoose", syst_vsjet, "dm"}); //!why need WPVSEle?
                sf_vsele = corr_vsele->evaluate({ieta, idecayMode, igenMatch, "VVLoose", syst_vsele}); 
            }else{
                sf_vsJet = corr_vsjet->evaluate({ipt, idecayMode, igenMatch, "Medium", syst_vsjet, "pt"}); //???not sure if is should be 5 or the genmatch of the tau
                sf_vsele = corr_vsele->evaluate({ieta, igenMatch, "VVLoose", syst_vsele}); // no VVVLoose histogram in file, use VVLoose and add +3% uncertainty (recommended by TAU POG conveners)
            }
            sf_vsmu = corr_vsmu->evaluate({ieta, igenMatch, "VLoose", syst_vsmu});
            // std::cout<<"sf_vsJet="<<sf_vsJet<<" sf_vsMu="<<sf_vsmu<<" sf_vsEle="<<sf_vsele<<"\n";
            sf *= sf_vsJet;
            sf *= sf_vsmu;
            sf *= sf_vsele;
            // std::cout<<"genMatch="<<igenMatch<<" sf_vsJet="<<sf_vsJet<<" sf_vsMu="<<sf_vsmu<<" sf_vsEle="<<sf_vsele<<"\n";
        }
    }
    return sf;
}

Double_t calBtagShapeWeight(const TTreeReaderArray<Double_t> &jets_pt, const TTreeReaderArray<Double_t> &jets_eta, const TTreeReaderArray<Int_t> &jets_flavour, const TTreeReaderArray<Double_t> &jets_btag, correction::CorrectionSet *cset_btag, Bool_t isData, const std::string sys)
{
    // https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration#Using_b_tag_scale_factors_in_you
    // https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/btvExample.py
    /*
    "jes": Combined JES uncertainty.
    "jes<x>": Uncertainty due to JES source x.
    "lf": Contamination from udsg+c jets in HF region.
    "hf": Contamination from b+c jets in LF region.
    Linear and quadratic statistical fluctuations:
    "hfstats1" / "hfstats2": b jets.
    "lfstats1" / "lfstats2": udsg jets.
    "cferr1" / "cferr2": Uncertainty for charm jets. //???the only uncertainty to consider for charm jets???
    variations due to "jes", "lf", "hf", "hfstats1/2", and "lfstats1/2" are applied to both b and udsg jets. For c-flavored jets, only "cferr1/2" is applied.

*/
    // I guess for sys variation, for c jets uncertainty, other jets SF should be "central"
    Double_t sf = 1.0;
    if (!isData)
    {
        auto corr_deepJet = cset_btag->at("deepJet_shape");
        // std::cout << "sys=" << sys << "\n";
        for (UInt_t j = 0; j < jets_pt.GetSize(); j++)
        {
            Double_t ijetSF = 1.0;
            Double_t ijetPt = jets_pt.At(j);
            Double_t ijetEta = std::abs(jets_eta.At(j));
            Double_t ijetBtag = jets_btag.At(j);
            Int_t ijetFlav = jets_flavour.At(j);

            //for PT btag a few value of -3
            if(!(ijetBtag>0. && ijetBtag<1.)){
                std::cout<<"!!!Warning: btag value out of range: "<<ijetBtag<<"\n";
                return 1.0;
            }

            if (sys == "central")
            {
                ijetSF = corr_deepJet->evaluate({sys, jets_flavour.At(j), std::abs(jets_eta.At(j)), jets_pt.At(j), jets_btag.At(j)});
            }
            else if (sys.find("cferr") != std::string::npos)
            {
                if (ijetFlav == 4)
                {
                    ijetSF = corr_deepJet->evaluate({sys, ijetFlav, ijetEta, ijetPt, ijetBtag});
                }
                else
                {
                    ijetSF = corr_deepJet->evaluate({"central", ijetFlav, ijetEta, ijetPt, ijetBtag});
                }
            }
            else if (!(sys.find("cferr") != std::string::npos))
            {
                if (!(ijetFlav == 4))
                {
                    ijetSF = corr_deepJet->evaluate({sys, ijetFlav, ijetEta, ijetPt, ijetBtag});
                }
                else
                {
                    ijetSF = corr_deepJet->evaluate({"central", ijetFlav, ijetEta, ijetPt, ijetBtag});
                }
            }
            // {
            //     if (jets_flavour.At(j) == 4)
            //     {
            //         //???is this way of accessing correct?
            //         // c jet
            //         if (sys.find("cferr1") != std::string::npos || sys.find("cferr2") != std::string::npos)
            //         {
            //             ijetSF = corr_deepJet->evaluate({sys, jets_flavour.At(j), std::abs(jets_eta.At(j)), jets_pt.At(j), jets_btag.At(j)});
            //         }
            //     }
            //     else
            //     {
            //         // b and light jets
            //         if (!(sys.find("cferr1") != std::string::npos || sys.find("cferr2") != std::string::npos))
            //         {
            //             ijetSF = corr_deepJet->evaluate({sys, jets_flavour.At(j), std::abs(jets_eta.At(j)), jets_pt.At(j), jets_btag.At(j)});
            //         }
            //     }
            // }
            // std::cout << "ijetSF=" << ijetSF << "n";
            // sf *= ijetSF;
            if (ijetSF > 0)
            {
                sf = sf * ijetSF;
            }
            // std::cout << "sf=" << sf << "\n";
        }
    }
    // std::cout << "btagSF = " << sf << "sys="<<sys<<"\n";
    // std::cout << "\n";
    return sf;
}

Double_t calBtagWPMWeight(const TTreeReaderArray<Double_t> &jets_pt, const TTreeReaderArray<Double_t> &jets_eta, const TTreeReaderArray<Int_t> &jets_flavour, const TTreeReaderArray<Double_t> &jets_btag, correction::CorrectionSet *cset_btag, TH2D *btagEff_b, TH2D *btagEff_c, TH2D *btagEff_l, TH2D *btagTEff_b, TH2D *btagTEff_c, TH2D *btagTEff_l, Bool_t isData, TString era, const std::string sys, const Bool_t isRun3, const Bool_t ifBTagT)
{ // https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation
    // https://twiki.cern.ch/twiki/bin/view/CMS/TopSystematics#b_tagging
    Double_t sf = 1.0;
    if(isData){
        return 1.0;
    }
    std::string btagWPTag = isRun3 ? "robustParticleTransformer_comb" : "deepJet_comb";
    std::string btagWPLTag = isRun3 ? "robustParticleTransformer_light" : "deepJet_incl";
    auto corr_deepJet = cset_btag->at(btagWPTag);       // b and c jet
    auto corr_deepJet_light = cset_btag->at(btagWPLTag);       // b and c jet
    Double_t p_mc = 1.0;
    Double_t p_data = 1.0;
    Double_t btagMWP = isRun3 ? TTTT::particleNetBMT.at(era).at(0) : TTTT::DeepJetM.at(era);
    Double_t btagTWP = isRun3 ? TTTT::particleNetBMT.at(era).at(1) : TTTT::DeepJetT.at(era);
    for (UInt_t j = 0; j < jets_pt.GetSize(); j++)
    {
        Double_t ijetSF = 1.0;
        Double_t ijetSFT = 1.0;
        Double_t ijetFlav = jets_flavour.At(j);
        Double_t ijetEta = std::abs(jets_eta.At(j));
        Double_t ijetPt = jets_pt.At(j);
        Double_t ijetBtag = jets_btag.At(j);

        if(ijetBtag<0. || ijetBtag>1.){
            std::cout<<"!!!Warning: btag value out of range: "<<ijetBtag<<"\n";
            return 1.0;
        }

        if (ijetFlav == 4 || ijetFlav == 5)
        {
            // b and c
            ijetSF = corr_deepJet->evaluate({sys, "M", jets_flavour.At(j), std::abs(jets_eta.At(j)), jets_pt.At(j)});
            ijetSFT = corr_deepJet->evaluate({sys, "T", jets_flavour.At(j), std::abs(jets_eta.At(j)), jets_pt.At(j)});
        }
        else
        {
            ijetSF = corr_deepJet_light->evaluate({sys, "M", jets_flavour.At(j), std::abs(jets_eta.At(j)), jets_pt.At(j)});
            ijetSFT = corr_deepJet_light->evaluate({sys, "T", jets_flavour.At(j), std::abs(jets_eta.At(j)), jets_pt.At(j)});
        }

        Bool_t ifBtagged = kFALSE;
        Bool_t ifBtaggedT = kFALSE;
        if (ijetBtag>btagMWP){
            ifBtagged = kTRUE;
        }
        if (ijetBtag>btagTWP){
            ifBtaggedT = kTRUE;
        }

        Double_t btagEff = getBtagEff(btagEff_b, btagEff_c, btagEff_l, ijetPt, ijetEta, ijetFlav, 0);
        Double_t btagEffT = getBtagEff(btagTEff_b, btagTEff_c, btagTEff_l, ijetPt, ijetEta, ijetFlav, 0);
        if(!ifBTagT){
            if (ifBtagged)
            {
                p_mc = p_mc * btagEff;
                p_data = p_data * ijetSF * btagEff;
            }
            else
            {
                p_mc = p_mc * (1. - btagEff);
                p_data = p_data * (1. - ijetSF * btagEff);
            }
        }else{
            if(ifBtaggedT){
                p_mc = p_mc * btagEffT;
                p_data = p_data * ijetSF * btagEffT;
            }
            else if (ifBtagged)
            {
                p_mc = p_mc * (btagEff - btagEffT);
                p_data = p_data * (ijetSF * btagEff - ijetSFT * btagEffT);
            }else{
                p_mc = p_mc * (1. - btagEff);
                p_data = p_data * (1. - ijetSF * btagEff);
            }
        }
        // if(std::abs(p_mc)<1e-6){
        //     std::cout<<"jetFlav="<<ijetFlav<<" jetPt="<<ijetPt<<" jetEta="<<ijetEta<<" jetBtag="<<ijetBtag<<" btagEff="<<btagEff<<" btagEffT="<<btagEffT<<" ijetSF="<<ijetSF<<" ijetSFT="<<ijetSFT<<" p_mc="<<p_mc<<" p_data="<<p_data<<"\n";
        // }

    }
    sf = std::abs(p_mc)<1e-8? 1: (p_data / p_mc);
    // sf = (p_data / p_mc);
    // if(std::isinf(sf)){
    //     std::cout<<"p_mc"<<p_mc<<" p_data"<<p_data<<"\n";
    // }
    return sf;
}

Double_t getBtagEff(TH2D *btagEff_b, TH2D *btagEff_c, TH2D *btagEff_l, Double_t jetPt, Double_t jetEta, Int_t jetFlavor, Int_t sys)
{
    Double_t btagEff = 1.0;
    switch (jetFlavor)
    {
    case 4: // c
        btagEff = TTTT::get2DSF(jetPt, jetEta, btagEff_c, 0);
        break;
    case 5: // b
        btagEff = TTTT::get2DSF(jetPt, jetEta, btagEff_b, 0);
        break;
    default: // l
        btagEff = TTTT::get2DSF(jetPt, jetEta, btagEff_l, 0);
        break;
    }
    return btagEff;
}

Double_t calBtagR(Int_t jets_number, TH1D *btagRHist)
{
    Double_t r = 1.0;
    if (jets_number >= btagRHist->GetXaxis()->GetXmin() && jets_number <= btagRHist->GetXaxis()->GetXmax())
    {
        Int_t binx = btagRHist->GetXaxis()->FindBin(jets_number);
        r = btagRHist->GetBinContent(binx);
    }
    return r;
}


Double_t HLTWeightCal(Double_t jets_HT, const Double_t jets_6pt, Int_t bjets_num, TH2D *triggerHist1b, TH2D *triggerHist2b, TH2D *triggerHist3b, Bool_t isdata, UInt_t sys)
{
    Double_t weight = 1.;
    //deal with events with <6 jets
    // if(jets_6pt<0){
    //     jets_6pt = 33.;
    // }
    if (!isdata)
    {
        // if (bjets_num == 1)
        if (bjets_num > 3)
        {
            weight = TTTT::get2DSF(jets_HT, jets_6pt, triggerHist1b, sys);
        }
        else if (bjets_num == 2)
        {
            weight = TTTT::get2DSF(jets_HT, jets_6pt, triggerHist2b, sys);
        }
        else if (bjets_num ==3)
        {
            weight = TTTT::get2DSF(jets_HT, jets_6pt, triggerHist3b, sys);
        }
    }
    return weight;
}

void getLorentzVec(const TTreeReaderArray<Double_t> &ptVec, const TTreeReaderArray<Double_t> &etaVec, const TTreeReaderArray<Double_t> &phiVec, const TTreeReaderArray<Double_t> &massVec, std::vector<ROOT::Math::PtEtaPhiMVector> &outLorVec)
{
    outLorVec.clear();
    for (UInt_t i = 0; i < ptVec.GetSize(); i++)
    {
        ROOT::Math::PtEtaPhiMVector iLorentz{ptVec.At(i), etaVec.At(i), phiVec.At(i), massVec.At(i)};
        outLorVec.push_back(iLorentz);
    }
}

// Function to sort a vector of ROOT::Math::PtEtaPhiMVector by pt
void sortByPt(std::vector<ROOT::Math::PtEtaPhiMVector>& vec) {
    std::sort(vec.begin(), vec.end(), [](const ROOT::Math::PtEtaPhiMVector& a, const ROOT::Math::PtEtaPhiMVector& b) {
        return a.Pt() < b.Pt();
    });
}

void addLorentzVector(const std::vector<ROOT::Math::PtEtaPhiMVector> &a, const std::vector<ROOT::Math::PtEtaPhiMVector> &b, std::vector<ROOT::Math::PtEtaPhiMVector> &out){
    out.clear();
    out.insert(out.end(), a.begin(), a.end());
    out.insert(out.end(), b.begin(), b.end());
    sortByPt(out);
}

Double_t calculateMT2(const ROOT::Math::PtEtaPhiMVector& visible1, const ROOT::Math::PtEtaPhiMVector& visible2, const Double_t MET_pt, const Double_t MET_phi) {
    Double_t MT2 = asymm_mt2_lester_bisect::get_mT2(
        visible1.M(), visible1.Px(), visible1.Py(),
        visible2.M(), visible2.Px(), visible2.Py(),
        MET_pt, MET_phi,
        0, 0,
        0
    );

    return MT2;
}

TString removeTrailingNumbers(const TString &str) {
    // Find the position of the first numeric character from the end
    int pos = str.Length() - 1;
    while (pos >= 0 && std::isdigit(str[pos])) {
        --pos;
    }

    // Return a new substring without the trailing numeric characters
    return str(0, pos + 1);
}
