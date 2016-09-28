#include "genClassyInfo.h"

//////////////////////////////////////////////////////////////////////

genClassyInfo::Util::Util( genClassyInfo::ID genClassy ){

  switch( genClassy ){

  case( k_ee1lep):
    id    = genClassy;
    label = "ee1lep";
    title = "1 lepton";
    tex   = "$1$~lepton";
    eval_GenClassy = genClassyInfo::eval_ee1lep;
    break;

  case( k_ee1lep_fromW):
    id    = genClassy;
    label = "ee1lep_fromW";
    title = "1 lepton, from W";
    tex   = "$1$~lepton,~from~$W$";
    eval_GenClassy = genClassyInfo::eval_ee1lep_fromW;
    break;

  case( k_ee1lep_fromTop):
    id    = genClassy;
    label = "ee1lep_fromTop";
    title = "1 lepton, from Top";
    tex   = "$1$~lepton,~from~$t$";
    eval_GenClassy = genClassyInfo::eval_ee1lep_fromTop;
    break;

  case( k_ge2lep):
    id    = genClassy;
    label = "ge2lep";
    title = ">=2 leptons";
    tex   = "$\\ge2$~leptons";
    eval_GenClassy = genClassyInfo::eval_ge2lep;
    break;

  case( k_ZtoNuNu):
    id    = genClassy;
    label = "ZtoNuNu";
    title = "Z->NuNu";
    tex   = "$Z\\rightarrow\\nu\\nu$";
    eval_GenClassy = genClassyInfo::eval_ZtoNuNu;
    break;

  case( k_incl):
    id    = genClassy;
    label = "incl";
    title = "Inclusive";
    tex   = "Inclusve";
    eval_GenClassy = genClassyInfo::eval_incl;
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

bool genClassyInfo::eval_incl(){ return true; }

//////////////////////////////////////////////////////////////////////

bool genClassyInfo::eval_ee1lep(){ 

  bool result = false;

  if( babyAnalyzer.is1lep() && !babyAnalyzer.isZtoNuNu() ){
    result = true;
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool genClassyInfo::eval_ee1lep_fromW(){ 

  bool result = false;

  if( babyAnalyzer.is1lepFromW() && !babyAnalyzer.isZtoNuNu() ){
    result = true;
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool genClassyInfo::eval_ee1lep_fromTop(){ 

  bool result = false;

  if( babyAnalyzer.is1lepFromTop() && !babyAnalyzer.isZtoNuNu() ){
    result = true;
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool genClassyInfo::eval_ge2lep(){ 

  bool result = false;

  if( babyAnalyzer.is2lep() && !babyAnalyzer.isZtoNuNu() ){
    result = true;
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool genClassyInfo::eval_ZtoNuNu(){ 

  bool result = false;

  if( babyAnalyzer.isZtoNuNu() ){
    result = true;
  }

  return result;
}


//////////////////////////////////////////////////////////////////////
