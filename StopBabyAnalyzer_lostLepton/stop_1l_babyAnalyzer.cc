#include "stop_1l_babyAnalyzer.h"
stop_1l_babyAnalyzer babyAnalyzer;
namespace stop_1l {
	const unsigned int &run() { return babyAnalyzer.run(); }
	const unsigned int &ls() { return babyAnalyzer.ls(); }
	const unsigned int &evt() { return babyAnalyzer.evt(); }
	const int &nvtxs() { return babyAnalyzer.nvtxs(); }
	const int &pu_nvtxs() { return babyAnalyzer.pu_nvtxs(); }
	const float &pfmet() { return babyAnalyzer.pfmet(); }
	const float &pfmet_phi() { return babyAnalyzer.pfmet_phi(); }
	const float &scale1fb() { return babyAnalyzer.scale1fb(); }
	const float &xsec() { return babyAnalyzer.xsec(); }
	const float &kfactor() { return babyAnalyzer.kfactor(); }
	const float &pu_ntrue() { return babyAnalyzer.pu_ntrue(); }
	const int &ngoodleps() { return babyAnalyzer.ngoodleps(); }
	const int &nvetoleps() { return babyAnalyzer.nvetoleps(); }
	const bool &is_data() { return babyAnalyzer.is_data(); }
	const string &dataset() { return babyAnalyzer.dataset(); }
	const string &filename() { return babyAnalyzer.filename(); }
	const string &cms3tag() { return babyAnalyzer.cms3tag(); }
	const unsigned int &nEvents() { return babyAnalyzer.nEvents(); }
	const unsigned int &nEvents_goodvtx() { return babyAnalyzer.nEvents_goodvtx(); }
	const unsigned int &nEvents_MET30() { return babyAnalyzer.nEvents_MET30(); }
	const unsigned int &nEvents_1goodlep() { return babyAnalyzer.nEvents_1goodlep(); }
	const unsigned int &nEvents_2goodjets() { return babyAnalyzer.nEvents_2goodjets(); }
	const int &genlepsfromtop() { return babyAnalyzer.genlepsfromtop(); }
	const float &MT2W() { return babyAnalyzer.MT2W(); }
	const float &MT2W_lep2() { return babyAnalyzer.MT2W_lep2(); }
	const float &mindphi_met_j1_j2() { return babyAnalyzer.mindphi_met_j1_j2(); }
	const float &mt_met_lep() { return babyAnalyzer.mt_met_lep(); }
	const float &mt_met_lep2() { return babyAnalyzer.mt_met_lep2(); }
	const float &dR_lep_leadb() { return babyAnalyzer.dR_lep_leadb(); }
	const float &dR_lep2_leadb() { return babyAnalyzer.dR_lep2_leadb(); }
	const float &hadronic_top_chi2() { return babyAnalyzer.hadronic_top_chi2(); }
	const float &dphi_Wlep() { return babyAnalyzer.dphi_Wlep(); }
	const float &MET_over_sqrtHT() { return babyAnalyzer.MET_over_sqrtHT(); }
	const float &ak4pfjets_rho() { return babyAnalyzer.ak4pfjets_rho(); }
	const vector<string> &sparms_comment() { return babyAnalyzer.sparms_comment(); }
	const vector<string> &sparms_names() { return babyAnalyzer.sparms_names(); }
	const float &sparms_filterEfficiency() { return babyAnalyzer.sparms_filterEfficiency(); }
	const float &sparms_pdfScale() { return babyAnalyzer.sparms_pdfScale(); }
	const float &sparms_pdfWeight1() { return babyAnalyzer.sparms_pdfWeight1(); }
	const float &sparms_pdfWeight2() { return babyAnalyzer.sparms_pdfWeight2(); }
	const float &sparms_weight() { return babyAnalyzer.sparms_weight(); }
	const float &sparms_xsec() { return babyAnalyzer.sparms_xsec(); }
	const vector<float> &sparms_values() { return babyAnalyzer.sparms_values(); }
	const int &sparms_subProcessId() { return babyAnalyzer.sparms_subProcessId(); }
	const float &mass_lsp() { return babyAnalyzer.mass_lsp(); }
	const float &mass_chargino() { return babyAnalyzer.mass_chargino(); }
	const float &mass_stop() { return babyAnalyzer.mass_stop(); }
	const float &genmet() { return babyAnalyzer.genmet(); }
	const float &genmet_phi() { return babyAnalyzer.genmet_phi(); }
	const bool &PassTrackVeto() { return babyAnalyzer.PassTrackVeto(); }
	const bool &PassTauVeto() { return babyAnalyzer.PassTauVeto(); }
	const float &EA_all_rho() { return babyAnalyzer.EA_all_rho(); }
	const float &EA_allcalo_rho() { return babyAnalyzer.EA_allcalo_rho(); }
	const float &EA_centralcalo_rho() { return babyAnalyzer.EA_centralcalo_rho(); }
	const float &EA_centralchargedpileup_rho() { return babyAnalyzer.EA_centralchargedpileup_rho(); }
	const float &EA_centralneutral_rho() { return babyAnalyzer.EA_centralneutral_rho(); }
	const float &topness() { return babyAnalyzer.topness(); }
	const float &Topness_lep2() { return babyAnalyzer.Topness_lep2(); }
	const float &TopnessMod_lep1() { return babyAnalyzer.TopnessMod_lep1(); }
	const float &TopnessMod_lep2() { return babyAnalyzer.TopnessMod_lep2(); }
	const float &MT2_lb_b_lep1() { return babyAnalyzer.MT2_lb_b_lep1(); }
	const float &MT2_lb_b_lep2() { return babyAnalyzer.MT2_lb_b_lep2(); }
	const float &MT2_lb_b_mass_lep1() { return babyAnalyzer.MT2_lb_b_mass_lep1(); }
	const float &MT2_lb_b_mass_lep2() { return babyAnalyzer.MT2_lb_b_mass_lep2(); }
	const float &MT2_lb_bqq_lep1() { return babyAnalyzer.MT2_lb_bqq_lep1(); }
	const float &MT2_lb_bqq_lep2() { return babyAnalyzer.MT2_lb_bqq_lep2(); }
	const float &MT2_lb_bqq_mass_lep1() { return babyAnalyzer.MT2_lb_bqq_mass_lep1(); }
	const float &MT2_lb_bqq_mass_lep2() { return babyAnalyzer.MT2_lb_bqq_mass_lep2(); }
	const float &Mlb_closestb() { return babyAnalyzer.Mlb_closestb(); }
	const float &Mlb_lead_bdiscr() { return babyAnalyzer.Mlb_lead_bdiscr(); }
	const float &Mlb_closestb_lep2() { return babyAnalyzer.Mlb_closestb_lep2(); }
	const float &Mlb_lead_bdiscr_lep2() { return babyAnalyzer.Mlb_lead_bdiscr_lep2(); }
	const float &M3b() { return babyAnalyzer.M3b(); }
	const float &M3b_lep2() { return babyAnalyzer.M3b_lep2(); }
	const int &HLT_SingleEl() { return babyAnalyzer.HLT_SingleEl(); }
	const int &HLT_SingleMu() { return babyAnalyzer.HLT_SingleMu(); }
	const int &HLT_MET170() { return babyAnalyzer.HLT_MET170(); }
	const int &HLT_ht350met120() { return babyAnalyzer.HLT_ht350met120(); }
	const int &HLT_MET120Btag() { return babyAnalyzer.HLT_MET120Btag(); }
	const int &HLT_MET120Mu5() { return babyAnalyzer.HLT_MET120Mu5(); }
	const float &pu_weight() { return babyAnalyzer.pu_weight(); }
	const float &lep_sf() { return babyAnalyzer.lep_sf(); }
	const float &btag_sf() { return babyAnalyzer.btag_sf(); }
	const float &HLT_SingleMu_eff() { return babyAnalyzer.HLT_SingleMu_eff(); }
	const float &HLT_SingleMu_eff() { return babyAnalyzer.HLT_SingleMu_eff(); }
	const bool &lep1_is_mu() { return babyAnalyzer.lep1_is_mu(); }
	const bool &lep1_is_el() { return babyAnalyzer.lep1_is_el(); }
	const int &lep1_charge() { return babyAnalyzer.lep1_charge(); }
	const int &lep1_pdgid() { return babyAnalyzer.lep1_pdgid(); }
	const int &lep1_type() { return babyAnalyzer.lep1_type(); }
	const int &lep1_production_type() { return babyAnalyzer.lep1_production_type(); }
	const float &lep1_d0() { return babyAnalyzer.lep1_d0(); }
	const float &lep1_d0err() { return babyAnalyzer.lep1_d0err(); }
	const float &lep1_dz() { return babyAnalyzer.lep1_dz(); }
	const float &lep1_dzerr() { return babyAnalyzer.lep1_dzerr(); }
	const float &lep1_sigmaIEtaEta_fill5x5() { return babyAnalyzer.lep1_sigmaIEtaEta_fill5x5(); }
	const float &lep1_dEtaIn() { return babyAnalyzer.lep1_dEtaIn(); }
	const float &lep1_dPhiIn() { return babyAnalyzer.lep1_dPhiIn(); }
	const float &lep1_hOverE() { return babyAnalyzer.lep1_hOverE(); }
	const float &lep1_ooEmooP() { return babyAnalyzer.lep1_ooEmooP(); }
	const int &lep1_expectedMissingInnerHits() { return babyAnalyzer.lep1_expectedMissingInnerHits(); }
	const bool &lep1_conversionVeto() { return babyAnalyzer.lep1_conversionVeto(); }
	const float &lep1_etaSC() { return babyAnalyzer.lep1_etaSC(); }
	const float &lep1_ChiSqr() { return babyAnalyzer.lep1_ChiSqr(); }
	const float &lep1_chiso() { return babyAnalyzer.lep1_chiso(); }
	const float &lep1_nhiso() { return babyAnalyzer.lep1_nhiso(); }
	const float &lep1_emiso() { return babyAnalyzer.lep1_emiso(); }
	const float &lep1_deltaBeta() { return babyAnalyzer.lep1_deltaBeta(); }
	const float &lep1_relIso03DB() { return babyAnalyzer.lep1_relIso03DB(); }
	const float &lep1_relIso03EA() { return babyAnalyzer.lep1_relIso03EA(); }
	const float &lep1_relIso04DB() { return babyAnalyzer.lep1_relIso04DB(); }
	const float &lep1_miniRelIsoDB() { return babyAnalyzer.lep1_miniRelIsoDB(); }
	const float &lep1_miniRelIsoEA() { return babyAnalyzer.lep1_miniRelIsoEA(); }
	const float &lep1_MiniIso() { return babyAnalyzer.lep1_MiniIso(); }
	const int &lep1_mcid() { return babyAnalyzer.lep1_mcid(); }
	const int &lep1_mcstatus() { return babyAnalyzer.lep1_mcstatus(); }
	const int &lep1_mc3dr() { return babyAnalyzer.lep1_mc3dr(); }
	const int &lep1_mc3id() { return babyAnalyzer.lep1_mc3id(); }
	const int &lep1_mc3idx() { return babyAnalyzer.lep1_mc3idx(); }
	const int &lep1_mc3motherid() { return babyAnalyzer.lep1_mc3motherid(); }
	const int &lep1_mc3motheridx() { return babyAnalyzer.lep1_mc3motheridx(); }
	const bool &lep1_is_eleid_loose() { return babyAnalyzer.lep1_is_eleid_loose(); }
	const bool &lep1_is_eleid_medium() { return babyAnalyzer.lep1_is_eleid_medium(); }
	const bool &lep1_is_eleid_tight() { return babyAnalyzer.lep1_is_eleid_tight(); }
	const bool &lep1_is_phys14_loose_noIso() { return babyAnalyzer.lep1_is_phys14_loose_noIso(); }
	const bool &lep1_is_phys14_medium_noIso() { return babyAnalyzer.lep1_is_phys14_medium_noIso(); }
	const bool &lep1_is_phys14_tight_noIso() { return babyAnalyzer.lep1_is_phys14_tight_noIso(); }
	const float &lep1_eoverpin() { return babyAnalyzer.lep1_eoverpin(); }
	const bool &lep1_is_muoid_loose() { return babyAnalyzer.lep1_is_muoid_loose(); }
	const bool &lep1_is_muoid_medium() { return babyAnalyzer.lep1_is_muoid_medium(); }
	const bool &lep1_is_muoid_tight() { return babyAnalyzer.lep1_is_muoid_tight(); }
	const float &lep1_ip3d() { return babyAnalyzer.lep1_ip3d(); }
	const float &lep1_ip3derr() { return babyAnalyzer.lep1_ip3derr(); }
	const bool &lep1_is_pfmu() { return babyAnalyzer.lep1_is_pfmu(); }
	const bool &lep1_passMediumID() { return babyAnalyzer.lep1_passMediumID(); }
	const bool &lep1_passVeto() { return babyAnalyzer.lep1_passVeto(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return babyAnalyzer.lep1_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4() { return babyAnalyzer.lep1_mcp4(); }
	const float &lep1_pt() { return babyAnalyzer.lep1_pt(); }
	const float &lep1_eta() { return babyAnalyzer.lep1_eta(); }
	const float &lep1_phi() { return babyAnalyzer.lep1_phi(); }
	const float &lep1_mass() { return babyAnalyzer.lep1_mass(); }
	const bool &lep2_is_mu() { return babyAnalyzer.lep2_is_mu(); }
	const bool &lep2_is_el() { return babyAnalyzer.lep2_is_el(); }
	const int &lep2_charge() { return babyAnalyzer.lep2_charge(); }
	const int &lep2_pdgid() { return babyAnalyzer.lep2_pdgid(); }
	const int &lep2_type() { return babyAnalyzer.lep2_type(); }
	const int &lep2_production_type() { return babyAnalyzer.lep2_production_type(); }
	const float &lep2_d0() { return babyAnalyzer.lep2_d0(); }
	const float &lep2_d0err() { return babyAnalyzer.lep2_d0err(); }
	const float &lep2_dz() { return babyAnalyzer.lep2_dz(); }
	const float &lep2_dzerr() { return babyAnalyzer.lep2_dzerr(); }
	const float &lep2_sigmaIEtaEta_fill5x5() { return babyAnalyzer.lep2_sigmaIEtaEta_fill5x5(); }
	const float &lep2_dEtaIn() { return babyAnalyzer.lep2_dEtaIn(); }
	const float &lep2_dPhiIn() { return babyAnalyzer.lep2_dPhiIn(); }
	const float &lep2_hOverE() { return babyAnalyzer.lep2_hOverE(); }
	const float &lep2_ooEmooP() { return babyAnalyzer.lep2_ooEmooP(); }
	const int &lep2_expectedMissingInnerHits() { return babyAnalyzer.lep2_expectedMissingInnerHits(); }
	const bool &lep2_conversionVeto() { return babyAnalyzer.lep2_conversionVeto(); }
	const float &lep2_etaSC() { return babyAnalyzer.lep2_etaSC(); }
	const float &lep2_ChiSqr() { return babyAnalyzer.lep2_ChiSqr(); }
	const float &lep2_chiso() { return babyAnalyzer.lep2_chiso(); }
	const float &lep2_nhiso() { return babyAnalyzer.lep2_nhiso(); }
	const float &lep2_emiso() { return babyAnalyzer.lep2_emiso(); }
	const float &lep2_deltaBeta() { return babyAnalyzer.lep2_deltaBeta(); }
	const float &lep2_relIso03DB() { return babyAnalyzer.lep2_relIso03DB(); }
	const float &lep2_relIso03EA() { return babyAnalyzer.lep2_relIso03EA(); }
	const float &lep2_relIso04DB() { return babyAnalyzer.lep2_relIso04DB(); }
	const float &lep2_miniRelIsoDB() { return babyAnalyzer.lep2_miniRelIsoDB(); }
	const float &lep2_miniRelIsoEA() { return babyAnalyzer.lep2_miniRelIsoEA(); }
	const float &lep2_MiniIso() { return babyAnalyzer.lep2_MiniIso(); }
	const int &lep2_mcid() { return babyAnalyzer.lep2_mcid(); }
	const int &lep2_mcstatus() { return babyAnalyzer.lep2_mcstatus(); }
	const int &lep2_mc3dr() { return babyAnalyzer.lep2_mc3dr(); }
	const int &lep2_mc3id() { return babyAnalyzer.lep2_mc3id(); }
	const int &lep2_mc3idx() { return babyAnalyzer.lep2_mc3idx(); }
	const int &lep2_mc3motherid() { return babyAnalyzer.lep2_mc3motherid(); }
	const int &lep2_mc3motheridx() { return babyAnalyzer.lep2_mc3motheridx(); }
	const bool &lep2_is_eleid_loose() { return babyAnalyzer.lep2_is_eleid_loose(); }
	const bool &lep2_is_eleid_medium() { return babyAnalyzer.lep2_is_eleid_medium(); }
	const bool &lep2_is_eleid_tight() { return babyAnalyzer.lep2_is_eleid_tight(); }
	const bool &lep2_is_phys14_loose_noIso() { return babyAnalyzer.lep2_is_phys14_loose_noIso(); }
	const bool &lep2_is_phys14_medium_noIso() { return babyAnalyzer.lep2_is_phys14_medium_noIso(); }
	const bool &lep2_is_phys14_tight_noIso() { return babyAnalyzer.lep2_is_phys14_tight_noIso(); }
	const float &lep2_eoverpin() { return babyAnalyzer.lep2_eoverpin(); }
	const bool &lep2_is_muoid_loose() { return babyAnalyzer.lep2_is_muoid_loose(); }
	const bool &lep2_is_muoid_medium() { return babyAnalyzer.lep2_is_muoid_medium(); }
	const bool &lep2_is_muoid_tight() { return babyAnalyzer.lep2_is_muoid_tight(); }
	const float &lep2_ip3d() { return babyAnalyzer.lep2_ip3d(); }
	const float &lep2_ip3derr() { return babyAnalyzer.lep2_ip3derr(); }
	const bool &lep2_is_pfmu() { return babyAnalyzer.lep2_is_pfmu(); }
	const bool &lep2_passMediumID() { return babyAnalyzer.lep2_passMediumID(); }
	const bool &lep2_passVeto() { return babyAnalyzer.lep2_passVeto(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return babyAnalyzer.lep2_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4() { return babyAnalyzer.lep2_mcp4(); }
	const float &lep2_pt() { return babyAnalyzer.lep2_pt(); }
	const float &lep2_eta() { return babyAnalyzer.lep2_eta(); }
	const float &lep2_phi() { return babyAnalyzer.lep2_phi(); }
	const float &lep2_mass() { return babyAnalyzer.lep2_mass(); }
	const int &nGoodGenJets() { return babyAnalyzer.nGoodGenJets(); }
	const int &ngoodjets() { return babyAnalyzer.ngoodjets(); }
	const int &ak8GoodPFJets() { return babyAnalyzer.ak8GoodPFJets(); }
	const int &ngoodbtags() { return babyAnalyzer.ngoodbtags(); }
	const float &ak4_HT() { return babyAnalyzer.ak4_HT(); }
	const float &ak4_htssm() { return babyAnalyzer.ak4_htssm(); }
	const float &ak4_htosm() { return babyAnalyzer.ak4_htosm(); }
	const float &ak4_htratiom() { return babyAnalyzer.ak4_htratiom(); }
	const vector<float> &dphi_ak4pfjet_met() { return babyAnalyzer.dphi_ak4pfjet_met(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4pfjets_p4() { return babyAnalyzer.ak4pfjets_p4(); }
	const vector<float> &ak4pfjets_pt() { return babyAnalyzer.ak4pfjets_pt(); }
	const vector<float> &ak4pfjets_eta() { return babyAnalyzer.ak4pfjets_eta(); }
	const vector<float> &ak4pfjets_phi() { return babyAnalyzer.ak4pfjets_phi(); }
	const vector<float> &ak4pfjets_mass() { return babyAnalyzer.ak4pfjets_mass(); }
	const vector<float> &ak4pfjets_qg_disc() { return babyAnalyzer.ak4pfjets_qg_disc(); }
	const vector<float> &ak4pfjets_CSV() { return babyAnalyzer.ak4pfjets_CSV(); }
	const vector<float> &ak4pfjets_puid() { return babyAnalyzer.ak4pfjets_puid(); }
	const vector<int> &ak4pfjets_parton_flavor() { return babyAnalyzer.ak4pfjets_parton_flavor(); }
	const vector<bool> &ak4pfjets_loose_puid() { return babyAnalyzer.ak4pfjets_loose_puid(); }
	const vector<bool> &ak4pfjets_loose_pfid() { return babyAnalyzer.ak4pfjets_loose_pfid(); }
	const vector<bool> &ak4pfjets_medium_pfid() { return babyAnalyzer.ak4pfjets_medium_pfid(); }
	const vector<bool> &ak4pfjets_tight_pfid() { return babyAnalyzer.ak4pfjets_tight_pfid(); }
	const vector<float> &ak4pfjets_MEDbjet_pt() { return babyAnalyzer.ak4pfjets_MEDbjet_pt(); }
	const float &ak4pfjets_leadMEDbjet_pt() { return babyAnalyzer.ak4pfjets_leadMEDbjet_pt(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadMEDbjet_p4() { return babyAnalyzer.ak4pfjets_leadMEDbjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadbtag_p4() { return babyAnalyzer.ak4pfjets_leadbtag_p4(); }
	const vector<float> &ak4pfjets_chf() { return babyAnalyzer.ak4pfjets_chf(); }
	const vector<float> &ak4pfjets_nhf() { return babyAnalyzer.ak4pfjets_nhf(); }
	const vector<float> &ak4pfjets_cef() { return babyAnalyzer.ak4pfjets_cef(); }
	const vector<float> &ak4pfjets_nef() { return babyAnalyzer.ak4pfjets_nef(); }
	const vector<int> &ak4pfjets_cm() { return babyAnalyzer.ak4pfjets_cm(); }
	const vector<int> &ak4pfjets_nm() { return babyAnalyzer.ak4pfjets_nm(); }
	const vector<int> &ak4pfjets_mc3dr() { return babyAnalyzer.ak4pfjets_mc3dr(); }
	const vector<int> &ak4pfjets_mc3id() { return babyAnalyzer.ak4pfjets_mc3id(); }
	const vector<int> &ak4pfjets_mc3idx() { return babyAnalyzer.ak4pfjets_mc3idx(); }
	const vector<int> &ak4pfjets_mcmotherid() { return babyAnalyzer.ak4pfjets_mcmotherid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjet_overlep1_p4() { return babyAnalyzer.ak4pfjet_overlep1_p4(); }
	const float &ak4pfjet_overlep1_CSV() { return babyAnalyzer.ak4pfjet_overlep1_CSV(); }
	const float &ak4pfjet_overlep1_pu_id() { return babyAnalyzer.ak4pfjet_overlep1_pu_id(); }
	const float &ak4pfjet_overlep1_chf() { return babyAnalyzer.ak4pfjet_overlep1_chf(); }
	const float &ak4pfjet_overlep1_nhf() { return babyAnalyzer.ak4pfjet_overlep1_nhf(); }
	const float &ak4pfjet_overlep1_cef() { return babyAnalyzer.ak4pfjet_overlep1_cef(); }
	const float &ak4pfjet_overlep1_nef() { return babyAnalyzer.ak4pfjet_overlep1_nef(); }
	const int &ak4pfjet_overlep1_cm() { return babyAnalyzer.ak4pfjet_overlep1_cm(); }
	const int &ak4pfjet_overlep1_nm() { return babyAnalyzer.ak4pfjet_overlep1_nm(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjet_overlep2_p4() { return babyAnalyzer.ak4pfjet_overlep2_p4(); }
	const float &ak4pfjet_overlep2_CSV() { return babyAnalyzer.ak4pfjet_overlep2_CSV(); }
	const float &ak4pfjet_overlep2_pu_id() { return babyAnalyzer.ak4pfjet_overlep2_pu_id(); }
	const float &ak4pfjet_overlep2_chf() { return babyAnalyzer.ak4pfjet_overlep2_chf(); }
	const float &ak4pfjet_overlep2_nhf() { return babyAnalyzer.ak4pfjet_overlep2_nhf(); }
	const float &ak4pfjet_overlep2_cef() { return babyAnalyzer.ak4pfjet_overlep2_cef(); }
	const float &ak4pfjet_overlep2_nef() { return babyAnalyzer.ak4pfjet_overlep2_nef(); }
	const int &ak4pfjet_overlep2_cm() { return babyAnalyzer.ak4pfjet_overlep2_cm(); }
	const int &ak4pfjet_overlep2_nm() { return babyAnalyzer.ak4pfjet_overlep2_nm(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak8pfjets_p4() { return babyAnalyzer.ak8pfjets_p4(); }
	const vector<float> &ak8pfjets_tau1() { return babyAnalyzer.ak8pfjets_tau1(); }
	const vector<float> &ak8pfjets_tau2() { return babyAnalyzer.ak8pfjets_tau2(); }
	const vector<float> &ak8pfjets_tau3() { return babyAnalyzer.ak8pfjets_tau3(); }
	const vector<float> &ak8pfjets_top_mass() { return babyAnalyzer.ak8pfjets_top_mass(); }
	const vector<float> &ak8pfjets_pruned_mass() { return babyAnalyzer.ak8pfjets_pruned_mass(); }
	const vector<float> &ak8pfjets_trimmed_mass() { return babyAnalyzer.ak8pfjets_trimmed_mass(); }
	const vector<float> &ak8pfjets_filtered_mass() { return babyAnalyzer.ak8pfjets_filtered_mass(); }
	const vector<float> &ak8pfjets_pu_id() { return babyAnalyzer.ak8pfjets_pu_id(); }
	const vector<int> &ak8pfjets_parton_flavor() { return babyAnalyzer.ak8pfjets_parton_flavor(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4genjets_p4() { return babyAnalyzer.ak4genjets_p4(); }
	const vector<bool> &genels_isfromt() { return babyAnalyzer.genels_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genels_p4() { return babyAnalyzer.genels_p4(); }
	const vector<float> &genels_charge() { return babyAnalyzer.genels_charge(); }
	const vector<float> &genels_iso() { return babyAnalyzer.genels_iso(); }
	const vector<float> &genels_mass() { return babyAnalyzer.genels_mass(); }
	const vector<int> &genels_id() { return babyAnalyzer.genels_id(); }
	const vector<int> &genels__genpsidx() { return babyAnalyzer.genels__genpsidx(); }
	const vector<int> &genels_status() { return babyAnalyzer.genels_status(); }
	const vector<vector<int> > &genels_lepdaughter_id() { return babyAnalyzer.genels_lepdaughter_id(); }
	const vector<int> &genels_gentaudecay() { return babyAnalyzer.genels_gentaudecay(); }
	const int &gen_nfromtels_() { return babyAnalyzer.gen_nfromtels_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genels_motherp4() { return babyAnalyzer.genels_motherp4(); }
	const vector<float> &genels_mothercharge() { return babyAnalyzer.genels_mothercharge(); }
	const vector<int> &genels_motherid() { return babyAnalyzer.genels_motherid(); }
	const vector<int> &genels_motheridx() { return babyAnalyzer.genels_motheridx(); }
	const vector<int> &genels_motherstatus() { return babyAnalyzer.genels_motherstatus(); }
	const vector<bool> &genmus_isfromt() { return babyAnalyzer.genmus_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genmus_p4() { return babyAnalyzer.genmus_p4(); }
	const vector<float> &genmus_charge() { return babyAnalyzer.genmus_charge(); }
	const vector<float> &genmus_iso() { return babyAnalyzer.genmus_iso(); }
	const vector<float> &genmus_mass() { return babyAnalyzer.genmus_mass(); }
	const vector<int> &genmus_id() { return babyAnalyzer.genmus_id(); }
	const vector<int> &genmus__genpsidx() { return babyAnalyzer.genmus__genpsidx(); }
	const vector<int> &genmus_status() { return babyAnalyzer.genmus_status(); }
	const vector<vector<int> > &genmus_lepdaughter_id() { return babyAnalyzer.genmus_lepdaughter_id(); }
	const vector<int> &genmus_gentaudecay() { return babyAnalyzer.genmus_gentaudecay(); }
	const int &gen_nfromtmus_() { return babyAnalyzer.gen_nfromtmus_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genmus_motherp4() { return babyAnalyzer.genmus_motherp4(); }
	const vector<float> &genmus_mothercharge() { return babyAnalyzer.genmus_mothercharge(); }
	const vector<int> &genmus_motherid() { return babyAnalyzer.genmus_motherid(); }
	const vector<int> &genmus_motheridx() { return babyAnalyzer.genmus_motheridx(); }
	const vector<int> &genmus_motherstatus() { return babyAnalyzer.genmus_motherstatus(); }
	const vector<bool> &genleptau_els_isfromt() { return babyAnalyzer.genleptau_els_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleptau_els_p4() { return babyAnalyzer.genleptau_els_p4(); }
	const vector<float> &genleptau_els_charge() { return babyAnalyzer.genleptau_els_charge(); }
	const vector<float> &genleptau_els_iso() { return babyAnalyzer.genleptau_els_iso(); }
	const vector<float> &genleptau_els_mass() { return babyAnalyzer.genleptau_els_mass(); }
	const vector<int> &genleptau_els_id() { return babyAnalyzer.genleptau_els_id(); }
	const vector<int> &genleptau_els__genpsidx() { return babyAnalyzer.genleptau_els__genpsidx(); }
	const vector<int> &genleptau_els_status() { return babyAnalyzer.genleptau_els_status(); }
	const vector<vector<int> > &genleptau_els_lepdaughter_id() { return babyAnalyzer.genleptau_els_lepdaughter_id(); }
	const vector<int> &genleptau_els_gentaudecay() { return babyAnalyzer.genleptau_els_gentaudecay(); }
	const int &gen_nfromtleptau_els_() { return babyAnalyzer.gen_nfromtleptau_els_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleptau_els_motherp4() { return babyAnalyzer.genleptau_els_motherp4(); }
	const vector<float> &genleptau_els_mothercharge() { return babyAnalyzer.genleptau_els_mothercharge(); }
	const vector<int> &genleptau_els_motherid() { return babyAnalyzer.genleptau_els_motherid(); }
	const vector<int> &genleptau_els_motheridx() { return babyAnalyzer.genleptau_els_motheridx(); }
	const vector<int> &genleptau_els_motherstatus() { return babyAnalyzer.genleptau_els_motherstatus(); }
	const vector<bool> &genleptau_mus_isfromt() { return babyAnalyzer.genleptau_mus_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleptau_mus_p4() { return babyAnalyzer.genleptau_mus_p4(); }
	const vector<float> &genleptau_mus_charge() { return babyAnalyzer.genleptau_mus_charge(); }
	const vector<float> &genleptau_mus_iso() { return babyAnalyzer.genleptau_mus_iso(); }
	const vector<float> &genleptau_mus_mass() { return babyAnalyzer.genleptau_mus_mass(); }
	const vector<int> &genleptau_mus_id() { return babyAnalyzer.genleptau_mus_id(); }
	const vector<int> &genleptau_mus__genpsidx() { return babyAnalyzer.genleptau_mus__genpsidx(); }
	const vector<int> &genleptau_mus_status() { return babyAnalyzer.genleptau_mus_status(); }
	const vector<vector<int> > &genleptau_mus_lepdaughter_id() { return babyAnalyzer.genleptau_mus_lepdaughter_id(); }
	const vector<int> &genleptau_mus_gentaudecay() { return babyAnalyzer.genleptau_mus_gentaudecay(); }
	const int &gen_nfromtleptau_mus_() { return babyAnalyzer.gen_nfromtleptau_mus_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleptau_mus_motherp4() { return babyAnalyzer.genleptau_mus_motherp4(); }
	const vector<float> &genleptau_mus_mothercharge() { return babyAnalyzer.genleptau_mus_mothercharge(); }
	const vector<int> &genleptau_mus_motherid() { return babyAnalyzer.genleptau_mus_motherid(); }
	const vector<int> &genleptau_mus_motheridx() { return babyAnalyzer.genleptau_mus_motheridx(); }
	const vector<int> &genleptau_mus_motherstatus() { return babyAnalyzer.genleptau_mus_motherstatus(); }
	const vector<bool> &gentaus_isfromt() { return babyAnalyzer.gentaus_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gentaus_p4() { return babyAnalyzer.gentaus_p4(); }
	const vector<float> &gentaus_charge() { return babyAnalyzer.gentaus_charge(); }
	const vector<float> &gentaus_iso() { return babyAnalyzer.gentaus_iso(); }
	const vector<float> &gentaus_mass() { return babyAnalyzer.gentaus_mass(); }
	const vector<int> &gentaus_id() { return babyAnalyzer.gentaus_id(); }
	const vector<int> &gentaus__genpsidx() { return babyAnalyzer.gentaus__genpsidx(); }
	const vector<int> &gentaus_status() { return babyAnalyzer.gentaus_status(); }
	const vector<vector<int> > &gentaus_lepdaughter_id() { return babyAnalyzer.gentaus_lepdaughter_id(); }
	const vector<int> &gentaus_gentaudecay() { return babyAnalyzer.gentaus_gentaudecay(); }
	const int &gen_nfromttaus_() { return babyAnalyzer.gen_nfromttaus_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gentaus_motherp4() { return babyAnalyzer.gentaus_motherp4(); }
	const vector<float> &gentaus_mothercharge() { return babyAnalyzer.gentaus_mothercharge(); }
	const vector<int> &gentaus_motherid() { return babyAnalyzer.gentaus_motherid(); }
	const vector<int> &gentaus_motheridx() { return babyAnalyzer.gentaus_motheridx(); }
	const vector<int> &gentaus_motherstatus() { return babyAnalyzer.gentaus_motherstatus(); }
	const vector<bool> &gennus_isfromt() { return babyAnalyzer.gennus_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_p4() { return babyAnalyzer.gennus_p4(); }
	const vector<float> &gennus_charge() { return babyAnalyzer.gennus_charge(); }
	const vector<float> &gennus_iso() { return babyAnalyzer.gennus_iso(); }
	const vector<float> &gennus_mass() { return babyAnalyzer.gennus_mass(); }
	const vector<int> &gennus_id() { return babyAnalyzer.gennus_id(); }
	const vector<int> &gennus__genpsidx() { return babyAnalyzer.gennus__genpsidx(); }
	const vector<int> &gennus_status() { return babyAnalyzer.gennus_status(); }
	const vector<vector<int> > &gennus_lepdaughter_id() { return babyAnalyzer.gennus_lepdaughter_id(); }
	const vector<int> &gennus_gentaudecay() { return babyAnalyzer.gennus_gentaudecay(); }
	const int &gen_nfromtnus_() { return babyAnalyzer.gen_nfromtnus_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_motherp4() { return babyAnalyzer.gennus_motherp4(); }
	const vector<float> &gennus_mothercharge() { return babyAnalyzer.gennus_mothercharge(); }
	const vector<int> &gennus_motherid() { return babyAnalyzer.gennus_motherid(); }
	const vector<int> &gennus_motheridx() { return babyAnalyzer.gennus_motheridx(); }
	const vector<int> &gennus_motherstatus() { return babyAnalyzer.gennus_motherstatus(); }
	const vector<bool> &genbs_isfromt() { return babyAnalyzer.genbs_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbs_p4() { return babyAnalyzer.genbs_p4(); }
	const vector<float> &genbs_charge() { return babyAnalyzer.genbs_charge(); }
	const vector<float> &genbs_iso() { return babyAnalyzer.genbs_iso(); }
	const vector<float> &genbs_mass() { return babyAnalyzer.genbs_mass(); }
	const vector<int> &genbs_id() { return babyAnalyzer.genbs_id(); }
	const vector<int> &genbs__genpsidx() { return babyAnalyzer.genbs__genpsidx(); }
	const vector<int> &genbs_status() { return babyAnalyzer.genbs_status(); }
	const vector<vector<int> > &genbs_lepdaughter_id() { return babyAnalyzer.genbs_lepdaughter_id(); }
	const vector<int> &genbs_gentaudecay() { return babyAnalyzer.genbs_gentaudecay(); }
	const int &gen_nfromtbs_() { return babyAnalyzer.gen_nfromtbs_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbs_motherp4() { return babyAnalyzer.genbs_motherp4(); }
	const vector<float> &genbs_mothercharge() { return babyAnalyzer.genbs_mothercharge(); }
	const vector<int> &genbs_motherid() { return babyAnalyzer.genbs_motherid(); }
	const vector<int> &genbs_motheridx() { return babyAnalyzer.genbs_motheridx(); }
	const vector<int> &genbs_motherstatus() { return babyAnalyzer.genbs_motherstatus(); }
	const vector<bool> &gents_isfromt() { return babyAnalyzer.gents_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gents_p4() { return babyAnalyzer.gents_p4(); }
	const vector<float> &gents_charge() { return babyAnalyzer.gents_charge(); }
	const vector<float> &gents_iso() { return babyAnalyzer.gents_iso(); }
	const vector<float> &gents_mass() { return babyAnalyzer.gents_mass(); }
	const vector<int> &gents_id() { return babyAnalyzer.gents_id(); }
	const vector<int> &gents__genpsidx() { return babyAnalyzer.gents__genpsidx(); }
	const vector<int> &gents_status() { return babyAnalyzer.gents_status(); }
	const vector<vector<int> > &gents_lepdaughter_id() { return babyAnalyzer.gents_lepdaughter_id(); }
	const vector<int> &gents_gentaudecay() { return babyAnalyzer.gents_gentaudecay(); }
	const int &gen_nfromtts_() { return babyAnalyzer.gen_nfromtts_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gents_motherp4() { return babyAnalyzer.gents_motherp4(); }
	const vector<float> &gents_mothercharge() { return babyAnalyzer.gents_mothercharge(); }
	const vector<int> &gents_motherid() { return babyAnalyzer.gents_motherid(); }
	const vector<int> &gents_motheridx() { return babyAnalyzer.gents_motheridx(); }
	const vector<int> &gents_motherstatus() { return babyAnalyzer.gents_motherstatus(); }
	const vector<bool> &genqs_isfromt() { return babyAnalyzer.genqs_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_p4() { return babyAnalyzer.genqs_p4(); }
	const vector<float> &genqs_charge() { return babyAnalyzer.genqs_charge(); }
	const vector<float> &genqs_iso() { return babyAnalyzer.genqs_iso(); }
	const vector<float> &genqs_mass() { return babyAnalyzer.genqs_mass(); }
	const vector<int> &genqs_id() { return babyAnalyzer.genqs_id(); }
	const vector<int> &genqs__genpsidx() { return babyAnalyzer.genqs__genpsidx(); }
	const vector<int> &genqs_status() { return babyAnalyzer.genqs_status(); }
	const vector<vector<int> > &genqs_lepdaughter_id() { return babyAnalyzer.genqs_lepdaughter_id(); }
	const vector<int> &genqs_gentaudecay() { return babyAnalyzer.genqs_gentaudecay(); }
	const int &gen_nfromtqs_() { return babyAnalyzer.gen_nfromtqs_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_motherp4() { return babyAnalyzer.genqs_motherp4(); }
	const vector<float> &genqs_mothercharge() { return babyAnalyzer.genqs_mothercharge(); }
	const vector<int> &genqs_motherid() { return babyAnalyzer.genqs_motherid(); }
	const vector<int> &genqs_motheridx() { return babyAnalyzer.genqs_motheridx(); }
	const vector<int> &genqs_motherstatus() { return babyAnalyzer.genqs_motherstatus(); }
	const vector<bool> &genlsp_isfromt() { return babyAnalyzer.genlsp_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genlsp_p4() { return babyAnalyzer.genlsp_p4(); }
	const vector<float> &genlsp_charge() { return babyAnalyzer.genlsp_charge(); }
	const vector<float> &genlsp_iso() { return babyAnalyzer.genlsp_iso(); }
	const vector<float> &genlsp_mass() { return babyAnalyzer.genlsp_mass(); }
	const vector<int> &genlsp_id() { return babyAnalyzer.genlsp_id(); }
	const vector<int> &genlsp__genpsidx() { return babyAnalyzer.genlsp__genpsidx(); }
	const vector<int> &genlsp_status() { return babyAnalyzer.genlsp_status(); }
	const vector<vector<int> > &genlsp_lepdaughter_id() { return babyAnalyzer.genlsp_lepdaughter_id(); }
	const vector<int> &genlsp_gentaudecay() { return babyAnalyzer.genlsp_gentaudecay(); }
	const int &gen_nfromtlsp_() { return babyAnalyzer.gen_nfromtlsp_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genlsp_motherp4() { return babyAnalyzer.genlsp_motherp4(); }
	const vector<float> &genlsp_mothercharge() { return babyAnalyzer.genlsp_mothercharge(); }
	const vector<int> &genlsp_motherid() { return babyAnalyzer.genlsp_motherid(); }
	const vector<int> &genlsp_motheridx() { return babyAnalyzer.genlsp_motheridx(); }
	const vector<int> &genlsp_motherstatus() { return babyAnalyzer.genlsp_motherstatus(); }
	const vector<bool> &genstop_isfromt() { return babyAnalyzer.genstop_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genstop_p4() { return babyAnalyzer.genstop_p4(); }
	const vector<float> &genstop_charge() { return babyAnalyzer.genstop_charge(); }
	const vector<float> &genstop_iso() { return babyAnalyzer.genstop_iso(); }
	const vector<float> &genstop_mass() { return babyAnalyzer.genstop_mass(); }
	const vector<int> &genstop_id() { return babyAnalyzer.genstop_id(); }
	const vector<int> &genstop__genpsidx() { return babyAnalyzer.genstop__genpsidx(); }
	const vector<int> &genstop_status() { return babyAnalyzer.genstop_status(); }
	const vector<vector<int> > &genstop_lepdaughter_id() { return babyAnalyzer.genstop_lepdaughter_id(); }
	const vector<int> &genstop_gentaudecay() { return babyAnalyzer.genstop_gentaudecay(); }
	const int &gen_nfromtstop_() { return babyAnalyzer.gen_nfromtstop_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genstop_motherp4() { return babyAnalyzer.genstop_motherp4(); }
	const vector<float> &genstop_mothercharge() { return babyAnalyzer.genstop_mothercharge(); }
	const vector<int> &genstop_motherid() { return babyAnalyzer.genstop_motherid(); }
	const vector<int> &genstop_motheridx() { return babyAnalyzer.genstop_motheridx(); }
	const vector<int> &genstop_motherstatus() { return babyAnalyzer.genstop_motherstatus(); }
	const vector<TString> &tau_IDnames() { return babyAnalyzer.tau_IDnames(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_leadtrack_p4() { return babyAnalyzer.tau_leadtrack_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_leadneutral_p4() { return babyAnalyzer.tau_leadneutral_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &tau_p4() { return babyAnalyzer.tau_p4(); }
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &tau_isocand_p4() { return babyAnalyzer.tau_isocand_p4(); }
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &tau_sigcand_p4() { return babyAnalyzer.tau_sigcand_p4(); }
	const vector<float> &tau_mass() { return babyAnalyzer.tau_mass(); }
	const vector<vector<float> > &tau_ID() { return babyAnalyzer.tau_ID(); }
	const vector<float> &tau_charge() { return babyAnalyzer.tau_charge(); }
	const int &ngoodtaus() { return babyAnalyzer.ngoodtaus(); }
	const vector<float> &tau_againstMuonTight() { return babyAnalyzer.tau_againstMuonTight(); }
	const vector<float> &tau_againstElectronLoose() { return babyAnalyzer.tau_againstElectronLoose(); }
	const vector<bool> &tau_isVetoTau() { return babyAnalyzer.tau_isVetoTau(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &isoTracks_p4() { return babyAnalyzer.isoTracks_p4(); }
	const vector<int> &isoTracks_charge() { return babyAnalyzer.isoTracks_charge(); }
	const vector<float> &isoTracks_absIso() { return babyAnalyzer.isoTracks_absIso(); }
	const vector<float> &isoTracks_dz() { return babyAnalyzer.isoTracks_dz(); }
	const vector<int> &isoTracks_pdgId() { return babyAnalyzer.isoTracks_pdgId(); }
	const vector<int> &isoTracks_selectedidx() { return babyAnalyzer.isoTracks_selectedidx(); }
	const int &isoTracks_nselected() { return babyAnalyzer.isoTracks_nselected(); }
	const vector<bool> &isoTracks_isVetoTrack() { return babyAnalyzer.isoTracks_isVetoTrack(); }
}
