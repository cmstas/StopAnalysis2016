#include "recoClassyInfo.h"

//////////////////////////////////////////////////////////////////////

recoClassyInfo::recoClassyUtil::recoClassyUtil( recoClassyInfo::ID recoClassy ){

  switch( recoClassy ){

  case( k_incl ):
    id    = recoClassy;
    label = "incl";
    title = "Inclusive Reco Classification";
    tex   = "Inclusive~Reco~Classification";
    break;

  case( k_1lep_el ):
    id    = recoClassy;
    label = "ee1lep_el";
    title = "1 lepton, el";
    tex   = "$1$~lepton,~el";
    break;

  case( k_1lep_mu ):
    id    = recoClassy;
    label = "ee1lep_mu";
    title = "1 lepton, muon";
    tex   = "$1$~lepton,~muon";
    break;

  case( k_2lep_elel ):
    id    = recoClassy;
    label = "ee2lep_elel";
    title = "2 leptons, el,el";
    tex   = "$2$~leptons,~el,el";
    break;

  case( k_2lep_elmu ):
    id    = recoClassy;
    label = "ee2lep_elmu";
    title = "2 leptons, el,mu";
    tex   = "$2$~leptons,~el,$\\mu$";
    break;

  case( k_2lep_mumu ):
    id    = recoClassy;
    label = "ee2lep_mumu";
    title = "2 leptons, mu,mu";
    tex   = "$2$~leptons,~$\\mu,\\mu$";
    break;

  case( k_2lep_2selLep ):
    id    = recoClassy;
    label = "ee2lep_2selLep";
    title = "2 leptons, 2 selected leptons";
    tex   = "$2$~leptons,~2~selected~leptons";
    break;

  case( k_2lep_1selLep_1vetoLep ):
    id    = recoClassy;
    label = "ee2lep_1selLep_1vetoLep";
    title = "2 leptons, 1 selected, 1 veto lepton";
    tex   = "$2$~leptons,~1~selected,~1~veto~lepton";
    break;

  case( k_2lep_2selOrVetoLep ):
    id    = recoClassy;
    label = "ee2lep_2selLepOrVetoLep";
    title = "2 leptons, 2 selected or veto leptons";
    tex   = "$2$~leptons,~2~selected~or~veto~leptons";
    break;
    

  case( k_2lep_1selLep_1isoTrackOrPfTau ):
    id    = recoClassy;
    label = "ee2lep_1selLep_1isoTrackOrPfTau";
    title = "2 leptons, 1 selected lepton, 1 isolated track or pfTau";
    tex   = "$2$~leptons,~1~selected~lepton,~1~isolated~track~or~pfTau";
    break;

  default:
    std::cout << "Could not find reco classification info from recoClassy enum provided!" << std::endl;
    id    = recoClassy;
    label = "NO RECO CLASSY INFO FOUND FROM ENUM PROVIDED";
    title = "NO RECO CLASSY INFO FOUND FROM ENUM PROVIDED";
    tex   = "NO RECO CLASSY INFO FOUND FROM ENUM PROVIDED";
    break;
    
  };

}

//////////////////////////////////////////////////////////////////////

