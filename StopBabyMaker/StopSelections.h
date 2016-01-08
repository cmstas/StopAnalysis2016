#ifndef STOPSELECTIONS_H
#define STOPSELECTIONS_H
#include "TString.h"
#include <vector>
#include "Math/LorentzVector.h"
#include <functional>
#include <list>
#include <algorithm>
#include <utility>
#include <assert.h>

#include "JetCorrector.h"
#include "JetSelections.h"
#include "jetcorr/FactorizedJetCorrector.h"
#include "jetcorr/JetCorrectionUncertainty.h"
#include "btagsf/BTagCalibrationStandalone.h"

/*
#ifndef JETCORR_INCL
#define JETCORR_INCL
#include "../CORE/Tools/jetcorr/Utilities.icc"
#include "../CORE/Tools/jetcorr/JetCorrectionUncertainty.icc"
#include "../CORE/Tools/jetcorr/SimpleJetCorrectionUncertainty.icc"
#endif
*/

using namespace std;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

   const int pdg_p = 2212;
   const int pdg_el = 11;
   const int pdg_nue = 12;
   const int pdg_mu = 13;
   const int pdg_numu = 14;
   const int pdg_tau = 15;
   const int pdg_nutau = 16;
   const int pdg_b = 5;
   const int pdg_t = 6;
   const int pdg_d = 1;
   const int pdg_u = 2;
   const int pdg_s = 3;
   const int pdg_c = 4;
   const int pdg_stop1 = 1000006;
   const int pdg_stop2 = 2000006;
   const int pdg_chi_1neutral = 1000022;
   const int pdg_chi_2neutral = 1000023;
   const int pdg_chi_1plus1 = 1000024;
   const int pdg_chi_3neutral = 1000025;
   const int pdg_chi_4neutral = 1000035;
   const int pdg_chi_2plus1 = 1000037;
   const int pdg_W = 24;
   const int pdg_Z = 23;
   const int pdg_h = 25;
   const int pdg_g = 21;
   const int pdg_ph = 22;

//vertices & pileup
int numberOfGoodVertices();

//gen functions
int leptonGenpCount(int& nele, int& nmuon, int& ntau);
int leptonGenpCount_lepTauDecays(int& nele, int& nmuon, int& ntau);
bool PassMuonPreSelections(unsigned int muIdx, float pt, float eta);
bool PassElectronPreSelections(unsigned int elIdx, float pt, float eta);
bool PassMuonVetoSelections(unsigned int muIdx, float pt, float eta);
bool PassElectronVetoSelections(unsigned int elIdx, float pt, float eta);
bool PassJetPreSelections(unsigned int jetIdx, float pt, float eta, bool passjid,FactorizedJetCorrector* corrector,bool applynewcorr,JetCorrectionUncertainty* jetcorr_uncertainty, int JES_type, bool isFastsim);
vector<pair <int, LorentzVector> > sort_pt( vector<LorentzVector> p4_, float pt_);
vector< LorentzVector> getsortedp4(vector<pair <int, LorentzVector> > index_);
float getMinDphi(float metPhi, LorentzVector& vec1, LorentzVector& vec2 );
float getdphi( float phi1 , float phi2 );
float dRbetweenVectors(LorentzVector& vec1, LorentzVector& vec2 );
float  calculateMt(const LorentzVector p4, double met, double met_phi);
int getOverlappingJetIndex(LorentzVector& lep_, vector<LorentzVector> jets_, double dR, float pt, float eta, bool passjid,FactorizedJetCorrector* corrector,bool applynewcorr,JetCorrectionUncertainty* jetcorr_uncertainty, int JES_type, bool isFastsim);
int getOverlappingTrackIndex(LorentzVector& lep_, int pdgid_, vector<LorentzVector> tracks_, double dR);
bool isVetoTrack(int ipf, LorentzVector lepp4_, int charge);
bool isVetoTrack_v2(int ipf, LorentzVector lepp4_, int charge);
bool isVetoTrack_v3(int ipf, LorentzVector lepp4_, int charge);
bool isVetoTau(int ipf, LorentzVector lepp4_, int charge);
float DPhi_W_lep(float MET, float MET_Phi, LorentzVector p4);
//int leptonIsFromW(int idx, int id, bool alsoSusy);
//bool idIsCharm(int id);
//bool idIsBeauty(int id);
//TString triggerName(TString);
//bool passHLTTriggerPattern(const char*);
//float TrackIso(int);
//bool isFromW(Lep lep);
//bool isFromZ(Lep lep);

void passesBaselineCuts(int njets, int nbtag, float met, float ht, int ngoodlep, int ngoodvertex);

//void passesBaselineCuts(int njets, int nbtag, float met, float ht, unsigned int& analysisBitMask);

//  float met;
//  float metphi;
//  float metx;
//  float mety;
//  float sumet;

#endif
