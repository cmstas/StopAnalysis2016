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
  typedef std::pair< std::string, bool() > cut;
  typedef std::vector< std::pair< std::string, bool() > > v_cut;
  

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
  bool pass_geX_diLepMass(double cut_diLepMass=20.0);
  bool pass_ge20_diLepMass();

  // Jet Selection
  bool pass_geX_jets(int cut_nJets=2, int jesType=0);
  bool pass_ge2_jets();
  
  // bTagging Selection, SR
  bool pass_geX_bJets(int cut_nBJets=1, int jesType=0);
  bool pass_ge1_bJets();

  // bTagging Selection, CR0b
  bool pass_eeX_bJets(int cut_nBJets=0, int jesType=0); 
  bool pass_ee0_bJets();
  bool pass_eeX_bJets_tightBTagHighMlb(int cut_nBTags=0, int jesType=0);
  bool pass_ee0_bJets_tightBTagHighMlb();

  // MET Selection
  bool pass_geX_met(double cut_met=150.0, int jesType=0, bool add2ndLepToMet=false);
  bool pass_ge50_met();
  bool pass_ge150_met();
  
  // MT Selection
  bool pass_geX_mt(double cut_mt=150.0, int jesType=0, bool add2ndLepToMet=false);
  bool pass_ge150_mt();

  // min DeltaPhi (MET, (j1, j2))
  bool pass_geX_minDPhi(double cut_minDPhi=0.8, int jesType=0, bool add2ndLepToMet=false);
  bool pass_ge0p5_minDPhi();
  bool pass_ge0p8_minDPhi();


  // Utility Functions to help with selection
  TH1D* get_cutflowHistoTemplate( v_cut );
  //vector<TH1D*> get_cutflowHistoTemplate_nMinus1_SR();
  
  // Full Selections for search regions
  
  bool pass_SR_loose(int jesType=0);
  bool pass_SR_loose();
  std::vector<bool> get_selectionResults_SR_loose(int jesType=0);
  TH1D* get_cutflowHistoTemplate_SR_loose();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_SR_loose();
  
  bool pass_SR(int jesType=0);
  //v_cut get_selection_SR(int jesType=0);
  //bool pass_SR();
  v_cut get_selection_SR();
  
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
