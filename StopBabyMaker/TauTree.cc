#include "TauTree.h"
#include "Math/GenVector/PtEtaPhiE4D.h"
#include "CMS3.h"

TauTree::TauTree ()
{
}

using namespace tas;

void TauTree::FillCommon (int idx,float tau_pt_cut, float tau_eta_cut)
{

    if(taus_pf_p4().at(idx).pt() < tau_pt_cut) return;
    if(fabs(taus_pf_p4().at(idx).eta()) > tau_eta_cut) return;

    tau_leadtrack_p4.push_back(taus_pf_lead_chargecand_p4().at(idx));
    tau_leadneutral_p4.push_back(taus_pf_lead_neutrcand_p4().at(idx));
    tau_p4.push_back(taus_pf_p4().at(idx));
    tau_isocand_p4.push_back(taus_pf_isocands_p4().at(idx));
    tau_sigcand_p4.push_back(taus_pf_signalcands_p4().at(idx));
    tau_ID.push_back(taus_pf_IDs().at(idx));
    tau_passID.push_back(passTauID("decayModeFinding",idx) &&
						 passTauID("byMediumCombinedIsolationDeltaBetaCorr3Hits",idx) );
    //tau_againstMuonTight.push_back();
    //tau_againstElectronLoose.push_back();
   // tau_isVetoTau.push_back();

}


void TauTree::Reset()
{
    tau_IDnames.clear();
    tau_leadtrack_p4.clear();
    tau_leadneutral_p4.clear();
    tau_p4.clear();
    tau_isocand_p4.clear();
    tau_sigcand_p4.clear();
    tau_ID.clear();
    tau_passID.clear();
    ngoodtaus= -9999.;
    tau_againstMuonTight.clear();
    tau_againstElectronLoose.clear();
    tau_isVetoTau.clear();
}

void TauTree::SetBranches(TTree* tree)
{
    tree->Branch("tau_IDnames",&tau_IDnames);
    tree->Branch("tau_leadtrack_p4",&tau_leadtrack_p4);
    tree->Branch("tau_leadneutral_p4",&tau_leadneutral_p4);
    tree->Branch("tau_p4",&tau_p4);
    tree->Branch("tau_isocand_p4",&tau_isocand_p4);
    tree->Branch("tau_sigcand_p4",&tau_sigcand_p4);
    tree->Branch("tau_ID",&tau_ID);
    tree->Branch("tau_passID",&tau_passID);
    tree->Branch("ngoodtaus",&ngoodtaus);
    tree->Branch("tau_againstMuonTight",&tau_againstMuonTight);
    tree->Branch("tau_againstElectronLoose",&tau_againstElectronLoose);
    tree->Branch("tau_isVetoTau",&tau_isVetoTau);
}
