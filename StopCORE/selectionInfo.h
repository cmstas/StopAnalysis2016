#ifndef selectionInfo_H
#define selectionInfo_H

// stopCORE
#include "stop_1l_babyAnalyzer.h"

// ROOT
#include "TFile.h"
#include "TH1D.h"
#include "TH3D.h"
#include "Math/VectorUtil.h"

// C
#include <string>
#include <vector>

//
// NAMESPACE
//
namespace selectionInfo{

  //
  // Namespace functions
  //
  typedef std::pair< std::string, bool(*)() > cut;
  typedef std::vector< std::pair< std::string, bool(*)() > > v_cut;
  

  // Notes:
  //   jesType 0=nominal, 1=up, -1=down
  void SetJesType( int type );
  void SetAdd2ndLep( bool addlep2 );
  void SetIncludeTaus( bool usetaus );

  // Met filters
  bool pass_metFilter();
	bool pass_metFilter_photons();

  // Triggers
  bool pass_trigger_SR();
  bool pass_trigger_CR2l();
  bool pass_trigger_CR2l_bulkTTbar();
	bool pass_trigger_phoPt();

  // Good Vertex
  bool pass_goodVtx();

  // Single Lepton Selection
  bool pass_ee1_sel_lep();
  bool pass_ee0_veto_lep();
  bool pass_trackVeto();
  bool pass_tauVeto();

	// Single Lepton Selection, for studies
	bool pass_ge1_veto_lep();
	bool pass_ge1_sel_lep();

  // DiLepton Selection
  bool pass_diLep();

  // DiLepton Selection, CR2l_bulkTTbar
  bool pass_diLep_bulkTTbar();
  bool pass_oppSign_leps();
  bool pass_ZWindow_diLepMass();
  bool pass_geX_diLepMass(double cut_diLepMass=20.0);
  bool pass_ge20_diLepMass();
	bool pass_ee_diLepFlavor();
	bool pass_emu_diLepFlavor();
	bool pass_mumu_diLepFlavor();

  // Jet Selection
  bool pass_geX_jets(int cut_nJets=2, int jesType=0);
  bool pass_ge2_jets();
	bool pass_ge5_jets();

  // bTagging Selection, SR
  bool pass_geX_bJets(int cut_nBJets=1, int jesType=0);
  bool pass_ge1_bJets();

	bool pass_ge1_bJets_inclSoft();

  // bTagging Selection, CR0b
  bool pass_eeX_bJets(int cut_nBJets=0, int jesType=0); 
  bool pass_ee0_bJets();
  bool pass_eeX_bJets_tightBTagHighMlb(int cut_nBTags=0, int jesType=0);
  bool pass_ee0_bJets_tightBTagHighMlb();

	bool pass_ee0_bJets_inclSoft();

  // MET Selection
  bool pass_geX_met(double cut_met=150.0, int jesType=0, bool add2ndLepToMet=false);
  bool pass_ge50_met();
  bool pass_ge150_met();
	bool pass_ge250_met();
  
  // MT Selection
  bool pass_geX_mt(double cut_mt=150.0, int jesType=0, bool add2ndLepToMet=false);
	bool pass_ge120_mt();
  bool pass_ge150_mt();

  // min DeltaPhi (MET, (j1, j2))
  bool pass_geX_minDPhi(double cut_minDPhi=0.8, int jesType=0, bool add2ndLepToMet=false);
  bool pass_ge0p5_minDPhi();
  bool pass_ge0p8_minDPhi();

	// Corridor selections

	// Leading jet pt
	// bool pass_ge250_j1pt();
	// bool pass_geX_j1pt( double cut_pt=250., int jesType=0 );

	// Leading jet b-tag
	bool pass_j1NotBtag();
	bool pass_j1MedBtag( int jesType=0 );

	// Leading lepton pT
	bool pass_lt150_lep1pt();
	bool pass_geX_lep1pt( double cut_pt=20. );

	// DPhi(lep, MET)
	bool pass_lt2_dPhiLepMet();
	bool pass_geX_dPhiLepMet( double cut_phi=0., int jesType=0, bool add2ndLepToMet=false );

	// Photon selections
	bool pass_ee0_lep();
	bool pass_ge2_ph_jets();
	bool pass_ge5_ph_jets();
	bool pass_ee0_ph_bJets();
	bool pass_ge150_ph_met();
	bool pass_ge0p8_ph_minDPhi();
	bool pass_ge0p5_ph_minDPhi();
	bool pass_selected_photon();


  // Utility Functions to help with selection
  TH1D* get_cutflowHistoTemplate( v_cut cutList );
	TH1D* get_cutflowHistoTemplate( v_cut cutList, std::string name, std::string title );
	std::vector<TH1D*> get_cutflowHistoTemplate_nMinus1( TH1D* original );
	std::vector<bool> get_selectionResults( v_cut cutList );
  
  // Full Selections for search regions
  
  bool pass_SR_loose(int jesType=0);
	std::vector<cut> get_selection_SR_loose();
  
  bool pass_SR(int jesType=0);
	std::vector<cut> get_selection_SR();

	bool pass_SR_inclSoft(int jesType=0);
	std::vector<cut> get_selection_SR_inclSoft();

	bool pass_SR_corridor(int jesType=0);
	std::vector<cut> get_selection_SR_corridor();

	bool pass_SR_corridor_inclSoft(int jesType=0);
	std::vector<cut> get_selection_SR_corridor_inclSoft();
  
  bool pass_CR0b(int jesType=0);
	std::vector<cut> get_selection_CR0b();

  // bool pass_CR0b_inclSoft(int jesType=0);
	// std::vector<cut> get_selection_CR0b_inclSoft();

  bool pass_CR0b_tightBTagHighMlb(int jesType=0);
	std::vector<cut> get_selection_CR0b_tightBTagHighMlb();

  // bool pass_CR0b_tightBTagHighMlb_inclSoft(int jesType=0);
	// std::vector<cut> get_selection_CR0b_tightBTagHighMlb_inclSoft();

	bool pass_CR0b_corridor(int jesType=0);
	std::vector<cut> get_selection_CR0b_corridor();

	bool pass_CR0b_corridor_inclSoft(int jesType=0);
	std::vector<cut> get_selection_CR0b_corridor_inclSoft();

  bool pass_CR2l(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
  bool pass_CR2l(int jesType=0);
	std::vector<cut> get_selection_CR2l();

  bool pass_CR2l_inclSoft(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
  bool pass_CR2l_inclSoft(int jesType=0);
	std::vector<cut> get_selection_CR2l_inclSoft();

  bool pass_CR2l_corridor(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
	bool pass_CR2l_corridor(int jesType=0);
	std::vector<cut> get_selection_CR2l_corridor();

  bool pass_CR2l_corridor_inclSoft(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
	bool pass_CR2l_corridor_inclSoft(int jesType=0);
	std::vector<cut> get_selection_CR2l_corridor_inclSoft();
  
  bool pass_CR2l_bulkTTbar(int jesType=0, bool add2ndLepToMet=false );
  bool pass_CR2l_bulkTTbar(int jesType=0);
	std::vector<cut> get_selection_CR2l_bulkTTbar();

	std::vector<cut> get_selection_nupt();

	std::vector<cut> get_selection_nupt_corridor();

	std::vector<cut> get_selection_phopt();

	std::vector<cut> get_selection_phopt_corridor();
  
}; // end namespace def


//////////////////////////////////////////////////////////////////////

#endif
