#ifndef categoryInfo_H
#define categoryInfo_H

// stopCORE
#include "analyzerInfo.h"
#include "stop_1l_babyAnalyzer.h"

// C
#include <string>
#include <utility>
#include <vector>


//
// NAMESPACE
//
namespace categoryInfo{

  //
  // ENUMS
  //
  enum ID{ k_incl,
	   k_ge2jets,
	   k_ge2jets_ge6p4modTop,
	   k_ge2jets_lt200mt2w,
	   k_ge2jets_ge200mt2w,
	   k_ee2jets,
	   k_ee2jets_250to350met,
	   k_ee2jets_350toInfmet,
	   k_ee2jets_ge6p4modTop,
	   k_ee2jets_ge6p4modTop_250to350met,
	   k_ee2jets_ge6p4modTop_350toInfmet,
	   k_ge3jets,
	   k_ge3jets_lt200mt2w,
	   k_ge3jets_ge200mt2w,
	   k_ee3jets,
	   k_ee3jets_250to350met,
	   k_ee3jets_350toInfmet,
	   k_ee3jets_lt200mt2w,
	   k_ee3jets_ge200mt2w,
	   k_ee3jets_ge200mt2w_250to350met,
	   k_ee3jets_ge200mt2w_350toInfmet,
	   k_ge4jets,
	   k_ge4jets_250to325met,
	   k_ge4jets_325toInfmet,
	   k_ge4jets_250to350met,
	   k_ge4jets_350to450met,
	   k_ge4jets_450toInfmet,
	   k_ge4jets_lt200mt2w,
	   k_ge4jets_lt200mt2w_250to325met,
	   k_ge4jets_lt200mt2w_325toInfmet,
	   k_ge4jets_ge200mt2w,
	   k_ge4jets_ge200mt2w_250to350met,
	   k_ge4jets_ge200mt2w_350to450met,
	   k_ge4jets_ge200mt2w_450toInfmet,
	   k_ge5jets,
	   k_ge1btags_ge50met,
	   k_ge1btags_ge100met,
	   k_ge1btags_ge150met,
	   k_ge1btags_ge200met,
	   k_ge1btags_ge250met,
	   k_ge2btags_ge50met,
	   k_ge2btags_ge100met,
	   k_ge2btags_ge150met,
	   k_ge2btags_ge200met,
	   k_ge2btags_ge250met
  };


  //
  // CLASS
  //
  class categoryUtil{

    public:
      categoryInfo::ID id;
      std::string     label;
      std::string     title;
      std::string     tex;
      
      categoryUtil( categoryInfo::ID category );
      ~categoryUtil(){};
  };

  
  //
  // TYPEDEFs
  //
  typedef std::vector< std::pair< categoryInfo::ID, bool > > vect_id_passBool;
  typedef std::pair< categoryInfo::ID, bool > pair_id_passBool;
  typedef std::vector< categoryInfo::ID > vect_id;


  //
  // NAMESPACE FUNCTIONS
  //
  bool passCategory( categoryInfo::ID category );
  vect_id_passBool passCategoriesFromList( vect_id categoryList );
  vect_id getCategoryList( analyzerInfo::ID analysis );

}; // end class def


#endif
