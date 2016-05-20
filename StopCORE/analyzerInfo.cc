#include "analyzerInfo.h"

// ROOT
#include "Riostream.h"

// C
#include <vector>

//////////////////////////////////////////////////////////////////////

analyzerInfo::analyzerUtil::analyzerUtil( analyzerInfo::ID analysis ){

  switch( analysis ){

  case( k_SR ):
    label = "SR";
    title = "Signal Region";
    tex   = "Signal~Region";
    break;

  case( k_CR0b ):
    label = "CR0b";
    title = "Control Region, 0 bTags";
    tex   = "Control~Region,~0~bTags";
    break;

  case( k_CR1l_bulkWJets ):
    label = "CR1l_bulkWJets";
    title = "Control Region, 1 lep, bulk WJets";
    tex   = "Control~Region,~1~lep,~bulk~WJets";
    break;

  case( k_CR2l ):
    label = "CR2l";
    title = "Control Region, lost lepton";
    tex   = "Control~Region,~lost~lepton";
    break;

  case( k_CR2l_bulkTTbar ):
    label = "CR2l_bulkTTbar";
    title = "Control Region, 2 lep, bulk ttbar";
    tex   = "Control~Region,~2~lep,~bulk~$t\\bar{t}$";
    break;

  case( k_CRGammaJets ):
    label = "CRGammaJets";
    title = "Control Region, Gamma+Jets";
    tex   = "Control~Region,~$\\gamma$+Jets";
    break;

  default:
    std::cout << "Could not find analyzer info from analyzer enum provided!" << std::endl;
    label = "NO ANALYZER INFO FOUND FROM ENUM PROVIDED";
    title = "NO ANALYZER INFO FOUND FROM ENUM PROVIDED";
    tex   = "NO ANALYZER INFO FOUND FROM ENUM PROVIDED";
    break;
  

  };

}

//////////////////////////////////////////////////////////////////////
