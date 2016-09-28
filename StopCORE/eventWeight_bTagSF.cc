#include "eventWeight_bTagSF.h"

//////////////////////////////////////////////////////////////////////

eventWeight_bTagSF::eventWeight_bTagSF( bool isFastsim ){

  sampleIsFastsim = isFastsim;

  // 25s version of SFs
  calib           = new BTagCalibration("csvv2", "../../CORE/Tools/btagsf/data/run2_25ns/CSVv2.csv"); 
  //calib           = new BTagCalibration("csvv2", "../../CORE/Tools/btagsf/data/run2_25ns/CSVv2_4invfb.csv"); 
  reader_heavy    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "central"); // central, hf
  reader_heavy_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "up");      // sys up, hf
  reader_heavy_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "down");    // sys down, hf
  reader_light    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central");   // central, lf
  reader_light_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up");        // sys up, lf
  reader_light_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down");      // sys down, lf
  
  if( !sampleIsFastsim ) {
    f_btag_eff      = new TFile("../../CORE/Tools/btagsf/data/run2_25ns/btageff__ttbar_powheg_pythia8_25ns.root");
    //f_btag_eff      = new TFile("../../CORE/Tools/btagsf/data/run2_25ns/bTagEffs_80X.root");
    h_btag_eff_b    = (TH2D*)f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_b");
    h_btag_eff_c    = (TH2D*)f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_c");
    h_btag_eff_udsg = (TH2D*)f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_udsg");

    std::cout << "    Loaded fullsim btag SFs" << std::endl;
    std::cout << std::endl;
  }
  else{
    // 25ns fastsim version of SFs
    calib_fastsim      = new BTagCalibration("CSV", "../../CORE/Tools/btagsf/data/run2_fastsim/CSV_13TEV_Combined_20_11_2015.csv"); 
    reader_fastsim     = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "central"); // central
    reader_fastsim_UP  = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "up");      // sys up
    reader_fastsim_DN  = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "down");    // sys down

    f_btag_eff_fastsim = new TFile("../../CORE/Tools/btagsf/data/run2_fastsim/btageff__SMS-T1bbbb-T1qqqq_fastsim.root");
    h_btag_eff_b       = (TH2D*)f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_b");
    h_btag_eff_c       = (TH2D*)f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_c");
    h_btag_eff_udsg    = (TH2D*)f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_udsg");

    std::cout << "    Loaded fastsim btag SFs" << std::endl;
    std::cout << std::endl;

  } // end if isFastsim
  
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
  
  if(sampleIsFastsim){

    f_btag_eff_fastsim->Close();
    f_btag_eff_fastsim->~TFile();

    delete calib_fastsim;
    delete reader_fastsim;
    delete reader_fastsim_UP;
    delete reader_fastsim_DN;
  }
  else{
    f_btag_eff->Close();
    f_btag_eff->~TFile();
  }
  
}

//////////////////////////////////////////////////////////////////////

