#include "StopSelections.h"
#include "Math/LorentzVector.h"
#include "Math/VectorUtil.h"
#include "CMS3.h"
#include "ElectronSelections.h"
#include "MuonSelections.h"
#include "VertexSelections.h"
#include "IsoTrackVeto.h"
#include "IsolationTools.h"
#include "TVector3.h"

using namespace tas;

int numberOfGoodVertices() {
  int ngv = 0;
  for (unsigned int vidx = 0; vidx < vtxs_position().size(); vidx++) {
    if (isGoodVertex(vidx)) ++ngv;
  }
  return ngv;
}

bool PassElectronVetoSelections(unsigned int elIdx,float pt, float eta){
  if(els_p4().at(elIdx).pt() < pt) return false;
  if(fabs(els_p4().at(elIdx).eta()) > eta) return false;
  if(!electronID(elIdx, STOP_veto_v3)) return false;  //pass veto, mini-isolation applied at 0.2
  return true;
}

bool PassMuonVetoSelections(unsigned int muIdx,float pt, float eta){
  if(mus_p4().at(muIdx).pt() < pt) return false;
  if(fabs(mus_p4().at(muIdx).eta()) > eta) return false;
  if(!muonID(muIdx, STOP_loose_v3)) return false;  //pass loose, mini-isolation applied at 0.2
  return true;
}

bool PassElectronPreSelections(unsigned int elIdx,float pt, float eta){
  if(els_p4().at(elIdx).pt() < pt) return false;
  if(fabs(els_p4().at(elIdx).eta()) > eta) return false;
  if(!electronID(elIdx, STOP_medium_v3)) return false;  //mini-isolation applied at 0.1
  return true;
}

bool PassMuonPreSelections(unsigned int muIdx,float pt, float eta){
  if(mus_p4().at(muIdx).pt() < pt) return false;
  if(fabs(mus_p4().at(muIdx).eta()) > eta) return false;
  if(!muonID(muIdx, STOP_tight_v2)) return false;  //mini-isolation applied at 0.1
  return true;
}

bool PassJetPreSelections(unsigned int jetIdx,float pt, float eta, bool passjid,FactorizedJetCorrector* corrector,bool applynewcorr,JetCorrectionUncertainty* jetcorr_uncertainty, int JES_type, bool isFastsim){
//apply JEC
        LorentzVector pfjet_p4_cor = cms3.pfjets_p4().at(jetIdx);
          // get uncorrected jet p4 to use as input for corrections
        LorentzVector pfjet_p4_uncor = pfjets_p4().at(jetIdx) * cms3.pfjets_undoJEC().at(jetIdx);

          // get L1FastL2L3Residual total correction
          corrector->setRho   ( cms3.evt_fixgridfastjet_all_rho() );
          corrector->setJetA  ( cms3.pfjets_area().at(jetIdx)       );
          corrector->setJetPt ( pfjet_p4_uncor.pt()               );
          corrector->setJetEta( pfjet_p4_uncor.eta()              );
          double corr = corrector->getCorrection();

          // check for negative correction
          if (corr < 0. && fabs(pfjet_p4_uncor.eta()) < 4.7) {
            std::cout << "ScanChain::Looper: WARNING: negative jet correction: " << corr
                      << ", raw jet pt: " << pfjet_p4_uncor.pt() << ", eta: " << pfjet_p4_uncor.eta() << std::endl;
          }
	  // include protections here on jet kinematics to prevent rare warnings/crashes
	  double var = 1.;
	  if (!evt_isRealData() && JES_type != 0 && pfjet_p4_uncor.pt()*corr > 0. && fabs(pfjet_p4_uncor.eta()) < 5.4) {
	    jetcorr_uncertainty->setJetEta(pfjet_p4_uncor.eta());
	    jetcorr_uncertainty->setJetPt(pfjet_p4_uncor.pt() * corr); // must use CORRECTED pt
	    double unc = jetcorr_uncertainty->getUncertainty(true);
	    var = (1. + JES_type * unc);
	  }

          // apply new JEC to p4
          if(applynewcorr) pfjet_p4_cor = pfjet_p4_uncor * corr*var;
          else pfjet_p4_cor = pfjets_p4().at(jetIdx);

  if(jetIdx>=pfjets_p4().size()) return false;//safety requirement
  if(pfjet_p4_cor.pt() < pt) return false;
  if(fabs(pfjet_p4_cor.eta()) > eta) return false;
  if(!isFastsim && passjid && !isLoosePFJetV2(jetIdx)) return false;
  return true;
}

