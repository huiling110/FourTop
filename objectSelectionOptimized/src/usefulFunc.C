#include "../include/usefulFunc.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

#include <TString.h>
#include "TObjString.h"
#include <TObjArray.h>

namespace OS
{

    // https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM
    void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis)
    {
        if (isdata)
        { // deal with Lumi JSONs only if reading data
            if (jsonInFile)
            {
                std::cout << "Reading JSON file " << jsonInFile << std::endl;
                std::ifstream cfgfile(jsonInFile);
                if (!cfgfile.good())
                {
                    std::cout << "File " << jsonInFile << " is not a correct file - please check JSON file strings in configuration file.\nExiting." << std::endl;
                    exit(8);
                }
                std::string JSON = "";
                std::string readLine;
                bool firstline = true;
                while (getline(cfgfile, readLine))
                { // read all lines from JSON file
                    std::stringstream ss(readLine);
                    std::string line = ss.str();
                    if (!firstline && line != "}")
                        line.erase(0, 1); // erase first charater: in golden JSONs each line starts with two spaces, but we want just one separating good runs; also, save last curly bracket
                    JSON.append(line);
                    if (firstline)
                        firstline = false;
                }
                TString processString = JSON;
                TString segment;
                Ssiz_t from = 2;
                while (processString.Tokenize(segment, from, ", \""))
                {
                    // JSON file has a layout like this: "284029": [[1, 112]], "284035": [[1, 369]], etc
                    // So first tokenize with respect to the string ', "' which separates each run+lumi block
                    // You get tokens in the form 284029": [[1, 112]]
                    TObjArray *mapItem = segment.Tokenize("\"");
                    // Now tokenize with respect to the string '"'
                    // You get two-element tokens with 1st being '284029' and second being ': [[1, 112]]'
                    Int_t key = (((TObjString *)(mapItem->At(0)))->String()).Atoi();
                    TString value = ((TObjString *)(mapItem->At(1)))->String();
                    TObjArray *values = value.Tokenize("[], :}");
                    // Finally tokenize the second element to remove everything which is not an integer
                    // You get the good lumi sections
                    // std::vector<Int_t> valueVec;
                    std::vector<UInt_t> valueVec;
                    for (Int_t i = 0; i < values->GetEntries(); i++)
                    {
                        valueVec.push_back((((TObjString *)(values->At(i)))->String()).Atoi());
                    }
                    _goodLumis[key] = valueVec;
                }
            } // end if JSON file
        }
    }

    Double_t TopLeptonEvaluate(std::map<TString, Float_t> &inputFeatures, const BoosterHandle &booster)
    {

        float boosterVars[1][13];
        boosterVars[0][0] = inputFeatures["pt"];
        boosterVars[0][1] = inputFeatures["eta"];
        boosterVars[0][2] = inputFeatures["jetNDauCharged"];
        boosterVars[0][3] = inputFeatures["miniPFRelIso_chg"];
        boosterVars[0][4] = inputFeatures["miniPFRelIso_all"] - inputFeatures["miniPFRelIso_chg"];
        boosterVars[0][5] = inputFeatures["jetPtRelv2"];
        boosterVars[0][6] = inputFeatures["jetPtRatio"];
        boosterVars[0][7] = inputFeatures["pfRelIso03_all"];
        boosterVars[0][8] = inputFeatures["jetBTag"];
        boosterVars[0][9] = inputFeatures["sip3d"];
        boosterVars[0][10] = TMath::Log(TMath::Abs(inputFeatures["dxy"]));
        boosterVars[0][11] = TMath::Log(TMath::Abs(inputFeatures["dz"]));
        boosterVars[0][12] = inputFeatures["mvaFall17V2noIso"];

        // for (Int_t i = 0; i < 13; i++)
        // {
        //     std::cout << "inputFeatures: "<<i<<" " << boosterVars[0][i] << "\n";
        // }
        // std::cout<<"\n";

        // BoosterHandle booster;
        // XGBoosterCreate(NULL, 0, &booster);
        // XGBoosterLoadModel(booster, muonWeight.Data());

        DMatrixHandle dtest;
        int nfeat = 13;
        XGDMatrixCreateFromMat(reinterpret_cast<float *>(boosterVars[0]), 1, nfeat, NAN, &dtest);
        bst_ulong out_len;
        const float *f;
        XGBoosterPredict(booster, dtest, 0, 0, &out_len, &f);
        // XGBoosterPredict(booster[0], dtest, 0, 0, 0, &out_len, &f);
        XGDMatrixFree(dtest);
        // XGBoosterFree(booster);
        // std::cout << "Top lepton score = " << f[0] << "\n";
        Double_t score = f[0];
        // std::cout<<"MVAscore="<<score<<"\n";

        return score;
    }

    Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2)
    {
        Double_t deltaPhi = TMath::Abs(phi1 - phi2);
        Double_t deltaEta = eta1 - eta2;
        if (deltaPhi > TMath::Pi()){
            deltaPhi = TMath::TwoPi() - deltaPhi;
        }
        return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
    }

    Double_t deltRmin(const Double_t eta1, const Double_t phi1, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec)
    {
        //???what if lep size=0?
        Double_t deltaR = 0;
        Double_t minDeltaR = 100;
        for (UInt_t lep = 0; lep < lepEtaVec.size(); lep++)
        {
            deltaR = DeltaR(lepEtaVec[lep], eta1, lepPhiVec[lep], phi1);
            // std::cout << lepEtaVec[lep]<< eta1<< lepPhiVec[lep]<< phi1 << " "<<deltaR<< "\n";
            if (deltaR < minDeltaR)
                minDeltaR = deltaR; // The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
        }
        return minDeltaR;
    };

    Bool_t overlapRemove(Double_t tauEta, Double_t tauPhi, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec ){
        Bool_t removeTau = kFALSE;
        Double_t min = deltRmin(tauEta, tauPhi, lepEtaVec, lepPhiVec);
        if (min < 0.4) {
            removeTau = kTRUE;
        }
        return removeTau;
    };

    void addTwoObjs(const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &eleEtaVec, std::vector<Double_t> &lepEtaVec)

    {
        lepEtaVec.clear();
        lepEtaVec = muEtaVec;
        lepEtaVec.insert(lepEtaVec.end(), eleEtaVec.begin(), eleEtaVec.end());
        std::sort(lepEtaVec.begin(), lepEtaVec.end(), descendingComparator);
    };

    Bool_t descendingComparator(const Double_t &a, const Double_t &b)
    {
        return a > b;
    };

    // void getLepEtaPhi(std::vector<Double_t>& lepEtaVec, std::vector<Double_t>& lepPhiVec,const std::vector<Double_t>& muEtaVec, const std::vector<Double_t>& muPhiVec,  const std::vector<Double_t>& eleEtaVec, const std::vector<Double_t>& elePhiVec){
    // void getLepEtaPhi(std::vector<Double_t>& lepEtaVec, std::vector<Double_t>& lepPhiVec,  EleTopMVASel& eleTopMVATSel, MuTopMVASel& muTopMVATSel ){
    //     const std::vector<Double_t>& muEtaVec= muTopMVATSel.getEtaVec();
    //     const std::vector<Double_t>& muPhiVec= muTopMVATSel.getPhiVec();
    //     std::cout<<"muEtaVec = "<< muEtaVec.size()<<"\n";
    //     const std::vector<Double_t>& eleEtaVec= eleTopMVATSel.getEtaVec();
    //     const std::vector<Double_t>& elePhiVec= eleTopMVATSel.getPhiVec();
    //     std::cout<<"eleEtaVec = "<< eleEtaVec.size()<<"\n";
    //     addTwoObjs( muEtaVec, eleEtaVec, lepEtaVec);
    //     addTwoObjs( muPhiVec, elePhiVec, lepPhiVec);
    //     std::cout<<"lepEtaVec = "<< lepEtaVec.size()<<"\n";
    // };

    Int_t genMatchForJER(Double_t recoEta, Double_t recoPhi, Double_t recoPt, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, TTreeReaderArray<Float_t> &genPt, Double_t jet_resolution)
    {
        // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h#L61
        Double_t matched_genJetIndex = -99;
        double min_dR = std::numeric_limits<double>::infinity();
        for (UInt_t i = 0; i <= genEta.GetSize(); i++)
        {
            // Try to find a gen jet matching
            // dR < m_dR_max
            // dPt < m_dPt_max_factor * resolution
            // resolution = jet.pt() * jet_resolution

            Double_t dR = DeltaR(recoEta, genEta.At(i), recoPhi, genPhi.At(i));

            if (dR > min_dR)
                continue;
            if (dR < 0.2)
            { // m_dR_max = 0.2
                Double_t dPt = std::abs(genPt[i] - recoPt);
                // if (TMath::Abs(recoPt - genPt[i]) > 3 * recoPt * jet_resolution)
                // if (dPt > m_dPt_max_factor * resolution)
                if (dPt > 3 * recoPt * jet_resolution)
                    continue;
                min_dR = dR;
                matched_genJetIndex = i;
            }
        }
        return matched_genJetIndex;
    };

    Bool_t isRun3(TString era)
    {
        Bool_t isRun3 = kFALSE;
        if (era.CompareTo("2022") == 0)
        {
            isRun3 = kTRUE;
        }
        return isRun3;
    }

    Double_t quadraticSum(TTreeReaderArray<Float_t>& vec, const Float_t nominal, Int_t eleNum) {
        Double_t sum = 0.0;
        Int_t count = 0;
        // if (vec!=nullptr){
            for (Float_t element : vec)
            {
                // for (UInt_t i = 0; i < vec.GetSize(); i++){
                // if(i<eleNum+1){
                if(count<eleNum+1){
                    // sum += std::pow(vec.At(i)-nominal, 2);
                    sum += std::pow(element-nominal, 2);
                }
                count++;
            }
        // }
        return TMath::Sqrt(sum);
    }

    // Int_t getValForDynamicReader(const Bool_t isRun3, const DynamicBranchReader& reader, const UInt_t i){
    //     Int_t val = 0;
    //     if(isRun3){
    //         val = std::any_cast<UChar_t>(reader.at(i));
    //     }else
    //     {
    //         val = std::any_cast<Int_t>(reader.at(i));
    //     }
    //     return val;
    // }



};
