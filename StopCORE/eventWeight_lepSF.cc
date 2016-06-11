#include "eventWeight_lepSF.h"

//////////////////////////////////////////////////////////////////////

eventWeight_lepSF::eventWeight_lepSF( bool isFastsim ){

  sampleIsFastsim = isFastsim;

  // Load Files
  f_el_SF          = new TFile("../StopCORE/inputs/lepsf/kinematicBinSFele.root", "read");
  f_mu_SF_id       = new TFile("../StopCORE/inputs/lepsf/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
  f_mu_SF_iso      = new TFile("../StopCORE/inputs/lepsf/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");
  
  f_mu_SF_veto_id  = new TFile("../StopCORE/inputs/lepsf/TnP_MuonID_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
  f_mu_SF_veto_iso = new TFile("../StopCORE/inputs/lepsf/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");
  
  f_vetoLep_eff    = new TFile("../StopCORE/inputs/lepsf/lepeff__ttbar_powheg_pythia8_25ns__SRcuts.root", "read");

  std::cout << "    Loaded lepton SFs" << std::endl;
  std::cout << std::endl;

  
  TH2D *h_el_SF_id_temp       = (TH2D*)f_el_SF->Get("CutBasedMedium");
  TH2D *h_el_SF_iso_temp      = (TH2D*)f_el_SF->Get("MiniIso0p1_vs_AbsEta");
  TH2D *h_el_SF_veto_id_temp  = (TH2D*)f_el_SF->Get("CutBasedVeto");
  TH2D *h_el_SF_veto_iso_temp = (TH2D*)f_el_SF->Get("MiniIso0p4_vs_AbsEta");
  TH2D *h_mu_SF_id_temp       = (TH2D*)f_mu_SF_id->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
  TH2D *h_mu_SF_iso_temp      = (TH2D*)f_mu_SF_iso->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");
  TH2D *h_mu_SF_veto_id_temp  = (TH2D*)f_mu_SF_veto_id->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
  TH2D *h_mu_SF_veto_iso_temp = (TH2D*)f_mu_SF_veto_iso->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");
  TH2D *h_el_vetoLepEff_temp  = (TH2D*)f_vetoLep_eff->Get("h2_lepEff_vetoSel_rebin_Eff_el");
  TH2D *h_mu_vetoLepEff_temp  = (TH2D*)f_vetoLep_eff->Get("h2_lepEff_vetoSel_rebin_Eff_mu");
    
  TH2D *h_el_SF_id       = (TH2D*)h_el_SF_id_temp->Clone("h_el_SF_id");
  TH2D *h_el_SF_iso      = (TH2D*)h_el_SF_iso_temp->Clone("h_el_SF_iso");
  TH2D *h_mu_SF_id       = (TH2D*)h_mu_SF_id_temp->Clone("h_mu_SF_id");
  TH2D *h_mu_SF_iso      = (TH2D*)h_mu_SF_iso_temp->Clone("h_mu_SF_iso");
  TH2D *h_el_SF_veto_id  = (TH2D*)h_el_SF_veto_id_temp->Clone("h_el_SF_veto_id");
  TH2D *h_el_SF_veto_iso = (TH2D*)h_el_SF_veto_iso_temp->Clone("h_el_SF_veto_iso");
  TH2D *h_mu_SF_veto_id  = (TH2D*)h_mu_SF_veto_id_temp->Clone("h_mu_SF_veto_id");
  TH2D *h_mu_SF_veto_iso = (TH2D*)h_mu_SF_veto_iso_temp->Clone("h_mu_SF_veto_iso");
  
  h_el_vetoLepEff = (TH2D*)h_el_vetoLepEff_temp->Clone("h_el_vetoLepEff");
  h_mu_vetoLepEff = (TH2D*)h_mu_vetoLepEff_temp->Clone("h_mu_vetoLepEff");
  
  h_el_SF = (TH2D*)h_el_SF_id->Clone("h_el_SF");
  h_el_SF->Multiply(h_el_SF_iso);
  
  h_el_SF_veto = (TH2D*)h_el_SF_veto_id->Clone("h_el_SF_veto");
  h_el_SF_veto->Multiply(h_el_SF_veto_iso);
  
  h_mu_SF = (TH2D*)h_mu_SF_id->Clone("h_mu_SF");
  h_mu_SF->Multiply(h_mu_SF_iso);
  
  h_mu_SF_veto = (TH2D*)h_mu_SF_veto_id->Clone("h_mu_SF_veto");
  h_mu_SF_veto->Multiply(h_mu_SF_veto_iso);


  if( sampleIsFastsim ){

    f_el_FS_ID  = new TFile("../StopCORE/inputs/lepsf/sf_el_mediumCB.root", "read");
    f_el_FS_Iso = new TFile("../StopCORE/inputs/lepsf/sf_el_mini01.root", "read");
    f_mu_FS_ID  = new TFile("../StopCORE/inputs/lepsf/sf_mu_mediumID.root", "read");
    f_mu_FS_Iso = new TFile("../StopCORE/inputs/lepsf/sf_mu_mini02.root", "read");

    std::cout << "    Loaded fastsim lepton SFs" << std::endl;
    std::cout << std::endl;
    
    TH2D *h_el_FS_ID_temp  = (TH2D*)f_el_FS_ID->Get("histo2D");
    TH2D *h_el_FS_Iso_temp = (TH2D*)f_el_FS_Iso->Get("histo2D");
    TH2D *h_mu_FS_ID_temp  = (TH2D*)f_mu_FS_ID->Get("histo2D");
    TH2D *h_mu_FS_Iso_temp = (TH2D*)f_mu_FS_Iso->Get("histo2D");
    
    h_el_FS = (TH2D*)h_el_FS_ID_temp->Clone("h_el_FS");
    h_el_FS->Multiply(h_el_FS_Iso_temp);
    
    h_mu_FS = (TH2D*)h_mu_FS_ID_temp->Clone("h_mu_FS");
    h_mu_FS->Multiply(h_mu_FS_Iso_temp);
  } // end if isFastsim
  
  
}

//////////////////////////////////////////////////////////////////////

eventWeight_lepSF::~eventWeight_lepSF(){

  f_el_SF->Close();
  f_mu_SF_id->Close();
  f_mu_SF_iso->Close();
  f_mu_SF_veto_id->Close();
  f_mu_SF_veto_iso->Close();
  f_vetoLep_eff->Close();
  
  if( sampleIsFastsim ){
    f_el_FS_ID->Close();
    f_el_FS_Iso->Close();
    f_mu_FS_ID->Close();
    f_mu_FS_Iso->Close();
  } // end if isFastsim
      
}

//////////////////////////////////////////////////////////////////////

void eventWeight_lepSF::getLepWeight( std::vector< double > recoLep_pt, std::vector< double > recoLep_eta, std::vector< int > recoLep_pdgid, std::vector< bool > recoLep_isSel, std::vector< double > genLostLep_pt, std::vector< double > genLostLep_eta, std::vector< int > genLostLep_pdgid, double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepFSSF, double &weight_lepFSSF_Up, double &weight_lepFSSF_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn ){

  double lepSF_pt_cutoff    = 100.0;
  double lepSF_pt_min       = 10.0;

  double lepSF_FS_pt_cutoff = 100.0;
  //double lepSF_FS_pt_min    = 10.0;

  weight_lepSF        = 1.0;
  weight_lepSF_Up     = 1.0;
  weight_lepSF_Dn     = 1.0;
  weight_lepFSSF      = 1.0;
  weight_lepFSSF_Up   = 1.0;
  weight_lepFSSF_Dn   = 1.0;
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

    // Reco Electron SFs
    if( abs(recoLep_pdgid[iLep])==11 ){

      if( recoLep_isSel[iLep] ){
	binX = h_el_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, recoLep_pt[iLep]) );
	binY = h_el_SF->GetYaxis()->FindBin( fabs(recoLep_eta[iLep]) );
	double tmp_lepSF = h_el_SF->GetBinContent(binX, binY);
	weight_lepSF    *= tmp_lepSF;
	weight_lepSF_Up *= ( tmp_lepSF + h_el_SF->GetBinError(binX, binY) );
	weight_lepSF_Dn *= ( tmp_lepSF - h_el_SF->GetBinError(binX, binY) );
      }
      else{
	binX = h_el_SF_veto->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, recoLep_pt[iLep]) );
	binY = h_el_SF_veto->GetYaxis()->FindBin( fabs(recoLep_eta[iLep]) );
	double tmp_lepSF = h_el_SF_veto->GetBinContent(binX, binY);
	weight_lepSF    *= tmp_lepSF;
	weight_lepSF_Up *= ( tmp_lepSF + h_el_SF_veto->GetBinError(binX, binY) );
	weight_lepSF_Dn *= ( tmp_lepSF - h_el_SF_veto->GetBinError(binX, binY) );
      }

      // If Fastsim
      if( sampleIsFastsim){
	binX = h_el_FS->GetXaxis()->FindBin( std::min(lepSF_FS_pt_cutoff, recoLep_pt[iLep]) );
	binY = h_el_FS->GetYaxis()->FindBin( fabs(recoLep_eta[iLep]) );
	double tmp_lepFSSF = h_el_FS->GetBinContent(binX, binY);
	weight_lepFSSF     *= tmp_lepFSSF;
	weight_lepFSSF_Up  *= ( tmp_lepFSSF + h_el_FS->GetBinContent(binX, binY) );
	weight_lepFSSF_Dn  *= ( tmp_lepFSSF - h_el_FS->GetBinContent(binX, binY) );
      } // end if isFastSim

    } // end if electron


    // Reco Muon SFs
    if( abs(recoLep_pdgid[iLep])==13 ){

      if( recoLep_isSel[iLep] ){
	binX = h_mu_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, recoLep_pt[iLep]) );
	binY = h_mu_SF->GetYaxis()->FindBin( fabs(recoLep_eta[iLep]) );
	double tmp_lepSF = h_mu_SF->GetBinContent(binX, binY);
	weight_lepSF    *= tmp_lepSF;
	weight_lepSF_Up *= ( tmp_lepSF + h_mu_SF->GetBinError(binX, binY) );
	weight_lepSF_Dn *= ( tmp_lepSF - h_mu_SF->GetBinError(binX, binY) );
      }
      else{
	binX = h_mu_SF_veto->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, recoLep_pt[iLep]) );
	binY = h_mu_SF_veto->GetYaxis()->FindBin( fabs(recoLep_eta[iLep]) );
	double tmp_lepSF = h_mu_SF_veto->GetBinContent(binX, binY);
	weight_lepSF    *= tmp_lepSF;
	weight_lepSF_Up *= ( tmp_lepSF + h_mu_SF_veto->GetBinError(binX, binY) );
	weight_lepSF_Dn *= ( tmp_lepSF - h_mu_SF_veto->GetBinError(binX, binY) );
      }

      // If Fastsim
      if( sampleIsFastsim){
	binX = h_mu_FS->GetXaxis()->FindBin( std::min(lepSF_FS_pt_cutoff, recoLep_pt[iLep]) );
	binY = h_mu_FS->GetYaxis()->FindBin( fabs(recoLep_eta[iLep]) );
	double tmp_lepFSSF = h_mu_FS->GetBinContent(binX, binY);
	weight_lepFSSF     *= tmp_lepFSSF;
	weight_lepFSSF_Up  *= ( tmp_lepFSSF + h_mu_FS->GetBinContent(binX, binY) );
	weight_lepFSSF_Dn  *= ( tmp_lepFSSF - h_mu_FS->GetBinContent(binX, binY) );
      } // end if isFastsim

    } // end if recoMuon


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
    
      binX = h_el_vetoLepEff->GetXaxis()->FindBin( std::max( std::min(lepSF_pt_cutoff, genLostLep_pt[iLep]), lepSF_pt_min ) );
      binY = h_el_vetoLepEff->GetYaxis()->FindBin( fabs(genLostLep_eta[iLep]) );
      double vetoEff = h_el_vetoLepEff->GetBinContent( binX, binY );

      binX = h_el_SF_veto->GetXaxis()->FindBin( std::max( std::min(lepSF_pt_cutoff, genLostLep_pt[iLep]), lepSF_pt_min ) );
      binY = h_el_SF_veto->GetYaxis()->FindBin( fabs(genLostLep_eta[iLep]) );
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
    
      binX = h_mu_vetoLepEff->GetXaxis()->FindBin( std::max( std::min(lepSF_pt_cutoff, genLostLep_pt[iLep]), lepSF_pt_min ) );
      binY = h_mu_vetoLepEff->GetYaxis()->FindBin( fabs(genLostLep_eta[iLep]) );
      double vetoEff = h_mu_vetoLepEff->GetBinContent( binX, binY );

      binX = h_mu_SF_veto->GetXaxis()->FindBin( std::max( std::min(lepSF_pt_cutoff, genLostLep_pt[iLep]), lepSF_pt_min ) );
      binY = h_mu_SF_veto->GetYaxis()->FindBin( fabs(genLostLep_eta[iLep]) );
      double vetoLepSF_temp    = h_mu_SF_veto->GetBinContent( binX, binY );
      double vetoLepSF_temp_Up = (vetoLepSF_temp + h_mu_SF_veto->GetBinError(binX, binY));
      double vetoLepSF_temp_Dn = (vetoLepSF_temp - h_mu_SF_veto->GetBinError(binX, binY));
      
      if( (1-vetoEff)>0.0 ){
	weight_vetoLepSF    = ( 1-(vetoEff*vetoLepSF_temp) )/( 1-vetoEff );
	weight_vetoLepSF_Up = ( 1-(vetoEff*vetoLepSF_temp_Up) )/( 1-vetoEff );
	weight_vetoLepSF_Dn = ( 1-(vetoEff*vetoLepSF_temp_Dn) )/( 1-vetoEff );	    
      }
      else{
	weight_vetoLepSF    = 1.0;
	weight_vetoLepSF_Up = 1.0;
	weight_vetoLepSF_Dn = 1.0;
      }

    } // end if genLostLepton is muon



  } // end loop over genLostLeptons
    


  return;
}

//////////////////////////////////////////////////////////////////////