void eventWeight_bTagSF::getBTagWeight( std::vector< double > jet_pt, std::vector< double > jet_eta, std::vector< int > jet_flavour, std::vector< bool > jet_passCSV, double &weight_btagsf, double &weight_btagsf_heavy_UP, double &weight_btagsf_heavy_DN, double &weight_btagsf_light_UP, double &weight_btagsf_light_DN ){

  // Initialize output variables
  weight_btagsf          = 1.0;
  weight_btagsf_heavy_UP = 1.0;
  weight_btagsf_heavy_DN = 1.0;
  weight_btagsf_light_UP = 1.0;
  weight_btagsf_light_DN = 1.0;

  // Input sanitation
  if( jet_pt.size()!=jet_eta.size() ){
    std::cout << "btag sf vectors for jet pt, eta are different sizes, exiting..." << std::endl;
    return;
  }
  if( jet_eta.size()!=jet_flavour.size() ){
    std::cout << "btag sf vectors for jet eta, flavour are different sizes, exiting..." << std::endl;
    return;
  }
  if( jet_flavour.size()!=jet_passCSV.size() ){
    std::cout << "btag sf vectors for jet flavour, passCSV are different sizes, exiting..." << std::endl;
    return;
  }

  // Initialize utility variables
  double btagprob_eff  = 1.0;
  double btagprob_mc   = 1.0;
  double btagprob_data = 1.0;

  double btagprob_err_heavy_UP = 0.0;
  double btagprob_err_heavy_DN = 0.0;
  double btagprob_err_light_UP = 0.0;
  double btagprob_err_light_DN = 0.0;

  double weight_cent = 1.0;
  double weight_UP   = 1.0;
  double weight_DN   = 1.0;

  // Loop over jet vectors
  for(int iJet=0; iJet<(int)jet_pt.size(); iJet++){

    BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
  
    // Get jet pT, eta, within cutoffs of efficiency file
    double pt_eff  = std::max(20.0, std::min(399.0, jet_pt[iJet]));
    double eta_eff = std::min(2.39, fabs(jet_eta[iJet]) );
    
    double pt_reader  = std::max(30.0, std::min(669.0, jet_pt[iJet]));
    double eta_reader = std::min(2.39, fabs(jet_eta[iJet]) );

    int binx=-99;
    int biny=-99;
    
    // bJets
    if( abs(jet_flavour[iJet])==5 ){
      flavor = BTagEntry::FLAV_B;
      pt_eff     = std::max(20.0,std::min(599.0, jet_pt[iJet])); // max pt of 600.0 GeV for b

      binx = h_btag_eff_b->GetXaxis()->FindBin(pt_eff);
      biny = h_btag_eff_b->GetYaxis()->FindBin(eta_eff);
      btagprob_eff = h_btag_eff_b->GetBinContent(binx,biny);
      
      weight_cent  = reader_heavy->eval(flavor, eta_reader, pt_reader);
      weight_UP    = reader_heavy_UP->eval(flavor, eta_reader, pt_reader);
      weight_DN    = reader_heavy_DN->eval(flavor, eta_reader, pt_reader);
    }
    // Charm
    else if( abs(jet_flavour[iJet])==4 ){
      flavor = BTagEntry::FLAV_C;
      
      binx = h_btag_eff_c->GetXaxis()->FindBin(pt_eff);
      biny = h_btag_eff_c->GetYaxis()->FindBin(eta_eff);
      btagprob_eff = h_btag_eff_c->GetBinContent(binx,biny);
      
      weight_cent = reader_heavy->eval(flavor, eta_reader, pt_reader);
      weight_UP   = reader_heavy_UP->eval(flavor, eta_reader, pt_reader);
      weight_DN   = reader_heavy_DN->eval(flavor, eta_reader, pt_reader);
    }
    // UDSG  
    else{
      binx = h_btag_eff_udsg->GetXaxis()->FindBin(pt_eff);
      biny = h_btag_eff_udsg->GetYaxis()->FindBin(eta_eff);
      btagprob_eff = h_btag_eff_udsg->GetBinContent(binx,biny);
      
      weight_cent = reader_light->eval(flavor, eta_reader, pt_reader);
      weight_UP   = reader_light_UP->eval(flavor, eta_reader, pt_reader);
      weight_DN   = reader_light_DN->eval(flavor, eta_reader, pt_reader);
    }

    
    // extra SF for fastsim
    if(sampleIsFastsim) {
      weight_cent *= reader_fastsim->eval(flavor,eta_reader,pt_reader);
      weight_UP   *= reader_fastsim_UP->eval(flavor,eta_reader,pt_reader);
      weight_DN   *= reader_fastsim_DN->eval(flavor,eta_reader,pt_reader);
    }
    

    double abserr_UP = weight_UP - weight_cent;
    double abserr_DN = weight_cent - weight_DN;
    
    
    // If jet is bTagged
    if( jet_passCSV[iJet] ){
      
      btagprob_data *= (weight_cent * btagprob_eff);
      btagprob_mc   *= btagprob_eff;
      
      if (flavor == BTagEntry::FLAV_UDSG) {
	btagprob_err_light_UP += abserr_UP/weight_cent;
	btagprob_err_light_DN += abserr_DN/weight_cent;
      } 
      else {
	btagprob_err_heavy_UP += abserr_UP/weight_cent;
	btagprob_err_heavy_DN += abserr_DN/weight_cent;
      }
      
    } // end if jet is bTagged

    // if jet fails bTag
    else{
      
      btagprob_data *= (1. - weight_cent * btagprob_eff);
      btagprob_mc   *= (1. - btagprob_eff);
      
      if (flavor == BTagEntry::FLAV_UDSG) {
	btagprob_err_light_UP += (-btagprob_eff * abserr_UP)/(1 - btagprob_eff * weight_cent);
	btagprob_err_light_DN += (-btagprob_eff * abserr_DN)/(1 - btagprob_eff * weight_cent);
      } 
      else {
	btagprob_err_heavy_UP += (-btagprob_eff * abserr_UP)/(1 - btagprob_eff * weight_cent);
	btagprob_err_heavy_DN += (-btagprob_eff * abserr_DN)/(1 - btagprob_eff * weight_cent);
      }
    
    } // end if jet not bTagged
    

  } // end loop over jets


  // Set values of btagsf weights
  weight_btagsf          = (btagprob_data / btagprob_mc);
  weight_btagsf_heavy_UP = (weight_btagsf + btagprob_err_heavy_UP*weight_btagsf);
  weight_btagsf_light_UP = (weight_btagsf + btagprob_err_light_UP*weight_btagsf);
  weight_btagsf_heavy_DN = (weight_btagsf - btagprob_err_heavy_DN*weight_btagsf);
  weight_btagsf_light_DN = (weight_btagsf - btagprob_err_light_DN*weight_btagsf);
   

  return;
}

//////////////////////////////////////////////////////////////////////
