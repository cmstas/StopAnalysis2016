#ifndef selectionInfo_H
#define selectionInfo_H

// snt CORE, duplicate data event removal
#include "../../CORE/Tools/dorky/dorky.cc"

// snt CORE, met filters
#include "../../CORE/Tools/badEventFilter.cc"

// stopCORE
#include "analyzerInfo.h"
#include "sampleInfo.h"
#include "stop_1l_babyAnalyzer.h"

// ROOT
#include "TFile.h"
#include "TH1D.h"
#include "TH3D.h"

// C
#include <string>
#include <vector>


//
// NAMESPACE
//
namespace selectionInfo{


  //
  // ENUMS
  //
  enum ID{ k_duplicateRemoval,
	   k_dataFilter,
	   k_trigger_singleLep,
	   k_trigger_MET,
	   k_trigger_singleLep_or_MET,
	   k_trigger_diLep,
	   k_goodVtx,
	   k_ee1_selLep,
	   k_ee0_vetoLep,
	   k_trackVeto,
	   k_tauVeto,
	   k_diLepton,
	   k_diLepton_bulkTTbar,
	   k_oppSignLeptons,
	   k_zMassWindow,
	   k_ge20_diLepMass,
	   k_ge2_jets,
	   k_ee0_bJets,
	   k_ge1_bJets,
	   k_ge50_met,
	   k_ge150_met,
	   k_ge250_met,
	   k_ge150_mt,
	   k_ge0p8_minDPhi
  };
  
  typedef std::vector< selectionInfo::ID > vect_id;

  //
  // UTILITY CLASS FOR INDIVIDUAL CUTS
  //
  class cutUtil{

    public:
      selectionInfo::ID id;

      std::string label;
      std::string title;
      std::string tex;

      cutUtil(){};
      cutUtil( selectionInfo::ID cut );
      ~cutUtil(){};
 
  };
  
  typedef std::vector< selectionInfo::cutUtil > vect_util;

  //
  // UTILITY CLASS FOR SETS OF CUTS
  //
  class selectionUtil{

    public:

      vect_util v_cuts;

      sampleInfo::sampleUtil *sample_info;

      bool addSecondLepToMet;

      eventFilter metFilterTxt; 
      
      TH1D *h_cutflow;
      TH1D *h_cutflow_wgt;
      std::vector< TH1D* > vect_cutflow_nMinus1;

      TH3D *h_cutflow_sig;
      TH3D *h_cutflow_sig_wgt;
      std::vector< TH3D* > vect_cutflow_nMinus1_sig;

      selectionUtil( vect_util selection, sampleInfo::ID sample, bool add2ndLepToMet=false );
      ~selectionUtil();

      void setupCutflowHistos( TFile *f_out );  
      bool passCut( selectionInfo::ID cut );
      bool passSelection();
      void fillCutflowHistos( double wgt );
      void printCutflow(double mStop=800.0, double mLSP=100.0);

  }; // end class def


  //
  // Namespace functions
  //
  vect_util getCutList( analyzerInfo::ID analysis );

  bool sortByCSV (std::pair<int, double>& p1, std::pair<int, double>& p2);
}; // end namespace def

#endif
