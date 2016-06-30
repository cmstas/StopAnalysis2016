#include <string.h>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <cmath>
#include <utility>

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
#include "JetCorrector.h"
#include "btagsf/BTagCalibrationStandalone.h"

#include "PhotonSelections.h"
#include "MuonSelections.h"//93991
#include "IsolationTools.h"//93991
#include "MetSelections.h"

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

bool CompareIndexValueGreatest(const std::pair<double, int>& firstElem, const std::pair<double, int>& secondElem) {
  return firstElem.first > secondElem.first;
}
bool CompareIndexValueSmallest(const std::pair<double, int>& firstElem, const std::pair<double, int>& secondElem) {
  return firstElem.first < secondElem.first;
}


//===========//
//           //
// Functions //
//           //
//===========//

babyMaker::babyMaker(){

   StopEvt = EventTree();
   lep1 = LeptonTree("lep1_");
   lep2 = LeptonTree("lep2_");
   ph = PhotonTree("ph_");
   jets = JetTree();
   Taus = TauTree();
   Tracks = IsoTracksTree();
   gen_leps = GenParticleTree("leps_");
   gen_nus = GenParticleTree("nus_");
   gen_qs  = GenParticleTree("qs_");
   gen_bosons = GenParticleTree("bosons_");
   gen_susy = GenParticleTree("susy_");

//obsolete
//   gen_tops = GenParticleTree("ts_");  //merged into gen_qs   
   //gen_els = GenParticleTree("els_");
   //gen_mus = GenParticleTree("mus_");
   //gen_taus = GenParticleTree("taus_");
   //gen_nuels = GenParticleTree("nuels_");
   //gen_numus = GenParticleTree("numus_");
   //gen_nutaus = GenParticleTree("nutaus_");
   //gen_bs  = GenParticleTree("bs_");
   //gen_cs  = GenParticleTree("cs_");
   //gen_glus = GenParticleTree("glus_");
   //gen_ws  = GenParticleTree("ws_");
   //gen_zs  = GenParticleTree("zs_");
   //gen_phs = GenParticleTree("phs_");
   //gen_hs  = GenParticleTree("hs_");


}

void babyMaker::setSkimVariables(int nvtx, float met, int nGoodLep, float goodLep_el_pt, float goodLep_el_eta, float goodLep_mu_pt, float goodLep_mu_eta, float looseLep_el_pt, float looseLep_el_eta, float looseLep_mu_pt, float looseLep_mu_eta, float vetoLep_el_pt, float vetoLep_el_eta, float vetoLep_mu_pt, float vetoLep_mu_eta, bool apply2ndlepveto, int njets, float jet_pt, float jet_eta, float jet_ak8_pt, float jet_ak8_eta, int nbjets, int nphs, float phs_pt, float phs_eta, bool applyJEC, int JES_type_central_up_down,   bool applyLeptonSFs, bool applyVetoLeptonSFs, bool applyBtagSFs, bool isFastsim,bool filltaus_, bool filltracks_, bool fillZll_, bool fillPhoton_,bool fillMETfilt_, bool fill2ndlep_, bool fillExtraEvtVar_, bool fillAK4EF_, bool fillAK4_Other_, bool fillOverleps_, bool fillAK4Synch_, bool fillElID_, bool fillIso_, bool fillLepSynch_){

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

  skim_nBJets          = nbjets;

  skim_jet_ak8_pt      = jet_ak8_pt;
  skim_jet_ak8_eta     = jet_ak8_eta;

  skim_nPhotons        = nphs;
  skim_ph_pt           = phs_pt;
  skim_ph_eta          = phs_eta;
  skim_2ndlepveto      = apply2ndlepveto; 
  applyJECfromFile     = applyJEC;
  JES_type 	       = JES_type_central_up_down;
  skim_applyLeptonSFs  = applyLeptonSFs;
  skim_applyVetoLeptonSFs  = applyVetoLeptonSFs;
  skim_applyBtagSFs    = applyBtagSFs;
  skim_isFastsim       = isFastsim;

  filltaus   = filltaus_;
  filltracks   =filltracks_;
  fillZll   =fillZll_;
  fillPhoton   =fillPhoton_;
  fillMETfilt   =fillMETfilt_;
  fill2ndlep   =fill2ndlep_;
  fillExtraEvtVar   =fillExtraEvtVar_;

  fillAK4EF   =fillAK4EF_;
  fillAK4_Other   =fillAK4_Other_;
  fillOverleps   =fillOverleps_;
  fillAK4Synch   =fillAK4Synch_;
  fillElID   =fillElID_;
  fillIso   =fillIso_;
  fillLepSynch   =fillLepSynch_;
}


void babyMaker::MakeBabyNtuple(const char* output_name){

  //histFile = new TFile(Form("%s/hist_%s", babypath, output_name), "RECREATE");
  BabyFile = new TFile(Form("%s/%s", babypath, output_name), "RECREATE");
  BabyTree = new TTree("t", "Stop2015 Baby Ntuple");

  StopEvt.SetBranches(BabyTree);
  lep1.SetBranches(BabyTree);
  lep2.SetBranches(BabyTree);
  ph.SetBranches(BabyTree);
  jets.SetAK4Branches(BabyTree);
//  Taus.SetBranches(BabyTree);
//  Tracks.SetBranches(BabyTree);
  gen_leps.SetBranches(BabyTree);
  gen_nus.SetBranches(BabyTree);
  gen_qs.SetBranches(BabyTree);
  gen_bosons.SetBranches(BabyTree);
  gen_susy.SetBranches(BabyTree);

  //optional
  if(filltaus)  Taus.SetBranches(BabyTree);
  if(filltracks)  Tracks.SetBranches(BabyTree);

  if(fillZll)  StopEvt.SetZllBranches(BabyTree);
  if(fillPhoton) StopEvt.SetPhotonBranches(BabyTree);
  if(fillMETfilt) StopEvt.SetMETFilterBranches(BabyTree);
  if(fill2ndlep) StopEvt.SetSecondLepBranches(BabyTree);
  if(fillExtraEvtVar) StopEvt.SetExtraVariablesBranches(BabyTree);
 
  if(fillAK4EF)   jets.SetAK4Branches_EF(BabyTree);
  if(fillAK4_Other)  jets.SetAK4Branches_Other(BabyTree);
  if(fillOverleps)  jets.SetAK4Branches_Overleps(BabyTree);
  if(fillAK4Synch)  jets.SetAK4Branches_SynchTools(BabyTree);
  if(fillElID)  lep1.SetBranches_electronID(BabyTree);
  if(fillIso)  lep1.SetBranches_Iso(BabyTree);
  if(fillLepSynch)  lep1.SetBranches_SynchTools(BabyTree);
  if(fillElID)  lep2.SetBranches_electronID(BabyTree);
  if(fillIso)  lep2.SetBranches_Iso(BabyTree);
  if(fillLepSynch)  lep2.SetBranches_SynchTools(BabyTree);

   
//obsolete
  //gen_els.SetBranches(BabyTree);
  //gen_mus.SetBranches(BabyTree);
  //gen_taus.SetBranches(BabyTree);
  //gen_nuels.SetBranches(BabyTree);
  //gen_numus.SetBranches(BabyTree);
  //gen_nutaus.SetBranches(BabyTree);
  //gen_tops.SetBranches(BabyTree);
  //gen_bs.SetBranches(BabyTree);
  //gen_cs.SetBranches(BabyTree);
  //gen_glus.SetBranches(BabyTree);
  //gen_ws.SetBranches(BabyTree);
  //gen_zs.SetBranches(BabyTree);
  //gen_phs.SetBranches(BabyTree);
  //gen_hs.SetBranches(BabyTree); 
}

