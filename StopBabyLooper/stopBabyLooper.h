#ifndef STOPBABYLOOPER_H
#define STOPBABYLOOPER_H


//////////////
//          //
// INCLUDES //
//          //
//////////////

// C++
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

// ROOT
#include "TROOT.h"
#include "Riostream.h"
#include "TCollection.h"
#include "TKey.h"
#include "TClass.h"
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TTreeCache.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TPie.h"

// sntCORE
#include "Tools/dorky/dorky.h"
#include "Tools/goodrun.h"

// stopCORE
#include "../StopCORE/stop_1l_babyAnalyzer.h"
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/selectionInfo.h"
#include "../StopCORE/sysInfo.h"
#include "../StopCORE/analyzer.h"


////////////////
//            //
// Namespaces //
//            //
////////////////

using namespace std;
using namespace tas;
using namespace stop_1l;


/////////////////////
//                 //
// Utility Classes //
//                 //
/////////////////////

// Merging Struct
struct mergeUtil{
  
  sampleInfo::ID id;
  bool useZeroed;
  bool useRescaled;

  mergeUtil():useZeroed(false),useRescaled(false){}
  mergeUtil(sampleInfo::ID ID):id(ID),useZeroed(false),useRescaled(false){}
  mergeUtil(sampleInfo::ID ID, bool use_zeroed, bool use_rescale):id(ID),useZeroed(use_zeroed),useRescaled(use_rescale){}
  
  void reset(){
    useZeroed=false;
    useRescaled=false;
  }
};

// TableMaking Struct
struct yieldHelper{
  std::string histName;
  std::string tex;
  int binNumber;
};

// Background Estimate Class
class bkgEstUtil{

public:
  TString outName_base;
  TString hName_base;

	TString name_SR;
	TString name_CR;

  bool forceOneTF;
  bool useFractionInCR;
  
  vector<int> SR_bins;
  vector<int> CR_bins;

  vector<bool> use_mc;
  vector<double> err_mc;
  
  vector<TString> regionName;
  vector<TString> regionName_short;
  vector<TString> binName;

	vector<TString> names_SR;
	vector<TString> names_CR;

  bkgEstUtil(){};
  ~bkgEstUtil(){};
};


///////////////
//           //
// Functions //
//           //
///////////////

// Looper 
int stopBabyLooper ();
int looper( sampleInfo::ID sample, std::vector<analyzer*> analyzers, int nEvents=-1, bool readFast=true );
void fillHistos( TH1D *histo, vector<int> passCats, double wgt );
void fillHistosScan( TH3D *histo, vector<int> passCats, int mStop, int mLSP, double wgt );

// Scale sample output post-looper
void scaleSamples(std::string f_input_dir, std::string f_output_dir);

// Merge samples from components 
void mergeStopBabies( std::string f_input_dir, std::string f_output_dir, bool use_zeroed_samp=true );
int mergeEm( sampleInfo::ID target, std::vector< mergeUtil > sources, std::string f_input_dir, std::string f_output_dir );

// Table making, for merged and component samples
void tableMaker_allInputs( std::string f_input_dir="Output/Histos/", std::string f_out_name_base="Output/Tables/yields_allInputs", bool useZeroedAMCNLO=true );

// Zero out negative yields
int zeroOutNegativeYields(std::string f_input_dir="Output/Histos/");

// Table making, for final samples
void tableMaker_summedInputs( std::string f_input_dir="Output/Histos/", std::string f_out_name_base="Output/Tables/yields_summedInputs", bool useZeroedAMCNLO=true );

// Table making, for systematic uncertainties
void calcErrors();
void calcThis(std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sampleList );

// Plot making
void plotMaker( bool plotByGenDecay=true );

// Pie chart making
int pieCharts( std::string f_input_dir="Output/Histos/", std::string f_out_name_base="Output/Plots/pieChart_yields", bool useZeroedAMCNLO=true );

// Background Estimates, lost lepton
int bkgEstimate_diLepton();
void printLatexHeader( FILE *file );

// Background Estimates, one lep from W
int bkgEstimate_1lepFromW();

// Background Estimates, one lep from Top
int bkgEstimate_1lepFromTop();

// Background Estimates, ZtoNuNu
int bkgEstimate_ZtoNuNu();


#endif
