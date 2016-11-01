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
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

// sntCORE
#include "../../CORE/Tools/dorky/dorky.cc"
#include "../../CORE/Tools/goodrun.h"

// stopCORE
#include "../StopCORE/stop_1l_babyAnalyzer.cc"
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/selectionInfo.h"
#include "../StopCORE/sysInfo.h"


using namespace std;
using namespace tas;
using namespace stop_1l;


//////////////////////////////
//                          //
// Configuration Parameters //
//                          //
//////////////////////////////

bool analyzeFast_           = true; // skips systematics

bool applyjson              = true;

bool add2ndLepToMet_        = false;

bool useBTagSFs_fromUtils_  = false;
bool useLepSFs_fromUtils_   = false;
        
bool apply_diLepTrigger_sf_ = true; // for ee/emu/mumu triggers only
bool apply_bTag_sf_         = true; // event weight, product of all jet wgts
bool apply_lep_sf_          = true; // both lep1 and lep2 (if available) are multiplied together
bool apply_lepFS_sf_        = false;
bool apply_topPt_sf_        = false; // true=sf, false=uncertainty
bool apply_metRes_sf_       = false;
bool apply_ttbarSysPt_sf_   = false;  // true=sf, false=uncertainty, only !=1.0 for madgraph tt2l, tW2l
bool apply_ISR_sf_          = false; // only !=1.0 for signal
bool apply_sample_sf_       = false; // only !=1.0 for some WJetsHT samps
  

//
// Function Declarations
//
int looper( sampleInfo::ID sample, int nEvents=-1, bool readFast=true );


//
// Main
//
int stopBabyLooper__CR2l_bulkTTbar(){


  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList_CR2l_bulkTTbar(); 


  //
  // Examples for Quick Tests
  //
  //sampleList.clear();
  //sampleList.push_back( sampleInfo::k_diLepton );
  //sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8 ); 
  

  //
  // Loop over samples
  //
  for( int iSample=0; iSample<(int)sampleList.size(); iSample++){
    looper( sampleList[iSample] );
  }


  //
  // Done
  //
  return 0;

}




