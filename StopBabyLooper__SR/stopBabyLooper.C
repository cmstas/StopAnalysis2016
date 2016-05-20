// Usage:
// > root -l -b -q head.C stopBabyLooper.C++

// C++
#include <iostream>
#include <string>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"

// stopCORE
#include "../StopCORE/stop_1l_babyAnalyzer.h"
#include "../StopCORE/analyzerInfo.h"
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/selectionInfo.h"
#include "../StopCORE/eventWeightInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"


using namespace std;
using namespace tas;
using namespace stop_1l;


//
// Function Declarations
//
int looper( analyzerInfo::ID analysis, sampleInfo::ID sample, int nEvents=-1, bool fast=true );


//
// Main
//
int stopBabyLooper(){

  //
  // Declare Analyzer Type
  //
  analyzerInfo::ID analysis = analyzerInfo::k_SR;
 

  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList( analysis ); 
  //sampleList.push_back( sampleInfo::k_single_lepton_met_2015CD );
  //sampleList.push_back( sampleInfo::k_ttbar_powheg_pythia8_ext3 ); 
  

  //
  // Loop over samples
  //
  for( int iSample=0; iSample<(int)sampleList.size(); iSample++){
    looper( analysis, sampleList[iSample] );
  }

  
  return 0;

}




