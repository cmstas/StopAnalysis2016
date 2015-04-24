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
#include "stop_variables/mt2w.cc"
#include "stop_variables/mt2w_bisect.cpp"
#include "stop_variables/chi2.cc"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;
using namespace tas;
//Switches
//char* path = "../babies_16April2015/";

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

void babyMaker::setSkimVariables(int nvtx, float met, int nlep, float leppt, float lepeta, int njets, int jetpt, int jeteta){
        skim_nvtx = nvtx;
        skim_met = met;

        skim_nlep = nlep;
        skim_leppt = leppt;
        skim_lepeta = lepeta;
   
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
    unsigned int track_overlep1_idx = -9999;
    unsigned int track_overlep2_idx = -9999;


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

      //std::cout << "[babymaker::looper]: filling event vars" << std::endl;
      //Fill Event Variables
      StopEvt.FillCommon(file->GetName()); 
     // std::cout << "[babymaker::looper]: filling event vars completed" << std::endl; 
   //   dumpDocLines();

      if(StopEvt.nvtxs<skim_nvtx) continue;
      nEvents_GoodVtx++;
      if(evt_pfmet()<skim_met) continue;
      nEvents_MET30++;

     //Lepton Variables
      //We only look at the two highest pt ones
      int nGoodLeptons = 0;
      int idx1 = -9999;
      int idx2 = -9999;
      int pdgid1 = -9999;
      int pdgid2 = -9999;

//std::cout << "[babymaker::looper]: selecting leptons" << std::endl;
      vector<Lepton> GoodLeps;
      for (unsigned int eidx = 0; eidx < els_p4().size(); eidx++){
        if(!PassElectronPreSelections(eidx, skim_leppt)) continue;
        Lepton goodlepton;
        goodlepton.id  = -11*els_charge().at(eidx);
        goodlepton.idx = eidx;
        goodlepton.p4  = els_p4().at(eidx);  
        GoodLeps.push_back(goodlepton);
      }

      for (unsigned int midx = 0; midx < mus_p4().size(); midx++){
        if(!PassMuonPreSelections(midx, skim_leppt)) continue;
        Lepton goodlepton;
        goodlepton.id  = -13*mus_charge().at(midx);
        goodlepton.idx = midx;
        goodlepton.p4  = mus_p4().at(midx);
        GoodLeps.push_back(goodlepton);
      }
   
      sort(GoodLeps.begin(),GoodLeps.end(),sortLepbypt());       

      nGoodLeptons = GoodLeps.size();
      if(nGoodLeptons<skim_nlep) continue;
      nEvents_GoodLep++; 

      StopEvt.ngoodlep = nGoodLeptons; 

//std::cout << "[babymaker::looper]: filling lepton variables" << std::endl;
      lep1.FillCommon(GoodLeps.at(0).id, GoodLeps.at(0).idx);      
      if( nGoodLeptons > 1 ) lep2.FillCommon(GoodLeps.at(1).id, GoodLeps.at(1).idx);

     //get the jets overlapping with the selected leptons
      jet_overlep1_idx = getOverlappingJetIndex(lep1.p4, pfjets_p4() , 0.4);
      if(nGoodLeptons>1) jet_overlep2_idx = getOverlappingJetIndex(lep2.p4, pfjets_p4() , 0.4); 
      
      //std::cout << "[babymaker::looper]: filling jets vars" << std::endl;         
     //jets and b-tag variables feeding the index for the jet overlapping the selected leptons
//std::cout << "[babymaker::looper]: filling jet vars" << std::endl;
      jets.FillCommon(jet_overlep1_idx, jet_overlep2_idx);
      if(jets.ak4GoodPFJets < 2) continue;
      nEvents_2GoodJets++;
     // now calculate jets + lep variables
     //DR(lep, leadB) with medium discriminator
     StopEvt.dR_lep1_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep1.p4);
     if(nGoodLeptons>1) StopEvt.dR_lep2_leadb = dRbetweenVectors(jets.ak4pfjets_leadMEDbjet_p4, lep2.p4);
     //MT2W
     StopEvt.MT2W_lep1 = calculateMT2w(jets.ak4pfjets_p4, jets.ak4pfjets_passMEDbtag, lep1.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
     if(nGoodLeptons>1) StopEvt.MT2W_lep2 = calculateMT2w(jets.ak4pfjets_p4, jets.ak4pfjets_passMEDbtag, lep2.p4,StopEvt.pfmet, StopEvt.pfmet_phi);
    //chi2
    vector<float> dummy_sigma;
    for (size_t idx = 0; idx < jets.ak4pfjets_p4.size(); ++idx){
      dummy_sigma.push_back(0.1);
    } 
    StopEvt.chi2 = calculateChi2(jets.ak4pfjets_p4, dummy_sigma, jets.ak4pfjets_passMEDbtag);
    //Jets & MET
    StopEvt.mindphi_met_j1_j2 =  getMinDphi(StopEvt.pfmet_phi,jets.ak4pfjets_p4.at(0),jets.ak4pfjets_p4.at(1));
    //MET & Leptons
    StopEvt.MT_MET_lep1 = calculateMt(lep1.p4, StopEvt.pfmet, StopEvt.pfmet_phi);
    if(nGoodLeptons>1) StopEvt.MT_MET_lep2 = calculateMt(lep2.p4, StopEvt.pfmet, StopEvt.pfmet_phi);

    //taus
    int vetotaus=0;

    Taus.tau_IDnames = taus_pf_IDnames();

 //   for(unsigned int iTau = 0; iTau < taus_pf_IDnames().size(); iTau++){
   //       cout<<taus_pf_IDnames().at(iTau)<<endl;
   // }

    for(unsigned int iTau = 0; iTau < taus_pf_p4().size(); iTau++){
      Taus.FillCommon(iTau, 20, 2.4);
      if(isVetoTau(iTau, lep1.p4, lep1.charge)){
         Taus.tau_isVetoTau.push_back(true);
         vetotaus++;
      }else Taus.tau_isVetoTau.push_back(false);
    }
    if(vetotaus<1) StopEvt.PassTauVeto = true;
    else StopEvt.PassTauVeto = false;

    int vetotracks = 0;
    for (unsigned int ipf = 0; ipf < pfcands_p4().size(); ipf++) {
    // some selections
      if(pfcands_charge().at(ipf) == 0) continue;
      if(pfcands_p4().at(ipf).pt() < 5) continue;
      if(fabs(pfcands_dz().at(ipf)) > 0.1) continue;

      //remove everything that is within 0.1 of selected lead and subleading leptons
      if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lep1.p4)<0.1) continue;
      if(nGoodLeptons>1){
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

   //ttbar counters:
   int ntausfromt=0;
   int nelsfromt=0;
   int nmusfromt=0;
   int n_nutaufromt=0;
   int n_nuelfromt=0;
   int n_numufromt=0;

   int econv = 0;
    //std::cout << "[babymaker::looper]: filling gen particles vars" << std::endl;
    //gen particles
    for(unsigned int genx = 0; genx < genps_p4().size() ; genx++){
      //void GenParticleTree::FillCommon (int idx, int pdgid_=0, int pdgmotherid_=0, int status_=0)
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_els.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1) gen_leptau_els.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t) nelsfromt++;
//if(abs(genps_id().at(genx)) == pdg_el && abs(genps_id_mother().at(genx)) == pdg_el && genps_charge().at(genx) == (-1)*genps_charge().at(genps_idx_mother().at(genx))) econv++;
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t) n_nuelfromt++;      

      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_mus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_tau && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1) gen_leptau_mus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_mu && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) nmusfromt++;
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_numufromt++;
      //if(abs(genps_id().at(genx)) == pdg_tau) cout<<"found a tau and status ="<<genps_status().at(genx)<<endl;
      //if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_tau) cout<<"found a tau with mother W and status = "<<genps_status().at(genx) <<endl;
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) ntausfromt++;
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t ) n_nutaufromt++;
      if(abs(genps_id().at(genx)) == pdg_tau && genps_status().at(genx) == 2) gen_taus.FillCommon(genx); 

      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nue && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_numu && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_nutau && genps_status().at(genx) == 1) gen_nus.FillCommon(genx);

      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_d && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_u && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_s && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
      if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_c && genps_status().at(genx) == 23) gen_qs.FillCommon(genx);
       
      if(abs(genps_id_mother().at(genx)) == pdg_t && abs(genps_id().at(genx)) == pdg_b && genps_status().at(genx) == 23) gen_bs.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_t && genps_status().at(genx) == 62) gen_tops.FillCommon(genx);
    
      if(abs(genps_id().at(genx)) == pdg_chi_1neutral && genps_status().at(genx) == 1) gen_lsp.FillCommon(genx);
     
      if(abs(genps_id().at(genx)) == pdg_stop1 && genps_status().at(genx) == 62) gen_stop.FillCommon(genx);
      if(abs(genps_id().at(genx)) == pdg_stop2 && genps_status().at(genx) == 62) gen_stop.FillCommon(genx);

    }

    gen_els.gen_nfromt = n_nuelfromt;
    gen_mus.gen_nfromt = n_numufromt;
    gen_taus.gen_nfromt = n_nutaufromt;

/*    if(nelsfromt + nmusfromt + ntausfromt == 3){
      cout<<"***************************BEGIN******************************"<<endl;
      cout<<"gen els = "<<n_nuelfromt<<" gen mus = "<<n_numufromt<<" gen taus = "<<n_nutaufromt<<endl;
       dumpDocLines(); 
    

    for(unsigned int genx = 0; genx < genps_p4().size() ; genx++){
         if(abs(genps_id_mother().at(genx)) == pdg_W && abs(genps_id().at(genx)) == pdg_el && genps_status().at(genx) == 1 && abs(genps_id_mother().at(genps_idx_mother().at(genx))) == pdg_t) cout<<"genps_id().at(genx) = "<<genps_id().at(genx)<<" genps_id_mother().at(genx) = "<<genps_id_mother().at(genx)<<" abs(genps_id_mother().at(genps_idx_mother().at(genx))) = "<<abs(genps_id_mother().at(genps_idx_mother().at(genx))) <<" abs(genps_id_mother().at(genps_idx_mother().at(genps_idx_mother().at(genx)))) = "<< abs(genps_id_mother().at(genps_idx_mother().at(genps_idx_mother().at(genx)))) <<endl;
   }
}*/
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
