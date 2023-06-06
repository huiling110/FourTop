#include "../include/jetSel.h"
#include <map>

JetSel::JetSel(TTree *outTree, const TString era, const Int_t jetType) : m_jetType{jetType}, m_era{era}
{ // m_type for different electrons
    // 1:loose;2:fakeble;3:tight
    std::cout << "Initializing JetSel: m_jetType=" << m_jetType << "......\n";

    TString jsonBase = "../../../jsonpog-integration/POG/";
    cset_jerSF = correction::CorrectionSet::from_file((jsonBase + json_map[era].at(0)).Data());
    std::cout << "JEC sf file: " << (jsonBase + json_map[era].at(0)).Data() << "\n";

    std::map<Int_t, TString> jetTypeMap = {
        {0, "jets"},
        {1, "jetsT"},
        {11, "bjetsL"},
        {12, "bjetsM"},
        {13, "bjetsT"},
        {2, "forward"},
    };

    ULong64_t seed = 37428479;
    m_random_generator = std::mt19937(seed); //

    outTree->Branch(jetTypeMap[m_jetType] + "_pt", &jets_pt);
    outTree->Branch(jetTypeMap[m_jetType] + "_eta", &jets_eta);
    outTree->Branch(jetTypeMap[m_jetType] + "_phi", &jets_phi);
    outTree->Branch(jetTypeMap[m_jetType] + "_mass", &jets_mass);
    outTree->Branch(jetTypeMap[m_jetType] + "_flavour", &jets_flavour);
    outTree->Branch(jetTypeMap[m_jetType] + "_btags", &jets_btags);

    std::cout << "Done JetSel initialization......\n";
    std::cout << "\n";
};

JetSel::~JetSel(){};

