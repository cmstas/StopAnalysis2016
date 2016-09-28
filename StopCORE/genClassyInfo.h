#ifndef genClassyInfo_H
#define genClassyInfo_H

// stopCORE
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
  // TYPEDEFs
  //
  typedef std::vector< genClassyInfo::ID > vect_id;


  // 
  // Utility Class
  //
  class Util{

  public:
      genClassyInfo::ID id;
      std::string       label;
      std::string       title;
      std::string       tex;

      // Creation/Annihilation Operators
      ~Util(){};
      Util( genClassyInfo::ID genClassy );
      
      // Pointer to classifcation function
      bool (*eval_GenClassy)();
   
  }; // end class definition

  
  //
  // TYPEDEFs
  //
  typedef std::vector< genClassyInfo::Util > vect_util;


  //
  // Namespace functions
  //
  bool eval_incl();
  bool eval_ee1lep();
  bool eval_ee1lep_fromW();
  bool eval_ee1lep_fromTop();
  bool eval_ge2lep();
  bool eval_ZtoNuNu();
  
}; // end namespace


//////////////////////////////////////////////////////////////////////


#endif
