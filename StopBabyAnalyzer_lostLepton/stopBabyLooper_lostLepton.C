// Usage:
// > root -b scanAllChains.C

// C++
#include <iostream>
#include <vector>
#include <map>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"

// stop_1l_babyAnalyzer
#include "stop_1l_babyAnalyzer.cc"

using namespace std;
using namespace stop_1l;


//
// Main
//

int stopBabyLooper_lostLepton( TChain* chain, TString output_file="histos.root", bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

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
  // Check if this is ttbar 1l or 2l sample
  //
  bool is_0l = false;
  bool is_1l = false;
  bool is_2l = false;
  if( output_file.Contains("_0l") ) is_0l = true;
  if( output_file.Contains("_1l") ) is_1l = true;
  if( output_file.Contains("_2l") ) is_2l = true;
     
  //
  // Event Counters
  //
  
  // Total events processed
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;

  // Stop 1 Lepton Selection Cutflow
  bool doCut_nVtx = true;
  unsigned int nEvents_pass_nVtx = 0;
  double nEvents_pass_nVtx_wgt = 0.0;
  int cut_nVtx = 1;

  bool doCut_nGoodLep = true;
  unsigned int nEvents_pass_nGoodLep = 0;
  double nEvents_pass_nGoodLep_wgt = 0.0;
  int cut_nGoodLep = 1;

  bool doCut_nSelLep = true;
  unsigned int nEvents_pass_nSelLep = 0;
  double nEvents_pass_nSelLep_wgt = 0.0;
  int cut_nSelLep = 1;

  bool doCut_trackVeto = false;
  unsigned int nEvents_pass_trackVeto = 0;
  double nEvents_pass_trackVeto_wgt = 0.0;

  bool doCut_tauVeto = true;
  unsigned int nEvents_pass_tauVeto = 0;
  double nEvents_pass_tauVeto_wgt = 0.0;

  bool doCut_nJets = true;
  unsigned int nEvents_pass_nJets = 0;
  double nEvents_pass_nJets_wgt = 0.0;
  int cut_nJets = 4;

  bool doCut_nBJets = true; 
  unsigned int nEvents_pass_nBJets = 0;
  double nEvents_pass_nBJets_wgt = 0.0;
  int cut_nBJets = 1;

  bool doCut_met = true;
  unsigned int nEvents_pass_met = 0;
  double nEvents_pass_met_wgt = 0.0;
  double cut_met = 200.0;

  bool doCut_mt = true;
  unsigned int nEvents_pass_mtCut = 0;
  double nEvents_pass_mtCut_wgt = 0.0;
  double cut_mt = 120.0;

  bool doCut_minDPhi = true;
  unsigned int nEvents_pass_minDPhi = 0;
  double nEvents_pass_minDPhi_wgt = 0.0;
  double cut_minDPhi = 0.8;

  bool doCut_chi2 = true;
  unsigned int nEvents_pass_chi2 = 0;
  double nEvents_pass_chi2_wgt = 0.0;
  double cut_chi2 = 5.0;

  unsigned int nEvents_pass_baseline = 0;
  double nEvents_pass_baseline_wgt = 0.0;
  

  // Signal regions
  double nEvents_pass_met150_wgt = 0;
  double nEvents_pass_met200_wgt = 0;
  double nEvents_pass_met250_wgt = 0;
  double nEvents_pass_met300_wgt = 0;
  
  double nEvents_pass_met150_mt2w200_wgt = 0;
  double nEvents_pass_met200_mt2w200_wgt = 0;
  double nEvents_pass_met250_mt2w200_wgt = 0;
  double nEvents_pass_met300_mt2w200_wgt = 0;


  // Track isolation veto optimization
  std::vector<TString> trkIsoVeto_name;
  std::map<TString, int> trkIsoVeto_nEvents_passCut;
  int nElements=0;
  for(double pfMuIso=0.1; pfMuIso<=0.5; pfMuIso+=0.1){
    for(int pfMuQVeto=0; pfMuQVeto<=1; pfMuQVeto++){
      for(double pfElIso=0.1; pfElIso<=0.5; pfElIso+=0.1){
	for(int pfElQVeto=0; pfElQVeto<=1; pfElQVeto++){
	  for(int pfAbsIso=0; pfAbsIso<=1; pfAbsIso++){
	    for(double pfHadIso=0.1; pfHadIso<=0.4; pfHadIso+=0.1){

	      TString vetoName = "";
	      vetoName+= "pfMuIso=";
	      vetoName+=Form("%.1f",pfMuIso);
	      vetoName+= ", ";
	      vetoName+= "pfMuQVeto=";
	      vetoName+=Form("%d",pfMuQVeto);
	      vetoName+= ", ";
	      vetoName+= "pfElIso=";
	      vetoName+=Form("%.1f",pfElIso);
	      vetoName+= ", ";
	      vetoName+= "pfElQVeto=";
	      vetoName+=Form("%d",pfElQVeto);
	      vetoName+= ", ";
	      vetoName+= "pfAbsIso=";
	      vetoName+=Form("%d",pfAbsIso);
	      vetoName+= ", ";
	      vetoName+= "pfHadIso=";
	      vetoName+=Form("%.1f",pfHadIso);
	      
	      trkIsoVeto_nEvents_passCut[ vetoName ] = 0;
	      nElements++;
	    }
	  }
	}
      }
    }
  }

  unsigned int passTrackIso_veto = 0;
  double passTrackIsoVeto_wgt = 0.0;
  
  unsigned int passTrackIso_veto_nMinus1_el = 0;
  double passTrackIso_veto_nMinus1_el_wgt = 0.0;

  unsigned int passTrackIso_veto_nMinus1_mu = 0;
  double passTrackIso_veto_nMinus1_mu_wgt = 0.0;
  
  unsigned int passTrackIso_veto_nMinus1_had = 0;
  double passTrackIso_veto_nMinus1_had_wgt = 0.0;

  unsigned int passTrackIso_veto_optimized = 0;
  double passTrackIso_veto_optimized_wgt = 0.0;
 
  

  //
  // Declare Histo Pointers
  //
  TH1D *h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso;
  TH1D *h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso;
  TH1D *h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso;
  
  TH1D *h_isoTrack_isEl_pt;
  TH1D *h_isoTrack_isMu_pt;
  TH1D *h_isoTrack_isHad_pt;
  
  TH1D *h_isoTrack_isEl_relTrkIso;
  TH1D *h_isoTrack_isMu_relTrkIso;
  TH1D *h_isoTrack_isHad_relTrkIso;
  
  TH1D *h_isoTrack_isEl_ptGT60_absIso;
  TH1D *h_isoTrack_isMu_ptGT30_absIso;
  TH1D *h_isoTrack_isHad_ptGT60_absIso;
  

  TH1D *h_genLeptonFromTop_id;

  TH2D *h_genEl_pt_vs_eta;
  TH2D *h_genMu_pt_vs_eta;
  TH2D *h_genHadTau_1prong_pt_vs_eta;
  TH2D *h_genHadTau_1prong_daughter_pt_vs_eta;
  TH2D *h_genHadTau_3prong_pt_vs_eta;

  TH2D *h_genEl_goodPtEta_pt_vs_eta;
  TH2D *h_genMu_goodPtEta_pt_vs_eta;
  TH2D *h_genHadTau_1prong_goodPtEta_pt_vs_eta;
  TH2D *h_genHadTau_1prong_daughter_goodPtEta_pt_vs_eta;
  TH2D *h_genHadTau_3prong_goodPtEta_pt_vs_eta;
  
  TH1D *h_minDR_pfEl_genEl;
  TH2D *h_genEl_pt_vs_eta_matchedTo_pfEl;
  TH1D *h_minDR_pfHad_genEl_notMatchedToPfEl;
  TH2D *h_genEl_notMatchedToPfEl_pt_vs_eta_matchedTo_pfHad;
  
  TH1D *h_minDR_pfMu_genMu;
  TH2D *h_genMu_pt_vs_eta_matchedTo_pfMu;
  TH1D *h_minDR_pfHad_genMu_notMatchedToPfMu;
  TH2D *h_genMu_notMatchedToPfMu_pt_vs_eta_matchedTo_pfHad;
  
  TH1D *h_minDR_pfHad_genHadTau_1prong;
  TH2D *h_genHadTau_1prong_pt_vs_eta_matchedTo_pfHad;
  
  TH1D *h_minDR_pfHad_genHadTau_1prong_daughter;
  TH2D *h_genHadTau_1prong_daughter_pt_vs_eta_matchedTo_pfHad;
  
  TH1D *h_minDR_pfHad_genHadTau_3prong;
  TH2D *h_genHadTau_3prong_pt_vs_eta_matchedTo_pfHad;
  

  TH1D *h_nGenLeptons_fromTop;
  TH1D *h_nFound_gen_ttbarLostLeptons_notMatchedToSelLep;
  
  TH1D *h_dR_selLep_genLep;
  TH2D *h_minDR_genElMatchedToSelEl_pfEl__vs__allOtherPfCand;
  TH2D *h_minDR_genMuMatchedToSelMu_pfMu__vs__allOtherPfCand;


  TH1D *h_lostLepton_id;
  
  TH2D *h_lostLepton_pt_vs_eta_el;
  TH2D *h_lostLepton_pt_vs_eta_mu;
  TH2D *h_lostLepton_pt_vs_eta_hadTau_1prong;
  TH2D *h_lostLepton_pt_vs_eta_hadTau_3prong;

  TH2D *h_lostLepton_pt_vs_eta_goodPtEta_el;
  TH2D *h_lostLepton_pt_vs_eta_goodPtEta_mu;
  TH2D *h_lostLepton_pt_vs_eta_goodPtEta_hadTau_1prong;
  TH2D *h_lostLepton_pt_vs_eta_goodPtEta_hadTau_3prong;

  
  TH1D *h_minDR_pfEl_genLostEl;
  TH1D *h_minDR_pfHad_genLostEl_noPfElMatch;
  TH1D *h_minDR_pfCand_genLostEl;
  
  TH1D *h_minDR_pfMu_genLostMu;
  TH1D *h_minDR_pfHad_genLostMu_noPfMuMatch;
  TH1D *h_minDR_pfCand_genLostMu;
  
  TH1D *h_minDR_pfHad_genLostHadTau_1prong;
  TH1D *h_minDR_pfCand_genLostHadTau_1prong;
  
  TH1D *h_minDR_pfHad_genLostHadTau_3prong;
  TH1D *h_minDR_pfCand_genLostLep_hadTau_3prong;
 
  TH2D *h_genLostEl_matchedTo_pfEl_pt_vs_eta;
  TH2D *h_genLostMu_matchedTo_pfMu_pt_vs_eta;
  TH2D *h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_1prong;
  TH2D *h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_3prong;

  TH2D *h_pfEl_matchedTo_genLostEl_pt_vs_eta;  
  TH2D *h_pfMu_matchedTo_genLostMu_pt_vs_eta;
  TH2D *h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_1prong;
  TH2D *h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_3prong;

  TH2D *h_genLostEl_unMatchedTo_pfEl_pt_vs_eta;
  TH2D *h_genLostMu_unMatchedTo_pfMu_pt_vs_eta;
  TH2D *h_genLostHadTau_1prong_unMatchedTo_pfHad_pt_vs_eta;
  TH2D *h_genLostHadTau_3prong_unMatchedTo_pfHad_pt_vs_eta;

  TH2D *h_genLostEl_matchedTo_pfCand_pt_vs_eta;
  TH2D *h_genLostMu_matchedTo_pfCand_pt_vs_eta;
  TH2D *h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_1prong;
  TH2D *h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_3prong;

  TH2D *h_pfCand_matchedTo_genLostEl_pt_vs_eta; 
  TH2D *h_pfCand_matchedTo_genLostMu_pt_vs_eta;
  TH2D *h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_1prong;
  TH2D *h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_3prong;

  TH1D *h_relTrackIso_pfEl_matchedTo_genLostEl;
  TH1D *h_relTrackIso_pfLep_matchedTo_genLostLep_mu;
  TH1D *h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_1prong;
  TH1D *h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_3prong;

  TH1D *h_relTrackIso_pfHad_genLostEl_noPfElMatch;
  TH1D *h_relTrackIso_pfHad_genLostMu_noPfMuMatch;

  TH2D *h_relTrackIso_vs_pT_pfMu_matchedTo_genLostMu;
  TH2D *h_relTrackIso_vs_pT_pfEl_matchedTo_genLostEl;
  TH2D *h_relTrackIso_vs_pT_pfHad_matchedTo_genLostHadTau_1prong;

  
  //
  // Bin info
  //
  double eps = 0.00001;

  int nBins_pt = 200;
  double pt_min = 0.0;
  double pt_max = 200.0;

  int nBins_eta = 100;
  double eta_min = 0.0;
  double eta_max = 5.0;

  int nBins_dr = 100;
  double dr_min = 0.0;
  double dr_max = 1.0;

  int nBins_relIso = 40;
  double relIso_min = 0.0;
  double relIso_max = 2.0;

  int nBins_absIso = 50;
  double absIso_min = 0.0;
  double absIso_max = 20.0;


  //
  // Histo Constructors
  //
  h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso = new TH1D("h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso", "pfEl, pt>5, 0.0 < iso < 0.6", 60, 0.0, 0.6);
  h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso = new TH1D("h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso", "pfMu, pt>5, 0.0 < iso < 0.6", 60, 0.0, 0.6);
  h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso = new TH1D("h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso", "pfHad, pt>5, 0.0 < iso < 0.6", 60, 0.0, 0.6);
  
  h_isoTrack_isEl_ptGT60_absIso = new TH1D("h_isoTrack_isEl_ptGT60_absIso", "pfEl, pt>60.0, abs iso", nBins_absIso, absIso_min, absIso_max+eps);
  h_isoTrack_isMu_ptGT30_absIso = new TH1D("h_isoTrack_isMu_ptGT30_absIso", "pfMu, pt>30.0, abs iso", nBins_absIso, absIso_min, absIso_max+eps);
  h_isoTrack_isHad_ptGT60_absIso = new TH1D("h_isoTrack_isHad_ptGT60_absIso", "pfHad, pt>60.0, abs iso", nBins_absIso, absIso_min, absIso_max+eps);
    
  h_isoTrack_isEl_pt = new TH1D("h_isoTrack_isEl_pt", "iso track, pfEl, pT; pT", nBins_pt, pt_min, pt_max+eps);
  h_isoTrack_isMu_pt = new TH1D("h_isoTrack_isMu_pt", "iso track, pfMu, pT; pT", nBins_pt, pt_min, pt_max+eps);
  h_isoTrack_isHad_pt = new TH1D("h_isoTrack_isHad_pt", "iso track, pfHad, pT; pT", nBins_pt, pt_min, pt_max+eps);

  h_isoTrack_isEl_relTrkIso = new TH1D("h_isoTrack_isEl_relTrkIso", "iso track, pfEl, relTrackIso; relTrackIso", 20, 0.0, 0.2);
  h_isoTrack_isMu_relTrkIso = new TH1D("h_isoTrack_isMu_relTrkIso", "iso track, pMul, relTrackIso; relTrackIso", 20, 0.0, 0.2);
  h_isoTrack_isHad_relTrkIso = new TH1D("h_isoTrack_isHad_relTrkIso", "iso track, pfHad, relTrackIso; relTrackIso", 20, 0.0, 0.2);
  

  h_genLeptonFromTop_id = new TH1D("h_genLeptonFromTop_id", "gen lepton from top ID", 7, 0, 7);
  h_genLeptonFromTop_id->GetXaxis()->SetBinLabel(1, "ele");
  h_genLeptonFromTop_id->GetXaxis()->SetBinLabel(2, "mu");
  h_genLeptonFromTop_id->GetXaxis()->SetBinLabel(3, "lep tau, ele");
  h_genLeptonFromTop_id->GetXaxis()->SetBinLabel(4, "lep tau, mu");
  h_genLeptonFromTop_id->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
  h_genLeptonFromTop_id->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
  h_genLeptonFromTop_id->GetXaxis()->SetBinLabel(7, "\"other\" tau");
  
  h_genEl_pt_vs_eta = new TH2D("h_genEl_pt_vs_eta", "gen Electron from top, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genMu_pt_vs_eta = new TH2D("h_genMu_pt_vs_eta", "gen Muon from top, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genHadTau_1prong_pt_vs_eta = new TH2D("h_genHadTau_1prong_pt_vs_eta", "gen 1 prong hadronic tau from top, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genHadTau_1prong_daughter_pt_vs_eta = new TH2D("h_genHadTau_1prong_daughter_pt_vs_eta", "gen 1 prong hadronic tau from top, daughter, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genHadTau_3prong_pt_vs_eta = new TH2D("h_genHadTau_3prong_pt_vs_eta", "gen 3 prong hadronic tau from top, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);

  h_genEl_goodPtEta_pt_vs_eta = new TH2D("h_genEl_goodPtEta_pt_vs_eta", "gen Electron from top, pT vs #eta, pT>5.0 && |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genMu_goodPtEta_pt_vs_eta = new TH2D("h_genMu_goodPtEta_pt_vs_eta", "gen Muon from top, pT vs #eta, pT>5.0 && |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genHadTau_1prong_goodPtEta_pt_vs_eta = new TH2D("h_genHadTau_1prong_goodPtEta_pt_vs_eta", "gen 1 prong hadronic tau from top, pT vs #eta, pT>5.0 && |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genHadTau_1prong_daughter_goodPtEta_pt_vs_eta = new TH2D("h_genHadTau_1prong_daughter_goodPtEta_pt_vs_eta", "gen 1 prong hadronic tau from top, daughter, pT vs #eta, pT>5.0 && |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genHadTau_3prong_goodPtEta_pt_vs_eta = new TH2D("h_genHadTau_3prong_goodPtEta_pt_vs_eta", "gen 3 prong hadronic tau from top, pT vs #et, pT>5.0 && |#eta|<2.4a", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
 

  h_minDR_pfEl_genEl = new TH1D("h_minDR_pfEl_genEl", "min#DeltaR(genEl from Top, pfEl)", nBins_dr, dr_min, dr_max+eps);
  h_genEl_pt_vs_eta_matchedToPfEl = new TH2D("h_genEl_pt_vs_eta_matchedToPfEl", "gen Electron, matched to pfEl, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_minDR_pfHad_genEl_notMatchedToPfEl = new TH1D("h_minDR_pfHad_genEl_notMatchedToPfEl", "min#DeltaR(genEl from Top, pfHadron), when genEl not #DeltaR matched to pfEl", nBins_dr, dr_min, dr_max+eps);
  h_genEl_notMatchedToPfEl_pt_vs_eta_matchedToPfHad = new TH2D("h_genEl_notMatchedToPfE_lpt_vs_eta_matchedToPfHad", "gen Electron, matched to pfHad, when not matched to a pfEl, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  
  h_minDR_pfMu_genMu = new TH1D("h_minDR_pfMu_genMu", "min#DeltaR(genMu from Top, pfMu)", nBins_dr, dr_min, dr_max+eps);
  h_genMu_pt_vs_eta_matchedToPfMu = new TH2D("h_genMu_pt_vs_eta_matchedToPfMu", "gen Muon, matched to pfMu, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_minDR_pfHad_genMu_notMatchedToPfMu = new TH1D("h_minDR_pfHad_genMu_notMatchedToPfMu", "min#DeltaR(genMu from Top, pfHadron), when genMu not #DeltaR matched to pfMu", nBins_dr, dr_min, dr_max+eps);
  h_genMu_notMatchedToPfMu_pt_vs_eta_matchedToPfHad = new TH2D("h_genMu_notMatchedToPfE_lpt_vs_eta_matchedToPfHad", "gen Muon, matched to pfHad, when not matched to a pfMu, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  
  h_minDR_pfHad_genHadTau_1prong = new TH1D("h_minDR_pfHad_genHadTau_1prong", "min#DeltaR(genHadTau 1 prong, from Top, pfHad)", nBins_dr, dr_min, dr_max+eps);
  h_genHadTau_1prong_pt_vs_eta_matchedTo_pfHad = new TH2D("h_genHadTau_1prong_pt_vs_eta_matchedToPfHad", "gen 1 prong hadronic tau, matched to pfHad, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  
  h_minDR_pfHad_genHadTau_1prong_daughter = new TH1D("h_minDR_pfHad_genHadTau_1prong_daughter", "min#DeltaR(genHadTau 1 prong daughter, from Top, pfHad)", nBins_dr, dr_min, dr_max+eps);
  h_genHadTau_1prong_daughter_pt_vs_eta_matchedTo_pfHad = new TH2D("h_genHadTau_1prong_daughter_pt_vs_eta_matchedToPfHad", "gen 1 prong hadronic tau daughter, matched to pfHad, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  
  h_minDR_pfHad_genHadTau_3prong = new TH1D("h_minDR_pfHad_genHadTau_3prong", "min#DeltaR(genHadTau 3 prong, from Top, pfHad)", nBins_dr, dr_min, dr_max+eps);
  h_genHadTau_3prong_pt_vs_eta_matchedTo_pfHad = new TH2D("h_genHadTau_3prong_pt_vs_eta_matchedToPfHad", "gen 3 prong hadronic tau, matched to pfHad, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  

 
  
  h_nGenLeptons_fromTop = new TH1D("h_nGenLeptons_fromTop", "nGenLeptons from Top", 5, 0, 5);
  h_nFound_gen_ttbarLostLeptons_notMatchedToSelLep = new TH1D("h_nFound_gen_ttbarLostLeptons_notMatchedToSelLep", "found N gen ttbar leptons, not matched to the selected reco lepton", 10, 0, 10);
  
  h_dR_selLep_genLep = new TH1D("h_dR_selLep_genLep", "#DeltaR(gen,reco) selected lepton", nBins_dr, dr_min, dr_max+eps);
  h_minDR_genElMatchedToSelEl_pfEl__vs__allOtherPfCand = new TH2D("h_minDR_genElMatchedToSelEl_pfEl__vs__allOtherPfCand", "#DeltaR(pfEl Matched to GenEl Matched to selEl) vs #DeltaR(pfCand, genEl Matched to SelEl)", nBins_dr, dr_min, dr_max+eps, nBins_dr, dr_min, dr_max+eps);
  h_minDR_genMuMatchedToSelMu_pfMu__vs__allOtherPfCand = new TH2D("h_minDR_genMuMatchedToSelMu_pfMu__vs__allOtherPfCand", "#DeltaR(pfMu Matched to GenMu Matched to selMu) vs #DeltaR(pfCand, genMu Matched to SelMu)", nBins_dr, dr_min, dr_max+eps, nBins_dr, dr_min, dr_max+eps);;

  

  h_lostLepton_id = new TH1D("h_lostLepton_id", "lost lepton ID", 7, 0, 7);
  h_lostLepton_id->GetXaxis()->SetBinLabel(1, "ele");
  h_lostLepton_id->GetXaxis()->SetBinLabel(2, "mu");
  h_lostLepton_id->GetXaxis()->SetBinLabel(3, "lep tau, ele");
  h_lostLepton_id->GetXaxis()->SetBinLabel(4, "lep tau, mu");
  h_lostLepton_id->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
  h_lostLepton_id->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
  h_lostLepton_id->GetXaxis()->SetBinLabel(7, "\"other\" tau");
 

  h_lostLepton_pt_vs_eta_el = new TH2D("h_lostLepton_pt_vs_eta_el", "lost lepton, pT vs #eta, electrons", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_lostLepton_pt_vs_eta_mu = new TH2D("h_lostLepton_pt_vs_eta_mu", "lost lepton, pT vs #eta, muons", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_lostLepton_pt_vs_eta_hadTau_1prong = new TH2D("h_lostLepton_pt_vs_eta_hadTau_1prong", "lost lepton, pT vs #eta, 1 prong Hadronic Taus", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_lostLepton_pt_vs_eta_hadTau_3prong = new TH2D("h_lostLepton_pt_vs_eta_hadTau_3prong", "lost lepton, pT vs #eta, 3 prong Hadronic Taus", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);

  
  h_lostLepton_pt_vs_eta_goodPtEta_el = new TH2D("h_lostLepton_pt_vs_eta_goodPtEta_el", "lost electron, pT vs #eta, pT>5.0, |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_lostLepton_pt_vs_eta_goodPtEta_mu = new TH2D("h_lostLepton_pt_vs_eta_goodPtEta_mu", "lost muon, pT vs #eta, pT>5.0, |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_lostLepton_pt_vs_eta_goodPtEta_hadTau_1prong = new TH2D("h_lostLepton_pt_vs_eta_goodPtEta_hadTau_1prong", "lost 1-prong hadronic tau, pT vs #eta, pT>5.0, |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_lostLepton_pt_vs_eta_goodPtEta_hadTau_3prong = new TH2D("h_lostLepton_pt_vs_eta_goodPtEta_hadTau_3prong", "lost 3-prong hadornic tau, pT vs #eta, pT>5.0, |#eta|<2.4", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);

  
  h_minDR_pfEl_genLostEl = new TH1D("h_minDR_pfEl_genLostEl", "min#DeltaR(pfEl, genLostElectron)", nBins_dr, dr_min, dr_max+eps);
  h_minDR_pfMu_genLostMu = new TH1D("h_minDR_pfMu_genLostMu", "min#DeltaR(pfMu, genLostMuon)", nBins_dr, dr_min, dr_max+eps);
  h_minDR_pfHad_genLostHadTau_1prong = new TH1D("h_minDR_pfHad_genLostHadTau_1prong", "min#DeltaR(pfHad, 1 prong genLostHadTau)", nBins_dr, dr_min, dr_max+eps);
  h_minDR_pfHad_genLostHadTau_3prong = new TH1D("h_minDR_pfHad_genLostHadTau_3prong", "min#DeltaR(pfHad, 3 prong genLostHadTau)", nBins_dr, dr_min, dr_max+eps);

  h_minDR_pfHad_genLostEl_noPfElMatch = new TH1D("h_minDR_pfHad_genLostEl_noPfElMatch", "min#DeltaR(pfHad, genLostElectron), when no match to pfEl found", nBins_dr, dr_min, dr_max+eps);   
  h_minDR_pfHad_genLostMu_noPfMuMatch = new TH1D("h_minDR_pfHad_genLostMu_noPfMuMatch", "min#DeltaR(pfHad, genLostMuon), when no match to pfMu found", nBins_dr, dr_min, dr_max+eps);
  


  h_minDR_pfCand_genLostEl = new TH1D("h_minDR_pfCand_genLostEl", "min#DeltaR(pfCand, genLostElectron)", nBins_dr, dr_min, dr_max+eps);
  h_minDR_pfCand_genLostMu = new TH1D("h_minDR_pfCand_genLostMu", "min#DeltaR(pfCand, genLostMuon)", nBins_dr, dr_min, dr_max+eps);
  h_minDR_pfCand_genLostHadTau_1prong = new TH1D("h_minDR_pfCand_genLostHadTau_1prong", "min#DeltaR(pfHad, 1 prong genLostHadTau)", nBins_dr, dr_min, dr_max+eps);
  h_minDR_pfCand_genLostLep_hadTau_3prong = new TH1D("h_minDR_pfCand_genLostLep_hadTau_3prong", "min#DeltaR(pfHad, 3 prong genLostHadTau)", nBins_dr, dr_min, dr_max+eps);


    
  h_genLostEl_matchedTo_pfEl_pt_vs_eta = new TH2D("h_genLostEl_matchedTo_pfEl_pt_vs_eta_el", "gen lost electron, matched to pfElectron, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostMu_matchedTo_pfMu_pt_vs_eta = new TH2D("h_genLostMu_matchedTo_pfMu_pt_vs_eta_mu", "gen lost muon, matched to pfMuon, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_1prong = new TH2D("h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_1prong", "gen lost hadronic 1 prong tau, matched to pfHadron, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_3prong = new TH2D("h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_3prong", "gen lost hadronic 3 prong tau, matched to pfHadron, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);


  h_genLostEl_unMatchedTo_pfEl_pt_vs_eta = new TH2D("h_genLostEl_unMatchedTo_pfEl_pt_vs_eta_el", "gen lost electron, NOT matched to pfElectron, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostMu_unMatchedTo_pfMu_pt_vs_eta = new TH2D("h_genLostMu_unMatchedTo_pfMu_pt_vs_eta_el", "gen lost muon, NOT matched to pfMuon, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostHadTau_1prong_unMatchedTo_pfHad_pt_vs_eta = new TH2D("h_genLostHadTau_1prong_unMatchedTo_pfMu_pt_vs_eta_el", "gen lost 1prong hadronic tau, NOT matched to pfHad, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostHadTau_3prong_unMatchedTo_pfHad_pt_vs_eta = new TH2D("h_genLostHadTau_3prong_unMatchedTo_pfMu_pt_vs_eta_el", "gen lost 3prong hadronic tau, NOT matched to pfHad, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);


  h_pfEl_matchedTo_genLostEl_pt_vs_eta = new TH2D("h_pfEl_matchedTo_genLostEl_pt_vs_eta", "pfElectron, matched to gen lost electron, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_pfMu_matchedTo_genLostMu_pt_vs_eta = new TH2D("h_pfMu_matchedTo_genLostMu_pt_vs_eta", "pfMuon, matched to gen lost muon, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_1prong = new TH2D("h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_1prong", "pfHadron, matched to gen lost hadronic 1 prong tau, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_3prong = new TH2D("h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_3prong", "pfHadron, matched to gen lost hadronic 3 prong tau, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  
    
  h_genLostEl_matchedTo_pfCand_pt_vs_eta = new TH2D("h_genLostEl_matchedTo_pfCand_pt_vs_eta", "gen lost electron, matched to pfCandidate, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostMu_matchedTo_pfCand_pt_vs_eta = new TH2D("h_genLostMu_matchedTo_pfCand_pt_vs_eta", "gen lost muon, matched to pfCandidate, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_1prong = new TH2D("h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_1prong", "gen lost hadronic 1 prong tau, matched to pfCandidate, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_3prong = new TH2D("h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_3prong", "gen lost hadronic 3 prong tau, matched to pfCandidate, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);

  
  h_pfCand_matchedTo_genLostEl_pt_vs_eta = new TH2D("h_pfCand_matchedTo_genLostEl_pt_vs_eta", "pfCandidate, matched to gen lost electron, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_pfCand_matchedTo_genLostMu_pt_vs_eta = new TH2D("h_pfCand_matchedTo_genLostMu_pt_vs_eta", "pfCandidate, matched to gen lost muon, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_1prong = new TH2D("h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_1prong", "pfCandidate, matched to gen lost hadronic 1 prong tau, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_3prong = new TH2D("h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_3prong", "pfCandidate, matched to gen lost hadronic 3 prong tau, pT vs #eta", nBins_eta, eta_min, eta_max+eps, nBins_pt, pt_min, pt_max+eps);
  
  

  h_relTrackIso_pfLep_matchedTo_genLostLep_mu = new TH1D("h_relTrackIso_pfLep_matchedTo_genLostLep_mu", "Relative TrackIso for pfMuons matched to gen lost muons in region of pT>5 #eta<2.4", nBins_relIso, relIso_min, relIso_max+eps);
  h_relTrackIso_pfEl_matchedTo_genLostEl = new TH1D("h_relTrackIso_pfEl_matchedTo_genLostEl", "Relative TrackIso for pfElectrons matched to gen lost electrons in region of pT>5 #eta<2.4", nBins_relIso, relIso_min, relIso_max+eps); 
  h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_1prong = new TH1D("h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_1prong", "Relative TrackIso for pfHadrons matched to gen lost 1 prong had taus in region of pT>5 #eta<2.4", nBins_relIso, relIso_min, relIso_max+eps);
  h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_3prong = new TH1D("h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_3prong", "Relative TrackIso for pfElectrons matched to gen lost 3 prong had taus in region of pT>5 #eta<2.4", nBins_relIso, relIso_min, relIso_max+eps);


  h_relTrackIso_vs_pT_pfMu_matchedTo_genLostMu = new TH2D("h_relTrackIso_vs_pT_pfMu_matchedTo_genLostMu", "Relative trackIso vs pT for pfMuons matched to gen lost muon; pT; relTrackIso", nBins_pt, pt_min, pt_max+eps, nBins_relIso, relIso_min, relIso_max+eps);
  h_relTrackIso_vs_pT_pfEl_matchedTo_genLostEl = new TH2D("h_relTrackIso_vs_pT_pfEl_matchedTo_genLostEl", "Relative trackIso vs pT for pfEl matched to gen lost electron; pT; relTrackIso", nBins_pt, pt_min, pt_max+eps, nBins_relIso, relIso_min, relIso_max+eps);
  h_relTrackIso_vs_pT_pfHad_matchedTo_genLostHadTau_1prong = new TH2D("h_relTrackIso_vs_pT_pfHadTau_matchedTo_genLostHadTau_1prong", "Relative trackIso vs pT for pfHadrons matched to gen lost hadronic tau, 1 prong; pT; relTrackIso", nBins_pt, pt_min, pt_max+eps, nBins_relIso, relIso_min, relIso_max+eps);;


  
  

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
      if( is_0l && nGenLeptons!=0 ) continue;
      if( is_1l && nGenLeptons!=1 ) continue;
      if( is_2l && nGenLeptons!=2 ) continue;
            
      //
      // Pre-Selection
      //
      if( doCut_nVtx && nvtxs()<cut_nVtx ) continue;
      nEvents_pass_nVtx++;
      nEvents_pass_nVtx_wgt+=wgt;

      if( doCut_nGoodLep && ngoodleps()<cut_nGoodLep ) continue;
      nEvents_pass_nGoodLep++;
      nEvents_pass_nGoodLep_wgt+=wgt;
      
      int nSelLeptons = 0;
      TLorentzVector selLep_TLV(0.0, 0.0, 0.0, 0.0);
      double selLep_charge = 0;
      if( doCut_nSelLep ){
	
	if( lep1_is_mu() ){
	  if( lep1_passMediumID() &&
	      lep1_pt()>30.0 &&
	      fabs(lep1_eta())<2.1 &&
	      fabs(lep1_d0())<0.02 &&
	      fabs(lep1_dz())<0.1 &&
	      lep1_miniRelIsoDB()<0.10 ){
	    nSelLeptons++;
	    selLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
	    selLep_charge = lep1_charge();
	  } // end if good muon
	}
	  
	if( lep1_is_el() ){
	  if( lep1_passMediumID() &&
	      lep1_pt()>40.0 &&
	      fabs(lep1_eta())<2.1 &&
	      lep1_is_phys14_medium_noIso() &&
	      lep1_miniRelIsoDB()<0.10 ){
	    nSelLeptons++;
	    selLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
	    selLep_charge = lep1_charge();
	  } // end if good electron
	}
      
	  
      	if( nSelLeptons != cut_nSelLep ) continue;
      }
      nEvents_pass_nSelLep++;
      nEvents_pass_nSelLep_wgt+=wgt;

      if( doCut_trackVeto && !PassTrackVeto() ) continue;
      nEvents_pass_trackVeto++;
      nEvents_pass_trackVeto_wgt+=wgt;
      
      if( doCut_tauVeto && !PassTauVeto() ) continue;
      nEvents_pass_tauVeto++;
      nEvents_pass_tauVeto_wgt+=wgt;

      
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
      nEvents_pass_nJets_wgt+=wgt;
      
      if( doCut_nBJets && nTagJets<cut_nBJets ) continue;
      nEvents_pass_nBJets++;
      nEvents_pass_nBJets_wgt+=wgt;
      

      //
      // Additional Selection for Baseline Region
      //
      if( doCut_met && pfmet()<=cut_met ) continue;
      nEvents_pass_met++;
      nEvents_pass_met_wgt+=wgt;
      
      
      if( doCut_mt && mt_met_lep()<=cut_mt ) continue;
      nEvents_pass_mtCut++;
      nEvents_pass_mtCut_wgt+=wgt;
      
      
      if( doCut_minDPhi && mindphi_met_j1_j2()<=cut_minDPhi ) continue;
      nEvents_pass_minDPhi++;
      nEvents_pass_minDPhi_wgt+=wgt;


      if( doCut_chi2 && chi2()>=cut_chi2 ) continue;
      nEvents_pass_chi2++;
      nEvents_pass_chi2_wgt+=wgt;


      nEvents_pass_baseline++;
      nEvents_pass_baseline_wgt+=wgt;
  

      //
      // Determine Signal Region Category
      //
      std::vector<int> qualified_cats;

      // Low DeltaM
      if( pfmet()>150.0 ){
	qualified_cats.push_back(7);
	nEvents_pass_met150_wgt+=wgt;
      }
      if( pfmet()>200.0 ){
	qualified_cats.push_back(8);
	nEvents_pass_met200_wgt+=wgt;
      }
      if( pfmet()>250.0 ){
	qualified_cats.push_back(9);
	nEvents_pass_met250_wgt+=wgt;
      }
      if( pfmet()>300.0 ){
	qualified_cats.push_back(10);
	nEvents_pass_met300_wgt+=wgt;
      }
      
      // High DeltaM
      if( pfmet()>150.0 && MT2W()>200.0 ){
	qualified_cats.push_back(11);
	nEvents_pass_met150_mt2w200_wgt+=wgt;
      }
      if( pfmet()>200.0 && MT2W()>200.0 ){
	qualified_cats.push_back(12);
	nEvents_pass_met200_mt2w200_wgt+=wgt;
      }
      if( pfmet()>250.0 && MT2W()>200.0 ){
	qualified_cats.push_back(13);
	nEvents_pass_met250_mt2w200_wgt+=wgt;
      }
      if( pfmet()>300.0 && MT2W()>200.0 ){
	qualified_cats.push_back(14);
	nEvents_pass_met300_mt2w200_wgt+=wgt;
      }
      
      

      for(int i=0; i<(int)qualified_cats.size(); i++){
	
      } // end loop over qualified cats


            
      //
      // Track Isolation Veto, in looper
      //
      double dr_selLep = 0.4;
      
      double pfElPt = 5.0;
      double pfMuPt = 5.0;
      double pfHadPt = 10.0;
      
      double pfElRelIso = 0.2;
      double pfMuRelIso = 0.2;
      double pfHadRelIso = 0.1;
      
      double pfEl_pt_forAbsIso = 60.0;
      double pfMu_pt_forAbsIso = 30.0;
      double pfHad_pt_forAbsIso = 60.0;

      int nIsoTrks=0;
      for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
	temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	// Overlap removal of pfCands near selected reco lepton
	if( selLep_TLV.DeltaR(temp) < dr_selLep ) continue;

	// Muon component of track isolation veto

	// pfMuon pT cut
	if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_p4().at(iPFCand).Pt()>=pfMuPt ){

	  // Histo of pfMu relative track isolation, for pfMuons that pass pT cut
	  if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<0.6 ){
	    h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso->Fill(isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt());
	  }

	  // pfMuon relative isolation cut
	  if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfMuRelIso ){

	    // This pfMuon is an isolated track
	    nIsoTrks++;

	    // Histos of pT and relative track isolation of pfMuon that is an isoTrack
	    h_isoTrack_isMu_pt->Fill( std::min( (double)isoTracks_p4().at(iPFCand).Pt(), pt_max ), wgt );
	    h_isoTrack_isMu_relTrkIso->Fill(isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt(), wgt);
	    
	    // Histo of absolute isolation, for pfMuons that are isoTracks and have pT> pfMu_pt_forAbsIso
	    if( isoTracks_p4().at(iPFCand).Pt()>pfMu_pt_forAbsIso ){
	      h_isoTrack_isMu_ptGT30_absIso->Fill( std::min( (double)isoTracks_absIso().at(iPFCand), absIso_max ), wgt );
	    }

	  } // end if passes relative track isolation
	} // enbd if passes pt

	
	// Electron component of track isolation
	
	// pfElectron pT cut		    
	if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_p4().at(iPFCand).Pt()>=pfElPt ){

	  // Histo of pfEl relative track isolation, for pfElectrons that pass pT cut
	  if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<0.6 ){
	    h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso->Fill(isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt());
	  }

	  // pfElectron relative track isolation cut
	  if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfElRelIso ){

	    // This  pfElectron is an isoTrack
	    nIsoTrks++;

	    // Histos of pT and relative track isolation of pfElectron that is an isoTrack
	    h_isoTrack_isEl_pt->Fill( std::min( (double)isoTracks_p4().at(iPFCand).Pt(), pt_max ), wgt );
	    h_isoTrack_isEl_relTrkIso->Fill(isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt(), wgt);

	    // Histo of absolute isolation of pfElectron that is an isoTrack and has pT> pfEl_pt_forAbsIso
	    if( isoTracks_p4().at(iPFCand).Pt()>pfEl_pt_forAbsIso ){
	      h_isoTrack_isEl_ptGT60_absIso->Fill( std::min( (double)isoTracks_absIso().at(iPFCand), absIso_max ), wgt );
	    }

	  } // end if passes relative isolation cut
	} // end if passes pT cut


	// Charged Hadron component of track isolation veto

	// pfHadron pT cut
	if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_p4().at(iPFCand).Pt()>=pfHadPt ){
	  
	  // Histo of pfHad relative track isolation, for pfHadrons that pass pT cut
	  if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<0.6 ){
	    h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso->Fill(isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt());
	  }

	  // pfHadron relative isolation cut
	  if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfHadRelIso ){

	    // pfHadron opposite sign charge cut (wrt selected reco lepton)
	    if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_charge().at(iPFCand)*selLep_charge<0 ){

	      // This pfHadron is an isoTrack
	      nIsoTrks++;

	      // Histos for pT and relative track isolation of pfHadron that is an isoTrack
	      h_isoTrack_isHad_pt->Fill( std::min((double)isoTracks_p4().at(iPFCand).Pt(), pt_max), wgt );
	      h_isoTrack_isHad_relTrkIso->Fill(isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt(), wgt);

	      // Histo of absolute isolation of pfHadron that is an isoTrack
	      if( isoTracks_p4().at(iPFCand).Pt()>pfHad_pt_forAbsIso ){
		h_isoTrack_isHad_ptGT60_absIso->Fill( std::min( (double)isoTracks_absIso().at(iPFCand), absIso_max ), wgt );
	      }

	    } // end if passes opposite sign charge veto
	  } // end if passes relative isolation cut
	} // end if passes pT cut


      } // end loop over pfCandidates

      // If no isoTracks found, this event passes track isolation veto
      if( nIsoTrks==0 ){
	passTrackIso_veto++;
	passTrackIsoVeto_wgt+=wgt;
      }


     
      //
      // Track Iso Veto Optimization
      //
      for(double pfMuIso=0.1; pfMuIso<=0.5; pfMuIso+=0.1){
	for(int pfMuQVeto=0; pfMuQVeto<=1; pfMuQVeto++){
	  for(double pfElIso=0.1; pfElIso<=0.5; pfElIso+=0.1){
	    for(int pfElQVeto=0; pfElQVeto<=1; pfElQVeto++){
	      for(int pfAbsIso=0; pfAbsIso<=1; pfAbsIso++){
		for(double pfHadIso=0.1; pfHadIso<=0.4; pfHadIso+=0.1){
		    
		  TString vetoName = "";
		  vetoName+= "pfMuIso=";
		  vetoName+=Form("%.1f",pfMuIso);
		  vetoName+= ", ";
		  vetoName+= "pfMuQVeto=";
		  vetoName+=Form("%d",pfMuQVeto);
		  vetoName+= ", ";
		  vetoName+= "pfElIso=";
		  vetoName+=Form("%.1f",pfElIso);
		  vetoName+= ", ";
		  vetoName+= "pfElQVeto=";
		  vetoName+=Form("%d",pfElQVeto);
		  vetoName+= ", ";
		  vetoName+= "pfAbsIso=";
		  vetoName+=Form("%d",pfAbsIso);
		  vetoName+= ", ";
		  vetoName+= "pfHadIso=";
		  vetoName+=Form("%.1f",pfHadIso);
	      
			  
		  // Do trackIsoVetoCut
		  int nIsoTrks=0;
		  for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
		    TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
		    temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );

		    // Overlap removal wrt selected reco lepton
		    if( selLep_TLV.DeltaR(temp) < dr_selLep ) continue;
		      

		    // Muon component of track isolation veto
		    if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_p4().at(iPFCand).Pt()<pfMuPt ) continue;
		    if(pfAbsIso>0.0 && isoTracks_p4().at(iPFCand).Pt()>pfMu_pt_forAbsIso){
		      if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)>pfMuIso*pfMu_pt_forAbsIso ) continue;
		    }
		    else{
		      if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()>pfMuIso ) continue;
		    }
		    //if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()>pfMuIso ) continue;
		    if( abs(isoTracks_pdgId().at(iPFCand))==13 && pfMuQVeto==1 && isoTracks_charge().at(iPFCand)*selLep_charge>0 ) continue;

		    
		    // Electron component of track isolation veto
		    if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_p4().at(iPFCand).Pt()<pfElPt ) continue;
		    if(pfAbsIso>0.0 && isoTracks_p4().at(iPFCand).Pt()>pfEl_pt_forAbsIso){
		      if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)>pfElIso*pfEl_pt_forAbsIso ) continue;
		    }
		    else{
		      if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()>pfElIso ) continue;
		    }
		    //if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()>pfElIso ) continue;
		    if( abs(isoTracks_pdgId().at(iPFCand))==11 && pfElQVeto==1 && isoTracks_charge().at(iPFCand)*selLep_charge>0 ) continue;
			 

		    // Hadron component of track isolation veto
		    if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_p4().at(iPFCand).Pt()<pfHadPt ) continue;
		    if(pfAbsIso>0.0 && isoTracks_p4().at(iPFCand).Pt()>pfHad_pt_forAbsIso){
		      if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)>pfHadIso*pfHad_pt_forAbsIso ) continue;
		    }
		    else{
		      if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()>pfHadIso ) continue;
		    }
		    //if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()>pfHadIso ) continue;
		    if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_charge().at(iPFCand)*selLep_charge>0 ) continue;

		    nIsoTrks++;
		  }

		  // If this event passes, then increase counter of map for this veto name
		  if(nIsoTrks==0) trkIsoVeto_nEvents_passCut[ vetoName ]+=1;
			    
		}
	      }
	    }
	  }
	}
      }
    
       
      
      //
      // N-1 track isolation veto wrt electrons
      //
      int nIsoTrks_nMinus1_el=0;
      for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
	temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	if( selLep_TLV.DeltaR(temp) < dr_selLep ) continue;


	if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_p4().at(iPFCand).Pt()>=pfMuPt ){
	  if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfMuRelIso ){
	    nIsoTrks_nMinus1_el++;
	  }
	}

			    
	//if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_p4().at(iPFCand).Pt()>=pfElPt ){
	//  if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfElRelIso ){
	//    nIsoTrks_nMinus1_el++;
	//  }
	//}


	if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_p4().at(iPFCand).Pt()>=pfHadPt ){
	  if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfHadRelIso ){
	    if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_charge().at(iPFCand)*selLep_charge<0 ){
	      nIsoTrks_nMinus1_el++;
	    }
	  }
	}


      }
      if( nIsoTrks_nMinus1_el==0 ){
	passTrackIso_veto_nMinus1_el++;
	passTrackIso_veto_nMinus1_el_wgt+=wgt;
      }
	

      //
      // N-1 track isolation veto wrt muons
      //
      int nIsoTrks_nMinus1_mu=0;
      for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
	temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	if( selLep_TLV.DeltaR(temp) < dr_selLep ) continue;
	
	
	//if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_p4().at(iPFCand).Pt()>=pfMuPt ){
	//  if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfMuRelIso ){
	//    nIsoTrks_nMinus1_mu++;
	//  }
	//}

			    
	if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_p4().at(iPFCand).Pt()>=pfElPt ){
	  if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfElRelIso ){
	    nIsoTrks_nMinus1_mu++;
	  }
	}


	if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_p4().at(iPFCand).Pt()>=pfHadPt ){
	  if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfHadRelIso ){
	    if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_charge().at(iPFCand)*selLep_charge<0 ){
	      nIsoTrks_nMinus1_mu++;
	    }
	  }
	}


      }
      if( nIsoTrks_nMinus1_mu==0 ){
	passTrackIso_veto_nMinus1_mu++;
	passTrackIso_veto_nMinus1_mu_wgt+=wgt;
      }


      
      //
      // N-1 track islation veto wrt hadrons
      int nIsoTrks_nMinus1_had=0;
      for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
	temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	if( selLep_TLV.DeltaR(temp) < dr_selLep ) continue;
	
	if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_p4().at(iPFCand).Pt()>=pfMuPt ){
	  if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfMuRelIso ){
	    nIsoTrks_nMinus1_had++;
	  }
	}
			    
	if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_p4().at(iPFCand).Pt()>=pfElPt ){
	  if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfElRelIso ){
	    nIsoTrks_nMinus1_had++;
	  }
	}

	//if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_p4().at(iPFCand).Pt()>=pfHadPt ){
	//  if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfHadRelIso ){
	//    if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_charge().at(iPFCand)*selLep_charge<0 ){
	//      nIsoTrks_nMinus1_had++;
	//    }
	//  }
	//}


      }
      if( nIsoTrks_nMinus1_had==0 ){
	passTrackIso_veto_nMinus1_had++;
	passTrackIso_veto_nMinus1_had_wgt+=wgt;
      }

      
                  
      //
      // Optimized track isolation veto cut
      //
      double pfElRelIso_optimized = 0.1;
      double pfMuRelIso_optimized = 0.2;
      double pfHadRelIso_optimized = 0.1;
      
      int nIsoTrks_optimized=0;
      for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
	temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	if( selLep_TLV.DeltaR(temp) < dr_selLep ) continue;


	if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_p4().at(iPFCand).Pt()>=pfMuPt ){
	  if(isoTracks_p4().at(iPFCand).Pt()>pfMu_pt_forAbsIso){
	    if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)<=pfMuRelIso*pfMu_pt_forAbsIso ){
	      nIsoTrks_optimized++;
	    }
	  }
	  else{
	    if( abs(isoTracks_pdgId().at(iPFCand))==13 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfMuRelIso_optimized ){
	      nIsoTrks_optimized++;
	    }
	  }
	}
	
	if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_p4().at(iPFCand).Pt()>=pfElPt ){
	  if(isoTracks_p4().at(iPFCand).Pt()>pfEl_pt_forAbsIso){
	    if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)<=pfElRelIso*pfEl_pt_forAbsIso ){
	      nIsoTrks_optimized++;
	    }
	  }
	  else{
	    if( abs(isoTracks_pdgId().at(iPFCand))==11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfElRelIso_optimized ){
	      nIsoTrks_optimized++;
	    }
	  }
	}


	if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_p4().at(iPFCand).Pt()>=pfHadPt ){
	  if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_charge().at(iPFCand)*selLep_charge<0 ){
	    if(isoTracks_p4().at(iPFCand).Pt()>pfHad_pt_forAbsIso){
	      if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)<=pfHadIso*pfHad_pt_forAbsIso ){
		nIsoTrks_optimized++;
	      }
	    }
	    else{
	      if( abs(isoTracks_pdgId().at(iPFCand))!=13 && abs(isoTracks_pdgId().at(iPFCand))!=11 && isoTracks_absIso().at(iPFCand)/isoTracks_p4().at(iPFCand).Pt()<=pfHadRelIso ){
		nIsoTrks_optimized++;
	      }
	    }

	  }
	}


      }
      if( nIsoTrks_optimized==0 ){
	passTrackIso_veto_optimized++;
	passTrackIso_veto_optimized_wgt+=wgt;
      }


      
      //
      // Look at properties of gen leptons and pfCandidates
      //
      if( nGenLeptons>=0 ){


	// Look at direct genEls from top
	std::vector<int> matched_pfEl_idx;
	std::vector<int> matched_pfElOrHad_idx;
	for(int iGen=0; iGen<(int)genels_p4().size(); iGen++){
	  
	  h_genLeptonFromTop_id->Fill( "ele", wgt );

	  h_genEl_pt_vs_eta->Fill( std::min( (double)fabs(genels_p4().at(iGen).Eta()), eta_max), std::min( (double)genels_p4().at(iGen).Pt(), pt_max), wgt);

	  TLorentzVector genEl(0.0,0.0,0.0,0.0);
	  genEl.SetPxPyPzE( genels_p4().at(iGen).Px(), genels_p4().at(iGen).Py(), genels_p4().at(iGen).Pz(), genels_p4().at(iGen).E() );

	  if( genEl.Pt()<5.0 || fabs(genEl.Eta())>2.4 ) continue;
	  
	  h_genEl_goodPtEta_pt_vs_eta->Fill( std::min( (double)fabs(genEl.Eta()), eta_max), std::min( (double)genEl.Pt(), pt_max), wgt);

	  double mindr_genEl_pfEl=99.9;
	  int mindr_pfEl_idx=-99;
	  for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	    if( abs(isoTracks_pdgId().at(iPf))==11 ){
		  
	      bool alreadyMatched=false;
	      for(int iMatched=0; iMatched<(int)matched_pfEl_idx.size(); iMatched++){
		if( matched_pfEl_idx[iMatched]==iPf ) alreadyMatched=true;
	      }
	      if( alreadyMatched ) continue;

	      TLorentzVector pfEl(0.0,0.0,0.0,0.0);
	      pfEl.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
	      double dr = genEl.DeltaR(pfEl);
	      if( dr<mindr_genEl_pfEl ){
		mindr_genEl_pfEl = dr;
		mindr_pfEl_idx=iPf;
	      } // end if minDr
		  
	    } // end if pfEl

	  } // end loop over pfCands

	  
	  h_minDR_pfEl_genEl->Fill( std::min(mindr_genEl_pfEl, dr_max), wgt );

	  if(mindr_genEl_pfEl<0.1){
	    matched_pfEl_idx.push_back(mindr_pfEl_idx);
	    h_genEl_pt_vs_eta_matchedToPfEl->Fill( std::min( (double)fabs(genels_p4().at(iGen).Eta()), eta_max), std::min( (double)genels_p4().at(iGen).Pt(), pt_max), wgt);
	  } // end if found matched pfEl
	  else{
	    double mindr_genEl_pfCand=99.9;
	    int mindr_pfCand_idx=-99;
	    for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	      if( abs(isoTracks_pdgId().at(iPf))!=11 &&
		  abs(isoTracks_pdgId().at(iPf))!=13    ){
		    
		bool alreadyMatched=false;
		for(int iMatched=0; iMatched<(int)matched_pfElOrHad_idx.size(); iMatched++){
		  if( matched_pfElOrHad_idx[iMatched]==iPf ) alreadyMatched=true;
		}
		if( alreadyMatched ) continue;
		
		TLorentzVector pfCand(0.0,0.0,0.0,0.0);
		pfCand.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
		double dr = genEl.DeltaR(pfCand);
		if( dr<mindr_genEl_pfCand ){
		  mindr_genEl_pfCand = dr;
		  mindr_pfCand_idx=iPf;
		} // end if minDr
		    
	      } // end if pfEl
	      
	    } // end loop over pfCands
	    
	    h_minDR_pfHad_genEl_notMatchedToPfEl_incl->Fill( std::min(mindr_genEl_pfCand, dr_max), wgt );

	    if(mindr_genEl_pfCand<0.1){
	      matched_pfElOrHad_idx.push_back(mindr_pfCand_idx);		  
	      h_genEl_notMatchedToPfEl_pt_vs_eta_matchedToPfHad->Fill( std::min( (double)fabs(genels_p4().at(iGen).Eta()), eta_max), std::min( (double)genels_p4().at(iGen).Pt(), pt_max), wgt);
	    } // end if found matched pfHad
	    
	  } // end if not matched to pfEl

	} // end loop over genels




	// Look at gen els from tau decays 
	for(int iGen=0; iGen<(int)genleptau_els_p4().size(); iGen++){
	  
	  h_genLeptonFromTop_id->Fill( "ele", wgt );

	  h_genEl_pt_vs_eta->Fill( std::min( (double)fabs(genleptau_els_p4().at(iGen).Eta()), eta_max), std::min( (double)genleptau_els_p4().at(iGen).Pt(), pt_max), wgt);

	  TLorentzVector genEl(0.0,0.0,0.0,0.0);
	  genEl.SetPxPyPzE( genleptau_els_p4().at(iGen).Px(), genleptau_els_p4().at(iGen).Py(), genleptau_els_p4().at(iGen).Pz(), genleptau_els_p4().at(iGen).E() );

	  if( genEl.Pt()<5.0 || fabs(genEl.Eta())>2.4 ) continue;
	  
	  h_genEl_goodPtEta_pt_vs_eta->Fill( std::min( (double)fabs(genEl.Eta()), eta_max), std::min( (double)genEl.Pt(), pt_max), wgt);

	  double mindr_genEl_pfEl=99.9;
	  int mindr_pfEl_idx=-99;
	  for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	    if( abs(isoTracks_pdgId().at(iPf))==11 ){
		  
	      bool alreadyMatched=false;
	      for(int iMatched=0; iMatched<(int)matched_pfEl_idx.size(); iMatched++){
		if( matched_pfEl_idx[iMatched]==iPf ) alreadyMatched=true;
	      }
	      if( alreadyMatched ) continue;

	      TLorentzVector pfEl(0.0,0.0,0.0,0.0);
	      pfEl.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
	      double dr = genEl.DeltaR(pfEl);
	      if( dr<mindr_genEl_pfEl ){
		mindr_genEl_pfEl = dr;
		mindr_pfEl_idx=iPf;
	      } // end if minDr
		  
	    } // end if pfEl

	  } // end loop over pfCands

	  h_minDR_pfEl_genEl->Fill( std::min(mindr_genEl_pfEl, dr_max), wgt );

	  if(mindr_genEl_pfEl<0.1){
	    matched_pfEl_idx.push_back(mindr_pfEl_idx);
	    h_genEl_pt_vs_eta_matchedToPfEl->Fill( std::min( (double)fabs(genleptau_els_p4().at(iGen).Eta()), eta_max), std::min( (double)genleptau_els_p4().at(iGen).Pt(), pt_max), wgt);
	  } // end if found matched pfEl
	  else{
	    double mindr_genEl_pfCand=99.9;
	    int mindr_pfCand_idx=-99;
	    for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	      if( abs(isoTracks_pdgId().at(iPf))!=11 &&
		  abs(isoTracks_pdgId().at(iPf))!=13    ){
		    
		bool alreadyMatched=false;
		for(int iMatched=0; iMatched<(int)matched_pfElOrHad_idx.size(); iMatched++){
		  if( matched_pfElOrHad_idx[iMatched]==iPf ) alreadyMatched=true;
		}
		if( alreadyMatched ) continue;
		
		TLorentzVector pfCand(0.0,0.0,0.0,0.0);
		pfCand.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
		double dr = genEl.DeltaR(pfCand);
		if( dr<mindr_genEl_pfCand ){
		  mindr_genEl_pfCand = dr;
		  mindr_pfCand_idx=iPf;
		} // end if minDr
		    
	      } // end if pfEl
	      
	    } // end loop over pfCands
	    
	    h_minDR_pfHad_genEl_notMatchedToPfEl_incl->Fill( std::min(mindr_genEl_pfCand, dr_max), wgt );

	    if(mindr_genEl_pfCand<0.1){
	      matched_pfElOrHad_idx.push_back(mindr_pfCand_idx);		  
	      h_genEl_notMatchedToPfEl_pt_vs_eta_matchedToPfHad->Fill( std::min( (double)fabs(genleptau_els_p4().at(iGen).Eta()), eta_max), std::min( (double)genleptau_els_p4().at(iGen).Pt(), pt_max), wgt);
	    } // end if found matched pfHad
	    
	  } // end if not matched to pfEl

	} // end loop over genleptau_els


	


	// Look at direct genMus from top
	std::vector<int> matched_pfMu_idx;
	std::vector<int> matched_pfMuOrHad_idx;
	for(int iGen=0; iGen<(int)genmus_p4().size(); iGen++){
	  
	  h_genLeptonFromTop_id->Fill( "mu", wgt );

	  h_genMu_pt_vs_eta->Fill( std::min( (double)fabs(genmus_p4().at(iGen).Eta()), eta_max), std::min( (double)genmus_p4().at(iGen).Pt(), pt_max), wgt);

	  TLorentzVector genMu(0.0,0.0,0.0,0.0);
	  genMu.SetPxPyPzE( genmus_p4().at(iGen).Px(), gengmus_p4().at(iGen).Py(), genmus_p4().at(iGen).Pz(), genmus_p4().at(iGen).E() );

	  if( genMu.Pt()<5.0 || fabs(genMu.Eta())>2.4 ) continue;
	  
	  h_genMu_goodPtEta_pt_vs_eta->Fill( std::min( (double)fabs(genMu.Eta()), eta_max), std::min( (double)genMu.Pt(), pt_max), wgt);

	  double mindr_genMu_pfMu=99.9;
	  int mindr_pfMu_idx=-99;
	  for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	    if( abs(isoTracks_pdgId().at(iPf))==11 ){
		  
	      bool alreadyMatched=false;
	      for(int iMatched=0; iMatched<(int)matched_pfMu_idx.size(); iMatched++){
		if( matched_pfMu_idx[iMatched]==iPf ) alreadyMatched=true;
	      }
	      if( alreadyMatched ) continue;

	      TLorentzVector pfMu(0.0,0.0,0.0,0.0);
	      pfMu.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
	      double dr = genMu.DeltaR(pfMu);
	      if( dr<mindr_genMu_pfMu ){
		mindr_genMu_pfMu = dr;
		mindr_pfMu_idx=iPf;
	      } // end if minDr
		  
	    } // end if pfMu

	  } // end loop over pfCands

	  
	  h_minDR_pfMu_genMu->Fill( std::min(mindr_genMu_pfMu, dr_max), wgt );

	  if(mindr_genMu_pfMu<0.1){
	    matched_pfMu_idx.push_back(mindr_pfMu_idx);
	    h_genMu_pt_vs_eta_matchedToPfMu->Fill( std::min( (double)fabs(genmus_p4().at(iGen).Eta()), eta_max), std::min( (double)genmus_p4().at(iGen).Pt(), pt_max), wgt);
	  } // end if found matched pfMu
	  else{
	    double mindr_genMu_pfCand=99.9;
	    int mindr_pfCand_idx=-99;
	    for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	      if( abs(isoTracks_pdgId().at(iPf))!=11 &&
		  abs(isoTracks_pdgId().at(iPf))!=13    ){
		    
		bool alreadyMatched=false;
		for(int iMatched=0; iMatched<(int)matched_pfMuOrHad_idx.size(); iMatched++){
		  if( matched_pfMuOrHad_idx[iMatched]==iPf ) alreadyMatched=true;
		}
		if( alreadyMatched ) continue;
		
		TLorentzVector pfCand(0.0,0.0,0.0,0.0);
		pfCand.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
		double dr = genMu.DeltaR(pfCand);
		if( dr<mindr_genMu_pfCand ){
		  mindr_genMu_pfCand = dr;
		  mindr_pfCand_idx=iPf;
		} // end if minDr
		    
	      } // end if pfMu
	      
	    } // end loop over pfCands
	    
	    h_minDR_pfHad_genMu_notMatchedToPfMu_incl->Fill( std::min(mindr_genMu_pfCand, dr_max), wgt );

	    if(mindr_genMu_pfCand<0.1){
	      matched_pfMuOrHad_idx.push_back(mindr_pfCand_idx);		  
	      h_genMu_notMatchedToPfMu_pt_vs_eta_matchedToPfHad->Fill( std::min( (double)fabs(genmus_p4().at(iGen).Eta()), eta_max), std::min( (double)genmus_p4().at(iGen).Pt(), pt_max), wgt);
	    } // end if found matched pfHad
	    
	  } // end if not matched to pfMu

	} // end loop over genmus




	// Look at gen mus from tau decays 
	for(int iGen=0; iGen<(int)genleptau_mus_p4().size(); iGen++){
	  
	  h_genLeptonFromTop_id->Fill( "mu", wgt );

	  h_genMu_pt_vs_eta->Fill( std::min( (double)fabs(genleptau_mus_p4().at(iGen).Eta()), eta_max), std::min( (double)genleptau_mus_p4().at(iGen).Pt(), pt_max), wgt);

	  TLorentzVector genMu(0.0,0.0,0.0,0.0);
	  genMu.SetPxPyPzE( genleptau_mus_p4().at(iGen).Px(), genleptau_mus_p4().at(iGen).Py(), genleptau_mus_p4().at(iGen).Pz(), genleptau_mus_p4().at(iGen).E() );

	  if( genMu.Pt()<5.0 || fabs(genMu.Eta())>2.4 ) continue;
	  
	  h_genMu_goodPtEta_pt_vs_eta->Fill( std::min( (double)fabs(genMu.Eta()), eta_max), std::min( (double)genMu.Pt(), pt_max), wgt);

	  double mindr_genMu_pfMu=99.9;
	  int mindr_pfMu_idx=-99;
	  for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	    if( abs(isoTracks_pdgId().at(iPf))==11 ){
		  
	      bool alreadyMatched=false;
	      for(int iMatched=0; iMatched<(int)matched_pfMu_idx.size(); iMatched++){
		if( matched_pfMu_idx[iMatched]==iPf ) alreadyMatched=true;
	      }
	      if( alreadyMatched ) continue;

	      TLorentzVector pfMu(0.0,0.0,0.0,0.0);
	      pfMu.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
	      double dr = genMu.DeltaR(pfMu);
	      if( dr<mindr_genMu_pfMu ){
		mindr_genMu_pfMu = dr;
		mindr_pfMu_idx=iPf;
	      } // end if minDr
		  
	    } // end if pfMu

	  } // end loop over pfCands

	  h_minDR_pfMu_genMu->Fill( std::min(mindr_genMu_pfMu, dr_max), wgt );

	  if(mindr_genMu_pfMu<0.1){
	    matched_pfMu_idx.push_back(mindr_pfMu_idx);
	    h_genMu_pt_vs_eta_matchedToPfMu->Fill( std::min( (double)fabs(genleptau_mus_p4().at(iGen).Eta()), eta_max), std::min( (double)genleptau_mus_p4().at(iGen).Pt(), pt_max), wgt);
	  } // end if found matched pfMu
	  else{
	    double mindr_genMu_pfCand=99.9;
	    int mindr_pfCand_idx=-99;
	    for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	      if( abs(isoTracks_pdgId().at(iPf))!=11 &&
		  abs(isoTracks_pdgId().at(iPf))!=13    ){
		    
		bool alreadyMatched=false;
		for(int iMatched=0; iMatched<(int)matched_pfMuOrHad_idx.size(); iMatched++){
		  if( matched_pfMuOrHad_idx[iMatched]==iPf ) alreadyMatched=true;
		}
		if( alreadyMatched ) continue;
		
		TLorentzVector pfCand(0.0,0.0,0.0,0.0);
		pfCand.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
		double dr = genMu.DeltaR(pfCand);
		if( dr<mindr_genMu_pfCand ){
		  mindr_genMu_pfCand = dr;
		  mindr_pfCand_idx=iPf;
		} // end if minDr
		    
	      } // end if pfMu
	      
	    } // end loop over pfCands
	    
	    h_minDR_pfHad_genMu_notMatchedToPfMu_incl->Fill( std::min(mindr_genMu_pfCand, dr_max), wgt );

	    if(mindr_genMu_pfCand<0.1){
	      matched_pfMuOrHad_idx.push_back(mindr_pfCand_idx);		  
	      h_genMu_notMatchedToPfMu_pt_vs_eta_matchedToPfHad->Fill( std::min( (double)fabs(genleptau_mus_p4().at(iGen).Eta()), eta_max), std::min( (double)genleptau_mus_p4().at(iGen).Pt(), pt_max), wgt);
	    } // end if found matched pfHad
	    
	  } // end if not matched to pfMu

	} // end loop over genleptau_mus


	


	// Look at direct genTaus
	std::vector<int> matched_pfHad_idx;
	for(int iGen=0; iGen<(int)gentaus_p4().size(); iGen++){
	  
	  TLorentzVector genTau(0.0,0.0,0.0,0.0);
	  genTau.SetPxPyPzE( gentaus_p4().at(iGen).Px(), gentaus_p4().at(iGen).Py(), gentaus_p4().at(iGen).Pz(), gentaus_p4().at(iGen).E() );

	  if( gentaus_gentaudecay().at(iGen)==1 ){
	    h_genLeptonFromTop_id->Fill( "lep tau, ele", wgt );
	  }
	  if( gentaus_gentaudecay().at(iGen)==2 ){
	    h_genLeptonFromTop_id->Fill( "lep tau, mu", wgt );
	  }

	  if( gentaus_gentaudecay().at(iGen)==3 ){

	    h_genLeptonFromTop_id->Fill( "had tau, 1 prong", wgt );
	    h_genHadTau_1prong_pt_vs_eta->Fill( std::min( (double)fabs(genTau.Eta()), eta_max), std::min( (double)genTau.Pt(), pt_max), wgt);
	    
	    if( genTau.Pt()<5.0 || fabs(genTau.Eta())>2.4 ) continue;
	    h_genHadTau_1prong_goodPtEta_pt_vs_eta->Fill( std::min( (double)fabs(genTau.Eta()), eta_max), std::min( (double)genTau.Pt(), pt_max), wgt);

	  }
	  if( gentaus_gentaudecay().at(iGen)==4 ){
	    h_genLeptonFromTop_id->Fill( "had tau, 3 prong", wgt );
	    h_genHadTau_3prong_pt_vs_eta->Fill( std::min( (double)fabs(genTau.Eta()), eta_max), std::min( (double)genTau.Pt(), pt_max), wgt);
	    
	    if( genTau.Pt()<5.0 || fabs(genTau.Eta())>2.4 ) continue;
	    h_genHadTau_3prong_goodPtEta_pt_vs_eta->Fill( std::min( (double)fabs(genTau.Eta()), eta_max), std::min( (double)genTau.Pt(), pt_max), wgt);

	  }
	  if( gentaus_gentaudecay().at(iGen)==5 ){
	    h_genLeptonFromTop_id->Fill( "\"other\" tau", wgt );
	  }


	  double mindr_genTau_pfHad=99.9;
	  int mindr_pfHad_idx=-99;
	  for(int iPf=0; iPf<(int)isoTracks_p4().size(); iPf++){
	
	    if( abs(isoTracks_pdgId().at(iPf))!=11 &&
		abs(isoTracks_pdgId().at(iPf))!=13    ){
		  
	      bool alreadyMatched=false;
	      for(int iMatched=0; iMatched<(int)matched_pfHad_idx.size(); iMatched++){
		if( matched_pfHad_idx[iMatched]==iPf ) alreadyMatched=true;
	      }
	      if( alreadyMatched ) continue;

	      TLorentzVector pfHad(0.0,0.0,0.0,0.0);
	      pfHad.SetPxPyPzE( isoTracks_p4().at(iPf).Px(), isoTracks_p4().at(iPf).Py(), isoTracks_p4().at(iPf).Pz(), isoTracks_p4().at(iPf).E() );
		  
	      double dr = genTau.DeltaR(pfHad);
	      if( dr<mindr_genTau_pfHad ){
		mindr_genTau_pfHad = dr;
		mindr_pfHad_idx=iPf;
	      } // end if minDr
		  
	    } // end if pfHad

	  } // end loop over pfCands

	  
	  if( gentaus_gentaudecay().at(iGen)==3 ){
	    
	    h_minDR_pfHad_genHadTau_1prong->Fill( std::min(mindr_genTau_pfHad, dr_max), wgt );

	    if(mindr_genTau_pfHad<0.1){
	      matched_pfHad_idx.push_back(mindr_pfHad_idx);
	      h_genHadTau_1prong_pt_vs_eta_matchedToPfHad->Fill( std::min( (double)fabs(genTau.Eta()), eta_max), std::min( (double)genTau.Pt(), pt_max), wgt);
	    } // end if found matched pfHad
	    
	  } // end if 1 prong decay

	  if( gentaus_gentaudecay().at(iGen)==4 ){
	    
	    h_minDR_pfHad_genHadTau_3prong->Fill( std::min(mindr_genTau_pfHad, dr_max), wgt );

	    if(mindr_genTau_pfHad<0.1){
	      matched_pfHad_idx.push_back(mindr_pfHad_idx);
	      h_genHadTau_3prong_pt_vs_eta_matchedToPfHad->Fill( std::min( (double)fabs(genTau.Eta()), eta_max), std::min( (double)genTau.Pt(), pt_max), wgt);
	    } // end if found matched pfHad
	    
	  } // end if 3 prong decay

	} // end loop over gen taus 




	//TH1D *h_minDR_pfHad_genHadTau_1prong_daughter;
	//TH2D *h_genHadTau_1prong_daughter_pt_vs_eta_matchedTo_pfHad;
  
  	  	    
  
	
      } // end if genleptons>0
   
  


      

      //
      // Classify events that pass track isolation veto
      //
      if( !PassTrackVeto() ) continue;

      if( nGenLeptons<2 ) continue;
      h_nGenLeptons_fromTop->Fill(nGenLeptons, wgt);


      //
      // Match gen lep to selected Reco lep
      //
      TLorentzVector genLep_matchedTo_selLep_TLV( 0.0, 0.0, 0.0, 0.0 );
      int genLep_matchedTo_selLep_idx = -99;
      int genLep_matchedTo_selLep_pdgId = -99;
      double min_dr_genLep_matchedTo_selLep=99.9;
      
      if( lep1_is_mu() ){
	  
	for(int iGen=0; iGen<(int)genmus_p4().size(); iGen++){
	    
	  if( !genmus_isfromt().at(iGen) ) continue;
	    
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( genmus_p4().at(iGen).Px(), genmus_p4().at(iGen).Py(), genmus_p4().at(iGen).Pz(), genmus_p4().at(iGen).E() );

	  double dr = temp.DeltaR( selLep_TLV );
	  if( dr >= min_dr_genLep_matchedTo_selLep ) continue;
	  min_dr_genLep_matchedTo_selLep = dr;
	  genLep_matchedTo_selLep_TLV = temp;
	  genLep_matchedTo_selLep_idx = genmus__genpsidx().at(iGen);
	  genLep_matchedTo_selLep_pdgId = genmus_id().at(iGen);

	} // end loop over gen mus
	  
	for(int iGen=0; iGen<(int)genleptau_mus_p4().size(); iGen++){
	    
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( genleptau_mus_p4().at(iGen).Px(), genleptau_mus_p4().at(iGen).Py(), genleptau_mus_p4().at(iGen).Pz(), genleptau_mus_p4().at(iGen).E() );
	    
	  double dr = temp.DeltaR( selLep_TLV );
	  if( dr >= min_dr_genLep_matchedTo_selLep ) continue;
	  min_dr_genLep_matchedTo_selLep = dr;
	  genLep_matchedTo_selLep_TLV = temp;
	  genLep_matchedTo_selLep_idx = genleptau_mus__genpsidx().at(iGen);
	  genLep_matchedTo_selLep_pdgId = genleptau_mus_id().at(iGen);

	} // end loop over gen mus from taus

      } // end if selected lep is a muon

      
      if( lep1_is_el() ){
	  
	for(int iGen=0; iGen<(int)genels_p4().size(); iGen++){
	    
	  if( !genels_isfromt().at(iGen) ) continue;
	    
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( genels_p4().at(iGen).Px(), genels_p4().at(iGen).Py(), genels_p4().at(iGen).Pz(), genels_p4().at(iGen).E() );
	    
	  double dr = temp.DeltaR( selLep_TLV );
	  if( dr >= min_dr_genLep_matchedTo_selLep ) continue;
	  min_dr_genLep_matchedTo_selLep = dr;
	  genLep_matchedTo_selLep_TLV = temp;
	  genLep_matchedTo_selLep_idx = genels__genpsidx().at(iGen);
	  genLep_matchedTo_selLep_pdgId = genels_id().at(iGen);

	} // end loop over gen els
	  
	for(int iGen=0; iGen<(int)genleptau_els_p4().size(); iGen++){
	    
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( genleptau_els_p4().at(iGen).Px(), genleptau_els_p4().at(iGen).Py(), genleptau_els_p4().at(iGen).Pz(), genleptau_els_p4().at(iGen).E() );

	  double dr = temp.DeltaR( selLep_TLV );
	  if( dr >= min_dr_genLep_matchedTo_selLep ) continue;
	  min_dr_genLep_matchedTo_selLep = dr;
	  genLep_matchedTo_selLep_TLV = temp;
	  genLep_matchedTo_selLep_idx = genleptau_els__genpsidx().at(iGen);
	  genLep_matchedTo_selLep_pdgId = genleptau_els_id().at(iGen);

	} // end loop over gen els from taus

      } // end if selected lep is an electron

      h_dR_selLep_genLep->Fill( std::min( (double)min_dr_genLep_matchedTo_selLep, dr_max), wgt );

      //if( min_dr_genLep_matchedTo_selLep == 99.9 ) continue;
      if( min_dr_genLep_matchedTo_selLep > 0.4 ) continue;
      

      //
      // Check deltaR of genLep matched to selRecoLep and nearest pfCand
      //
      double min_dr_genEl_pfCand = 99.9;
      int pfCand_idx_matchedTo_genElMatchedToSelEl=-99; 
      if( lep1_is_el() ){
	for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	  if( abs(isoTracks_pdgId().at(iPFCand))!=11 ) continue;
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	  double dr = temp.DeltaR( genLep_matchedTo_selLep_TLV );
	  if( dr < min_dr_genEl_pfCand ){
	    min_dr_genEl_pfCand = dr;
	    pfCand_idx_matchedTo_genElMatchedToSelEl=iPFCand; 
	  }
	} // end loop over pfCands
      } // end if selected reco lepton is electron

      double min_dr_genMu_pfCand = 99.9;
      int pfCand_idx_matchedTo_genMuMatchedToSelMu=-99; 
      if( lep1_is_mu() ){
	for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	  if( abs(isoTracks_pdgId().at(iPFCand))!=13 ) continue;
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	  double dr = temp.DeltaR( genLep_matchedTo_selLep_TLV );
	  if( dr < min_dr_genMu_pfCand ){
	    min_dr_genMu_pfCand = dr;
	    pfCand_idx_matchedTo_genMuMatchedToSelMu=iPFCand; 
	  }
	} // end loop over pfCands
      } // end if selected reco lepton is muon


      //
      // Check what the deltaR of matched cand is to selRecoLep vs all Others
      //
      if( pfCand_idx_matchedTo_genElMatchedToSelEl!=-99 ){
	for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	  if( iPFCand ==  pfCand_idx_matchedTo_genElMatchedToSelEl ) continue;
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	  double dr = temp.DeltaR( genLep_matchedTo_selLep_TLV );
	  h_minDR_genElMatchedToSelEl_pfEl__vs__allOtherPfCand->Fill( std::min( min_dr_genEl_pfCand, dr_max ), std::min( dr, dr_max ), wgt );
	}
      }
      if( pfCand_idx_matchedTo_genMuMatchedToSelMu!=-99 ){
	for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){
	  if( iPFCand ==  pfCand_idx_matchedTo_genMuMatchedToSelMu ) continue;
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	  double dr = temp.DeltaR( genLep_matchedTo_selLep_TLV );
	  h_minDR_genMuMatchedToSelMu_pfMu__vs__allOtherPfCand->Fill( std::min( min_dr_genMu_pfCand, dr_max ), std::min( dr, dr_max ), wgt );
	}
      }
      


      //
      // Find genLepton from 2nd ttbar decay
      //
      TLorentzVector genLep_lostLep_TLV( 0.0, 0.0, 0.0, 0.0 );
      int genLep_lostLep_id = -99;
      int genLep_lostLep_tauDecayType = -99;
      double genLep_lostLep_charge = 0.0;
      
      int nFound_ttbarLostLeptons=0;
      int nFound_ttbarLostLeptons_mu=0;
      int nFound_ttbarLostLeptons_el=0;
      int nFound_ttbarLostLeptons_taumu=0;
      int nFound_ttbarLostLeptons_tauel=0;
      int nFound_ttbarLostLeptons_tauhad=0;
      int nFound_ttbarLostLeptons_tauother=0;
      
      // check gen mus
      if( gen_nfromtmus_()>0 ){

	for(int iGen=0; iGen<(int)genmus_p4().size(); iGen++){

	  if( !genmus_isfromt().at(iGen) ) continue;
	    
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( genmus_p4().at(iGen).Px(), genmus_p4().at(iGen).Py(), genmus_p4().at(iGen).Pz(), genmus_p4().at(iGen).E() );
	    
	  // Check that this is not the mu matched to selected lep
	  if( genLep_matchedTo_selLep_idx==genmus__genpsidx().at(iGen) ) continue;

	  genLep_lostLep_TLV = temp;
	  genLep_lostLep_id = genmus_id().at(iGen);
	  genLep_lostLep_charge = genmus_charge().at(iGen);

	  h_lostLepton_id->Fill("mu", wgt);

	  nFound_ttbarLostLeptons++;
	  nFound_ttbarLostLeptons_mu++;
	    
	} // end loop over gen mus
	  
      } // if number of gen mus from top > 0

      
      if( gen_nfromtels_()>0 ){

	for(int iGen=0; iGen<(int)genels_p4().size(); iGen++){

	  if( !genels_isfromt().at(iGen) ) continue;
	    
	  TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	  temp.SetPxPyPzE( genels_p4().at(iGen).Px(), genels_p4().at(iGen).Py(), genels_p4().at(iGen).Pz(), genels_p4().at(iGen).E() );
	  
	  // Check that this is not the el matched to selected lep
	  if( genLep_matchedTo_selLep_idx==genels__genpsidx().at(iGen) ) continue;

	  genLep_lostLep_TLV = temp;
	  genLep_lostLep_id = genels_id().at(iGen);
	  genLep_lostLep_charge = genels_charge().at(iGen);

	  h_lostLepton_id->Fill("ele", wgt);

	  nFound_ttbarLostLeptons++;
	  nFound_ttbarLostLeptons_el++;
	    
	} // end loop over gen els

      } // end if number of els > 0

      
      if( gen_nfromttaus_()>0 ){
	  	  
	for(int iGen=0; iGen<(int)gentaus_p4().size(); iGen++){
	    
	  if( !gentaus_isfromt().at(iGen) ) continue;

	  TLorentzVector temp_tau( 0.0, 0.0, 0.0, 0.0 );
	  temp_tau.SetPxPyPzE( gentaus_p4().at(iGen).Px(), gentaus_p4().at(iGen).Py(), gentaus_p4().at(iGen).Pz(), gentaus_p4().at(iGen).E() );
	  
	  // Check for hadronic taus
	  if( gentaus_gentaudecay().at(iGen)==3){
	    genLep_lostLep_tauDecayType = 3;

	    genLep_lostLep_TLV = temp_tau;
	    genLep_lostLep_id = gentaus_id().at(iGen);
	    genLep_lostLep_charge = gentaus_charge().at(iGen);

	    h_lostLepton_id->Fill("had tau, 1 prong", wgt);
	    
	    nFound_ttbarLostLeptons++;
	    nFound_ttbarLostLeptons_tauhad++;
	    continue;
	  }
	  if( gentaus_gentaudecay().at(iGen)==4){
	    genLep_lostLep_tauDecayType = 4;
	   
	    genLep_lostLep_TLV = temp_tau;
	    genLep_lostLep_id = gentaus_id().at(iGen);
	    genLep_lostLep_charge = gentaus_charge().at(iGen);

	    h_lostLepton_id->Fill("had tau, 3 prong", wgt);
	    
	    nFound_ttbarLostLeptons++;
	    nFound_ttbarLostLeptons_tauhad++;
	    continue;
	  }
	  if( gentaus_gentaudecay().at(iGen)==5){
	    genLep_lostLep_tauDecayType = 5;

	    genLep_lostLep_TLV = temp_tau;
	    genLep_lostLep_id = gentaus_id().at(iGen);
	    genLep_lostLep_charge = gentaus_charge().at(iGen);

	    h_lostLepton_id->Fill("\"other\" tau", wgt);
	    
	    nFound_ttbarLostLeptons++;
	    nFound_ttbarLostLeptons_tauother++;
	    continue;
	  }

	  // Check leptonic taus
	  if( gentaus_gentaudecay().at(iGen)==1){
	    genLep_lostLep_tauDecayType = 1;
	    h_lostLepton_id->Fill("lep tau, ele", wgt);
	  }
	  if( gentaus_gentaudecay().at(iGen)==2){
	    genLep_lostLep_tauDecayType = 2;
	    h_lostLepton_id->Fill("lep tau, mu", wgt);
	  }
	    
	  for(int iGenD=0; iGenD<(int)genleptau_mus_p4().size(); iGenD++){
	    // Check that mu(iGenD) is the daughter of tau(iGen)
	    if( genleptau_mus_motheridx().at(iGenD)!=gentaus__genpsidx().at(iGen) ) continue;

	    TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	    temp.SetPxPyPzE( genleptau_mus_p4().at(iGenD).Px(), genleptau_mus_p4().at(iGenD).Py(), genleptau_mus_p4().at(iGenD).Pz(), genleptau_mus_p4().at(iGenD).E() );

	    // Check that this is not the tau-mu matched to selected lep
	    if( genLep_matchedTo_selLep_idx==genleptau_mus__genpsidx().at(iGenD) ) continue;
	      
	    genLep_lostLep_TLV = temp;
	    genLep_lostLep_id = genleptau_mus_id().at(iGenD);
	    genLep_lostLep_charge = genleptau_mus_charge().at(iGenD);
	    nFound_ttbarLostLeptons++;
	    nFound_ttbarLostLeptons_taumu++;
	      
	  } // end loop over genleptau_mus

	      
	  for(int iGenD=0; iGenD<(int)genleptau_els_p4().size(); iGenD++){
	    // Check that el(iGenD) is the daughter of tau(iGen)
	    if( genleptau_els_motheridx().at(iGenD)!=gentaus__genpsidx().at(iGen) ) continue;
	      
	    TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	    temp.SetPxPyPzE( genleptau_els_p4().at(iGenD).Px(), genleptau_els_p4().at(iGenD).Py(), genleptau_els_p4().at(iGenD).Pz(), genleptau_els_p4().at(iGenD).E() );

	    // Check that this is not the tau-el matched to selected lep
	    if( genLep_matchedTo_selLep_idx==genleptau_els__genpsidx().at(iGenD) ) continue;
	      
	    genLep_lostLep_TLV = temp;
	    genLep_lostLep_id = genleptau_els_id().at(iGenD);
	    genLep_lostLep_charge = genleptau_els_id().at(iGenD);
	    nFound_ttbarLostLeptons++;
	    nFound_ttbarLostLeptons_tauel++;
	      			
	  } // end loop over genleptau_els
	    	    
	} // end loop over gen taus

      } // end if number of gen taus from top is > 0
      
      h_nFound_gen_ttbarLostLeptons_notMatchedToSelLep->Fill(nFound_ttbarLostLeptons, wgt);
      

      if( abs(genLep_lostLep_id)==11) h_lostLepton_pt_vs_eta_el->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
      if( abs(genLep_lostLep_id)==13) h_lostLepton_pt_vs_eta_mu->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );

      if( abs(genLep_lostLep_id)==15    &&
	  genLep_lostLep_tauDecayType==3    ) h_lostLepton_pt_vs_eta_hadTau_1prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt);
      if( abs(genLep_lostLep_id)==15    &&
	  genLep_lostLep_tauDecayType==4    ) h_lostLepton_pt_vs_eta_hadTau_3prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt);


      //
      // Good PT and Eta - ie should be candidates for isoTrackVeto
      //
      if( genLep_lostLep_TLV.Pt()<5 || fabs(genLep_lostLep_TLV.Eta())>2.4 ) continue;
      
      
      if( abs(genLep_lostLep_id)==11) h_lostLepton_pt_vs_eta_goodPtEta_el->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt);
      if( abs(genLep_lostLep_id)==13) h_lostLepton_pt_vs_eta_goodPtEta_mu->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt);
      if( abs(genLep_lostLep_id)==15    &&
	  genLep_lostLep_tauDecayType==3    ) h_lostLepton_pt_vs_eta_goodPtEta_hadTau_1prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt);
      if( abs(genLep_lostLep_id)==15    &&
	  genLep_lostLep_tauDecayType==4    ) h_lostLepton_pt_vs_eta_goodPtEta_hadTau_3prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt);

	
 
      //
      // Find pfCandidate that is matched to the "lostLepton"
      //

      // Match pfMuons to genLostMuons
      TLorentzVector pfMu_matchedTo_genLostMu_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfMu_matchedTo_genLostMu_idx = -99;
      int pfMu_matchedTo_genLostMu_pdgId = -99;
      double min_dr_pfMu_genLostMu=99.9;

      // Match pfElectrons to genLostElectrons
      TLorentzVector pfEl_matchedTo_genLostEl_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfEl_matchedTo_genLostEl_idx = -99;
      int pfEl_matchedTo_genLostEl_pdgId = -99;
      double min_dr_pfEl_genLostEl=99.9;
            
      // Match pfHadrons to genLostHadronicTaus
      TLorentzVector pfHad_matchedTo_genLostHadTau_1prong_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfHad_matchedTo_genLostHadTau_1prong_idx = -99;
      int pfHad_matchedTo_genLostHadTau_1prong_pdgId = -99;
      double min_dr_pfHad_genLostHadTau_1prong=99.9;

      // Match pfHadrons to genLostHadronicTaus
      TLorentzVector pfHad_matchedTo_genLostHadTau_3prong_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfHad_matchedTo_genLostHadTau_3prong_idx = -99;
      int pfHad_matchedTo_genLostHadTau_3prong_pdgId = -99;
      double min_dr_pfHad_genLostHadTau_3prong=99.9;


      // Match any pfCand to the genLostMuon
      TLorentzVector pfCand_matchedTo_genLostMu_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfCand_matchedTo_genLostMu_idx = -99;
      int pfCand_matchedTo_genLostMu_pdgId = -99;
      double min_dr_pfCand_genLostMu=99.9;

      // Match any pfCand to the genLostElectron
      TLorentzVector pfCand_matchedTo_genLostEl_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfCand_matchedTo_genLostEl_idx = -99;
      int pfCand_matchedTo_genLostEl_pdgId = -99;
      double min_dr_pfCand_genLostEl=99.9;

      // Match any pfCand to the genLostHadronicTau 1prong
      TLorentzVector pfCand_matchedTo_genLostHadTau_1prong_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfCand_matchedTo_genLostHadTau_1prong_idx = -99;
      int pfCand_matchedTo_genLostHadTau_1prong_pdgId = -99;
      double min_dr_pfCand_genLostHadTau_1prong=99.9;

      // Match any pfCand to the genLostHadronicTau 3prong
      TLorentzVector pfCand_matchedTo_genLostHadTau_3prong_TLV( 0.0, 0.0, 0.0, 0.0 );
      int pfCand_matchedTo_genLostHadTau_3prong_idx = -99;
      int pfCand_matchedTo_genLostHadTau_3prong_pdgId = -99;
      double min_dr_pfCand_genLostHadTau_3prong=99.9;

      
      // Loop over pfCandidates
      for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){

	TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
	temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	
	if( temp.DeltaR( selLep_TLV) <= dr_selLep ) continue;
	if( isoTracks_dz().at(iPFCand ) > 0.1 ) continue;
	
	if( abs(isoTracks_pdgId().at(iPFCand))!=11 && abs(isoTracks_pdgId().at(iPFCand))!=13 && isoTracks_charge().at(iPFCand)*selLep_charge>0 ) continue;

	double dr = temp.DeltaR( genLep_lostLep_TLV );

	// minDR match pfElectrons to genLost Electrons
	if( abs(genLep_lostLep_id)==11 && abs(isoTracks_pdgId().at(iPFCand))==11){
	  
	  if( dr<min_dr_pfEl_genLostEl ){	  
	    min_dr_pfEl_genLostEl = dr;
	    pfEl_matchedTo_genLostEl_TLV = temp;
	    pfEl_matchedTo_genLostEl_idx = iPFCand;
	    pfEl_matchedTo_genLostEl_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if minDr
	} // end case of pfElectron and genLost Electrons


	// minDr match pfMuons to genLost Muons
	if( abs(genLep_lostLep_id)==13 && abs(isoTracks_pdgId().at(iPFCand))==13){

	  if( dr<min_dr_pfMu_genLostMu ){
	    min_dr_pfMu_genLostMu = dr;
	    pfMu_matchedTo_genLostMu_TLV = temp;
	    pfMu_matchedTo_genLostMu_idx = iPFCand;
	    pfMu_matchedTo_genLostMu_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if min dr
	} // end case of pfMuon and genLost Muons 
	

	// minDr match pfHadrons to genLost 1 prong Hadronic Taus
	if( abs(genLep_lostLep_id)==15 &&
	    abs(isoTracks_pdgId().at(iPFCand))!=11 && abs(isoTracks_pdgId().at(iPFCand))!=13 &&
	    genLep_lostLep_tauDecayType==3 ){

	  if( dr<min_dr_pfHad_genLostHadTau_1prong ){
	    min_dr_pfHad_genLostHadTau_1prong = dr;
	    pfHad_matchedTo_genLostHadTau_1prong_TLV = temp;
	    pfHad_matchedTo_genLostHadTau_1prong_idx = iPFCand;
	    pfHad_matchedTo_genLostHadTau_1prong_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if min dr
	} // end case of pfHadron and genLost 1 prong Hadronic Tau


	// minDr match pfHadrons to genLost 3 prong Hadronic Taus
	if( abs(genLep_lostLep_id)==15 &&
	    abs(isoTracks_pdgId().at(iPFCand))!=11 && abs(isoTracks_pdgId().at(iPFCand))!=13 &&
	    genLep_lostLep_tauDecayType==4 ){

	  if( dr<min_dr_pfHad_genLostHadTau_3prong ){
	    min_dr_pfHad_genLostHadTau_3prong = dr;
	    pfHad_matchedTo_genLostHadTau_3prong_TLV = temp;
	    pfHad_matchedTo_genLostHadTau_3prong_idx = iPFCand;
	    pfHad_matchedTo_genLostHadTau_3prong_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if min dr
	} // end case of pfHadron and genLost 3 prong Hadronic Tau


	// minDR match any pfHad to genLost Electrons
	if( abs(genLep_lostLep_id)==11 ){
	  
	  if( abs(isoTracks_pdgId().at(iPFCand))==13 ) continue;

	  if( dr<min_dr_pfCand_genLostEl ){	  
	    min_dr_pfCand_genLostEl = dr;
	    pfCand_matchedTo_genLostEl_TLV = temp;
	    pfCand_matchedTo_genLostEl_idx = iPFCand;
	    pfCand_matchedTo_genLostEl_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if minDr
	} // end case of any pfCandidate and genLost Electrons


	// minDr match any pfCand to genLost Muons
	if( abs(genLep_lostLep_id)==13 ){

	  if( abs(isoTracks_pdgId().at(iPFCand))==11 ) continue;

	  if( dr<min_dr_pfCand_genLostMu ){
	    min_dr_pfCand_genLostMu = dr;
	    pfCand_matchedTo_genLostMu_TLV = temp;
	    pfCand_matchedTo_genLostMu_idx = iPFCand;
	    pfCand_matchedTo_genLostMu_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if min dr
	} // end case of any pfCandidate and genLost Muons 
	

	// minDr match any pfCand to genLost 1 prong Hadronic Taus
	if( abs(genLep_lostLep_id)==15 &&
	    genLep_lostLep_tauDecayType==3 ){

	  if( dr<min_dr_pfCand_genLostHadTau_1prong ){
	    min_dr_pfCand_genLostHadTau_1prong = dr;
	    pfCand_matchedTo_genLostHadTau_1prong_TLV = temp;
	    pfCand_matchedTo_genLostHadTau_1prong_idx = iPFCand;
	    pfCand_matchedTo_genLostHadTau_1prong_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if min dr
	} // end case of pfHadron and genLost 1 prong Hadronic Tau

	
	// minDr match any pfCand to genLost 3 prong Hadronic Taus
	if( abs(genLep_lostLep_id)==15 &&
	    genLep_lostLep_tauDecayType==4 ){

	  if( dr<min_dr_pfCand_genLostHadTau_3prong ){
	    min_dr_pfCand_genLostHadTau_3prong = dr;
	    pfCand_matchedTo_genLostHadTau_3prong_TLV = temp;
	    pfCand_matchedTo_genLostHadTau_3prong_idx = iPFCand;
	    pfCand_matchedTo_genLostHadTau_3prong_pdgId = isoTracks_pdgId().at(iPFCand);
	  } // end if min dr
	} // end case of pfHadron and genLost 3 prong Hadronic Tau
	
	
	
      }

      // Define minDr matching cut
      double minDr_matching_cut = 0.1;

      //
      // Store minDr Values of case where pfLep is matched to like flavour genLost Lepton
      //
     
      if( abs(genLep_lostLep_id)==11 ){
	
	h_minDR_pfEl_genLostEl->Fill( std::min( min_dr_pfEl_genLostEl, dr_max), wgt );

	if( min_dr_pfEl_genLostEl < minDr_matching_cut ){

	  h_genLostEl_matchedTo_pfEl_pt_vs_eta->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfEl_matchedTo_genLostEl_pt_vs_eta->Fill( std::min( (double)fabs(pfEl_matchedTo_genLostEl_TLV.Eta()), eta_max), std::min( (double)pfEl_matchedTo_genLostEl_TLV.Pt(), pt_max), wgt );
	  
	} // end if passes minDr pF matching cut
	else{
	  h_genLostEl_unMatchedTo_pfEl_pt_vs_eta->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );

	  // Match pfHadrons to genLostElectrons, when no pfEl is found
	  TLorentzVector pfHad_matchedTo_genLostEl_noPfElMatch_TLV( 0.0, 0.0, 0.0, 0.0 );
	  int pfHad_matchedTo_genLostEl_noPfElMatch_idx = -99;
	  int pfHad_matchedTo_genLostEl_noPfElMatch_pdgId = -99;
	  double pfHad_matchedTo_genLostEl_noPfElMatch_charge = 0;
	  double min_dr_pfHad_genLostEl_noPfElMatch=99.9;

	  // Loop over pfCandidates
	  for(int iPFCand=0; iPFCand<(int)isoTracks_p4().size(); iPFCand++){

	    TLorentzVector temp( 0.0, 0.0, 0.0, 0.0);
	    temp.SetPxPyPzE( isoTracks_p4().at(iPFCand).Px(), isoTracks_p4().at(iPFCand).Py(), isoTracks_p4().at(iPFCand).Pz(), isoTracks_p4().at(iPFCand).E() );
	    if( temp.DeltaR( selLep_TLV) < dr_selLep ) continue;
	    if( abs(isoTracks_pdgId().at(iPFCand))==11 ) continue;
	    if( abs(isoTracks_pdgId().at(iPFCand))==13 ) continue;
	    if( isoTracks_p4().at(iPFCand).Pt()>10 && isoTracks_absIso().at(iPFCand)<0.1 && isoTracks_charge().at(iPFCand)*selLep_charge<0 ) continue;
	    
	    double dr = temp.DeltaR( genLep_lostLep_TLV );
	    if( dr<min_dr_pfHad_genLostEl_noPfElMatch ){
	      min_dr_pfHad_genLostEl_noPfElMatch = dr;
	      pfHad_matchedTo_genLostEl_noPfElMatch_TLV = temp;
	      pfHad_matchedTo_genLostEl_noPfElMatch_charge = isoTracks_charge().at(iPFCand);
	    } // end if minDr

	  } // end loop over pfHadrons
	  
	  h_minDR_pfHad_genLostEl_noPfElMatch->Fill( std::min( min_dr_pfHad_genLostEl_noPfElMatch, dr_max ), wgt );

	  
	} // end if NOT passing minDr pF matching cut

      } // end if pfElectron is matched to genLostElectron

      
      
            
      // pfMuon matched to genLostMuon
      if( abs(genLep_lostLep_id)==13 ){

	h_minDR_pfMu_genLostMu->Fill( std::min( min_dr_pfMu_genLostMu, dr_max), wgt );
	if( min_dr_pfMu_genLostMu < minDr_matching_cut ){

	  h_genLostMu_matchedTo_pfMu_pt_vs_eta->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfMu_matchedTo_genLostMu_pt_vs_eta->Fill( std::min( (double)fabs(pfMu_matchedTo_genLostMu_TLV.Eta()), eta_max), std::min( (double)pfMu_matchedTo_genLostMu_TLV.Pt(), pt_max), wgt );
	  
	} // end if passes minDr pF matching cut

      } // end if pfMuon is matched to genLostMuon

      
      
      // pfHad matched to genLostHadTau, 1 prong
      if( abs(genLep_lostLep_id)==15 && genLep_lostLep_tauDecayType==3 ){

	h_minDR_pfHad_genLostHadTau_1prong->Fill( std::min( min_dr_pfHad_genLostHadTau_1prong, dr_max), wgt );
	if( min_dr_pfHad_genLostHadTau_1prong < minDr_matching_cut ){
	  
	  h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_1prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_1prong->Fill( std::min( (double)fabs(pfHad_matchedTo_genLostHadTau_1prong_TLV.Eta()), eta_max), std::min( (double)pfHad_matchedTo_genLostHadTau_1prong_TLV.Pt(), pt_max), wgt );
	  
	} // end if passes minDr pF matching cut

      } // end if pfHad is matched to genLostHadTau 1 prong
      


      // pfHad matched to genLostHadTau, 3 prong
      if( abs(genLep_lostLep_id)==15 && genLep_lostLep_tauDecayType==4 ){

	h_minDR_pfHad_genLostHadTau_3prong->Fill( std::min( min_dr_pfHad_genLostHadTau_3prong, dr_max), wgt );
	if( min_dr_pfHad_genLostHadTau_3prong < minDr_matching_cut ){
	  
	  h_genLostHadTau_matchedTo_pfHad_pt_vs_eta_3prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfHad_matchedTo_genLostHadTau_pt_vs_eta_3prong->Fill( std::min( (double)fabs(pfHad_matchedTo_genLostHadTau_3prong_TLV.Eta()), eta_max), std::min( (double)pfHad_matchedTo_genLostHadTau_3prong_TLV.Pt(), pt_max), wgt );
	  
	} // end if passes minDr pF matching cut

      } // end if pfHad is matched to genLostHadTau 3 prong
      
      

      //
      // Store minDr Values of case where any pfCand is matched to genLost Leptons
      //
      if( abs(genLep_lostLep_id)==11 ){
	
	h_minDR_pfCand_genLostEl->Fill( std::min( min_dr_pfCand_genLostEl, dr_max), wgt );
	if( min_dr_pfCand_genLostEl < minDr_matching_cut ){

	  h_genLostEl_matchedTo_pfCand_pt_vs_eta->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfCand_matchedTo_genLostEl_pt_vs_eta->Fill( std::min( (double)fabs(pfCand_matchedTo_genLostEl_TLV.Eta()), eta_max), std::min( (double)pfCand_matchedTo_genLostEl_TLV.Pt(), pt_max), wgt );
	  
	} // end if passes minDr pF matching cut

      } // end if pfCand is matched to genLostElectron


      if( abs(genLep_lostLep_id)==13 ){
	
	h_minDR_pfCand_genLostMu->Fill( std::min( min_dr_pfCand_genLostMu, dr_max), wgt );
	if( min_dr_pfCand_genLostMu < minDr_matching_cut ){

	  h_genLostMu_matchedTo_pfCand_pt_vs_eta->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfCand_matchedTo_genLostMu_pt_vs_eta->Fill( std::min( (double)fabs(pfCand_matchedTo_genLostMu_TLV.Eta()), eta_max), std::min( (double)pfCand_matchedTo_genLostMu_TLV.Pt(), pt_max), wgt );

	  
	} // end if passes minDr pF matching cut

      } // end if pfCand is matched to genLostMuon

      
      
      if( abs(genLep_lostLep_id)==15 &&
	  genLep_lostLep_tauDecayType==3){
	
	h_minDR_pfCand_genLostHadTau_1prong->Fill( std::min( min_dr_pfCand_genLostHadTau_1prong, dr_max), wgt );
	if( min_dr_pfCand_genLostHadTau_1prong < minDr_matching_cut ){

	  h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_1prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_1prong->Fill( std::min( (double)fabs(pfCand_matchedTo_genLostHadTau_1prong_TLV.Eta()), eta_max), std::min( (double)pfCand_matchedTo_genLostHadTau_1prong_TLV.Pt(), pt_max), wgt );

	} // end if passes minDr pF matching cut

      } // end if pfCand is matched to 1 prong genLostHadTau
      
      

      if( abs(genLep_lostLep_id)==15 &&
	  genLep_lostLep_tauDecayType==4){
	
	h_minDR_pfCand_genLostLep_hadTau_3prong->Fill( std::min( min_dr_pfCand_genLostHadTau_3prong, dr_max), wgt );
	if( min_dr_pfCand_genLostHadTau_3prong < minDr_matching_cut ){

	  h_genLostHadTau_matchedTo_pfCand_pt_vs_eta_3prong->Fill( std::min( (double)fabs(genLep_lostLep_TLV.Eta()), eta_max), std::min( (double)genLep_lostLep_TLV.Pt(), pt_max), wgt );
	  h_pfCand_matchedTo_genLostHadTau_pt_vs_eta_3prong->Fill( std::min( (double)fabs(pfCand_matchedTo_genLostHadTau_3prong_TLV.Eta()), eta_max), std::min( (double)pfCand_matchedTo_genLostHadTau_3prong_TLV.Pt(), pt_max), wgt );

	} // end if passes minDr pF matching cut

      } // end if pfCand is matched to 3 prong genLostHadTau
      
      
           
            
      
      // Check relTrackIso
      if( pfEl_matchedTo_genLostEl_idx>0 ){
	
	h_relTrackIso_pfEl_matchedTo_genLostEl->Fill( std::min( (double)(isoTracks_absIso().at( pfEl_matchedTo_genLostEl_idx )/ pfEl_matchedTo_genLostEl_TLV.Pt()), relIso_max ), wgt);
	
	h_relTrackIso_vs_pT_pfEl_matchedTo_genLostEl->Fill( std::min( (double)isoTracks_p4().at( pfEl_matchedTo_genLostEl_idx ).Pt(), pt_max ), std::min( (double)(isoTracks_absIso().at( pfEl_matchedTo_genLostEl_idx )/ pfEl_matchedTo_genLostEl_TLV.Pt()), relIso_max ), wgt);
	
      }


      if( pfMu_matchedTo_genLostMu_idx>0 ){
	
	h_relTrackIso_pfLep_matchedTo_genLostLep_mu->Fill( std::min( (double)(isoTracks_absIso().at( pfMu_matchedTo_genLostMu_idx )/ pfMu_matchedTo_genLostMu_TLV.Pt()), relIso_max ), wgt);
	  
	h_relTrackIso_vs_pT_pfMu_matchedTo_genLostMu->Fill( std::min( (double)isoTracks_p4().at( pfMu_matchedTo_genLostMu_idx ).Pt(), pt_max ), std::min( (double)(isoTracks_absIso().at( pfMu_matchedTo_genLostMu_idx )/ pfMu_matchedTo_genLostMu_TLV.Pt()), relIso_max ), wgt );
      	
      }


      if( pfHad_matchedTo_genLostHadTau_1prong_idx>0 ){
	
	h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_1prong->Fill( std::min( (double)(isoTracks_absIso().at( pfHad_matchedTo_genLostHadTau_1prong_idx )/ pfHad_matchedTo_genLostHadTau_1prong_TLV.Pt()), relIso_max ), wgt);
	  
	h_relTrackIso_vs_pT_pfHad_matchedTo_genLostHadTau_1prong->Fill( std::min( (double)isoTracks_p4().at( pfHad_matchedTo_genLostHadTau_1prong_idx ).Pt(), pt_max ), std::min( (double)(isoTracks_absIso().at( pfHad_matchedTo_genLostHadTau_1prong_idx )/ pfHad_matchedTo_genLostHadTau_1prong_TLV.Pt()), relIso_max ), wgt);

      }


      if( pfHad_matchedTo_genLostHadTau_3prong_idx>0 ){
       
	h_relTrackIso_pfHad_matchedTo_genLostLep_hadTau_3prong->Fill( std::min( (double)(isoTracks_absIso().at( pfHad_matchedTo_genLostHadTau_3prong_idx )/ pfHad_matchedTo_genLostHadTau_3prong_TLV.Pt()), relIso_max), wgt);
		
      }

      
            
    
       
          
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
  // Track Iso Veto Optimization
  //
  const int nTrkIsoEffBins = (int)trkIsoVeto_nEvents_passCut.size();
  
  TH1D *h_trkIso_optimization_eff = new TH1D("h_trkIso_optimization_eff", "Efficiencies for various trk iso veto working points", nTrkIsoEffBins, 0, nTrkIsoEffBins);
  h_trkIso_optimization_eff->SetDirectory(out_file);
  
  int wp_count=1;
  for(double pfMuIso=0.1; pfMuIso<=0.5; pfMuIso+=0.1){
    for(int pfMuQVeto=0; pfMuQVeto<=1; pfMuQVeto++){
      for(double pfElIso=0.1; pfElIso<=0.5; pfElIso+=0.1){
	for(int pfElQVeto=0; pfElQVeto<=1; pfElQVeto++){
	  for(int pfAbsIso=0; pfAbsIso<=1; pfAbsIso++){
	    for(double pfHadIso=0.1; pfHadIso<=0.4; pfHadIso+=0.1){
		    
	      TString vetoName = "";
	      vetoName+= "pfMuIso=";
	      vetoName+=Form("%.1f",pfMuIso);
	      vetoName+= ", ";
	      vetoName+= "pfMuQVeto=";
	      vetoName+=Form("%d",pfMuQVeto);
	      vetoName+= ", ";
	      vetoName+= "pfElIso=";
	      vetoName+=Form("%.1f",pfElIso);
	      vetoName+= ", ";
	      vetoName+= "pfElQVeto=";
	      vetoName+=Form("%d",pfElQVeto);
	      vetoName+= ", ";
	      vetoName+= "pfAbsIso=";
	      vetoName+=Form("%d",pfAbsIso);
	      vetoName+= ", ";
	      vetoName+= "pfHadIso=";
	      vetoName+=Form("%.1f",pfHadIso);

			    
	      if( pfMuIso==0.2 && pfMuQVeto==0 && pfElIso==0.2 && pfElQVeto==0 && pfAbsIso==0.0 && pfHadIso==0.1 ) cout << "nevents passed std trackIsoVet cut:" <<  vetoName << " = " << trkIsoVeto_nEvents_passCut[ vetoName ] << endl;
		
	      if( pfMuIso==0.1 && pfMuQVeto==0 && pfElIso==0.1 && pfElQVeto==1 && pfAbsIso==1.0 && pfHadIso==0.1 ) cout << "nevents passed std trackIsoVet cut:" <<  vetoName << " = " << trkIsoVeto_nEvents_passCut[ vetoName ] << endl;
		
	      h_trkIso_optimization_eff->GetXaxis()->SetBinLabel(wp_count, vetoName);
	      double wp_eff = (double)trkIsoVeto_nEvents_passCut[ vetoName ]/nEvents_pass_baseline;
	      h_trkIso_optimization_eff->Fill(vetoName, wp_eff);

	      wp_count++;

	    }		
	  }
	}
      }
    }
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
  cout << "Selection Cutflow, weighted for 10fb" << endl;
  cout << "    nEvents Processed                    = " << nEventsChain << endl;
  cout << "    nEvents Pass >1 Vertex (wgt)         = " << nEvents_pass_nVtx << "(" << nEvents_pass_nVtx_wgt << "), Eff: " << 1.0 << endl;
  cout << "    nEvents Pass >=1 Good Lepton (wgt)   = " << nEvents_pass_nGoodLep << "(" <<  nEvents_pass_nGoodLep_wgt << "), Eff: " <<  nEvents_pass_nGoodLep_wgt/nEvents_pass_nVtx_wgt << endl;
  cout << "    nEvents Pass 1 Selected Lepton (wgt) = " << nEvents_pass_nSelLep << " (" << nEvents_pass_nSelLep_wgt << "), Eff: " << nEvents_pass_nSelLep_wgt/nEvents_pass_nGoodLep_wgt << endl;
  cout << "    nEvents Pass Track Veto (wgt)        = " << nEvents_pass_trackVeto << " (" << nEvents_pass_trackVeto_wgt << "), Eff: " << nEvents_pass_trackVeto_wgt/nEvents_pass_nSelLep_wgt << endl;
  cout << "    nEvents Pass Tau Veto (wgt)          = " << nEvents_pass_tauVeto << " (" <<  nEvents_pass_tauVeto_wgt << "), Eff: " <<  nEvents_pass_tauVeto_wgt/nEvents_pass_trackVeto_wgt << endl;
  cout << "    nEvents Pass >=4 Selected Jets (wgt) = " << nEvents_pass_nJets << " (" << nEvents_pass_nJets_wgt << "), Eff: " << nEvents_pass_nJets_wgt/nEvents_pass_tauVeto_wgt << endl;
  cout << "    nEvents Pass >=1 BTagged Jets (wgt)  = " << nEvents_pass_nBJets << " (" << nEvents_pass_nBJets_wgt << "), Eff: " << nEvents_pass_nBJets_wgt/nEvents_pass_nJets_wgt << endl;
  cout << "    nEvents Pass Met>200.0 (wgt)         = " << nEvents_pass_met << " (" << nEvents_pass_met_wgt << "), Eff: " << nEvents_pass_met_wgt/nEvents_pass_nBJets_wgt << endl;
  cout << "    nEvents Pass MT>120.0 (wgt)          = " << nEvents_pass_mtCut << " (" << nEvents_pass_mtCut_wgt << "), Eff: " << nEvents_pass_mtCut_wgt/nEvents_pass_met_wgt << endl;
  cout << "    nEvents Pass minDeltaPhi>0.8 (wgt)   = " << nEvents_pass_minDPhi << " (" << nEvents_pass_minDPhi_wgt << "), Eff: " << nEvents_pass_minDPhi_wgt/nEvents_pass_mtCut_wgt << endl;
  cout << "    nEvents Pass Chi2<5.0 (wgt)          = " << nEvents_pass_chi2 << " (" << nEvents_pass_chi2_wgt << "), Eff: " << nEvents_pass_chi2_wgt/nEvents_pass_minDPhi_wgt << endl;
  cout << "=====================================================" << endl;

  cout << "    nEvents Pass TrackIsolation Veto (wgt)   = " << passTrackIso_veto << " (" << passTrackIsoVeto_wgt << "), Eff: " << passTrackIsoVeto_wgt/nEvents_pass_baseline_wgt << endl;
  cout << "    nEvents Pass TrackIso Veto N-1 Ele (wgt) = " << passTrackIso_veto_nMinus1_el << " (" << passTrackIso_veto_nMinus1_el_wgt << "), Eff:" << passTrackIso_veto_nMinus1_el_wgt/nEvents_pass_baseline_wgt << endl;
  cout << "    nEvents Pass TrackIso Veto N-1 Mu (wgt)  = " <<  passTrackIso_veto_nMinus1_mu << " (" << passTrackIso_veto_nMinus1_mu_wgt << "), Eff:" << passTrackIso_veto_nMinus1_mu_wgt/nEvents_pass_baseline_wgt << endl;
  cout << "    nEvents Pass TrackIso Veto N-1 Had (wgt) = " << passTrackIso_veto_nMinus1_had << " (" << passTrackIso_veto_nMinus1_had_wgt << "), Eff:" << passTrackIso_veto_nMinus1_had_wgt/nEvents_pass_baseline_wgt << endl;
  cout << endl;
  cout << "    nEvents Pass TrackIso Veto with Ele Q Veto (wgt) = " << passTrackIso_veto_with_elQVeto << " (" << passTrackIso_veto_with_elQVeto_wgt << "), Eff:" << passTrackIso_veto_with_elQVeto_wgt/nEvents_pass_baseline_wgt << endl;
  cout << "    nEvents pass Track Iso Veto with Ele Q Veto and AbsIso<6.0 for pT>60 (wgt) = " << passTrackIso_veto_with_elQVeto_absIso << " (" << passTrackIso_veto_with_elQVeto_absIso_wgt << "), Eff:" << passTrackIso_veto_with_elQVeto_absIso_wgt/nEvents_pass_baseline_wgt << endl;
  cout << endl;
  cout << "    nEvents pass Track Iso Veto with pfLepIso<0.1 LepQVeto AbsIso (wgt) = " << passTrackIso_veto_optimized << " (" << passTrackIso_veto_optimized_wgt << "), Eff: " << passTrackIso_veto_optimized_wgt/nEvents_pass_baseline_wgt << endl;
  cout << "    nEvents pass Track Iso Veto with pfLepIso<0.1 ElQVeto AbsIso (wgt)  = " << passTrackIso_veto_optimized_noMuQVeto << " (" << passTrackIso_veto_optimized_noMuQVeto_wgt << "), Eff: " << passTrackIso_veto_optimized_noMuQVeto_wgt/nEvents_pass_baseline_wgt << endl;


  cout << "=====================================================" << endl;
  cout << "  Signal Regions: Low DeltaM, weighted events only " << endl;
  cout << "    nEvents Pass Met>150           = " << nEvents_pass_met150_wgt << endl;
  cout << "    nEvents Pass Met>200           = " << nEvents_pass_met200_wgt << endl;
  cout << "    nEvents Pass Met>250           = " << nEvents_pass_met250_wgt << endl;
  cout << "    nEvents Pass Met>300           = " << nEvents_pass_met300_wgt << endl;
  cout << endl;
  cout << "  Signal Regions: High DeltaM, weighted events only " << endl;
  cout << "    nEvents Pass MT2W>200 && Met>150  = " << nEvents_pass_met150_mt2w200_wgt << endl;
  cout << "    nEvents Pass MT2W>200 && Met>200  = " << nEvents_pass_met200_mt2w200_wgt << endl;
  cout << "    nEvents Pass MT2W>200 && Met>250  = " << nEvents_pass_met250_mt2w200_wgt << endl;
  cout << "    nEvents Pass MT2W>200 && Met>300  = " << nEvents_pass_met300_mt2w200_wgt << endl;
  cout << endl;
 
  

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