//
// Functions
//
int looper( sampleInfo::ID sampleID, int nEvents, bool readFast ) {


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
  // Benchmark
  //
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
  

  //
  // Input SampleInfo
  //
  sampleInfo::sampleUtil sample( sampleID );

  bool sampleIsTTbar = false;
  if( sample.id == sampleInfo::k_ttbar_powheg_pythia8 ||
      sample.id == sampleInfo::k_ttbar_powheg_pythia8_ext4 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 ||
      sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8 ||
      sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ){
    sampleIsTTbar = true;
  }
  
  //
  // Input chain
  //
  TChain *chain = new TChain("t");
  
  cout << "    Processing the following: " << endl;  
  for(int iFile=0; iFile<(int)sample.inputBabies.size(); iFile++){
    
    // input directory
    TString input = sample.baby_i_o.first;
    input.ReplaceAll("/skim/","/output/");

    // input file
    input += sample.inputBabies[iFile];
      
    chain->Add( input );
    cout << "      " << input << endl; 
  }
  cout << endl;
  
  
  //
  // Output File
  //

  // output dir
  string f_output_name = "";
  f_output_name += sample.baby_i_o.second;

  // output name
  f_output_name += sample.label;
  f_output_name += ".root";

  // output file
  TFile *f_output = new TFile( f_output_name.c_str(), "recreate" );

  // print output location
  cout << "    Output Written to: " << endl;
  cout << "      " << f_output_name << endl;
  cout << endl;
  
  
  //
  // Selection Bools
  //
  
  bool pass_evtSel        = false;
  bool pass_evtSel_jup    = false;
  bool pass_evtSel_jdown  = false;
  TH1D *h_cutflow_evtSel  = selectionInfo::get_cutflowHistoTemplate_CR2l_bulkTTbar();
  h_cutflow_evtSel->SetDirectory(f_output);

  vector< std::pair< TString, bool > > v_lepFlav; 
  std::pair< TString, bool > lepFlav;
  lepFlav.first = "ee";   lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  lepFlav.first = "emu";  lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  lepFlav.first = "mumu"; lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  lepFlav.first = "incl"; lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  const int nLepFlav = v_lepFlav.size();


  //
  // JSON File Tools
  //
  const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-282037_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"; // 29.53fb golden json
  //const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"; // ICHEP 12.9fb SUS-16-028
  if( sample.isData ) set_goodrun_file_json(json_file);
  

  //
  // Event Weight Utilities
  //
  cout << "    Loading eventWeight Utilities..." << endl << endl;
  sysInfo::evtWgtInfo *wgtInfo = new sysInfo::evtWgtInfo( sample.id, useBTagSFs_fromUtils_, useLepSFs_fromUtils_, add2ndLepToMet_ );  
  wgtInfo->apply_diLepTrigger_sf = false;
  wgtInfo->apply_bTag_sf         = apply_bTag_sf_;
  wgtInfo->apply_lep_sf          = apply_lep_sf_;
  wgtInfo->apply_lepFS_sf        = apply_lepFS_sf_;
  wgtInfo->apply_topPt_sf        = apply_topPt_sf_;
  wgtInfo->apply_metRes_sf       = apply_metRes_sf_;
  wgtInfo->apply_ttbarSysPt_sf   = apply_ttbarSysPt_sf_;
  wgtInfo->apply_ISR_sf          = apply_ISR_sf_;
  wgtInfo->apply_sample_sf       = apply_sample_sf_;
  
  
  //
  // Declare Systematics
  //
  cout << "    Loading systematicList: ";
  std::vector< sysInfo::Util > systematicList;
  if( sample.isData || analyzeFast_ ){
    systematicList.push_back(sysInfo::Util(sysInfo::k_nominal));
  }
  else{
    for(int iSys=0; iSys<sysInfo::k_nSys; iSys++){
      systematicList.push_back( sysInfo::Util(sysInfo::ID(iSys)) );
    }
  }  
  const int nSystematics = (int)systematicList.size();
  cout << nSystematics << " systematics" << endl << endl;
  
  //
  // Declare genClassification list
  //
  cout << "    Loading genClassyList: ";
  std::vector< genClassyInfo::Util > genClassyList;
  if( sample.isData ){
    genClassyList.push_back(genClassyInfo::Util(genClassyInfo::k_incl));
  }
  else{
    for(int iGenClassy=0; iGenClassy<genClassyInfo::k_nGenClassy; iGenClassy++){
      genClassyList.push_back( genClassyInfo::Util(genClassyInfo::ID(iGenClassy)) );
    }
  }
  const int nGenClassy=(int)genClassyList.size();
  bool passGenClassy[nGenClassy];
  cout << nGenClassy << " genClassifications" << endl << endl;


  //
  // Declare Category Utils
  //
  vector<int> passCats_CR2l_bulkTTbar; 
  vector<int> passCats_CR2l_bulkTTbar_jup;
  vector<int> passCats_CR2l_bulkTTbar_jdown;
  
  
  ////////////////////////
  //                    //
  // Declare Histograms //
  //                    //
  ////////////////////////
  //
  //
  //  For Using DownStream Scripts, please adhere to the conventions:
  //
  //
  //    histogram_name = "your_name_here"+"__emu"+"__genClassy_"+genClassyObject.label+"__systematic_"+sysInfoObject.label;
  //
  //
  //  Where "__emu" can be replaced by "__ee", or "__mumu", or "__incl"
  //
  //    And systematicList[0] is the nominal selection
  //
  //    And if there is andditional selection involved in this histogram, please refer to it in "you name here"
  //

  cout << "    Loading histograms" << endl << endl;
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  

  //
  // Yields
  //
  const int nHistos = nLepFlav*nGenClassy*nSystematics;
  
  // CR2l bulk TTbar bins
  TH1D *h_yields_CR2l_bulkTTbar_template = categoryInfo::getYieldHistoTemplate_CR2l_bulkTTbar();
  TH1D *h_yields_CR2l_bulkTTbar[nHistos];
  
  // Loop over lepFlavs, genClassifications and systematics
  for(int iFlav=0; iFlav<nLepFlav; iFlav++){
    for(int iGen=0; iGen<nGenClassy; iGen++){
      for(int iSys=0; iSys<nSystematics; iSys++){
	
	// Histo Index
	int iHisto = iFlav*nGenClassy*nSystematics + iGen*nSystematics + iSys;
	//int iHisto = iGen*nSystematics + iSys;
	
	// Flav, Gen and Systematic String
	TString flav_gen_sys_name = "__lepFlav_";
	flav_gen_sys_name += v_lepFlav[iFlav].first; 
	flav_gen_sys_name += "__genClassy_";
	flav_gen_sys_name += genClassyList[iGen].label;
	flav_gen_sys_name += "__systematic_";
	flav_gen_sys_name += systematicList[iSys].label;


	// CR2l bulk TTbar Singal Regions

	// Baseline Name
	TString h_name_CR2l_bulkTTbar_base = h_yields_CR2l_bulkTTbar_template->GetName();
	
	// yields
	TString h_name_CR2l_bulkTTbar = h_name_CR2l_bulkTTbar_base;
	h_name_CR2l_bulkTTbar += flav_gen_sys_name;
	h_yields_CR2l_bulkTTbar[iHisto] = (TH1D*)h_yields_CR2l_bulkTTbar_template->Clone(h_name_CR2l_bulkTTbar);
	h_yields_CR2l_bulkTTbar[iHisto]->SetDirectory(f_output);

       
      } // end loop over systematics
    } // end loop over gen classifications
  } // end loop over lepton flavours

  
  //////////////////////////
  //                      //
  // Non-yield Histograms //
  //                      //
  //////////////////////////

  // nBTags
  TH1D *h_nBTags[nLepFlav][nGenClassy];
  
  // nJets
  TH1D *h_nJets_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_nJets_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_nJets_ge2bTags[nLepFlav][nGenClassy];
  
  // lep1 pT
  TH1D *h_lep1Pt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1Pt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1Pt_ge2bTags[nLepFlav][nGenClassy];

  // lep2 pT
  TH1D *h_lep2Pt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_lep2Pt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_lep2Pt_ge2bTags[nLepFlav][nGenClassy];

  // diLep pT
  TH1D *h_diLepPt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_diLepPt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_diLepPt_ge2bTags[nLepFlav][nGenClassy];

  // jet pT
  TH1D *h_jetPt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_jetPt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_jetPt_ge2bTags[nLepFlav][nGenClassy];

  // jet 1 pT
  TH1D *h_jet1Pt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_jet1Pt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_jet1Pt_ge2bTags[nLepFlav][nGenClassy];

  // jet 2 pT
  TH1D *h_jet2Pt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_jet2Pt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_jet2Pt_ge2bTags[nLepFlav][nGenClassy];

  // csv jet 1 pT
  TH1D *h_csvJet1Pt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_csvJet1Pt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_csvJet1Pt_ge2bTags[nLepFlav][nGenClassy];

  // csv jet 2 pT
  TH1D *h_csvJet2Pt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_csvJet2Pt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_csvJet2Pt_ge2bTags[nLepFlav][nGenClassy];
  
  // met
  TH1D *h_met_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_met_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_met_ge2bTags[nLepFlav][nGenClassy];

  // lep1lep2bbMet, ttbar visible system pT
  TH1D *h_lep1lep2bbPt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1lep2bbPt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1lep2bbPt_ge2bTags[nLepFlav][nGenClassy];
 
  // lep1lep2bbMet, ttbar system pT
  TH1D *h_lep1lep2bbMetPt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1lep2bbMetPt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1lep2bbMetPt_ge2bTags[nLepFlav][nGenClassy];
 
  for(int iFlav=0; iFlav<nLepFlav; iFlav++){
    for(int iGen=0; iGen<nGenClassy; iGen++){
      
      TString hName = "";
      
      TString flav_gen_sys_name = "__lepFlav_";
      flav_gen_sys_name += v_lepFlav[iFlav].first; 
      flav_gen_sys_name += "__genClassy_";
      flav_gen_sys_name += genClassyList[iGen].label;
      flav_gen_sys_name += "__systematic_";
      flav_gen_sys_name += systematicList[0].label;


      // NBTags
      hName = "h_nBTags";
      hName += flav_gen_sys_name;
      h_nBTags[iFlav][iGen] = new TH1D( hName, "Number of bTagged Jets;nBTags", 5, -0.5, 4.5);
      h_nBTags[iFlav][iGen]->SetDirectory(f_output);


      // Njets, g0bTags
      hName = "h_nJets__ge0bTags";
      hName += flav_gen_sys_name;
      h_nJets_ge0bTags[iFlav][iGen] = new TH1D( hName, "Number of Selected Jets, >=0 bTags;nJets", 11, -0.5, 10.5);
      h_nJets_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // Njets, g1bTags
      hName = "h_nJets__ge1bTags";
      hName += flav_gen_sys_name;
      h_nJets_ge1bTags[iFlav][iGen] = new TH1D( hName, "Number of Selected Jets, >=1 bTags;nJets", 11, -0.5, 10.5);
      h_nJets_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // Njets, g2bTags
      hName = "h_nJets__ge2bTags";
      hName += flav_gen_sys_name;
      h_nJets_ge2bTags[iFlav][iGen] = new TH1D( hName, "Number of Selected Jets, >=2 bTags;nJets", 11, -0.5, 10.5);
      h_nJets_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // lep1 pT, ge0bTags
      hName = "h_lep1Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_lep1Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Leading Lepton pT, >=0 bTags;pT [GeV]", 20, 0.0, 200.0);
      h_lep1Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // lep1 pT, ge1bTags
      hName = "h_lep1Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_lep1Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Leading Lepton pT, >=1 bTags;pT [GeV]", 20, 0.0, 200.0);
      h_lep1Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // lep1 pT, ge2bTags
      hName = "h_lep1Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_lep1Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Leading Lepton pT, >=2 bTags;pT [GeV]", 20, 0.0, 200.0);
      h_lep1Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);

     
      // lep2 pT, ge0bTags
      hName = "h_lep2Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_lep2Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Trailing Lepton pT, >=0 bTags;pT [GeV]", 20, 0.0, 200.0);
      h_lep2Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // lep2 pT, ge1bTags
      hName = "h_lep2Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_lep2Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Trailing Lepton pT, >=1 bTags;pT [GeV]", 20, 0.0, 200.0);
      h_lep2Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // lep2 pT, ge2bTags
      hName = "h_lep2Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_lep2Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Trailing Lepton pT, >=2 bTags;pT [GeV]", 20, 0.0, 200.0);
      h_lep2Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);

      
      // diLep pT, ge0bTags
      hName = "h_diLepPt__ge0bTags";
      hName += flav_gen_sys_name;
      h_diLepPt_ge0bTags[iFlav][iGen] = new TH1D( hName, "diLepton System pT, >=0 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_diLepPt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // diLep pT, ge1bTags
      hName = "h_diLepPt__ge1bTags";
      hName += flav_gen_sys_name;
      h_diLepPt_ge1bTags[iFlav][iGen] = new TH1D( hName, "diLepton System pT, >=1 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_diLepPt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // diLep pT, ge2bTags
      hName = "h_diLepPt__ge2bTags";
      hName += flav_gen_sys_name;
      h_diLepPt_ge2bTags[iFlav][iGen] = new TH1D( hName, "diLepton System pT, >=2 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_diLepPt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // jet pT, ge0bTags
      hName = "h_jetPt__ge0bTags";
      hName += flav_gen_sys_name;
      h_jetPt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Selected Jet pT, >=0 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jetPt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet pT, ge1bTags
      hName = "h_jetPt__ge1bTags";
      hName += flav_gen_sys_name;
      h_jetPt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Selected Jet pT, >=1 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jetPt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet pT, ge2bTags
      hName = "h_jetPt__ge2bTags";
      hName += flav_gen_sys_name;
      h_jetPt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Selected Jet pT, >=2 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jetPt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // jet1 pT, ge0bTags
      hName = "h_jet1Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_jet1Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Leading Jet pT, >=0 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jet1Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet1 pT, ge1bTags
      hName = "h_jet1Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_jet1Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Leading Jet pT, >=1 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jet1Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet1 pT, ge2bTags
      hName = "h_jet1Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_jet1Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Leading Jet pT, >=2 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jet1Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // jet2 pT, ge0bTags
      hName = "h_jet2Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_jet2Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Trailing Jet pT, >=0 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jet2Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet2 pT, ge1bTags
      hName = "h_jet2Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_jet2Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Trailing Jet pT, >=1 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jet2Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet2 pT, ge2bTags
      hName = "h_jet2Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_jet2Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Trailing Jet pT, >=2 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_jet2Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // csvJet1 pT, ge0bTags
      hName = "h_csvJet1Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_csvJet1Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=0 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_csvJet1Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet1 pT, ge1bTags
      hName = "h_csvJet1Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_csvJet1Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=1 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_csvJet1Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet1 pT, ge2bTags
      hName = "h_csvJet1Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_csvJet1Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=2 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_csvJet1Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // csvJet2 pT, ge0bTags
      hName = "h_csvJet2Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_csvJet2Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=0 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_csvJet2Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet2 pT, ge1bTags
      hName = "h_csvJet2Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_csvJet2Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=1 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_csvJet2Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet2 pT, ge2bTags
      hName = "h_csvJet2Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_csvJet2Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=2 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_csvJet2Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // MET, ge0bTags
      hName = "h_met__ge0bTags";
      hName += flav_gen_sys_name;
      h_met_ge0bTags[iFlav][iGen] = new TH1D( hName, "MET, >=0 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_met_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // MET, ge1bTags
      hName = "h_met__ge1bTags";
      hName += flav_gen_sys_name;
      h_met_ge1bTags[iFlav][iGen] = new TH1D( hName, "MET, >=1 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_met_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // MET, ge2bTags
      hName = "h_met__ge2bTags";
      hName += flav_gen_sys_name;
      h_met_ge2bTags[iFlav][iGen] = new TH1D( hName, "MET, >=2 bTags;pT [GeV]", 40, 0.0, 400.0);
      h_met_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // lep1lep2bb pT, ge0bTags
      hName = "h_lep1lep2bbPt__ge0bTags";
      hName += flav_gen_sys_name;
      h_lep1lep2bbPt_ge0bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bb, t#bar{t} visible system, p_{T}, >=0 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      h_lep1lep2bbPt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);
      
      // lep1lep2bb pT, ge1bTags
      hName = "h_lep1lep2bbPt__ge1bTags";
      hName += flav_gen_sys_name;
      h_lep1lep2bbPt_ge1bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bb, t#bar{t} visible system, p_{T}, >=1 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      h_lep1lep2bbPt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // lep1lep2bb pT, ge2bTags
      hName = "h_lep1lep2bbPt__ge2bTags";
      hName += flav_gen_sys_name;
      h_lep1lep2bbPt_ge2bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bb, t#bar{t} visible system, p_{T}, >=2 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      h_lep1lep2bbPt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);

      
      // lep1lep2bbMet pT, ge0bTags
      hName = "h_lep1lep2bbMetPt__ge0bTags";
      hName += flav_gen_sys_name;
      h_lep1lep2bbMetPt_ge0bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=0 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      h_lep1lep2bbMetPt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);
      
      // lep1lep2bbMet pT, ge1bTags
      hName = "h_lep1lep2bbMetPt__ge1bTags";
      hName += flav_gen_sys_name;
      h_lep1lep2bbMetPt_ge1bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      h_lep1lep2bbMetPt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // lep1lep2bbMet pT, ge2bTags
      hName = "h_lep1lep2bbMetPt__ge2bTags";
      hName += flav_gen_sys_name;
      h_lep1lep2bbMetPt_ge2bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=2 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      h_lep1lep2bbMetPt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);



    } // end loop over genClassifications for histogram arrays
  } // end loop over leptonFlavs for histogram arrays


  /*
      
  
  //
  // modified Topness
  //
  cat_temp.clear(); sys_temp.clear();

  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
  
  sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
  
  
  //
  // MT2W
  //
  cat_temp.clear(); sys_temp.clear();
  
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  
  sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
  
  
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
  
  

  //
  // MT
  //
  cat_temp.clear(); sys_temp.clear();

  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  
  sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
  
  
  //
  // jet pT
  //
  cat_temp.clear(); sys_temp.clear();
  
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );
  
  sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );

   


  //
  // lep1,lep2,b,bbar pT
  //
  cat_temp.clear(); sys_temp.clear();
  
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );
  
  sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
  
  
  //
  // lep1,lep2,b,bbar,MET pT
  //
  cat_temp.clear(); sys_temp.clear();
  
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  cat_temp.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_250toInfmet) );
  
  sys_temp.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
  */
      

  


  //////////////////////
  //                  //
  // Loop Over Events //
  //                  //
  //////////////////////
    
  // Event Counters
  cout << "    Loading files to loop over" << endl << endl;
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  
  // Grab list of files
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    
    
    //////////////////////
    //                  //
    // Get File Content //
    //                  //
    //////////////////////
    
    // Open File and Get Tree
    TFile *file = new TFile( currentFile->GetTitle(), "read" );
    TTree *tree = (TTree*)file->Get("t");
    if(readFast) TTreeCache::SetLearnEntries(10);
    if(readFast) tree->SetCacheSize(128*1024*1024);
    babyAnalyzer.Init(tree);

    // Get weight histogram from baby
    wgtInfo->getWeightHistogramFromBaby( file );
            
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {


      ///////////////////////
      //                   //
      // Get Event Content //
      //                   //
      ///////////////////////
   
      // Read Tree
      if( nEventsTotal >= nEventsChain ) continue;
      if(readFast) tree->LoadTree(event);
      babyAnalyzer.GetEntry(event);
      ++nEventsTotal;

      // Progress
      stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );

      
      /////////////////////
      //                 //
      // Check Selection //
      //                 //
      /////////////////////


      // Check JSON
      if( sample.isData && applyjson ){
	if( !goodrun(run(),ls()) ) continue;
      }
	
      // Check duplicate event
      if( sample.isData ){
	duplicate_removal::DorkyEventIdentifier id(run(), evt(), ls());
	if( is_duplicate(id) ) continue;
      }

      // Check WNJets genPt
      if( sample.id == sampleInfo::k_W1JetsToLNu_madgraph_pythia8 ||
	  sample.id == sampleInfo::k_W2JetsToLNu_madgraph_pythia8 ||
	  sample.id == sampleInfo::k_W3JetsToLNu_madgraph_pythia8 ||
	  sample.id == sampleInfo::k_W4JetsToLNu_madgraph_pythia8    ){
	if( genmet()>200.0 ) continue;
      }

      bool passAnyRegion = false;

      // Evt Selection
      pass_evtSel = selectionInfo::pass_CR2l_bulkTTbar(0, -1, add2ndLepToMet_);

      if( !sample.isData && !analyzeFast_ ) pass_evtSel_jup   = selectionInfo::pass_CR2l_bulkTTbar(1,  -1, add2ndLepToMet_);
      if( !sample.isData && !analyzeFast_ ) pass_evtSel_jdown = selectionInfo::pass_CR2l_bulkTTbar(-1, -1, add2ndLepToMet_);

      if( pass_evtSel || pass_evtSel_jup || pass_evtSel_jdown ) passAnyRegion=true;

      // Cutflow
      vector<bool> cutflow = selectionInfo::get_selectionResults_CR2l_bulkTTbar(0);
      for(int i=0; i<(int)cutflow.size(); i++){
	if(!cutflow[i]) break;
	h_cutflow_evtSel->Fill( i, cutflow[i] );
      }


      //
      // Continue if Event Passes No Region of Interest
      //
      if( !passAnyRegion ) continue;



      // Check Lepton Flavs
      for(int iFlav=0; iFlav<nLepFlav; iFlav++){
	if( v_lepFlav[iFlav].first=="ee" ){
	  if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==22 ){ v_lepFlav[iFlav].second = true; }
	}
	if( v_lepFlav[iFlav].first=="emu" ){
	  if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==24 ){ v_lepFlav[iFlav].second = true; }
	}
	if( v_lepFlav[iFlav].first=="mumu" ){
	  if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==26 ){ v_lepFlav[iFlav].second = true; }
	}
	if( v_lepFlav[iFlav].first=="incl" ){ v_lepFlav[iFlav].second = true; }
      }
	
      
      

      /////////////////////////////
      //                         //
      // Calculate Event Weights //
      //                         //
      /////////////////////////////
   
      wgtInfo->getEventWeights( analyzeFast_ );

      double wgt_nominal = wgtInfo->sys_wgts[sysInfo::k_nominal];



      ///////////////////////////////
      //                           //
      // Check Gen Classifications //
      //                           //
      ///////////////////////////////
   
      for(int i=0; i<nGenClassy; i++){
	passGenClassy[i] = genClassyList[i].eval_GenClassy();
      }



      ////////////////////////////
      //                        //
      // Check Yield Cateogries //
      //                        //
      ////////////////////////////
   
      // CR2l bulk TTbar regions
      passCats_CR2l_bulkTTbar.clear(); 
      passCats_CR2l_bulkTTbar_jup.clear();
      passCats_CR2l_bulkTTbar_jdown.clear();

      if( pass_evtSel ){
	passCats_CR2l_bulkTTbar = categoryInfo::passCategory_CR2l_bulkTTbar(0, add2ndLepToMet_);
      }
      
      // No JES for data
      if( !sample.isData ){
	if( pass_evtSel_jup ){
	  passCats_CR2l_bulkTTbar_jup = categoryInfo::passCategory_CR2l_bulkTTbar(1, add2ndLepToMet_);
	}
	if( pass_evtSel_jdown ){
	  passCats_CR2l_bulkTTbar_jdown = categoryInfo::passCategory_CR2l_bulkTTbar(-1, add2ndLepToMet_);
	}
      }
  
      
      /////////////////////////////
      //                         //
      // Compute Event Variables //
      //                         //
      /////////////////////////////
      
      
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

      } // end if sample is ttbar

   

      // lep1 lep2 b b TLV
      LorentzVector csvJet1_TLV(0.0,0.0,0.0,0.0);
      double csvJet1_pt = -99.9;

      LorentzVector csvJet2_TLV(0.0,0.0,0.0,0.0);
      double csvJet2_pt = -99.9;
      
      LorentzVector lep1lep2bb_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bb_pt = -99.9;

      LorentzVector lep1lep2bbMet_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bbMet_pt = -99.9;
      
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
      if(jet1_idx>=0){
	lep1lep2bb_TLV += ak4pfjets_p4().at(jet1_idx);
	csvJet1_TLV += ak4pfjets_p4().at(jet1_idx);
	csvJet1_pt = csvJet1_TLV.Pt();
      }
	
      int jet2_idx = -1;
      max_csv = -99.9;
      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
	if( iJet==jet1_idx ) continue;
	if( ak4pfjets_CSV().at(iJet) > max_csv ){
	  jet2_idx = iJet;
	  max_csv = ak4pfjets_CSV().at(iJet);
	}
      }
      if(jet2_idx>=0){
	lep1lep2bb_TLV += ak4pfjets_p4().at(jet2_idx);
	csvJet2_TLV += ak4pfjets_p4().at(jet2_idx);
	csvJet2_pt = csvJet2_TLV.Pt();
      }
	
      lep1lep2bb_pt = lep1lep2bb_TLV.Pt();
     
      
      // lep1 lep2 b b MET TLV
      lep1lep2bbMet_TLV = lep1lep2bb_TLV;

      if( add2ndLepToMet_ ){
	LorentzVector met_TLV( pfmet_rl()*cos(pfmet_phi_rl()), pfmet_rl()*sin(pfmet_phi_rl()), 0.0, pfmet_rl() );
	lep1lep2bbMet_TLV += met_TLV;
      }
      else{
	LorentzVector met_TLV( pfmet()*cos(pfmet_phi()), pfmet()*sin(pfmet_phi()), 0.0, pfmet() );
	lep1lep2bbMet_TLV += met_TLV;
      }
      lep1lep2bbMet_pt = lep1lep2bbMet_TLV.Pt();

    


      
      /////////////////////
      //                 //
      // Fill Histograms //
      //                 //
      /////////////////////
   
	
      //
      // Pass CR2l bulkTTbar Region
      //
      if( pass_evtSel || pass_evtSel_jup || pass_evtSel_jdown ){

	//
	// Yields
	//
	for(int iFlav=0; iFlav<nLepFlav; iFlav++){

	  if( !v_lepFlav[iFlav].second ) continue;

	  for(int iGen=0; iGen<nGenClassy; iGen++){
	  
	    if( !passGenClassy[iGen] ) continue;

	    for(int iSys=0; iSys<nSystematics; iSys++){
	  
	      if(iSys==sysInfo::k_JESUp){ if(!pass_evtSel_jup) continue; }
	      else if(iSys==sysInfo::k_JESDown){ if(!pass_evtSel_jdown) continue; }
	      else{ if(!pass_evtSel) continue; }

	      // Histo Index
	      int iHisto = iFlav*nGenClassy*nSystematics + iGen*nSystematics + iSys;
	      //int iHisto = iGen*nSystematics + iSys;
	
	      // Event Weight for this Systematic
	      double wgt = wgtInfo->sys_wgts[iSys];


	      // CR2l Bulk TTbar Regions
	    
	      // JES Up
	      if( iSys==sysInfo::k_JESUp ){
		for(int iCat=0; iCat<(int)passCats_CR2l_bulkTTbar_jup.size(); iCat++){
		  h_yields_CR2l_bulkTTbar[iHisto]->Fill( passCats_CR2l_bulkTTbar_jup[iCat], wgt );
		}
	      }
	      // JES Dn
	      else if( iSys==sysInfo::k_JESDown ){
		for(int iCat=0; iCat<(int)passCats_CR2l_bulkTTbar_jdown.size(); iCat++){
		  h_yields_CR2l_bulkTTbar[iHisto]->Fill( passCats_CR2l_bulkTTbar_jdown[iCat], wgt );
		}
	      }
	      // All Others
	      else{
		for(int iCat=0; iCat<(int)passCats_CR2l_bulkTTbar.size(); iCat++){
		  h_yields_CR2l_bulkTTbar[iHisto]->Fill( passCats_CR2l_bulkTTbar[iCat], wgt );
		}
	      }
	      

	    } // end loop over systematics
	  

	    //
	    // Non-yield Histograms
	    //
	    

	    // nBTags
	    h_nBTags[iFlav][iGen]->Fill( ngoodbtags(), wgt_nominal );

	    // nJets
	    if( ngoodbtags()>=0 ) h_nJets_ge0bTags[iFlav][iGen]->Fill( ngoodjets(), wgt_nominal );
	    if( ngoodbtags()>=1 ) h_nJets_ge1bTags[iFlav][iGen]->Fill( ngoodjets(), wgt_nominal );
	    if( ngoodbtags()>=2 ) h_nJets_ge2bTags[iFlav][iGen]->Fill( ngoodjets(), wgt_nominal );
	    
	    // lep1 pT
	    if( ngoodbtags()>=0 ) h_lep1Pt_ge0bTags[iFlav][iGen]->Fill( lep1_p4().Pt(), wgt_nominal );
	    if( ngoodbtags()>=1 ) h_lep1Pt_ge1bTags[iFlav][iGen]->Fill( lep1_p4().Pt(), wgt_nominal );
	    if( ngoodbtags()>=2 ) h_lep1Pt_ge2bTags[iFlav][iGen]->Fill( lep1_p4().Pt(), wgt_nominal );

	    // lep2 pT
	    if( ngoodbtags()>=0 ) h_lep2Pt_ge0bTags[iFlav][iGen]->Fill( lep2_p4().Pt(), wgt_nominal );
	    if( ngoodbtags()>=1 ) h_lep2Pt_ge1bTags[iFlav][iGen]->Fill( lep2_p4().Pt(), wgt_nominal );
	    if( ngoodbtags()>=2 ) h_lep2Pt_ge2bTags[iFlav][iGen]->Fill( lep2_p4().Pt(), wgt_nominal );

	    // diLep pT
	    if( ngoodbtags()>=0 ) h_diLepPt_ge0bTags[iFlav][iGen]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt_nominal );
	    if( ngoodbtags()>=1 ) h_diLepPt_ge1bTags[iFlav][iGen]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt_nominal );
	    if( ngoodbtags()>=2 ) h_diLepPt_ge2bTags[iFlav][iGen]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt_nominal );

	    // jet pT
	    for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
	      if( ngoodbtags()>=0 ) h_jetPt_ge0bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[iJet].Pt(), wgt_nominal );
	      if( ngoodbtags()>=1 ) h_jetPt_ge1bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[iJet].Pt(), wgt_nominal );
	      if( ngoodbtags()>=2 ) h_jetPt_ge2bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[iJet].Pt(), wgt_nominal );
	    }

	    // jet1 pt
	    if( ngoodbtags()>=0 ) h_jet1Pt_ge0bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[0].Pt(), wgt_nominal );
	    if( ngoodbtags()>=1 ) h_jet1Pt_ge1bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[0].Pt(), wgt_nominal );
	    if( ngoodbtags()>=2 ) h_jet1Pt_ge2bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[0].Pt(), wgt_nominal );

	    // jet 2 pt
	    if( ngoodbtags()>=0 ) h_jet2Pt_ge0bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[1].Pt(), wgt_nominal );
	    if( ngoodbtags()>=1 ) h_jet2Pt_ge1bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[1].Pt(), wgt_nominal );
	    if( ngoodbtags()>=2 ) h_jet2Pt_ge2bTags[iFlav][iGen]->Fill( ak4pfjets_p4()[1].Pt(), wgt_nominal );

	    // csvJet1 pt
	    if( ngoodbtags()>=0 ) h_csvJet1Pt_ge0bTags[iFlav][iGen]->Fill( csvJet1_pt, wgt_nominal );
	    if( ngoodbtags()>=1 ) h_csvJet1Pt_ge1bTags[iFlav][iGen]->Fill( csvJet1_pt, wgt_nominal );
	    if( ngoodbtags()>=2 ) h_csvJet1Pt_ge2bTags[iFlav][iGen]->Fill( csvJet1_pt, wgt_nominal );

	    // csvJet 2 pt
	    if( ngoodbtags()>=0 ) h_csvJet2Pt_ge0bTags[iFlav][iGen]->Fill( csvJet2_pt, wgt_nominal );
	    if( ngoodbtags()>=1 ) h_csvJet2Pt_ge1bTags[iFlav][iGen]->Fill( csvJet2_pt, wgt_nominal );
	    if( ngoodbtags()>=2 ) h_csvJet2Pt_ge2bTags[iFlav][iGen]->Fill( csvJet2_pt, wgt_nominal );

	    // met
	    if( add2ndLepToMet_ ){
	      if( ngoodbtags()>=0 ) h_met_ge0bTags[iFlav][iGen]->Fill( pfmet_rl(), wgt_nominal );
	      if( ngoodbtags()>=1 ) h_met_ge1bTags[iFlav][iGen]->Fill( pfmet_rl(), wgt_nominal );
	      if( ngoodbtags()>=2 ) h_met_ge2bTags[iFlav][iGen]->Fill( pfmet_rl(), wgt_nominal );
	    }
	    else{
	      if( ngoodbtags()>=0 ) h_met_ge0bTags[iFlav][iGen]->Fill( pfmet(), wgt_nominal );
	      if( ngoodbtags()>=1 ) h_met_ge1bTags[iFlav][iGen]->Fill( pfmet(), wgt_nominal );
	      if( ngoodbtags()>=2 ) h_met_ge2bTags[iFlav][iGen]->Fill( pfmet(), wgt_nominal );
	    }
	    

	    // lep1lep2bb pT
	    if( ngoodbtags()>=0 ) h_lep1lep2bbPt_ge0bTags[iFlav][iGen]->Fill( lep1lep2bb_pt, wgt_nominal );
	    if( ngoodbtags()>=1 ) h_lep1lep2bbPt_ge1bTags[iFlav][iGen]->Fill( lep1lep2bb_pt, wgt_nominal );
	    if( ngoodbtags()>=2 ) h_lep1lep2bbPt_ge2bTags[iFlav][iGen]->Fill( lep1lep2bb_pt, wgt_nominal );


            // lep1lep2bbMet pT
	    if( ngoodbtags()>=0 ) h_lep1lep2bbMetPt_ge0bTags[iFlav][iGen]->Fill( lep1lep2bbMet_pt, wgt_nominal );
	    if( ngoodbtags()>=1 ) h_lep1lep2bbMetPt_ge1bTags[iFlav][iGen]->Fill( lep1lep2bbMet_pt, wgt_nominal );
	    if( ngoodbtags()>=2 ) h_lep1lep2bbMetPt_ge2bTags[iFlav][iGen]->Fill( lep1lep2bbMet_pt, wgt_nominal );


	  } // end loop over genClassifications
	} // end loop over lepton flavours

      } // end if pass CR2l bulkTTbar Region

      

     

    
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
  cout << endl;
  cout << "    Control Region, 2l bulk TTbar Cutflow: " << endl;
  for(int iCut=1; iCut<=(int)h_cutflow_evtSel->GetNbinsX(); iCut++){
    cout << "      nEvents pass " << h_cutflow_evtSel->GetXaxis()->GetBinLabel(iCut) << " = " << h_cutflow_evtSel->GetBinContent(iCut) << endl;
  }
  cout << endl;
  cout << "====================================================" << endl;

  
  //
  // Clean stopCORE objects
  //
  wgtInfo->~evtWgtInfo(); 


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
    


  //
  // Return!
  //
  return 0;

}

