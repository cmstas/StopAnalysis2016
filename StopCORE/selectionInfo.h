#ifndef selectionInfo_H
#define selectionInfo_H

// snt CORE, duplicate data event removal
#include "../../CORE/Tools/dorky/dorky.cc"

// snt CORE, met filters
#include "../../CORE/Tools/badEventFilter.cc"

// stopCORE
#include "analyzerInfo.h"
#include "stop_1l_babyAnalyzer.h"

// ROOT
#include "TFile.h"
#include "TH1D.h"

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

      cutUtil( selectionInfo::ID cut );
      ~cutUtil(){};
 
  };
  

  //
  // UTILITY CLASS FOR SETS OF CUTS
  //
  class selectionUtil{

    public:

      vect_id v_cuts;

      bool sample_is_data;

      eventFilter metFilterTxt; 
      
      TH1D *h_cutflow;
      TH1D *h_cutflow_wgt;
      std::vector< TH1D* > vect_cutflow_nMinus1;

      selectionUtil( vect_id selection, bool isData );
      ~selectionUtil();

      void setupCutflowHistos( TFile *f_out );  
      bool passCut( selectionInfo::ID cut );
      bool passSelection();
      void fillCutflowHistos( double wgt );
      void printCutflow();

  }; // end class def


  //
  // Namespace functions
  //
  vect_id getCutList( analyzerInfo::ID analysis );

    
}; // end namespace def

#endif