bool recoClassyInfo::passRecoClassy( recoClassyInfo::ID recoClassy ){

  bool result = false;

  switch( recoClassy ){

  case( k_incl ):
    result = true;
    break;

  case( k_1lep_el ):
    if( abs(babyAnalyzer.lep1_pdgid())==11 ) result = true;
    break;

  case( k_1lep_mu ):
    if( abs(babyAnalyzer.lep1_pdgid())==13 ) result = true;
    break;

  case( k_2lep_elel ):
    if( abs(babyAnalyzer.lep1_pdgid())==11 &&
	abs(babyAnalyzer.lep2_pdgid())==11    ) result = true;
    break;

  case( k_2lep_elmu ):
    if( ( abs(babyAnalyzer.lep1_pdgid())==11 &&
	  abs(babyAnalyzer.lep2_pdgid())==13    ) || 
	( abs(babyAnalyzer.lep1_pdgid())==13 &&
	  abs(babyAnalyzer.lep2_pdgid())==11    )    ) result = true;
    break;

  case( k_2lep_mumu ):
    if( abs(babyAnalyzer.lep1_pdgid())==13 &&
	abs(babyAnalyzer.lep2_pdgid())==13    ) result = true;
    break;

  case( k_2lep_2selLep ):
    if( babyAnalyzer.ngoodleps()>=2 ) result = true;
    break;

  //case( k_2lep_1selLep_1vetoLep ):
    //if( babyAnalyzer.ngoodleps()==1 &&
    //	babyAnalyzer.nvetoleps()>=2 && babyAnalyzer.lep2_p4().Pt()>10.0 ) result = true;
    //break;

  //case( k_2lep_2selOrVetoLep ):
    //if( (babyAnalyzer.ngoodleps()>=2)     ||
    //	(babyAnalyzer.ngoodleps()==1 &&
    //	 babyAnalyzer.nvetoleps()>=2 && babyAnalyzer.lep2_p4().Pt()>10.0   )    ) result = true;
    //break;
  
  case( k_2lep_1selLep_1vetoLep ):
    if( babyAnalyzer.ngoodleps()==1 &&
	babyAnalyzer.nvetoleps()>=2    ) result = true;
    break;

  case( k_2lep_2selOrVetoLep ):
    if( (babyAnalyzer.ngoodleps()>=2)     ||
	(babyAnalyzer.ngoodleps()==1 &&
	 babyAnalyzer.nvetoleps()>=2   )    ) result = true;
    break;
      
  case( k_2lep_1selLep_1isoTrackOrPfTau ):
    if( babyAnalyzer.ngoodleps()==1 &&
	babyAnalyzer.nvetoleps()==1 &&
	(!babyAnalyzer.PassTrackVeto()||!babyAnalyzer.PassTauVeto()) ) result = true;
    break;

  default:
    std::cout << "Could not find reco classification info from recoClassy enum provided!" << std::endl;
    break;

  };

  return result;

}


//////////////////////////////////////////////////////////////////////

recoClassyInfo::vect_util_passBool recoClassyInfo::passRecoClassyFromList( vect_util recoClassyList, bool onlyReturnTrue ){

  vect_util_passBool result;

  for(int iClassy=0; iClassy<(int)recoClassyList.size(); iClassy++){

    pair_util_passBool temp_result;
    temp_result.first  = recoClassyList[iClassy];
    temp_result.second = passRecoClassy( temp_result.first.id ) ? true : false;
    if( onlyReturnTrue ){
      if( temp_result.second ) result.push_back( temp_result );
    }
    else result.push_back( temp_result );

  }

  return result;

}

//////////////////////////////////////////////////////////////////////

recoClassyInfo::vect_util recoClassyInfo::getRecoClassyList( analyzerInfo::ID analysis ){

  vect_util result;
  
  switch( analysis ){

  case( analyzerInfo::k_SR ):
    result.push_back( recoClassyUtil(k_incl) );
    //result.push_back( recoClassyUtil(k_1lep_el) );
    //result.push_back( recoClassyUtil(k_1lep_mu) );
    break;

  case( analyzerInfo::k_CR0b ):
    result.push_back( recoClassyUtil(k_incl) );
    //result.push_back( recoClassyUtil(k_1lep_el) );
    //result.push_back( recoClassyUtil(k_1lep_mu) );
    break;

  case( analyzerInfo::k_CR1l_bulkWJets ):
    result.push_back( recoClassyUtil(k_incl) );
    //result.push_back( recoClassyUtil(k_1lep_el) );
    //result.push_back( recoClassyUtil(k_1lep_mu) );
    break;

  case( analyzerInfo::k_CR2l ):
    result.push_back( recoClassyUtil(k_incl) );
    result.push_back( recoClassyUtil(k_2lep_2selLep) );
    result.push_back( recoClassyUtil(k_2lep_1selLep_1vetoLep) );
    result.push_back( recoClassyUtil(k_2lep_2selOrVetoLep) );
    result.push_back( recoClassyUtil(k_2lep_1selLep_1isoTrackOrPfTau) );
    break;

  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( recoClassyUtil(k_incl) );
    result.push_back( recoClassyUtil(k_2lep_elel) );
    result.push_back( recoClassyUtil(k_2lep_elmu) );
    result.push_back( recoClassyUtil(k_2lep_mumu) );
    break;


  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( recoClassyUtil(k_incl) );
    break;

  default:
    std::cout << "Could not find reco classification info from recoClassy enum provided!" << std::endl;
    result.push_back( recoClassyUtil(k_incl) );
    break;

  }; // end selection switch


  return result;
}

//////////////////////////////////////////////////////////////////////


