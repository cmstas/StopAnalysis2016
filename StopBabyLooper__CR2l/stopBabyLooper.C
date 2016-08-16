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

#include "../StopBabyMaker/stop_variables/mt2w.h"
#include "../StopBabyMaker/stop_variables/topness.h"

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
  analyzerInfo::ID analysis = analyzerInfo::k_CR2l;
 

  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList( analysis ); 
  //sampleList.push_back( sampleInfo::k_single_lepton_met_2016B );
  //sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_T2tt ); 
  
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
      //if(iDir==0 && 
      //   sample_id!=sampleInfo::k_T2tt) input += "Skims_CR_2lep__20160202/";
      
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
    bool add2ndLeptonToMet = true;
    selectionInfo::selectionUtil selector( cutList, sample.id, add2ndLeptonToMet );
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
    bool bTagSF_fromFile = false;
    bool lepSF_fromFile  = false;
    eventWeightInfo *wgtInfo = new eventWeightInfo( sample.id, bTagSF_fromFile, lepSF_fromFile, add2ndLeptonToMet );

    // Switches for applying weights
    wgtInfo->apply_diLepTrigger_sf = false;
    wgtInfo->apply_cr2lTrigger_sf  = true;
    wgtInfo->apply_bTag_sf         = true;
    wgtInfo->apply_lep_sf          = true;
    wgtInfo->apply_vetoLep_sf      = true;
    wgtInfo->apply_lepFS_sf        = false;
    wgtInfo->apply_topPt_sf        = false; // true=sf, false=uncertainty
    wgtInfo->apply_metRes_sf       = true;
    wgtInfo->apply_ttbarSysPt_sf   = true; // true=sf, false=uncertainty, only !=1.0 for madgraph tt2l, tW2l
    wgtInfo->apply_ISR_sf          = false; // only !=1.0 for signal
    wgtInfo->apply_sample_sf       = false; // only !=1.0 for some WJetsHT samps

    
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
    
    
    //
    // Yields
    //
    histogramInfo::h1_Yield_Util *h1_yield = NULL;
    histogramInfo::h3_Yield_Util *h3_yield = NULL;
    if( sample.isSignalScan ){
      h3_yield = new histogramInfo::h3_Yield_Util( f_output, "yields", "Yields", sample.nBins_stop, sample.min_stop, sample.max_stop, sample.nBins_lsp, sample.min_lsp, sample.max_lsp, genClassyList, recoClassyList, catList, systematicList );
    }
    else{
      h1_yield = new histogramInfo::h1_Yield_Util( f_output, "yields", "Yields", genClassyList, recoClassyList, catList, systematicList );
    }
    

    //
    // Gen ttbar system pT
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    
    histogramInfo::h1_Util *h1_gen_ttbar_pt = NULL;
    histogramInfo::h1_Util *h1_gen_ttbar_pt__ge350met = NULL;
    histogramInfo::h1_Util *h1_gen_ttbar_pt__ge200mt2w = NULL;
    histogramInfo::h1_Util *h1_gen_ttbar_pt__ge200mt2w_ge350met = NULL;
    bool sampleIsTTbar = false;
    if( sample.id == sampleInfo::k_ttbar_powheg_pythia8 ||
	sample.id == sampleInfo::k_ttbar_powheg_pythia8_ext3 ||
	sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 ||
	sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 ||
	sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 ||
	sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 ||
	sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8 ||
	sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ){
      sampleIsTTbar = true;
    }

    if( sampleIsTTbar ){
      
      h1_gen_ttbar_pt = new histogramInfo::h1_Util( f_output, "gen_ttbar_pt", "Gen t#bar{t}, system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      h1_gen_ttbar_pt__ge350met = new histogramInfo::h1_Util( f_output, "gen_ttbar_pt__ge350met", "Gen t#bar{t}, system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      h1_gen_ttbar_pt__ge200mt2w = new histogramInfo::h1_Util( f_output, "gen_ttbar_pt__ge200mt2w", "Gen t#bar{t}, system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      h1_gen_ttbar_pt__ge200mt2w_ge350met = new histogramInfo::h1_Util( f_output, "gen_ttbar_pt__ge200mt2w_ge350met", "Gen t#bar{t}, system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );

    }

    
    //
    // nJets
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_nJets = NULL;
    histogramInfo::h1_Util *h1_scan_nJets[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "nJets__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "nJets, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_nJets[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 11, -0.5, 10.5, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_nJets = new histogramInfo::h1_Util( f_output, "nJets", "nJets", 11, -0.5, 10.5, genClassyList, recoClassyList, cat_temp, sys_temp );
    }


    //
    // modified Topness
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_modTop = NULL;
    histogramInfo::h1_Util *h1_scan_modTop[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "modTopness__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "modified topness, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_modTop[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 20, -20.0, 20.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_modTop = new histogramInfo::h1_Util( f_output, "modTopness", "modified topness", 20, -20.0, 20.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }


    //
    // MT2W
    //
    cat_temp.clear(); sys_temp.clear();
    
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_mt2w = NULL;
    histogramInfo::h1_Util *h1_scan_mt2w[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "mt2w__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "MT2W, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_mt2w[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_mt2w = new histogramInfo::h1_Util( f_output, "mt2w", "MT2W", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }


    //
    // MET
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_met = NULL;
    histogramInfo::h1_Util *h1_scan_met[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "met__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "MET, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_met[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 32, 0.0, 800.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_met = new histogramInfo::h1_Util( f_output, "met", "MET", 32, 0.0, 800.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }



    //
    // pfMET
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_pfmet = NULL;
    histogramInfo::h1_Util *h1_scan_pfmet[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "pfmet__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "PFMET, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_pfmet[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 32, 0.0, 800.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_pfmet = new histogramInfo::h1_Util( f_output, "pfmet", "PFMET", 32, 0.0, 800.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }



    //
    // MT
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_mt = NULL;
    histogramInfo::h1_Util *h1_scan_mt[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "mt__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "MT, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_mt[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_mt = new histogramInfo::h1_Util( f_output, "mt", "MT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }


    //
    // jet 1 pT
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_jet1_pt = NULL;
    histogramInfo::h1_Util *h1_scan_jet1_pt[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "jet1_pt__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "leading jet pT, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_jet1_pt[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_jet1_pt = new histogramInfo::h1_Util( f_output, "jet1_pt", "leading jet pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }



    //
    // jet 2 pT
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_jet2_pt = NULL;
    histogramInfo::h1_Util *h1_scan_jet2_pt[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "jet2_pt__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "trailing jet pT, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_jet2_pt[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_jet2_pt = new histogramInfo::h1_Util( f_output, "jet2_pt", "trailing jet pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }



    //
    // jet pT
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_jet_pt = NULL;
    histogramInfo::h1_Util *h1_scan_jet_pt[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "jet_pt__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "jet pT, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_jet_pt[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_jet_pt = new histogramInfo::h1_Util( f_output, "jet_pt", "jet pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }


    
    //
    // jet pT, not j1j2
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_jet_pt_notJ1J2 = NULL;
    histogramInfo::h1_Util *h1_scan_jet_pt_notJ1J2[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "jet_pt_notJ1J2__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "jet pT, excluding 2 leading pT jets";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_jet_pt_notJ1J2[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_jet_pt_notJ1J2 = new histogramInfo::h1_Util( f_output, "jet_pt_notJ1J2", "jet pT, excluding 2 leading pT jets", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }



    //
    // lep1,lep2,b,bbar pT
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_lep1lep2bb_pt = NULL;
    histogramInfo::h1_Util *h1_scan_lep1lep2bb_pt[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "lep1lep2bb_pt__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "lep1, lep2, b, bbar system pT, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_lep1lep2bb_pt[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_lep1lep2bb_pt = new histogramInfo::h1_Util( f_output, "lep1lep2bb_pt", "lep1, lep2, b, bbar system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }


    //
    // lep1,lep2,b,bbar,MET pT
    //
    cat_temp.clear(); sys_temp.clear();

    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
    cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );

    sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

    histogramInfo::h1_Util *h1_lep1lep2bbMet_pt = NULL;
    histogramInfo::h1_Util *h1_scan_lep1lep2bbMet_pt[ h_nMassPt ];
    if( sample.isSignalScan ){

      for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){
	std::string h_name = "lep1lep2bbMet_pt__";
	h_name += "mStop_";  h_name += sample.massPtList[iMassPt].first;
	h_name += "__mLSP_";  h_name += sample.massPtList[iMassPt].second;
	
	std::string h_title = "lep1, lep2, b, bbar, MET system pT, ";
	h_title += "mStop=";   h_title += sample.massPtList[iMassPt].first;
	h_title += ", mLSP=";  h_title += sample.massPtList[iMassPt].second;

	h1_scan_lep1lep2bbMet_pt[iMassPt] = new histogramInfo::h1_Util( f_output, h_name, h_title, 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
      } // end loop over mass points

    } // end if signal scan
    else{
      h1_lep1lep2bbMet_pt = new histogramInfo::h1_Util( f_output, "lep1lep2bbMet_pt", "lep1, lep2, b, bbar, MET system pT", 24, 0.0, 600.0, genClassyList, recoClassyList, cat_temp, sys_temp );
    }

    

    TH2D *h2__lep1_vs_secondLepType_ee2j = new TH2D("h2__lep1_vs_secondLepType_ee2j", "leading lepton reco vs seocnd lepton reco, >=4 jets", 2, 0.0, 2.0, 4, 0.0, 4.0);
    h2__lep1_vs_secondLepType_ee2j->SetDirectory(f_output);
    h2__lep1_vs_secondLepType_ee2j->GetXaxis()->SetBinLabel(1, "el");
    h2__lep1_vs_secondLepType_ee2j->GetXaxis()->SetBinLabel(2, "mu");
    h2__lep1_vs_secondLepType_ee2j->GetYaxis()->SetBinLabel(1, "good el");
    h2__lep1_vs_secondLepType_ee2j->GetYaxis()->SetBinLabel(2, "good mu");
    h2__lep1_vs_secondLepType_ee2j->GetYaxis()->SetBinLabel(3, "veto el");
    h2__lep1_vs_secondLepType_ee2j->GetYaxis()->SetBinLabel(4, "veto mu");
    //h2__lep1_vs_secondLepType_ee2j->GetYaxis()->SetBinLabel(4, "isoTrk || pfTau");


    TH2D *h2__lep1_vs_secondLepType_ge4j = new TH2D("h2__lep1_vs_secondLepType_ge4j", "leading lepton reco vs seocnd lepton reco, >=4 jets", 2, 0.0, 2.0, 4, 0.0, 4.0);
    h2__lep1_vs_secondLepType_ge4j->SetDirectory(f_output);
    h2__lep1_vs_secondLepType_ge4j->GetXaxis()->SetBinLabel(1, "el");
    h2__lep1_vs_secondLepType_ge4j->GetXaxis()->SetBinLabel(2, "mu");
    h2__lep1_vs_secondLepType_ge4j->GetYaxis()->SetBinLabel(1, "good el");
    h2__lep1_vs_secondLepType_ge4j->GetYaxis()->SetBinLabel(2, "good mu");
    h2__lep1_vs_secondLepType_ge4j->GetYaxis()->SetBinLabel(3, "veto el");
    h2__lep1_vs_secondLepType_ge4j->GetYaxis()->SetBinLabel(4, "veto mu");
    //h2__lep1_vs_secondLepType_ge4j->GetYaxis()->SetBinLabel(5, "isoTrk || pfTau");


    TH1D *h1_wgt_cr2lTriggerSF = new TH1D("h1_wgt_cr2lTriggerSF", "CR2l trigger eff SF", 100, -0.01, 1.01);
    h1_wgt_cr2lTriggerSF->SetDirectory(f_output);


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
	
	double nominal_wgt = scaleToLumi_wgt;
	for( int iSys=0; iSys<(int)sysWgtsList.size(); iSys++ ){
	  if( sysWgtsList[iSys].first.id == systematicInfo::k_nominal ){
	    nominal_wgt = sysWgtsList[iSys].second;
	    break;
	  }
	}



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
	passCatList = categoryInfo::passCategoriesFromList( catList, true, add2ndLeptonToMet );

	
	//
	// Compute Event Variables
	//

	// gen ttbar system pT
	double ttbarPt = -99.9;
       	LorentzVector genTTbar_LV;
	int nFoundGenTop=0;
	if( sampleIsTTbar ){
	
	  for(int iGen=0; iGen<(int)genqs_p4().size(); iGen++){
	    if( abs(genqs_id().at(iGen))==6 &&
		genqs_isLastCopy().at(iGen)    ){
	      genTTbar_LV += genqs_p4().at(iGen);
	      nFoundGenTop++;
	    } // end if last copy of top
	  } // end loop over gen quarks

	  if( nFoundGenTop == 2 ) ttbarPt = genTTbar_LV.Pt();
	} // end if not data



	// If adding 2nd lepton to Met, recalculate appropriate vars
	double met = pfmet();
	//double met_phi = pfmet_phi();
	//double dphi_metLep = std::acos(std::cos(met_phi - lep1_p4().Phi()));
	double mt = mt_met_lep();
	double minDPhi_met_j1_j1 = mindphi_met_j1_j2();
	double modTopness = topnessMod();
	double mt2w = MT2W();
	if( add2ndLeptonToMet ){
	  /*
	  if( (ngoodleps()>=2) ||
	      (ngoodleps()==1 && nvetoleps()>=2 && lep2_p4().Pt()>10.0 ) ){
	    
	    double metX = met*std::cos(met_phi);
	    double metY = met*std::sin(met_phi);
	    
	    metX += lep2_p4().Px();
	    metY += lep2_p4().Py();
	    
	    met = sqrt( metX*metX + metY*metY );
	    met_phi = std::atan2( metY, metX );
	    dphi_metLep = std::acos(std::cos(met_phi - lep1_p4().Phi()));
	    mt = sqrt(2*lep1_p4().pt()*met*(1-std::cos(dphi_metLep)));
	    
	    double minDPhi_met_j1 = std::acos(std::cos(met_phi - ak4pfjets_p4().at(0).Phi()));
	    double minDPhi_met_j2 = std::acos(std::cos(met_phi - ak4pfjets_p4().at(1).Phi()));
	    minDPhi_met_j1_j1 = std::min( minDPhi_met_j1, minDPhi_met_j2 );
	   
	    //
	    // first, we need to sort jets by CSV value
	    // 
	    std::vector<std::pair<int, double> > v_idx_csv;
	    for (unsigned int idx = 0; idx < babyAnalyzer.ak4pfjets_p4().size(); idx++) {
	      v_idx_csv.push_back(std::make_pair(idx, babyAnalyzer.ak4pfjets_CSV().at(idx)));
	    }
	    std::sort(v_idx_csv.begin(), v_idx_csv.end(), categoryInfo::sortByCSV);

	    //
	    // now get vector<LV> of b-jets and add-jets
	    // 
	    std::vector<LorentzVector> mybjets;
	    std::vector<LorentzVector> addjets;
	    for (auto p : v_idx_csv) {
	      if (babyAnalyzer.ak4pfjets_passMEDbtag().at(p.first))
		mybjets.push_back(babyAnalyzer.ak4pfjets_p4().at(p.first));
	      else if (mybjets.size() <=1 && (mybjets.size() + addjets.size()) < 3)
		addjets.push_back(babyAnalyzer.ak4pfjets_p4().at(p.first));
	    }
	    
	    // 
	    // if == 2 jets, recalculate modified topness with new met
	    //
	    if (babyAnalyzer.ngoodjets() == 2)
	      modTopness = CalcTopness_(1, met, met_phi, babyAnalyzer.lep1_p4(), mybjets, addjets);

	    //
	    // if >=3 jets, recalculate mt2w with new met
	    // 
	    if (babyAnalyzer.ngoodjets() >= 3)
	      mt2w = CalcMT2W_(mybjets, addjets, babyAnalyzer.lep1_p4(), met, met_phi);
	    
  
	  } // min if 2nd lepton exists
	  */

	  met = pfmet_rl();
	  //met_phi = pfmet_phi_rl();
	  //dphi_metLep = std::acos(std::cos(met_phi - lep1_p4().Phi()));
	  mt = mt_met_lep_rl();
	  minDPhi_met_j1_j1 = mindphi_met_j1_j2_rl();
	  modTopness = topnessMod_rl();
	  mt2w = MT2W_rl();

	} // end if addSeocnLepToMet



	//
	// Fill Histograms
	//
	if( ngoodjets()==2 &&
	    met>=250.0    ){
	  
	  if( abs(lep1_pdgid())==11 ){
	    
	    if( abs(lep2_pdgid())==11 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "el", "good el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==11 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "el", "veto el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==13 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "el", "good mu", nominal_wgt );
	    }

	    else if( abs(lep2_pdgid())==13 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "el", "veto mu", nominal_wgt );
	    }
	    
	    else if( !PassTrackVeto() || !PassTauVeto() ){
	      //h2__lep1_vs_secondLepType_ee2j->Fill( "el", "isoTrk || pfTau", nominal_wgt );
	    }

	  }

	  if( abs(lep1_pdgid())==13 ){
	    
	    if( abs(lep2_pdgid())==11 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "mu", "good el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==11 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "mu", "veto el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==13 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "mu", "good mu", nominal_wgt );
	    }

	    else if( abs(lep2_pdgid())==13 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ee2j->Fill( "mu", "veto mu", nominal_wgt );
	    }
	    
	    else if( !PassTrackVeto() || !PassTauVeto() ){
	      //h2__lep1_vs_secondLepType_ee2j->Fill( "mu", "isoTrk || pfTau", nominal_wgt );
	    }

	  }

	}


	if( ngoodjets()>=4 &&
	    met>=250.0    ){
	  
	  if( abs(lep1_pdgid())==11 ){
	    
	    if( abs(lep2_pdgid())==11 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "el", "good el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==11 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "el", "veto el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==13 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "el", "good mu", nominal_wgt );
	    }

	    else if( abs(lep2_pdgid())==13 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "el", "veto mu", nominal_wgt );
	    }
	    
	    else if( !PassTrackVeto() || !PassTauVeto() ){
	      //h2__lep1_vs_secondLepType_ge4j->Fill( "el", "isoTrk || pfTau", nominal_wgt );
	    }

	  }

	  if( abs(lep1_pdgid())==13 ){
	    
	    if( abs(lep2_pdgid())==11 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "mu", "good el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==11 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "mu", "veto el", nominal_wgt );
	    }
	    
	    else if( abs(lep2_pdgid())==13 && ngoodleps()==2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "mu", "good mu", nominal_wgt );
	    }

	    else if( abs(lep2_pdgid())==13 && ngoodleps()==1 && nvetoleps()>=2 ){
	      h2__lep1_vs_secondLepType_ge4j->Fill( "mu", "veto mu", nominal_wgt );
	    }
	    
	    else if( !PassTrackVeto() || !PassTauVeto() ){
	      //h2__lep1_vs_secondLepType_ge4j->Fill( "mu", "isoTrk || pfTau", nominal_wgt );
	    }

	  }

	}


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



	h1_wgt_cr2lTriggerSF->Fill( wgtInfo->sf_cr2lTrigger, nominal_wgt );

	
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
		  
		  
		  // Loop over mass point list
		  for(int iMassPt=0; iMassPt<(int)h_nMassPt; iMassPt++){

		    if( wgtInfo->mStop != sample.massPtList[iMassPt].first ) continue;
		    if( wgtInfo->mLSP != sample.massPtList[iMassPt].second ) continue;
		   
		    // nJets
		    if( h1_scan_nJets[iMassPt]->histos[iHist] ) h1_scan_nJets[iMassPt]->histos[iHist]->Fill( ngoodjets(), sysWgtsList[iSys].second );

		    // modTop
		    if( h1_scan_modTop[iMassPt]->histos[iHist] ) h1_scan_modTop[iMassPt]->histos[iHist]->Fill( modTopness, sysWgtsList[iSys].second );
		    
		    // mt2w
		    if( h1_scan_mt2w[iMassPt]->histos[iHist] ) h1_scan_mt2w[iMassPt]->histos[iHist]->Fill( mt2w, sysWgtsList[iSys].second );

		    // met
		    if( h1_scan_met[iMassPt]->histos[iHist] ) h1_scan_met[iMassPt]->histos[iHist]->Fill( met, sysWgtsList[iSys].second );
		    
		    // pfmet
		    if( h1_scan_pfmet[iMassPt]->histos[iHist] ) h1_scan_pfmet[iMassPt]->histos[iHist]->Fill( pfmet(), sysWgtsList[iSys].second );
		    
		    // mt
		    if( h1_scan_mt[iMassPt]->histos[iHist] ) h1_scan_mt[iMassPt]->histos[iHist]->Fill( mt, sysWgtsList[iSys].second );

		    // jet1 pt
		    if( h1_scan_jet1_pt[iMassPt]->histos[iHist] ) h1_scan_jet1_pt[iMassPt]->histos[iHist]->Fill( ak4pfjets_p4().at(0).Pt(), sysWgtsList[iSys].second );

		    // jet2 pt
		    if( h1_scan_jet2_pt[iMassPt]->histos[iHist] ) h1_scan_jet2_pt[iMassPt]->histos[iHist]->Fill( ak4pfjets_p4().at(1).Pt(), sysWgtsList[iSys].second );


		    // jet pt
		    if( h1_scan_jet_pt[iMassPt]->histos[iHist] ){
		      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
			h1_scan_jet_pt[iMassPt]->histos[iHist]->Fill( ak4pfjets_p4().at(iJet).Pt(), sysWgtsList[iSys].second );
			if( h1_scan_jet_pt_notJ1J2[iMassPt]->histos[iHist] ){
			  if( iJet!=0 && iJet!=1 ) h1_scan_jet_pt_notJ1J2[iMassPt]->histos[iHist]->Fill( ak4pfjets_p4().at(iJet).Pt(), sysWgtsList[iSys].second );
			}
		      }
		    }


		    // lep1lep2bb pt
		    if( h1_scan_lep1lep2bb_pt[iMassPt]->histos[iHist] ) h1_scan_lep1lep2bb_pt[iMassPt]->histos[iHist]->Fill( lep1lep2bb_pt, sysWgtsList[iSys].second );

		    // lep1lep2bbMet pt
		    if( h1_scan_lep1lep2bbMet_pt[iMassPt]->histos[iHist] ) h1_scan_lep1lep2bbMet_pt[iMassPt]->histos[iHist]->Fill( lep1lep2bbMet_pt, sysWgtsList[iSys].second );



		  } // end loop over mass points

		} 
		// Data and Backgrounds
		else{

		  // Yields
		  if( h1_yield->histos[iYieldHist] ) h1_yield->histos[iYieldHist]->Fill( passCatList[iCat].first.label.c_str(), sysWgtsList[iSys].second );

		  // gen ttbar pT
		  if( sampleIsTTbar ){
		    if( h1_gen_ttbar_pt->histos[iHist] ) h1_gen_ttbar_pt->histos[iHist]->Fill( ttbarPt, sysWgtsList[iSys].second );
		    if( pfmet()>350.0 ){
		      if( h1_gen_ttbar_pt__ge350met->histos[iHist] ) h1_gen_ttbar_pt__ge350met->histos[iHist]->Fill( ttbarPt, sysWgtsList[iSys].second );
		    }
		    if( mt2w>200.0 ){
		      if( h1_gen_ttbar_pt__ge200mt2w->histos[iHist] ) h1_gen_ttbar_pt__ge200mt2w->histos[iHist]->Fill( ttbarPt, sysWgtsList[iSys].second );
		      if( pfmet()>350.0 ){
			if( h1_gen_ttbar_pt__ge200mt2w_ge350met->histos[iHist] ) h1_gen_ttbar_pt__ge200mt2w_ge350met->histos[iHist]->Fill( ttbarPt, sysWgtsList[iSys].second );
		      }
		    }
		  } // end if sample is ttbar

		  
		  // nJets
		  if( h1_nJets->histos[iHist] ) h1_nJets->histos[iHist]->Fill( ngoodjets(), sysWgtsList[iSys].second );

		  // modTop
		  if( h1_modTop->histos[iHist] ) h1_modTop->histos[iHist]->Fill( modTopness, sysWgtsList[iSys].second );

		  // mt2w
		  if( h1_mt2w->histos[iHist] ) h1_mt2w->histos[iHist]->Fill( mt2w, sysWgtsList[iSys].second );
		  
		  // met
		  if( h1_met->histos[iHist] ) h1_met->histos[iHist]->Fill( met, sysWgtsList[iSys].second );

		  // pfmet
		  if( h1_pfmet->histos[iHist] ) h1_pfmet->histos[iHist]->Fill( pfmet(), sysWgtsList[iSys].second );

		  // mt
		  if( h1_mt->histos[iHist] ) h1_mt->histos[iHist]->Fill( mt, sysWgtsList[iSys].second );

		  // jet1 pt
		  if( h1_jet1_pt->histos[iHist] ) h1_jet1_pt->histos[iHist]->Fill( ak4pfjets_p4().at(0).Pt(), sysWgtsList[iSys].second );

		  // jet2 pt
		  if( h1_jet2_pt->histos[iHist] ) h1_jet2_pt->histos[iHist]->Fill( ak4pfjets_p4().at(1).Pt(), sysWgtsList[iSys].second );

		  // jet pt
		  if( h1_jet_pt->histos[iHist] ){
		    for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
		      h1_jet_pt->histos[iHist]->Fill( ak4pfjets_p4().at(iJet).Pt(), sysWgtsList[iSys].second );
		      if( h1_jet_pt_notJ1J2->histos[iHist] ){
			if( iJet!=0 && iJet!=1 ) h1_jet_pt_notJ1J2->histos[iHist]->Fill( ak4pfjets_p4().at(iJet).Pt(), sysWgtsList[iSys].second );
		      }
		    }
		  }
		  
		  // lep1lep2bb pt
		  if( h1_lep1lep2bb_pt->histos[iHist] ) h1_lep1lep2bb_pt->histos[iHist]->Fill( lep1lep2bb_pt, sysWgtsList[iSys].second );

		  // lep1lep2bbMet pt
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

