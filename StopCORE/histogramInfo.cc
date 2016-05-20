#include "histogramInfo.h"

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getHistoLabel( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, categoryInfo::ID catId, systematicInfo::ID sysId ){

  std::string result = "";

  result += "h__";
  result += base;
  
  genClassyInfo::genClassyUtil genClassy( genClassyId );
  result += "__genClassy_";
  result += genClassy.label;
  
  recoClassyInfo::recoClassyUtil recoClassy( recoClassyId );
  result += "__recoClassy_";
  result += recoClassy.label;
  
  categoryInfo::categoryUtil category( catId );
  result += "__cat_";
  result += category.label;
  
  systematicInfo::systematicUtil systematic( sysId );
  result += "__sys_";
  result += systematic.label;

  return result;

}

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getHistoTitle( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, categoryInfo::ID catId, systematicInfo::ID sysId ){

  std::string result = "";

  result += base;
  
  genClassyInfo::genClassyUtil genClassy( genClassyId );
  result += ", genClassy: ";
  result += genClassy.title;
  
  recoClassyInfo::recoClassyUtil recoClassy( recoClassyId );
  result += ", recoClassy: ";
  result += recoClassy.title;
  
  categoryInfo::categoryUtil category( catId );
  result += ", category: ";
  result += category.title;
  
  systematicInfo::systematicUtil systematic( sysId );
  result += ", systematic: ";
  result += systematic.title;

  return result;

}

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getYieldHistoLabel( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, systematicInfo::ID sysId ){
  
  std::string result = "";

  result += "h__";
  result += base;
  
  genClassyInfo::genClassyUtil genClassy( genClassyId );
  result += "__genClassy_";
  result += genClassy.label;
  
  recoClassyInfo::recoClassyUtil recoClassy( recoClassyId );
  result += "__recoClassy_";
  result += recoClassy.label;
  
  systematicInfo::systematicUtil systematic( sysId );
  result += "__sys_";
  result += systematic.label;
  
  return result;

}

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getYieldHistoTitle( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, systematicInfo::ID sysId ){

  std::string result = "";

  result += base;
  
  genClassyInfo::genClassyUtil genClassy( genClassyId );
  result += ", genClassy: ";
  result += genClassy.title;
  
  recoClassyInfo::recoClassyUtil recoClassy( recoClassyId );
  result += ", recoClassy: ";
  result += recoClassy.title;
  
  systematicInfo::systematicUtil systematic( sysId );
  result += ", systematic: ";
  result += systematic.title;
  
  return result;

}

//////////////////////////////////////////////////////////////////////   

histogramInfo::h1_Util::h1_Util( TFile *f_out, std::string label, std::string title, int nBins, double min, double max, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys ){

  histos.clear();

  h_label_base = label;
  h_title_base = title;
  
  h_nBins = nBins;
  h_min   = min;
  h_max   = max; 
  
  h_genClassy   = genClassys;
  h_recoClassy  = recoClassys;
  h_categories  = cats;
  h_systematics = sys;

  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){
		  
	  std::string h_label = getHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
	  std::string h_title = getHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );

	  TH1D *h_temp = new TH1D( h_label.c_str(), h_title.c_str(), h_nBins, h_min, h_max );
	  h_temp->SetDirectory( f_out );

	  histos[ h_label ] = h_temp;

	} // end loop over categories
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics

}

////////////////////////////////////////////////////////////////////// 
/*
void histogramInfo::h1_Util::fill( double value, genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts ){

  //
  // Loop over genClassy,recoClassy,categories,systematics that
  //   are owned by h1_Util, fill when pass evt criteria for each
  //
  
  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){
	  
	  for(int iEvtSys=0; iEvtSys<(int)sys_wgts.size(); iEvtSys++){
	    if( sys_wgts[iEvtSys].first != h_systematics[iSys] ) continue;
	  	    
	    for(int iEvtGen=0; iEvtGen<(int)pass_genClassy.size(); iEvtGen++){
	      if( pass_genClassy[iEvtGen].first != h_genClassy[iGen] ) continue;
	      if( !pass_genClassy[iEvtGen].second ) continue;

	      for(int iEvtReco=0; iEvtReco<(int)pass_recoClassy.size(); iEvtReco++){
		if( pass_recoClassy[iEvtReco].first != h_recoClassy[iReco] ) continue;
		if( !pass_recoClassy[iEvtReco].second ) continue;

		for(int iEvtCat=0; iEvtCat<(int)pass_cat.size(); iEvtCat++){
		  if( pass_cat[iEvtCat].first != h_categories[iCat] ) continue;
		  if( !pass_cat[iEvtCat].second ) continue;

		  std::string h_label = getHistoLabel( h_label_base, h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
		  histos[ h_label ]->Fill( std::max( h_min+EPS, std::min(value, h_max-EPS) ), sys_wgts[iEvtSys].second );
		  
		} // end loop over categories, passed this event
	      } // end loop over reco classifications, passed this event
	    } // end gen classifications, passed this event
	  } // end loop over systematic weights, this event

	} // end loop over histogram categories
      } // end loop over histogram recoClassifications
    } // end loop over histogram genClassifications
  } // end loop over histogram systematics

  return;
}
*/
////////////////////////////////////////////////////////////////////// 

