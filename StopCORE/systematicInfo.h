#ifndef systematicInfo_H
#define systematicInfo_H

// stopCORE
#include "analyzerInfo.h"
#include "stop_1l_babyAnalyzer.h"
#include "eventWeightInfo.h"

// C
#include <string>
#include <utility>
#include <vector>


//
// NAMESPACE
//
namespace systematicInfo{


  //
  // ENUMS
  //
  enum ID{ k_nominal,
	   k_JESUp,
	   k_JESDown,
	   k_bTagEffHFUp,
	   k_bTagEffHFDown,
	   k_bTagEffLFUp,
	   k_bTagEffLFDown,
	   k_lepSFUp,
	   k_lepSFDown,
	   k_lepFSSFUp,
	   k_lepFSSFDown,
	   k_topPtSFUp,
	   k_topPtSFDown,
	   k_metResUp,
	   k_metResDown,
	   k_nJetsSFK3Up,
	   k_nJetsSFK3Down,
	   k_nJetsSFK4Up,
	   k_nJetsSFK4Down,
	   k_diNuPtSF_Up,
	   k_diNuPtSF_Down,
	   k_nuPtSF_Up,
	   k_nuPtSF_Down,
	   k_WwidthSF_Up,
	   k_WwidthSF_Down,
	   k_hfXsec_Up,
	   k_hfXsec_Down,
	   k_pdfUp,
	   k_pdfDown,
	   k_alphasUp,
	   k_alphasDown,
	   k_q2Up,
	   k_q2Down,
	   k_lumiUp,
	   k_lumiDown,
	   k_ISRUp,
	   k_ISRDown,
	   k_xsecUp,
	   k_xsecDown,
	   k_nSys
  };


  //
  // TYPEDEFs
  //
  typedef std::vector< systematicInfo::ID > vect_id;
  typedef std::pair< systematicInfo::ID, double > pair_id_wgt;
  typedef std::vector< std::pair< systematicInfo::ID, double > > vect_id_wgt;


  //
  // CLASS
  //
  class systematicUtil{

    public:
      systematicInfo::ID id;
      std::string        label;
      std::string        title;
      std::string        tex;
      bool               hasOwnBabies;

      systematicUtil(){};
      systematicUtil( systematicInfo::ID systematic );
      ~systematicUtil(){};
  };


  //
  // TYPEDEFs
  //
  typedef std::vector< systematicInfo::systematicUtil > vect_util;
  typedef std::pair< systematicInfo::systematicUtil, double > pair_util_wgt;
  typedef std::vector< std::pair< systematicInfo::systematicUtil, double > > vect_util_wgt;

  //
  // Namespace functions
  //
  double getSystematicWeight( systematicInfo::ID systematic, eventWeightInfo *evt_wgt );
  
  vect_util_wgt getSystematicWeightsFromList( vect_util systematicList, eventWeightInfo *evt_wgt );
  
  vect_util getSystematicList( analyzerInfo::ID analysis, bool sample_isFastsim, bool sample_isSignal );
  
  vect_util getSystematicList_all();
  vect_util getSystematicList_forLimit_lostLepton();
  vect_util getSystematicList_forLimit_oneLeptonNotFromTop();
  vect_util getSystematicList_forLimit_oneLeptonFromTop();
  vect_util getSystematicList_forLimit_ZtoNuNu();
  vect_util getSystematicList_forLimit_sig();
    
}; // end class def


#endif
