#ifndef eventWeight_bTagSF_H
#define eventWeight_bTagSF_H

// SNT CORE
//#ifndef __CINT__
//#include "../../CORE/Tools/btagsf/BTagCalibrationStandalone.h"
#include "btagsf/BTagCalibrationStandalone.h"
//#include "BTagCalibrationStandalone.h"
//#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
//#endif /* __CINT __ */

// ROOT
#include "TFile.h"
#include "TH2.h"

// C
#include <string>
#include <vector>


//
// CLASS
//
class eventWeight_bTagSF{

 public:

  // Sample info 
  bool sampleIsFastsim;

  // bTag SF machinery
  float BTAG_LSE;
  float BTAG_MED;
  float BTAG_TGT;
    
  BTagCalibration* calib;
  BTagCalibrationReader* reader_heavy;
  BTagCalibrationReader* reader_heavy_UP;
  BTagCalibrationReader* reader_heavy_DN;
  BTagCalibrationReader* reader_light;
  BTagCalibrationReader* reader_light_UP;
  BTagCalibrationReader* reader_light_DN;
  BTagCalibrationReader* reader_loose_heavy;
  BTagCalibrationReader* reader_loose_heavy_UP;
  BTagCalibrationReader* reader_loose_heavy_DN;
  BTagCalibrationReader* reader_loose_light;
  BTagCalibrationReader* reader_loose_light_UP;
  BTagCalibrationReader* reader_loose_light_DN;
  BTagCalibrationReader* reader_tight_heavy;
  BTagCalibrationReader* reader_tight_heavy_UP;
  BTagCalibrationReader* reader_tight_heavy_DN;
  BTagCalibrationReader* reader_tight_light;
  BTagCalibrationReader* reader_tight_light_UP;
  BTagCalibrationReader* reader_tight_light_DN;
  BTagCalibration* calib_fastsim;
  BTagCalibrationReader* reader_fastsim;
  BTagCalibrationReader* reader_fastsim_UP;
  BTagCalibrationReader* reader_fastsim_DN;
  BTagCalibrationReader* reader_tight_fastsim;
  BTagCalibrationReader* reader_tight_fastsim_UP;
  BTagCalibrationReader* reader_tight_fastsim_DN;
  BTagCalibrationReader* reader_loose_fastsim;
  BTagCalibrationReader* reader_loose_fastsim_UP;
  BTagCalibrationReader* reader_loose_fastsim_DN;
  TFile *feff;
  TH2D* h_btag_eff_b;
  TH2D* h_btag_eff_c;
  TH2D* h_btag_eff_udsg;
  TH2D* h_loose_btag_eff_b;
  TH2D* h_loose_btag_eff_c;
  TH2D* h_loose_btag_eff_udsg;
  TH2D* h_tight_btag_eff_b;
  TH2D* h_tight_btag_eff_c;
  TH2D* h_tight_btag_eff_udsg;
  
  
  eventWeight_bTagSF( bool isFastsim );
  ~eventWeight_bTagSF();

  void getBTagWeight( int WP, std::vector< double > jet_pt, std::vector< double > jet_eta, std::vector< double > jet_CSV, std::vector< int > jet_flavour, double &weight_btagsf, double &weight_btagsf_heavy_UP, double &weight_btagsf_heavy_DN, double &weight_btagsf_light_UP, double &weight_btagsf_light_DN, double &weight_btagsf_fastsim_UP, double &weight_btagsf_fastsim_DN );
  
}; // end class def

#endif
