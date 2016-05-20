#ifndef recoClassyInfo_H
#define recoClassyInfo_H

// stopCORE
#include "analyzerInfo.h"
#include "stop_1l_babyAnalyzer.h"

// C
#include <string>
#include <utility>
#include <vector>


//
// Namespace
//
namespace recoClassyInfo{


  //
  // ENUMS
  //
  enum ID{ k_incl,
	   k_1lep_el,
	   k_1lep_mu,
	   k_2lep_elel,
	   k_2lep_elmu,
	   k_2lep_mumu,
	   k_2lep_2selLep,
	   k_2lep_1selLep_1vetoLep,
	   k_2lep_1selLep_1isoTrack,
	   k_2lep_1selLep_1pfTau
  };

  
  //
  // CLASS
  //
  class recoClassyUtil{

    public:
      recoClassyInfo::ID id;
      std::string        label;
      std::string        title;
      std::string        tex;
  
      recoClassyUtil( recoClassyInfo::ID recoClassy );
      ~recoClassyUtil(){};

  };


  //
  // TYPEDEFs
  //
  typedef std::vector< recoClassyInfo::ID > vect_id;
  typedef std::pair< recoClassyInfo::ID, bool > pair_id_passBool;
  typedef std::vector< std::pair< recoClassyInfo::ID, bool > > vect_id_passBool;

  
  //
  // Namespace functions
  //
  bool passRecoClassy( recoClassyInfo::ID recoClassy );
  vect_id_passBool passRecoClassyFromList( vect_id recoClassyList );
  vect_id getRecoClassyList( analyzerInfo::ID analysis );

  
}; // end namespace def

#endif
