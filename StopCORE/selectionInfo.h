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

  // Notes:
  //   jesType 0=nominal, 1=up, -1=down

	void SetJesType( int type );
	void SetAdd2ndLep( bool addlep2 );
	void SetIncludeTaus( bool usetaus );

  // Met filters
  bool pass_metFilter();

  // Triggers
  bool pass_trigger_SR();
  bool pass_trigger_CR2l();
  bool pass_trigger_CR2l_bulkTTbar();

  // Good Vertex
  bool pass_goodVtx();

  // Single Lepton Selection
  bool pass_ee1_sel_lep();
  bool pass_ee0_veto_lep();
  bool pass_trackVeto();
  bool pass_tauVeto();

  // DiLepton Selection
  bool pass_diLep(bool inclTau=false);
	bool pass_diLep();

  // DiLepton Selection, CR2l_bulkTTbar
  bool pass_diLep_bulkTTbar();
  bool pass_oppSign_leps();
  bool pass_ZWindow_diLepMass();
  bool pass_ge20_diLepMass();

  // Jet Selection
  bool pass_ge2_jets(int jesType=0);
	bool pass_ge2_jets();
  
  // bTagging Selection, SR
  bool pass_ge1_bJets(int jesType=0);
	bool pass_ge1_bJets();

  // bTagging Selection, CR0b
  bool pass_ee0_bJets(int jesType=0); 
  bool pass_ee0_bJets_tightBTagHighMlb(int jesType=0);
	bool pass_ee0_bJets();
	bool pass_ee0_bJets_tightBTagHighMlb();

  // MET Selection
  bool pass_ge50_met(int jesType=0, bool add2ndLepToMet=false);
  bool pass_ge150_met(int jesType=0, bool add2ndLepToMet=false);
	bool pass_ge50_met();
	bool pass_ge150_met();
  
  // MT Selection
  bool pass_ge150_mt(int jesType=0, bool add2ndLepToMet=false);
	bool pass_ge150_mt();

  // min DeltaPhi (MET, (j1, j2))
  bool pass_ge0p5_minDPhi(int jesType=0, bool add2ndLepToMet=false);
	bool pass_ge0p5_minDPhi();



  bool pass_SR_loose(int jesType=0);
	bool pass_SR_loose();
  std::vector<bool> get_selectionResults_SR_loose(int jesType=0);
  TH1D* get_cutflowHistoTemplate_SR_loose();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_SR_loose();

  bool pass_SR(int jesType=0);
	bool pass_SR();
  std::vector<bool> get_selectionResults_SR(int jesType=0);
  TH1D* get_cutflowHistoTemplate_SR();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_SR();
  
  bool pass_CR0b(int jesType=0);
	bool pass_CR0b();
  std::vector<bool> get_selectionResults_CR0b(int jesType=0);
  TH1D* get_cutflowHistoTemplate_CR0b();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR0b();

  bool pass_CR0b_tightBTagHighMlb(int jesType=0);
	bool pass_CR0b_tightBTagHighMlb();
  std::vector<bool> get_selectionResults_CR0b_tightBTagHighMlb(int jesType=0);
  TH1D* get_cutflowHistoTemplate_CR0b_tightBTagHighMlb();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR0b_tightBTagHighMlb();

  bool pass_CR2l(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
	bool pass_CR2l();
  std::vector<bool> get_selectionResults_CR2l(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
  TH1D* get_cutflowHistoTemplate_CR2l();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR2l();
  
  bool pass_CR2l_bulkTTbar(int jesType=0, bool add2ndLepToMet=false );
	bool pass_CR2l_bulkTTbar();
  std::vector<bool> get_selectionResults_CR2l_bulkTTbar(int jesType=0, bool add2ndLepToMet=false );
  TH1D* get_cutflowHistoTemplate_CR2l_bulkTTbar();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR2l_bulkTTbar();

  //bool pass_CRGammaJets(int jesType=0);
  //std::vector<bool> get_selectionResults_CRGammaJets(int jesType=0);
  //TH1D* get_cutflowHistoTemplate_CRGammaJets();
  //vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CRGammaJets();
  
}; // end namespace def


//////////////////////////////////////////////////////////////////////

#endif
