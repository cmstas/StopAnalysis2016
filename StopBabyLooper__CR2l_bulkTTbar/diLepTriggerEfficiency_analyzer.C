#include "stopBabyLooper__CR2l_bulkTTbar.h"

int diLepTriggerEfficiency_analyzer(){


  // Trigger Efficiency Plots for Data

  // Get Data File
  //TFile *f_in = new TFile( "Output/Histos/data_diLepton.root", "read" );
  TFile *f_in = new TFile( "Output/Histos/data_met.root", "read" );

  // Open Output File, and make sure all subsequent histos will be written here
  TFile *f_out = new TFile( "Output/Histos/diLeptonTriggerEfficiencies.root", "update" );
  f_out->cd();

  // Utility Vars
  TCanvas *can = NULL;

  TH1D *h1_num = NULL;
  TH1D *h1_den = NULL;
  TH1D *h1_eff = NULL;

  TH2D *h2_num = NULL;
  TH2D *h2_den = NULL;
  TH2D *h2_eff = NULL;

  const int nBins = 7;
  double xBins[nBins+1]{ 0.0, 30.0, 40.0, 50.0, 75.0, 100.0, 125.0, 200.0 };

  // DiEl Trigger Efficiency vs lep1 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h1_num = (TH1D*)f_in->Get("h_diEl_trigger_eff_vs_lep1Pt_num");
  h1_num = (TH1D*)h1_num->Rebin( nBins, "h1_num_rebin", xBins );
  h1_den = (TH1D*)f_in->Get("h_diEl_trigger_eff_vs_lep1Pt_den");
  h1_den = (TH1D*)h1_den->Rebin( nBins, "h1_den_rebin", xBins );
  h1_eff = (TH1D*)h1_num->Clone("diEl_triggerEff_vs_lep1Pt");
  h1_eff->Divide(h1_num,h1_den,1,1,"b");
  h1_eff->SetTitle("DiElectron Trigger Efficiency vs leading lepton pT");
  h1_eff->Fit("pol0");
  gStyle->SetStatX(0.50);
  gStyle->SetStatY(0.45);
  gStyle->SetOptFit(0111);
  h1_eff->SetMinimum(0.0);
  h1_eff->Draw("e1");
  can->SaveAs("Output/Plots/diEl_trigger_eff_vs_lep1Pt.pdf");
  delete can;
  delete h1_num;
  delete h1_den;


  // DiEl Trigger Efficiency vs lep2 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h1_num = (TH1D*)f_in->Get("h_diEl_trigger_eff_vs_lep2Pt_num");
  h1_num = (TH1D*)h1_num->Rebin( nBins, "h1_num_rebin", xBins );
  h1_den = (TH1D*)f_in->Get("h_diEl_trigger_eff_vs_lep2Pt_den");
  h1_den = (TH1D*)h1_den->Rebin( nBins, "h1_den_rebin", xBins );
  h1_eff = (TH1D*)h1_num->Clone("diEl_triggerEff_vs_lep2Pt");
  h1_eff->Divide(h1_num,h1_den,1,1,"b");
  h1_eff->SetTitle("DiElectron Trigger Efficiency vs trailing lepton pT");
  h1_eff->Fit("pol0");
  gStyle->SetStatX(0.50);
  gStyle->SetStatY(0.45);
  gStyle->SetOptFit(0111);
  h1_eff->SetMinimum(0.0);
  h1_eff->Draw("e1");
  can->SaveAs("Output/Plots/diEl_trigger_eff_vs_lep2Pt.pdf");
  delete can;
  delete h1_num;
  delete h1_den;


  // DiEl Trigger Efficiency, lep1 pT vs lep2 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h2_num = (TH2D*)f_in->Get("h_diEl_trigger_eff_num");
  h2_num->Rebin2D(4,4);
  h2_den = (TH2D*)f_in->Get("h_diEl_trigger_eff_den");
  h2_den->Rebin2D(4,4);
  h2_eff = (TH2D*)h2_num->Clone("diEl_triggerEff_lep1Pt_vs_lep2Pt");
  h2_eff->Divide(h2_num,h2_den,1,1,"b");
  h2_eff->SetTitle("DiElectron Trigger Efficiency, leading lepton pT vs trailing lepton pT");
  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.45);
  h2_eff->Draw("colz text");
  can->SaveAs("Output/Plots/diEl_trigger_eff_lep1Pt_vs_lep2Pt.pdf");
  delete can;


  // MuE Trigger Efficiency vs lep1 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h1_num = (TH1D*)f_in->Get("h_emu_trigger_eff_vs_lep1Pt_num");
  h1_num = (TH1D*)h1_num->Rebin( nBins, "h1_num_rebin", xBins );
  h1_den = (TH1D*)f_in->Get("h_emu_trigger_eff_vs_lep1Pt_den");
  h1_den = (TH1D*)h1_den->Rebin( nBins, "h1_den_rebin", xBins );
  h1_eff = (TH1D*)h1_num->Clone("emu_triggerEff_vs_lep1Pt");
  h1_eff->Divide(h1_num,h1_den,1,1,"b");
  h1_eff->SetTitle("MuE Trigger Efficiency vs leading lepton pT");
  h1_eff->Fit("pol0");
  gStyle->SetStatX(0.50);
  gStyle->SetStatY(0.45);
  gStyle->SetOptFit(0111);
  h1_eff->SetMinimum(0.0);
  h1_eff->Draw("e1");
  can->SaveAs("Output/Plots/emu_trigger_eff_vs_lep1Pt.pdf");
  delete can;
  delete h1_num;
  delete h1_den;

  // MuE Trigger Efficiency vs lep2 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h1_num = (TH1D*)f_in->Get("h_emu_trigger_eff_vs_lep2Pt_num");
  h1_num = (TH1D*)h1_num->Rebin( nBins, "h1_num_rebin", xBins );
  h1_den = (TH1D*)f_in->Get("h_emu_trigger_eff_vs_lep2Pt_den");
  h1_den = (TH1D*)h1_den->Rebin( nBins, "h1_den_rebin", xBins );
  h1_eff = (TH1D*)h1_num->Clone("emu_triggerEff_vs_lep2Pt");
  h1_eff->Divide(h1_num,h1_den,1,1,"b");
  h1_eff->SetTitle("MuE Trigger Efficiency vs trailing lepton pT");
  h1_eff->Fit("pol0");
  gStyle->SetStatX(0.50);
  gStyle->SetStatY(0.45);
  gStyle->SetOptFit(0111);
  h1_eff->SetMinimum(0.0);
  h1_eff->Draw("e1");
  can->SaveAs("Output/Plots/emu_trigger_eff_vs_lep2Pt.pdf");
  delete can;
  delete h1_num;
  delete h1_den;

  // MuE Trigger Efficiency, lep1 pT vs lep2 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h2_num = (TH2D*)f_in->Get("h_emu_trigger_eff_num");
  h2_num->Rebin2D(4,4);
  h2_den = (TH2D*)f_in->Get("h_emu_trigger_eff_den");
  h2_den->Rebin2D(4,4);
  h2_eff = (TH2D*)h2_num->Clone("emu_triggerEff_lep1Pt_vs_lep2Pt");
  h2_eff->Divide(h2_num,h2_den,1,1,"b");
  h2_eff->SetTitle("MuE Trigger Efficiency, leading lepton pT vs trailing lepton pT");
  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.45);
  h2_eff->Draw("colz text");
  can->SaveAs("Output/Plots/emu_trigger_eff_lep1Pt_vs_lep2Pt.pdf");
  delete can;


  // DiMu Trigger Efficiency vs lep1 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h1_num = (TH1D*)f_in->Get("h_diMu_trigger_eff_vs_lep1Pt_num");
  h1_num = (TH1D*)h1_num->Rebin( nBins, "h1_num_rebin", xBins );
  h1_den = (TH1D*)f_in->Get("h_diMu_trigger_eff_vs_lep1Pt_den");
  h1_den = (TH1D*)h1_den->Rebin( nBins, "h1_den_rebin", xBins );
  h1_eff = (TH1D*)h1_num->Clone("diMu_triggerEff_vs_lep1Pt");
  h1_eff->Divide(h1_num,h1_den,1,1,"b");
  h1_eff->SetTitle("DiMuon Trigger Efficiency vs leading lepton pT");
  h1_eff->Fit("pol0");
  gStyle->SetStatX(0.50);
  gStyle->SetStatY(0.45);
  gStyle->SetOptFit(0111);
  h1_eff->SetMinimum(0.0);
  h1_eff->Draw("e1");
  can->SaveAs("Output/Plots/diMu_trigger_eff_vs_lep1Pt.pdf");
  delete can;
  delete h1_num;
  delete h1_den;


  // DiMu Trigger Efficiency vs lep2 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h1_num = (TH1D*)f_in->Get("h_diMu_trigger_eff_vs_lep2Pt_num");
  h1_num = (TH1D*)h1_num->Rebin( nBins, "h1_num_rebin", xBins );
  h1_den = (TH1D*)f_in->Get("h_diMu_trigger_eff_vs_lep2Pt_den");
  h1_den = (TH1D*)h1_den->Rebin( nBins, "h1_den_rebin", xBins );
  h1_eff = (TH1D*)h1_num->Clone("diMu_triggerEff_vs_lep2Pt");
  h1_eff->Divide(h1_num,h1_den,1,1,"b");
  h1_eff->SetTitle("DiMuon Trigger Efficiency vs trailing lepton pT");
  h1_eff->Fit("pol0");
  gStyle->SetStatX(0.50);
  gStyle->SetStatY(0.45);
  gStyle->SetOptFit(0111);
  h1_eff->SetMinimum(0.0);
  h1_eff->Draw("e1");
  can->SaveAs("Output/Plots/diMu_trigger_eff_vs_lep2Pt.pdf");
  delete can;
  delete h1_num;
  delete h1_den;


  // DiMu Trigger Efficiency, lep1 pT vs lep2 pT
  can = new TCanvas("can","can",10,10,1000,800);
  h2_num = (TH2D*)f_in->Get("h_diMu_trigger_eff_num");
  h2_num->Rebin2D(4,4);
  h2_den = (TH2D*)f_in->Get("h_diMu_trigger_eff_den");
  h2_den->Rebin2D(4,4);
  h2_eff = (TH2D*)h2_num->Clone("diMu_triggerEff_lep1Pt_vs_lep2Pt");
  h2_eff->Divide(h2_num,h2_den,1,1,"b");
  h2_eff->SetTitle("DiMuon Trigger Efficiency, leading lepton pT vs trailing lepton pT");
  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.45);
  h2_eff->Draw("colz text");
  can->SaveAs("Output/Plots/diMu_trigger_eff_lep1Pt_vs_lep2Pt.pdf");
  delete can;


  //
  // Clean up
  //
  f_out->Write( "", TObject::kOverwrite );
  f_out->Close();
  f_in->Close();
 
  return 0;
}
