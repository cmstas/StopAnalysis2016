#ifndef EVENTTREE_H
#define EVENTTREE_H
 
#include <string>
#include <vector>
#include "Math/LorentzVector.h"
 
// forward declarations
class TTree;
 
// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<std::string> vecs;
typedef std::vector<int> veci; 
typedef std::vector<bool> vecb;
 
class EventTree
{
public:
    // constructor/destructor
    EventTree ();
    EventTree (const std::string &prefix);
    virtual ~EventTree (){}
 
    void Reset ();
    void SetBranches (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon (const std::string &root_file_name = "");
 
private:
    std::string prefix_;
 
public:
    // branch objects
    unsigned int run;
    unsigned int ls;
    unsigned int evt;
    int nvtxs;

    unsigned int nEvents;
    unsigned int nEvents_goodvtx;
    unsigned int nEvents_MET30;
    unsigned int nEvents_1goodlep;
    unsigned int nEvents_2goodjets;    

    int ngoodleps;
    int nvetoleps;   
 
    double MT2W;
    double MT2W_lep2;
    double chi2;
    double topness;
    double Topness_lep2;
    double TopnessMod_lep1;
    double TopnessMod_lep2;

    float MT2_lb_b_lep1;
    float MT2_lb_b_lep2;
    float MT2_lb_b_mass_lep1;
    float MT2_lb_b_mass_lep2;
    float MT2_lb_bqq_lep1;
    float MT2_lb_bqq_lep2;
    float MT2_lb_bqq_mass_lep1;
    float MT2_lb_bqq_mass_lep2;

    float Mlb;
    float Mlb_lep2;
    float M3b;
    float M3b_lep2;

    float pfmet;
    float pfmet_phi;

    float dR_lep_leadb;
    float dR_lep2_leadb;    
    float mindphi_met_j1_j2;
    float mt_met_lep;
    float mt_met_lep2;

    float dphi_Wlep;
    float MET_over_sqrtHT;
    float ak4jets_rho;
 
    bool is_data;
 
    std::string dataset;
    std::string filename;    
    std::string cms3tag;

    //gen info//
    float scale1fb;
    float xsec;
    float kfactor;
    float pu_ntrue;
    int pu_nvtxs;

    //sparms
    vecs sparms_comment;
    vecs sparms_names;
    float sparms_filterEfficiency;
    float sparms_pdfScale;
    float sparms_pdfWeight1;
    float sparms_pdfWeight2;
    float sparms_weight;
    float sparms_xsec;
    vecd sparms_values;
    int sparms_subProcessId;
        
    //gen met
    float genmet;
    float genmet_phi;

   //veto
   bool PassTrackVeto;
   bool PassTauVeto;

    float EA_all_rho;
    float EA_allcalo_rho;
    float EA_centralcalo_rho;
    float EA_centralchargedpileup_rho;
    float EA_centralneutral_rho;
    //trigger
    //int  HLT_HT900;
    int HLT_SingleMu; 
    int HLT_SingleEl;
    int HLT_MET170;
    int HLT_ht350met120; 
    int HLT_MET120Btag;      
    int HLT_MET120Mu5;      
};
 
#endif
