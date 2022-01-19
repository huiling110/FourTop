#ifndef TauIDSFTool_h
#define TauIDSFTool_h

/*
 * @class TauIDSFTool
 *
 * Class to retrieve tau ID SFs.
 *  - pT-dependent SFs for MVAoldDM2017v2
 *  - DM-dependent SFs for MVAoldDM2017v2
 *  - eta-dependent SFs for anti-lepton discriminators
 * Source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV
 * Inspiration from TauTriggerSFs/src/TauTriggerSFs2017.cc
 *
 * @author Izaak Neutelings
 * @date July 2019
 *
 */

#include <TFile.h>   // TFile
#include <TH1.h>     // TH1
#include <TF1.h>     // TF1
#include <TGraph.h>
#include <TString.h> // Form
#include <string>    // std::string
#include <vector>    // std::vector
#include <map>       // std::map
#include <stdlib.h>  // getenv
#include <functional>

class TauIDSFTool {

  protected:

    std::map<const std::string,const TF1*> func;
    TH1* hist;
    [[noreturn]] void disabled() const;

  public:

    std::string ID;
    std::string WP;
    bool emb;
    bool otherVSlepWP;
    std::vector<int> DMs;
    std::vector<int> genmatches;
    bool isVsPT  = false;
    bool isVsDM  = false;
    bool isVsEta = false;

    TauIDSFTool(const std::string& year, const std::string& id="MVAoldDM2017v2", const std::string& wp="Tight",
                const bool dm=false, const bool embedding=false, const bool OtherVSlepWP=false);
    ~TauIDSFTool() { }

    float getSFvsPT( double pt,          int genmatch, const std::string& unc="");
    float getSFvsPT( double pt,                        const std::string& unc="");
    float getSFvsDM( double pt,  int dm, int genmatch, const std::string& unc="") const;
    float getSFvsDM( double pt,  int dm,               const std::string& unc="") const;
    float getSFvsEta(double eta,         int genmatch, const std::string& unc="") const;

};

class TauESTool {

 protected:
    TH1* hist_lowpt;
    TH1* hist_highpt;
    [[noreturn]] void disabled() const;
 public:
    std::string ID;
    std::vector<int> DMs;
    float pt_low = 34.0;
    float pt_high = 170;
    TauESTool(const std::string& year, const std::string& id="DeepTau2017v2p1VSjet");
    ~TauESTool() { }

    float getTES(double pt, int dm, int genmatch, const std::string& unc);
};

class TauFESTool {

 protected:
    TGraph* graph;
    [[noreturn]] void disabled() const;
 public:
    std::string ID;
    std::vector<int> DMs = {0, 1};
    std::vector<int> genmatches = {1, 3};
    TauFESTool(const std::string& year, const std::string& id="DeepTau2017v2p1VSe");
    ~TauFESTool() { }

    float getFES(double eta, int dm, int genmatch, const std::string& unc);
};

#endif // TauIDSFTool_h
