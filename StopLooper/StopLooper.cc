// C++
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>
#include <stdexcept>

// ROOT
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TBenchmark.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TF1.h"

// Tools
#include "../CORE/Tools/utils.h"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/badEventFilter.h"

#include "SR.h"
#include "sigSelections.h"
#include "StopLooper.h"
#include "PlotUtilities.h"

using namespace std;
using namespace duplicate_removal;

class SR;

const bool verbose = false;
// turn on to apply weights to central value
const bool applyWeights = false;
// turn on to apply btag sf to central value
const bool applyBtagSF = true; // default true
// turn on to apply lepton sf to central value - take from babies
const bool applyLeptonSFfromBabies = false;
// turn on to apply lepton sf to central value - reread from files
const bool applyLeptonSFfromFiles = true; // default true
// turn on to apply lepton sf to central value also for 0L SR. values chosen by options above
const bool applyLeptonSFtoSR = false;
// turn on to apply reweighting to ttbar based on top pt
const bool applyTopPtReweight = false;
// add weights to correct for photon trigger efficiencies
const bool applyPhotonTriggerWeights = false; //not needed since we apply trigger safe H/E cut
// add weights to correct for dilepton trigger efficiencies
const bool applyDileptonTriggerWeights = true;
// use 2016 ICHEP ISR weights based on nisrMatch, signal and ttbar only
const bool applyISRWeights = true;
// turn on to enable plots of MT2 with systematic variations applied. will only do variations for applied weights
const bool doSystVariationPlots = true;
// turn on to apply Nvtx reweighting to MC
const bool doNvtxReweight = false;
// turn on to apply nTrueInt reweighting to MC
const bool doNTrueIntReweight = true;
// turn on to apply json file to data
const bool applyJSON = true;
// ignore scale1fb to run over test samples
const bool ignoreScale1fb = false;
// to test synchronization with the standard Analysis
const bool synchronizing = false;
// not running the standard regions to speed up
const bool fasterRuntime = true;


void StopLooper::SetSignalRegions() {

  CRVec = getStopControlRegions();

  if (verbose) {
    cout << "CRVec.size = " << CRVec.size() << ", including the following:" << endl;
    for (auto it = CRVec.begin(); it != CRVec.end(); ++it)
      cout << it-CRVec.begin() << "  "<< it->GetName() << endl;
  }

  for (unsigned int i = 0; i < CRVec.size(); i++) {
    vector<string> vars = CRVec.at(i).GetListOfVariables();
    TDirectory * dir = (TDirectory*) outfile_->Get(("sr"+CRVec.at(i).GetName()).c_str());
    if (dir == 0) dir = outfile_->mkdir(("sr"+CRVec.at(i).GetName()).c_str());
    dir->cd();
    for (unsigned int j = 0; j < vars.size(); j++) {
      plot1D("h_"+vars.at(j)+"_"+"LOW",  1, CRVec.at(i).GetLowerBound(vars.at(j)), CRVec.at(i).histMap, "", 1, 0, 2);
      plot1D("h_"+vars.at(j)+"_"+"HI",   1, CRVec.at(i).GetUpperBound(vars.at(j)), CRVec.at(i).histMap, "", 1, 0, 2);
    }
  }
}


void StopLooper::looper(TChain* chain, string sample, string output_dir) {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // gROOT->cd();
  TString output_name = Form("%s/%s.root",output_dir.c_str(),sample.c_str());
  cout << "[looper] creating output file: " << output_name << endl;  outfile_ = new TFile(output_name.Data(),"RECREATE") ; 

  // full 2016 dataset json, 36.26/fb:
  const char* json_file = "../jsons/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_snt.txt";
  // to reproduce ICHEP, 12.9/fb:
  if (applyJSON) {
    cout << "Loading json file: " << json_file << endl;
    set_goodrun_file(json_file);
  }
  
  int nDuplicates = 0;
  int nEvents = chain->GetEntries();
  unsigned int nEventsChain = nEvents;
  cout << "[MT2Looper::loop] running on " << nEventsChain << " events" << endl;
  unsigned int nEventsTotal = 0;

  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {


  } // end of file loop

  cout << "[looper] processed " << nEventsTotal << " events" << endl;
  if ( nEventsChain != nEventsTotal )
    std::cout << "WARNING: number of events from files is not equal to total number of events" << std::endl;


  outfile_->Write();
  outfile_->Close();

  bmark->Stop("benchmark");

  cout << endl;
  cout << nEventsTotal << " Events Processed, where " << nDuplicates << " duplicates were skipped" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f s", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f s", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  return;
}
