#include "stopBabyLooper.h"

int pieCharts( std::string f_input_dir, std::string f_out_name_base, bool useZeroedAMCNLO ){

  // Make a tex document where each page will have a table
  //   This table will be for a given systematic. 
  //   It will show the yields for a set of catogries in rows
  //      and columns will be the input samples split by gen and reco
  //      classifications

  
  //
  // Configuration Variables
  //
  bool doRescale = false;
  double rescale = 1.0; // use lumi from stopCORE
  //double rescale = 10.0/35.867; // rescale to new lumi

  
  //
  // Sample List
  //
  TFile *f_input = NULL;

  sampleInfo::sampleUtil allBkg_util( sampleInfo::k_allBkg );

  std::pair< sampleInfo::ID, genClassyInfo::ID > sample;
  
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > bkgList;
  std::vector<Color_t> bkgList_colors;

  sample.first = sampleInfo::k_ttbar; 
  sample.second = genClassyInfo::k_ge2lep;
  bkgList.push_back(sample);
  bkgList_colors.push_back( kCyan-3 );

  sample.first = sampleInfo::k_ttbar; 
  sample.second = genClassyInfo::k_ee1lep;
  bkgList.push_back(sample);
  bkgList_colors.push_back( kRed-7 );

  sample.first = sampleInfo::k_singleT; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);
  bkgList_colors.push_back(kOrange-2);

  sample.first = sampleInfo::k_VJets; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);
  bkgList_colors.push_back( kGreen-3 );

  sample.first = sampleInfo::k_rare; 
  sample.second = genClassyInfo::k_incl;
  bkgList.push_back(sample);
  bkgList_colors.push_back( kMagenta-5 );

  
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > bkgList_byGen;
  std::vector<Color_t> bkgList_byGen_colors;

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ge2lep;
  bkgList_byGen.push_back(sample);
  bkgList_byGen_colors.push_back( kCyan-3 );

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ee1lep_fromW;
  bkgList_byGen.push_back(sample);
  bkgList_byGen_colors.push_back( kOrange-2 );

  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  bkgList_byGen.push_back(sample);
  bkgList_byGen_colors.push_back( kRed-7 );
  
  sample.first = sampleInfo::k_allBkg; 
  sample.second = genClassyInfo::k_ZtoNuNu;
  bkgList_byGen.push_back(sample);
  bkgList_byGen_colors.push_back( kMagenta-5 );

  const char *labels_byGen[4] = {"2lep", "1lep W", "1lep t", "ZtoNuNu"};
  
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


 

  //
  // Yields, Top Corridor
  //
  catList.clear();
  cat.histName = "h_yields"; cat.binNumber = 1; cat.tex = "top~corridor,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields"; cat.binNumber = 2; cat.tex = "top~corridor,~$350<MET<450$";
  catList.push_back( cat );
  tableList_corridor.push_back( catList );
  catList.clear();
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

  
  //
  // Make yield tables
  //
  for(int iRegion=0; iRegion<(int)regionList.size(); iRegion++){

    // Loop over systematics
    for(int iSys=0; iSys<(int)systematicList.size(); iSys++){

      sysInfo::Util systematic(systematicList[iSys]);

	
      std::vector< std::vector<yieldHelper> > iTableList = regionList.at(iRegion).second;

	// Table Title
	TString regionListTitle = regionList.at(iRegion).first;
	regionListTitle.ReplaceAll("_", " ");

	TString table_title = "";
	table_title += regionListTitle;
	table_title += ", ";
	table_title += systematicList[iSys].tex;
	table_title += " Systematic, Yield Table for ";
	
	TString hName_temp = iTableList[0][0].histName;
	hName_temp.ReplaceAll("h_","");
	hName_temp.ReplaceAll("_"," ");
	table_title += hName_temp;
	
	// TCanvas of Pie Charts
	TCanvas *can = new TCanvas("can",table_title,20,20,1500,1000);

	int nRegions_y = iTableList.size();
	int nRegions_x = 1;
	for(int iTable=0; iTable<(int)iTableList.size(); iTable++){
	  if( (int)iTableList[iTable].size()>nRegions_x ) nRegions_x = (int)iTableList[iTable].size();
	}

	can->Divide(nRegions_x, nRegions_y);
	
	// Loop over regions for Y direction
	for(int iTable=0; iTable<(int)iTableList.size(); iTable++){

	  std::vector<yieldHelper> iCatList = iTableList[iTable];

	  // Loop over metBins for X direction
	  for(int iCat=0; iCat<(int)iCatList.size(); iCat++){

	    int pad = iTable*nRegions_x + iCat + 1;
	    can->cd(pad);
	

	    // One Pie Chart
	    const int nBkgs = bkgList_byGen.size();
	    Float_t vals[nBkgs];
	    Int_t colors[nBkgs];
	    
	        
	    for(int iBkg=0; iBkg<(int)nBkgs; iBkg++){
	      sampleInfo::sampleUtil sample( bkgList_byGen[iBkg].first );
	      genClassyInfo::Util genClassy( bkgList_byGen[iBkg].second );
	      
	      TString f_input_name = f_input_dir;
	      f_input_name += sample.label;
	      if( useZeroedAMCNLO && sample.isAMCNLO ){
		f_input_name += "_noNegYield";
	      }
	      f_input_name += ".root";
	      f_input = new TFile( f_input_name, "read");

	      TString h_name = iCatList[iCat].histName;
	      h_name += "__";
	      h_name += regionList.at(iRegion).first;
	      h_name += "__genClassy_";
	      h_name += genClassy.label;
	      h_name += "__systematic_";
	      h_name += systematicList[iSys].label;

	      double yield = 0.0;
	      double error = 0.0;
	      
	      TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name);
	      yield = h_yield_bkg->GetBinContent( iCatList[iCat].binNumber );
	      error = h_yield_bkg->GetBinError( iCatList[iCat].binNumber );
	      
	      if(doRescale){
		yield *= rescale;
		error *= rescale;
	      }
	    
	      vals[iBkg] = yield;
	      colors[iBkg] = bkgList_byGen_colors[iBkg];
	      	      
	      f_input->Close();

	    } // end loop over gen categories

	    TString pie_label = iCatList[iCat].histName;
	    pie_label += "__";
	    pie_label += iCatList[iCat].tex;
	    pie_label.ReplaceAll("$","");
	    pie_label.ReplaceAll("~","_");
	    pie_label.ReplaceAll("\\ge","ge");
	    pie_label.ReplaceAll("\\le","ee");
	    pie_label.ReplaceAll(">","gt");
	    pie_label.ReplaceAll("<","lt");

	    TString pie_title = iCatList[iCat].histName;
	    pie_title += "__";
	    pie_title += iCatList[iCat].tex;
	    pie_title.ReplaceAll("h_","");
	    pie_title.ReplaceAll("__",", ");
	    pie_title.ReplaceAll("_"," ");
	    pie_title.ReplaceAll("$","");
	    pie_title.ReplaceAll("~"," ");
	    pie_title.ReplaceAll("\\ge",">=");
	    pie_title.ReplaceAll("\\le","<=");

	    
	    TPie *pie = new TPie(pie_label, pie_title, nBkgs, vals, colors, labels_byGen);
	    
	    pie->SetRadius(.2);
	    pie->SetLabelsOffset(.01);
	    pie->SetLabelFormat("#splitline{%val (%perc)}{%txt}");
	    pie->Draw("nol <");
	    
	    //pad++;
	    //can->cd(pad);

	  } // end loop over table of categories
	  
	} // end loop over set of tables

	TString saveMe = f_out_name_base;
        saveMe += "__";
	saveMe += iTableList[0][0].histName;
	saveMe += "__region_";
        saveMe += regionList.at(iRegion).first;
        saveMe += "__systematic_";
        saveMe += systematicList[iSys].label;
        saveMe += ".pdf";

	can->SaveAs(saveMe.Data());
	
	can->~TCanvas();

    } // end loop over systematics

  } // end loop over regions

 

  return 0;
}