bool isVetoTrack(int ipf, LorentzVector lepp4_, int charge){
      if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lepp4_) < 0.4)  return false;
      //if not electron or muon
      if(abs(pfcands_particleId().at(ipf))!=11 && abs(pfcands_particleId().at(ipf))!=13){
          if(pfcands_p4().at(ipf).pt() < 10.) return false;
          if(TrackIso(ipf,0.3,0.1)/pfcands_p4().at(ipf).pt() >0.1) return false;
          if(pfcands_charge().at(ipf) * charge > 0) return false;
      }else{
          if(pfcands_p4().at(ipf).pt() < 5.) return false;
          if(TrackIso(ipf,0.3,0.1)/pfcands_p4().at(ipf).pt()  >0.2) return false;
      }
      return true;
}

bool isVetoTrack_v2(int ipf, LorentzVector lepp4_, int charge){
      if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lepp4_) < 0.4)  return false;
      //if not electron or muon
      if(abs(pfcands_particleId().at(ipf))!=11 && abs(pfcands_particleId().at(ipf))!=13){
          if(pfcands_p4().at(ipf).pt() < 10.) return false;
	  if(pfcands_p4().at(ipf).pt() > 60. ){
	    if(TrackIso(ipf,0.3,0.1) > 6.0 ) return false;
	  }
	  else{
	    if(TrackIso(ipf,0.3,0.1)/pfcands_p4().at(ipf).pt() > 0.1) return false;
	  }
          if(pfcands_charge().at(ipf) * charge > 0) return false;
      }
      else if(abs(pfcands_particleId().at(ipf))==11 ){
	if(pfcands_p4().at(ipf).pt() < 5.) return false;
	if(pfcands_p4().at(ipf).pt() > 60.0 ){
	  if(TrackIso(ipf,0.3,0.1) > 6.0 ) return false;
	}
	else{
	  if(TrackIso(ipf,0.3,0.1)/pfcands_p4().at(ipf).pt() > 0.1) return false;
	}
      }
      else if(abs(pfcands_particleId().at(ipf))==13 ){
	if(pfcands_p4().at(ipf).pt() < 5.) return false;
	if(pfcands_p4().at(ipf).pt() > 30.0 ){
	  if(TrackIso(ipf,0.3,0.1) > 6.0 ) return false;
	}
	else{
	  if(TrackIso(ipf,0.3,0.1)/pfcands_p4().at(ipf).pt() > 0.2) return false;
	}
      }
      return true;
}

bool isVetoTrack_v3(int ipf, LorentzVector lepp4_, int charge){
      if(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(ipf), lepp4_) < 0.4)  return false;
      //if not electron or muon
      if(abs(pfcands_particleId().at(ipf))!=11 && abs(pfcands_particleId().at(ipf))!=13){
          if(pfcands_p4().at(ipf).pt() <= 10.) return false;
	  if(pfcands_p4().at(ipf).pt() > 60. ){
	    if(TrackIso(ipf,0.3,0.1) > 6.0 ) return false;
	  }
	  else{
	    if(TrackIso(ipf,0.3,0.1)/pfcands_p4().at(ipf).pt() > 0.1) return false;
	  }
          if(pfcands_charge().at(ipf) * charge > 0) return false;
      }
      else return false;
      
      return true;
}

