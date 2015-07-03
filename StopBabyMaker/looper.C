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

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;
using namespace tas;
//Switches

struct Lepton{
        int id;
        int idx;
        LorentzVector p4;
      //  Lepton(id, idx, p4) {id = id; idx = idx; p4 = p4;}
};

struct sortbypt{
  bool operator () (const pair<int, LorentzVector> &v1, const pair<int,LorentzVector> &v2)
  {
        return v1.second.pt() > v2.second.pt();
  }
};

struct sortLepbypt{
  bool operator () (const Lepton &lep1, const Lepton &lep2)
  {
        return lep1.p4.pt() > lep2.p4.pt();
  }
};

babyMaker::babyMaker()
{
   StopEvt = EventTree();
   lep1 = LeptonTree("lep1_");
   lep2 = LeptonTree("lep2_");
   jets = JetTree();
   gen_els = GenParticleTree("els_");
   gen_mus = GenParticleTree("mus_");
   gen_leptau_els = GenParticleTree("leptau_els_");
   gen_leptau_mus = GenParticleTree("leptau_mus_");
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

void babyMaker::setSkimVariables(int nvtx, float met, int nlep, float el_pt, float el_eta, float mu_pt, float mu_eta, int njets, float jetpt, float jeteta){
        skim_nvtx = nvtx;
        skim_met = met;

        skim_nlep = nlep;
        skim_elpt = el_pt;
        skim_eleta = el_eta;
        skim_mupt = mu_pt;
        skim_mueta = mu_eta;

        skim_njets = njets;
        skim_jetpt = jetpt;
        skim_jeteta = jeteta;
}

//Main functions
void babyMaker::MakeBabyNtuple(const char* output_name){

  BabyFile = new TFile(Form("%s/%s", babypath, output_name), "RECREATE");
  BabyTree = new TTree("t", "Stop2015 Baby Ntuple");

  //Define Branches
  StopEvt.SetBranches(BabyTree);
  lep1.SetBranches(BabyTree);
  lep2.SetBranches(BabyTree);
  jets.SetBranches(BabyTree);
  gen_els.SetBranches(BabyTree);
  gen_mus.SetBranches(BabyTree);
  gen_leptau_els.SetBranches(BabyTree);
  gen_leptau_mus.SetBranches(BabyTree);
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
    //Clear variables
    StopEvt.Reset();
    lep1.Reset();
    lep2.Reset();
    jets.Reset();
    gen_els.Reset();
    gen_mus.Reset();
    gen_leptau_els.Reset();
    gen_leptau_mus.Reset();
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

//Main function
int babyMaker::looper(TChain* chain, char* output_name, int nEvents, char* path){

   babypath = path;

  // Benchmark
    TBenchmark *bmark = new TBenchmark();
    bmark->Start("benchmark");

    //Set up loop over chain
    unsigned int nEventsDone = 0;
    unsigned int nEvents_GoodVtx = 0;
    unsigned int nEvents_MET30 = 0;
    unsigned int nEvents_GoodLep = 0;
    unsigned int nEvents_2GoodJets = 0;
    unsigned int nEventsToDo = chain->GetEntries();
    unsigned int jet_overlep1_idx = -9999;
    unsigned int jet_overlep2_idx = -9999;
    //unsigned int track_overlep1_idx = -9999;
    //unsigned int track_overlep2_idx = -9999;


  if( nEvents >= 0 ) nEventsToDo = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //Make Baby Ntuple  
  MakeBabyNtuple( Form("%s.root", output_name) );
  //Initialize Baby Ntuple
  InitBabyNtuple();

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) { 

    // Get File Content
    if(nEventsDone >= nEventsToDo) continue;
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("Events");
    cms3.Init(tree);
    cout << "file name is " << file->GetName() << endl;

    // Loop over Events in current file
    unsigned int nEventsTree = tree->GetEntriesFast();

    for(unsigned int evt = 0; evt < nEventsTree; evt++){

      // Get Event Content
      if(nEventsDone >= nEventsToDo) break;
      cms3.GetEntry(evt);
      nEventsDone++;

      // Progress
      CMS3::progress(nEventsDone, nEventsToDo);

      InitBabyNtuple();

//      std::cout << "[babymaker::looper]: filling event vars" << std::endl;
      //Fill Event Variables
      StopEvt.FillCommon(file->GetName()); 
//      std::cout << "[babymaker::looper]: filling event vars completed" << std::endl; 
      //dumpDocLines();
      if(StopEvt.nvtxs<skim_nvtx) continue;
      if(StopEvt.firstGoodVtxIdx!=0) continue;//really check that first vertex is good
      nEvents_GoodVtx++;
      if(evt_pfmet()<skim_met) continue;
      nEvents_MET30++;

     //Lepton Variables
      int nGoodLeptons = 0;//stored lep1,lep2
      //int nGoodandLooseLeptons = 0;
      int nVetoLeptons = 0;
      //std::cout << "[babymaker::looper]: selecting leptons" << std::endl;
      vector<Lepton> GoodLeps;
      vector<Lepton> LooseLeps;
      vector<Lepton> VetoLeps;
      vector<unsigned int> idx_alloverlapjets;
      for (unsigned int eidx = 0; eidx < els_p4().size(); eidx++){
	if(!PassElectronVetoSelections(eidx, 10.,2.4)) continue;
	//if(els_p4().at(eidx).Pt()<10||fabs(els_p4().at(eidx).Eta())>2.4) continue;
	Lepton mylepton;
        mylepton.id  = -11*els_charge().at(eidx);
        mylepton.idx = eidx;
        mylepton.p4  = els_p4().at(eidx);
	int overlapping_jet = getOverlappingJetIndex(mylepton.p4, pfjets_p4() , 0.4, skim_jetpt,skim_jeteta,false);//don't care about jid
	if( overlapping_jet>=0) idx_alloverlapjets.push_back(overlapping_jet);//overlap removal for all jets w.r.t. all leptons
	if(!PassElectronPreSelections(eidx, 20.,2.4)) VetoLeps.push_back(mylepton);//veto, but not loose or good
        if(!PassElectronPreSelections(eidx, 20.,2.4)) continue;
	if(!PassElectronPreSelections(eidx, skim_elpt,skim_eleta)) LooseLeps.push_back(mylepton);//loose, but not good
        if(!PassElectronPreSelections(eidx, skim_elpt,skim_eleta)) continue;  
        GoodLeps.push_back(mylepton);
      }

      for (unsigned int midx = 0; midx < mus_p4().size(); midx++){
	if(!PassMuonVetoSelections(midx, 10.,2.4)) continue;
	//if(mus_p4().at(midx).Pt()<10||fabs(mus_p4().at(midx).Eta())>2.4) continue;
	Lepton mylepton;
        mylepton.id  = -13*mus_charge().at(midx);
        mylepton.idx = midx;
        mylepton.p4  = mus_p4().at(midx);
	int overlapping_jet = getOverlappingJetIndex(mylepton.p4, pfjets_p4() , 0.4, skim_jetpt,skim_jeteta,false);//don't care about jid
	if( overlapping_jet>=0) idx_alloverlapjets.push_back(overlapping_jet);//overlap removal for all jets w.r.t. all leptons
	if(!PassMuonPreSelections(midx, 20.,2.4)) VetoLeps.push_back(mylepton);//veto, but not loose or good
        if(!PassMuonPreSelections(midx, 20.,2.4)) continue;
        if(!PassMuonPreSelections(midx, skim_mupt,skim_mueta)) LooseLeps.push_back(mylepton);//loose, but not good
        if(!PassMuonPreSelections(midx, skim_mupt,skim_mueta)) continue;
        GoodLeps.push_back(mylepton);
      }
      sort(GoodLeps.begin(),GoodLeps.end(),sortLepbypt());       
      sort(LooseLeps.begin(),LooseLeps.end(),sortLepbypt());       
      sort(VetoLeps.begin(),VetoLeps.end(),sortLepbypt());       
      nGoodLeptons = GoodLeps.size();
      if(nGoodLeptons<skim_nlep) continue;
      nEvents_GoodLep++;
      //nGoodandLooseLeptons = GoodLeps.size() + LooseLeps.size();
      nVetoLeptons = GoodLeps.size() + LooseLeps.size() + VetoLeps.size();

      StopEvt.ngoodleps = nGoodLeptons; 
      StopEvt.nvetoleps = nVetoLeptons; 
//      std::cout << "[babymaker::looper]: filling lepton variables" << std::endl;
      lep1.FillCommon(GoodLeps.at(0).id, GoodLeps.at(0).idx);      
      if( nGoodLeptons        >1) lep2.FillCommon(GoodLeps.at(1).id,  GoodLeps.at(1).idx);
      else if(LooseLeps.size()>0) lep2.FillCommon(LooseLeps.at(0).id, LooseLeps.at(0).idx);
      else if(VetoLeps.size() >0) lep2.FillCommon(VetoLeps.at(0).id,  VetoLeps.at(0).idx);
     //get the jets overlapping with the selected leptons
      if(pfjets_p4().size() < 1) continue; 
      jet_overlep1_idx = -9999;
      jet_overlep2_idx = -9999;
      jet_overlep1_idx = getOverlappingJetIndex(lep1.p4, pfjets_p4() , 0.4, skim_jetpt,skim_jeteta,false);//don't care about jid
      if(nVetoLeptons>1) jet_overlep2_idx = getOverlappingJetIndex(lep2.p4, pfjets_p4() , 0.4, skim_jetpt,skim_jeteta,false);//don't care about jid
      
//      std::cout << "[babymaker::looper]: filling jets vars" << std::endl;         
      //jets and b-tag variables feeding the index for the jet overlapping the selected leptons
      jets.SetJetSelection("ak4",skim_jetpt,skim_jeteta,true);//save only jets passing jid
      jets.SetJetSelection("ak8",100.,skim_jeteta,true);//save only jets passing jid
      jets.FillCommon(idx_alloverlapjets, jet_overlep1_idx, jet_overlep2_idx);
      if(jets.ngoodjets < skim_njets) continue;
      nEvents_2GoodJets++;

//       std::cout << "[babymaker::looper]: Calculating Event Variables" << std::endl;
      //DR(lep, leadB) with medium discriminator
      StopEvt.dR_lep_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep1.p4);
      if(nVetoLeptons>1) StopEvt.dR_lep2_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep2.p4);
      //MT2W
      //StopEvt.MT2W = calculateMT2w(jets.ak4pfjets_p4, jets.ak4pfjets_passMEDbtag, lep1.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
      //if(nVetoLeptons>1) StopEvt.MT2W_lep2 = calculateMT2w(jets.ak4pfjets_p4, jets.ak4pfjets_passMEDbtag, lep2.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
      //chi2
      vector<float> dummy_sigma;
      for (size_t idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
	dummy_sigma.push_back(0.1);
      } 
      //add protection for skim settings of no jet requirement.
      if (jets.ak4pfjets_p4.size()>1&&skim_njets>1)
      { StopEvt.hadronic_top_chi2 = calculateChi2(jets.ak4pfjets_p4, dummy_sigma, jets.ak4pfjets_passMEDbtag);
      //Jets & MET
      StopEvt.mindphi_met_j1_j2 =  getMinDphi(StopEvt.pfmet_phi,jets.ak4pfjets_p4.at(0),jets.ak4pfjets_p4.at(1));
      }
//MET & Leptons
      StopEvt.mt_met_lep = calculateMt(lep1.p4, StopEvt.pfmet, StopEvt.pfmet_phi);
      if(nVetoLeptons>1) StopEvt.mt_met_lep2 = calculateMt(lep2.p4, StopEvt.pfmet, StopEvt.pfmet_phi);
      
      StopEvt.dphi_Wlep = DPhi_W_lep(StopEvt.pfmet, StopEvt.pfmet_phi, lep1.p4);
      StopEvt.MET_over_sqrtHT = StopEvt.pfmet/TMath::Sqrt(jets.ak4_HT);
      StopEvt.ak4pfjets_rho = evt_fixgridfastjet_all_rho();
    
      vector<int> jetIndexSortedCSV = JetUtil::JetIndexCSVsorted(jets.ak4pfjets_CSV,jets.ak4pfjets_p4,jets.ak4pfjets_loose_pfid,30.,2.4,true);
      vector<LorentzVector> mybjets; vector<LorentzVector> myaddjets;
      for(unsigned int idx = 0; idx<jetIndexSortedCSV.size(); ++idx){
	if(jets.ak4pfjets_passMEDbtag.at(jetIndexSortedCSV[idx])==true) mybjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
	else if(mybjets.size()<=1 && (mybjets.size()+myaddjets.size())<3) myaddjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
      }
      //looks like all the following variables need jets to be calculated. add protection for skim settings of njets==0
      if(skim_njets>1){
      //MT2W
      StopEvt.MT2W = CalcMT2W_(mybjets,myaddjets,lep1.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
      if(nVetoLeptons>1) StopEvt.MT2W_lep2 = CalcMT2W_(mybjets,myaddjets,lep2.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
      //Topness
      StopEvt.topness = CalcTopness_(0,StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets);
      if(nVetoLeptons>1) StopEvt.topness_lep2 = CalcTopness_(0,StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets);
      StopEvt.topnessMod = CalcTopness_(1,StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets);
      if(nVetoLeptons>1) StopEvt.topnessMod_lep2 = CalcTopness_(1,StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets);
      //MT2(lb,b)
      StopEvt.MT2_lb_b_mass = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,0,true);
      StopEvt.MT2_lb_b = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,0,false);
      if(nVetoLeptons>1) StopEvt.MT2_lb_b_mass_lep2 = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,0,true);
      if(nVetoLeptons>1) StopEvt.MT2_lb_b_lep2 = CalcMT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,0,false);
      //MT2(lb,bqq)
      StopEvt.MT2_lb_bqq_mass = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,true);
      StopEvt.MT2_lb_bqq = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,false);
      if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_mass_lep2 = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,true);
      if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_lep2 = CalcMT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,false);
      
    //Topness
    //vector<LorentzVector > mybjets = JetUtil::BJetSelector(jets.ak4pfjets_p4,jets.ak4pfjets_CSV,MYBTAG,2,3,2);
    //StopEvt.topness=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,0);
    //if(nVetoLeptons>1) StopEvt.Topness_lep2=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,0);
    //StopEvt.TopnessMod_lep1=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,1);
    //if(nVetoLeptons>1) StopEvt.TopnessMod_lep2=Gettopness_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,1);
    //MT2(lb,b)
    //StopEvt.MT2_lb_b_mass_lep1 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,true ,0);
    //StopEvt.MT2_lb_b_lep1 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,false ,0);
    //if(nVetoLeptons>1) StopEvt.MT2_lb_b_mass_lep2 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,true ,0);
    //if(nVetoLeptons>1) StopEvt.MT2_lb_b_lep2 = MT2_lb_b_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,false ,0);
    //MT2(lb,bqq)
    //StopEvt.MT2_lb_bqq_mass_lep1 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,jets.ak4pfjets_p4,true ,0);
    //StopEvt.MT2_lb_bqq_lep1 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,mybjets,jets.ak4pfjets_p4,false ,0);
    //if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_mass_lep2 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,jets.ak4pfjets_p4,true ,0);
    //if(nVetoLeptons>1) StopEvt.MT2_lb_bqq_lep2 = MT2_lb_bqq_(StopEvt.pfmet,StopEvt.pfmet_phi,lep2.p4,mybjets,jets.ak4pfjets_p4,false ,0);
    
    //Mlb + Mjjj
      float minDR1 = 99.; float minDR2 = 99.; //minDR for closest b in Mlb
      int jb1 = -1; int jb2 = -1; int jb3 = -1;//jet indices for Mjjj(lep1)
      int jb21 = -1; int jb22 = -1; int jb23 = -1;//jet indices for Mjjj(lep2)
      for (unsigned int idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
	float myDR = getdphi(jets.ak4pfjets_p4.at(idx).Phi(),lep1.p4.Phi());
	float myDR1 = -1; float myDR2 = -2; float myDR3 = -3;//is actually DPhi now
	if(jb1>=0) myDR1 = getdphi(jets.ak4pfjets_p4.at(jb1).Phi(),lep1.p4.Phi());
	if(jb2>=0) myDR2 = getdphi(jets.ak4pfjets_p4.at(jb2).Phi(),lep1.p4.Phi());
	if(jb3>=0) myDR3 = getdphi(jets.ak4pfjets_p4.at(jb3).Phi(),lep1.p4.Phi());
	if(myDR>myDR1){ jb3 =jb2; jb2 = jb1; jb1 = idx; }
	else if(myDR>myDR2){ jb3 = jb2; jb2 = idx; }
	else if(myDR>myDR3){ jb3 = idx; }
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
          //StopEvt.Mlb_lead_bdiscr = (jets.ak4pfjets_p4.at(idx)+lep1.p4).M();
          //if(nVetoLeptons>1) StopEvt.Mlb_lead_bdiscr_lep2 = (jets.ak4pfjets_p4.at(idx)+lep2.p4).M();
	//}
	if(!(jets.ak4pfjets_passMEDbtag.at(idx)) ) continue;
	myDR = dRbetweenVectors(jets.ak4pfjets_p4.at(idx),lep1.p4);
	if(myDR<minDR1) {
	  StopEvt.Mlb_closestb = (jets.ak4pfjets_p4.at(idx)+lep1.p4).M();
	  minDR1 =myDR;
	}
	if(nVetoLeptons>1){
	  myDR = dRbetweenVectors(jets.ak4pfjets_p4.at(idx),lep2.p4);
	  if(myDR<minDR2) {
	    StopEvt.Mlb_closestb_lep2 = (jets.ak4pfjets_p4.at(idx)+lep2.p4).M();
	    minDR2 = myDR;
	  }
	}
      }
      StopEvt.Mlb_lead_bdiscr = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[0])+lep1.p4).M();
      if(nVetoLeptons>1) StopEvt.Mlb_lead_bdiscr_lep2 = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[0])+lep2.p4).M();
      if(jb3>=0) {//as sorted, jb1 and jb2 also >=0
	StopEvt.Mjjj = (jets.ak4pfjets_p4.at(jb1)+jets.ak4pfjets_p4.at(jb2)+jets.ak4pfjets_p4.at(jb3)).M();
      }
      if(jb23>=0) {//as sorted, jb21 and jb22 also >=0
	StopEvt.Mjjj_lep2 = (jets.ak4pfjets_p4.at(jb21)+jets.ak4pfjets_p4.at(jb22)+jets.ak4pfjets_p4.at(jb23)).M();
      }
    }
      
    //taus
    int vetotaus=0;
