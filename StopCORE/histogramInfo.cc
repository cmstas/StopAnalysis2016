#include "histogramInfo.h"

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getHistoLabel( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, categoryInfo::categoryUtil cat, systematicInfo::systematicUtil sys ){

  std::string result = "";

  result += base;
  
  result += "__genClassy_";
  result += genClassy.label;
  
  result += "__recoClassy_";
  result += recoClassy.label;
  
  result += "__cat_";
  result += cat.label;
  
  result += "__sys_";
  result += sys.label;

  return result;

}

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getHistoTitle( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, categoryInfo::categoryUtil cat, systematicInfo::systematicUtil sys ){

  std::string result = "";

  result += base;
  
  result += ", genClassy: ";
  result += genClassy.title;
  
  result += ", recoClassy: ";
  result += recoClassy.title;
  
  result += ", category: ";
  result += cat.title;
  
  result += ", systematic: ";
  result += sys.title;

  return result;

}

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getYieldHistoLabel( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, systematicInfo::systematicUtil sys ){
  
  std::string result = "";

  result += base;
  
  result += "__genClassy_";
  result += genClassy.label;
  
  result += "__recoClassy_";
  result += recoClassy.label;
  
  result += "__sys_";
  result += sys.label;
  
  return result;

}

////////////////////////////////////////////////////////////////////// 

std::string histogramInfo::getYieldHistoTitle( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, systematicInfo::systematicUtil sys ){

  std::string result = "";

  result += base;
  
  result += ", genClassy: ";
  result += genClassy.title;
  
  result += ", recoClassy: ";
  result += recoClassy.title;
  
  result += ", systematic: ";
  result += sys.title;
  
  return result;

}

//////////////////////////////////////////////////////////////////////   

int histogramInfo::getHistoIndex( systematicInfo::ID sys, genClassyInfo::ID genClassy, recoClassyInfo::ID recoClassy, categoryInfo::ID cat ){
  
  int result = sys*nGenClassy_*nRecoClassy_*nCats_ + genClassy*nRecoClassy_*nCats_ + recoClassy*nCats_ + cat;

  return result;
}
  
//////////////////////////////////////////////////////////////////////   

int histogramInfo::getYieldHistoIndex( systematicInfo::ID sys, genClassyInfo::ID genClassy, recoClassyInfo::ID recoClassy ){

  int result = sys*nGenClassy_*nRecoClassy_ + genClassy*nRecoClassy_ + recoClassy;

  return result;
}

//////////////////////////////////////////////////////////////////////   

histogramInfo::h1_Util::h1_Util( TFile *f_out, std::string label, std::string title, int nBins, double min, double max, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys ){

  h_label_base = label;
  h_title_base = title;
  
  h_nBins = nBins;
  h_min   = min;
  h_max   = max; 
  
  h_genClassy   = genClassys;
  h_recoClassy  = recoClassys;
  h_categories  = cats;
  h_systematics = sys;

  for(int iHist=0; iHist<nHists_; iHist++) histos[iHist] = NULL;

  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){

	  int iHist = getHistoIndex( h_systematics[iSys].id, h_genClassy[iGen].id, h_recoClassy[iReco].id, h_categories[iCat].id );
	  //int iHist = h_systematics[iSys].id*nGenClassy_*nRecoClassy_*nCats_ + h_genClassy[iGen].id*nRecoClassy_*nCats_ + h_recoClassy[iReco].id*nCats_ + h_categories[iCat].id;
	  
	  std::string h_name  = getHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
	  std::string h_title = getHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );

	  histos[ iHist ] = new TH1D( h_name.c_str(), h_title.c_str(), h_nBins, h_min, h_max );

	  histos[ iHist ]->SetDirectory( f_out );
	  
	} // end loop over categories
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics

}

////////////////////////////////////////////////////////////////////// 

histogramInfo::h1_Yield_Util::h1_Yield_Util( TFile *f_out, std::string label, std::string title, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys ){

  h_label_base = label;
  h_title_base = title;
  
  h_genClassy   = genClassys;
  h_recoClassy  = recoClassys;
  h_categories  = cats;
  h_systematics = sys;
  
  int nBins = (int)h_categories.size();

  for(int iHist=0; iHist<nYieldHists_; iHist++) histos[iHist] = NULL;
  
  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	
	int iHist = getYieldHistoIndex( h_systematics[iSys].id, h_genClassy[iGen].id, h_recoClassy[iReco].id );
	//int iHist = h_systematics[iSys].id*nGenClassy_*nRecoClassy_ + h_genClassy[iGen].id*nRecoClassy_ + h_recoClassy[iReco].id;
	
	std::string h_name  = getYieldHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );
	std::string h_title = getYieldHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );
	
	histos[ iHist ] = new TH1D( h_name.c_str(), h_title.c_str(), nBins, 0.0, (double)nBins );
	
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){
	  histos[ iHist ]->GetXaxis()->SetBinLabel(iCat+1, h_categories[iCat].label.c_str() ); 
	} // end loop over categories
	
	histos[ iHist ]->SetDirectory( f_out );
	
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics
}

////////////////////////////////////////////////////////////////////// 