bool isVetoTau(int ipf, LorentzVector lepp4_, int charge){
      if(taus_pf_p4().at(ipf).pt() < 20) return false;
      if(fabs(taus_pf_p4().at(ipf).eta()) > 2.4) return false;
      if(passTauID("decayModeFinding",ipf) < 1) return false;
      if(passTauID("byMediumCombinedIsolationDeltaBetaCorr3Hits",ipf) < 1) return false;
      if(abs(charge) >= 99 || lepp4_.E() < 0.000001) return true; //If the lepton is a dummy, bypass the Delta-R and charge cuts
      if(ROOT::Math::VectorUtil::DeltaR(taus_pf_p4().at(ipf), lepp4_) < 0.4)  return false;
      if(taus_pf_charge().at(ipf) * charge > 0) return false;
      //if(taus_pf_IDs().at(ipf).at(33) < 1) return false;
      return true;
}

//overlap removal
int getOverlappingJetIndex(LorentzVector& lep_, vector<LorentzVector> jets_, double dR, float pt, float eta, bool passjid,FactorizedJetCorrector* corrector,bool applynewcorr, JetCorrectionUncertainty* jetcorr_uncertainty, int JES_type, bool isFastsim){
  float DR_lep_jet1 = 0.;
  float DR_lep_jet2 = 0.;
  int closestjet_idx = 0;
  
  if(jets_.size()==0) return -999;
  
	for(unsigned int iJet=1; iJet<jets_.size(); iJet++){
	  if(!PassJetPreSelections(iJet,pt,eta,passjid,corrector,applynewcorr,jetcorr_uncertainty,JES_type,isFastsim)) continue;
	  //if(jets_.at(iJet).Pt()<pt) continue;
	  //if(TMath::Abs(jets_.at(iJet).Eta())>eta) continue;
	  DR_lep_jet1 = ROOT::Math::VectorUtil::DeltaR(jets_.at(closestjet_idx), lep_);
	  DR_lep_jet2 = ROOT::Math::VectorUtil::DeltaR(jets_.at(iJet), lep_);
	  if(DR_lep_jet1 > DR_lep_jet2) closestjet_idx = iJet;
	}


	if(ROOT::Math::VectorUtil::DeltaR(jets_.at(closestjet_idx), lep_) > dR){
       //   cout<<"No overlapping jet found"<<endl;
          return -9999;
        }else return closestjet_idx;
}

int getOverlappingTrackIndex(LorentzVector& lep_, int pdgid_, vector<LorentzVector> tracks_, double dR){
  float DR_lep_track1 = 0.;
  float DR_lep_track2 = 0.;
  int closesttrack_idx = 0;
  if(tracks_.size()==0) return -999;

        for(unsigned int iTrk=1; iTrk<tracks_.size(); iTrk++){
            if(pfcands_particleId().at(iTrk) != pdgid_) continue;
        //    cout<<"Track PDG-id = "<<pfcands_particleId().at(iTrk)<<endl;
            if(pfcands_charge().at(iTrk) == 0) continue;
      	    if(pfcands_p4().at(iTrk).pt() < 5) continue;
      	    if(fabs(pfcands_dz().at(iTrk)) > 0.1) continue;
            DR_lep_track1 = ROOT::Math::VectorUtil::DeltaR(tracks_.at(closesttrack_idx), lep_);
            DR_lep_track2 = ROOT::Math::VectorUtil::DeltaR(tracks_.at(iTrk), lep_);
            if(DR_lep_track1 > DR_lep_track2) closesttrack_idx = iTrk;
        }

        if(ROOT::Math::VectorUtil::DeltaR(tracks_.at(closesttrack_idx), lep_) > dR){
          return -9999;
        }else return closesttrack_idx;
}