//    std::cout << "[babymaker::looper]: tau  vars" << std::endl;

    Taus.tau_IDnames = taus_pf_IDnames();

    for(unsigned int iTau = 0; iTau < taus_pf_p4().size(); iTau++){
      Taus.FillCommon(iTau, 20, 2.4);
      if(isVetoTau(iTau, lep1.p4, lep1.charge)){
         Taus.tau_isVetoTau.push_back(true);
         vetotaus++;
      }else Taus.tau_isVetoTau.push_back(false);
    }
    if(vetotaus<1) StopEvt.PassTauVeto = true;
    else StopEvt.PassTauVeto = false;
    Taus.ngoodtaus = vetotaus;

 // std::cout << "[babymaker::looper]: filling isotrack vars" << std::endl;
    int vetotracks = 0;
    for (unsigned int ipf = 0; ipf < pfcands_p4().size(); ipf++) {
      //some selections
      if(pfcands_charge().at(ipf) == 0) continue;
      if(pfcands_p4().at(ipf).pt() < 5) continue;
      if(fabs(pfcands_dz().at(ipf)) > 0.1) continue;

      //remove everything that is within 0.1 of selected lead and subleading leptons
      if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lep1.p4)<0.1) continue;
      if(nVetoLeptons>1){
          if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lep2.p4)<0.1) continue;
      }
      Tracks.FillCommon(ipf);
      
      if(isVetoTrack(ipf, lep1.p4, lep1.charge)){
         Tracks.isoTracks_isVetoTrack.push_back(true);
         vetotracks++;
      }else Tracks.isoTracks_isVetoTrack.push_back(false);
    }
    if(vetotracks<1) StopEvt.PassTrackVeto = true;
    else StopEvt.PassTrackVeto = false;
    //ttbar counters using neutrinos:
    int n_nutaufromt=0;
    int n_nuelfromt=0;
    int n_numufromt=0;