void histogramInfo::h1_Util::fill( double value, genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts ){

  //
  // Loop over genClassy,recoClassy,categories,systematics that
  //   are owned by h1_Util, fill when pass evt criteria for each
  //
  
  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){

    bool fillSys=false;
    for(int iEvtSys=0; iEvtSys<(int)sys_wgts.size(); iEvtSys++){
      if( sys_wgts[iEvtSys].first == h_systematics[iSys] ){
	fillSys = true;
	break;
      }
    }
    if(!fillSys) continue;

	  
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      
      bool fillGenClassy=false;
      for(int iEvtGen=0; iEvtGen<(int)pass_genClassy.size(); iEvtGen++){
	if( pass_genClassy[iEvtGen].first == h_genClassy[iGen] &&
	    pass_genClassy[iEvtGen].second ){
	  fillGenClassy = true;
	  break;
	}
      }
      if(!fillGenClassy) continue;
	  

      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){

	bool fillRecoClassy=false;
	for(int iEvtReco=0; iEvtReco<(int)pass_recoClassy.size(); iEvtReco++){
	  if( pass_recoClassy[iEvtReco].first == h_recoClassy[iReco] &&
	      pass_recoClassy[iEvtReco].second ){
	    fillRecoClassy=true;
	    break;
	  }
	}
	if(!fillRecoClassy) continue;
	
	
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){
	  
	  bool fillCat=false;
	  for(int iEvtCat=0; iEvtCat<(int)pass_cat.size(); iEvtCat++){
	    if( pass_cat[iEvtCat].first == h_categories[iCat] &&
		pass_cat[iEvtCat].second ){
	      fillCat=true;
	      break;
	    }
	  }
	  if(!fillCat) continue;


	  std::string h_label = getHistoLabel( h_label_base, h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
	  histos[ h_label ]->Fill( std::max( h_min+EPS, std::min(value, h_max-EPS) ), sys_wgts[iSys].second );
	  
	} // end loop over histogram categories
      } // end loop over histogram recoClassifications
    } // end loop over histogram genClassifications
  } // end loop over histogram systematics
  
  return;
}

////////////////////////////////////////////////////////////////////// 

histogramInfo::h1_Yield_Util::h1_Yield_Util( TFile *f_out, std::string label, std::string title, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys ){

  histos.clear();
  
  h_label_base = label;
  h_title_base = title;
  
  h_genClassy   = genClassys;
  h_recoClassy  = recoClassys;
  h_categories  = cats;
  h_systematics = sys;
  
  int nBins = (int)h_categories.size();
  
  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	
	std::string h_label = getYieldHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );
	std::string h_title = getYieldHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );
	
	TH1D *h_temp = new TH1D( h_label.c_str(), h_title.c_str(), nBins, 0.0, (double)nBins );
	
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){
	  categoryInfo::categoryUtil category( h_categories[iCat] );
	  h_temp->GetXaxis()->SetBinLabel(iCat+1, category.label.c_str() ); 
	} // end loop over categories
	
	h_temp->SetDirectory( f_out );
	histos[ h_label ] = h_temp;
	
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics
}

////////////////////////////////////////////////////////////////////// 
/*
void histogramInfo::h1_Yield_Util::fill( genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts ){

  //
  // Loop over genClassy,recoClassy,categories,systematics that
  //   are owned by h1_Util, fill when pass evt criteria for each
  //
  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	
	for(int iEvtSys=0; iEvtSys<(int)sys_wgts.size(); iEvtSys++){
	  if( sys_wgts[iEvtSys].first != h_systematics[iSys] ) continue;
	  
	  for(int iEvtGen=0; iEvtGen<(int)pass_genClassy.size(); iEvtGen++){
	    if( pass_genClassy[iEvtGen].first != h_genClassy[iGen] ) continue;
	    if( !pass_genClassy[iEvtGen].second ) continue;

	    for(int iEvtReco=0; iEvtReco<(int)pass_recoClassy.size(); iEvtReco++){
	      if( pass_recoClassy[iEvtReco].first != h_recoClassy[iReco] ) continue;
	      if( !pass_recoClassy[iEvtReco].second ) continue;

	      for(int iEvtCat=0; iEvtCat<(int)pass_cat.size(); iEvtCat++){
		if( !pass_cat[iEvtCat].second ) continue;
		
		std::string h_label = getYieldHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );

		categoryInfo::categoryUtil category( pass_cat[iEvtCat].first );

		histos[ h_label ]->Fill( category.label.c_str(), sys_wgts[iEvtSys].second );
		  
	      } // end loop over categories, passed this event
	    } // end loop over reco classifications, passed this event
	  } // end gen classifications, passed this event
	} // end loop over systematic weights, this event

      
      } // end loop over histogram recoClassifications
    } // end loop over histogram genClassifications
  } // end loop over histogram systematics

  return;
}
*/
////////////////////////////////////////////////////////////////////// 


