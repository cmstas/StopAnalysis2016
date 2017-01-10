// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TColor.h"

// std
#include <algorithm>
#include <string>
#include <vector>

#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/sysInfo.h"

// dataMCplotMaker
#include "../../Software/dataMCplotMaker/dataMCplotMaker.cc"

//
// Main
//
void plotMaker( bool plotByGenDecay=true ){

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  //
  // Intialize User Inputs
  //
  bool plotData  = true;

  bool rescaleBinsAfterRebin = false;
  
  TString inDir  = "Output/Histos/";
  TString outDir = "Output/Plots/";

  TString outExt = ".pdf";
  
  //double lumi    = 12.9; // 2016 ICHEp
  //double lumi    = 29.53; // 2016 intermediate status update
  double lumi    = 36.46; // 2016 final lumi
  
  double sig_SF  = 1.0;

  
  //
  // Signal and Control Regions
  //
  std::vector<std::string> regionList;
  regionList.push_back("SR");
  regionList.push_back("CR0b");
  regionList.push_back("CR0b_tightBTagHighMlb");
  regionList.push_back("CR2l");
  const int nRegions = regionList.size();

  //
  // Gen Classifications
  //
  genClassyInfo::Util gen_incl( genClassyInfo::k_incl );
  TString hName_incl = gen_incl.label;

  genClassyInfo::Util gen_ee1lep( genClassyInfo::k_ee1lep );
  TString hName_1lep = gen_ee1lep.label;

  genClassyInfo::Util gen_ge2lep( genClassyInfo::k_ge2lep );
  TString hName_2lep = gen_ge2lep.label;

  genClassyInfo::Util gen_ZtoNuNu( genClassyInfo::k_ZtoNuNu );
  TString hName_ZtoNuNu = gen_ZtoNuNu.label;

    
  //
  // Nominal Systematic Label
  //
  sysInfo::Util sys_nominal( sysInfo::k_nominal );
  TString hName_nominal_sys = sys_nominal.label;
  
   
  //
  // Utility Vars
  //
  std::pair< sampleInfo::ID, genClassyInfo::ID > sample;

  std::vector<Color_t> colors; // order as bkg, then signal


  //
  // data
  //
  std::pair< sampleInfo::ID, genClassyInfo::ID > sample_data;
  sample_data.first  = sampleInfo::k_single_lepton_met;
  sample_data.second = genClassyInfo::k_incl;
 

  //
  // Bkgs
  //
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > bkgList;

  if(plotByGenDecay){
    
    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ZtoNuNu;
    bkgList.push_back(sample);
    colors.push_back( kMagenta-5 );

    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ee1lep_fromTop;
    bkgList.push_back(sample);
    colors.push_back( kRed-7 );

    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ee1lep_fromW;
    bkgList.push_back(sample);
    colors.push_back( kOrange-2 );

    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ge2lep;
    bkgList.push_back(sample);
    colors.push_back( kCyan-3 );

  } // end if plot by genDecay
  else{
    
    sample.first  = sampleInfo::k_rare; 
    sample.second = genClassyInfo::k_incl;
    bkgList.push_back(sample);
    colors.push_back( kMagenta-5 );

    sample.first  = sampleInfo::k_VJets; 
    sample.second = genClassyInfo::k_incl;
    bkgList.push_back(sample);
    colors.push_back( kGreen-3 );

    sample.first  = sampleInfo::k_singleT; 
    sample.second = genClassyInfo::k_incl;
    bkgList.push_back(sample);
    colors.push_back(kOrange-2);
   
    sample.first  = sampleInfo::k_ttbar; 
    sample.second = genClassyInfo::k_ee1lep;
    bkgList.push_back(sample);
    colors.push_back( kRed-7 );

    sample.first  = sampleInfo::k_ttbar; 
    sample.second = genClassyInfo::k_ge2lep;
    bkgList.push_back(sample);
    colors.push_back( kCyan-3 );

  }


  //
  // Signals
  //
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sigList;
 
  sample.first  = sampleInfo::k_T2tt;
  sample.second = genClassyInfo::k_incl;
  //sigList.push_back( sample );

  // T2tt mass points
  std::vector< std::pair< double, double > > T2tt_list;
  std::pair< double, double > T2tt_mass_point;
    
  T2tt_mass_point.first  = 400;
  T2tt_mass_point.second = 225;
  T2tt_list.push_back( T2tt_mass_point );
  //colors.push_back( kGreen );

  T2tt_mass_point.first  = 500;
  T2tt_mass_point.second = 325;
  T2tt_list.push_back( T2tt_mass_point );
  //colors.push_back( kMagenta+2 );

  T2tt_mass_point.first  = 800;
  T2tt_mass_point.second = 350;
  T2tt_list.push_back( T2tt_mass_point );
  //colors.push_back( kOrange+7 );

  T2tt_mass_point.first  = 800;
  T2tt_mass_point.second = 100;
  T2tt_list.push_back( T2tt_mass_point );
  //colors.push_back( kBlue );

  
  
  
  //
  // Variables to plot
  //
  std::vector< std::vector< sysInfo::Util > > sysList;
  std::vector< sysInfo::Util > sysListPerPlot;  // Must add Up and Down Variations for a single systematic

  std::vector<std::string> var_list_label;
  std::vector<std::string> var_list_title;
  std::vector<std::string> var_list_xaxis;

  std::vector<bool> var_doRebin;
  std::vector<TString> var_rebin_labels;
  std::vector<int> var_rebin_nBins;
  std::vector<double*> var_rebin_xBins;
  std::vector<double*> var_rebin_xBinsSF;

  bool noRebin = false;
  TString noRebin_label = "";
  int noRebin_nBins = 1;
  double noRebin_xBins[2]{0.0,0.0}; // entries = nBins+1
  double noRebin_xBinsSF[1]{1.0};   // SFs to keep bins Events/width



  // Yields, ICHEP
  var_list_label.push_back( "h_yields_SR_ICHEP" );
  var_list_title.push_back( "ICHEP Yields" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  // First 15 bins are SR
  const int nRebins_yields_SR_ICHEP = 15;
  double xRebins_yields_SR_ICHEP[nRebins_yields_SR_ICHEP+1]; 
  for(int i=1; i<=nRebins_yields_SR_ICHEP+1; i++){ xRebins_yields_SR_ICHEP[i-1]=i;} 
  double xRebinsSF_yields_SR_ICHEP[nRebins_yields_SR_ICHEP];
  for(int i=1; i<=nRebins_yields_SR_ICHEP; i++){ xRebinsSF_yields_SR_ICHEP[i-1]=1;}
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("srbins");
  var_rebin_nBins.push_back(nRebins_yields_SR_ICHEP);
  var_rebin_xBins.push_back(xRebins_yields_SR_ICHEP);
  var_rebin_xBinsSF.push_back(xRebinsSF_yields_SR_ICHEP);


  // Yields, ICHEP ext30fb
  var_list_label.push_back( "h_yields_SR_ICHEP_ext30fb" );
  var_list_title.push_back( "ICHEP Yields, ext" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  // First 21 bins are SR
  const int nRebins_yields_SR_ICHEP_ext30fb = 21;
  double xRebins_yields_SR_ICHEP_ext30fb[nRebins_yields_SR_ICHEP_ext30fb+1]; 
  for(int i=1; i<=nRebins_yields_SR_ICHEP_ext30fb+1; i++){ xRebins_yields_SR_ICHEP_ext30fb[i-1]=i;} 
  double xRebinsSF_yields_SR_ICHEP_ext30fb[nRebins_yields_SR_ICHEP_ext30fb];
  for(int i=1; i<=nRebins_yields_SR_ICHEP_ext30fb; i++){ xRebinsSF_yields_SR_ICHEP_ext30fb[i-1]=1;}
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("srbins");
  var_rebin_nBins.push_back(nRebins_yields_SR_ICHEP_ext30fb);
  var_rebin_xBins.push_back(xRebins_yields_SR_ICHEP_ext30fb);
  var_rebin_xBinsSF.push_back(xRebinsSF_yields_SR_ICHEP_ext30fb);


  // Yields, dev mlb
  var_list_label.push_back( "h_yields_SR_dev_ext30fb_mlb_v1" );
  var_list_title.push_back( "Yields" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  // First 29 bins are SR
  const int nRebins_yields_SR_dev_ext30fb_mlb_v1 = 29;
  double xRebins_yields_SR_dev_ext30fb_mlb_v1[nRebins_yields_SR_dev_ext30fb_mlb_v1+1]; 
  for(int i=1; i<=nRebins_yields_SR_dev_ext30fb_mlb_v1+1; i++){ xRebins_yields_SR_dev_ext30fb_mlb_v1[i-1]=i;} 
  double xRebinsSF_yields_SR_dev_ext30fb_mlb_v1[nRebins_yields_SR_dev_ext30fb_mlb_v1];
  for(int i=1; i<=nRebins_yields_SR_dev_ext30fb_mlb_v1; i++){ xRebinsSF_yields_SR_dev_ext30fb_mlb_v1[i-1]=1;}
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("srbins");
  var_rebin_nBins.push_back(nRebins_yields_SR_dev_ext30fb_mlb_v1);
  var_rebin_xBins.push_back(xRebins_yields_SR_dev_ext30fb_mlb_v1);
  var_rebin_xBinsSF.push_back(xRebinsSF_yields_SR_dev_ext30fb_mlb_v1);


  // Yields, dev mlb with tight bTagging
  var_list_label.push_back( "h_yields_SR_dev_ext30fb_mlb_v2" );
  var_list_title.push_back( "Yields" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  // First 29 bins are SR
  const int nRebins_yields_SR_dev_ext30fb_mlb_v2 = 27;
  double xRebins_yields_SR_dev_ext30fb_mlb_v2[nRebins_yields_SR_dev_ext30fb_mlb_v2+1]; 
  for(int i=1; i<=nRebins_yields_SR_dev_ext30fb_mlb_v2+1; i++){ xRebins_yields_SR_dev_ext30fb_mlb_v2[i-1]=i;} 
  double xRebinsSF_yields_SR_dev_ext30fb_mlb_v2[nRebins_yields_SR_dev_ext30fb_mlb_v2];
  for(int i=1; i<=nRebins_yields_SR_dev_ext30fb_mlb_v2; i++){ xRebinsSF_yields_SR_dev_ext30fb_mlb_v2[i-1]=1;}
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("srbins");
  var_rebin_nBins.push_back(nRebins_yields_SR_dev_ext30fb_mlb_v2);
  var_rebin_xBins.push_back(xRebins_yields_SR_dev_ext30fb_mlb_v2);
  var_rebin_xBinsSF.push_back(xRebinsSF_yields_SR_dev_ext30fb_mlb_v2);


  // Yields, dev bJetPt
  var_list_label.push_back( "h_yields_SR_dev_ext30fb_bJetPt_v1" );
  var_list_title.push_back( "Yields" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  // First 15 bins are SR
  const int nRebins_yields_SR_dev_ext30fb_bJetPt_v1 = 29;
  double xRebins_yields_SR_dev_ext30fb_bJetPt_v1[nRebins_yields_SR_dev_ext30fb_bJetPt_v1+1]; 
  for(int i=1; i<=nRebins_yields_SR_dev_ext30fb_bJetPt_v1+1; i++){ xRebins_yields_SR_dev_ext30fb_bJetPt_v1[i-1]=i;} 
  double xRebinsSF_yields_SR_dev_ext30fb_bJetPt_v1[nRebins_yields_SR_dev_ext30fb_bJetPt_v1];
  for(int i=1; i<=nRebins_yields_SR_dev_ext30fb_bJetPt_v1; i++){ xRebinsSF_yields_SR_dev_ext30fb_bJetPt_v1[i-1]=1;}
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("srbins");
  var_rebin_nBins.push_back(nRebins_yields_SR_dev_ext30fb_bJetPt_v1);
  var_rebin_xBins.push_back(xRebins_yields_SR_dev_ext30fb_bJetPt_v1);
  var_rebin_xBinsSF.push_back(xRebinsSF_yields_SR_dev_ext30fb_bJetPt_v1);


  // Yields, dev top corridor
  var_list_label.push_back( "h_yields_SR_corridor" );
  var_list_title.push_back( "Yields" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  // First 4 bins are SR
  const int nRebins_yields_SR_corridor = 4;
  double xRebins_yields_SR_corridor[nRebins_yields_SR_corridor+1]; 
  for(int i=1; i<=nRebins_yields_SR_corridor+1; i++){ xRebins_yields_SR_corridor[i-1]=i;} 
  double xRebinsSF_yields_SR_corridor[nRebins_yields_SR_corridor];
  for(int i=1; i<=nRebins_yields_SR_corridor; i++){ xRebinsSF_yields_SR_corridor[i-1]=1;}
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("srbins");
  var_rebin_nBins.push_back(nRebins_yields_SR_corridor);
  var_rebin_xBins.push_back(xRebins_yields_SR_corridor);
  var_rebin_xBinsSF.push_back(xRebinsSF_yields_SR_corridor);

  

  // nJets
  var_list_label.push_back( "h_nJets" );
  var_list_title.push_back( "Number of Jets" );
  var_list_xaxis.push_back( "nJets" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // nJets Rebinned
  var_list_label.push_back( "h_nJets" );
  var_list_title.push_back( "Number of Jets" );
  var_list_xaxis.push_back( "nJets" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_nJets = 3;
  double xRebins_nJets[nRebins_nJets+1]{ 1.5, 2.5, 3.5, 10.5 };
  double xRebinsSF_nJets[nRebins_nJets]{    1.0, 1.0, (1.0/7.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("rebinned");
  var_rebin_nBins.push_back(nRebins_nJets);
  var_rebin_xBins.push_back(xRebins_nJets);
  var_rebin_xBinsSF.push_back(xRebinsSF_nJets);


  // nBTags
  var_list_label.push_back( "h_nBTags" );
  var_list_title.push_back( "Number of b-Tagged Jets" );
  var_list_xaxis.push_back( "nBTags" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  
  // lep1 pT, incl selection
  var_list_label.push_back( "h_lep1Pt__inclSelection" );
  var_list_title.push_back( "Lepton p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1 pT, ==2jets
  var_list_label.push_back( "h_lep1Pt__ee2jSelection" );
  var_list_title.push_back( "Lepton p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1 pT, ==3jets
  var_list_label.push_back( "h_lep1Pt__ee3jSelection" );
  var_list_title.push_back( "Lepton p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1 pT, >=4jets
  var_list_label.push_back( "h_lep1Pt__ge4jSelection" );
  var_list_title.push_back( "Lepton p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  

  // lep2 pT, incl selection
  var_list_label.push_back( "h_lep2Pt__inclSelection" );
  var_list_title.push_back( "Trailing Lepton p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep2 pT, ==2jets
  var_list_label.push_back( "h_lep2Pt__ee2jSelection" );
  var_list_title.push_back( "Trailing Lepton p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep2 pT, ==3jets
  var_list_label.push_back( "h_lep2Pt__ee3jSelection" );
  var_list_title.push_back( "Trailing Lepton p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep2 pT, >=4jets
  var_list_label.push_back( "h_lep2Pt__ge4jSelection" );
  var_list_title.push_back( "Trailing Lepton p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  

  // jet pT, incl selection
  var_list_label.push_back( "h_jetPt__inclSelection" );
  var_list_title.push_back( "Selected Jets p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet pT, ==2jets
  var_list_label.push_back( "h_jetPt__ee2jSelection" );
  var_list_title.push_back( "Selected Jets p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet pT, ==3jets
  var_list_label.push_back( "h_jetPt__ee3jSelection" );
  var_list_title.push_back( "Selected Jets p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet pT, >=4jets
  var_list_label.push_back( "h_jetPt__ge4jSelection" );
  var_list_title.push_back( "Selected Jets p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);



  // jet1 pT, incl selection
  var_list_label.push_back( "h_jet1Pt__inclSelection" );
  var_list_title.push_back( "Leading Jet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet1 pT, ==2jets
  var_list_label.push_back( "h_jet1Pt__ee2jSelection" );
  var_list_title.push_back( "Leading Jet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet1 pT, ==3jets
  var_list_label.push_back( "h_jet1Pt__ee3jSelection" );
  var_list_title.push_back( "Leading Jet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet1 pT, >=4jets
  var_list_label.push_back( "h_jet1Pt__ge4jSelection" );
  var_list_title.push_back( "Leading Jet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  
  // jet2 pT, incl selection
  var_list_label.push_back( "h_jet2Pt__inclSelection" );
  var_list_title.push_back( "Trailing Jet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet2 pT, ==2jets
  var_list_label.push_back( "h_jet2Pt__ee2jSelection" );
  var_list_title.push_back( "Trailing Jet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet2 pT, ==3jets
  var_list_label.push_back( "h_jet2Pt__ee3jSelection" );
  var_list_title.push_back( "Trailing Jet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // jet2 pT, >=4jets
  var_list_label.push_back( "h_jet2Pt__ge4jSelection" );
  var_list_title.push_back( "Trailing Jet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);



  // csvJet1 pT, incl selection
  var_list_label.push_back( "h_csvJet1Pt__inclSelection" );
  var_list_title.push_back( "Highest bTag Disc. Jet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // csvJet1 pT, ==2jets
  var_list_label.push_back( "h_csvJet1Pt__ee2jSelection" );
  var_list_title.push_back( "Highest bTag Disc. Jet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // csvJet1 pT, ==3jets
  var_list_label.push_back( "h_csvJet1Pt__ee3jSelection" );
  var_list_title.push_back( "Highest bTag Disc. Jet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // csvJet1 pT, >=4jets
  var_list_label.push_back( "h_csvJet1Pt__ge4jSelection" );
  var_list_title.push_back( "Highest bTag Disc. Jet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  

  // csvJet2 pT, incl selection
  var_list_label.push_back( "h_csvJet2Pt__inclSelection" );
  var_list_title.push_back( "Lepton p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // csvJet2 pT, ==2jets
  var_list_label.push_back( "h_csvJet2Pt__ee2jSelection" );
  var_list_title.push_back( "Lepton p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // csvJet2 pT, ==3jets
  var_list_label.push_back( "h_csvJet2Pt__ee3jSelection" );
  var_list_title.push_back( "Lepton p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // csvJet2 pT, >=4jets
  var_list_label.push_back( "h_csvJet2Pt__ge4jSelection" );
  var_list_title.push_back( "Lepton p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // met, incl selection
  var_list_label.push_back( "h_met__inclSelection" );
  var_list_title.push_back( "MET, >=2 jets" );
  var_list_xaxis.push_back( "MET [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // met, ==2jets
  var_list_label.push_back( "h_met__ee2jSelection" );
  var_list_title.push_back( "MET, ==2 jets" );
  var_list_xaxis.push_back( "MET [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // met, ==3jets
  var_list_label.push_back( "h_met__ee3jSelection" );
  var_list_title.push_back( "MET, ==3 jets" );
  var_list_xaxis.push_back( "MET [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // met, <4jets
  var_list_label.push_back( "h_met__lt4jSelection" );
  var_list_title.push_back( "MET, <4 jets" );
  var_list_xaxis.push_back( "MET [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // met, >=4jets
  var_list_label.push_back( "h_met__ge4jSelection" );
  var_list_title.push_back( "MET, >=4 jets" );
  var_list_xaxis.push_back( "MET [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // met, <4jets
  var_list_label.push_back( "h_met__lt4jSelection" );
  var_list_title.push_back( "MET, <4 jets" );
  var_list_xaxis.push_back( "MET [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_met_lt4j = 10;
  double xRebins_met_lt4j[nRebins_met_lt4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 550.0, 650.0, 800.0 };
  double xRebinsSF_met_lt4j[nRebins_met_lt4j]{   0.5,  0.5,   0.5,   0.5,   0.5,   0.5,    0.5,  0.5,   0.5, (1.0/3.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_met_lt4j);
  var_rebin_xBins.push_back(xRebins_met_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_met_lt4j);

  
  // met, >=4jets
  var_list_label.push_back( "h_met__ge4jSelection" );
  var_list_title.push_back( "MET, >=4 jets" );
  var_list_xaxis.push_back( "MET [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_met_ge4j = 10;
  double xRebins_met_ge4j[nRebins_met_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 550.0, 650.0, 800.0 };
  double xRebinsSF_met_ge4j[nRebins_met_ge4j]{   0.5,  0.5,   0.5,   0.5,   0.5,   0.5,    0.5,  0.5,   0.5, (1.0/3.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_met_ge4j);
  var_rebin_xBins.push_back(xRebins_met_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_met_ge4j);


  // lep1lep2bbPt, incl selection
  var_list_label.push_back( "h_lep1lep2bbPt__inclSelection" );
  var_list_title.push_back( "lep1(lep2)bb system p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bb system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1lep2bbPt, ==2jets
  var_list_label.push_back( "h_lep1lep2bbPt__ee2jSelection" );
  var_list_title.push_back( "lep1(lep2)bb system p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bb system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1lep2bbPt, ==3jets
  var_list_label.push_back( "h_lep1lep2bbPt__ee3jSelection" );
  var_list_title.push_back( "lep1(lep2)bb system p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bb system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1lep2bbPt, >=4jets
  var_list_label.push_back( "h_lep1lep2bbPt__ge4jSelection" );
  var_list_title.push_back( "lep1(lep2)bb system p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bb system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  
  // lep1lep2bbMetPt, incl selection
  var_list_label.push_back( "h_lep1lep2bbMetPt__inclSelection" );
  var_list_title.push_back( "lep1(lep2)bbMet system p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bbMet system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1lep2bbMetPt, ==2jets
  var_list_label.push_back( "h_lep1lep2bbMetPt__ee2jSelection" );
  var_list_title.push_back( "lep1(lep2)bbMet system p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bbMet system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1lep2bbMetPt, ==3jets
  var_list_label.push_back( "h_lep1lep2bbMetPt__ee3jSelection" );
  var_list_title.push_back( "lep1(lep2)bbMet system p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bbMet system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // lep1lep2bbMetPt, >=4jets
  var_list_label.push_back( "h_lep1lep2bbMetPt__ge4jSelection" );
  var_list_title.push_back( "lep1(lep2)bbMet system p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "lep1(lep2)bbMet system p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);



  // mt, incl selection
  var_list_label.push_back( "h_mt__inclSelection" );
  var_list_title.push_back( "M_{T}, >=2 jets" );
  var_list_xaxis.push_back( "M_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mt, ==2jets
  var_list_label.push_back( "h_mt__ee2jSelection" );
  var_list_title.push_back( "M_{T}, ==2 jets" );
  var_list_xaxis.push_back( "M_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mt, ==3jets
  var_list_label.push_back( "h_mt__ee3jSelection" );
  var_list_title.push_back( "M_{T}, ==3 jets" );
  var_list_xaxis.push_back( "M_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mt, >=4jets
  var_list_label.push_back( "h_mt__ge4jSelection" );
  var_list_title.push_back( "M_{T}, >=4 jets" );
  var_list_xaxis.push_back( "M_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);



  // modTopness, incl selection
  var_list_label.push_back( "h_modTopness__inclSelection" );
  var_list_title.push_back( "modified topness, >=2 jets" );
  var_list_xaxis.push_back( "modified topness" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // modTopness, ==2jets
  var_list_label.push_back( "h_modTopness__ee2jSelection" );
  var_list_title.push_back( "modified topness, ==2 jets" );
  var_list_xaxis.push_back( "modified topness" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // modTopness, ==3jets
  var_list_label.push_back( "h_modTopness__ee3jSelection" );
  var_list_title.push_back( "modified topness, ==3 jets" );
  var_list_xaxis.push_back( "modified topness" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // modTopness, >=4jets
  var_list_label.push_back( "h_modTopness__ge4jSelection" );
  var_list_title.push_back( "modified topness, >=4 jets" );
  var_list_xaxis.push_back( "modified topness" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  
  // mt2w, incl selection
  var_list_label.push_back( "h_mt2w__inclSelection" );
  var_list_title.push_back( "MT2W, >=2 jets" );
  var_list_xaxis.push_back( "MT2W [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mt2w, ==2jets
  var_list_label.push_back( "h_mt2w__ee2jSelection" );
  var_list_title.push_back( "MT2W, ==2 jets" );
  var_list_xaxis.push_back( "MT2W [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mt2w, ==3jets
  var_list_label.push_back( "h_mt2w__ee3jSelection" );
  var_list_title.push_back( "MT2W, ==3 jets" );
  var_list_xaxis.push_back( "MT2W [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mt2w, >=4jets
  var_list_label.push_back( "h_mt2w__ge4jSelection" );
  var_list_title.push_back( "MT2W, >=4 jets" );
  var_list_xaxis.push_back( "MT2W [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  
  // mlb, incl selection
  var_list_label.push_back( "h_mlb__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb, ==2jets
  var_list_label.push_back( "h_mlb__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  
  
  // mlb, incl selection
  var_list_label.push_back( "h_mlb__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_incl = 8;
  double xRebins_mlb_incl[nRebins_mlb_incl+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_incl[nRebins_mlb_incl]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_incl);
  var_rebin_xBins.push_back(xRebins_mlb_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_ee2j = 8;
  double xRebins_mlb_ee2j[nRebins_mlb_ee2j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_ee2j[nRebins_mlb_ee2j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_ee3j = 8;
  double xRebins_mlb_ee3j[nRebins_mlb_ee3j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_ee3j[nRebins_mlb_ee3j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lt4j = 8;
  double xRebins_mlb_lt4j[nRebins_mlb_lt4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lt4j[nRebins_mlb_lt4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_ge4j = 8;
  double xRebins_mlb_ge4j[nRebins_mlb_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_ge4j[nRebins_mlb_ge4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_ge4j);



  // mlb, incl selection
  var_list_label.push_back( "h_mlb__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_coarseRebin_incl = 2;
  double xRebins_mlb_coarseRebin_incl[nRebins_mlb_coarseRebin_incl+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_incl[nRebins_mlb_coarseRebin_incl]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_incl);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_coarseRebin_ee2j = 2;
  double xRebins_mlb_coarseRebin_ee2j[nRebins_mlb_coarseRebin_ee2j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_ee2j[nRebins_mlb_coarseRebin_ee2j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_coarseRebin_ee3j = 2;
  double xRebins_mlb_coarseRebin_ee3j[nRebins_mlb_coarseRebin_ee3j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_ee3j[nRebins_mlb_coarseRebin_ee3j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_coarseRebin_lt4j = 2;
  double xRebins_mlb_coarseRebin_lt4j[nRebins_mlb_coarseRebin_lt4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_lt4j[nRebins_mlb_coarseRebin_lt4j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_coarseRebin_ge4j = 2;
  double xRebins_mlb_coarseRebin_ge4j[nRebins_mlb_coarseRebin_ge4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_ge4j[nRebins_mlb_coarseRebin_ge4j]{ (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_ge4j);



  // mlb, modTopness<0.0 selection
  var_list_label.push_back( "h_mlb__lt0modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness<0.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb, modTopness>=0.0 selection
  var_list_label.push_back( "h_mlb__ge0modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness>=0.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb, modTopness>=10.0 selection
  var_list_label.push_back( "h_mlb__ge10modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness>=10.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

   
  
  // mlb, modTopness<0.0 selection, fine rebin
  var_list_label.push_back( "h_mlb__lt0modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness<0.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lt0modTop = 8;
  double xRebins_mlb_lt0modTop[nRebins_mlb_lt0modTop+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lt0modTop[nRebins_mlb_lt0modTop]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lt0modTop);
  var_rebin_xBins.push_back(xRebins_mlb_lt0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lt0modTop);

  
  // mlb, modTopness>=0.0 selection, fine rebin
  var_list_label.push_back( "h_mlb__ge0modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness>=0.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_ge0modTop = 8;
  double xRebins_mlb_ge0modTop[nRebins_mlb_ge0modTop+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_ge0modTop[nRebins_mlb_ge0modTop]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_ge0modTop);
  var_rebin_xBins.push_back(xRebins_mlb_ge0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_ge0modTop);

  // mlb, modTopness>=10.0 selection, fine rebin
  var_list_label.push_back( "h_mlb__ge10modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness>=10.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_ge10modTop = 8;
  double xRebins_mlb_ge10modTop[nRebins_mlb_ge10modTop+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_ge10modTop[nRebins_mlb_ge10modTop]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_ge10modTop);
  var_rebin_xBins.push_back(xRebins_mlb_ge10modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_ge10modTop);


  // mlb, modTopness<0.0 selection, coarse rebin
  var_list_label.push_back( "h_mlb__lt0modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness<0.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_coarseRebin_lt0modTop = 2;
  double xRebins_mlb_coarseRebin_lt0modTop[nRebins_mlb_coarseRebin_lt0modTop+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_lt0modTop[nRebins_mlb_coarseRebin_lt0modTop]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_lt0modTop);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_lt0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_lt0modTop);

  
  // mlb, modTopness>=0.0 selection, coarse rebin
  var_list_label.push_back( "h_mlb__ge0modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness>=0.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_coarseRebin_ge0modTop = 2;
  double xRebins_mlb_coarseRebin_ge0modTop[nRebins_mlb_coarseRebin_ge0modTop+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_ge0modTop[nRebins_mlb_coarseRebin_ge0modTop]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_ge0modTop);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_ge0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_ge0modTop);

  // mlb, modTopness>=10.0 selection, coarse rebin
  var_list_label.push_back( "h_mlb__ge10modTopnessSelection" );
  var_list_title.push_back( "M_{lb}, modTopness>=10.0" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_coarseRebin_ge10modTop = 2;
  double xRebins_mlb_coarseRebin_ge10modTop[nRebins_mlb_coarseRebin_ge10modTop+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_coarseRebin_ge10modTop[nRebins_mlb_coarseRebin_ge10modTop]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_coarseRebin_ge10modTop);
  var_rebin_xBins.push_back(xRebins_mlb_coarseRebin_ge10modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_coarseRebin_ge10modTop);

  

  // mlb_lep2, incl selection
  var_list_label.push_back( "h_mlb_lep2__inclSelection" );
  var_list_title.push_back( "M_{lep2b}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2, ==2jets
  var_list_label.push_back( "h_mlb_lep2__ee2jSelection" );
  var_list_title.push_back( "M_{lep2b}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2, ==3jets
  var_list_label.push_back( "h_mlb_lep2__ee3jSelection" );
  var_list_title.push_back( "M_{lep2b}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2, <4jets
  var_list_label.push_back( "h_mlb_lep2__lt4jSelection" );
  var_list_title.push_back( "M_{lep2b}, <4 jets" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2, >=4jets
  var_list_label.push_back( "h_mlb_lep2__ge4jSelection" );
  var_list_title.push_back( "M_{lep2b}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);



  // mlb_lep2, incl selection, rebin
  var_list_label.push_back( "h_mlb_lep2__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_incl = 8;
  double xRebins_mlb_lep2_incl[nRebins_mlb_lep2_incl+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_incl[nRebins_mlb_lep2_incl]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_incl);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb_lep2__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_ee2j = 8;
  double xRebins_mlb_lep2_ee2j[nRebins_mlb_lep2_ee2j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_ee2j[nRebins_mlb_lep2_ee2j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb_lep2__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_ee3j = 8;
  double xRebins_mlb_lep2_ee3j[nRebins_mlb_lep2_ee3j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_ee3j[nRebins_mlb_lep2_ee3j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb_lep2__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_lt4j = 8;
  double xRebins_mlb_lep2_lt4j[nRebins_mlb_lep2_lt4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_lt4j[nRebins_mlb_lep2_lt4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb_lep2__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_lep2_ge4j = 8;
  double xRebins_mlb_lep2_ge4j[nRebins_mlb_lep2_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_ge4j[nRebins_mlb_lep2_ge4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_ge4j);



  // mlb, incl selection
  var_list_label.push_back( "h_mlb_lep2__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_coarseRebin_incl = 2;
  double xRebins_mlb_lep2_coarseRebin_incl[nRebins_mlb_lep2_coarseRebin_incl+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_coarseRebin_incl[nRebins_mlb_lep2_coarseRebin_incl]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_coarseRebin_incl);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_coarseRebin_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_coarseRebin_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb_lep2__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_coarseRebin_ee2j = 2;
  double xRebins_mlb_lep2_coarseRebin_ee2j[nRebins_mlb_lep2_coarseRebin_ee2j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_coarseRebin_ee2j[nRebins_mlb_lep2_coarseRebin_ee2j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_coarseRebin_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_coarseRebin_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_coarseRebin_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb_lep2__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_coarseRebin_ee3j = 2;
  double xRebins_mlb_lep2_coarseRebin_ee3j[nRebins_mlb_lep2_coarseRebin_ee3j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_coarseRebin_ee3j[nRebins_mlb_lep2_coarseRebin_ee3j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_coarseRebin_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_coarseRebin_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_coarseRebin_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb_lep2__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_coarseRebin_lt4j = 2;
  double xRebins_mlb_lep2_coarseRebin_lt4j[nRebins_mlb_lep2_coarseRebin_lt4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_coarseRebin_lt4j[nRebins_mlb_lep2_coarseRebin_lt4j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_coarseRebin_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_coarseRebin_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_coarseRebin_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb_lep2__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_lep2_coarseRebin_ge4j = 2;
  double xRebins_mlb_lep2_coarseRebin_ge4j[nRebins_mlb_lep2_coarseRebin_ge4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_coarseRebin_ge4j[nRebins_mlb_lep2_coarseRebin_ge4j]{ (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_coarseRebin_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_coarseRebin_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_coarseRebin_ge4j);



  // mlb_150to250met, incl selection
  var_list_label.push_back( "h_mlb_150to250met__inclSelection" );
  var_list_title.push_back( "M_{lb}, nJet>=2, 150<met<250" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_150to250met, ==2jets
  var_list_label.push_back( "h_mlb_150to250met__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_150to250met, ==3jets
  var_list_label.push_back( "h_mlb_150to250met__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_150to250met, <4jets
  var_list_label.push_back( "h_mlb_150to250met__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_150to250met, >=4jets
  var_list_label.push_back( "h_mlb_150to250met__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // mlb, incl selection, met sideband CR
  var_list_label.push_back( "h_mlb_150to250met__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_incl = 8;
  double xRebins_mlb_150to250met_incl[nRebins_mlb_150to250met_incl+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_150to250met_incl[nRebins_mlb_150to250met_incl]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_incl);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb_150to250met__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_ee2j = 8;
  double xRebins_mlb_150to250met_ee2j[nRebins_mlb_150to250met_ee2j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_150to250met_ee2j[nRebins_mlb_150to250met_ee2j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb_150to250met__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_ee3j = 8;
  double xRebins_mlb_150to250met_ee3j[nRebins_mlb_150to250met_ee3j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_150to250met_ee3j[nRebins_mlb_150to250met_ee3j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb_150to250met__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_lt4j = 8;
  double xRebins_mlb_150to250met_lt4j[nRebins_mlb_150to250met_lt4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_150to250met_lt4j[nRebins_mlb_150to250met_lt4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb_150to250met__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_150to250met_ge4j = 8;
  double xRebins_mlb_150to250met_ge4j[nRebins_mlb_150to250met_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_150to250met_ge4j[nRebins_mlb_150to250met_ge4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_ge4j);



  // mlb, incl selection
  var_list_label.push_back( "h_mlb_150to250met__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_coarseRebin_incl = 2;
  double xRebins_mlb_150to250met_coarseRebin_incl[nRebins_mlb_150to250met_coarseRebin_incl+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_150to250met_coarseRebin_incl[nRebins_mlb_150to250met_coarseRebin_incl]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_coarseRebin_incl);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_coarseRebin_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_coarseRebin_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb_150to250met__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_coarseRebin_ee2j = 2;
  double xRebins_mlb_150to250met_coarseRebin_ee2j[nRebins_mlb_150to250met_coarseRebin_ee2j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_150to250met_coarseRebin_ee2j[nRebins_mlb_150to250met_coarseRebin_ee2j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_coarseRebin_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_coarseRebin_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_coarseRebin_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb_150to250met__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_coarseRebin_ee3j = 2;
  double xRebins_mlb_150to250met_coarseRebin_ee3j[nRebins_mlb_150to250met_coarseRebin_ee3j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_150to250met_coarseRebin_ee3j[nRebins_mlb_150to250met_coarseRebin_ee3j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_coarseRebin_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_coarseRebin_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_coarseRebin_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb_150to250met__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_150to250met_coarseRebin_lt4j = 2;
  double xRebins_mlb_150to250met_coarseRebin_lt4j[nRebins_mlb_150to250met_coarseRebin_lt4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_150to250met_coarseRebin_lt4j[nRebins_mlb_150to250met_coarseRebin_lt4j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_coarseRebin_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_coarseRebin_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_coarseRebin_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb_150to250met__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_150to250met_coarseRebin_ge4j = 2;
  double xRebins_mlb_150to250met_coarseRebin_ge4j[nRebins_mlb_150to250met_coarseRebin_ge4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_150to250met_coarseRebin_ge4j[nRebins_mlb_150to250met_coarseRebin_ge4j]{ (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_150to250met_coarseRebin_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_150to250met_coarseRebin_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_150to250met_coarseRebin_ge4j);



  // mlb_lep2_150to250met, incl selection
  var_list_label.push_back( "h_mlb_lep2_150to250met__inclSelection" );
  var_list_title.push_back( "M_{lep2b}, nJet>=2, 150<met<250" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2_150to250met, ==2jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ee2jSelection" );
  var_list_title.push_back( "M_{lep2b}, ==2 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2_150to250met, ==3jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ee3jSelection" );
  var_list_title.push_back( "M_{lep2b}, ==3 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2_150to250met, <4jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__lt4jSelection" );
  var_list_title.push_back( "M_{lep2b}, <4 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // mlb_lep2_150to250met, >=4jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ge4jSelection" );
  var_list_title.push_back( "M_{lep2b}, >=4 jet, 150<met<250" );
  var_list_xaxis.push_back( "M_{lep2b} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // mlb_lep2_150to250met, incl selection
  var_list_label.push_back( "h_mlb_lep2_150to250met__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_incl = 8;
  double xRebins_mlb_lep2_150to250met_incl[nRebins_mlb_lep2_150to250met_incl+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_incl[nRebins_mlb_lep2_150to250met_incl]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_incl);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_ee2j = 8;
  double xRebins_mlb_lep2_150to250met_ee2j[nRebins_mlb_lep2_150to250met_ee2j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_ee2j[nRebins_mlb_lep2_150to250met_ee2j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_ee3j = 8;
  double xRebins_mlb_lep2_150to250met_ee3j[nRebins_mlb_lep2_150to250met_ee3j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_ee3j[nRebins_mlb_lep2_150to250met_ee3j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_lt4j = 8;
  double xRebins_mlb_lep2_150to250met_lt4j[nRebins_mlb_lep2_150to250met_lt4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_lt4j[nRebins_mlb_lep2_150to250met_lt4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_lep2_150to250met_ge4j = 8;
  double xRebins_mlb_lep2_150to250met_ge4j[nRebins_mlb_lep2_150to250met_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_ge4j[nRebins_mlb_lep2_150to250met_ge4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_ge4j);



  // mlb, incl selection
  var_list_label.push_back( "h_mlb_lep2_150to250met__inclSelection" );
  var_list_title.push_back( "M_{lb}, >=2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_coarseRebin_incl = 2;
  double xRebins_mlb_lep2_150to250met_coarseRebin_incl[nRebins_mlb_lep2_150to250met_coarseRebin_incl+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_coarseRebin_incl[nRebins_mlb_lep2_150to250met_coarseRebin_incl]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_coarseRebin_incl);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_coarseRebin_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_coarseRebin_incl);

  
  // mlb, ==2jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ee2jSelection" );
  var_list_title.push_back( "M_{lb}, ==2 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_coarseRebin_ee2j = 2;
  double xRebins_mlb_lep2_150to250met_coarseRebin_ee2j[nRebins_mlb_lep2_150to250met_coarseRebin_ee2j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_coarseRebin_ee2j[nRebins_mlb_lep2_150to250met_coarseRebin_ee2j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_coarseRebin_ee2j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_coarseRebin_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_coarseRebin_ee2j);

  // mlb, ==3jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ee3jSelection" );
  var_list_title.push_back( "M_{lb}, ==3 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_coarseRebin_ee3j = 2;
  double xRebins_mlb_lep2_150to250met_coarseRebin_ee3j[nRebins_mlb_lep2_150to250met_coarseRebin_ee3j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_coarseRebin_ee3j[nRebins_mlb_lep2_150to250met_coarseRebin_ee3j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_coarseRebin_ee3j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_coarseRebin_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_coarseRebin_ee3j);

  // mlb, <4jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__lt4jSelection" );
  var_list_title.push_back( "M_{lb}, <4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_mlb_lep2_150to250met_coarseRebin_lt4j = 2;
  double xRebins_mlb_lep2_150to250met_coarseRebin_lt4j[nRebins_mlb_lep2_150to250met_coarseRebin_lt4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_coarseRebin_lt4j[nRebins_mlb_lep2_150to250met_coarseRebin_lt4j]{   (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_coarseRebin_lt4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_coarseRebin_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_coarseRebin_lt4j);

  // mlb, >=4jets
  var_list_label.push_back( "h_mlb_lep2_150to250met__ge4jSelection" );
  var_list_title.push_back( "M_{lb}, >=4 jets" );
  var_list_xaxis.push_back( "M_{lb} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_mlb_lep2_150to250met_coarseRebin_ge4j = 2;
  double xRebins_mlb_lep2_150to250met_coarseRebin_ge4j[nRebins_mlb_lep2_150to250met_coarseRebin_ge4j+1]{ 0.0, 175.0, 600.0 };
  double xRebinsSF_mlb_lep2_150to250met_coarseRebin_ge4j[nRebins_mlb_lep2_150to250met_coarseRebin_ge4j]{ (1.0/7.0), (1.0/31.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_mlb_lep2_150to250met_coarseRebin_ge4j);
  var_rebin_xBins.push_back(xRebins_mlb_lep2_150to250met_coarseRebin_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_mlb_lep2_150to250met_coarseRebin_ge4j);



  // bJetPt, incl selection
  var_list_label.push_back( "h_bJetPt__inclSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt, ==2jets
  var_list_label.push_back( "h_bJetPt__ee2jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt, ==3jets
  var_list_label.push_back( "h_bJetPt__ee3jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt, <4jets
  var_list_label.push_back( "h_bJetPt__lt4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, <4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt, >=4jets
  var_list_label.push_back( "h_bJetPt__ge4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  
  
  // bJetPt, incl selection
  var_list_label.push_back( "h_bJetPt__inclSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_incl = 8;
  double xRebins_bJetPt_incl[nRebins_bJetPt_incl+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_incl[nRebins_bJetPt_incl]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_incl);
  var_rebin_xBins.push_back(xRebins_bJetPt_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_incl);

  
  // bJetPt, ==2jets
  var_list_label.push_back( "h_bJetPt__ee2jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_ee2j = 8;
  double xRebins_bJetPt_ee2j[nRebins_bJetPt_ee2j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_ee2j[nRebins_bJetPt_ee2j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_ee2j);
  var_rebin_xBins.push_back(xRebins_bJetPt_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_ee2j);

  // bJetPt, ==3jets
  var_list_label.push_back( "h_bJetPt__ee3jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_ee3j = 8;
  double xRebins_bJetPt_ee3j[nRebins_bJetPt_ee3j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_ee3j[nRebins_bJetPt_ee3j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_ee3j);
  var_rebin_xBins.push_back(xRebins_bJetPt_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_ee3j);

  // bJetPt, <4jets
  var_list_label.push_back( "h_bJetPt__lt4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, <4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_lt4j = 8;
  double xRebins_bJetPt_lt4j[nRebins_bJetPt_lt4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_lt4j[nRebins_bJetPt_lt4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_lt4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_lt4j);

  // bJetPt, >=4jets
  var_list_label.push_back( "h_bJetPt__ge4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_bJetPt_ge4j = 8;
  double xRebins_bJetPt_ge4j[nRebins_bJetPt_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_ge4j[nRebins_bJetPt_ge4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_ge4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_ge4j);



  // bJetPt, incl selection
  var_list_label.push_back( "h_bJetPt__inclSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_coarseRebin_incl = 2;
  double xRebins_bJetPt_coarseRebin_incl[nRebins_bJetPt_coarseRebin_incl+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_incl[nRebins_bJetPt_coarseRebin_incl]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_incl);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_incl);

  
  // bJetPt, ==2jets
  var_list_label.push_back( "h_bJetPt__ee2jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_coarseRebin_ee2j = 2;
  double xRebins_bJetPt_coarseRebin_ee2j[nRebins_bJetPt_coarseRebin_ee2j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_ee2j[nRebins_bJetPt_coarseRebin_ee2j]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_ee2j);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_ee2j);

  // bJetPt, ==3jets
  var_list_label.push_back( "h_bJetPt__ee3jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_coarseRebin_ee3j = 2;
  double xRebins_bJetPt_coarseRebin_ee3j[nRebins_bJetPt_coarseRebin_ee3j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_ee3j[nRebins_bJetPt_coarseRebin_ee3j]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_ee3j);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_ee3j);

  // bJetPt, <4jets
  var_list_label.push_back( "h_bJetPt__lt4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, <4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_coarseRebin_lt4j = 2;
  double xRebins_bJetPt_coarseRebin_lt4j[nRebins_bJetPt_coarseRebin_lt4j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_lt4j[nRebins_bJetPt_coarseRebin_lt4j]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_lt4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_lt4j);

  // bJetPt, >=4jets
  var_list_label.push_back( "h_bJetPt__ge4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_bJetPt_coarseRebin_ge4j = 2;
  double xRebins_bJetPt_coarseRebin_ge4j[nRebins_bJetPt_coarseRebin_ge4j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_ge4j[nRebins_bJetPt_coarseRebin_ge4j]{ (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_ge4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_ge4j);



  // bJetPt, modTopness<0.0 selection
  var_list_label.push_back( "h_bJetPt__lt0modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness<0.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt, modTopness>=0.0 selection
  var_list_label.push_back( "h_bJetPt__ge0modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness>=0.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt, modTopness>=10.0 selection
  var_list_label.push_back( "h_bJetPt__ge10modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness>=10.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

   
  
  // bJetPt, modTopness<0.0 selection, fine rebin
  var_list_label.push_back( "h_bJetPt__lt0modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness<0.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_lt0modTop = 8;
  double xRebins_bJetPt_lt0modTop[nRebins_bJetPt_lt0modTop+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_lt0modTop[nRebins_bJetPt_lt0modTop]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_lt0modTop);
  var_rebin_xBins.push_back(xRebins_bJetPt_lt0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_lt0modTop);

  
  // bJetPt, modTopness>=0.0 selection, fine rebin
  var_list_label.push_back( "h_bJetPt__ge0modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness>=0.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_ge0modTop = 8;
  double xRebins_bJetPt_ge0modTop[nRebins_bJetPt_ge0modTop+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_ge0modTop[nRebins_bJetPt_ge0modTop]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_ge0modTop);
  var_rebin_xBins.push_back(xRebins_bJetPt_ge0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_ge0modTop);

  // bJetPt, modTopness>=10.0 selection, fine rebin
  var_list_label.push_back( "h_bJetPt__ge10modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness>=10.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_ge10modTop = 8;
  double xRebins_bJetPt_ge10modTop[nRebins_bJetPt_ge10modTop+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_ge10modTop[nRebins_bJetPt_ge10modTop]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_ge10modTop);
  var_rebin_xBins.push_back(xRebins_bJetPt_ge10modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_ge10modTop);


  // bJetPt, modTopness<0.0 selection, coarse rebin
  var_list_label.push_back( "h_bJetPt__lt0modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness<0.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_coarseRebin_lt0modTop = 2;
  double xRebins_bJetPt_coarseRebin_lt0modTop[nRebins_bJetPt_coarseRebin_lt0modTop+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_lt0modTop[nRebins_bJetPt_coarseRebin_lt0modTop]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_lt0modTop);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_lt0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_lt0modTop);

  
  // bJetPt, modTopness>=0.0 selection, coarse rebin
  var_list_label.push_back( "h_bJetPt__ge0modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness>=0.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_coarseRebin_ge0modTop = 2;
  double xRebins_bJetPt_coarseRebin_ge0modTop[nRebins_bJetPt_coarseRebin_ge0modTop+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_ge0modTop[nRebins_bJetPt_coarseRebin_ge0modTop]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_ge0modTop);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_ge0modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_ge0modTop);

  // bJetPt, modTopness>=10.0 selection, coarse rebin
  var_list_label.push_back( "h_bJetPt__ge10modTopnessSelection" );
  var_list_title.push_back( "lead bJet p_{T}, modTopness>=10.0" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_coarseRebin_ge10modTop = 2;
  double xRebins_bJetPt_coarseRebin_ge10modTop[nRebins_bJetPt_coarseRebin_ge10modTop+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_coarseRebin_ge10modTop[nRebins_bJetPt_coarseRebin_ge10modTop]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_coarseRebin_ge10modTop);
  var_rebin_xBins.push_back(xRebins_bJetPt_coarseRebin_ge10modTop);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_coarseRebin_ge10modTop);


  // bJetPt_150to250met, incl selection
  var_list_label.push_back( "h_bJetPt_150to250met__inclSelection" );
  var_list_title.push_back( "lead bJet p_{T}, nJet>=2, 150<met<250" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt_150to250met, ==2jets
  var_list_label.push_back( "h_bJetPt_150to250met__ee2jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==2 jet, 150<met<250" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt_150to250met, ==3jets
  var_list_label.push_back( "h_bJetPt_150to250met__ee3jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==3 jet, 150<met<250" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt_150to250met, <4jets
  var_list_label.push_back( "h_bJetPt_150to250met__lt4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, <4 jet, 150<met<250" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // bJetPt_150to250met, >=4jets
  var_list_label.push_back( "h_bJetPt_150to250met__ge4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=4 jet, 150<met<250" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // bJetPt, incl selection, met sideband CR
  var_list_label.push_back( "h_bJetPt_150to250met__inclSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_incl = 8;
  double xRebins_bJetPt_150to250met_incl[nRebins_bJetPt_150to250met_incl+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_incl[nRebins_bJetPt_150to250met_incl]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_incl);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_incl);

  
  // bJetPt, ==2jets
  var_list_label.push_back( "h_bJetPt_150to250met__ee2jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_ee2j = 8;
  double xRebins_bJetPt_150to250met_ee2j[nRebins_bJetPt_150to250met_ee2j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_ee2j[nRebins_bJetPt_150to250met_ee2j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_ee2j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_ee2j);

  // bJetPt, ==3jets
  var_list_label.push_back( "h_bJetPt_150to250met__ee3jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_ee3j = 8;
  double xRebins_bJetPt_150to250met_ee3j[nRebins_bJetPt_150to250met_ee3j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_ee3j[nRebins_bJetPt_150to250met_ee3j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_ee3j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_ee3j);

  // bJetPt, <4jets
  var_list_label.push_back( "h_bJetPt_150to250met__lt4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, <4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_lt4j = 8;
  double xRebins_bJetPt_150to250met_lt4j[nRebins_bJetPt_150to250met_lt4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_lt4j[nRebins_bJetPt_150to250met_lt4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_lt4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_lt4j);

  // bJetPt, >=4jets
  var_list_label.push_back( "h_bJetPt_150to250met__ge4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_bJetPt_150to250met_ge4j = 8;
  double xRebins_bJetPt_150to250met_ge4j[nRebins_bJetPt_150to250met_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_ge4j[nRebins_bJetPt_150to250met_ge4j]{   0.5,  0.5,   0.5,   0.5,   0.5,  0.25,   0.25, (1.0/6.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("fineRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_ge4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_ge4j);



  // bJetPt, incl selection
  var_list_label.push_back( "h_bJetPt_150to250met__inclSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_coarseRebin_incl = 2;
  double xRebins_bJetPt_150to250met_coarseRebin_incl[nRebins_bJetPt_150to250met_coarseRebin_incl+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_coarseRebin_incl[nRebins_bJetPt_150to250met_coarseRebin_incl]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_coarseRebin_incl);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_coarseRebin_incl);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_coarseRebin_incl);

  
  // bJetPt, ==2jets
  var_list_label.push_back( "h_bJetPt_150to250met__ee2jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_coarseRebin_ee2j = 2;
  double xRebins_bJetPt_150to250met_coarseRebin_ee2j[nRebins_bJetPt_150to250met_coarseRebin_ee2j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_coarseRebin_ee2j[nRebins_bJetPt_150to250met_coarseRebin_ee2j]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_coarseRebin_ee2j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_coarseRebin_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_coarseRebin_ee2j);

  // bJetPt, ==3jets
  var_list_label.push_back( "h_bJetPt_150to250met__ee3jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_coarseRebin_ee3j = 2;
  double xRebins_bJetPt_150to250met_coarseRebin_ee3j[nRebins_bJetPt_150to250met_coarseRebin_ee3j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_coarseRebin_ee3j[nRebins_bJetPt_150to250met_coarseRebin_ee3j]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_coarseRebin_ee3j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_coarseRebin_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_coarseRebin_ee3j);

  // bJetPt, <4jets
  var_list_label.push_back( "h_bJetPt_150to250met__lt4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, <4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_bJetPt_150to250met_coarseRebin_lt4j = 2;
  double xRebins_bJetPt_150to250met_coarseRebin_lt4j[nRebins_bJetPt_150to250met_coarseRebin_lt4j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_coarseRebin_lt4j[nRebins_bJetPt_150to250met_coarseRebin_lt4j]{   (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_coarseRebin_lt4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_coarseRebin_lt4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_coarseRebin_lt4j);

  // bJetPt, >=4jets
  var_list_label.push_back( "h_bJetPt_150to250met__ge4jSelection" );
  var_list_title.push_back( "lead bJet p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "lead bJet p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  const int nRebins_bJetPt_150to250met_coarseRebin_ge4j = 2;
  double xRebins_bJetPt_150to250met_coarseRebin_ge4j[nRebins_bJetPt_150to250met_coarseRebin_ge4j+1]{ 0.0, 200.0, 600.0 };
  double xRebinsSF_bJetPt_150to250met_coarseRebin_ge4j[nRebins_bJetPt_150to250met_coarseRebin_ge4j]{ (1.0/8.0), (1.0/16.0) };
  var_doRebin.push_back(true);
  var_rebin_labels.push_back("coarseRebin");
  var_rebin_nBins.push_back(nRebins_bJetPt_150to250met_coarseRebin_ge4j);
  var_rebin_xBins.push_back(xRebins_bJetPt_150to250met_coarseRebin_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_bJetPt_150to250met_coarseRebin_ge4j);



  // gen ttbarPt, incl selection
  var_list_label.push_back( "h_gen_ttbarPt__inclSelection" );
  var_list_title.push_back( "Gen t#bar{t} system p_{T}, >=2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // gen ttbarPt, ==2jets
  var_list_label.push_back( "h_gen_ttbarPt__ee2jSelection" );
  var_list_title.push_back( "Gen t#bar{t} system p_{T}, ==2 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // gen ttbarPt, ==3jets
  var_list_label.push_back( "h_gen_ttbarPt__ee3jSelection" );
  var_list_title.push_back( "Gen t#bar{t} system p_{T}, ==3 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // gen ttbarPt, <4jets
  var_list_label.push_back( "h_gen_ttbarPt__lt4jSelection" );
  var_list_title.push_back( "Gen t#bar{t} system p_{T}, <4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // gen ttbarPt, >=4jets
  var_list_label.push_back( "h_gen_ttbarPt__ge4jSelection" );
  var_list_title.push_back( "Gen t#bar{t} system p_{T}, >=4 jets" );
  var_list_xaxis.push_back( "p_{T} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // gen lep2ID, incl selection
  var_list_label.push_back( "h_gen_lep2_id__inclSelection" );
  var_list_title.push_back( "Gen 2nd Lepton pdgid, >=2 jets" );
  var_list_xaxis.push_back( "" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // gen lep2ID, ==2jets
  var_list_label.push_back( "h_gen_lep2_id__ee2jSelection" );
  var_list_title.push_back( "Gen 2nd Lepton pdgid, ==2 jets" );
  //var_list_title.push_back( "Gen 2nd Lepton pdgid, ==2 jet, modTop>6.4" );
  var_list_xaxis.push_back( "" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // gen lep2ID, ==3jets
  var_list_label.push_back( "h_gen_lep2_id__ee3jSelection" );
  var_list_title.push_back( "Gen 2nd Lepton pdgid, ==3 jets" );
  //var_list_title.push_back( "Gen 2nd Lepton pdgid, ==3 jet, mt2w>200" );
  var_list_xaxis.push_back( "" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // gen lep2ID, <4jets
  var_list_label.push_back( "h_gen_lep2_id__lt4jSelection" );
  var_list_title.push_back( "Gen 2nd Lepton pdgid, <4 jets" );
  //var_list_title.push_back( "Gen 2nd Lepton pdgid, >=4 jet, mt2w<200" );
  var_list_xaxis.push_back( "" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // gen lep2ID, >=4jets
  var_list_label.push_back( "h_gen_lep2_id__ge4jSelection" );
  var_list_title.push_back( "Gen 2nd Lepton pdgid, >=4 jets" );
  //var_list_title.push_back( "Gen 2nd Lepton pdgid, >=4 jet, mt2w>200" );
  var_list_xaxis.push_back( "" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_labels.push_back(noRebin_label);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  
    
  //
  // Loop over files and grab histograms
  //
  TString hName = "";
  TString hName_clone = "";
  //TH1F *h_null = new TH1F("","",1,0,1);
  TH1F *h_null = new TH1F("","",7,0.0,7.0);
  TH1F *h_data      = NULL;
  TH1F *h_temp      = NULL;
  TH1F *h_temp_up   = NULL;
  TH1F *h_temp_dn   = NULL;
  TH1F *h_clone     = NULL;
  TH1F *h_clone_up  = NULL;
  TH1F *h_clone_dn  = NULL;
  TH1F *h_clone_unc = NULL;
  TH3D *h3_temp     = NULL;


  for(int iReg=0; iReg<nRegions; iReg++){
  
    for(int iVar=0; iVar<(int)var_list_label.size(); iVar++){
      
      bool isYieldPlot = false;
      std::size_t foundYield = var_list_label[iVar].find("yields");
      if( foundYield!=std::string::npos ) isYieldPlot=true;

      bool isGenPlot = false;
      std::size_t foundGen = var_list_label[iVar].find("_gen_");
      if( foundGen!=std::string::npos ) isGenPlot=true;
      
      std::string cat_title_for_subtitle = "";
      
      // Get Data Data;
      TFile *f_data = NULL;
      if(plotData && !isGenPlot){
	sampleInfo::sampleUtil data_util( sample_data.first );
	genClassyInfo::Util data_genClassy( sample_data.second );
	
	TString f_name = inDir;
	f_name += data_util.label;
	f_name += ".root";
	f_data = new TFile( f_name.Data(), "read" );
	
	hName = var_list_label[iVar];
	hName += "__";
	hName += regionList[iReg];
	hName += "__genClassy_";
	hName += data_genClassy.label;
	hName += "__systematic_";
	hName += sys_nominal.label;
	
	hName_clone = hName;
	hName_clone += "__data";
	
	h_temp = (TH1F*)f_data->Get(hName);
	if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
	
	// Do rebin
	if( var_doRebin[iVar] ){
	  h_data = (TH1F*)h_temp->Rebin( var_rebin_nBins[iVar], hName_clone, var_rebin_xBins[iVar]);
	  if(rescaleBinsAfterRebin){
	    for(int iBin=1; iBin<=(int)h_data->GetNbinsX(); iBin++){
	      h_data->SetBinContent( iBin, h_data->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	      h_data->SetBinError( iBin, h_data->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	    }
	  }
	}
	else{
	  h_data = (TH1F*)h_temp->Clone(hName_clone);
	}
	
      } // end if plotting data
      
      if(isGenPlot) h_data = h_null;

      
      // Backgrounds
      std::vector<TFile*> bkg_files;
      std::pair<TH1F*,TH1F*> bkg_and_unc;
      std::vector< std::pair<TH1F*,TH1F*> > bkg_histos;
      std::vector<std::string> bkg_titles;
      for(int iBkg=0; iBkg<(int)bkgList.size(); iBkg++){
	
	sampleInfo::sampleUtil background( bkgList[iBkg].first );
	genClassyInfo::Util genClassification( bkgList[iBkg].second );
	
	TString f_name = inDir;
	f_name += background.label;
	f_name += ".root";
	TFile *f_bkg = new TFile( f_name.Data(), "read" );
	bkg_files.push_back(f_bkg);
	
	hName = var_list_label[iVar];
	hName += "__";
	hName += regionList[iReg];
	hName += "__genClassy_";
	hName += genClassification.label;
	hName += "__systematic_";
	hName += sys_nominal.label;
	
	hName_clone = hName;
	hName_clone += "__";
	hName_clone += background.label;
	
	h_temp = (TH1F*)f_bkg->Get(hName);
	if(!h_temp){
	  cout << "BAD BKG HISTO: " << hName << endl;
	  cout << "  FROM FILE: " << f_name.Data() << endl;
	}
	
	// Do rebin
	if( var_doRebin[iVar] ){
	  h_clone = (TH1F*)h_temp->Rebin( var_rebin_nBins[iVar], hName_clone, var_rebin_xBins[iVar]);
	  if(rescaleBinsAfterRebin){
	    for(int iBin=1; iBin<=(int)h_clone->GetNbinsX(); iBin++){
	      h_clone->SetBinContent( iBin, h_clone->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	      h_clone->SetBinError( iBin, h_clone->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	    }
	  }
	}
	else{
	  h_clone = (TH1F*)h_temp->Clone(hName_clone);
	}
	
	
	bkg_and_unc.first = h_clone;
	
	h_clone_unc = (TH1F*)h_clone->Clone(hName_clone+"__unc");
	if( (int)sysList[iVar].size()==1 ){
	  bkg_and_unc.second = h_clone_unc;
	}
	else{
	  
	  for(int iSys=1; iSys<(int)sysList[iVar].size(); iSys+=2){
	    
	    // Get Up Variation
	    hName = var_list_label[iVar];
	    hName += "__";
	    hName += regionList[iReg];
	    hName += "__genClassy_";
	    hName += genClassification.label;
	    hName += "__systematic_";
	    hName += sysList[iVar][iSys].label;
	    
	    h_temp_up = (TH1F*)f_bkg->Get(hName);
	    
	    hName_clone = hName;
	    hName_clone += "__";
	    hName_clone += background.label;
	    hName_clone += "__";
	    hName_clone += sysList[iVar][iSys].label;
	    
	    // Do rebin
	    if( var_doRebin[iVar] ){
	      h_clone_up = (TH1F*)h_temp_up->Rebin( var_rebin_nBins[iVar], hName_clone, var_rebin_xBins[iVar]);
	      if(rescaleBinsAfterRebin){
		for(int iBin=1; iBin<=(int)h_clone_up->GetNbinsX(); iBin++){
		  h_clone_up->SetBinContent( iBin, h_clone_up->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
		  h_clone_up->SetBinError( iBin, h_clone_up->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
		}
	      }
	    }
	    else{
	      h_clone_up = (TH1F*)h_temp_up->Clone(hName_clone);
	    }
	    
	    
	    // Get Down Variation
	    hName = var_list_label[iVar];
	    hName += "__";
	    hName += regionList[iReg];
	    hName += "__genClassy_";
	    hName += genClassification.label;
	    hName += "__systematic_";
	    hName += sysList[iVar][iSys+1].label;
	    
	    h_temp_dn = (TH1F*)f_bkg->Get(hName);
	    
	    hName_clone = hName;
	    hName_clone += "__";
	    hName_clone += background.label;
	    hName_clone += "__";
	    hName_clone += sysList[iVar][iSys+1].label;
	    
	    // Do rebin
	    if( var_doRebin[iVar] ){
	      h_clone_dn = (TH1F*)h_temp_dn->Rebin( var_rebin_nBins[iVar], hName_clone, var_rebin_xBins[iVar]);
	      if(rescaleBinsAfterRebin){
		for(int iBin=1; iBin<=(int)h_clone_dn->GetNbinsX(); iBin++){
		  h_clone_dn->SetBinContent( iBin, h_clone_dn->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
		  h_clone_dn->SetBinError( iBin, h_clone_dn->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
		}
	      }
	    }
	    else{
	      h_clone_dn = (TH1F*)h_temp_dn->Clone(hName_clone);
	    }
	    
	    
	    for(int iBin=1; iBin<=(int)h_clone_up->GetNbinsX(); iBin++){
	      double nom_val    = h_clone_unc->GetBinContent(iBin);
	      double nom_err    = h_clone_unc->GetBinError(iBin);
	      double nom_err_sq = pow( nom_err, 2 );
	      
	      double up_val = h_clone_up->GetBinContent(iBin);
	      double dn_val = h_clone_dn->GetBinContent(iBin);
	      
	      double max_diff = fabs(nom_val-up_val);
	      max_diff = std::max( max_diff, fabs(nom_val-dn_val) );
	      
	      nom_err_sq += pow(max_diff,2);
	      nom_err     = sqrt(nom_err_sq);
	      
	      h_clone_unc->SetBinError(iBin,nom_err);
	    } // end loop over bins
	    
	  } // end loop over sys
	  
	  bkg_and_unc.second = h_clone_unc;
	  
	} // end if more than 1 systematic
	
	bkg_histos.push_back(bkg_and_unc);
	
	if(plotByGenDecay) bkg_titles.push_back(genClassification.title);
	else{
	  std::string bkg_title = "";
	  bkg_title += background.title;
	  if( genClassification.id!=genClassyInfo::k_incl ){
	    bkg_title += ", ";
	    bkg_title += genClassification.title;
	  }
	  bkg_titles.push_back(bkg_title);
	}
	
      } // end loop over files
      
      
      // Signal
      std::vector<TFile*> sig_files;
      std::vector<TH1F*> sig_histos;
      std::vector<std::string> sig_titles;
      for(int iSig=0; iSig<(int)sigList.size(); iSig++){
	
	sampleInfo::sampleUtil signal( sigList[iSig].first );
	genClassyInfo::Util genClassification( sigList[iSig].second );
      
	TString f_name = inDir;
	f_name += signal.label;
	f_name += ".root";
	
	TFile *f_sig = new TFile( f_name.Data(), "read" );
	sig_files.push_back(f_sig);
	
	hName = var_list_label[iVar];
	hName += "__";
	hName += regionList[iReg];
	hName += "__genClassy_";
	hName += genClassification.label;
	hName += "__systematic_";
	hName += sys_nominal.label;
	
	if( signal.isSignalScan ){
	  
	  std::vector< std::pair< double, double > > massPtList;
	  if( signal.id==sampleInfo::k_T2tt ) massPtList = T2tt_list;
	  
	  for(int iMassPt=0; iMassPt<(int)massPtList.size(); iMassPt++){
	    
	    int mStop = massPtList[iMassPt].first;
	    int mLSP  = massPtList[iMassPt].second;
	    
	    hName_clone = hName;
	    hName_clone += "__mStop_";
	    hName_clone += mStop;
	    hName_clone += "__mLSP_";
	    hName_clone += mLSP;
	    
	    h3_temp = (TH3D*)f_sig->Get(hName);
	    if(!h3_temp) cout << "BAD SIG HISTO: " << hName << endl;
	    
	    int binX = h3_temp->GetXaxis()->FindBin( mStop );
	    int binY = h3_temp->GetYaxis()->FindBin( mLSP );
	    h3_temp->GetXaxis()->SetRange( binX, binX );
	    h3_temp->GetYaxis()->SetRange( binY, binY );
	    h3_temp->GetZaxis()->SetRange( 1, h3_temp->GetNbinsZ() );
	    TH1D *h1_temp = (TH1D*)h3_temp->Project3D( "z" );
	    
	    if(!h1_temp) cout << "BAD SIG HISTO: " << hName << endl;
	    
	    // Do rebin
	    if( var_doRebin[iVar] ){
	      h_clone = (TH1F*)h_temp->Rebin( var_rebin_nBins[iVar], hName_clone, var_rebin_xBins[iVar]);
	      if(rescaleBinsAfterRebin){
		for(int iBin=1; iBin<=(int)h_clone->GetNbinsX(); iBin++){
		  h_clone->SetBinContent( iBin, h_clone->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
		  h_clone->SetBinError( iBin, h_clone->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
		}
	      }
	    }
	    else{
	      h_clone = (TH1F*)h_temp->Clone(hName_clone);
	    }
	    sig_histos.push_back(h_clone);
	    
	    TString sig_title_temp = "";
	    sig_title_temp += signal.title;
	    sig_title_temp += " ";
	    sig_title_temp += mStop;
	    sig_title_temp += ", ";
	    sig_title_temp += mLSP;
	    std::string sig_title = sig_title_temp.Data();
	    sig_titles.push_back( sig_title );
	    
	  } // end loop over mass points
	  
	} // end if signal scan
	else{
	  
	  hName_clone = hName;
	  hName_clone += "__";
	  hName_clone += signal.label;
	  
	  h_temp = (TH1F*)f_sig->Get(hName);
	  if(!h_temp) cout << "BAD SIG HISTO: " << hName << endl;
	  h_clone = (TH1F*)h_temp->Clone(hName_clone);
	  sig_histos.push_back(h_clone);
	  sig_titles.push_back(signal.title);
	}
	
      } // end loop over signal samples
      
      
      // Option String, Log Scale Plot
      std::string options = "";
      
      options += "--outputName ";
      options += outDir;
      options += "data_MC_plot";
      if(plotByGenDecay) options  += "__byGenDecayMode__";
      else                options += "__byProductionMode__";
      options += var_list_label[iVar];
      options += "__";
      options += regionList[iReg];
      options += "__logScale";
      if( var_doRebin[iVar] ) options += Form("__%s", var_rebin_labels[iVar].Data());
      options += outExt;
      options += "  ";
      
      options += "--xAxisLabel ";
      options += var_list_xaxis[iVar];
      options += "  ";
      
      options += "--noXaxisUnit  ";
      
      options += "--legendRight -0.12  ";
      options += "--legendUp 0.05  ";
      
      options += "--energy 13  ";
      
      options += "--lumiPrec 1  ";
      
      options += "--lumi ";
      options += Form("%.1f  ", lumi);
      
      options += "--preserveBackgroundOrder  ";
      options += "--preserveSignalOrder  ";
      
      options += "--errHistAtBottom  ";
      
      options += "--outOfFrame ";
      
      options += "--type Preliminary  ";
      //options += "--type Simulation  ";
      
      if(isYieldPlot) options += "--noOverflow ";
      
      dataMCplotMaker(h_data, bkg_histos, bkg_titles, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_titles, colors);
      
      
      // Option String, Linear Scale Plot
      options = "";
      
      options += "--outputName ";
      options += outDir;
      options += "data_MC_plot";
      if(plotByGenDecay) options  += "__byGenDecayMode__";
      else                options += "__byProductionMode__";
      options += var_list_label[iVar];
      options += "__";
      options += regionList[iReg];
      options += "__linScale";
      if( var_doRebin[iVar] ) options += Form("__%s", var_rebin_labels[iVar].Data());
      options += outExt;
      options += "  ";
      
      options += "--xAxisLabel ";
      options += var_list_xaxis[iVar];
      options += "  ";
      
      options += "--noXaxisUnit ";
      
      options += "--legendRight -0.12  ";
      options += "--legendUp 0.05  ";
      
      options += "--energy 13  ";
      
      options += "--lumiPrec 1  ";
      
      options += "--lumi ";
      options += Form("%.1f  ", lumi);
      
      options += "--preserveBackgroundOrder  ";
      options += "--preserveSignalOrder  ";
      
      options += "--errHistAtBottom  ";
      
      options += "--outOfFrame ";
      
      options += "--isLinear ";
      
      options += "--yTitleOffset -0.3  ";
      
      options += "--type Preliminary  ";
      //options += "--type Simulation  ";

      if(isYieldPlot) options += "--noOverflow ";
      
      dataMCplotMaker(h_data, bkg_histos, bkg_titles, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_titles, colors);
      
      
      
      //
      // Clean up
      //
      if(plotData && !isGenPlot){
	f_data->Close();
	f_data->~TFile();
      }
      
      for(int iBkg=0; iBkg<(int)bkg_files.size(); iBkg++){
	bkg_files[iBkg]->Close();
	bkg_files[iBkg]->~TFile();
      }
      
      for(int iSig=0; iSig<(int)sig_files.size(); iSig++){
	sig_files[iSig]->Close();
	sig_files[iSig]->~TFile();
      }
      
            
    } // end loop over vars
    
  } // end loop over regions  
    
  return;

}
