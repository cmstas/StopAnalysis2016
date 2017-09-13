#include "IsoTracksTree.h"
#include "Math/GenVector/PtEtaPhiE4D.h"
#include "CMS3.h"
#include "IsoTrackVeto.h"
#include "StopSelections.h"

IsoTracksTree::IsoTracksTree ()
{
}

using namespace tas;

void IsoTracksTree::FillCommon (int idx)
{
       if (idx < 0) return;

     //if electron or muon, iso < 0.2
      isoTracks_charge.push_back( pfcands_charge().at(idx)    );
      isoTracks_p4.push_back    ( pfcands_p4().at(idx)        );
      isoTracks_absIso.push_back( pfcands_trackIso().at(idx)  );
      isoTracks_dz.push_back    ( pfcands_dz().at(idx)        );
      isoTracks_pdgId.push_back ( pfcands_particleId().at(idx));
}


void IsoTracksTree::Reset()
{
    isoTracks_p4.clear();
    isoTracks_charge.clear();
    isoTracks_absIso.clear();
    isoTracks_dz.clear();
    isoTracks_pdgId.clear();
   // isoTracks_selectedidx.clear();
  //  isoTracks_nselected = -9999;
    isoTracks_isVetoTrack.clear();
    isoTracks_isVetoTrack_v2.clear();
    isoTracks_isVetoTrack_v3.clear();
}

void IsoTracksTree::SetBranches(TTree* tree)
{

    tree->Branch("isoTracks_p4", &isoTracks_p4);
    tree->Branch("isoTracks_charge", &isoTracks_charge);
    tree->Branch("isoTracks_absIso", &isoTracks_absIso);
    tree->Branch("isoTracks_dz", &isoTracks_dz);
    tree->Branch("isoTracks_pdgId", &isoTracks_pdgId);
   // tree->Branch("isoTracks_selectedidx", &isoTracks_selectedidx);
  //  tree->Branch("isoTracks_nselected", &isoTracks_nselected);
    tree->Branch("isoTracks_isVetoTrack", &isoTracks_isVetoTrack);
    tree->Branch("isoTracks_isVetoTrack_v2", &isoTracks_isVetoTrack_v2);
    tree->Branch("isoTracks_isVetoTrack_v3", &isoTracks_isVetoTrack_v3);
}
