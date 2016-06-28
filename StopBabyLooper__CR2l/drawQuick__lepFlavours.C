{

  // To Run: root -l -b -q drawQuick__lepFlavours.C

  // Open Data File
  TFile *f_data = new TFile("Histos/Nominal/h__data_single_lepton_met_2016B_25ns.root", "read");
  TH2D *h_data = (TH2D*)f_data->Get("h2__lep1_vs_secondLepType");
  TCanvas *c_data = new TCanvas("c_data", "c_data",10,10,800,1000);
  h_data->Draw("colz text00");
  c_data->SaveAs("Output/Plots/lepFlavour__data__lep1_vs_lep2Type.pdf");
  c_data->~TCanvas();


  // Open MC File
  TFile *f_mc = new TFile("Histos/Nominal/h__allBkg_25ns.root", "read");
  TH2D *h_mc = (TH2D*)f_mc->Get("h2__lep1_vs_secondLepType");
  TCanvas *c_mc = new TCanvas("c_mc", "c_mc",10,10,800,1000);
  h_mc->Draw("colz text00");
  c_mc->SaveAs("Output/Plots/lepFlavour__mc__lep1_vs_lep2Type.pdf");
  c_mc->~TCanvas();
  


}
