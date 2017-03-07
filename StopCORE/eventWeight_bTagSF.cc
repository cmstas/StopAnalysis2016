#include "eventWeight_bTagSF.h"

//////////////////////////////////////////////////////////////////////

eventWeight_bTagSF::eventWeight_bTagSF( bool isFastsim ){

  sampleIsFastsim = isFastsim;

  BTAG_LSE = 0.5426;
  BTAG_MED = 0.8484;
  BTAG_TGT = 0.9535;

  std::cout << "    Loading btag SFs..." << std::endl << std::endl;
   
  // 25s version of SFs
  calib         = new BTagCalibration("csvv2", "../StopCORE/inputs/btagsf/CSVv2_Moriond17_B_H.csv"); // Moriond17 SFs
  calib_fastsim = new BTagCalibration("CSV", "../StopCORE/inputs/btagsf/fastsim_csvv2_ttbar_26_1_2017.csv"); // Moriond17 SFs

  reader_heavy      = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central"); // central
  reader_heavy_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up");  // sys up
  reader_heavy_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down");  // sys down
  reader_light      = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "central");  // central
  reader_light_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "up");  // sys up
  reader_light_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "down");  // sys down
  reader_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "central"); // central
  reader_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "up");  // sys up
  reader_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "down");  // sys down

  reader_loose_heavy      = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "central"); // central
  reader_loose_heavy_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "up");  // sys up
  reader_loose_heavy_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "down");  // sys down
  reader_loose_light      = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "central");  // central
  reader_loose_light_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "up");  // sys up
  reader_loose_light_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "down");  // sys down
  reader_loose_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_LOOSE, "fastsim", "central"); // central
  reader_loose_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_LOOSE, "fastsim", "up");  // sys up
  reader_loose_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_LOOSE, "fastsim", "down");  // sys down

  reader_tight_heavy      = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "comb", "central"); // central
  reader_tight_heavy_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "comb", "up");  // sys up
  reader_tight_heavy_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "comb", "down");  // sys down
  reader_tight_light      = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "incl", "central");  // central
  reader_tight_light_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "incl", "up");  // sys up
  reader_tight_light_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "incl", "down");  // sys down
  reader_tight_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_TIGHT, "fastsim", "central"); // central
  reader_tight_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_TIGHT, "fastsim", "up");  // sys up
  reader_tight_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_TIGHT, "fastsim", "down");  // sys down

  TH2D* h_btag_eff_b_temp = NULL;
  TH2D* h_btag_eff_c_temp = NULL;
  TH2D* h_btag_eff_udsg_temp = NULL;

  TH2D* h_tight_btag_eff_b_temp = NULL;
  TH2D* h_tight_btag_eff_c_temp = NULL;
  TH2D* h_tight_btag_eff_udsg_temp = NULL;

  TH2D* h_loose_btag_eff_b_temp = NULL;
  TH2D* h_loose_btag_eff_c_temp = NULL;
  TH2D* h_loose_btag_eff_udsg_temp = NULL;

  if(sampleIsFastsim){
    feff =  new TFile("../StopCORE/inputs/btagsf/BTagEff_76X_T2ttT2bWT2tb.root");

    h_btag_eff_b_temp = (TH2D*) feff->Get("MediumBEfficiency");
    h_btag_eff_c_temp = (TH2D*) feff->Get("MediumCEfficiency");
    h_btag_eff_udsg_temp = (TH2D*) feff->Get("MediumLEfficiency");

    h_tight_btag_eff_b_temp = (TH2D*) feff->Get("TightBEfficiency");
    h_tight_btag_eff_c_temp = (TH2D*) feff->Get("TightCEfficiency");
    h_tight_btag_eff_udsg_temp = (TH2D*) feff->Get("TightLEfficiency");

    h_loose_btag_eff_b_temp = (TH2D*) feff->Get("LooseBEfficiency");
    h_loose_btag_eff_c_temp = (TH2D*) feff->Get("LooseCEfficiency");
    h_loose_btag_eff_udsg_temp = (TH2D*) feff->Get("LooseLEfficiency");
  } else {
    feff =  new TFile("../StopCORE/inputs/btagsf/BTagEff_Moriond17_TTandW.root");

    h_btag_eff_b_temp = (TH2D*) feff->Get("MediumBEfficiency");
    h_btag_eff_c_temp = (TH2D*) feff->Get("MediumCEfficiency");
    h_btag_eff_udsg_temp = (TH2D*) feff->Get("MediumLEfficiency");

    h_tight_btag_eff_b_temp = (TH2D*) feff->Get("TightBEfficiency");
    h_tight_btag_eff_c_temp = (TH2D*) feff->Get("TightCEfficiency");
    h_tight_btag_eff_udsg_temp = (TH2D*) feff->Get("TightLEfficiency");

    h_loose_btag_eff_b_temp = (TH2D*) feff->Get("LooseBEfficiency");
    h_loose_btag_eff_c_temp = (TH2D*) feff->Get("LooseCEfficiency");
    h_loose_btag_eff_udsg_temp = (TH2D*) feff->Get("LooseLEfficiency");
  }

  h_btag_eff_b = (TH2D*) h_btag_eff_b_temp->Clone("h_btag_eff_b");
  h_btag_eff_c = (TH2D*) h_btag_eff_c_temp->Clone("h_btag_eff_c");
  h_btag_eff_udsg = (TH2D*) h_btag_eff_udsg_temp->Clone("h_btag_eff_udsg");

  h_tight_btag_eff_b = (TH2D*) h_tight_btag_eff_b_temp->Clone("h_tight_btag_eff_b");
  h_tight_btag_eff_c = (TH2D*) h_tight_btag_eff_c_temp->Clone("h_tight_btag_eff_c");
  h_tight_btag_eff_udsg = (TH2D*) h_tight_btag_eff_udsg_temp->Clone("h_tight_btag_eff_udsg");

  h_loose_btag_eff_b = (TH2D*) h_loose_btag_eff_b_temp->Clone("h_loose_btag_eff_b");
  h_loose_btag_eff_c = (TH2D*) h_loose_btag_eff_c_temp->Clone("h_loose_btag_eff_c");
  h_loose_btag_eff_udsg = (TH2D*) h_loose_btag_eff_udsg_temp->Clone("h_loose_btag_eff_udsg");
   

}