histogramInfo::h2_Util::h2_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double min_x, double max_x, int nBins_y, double min_y, double max_y, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys ){

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
  
  for(int iHist=0; iHist<nHists_; iHist++) histos[iHist] = NULL;

  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){

	  int iHist = getHistoIndex( h_systematics[iSys].id, h_genClassy[iGen].id, h_recoClassy[iReco].id, h_categories[iCat].id );
	  //int iHist = h_systematics[iSys].id*nGenClassy_*nRecoClassy_*nCats_ + h_genClassy[iGen].id*nRecoClassy_*nCats_ + h_recoClassy[iReco].id*nCats_ + h_categories[iCat].id;
		  
	  std::string h_name  = getHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
	  std::string h_title = getHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );

	  histos[ iHist ] = new TH2D( h_name.c_str(), h_title.c_str(), h_nBins_x, h_min_x, h_max_x, h_nBins_y, h_min_y, h_max_y );
	  
	  histos[ iHist ]->SetDirectory( f_out );
	  
	} // end loop over categories
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics

}

////////////////////////////////////////////////////////////////////// 

histogramInfo::h3_Util::h3_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double min_x, double max_x, int nBins_y, double min_y, double max_y, int nBins_z, double min_z, double max_z, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys ){

  h_label_base = label;
  h_title_base = title;
  
  h_nBins_x = nBins_x;
  h_min_x   = min_x;
  h_max_x   = max_x; 

  h_nBins_y = nBins_y;
  h_min_y   = min_y;
  h_max_y   = max_y; 
 
  h_nBins_y = nBins_z;
  h_min_y   = min_z;
  h_max_y   = max_z; 
 
  h_genClassy   = genClassys;
  h_recoClassy  = recoClassys;
  h_categories  = cats;
  h_systematics = sys;
  
  for(int iHist=0; iHist<nHists_; iHist++) histos[iHist] = NULL;

  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	for(int iCat=0; iCat<(int)h_categories.size(); iCat++){

	  int iHist = getHistoIndex( h_systematics[iSys].id, h_genClassy[iGen].id, h_recoClassy[iReco].id, h_categories[iCat].id );
	  //int iHist = h_systematics[iSys].id*nGenClassy_*nRecoClassy_*nCats_ + h_genClassy[iGen].id*nRecoClassy_*nCats_ + h_recoClassy[iReco].id*nCats_ + h_categories[iCat].id;

	  std::string h_name = getHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );
	  std::string h_title = getHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_categories[iCat], h_systematics[iSys] );

	  histos[ iHist ] = new TH3D( h_name.c_str(), h_title.c_str(), h_nBins_x, h_min_x, h_max_x, h_nBins_y, h_min_y, h_max_y, h_nBins_z, h_min_z, h_max_z );
	  histos[ iHist ]->SetDirectory( f_out );
	  
	} // end loop over categories
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics

}

////////////////////////////////////////////////////////////////////// 

histogramInfo::h3_Yield_Util::h3_Yield_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double h_min_x, double h_max_x, int nBins_y, double h_min_y, double h_max_y, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys ){

  h_label_base = label;
  h_title_base = title;
  
  h_genClassy   = genClassys;
  h_recoClassy  = recoClassys;
  h_categories  = cats;
  h_systematics = sys;
  
  int nBins = (int)h_categories.size();
  
  for(int iHist=0; iHist<nYieldHists_; iHist++) histos[iHist] = NULL;

  for(int iSys=0; iSys<(int)h_systematics.size(); iSys++){
    for(int iGen=0; iGen<(int)h_genClassy.size(); iGen++){
      for(int iReco=0; iReco<(int)h_recoClassy.size(); iReco++){
	
	int iHist = getYieldHistoIndex( h_systematics[iSys].id, h_genClassy[iGen].id, h_recoClassy[iReco].id );
	//int iHist = h_systematics[iSys].id*nGenClassy_*nRecoClassy_ + h_genClassy[iGen].id*nRecoClassy_ + h_recoClassy[iReco].id;

	std::string h_name  = getYieldHistoLabel( h_label_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );
	std::string h_title = getYieldHistoTitle( h_title_base.c_str(), h_genClassy[iGen], h_recoClassy[iReco], h_systematics[iSys] );
	
	histos[ iHist ] = new TH3D( h_name.c_str(), h_title.c_str(), nBins_x, h_min_x, h_max_x, nBins_y, h_min_y, h_max_y, nBins, 0.0, (double)nBins );
	
	for(int iCat=0; iCat<nBins; iCat++){
	  histos[ iHist ]->GetZaxis()->SetBinLabel(iCat+1, h_categories[iCat].label.c_str() ); 
	} // end loop over categories
	
	histos[ iHist ]->SetDirectory( f_out );
	
      } // end loop over reco classifications
    } // end loop over gen classifications
  } // end loop over systematics
}

////////////////////////////////////////////////////////////////////// 

TH1D* histogramInfo::getProjectionZ( double valX, double valY, TH3D *h3 ){

  TH1D *result = NULL;

  int binX = h3->GetXaxis()->FindBin( valX );
  int binY = h3->GetYaxis()->FindBin( valY );

  h3->GetXaxis()->SetRange( binX, binX );
  h3->GetYaxis()->SetRange( binY, binY );
  h3->GetZaxis()->SetRange( 1, h3->GetNbinsZ() );
  
  result = (TH1D*)h3->Project3D( "z" );

  return result;
}

////////////////////////////////////////////////////////////////////// 