void histogramInfo::h1_Yield_Util::fill( genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts ){

  //
  // Loop over genClassy,recoClassy,categories,systematics that
  //   are owned by h1_Util, fill when pass evt criteria for each
  //
  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    
    bool fillSys=false;
    for(int iEvtSys=0; iEvtSys<(int)sys_wgts.size(); iEvtSys++){
      if( sys_wgts[iEvtSys].first == h_systematics[iSys] ){
	fillSys=true;
	break;
      }
    }
    if(!fillSys) continue;

    
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){

      bool fillGenClassy=false;
      for(int iEvtGen=0; iEvtGen<(int)pass_genClassy.size(); iEvtGen++){
	if( pass_genClassy[iEvtGen].first == h_genClassy[iGen] &&
	    pass_genClassy[iEvtGen].second ){
	  fillGenClassy=true;
	  break;
	}
      }
      if(!fillGenClassy) continue;


      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){

	bool fillRecoClassy=false;
	for(int iEvtReco=0; iEvtReco<(int)pass_recoClassy.size(); iEvtReco++){
	  if( pass_recoClassy[iEvtReco].first == h_recoClassy[iReco] &&
	      pass_recoClassy[iEvtReco].second ){
	    fillRecoClassy=true;
	    break;
	  }
	}
	if(!fillRecoClassy) continue;
	

	for(int iEvtCat=0; iEvtCat<(int)pass_cat.size(); iEvtCat++){
	  if( pass_cat[iEvtCat].second ){
	    
	    std::string h_label = getYieldHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );
	    
	    categoryInfo::categoryUtil category( pass_cat[iEvtCat].first );
	    
	    histos[ h_label ]->Fill( category.label.c_str(), sys_wgts[iSys].second );
	    
	  } // end if pass category	  
	} // end loop over categories, passed this event
	
	
      } // end loop over histogram recoClassifications
    } // end loop over histogram genClassifications
  } // end loop over histogram systematics
  
  return;
}

////////////////////////////////////////////////////////////////////// 

histogramInfo::h2_Util::h2_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double min_x, double max_x, int nBins_y, double min_y, double max_y, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys ){

  histos.clear();

  h_label_base = label;
  h_title_base = title;
  
  h_nBins_x = nBins_x;
  h_min_x   = min_x;
  h_max_x   = max_x; 

  h_nBins_y = nBins_y;
  h_min_y   = min_y;
  h_max_y   = max_y; 
  
  h_genClassy   = genClassys;
  h_recoClassy  = recoClassys;
  h_categories  = cats;
  h_systematics = sys;

  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){
		  
	  std::string h_label = getHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
	  std::string h_title = getHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );

	  TH2D *h_temp = new TH2D( h_label.c_str(), h_title.c_str(), h_nBins_x, h_min_x, h_max_x, h_nBins_y, h_min_y, h_max_y );
	  h_temp->SetDirectory( f_out );

	  histos[ h_label ] = h_temp;

	} // end loop over categories
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics

}

////////////////////////////////////////////////////////////////////// 

void histogramInfo::h2_Util::fill( double value_x, double value_y, genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts ){

  //
  // Loop over genClassy,recoClassy,categories,systematics that
  //   are owned by h1_Util, fill when pass evt criteria for each
  //
  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){
	  

	  for(int iEvtSys=0; iEvtSys<(int)sys_wgts.size(); iEvtSys++){
	    if( sys_wgts[iEvtSys].first != h_systematics[iSys] ) continue;
	    
	    for(int iEvtGen=0; iEvtGen<(int)pass_genClassy.size(); iEvtGen++){
	      if( pass_genClassy[iEvtGen].first != h_genClassy[iGen] ) continue;
	      if( !pass_genClassy[iEvtGen].second ) continue;

	      for(int iEvtReco=0; iEvtReco<(int)pass_recoClassy.size(); iEvtReco++){
		if( pass_recoClassy[iEvtReco].first != h_recoClassy[iReco] ) continue;
		if( !pass_recoClassy[iEvtReco].second ) continue;

		for(int iEvtCat=0; iEvtCat<(int)pass_cat.size(); iEvtCat++){
		  if( pass_cat[iEvtCat].first != h_categories[iCat] ) continue;
		  if( !pass_cat[iEvtCat].second ) continue;

		  std::string h_label = getHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
		  histos[ h_label ]->Fill( std::max( h_min_x+EPS, std::min(value_x, h_max_x-EPS) ), std::max( h_min_y+EPS, std::min(value_y, h_max_y-EPS) ), sys_wgts[iEvtSys].second );
		  
		} // end loop over categories, passed this event
	      } // end loop over reco classifications, passed this event
	    } // end gen classifications, passed this event
	  } // end loop over systematic weights, this event

	} // end loop over histogram categories
      } // end loop over histogram recoClassifications
    } // end loop over histogram genClassifications
  } // end loop over histogram systematics

  return;
}

////////////////////////////////////////////////////////////////////// 
