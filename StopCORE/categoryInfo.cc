#include "categoryInfo.h"

//////////////////////////////////////////////////////////////////////

categoryInfo::categoryUtil::categoryUtil( categoryInfo::ID category ){

  switch( category ){

  case( k_incl ):
    id    = category;
    label = "incl";
    title = "Post-Selection";
    tex   = "Post~Selection";
    break;  

  case( k_ge2jets ):
    id    = category;
    label = "ge2jets";
    title = ">=2 jets";
    tex   = "$\\ge2$~jets";
    break;

  case( k_ge2jets_ge6p4modTop ):
    id    = category;
    label = "ge2jets_ge6p4modTop";
    title = ">=2 jets, modTopness>=6.4";
    tex   = "$\\ge2$~jets,~modTopness$\\ge6.4$";
    break;  

  case( k_ge2jets_lt200mt2w ):
    id    = category;
    label = "ge2jets_lt200mt2w";
    title = ">=2 jets, MT2W<200";
    tex   = "$\\ge2$~jets,~MT2W$<200$";
    break;

  case( k_ge2jets_ge200mt2w ):
    id    = category;
    label = "ge2jets_ge200mt2w";
    title = ">=2 jets, MT2W>=200";
    tex   = "$\\ge2$~jets,~MT2W$\\ge200$";
    break;  

  case( k_ee2jets ):
    id    = category;
    label = "ee2jets";
    title = "2 jets";
    tex   = "$2$~jets";
    break;  

  case( k_ee2jets_250to350met ):
    id    = category;
    label = "ee2jets_250to350met";
    title = "2 jets, 250<MET<350";
    tex   = "$2$~jets,~$250<MET<350$";
    break;

  case( k_ee2jets_350toInfmet ):
    id    = category;
    label = "ee2jets_350toInfmet";
    title = "2 jets, MET>350";
    tex   = "$2$~jets,~$MET>350$";
    break;

  case( k_ee2jets_ge6p4modTop ):
    id    = category;
    label = "ee2jets_ge6p4modTop";
    title = "2 jets, modTopness>=6.4";
    tex   = "$2$~jets,~modTopness$\\ge6.4$";
    break;

  case( k_ee2jets_ge6p4modTop_250to350met ):
    id    = category;
    label = "ee2jets_ge6p4modTop_250to350met";
    title = "2 jets, modTopness>=6.4, 250<MET<350";
    tex   = "$2$~jets,~modTopness$\\ge6.4$,~$250<MET<350$";
    break;

  case( k_ee2jets_ge6p4modTop_350toInfmet ):
    id    = category;
    label = "ee2jets_ge6p4modTop_350toInfmet";
    title = "2 jets, modTopness>=6.4, MET>350";
    tex   = "$2$~jets,~modTopness$\\ge6.4$,~$MET>350$";
    break;

  case( k_ge3jets ):
    id    = category;
    label = "ge3jets";
    title = ">=3 jets";
    tex   = "$\\ge3$~jets";
    break;

  case( k_ge3jets_lt200mt2w ):
    id    = category;
    label = "ge3jets_lt200mt2w";
    title = ">=3 jets, MT2W<200";
    tex   = "$\\ge3$~jets,~MT2W$<200$";
    break;

  case( k_ge3jets_ge200mt2w ):
    id    = category;
    label = "ge3jets_ge200mt2w";
    title = ">=3 jets, MT2W>=200";
    tex   = "$\\ge3$~jets,~MT2W$\\ge200$";
    break;  

  case( k_ee3jets ):
    id    = category;
    label = "ee3jets";
    title = "3 jets";
    tex   = "$3$~jets";
    break;

  case( k_ee3jets_250to350met ):
    id    = category;
    label = "ee3jets_250to350met";
    title = "3 jets, 250<MET<350";
    tex   = "$3$~jets,~$250<MET<350$";
    break;

  case( k_ee3jets_350toInfmet ):
    id    = category;
    label = "ee3jets_350toInfmet";
    title = "3 jets, MET>350";
    tex   = "$3$~jets,~$MET>350$";
    break;

  case( k_ee3jets_lt200mt2w ):
    id    = category;
    label = "ee3jets_lt200mt2w";
    title = "3 jets, MT2W<200";
    tex   = "$3$~jets,~MT2W$<200$";
    break;

  case( k_ee3jets_ge200mt2w ):
    id    = category;
    label = "ee3jets_ge200mt2w";
    title = "3 jets, MT2W>=200";
    tex   = "$3$~jets,~MT2W$\\ge200$";
    break;

  case( k_ee3jets_ge200mt2w_250to350met ):
    id    = category;
    label = "ee3jets_ge200mt2w_250to350met";
    title = "3 jets, MT2W>=200, 250<MET<350";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$250<MET<350$";
    break;

  case( k_ee3jets_ge200mt2w_350toInfmet ):
    id    = category;
    label = "ee3jets_ge200mt2w_350toInfmet";
    title = "3 jets, MT2W>=200, MET>350";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$MET>350$";
    break;

  case( k_ge4jets ):
    id    = category;
    label = "ge4jets";
    title = ">=4 jets";
    tex   = "$\\ge4$~jets";
    break;
    
  case( k_ge4jets_250to325met ):
    id    = category;
    label = "ge4jets_250to325met";
    title = ">=4 jets, 250<MET<325";
    tex   = "$\\ge4$~jets,~$250<MET<325$";
    break;

  case( k_ge4jets_325toInfmet ):
    id    = category;
    label = "ge4jets_325toInfmet";
    title = ">=4 jets, MET>325";
    tex   = "$\\ge4$~jets,~$MET>325$";
    break;

  case( k_ge4jets_250to350met ):
    id    = category;
    label = "ge4jets_250to350met";
    title = ">=4 jets, 250<MET<350";
    tex   = "$\\ge4$~jets,~$250<MET<350$";
    break;

  case( k_ge4jets_350to450met ):
    id    = category;
    label = "ge4jets_350to450met";
    title = ">=4 jets, 350<MET<450";
    tex   = "$\\ge4$~jets,~$350<MET<450$";
    break;

  case( k_ge4jets_450toInfmet ):
    id    = category;
    label = "ge4jets_450toInfmet";
    title = ">=4 jets, MET>450";
    tex   = "$\\ge4$~jets,~$MET>450$";
    break;

  case( k_ge4jets_lt200mt2w ):
    id    = category;
    label = "ge4jets_lt200mt2w";
    title = ">=4 jets, MT2W<200";
    tex   = "$\\ge4$~jets,~MT2W$<200$";
    break;

  case( k_ge4jets_lt200mt2w_250to325met ):
    id    = category;
    label = "ge4jets_lt200mt2w_250to325met";
    title = ">=4 jets, MT2W<200, 250<MET<325";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$250<MET<325$";
    break;

  case( k_ge4jets_lt200mt2w_325toInfmet ):
    id    = category;
    label = "ge4jets_lt200mt2w_325toInfmet";
    title = ">=4 jets, MT2W<200, MET>325";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$MET>325$";
    break;

  case( k_ge4jets_ge200mt2w ):
    id    = category;
    label = "ge4jets_ge200mt2w";
    title = ">=4 jets, MT2W>=200";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$";
    break;  

  case( k_ge4jets_ge200mt2w_250to350met ):
    id    = category;
    label = "ge4jets_ge200mt2w_250to350met";
    title = ">=4 jets, MT2W>=200, 250<MET<350";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$250<MET<350$";
    break;

  case( k_ge4jets_ge200mt2w_350to450met ):
    id    = category;
    label = "ge4jets_ge200mt2w_350to450met";
    title = ">=4 jets, MT2W>=200, 350<MET<450";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$350<MET<450$";
    break;

  case( k_ge4jets_ge200mt2w_450toInfmet ):
    id    = category;
    label = "ge4jets_ge200mt2w_450toInfmet";
    title = ">=4 jets, MT2W>=200, MET>450";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$MET>450$";
    break;

  case( k_ge5jets ):
    id    = category;
    label = "ge5jets";
    title = ">=5 jets";
    tex   = "$\\ge5$~jets";
    break;

  case( k_ge1btags_ge50met ):
    id    = category;
    label = "ge1btags_ge50met";
    title = ">=1 b-tagged jets, MET>50";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>50$";
    break;

  case( k_ge1btags_ge100met ):
    id    = category;
    label = "ge1btags_ge100met";
    title = ">=1 b-tagged jets, MET>100";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>100$";
    break;

  case( k_ge1btags_ge150met ):
    id    = category;
    label = "ge1btags_ge150met";
    title = ">=1 b-tagged jets, MET>150";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>150$";
    break;
    
  case( k_ge1btags_ge200met ):
    id    = category;
    label = "ge1btags_ge200met";
    title = ">=1 b-tagged jets, MET>200";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>200$";
    break;

  case( k_ge1btags_ge250met ):
    id    = category;
    label = "ge1btags_ge250met";
    title = ">=1 b-tagged jets, MET>250";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>250$";
    break;

  case( k_ge2btags_ge50met ):
    id    = category;
    label = "ge2btags_ge50met";
    title = ">=2 b-tagged jets, MET>50";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>50$";
    break;

  case( k_ge2btags_ge100met ):
    id    = category;
    label = "ge2btags_ge100met";
    title = ">=2 b-tagged jets, MET>100";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>100$";
    break;

  case( k_ge2btags_ge150met ):
    id    = category;
    label = "ge2btags_ge150met";
    title = ">=2 b-tagged jets, MET>150";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>150$";
    break;
    
  case( k_ge2btags_ge200met ):
    id    = category;
    label = "ge2btags_ge200met";
    title = ">=2 b-tagged jets, MET>200";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>200$";
    break;

  case( k_ge2btags_ge250met ):
    id    = category;
    label = "ge2btags_ge250met";
    title = ">=2 b-tagged jets, MET>250";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>250$";
    break;

  default:
    std::cout << "Could not find category info from category enum provided!" << std::endl;
    id    = category;
    label = "NO CATEGORY INFO FOUND FROM ENUM PROVIDED";
    title = "NO CATEGORY INFO FOUND FROM ENUM PROVIDED";
    tex   = "NO CATEGORY INFO FOUND FROM ENUM PROVIDED";
    break;

  }; // end switch

}

