#ifndef STOPBABYLOOPER__CR2l_BULKTTBAR_H
#define STOPBABYLOOPER__CR2l_BULKTTBAR_H


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
#include "TGaxis.h"
#include "TStyle.h"

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

  bool forceOneTF;
  bool useFractionInCR;
  
  vector<int> SR_bins;
  vector<int> CR_bins;

  vector<bool> use_mc;
  vector<double> err_mc;
  
  vector<TString> regionName;
  vector<TString> regionName_short;
  vector<TString> binName;

  bkgEstUtil(){};
  ~bkgEstUtil(){};
};


///////////////
//           //
// Functions //
//           //
///////////////

// Looper 
int stopBabyLooper__CR2l_bulkTTbar();
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

// diLepton trigger efficiency plotting
int diLepTriggerEfficiency_analyzer();

// ttbar system pT scalce factor analyzer
int ttbarSystemPt_analyzer();

// ttbar system pT plotter
void ttbarSystemPt_plotMaker( bool plotByGenDecay=true, bool scaleToData=true );

#endif
