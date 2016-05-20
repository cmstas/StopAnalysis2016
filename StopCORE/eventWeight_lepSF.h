#ifndef eventWeight_lepSF_H
#define eventWeight_lepSF_H

// ROOT
#include "Riostream.h"
#include "TFile.h"
#include "TH2.h"

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

  // Lepton SF files
  TFile *f_el_SF;
  TFile *f_mu_SF_id;
  TFile *f_mu_SF_iso;
  TFile *f_mu_SF_veto_id;
  TFile *f_mu_SF_veto_iso;

  // Lepton Efficiency file for vetoLep
  TFile *f_vetoLep_eff;

  // Fastsim files
  TFile *f_el_FS_ID;
  TFile *f_el_FS_Iso;
  TFile *f_mu_FS_ID;
  TFile *f_mu_FS_Iso;

  // SF Histograms
  TH2D *h_el_SF;
  TH2D *h_mu_SF;

  TH2D *h_el_SF_veto;
  TH2D *h_mu_SF_veto;

  TH2D *h_el_vetoLepEff;
  TH2D *h_mu_vetoLepEff;

  TH2D *h_el_FS;
  TH2D *h_mu_FS;

  eventWeight_lepSF( bool isFastsim );
  ~eventWeight_lepSF();

  void getLepWeight( std::vector< double > recoLep_pt, std::vector< double > recoLep_eta, std::vector< int > recoLep_pdgid, std::vector< bool > recoLep_isSel, std::vector< double > genLostLep_pt, std::vector< double > genLostLep_eta, std::vector< int > genLostLep_pdgid, double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepFSSF, double &weight_lepFSSF_Up, double &weight_lepFSSF_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn );

};

#endif
