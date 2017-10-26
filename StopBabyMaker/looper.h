#include "EventTree.h"
#include "GenParticleTree.h"
#include "LeptonTree.h"
#include "PhotonTree.h"
#include "JetTree.h"
#include "TauTree.h"
#include "IsoTracksTree.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH3D.h"
#include "Math/VectorUtil.h"
#include "TChain.h"
#include "Math/LorentzVector.h"

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

#ifndef LOOPER_H
#define LOOPER_H

#pragma GCC diagnostic ignored "-Wwrite-strings"

using namespace std;

class babyMaker {

 public:
  // Constructor/destructor
  babyMaker ();
  babyMaker (const std::string &prefix);
  virtual ~babyMaker (){ delete BabyFile; }

  void MakeBabyNtuple(const char* output_name);
  void InitBabyNtuple();
  int looper(TChain* chain, char* output_name, int nEvents = -1, char* path = "./");
  char* babypath;

  // Variables for baby skim
  int skim_nvtx;
  float skim_met;

  int   skim_nGoodLep;
  float skim_goodLep_el_pt;
  float skim_goodLep_el_eta;
  float skim_goodLep_mu_pt;
  float skim_goodLep_mu_eta;

  float skim_looseLep_el_pt;
  float skim_looseLep_el_eta;
  float skim_looseLep_mu_pt;
  float skim_looseLep_mu_eta;

  float skim_vetoLep_el_pt;
  float skim_vetoLep_el_eta;
  float skim_vetoLep_mu_pt;
  float skim_vetoLep_mu_eta;

  int   skim_nJets;
  float skim_jet_pt;
  float skim_jet_eta;
  int   skim_nBJets;

  float skim_jet_ak8_pt;
  float skim_jet_ak8_eta;

  int   skim_nPhotons;
  float skim_ph_pt;
  float skim_ph_eta;

  bool applyJECfromFile;
  int  JES_type;

  bool applyBtagSFs;
  bool applyLeptonSFs;
  bool applyVetoLeptonSFs;
  bool apply2ndLepVeto;

  bool filltaus;
  bool filltracks;
  bool fillZll;
  bool fillPhoton;
  bool fillMETfilt;
  bool fill2ndlep;
  bool fillExtraEvtVar;

  bool fillAK8;
  bool fillTopTag;
  bool fillAK4EF;
  bool fillAK4_Other;
  bool fillOverleps;
  bool fillAK4Synch;
  bool fillElID;
  bool fillIso;
  bool fillLepSynch;

  bool isFastsim;

 protected:
  TFile* BabyFile;
  TFile* histFile;
  TTree* BabyTree;
  TH1D*  histcounter;
 private:

  // Tree Branches
  EventTree StopEvt;
  LeptonTree lep1;
  LeptonTree lep2;
  PhotonTree ph;
  JetTree jets;
  JetTree jets_jup;
  JetTree jets_jdown;
  TauTree Taus;
  IsoTracksTree Tracks;
  //GenParticleTree gen_els;
  //GenParticleTree gen_mus;
  //GenParticleTree gen_taus;
  GenParticleTree gen_leps;
  GenParticleTree gen_nus;
  //GenParticleTree gen_nuels;
  //GenParticleTree gen_numus;
  //GenParticleTree gen_nutaus;
  GenParticleTree gen_tops;
  //GenParticleTree gen_bs;
  //GenParticleTree gen_cs;
  GenParticleTree gen_qs;
  //GenParticleTree gen_glus;
  GenParticleTree gen_bosons;
  //GenParticleTree gen_ws;
  //GenParticleTree gen_zs;
  //GenParticleTree gen_phs;
  //GenParticleTree gen_hs;
  GenParticleTree gen_susy;

  // for btag SFs
  BTagCalibration* calib;
  BTagCalibrationReader* reader_heavy;
  BTagCalibrationReader* reader_heavy_UP;
  BTagCalibrationReader* reader_heavy_DN;
  BTagCalibrationReader* reader_light;
  BTagCalibrationReader* reader_light_UP;
  BTagCalibrationReader* reader_light_DN;

  TH2D* h_btag_eff_b;
  TH2D* h_btag_eff_c;
  TH2D* h_btag_eff_udsg;

  BTagCalibration* calib_fastsim;
  BTagCalibrationReader* reader_fastsim;
  BTagCalibrationReader* reader_fastsim_UP;
  BTagCalibrationReader* reader_fastsim_DN;

  TH2D* h_btag_eff_b_fastsim;
  TH2D* h_btag_eff_c_fastsim;
  TH2D* h_btag_eff_udsg_fastsim;

};

struct val_err_t { float value; float error; };

#endif