//    std::cout << "[babymaker::looper]: filling gen particles vars" << std::endl;
    //gen particles
    for(unsigned int genx = 0; genx < genps_p4().size() ; genx++){
      //void GenParticleTree::FillCommon (int idx, int pdgid_=0, int pdgmotherid_=0, int status_=0)
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_leptau_els.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t) n_nuelfromt++;      

      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_leptau_mus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_numufromt++;

      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_nutaufromt++;
      //if(abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx); 

      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);

      if(abs(genps_id().at(genx)) == pdg_d && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_u && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_s && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_c && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
       
      if(abs(genps_id().at(genx)) == pdg_b && genps_status().at(genx) == 23) gen_bs.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_t && genps_status().at(genx) == 62) gen_tops.FillCommon(genx);
    
      if(abs(genps_id().at(genx)) == pdg_chi_1neutral && genps_status().at(genx) == 1) gen_lsp.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_chi_1neutral && genps_status().at(genx) == 1) StopEvt.mass_lsp = genps_mass().at(genx);
     
      if(abs(genps_id().at(genx)) == pdg_stop1 && genps_status().at(genx) == 62) gen_stop.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_stop2 && genps_status().at(genx) == 62) gen_stop.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_stop1 && genps_status().at(genx) == 62) StopEvt.mass_stop = genps_mass().at(genx);
      if(abs(genps_id().at(genx)) == pdg_chi_1plus1 && genps_status().at(genx) == 62) StopEvt.mass_chargino = genps_mass().at(genx);

    }

    StopEvt.genlepsfromtop = n_nuelfromt+n_numufromt+n_nutaufromt;
    gen_els.gen_nfromt = n_nuelfromt;
    gen_mus.gen_nfromt = n_numufromt;
    gen_taus.gen_nfromt = n_nutaufromt;
    // add trigger variables
