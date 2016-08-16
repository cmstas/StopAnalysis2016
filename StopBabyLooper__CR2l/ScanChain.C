// Usage:
// > root -b doAll.C

// C++
#include <iostream>
#include <vector>
#include <cmath>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TH1F.h"
#include "TCanvas.h"

// stop_1l_babyAnalyzer
#include "../StopCORE/stop_1l_babyAnalyzer.h"
#include "../StopBabyMaker/stop_variables/mt2w.h"
#include "../StopBabyMaker/stop_variables/topness.h"
#include "../../CORE/Tools/dorky/dorky.h"

using namespace std;
using namespace stop_1l;

int getRegionIndex (int njets, float modtop, float mt2w, float met);
double getLostLepTransferFactor (int njets, float modtop, float mt2w, float met);
double getLostLepOnlyLepTransferFactor (int njets, float modtop, float mt2w, float met);
double getWJetsTransferFactor (int njets, float modtop, float mt2w, float met);
bool sortByCSV ( std::pair<int, double>& p1, std::pair<int, double>& p2) { return p1.second > p2.second; }

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  bool verbose = false;
  bool remove_lep_from_met = true;
  bool use_only_e_or_mu = true;
  
  if (use_only_e_or_mu)
    cout << "only using e and mu for LL background estimate!" << endl;
  if (remove_lep_from_met)
    cout << "remove pt of second lepton from all objects involving MET!" << endl;    
  
  //
  // current integrated lumi in /fb
  //
  double lumi = 2.6;
  // double lumi = 3.99;
  
  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");


  double tt2l_sr_cnt[15];
  double tt2l_cr_cnt[15];
  double tt2l_tf[15];
  double tt2l_cr_onlyLep_cnt[15];
  double tt2l_ll_bkgd_est[15];
  double wjets_sr_cnt[15];
  double wjets_cr_cnt[15];
  double wjets_tf[15];
  double wjets_bkgd_est[15];
  double rare_bkgd_est[15];
  double tt1l_bkgd_est[15];
  double wjets_cont[15];
  int sr_cnt[15][3];
  int cr2l_cnt[15][5];
  int cr0b_cnt[15][3];  
  static const unsigned int nregions = 15;
  for (unsigned int idx = 0; idx < nregions; idx++)
  {
    tt2l_sr_cnt[idx] = 0;
    tt2l_cr_cnt[idx] = 0;
    tt2l_cr_onlyLep_cnt[idx] = 0;
    wjets_sr_cnt[idx] = 0;
    wjets_cr_cnt[idx] = 0;
    wjets_bkgd_est[idx] = 0;
    rare_bkgd_est[idx] = 0;
    tt1l_bkgd_est[idx] = 0;
    wjets_cont[idx] = 0;
    tt2l_tf[idx] = 0;
    wjets_tf[idx] = 0;
    for (unsigned int jidx = 0; jidx < 5; jidx++) {
      if (jidx < 3) {
        sr_cnt[idx][jidx] = 0;
        cr0b_cnt[idx][jidx] = 0;        
      }
      cr2l_cnt[idx][jidx] = 0;
    }
  }
  
  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  TH1F *h_tt2l_sr_cnt = new TH1F("h_tt2l_sr_cnt", "h_tt2l_sr_cnt", nregions,-0.5,nregions-0.5);
  h_tt2l_sr_cnt->Sumw2();
  h_tt2l_sr_cnt->SetDirectory(rootdir);
  TH1F *h_tt2l_cr_cnt = new TH1F("h_tt2l_cr_cnt", "h_tt2l_cr_cnt", nregions,-0.5,nregions-0.5);
  h_tt2l_cr_cnt->Sumw2();
  h_tt2l_cr_cnt->SetDirectory(rootdir);
  TH1F *h_tt2l_cr_onlyLep_cnt = new TH1F("h_tt2l_cr_onlyLep_cnt", "h_tt2l_cr_onlyLep_cnt", nregions,-0.5,nregions-0.5);
  h_tt2l_cr_onlyLep_cnt->Sumw2();
  h_tt2l_cr_onlyLep_cnt->SetDirectory(rootdir);
  TH1F *h_wjets_cr_cnt = new TH1F("h_wjets_cr_cnt", "h_wjets_cr_cnt", nregions,-0.5,nregions-0.5);
  h_wjets_cr_cnt->Sumw2();
  h_wjets_cr_cnt->SetDirectory(rootdir);
  TH1F *h_wjets_sr_cnt = new TH1F("h_wjets_sr_cnt", "h_wjets_sr_cnt", nregions,-0.5,nregions-0.5);
  h_wjets_sr_cnt->Sumw2();
  h_wjets_sr_cnt->SetDirectory(rootdir);
  
  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;


  unsigned int passes_presel = 0;
  unsigned int passes_met_mt = 0;
  unsigned int fails_ee1_selLep = 0;
  unsigned int fails_ee0_vetoLep = 0;
  unsigned int fails_trackVeto = 0;
  unsigned int fails_tauVeto = 0;
  unsigned int passes_sr_or_cr_before = 0;
  unsigned int passes_sr_or_cr_after = 0;  
  unsigned int passes_true_2l = 0;
  
  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("t");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    babyAnalyzer.Init(tree);
    
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();

    bool is_wjets = false;
    bool is_wnjets_nupt = false;
    bool is_wnjets = false;    
    bool is_rare = false;
    bool is_tt1l = false;
    bool tf_calc = false;
    
    for( unsigned int event = 0; event < nEventsTree; ++event) {      
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      babyAnalyzer.GetEntry(event);
      ++nEventsTotal;

      if (event == 0) {
        if (babyAnalyzer.dataset().find("WJetsToLNu") != std::string::npos) is_wjets = true;
        else is_wjets = false;
        
        if (babyAnalyzer.dataset().find("NuPt-200") != std::string::npos) {
          is_wnjets_nupt = true;
          is_wnjets = false;
        }
        else if (babyAnalyzer.dataset().find("W1JetsToLNu") != std::string::npos ||
                 babyAnalyzer.dataset().find("W2JetsToLNu") != std::string::npos ||
                 babyAnalyzer.dataset().find("W3JetsToLNu") != std::string::npos ||
                 babyAnalyzer.dataset().find("W4JetsToLNu") != std::string::npos) {
          is_wnjets = true;
          is_wnjets_nupt = false;
        }
        else {
          is_wnjets = false;
          is_wnjets_nupt = false;
        }

        if (babyAnalyzer.dataset().find("TTZ") != std::string::npos ||
            babyAnalyzer.dataset().find("WZTo1L3Nu") != std::string::npos) is_rare = true;
        else is_rare = false;

        if (babyAnalyzer.dataset().find("SingleLeptFromT") != std::string::npos) is_tt1l = true;
        else is_tt1l = false;
        
        if (babyAnalyzer.is_data()) {
          if (!tf_calc) {
            for (unsigned int idx = 0; idx < nregions; idx++) {
              if (tt2l_cr_cnt[idx] > 0.00001)
                tt2l_tf[idx] = tt2l_sr_cnt[idx] / tt2l_cr_cnt[idx];
              if (wjets_cr_cnt[idx] > 0.00001) {
                wjets_tf[idx] = wjets_sr_cnt[idx] / wjets_cr_cnt[idx];
                wjets_cont[idx] = wjets_cr_cnt[idx] / (wjets_cr_cnt[idx] + wjets_cont[idx]);
              }
            }
            tf_calc = true;
          }
        }
      }

      // Progress
      stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );

      // Analysis Code

      if (is_wnjets && babyAnalyzer.genmet() > 200.) continue;
      
      bool passes_met_filter = false;
      bool passes_met_or_1l_trigger = false;
      bool passes_good_vtx = false;
      bool passes_ee1_selLep = false;
      bool passes_ge1_selLep = false;      
      bool passes_ee0_vetoLep = false;
      bool passes_trackVeto = false;
      bool passes_tauVeto = false;
      bool passes_minDphi = false;
      bool passes_ge2jets = false;
      bool passes_ge1btag = false;
      
      if (!babyAnalyzer.is_data()) {
        passes_met_filter = true;
        passes_met_or_1l_trigger = true;
      }
      else {
        duplicate_removal::DorkyEventIdentifier id = { babyAnalyzer.run(), babyAnalyzer.evt(), babyAnalyzer.ls() };
        if (duplicate_removal::is_duplicate(id) ) continue;
        if (babyAnalyzer.filt_met()) passes_met_filter = true;
        if (babyAnalyzer.HLT_MET() || babyAnalyzer.HLT_SingleMu() || babyAnalyzer.HLT_SingleEl()) passes_met_or_1l_trigger = true;
      }

      if (babyAnalyzer.nvtxs() >= 1) passes_good_vtx = true;
      if (babyAnalyzer.ngoodleps() == 1) passes_ee1_selLep = true;
      if (babyAnalyzer.ngoodleps() >= 1) passes_ge1_selLep = true;      
      if (babyAnalyzer.nvetoleps() == 1) passes_ee0_vetoLep = true;
      if (babyAnalyzer.PassTrackVeto()) passes_trackVeto = true;
      if (babyAnalyzer.PassTauVeto()) passes_tauVeto = true;
      if (babyAnalyzer.ngoodjets() >= 2) passes_ge2jets = true;
      if (babyAnalyzer.ngoodbtags() >=1 ) passes_ge1btag = true;
      if (babyAnalyzer.mindphi_met_j1_j2()>=0.8) passes_minDphi = true;
      
      bool passes_preselection = false;
      passes_preselection = (passes_met_filter &&
                             passes_met_or_1l_trigger &&
                             passes_good_vtx &&
                             passes_ge2jets &&
                             passes_ge1_selLep);
      
      if (!passes_preselection) continue;
      ++passes_presel;     
            
      bool is_true_2l = false;
      if (babyAnalyzer.is_data()) is_true_2l = true;
      else if (babyAnalyzer.is2lep() && !babyAnalyzer.isZtoNuNu() && !babyAnalyzer.is_data()) is_true_2l = true;
      
      bool is_dilep = false;
      bool is_dilep_emu = false;
      if (babyAnalyzer.ngoodleps() >= 2) {
        is_dilep = true;
        is_dilep_emu = true;
      }
      else if (babyAnalyzer.ngoodleps() == 1 && babyAnalyzer.nvetoleps() >= 2 && babyAnalyzer.lep2_p4().Pt()>10) {
        is_dilep = true;
        is_dilep_emu = true;
      }
      else if (babyAnalyzer.ngoodleps() == 1 && !babyAnalyzer.PassTrackVeto() ) is_dilep = true;
      else if (babyAnalyzer.ngoodleps() == 1 && !babyAnalyzer.PassTauVeto()) is_dilep = true;

      double met = babyAnalyzer.pfmet();
      double met_phi = babyAnalyzer.pfmet_phi();
      if (is_dilep && remove_lep_from_met) {
        double pfmet_x = babyAnalyzer.pfmet() * std::cos(babyAnalyzer.pfmet_phi());
        double pfmet_y = babyAnalyzer.pfmet() * std::sin(babyAnalyzer.pfmet_phi());

        double remove_x = 0.;
        double remove_y = 0.;
        if (babyAnalyzer.ngoodleps() > 1 || (babyAnalyzer.ngoodleps() == 1 && babyAnalyzer.nvetoleps() > 1 && babyAnalyzer.lep2_p4().pt()>10)) {
          remove_x = babyAnalyzer.lep2_p4().px();
          remove_y = babyAnalyzer.lep2_p4().py();
        }

        pfmet_x += remove_x;
        pfmet_y += remove_y;
        double new_pfmet = std::sqrt(pfmet_x*pfmet_x + pfmet_y*pfmet_y);
        if (new_pfmet < 150.) continue;
        double new_pfmet_phi = std::atan2(pfmet_y,pfmet_x);
        double dphi = std::acos(std::cos(new_pfmet_phi - babyAnalyzer.lep1_p4().phi()));        
        double new_mt = std::sqrt(2*babyAnalyzer.lep1_p4().pt()*new_pfmet*(1 - std::cos(dphi)));
        if (new_mt < 150) continue;
        met = new_pfmet;
        met_phi = new_pfmet_phi;

        double dphi1 = std::acos(std::cos(new_pfmet_phi - babyAnalyzer.ak4pfjets_p4().at(0).phi()));
        double dphi2 = std::acos(std::cos(new_pfmet_phi - babyAnalyzer.ak4pfjets_p4().at(1).phi()));
        double dphi_min = std::min(dphi1, dphi2);
        if (dphi_min < 0.8) continue;
      
	//std::cout << "  Evt, Run, Ls = " << babyAnalyzer.evt() << ", " << babyAnalyzer.run() << ", " << babyAnalyzer.ls() << std::endl;
	//std::cout << "    MET = " << new_pfmet << std::endl;
	//std::cout << "    MET_phi = " << new_pfmet_phi << std::endl;
	//std::cout << "    MT = " << new_mt << std::endl;
	//std::cout << "    minDPhiJ1J2 = " << dphi_min << std::endl;
      
      }
      else {
        if (babyAnalyzer.pfmet() < 150) continue;
        if (babyAnalyzer.mt_met_lep() < 150) continue;
        if (babyAnalyzer.mindphi_met_j1_j2() < 0.8) continue;
        ++passes_met_mt;
      }

      
      
      //
      // check if it passes the SR selection
      //
      bool passes_SR_preselection = (passes_ee1_selLep &&
                                     passes_ee0_vetoLep &&
                                     passes_trackVeto &&
                                     passes_tauVeto &&
                                     passes_ge1btag);
            
      if (!passes_ee1_selLep) ++fails_ee1_selLep;        
      else if (!passes_ee0_vetoLep) ++fails_ee0_vetoLep;
      else if (!passes_trackVeto) ++fails_trackVeto;
      else if (!passes_tauVeto) ++fails_tauVeto;
      
      bool passes_tt2l_CR_preselection = passes_preselection && passes_ge1btag && is_dilep;
      if (use_only_e_or_mu) passes_tt2l_CR_preselection = (passes_preselection && passes_ge1btag && is_dilep_emu);
      bool passes_wjets_CR_preselection = (passes_preselection && passes_ee1_selLep && passes_ee0_vetoLep && passes_trackVeto && passes_tauVeto && (babyAnalyzer.ngoodbtags() == 0));
      
      double mt2w = babyAnalyzer.MT2W();
      double topness = babyAnalyzer.topnessMod();
      if ((is_dilep || is_dilep_emu) && remove_lep_from_met) {
        //
        // first, we need to sort jets by CSV value
        //
        std::vector<std::pair<int, double> > v_idx_csv;
        for (unsigned int idx = 0; idx < babyAnalyzer.ak4pfjets_p4().size(); idx++) {
          v_idx_csv.push_back(std::make_pair(idx, babyAnalyzer.ak4pfjets_CSV().at(idx)));
        }
        std::sort(v_idx_csv.begin(), v_idx_csv.end(), sortByCSV);

        //
        // now get vector<LV> of b-jets and add-jets
        //
        std::vector<LorentzVector> mybjets;
        std::vector<LorentzVector> addjets;        
        for (auto p : v_idx_csv) {
          if (babyAnalyzer.ak4pfjets_passMEDbtag().at(p.first))
            mybjets.push_back(babyAnalyzer.ak4pfjets_p4().at(p.first));
          else if (mybjets.size() <=1 && (mybjets.size() + addjets.size()) < 3)
            addjets.push_back(babyAnalyzer.ak4pfjets_p4().at(p.first));                       
        }
               
        //
        // if == 2 jets, recalculate modified topness with new met
        //
        if (babyAnalyzer.ngoodjets() == 2)
          topness = CalcTopness_(1, met, met_phi, babyAnalyzer.lep1_p4(), mybjets, addjets);
        
        //
        // if >=3 jets, recalculate mt2w with new met
        //
        if (babyAnalyzer.ngoodjets() >= 3)   
          mt2w = CalcMT2W_(mybjets, addjets, babyAnalyzer.lep1_p4(), met, met_phi);
      }
      
      //std::cout << "  Evt, Run, Ls = " << babyAnalyzer.evt() << ", " << babyAnalyzer.run() << ", " << babyAnalyzer.ls() << std::endl;
      //std::cout << "    Topness = " << topness << std::endl;
      //std::cout << "    MT2W = " << mt2w << std::endl;
      

      int index = getRegionIndex(babyAnalyzer.ngoodjets(),
                                 topness,
                                 mt2w,
                                 met);

      ++passes_sr_or_cr_before;

      if (!(passes_SR_preselection || passes_tt2l_CR_preselection || passes_wjets_CR_preselection)) ++passes_sr_or_cr_after;

        
      if ( index < 0){
	//cout << "NEGATIVE INDEX!" << endl;
	//cout << "goodjets = " << babyAnalyzer.ngoodjets() << endl;
	//cout << "topness = " << topness << endl;
	//cout << "met = " << met << endl;
	//cout << "mt2w = " << mt2w << endl;
        continue;
      }

      //if( index==1 ) cout << "  Evt, Run, Ls = " << babyAnalyzer.evt() << ", " << babyAnalyzer.run() << ", " << babyAnalyzer.ls() << std::endl;

      double wgt = babyAnalyzer.scale1fb() * lumi;
      if (babyAnalyzer.is_data()) wgt = 1;
      
      if (babyAnalyzer.is_data()) {
        if (passes_SR_preselection) {
          sr_cnt[index][0] += wgt;
          if (abs(babyAnalyzer.lep1_pdgid()) == 11) sr_cnt[index][1] += wgt;
          else if (abs(babyAnalyzer.lep1_pdgid()) == 13) sr_cnt[index][2] += wgt;
        }
        else if (passes_tt2l_CR_preselection) {
          cr2l_cnt[index][0] += wgt;
          if (babyAnalyzer.ngoodleps() > 1 || (babyAnalyzer.ngoodleps() == 1 && babyAnalyzer.nvetoleps() > 1 && babyAnalyzer.lep2_p4().pt()>10)) {
            if (abs(babyAnalyzer.lep2_pdgid()) == 11) cr2l_cnt[index][1] += wgt;
            else if (abs(babyAnalyzer.lep2_pdgid()) == 13) cr2l_cnt[index][2] += wgt;
          }
          else if (babyAnalyzer.ngoodleps() == 1 && !passes_trackVeto) cr2l_cnt[index][3] += wgt;
          else if (babyAnalyzer.ngoodleps() == 1 && !passes_tauVeto) cr2l_cnt[index][4] += wgt;
        }
        else if (passes_wjets_CR_preselection) {
          cr0b_cnt[index][0] += wgt;
          if (abs(babyAnalyzer.lep1_pdgid()) == 11) cr0b_cnt[index][1] += wgt;
          else if (abs(babyAnalyzer.lep1_pdgid()) == 13) cr0b_cnt[index][2] += wgt;
        }
      }                    
      else {
        if (passes_SR_preselection) {
          if (is_true_2l) {
            tt2l_sr_cnt[index] += wgt;
            h_tt2l_sr_cnt->Fill(index, wgt);
          }
          if (is_wjets)
          {
            wjets_sr_cnt[index] += wgt;
            h_wjets_sr_cnt->Fill(index, wgt);
          }
          if (is_rare)
            rare_bkgd_est[index] += wgt;
          if (is_tt1l)
            tt1l_bkgd_est[index] += wgt;
            
        }
        else if (passes_tt2l_CR_preselection) {
          tt2l_cr_cnt[index] += wgt;
          h_tt2l_cr_cnt->Fill(index, wgt);

          if (is_dilep_emu) {
            tt2l_cr_onlyLep_cnt[index] += wgt;
            h_tt2l_cr_onlyLep_cnt->Fill(index, wgt);
          }
        }
        else if (passes_wjets_CR_preselection) {
          if (is_wjets) {
            wjets_cr_cnt[index] += wgt;
            h_wjets_cr_cnt->Fill(index, wgt);
          }
          else
            wjets_cont[index] += wgt;
        }
      }

      //
      // now we want to check on if the event passes the selections of the ISR regions
      //
      index = -1;
      if (babyAnalyzer.ak4pfjets_p4().at(0).pt() > 250 && !babyAnalyzer.ak4pfjets_passMEDbtag().at(0) && babyAnalyzer.ngoodjets() >= 5) {
        if (met >= 250 && met < 350)
          index = 13;
        else if (met >= 350)
          index = 14;
        else
          index = -1;
      }
      if (index == 13 || index == 14) {
        if (babyAnalyzer.is_data()) {
          if (passes_SR_preselection) {
            sr_cnt[index][0] += wgt;
            if (abs(babyAnalyzer.lep1_pdgid()) == 11) sr_cnt[index][1] += wgt;
            else if (abs(babyAnalyzer.lep1_pdgid()) == 13) sr_cnt[index][2] += wgt;
          }
          else if (passes_tt2l_CR_preselection) {
            cr2l_cnt[index][0] += wgt;
            if (babyAnalyzer.ngoodleps() > 1 || (babyAnalyzer.ngoodleps() == 1 && babyAnalyzer.nvetoleps() > 1 && babyAnalyzer.lep2_p4().pt()>10)) {
              if (abs(babyAnalyzer.lep2_pdgid()) == 11) cr2l_cnt[index][1] += wgt;
              else if (abs(babyAnalyzer.lep2_pdgid()) == 13) cr2l_cnt[index][2] += wgt;
            }
            else if (babyAnalyzer.ngoodleps() == 1 && !passes_trackVeto) cr2l_cnt[index][3] += wgt;
            else if (babyAnalyzer.ngoodleps() == 1 && !passes_tauVeto) cr2l_cnt[index][4] += wgt;
          }
          else if (passes_wjets_CR_preselection) {
            cr0b_cnt[index][0] += wgt;
            if (abs(babyAnalyzer.lep1_pdgid()) == 11) cr0b_cnt[index][1] += wgt;
            else if (abs(babyAnalyzer.lep1_pdgid()) == 13) cr0b_cnt[index][2] += wgt;
          }
        }                    
        else {
          if (passes_SR_preselection) {
            if (is_true_2l) {
              tt2l_sr_cnt[index] += wgt;
              h_tt2l_sr_cnt->Fill(index, wgt);
            }
            if (is_wjets)
            {
              wjets_sr_cnt[index] += wgt;
              h_wjets_sr_cnt->Fill(index, wgt);
            }
            if (is_rare)
              rare_bkgd_est[index] += wgt;
            if (is_tt1l)
              tt1l_bkgd_est[index] += wgt;
            
          }
          else if (passes_tt2l_CR_preselection) {
            tt2l_cr_cnt[index] += wgt;
            h_tt2l_cr_cnt->Fill(index, wgt);

            if (is_dilep_emu) {
              tt2l_cr_onlyLep_cnt[index] += wgt;
              h_tt2l_cr_onlyLep_cnt->Fill(index, wgt);
            }
          }
          else if (passes_wjets_CR_preselection) {
            if (is_wjets) {
              wjets_cr_cnt[index] += wgt;
              h_wjets_cr_cnt->Fill(index, wgt);
            }
            else
              wjets_cont[index] += wgt;
          }
        }
        
      }
    }      
    
    // Clean Up
    delete tree;
    file->Close();
    delete file;
  }
  
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

  duplicate_removal::clear_list();
  
  // Example Histograms
  TCanvas c1("c1","c1",800,1200);
  c1.Divide(3,2);
  c1.cd(1);
  h_tt2l_sr_cnt->Draw();
  c1.cd(2);
  h_tt2l_cr_cnt->Draw();
  c1.cd(3);
  h_tt2l_cr_onlyLep_cnt->Draw();
  c1.cd(4);
  TH1F *heff_sr = (TH1F*)h_tt2l_sr_cnt->Clone();
  heff_sr->Divide(h_tt2l_sr_cnt);
  heff_sr->Draw();
  c1.cd(5);
  TH1F *heff_cr = (TH1F*)h_tt2l_sr_cnt->Clone();
  heff_cr->Divide(h_tt2l_cr_cnt);
  heff_cr->Draw();
  c1.cd(6);
  TH1F *heff_cr_onlyLep = (TH1F*)h_tt2l_sr_cnt->Clone();
  heff_cr_onlyLep->Divide(h_tt2l_cr_onlyLep_cnt);
  heff_cr_onlyLep->Draw();
  c1.Print("stop1l_ll_tf_xcheck.root");
  c1.Print("stop1l_ll_tf_xcheck.pdf");  
  c1.Print("stop1l_ll_tf_xcheck.png");  

  //
  // get wjets bkgd estimate
  // [ (observed yield in 0b CR) * (contamination from MC)  ] * TFbtag
  //
  for (unsigned int idx = 0; idx < nregions; idx++) {
    if (idx < 6 || (idx > 8 && idx < 13))
      wjets_bkgd_est[idx] = cr0b_cnt[idx][0] * wjets_cont[idx] * wjets_tf[idx];
    else
      wjets_bkgd_est[idx] = wjets_sr_cnt[idx];
    tt2l_ll_bkgd_est[idx] = cr2l_cnt[idx][0] * tt2l_tf[idx];
  }
  
  cout << "counts of events failing different SR selections" << endl;
  cout << endl;
  cout << "# events passing presel: " << passes_presel << endl;
  cout << "# events passing MET, MT: " << passes_met_mt << endl;
  cout << "# events passing 1 good lep: " << passes_met_mt-fails_ee1_selLep << endl;
  cout << "# events passing 0 veto lep: " << passes_met_mt-fails_ee1_selLep-fails_ee0_vetoLep << endl;  
  cout << "# events passing track veto: " << passes_met_mt-fails_ee1_selLep-fails_ee0_vetoLep-fails_trackVeto << endl;
  cout << "# events passing 0 tau veto: " << passes_met_mt-fails_ee1_selLep-fails_ee0_vetoLep-fails_tauVeto << endl;
  cout << "# events passing SR or CR before: " << passes_sr_or_cr_before << endl;
  cout << "# events passing SR or CR after: " << passes_sr_or_cr_after << endl;  
  cout << endl;
  
  std::string names[nregions];
  names[0] = "== 2 jets, 150 < MET < 250";
  names[1] = "== 2 jets, 250 < MET < 350";
  names[2] = "== 2 jets, MET > 350";
  names[3] = "== 3 jets, 150 < MET < 250";
  names[4] = "== 3 jets, 250 < MET < 350";
  names[5] = "== 3 jets, MET > 350";
  names[6] = ">= 4 jets, mt2w < 200, 150 < MET < 250";
  names[7] = ">= 4 jets, mt2w < 200, 250 < MET < 325";
  names[8] = ">= 4 jets, mt2w < 200, MET > 325";
  names[9] = ">= 4 jets, mt2w > 200, 150 < MET < 250";
  names[10] = ">= 4 jets, mt2w > 200, 250 < MET < 350";
  names[11] = ">= 4 jets, mt2w > 200, 350 < MET < 450";
  names[12] = ">= 4 jets, mt2w > 200, MET > 450";
  names[13] = ">= 5 jets, 250 < MET < 350";  
  names[14] = ">= 5 jets, MET > 350";  
  
  cout << "table of counts for SR and CR for ttbar LL" << endl;
  cout << "region \t SR yield \t CR yield \t TF \t CR yield, e/mu only \t TF (e/mu)" << std::endl;
  cout << endl;
  for (unsigned int idx = 0; idx < nregions; idx++) {
    std::string delim = ":\t";
    if (idx < 6) delim = ":\t\t";
    if (idx == 2 || idx == 5) delim = ":\t\t\t";
    cout << names[idx] << delim << tt2l_sr_cnt[idx] << "\t\t"
         << tt2l_cr_cnt[idx] << "\t\t" << tt2l_sr_cnt[idx]/tt2l_cr_cnt[idx] << "\t\t"
         << tt2l_cr_onlyLep_cnt[idx] << "\t\t" << tt2l_sr_cnt[idx]/tt2l_cr_onlyLep_cnt[idx]
         << endl;
  }
  cout << endl;

  cout << "table of counts for SR and CR for Wjets 1L background" << endl;
  cout << "region \t\t SR yield \t\t CR yield \t\t TF \t\t cont" << std::endl;
  cout << endl;
  for (unsigned int idx = 0; idx < nregions; idx++) {
    std::string delim = ":\t";
    if (idx < 6) delim = ":\t\t";
    if (idx == 2 || idx == 5) delim = ":\t\t\t";
    cout << names[idx] << delim << wjets_sr_cnt[idx] << "\t\t"
         << wjets_cr_cnt[idx] << "\t\t" << wjets_sr_cnt[idx]/wjets_cr_cnt[idx]
         << "\t\t" << wjets_cont[idx] << endl;
  }
  cout << endl;
    
  cout << "table of breakdown of observed yields" << endl;
  cout << "region \t\t total \t\t ele \t\t mu" << endl;
  cout << endl;
  for (unsigned int idx = 0; idx < nregions; idx++) {
    std::string delim = ":\t";
    if (idx < 6) delim = ":\t\t";
    if (idx == 2 || idx == 5) delim = ":\t\t\t";
    cout << names[idx] << delim << sr_cnt[idx][0]
         << "\t\t" << sr_cnt[idx][1] << "\t\t"
         << sr_cnt[idx][2] << endl;
  }
  cout << endl;

  cout << "table of breakdown of LL CR yields" << endl;
  cout << "region \t\t total \t\t ele \t\t mu \t\t iso track \t\t tau" << endl;
  cout << endl;
  for (unsigned int idx = 0; idx < nregions; idx++) {
    std::string delim = ":\t";
    if (idx < 6) delim = ":\t\t";
    if (idx == 2 || idx == 5) delim = ":\t\t\t";
    cout << names[idx] << delim << cr2l_cnt[idx][0] << "\t\t" << cr2l_cnt[idx][1] << "\t\t"
         << cr2l_cnt[idx][2] << "\t\t" << cr2l_cnt[idx][3] << "\t\t" << cr2l_cnt[idx][4] << endl;
  }
  cout << endl;

  cout << "table of breakdown of 0b CR yields" << endl;
  cout << "region \t\t total \t\t ele \t\t mu " << endl;
  cout << endl;
  for (unsigned int idx = 0; idx < nregions; idx++) {
    std::string delim = ":\t";
    if (idx < 6) delim = ":\t\t";
    if (idx == 2 || idx == 5) delim = ":\t\t\t";
    cout << names[idx] << delim << cr0b_cnt[idx][0] << "\t\t" << cr0b_cnt[idx][1] << "\t\t"
         << cr0b_cnt[idx][2] << endl;
  }
  cout << endl;
  
  cout << "table of estimated backgrounds and oberved yields" << endl;
  cout << "region \t\t LL \t\t Wjets \t\t top(1l) \t\t rare \t\t tot bkgd \t\t obs" << endl;
  cout << endl;
  for (unsigned int idx = 0; idx < nregions; idx++) {
    std::string delim = ":\t";
    if (idx < 6) delim = ":\t\t";
    if (idx == 2 || idx == 5) delim = ":\t\t\t";
    cout << names[idx] << delim << tt2l_ll_bkgd_est[idx]
         << "\t\t" << wjets_bkgd_est[idx]
         << "\t\t" << tt1l_bkgd_est[idx]
         << "\t\t" << rare_bkgd_est[idx]
         << "\t\t" << tt2l_ll_bkgd_est[idx]+wjets_bkgd_est[idx]+tt1l_bkgd_est[idx]+rare_bkgd_est[idx]
         << "\t\t" << sr_cnt[idx][0] << endl;
  }
  cout << endl;
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}

