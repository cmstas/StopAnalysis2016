#ifndef eventWeight_lepSF_H
#define eventWeight_lepSF_H

// ROOT
#include "Riostream.h"
#include "TFile.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"

// C
#include <string>
#include <vector>

#include "stop_1l_babyAnalyzer.h"

//
// CLASS
//
class eventWeight_lepSF{

 public:

  // Sample info 
  bool sampleIsFastsim;


  // Fullsim Electron file
  TFile *f_el_SF;
  TFile *f_el_SF_tracking;

  // Fullsim Muon files
  TFile *f_mu_SF_id;
  TFile *f_mu_SF_iso;
  TFile *f_mu_SF_ip;
  TFile *f_mu_SF_tracking;
  TFile *f_mu_SF_veto_id;
  TFile *f_mu_SF_veto_iso;
  TFile *f_mu_SF_veto_ip;

  // Fullsim/Fastsim Electron files
  TFile *f_el_FS_ID;
  TFile *f_el_FS_Iso;
  TFile *f_el_veto_FS_ID;
  TFile *f_el_veto_FS_Iso;

  // Fullsim/Fastsim Muon files
  TFile *f_mu_FS_ID;
  TFile *f_mu_FS_Iso;
  TFile *f_mu_FS_Ip;
  TFile *f_mu_veto_FS_ID;
  TFile *f_mu_veto_FS_Iso;
  TFile *f_mu_veto_FS_Ip;

  // Lepton MC reco efficiency for veto lep IDs
  TFile *f_vetoLep_eff;
 
  // Final scale factor histograms for selected leptons
  TH2D *h_el_SF = NULL;
  TH2D *h_mu_SF = NULL;
  
  // Final scale factor histograms for veto leptons
  TH2D *h_el_SF_veto = NULL;
  TH2D *h_mu_SF_veto = NULL;

  // Final scale factor histograms for tracking
  TH2D *h_el_SF_tracking = NULL;
  TH1D *h_mu_SF_tracking = NULL;

  // Final scale factor histograms for fastim/fullsim for selected leptons
  TH2D *h_el_FS = NULL;
  TH2D *h_mu_FS = NULL;

  // Final scale factor histograms for fastim/fullsim for veto leptons
  TH2D *h_el_veto_FS = NULL;
  TH2D *h_mu_veto_FS = NULL;

  // Final scale factor histograms for lost leptons
  TH2D *h_el_vetoLepEff = NULL;
  TH2D *h_mu_vetoLepEff = NULL;

  float xmin_h_el_SF;
  float xmax_h_el_SF;
  float ymin_h_el_SF;
  float ymax_h_el_SF;
  float xmin_h_el_SF_veto;
  float xmax_h_el_SF_veto;
  float ymin_h_el_SF_veto;
  float ymax_h_el_SF_veto;
  float xmin_h_el_SF_tracking;
  float xmax_h_el_SF_tracking;
  float ymin_h_el_SF_tracking;
  float ymax_h_el_SF_tracking;
  float xmin_h_mu_SF;
  float xmax_h_mu_SF;
  float ymin_h_mu_SF;
  float ymax_h_mu_SF;
  float xmin_h_mu_SF_tracking;
  float xmax_h_mu_SF_tracking;
  float xmin_h_mu_SF_veto;
  float xmax_h_mu_SF_veto;
  float ymin_h_mu_SF_veto;
  float ymax_h_mu_SF_veto;
  float xmin_h_el_FS;
  float xmax_h_el_FS;
  float ymin_h_el_FS;
  float ymax_h_el_FS;
  float xmin_h_el_veto_FS;
  float xmax_h_el_veto_FS;
  float ymin_h_el_veto_FS;
  float ymax_h_el_veto_FS;
  float xmin_h_mu_FS;
  float xmax_h_mu_FS;
  float ymin_h_mu_FS;
  float ymax_h_mu_FS;
  float xmin_h_mu_veto_FS;
  float xmax_h_mu_veto_FS;
  float ymin_h_mu_veto_FS;
  float ymax_h_mu_veto_FS;
  float xmin_h_el_vetoLepEff;
  float xmax_h_el_vetoLepEff;
  float ymin_h_el_vetoLepEff;
  float ymax_h_el_vetoLepEff;
  float xmin_h_mu_vetoLepEff;
  float xmax_h_mu_vetoLepEff;
  float ymin_h_mu_vetoLepEff;
  float ymax_h_mu_vetoLepEff;
  
  eventWeight_lepSF( bool isFastsim );
  ~eventWeight_lepSF();

  void getLepWeight( std::vector< double > recoLep_pt, std::vector< double > recoLep_eta, std::vector< int > recoLep_pdgid, std::vector< bool > recoLep_isSel, std::vector< double > genLostLep_pt, std::vector< double > genLostLep_eta, std::vector< int > genLostLep_pdgid, double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepFSSF, double &weight_lepFSSF_Up, double &weight_lepFSSF_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn );

};

#endif
