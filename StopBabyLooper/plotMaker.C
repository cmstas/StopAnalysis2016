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
  
  TString inDir  = "Output/Histos/";
  TString outDir = "Output/Plots/";

  TString outExt = ".pdf";
  
  //double lumi    = 12.9; // 2016 ICHEp
  double lumi    = 29.53; // 2016 Current
  
  double sig_SF  = 1.0;

  
  //
  // Signal and Control Regions
  //
  std::vector<std::string> regionList;
  regionList.push_back("SR");
  regionList.push_back("CR0b");
  regionList.push_back("CR2l");


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
  std::vector<int> var_rebin_nBins;
  std::vector<double*> var_rebin_xBins;
  std::vector<double*> var_rebin_xBinsSF;

  bool noRebin = false;
  int noRebin_nBins = 1;
  double noRebin_xBins[2]{0.0,0.0}; // entries = nBins+1
  double noRebin_xBinsSF[1]{1.0};   // SFs to keep bins Events/width



  // Plot Yields
  
  // Signal Region
  var_list_label.push_back( "h_yields_SR_ICHEP__SR" );
  var_list_title.push_back( "Signal Region Yields" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot nJets

  // Signal Region
  var_list_label.push_back( "h_nJets__SR" );
  var_list_title.push_back( "Number of Jets, Signal Region" );
  var_list_xaxis.push_back( "nJets" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  // Signal Region, Rebinned
  var_list_label.push_back( "h_nJets__SR" );
  var_list_title.push_back( "Number of Jets, Signal Region" );
  var_list_xaxis.push_back( "nJets" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  const int nRebins_nJets_SR = 5;
  double xRebins_nJets_SR[nRebins_nJets_SR+1]{ -0.5, 0.5, 1.5, 2.5, 3.5, 10.5 };
  double xRebinsSF_nJets_SR[nRebins_nJets_SR]{    1.0, 1.0, 1.0, 1.0, (1.0/7.0) };
  var_doRebin.push_back(true);
  var_rebin_nBins.push_back(nRebins_nJets_SR);
  var_rebin_xBins.push_back(xRebins_nJets_SR);
  var_rebin_xBinsSF.push_back(xRebinsSF_nJets_SR);


  

  /*
  // Plot Modified topness
  var_list_label.push_back( "modTopness" );
  var_list_title.push_back( "modified topness" );
  var_list_xaxis.push_back( "modified topness" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot MT2W
  var_list_label.push_back( "mt2w" );
  var_list_title.push_back( "MT2W" );
  var_list_xaxis.push_back( "MT2W [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot MET
  var_list_label.push_back( "met" );
  var_list_title.push_back( "E_{T}^{miss}" );
  var_list_xaxis.push_back( "E_{T}^{miss} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot MET, rebinned, 2 jets
  var_list_label.push_back( "met" );
  var_list_title.push_back( "E_{T}^{miss}" );
  var_list_xaxis.push_back( "E_{T}^{miss} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();
  
  //const int nRebins_met = 8;
  //double xRebins_met[nRebins_met+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 800.0 };
  //double xRebinsSF_met[nRebins_met]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.714  };
  const int nRebins_met_ee2j = 8;
  double xRebins_met_ee2j[nRebins_met_ee2j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 800.0 };
  double xRebinsSF_met_ee2j[nRebins_met_ee2j]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.0714  };
  var_doRebin.push_back(true);
  var_rebin_nBins.push_back(nRebins_met_ee2j);
  var_rebin_xBins.push_back(xRebins_met_ee2j);
  var_rebin_xBinsSF.push_back(xRebinsSF_met_ee2j);


  // Plot MET, rebinned, 3 jets
  var_list_label.push_back( "met" );
  var_list_title.push_back( "E_{T}^{miss}" );
  var_list_xaxis.push_back( "E_{T}^{miss} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  //const int nRebins_met = 8;
  //double xRebins_met[nRebins_met+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 800.0 };
  //double xRebinsSF_met[nRebins_met]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.714  };
  const int nRebins_met_ee3j = 8;
  double xRebins_met_ee3j[nRebins_met_ee3j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 800.0 };
  double xRebinsSF_met_ee3j[nRebins_met_ee3j]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.0714  };
  var_doRebin.push_back(true);
  var_rebin_nBins.push_back(nRebins_met_ee3j);
  var_rebin_xBins.push_back(xRebins_met_ee3j);
  var_rebin_xBinsSF.push_back(xRebinsSF_met_ee3j);

  
  // Plot MET, rebinned, >=4 jets, mt2w<200
  var_list_label.push_back( "met" );
  var_list_title.push_back( "E_{T}^{miss}" );
  var_list_xaxis.push_back( "E_{T}^{miss} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  //const int nRebins_met = 8;
  //double xRebins_met[nRebins_met+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 800.0 };
  //double xRebinsSF_met[nRebins_met]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.714  };
  const int nRebins_met_ge4j = 8;
  double xRebins_met_ge4j[nRebins_met_ge4j+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 800.0 };
  double xRebinsSF_met_ge4j[nRebins_met_ge4j]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.0714  };
  var_doRebin.push_back(true);
  var_rebin_nBins.push_back(nRebins_met_ge4j);
  var_rebin_xBins.push_back(xRebins_met_ge4j);
  var_rebin_xBinsSF.push_back(xRebinsSF_met_ge4j);


  // Plot MET, rebinned, mt2w>200
  var_list_label.push_back( "met" );
  var_list_title.push_back( "E_{T}^{miss}" );
  var_list_xaxis.push_back( "E_{T}^{miss} [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  //catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  //const int nRebins_met = 8;
  //double xRebins_met[nRebins_met+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 800.0 };
  //double xRebinsSF_met[nRebins_met]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.714  };
  const int nRebins_met_ge4j_ge200mt2w = 9;
  double xRebins_met_ge4j_ge200mt2w[nRebins_met_ge4j_ge200mt2w+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 550.0, 800.0 };
  double xRebinsSF_met_ge4j_ge200mt2w[nRebins_met_ge4j_ge200mt2w]{   0.5,   0.5,   0.5,   0.5,   0.5,   0.25,  0.25,  0.25,  0.1  };
  var_doRebin.push_back(true);
  var_rebin_nBins.push_back(nRebins_met_ge4j_ge200mt2w);
  var_rebin_xBins.push_back(xRebins_met_ge4j_ge200mt2w);
  var_rebin_xBinsSF.push_back(xRebinsSF_met_ge4j_ge200mt2w);


  // Plot MT
  var_list_label.push_back( "mt" );
  var_list_title.push_back( "MT" );
  var_list_xaxis.push_back( "MT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);

  
  // Plot jet1 pT
  var_list_label.push_back( "jet1_pt" );
  var_list_title.push_back( "Leading Jet pT" );
  var_list_xaxis.push_back( "jet pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot jet2 pT
  var_list_label.push_back( "jet2_pt" );
  var_list_title.push_back( "Trailing Jet pT" );
  var_list_xaxis.push_back( "jet pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);



  // Plot jet pT
  var_list_label.push_back( "jet_pt" );
  var_list_title.push_back( "Jet pT" );
  var_list_xaxis.push_back( "jet pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);



  // Plot jet pT
  var_list_label.push_back( "jet_pt_notJ1J2" );
  var_list_title.push_back( "Jet pT, excluding 2 leading pT jets" );
  var_list_xaxis.push_back( "jet pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot lep1,2,b,b pT
  var_list_label.push_back( "lep1lep2bb_pt" );
  var_list_title.push_back( "lep1,2,b,b system pT" );
  var_list_xaxis.push_back( "pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot lep1,2,b,b pT, rebinned
  var_list_label.push_back( "lep1lep2bb_pt" );
  var_list_title.push_back( "lep1,2,b,b system pT" );
  var_list_xaxis.push_back( "pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  const int nRebins_lep12bbPt = 8;
  double xRebins_lep12bbPt[nRebins_lep12bbPt+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_lep12bbPt[nRebins_lep12bbPt]{   1.0,   1.0,   1.0,   1.0,   1.0,   0.5,  0.5,  0.33333  };
  var_doRebin.push_back(true);
  var_rebin_nBins.push_back(nRebins_lep12bbPt);
  var_rebin_xBins.push_back(xRebins_lep12bbPt);
  var_rebin_xBinsSF.push_back(xRebinsSF_lep12bbPt);


  // Plot lep1,2,b,b,met pT
  var_list_label.push_back( "lep1lep2bbMet_pt" );
  var_list_title.push_back( "lep1,2,b,b,Met system pT" );
  var_list_xaxis.push_back( "pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  var_doRebin.push_back(noRebin);
  var_rebin_nBins.push_back(noRebin_nBins);
  var_rebin_xBins.push_back(noRebin_xBins);
  var_rebin_xBinsSF.push_back(noRebin_xBinsSF);


  // Plot lep1,2,b,b,met pT
  var_list_label.push_back( "lep1lep2bbMet_pt" );
  var_list_title.push_back( "lep1,2,b,b,Met system pT" );
  var_list_xaxis.push_back( "pT [GeV]" );
  
  sysListPerPlot.push_back( sysInfo::Util(sysInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();

  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets) );
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();

  const int nRebins_lep12bbMetPt = 8;
  double xRebins_lep12bbMetPt[nRebins_lep12bbMetPt+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF_lep12bbMetPt[nRebins_lep12bbMetPt]{   1.0,   1.0,   1.0,   1.0,   1.0,   0.5,  0.5,  0.33333  };
  var_doRebin.push_back(true);
  var_rebin_nBins.push_back(nRebins_lep12bbMetPt);
  var_rebin_xBins.push_back(xRebins_lep12bbMetPt);
  var_rebin_xBinsSF.push_back(xRebinsSF_lep12bbMetPt);
  */


  
  //
  // Loop over files and grab histograms
  //
  TString hName = "";
  TString hName_clone = "";
  
  TH1F *h_data      = new TH1F("","",1,0,1);
  TH1F *h_temp      = NULL;
  TH1F *h_temp_up   = NULL;
  TH1F *h_temp_dn   = NULL;
  TH1F *h_clone     = NULL;
  TH1F *h_clone_up  = NULL;
  TH1F *h_clone_dn  = NULL;
  TH1F *h_clone_unc = NULL;
  TH3D *h3_temp     = NULL;

  
  for(int iVar=0; iVar<(int)var_list_label.size(); iVar++){
    
    bool isYieldPlot = false;
    std::size_t foundYield = var_list_label[iVar].find("yields");
    if( foundYield!=std::string::npos ) isYieldPlot=true;

    std::string cat_title_for_subtitle = "";
    
    // Get Data Data;
    TFile *f_data = NULL;
    if(plotData){
      sampleInfo::sampleUtil data_util( sample_data.first );
      genClassyInfo::Util data_genClassy( sample_data.second );
      
      TString f_name = inDir;
      f_name += data_util.label;
      f_name += ".root";
      f_data = new TFile( f_name.Data(), "read" );
	
      hName = var_list_label[iVar];
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
	for(int iBin=1; iBin<=(int)h_data->GetNbinsX(); iBin++){
	  h_data->SetBinContent( iBin, h_data->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	  h_data->SetBinError( iBin, h_data->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	}
      }
      else{
	h_data = (TH1F*)h_temp->Clone(hName_clone);
      }
	  
    } // end if plotting data


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
	for(int iBin=1; iBin<=(int)h_clone->GetNbinsX(); iBin++){
	  h_clone->SetBinContent( iBin, h_clone->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	  h_clone->SetBinError( iBin, h_clone->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
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
	  
	for(int iSys=0; iSys<(int)sysList[iVar].size(); iSys+=2){
	    
	  // Get Up Variation
	  hName = var_list_label[iVar];
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
	    for(int iBin=1; iBin<=(int)h_clone_up->GetNbinsX(); iBin++){
	      h_clone_up->SetBinContent( iBin, h_clone_up->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	      h_clone_up->SetBinError( iBin, h_clone_up->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	    }
	  }
	  else{
	    h_clone_up = (TH1F*)h_temp_up->Clone(hName_clone);
	  }
	      

	  // Get Down Variation
	  hName = var_list_label[iVar];
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
	    for(int iBin=1; iBin<=(int)h_clone_dn->GetNbinsX(); iBin++){
	      h_clone_dn->SetBinContent( iBin, h_clone_dn->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	      h_clone_dn->SetBinError( iBin, h_clone_dn->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
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
	      
	    nom_err_sq += max_diff;
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
	    for(int iBin=1; iBin<=(int)h_clone->GetNbinsX(); iBin++){
	      h_clone->SetBinContent( iBin, h_clone->GetBinContent(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
	      h_clone->SetBinError( iBin, h_clone->GetBinError(iBin)*var_rebin_xBinsSF[iVar][iBin-1] );
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
    options += "__logScale";
    if( var_doRebin[iVar] ) options += "__rebinned";
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
      

    dataMCplotMaker(h_data, bkg_histos, bkg_titles, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_titles, colors);
      
      
    // Option String, Linear Scale Plot
    options = "";
      
    options += "--outputName ";
    options += outDir;
    options += "data_MC_plot";
    if(plotByGenDecay) options  += "__byGenDecayMode__";
    else                options += "__byProductionMode__";
    options += var_list_label[iVar];
    options += "__linScale";
    if( var_doRebin[iVar] ) options += "__rebinned";
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
      
    dataMCplotMaker(h_data, bkg_histos, bkg_titles, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_titles, colors);
      
      
      
    //
    // Clean up
    //
    if(plotData){
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
      
    //f_dummy->Close();
      
   
  } // end loop over vars
      


  return;
}
