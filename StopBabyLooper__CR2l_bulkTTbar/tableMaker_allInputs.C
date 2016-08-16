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

int tableMaker_allInputs( std::string f_input_dir="Histos/Nominal/", std::string f_out_name="Output/Tables/yields_allInputs.tex", bool useZeroedAMCNLO=true ){

  // Make a tex document where each page will have a table
  //   This table will be for a given systematic. 
  //   It will show the yields for a set of catogries in rows
  //      and columns will be the input samples split by gen and reco
  //      classifications

  
  //
  // Analyzer Type
  //
  analyzerInfo::ID analysis = analyzerInfo::k_CR2l_bulkTTbar;

  //
  // Sample List
  //
  sampleInfo::vect_id sampleList;
  sampleList.push_back( sampleInfo::k_diLepton_2016B );
  sampleList.push_back( sampleInfo::k_allBkg );
  sampleList.push_back( sampleInfo::k_ttbar );
  //sampleList.push_back( sampleInfo::k_ttbar_powheg_pythia8_ext3 );
  //sampleList.push_back( sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 );
  sampleList.push_back( sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1);
  sampleList.push_back( sampleInfo::k_singleT );
  sampleList.push_back( sampleInfo::k_singleT_tW );
  sampleList.push_back( sampleInfo::k_t_tW_5f_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_t_tbarW_5f_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_singleT_non_tW );
  sampleList.push_back( sampleInfo::k_t_sch_4f_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_t_tch_4f_powheg_pythia8 );
  //sampleList.push_back( sampleInfo::k_tbar_tch_4f_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_VJets );
  sampleList.push_back( sampleInfo::k_DYJetsToLL );
  sampleList.push_back( sampleInfo::k_DYJetsToLL_m10To50_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_DYJetsToLL_m50_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT600ToInf_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8_ext1 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8_ext1 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8_ext1 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_rare );
  sampleList.push_back( sampleInfo::k_diBoson );
  sampleList.push_back( sampleInfo::k_WW );
  sampleList.push_back( sampleInfo::k_WWTo2l2Nu_powheg );
  sampleList.push_back( sampleInfo::k_WWToLNuQQ_powheg );
  sampleList.push_back( sampleInfo::k_WZ );
  sampleList.push_back( sampleInfo::k_WZTo3LNu_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_WZTo2L2Q_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_WZTo1LNu2Q_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_WZTo1L3Nu_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZ );
  //sampleList.push_back( sampleInfo::k_ZZTo4L_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2L2Q_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2L2Nu_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2Q2Nu_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_TTV );
  sampleList.push_back( sampleInfo::k_TTW );
  sampleList.push_back( sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_TTWJetsToQQ_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_TTZ );
  sampleList.push_back( sampleInfo::k_ttZJets_13TeV_madgraphMLM );
  sampleList.push_back( sampleInfo::k_TTZToQQ_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_TTZToLLNuNu_m10_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_tZq );
  //sampleList.push_back( sampleInfo::k_tZq_ll_4f_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_tZq_nunu_4f_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_T2tt );
    

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
  // Gen Classy List
  //
  genClassyInfo::vect_util genClassyList;
  genClassyList = genClassyInfo::getGenClassyList( analysis );
  
  //
  // Reco Classy lsit
  //
  recoClassyInfo::vect_util recoClassyList;
  recoClassyList = recoClassyInfo::getRecoClassyList( analysis );

  //
  // Category List
  //
  std::vector< categoryInfo::vect_id > tableList;
  categoryInfo::vect_id catList;

  catList.push_back( categoryInfo::k_incl );
  catList.push_back( categoryInfo::k_ge1btags_ge50met );
  catList.push_back( categoryInfo::k_ge2btags_ge50met );
  tableList.push_back( catList );

  catList.clear();
  catList.push_back( categoryInfo::k_ge1btags_ge50met );
  catList.push_back( categoryInfo::k_ge1btags_ge100met );
  catList.push_back( categoryInfo::k_ge1btags_ge150met );
  catList.push_back( categoryInfo::k_ge1btags_ge200met );
  tableList.push_back( catList );

  catList.clear();
  catList.push_back( categoryInfo::k_ge2btags_ge50met );
  catList.push_back( categoryInfo::k_ge2btags_ge100met );
  catList.push_back( categoryInfo::k_ge2btags_ge150met );
  catList.push_back( categoryInfo::k_ge2btags_ge200met );
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

    for(int iReco=0; iReco<(int)recoClassyList.size(); iReco++){

      for(int iTable=0; iTable<(int)tableList.size(); iTable++){

	// Get number of collumns for table - ie categories
	int nCol = 2 + (int)tableList[iTable].size();
	fprintf(f_out, "\\begin{longtable}{|l|c|"); // samples+classifications
	for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	  fprintf(f_out,"c|");
	}
	fprintf(f_out, "} \n \n");

	// Top Title
	std::string table_title = "";
	table_title += recoClassyList[iReco].tex;
	table_title += ",~";
	table_title += systematicList[iSys].tex;
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

	  std::string row_str = "Sample & Classification ";
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
	    
	      if( iRow==floor(maxRows/2.0) && iCat==0 ) row_str += "Sample & Classification ";
	      else if( iCat==0 ) row_str += " & ";
	    
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
      

	// Loop over samples
	for(int iSample=0; iSample<(int)sampleList.size(); iSample++){
	
	  sampleInfo::sampleUtil sample( sampleList[iSample] );
	
	  TString f_input_name = f_input_dir;
	  f_input_name += "h__";
	  f_input_name += sample.label;
	  if( useZeroedAMCNLO && sample.isAMCNLO ){
	    f_input_name += "_noNegYield";
	  }
	  f_input_name += ".root";
	  TFile *f_input = new TFile( f_input_name.Data(), "read");

	  // If signal scan
	  if( sample.isSignalScan ){

	    std::vector< std::pair< int, int > > massPtList;
	  
	    if( sample.id==sampleInfo::k_T2tt ) massPtList = T2tt_list;

	    for(int iMassPt=0; iMassPt<(int)massPtList.size(); iMassPt++){

	      int mStop = massPtList[iMassPt].first;
	      int mLSP  = massPtList[iMassPt].second;
		
	      fprintf(f_out, "\\multirow{%d}{*}{%s, mStop=%d, mLSP=%d}", (int)genClassyList.size(), sample.tex.c_str(), mStop, mLSP );
	    
	      // Loop over gen classifications
	      for(int iGen=0; iGen<(int)genClassyList.size(); iGen++){
	      
		if( sample.isData && genClassyList[iGen].id!=genClassyInfo::k_incl ) continue;
	      
		fprintf(f_out, " & %s ", genClassyList[iGen].tex.c_str() );
	      
		// Loop over category list
		for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
		
		  categoryInfo::categoryUtil category( tableList[iTable][iCat] );
		
		  std::string h_name = histogramInfo::getYieldHistoLabel( "yields", genClassyList[iGen], recoClassyList[iReco], systematicList[iSys] );
		
		  double yield = 0.0;
		  double error = 0.0;
		
		  TH3D *h_yield = (TH3D*)f_input->Get(h_name.c_str());

		  int binX = h_yield->GetXaxis()->FindBin(mStop);
		  int binY = h_yield->GetYaxis()->FindBin(mLSP);
		  int binZ = h_yield->GetZaxis()->FindBin(category.label.c_str());
		  yield = h_yield->GetBinContent( binX,binY,binZ );
		  error = h_yield->GetBinError( binX,binY,binZ );
		
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
	      
	      } // end loop over gen classifications	    

	      fprintf(f_out, "\\hline \n");

	    } // end loop over mass points
	  
	  
	  }
	  // If not signal scan
	  else{
	
	    if( sample.isData ) fprintf(f_out, "\\multirow{%d}{*}{%s}", 1, sample.tex.c_str() );
	    else                fprintf(f_out, "\\multirow{%d}{*}{%s}", (int)genClassyList.size(), sample.tex.c_str() );

	  
	    // Loop over gen classifications
	    for(int iGen=0; iGen<(int)genClassyList.size(); iGen++){
	    
	      if( sample.isData && genClassyList[iGen].id!=genClassyInfo::k_incl ) continue;
	    
	      fprintf(f_out, " & %s ", genClassyList[iGen].tex.c_str() );
	    
	      // Loop over category list
	      for(int iCat=0; iCat<(int)tableList[iTable].size(); iCat++){
	      
		categoryInfo::categoryUtil category( tableList[iTable][iCat] );
	      
		std::string h_name = histogramInfo::getYieldHistoLabel( "yields", genClassyList[iGen], recoClassyList[iReco], systematicList[iSys] );
	      
		double yield = 0.0;
		double error = 0.0;
	      
		TH1D *h_yield = (TH1D*)f_input->Get(h_name.c_str());
		yield = h_yield->GetBinContent( h_yield->GetXaxis()->FindBin(category.label.c_str()) );
		error = h_yield->GetBinError( h_yield->GetXaxis()->FindBin(category.label.c_str()) );
	      
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
	    
	    } // end loop over gen classifications	    


	    if( sample.isData ) fprintf(f_out, "\\hline \\hline \n");
	    else fprintf(f_out, "\\hline \n");
	
	  } // end if not signal scan
		
	  f_input->Close();
	  f_input->~TFile();

	} // end loop over samples
      

	// End table
	fprintf(f_out, "\\end{longtable} \n");

	fprintf(f_out, "\n \n \n \n \n");
	fprintf(f_out, "\\pagebreak \n");
	fprintf(f_out, "\n \n \n \n \n");
      
      } // end loop over tableList

    } // end loop ove recoClassyList

  } // end loop over systematic list


  fprintf(f_out, "\\end{document} \n");

  
  fclose(f_out);


  return 0;
}
