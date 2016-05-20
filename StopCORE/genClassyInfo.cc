#include "genClassyInfo.h"

//////////////////////////////////////////////////////////////////////

genClassyInfo::genClassyUtil::genClassyUtil( genClassyInfo::ID genClassy ){

  switch( genClassy ){

  case( k_ee1lep):
    id    = genClassy;
    label = "ee1lep";
    title = "==1 lepton";
    tex   = "$==1$~lepton";
    break;

  case( k_ee1lep_fromW):
    id    = genClassy;
    label = "ee1lep_fromW";
    title = "==1 lepton, from W";
    tex   = "$==1$~lepton,~from~$W$";
    break;

  case( k_ee1lep_fromTop):
    id    = genClassy;
    label = "ee1lep_fromTop";
    title = "==1 lepton, from Top";
    tex   = "$==1$~lepton,~from~$t$";
    break;

  case( k_ge2lep):
    id    = genClassy;
    label = "ge2lep";
    title = ">=2 leptons";
    tex   = "$\\ge2$~leptons";
    break;

  case( k_ZtoNuNu):
    id    = genClassy;
    label = "ZtoNuNu";
    title = "Z->NuNu";
    tex   = "$Z\\rightarrow\\nu\\nu$";
    break;

  case( k_incl):
    id    = genClassy;
    label = "incl";
    title = "Inclusive";
    tex   = "Inclusve";
    break;

  default:
    std::cout << "Could not find cut info from cut enum provided!" << std::endl;
    id    = genClassy;
    label = "NO GEN CLASSY INFO FOUND FROM ENUM PROVIDED";
    title = "NO GEN CLASSY INFO FOUND FROM ENUM PROVIDED";
    tex   = "NO GEN CLASSY INFO FOUND FROM ENUM PROVIDED";
    break;
    
  };

  
}


//////////////////////////////////////////////////////////////////////

bool genClassyInfo::passGenClassy( genClassyInfo::ID genClassy ){

  bool result = false;

  switch( genClassy ){

  case( k_incl ):
    result = true;
    break;

  case( k_ee1lep ):
    if( babyAnalyzer.is1lep() ) result = true;
    break;

  case( k_ee1lep_fromW ):
    if( babyAnalyzer.is1lepFromW() ) result = true;
    break;

  case( k_ee1lep_fromTop ):
    if( babyAnalyzer.is1lepFromTop() ) result = true;
    break;

  case( k_ge2lep ):
    if( babyAnalyzer.is2lep() ) result = true;
    break;

  case( k_ZtoNuNu ):
    if( babyAnalyzer.isZtoNuNu() ) result = true;
    break;

  default:
    std::cout << "Could not find gen classification info from genClassy enum provided!" << std::endl;
    break;
    
  };

  return result;

}

//////////////////////////////////////////////////////////////////////

genClassyInfo::vect_id_passBool genClassyInfo::passGenClassyFromList( vect_id genClassyList ){

  vect_id_passBool result;

  for(int iClassy=0; iClassy<(int)genClassyList.size(); iClassy++){

    pair_id_passBool temp_result;
    temp_result.first  = genClassyList[iClassy];
    temp_result.second = passGenClassy( temp_result.first ) ? true : false;
    result.push_back( temp_result );

  }

  return result;
}

//////////////////////////////////////////////////////////////////////

genClassyInfo::vect_id genClassyInfo::getGenClassyList( analyzerInfo::ID analysis ){

  vect_id result;

  switch( analysis ){

  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( genClassyInfo::k_incl );
    break;

  case( analyzerInfo::k_SR ):
  case( analyzerInfo::k_CR0b ):
  case( analyzerInfo::k_CR1l_bulkWJets ):
  case( analyzerInfo::k_CR2l ):
  case( analyzerInfo::k_CR2l_bulkTTbar ):
  default:
    result.push_back( genClassyInfo::k_incl );
    result.push_back( genClassyInfo::k_ee1lep );
    result.push_back( genClassyInfo::k_ee1lep_fromW );
    result.push_back( genClassyInfo::k_ee1lep_fromTop );
    result.push_back( genClassyInfo::k_ge2lep );
    result.push_back( genClassyInfo::k_ZtoNuNu );
    break;

  }; // end analysis switch

  return result;

}

//////////////////////////////////////////////////////////////////////
