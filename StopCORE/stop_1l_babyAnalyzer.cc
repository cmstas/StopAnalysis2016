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
	const float &xsec_uncert() { return babyAnalyzer.xsec_uncert(); }
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
	const int &is0lep() { return babyAnalyzer.is0lep(); }
	const int &is1lep() { return babyAnalyzer.is1lep(); }
	const int &is2lep() { return babyAnalyzer.is2lep(); }
	const int &isZtoNuNu() { return babyAnalyzer.isZtoNuNu(); }
	const int &is1lepFromW() { return babyAnalyzer.is1lepFromW(); }
	const int &is1lepFromTop() { return babyAnalyzer.is1lepFromTop(); }
	const float &MT2W() { return babyAnalyzer.MT2W(); }
	const float &mindphi_met_j1_j2() { return babyAnalyzer.mindphi_met_j1_j2(); }
	const float &mt_met_lep() { return babyAnalyzer.mt_met_lep(); }
	const float &hadronic_top_chi2() { return babyAnalyzer.hadronic_top_chi2(); }
	const float &ak4pfjets_rho() { return babyAnalyzer.ak4pfjets_rho(); }
	const float &pdf_up_weight() { return babyAnalyzer.pdf_up_weight(); }
	const float &pdf_down_weight() { return babyAnalyzer.pdf_down_weight(); }
	const vector<string> &genweightsID() { return babyAnalyzer.genweightsID(); }
	const vector<float> &genweights() { return babyAnalyzer.genweights(); }
	const float &weight_btagsf() { return babyAnalyzer.weight_btagsf(); }
	const float &weight_btagsf_heavy_UP() { return babyAnalyzer.weight_btagsf_heavy_UP(); }
	const float &weight_btagsf_light_UP() { return babyAnalyzer.weight_btagsf_light_UP(); }
	const float &weight_btagsf_heavy_DN() { return babyAnalyzer.weight_btagsf_heavy_DN(); }
	const float &weight_btagsf_light_DN() { return babyAnalyzer.weight_btagsf_light_DN(); }
	const float &weight_lepSF() { return babyAnalyzer.weight_lepSF(); }
	const float &weight_lepSF_up() { return babyAnalyzer.weight_lepSF_up(); }
	const float &weight_lepSF_down() { return babyAnalyzer.weight_lepSF_down(); }
	const float &weight_vetoLepSF() { return babyAnalyzer.weight_vetoLepSF(); }
	const float &weight_vetoLepSF_up() { return babyAnalyzer.weight_vetoLepSF_up(); }
	const float &weight_vetoLepSF_down() { return babyAnalyzer.weight_vetoLepSF_down(); }
	const float &weight_lepSF_fastSim() { return babyAnalyzer.weight_lepSF_fastSim(); }
	const float &weight_lepSF_fastSim_up() { return babyAnalyzer.weight_lepSF_fastSim_up(); }
	const float &weight_lepSF_fastSim_down() { return babyAnalyzer.weight_lepSF_fastSim_down(); }
	const float &weight_ISR() { return babyAnalyzer.weight_ISR(); }
	const float &weight_ISRup() { return babyAnalyzer.weight_ISRup(); }
	const float &weight_ISRdown() { return babyAnalyzer.weight_ISRdown(); }
	const float &weight_PU() { return babyAnalyzer.weight_PU(); }
	const float &weight_PUup() { return babyAnalyzer.weight_PUup(); }
	const float &weight_PUdown() { return babyAnalyzer.weight_PUdown(); }
	const vector<string> &sparms_names() { return babyAnalyzer.sparms_names(); }
	const vector<float> &sparms_values() { return babyAnalyzer.sparms_values(); }
	const int &sparms_subProcessId() { return babyAnalyzer.sparms_subProcessId(); }
	const float &mass_lsp() { return babyAnalyzer.mass_lsp(); }
	const float &mass_chargino() { return babyAnalyzer.mass_chargino(); }
	const float &mass_stop() { return babyAnalyzer.mass_stop(); }
	const float &mass_gluino() { return babyAnalyzer.mass_gluino(); }
	const float &genmet() { return babyAnalyzer.genmet(); }
	const float &genmet_phi() { return babyAnalyzer.genmet_phi(); }
	const float &genht() { return babyAnalyzer.genht(); }
	const bool &PassTrackVeto() { return babyAnalyzer.PassTrackVeto(); }
	const bool &PassTauVeto() { return babyAnalyzer.PassTauVeto(); }
	const float &topness() { return babyAnalyzer.topness(); }
	const float &topnessMod() { return babyAnalyzer.topnessMod(); }
	const float &Mlb_closestb() { return babyAnalyzer.Mlb_closestb(); }
	const int &HLT_SingleEl() { return babyAnalyzer.HLT_SingleEl(); }
	const int &HLT_SingleMu() { return babyAnalyzer.HLT_SingleMu(); }
	const int &HLT_MET() { return babyAnalyzer.HLT_MET(); }
	const int &HLT_DiEl() { return babyAnalyzer.HLT_DiEl(); }
	const int &HLT_DiMu() { return babyAnalyzer.HLT_DiMu(); }
	const int &HLT_MuE() { return babyAnalyzer.HLT_MuE(); }
	const int &HLT_Photon90_CaloIdL_PFHT500() { return babyAnalyzer.HLT_Photon90_CaloIdL_PFHT500(); }
	const int &HLT_Photon22_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon22_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon30_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon30_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon36_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon36_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon50_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon50_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon75_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon75_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon90_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon90_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon120_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon120_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon165_R9Id90_HE10_IsoM() { return babyAnalyzer.HLT_Photon165_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon175() { return babyAnalyzer.HLT_Photon175(); }
	const int &HLT_Photon165_HE10() { return babyAnalyzer.HLT_Photon165_HE10(); }
	const int &nPhotons() { return babyAnalyzer.nPhotons(); }
	const int &ph_ngoodjets() { return babyAnalyzer.ph_ngoodjets(); }
	const int &ph_ngoodbtags() { return babyAnalyzer.ph_ngoodbtags(); }
	const float &filt_met() { return babyAnalyzer.filt_met(); }
	const float &hardgenpt() { return babyAnalyzer.hardgenpt(); }
	const int &lep1_pdgid() { return babyAnalyzer.lep1_pdgid(); }
	const int &lep1_production_type() { return babyAnalyzer.lep1_production_type(); }
	const float &lep1_MiniIso() { return babyAnalyzer.lep1_MiniIso(); }
	const float &lep1_relIso() { return babyAnalyzer.lep1_relIso(); }
	const bool &lep1_passLooseID() { return babyAnalyzer.lep1_passLooseID(); }
	const bool &lep1_passMediumID() { return babyAnalyzer.lep1_passMediumID(); }
	const bool &lep1_passTightID() { return babyAnalyzer.lep1_passTightID(); }
	const bool &lep1_passVeto() { return babyAnalyzer.lep1_passVeto(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return babyAnalyzer.lep1_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4() { return babyAnalyzer.lep1_mcp4(); }
	const int &lep1_mc_motherid() { return babyAnalyzer.lep1_mc_motherid(); }
	const int &lep2_pdgid() { return babyAnalyzer.lep2_pdgid(); }
	const int &lep2_production_type() { return babyAnalyzer.lep2_production_type(); }
	const float &lep2_MiniIso() { return babyAnalyzer.lep2_MiniIso(); }
	const float &lep2_relIso() { return babyAnalyzer.lep2_relIso(); }
	const bool &lep2_passLooseID() { return babyAnalyzer.lep2_passLooseID(); }
	const bool &lep2_passMediumID() { return babyAnalyzer.lep2_passMediumID(); }
	const bool &lep2_passTightID() { return babyAnalyzer.lep2_passTightID(); }
	const bool &lep2_passVeto() { return babyAnalyzer.lep2_passVeto(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return babyAnalyzer.lep2_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4() { return babyAnalyzer.lep2_mcp4(); }
	const int &lep2_mc_motherid() { return babyAnalyzer.lep2_mc_motherid(); }
	const vector<float> &ph_sigmaIEtaEta_fill5x5() { return babyAnalyzer.ph_sigmaIEtaEta_fill5x5(); }
	const vector<float> &ph_hOverE() { return babyAnalyzer.ph_hOverE(); }
	const vector<float> &ph_r9() { return babyAnalyzer.ph_r9(); }
	const vector<float> &ph_chiso() { return babyAnalyzer.ph_chiso(); }
	const vector<float> &ph_nhiso() { return babyAnalyzer.ph_nhiso(); }
	const vector<float> &ph_phiso() { return babyAnalyzer.ph_phiso(); }
	const vector<bool> &ph_idCutBased() { return babyAnalyzer.ph_idCutBased(); }
	const vector<int> &ph_overlapJetId() { return babyAnalyzer.ph_overlapJetId(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ph_p4() { return babyAnalyzer.ph_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ph_mcp4() { return babyAnalyzer.ph_mcp4(); }
	const vector<float> &ph_pt() { return babyAnalyzer.ph_pt(); }
	const vector<float> &ph_eta() { return babyAnalyzer.ph_eta(); }
	const vector<float> &ph_phi() { return babyAnalyzer.ph_phi(); }
	const vector<float> &ph_mass() { return babyAnalyzer.ph_mass(); }
	const vector<int> &ph_mcMatchId() { return babyAnalyzer.ph_mcMatchId(); }
	const vector<float> &ph_genIso04() { return babyAnalyzer.ph_genIso04(); }
	const vector<float> &ph_drMinParton() { return babyAnalyzer.ph_drMinParton(); }
	const int &ngoodjets() { return babyAnalyzer.ngoodjets(); }
	const int &ngoodbtags() { return babyAnalyzer.ngoodbtags(); }
	const float &ak4_HT() { return babyAnalyzer.ak4_HT(); }
	const float &ak4_htratiom() { return babyAnalyzer.ak4_htratiom(); }
	const vector<float> &dphi_ak4pfjet_met() { return babyAnalyzer.dphi_ak4pfjet_met(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4pfjets_p4() { return babyAnalyzer.ak4pfjets_p4(); }
	const vector<bool> &ak4pfjets_passMEDbtag() { return babyAnalyzer.ak4pfjets_passMEDbtag(); }
	const vector<float> &ak4pfjets_CSV() { return babyAnalyzer.ak4pfjets_CSV(); }
	const vector<float> &ak4pfjets_mva() { return babyAnalyzer.ak4pfjets_mva(); }
	const vector<int> &ak4pfjets_parton_flavor() { return babyAnalyzer.ak4pfjets_parton_flavor(); }
	const vector<int> &ak4pfjets_hadron_flavor() { return babyAnalyzer.ak4pfjets_hadron_flavor(); }
	const vector<bool> &ak4pfjets_loose_puid() { return babyAnalyzer.ak4pfjets_loose_puid(); }
	const vector<bool> &ak4pfjets_loose_pfid() { return babyAnalyzer.ak4pfjets_loose_pfid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadMEDbjet_p4() { return babyAnalyzer.ak4pfjets_leadMEDbjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ak4pfjets_leadbtag_p4() { return babyAnalyzer.ak4pfjets_leadbtag_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak4genjets_p4() { return babyAnalyzer.ak4genjets_p4(); }
	const vector<bool> &genleps_isfromt() { return babyAnalyzer.genleps_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_p4() { return babyAnalyzer.genleps_p4(); }
	const vector<int> &genleps_id() { return babyAnalyzer.genleps_id(); }
	const vector<int> &genleps__genpsidx() { return babyAnalyzer.genleps__genpsidx(); }
	const vector<int> &genleps_status() { return babyAnalyzer.genleps_status(); }
	const vector<bool> &genleps_fromHardProcessDecayed() { return babyAnalyzer.genleps_fromHardProcessDecayed(); }
	const vector<bool> &genleps_fromHardProcessFinalState() { return babyAnalyzer.genleps_fromHardProcessFinalState(); }
	const vector<bool> &genleps_isHardProcess() { return babyAnalyzer.genleps_isHardProcess(); }
	const vector<bool> &genleps_isLastCopy() { return babyAnalyzer.genleps_isLastCopy(); }
	const vector<int> &genleps_gentaudecay() { return babyAnalyzer.genleps_gentaudecay(); }
	const int &gen_nfromtleps_() { return babyAnalyzer.gen_nfromtleps_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_motherp4() { return babyAnalyzer.genleps_motherp4(); }
	const vector<int> &genleps_motherid() { return babyAnalyzer.genleps_motherid(); }
	const vector<int> &genleps_motheridx() { return babyAnalyzer.genleps_motheridx(); }
	const vector<int> &genleps_motherstatus() { return babyAnalyzer.genleps_motherstatus(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genleps_gmotherp4() { return babyAnalyzer.genleps_gmotherp4(); }
	const vector<int> &genleps_gmotherid() { return babyAnalyzer.genleps_gmotherid(); }
	const vector<int> &genleps_gmotheridx() { return babyAnalyzer.genleps_gmotheridx(); }
	const vector<int> &genleps_gmotherstatus() { return babyAnalyzer.genleps_gmotherstatus(); }
	const vector<bool> &gennus_isfromt() { return babyAnalyzer.gennus_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_p4() { return babyAnalyzer.gennus_p4(); }
	const vector<int> &gennus_id() { return babyAnalyzer.gennus_id(); }
	const vector<int> &gennus__genpsidx() { return babyAnalyzer.gennus__genpsidx(); }
	const vector<int> &gennus_status() { return babyAnalyzer.gennus_status(); }
	const vector<bool> &gennus_fromHardProcessDecayed() { return babyAnalyzer.gennus_fromHardProcessDecayed(); }
	const vector<bool> &gennus_fromHardProcessFinalState() { return babyAnalyzer.gennus_fromHardProcessFinalState(); }
	const vector<bool> &gennus_isHardProcess() { return babyAnalyzer.gennus_isHardProcess(); }
	const vector<bool> &gennus_isLastCopy() { return babyAnalyzer.gennus_isLastCopy(); }
	const vector<int> &gennus_gentaudecay() { return babyAnalyzer.gennus_gentaudecay(); }
	const int &gen_nfromtnus_() { return babyAnalyzer.gen_nfromtnus_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_motherp4() { return babyAnalyzer.gennus_motherp4(); }
	const vector<int> &gennus_motherid() { return babyAnalyzer.gennus_motherid(); }
	const vector<int> &gennus_motheridx() { return babyAnalyzer.gennus_motheridx(); }
	const vector<int> &gennus_motherstatus() { return babyAnalyzer.gennus_motherstatus(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gennus_gmotherp4() { return babyAnalyzer.gennus_gmotherp4(); }
	const vector<int> &gennus_gmotherid() { return babyAnalyzer.gennus_gmotherid(); }
	const vector<int> &gennus_gmotheridx() { return babyAnalyzer.gennus_gmotheridx(); }
	const vector<int> &gennus_gmotherstatus() { return babyAnalyzer.gennus_gmotherstatus(); }
	const vector<bool> &genqs_isfromt() { return babyAnalyzer.genqs_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_p4() { return babyAnalyzer.genqs_p4(); }
	const vector<int> &genqs_id() { return babyAnalyzer.genqs_id(); }
	const vector<int> &genqs__genpsidx() { return babyAnalyzer.genqs__genpsidx(); }
	const vector<int> &genqs_status() { return babyAnalyzer.genqs_status(); }
	const vector<bool> &genqs_fromHardProcessDecayed() { return babyAnalyzer.genqs_fromHardProcessDecayed(); }
	const vector<bool> &genqs_fromHardProcessFinalState() { return babyAnalyzer.genqs_fromHardProcessFinalState(); }
	const vector<bool> &genqs_isHardProcess() { return babyAnalyzer.genqs_isHardProcess(); }
	const vector<bool> &genqs_isLastCopy() { return babyAnalyzer.genqs_isLastCopy(); }
	const vector<int> &genqs_gentaudecay() { return babyAnalyzer.genqs_gentaudecay(); }
	const int &gen_nfromtqs_() { return babyAnalyzer.gen_nfromtqs_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_motherp4() { return babyAnalyzer.genqs_motherp4(); }
	const vector<int> &genqs_motherid() { return babyAnalyzer.genqs_motherid(); }
	const vector<int> &genqs_motheridx() { return babyAnalyzer.genqs_motheridx(); }
	const vector<int> &genqs_motherstatus() { return babyAnalyzer.genqs_motherstatus(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genqs_gmotherp4() { return babyAnalyzer.genqs_gmotherp4(); }
	const vector<int> &genqs_gmotherid() { return babyAnalyzer.genqs_gmotherid(); }
	const vector<int> &genqs_gmotheridx() { return babyAnalyzer.genqs_gmotheridx(); }
	const vector<int> &genqs_gmotherstatus() { return babyAnalyzer.genqs_gmotherstatus(); }
	const vector<bool> &genbosons_isfromt() { return babyAnalyzer.genbosons_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_p4() { return babyAnalyzer.genbosons_p4(); }
	const vector<int> &genbosons_id() { return babyAnalyzer.genbosons_id(); }
	const vector<int> &genbosons__genpsidx() { return babyAnalyzer.genbosons__genpsidx(); }
	const vector<int> &genbosons_status() { return babyAnalyzer.genbosons_status(); }
	const vector<bool> &genbosons_fromHardProcessDecayed() { return babyAnalyzer.genbosons_fromHardProcessDecayed(); }
	const vector<bool> &genbosons_fromHardProcessFinalState() { return babyAnalyzer.genbosons_fromHardProcessFinalState(); }
	const vector<bool> &genbosons_isHardProcess() { return babyAnalyzer.genbosons_isHardProcess(); }
	const vector<bool> &genbosons_isLastCopy() { return babyAnalyzer.genbosons_isLastCopy(); }
	const vector<int> &genbosons_gentaudecay() { return babyAnalyzer.genbosons_gentaudecay(); }
	const int &gen_nfromtbosons_() { return babyAnalyzer.gen_nfromtbosons_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_motherp4() { return babyAnalyzer.genbosons_motherp4(); }
	const vector<int> &genbosons_motherid() { return babyAnalyzer.genbosons_motherid(); }
	const vector<int> &genbosons_motheridx() { return babyAnalyzer.genbosons_motheridx(); }
	const vector<int> &genbosons_motherstatus() { return babyAnalyzer.genbosons_motherstatus(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genbosons_gmotherp4() { return babyAnalyzer.genbosons_gmotherp4(); }
	const vector<int> &genbosons_gmotherid() { return babyAnalyzer.genbosons_gmotherid(); }
	const vector<int> &genbosons_gmotheridx() { return babyAnalyzer.genbosons_gmotheridx(); }
	const vector<int> &genbosons_gmotherstatus() { return babyAnalyzer.genbosons_gmotherstatus(); }
	const vector<bool> &gensusy_isfromt() { return babyAnalyzer.gensusy_isfromt(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_p4() { return babyAnalyzer.gensusy_p4(); }
	const vector<int> &gensusy_id() { return babyAnalyzer.gensusy_id(); }
	const vector<int> &gensusy__genpsidx() { return babyAnalyzer.gensusy__genpsidx(); }
	const vector<int> &gensusy_status() { return babyAnalyzer.gensusy_status(); }
	const vector<bool> &gensusy_fromHardProcessDecayed() { return babyAnalyzer.gensusy_fromHardProcessDecayed(); }
	const vector<bool> &gensusy_fromHardProcessFinalState() { return babyAnalyzer.gensusy_fromHardProcessFinalState(); }
	const vector<bool> &gensusy_isHardProcess() { return babyAnalyzer.gensusy_isHardProcess(); }
	const vector<bool> &gensusy_isLastCopy() { return babyAnalyzer.gensusy_isLastCopy(); }
	const vector<int> &gensusy_gentaudecay() { return babyAnalyzer.gensusy_gentaudecay(); }
	const int &gen_nfromtsusy_() { return babyAnalyzer.gen_nfromtsusy_(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_motherp4() { return babyAnalyzer.gensusy_motherp4(); }
	const vector<int> &gensusy_motherid() { return babyAnalyzer.gensusy_motherid(); }
	const vector<int> &gensusy_motheridx() { return babyAnalyzer.gensusy_motheridx(); }
	const vector<int> &gensusy_motherstatus() { return babyAnalyzer.gensusy_motherstatus(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gensusy_gmotherp4() { return babyAnalyzer.gensusy_gmotherp4(); }
	const vector<int> &gensusy_gmotherid() { return babyAnalyzer.gensusy_gmotherid(); }
	const vector<int> &gensusy_gmotheridx() { return babyAnalyzer.gensusy_gmotheridx(); }
	const vector<int> &gensusy_gmotherstatus() { return babyAnalyzer.gensusy_gmotherstatus(); }
}
