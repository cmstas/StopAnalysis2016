#include "Riostream.h"
#include "TFile.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TString.h"

#include <algorithm>
#include <vector>
#include <utility>

bool comparePairBySecond(std::pair<int,double> left, std::pair<int, double> right){
  return left.second>right.second;
}

bool comparePairBySecondLowToHigh(std::pair<int,double> left, std::pair<int, double> right){
  return left.second<right.second;
}


void drawQuick__lostLepton_studies(){
  
  // This code draws plots from ttbar_2l for studies related to
  //   the behaviour of the ttbar system
  
  // Open ttbar_2l file and signal files
  TFile *f_ttbar_2l = new TFile("Histos/histos__ttbar_2l.root", "read");
  TFile *f_stop_850_100 = new TFile("Histos/histos__stop_850_100_1l.root", "read");
  TFile *f_stop_650_325 = new TFile("Histos/histos__stop_650_325_1l.root", "read");
  TFile *f_stop_500_325 = new TFile("Histos/histos__stop_500_325_1l.root", "read");
  
  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(3);

  TH1D *h1;
  TH1D *h1_2;
  TH2D *h2;
  TProfile *prof;
  TMultiGraph *mg;
  TGraph *g;

  TCanvas *c1;
  TLegend *leg;
  TLine *line;
  TLatex tex;
  tex.SetTextSize(0.025);

  std::vector< std::pair<int,double> > bkgEff;
  std::vector< std::pair<int,double> > sigEff;
  
  std::vector<double> xEff;
  std::vector<double> yEff;
  std::vector<TString> cfgTitle;

  FILE *cfgFile;

  double yMax = 1.0;


  //TString default_cfg = "dr=0.4, pfMuIso=0.2, pfMuQVeto=0, pfElIso=0.2, pfElQVeto=0, pfHadIso=0.1";
  //TString default_cfg = "dr=0.4, pfMuIso=0.2, pfMuQVeto=0, pfElIso=0.2, pfElQVeto=0, pfElAbsIso=0.0, pfHadIso=0.1";
  //TString default_cfg = "pfMuIso=0.2, pfMuQVeto=0, pfElIso=0.2, pfElQVeto=0, pfElAbsIso=0.0, pfHadIso=0.1";
  TString default_cfg = "pfMuIso=0.2, pfMuQVeto=0, pfElIso=0.2, pfElQVeto=0, pfAbsIso=0.0, pfHadIso=0.1";
  Double_t y_default[1] = {0.0};
  Double_t x_default[1] = {0.0};


  /*
  //
  // Plot of the number of Gen leptons in the event
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_nGenLeptons_fromTop");
  h1->SetTitle("t#bar{t} 2l, baseline selection, nGen Leptons from Top");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("N Gen Leptons from Top");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__nGenLeptonsFromTop.pdf");
  c1->~TCanvas();


  //
  // Plot of the number of lost gen leptons in the event
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_nFound_gen_ttbarLostLeptons_notMatchedToSelLep");
  h1->SetTitle("t#bar{t} 2l, baseline selection, nGen Leptons from Top, NOT matched to selected lepton");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("N Gen Leptons from Top, NOT matched to selected Lepton");
  tex.DrawLatex( 3.0, 0.5, Form("%.5f%% of cases where 2 leptons from top found,", h1->Integral(3,-1)/h1->Integral(0,-1)) ); 
  tex.DrawLatex( 3.0, 0.4, Form("mostly cases of double hadronic tau decay") ); 
  tex.DrawLatex( 3.0, 0.3, Form("1 case: 2 el decay, selected lepton mu") );
  tex.DrawLatex( 3.0, 0.2, Form("3 cases: 3 gen particles found with isFromTop==true") );
 
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__nGenLeptonsFromTop_NotMatchedToSelectedLepton.pdf");
  c1->~TCanvas();


  //
  // Plot of the number of Gen leptons in the event
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_deltaR_selLep_genLep");
  h1->SetTitle("t#bar{t} 2l, baseline selection, #DeltaR(sel,gen)");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("#DeltaR(sel,gen)");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__deltaR_selLep_genLep.pdf");
  c1->~TCanvas();
  

  //
  // Plot of the number of Gen leptons in the event
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_lostLepton_id");
  h1->SetTitle("t#bar{t} 2l, baseline selection, Lost Lepton ID");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetStats(0);
  h1->Draw("hist text00");
  h1->GetXaxis()->SetTitle("");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__lostLeptonID.pdf");
  c1->~TCanvas();


  //
  // Plot of lost lepton pT vs eta, projections, Baseline
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h2 = (TH2D*)f_ttbar_2l->Get("h_lostLepton_pt_vs_eta");
  gStyle->SetOptStat(0);
  h2->SetTitle("t#bar{t} 2l, Baseline, gen lost lepton, pT vs #eta");
  h2->Draw("colz norm");
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostLepton__pt_vs_eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionX();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost lepton #eta");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost Lepton #eta");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostLepton__pt_vs_eta__projectionX__eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionY();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost lepton pT");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen lost lepton pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostLepton__pt_vs_eta__projectionY__pt.pdf");
  c1->~TCanvas();



  //
  // Plot of good Lost Lepton pT vs eta, projections, Baseline
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h2 = (TH2D*)f_ttbar_2l->Get("h_lostLepton_pt_vs_eta_goodPtEta");
  gStyle->SetOptStat(0);
  h2->SetTitle("t#bar{t} 2l, Baseline, gen lost lepton, pT vs #eta, passing pT #eta cuts for trackIsoVeto");
  h2->Draw("colz norm");
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostLepton__pt_vs_eta_goodPtEta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionX();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost lepton #eta, passing pT #eta cuts for trackIsoVeto");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost Lepton #eta");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostLepton__pt_vs_eta_goodPtEta__projectionX__eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionY();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost lepton pT, passing pT #eta cuts for trackIsoVeto");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen lost lepton pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostLepton__pt_vs_eta_goodPtEta__projectionY__pt.pdf");
  c1->~TCanvas();



  //
  // Plot of good Lost Muon pT vs eta, projections, Baseline
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h2 = (TH2D*)f_ttbar_2l->Get("h_lostLepton_pt_vs_eta_mu");
  gStyle->SetOptStat(0);
  h2->SetTitle("t#bar{t} 2l, Baseline, gen lost muon, pT vs #eta");
  h2->Draw("colz norm");
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostMuon__pt_vs_eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionX();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost muon #eta");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost Muon #eta");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostMuon__pt_vs_eta__projectionX__eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionY();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost muon pT");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost Muon pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostMuon__pt_vs_eta__projectionY__pt.pdf");
  c1->~TCanvas();


  //
  // Plot of good Lost Electron pT vs eta, projections, Baseline
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h2 = (TH2D*)f_ttbar_2l->Get("h_lostLepton_pt_vs_eta_el");
  gStyle->SetOptStat(0);
  h2->SetTitle("t#bar{t} 2l, Baseline, gen lost electron, pT vs #eta");
  h2->Draw("colz norm");
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostElectron__pt_vs_eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionX();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost electron #eta");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost Electron #eta");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostElectron__pt_vs_eta__projectionX__eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionY();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost electron pT");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost Electron pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostElectron__pt_vs_eta__projectionY__pt.pdf");
  c1->~TCanvas();

  

  //
  // Plot of good Lost 1 prong had tau pT vs eta, projections, Baseline
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h2 = (TH2D*)f_ttbar_2l->Get("h_lostLepton_pt_vs_eta_hadTau_1prong");
  gStyle->SetOptStat(0);
  h2->SetTitle("t#bar{t} 2l, Baseline, gen lost 1 prong had tau, pT vs #eta");
  h2->Draw("colz norm");
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostHadTau_1prong__pt_vs_eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionX();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost 1 prong had tau #eta");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost 1 prong had tau #eta");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostHadTau_1prong__pt_vs_eta__projectionX__eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionY();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost 1 prong had tau pT");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen lost 1 prong had tau pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostHadTau_1prong__pt_vs_eta__projectionY__pt.pdf");
  c1->~TCanvas();


  //
  // Plot of good Lost 3 prong had tau pT vs eta, projections, Baseline
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h2 = (TH2D*)f_ttbar_2l->Get("h_lostLepton_pt_vs_eta_hadTau_3prong");
  gStyle->SetOptStat(0);
  h2->SetTitle("t#bar{t} 2l, Baseline, gen lost 3 prong had tau, pT vs #eta");
  h2->Draw("colz norm");
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostHadTau_3prong__pt_vs_eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionX();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost 3 prong had tau #eta");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen Lost 3 prong had tau #eta");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostHadTau_3prong__pt_vs_eta__projectionX__eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionY();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost 3 prong had tau pT");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("Gen lost 3 prong had tau pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostHadTau_3prong__pt_vs_eta__projectionY__pt.pdf");
  c1->~TCanvas();



  //
  // Plot of the dR pfEle and gen Lost ele
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
 
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfCand_genLostLep_el");
  h1->SetLineColor(kBlue);
  h1->SetTitle("t#bar{t} 2l, baseline selection, min#DeltaR(pfEl and pfCand,genLostEl)");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("#DeltaR(pfCand,genLostEl)");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "min#DeltaR(pfEl or pfHad, gen lost electron)", "l");
  
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfEl_genLostLep_el");
  h1->SetLineColor(kRed);
  h1->SetTitle("t#bar{t} 2l, baseline selection, #DeltaR(pfEl,genLostEl)");
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "min#DeltaR(pfEl, gen lost electron)", "l");
  leg->SetTextSize(0.020);
  leg->Draw();

  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__minDeltaR_pfEl_and_pfCand_genLostLep_el.pdf");
  c1->~TCanvas();
  

  //
  // Plot of the dR pfMu and gen Lost Mu
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfCand_genLostLep_mu");
  h1->SetLineColor(kBlue);
  h1->SetTitle("t#bar{t} 2l, baseline selection, #DeltaR(pfMu and pfCand,genLostMu)");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("#DeltaR(pfCand,genLostMu)");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "min#DeltaR(pfMu or pfHad, gen lost muon)", "l");
  
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfMu_genLostLep_mu");
  h1->SetLineColor(kRed);
  h1->Draw("hist same");
  h1->Rebin(10);

  leg->AddEntry(h1, "min#DeltaR(pfMu, gen lost muon)", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__minDeltaR_pfMu_and_pfCand_genLostLep_mu.pdf");
  c1->~TCanvas();


  //
  // Plot of the dR pfHad and gen lost Had Tau, 1 prong
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfCand_genLostLep_hadTau_1prong");
  h1->SetLineColor(kBlue);
  h1->SetTitle("t#bar{t} 2l, baseline selection, #DeltaR(pfHad and pfCand,genLost 1 prong Had Tau)");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("#DeltaR(pfCand,genLost 1 prong Had Tau)");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "min#DeltaR(pfCand or pfHad, gen lost had tau)", "l");
    
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfHad_genLostLep_hadTau_1prong");
  h1->SetLineColor(kRed);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "min#DeltaR(pfHad, gen lost had tau)", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__minDeltaR_pfHad_and_pfCand_genLostLep_hadTau_1prong.pdf");
  c1->~TCanvas();


  //
  // Plot of the dR pfHad and gen lost Had Tau, 3 prong
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfCand_genLostLep_hadTau_3prong");
  h1->SetLineColor(kBlue);
  h1->SetTitle("t#bar{t} 2l, baseline selection, #DeltaR(pfHad and pfCand,genLost 3 prong Had Tau)");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("#DeltaR(pfCand,genLost 3 prong Had Tau)");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "min#DeltaR(pfCand or pfHad, gen lost had tau)", "l");
  
  h1 = (TH1D*)f_ttbar_2l->Get("h_minDeltaR_pfHad_genLostLep_hadTau_3prong");
  h1->SetLineColor(kRed);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "min#DeltaR(pfHad, gen lost had tau)", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__minDeltaR_pfHad_and_pfCand_genLostLep_hadTau_3prong.pdf");
  c1->~TCanvas();


  
  //
  // Plot of lost Electron unMatched to pfEl, Baseline
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h2 = (TH2D*)f_ttbar_2l->Get("h_genLostEl_unMatchedTo_pfEl_pt_vs_eta_el");
  gStyle->SetOptStat(0);
  h2->SetTitle("t#bar{t} 2l, Baseline, gen lost electron NOT matched to pfEl, pT vs #eta");
  h2->Draw("colz norm");
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostElectron_NOTmatchedToPfEl__pt_vs_eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionX();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost electron, NOT matched to pfEl #eta");
  h1->Draw("hist");
  h1->Rebin(2);
  h1->GetXaxis()->SetTitle("unMatched Gen Lost Electron #eta");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostElectron_NOTmatchedToPfEl__pt_vs_eta__projectionX__eta.pdf");
  c1->~TCanvas();

  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)h2->ProjectionY();
  h1->SetTitle("t#bar{t} 2l, Baseline, gen lost electron, NOT matched to pfEl pT");
  h1->Draw("hist");
  h1->GetXaxis()->SetTitle("unMatched Gen Lost Electron pT [GeV]");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__genLostElectron_NOTmatchedToPfEl__pt_vs_eta__projectionY__pt.pdf");
  c1->~TCanvas();


  //
  // Plot of the relTrackIso for matched genLepton
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_relTrackIso_pfLep_matchedTo_genLostLep_mu");
  h1->SetTitle("t#bar{t} 2l, baseline selection, relative track Iso, pfMu matched to genLostMu");
  h1->Draw("hist");
  //h1->Rebin(10);
  h1->GetXaxis()->SetTitle("relative TrackIso");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__relTrackIso_pfLep_matchedTo_genLostLep_mu.pdf");
  c1->~TCanvas();


  //
  // Plot of the relTrackIso for matched genLepton ZOOMED
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_relTrackIso_pfLep_matchedTo_genLostLep_mu");
  h1->SetTitle("t#bar{t} 2l, baseline selection, relative track Iso, pfMu matched to genLostMu");
  h1->Draw("hist");
  //h1->Rebin(10);
  h1->GetXaxis()->SetRangeUser(0.0, 1.0);
  h1->GetXaxis()->SetTitle("relative TrackIso");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__relTrackIso_pfLep_matchedTo_genLostLep_mu_ZOOMED.pdf");
  c1->~TCanvas();


  //
  // Plot of the relTrackIso for matched genLepton
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_relTrackIso_pfLep_matchedTo_genLostLep_el");
  h1->SetTitle("t#bar{t} 2l, baseline selection, relative track Iso, pfEl matched to genLostEl");
  h1->Draw("hist");
  //h1->Rebin(10);
  h1->GetXaxis()->SetTitle("relative TrackIso");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__relTrackIso_pfLep_matchedTo_genLostLep_el.pdf");
  c1->~TCanvas();

  //
  // Plot of the relTrackIso for matched genLepton ZOOMED
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_relTrackIso_pfLep_matchedTo_genLostLep_el");
  h1->SetTitle("t#bar{t} 2l, baseline selection, relative track Iso, pfEl matched to genLostEl");
  h1->Draw("hist");
  //h1->Rebin(10);
  h1->GetXaxis()->SetRangeUser(0.0, 1.0);
  h1->GetXaxis()->SetTitle("relative TrackIso");
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l__relTrackIso_pfLep_matchedTo_genLostLep_el_ZOOMED.pdf");
  c1->~TCanvas();


  */

  
  /*
  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop850/100, without AbsIso, with dR
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    //if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfElAbsIso=0.0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond ); 
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, both dR(selLep) working points, no absIso");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__bestSigEff_noPfElAbsIso_withDr.pdf");
  c1->~TCanvas();
  */

  //
  // Sig 850/100
  //

  //
  // Plot trkIso Optimization sig eff vs bkg eff, stop850/100, all points
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );
    
    xEff.push_back( h1->GetBinContent(iBin) );
    yEff.push_back( h1_2->GetBinContent(iBin) );
    cfgTitle.push_back( test );

  }
  //std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, all working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<(int)sigEff.size(); i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    //g->SetMarkerColor(i+1);
    //g->SetMarkerStyle(24+i);
    g->SetMarkerColor(kBlack);
    g->SetMarkerStyle(20);
    g->SetMarkerSize(0.25);
    mg->Add(g);
    //leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kRed);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(0.45);
  mg->Add(g);
  //leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  //mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  //leg->Draw();

  cfgFile = fopen("Plots/trkIsoVeto_workingPoints__stop_850_100_1l__vs__ttbar2l.txt", "w");
  tex.SetTextSize(0.002);
  for(int i=0; i<(int)xEff.size(); i++){
    tex.DrawLatex( xEff[i]+0.002, yEff[i], Form("%d",i) );
    fprintf( cfgFile, "Pnt %d, %.4f, %.4f, %s \n", i, xEff[i], yEff[i], cfgTitle[i].Data() );
  }

  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__allCfgs.pdf");
  c1->~TCanvas();
  
  fclose(cfgFile);
  xEff.clear();
  yEff.clear();
  cfgTitle.clear();
  

  
  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop850/100, without lepQVeto, without AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    if( !(test.Contains("pfMuQVeto=0")) ) continue;
    if( !(test.Contains("pfElQVeto=0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no lepQ veto or absIso working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
    //cout << "(x,y)=" << x[0] << "," << y[0] << endl;
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.80, 1.1);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__bestSigEff_noPfLepQVeto_noPfAbsIso.pdf");
  c1->~TCanvas();



  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop850/100, without lepQVeto
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    if( !(test.Contains("pfMuQVeto=0")) ) continue;
    if( !(test.Contains("pfElQVeto=0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no lepQVeto working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
    //cout << "(x,y)=" << x[0] << "," << y[0] << endl;
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.80, 1.1);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__bestSigEff_noPfLepQVeto.pdf");
  c1->~TCanvas();



  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop850/100, without AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=0.0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no absIso working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__bestSigEff_noPfAbsIso.pdf");
  c1->~TCanvas();
  

  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop850/100, with AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );
  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 sig eff working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__bestSigEff.pdf");
  c1->~TCanvas();


  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop850/100, with AbsIso==6.0
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=1.0")) ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 best sig working points, absIso<pfEl/Had relIso*60, absIso<pfMu relIso*30");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__bestSigEff_pfAbsIso6p0.pdf");
  c1->~TCanvas();


  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop850/100, with AbsIso==6.0, muRelIso0.2
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=1.0")) ) continue;
    if( !(test.Contains("pfMuIso=0.2")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 best sig working points, pfMuRelIso=0.2, pfMuAbsIso<6.0, absIso<pfEl/Had relIso*60");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__bestSigEff__pfMuIso0p2_pfAbsIso6p0.pdf");
  c1->~TCanvas();




  //
  // Plot trkIso Optimization sig eff vs bkg eff, lowest bkg Eff, stop850/100
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1->GetBinContent(iBin);
    bkgEff.push_back( temp );

  }
  std::sort( bkgEff.begin(), bkgEff.end(), comparePairBySecondLowToHigh );
  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 lowest bkg eff working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 lowest bkg eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(bkgEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(bkgEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(bkgEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.65, 1.05);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__lowestBkgEff.pdf");
  c1->~TCanvas();
  

  
  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig/bkg Eff, stop850/100
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_850_100->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;

    double minR = sqrt( pow((h1->GetBinContent(iBin)-0.0), 2) + pow((h1_2->GetBinContent(iBin)-1.0),2) );

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = minR;
    bkgEff.push_back( temp );

  }
  std::sort( bkgEff.begin(), bkgEff.end(), comparePairBySecondLowToHigh );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 850/100) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 minR from (0,1) working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 lowest bkg eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(bkgEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(bkgEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(bkgEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.75, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop850_100__maxSigEffAndBkgRej.pdf");
  c1->~TCanvas();


  
  //
  // Sig 650/325
  //

  //
  // Plot trkIso Optimization sig eff vs bkg eff, stop650/325, all points
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );
    
    xEff.push_back( h1->GetBinContent(iBin) );
    yEff.push_back( h1_2->GetBinContent(iBin) );
    cfgTitle.push_back( test );

  }
  //std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, all working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<(int)sigEff.size(); i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    //g->SetMarkerColor(i+1);
    //g->SetMarkerStyle(24+i);
    g->SetMarkerColor(kBlack);
    g->SetMarkerStyle(20);
    g->SetMarkerSize(0.25);
    mg->Add(g);
    //leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kRed);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(0.45);
  mg->Add(g);
  //leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  //mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  //leg->Draw();

  cfgFile = fopen("Plots/trkIsoVeto_workingPoints__stop_650_325_1l__vs__ttbar2l.txt", "w");
  tex.SetTextSize(0.002);
  for(int i=0; i<(int)xEff.size(); i++){
    tex.DrawLatex( xEff[i]+0.002, yEff[i], Form("%d",i) );
    fprintf( cfgFile, "Pnt %d, %.4f, %.4f, %s \n", i, xEff[i], yEff[i], cfgTitle[i].Data() );
  }

  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__allCfgs.pdf");
  c1->~TCanvas();
  
  fclose(cfgFile);
  xEff.clear();
  yEff.clear();
  cfgTitle.clear();
  

  
  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop650/325, without lepQVeto, without AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    if( !(test.Contains("pfMuQVeto=0")) ) continue;
    if( !(test.Contains("pfElQVeto=0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no lepQ veto or absIso working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
    //cout << "(x,y)=" << x[0] << "," << y[0] << endl;
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.80, 1.1);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__bestSigEff_noPfLepQVeto_noPfAbsIso.pdf");
  c1->~TCanvas();



  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop650/325, without lepQVeto
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    if( !(test.Contains("pfMuQVeto=0")) ) continue;
    if( !(test.Contains("pfElQVeto=0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no lepQVeto working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
    //cout << "(x,y)=" << x[0] << "," << y[0] << endl;
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.80, 1.1);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__bestSigEff_noPfLepQVeto.pdf");
  c1->~TCanvas();



  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop650/325, without AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=0.0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no absIso working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__bestSigEff_noPfAbsIso.pdf");
  c1->~TCanvas();
  

  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop650/325, with AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );
  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 sig eff working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__bestSigEff.pdf");
  c1->~TCanvas();


  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop650/325, with AbsIso==6.0
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=1.0")) ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 best sig working points, absIso<pfEl/Had relIso*60, absIso<pfMu relIso*30");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__bestSigEff_pfAbsIso6p0.pdf");
  c1->~TCanvas();




  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop650/325, with AbsIso==6.0, muRelIso0.2
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=1.0")) ) continue;
    if( !(test.Contains("pfMuIso=0.2")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 best sig working points, pfMuIso=0.2, pfMuAbsIso<6.0, absIso<pfEl/Had relIso*60");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__bestSigEff__pfMuIso0p2_pfAbsIso6p0.pdf");
  c1->~TCanvas();




  //
  // Plot trkIso Optimization sig eff vs bkg eff, lowest bkg Eff, stop650/325
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1->GetBinContent(iBin);
    bkgEff.push_back( temp );

  }
  std::sort( bkgEff.begin(), bkgEff.end(), comparePairBySecondLowToHigh );
  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 lowest bkg eff working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 lowest bkg eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(bkgEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(bkgEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(bkgEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.65, 1.05);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__lowestBkgEff.pdf");
  c1->~TCanvas();
  

  
  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig/bkg Eff, stop650/325
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_650_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;

    double minR = sqrt( pow((h1->GetBinContent(iBin)-0.0), 2) + pow((h1_2->GetBinContent(iBin)-1.0),2) );

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = minR;
    bkgEff.push_back( temp );

  }
  std::sort( bkgEff.begin(), bkgEff.end(), comparePairBySecondLowToHigh );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 650/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 minR from (0,1) working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 lowest bkg eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(bkgEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(bkgEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(bkgEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.75, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop650_325__maxSigEffAndBkgRej.pdf");
  c1->~TCanvas();


  // 
  // Sig 500/325
  //
  

  //
  // Plot trkIso Optimization sig eff vs bkg eff, stop500/325, all points
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );
    
    xEff.push_back( h1->GetBinContent(iBin) );
    yEff.push_back( h1_2->GetBinContent(iBin) );
    cfgTitle.push_back( test );

  }
  //std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, all working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<(int)sigEff.size(); i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    //g->SetMarkerColor(i+1);
    //g->SetMarkerStyle(24+i);
    g->SetMarkerColor(kBlack);
    g->SetMarkerStyle(20);
    g->SetMarkerSize(0.25);
    mg->Add(g);
    //leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kRed);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(0.45);
  mg->Add(g);
  //leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  //mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  //leg->Draw();

  cfgFile = fopen("Plots/trkIsoVeto_workingPoints__stop_500_325_1l__vs__ttbar2l.txt", "w");
  tex.SetTextSize(0.002);
  for(int i=0; i<(int)xEff.size(); i++){
    tex.DrawLatex( xEff[i]+0.002, yEff[i], Form("%d",i) );
    fprintf( cfgFile, "Pnt %d, %.4f, %.4f, %s \n", i, xEff[i], yEff[i], cfgTitle[i].Data() );
  }

  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__allCfgs.pdf");
  c1->~TCanvas();
  
  fclose(cfgFile);
  xEff.clear();
  yEff.clear();
  cfgTitle.clear();
  

  
  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop500/325, without lepQVeto, without AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    if( !(test.Contains("pfMuQVeto=0")) ) continue;
    if( !(test.Contains("pfElQVeto=0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no lepQ veto or absIso working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
    //cout << "(x,y)=" << x[0] << "," << y[0] << endl;
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.80, 1.1);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__bestSigEff_noPfLepQVeto_noPfAbsIso.pdf");
  c1->~TCanvas();



  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop500/325, without lepQVeto
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    if( !(test.Contains("pfMuQVeto=0")) ) continue;
    if( !(test.Contains("pfElQVeto=0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no lepQVeto working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
    //cout << "(x,y)=" << x[0] << "," << y[0] << endl;
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.80, 1.1);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__bestSigEff_noPfLepQVeto.pdf");
  c1->~TCanvas();



  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop500/325, without AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=0.0")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, no absIso working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__bestSigEff_noPfAbsIso.pdf");
  c1->~TCanvas();
  

  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop500/325, with AbsIso
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    //if( !(test.Contains("pfAbsIso=0.0")) ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );
  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 sig eff working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__bestSigEff.pdf");
  c1->~TCanvas();


  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop500/325, with AbsIso==6.0
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=1.0")) ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 best sig working points, absIso<pfEl/Had relIso*60, absIso<pfMu relIso*30");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__bestSigEff_pfAbsIso6p0.pdf");
  c1->~TCanvas();



  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig Eff, stop500/325, with AbsIso==6.0, muRelIso0.2
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    if( !(test.Contains("pfAbsIso=1.0")) ) continue;
    if( !(test.Contains("pfMuIso=0.2")) ) continue;

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1_2->GetBinContent(iBin);
    sigEff.push_back( temp );

  }
  std::sort( sigEff.begin(), sigEff.end(), comparePairBySecond );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 best sig working points, pfMuIso=0.2, pfMuAbsIso<6.0, absIso<pfEl/Had relIso*60");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 most sig eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(sigEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(sigEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(sigEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.90, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__bestSigEff__pfMuIso0p2_pfAbsIso6p0.pdf");
  c1->~TCanvas();




  //
  // Plot trkIso Optimization sig eff vs bkg eff, lowest bkg Eff, stop500/325
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;
    
    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = h1->GetBinContent(iBin);
    bkgEff.push_back( temp );

  }
  std::sort( bkgEff.begin(), bkgEff.end(), comparePairBySecondLowToHigh );
  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 lowest bkg eff working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 lowest bkg eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(bkgEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(bkgEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(bkgEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.65, 1.05);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__lowestBkgEff.pdf");
  c1->~TCanvas();
  

  
  //
  // Plot trkIso Optimization sig eff vs bkg eff, best sig/bkg Eff, stop500/325
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_trkIso_optimization_eff");
  h1_2 = (TH1D*)f_stop_500_325->Get("h_trkIso_optimization_eff");
  
  bkgEff.clear();
  sigEff.clear();
  for(int iBin=1; iBin<=(int)h1_2->GetNbinsX(); iBin++){
    TString test = h1_2->GetXaxis()->GetBinLabel(iBin);
    if( test.Contains(default_cfg) ){
      y_default[0] = h1_2->GetBinContent(iBin);
      x_default[0] = h1->GetBinContent(iBin);
    }

    if( test.Contains("dr=0.1") ) continue;

    double minR = sqrt( pow((h1->GetBinContent(iBin)-0.0), 2) + pow((h1_2->GetBinContent(iBin)-1.0),2) );

    std::pair<int,double> temp;
    temp.first = iBin;
    temp.second = minR;
    bkgEff.push_back( temp );

  }
  std::sort( bkgEff.begin(), bkgEff.end(), comparePairBySecondLowToHigh );  
  //for(int i=0; i<(int)sigEff.size(); i++) cout << "sigEff=" << sigEff[i].second << ", bin=" << sigEff[i].first << endl; 
   
  mg = new TMultiGraph();
  mg->SetTitle( "Signal Eff (Stop 500/325) vs Bkg Eff (t#bar{t} 2l), track isolation veto, top 10 minR from (0,1) working points");
  leg = new TLegend(0.1, 0.7, 0.9, 0.9);
  leg->SetNColumns(2);

  // Get top 10 lowest bkg eff cfgs
  for(int i=0; i<9; i++){
    Double_t x[1] = {h1->GetBinContent(bkgEff[i].first)};
    Double_t y[1] = {h1_2->GetBinContent(bkgEff[i].first)};
    g = new TGraph(1, x, y);
    g->SetMarkerColor(i+1);
    g->SetMarkerStyle(24+i);
    mg->Add(g);
    leg->AddEntry(g, h1->GetXaxis()->GetBinLabel(bkgEff[i].first), "p");
  }
  // Add default
  g = new TGraph(1, x_default, y_default);
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  mg->Add(g);
  leg->AddEntry(g, "Default Cfg: "+default_cfg, "p");
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("background efficiency");
  mg->GetYaxis()->SetTitle("signal efficiency");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetRangeUser(0.75, 1.0);
  leg->Draw();
  c1->SaveAs("Plots/lostLeptonStudies__trkIsoVeto_workingPoints__sigEff_vs_bkgEff__stop500_325__maxSigEffAndBkgRej.pdf");
  c1->~TCanvas();

  



  //
  // Plot of the pf El absTrkIso for pt>60.0
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_isEl_ptGT60_absIso");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.8);
  h1->SetTitle("Baseline selection, Absolute track isolation, of a pfEl that is an isoTrack and has p_{T}>60.0");
  h1->Draw("hist");
  h1->Rebin(5);
  h1->GetXaxis()->SetTitle("aboslute track iso dr0.3");
  
  leg = new TLegend(0.10, 0.70, 0.60, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_isEl_ptGT60_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_isEl_ptGT60_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_isEl_ptGT60_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__absTrkIso_pfEl_ptGT60.pdf");
  c1->~TCanvas();


  
  //
  // Plot of the pf El relTrkIso for values < 0.6
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.6);
  h1->SetTitle("Baseline selection, Relative track isolation, of a pfEl that has passed pT requirement && iso<0.6");
  h1->Draw("hist");
  h1->Rebin(2);
  h1->GetXaxis()->SetTitle("relative track iso dr0.3");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_passPt_isoLT0p6_isEl_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__relTrkIso_pfEl_ptGT5p0_relIsoLT0p6.pdf");
  c1->~TCanvas();


  //
  // Plot of pT for isoTrack that is pfEl
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_isEl_pt");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.6);
  h1->SetTitle("Baseline selection, pT of pfEl that is isoTrack");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("p_{T}");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_isEl_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_isEl_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_isEl_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__pfEl_isIsoTrk_pT.pdf");
  c1->~TCanvas();



  //
  // Plot of the pf Mu absTrkIso for pt>60.0
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_isMu_ptGT30_absIso");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.8);
  h1->SetTitle("Baseline selection, Absolute track isolation, of a pfMu that is an isoTrack and has p_{T}>30.0");
  h1->Draw("hist");
  h1->Rebin(5);
  h1->GetXaxis()->SetTitle("aboslute track iso dr0.3");
  
  leg = new TLegend(0.10, 0.70, 0.60, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_isMu_ptGT30_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_isMu_ptGT30_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_isMu_ptGT30_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__absTrkIso_pfMu_ptGT30.pdf");
  c1->~TCanvas();


  
  //
  // Plot of the pf Mu relTrkIso for values < 0.6
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.6);
  h1->SetTitle("Baseline selection, Relative track isolation, of a pfMu that has passed pT requirement && iso<0.6");
  h1->Draw("hist");
  h1->Rebin(2);
  h1->GetXaxis()->SetTitle("relative track iso dr0.3");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_passPt_isoLT0p6_isMu_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__relTrkIso_pfMu_ptGT5p0_relIsoLT0p6.pdf");
  c1->~TCanvas();


  //
  // Plot of pT for isoTrack that is pfMu
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_isMu_pt");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.6);
  h1->SetTitle("Baseline selection, pT of pfMu that is isoTrack");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("p_{T}");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_isMu_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_isMu_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_isMu_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__pfMu_isIsoTrk_pT.pdf");
  c1->~TCanvas();




  //
  // Plot of the pf Had absTrkIso for pt>60.0
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_isHad_ptGT60_absIso");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(1.0);
  h1->SetTitle("Baseline selection, Absolute track isolation, of a pfHad that is an isoTrack and has p_{T}>60.0");
  h1->Draw("hist");
  h1->Rebin(5);
  h1->GetXaxis()->SetTitle("aboslute track iso dr0.3");
  
  leg = new TLegend(0.1, 0.70, 0.60, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_isHad_ptGT60_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_isHad_ptGT60_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_isHad_ptGT60_absIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(5);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__absTrkIso_pfHad_ptGT60.pdf");
  c1->~TCanvas();


  
  //
  // Plot of pfHad relIso for values <0.6
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.2);
  h1->SetTitle("Baseline selection, Relative track isolation, of a pfHad that has passed pT requirement && iso<0.6");
  h1->Draw("hist");
  h1->Rebin(2);
  h1->GetXaxis()->SetTitle("relative track iso dr0.3");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_passPt_isoLT0p6_isHad_relTrkIso");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(2);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__relTrkIso_pfHad_ptGT5p0_relIsoLT0p6.pdf");
  c1->~TCanvas();


  //
  // Plot of pT for isoTrack that is pfHad
  //
  c1 = new TCanvas("can", "can", 10, 10, 800, 800);
  h1 = (TH1D*)f_ttbar_2l->Get("h_isoTrack_isHad_pt");
  h1->SetLineColor(kBlack);
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetMaximum(0.6);
  h1->SetTitle("Baseline selection, pT of pfHad that is isoTrack");
  h1->Draw("hist");
  h1->Rebin(10);
  h1->GetXaxis()->SetTitle("p_{T}");
  
  leg = new TLegend(0.40, 0.70, 0.90, 0.90);
  leg->SetFillColor(0);
  leg->AddEntry(h1, "ttbar_2l", "l");
  
  h1 = (TH1D*)f_stop_850_100->Get("h_isoTrack_isHad_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kBlue);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 850/100", "l");
  

  h1 = (TH1D*)f_stop_650_325->Get("h_isoTrack_isHad_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kMagenta);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 650/325", "l");
  
  h1 = (TH1D*)f_stop_500_325->Get("h_isoTrack_isHad_pt");
  h1->Scale(1.0/h1->Integral(0,-1));
  h1->SetLineColor(kGreen);
  h1->Draw("hist same");
  h1->Rebin(10);
  
  leg->AddEntry(h1, "stop 500/325", "l");
  leg->SetTextSize(0.020);
  leg->Draw();
  
  c1->SaveAs("Plots/lostLeptonStudies__ttbar2l_vs_signal__pfHad_isIsoTrk_pT.pdf");
  c1->~TCanvas();


  
  //
  // Clean up
  //
  f_ttbar_2l->Close();
  f_stop_850_100->Close();
  f_stop_650_325->Close();
  f_stop_500_325->Close();
}
