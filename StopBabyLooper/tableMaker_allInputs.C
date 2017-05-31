#include "stopBabyLooper.h"

void tableMaker_allInputs( std::string f_input_dir, std::string f_out_name_base, bool useZeroedAMCNLO ){

  // Make a tex document where each page will have a table
  //   This table will be for a given systematic. 
  //   It will show the yields for a set of catogries in rows
  //      and columns will be the input samples split by gen and reco
  //      classifications

	std::cout << "Making yield tables..." << std::endl;


  //
  // Sample List
  //
  sampleInfo::vect_id sampleList;
  
  // Get List from Looper
  //sampleList = sampleInfo::getSampleList_SR(); // only gives unmerged samples
  
  // Data
  //sampleList.push_back( sampleInfo::k_single_lepton_met );
  sampleList.push_back( sampleInfo::k_allBkg );
  sampleList.push_back( sampleInfo::k_ttbar );
  //sampleList.push_back( sampleInfo::k_ttbar_powheg_pythia8_ext4 );
  sampleList.push_back( sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 );
  sampleList.push_back( sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 );
  sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8);
  sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1);
  sampleList.push_back( sampleInfo::k_singleT );
  sampleList.push_back( sampleInfo::k_singleT_tW );
  sampleList.push_back( sampleInfo::k_t_tW_5f_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_t_tbarW_5f_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_singleT_non_tW );
  sampleList.push_back( sampleInfo::k_t_sch_4f_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_t_tch_4f_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_tbar_tch_4f_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_VJets );
  sampleList.push_back( sampleInfo::k_DYJetsToLL );
  sampleList.push_back( sampleInfo::k_DYJetsToLL_m10To50_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_DYJetsToLL_m50_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_WJetsToLNu );
  sampleList.push_back( sampleInfo::k_WNJetsToLNu_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W1JetsToLNu_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W2JetsToLNu_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W3JetsToLNu_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W4JetsToLNu_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W1JetsToLNu_NuPt200_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W2JetsToLNu_NuPt200_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W3JetsToLNu_NuPt200_madgraph_pythia8 );
  sampleList.push_back( sampleInfo::k_W4JetsToLNu_NuPt200_madgraph_pythia8 );  
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT100ToInf_madgraph_pythia8 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8_ext1 );
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
  sampleList.push_back( sampleInfo::k_ZZTo4L_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2L2Q_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2L2Nu_powheg_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2Q2Nu_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_TTV );
  sampleList.push_back( sampleInfo::k_TTW );
  sampleList.push_back( sampleInfo::k_ttWJets_13TeV_madgraphMLM );
  //sampleList.push_back( sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_TTWJetsToQQ_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_TTZ );
  sampleList.push_back( sampleInfo::k_ttZJets_13TeV_madgraphMLM );
  //sampleList.push_back( sampleInfo::k_TTZToQQ_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_TTZToLLNuNu_m10_amcnlo_pythia8 );
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
  // Category List
  //
  std::vector< std::vector<yieldHelper> > tableList_bulk, tableList_corridor;
  std::vector<yieldHelper> catList;
  yieldHelper cat;
  

  
  //
  // Yields, dev ext30fb, mlb with tight bTagging
  //

  // Region A, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 1; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 2; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 3; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 4; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$MET>600$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  // Region B, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 5; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 6; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$450<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 7; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$MET>600$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );
  
  // Region C, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 8; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 9; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 10; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 11; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 12; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$MET>650$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  // Region D, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 13; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 14; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 15; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 16; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$MET>550$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  // Region E, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 17; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 18; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$350<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 19; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$MET>550$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  // Region F, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 20; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 21; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$MET>450$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );
  
  // Region G, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 22; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 23; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 24; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 25; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$MET>600$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  // Region H, mlb and tight bTagging
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 26; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 27; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$MET>450$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );


  
  
  //
  // Yields, Top Corridor
  //
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 1; cat.tex = "top~corridor,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 2; cat.tex = "top~corridor,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 3; cat.tex = "top~corridor,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 4; cat.tex = "top~corridor,~$MET>550$";
  catList.push_back( cat );
  tableList_corridor.push_back( catList );


  //
  // Signal and Control Regions
  //
  std::vector<std::pair<std::string,std::vector<std::vector<yieldHelper> > > > regionList;
  regionList.push_back( std::make_pair("SR_bulk", tableList_bulk) );
  regionList.push_back( std::make_pair("SR_corridor", tableList_corridor) );
  regionList.push_back( std::make_pair("CR0b_bulk", tableList_bulk) );
  regionList.push_back( std::make_pair("CR0b_highMlb_bulk", tableList_bulk) );
  regionList.push_back( std::make_pair("CR0b_corridor", tableList_corridor) );
  regionList.push_back( std::make_pair("CR2l_bulk", tableList_bulk) );
  regionList.push_back( std::make_pair("CR2l_corridor", tableList_corridor) );
  

  //
  // Gen Classy List
  //
  genClassyInfo::vect_util genClassyList_mc;
  for(int iGen=0; iGen<genClassyInfo::k_nGenClassy; iGen++){
    genClassyList_mc.push_back( genClassyInfo::Util(genClassyInfo::ID(iGen)) );
  }
  
  genClassyInfo::vect_util genClassyList_data;
  genClassyList_data.push_back( genClassyInfo::Util(genClassyInfo::k_incl) );
  
  
  //
  // Systematic List
  //
  sysInfo::vect_util systematicList;
  systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) ); 
  systematicList.push_back( sysInfo::Util(sysInfo::k_JESUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_JESDown) );


    
  //
  // Make yield tables
  //
  for(int iRegion=0; iRegion<(int)regionList.size(); iRegion++) {

    for(int iSys=0; iSys<(int)systematicList.size(); iSys++) {

	    std::vector< std::vector<yieldHelper> > iTableList = regionList[iRegion].second;

	// Open output file
	std::string f_out_name = f_out_name_base;
	f_out_name += "__region_";
	f_out_name += regionList[iRegion].first;
	f_out_name += "__systematic_";
	f_out_name += systematicList[iSys].label;
	f_out_name += ".tex";

	FILE *f_out;
	std::cout << "    Output written to: " << std::endl;
	std::cout << "      " << f_out_name << std::endl << std::endl;
	f_out = fopen( f_out_name.c_str(), "w" );
	
	// Print header info
	fprintf(f_out, "\\documentclass{article}\n");
	fprintf(f_out, "\\usepackage[landscape]{geometry}\n");
	fprintf(f_out, "\\usepackage{multirow}\n");
	fprintf(f_out, "\\usepackage{color}\n");
	fprintf(f_out, "\\usepackage{longtable}\n\n");
	fprintf(f_out, "\\begin{document}\n");
	fprintf(f_out, "\\tiny\n");
	fprintf(f_out, "\n\n\n\n");


	for(int iTable=0; iTable<(int)iTableList.size(); iTable++){
	
	  std::vector<yieldHelper> iCatList = iTableList[iTable];

	  // Get number of columns for table - ie categories
	  int nCol = 2 + (int)iCatList.size();
	  fprintf(f_out, "\\begin{longtable}{|l|c|"); // samples+classifications
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	    fprintf(f_out,"c|");
	  }
	  fprintf(f_out, "} \n \n");
	
	  // Top Title
	  TString regionListTitle = regionList[iRegion].first;
	  regionListTitle.ReplaceAll("_", " ");

	  std::string table_title = "";
	  table_title += regionListTitle;
	  table_title += ", ";
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
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	    std::string cat_title = iCatList[iCat].tex;
	    int nCommas = 0;
	    for(int iChar=0; iChar<(int)cat_title.size(); iChar++){
	      if( cat_title.compare(iChar,1,",")==0 ) nCommas++;
	    }
	    maxRows = std::max( maxRows, nCommas+1 );
	  }
	
	  if( maxRows == 1 ){
	  
	    std::string row_str = "Sample & Classification ";
	    for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	      std::string cat_title = iCatList[iCat].tex;
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
	      for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	      
		if( iRow==floor(maxRows/2.0) && iCat==0 ) row_str += "Sample & Classification ";
		else if( iCat==0 ) row_str += " & ";
	      
		std::string cat_title = iCatList[iCat].tex;
	      
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
	  
	    genClassyInfo::vect_util genClassyList = genClassyList_mc;
	    if( sample.isData ) genClassyList = genClassyList_data;
	  
	    TString f_input_name = f_input_dir;
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
		
		  genClassyInfo::Util genClassy = genClassyList[iGen];
		
		  if( sample.isData && genClassy.id!=genClassyInfo::k_incl ) continue;
		
		  fprintf(f_out, " & %s ", genClassy.tex.c_str() );
		
		  // Loop over category list
		  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
		  
		    std::string h_name = iCatList[iCat].histName;
		    h_name += "__";
		    h_name += regionList[iRegion].first;
		    h_name += "__genClassy_";
		    h_name += genClassy.label;
		    h_name += "__systematic_";
		    h_name += systematicList[iSys].label;
		  
		    double yield = 0.0;
		    double error = 0.0;
		  
		    TH3D *h_yield = (TH3D*)f_input->Get(h_name.c_str());
		    if(!h_yield) cout << "BAD HISTOGRAM: " << h_name << ", from File: " << f_input_name << endl << "    Line=" << __LINE__ << endl;
		  
		    int binX = h_yield->GetXaxis()->FindBin(mStop);
		    int binY = h_yield->GetYaxis()->FindBin(mLSP);
		    int binZ = iCatList[iCat].binNumber;
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
	      
		genClassyInfo::Util genClassy = genClassyList[iGen];
	      
		if( sample.isData && genClassy.id!=genClassyInfo::k_incl ) continue;
	      
		fprintf(f_out, " & %s ", genClassy.tex.c_str() );
	      
		// Loop over category list
		for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
		
		  std::string h_name = iCatList[iCat].histName;
		  h_name += "__";
		  h_name += regionList[iRegion].first;
		  h_name += "__genClassy_";
		  h_name += genClassy.label;
		  h_name += "__systematic_";
		  h_name += systematicList[iSys].label;
		
		  double yield = 0.0;
		  double error = 0.0;
		
		  TH1D *h_yield = (TH1D*)f_input->Get(h_name.c_str());
		  if(!h_yield) cout << "BAD HISTOGRAM: " << h_name << ", from File: " << f_input_name << endl << "    Line=" << __LINE__ << endl;
		  yield = h_yield->GetBinContent( iCatList[iCat].binNumber );
		  error = h_yield->GetBinError( iCatList[iCat].binNumber );
		
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
    

	fprintf(f_out, "\\end{document} \n");
	fclose(f_out);
      
    } // end loop over systematic list
    
  } // end loop over signal and control regions

    

  return;
}
