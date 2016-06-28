{

  // To Run: root -l -b -q drawQuick__lepInfo.C

  // Open Data File
  TFile *f_data = new TFile("Histos/Nominal/h__data_single_lepton_met_2016B_25ns.root", "read");
  TH2D *h_data = (TH2D*)f_data->Get("h1__recoLep_pt_type");
  h_data->SetLineColor(kBlue);
  h_data->SetStats(0);

  
  // Open MC File
  TFile *f_mc = new TFile("Histos/Nominal/h__allBkg_25ns.root", "read");
  TH2D *h_mc = (TH2D*)f_mc->Get("h1__recoLep_pt_type");
  h_mc->SetLineColor(kRed);
  h_mc->SetStats(0);

  TCanvas *can = new TCanvas("can", "can",10,10,800,1000);
  h_mc->Draw("hist text00");
  h_data->Draw("hist text00 same");

  TLegend *leg = new TLegend( 0.15, 0.75, 0.35, 0.90 );
  leg->AddEntry(h_mc, "MC", "l");
  leg->AddEntry(h_data, "Data", "l");
  leg->Draw();

  h_mc->SetTitle("Data vs MC, lepton flavour by pT bin");

  can->SaveAs("Output/Plots/lepton_flavour_and_pt.pdf");
  can->~TCanvas();
  


}
