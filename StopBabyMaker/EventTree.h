#ifndef EVENTTREE_H
#define EVENTTREE_H
 
#include <string>
#include <vector>
#include "Math/LorentzVector.h"
#include "Tools/badEventFilter.h"
 
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
    void SetMetFilterEvents(); 
private:
    std::string prefix_;
      eventFilter metFilterTxt; 
public:
    // branch objects
    unsigned int run;
    unsigned int ls;
    unsigned int evt;
    int nvtxs;

    int   firstGoodVtxIdx;
    int   firstVtx_isfake;
    float firstVtx_ndof;
    float firstVtx_posRho;
    float firstVtx_posZ;
    LorentzVector  firstVtx_posp4;

    unsigned int nEvents;
    unsigned int nEvents_goodvtx;
    unsigned int nEvents_MET30;
    unsigned int nEvents_1goodlep;
    unsigned int nEvents_2goodjets;

    int genlepsfromtop;

    int genLepsHardProcess;
    int genNusHardProcess;
    
    int is0lep;
    int is1lep;
    int is2lep;
    int isZtoNuNu;

    int is1lepFromW;
    int is1lepFromTop;

    int ngoodleps;
    int nlooseleps;   
    int nvetoleps;   
 
    float MT2W;
    float MT2W_lep2;
    float hadronic_top_chi2;
    float topness;
    float topness_lep2;
    float topnessMod;
    float topnessMod_lep2;

    float MT2_lb_b;
    float MT2_lb_b_lep2;
    float MT2_lb_b_mass;
    float MT2_lb_b_mass_lep2;
    float MT2_lb_bqq;
    float MT2_lb_bqq_lep2;
    float MT2_lb_bqq_mass;
    float MT2_lb_bqq_mass_lep2;

    float Mlb_closestb;
    float Mlb_lead_bdiscr;
    float Mlb_closestb_lep2;
    float Mlb_lead_bdiscr_lep2;
    float Mjjj;
    float Mjjj_lep2;

    float pfmet;
    float pfmet_phi;
    float calomet;
    float calomet_phi;

    float filt_cscbeamhalo;
    float filt_ecallaser;
    float filt_ecaltp;
    float filt_eebadsc;
    float filt_goodvtx;
    float filt_badevents;
    float filt_hbhenoise;
    float filt_hcallaser;
    float filt_met;
    float filt_trkfail;
    float filt_trkPOG;
    float filt_trkPOG_tmc;
    float filt_trkPOG_tms;
    float filt_eff;

    float dR_lep_leadb;
    float dR_lep2_leadb;    
    float mindphi_met_j1_j2;
    float mt_met_lep;
    float mt_met_lep2;

    float dphi_Wlep;
    float MET_over_sqrtHT;
    float ak4pfjets_rho;
 
    bool is_data;
 
    std::string dataset;
    std::string filename;    
    std::string cms3tag;

    //gen info//
    float scale1fb;
    float xsec;
    float kfactor;
    float pu_ntrue;
    int   pu_nvtxs;
    vecd  genweights;
    vecs  genweightsID;

    //sparms
    vecs  sparms_comment;
    vecs  sparms_names;
    float sparms_filterEfficiency;
    float sparms_pdfScale;
    float sparms_pdfWeight1;
    float sparms_pdfWeight2;
    float sparms_weight;
    float sparms_xsec;
    vecd  sparms_values;
    int   sparms_subProcessId;
    float mass_lsp;
    float mass_chargino;
    float mass_stop;
        
    //gen met
    float genmet;
    float genmet_phi;
    float genht;

    //veto
    bool PassTrackVeto;
    bool PassTrackVeto_v2;
    bool PassTrackVeto_v3;
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
    int HLT_MET120Btag;      
    int HLT_MET120Mu5;
    //new
    int HLT_HT350MET120;
    int HLT_DiEl;
    int HLT_DiEl_17_12;
    int HLT_DiMu;
    int HLT_Mu8El17;
    int HLT_Mu8El23;
    int HLT_Mu17El12;
    int HLT_Mu23El12;
    int HLT_SingleElTight;
    int HLT_SingleEl23;
    int HLT_SingleEl27;
    int HLT_SingleEl27Tight;
    int HLT_SingleElHT200;
    int HLT_SingleMuNoEta;
    int HLT_SingleMuNoIso;
    int HLT_SingleMuNoIsoNoEta;
    int HLT_Mu6HT200MET125;

    int HLT_HT350MET100;
    int HLT_SingleMu17 ;
    int HLT_SingleMu20 ;
    int HLT_SingleMu24 ;

    int HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight;
    int HLT_MET90_MHT90_IDTight;
    int HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight;

    int HLT_Photon90_CaloIdL_PFHT500;
    int HLT_Photon22_R9Id90_HE10_IsoM;
    int HLT_Photon30_R9Id90_HE10_IsoM;
    int HLT_Photon36_R9Id90_HE10_IsoM;
    int HLT_Photon50_R9Id90_HE10_IsoM;
    int HLT_Photon75_R9Id90_HE10_IsoM; 
    int HLT_Photon90_R9Id90_HE10_IsoM; 
    int HLT_Photon120_R9Id90_HE10_IsoM;
    int HLT_Photon165_R9Id90_HE10_IsoM;
    int HLT_Photon175;
    int HLT_Photon165_HE10;

    float pu_weight;
    float lep_sf;
    float btag_sf;
    float HLT_SingleMu_eff;
    float HLT_SingleEl_eff;

    //photon addition
    int nPhotons;
    int ph_selectedidx;//not necessarily first photon
    int ph_ngoodjets;
    int ph_ngoodbtags;
    float ph_met;
    float ph_met_phi;
    float ph_HT;
    float ph_htssm;
    float ph_htosm;
    float ph_htratiom;
    float ph_mt_met_lep;
    float ph_dphi_Wlep;
    float ph_MT2W;
    float ph_topness;
    float ph_topnessMod;
    float ph_MT2_lb_b_mass;
    float ph_MT2_lb_b;
    float ph_MT2_lb_bqq_mass;
    float ph_MT2_lb_bqq;
    float ph_hadronic_top_chi2;
    float ph_mindphi_met_j1_j2;
    float ph_Mlb_lead_bdiscr;
    float ph_dR_lep_leadb;
    float ph_Mlb_closestb;
    float ph_Mjjj;

    int   Zll_idl1;
    int   Zll_idl2;
    LorentzVector  Zll_p4l1;
    LorentzVector  Zll_p4l2;
    bool  Zll_OS;
    bool  Zll_SF;
    bool  Zll_isZmass;
    float Zll_M;
    LorentzVector  Zll_p4;
    int   Zll_selLep;
    float Zll_met;
    float Zll_met_phi;
    float Zll_mindphi_met_j1_j2;
    float Zll_mt_met_lep;
    float Zll_dphi_Wlep;
    float Zll_MT2W;
    float Zll_topness;
    float Zll_topnessMod;
    float Zll_MT2_lb_b_mass;
    float Zll_MT2_lb_b;
    float Zll_MT2_lb_bqq_mass;
    float Zll_MT2_lb_bqq;

    
};
 
#endif
