#include "TFile.h"
#include "TH1.h"

void getPileupWeights(){

  TH1D *temp = NULL;

  TFile *f_out = new TFile("Output/Histos/pileup_wgts.root", "recreate");
  

  // Open MC file
  TFile *f_mc = new TFile("Output/Histos/ttbar_diLept_madgraph_pythia8_ext1_25ns.root", "read");
  temp = (TH1D*)f_mc->Get("h_nTrueVtx__lepFlav_emu__genClassy_incl__systematic_nominal");
  TH1D *h_mc = (TH1D*)temp->Clone("h_pileup_MC");
  h_mc->Scale(1.0/h_mc->Integral(0,-1));
  h_mc->SetDirectory(f_out);


  // Open Data files
  TFile *f_data_nom = new TFile("../StopCORE/inputs/pileup/pileup_nominal_minBiasXSec_69200.root", "read");
  temp = (TH1D*)f_data_nom->Get("pileup");
  TH1D *h_data_nom = (TH1D*)temp->Clone("h_pileup_Data");
  h_data_nom->Scale(1.0/h_data_nom->Integral(0,-1));
  h_data_nom->SetDirectory(f_out);

  TFile *f_data_up = new TFile("../StopCORE/inputs/pileup/pileup_up_minBiasXSec_72660.root", "read");
  temp = (TH1D*)f_data_up->Get("pileup");
  TH1D *h_data_up = (TH1D*)temp->Clone("h_pileup_Data_up");
  h_data_up->Scale(1.0/h_data_up->Integral(0,-1));
  h_data_up->SetDirectory(f_out);

  TFile *f_data_down = new TFile("../StopCORE/inputs/pileup/pileup_down_minBiasXSec_65740.root", "read");
  temp = (TH1D*)f_data_down->Get("pileup");
  TH1D *h_data_down = (TH1D*)temp->Clone("h_pileup_Data_down");
  h_data_down->Scale(1.0/h_data_down->Integral(0,-1));
  h_data_down->SetDirectory(f_out);


  // Create Weights
  TH1D *h_nVtx_wgt = (TH1D*)h_data_nom->Clone("h_pileup_wgt");
  h_nVtx_wgt->SetDirectory(f_out);
  h_nVtx_wgt->Divide(h_mc);

  TH1D *h_nVtx_wgt_up = (TH1D*)h_data_up->Clone("h_pileup_wgt_up");
  h_nVtx_wgt_up->SetDirectory(f_out);
  h_nVtx_wgt_up->Divide(h_mc);

  TH1D *h_nVtx_wgt_down = (TH1D*)h_data_down->Clone("h_pileup_wgt_down");
  h_nVtx_wgt_down->SetDirectory(f_out);
  h_nVtx_wgt_down->Divide(h_mc);

  f_out->Write();
  f_out->Close();

  return;
}
