#include "eventWeight_lepSF.h"

//////////////////////////////////////////////////////////////////////

eventWeight_lepSF::eventWeight_lepSF( bool isFastsim ){

  sampleIsFastsim = isFastsim;

  xmin_h_el_SF = 1.0;
  xmax_h_el_SF = 1.0;
  ymin_h_el_SF = 1.0;
  ymax_h_el_SF = 1.0;
  xmin_h_el_SF_veto = 1.0;
  xmax_h_el_SF_veto = 1.0;
  ymin_h_el_SF_veto = 1.0;
  ymax_h_el_SF_veto = 1.0;
  xmin_h_el_SF_tracking = 1.0;
  xmax_h_el_SF_tracking = 1.0;
  ymin_h_el_SF_tracking = 1.0;
  ymax_h_el_SF_tracking = 1.0;
  xmin_h_mu_SF = 1.0;
  xmax_h_mu_SF = 1.0;
  ymin_h_mu_SF = 1.0;
  ymax_h_mu_SF = 1.0;
  xmin_h_mu_SF_tracking = 1.0;
  xmax_h_mu_SF_tracking = 1.0;
  xmin_h_mu_SF_veto = 1.0;
  xmax_h_mu_SF_veto = 1.0;
  ymin_h_mu_SF_veto = 1.0;
  ymax_h_mu_SF_veto = 1.0;
  xmin_h_el_FS = 1.0;
  xmax_h_el_FS = 1.0;
  ymin_h_el_FS = 1.0;
  ymax_h_el_FS = 1.0;
  xmin_h_el_veto_FS = 1.0;
  xmax_h_el_veto_FS = 1.0;
  ymin_h_el_veto_FS = 1.0;
  ymax_h_el_veto_FS = 1.0;
  xmin_h_mu_FS = 1.0;
  xmax_h_mu_FS = 1.0;
  ymin_h_mu_FS = 1.0;
  ymax_h_mu_FS = 1.0;
  xmin_h_mu_veto_FS = 1.0;
  xmax_h_mu_veto_FS = 1.0;
  ymin_h_mu_veto_FS = 1.0;
  ymax_h_mu_veto_FS = 1.0;
  xmin_h_el_vetoLepEff = 1.0;
  xmax_h_el_vetoLepEff = 1.0;
  ymin_h_el_vetoLepEff = 1.0;
  ymax_h_el_vetoLepEff = 1.0;
  xmin_h_mu_vetoLepEff = 1.0;
  xmax_h_mu_vetoLepEff = 1.0;
  ymin_h_mu_vetoLepEff = 1.0;
  ymax_h_mu_vetoLepEff = 1.0;

  cout << "    Loading lepton scale factors..." << endl << endl;
    
  // Electron file
  f_el_SF          = new TFile("../StopCORE/inputs/lepsf/Moriond17/scaleFactors.root", "read");
  f_el_SF_tracking = new TFile("../StopCORE/inputs/lepsf/Moriond17/egammaEffi.txt_EGM2D.root", "read");
    
  // Muon files
  f_mu_SF_id       = new TFile("../StopCORE/inputs/lepsf/Moriond17/TnP_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root", "read"); 
  f_mu_SF_iso      = new TFile("../StopCORE/inputs/lepsf/Moriond17/TnP_NUM_MiniIsoTight_DENOM_MediumID_VAR_map_pt_eta.root", "read"); // double unc
  f_mu_SF_ip       = new TFile("../StopCORE/inputs/lepsf/Moriond17/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root", "read"); // double unc
  f_mu_SF_tracking = new TFile("../StopCORE/inputs/lepsf/Moriond17/Tracking_EfficienciesAndSF_BCDEFGH.root", "read"); 
    
  f_mu_SF_veto_id  = new TFile("../StopCORE/inputs/lepsf/Moriond17/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
  f_mu_SF_veto_iso = new TFile("../StopCORE/inputs/lepsf/Moriond17/TnP_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root", "read");
  f_mu_SF_veto_ip  = new TFile("../StopCORE/inputs/lepsf/Moriond17/TnP_NUM_MediumIP2D_DENOM_LooseID_VAR_map_pt_eta.root", "read"); // double unc for this
    
  // Fastsim/Fullsim el files
  f_el_FS_ID  = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_el_mediumCB.root", "read");
  f_el_FS_Iso = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_el_mini01.root", "read");
    
  f_el_veto_FS_ID  = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_el_vetoCB.root", "read");
  f_el_veto_FS_Iso = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_el_mini02.root", "read"); 
    
  // Fastsim/Fullsim mu files
  f_mu_FS_ID  = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_mu_mediumID.root", "read"); // double unc for this
  f_mu_FS_Iso = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_mu_mediumID_mini02.root", "read"); // double unc for this
  f_mu_FS_Ip  = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_mu_mediumID_tightIP2D.root", "read"); // double unc for this
    
  f_mu_veto_FS_ID  = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_mu_looseID.root", "read");
  f_mu_veto_FS_Iso = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_mu_looseID_mini02.root", "read");
  f_mu_veto_FS_Ip  = new TFile("../StopCORE/inputs/lepsf/Moriond17/sf_mu_mediumID_looseIP2D.root", "read"); // double unc for this

  // Veto lepton reco efficiency files
  f_vetoLep_eff = new TFile("../StopCORE/inputs/lepsf/Moriond17/lepeff__moriond17__ttbar_powheg_pythia8_25ns.root", "read");


  // Grab selected el histos
  TH2D *h_el_SF_id_temp       = (TH2D*)f_el_SF->Get("GsfElectronToCutBasedSpring15M");
  TH2D *h_el_SF_iso_temp      = (TH2D*)f_el_SF->Get("MVAVLooseElectronToMini");
  TH2D *h_el_SF_tracking_temp = (TH2D*)f_el_SF_tracking->Get("EGamma_SF2D");

  // Grab veto el histos
  TH2D *h_el_SF_veto_id_temp  = (TH2D*)f_el_SF->Get("GsfElectronToCutBasedSpring15V");
  TH2D *h_el_SF_veto_iso_temp = (TH2D*)f_el_SF->Get("MVAVLooseElectronToMini2");


  // Grab selected mu histos
  TH2D *h_mu_SF_id_temp  = (TH2D*)f_mu_SF_id->Get("SF");
  TH2D *h_mu_SF_iso_temp = (TH2D*)f_mu_SF_iso->Get("SF");
  TH2D *h_mu_SF_ip_temp  = (TH2D*)f_mu_SF_ip->Get("SF");
  //TGraphAsymmErrors *h_mu_SF_tracking_temp  = (TGraphAsymmErrors*)f_mu_SF_tracking->Get("ratio_eta");
  TGraphAsymmErrors *h_mu_SF_tracking_temp  = (TGraphAsymmErrors*)f_mu_SF_tracking->Get("ratio_eff_aeta_dr030e030_corr");

  // Grab veto mu histos
  TH2D *h_mu_SF_veto_id_temp  = (TH2D*)f_mu_SF_veto_id->Get("SF");
  TH2D *h_mu_SF_veto_iso_temp = (TH2D*)f_mu_SF_veto_iso->Get("SF");
  TH2D *h_mu_SF_veto_ip_temp  = (TH2D*)f_mu_SF_veto_ip->Get("SF");
    

  // Grab fastsim/fullsim selected el histos
  TH2D *h_el_FS_ID_temp  = (TH2D*)f_el_FS_ID->Get("histo2D");
  TH2D *h_el_FS_Iso_temp = (TH2D*)f_el_FS_Iso->Get("histo2D");

  // Grab fastsim/fullsim veto el histos
  TH2D *h_el_veto_FS_ID_temp  = (TH2D*)f_el_veto_FS_ID->Get("histo2D");
  TH2D *h_el_veto_FS_Iso_temp = (TH2D*)f_el_veto_FS_Iso->Get("histo2D");
    
  // Grab fastsim/fullsim selected mu histos
  TH2D *h_mu_FS_ID_temp  = (TH2D*)f_mu_FS_ID->Get("histo2D");
  TH2D *h_mu_FS_Iso_temp = (TH2D*)f_mu_FS_Iso->Get("histo2D");
  TH2D *h_mu_FS_Ip_temp  = (TH2D*)f_mu_FS_Ip->Get("histo2D");
    
  // Grab fastsim/fullsim veto mu histos
  TH2D *h_mu_veto_FS_ID_temp  = (TH2D*)f_mu_veto_FS_ID->Get("histo2D");
  TH2D *h_mu_veto_FS_Iso_temp = (TH2D*)f_mu_veto_FS_Iso->Get("histo2D");
  TH2D *h_mu_veto_FS_Ip_temp  = (TH2D*)f_mu_veto_FS_Ip->Get("histo2D");

    
  // Grab mc eff for veto lepton (for lost lepto SFs) histos
  TH2D *h_el_vetoLepEff_temp = (TH2D*)f_vetoLep_eff->Get("h2_lepEff_vetoSel_Eff_el");
  TH2D *h_mu_vetoLepEff_temp = (TH2D*)f_vetoLep_eff->Get("h2_lepEff_vetoSel_Eff_mu");
   

  // Get final fullsim, selected el, sfs
  TH2D *h_el_SF_id  = (TH2D*)h_el_SF_id_temp->Clone("h_el_SF_id");
  TH2D *h_el_SF_iso = (TH2D*)h_el_SF_iso_temp->Clone("h_el_SF_iso");
  h_el_SF = (TH2D*)h_el_SF_id->Clone("h_el_SF");
  h_el_SF->Multiply(h_el_SF_iso);
  xmin_h_el_SF = h_el_SF->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_el_SF = h_el_SF->GetXaxis()->GetBinLowEdge(h_el_SF->GetNbinsX()+1)-0.01;
  ymin_h_el_SF = h_el_SF->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_el_SF = h_el_SF->GetYaxis()->GetBinLowEdge(h_el_SF->GetNbinsY()+1)-0.01;
    
  // Get final fullsim, selected el, tracking sfs
  h_el_SF_tracking = (TH2D*)h_el_SF_tracking_temp->Clone("h_el_SF_iso");
  xmin_h_el_SF_tracking = h_el_SF_tracking->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_el_SF_tracking = h_el_SF_tracking->GetXaxis()->GetBinLowEdge(h_el_SF_tracking->GetNbinsX()+1)-0.01;
  ymin_h_el_SF_tracking = h_el_SF_tracking->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_el_SF_tracking = h_el_SF_tracking->GetYaxis()->GetBinLowEdge(h_el_SF_tracking->GetNbinsY()+1)-0.01;
    
  // Get final fullsim, veto el, sfs
  TH2D *h_el_SF_veto_id  = (TH2D*)h_el_SF_veto_id_temp->Clone("h_el_SF_veto_id");
  TH2D *h_el_SF_veto_iso = (TH2D*)h_el_SF_veto_iso_temp->Clone("h_el_SF_veto_iso");
  h_el_SF_veto = (TH2D*)h_el_SF_veto_id->Clone("h_el_SF_veto");
  h_el_SF_veto->Multiply(h_el_SF_veto_iso);
  // Double unc. on veto electron sfs, since we go lower in pT
  for(int x=1; x<=(int)h_el_SF_veto->GetNbinsX(); x++){
    for(int y=1; y<=(int)h_el_SF_veto->GetNbinsY(); y++){
      h_el_SF_veto->SetBinError(x,y,h_el_SF_veto->GetBinError(x,y)*2.0);
    }
  }
  xmin_h_el_SF_veto = h_el_SF_veto->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_el_SF_veto = h_el_SF_veto->GetXaxis()->GetBinLowEdge(h_el_SF_veto->GetNbinsX()+1)-0.01;
  ymin_h_el_SF_veto = h_el_SF_veto->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_el_SF_veto = h_el_SF_veto->GetYaxis()->GetBinLowEdge(h_el_SF_veto->GetNbinsY()+1)-0.01;
    
  // Get final fullsim, selected mu, sfs
  TH2D *h_mu_SF_id  = (TH2D*)h_mu_SF_id_temp->Clone("h_mu_SF_id");
  TH2D *h_mu_SF_iso = (TH2D*)h_mu_SF_iso_temp->Clone("h_mu_SF_iso");
  TH2D *h_mu_SF_ip  = (TH2D*)h_mu_SF_ip_temp->Clone("h_mu_SF_ip");
  // Double unc. on selected muon iso sfs, since not for our exact wp
  for(int x=1; x<=(int)h_mu_SF_iso->GetNbinsX(); x++){
    for(int y=1; y<=(int)h_mu_SF_iso->GetNbinsY(); y++){
      h_mu_SF_iso->SetBinError(x,y,h_mu_SF_iso->GetBinError(x,y)*2.0);
    }
  }
  // Double unc. on selected muon ip sfs, since not for our exact wp
  for(int x=1; x<=(int)h_mu_SF_ip->GetNbinsX(); x++){
    for(int y=1; y<=(int)h_mu_SF_ip->GetNbinsY(); y++){
      h_mu_SF_ip->SetBinError(x,y,h_mu_SF_ip->GetBinError(x,y)*2.0);
    }
  }
  h_mu_SF = (TH2D*)h_mu_SF_id->Clone("h_mu_SF");
  h_mu_SF->Multiply(h_mu_SF_iso);
  h_mu_SF->Multiply(h_mu_SF_ip);
  xmin_h_mu_SF = h_mu_SF->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_mu_SF = h_mu_SF->GetXaxis()->GetBinLowEdge(h_mu_SF->GetNbinsX()+1)-0.01;
  ymin_h_mu_SF = h_mu_SF->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_mu_SF = h_mu_SF->GetYaxis()->GetBinLowEdge(h_mu_SF->GetNbinsY()+1)-0.01;

  // Get final fullsim, selected muon, tracking sfs, convert TGraphErrors
  int nX = h_mu_SF_tracking_temp->GetN();
  Double_t *x_val = h_mu_SF_tracking_temp->GetX();
  Double_t *y_val = h_mu_SF_tracking_temp->GetY();
  Double_t *y_err_up = h_mu_SF_tracking_temp->GetEYhigh();
  Double_t *y_err_low = h_mu_SF_tracking_temp->GetEYhigh();
  h_mu_SF_tracking = new TH1D("h_mu_SF_tracking","h_mu_SF_tracking",nX-1,x_val);
  for(int i=0; i<nX; i++){
    h_mu_SF_tracking->SetBinContent(i+1,y_val[i]);
    h_mu_SF_tracking->SetBinError(i+1,std::max(y_err_up[i],y_err_low[i]));
  }
  xmin_h_mu_SF_tracking = h_mu_SF_tracking->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_mu_SF_tracking = h_mu_SF_tracking->GetXaxis()->GetBinLowEdge(h_mu_SF_tracking->GetNbinsX()+1)-0.01;
  //float ymin_h_mu_SF_tracking = h_mu_SF_tracking->GetYaxis()->GetBinLowEdge(1)+0.01;
  //float ymax_h_mu_SF_tracking = h_mu_SF_tracking->GetYaxis()->GetBinLowEdge(h_mu_SF_tracking->GetNbinsY()+1)-0.01;
 

  // Get final fullsim, veto mu, sfs
  TH2D *h_mu_SF_veto_id  = (TH2D*)h_mu_SF_veto_id_temp->Clone("h_mu_SF_veto_id");
  TH2D *h_mu_SF_veto_iso = (TH2D*)h_mu_SF_veto_iso_temp->Clone("h_mu_SF_veto_iso");
  TH2D *h_mu_SF_veto_ip  = (TH2D*)h_mu_SF_veto_ip_temp->Clone("h_mu_SF_veto_ip");
  // Double unc. on veto muon ip sfs, since not for our exact wp
  for(int x=1; x<=(int)h_mu_SF_veto_ip->GetNbinsX(); x++){
    for(int y=1; y<=(int)h_mu_SF_veto_ip->GetNbinsY(); y++){
      h_mu_SF_ip->SetBinError(x,y,h_mu_SF_veto_ip->GetBinError(x,y)*2.0);
    }
  }
  h_mu_SF_veto = (TH2D*)h_mu_SF_veto_id->Clone("h_mu_SF_veto");
  h_mu_SF_veto->Multiply(h_mu_SF_veto_iso);
  h_mu_SF_veto->Multiply(h_mu_SF_veto_ip);
  xmin_h_mu_SF_veto = h_mu_SF_veto->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_mu_SF_veto = h_mu_SF_veto->GetXaxis()->GetBinLowEdge(h_mu_SF_veto->GetNbinsX()+1)-0.01;
  ymin_h_mu_SF_veto = h_mu_SF_veto->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_mu_SF_veto = h_mu_SF_veto->GetYaxis()->GetBinLowEdge(h_mu_SF_veto->GetNbinsY()+1)-0.01;


  // Get final fullsim/fastsim, selected el, sfs
  TH2D* h_el_FS_ID  = (TH2D*)h_el_FS_ID_temp->Clone("h_el_FS_ID");
  TH2D* h_el_FS_Iso = (TH2D*)h_el_FS_Iso_temp->Clone("h_el_FS_Iso");
  h_el_FS = (TH2D*)h_el_FS_ID->Clone("h_el_FS");
  h_el_FS->Multiply(h_el_FS_Iso);
  xmin_h_el_FS = h_el_FS->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_el_FS = h_el_FS->GetXaxis()->GetBinLowEdge(h_el_FS->GetNbinsX()+1)-0.01;
  ymin_h_el_FS = h_el_FS->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_el_FS = h_el_FS->GetYaxis()->GetBinLowEdge(h_el_FS->GetNbinsY()+1)-0.01;

  // Get final fullsim/fastsim, veto el, sfs
  TH2D* h_el_veto_FS_ID  = (TH2D*)h_el_veto_FS_ID_temp->Clone("h_el_veto_FS_ID");
  TH2D* h_el_veto_FS_Iso = (TH2D*)h_el_veto_FS_Iso_temp->Clone("h_el_veto_FS_Iso");
  h_el_veto_FS = (TH2D*)h_el_veto_FS_ID->Clone("h_el_FS");
  h_el_veto_FS->Multiply(h_el_veto_FS_Iso);
  xmin_h_el_veto_FS = h_el_veto_FS->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_el_veto_FS = h_el_veto_FS->GetXaxis()->GetBinLowEdge(h_el_veto_FS->GetNbinsX()+1)-0.01;
  ymin_h_el_veto_FS = h_el_veto_FS->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_el_veto_FS = h_el_veto_FS->GetYaxis()->GetBinLowEdge(h_el_veto_FS->GetNbinsY()+1)-0.01;
  
  // Get final fullsim/fastsim, selected mu, sfs
  TH2D* h_mu_FS_ID  = (TH2D*)h_mu_FS_ID_temp->Clone("h_mu_FS_ID");
  TH2D* h_mu_FS_Iso = (TH2D*)h_mu_FS_Iso_temp->Clone("h_mu_FS_Iso");
  TH2D* h_mu_FS_Ip  = (TH2D*)h_mu_FS_Ip_temp->Clone("h_mu_FS_Ip");
  // Double unc. on selected muon FS iso sfs, since not for our exact wp
  for(int x=1; x<=(int)h_mu_FS_Iso->GetNbinsX(); x++){
    for(int y=1; y<=(int)h_mu_FS_Iso->GetNbinsY(); y++){
      h_mu_FS_Iso->SetBinError(x,y,h_mu_FS_Iso->GetBinError(x,y)*2.0);
    }
  }
  // Double unc. on selected muon FS ip sfs, since not for our exact wp
  for(int x=1; x<=(int)h_mu_FS_Ip->GetNbinsX(); x++){
    for(int y=1; y<=(int)h_mu_FS_Ip->GetNbinsY(); y++){
      h_mu_FS_Ip->SetBinError(x,y,h_mu_FS_Ip->GetBinError(x,y)*2.0);
    }
  }
  h_mu_FS = (TH2D*)h_mu_FS_ID->Clone("h_mu_FS");
  h_mu_FS->Multiply(h_mu_FS_Iso);
  h_mu_FS->Multiply(h_mu_FS_Ip);
  xmin_h_mu_FS = h_mu_FS->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_mu_FS = h_mu_FS->GetXaxis()->GetBinLowEdge(h_mu_FS->GetNbinsX()+1)-0.01;
  ymin_h_mu_FS = h_mu_FS->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_mu_FS = h_mu_FS->GetYaxis()->GetBinLowEdge(h_mu_FS->GetNbinsY()+1)-0.01;
    
  // Get final fullsim/fastsim, veto mu, sfs
  TH2D* h_mu_veto_FS_ID  = (TH2D*)h_mu_veto_FS_ID_temp->Clone("h_mu_veto_FS_ID");
  TH2D* h_mu_veto_FS_Iso = (TH2D*)h_mu_veto_FS_Iso_temp->Clone("h_mu_veto_FS_Iso");
  TH2D* h_mu_veto_FS_Ip  = (TH2D*)h_mu_veto_FS_Ip_temp->Clone("h_mu_veto_FS_Ip");
  // Double unc. on selected muon FS ip sfs, since not for our exact wp
  for(int x=1; x<=(int)h_mu_veto_FS_Ip->GetNbinsX(); x++){
    for(int y=1; y<=(int)h_mu_veto_FS_Ip->GetNbinsY(); y++){
      h_mu_veto_FS_Ip->SetBinError(x,y,h_mu_veto_FS_Ip->GetBinError(x,y)*2.0);
    }
  }
  h_mu_veto_FS = (TH2D*)h_mu_veto_FS_ID->Clone("h_mu_veto_FS");
  h_mu_veto_FS->Multiply(h_mu_veto_FS_Iso);
  h_mu_veto_FS->Multiply(h_mu_veto_FS_Ip);
  xmin_h_mu_veto_FS = h_mu_veto_FS->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_mu_veto_FS = h_mu_veto_FS->GetXaxis()->GetBinLowEdge(h_mu_veto_FS->GetNbinsX()+1)-0.01;
  ymin_h_mu_veto_FS = h_mu_veto_FS->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_mu_veto_FS = h_mu_veto_FS->GetYaxis()->GetBinLowEdge(h_mu_veto_FS->GetNbinsY()+1)-0.01;


  // Lepton efficiencies for Lost Leptons
  h_el_vetoLepEff = (TH2D*)h_el_vetoLepEff_temp->Clone("h_el_vetoLepEff");
  h_mu_vetoLepEff = (TH2D*)h_mu_vetoLepEff_temp->Clone("h_mu_vetoLepEff");
  xmin_h_el_vetoLepEff = h_el_vetoLepEff->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_el_vetoLepEff = h_el_vetoLepEff->GetXaxis()->GetBinLowEdge(h_el_vetoLepEff->GetNbinsX()+1)-0.01;
  ymin_h_el_vetoLepEff = h_el_vetoLepEff->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_el_vetoLepEff = h_el_vetoLepEff->GetYaxis()->GetBinLowEdge(h_el_vetoLepEff->GetNbinsY()+1)-0.01;
  xmin_h_mu_vetoLepEff = h_mu_vetoLepEff->GetXaxis()->GetBinLowEdge(1)+0.01;
  xmax_h_mu_vetoLepEff = h_mu_vetoLepEff->GetXaxis()->GetBinLowEdge(h_mu_vetoLepEff->GetNbinsX()+1)-0.01;
  ymin_h_mu_vetoLepEff = h_mu_vetoLepEff->GetYaxis()->GetBinLowEdge(1)+0.01;
  ymax_h_mu_vetoLepEff = h_mu_vetoLepEff->GetYaxis()->GetBinLowEdge(h_mu_vetoLepEff->GetNbinsY()+1)-0.01;
  
  
}

//////////////////////////////////////////////////////////////////////

eventWeight_lepSF::~eventWeight_lepSF(){

  // Fullsim Electron file
  f_el_SF->Close();
  f_el_SF_tracking->Close();

  // Fullsim Muon files
  f_mu_SF_id->Close();
  f_mu_SF_iso->Close();
  f_mu_SF_ip->Close();
  f_mu_SF_tracking->Close();
  f_mu_SF_veto_id->Close();
  f_mu_SF_veto_iso->Close();
  f_mu_SF_veto_ip->Close();

  // Fullsim/Fastsim Electron files
  f_el_FS_ID->Close();
  f_el_FS_Iso->Close();
  f_el_veto_FS_ID->Close();
  f_el_veto_FS_Iso->Close();

  // Fullsim/Fastsim Muon files
  f_mu_FS_ID->Close();
  f_mu_FS_Iso->Close();
  f_mu_FS_Ip->Close();
  f_mu_veto_FS_ID->Close();
  f_mu_veto_FS_Iso->Close();
  f_mu_veto_FS_Ip->Close();

  // Lepton MC reco efficiency for veto lep IDs
  f_vetoLep_eff->Close();

}

//////////////////////////////////////////////////////////////////////

void eventWeight_lepSF::getLepWeight( std::vector< double > recoLep_pt, std::vector< double > recoLep_eta, std::vector< int > recoLep_pdgid, std::vector< bool > recoLep_isSel, std::vector< double > genLostLep_pt, std::vector< double > genLostLep_eta, std::vector< int > genLostLep_pdgid, double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepSF_FS, double &weight_lepSF_FS_Up, double &weight_lepSF_FS_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn ){

  weight_lepSF        = 1.0;
  weight_lepSF_Up     = 1.0;
  weight_lepSF_Dn     = 1.0;
  weight_lepSF_FS     = 1.0;
  weight_lepSF_FS_Up  = 1.0;
  weight_lepSF_FS_Dn  = 1.0;
  weight_vetoLepSF    = 1.0;
  weight_vetoLepSF_Up = 1.0;
  weight_vetoLepSF_Dn = 1.0;

  // Input sanitation
  if( (int)recoLep_pt.size()!= (int)recoLep_eta.size() ){
    std::cout << "lep sf vectors for lep pt, eta are different sizes, exiting..." << std::endl;
    return;
  }
  if( (int)recoLep_eta.size()!= (int)recoLep_pdgid.size() ){
    std::cout << "lep sf vectors for lep eta, pdgid are different sizes, exiting..." << std::endl;
    return;
  }

  if( (int)genLostLep_pt.size()!= (int)genLostLep_eta.size() ){
    std::cout << "lep sf vectors for lep pt, eta are different sizes, exiting..." << std::endl;
    return;
  }
  if( (int)genLostLep_eta.size()!= (int)genLostLep_pdgid.size() ){
    std::cout << "lep sf vectors for lep eta, pdgid are different sizes, exiting..." << std::endl;
    return;
  }


  // Reco Lepton Scale Factors
  int binX = -99;
  int binY = -99;
  for(int iLep=0; iLep<(int)recoLep_pt.size(); iLep++){

    if(abs(recoLep_pdgid[iLep]) == 11){

      if(recoLep_isSel[iLep]){
	
	int binX = h_el_SF->GetXaxis()->FindBin( std::max( std::min(xmax_h_el_SF, (float)recoLep_pt[iLep] ), xmin_h_el_SF ) );
	int binY = h_el_SF->GetYaxis()->FindBin( std::max( std::min(ymax_h_el_SF, (float)recoLep_eta[iLep]), ymin_h_el_SF ) );
	weight_lepSF    *= h_el_SF->GetBinContent( binX, binY );
	weight_lepSF_Up *= ( weight_lepSF + h_el_SF->GetBinError( binX, binY ) );
	weight_lepSF_Dn *= ( weight_lepSF - h_el_SF->GetBinError( binX, binY ) );
	    
	if(sampleIsFastsim){
	  int bin_FS  = h_el_FS->FindBin( std::max( std::min(xmax_h_el_FS, (float)recoLep_pt[iLep]), xmin_h_el_FS ), std::max( std::min(ymax_h_el_FS, float(fabs(recoLep_eta[iLep])) ), ymin_h_el_FS ) );
	  weight_lepSF_FS    *= h_el_FS->GetBinContent(bin_FS);
	  weight_lepSF_FS_Up *= (weight_lepSF_FS + h_el_FS->GetBinError(bin_FS));
	  weight_lepSF_FS_Dn *= (weight_lepSF_FS - h_el_FS->GetBinError(bin_FS));
	}
      } // end if is selected lepton
      else{
	int binX = h_el_SF_veto->GetXaxis()->FindBin( std::max( std::min(xmax_h_el_SF_veto, (float)recoLep_pt[iLep]), xmin_h_el_SF_veto ) );
	int binY = h_el_SF_veto->GetYaxis()->FindBin( std::max( std::min(ymax_h_el_SF_veto, float(fabs(recoLep_eta[iLep])) ), ymin_h_el_SF_veto ) );
	weight_lepSF    *= h_el_SF_veto->GetBinContent( binX, binY );
	weight_lepSF_Up *= ( weight_lepSF + h_el_SF_veto->GetBinError( binX, binY ) );
	weight_lepSF_Dn *= ( weight_lepSF - h_el_SF_veto->GetBinError( binX, binY ) );
	
	if(sampleIsFastsim){
	  int bin_FS  = h_el_veto_FS->FindBin( std::max( std::min(xmax_h_el_veto_FS, (float)recoLep_pt[iLep]), xmin_h_el_veto_FS ), std::max( std::min(ymax_h_el_veto_FS,float(fabs(recoLep_eta[iLep])) ),ymin_h_el_veto_FS ) );
	  weight_lepSF_FS    *= h_el_veto_FS->GetBinContent(bin_FS);
	  weight_lepSF_FS_Up *= (weight_lepSF_FS + h_el_veto_FS->GetBinError(bin_FS));
	  weight_lepSF_FS_Dn *= (weight_lepSF_FS - h_el_veto_FS->GetBinError(bin_FS));
	}
      }
	  
      int binX = h_el_SF_tracking->GetXaxis()->FindBin( std::max( std::min(xmax_h_el_SF_tracking, float(fabs(recoLep_eta[iLep])) ),xmin_h_el_SF_tracking) );
      int binY = h_el_SF_tracking->GetYaxis()->FindBin( std::max( std::min(ymax_h_el_SF_tracking,(float)recoLep_pt[iLep]), ymin_h_el_SF_tracking ) );
      weight_lepSF *= h_el_SF_tracking->GetBinContent( binX, binY );
      weight_lepSF_Up *= ( h_el_SF_tracking->GetBinContent(binX,binY) + h_el_SF_tracking->GetBinError(binX,binY) );
      weight_lepSF_Dn *= ( h_el_SF_tracking->GetBinContent(binX,binY) - h_el_SF_tracking->GetBinError(binX,binY) );
      
    } // end if 2nd lep if el
    
    
    if(abs(recoLep_pdgid[iLep]) == 13){

      if(recoLep_isSel[iLep]){
	int binX = h_mu_SF->GetXaxis()->FindBin( std::max( std::min(xmax_h_mu_SF, (float)recoLep_pt[iLep]), xmin_h_mu_SF ) );
	int binY = h_mu_SF->GetYaxis()->FindBin( std::max( std::min(ymax_h_mu_SF, float(fabs(recoLep_eta[iLep])) ), ymin_h_mu_SF ) );
	weight_lepSF    *= h_mu_SF->GetBinContent( binX, binY );
	weight_lepSF_Up *= ( weight_lepSF + h_mu_SF->GetBinError( binX, binY ) );
	weight_lepSF_Dn *= ( weight_lepSF - h_mu_SF->GetBinError( binX, binY ) );
	    
	if(sampleIsFastsim){
	  int bin_FS  = h_mu_FS->FindBin( std::max( std::min(xmax_h_mu_FS, (float)recoLep_pt[iLep]), xmin_h_mu_FS ), std::max( std::min(ymax_h_mu_FS, float(fabs(recoLep_eta[iLep]) )), ymin_h_mu_FS ) );
	  weight_lepSF_FS    *= h_mu_FS->GetBinContent(bin_FS);
	  weight_lepSF_FS_Up *= weight_lepSF_FS + h_mu_FS->GetBinError(bin_FS);
	  weight_lepSF_FS_Dn *= weight_lepSF_FS - h_mu_FS->GetBinError(bin_FS);
	}
      } // end if selected lepton
	  
      else{
	int binX = h_mu_SF_veto->GetXaxis()->FindBin( std::max( std::min(xmax_h_mu_SF_veto, (float)recoLep_pt[iLep]), xmin_h_mu_SF_veto ) );
	int binY = h_mu_SF_veto->GetYaxis()->FindBin( std::max( std::min(ymax_h_mu_SF_veto, float(fabs(recoLep_eta[iLep]))), ymin_h_mu_SF_veto ) );
	weight_lepSF    *= h_mu_SF_veto->GetBinContent( binX, binY );
	weight_lepSF_Up *= ( weight_lepSF + h_mu_SF_veto->GetBinError( binX, binY ) );
	weight_lepSF_Dn *= ( weight_lepSF - h_mu_SF_veto->GetBinError( binX, binY ) );
	    
	if(sampleIsFastsim){
	  int bin_FS  = h_mu_veto_FS->FindBin( std::max( std::min(xmax_h_mu_veto_FS, (float)recoLep_pt[iLep]), xmin_h_mu_veto_FS ), std::max( std::min(ymax_h_mu_veto_FS, float(fabs(recoLep_eta[iLep]))), ymin_h_mu_veto_FS ) );
	  weight_lepSF_FS    *= h_mu_veto_FS->GetBinContent(bin_FS);
	  weight_lepSF_FS_Up *= weight_lepSF_FS + h_mu_veto_FS->GetBinError(bin_FS);
	  weight_lepSF_FS_Dn *= weight_lepSF_FS - h_mu_veto_FS->GetBinError(bin_FS);
	}
      }
    	
      int binX = h_mu_SF_tracking->GetXaxis()->FindBin( std::max( std::min(xmax_h_mu_SF_tracking,(float)recoLep_eta[iLep]), xmin_h_mu_SF_tracking ) );
      weight_lepSF *= h_mu_SF_tracking->GetBinContent( binX );
      weight_lepSF_Up *= ( h_mu_SF_tracking->GetBinContent(binX) + h_mu_SF_tracking->GetBinError(binX) );
      weight_lepSF_Dn *= ( h_mu_SF_tracking->GetBinContent(binX) - h_mu_SF_tracking->GetBinError(binX) );
      
    } // end if 2nd lep is mu

  } // end loop over reco leptons
        
  
  if(sampleIsFastsim) return;
  if( (int)genLostLep_pt.size()==0 ) return;
  
  // GenLostLepton scale factors
  binX = -99;
  binY = -99;
  for(int iLep=0; iLep<(int)genLostLep_pt.size(); iLep++){
    
    if( abs(genLostLep_pdgid[iLep])!=11 &&
	abs(genLostLep_pdgid[iLep])!=13    ) continue;
    if( genLostLep_pt[iLep] <= 5.0 ) continue;
    if( fabs(genLostLep_eta[iLep]) >= 2.4 ) continue;
    
    // Gen Lost Electron
    if( abs(genLostLep_pdgid[iLep])==11 ){
      
      binX = h_el_vetoLepEff->GetXaxis()->FindBin( std::max( std::min(xmax_h_el_vetoLepEff, (float)genLostLep_pt[iLep]), xmin_h_el_vetoLepEff ) );
      binY = h_el_vetoLepEff->GetYaxis()->FindBin( std::max( std::min(ymax_h_el_vetoLepEff, float(fabs(genLostLep_eta[iLep]))), ymin_h_el_vetoLepEff ) );
      double vetoEff = h_el_vetoLepEff->GetBinContent( binX, binY );
      
      binX = h_el_SF_veto->GetXaxis()->FindBin( std::max( std::min(xmax_h_el_SF_veto, (float)genLostLep_pt[iLep]), xmin_h_el_SF_veto ) );
      binY = h_el_SF_veto->GetYaxis()->FindBin( std::max( std::min(ymax_h_el_SF_veto, float(fabs(genLostLep_eta[iLep]))), ymin_h_el_SF_veto ) );
      double vetoLepSF_temp    = h_el_SF_veto->GetBinContent( binX, binY );
      double vetoLepSF_temp_Up = (vetoLepSF_temp + h_el_SF_veto->GetBinError(binX, binY));
      double vetoLepSF_temp_Dn = (vetoLepSF_temp - h_el_SF_veto->GetBinError(binX, binY));
      
      if( (1-vetoEff)>0.0 ){
	weight_vetoLepSF    *= ( 1-(vetoEff*vetoLepSF_temp) )/( 1-vetoEff );
	weight_vetoLepSF_Up *= ( 1-(vetoEff*vetoLepSF_temp_Up) )/( 1-vetoEff );
	weight_vetoLepSF_Dn *= ( 1-(vetoEff*vetoLepSF_temp_Dn) )/( 1-vetoEff );	    
      }
      else{
	weight_vetoLepSF    *= 1.0;
	weight_vetoLepSF_Up *= 1.0;
	weight_vetoLepSF_Dn *= 1.0;
      }
      
    } // end if genLostLepton is electron
    
    
    // Gen Lost Muon
    if( abs(genLostLep_pdgid[iLep])==13 ){
      
      binX = h_mu_vetoLepEff->GetXaxis()->FindBin( std::max( std::min(xmax_h_mu_vetoLepEff, (float)genLostLep_pt[iLep]), xmin_h_mu_vetoLepEff ) );
      binY = h_mu_vetoLepEff->GetYaxis()->FindBin( std::max( std::min(ymax_h_mu_vetoLepEff, float(fabs(genLostLep_eta[iLep]))), ymin_h_mu_vetoLepEff ) );
      double vetoEff = h_mu_vetoLepEff->GetBinContent( binX, binY );
      
      binX = h_mu_SF_veto->GetXaxis()->FindBin( std::max( std::min(xmax_h_mu_SF_veto, (float)genLostLep_pt[iLep]), xmin_h_mu_SF_veto ) );
      binY = h_mu_SF_veto->GetYaxis()->FindBin( std::max( std::min(ymax_h_mu_SF_veto, float(fabs(genLostLep_eta[iLep]))), ymin_h_mu_SF_veto ) );
      double vetoLepSF_temp    = h_mu_SF_veto->GetBinContent( binX, binY );
      double vetoLepSF_temp_Up = (vetoLepSF_temp + h_mu_SF_veto->GetBinError(binX, binY));
      double vetoLepSF_temp_Dn = (vetoLepSF_temp - h_mu_SF_veto->GetBinError(binX, binY));
      
      if( (1-vetoEff)>0.0 ){
	weight_vetoLepSF    *= ( 1-(vetoEff*vetoLepSF_temp) )/( 1-vetoEff );
	weight_vetoLepSF_Up *= ( 1-(vetoEff*vetoLepSF_temp_Up) )/( 1-vetoEff );
	weight_vetoLepSF_Dn *= ( 1-(vetoEff*vetoLepSF_temp_Dn) )/( 1-vetoEff );	    
      }
      else{
	weight_vetoLepSF    *= 1.0;
	weight_vetoLepSF_Up *= 1.0;
	weight_vetoLepSF_Dn *= 1.0;
      }

    } // end if genLostLepton is muon



  } // end loop over genLostLeptons
    


  return;
}

//////////////////////////////////////////////////////////////////////
