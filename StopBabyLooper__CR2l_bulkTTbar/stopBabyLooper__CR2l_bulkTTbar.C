// Usage:
// > root -l -b -q head.C stopBabyLooper__CR2l_bulkTTbar.C++

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

bool analyzeFast_           = false;  // skips systematics

bool applyjson              = true;

bool add2ndLepToMet_        = false;

bool useBTagSFs_fromUtils_  = false;
bool useLepSFs_fromUtils_   = false;
        
bool apply_diLepTrigger_sf_ = true;  // for ee/emu/mumu triggers only
bool apply_bTag_sf_         = false;  // event weight, product of all jet wgts
bool apply_lep_sf_          = true;  // both lep1 and lep2 (if available) are multiplied together
bool apply_vetoLep_sf_      = true;  // this is actually the lost lepton sf, only !=1 if there is >=2 genLeptons and ==1 recoLeptons in the event
bool apply_lepFS_sf_        = false;
bool apply_topPt_sf_        = false; // true=sf, false=uncertainty
bool apply_metRes_sf_       = true;
bool apply_ttbarSysPt_sf_   = false; // true=sf, false=uncertainty, only !=1.0 for madgraph tt2l, tW2l
bool apply_ISR_sf_          = true; // only !=1.0 for signal
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
  //sampleList.push_back( sampleInfo::k_met );
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
  //lepFlav.first = "ee";   lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  lepFlav.first = "emu";  lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  //lepFlav.first = "mumu"; lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  //lepFlav.first = "incl"; lepFlav.second = false; v_lepFlav.push_back(lepFlav);
  const int nLepFlav = v_lepFlav.size();


  //
  // JSON File Tools
  //
  const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"; // 36.46fb final 2016 run 
  //const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-282037_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"; // 29.53fb golden json, intermediate status
  //const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"; // ICHEP 12.9fb SUS-16-028
  if( sample.isData ) set_goodrun_file_json(json_file);
  

  //
  // Event Weight Utilities
  //
  cout << "    Loading eventWeight Utilities..." << endl << endl;
  sysInfo::evtWgtInfo *wgtInfo = new sysInfo::evtWgtInfo( sample.id, useBTagSFs_fromUtils_, useLepSFs_fromUtils_, add2ndLepToMet_ );  
  wgtInfo->apply_diLepTrigger_sf = apply_diLepTrigger_sf_;
  wgtInfo->apply_bTag_sf         = apply_bTag_sf_;
  wgtInfo->apply_lep_sf          = apply_lep_sf_;
  wgtInfo->apply_vetoLep_sf      = apply_vetoLep_sf_;
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
    // Custom List
    systematicList.clear();
    systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_JESUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_JESDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_ISRUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_ISRDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_metResUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_metResDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_lepSFUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_lepSFDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_pdfUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_pdfDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_alphasUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_alphasDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_q2Up) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_q2Down) );
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


  //
  // Histograms with all systematics
  //
  TH1D *h_met_ge1bTags[nHistos];
  TH1D *h_met_ge1bTags_ge50ttbarSysPt[nHistos];
  TH1D *h_met_ge1bTags_ge100ttbarSysPt[nHistos];
  TH1D *h_met_ge1bTags_ge150ttbarSysPt[nHistos];
  
  TH1D *h_diLepPt_ge1bTags[nHistos];
  TH1D *h_diLepPt_ge1bTags_ge100met[nHistos];
  TH1D *h_diLepPt_ge1bTags_ge150met[nHistos];
  
  TH1D *h_lep1lep2bbMetPt_ge1bTags[nHistos];
  TH1D *h_lep1lep2bbMetPt_ge1bTags_ge100met[nHistos];
  TH1D *h_lep1lep2bbMetPt_ge1bTags_ge150met[nHistos];
  
  
  // Loop over lepFlavs, genClassifications and systematics
  for(int iFlav=0; iFlav<nLepFlav; iFlav++){
    for(int iGen=0; iGen<nGenClassy; iGen++){
      for(int iSys=0; iSys<nSystematics; iSys++){
	
	// Histo Index
	int iHisto = iFlav*nGenClassy*nSystematics + iGen*nSystematics + iSys;
	//int iHisto = iGen*nSystematics + iSys;
	
	TString hName = "";

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

	
	// MET, ge1bTags
	hName = "h_met__ge1bTags";
	hName += flav_gen_sys_name;
	h_met_ge1bTags[iHisto] = new TH1D( hName, "MET, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
	h_met_ge1bTags[iHisto]->SetDirectory(f_output);

	// MET, ge1bTags, ge50ttbarSysPt
	hName = "h_met__ge1bTags_ge50ttbarSysPt";
	hName += flav_gen_sys_name;
	h_met_ge1bTags_ge50ttbarSysPt[iHisto] = new TH1D( hName, "MET, >=1 bTags, ttbar system pT>50;pT [GeV]", 24, 0.0, 600.0);
	h_met_ge1bTags_ge50ttbarSysPt[iHisto]->SetDirectory(f_output);

	// MET, ge1bTags, ge100ttbarSysPt
	hName = "h_met__ge1bTags_ge100ttbarSysPt";
	hName += flav_gen_sys_name;
	h_met_ge1bTags_ge100ttbarSysPt[iHisto] = new TH1D( hName, "MET, >=1 bTags, ttbar system pT>100;pT [GeV]", 24, 0.0, 600.0);
	h_met_ge1bTags_ge100ttbarSysPt[iHisto]->SetDirectory(f_output);

	// MET, ge1bTags, ge150ttbarSysPt
	hName = "h_met__ge1bTags_ge150ttbarSysPt";
	hName += flav_gen_sys_name;
	h_met_ge1bTags_ge150ttbarSysPt[iHisto] = new TH1D( hName, "MET, >=1 bTags, ttbar system pT>150;pT [GeV]", 24, 0.0, 600.0);
	h_met_ge1bTags_ge150ttbarSysPt[iHisto]->SetDirectory(f_output);

	

	// diLep pT, ge1bTags
	hName = "h_diLepPt__ge1bTags";
	hName += flav_gen_sys_name;
	h_diLepPt_ge1bTags[iHisto] = new TH1D( hName, "diLepton System pT, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
	h_diLepPt_ge1bTags[iHisto]->SetDirectory(f_output);
	
	// diLep pT, ge1bTags, ge100met
	hName = "h_diLepPt__ge1bTags_ge100met";
	hName += flav_gen_sys_name;
	h_diLepPt_ge1bTags_ge100met[iHisto] = new TH1D( hName, "diLepton System pT, >=1 bTags, MET>100;pT [GeV]", 24, 0.0, 600.0);
	h_diLepPt_ge1bTags_ge100met[iHisto]->SetDirectory(f_output);
	
	// diLep pT, ge1bTags, ge150met
	hName = "h_diLepPt__ge1bTags_ge150met";
	hName += flav_gen_sys_name;
	h_diLepPt_ge1bTags_ge150met[iHisto] = new TH1D( hName, "diLepton System pT, >=1 bTags, MET>150;pT [GeV]", 24, 0.0, 600.0);
	h_diLepPt_ge1bTags_ge150met[iHisto]->SetDirectory(f_output);
	
	

	// lep1lep2bbMet pT, ge1bTags
	hName = "h_lep1lep2bbMetPt__ge1bTags";
	hName += flav_gen_sys_name;
	h_lep1lep2bbMetPt_ge1bTags[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
	h_lep1lep2bbMetPt_ge1bTags[iHisto]->SetDirectory(f_output);

	// lep1lep2bbMet pT, ge1bTags, ge100met
	hName = "h_lep1lep2bbMetPt__ge1bTags_ge100met";
	hName += flav_gen_sys_name;
	h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags, MET>100;p_{T} [GeV]", 24, 0.0, 600.0 );
	h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto]->SetDirectory(f_output);

	// lep1lep2bbMet pT, ge1bTags, ge150met
	hName = "h_lep1lep2bbMetPt__ge1bTags_ge150met";
	hName += flav_gen_sys_name;
	h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags, MET>150;p_{T} [GeV]", 24, 0.0, 600.0 );
	h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto]->SetDirectory(f_output);

      

       
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
  
  // nISRJets
  TH1D *h_nISRJets_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_nISRJets_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_nISRJets_ge2bTags[nLepFlav][nGenClassy];
  
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
  //TH1D *h_diLepPt_ge1bTags[nLepFlav][nGenClassy]; // moved to section with all systematics
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
  //TH1D *h_met_ge1bTags[nLepFlav][nGenClassy]; // moved to section for all systematics
  TH1D *h_met_ge2bTags[nLepFlav][nGenClassy];

  // lep1lep2bbMet, ttbar visible system pT
  TH1D *h_lep1lep2bbPt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1lep2bbPt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_lep1lep2bbPt_ge2bTags[nLepFlav][nGenClassy];
 
  // lep1lep2bbMet, ttbar system pT
  TH1D *h_lep1lep2bbMetPt_ge0bTags[nLepFlav][nGenClassy];
  //TH1D *h_lep1lep2bbMetPt_ge1bTags[nLepFlav][nGenClassy]; moved to section for all systematics
  TH1D *h_lep1lep2bbMetPt_ge2bTags[nLepFlav][nGenClassy];
  
  // mt
  TH1D *h_mt_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_mt_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_mt_ge2bTags[nLepFlav][nGenClassy];

  // modifiedTopness
  TH1D *h_modTopness_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_modTopness_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_modTopness_ge2bTags[nLepFlav][nGenClassy];

  // mt2w
  TH1D *h_mt2w_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_mt2w_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_mt2w_ge2bTags[nLepFlav][nGenClassy];

  // Mlb
  TH1D *h_mlb_ge0bTags[nLepFlav][nGenClassy];
  TH1D *h_mlb_ge1bTags[nLepFlav][nGenClassy];
  TH1D *h_mlb_ge2bTags[nLepFlav][nGenClassy];

  for(int iFlav=0; iFlav<nLepFlav; iFlav++){
    for(int iGen=0; iGen<nGenClassy; iGen++){
      
      TString hName = "";
      
      TString flav_gen_name = "__lepFlav_";
      flav_gen_name += v_lepFlav[iFlav].first; 
      flav_gen_name += "__genClassy_";
      flav_gen_name += genClassyList[iGen].label;

      TString flav_gen_sys_name = flav_gen_name;
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

      // Njets, g0bTags
      hName = "h_nISRJets__ge0bTags";
      hName += flav_gen_sys_name;
      h_nISRJets_ge0bTags[iFlav][iGen] = new TH1D( hName, "Number of Selected Jets, >=0 bTags;nISRJets", 11, -0.5, 10.5);
      h_nISRJets_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // Njets, g1bTags
      hName = "h_nISRJets__ge1bTags";
      hName += flav_gen_sys_name;
      h_nISRJets_ge1bTags[iFlav][iGen] = new TH1D( hName, "Number of Selected Jets, >=1 bTags;nISRJets", 11, -0.5, 10.5);
      h_nISRJets_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // Njets, g2bTags
      hName = "h_nISRJets__ge2bTags";
      hName += flav_gen_sys_name;
      h_nISRJets_ge2bTags[iFlav][iGen] = new TH1D( hName, "Number of Selected Jets, >=2 bTags;nISRJets", 11, -0.5, 10.5);
      h_nISRJets_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


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
      h_diLepPt_ge0bTags[iFlav][iGen] = new TH1D( hName, "diLepton System pT, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_diLepPt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // diLep pT, ge1bTags
      //hName = "h_diLepPt__ge1bTags";
      //hName += flav_gen_sys_name;
      //h_diLepPt_ge1bTags[iFlav][iGen] = new TH1D( hName, "diLepton System pT, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      //h_diLepPt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // diLep pT, ge2bTags
      hName = "h_diLepPt__ge2bTags";
      hName += flav_gen_sys_name;
      h_diLepPt_ge2bTags[iFlav][iGen] = new TH1D( hName, "diLepton System pT, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_diLepPt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // jet pT, ge0bTags
      hName = "h_jetPt__ge0bTags";
      hName += flav_gen_sys_name;
      h_jetPt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Selected Jet pT, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jetPt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet pT, ge1bTags
      hName = "h_jetPt__ge1bTags";
      hName += flav_gen_sys_name;
      h_jetPt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Selected Jet pT, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jetPt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet pT, ge2bTags
      hName = "h_jetPt__ge2bTags";
      hName += flav_gen_sys_name;
      h_jetPt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Selected Jet pT, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jetPt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // jet1 pT, ge0bTags
      hName = "h_jet1Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_jet1Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Leading Jet pT, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jet1Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet1 pT, ge1bTags
      hName = "h_jet1Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_jet1Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Leading Jet pT, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jet1Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet1 pT, ge2bTags
      hName = "h_jet1Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_jet1Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Leading Jet pT, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jet1Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // jet2 pT, ge0bTags
      hName = "h_jet2Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_jet2Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Trailing Jet pT, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jet2Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet2 pT, ge1bTags
      hName = "h_jet2Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_jet2Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Trailing Jet pT, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jet2Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // jet2 pT, ge2bTags
      hName = "h_jet2Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_jet2Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Trailing Jet pT, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_jet2Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // csvJet1 pT, ge0bTags
      hName = "h_csvJet1Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_csvJet1Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_csvJet1Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet1 pT, ge1bTags
      hName = "h_csvJet1Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_csvJet1Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_csvJet1Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet1 pT, ge2bTags
      hName = "h_csvJet1Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_csvJet1Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_csvJet1Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // csvJet2 pT, ge0bTags
      hName = "h_csvJet2Pt__ge0bTags";
      hName += flav_gen_sys_name;
      h_csvJet2Pt_ge0bTags[iFlav][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_csvJet2Pt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet2 pT, ge1bTags
      hName = "h_csvJet2Pt__ge1bTags";
      hName += flav_gen_sys_name;
      h_csvJet2Pt_ge1bTags[iFlav][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_csvJet2Pt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // csvJet2 pT, ge2bTags
      hName = "h_csvJet2Pt__ge2bTags";
      hName += flav_gen_sys_name;
      h_csvJet2Pt_ge2bTags[iFlav][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_csvJet2Pt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // MET, ge0bTags
      hName = "h_met__ge0bTags";
      hName += flav_gen_sys_name;
      h_met_ge0bTags[iFlav][iGen] = new TH1D( hName, "MET, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_met_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // MET, ge1bTags
      //hName = "h_met__ge1bTags";
      //hName += flav_gen_sys_name;
      //h_met_ge1bTags[iFlav][iGen] = new TH1D( hName, "MET, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      //h_met_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // MET, ge2bTags
      hName = "h_met__ge2bTags";
      hName += flav_gen_sys_name;
      h_met_ge2bTags[iFlav][iGen] = new TH1D( hName, "MET, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
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
      //hName = "h_lep1lep2bbMetPt__ge1bTags";
      //hName += flav_gen_sys_name;
      //h_lep1lep2bbMetPt_ge1bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      //h_lep1lep2bbMetPt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // lep1lep2bbMet pT, ge2bTags
      hName = "h_lep1lep2bbMetPt__ge2bTags";
      hName += flav_gen_sys_name;
      h_lep1lep2bbMetPt_ge2bTags[iFlav][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=2 bTags;p_{T} [GeV]", 24, 0.0, 600.0 );
      h_lep1lep2bbMetPt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);

      
      // MT, ge0bTags
      hName = "h_mt__ge0bTags";
      hName += flav_gen_sys_name;
      h_mt_ge0bTags[iFlav][iGen] = new TH1D( hName, "MT, >=0 bTags;M_{T} [GeV]", 24, 0.0, 600.0);
      h_mt_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // MT, ge1bTags
      hName = "h_mt__ge1bTags";
      hName += flav_gen_sys_name;
      h_mt_ge1bTags[iFlav][iGen] = new TH1D( hName, "MT, >=1 bTags;M_{T} [GeV]", 24, 0.0, 600.0);
      h_mt_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // MT, ge2bTags
      hName = "h_mt__ge2bTags";
      hName += flav_gen_sys_name;
      h_mt_ge2bTags[iFlav][iGen] = new TH1D( hName, "MT, >=2 bTags;M_{T} [GeV]", 24, 0.0, 600.0);
      h_mt_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // modified topness, ge0bTags
      hName = "h_modTopness__ge0bTags";
      hName += flav_gen_sys_name;
      h_modTopness_ge0bTags[iFlav][iGen] = new TH1D( hName, "modified topness, >=0 bTags;pT [GeV]", 20, -20.0, 20.0);
      h_modTopness_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // modified topness, ge1bTags
      hName = "h_modTopness__ge1bTags";
      hName += flav_gen_sys_name;
      h_modTopness_ge1bTags[iFlav][iGen] = new TH1D( hName, "modified topness, >=1 bTags;pT [GeV]", 20, -20.0, 20.0);
      h_modTopness_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // modified topness, ge2bTags
      hName = "h_modTopness__ge2bTags";
      hName += flav_gen_sys_name;
      h_modTopness_ge2bTags[iFlav][iGen] = new TH1D( hName, "modified topness, >=2 bTags;pT [GeV]", 20, -20.0, 20.0);
      h_modTopness_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // MT2W, ge0bTags
      hName = "h_mt2w__ge0bTags";
      hName += flav_gen_sys_name;
      h_mt2w_ge0bTags[iFlav][iGen] = new TH1D( hName, "MT2W, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_mt2w_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // MT2W, ge1bTags
      hName = "h_mt2w__ge1bTags";
      hName += flav_gen_sys_name;
      h_mt2w_ge1bTags[iFlav][iGen] = new TH1D( hName, "MT2W, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_mt2w_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // MT2W, ge2bTags
      hName = "h_mt2w__ge2bTags";
      hName += flav_gen_sys_name;
      h_mt2w_ge2bTags[iFlav][iGen] = new TH1D( hName, "MT2W, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_mt2w_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


      // Mlb, ge0bTags
      hName = "h_mlb__ge0bTags";
      hName += flav_gen_sys_name;
      h_mlb_ge0bTags[iFlav][iGen] = new TH1D( hName, "Mlb, >=0 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_mlb_ge0bTags[iFlav][iGen]->SetDirectory(f_output);

      // Mlb, ge1bTags
      hName = "h_mlb__ge1bTags";
      hName += flav_gen_sys_name;
      h_mlb_ge1bTags[iFlav][iGen] = new TH1D( hName, "Mlb, >=1 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_mlb_ge1bTags[iFlav][iGen]->SetDirectory(f_output);

      // Mlb, ge2bTags
      hName = "h_mlb__ge2bTags";
      hName += flav_gen_sys_name;
      h_mlb_ge2bTags[iFlav][iGen] = new TH1D( hName, "Mlb, >=2 bTags;pT [GeV]", 24, 0.0, 600.0);
      h_mlb_ge2bTags[iFlav][iGen]->SetDirectory(f_output);


    } // end loop over genClassifications for histogram arrays
  } // end loop over leptonFlavs for histogram arrays

        

  ////////////////////////////////
  //                            //
  // Trigger Efficiency Studies //
  //                            //
  ////////////////////////////////

  // OR of all diLepton triggers
  int nEvents_pass_diLepSel_and_metTrig = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_diLepTrig = 0;
  
  TH1D *h1_diLep_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_diLep_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_diLep_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_diLep_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_diLep_trigger_eff_num = NULL;
  TH2D *h2_diLep_trigger_eff_den = NULL;

  // MuE Triggers
  int nEvents_pass_diLepSel_and_singleElTrig = 0;
  int nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig = 0;
  int nEvents_pass_diLepSel_and_singleMuTrig = 0;
  int nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig = 0;
  int nEvents_pass_diLepSel_and_metTrig_emuEvents = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_emuTrig = 0;
  
  TH1D *h1_emu_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_emu_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_emu_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_emu_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_emu_trigger_eff_num = NULL;
  TH2D *h2_emu_trigger_eff_den = NULL;

  // DiEl Trigger
  int nEvents_pass_diLepSel_and_metTrig_diElEvents = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_diElTrig = 0;

  TH1D *h1_diEl_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_diEl_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_diEl_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_diEl_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_diEl_trigger_eff_num = NULL;
  TH2D *h2_diEl_trigger_eff_den = NULL;

  // DiMu Triggers
  int nEvents_pass_diLepSel_and_metTrig_diMuEvents = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_diMuTrig = 0;
  
  TH1D *h1_diMu_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_diMu_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_diMu_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_diMu_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_diMu_trigger_eff_num = NULL;
  TH2D *h2_diMu_trigger_eff_den = NULL;

  if( sample.isData && sample.id==sampleInfo::k_met ){

    h1_diLep_trigger_eff_vs_lep1Pt_num = new TH1D( "h_diLep_trigger_eff_vs_lep1Pt_num", "ee/emu/mumu trigger efficiency vs leading lepton pT, numerator;diLep trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diLep_trigger_eff_vs_lep1Pt_den = new TH1D( "h_diLep_trigger_eff_vs_lep1Pt_den", "ee/emu/mumu trigger efficiency vs leading lepton pT, denominator;diLep trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    
    h1_diLep_trigger_eff_vs_lep2Pt_num = new TH1D( "h_diLep_trigger_eff_vs_lep2Pt_num", "ee/emu/mumu trigger efficiency vs trailing lepton pT, numerator;diLep trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_diLep_trigger_eff_vs_lep2Pt_den = new TH1D( "h_diLep_trigger_eff_vs_lep2Pt_den", "ee/emu/mumu trigger efficiency vs trailing lepton pT, denominator;diLep trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    
    h2_diLep_trigger_eff_num = new TH2D( "h_diLep_trigger_eff_num", "ee/emu/mumu trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_diLep_trigger_eff_den = new TH2D( "h_diLep_trigger_eff_den", "ee/emu/mumu trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );

    
    h1_emu_trigger_eff_vs_lep1Pt_num = new TH1D( "h_emu_trigger_eff_vs_lep1Pt_num", "emu trigger efficiency vs leading lepton pT, numerator;emu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_emu_trigger_eff_vs_lep1Pt_den = new TH1D( "h_emu_trigger_eff_vs_lep1Pt_den", "emu trigger efficiency vs leading lepton pT, denominator;emu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_emu_trigger_eff_vs_lep2Pt_num = new TH1D( "h_emu_trigger_eff_vs_lep2Pt_num", "emu trigger efficiency vs trailing lepton pT, numerator;emu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_emu_trigger_eff_vs_lep2Pt_den = new TH1D( "h_emu_trigger_eff_vs_lep2Pt_den", "emu trigger efficiency vs trailing lepton pT, denominator;emu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    h2_emu_trigger_eff_num = new TH2D( "h_emu_trigger_eff_num", "e/mu trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_emu_trigger_eff_den = new TH2D( "h_emu_trigger_eff_den", "e/mu trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
  
        
    h1_diEl_trigger_eff_vs_lep1Pt_num = new TH1D( "h_diEl_trigger_eff_vs_lep1Pt_num", "ee trigger efficiency vs leading lepton pT, numerator;diEl trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diEl_trigger_eff_vs_lep1Pt_den = new TH1D( "h_diEl_trigger_eff_vs_lep1Pt_den", "ee trigger efficiency vs leading lepton pT, denominator;diEl trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
  
    h1_diEl_trigger_eff_vs_lep2Pt_num = new TH1D( "h_diEl_trigger_eff_vs_lep2Pt_num", "ee trigger efficiency vs trailing lepton pT, numerator;diEl trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_diEl_trigger_eff_vs_lep2Pt_den = new TH1D( "h_diEl_trigger_eff_vs_lep2Pt_den", "ee trigger efficiency vs trailing lepton pT, denominator;diEl trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    h2_diEl_trigger_eff_num = new TH2D( "h_diEl_trigger_eff_num", "ee trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_diEl_trigger_eff_den = new TH2D( "h_diEl_trigger_eff_den", "ee trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
  
    
    h1_diMu_trigger_eff_vs_lep1Pt_num = new TH1D( "h_diMu_trigger_eff_vs_lep1Pt_num", "mumu trigger efficiency vs leading lepton pT, numerator;diMu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diMu_trigger_eff_vs_lep1Pt_den = new TH1D( "h_diMu_trigger_eff_vs_lep1Pt_den", "mumu trigger efficiency vs leading lepton pT, denominator;diMu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diMu_trigger_eff_vs_lep2Pt_num = new TH1D( "h_diMu_trigger_eff_vs_lep2Pt_num", "mumu trigger efficiency vs trailing lepton pT, numerator;diMu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_diMu_trigger_eff_vs_lep2Pt_den = new TH1D( "h_diMu_trigger_eff_vs_lep2Pt_den", "mumu trigger efficiency vs trailing lepton pT, denominator;diMu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    h2_diMu_trigger_eff_num = new TH2D( "h_diMu_trigger_eff_num", "mumu trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_diMu_trigger_eff_den = new TH2D( "h_diMu_trigger_eff_den", "mumu trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );

  } // end if data for trigger efficiency histogram declarations
  
  


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

      

      /////////////////////////////
      //                         //
      // Calculate Event Weights //
      //                         //
      /////////////////////////////
   
      wgtInfo->getEventWeights( analyzeFast_ );

      double wgt_nominal = wgtInfo->sys_wgts[sysInfo::k_nominal];

      
      
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
	if( nupt()>200.0 ) continue;
      }

      // Evt Selection
      pass_evtSel = selectionInfo::pass_CR2l_bulkTTbar(0, -1, add2ndLepToMet_);

      if( !sample.isData && !analyzeFast_ ) pass_evtSel_jup   = selectionInfo::pass_CR2l_bulkTTbar(1,  -1, add2ndLepToMet_);
      if( !sample.isData && !analyzeFast_ ) pass_evtSel_jdown = selectionInfo::pass_CR2l_bulkTTbar(-1, -1, add2ndLepToMet_);

      bool passAnyRegion = false;
      if( pass_evtSel || pass_evtSel_jup || pass_evtSel_jdown ) passAnyRegion=true;

      // Cutflow
      vector<bool> cutflow = selectionInfo::get_selectionResults_CR2l_bulkTTbar(0, -1);
      for(int i=0; i<(int)cutflow.size(); i++){
	if(!cutflow[i]) break;
	h_cutflow_evtSel->Fill( i, cutflow[i] );
      }


      //
      // If Data, before selection continue, look at trigger efficiency
      //
      if( sample.isData && sample.id==sampleInfo::k_met ){

	// Check if event passes cutlist for "diLepton selection"
	bool pass_selection_noTrigger = true;
	for(int iCut=0; iCut<(int)cutflow.size(); iCut++){
	  if( iCut==1 ) continue; // ignore diLepton trigger cut
	  if( !cutflow[iCut] ){
	    pass_selection_noTrigger = false;
	    break;
	  }
	}
	
	// Check if event passes triggers
	bool pass_trigger_singleEl = HLT_SingleEl();
	bool pass_trigger_singleMu = HLT_SingleMu(); 
	bool pass_trigger_met      = HLT_MET() || HLT_MET100_MHT100();
	bool pass_trigger_emu      = HLT_MuE();
	bool pass_trigger_diEl     = HLT_DiEl();
	bool pass_trigger_diMu     = HLT_DiMu();
	bool pass_trigger_diLep    = HLT_DiEl() || HLT_MuE() || HLT_DiMu();
	
	// DiLep Triggers (OR'd of all 3), MET trigger method
	if( pass_selection_noTrigger && pass_trigger_met ){
	  h1_diLep_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
	  h1_diLep_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
	  h2_diLep_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	  nEvents_pass_diLepSel_and_metTrig++;
	  if( pass_trigger_diLep ){
	    nEvents_pass_diLepSel_and_metTrig_and_diLepTrig++;
	    h1_diLep_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
	    h1_diLep_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
	    h2_diLep_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	    
	  }
	}

	// E/Mu Triggers
	if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==24 ){

	  // E/mu Trigger, SingleLep factorized method, Test trailing electron leg
	  if( pass_selection_noTrigger && pass_trigger_singleEl && abs(lep1_pdgid())==11 ){
	    nEvents_pass_diLepSel_and_singleElTrig++;
	    if( pass_trigger_emu ){
	      nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig++;
	    }
	  }

	  // E/mu Trigger, SingleLep factorized method, Test trailing muon leg
	  if( pass_selection_noTrigger && pass_trigger_singleMu && abs(lep1_pdgid())==13 ){
	    nEvents_pass_diLepSel_and_singleMuTrig++;
	    if( pass_trigger_diLep ){
	      nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig++;
	    }
	  }

	  // E/mu Trigger, MET Trigger method
	  if( pass_selection_noTrigger && pass_trigger_met ){
	    nEvents_pass_diLepSel_and_metTrig_emuEvents++;
	    h1_emu_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
	    h1_emu_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
	    h2_emu_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	    if( pass_trigger_emu ){
	      nEvents_pass_diLepSel_and_metTrig_and_emuTrig++;
	      h1_emu_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
	      h1_emu_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
	      h2_emu_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	    }
	  }

	} // end if e/mu

	
	// DiEl Triggers, MET Trigger method
	if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==22 ){
	  if( pass_selection_noTrigger && pass_trigger_met ){
	    nEvents_pass_diLepSel_and_metTrig_diElEvents++;
	    h1_diEl_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
	    h1_diEl_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
	    h2_diEl_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	    if( pass_trigger_diEl ){
	      nEvents_pass_diLepSel_and_metTrig_and_diElTrig++;
	      h1_diEl_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
	      h1_diEl_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
	      h2_diEl_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	    }
	  }
	} // end if elel


	// DiMu Triggers, MET Trigger method
	if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==26 ){
	  if( pass_selection_noTrigger && pass_trigger_met ){
	    nEvents_pass_diLepSel_and_metTrig_diMuEvents++;
	    h1_diMu_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
	    h1_diMu_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
	    h2_diMu_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	    if( pass_trigger_diMu ){
	      nEvents_pass_diLepSel_and_metTrig_and_diMuTrig++;
	      h1_diMu_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
	      h1_diMu_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
	      h2_diMu_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
	    }
	  }
	} // end if mumu


      } // end if sample is data


      
      //
      // Continue if Event Passes No Region of Interest
      //
      if( !passAnyRegion ) continue;


      // Intialize lepFlav vector
      for(int iFlav=0; iFlav<nLepFlav; iFlav++){ v_lepFlav[iFlav].second=false; }

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
	
      
      
      
      ///////////////////////////////
      //                           //
      // Check Gen Classifications //
      //                           //
      ///////////////////////////////
   
      for(int i=0; i<nGenClassy; i++){
	passGenClassy[i] = genClassyList[i].eval_GenClassy();
      }

      // Fix ZZ->2l2Nu, in baby is Z->NuNu, should be lostLep
      if( sample.id==sampleInfo::k_ZZTo2L2Nu_powheg_pythia8 ){
        for(int i=0; i<nGenClassy; i++){
          passGenClassy[i] = false;
          if( i==genClassyInfo::k_ge2lep ||
	      i==genClassyInfo::k_incl      ) passGenClassy[i] = true;
	}
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

    
      double met = pfmet();
      if(add2ndLepToMet_) met = pfmet_rl();
      
      double mt = mt_met_lep();
      if(add2ndLepToMet_) mt = mt_met_lep_rl();

      double tMod = topnessMod();
      if(add2ndLepToMet_) tMod = topnessMod_rl();

      double mt2w = MT2W();
      if(add2ndLepToMet_) mt2w = MT2W_rl();
      
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
	  
	      if(systematicList[iSys].id==sysInfo::k_JESUp){ if(!pass_evtSel_jup) continue; }
	      else if(systematicList[iSys].id==sysInfo::k_JESDown){ if(!pass_evtSel_jdown) continue; }
	      else{ if(!pass_evtSel) continue; }

	      // Histo Index
	      int iHisto = iFlav*nGenClassy*nSystematics + iGen*nSystematics + iSys;
	      //int iHisto = iGen*nSystematics + iSys;
	
	      // Event Weight for this Systematic
	      double wgt = wgtInfo->sys_wgts[systematicList[iSys].id];


	      // CR2l Bulk TTbar Regions
	    
	      // JES Up
	      if( systematicList[iSys].id==sysInfo::k_JESUp ){
		for(int iCat=0; iCat<(int)passCats_CR2l_bulkTTbar_jup.size(); iCat++){
		  h_yields_CR2l_bulkTTbar[iHisto]->Fill( passCats_CR2l_bulkTTbar_jup[iCat], wgt );
		}
	      }
	      // JES Dn
	      else if( systematicList[iSys].id==sysInfo::k_JESDown ){
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
	      

	      // Systematic variations for variables
	      if(systematicList[iSys].id==sysInfo::k_JESUp){
		if(add2ndLepToMet_) met = pfmet_rl_jup();
		else                met = pfmet_jup();
	      }
	      else if(systematicList[iSys].id==sysInfo::k_JESDown){
		if(add2ndLepToMet_) met = pfmet_rl_jdown();
		else                met = pfmet_jdown();
	      }
	      
	      
	      // met
	      if(systematicList[iSys].id==sysInfo::k_JESUp){
		if( jup_ngoodbtags()>=1 ){
		  h_met_ge1bTags[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>50)  h_met_ge1bTags_ge50ttbarSysPt[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>100) h_met_ge1bTags_ge100ttbarSysPt[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>150) h_met_ge1bTags_ge150ttbarSysPt[iHisto]->Fill( met, wgt );
		}
	      }
	      if(systematicList[iSys].id==sysInfo::k_JESDown){
		if( jdown_ngoodbtags()>=1 ){
		  h_met_ge1bTags[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>50)  h_met_ge1bTags_ge50ttbarSysPt[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>100) h_met_ge1bTags_ge100ttbarSysPt[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>150) h_met_ge1bTags_ge150ttbarSysPt[iHisto]->Fill( met, wgt );
		}
	      }
	      else{
		if( ngoodbtags()>=1 ){
		  h_met_ge1bTags[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>50)  h_met_ge1bTags_ge50ttbarSysPt[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>100) h_met_ge1bTags_ge100ttbarSysPt[iHisto]->Fill( met, wgt );
		  if(lep1lep2bbMet_pt>150) h_met_ge1bTags_ge150ttbarSysPt[iHisto]->Fill( met, wgt );
		}
	      }

	      
	      // diLepPt
	      if(systematicList[iSys].id==sysInfo::k_JESUp){
		if( jup_ngoodbtags()>=1 ){
		  h_diLepPt_ge1bTags[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		  if(met>100) h_diLepPt_ge1bTags_ge100met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		  if(met>150) h_diLepPt_ge1bTags_ge150met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		}
	      }
	      if(systematicList[iSys].id==sysInfo::k_JESDown){
		if( jdown_ngoodbtags()>=1 ){
		  h_diLepPt_ge1bTags[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		  if(met>100) h_diLepPt_ge1bTags_ge100met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		  if(met>150) h_diLepPt_ge1bTags_ge150met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		}
	      }
	      else{
		if( ngoodbtags()>=1 ){
		  h_diLepPt_ge1bTags[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		  if(met>100) h_diLepPt_ge1bTags_ge100met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		  if(met>150) h_diLepPt_ge1bTags_ge150met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt );
		}
	      }


	      // lep1lep2bbMet
	      if(systematicList[iSys].id==sysInfo::k_JESUp){
		if( jup_ngoodbtags()>=1 ){
		  h_lep1lep2bbMetPt_ge1bTags[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		  if(met>100) h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		  if(met>150) h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		}
	      }
	      if(systematicList[iSys].id==sysInfo::k_JESDown){
		if( jdown_ngoodbtags()>=1 ){
		  h_lep1lep2bbMetPt_ge1bTags[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		  if(met>100) h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		  if(met>150) h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		}
	      }
	      else{
		if( ngoodbtags()>=1 ){
		  h_lep1lep2bbMetPt_ge1bTags[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		  if(met>100) h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		  if(met>150) h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto]->Fill( lep1lep2bbMet_pt, wgt );
		}
	      }



	    } // end loop over systematics
	  

	    //
	    // Non-yield Histograms
	    //
	    if( pass_evtSel ){
	    
	      // nBTags
	      h_nBTags[iFlav][iGen]->Fill( ngoodbtags(), wgt_nominal );

	      // nJets
	      if( ngoodbtags()>=0 ) h_nJets_ge0bTags[iFlav][iGen]->Fill( ngoodjets(), wgt_nominal );
	      if( ngoodbtags()>=1 ) h_nJets_ge1bTags[iFlav][iGen]->Fill( ngoodjets(), wgt_nominal );
	      if( ngoodbtags()>=2 ) h_nJets_ge2bTags[iFlav][iGen]->Fill( ngoodjets(), wgt_nominal );
	    
	      // nISRJets
	      if(!sample.isData){
		if( ngoodbtags()>=0 ) h_nISRJets_ge0bTags[iFlav][iGen]->Fill( NISRjets(), wgt_nominal );
		if( ngoodbtags()>=1 ) h_nISRJets_ge1bTags[iFlav][iGen]->Fill( NISRjets(), wgt_nominal );
		if( ngoodbtags()>=2 ) h_nISRJets_ge2bTags[iFlav][iGen]->Fill( NISRjets(), wgt_nominal );
	      }

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
	      //if( ngoodbtags()>=1 ) h_diLepPt_ge1bTags[iFlav][iGen]->Fill( (lep1_p4()+lep2_p4()).Pt(), wgt_nominal );
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
	      if( ngoodbtags()>=0 ) h_met_ge0bTags[iFlav][iGen]->Fill( met, wgt_nominal );
	      //if( ngoodbtags()>=1 ) h_met_ge1bTags[iFlav][iGen]->Fill( met, wgt_nominal );
	      if( ngoodbtags()>=2 ) h_met_ge2bTags[iFlav][iGen]->Fill( met, wgt_nominal );
	      

	      // lep1lep2bb pT
	      if( ngoodbtags()>=0 ) h_lep1lep2bbPt_ge0bTags[iFlav][iGen]->Fill( lep1lep2bb_pt, wgt_nominal );
	      if( ngoodbtags()>=1 ) h_lep1lep2bbPt_ge1bTags[iFlav][iGen]->Fill( lep1lep2bb_pt, wgt_nominal );
	      if( ngoodbtags()>=2 ) h_lep1lep2bbPt_ge2bTags[iFlav][iGen]->Fill( lep1lep2bb_pt, wgt_nominal );


	      // lep1lep2bbMet pT
	      if( ngoodbtags()>=0 ) h_lep1lep2bbMetPt_ge0bTags[iFlav][iGen]->Fill( lep1lep2bbMet_pt, wgt_nominal );
	      //if( ngoodbtags()>=1 ) h_lep1lep2bbMetPt_ge1bTags[iFlav][iGen]->Fill( lep1lep2bbMet_pt, wgt_nominal );
	      if( ngoodbtags()>=2 ) h_lep1lep2bbMetPt_ge2bTags[iFlav][iGen]->Fill( lep1lep2bbMet_pt, wgt_nominal );

	    
	      // mt
	      if( ngoodbtags()>=0 ) h_mt_ge0bTags[iFlav][iGen]->Fill( mt, wgt_nominal );
	      if( ngoodbtags()>=1 ) h_mt_ge1bTags[iFlav][iGen]->Fill( mt, wgt_nominal );
	      if( ngoodbtags()>=2 ) h_mt_ge2bTags[iFlav][iGen]->Fill( mt, wgt_nominal );
	      

	      // modified topness
	      if( ngoodbtags()>=0 ) h_modTopness_ge0bTags[iFlav][iGen]->Fill( tMod, wgt_nominal );
	      if( ngoodbtags()>=1 ) h_modTopness_ge1bTags[iFlav][iGen]->Fill( tMod, wgt_nominal );
	      if( ngoodbtags()>=2 ) h_modTopness_ge2bTags[iFlav][iGen]->Fill( tMod, wgt_nominal );
	      

	      // mt2w
	      if( ngoodbtags()>=0 ) h_mt2w_ge0bTags[iFlav][iGen]->Fill( mt2w, wgt_nominal );
	      if( ngoodbtags()>=1 ) h_mt2w_ge1bTags[iFlav][iGen]->Fill( mt2w, wgt_nominal );
	      if( ngoodbtags()>=2 ) h_mt2w_ge2bTags[iFlav][iGen]->Fill( mt2w, wgt_nominal );
	    

	      // mlb
	      if( ngoodbtags()>=0 ) h_mlb_ge0bTags[iFlav][iGen]->Fill( Mlb_closestb(), wgt_nominal );
	      if( ngoodbtags()>=1 ) h_mlb_ge1bTags[iFlav][iGen]->Fill( Mlb_closestb(), wgt_nominal );
	      if( ngoodbtags()>=2 ) h_mlb_ge2bTags[iFlav][iGen]->Fill( Mlb_closestb(), wgt_nominal );
	    

	    } // end if pass evt selection
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
  // Trigger Efficiency Printouts
  //
  if( sample.isData && sample.id==sampleInfo::k_met ){
    
    cout << "  Trigger Efficiency Results: " << endl;

    double trigger_eff_diLep = (double)nEvents_pass_diLepSel_and_metTrig_and_diLepTrig/(double)nEvents_pass_diLepSel_and_metTrig;
    double trigger_eff_diLep_err = sqrt( (trigger_eff_diLep*(1-trigger_eff_diLep))/(double)nEvents_pass_diLepSel_and_metTrig );
    cout << "    OR of all diLep Triggers, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_diLepTrig << " / " << nEvents_pass_diLepSel_and_metTrig << " ) = " << trigger_eff_diLep << " +/- " << trigger_eff_diLep_err << endl;
    

    double trigger_eff_diEl = (double)nEvents_pass_diLepSel_and_metTrig_and_diElTrig/(double)nEvents_pass_diLepSel_and_metTrig_diElEvents;
    double trigger_eff_diEl_err = sqrt( (trigger_eff_diEl*(1-trigger_eff_diEl))/(double)nEvents_pass_diLepSel_and_metTrig_diElEvents );
    cout << "    diEl Trigger, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_diElTrig << " / " << nEvents_pass_diLepSel_and_metTrig_diElEvents << " ) = " << trigger_eff_diEl << " +/- " << trigger_eff_diEl_err << endl;
    

    double trigger_eff_diMu = (double)nEvents_pass_diLepSel_and_metTrig_and_diMuTrig/(double)nEvents_pass_diLepSel_and_metTrig_diMuEvents;
    double trigger_eff_diMu_err = sqrt( (trigger_eff_diMu*(1-trigger_eff_diMu))/(double)nEvents_pass_diLepSel_and_metTrig_diMuEvents );
    cout << "    diMu Trigger, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_diMuTrig << " / " << nEvents_pass_diLepSel_and_metTrig_diMuEvents << " ) = " << trigger_eff_diMu << " +/- " << trigger_eff_diMu_err << endl;
  

    double trigger_eff_emu = (double)nEvents_pass_diLepSel_and_metTrig_and_emuTrig/(double)nEvents_pass_diLepSel_and_metTrig_emuEvents;
    double trigger_eff_emu_err = sqrt( (trigger_eff_emu*(1-trigger_eff_emu))/(double)nEvents_pass_diLepSel_and_metTrig_emuEvents );
    cout << "    e/mu Trigger, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_emuTrig << " / " << nEvents_pass_diLepSel_and_metTrig_emuEvents << " ) = " << trigger_eff_emu << " +/- " << trigger_eff_emu_err << endl;
  

    double trigger_eff_emu_trailingLep_el = (double)nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig/(double)nEvents_pass_diLepSel_and_singleElTrig;
    double trigger_eff_emu_trailingLep_el_err = sqrt( (trigger_eff_emu_trailingLep_el*(1-trigger_eff_emu_trailingLep_el))/(double)nEvents_pass_diLepSel_and_singleElTrig );
    cout << "    e/mu Trigger, using SingleLep monitoring triggers " << endl;
    cout << "        Trailing Mu Leg Efficiency, using singleEl triggers = " << "( " << (double)nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig << " / " << (double)nEvents_pass_diLepSel_and_singleElTrig << " ) = " << trigger_eff_emu_trailingLep_el << " +/- " << trigger_eff_emu_trailingLep_el_err << endl;

    
    double trigger_eff_emu_trailingLep_mu = (double)nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig/(double)nEvents_pass_diLepSel_and_singleMuTrig;
    double trigger_eff_emu_trailingLep_mu_err = sqrt( (trigger_eff_emu_trailingLep_mu*(1-trigger_eff_emu_trailingLep_mu))/(double)nEvents_pass_diLepSel_and_singleMuTrig );
    cout << "        Trailing El Leg Efficiency, using singleMu triggers = " << "( " << (double)nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig << " / " << (double)nEvents_pass_diLepSel_and_singleMuTrig << " ) = " << trigger_eff_emu_trailingLep_mu << " +/- " << trigger_eff_emu_trailingLep_mu_err << endl;

    double trigger_eff_emu_singleLepMethod = trigger_eff_emu_trailingLep_mu*trigger_eff_emu_trailingLep_el;
    double trigger_eff_emu_singleLepMethod_err = trigger_eff_emu_singleLepMethod*sqrt( pow(trigger_eff_emu_trailingLep_mu_err/trigger_eff_emu_trailingLep_mu,2) + pow(trigger_eff_emu_trailingLep_el_err/trigger_eff_emu_trailingLep_el,2) );
    cout << "        Factorized Trigger Efficiency = (" << trigger_eff_emu_trailingLep_mu << " * " << trigger_eff_emu_trailingLep_el << " ) = " << trigger_eff_emu_singleLepMethod << " +/- " << trigger_eff_emu_singleLepMethod_err << endl;
 
    cout << "====================================================" << endl;
  }


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
  if( sample.isData ) duplicate_removal::clear_list();
  

       
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

