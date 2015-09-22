#include "PhotonTree.h"
#include <algorithm>
#include <cmath>
#include "Math/GenVector/PtEtaPhiE4D.h"
#include "Math/VectorUtil.h"
#include "CMS3.h"
#include "PhotonSelections.h"
#include "MCSelections.h"
#include "VertexSelections.h"
#include "StopSelections.h"
#include "IsolationTools.h"
#include "MCSelections.h"

PhotonTree::PhotonTree ()
{
}

PhotonTree::PhotonTree (const std::string &prefix)
  : prefix_(prefix)
{
}

using namespace tas;

void PhotonTree::FillCommon ()
{
   for(unsigned int idx = 0; idx < cms3.photons_p4().size(); idx++) {
    if (idx < 0) return;
    if(cms3.photons_p4().at(idx).pt() < m_ph_pt_cut) continue;
    if(fabs(cms3.photons_p4().at(idx).eta()) > m_ph_eta_cut) continue;
    if ( !isLoosePhoton(idx,analysis_t::HAD,2) ) continue;
    //general stuff
    p4.push_back(cms3.photons_p4().at(idx));
    pt.push_back(cms3.photons_p4().at(idx).pt());
    eta.push_back(cms3.photons_p4().at(idx).eta());
    phi.push_back(cms3.photons_p4().at(idx).phi());
    mass.push_back(cms3.photons_mass().at(idx));
    //id variables
    sigmaIEtaEta_fill5x5.push_back(photons_full5x5_sigmaIEtaIEta().at(idx));
    hOverE.push_back(photons_full5x5_hOverEtowBC().at(idx));
    r9.push_back(photons_full5x5_r9().at(idx));
    idCutBased.push_back(isTightPhoton(idx,analysis_t::HAD,2) ? 1 : 0); 
    //iso variables
    chiso.push_back(photons_recoChargedHadronIso().at(idx));
    nhiso.push_back(photons_recoNeutralHadronIso().at(idx));
    phiso.push_back(photons_recoPhotonIso().at(idx));
    overlapJetId.push_back(-1.);//this is a dummy and gets filled in looper.C


    //mc stuff
    //Some work for truth-matching (should be integrated in CMS3 as for the leptons
    int bestMatch = -1;
    if (!evt_isRealData()) {
       bestMatch = genbestMatch(idx);
       if(bestMatch>-1) mcp4.push_back(cms3.genps_p4().at(bestMatch)); else mcp4.push_back(LorentzVector(0, 0, 0, 0));
    }

 //   else {
//       cout<<__LINE__<<endl;
//       mcp4.push_back(LorentzVector(0, 0, 0, 0));
//    }

    if (bestMatch != -1) {        
	  // 7 is a special code for photons without a mother. this seems to be due to a miniAOD bug where links are broken.
	  mcMatchId.push_back(cms3.genps_id_simplemother().at(bestMatch) == 0 ? 7 : 22); 
	  genIso04.push_back(cms3.genps_iso().at(bestMatch));
	  // Now want to look at DR between photon and parton
	  float minDR = 999.;  
	  for(unsigned int iGen = 0; iGen < cms3.genps_p4().size(); iGen++){
	    if (cms3.genps_status().at(iGen) != 22 && cms3.genps_status().at(iGen) != 23) continue;
	    if (fabs(cms3.genps_id().at(iGen)) > 21) continue;
	    float dr = ROOT::Math::VectorUtil::DeltaR( cms3.genps_p4().at(iGen),cms3.genps_p4().at(bestMatch));
	    if (dr < minDR) minDR = dr;
	  }
	  drMinParton.push_back(minDR);
	}
	else {
	  mcMatchId.push_back(0);
	  genIso04.push_back(-1);
	  drMinParton.push_back(-1);
       } 
    } 
}

int  PhotonTree::genbestMatch(int idx)
{
    int bestMatch = -1;  float bestDr = 0.1; 
    float pt = cms3.photons_p4().at(idx).pt(); 
    float eta = cms3.photons_p4().at(idx).eta();

    for(unsigned int iGen = 0; iGen < cms3.genps_p4().size(); iGen++){
       if (cms3.genps_id().at(iGen) != 22) continue; 
       if (cms3.genps_status().at(iGen) != 1) continue; 
       if (fabs(cms3.genps_id_simplemother().at(iGen)) > 22  && cms3.genps_id_simplemother().at(iGen)!=2212) continue; // pions etc // but keep photons from the leading proton
       if ( fabs(eta - cms3.genps_p4().at(iGen).eta()) > 0.1) continue;
       if ( pt > 2*cms3.genps_p4().at(iGen).pt() ) continue;
       if ( pt < 0.5*cms3.genps_p4().at(iGen).pt() ) continue;
       float thisDR = ROOT::Math::VectorUtil::DeltaR( cms3.genps_p4().at(iGen), cms3.photons_p4().at(idx));
       if (thisDR < bestDr) {
	  bestDr = thisDR;
	  bestMatch = iGen;
       }
   }
   return bestMatch;
}

void PhotonTree::SetPhotonSelection (float pt_cut,float eta)
{
  m_ph_pt_cut = pt_cut; m_ph_eta_cut = eta;
   
  return;
}

void PhotonTree::Reset()
{
    sigmaIEtaEta_fill5x5.clear(); 
    hOverE.clear();
    r9.clear();
    idCutBased.clear();

    p4.clear();
    pt.clear();
    eta.clear();
    mass.clear();
    phi.clear();

    chiso.clear();     	   
    nhiso.clear();
    phiso.clear();

    overlapJetId.clear();

    mcp4.clear();
    mcMatchId.clear();
    genIso04.clear();
    drMinParton.clear();
}

void PhotonTree::SetBranches(TTree* tree)
{
    tree->Branch(Form("%ssigmaIEtaEta_fill5x5", prefix_.c_str()) , &sigmaIEtaEta_fill5x5);
    tree->Branch(Form("%shOverE"        , prefix_.c_str()) , &hOverE);
    tree->Branch(Form("%sr9"        , prefix_.c_str()) , &r9);

    tree->Branch(Form("%schiso"       , prefix_.c_str()) , &chiso);
    tree->Branch(Form("%snhiso"       , prefix_.c_str()) , &nhiso);
    tree->Branch(Form("%sphiso"       , prefix_.c_str()) , &phiso);
    tree->Branch(Form("%sidCutBased"       , prefix_.c_str()) , &idCutBased);

    tree->Branch(Form("%soverlapJetId"       , prefix_.c_str()) , &overlapJetId);
    
    tree->Branch(Form("%sp4"      , prefix_.c_str()) , &p4      );
    tree->Branch(Form("%smcp4"    , prefix_.c_str()) , &mcp4    );

    tree->Branch(Form("%spt"	 , prefix_.c_str()) , &pt);
    tree->Branch(Form("%seta"      , prefix_.c_str()) , &eta);
    tree->Branch(Form("%sphi"      , prefix_.c_str()) , &phi);
    tree->Branch(Form("%smass"      , prefix_.c_str()) , &mass);
    tree->Branch(Form("%smcMatchId"      , prefix_.c_str()) , &mcMatchId);
    tree->Branch(Form("%sgenIso04"      , prefix_.c_str()) , &genIso04);
    tree->Branch(Form("%sdrMinParton"      , prefix_.c_str()) , &drMinParton);
}
