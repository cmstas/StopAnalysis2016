#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH3.h"
#include "TString.h"

#include <algorithm>
#include <string>
#include <vector>

#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"

int tableMaker_summedInputs( std::string f_input_dir="Histos/Nominal/", std::string f_out_name="Output/Tables/yields_summedInputs.tex", bool useZeroedAMCNLO=true ){

  // Make a tex document where each page will have a table
  //   This table will be for a given systematic. 
  //   It will show the yields for a set of catogries in rows
  //      and columns will be the input samples split by gen and reco
  //      classifications

  
  //
  // Configuration Variables
  //
  bool usePsuedoData = true;

  bool doRescale = true;
  //double rescale = 1.0; // use lumi from stopCORE
  double rescale = 5.0/0.8042; // rescale to new lumi

  
  //
  // Analyzer Type
  //
  analyzerInfo::ID analysis = analyzerInfo::k_CR2l;

  //
  // Sample List
  //
  TFile *f_input = NULL;

  sampleInfo::sampleUtil *data_util = NULL;
  if(usePsuedoData){
    data_util = new sampleInfo::sampleUtil( sampleInfo::k_allBkg );
  }
  else{
    data_util = new sampleInfo::sampleUtil( sampleInfo::k_single_lepton_met_2015CD );
  }
  

  sampleInfo::sampleUtil allBkg_util( sampleInfo::k_allBkg );

  std::pair< sampleInfo::ID, genClassyInfo::ID > sample;
  
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > bkgList;

  sample.first = sampleInfo::k_ttbar; 
  sample.second = genClassyInfo::k_ge2lep;
  bkgList.push_back(sample);

  sample.first = sampleInfo::k_ttbar; 
  sample.second = genClassyInfo::k_ee1lep;
  bkgList.push_back(sample);
  
  sample.first = sampleInfo::k_singleT; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);

  sample.first = sampleInfo::k_DYJetsToLL; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);

  sample.first = sampleInfo::k_WJetsToLNu; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);

  sample.first = sampleInfo::k_diBoson; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);

  sample.first = sampleInfo::k_TTW; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);

  sample.first = sampleInfo::k_TTZ; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);

  sample.first = sampleInfo::k_tZq; 
  sample.second = genClassyInfo::k_incl;
  //bkgList.push_back(sample);


  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > bkgList_byGen;
  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ee1lep_fromW;
  bkgList_byGen.push_back(sample);

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  bkgList_byGen.push_back(sample);

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ge2lep;
  bkgList_byGen.push_back(sample);

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ZtoNuNu;
  bkgList_byGen.push_back(sample);


  
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sigList;
  sample.first = sampleInfo::k_T2tt; 
  sample.second = genClassyInfo::k_incl;
  //sigList.push_back(sample);


  // T2tt mass points
  std::vector< std::pair< int, int > > T2tt_list;
  std::pair< int, int > T2tt_mass_point;
  
  T2tt_mass_point.first  = 800;
  T2tt_mass_point.second = 100;
  T2tt_list.push_back( T2tt_mass_point );

  T2tt_mass_point.first  = 800;
  T2tt_mass_point.second = 350;
  T2tt_list.push_back( T2tt_mass_point );

  T2tt_mass_point.first  = 500;
  T2tt_mass_point.second = 325;
  T2tt_list.push_back( T2tt_mass_point );

  T2tt_mass_point.first  = 400;
  T2tt_mass_point.second = 225;
  T2tt_list.push_back( T2tt_mass_point );

  


  //
  // Reco Classy List
  //
  recoClassyInfo::vect_id recoClassyList;
  recoClassyList.push_back( recoClassyInfo::k_incl );
    

  //
  // Category List
  //
  std::vector< categoryInfo::vect_id > tableList;
  categoryInfo::vect_id catList;

  catList.push_back( categoryInfo::k_ee2jets_ge6p4modTop_250to350met );
  catList.push_back( categoryInfo::k_ee2jets_ge6p4modTop_350toInfmet );
  catList.push_back( categoryInfo::k_ee2jets_ge6p4modTop );
  tableList.push_back( catList );

  catList.clear();
  catList.push_back( categoryInfo::k_ee3jets_ge200mt2w_250to350met );
  catList.push_back( categoryInfo::k_ee3jets_ge200mt2w_350toInfmet );
  catList.push_back( categoryInfo::k_ee3jets_ge200mt2w );
  tableList.push_back( catList );

  catList.clear();
  catList.push_back( categoryInfo::k_ge4jets_lt200mt2w_250to325met );
  catList.push_back( categoryInfo::k_ge4jets_lt200mt2w_325toInfmet );
  catList.push_back( categoryInfo::k_ge4jets_lt200mt2w );
  tableList.push_back( catList );

  catList.clear();
  catList.push_back( categoryInfo::k_ge4jets_ge200mt2w_250to350met );
  catList.push_back( categoryInfo::k_ge4jets_ge200mt2w_350to450met );
  catList.push_back( categoryInfo::k_ge4jets_ge200mt2w_450toInfmet );
  catList.push_back( categoryInfo::k_ge4jets_ge200mt2w );
  tableList.push_back( catList );

  catList.clear();
  catList.push_back( categoryInfo::k_ee2jets );
  catList.push_back( categoryInfo::k_ee3jets );
  catList.push_back( categoryInfo::k_ge4jets );
  tableList.push_back( catList );

  catList.clear();
  catList.push_back( categoryInfo::k_ee2jets_ge6p4modTop );
  catList.push_back( categoryInfo::k_ee3jets_ge200mt2w );
  catList.push_back( categoryInfo::k_ge4jets_lt200mt2w );
  catList.push_back( categoryInfo::k_ge4jets_ge200mt2w );
  tableList.push_back( catList );



  //
  // Systematic List
  //
  systematicInfo::vect_util systematicList;
  systematicList.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) ); 

  //
  // Open output file
  //
  FILE *f_out;
  std::cout << "    Output written to: " << std::endl;
  std::cout << "      " << f_out_name << std::endl << std::endl;
  f_out = fopen( f_out_name.c_str(), "w" );

  //
  // Print header info
  //
  fprintf(f_out, "\\documentclass{article}\n");
  fprintf(f_out, "\\usepackage[landscape]{geometry}\n");
  fprintf(f_out, "\\usepackage{multirow}\n");
  fprintf(f_out, "\\usepackage{color}\n");
  fprintf(f_out, "\\usepackage{longtable}\n\n");
  fprintf(f_out, "\\begin{document}\n");
  fprintf(f_out, "\\tiny\n");
  fprintf(f_out, "\n\n\n\n");

  //
  // Make yield tables
  //
  for(int iSys=0; iSys<(int)systematicList.size(); iSys++){
    
    for(int iRecoClassy=0; iRecoClassy<(int)recoClassyList.size(); iRecoClassy++){

      for(int iTable=0; iTable<(int)tableList.size(); iTable++){

	// Get number of collumns for table - ie categories
	int nCol = 1 + (int)tableList[iTable].size();
	fprintf(f_out, "\\begin{longtable}{|l|"); // samples
	for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	  fprintf(f_out,"c|");
	}
	fprintf(f_out, "} \n \n");

	// Top Title
	systematicInfo::systematicUtil systematic(systematicList[iSys]);
	std::string table_title = systematic.tex;
	table_title += " Systematic, Yield Table for Input Samples";

	// First Header
	fprintf(f_out, "\\multicolumn{%d}{c}{ %s }", nCol, table_title.c_str());
	fprintf(f_out, "\\"); 
	fprintf(f_out, "\\* \\hline \n");

	// Loop over categories for titles, one row per comma in title
	std::vector<std::string> header_str;

	// Get number of rows, each row is comma separated
	int maxRows = 1;
	for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	  categoryInfo::categoryUtil category(tableList[iTable][iCat]);
	  std::string cat_title = category.tex;
	  int nCommas = 0;
	  for(int iChar=0; iChar<(int)cat_title.size(); iChar++){
	    if( cat_title.compare(iChar,1,",")==0 ) nCommas++;
	  }
	  maxRows = std::max( maxRows, nCommas+1 );
	}

	if( maxRows == 1 ){

	  std::string row_str = "Sample ";
	  for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	    categoryInfo::categoryUtil category(tableList[iTable][iCat]);
	    std::string cat_title = category.tex;
	    row_str += " & ";
	    row_str += cat_title;
	    row_str += " ";
	  }
	  header_str.push_back(row_str);
	  fprintf(f_out, "%s", row_str.c_str());
	  fprintf(f_out, "\\");
	  fprintf(f_out, "\\* \n");
	
	}
	else{

	  // Get section of title for comma position
	  for(int iRow=0; iRow<maxRows; iRow++){
	    std::string row_str = "";
	    for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	    
	      if( iRow==floor(maxRows/2.0) && iCat==0 ) row_str += "Sample ";
	      else if( iCat==0 ) row_str += " ";
	    
	      categoryInfo::categoryUtil category(tableList[iTable][iCat]);
	      std::string cat_title = category.tex;
	    
	      std::size_t commaPos_begin = 0;
	      std::size_t commaPos_end   = cat_title.size();
	    
	      // Get first position of section
	      int nCommaFound=0;
	      if( iRow>0 ){
		std::size_t commaPos = 0;
		for(int jRow=0; jRow<maxRows; jRow++){
		  commaPos = cat_title.find(",", commaPos+1);
		  if( commaPos!=std::string::npos ){
		    nCommaFound++;
		    if(nCommaFound==iRow){
		      commaPos_begin = commaPos+1;
		      break;
		    } 
		  } 
		  else break;
		} 
	      } 
	      // Get last position of section
	      nCommaFound=0;
	      if( iRow<(maxRows-1) ){
		std::size_t commaPos = 0;
		for(int jRow=0; jRow<maxRows; jRow++){
		  commaPos = cat_title.find(",", commaPos+1);
		  if( commaPos!=std::string::npos){
		    nCommaFound++;
		    if(nCommaFound==(iRow+1)){
		      commaPos_end = commaPos;
		      break;
		    } 
		  } 
		  else break;
		} 
	      } 
	     
	      // Get category substring
	      cat_title = cat_title.substr(commaPos_begin, commaPos_end-commaPos_begin);

	      if( commaPos_begin==0 && 
		  commaPos_end==cat_title.size() && 
		  iRow>nCommaFound                  ) row_str += " & ";
	      else{
		row_str += " & ";
		row_str += cat_title;
		row_str += " ";
	      }

	    } // end loop over categories

	    header_str.push_back(row_str);
	    fprintf(f_out, "%s", row_str.c_str());
	    fprintf(f_out, "\\"); 
	    fprintf(f_out, "\\* \n");

	  } // end loop over commas, ie title rows

	} // end if maxCommas != 1

	fprintf(f_out, "\\hline \\hline \n");
	fprintf(f_out, "\\endfirsthead \n \n");

	// Header
	fprintf(f_out, "\\multicolumn{%d}{c}", nCol);
	fprintf(f_out, "{{\\bfseries \\tablename\\ \\thetable{} -- continued from previous page}}");
	fprintf(f_out, "\\");
	fprintf(f_out, "\\* \\hline \n");
	for(int iRow=0; iRow<(int)header_str.size(); iRow++){
	  fprintf(f_out, "%s", header_str[iRow].c_str());
	  fprintf(f_out, "\\"); 
	  fprintf(f_out, "\\* \n");
	}      
	fprintf(f_out, "\\hline \\hline \n");
	fprintf(f_out, "\\endhead \n \n");

	// Footer
	fprintf(f_out, "\\multicolumn{%d}{|r|}{{%s}}", nCol, "Continued on next page");
	fprintf(f_out, "\\"); 
	fprintf(f_out, "\\* \\hline \n");
	fprintf(f_out, "\\endfoot \n \n");

	// Last Foot
	//fprintf(f_out, "\\hline \n");
	fprintf(f_out, " \n");
	fprintf(f_out, "\\endlastfoot \n \n");
      

	//
	// Loop over Signal Samples
	//
	for(int iSig=0; iSig<(int)sigList.size(); iSig++){
	
	  sampleInfo::sampleUtil sample( sigList[iSig].first );

	  genClassyInfo::genClassyUtil genClassy( sigList[iSig].second );

	  TString f_input_name = f_input_dir;
	  f_input_name += "h__";
	  f_input_name += sample.label;
	  f_input_name += ".root";
	  f_input = new TFile( f_input_name.Data(), "read");

	  std::vector< std::pair< int, int > > massPtList;
	  if( sample.id==sampleInfo::k_T2tt ) massPtList = T2tt_list;

	  
	  //
	  // Loop over mass points
	  //
	  for(int iMassPt=0; iMassPt<(int)massPtList.size(); iMassPt++){

	    int mStop = massPtList[iMassPt].first;
	    int mLSP  = massPtList[iMassPt].second;
	
	    fprintf(f_out, "%s, mStop=%d, mLSP=%d ", sample.tex.c_str(), mStop, mLSP );

	    // Loop over category list
	    for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	    
	      categoryInfo::categoryUtil category( tableList[iTable][iCat] );
	    
	      std::string h_name = histogramInfo::getYieldHistoLabel( "yields", genClassy, recoClassyInfo::recoClassyUtil(recoClassyInfo::k_incl), systematic );
	      
	      double yield = 0.0;
	      double error = 0.0;
	      
	      TH3D *h_yield_sig = (TH3D*)f_input->Get(h_name.c_str());

	      int binX = h_yield_sig->GetXaxis()->FindBin(mStop);
	      int binY = h_yield_sig->GetYaxis()->FindBin(mLSP);
	      int binZ = h_yield_sig->GetZaxis()->FindBin(category.label.c_str());

	      yield = h_yield_sig->GetBinContent( binX,binY,binZ );
	      error = h_yield_sig->GetBinError( binX,binY,binZ );
	    
	      if(doRescale){
		yield *= rescale;
		error *= rescale;
	      }

	      if( yield == 0.0 ){
		fprintf(f_out, " & --- ");
	      }
	      else if( yield < 0.0 ){
		fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", yield, error);
	      }
	      else{
		fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
	      }
	      
	    } // end loop over categories

	    fprintf(f_out, "\\"); 
	    fprintf(f_out, "\\* \n");
	  
	  } // end loop over massPoints
	  
	  f_input->Close();
	  f_input->~TFile();

	} // end loop over samples
	
	if((int)sigList.size()>0) fprintf(f_out, "\\hline \\hline \n");
	

	//
	// Loop over Bkg samples
	//
	for(int iBkg=0; iBkg<(int)bkgList.size(); iBkg++){
	
	  sampleInfo::sampleUtil sample( bkgList[iBkg].first );

	  genClassyInfo::genClassyUtil genClassy( bkgList[iBkg].second );
	  
	  TString f_input_name = f_input_dir;
	  f_input_name += "h__";
	  f_input_name += sample.label;
	  if( useZeroedAMCNLO && sample.isAMCNLO ){
	    f_input_name += "_noNegYield";
	  }
	  f_input_name += ".root";
	  f_input = new TFile( f_input_name.Data(), "read");

	  if( genClassy.id == genClassyInfo::k_incl ) fprintf(f_out, "%s ", sample.tex.c_str() );
	  else fprintf(f_out, "%s,~%s", sample.tex.c_str(), genClassy.tex.c_str() );

	  // Loop over category list
	  for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	    
	    categoryInfo::categoryUtil category( tableList[iTable][iCat] );
	    
	    std::string h_name = histogramInfo::getYieldHistoLabel( "yields", genClassy, recoClassyInfo::recoClassyUtil(recoClassyInfo::k_incl), systematic );
	    
	    double yield = 0.0;
	    double error = 0.0;
	    
	    TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
	    yield = h_yield_bkg->GetBinContent( h_yield_bkg->GetXaxis()->FindBin(category.label.c_str()) );
	    error = h_yield_bkg->GetBinError( h_yield_bkg->GetXaxis()->FindBin(category.label.c_str()) );
	   
	    if(doRescale){
		yield *= rescale;
		error *= rescale;
	      }

	    if( yield == 0.0 ){
	      fprintf(f_out, " & --- ");
	    }
	    else if( yield < 0.0 ){
	      fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", yield, error);
	    }
	    else{
	      fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
	    }

	  } // end loop over categories
	  
	  fprintf(f_out, "\\"); 
	  fprintf(f_out, "\\* \n");
	  
	  f_input->Close();
	  f_input->~TFile();

	} // end loop over samples

	
	
	//
	//  Sum of All Background
	//
	TString f_input_name = f_input_dir;
	f_input_name += "h__";
	f_input_name += allBkg_util.label;
	f_input_name += ".root";
	f_input = new TFile( f_input_name.Data(), "read");

	fprintf(f_out, "%s ", allBkg_util.tex.c_str() );

	// Loop over category list
	for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	  
	  categoryInfo::categoryUtil category( tableList[iTable][iCat] );
	  
	  std::string h_name = histogramInfo::getYieldHistoLabel( "yields", genClassyInfo::k_incl, recoClassyInfo::k_incl, systematicList[iSys] );
	    
	  double yield = 0.0;
	  double error = 0.0;
	    
	  TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
	  yield = h_yield_bkg->GetBinContent( h_yield_bkg->GetXaxis()->FindBin(category.label.c_str()) );
	  error = h_yield_bkg->GetBinError( h_yield_bkg->GetXaxis()->FindBin(category.label.c_str()) );
	  
	  if(doRescale){
	    yield *= rescale;
	    error *= rescale;
	  }

	  if( yield == 0.0 ){
	    fprintf(f_out, " & --- ");
	  }
	  else if( yield < 0.0 ){
	    fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", yield, error);
	  }
	  else{
	    fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
	  }
	  
	} // end loop over categories
	
	fprintf(f_out, "\\"); 
	fprintf(f_out, "\\* \n");
	fprintf(f_out, "\\hline \\hline \n");

	f_input->Close();
	f_input->~TFile();


	//
	// Data
	//
	f_input_name = f_input_dir;
	f_input_name += "h__";
	f_input_name += data_util->label;
	f_input_name += ".root";
	f_input = new TFile( f_input_name.Data(), "read");

	fprintf(f_out, "%s ", data_util->tex.c_str() );

	// Loop over category list
	for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	  
	  categoryInfo::categoryUtil category( tableList[iTable][iCat] );
	  
	  std::string h_name = histogramInfo::getYieldHistoLabel( "yields", genClassyInfo::genClassyUtil(genClassyInfo::k_incl), recoClassyInfo::recoClassyUtil(recoClassyInfo::k_incl), systematicInfo::systematicUtil(systematicInfo::k_nominal) );
	    
	  double yield = 0.0;
	  double error = 0.0;
	    
	  TH1D *h_yield_data = (TH1D*)f_input->Get(h_name.c_str());
	  yield = h_yield_data->GetBinContent( h_yield_data->GetXaxis()->FindBin(category.label.c_str()) );
	  error = sqrt(yield);
	  
	  if(doRescale){
	    yield *= rescale;
	    error = sqrt(yield);
	  }
	  
	  if( yield == 0.0 ){
	    fprintf(f_out, " & --- ");
	  }
	  else if( yield < 0.0 ){
	    fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", yield, error);
	  }
	  else{
	    fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
	  }
	  
	} // end loop over categories
	
	fprintf(f_out, "\\"); 
	fprintf(f_out, "\\* \n");
	fprintf(f_out, "\\hline \\hline \n");

	f_input->Close();
	f_input->~TFile();

	

	//
	// Loop over Bkg samples, byGen
	//
	for(int iBkg=0; iBkg<(int)bkgList_byGen.size(); iBkg++){
	
	  sampleInfo::sampleUtil sample( bkgList_byGen[iBkg].first );

	  genClassyInfo::genClassyUtil genClassy( bkgList_byGen[iBkg].second );
	  
	  TString f_input_name = f_input_dir;
	  f_input_name += "h__";
	  f_input_name += sample.label;
	  if( useZeroedAMCNLO && sample.isAMCNLO ){
	    f_input_name += "_noNegYield";
	  }
	  f_input_name += ".root";
	  f_input = new TFile( f_input_name.Data(), "read");

	  fprintf(f_out, "%s ", genClassy.tex.c_str() );

	  // Loop over category list
	  for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	    
	    categoryInfo::categoryUtil category( tableList[iTable][iCat] );
	    
	    std::string h_name = histogramInfo::getYieldHistoLabel( "yields", genClassy, recoClassyInfo::recoClassyUtil(recoClassyInfo::k_incl), systematic );
	    
	    double yield = 0.0;
	    double error = 0.0;
	    
	    TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
	    yield = h_yield_bkg->GetBinContent( h_yield_bkg->GetXaxis()->FindBin(category.label.c_str()) );
	    error = h_yield_bkg->GetBinError( h_yield_bkg->GetXaxis()->FindBin(category.label.c_str()) );
	   
	    if(doRescale){
	      yield *= rescale;
	      error *= rescale;
	    }

	    if( yield == 0.0 ){
	      fprintf(f_out, " & --- ");
	    }
	    else if( yield < 0.0 ){
	      fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", yield, error);
	    }
	    else{
	      fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
	    }

	  } // end loop over categories
	  
	  fprintf(f_out, "\\"); 
	  fprintf(f_out, "\\* \n");
	  
	  f_input->Close();
	  f_input->~TFile();

	} // end loop over samples

	fprintf(f_out, "\\hline \n");


      	// End table
	fprintf(f_out, "\\end{longtable} \n");

	fprintf(f_out, "\n \n \n \n \n");
	fprintf(f_out, "\\pagebreak \n");
	fprintf(f_out, "\n \n \n \n \n");
      
      } // end loop over tableList

    } // end loop over reco classifications

  } // end loop over systematic list


  fprintf(f_out, "\\end{document} \n");

  
  fclose(f_out);


  return 0;
}
