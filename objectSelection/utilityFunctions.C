
#include "utilityFunctions.h"
#include "TString.h"
#include "TObjString.h"

void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Float_t> &array, std::vector<Double_t> &vec)
{
    for (UInt_t i = 0; i < array.GetSize(); i++)
    {
        vec.push_back(array.At(i));
    }
}
void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Int_t> &array, std::vector<Double_t> &vec)
{
    for (UInt_t i = 0; i < array.GetSize(); i++)
    {
        vec.push_back(array.At(i));
    }
}

void printElements(const std::vector<Double_t> &jets_btags, const std::vector<ROOT::Math::PtEtaPhiMVector> &jets)
{
    for (UInt_t j = 0; j < jets_btags.size(); j++)
    {
        std::cout << jets[j].Pt() << ":" << jets_btags[j] << " ";
        // std::cout<<jets_btags[j]<<"  ";
    }
    std::cout << "  \n";
}

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2)
{
    Double_t deltaPhi = TMath::Abs(phi1 - phi2);
    Double_t deltaEta = eta1 - eta2;
    if (deltaPhi > TMath::Pi())
    {
        deltaPhi = TMath::TwoPi() - deltaPhi;
    }
    return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}

Double_t deltRmin(const Double_t eta1, const Double_t phi1, const std::vector<ROOT::Math::PtEtaPhiMVector> LeptonsMVAF)
{
    Double_t deltaR = 0;
    Double_t minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++)
    {
        deltaR = DeltaR(LeptonsMVAF[lep].Eta(), eta1, LeptonsMVAF[lep].Phi(), phi1);
        if (deltaR < minDeltaR)
            minDeltaR = deltaR; // The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    return minDeltaR;
}

bool compEle(const ROOT::Math::PtEtaPhiMVector a, const ROOT::Math::PtEtaPhiMVector b)
{
    return a.Pt() > b.Pt();
}
// test
/*
void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Float_t> &array, std::vector<Double_t> & vec){
    for( UInt_t i=0; i< array.GetSize(); i++){
        vec.push_back( array.At(i));
    }
}
void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Int_t> &array, std::vector<Double_t> & vec){
    for( UInt_t i=0; i< array.GetSize(); i++){
        vec.push_back( array.At(i));
    }
}
*/

// void jetsSubstructBjets(std::vector<TLorentzVector>& nonbjets, const std::vector<Double_t> &bjets_btags,const std::vector<Double_t> &jets_btags,  const std::vector<TLorentzVector>& jets ){
void jetsSubstructBjets(std::vector<ROOT::Math::PtEtaPhiMVector> &nonbjets, const std::vector<ROOT::Math::PtEtaPhiMVector> &jets, const std::vector<ROOT::Math::PtEtaPhiMVector> &bjets)
{
    // for( UInt_t jet =0; jet<jets_btags.size(); jet++){
    // if ( jets_btags[jet]== bjets_btags[jet]){
    // nonbjets.push_back( jets[jet]);
    // }
    // }
    Bool_t findMatchingB = false;
    for (UInt_t j = 0; j < jets.size(); j++)
    {
        for (UInt_t i = 0; i < bjets.size(); i++)
        {
            if (bjets[i] == jets[j])
            {
                // nonbjets.push_back( jets[j]);
                findMatchingB = true;
                break;
            }
        }
        if (!findMatchingB)
            nonbjets.push_back(jets[j]);
        findMatchingB = false;
    }
}

// SelectJets(0, deepJet, jets, jets_btags, jets_index, jets_flavour, SysJes, SysJer, leptonsMVAL, tausL);
void sortJetAndFlavorAndBcore(std::vector<ROOT::Math::PtEtaPhiMVector> &jets, std::vector<Double_t> &jets_btags, std::vector<Int_t> jets_flavour)
{
    sort(jets_btags.begin(), jets_btags.end(), [&](std::size_t i, std::size_t j)
         { return jets[i].Pt() > jets[j].Pt(); });
}

void readSmearingFile(TString _path, std::vector<std::vector<std::string>> &_resolution, std::string &_resFormula)
{

    std::ifstream file(_path);
    std::string lineStr;
    bool firstLine = true;
    while (std::getline(file, lineStr))
    {
        std::stringstream ss(lineStr);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        if (firstLine)
        {
            // if reading resolution file, store formula
            if (vstrings.size() > 5)
                _resFormula = vstrings[5];
            // else, store a toy formula
            else
                _resFormula = "none";
            firstLine = false;
            continue;
        }

        _resolution.push_back(vstrings);
    }
}

void getMatchingToGen(TTreeReaderArray<Float_t> &recoEta, TTreeReaderArray<Float_t> &recoPhi, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, std::vector<Int_t>* &matchingIdx)
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
//???relative pT resolution not implementing
{
    for (UInt_t i = 0; i < recoEta.GetSize(); i++)
    {
        Double_t dRmin = 10.0;
        int matchIdx = -1;
        int idx = -1;
        for (unsigned int j = 0; j < genEta.GetSize(); j++)
        {
            Double_t dr = DeltaR(recoEta.At(i), genEta.At(j), recoPhi.At(i), genPhi.At(j));
            if (dr < dRmin)
            {
                dRmin = dr;
                idx = j;
            }
        }
        if (dRmin < 0.2)
            matchIdx = idx;
        matchingIdx->push_back(matchIdx);
    }
}

Double_t GetJerFromFile(Double_t eta, std::vector<std::vector<std::string>> resSFs, int central)
{
    for (auto res : resSFs)
    { // go through all the lines
        if (eta < std::stof(res[0]) || eta > std::stof(res[1]))
            continue;                       // if jet eta out of range, move to next line
        return std::stof(res[central + 3]); // get SF. central == 0 ---> nominal, central == 1/2 ---> Down/Up
    }
    return 1.;
}

Double_t GetStochasticFactor(Double_t pt, Double_t eta, Double_t rho, std::vector<std::vector<std::string>> resolution, TString resFormula)
{

    TFormula resForm("", resFormula);

    for (auto res : resolution)
    {
        // skip if not in the right bin
        if (eta < std::stof(res[0]) || eta > std::stof(res[1]) || rho < std::stof(res[2]) || rho > std::stof(res[3]))
            continue;
        resForm.SetParameter(0, std::stof(res[7]));
        resForm.SetParameter(1, std::stof(res[8]));
        resForm.SetParameter(2, std::stof(res[9]));
        resForm.SetParameter(3, std::stof(res[10]));
    }
    return resForm.Eval(pt);
}

Double_t GetSmearFactor(Double_t pt, Double_t genPt, Double_t eta, Double_t rho, Double_t jer_sf, std::vector<std::vector<std::string>> resolution, TString resFormula, TRandom3 ran)
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
{

    Double_t smearFactor = 1.;
    Double_t relpterr = GetStochasticFactor(pt, eta, rho, resolution, resFormula);
    if (genPt > 0. && (abs(pt - genPt) < 3 * relpterr * pt))
    {
        double dPt = pt - genPt;
        smearFactor = 1 + (jer_sf - 1.) * dPt / pt;
    }
    else
    {
        smearFactor = 1 + ran.Gaus(0, relpterr) * std::sqrt(std::max(0., (jer_sf * jer_sf) - 1.));
        if (smearFactor <= 0.)
            smearFactor = 1.;
    }
    return smearFactor;
}

// https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM
void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis)
{
    if (isdata)
    { // deal with Lumi JSONs only if reading data
        //    TString jsonInFile = GoldenJSONs[era];
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

/////////////////////////