void JetSel::Select(eventForNano *e, const Bool_t isData, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec, const std::vector<Double_t> &tauEtaVec, const std::vector<Double_t> &tauPhiVec, const Bool_t deepJet, const Bool_t ifJER, const Int_t sysJEC)
{
    // jetType=0  -> usual jets; we use loose ID; jetType = 1: tight ID
    // jetType=11 -> b-jets L, jetType=12 -> b-jets M, jetType=13 -> b-jets T, jetType=2  -> forward jets
    clearBranch();
    calJER_SF(e, isData);

    Double_t MaxMostForwardJetEta = -99;
    for (UInt_t j = 0; j < e->Jet_pt.GetSize(); ++j)
    {
        Double_t jetpt = static_cast<Double_t>(e->Jet_pt.At(j));
        Double_t ijetMass = e->Jet_mass.At(j);
        Double_t ijetEta = e->Jet_eta.At(j);
        Double_t ijetPhi = e->Jet_phi.At(j);
        if (ifJER)
        {
            jetpt = jetpt * JER_SF_new.at(j);
            ijetMass = ijetMass * JER_SF_new.at(j);
            // jetpt *= jetSmearingFactors[j];
            // ijetMass *= jetSmearingFactors[j];
        }
        // maybe scaling only changes pt and mass? yes!
        switch (sysJEC)
        {
        case 0:
            break;
        case 1:
            jetpt = jetpt * (1 + jets_JESuncer[j]);
            ijetMass *= (1 + jets_JESuncer[j]);
            break;
        case 2:
            jetpt *= (1 - jets_JESuncer[j]);
            ijetMass *= (1 - jets_JESuncer[j]);
            break;
        default:
            break;
        }
        // here SF_up or SF_down should also be apllied.
        if (!(jetpt > 25))
            continue;
        if (!(fabs(ijetEta) < 5.0))
            continue;
        // cout << "jetId = " << e->Jet_jetId.At(j)<<"\n";
        if (!(e->Jet_jetId.At(j) > 0))
            continue; // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        // Jet ID flags bit1 is loose (always ：wfalse in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        // passlooseID*1+passtightID*2+passtightLepVetoID*4
        if (m_jetType == 1)
        {
            if (!(e->Jet_jetId.At(j) > 1))
                continue; // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        }

        if (m_jetType == 11 || m_jetType == 12 || m_jetType == 13)
        {
            if (!(fabs(ijetEta) < 2.4))
                continue;
        }
        if (deepJet)
        { // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
            if (m_jetType == 11)
            {
                if (!(e->Jet_btagDeepFlavB.At(j) > DeepJetL[m_era]))
                    continue;
            }
            if (m_jetType == 12)
            {
                if (!(e->Jet_btagDeepFlavB.At(j) > DeepJetM[m_era]))
                    continue;
            }
            if (m_jetType == 13)
            {
                if (!(e->Jet_btagDeepFlavB.At(j) > DeepJetT[m_era]))
                    continue;
            }
        }
        else
        {
            if (m_jetType == 11)
            {
                if (!(e->Jet_btagDeepB.At(j) > DeepCSVL[m_era]))
                    continue;
            }
            if (m_jetType == 12)
            {
                if (!(e->Jet_btagDeepB.At(j) > DeepCSVM[m_era]))
                    continue;
            }
            if (m_jetType == 13)
            {
                if (!(e->Jet_btagDeepB.At(j) > DeepCSVT[m_era]))
                    continue;
            }
        }
        // find mostforwardjeteta
        if (m_jetType == 0 || m_jetType == 1)
        { // normal jet
            if (fabs(ijetEta) > MaxMostForwardJetEta)
            {
                MaxMostForwardJetEta = fabs(ijetEta);
            } // MostForwardJetEta branch in new tree and SB.
            if (!(fabs(ijetEta) < 2.4))
                continue;
        }
        if (m_jetType == 2)
        { // forwardjet
            if (!(fabs(ijetEta) >= 2.4 && fabs(ijetEta) <= 5))
                continue;
            if (!(jetpt > 25))
                continue;
            if (fabs(ijetEta) >= 2.7 && fabs(ijetEta) <= 3.0)
            {
                if (!(jetpt > 60.0))
                    continue;
            }
        }
        // overlap removal
        if (lepEtaVec.size() > 0)
        {
            Double_t minDeltaR_lep = deltRmin(e->Jet_eta.At(j), e->Jet_phi.At(j), lepEtaVec, lepPhiVec);
            // Double_t deltaR = 0;
            // Double_t minDeltaR = 100;
            // for (UInt_t lep = 0; lep < lepEtaVec.size(); lep++)
            // {
            //     deltaR = DeltaR(LeptonsMVAF[lep].Eta(), ijetEta, LeptonsMVAF[lep].Phi(), ijetPhi);
            //     if (deltaR < minDeltaR)
            //         minDeltaR = deltaR; // The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
            // }
            if (!(minDeltaR_lep >= 0.4))
                continue;
        }
        if (tauEtaVec.size() > 0)
        {
            Double_t minDeltaR_tau = deltRmin(e->Jet_eta.At(j), e->Jet_phi.At(j), tauEtaVec, tauPhiVec);
            // Double_t deltaR_tau = 0;
            // Double_t minDeltaR_tau = 100;
            // for (UInt_t tau = 0; tau < SelectedTausL.size(); tau++)
            // {
            //     deltaR_tau = DeltaR(SelectedTausL[tau].Eta(), ijetEta, SelectedTausL[tau].Phi(), ijetPhi);
            //     if (deltaR_tau < minDeltaR_tau)
            //         minDeltaR_tau = deltaR_tau;
            // }
            if (!(minDeltaR_tau >= 0.4))
                continue;
        }
        // ROOT::Math::PtEtaPhiMVector jet_prov(jetpt, ijetEta, ijetPhi, ijetMass);
        // SelectedJets.push_back(jet_prov);
        // SelectedJetsIndex.push_back(j);
        // // CHANGE HERE TO RUN ON DATA
        // SelectedJetsFlavor.push_back(e->Jet_hadronFlavour.At(j));
        // if (deepJet)
        // {
        //     SelectedJetsBTags.push_back(e->Jet_btagDeepFlavB.At(j));
        // }
        // else
        // {
        //     SelectedJetsBTags.push_back(e->Jet_btagDeepB.At(j));
        // }
        jets_pt.push_back(jetpt);
        jets_eta.push_back(ijetEta);
        jets_phi.push_back(ijetPhi);
        jets_mass.push_back(ijetMass);
        jets_flavour.push_back(e->Jet_hadronFlavour.At(j));
        jets_btags.push_back(e->Jet_btagDeepB.At(j));
    }
};

// void JetSel::calJER_SF(const eventForNano *e, const Bool_t isData)
void JetSel::calJER_SF(eventForNano *e, const Bool_t isData)
{
    // https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/jercExample.py
    // https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Uncertai
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
    // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h
    auto corr_jerSF = cset_jerSF->at(corr_SF_map[m_era].at(0).Data());
    auto corr_jerResolution = cset_jerSF->at(corr_SF_map[m_era].at(2).Data());

    //???not sure how to get the JEC uncertainty for data yet?
    // https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetmetHelperRun2.py
    auto corr_jesUncer = cset_jerSF->at(corr_SF_map[m_era].at(1).Data());
    //???does the MC_Total include the JER uncertainty?

    JER_SF_new.clear();

    Double_t iSF = 1.0;
    // Double_t iSF_up = 1.0;
    // Double_t iSF_down = 1.0;
    Double_t iSF_JESuncer = 0.0;
    const Double_t MIN_JET_ENERGY = 1e-2;
    for (UInt_t i = 0; i < e->Jet_pt.GetSize(); i++)
    {
        Double_t ieta = e->Jet_eta.At(i);
        Double_t iphi = e->Jet_phi.At(i);
        Double_t ipt = e->Jet_pt.At(i);
        ROOT::Math::PtEtaPhiMVector ijetVec(ipt, ieta, iphi, e->Jet_mass.At(i));
        Double_t ienergy = ijetVec.energy();
        // std::cout << "Jet_rawFactor=" << Jet_rawFactor[i] << "\n";
        // Double_t rawJetPt = ipt * (1 - Jet_rawFactor[i]);

        Double_t ijet_sf = corr_jerSF->evaluate({ieta, "nom"}); // JER_SF_new
        // not in a pT-dependent format, strong pT dependency at high eta is however observed to be reduced in UL
        // iSF_up = corr_jerSF->evaluate({Jet_eta.At(i), "up"});
        // iSF_down = corr_jerSF->evaluate({Jet_eta.At(i), "down"});
        Double_t ijet_res = corr_jerResolution->evaluate({{ipt, ieta, *e->fixedGridRhoFastjetAll}}); // jet_resolution
        // Double_t ijet_res = corr_jerResolution->evaluate({{rawJetPt, ieta, *fixedGridRhoFastjetAll}}); // jet_resolution
        // what is this rho? average energy density , for a event

        // find gen matching
        Int_t genMatchIndex = genMatchForJER(ieta, iphi, ipt, *e->GenJet_eta, *e->GenJet_phi, *e->GenJet_pt, ijet_res);
        // Int_t genMatchIndex = genMatchForJER(ieta, iphi, rawJetPt, GenJet_eta, GenJet_phi, GenJet_pt, ijet_res);
        if (!isData)
        {
            if (genMatchIndex > 0)
            {
                // Case 1: we have a "good" generator level jet matched to the reconstructed jet
                Double_t dPt = ipt - (*e->GenJet_pt)[genMatchIndex];
                // Double_t dPt = rawJetPt - GenJet_pt[genMatchIndex];
                iSF = 1 + (ijet_sf - 1.) * dPt / ipt;
                // iSF = 1 + (ijet_sf - 1.) * dPt / rawJetPt;
            }
            else
            { // Case 2: we don't have a gen jet. Smear jet pt using a random gaussian variation
                Double_t sigma = ijet_res * std::sqrt(ijet_sf * ijet_sf - 1);

                std::normal_distribution<> d(0, sigma);
                iSF = 1. + d(m_random_generator); // m_random_generator = std::mt19937(seed) //std::uint32_t>("seed", 37428479);
            }
            if (ienergy * iSF < MIN_JET_ENERGY)
            {
                // Negative or too small smearFactor. We would change direction of the jet
                // and this is not what we want.
                // Recompute the smearing factor in order to have jet.energy() == MIN_JET_ENERGY
                Double_t newSmearFactor = MIN_JET_ENERGY / ienergy;
                iSF = newSmearFactor;
            }

            // iSF_JES = corr_jesSF_L1->evaluate({ieta, ipt, "nom"});
            // iSF_JES = corr_jesSF_L1->evaluate({ Jet_area.At(i), ieta, ipt, 0.0 });
            iSF_JESuncer = corr_jesUncer->evaluate({ieta, ipt});
        }
        // std::cout << "iJERSF: " << iSF << "\n";
        // std::cout<<"iSF_JES"<<iSF_JESuncer<<"\n";
        JER_SF_new.push_back(iSF);
        // jer_sf_up.push_back(iSF_up);
        // jer_sf_down.push_back(iSF_down);
        jets_JESuncer.push_back(iSF_JESuncer);
    }
    // for (UInt_t i = 0; i < JER_SF_new.size(); i++)
    // {
    //     std::cout << i << "jerSF=" << JER_SF_new[i] << "  ";
    // }
    // std::cout << "\n";
};

void JetSel::clearBranch()
{
    jets_pt.clear();
    jets_eta.clear();
    jets_phi.clear();
    jets_mass.clear();
    jets_flavour.clear();
    jets_btags.clear();
};

std::vector<Double_t> &JetSel::getEtaVec()
{
    return jets_eta;
};
std::vector<Double_t> &JetSel::getPhiVec()
{
    return jets_phi;
};

Int_t JetSel::getSize(){
    return jets_pt.size();
}