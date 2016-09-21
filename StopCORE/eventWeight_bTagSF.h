#ifndef eventWeight_bTagSF_H
#define eventWeight_bTagSF_H

// SNT CORE
#include "../../CORE/Tools/btagsf/BTagCalibrationStandalone.h"

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
  TFile* f_btag_eff;
  TFile* f_btag_eff_fastsim;
  
  TH2D* h_btag_eff_b;
  TH2D* h_btag_eff_c;
  TH2D* h_btag_eff_udsg;
    
  BTagCalibration* calib;
  BTagCalibrationReader* reader_heavy;
  BTagCalibrationReader* reader_heavy_UP;
  BTagCalibrationReader* reader_heavy_DN;
  BTagCalibrationReader* reader_light;
  BTagCalibrationReader* reader_light_UP;
  BTagCalibrationReader* reader_light_DN;
  
  // bTag FastSim SF machinery
  BTagCalibration* calib_fastsim;
  BTagCalibrationReader* reader_fastsim;
  BTagCalibrationReader* reader_fastsim_UP;
  BTagCalibrationReader* reader_fastsim_DN;
  

  eventWeight_bTagSF( bool isFastsim );
  ~eventWeight_bTagSF();

  void getBTagWeight( std::vector< double > jet_pt, std::vector< double > jet_eta, std::vector< int > jet_flavour, std::vector< bool > jet_passCSV, double &weight_btagsf, double &weight_btagsf_heavy_UP, double &weight_btagsf_heavy_DN, double &weight_btagsf_light_UP, double &weight_btagsf_light_DN );
  
}; // end class def

#endif