//////////////////////////////////////////////////////////////////////

bool categoryInfo::passCategory( categoryInfo::ID category ){

  bool result = false;

  switch( category ){

  case( k_incl ):
    result = true;
    break;

  case( k_ge2jets ):
    if( babyAnalyzer.ngoodjets()>=2 ) result = true;
    break;

  case( k_ge2jets_ge6p4modTop ):
    if( babyAnalyzer.ngoodjets()>=2 && 
	babyAnalyzer.topnessMod()>=6.4 ) result = true;
    break;  

  case( k_ge2jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()>=2 && 
	babyAnalyzer.MT2W()<200.0      ) result = true;
    break;

  case( k_ge2jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()>=2 && 
	babyAnalyzer.MT2W()>=200.0      ) result = true;
    break;  

  case( k_ee2jets ):
    if( babyAnalyzer.ngoodjets()==2 ) result = true;
    break;  

  case( k_ee2jets_250to350met ):
    if( babyAnalyzer.ngoodjets()==2 &&
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<350       ) result = true;
    break;

  case( k_ee2jets_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==2 &&
	babyAnalyzer.pfmet()>=350.0     ) result = true;
    break; 

  case( k_ee2jets_ge6p4modTop ):
    if( babyAnalyzer.ngoodjets()==2 && 
	babyAnalyzer.topnessMod()>=6.4 ) result = true;
    break;

  case( k_ee2jets_ge6p4modTop_250to350met ):
    if( babyAnalyzer.ngoodjets()==2 &&
	babyAnalyzer.topnessMod()>=6.4 &&
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<350           ) result = true;
    break;

  case( k_ee2jets_ge6p4modTop_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==2 &&
	babyAnalyzer.topnessMod()>=6.4 &&
	babyAnalyzer.pfmet()>=350.0        ) result = true;
    break;

  case( k_ge3jets ):
    if( babyAnalyzer.ngoodjets()>=3 ) result = true;
    break;

  case( k_ge3jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()>=3 && 
	babyAnalyzer.MT2W()<200.0      ) result = true;
    break;

  case( k_ge3jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()>=3 && 
	babyAnalyzer.MT2W()>=200.0      ) result = true;
    break;  

  case( k_ee3jets ):
    if( babyAnalyzer.ngoodjets()==3 ) result = true;
    break;

  case( k_ee3jets_250to350met ):
    if( babyAnalyzer.ngoodjets()==3 &&
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<350           ) result = true;
    break;

  case( k_ee3jets_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==3 &&
	babyAnalyzer.pfmet()>=350.0    ) result = true;
    break;

  case( k_ee3jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()==3 && 
	babyAnalyzer.MT2W()<200.0      ) result = true;
    break;

  case( k_ee3jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()==3 && 
	babyAnalyzer.MT2W()>=200.0      ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_250to350met ):
    if( babyAnalyzer.ngoodjets()==3 &&
	babyAnalyzer.MT2W()>=200.0 && 
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<350        ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==3 &&
	babyAnalyzer.MT2W()>=200.0 && 
	babyAnalyzer.pfmet()>=350.0    ) result = true;
    break;

  case( k_ge4jets ):
    if( babyAnalyzer.ngoodjets()>=4 ) result = true;
    break;
    
  case( k_ge4jets_250to325met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<325.0       ) result = true;
    break;

  case( k_ge4jets_325toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	babyAnalyzer.pfmet()>=325.0    ) result = true;
    break;

  case( k_ge4jets_250to350met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<350.0       ) result = true;
    break;

  case( k_ge4jets_350to450met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	babyAnalyzer.pfmet()>=350.0 &&
	babyAnalyzer.pfmet()<450.0       ) result = true;
    break;

  case( k_ge4jets_450toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	babyAnalyzer.pfmet()>=450.0    ) result = true;
    break;

  case( k_ge4jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	babyAnalyzer.MT2W()<200.0      ) result = true;
    break;

  case( k_ge4jets_lt200mt2w_250to325met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	babyAnalyzer.MT2W()<200.0 &&
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<325.0     ) result = true;
    break;

  case( k_ge4jets_lt200mt2w_325toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	babyAnalyzer.MT2W()<200.0 &&
	babyAnalyzer.pfmet()>=325.0    ) result = true;
    break;

  case( k_ge4jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	babyAnalyzer.MT2W()>=200.0      ) result = true;
    break;  

  case( k_ge4jets_ge200mt2w_250to350met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	babyAnalyzer.MT2W()>=200.0 &&
	babyAnalyzer.pfmet()>=250.0 &&
	babyAnalyzer.pfmet()<350.0     ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_350to450met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	babyAnalyzer.MT2W()>=200.0 &&
	babyAnalyzer.pfmet()>=350.0 &&
	babyAnalyzer.pfmet()<450.0     ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_450toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	babyAnalyzer.MT2W()>=200.0 &&
	babyAnalyzer.pfmet()>=450.0    ) result = true;
    break;

  case( k_ge5jets ):
    if( babyAnalyzer.ngoodjets()>=5 ) result = true;
    break;

  case( k_ge1btags_ge50met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	babyAnalyzer.pfmet()>=50.0      ) result = true;
    break;

  case( k_ge1btags_ge100met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	babyAnalyzer.pfmet()>=100.0     ) result = true;
    break;

  case( k_ge1btags_ge150met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	babyAnalyzer.pfmet()>=150.0     ) result = true;
    break;
    
  case( k_ge1btags_ge200met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	babyAnalyzer.pfmet()>=200.0     ) result = true;
    break;

  case( k_ge1btags_ge250met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	babyAnalyzer.pfmet()>=250.0     ) result = true;
    break;

  case( k_ge2btags_ge50met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	babyAnalyzer.pfmet()>=50.0     ) result = true;
    break;

  case( k_ge2btags_ge100met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	babyAnalyzer.pfmet()>=100.0     ) result = true;
    break;

  case( k_ge2btags_ge150met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	babyAnalyzer.pfmet()>=150.0     ) result = true;
    break;
    
  case( k_ge2btags_ge200met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	babyAnalyzer.pfmet()>=200.0     ) result = true;
    break;

  case( k_ge2btags_ge250met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	babyAnalyzer.pfmet()>=250.0     ) result = true;
    break;

  default:
    std::cout << "Could not find category info from category enum provided!" << std::endl;
    break;

  }; // end switch

  return result;
  
}