//
// Functions
//
int looper( analyzerInfo::ID analysis, sampleInfo::ID sample_id, int nEvents, bool fast ) {


  //
  // Intro
  //
  cout << "====================================================" << endl;
  cout << endl;
  cout << "  WELCOME TO STOP BABY ANALYZER! " << endl;
  cout << endl;
  cout << "====================================================" << endl;
  cout << endl;


  //
  // Input sample
  //
  sampleInfo::sampleUtil sample( sample_id );

  
  //
  // Loop over different input directories for each sample, ie Nominal, JES
  //
  for(int iDir=0; iDir<(int)sample.baby_i_o.size(); iDir++){
    
    //
    // Benchmark
    //
    TBenchmark *bmark = new TBenchmark();
    bmark->Start("benchmark");


    //
    // Input chain
    //
    TChain *chain = new TChain("t");
  
    cout << "    Processing the following: " << endl;  
    for(int iFile=0; iFile<(int)sample.inputBabies.size(); iFile++){

      // input directory
      string input = sample.baby_i_o[iDir].first;
      if(iDir==0) input += "Skims_SR__20160202/";
      
      // input file
      input += sample.inputBabies[iFile];
      
      chain->Add( input.c_str() );
      cout << "      " << input << endl; 
    }
    cout << endl;

    
    //
    // Output File
    //

    // output dir
    string f_output_name = "";
    f_output_name += "/data/tmp/jgwood/temp_stopAnalysis/";
    f_output_name += sample.baby_i_o[iDir].second;

    // output name
    f_output_name += "h__";
    f_output_name += sample.label;
    f_output_name += ".root";

    // output file
    TFile *f_output = new TFile( f_output_name.c_str(), "recreate" );

    // print output location
    cout << "    Output Written to: " << endl;
    cout << "      " << f_output_name << endl;
    cout << endl;

  
    //
    // Get List of Cuts for selection
    //
    cout << "    Loading cutList" << endl << endl;
    selectionInfo::vect_id cutList;
    cutList = selectionInfo::getCutList( analysis ); 
    //cutList.push_back( selectionInfo::k_goodVtx );  

  
    //
    // Declare Selection Object
    //
    cout << "    Loading selectorUtil" << endl << endl;
    selectionInfo::selectionUtil selector( cutList, sample.isData );
    selector.setupCutflowHistos( f_output );


    //
    // Declare genClassification list
    //
    cout << "    Loading genClassyList" << endl << endl;
    genClassyInfo::vect_id genClassyList;
    genClassyList = genClassyInfo::getGenClassyList( analysis );
    //genClassyList.push_back( genClassyInfo::k_incl );
  
    if( sample.isData ){
      genClassyList.clear();
      genClassyList.push_back( genClassyInfo::k_incl );
    }


    //
    // Declare recoClassification list
    //
    recoClassyInfo::vect_id recoClassyList;
    cout << "    Loading recoClassyList" << endl << endl;
    recoClassyList = recoClassyInfo::getRecoClassyList( analysis );
    //recoClassyList.push_back( recoClassyInfo::k_incl ); 
  

    //
    // Declare categoryInfo List
    //
    categoryInfo::vect_id catList;
    cout << "    Loading categoryList" << endl << endl;
    catList = categoryInfo::getCategoryList( analysis );
    //catList.push_back( categoryInfo::k_incl );


    //
    // Get Event Weight Object
    //
    cout << "    Loading eventWeighInfo" << endl << endl;
    bool bTagSF_fromFile = true;
    bool lepSF_fromFile  = true;
    eventWeightInfo *wgtInfo = new eventWeightInfo( sample.id, bTagSF_fromFile, lepSF_fromFile );
      

    //
    // Declare systematicInfo Object
    //
    systematicInfo::vect_id systematicList;
    cout << "    Loading systematicList" << endl << endl;
    systematicList = systematicInfo::getSystematicList( analysis, sample.isFastsim, sample.isSignal );
    //systematicList.push_back( systematicInfo::k_nominal ); 

    if( sample.isData ){
      systematicList.clear();
      systematicList.push_back( systematicInfo::k_nominal ); 
    }


    //
    // Declare Histograms
    //
    cout << "    Loading histograms" << endl << endl;
    TH1::SetDefaultSumw2();
  
    categoryInfo::vect_id   cat_temp;
    systematicInfo::vect_id sys_temp;
    
    
    //
    // Yields
    //
    histogramInfo::h1_Yield_Util h_yield( f_output, "yields", "Yields", genClassyList, recoClassyList, catList, systematicList );

    
    //
    // nJets
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::k_incl );

    sys_temp.push_back( systematicInfo::k_nominal );

    histogramInfo::h1_Util h_nJets( f_output, "nJets", "nJets", 11, -0.5, 10.5, genClassyList, recoClassyList, cat_temp, sys_temp );

    
    
    //
    // Event Counters
    //
    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();
    if( nEvents >= 0 ) nEventsChain = nEvents;


    //
    // Grab list of files
    //
    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;
    while ( (currentFile = (TFile*)fileIter.Next()) ) {


      //
      // Get File Content
      //
      TFile *file = new TFile( currentFile->GetTitle(), "read" );
      TTree *tree = (TTree*)file->Get("t");
      if(fast) TTreeCache::SetLearnEntries(10);
      if(fast) tree->SetCacheSize(128*1024*1024);
      babyAnalyzer.Init(tree);

    
      //
      // Get weight histogram from baby
      //
      wgtInfo->getWeightHistogramFromBaby( file );
      
      
      //
      // Loop over Events in current file
      //
      if( nEventsTotal >= nEventsChain ) continue;
      unsigned int nEventsTree = tree->GetEntriesFast();
      for( unsigned int event = 0; event < nEventsTree; ++event) {

	
	//
	// Get Event Content
	//
	if( nEventsTotal >= nEventsChain ) continue;
	if(fast) tree->LoadTree(event);
	babyAnalyzer.GetEntry(event);
	++nEventsTotal;
	
	
	//
	// Progress
	//
	stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );


	//
	// Check duplicate event
	//
	if( sample.isData &&
	    !selector.passCut( selectionInfo::k_duplicateRemoval ) ){
	  continue;
	}
	  
	
	//
	// Get Event Weight
	//
	wgtInfo->initializeWeights();
	wgtInfo->getEventWeights();
	
	systematicInfo::vect_id_wgt evt_wgts;
	evt_wgts = systematicInfo::getSystematicWeightsFromList( systematicList, wgtInfo );
	

	//
	// Get nominal weight
	//
	double nominal_wgt = 1.0;
	for(int iSys=0; iSys<(int)evt_wgts.size(); iSys++){
	  if( evt_wgts[iSys].first == systematicInfo::k_nominal ){
	    nominal_wgt = evt_wgts[iSys].second;
	    break;
	  }
	}

	
	//
	// Pass Cuts
	//
	selector.fillCutflowHistos( nominal_wgt );
	if( !selector.passSelection() ) continue;
	
	
	//
	// Determine Gen Classification
	//
	genClassyInfo::vect_id_passBool evt_genClassy;
	evt_genClassy = genClassyInfo::passGenClassyFromList( genClassyList );

	
	//
	// Determine Reco Classification
	//
	recoClassyInfo::vect_id_passBool evt_recoClassy;
	evt_recoClassy = recoClassyInfo::passRecoClassyFromList( recoClassyList );

	
	//
	// Determine Signal Region Category
	//
	categoryInfo::vect_id_passBool evt_categories;
	evt_categories = categoryInfo::passCategoriesFromList( catList );
      	
	
	//
	// Fill Histos
	//

	// Yields
	h_yield.fill( evt_genClassy, evt_recoClassy, evt_categories, evt_wgts );
	
	// nJets
	h_nJets.fill( ngoodjets(), evt_genClassy, evt_recoClassy, evt_categories, evt_wgts ) ;
	


      } // end loop over events in tree
      
      
      //
      // Clean Up
      //
      delete tree;
      file->Close();
      delete file;
      
    } // end loop over file list
    
    
    //
    // Output Sanitation
    //
    if ( nEventsChain != nEventsTotal ) {
      cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
    }
    
    
    //
    // Print Selection Cutflow
    //
    cout << "====================================================" << endl;
    selector.printCutflow();
    cout << "====================================================" << endl;


    //
    // Clean stopCORE objects
    //
    wgtInfo->~eventWeightInfo();


    //
    // Close Output File
    //
    f_output->Write();
    f_output->Close();

    
    //
    // Clean input chain
    // 
    chain->~TChain();

       
    //
    // Benchmark Reporting
    //
    bmark->Stop("benchmark");
    cout << endl;
    cout << nEventsTotal << " Events Processed" << endl;
    cout << "------------------------------" << endl;
    cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
    cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
    cout << endl;
    delete bmark;

    cout << "====================================================" << endl;
    
  } // end loop over input directories


  //
  // Return!
  //
  return 0;

}

