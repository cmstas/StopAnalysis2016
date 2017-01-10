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
  bool pass_SR(int jesType=0);
  std::vector<bool> get_selectionResults_SR(int jesType=0);
  TH1D* get_cutflowHistoTemplate_SR();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_SR();

  bool pass_CR0b(int jesType=0);
  std::vector<bool> get_selectionResults_CR0b(int jesType=0);
  TH1D* get_cutflowHistoTemplate_CR0b();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR0b();

  bool pass_CR0b_tightBTagHighMlb(int jesType=0);
  std::vector<bool> get_selectionResults_CR0b_tightBTagHighMlb(int jesType=0);
  TH1D* get_cutflowHistoTemplate_CR0b_tightBTagHighMlb();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR0b_tightBTagHighMlb();

  bool pass_CR2l(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
  std::vector<bool> get_selectionResults_CR2l(int jesType=0, bool inclTau=false, bool add2ndLepToMet=true);
  TH1D* get_cutflowHistoTemplate_CR2l();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR2l();
  
  bool pass_CR2l_bulkTTbar(int jesType=0, int lepFlavour=24, bool add2ndLepToMet=false );
  std::vector<bool> get_selectionResults_CR2l_bulkTTbar(int jesType=0, int lepFlavour=24, bool add2ndLepToMet=false );
  TH1D* get_cutflowHistoTemplate_CR2l_bulkTTbar();
  vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CR2l_bulkTTbar();

  //bool pass_CRGammaJets(int jesType=0);
  //std::vector<bool> get_selectionResults_CRGammaJets(int jesType=0);
  //TH1D* get_cutflowHistoTemplate_CRGammaJets();
  //vector<TH1D*> get_cutflowHistoTemplate_nMinus1_CRGammaJets();
  
}; // end namespace def


//////////////////////////////////////////////////////////////////////

#endif
