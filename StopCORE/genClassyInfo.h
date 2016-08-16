#ifndef genClassyInfo_H
#define genClassyInfo_H

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
namespace genClassyInfo{

  //
  // ENUMS
  //
  enum ID{ k_incl,
           k_ee1lep,
	   k_ee1lep_fromW,
	   k_ee1lep_fromTop,
	   k_ge2lep,
	   k_ZtoNuNu,
	   k_nGenClassy
  };


  // 
  // Utility Class
  //
  class genClassyUtil{

  public:
      genClassyInfo::ID id;
      std::string       label;
      std::string       title;
      std::string       tex;
      
      genClassyUtil(){};
      genClassyUtil( genClassyInfo::ID genClassy );
      ~genClassyUtil(){};
   
  }; // end class definition
  

  //
  // TYPEDEFs
  //
  typedef std::vector< genClassyInfo::ID > vect_id;
  typedef std::pair< genClassyInfo::ID, bool > pair_id_passBool;
  typedef std::vector< std::pair< genClassyInfo::ID, bool > > vect_id_passBool;

  typedef std::vector< genClassyInfo::genClassyUtil > vect_util;
  typedef std::pair< genClassyInfo::genClassyUtil, bool > pair_util_passBool;
  typedef std::vector< std::pair< genClassyInfo::genClassyUtil, bool > > vect_util_passBool;


  //
  // Namespace functions
  //
  bool passGenClassy( genClassyInfo::ID genClassy );
  vect_util_passBool passGenClassyFromList( vect_util genClassyList, bool returnOnlyTrue );
  vect_util getGenClassyList( analyzerInfo::ID analysis );


}; // end namespace



#endif
