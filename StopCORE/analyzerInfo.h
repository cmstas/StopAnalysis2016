#ifndef analyzerInfo_H
#define analyzerInfo_H

// C
#include <string>
#include <vector>
#include <utility>

//
// Namespace
//
namespace analyzerInfo{

  //
  // ENUM
  //
  enum ID{ k_SR,
	   k_CR0b,
	   k_CR1l_bulkWJets,
	   k_CR2l,
	   k_CR2l_bulkTTbar,
	   k_CRGammaJets,
	   k_nAnalyzer
  };


  //
  // UTILITY CLASS
  //
  class analyzerUtil{

    public:
    
      analyzerInfo::ID id;
      std::string      label;
      std::string      title;
      std::string      tex;

      analyzerUtil( analyzerInfo::ID analysis );
      ~analyzerUtil(){};
    
  };
	   
	   

}; // end namespace definition

#endif