int getRegionIndex (int njets, float modtop, float mt2w, float met) {
  if (njets < 2) return -1;
  if (njets == 2 && modtop >= 6.4) {
    if (met >= 150 && met < 250) return 0;
    else if (met >= 250 && met < 350) return 1;
    else if (met >= 350) return 2;
    else return -1;
  }
  else if (njets == 3 && mt2w >= 200)
  {
    if (met >= 150 && met < 250) return 3;
    else if (met >= 250 && met < 350) return 4;
    else if (met >= 350) return 5;
    else return -1;    
  }
  else if (njets >= 4)
  {
    if (mt2w <= 200)
    {
      if (met >= 150 && met < 250) return 6;
      else if (met >= 250 && met < 325) return 7;
      else if (met >= 325) return 8;
      else return -1;
    }
    else if (mt2w > 200)
    {
      if (met >= 150 && met < 250) return 9;
      else if (met >= 250 && met < 350) return 10;
      else if (met >= 350 && met < 450) return 11;
      else if (met >= 450) return 12;
    }
    else return -1;
  }
  else return -1;
  return -2;
}

double getLostLepTransferFactor (int njets, float modtop, float mt2w, float met) {
  if (njets < 2) return -1;
  if (njets == 2 && modtop >= 6.4) {
    if (met >= 150 && met < 250) return 0.533543;
    else if (met >= 250 && met < 350) return 0.57705;
    else if (met >= 350) return 0.476351;
    else return -1;
  }
  else if (njets == 3 && mt2w >= 200)
  {
    if (met >= 150 && met < 250) return 0.601559;
    else if (met >= 250 && met < 350) return 0.547189;
    else if (met >= 350) return 0.395894;
    else return -1;    
  }
  else if (njets >= 4)
  {
    if (mt2w <= 200)
    {
      if (met >= 150 && met < 250) return 0.701108;
      else if (met >= 250 && met < 325) return 0.718084;
      else if (met >= 325) return 0.669788;
      else return -1;
    }
    else if (mt2w > 200)
    {
      if (met >= 150 && met < 250) return 0.611177;
      else if (met >= 250 && met < 350) return 0.520874;
      else if (met >= 350 && met < 450) return 0.548541;
      else if (met >= 450) return 0.526296;
    }
    else return -1;
  }
  else return -1;
  return -1;
}

