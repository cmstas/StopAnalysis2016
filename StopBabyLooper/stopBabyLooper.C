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

bool analyzeFast_ = false;

bool doSelection_SR_   = true;
bool doSelection_CR0b_ = true;
bool doSelection_CR2l_ = true;

bool applyjson = true;

bool add2ndLepToMet_ = true;
bool inclTaus_CR2l_  = false;

bool useBTagSFs_fromUtils_ = false;
bool useLepSFs_fromUtils_  = false;
        
bool apply_diLepTrigger_sf_ = false; // for ee/emu/mumu triggers only, left in here, just in case this macro is copied as a prototype
bool apply_cr2lTrigger_sf_  = true; // only !=1 if pfmet!=pfmet_rl ie no weight for ==1lepton events in SR and CR0b
bool apply_bTag_sf_         = true; // event weight, product of all jet wgts
bool apply_lep_sf_          = true; // both lep1 and lep2 (if available) are multiplied together
bool apply_vetoLep_sf_      = true; // this is actually the lost lepton sf, only !=1 if there is >=2 genLeptons and ==1 recoLeptons in the event
bool apply_lepFS_sf_        = false;
bool apply_topPt_sf_        = false; // true=sf, false=uncertainty
bool apply_metRes_sf_       = true;
bool apply_ttbarSysPt_sf_   = true;  // true=sf, false=uncertainty, only !=1.0 for madgraph tt2l, tW2l
bool apply_ISR_sf_          = false; // only !=1.0 for signal
bool apply_sample_sf_       = false; // only !=1.0 for some WJetsHT samps

  

//
// Function Declarations
//
int looper( sampleInfo::ID sample, int nEvents=-1, bool readFast=true );


