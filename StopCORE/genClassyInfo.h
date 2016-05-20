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
	   k_ZtoNuNu
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
      
      genClassyUtil( genClassyInfo::ID genClassy );
      ~genClassyUtil(){};
   
  }; // end class definition
  

  //
  // TYPEDEFs
  //
  typedef std::vector< genClassyInfo::ID > vect_id;
  typedef std::pair< genClassyInfo::ID, bool > pair_id_passBool;
  typedef std::vector< std::pair< genClassyInfo::ID, bool > > vect_id_passBool;


  //
  // Namespace functions
  //
  bool passGenClassy( genClassyInfo::ID genClassy );
  vect_id_passBool passGenClassyFromList( vect_id genClassyList );
  vect_id getGenClassyList( analyzerInfo::ID analysis );


}; // end namespace



#endif
