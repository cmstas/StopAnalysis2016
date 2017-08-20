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

// CORE
#include "../CORE/Tools/utils.h"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/badEventFilter.h"

// Stop CORE
#include "../StopCORE/stop_1l_babyAnalyzer.h"
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/selectionInfo.h"
#include "../StopCORE/sysInfo.h"

#include "SR.h"
#include "StopSelections.h"
#include "StopLooper.h"
#include "PlotUtilities.h"

using namespace std;
using namespace stop_1l;
using namespace selectionInfo;

class SR;
extern stop_1l_babyAnalyzer babyAnalyzer;

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
const bool applyjson = true;
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

  for (auto& cr : CRVec) {
    vector<string> vars = cr.GetListOfVariables();
    TDirectory * dir = (TDirectory*) outfile_->Get((cr.GetName() + "/ranges").c_str());
    if (dir == 0) dir = outfile_->mkdir((cr.GetName() + "/ranges").c_str());
    dir->cd("ranges");
    for (auto& var : vars) {
      plot1D("h_"+var+"_"+"LOW",  1, cr.GetLowerBound(var), cr.histMap, "", 1, 0, 2);
      plot1D("h_"+var+"_"+"HI",   1, cr.GetUpperBound(var), cr.histMap, "", 1, 0, 2);
    }
  }
}


void StopLooper::looper(TChain* chain, string sample, string output_dir) {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // gROOT->cd();
  TString output_name = Form("%s/%s.root",output_dir.c_str(),sample.c_str());
  cout << "[StopLooper::looper] creating output file: " << output_name << endl;  outfile_ = new TFile(output_name.Data(),"RECREATE") ; 

  outfile_ = new TFile(output_name.Data(), "RECREATE") ; 

  // full 2016 dataset json, 36.26/fb:
  // const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt";
  const char* json_file = "../StopCORE/inputs/json_files/Cert_294927-300575_13TeV_PromptReco_Collisions17_JSON_snt.txt";  // 2017 dataset json 
  if (applyjson) {
    cout << "Loading json file: " << json_file << endl;
    set_goodrun_file(json_file);
  }
  
  // sampleInfo::sampleUtil sample( sampleInfo::ID::k_single_mu );
  TFile dummy("dummy.root", "RECREATE");
  SetSignalRegions();

  int nDuplicates = 0;
  int nEvents = chain->GetEntries();
  unsigned int nEventsChain = nEvents;
  cout << "[StopLooper::looper] running on " << nEventsChain << " events" << endl;
  unsigned int nEventsTotal = 0;
  unsigned int nPassedTotal = 0;

  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    TFile file( currentFile->GetTitle(), "READ" );
    TTree *tree = (TTree*) file.Get("t");
    TTreeCache::SetLearnEntries(10);
    tree->SetCacheSize(128*1024*1024);
    babyAnalyzer.Init(tree);

    dummy.cd();
    // Loop over Events in current file
    if (nEventsTotal >= nEventsChain) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for (unsigned int event = 0; event < nEventsTree; ++event) {
    // for (unsigned int event = 0; event < 3; ++event) {

      // Read Tree
      if (nEventsTotal >= nEventsChain) continue;
      tree->LoadTree(event);
      babyAnalyzer.GetEntry(event);
      ++nEventsTotal;

      // if (sample.isData) {
      if (true) {
        if ( applyjson && !goodrun(run(), ls()) ) continue;
	duplicate_removal::DorkyEventIdentifier id(run(), evt(), ls());
	if ( is_duplicate(id) ) continue;
      }

      // apply filters
      // if (!filt_globalTightHalo2016()) continue; // problematic
      if ( !filt_globalsupertighthalo2016() ) continue;
      if ( !filt_hbhenoise() ) continue;
      if ( !filt_hbheisonoise() )   continue;
      if ( !filt_ecaltp() ) continue;
      if ( !filt_eebadsc() ) continue;
      if ( !filt_goodvtx() ) continue;
      if ( firstGoodVtxIdx() == -1 ) continue;
      if ( !filt_badMuonFilter() ) continue;
      if ( !filt_badChargedCandidateFilter() ) continue;
      
      map<string,float> vals;

      vals["mt"] = MT2W();
      vals["met"] = pfmet();
      vals["mlb"] = 1; // just here for demonstration purpose for now.
      vals["tmod"] = (topnessMod() < 0)? 0 : 1;
      vals["nlep"] = 1; // just here for demonstration purpose for now.
      vals["njet"] = ak4pfjets_p4().size();
      vals["nbjet"] = 1; // just here for demonstration purpose for now.

      string suf = "";
      float evtweight_ = 1.0; // just here for demonstration purpose for now.


      ++nPassedTotal;

      for (auto& cr : CRVec) {
        if ( cr.PassesSelection(vals) ) {
          // cout << "Passed selections!: " << cr.GetName() << endl;
          plot1D("h_met"+suf, pfmet(), evtweight_, cr.histMap, ";E_{T}^{miss} [GeV]", 150, 0, 1500);
        }
      }
    }

    delete tree;
    file.Close();
  } // end of file loop

  cout << "[StopLooper::looper] processed  " << nEventsTotal << " events" << endl;
  if ( nEventsChain != nEventsTotal )
    std::cout << "WARNING: number of events from files is not equal to total number of events" << std::endl;

  outfile_->cd();

  for (auto& cr : CRVec) {
    TDirectory * dir = (TDirectory*) outfile_->Get(cr.GetName().c_str());
    if (dir == 0) dir = outfile_->mkdir(cr.GetName().c_str()); // shouldn't happen
    dir->cd();
    for (auto& h : cr.histMap) {
      if (h.first.find("HI") != string::npos || h.first.find("LOW") != string::npos) continue;
      h.second->Write();
    }
  }

  outfile_->Write();
  outfile_->Close();

  bmark->Stop("benchmark");

  cout << endl;
  cout << nEventsTotal << " Events Processed, where " << nDuplicates << " duplicates were skipped, and ";
  cout << nPassedTotal << " Events passed all selections." << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f s", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f s", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  return;
}