//
// Main
//
int stopBabyLooper(){


  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList_SR(); 


  //
  // Examples for Quick Tests
  //
  //sampleList.clear();
  //sampleList.push_back( sampleInfo::k_single_lepton_met );
  //sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8 ); 
  //sampleList.push_back( sampleInfo::k_T2tt ); 
  

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
    string input = sample.baby_i_o.first;
      
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
  
  bool pass_SR         = false;
  bool pass_SR_jup     = false;
  bool pass_SR_jdown   = false;
  TH1D *h_cutflow_SR   = selectionInfo::get_cutflowHistoTemplate_SR();
  h_cutflow_SR->SetDirectory(f_output);

  bool pass_CR0b       = false;
  bool pass_CR0b_jup   = false;
  bool pass_CR0b_jdown = false;
  TH1D *h_cutflow_CR0b = selectionInfo::get_cutflowHistoTemplate_CR0b();
  h_cutflow_CR0b->SetDirectory(f_output);

  bool pass_CR2l       = false;
  bool pass_CR2l_jup   = false;
  bool pass_CR2l_jdown = false;
  TH1D *h_cutflow_CR2l = selectionInfo::get_cutflowHistoTemplate_CR2l();
  if( inclTaus_CR2l_ ){
    h_cutflow_CR2l->GetXaxis()->SetBinLabel(4, ">=2 leptons (incl tau)" );
  }
  else{
    h_cutflow_CR2l->GetXaxis()->SetBinLabel(4, ">=2 leptons (e/mu only)" );
  }
  

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
  wgtInfo->apply_cr2lTrigger_sf  = (apply_cr2lTrigger_sf_ && add2ndLepToMet_);
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
  vector<int> passCats_SR_ICHEP; 
  vector<int> passCats_SR_ICHEP_jup;
  vector<int> passCats_SR_ICHEP_jdown;
  
  vector<int> passCats_SR_ICHEP_ext30fb; 
  vector<int> passCats_SR_ICHEP_ext30fb_jup;
  vector<int> passCats_SR_ICHEP_ext30fb_jdown;

  vector<int> passCats_SR_dev_ext30fb_mlb_v1; 
  vector<int> passCats_SR_dev_ext30fb_mlb_v1_jup;
  vector<int> passCats_SR_dev_ext30fb_mlb_v1_jdown;

  vector<int> passCats_SR_dev_ext30fb_bJetPt_v1; 
  vector<int> passCats_SR_dev_ext30fb_bJetPt_v1_jup;
  vector<int> passCats_SR_dev_ext30fb_bJetPt_v1_jdown;

  vector<int> passCats_SR_corridor; 
  vector<int> passCats_SR_corridor_jup;
  vector<int> passCats_SR_corridor_jdown;

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
  //    histogram_name = "your_name_here"+"__SR"+"__genClassy_"+genClassyObject.label+"__systematic_"+sysInfoObject.label;
  //
  //
  //  Where "__SR" can be replaced by "__CR0b", or "__CR2l"
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
  const int nHistos = nGenClassy*nSystematics;
  
  // ICHEP SR bins, 12.9fb
  TH1D *h_yields_ICHEP_template = categoryInfo::getYieldHistoTemplate_SR_ICHEP();
  TH1D *h_yields_ICHEP_SR[nHistos];
  TH1D *h_yields_ICHEP_CR0b[nHistos];
  TH1D *h_yields_ICHEP_CR2l[nHistos];

  // ICHEP SR bins, extended to 30fb
  TH1D *h_yields_ICHEP_ext30fb_template = categoryInfo::getYieldHistoTemplate_SR_ICHEP_ext30fb();
  TH1D *h_yields_ICHEP_ext30fb_SR[nHistos];
  TH1D *h_yields_ICHEP_ext30fb_CR0b[nHistos];
  TH1D *h_yields_ICHEP_ext30fb_CR2l[nHistos];

  // ICHEP SR bins, extended to 30fb, mlb bins
  TH1D *h_yields_dev_ext30fb_mlb_v1_template = categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_mlb_v1();
  TH1D *h_yields_dev_ext30fb_mlb_v1_SR[nHistos];
  TH1D *h_yields_dev_ext30fb_mlb_v1_CR0b[nHistos];
  TH1D *h_yields_dev_ext30fb_mlb_v1_CR2l[nHistos];
  
  // ICHEP SR bins, extended to 30fb, bJetPt bins
  TH1D *h_yields_dev_ext30fb_bJetPt_v1_template = categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_bJetPt_v1();
  TH1D *h_yields_dev_ext30fb_bJetPt_v1_SR[nHistos];
  TH1D *h_yields_dev_ext30fb_bJetPt_v1_CR0b[nHistos];
  TH1D *h_yields_dev_ext30fb_bJetPt_v1_CR2l[nHistos];

  // Top Corridor SR bins, Dan
  TH1D *h_yields_corridor_template = categoryInfo::getYieldHistoTemplate_SR_corridor();
  TH1D *h_yields_corridor_SR[nHistos];
  TH1D *h_yields_corridor_CR0b[nHistos];
  TH1D *h_yields_corridor_CR2l[nHistos];


  // Loop over genClassifications and systematics
  for(int iGen=0; iGen<nGenClassy; iGen++){
    for(int iSys=0; iSys<nSystematics; iSys++){

      // Histo Index
      int iHisto = iGen*nSystematics + iSys;

      // Gen and Systematic String
      TString gen_sys_name = "__genClassy_";
      gen_sys_name += genClassyList[iGen].label;
      gen_sys_name += "__systematic_";
      gen_sys_name += systematicList[iSys].label;


      // ICHEP Signal Regions, 12.9fb

      // Baseline Name
      TString h_name_ICHEP_base = h_yields_ICHEP_template->GetName();
      
      // SR yields
      TString h_name_ICHEP_SR = h_name_ICHEP_base;
      h_name_ICHEP_SR += "__SR";
      h_name_ICHEP_SR += gen_sys_name;
      h_yields_ICHEP_SR[iHisto] = (TH1D*)h_yields_ICHEP_template->Clone(h_name_ICHEP_SR);
      h_yields_ICHEP_SR[iHisto]->SetDirectory(f_output);

      // CR0b yields
      TString h_name_ICHEP_CR0b = h_name_ICHEP_base;
      h_name_ICHEP_CR0b += "__CR0b";
      h_name_ICHEP_CR0b += gen_sys_name;
      h_yields_ICHEP_CR0b[iHisto] = (TH1D*)h_yields_ICHEP_template->Clone(h_name_ICHEP_CR0b);
      h_yields_ICHEP_CR0b[iHisto]->SetDirectory(f_output);

      // CR2l yields
      TString h_name_ICHEP_CR2l = h_name_ICHEP_base;
      h_name_ICHEP_CR2l += "__CR2l";
      h_name_ICHEP_CR2l += gen_sys_name;
      h_yields_ICHEP_CR2l[iHisto] = (TH1D*)h_yields_ICHEP_template->Clone(h_name_ICHEP_CR2l);
      h_yields_ICHEP_CR2l[iHisto]->SetDirectory(f_output);


      
      // ICHEP Signal Regions, extended to 30fb

      // Baseline Name
      TString h_name_ICHEP_ext30fb_base = h_yields_ICHEP_ext30fb_template->GetName();
      
      // SR yields
      TString h_name_ICHEP_ext30fb_SR = h_name_ICHEP_ext30fb_base;
      h_name_ICHEP_ext30fb_SR += "__SR";
      h_name_ICHEP_ext30fb_SR += gen_sys_name;
      h_yields_ICHEP_ext30fb_SR[iHisto] = (TH1D*)h_yields_ICHEP_ext30fb_template->Clone(h_name_ICHEP_ext30fb_SR);
      h_yields_ICHEP_ext30fb_SR[iHisto]->SetDirectory(f_output);

      // CR0b yields
      TString h_name_ICHEP_ext30fb_CR0b = h_name_ICHEP_ext30fb_base;
      h_name_ICHEP_ext30fb_CR0b += "__CR0b";
      h_name_ICHEP_ext30fb_CR0b += gen_sys_name;
      h_yields_ICHEP_ext30fb_CR0b[iHisto] = (TH1D*)h_yields_ICHEP_ext30fb_template->Clone(h_name_ICHEP_ext30fb_CR0b);
      h_yields_ICHEP_ext30fb_CR0b[iHisto]->SetDirectory(f_output);

      // CR2l yields
      TString h_name_ICHEP_ext30fb_CR2l = h_name_ICHEP_ext30fb_base;
      h_name_ICHEP_ext30fb_CR2l += "__CR2l";
      h_name_ICHEP_ext30fb_CR2l += gen_sys_name;
      h_yields_ICHEP_ext30fb_CR2l[iHisto] = (TH1D*)h_yields_ICHEP_ext30fb_template->Clone(h_name_ICHEP_ext30fb_CR2l);
      h_yields_ICHEP_ext30fb_CR2l[iHisto]->SetDirectory(f_output);


      // Dev Signal Regions, extended to 30fb, mlb bins

      // Baseline Name
      TString h_name_dev_ext30fb_mlb_v1_base = h_yields_dev_ext30fb_mlb_v1_template->GetName();
      
      // SR yields
      TString h_name_dev_ext30fb_mlb_v1_SR = h_name_dev_ext30fb_mlb_v1_base;
      h_name_dev_ext30fb_mlb_v1_SR += "__SR";
      h_name_dev_ext30fb_mlb_v1_SR += gen_sys_name;
      h_yields_dev_ext30fb_mlb_v1_SR[iHisto] = (TH1D*)h_yields_dev_ext30fb_mlb_v1_template->Clone(h_name_dev_ext30fb_mlb_v1_SR);
      h_yields_dev_ext30fb_mlb_v1_SR[iHisto]->SetDirectory(f_output);

      // CR0b yields
      TString h_name_dev_ext30fb_mlb_v1_CR0b = h_name_dev_ext30fb_mlb_v1_base;
      h_name_dev_ext30fb_mlb_v1_CR0b += "__CR0b";
      h_name_dev_ext30fb_mlb_v1_CR0b += gen_sys_name;
      h_yields_dev_ext30fb_mlb_v1_CR0b[iHisto] = (TH1D*)h_yields_dev_ext30fb_mlb_v1_template->Clone(h_name_dev_ext30fb_mlb_v1_CR0b);
      h_yields_dev_ext30fb_mlb_v1_CR0b[iHisto]->SetDirectory(f_output);

      // CR2l yields
      TString h_name_dev_ext30fb_mlb_v1_CR2l = h_name_dev_ext30fb_mlb_v1_base;
      h_name_dev_ext30fb_mlb_v1_CR2l += "__CR2l";
      h_name_dev_ext30fb_mlb_v1_CR2l += gen_sys_name;
      h_yields_dev_ext30fb_mlb_v1_CR2l[iHisto] = (TH1D*)h_yields_dev_ext30fb_mlb_v1_template->Clone(h_name_dev_ext30fb_mlb_v1_CR2l);
      h_yields_dev_ext30fb_mlb_v1_CR2l[iHisto]->SetDirectory(f_output);


      // Dev Signal Regions, extended to 30fb, bJetPt bins

      // Baseline Name
      TString h_name_dev_ext30fb_bJetPt_v1_base = h_yields_dev_ext30fb_bJetPt_v1_template->GetName();
      
      // SR yields
      TString h_name_dev_ext30fb_bJetPt_v1_SR = h_name_dev_ext30fb_bJetPt_v1_base;
      h_name_dev_ext30fb_bJetPt_v1_SR += "__SR";
      h_name_dev_ext30fb_bJetPt_v1_SR += gen_sys_name;
      h_yields_dev_ext30fb_bJetPt_v1_SR[iHisto] = (TH1D*)h_yields_dev_ext30fb_bJetPt_v1_template->Clone(h_name_dev_ext30fb_bJetPt_v1_SR);
      h_yields_dev_ext30fb_bJetPt_v1_SR[iHisto]->SetDirectory(f_output);

      // CR0b yields
      TString h_name_dev_ext30fb_bJetPt_v1_CR0b = h_name_dev_ext30fb_bJetPt_v1_base;
      h_name_dev_ext30fb_bJetPt_v1_CR0b += "__CR0b";
      h_name_dev_ext30fb_bJetPt_v1_CR0b += gen_sys_name;
      h_yields_dev_ext30fb_bJetPt_v1_CR0b[iHisto] = (TH1D*)h_yields_dev_ext30fb_bJetPt_v1_template->Clone(h_name_dev_ext30fb_bJetPt_v1_CR0b);
      h_yields_dev_ext30fb_bJetPt_v1_CR0b[iHisto]->SetDirectory(f_output);

      // CR2l yields
      TString h_name_dev_ext30fb_bJetPt_v1_CR2l = h_name_dev_ext30fb_bJetPt_v1_base;
      h_name_dev_ext30fb_bJetPt_v1_CR2l += "__CR2l";
      h_name_dev_ext30fb_bJetPt_v1_CR2l += gen_sys_name;
      h_yields_dev_ext30fb_bJetPt_v1_CR2l[iHisto] = (TH1D*)h_yields_dev_ext30fb_bJetPt_v1_template->Clone(h_name_dev_ext30fb_bJetPt_v1_CR2l);
      h_yields_dev_ext30fb_bJetPt_v1_CR2l[iHisto]->SetDirectory(f_output);


      // Top Corridor Region

      // Baseline Name
      TString h_name_corridor_base = h_yields_corridor_template->GetName();
      
      // SR yields
      TString h_name_corridor_SR = h_name_corridor_base;
      h_name_corridor_SR += "__SR";
      h_name_corridor_SR += gen_sys_name;
      h_yields_corridor_SR[iHisto] = (TH1D*)h_yields_corridor_template->Clone(h_name_corridor_SR);
      h_yields_corridor_SR[iHisto]->SetDirectory(f_output);

      // CR0b yields
      TString h_name_corridor_CR0b = h_name_corridor_base;
      h_name_corridor_CR0b += "__CR0b";
      h_name_corridor_CR0b += gen_sys_name;
      h_yields_corridor_CR0b[iHisto] = (TH1D*)h_yields_corridor_template->Clone(h_name_corridor_CR0b);
      h_yields_corridor_CR0b[iHisto]->SetDirectory(f_output);

      // CR2l yields
      TString h_name_corridor_CR2l = h_name_corridor_base;
      h_name_corridor_CR2l += "__CR2l";
      h_name_corridor_CR2l += gen_sys_name;
      h_yields_corridor_CR2l[iHisto] = (TH1D*)h_yields_corridor_template->Clone(h_name_corridor_CR2l);
      h_yields_corridor_CR2l[iHisto]->SetDirectory(f_output);
      

    } // end loop over systematics
  } // end loop over gen classifications


  
  //////////////////////////
  //                      //
  // Non-yield Histograms //
  //                      //
  //////////////////////////

  // nJets
  TH1D *h_nJets_SR[nGenClassy];
  TH1D *h_nJets_CR0b[nGenClassy];
  TH1D *h_nJets_CR2l[nGenClassy];
  
  // Gen ttbar system pT
  TH1D *h_genTTbarPt_SR_incl[nGenClassy];
  TH1D *h_genTTbarPt_SR_ee2j[nGenClassy];
  TH1D *h_genTTbarPt_SR_ee3j[nGenClassy];
  TH1D *h_genTTbarPt_SR_ge4j[nGenClassy];

  TH1D *h_genTTbarPt_CR2l_incl[nGenClassy];
  TH1D *h_genTTbarPt_CR2l_ee2j[nGenClassy];
  TH1D *h_genTTbarPt_CR2l_ee3j[nGenClassy];
  TH1D *h_genTTbarPt_CR2l_ge4j[nGenClassy];

  for(int iGen=0; iGen<nGenClassy; iGen++){
    
    TString hName = "";

    TString gen_sys_name = "__genClassy_";
    gen_sys_name += genClassyList[iGen].label;
    gen_sys_name += "__systematic_";
    gen_sys_name += systematicList[0].label;


    //
    // Njets
    //

    // SR
    hName = "h_nJets";
    hName += "__SR";
    hName += gen_sys_name;
    h_nJets_SR[iGen] = new TH1D( hName, "Number of Selected Jets;nJets", 11, -0.5, 10.5);
    h_nJets_SR[iGen]->SetDirectory(f_output);

    // CR0b
    hName = "h_nJets";
    hName += "__CR0b";
    hName += gen_sys_name;
    h_nJets_CR0b[iGen] = new TH1D( hName, "Number of Selected Jets;nJets", 11, -0.5, 10.5);
    h_nJets_CR0b[iGen]->SetDirectory(f_output);

    // CR2l
    hName = "h_nJets";
    hName += "__CR2l";
    hName += gen_sys_name;
    h_nJets_CR2l[iGen] = new TH1D( hName, "Number of Selected Jets;nJets", 11, -0.5, 10.5);
    h_nJets_CR2l[iGen]->SetDirectory(f_output);

        
    //
    // Gen ttbar pT
    //
    if( sampleIsTTbar ){
    
      // SR, Incl Selection
      hName = "h_gen_ttbar_pt__inclSelection";
      hName += "__SR";
      hName += gen_sys_name;
      h_genTTbarPt_SR_incl[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_SR_incl[iGen]->SetDirectory(f_output);

      // SR, ==2j Selection
      hName = "h_gen_ttbar_pt__ee2jSelection";
      hName += "__SR";
      hName += gen_sys_name;
      h_genTTbarPt_SR_ee2j[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_SR_ee2j[iGen]->SetDirectory(f_output);

      // SR, ==3j Selection
      hName = "h_gen_ttbar_pt__ee3jSelection";
      hName += "__SR";
      hName += gen_sys_name;
      h_genTTbarPt_SR_ee3j[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_SR_ee3j[iGen]->SetDirectory(f_output);

      // SR, >=4j Selection
      hName = "h_gen_ttbar_pt__ge4jSelection";
      hName += "__SR";
      hName += gen_sys_name;
      h_genTTbarPt_SR_ge4j[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_SR_ge4j[iGen]->SetDirectory(f_output);


      // CR2l, Incl Selection
      hName = "h_gen_ttbar_pt__inclSelection";
      hName += "__CR2l";
      hName += gen_sys_name;
      h_genTTbarPt_CR2l_incl[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_CR2l_incl[iGen]->SetDirectory(f_output);

      // CR2l, ==2j Selection
      hName = "h_gen_ttbar_pt__ee2jSelection";
      hName += "__CR2l";
      hName += gen_sys_name;
      h_genTTbarPt_CR2l_ee2j[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_CR2l_ee2j[iGen]->SetDirectory(f_output);

      // CR2l, ==3j Selection
      hName = "h_gen_ttbar_pt__ee3jSelection";
      hName += "__CR2l";
      hName += gen_sys_name;
      h_genTTbarPt_CR2l_ee3j[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_CR2l_ee3j[iGen]->SetDirectory(f_output);

      // CR2l, >=4j Selection
      hName = "h_gen_ttbar_pt__ge4jSelection";
      hName += "__CR2l";
      hName += gen_sys_name;
      h_genTTbarPt_CR2l_ge4j[iGen] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      h_genTTbarPt_CR2l_ge4j[iGen]->SetDirectory(f_output);

    } // end if sample is ttbar

  } // end loop over genClassifications for histogram arrays


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

      // Signal Region
      pass_SR        = false;
      pass_SR_jup    = false;
      pass_SR_jdown  = false;
      if( doSelection_SR_ ){
	pass_SR          = selectionInfo::pass_SR(0);
	if( !sample.isData && !analyzeFast_ ){
	  pass_SR_jup    = selectionInfo::pass_SR(1);
	  pass_SR_jdown  = selectionInfo::pass_SR(-1);
	}
	if( pass_SR || pass_SR_jup || pass_SR_jdown ) passAnyRegion=true;

	// Cutflow
	vector<bool> cutflow = selectionInfo::get_selectionResults_SR(0);
	for(int i=0; i<(int)cutflow.size(); i++){
	  if(!cutflow[i]) break;
	  h_cutflow_SR->Fill( i, cutflow[i] );
	}
      
      } // end SR selection

      // CR0b 
      pass_CR0b        = false;
      pass_CR0b_jup    = false;
      pass_CR0b_jdown  = false;
      if( doSelection_CR0b_ ){
	pass_CR0b          = selectionInfo::pass_CR0b(0);
	if( !sample.isData && !analyzeFast_ ){
	  pass_CR0b_jup    = selectionInfo::pass_CR0b(1);
	  pass_CR0b_jdown  = selectionInfo::pass_CR0b(-1);
	}
	if( pass_CR0b || pass_CR0b_jup || pass_CR0b_jdown ) passAnyRegion=true;
	
	// Cutflow
	vector<bool> cutflow = selectionInfo::get_selectionResults_CR0b(0);
	for(int i=0; i<(int)cutflow.size(); i++){
	  if(!cutflow[i]) break;
	  h_cutflow_CR0b->Fill( i, cutflow[i] );
	}
	
      } // end CR0b selection

      // CR2l
      pass_CR2l        = false;
      pass_CR2l_jup    = false;
      pass_CR2l_jdown  = false;
      if( doSelection_CR2l_ ){
	pass_CR2l          = selectionInfo::pass_CR2l(0, inclTaus_CR2l_, add2ndLepToMet_);
	if( !sample.isData && !analyzeFast_ ){
	  pass_CR2l_jup    = selectionInfo::pass_CR2l(1, inclTaus_CR2l_, add2ndLepToMet_);
	  pass_CR2l_jdown  = selectionInfo::pass_CR2l(-1, inclTaus_CR2l_, add2ndLepToMet_);
	}
	if( pass_CR2l || pass_CR2l_jup || pass_CR2l_jdown ) passAnyRegion=true;

	// Cutflow
	vector<bool> cutflow = selectionInfo::get_selectionResults_CR2l(0);
	for(int i=0; i<(int)cutflow.size(); i++){
	  if(!cutflow[i]) break;
	  h_cutflow_CR2l->Fill( i, cutflow[i] );
	}
	
      } // end CR2l selection


      //
      // Continue if Event Passes No Region of Interest
      //
      if( !passAnyRegion ) continue;



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
   
      // ICHEP 12.9fb Singal Regions
      passCats_SR_ICHEP.clear(); 
      passCats_SR_ICHEP_jup.clear();
      passCats_SR_ICHEP_jdown.clear();

      // ICHEP extended to 30fb Singal Regions
      passCats_SR_ICHEP_ext30fb.clear(); 
      passCats_SR_ICHEP_ext30fb_jup.clear();
      passCats_SR_ICHEP_ext30fb_jdown.clear();
     
      // ICHEP extended to 30fb, with mlb bins Singal Regions
      passCats_SR_dev_ext30fb_mlb_v1.clear(); 
      passCats_SR_dev_ext30fb_mlb_v1_jup.clear();
      passCats_SR_dev_ext30fb_mlb_v1_jdown.clear();
    
      // ICHEP extended to 30fb, with bJetPt bins Singal Regions
      passCats_SR_dev_ext30fb_bJetPt_v1.clear(); 
      passCats_SR_dev_ext30fb_bJetPt_v1_jup.clear();
      passCats_SR_dev_ext30fb_bJetPt_v1_jdown.clear();
    
      // Top Corridor Singal Regions
      passCats_SR_corridor.clear(); 
      passCats_SR_corridor_jup.clear();
      passCats_SR_corridor_jdown.clear();

      if( pass_SR || pass_CR0b || pass_CR2l ){
	passCats_SR_ICHEP = categoryInfo::passCategory_SR_ICHEP(0, add2ndLepToMet_);
	passCats_SR_ICHEP_ext30fb = categoryInfo::passCategory_SR_ICHEP_ext30fb(0, add2ndLepToMet_);
	passCats_SR_dev_ext30fb_mlb_v1 = categoryInfo::passCategory_SR_dev_ext30fb_mlb_v1(0, add2ndLepToMet_);
	passCats_SR_dev_ext30fb_bJetPt_v1 = categoryInfo::passCategory_SR_dev_ext30fb_bJetPt_v1(0, add2ndLepToMet_);
	passCats_SR_corridor = categoryInfo::passCategory_SR_corridor(0, add2ndLepToMet_);
      }
      // No JES for data
      if( !sample.isData ){
	if( pass_SR_jup || pass_CR0b_jup || pass_CR2l_jup ){
	  passCats_SR_ICHEP_jup = categoryInfo::passCategory_SR_ICHEP(1, add2ndLepToMet_);
	  passCats_SR_ICHEP_ext30fb_jup = categoryInfo::passCategory_SR_ICHEP_ext30fb(1, add2ndLepToMet_);
	  passCats_SR_dev_ext30fb_mlb_v1_jup = categoryInfo::passCategory_SR_dev_ext30fb_mlb_v1(1, add2ndLepToMet_);
	  passCats_SR_dev_ext30fb_bJetPt_v1_jup = categoryInfo::passCategory_SR_dev_ext30fb_bJetPt_v1(1, add2ndLepToMet_);
	  passCats_SR_corridor_jup = categoryInfo::passCategory_SR_corridor(1, add2ndLepToMet_);
	}
	if( pass_SR_jdown || pass_CR0b_jdown || pass_CR2l_jdown ){
	  passCats_SR_ICHEP_jdown = categoryInfo::passCategory_SR_ICHEP(-1, add2ndLepToMet_);
	  passCats_SR_ICHEP_ext30fb_jdown = categoryInfo::passCategory_SR_ICHEP_ext30fb(-1, add2ndLepToMet_);
	  passCats_SR_dev_ext30fb_mlb_v1_jdown = categoryInfo::passCategory_SR_dev_ext30fb_mlb_v1(-1, add2ndLepToMet_);
	  passCats_SR_dev_ext30fb_bJetPt_v1_jdown = categoryInfo::passCategory_SR_dev_ext30fb_bJetPt_v1(-1, add2ndLepToMet_);
	  passCats_SR_corridor_jdown = categoryInfo::passCategory_SR_corridor(-1, add2ndLepToMet_);
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
      LorentzVector lep1lep2bb_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bb_pt = -99.9;

      LorentzVector lep1lep2bbMet_TLV;
      double lep1lep2bbMet_pt = -99.9;
      if( pass_CR2l || pass_CR2l_jup || pass_CR2l_jdown ){
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

      } // end if pass CR2l 




      
      /////////////////////
      //                 //
      // Fill Histograms //
      //                 //
      /////////////////////
   
	
      //
      // Pass Signal Region
      //
      if( pass_SR || pass_SR_jup || pass_SR_jdown ){

	//
	// Yields
	//
	for(int iGen=0; iGen<nGenClassy; iGen++){

	  if( !passGenClassy[iGen] ) continue;

	  for(int iSys=0; iSys<nSystematics; iSys++){
	  
	    if(iSys==sysInfo::k_JESUp){ if(!pass_SR_jup) continue; }
	    else if(iSys==sysInfo::k_JESDown){ if(!pass_SR_jdown) continue; }
	    else{ if(!pass_SR) continue; }

	    // Histo Index
	    int iHisto = iGen*nSystematics + iSys;
	
	    // Event Weight for this Systematic
	    double wgt = wgtInfo->sys_wgts[iSys];


	    // ICHEP Signal Regions
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_jup.size(); iCat++){
		h_yields_ICHEP_SR[iHisto]->Fill( passCats_SR_ICHEP_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_jdown.size(); iCat++){
		h_yields_ICHEP_SR[iHisto]->Fill( passCats_SR_ICHEP_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP.size(); iCat++){
		h_yields_ICHEP_SR[iHisto]->Fill( passCats_SR_ICHEP[iCat], wgt );
	      }
	    }


	    // ICHEP Signal Regions, extened to 30fb
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb_jup.size(); iCat++){
		h_yields_ICHEP_ext30fb_SR[iHisto]->Fill( passCats_SR_ICHEP_ext30fb_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb_jdown.size(); iCat++){
		h_yields_ICHEP_ext30fb_SR[iHisto]->Fill( passCats_SR_ICHEP_ext30fb_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb.size(); iCat++){
		h_yields_ICHEP_ext30fb_SR[iHisto]->Fill( passCats_SR_ICHEP_ext30fb[iCat], wgt );
	      }
	    }



	    // Dev Signal Regions, extened to 30fb, with mlb bins
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1_jup.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_SR[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1_jdown.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_SR[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_SR[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1[iCat], wgt );
	      }
	    }


	    // Dev Signal Regions, extened to 30fb, with bJetPt bins
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1_jup.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_SR[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1_jdown.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_SR[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_SR[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1[iCat], wgt );
	      }
	    }


	    // Corridor Signal Regions
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_corridor_jup.size(); iCat++){
		h_yields_corridor_SR[iHisto]->Fill( passCats_SR_corridor_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_corridor_jdown.size(); iCat++){
		h_yields_corridor_SR[iHisto]->Fill( passCats_SR_corridor_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_corridor.size(); iCat++){
		h_yields_corridor_SR[iHisto]->Fill( passCats_SR_corridor[iCat], wgt );
	      }
	    }



	  } // end loop over systematics


	  //
	  // Non-yield Histograms
	  //
	  
	  // nJets
	  h_nJets_SR[iGen]->Fill( ngoodjets(), wgt_nominal );
  

	} // end loop over genClassifications
	


      } // end if pass Signal Region



      //
      // Pass Control Region, 0b
      //
      if( pass_CR0b || pass_CR0b_jup || pass_CR0b_jdown ){

	//
	// Yields
	//
	for(int iGen=0; iGen<nGenClassy; iGen++){

	  if( !passGenClassy[iGen] ) continue;

	  for(int iSys=0; iSys<nSystematics; iSys++){

	    if(iSys==sysInfo::k_JESUp){ if(!pass_CR0b_jup) continue; }
	    else if(iSys==sysInfo::k_JESDown){ if(!pass_CR0b_jdown) continue; }
	    else{ if(!pass_CR0b) continue; }
	
	    // Histo Index
	    int iHisto = iGen*nSystematics + iSys;

	    // Event Weight for this Systematic
	    double wgt = wgtInfo->sys_wgts[iSys];


	    // ICHEP Signal Regions
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_jup.size(); iCat++){
		h_yields_ICHEP_CR0b[iHisto]->Fill( passCats_SR_ICHEP_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_jdown.size(); iCat++){
		h_yields_ICHEP_CR0b[iHisto]->Fill( passCats_SR_ICHEP_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP.size(); iCat++){
		h_yields_ICHEP_CR0b[iHisto]->Fill( passCats_SR_ICHEP[iCat], wgt );
	      }
	    }


	    // ICHEP Signal Regions, extended to 30fb
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb_jup.size(); iCat++){
		h_yields_ICHEP_ext30fb_CR0b[iHisto]->Fill( passCats_SR_ICHEP_ext30fb_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb_jdown.size(); iCat++){
		h_yields_ICHEP_ext30fb_CR0b[iHisto]->Fill( passCats_SR_ICHEP_ext30fb_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb.size(); iCat++){
		h_yields_ICHEP_ext30fb_CR0b[iHisto]->Fill( passCats_SR_ICHEP_ext30fb[iCat], wgt );
	      }
	    }



	    // Dev Signal Regions, extended to 30fb, with mlb bins
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1_jup.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_CR0b[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1_jdown.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_CR0b[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_CR0b[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1[iCat], wgt );
	      }
	    }


	    // Dev Signal Regions, extended to 30fb, with bJetPt bins
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1_jup.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_CR0b[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1_jdown.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_CR0b[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_CR0b[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1[iCat], wgt );
	      }
	    }


	    // corridor Signal Regions
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_corridor_jup.size(); iCat++){
		h_yields_corridor_CR0b[iHisto]->Fill( passCats_SR_corridor_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_corridor_jdown.size(); iCat++){
		h_yields_corridor_CR0b[iHisto]->Fill( passCats_SR_corridor_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_corridor.size(); iCat++){
		h_yields_corridor_CR0b[iHisto]->Fill( passCats_SR_corridor[iCat], wgt );
	      }
	    }


	  
	  } // end loop over systematics


	  //
	  // Non-yield Histograms
	  //

	  // nJets
	  h_nJets_CR0b[iGen]->Fill( ngoodjets(), wgt_nominal );
  

	} // end loop over genClassifications
	
	

      } // end if pass Control Region, 0b



      //
      // Pass Control Region, 2l
      //
      if( pass_CR2l || pass_CR2l_jup || pass_CR2l_jdown ){
	
	// Loop over genClassifications
	for(int iGen=0; iGen<nGenClassy; iGen++){

	  if( !passGenClassy[iGen] ) continue;

	  // Loop over systematics
	  for(int iSys=0; iSys<nSystematics; iSys++){

	    if(iSys==sysInfo::k_JESUp){ if(!pass_CR2l_jup) continue; }
	    else if(iSys==sysInfo::k_JESDown){ if(!pass_CR2l_jdown) continue; }
	    else{ if(!pass_CR2l) continue; }
	
	    
	    // Histo Index
	    int iHisto = iGen*nSystematics + iSys;

	    // Event Weight for this Systematic
	    double wgt = wgtInfo->sys_wgts[iSys];


	    //
	    // Yields
	    //
	

	    // ICHEP Signal Regions
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_jup.size(); iCat++){
		h_yields_ICHEP_CR2l[iHisto]->Fill( passCats_SR_ICHEP_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_jdown.size(); iCat++){
		h_yields_ICHEP_CR2l[iHisto]->Fill( passCats_SR_ICHEP_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP.size(); iCat++){
		h_yields_ICHEP_CR2l[iHisto]->Fill( passCats_SR_ICHEP[iCat], wgt );
	      }
	    }


	    // ICHEP Signal Regions, extended to 30fb
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb_jup.size(); iCat++){
		h_yields_ICHEP_ext30fb_CR2l[iHisto]->Fill( passCats_SR_ICHEP_ext30fb_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb_jdown.size(); iCat++){
		h_yields_ICHEP_ext30fb_CR2l[iHisto]->Fill( passCats_SR_ICHEP_ext30fb_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_ICHEP_ext30fb.size(); iCat++){
		h_yields_ICHEP_ext30fb_CR2l[iHisto]->Fill( passCats_SR_ICHEP_ext30fb[iCat], wgt );
	      }
	    }



	    // Dev Signal Regions, extended to 30fb, mlb bins
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1_jup.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_CR2l[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1_jdown.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_CR2l[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_mlb_v1.size(); iCat++){
		h_yields_dev_ext30fb_mlb_v1_CR2l[iHisto]->Fill( passCats_SR_dev_ext30fb_mlb_v1[iCat], wgt );
	      }
	    }


	    // Dev Signal Regions, extended to 30fb, bJetPt bins
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1_jup.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_CR2l[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1_jdown.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_CR2l[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_dev_ext30fb_bJetPt_v1.size(); iCat++){
		h_yields_dev_ext30fb_bJetPt_v1_CR2l[iHisto]->Fill( passCats_SR_dev_ext30fb_bJetPt_v1[iCat], wgt );
	      }
	    }


	    // corridor Signal Regions
	    
	    // JES Up
	    if( iSys==sysInfo::k_JESUp ){
	      for(int iCat=0; iCat<(int)passCats_SR_corridor_jup.size(); iCat++){
		h_yields_corridor_CR2l[iHisto]->Fill( passCats_SR_corridor_jup[iCat], wgt );
	      }
	    }
	    // JES Dn
	    else if( iSys==sysInfo::k_JESDown ){
	      for(int iCat=0; iCat<(int)passCats_SR_corridor_jdown.size(); iCat++){
		h_yields_corridor_CR2l[iHisto]->Fill( passCats_SR_corridor_jdown[iCat], wgt );
	      }
	    }
	    // All Others
	    else{
	      for(int iCat=0; iCat<(int)passCats_SR_corridor.size(); iCat++){
		h_yields_corridor_CR2l[iHisto]->Fill( passCats_SR_corridor[iCat], wgt );
	      }
	    }



	  } // end loop over systematics


	  //
	  // Non-yield Histograms
	  //

	  // nJets
	  h_nJets_CR2l[iGen]->Fill( ngoodjets(), wgt_nominal );
  


	} // end loop over genClassifications
	

	
      }// end if pass Control Region 2l
      

     

    
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
  cout << "    Signal Region Cutflow: " << endl;
  for(int iCut=1; iCut<=(int)h_cutflow_SR->GetNbinsX(); iCut++){
    cout << "      nEvents pass " << h_cutflow_SR->GetXaxis()->GetBinLabel(iCut) << " = " << h_cutflow_SR->GetBinContent(iCut) << endl;
  }
  cout << endl;

  cout << endl;
  cout << "    Control Region, 0b Cutflow: " << endl;
  for(int iCut=1; iCut<=(int)h_cutflow_CR0b->GetNbinsX(); iCut++){
    cout << "      nEvents pass " << h_cutflow_CR0b->GetXaxis()->GetBinLabel(iCut) << " = " << h_cutflow_CR0b->GetBinContent(iCut) << endl;
  }
  cout << endl;

  cout << endl;
  cout << "    Control Region, 2l Cutflow: " << endl;
  for(int iCut=1; iCut<=(int)h_cutflow_CR2l->GetNbinsX(); iCut++){
    cout << "      nEvents pass " << h_cutflow_CR2l->GetXaxis()->GetBinLabel(iCut) << " = " << h_cutflow_CR2l->GetBinContent(iCut) << endl;
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

