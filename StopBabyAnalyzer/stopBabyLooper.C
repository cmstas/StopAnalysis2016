// Usage:
// > root -b scanAllChains.C

// C++
#include <iostream>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLorentzVector.h"
#include "TString.h"

// stop_1l_babyAnalyzer
#include "stop_1l_babyAnalyzer.cc"

// histoHelper
#include "histoHelper.h"

using namespace std;
using namespace stop_1l;


//
// Main
//

int stopBabyLooper( TChain* chain, TString output_file="histos.root", bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  //
  // Intro
  //
  cout << "=========================================" << endl;
  cout << "  WELCOME TO STOP BABY ANALYZER! " << endl;
  cout << endl;
  cout << "     Output written to: " << output_file << endl;
  cout << "=========================================" << endl;

  //
  // Benchmark
  //
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  //
  // Output File
  //
  TFile *out_file = new TFile(output_file, "recreate");

  //
  // Declare histoHelper
  //
  histoHelper histos;

  //
  // Check if this is ttbar 1l or 2l sample
  //
  bool is_ttbar_0l = false;
  bool is_ttbar_1l = false;
  bool is_ttbar_2l = false;
  if( output_file.Contains("ttbar_0l") ) is_ttbar_0l = true;
  if( output_file.Contains("ttbar_1l") ) is_ttbar_1l = true;
  if( output_file.Contains("ttbar_2l") ) is_ttbar_2l = true;
     
  //
  // Event Counters
  //
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;

  //
  // Stop 1 Lepton Selection Cutflow
  //
  bool doCut_nVtx = true;
  unsigned int nEvents_pass_nVtx = 0;
  int cut_nVtx = 1;

  bool doCut_nGoodLep = true;
  unsigned int nEvents_pass_nGoodLep = 0;
  int cut_nGoodLep = 1;

  bool doCut_nSelLep = true;
  unsigned int nEvents_pass_nSelLep = 0;
  unsigned int nEvents_pass_nSelLep_isMu = 0;
  unsigned int nEvents_pass_nSelLep_isEle = 0;
  int cut_nSelLep = 1;
  
  bool doCut_trackVeto = true;
  unsigned int nEvents_pass_trackVeto = 0;

  bool doCut_tauVeto = true;
  unsigned int nEvents_pass_tauVeto = 0;

  bool doCut_nJets = true;
  unsigned int nEvents_pass_nJets = 0;
  int cut_nJets = 4;

  bool doCut_nBJets = true; 
  unsigned int nEvents_pass_nBJets = 0;
  int cut_nBJets = 1;

  bool doCut_met = true;
  unsigned int nEvents_pass_met = 0;
  double cut_met = 100.0;

  bool doCut_mt = true;
  unsigned int nEvents_pass_mtCut = 0;
  double cut_mt = 120.0;

  bool doCut_minDPhi = true;
  unsigned int nEvents_pass_minDPhi = 0;
  double cut_minDPhi = 0.8;

  bool doCut_chi2 = true;
  unsigned int nEvents_pass_chi2 = 0;
  double cut_chi2 = 5.0;

  unsigned int nEvents_pass_baseline_isMu = 0;
  unsigned int nEvents_pass_baseline_isEle = 0;
    

  //
  // Grab list of files
  //
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //
  // File Loop
  //
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    //
    // Get File Content
    //
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("t");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    babyAnalyzer.Init(tree);

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

      double wgt = 1.0;
      wgt = scale1fb();

      double lumi = 10.0;
      wgt *= lumi;

      //
      // Progress
      //
      stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );
      
      //
      // Determine type of ttbar event
      //
      int nGenLeptons = gen_nfromtmus_() + gen_nfromtels_() + gen_nfromttaus_();
      if( is_ttbar_0l && nGenLeptons!=0 ) continue;
      if( is_ttbar_1l && nGenLeptons!=1 ) continue;
      if( is_ttbar_2l && nGenLeptons!=2 ) continue;

      //
      // Fill Histos for baby Selection
      //
      histos.fillHistos( 0, wgt, ngoodjets(), ngoodbtags() );

      //
      // Pre-Selection
      //
      if( doCut_nVtx && nvtxs()<cut_nVtx ) continue;
      nEvents_pass_nVtx++;

      if( doCut_nGoodLep && ngoodleps()!=cut_nGoodLep ) continue;
      nEvents_pass_nGoodLep++;

      int nSelLeptons = 0;
      bool lep1IsSel = false;
      if( doCut_nSelLep ){
	
	if( lep1_is_mu() ){
	  if( lep1_pt()>30.0 &&
	      fabs(lep1_eta())<2.1 &&
	      fabs(lep1_d0())<0.02 &&
	      fabs(lep1_dz())<0.1 &&
	      lep1_miniRelIsoDB()<0.10 ){
	    nSelLeptons++;
	    nEvents_pass_nSelLep_isMu++;
	    lep1IsSel=true;
	  } // end if good muon
	}
       
	if( lep1_is_el() ){
	  if( lep1_pt()>40.0 &&
	      fabs(lep1_eta())<2.1 &&
	      lep1_is_phys14_medium_noIso() &&
	      lep1_miniRelIsoDB()<0.10 ){
	    nSelLeptons++;
	    nEvents_pass_nSelLep_isEle++;
	    lep1IsSel=true;
	  } // end if good electron
	}
	
	if( lep2_is_mu() ){
	  if( lep2_pt()>30.0 &&
	      fabs(lep2_eta())<2.1 &&
	      fabs(lep2_d0())<0.02 &&
	      fabs(lep2_dz())<0.1 &&
	      lep2_miniRelIsoDB()<0.10 ){
	    nSelLeptons++;
	    nEvents_pass_nSelLep_isMu++;
	  } // end if good muon
	}
       
	if( lep2_is_el() ){
	  if( lep2_pt()>40.0 &&
	      fabs(lep2_eta())<2.1 &&
	      lep2_is_phys14_medium_noIso() &&
	      lep2_miniRelIsoDB()<0.10 ){
	    nSelLeptons++;
	    nEvents_pass_nSelLep_isEle++;
	  } // end if good electron
	}
	
	if( nSelLeptons != cut_nSelLep ) continue;
      }
      nEvents_pass_nSelLep++;

      
      if( doCut_trackVeto && !PassTrackVeto() ) continue;
      nEvents_pass_trackVeto++;
      
      if( doCut_tauVeto && !PassTauVeto() ) continue;
      nEvents_pass_tauVeto++;

      
      int nSelJets = 0;
      int nTagJets = 0;
      double btag_wp = 0.814; // 8TeV = 0.679
      std::vector<int> selJet_index;
      std::vector<int> tagJet_index;
      if( doCut_nJets ){
	for( int iJet=0; iJet<(int)ngoodjets(); iJet++){
	  
	  if( ak4pfjets_p4()[iJet].Pt()>30.0 &&
	      fabs(ak4pfjets_p4()[iJet].Eta())<2.4 &&
	      ak4pfjets_loose_pfid()[iJet] ){
	    nSelJets++;
	    selJet_index.push_back(iJet);
	    
	    if( ak4pfjets_CSV()[iJet] > btag_wp ){
	      nTagJets++;
	      tagJet_index.push_back(iJet);
	    } // end if tagged jet

	  } // end if selected jet					 
	} // end loop over good jets

	if( nSelJets<cut_nJets ) continue;
      }
      nEvents_pass_nJets++;
   
      if( doCut_nBJets && nTagJets<cut_nBJets ) continue;
      nEvents_pass_nBJets++;
      

      //
      // Fill Histos for preSelection
      //
      histos.fillHistos( 1, wgt, nSelJets, nTagJets );
      

      //
      // Additional Selection for Signal Regions
      //
      if( doCut_met && pfmet()<=cut_met ) continue;
      nEvents_pass_met++;
      histos.fillHistos( 2, wgt, nSelJets, nTagJets );
      
      
      if( doCut_mt && mt_met_lep()<=cut_mt ) continue;
      nEvents_pass_mtCut++;
      histos.fillHistos( 3, wgt, nSelJets, nTagJets );

      
      if( doCut_minDPhi && mindphi_met_j1_j2()<=cut_minDPhi ) continue;
      nEvents_pass_minDPhi++;
      histos.fillHistos( 4, wgt, nSelJets, nTagJets );
       
      
      if( doCut_chi2 && chi2()>=cut_chi2 ) continue;
      nEvents_pass_chi2++;
      histos.fillHistos( 5, wgt, nSelJets, nTagJets );

      //
      // This completes the baseline selection
      //
      histos.fillHistos( 6, wgt, nSelJets, nTagJets );

      if( lep1IsSel ){
	if( lep1_is_mu() ) nEvents_pass_baseline_isMu++;
	if( lep1_is_el() ) nEvents_pass_baseline_isEle++;
      }
      else{
	if( lep2_is_mu() ) nEvents_pass_baseline_isMu++;
	if( lep2_is_el() ) nEvents_pass_baseline_isEle++;
      }

      //
      // Determine Signal Region Category
      //
      std::vector<int> qualified_cats;
      if( pfmet()>150 ) qualified_cats.push_back(7);
      if( pfmet()>200 ) qualified_cats.push_back(8);
      if( pfmet()>250 ) qualified_cats.push_back(9);
      if( pfmet()>300 ) qualified_cats.push_back(10);

      if( pfmet()>150 && MT2W()>200.0 ) qualified_cats.push_back(11);
      if( pfmet()>200 && MT2W()>200.0 ) qualified_cats.push_back(12);
      if( pfmet()>250 && MT2W()>200.0 ) qualified_cats.push_back(13);
      if( pfmet()>300 && MT2W()>200.0 ) qualified_cats.push_back(14);
      
      for(int i=0; i<(int)qualified_cats.size(); i++){
	histos.fillHistos( qualified_cats[i], wgt, nSelJets, nTagJets );
      } // end loop over qualified cats
    
    } // end loop over events
  
    //
    // Clean Up
    //
    delete tree;
    file->Close();
    delete file;
  }
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  //
  // Close Output File
  //
  out_file->Write();
  out_file->Close();
  
  //
  // Print Selection Cutflow
  //
  cout << endl;
  cout << "=====================================================" << endl;
  cout << "Selection Cutflow" << endl;
  cout << "    nEvents Processed              = " << nEventsChain << endl;
  cout << "    nEvents Pass >1 Vertex         = " << nEvents_pass_nVtx << endl;
  cout << "    nEvents Pass 1 Good Lepton     = " << nEvents_pass_nGoodLep << endl;
  cout << "    nEvents Pass 1 Selected Lepton = " << nEvents_pass_nSelLep << endl;
  cout << "                     nMuons        = " << nEvents_pass_nSelLep_isMu << endl;
  cout << "                     nElectrons    = " << nEvents_pass_nSelLep_isEle << endl;
  cout << "    nEvents Pass Track Veto        = " << nEvents_pass_trackVeto << endl;
  cout << "    nEvents Pass Tau Veto          = " << nEvents_pass_tauVeto << endl;
  cout << "    nEvents Pass >=4 Selected Jets = " << nEvents_pass_nJets << endl;
  cout << "    nEvents Pass >=1 BTagged Jets  = " << nEvents_pass_nBJets << endl;
  cout << "    nEvents Pass Met>100.0         = " << nEvents_pass_met << endl;
  cout << "    nEvents Pass MT>120.0          = " << nEvents_pass_mtCut << endl;
  cout << "    nEvents Pass minDeltaPhi>0.8   = " << nEvents_pass_minDPhi << endl;
  cout << "    nEvents Pass Chi2<5.0          = " << nEvents_pass_chi2 << endl;
  cout << "                    nMuons         = " << nEvents_pass_baseline_isMu << endl;
  cout << "                    nElectrons     = " << nEvents_pass_baseline_isEle << endl;
  cout << "=====================================================" << endl;

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
 
  //
  // Return!
  //
  return 0;

}
