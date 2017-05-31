#include "stopBabyLooper.h"

void tableMaker_summedInputs( std::string f_input_dir, std::string f_out_name_base, bool useZeroedAMCNLO ){

  // Make a tex document where each page will have a table
  //   This table will be for a given systematic. 
  //   It will show the yields for a set of catogries in rows
  //      and columns will be the input samples split by gen and reco
  //      classifications

	std::cout << "Making yield tables..." << std::endl;
  
  //
  // Configuration Variables
  //
  bool blindSR = false;

  bool usePsuedoData = false;

  bool doRescale = false;
  double rescale = 1.0; // use lumi from stopCORE
  //double rescale = 10.0/35.867; // rescale to new lumi

  
  //
  // Sample List
  //
  TFile *f_input = NULL;

  sampleInfo::sampleUtil *data_util = NULL; // Set inside regionList loop in case of blind SR
  
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
  sample.second = genClassyInfo::k_ge2lep;
  bkgList_byGen.push_back(sample);

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ee1lep_fromW;
  bkgList_byGen.push_back(sample);

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ee1lep_fromTop;
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

    
  // Yields, dev ext30fb, inclusive in mlb
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 43; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 44; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 45; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 46; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$MET>600$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 47; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 48; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 49; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$MET>600$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 51; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 52; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 53; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 54; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 55; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$MET>650$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 56; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$MET>550$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 58; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 59; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$350<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 60; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$MET>550$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 61; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 62; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$MET>450$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );
  
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 64; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 65; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 66; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 67; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$MET>600$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 68; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 69; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$MET>450$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  // Yields, dev ext30fb, mlb and tight bTagging, 150<met<250 CR
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 70; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 71; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 72; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 73; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 74; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 75; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 76; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 77; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$150<MET<250$";
  catList.push_back( cat );
  tableList_bulk.push_back( catList );

  // Yields, dev ext30fb, mlb and tight bTagging, 150<met<250 CR
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 42; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 50; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 57; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$150<MET<250$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 63; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$150<MET<250$";
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

    // Determine if data or psuedodata
    if(usePsuedoData){
      data_util = new sampleInfo::sampleUtil( sampleInfo::k_allBkg );
    }
    else if( blindSR && TString(regionList.at(iRegion).first).Contains("SR") ){
      data_util = new sampleInfo::sampleUtil( sampleInfo::k_allBkg );
    }
    else{
      data_util = new sampleInfo::sampleUtil( sampleInfo::k_single_lepton_met );
    }

    // Loop over systematics
    for(int iSys=0; iSys<(int)systematicList.size(); iSys++){

      sysInfo::Util systematic(systematicList[iSys]);
      
      std::vector< std::vector<yieldHelper> > iTableList = regionList.at(iRegion).second;

	// Open output file
	std::string f_out_name = f_out_name_base;
	f_out_name += "__region_";
	f_out_name += regionList.at(iRegion).first;
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
	

	// Table Title
	TString regionListTitle = regionList.at(iRegion).first;
	regionListTitle.ReplaceAll("_", " ");

	std::string table_title = "";
	table_title += regionListTitle;
	table_title += ", ";
	table_title += systematicList[iSys].tex;
	table_title += " Systematic, Yield Table for ";
	
	TString hName_temp = iTableList[0][0].histName;
	hName_temp.ReplaceAll("h_","");
	hName_temp.ReplaceAll("_"," ");
	table_title += hName_temp;
	

	//
	// Summary Table
	//
	fprintf(f_out, "\\begin{longtable}{|l|"); // category
	for(int iGen=0; iGen<(int)bkgList_byGen.size(); iGen++){ fprintf(f_out, "c "); } // genBkg
	fprintf(f_out, "c|c|c|} \n \n"); // allBkg & data & data/mc

	// First Header
	fprintf(f_out, "\\multicolumn{%d}{c}{ %s }", (int)bkgList_byGen.size()+4, table_title.c_str());
	fprintf(f_out, "\\"); 
	fprintf(f_out, "\\* \\hline \n");

	fprintf(f_out, "Category ");
	for(int iGen=0; iGen<(int)bkgList_byGen.size(); iGen++){
	  genClassyInfo::Util genClassy( bkgList_byGen[iGen].second );
	  fprintf(f_out, " & %s", genClassy.tex.c_str() );
	}
	fprintf(f_out, " & Sum Bkg. & Data & Data/MC ");
	fprintf(f_out, "\\");
	fprintf(f_out, "\\* \n");

	fprintf(f_out, "\\hline \\hline \n");
	fprintf(f_out, "\\endfirsthead \n \n");
	
	// Header
	fprintf(f_out, "\\multicolumn{%d}{c}", (int)bkgList_byGen.size()+4);
	fprintf(f_out, "{{\\bfseries \\tablename\\ \\thetable{} -- continued from previous page}}");
	fprintf(f_out, "\\");
	fprintf(f_out, "\\* \\hline \n");
	fprintf(f_out, "Category ");
	for(int iGen=0; iGen<(int)bkgList_byGen.size(); iGen++){
	  genClassyInfo::Util genClassy( bkgList_byGen[iGen].second );
	  fprintf(f_out, " & %s", genClassy.tex.c_str() );
	}
	fprintf(f_out, " & Data & Data/MC ");
	fprintf(f_out, "\\"); 
	fprintf(f_out, "\\* \n");
	fprintf(f_out, "\\hline \\hline \n");
	fprintf(f_out, "\\endhead \n \n");
	
	// Footer
	fprintf(f_out, "\\multicolumn{%d}{|r|}{{%s}}", (int)bkgList_byGen.size()+4, "Continued on next page");
	fprintf(f_out, "\\"); 
	fprintf(f_out, "\\* \\hline \n");
	fprintf(f_out, "\\endfoot \n \n");
	
	// Last Foot
	fprintf(f_out, " \n");
	fprintf(f_out, "\\endlastfoot \n \n");
	
	for(int iTable=0; iTable<(int)iTableList.size(); iTable++){
	  std::vector<yieldHelper> iCatList = iTableList[iTable];
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	    fprintf(f_out, "%s ", iCatList[iCat].tex.c_str());

	    double sumBkg=0.0, errBkg=0.0;
	    for(int iGen=0; iGen<(int)bkgList_byGen.size(); iGen++){
	      sampleInfo::sampleUtil sample( bkgList_byGen[iGen].first );
	      genClassyInfo::Util genClassy( bkgList_byGen[iGen].second );

	      TString f_input_name = f_input_dir;
	      f_input_name += sample.label;
	      if( useZeroedAMCNLO && sample.isAMCNLO ){
		f_input_name += "_noNegYield";
	      }
	      f_input_name += ".root";
	      f_input = new TFile( f_input_name.Data(), "read");

	      std::string h_name = iCatList[iCat].histName;
	      h_name += "__";
	      h_name += regionList.at(iRegion).first;
	      h_name += "__genClassy_";
	      h_name += genClassy.label;
	      h_name += "__systematic_";
	      h_name += systematicList[iSys].label;

	      double yield = 0.0;
	      double error = 0.0;
	    
	      TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
	      yield = h_yield_bkg->GetBinContent( iCatList[iCat].binNumber );
	      error = h_yield_bkg->GetBinError( iCatList[iCat].binNumber );
	   
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

	      if( yield>=0.0 ) sumBkg += yield;
	      if( error>=0.0 ) errBkg += pow(error,2);
	      
	      f_input->Close();

	    } // end loop over gen categories

	    if(errBkg>=0.0) errBkg = sqrt(errBkg);
	    
	    fprintf(f_out, " & %.2f $\\pm$ %.2f ", sumBkg, errBkg);

	    TString f_input_name = f_input_dir;
	    f_input_name += data_util->label;
	    f_input_name += ".root";
	    f_input = new TFile( f_input_name.Data(), "read");

	    genClassyInfo::Util genClassy_data(genClassyInfo::k_incl);
	    sysInfo::Util sysInfo_data(sysInfo::k_nominal);

	    std::string h_name = iCatList[iCat].histName;
	    h_name += "__";
	    h_name += regionList.at(iRegion).first;
	    h_name += "__genClassy_";
	    h_name += genClassy_data.label;
	    h_name += "__systematic_";
	    h_name += sysInfo_data.label;
	    
	    double yield = 0.0;
	    double error = 0.0;
	    
	    TH1D *h_yield_data = (TH1D*)f_input->Get(h_name.c_str());
	    yield = h_yield_data->GetBinContent( iCatList[iCat].binNumber );
	    error = sqrt(yield);
	  
	    if(doRescale){
	      yield *= rescale;
	      error = sqrt(yield);
	    }
	    
	    fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
	    fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield/sumBkg, (yield/sumBkg)*sqrt(pow(errBkg/sumBkg,2)+pow(error/yield,2)) );

	    f_input->Close();

	    fprintf(f_out, "\\");
	    fprintf(f_out, "\\* \n");
	    
	  } // end loop over table of categories

	  fprintf(f_out, "\\hline \n");

	} // end loop over set of tables
	
	// End table
	fprintf(f_out, "\\end{longtable} \n");
	fprintf(f_out, "\n \n \n \n \n");
	fprintf(f_out, "\\pagebreak \n");
	fprintf(f_out, "\n \n \n \n \n");
      
	


	//
	// Tables for sets of categories
	//
	for(int iTable=0; iTable<(int)iTableList.size(); iTable++){

	  std::vector<yieldHelper> iCatList = iTableList[iTable];
      	  
	  // Get number of collumns for table - ie categories
	  int nCol = 1 + (int)iCatList.size();
	  fprintf(f_out, "\\begin{longtable}{|l|"); // samples
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	    fprintf(f_out,"c|");
	  }
	  fprintf(f_out, "} \n \n");

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

	    std::string row_str = "Sample ";
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
	    
		if( iRow==floor(maxRows/2.0) && iCat==0 ) row_str += "Sample ";
		else if( iCat==0 ) row_str += " ";
	    
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
	  fprintf(f_out, " \n");
	  fprintf(f_out, "\\endlastfoot \n \n");
      

	  //
	  // Loop over Signal Samples
	  //
	  for(int iSig=0; iSig<(int)sigList.size(); iSig++){
	
	    sampleInfo::sampleUtil sample( sigList[iSig].first );

	    genClassyInfo::Util genClassy( sigList[iSig].second );

	    TString f_input_name = f_input_dir;
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
	      for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
		
		std::string h_name = iCatList[iCat].histName;
		h_name += "__";
		h_name += regionList.at(iRegion).first;
		h_name += "__genClassy_";
		h_name += genClassy.label;
		h_name += "__systematic_";
		h_name += systematicList[iSys].label;
	      
		double yield = 0.0;
		double error = 0.0;
	      
		TH3D *h_yield_sig = (TH3D*)f_input->Get(h_name.c_str());

		int binX = h_yield_sig->GetXaxis()->FindBin(mStop);
		int binY = h_yield_sig->GetYaxis()->FindBin(mLSP);
		int binZ = iCatList[iCat].binNumber;

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

	    genClassyInfo::Util genClassy( bkgList[iBkg].second );
	  
	    TString f_input_name = f_input_dir;
	    f_input_name += sample.label;
	    if( useZeroedAMCNLO && sample.isAMCNLO ){
	      f_input_name += "_noNegYield";
	    }
	    f_input_name += ".root";
	    f_input = new TFile( f_input_name.Data(), "read");

	    if( genClassy.id == genClassyInfo::k_incl ) fprintf(f_out, "%s ", sample.tex.c_str() );
	    else fprintf(f_out, "%s,~%s", sample.tex.c_str(), genClassy.tex.c_str() );

	    // Loop over category list
	    for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	  
	      std::string h_name = iCatList[iCat].histName;
	      h_name += "__";
	      h_name += regionList.at(iRegion).first;
	      h_name += "__genClassy_";
	      h_name += genClassy.label;
	      h_name += "__systematic_";
	      h_name += systematicList[iSys].label;
	      
	      double yield = 0.0;
	      double error = 0.0;
	    
	      TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
	      yield = h_yield_bkg->GetBinContent( iCatList[iCat].binNumber );
	      error = h_yield_bkg->GetBinError( iCatList[iCat].binNumber );
	   
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

	  fprintf(f_out, "\\hline \\hline \n");

	
	  //
	  //  Sum of All Background
	  //
	  TString f_input_name = f_input_dir;
	  f_input_name += allBkg_util.label;
	  f_input_name += ".root";
	  f_input = new TFile( f_input_name.Data(), "read");

	  fprintf(f_out, "%s ", allBkg_util.tex.c_str() );

	  // Loop over category list
	  vector<double> allBkg_yield, allBkg_error;
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	  
	    genClassyInfo::Util genClassy_allBkg(genClassyInfo::k_incl);

	    std::string h_name = iCatList[iCat].histName;
	    h_name += "__";
	    h_name += regionList.at(iRegion).first;
	    h_name += "__genClassy_";
	    h_name += genClassy_allBkg.label;
	    h_name += "__systematic_";
	    h_name += systematicList[iSys].label;

	    double yield = 0.0;
	    double error = 0.0;
	    
	    TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
	    yield = h_yield_bkg->GetBinContent( iCatList[iCat].binNumber );
	    error = h_yield_bkg->GetBinError( iCatList[iCat].binNumber );
	  
	    if(doRescale){
	      yield *= rescale;
	      error *= rescale;
	    }

	    allBkg_yield.push_back(yield);
	    allBkg_error.push_back(error);


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
	  //fprintf(f_out, "\\hline \\hline \n");
	  
	  f_input->Close();
	  f_input->~TFile();


	  //
	  // Data
	  //
	  f_input_name = f_input_dir;
	  f_input_name += data_util->label;
	  f_input_name += ".root";
	  f_input = new TFile( f_input_name.Data(), "read");

	  fprintf(f_out, "%s ", data_util->tex.c_str() );

	  // Loop over category list
	  vector<double> data_yield, data_error;
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){

	    genClassyInfo::Util genClassy_data(genClassyInfo::k_incl);
	    sysInfo::Util sysInfo_data(sysInfo::k_nominal);

	    std::string h_name = iCatList[iCat].histName;
	    h_name += "__";
	    h_name += regionList.at(iRegion).first;
	    h_name += "__genClassy_";
	    h_name += genClassy_data.label;
	    h_name += "__systematic_";
	    h_name += sysInfo_data.label;

	    double yield = 0.0;
	    double error = 0.0;
	    
	    TH1D *h_yield_data = (TH1D*)f_input->Get(h_name.c_str());
	    yield = h_yield_data->GetBinContent( iCatList[iCat].binNumber );
	    error = sqrt(yield);
	  
	    if(doRescale){
	      yield *= rescale;
	      error = sqrt(yield);
	    }

	    data_yield.push_back(yield);
	    data_error.push_back(error);
	  	  
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
	  //fprintf(f_out, "\\hline \\hline \n");

	  f_input->Close();
	  f_input->~TFile();

	
	  //
	  // Calc Data/MC
	  //
	  fprintf(f_out, "Data/MC " );
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	  
	    double ratio_val = 0.0;
	    double ratio_err = 0.0;

	    if( allBkg_yield[iCat]>0.0 ) ratio_val = data_yield[iCat]/allBkg_yield[iCat];
	    if( allBkg_yield[iCat]>0.0 && data_yield[iCat]>0.0 ) ratio_err = ratio_val*sqrt( pow(allBkg_error[iCat]/allBkg_yield[iCat],2) + pow(data_error[iCat]/data_yield[iCat],2) );

	    if( ratio_val == 0.0 ){
	      fprintf(f_out, " & --- ");
	    }
	    else if( ratio_val < 0.0 ){
	      fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", ratio_val, ratio_err);
	    }
	    else{
	      fprintf(f_out, " & %.2f $\\pm$ %.2f ", ratio_val, ratio_err);
	    }

	  }

	  fprintf(f_out, "\\"); 
	  fprintf(f_out, "\\* \n");
	  fprintf(f_out, "\\hline \\hline \n");

	

	  //
	  // Loop over Bkg samples, byGen
	  //
	  for(int iBkg=0; iBkg<(int)bkgList_byGen.size(); iBkg++){
	
	    sampleInfo::sampleUtil sample( bkgList_byGen[iBkg].first );

	    genClassyInfo::Util genClassy( bkgList_byGen[iBkg].second );
	  
	    TString f_input_name = f_input_dir;
	    f_input_name += sample.label;
	    if( useZeroedAMCNLO && sample.isAMCNLO ){
	      f_input_name += "_noNegYield";
	    }
	    f_input_name += ".root";
	    f_input = new TFile( f_input_name.Data(), "read");

	    fprintf(f_out, "%s ", genClassy.tex.c_str() );

	    // Loop over category list
	    for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	    
	      std::string h_name = iCatList[iCat].histName;
	      h_name += "__";
	      h_name += regionList.at(iRegion).first;
	      h_name += "__genClassy_";
	      h_name += genClassy.label;
	      h_name += "__systematic_";
	      h_name += systematic.label;
		
	      double yield = 0.0;
	      double error = 0.0;
	    
	      TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
	      yield = h_yield_bkg->GetBinContent( iCatList[iCat].binNumber );
	      error = h_yield_bkg->GetBinError( iCatList[iCat].binNumber );
	   
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

	fprintf(f_out, "\\end{document} \n");
	fclose(f_out);


    } // end loop over reco classifications

  } // end loop over systematic list

 

  return;
}