int leptonGenpCount(int& nele, int& nmuon, int& ntau) {
  nele=0;
  nmuon=0;
  ntau=0;
  int size = genps_id().size();
  for (int jj=0; jj<size; jj++) {
    if (abs(genps_id().at(jj)) == 11) nele++;
    if (abs(genps_id().at(jj)) == 13) nmuon++;
    if (abs(genps_id().at(jj)) == 15) ntau++;
  }

  return nele + nmuon + ntau;

}

int leptonGenpCount_lepTauDecays(int& nele, int& nmuon, int& ntau) {
  nele=0;
  nmuon=0;
  ntau=0;
  int size = genps_id().size();
  for (int jj=0; jj<size; jj++) {
    if (abs(genps_id().at(jj)) == 11) nele++;
    if (abs(genps_id().at(jj)) == 13) nmuon++;
    if (abs(genps_id().at(jj)) == 15) {
      for(unsigned int kk = 0; kk < genps_lepdaughter_id()[jj].size(); kk++) {
        int daughter = abs(genps_lepdaughter_id()[jj][kk]);
        //we count neutrino's because that guarantees that 
        //        //there is a corresponding lepton and that it comes from
        //                // a leptonic tau decay. You can get electrons from converted photons
        //                        //which are radiated by charged pions from the tau decay but thats
        //                                //hadronic and we don't care for those 
        if( daughter == 12 || daughter == 14)
          ntau++;
      }//daughter loop
    }//if tau
  }//genps loop

  return nele + nmuon + ntau;
}

struct sortbypt{
  bool operator () (const pair<int, LorentzVector> &v1, const pair<int,LorentzVector> &v2)
  {
        return v1.second.pt() > v2.second.pt();
  }
};

vector<pair <int, LorentzVector> > sort_pt( vector<LorentzVector> p4_, float pt_){
  vector<pair <int, LorentzVector> > sorted_;
  for(unsigned int iObj=0; iObj<p4_.size(); iObj++){
   if(p4_.at(iObj).pt()<pt_) continue;
   sorted_.push_back(make_pair(iObj,p4_.at(iObj)));
  }
  sort(sorted_.begin(),sorted_.end(),sortbypt());
  return sorted_;
}

vector< LorentzVector> getsortedp4(vector<pair <int, LorentzVector> > index_){
  vector<LorentzVector> sorted_p4;
  for(unsigned int iObj=0; iObj<index_.size(); iObj++){
   sorted_p4.push_back(index_.at(iObj).second);
  }
  return sorted_p4;
}

float getMinDphi(float metPhi, LorentzVector& vec1, LorentzVector& vec2 ) {                                                                                                    
  float dphimj1_    = getdphi(metPhi, vec1.phi() );
  float dphimj2_    = getdphi(metPhi, vec2.phi() );
  float dphimjmin_  = TMath::Min( dphimj1_ , dphimj2_ );

  return dphimjmin_;

}

float getdphi( float phi1 , float phi2 ){                                                                                                                                      
  float dphi = fabs( phi1 - phi2 );
  if( dphi > TMath::Pi() ) dphi = TMath::TwoPi() - dphi;
  return dphi;
}

float dRbetweenVectors(LorentzVector& vec1,LorentzVector& vec2 ){                                                                                                              
  float dphi = std::min(::fabs(vec1.Phi() - vec2.Phi()), 2 * M_PI - fabs(vec1.Phi() - vec2.Phi()));
  float deta = vec1.Eta() - vec2.Eta();

  return sqrt(dphi*dphi + deta*deta);
}

float calculateMt(const LorentzVector p4, double met, double met_phi){
  float phi1 = p4.Phi();
  float phi2 = met_phi;
  float Et1  = p4.Et();
  float Et2  = met;

  return sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
}

float DPhi_W_lep(float MET, float MET_Phi, LorentzVector p4){
  const TVector3 lep(p4.x(), p4.y(), p4.z());
  const TVector3 met(MET*cos(MET_Phi),MET*sin(MET_Phi),0);
  const TVector3 w = lep+met;
  double dphi = fabs(w.DeltaPhi(lep));
  return dphi;
}
