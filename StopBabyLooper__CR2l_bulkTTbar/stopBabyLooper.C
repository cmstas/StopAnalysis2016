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

#include "Math/LorentzVector.h"

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

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;


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
  analyzerInfo::ID analysis = analyzerInfo::k_CR2l_bulkTTbar;
 

  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList( analysis ); 
  //sampleList.push_back( sampleInfo::k_diLepton_2015CD );
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
    // Nominal=0, JesUp=1, JesDn=2
    //
    if( iDir!=0 ) continue;


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
      //if(iDir==0 && 
      //   sample_id!=sampleInfo::k_T2tt) input += "Skims_CR_emu__20160202/";
      
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
    //f_output_name += "/data/tmp/jgwood/temp_stopAnalysis/";
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
    selectionInfo::vect_util cutList;
    cutList = selectionInfo::getCutList( analysis ); 
    //cutList.push_back( selectionInfo::cutUtil(selectionInfo::k_goodVtx) );  
    
    
    //
    // Declare Selection Object
    //
    cout << "    Loading selectorUtil" << endl << endl;
    selectionInfo::selectionUtil selector( cutList, sample.id );
    selector.setupCutflowHistos( f_output );


    //
    // Declare genClassification list
    //
    cout << "    Loading genClassyList" << endl << endl;
    genClassyInfo::vect_util genClassyList;
    genClassyList = genClassyInfo::getGenClassyList( analysis );
    //genClassyList.push_back( genClassyInfo::genClassyUtil(genClassyInfo::k_incl) );
    
    if( sample.isData ){
      genClassyList.clear();
      genClassyList.push_back( genClassyInfo::genClassyUtil(genClassyInfo::k_incl) );
    }

    
    //
    // Declare recoClassification list
    //
    cout << "    Loading recoClassyList" << endl << endl;
    recoClassyInfo::vect_util recoClassyList;
    recoClassyList = recoClassyInfo::getRecoClassyList( analysis );
    //recoClassyList.push_back( recoClassyInfo::recoClassyUtil(recoClassyInfo::k_incl) ); 
    

    //
    // Declare categoryInfo List
    //
    cout << "    Loading categoryList" << endl << endl;
    categoryInfo::vect_util catList;
    catList = categoryInfo::getCategoryList( analysis );
    //catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    

    //
    // Get Event Weight Object
    //
    cout << "    Loading eventWeighInfo" << endl << endl;
    bool bTagSF_fromFile = true;
    bool lepSF_fromFile  = true;
    eventWeightInfo *wgtInfo = new eventWeightInfo( sample.id, bTagSF_fromFile, lepSF_fromFile );

    // Switches for applying weights
    wgtInfo->apply_bTag_sf    = false;
    wgtInfo->apply_lep_sf     = false;
    wgtInfo->apply_vetoLep_sf = false;
    wgtInfo->apply_lepFS_sf   = false;
    wgtInfo->apply_topPt_sf   = false; // true=sf, false=uncertainty
    wgtInfo->apply_metRes_sf  = false;
    wgtInfo->apply_nJetsK3_sf = false; // only !=1.0 for powheg pythia8 tt2l
    wgtInfo->apply_nJetsK4_sf = false; // only !=1.0 for powheg pythia8 tt2l
    wgtInfo->apply_diNuPt_sf  = false; // only !=1.0 for powheg pythia8 tt2l
    wgtInfo->apply_ISR_sf     = false; // only !=1.0 for signal
    wgtInfo->apply_sample_sf  = false; // only !=1.0 for some WJetsHT samps


    //
    // Declare systematicInfo Object
    //
    cout << "    Loading systematicList" << endl << endl;
    systematicInfo::vect_util systematicList;
    systematicList = systematicInfo::getSystematicList( analysis, sample.isFastsim, sample.isSignal );
    //systematicList.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) ); 
    
    if( sample.isData ){
      systematicList.clear();
      systematicList.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) ); 
    }

       
    //
    // Declare Histograms
    //
    cout << "    Loading histograms" << endl << endl;
    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();
    TH3::SetDefaultSumw2();

    const int h_nSystematic = systematicInfo::k_nSys;
    const int h_nGenClassy  = genClassyInfo::k_nGenClassy;
    const int h_nRecoClassy = recoClassyInfo::k_nRecoClassy;
    const int h_nCategory   = categoryInfo::k_nCats;
  
    const int h_nMassPt = sample.massPtList.size();

    categoryInfo::vect_util   cat_temp;
    systematicInfo::vect_util sys_temp;
    
       
    histogramInfo::h3_Yield_Util *h3_yield = NULL;
    histogramInfo::h1_Yield_Util *h1_yield = NULL;
    histogramInfo::h1_Util *h1_nJets = NULL;
    histogramInfo::h1_Util *h1_met = NULL;
    histogramInfo::h1_Util *h1_nTags = NULL;
    histogramInfo::h1_Util *h1_lep1_pt = NULL;
    histogramInfo::h1_Util *h1_lep2_pt = NULL;
    histogramInfo::h1_Util *h1_diLep_pt = NULL;
    histogramInfo::h1_Util *h1_jet1_pt = NULL;
    histogramInfo::h1_Util *h1_jet2_pt = NULL;
    histogramInfo::h1_Util *h1_jet_pt = NULL;
    histogramInfo::h1_Util *h1_lep1lep2bb_pt = NULL;
    histogramInfo::h1_Util *h1_lep1lep2bbMet_pt = NULL;
    
    if( sample.isSignalScan ){

      //
      // Yields
      //
      cat_temp.clear(); sys_temp.clear();
      sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

      h3_yield = new histogramInfo::h3_Yield_Util( f_output, "yields", "Yields", sample.nBins_stop, sample.min_stop, sample.max_stop, sample.nBins_lsp, sample.min_lsp, sample.max_lsp, genClassyList, recoClassyList, catList, sys_temp );
    }
    
    else{
    
      //
      // Yields
      //
      h1_yield = new histogramInfo::h1_Yield_Util( f_output, "yields", "Yields", genClassyList, recoClassyList, catList, systematicList );


      //
      // nJets
      //
      h1_nJets = new histogramInfo::h1_Util( f_output, "nJets", "nJets", 11, -0.5, 10.5, genClassyList, recoClassyList, catList, systematicList );

 
      //
      // diNu pT, aka MET
      //
      h1_met = new histogramInfo::h1_Util( f_output, "met", "MET", 24, 0.0, 600.0, genClassyList, recoClassyList, catList, systematicList );


      //
      // Fill only a subset of categories and systematics for most histos
      //
      cat_temp.clear(); sys_temp.clear();
      
      cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
      cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge1btags_ge50met) );
      cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge2btags_ge50met) );
     
      sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
      

      //
      // nTags
      //
      h1_nTags = new histogramInfo::h1_Util( f_output, "nTags", "N b-Tagged Jets", 5, -0.5, 4.5, genClassyList, recoClassyList, cat_temp, sys_temp );


      //
      // Lep1 pT
      //
      h1_lep1_pt = new histogramInfo::h1_Util( f_output, "lep1_pt", "Leadig Lepton pT", 12, 0.0, 300.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    

      //
      // Lep2 pT
      //
      h1_lep2_pt = new histogramInfo::h1_Util( f_output, "lep2_pt", "Trailing Lepton pT", 12, 0.0, 300.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      

      //
      // diLepton pT
      //
      h1_diLep_pt = new histogramInfo::h1_Util( f_output, "diLepton_pt", "diLepton pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );


      //
      // Jet 1 pT
      //
      h1_jet1_pt = new histogramInfo::h1_Util( f_output, "jet1_pt", "Leading jet pT", 12, 0.0, 300.0, genClassyList, recoClassyList, cat_temp, sys_temp );


      //
      // Jet 2 pT
      //
      h1_jet2_pt = new histogramInfo::h1_Util( f_output, "jet2_pt", "Trailing jet pT", 12, 0.0, 300.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      

      //
      // All jet pT
      //
      h1_jet_pt = new histogramInfo::h1_Util( f_output, "jet_pt", "Jet pT", 12, 0.0, 300.0, genClassyList, recoClassyList, cat_temp, sys_temp );

      
      //
      // Lep 1, 2, b, b system pT
      //
      h1_lep1lep2bb_pt = new histogramInfo::h1_Util( f_output, "lep1lep2bb_pt", "lep1, lep2, b, b, system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );

      
      //
      // Lep 1, 2, b, b, met system pT
      //
      h1_lep1lep2bbMet_pt = new histogramInfo::h1_Util( f_output, "lep1lep2bbMet_pt", "lep1, lep2, b, b, MET, system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      

    } // end if not signal scan
        

    
    //
    // Event Counters
    //
    cout << "    Loading files to loop over" << endl << endl;
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
	// Initialize Weights
	//
	wgtInfo->initializeWeights();
	
	
	//
	// Check duplicate event
	//
	if( sample.isData &&
	    !selector.passCut( selectionInfo::k_duplicateRemoval ) ){
	  continue;
	}

	
	//
	// Get Weight To Scale to Lumi (scale1fb*LUMI)
	//
	double scaleToLumi_wgt = 1.0;
	wgtInfo->getScaleToLumiWeight( scaleToLumi_wgt );

	
	//
	// Pass Cuts
	//
	selector.fillCutflowHistos( scaleToLumi_wgt );
	if( !selector.passSelection() ) continue;
	
	
	//
	// Fill event weights
	//
	wgtInfo->getEventWeights();

	
	//
	// Get event weights for each systematic
	//
	systematicInfo::vect_util_wgt sysWgtsList;
	sysWgtsList = systematicInfo::getSystematicWeightsFromList( systematicList, wgtInfo );

	
	//
	// Check gen classifications that pass for this event
	//
	genClassyInfo::vect_util_passBool passGenClassyList;
	passGenClassyList = genClassyInfo::passGenClassyFromList( genClassyList, true );
	
	
	//
	// Check reco classifications that pass for this event
	//
	recoClassyInfo::vect_util_passBool passRecoClassyList;
	passRecoClassyList = recoClassyInfo::passRecoClassyFromList( recoClassyList, true );
	
	
	//
	// Check categories that pass for this event
	//
	categoryInfo::vect_util_passBool passCatList;
	passCatList = categoryInfo::passCategoriesFromList( catList, true );

	
	//
	// Compute Event Variables
	//

	// lep1 lep2 b b TLV
	LorentzVector lep1lep2bb_TLV;
	lep1lep2bb_TLV += lep1_p4();
	lep1lep2bb_TLV += lep2_p4();
	
	int jet1_idx = -1;
	double max_csv = -99.9;
	for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
	  if( ak4pfjets_CSV().at(iJet) > max_csv ){
	    jet1_idx = iJet;
	    max_csv  = ak4pfjets_CSV().at(iJet);
	  }
	}
	if(jet1_idx>=0) lep1lep2bb_TLV += ak4pfjets_p4().at(jet1_idx);
	
	int jet2_idx = -1;
	max_csv = -99.9;
	for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
	  if( iJet==jet1_idx ) continue;
	  if( ak4pfjets_CSV().at(iJet) > max_csv ){
	    jet2_idx = iJet;
	    max_csv = ak4pfjets_CSV().at(iJet);
	  }
	}
	if(jet2_idx>=0) lep1lep2bb_TLV += ak4pfjets_p4().at(jet2_idx);
	
	double lep1lep2bb_pt = lep1lep2bb_TLV.Pt();
	


	// lep1 lep2 b b MET TLV
	LorentzVector lep1lep2bbMet_TLV;
	lep1lep2bbMet_TLV = lep1lep2bb_TLV;
	
	LorentzVector met_TLV( pfmet()*cos(pfmet_phi()), pfmet()*sin(pfmet_phi()), 0.0, pfmet() );
	lep1lep2bbMet_TLV += met_TLV;
	
	double lep1lep2bbMet_pt = lep1lep2bbMet_TLV.Pt();

	
	//
	// Fill Histograms
	//
	
	// Loop over systematics
	for( int iSys=0; iSys<(int)sysWgtsList.size(); iSys++){
	  
	  // Loop over gen classifications
	  for(int iGen=0; iGen<(int)passGenClassyList.size(); iGen++){
	    
	    // Loop over reco classifications
	    for(int iReco=0; iReco<(int)passRecoClassyList.size(); iReco++){
	      
	      // Loop over categories
	      for(int iCat=0; iCat<(int)passCatList.size(); iCat++){
		
		int iYieldHist = histogramInfo::getYieldHistoIndex( sysWgtsList[iSys].first.id, passGenClassyList[iGen].first.id, passRecoClassyList[iReco].first.id );
		int iHist      = histogramInfo::getHistoIndex( sysWgtsList[iSys].first.id, passGenClassyList[iGen].first.id, passRecoClassyList[iReco].first.id, passCatList[iCat].first.id );
		
  		
		//
		// Fill Histograms
		//
		
		// Signal
		if( sample.isSignalScan ){
		  
		  // Yields
		  if( h3_yield->histos[iYieldHist] ) h3_yield->histos[iYieldHist]->Fill( wgtInfo->mStop, wgtInfo->mLSP, passCatList[iCat].first.label.c_str(), sysWgtsList[iSys].second );
		  
		} 
		// Data and Backgrounds
		else{
		  
		  // Yields
		  if( h1_yield->histos[iYieldHist] ) h1_yield->histos[iYieldHist]->Fill( passCatList[iCat].first.label.c_str(), sysWgtsList[iSys].second );
		  
		  // nJets
		  if( h1_nJets->histos[iHist] ) h1_nJets->histos[iHist]->Fill( ngoodjets(), sysWgtsList[iSys].second );
		  
		  // met
		  if( h1_met->histos[iHist] ) h1_met->histos[iHist]->Fill( pfmet(), sysWgtsList[iSys].second );
		  
		  // nTags
		  if( h1_nTags->histos[iHist] ) h1_nTags->histos[iHist]->Fill( ngoodbtags(), sysWgtsList[iSys].second );
		  
		  // lep1 pT
		  if( h1_lep1_pt->histos[iHist] ) h1_lep1_pt->histos[iHist]->Fill( lep1_p4().Pt(), sysWgtsList[iSys].second );
		  
		  // lep2 pT
		  if( h1_lep2_pt->histos[iHist] ) h1_lep2_pt->histos[iHist]->Fill( lep2_p4().Pt(), sysWgtsList[iSys].second );
		  
		  // diLep pT
		  if( h1_diLep_pt->histos[iHist] ) h1_diLep_pt->histos[iHist]->Fill( (lep1_p4()+lep2_p4()).Pt(), sysWgtsList[iSys].second );
		  
		  // jet1 pT
		  if( h1_jet1_pt->histos[iHist] ) h1_jet1_pt->histos[iHist]->Fill( ak4pfjets_p4().at(0).Pt(), sysWgtsList[iSys].second );
		  
		  // jet1 pT
		  if( h1_jet2_pt->histos[iHist] ) h1_jet2_pt->histos[iHist]->Fill( ak4pfjets_p4().at(1).Pt(), sysWgtsList[iSys].second );
		  
		  // jet pT
		  if( h1_jet_pt->histos[iHist] ){
		    for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
		      h1_jet_pt->histos[iHist]->Fill( ak4pfjets_p4().at(iJet).Pt(), sysWgtsList[iSys].second );
		    }
		  }
		  
		  // lep1lep2bb pT
		  if( h1_lep1lep2bb_pt->histos[iHist] ) h1_lep1lep2bb_pt->histos[iHist]->Fill( lep1lep2bb_pt, sysWgtsList[iSys].second );
		  
		  // lep1lep2bbMet pT
		  if( h1_lep1lep2bbMet_pt->histos[iHist] ) h1_lep1lep2bbMet_pt->histos[iHist]->Fill( lep1lep2bbMet_pt, sysWgtsList[iSys].second );
		  

		}
		
		
	      } // end loop over categories

	    } // end loop over reco classifications

	  } // end loop over gen classifications

	} // end loop over systematics
		


    
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

