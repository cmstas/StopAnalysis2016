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
	   k_ee2jets_ge6p4modTop_150to250met,
	   k_ee2jets_ge6p4modTop_250to350met,
	   k_ee2jets_ge6p4modTop_350toInfmet,
	   k_ee2jets_ge6p4modTop_350to450met,
	   k_ee2jets_ge6p4modTop_450toInfmet,
	   k_ge3jets,
	   k_ge3jets_lt200mt2w,
	   k_ge3jets_ge200mt2w,
	   k_ee3jets,
	   k_ee3jets_250to350met,
	   k_ee3jets_350toInfmet,
	   k_ee3jets_lt200mt2w,
	   k_ee3jets_ge200mt2w,
	   k_ee3jets_ge200mt2w_150to250met,
	   k_ee3jets_ge200mt2w_250to350met,
	   k_ee3jets_ge200mt2w_350toInfmet,
	   k_ee3jets_ge200mt2w_350to450met,
	   k_ee3jets_ge200mt2w_450to550met,
	   k_ee3jets_ge200mt2w_550toInfmet,
	   k_ge4jets,
	   k_ge4jets_250toInfmet,
	   k_ge4jets_250to325met,
	   k_ge4jets_325toInfmet,
	   k_ge4jets_250to350met,
	   k_ge4jets_350to450met,
	   k_ge4jets_450toInfmet,
	   k_ge4jets_lt200mt2w,
	   k_ge4jets_lt200mt2w_150to250met,
	   k_ge4jets_lt200mt2w_250to325met,
	   k_ge4jets_lt200mt2w_325toInfmet,
	   k_ge4jets_lt200mt2w_250to350met,
	   k_ge4jets_lt200mt2w_350to450met,
	   k_ge4jets_lt200mt2w_450toInfmet,
	   k_ge4jets_ge200mt2w,
	   k_ge4jets_ge200mt2w_150to250met,
	   k_ge4jets_ge200mt2w_250to350met,
	   k_ge4jets_ge200mt2w_350to450met,
	   k_ge4jets_ge200mt2w_350toInfmet,
	   k_ge4jets_ge200mt2w_450toInfmet,
	   k_ge4jets_ge200mt2w_450to550met,
	   k_ge4jets_ge200mt2w_550to650met,
	   k_ge4jets_ge200mt2w_650toInfmet,
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
	   k_ge2btags_ge250met,
	   k_ge4jets_ge1btags_ge50met,
	   k_ge4jets_ge1btags_ge250met,
	   k_nCats
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

      categoryUtil(){};
      categoryUtil( categoryInfo::ID category );
      ~categoryUtil(){};
  };

  
  //
  // TYPEDEFs
  //
  typedef std::vector< std::pair< categoryInfo::ID, bool > > vect_id_passBool;
  typedef std::pair< categoryInfo::ID, bool > pair_id_passBool;
  typedef std::vector< categoryInfo::ID > vect_id;

  typedef std::vector< std::pair< categoryInfo::categoryUtil, bool > > vect_util_passBool;
  typedef std::pair< categoryInfo::categoryUtil, bool > pair_util_passBool;
  typedef std::vector< categoryInfo::categoryUtil > vect_util;


  //
  // NAMESPACE FUNCTIONS
  //
  bool passCategory( categoryInfo::ID category, bool add2ndLepToMet=false );
  vect_util_passBool passCategoriesFromList( vect_util categoryList, bool onlyReturnTrue, bool add2ndLepToMet=false );
  vect_util getCategoryList( analyzerInfo::ID analysis );

  bool sortByCSV (std::pair<int, double>& p1, std::pair<int, double>& p2);
}; // end class def


#endif