//////////////////////////////////////////////////////////////////////

eventWeight_bTagSF::~eventWeight_bTagSF(){
  

  delete calib;
  delete reader_heavy;
  delete reader_heavy_UP;
  delete reader_heavy_DN;
  delete reader_light;
  delete reader_light_UP;
  delete reader_light_DN;
  delete reader_loose_heavy;
  delete reader_loose_heavy_UP;
  delete reader_loose_heavy_DN;
  delete reader_loose_light;
  delete reader_loose_light_UP;
  delete reader_loose_light_DN;
  delete reader_tight_heavy;
  delete reader_tight_heavy_UP;
  delete reader_tight_heavy_DN;
  delete reader_tight_light;
  delete reader_tight_light_UP;
  delete reader_tight_light_DN;
  delete calib_fastsim;
  delete reader_fastsim;
  delete reader_fastsim_UP;
  delete reader_fastsim_DN;
  delete reader_tight_fastsim;
  delete reader_tight_fastsim_UP;
  delete reader_tight_fastsim_DN;
  delete reader_loose_fastsim;
  delete reader_loose_fastsim_UP;
  delete reader_loose_fastsim_DN;
  
  feff->Close();
  
}

//////////////////////////////////////////////////////////////////////

void eventWeight_bTagSF::getBTagWeight( int WP, std::vector< double > jet_pt, std::vector< double > jet_eta, std::vector< double > jet_CSV, std::vector< int > jet_flavour, double &weight_btagsf, double &weight_btagsf_heavy_UP, double &weight_btagsf_heavy_DN, double &weight_btagsf_light_UP, double &weight_btagsf_light_DN, double &weight_btagsf_FS_UP, double &weight_btagsf_FS_DN ){

  // Initialize output variables
  weight_btagsf          = 1.0;
  weight_btagsf_heavy_UP = 1.0;
  weight_btagsf_heavy_DN = 1.0;
  weight_btagsf_light_UP = 1.0;
  weight_btagsf_light_DN = 1.0;
  weight_btagsf_FS_UP = 1.0;
  weight_btagsf_FS_DN = 1.0;

  // Input sanitation
  if( WP<0 || WP>2 ){
    std::cout << "btag sf WP needs an argument of 0, 1, or 2, for loose, medium, or tight ID" << std::endl;
  }

  if( jet_pt.size()!=jet_eta.size() ){
    std::cout << "btag sf vectors for jet pt, eta are different sizes, exiting..." << std::endl;
    return;
  }
  if( jet_eta.size()!=jet_flavour.size() ){
    std::cout << "btag sf vectors for jet eta, flavour are different sizes, exiting..." << std::endl;
    return;
  }
  if( jet_flavour.size()!=jet_CSV.size() ){
    std::cout << "btag sf vectors for jet flavour, passCSV are different sizes, exiting..." << std::endl;
    return;
  }

  // Initialize utility variables
  double btagprob_eff  = 1.0;
  double btagprob_mc   = 1.0;
  double btagprob_data = 1.0;

  double btagprob_err_heavy_UP = 1.0;
  double btagprob_err_heavy_DN = 1.0;
  double btagprob_err_light_UP = 1.0;
  double btagprob_err_light_DN = 1.0;
  double btagprob_err_FS_UP    = 1.0;
  double btagprob_err_FS_DN    = 1.0;

  double weight_cent  = 1.0;
  double weight_UP    = 1.0;
  double weight_DN    = 1.0;
  double weight_FS_UP = 1.0;
  double weight_FS_DN = 1.0;

  // Loop over jet vectors
  for(int iJet=0; iJet<(int)jet_pt.size(); iJet++){

    BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
  
    // Get jet pT, eta, within cutoffs of efficiency file
    int binx=-99;
    int biny=-99;
    TH2D* h_eff = NULL;

    double pt_eff  = std::max(20.0, std::min(399.0, jet_pt[iJet]));
    double eta_eff = std::min(2.39, fabs(jet_eta[iJet]) );
    
    double pt_reader  = std::max(30.0, std::min(669.0, jet_pt[iJet]));
    double eta_reader = std::min(2.39, fabs(jet_eta[iJet]) );

    
    // bJets
    if( abs(jet_flavour[iJet])==5 ){
      flavor = BTagEntry::FLAV_B;
      pt_eff     = std::max(20.0,std::min(599.0, jet_pt[iJet])); // max pt of 600.0 GeV for b

      if( WP==0 ) h_eff = h_loose_btag_eff_b;
      if( WP==1 ) h_eff = h_btag_eff_b;
      if( WP==2 ) h_eff = h_tight_btag_eff_b;
      binx = h_eff->GetXaxis()->FindBin(pt_eff);
      biny = h_eff->GetYaxis()->FindBin(eta_eff);
      btagprob_eff = h_eff->GetBinContent(binx,biny);

      if( WP==0 ){
	weight_cent  = reader_loose_heavy->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_loose_heavy_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_loose_heavy_DN->eval(flavor, eta_reader, pt_reader);
      }
      if( WP==1 ){
	weight_cent  = reader_heavy->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_heavy_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_heavy_DN->eval(flavor, eta_reader, pt_reader);
      }
      if( WP==2 ){
	weight_cent  = reader_tight_heavy->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_tight_heavy_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_tight_heavy_DN->eval(flavor, eta_reader, pt_reader);
      }


    }
    // Charm
    else if( abs(jet_flavour[iJet])==4 ){
      flavor = BTagEntry::FLAV_C;
      
      if( WP==0 ) h_eff = h_loose_btag_eff_c;
      if( WP==1 ) h_eff = h_btag_eff_c;
      if( WP==2 ) h_eff = h_tight_btag_eff_c;
      binx = h_eff->GetXaxis()->FindBin(pt_eff);
      biny = h_eff->GetYaxis()->FindBin(eta_eff);
      btagprob_eff = h_eff->GetBinContent(binx,biny);
      
      if( WP==0 ){
	weight_cent  = reader_loose_heavy->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_loose_heavy_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_loose_heavy_DN->eval(flavor, eta_reader, pt_reader);
      }
      if( WP==1 ){
	weight_cent  = reader_heavy->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_heavy_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_heavy_DN->eval(flavor, eta_reader, pt_reader);
      }
      if( WP==2 ){
	weight_cent  = reader_tight_heavy->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_tight_heavy_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_tight_heavy_DN->eval(flavor, eta_reader, pt_reader);
      }
      
    }
    // UDSG  
    else{
      if( WP==0 ) h_eff = h_loose_btag_eff_udsg;
      if( WP==1 ) h_eff = h_btag_eff_udsg;
      if( WP==2 ) h_eff = h_tight_btag_eff_udsg;
      binx = h_eff->GetXaxis()->FindBin(pt_eff);
      biny = h_eff->GetYaxis()->FindBin(eta_eff);
      btagprob_eff = h_eff->GetBinContent(binx,biny);
      
      if( WP==0 ){
	weight_cent  = reader_loose_light->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_loose_light_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_loose_light_DN->eval(flavor, eta_reader, pt_reader);
      }
      if( WP==1 ){
	weight_cent  = reader_light->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_light_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_light_DN->eval(flavor, eta_reader, pt_reader);
      }
      if( WP==2 ){
	weight_cent  = reader_tight_light->eval(flavor, eta_reader, pt_reader);
	weight_UP    = reader_tight_light_UP->eval(flavor, eta_reader, pt_reader);
	weight_DN    = reader_tight_light_DN->eval(flavor, eta_reader, pt_reader);
      }
    }

    
    // extra SF for fastsim
    if(sampleIsFastsim) {

      if( WP==0 ){
	weight_FS_UP = reader_loose_fastsim_UP->eval(flavor,eta_reader,pt_reader)*weight_cent;
	weight_FS_DN = reader_loose_fastsim_DN->eval(flavor,eta_reader,pt_reader)*weight_cent;
	weight_cent *= reader_loose_fastsim->eval(flavor,eta_reader,pt_reader);
	
      }
      if( WP==1 ){
	weight_FS_UP = reader_fastsim_UP->eval(flavor,eta_reader,pt_reader)*weight_cent;
	weight_FS_DN = reader_fastsim_DN->eval(flavor,eta_reader,pt_reader)*weight_cent;
	weight_cent *= reader_fastsim->eval(flavor,eta_reader,pt_reader);
	
      }
      if( WP==2 ){
	weight_FS_UP = reader_tight_fastsim_UP->eval(flavor,eta_reader,pt_reader)*weight_cent;
	weight_FS_DN = reader_tight_fastsim_DN->eval(flavor,eta_reader,pt_reader)*weight_cent;
	weight_cent *= reader_tight_fastsim->eval(flavor,eta_reader,pt_reader);
	
      }

    }
    

    // Check if CSV passes WP
    bool passWP = false;
    if( WP==0 && jet_CSV[iJet]>BTAG_LSE ) passWP = true;
    if( WP==1 && jet_CSV[iJet]>BTAG_MED ) passWP = true;
    if( WP==2 && jet_CSV[iJet]>BTAG_TGT ) passWP = true;
    
    // If jet is bTagged
    if( passWP ){
      
      btagprob_data *= (weight_cent * btagprob_eff);
      btagprob_mc   *= btagprob_eff;
      
      if (flavor == BTagEntry::FLAV_UDSG) {
	btagprob_err_light_UP *= weight_UP*btagprob_eff;
	btagprob_err_light_DN *= weight_DN*btagprob_eff;
	btagprob_err_heavy_UP *= weight_cent*btagprob_eff;
	btagprob_err_heavy_DN *= weight_cent*btagprob_eff;
      } 
      else {
	btagprob_err_light_UP *= weight_cent*btagprob_eff;
	btagprob_err_light_DN *= weight_cent*btagprob_eff;
	btagprob_err_heavy_UP *= weight_UP*btagprob_eff;
	btagprob_err_heavy_DN *= weight_DN*btagprob_eff;
      }

      if(sampleIsFastsim){
	btagprob_err_FS_UP *= weight_FS_UP*btagprob_eff;
	btagprob_err_FS_DN *= weight_FS_DN*btagprob_eff;
      }
      
    } // end if jet is bTagged

    // if jet fails bTag
    else{
      
      btagprob_data *= (1. - weight_cent * btagprob_eff);
      btagprob_mc   *= (1. - btagprob_eff);
      
      if (flavor == BTagEntry::FLAV_UDSG) {
	btagprob_err_light_UP *= (1. - weight_UP * btagprob_eff);
	btagprob_err_light_DN *= (1. - weight_DN * btagprob_eff);
	btagprob_err_heavy_UP *= (1. - weight_cent * btagprob_eff);
	btagprob_err_heavy_DN *= (1. - weight_cent * btagprob_eff);
      } 
      else {
	btagprob_err_light_UP *= (1. - weight_cent * btagprob_eff);
	btagprob_err_light_DN *= (1. - weight_cent * btagprob_eff);
	btagprob_err_heavy_UP *= (1. - weight_UP * btagprob_eff);
	btagprob_err_heavy_DN *= (1. - weight_DN * btagprob_eff);
      }
    
      if(sampleIsFastsim){
	btagprob_err_FS_UP *= (1. - weight_FS_UP * btagprob_eff);
	btagprob_err_FS_DN *= (1. - weight_FS_DN * btagprob_eff);
      }

    } // end if jet not bTagged
   
    
  } // end loop over jets


  // Set values of btagsf weights
  weight_btagsf          = (btagprob_data / btagprob_mc);
  weight_btagsf_heavy_UP = (btagprob_err_heavy_UP / btagprob_mc);
  weight_btagsf_light_UP = (btagprob_err_light_UP / btagprob_mc);
  weight_btagsf_heavy_DN = (btagprob_err_heavy_DN / btagprob_mc);
  weight_btagsf_light_DN = (btagprob_err_light_DN / btagprob_mc);
  weight_btagsf_FS_UP    = (btagprob_err_FS_UP / btagprob_mc);
  weight_btagsf_FS_DN    = (btagprob_err_FS_DN / btagprob_mc);
  
  return;
}

//////////////////////////////////////////////////////////////////////