//     std::cout << "[babymaker::looper]: filling HLT vars" << std::endl;

    StopEvt.HLT_SingleMu = passHLTTriggerPattern("HLT_IsoMu20_eta2p1_IterTrk02_v") || passHLTTriggerPattern("HLT_IsoTkMu20_eta2p1_IterTrk02_v");   
    StopEvt.HLT_SingleEl = passHLTTriggerPattern("HLT_Ele27_WP85_Gsf_v");   
    StopEvt.HLT_MET170 = passHLTTriggerPattern("HLT_PFMET170_NoiseCleaned_v"); 
    StopEvt.HLT_ht350met120  = passHLTTriggerPattern("HLT_PFHT350_PFMET120_NoiseCleaned_v");
    StopEvt.HLT_MET120Btag = passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_BTagCSV07_v");
    StopEvt.HLT_MET120Mu5 = passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_Mu5_v"); 

    BabyTree->Fill();

    }//close event loop
    
    file->Close();
    delete file;

  }//close file loop

  BabyFile->cd();
  BabyTree->Write();
  BabyFile->Close();

  bmark->Stop("benchmark");
  cout << endl;
  cout << "Wrote babies into file " << BabyFile->GetName() << endl;
  cout << "-----------------------------" << endl;
  cout << "Events Processed                     " << nEventsDone << endl;
  cout << "Events with 1 Good Vertex            " << nEvents_GoodVtx << endl;
  cout << "Events with MET > 30 GeV             " << nEvents_MET30 << endl;
  cout << "Events with at least 1 Good Lepton   " << nEvents_GoodLep << endl;
  cout << "Events with at least 2 Good Jets     " << nEvents_2GoodJets << endl;
  cout << "-----------------------------" << endl;
  cout << "CPU  Time:   " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;                                                                                          
  cout << "Real Time:   " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  return 0;  

}
