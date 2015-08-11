#include <string.h>
#include <iostream>
#include <vector>
#include <typeinfo>

#include "looper.h"

#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"

#include "CMS3.h"
#include "MCSelections.h"
#include "StopSelections.h"
#include "TriggerSelections.h"
#include "stop_variables/mt2w.cc"
#include "stop_variables/mt2w_bisect.cpp"
#include "stop_variables/chi2.cc"
#include "stop_variables/JetUtil.cc"
#include "stop_variables/topness.cc"
#include "stop_variables/MT2_implementations.cc"

#include "MuonSelections.h"//93991
#include "IsolationTools.h"//93991

#include "goodrun.h"
#include "dorky.cc"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;
using namespace tas;
using namespace duplicate_removal;


//====================//
//                    //
// Utility Structures //
//                    //
//====================//

struct Lepton{
        int id;
        int idx;
        LorentzVector p4;
        //Lepton(id, idx, p4) {id = id; idx = idx; p4 = p4;}
};

struct sortbypt{
  bool operator () (const pair<int, LorentzVector> &v1, const pair<int,LorentzVector> &v2){
    return v1.second.pt() > v2.second.pt();
  }
};

struct sortLepbypt{
  bool operator () (const Lepton &lep1, const Lepton &lep2){
    return lep1.p4.pt() > lep2.p4.pt();
  }
};


//===========//
//           //
// Functions //
//           //
//===========//

babyMaker::babyMaker(){

   StopEvt = EventTree();
   lep1 = LeptonTree("lep1_");
   lep2 = LeptonTree("lep2_");
   jets = JetTree();
   gen_els = GenParticleTree("els_");
   gen_mus = GenParticleTree("mus_");
   //gen_leptau_els = GenParticleTree("leptau_els_");
   //gen_leptau_mus = GenParticleTree("leptau_mus_");
   gen_taus = GenParticleTree("taus_");
   gen_nus = GenParticleTree("nus_");
   gen_bs  = GenParticleTree("bs_");
   gen_tops = GenParticleTree("ts_");
   gen_qs  = GenParticleTree("qs_");
   gen_lsp = GenParticleTree("lsp_");
   gen_stop = GenParticleTree("stop_");
   Taus = TauTree();
   Tracks = IsoTracksTree();
}

void babyMaker::setSkimVariables(int nvtx, float met, int nGoodLep, float goodLep_el_pt, float goodLep_el_eta, float goodLep_mu_pt, float goodLep_mu_eta, float looseLep_el_pt, float looseLep_el_eta, float looseLep_mu_pt, float looseLep_mu_eta, float vetoLep_el_pt, float vetoLep_el_eta, float vetoLep_mu_pt, float vetoLep_mu_eta, int njets, float jet_pt, float jet_eta, float jet_ak8_pt, float jet_ak8_eta){

  skim_nvtx            = nvtx;
  skim_met             = met;
  
  skim_nGoodLep        = nGoodLep;
  skim_goodLep_el_pt   = goodLep_el_pt;
  skim_goodLep_el_eta  = goodLep_el_eta;
  skim_goodLep_mu_pt   = goodLep_mu_pt;
  skim_goodLep_mu_eta  = goodLep_mu_eta;
  
  skim_looseLep_el_pt  = looseLep_el_pt;
  skim_looseLep_el_eta = looseLep_el_eta;
  skim_looseLep_mu_pt  = looseLep_mu_pt;
  skim_looseLep_mu_eta = looseLep_mu_eta;
  
  skim_vetoLep_el_pt   = vetoLep_el_pt;
  skim_vetoLep_el_eta  = vetoLep_el_eta;
  skim_vetoLep_mu_pt   = vetoLep_mu_pt;
  skim_vetoLep_mu_eta  = vetoLep_mu_eta;
  
  skim_nJets           = njets;
  skim_jet_pt          = jet_pt;
  skim_jet_eta         = jet_eta;

  skim_jet_ak8_pt      = jet_ak8_pt;
  skim_jet_ak8_eta     = jet_ak8_eta;

}


void babyMaker::MakeBabyNtuple(const char* output_name){

  BabyFile = new TFile(Form("%s/%s", babypath, output_name), "RECREATE");
  BabyTree = new TTree("t", "Stop2015 Baby Ntuple");

  StopEvt.SetBranches(BabyTree);
  lep1.SetBranches(BabyTree);
  lep2.SetBranches(BabyTree);
  jets.SetBranches(BabyTree);
  gen_els.SetBranches(BabyTree);
  gen_mus.SetBranches(BabyTree);
  //gen_leptau_els.SetBranches(BabyTree);
  //gen_leptau_mus.SetBranches(BabyTree);
  gen_taus.SetBranches(BabyTree);
  gen_nus.SetBranches(BabyTree);
  gen_bs.SetBranches(BabyTree);
  gen_tops.SetBranches(BabyTree);
  gen_qs.SetBranches(BabyTree);
  gen_lsp.SetBranches(BabyTree);
  gen_stop.SetBranches(BabyTree);
  Taus.SetBranches(BabyTree);
  Tracks.SetBranches(BabyTree);
}

