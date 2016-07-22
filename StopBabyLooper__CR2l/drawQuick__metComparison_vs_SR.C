#include "TStyle.h"
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLine.h"

int drawQuick__metComparison_vs_SR(){

  // Global Style
  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(3);

  // Vars
  TH1D *ratio_pfmet = NULL;
  TH1D *ratio_rlmet = NULL;
  
  TCanvas *can = NULL;
  TPad *pad_main = NULL;
  TPad *pad_ratio = NULL;
  TLegend *leg = NULL;
  TLine *line = NULL;

  double max = -99.9;

  // Open Files
  
  //TFile *f_SR = new TFile("../StopBabyLooper__SR/Histos/Nominal/h__ttbar_diLept_madgraph_pythia8_ext1_25ns.root", "read");
  //TFile *f_CR_pfmet = new TFile("OLD/Histos__3p99fb__20160626/Nominal/h__ttbar_diLept_madgraph_pythia8_ext1_25ns.root", "read");
  //TFile *f_CR_rlmet = new TFile("Histos/Nominal/h__ttbar_diLept_madgraph_pythia8_ext1_25ns.root", "read");

  TFile *f_SR = new TFile("../StopBabyLooper__SR/Histos/Nominal/h__allBkg_25ns.root", "read");
  TFile *f_CR_pfmet = new TFile("OLD/Histos__3p99fb__20160626/Nominal/h__allBkg_25ns.root", "read");
  TFile *f_CR_rlmet = new TFile("Histos/Nominal/h__allBkg_25ns.root", "read");
  
  
  // ==2 jets

  // Get Histos
  TH1D *h_SR_ee2j_met   = (TH1D*)f_SR->Get("met__genClassy_ge2lep__recoClassy_incl__cat_ee2jets__sys_nominal");
  TH1D *h_CR_ee2j_pfmet = (TH1D*)f_CR_pfmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ee2jets__sys_nominal");
  TH1D *h_CR_ee2j_rlmet = (TH1D*)f_CR_rlmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ee2jets__sys_nominal");
  
  //h_SR_ee2j_met->Rebin(4);
  //h_CR_ee2j_pfmet->Rebin(4);
  //h_CR_ee2j_rlmet->Rebin(4);

  const int nBins_ee2jets = 3;
  double xBins_ee2jets[nBins_ee2jets+1]{ 250.0, 350.0, 450.0, 800.0 };
  double xBins_SF_ee2jets[nBins_ee2jets]{   1.0,    1.0,   0.2857   };

  h_SR_ee2j_met = (TH1D*)h_SR_ee2j_met->Rebin(nBins_ee2jets, "SR_ee2j_met_rebin", xBins_ee2jets);
  h_CR_ee2j_pfmet = (TH1D*)h_CR_ee2j_pfmet->Rebin(nBins_ee2jets, "CR_ee2j_pfmet_rebin", xBins_ee2jets);
  h_CR_ee2j_rlmet = (TH1D*)h_CR_ee2j_rlmet->Rebin(nBins_ee2jets, "CR_ee2j_rlmet_rebin", xBins_ee2jets);
  for(int iBin=1; iBin<=nBins_ee2jets; iBin++){
    h_SR_ee2j_met->SetBinContent( iBin, h_SR_ee2j_met->GetBinContent(iBin)*xBins_SF_ee2jets[iBin-1] );
    h_SR_ee2j_met->SetBinError( iBin, h_SR_ee2j_met->GetBinError(iBin)*xBins_SF_ee2jets[iBin-1] );
    h_CR_ee2j_pfmet->SetBinContent( iBin, h_CR_ee2j_pfmet->GetBinContent(iBin)*xBins_SF_ee2jets[iBin-1] );
    h_CR_ee2j_pfmet->SetBinError( iBin, h_CR_ee2j_pfmet->GetBinError(iBin)*xBins_SF_ee2jets[iBin-1] );
    h_CR_ee2j_rlmet->SetBinContent( iBin, h_CR_ee2j_rlmet->GetBinContent(iBin)*xBins_SF_ee2jets[iBin-1] );
    h_CR_ee2j_rlmet->SetBinError( iBin, h_CR_ee2j_rlmet->GetBinError(iBin)*xBins_SF_ee2jets[iBin-1] );
  }

  h_SR_ee2j_met->SetLineColor(kRed);
  h_CR_ee2j_pfmet->SetLineColor(kGreen);
  h_CR_ee2j_rlmet->SetLineColor(kBlue);
  
  h_SR_ee2j_met->Scale(1.0/h_SR_ee2j_met->Integral(0,-1));
  h_CR_ee2j_pfmet->Scale(1.0/h_CR_ee2j_pfmet->Integral(0,-1));
  h_CR_ee2j_rlmet->Scale(1.0/h_CR_ee2j_rlmet->Integral(0,-1));
  

  ratio_pfmet = (TH1D*)h_SR_ee2j_met->Clone("ratio_SR_CR_pfmet");
  ratio_pfmet->Divide(h_SR_ee2j_met,h_CR_ee2j_pfmet,1,1);

  ratio_rlmet = (TH1D*)h_SR_ee2j_met->Clone("ratio_SR_CR_rlmet");
  ratio_rlmet->Divide(h_SR_ee2j_met,h_CR_ee2j_rlmet,1,1);

  ratio_pfmet->SetLineColor(kGreen);
  ratio_rlmet->SetLineColor(kBlue);

  
  can = new TCanvas("can","can",10,10,1000,800);
  pad_main  = new TPad("main", "main",   0.0, 0.16, 1.00, 1.00);
  pad_ratio = new TPad("ratio", "ratio", 0.0, 0.00, 1.00, 0.17);

  pad_main->Draw();
  pad_ratio->Draw();

  pad_main->cd();
  pad_main->SetLogy();
  
  max = std::max( h_SR_ee2j_met->GetBinContent(h_SR_ee2j_met->GetMaximumBin()), h_CR_ee2j_pfmet->GetBinContent(h_CR_ee2j_pfmet->GetMaximumBin()) );
  max = std::max( max, h_CR_ee2j_rlmet->GetBinContent(h_CR_ee2j_rlmet->GetMaximumBin()) );
    
  h_SR_ee2j_met->SetMaximum(max*1.5);

  h_SR_ee2j_met->SetTitle("ee2j, SR and CR comparison of met");
  
  h_SR_ee2j_met->Draw("hist");
  h_CR_ee2j_pfmet->Draw("hist same");
  h_CR_ee2j_rlmet->Draw("hist same");
  
  leg = new TLegend(0.65, 0.65, 0.90, 0.90);
  leg->AddEntry(h_SR_ee2j_met,   "SR, standard pfmet", "l");
  leg->AddEntry(h_CR_ee2j_pfmet, "CR, standard pfmet", "l");
  leg->AddEntry(h_CR_ee2j_rlmet, "CR, 2nd lep removed met", "l");
  leg->Draw();


  pad_ratio->cd();
  
  line = new TLine( ratio_pfmet->GetXaxis()->GetBinLowEdge(1), 1.0, ratio_pfmet->GetXaxis()->GetBinUpEdge(ratio_pfmet->GetNbinsX()), 1.0 );
  line->SetLineWidth(3);
  line->SetLineColor(kRed);
  
  ratio_pfmet->SetMaximum(1.5);
  ratio_pfmet->SetMinimum(0.0);
  
  ratio_pfmet->Draw("e1");
  line->Draw("same");
  ratio_pfmet->Draw("e1 same");
  ratio_rlmet->Draw("e1 same");
  
  can->SaveAs("metComparison_SR_vs_CR__ee2j.pdf");
  can->~TCanvas();


  
  // ==3 jets

  // Get Histos
  TH1D *h_SR_ee3j_met   = (TH1D*)f_SR->Get("met__genClassy_ge2lep__recoClassy_incl__cat_ee3jets__sys_nominal");
  TH1D *h_CR_ee3j_pfmet = (TH1D*)f_CR_pfmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ee3jets__sys_nominal");
  TH1D *h_CR_ee3j_rlmet = (TH1D*)f_CR_rlmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ee3jets__sys_nominal");
  
  //h_SR_ee3j_met->Rebin(4);
  //h_CR_ee3j_pfmet->Rebin(4);
  //h_CR_ee3j_rlmet->Rebin(4);
  
  const int nBins_ee3jets = 4;
  double xBins_ee3jets[nBins_ee3jets+1]{ 250.0, 350.0, 450.0, 550.0, 800.0 };
  double xBins_SF_ee3jets[nBins_ee3jets]{   1.0,    1.0,   1.0,  0.4   };

  h_SR_ee3j_met = (TH1D*)h_SR_ee3j_met->Rebin(nBins_ee3jets, "SR_ee3j_met_rebin", xBins_ee3jets);
  h_CR_ee3j_pfmet = (TH1D*)h_CR_ee3j_pfmet->Rebin(nBins_ee3jets, "CR_ee3j_pfmet_rebin", xBins_ee3jets);
  h_CR_ee3j_rlmet = (TH1D*)h_CR_ee3j_rlmet->Rebin(nBins_ee3jets, "CR_ee3j_rlmet_rebin", xBins_ee3jets);
  for(int iBin=1; iBin<=nBins_ee3jets; iBin++){
    h_SR_ee3j_met->SetBinContent( iBin, h_SR_ee3j_met->GetBinContent(iBin)*xBins_SF_ee3jets[iBin-1] );
    h_SR_ee3j_met->SetBinError( iBin, h_SR_ee3j_met->GetBinError(iBin)*xBins_SF_ee3jets[iBin-1] );
    h_CR_ee3j_pfmet->SetBinContent( iBin, h_CR_ee3j_pfmet->GetBinContent(iBin)*xBins_SF_ee3jets[iBin-1] );
    h_CR_ee3j_pfmet->SetBinError( iBin, h_CR_ee3j_pfmet->GetBinError(iBin)*xBins_SF_ee3jets[iBin-1] );
    h_CR_ee3j_rlmet->SetBinContent( iBin, h_CR_ee3j_rlmet->GetBinContent(iBin)*xBins_SF_ee3jets[iBin-1] );
    h_CR_ee3j_rlmet->SetBinError( iBin, h_CR_ee3j_rlmet->GetBinError(iBin)*xBins_SF_ee3jets[iBin-1] );
  }


  h_SR_ee3j_met->SetLineColor(kRed);
  h_CR_ee3j_pfmet->SetLineColor(kGreen);
  h_CR_ee3j_rlmet->SetLineColor(kBlue);
  
  h_SR_ee3j_met->Scale(1.0/h_SR_ee3j_met->Integral(0,-1));
  h_CR_ee3j_pfmet->Scale(1.0/h_CR_ee3j_pfmet->Integral(0,-1));
  h_CR_ee3j_rlmet->Scale(1.0/h_CR_ee3j_rlmet->Integral(0,-1));
  

  ratio_pfmet = (TH1D*)h_SR_ee3j_met->Clone("ratio_SR_CR_pfmet");
  ratio_pfmet->Divide(h_SR_ee3j_met,h_CR_ee3j_pfmet,1,1);

  ratio_rlmet = (TH1D*)h_SR_ee3j_met->Clone("ratio_SR_CR_rlmet");
  ratio_rlmet->Divide(h_SR_ee3j_met,h_CR_ee3j_rlmet,1,1);

  ratio_pfmet->SetLineColor(kGreen);
  ratio_rlmet->SetLineColor(kBlue);

  
  can = new TCanvas("can","can",10,10,1000,800);
  pad_main  = new TPad("main", "main",   0.0, 0.16, 1.00, 1.00);
  pad_ratio = new TPad("ratio", "ratio", 0.0, 0.00, 1.00, 0.17);

  pad_main->Draw();
  pad_ratio->Draw();

  pad_main->cd();
  pad_main->SetLogy();
  
  max = std::max( h_SR_ee3j_met->GetBinContent(h_SR_ee3j_met->GetMaximumBin()), h_CR_ee3j_pfmet->GetBinContent(h_CR_ee3j_pfmet->GetMaximumBin()) );
  max = std::max( max, h_CR_ee3j_rlmet->GetBinContent(h_CR_ee3j_rlmet->GetMaximumBin()) );
    
  h_SR_ee3j_met->SetMaximum(max*1.5);

  h_SR_ee3j_met->SetTitle("ee3j, SR and CR comparison of met");
  
  h_SR_ee3j_met->Draw("hist");
  h_CR_ee3j_pfmet->Draw("hist same");
  h_CR_ee3j_rlmet->Draw("hist same");
  
  leg = new TLegend(0.65, 0.65, 0.90, 0.90);
  leg->AddEntry(h_SR_ee3j_met,   "SR, standard pfmet", "l");
  leg->AddEntry(h_CR_ee3j_pfmet, "CR, standard pfmet", "l");
  leg->AddEntry(h_CR_ee3j_rlmet, "CR, 2nd lep removed met", "l");
  leg->Draw();


  pad_ratio->cd();
  
  line = new TLine( ratio_pfmet->GetXaxis()->GetBinLowEdge(1), 1.0, ratio_pfmet->GetXaxis()->GetBinUpEdge(ratio_pfmet->GetNbinsX()), 1.0 );
  line->SetLineWidth(3);
  line->SetLineColor(kRed);
  
  ratio_pfmet->SetMaximum(1.5);
  ratio_pfmet->SetMinimum(0.0);
  
  ratio_pfmet->Draw("e1");
  line->Draw("same");
  ratio_pfmet->Draw("e1 same");
  ratio_rlmet->Draw("e1 same");
  
  can->SaveAs("metComparison_SR_vs_CR__ee3j.pdf");
  can->~TCanvas();



  // >=4 jets

  // Get Histos
  TH1D *h_SR_ge4j_met   = (TH1D*)f_SR->Get("met__genClassy_ge2lep__recoClassy_incl__cat_ge4jets__sys_nominal");
  TH1D *h_CR_ge4j_pfmet = (TH1D*)f_CR_pfmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets__sys_nominal");
  TH1D *h_CR_ge4j_rlmet = (TH1D*)f_CR_rlmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets__sys_nominal");
  
  //h_SR_ge4j_met->Rebin(4);
  //h_CR_ge4j_pfmet->Rebin(4);
  //h_CR_ge4j_rlmet->Rebin(4);
  
  const int nBins_ge4jets = 4;
  double xBins_ge4jets[nBins_ge4jets+1]{ 250.0, 350.0, 450.0, 550.0, 800.0 };
  double xBins_SF_ge4jets[nBins_ge4jets]{   1.0,    1.0,   1.0,  0.4   };

  h_SR_ge4j_met = (TH1D*)h_SR_ge4j_met->Rebin(nBins_ge4jets, "SR_ge4j_met_rebin", xBins_ge4jets);
  h_CR_ge4j_pfmet = (TH1D*)h_CR_ge4j_pfmet->Rebin(nBins_ge4jets, "CR_ge4j_pfmet_rebin", xBins_ge4jets);
  h_CR_ge4j_rlmet = (TH1D*)h_CR_ge4j_rlmet->Rebin(nBins_ge4jets, "CR_ge4j_rlmet_rebin", xBins_ge4jets);
  for(int iBin=1; iBin<=nBins_ge4jets; iBin++){
    h_SR_ge4j_met->SetBinContent( iBin, h_SR_ge4j_met->GetBinContent(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_SR_ge4j_met->SetBinError( iBin, h_SR_ge4j_met->GetBinError(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_CR_ge4j_pfmet->SetBinContent( iBin, h_CR_ge4j_pfmet->GetBinContent(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_CR_ge4j_pfmet->SetBinError( iBin, h_CR_ge4j_pfmet->GetBinError(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_CR_ge4j_rlmet->SetBinContent( iBin, h_CR_ge4j_rlmet->GetBinContent(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_CR_ge4j_rlmet->SetBinError( iBin, h_CR_ge4j_rlmet->GetBinError(iBin)*xBins_SF_ge4jets[iBin-1] );
  }

  
  h_SR_ge4j_met->SetLineColor(kRed);
  h_CR_ge4j_pfmet->SetLineColor(kGreen);
  h_CR_ge4j_rlmet->SetLineColor(kBlue);
  
  h_SR_ge4j_met->Scale(1.0/h_SR_ge4j_met->Integral(0,-1));
  h_CR_ge4j_pfmet->Scale(1.0/h_CR_ge4j_pfmet->Integral(0,-1));
  h_CR_ge4j_rlmet->Scale(1.0/h_CR_ge4j_rlmet->Integral(0,-1));
  

  ratio_pfmet = (TH1D*)h_SR_ge4j_met->Clone("ratio_SR_CR_pfmet");
  ratio_pfmet->Divide(h_SR_ge4j_met,h_CR_ge4j_pfmet,1,1);

  ratio_rlmet = (TH1D*)h_SR_ge4j_met->Clone("ratio_SR_CR_rlmet");
  ratio_rlmet->Divide(h_SR_ge4j_met,h_CR_ge4j_rlmet,1,1);

  ratio_pfmet->SetLineColor(kGreen);
  ratio_rlmet->SetLineColor(kBlue);

  
  can = new TCanvas("can","can",10,10,1000,800);
  pad_main  = new TPad("main", "main",   0.0, 0.16, 1.00, 1.00);
  pad_ratio = new TPad("ratio", "ratio", 0.0, 0.00, 1.00, 0.17);

  pad_main->Draw();
  pad_ratio->Draw();

  pad_main->cd();
  pad_main->SetLogy();
  
  max = std::max( h_SR_ge4j_met->GetBinContent(h_SR_ge4j_met->GetMaximumBin()), h_CR_ge4j_pfmet->GetBinContent(h_CR_ge4j_pfmet->GetMaximumBin()) );
  max = std::max( max, h_CR_ge4j_rlmet->GetBinContent(h_CR_ge4j_rlmet->GetMaximumBin()) );
    
  h_SR_ge4j_met->SetMaximum(max*1.5);

  h_SR_ge4j_met->SetTitle("ge4j, SR and CR comparison of met");
  
  h_SR_ge4j_met->Draw("hist");
  h_CR_ge4j_pfmet->Draw("hist same");
  h_CR_ge4j_rlmet->Draw("hist same");
  
  leg = new TLegend(0.65, 0.65, 0.90, 0.90);
  leg->AddEntry(h_SR_ge4j_met,   "SR, standard pfmet", "l");
  leg->AddEntry(h_CR_ge4j_pfmet, "CR, standard pfmet", "l");
  leg->AddEntry(h_CR_ge4j_rlmet, "CR, 2nd lep removed met", "l");
  leg->Draw();


  pad_ratio->cd();
  
  line = new TLine( ratio_pfmet->GetXaxis()->GetBinLowEdge(1), 1.0, ratio_pfmet->GetXaxis()->GetBinUpEdge(ratio_pfmet->GetNbinsX()), 1.0 );
  line->SetLineWidth(3);
  line->SetLineColor(kRed);
  
  ratio_pfmet->SetMaximum(1.5);
  ratio_pfmet->SetMinimum(0.0);
  
  ratio_pfmet->Draw("e1");
  line->Draw("same");
  ratio_pfmet->Draw("e1 same");
  ratio_rlmet->Draw("e1 same");
  
  can->SaveAs("metComparison_SR_vs_CR__ge4j.pdf");
  can->~TCanvas();


  // >=4 jets, mt2w<200

  // Get Histos
  TH1D *h_SR_ge4j_lt200mt2w_met   = (TH1D*)f_SR->Get("met__genClassy_ge2lep__recoClassy_incl__cat_ge4jets_lt200mt2w__sys_nominal");
  TH1D *h_CR_ge4j_lt200mt2w_pfmet = (TH1D*)f_CR_pfmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets_lt200mt2w__sys_nominal");
  TH1D *h_CR_ge4j_lt200mt2w_rlmet = (TH1D*)f_CR_rlmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets_lt200mt2w__sys_nominal");
  
  //h_SR_ge4j_lt200mt2w_met->Rebin(4);
  //h_CR_ge4j_lt200mt2w_pfmet->Rebin(4);
  //h_CR_ge4j_lt200mt2w_rlmet->Rebin(4);
  
  const int nBins_ge4jets_lt200mt2w = 3;
  double xBins_ge4jets_lt200mt2w[nBins_ge4jets_lt200mt2w+1]{ 250.0, 350.0, 450.0, 800.0 };
  double xBins_SF_ge4jets_lt200mt2w[nBins_ge4jets_lt200mt2w]{   1.0,    1.0,   0.2857   };

  h_SR_ge4j_lt200mt2w_met = (TH1D*)h_SR_ge4j_lt200mt2w_met->Rebin(nBins_ge4jets_lt200mt2w, "SR_ge4j_lt200mt2w_met_rebin", xBins_ge4jets_lt200mt2w);
  h_CR_ge4j_lt200mt2w_pfmet = (TH1D*)h_CR_ge4j_lt200mt2w_pfmet->Rebin(nBins_ge4jets_lt200mt2w, "CR_ge4j_lt200mt2w_pfmet_rebin", xBins_ge4jets_lt200mt2w);
  h_CR_ge4j_lt200mt2w_rlmet = (TH1D*)h_CR_ge4j_lt200mt2w_rlmet->Rebin(nBins_ge4jets_lt200mt2w, "CR_ge4j_lt200mt2w_rlmet_rebin", xBins_ge4jets_lt200mt2w);
  for(int iBin=1; iBin<=nBins_ge4jets_lt200mt2w; iBin++){
    h_SR_ge4j_lt200mt2w_met->SetBinContent( iBin, h_SR_ge4j_lt200mt2w_met->GetBinContent(iBin)*xBins_SF_ge4jets_lt200mt2w[iBin-1] );
    h_SR_ge4j_lt200mt2w_met->SetBinError( iBin, h_SR_ge4j_lt200mt2w_met->GetBinError(iBin)*xBins_SF_ge4jets_lt200mt2w[iBin-1] );
    h_CR_ge4j_lt200mt2w_pfmet->SetBinContent( iBin, h_CR_ge4j_lt200mt2w_pfmet->GetBinContent(iBin)*xBins_SF_ge4jets_lt200mt2w[iBin-1] );
    h_CR_ge4j_lt200mt2w_pfmet->SetBinError( iBin, h_CR_ge4j_lt200mt2w_pfmet->GetBinError(iBin)*xBins_SF_ge4jets_lt200mt2w[iBin-1] );
    h_CR_ge4j_lt200mt2w_rlmet->SetBinContent( iBin, h_CR_ge4j_lt200mt2w_rlmet->GetBinContent(iBin)*xBins_SF_ge4jets_lt200mt2w[iBin-1] );
    h_CR_ge4j_lt200mt2w_rlmet->SetBinError( iBin, h_CR_ge4j_lt200mt2w_rlmet->GetBinError(iBin)*xBins_SF_ge4jets_lt200mt2w[iBin-1] );
  }


  h_SR_ge4j_lt200mt2w_met->SetLineColor(kRed);
  h_CR_ge4j_lt200mt2w_pfmet->SetLineColor(kGreen);
  h_CR_ge4j_lt200mt2w_rlmet->SetLineColor(kBlue);
  
  h_SR_ge4j_lt200mt2w_met->Scale(1.0/h_SR_ge4j_lt200mt2w_met->Integral(0,-1));
  h_CR_ge4j_lt200mt2w_pfmet->Scale(1.0/h_CR_ge4j_lt200mt2w_pfmet->Integral(0,-1));
  h_CR_ge4j_lt200mt2w_rlmet->Scale(1.0/h_CR_ge4j_lt200mt2w_rlmet->Integral(0,-1));
  

  ratio_pfmet = (TH1D*)h_SR_ge4j_lt200mt2w_met->Clone("ratio_SR_CR_pfmet");
  ratio_pfmet->Divide(h_SR_ge4j_lt200mt2w_met,h_CR_ge4j_lt200mt2w_pfmet,1,1);

  ratio_rlmet = (TH1D*)h_SR_ge4j_lt200mt2w_met->Clone("ratio_SR_CR_rlmet");
  ratio_rlmet->Divide(h_SR_ge4j_lt200mt2w_met,h_CR_ge4j_lt200mt2w_rlmet,1,1);

  ratio_pfmet->SetLineColor(kGreen);
  ratio_rlmet->SetLineColor(kBlue);

  
  can = new TCanvas("can","can",10,10,1000,800);
  pad_main  = new TPad("main", "main",   0.0, 0.16, 1.00, 1.00);
  pad_ratio = new TPad("ratio", "ratio", 0.0, 0.00, 1.00, 0.17);

  pad_main->Draw();
  pad_ratio->Draw();

  pad_main->cd();
  pad_main->SetLogy();
  
  max = std::max( h_SR_ge4j_lt200mt2w_met->GetBinContent(h_SR_ge4j_lt200mt2w_met->GetMaximumBin()), h_CR_ge4j_lt200mt2w_pfmet->GetBinContent(h_CR_ge4j_lt200mt2w_pfmet->GetMaximumBin()) );
  max = std::max( max, h_CR_ge4j_lt200mt2w_rlmet->GetBinContent(h_CR_ge4j_lt200mt2w_rlmet->GetMaximumBin()) );
    
  h_SR_ge4j_lt200mt2w_met->SetMaximum(max*1.5);

  h_SR_ge4j_lt200mt2w_met->SetTitle("ge4j_lt200mt2w, SR and CR comparison of met");
  
  h_SR_ge4j_lt200mt2w_met->Draw("hist");
  h_CR_ge4j_lt200mt2w_pfmet->Draw("hist same");
  h_CR_ge4j_lt200mt2w_rlmet->Draw("hist same");
  
  leg = new TLegend(0.65, 0.65, 0.90, 0.90);
  leg->AddEntry(h_SR_ge4j_lt200mt2w_met,   "SR, standard pfmet", "l");
  leg->AddEntry(h_CR_ge4j_lt200mt2w_pfmet, "CR, standard pfmet", "l");
  leg->AddEntry(h_CR_ge4j_lt200mt2w_rlmet, "CR, 2nd lep removed met", "l");
  leg->Draw();


  pad_ratio->cd();
  
  line = new TLine( ratio_pfmet->GetXaxis()->GetBinLowEdge(1), 1.0, ratio_pfmet->GetXaxis()->GetBinUpEdge(ratio_pfmet->GetNbinsX()), 1.0 );
  line->SetLineWidth(3);
  line->SetLineColor(kRed);
  
  ratio_pfmet->SetMaximum(1.5);
  ratio_pfmet->SetMinimum(0.0);
  
  ratio_pfmet->Draw("e1");
  line->Draw("same");
  ratio_pfmet->Draw("e1 same");
  ratio_rlmet->Draw("e1 same");
  
  can->SaveAs("metComparison_SR_vs_CR__ge4j_lt200mt2w.pdf");
  can->~TCanvas();


  // >=4 jets, mt2w>200

  // Get Histos
  TH1D *h_SR_ge4j_ge200mt2w_met   = (TH1D*)f_SR->Get("met__genClassy_ge2lep__recoClassy_incl__cat_ge4jets_ge200mt2w__sys_nominal");
  TH1D *h_CR_ge4j_ge200mt2w_pfmet = (TH1D*)f_CR_pfmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets_ge200mt2w__sys_nominal");
  TH1D *h_CR_ge4j_ge200mt2w_rlmet = (TH1D*)f_CR_rlmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets_ge200mt2w__sys_nominal");
  
  //h_SR_ge4j_ge200mt2w_met->Rebin(4);
  //h_CR_ge4j_ge200mt2w_pfmet->Rebin(4);
  //h_CR_ge4j_ge200mt2w_rlmet->Rebin(4);
  
  const int nBins_ge4jets_ge200mt2w = 5;
  double xBins_ge4jets_ge200mt2w[nBins_ge4jets_ge200mt2w+1]{ 250.0, 350.0, 450.0, 550.0, 650.0, 800.0 };
  double xBins_SF_ge4jets_ge200mt2w[nBins_ge4jets_ge200mt2w]{   1.0,    1.0,   1.0,    1.0,   0.6666  };

  h_SR_ge4j_ge200mt2w_met = (TH1D*)h_SR_ge4j_ge200mt2w_met->Rebin(nBins_ge4jets_ge200mt2w, "SR_ge4j_ge200mt2w_met_rebin", xBins_ge4jets_ge200mt2w);
  h_CR_ge4j_ge200mt2w_pfmet = (TH1D*)h_CR_ge4j_ge200mt2w_pfmet->Rebin(nBins_ge4jets_ge200mt2w, "CR_ge4j_ge200mt2w_pfmet_rebin", xBins_ge4jets_ge200mt2w);
  h_CR_ge4j_ge200mt2w_rlmet = (TH1D*)h_CR_ge4j_ge200mt2w_rlmet->Rebin(nBins_ge4jets_ge200mt2w, "CR_ge4j_ge200mt2w_rlmet_rebin", xBins_ge4jets_ge200mt2w);
  for(int iBin=1; iBin<=nBins_ge4jets_ge200mt2w; iBin++){
    h_SR_ge4j_ge200mt2w_met->SetBinContent( iBin, h_SR_ge4j_ge200mt2w_met->GetBinContent(iBin)*xBins_SF_ge4jets_ge200mt2w[iBin-1] );
    h_SR_ge4j_ge200mt2w_met->SetBinError( iBin, h_SR_ge4j_ge200mt2w_met->GetBinError(iBin)*xBins_SF_ge4jets_ge200mt2w[iBin-1] );
    h_CR_ge4j_ge200mt2w_pfmet->SetBinContent( iBin, h_CR_ge4j_ge200mt2w_pfmet->GetBinContent(iBin)*xBins_SF_ge4jets_ge200mt2w[iBin-1] );
    h_CR_ge4j_ge200mt2w_pfmet->SetBinError( iBin, h_CR_ge4j_ge200mt2w_pfmet->GetBinError(iBin)*xBins_SF_ge4jets_ge200mt2w[iBin-1] );
    h_CR_ge4j_ge200mt2w_rlmet->SetBinContent( iBin, h_CR_ge4j_ge200mt2w_rlmet->GetBinContent(iBin)*xBins_SF_ge4jets_ge200mt2w[iBin-1] );
    h_CR_ge4j_ge200mt2w_rlmet->SetBinError( iBin, h_CR_ge4j_ge200mt2w_rlmet->GetBinError(iBin)*xBins_SF_ge4jets_ge200mt2w[iBin-1] );
  }

  h_SR_ge4j_ge200mt2w_met->SetLineColor(kRed);
  h_CR_ge4j_ge200mt2w_pfmet->SetLineColor(kGreen);
  h_CR_ge4j_ge200mt2w_rlmet->SetLineColor(kBlue);
  
  h_SR_ge4j_ge200mt2w_met->Scale(1.0/h_SR_ge4j_ge200mt2w_met->Integral(0,-1));
  h_CR_ge4j_ge200mt2w_pfmet->Scale(1.0/h_CR_ge4j_ge200mt2w_pfmet->Integral(0,-1));
  h_CR_ge4j_ge200mt2w_rlmet->Scale(1.0/h_CR_ge4j_ge200mt2w_rlmet->Integral(0,-1));
  

  ratio_pfmet = (TH1D*)h_SR_ge4j_ge200mt2w_met->Clone("ratio_SR_CR_pfmet");
  ratio_pfmet->Divide(h_SR_ge4j_ge200mt2w_met,h_CR_ge4j_ge200mt2w_pfmet,1,1);

  ratio_rlmet = (TH1D*)h_SR_ge4j_ge200mt2w_met->Clone("ratio_SR_CR_rlmet");
  ratio_rlmet->Divide(h_SR_ge4j_ge200mt2w_met,h_CR_ge4j_ge200mt2w_rlmet,1,1);

  ratio_pfmet->SetLineColor(kGreen);
  ratio_rlmet->SetLineColor(kBlue);

  
  can = new TCanvas("can","can",10,10,1000,800);
  pad_main  = new TPad("main", "main",   0.0, 0.16, 1.00, 1.00);
  pad_ratio = new TPad("ratio", "ratio", 0.0, 0.00, 1.00, 0.17);

  pad_main->Draw();
  pad_ratio->Draw();

  pad_main->cd();
  pad_main->SetLogy();
  
  max = std::max( h_SR_ge4j_ge200mt2w_met->GetBinContent(h_SR_ge4j_ge200mt2w_met->GetMaximumBin()), h_CR_ge4j_ge200mt2w_pfmet->GetBinContent(h_CR_ge4j_ge200mt2w_pfmet->GetMaximumBin()) );
  max = std::max( max, h_CR_ge4j_ge200mt2w_rlmet->GetBinContent(h_CR_ge4j_ge200mt2w_rlmet->GetMaximumBin()) );
    
  h_SR_ge4j_ge200mt2w_met->SetMaximum(max*1.5);

  h_SR_ge4j_ge200mt2w_met->SetTitle("ge4j_ge200mt2w, SR and CR comparison of met");
  
  h_SR_ge4j_ge200mt2w_met->Draw("hist");
  h_CR_ge4j_ge200mt2w_pfmet->Draw("hist same");
  h_CR_ge4j_ge200mt2w_rlmet->Draw("hist same");
  
  leg = new TLegend(0.65, 0.65, 0.90, 0.90);
  leg->AddEntry(h_SR_ge4j_ge200mt2w_met,   "SR, standard pfmet", "l");
  leg->AddEntry(h_CR_ge4j_ge200mt2w_pfmet, "CR, standard pfmet", "l");
  leg->AddEntry(h_CR_ge4j_ge200mt2w_rlmet, "CR, 2nd lep removed met", "l");
  leg->Draw();


  pad_ratio->cd();
  
  line = new TLine( ratio_pfmet->GetXaxis()->GetBinLowEdge(1), 1.0, ratio_pfmet->GetXaxis()->GetBinUpEdge(ratio_pfmet->GetNbinsX()), 1.0 );
  line->SetLineWidth(3);
  line->SetLineColor(kRed);
  
  ratio_pfmet->SetMaximum(2.0);
  ratio_pfmet->SetMinimum(0.5);
  
  ratio_pfmet->Draw("e1");
  line->Draw("same");
  ratio_pfmet->Draw("e1 same");
  ratio_rlmet->Draw("e1 same");
  
  can->SaveAs("metComparison_SR_vs_CR__ge4j_ge200mt2w.pdf");
  can->~TCanvas();



  // >=4 jets, SR met from genLostLep, vs genLostTau cs CR met

  // Get Histos
  TH1D *h_SR_ge4j_met_genLostLep = (TH1D*)f_SR->Get("met_genLostLep__genClassy_ge2lep__recoClassy_incl__cat_ge4jets__sys_nominal");
  TH1D *h_SR_ge4j_met_genLostTau = (TH1D*)f_SR->Get("met_genLostTau__genClassy_ge2lep__recoClassy_incl__cat_ge4jets__sys_nominal");
  h_CR_ge4j_pfmet = (TH1D*)f_CR_pfmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets__sys_nominal");
  h_CR_ge4j_rlmet = (TH1D*)f_CR_rlmet->Get("met__genClassy_incl__recoClassy_ee2lep_2selLepOrVetoLep__cat_ge4jets__sys_nominal");
  
  const int nBins_ge4jets_genLost = 4;
  double xBins_ge4jets_genLost[nBins_ge4jets_genLost+1]{ 250.0, 350.0, 450.0, 550.0, 800.0 };
  double xBins_SF_ge4jets_genLost[nBins_ge4jets_genLost]{   1.0,    1.0,   1.0,  0.4   };

  h_SR_ge4j_met_genLostLep = (TH1D*)h_SR_ge4j_met_genLostLep->Rebin(nBins_ge4jets_genLost, "SR_ge4j_met_genLostLep_rebin", xBins_ge4jets_genLost);
  h_SR_ge4j_met_genLostTau = (TH1D*)h_SR_ge4j_met_genLostTau->Rebin(nBins_ge4jets_genLost, "SR_ge4j_met_genLostTau_rebin", xBins_ge4jets_genLost);
  h_CR_ge4j_pfmet = (TH1D*)h_CR_ge4j_pfmet->Rebin(nBins_ge4jets_genLost, "CR_ge4j_pfmet_rebin2", xBins_ge4jets_genLost);
  h_CR_ge4j_rlmet = (TH1D*)h_CR_ge4j_rlmet->Rebin(nBins_ge4jets_genLost, "CR_ge4j_rlmet_rebin2", xBins_ge4jets_genLost);
  for(int iBin=1; iBin<=nBins_ge4jets_genLost; iBin++){
    h_SR_ge4j_met_genLostLep->SetBinContent( iBin, h_SR_ge4j_met_genLostLep->GetBinContent(iBin)*xBins_SF_ge4jets_genLost[iBin-1] );
    h_SR_ge4j_met_genLostLep->SetBinError( iBin, h_SR_ge4j_met_genLostLep->GetBinError(iBin)*xBins_SF_ge4jets_genLost[iBin-1] );
    h_SR_ge4j_met_genLostTau->SetBinContent( iBin, h_SR_ge4j_met_genLostTau->GetBinContent(iBin)*xBins_SF_ge4jets_genLost[iBin-1] );
    h_SR_ge4j_met_genLostTau->SetBinError( iBin, h_SR_ge4j_met_genLostTau->GetBinError(iBin)*xBins_SF_ge4jets_genLost[iBin-1] );
    h_CR_ge4j_pfmet->SetBinContent( iBin, h_CR_ge4j_pfmet->GetBinContent(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_CR_ge4j_pfmet->SetBinError( iBin, h_CR_ge4j_pfmet->GetBinError(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_CR_ge4j_rlmet->SetBinContent( iBin, h_CR_ge4j_rlmet->GetBinContent(iBin)*xBins_SF_ge4jets[iBin-1] );
    h_CR_ge4j_rlmet->SetBinError( iBin, h_CR_ge4j_rlmet->GetBinError(iBin)*xBins_SF_ge4jets[iBin-1] );
  }

  
  h_SR_ge4j_met_genLostLep->SetLineColor(kRed);
  h_SR_ge4j_met_genLostTau->SetLineColor(kBlue);
  h_CR_ge4j_pfmet->SetLineColor(kGreen);
  h_CR_ge4j_rlmet->SetLineColor(kMagenta);
  
  h_SR_ge4j_met_genLostLep->Scale(1.0/h_SR_ge4j_met_genLostLep->Integral(0,-1));
  h_SR_ge4j_met_genLostTau->Scale(1.0/h_SR_ge4j_met_genLostTau->Integral(0,-1));
  h_CR_ge4j_pfmet->Scale(1.0/h_CR_ge4j_pfmet->Integral(0,-1));
  h_CR_ge4j_rlmet->Scale(1.0/h_CR_ge4j_rlmet->Integral(0,-1));


  can = new TCanvas("can","can",10,10,1000,800);
  can->SetLogy();
  
  max = std::max( h_SR_ge4j_met_genLostLep->GetBinContent(h_SR_ge4j_met_genLostLep->GetMaximumBin()), h_SR_ge4j_met_genLostTau->GetBinContent(h_SR_ge4j_met_genLostTau->GetMaximumBin()) );
  max = std::max( max, h_CR_ge4j_pfmet->GetBinContent(h_CR_ge4j_pfmet->GetMaximumBin()) );
  max = std::max( max, h_CR_ge4j_rlmet->GetBinContent(h_CR_ge4j_rlmet->GetMaximumBin()) );
    
  h_SR_ge4j_met_genLostLep->SetMaximum(max*1.5);

  h_SR_ge4j_met_genLostLep->SetTitle("ge4j, SR and CR comparison of met");
  
  h_SR_ge4j_met_genLostLep->Draw("hist");
  h_SR_ge4j_met_genLostTau->Draw("hist same");
  h_CR_ge4j_pfmet->Draw("hist same");
  h_CR_ge4j_rlmet->Draw("hist same");
 
  h_SR_ge4j_met_genLostLep->Draw("e1 same");
  h_SR_ge4j_met_genLostTau->Draw("e1 same");
  h_CR_ge4j_pfmet->Draw("e1 same");
  h_CR_ge4j_rlmet->Draw("e1 same");
 
  leg = new TLegend(0.65, 0.65, 0.90, 0.90);
  leg->AddEntry(h_SR_ge4j_met_genLostLep,   "SR, standard pfmet, genLost e/mu", "l");
  leg->AddEntry(h_SR_ge4j_met_genLostTau,   "SR, standard pfmet, genLost tau", "l");
  leg->AddEntry(h_CR_ge4j_pfmet, "CR, standard pfmet", "l");
  leg->AddEntry(h_CR_ge4j_rlmet, "CR, 2nd lep removed met", "l");
  leg->Draw();


  can->SaveAs("metComparison__SR_genLostLeps_vs_CR__ge4j.pdf");
  can->~TCanvas();


  return 0;
}