void babyMaker::InitBabyNtuple(){
  
  StopEvt.Reset();
  lep1.Reset();
  lep2.Reset();
  jets.Reset();
  ph.Reset();
  Taus.Reset();
  Tracks.Reset();
  
  gen_leps.Reset();
  gen_nus.Reset();
  gen_qs.Reset();
  gen_bosons.Reset();
  gen_susy.Reset();

//obsolete
  //gen_els.Reset();
  //gen_mus.Reset();
  //gen_taus.Reset();
  //gen_nuels.Reset();
  //gen_numus.Reset();
  //gen_nutaus.Reset();
  //gen_tops.Reset();
  //gen_bs.Reset();
  //gen_cs.Reset(); 
  //gen_qs.Reset();
  //gen_glus.Reset();
  //gen_ws.Reset();
  //gen_zs.Reset();
  //gen_phs.Reset();
  //gen_lsp.Reset();
  //gen_stop.Reset();
  //gen_tops.Reset();
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
  unsigned int nEvents_pass_skim_nBJets=0;
  unsigned int nEvents_pass_skim_2ndlepVeto=0;
  unsigned int nEventsToDo = chain->GetEntries();
  unsigned int jet_overlep1_idx = -9999;  
  unsigned int jet_overlep2_idx = -9999;

 //unsigned int track_overlep1_idx = -9999;
  //unsigned int track_overlep2_idx = -9999;
  
  if( nEvents >= 0 ) nEventsToDo = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  bool applyJECunc = false;
  if(JES_type != 0) applyJECunc = true; 

  //
  // JEC files
  //
  bool isDataFromFileName;
  bool isSignalFromFileName;
  string filestr(output_name);
  cout<<"output name "<< output_name;
  if (filestr.find("data") != std::string::npos) {
    isDataFromFileName = true;
    isSignalFromFileName = false;
    cout << ", running on DATA, based on file name: " << output_name<<endl;
  } 
  else if((filestr.find("SMS") != std::string::npos) || (filestr.find("Signal") != std::string::npos)){
    isDataFromFileName = false;
    isSignalFromFileName = true;
    cout << ", running on SIGNAL, based on file name: " << output_name<<endl;
  }
  else {
    isDataFromFileName = false;
    isSignalFromFileName = false;
    cout << ", running on MC, based on file name: " << output_name<<endl;
  }

  
  //
  // Open lepton SF histos
  //
  TFile *f_el_SF;
  TFile *f_mu_SF_id;
  TFile *f_mu_SF_iso;
  TFile *f_mu_SF_veto_id;
  TFile *f_mu_SF_veto_iso;

  TFile *f_el_FS_ID;
  TFile *f_el_FS_Iso;
  TFile *f_mu_FS_ID;
  TFile *f_mu_FS_Iso;

  TFile *f_vetoLep_eff;
  
  TH2D *h_el_SF = NULL;
  TH2D *h_mu_SF = NULL;
  TH2D *h_el_SF_veto = NULL;
  TH2D *h_mu_SF_veto = NULL;

  TH2D *h_el_FS = NULL;
  TH2D *h_mu_FS = NULL;

  TH2D *h_el_vetoLepEff = NULL;
  TH2D *h_mu_vetoLepEff = NULL;
  
  double matched_dr = 0.1;
  
  if( (skim_applyLeptonSFs || skim_applyVetoLeptonSFs) && !isDataFromFileName){
    
    f_el_SF       = new TFile("lepsf/kinematicBinSFele.root", "read");

    f_mu_SF_id    = new TFile("lepsf/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
    f_mu_SF_iso   = new TFile("lepsf/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");

    f_mu_SF_veto_id  = new TFile("lepsf/TnP_MuonID_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
    f_mu_SF_veto_iso = new TFile("lepsf/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");

    
    f_el_FS_ID       = new TFile("lepsf/sf_el_mediumCB.root", "read");
    f_el_FS_Iso      = new TFile("lepsf/sf_el_mini01.root", "read");

    f_mu_FS_ID       = new TFile("lepsf/sf_mu_mediumID.root", "read");
    f_mu_FS_Iso      = new TFile("lepsf/sf_mu_mini02.root", "read");
    
    f_vetoLep_eff = new TFile("lepsf/lepeff__ttbar_powheg_pythia8_25ns__SRcuts.root", "read");

    
    TH2D *h_el_SF_id_temp      = (TH2D*)f_el_SF->Get("CutBasedMedium");
    TH2D *h_el_SF_iso_temp     = (TH2D*)f_el_SF->Get("MiniIso0p1_vs_AbsEta");
    TH2D *h_el_SF_veto_id_temp  = (TH2D*)f_el_SF->Get("CutBasedVeto");
    TH2D *h_el_SF_veto_iso_temp = (TH2D*)f_el_SF->Get("MiniIso0p4_vs_AbsEta");
    
    TH2D *h_mu_SF_id_temp      = (TH2D*)f_mu_SF_id->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
    TH2D *h_mu_SF_iso_temp     = (TH2D*)f_mu_SF_iso->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");
    
    TH2D *h_mu_SF_veto_id_temp  = (TH2D*)f_mu_SF_veto_id->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
    TH2D *h_mu_SF_veto_iso_temp = (TH2D*)f_mu_SF_veto_iso->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");
    

    TH2D *h_el_FS_ID_temp  = (TH2D*)f_el_FS_ID->Get("histo2D");
    TH2D *h_el_FS_Iso_temp = (TH2D*)f_el_FS_Iso->Get("histo2D");
    
    TH2D *h_mu_FS_ID_temp  = (TH2D*)f_mu_FS_ID->Get("histo2D");
    TH2D *h_mu_FS_Iso_temp = (TH2D*)f_mu_FS_Iso->Get("histo2D");
    
    
    TH2D *h_el_vetoLepEff_temp = (TH2D*)f_vetoLep_eff->Get("h2_lepEff_vetoSel_rebin_Eff_el");
    TH2D *h_mu_vetoLepEff_temp = (TH2D*)f_vetoLep_eff->Get("h2_lepEff_vetoSel_rebin_Eff_mu");
    
    //BabyFile->cd();
    
    TH2D *h_el_SF_id  = (TH2D*)h_el_SF_id_temp->Clone("h_el_SF_id");
    TH2D *h_el_SF_iso = (TH2D*)h_el_SF_iso_temp->Clone("h_el_SF_iso");
    TH2D *h_mu_SF_id  = (TH2D*)h_mu_SF_id_temp->Clone("h_mu_SF_id");
    TH2D *h_mu_SF_iso = (TH2D*)h_mu_SF_iso_temp->Clone("h_mu_SF_iso");
    
    TH2D *h_el_SF_veto_id  = (TH2D*)h_el_SF_veto_id_temp->Clone("h_el_SF_veto_id");
    TH2D *h_el_SF_veto_iso = (TH2D*)h_el_SF_veto_iso_temp->Clone("h_el_SF_veto_iso");
    TH2D *h_mu_SF_veto_id  = (TH2D*)h_mu_SF_veto_id_temp->Clone("h_mu_SF_veto_id");
    TH2D *h_mu_SF_veto_iso = (TH2D*)h_mu_SF_veto_iso_temp->Clone("h_mu_SF_veto_iso");
    
    h_el_FS          = (TH2D*)h_el_FS_ID_temp->Clone("h_el_FS");
    h_el_FS->Multiply(h_el_FS_Iso_temp);

    h_mu_FS          = (TH2D*)h_mu_FS_ID_temp->Clone("h_mu_FS");
    h_mu_FS->Multiply(h_mu_FS_Iso_temp);


    h_el_vetoLepEff = (TH2D*)h_el_vetoLepEff_temp->Clone("h_el_vetoLepEff");
    h_mu_vetoLepEff = (TH2D*)h_mu_vetoLepEff_temp->Clone("h_mu_vetoLepEff");

    h_el_SF = (TH2D*)h_el_SF_id->Clone("h_el_SF");
    h_el_SF->Multiply(h_el_SF_iso);

    h_el_SF_veto = (TH2D*)h_el_SF_veto_id->Clone("h_el_SF_veto");
    h_el_SF_veto->Multiply(h_el_SF_veto_iso);

    h_mu_SF = (TH2D*)h_mu_SF_id->Clone("h_mu_SF");
    h_mu_SF->Multiply(h_mu_SF_iso);

    h_mu_SF_veto = (TH2D*)h_mu_SF_veto_id->Clone("h_mu_SF_veto");
    h_mu_SF_veto->Multiply(h_mu_SF_veto_iso);
        
  }
  

  TFile *fxsec;
  TH1D *hxsec;
  if(isSignalFromFileName){
    //fxsec = TFile::Open("xsec_stop_13TeV.root");
    fxsec = new TFile("xsec_stop_13TeV.root","READ");
    if(fxsec->IsZombie()) {
      std::cout << "Somehow xsec_stop_13TeV.root is corrupted. Exit..." << std::endl;
      exit(0);
    }
    hxsec = (TH1D*)fxsec->Get("stop");
  }
  TFile *pileupfile;
  TH1D *hPU;
  TH1D *hPUup;
  TH1D *hPUdown;
  if(!isDataFromFileName){
    pileupfile = new TFile("puWeights_2015data_2p2fbinv.root","READ");
    if(pileupfile->IsZombie()) {
      std::cout << "Somehow puWeights_2015data_2p2fbinv.root is corrupted. Exit..." << std::endl;
      exit(0);
    }
    hPU     = (TH1D*)pileupfile->Get("puWeight");
    hPUup   = (TH1D*)pileupfile->Get("puWeightUp");
    hPUdown = (TH1D*)pileupfile->Get("puWeightDown");
  }
  
  TH1D* counterhist = new TH1D( "h_counter", "h_counter", 24, 0.5,24.5);
  counterhist->Sumw2();
  counterhist->GetXaxis()->SetBinLabel(1,"nominal,muR=1 muF=1");
  counterhist->GetXaxis()->SetBinLabel(2,"muR=1 muF=2");
  counterhist->GetXaxis()->SetBinLabel(3,"muR=1 muF=0.5");
  counterhist->GetXaxis()->SetBinLabel(4,"muR=2 muF=1");
  counterhist->GetXaxis()->SetBinLabel(5,"muR=2 muF=2");
  counterhist->GetXaxis()->SetBinLabel(6,"muR=2 muF=0.5");
  counterhist->GetXaxis()->SetBinLabel(7,"muR=0.5 muF=1");
  counterhist->GetXaxis()->SetBinLabel(8,"muR=0.5 muF=2");
  counterhist->GetXaxis()->SetBinLabel(9,"muR=0.5 muF=0.5");
  counterhist->GetXaxis()->SetBinLabel(10,"pdf_up");
  counterhist->GetXaxis()->SetBinLabel(11,"pdf_down");
  counterhist->GetXaxis()->SetBinLabel(12,"pdf_alphas_var_1");
  counterhist->GetXaxis()->SetBinLabel(13,"pdf_alphas_var_2");
  counterhist->GetXaxis()->SetBinLabel(14,"weight_btagsf");
  counterhist->GetXaxis()->SetBinLabel(15,"weight_btagsf_heavy_UP");
  counterhist->GetXaxis()->SetBinLabel(16,"weight_btagsf_light_UP");
  counterhist->GetXaxis()->SetBinLabel(17,"weight_btagsf_heavy_DN");
  counterhist->GetXaxis()->SetBinLabel(18,"weight_btagsf_light_DN");
  counterhist->GetXaxis()->SetBinLabel(19,"weight_ISR_nominal");
  counterhist->GetXaxis()->SetBinLabel(20,"weight_ISR_up");
  counterhist->GetXaxis()->SetBinLabel(21,"weight_ISR_down");
  counterhist->GetXaxis()->SetBinLabel(22,"NEvents");
  counterhist->GetXaxis()->SetBinLabel(23,"weight_btagsf_fastsim_UP");
  counterhist->GetXaxis()->SetBinLabel(24,"weight_btagsf_fastsim_DN");

  TH3D* counterhistSig;
  TH2F* histNEvts;//count #evts per signal point
  if(isSignalFromFileName){//create histos only for signals
    counterhistSig = new TH3D( "h_counterSMS", "h_counterSMS", 37,99,1024, 19,-1,474, 23, 0.5,23.5);//15000 bins!
    counterhistSig->Sumw2();
    counterhistSig->GetZaxis()->SetBinLabel(1,"nominal,muR=1 muF=1");
    counterhistSig->GetZaxis()->SetBinLabel(2,"muR=1 muF=2");
    counterhistSig->GetZaxis()->SetBinLabel(3,"muR=1 muF=0.5");
    counterhistSig->GetZaxis()->SetBinLabel(4,"muR=2 muF=1");
    counterhistSig->GetZaxis()->SetBinLabel(5,"muR=2 muF=2");
    counterhistSig->GetZaxis()->SetBinLabel(6,"muR=2 muF=0.5");
    counterhistSig->GetZaxis()->SetBinLabel(7,"muR=0.5 muF=1");
    counterhistSig->GetZaxis()->SetBinLabel(8,"muR=0.5 muF=2");
    counterhistSig->GetZaxis()->SetBinLabel(9,"muR=0.5 muF=0.5");
    counterhistSig->GetZaxis()->SetBinLabel(10,"pdf_up");
    counterhistSig->GetZaxis()->SetBinLabel(11,"pdf_down");
    counterhistSig->GetZaxis()->SetBinLabel(12,"pdf_alphas_var_1");
    counterhistSig->GetZaxis()->SetBinLabel(13,"pdf_alphas_var_2");
    counterhistSig->GetZaxis()->SetBinLabel(14,"weight_btagsf");
    counterhistSig->GetZaxis()->SetBinLabel(15,"weight_btagsf_heavy_UP");
    counterhistSig->GetZaxis()->SetBinLabel(16,"weight_btagsf_light_UP");
    counterhistSig->GetZaxis()->SetBinLabel(17,"weight_btagsf_heavy_DN");
    counterhistSig->GetZaxis()->SetBinLabel(18,"weight_btagsf_light_DN");
    counterhistSig->GetZaxis()->SetBinLabel(19,"weight_ISR_nominal");
    counterhistSig->GetZaxis()->SetBinLabel(20,"weight_ISR_up");
    counterhistSig->GetZaxis()->SetBinLabel(21,"weight_ISR_down");
    counterhistSig->GetZaxis()->SetBinLabel(22,"weight_btagsf_fastsim_UP");
    counterhistSig->GetZaxis()->SetBinLabel(23,"weight_btagsf_fastsim_DN");
    histNEvts = new TH2F( "histNEvts", "h_histNEvts", 37,99,1024, 19,-1,474);//x=mStop, y=mLSP
    histNEvts->Sumw2();
  }


  //
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
  const char* json_file = "json_files/Cert_271036-275125_13TeV_PromptReco_Collisions16_JSON.txt";
  set_goodrun_file_json(json_file);
  
  //
  // JEC files
  //
  std::vector<std::string> jetcorr_filenames_pfL1FastJetL2L3;
  FactorizedJetCorrector *jet_corrector_pfL1FastJetL2L3(0);
  JetCorrectionUncertainty* jetcorr_uncertainty(0);
  jetcorr_filenames_pfL1FastJetL2L3.clear();
  std::string jetcorr_uncertainty_filename;

  // files for RunIISpring15 MC
  if (isDataFromFileName) {
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Spring16_25nsV3_DATA_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Spring16_25nsV3_DATA_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Spring16_25nsV3_DATA_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Spring16_25nsV3_DATA_L2L3Residual_AK4PFchs.txt");
    jetcorr_uncertainty_filename = "jecfiles/Spring16_25nsV3_DATA_Uncertainty_AK4PFchs.txt";
  } else if(isSignalFromFileName){
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Fastsim15_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Fastsim15_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Fastsim15_L3Absolute_AK4PFchs.txt");
    jetcorr_uncertainty_filename = "jecfiles/Fastsim15_Uncertainty_AK4PFchs.txt";
  }  
  else {
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Spring16_25nsV3_MC_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Spring16_25nsV3_MC_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jecfiles/Spring16_25nsV3_MC_L3Absolute_AK4PFchs.txt");
    jetcorr_uncertainty_filename = "jecfiles/Spring16_25nsV3_MC_Uncertainty_AK4PFchs.txt";
  }

  cout << "applying JEC from the following files:" << endl;
  for (unsigned int ifile = 0; ifile < jetcorr_filenames_pfL1FastJetL2L3.size(); ++ifile) {
    cout << "   " << jetcorr_filenames_pfL1FastJetL2L3.at(ifile) << endl;
  }

  jet_corrector_pfL1FastJetL2L3  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3);
  
  if (!isDataFromFileName && applyJECunc != 0) {
    cout << "applying JEC uncertainties with weight " << applyJECunc << " from file: " << endl
	 << "   " << jetcorr_uncertainty_filename << endl;
    jetcorr_uncertainty = new JetCorrectionUncertainty(jetcorr_uncertainty_filename);
  }

  //
  // Get bad events from txt files
  //
  //StopEvt.SetMetFilterEvents();
  // btagging scale factor//
  //
  if (skim_applyBtagSFs) {
    //reader_heavy = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "central"); // central
    //reader_heavy_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "up");  // sys up
    //reader_heavy_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "down");  // sys down
    //reader_light = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central");  // central
   // reader_light_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up");  // sys up
   // reader_light_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down");  // sys down

    // get btag efficiencies
    TFile* f_btag_eff;
    if(!skim_isFastsim) f_btag_eff = new TFile("btagsf/btageff__ttbar_powheg_pythia8_25ns.root");
    else f_btag_eff = new TFile("btagsf/btageff__SMS-T1bbbb-T1qqqq_fastsim.root");
    TH2D* h_btag_eff_b_temp = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_b");
    TH2D* h_btag_eff_c_temp = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_c");
    TH2D* h_btag_eff_udsg_temp = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_udsg");

    BabyFile->cd();
    h_btag_eff_b = (TH2D*) h_btag_eff_b_temp->Clone("h_btag_eff_b");
    h_btag_eff_c = (TH2D*) h_btag_eff_c_temp->Clone("h_btag_eff_c");
    h_btag_eff_udsg = (TH2D*) h_btag_eff_udsg_temp->Clone("h_btag_eff_udsg");
    f_btag_eff->Close(); 
 }    
   jets.InitBtagSFTool(h_btag_eff_b,h_btag_eff_c,h_btag_eff_udsg, skim_isFastsim); 
   

  //
  // File Loop
  //
  while ( (currentFile = (TFile*)fileIter.Next()) ) { 
    //
    // Get File Content
    //
    if(nEvents_processed >= nEventsToDo) continue;
    TFile file( currentFile->GetTitle() );
    TTree *tree = (TTree*)file.Get("Events");
    cms3.Init(tree);
    TString thisfilename = file.GetName();
    cout << "file name is " << file.GetName() << endl;

    bool isbadrawMET = false;
    if(thisfilename.Contains("V07-04-12_miniaodv1_FS")){
      cout << "This file seems to have a badrawMET, thus MET needs to be recalculated" << endl;
      isbadrawMET = true;
    }

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
      // calculate sum of weights and save them in a hisogram.
      //      
      float pdf_weight_up = 1;
      float pdf_weight_down = 1;
      float sum_of_weights= 0;
      float average_of_weights= 0;

    counterhist->Fill(22,1.);
    if(!evt_isRealData()){
       //error on pdf replicas
      if(genweights().size()>109){ 
        for(int ipdf=9;ipdf<109;ipdf++){
           average_of_weights += cms3.genweights().at(ipdf);        
           }// average of weights
         average_of_weights =  average_of_weights/100;
 
        for(int ipdf=9;ipdf<109;ipdf++){
           sum_of_weights += (cms3.genweights().at(ipdf)- average_of_weights)*(cms3.genweights().at(ipdf)-average_of_weights);          
          }//std of weights.     

          pdf_weight_up = (average_of_weights+sqrt(sum_of_weights/99)); 
          pdf_weight_down = (average_of_weights-sqrt(sum_of_weights/99)); 
          StopEvt.pdf_up_weight = pdf_weight_up;
          StopEvt.pdf_down_weight = pdf_weight_down;
          counterhist->Fill(1,genweights()[0]);  
          counterhist->Fill(2,genweights()[1]);  
          counterhist->Fill(3,genweights()[2]);  
          counterhist->Fill(4,genweights()[3]);  
          counterhist->Fill(5,genweights()[4]);  
          counterhist->Fill(6,genweights()[5]);  
          counterhist->Fill(7,genweights()[6]);  
          counterhist->Fill(8,genweights()[7]);  
          counterhist->Fill(9,genweights()[8]);  
          counterhist->Fill(10,pdf_weight_up);  
          counterhist->Fill(11,pdf_weight_down);  
          counterhist->Fill(12,genweights()[109]); // α_s variation. 
          counterhist->Fill(13,genweights()[110]); // α_s variation. 
        }
      }
      //////////////////////////////////////////
      // If data, check against good run list//
      /////////////////////////////////////////
      if( evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()) ) continue;
      if( evt_isRealData() ) {
	DorkyEventIdentifier id(evt_run(), evt_event(), evt_lumiBlock());
	if (is_duplicate(id) ) continue;
      }

      //
      // Fill Event Variables
      //
      //std::cout << "[babymaker::looper]: filling event vars" << std::endl;
      StopEvt.FillCommon(file.GetName()); 
      //std::cout << "[babymaker::looper]: filling event vars completed" << std::endl; 
      //dumpDocLines();
      if(!StopEvt.is_data){
	StopEvt.weight_PU     = hPU    ->GetBinContent(hPU    ->FindBin(StopEvt.pu_ntrue));
	StopEvt.weight_PUup   = hPUup  ->GetBinContent(hPUup  ->FindBin(StopEvt.pu_ntrue));
	StopEvt.weight_PUdown = hPUdown->GetBinContent(hPUdown->FindBin(StopEvt.pu_ntrue));
      }

      //This must come before any continue affecting signal scans
      if(isSignalFromFileName){
	//get stop and lsp mass from sparms
	for(unsigned int nsparm = 0; nsparm<sparm_names().size(); ++nsparm){
	  //if(sparm_names().at(nsparm).Contains("mGluino")) StopEvt.mass_stop = sparm_values().at(nsparm);//dummy for testing as only T1's exist
	  if(sparm_names().at(nsparm).Contains("mStop")) StopEvt.mass_stop = sparm_values().at(nsparm);
	  if(sparm_names().at(nsparm).Contains("mCharg")) StopEvt.mass_chargino = sparm_values().at(nsparm);
	  if(sparm_names().at(nsparm).Contains("mLSP")) StopEvt.mass_lsp = sparm_values().at(nsparm);
          if(sparm_names().at(nsparm).Contains("mGl")) StopEvt.mass_gluino = sparm_values().at(nsparm);
	}
	//std::cout << "Got signal mass point mStop " << StopEvt.mass_stop << " mLSP " << StopEvt.mass_lsp << std::endl;
	if(genps_weight()>0) histNEvts->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,1);
	else if(genps_weight()<0) histNEvts->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,-1);
	StopEvt.xsec = hxsec->GetBinContent(hxsec->FindBin(StopEvt.mass_stop));
	StopEvt.xsec_uncert = hxsec->GetBinError(hxsec->FindBin(StopEvt.mass_stop));
	//note to get correct scale1fb you need to use in your looper xsec/nevt, where nevt you get via
	//histNEvts->GetBinContent(histNEvts->FindBin(StopEvt.mass_stop,StopEvt.mass_lsp));

        //copy from Mia's code
        float SMSpdf_weight_up = 1;
        float SMSpdf_weight_down = 1;
        float SMSsum_of_weights= 0;
        float SMSaverage_of_weights= 0;
        //error on pdf replicas
        if(genweights().size()>109){ //fix segfault
          for(int ipdf=9;ipdf<109;ipdf++){
            SMSaverage_of_weights += cms3.genweights().at(ipdf);
          }// average of weights
          SMSaverage_of_weights =  average_of_weights/100.;
          for(int ipdf=9;ipdf<109;ipdf++){
            SMSsum_of_weights += pow(cms3.genweights().at(ipdf)- SMSaverage_of_weights,2);
          }//std of weights.
          SMSpdf_weight_up = (average_of_weights+sqrt(SMSsum_of_weights/99.));
          SMSpdf_weight_down = (average_of_weights-sqrt(SMSsum_of_weights/99.));
          StopEvt.pdf_up_weight = SMSpdf_weight_up;//overwrite here, although it should not matter
          StopEvt.pdf_down_weight = SMSpdf_weight_down;//overwrite here, although it should not matter
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,1,genweights()[0]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,2,genweights()[1]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,3,genweights()[2]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,4,genweights()[3]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,5,genweights()[4]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,6,genweights()[5]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,7,genweights()[6]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,8,genweights()[7]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,9,genweights()[8]);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,10,SMSpdf_weight_up);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,11,SMSpdf_weight_down);
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,12,genweights()[109]); // α_s variation. 
          counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,13,genweights()[110]); // α_s variation.
        }
      }// is signal
      //
      // Gen Information - now goes first
      //
      //std::cout << "[babymaker::looper]: filling gen particles vars" << std::endl;
    
      //ttbar counters using neutrinos:
      int n_nutaufromt=0;
      int n_nuelfromt=0;
      int n_numufromt=0;

      int nLepsHardProcess=0;
      int nNusHardProcess=0;

      bool ee0lep=false;
      bool ee1lep=false;
      bool ge2lep=false;
      bool zToNuNu=false;

      TString thisFile = chain->GetFile()->GetName();
      bool isstopevent = false;
      bool istopevent = false;
      bool isWevent = false;
      bool isZevent = false;

      if(thisFile.Contains("DYJets") || thisFile.Contains("ZJets") ||
	 thisFile.Contains("ZZ") || thisFile.Contains("WZ") ||
	 thisFile.Contains("TTZ") || thisFile.Contains("tZq") )
	isZevent = true;
      if(thisFile.Contains("WJets") ||
	 thisFile.Contains("WW") || thisFile.Contains("WZ") ||
	 thisFile.Contains("TTW") )
	isWevent = true;
      if(thisFile.Contains("TTJets") || thisFile.Contains("TTTo2L2Nu") || thisFile.Contains("TT_") ||
	 thisFile.Contains("ST_") || thisFile.Contains("tZq") ||
	 thisFile.Contains("TTW") || thisFile.Contains("TTZ") )
	istopevent = true;
      if(isSignalFromFileName ||
	 thisFile.Contains("T2tt") || thisFile.Contains("T2tb") || thisFile.Contains("T2bW") )
	isstopevent = true;

      //gen particles
      if (!evt_isRealData()){
	for(unsigned int genx = 0; genx < genps_p4().size() ; genx++){
	  if( genps_id().at(genx)==genps_id_simplemother().at(genx) && !genps_isLastCopy().at(genx) ) continue;

	  if( genps_isHardProcess().at(genx) ||
	      genps_fromHardProcessDecayed().at(genx) ||
	      genps_fromHardProcessFinalState().at(genx) ||
	      genps_isLastCopy().at(genx) ||
	      genps_status().at(genx)==1 ){
     	    
	    if( abs(genps_id().at(genx)) == pdg_el  ||  abs(genps_id().at(genx)) == pdg_mu || abs(genps_id().at(genx)) == pdg_tau) gen_leps.FillCommon(genx);
	    if( abs(genps_id().at(genx)) == pdg_numu || abs(genps_id().at(genx)) == pdg_nue || abs(genps_id().at(genx)) == pdg_nutau ) gen_nus.FillCommon(genx);
	    if( abs(genps_id().at(genx)) == pdg_t || abs(genps_id().at(genx)) == pdg_b || abs(genps_id().at(genx)) == pdg_c || abs(genps_id().at(genx)) == pdg_s || abs(genps_id().at(genx)) == pdg_d ||abs(genps_id().at(genx)) == pdg_u   ) gen_qs.FillCommon(genx);
	    if( abs(genps_id().at(genx)) == pdg_W || abs(genps_id().at(genx)) == pdg_Z ||(abs(genps_id().at(genx)) == pdg_ph &&
                genps_p4().at(genx).Pt()>5.0)  || abs(genps_id().at(genx)) == pdg_h  ) gen_bosons.FillCommon(genx);

            //add all SUSY particles
            if(abs(genps_id().at(genx))>=1000000&&abs(genps_id().at(genx))<=1000040) gen_susy.FillCommon(genx);	    
 
	    if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t) n_nuelfromt++;      
	    
	    if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_numufromt++;
	    
	    if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_nutaufromt++;

	    if( abs(genps_id().at(genx))==pdg_el  && genps_fromHardProcessFinalState().at(genx) && genps_isLastCopy().at(genx) ) nLepsHardProcess++;
	    if( abs(genps_id().at(genx))==pdg_mu  && genps_fromHardProcessFinalState().at(genx) && genps_isLastCopy().at(genx) ) nLepsHardProcess++;
	    if( abs(genps_id().at(genx))==pdg_tau && genps_fromHardProcessDecayed().at(genx) && genps_isLastCopy().at(genx) ) nLepsHardProcess++;
	    
	    if( abs(genps_id().at(genx))==pdg_nue   && genps_fromHardProcessFinalState().at(genx) && genps_isLastCopy().at(genx) ) nNusHardProcess++;
	    if( abs(genps_id().at(genx))==pdg_numu  && genps_fromHardProcessFinalState().at(genx) && genps_isLastCopy().at(genx) ) nNusHardProcess++;
	    if( abs(genps_id().at(genx))==pdg_nutau && genps_fromHardProcessFinalState().at(genx) && genps_isLastCopy().at(genx) ) nNusHardProcess++;

	  }	  
	}
	//use babies genparticles
	LorentzVector hardsystem;
	hardsystem.SetPxPyPzE(0.,0.,0.,0.);
	if(isstopevent){
	  for(unsigned int genx = 0; genx < gen_susy.id.size() ; genx++){
	    if(abs(gen_susy.id.at(genx))==pdg_stop1 && gen_susy.isLastCopy.at(genx)) hardsystem += gen_susy.p4.at(genx);
	  }
	}
	if(istopevent){
	  for(unsigned int genx = 0; genx < gen_qs.id.size() ; genx++){
	    if(abs(gen_qs.id.at(genx))==pdg_t && gen_qs.isLastCopy.at(genx)) hardsystem += gen_qs.p4.at(genx);
	  }
	}
	if(isWevent){
	  for(unsigned int genx = 0; genx < gen_bosons.id.size() ; genx++){
	    if(abs(gen_bosons.id.at(genx))==pdg_W && abs(gen_bosons.id.at(genx))!=pdg_t && gen_bosons.isLastCopy.at(genx)) hardsystem +=+ gen_bosons.p4.at(genx);
	  }
	}
	if(isZevent){
	  for(unsigned int genx = 0; genx < gen_bosons.id.size() ; genx++){
	    if(abs(gen_bosons.id.at(genx))==pdg_Z && abs(gen_bosons.id.at(genx))!=pdg_t && gen_bosons.isLastCopy.at(genx)) hardsystem += gen_bosons.p4.at(genx);
	  }
	}
	StopEvt.hardgenpt = hardsystem.Pt();
	StopEvt.weight_ISR = 1.;
	//caution - hardcoded
	//note - these weights don't contain the renormalization
	if(StopEvt.hardgenpt>600.) {
	  StopEvt.weight_ISRup = 1.3;
	  StopEvt.weight_ISRdown = 0.7;
	} else if(StopEvt.hardgenpt>400.) {
	  StopEvt.weight_ISRup = 1.15;
	  StopEvt.weight_ISRdown = 0.85;
	} else {
	  StopEvt.weight_ISRup = 1.;
	  StopEvt.weight_ISRdown = 1.;
	}
	counterhist->Fill(19,StopEvt.weight_ISR);
	counterhist->Fill(20,StopEvt.weight_ISRup);
	counterhist->Fill(21,StopEvt.weight_ISRdown);
	if(isSignalFromFileName){
	  counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,19,StopEvt.weight_ISR);
	  counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,20,StopEvt.weight_ISRup);
	  counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,21,StopEvt.weight_ISRdown);
	}
      }//no data

      // Gen lepton counting and event classification
      StopEvt.genlepsfromtop = n_nuelfromt+n_numufromt+n_nutaufromt;
      gen_leps.gen_nfromt = n_nuelfromt+ n_numufromt + n_nutaufromt;
      //gen_els.gen_nfromt = n_nuelfromt;
      //gen_mus.gen_nfromt = n_numufromt;
      //gen_taus.gen_nfromt = n_nutaufromt;
 
      StopEvt.genLepsHardProcess = nLepsHardProcess;
      StopEvt.genNusHardProcess  = nNusHardProcess;

      if(nLepsHardProcess==0) ee0lep=true;
      if(nLepsHardProcess==1) ee1lep=true;
      if(nLepsHardProcess>=2) ge2lep=true;
      
      if( thisFile.Contains("DYJets") ||
	  thisFile.Contains("ZJets")  ||
	  thisFile.Contains("ZZ")        ){
	if(nNusHardProcess>=2) zToNuNu=true;
      }
      if( thisFile.Contains("WZ")  ||
	  thisFile.Contains("TTZ") ||
	  thisFile.Contains("tZq")    ){
	if(nNusHardProcess-nLepsHardProcess>=2) zToNuNu=true;
      }

      if( zToNuNu )    { StopEvt.isZtoNuNu=1; StopEvt.is0lep=0; StopEvt.is1lep=0; StopEvt.is2lep=0; }
      else if( ee0lep ){ StopEvt.isZtoNuNu=0; StopEvt.is0lep=1;	StopEvt.is1lep=0; StopEvt.is2lep=0; }
      else if( ee1lep ){ StopEvt.isZtoNuNu=0; StopEvt.is0lep=0; StopEvt.is1lep=1; StopEvt.is2lep=0; }
      else if( ge2lep ){ StopEvt.isZtoNuNu=0; StopEvt.is0lep=0; StopEvt.is1lep=0; StopEvt.is2lep=1; }

      if( (ee1lep) && ((StopEvt.genLepsHardProcess-StopEvt.genlepsfromtop)>0) )  StopEvt.is1lepFromW=1;
      else StopEvt.is1lepFromW=0;

      if( (ee1lep) && ((StopEvt.genLepsHardProcess-StopEvt.genlepsfromtop)==0) ) StopEvt.is1lepFromTop=1;
      else StopEvt.is1lepFromTop=0;      
      
      //
      // nVertex Cut
      //
      if(StopEvt.nvtxs < skim_nvtx) continue;
      if(StopEvt.firstGoodVtxIdx!=0) continue; //really check that first vertex is good
      nEvents_pass_skim_nVtx++;
      //keep those here - any event without vertex is BS
      //save met here because of JEC
      if(applyJECfromFile){
        pair<float,float> newmet;
        if(!evt_isRealData() && applyJECunc){
	  if(JES_type > 0)  newmet = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3, jetcorr_uncertainty,true,isbadrawMET);
	  else if(JES_type < 0)  newmet = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3, jetcorr_uncertainty,false,isbadrawMET);
	  else cout << "This should not happen" << endl;
        }
	else if(isbadrawMET) newmet = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3,NULL,0,isbadrawMET);
	else newmet = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3);
	StopEvt.pfmet = newmet.first;
	StopEvt.pfmet_phi = newmet.second;
	if(TMath::IsNaN(StopEvt.pfmet)||(!TMath::Finite(StopEvt.pfmet))||StopEvt.pfmet>14000.) continue;
      }
      else{
	StopEvt.pfmet = evt_pfmet();
	StopEvt.pfmet_phi = evt_pfmetPhi();
      }

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
	int overlapping_jet = getOverlappingJetIndex(mylepton.p4, pfjets_p4(), 0.4, skim_jet_pt, skim_jet_eta, false,jet_corrector_pfL1FastJetL2L3,applyJECfromFile,jetcorr_uncertainty,JES_type,skim_isFastsim);  //don't care about jid
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
	int overlapping_jet = getOverlappingJetIndex(mylepton.p4, pfjets_p4() , 0.4, skim_jet_pt, skim_jet_eta,false,jet_corrector_pfL1FastJetL2L3,applyJECfromFile,jetcorr_uncertainty,JES_type,skim_isFastsim);  //don't care about jid
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
      int nLooseLeptons = GoodLeps.size() + LooseLeps.size();//use for Zll
      nVetoLeptons = GoodLeps.size() + LooseLeps.size() + VetoLeps.size();
      
      StopEvt.ngoodleps  = nGoodLeptons; 