void babyMaker::InitBabyNtuple(){
  
  StopEvt.Reset();
  lep1.Reset();
  lep2.Reset();
  jets.Reset();
  gen_els.Reset();
  gen_mus.Reset();
  //gen_leptau_els.Reset();
  //gen_leptau_mus.Reset();
  gen_taus.Reset();
  gen_nus.Reset();
  gen_bs.Reset();
  gen_tops.Reset();
  gen_qs.Reset();
  gen_lsp.Reset();
  gen_stop.Reset();
  Taus.Reset();
  Tracks.Reset();
} 




//================//
//                //
// Main function  //
//                //
//================//

int babyMaker::looper(TChain* chain, char* output_name, int nEvents, char* path){

  //
  // Set output file path
  //
  babypath = path;
  
  //
  // Benchmark
  //
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
  
  //
  //Set up loop over chain
  //
  unsigned int nEvents_processed = 0;
  unsigned int nEvents_pass_skim_nVtx = 0;
  unsigned int nEvents_pass_skim_met = 0;
  unsigned int nEvents_pass_skim_nGoodLep = 0;
  unsigned int nEvents_pass_skim_nJets = 0;
  unsigned int nEventsToDo = chain->GetEntries();
  unsigned int jet_overlep1_idx = -9999;
  unsigned int jet_overlep2_idx = -9999;
  //unsigned int track_overlep1_idx = -9999;
  //unsigned int track_overlep2_idx = -9999;
  
  
  if( nEvents >= 0 ) nEventsToDo = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //
  // Make Baby Ntuple  
  //
  MakeBabyNtuple( Form("%s.root", output_name) );

  //
  // Initialize Baby Ntuple Branches
  //
  InitBabyNtuple();

  //
  // Set JSON file
  //
  const char* json_file = "json_files/Cert_246908-251883_13TeV_PromptReco_Collisions15_JSON_v2_snt.txt";
  set_goodrun_file(json_file);

  //
  // File Loop
  //
  while ( (currentFile = (TFile*)fileIter.Next()) ) { 

    //
    // Get File Content
    //
    if(nEvents_processed >= nEventsToDo) continue;
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("Events");
    cms3.Init(tree);
    cout << "file name is " << file->GetName() << endl;

    //
    // Loop over Events in current file
    //
    unsigned int nEventsTree = tree->GetEntriesFast();

    for(unsigned int evt = 0; evt < nEventsTree; evt++){

      //
      // Get Event Content
      //
      if(nEvents_processed >= nEventsToDo) break;
      cms3.GetEntry(evt);
      nEvents_processed++;

      //
      // Progress
      //
      CMS3::progress(nEvents_processed, nEventsToDo);

      //
      // Intialize Baby NTuple Branches
      //
      InitBabyNtuple();

      //
      // If data, check against good run list
      //
      if( evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()) ) continue;
      if( evt_isRealData() ) {
	DorkyEventIdentifier id(evt_run(), evt_event(), evt_lumiBlock());
	if (is_duplicate(id) ) continue;
      }

      //
      // Fill Event Variables
      //
      //std::cout << "[babymaker::looper]: filling event vars" << std::endl;
      StopEvt.FillCommon(file->GetName()); 
      //std::cout << "[babymaker::looper]: filling event vars completed" << std::endl; 
      //dumpDocLines();
      
      //
      // nVertex Cut
      //
      if(StopEvt.nvtxs < skim_nvtx) continue;
      if(StopEvt.firstGoodVtxIdx!=0) continue; //really check that first vertex is good
      nEvents_pass_skim_nVtx++;

      // 
      // met Cut
      //
      if(evt_pfmet() < skim_met) continue;
      nEvents_pass_skim_met++;

      //
      //Lepton Variables
      //
      //std::cout << "[babymaker::looper]: selecting leptons" << std::endl;
      int nGoodLeptons = 0;  //stored lep1,lep2
      int nVetoLeptons = 0;
            
      vector<Lepton> GoodLeps;
      vector<Lepton> LooseLeps;
      vector<Lepton> VetoLeps;
      vector<Lepton> AllLeps;
      vector<unsigned int> idx_alloverlapjets;

      // Electrons
      for (unsigned int eidx = 0; eidx < els_p4().size(); eidx++){

	if( !PassElectronVetoSelections(eidx, skim_vetoLep_el_pt, skim_vetoLep_el_eta) ) continue;
	
	Lepton mylepton;
        mylepton.id  = -11*els_charge().at(eidx);
        mylepton.idx = eidx;
        mylepton.p4  = els_p4().at(eidx);
	int overlapping_jet = getOverlappingJetIndex(mylepton.p4, pfjets_p4(), 0.4, skim_jet_pt, skim_jet_eta, false);  //don't care about jid
	if( overlapping_jet>=0) idx_alloverlapjets.push_back(overlapping_jet);  //overlap removal for all jets w.r.t. all leptons

	if( ( PassElectronVetoSelections(eidx, skim_vetoLep_el_pt, skim_vetoLep_el_eta) ) &&
	    (!PassElectronPreSelections(eidx, skim_looseLep_el_pt, skim_looseLep_el_eta) )    ) VetoLeps.push_back(mylepton);

	if( ( PassElectronPreSelections(eidx, skim_looseLep_el_pt, skim_looseLep_el_eta) ) &&
	    (!PassElectronPreSelections(eidx, skim_goodLep_el_pt, skim_goodLep_el_eta) )      ) LooseLeps.push_back(mylepton);

	if( PassElectronPreSelections(eidx, skim_goodLep_el_pt, skim_goodLep_el_eta)          ) GoodLeps.push_back(mylepton);

      }

      // Muons
      for (unsigned int midx = 0; midx < mus_p4().size(); midx++){

	if( !PassMuonVetoSelections(midx, skim_vetoLep_mu_pt, skim_vetoLep_mu_eta) ) continue;
	
	Lepton mylepton;
        mylepton.id  = -13*mus_charge().at(midx);
        mylepton.idx = midx;
        mylepton.p4  = mus_p4().at(midx);
	int overlapping_jet = getOverlappingJetIndex(mylepton.p4, pfjets_p4() , 0.4, skim_jet_pt, skim_jet_eta,false);  //don't care about jid
	if( overlapping_jet>=0) idx_alloverlapjets.push_back(overlapping_jet);  //overlap removal for all jets w.r.t. all leptons
	
	if( ( PassMuonVetoSelections(midx, skim_vetoLep_mu_pt, skim_vetoLep_mu_eta) ) &&
	    (!PassMuonPreSelections(midx, skim_looseLep_mu_pt, skim_looseLep_mu_eta) )    ) VetoLeps.push_back(mylepton);

	if( ( PassMuonPreSelections(midx, skim_looseLep_mu_pt, skim_looseLep_mu_eta) ) &&
	    (!PassMuonPreSelections(midx, skim_goodLep_mu_pt, skim_goodLep_mu_eta) )      ) LooseLeps.push_back(mylepton);

	if( PassMuonPreSelections(midx, skim_goodLep_mu_pt, skim_goodLep_mu_eta)          ) GoodLeps.push_back(mylepton);

      }
      sort(GoodLeps.begin(),GoodLeps.end(),sortLepbypt());       
      sort(LooseLeps.begin(),LooseLeps.end(),sortLepbypt());       
      sort(VetoLeps.begin(),VetoLeps.end(),sortLepbypt());       
      
      nGoodLeptons = GoodLeps.size();

      if(nGoodLeptons < skim_nGoodLep) continue;
      nEvents_pass_skim_nGoodLep++;
      
      nVetoLeptons = GoodLeps.size() + LooseLeps.size() + VetoLeps.size();

      StopEvt.ngoodleps = nGoodLeptons; 
      StopEvt.nvetoleps = nVetoLeptons; 
      
      //std::cout << "[babymaker::looper]: filling lepton variables" << std::endl;
      AllLeps.clear();
      AllLeps.insert( AllLeps.end(), GoodLeps.begin(),  GoodLeps.end() );
      AllLeps.insert( AllLeps.end(), LooseLeps.begin(), LooseLeps.end() );
      AllLeps.insert( AllLeps.end(), VetoLeps.begin(),  VetoLeps.end() );
      if( nVetoLeptons > 0 ) lep1.FillCommon( AllLeps.at(0).id, AllLeps.at(0).idx );
      if( nVetoLeptons > 1 ) lep2.FillCommon( AllLeps.at(1).id, AllLeps.at(1).idx );

      //lep1.FillCommon(GoodLeps.at(0).id, GoodLeps.at(0).idx);      
      //if( nGoodLeptons        >1) lep2.FillCommon(GoodLeps.at(1).id,  GoodLeps.at(1).idx);
      //else if(LooseLeps.size()>0) lep2.FillCommon(LooseLeps.at(0).id, LooseLeps.at(0).idx);
      //else if(VetoLeps.size() >0) lep2.FillCommon(VetoLeps.at(0).id,  VetoLeps.at(0).idx);
    

      //
      // Jet Selection
      //

      //std::cout << "[babymaker::looper]: filling jets vars" << std::endl;         
      // Get the jets overlapping with the selected leptons
      if(pfjets_p4().size() > 0){
	jet_overlep1_idx = -9999;
	jet_overlep2_idx = -9999;
	if(nVetoLeptons>0) jet_overlep1_idx = getOverlappingJetIndex(lep1.p4, pfjets_p4(), 0.4, skim_jet_pt, skim_jet_eta, false);  //don't care about jid
	if(nVetoLeptons>1) jet_overlep2_idx = getOverlappingJetIndex(lep2.p4, pfjets_p4(), 0.4, skim_jet_pt, skim_jet_eta, false);  //don't care about jid
	
	// Jets and b-tag variables feeding the index for the jet overlapping the selected leptons
	jets.SetJetSelection("ak4", skim_jet_pt, skim_jet_eta, true); //save only jets passing jid
	jets.SetJetSelection("ak8", skim_jet_ak8_pt, skim_jet_ak8_eta, true); //save only jets passing jid
	jets.FillCommon(idx_alloverlapjets, jet_overlep1_idx, jet_overlep2_idx);
      }
      
      if(jets.ngoodjets < skim_nJets) continue;
      nEvents_pass_skim_nJets++;


      //
      // Event Variables
      //

      //std::cout << "[babymaker::looper]: Calculating Event Variables" << std::endl;
      // MT2W
      //if(nVetoLeptons>0) StopEvt.MT2W = calculateMT2w(jets.ak4pfjets_p4, jets.ak4pfjets_passMEDbtag, lep1.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
      //if(nVetoLeptons>1) StopEvt.MT2W_lep2 = calculateMT2w(jets.ak4pfjets_p4, jets.ak4pfjets_passMEDbtag, lep2.p4,StopEvt.pfmet, StopEvt.pfmet_phi);

      // MET & Leptons
      if(nVetoLeptons>0) StopEvt.mt_met_lep = calculateMt(lep1.p4, StopEvt.pfmet, StopEvt.pfmet_phi);
      if(nVetoLeptons>1) StopEvt.mt_met_lep2 = calculateMt(lep2.p4, StopEvt.pfmet, StopEvt.pfmet_phi);
      
      if(nVetoLeptons>0) StopEvt.dphi_Wlep = DPhi_W_lep(StopEvt.pfmet, StopEvt.pfmet_phi, lep1.p4);

      if(pfjets_p4().size() > 0) StopEvt.MET_over_sqrtHT = StopEvt.pfmet/TMath::Sqrt(jets.ak4_HT);

      StopEvt.ak4pfjets_rho = evt_fixgridfastjet_all_rho();

    
      vector<int> jetIndexSortedCSV = JetUtil::JetIndexCSVsorted(jets.ak4pfjets_CSV, jets.ak4pfjets_p4, jets.ak4pfjets_loose_pfid, skim_jet_pt, skim_jet_eta, true);
      vector<LorentzVector> mybjets; vector<LorentzVector> myaddjets;
      for(unsigned int idx = 0; idx<jetIndexSortedCSV.size(); ++idx){
	if(jets.ak4pfjets_passMEDbtag.at(jetIndexSortedCSV[idx])==true) mybjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
	else if(mybjets.size()<=1 && (mybjets.size()+myaddjets.size())<3) myaddjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
      }

      //looks like all the following variables need jets to be calculated. add protection for skim settings of njets<2
      if(jets.ak4pfjets_p4.size()>1){

	// DR(lep, leadB) with medium discriminator
	if(nVetoLeptons>0) StopEvt.dR_lep_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep1.p4);
	if(nVetoLeptons>1) StopEvt.dR_lep2_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep2.p4);
	vector<float> dummy_sigma;
	for (size_t idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
	  dummy_sigma.push_back(0.1);
	} 

	// Hadronic Chi2
	StopEvt.hadronic_top_chi2 = calculateChi2(jets.ak4pfjets_p4, dummy_sigma, jets.ak4pfjets_passMEDbtag);

	// Jets & MET
	StopEvt.mindphi_met_j1_j2 =  getMinDphi(StopEvt.pfmet_phi,jets.ak4pfjets_p4.at(0),jets.ak4pfjets_p4.at(1));

	// MT2W
	if(nVetoLeptons>0) StopEvt.MT2W = CalcMT2W_(mybjets,myaddjets,lep1.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
	if(nVetoLeptons>1) StopEvt.MT2W_lep2 = CalcMT2W_(mybjets,myaddjets,lep2.p4,StopEvt.pfmet, StopEvt.pfmet_phi);

	// Topness
	if(nVetoLeptons>0) StopEvt.topness = CalcTopness_(0,StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets);
	if(nVetoLeptons>1) StopEvt.topness_lep2 = CalcTopness_(0,StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets);
	
	if(nVetoLeptons>0) StopEvt.topnessMod = CalcTopness_(1,StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets);
	if(nVetoLeptons>1) StopEvt.topnessMod_lep2 = CalcTopness_(1,StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets);

	// MT2(lb,b)
	if(nVetoLeptons>0) StopEvt.MT2_lb_b_mass = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,0,true);
	if(nVetoLeptons>0) StopEvt.MT2_lb_b = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,0,false);
	if(nVetoLeptons>1) StopEvt.MT2_lb_b_mass_lep2 = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,0,true);
	if(nVetoLeptons>1) StopEvt.MT2_lb_b_lep2 = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,0,false);

	// MT2(lb,bqq)
	if(nVetoLeptons>0) StopEvt.MT2_lb_bqq_mass = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,true);
	if(nVetoLeptons>0) StopEvt.MT2_lb_bqq = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,false);
	if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_mass_lep2 = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,true);
	if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_lep2 = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,false);
      
	// Topness
	//vector<LorentzVector > mybjets = JetUtil::BJetSelector(jets.ak4pfjets_p4,jets.ak4pfjets_CSV,MYBTAG,2,3,2);
	//if(nVetoLeptons>0) StopEvt.topness=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,0);
	//if(nVetoLeptons>1) StopEvt.Topness_lep2=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,0);
	//if(nVetoLeptons>0) StopEvt.TopnessMod_lep1=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,1);
	//if(nVetoLeptons>1) StopEvt.TopnessMod_lep2=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,1);
	// MT2(lb,b)
	//if(nVetoLeptons>0) StopEvt.MT2_lb_b_mass_lep1 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,true ,0);
	//if(nVetoLeptons>0) StopEvt.MT2_lb_b_lep1 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,false ,0);
	//if(nVetoLeptons>1) StopEvt.MT2_lb_b_mass_lep2 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,true ,0);
	//if(nVetoLeptons>1) StopEvt.MT2_lb_b_lep2 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,false ,0);
	// MT2(lb,bqq)
	//if(nVetoLeptons>0) StopEvt.MT2_lb_bqq_mass_lep1 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,jets.ak4pfjets_p4,true ,0);
	//if(nVetoLeptons>0) StopEvt.MT2_lb_bqq_lep1 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,jets.ak4pfjets_p4,false ,0);
	//if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_mass_lep2 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,jets.ak4pfjets_p4,true ,0);
	//if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_lep2 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,jets.ak4pfjets_p4,false ,0);
      }

      if(jets.ak4pfjets_p4.size()>0){

	// Mlb + Mjjj
	float minDR1 = 99.; float minDR2 = 99.; //minDR for closest b in Mlb
	int jb1 = -1; int jb2 = -1; int jb3 = -1;//jet indices for Mjjj(lep1)
	int jb21 = -1; int jb22 = -1; int jb23 = -1;//jet indices for Mjjj(lep2)
	for (unsigned int idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
	  float myDR = getdphi(jets.ak4pfjets_p4.at(idx).Phi(),lep1.p4.Phi());
	  float myDR1 = -1; float myDR2 = -2; float myDR3 = -3;//is actually DPhi now
	  if(nVetoLeptons>0){
	    if(jb1>=0) myDR1 = getdphi(jets.ak4pfjets_p4.at(jb1).Phi(),lep1.p4.Phi());
	    if(jb2>=0) myDR2 = getdphi(jets.ak4pfjets_p4.at(jb2).Phi(),lep1.p4.Phi());
	    if(jb3>=0) myDR3 = getdphi(jets.ak4pfjets_p4.at(jb3).Phi(),lep1.p4.Phi());

	    if(myDR>myDR1){ jb3 =jb2; jb2 = jb1; jb1 = idx; }
	    else if(myDR>myDR2){ jb3 = jb2; jb2 = idx; }
	    else if(myDR>myDR3){ jb3 = idx; }
	  }
	  if(nVetoLeptons>1){
	    myDR = getdphi(jets.ak4pfjets_p4.at(idx).Phi(),lep2.p4.Phi());
	    float myDR1 = -1; float myDR2 = -2; float myDR3 = -3;
	    if(jb21>=0) myDR1 = getdphi(jets.ak4pfjets_p4.at(jb21).Phi(),lep2.p4.Phi());
	    else if(jb22>=0) myDR2 = getdphi(jets.ak4pfjets_p4.at(jb22).Phi(),lep2.p4.Phi());
	    else if(jb23>=0) myDR3 = getdphi(jets.ak4pfjets_p4.at(jb23).Phi(),lep2.p4.Phi());
	    if(myDR>myDR1){ jb23 =jb22; jb22 = jb22; jb21 = idx; }
	    else if(myDR>myDR2){ jb23 = jb22; jb22 = idx; }
	    else if(myDR>myDR3){ jb23 = idx; }
	  }

	  //if(jets.ak4pfjets_CSV.at(idx)>maxCSV){
          //maxCSV = jets.ak4pfjets_CSV.at(idx);
          //if(nVetoLeptons>0) StopEvt.Mlb_lead_bdiscr = (jets.ak4pfjets_p4.at(idx)+lep1.p4).M();
          //if(nVetoLeptons>1) StopEvt.Mlb_lead_bdiscr_lep2 = (jets.ak4pfjets_p4.at(idx)+lep2.p4).M();
	  //}

	  if(!(jets.ak4pfjets_passMEDbtag.at(idx)) ) continue;
	  if(nVetoLeptons>0){
	    myDR = dRbetweenVectors(jets.ak4pfjets_p4.at(idx),lep1.p4);
	    if(myDR<minDR1) {
	      StopEvt.Mlb_closestb = (jets.ak4pfjets_p4.at(idx)+lep1.p4).M();
	      minDR1 =myDR;
	    }
	  }
	  if(nVetoLeptons>1){
	    myDR = dRbetweenVectors(jets.ak4pfjets_p4.at(idx),lep2.p4);
	    if(myDR<minDR2) {
	      StopEvt.Mlb_closestb_lep2 = (jets.ak4pfjets_p4.at(idx)+lep2.p4).M();
	      minDR2 = myDR;
	    }
	  }
	}
	if(nVetoLeptons>0) StopEvt.Mlb_lead_bdiscr = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[0])+lep1.p4).M();
	if(nVetoLeptons>1) StopEvt.Mlb_lead_bdiscr_lep2 = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[0])+lep2.p4).M();
	if(jb3>=0) {//as sorted, jb1 and jb2 also >=0
	  StopEvt.Mjjj = (jets.ak4pfjets_p4.at(jb1)+jets.ak4pfjets_p4.at(jb2)+jets.ak4pfjets_p4.at(jb3)).M();
	}
	if(jb23>=0) {//as sorted, jb21 and jb22 also >=0
	  StopEvt.Mjjj_lep2 = (jets.ak4pfjets_p4.at(jb21)+jets.ak4pfjets_p4.at(jb22)+jets.ak4pfjets_p4.at(jb23)).M();
	}
    
      } // end if >0 jets      



      //
      // Tau Selection
      //
      //std::cout << "[babymaker::looper]: tau  vars" << std::endl;
      int vetotaus=0;
          
      Taus.tau_IDnames = taus_pf_IDnames();

      for(unsigned int iTau = 0; iTau < taus_pf_p4().size(); iTau++){
	Taus.FillCommon(iTau, 20, 2.4);
	if(nVetoLeptons>0){
	  if(isVetoTau(iTau, lep1.p4, lep1.charge)){
	    Taus.tau_isVetoTau.push_back(true);
	    vetotaus++;
	  }else Taus.tau_isVetoTau.push_back(false);
	}
	else Taus.tau_isVetoTau.push_back(false);
      }

      if(vetotaus<1) StopEvt.PassTauVeto = true;
      else StopEvt.PassTauVeto = false;
      Taus.ngoodtaus = vetotaus;


      //
      // IsoTracks (Charged pfLeptons and pfChargedHadrons)
      //
      //std::cout << "[babymaker::looper]: filling isotrack vars" << std::endl;
      int vetotracks = 0;
      int vetotracks_v2 = 0;
      int vetotracks_v3 = 0;
      for (unsigned int ipf = 0; ipf < pfcands_p4().size(); ipf++) {
	//some selections
	if(pfcands_charge().at(ipf) == 0) continue;
	if(pfcands_p4().at(ipf).pt() < 5) continue;
	if(fabs(pfcands_dz().at(ipf)) > 0.1) continue;

	//remove everything that is within 0.1 of selected lead and subleading leptons
	if(nVetoLeptons>0){
	  if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lep1.p4)<0.1) continue;
	}
	if(nVetoLeptons>1){
          if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lep2.p4)<0.1) continue;
	}
	Tracks.FillCommon(ipf);

	// 8 TeV Track Isolation Configuration
	if(nVetoLeptons>0){
	  if(isVetoTrack(ipf, lep1.p4, lep1.charge)){
	    Tracks.isoTracks_isVetoTrack.push_back(true);
	    vetotracks++;
	  }else Tracks.isoTracks_isVetoTrack.push_back(false);
	}
	else{
	  LorentzVector temp( -99.9, -99.9, -99.9, -99.9 );
	  if(isVetoTrack(ipf, temp, 0)){
	    Tracks.isoTracks_isVetoTrack.push_back(true);
	    vetotracks++;
	  }else Tracks.isoTracks_isVetoTrack.push_back(false);
	}

	// 13 TeV Track Isolation Configuration, pfLep and pfCH
	if(nVetoLeptons>0){
	  if(isVetoTrack_v2(ipf, lep1.p4, lep1.charge)){
	    Tracks.isoTracks_isVetoTrack_v2.push_back(true);
	    vetotracks_v2++;
	  }else Tracks.isoTracks_isVetoTrack_v2.push_back(false);
	}
	else{
	  LorentzVector temp( -99.9, -99.9, -99.9, -99.9 );
	  if(isVetoTrack_v2(ipf, temp, 0)){
	    Tracks.isoTracks_isVetoTrack_v2.push_back(true);
	    vetotracks_v2++;
	  }else Tracks.isoTracks_isVetoTrack_v2.push_back(false);
	}

	// 13 TeV Track Isolation Configuration, pfCH
	if(nVetoLeptons>0){
	  if(isVetoTrack_v3(ipf, lep1.p4, lep1.charge)){
	    Tracks.isoTracks_isVetoTrack_v3.push_back(true);
	    vetotracks_v3++;
	  }else Tracks.isoTracks_isVetoTrack_v3.push_back(false);
	}
	else{
	  LorentzVector temp( -99.9, -99.9, -99.9, -99.9 );
	  if(isVetoTrack_v3(ipf, temp, 0)){
	    Tracks.isoTracks_isVetoTrack_v3.push_back(true);
	    vetotracks_v3++;
	  }else Tracks.isoTracks_isVetoTrack_v3.push_back(false);
	}


      } // end loop over pfCands

      if(vetotracks<1) StopEvt.PassTrackVeto = true;
      else StopEvt.PassTrackVeto = false;
    
      if(vetotracks_v2<1) StopEvt.PassTrackVeto_v2 = true;
      else StopEvt.PassTrackVeto_v2 = false;
    
      if(vetotracks_v3<1) StopEvt.PassTrackVeto_v3 = true;
      else StopEvt.PassTrackVeto_v3 = false;
    

      //
      // Gen Information
      //

      //ttbar counters using neutrinos:
      int n_nutaufromt=0;
      int n_nuelfromt=0;
      int n_numufromt=0;
      //std::cout << "[babymaker::looper]: filling gen particles vars" << std::endl;
      //gen particles
      if (!evt_isRealData()){
	for(unsigned int genx = 0; genx < genps_p4().size() ; genx++){
	  //void GenParticleTree::FillCommon (int idx, int pdgid_=0, int pdgmotherid_=0, int status_=0)
     
	  //if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_leptau_els.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t) n_nuelfromt++;      

	  //if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_leptau_mus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_numufromt++;

	  //if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_nutaufromt++;

	  if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);
        
	  if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);

	  if(abs(genps_id_mother().at(genx)) == pdg_Z && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_Z && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_Z && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);
        
	  if(abs(genps_id_mother().at(genx)) == pdg_ph&& abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_ph&& abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_ph&& abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);
        
	  if(abs(genps_id_mother().at(genx)) == pdg_h && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_h && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_h && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);
        
	  if(abs(genps_id_mother().at(genx)) == pdg_t && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_t && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) == pdg_t && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);

	  // don't store leptons/neutrinos from u,d,s,c,b or proton, those seem to go crazy some times (especially electrons)
	  //if(abs(genps_id_mother().at(genx)) >= pdg_t && abs(genps_id_mother().at(genx)) != pdg_p && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) >= pdg_t && abs(genps_id_mother().at(genx)) != pdg_p && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) >= pdg_t && abs(genps_id_mother().at(genx)) != pdg_p && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);

	  //if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	
	  //if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	  //if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	
	  // don't store leptons/neutrinos from u,d,s,c,b or proton, those seem to go crazy some times (especially electrons)
	  if(abs(genps_id_mother().at(genx)) >= pdg_t && abs(genps_id_mother().at(genx)) != pdg_p && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) >= pdg_t && abs(genps_id_mother().at(genx)) != pdg_p && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
	  if(abs(genps_id_mother().at(genx)) >= pdg_t && abs(genps_id_mother().at(genx)) != pdg_p && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
      
	  if(abs(genps_id().at(genx)) == pdg_d && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
	  if(abs(genps_id().at(genx)) == pdg_u && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
	  if(abs(genps_id().at(genx)) == pdg_s && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
	  if(abs(genps_id().at(genx)) == pdg_c && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
       
	  if(abs(genps_id().at(genx)) == pdg_b && genps_status().at(genx) == 23) gen_bs.FillCommon(genx);
	  if(abs(genps_id().at(genx)) == pdg_t && genps_status().at(genx) == 52) gen_tops.FillCommon(genx);
    
	  if(abs(genps_id().at(genx)) == pdg_chi_1neutral && genps_status().at(genx) == 1) gen_lsp.FillCommon(genx);
	  if(abs(genps_id().at(genx)) == pdg_chi_1neutral && genps_status().at(genx) == 1) StopEvt.mass_lsp = genps_mass().at(genx);
     
	  if(abs(genps_id().at(genx)) == pdg_stop1 && genps_status().at(genx) == 62) gen_stop.FillCommon(genx);
	  if(abs(genps_id().at(genx)) == pdg_stop2 && genps_status().at(genx) == 62) gen_stop.FillCommon(genx);
	  if(abs(genps_id().at(genx)) == pdg_stop1 && genps_status().at(genx) == 62) StopEvt.mass_stop = genps_mass().at(genx);
	  if(abs(genps_id().at(genx)) == pdg_chi_1plus1 && genps_status().at(genx) == 62) StopEvt.mass_chargino = genps_mass().at(genx);
	}
      }
    
      StopEvt.genlepsfromtop = n_nuelfromt+n_numufromt+n_nutaufromt;
      gen_els.gen_nfromt = n_nuelfromt;
      gen_mus.gen_nfromt = n_numufromt;
      gen_taus.gen_nfromt = n_nutaufromt;

      
      //
      // Trigger Information
      //

      //std::cout << "[babymaker::looper]: filling HLT vars" << std::endl;

      //StopEvt.HLT_SingleMu = passHLTTriggerPattern("HLT_IsoMu20_eta2p1_IterTrk02_v") || passHLTTriggerPattern("HLT_IsoTkMu20_eta2p1_IterTrk02_v");   
      //StopEvt.HLT_SingleEl = passHLTTriggerPattern("HLT_Ele27_WP85_Gsf_v");   
      StopEvt.HLT_MET170 = passHLTTriggerPattern("HLT_PFMET170_NoiseCleaned_v"); 
      StopEvt.HLT_HT350MET120  = passHLTTriggerPattern("HLT_PFHT350_PFMET120_NoiseCleaned_v");
      StopEvt.HLT_HT350MET100 = passHLTTriggerPattern("HLT_PFHT350_PFMET100_NoiseCleaned_v");
      StopEvt.HLT_MET120Btag = passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_BTagCSV07_v") || passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_BTagCSV072_v");
      StopEvt.HLT_MET120Mu5 = passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_Mu5_v");
      StopEvt.HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight = passHLTTriggerPattern("HLT_MonoCentralPFJet80_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight");
      StopEvt.HLT_MET90_MHT90_IDTight = passHLTTriggerPattern("HLT_PFMET90_PFMHT90_IDTight");
      StopEvt.HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight = passHLTTriggerPattern("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight");     

      StopEvt.HLT_DiEl =  passHLTTriggerPattern("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
      StopEvt.HLT_DiMu =  passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") || passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
      StopEvt.HLT_Mu8El17 = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v");
      StopEvt.HLT_Mu8El23 = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
      StopEvt.HLT_Mu17El12 = passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
      StopEvt.HLT_Mu23El12 = passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");

      //notation in RunIISpring15MC is WP85/WP75, for data will have WPLoose and WPTight
      StopEvt.HLT_SingleEl27 = passHLTTriggerPattern("HLT_Ele27_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("HLT_Ele27_WP85_Gsf_v")||passHLTTriggerPattern("Ele27_eta2p1_WPLoose_Gsf_v");//precsaled for 14e33
      StopEvt.HLT_SingleEl27Tight = passHLTTriggerPattern("HLT_Ele27_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("Ele27_eta2p1_WPTight_Gsf_v");//precsaled for 14e33
      StopEvt.HLT_SingleElTight = passHLTTriggerPattern("HLT_Ele32_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("Ele32_eta2p1_WPTight_Gsf_v");
      StopEvt.HLT_SingleEl = passHLTTriggerPattern("HLT_Ele32_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("Ele32_eta2p1_WPLoose_Gsf_v");

      StopEvt.HLT_SingleElHT200 = passHLTTriggerPattern("HLT_Ele27_eta2p1_WP85_Gsf_HT200_v")||passHLTTriggerPattern("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v");

      StopEvt.HLT_SingleMu17 = passHLTTriggerPattern("HLT_IsoMu17_eta2p1_v");
      StopEvt.HLT_SingleMu20 = passHLTTriggerPattern("HLT_IsoMu20_eta2p1_v") || passHLTTriggerPattern("HLT_IsoMu20_v") || passHLTTriggerPattern("HLT_IsoTkMu20_eta2p1_v") || passHLTTriggerPattern("HLT_IsoTkMu20_v");
      StopEvt.HLT_SingleMu24 = passHLTTriggerPattern("HLT_IsoMu24_eta2p1_v") || passHLTTriggerPattern("HLT_IsoTkMu24_eta2p1_v");
      StopEvt.HLT_SingleMuNoEta = passHLTTriggerPattern("HLT_IsoMu27_v") || passHLTTriggerPattern("HLT_IsoTkMu27_v");
      StopEvt.HLT_SingleMuNoIso = passHLTTriggerPattern("HLT_Mu45_eta2p1_v");
      StopEvt.HLT_SingleMuNoIsoNoEta = passHLTTriggerPattern("HLT_Mu50_v");
      StopEvt.HLT_Mu6HT200MET125 = passHLTTriggerPattern("HLT_Mu6_PFHT200_PFMET125_NoiseCleaned_v");
      StopEvt.HLT_SingleMu = passHLTTriggerPattern("HLT_IsoMu24_eta2p1_v") || passHLTTriggerPattern("HLT_IsoTkMu24_eta2p1_v");
      

      //
      // Fill Tree
      //
      BabyTree->Fill();

    
    }//close event loop
    

    //
    // Close input file
    //
    file->Close();
    delete file;

  }//close file loop


  //
  // Write and Close baby file
  //
  BabyFile->cd();
  BabyTree->Write();
  BabyFile->Close();


  //
  // Benchmarking
  //
  bmark->Stop("benchmark");
  

  //
  // Print Skim Cutflow
  //
  cout << endl;
  cout << "Wrote babies into file " << BabyFile->GetName() << endl;
  cout << "-----------------------------" << endl;
  cout << "Events Processed                     " << nEvents_processed << endl;
  cout << "Events with " << skim_nvtx << " Good Vertex            " << nEvents_pass_skim_nVtx << endl;
  cout << "Events with MET > " << skim_met << " GeV             " << nEvents_pass_skim_met << endl;
  cout << "Events with at least " << skim_nGoodLep << " Good Lepton   " << nEvents_pass_skim_nGoodLep << endl;
  cout << "Events with at least " << skim_nJets << " Good Jets     " << nEvents_pass_skim_nJets << endl;
  cout << "-----------------------------" << endl;
  cout << "CPU  Time:   " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;                                                                                          
  cout << "Real Time:   " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  return 0;  

}