double getLostLepOnlyLepTransferFactor (int njets, float modtop, float mt2w, float met) {
  if (njets < 2) return -1;
  if (njets == 2 && modtop >= 6.4) {
    if (met >= 150 && met < 250) return 1.0777;
    else if (met >= 250 && met < 350) return 1.18755;
    else if (met >= 350) return 1.02664;
    else return -1;
  }
  else if (njets == 3 && mt2w >= 200)
  {
    if (met >= 150 && met < 250) return 1.37137;
    else if (met >= 250 && met < 350) return 1.29449;
    else if (met >= 350) return 0.94411;
    else return -1;    
  }
  else if (njets >= 4)
  {
    if (mt2w <= 200)
    {
      if (met >= 150 && met < 250) return 2.26176;
      else if (met >= 250 && met < 325) return 2.38104;
      else if (met >= 325) return 2.23201;
      else return -1;
    }
    else if (mt2w > 200)
    {
      if (met >= 150 && met < 250) return 1.75662;
      else if (met >= 250 && met < 350) return 1.71672;
      else if (met >= 350 && met < 450) return 1.94557;
      else if (met >= 450) return 1.29771;
    }
    else return -1;
  }
  else return -1;
  return -1;
}

double getWJetsTransferFactor (int njets, float modtop, float mt2w, float met) {
  if (njets < 2) return -1;
  if (njets == 2 && modtop >= 6.4) {
    if (met >= 150 && met < 250) return 0.0889367;
    else if (met >= 250 && met < 350) return 0.0654016;
    else if (met >= 350) return 0.0750763;
    else return -1;
  }
  else if (njets == 3 && mt2w >= 200)
  {
    if (met >= 150 && met < 250) return 0.198635;
    else if (met >= 250 && met < 350) return 0.211049;
    else if (met >= 350) return 0.129747;
    else return -1;    
  }
  else if (njets >= 4)
  {
    if (mt2w <= 200)
    {
      if (met >= 150 && met < 250) return 0.255842;
      else if (met >= 250 && met < 325) return 0.285104;
      else if (met >= 325) return 0.178847;
      else return -1;
    }
    else if (mt2w > 200)
    {
      if (met >= 150 && met < 250) return 0.319011;
      else if (met >= 250 && met < 350) return 0.25856;
      else if (met >= 350 && met < 450) return 0.217775;
      else if (met >= 450) return 0.214045;
    }
    else return -1;
  }
  else return -1;
  return -1;
}