//////////////////////////////////////////////////////////////////////

categoryInfo::vect_util_passBool categoryInfo::passCategoriesFromList( vect_util categoryList, bool onlyReturnTrue ){

  vect_util_passBool result;

  for(int iCat=0; iCat<(int)categoryList.size(); iCat++){

    pair_util_passBool temp_result;
    temp_result.first  = categoryList[iCat];
    temp_result.second = passCategory( temp_result.first.id ) ? true : false;
    if( onlyReturnTrue ){
      if( temp_result.second ) result.push_back( temp_result );
    }
    else result.push_back( temp_result );

  }

  return result;

}

//////////////////////////////////////////////////////////////////////

categoryInfo::vect_util categoryInfo::getCategoryList( analyzerInfo::ID analysis ){

  vect_util result;

  switch( analysis ){
    
  case( analyzerInfo::k_SR ):
  case( analyzerInfo::k_CR0b ):
  case( analyzerInfo::k_CR2l ):
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge2jets) );
    result.push_back( categoryUtil(k_ge2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ge2jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge2jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee2jets) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop_250to350met) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop_350toInfmet) );
    result.push_back( categoryUtil(k_ge3jets) );
    result.push_back( categoryUtil(k_ge3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee3jets) );
    result.push_back( categoryUtil(k_ee3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_250to350met) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_350toInfmet) );
    result.push_back( categoryUtil(k_ge4jets) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_250to325met) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_325toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_250to350met) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_350to450met) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_450toInfmet) );
    result.push_back( categoryUtil(k_ge5jets) );
    break;

  case( analyzerInfo::k_CR1l_bulkWJets ):
    result.push_back( categoryUtil(k_incl) );
    break;
  
  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge1btags_ge50met) );
    result.push_back( categoryUtil(k_ge1btags_ge100met) );
    result.push_back( categoryUtil(k_ge1btags_ge150met) );
    result.push_back( categoryUtil(k_ge1btags_ge200met) );
    result.push_back( categoryUtil(k_ge1btags_ge250met) );
    result.push_back( categoryUtil(k_ge2btags_ge50met) );
    result.push_back( categoryUtil(k_ge2btags_ge100met) );
    result.push_back( categoryUtil(k_ge2btags_ge150met) );
    result.push_back( categoryUtil(k_ge2btags_ge200met) );
    result.push_back( categoryUtil(k_ge2btags_ge250met) );
    break;

  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge2jets) );
    result.push_back( categoryUtil(k_ee2jets) );
    result.push_back( categoryUtil(k_ee2jets_250to350met) );
    result.push_back( categoryUtil(k_ee2jets_350toInfmet) );
    result.push_back( categoryUtil(k_ge3jets) );
    result.push_back( categoryUtil(k_ee3jets) );
    result.push_back( categoryUtil(k_ee3jets_250to350met) );
    result.push_back( categoryUtil(k_ee3jets_350toInfmet) );
    result.push_back( categoryUtil(k_ge4jets) );
    result.push_back( categoryUtil(k_ge4jets_250to325met) );
    result.push_back( categoryUtil(k_ge4jets_325toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_250to350met) );
    result.push_back( categoryUtil(k_ge4jets_350to450met) );
    result.push_back( categoryUtil(k_ge4jets_450toInfmet) );
    result.push_back( categoryUtil(k_ge5jets) );
    break;
  
  default:
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge2jets) );
    result.push_back( categoryUtil(k_ge2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ge2jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge2jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee2jets) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ge3jets) );
    result.push_back( categoryUtil(k_ge3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee3jets) );
    result.push_back( categoryUtil(k_ee3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ge4jets) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ge5jets) );
    break;
    
  }; // end analysis switch


  return result;

}

//////////////////////////////////////////////////////////////////////