//      StopEvt.nlooseleps = nLooseLeptons; //why are these needed?
      StopEvt.nvetoleps  = nVetoLeptons; 
      
      //std::cout << "[babymaker::looper]: filling lepton variables" << std::endl;
      AllLeps.clear();
      AllLeps.insert( AllLeps.end(), GoodLeps.begin(),  GoodLeps.end() );
      AllLeps.insert( AllLeps.end(), LooseLeps.begin(), LooseLeps.end() );
      AllLeps.insert( AllLeps.end(), VetoLeps.begin(),  VetoLeps.end() );
      if( nVetoLeptons > 0 ) lep1.FillCommon( AllLeps.at(0).id, AllLeps.at(0).idx );
      if( nVetoLeptons > 1 ) lep2.FillCommon( AllLeps.at(1).id, AllLeps.at(1).idx );


      // Lepton SFs
      float lepSF_pt_cutoff = 100.0;
      float lepSF_pt_min    = 10.0;
      
      double lepSF    = 1.0;
      double lepSF_Up = 1.0;
      double lepSF_Dn = 1.0;
      
      double vetoLepSF    = 1.0;
      double vetoLepSF_Up = 1.0;
      double vetoLepSF_Dn = 1.0;


      float lepSF_FS_pt_cutoff = 200.0;
      float lepSF_FS_pt_min    = 10.0;

      double lepSF_FS    = 1.0;
      double lepSF_FS_Up = 1.0;
      double lepSF_FS_Dn = 1.0;	
      
      // Lep1 SF
      if(skim_applyLeptonSFs && !StopEvt.is_data && nVetoLeptons>0){
	
	if(abs(lep1.pdgid) == pdg_el){
	  int binX = h_el_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, (float)lep1.p4.Pt()) );
	  int binY = h_el_SF->GetYaxis()->FindBin( fabs(lep1.p4.Eta()) );
	  lepSF    = h_el_SF->GetBinContent( binX, binY );
	  lepSF_Up = lepSF + h_el_SF->GetBinError( binX, binY );
	  lepSF_Dn = lepSF - h_el_SF->GetBinError( binX, binY );
	  
	  if(skim_isFastsim){
	    int bin_FS  = h_el_FS->FindBin( std::min(lepSF_FS_pt_cutoff, (float)lep1.p4.Pt()), fabs(lep1.p4.Eta()) );
	    lepSF_FS    = h_el_FS->GetBinContent(bin_FS);
	    lepSF_FS_Up = lepSF_FS + h_el_FS->GetBinError(bin_FS);
	    lepSF_FS_Dn = lepSF_FS + h_el_FS->GetBinError(bin_FS);
	  }
	  
	}
	
	if(abs(lep1.pdgid) == pdg_mu){
	  int binX = h_mu_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, (float)lep1.p4.Pt()) );
	  int binY = h_mu_SF->GetYaxis()->FindBin( fabs(lep1.p4.Eta()) );
	  lepSF    = h_mu_SF->GetBinContent( binX, binY );
	  lepSF_Up = lepSF + h_mu_SF->GetBinError( binX, binY );
	  lepSF_Dn = lepSF - h_mu_SF->GetBinError( binX, binY );
	  
	  if(skim_isFastsim){
	    int bin_FS  = h_mu_FS->FindBin( std::min(lepSF_FS_pt_cutoff, (float)lep1.p4.Pt()), fabs(lep1.p4.Eta()) );
	    lepSF_FS    = h_mu_FS->GetBinContent(bin_FS);
	    lepSF_FS_Up = lepSF_FS + h_mu_FS->GetBinError(bin_FS);
	    lepSF_FS_Dn = lepSF_FS + h_mu_FS->GetBinError(bin_FS);
	  }

	}
		    
      }
      
      // Lep2 SF
      if( skim_applyLeptonSFs && !StopEvt.is_data && nVetoLeptons>1 ){
	
	if(abs(lep2.pdgid) == pdg_el){
	  
	  int binX = h_el_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, (float)lep2.p4.Pt()) );
	  int binY = h_el_SF->GetYaxis()->FindBin( fabs(lep2.p4.Eta()) );
	  lepSF    *= h_el_SF->GetBinContent( binX, binY );
	  lepSF_Up *= ( lepSF + h_el_SF->GetBinError( binX, binY ) );
	  lepSF_Dn *= ( lepSF - h_el_SF->GetBinError( binX, binY ) );
	  
	  if(skim_isFastsim){
	    int bin_FS  = h_el_FS->FindBin( std::min(lepSF_FS_pt_cutoff, (float)lep2.p4.Pt()), fabs(lep2.p4.Eta()) );
	    lepSF_FS    *= h_el_FS->GetBinContent(bin_FS);
	    lepSF_FS_Up *= (lepSF_FS + h_el_FS->GetBinError(bin_FS));
	    lepSF_FS_Dn *= (lepSF_FS + h_el_FS->GetBinError(bin_FS));
	  }

	}
	
	if(abs(lep2.pdgid) == pdg_mu){
	  int binX = h_mu_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, (float)lep2.p4.Pt()) );
	  int binY = h_mu_SF->GetYaxis()->FindBin( fabs(lep2.p4.Eta()) );
	  lepSF    *= h_mu_SF->GetBinContent( binX, binY );
	  lepSF_Up *= ( lepSF + h_mu_SF->GetBinError( binX, binY ) );
	  lepSF_Dn *= ( lepSF - h_mu_SF->GetBinError( binX, binY ) );
	}
	
	if(skim_isFastsim){
	  int bin_FS  = h_mu_FS->FindBin( std::min(lepSF_FS_pt_cutoff, (float)lep2.p4.Pt()), fabs(lep2.p4.Eta()) );
	  lepSF_FS    *= h_mu_FS->GetBinContent(bin_FS);
	  lepSF_FS_Up *= lepSF_FS + h_mu_FS->GetBinError(bin_FS);
	  lepSF_FS_Dn *= lepSF_FS + h_mu_FS->GetBinError(bin_FS);
	}


      }
      
      // If only 1 reco lepton, and is2lep event, then find lost gen lepton
      if( skim_applyVetoLeptonSFs && !StopEvt.is_data && nVetoLeptons==1 && StopEvt.is2lep ){
	
	for(int iGen=0; iGen<(int)gen_leps.p4.size(); iGen++){
	  if( abs(gen_leps.id.at(iGen))!=11 && abs(gen_leps.id.at(iGen))!=13 ) continue;
	  if( !gen_leps.fromHardProcessFinalState.at(iGen) ) continue;
	  if( !gen_leps.isLastCopy.at(iGen) ) continue;
	  if( ROOT::Math::VectorUtil::DeltaR(gen_leps.p4.at(iGen), lep1.p4)<matched_dr ) continue;
	  if( gen_leps.p4.at(iGen).Pt()<5 || fabs(gen_leps.p4.at(iGen).Eta())>2.4 ) continue;
	  
	  TH2D *h_vetoLep_eff = NULL;
	  if( abs(gen_leps.id.at(iGen))==11 ) h_vetoLep_eff = h_el_vetoLepEff;
	  if( abs(gen_leps.id.at(iGen))==13 ) h_vetoLep_eff = h_mu_vetoLepEff;
	  
	  int binX_eff = h_vetoLep_eff->GetXaxis()->FindBin( std::max( std::min(lepSF_pt_cutoff, (float)gen_leps.p4.at(iGen).Pt()), lepSF_pt_min ) );
	  int binY_eff = h_vetoLep_eff->GetYaxis()->FindBin( fabs(gen_leps.p4.at(iGen).Eta()) );
	  double vetoEff = h_vetoLep_eff->GetBinContent( binX_eff, binY_eff );
	  
	  TH2D *h_lep_sf = NULL;
	  if( abs(gen_leps.id.at(iGen))==11 ) h_lep_sf = h_el_SF_veto;
	  if( abs(gen_leps.id.at(iGen))==13 ) h_lep_sf = h_mu_SF_veto;

	  int binX_sf = h_lep_sf->GetXaxis()->FindBin( std::max( std::min(lepSF_pt_cutoff, (float)gen_leps.p4.at(iGen).Pt()), lepSF_pt_min ) );
	  int binY_sf = h_lep_sf->GetYaxis()->FindBin( fabs(gen_leps.p4.at(iGen).Eta()) );
	  
	  double vetoLepSF_temp    = h_lep_sf->GetBinContent( binX_sf, binY_sf );
	  double vetoLepSF_temp_Up = vetoLepSF_temp + h_lep_sf->GetBinError( binX_sf, binY_sf );
	  double vetoLepSF_temp_Dn = vetoLepSF_temp - h_lep_sf->GetBinError( binX_sf, binY_sf );
	  
	  
	  if( vetoEff==1.0 ){
	    vetoLepSF    = 1.0;
	    vetoLepSF_Up = 1.0;
	    vetoLepSF_Dn = 1.0;
	  }
	  else{
	    vetoLepSF    = ( 1-(vetoEff*vetoLepSF_temp) )/( 1-vetoEff );
	    vetoLepSF_Up = ( 1-(vetoEff*vetoLepSF_temp_Up) )/( 1-vetoEff );
	    vetoLepSF_Dn = ( 1-(vetoEff*vetoLepSF_temp_Dn) )/( 1-vetoEff );	    
	  }
	  
	  break; // break after finding 2nd hard gen lepton

	} // end loop over gen leptons
      
      } // end if finding gen lost lepton for vetoEff SF
      
      StopEvt.weight_lepSF      = lepSF;
      StopEvt.weight_lepSF_up   = lepSF_Up;
      StopEvt.weight_lepSF_down = lepSF_Dn;

      StopEvt.weight_vetoLepSF      = vetoLepSF;
      StopEvt.weight_vetoLepSF_up   = vetoLepSF_Up;
      StopEvt.weight_vetoLepSF_down = vetoLepSF_Dn;
      
      StopEvt.weight_lepSF_fastSim      = lepSF_FS;
      StopEvt.weight_lepSF_fastSim_up   = lepSF_FS_Up;
      StopEvt.weight_lepSF_fastSim_down = lepSF_FS_Dn;
      

      //
      // Jet Selection
       float btagprob_data = 1.;
       float btagprob_mc = 1.;
       float btagprob_err_heavy_UP = 0.;
       float btagprob_err_heavy_DN = 0.;
       float btagprob_err_light_UP = 0.;
       float btagprob_err_light_DN = 0.;
       float btagprob_err_FS_UP = 0.;
       float btagprob_err_FS_DN = 0.;
 
      //std::cout << "[babymaker::looper]: filling jets vars" << std::endl;         
      // Get the jets overlapping with the selected leptons
      if(pfjets_p4().size() > 0){
	jet_overlep1_idx = -9999;
	jet_overlep2_idx = -9999;
	if(nVetoLeptons>0) jet_overlep1_idx = getOverlappingJetIndex(lep1.p4, pfjets_p4(), 0.4, skim_jet_pt, skim_jet_eta, false,jet_corrector_pfL1FastJetL2L3,applyJECfromFile,jetcorr_uncertainty,JES_type,skim_isFastsim);  //don't care about jid
	if(nVetoLeptons>1) jet_overlep2_idx = getOverlappingJetIndex(lep2.p4, pfjets_p4(), 0.4, skim_jet_pt, skim_jet_eta, false,jet_corrector_pfL1FastJetL2L3,applyJECfromFile,jetcorr_uncertainty,JES_type,skim_isFastsim);  //don't care about jid
	
	// Jets and b-tag variables feeding the index for the jet overlapping the selected leptons
	jets.SetJetSelection("ak4", skim_jet_pt, skim_jet_eta, true); //save only jets passing jid
	jets.SetJetSelection("ak8", skim_jet_ak8_pt, skim_jet_ak8_eta, true); //save only jets passing jid
        jets.FillCommon(idx_alloverlapjets, jet_corrector_pfL1FastJetL2L3,btagprob_data,btagprob_mc,btagprob_err_heavy_UP, btagprob_err_heavy_DN, btagprob_err_light_UP,btagprob_err_light_DN,btagprob_err_FS_UP,btagprob_err_FS_DN,jet_overlep1_idx, jet_overlep2_idx,applyJECfromFile,jetcorr_uncertainty,JES_type, skim_applyBtagSFs, skim_isFastsim);
      }

      // SAVE B TAGGING SF 
     if (!evt_isRealData() && skim_applyBtagSFs) {
        StopEvt.weight_btagsf = btagprob_data / btagprob_mc;
        StopEvt.weight_btagsf_heavy_UP = StopEvt.weight_btagsf + btagprob_err_heavy_UP*StopEvt.weight_btagsf;
        StopEvt.weight_btagsf_light_UP = StopEvt.weight_btagsf + btagprob_err_light_UP*StopEvt.weight_btagsf;
        StopEvt.weight_btagsf_heavy_DN = StopEvt.weight_btagsf - btagprob_err_heavy_DN*StopEvt.weight_btagsf;
        StopEvt.weight_btagsf_light_DN = StopEvt.weight_btagsf - btagprob_err_light_DN*StopEvt.weight_btagsf;
 	StopEvt.weight_btagsf_fastsim_UP = StopEvt.weight_btagsf + btagprob_err_FS_UP*StopEvt.weight_btagsf;
        StopEvt.weight_btagsf_fastsim_DN = StopEvt.weight_btagsf - btagprob_err_FS_DN*StopEvt.weight_btagsf;
      }
     // save the sum of weights for normalization offline to n-babies.
     // comment: this has to go before the skim_nBJets - else you create a bias
     if(!evt_isRealData() && skim_applyBtagSFs) {
       counterhist->Fill(14,StopEvt.weight_btagsf);
       counterhist->Fill(15,StopEvt.weight_btagsf_heavy_UP);
       counterhist->Fill(16,StopEvt.weight_btagsf_light_UP);
       counterhist->Fill(17,StopEvt.weight_btagsf_heavy_DN);
       counterhist->Fill(18,StopEvt.weight_btagsf_light_DN);
       counterhist->Fill(23,StopEvt.weight_btagsf_fastsim_UP);
       counterhist->Fill(24,StopEvt.weight_btagsf_fastsim_DN);
     }
     if(isSignalFromFileName && !evt_isRealData() && skim_applyBtagSFs){
       counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,14,StopEvt.weight_btagsf);
       counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,15,StopEvt.weight_btagsf_heavy_UP);
       counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,16,StopEvt.weight_btagsf_light_UP);
       counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,17,StopEvt.weight_btagsf_heavy_DN);
       counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,18,StopEvt.weight_btagsf_light_DN);
       counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,22,StopEvt.weight_btagsf_fastsim_UP);
       counterhistSig->Fill(StopEvt.mass_stop,StopEvt.mass_lsp,23,StopEvt.weight_btagsf_fastsim_DN);
     }

     // 
     // met Cut
      //
      if(StopEvt.pfmet < skim_met) continue;
      nEvents_pass_skim_met++;

      if(nGoodLeptons < skim_nGoodLep) continue;
      nEvents_pass_skim_nGoodLep++;

      if(jets.ngoodjets < skim_nJets) continue;
      nEvents_pass_skim_nJets++;
      if(jets.ngoodbtags < skim_nBJets) continue;
      nEvents_pass_skim_nBJets++;


      //
      // Photon Selection
      //
      ph.SetPhotonSelection(skim_ph_pt, skim_ph_eta);
      ph.FillCommon();
      StopEvt.nPhotons = ph.p4.size();
      if(StopEvt.nPhotons < skim_nPhotons) continue;
      int leadph = -1;//use this in case we have a wide photon selection (like loose id), but want to use specific photon
      for(unsigned int i = 0; i<ph.p4.size(); ++i){
	int overlapping_jet = getOverlappingJetIndex(ph.p4.at(i), jets.ak4pfjets_p4, 0.4, skim_jet_pt, skim_jet_eta,false,jet_corrector_pfL1FastJetL2L3,applyJECfromFile,jetcorr_uncertainty,JES_type,skim_isFastsim);
	ph.overlapJetId.at(i) = overlapping_jet;
	if(leadph!=-1 && ph.p4.at(i).Pt()<ph.p4.at(leadph).Pt()) continue;
	if(StopEvt.ngoodleps>0 && ROOT::Math::VectorUtil::DeltaR(ph.p4.at(i), lep1.p4)<0.2) continue;
	if(StopEvt.ngoodleps>1 && ROOT::Math::VectorUtil::DeltaR(ph.p4.at(i), lep2.p4)<0.2) continue;
	leadph = i;
      }
      StopEvt.ph_selectedidx = leadph;

      //
      // Event Variables
      //

      // MET & Leptons
      if(nVetoLeptons>0) StopEvt.mt_met_lep = calculateMt(lep1.p4, StopEvt.pfmet, StopEvt.pfmet_phi);
      if(nVetoLeptons>1) StopEvt.mt_met_lep2 = calculateMt(lep2.p4, StopEvt.pfmet, StopEvt.pfmet_phi);
      if(nVetoLeptons>0) StopEvt.dphi_Wlep = DPhi_W_lep(StopEvt.pfmet, StopEvt.pfmet_phi, lep1.p4);
      if(jets.ak4pfjets_p4.size()> 0) StopEvt.MET_over_sqrtHT = StopEvt.pfmet/TMath::Sqrt(jets.ak4_HT);

      StopEvt.ak4pfjets_rho = evt_fixgridfastjet_all_rho();

      vector<int> jetIndexSortedCSV;
      if(skim_isFastsim) jetIndexSortedCSV = JetUtil::JetIndexCSVsorted(jets.ak4pfjets_CSV, jets.ak4pfjets_p4, jets.ak4pfjets_loose_pfid, skim_jet_pt, skim_jet_eta, false);
      else jetIndexSortedCSV = JetUtil::JetIndexCSVsorted(jets.ak4pfjets_CSV, jets.ak4pfjets_p4, jets.ak4pfjets_loose_pfid, skim_jet_pt, skim_jet_eta, true);
      vector<LorentzVector> mybjets; vector<LorentzVector> myaddjets;
      for(unsigned int idx = 0; idx<jetIndexSortedCSV.size(); ++idx){
	if(jets.ak4pfjets_passMEDbtag.at(jetIndexSortedCSV[idx])==true) mybjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
	else if(mybjets.size()<=1 && (mybjets.size()+myaddjets.size())<3) myaddjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
      }

     // looks like all the following variables need jets to be calculated. 
      //   add protection for skim settings of njets<2
      vector<float> dummy_sigma; dummy_sigma.clear(); //move outside of if-clause to be able to copy for photon selection
      for (size_t idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
	dummy_sigma.push_back(0.1);
      } 
      if(jets.ak4pfjets_p4.size()>1){

	// DR(lep, leadB) with medium discriminator
	if(nVetoLeptons>0) StopEvt.dR_lep_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep1.p4);
	if(nVetoLeptons>1) StopEvt.dR_lep2_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep2.p4);
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
        //MT2(l,l)
        if(nVetoLeptons>1) StopEvt.MT2_l_l = CalcMT2_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,lep2.p4,false,0); 
      }

      vector<pair<float, int> > rankminDR; 
      vector<pair<float, int> > rankmaxDPhi;
      vector<pair<float, int> > rankminDR_lep2;
      vector<pair<float, int> > rankmaxDPhi_lep2;
      for (unsigned int idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
	if(nVetoLeptons==0) continue;
	pair<float, int> mypair;
	mypair.second = idx;
	mypair.first = getdphi(jets.ak4pfjets_p4.at(idx).Phi(),lep1.p4.Phi());
	rankmaxDPhi.push_back(mypair);
	mypair.first = dRbetweenVectors(jets.ak4pfjets_p4.at(idx),lep1.p4);
	rankminDR.push_back(mypair);
	if(nVetoLeptons<=1) continue;
	mypair.first = getdphi(jets.ak4pfjets_p4.at(idx).Phi(),lep2.p4.Phi());
	rankmaxDPhi_lep2.push_back(mypair);
	mypair.first = dRbetweenVectors(jets.ak4pfjets_p4.at(idx),lep2.p4);
	rankminDR_lep2.push_back(mypair);
      }
      sort(rankminDR.begin(),        rankminDR.end(),        CompareIndexValueSmallest);
      sort(rankminDR_lep2.begin(),   rankminDR_lep2.end(),   CompareIndexValueSmallest);
      sort(rankmaxDPhi.begin(),      rankmaxDPhi.end(),      CompareIndexValueGreatest);
      sort(rankmaxDPhi_lep2.begin(), rankmaxDPhi_lep2.end(), CompareIndexValueGreatest);

      if(jets.ak4pfjets_p4.size()>0){
	for (unsigned int idx = 0; idx < rankminDR.size(); ++idx){
	  if(nVetoLeptons==0) continue;
	  if(!(jets.ak4pfjets_passMEDbtag.at(rankminDR[idx].second)) ) continue;
	  StopEvt.Mlb_closestb = (jets.ak4pfjets_p4.at(rankminDR[idx].second)+lep1.p4).M();
	  break;
	}
	for (unsigned int idx = 0; idx < rankminDR_lep2.size(); ++idx){
	  if(nVetoLeptons<=1) continue;
	  if(!(jets.ak4pfjets_passMEDbtag.at(rankminDR_lep2[idx].second)) ) continue;
	  StopEvt.Mlb_closestb_lep2 = (jets.ak4pfjets_p4.at(rankminDR_lep2[idx].second)+lep2.p4).M();
	  break;
	}
	if(nVetoLeptons>0) StopEvt.Mlb_lead_bdiscr = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[0])+lep1.p4).M();
	if(nVetoLeptons>1) StopEvt.Mlb_lead_bdiscr_lep2 = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[0])+lep2.p4).M();
	if(rankmaxDPhi.size()>=3) {
	  StopEvt.Mjjj = (jets.ak4pfjets_p4.at(rankmaxDPhi[0].second)+jets.ak4pfjets_p4.at(rankmaxDPhi[1].second)+jets.ak4pfjets_p4.at(rankmaxDPhi[2].second)).M();
	}
	if(rankmaxDPhi_lep2.size()>=3) {
	  StopEvt.Mjjj_lep2 = (jets.ak4pfjets_p4.at(rankmaxDPhi_lep2[0].second)+jets.ak4pfjets_p4.at(rankmaxDPhi_lep2[1].second)+jets.ak4pfjets_p4.at(rankmaxDPhi_lep2[2].second)).M();
	  //StopEvt.Mjjj_lep2 = (jets.ak4pfjets_p4.at(jb21)+jets.ak4pfjets_p4.at(jb22)+jets.ak4pfjets_p4.at(jb23)).M();
	}
	
      } // end if >0 jets      

      if(fillZll){
      //
      // Zll Event Variables
      //
      //  first find a Zll
      //  fill only for 2 or three lepton events//Zl2 will have always idx 1(2) for 2l(3l) events
      //  if four lepton events test only leading three leptons
      //  Zll must be always OS, then prefer OF, then prefer Zmass
      //  Zll needs to go before ph, as we recalculate myaddjets, mybjets
      if(nLooseLeptons>=2){
	int Zl1 = -1;
	if(nLooseLeptons==2 && AllLeps[0].id*AllLeps[1].id<0) Zl1 = 0;
	else if(nLooseLeptons>=3){
	  if(     nGoodLeptons==1 && AllLeps[1].id*AllLeps[2].id<0) Zl1 = 1;//0 is taken by selection lepton
	  else if(nGoodLeptons>=2){//selection lepton can be either 0(lep1) or 1(lep2)
	    if(     (AllLeps[0].id*AllLeps[2].id)<0 && (AllLeps[1].id*AllLeps[2].id)>0) Zl1 = 0;
	    else if((AllLeps[0].id*AllLeps[2].id)>0 && (AllLeps[1].id*AllLeps[2].id)<0) Zl1 = 1;
	    else if((AllLeps[0].id*AllLeps[2].id)<0 && (AllLeps[1].id*AllLeps[2].id)<0){
	      if(      (abs(AllLeps[0].id)==abs(AllLeps[2].id)) && !(abs(AllLeps[1].id)==abs(AllLeps[2].id))) Zl1 = 0;
	      else if(!(abs(AllLeps[0].id)==abs(AllLeps[2].id)) &&  (abs(AllLeps[1].id)==abs(AllLeps[2].id))) Zl1 = 1;
	      else {//Z will be SF/OF for either combination, decide on Zmass
		if(fabs((AllLeps[0].p4+AllLeps[2].p4).M()-91.)>fabs((AllLeps[1].p4+AllLeps[2].p4).M()-91.)) Zl1 = 1; 
		else Zl1 = 0; 
	      }
	    }
	  }
	}//end of Zl1 selection
	if(Zl1>=0){//found a Zll candidate
	  int Zl2 = -1; 
	  if(nLooseLeptons==2) Zl2 = 1; 
	  else Zl2 = 2;
	  StopEvt.Zll_idl1 = AllLeps[Zl1].id;
	  StopEvt.Zll_idl2 = AllLeps[Zl2].id;
	  StopEvt.Zll_p4l1 = AllLeps[Zl1].p4;
	  StopEvt.Zll_p4l2 = AllLeps[Zl2].p4;
	  StopEvt.Zll_OS = (AllLeps[Zl1].id*AllLeps[Zl2].id<0);
	  StopEvt.Zll_SF = (abs(AllLeps[Zl1].id)==abs(AllLeps[Zl2].id));
	  StopEvt.Zll_isZmass = (fabs((AllLeps[Zl1].p4+AllLeps[Zl2].p4).M()-91.)<15);
	  StopEvt.Zll_M = (AllLeps[Zl1].p4+AllLeps[Zl2].p4).M();
	  StopEvt.Zll_p4 = (AllLeps[Zl1].p4+AllLeps[Zl2].p4);
	  if(nLooseLeptons==2) StopEvt.Zll_selLep = 1;//selection lepton (not Zll) is lep1
	  else if(Zl1==0) StopEvt.Zll_selLep = 2;//selection lepton (not Zll) is lep2
	  else StopEvt.Zll_selLep = 1;//selection lepton (not Zll) is lep1
	  //Zll_selLep decides if one has to use Mlb_closestb or Mlb_closestb_lep2 for variables without MET.
	  //it also decides if we recalculate mt_met_lep using lep1 or lep2, etc.
	  double Zllmetpx = ( StopEvt.pfmet * cos(StopEvt.pfmet_phi) ) + ( StopEvt.Zll_p4.Px() );
	  double Zllmetpy = ( StopEvt.pfmet * sin(StopEvt.pfmet_phi) ) + ( StopEvt.Zll_p4.Py() );
	  StopEvt.Zll_met     = sqrt(pow(Zllmetpx,2)+pow(Zllmetpy,2) );
	  StopEvt.Zll_met_phi = atan2(Zllmetpy,Zllmetpx);
	  if(jets.ak4pfjets_p4.size()>1) StopEvt.Zll_mindphi_met_j1_j2 =  getMinDphi(StopEvt.Zll_met_phi,jets.ak4pfjets_p4.at(0),jets.ak4pfjets_p4.at(1));
          if(nVetoLeptons>2) StopEvt.Zll_MT2_l_l = CalcMT2_(StopEvt.pfmet,StopEvt.pfmet_phi,AllLeps[Zl1].p4,AllLeps[Zl2].p4,false,0);
	  if(StopEvt.Zll_selLep == 1){
	    StopEvt.Zll_mt_met_lep = calculateMt(lep1.p4, StopEvt.Zll_met, StopEvt.Zll_met_phi);
	    StopEvt.Zll_dphi_Wlep = DPhi_W_lep(StopEvt.Zll_met, StopEvt.Zll_met_phi, lep1.p4);
	    if(jets.ak4pfjets_p4.size()>1){
	      StopEvt.Zll_MT2W = CalcMT2W_(mybjets,myaddjets,lep1.p4,StopEvt.Zll_met, StopEvt.Zll_met_phi);
	      StopEvt.Zll_topness = CalcTopness_(0,StopEvt.Zll_met, StopEvt.Zll_met_phi,lep1.p4,mybjets,myaddjets);	
	      StopEvt.Zll_topnessMod = CalcTopness_(1,StopEvt.Zll_met, StopEvt.Zll_met_phi,lep1.p4,mybjets,myaddjets);
	      StopEvt.Zll_MT2_lb_b_mass = CalcMT2_lb_b_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep1.p4,mybjets,myaddjets,0,true);
	      StopEvt.Zll_MT2_lb_b = CalcMT2_lb_b_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep1.p4,mybjets,myaddjets,0,false);
	      StopEvt.Zll_MT2_lb_bqq_mass = CalcMT2_lb_bqq_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep1.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,true);
	      StopEvt.Zll_MT2_lb_bqq = CalcMT2_lb_bqq_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep1.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,false);
	    }
	  } else {
	    StopEvt.Zll_mt_met_lep = calculateMt(lep2.p4, StopEvt.Zll_met, StopEvt.Zll_met_phi);
	    StopEvt.Zll_dphi_Wlep = DPhi_W_lep(StopEvt.Zll_met, StopEvt.Zll_met_phi, lep2.p4);
	    if(jets.ak4pfjets_p4.size()>1){
	      StopEvt.Zll_MT2W = CalcMT2W_(mybjets,myaddjets,lep2.p4,StopEvt.Zll_met, StopEvt.Zll_met_phi);
	      StopEvt.Zll_topness = CalcTopness_(0,StopEvt.Zll_met, StopEvt.Zll_met_phi,lep2.p4,mybjets,myaddjets);	
	      StopEvt.Zll_topnessMod = CalcTopness_(1,StopEvt.Zll_met, StopEvt.Zll_met_phi,lep2.p4,mybjets,myaddjets);
	      StopEvt.Zll_MT2_lb_b_mass = CalcMT2_lb_b_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep2.p4,mybjets,myaddjets,0,true);
	      StopEvt.Zll_MT2_lb_b = CalcMT2_lb_b_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep2.p4,mybjets,myaddjets,0,false);
	      StopEvt.Zll_MT2_lb_bqq_mass = CalcMT2_lb_bqq_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep2.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,true);
	      StopEvt.Zll_MT2_lb_bqq = CalcMT2_lb_bqq_(StopEvt.Zll_met, StopEvt.Zll_met_phi,lep2.p4,mybjets,myaddjets,jets.ak4pfjets_p4,0,false);
	    }
	  }
	}//end of Zll filling
      }//end of Zll
    }
 
    if(fillPhoton){ 
     //
      // Photon Event Variables
      //
      if(StopEvt.ph_selectedidx>=0){
	int oljind = ph.overlapJetId.at(StopEvt.ph_selectedidx);
	double phmetpx = ( StopEvt.pfmet * cos(StopEvt.pfmet_phi) ) + ( ph.p4.at(StopEvt.ph_selectedidx).Px() );
	double phmetpy = ( StopEvt.pfmet * sin(StopEvt.pfmet_phi) ) + ( ph.p4.at(StopEvt.ph_selectedidx).Py() );
	StopEvt.ph_met     = sqrt(pow(phmetpx,2)+pow(phmetpy,2) );
	StopEvt.ph_met_phi = atan2(phmetpy,phmetpx);
	StopEvt.ph_ngoodjets = jets.ngoodjets;
	StopEvt.ph_ngoodbtags = jets.ngoodbtags;
	if(oljind>=0){
	  StopEvt.ph_ngoodjets = jets.ngoodjets-1;
	  if(jets.ak4pfjets_passMEDbtag.at(oljind)==true) StopEvt.ph_ngoodbtags = jets.ngoodbtags-1;
	}
	vector<LorentzVector> jetsp4_phcleaned; jetsp4_phcleaned.clear();//used
	vector<float>         jetsCSV_phcleaned; jetsCSV_phcleaned.clear();
	vector<bool>          jetsbtag_phcleaned; jetsbtag_phcleaned.clear();
	vector<float>         dummy_sigma_phcleaned; dummy_sigma_phcleaned.clear();//used
	int leadbidx = -1;
	float htph(0), htssmph(0), htosmph(0);
	for (unsigned int idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
	  if((int)idx==oljind) continue;
	  jetsp4_phcleaned.push_back(jets.ak4pfjets_p4.at(idx));
	  jetsCSV_phcleaned.push_back(jets.ak4pfjets_CSV.at(idx));
	  jetsbtag_phcleaned.push_back(jets.ak4pfjets_passMEDbtag.at(idx));
	  dummy_sigma_phcleaned.push_back(dummy_sigma.at(idx));
	  htph += jets.ak4pfjets_pt.at(idx);
	  float dPhiM = getdphi(StopEvt.ph_met_phi, jets.ak4pfjets_phi.at(idx) );
	  if ( dPhiM  < (TMath::Pi()/2) ) htssmph += jets.ak4pfjets_pt.at(idx);
	  else                            htosmph += jets.ak4pfjets_pt.at(idx);
	  if(leadbidx==-1 && jets.ak4pfjets_passMEDbtag.at(idx)) leadbidx = idx;//leading bjet photon cleaned
	}
	StopEvt.ph_HT = htph;
	StopEvt.ph_htssm = htssmph;
	StopEvt.ph_htosm = htosmph;
	StopEvt.ph_htratiom   = StopEvt.ph_htssm / (StopEvt.ph_htosm + StopEvt.ph_htssm);
	mybjets.clear(); myaddjets.clear();
	for(unsigned int idx = 0; idx<jetIndexSortedCSV.size(); ++idx){
	  if(jetIndexSortedCSV[idx]==oljind) continue;
	  if(jets.ak4pfjets_passMEDbtag.at(jetIndexSortedCSV[idx])==true) mybjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
	  else if(mybjets.size()<=1 && (mybjets.size()+myaddjets.size())<3) myaddjets.push_back(jets.ak4pfjets_p4.at(jetIndexSortedCSV[idx]) );
	}
	if(nVetoLeptons>0) {
	  StopEvt.ph_mt_met_lep = calculateMt(lep1.p4, StopEvt.ph_met, StopEvt.ph_met_phi);
	  StopEvt.ph_dphi_Wlep = DPhi_W_lep(StopEvt.ph_met, StopEvt.ph_met_phi, lep1.p4);
	}
        if(nVetoLeptons>1) StopEvt.ph_MT2_l_l = CalcMT2_(StopEvt.pfmet,StopEvt.pfmet_phi,lep1.p4,lep2.p4,false,0);
	if(jetsp4_phcleaned.size()>1){
	  if(nVetoLeptons>0) {
	    StopEvt.ph_MT2W = CalcMT2W_(mybjets,myaddjets,lep1.p4,StopEvt.ph_met, StopEvt.ph_met_phi);
	    StopEvt.ph_topness = CalcTopness_(0,StopEvt.ph_met, StopEvt.ph_met_phi,lep1.p4,mybjets,myaddjets);	
	    StopEvt.ph_topnessMod = CalcTopness_(1,StopEvt.ph_met, StopEvt.ph_met_phi,lep1.p4,mybjets,myaddjets);
	    StopEvt.ph_MT2_lb_b_mass = CalcMT2_lb_b_(StopEvt.ph_met, StopEvt.ph_met_phi,lep1.p4,mybjets,myaddjets,0,true);
	    StopEvt.ph_MT2_lb_b = CalcMT2_lb_b_(StopEvt.ph_met, StopEvt.ph_met_phi,lep1.p4,mybjets,myaddjets,0,false);
	    StopEvt.ph_MT2_lb_bqq_mass = CalcMT2_lb_bqq_(StopEvt.ph_met, StopEvt.ph_met_phi,lep1.p4,mybjets,myaddjets,jetsp4_phcleaned,0,true);
	    StopEvt.ph_MT2_lb_bqq = CalcMT2_lb_bqq_(StopEvt.ph_met, StopEvt.ph_met_phi,lep1.p4,mybjets,myaddjets,jetsp4_phcleaned,0,false);
	  }
	  StopEvt.ph_hadronic_top_chi2 = calculateChi2(jetsp4_phcleaned, dummy_sigma_phcleaned, jetsbtag_phcleaned);
	  StopEvt.ph_mindphi_met_j1_j2 =  getMinDphi(StopEvt.ph_met_phi,jetsp4_phcleaned.at(0),jetsp4_phcleaned.at(1));
	}//at least two jets
	if(jetsp4_phcleaned.size()>0){
	  if(nVetoLeptons>0) {
	    StopEvt.ph_Mlb_lead_bdiscr = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[0])+lep1.p4).M();
	    if(oljind==jetIndexSortedCSV[0]) StopEvt.ph_Mlb_lead_bdiscr = (jets.ak4pfjets_p4.at(jetIndexSortedCSV[1])+lep1.p4).M();//exists as index=0 doesn't count for jetsp4_phcleaned.size()
	    if(leadbidx>=0) StopEvt.ph_dR_lep_leadb = dRbetweenVectors(jets.ak4pfjets_p4.at(leadbidx), lep1.p4);
	    for (unsigned int idx = 0; idx < rankminDR.size(); ++idx){
	      if(rankminDR[idx].second==oljind) continue;
	      if(nVetoLeptons==0) continue;
	      if(!(jets.ak4pfjets_passMEDbtag.at(rankminDR[idx].second)) ) continue;
	      StopEvt.ph_Mlb_closestb = (jets.ak4pfjets_p4.at(rankminDR[idx].second)+lep1.p4).M();
	      break;
	    }
	    LorentzVector threejetsum; threejetsum.SetPxPyPzE(0.,0.,0.,0.);
	    int threejetcounter = 0;
	    for (unsigned int idx = 0; idx < rankmaxDPhi.size(); ++idx){
	      if(rankmaxDPhi[idx].second==oljind) continue;
	      threejetsum = threejetsum + jets.ak4pfjets_p4.at(rankmaxDPhi[idx].second);
	      ++threejetcounter;
	      if(threejetcounter>=3) break;
	    }
	    if(threejetcounter==3) StopEvt.ph_Mjjj = threejetsum.M();
	  }//at least one lepton
	}//at least one jet
      }//end of photon additions
   } 
      //
      // Tau Selection
      //
      //std::cout << "[babymaker::looper]: tau  vars" << std::endl;
      int vetotaus=0;
      double tau_pt  = 20.0;
      double tau_eta = 2.4;  
      
      Taus.tau_IDnames = taus_pf_IDnames();
      
      for(unsigned int iTau = 0; iTau < taus_pf_p4().size(); iTau++){
	
	if( taus_pf_p4().at(iTau).Pt() < tau_pt ) continue;
	if( fabs(taus_pf_p4().at(iTau).Eta()) > tau_eta ) continue;
	
	Taus.FillCommon(iTau, tau_pt, tau_eta);
	if(isVetoTau(iTau, lep1.p4, lep1.charge)){
	  Taus.tau_isVetoTau.push_back(true);
	  vetotaus++;
	}else Taus.tau_isVetoTau.push_back(false);
      }

      if(vetotaus<1) StopEvt.PassTauVeto = true;
      else StopEvt.PassTauVeto = false;
      Taus.ngoodtaus = vetotaus;

      //
      // IsoTracks (Charged pfLeptons and pfChargedHadrons)
      //
      //std::cout << "[babymaker::laooper]: filling isotrack vars" << std::endl;
      int vetotracks = 0;
      int vetotracks_v2 = 0;
      int vetotracks_v3 = 0;
      for (unsigned int ipf = 0; ipf < pfcands_p4().size(); ipf++) {
	
	//some selections
	if(pfcands_charge().at(ipf) == 0) continue;
	if(pfcands_p4().at(ipf).pt() < 5) continue;
	if(fabs(pfcands_p4().at(ipf).eta()) > 2.4 ) continue;
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

     /*obsolete
      if(vetotracks<1) StopEvt.PassTrackVeto = true;
      else StopEvt.PassTrackVeto = false;
    
      if(vetotracks_v2<1) StopEvt.PassTrackVeto_v2 = true;
      else StopEvt.PassTrackVeto_v2 = false;
    */
      if(vetotracks_v3<1) StopEvt.PassTrackVeto = true;
      else StopEvt.PassTrackVeto = false;
    
      if(skim_2ndlepveto){
            if(StopEvt.nvetoleps!=1) continue;
            if(!StopEvt.PassTrackVeto) continue;
            if(!StopEvt.PassTauVeto) continue;
      }
      nEvents_pass_skim_2ndlepVeto++;

      //std::cout << "[babymaker::looper]: updating geninfo for recoleptons" << std::endl;
      // Check that we have the gen leptons matched to reco leptons
      int lep1_match_idx = -99;
      int lep2_match_idx = -99;

      double min_dr_lep1 = 999.9;
      int min_dr_lep1_idx = -99;

      double min_dr_lep2 = 999.9;
      int min_dr_lep2_idx = -99;
      
      if (!evt_isRealData()){

	if(nVetoLeptons>0){
	  for(int iGen=0; iGen<(int)gen_leps.p4.size(); iGen++){
	    if( abs(gen_leps.id.at(iGen))==abs(lep1.pdgid) ){
	      double temp_dr = ROOT::Math::VectorUtil::DeltaR(gen_leps.p4.at(iGen), lep1.p4);
	      if(temp_dr<matched_dr){
		lep1_match_idx=gen_leps.genpsidx.at(iGen);
		break;
	      }
	      else if(temp_dr<min_dr_lep1){
		min_dr_lep1=temp_dr;
		min_dr_lep1_idx=gen_leps.genpsidx.at(iGen);
	      }
	    } // end if lep1 id matches genLep id
	  } // end loop over gen leps
	}
	if(nVetoLeptons>1){
	  for(int iGen=0; iGen<(int)gen_leps.p4.size(); iGen++){
	    if( lep1_match_idx == iGen ) continue;
	    if( abs(gen_leps.id.at(iGen))==abs(lep2.pdgid) ){
	      double temp_dr = ROOT::Math::VectorUtil::DeltaR(gen_leps.p4.at(iGen), lep2.p4);
	      if(temp_dr<matched_dr){
		lep2_match_idx=gen_leps.genpsidx.at(iGen);
		break;
	      }
	      else if(temp_dr<min_dr_lep2){
		min_dr_lep2=temp_dr;
		min_dr_lep2_idx=gen_leps.genpsidx.at(iGen);
	      }
	    }
	  }
	}
	
	// If lep1 isn't matched to a lepton already stored, then try to find another match
	if( (nVetoLeptons>0 && lep1_match_idx<0) ){
	  for(unsigned int genx = 0; genx < genps_p4().size(); genx++){
	    if(!genps_isLastCopy().at(genx) ) continue;
	    if( abs(genps_id().at(genx))==abs(lep1.pdgid) ){
	      double temp_dr = ROOT::Math::VectorUtil::DeltaR(genps_p4().at(genx), lep1.p4);
	      if(temp_dr<matched_dr){
		lep1_match_idx=genx;
		gen_leps.FillCommon(genx);
		break;
	      }
	      else if(temp_dr<min_dr_lep1){
		min_dr_lep1=temp_dr;
		min_dr_lep1_idx=genx;
	      }
	    }
	  }
	  // if lep1 is still unmatched, fill with closest match, if possible
	  if( lep1_match_idx<0 && min_dr_lep1_idx>0 ) gen_leps.FillCommon(min_dr_lep1_idx);
	}
	
	// If lep2 isn't matched to a lepton already stored, then try to find another match
	if( (nVetoLeptons>1 && lep2_match_idx<0) ){
	  for(unsigned int genx = 0; genx < genps_p4().size() ; genx++){
	    if(!genps_isLastCopy().at(genx) ) continue;
	    if( abs(genps_id().at(genx))==abs(lep2.pdgid) ){
	      double temp_dr = ROOT::Math::VectorUtil::DeltaR(genps_p4().at(genx), lep2.p4);
	      if(temp_dr<matched_dr){
		lep2_match_idx=genx;
		gen_leps.FillCommon(genx);
		break;
	      }
	      else if(temp_dr<min_dr_lep2){
		min_dr_lep2=temp_dr;
		min_dr_lep2_idx=genx;
	      }
	    }
	  }
	  // if lep2 is still unmatched, fill with closest match, if possible
	  if( lep2_match_idx<0 && min_dr_lep2_idx>0 ) gen_leps.FillCommon(min_dr_lep2_idx);
	}

      } // end if not data      

      

      //
      // Trigger Information
      //
      //std::cout << "[babymaker::looper]: filling HLT vars" << std::endl;
      //////////////// 2015 Run II  //////////////////////
      StopEvt.HLT_MET = passHLTTriggerPattern("HLT_PFMET170_NoiseCleaned_v") || passHLTTriggerPattern("HLT_PFMET170_JetIdCleaned_v") || passHLTTriggerPattern("HLT_PFMET170_HBHECleaned_v") || passHLTTriggerPattern("HLT_PFMET170_NotCleaned_v"); 
      StopEvt.HLT_MET100_MHT100 = passHLTTriggerPattern("HLT_PFMET100_PFMHT100_IDTight_v");
      StopEvt.HLT_SingleEl = passHLTTriggerPattern("HLT_Ele25_eta2p1_WPTight_Gsf_v") || passHLTTriggerPattern("HLT_Ele27_WP85_Gsf_v") ||passHLTTriggerPattern("HLT_Ele27_eta2p1_WPLoose_Gsf_v") || passHLTTriggerPattern("HLT_Ele27_eta2p1_WPTight_Gsf_v");
      StopEvt.HLT_SingleMu = passHLTTriggerPattern("HLT_IsoMu20_v") || passHLTTriggerPattern("HLT_IsoTkMu20_v") || passHLTTriggerPattern("HLT_IsoMu22_v") || passHLTTriggerPattern("HLT_IsoTkMu22_v") || passHLTTriggerPattern("HLT_IsoMu24_v") || passHLTTriggerPattern("HLT_IsoTkMu24_v");
      StopEvt.HLT_DiEl =  passHLTTriggerPattern("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
      StopEvt.HLT_DiMu =  passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") || passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
      StopEvt.HLT_MuE = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") || passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v"); 
     //photons more complicated because of prescales
      StopEvt.HLT_Photon90_CaloIdL_PFHT500 = passHLTTriggerPattern("HLT_Photon90_CaloIdL_PFHT500_v");
      StopEvt.HLT_Photon22_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon22_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon30_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon30_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon36_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon36_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon50_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon50_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon75_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon75_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon90_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon90_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon120_R9Id90_HE10_IsoM = HLT_prescale(triggerName("HLT_Photon120_R9Id90_HE10_IsoM_v"));
      StopEvt.HLT_Photon165_R9Id90_HE10_IsoM = HLT_prescale(triggerName("HLT_Photon165_R9Id90_HE10_IsoM_v"));
      StopEvt.HLT_Photon175 = passHLTTriggerPattern("HLT_Photon175_v");
      StopEvt.HLT_Photon165_HE10 = passHLTTriggerPattern("HLT_Photon165_HE10_v");

     ///////////////////////////////////////////////////////////

      /*obsolete
      //StopEvt.HLT_SingleMu = passHLTTriggerPattern("HLT_IsoMu20_eta2p1_IterTrk02_v") || passHLTTriggerPattern("HLT_IsoTkMu20_eta2p1_IterTrk02_v");   
      //StopEvt.HLT_SingleEl = passHLTTriggerPattern("HLT_Ele27_WP85_Gsf_v");   
      //StopEvt.HLT_MET170 = passHLTTriggerPattern("HLT_PFMET170_NoiseCleaned_v");
      StopEvt.HLT_MET170 = passHLTTriggerPattern("HLT_PFMET170_NoiseCleaned_v") || passHLTTriggerPattern("HLT_PFMET170_JetIdCleaned_v") || passHLTTriggerPattern("HLT_PFMET170_v");//just to be safe
      StopEvt.HLT_HT350MET120  = passHLTTriggerPattern("HLT_PFHT350_PFMET120_NoiseCleaned_v");
      StopEvt.HLT_HT350MET100 = passHLTTriggerPattern("HLT_PFHT350_PFMET100_NoiseCleaned_v");
      StopEvt.HLT_MET120Btag = passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_BTagCSV07_v") || passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_BTagCSV072_v");
      StopEvt.HLT_MET120Mu5 = passHLTTriggerPattern("HLT_PFMET120_NoiseCleaned_Mu5_v");
      StopEvt.HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight = passHLTTriggerPattern("HLT_MonoCentralPFJet80_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight") || passHLTTriggerPattern("HLT_MonoCentralPFJet80_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight");
      StopEvt.HLT_MET90_MHT90_IDTight = passHLTTriggerPattern("HLT_PFMET90_PFMHT90_IDTight") || passHLTTriggerPattern("HLT_PFMET90_PFMHT90_IDLoose");
      StopEvt.HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight = passHLTTriggerPattern("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight") || passHLTTriggerPattern("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight");     

      StopEvt.HLT_DiEl =  passHLTTriggerPattern("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
      StopEvt.HLT_DiEl_17_12 = passHLTTriggerPattern("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
      StopEvt.HLT_DiMu =  passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") || passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
      StopEvt.HLT_Mu8El17 = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v");
      StopEvt.HLT_Mu8El23 = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
      StopEvt.HLT_Mu17El12 = passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
      StopEvt.HLT_Mu23El12 = passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");

      //notation in RunIISpring15MC is WP85/WP75, for data will have WPLoose and WPTight
      StopEvt.HLT_SingleEl23 = passHLTTriggerPattern("HLT_Ele23_WPLoose_Gsf_v");
      StopEvt.HLT_SingleEl27 = passHLTTriggerPattern("HLT_Ele27_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("HLT_Ele27_WP85_Gsf_v")||passHLTTriggerPattern("Ele27_eta2p1_WPLoose_Gsf_v");//precsaled for 14e33
      StopEvt.HLT_SingleEl27Tight = passHLTTriggerPattern("HLT_Ele27_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("Ele27_eta2p1_WPTight_Gsf_v");//precsaled for 14e33
      StopEvt.HLT_SingleElTight = passHLTTriggerPattern("HLT_Ele32_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("Ele32_eta2p1_WPTight_Gsf_v");
      StopEvt.HLT_SingleEl = passHLTTriggerPattern("HLT_Ele32_eta2p1_WP75_Gsf_v")||passHLTTriggerPattern("Ele32_eta2p1_WPLoose_Gsf_v");

      StopEvt.HLT_SingleElHT200 = passHLTTriggerPattern("HLT_Ele27_eta2p1_WP85_Gsf_HT200_v")||passHLTTriggerPattern("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v");

      StopEvt.HLT_SingleMu17 = passHLTTriggerPattern("HLT_IsoMu17_eta2p1_v");
      StopEvt.HLT_SingleMu18 = passHLTTriggerPattern("HLT_IsoMu18_v") || passHLTTriggerPattern("HLT_IsoTkMu18_v");
      StopEvt.HLT_SingleMu20 = passHLTTriggerPattern("HLT_IsoMu20_eta2p1_v") || passHLTTriggerPattern("HLT_IsoMu20_v") || passHLTTriggerPattern("HLT_IsoTkMu20_eta2p1_v") || passHLTTriggerPattern("HLT_IsoTkMu20_v");
      StopEvt.HLT_SingleMu24 = passHLTTriggerPattern("HLT_IsoMu24_eta2p1_v") || passHLTTriggerPattern("HLT_IsoTkMu24_eta2p1_v");
      StopEvt.HLT_SingleMuNoEta = passHLTTriggerPattern("HLT_IsoMu27_v") || passHLTTriggerPattern("HLT_IsoTkMu27_v");
      StopEvt.HLT_SingleMuNoIso = passHLTTriggerPattern("HLT_Mu45_eta2p1_v");
      StopEvt.HLT_SingleMuNoIsoNoEta = passHLTTriggerPattern("HLT_Mu50_v");
      StopEvt.HLT_Mu6HT200MET125 = passHLTTriggerPattern("HLT_Mu6_PFHT200_PFMET125_NoiseCleaned_v");
      StopEvt.HLT_SingleMu = passHLTTriggerPattern("HLT_IsoMu24_eta2p1_v") || passHLTTriggerPattern("HLT_IsoTkMu24_eta2p1_v");

      StopEvt.HLT_Photon90_CaloIdL_PFHT500 = passHLTTriggerPattern("HLT_Photon90_CaloIdL_PFHT500_v");
      StopEvt.HLT_Photon22_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon22_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon30_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon30_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon36_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon36_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon50_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon50_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon75_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon75_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon90_R9Id90_HE10_IsoM  = HLT_prescale(triggerName("HLT_Photon90_R9Id90_HE10_IsoM_v" ));
      StopEvt.HLT_Photon120_R9Id90_HE10_IsoM = HLT_prescale(triggerName("HLT_Photon120_R9Id90_HE10_IsoM_v"));
      StopEvt.HLT_Photon165_R9Id90_HE10_IsoM = HLT_prescale(triggerName("HLT_Photon165_R9Id90_HE10_IsoM_v"));
      StopEvt.HLT_Photon175 = passHLTTriggerPattern("HLT_Photon175_v");
      StopEvt.HLT_Photon165_HE10 = passHLTTriggerPattern("HLT_Photon165_HE10_v");
  */
      //
      // Fill Tree
      //
      BabyTree->Fill();
    
    }//close event loop
    //
    // Close input file
    //
    file.Close();
    //delete file;

  }//close file loop

  //
  // Write and Close baby file
  //
  BabyFile->cd();
   // save counter histogram
  BabyTree->Write();
  counterhist->Write();
  if(isSignalFromFileName){
    counterhistSig->Write();
    histNEvts->Write();
  }
  BabyFile->Close();
  //delete BabyFile;
  //histFile->cd();
  
  //
  // Some clean up
  //
  if(isSignalFromFileName) {
    fxsec->Close();
    delete fxsec;
  }
  if(!isDataFromFileName){
    pileupfile->Close();
    delete pileupfile;
  }
  if (skim_applyBtagSFs) {
    jets.deleteBtagSFTool();
  }

  if( !isDataFromFileName && (skim_applyLeptonSFs || skim_applyVetoLeptonSFs) ){
    f_el_SF->Close();
    f_mu_SF_id->Close();
    f_mu_SF_iso->Close();
    f_mu_SF_veto_id->Close();
    f_mu_SF_veto_iso->Close();
    f_el_FS_ID->Close();
    f_el_FS_Iso->Close();
    f_mu_FS_ID->Close();
    f_mu_FS_Iso->Close();
    f_vetoLep_eff->Close();
  }

  
  //
  // Benchmarking
  //
  bmark->Stop("benchmark");
  

  //
  // Print Skim Cutflow
  //
  cout << endl;
  cout << "Wrote babies into file " << BabyFile->GetName() << endl;
//  cout << "Wrote hists into file " << histFile->GetName() << endl;
  cout << "-----------------------------" << endl;
  cout << "Events Processed                     " << nEvents_processed << endl;
  cout << "Events with " << skim_nvtx << " Good Vertex            " << nEvents_pass_skim_nVtx << endl;
  cout << "Events with MET > " << skim_met << " GeV             " << nEvents_pass_skim_met << endl;
  cout << "Events with at least " << skim_nGoodLep << " Good Lepton   " << nEvents_pass_skim_nGoodLep << endl;
  cout << "Events with at least " << skim_nJets << " Good Jets     " << nEvents_pass_skim_nJets << endl;
  cout << "Events with at least " << skim_nBJets << " Good BJets   " << nEvents_pass_skim_nBJets << endl;
  cout << "Events passing 2nd Lep Veto " << skim_2ndlepveto << "    " << nEvents_pass_skim_2ndlepVeto << endl;
  cout << "-----------------------------" << endl;
  cout << "CPU  Time:   " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;                                                                                          
  cout << "Real Time:   " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  return 0;  

}
