// -*- C++ -*-
#ifndef stop_1l_babyAnalyzer_H
#define stop_1l_babyAnalyzer_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include <vector> 
#include <unistd.h> 
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std; 
class stop_1l_babyAnalyzer {
private: 
protected: 
	unsigned int index;
	unsigned int	run_;
	TBranch *run_branch;
	bool run_isLoaded;
	unsigned int	ls_;
	TBranch *ls_branch;
	bool ls_isLoaded;
	unsigned int	evt_;
	TBranch *evt_branch;
	bool evt_isLoaded;
	int	nvtxs_;
	TBranch *nvtxs_branch;
	bool nvtxs_isLoaded;
	int	pu_nvtxs_;
	TBranch *pu_nvtxs_branch;
	bool pu_nvtxs_isLoaded;
	float	pfmet_;
	TBranch *pfmet_branch;
	bool pfmet_isLoaded;
	float	pfmet_phi_;
	TBranch *pfmet_phi_branch;
	bool pfmet_phi_isLoaded;
	float	pfmet_rl_;
	TBranch *pfmet_rl_branch;
	bool pfmet_rl_isLoaded;
	float	pfmet_phi_rl_;
	TBranch *pfmet_phi_rl_branch;
	bool pfmet_phi_rl_isLoaded;
	float	scale1fb_;
	TBranch *scale1fb_branch;
	bool scale1fb_isLoaded;
	float	xsec_;
	TBranch *xsec_branch;
	bool xsec_isLoaded;
	float	xsec_uncert_;
	TBranch *xsec_uncert_branch;
	bool xsec_uncert_isLoaded;
	float	kfactor_;
	TBranch *kfactor_branch;
	bool kfactor_isLoaded;
	float	pu_ntrue_;
	TBranch *pu_ntrue_branch;
	bool pu_ntrue_isLoaded;
	int	ngoodleps_;
	TBranch *ngoodleps_branch;
	bool ngoodleps_isLoaded;
	int	nvetoleps_;
	TBranch *nvetoleps_branch;
	bool nvetoleps_isLoaded;
	bool	is_data_;
	TBranch *is_data_branch;
	bool is_data_isLoaded;
	string *dataset_;
	TBranch *dataset_branch;
	bool dataset_isLoaded;
	string *filename_;
	TBranch *filename_branch;
	bool filename_isLoaded;
	string *cms3tag_;
	TBranch *cms3tag_branch;
	bool cms3tag_isLoaded;
	unsigned int	nEvents_;
	TBranch *nEvents_branch;
	bool nEvents_isLoaded;
	unsigned int	nEvents_goodvtx_;
	TBranch *nEvents_goodvtx_branch;
	bool nEvents_goodvtx_isLoaded;
	unsigned int	nEvents_MET30_;
	TBranch *nEvents_MET30_branch;
	bool nEvents_MET30_isLoaded;
	unsigned int	nEvents_1goodlep_;
	TBranch *nEvents_1goodlep_branch;
	bool nEvents_1goodlep_isLoaded;
	unsigned int	nEvents_2goodjets_;
	TBranch *nEvents_2goodjets_branch;
	bool nEvents_2goodjets_isLoaded;
	int	is0lep_;
	TBranch *is0lep_branch;
	bool is0lep_isLoaded;
	int	is1lep_;
	TBranch *is1lep_branch;
	bool is1lep_isLoaded;
	int	is2lep_;
	TBranch *is2lep_branch;
	bool is2lep_isLoaded;
	int	isZtoNuNu_;
	TBranch *isZtoNuNu_branch;
	bool isZtoNuNu_isLoaded;
	int	is1lepFromW_;
	TBranch *is1lepFromW_branch;
	bool is1lepFromW_isLoaded;
	int	is1lepFromTop_;
	TBranch *is1lepFromTop_branch;
	bool is1lepFromTop_isLoaded;
	float	MT2W_;
	TBranch *MT2W_branch;
	bool MT2W_isLoaded;
	float	MT2W_rl_;
	TBranch *MT2W_rl_branch;
	bool MT2W_rl_isLoaded;
	float	mindphi_met_j1_j2_;
	TBranch *mindphi_met_j1_j2_branch;
	bool mindphi_met_j1_j2_isLoaded;
	float	mindphi_met_j1_j2_rl_;
	TBranch *mindphi_met_j1_j2_rl_branch;
	bool mindphi_met_j1_j2_rl_isLoaded;
	float	mt_met_lep_;
	TBranch *mt_met_lep_branch;
	bool mt_met_lep_isLoaded;
	float	mt_met_lep_rl_;
	TBranch *mt_met_lep_rl_branch;
	bool mt_met_lep_rl_isLoaded;
	float	hadronic_top_chi2_;
	TBranch *hadronic_top_chi2_branch;
	bool hadronic_top_chi2_isLoaded;
	float	ak4pfjets_rho_;
	TBranch *ak4pfjets_rho_branch;
	bool ak4pfjets_rho_isLoaded;
	float	pdf_up_weight_;
	TBranch *pdf_up_weight_branch;
	bool pdf_up_weight_isLoaded;
	float	pdf_down_weight_;
	TBranch *pdf_down_weight_branch;
	bool pdf_down_weight_isLoaded;
	vector<string> *genweightsID_;
	TBranch *genweightsID_branch;
	bool genweightsID_isLoaded;
	vector<float> *genweights_;
	TBranch *genweights_branch;
	bool genweights_isLoaded;
	float	weight_btagsf_;
	TBranch *weight_btagsf_branch;
	bool weight_btagsf_isLoaded;
	float	weight_btagsf_heavy_UP_;
	TBranch *weight_btagsf_heavy_UP_branch;
	bool weight_btagsf_heavy_UP_isLoaded;
	float	weight_btagsf_light_UP_;
	TBranch *weight_btagsf_light_UP_branch;
	bool weight_btagsf_light_UP_isLoaded;
	float	weight_btagsf_heavy_DN_;
	TBranch *weight_btagsf_heavy_DN_branch;
	bool weight_btagsf_heavy_DN_isLoaded;
	float	weight_btagsf_light_DN_;
	TBranch *weight_btagsf_light_DN_branch;
	bool weight_btagsf_light_DN_isLoaded;
	float	weight_btagsf_fastsim_UP_;
	TBranch *weight_btagsf_fastsim_UP_branch;
	bool weight_btagsf_fastsim_UP_isLoaded;
	float	weight_btagsf_fastsim_DN_;
	TBranch *weight_btagsf_fastsim_DN_branch;
	bool weight_btagsf_fastsim_DN_isLoaded;
	float	weight_lepSF_;
	TBranch *weight_lepSF_branch;
	bool weight_lepSF_isLoaded;
	float	weight_lepSF_up_;
	TBranch *weight_lepSF_up_branch;
	bool weight_lepSF_up_isLoaded;
	float	weight_lepSF_down_;
	TBranch *weight_lepSF_down_branch;
	bool weight_lepSF_down_isLoaded;
	float	weight_vetoLepSF_;
	TBranch *weight_vetoLepSF_branch;
	bool weight_vetoLepSF_isLoaded;
	float	weight_vetoLepSF_up_;
	TBranch *weight_vetoLepSF_up_branch;
	bool weight_vetoLepSF_up_isLoaded;
	float	weight_vetoLepSF_down_;
	TBranch *weight_vetoLepSF_down_branch;
	bool weight_vetoLepSF_down_isLoaded;
	float	weight_lepSF_fastSim_;
	TBranch *weight_lepSF_fastSim_branch;
	bool weight_lepSF_fastSim_isLoaded;
	float	weight_lepSF_fastSim_up_;
	TBranch *weight_lepSF_fastSim_up_branch;
	bool weight_lepSF_fastSim_up_isLoaded;
	float	weight_lepSF_fastSim_down_;
	TBranch *weight_lepSF_fastSim_down_branch;
	bool weight_lepSF_fastSim_down_isLoaded;
	float	weight_ISR_;
	TBranch *weight_ISR_branch;
	bool weight_ISR_isLoaded;
	float	weight_ISRup_;
	TBranch *weight_ISRup_branch;
	bool weight_ISRup_isLoaded;
	float	weight_ISRdown_;
	TBranch *weight_ISRdown_branch;
	bool weight_ISRdown_isLoaded;
	float	weight_PU_;
	TBranch *weight_PU_branch;
	bool weight_PU_isLoaded;
	float	weight_PUup_;
	TBranch *weight_PUup_branch;
	bool weight_PUup_isLoaded;
	float	weight_PUdown_;
	TBranch *weight_PUdown_branch;
	bool weight_PUdown_isLoaded;
	vector<string> *sparms_names_;
	TBranch *sparms_names_branch;
	bool sparms_names_isLoaded;
	vector<float> *sparms_values_;
	TBranch *sparms_values_branch;
	bool sparms_values_isLoaded;
	int	sparms_subProcessId_;
	TBranch *sparms_subProcessId_branch;
	bool sparms_subProcessId_isLoaded;
	float	mass_lsp_;
	TBranch *mass_lsp_branch;
	bool mass_lsp_isLoaded;
	float	mass_chargino_;
	TBranch *mass_chargino_branch;
	bool mass_chargino_isLoaded;
	float	mass_stop_;
	TBranch *mass_stop_branch;
	bool mass_stop_isLoaded;
	float	mass_gluino_;
	TBranch *mass_gluino_branch;
	bool mass_gluino_isLoaded;
	float	genmet_;
	TBranch *genmet_branch;
	bool genmet_isLoaded;
	float	genmet_phi_;
	TBranch *genmet_phi_branch;
	bool genmet_phi_isLoaded;
	float	nupt_;
	TBranch *nupt_branch;
	bool nupt_isLoaded;
	float	genht_;
	TBranch *genht_branch;
	bool genht_isLoaded;
	bool	PassTrackVeto_;
	TBranch *PassTrackVeto_branch;
	bool PassTrackVeto_isLoaded;
	bool	PassTauVeto_;
	TBranch *PassTauVeto_branch;
	bool PassTauVeto_isLoaded;
	float	topness_;
	TBranch *topness_branch;
	bool topness_isLoaded;
	float	topnessMod_;
	TBranch *topnessMod_branch;
	bool topnessMod_isLoaded;
	float	topnessMod_rl_;
	TBranch *topnessMod_rl_branch;
	bool topnessMod_rl_isLoaded;
	float	Mlb_closestb_;
	TBranch *Mlb_closestb_branch;
	bool Mlb_closestb_isLoaded;
	int	HLT_SingleEl_;
	TBranch *HLT_SingleEl_branch;
	bool HLT_SingleEl_isLoaded;
	int	HLT_SingleMu_;
	TBranch *HLT_SingleMu_branch;
	bool HLT_SingleMu_isLoaded;
	int	HLT_MET_;
	TBranch *HLT_MET_branch;
	bool HLT_MET_isLoaded;
	int	HLT_MET100_MHT100_;
	TBranch *HLT_MET100_MHT100_branch;
	bool HLT_MET100_MHT100_isLoaded;
	int	HLT_DiEl_;
	TBranch *HLT_DiEl_branch;
	bool HLT_DiEl_isLoaded;
	int	HLT_DiMu_;
	TBranch *HLT_DiMu_branch;
	bool HLT_DiMu_isLoaded;
	int	HLT_MuE_;
	TBranch *HLT_MuE_branch;
	bool HLT_MuE_isLoaded;
	int	HLT_Photon90_CaloIdL_PFHT500_;
	TBranch *HLT_Photon90_CaloIdL_PFHT500_branch;
	bool HLT_Photon90_CaloIdL_PFHT500_isLoaded;
	int	HLT_Photon22_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon22_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon22_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon30_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon30_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon30_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon36_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon36_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon36_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon50_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon50_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon50_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon75_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon75_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon75_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon90_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon90_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon90_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon120_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon120_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon120_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon165_R9Id90_HE10_IsoM_;
	TBranch *HLT_Photon165_R9Id90_HE10_IsoM_branch;
	bool HLT_Photon165_R9Id90_HE10_IsoM_isLoaded;
	int	HLT_Photon175_;
	TBranch *HLT_Photon175_branch;
	bool HLT_Photon175_isLoaded;
	int	HLT_Photon165_HE10_;
	TBranch *HLT_Photon165_HE10_branch;
	bool HLT_Photon165_HE10_isLoaded;
	int	nPhotons_;
	TBranch *nPhotons_branch;
	bool nPhotons_isLoaded;
	int	ph_ngoodjets_;
	TBranch *ph_ngoodjets_branch;
	bool ph_ngoodjets_isLoaded;
	int	ph_ngoodbtags_;
	TBranch *ph_ngoodbtags_branch;
	bool ph_ngoodbtags_isLoaded;
	float	filt_met_;
	TBranch *filt_met_branch;
	bool filt_met_isLoaded;
	float	hardgenpt_;
	TBranch *hardgenpt_branch;
	bool hardgenpt_isLoaded;
	float	filt_badChargedCandidateFilter_;
	TBranch *filt_badChargedCandidateFilter_branch;
	bool filt_badChargedCandidateFilter_isLoaded;
	float	filt_badMuonFilter_;
	TBranch *filt_badMuonFilter_branch;
	bool filt_badMuonFilter_isLoaded;
	float	calomet_;
	TBranch *calomet_branch;
	bool calomet_isLoaded;
	float	calomet_phi_;
	TBranch *calomet_phi_branch;
	bool calomet_phi_isLoaded;
	int	lep1_pdgid_;
	TBranch *lep1_pdgid_branch;
	bool lep1_pdgid_isLoaded;
	int	lep1_production_type_;
	TBranch *lep1_production_type_branch;
	bool lep1_production_type_isLoaded;
	float	lep1_MiniIso_;
	TBranch *lep1_MiniIso_branch;
	bool lep1_MiniIso_isLoaded;
	float	lep1_relIso_;
	TBranch *lep1_relIso_branch;
	bool lep1_relIso_isLoaded;
	bool	lep1_passLooseID_;
	TBranch *lep1_passLooseID_branch;
	bool lep1_passLooseID_isLoaded;
	bool	lep1_passMediumID_;
	TBranch *lep1_passMediumID_branch;
	bool lep1_passMediumID_isLoaded;
	bool	lep1_passTightID_;
	TBranch *lep1_passTightID_branch;
	bool lep1_passTightID_isLoaded;
	bool	lep1_passVeto_;
	TBranch *lep1_passVeto_branch;
	bool lep1_passVeto_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_p4_;
	TBranch *lep1_p4_branch;
	bool lep1_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_mcp4_;
	TBranch *lep1_mcp4_branch;
	bool lep1_mcp4_isLoaded;
	int	lep1_mc_motherid_;
	TBranch *lep1_mc_motherid_branch;
	bool lep1_mc_motherid_isLoaded;
	int	lep2_pdgid_;
	TBranch *lep2_pdgid_branch;
	bool lep2_pdgid_isLoaded;
	int	lep2_production_type_;
	TBranch *lep2_production_type_branch;
	bool lep2_production_type_isLoaded;
	float	lep2_MiniIso_;
	TBranch *lep2_MiniIso_branch;
	bool lep2_MiniIso_isLoaded;
	float	lep2_relIso_;
	TBranch *lep2_relIso_branch;
	bool lep2_relIso_isLoaded;
	bool	lep2_passLooseID_;
	TBranch *lep2_passLooseID_branch;
	bool lep2_passLooseID_isLoaded;
	bool	lep2_passMediumID_;
	TBranch *lep2_passMediumID_branch;
	bool lep2_passMediumID_isLoaded;
	bool	lep2_passTightID_;
	TBranch *lep2_passTightID_branch;
	bool lep2_passTightID_isLoaded;
	bool	lep2_passVeto_;
	TBranch *lep2_passVeto_branch;
	bool lep2_passVeto_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_p4_;
	TBranch *lep2_p4_branch;
	bool lep2_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_mcp4_;
	TBranch *lep2_mcp4_branch;
	bool lep2_mcp4_isLoaded;
	int	lep2_mc_motherid_;
	TBranch *lep2_mc_motherid_branch;
	bool lep2_mc_motherid_isLoaded;
	vector<float> *ph_sigmaIEtaEta_fill5x5_;
	TBranch *ph_sigmaIEtaEta_fill5x5_branch;
	bool ph_sigmaIEtaEta_fill5x5_isLoaded;
	vector<float> *ph_hOverE_;
	TBranch *ph_hOverE_branch;
	bool ph_hOverE_isLoaded;
	vector<float> *ph_r9_;
	TBranch *ph_r9_branch;
	bool ph_r9_isLoaded;
	vector<float> *ph_chiso_;
	TBranch *ph_chiso_branch;
	bool ph_chiso_isLoaded;
	vector<float> *ph_nhiso_;
	TBranch *ph_nhiso_branch;
	bool ph_nhiso_isLoaded;
	vector<float> *ph_phiso_;
	TBranch *ph_phiso_branch;
	bool ph_phiso_isLoaded;
	vector<bool> *ph_idCutBased_;
	TBranch *ph_idCutBased_branch;
	bool ph_idCutBased_isLoaded;
	vector<int> *ph_overlapJetId_;
	TBranch *ph_overlapJetId_branch;
	bool ph_overlapJetId_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *ph_p4_;
	TBranch *ph_p4_branch;
	bool ph_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *ph_mcp4_;
	TBranch *ph_mcp4_branch;
	bool ph_mcp4_isLoaded;
	vector<float> *ph_pt_;
	TBranch *ph_pt_branch;
	bool ph_pt_isLoaded;
	vector<float> *ph_eta_;
	TBranch *ph_eta_branch;
	bool ph_eta_isLoaded;
	vector<float> *ph_phi_;
	TBranch *ph_phi_branch;
	bool ph_phi_isLoaded;
	vector<float> *ph_mass_;
	TBranch *ph_mass_branch;
	bool ph_mass_isLoaded;
	vector<int> *ph_mcMatchId_;
	TBranch *ph_mcMatchId_branch;
	bool ph_mcMatchId_isLoaded;
	vector<float> *ph_genIso04_;
	TBranch *ph_genIso04_branch;
	bool ph_genIso04_isLoaded;
	vector<float> *ph_drMinParton_;
	TBranch *ph_drMinParton_branch;
	bool ph_drMinParton_isLoaded;
	int	ngoodjets_;
	TBranch *ngoodjets_branch;
	bool ngoodjets_isLoaded;
	int	ngoodbtags_;
	TBranch *ngoodbtags_branch;
	bool ngoodbtags_isLoaded;
	float	ak4_HT_;
	TBranch *ak4_HT_branch;
	bool ak4_HT_isLoaded;
	float	ak4_htratiom_;
	TBranch *ak4_htratiom_branch;
	bool ak4_htratiom_isLoaded;
	vector<float> *dphi_ak4pfjet_met_;
	TBranch *dphi_ak4pfjet_met_branch;
	bool dphi_ak4pfjet_met_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *ak4pfjets_p4_;
	TBranch *ak4pfjets_p4_branch;
	bool ak4pfjets_p4_isLoaded;
	vector<bool> *ak4pfjets_passMEDbtag_;
	TBranch *ak4pfjets_passMEDbtag_branch;
	bool ak4pfjets_passMEDbtag_isLoaded;
	vector<float> *ak4pfjets_CSV_;
	TBranch *ak4pfjets_CSV_branch;
	bool ak4pfjets_CSV_isLoaded;
	vector<float> *ak4pfjets_mva_;
	TBranch *ak4pfjets_mva_branch;
	bool ak4pfjets_mva_isLoaded;
	vector<int> *ak4pfjets_parton_flavor_;
	TBranch *ak4pfjets_parton_flavor_branch;
	bool ak4pfjets_parton_flavor_isLoaded;
	vector<int> *ak4pfjets_hadron_flavor_;
	TBranch *ak4pfjets_hadron_flavor_branch;
	bool ak4pfjets_hadron_flavor_isLoaded;
	vector<bool> *ak4pfjets_loose_puid_;
	TBranch *ak4pfjets_loose_puid_branch;
	bool ak4pfjets_loose_puid_isLoaded;
	vector<bool> *ak4pfjets_loose_pfid_;
	TBranch *ak4pfjets_loose_pfid_branch;
	bool ak4pfjets_loose_pfid_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *ak4pfjets_leadMEDbjet_p4_;
	TBranch *ak4pfjets_leadMEDbjet_p4_branch;
	bool ak4pfjets_leadMEDbjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *ak4pfjets_leadbtag_p4_;
	TBranch *ak4pfjets_leadbtag_p4_branch;
	bool ak4pfjets_leadbtag_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *ak4genjets_p4_;
	TBranch *ak4genjets_p4_branch;
	bool ak4genjets_p4_isLoaded;
	vector<bool> *genleps_isfromt_;
	TBranch *genleps_isfromt_branch;
	bool genleps_isfromt_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genleps_p4_;
	TBranch *genleps_p4_branch;
	bool genleps_p4_isLoaded;
	vector<int> *genleps_id_;
	TBranch *genleps_id_branch;
	bool genleps_id_isLoaded;
	vector<int> *genleps__genpsidx_;
	TBranch *genleps__genpsidx_branch;
	bool genleps__genpsidx_isLoaded;
	vector<int> *genleps_status_;
	TBranch *genleps_status_branch;
	bool genleps_status_isLoaded;
	vector<bool> *genleps_fromHardProcessDecayed_;
	TBranch *genleps_fromHardProcessDecayed_branch;
	bool genleps_fromHardProcessDecayed_isLoaded;
	vector<bool> *genleps_fromHardProcessFinalState_;
	TBranch *genleps_fromHardProcessFinalState_branch;
	bool genleps_fromHardProcessFinalState_isLoaded;
	vector<bool> *genleps_isHardProcess_;
	TBranch *genleps_isHardProcess_branch;
	bool genleps_isHardProcess_isLoaded;
	vector<bool> *genleps_isLastCopy_;
	TBranch *genleps_isLastCopy_branch;
	bool genleps_isLastCopy_isLoaded;
	vector<int> *genleps_gentaudecay_;
	TBranch *genleps_gentaudecay_branch;
	bool genleps_gentaudecay_isLoaded;
	int	gen_nfromtleps__;
	TBranch *gen_nfromtleps__branch;
	bool gen_nfromtleps__isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genleps_motherp4_;
	TBranch *genleps_motherp4_branch;
	bool genleps_motherp4_isLoaded;
	vector<int> *genleps_motherid_;
	TBranch *genleps_motherid_branch;
	bool genleps_motherid_isLoaded;
	vector<int> *genleps_motheridx_;
	TBranch *genleps_motheridx_branch;
	bool genleps_motheridx_isLoaded;
	vector<int> *genleps_motherstatus_;
	TBranch *genleps_motherstatus_branch;
	bool genleps_motherstatus_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genleps_gmotherp4_;
	TBranch *genleps_gmotherp4_branch;
	bool genleps_gmotherp4_isLoaded;
	vector<int> *genleps_gmotherid_;
	TBranch *genleps_gmotherid_branch;
	bool genleps_gmotherid_isLoaded;
	vector<int> *genleps_gmotheridx_;
	TBranch *genleps_gmotheridx_branch;
	bool genleps_gmotheridx_isLoaded;
	vector<int> *genleps_gmotherstatus_;
	TBranch *genleps_gmotherstatus_branch;
	bool genleps_gmotherstatus_isLoaded;
	vector<bool> *gennus_isfromt_;
	TBranch *gennus_isfromt_branch;
	bool gennus_isfromt_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gennus_p4_;
	TBranch *gennus_p4_branch;
	bool gennus_p4_isLoaded;
	vector<int> *gennus_id_;
	TBranch *gennus_id_branch;
	bool gennus_id_isLoaded;
	vector<int> *gennus__genpsidx_;
	TBranch *gennus__genpsidx_branch;
	bool gennus__genpsidx_isLoaded;
	vector<int> *gennus_status_;
	TBranch *gennus_status_branch;
	bool gennus_status_isLoaded;
	vector<bool> *gennus_fromHardProcessDecayed_;
	TBranch *gennus_fromHardProcessDecayed_branch;
	bool gennus_fromHardProcessDecayed_isLoaded;
	vector<bool> *gennus_fromHardProcessFinalState_;
	TBranch *gennus_fromHardProcessFinalState_branch;
	bool gennus_fromHardProcessFinalState_isLoaded;
	vector<bool> *gennus_isHardProcess_;
	TBranch *gennus_isHardProcess_branch;
	bool gennus_isHardProcess_isLoaded;
	vector<bool> *gennus_isLastCopy_;
	TBranch *gennus_isLastCopy_branch;
	bool gennus_isLastCopy_isLoaded;
	vector<int> *gennus_gentaudecay_;
	TBranch *gennus_gentaudecay_branch;
	bool gennus_gentaudecay_isLoaded;
	int	gen_nfromtnus__;
	TBranch *gen_nfromtnus__branch;
	bool gen_nfromtnus__isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gennus_motherp4_;
	TBranch *gennus_motherp4_branch;
	bool gennus_motherp4_isLoaded;
	vector<int> *gennus_motherid_;
	TBranch *gennus_motherid_branch;
	bool gennus_motherid_isLoaded;
	vector<int> *gennus_motheridx_;
	TBranch *gennus_motheridx_branch;
	bool gennus_motheridx_isLoaded;
	vector<int> *gennus_motherstatus_;
	TBranch *gennus_motherstatus_branch;
	bool gennus_motherstatus_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gennus_gmotherp4_;
	TBranch *gennus_gmotherp4_branch;
	bool gennus_gmotherp4_isLoaded;
	vector<int> *gennus_gmotherid_;
	TBranch *gennus_gmotherid_branch;
	bool gennus_gmotherid_isLoaded;
	vector<int> *gennus_gmotheridx_;
	TBranch *gennus_gmotheridx_branch;
	bool gennus_gmotheridx_isLoaded;
	vector<int> *gennus_gmotherstatus_;
	TBranch *gennus_gmotherstatus_branch;
	bool gennus_gmotherstatus_isLoaded;
	vector<bool> *genqs_isfromt_;
	TBranch *genqs_isfromt_branch;
	bool genqs_isfromt_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genqs_p4_;
	TBranch *genqs_p4_branch;
	bool genqs_p4_isLoaded;
	vector<int> *genqs_id_;
	TBranch *genqs_id_branch;
	bool genqs_id_isLoaded;
	vector<int> *genqs__genpsidx_;
	TBranch *genqs__genpsidx_branch;
	bool genqs__genpsidx_isLoaded;
	vector<int> *genqs_status_;
	TBranch *genqs_status_branch;
	bool genqs_status_isLoaded;
	vector<bool> *genqs_fromHardProcessDecayed_;
	TBranch *genqs_fromHardProcessDecayed_branch;
	bool genqs_fromHardProcessDecayed_isLoaded;
	vector<bool> *genqs_fromHardProcessFinalState_;
	TBranch *genqs_fromHardProcessFinalState_branch;
	bool genqs_fromHardProcessFinalState_isLoaded;
	vector<bool> *genqs_isHardProcess_;
	TBranch *genqs_isHardProcess_branch;
	bool genqs_isHardProcess_isLoaded;
	vector<bool> *genqs_isLastCopy_;
	TBranch *genqs_isLastCopy_branch;
	bool genqs_isLastCopy_isLoaded;
	vector<int> *genqs_gentaudecay_;
	TBranch *genqs_gentaudecay_branch;
	bool genqs_gentaudecay_isLoaded;
	int	gen_nfromtqs__;
	TBranch *gen_nfromtqs__branch;
	bool gen_nfromtqs__isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genqs_motherp4_;
	TBranch *genqs_motherp4_branch;
	bool genqs_motherp4_isLoaded;
	vector<int> *genqs_motherid_;
	TBranch *genqs_motherid_branch;
	bool genqs_motherid_isLoaded;
	vector<int> *genqs_motheridx_;
	TBranch *genqs_motheridx_branch;
	bool genqs_motheridx_isLoaded;
	vector<int> *genqs_motherstatus_;
	TBranch *genqs_motherstatus_branch;
	bool genqs_motherstatus_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genqs_gmotherp4_;
	TBranch *genqs_gmotherp4_branch;
	bool genqs_gmotherp4_isLoaded;
	vector<int> *genqs_gmotherid_;
	TBranch *genqs_gmotherid_branch;
	bool genqs_gmotherid_isLoaded;
	vector<int> *genqs_gmotheridx_;
	TBranch *genqs_gmotheridx_branch;
	bool genqs_gmotheridx_isLoaded;
	vector<int> *genqs_gmotherstatus_;
	TBranch *genqs_gmotherstatus_branch;
	bool genqs_gmotherstatus_isLoaded;
	vector<bool> *genbosons_isfromt_;
	TBranch *genbosons_isfromt_branch;
	bool genbosons_isfromt_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genbosons_p4_;
	TBranch *genbosons_p4_branch;
	bool genbosons_p4_isLoaded;
	vector<int> *genbosons_id_;
	TBranch *genbosons_id_branch;
	bool genbosons_id_isLoaded;
	vector<int> *genbosons__genpsidx_;
	TBranch *genbosons__genpsidx_branch;
	bool genbosons__genpsidx_isLoaded;
	vector<int> *genbosons_status_;
	TBranch *genbosons_status_branch;
	bool genbosons_status_isLoaded;
	vector<bool> *genbosons_fromHardProcessDecayed_;
	TBranch *genbosons_fromHardProcessDecayed_branch;
	bool genbosons_fromHardProcessDecayed_isLoaded;
	vector<bool> *genbosons_fromHardProcessFinalState_;
	TBranch *genbosons_fromHardProcessFinalState_branch;
	bool genbosons_fromHardProcessFinalState_isLoaded;
	vector<bool> *genbosons_isHardProcess_;
	TBranch *genbosons_isHardProcess_branch;
	bool genbosons_isHardProcess_isLoaded;
	vector<bool> *genbosons_isLastCopy_;
	TBranch *genbosons_isLastCopy_branch;
	bool genbosons_isLastCopy_isLoaded;
	vector<int> *genbosons_gentaudecay_;
	TBranch *genbosons_gentaudecay_branch;
	bool genbosons_gentaudecay_isLoaded;
	int	gen_nfromtbosons__;
	TBranch *gen_nfromtbosons__branch;
	bool gen_nfromtbosons__isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genbosons_motherp4_;
	TBranch *genbosons_motherp4_branch;
	bool genbosons_motherp4_isLoaded;
	vector<int> *genbosons_motherid_;
	TBranch *genbosons_motherid_branch;
	bool genbosons_motherid_isLoaded;
	vector<int> *genbosons_motheridx_;
	TBranch *genbosons_motheridx_branch;
	bool genbosons_motheridx_isLoaded;
	vector<int> *genbosons_motherstatus_;
	TBranch *genbosons_motherstatus_branch;
	bool genbosons_motherstatus_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *genbosons_gmotherp4_;
	TBranch *genbosons_gmotherp4_branch;
	bool genbosons_gmotherp4_isLoaded;
	vector<int> *genbosons_gmotherid_;
	TBranch *genbosons_gmotherid_branch;
	bool genbosons_gmotherid_isLoaded;
	vector<int> *genbosons_gmotheridx_;
	TBranch *genbosons_gmotheridx_branch;
	bool genbosons_gmotheridx_isLoaded;
	vector<int> *genbosons_gmotherstatus_;
	TBranch *genbosons_gmotherstatus_branch;
	bool genbosons_gmotherstatus_isLoaded;
	vector<bool> *gensusy_isfromt_;
	TBranch *gensusy_isfromt_branch;
	bool gensusy_isfromt_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gensusy_p4_;
	TBranch *gensusy_p4_branch;
	bool gensusy_p4_isLoaded;
	vector<int> *gensusy_id_;
	TBranch *gensusy_id_branch;
	bool gensusy_id_isLoaded;
	vector<int> *gensusy__genpsidx_;
	TBranch *gensusy__genpsidx_branch;
	bool gensusy__genpsidx_isLoaded;
	vector<int> *gensusy_status_;
	TBranch *gensusy_status_branch;
	bool gensusy_status_isLoaded;
	vector<bool> *gensusy_fromHardProcessDecayed_;
	TBranch *gensusy_fromHardProcessDecayed_branch;
	bool gensusy_fromHardProcessDecayed_isLoaded;
	vector<bool> *gensusy_fromHardProcessFinalState_;
	TBranch *gensusy_fromHardProcessFinalState_branch;
	bool gensusy_fromHardProcessFinalState_isLoaded;
	vector<bool> *gensusy_isHardProcess_;
	TBranch *gensusy_isHardProcess_branch;
	bool gensusy_isHardProcess_isLoaded;
	vector<bool> *gensusy_isLastCopy_;
	TBranch *gensusy_isLastCopy_branch;
	bool gensusy_isLastCopy_isLoaded;
	vector<int> *gensusy_gentaudecay_;
	TBranch *gensusy_gentaudecay_branch;
	bool gensusy_gentaudecay_isLoaded;
	int	gen_nfromtsusy__;
	TBranch *gen_nfromtsusy__branch;
	bool gen_nfromtsusy__isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gensusy_motherp4_;
	TBranch *gensusy_motherp4_branch;
	bool gensusy_motherp4_isLoaded;
	vector<int> *gensusy_motherid_;
	TBranch *gensusy_motherid_branch;
	bool gensusy_motherid_isLoaded;
	vector<int> *gensusy_motheridx_;
	TBranch *gensusy_motheridx_branch;
	bool gensusy_motheridx_isLoaded;
	vector<int> *gensusy_motherstatus_;
	TBranch *gensusy_motherstatus_branch;
	bool gensusy_motherstatus_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gensusy_gmotherp4_;
	TBranch *gensusy_gmotherp4_branch;
	bool gensusy_gmotherp4_isLoaded;
	vector<int> *gensusy_gmotherid_;
	TBranch *gensusy_gmotherid_branch;
	bool gensusy_gmotherid_isLoaded;
	vector<int> *gensusy_gmotheridx_;
	TBranch *gensusy_gmotheridx_branch;
	bool gensusy_gmotheridx_isLoaded;
	vector<int> *gensusy_gmotherstatus_;
	TBranch *gensusy_gmotherstatus_branch;
	bool gensusy_gmotherstatus_isLoaded;
	vector<TString> *tau_IDnames_;
	TBranch *tau_IDnames_branch;
	bool tau_IDnames_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *tau_leadtrack_p4_;
	TBranch *tau_leadtrack_p4_branch;
	bool tau_leadtrack_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *tau_leadneutral_p4_;
	TBranch *tau_leadneutral_p4_branch;
	bool tau_leadneutral_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *tau_p4_;
	TBranch *tau_p4_branch;
	bool tau_p4_isLoaded;
	vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > *tau_isocand_p4_;
	TBranch *tau_isocand_p4_branch;
	bool tau_isocand_p4_isLoaded;
	vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > *tau_sigcand_p4_;
	TBranch *tau_sigcand_p4_branch;
	bool tau_sigcand_p4_isLoaded;
	vector<vector<float> > *tau_ID_;
	TBranch *tau_ID_branch;
	bool tau_ID_isLoaded;
	vector<float> *tau_passID_;
	TBranch *tau_passID_branch;
	bool tau_passID_isLoaded;
	int	ngoodtaus_;
	TBranch *ngoodtaus_branch;
	bool ngoodtaus_isLoaded;
	vector<float> *tau_againstMuonTight_;
	TBranch *tau_againstMuonTight_branch;
	bool tau_againstMuonTight_isLoaded;
	vector<float> *tau_againstElectronLoose_;
	TBranch *tau_againstElectronLoose_branch;
	bool tau_againstElectronLoose_isLoaded;
	vector<bool> *tau_isVetoTau_;
	TBranch *tau_isVetoTau_branch;
	bool tau_isVetoTau_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *isoTracks_p4_;
	TBranch *isoTracks_p4_branch;
	bool isoTracks_p4_isLoaded;
	vector<int> *isoTracks_charge_;
	TBranch *isoTracks_charge_branch;
	bool isoTracks_charge_isLoaded;
	vector<float> *isoTracks_absIso_;
	TBranch *isoTracks_absIso_branch;
	bool isoTracks_absIso_isLoaded;
	vector<float> *isoTracks_dz_;
	TBranch *isoTracks_dz_branch;
	bool isoTracks_dz_isLoaded;
	vector<int> *isoTracks_pdgId_;
	TBranch *isoTracks_pdgId_branch;
	bool isoTracks_pdgId_isLoaded;
	vector<bool> *isoTracks_isVetoTrack_;
	TBranch *isoTracks_isVetoTrack_branch;
	bool isoTracks_isVetoTrack_isLoaded;
	vector<bool> *isoTracks_isVetoTrack_v2_;
	TBranch *isoTracks_isVetoTrack_v2_branch;
	bool isoTracks_isVetoTrack_v2_isLoaded;
	vector<bool> *isoTracks_isVetoTrack_v3_;
	TBranch *isoTracks_isVetoTrack_v3_branch;
	bool isoTracks_isVetoTrack_v3_isLoaded;
public: 
void Init(TTree *tree) {
	lep1_p4_branch = 0;
	if (tree->GetBranch("lep1_p4") != 0) {
		lep1_p4_branch = tree->GetBranch("lep1_p4");
		if (lep1_p4_branch) {lep1_p4_branch->SetAddress(&lep1_p4_);}
	}
	lep1_mcp4_branch = 0;
	if (tree->GetBranch("lep1_mcp4") != 0) {
		lep1_mcp4_branch = tree->GetBranch("lep1_mcp4");
		if (lep1_mcp4_branch) {lep1_mcp4_branch->SetAddress(&lep1_mcp4_);}
	}
	lep2_p4_branch = 0;
	if (tree->GetBranch("lep2_p4") != 0) {
		lep2_p4_branch = tree->GetBranch("lep2_p4");
		if (lep2_p4_branch) {lep2_p4_branch->SetAddress(&lep2_p4_);}
	}
	lep2_mcp4_branch = 0;
	if (tree->GetBranch("lep2_mcp4") != 0) {
		lep2_mcp4_branch = tree->GetBranch("lep2_mcp4");
		if (lep2_mcp4_branch) {lep2_mcp4_branch->SetAddress(&lep2_mcp4_);}
	}
	ph_p4_branch = 0;
	if (tree->GetBranch("ph_p4") != 0) {
		ph_p4_branch = tree->GetBranch("ph_p4");
		if (ph_p4_branch) {ph_p4_branch->SetAddress(&ph_p4_);}
	}
	ph_mcp4_branch = 0;
	if (tree->GetBranch("ph_mcp4") != 0) {
		ph_mcp4_branch = tree->GetBranch("ph_mcp4");
		if (ph_mcp4_branch) {ph_mcp4_branch->SetAddress(&ph_mcp4_);}
	}
	ak4pfjets_p4_branch = 0;
	if (tree->GetBranch("ak4pfjets_p4") != 0) {
		ak4pfjets_p4_branch = tree->GetBranch("ak4pfjets_p4");
		if (ak4pfjets_p4_branch) {ak4pfjets_p4_branch->SetAddress(&ak4pfjets_p4_);}
	}
	ak4pfjets_leadMEDbjet_p4_branch = 0;
	if (tree->GetBranch("ak4pfjets_leadMEDbjet_p4") != 0) {
		ak4pfjets_leadMEDbjet_p4_branch = tree->GetBranch("ak4pfjets_leadMEDbjet_p4");
		if (ak4pfjets_leadMEDbjet_p4_branch) {ak4pfjets_leadMEDbjet_p4_branch->SetAddress(&ak4pfjets_leadMEDbjet_p4_);}
	}
	ak4pfjets_leadbtag_p4_branch = 0;
	if (tree->GetBranch("ak4pfjets_leadbtag_p4") != 0) {
		ak4pfjets_leadbtag_p4_branch = tree->GetBranch("ak4pfjets_leadbtag_p4");
		if (ak4pfjets_leadbtag_p4_branch) {ak4pfjets_leadbtag_p4_branch->SetAddress(&ak4pfjets_leadbtag_p4_);}
	}
	ak4genjets_p4_branch = 0;
	if (tree->GetBranch("ak4genjets_p4") != 0) {
		ak4genjets_p4_branch = tree->GetBranch("ak4genjets_p4");
		if (ak4genjets_p4_branch) {ak4genjets_p4_branch->SetAddress(&ak4genjets_p4_);}
	}
	genleps_p4_branch = 0;
	if (tree->GetBranch("genleps_p4") != 0) {
		genleps_p4_branch = tree->GetBranch("genleps_p4");
		if (genleps_p4_branch) {genleps_p4_branch->SetAddress(&genleps_p4_);}
	}
	genleps_motherp4_branch = 0;
	if (tree->GetBranch("genleps_motherp4") != 0) {
		genleps_motherp4_branch = tree->GetBranch("genleps_motherp4");
		if (genleps_motherp4_branch) {genleps_motherp4_branch->SetAddress(&genleps_motherp4_);}
	}
	genleps_gmotherp4_branch = 0;
	if (tree->GetBranch("genleps_gmotherp4") != 0) {
		genleps_gmotherp4_branch = tree->GetBranch("genleps_gmotherp4");
		if (genleps_gmotherp4_branch) {genleps_gmotherp4_branch->SetAddress(&genleps_gmotherp4_);}
	}
	gennus_p4_branch = 0;
	if (tree->GetBranch("gennus_p4") != 0) {
		gennus_p4_branch = tree->GetBranch("gennus_p4");
		if (gennus_p4_branch) {gennus_p4_branch->SetAddress(&gennus_p4_);}
	}
	gennus_motherp4_branch = 0;
	if (tree->GetBranch("gennus_motherp4") != 0) {
		gennus_motherp4_branch = tree->GetBranch("gennus_motherp4");
		if (gennus_motherp4_branch) {gennus_motherp4_branch->SetAddress(&gennus_motherp4_);}
	}
	gennus_gmotherp4_branch = 0;
	if (tree->GetBranch("gennus_gmotherp4") != 0) {
		gennus_gmotherp4_branch = tree->GetBranch("gennus_gmotherp4");
		if (gennus_gmotherp4_branch) {gennus_gmotherp4_branch->SetAddress(&gennus_gmotherp4_);}
	}
	genqs_p4_branch = 0;
	if (tree->GetBranch("genqs_p4") != 0) {
		genqs_p4_branch = tree->GetBranch("genqs_p4");
		if (genqs_p4_branch) {genqs_p4_branch->SetAddress(&genqs_p4_);}
	}
	genqs_motherp4_branch = 0;
	if (tree->GetBranch("genqs_motherp4") != 0) {
		genqs_motherp4_branch = tree->GetBranch("genqs_motherp4");
		if (genqs_motherp4_branch) {genqs_motherp4_branch->SetAddress(&genqs_motherp4_);}
	}
	genqs_gmotherp4_branch = 0;
	if (tree->GetBranch("genqs_gmotherp4") != 0) {
		genqs_gmotherp4_branch = tree->GetBranch("genqs_gmotherp4");
		if (genqs_gmotherp4_branch) {genqs_gmotherp4_branch->SetAddress(&genqs_gmotherp4_);}
	}
	genbosons_p4_branch = 0;
	if (tree->GetBranch("genbosons_p4") != 0) {
		genbosons_p4_branch = tree->GetBranch("genbosons_p4");
		if (genbosons_p4_branch) {genbosons_p4_branch->SetAddress(&genbosons_p4_);}
	}
	genbosons_motherp4_branch = 0;
	if (tree->GetBranch("genbosons_motherp4") != 0) {
		genbosons_motherp4_branch = tree->GetBranch("genbosons_motherp4");
		if (genbosons_motherp4_branch) {genbosons_motherp4_branch->SetAddress(&genbosons_motherp4_);}
	}
	genbosons_gmotherp4_branch = 0;
	if (tree->GetBranch("genbosons_gmotherp4") != 0) {
		genbosons_gmotherp4_branch = tree->GetBranch("genbosons_gmotherp4");
		if (genbosons_gmotherp4_branch) {genbosons_gmotherp4_branch->SetAddress(&genbosons_gmotherp4_);}
	}
	gensusy_p4_branch = 0;
	if (tree->GetBranch("gensusy_p4") != 0) {
		gensusy_p4_branch = tree->GetBranch("gensusy_p4");
		if (gensusy_p4_branch) {gensusy_p4_branch->SetAddress(&gensusy_p4_);}
	}
	gensusy_motherp4_branch = 0;
	if (tree->GetBranch("gensusy_motherp4") != 0) {
		gensusy_motherp4_branch = tree->GetBranch("gensusy_motherp4");
		if (gensusy_motherp4_branch) {gensusy_motherp4_branch->SetAddress(&gensusy_motherp4_);}
	}
	gensusy_gmotherp4_branch = 0;
	if (tree->GetBranch("gensusy_gmotherp4") != 0) {
		gensusy_gmotherp4_branch = tree->GetBranch("gensusy_gmotherp4");
		if (gensusy_gmotherp4_branch) {gensusy_gmotherp4_branch->SetAddress(&gensusy_gmotherp4_);}
	}
	tau_leadtrack_p4_branch = 0;
	if (tree->GetBranch("tau_leadtrack_p4") != 0) {
		tau_leadtrack_p4_branch = tree->GetBranch("tau_leadtrack_p4");
		if (tau_leadtrack_p4_branch) {tau_leadtrack_p4_branch->SetAddress(&tau_leadtrack_p4_);}
	}
	tau_leadneutral_p4_branch = 0;
	if (tree->GetBranch("tau_leadneutral_p4") != 0) {
		tau_leadneutral_p4_branch = tree->GetBranch("tau_leadneutral_p4");
		if (tau_leadneutral_p4_branch) {tau_leadneutral_p4_branch->SetAddress(&tau_leadneutral_p4_);}
	}
	tau_p4_branch = 0;
	if (tree->GetBranch("tau_p4") != 0) {
		tau_p4_branch = tree->GetBranch("tau_p4");
		if (tau_p4_branch) {tau_p4_branch->SetAddress(&tau_p4_);}
	}
	isoTracks_p4_branch = 0;
	if (tree->GetBranch("isoTracks_p4") != 0) {
		isoTracks_p4_branch = tree->GetBranch("isoTracks_p4");
		if (isoTracks_p4_branch) {isoTracks_p4_branch->SetAddress(&isoTracks_p4_);}
	}
  tree->SetMakeClass(1);
	run_branch = 0;
	if (tree->GetBranch("run") != 0) {
		run_branch = tree->GetBranch("run");
		if (run_branch) {run_branch->SetAddress(&run_);}
	}
	ls_branch = 0;
	if (tree->GetBranch("ls") != 0) {
		ls_branch = tree->GetBranch("ls");
		if (ls_branch) {ls_branch->SetAddress(&ls_);}
	}
	evt_branch = 0;
	if (tree->GetBranch("evt") != 0) {
		evt_branch = tree->GetBranch("evt");
		if (evt_branch) {evt_branch->SetAddress(&evt_);}
	}
	nvtxs_branch = 0;
	if (tree->GetBranch("nvtxs") != 0) {
		nvtxs_branch = tree->GetBranch("nvtxs");
		if (nvtxs_branch) {nvtxs_branch->SetAddress(&nvtxs_);}
	}
	pu_nvtxs_branch = 0;
	if (tree->GetBranch("pu_nvtxs") != 0) {
		pu_nvtxs_branch = tree->GetBranch("pu_nvtxs");
		if (pu_nvtxs_branch) {pu_nvtxs_branch->SetAddress(&pu_nvtxs_);}
	}
	pfmet_branch = 0;
	if (tree->GetBranch("pfmet") != 0) {
		pfmet_branch = tree->GetBranch("pfmet");
		if (pfmet_branch) {pfmet_branch->SetAddress(&pfmet_);}
	}
	pfmet_phi_branch = 0;
	if (tree->GetBranch("pfmet_phi") != 0) {
		pfmet_phi_branch = tree->GetBranch("pfmet_phi");
		if (pfmet_phi_branch) {pfmet_phi_branch->SetAddress(&pfmet_phi_);}
	}
	pfmet_rl_branch = 0;
	if (tree->GetBranch("pfmet_rl") != 0) {
		pfmet_rl_branch = tree->GetBranch("pfmet_rl");
		if (pfmet_rl_branch) {pfmet_rl_branch->SetAddress(&pfmet_rl_);}
	}
	pfmet_phi_rl_branch = 0;
	if (tree->GetBranch("pfmet_phi_rl") != 0) {
		pfmet_phi_rl_branch = tree->GetBranch("pfmet_phi_rl");
		if (pfmet_phi_rl_branch) {pfmet_phi_rl_branch->SetAddress(&pfmet_phi_rl_);}
	}
	scale1fb_branch = 0;
	if (tree->GetBranch("scale1fb") != 0) {
		scale1fb_branch = tree->GetBranch("scale1fb");
		if (scale1fb_branch) {scale1fb_branch->SetAddress(&scale1fb_);}
	}
	xsec_branch = 0;
	if (tree->GetBranch("xsec") != 0) {
		xsec_branch = tree->GetBranch("xsec");
		if (xsec_branch) {xsec_branch->SetAddress(&xsec_);}
	}
	xsec_uncert_branch = 0;
	if (tree->GetBranch("xsec_uncert") != 0) {
		xsec_uncert_branch = tree->GetBranch("xsec_uncert");
		if (xsec_uncert_branch) {xsec_uncert_branch->SetAddress(&xsec_uncert_);}
	}
	kfactor_branch = 0;
	if (tree->GetBranch("kfactor") != 0) {
		kfactor_branch = tree->GetBranch("kfactor");
		if (kfactor_branch) {kfactor_branch->SetAddress(&kfactor_);}
	}
	pu_ntrue_branch = 0;
	if (tree->GetBranch("pu_ntrue") != 0) {
		pu_ntrue_branch = tree->GetBranch("pu_ntrue");
		if (pu_ntrue_branch) {pu_ntrue_branch->SetAddress(&pu_ntrue_);}
	}
	ngoodleps_branch = 0;
	if (tree->GetBranch("ngoodleps") != 0) {
		ngoodleps_branch = tree->GetBranch("ngoodleps");
		if (ngoodleps_branch) {ngoodleps_branch->SetAddress(&ngoodleps_);}
	}
	nvetoleps_branch = 0;
	if (tree->GetBranch("nvetoleps") != 0) {
		nvetoleps_branch = tree->GetBranch("nvetoleps");
		if (nvetoleps_branch) {nvetoleps_branch->SetAddress(&nvetoleps_);}
	}
	is_data_branch = 0;
	if (tree->GetBranch("is_data") != 0) {
		is_data_branch = tree->GetBranch("is_data");
		if (is_data_branch) {is_data_branch->SetAddress(&is_data_);}
	}
	dataset_branch = 0;
	if (tree->GetBranch("dataset") != 0) {
		dataset_branch = tree->GetBranch("dataset");
		if (dataset_branch) {dataset_branch->SetAddress(&dataset_);}
	}
	filename_branch = 0;
	if (tree->GetBranch("filename") != 0) {
		filename_branch = tree->GetBranch("filename");
		if (filename_branch) {filename_branch->SetAddress(&filename_);}
	}
	cms3tag_branch = 0;
	if (tree->GetBranch("cms3tag") != 0) {
		cms3tag_branch = tree->GetBranch("cms3tag");
		if (cms3tag_branch) {cms3tag_branch->SetAddress(&cms3tag_);}
	}
	nEvents_branch = 0;
	if (tree->GetBranch("nEvents") != 0) {
		nEvents_branch = tree->GetBranch("nEvents");
		if (nEvents_branch) {nEvents_branch->SetAddress(&nEvents_);}
	}
	nEvents_goodvtx_branch = 0;
	if (tree->GetBranch("nEvents_goodvtx") != 0) {
		nEvents_goodvtx_branch = tree->GetBranch("nEvents_goodvtx");
		if (nEvents_goodvtx_branch) {nEvents_goodvtx_branch->SetAddress(&nEvents_goodvtx_);}
	}
	nEvents_MET30_branch = 0;
	if (tree->GetBranch("nEvents_MET30") != 0) {
		nEvents_MET30_branch = tree->GetBranch("nEvents_MET30");
		if (nEvents_MET30_branch) {nEvents_MET30_branch->SetAddress(&nEvents_MET30_);}
	}
	nEvents_1goodlep_branch = 0;
	if (tree->GetBranch("nEvents_1goodlep") != 0) {
		nEvents_1goodlep_branch = tree->GetBranch("nEvents_1goodlep");
		if (nEvents_1goodlep_branch) {nEvents_1goodlep_branch->SetAddress(&nEvents_1goodlep_);}
	}
	nEvents_2goodjets_branch = 0;
	if (tree->GetBranch("nEvents_2goodjets") != 0) {
		nEvents_2goodjets_branch = tree->GetBranch("nEvents_2goodjets");
		if (nEvents_2goodjets_branch) {nEvents_2goodjets_branch->SetAddress(&nEvents_2goodjets_);}
	}
	is0lep_branch = 0;
	if (tree->GetBranch("is0lep") != 0) {
		is0lep_branch = tree->GetBranch("is0lep");
		if (is0lep_branch) {is0lep_branch->SetAddress(&is0lep_);}
	}
	is1lep_branch = 0;
	if (tree->GetBranch("is1lep") != 0) {
		is1lep_branch = tree->GetBranch("is1lep");
		if (is1lep_branch) {is1lep_branch->SetAddress(&is1lep_);}
	}
	is2lep_branch = 0;
	if (tree->GetBranch("is2lep") != 0) {
		is2lep_branch = tree->GetBranch("is2lep");
		if (is2lep_branch) {is2lep_branch->SetAddress(&is2lep_);}
	}
	isZtoNuNu_branch = 0;
	if (tree->GetBranch("isZtoNuNu") != 0) {
		isZtoNuNu_branch = tree->GetBranch("isZtoNuNu");
		if (isZtoNuNu_branch) {isZtoNuNu_branch->SetAddress(&isZtoNuNu_);}
	}
	is1lepFromW_branch = 0;
	if (tree->GetBranch("is1lepFromW") != 0) {
		is1lepFromW_branch = tree->GetBranch("is1lepFromW");
		if (is1lepFromW_branch) {is1lepFromW_branch->SetAddress(&is1lepFromW_);}
	}
	is1lepFromTop_branch = 0;
	if (tree->GetBranch("is1lepFromTop") != 0) {
		is1lepFromTop_branch = tree->GetBranch("is1lepFromTop");
		if (is1lepFromTop_branch) {is1lepFromTop_branch->SetAddress(&is1lepFromTop_);}
	}
	MT2W_branch = 0;
	if (tree->GetBranch("MT2W") != 0) {
		MT2W_branch = tree->GetBranch("MT2W");
		if (MT2W_branch) {MT2W_branch->SetAddress(&MT2W_);}
	}
	MT2W_rl_branch = 0;
	if (tree->GetBranch("MT2W_rl") != 0) {
		MT2W_rl_branch = tree->GetBranch("MT2W_rl");
		if (MT2W_rl_branch) {MT2W_rl_branch->SetAddress(&MT2W_rl_);}
	}
	mindphi_met_j1_j2_branch = 0;
	if (tree->GetBranch("mindphi_met_j1_j2") != 0) {
		mindphi_met_j1_j2_branch = tree->GetBranch("mindphi_met_j1_j2");
		if (mindphi_met_j1_j2_branch) {mindphi_met_j1_j2_branch->SetAddress(&mindphi_met_j1_j2_);}
	}
	mindphi_met_j1_j2_rl_branch = 0;
	if (tree->GetBranch("mindphi_met_j1_j2_rl") != 0) {
		mindphi_met_j1_j2_rl_branch = tree->GetBranch("mindphi_met_j1_j2_rl");
		if (mindphi_met_j1_j2_rl_branch) {mindphi_met_j1_j2_rl_branch->SetAddress(&mindphi_met_j1_j2_rl_);}
	}
	mt_met_lep_branch = 0;
	if (tree->GetBranch("mt_met_lep") != 0) {
		mt_met_lep_branch = tree->GetBranch("mt_met_lep");
		if (mt_met_lep_branch) {mt_met_lep_branch->SetAddress(&mt_met_lep_);}
	}
	mt_met_lep_rl_branch = 0;
	if (tree->GetBranch("mt_met_lep_rl") != 0) {
		mt_met_lep_rl_branch = tree->GetBranch("mt_met_lep_rl");
		if (mt_met_lep_rl_branch) {mt_met_lep_rl_branch->SetAddress(&mt_met_lep_rl_);}
	}
	hadronic_top_chi2_branch = 0;
	if (tree->GetBranch("hadronic_top_chi2") != 0) {
		hadronic_top_chi2_branch = tree->GetBranch("hadronic_top_chi2");
		if (hadronic_top_chi2_branch) {hadronic_top_chi2_branch->SetAddress(&hadronic_top_chi2_);}
	}
	ak4pfjets_rho_branch = 0;
	if (tree->GetBranch("ak4pfjets_rho") != 0) {
		ak4pfjets_rho_branch = tree->GetBranch("ak4pfjets_rho");
		if (ak4pfjets_rho_branch) {ak4pfjets_rho_branch->SetAddress(&ak4pfjets_rho_);}
	}
	pdf_up_weight_branch = 0;
	if (tree->GetBranch("pdf_up_weight") != 0) {
		pdf_up_weight_branch = tree->GetBranch("pdf_up_weight");
		if (pdf_up_weight_branch) {pdf_up_weight_branch->SetAddress(&pdf_up_weight_);}
	}
	pdf_down_weight_branch = 0;
	if (tree->GetBranch("pdf_down_weight") != 0) {
		pdf_down_weight_branch = tree->GetBranch("pdf_down_weight");
		if (pdf_down_weight_branch) {pdf_down_weight_branch->SetAddress(&pdf_down_weight_);}
	}
	genweightsID_branch = 0;
	if (tree->GetBranch("genweightsID") != 0) {
		genweightsID_branch = tree->GetBranch("genweightsID");
		if (genweightsID_branch) {genweightsID_branch->SetAddress(&genweightsID_);}
	}
	genweights_branch = 0;
	if (tree->GetBranch("genweights") != 0) {
		genweights_branch = tree->GetBranch("genweights");
		if (genweights_branch) {genweights_branch->SetAddress(&genweights_);}
	}
	weight_btagsf_branch = 0;
	if (tree->GetBranch("weight_btagsf") != 0) {
		weight_btagsf_branch = tree->GetBranch("weight_btagsf");
		if (weight_btagsf_branch) {weight_btagsf_branch->SetAddress(&weight_btagsf_);}
	}
	weight_btagsf_heavy_UP_branch = 0;
	if (tree->GetBranch("weight_btagsf_heavy_UP") != 0) {
		weight_btagsf_heavy_UP_branch = tree->GetBranch("weight_btagsf_heavy_UP");
		if (weight_btagsf_heavy_UP_branch) {weight_btagsf_heavy_UP_branch->SetAddress(&weight_btagsf_heavy_UP_);}
	}
	weight_btagsf_light_UP_branch = 0;
	if (tree->GetBranch("weight_btagsf_light_UP") != 0) {
		weight_btagsf_light_UP_branch = tree->GetBranch("weight_btagsf_light_UP");
		if (weight_btagsf_light_UP_branch) {weight_btagsf_light_UP_branch->SetAddress(&weight_btagsf_light_UP_);}
	}
	weight_btagsf_heavy_DN_branch = 0;
	if (tree->GetBranch("weight_btagsf_heavy_DN") != 0) {
		weight_btagsf_heavy_DN_branch = tree->GetBranch("weight_btagsf_heavy_DN");
		if (weight_btagsf_heavy_DN_branch) {weight_btagsf_heavy_DN_branch->SetAddress(&weight_btagsf_heavy_DN_);}
	}
	weight_btagsf_light_DN_branch = 0;
	if (tree->GetBranch("weight_btagsf_light_DN") != 0) {
		weight_btagsf_light_DN_branch = tree->GetBranch("weight_btagsf_light_DN");
		if (weight_btagsf_light_DN_branch) {weight_btagsf_light_DN_branch->SetAddress(&weight_btagsf_light_DN_);}
	}
	weight_btagsf_fastsim_UP_branch = 0;
	if (tree->GetBranch("weight_btagsf_fastsim_UP") != 0) {
		weight_btagsf_fastsim_UP_branch = tree->GetBranch("weight_btagsf_fastsim_UP");
		if (weight_btagsf_fastsim_UP_branch) {weight_btagsf_fastsim_UP_branch->SetAddress(&weight_btagsf_fastsim_UP_);}
	}
	weight_btagsf_fastsim_DN_branch = 0;
	if (tree->GetBranch("weight_btagsf_fastsim_DN") != 0) {
		weight_btagsf_fastsim_DN_branch = tree->GetBranch("weight_btagsf_fastsim_DN");
		if (weight_btagsf_fastsim_DN_branch) {weight_btagsf_fastsim_DN_branch->SetAddress(&weight_btagsf_fastsim_DN_);}
	}
	weight_lepSF_branch = 0;
	if (tree->GetBranch("weight_lepSF") != 0) {
		weight_lepSF_branch = tree->GetBranch("weight_lepSF");
		if (weight_lepSF_branch) {weight_lepSF_branch->SetAddress(&weight_lepSF_);}
	}
	weight_lepSF_up_branch = 0;
	if (tree->GetBranch("weight_lepSF_up") != 0) {
		weight_lepSF_up_branch = tree->GetBranch("weight_lepSF_up");
		if (weight_lepSF_up_branch) {weight_lepSF_up_branch->SetAddress(&weight_lepSF_up_);}
	}
	weight_lepSF_down_branch = 0;
	if (tree->GetBranch("weight_lepSF_down") != 0) {
		weight_lepSF_down_branch = tree->GetBranch("weight_lepSF_down");
		if (weight_lepSF_down_branch) {weight_lepSF_down_branch->SetAddress(&weight_lepSF_down_);}
	}
	weight_vetoLepSF_branch = 0;
	if (tree->GetBranch("weight_vetoLepSF") != 0) {
		weight_vetoLepSF_branch = tree->GetBranch("weight_vetoLepSF");
		if (weight_vetoLepSF_branch) {weight_vetoLepSF_branch->SetAddress(&weight_vetoLepSF_);}
	}
	weight_vetoLepSF_up_branch = 0;
	if (tree->GetBranch("weight_vetoLepSF_up") != 0) {
		weight_vetoLepSF_up_branch = tree->GetBranch("weight_vetoLepSF_up");
		if (weight_vetoLepSF_up_branch) {weight_vetoLepSF_up_branch->SetAddress(&weight_vetoLepSF_up_);}
	}
	weight_vetoLepSF_down_branch = 0;
	if (tree->GetBranch("weight_vetoLepSF_down") != 0) {
		weight_vetoLepSF_down_branch = tree->GetBranch("weight_vetoLepSF_down");
		if (weight_vetoLepSF_down_branch) {weight_vetoLepSF_down_branch->SetAddress(&weight_vetoLepSF_down_);}
	}
	weight_lepSF_fastSim_branch = 0;
	if (tree->GetBranch("weight_lepSF_fastSim") != 0) {
		weight_lepSF_fastSim_branch = tree->GetBranch("weight_lepSF_fastSim");
		if (weight_lepSF_fastSim_branch) {weight_lepSF_fastSim_branch->SetAddress(&weight_lepSF_fastSim_);}
	}
	weight_lepSF_fastSim_up_branch = 0;
	if (tree->GetBranch("weight_lepSF_fastSim_up") != 0) {
		weight_lepSF_fastSim_up_branch = tree->GetBranch("weight_lepSF_fastSim_up");
		if (weight_lepSF_fastSim_up_branch) {weight_lepSF_fastSim_up_branch->SetAddress(&weight_lepSF_fastSim_up_);}
	}
	weight_lepSF_fastSim_down_branch = 0;
	if (tree->GetBranch("weight_lepSF_fastSim_down") != 0) {
		weight_lepSF_fastSim_down_branch = tree->GetBranch("weight_lepSF_fastSim_down");
		if (weight_lepSF_fastSim_down_branch) {weight_lepSF_fastSim_down_branch->SetAddress(&weight_lepSF_fastSim_down_);}
	}
	weight_ISR_branch = 0;
	if (tree->GetBranch("weight_ISR") != 0) {
		weight_ISR_branch = tree->GetBranch("weight_ISR");
		if (weight_ISR_branch) {weight_ISR_branch->SetAddress(&weight_ISR_);}
	}
	weight_ISRup_branch = 0;
	if (tree->GetBranch("weight_ISRup") != 0) {
		weight_ISRup_branch = tree->GetBranch("weight_ISRup");
		if (weight_ISRup_branch) {weight_ISRup_branch->SetAddress(&weight_ISRup_);}
	}
	weight_ISRdown_branch = 0;
	if (tree->GetBranch("weight_ISRdown") != 0) {
		weight_ISRdown_branch = tree->GetBranch("weight_ISRdown");
		if (weight_ISRdown_branch) {weight_ISRdown_branch->SetAddress(&weight_ISRdown_);}
	}
	weight_PU_branch = 0;
	if (tree->GetBranch("weight_PU") != 0) {
		weight_PU_branch = tree->GetBranch("weight_PU");
		if (weight_PU_branch) {weight_PU_branch->SetAddress(&weight_PU_);}
	}
	weight_PUup_branch = 0;
	if (tree->GetBranch("weight_PUup") != 0) {
		weight_PUup_branch = tree->GetBranch("weight_PUup");
		if (weight_PUup_branch) {weight_PUup_branch->SetAddress(&weight_PUup_);}
	}
	weight_PUdown_branch = 0;
	if (tree->GetBranch("weight_PUdown") != 0) {
		weight_PUdown_branch = tree->GetBranch("weight_PUdown");
		if (weight_PUdown_branch) {weight_PUdown_branch->SetAddress(&weight_PUdown_);}
	}
	sparms_names_branch = 0;
	if (tree->GetBranch("sparms_names") != 0) {
		sparms_names_branch = tree->GetBranch("sparms_names");
		if (sparms_names_branch) {sparms_names_branch->SetAddress(&sparms_names_);}
	}
	sparms_values_branch = 0;
	if (tree->GetBranch("sparms_values") != 0) {
		sparms_values_branch = tree->GetBranch("sparms_values");
		if (sparms_values_branch) {sparms_values_branch->SetAddress(&sparms_values_);}
	}
	sparms_subProcessId_branch = 0;
	if (tree->GetBranch("sparms_subProcessId") != 0) {
		sparms_subProcessId_branch = tree->GetBranch("sparms_subProcessId");
		if (sparms_subProcessId_branch) {sparms_subProcessId_branch->SetAddress(&sparms_subProcessId_);}
	}
	mass_lsp_branch = 0;
	if (tree->GetBranch("mass_lsp") != 0) {
		mass_lsp_branch = tree->GetBranch("mass_lsp");
		if (mass_lsp_branch) {mass_lsp_branch->SetAddress(&mass_lsp_);}
	}
	mass_chargino_branch = 0;
	if (tree->GetBranch("mass_chargino") != 0) {
		mass_chargino_branch = tree->GetBranch("mass_chargino");
		if (mass_chargino_branch) {mass_chargino_branch->SetAddress(&mass_chargino_);}
	}
	mass_stop_branch = 0;
	if (tree->GetBranch("mass_stop") != 0) {
		mass_stop_branch = tree->GetBranch("mass_stop");
		if (mass_stop_branch) {mass_stop_branch->SetAddress(&mass_stop_);}
	}
	mass_gluino_branch = 0;
	if (tree->GetBranch("mass_gluino") != 0) {
		mass_gluino_branch = tree->GetBranch("mass_gluino");
		if (mass_gluino_branch) {mass_gluino_branch->SetAddress(&mass_gluino_);}
	}
	genmet_branch = 0;
	if (tree->GetBranch("genmet") != 0) {
		genmet_branch = tree->GetBranch("genmet");
		if (genmet_branch) {genmet_branch->SetAddress(&genmet_);}
	}
	genmet_phi_branch = 0;
	if (tree->GetBranch("genmet_phi") != 0) {
		genmet_phi_branch = tree->GetBranch("genmet_phi");
		if (genmet_phi_branch) {genmet_phi_branch->SetAddress(&genmet_phi_);}
	}
	nupt_branch = 0;
	if (tree->GetBranch("nupt") != 0) {
		nupt_branch = tree->GetBranch("nupt");
		if (nupt_branch) {nupt_branch->SetAddress(&nupt_);}
	}
	genht_branch = 0;
	if (tree->GetBranch("genht") != 0) {
		genht_branch = tree->GetBranch("genht");
		if (genht_branch) {genht_branch->SetAddress(&genht_);}
	}
	PassTrackVeto_branch = 0;
	if (tree->GetBranch("PassTrackVeto") != 0) {
		PassTrackVeto_branch = tree->GetBranch("PassTrackVeto");
		if (PassTrackVeto_branch) {PassTrackVeto_branch->SetAddress(&PassTrackVeto_);}
	}
	PassTauVeto_branch = 0;
	if (tree->GetBranch("PassTauVeto") != 0) {
		PassTauVeto_branch = tree->GetBranch("PassTauVeto");
		if (PassTauVeto_branch) {PassTauVeto_branch->SetAddress(&PassTauVeto_);}
	}
	topness_branch = 0;
	if (tree->GetBranch("topness") != 0) {
		topness_branch = tree->GetBranch("topness");
		if (topness_branch) {topness_branch->SetAddress(&topness_);}
	}
	topnessMod_branch = 0;
	if (tree->GetBranch("topnessMod") != 0) {
		topnessMod_branch = tree->GetBranch("topnessMod");
		if (topnessMod_branch) {topnessMod_branch->SetAddress(&topnessMod_);}
	}
	topnessMod_rl_branch = 0;
	if (tree->GetBranch("topnessMod_rl") != 0) {
		topnessMod_rl_branch = tree->GetBranch("topnessMod_rl");
		if (topnessMod_rl_branch) {topnessMod_rl_branch->SetAddress(&topnessMod_rl_);}
	}
	Mlb_closestb_branch = 0;
	if (tree->GetBranch("Mlb_closestb") != 0) {
		Mlb_closestb_branch = tree->GetBranch("Mlb_closestb");
		if (Mlb_closestb_branch) {Mlb_closestb_branch->SetAddress(&Mlb_closestb_);}
	}
	HLT_SingleEl_branch = 0;
	if (tree->GetBranch("HLT_SingleEl") != 0) {
		HLT_SingleEl_branch = tree->GetBranch("HLT_SingleEl");
		if (HLT_SingleEl_branch) {HLT_SingleEl_branch->SetAddress(&HLT_SingleEl_);}
	}
	HLT_SingleMu_branch = 0;
	if (tree->GetBranch("HLT_SingleMu") != 0) {
		HLT_SingleMu_branch = tree->GetBranch("HLT_SingleMu");
		if (HLT_SingleMu_branch) {HLT_SingleMu_branch->SetAddress(&HLT_SingleMu_);}
	}
	HLT_MET_branch = 0;
	if (tree->GetBranch("HLT_MET") != 0) {
		HLT_MET_branch = tree->GetBranch("HLT_MET");
		if (HLT_MET_branch) {HLT_MET_branch->SetAddress(&HLT_MET_);}
	}
	HLT_MET100_MHT100_branch = 0;
	if (tree->GetBranch("HLT_MET100_MHT100") != 0) {
		HLT_MET100_MHT100_branch = tree->GetBranch("HLT_MET100_MHT100");
		if (HLT_MET100_MHT100_branch) {HLT_MET100_MHT100_branch->SetAddress(&HLT_MET100_MHT100_);}
	}
	HLT_DiEl_branch = 0;
	if (tree->GetBranch("HLT_DiEl") != 0) {
		HLT_DiEl_branch = tree->GetBranch("HLT_DiEl");
		if (HLT_DiEl_branch) {HLT_DiEl_branch->SetAddress(&HLT_DiEl_);}
	}
	HLT_DiMu_branch = 0;
	if (tree->GetBranch("HLT_DiMu") != 0) {
		HLT_DiMu_branch = tree->GetBranch("HLT_DiMu");
		if (HLT_DiMu_branch) {HLT_DiMu_branch->SetAddress(&HLT_DiMu_);}
	}
	HLT_MuE_branch = 0;
	if (tree->GetBranch("HLT_MuE") != 0) {
		HLT_MuE_branch = tree->GetBranch("HLT_MuE");
		if (HLT_MuE_branch) {HLT_MuE_branch->SetAddress(&HLT_MuE_);}
	}
	HLT_Photon90_CaloIdL_PFHT500_branch = 0;
	if (tree->GetBranch("HLT_Photon90_CaloIdL_PFHT500") != 0) {
		HLT_Photon90_CaloIdL_PFHT500_branch = tree->GetBranch("HLT_Photon90_CaloIdL_PFHT500");
		if (HLT_Photon90_CaloIdL_PFHT500_branch) {HLT_Photon90_CaloIdL_PFHT500_branch->SetAddress(&HLT_Photon90_CaloIdL_PFHT500_);}
	}
	HLT_Photon22_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon22_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon22_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon22_R9Id90_HE10_IsoM");
		if (HLT_Photon22_R9Id90_HE10_IsoM_branch) {HLT_Photon22_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon22_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon30_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon30_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon30_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon30_R9Id90_HE10_IsoM");
		if (HLT_Photon30_R9Id90_HE10_IsoM_branch) {HLT_Photon30_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon30_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon36_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon36_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon36_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon36_R9Id90_HE10_IsoM");
		if (HLT_Photon36_R9Id90_HE10_IsoM_branch) {HLT_Photon36_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon36_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon50_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon50_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon50_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon50_R9Id90_HE10_IsoM");
		if (HLT_Photon50_R9Id90_HE10_IsoM_branch) {HLT_Photon50_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon50_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon75_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon75_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon75_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon75_R9Id90_HE10_IsoM");
		if (HLT_Photon75_R9Id90_HE10_IsoM_branch) {HLT_Photon75_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon75_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon90_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon90_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon90_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon90_R9Id90_HE10_IsoM");
		if (HLT_Photon90_R9Id90_HE10_IsoM_branch) {HLT_Photon90_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon90_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon120_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon120_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon120_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon120_R9Id90_HE10_IsoM");
		if (HLT_Photon120_R9Id90_HE10_IsoM_branch) {HLT_Photon120_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon120_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon165_R9Id90_HE10_IsoM_branch = 0;
	if (tree->GetBranch("HLT_Photon165_R9Id90_HE10_IsoM") != 0) {
		HLT_Photon165_R9Id90_HE10_IsoM_branch = tree->GetBranch("HLT_Photon165_R9Id90_HE10_IsoM");
		if (HLT_Photon165_R9Id90_HE10_IsoM_branch) {HLT_Photon165_R9Id90_HE10_IsoM_branch->SetAddress(&HLT_Photon165_R9Id90_HE10_IsoM_);}
	}
	HLT_Photon175_branch = 0;
	if (tree->GetBranch("HLT_Photon175") != 0) {
		HLT_Photon175_branch = tree->GetBranch("HLT_Photon175");
		if (HLT_Photon175_branch) {HLT_Photon175_branch->SetAddress(&HLT_Photon175_);}
	}
	HLT_Photon165_HE10_branch = 0;
	if (tree->GetBranch("HLT_Photon165_HE10") != 0) {
		HLT_Photon165_HE10_branch = tree->GetBranch("HLT_Photon165_HE10");
		if (HLT_Photon165_HE10_branch) {HLT_Photon165_HE10_branch->SetAddress(&HLT_Photon165_HE10_);}
	}
	nPhotons_branch = 0;
	if (tree->GetBranch("nPhotons") != 0) {
		nPhotons_branch = tree->GetBranch("nPhotons");
		if (nPhotons_branch) {nPhotons_branch->SetAddress(&nPhotons_);}
	}
	ph_ngoodjets_branch = 0;
	if (tree->GetBranch("ph_ngoodjets") != 0) {
		ph_ngoodjets_branch = tree->GetBranch("ph_ngoodjets");
		if (ph_ngoodjets_branch) {ph_ngoodjets_branch->SetAddress(&ph_ngoodjets_);}
	}
	ph_ngoodbtags_branch = 0;
	if (tree->GetBranch("ph_ngoodbtags") != 0) {
		ph_ngoodbtags_branch = tree->GetBranch("ph_ngoodbtags");
		if (ph_ngoodbtags_branch) {ph_ngoodbtags_branch->SetAddress(&ph_ngoodbtags_);}
	}
	filt_met_branch = 0;
	if (tree->GetBranch("filt_met") != 0) {
		filt_met_branch = tree->GetBranch("filt_met");
		if (filt_met_branch) {filt_met_branch->SetAddress(&filt_met_);}
	}
	hardgenpt_branch = 0;
	if (tree->GetBranch("hardgenpt") != 0) {
		hardgenpt_branch = tree->GetBranch("hardgenpt");
		if (hardgenpt_branch) {hardgenpt_branch->SetAddress(&hardgenpt_);}
	}
	filt_badChargedCandidateFilter_branch = 0;
	if (tree->GetBranch("filt_badChargedCandidateFilter") != 0) {
		filt_badChargedCandidateFilter_branch = tree->GetBranch("filt_badChargedCandidateFilter");
		if (filt_badChargedCandidateFilter_branch) {filt_badChargedCandidateFilter_branch->SetAddress(&filt_badChargedCandidateFilter_);}
	}
	filt_badMuonFilter_branch = 0;
	if (tree->GetBranch("filt_badMuonFilter") != 0) {
		filt_badMuonFilter_branch = tree->GetBranch("filt_badMuonFilter");
		if (filt_badMuonFilter_branch) {filt_badMuonFilter_branch->SetAddress(&filt_badMuonFilter_);}
	}
	calomet_branch = 0;
	if (tree->GetBranch("calomet") != 0) {
		calomet_branch = tree->GetBranch("calomet");
		if (calomet_branch) {calomet_branch->SetAddress(&calomet_);}
	}
	calomet_phi_branch = 0;
	if (tree->GetBranch("calomet_phi") != 0) {
		calomet_phi_branch = tree->GetBranch("calomet_phi");
		if (calomet_phi_branch) {calomet_phi_branch->SetAddress(&calomet_phi_);}
	}
	lep1_pdgid_branch = 0;
	if (tree->GetBranch("lep1_pdgid") != 0) {
		lep1_pdgid_branch = tree->GetBranch("lep1_pdgid");
		if (lep1_pdgid_branch) {lep1_pdgid_branch->SetAddress(&lep1_pdgid_);}
	}
	lep1_production_type_branch = 0;
	if (tree->GetBranch("lep1_production_type") != 0) {
		lep1_production_type_branch = tree->GetBranch("lep1_production_type");
		if (lep1_production_type_branch) {lep1_production_type_branch->SetAddress(&lep1_production_type_);}
	}
	lep1_MiniIso_branch = 0;
	if (tree->GetBranch("lep1_MiniIso") != 0) {
		lep1_MiniIso_branch = tree->GetBranch("lep1_MiniIso");
		if (lep1_MiniIso_branch) {lep1_MiniIso_branch->SetAddress(&lep1_MiniIso_);}
	}
	lep1_relIso_branch = 0;
	if (tree->GetBranch("lep1_relIso") != 0) {
		lep1_relIso_branch = tree->GetBranch("lep1_relIso");
		if (lep1_relIso_branch) {lep1_relIso_branch->SetAddress(&lep1_relIso_);}
	}
	lep1_passLooseID_branch = 0;
	if (tree->GetBranch("lep1_passLooseID") != 0) {
		lep1_passLooseID_branch = tree->GetBranch("lep1_passLooseID");
		if (lep1_passLooseID_branch) {lep1_passLooseID_branch->SetAddress(&lep1_passLooseID_);}
	}
	lep1_passMediumID_branch = 0;
	if (tree->GetBranch("lep1_passMediumID") != 0) {
		lep1_passMediumID_branch = tree->GetBranch("lep1_passMediumID");
		if (lep1_passMediumID_branch) {lep1_passMediumID_branch->SetAddress(&lep1_passMediumID_);}
	}
	lep1_passTightID_branch = 0;
	if (tree->GetBranch("lep1_passTightID") != 0) {
		lep1_passTightID_branch = tree->GetBranch("lep1_passTightID");
		if (lep1_passTightID_branch) {lep1_passTightID_branch->SetAddress(&lep1_passTightID_);}
	}
	lep1_passVeto_branch = 0;
	if (tree->GetBranch("lep1_passVeto") != 0) {
		lep1_passVeto_branch = tree->GetBranch("lep1_passVeto");
		if (lep1_passVeto_branch) {lep1_passVeto_branch->SetAddress(&lep1_passVeto_);}
	}
	lep1_mc_motherid_branch = 0;
	if (tree->GetBranch("lep1_mc_motherid") != 0) {
		lep1_mc_motherid_branch = tree->GetBranch("lep1_mc_motherid");
		if (lep1_mc_motherid_branch) {lep1_mc_motherid_branch->SetAddress(&lep1_mc_motherid_);}
	}
	lep2_pdgid_branch = 0;
	if (tree->GetBranch("lep2_pdgid") != 0) {
		lep2_pdgid_branch = tree->GetBranch("lep2_pdgid");
		if (lep2_pdgid_branch) {lep2_pdgid_branch->SetAddress(&lep2_pdgid_);}
	}
	lep2_production_type_branch = 0;
	if (tree->GetBranch("lep2_production_type") != 0) {
		lep2_production_type_branch = tree->GetBranch("lep2_production_type");
		if (lep2_production_type_branch) {lep2_production_type_branch->SetAddress(&lep2_production_type_);}
	}
	lep2_MiniIso_branch = 0;
	if (tree->GetBranch("lep2_MiniIso") != 0) {
		lep2_MiniIso_branch = tree->GetBranch("lep2_MiniIso");
		if (lep2_MiniIso_branch) {lep2_MiniIso_branch->SetAddress(&lep2_MiniIso_);}
	}
	lep2_relIso_branch = 0;
	if (tree->GetBranch("lep2_relIso") != 0) {
		lep2_relIso_branch = tree->GetBranch("lep2_relIso");
		if (lep2_relIso_branch) {lep2_relIso_branch->SetAddress(&lep2_relIso_);}
	}
	lep2_passLooseID_branch = 0;
	if (tree->GetBranch("lep2_passLooseID") != 0) {
		lep2_passLooseID_branch = tree->GetBranch("lep2_passLooseID");
		if (lep2_passLooseID_branch) {lep2_passLooseID_branch->SetAddress(&lep2_passLooseID_);}
	}
	lep2_passMediumID_branch = 0;
	if (tree->GetBranch("lep2_passMediumID") != 0) {
		lep2_passMediumID_branch = tree->GetBranch("lep2_passMediumID");
		if (lep2_passMediumID_branch) {lep2_passMediumID_branch->SetAddress(&lep2_passMediumID_);}
	}
	lep2_passTightID_branch = 0;
	if (tree->GetBranch("lep2_passTightID") != 0) {
		lep2_passTightID_branch = tree->GetBranch("lep2_passTightID");
		if (lep2_passTightID_branch) {lep2_passTightID_branch->SetAddress(&lep2_passTightID_);}
	}
	lep2_passVeto_branch = 0;
	if (tree->GetBranch("lep2_passVeto") != 0) {
		lep2_passVeto_branch = tree->GetBranch("lep2_passVeto");
		if (lep2_passVeto_branch) {lep2_passVeto_branch->SetAddress(&lep2_passVeto_);}
	}
	lep2_mc_motherid_branch = 0;
	if (tree->GetBranch("lep2_mc_motherid") != 0) {
		lep2_mc_motherid_branch = tree->GetBranch("lep2_mc_motherid");
		if (lep2_mc_motherid_branch) {lep2_mc_motherid_branch->SetAddress(&lep2_mc_motherid_);}
	}
	ph_sigmaIEtaEta_fill5x5_branch = 0;
	if (tree->GetBranch("ph_sigmaIEtaEta_fill5x5") != 0) {
		ph_sigmaIEtaEta_fill5x5_branch = tree->GetBranch("ph_sigmaIEtaEta_fill5x5");
		if (ph_sigmaIEtaEta_fill5x5_branch) {ph_sigmaIEtaEta_fill5x5_branch->SetAddress(&ph_sigmaIEtaEta_fill5x5_);}
	}
	ph_hOverE_branch = 0;
	if (tree->GetBranch("ph_hOverE") != 0) {
		ph_hOverE_branch = tree->GetBranch("ph_hOverE");
		if (ph_hOverE_branch) {ph_hOverE_branch->SetAddress(&ph_hOverE_);}
	}
	ph_r9_branch = 0;
	if (tree->GetBranch("ph_r9") != 0) {
		ph_r9_branch = tree->GetBranch("ph_r9");
		if (ph_r9_branch) {ph_r9_branch->SetAddress(&ph_r9_);}
	}
	ph_chiso_branch = 0;
	if (tree->GetBranch("ph_chiso") != 0) {
		ph_chiso_branch = tree->GetBranch("ph_chiso");
		if (ph_chiso_branch) {ph_chiso_branch->SetAddress(&ph_chiso_);}
	}
	ph_nhiso_branch = 0;
	if (tree->GetBranch("ph_nhiso") != 0) {
		ph_nhiso_branch = tree->GetBranch("ph_nhiso");
		if (ph_nhiso_branch) {ph_nhiso_branch->SetAddress(&ph_nhiso_);}
	}
	ph_phiso_branch = 0;
	if (tree->GetBranch("ph_phiso") != 0) {
		ph_phiso_branch = tree->GetBranch("ph_phiso");
		if (ph_phiso_branch) {ph_phiso_branch->SetAddress(&ph_phiso_);}
	}
	ph_idCutBased_branch = 0;
	if (tree->GetBranch("ph_idCutBased") != 0) {
		ph_idCutBased_branch = tree->GetBranch("ph_idCutBased");
		if (ph_idCutBased_branch) {ph_idCutBased_branch->SetAddress(&ph_idCutBased_);}
	}
	ph_overlapJetId_branch = 0;
	if (tree->GetBranch("ph_overlapJetId") != 0) {
		ph_overlapJetId_branch = tree->GetBranch("ph_overlapJetId");
		if (ph_overlapJetId_branch) {ph_overlapJetId_branch->SetAddress(&ph_overlapJetId_);}
	}
	ph_pt_branch = 0;
	if (tree->GetBranch("ph_pt") != 0) {
		ph_pt_branch = tree->GetBranch("ph_pt");
		if (ph_pt_branch) {ph_pt_branch->SetAddress(&ph_pt_);}
	}
	ph_eta_branch = 0;
	if (tree->GetBranch("ph_eta") != 0) {
		ph_eta_branch = tree->GetBranch("ph_eta");
		if (ph_eta_branch) {ph_eta_branch->SetAddress(&ph_eta_);}
	}
	ph_phi_branch = 0;
	if (tree->GetBranch("ph_phi") != 0) {
		ph_phi_branch = tree->GetBranch("ph_phi");
		if (ph_phi_branch) {ph_phi_branch->SetAddress(&ph_phi_);}
	}
	ph_mass_branch = 0;
	if (tree->GetBranch("ph_mass") != 0) {
		ph_mass_branch = tree->GetBranch("ph_mass");
		if (ph_mass_branch) {ph_mass_branch->SetAddress(&ph_mass_);}
	}
	ph_mcMatchId_branch = 0;
	if (tree->GetBranch("ph_mcMatchId") != 0) {
		ph_mcMatchId_branch = tree->GetBranch("ph_mcMatchId");
		if (ph_mcMatchId_branch) {ph_mcMatchId_branch->SetAddress(&ph_mcMatchId_);}
	}
	ph_genIso04_branch = 0;
	if (tree->GetBranch("ph_genIso04") != 0) {
		ph_genIso04_branch = tree->GetBranch("ph_genIso04");
		if (ph_genIso04_branch) {ph_genIso04_branch->SetAddress(&ph_genIso04_);}
	}
	ph_drMinParton_branch = 0;
	if (tree->GetBranch("ph_drMinParton") != 0) {
		ph_drMinParton_branch = tree->GetBranch("ph_drMinParton");
		if (ph_drMinParton_branch) {ph_drMinParton_branch->SetAddress(&ph_drMinParton_);}
	}
	ngoodjets_branch = 0;
	if (tree->GetBranch("ngoodjets") != 0) {
		ngoodjets_branch = tree->GetBranch("ngoodjets");
		if (ngoodjets_branch) {ngoodjets_branch->SetAddress(&ngoodjets_);}
	}
	ngoodbtags_branch = 0;
	if (tree->GetBranch("ngoodbtags") != 0) {
		ngoodbtags_branch = tree->GetBranch("ngoodbtags");
		if (ngoodbtags_branch) {ngoodbtags_branch->SetAddress(&ngoodbtags_);}
	}
	ak4_HT_branch = 0;
	if (tree->GetBranch("ak4_HT") != 0) {
		ak4_HT_branch = tree->GetBranch("ak4_HT");
		if (ak4_HT_branch) {ak4_HT_branch->SetAddress(&ak4_HT_);}
	}
	ak4_htratiom_branch = 0;
	if (tree->GetBranch("ak4_htratiom") != 0) {
		ak4_htratiom_branch = tree->GetBranch("ak4_htratiom");
		if (ak4_htratiom_branch) {ak4_htratiom_branch->SetAddress(&ak4_htratiom_);}
	}
	dphi_ak4pfjet_met_branch = 0;
	if (tree->GetBranch("dphi_ak4pfjet_met") != 0) {
		dphi_ak4pfjet_met_branch = tree->GetBranch("dphi_ak4pfjet_met");
		if (dphi_ak4pfjet_met_branch) {dphi_ak4pfjet_met_branch->SetAddress(&dphi_ak4pfjet_met_);}
	}
	ak4pfjets_passMEDbtag_branch = 0;
	if (tree->GetBranch("ak4pfjets_passMEDbtag") != 0) {
		ak4pfjets_passMEDbtag_branch = tree->GetBranch("ak4pfjets_passMEDbtag");
		if (ak4pfjets_passMEDbtag_branch) {ak4pfjets_passMEDbtag_branch->SetAddress(&ak4pfjets_passMEDbtag_);}
	}
	ak4pfjets_CSV_branch = 0;
	if (tree->GetBranch("ak4pfjets_CSV") != 0) {
		ak4pfjets_CSV_branch = tree->GetBranch("ak4pfjets_CSV");
		if (ak4pfjets_CSV_branch) {ak4pfjets_CSV_branch->SetAddress(&ak4pfjets_CSV_);}
	}
	ak4pfjets_mva_branch = 0;
	if (tree->GetBranch("ak4pfjets_mva") != 0) {
		ak4pfjets_mva_branch = tree->GetBranch("ak4pfjets_mva");
		if (ak4pfjets_mva_branch) {ak4pfjets_mva_branch->SetAddress(&ak4pfjets_mva_);}
	}
	ak4pfjets_parton_flavor_branch = 0;
	if (tree->GetBranch("ak4pfjets_parton_flavor") != 0) {
		ak4pfjets_parton_flavor_branch = tree->GetBranch("ak4pfjets_parton_flavor");
		if (ak4pfjets_parton_flavor_branch) {ak4pfjets_parton_flavor_branch->SetAddress(&ak4pfjets_parton_flavor_);}
	}
	ak4pfjets_hadron_flavor_branch = 0;
	if (tree->GetBranch("ak4pfjets_hadron_flavor") != 0) {
		ak4pfjets_hadron_flavor_branch = tree->GetBranch("ak4pfjets_hadron_flavor");
		if (ak4pfjets_hadron_flavor_branch) {ak4pfjets_hadron_flavor_branch->SetAddress(&ak4pfjets_hadron_flavor_);}
	}
	ak4pfjets_loose_puid_branch = 0;
	if (tree->GetBranch("ak4pfjets_loose_puid") != 0) {
		ak4pfjets_loose_puid_branch = tree->GetBranch("ak4pfjets_loose_puid");
		if (ak4pfjets_loose_puid_branch) {ak4pfjets_loose_puid_branch->SetAddress(&ak4pfjets_loose_puid_);}
	}
	ak4pfjets_loose_pfid_branch = 0;
	if (tree->GetBranch("ak4pfjets_loose_pfid") != 0) {
		ak4pfjets_loose_pfid_branch = tree->GetBranch("ak4pfjets_loose_pfid");
		if (ak4pfjets_loose_pfid_branch) {ak4pfjets_loose_pfid_branch->SetAddress(&ak4pfjets_loose_pfid_);}
	}
	genleps_isfromt_branch = 0;
	if (tree->GetBranch("genleps_isfromt") != 0) {
		genleps_isfromt_branch = tree->GetBranch("genleps_isfromt");
		if (genleps_isfromt_branch) {genleps_isfromt_branch->SetAddress(&genleps_isfromt_);}
	}
	genleps_id_branch = 0;
	if (tree->GetBranch("genleps_id") != 0) {
		genleps_id_branch = tree->GetBranch("genleps_id");
		if (genleps_id_branch) {genleps_id_branch->SetAddress(&genleps_id_);}
	}
	genleps__genpsidx_branch = 0;
	if (tree->GetBranch("genleps__genpsidx") != 0) {
		genleps__genpsidx_branch = tree->GetBranch("genleps__genpsidx");
		if (genleps__genpsidx_branch) {genleps__genpsidx_branch->SetAddress(&genleps__genpsidx_);}
	}
	genleps_status_branch = 0;
	if (tree->GetBranch("genleps_status") != 0) {
		genleps_status_branch = tree->GetBranch("genleps_status");
		if (genleps_status_branch) {genleps_status_branch->SetAddress(&genleps_status_);}
	}
	genleps_fromHardProcessDecayed_branch = 0;
	if (tree->GetBranch("genleps_fromHardProcessDecayed") != 0) {
		genleps_fromHardProcessDecayed_branch = tree->GetBranch("genleps_fromHardProcessDecayed");
		if (genleps_fromHardProcessDecayed_branch) {genleps_fromHardProcessDecayed_branch->SetAddress(&genleps_fromHardProcessDecayed_);}
	}
	genleps_fromHardProcessFinalState_branch = 0;
	if (tree->GetBranch("genleps_fromHardProcessFinalState") != 0) {
		genleps_fromHardProcessFinalState_branch = tree->GetBranch("genleps_fromHardProcessFinalState");
		if (genleps_fromHardProcessFinalState_branch) {genleps_fromHardProcessFinalState_branch->SetAddress(&genleps_fromHardProcessFinalState_);}
	}
	genleps_isHardProcess_branch = 0;
	if (tree->GetBranch("genleps_isHardProcess") != 0) {
		genleps_isHardProcess_branch = tree->GetBranch("genleps_isHardProcess");
		if (genleps_isHardProcess_branch) {genleps_isHardProcess_branch->SetAddress(&genleps_isHardProcess_);}
	}
	genleps_isLastCopy_branch = 0;
	if (tree->GetBranch("genleps_isLastCopy") != 0) {
		genleps_isLastCopy_branch = tree->GetBranch("genleps_isLastCopy");
		if (genleps_isLastCopy_branch) {genleps_isLastCopy_branch->SetAddress(&genleps_isLastCopy_);}
	}
	genleps_gentaudecay_branch = 0;
	if (tree->GetBranch("genleps_gentaudecay") != 0) {
		genleps_gentaudecay_branch = tree->GetBranch("genleps_gentaudecay");
		if (genleps_gentaudecay_branch) {genleps_gentaudecay_branch->SetAddress(&genleps_gentaudecay_);}
	}
	gen_nfromtleps__branch = 0;
	if (tree->GetBranch("gen_nfromtleps_") != 0) {
		gen_nfromtleps__branch = tree->GetBranch("gen_nfromtleps_");
		if (gen_nfromtleps__branch) {gen_nfromtleps__branch->SetAddress(&gen_nfromtleps__);}
	}
	genleps_motherid_branch = 0;
	if (tree->GetBranch("genleps_motherid") != 0) {
		genleps_motherid_branch = tree->GetBranch("genleps_motherid");
		if (genleps_motherid_branch) {genleps_motherid_branch->SetAddress(&genleps_motherid_);}
	}
	genleps_motheridx_branch = 0;
	if (tree->GetBranch("genleps_motheridx") != 0) {
		genleps_motheridx_branch = tree->GetBranch("genleps_motheridx");
		if (genleps_motheridx_branch) {genleps_motheridx_branch->SetAddress(&genleps_motheridx_);}
	}
	genleps_motherstatus_branch = 0;
	if (tree->GetBranch("genleps_motherstatus") != 0) {
		genleps_motherstatus_branch = tree->GetBranch("genleps_motherstatus");
		if (genleps_motherstatus_branch) {genleps_motherstatus_branch->SetAddress(&genleps_motherstatus_);}
	}
	genleps_gmotherid_branch = 0;
	if (tree->GetBranch("genleps_gmotherid") != 0) {
		genleps_gmotherid_branch = tree->GetBranch("genleps_gmotherid");
		if (genleps_gmotherid_branch) {genleps_gmotherid_branch->SetAddress(&genleps_gmotherid_);}
	}
	genleps_gmotheridx_branch = 0;
	if (tree->GetBranch("genleps_gmotheridx") != 0) {
		genleps_gmotheridx_branch = tree->GetBranch("genleps_gmotheridx");
		if (genleps_gmotheridx_branch) {genleps_gmotheridx_branch->SetAddress(&genleps_gmotheridx_);}
	}
	genleps_gmotherstatus_branch = 0;
	if (tree->GetBranch("genleps_gmotherstatus") != 0) {
		genleps_gmotherstatus_branch = tree->GetBranch("genleps_gmotherstatus");
		if (genleps_gmotherstatus_branch) {genleps_gmotherstatus_branch->SetAddress(&genleps_gmotherstatus_);}
	}
	gennus_isfromt_branch = 0;
	if (tree->GetBranch("gennus_isfromt") != 0) {
		gennus_isfromt_branch = tree->GetBranch("gennus_isfromt");
		if (gennus_isfromt_branch) {gennus_isfromt_branch->SetAddress(&gennus_isfromt_);}
	}
	gennus_id_branch = 0;
	if (tree->GetBranch("gennus_id") != 0) {
		gennus_id_branch = tree->GetBranch("gennus_id");
		if (gennus_id_branch) {gennus_id_branch->SetAddress(&gennus_id_);}
	}
	gennus__genpsidx_branch = 0;
	if (tree->GetBranch("gennus__genpsidx") != 0) {
		gennus__genpsidx_branch = tree->GetBranch("gennus__genpsidx");
		if (gennus__genpsidx_branch) {gennus__genpsidx_branch->SetAddress(&gennus__genpsidx_);}
	}
	gennus_status_branch = 0;
	if (tree->GetBranch("gennus_status") != 0) {
		gennus_status_branch = tree->GetBranch("gennus_status");
		if (gennus_status_branch) {gennus_status_branch->SetAddress(&gennus_status_);}
	}
	gennus_fromHardProcessDecayed_branch = 0;
	if (tree->GetBranch("gennus_fromHardProcessDecayed") != 0) {
		gennus_fromHardProcessDecayed_branch = tree->GetBranch("gennus_fromHardProcessDecayed");
		if (gennus_fromHardProcessDecayed_branch) {gennus_fromHardProcessDecayed_branch->SetAddress(&gennus_fromHardProcessDecayed_);}
	}
	gennus_fromHardProcessFinalState_branch = 0;
	if (tree->GetBranch("gennus_fromHardProcessFinalState") != 0) {
		gennus_fromHardProcessFinalState_branch = tree->GetBranch("gennus_fromHardProcessFinalState");
		if (gennus_fromHardProcessFinalState_branch) {gennus_fromHardProcessFinalState_branch->SetAddress(&gennus_fromHardProcessFinalState_);}
	}
	gennus_isHardProcess_branch = 0;
	if (tree->GetBranch("gennus_isHardProcess") != 0) {
		gennus_isHardProcess_branch = tree->GetBranch("gennus_isHardProcess");
		if (gennus_isHardProcess_branch) {gennus_isHardProcess_branch->SetAddress(&gennus_isHardProcess_);}
	}
	gennus_isLastCopy_branch = 0;
	if (tree->GetBranch("gennus_isLastCopy") != 0) {
		gennus_isLastCopy_branch = tree->GetBranch("gennus_isLastCopy");
		if (gennus_isLastCopy_branch) {gennus_isLastCopy_branch->SetAddress(&gennus_isLastCopy_);}
	}
	gennus_gentaudecay_branch = 0;
	if (tree->GetBranch("gennus_gentaudecay") != 0) {
		gennus_gentaudecay_branch = tree->GetBranch("gennus_gentaudecay");
		if (gennus_gentaudecay_branch) {gennus_gentaudecay_branch->SetAddress(&gennus_gentaudecay_);}
	}
	gen_nfromtnus__branch = 0;
	if (tree->GetBranch("gen_nfromtnus_") != 0) {
		gen_nfromtnus__branch = tree->GetBranch("gen_nfromtnus_");
		if (gen_nfromtnus__branch) {gen_nfromtnus__branch->SetAddress(&gen_nfromtnus__);}
	}
	gennus_motherid_branch = 0;
	if (tree->GetBranch("gennus_motherid") != 0) {
		gennus_motherid_branch = tree->GetBranch("gennus_motherid");
		if (gennus_motherid_branch) {gennus_motherid_branch->SetAddress(&gennus_motherid_);}
	}
	gennus_motheridx_branch = 0;
	if (tree->GetBranch("gennus_motheridx") != 0) {
		gennus_motheridx_branch = tree->GetBranch("gennus_motheridx");
		if (gennus_motheridx_branch) {gennus_motheridx_branch->SetAddress(&gennus_motheridx_);}
	}
	gennus_motherstatus_branch = 0;
	if (tree->GetBranch("gennus_motherstatus") != 0) {
		gennus_motherstatus_branch = tree->GetBranch("gennus_motherstatus");
		if (gennus_motherstatus_branch) {gennus_motherstatus_branch->SetAddress(&gennus_motherstatus_);}
	}
	gennus_gmotherid_branch = 0;
	if (tree->GetBranch("gennus_gmotherid") != 0) {
		gennus_gmotherid_branch = tree->GetBranch("gennus_gmotherid");
		if (gennus_gmotherid_branch) {gennus_gmotherid_branch->SetAddress(&gennus_gmotherid_);}
	}
	gennus_gmotheridx_branch = 0;
	if (tree->GetBranch("gennus_gmotheridx") != 0) {
		gennus_gmotheridx_branch = tree->GetBranch("gennus_gmotheridx");
		if (gennus_gmotheridx_branch) {gennus_gmotheridx_branch->SetAddress(&gennus_gmotheridx_);}
	}
	gennus_gmotherstatus_branch = 0;
	if (tree->GetBranch("gennus_gmotherstatus") != 0) {
		gennus_gmotherstatus_branch = tree->GetBranch("gennus_gmotherstatus");
		if (gennus_gmotherstatus_branch) {gennus_gmotherstatus_branch->SetAddress(&gennus_gmotherstatus_);}
	}
	genqs_isfromt_branch = 0;
	if (tree->GetBranch("genqs_isfromt") != 0) {
		genqs_isfromt_branch = tree->GetBranch("genqs_isfromt");
		if (genqs_isfromt_branch) {genqs_isfromt_branch->SetAddress(&genqs_isfromt_);}
	}
	genqs_id_branch = 0;
	if (tree->GetBranch("genqs_id") != 0) {
		genqs_id_branch = tree->GetBranch("genqs_id");
		if (genqs_id_branch) {genqs_id_branch->SetAddress(&genqs_id_);}
	}
	genqs__genpsidx_branch = 0;
	if (tree->GetBranch("genqs__genpsidx") != 0) {
		genqs__genpsidx_branch = tree->GetBranch("genqs__genpsidx");
		if (genqs__genpsidx_branch) {genqs__genpsidx_branch->SetAddress(&genqs__genpsidx_);}
	}
	genqs_status_branch = 0;
	if (tree->GetBranch("genqs_status") != 0) {
		genqs_status_branch = tree->GetBranch("genqs_status");
		if (genqs_status_branch) {genqs_status_branch->SetAddress(&genqs_status_);}
	}
	genqs_fromHardProcessDecayed_branch = 0;
	if (tree->GetBranch("genqs_fromHardProcessDecayed") != 0) {
		genqs_fromHardProcessDecayed_branch = tree->GetBranch("genqs_fromHardProcessDecayed");
		if (genqs_fromHardProcessDecayed_branch) {genqs_fromHardProcessDecayed_branch->SetAddress(&genqs_fromHardProcessDecayed_);}
	}
	genqs_fromHardProcessFinalState_branch = 0;
	if (tree->GetBranch("genqs_fromHardProcessFinalState") != 0) {
		genqs_fromHardProcessFinalState_branch = tree->GetBranch("genqs_fromHardProcessFinalState");
		if (genqs_fromHardProcessFinalState_branch) {genqs_fromHardProcessFinalState_branch->SetAddress(&genqs_fromHardProcessFinalState_);}
	}
	genqs_isHardProcess_branch = 0;
	if (tree->GetBranch("genqs_isHardProcess") != 0) {
		genqs_isHardProcess_branch = tree->GetBranch("genqs_isHardProcess");
		if (genqs_isHardProcess_branch) {genqs_isHardProcess_branch->SetAddress(&genqs_isHardProcess_);}
	}
	genqs_isLastCopy_branch = 0;
	if (tree->GetBranch("genqs_isLastCopy") != 0) {
		genqs_isLastCopy_branch = tree->GetBranch("genqs_isLastCopy");
		if (genqs_isLastCopy_branch) {genqs_isLastCopy_branch->SetAddress(&genqs_isLastCopy_);}
	}
	genqs_gentaudecay_branch = 0;
	if (tree->GetBranch("genqs_gentaudecay") != 0) {
		genqs_gentaudecay_branch = tree->GetBranch("genqs_gentaudecay");
		if (genqs_gentaudecay_branch) {genqs_gentaudecay_branch->SetAddress(&genqs_gentaudecay_);}
	}
	gen_nfromtqs__branch = 0;
	if (tree->GetBranch("gen_nfromtqs_") != 0) {
		gen_nfromtqs__branch = tree->GetBranch("gen_nfromtqs_");
		if (gen_nfromtqs__branch) {gen_nfromtqs__branch->SetAddress(&gen_nfromtqs__);}
	}
	genqs_motherid_branch = 0;
	if (tree->GetBranch("genqs_motherid") != 0) {
		genqs_motherid_branch = tree->GetBranch("genqs_motherid");
		if (genqs_motherid_branch) {genqs_motherid_branch->SetAddress(&genqs_motherid_);}
	}
	genqs_motheridx_branch = 0;
	if (tree->GetBranch("genqs_motheridx") != 0) {
		genqs_motheridx_branch = tree->GetBranch("genqs_motheridx");
		if (genqs_motheridx_branch) {genqs_motheridx_branch->SetAddress(&genqs_motheridx_);}
	}
	genqs_motherstatus_branch = 0;
	if (tree->GetBranch("genqs_motherstatus") != 0) {
		genqs_motherstatus_branch = tree->GetBranch("genqs_motherstatus");
		if (genqs_motherstatus_branch) {genqs_motherstatus_branch->SetAddress(&genqs_motherstatus_);}
	}
	genqs_gmotherid_branch = 0;
	if (tree->GetBranch("genqs_gmotherid") != 0) {
		genqs_gmotherid_branch = tree->GetBranch("genqs_gmotherid");
		if (genqs_gmotherid_branch) {genqs_gmotherid_branch->SetAddress(&genqs_gmotherid_);}
	}
	genqs_gmotheridx_branch = 0;
	if (tree->GetBranch("genqs_gmotheridx") != 0) {
		genqs_gmotheridx_branch = tree->GetBranch("genqs_gmotheridx");
		if (genqs_gmotheridx_branch) {genqs_gmotheridx_branch->SetAddress(&genqs_gmotheridx_);}
	}
	genqs_gmotherstatus_branch = 0;
	if (tree->GetBranch("genqs_gmotherstatus") != 0) {
		genqs_gmotherstatus_branch = tree->GetBranch("genqs_gmotherstatus");
		if (genqs_gmotherstatus_branch) {genqs_gmotherstatus_branch->SetAddress(&genqs_gmotherstatus_);}
	}
	genbosons_isfromt_branch = 0;
	if (tree->GetBranch("genbosons_isfromt") != 0) {
		genbosons_isfromt_branch = tree->GetBranch("genbosons_isfromt");
		if (genbosons_isfromt_branch) {genbosons_isfromt_branch->SetAddress(&genbosons_isfromt_);}
	}
	genbosons_id_branch = 0;
	if (tree->GetBranch("genbosons_id") != 0) {
		genbosons_id_branch = tree->GetBranch("genbosons_id");
		if (genbosons_id_branch) {genbosons_id_branch->SetAddress(&genbosons_id_);}
	}
	genbosons__genpsidx_branch = 0;
	if (tree->GetBranch("genbosons__genpsidx") != 0) {
		genbosons__genpsidx_branch = tree->GetBranch("genbosons__genpsidx");
		if (genbosons__genpsidx_branch) {genbosons__genpsidx_branch->SetAddress(&genbosons__genpsidx_);}
	}
	genbosons_status_branch = 0;
	if (tree->GetBranch("genbosons_status") != 0) {
		genbosons_status_branch = tree->GetBranch("genbosons_status");
		if (genbosons_status_branch) {genbosons_status_branch->SetAddress(&genbosons_status_);}
	}
	genbosons_fromHardProcessDecayed_branch = 0;
	if (tree->GetBranch("genbosons_fromHardProcessDecayed") != 0) {
		genbosons_fromHardProcessDecayed_branch = tree->GetBranch("genbosons_fromHardProcessDecayed");
		if (genbosons_fromHardProcessDecayed_branch) {genbosons_fromHardProcessDecayed_branch->SetAddress(&genbosons_fromHardProcessDecayed_);}
	}
	genbosons_fromHardProcessFinalState_branch = 0;
	if (tree->GetBranch("genbosons_fromHardProcessFinalState") != 0) {
		genbosons_fromHardProcessFinalState_branch = tree->GetBranch("genbosons_fromHardProcessFinalState");
		if (genbosons_fromHardProcessFinalState_branch) {genbosons_fromHardProcessFinalState_branch->SetAddress(&genbosons_fromHardProcessFinalState_);}
	}
	genbosons_isHardProcess_branch = 0;
	if (tree->GetBranch("genbosons_isHardProcess") != 0) {
		genbosons_isHardProcess_branch = tree->GetBranch("genbosons_isHardProcess");
		if (genbosons_isHardProcess_branch) {genbosons_isHardProcess_branch->SetAddress(&genbosons_isHardProcess_);}
	}
	genbosons_isLastCopy_branch = 0;
	if (tree->GetBranch("genbosons_isLastCopy") != 0) {
		genbosons_isLastCopy_branch = tree->GetBranch("genbosons_isLastCopy");
		if (genbosons_isLastCopy_branch) {genbosons_isLastCopy_branch->SetAddress(&genbosons_isLastCopy_);}
	}
	genbosons_gentaudecay_branch = 0;
	if (tree->GetBranch("genbosons_gentaudecay") != 0) {
		genbosons_gentaudecay_branch = tree->GetBranch("genbosons_gentaudecay");
		if (genbosons_gentaudecay_branch) {genbosons_gentaudecay_branch->SetAddress(&genbosons_gentaudecay_);}
	}
	gen_nfromtbosons__branch = 0;
	if (tree->GetBranch("gen_nfromtbosons_") != 0) {
		gen_nfromtbosons__branch = tree->GetBranch("gen_nfromtbosons_");
		if (gen_nfromtbosons__branch) {gen_nfromtbosons__branch->SetAddress(&gen_nfromtbosons__);}
	}
	genbosons_motherid_branch = 0;
	if (tree->GetBranch("genbosons_motherid") != 0) {
		genbosons_motherid_branch = tree->GetBranch("genbosons_motherid");
		if (genbosons_motherid_branch) {genbosons_motherid_branch->SetAddress(&genbosons_motherid_);}
	}
	genbosons_motheridx_branch = 0;
	if (tree->GetBranch("genbosons_motheridx") != 0) {
		genbosons_motheridx_branch = tree->GetBranch("genbosons_motheridx");
		if (genbosons_motheridx_branch) {genbosons_motheridx_branch->SetAddress(&genbosons_motheridx_);}
	}
	genbosons_motherstatus_branch = 0;
	if (tree->GetBranch("genbosons_motherstatus") != 0) {
		genbosons_motherstatus_branch = tree->GetBranch("genbosons_motherstatus");
		if (genbosons_motherstatus_branch) {genbosons_motherstatus_branch->SetAddress(&genbosons_motherstatus_);}
	}
	genbosons_gmotherid_branch = 0;
	if (tree->GetBranch("genbosons_gmotherid") != 0) {
		genbosons_gmotherid_branch = tree->GetBranch("genbosons_gmotherid");
		if (genbosons_gmotherid_branch) {genbosons_gmotherid_branch->SetAddress(&genbosons_gmotherid_);}
	}
	genbosons_gmotheridx_branch = 0;
	if (tree->GetBranch("genbosons_gmotheridx") != 0) {
		genbosons_gmotheridx_branch = tree->GetBranch("genbosons_gmotheridx");
		if (genbosons_gmotheridx_branch) {genbosons_gmotheridx_branch->SetAddress(&genbosons_gmotheridx_);}
	}
	genbosons_gmotherstatus_branch = 0;
	if (tree->GetBranch("genbosons_gmotherstatus") != 0) {
		genbosons_gmotherstatus_branch = tree->GetBranch("genbosons_gmotherstatus");
		if (genbosons_gmotherstatus_branch) {genbosons_gmotherstatus_branch->SetAddress(&genbosons_gmotherstatus_);}
	}
	gensusy_isfromt_branch = 0;
	if (tree->GetBranch("gensusy_isfromt") != 0) {
		gensusy_isfromt_branch = tree->GetBranch("gensusy_isfromt");
		if (gensusy_isfromt_branch) {gensusy_isfromt_branch->SetAddress(&gensusy_isfromt_);}
	}
	gensusy_id_branch = 0;
	if (tree->GetBranch("gensusy_id") != 0) {
		gensusy_id_branch = tree->GetBranch("gensusy_id");
		if (gensusy_id_branch) {gensusy_id_branch->SetAddress(&gensusy_id_);}
	}
	gensusy__genpsidx_branch = 0;
	if (tree->GetBranch("gensusy__genpsidx") != 0) {
		gensusy__genpsidx_branch = tree->GetBranch("gensusy__genpsidx");
		if (gensusy__genpsidx_branch) {gensusy__genpsidx_branch->SetAddress(&gensusy__genpsidx_);}
	}
	gensusy_status_branch = 0;
	if (tree->GetBranch("gensusy_status") != 0) {
		gensusy_status_branch = tree->GetBranch("gensusy_status");
		if (gensusy_status_branch) {gensusy_status_branch->SetAddress(&gensusy_status_);}
	}
	gensusy_fromHardProcessDecayed_branch = 0;
	if (tree->GetBranch("gensusy_fromHardProcessDecayed") != 0) {
		gensusy_fromHardProcessDecayed_branch = tree->GetBranch("gensusy_fromHardProcessDecayed");
		if (gensusy_fromHardProcessDecayed_branch) {gensusy_fromHardProcessDecayed_branch->SetAddress(&gensusy_fromHardProcessDecayed_);}
	}
	gensusy_fromHardProcessFinalState_branch = 0;
	if (tree->GetBranch("gensusy_fromHardProcessFinalState") != 0) {
		gensusy_fromHardProcessFinalState_branch = tree->GetBranch("gensusy_fromHardProcessFinalState");
		if (gensusy_fromHardProcessFinalState_branch) {gensusy_fromHardProcessFinalState_branch->SetAddress(&gensusy_fromHardProcessFinalState_);}
	}
	gensusy_isHardProcess_branch = 0;
	if (tree->GetBranch("gensusy_isHardProcess") != 0) {
		gensusy_isHardProcess_branch = tree->GetBranch("gensusy_isHardProcess");
		if (gensusy_isHardProcess_branch) {gensusy_isHardProcess_branch->SetAddress(&gensusy_isHardProcess_);}
	}
	gensusy_isLastCopy_branch = 0;
	if (tree->GetBranch("gensusy_isLastCopy") != 0) {
		gensusy_isLastCopy_branch = tree->GetBranch("gensusy_isLastCopy");
		if (gensusy_isLastCopy_branch) {gensusy_isLastCopy_branch->SetAddress(&gensusy_isLastCopy_);}
	}
	gensusy_gentaudecay_branch = 0;
	if (tree->GetBranch("gensusy_gentaudecay") != 0) {
		gensusy_gentaudecay_branch = tree->GetBranch("gensusy_gentaudecay");
		if (gensusy_gentaudecay_branch) {gensusy_gentaudecay_branch->SetAddress(&gensusy_gentaudecay_);}
	}
	gen_nfromtsusy__branch = 0;
	if (tree->GetBranch("gen_nfromtsusy_") != 0) {
		gen_nfromtsusy__branch = tree->GetBranch("gen_nfromtsusy_");
		if (gen_nfromtsusy__branch) {gen_nfromtsusy__branch->SetAddress(&gen_nfromtsusy__);}
	}
	gensusy_motherid_branch = 0;
	if (tree->GetBranch("gensusy_motherid") != 0) {
		gensusy_motherid_branch = tree->GetBranch("gensusy_motherid");
		if (gensusy_motherid_branch) {gensusy_motherid_branch->SetAddress(&gensusy_motherid_);}
	}
	gensusy_motheridx_branch = 0;
	if (tree->GetBranch("gensusy_motheridx") != 0) {
		gensusy_motheridx_branch = tree->GetBranch("gensusy_motheridx");
		if (gensusy_motheridx_branch) {gensusy_motheridx_branch->SetAddress(&gensusy_motheridx_);}
	}
	gensusy_motherstatus_branch = 0;
	if (tree->GetBranch("gensusy_motherstatus") != 0) {
		gensusy_motherstatus_branch = tree->GetBranch("gensusy_motherstatus");
		if (gensusy_motherstatus_branch) {gensusy_motherstatus_branch->SetAddress(&gensusy_motherstatus_);}
	}
	gensusy_gmotherid_branch = 0;
	if (tree->GetBranch("gensusy_gmotherid") != 0) {
		gensusy_gmotherid_branch = tree->GetBranch("gensusy_gmotherid");
		if (gensusy_gmotherid_branch) {gensusy_gmotherid_branch->SetAddress(&gensusy_gmotherid_);}
	}
	gensusy_gmotheridx_branch = 0;
	if (tree->GetBranch("gensusy_gmotheridx") != 0) {
		gensusy_gmotheridx_branch = tree->GetBranch("gensusy_gmotheridx");
		if (gensusy_gmotheridx_branch) {gensusy_gmotheridx_branch->SetAddress(&gensusy_gmotheridx_);}
	}
	gensusy_gmotherstatus_branch = 0;
	if (tree->GetBranch("gensusy_gmotherstatus") != 0) {
		gensusy_gmotherstatus_branch = tree->GetBranch("gensusy_gmotherstatus");
		if (gensusy_gmotherstatus_branch) {gensusy_gmotherstatus_branch->SetAddress(&gensusy_gmotherstatus_);}
	}
	tau_IDnames_branch = 0;
	if (tree->GetBranch("tau_IDnames") != 0) {
		tau_IDnames_branch = tree->GetBranch("tau_IDnames");
		if (tau_IDnames_branch) {tau_IDnames_branch->SetAddress(&tau_IDnames_);}
	}
	tau_isocand_p4_branch = 0;
	if (tree->GetBranch("tau_isocand_p4") != 0) {
		tau_isocand_p4_branch = tree->GetBranch("tau_isocand_p4");
		if (tau_isocand_p4_branch) {tau_isocand_p4_branch->SetAddress(&tau_isocand_p4_);}
	}
	tau_sigcand_p4_branch = 0;
	if (tree->GetBranch("tau_sigcand_p4") != 0) {
		tau_sigcand_p4_branch = tree->GetBranch("tau_sigcand_p4");
		if (tau_sigcand_p4_branch) {tau_sigcand_p4_branch->SetAddress(&tau_sigcand_p4_);}
	}
	tau_ID_branch = 0;
	if (tree->GetBranch("tau_ID") != 0) {
		tau_ID_branch = tree->GetBranch("tau_ID");
		if (tau_ID_branch) {tau_ID_branch->SetAddress(&tau_ID_);}
	}
	tau_passID_branch = 0;
	if (tree->GetBranch("tau_passID") != 0) {
		tau_passID_branch = tree->GetBranch("tau_passID");
		if (tau_passID_branch) {tau_passID_branch->SetAddress(&tau_passID_);}
	}
	ngoodtaus_branch = 0;
	if (tree->GetBranch("ngoodtaus") != 0) {
		ngoodtaus_branch = tree->GetBranch("ngoodtaus");
		if (ngoodtaus_branch) {ngoodtaus_branch->SetAddress(&ngoodtaus_);}
	}
	tau_againstMuonTight_branch = 0;
	if (tree->GetBranch("tau_againstMuonTight") != 0) {
		tau_againstMuonTight_branch = tree->GetBranch("tau_againstMuonTight");
		if (tau_againstMuonTight_branch) {tau_againstMuonTight_branch->SetAddress(&tau_againstMuonTight_);}
	}
	tau_againstElectronLoose_branch = 0;
	if (tree->GetBranch("tau_againstElectronLoose") != 0) {
		tau_againstElectronLoose_branch = tree->GetBranch("tau_againstElectronLoose");
		if (tau_againstElectronLoose_branch) {tau_againstElectronLoose_branch->SetAddress(&tau_againstElectronLoose_);}
	}
	tau_isVetoTau_branch = 0;
	if (tree->GetBranch("tau_isVetoTau") != 0) {
		tau_isVetoTau_branch = tree->GetBranch("tau_isVetoTau");
		if (tau_isVetoTau_branch) {tau_isVetoTau_branch->SetAddress(&tau_isVetoTau_);}
	}
	isoTracks_charge_branch = 0;
	if (tree->GetBranch("isoTracks_charge") != 0) {
		isoTracks_charge_branch = tree->GetBranch("isoTracks_charge");
		if (isoTracks_charge_branch) {isoTracks_charge_branch->SetAddress(&isoTracks_charge_);}
	}
	isoTracks_absIso_branch = 0;
	if (tree->GetBranch("isoTracks_absIso") != 0) {
		isoTracks_absIso_branch = tree->GetBranch("isoTracks_absIso");
		if (isoTracks_absIso_branch) {isoTracks_absIso_branch->SetAddress(&isoTracks_absIso_);}
	}
	isoTracks_dz_branch = 0;
	if (tree->GetBranch("isoTracks_dz") != 0) {
		isoTracks_dz_branch = tree->GetBranch("isoTracks_dz");
		if (isoTracks_dz_branch) {isoTracks_dz_branch->SetAddress(&isoTracks_dz_);}
	}
	isoTracks_pdgId_branch = 0;
	if (tree->GetBranch("isoTracks_pdgId") != 0) {
		isoTracks_pdgId_branch = tree->GetBranch("isoTracks_pdgId");
		if (isoTracks_pdgId_branch) {isoTracks_pdgId_branch->SetAddress(&isoTracks_pdgId_);}
	}
	isoTracks_isVetoTrack_branch = 0;
	if (tree->GetBranch("isoTracks_isVetoTrack") != 0) {
		isoTracks_isVetoTrack_branch = tree->GetBranch("isoTracks_isVetoTrack");
		if (isoTracks_isVetoTrack_branch) {isoTracks_isVetoTrack_branch->SetAddress(&isoTracks_isVetoTrack_);}
	}
	isoTracks_isVetoTrack_v2_branch = 0;
	if (tree->GetBranch("isoTracks_isVetoTrack_v2") != 0) {
		isoTracks_isVetoTrack_v2_branch = tree->GetBranch("isoTracks_isVetoTrack_v2");
		if (isoTracks_isVetoTrack_v2_branch) {isoTracks_isVetoTrack_v2_branch->SetAddress(&isoTracks_isVetoTrack_v2_);}
	}
	isoTracks_isVetoTrack_v3_branch = 0;
	if (tree->GetBranch("isoTracks_isVetoTrack_v3") != 0) {
		isoTracks_isVetoTrack_v3_branch = tree->GetBranch("isoTracks_isVetoTrack_v3");
		if (isoTracks_isVetoTrack_v3_branch) {isoTracks_isVetoTrack_v3_branch->SetAddress(&isoTracks_isVetoTrack_v3_);}
	}
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		run_isLoaded = false;
		ls_isLoaded = false;
		evt_isLoaded = false;
		nvtxs_isLoaded = false;
		pu_nvtxs_isLoaded = false;
		pfmet_isLoaded = false;
		pfmet_phi_isLoaded = false;
		pfmet_rl_isLoaded = false;
		pfmet_phi_rl_isLoaded = false;
		scale1fb_isLoaded = false;
		xsec_isLoaded = false;
		xsec_uncert_isLoaded = false;
		kfactor_isLoaded = false;
		pu_ntrue_isLoaded = false;
		ngoodleps_isLoaded = false;
		nvetoleps_isLoaded = false;
		is_data_isLoaded = false;
		dataset_isLoaded = false;
		filename_isLoaded = false;
		cms3tag_isLoaded = false;
		nEvents_isLoaded = false;
		nEvents_goodvtx_isLoaded = false;
		nEvents_MET30_isLoaded = false;
		nEvents_1goodlep_isLoaded = false;
		nEvents_2goodjets_isLoaded = false;
		is0lep_isLoaded = false;
		is1lep_isLoaded = false;
		is2lep_isLoaded = false;
		isZtoNuNu_isLoaded = false;
		is1lepFromW_isLoaded = false;
		is1lepFromTop_isLoaded = false;
		MT2W_isLoaded = false;
		MT2W_rl_isLoaded = false;
		mindphi_met_j1_j2_isLoaded = false;
		mindphi_met_j1_j2_rl_isLoaded = false;
		mt_met_lep_isLoaded = false;
		mt_met_lep_rl_isLoaded = false;
		hadronic_top_chi2_isLoaded = false;
		ak4pfjets_rho_isLoaded = false;
		pdf_up_weight_isLoaded = false;
		pdf_down_weight_isLoaded = false;
		genweightsID_isLoaded = false;
		genweights_isLoaded = false;
		weight_btagsf_isLoaded = false;
		weight_btagsf_heavy_UP_isLoaded = false;
		weight_btagsf_light_UP_isLoaded = false;
		weight_btagsf_heavy_DN_isLoaded = false;
		weight_btagsf_light_DN_isLoaded = false;
		weight_btagsf_fastsim_UP_isLoaded = false;
		weight_btagsf_fastsim_DN_isLoaded = false;
		weight_lepSF_isLoaded = false;
		weight_lepSF_up_isLoaded = false;
		weight_lepSF_down_isLoaded = false;
		weight_vetoLepSF_isLoaded = false;
		weight_vetoLepSF_up_isLoaded = false;
		weight_vetoLepSF_down_isLoaded = false;
		weight_lepSF_fastSim_isLoaded = false;
		weight_lepSF_fastSim_up_isLoaded = false;
		weight_lepSF_fastSim_down_isLoaded = false;
		weight_ISR_isLoaded = false;
		weight_ISRup_isLoaded = false;
		weight_ISRdown_isLoaded = false;
		weight_PU_isLoaded = false;
		weight_PUup_isLoaded = false;
		weight_PUdown_isLoaded = false;
		sparms_names_isLoaded = false;
		sparms_values_isLoaded = false;
		sparms_subProcessId_isLoaded = false;
		mass_lsp_isLoaded = false;
		mass_chargino_isLoaded = false;
		mass_stop_isLoaded = false;
		mass_gluino_isLoaded = false;
		genmet_isLoaded = false;
		genmet_phi_isLoaded = false;
		nupt_isLoaded = false;
		genht_isLoaded = false;
		PassTrackVeto_isLoaded = false;
		PassTauVeto_isLoaded = false;
		topness_isLoaded = false;
		topnessMod_isLoaded = false;
		topnessMod_rl_isLoaded = false;
		Mlb_closestb_isLoaded = false;
		HLT_SingleEl_isLoaded = false;
		HLT_SingleMu_isLoaded = false;
		HLT_MET_isLoaded = false;
		HLT_MET100_MHT100_isLoaded = false;
		HLT_DiEl_isLoaded = false;
		HLT_DiMu_isLoaded = false;
		HLT_MuE_isLoaded = false;
		HLT_Photon90_CaloIdL_PFHT500_isLoaded = false;
		HLT_Photon22_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon30_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon36_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon50_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon75_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon90_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon120_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon165_R9Id90_HE10_IsoM_isLoaded = false;
		HLT_Photon175_isLoaded = false;
		HLT_Photon165_HE10_isLoaded = false;
		nPhotons_isLoaded = false;
		ph_ngoodjets_isLoaded = false;
		ph_ngoodbtags_isLoaded = false;
		filt_met_isLoaded = false;
		hardgenpt_isLoaded = false;
		filt_badChargedCandidateFilter_isLoaded = false;
		filt_badMuonFilter_isLoaded = false;
		calomet_isLoaded = false;
		calomet_phi_isLoaded = false;
		lep1_pdgid_isLoaded = false;
		lep1_production_type_isLoaded = false;
		lep1_MiniIso_isLoaded = false;
		lep1_relIso_isLoaded = false;
		lep1_passLooseID_isLoaded = false;
		lep1_passMediumID_isLoaded = false;
		lep1_passTightID_isLoaded = false;
		lep1_passVeto_isLoaded = false;
		lep1_p4_isLoaded = false;
		lep1_mcp4_isLoaded = false;
		lep1_mc_motherid_isLoaded = false;
		lep2_pdgid_isLoaded = false;
		lep2_production_type_isLoaded = false;
		lep2_MiniIso_isLoaded = false;
		lep2_relIso_isLoaded = false;
		lep2_passLooseID_isLoaded = false;
		lep2_passMediumID_isLoaded = false;
		lep2_passTightID_isLoaded = false;
		lep2_passVeto_isLoaded = false;
		lep2_p4_isLoaded = false;
		lep2_mcp4_isLoaded = false;
		lep2_mc_motherid_isLoaded = false;
		ph_sigmaIEtaEta_fill5x5_isLoaded = false;
		ph_hOverE_isLoaded = false;
		ph_r9_isLoaded = false;
		ph_chiso_isLoaded = false;
		ph_nhiso_isLoaded = false;
		ph_phiso_isLoaded = false;
		ph_idCutBased_isLoaded = false;
		ph_overlapJetId_isLoaded = false;
		ph_p4_isLoaded = false;
		ph_mcp4_isLoaded = false;
		ph_pt_isLoaded = false;
		ph_eta_isLoaded = false;
		ph_phi_isLoaded = false;
		ph_mass_isLoaded = false;
		ph_mcMatchId_isLoaded = false;
		ph_genIso04_isLoaded = false;
		ph_drMinParton_isLoaded = false;
		ngoodjets_isLoaded = false;
		ngoodbtags_isLoaded = false;
		ak4_HT_isLoaded = false;
		ak4_htratiom_isLoaded = false;
		dphi_ak4pfjet_met_isLoaded = false;
		ak4pfjets_p4_isLoaded = false;
		ak4pfjets_passMEDbtag_isLoaded = false;
		ak4pfjets_CSV_isLoaded = false;
		ak4pfjets_mva_isLoaded = false;
		ak4pfjets_parton_flavor_isLoaded = false;
		ak4pfjets_hadron_flavor_isLoaded = false;
		ak4pfjets_loose_puid_isLoaded = false;
		ak4pfjets_loose_pfid_isLoaded = false;
		ak4pfjets_leadMEDbjet_p4_isLoaded = false;
		ak4pfjets_leadbtag_p4_isLoaded = false;
		ak4genjets_p4_isLoaded = false;
		genleps_isfromt_isLoaded = false;
		genleps_p4_isLoaded = false;
		genleps_id_isLoaded = false;
		genleps__genpsidx_isLoaded = false;
		genleps_status_isLoaded = false;
		genleps_fromHardProcessDecayed_isLoaded = false;
		genleps_fromHardProcessFinalState_isLoaded = false;
		genleps_isHardProcess_isLoaded = false;
		genleps_isLastCopy_isLoaded = false;
		genleps_gentaudecay_isLoaded = false;
		gen_nfromtleps__isLoaded = false;
		genleps_motherp4_isLoaded = false;
		genleps_motherid_isLoaded = false;
		genleps_motheridx_isLoaded = false;
		genleps_motherstatus_isLoaded = false;
		genleps_gmotherp4_isLoaded = false;
		genleps_gmotherid_isLoaded = false;
		genleps_gmotheridx_isLoaded = false;
		genleps_gmotherstatus_isLoaded = false;
		gennus_isfromt_isLoaded = false;
		gennus_p4_isLoaded = false;
		gennus_id_isLoaded = false;
		gennus__genpsidx_isLoaded = false;
		gennus_status_isLoaded = false;
		gennus_fromHardProcessDecayed_isLoaded = false;
		gennus_fromHardProcessFinalState_isLoaded = false;
		gennus_isHardProcess_isLoaded = false;
		gennus_isLastCopy_isLoaded = false;
		gennus_gentaudecay_isLoaded = false;
		gen_nfromtnus__isLoaded = false;
		gennus_motherp4_isLoaded = false;
		gennus_motherid_isLoaded = false;
		gennus_motheridx_isLoaded = false;
		gennus_motherstatus_isLoaded = false;
		gennus_gmotherp4_isLoaded = false;
		gennus_gmotherid_isLoaded = false;
		gennus_gmotheridx_isLoaded = false;
		gennus_gmotherstatus_isLoaded = false;
		genqs_isfromt_isLoaded = false;
		genqs_p4_isLoaded = false;
		genqs_id_isLoaded = false;
		genqs__genpsidx_isLoaded = false;
		genqs_status_isLoaded = false;
		genqs_fromHardProcessDecayed_isLoaded = false;
		genqs_fromHardProcessFinalState_isLoaded = false;
		genqs_isHardProcess_isLoaded = false;
		genqs_isLastCopy_isLoaded = false;
		genqs_gentaudecay_isLoaded = false;
		gen_nfromtqs__isLoaded = false;
		genqs_motherp4_isLoaded = false;
		genqs_motherid_isLoaded = false;
		genqs_motheridx_isLoaded = false;
		genqs_motherstatus_isLoaded = false;
		genqs_gmotherp4_isLoaded = false;
		genqs_gmotherid_isLoaded = false;
		genqs_gmotheridx_isLoaded = false;
		genqs_gmotherstatus_isLoaded = false;
		genbosons_isfromt_isLoaded = false;
		genbosons_p4_isLoaded = false;
		genbosons_id_isLoaded = false;
		genbosons__genpsidx_isLoaded = false;
		genbosons_status_isLoaded = false;
		genbosons_fromHardProcessDecayed_isLoaded = false;
		genbosons_fromHardProcessFinalState_isLoaded = false;
		genbosons_isHardProcess_isLoaded = false;
		genbosons_isLastCopy_isLoaded = false;
		genbosons_gentaudecay_isLoaded = false;
		gen_nfromtbosons__isLoaded = false;
		genbosons_motherp4_isLoaded = false;
		genbosons_motherid_isLoaded = false;
		genbosons_motheridx_isLoaded = false;
		genbosons_motherstatus_isLoaded = false;
		genbosons_gmotherp4_isLoaded = false;
		genbosons_gmotherid_isLoaded = false;
		genbosons_gmotheridx_isLoaded = false;
		genbosons_gmotherstatus_isLoaded = false;
		gensusy_isfromt_isLoaded = false;
		gensusy_p4_isLoaded = false;
		gensusy_id_isLoaded = false;
		gensusy__genpsidx_isLoaded = false;
		gensusy_status_isLoaded = false;
		gensusy_fromHardProcessDecayed_isLoaded = false;
		gensusy_fromHardProcessFinalState_isLoaded = false;
		gensusy_isHardProcess_isLoaded = false;
		gensusy_isLastCopy_isLoaded = false;
		gensusy_gentaudecay_isLoaded = false;
		gen_nfromtsusy__isLoaded = false;
		gensusy_motherp4_isLoaded = false;
		gensusy_motherid_isLoaded = false;
		gensusy_motheridx_isLoaded = false;
		gensusy_motherstatus_isLoaded = false;
		gensusy_gmotherp4_isLoaded = false;
		gensusy_gmotherid_isLoaded = false;
		gensusy_gmotheridx_isLoaded = false;
		gensusy_gmotherstatus_isLoaded = false;
		tau_IDnames_isLoaded = false;
		tau_leadtrack_p4_isLoaded = false;
		tau_leadneutral_p4_isLoaded = false;
		tau_p4_isLoaded = false;
		tau_isocand_p4_isLoaded = false;
		tau_sigcand_p4_isLoaded = false;
		tau_ID_isLoaded = false;
		tau_passID_isLoaded = false;
		ngoodtaus_isLoaded = false;
		tau_againstMuonTight_isLoaded = false;
		tau_againstElectronLoose_isLoaded = false;
		tau_isVetoTau_isLoaded = false;
		isoTracks_p4_isLoaded = false;
		isoTracks_charge_isLoaded = false;
		isoTracks_absIso_isLoaded = false;
		isoTracks_dz_isLoaded = false;
		isoTracks_pdgId_isLoaded = false;
		isoTracks_isVetoTrack_isLoaded = false;
		isoTracks_isVetoTrack_v2_isLoaded = false;
		isoTracks_isVetoTrack_v3_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (run_branch != 0) run();
	if (ls_branch != 0) ls();
	if (evt_branch != 0) evt();
	if (nvtxs_branch != 0) nvtxs();
	if (pu_nvtxs_branch != 0) pu_nvtxs();
	if (pfmet_branch != 0) pfmet();
	if (pfmet_phi_branch != 0) pfmet_phi();
	if (pfmet_rl_branch != 0) pfmet_rl();
	if (pfmet_phi_rl_branch != 0) pfmet_phi_rl();
	if (scale1fb_branch != 0) scale1fb();
	if (xsec_branch != 0) xsec();
	if (xsec_uncert_branch != 0) xsec_uncert();
	if (kfactor_branch != 0) kfactor();
	if (pu_ntrue_branch != 0) pu_ntrue();
	if (ngoodleps_branch != 0) ngoodleps();
	if (nvetoleps_branch != 0) nvetoleps();
	if (is_data_branch != 0) is_data();
	if (dataset_branch != 0) dataset();
	if (filename_branch != 0) filename();
	if (cms3tag_branch != 0) cms3tag();
	if (nEvents_branch != 0) nEvents();
	if (nEvents_goodvtx_branch != 0) nEvents_goodvtx();
	if (nEvents_MET30_branch != 0) nEvents_MET30();
	if (nEvents_1goodlep_branch != 0) nEvents_1goodlep();
	if (nEvents_2goodjets_branch != 0) nEvents_2goodjets();
	if (is0lep_branch != 0) is0lep();
	if (is1lep_branch != 0) is1lep();
	if (is2lep_branch != 0) is2lep();
	if (isZtoNuNu_branch != 0) isZtoNuNu();
	if (is1lepFromW_branch != 0) is1lepFromW();
	if (is1lepFromTop_branch != 0) is1lepFromTop();
	if (MT2W_branch != 0) MT2W();
	if (MT2W_rl_branch != 0) MT2W_rl();
	if (mindphi_met_j1_j2_branch != 0) mindphi_met_j1_j2();
	if (mindphi_met_j1_j2_rl_branch != 0) mindphi_met_j1_j2_rl();
	if (mt_met_lep_branch != 0) mt_met_lep();
	if (mt_met_lep_rl_branch != 0) mt_met_lep_rl();
	if (hadronic_top_chi2_branch != 0) hadronic_top_chi2();
	if (ak4pfjets_rho_branch != 0) ak4pfjets_rho();
	if (pdf_up_weight_branch != 0) pdf_up_weight();
	if (pdf_down_weight_branch != 0) pdf_down_weight();
	if (genweightsID_branch != 0) genweightsID();
	if (genweights_branch != 0) genweights();
	if (weight_btagsf_branch != 0) weight_btagsf();
	if (weight_btagsf_heavy_UP_branch != 0) weight_btagsf_heavy_UP();
	if (weight_btagsf_light_UP_branch != 0) weight_btagsf_light_UP();
	if (weight_btagsf_heavy_DN_branch != 0) weight_btagsf_heavy_DN();
	if (weight_btagsf_light_DN_branch != 0) weight_btagsf_light_DN();
	if (weight_btagsf_fastsim_UP_branch != 0) weight_btagsf_fastsim_UP();
	if (weight_btagsf_fastsim_DN_branch != 0) weight_btagsf_fastsim_DN();
	if (weight_lepSF_branch != 0) weight_lepSF();
	if (weight_lepSF_up_branch != 0) weight_lepSF_up();
	if (weight_lepSF_down_branch != 0) weight_lepSF_down();
	if (weight_vetoLepSF_branch != 0) weight_vetoLepSF();
	if (weight_vetoLepSF_up_branch != 0) weight_vetoLepSF_up();
	if (weight_vetoLepSF_down_branch != 0) weight_vetoLepSF_down();
	if (weight_lepSF_fastSim_branch != 0) weight_lepSF_fastSim();
	if (weight_lepSF_fastSim_up_branch != 0) weight_lepSF_fastSim_up();
	if (weight_lepSF_fastSim_down_branch != 0) weight_lepSF_fastSim_down();
	if (weight_ISR_branch != 0) weight_ISR();
	if (weight_ISRup_branch != 0) weight_ISRup();
	if (weight_ISRdown_branch != 0) weight_ISRdown();
	if (weight_PU_branch != 0) weight_PU();
	if (weight_PUup_branch != 0) weight_PUup();
	if (weight_PUdown_branch != 0) weight_PUdown();
	if (sparms_names_branch != 0) sparms_names();
	if (sparms_values_branch != 0) sparms_values();
	if (sparms_subProcessId_branch != 0) sparms_subProcessId();
	if (mass_lsp_branch != 0) mass_lsp();
	if (mass_chargino_branch != 0) mass_chargino();
	if (mass_stop_branch != 0) mass_stop();
	if (mass_gluino_branch != 0) mass_gluino();
	if (genmet_branch != 0) genmet();
	if (genmet_phi_branch != 0) genmet_phi();
	if (nupt_branch != 0) nupt();
	if (genht_branch != 0) genht();
	if (PassTrackVeto_branch != 0) PassTrackVeto();
	if (PassTauVeto_branch != 0) PassTauVeto();
	if (topness_branch != 0) topness();
	if (topnessMod_branch != 0) topnessMod();
	if (topnessMod_rl_branch != 0) topnessMod_rl();
	if (Mlb_closestb_branch != 0) Mlb_closestb();
	if (HLT_SingleEl_branch != 0) HLT_SingleEl();
	if (HLT_SingleMu_branch != 0) HLT_SingleMu();
	if (HLT_MET_branch != 0) HLT_MET();
	if (HLT_MET100_MHT100_branch != 0) HLT_MET100_MHT100();
	if (HLT_DiEl_branch != 0) HLT_DiEl();
	if (HLT_DiMu_branch != 0) HLT_DiMu();
	if (HLT_MuE_branch != 0) HLT_MuE();
	if (HLT_Photon90_CaloIdL_PFHT500_branch != 0) HLT_Photon90_CaloIdL_PFHT500();
	if (HLT_Photon22_R9Id90_HE10_IsoM_branch != 0) HLT_Photon22_R9Id90_HE10_IsoM();
	if (HLT_Photon30_R9Id90_HE10_IsoM_branch != 0) HLT_Photon30_R9Id90_HE10_IsoM();
	if (HLT_Photon36_R9Id90_HE10_IsoM_branch != 0) HLT_Photon36_R9Id90_HE10_IsoM();
	if (HLT_Photon50_R9Id90_HE10_IsoM_branch != 0) HLT_Photon50_R9Id90_HE10_IsoM();
	if (HLT_Photon75_R9Id90_HE10_IsoM_branch != 0) HLT_Photon75_R9Id90_HE10_IsoM();
	if (HLT_Photon90_R9Id90_HE10_IsoM_branch != 0) HLT_Photon90_R9Id90_HE10_IsoM();
	if (HLT_Photon120_R9Id90_HE10_IsoM_branch != 0) HLT_Photon120_R9Id90_HE10_IsoM();
	if (HLT_Photon165_R9Id90_HE10_IsoM_branch != 0) HLT_Photon165_R9Id90_HE10_IsoM();
	if (HLT_Photon175_branch != 0) HLT_Photon175();
	if (HLT_Photon165_HE10_branch != 0) HLT_Photon165_HE10();
	if (nPhotons_branch != 0) nPhotons();
	if (ph_ngoodjets_branch != 0) ph_ngoodjets();
	if (ph_ngoodbtags_branch != 0) ph_ngoodbtags();
	if (filt_met_branch != 0) filt_met();
	if (hardgenpt_branch != 0) hardgenpt();
	if (filt_badChargedCandidateFilter_branch != 0) filt_badChargedCandidateFilter();
	if (filt_badMuonFilter_branch != 0) filt_badMuonFilter();
	if (calomet_branch != 0) calomet();
	if (calomet_phi_branch != 0) calomet_phi();
	if (lep1_pdgid_branch != 0) lep1_pdgid();
	if (lep1_production_type_branch != 0) lep1_production_type();
	if (lep1_MiniIso_branch != 0) lep1_MiniIso();
	if (lep1_relIso_branch != 0) lep1_relIso();
	if (lep1_passLooseID_branch != 0) lep1_passLooseID();
	if (lep1_passMediumID_branch != 0) lep1_passMediumID();
	if (lep1_passTightID_branch != 0) lep1_passTightID();
	if (lep1_passVeto_branch != 0) lep1_passVeto();
	if (lep1_p4_branch != 0) lep1_p4();
	if (lep1_mcp4_branch != 0) lep1_mcp4();
	if (lep1_mc_motherid_branch != 0) lep1_mc_motherid();
	if (lep2_pdgid_branch != 0) lep2_pdgid();
	if (lep2_production_type_branch != 0) lep2_production_type();
	if (lep2_MiniIso_branch != 0) lep2_MiniIso();
	if (lep2_relIso_branch != 0) lep2_relIso();
	if (lep2_passLooseID_branch != 0) lep2_passLooseID();
	if (lep2_passMediumID_branch != 0) lep2_passMediumID();
	if (lep2_passTightID_branch != 0) lep2_passTightID();
	if (lep2_passVeto_branch != 0) lep2_passVeto();
	if (lep2_p4_branch != 0) lep2_p4();
	if (lep2_mcp4_branch != 0) lep2_mcp4();
	if (lep2_mc_motherid_branch != 0) lep2_mc_motherid();
	if (ph_sigmaIEtaEta_fill5x5_branch != 0) ph_sigmaIEtaEta_fill5x5();
	if (ph_hOverE_branch != 0) ph_hOverE();
	if (ph_r9_branch != 0) ph_r9();
	if (ph_chiso_branch != 0) ph_chiso();
	if (ph_nhiso_branch != 0) ph_nhiso();
	if (ph_phiso_branch != 0) ph_phiso();
	if (ph_idCutBased_branch != 0) ph_idCutBased();
	if (ph_overlapJetId_branch != 0) ph_overlapJetId();
	if (ph_p4_branch != 0) ph_p4();
	if (ph_mcp4_branch != 0) ph_mcp4();
	if (ph_pt_branch != 0) ph_pt();
	if (ph_eta_branch != 0) ph_eta();
	if (ph_phi_branch != 0) ph_phi();
	if (ph_mass_branch != 0) ph_mass();
	if (ph_mcMatchId_branch != 0) ph_mcMatchId();
	if (ph_genIso04_branch != 0) ph_genIso04();
	if (ph_drMinParton_branch != 0) ph_drMinParton();
	if (ngoodjets_branch != 0) ngoodjets();
	if (ngoodbtags_branch != 0) ngoodbtags();
	if (ak4_HT_branch != 0) ak4_HT();
	if (ak4_htratiom_branch != 0) ak4_htratiom();
	if (dphi_ak4pfjet_met_branch != 0) dphi_ak4pfjet_met();
	if (ak4pfjets_p4_branch != 0) ak4pfjets_p4();
	if (ak4pfjets_passMEDbtag_branch != 0) ak4pfjets_passMEDbtag();
	if (ak4pfjets_CSV_branch != 0) ak4pfjets_CSV();
	if (ak4pfjets_mva_branch != 0) ak4pfjets_mva();
	if (ak4pfjets_parton_flavor_branch != 0) ak4pfjets_parton_flavor();
	if (ak4pfjets_hadron_flavor_branch != 0) ak4pfjets_hadron_flavor();
	if (ak4pfjets_loose_puid_branch != 0) ak4pfjets_loose_puid();
	if (ak4pfjets_loose_pfid_branch != 0) ak4pfjets_loose_pfid();
	if (ak4pfjets_leadMEDbjet_p4_branch != 0) ak4pfjets_leadMEDbjet_p4();
	if (ak4pfjets_leadbtag_p4_branch != 0) ak4pfjets_leadbtag_p4();
	if (ak4genjets_p4_branch != 0) ak4genjets_p4();
	if (genleps_isfromt_branch != 0) genleps_isfromt();
	if (genleps_p4_branch != 0) genleps_p4();
	if (genleps_id_branch != 0) genleps_id();
	if (genleps__genpsidx_branch != 0) genleps__genpsidx();
	if (genleps_status_branch != 0) genleps_status();
	if (genleps_fromHardProcessDecayed_branch != 0) genleps_fromHardProcessDecayed();
	if (genleps_fromHardProcessFinalState_branch != 0) genleps_fromHardProcessFinalState();
	if (genleps_isHardProcess_branch != 0) genleps_isHardProcess();
	if (genleps_isLastCopy_branch != 0) genleps_isLastCopy();
	if (genleps_gentaudecay_branch != 0) genleps_gentaudecay();
	if (gen_nfromtleps__branch != 0) gen_nfromtleps_();
	if (genleps_motherp4_branch != 0) genleps_motherp4();
	if (genleps_motherid_branch != 0) genleps_motherid();
	if (genleps_motheridx_branch != 0) genleps_motheridx();
	if (genleps_motherstatus_branch != 0) genleps_motherstatus();
	if (genleps_gmotherp4_branch != 0) genleps_gmotherp4();
	if (genleps_gmotherid_branch != 0) genleps_gmotherid();
	if (genleps_gmotheridx_branch != 0) genleps_gmotheridx();
	if (genleps_gmotherstatus_branch != 0) genleps_gmotherstatus();
	if (gennus_isfromt_branch != 0) gennus_isfromt();
	if (gennus_p4_branch != 0) gennus_p4();
	if (gennus_id_branch != 0) gennus_id();
	if (gennus__genpsidx_branch != 0) gennus__genpsidx();
	if (gennus_status_branch != 0) gennus_status();
	if (gennus_fromHardProcessDecayed_branch != 0) gennus_fromHardProcessDecayed();
	if (gennus_fromHardProcessFinalState_branch != 0) gennus_fromHardProcessFinalState();
	if (gennus_isHardProcess_branch != 0) gennus_isHardProcess();
	if (gennus_isLastCopy_branch != 0) gennus_isLastCopy();
	if (gennus_gentaudecay_branch != 0) gennus_gentaudecay();
	if (gen_nfromtnus__branch != 0) gen_nfromtnus_();
	if (gennus_motherp4_branch != 0) gennus_motherp4();
	if (gennus_motherid_branch != 0) gennus_motherid();
	if (gennus_motheridx_branch != 0) gennus_motheridx();
	if (gennus_motherstatus_branch != 0) gennus_motherstatus();
	if (gennus_gmotherp4_branch != 0) gennus_gmotherp4();
	if (gennus_gmotherid_branch != 0) gennus_gmotherid();
	if (gennus_gmotheridx_branch != 0) gennus_gmotheridx();
	if (gennus_gmotherstatus_branch != 0) gennus_gmotherstatus();
	if (genqs_isfromt_branch != 0) genqs_isfromt();
	if (genqs_p4_branch != 0) genqs_p4();
	if (genqs_id_branch != 0) genqs_id();
	if (genqs__genpsidx_branch != 0) genqs__genpsidx();
	if (genqs_status_branch != 0) genqs_status();
	if (genqs_fromHardProcessDecayed_branch != 0) genqs_fromHardProcessDecayed();
	if (genqs_fromHardProcessFinalState_branch != 0) genqs_fromHardProcessFinalState();
	if (genqs_isHardProcess_branch != 0) genqs_isHardProcess();
	if (genqs_isLastCopy_branch != 0) genqs_isLastCopy();
	if (genqs_gentaudecay_branch != 0) genqs_gentaudecay();
	if (gen_nfromtqs__branch != 0) gen_nfromtqs_();
	if (genqs_motherp4_branch != 0) genqs_motherp4();
	if (genqs_motherid_branch != 0) genqs_motherid();
	if (genqs_motheridx_branch != 0) genqs_motheridx();
	if (genqs_motherstatus_branch != 0) genqs_motherstatus();
	if (genqs_gmotherp4_branch != 0) genqs_gmotherp4();
	if (genqs_gmotherid_branch != 0) genqs_gmotherid();
	if (genqs_gmotheridx_branch != 0) genqs_gmotheridx();
	if (genqs_gmotherstatus_branch != 0) genqs_gmotherstatus();
	if (genbosons_isfromt_branch != 0) genbosons_isfromt();
	if (genbosons_p4_branch != 0) genbosons_p4();
	if (genbosons_id_branch != 0) genbosons_id();
	if (genbosons__genpsidx_branch != 0) genbosons__genpsidx();
	if (genbosons_status_branch != 0) genbosons_status();
	if (genbosons_fromHardProcessDecayed_branch != 0) genbosons_fromHardProcessDecayed();
	if (genbosons_fromHardProcessFinalState_branch != 0) genbosons_fromHardProcessFinalState();
	if (genbosons_isHardProcess_branch != 0) genbosons_isHardProcess();
	if (genbosons_isLastCopy_branch != 0) genbosons_isLastCopy();
	if (genbosons_gentaudecay_branch != 0) genbosons_gentaudecay();
	if (gen_nfromtbosons__branch != 0) gen_nfromtbosons_();
	if (genbosons_motherp4_branch != 0) genbosons_motherp4();
	if (genbosons_motherid_branch != 0) genbosons_motherid();
	if (genbosons_motheridx_branch != 0) genbosons_motheridx();
	if (genbosons_motherstatus_branch != 0) genbosons_motherstatus();
	if (genbosons_gmotherp4_branch != 0) genbosons_gmotherp4();
	if (genbosons_gmotherid_branch != 0) genbosons_gmotherid();
	if (genbosons_gmotheridx_branch != 0) genbosons_gmotheridx();
	if (genbosons_gmotherstatus_branch != 0) genbosons_gmotherstatus();
	if (gensusy_isfromt_branch != 0) gensusy_isfromt();
	if (gensusy_p4_branch != 0) gensusy_p4();
	if (gensusy_id_branch != 0) gensusy_id();
	if (gensusy__genpsidx_branch != 0) gensusy__genpsidx();
	if (gensusy_status_branch != 0) gensusy_status();
	if (gensusy_fromHardProcessDecayed_branch != 0) gensusy_fromHardProcessDecayed();
	if (gensusy_fromHardProcessFinalState_branch != 0) gensusy_fromHardProcessFinalState();
	if (gensusy_isHardProcess_branch != 0) gensusy_isHardProcess();
	if (gensusy_isLastCopy_branch != 0) gensusy_isLastCopy();
	if (gensusy_gentaudecay_branch != 0) gensusy_gentaudecay();
	if (gen_nfromtsusy__branch != 0) gen_nfromtsusy_();
	if (gensusy_motherp4_branch != 0) gensusy_motherp4();
	if (gensusy_motherid_branch != 0) gensusy_motherid();
	if (gensusy_motheridx_branch != 0) gensusy_motheridx();
	if (gensusy_motherstatus_branch != 0) gensusy_motherstatus();
	if (gensusy_gmotherp4_branch != 0) gensusy_gmotherp4();
	if (gensusy_gmotherid_branch != 0) gensusy_gmotherid();
	if (gensusy_gmotheridx_branch != 0) gensusy_gmotheridx();
	if (gensusy_gmotherstatus_branch != 0) gensusy_gmotherstatus();
	if (tau_IDnames_branch != 0) tau_IDnames();
	if (tau_leadtrack_p4_branch != 0) tau_leadtrack_p4();
	if (tau_leadneutral_p4_branch != 0) tau_leadneutral_p4();
	if (tau_p4_branch != 0) tau_p4();
	if (tau_isocand_p4_branch != 0) tau_isocand_p4();
	if (tau_sigcand_p4_branch != 0) tau_sigcand_p4();
	if (tau_ID_branch != 0) tau_ID();
	if (tau_passID_branch != 0) tau_passID();
	if (ngoodtaus_branch != 0) ngoodtaus();
	if (tau_againstMuonTight_branch != 0) tau_againstMuonTight();
	if (tau_againstElectronLoose_branch != 0) tau_againstElectronLoose();
	if (tau_isVetoTau_branch != 0) tau_isVetoTau();
	if (isoTracks_p4_branch != 0) isoTracks_p4();
	if (isoTracks_charge_branch != 0) isoTracks_charge();
	if (isoTracks_absIso_branch != 0) isoTracks_absIso();
	if (isoTracks_dz_branch != 0) isoTracks_dz();
	if (isoTracks_pdgId_branch != 0) isoTracks_pdgId();
	if (isoTracks_isVetoTrack_branch != 0) isoTracks_isVetoTrack();
	if (isoTracks_isVetoTrack_v2_branch != 0) isoTracks_isVetoTrack_v2();
	if (isoTracks_isVetoTrack_v3_branch != 0) isoTracks_isVetoTrack_v3();
}

	unsigned int &run()
	{
		if (not run_isLoaded) {
			if (run_branch != 0) {
				run_branch->GetEntry(index);
			} else { 
				printf("branch run_branch does not exist!\n");
				exit(1);
			}
			run_isLoaded = true;
		}
		return run_;
	}
	unsigned int &ls()
	{
		if (not ls_isLoaded) {
			if (ls_branch != 0) {
				ls_branch->GetEntry(index);
			} else { 
				printf("branch ls_branch does not exist!\n");
				exit(1);
			}
			ls_isLoaded = true;
		}
		return ls_;
	}
	unsigned int &evt()
	{
		if (not evt_isLoaded) {
			if (evt_branch != 0) {
				evt_branch->GetEntry(index);
			} else { 
				printf("branch evt_branch does not exist!\n");
				exit(1);
			}
			evt_isLoaded = true;
		}
		return evt_;
	}
	int &nvtxs()
	{
		if (not nvtxs_isLoaded) {
			if (nvtxs_branch != 0) {
				nvtxs_branch->GetEntry(index);
			} else { 
				printf("branch nvtxs_branch does not exist!\n");
				exit(1);
			}
			nvtxs_isLoaded = true;
		}
		return nvtxs_;
	}
	int &pu_nvtxs()
	{
		if (not pu_nvtxs_isLoaded) {
			if (pu_nvtxs_branch != 0) {
				pu_nvtxs_branch->GetEntry(index);
			} else { 
				printf("branch pu_nvtxs_branch does not exist!\n");
				exit(1);
			}
			pu_nvtxs_isLoaded = true;
		}
		return pu_nvtxs_;
	}
	float &pfmet()
	{
		if (not pfmet_isLoaded) {
			if (pfmet_branch != 0) {
				pfmet_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_branch does not exist!\n");
				exit(1);
			}
			pfmet_isLoaded = true;
		}
		return pfmet_;
	}
	float &pfmet_phi()
	{
		if (not pfmet_phi_isLoaded) {
			if (pfmet_phi_branch != 0) {
				pfmet_phi_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_phi_branch does not exist!\n");
				exit(1);
			}
			pfmet_phi_isLoaded = true;
		}
		return pfmet_phi_;
	}
	float &pfmet_rl()
	{
		if (not pfmet_rl_isLoaded) {
			if (pfmet_rl_branch != 0) {
				pfmet_rl_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_rl_branch does not exist!\n");
				exit(1);
			}
			pfmet_rl_isLoaded = true;
		}
		return pfmet_rl_;
	}
	float &pfmet_phi_rl()
	{
		if (not pfmet_phi_rl_isLoaded) {
			if (pfmet_phi_rl_branch != 0) {
				pfmet_phi_rl_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_phi_rl_branch does not exist!\n");
				exit(1);
			}
			pfmet_phi_rl_isLoaded = true;
		}
		return pfmet_phi_rl_;
	}
	float &scale1fb()
	{
		if (not scale1fb_isLoaded) {
			if (scale1fb_branch != 0) {
				scale1fb_branch->GetEntry(index);
			} else { 
				printf("branch scale1fb_branch does not exist!\n");
				exit(1);
			}
			scale1fb_isLoaded = true;
		}
		return scale1fb_;
	}
	float &xsec()
	{
		if (not xsec_isLoaded) {
			if (xsec_branch != 0) {
				xsec_branch->GetEntry(index);
			} else { 
				printf("branch xsec_branch does not exist!\n");
				exit(1);
			}
			xsec_isLoaded = true;
		}
		return xsec_;
	}
	float &xsec_uncert()
	{
		if (not xsec_uncert_isLoaded) {
			if (xsec_uncert_branch != 0) {
				xsec_uncert_branch->GetEntry(index);
			} else { 
				printf("branch xsec_uncert_branch does not exist!\n");
				exit(1);
			}
			xsec_uncert_isLoaded = true;
		}
		return xsec_uncert_;
	}
	float &kfactor()
	{
		if (not kfactor_isLoaded) {
			if (kfactor_branch != 0) {
				kfactor_branch->GetEntry(index);
			} else { 
				printf("branch kfactor_branch does not exist!\n");
				exit(1);
			}
			kfactor_isLoaded = true;
		}
		return kfactor_;
	}
	float &pu_ntrue()
	{
		if (not pu_ntrue_isLoaded) {
			if (pu_ntrue_branch != 0) {
				pu_ntrue_branch->GetEntry(index);
			} else { 
				printf("branch pu_ntrue_branch does not exist!\n");
				exit(1);
			}
			pu_ntrue_isLoaded = true;
		}
		return pu_ntrue_;
	}
	int &ngoodleps()
	{
		if (not ngoodleps_isLoaded) {
			if (ngoodleps_branch != 0) {
				ngoodleps_branch->GetEntry(index);
			} else { 
				printf("branch ngoodleps_branch does not exist!\n");
				exit(1);
			}
			ngoodleps_isLoaded = true;
		}
		return ngoodleps_;
	}
	int &nvetoleps()
	{
		if (not nvetoleps_isLoaded) {
			if (nvetoleps_branch != 0) {
				nvetoleps_branch->GetEntry(index);
			} else { 
				printf("branch nvetoleps_branch does not exist!\n");
				exit(1);
			}
			nvetoleps_isLoaded = true;
		}
		return nvetoleps_;
	}
	bool &	is_data()
	{
		if (not is_data_isLoaded) {
			if (is_data_branch != 0) {
				is_data_branch->GetEntry(index);
			} else { 
				printf("branch is_data_branch does not exist!\n");
				exit(1);
			}
			is_data_isLoaded = true;
		}
		return is_data_;
	}
	string &dataset()
	{
		if (not dataset_isLoaded) {
			if (dataset_branch != 0) {
				dataset_branch->GetEntry(index);
			} else { 
				printf("branch dataset_branch does not exist!\n");
				exit(1);
			}
			dataset_isLoaded = true;
		}
		return *dataset_;
	}
	string &filename()
	{
		if (not filename_isLoaded) {
			if (filename_branch != 0) {
				filename_branch->GetEntry(index);
			} else { 
				printf("branch filename_branch does not exist!\n");
				exit(1);
			}
			filename_isLoaded = true;
		}
		return *filename_;
	}
	string &cms3tag()
	{
		if (not cms3tag_isLoaded) {
			if (cms3tag_branch != 0) {
				cms3tag_branch->GetEntry(index);
			} else { 
				printf("branch cms3tag_branch does not exist!\n");
				exit(1);
			}
			cms3tag_isLoaded = true;
		}
		return *cms3tag_;
	}
	unsigned int &nEvents()
	{
		if (not nEvents_isLoaded) {
			if (nEvents_branch != 0) {
				nEvents_branch->GetEntry(index);
			} else { 
				printf("branch nEvents_branch does not exist!\n");
				exit(1);
			}
			nEvents_isLoaded = true;
		}
		return nEvents_;
	}
	unsigned int &nEvents_goodvtx()
	{
		if (not nEvents_goodvtx_isLoaded) {
			if (nEvents_goodvtx_branch != 0) {
				nEvents_goodvtx_branch->GetEntry(index);
			} else { 
				printf("branch nEvents_goodvtx_branch does not exist!\n");
				exit(1);
			}
			nEvents_goodvtx_isLoaded = true;
		}
		return nEvents_goodvtx_;
	}
	unsigned int &nEvents_MET30()
	{
		if (not nEvents_MET30_isLoaded) {
			if (nEvents_MET30_branch != 0) {
				nEvents_MET30_branch->GetEntry(index);
			} else { 
				printf("branch nEvents_MET30_branch does not exist!\n");
				exit(1);
			}
			nEvents_MET30_isLoaded = true;
		}
		return nEvents_MET30_;
	}
	unsigned int &nEvents_1goodlep()
	{
		if (not nEvents_1goodlep_isLoaded) {
			if (nEvents_1goodlep_branch != 0) {
				nEvents_1goodlep_branch->GetEntry(index);
			} else { 
				printf("branch nEvents_1goodlep_branch does not exist!\n");
				exit(1);
			}
			nEvents_1goodlep_isLoaded = true;
		}
		return nEvents_1goodlep_;
	}
	unsigned int &nEvents_2goodjets()
	{
		if (not nEvents_2goodjets_isLoaded) {
			if (nEvents_2goodjets_branch != 0) {
				nEvents_2goodjets_branch->GetEntry(index);
			} else { 
				printf("branch nEvents_2goodjets_branch does not exist!\n");
				exit(1);
			}
			nEvents_2goodjets_isLoaded = true;
		}
		return nEvents_2goodjets_;
	}
	int &is0lep()
	{
		if (not is0lep_isLoaded) {
			if (is0lep_branch != 0) {
				is0lep_branch->GetEntry(index);
			} else { 
				printf("branch is0lep_branch does not exist!\n");
				exit(1);
			}
			is0lep_isLoaded = true;
		}
		return is0lep_;
	}
	int &is1lep()
	{
		if (not is1lep_isLoaded) {
			if (is1lep_branch != 0) {
				is1lep_branch->GetEntry(index);
			} else { 
				printf("branch is1lep_branch does not exist!\n");
				exit(1);
			}
			is1lep_isLoaded = true;
		}
		return is1lep_;
	}
	int &is2lep()
	{
		if (not is2lep_isLoaded) {
			if (is2lep_branch != 0) {
				is2lep_branch->GetEntry(index);
			} else { 
				printf("branch is2lep_branch does not exist!\n");
				exit(1);
			}
			is2lep_isLoaded = true;
		}
		return is2lep_;
	}
	int &isZtoNuNu()
	{
		if (not isZtoNuNu_isLoaded) {
			if (isZtoNuNu_branch != 0) {
				isZtoNuNu_branch->GetEntry(index);
			} else { 
				printf("branch isZtoNuNu_branch does not exist!\n");
				exit(1);
			}
			isZtoNuNu_isLoaded = true;
		}
		return isZtoNuNu_;
	}
	int &is1lepFromW()
	{
		if (not is1lepFromW_isLoaded) {
			if (is1lepFromW_branch != 0) {
				is1lepFromW_branch->GetEntry(index);
			} else { 
				printf("branch is1lepFromW_branch does not exist!\n");
				exit(1);
			}
			is1lepFromW_isLoaded = true;
		}
		return is1lepFromW_;
	}
	int &is1lepFromTop()
	{
		if (not is1lepFromTop_isLoaded) {
			if (is1lepFromTop_branch != 0) {
				is1lepFromTop_branch->GetEntry(index);
			} else { 
				printf("branch is1lepFromTop_branch does not exist!\n");
				exit(1);
			}
			is1lepFromTop_isLoaded = true;
		}
		return is1lepFromTop_;
	}
	float &MT2W()
	{
		if (not MT2W_isLoaded) {
			if (MT2W_branch != 0) {
				MT2W_branch->GetEntry(index);
			} else { 
				printf("branch MT2W_branch does not exist!\n");
				exit(1);
			}
			MT2W_isLoaded = true;
		}
		return MT2W_;
	}
	float &MT2W_rl()
	{
		if (not MT2W_rl_isLoaded) {
			if (MT2W_rl_branch != 0) {
				MT2W_rl_branch->GetEntry(index);
			} else { 
				printf("branch MT2W_rl_branch does not exist!\n");
				exit(1);
			}
			MT2W_rl_isLoaded = true;
		}
		return MT2W_rl_;
	}
	float &mindphi_met_j1_j2()
	{
		if (not mindphi_met_j1_j2_isLoaded) {
			if (mindphi_met_j1_j2_branch != 0) {
				mindphi_met_j1_j2_branch->GetEntry(index);
			} else { 
				printf("branch mindphi_met_j1_j2_branch does not exist!\n");
				exit(1);
			}
			mindphi_met_j1_j2_isLoaded = true;
		}
		return mindphi_met_j1_j2_;
	}
	float &mindphi_met_j1_j2_rl()
	{
		if (not mindphi_met_j1_j2_rl_isLoaded) {
			if (mindphi_met_j1_j2_rl_branch != 0) {
				mindphi_met_j1_j2_rl_branch->GetEntry(index);
			} else { 
				printf("branch mindphi_met_j1_j2_rl_branch does not exist!\n");
				exit(1);
			}
			mindphi_met_j1_j2_rl_isLoaded = true;
		}
		return mindphi_met_j1_j2_rl_;
	}
	float &mt_met_lep()
	{
		if (not mt_met_lep_isLoaded) {
			if (mt_met_lep_branch != 0) {
				mt_met_lep_branch->GetEntry(index);
			} else { 
				printf("branch mt_met_lep_branch does not exist!\n");
				exit(1);
			}
			mt_met_lep_isLoaded = true;
		}
		return mt_met_lep_;
	}
	float &mt_met_lep_rl()
	{
		if (not mt_met_lep_rl_isLoaded) {
			if (mt_met_lep_rl_branch != 0) {
				mt_met_lep_rl_branch->GetEntry(index);
			} else { 
				printf("branch mt_met_lep_rl_branch does not exist!\n");
				exit(1);
			}
			mt_met_lep_rl_isLoaded = true;
		}
		return mt_met_lep_rl_;
	}
	float &hadronic_top_chi2()
	{
		if (not hadronic_top_chi2_isLoaded) {
			if (hadronic_top_chi2_branch != 0) {
				hadronic_top_chi2_branch->GetEntry(index);
			} else { 
				printf("branch hadronic_top_chi2_branch does not exist!\n");
				exit(1);
			}
			hadronic_top_chi2_isLoaded = true;
		}
		return hadronic_top_chi2_;
	}
	float &ak4pfjets_rho()
	{
		if (not ak4pfjets_rho_isLoaded) {
			if (ak4pfjets_rho_branch != 0) {
				ak4pfjets_rho_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_rho_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_rho_isLoaded = true;
		}
		return ak4pfjets_rho_;
	}
	float &pdf_up_weight()
	{
		if (not pdf_up_weight_isLoaded) {
			if (pdf_up_weight_branch != 0) {
				pdf_up_weight_branch->GetEntry(index);
			} else { 
				printf("branch pdf_up_weight_branch does not exist!\n");
				exit(1);
			}
			pdf_up_weight_isLoaded = true;
		}
		return pdf_up_weight_;
	}
	float &pdf_down_weight()
	{
		if (not pdf_down_weight_isLoaded) {
			if (pdf_down_weight_branch != 0) {
				pdf_down_weight_branch->GetEntry(index);
			} else { 
				printf("branch pdf_down_weight_branch does not exist!\n");
				exit(1);
			}
			pdf_down_weight_isLoaded = true;
		}
		return pdf_down_weight_;
	}
	const vector<string> &genweightsID()
	{
		if (not genweightsID_isLoaded) {
			if (genweightsID_branch != 0) {
				genweightsID_branch->GetEntry(index);
			} else { 
				printf("branch genweightsID_branch does not exist!\n");
				exit(1);
			}
			genweightsID_isLoaded = true;
		}
		return *genweightsID_;
	}
	const vector<float> &genweights()
	{
		if (not genweights_isLoaded) {
			if (genweights_branch != 0) {
				genweights_branch->GetEntry(index);
			} else { 
				printf("branch genweights_branch does not exist!\n");
				exit(1);
			}
			genweights_isLoaded = true;
		}
		return *genweights_;
	}
	float &weight_btagsf()
	{
		if (not weight_btagsf_isLoaded) {
			if (weight_btagsf_branch != 0) {
				weight_btagsf_branch->GetEntry(index);
			} else { 
				printf("branch weight_btagsf_branch does not exist!\n");
				exit(1);
			}
			weight_btagsf_isLoaded = true;
		}
		return weight_btagsf_;
	}
	float &weight_btagsf_heavy_UP()
	{
		if (not weight_btagsf_heavy_UP_isLoaded) {
			if (weight_btagsf_heavy_UP_branch != 0) {
				weight_btagsf_heavy_UP_branch->GetEntry(index);
			} else { 
				printf("branch weight_btagsf_heavy_UP_branch does not exist!\n");
				exit(1);
			}
			weight_btagsf_heavy_UP_isLoaded = true;
		}
		return weight_btagsf_heavy_UP_;
	}
	float &weight_btagsf_light_UP()
	{
		if (not weight_btagsf_light_UP_isLoaded) {
			if (weight_btagsf_light_UP_branch != 0) {
				weight_btagsf_light_UP_branch->GetEntry(index);
			} else { 
				printf("branch weight_btagsf_light_UP_branch does not exist!\n");
				exit(1);
			}
			weight_btagsf_light_UP_isLoaded = true;
		}
		return weight_btagsf_light_UP_;
	}
	float &weight_btagsf_heavy_DN()
	{
		if (not weight_btagsf_heavy_DN_isLoaded) {
			if (weight_btagsf_heavy_DN_branch != 0) {
				weight_btagsf_heavy_DN_branch->GetEntry(index);
			} else { 
				printf("branch weight_btagsf_heavy_DN_branch does not exist!\n");
				exit(1);
			}
			weight_btagsf_heavy_DN_isLoaded = true;
		}
		return weight_btagsf_heavy_DN_;
	}
	float &weight_btagsf_light_DN()
	{
		if (not weight_btagsf_light_DN_isLoaded) {
			if (weight_btagsf_light_DN_branch != 0) {
				weight_btagsf_light_DN_branch->GetEntry(index);
			} else { 
				printf("branch weight_btagsf_light_DN_branch does not exist!\n");
				exit(1);
			}
			weight_btagsf_light_DN_isLoaded = true;
		}
		return weight_btagsf_light_DN_;
	}
	float &weight_btagsf_fastsim_UP()
	{
		if (not weight_btagsf_fastsim_UP_isLoaded) {
			if (weight_btagsf_fastsim_UP_branch != 0) {
				weight_btagsf_fastsim_UP_branch->GetEntry(index);
			} else { 
				printf("branch weight_btagsf_fastsim_UP_branch does not exist!\n");
				exit(1);
			}
			weight_btagsf_fastsim_UP_isLoaded = true;
		}
		return weight_btagsf_fastsim_UP_;
	}
	float &weight_btagsf_fastsim_DN()
	{
		if (not weight_btagsf_fastsim_DN_isLoaded) {
			if (weight_btagsf_fastsim_DN_branch != 0) {
				weight_btagsf_fastsim_DN_branch->GetEntry(index);
			} else { 
				printf("branch weight_btagsf_fastsim_DN_branch does not exist!\n");
				exit(1);
			}
			weight_btagsf_fastsim_DN_isLoaded = true;
		}
		return weight_btagsf_fastsim_DN_;
	}
	float &weight_lepSF()
	{
		if (not weight_lepSF_isLoaded) {
			if (weight_lepSF_branch != 0) {
				weight_lepSF_branch->GetEntry(index);
			} else { 
				printf("branch weight_lepSF_branch does not exist!\n");
				exit(1);
			}
			weight_lepSF_isLoaded = true;
		}
		return weight_lepSF_;
	}
	float &weight_lepSF_up()
	{
		if (not weight_lepSF_up_isLoaded) {
			if (weight_lepSF_up_branch != 0) {
				weight_lepSF_up_branch->GetEntry(index);
			} else { 
				printf("branch weight_lepSF_up_branch does not exist!\n");
				exit(1);
			}
			weight_lepSF_up_isLoaded = true;
		}
		return weight_lepSF_up_;
	}
	float &weight_lepSF_down()
	{
		if (not weight_lepSF_down_isLoaded) {
			if (weight_lepSF_down_branch != 0) {
				weight_lepSF_down_branch->GetEntry(index);
			} else { 
				printf("branch weight_lepSF_down_branch does not exist!\n");
				exit(1);
			}
			weight_lepSF_down_isLoaded = true;
		}
		return weight_lepSF_down_;
	}
	float &weight_vetoLepSF()
	{
		if (not weight_vetoLepSF_isLoaded) {
			if (weight_vetoLepSF_branch != 0) {
				weight_vetoLepSF_branch->GetEntry(index);
			} else { 
				printf("branch weight_vetoLepSF_branch does not exist!\n");
				exit(1);
			}
			weight_vetoLepSF_isLoaded = true;
		}
		return weight_vetoLepSF_;
	}
	float &weight_vetoLepSF_up()
	{
		if (not weight_vetoLepSF_up_isLoaded) {
			if (weight_vetoLepSF_up_branch != 0) {
				weight_vetoLepSF_up_branch->GetEntry(index);
			} else { 
				printf("branch weight_vetoLepSF_up_branch does not exist!\n");
				exit(1);
			}
			weight_vetoLepSF_up_isLoaded = true;
		}
		return weight_vetoLepSF_up_;
	}
	float &weight_vetoLepSF_down()
	{
		if (not weight_vetoLepSF_down_isLoaded) {
			if (weight_vetoLepSF_down_branch != 0) {
				weight_vetoLepSF_down_branch->GetEntry(index);
			} else { 
				printf("branch weight_vetoLepSF_down_branch does not exist!\n");
				exit(1);
			}
			weight_vetoLepSF_down_isLoaded = true;
		}
		return weight_vetoLepSF_down_;
	}
	float &weight_lepSF_fastSim()
	{
		if (not weight_lepSF_fastSim_isLoaded) {
			if (weight_lepSF_fastSim_branch != 0) {
				weight_lepSF_fastSim_branch->GetEntry(index);
			} else { 
				printf("branch weight_lepSF_fastSim_branch does not exist!\n");
				exit(1);
			}
			weight_lepSF_fastSim_isLoaded = true;
		}
		return weight_lepSF_fastSim_;
	}
	float &weight_lepSF_fastSim_up()
	{
		if (not weight_lepSF_fastSim_up_isLoaded) {
			if (weight_lepSF_fastSim_up_branch != 0) {
				weight_lepSF_fastSim_up_branch->GetEntry(index);
			} else { 
				printf("branch weight_lepSF_fastSim_up_branch does not exist!\n");
				exit(1);
			}
			weight_lepSF_fastSim_up_isLoaded = true;
		}
		return weight_lepSF_fastSim_up_;
	}
	float &weight_lepSF_fastSim_down()
	{
		if (not weight_lepSF_fastSim_down_isLoaded) {
			if (weight_lepSF_fastSim_down_branch != 0) {
				weight_lepSF_fastSim_down_branch->GetEntry(index);
			} else { 
				printf("branch weight_lepSF_fastSim_down_branch does not exist!\n");
				exit(1);
			}
			weight_lepSF_fastSim_down_isLoaded = true;
		}
		return weight_lepSF_fastSim_down_;
	}
	float &weight_ISR()
	{
		if (not weight_ISR_isLoaded) {
			if (weight_ISR_branch != 0) {
				weight_ISR_branch->GetEntry(index);
			} else { 
				printf("branch weight_ISR_branch does not exist!\n");
				exit(1);
			}
			weight_ISR_isLoaded = true;
		}
		return weight_ISR_;
	}
	float &weight_ISRup()
	{
		if (not weight_ISRup_isLoaded) {
			if (weight_ISRup_branch != 0) {
				weight_ISRup_branch->GetEntry(index);
			} else { 
				printf("branch weight_ISRup_branch does not exist!\n");
				exit(1);
			}
			weight_ISRup_isLoaded = true;
		}
		return weight_ISRup_;
	}
	float &weight_ISRdown()
	{
		if (not weight_ISRdown_isLoaded) {
			if (weight_ISRdown_branch != 0) {
				weight_ISRdown_branch->GetEntry(index);
			} else { 
				printf("branch weight_ISRdown_branch does not exist!\n");
				exit(1);
			}
			weight_ISRdown_isLoaded = true;
		}
		return weight_ISRdown_;
	}
	float &weight_PU()
	{
		if (not weight_PU_isLoaded) {
			if (weight_PU_branch != 0) {
				weight_PU_branch->GetEntry(index);
			} else { 
				printf("branch weight_PU_branch does not exist!\n");
				exit(1);
			}
			weight_PU_isLoaded = true;
		}
		return weight_PU_;
	}
	float &weight_PUup()
	{
		if (not weight_PUup_isLoaded) {
			if (weight_PUup_branch != 0) {
				weight_PUup_branch->GetEntry(index);
			} else { 
				printf("branch weight_PUup_branch does not exist!\n");
				exit(1);
			}
			weight_PUup_isLoaded = true;
		}
		return weight_PUup_;
	}
	float &weight_PUdown()
	{
		if (not weight_PUdown_isLoaded) {
			if (weight_PUdown_branch != 0) {
				weight_PUdown_branch->GetEntry(index);
			} else { 
				printf("branch weight_PUdown_branch does not exist!\n");
				exit(1);
			}
			weight_PUdown_isLoaded = true;
		}
		return weight_PUdown_;
	}
	const vector<string> &sparms_names()
	{
		if (not sparms_names_isLoaded) {
			if (sparms_names_branch != 0) {
				sparms_names_branch->GetEntry(index);
			} else { 
				printf("branch sparms_names_branch does not exist!\n");
				exit(1);
			}
			sparms_names_isLoaded = true;
		}
		return *sparms_names_;
	}
	const vector<float> &sparms_values()
	{
		if (not sparms_values_isLoaded) {
			if (sparms_values_branch != 0) {
				sparms_values_branch->GetEntry(index);
			} else { 
				printf("branch sparms_values_branch does not exist!\n");
				exit(1);
			}
			sparms_values_isLoaded = true;
		}
		return *sparms_values_;
	}
	int &sparms_subProcessId()
	{
		if (not sparms_subProcessId_isLoaded) {
			if (sparms_subProcessId_branch != 0) {
				sparms_subProcessId_branch->GetEntry(index);
			} else { 
				printf("branch sparms_subProcessId_branch does not exist!\n");
				exit(1);
			}
			sparms_subProcessId_isLoaded = true;
		}
		return sparms_subProcessId_;
	}
	float &mass_lsp()
	{
		if (not mass_lsp_isLoaded) {
			if (mass_lsp_branch != 0) {
				mass_lsp_branch->GetEntry(index);
			} else { 
				printf("branch mass_lsp_branch does not exist!\n");
				exit(1);
			}
			mass_lsp_isLoaded = true;
		}
		return mass_lsp_;
	}
	float &mass_chargino()
	{
		if (not mass_chargino_isLoaded) {
			if (mass_chargino_branch != 0) {
				mass_chargino_branch->GetEntry(index);
			} else { 
				printf("branch mass_chargino_branch does not exist!\n");
				exit(1);
			}
			mass_chargino_isLoaded = true;
		}
		return mass_chargino_;
	}
	float &mass_stop()
	{
		if (not mass_stop_isLoaded) {
			if (mass_stop_branch != 0) {
				mass_stop_branch->GetEntry(index);
			} else { 
				printf("branch mass_stop_branch does not exist!\n");
				exit(1);
			}
			mass_stop_isLoaded = true;
		}
		return mass_stop_;
	}
	float &mass_gluino()
	{
		if (not mass_gluino_isLoaded) {
			if (mass_gluino_branch != 0) {
				mass_gluino_branch->GetEntry(index);
			} else { 
				printf("branch mass_gluino_branch does not exist!\n");
				exit(1);
			}
			mass_gluino_isLoaded = true;
		}
		return mass_gluino_;
	}
	float &genmet()
	{
		if (not genmet_isLoaded) {
			if (genmet_branch != 0) {
				genmet_branch->GetEntry(index);
			} else { 
				printf("branch genmet_branch does not exist!\n");
				exit(1);
			}
			genmet_isLoaded = true;
		}
		return genmet_;
	}
	float &genmet_phi()
	{
		if (not genmet_phi_isLoaded) {
			if (genmet_phi_branch != 0) {
				genmet_phi_branch->GetEntry(index);
			} else { 
				printf("branch genmet_phi_branch does not exist!\n");
				exit(1);
			}
			genmet_phi_isLoaded = true;
		}
		return genmet_phi_;
	}
	float &nupt()
	{
		if (not nupt_isLoaded) {
			if (nupt_branch != 0) {
				nupt_branch->GetEntry(index);
			} else { 
				printf("branch nupt_branch does not exist!\n");
				exit(1);
			}
			nupt_isLoaded = true;
		}
		return nupt_;
	}
	float &genht()
	{
		if (not genht_isLoaded) {
			if (genht_branch != 0) {
				genht_branch->GetEntry(index);
			} else { 
				printf("branch genht_branch does not exist!\n");
				exit(1);
			}
			genht_isLoaded = true;
		}
		return genht_;
	}
	bool &	PassTrackVeto()
	{
		if (not PassTrackVeto_isLoaded) {
			if (PassTrackVeto_branch != 0) {
				PassTrackVeto_branch->GetEntry(index);
			} else { 
				printf("branch PassTrackVeto_branch does not exist!\n");
				exit(1);
			}
			PassTrackVeto_isLoaded = true;
		}
		return PassTrackVeto_;
	}
	bool &	PassTauVeto()
	{
		if (not PassTauVeto_isLoaded) {
			if (PassTauVeto_branch != 0) {
				PassTauVeto_branch->GetEntry(index);
			} else { 
				printf("branch PassTauVeto_branch does not exist!\n");
				exit(1);
			}
			PassTauVeto_isLoaded = true;
		}
		return PassTauVeto_;
	}
	float &topness()
	{
		if (not topness_isLoaded) {
			if (topness_branch != 0) {
				topness_branch->GetEntry(index);
			} else { 
				printf("branch topness_branch does not exist!\n");
				exit(1);
			}
			topness_isLoaded = true;
		}
		return topness_;
	}
	float &topnessMod()
	{
		if (not topnessMod_isLoaded) {
			if (topnessMod_branch != 0) {
				topnessMod_branch->GetEntry(index);
			} else { 
				printf("branch topnessMod_branch does not exist!\n");
				exit(1);
			}
			topnessMod_isLoaded = true;
		}
		return topnessMod_;
	}
	float &topnessMod_rl()
	{
		if (not topnessMod_rl_isLoaded) {
			if (topnessMod_rl_branch != 0) {
				topnessMod_rl_branch->GetEntry(index);
			} else { 
				printf("branch topnessMod_rl_branch does not exist!\n");
				exit(1);
			}
			topnessMod_rl_isLoaded = true;
		}
		return topnessMod_rl_;
	}
	float &Mlb_closestb()
	{
		if (not Mlb_closestb_isLoaded) {
			if (Mlb_closestb_branch != 0) {
				Mlb_closestb_branch->GetEntry(index);
			} else { 
				printf("branch Mlb_closestb_branch does not exist!\n");
				exit(1);
			}
			Mlb_closestb_isLoaded = true;
		}
		return Mlb_closestb_;
	}
	int &HLT_SingleEl()
	{
		if (not HLT_SingleEl_isLoaded) {
			if (HLT_SingleEl_branch != 0) {
				HLT_SingleEl_branch->GetEntry(index);
			} else { 
				printf("branch HLT_SingleEl_branch does not exist!\n");
				exit(1);
			}
			HLT_SingleEl_isLoaded = true;
		}
		return HLT_SingleEl_;
	}
	int &HLT_SingleMu()
	{
		if (not HLT_SingleMu_isLoaded) {
			if (HLT_SingleMu_branch != 0) {
				HLT_SingleMu_branch->GetEntry(index);
			} else { 
				printf("branch HLT_SingleMu_branch does not exist!\n");
				exit(1);
			}
			HLT_SingleMu_isLoaded = true;
		}
		return HLT_SingleMu_;
	}
	int &HLT_MET()
	{
		if (not HLT_MET_isLoaded) {
			if (HLT_MET_branch != 0) {
				HLT_MET_branch->GetEntry(index);
			} else { 
				printf("branch HLT_MET_branch does not exist!\n");
				exit(1);
			}
			HLT_MET_isLoaded = true;
		}
		return HLT_MET_;
	}
	int &HLT_MET100_MHT100()
	{
		if (not HLT_MET100_MHT100_isLoaded) {
			if (HLT_MET100_MHT100_branch != 0) {
				HLT_MET100_MHT100_branch->GetEntry(index);
			} else { 
				printf("branch HLT_MET100_MHT100_branch does not exist!\n");
				exit(1);
			}
			HLT_MET100_MHT100_isLoaded = true;
		}
		return HLT_MET100_MHT100_;
	}
	int &HLT_DiEl()
	{
		if (not HLT_DiEl_isLoaded) {
			if (HLT_DiEl_branch != 0) {
				HLT_DiEl_branch->GetEntry(index);
			} else { 
				printf("branch HLT_DiEl_branch does not exist!\n");
				exit(1);
			}
			HLT_DiEl_isLoaded = true;
		}
		return HLT_DiEl_;
	}
	int &HLT_DiMu()
	{
		if (not HLT_DiMu_isLoaded) {
			if (HLT_DiMu_branch != 0) {
				HLT_DiMu_branch->GetEntry(index);
			} else { 
				printf("branch HLT_DiMu_branch does not exist!\n");
				exit(1);
			}
			HLT_DiMu_isLoaded = true;
		}
		return HLT_DiMu_;
	}
	int &HLT_MuE()
	{
		if (not HLT_MuE_isLoaded) {
			if (HLT_MuE_branch != 0) {
				HLT_MuE_branch->GetEntry(index);
			} else { 
				printf("branch HLT_MuE_branch does not exist!\n");
				exit(1);
			}
			HLT_MuE_isLoaded = true;
		}
		return HLT_MuE_;
	}
	int &HLT_Photon90_CaloIdL_PFHT500()
	{
		if (not HLT_Photon90_CaloIdL_PFHT500_isLoaded) {
			if (HLT_Photon90_CaloIdL_PFHT500_branch != 0) {
				HLT_Photon90_CaloIdL_PFHT500_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon90_CaloIdL_PFHT500_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon90_CaloIdL_PFHT500_isLoaded = true;
		}
		return HLT_Photon90_CaloIdL_PFHT500_;
	}
	int &HLT_Photon22_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon22_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon22_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon22_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon22_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon22_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon22_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon30_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon30_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon30_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon30_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon30_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon30_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon30_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon36_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon36_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon36_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon36_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon36_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon36_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon36_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon50_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon50_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon50_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon50_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon50_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon50_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon50_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon75_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon75_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon75_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon75_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon75_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon75_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon75_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon90_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon90_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon90_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon90_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon90_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon90_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon90_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon120_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon120_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon120_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon120_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon120_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon120_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon120_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon165_R9Id90_HE10_IsoM()
	{
		if (not HLT_Photon165_R9Id90_HE10_IsoM_isLoaded) {
			if (HLT_Photon165_R9Id90_HE10_IsoM_branch != 0) {
				HLT_Photon165_R9Id90_HE10_IsoM_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon165_R9Id90_HE10_IsoM_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon165_R9Id90_HE10_IsoM_isLoaded = true;
		}
		return HLT_Photon165_R9Id90_HE10_IsoM_;
	}
	int &HLT_Photon175()
	{
		if (not HLT_Photon175_isLoaded) {
			if (HLT_Photon175_branch != 0) {
				HLT_Photon175_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon175_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon175_isLoaded = true;
		}
		return HLT_Photon175_;
	}
	int &HLT_Photon165_HE10()
	{
		if (not HLT_Photon165_HE10_isLoaded) {
			if (HLT_Photon165_HE10_branch != 0) {
				HLT_Photon165_HE10_branch->GetEntry(index);
			} else { 
				printf("branch HLT_Photon165_HE10_branch does not exist!\n");
				exit(1);
			}
			HLT_Photon165_HE10_isLoaded = true;
		}
		return HLT_Photon165_HE10_;
	}
	int &nPhotons()
	{
		if (not nPhotons_isLoaded) {
			if (nPhotons_branch != 0) {
				nPhotons_branch->GetEntry(index);
			} else { 
				printf("branch nPhotons_branch does not exist!\n");
				exit(1);
			}
			nPhotons_isLoaded = true;
		}
		return nPhotons_;
	}
	int &ph_ngoodjets()
	{
		if (not ph_ngoodjets_isLoaded) {
			if (ph_ngoodjets_branch != 0) {
				ph_ngoodjets_branch->GetEntry(index);
			} else { 
				printf("branch ph_ngoodjets_branch does not exist!\n");
				exit(1);
			}
			ph_ngoodjets_isLoaded = true;
		}
		return ph_ngoodjets_;
	}
	int &ph_ngoodbtags()
	{
		if (not ph_ngoodbtags_isLoaded) {
			if (ph_ngoodbtags_branch != 0) {
				ph_ngoodbtags_branch->GetEntry(index);
			} else { 
				printf("branch ph_ngoodbtags_branch does not exist!\n");
				exit(1);
			}
			ph_ngoodbtags_isLoaded = true;
		}
		return ph_ngoodbtags_;
	}
	float &filt_met()
	{
		if (not filt_met_isLoaded) {
			if (filt_met_branch != 0) {
				filt_met_branch->GetEntry(index);
			} else { 
				printf("branch filt_met_branch does not exist!\n");
				exit(1);
			}
			filt_met_isLoaded = true;
		}
		return filt_met_;
	}
	float &hardgenpt()
	{
		if (not hardgenpt_isLoaded) {
			if (hardgenpt_branch != 0) {
				hardgenpt_branch->GetEntry(index);
			} else { 
				printf("branch hardgenpt_branch does not exist!\n");
				exit(1);
			}
			hardgenpt_isLoaded = true;
		}
		return hardgenpt_;
	}
	float &filt_badChargedCandidateFilter()
	{
		if (not filt_badChargedCandidateFilter_isLoaded) {
			if (filt_badChargedCandidateFilter_branch != 0) {
				filt_badChargedCandidateFilter_branch->GetEntry(index);
			} else { 
				printf("branch filt_badChargedCandidateFilter_branch does not exist!\n");
				exit(1);
			}
			filt_badChargedCandidateFilter_isLoaded = true;
		}
		return filt_badChargedCandidateFilter_;
	}
	float &filt_badMuonFilter()
	{
		if (not filt_badMuonFilter_isLoaded) {
			if (filt_badMuonFilter_branch != 0) {
				filt_badMuonFilter_branch->GetEntry(index);
			} else { 
				printf("branch filt_badMuonFilter_branch does not exist!\n");
				exit(1);
			}
			filt_badMuonFilter_isLoaded = true;
		}
		return filt_badMuonFilter_;
	}
	float &calomet()
	{
		if (not calomet_isLoaded) {
			if (calomet_branch != 0) {
				calomet_branch->GetEntry(index);
			} else { 
				printf("branch calomet_branch does not exist!\n");
				exit(1);
			}
			calomet_isLoaded = true;
		}
		return calomet_;
	}
	float &calomet_phi()
	{
		if (not calomet_phi_isLoaded) {
			if (calomet_phi_branch != 0) {
				calomet_phi_branch->GetEntry(index);
			} else { 
				printf("branch calomet_phi_branch does not exist!\n");
				exit(1);
			}
			calomet_phi_isLoaded = true;
		}
		return calomet_phi_;
	}
	int &lep1_pdgid()
	{
		if (not lep1_pdgid_isLoaded) {
			if (lep1_pdgid_branch != 0) {
				lep1_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch lep1_pdgid_branch does not exist!\n");
				exit(1);
			}
			lep1_pdgid_isLoaded = true;
		}
		return lep1_pdgid_;
	}
	int &lep1_production_type()
	{
		if (not lep1_production_type_isLoaded) {
			if (lep1_production_type_branch != 0) {
				lep1_production_type_branch->GetEntry(index);
			} else { 
				printf("branch lep1_production_type_branch does not exist!\n");
				exit(1);
			}
			lep1_production_type_isLoaded = true;
		}
		return lep1_production_type_;
	}
	float &lep1_MiniIso()
	{
		if (not lep1_MiniIso_isLoaded) {
			if (lep1_MiniIso_branch != 0) {
				lep1_MiniIso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_MiniIso_branch does not exist!\n");
				exit(1);
			}
			lep1_MiniIso_isLoaded = true;
		}
		return lep1_MiniIso_;
	}
	float &lep1_relIso()
	{
		if (not lep1_relIso_isLoaded) {
			if (lep1_relIso_branch != 0) {
				lep1_relIso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_relIso_branch does not exist!\n");
				exit(1);
			}
			lep1_relIso_isLoaded = true;
		}
		return lep1_relIso_;
	}
	bool &	lep1_passLooseID()
	{
		if (not lep1_passLooseID_isLoaded) {
			if (lep1_passLooseID_branch != 0) {
				lep1_passLooseID_branch->GetEntry(index);
			} else { 
				printf("branch lep1_passLooseID_branch does not exist!\n");
				exit(1);
			}
			lep1_passLooseID_isLoaded = true;
		}
		return lep1_passLooseID_;
	}
	bool &	lep1_passMediumID()
	{
		if (not lep1_passMediumID_isLoaded) {
			if (lep1_passMediumID_branch != 0) {
				lep1_passMediumID_branch->GetEntry(index);
			} else { 
				printf("branch lep1_passMediumID_branch does not exist!\n");
				exit(1);
			}
			lep1_passMediumID_isLoaded = true;
		}
		return lep1_passMediumID_;
	}
	bool &	lep1_passTightID()
	{
		if (not lep1_passTightID_isLoaded) {
			if (lep1_passTightID_branch != 0) {
				lep1_passTightID_branch->GetEntry(index);
			} else { 
				printf("branch lep1_passTightID_branch does not exist!\n");
				exit(1);
			}
			lep1_passTightID_isLoaded = true;
		}
		return lep1_passTightID_;
	}
	bool &	lep1_passVeto()
	{
		if (not lep1_passVeto_isLoaded) {
			if (lep1_passVeto_branch != 0) {
				lep1_passVeto_branch->GetEntry(index);
			} else { 
				printf("branch lep1_passVeto_branch does not exist!\n");
				exit(1);
			}
			lep1_passVeto_isLoaded = true;
		}
		return lep1_passVeto_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4()
	{
		if (not lep1_p4_isLoaded) {
			if (lep1_p4_branch != 0) {
				lep1_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_p4_isLoaded = true;
		}
		return *lep1_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4()
	{
		if (not lep1_mcp4_isLoaded) {
			if (lep1_mcp4_branch != 0) {
				lep1_mcp4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mcp4_branch does not exist!\n");
				exit(1);
			}
			lep1_mcp4_isLoaded = true;
		}
		return *lep1_mcp4_;
	}
	int &lep1_mc_motherid()
	{
		if (not lep1_mc_motherid_isLoaded) {
			if (lep1_mc_motherid_branch != 0) {
				lep1_mc_motherid_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mc_motherid_branch does not exist!\n");
				exit(1);
			}
			lep1_mc_motherid_isLoaded = true;
		}
		return lep1_mc_motherid_;
	}
	int &lep2_pdgid()
	{
		if (not lep2_pdgid_isLoaded) {
			if (lep2_pdgid_branch != 0) {
				lep2_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch lep2_pdgid_branch does not exist!\n");
				exit(1);
			}
			lep2_pdgid_isLoaded = true;
		}
		return lep2_pdgid_;
	}
	int &lep2_production_type()
	{
		if (not lep2_production_type_isLoaded) {
			if (lep2_production_type_branch != 0) {
				lep2_production_type_branch->GetEntry(index);
			} else { 
				printf("branch lep2_production_type_branch does not exist!\n");
				exit(1);
			}
			lep2_production_type_isLoaded = true;
		}
		return lep2_production_type_;
	}
	float &lep2_MiniIso()
	{
		if (not lep2_MiniIso_isLoaded) {
			if (lep2_MiniIso_branch != 0) {
				lep2_MiniIso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_MiniIso_branch does not exist!\n");
				exit(1);
			}
			lep2_MiniIso_isLoaded = true;
		}
		return lep2_MiniIso_;
	}
	float &lep2_relIso()
	{
		if (not lep2_relIso_isLoaded) {
			if (lep2_relIso_branch != 0) {
				lep2_relIso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_relIso_branch does not exist!\n");
				exit(1);
			}
			lep2_relIso_isLoaded = true;
		}
		return lep2_relIso_;
	}
	bool &	lep2_passLooseID()
	{
		if (not lep2_passLooseID_isLoaded) {
			if (lep2_passLooseID_branch != 0) {
				lep2_passLooseID_branch->GetEntry(index);
			} else { 
				printf("branch lep2_passLooseID_branch does not exist!\n");
				exit(1);
			}
			lep2_passLooseID_isLoaded = true;
		}
		return lep2_passLooseID_;
	}
	bool &	lep2_passMediumID()
	{
		if (not lep2_passMediumID_isLoaded) {
			if (lep2_passMediumID_branch != 0) {
				lep2_passMediumID_branch->GetEntry(index);
			} else { 
				printf("branch lep2_passMediumID_branch does not exist!\n");
				exit(1);
			}
			lep2_passMediumID_isLoaded = true;
		}
		return lep2_passMediumID_;
	}
	bool &	lep2_passTightID()
	{
		if (not lep2_passTightID_isLoaded) {
			if (lep2_passTightID_branch != 0) {
				lep2_passTightID_branch->GetEntry(index);
			} else { 
				printf("branch lep2_passTightID_branch does not exist!\n");
				exit(1);
			}
			lep2_passTightID_isLoaded = true;
		}
		return lep2_passTightID_;
	}
	bool &	lep2_passVeto()
	{
		if (not lep2_passVeto_isLoaded) {
			if (lep2_passVeto_branch != 0) {
				lep2_passVeto_branch->GetEntry(index);
			} else { 
				printf("branch lep2_passVeto_branch does not exist!\n");
				exit(1);
			}
			lep2_passVeto_isLoaded = true;
		}
		return lep2_passVeto_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4()
	{
		if (not lep2_p4_isLoaded) {
			if (lep2_p4_branch != 0) {
				lep2_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_p4_isLoaded = true;
		}
		return *lep2_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4()
	{
		if (not lep2_mcp4_isLoaded) {
			if (lep2_mcp4_branch != 0) {
				lep2_mcp4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mcp4_branch does not exist!\n");
				exit(1);
			}
			lep2_mcp4_isLoaded = true;
		}
		return *lep2_mcp4_;
	}
	int &lep2_mc_motherid()
	{
		if (not lep2_mc_motherid_isLoaded) {
			if (lep2_mc_motherid_branch != 0) {
				lep2_mc_motherid_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mc_motherid_branch does not exist!\n");
				exit(1);
			}
			lep2_mc_motherid_isLoaded = true;
		}
		return lep2_mc_motherid_;
	}
	const vector<float> &ph_sigmaIEtaEta_fill5x5()
	{
		if (not ph_sigmaIEtaEta_fill5x5_isLoaded) {
			if (ph_sigmaIEtaEta_fill5x5_branch != 0) {
				ph_sigmaIEtaEta_fill5x5_branch->GetEntry(index);
			} else { 
				printf("branch ph_sigmaIEtaEta_fill5x5_branch does not exist!\n");
				exit(1);
			}
			ph_sigmaIEtaEta_fill5x5_isLoaded = true;
		}
		return *ph_sigmaIEtaEta_fill5x5_;
	}
	const vector<float> &ph_hOverE()
	{
		if (not ph_hOverE_isLoaded) {
			if (ph_hOverE_branch != 0) {
				ph_hOverE_branch->GetEntry(index);
			} else { 
				printf("branch ph_hOverE_branch does not exist!\n");
				exit(1);
			}
			ph_hOverE_isLoaded = true;
		}
		return *ph_hOverE_;
	}
	const vector<float> &ph_r9()
	{
		if (not ph_r9_isLoaded) {
			if (ph_r9_branch != 0) {
				ph_r9_branch->GetEntry(index);
			} else { 
				printf("branch ph_r9_branch does not exist!\n");
				exit(1);
			}
			ph_r9_isLoaded = true;
		}
		return *ph_r9_;
	}
	const vector<float> &ph_chiso()
	{
		if (not ph_chiso_isLoaded) {
			if (ph_chiso_branch != 0) {
				ph_chiso_branch->GetEntry(index);
			} else { 
				printf("branch ph_chiso_branch does not exist!\n");
				exit(1);
			}
			ph_chiso_isLoaded = true;
		}
		return *ph_chiso_;
	}
	const vector<float> &ph_nhiso()
	{
		if (not ph_nhiso_isLoaded) {
			if (ph_nhiso_branch != 0) {
				ph_nhiso_branch->GetEntry(index);
			} else { 
				printf("branch ph_nhiso_branch does not exist!\n");
				exit(1);
			}
			ph_nhiso_isLoaded = true;
		}
		return *ph_nhiso_;
	}
	const vector<float> &ph_phiso()
	{
		if (not ph_phiso_isLoaded) {
			if (ph_phiso_branch != 0) {
				ph_phiso_branch->GetEntry(index);
			} else { 
				printf("branch ph_phiso_branch does not exist!\n");
				exit(1);
			}
			ph_phiso_isLoaded = true;
		}
		return *ph_phiso_;
	}
	const vector<bool> &ph_idCutBased()
	{
		if (not ph_idCutBased_isLoaded) {
			if (ph_idCutBased_branch != 0) {
				ph_idCutBased_branch->GetEntry(index);
			} else { 
				printf("branch ph_idCutBased_branch does not exist!\n");
				exit(1);
			}
			ph_idCutBased_isLoaded = true;
		}
		return *ph_idCutBased_;
	}
	const vector<int> &ph_overlapJetId()
	{
		if (not ph_overlapJetId_isLoaded) {
			if (ph_overlapJetId_branch != 0) {
				ph_overlapJetId_branch->GetEntry(index);
			} else { 
				printf("branch ph_overlapJetId_branch does not exist!\n");
				exit(1);
			}
			ph_overlapJetId_isLoaded = true;
		}
		return *ph_overlapJetId_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ph_p4()
	{
		if (not ph_p4_isLoaded) {
			if (ph_p4_branch != 0) {
				ph_p4_branch->GetEntry(index);
			} else { 
				printf("branch ph_p4_branch does not exist!\n");
				exit(1);
			}
			ph_p4_isLoaded = true;
		}
		return *ph_p4_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ph_mcp4()
	{
		if (not ph_mcp4_isLoaded) {
			if (ph_mcp4_branch != 0) {
				ph_mcp4_branch->GetEntry(index);
			} else { 
				printf("branch ph_mcp4_branch does not exist!\n");
				exit(1);
			}
			ph_mcp4_isLoaded = true;
		}
		return *ph_mcp4_;
	}
	const vector<float> &ph_pt()
	{
		if (not ph_pt_isLoaded) {
			if (ph_pt_branch != 0) {
				ph_pt_branch->GetEntry(index);
			} else { 
				printf("branch ph_pt_branch does not exist!\n");
				exit(1);
			}
			ph_pt_isLoaded = true;
		}
		return *ph_pt_;
	}
	const vector<float> &ph_eta()
	{
		if (not ph_eta_isLoaded) {
			if (ph_eta_branch != 0) {
				ph_eta_branch->GetEntry(index);
			} else { 
				printf("branch ph_eta_branch does not exist!\n");
				exit(1);
			}
			ph_eta_isLoaded = true;
		}
		return *ph_eta_;
	}
	const vector<float> &ph_phi()
	{
		if (not ph_phi_isLoaded) {
			if (ph_phi_branch != 0) {
				ph_phi_branch->GetEntry(index);
			} else { 
				printf("branch ph_phi_branch does not exist!\n");
				exit(1);
			}
			ph_phi_isLoaded = true;
		}
		return *ph_phi_;
	}
	const vector<float> &ph_mass()
	{
		if (not ph_mass_isLoaded) {
			if (ph_mass_branch != 0) {
				ph_mass_branch->GetEntry(index);
			} else { 
				printf("branch ph_mass_branch does not exist!\n");
				exit(1);
			}
			ph_mass_isLoaded = true;
		}
		return *ph_mass_;
	}
	const vector<int> &ph_mcMatchId()
	{
		if (not ph_mcMatchId_isLoaded) {
			if (ph_mcMatchId_branch != 0) {
				ph_mcMatchId_branch->GetEntry(index);
			} else { 
				printf("branch ph_mcMatchId_branch does not exist!\n");
				exit(1);
			}
			ph_mcMatchId_isLoaded = true;
		}
		return *ph_mcMatchId_;
	}
	const vector<float> &ph_genIso04()
	{
		if (not ph_genIso04_isLoaded) {
			if (ph_genIso04_branch != 0) {
				ph_genIso04_branch->GetEntry(index);
			} else { 
				printf("branch ph_genIso04_branch does not exist!\n");
				exit(1);
			}
			ph_genIso04_isLoaded = true;
		}
		return *ph_genIso04_;
	}
	const vector<float> &ph_drMinParton()
	{
		if (not ph_drMinParton_isLoaded) {
			if (ph_drMinParton_branch != 0) {
				ph_drMinParton_branch->GetEntry(index);
			} else { 
				printf("branch ph_drMinParton_branch does not exist!\n");
				exit(1);
			}
			ph_drMinParton_isLoaded = true;
		}
		return *ph_drMinParton_;
	}
	int &ngoodjets()
	{
		if (not ngoodjets_isLoaded) {
			if (ngoodjets_branch != 0) {
				ngoodjets_branch->GetEntry(index);
			} else { 
				printf("branch ngoodjets_branch does not exist!\n");
				exit(1);
			}
			ngoodjets_isLoaded = true;
		}
		return ngoodjets_;
	}
	int &ngoodbtags()
	{
		if (not ngoodbtags_isLoaded) {
			if (ngoodbtags_branch != 0) {
				ngoodbtags_branch->GetEntry(index);
			} else { 
				printf("branch ngoodbtags_branch does not exist!\n");
				exit(1);
			}
			ngoodbtags_isLoaded = true;
		}
		return ngoodbtags_;
	}
	float &ak4_HT()
	{
		if (not ak4_HT_isLoaded) {
			if (ak4_HT_branch != 0) {
				ak4_HT_branch->GetEntry(index);
			} else { 
				printf("branch ak4_HT_branch does not exist!\n");
				exit(1);
			}
			ak4_HT_isLoaded = true;
		}
		return ak4_HT_;
	}
	float &ak4_htratiom()
	{
		if (not ak4_htratiom_isLoaded) {
			if (ak4_htratiom_branch != 0) {
				ak4_htratiom_branch->GetEntry(index);
			} else { 
				printf("branch ak4_htratiom_branch does not exist!\n");
				exit(1);
			}
			ak4_htratiom_isLoaded = true;
		}
		return ak4_htratiom_;
	}
	const vector<float> &dphi_ak4pfjet_met()
	{
		if (not dphi_ak4pfjet_met_isLoaded) {
			if (dphi_ak4pfjet_met_branch != 0) {
				dphi_ak4pfjet_met_branch->GetEntry(index);
			} else { 
				printf("branch dphi_ak4pfjet_met_branch does not exist!\n");
				exit(1);
			}
			dphi_ak4pfjet_met_isLoaded = true;
		}
		return *dphi_ak4pfjet_met_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4pfjets_p4()
	{
		if (not ak4pfjets_p4_isLoaded) {
			if (ak4pfjets_p4_branch != 0) {
				ak4pfjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_p4_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_p4_isLoaded = true;
		}
		return *ak4pfjets_p4_;
	}
	const vector<bool> &ak4pfjets_passMEDbtag()
	{
		if (not ak4pfjets_passMEDbtag_isLoaded) {
			if (ak4pfjets_passMEDbtag_branch != 0) {
				ak4pfjets_passMEDbtag_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_passMEDbtag_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_passMEDbtag_isLoaded = true;
		}
		return *ak4pfjets_passMEDbtag_;
	}
	const vector<float> &ak4pfjets_CSV()
	{
		if (not ak4pfjets_CSV_isLoaded) {
			if (ak4pfjets_CSV_branch != 0) {
				ak4pfjets_CSV_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_CSV_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_CSV_isLoaded = true;
		}
		return *ak4pfjets_CSV_;
	}
	const vector<float> &ak4pfjets_mva()
	{
		if (not ak4pfjets_mva_isLoaded) {
			if (ak4pfjets_mva_branch != 0) {
				ak4pfjets_mva_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_mva_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_mva_isLoaded = true;
		}
		return *ak4pfjets_mva_;
	}
	const vector<int> &ak4pfjets_parton_flavor()
	{
		if (not ak4pfjets_parton_flavor_isLoaded) {
			if (ak4pfjets_parton_flavor_branch != 0) {
				ak4pfjets_parton_flavor_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_parton_flavor_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_parton_flavor_isLoaded = true;
		}
		return *ak4pfjets_parton_flavor_;
	}
	const vector<int> &ak4pfjets_hadron_flavor()
	{
		if (not ak4pfjets_hadron_flavor_isLoaded) {
			if (ak4pfjets_hadron_flavor_branch != 0) {
				ak4pfjets_hadron_flavor_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_hadron_flavor_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_hadron_flavor_isLoaded = true;
		}
		return *ak4pfjets_hadron_flavor_;
	}
	const vector<bool> &ak4pfjets_loose_puid()
	{
		if (not ak4pfjets_loose_puid_isLoaded) {
			if (ak4pfjets_loose_puid_branch != 0) {
				ak4pfjets_loose_puid_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_loose_puid_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_loose_puid_isLoaded = true;
		}
		return *ak4pfjets_loose_puid_;
	}
	const vector<bool> &ak4pfjets_loose_pfid()
	{
		if (not ak4pfjets_loose_pfid_isLoaded) {
			if (ak4pfjets_loose_pfid_branch != 0) {
				ak4pfjets_loose_pfid_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_loose_pfid_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_loose_pfid_isLoaded = true;
		}
		return *ak4pfjets_loose_pfid_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadMEDbjet_p4()
	{
		if (not ak4pfjets_leadMEDbjet_p4_isLoaded) {
			if (ak4pfjets_leadMEDbjet_p4_branch != 0) {
				ak4pfjets_leadMEDbjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_leadMEDbjet_p4_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_leadMEDbjet_p4_isLoaded = true;
		}
		return *ak4pfjets_leadMEDbjet_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadbtag_p4()
	{
		if (not ak4pfjets_leadbtag_p4_isLoaded) {
			if (ak4pfjets_leadbtag_p4_branch != 0) {
				ak4pfjets_leadbtag_p4_branch->GetEntry(index);
			} else { 
				printf("branch ak4pfjets_leadbtag_p4_branch does not exist!\n");
				exit(1);
			}
			ak4pfjets_leadbtag_p4_isLoaded = true;
		}
		return *ak4pfjets_leadbtag_p4_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4genjets_p4()
	{
		if (not ak4genjets_p4_isLoaded) {
			if (ak4genjets_p4_branch != 0) {
				ak4genjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch ak4genjets_p4_branch does not exist!\n");
				exit(1);
			}
			ak4genjets_p4_isLoaded = true;
		}
		return *ak4genjets_p4_;
	}
	const vector<bool> &genleps_isfromt()
	{
		if (not genleps_isfromt_isLoaded) {
			if (genleps_isfromt_branch != 0) {
				genleps_isfromt_branch->GetEntry(index);
			} else { 
				printf("branch genleps_isfromt_branch does not exist!\n");
				exit(1);
			}
			genleps_isfromt_isLoaded = true;
		}
		return *genleps_isfromt_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_p4()
	{
		if (not genleps_p4_isLoaded) {
			if (genleps_p4_branch != 0) {
				genleps_p4_branch->GetEntry(index);
			} else { 
				printf("branch genleps_p4_branch does not exist!\n");
				exit(1);
			}
			genleps_p4_isLoaded = true;
		}
		return *genleps_p4_;
	}
	const vector<int> &genleps_id()
	{
		if (not genleps_id_isLoaded) {
			if (genleps_id_branch != 0) {
				genleps_id_branch->GetEntry(index);
			} else { 
				printf("branch genleps_id_branch does not exist!\n");
				exit(1);
			}
			genleps_id_isLoaded = true;
		}
		return *genleps_id_;
	}
	const vector<int> &genleps__genpsidx()
	{
		if (not genleps__genpsidx_isLoaded) {
			if (genleps__genpsidx_branch != 0) {
				genleps__genpsidx_branch->GetEntry(index);
			} else { 
				printf("branch genleps__genpsidx_branch does not exist!\n");
				exit(1);
			}
			genleps__genpsidx_isLoaded = true;
		}
		return *genleps__genpsidx_;
	}
	const vector<int> &genleps_status()
	{
		if (not genleps_status_isLoaded) {
			if (genleps_status_branch != 0) {
				genleps_status_branch->GetEntry(index);
			} else { 
				printf("branch genleps_status_branch does not exist!\n");
				exit(1);
			}
			genleps_status_isLoaded = true;
		}
		return *genleps_status_;
	}
	const vector<bool> &genleps_fromHardProcessDecayed()
	{
		if (not genleps_fromHardProcessDecayed_isLoaded) {
			if (genleps_fromHardProcessDecayed_branch != 0) {
				genleps_fromHardProcessDecayed_branch->GetEntry(index);
			} else { 
				printf("branch genleps_fromHardProcessDecayed_branch does not exist!\n");
				exit(1);
			}
			genleps_fromHardProcessDecayed_isLoaded = true;
		}
		return *genleps_fromHardProcessDecayed_;
	}
	const vector<bool> &genleps_fromHardProcessFinalState()
	{
		if (not genleps_fromHardProcessFinalState_isLoaded) {
			if (genleps_fromHardProcessFinalState_branch != 0) {
				genleps_fromHardProcessFinalState_branch->GetEntry(index);
			} else { 
				printf("branch genleps_fromHardProcessFinalState_branch does not exist!\n");
				exit(1);
			}
			genleps_fromHardProcessFinalState_isLoaded = true;
		}
		return *genleps_fromHardProcessFinalState_;
	}
	const vector<bool> &genleps_isHardProcess()
	{
		if (not genleps_isHardProcess_isLoaded) {
			if (genleps_isHardProcess_branch != 0) {
				genleps_isHardProcess_branch->GetEntry(index);
			} else { 
				printf("branch genleps_isHardProcess_branch does not exist!\n");
				exit(1);
			}
			genleps_isHardProcess_isLoaded = true;
		}
		return *genleps_isHardProcess_;
	}
	const vector<bool> &genleps_isLastCopy()
	{
		if (not genleps_isLastCopy_isLoaded) {
			if (genleps_isLastCopy_branch != 0) {
				genleps_isLastCopy_branch->GetEntry(index);
			} else { 
				printf("branch genleps_isLastCopy_branch does not exist!\n");
				exit(1);
			}
			genleps_isLastCopy_isLoaded = true;
		}
		return *genleps_isLastCopy_;
	}
	const vector<int> &genleps_gentaudecay()
	{
		if (not genleps_gentaudecay_isLoaded) {
			if (genleps_gentaudecay_branch != 0) {
				genleps_gentaudecay_branch->GetEntry(index);
			} else { 
				printf("branch genleps_gentaudecay_branch does not exist!\n");
				exit(1);
			}
			genleps_gentaudecay_isLoaded = true;
		}
		return *genleps_gentaudecay_;
	}
	int &gen_nfromtleps_()
	{
		if (not gen_nfromtleps__isLoaded) {
			if (gen_nfromtleps__branch != 0) {
				gen_nfromtleps__branch->GetEntry(index);
			} else { 
				printf("branch gen_nfromtleps__branch does not exist!\n");
				exit(1);
			}
			gen_nfromtleps__isLoaded = true;
		}
		return gen_nfromtleps__;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_motherp4()
	{
		if (not genleps_motherp4_isLoaded) {
			if (genleps_motherp4_branch != 0) {
				genleps_motherp4_branch->GetEntry(index);
			} else { 
				printf("branch genleps_motherp4_branch does not exist!\n");
				exit(1);
			}
			genleps_motherp4_isLoaded = true;
		}
		return *genleps_motherp4_;
	}
	const vector<int> &genleps_motherid()
	{
		if (not genleps_motherid_isLoaded) {
			if (genleps_motherid_branch != 0) {
				genleps_motherid_branch->GetEntry(index);
			} else { 
				printf("branch genleps_motherid_branch does not exist!\n");
				exit(1);
			}
			genleps_motherid_isLoaded = true;
		}
		return *genleps_motherid_;
	}
	const vector<int> &genleps_motheridx()
	{
		if (not genleps_motheridx_isLoaded) {
			if (genleps_motheridx_branch != 0) {
				genleps_motheridx_branch->GetEntry(index);
			} else { 
				printf("branch genleps_motheridx_branch does not exist!\n");
				exit(1);
			}
			genleps_motheridx_isLoaded = true;
		}
		return *genleps_motheridx_;
	}
	const vector<int> &genleps_motherstatus()
	{
		if (not genleps_motherstatus_isLoaded) {
			if (genleps_motherstatus_branch != 0) {
				genleps_motherstatus_branch->GetEntry(index);
			} else { 
				printf("branch genleps_motherstatus_branch does not exist!\n");
				exit(1);
			}
			genleps_motherstatus_isLoaded = true;
		}
		return *genleps_motherstatus_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_gmotherp4()
	{
		if (not genleps_gmotherp4_isLoaded) {
			if (genleps_gmotherp4_branch != 0) {
				genleps_gmotherp4_branch->GetEntry(index);
			} else { 
				printf("branch genleps_gmotherp4_branch does not exist!\n");
				exit(1);
			}
			genleps_gmotherp4_isLoaded = true;
		}
		return *genleps_gmotherp4_;
	}
	const vector<int> &genleps_gmotherid()
	{
		if (not genleps_gmotherid_isLoaded) {
			if (genleps_gmotherid_branch != 0) {
				genleps_gmotherid_branch->GetEntry(index);
			} else { 
				printf("branch genleps_gmotherid_branch does not exist!\n");
				exit(1);
			}
			genleps_gmotherid_isLoaded = true;
		}
		return *genleps_gmotherid_;
	}
	const vector<int> &genleps_gmotheridx()
	{
		if (not genleps_gmotheridx_isLoaded) {
			if (genleps_gmotheridx_branch != 0) {
				genleps_gmotheridx_branch->GetEntry(index);
			} else { 
				printf("branch genleps_gmotheridx_branch does not exist!\n");
				exit(1);
			}
			genleps_gmotheridx_isLoaded = true;
		}
		return *genleps_gmotheridx_;
	}
	const vector<int> &genleps_gmotherstatus()
	{
		if (not genleps_gmotherstatus_isLoaded) {
			if (genleps_gmotherstatus_branch != 0) {
				genleps_gmotherstatus_branch->GetEntry(index);
			} else { 
				printf("branch genleps_gmotherstatus_branch does not exist!\n");
				exit(1);
			}
			genleps_gmotherstatus_isLoaded = true;
		}
		return *genleps_gmotherstatus_;
	}
	const vector<bool> &gennus_isfromt()
	{
		if (not gennus_isfromt_isLoaded) {
			if (gennus_isfromt_branch != 0) {
				gennus_isfromt_branch->GetEntry(index);
			} else { 
				printf("branch gennus_isfromt_branch does not exist!\n");
				exit(1);
			}
			gennus_isfromt_isLoaded = true;
		}
		return *gennus_isfromt_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_p4()
	{
		if (not gennus_p4_isLoaded) {
			if (gennus_p4_branch != 0) {
				gennus_p4_branch->GetEntry(index);
			} else { 
				printf("branch gennus_p4_branch does not exist!\n");
				exit(1);
			}
			gennus_p4_isLoaded = true;
		}
		return *gennus_p4_;
	}
	const vector<int> &gennus_id()
	{
		if (not gennus_id_isLoaded) {
			if (gennus_id_branch != 0) {
				gennus_id_branch->GetEntry(index);
			} else { 
				printf("branch gennus_id_branch does not exist!\n");
				exit(1);
			}
			gennus_id_isLoaded = true;
		}
		return *gennus_id_;
	}
	const vector<int> &gennus__genpsidx()
	{
		if (not gennus__genpsidx_isLoaded) {
			if (gennus__genpsidx_branch != 0) {
				gennus__genpsidx_branch->GetEntry(index);
			} else { 
				printf("branch gennus__genpsidx_branch does not exist!\n");
				exit(1);
			}
			gennus__genpsidx_isLoaded = true;
		}
		return *gennus__genpsidx_;
	}
	const vector<int> &gennus_status()
	{
		if (not gennus_status_isLoaded) {
			if (gennus_status_branch != 0) {
				gennus_status_branch->GetEntry(index);
			} else { 
				printf("branch gennus_status_branch does not exist!\n");
				exit(1);
			}
			gennus_status_isLoaded = true;
		}
		return *gennus_status_;
	}
	const vector<bool> &gennus_fromHardProcessDecayed()
	{
		if (not gennus_fromHardProcessDecayed_isLoaded) {
			if (gennus_fromHardProcessDecayed_branch != 0) {
				gennus_fromHardProcessDecayed_branch->GetEntry(index);
			} else { 
				printf("branch gennus_fromHardProcessDecayed_branch does not exist!\n");
				exit(1);
			}
			gennus_fromHardProcessDecayed_isLoaded = true;
		}
		return *gennus_fromHardProcessDecayed_;
	}
	const vector<bool> &gennus_fromHardProcessFinalState()
	{
		if (not gennus_fromHardProcessFinalState_isLoaded) {
			if (gennus_fromHardProcessFinalState_branch != 0) {
				gennus_fromHardProcessFinalState_branch->GetEntry(index);
			} else { 
				printf("branch gennus_fromHardProcessFinalState_branch does not exist!\n");
				exit(1);
			}
			gennus_fromHardProcessFinalState_isLoaded = true;
		}
		return *gennus_fromHardProcessFinalState_;
	}
	const vector<bool> &gennus_isHardProcess()
	{
		if (not gennus_isHardProcess_isLoaded) {
			if (gennus_isHardProcess_branch != 0) {
				gennus_isHardProcess_branch->GetEntry(index);
			} else { 
				printf("branch gennus_isHardProcess_branch does not exist!\n");
				exit(1);
			}
			gennus_isHardProcess_isLoaded = true;
		}
		return *gennus_isHardProcess_;
	}
	const vector<bool> &gennus_isLastCopy()
	{
		if (not gennus_isLastCopy_isLoaded) {
			if (gennus_isLastCopy_branch != 0) {
				gennus_isLastCopy_branch->GetEntry(index);
			} else { 
				printf("branch gennus_isLastCopy_branch does not exist!\n");
				exit(1);
			}
			gennus_isLastCopy_isLoaded = true;
		}
		return *gennus_isLastCopy_;
	}
	const vector<int> &gennus_gentaudecay()
	{
		if (not gennus_gentaudecay_isLoaded) {
			if (gennus_gentaudecay_branch != 0) {
				gennus_gentaudecay_branch->GetEntry(index);
			} else { 
				printf("branch gennus_gentaudecay_branch does not exist!\n");
				exit(1);
			}
			gennus_gentaudecay_isLoaded = true;
		}
		return *gennus_gentaudecay_;
	}
	int &gen_nfromtnus_()
	{
		if (not gen_nfromtnus__isLoaded) {
			if (gen_nfromtnus__branch != 0) {
				gen_nfromtnus__branch->GetEntry(index);
			} else { 
				printf("branch gen_nfromtnus__branch does not exist!\n");
				exit(1);
			}
			gen_nfromtnus__isLoaded = true;
		}
		return gen_nfromtnus__;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_motherp4()
	{
		if (not gennus_motherp4_isLoaded) {
			if (gennus_motherp4_branch != 0) {
				gennus_motherp4_branch->GetEntry(index);
			} else { 
				printf("branch gennus_motherp4_branch does not exist!\n");
				exit(1);
			}
			gennus_motherp4_isLoaded = true;
		}
		return *gennus_motherp4_;
	}
	const vector<int> &gennus_motherid()
	{
		if (not gennus_motherid_isLoaded) {
			if (gennus_motherid_branch != 0) {
				gennus_motherid_branch->GetEntry(index);
			} else { 
				printf("branch gennus_motherid_branch does not exist!\n");
				exit(1);
			}
			gennus_motherid_isLoaded = true;
		}
		return *gennus_motherid_;
	}
	const vector<int> &gennus_motheridx()
	{
		if (not gennus_motheridx_isLoaded) {
			if (gennus_motheridx_branch != 0) {
				gennus_motheridx_branch->GetEntry(index);
			} else { 
				printf("branch gennus_motheridx_branch does not exist!\n");
				exit(1);
			}
			gennus_motheridx_isLoaded = true;
		}
		return *gennus_motheridx_;
	}
	const vector<int> &gennus_motherstatus()
	{
		if (not gennus_motherstatus_isLoaded) {
			if (gennus_motherstatus_branch != 0) {
				gennus_motherstatus_branch->GetEntry(index);
			} else { 
				printf("branch gennus_motherstatus_branch does not exist!\n");
				exit(1);
			}
			gennus_motherstatus_isLoaded = true;
		}
		return *gennus_motherstatus_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_gmotherp4()
	{
		if (not gennus_gmotherp4_isLoaded) {
			if (gennus_gmotherp4_branch != 0) {
				gennus_gmotherp4_branch->GetEntry(index);
			} else { 
				printf("branch gennus_gmotherp4_branch does not exist!\n");
				exit(1);
			}
			gennus_gmotherp4_isLoaded = true;
		}
		return *gennus_gmotherp4_;
	}
	const vector<int> &gennus_gmotherid()
	{
		if (not gennus_gmotherid_isLoaded) {
			if (gennus_gmotherid_branch != 0) {
				gennus_gmotherid_branch->GetEntry(index);
			} else { 
				printf("branch gennus_gmotherid_branch does not exist!\n");
				exit(1);
			}
			gennus_gmotherid_isLoaded = true;
		}
		return *gennus_gmotherid_;
	}
	const vector<int> &gennus_gmotheridx()
	{
		if (not gennus_gmotheridx_isLoaded) {
			if (gennus_gmotheridx_branch != 0) {
				gennus_gmotheridx_branch->GetEntry(index);
			} else { 
				printf("branch gennus_gmotheridx_branch does not exist!\n");
				exit(1);
			}
			gennus_gmotheridx_isLoaded = true;
		}
		return *gennus_gmotheridx_;
	}
	const vector<int> &gennus_gmotherstatus()
	{
		if (not gennus_gmotherstatus_isLoaded) {
			if (gennus_gmotherstatus_branch != 0) {
				gennus_gmotherstatus_branch->GetEntry(index);
			} else { 
				printf("branch gennus_gmotherstatus_branch does not exist!\n");
				exit(1);
			}
			gennus_gmotherstatus_isLoaded = true;
		}
		return *gennus_gmotherstatus_;
	}
	const vector<bool> &genqs_isfromt()
	{
		if (not genqs_isfromt_isLoaded) {
			if (genqs_isfromt_branch != 0) {
				genqs_isfromt_branch->GetEntry(index);
			} else { 
				printf("branch genqs_isfromt_branch does not exist!\n");
				exit(1);
			}
			genqs_isfromt_isLoaded = true;
		}
		return *genqs_isfromt_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_p4()
	{
		if (not genqs_p4_isLoaded) {
			if (genqs_p4_branch != 0) {
				genqs_p4_branch->GetEntry(index);
			} else { 
				printf("branch genqs_p4_branch does not exist!\n");
				exit(1);
			}
			genqs_p4_isLoaded = true;
		}
		return *genqs_p4_;
	}
	const vector<int> &genqs_id()
	{
		if (not genqs_id_isLoaded) {
			if (genqs_id_branch != 0) {
				genqs_id_branch->GetEntry(index);
			} else { 
				printf("branch genqs_id_branch does not exist!\n");
				exit(1);
			}
			genqs_id_isLoaded = true;
		}
		return *genqs_id_;
	}
	const vector<int> &genqs__genpsidx()
	{
		if (not genqs__genpsidx_isLoaded) {
			if (genqs__genpsidx_branch != 0) {
				genqs__genpsidx_branch->GetEntry(index);
			} else { 
				printf("branch genqs__genpsidx_branch does not exist!\n");
				exit(1);
			}
			genqs__genpsidx_isLoaded = true;
		}
		return *genqs__genpsidx_;
	}
	const vector<int> &genqs_status()
	{
		if (not genqs_status_isLoaded) {
			if (genqs_status_branch != 0) {
				genqs_status_branch->GetEntry(index);
			} else { 
				printf("branch genqs_status_branch does not exist!\n");
				exit(1);
			}
			genqs_status_isLoaded = true;
		}
		return *genqs_status_;
	}
	const vector<bool> &genqs_fromHardProcessDecayed()
	{
		if (not genqs_fromHardProcessDecayed_isLoaded) {
			if (genqs_fromHardProcessDecayed_branch != 0) {
				genqs_fromHardProcessDecayed_branch->GetEntry(index);
			} else { 
				printf("branch genqs_fromHardProcessDecayed_branch does not exist!\n");
				exit(1);
			}
			genqs_fromHardProcessDecayed_isLoaded = true;
		}
		return *genqs_fromHardProcessDecayed_;
	}
	const vector<bool> &genqs_fromHardProcessFinalState()
	{
		if (not genqs_fromHardProcessFinalState_isLoaded) {
			if (genqs_fromHardProcessFinalState_branch != 0) {
				genqs_fromHardProcessFinalState_branch->GetEntry(index);
			} else { 
				printf("branch genqs_fromHardProcessFinalState_branch does not exist!\n");
				exit(1);
			}
			genqs_fromHardProcessFinalState_isLoaded = true;
		}
		return *genqs_fromHardProcessFinalState_;
	}
	const vector<bool> &genqs_isHardProcess()
	{
		if (not genqs_isHardProcess_isLoaded) {
			if (genqs_isHardProcess_branch != 0) {
				genqs_isHardProcess_branch->GetEntry(index);
			} else { 
				printf("branch genqs_isHardProcess_branch does not exist!\n");
				exit(1);
			}
			genqs_isHardProcess_isLoaded = true;
		}
		return *genqs_isHardProcess_;
	}
	const vector<bool> &genqs_isLastCopy()
	{
		if (not genqs_isLastCopy_isLoaded) {
			if (genqs_isLastCopy_branch != 0) {
				genqs_isLastCopy_branch->GetEntry(index);
			} else { 
				printf("branch genqs_isLastCopy_branch does not exist!\n");
				exit(1);
			}
			genqs_isLastCopy_isLoaded = true;
		}
		return *genqs_isLastCopy_;
	}
	const vector<int> &genqs_gentaudecay()
	{
		if (not genqs_gentaudecay_isLoaded) {
			if (genqs_gentaudecay_branch != 0) {
				genqs_gentaudecay_branch->GetEntry(index);
			} else { 
				printf("branch genqs_gentaudecay_branch does not exist!\n");
				exit(1);
			}
			genqs_gentaudecay_isLoaded = true;
		}
		return *genqs_gentaudecay_;
	}
	int &gen_nfromtqs_()
	{
		if (not gen_nfromtqs__isLoaded) {
			if (gen_nfromtqs__branch != 0) {
				gen_nfromtqs__branch->GetEntry(index);
			} else { 
				printf("branch gen_nfromtqs__branch does not exist!\n");
				exit(1);
			}
			gen_nfromtqs__isLoaded = true;
		}
		return gen_nfromtqs__;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_motherp4()
	{
		if (not genqs_motherp4_isLoaded) {
			if (genqs_motherp4_branch != 0) {
				genqs_motherp4_branch->GetEntry(index);
			} else { 
				printf("branch genqs_motherp4_branch does not exist!\n");
				exit(1);
			}
			genqs_motherp4_isLoaded = true;
		}
		return *genqs_motherp4_;
	}
	const vector<int> &genqs_motherid()
	{
		if (not genqs_motherid_isLoaded) {
			if (genqs_motherid_branch != 0) {
				genqs_motherid_branch->GetEntry(index);
			} else { 
				printf("branch genqs_motherid_branch does not exist!\n");
				exit(1);
			}
			genqs_motherid_isLoaded = true;
		}
		return *genqs_motherid_;
	}
	const vector<int> &genqs_motheridx()
	{
		if (not genqs_motheridx_isLoaded) {
			if (genqs_motheridx_branch != 0) {
				genqs_motheridx_branch->GetEntry(index);
			} else { 
				printf("branch genqs_motheridx_branch does not exist!\n");
				exit(1);
			}
			genqs_motheridx_isLoaded = true;
		}
		return *genqs_motheridx_;
	}
	const vector<int> &genqs_motherstatus()
	{
		if (not genqs_motherstatus_isLoaded) {
			if (genqs_motherstatus_branch != 0) {
				genqs_motherstatus_branch->GetEntry(index);
			} else { 
				printf("branch genqs_motherstatus_branch does not exist!\n");
				exit(1);
			}
			genqs_motherstatus_isLoaded = true;
		}
		return *genqs_motherstatus_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_gmotherp4()
	{
		if (not genqs_gmotherp4_isLoaded) {
			if (genqs_gmotherp4_branch != 0) {
				genqs_gmotherp4_branch->GetEntry(index);
			} else { 
				printf("branch genqs_gmotherp4_branch does not exist!\n");
				exit(1);
			}
			genqs_gmotherp4_isLoaded = true;
		}
		return *genqs_gmotherp4_;
	}
	const vector<int> &genqs_gmotherid()
	{
		if (not genqs_gmotherid_isLoaded) {
			if (genqs_gmotherid_branch != 0) {
				genqs_gmotherid_branch->GetEntry(index);
			} else { 
				printf("branch genqs_gmotherid_branch does not exist!\n");
				exit(1);
			}
			genqs_gmotherid_isLoaded = true;
		}
		return *genqs_gmotherid_;
	}
	const vector<int> &genqs_gmotheridx()
	{
		if (not genqs_gmotheridx_isLoaded) {
			if (genqs_gmotheridx_branch != 0) {
				genqs_gmotheridx_branch->GetEntry(index);
			} else { 
				printf("branch genqs_gmotheridx_branch does not exist!\n");
				exit(1);
			}
			genqs_gmotheridx_isLoaded = true;
		}
		return *genqs_gmotheridx_;
	}
	const vector<int> &genqs_gmotherstatus()
	{
		if (not genqs_gmotherstatus_isLoaded) {
			if (genqs_gmotherstatus_branch != 0) {
				genqs_gmotherstatus_branch->GetEntry(index);
			} else { 
				printf("branch genqs_gmotherstatus_branch does not exist!\n");
				exit(1);
			}
			genqs_gmotherstatus_isLoaded = true;
		}
		return *genqs_gmotherstatus_;
	}
	const vector<bool> &genbosons_isfromt()
	{
		if (not genbosons_isfromt_isLoaded) {
			if (genbosons_isfromt_branch != 0) {
				genbosons_isfromt_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_isfromt_branch does not exist!\n");
				exit(1);
			}
			genbosons_isfromt_isLoaded = true;
		}
		return *genbosons_isfromt_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_p4()
	{
		if (not genbosons_p4_isLoaded) {
			if (genbosons_p4_branch != 0) {
				genbosons_p4_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_p4_branch does not exist!\n");
				exit(1);
			}
			genbosons_p4_isLoaded = true;
		}
		return *genbosons_p4_;
	}
	const vector<int> &genbosons_id()
	{
		if (not genbosons_id_isLoaded) {
			if (genbosons_id_branch != 0) {
				genbosons_id_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_id_branch does not exist!\n");
				exit(1);
			}
			genbosons_id_isLoaded = true;
		}
		return *genbosons_id_;
	}
	const vector<int> &genbosons__genpsidx()
	{
		if (not genbosons__genpsidx_isLoaded) {
			if (genbosons__genpsidx_branch != 0) {
				genbosons__genpsidx_branch->GetEntry(index);
			} else { 
				printf("branch genbosons__genpsidx_branch does not exist!\n");
				exit(1);
			}
			genbosons__genpsidx_isLoaded = true;
		}
		return *genbosons__genpsidx_;
	}
	const vector<int> &genbosons_status()
	{
		if (not genbosons_status_isLoaded) {
			if (genbosons_status_branch != 0) {
				genbosons_status_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_status_branch does not exist!\n");
				exit(1);
			}
			genbosons_status_isLoaded = true;
		}
		return *genbosons_status_;
	}
	const vector<bool> &genbosons_fromHardProcessDecayed()
	{
		if (not genbosons_fromHardProcessDecayed_isLoaded) {
			if (genbosons_fromHardProcessDecayed_branch != 0) {
				genbosons_fromHardProcessDecayed_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_fromHardProcessDecayed_branch does not exist!\n");
				exit(1);
			}
			genbosons_fromHardProcessDecayed_isLoaded = true;
		}
		return *genbosons_fromHardProcessDecayed_;
	}
	const vector<bool> &genbosons_fromHardProcessFinalState()
	{
		if (not genbosons_fromHardProcessFinalState_isLoaded) {
			if (genbosons_fromHardProcessFinalState_branch != 0) {
				genbosons_fromHardProcessFinalState_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_fromHardProcessFinalState_branch does not exist!\n");
				exit(1);
			}
			genbosons_fromHardProcessFinalState_isLoaded = true;
		}
		return *genbosons_fromHardProcessFinalState_;
	}
	const vector<bool> &genbosons_isHardProcess()
	{
		if (not genbosons_isHardProcess_isLoaded) {
			if (genbosons_isHardProcess_branch != 0) {
				genbosons_isHardProcess_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_isHardProcess_branch does not exist!\n");
				exit(1);
			}
			genbosons_isHardProcess_isLoaded = true;
		}
		return *genbosons_isHardProcess_;
	}
	const vector<bool> &genbosons_isLastCopy()
	{
		if (not genbosons_isLastCopy_isLoaded) {
			if (genbosons_isLastCopy_branch != 0) {
				genbosons_isLastCopy_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_isLastCopy_branch does not exist!\n");
				exit(1);
			}
			genbosons_isLastCopy_isLoaded = true;
		}
		return *genbosons_isLastCopy_;
	}
	const vector<int> &genbosons_gentaudecay()
	{
		if (not genbosons_gentaudecay_isLoaded) {
			if (genbosons_gentaudecay_branch != 0) {
				genbosons_gentaudecay_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_gentaudecay_branch does not exist!\n");
				exit(1);
			}
			genbosons_gentaudecay_isLoaded = true;
		}
		return *genbosons_gentaudecay_;
	}
	int &gen_nfromtbosons_()
	{
		if (not gen_nfromtbosons__isLoaded) {
			if (gen_nfromtbosons__branch != 0) {
				gen_nfromtbosons__branch->GetEntry(index);
			} else { 
				printf("branch gen_nfromtbosons__branch does not exist!\n");
				exit(1);
			}
			gen_nfromtbosons__isLoaded = true;
		}
		return gen_nfromtbosons__;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_motherp4()
	{
		if (not genbosons_motherp4_isLoaded) {
			if (genbosons_motherp4_branch != 0) {
				genbosons_motherp4_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_motherp4_branch does not exist!\n");
				exit(1);
			}
			genbosons_motherp4_isLoaded = true;
		}
		return *genbosons_motherp4_;
	}
	const vector<int> &genbosons_motherid()
	{
		if (not genbosons_motherid_isLoaded) {
			if (genbosons_motherid_branch != 0) {
				genbosons_motherid_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_motherid_branch does not exist!\n");
				exit(1);
			}
			genbosons_motherid_isLoaded = true;
		}
		return *genbosons_motherid_;
	}
	const vector<int> &genbosons_motheridx()
	{
		if (not genbosons_motheridx_isLoaded) {
			if (genbosons_motheridx_branch != 0) {
				genbosons_motheridx_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_motheridx_branch does not exist!\n");
				exit(1);
			}
			genbosons_motheridx_isLoaded = true;
		}
		return *genbosons_motheridx_;
	}
	const vector<int> &genbosons_motherstatus()
	{
		if (not genbosons_motherstatus_isLoaded) {
			if (genbosons_motherstatus_branch != 0) {
				genbosons_motherstatus_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_motherstatus_branch does not exist!\n");
				exit(1);
			}
			genbosons_motherstatus_isLoaded = true;
		}
		return *genbosons_motherstatus_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_gmotherp4()
	{
		if (not genbosons_gmotherp4_isLoaded) {
			if (genbosons_gmotherp4_branch != 0) {
				genbosons_gmotherp4_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_gmotherp4_branch does not exist!\n");
				exit(1);
			}
			genbosons_gmotherp4_isLoaded = true;
		}
		return *genbosons_gmotherp4_;
	}
	const vector<int> &genbosons_gmotherid()
	{
		if (not genbosons_gmotherid_isLoaded) {
			if (genbosons_gmotherid_branch != 0) {
				genbosons_gmotherid_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_gmotherid_branch does not exist!\n");
				exit(1);
			}
			genbosons_gmotherid_isLoaded = true;
		}
		return *genbosons_gmotherid_;
	}
	const vector<int> &genbosons_gmotheridx()
	{
		if (not genbosons_gmotheridx_isLoaded) {
			if (genbosons_gmotheridx_branch != 0) {
				genbosons_gmotheridx_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_gmotheridx_branch does not exist!\n");
				exit(1);
			}
			genbosons_gmotheridx_isLoaded = true;
		}
		return *genbosons_gmotheridx_;
	}
	const vector<int> &genbosons_gmotherstatus()
	{
		if (not genbosons_gmotherstatus_isLoaded) {
			if (genbosons_gmotherstatus_branch != 0) {
				genbosons_gmotherstatus_branch->GetEntry(index);
			} else { 
				printf("branch genbosons_gmotherstatus_branch does not exist!\n");
				exit(1);
			}
			genbosons_gmotherstatus_isLoaded = true;
		}
		return *genbosons_gmotherstatus_;
	}
	const vector<bool> &gensusy_isfromt()
	{
		if (not gensusy_isfromt_isLoaded) {
			if (gensusy_isfromt_branch != 0) {
				gensusy_isfromt_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_isfromt_branch does not exist!\n");
				exit(1);
			}
			gensusy_isfromt_isLoaded = true;
		}
		return *gensusy_isfromt_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_p4()
	{
		if (not gensusy_p4_isLoaded) {
			if (gensusy_p4_branch != 0) {
				gensusy_p4_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_p4_branch does not exist!\n");
				exit(1);
			}
			gensusy_p4_isLoaded = true;
		}
		return *gensusy_p4_;
	}
	const vector<int> &gensusy_id()
	{
		if (not gensusy_id_isLoaded) {
			if (gensusy_id_branch != 0) {
				gensusy_id_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_id_branch does not exist!\n");
				exit(1);
			}
			gensusy_id_isLoaded = true;
		}
		return *gensusy_id_;
	}
	const vector<int> &gensusy__genpsidx()
	{
		if (not gensusy__genpsidx_isLoaded) {
			if (gensusy__genpsidx_branch != 0) {
				gensusy__genpsidx_branch->GetEntry(index);
			} else { 
				printf("branch gensusy__genpsidx_branch does not exist!\n");
				exit(1);
			}
			gensusy__genpsidx_isLoaded = true;
		}
		return *gensusy__genpsidx_;
	}
	const vector<int> &gensusy_status()
	{
		if (not gensusy_status_isLoaded) {
			if (gensusy_status_branch != 0) {
				gensusy_status_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_status_branch does not exist!\n");
				exit(1);
			}
			gensusy_status_isLoaded = true;
		}
		return *gensusy_status_;
	}
	const vector<bool> &gensusy_fromHardProcessDecayed()
	{
		if (not gensusy_fromHardProcessDecayed_isLoaded) {
			if (gensusy_fromHardProcessDecayed_branch != 0) {
				gensusy_fromHardProcessDecayed_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_fromHardProcessDecayed_branch does not exist!\n");
				exit(1);
			}
			gensusy_fromHardProcessDecayed_isLoaded = true;
		}
		return *gensusy_fromHardProcessDecayed_;
	}
	const vector<bool> &gensusy_fromHardProcessFinalState()
	{
		if (not gensusy_fromHardProcessFinalState_isLoaded) {
			if (gensusy_fromHardProcessFinalState_branch != 0) {
				gensusy_fromHardProcessFinalState_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_fromHardProcessFinalState_branch does not exist!\n");
				exit(1);
			}
			gensusy_fromHardProcessFinalState_isLoaded = true;
		}
		return *gensusy_fromHardProcessFinalState_;
	}
	const vector<bool> &gensusy_isHardProcess()
	{
		if (not gensusy_isHardProcess_isLoaded) {
			if (gensusy_isHardProcess_branch != 0) {
				gensusy_isHardProcess_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_isHardProcess_branch does not exist!\n");
				exit(1);
			}
			gensusy_isHardProcess_isLoaded = true;
		}
		return *gensusy_isHardProcess_;
	}
	const vector<bool> &gensusy_isLastCopy()
	{
		if (not gensusy_isLastCopy_isLoaded) {
			if (gensusy_isLastCopy_branch != 0) {
				gensusy_isLastCopy_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_isLastCopy_branch does not exist!\n");
				exit(1);
			}
			gensusy_isLastCopy_isLoaded = true;
		}
		return *gensusy_isLastCopy_;
	}
	const vector<int> &gensusy_gentaudecay()
	{
		if (not gensusy_gentaudecay_isLoaded) {
			if (gensusy_gentaudecay_branch != 0) {
				gensusy_gentaudecay_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_gentaudecay_branch does not exist!\n");
				exit(1);
			}
			gensusy_gentaudecay_isLoaded = true;
		}
		return *gensusy_gentaudecay_;
	}
	int &gen_nfromtsusy_()
	{
		if (not gen_nfromtsusy__isLoaded) {
			if (gen_nfromtsusy__branch != 0) {
				gen_nfromtsusy__branch->GetEntry(index);
			} else { 
				printf("branch gen_nfromtsusy__branch does not exist!\n");
				exit(1);
			}
			gen_nfromtsusy__isLoaded = true;
		}
		return gen_nfromtsusy__;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_motherp4()
	{
		if (not gensusy_motherp4_isLoaded) {
			if (gensusy_motherp4_branch != 0) {
				gensusy_motherp4_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_motherp4_branch does not exist!\n");
				exit(1);
			}
			gensusy_motherp4_isLoaded = true;
		}
		return *gensusy_motherp4_;
	}
	const vector<int> &gensusy_motherid()
	{
		if (not gensusy_motherid_isLoaded) {
			if (gensusy_motherid_branch != 0) {
				gensusy_motherid_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_motherid_branch does not exist!\n");
				exit(1);
			}
			gensusy_motherid_isLoaded = true;
		}
		return *gensusy_motherid_;
	}
	const vector<int> &gensusy_motheridx()
	{
		if (not gensusy_motheridx_isLoaded) {
			if (gensusy_motheridx_branch != 0) {
				gensusy_motheridx_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_motheridx_branch does not exist!\n");
				exit(1);
			}
			gensusy_motheridx_isLoaded = true;
		}
		return *gensusy_motheridx_;
	}
	const vector<int> &gensusy_motherstatus()
	{
		if (not gensusy_motherstatus_isLoaded) {
			if (gensusy_motherstatus_branch != 0) {
				gensusy_motherstatus_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_motherstatus_branch does not exist!\n");
				exit(1);
			}
			gensusy_motherstatus_isLoaded = true;
		}
		return *gensusy_motherstatus_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_gmotherp4()
	{
		if (not gensusy_gmotherp4_isLoaded) {
			if (gensusy_gmotherp4_branch != 0) {
				gensusy_gmotherp4_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_gmotherp4_branch does not exist!\n");
				exit(1);
			}
			gensusy_gmotherp4_isLoaded = true;
		}
		return *gensusy_gmotherp4_;
	}
	const vector<int> &gensusy_gmotherid()
	{
		if (not gensusy_gmotherid_isLoaded) {
			if (gensusy_gmotherid_branch != 0) {
				gensusy_gmotherid_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_gmotherid_branch does not exist!\n");
				exit(1);
			}
			gensusy_gmotherid_isLoaded = true;
		}
		return *gensusy_gmotherid_;
	}
	const vector<int> &gensusy_gmotheridx()
	{
		if (not gensusy_gmotheridx_isLoaded) {
			if (gensusy_gmotheridx_branch != 0) {
				gensusy_gmotheridx_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_gmotheridx_branch does not exist!\n");
				exit(1);
			}
			gensusy_gmotheridx_isLoaded = true;
		}
		return *gensusy_gmotheridx_;
	}
	const vector<int> &gensusy_gmotherstatus()
	{
		if (not gensusy_gmotherstatus_isLoaded) {
			if (gensusy_gmotherstatus_branch != 0) {
				gensusy_gmotherstatus_branch->GetEntry(index);
			} else { 
				printf("branch gensusy_gmotherstatus_branch does not exist!\n");
				exit(1);
			}
			gensusy_gmotherstatus_isLoaded = true;
		}
		return *gensusy_gmotherstatus_;
	}
	const vector<TString> &tau_IDnames()
	{
		if (not tau_IDnames_isLoaded) {
			if (tau_IDnames_branch != 0) {
				tau_IDnames_branch->GetEntry(index);
			} else { 
				printf("branch tau_IDnames_branch does not exist!\n");
				exit(1);
			}
			tau_IDnames_isLoaded = true;
		}
		return *tau_IDnames_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_leadtrack_p4()
	{
		if (not tau_leadtrack_p4_isLoaded) {
			if (tau_leadtrack_p4_branch != 0) {
				tau_leadtrack_p4_branch->GetEntry(index);
			} else { 
				printf("branch tau_leadtrack_p4_branch does not exist!\n");
				exit(1);
			}
			tau_leadtrack_p4_isLoaded = true;
		}
		return *tau_leadtrack_p4_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_leadneutral_p4()
	{
		if (not tau_leadneutral_p4_isLoaded) {
			if (tau_leadneutral_p4_branch != 0) {
				tau_leadneutral_p4_branch->GetEntry(index);
			} else { 
				printf("branch tau_leadneutral_p4_branch does not exist!\n");
				exit(1);
			}
			tau_leadneutral_p4_isLoaded = true;
		}
		return *tau_leadneutral_p4_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_p4()
	{
		if (not tau_p4_isLoaded) {
			if (tau_p4_branch != 0) {
				tau_p4_branch->GetEntry(index);
			} else { 
				printf("branch tau_p4_branch does not exist!\n");
				exit(1);
			}
			tau_p4_isLoaded = true;
		}
		return *tau_p4_;
	}
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &tau_isocand_p4()
	{
		if (not tau_isocand_p4_isLoaded) {
			if (tau_isocand_p4_branch != 0) {
				tau_isocand_p4_branch->GetEntry(index);
			} else { 
				printf("branch tau_isocand_p4_branch does not exist!\n");
				exit(1);
			}
			tau_isocand_p4_isLoaded = true;
		}
		return *tau_isocand_p4_;
	}
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &tau_sigcand_p4()
	{
		if (not tau_sigcand_p4_isLoaded) {
			if (tau_sigcand_p4_branch != 0) {
				tau_sigcand_p4_branch->GetEntry(index);
			} else { 
				printf("branch tau_sigcand_p4_branch does not exist!\n");
				exit(1);
			}
			tau_sigcand_p4_isLoaded = true;
		}
		return *tau_sigcand_p4_;
	}
	const vector<vector<float> > &tau_ID()
	{
		if (not tau_ID_isLoaded) {
			if (tau_ID_branch != 0) {
				tau_ID_branch->GetEntry(index);
			} else { 
				printf("branch tau_ID_branch does not exist!\n");
				exit(1);
			}
			tau_ID_isLoaded = true;
		}
		return *tau_ID_;
	}
	const vector<float> &tau_passID()
	{
		if (not tau_passID_isLoaded) {
			if (tau_passID_branch != 0) {
				tau_passID_branch->GetEntry(index);
			} else { 
				printf("branch tau_passID_branch does not exist!\n");
				exit(1);
			}
			tau_passID_isLoaded = true;
		}
		return *tau_passID_;
	}
	int &ngoodtaus()
	{
		if (not ngoodtaus_isLoaded) {
			if (ngoodtaus_branch != 0) {
				ngoodtaus_branch->GetEntry(index);
			} else { 
				printf("branch ngoodtaus_branch does not exist!\n");
				exit(1);
			}
			ngoodtaus_isLoaded = true;
		}
		return ngoodtaus_;
	}
	const vector<float> &tau_againstMuonTight()
	{
		if (not tau_againstMuonTight_isLoaded) {
			if (tau_againstMuonTight_branch != 0) {
				tau_againstMuonTight_branch->GetEntry(index);
			} else { 
				printf("branch tau_againstMuonTight_branch does not exist!\n");
				exit(1);
			}
			tau_againstMuonTight_isLoaded = true;
		}
		return *tau_againstMuonTight_;
	}
	const vector<float> &tau_againstElectronLoose()
	{
		if (not tau_againstElectronLoose_isLoaded) {
			if (tau_againstElectronLoose_branch != 0) {
				tau_againstElectronLoose_branch->GetEntry(index);
			} else { 
				printf("branch tau_againstElectronLoose_branch does not exist!\n");
				exit(1);
			}
			tau_againstElectronLoose_isLoaded = true;
		}
		return *tau_againstElectronLoose_;
	}
	const vector<bool> &tau_isVetoTau()
	{
		if (not tau_isVetoTau_isLoaded) {
			if (tau_isVetoTau_branch != 0) {
				tau_isVetoTau_branch->GetEntry(index);
			} else { 
				printf("branch tau_isVetoTau_branch does not exist!\n");
				exit(1);
			}
			tau_isVetoTau_isLoaded = true;
		}
		return *tau_isVetoTau_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &isoTracks_p4()
	{
		if (not isoTracks_p4_isLoaded) {
			if (isoTracks_p4_branch != 0) {
				isoTracks_p4_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_p4_branch does not exist!\n");
				exit(1);
			}
			isoTracks_p4_isLoaded = true;
		}
		return *isoTracks_p4_;
	}
	const vector<int> &isoTracks_charge()
	{
		if (not isoTracks_charge_isLoaded) {
			if (isoTracks_charge_branch != 0) {
				isoTracks_charge_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_charge_branch does not exist!\n");
				exit(1);
			}
			isoTracks_charge_isLoaded = true;
		}
		return *isoTracks_charge_;
	}
	const vector<float> &isoTracks_absIso()
	{
		if (not isoTracks_absIso_isLoaded) {
			if (isoTracks_absIso_branch != 0) {
				isoTracks_absIso_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_absIso_branch does not exist!\n");
				exit(1);
			}
			isoTracks_absIso_isLoaded = true;
		}
		return *isoTracks_absIso_;
	}
	const vector<float> &isoTracks_dz()
	{
		if (not isoTracks_dz_isLoaded) {
			if (isoTracks_dz_branch != 0) {
				isoTracks_dz_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_dz_branch does not exist!\n");
				exit(1);
			}
			isoTracks_dz_isLoaded = true;
		}
		return *isoTracks_dz_;
	}
	const vector<int> &isoTracks_pdgId()
	{
		if (not isoTracks_pdgId_isLoaded) {
			if (isoTracks_pdgId_branch != 0) {
				isoTracks_pdgId_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_pdgId_branch does not exist!\n");
				exit(1);
			}
			isoTracks_pdgId_isLoaded = true;
		}
		return *isoTracks_pdgId_;
	}
	const vector<bool> &isoTracks_isVetoTrack()
	{
		if (not isoTracks_isVetoTrack_isLoaded) {
			if (isoTracks_isVetoTrack_branch != 0) {
				isoTracks_isVetoTrack_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_isVetoTrack_branch does not exist!\n");
				exit(1);
			}
			isoTracks_isVetoTrack_isLoaded = true;
		}
		return *isoTracks_isVetoTrack_;
	}
	const vector<bool> &isoTracks_isVetoTrack_v2()
	{
		if (not isoTracks_isVetoTrack_v2_isLoaded) {
			if (isoTracks_isVetoTrack_v2_branch != 0) {
				isoTracks_isVetoTrack_v2_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_isVetoTrack_v2_branch does not exist!\n");
				exit(1);
			}
			isoTracks_isVetoTrack_v2_isLoaded = true;
		}
		return *isoTracks_isVetoTrack_v2_;
	}
	const vector<bool> &isoTracks_isVetoTrack_v3()
	{
		if (not isoTracks_isVetoTrack_v3_isLoaded) {
			if (isoTracks_isVetoTrack_v3_branch != 0) {
				isoTracks_isVetoTrack_v3_branch->GetEntry(index);
			} else { 
				printf("branch isoTracks_isVetoTrack_v3_branch does not exist!\n");
				exit(1);
			}
			isoTracks_isVetoTrack_v3_isLoaded = true;
		}
		return *isoTracks_isVetoTrack_v3_;
	}

  static void progress( int nEventsTotal, int nEventsChain ){
    int period = 1000;
    if(nEventsTotal%1000 == 0) {
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)) {
        if( ( nEventsChain - nEventsTotal ) > period ){
          float frac = (float)nEventsTotal/(nEventsChain*0.01);
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
          fflush(stdout);
        }
        else {
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", 100.);
          cout << endl;
        }
      }
    }
  }
  
};

#ifndef __CINT__
extern stop_1l_babyAnalyzer babyAnalyzer;
#endif

namespace stop_1l {
	const unsigned int &run();
	const unsigned int &ls();
	const unsigned int &evt();
	const int &nvtxs();
	const int &pu_nvtxs();
	const float &pfmet();
	const float &pfmet_phi();
	const float &pfmet_rl();
	const float &pfmet_phi_rl();
	const float &scale1fb();
	const float &xsec();
	const float &xsec_uncert();
	const float &kfactor();
	const float &pu_ntrue();
	const int &ngoodleps();
	const int &nvetoleps();
	const bool &is_data();
	const string &dataset();
	const string &filename();
	const string &cms3tag();
	const unsigned int &nEvents();
	const unsigned int &nEvents_goodvtx();
	const unsigned int &nEvents_MET30();
	const unsigned int &nEvents_1goodlep();
	const unsigned int &nEvents_2goodjets();
	const int &is0lep();
	const int &is1lep();
	const int &is2lep();
	const int &isZtoNuNu();
	const int &is1lepFromW();
	const int &is1lepFromTop();
	const float &MT2W();
	const float &MT2W_rl();
	const float &mindphi_met_j1_j2();
	const float &mindphi_met_j1_j2_rl();
	const float &mt_met_lep();
	const float &mt_met_lep_rl();
	const float &hadronic_top_chi2();
	const float &ak4pfjets_rho();
	const float &pdf_up_weight();
	const float &pdf_down_weight();
	const vector<string> &genweightsID();
	const vector<float> &genweights();
	const float &weight_btagsf();
	const float &weight_btagsf_heavy_UP();
	const float &weight_btagsf_light_UP();
	const float &weight_btagsf_heavy_DN();
	const float &weight_btagsf_light_DN();
	const float &weight_btagsf_fastsim_UP();
	const float &weight_btagsf_fastsim_DN();
	const float &weight_lepSF();
	const float &weight_lepSF_up();
	const float &weight_lepSF_down();
	const float &weight_vetoLepSF();
	const float &weight_vetoLepSF_up();
	const float &weight_vetoLepSF_down();
	const float &weight_lepSF_fastSim();
	const float &weight_lepSF_fastSim_up();
	const float &weight_lepSF_fastSim_down();
	const float &weight_ISR();
	const float &weight_ISRup();
	const float &weight_ISRdown();
	const float &weight_PU();
	const float &weight_PUup();
	const float &weight_PUdown();
	const vector<string> &sparms_names();
	const vector<float> &sparms_values();
	const int &sparms_subProcessId();
	const float &mass_lsp();
	const float &mass_chargino();
	const float &mass_stop();
	const float &mass_gluino();
	const float &genmet();
	const float &genmet_phi();
	const float &nupt();
	const float &genht();
	const bool &PassTrackVeto();
	const bool &PassTauVeto();
	const float &topness();
	const float &topnessMod();
	const float &topnessMod_rl();
	const float &Mlb_closestb();
	const int &HLT_SingleEl();
	const int &HLT_SingleMu();
	const int &HLT_MET();
	const int &HLT_MET100_MHT100();
	const int &HLT_DiEl();
	const int &HLT_DiMu();
	const int &HLT_MuE();
	const int &HLT_Photon90_CaloIdL_PFHT500();
	const int &HLT_Photon22_R9Id90_HE10_IsoM();
	const int &HLT_Photon30_R9Id90_HE10_IsoM();
	const int &HLT_Photon36_R9Id90_HE10_IsoM();
	const int &HLT_Photon50_R9Id90_HE10_IsoM();
	const int &HLT_Photon75_R9Id90_HE10_IsoM();
	const int &HLT_Photon90_R9Id90_HE10_IsoM();
	const int &HLT_Photon120_R9Id90_HE10_IsoM();
	const int &HLT_Photon165_R9Id90_HE10_IsoM();
	const int &HLT_Photon175();
	const int &HLT_Photon165_HE10();
	const int &nPhotons();
	const int &ph_ngoodjets();
	const int &ph_ngoodbtags();
	const float &filt_met();
	const float &hardgenpt();
	const float &filt_badChargedCandidateFilter();
	const float &filt_badMuonFilter();
	const float &calomet();
	const float &calomet_phi();
	const int &lep1_pdgid();
	const int &lep1_production_type();
	const float &lep1_MiniIso();
	const float &lep1_relIso();
	const bool &lep1_passLooseID();
	const bool &lep1_passMediumID();
	const bool &lep1_passTightID();
	const bool &lep1_passVeto();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4();
	const int &lep1_mc_motherid();
	const int &lep2_pdgid();
	const int &lep2_production_type();
	const float &lep2_MiniIso();
	const float &lep2_relIso();
	const bool &lep2_passLooseID();
	const bool &lep2_passMediumID();
	const bool &lep2_passTightID();
	const bool &lep2_passVeto();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4();
	const int &lep2_mc_motherid();
	const vector<float> &ph_sigmaIEtaEta_fill5x5();
	const vector<float> &ph_hOverE();
	const vector<float> &ph_r9();
	const vector<float> &ph_chiso();
	const vector<float> &ph_nhiso();
	const vector<float> &ph_phiso();
	const vector<bool> &ph_idCutBased();
	const vector<int> &ph_overlapJetId();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ph_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ph_mcp4();
	const vector<float> &ph_pt();
	const vector<float> &ph_eta();
	const vector<float> &ph_phi();
	const vector<float> &ph_mass();
	const vector<int> &ph_mcMatchId();
	const vector<float> &ph_genIso04();
	const vector<float> &ph_drMinParton();
	const int &ngoodjets();
	const int &ngoodbtags();
	const float &ak4_HT();
	const float &ak4_htratiom();
	const vector<float> &dphi_ak4pfjet_met();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4pfjets_p4();
	const vector<bool> &ak4pfjets_passMEDbtag();
	const vector<float> &ak4pfjets_CSV();
	const vector<float> &ak4pfjets_mva();
	const vector<int> &ak4pfjets_parton_flavor();
	const vector<int> &ak4pfjets_hadron_flavor();
	const vector<bool> &ak4pfjets_loose_puid();
	const vector<bool> &ak4pfjets_loose_pfid();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadMEDbjet_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadbtag_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4genjets_p4();
	const vector<bool> &genleps_isfromt();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_p4();
	const vector<int> &genleps_id();
	const vector<int> &genleps__genpsidx();
	const vector<int> &genleps_status();
	const vector<bool> &genleps_fromHardProcessDecayed();
	const vector<bool> &genleps_fromHardProcessFinalState();
	const vector<bool> &genleps_isHardProcess();
	const vector<bool> &genleps_isLastCopy();
	const vector<int> &genleps_gentaudecay();
	const int &gen_nfromtleps_();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_motherp4();
	const vector<int> &genleps_motherid();
	const vector<int> &genleps_motheridx();
	const vector<int> &genleps_motherstatus();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_gmotherp4();
	const vector<int> &genleps_gmotherid();
	const vector<int> &genleps_gmotheridx();
	const vector<int> &genleps_gmotherstatus();
	const vector<bool> &gennus_isfromt();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_p4();
	const vector<int> &gennus_id();
	const vector<int> &gennus__genpsidx();
	const vector<int> &gennus_status();
	const vector<bool> &gennus_fromHardProcessDecayed();
	const vector<bool> &gennus_fromHardProcessFinalState();
	const vector<bool> &gennus_isHardProcess();
	const vector<bool> &gennus_isLastCopy();
	const vector<int> &gennus_gentaudecay();
	const int &gen_nfromtnus_();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_motherp4();
	const vector<int> &gennus_motherid();
	const vector<int> &gennus_motheridx();
	const vector<int> &gennus_motherstatus();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_gmotherp4();
	const vector<int> &gennus_gmotherid();
	const vector<int> &gennus_gmotheridx();
	const vector<int> &gennus_gmotherstatus();
	const vector<bool> &genqs_isfromt();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_p4();
	const vector<int> &genqs_id();
	const vector<int> &genqs__genpsidx();
	const vector<int> &genqs_status();
	const vector<bool> &genqs_fromHardProcessDecayed();
	const vector<bool> &genqs_fromHardProcessFinalState();
	const vector<bool> &genqs_isHardProcess();
	const vector<bool> &genqs_isLastCopy();
	const vector<int> &genqs_gentaudecay();
	const int &gen_nfromtqs_();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_motherp4();
	const vector<int> &genqs_motherid();
	const vector<int> &genqs_motheridx();
	const vector<int> &genqs_motherstatus();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_gmotherp4();
	const vector<int> &genqs_gmotherid();
	const vector<int> &genqs_gmotheridx();
	const vector<int> &genqs_gmotherstatus();
	const vector<bool> &genbosons_isfromt();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_p4();
	const vector<int> &genbosons_id();
	const vector<int> &genbosons__genpsidx();
	const vector<int> &genbosons_status();
	const vector<bool> &genbosons_fromHardProcessDecayed();
	const vector<bool> &genbosons_fromHardProcessFinalState();
	const vector<bool> &genbosons_isHardProcess();
	const vector<bool> &genbosons_isLastCopy();
	const vector<int> &genbosons_gentaudecay();
	const int &gen_nfromtbosons_();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_motherp4();
	const vector<int> &genbosons_motherid();
	const vector<int> &genbosons_motheridx();
	const vector<int> &genbosons_motherstatus();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_gmotherp4();
	const vector<int> &genbosons_gmotherid();
	const vector<int> &genbosons_gmotheridx();
	const vector<int> &genbosons_gmotherstatus();
	const vector<bool> &gensusy_isfromt();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_p4();
	const vector<int> &gensusy_id();
	const vector<int> &gensusy__genpsidx();
	const vector<int> &gensusy_status();
	const vector<bool> &gensusy_fromHardProcessDecayed();
	const vector<bool> &gensusy_fromHardProcessFinalState();
	const vector<bool> &gensusy_isHardProcess();
	const vector<bool> &gensusy_isLastCopy();
	const vector<int> &gensusy_gentaudecay();
	const int &gen_nfromtsusy_();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_motherp4();
	const vector<int> &gensusy_motherid();
	const vector<int> &gensusy_motheridx();
	const vector<int> &gensusy_motherstatus();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_gmotherp4();
	const vector<int> &gensusy_gmotherid();
	const vector<int> &gensusy_gmotheridx();
	const vector<int> &gensusy_gmotherstatus();
	const vector<TString> &tau_IDnames();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_leadtrack_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_leadneutral_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_p4();
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &tau_isocand_p4();
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &tau_sigcand_p4();
	const vector<vector<float> > &tau_ID();
	const vector<float> &tau_passID();
	const int &ngoodtaus();
	const vector<float> &tau_againstMuonTight();
	const vector<float> &tau_againstElectronLoose();
	const vector<bool> &tau_isVetoTau();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &isoTracks_p4();
	const vector<int> &isoTracks_charge();
	const vector<float> &isoTracks_absIso();
	const vector<float> &isoTracks_dz();
	const vector<int> &isoTracks_pdgId();
	const vector<bool> &isoTracks_isVetoTrack();
	const vector<bool> &isoTracks_isVetoTrack_v2();
	const vector<bool> &isoTracks_isVetoTrack_v3();
}
#endif
