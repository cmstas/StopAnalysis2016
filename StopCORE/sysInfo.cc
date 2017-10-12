#include "sysInfo.h"

//////////////////////////////////////////////////////////////////////

sysInfo::evtWgtInfo wgtInfo;

//////////////////////////////////////////////////////////////////////

sysInfo::Util::Util( sysInfo::ID systematic ){
  
  switch( systematic ){

  case( k_nominal ):
    id          = systematic;
    label       = "nominal";
    title       = "Nominal";
    tex         = "Nominal";
    hasOwnBabies = true;
    break;

  case( k_JESUp ):
    id          = systematic;
    label       = "jesUp";
    title       = "JES Up";
    tex         = "JES~Up";
    hasOwnBabies = true;
    break;

  case( k_JESDown ):
    id          = systematic;
    label       = "jesDn";
    title       = "JES Down";
    tex         = "JES~Down";
    hasOwnBabies = true;
    break;

  case( k_diLepTriggerUp ):
    id          = systematic;
    label       = "diLepTriggerSFUp";
    title       = "DiLepton Trigger Scale Factor, Up";
    tex         = "DiLepton~Trigger~Scale~Factor,~Up";
    hasOwnBabies = false;
    break;

  case( k_diLepTriggerDown ):
    id          = systematic;
    label       = "diLepTriggerSFDn";
    title       = "DiLepton Trigger Scale Factor, Down";
    tex         = "DiLepton~Trigger~Scale~Factor,~Down";
    hasOwnBabies = false;
    break;

  case( k_cr2lTriggerUp ):
    id          = systematic;
    label       = "cr2lTriggerSFUp";
    title       = "CR2l Trigger Scale Factor, Up";
    tex         = "CR2l~Trigger~Scale~Factor,~Up";
    hasOwnBabies = false;
    break;

  case( k_cr2lTriggerDown ):
    id          = systematic;
    label       = "cr2lTriggerSFDn";
    title       = "CR2l Trigger Scale Factor, Down";
    tex         = "CR2l~Trigger~Scale~Factor,~Down";
    hasOwnBabies = false;
    break;

  case( k_bTagEffHFUp ):
    id          = systematic;
    label       = "bTagEffHFUp";
    title       = "bTag Efficicency, Heavy Flavour, Up";
    tex         = "bTag~Efficicency,~Heavy~Flavour,~Up";
    hasOwnBabies = false;
    break;

  case( k_bTagEffHFDown ):
    id          = systematic;
    label       = "bTagEffHFDn";
    title       = "bTag Efficicency, Heavy Flavour, Down";
    tex         = "bTag~Efficicency,~Heavy~Flavour,~Down";
    hasOwnBabies = false;
    break;

  case( k_bTagEffLFUp ):
    id          = systematic;
    label       = "bTagEffLFUp";
    title       = "bTag Efficicency, Light Flavour, Up";
    tex         = "bTag~Efficicency,~Light~Flavour,~Up";
    hasOwnBabies = false;
    break;

  case( k_bTagEffLFDown ):
    id          = systematic;
    label       = "bTagEffLFDn";
    title       = "bTag Efficicency, Light Flavour, Down";
    tex         = "bTag~Efficicency,~Light~Flavour,~Down";
    hasOwnBabies = false;
    break;

  case( k_lepSFUp ):
    id          = systematic;
    label       = "lepSFUp";
    title       = "Lepton Scale Factor, Up";
    tex         = "Lepton~Scale~Factor,~Up";
    hasOwnBabies = false;
    break;

  case( k_lepSFDown ):
    id          = systematic;
    label       = "lepSFDn";
    title       = "Lepton Scale Factor, Down";
    tex         = "Lepton~Scale~Factor,~Down";
    hasOwnBabies = false;
    break;

  case( k_lepFSSFUp ):
    id          = systematic;
    label       = "lepFSSFUp";
    title       = "Lepton Fastsim Scale Factor, Up";
    tex         = "Lepton~Fastsm~Scale~Factor,~Up";
    hasOwnBabies = false;
    break;

  case( k_lepFSSFDown ):
    id          = systematic;
    label       = "lepFSSFDn";
    title       = "Lepton Fastsim Scale Factor, Down";
    tex         = "Lepton~Fastsim~Scale~Factor,~Down";
    hasOwnBabies = false;
    break;

  case( k_topPtSFUp ):
    id          = systematic;
    label       = "topPtSFUp";
    title       = "top pT Scale Factor, Up";
    tex         = "top~$p_{T}$~Scale~Factor,~Up";
    hasOwnBabies = false;
    break;

  case( k_topPtSFDown ):
    id          = systematic;
    label       = "topPtSFDn";
    title       = "top pT Scale Factor, Down";
    tex         = "top~$p_{T}$~Scale~Factor,~Down";
    hasOwnBabies = false;
    break;

  case( k_metResUp ):
    id          = systematic;
    label       = "metResUp";
    title       = "MET Resolution, Up";
    tex         = "MET~Resolution,~Up";
    hasOwnBabies = false;
    break;

  case( k_metResDown ):
    id          = systematic;
    label       = "metResDn";
    title       = "MET Resolution, Down";
    tex         = "MET~Resolution,~Down";
    hasOwnBabies = false;
    break;

  case( k_metTTbarUp ):
    id          = systematic;
    label       = "metTTbarUp";
    title       = "MET ttbar SF, Up";
    tex         = "MET~$t\\bar{t}$~SF,~Up";
    hasOwnBabies = false;
    break;

  case( k_metTTbarDown ):
    id          = systematic;
    label       = "metTTbarDn";
    title       = "MET ttbar SF, Down";
    tex         = "MET~$t\\bar{t}$~SF,~Down";
    hasOwnBabies = false;
    break;

  case( k_ttbarSysPtUp ):
    id          = systematic;
    label       = "ttbarSysPtUp";
    title       = "ttbar/tW system pT, Up";
    tex         = "$t\\bar{t}/tW~p_{T}$,~Up";
    hasOwnBabies = false;
    break;

  case( k_ttbarSysPtDown ):
    id          = systematic;
    label       = "ttbarSysPtDn";
    title       = "ttbar/tW system pT, Down";
    tex         = "$t\\bar{t}/tW~p_{T}$,~Down";
    hasOwnBabies = false;
    break;

  case( k_nuPtSF_Up ):
    id          = systematic;
    label       = "nuPtUp";
    title       = "nuetrino pT, Up";
    tex         = "${\\nu}p_{T}$,~Up";
    hasOwnBabies = false;
    break;

  case( k_nuPtSF_Down ):
    id          = systematic;
    label       = "nuPtDn";
    title       = "nuetrino pT, Down";
    tex         = "${\\nu}p_{T}$,~Down";
    hasOwnBabies = false;
    break;

  case( k_WwidthSF_Up ):
    id          = systematic;
    label       = "WwidthSFUp";
    title       = "W Width, Up";
    tex         = "$W$~Width,~Up";
    hasOwnBabies = false;
    break;

  case( k_WwidthSF_Down ):
    id          = systematic;
    label       = "WwidthSFDn";
    title       = "W Width, Down";
    tex         = "$W$~Width,~Down";
    hasOwnBabies = false;
    break;

  case( k_hfXsec_Up ):
    id          = systematic;
    label       = "hfXsecUp";
    title       = "W+HF x-section, Up";
    tex         = "$W+HF$~x-section,~Up";
    hasOwnBabies = false;
    break;

  case( k_hfXsec_Down ):
    id          = systematic;
    label       = "hfXsecDn";
    title       = "W+HF x-section, Down";
    tex         = "$W+HF$~x-section,~Down";
    hasOwnBabies = false;
    break;

  case( k_pdfUp ):
    id          = systematic;
    label       = "pdfUp";
    title       = "PDF, Up";
    tex         = "PDF,~Up";
    hasOwnBabies = false;
    break;

  case( k_pdfDown ):
    id          = systematic;
    label       = "pdfDn";
    title       = "PDF, Down";
    tex         = "PDF,~Down";
    hasOwnBabies = false;
    break;
    
  case( k_alphasUp ):
    id          = systematic;
    label       = "alphasUp";
    title       = "Alpha S, Up";
    tex         = "$\\alpha_{S}$,~Up";
    hasOwnBabies = false;
    break;

  case( k_alphasDown ):
    id          = systematic;
    label       = "alphasDn";
    title       = "Alpha S, Down";
    tex         = "$\\alpha_{S}$,~Down";
    hasOwnBabies = false;
    break;
    
  case( k_q2Up ):
    id          = systematic;
    label       = "q2Up";
    title       = "Q2, Up";
    tex         = "$Q^{2}$,~Up";
    hasOwnBabies = false;
    break;    

  case( k_q2Down ):
    id          = systematic;
    label       = "q2Dn";
    title       = "Q2, Down";
    tex         = "$Q^{2}$,~Down";
    hasOwnBabies = false;
    break;    

  case( k_lumiUp ):
    id          = systematic;
    label       = "lumiUp";
    title       = "Luminosity, Up";
    tex         = "Luminosity,~Up";
    hasOwnBabies = false;
    break; 

  case( k_lumiDown ):
    id          = systematic;
    label       = "lumiDn";
    title       = "Luminosity, Down";
    tex         = "Luminosity,~Down";
    hasOwnBabies = false;
    break;    
    
  case( k_ISRUp ):
    id          = systematic;
    label       = "ISRUp";
    title       = "ISR, Up";
    tex         = "ISR,~Up";
    hasOwnBabies = false;
    break; 

  case( k_ISRDown ):
    id          = systematic;
    label       = "ISRDn";
    title       = "ISR, Down";
    tex         = "ISR,~Down";
    hasOwnBabies = false;
    break; 
    
  case( k_xsecUp ):
    id          = systematic;
    label       = "xsecUp";
    title       = "Signal X-Sec, Up";
    tex         = "Signal~X-Section,~Up";
    hasOwnBabies = false;
    break; 

  case( k_xsecDown ):
    id          = systematic;
    label       = "xsecDn";
    title       = "Signal X-Sec, Down";
    tex         = "Signal~X-Section,~Down";
    hasOwnBabies = false;
    break; 

  case( k_puUp ):
    id          = systematic;
    label       = "pileupUp";
    title       = "Pileup Reweight, Up";
    tex         = "Pileup~Reweight,~Up";
    hasOwnBabies = false;
    break; 

  case( k_puDown ):
    id          = systematic;
    label       = "pileupDn";
    title       = "Pileup Reweight, Down";
    tex         = "Pileup~Reweight,~Down";
    hasOwnBabies = false;
    break; 

  case( k_tauSFUp ):
    id          = systematic;
    label       = "tauSFUp";
    title       = "Tau Efficiency SF, Up";
    tex         = "$\\tau$~Efficiency~SF,~Up";
    hasOwnBabies = false;
    break; 

  case( k_tauSFDown ):
    id          = systematic;
    label       = "tauSFDn";
    title       = "Tau Efficiency SF, Down";
    tex         = "$\\tau$~Efficiency~SF,~Down";
    hasOwnBabies = false;
    break; 
 
  default:
    std::cout << "Could not find systematic info from systematic enum provided!" << std::endl;
    id           = systematic;
    label        = "NO SYSTEMATIC INFO FOUND FROM ENUM PROVIDED";
    title        = "NO SYSTEMATIC INFO FOUND FROM ENUM PROVIDED";
    tex          = "NO SYSTEMATIC INFO FOUND FROM ENUM PROVIDED";
    hasOwnBabies = false;
    break;

  }; // end systematic switch
    
}

//////////////////////////////////////////////////////////////////////

double sysInfo::GetEventWeight( sysInfo::ID whichSyst ) { return wgtInfo.sys_wgts[whichSyst]; }

double sysInfo::GetEventWeight_corridor( sysInfo::ID whichSyst ) { return wgtInfo.sys_wgts_corridor[whichSyst]; }

double sysInfo::GetEventWeight_SRbulk( sysInfo::ID whichSyst ) { return wgtInfo.sys_wgts_SRbulk[whichSyst]; }

double sysInfo::GetEventWeight_CR2lbulk( sysInfo::ID whichSyst ) { return wgtInfo.sys_wgts_CR2lbulk[whichSyst]; }

//////////////////////////////////////////////////////////////////////

sysInfo::evtWgtInfo::evtWgtInfo(){
  
  // Utilty Var Constants
  dr_matched = 0.1;
  lumi       = 35.867;     // Current lumi
  lumi_err   = lumi*0.026; // 2.6% uncertainty for Moriond17 
  
  // Initialize Switches for additional SFs
  apply_diLepTrigger_sf = false;
  apply_cr2lTrigger_sf  = false;
  apply_bTag_sf         = false;
  apply_lep_sf          = false;
  apply_vetoLep_sf      = false;
  apply_tau_sf          = false;
  apply_lepFS_sf        = false;
  apply_topPt_sf        = false;
  apply_metRes_sf       = false;
  apply_metTTbar_sf     = false;
  apply_ttbarSysPt_sf   = false;
  apply_ISR_sf          = false;
  apply_pu_sf           = false;
  apply_sample_sf       = false;

  // Initialize event weights and related variables
  initializeWeights();

  // Initialize baby weights histograms
  h_sig_counter         = NULL;
  h_sig_counter_nEvents = NULL;
  h_bkg_counter         = NULL;
  h_cr2lTrigger_sf_el   = NULL;
  h_cr2lTrigger_sf_mu   = NULL;
  h_pu_wgt              = NULL;
  h_pu_wgt_up           = NULL;
  h_pu_wgt_dn           = NULL;
  h_recoEff_tau         = NULL;
  
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::setUp( sampleInfo::ID sample, bool useBTagUtils, bool useLepSFUtils, bool use2ndLepToMet ){
  
  // Get sample info from enum
  sample_info = new sampleInfo::sampleUtil( sample );
  
  // Decision to use Utilities vs direct from baby for bTag and lep SFs
  useBTagSFs_fromFiles = useBTagUtils;
  useLepSFs_fromFiles  = useLepSFUtils;
  
  // Decision to use met with 2nd lepton removed (for lost lepton)
  add2ndLepToMet = use2ndLepToMet;

  // Get Signal XSection File
  if( sample_info->isSignal ){
    f_sig_xsec = new TFile("../StopCORE/inputs/signal_xsec/xsec_stop_13TeV.root","read");
    h_sig_xsec = (TH1D*)f_sig_xsec->Get("stop");
  }
  
  // Get SR trigger histos
  if( !sample_info->isData ){
    f_cr2lTrigger_sf = new TFile("../StopCORE/inputs/trigger/TriggerEff_2016.root","read");
    h_cr2lTrigger_sf_el = (TEfficiency*)f_cr2lTrigger_sf->Get("Efficiency_ge2l_metrl_el");
    h_cr2lTrigger_sf_mu = (TEfficiency*)f_cr2lTrigger_sf->Get("Efficiency_ge2l_metrl_mu");
  }

  // Initialize bTag SF machinery
  if( !sample_info->isData && useBTagSFs_fromFiles ){
    bTagSFUtil = new eventWeight_bTagSF( sample_info->isFastsim );
  }

  
  // Initialize Lepton Scale Factors
  if( !sample_info->isData && useLepSFs_fromFiles ){
    lepSFUtil  = new eventWeight_lepSF( sample_info->isFastsim );
  }

  // Get pileup wgt histo
  if( !sample_info->isData ){
    f_pu = new TFile("../StopCORE/inputs/pileup/pileup_wgts.root", "read");
    h_pu_wgt = (TH1D*)f_pu->Get("h_pileup_wgt");
    h_pu_wgt_up = (TH1D*)f_pu->Get("h_pileup_wgt_up");
    h_pu_wgt_dn = (TH1D*)f_pu->Get("h_pileup_wgt_down");
  }

  // Get lep reco histo 
  if( !sample_info->isData ){
    f_lepEff = new TFile("../StopCORE/inputs/lepsf/lepeff__moriond17__ttbar_powheg_pythia8_25ns__20170223.root", "read");
    h_recoEff_tau = (TH2D*)f_lepEff->Get("h2_lepEff_vetoSel_Eff_tau");
  }

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::cleanUp(){
  
  sample_info->~sampleUtil();
  
  if( !sample_info->isData && useBTagSFs_fromFiles){
    delete bTagSFUtil;
  }
  
  if( !sample_info->isData && useLepSFs_fromFiles){
    delete lepSFUtil;
  }

  if( !sample_info->isData ){
    f_cr2lTrigger_sf->Close();
    delete f_cr2lTrigger_sf;
  }
  
  if( sample_info->isSignal ){
    f_sig_xsec->Close();
    delete f_sig_xsec;
  }
  
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getWeightHistogramFromBaby( TFile *sourceFile ){

  // Get counter histogram from source file
  if( sample_info->isSignal ){
    h_sig_counter = (TH3D*)sourceFile->Get("h_counterSMS");
    h_sig_counter_nEvents = (TH2D*)sourceFile->Get("histNEvts");
  }
  else if( !sample_info->isData ){
    h_bkg_counter = (TH1D*)sourceFile->Get("h_counter");
  }

  return;
  
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::initializeWeights(){

  // Variables to form baseline event weight
  mStop = 0;
  mLSP = 0;
  mChargino = 0;
    
  nEvents = 1.0;
  xsec = 1.0;
  xsec_err = 0.0;

  // Event weights for each systematic
  sf_nominal = 1.0;

  sf_diLepTrigger = 1.0;
  sf_diLepTrigger_up = 1.0;
  sf_diLepTrigger_dn = 1.0;

  sf_cr2lTrigger = 1.0;
  sf_cr2lTrigger_up = 1.0;
  sf_cr2lTrigger_dn = 1.0;
  
  sf_bTag = 1.0;
  sf_bTagEffHF_up = 1.0;
  sf_bTagEffHF_dn = 1.0;
  sf_bTagEffLF_up = 1.0;
  sf_bTagEffLF_dn = 1.0;
  sf_bTag_FS_up = 1.0;
  sf_bTag_FS_dn = 1.0;
  sf_bTag_tight = 1.0;
  sf_bTagEffHF_tight_up = 1.0;
  sf_bTagEffHF_tight_dn = 1.0;
  sf_bTagEffLF_tight_up = 1.0;
  sf_bTagEffLF_tight_dn = 1.0;
  sf_bTag_tight_FS_up = 1.0;
  sf_bTag_tight_FS_dn = 1.0;
    
  sf_lep = 1.0;
  sf_lep_up = 1.0;
  sf_lep_dn = 1.0;
  
  sf_vetoLep = 1.0;
  sf_vetoLep_up = 1.0;
  sf_vetoLep_dn = 1.0;

  sf_tau = 1.0;
  sf_tau_up = 1.0;
  sf_tau_dn = 1.0;
    
  sf_lepFS = 1.0;
  sf_lepFS_up = 1.0;
  sf_lepFS_dn = 1.0;
  
  sf_topPt = 1.0;
  sf_topPt_up = 1.0;
  sf_topPt_dn = 1.0;
  
  sf_metRes = 1.0;
  sf_metRes_up = 1.0;
  sf_metRes_dn = 1.0;
	sf_metRes_corridor = 1.0;
	sf_metRes_corridor_up = 1.0;
	sf_metRes_corridor_dn = 1.0;
  
  sf_metTTbar = 1.0;
  sf_metTTbar_up = 1.0;
  sf_metTTbar_dn = 1.0;
  
  sf_ttbarSysPt = 1.0;
  sf_ttbarSysPt_up = 1.0;
  sf_ttbarSysPt_dn = 1.0;
  
  sf_ISR = 1.0;
  sf_ISR_up = 1.0;
  sf_ISR_dn = 1.0;
  
  sf_nuPt_up = 1.0;
  sf_nuPt_dn = 1.0;
  
  sf_Wwidth_up = 1.0;
  sf_Wwidth_dn = 1.0;
  
  sf_hfXsec_up = 1.0;
  sf_hfXsec_dn = 1.0;
  
  sf_pdf_up = 1.0;
  sf_pdf_dn = 1.0;

  sf_alphas_up = 1.0;
  sf_alphas_dn = 1.0;
  
  sf_q2_up = 1.0;
  sf_q2_dn = 1.0;
  
  sf_lumi = 1.0;
  sf_lumi_up = 1.0;
  sf_lumi_dn = 1.0;

  sf_pu = 1.0;
  sf_pu_up = 1.0;
  sf_pu_dn = 1.0;
  
  sf_xsec_up = 1.0;
  sf_xsec_dn = 1.0;

  sf_sample = 1.0;

  for(int iSys=0; iSys<sysInfo::k_nSys; iSys++) sys_wgts[iSys]=1.0;
  for(int iSys=0; iSys<sysInfo::k_nSys; iSys++) sys_wgts_corridor[iSys]=1.0;
  for(int iSys=0; iSys<sysInfo::k_nSys; iSys++) sys_wgts_SRbulk[iSys]=1.0;
  for(int iSys=0; iSys<sysInfo::k_nSys; iSys++) sys_wgts_CR2lbulk[iSys]=1.0;
  
  return;
}


//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getEventWeights(bool nominalOnly){
  
  initializeWeights();

  // If sample is data
  if( sample_info->isData ) return;
  
  // If sample is signal scan
  if( sample_info->isSignal ) getSusyMasses( mStop, mLSP );
  
  // Get nEvents
  getNEvents( nEvents );

  // Get xSec
  getXSecWeight( xsec, sf_xsec_up, sf_xsec_dn );  

  // Get Scale1fb*Lumi Wgt
  getScaleToLumiWeight( sf_nominal );

  // get dilepton trigger sf
  getDiLepTriggerWeight( sf_diLepTrigger, sf_diLepTrigger_up, sf_diLepTrigger_dn );

  // get SR trigger sf
  getCR2lTriggerWeight( sf_cr2lTrigger, sf_cr2lTrigger_up, sf_cr2lTrigger_dn );
  
  // btag
  getBTagWeight( 1, sf_bTag, sf_bTagEffHF_up, sf_bTagEffHF_dn, sf_bTagEffLF_up, sf_bTagEffLF_dn, sf_bTag_FS_up, sf_bTag_FS_dn ); 

  // btag, tightWP
  getBTagWeight( 2, sf_bTag_tight, sf_bTagEffHF_tight_up, sf_bTagEffHF_tight_dn, sf_bTagEffLF_tight_up, sf_bTagEffLF_tight_dn, sf_bTag_tight_FS_up, sf_bTag_tight_FS_dn ); 
  
  // lepSFs
  getLepSFWeight( sf_lep, sf_lep_up, sf_lep_dn, sf_lepFS, sf_lepFS_up, sf_lepFS_dn, sf_vetoLep, sf_vetoLep_up, sf_vetoLep_dn );

  // tau SF
  getTauSFWeight( sf_tau, sf_tau_up, sf_tau_dn );
 
  // top pT Reweighting
  getTopPtWeight( sf_topPt, sf_topPt_up, sf_topPt_dn );

  // MET resolution scale factors 
  getMetResWeight( sf_metRes, sf_metRes_up, sf_metRes_dn );
	getMetResWeight_corridor( sf_metRes_corridor, sf_metRes_corridor_up, sf_metRes_corridor_dn );
  
  // MET ttbar scale factors 
  getMetTTbarWeight( sf_metTTbar, sf_metTTbar_up, sf_metTTbar_dn );
  
  // ttbar system pT scale factor 
  getTTbarSysPtSF( sf_ttbarSysPt, sf_ttbarSysPt_up, sf_ttbarSysPt_dn );

  // Lumi Variation
  getLumi( sf_lumi, sf_lumi_up, sf_lumi_dn );

  // ISR Correction
  getISRnJetsWeight( sf_ISR, sf_ISR_up, sf_ISR_dn );

  // Pileup Reweighting
  getPileupWeight( sf_pu, sf_pu_up, sf_pu_dn );
  
  // Sample Scale Factor
  sf_sample = getSampleWeight( sample_info->id );

  // Scale Factors for Uncertainties
  if( !nominalOnly ){

    // Nuetrino pT scale factor
    getNuPtSF( sf_nuPt_up, sf_nuPt_dn );
    
    // W width scale factor
    getWwidthSF( sf_Wwidth_up, sf_Wwidth_dn );
    
    // W+HF xsec uncertainty
    getWJetsHFXSecSF( sf_hfXsec_up, sf_hfXsec_dn );
    
    // PDF Uncertainty
    getPDFWeight( sf_pdf_up, sf_pdf_dn );

    // Alpha Strong, QCD variation
    getAlphasWeight( sf_alphas_up, sf_alphas_dn );
    
    // Q2 Variation, muF, muR
    getQ2Weight( sf_q2_up, sf_q2_dn );
  
  } // end if !nominalOnly

  //
  // Systematic Weights
  //
  double evt_wgt = 1.0;
  
  // This is scale1fb*lumi = lumi*1000*xsec/nEvents
  evt_wgt *= sf_nominal; 
  
  //
  // Switches, set in looper determine if 
  //   these additional SFs are != 1.0
  //
  
  // Apply diLepton Trigger scale factor
  double wgt_diLepTrigger = sf_diLepTrigger;
  evt_wgt *= wgt_diLepTrigger;
  
  // Apply CR2l Trigger scale factor
  double wgt_cr2lTrigger = sf_cr2lTrigger;
  evt_wgt *= wgt_cr2lTrigger;
  
  // Apply bTag scale factor
  double wgt_bTag = sf_bTag;
  evt_wgt *= wgt_bTag;
  
  // Apply lepton scale factor
  double wgt_lep = sf_lep*sf_vetoLep*sf_lepFS;
  evt_wgt *= wgt_lep;

  // Apply tau sf
  double wgt_tau = sf_tau;
  evt_wgt *= wgt_tau;
  
  // Apply top pT sf
  double wgt_topPt = sf_topPt;
  evt_wgt *= wgt_topPt;
  
  // Apply met resolution sf
  double wgt_metRes = sf_metRes;
  evt_wgt *= wgt_metRes;

  // Apply ttbar system pT SF (will be 1 if not ttbar/tW 2l) 
  double wgt_ttbarSysPt = sf_ttbarSysPt;
  evt_wgt *= wgt_ttbarSysPt;
  
  // Apply ISR SF ( switched to ISRnjets )
  double wgt_ISR = sf_ISR;
  evt_wgt *= wgt_ISR;

  // Apply Pileup Wgt
  double wgt_pu = sf_pu;
  evt_wgt *= wgt_pu;
  
  // Apply sample weight (for WJets stitching)
  double wgt_sample = sf_sample;
  evt_wgt *= wgt_sample;
    
  //
  // Systematic Weights
  //
  for(int iSys=0; iSys<k_nSys; iSys++){

    double sys_wgt = evt_wgt;
    
    // Nominal
    if( iSys==k_nominal ){
    }
    
    // JES up
    else if( iSys==k_JESUp ){
    }
      
    // JES dn
    else if( iSys==k_JESDown ){
    }

    // CR2l_bulkTTbar diLepton Trigger, Up
    else if( iSys==k_diLepTriggerUp ){
      sys_wgt *= (sf_diLepTrigger_up/sf_diLepTrigger);
    }

    // CR2l_bulkTTbar diLepton Trigger, Dn
    else if( iSys==k_diLepTriggerDown ){
      sys_wgt *= (sf_diLepTrigger_dn/sf_diLepTrigger);
    }
      
    // CR2l diLepton Trigger, add2ndMetToLep, Up
    else if( iSys==k_cr2lTriggerUp ){
      sys_wgt *= (sf_cr2lTrigger_up/sf_cr2lTrigger);
    }

    // CR2l diLepton Trigger, add2ndMetToLep, Dn
    else if( iSys==k_cr2lTriggerDown ){
      sys_wgt *= (sf_cr2lTrigger_dn/sf_cr2lTrigger);
    }

    // BTagEff HF Up
    else if( iSys==k_bTagEffHFUp ){
      sys_wgt *= (sf_bTagEffHF_up/wgt_bTag);
    }

    // BTagEff HF Dn
    else if( iSys==k_bTagEffHFDown ){
      sys_wgt *= (sf_bTagEffHF_dn/wgt_bTag);
    }

    // BTagEff LF Up
    else if( iSys==k_bTagEffLFUp ){
      sys_wgt *= (sf_bTagEffLF_up/wgt_bTag);
    }

    // BTagEff LF Dn
    else if( iSys==k_bTagEffLFDown ){
      sys_wgt *= (sf_bTagEffLF_dn/wgt_bTag);
    }

    // Lepton SF Up
    else if( iSys==k_lepSFUp ){
      sys_wgt *= (sf_lep_up*sf_vetoLep_up*sf_lepFS)/wgt_lep;
    }

    // Lepton SF Dn
    else if( iSys==k_lepSFDown ){
      sys_wgt *= (sf_lep_dn*sf_vetoLep_dn*sf_lepFS)/wgt_lep;
    }

    // Tau SF Up
    else if( iSys==k_tauSFUp ){
      sys_wgt *= (sf_tau_up)/wgt_tau;
    }

    // Tau SF Dn
    else if( iSys==k_tauSFDown ){
      sys_wgt *= (sf_tau_dn)/wgt_tau;
    }

    // Lepton SF FastSim/FullsSim Up
    else if( iSys==k_lepFSSFUp ){
      sys_wgt *= (sf_lep*sf_vetoLep*sf_lepFS_up)/wgt_lep;
    }

    // Lepton SF Rastsim/FullSim Dn
    else if( iSys==k_lepFSSFDown ){
      sys_wgt *= (sf_lep*sf_vetoLep*sf_lepFS_dn)/wgt_lep;
    }

    // Top pT SF Up
    else if( iSys==k_topPtSFUp ){
      sys_wgt *= (sf_topPt_up/wgt_topPt);
    }

    // Top pT SF Dn
    else if( iSys==k_topPtSFDown ){
      sys_wgt *= (sf_topPt_dn/wgt_topPt);
    }

    // MetRes SF Up
    else if( iSys==k_metResUp ){
      sys_wgt *= sf_metRes_up/wgt_metRes;
    }

    // MetRes SF Dn
    else if( iSys==k_metResDown ){
      sys_wgt *= sf_metRes_dn/wgt_metRes;
    }

    // TTbar/tW System pT Up
    else if( iSys==k_ttbarSysPtUp ){
      sys_wgt *= (sf_ttbarSysPt_up/wgt_ttbarSysPt);
    }

    // TTbar/tW System pT Dn 
    else if( iSys==k_ttbarSysPtDown ){
      sys_wgt *= (sf_ttbarSysPt_dn/wgt_ttbarSysPt);
    }

    // Nu pT SF Up
    else if( iSys==k_nuPtSF_Up ){
      sys_wgt *= sf_nuPt_up;
    }

    // Nu pT SF Dn
    else if( iSys==k_nuPtSF_Down ){
      sys_wgt *= sf_nuPt_dn;
    }

    // W Width SF Up
    else if( iSys==k_WwidthSF_Up ){
      sys_wgt *= sf_Wwidth_up;
    }
      
    // W Width SF Dn
    else if( iSys==k_WwidthSF_Down ){
      sys_wgt *= sf_Wwidth_dn;
    }

    // W+HF XSec Up
    else if( iSys==k_hfXsec_Up ){
      sys_wgt *= sf_hfXsec_up;
    }

    // W+HF XSec Dn
    else if( iSys==k_hfXsec_Down ){
      sys_wgt *= sf_hfXsec_dn;
    }

    // PDF Up
    else if( iSys==k_pdfUp ){
      sys_wgt *= sf_pdf_up;
    }
     
    // PDF Dn
    else if( iSys==k_pdfDown ){
      sys_wgt *= sf_pdf_dn;
    }
      
    // Alpha Strong Up
    else if( iSys==k_alphasUp ){
      sys_wgt *= sf_alphas_up;
    }

    // Alpha Strong Dn
    else if( iSys==k_alphasDown ){
      sys_wgt *= sf_alphas_dn;
    }

    // Q2 Up
    else if( iSys==k_q2Up ){
      sys_wgt *= sf_q2_up;
    }

    // Q2 Dn
    else if( iSys==k_q2Down ){
      sys_wgt *= sf_q2_dn;
    }

    // Lumi Up
    else if( iSys==k_lumiUp ){
      sys_wgt *= sf_lumi_up/sf_lumi;
    }

    // Lumi Dn
    else if( iSys==k_lumiDown ){
      sys_wgt *= sf_lumi_dn/sf_lumi;
    }

    // ISR Up
    else if( iSys==k_ISRUp ){
      sys_wgt *= (sf_ISR_up/wgt_ISR);
    }
      
    // ISR Dn
    else if( iSys==k_ISRDown ){
      sys_wgt *= (sf_ISR_dn/wgt_ISR);
    }

    // XSection Up
    else if( iSys==k_xsecUp ){
      sys_wgt *= (sf_xsec_up/xsec);
    }

    // XSection Dn
    else if( iSys==k_xsecDown ){
      sys_wgt *= (sf_xsec_dn/xsec);
    }
    
    // Pileup Up
    else if( iSys==k_puUp ){
      sys_wgt *= (sf_pu_up/wgt_pu);
    }

    // Pileup Dn
    else if( iSys==k_puDown ){
      sys_wgt *= (sf_pu_dn/wgt_pu);
    }


		// Corridor regions use alternate MET resolution weights
		double wgt_corridor = sys_wgt;
		if(      iSys==k_metResUp   ) wgt_corridor *= sf_metRes_corridor_up / sf_metRes_up;
		else if( iSys==k_metResDown ) wgt_corridor *= sf_metRes_corridor_dn / sf_metRes_dn;
		else wgt_corridor *= sf_metRes_corridor / sf_metRes;

		// Bulk SR uses MET TTbar weights
		double wgt_SRbulk = sys_wgt;
		if(      iSys==k_metTTbarUp   ) wgt_SRbulk *= sf_metTTbar;
		else if( iSys==k_metTTbarDown ) wgt_SRbulk *= sf_metTTbar_up;
		else wgt_SRbulk *= sf_metTTbar;

		// Bulk SR and CR2L both use tight btag SFs in high-Mlb regions
		// Factor in JES when counting tight tags, but NOT when calculating Mlb!
		double wgt_CR2lbulk = sys_wgt;
		double ntighttags = babyAnalyzer.ntightbtags();
		if(      iSys==k_JESUp   ) ntighttags = babyAnalyzer.jup_ntightbtags();
		else if( iSys==k_JESDown ) ntighttags = babyAnalyzer.jdown_ntightbtags();

		if( babyAnalyzer.Mlb_closestb() >= 175. && ntighttags >= 1 ) {
			if( iSys==k_bTagEffHFUp ) {
				wgt_SRbulk   *= sf_bTagEffHF_tight_up / sf_bTagEffHF_up;
				wgt_CR2lbulk *= sf_bTagEffHF_tight_up / sf_bTagEffHF_up;
			}
			else if( iSys==k_bTagEffHFDown ) {
				wgt_SRbulk   *= sf_bTagEffHF_tight_dn / sf_bTagEffHF_dn;
				wgt_CR2lbulk *= sf_bTagEffHF_tight_dn / sf_bTagEffHF_dn;
			}
			else if( iSys==k_bTagEffLFUp ) {
				wgt_SRbulk   *= sf_bTagEffLF_tight_up / sf_bTagEffLF_up;
				wgt_CR2lbulk *= sf_bTagEffLF_tight_up / sf_bTagEffLF_up;
			}
			else if( iSys==k_bTagEffLFDown ) {
				wgt_SRbulk   *= sf_bTagEffLF_tight_dn / sf_bTagEffLF_dn;
				wgt_CR2lbulk *= sf_bTagEffLF_tight_dn / sf_bTagEffLF_dn;
			}
			else {
				wgt_SRbulk   *= sf_bTag_tight / sf_bTag;
				wgt_CR2lbulk *= sf_bTag_tight / sf_bTag;
			}
		}

    // Fill Array Element
    sys_wgts[iSys] = sys_wgt;
		sys_wgts_corridor[iSys] = wgt_corridor;
		sys_wgts_SRbulk[iSys] = wgt_SRbulk;
		sys_wgts_CR2lbulk[iSys] = wgt_CR2lbulk;


    // Break if only filling nominal
    if( nominalOnly &&
	iSys==k_nominal ) break;
    

  } // end loop over systematics


  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getSusyMasses( int &mStop, int &mLSP ){

  mStop = 0;
  mLSP  = 0;
  //mChargino = 0;

  if( sample_info->isSignal ){
    mStop     = babyAnalyzer.mass_stop();
    mLSP      = babyAnalyzer.mass_lsp();
    //mChargino = babyAnalyzer.mass_chargino();
  }

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getNEvents( int &nEvts ){

  nEvts = 1;

  if( sample_info->isSignal ){

    getSusyMasses(mStop,mLSP);

    nEvts = (int)h_sig_counter_nEvents->GetBinContent(h_sig_counter->FindBin(mStop,mLSP));
  }
  else{
    nEvts = h_bkg_counter->GetBinContent(22);
  }

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getScaleToLumiWeight( double &wgt ){

  wgt = 1.0;

  if( sample_info->isData ) return;

  if( sample_info->isSignal ){
    getSusyMasses(mStop,mLSP);
    getXSecWeight( xsec, sf_xsec_up, sf_xsec_dn );  
    getNEvents( nEvents );
    wgt = lumi*1000.0*xsec/(double)nEvents;
  }
  else{
    wgt = babyAnalyzer.scale1fb()*lumi;
  }

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getDiLepTriggerWeight( double &wgt_trigger, double &wgt_trigger_up, double &wgt_trigger_dn ){

  wgt_trigger = 1.0;
  wgt_trigger_up = 1.0;
  wgt_trigger_dn = 1.0;

  if( !apply_diLepTrigger_sf ) return;

  if( sample_info->isData ) return;

  double sf_val = 1.0;
  double sf_err = 0.0;

  // DiElectron Trigger
  if( abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==22 ){
    sf_val = 0.868705; // 35.876fb, reMiniAOD
    sf_err = 0.00457008;
    //sf_val = 0.869221; // 36.46fb, updated JECs
    //sf_err = 0.00452205;
    //sf_val = 0.869669; // 36.46fb
    //sf_err = 0.00456458;
    //sf_val = 0.884591; // 29.53fb
    //sf_err = 0.00811308;
    //sf_val = 0.883481; // 12.9fb ICHEP
    //sf_err = 0.012322;
  }

  // MuE Trigger
  if( abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==24 ){
    sf_val = 0.862895; // 35.876fb, reMiniAOD
    sf_err = 0.00204966;
    //sf_val = 0.86275; // 36.46fb, updated JECs
    //sf_err = 0.00207544;
    //sf_val = 0.86165; // 36.46fb
    //sf_err = 0.00255978;
    //sf_val = 0.908511; // 29.53fb
    //sf_err = 0.00420534;
    //sf_val = 0.893801; // 12.9fb ICHEP
    //sf_err = 0.00657751;
  }

  // DiMuon Trigger
  if( abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==26 ){
    sf_val = 0.804283; // 35.876fb, reMiniAOD
    sf_err = 0.00266679;
    //sf_val = 0.813382; // 36.46fb, updated JECs
    //sf_err = 0.00295138;
    //sf_val = 0.819581; // 36.46fb
    //sf_err = 0.00406059;
    //sf_val = 0.858291; // 29.53fb
    //sf_err = 0.00666499;
    //sf_val = 0.841817; // 12.9fb ICHEP
    //sf_err = 0.0102116;
  }

  // Calculate Scale Factor
  wgt_trigger    = sf_val;
  wgt_trigger_up = (sf_val + sf_err );
  wgt_trigger_dn = (sf_val - sf_err );
  
  return;

}

//////////////////////////////////////////////////////////////////////
/*
void sysInfo::evtWgtInfo::getCR2lTriggerWeight( double &wgt_trigger, double &wgt_trigger_up, double &wgt_trigger_dn ){

  wgt_trigger = 1.0;
  wgt_trigger_up = 1.0;
  wgt_trigger_dn = 1.0;

  if( !apply_cr2lTrigger_sf ) return;

  if( sample_info->isData ) return;

  if( !add2ndLepToMet ) return;

  // Flag for 1 reco lepton events, since there should be no difference
  //  in the two variables since pfmet_rl is initialized with pfmet
  double eps=0.001;
  if( babyAnalyzer.pfmet()<(babyAnalyzer.pfmet_rl()+eps) &&
      babyAnalyzer.pfmet()>(babyAnalyzer.pfmet_rl()-eps)    ) return;

  double sf_val = 1.0;
  double sf_err = 0.0;

  double met = babyAnalyzer.pfmet_rl();
  double max_met = 499.0;
  double min_met = 251.0;

  double lep_pt = babyAnalyzer.lep1_p4().Pt();
  double max_lep = 199.0;
  if(met>401.0) max_lep = 499.0;
  double min_lep = 21.0;
 
  // Blank spots on map
  if( met>249.0 && met<276.0 && 
      lep_pt>19.0 && lep_pt<30.1 ){
    sf_val = 0.93;
  }
  else if( met>299.0 && met<351.0 &&
	   lep_pt>19.0 && lep_pt<50.1 ){
    sf_val = 0.94;
  }
  else if( met>349.0 &&
	   lep_pt>29.0 && lep_pt<50.1 ){
    sf_val = 0.95;
  }
  // Grab bin
  else{
    int binX = h_cr2lTrigger_sf->GetXaxis()->FindBin( std::min( std::max(met,min_met), max_met ) );
    int binY = h_cr2lTrigger_sf->GetYaxis()->FindBin( std::min( std::max(lep_pt,min_lep), max_lep ) );
    sf_val = h_cr2lTrigger_sf->GetBinContent( binX,binY );
  }

  // 7% error for full coverage of trigger
  sf_err = 0.07;
 
  wgt_trigger = sf_val;
  wgt_trigger_up = sf_val + sf_err;
  wgt_trigger_dn = sf_val - sf_err;

  return;
}

//////////////////////////////////////////////////////////////////////
*/

void sysInfo::evtWgtInfo::getCR2lTriggerWeight( double &wgt_trigger, double &wgt_trigger_up, double &wgt_trigger_dn ){

  wgt_trigger = 1.0;
  wgt_trigger_up = 1.0;
  wgt_trigger_dn = 1.0;

  if( !apply_cr2lTrigger_sf ) return;

  if( sample_info->isData ) return;

  if( !add2ndLepToMet ) return;

  // Flag for 1 reco lepton events, since there should be no difference
  //  in the two variables since pfmet_rl is initialized with pfmet
  double eps=0.001;
  if( babyAnalyzer.pfmet()<(babyAnalyzer.pfmet_rl()+eps) &&
      babyAnalyzer.pfmet()>(babyAnalyzer.pfmet_rl()-eps)    ) return;

  double sf_val    = 1.0;
  double sf_err_up = 0.0;
  double sf_err_dn = 0.0;

  double met = babyAnalyzer.pfmet_rl();
  double max_met = 499.9;
  double min_met = 250.1;
  met = std::min( std::max(met,min_met), max_met );

  double lep_pt = babyAnalyzer.lep1_p4().Pt();
  double max_lep = 49.9;
  double min_lep = 20.1;
  lep_pt = std::min( std::max(lep_pt,min_lep), max_lep );

  if( abs(babyAnalyzer.lep1_pdgid())==11 ){
    int bin   = h_cr2lTrigger_sf_el->FindFixBin( lep_pt, met );
    sf_val    = h_cr2lTrigger_sf_el->GetEfficiency( bin );
    sf_err_up = h_cr2lTrigger_sf_el->GetEfficiencyErrorUp( bin );
    sf_err_dn = h_cr2lTrigger_sf_el->GetEfficiencyErrorLow( bin );
  }
  if( abs(babyAnalyzer.lep1_pdgid())==13 ){
    int bin   = h_cr2lTrigger_sf_mu->FindFixBin( lep_pt, met );
    sf_val    = h_cr2lTrigger_sf_mu->GetEfficiency( bin );
    sf_err_up = h_cr2lTrigger_sf_mu->GetEfficiencyErrorUp( bin );
    sf_err_dn = h_cr2lTrigger_sf_mu->GetEfficiencyErrorLow( bin );
  }
 
  wgt_trigger = sf_val;
  wgt_trigger_up = sf_val + sf_err_up;
  wgt_trigger_dn = sf_val - sf_err_dn;

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getBTagWeight( int WP, double &wgt_btagsf, double &wgt_btagsf_hf_up, double &wgt_btagsf_hf_dn, double &wgt_btagsf_lf_up, double &wgt_btagsf_lf_dn, double &wgt_btagsf_fs_up, double &wgt_btagsf_fs_dn ){

  // Working Point, WP = {0, 1, 2} = {loose, medium, tight}
  wgt_btagsf       = 1.0;
  wgt_btagsf_hf_up = 1.0;
  wgt_btagsf_hf_dn = 1.0;
  wgt_btagsf_lf_up = 1.0;
  wgt_btagsf_lf_dn = 1.0;
  wgt_btagsf_fs_up = 1.0;
  wgt_btagsf_fs_dn = 1.0;

  
  if( !apply_bTag_sf ) return;

  if( WP<0 || WP>2 ) return;

  // IF deriving SFs on the Looper level
  if( useBTagSFs_fromFiles ){
    getBTagWeight_fromFiles( WP, wgt_btagsf, wgt_btagsf_hf_up, wgt_btagsf_hf_dn, wgt_btagsf_lf_up, wgt_btagsf_lf_dn, wgt_btagsf_fs_up, wgt_btagsf_fs_dn ); 
  }

  // Else if taking SFs from babies
  else{

    // Loose WP
    if( WP==0 ){
      wgt_btagsf       = babyAnalyzer.weight_loosebtagsf();
      wgt_btagsf_hf_up = babyAnalyzer.weight_loosebtagsf_heavy_UP();
      wgt_btagsf_hf_dn = babyAnalyzer.weight_loosebtagsf_heavy_DN();
      wgt_btagsf_lf_up = babyAnalyzer.weight_loosebtagsf_light_UP();
      wgt_btagsf_lf_dn = babyAnalyzer.weight_loosebtagsf_light_DN();
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up = babyAnalyzer.weight_loosebtagsf_fastsim_UP();
	wgt_btagsf_fs_dn = babyAnalyzer.weight_loosebtagsf_fastsim_DN();
      }
    } // end if Loose WP

    // Medium WP
    if( WP==1 ){
      wgt_btagsf       = babyAnalyzer.weight_btagsf();
      wgt_btagsf_hf_up = babyAnalyzer.weight_btagsf_heavy_UP();
      wgt_btagsf_hf_dn = babyAnalyzer.weight_btagsf_heavy_DN();
      wgt_btagsf_lf_up = babyAnalyzer.weight_btagsf_light_UP();
      wgt_btagsf_lf_dn = babyAnalyzer.weight_btagsf_light_DN();
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up = babyAnalyzer.weight_btagsf_fastsim_UP();
	wgt_btagsf_fs_dn = babyAnalyzer.weight_btagsf_fastsim_DN();
      }
    } // end if Medium WP

    // Tight WP
    if( WP==2 ){
      wgt_btagsf       = babyAnalyzer.weight_tightbtagsf();
      wgt_btagsf_hf_up = babyAnalyzer.weight_tightbtagsf_heavy_UP();
      wgt_btagsf_hf_dn = babyAnalyzer.weight_tightbtagsf_heavy_DN();
      wgt_btagsf_lf_up = babyAnalyzer.weight_tightbtagsf_light_UP();
      wgt_btagsf_lf_dn = babyAnalyzer.weight_tightbtagsf_light_DN();
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up = babyAnalyzer.weight_tightbtagsf_fastsim_UP();
	wgt_btagsf_fs_dn = babyAnalyzer.weight_tightbtagsf_fastsim_DN();
      }
    } // end if Tight WP

  } // end if taking btag SFs from babies
  
  
  // Normalization
  getNEvents( nEvents );

  // Signal Sample Normalization
  if( sample_info->isSignal ){
    getSusyMasses(mStop,mLSP);

    // Loose WP Signal Normalization
    if( WP==0 ){
      wgt_btagsf       *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,44)) );
      wgt_btagsf_hf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,45)) );
      wgt_btagsf_hf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,47)) );
      wgt_btagsf_lf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,46)) );
      wgt_btagsf_lf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,48)) );
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,49)) );
	wgt_btagsf_fs_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,50)) );
      }
    } // end if Loose WP


    // Medium WP Signal Normalization
    if( WP==1 ){
      wgt_btagsf       *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,14)) );
      wgt_btagsf_hf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,15)) );
      wgt_btagsf_hf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,17)) );
      wgt_btagsf_lf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,16)) );
      wgt_btagsf_lf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,18)) );
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,22)) );
	wgt_btagsf_fs_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,23)) );
      }
    } // end if Medium WP

    // Tight WP Signal Normalization
    if( WP==2 ){
      wgt_btagsf       *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,37)) );
      wgt_btagsf_hf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,38)) );
      wgt_btagsf_hf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,40)) );
      wgt_btagsf_lf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,39)) );
      wgt_btagsf_lf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,41)) );
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,42)) );
	wgt_btagsf_fs_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,43)) );
      }
    } // end if Tight WP

  } // end if normalizing signal

  // Background Sample Normalization
  else{

    // Loose WP Bkg Normalization
    if( WP==0 ){
      wgt_btagsf       *= ( nEvents / h_bkg_counter->GetBinContent(44) );
      wgt_btagsf_hf_up *= ( nEvents / h_bkg_counter->GetBinContent(45) );
      wgt_btagsf_hf_dn *= ( nEvents / h_bkg_counter->GetBinContent(47) );
      wgt_btagsf_lf_up *= ( nEvents / h_bkg_counter->GetBinContent(46) );
      wgt_btagsf_lf_dn *= ( nEvents / h_bkg_counter->GetBinContent(48) );
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up *= ( nEvents / h_bkg_counter->GetBinContent(49) );
	wgt_btagsf_fs_dn *= ( nEvents / h_bkg_counter->GetBinContent(50) );
      }
    } // end if Loose WP

    // Medium WP Bkg Normalization
    if( WP==1 ){
      wgt_btagsf       *= ( nEvents / h_bkg_counter->GetBinContent(14) );
      wgt_btagsf_hf_up *= ( nEvents / h_bkg_counter->GetBinContent(15) );
      wgt_btagsf_hf_dn *= ( nEvents / h_bkg_counter->GetBinContent(17) );
      wgt_btagsf_lf_up *= ( nEvents / h_bkg_counter->GetBinContent(16) );
      wgt_btagsf_lf_dn *= ( nEvents / h_bkg_counter->GetBinContent(18) );
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up *= ( nEvents / h_bkg_counter->GetBinContent(23) );
	wgt_btagsf_fs_dn *= ( nEvents / h_bkg_counter->GetBinContent(24) );
      }
    } // end if Medium WP

    // Tight WP Bkg Normalization
    if( WP==2 ){
      wgt_btagsf       *= ( nEvents / h_bkg_counter->GetBinContent(37) );
      wgt_btagsf_hf_up *= ( nEvents / h_bkg_counter->GetBinContent(38) );
      wgt_btagsf_hf_dn *= ( nEvents / h_bkg_counter->GetBinContent(40) );
      wgt_btagsf_lf_up *= ( nEvents / h_bkg_counter->GetBinContent(39) );
      wgt_btagsf_lf_dn *= ( nEvents / h_bkg_counter->GetBinContent(41) );
      
      if( sample_info->isFastsim ){
	wgt_btagsf_fs_up *= ( nEvents / h_bkg_counter->GetBinContent(42) );
	wgt_btagsf_fs_dn *= ( nEvents / h_bkg_counter->GetBinContent(43) );
      }
    } // end if Tight WP

  } // end if normalizing bkg
  
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getBTagWeight_tightWP( double &wgt_btagsf_tight, double &wgt_btagsf_hf_tight_up, double &wgt_btagsf_hf_tight_dn, double &wgt_btagsf_lf_tight_up, double &wgt_btagsf_lf_tight_dn, double &wgt_btagsf_tight_fs_up, double &wgt_btagsf_tight_fs_dn ){

  wgt_btagsf_tight       = 1.0;
  wgt_btagsf_hf_tight_up = 1.0;
  wgt_btagsf_hf_tight_dn = 1.0;
  wgt_btagsf_lf_tight_up = 1.0;
  wgt_btagsf_lf_tight_dn = 1.0;
  wgt_btagsf_tight_fs_up = 1.0;
  wgt_btagsf_tight_fs_dn = 1.0;

  if( !apply_bTag_sf ) return;

  if( useBTagSFs_fromFiles ){
    getBTagWeight_fromFiles( 2, wgt_btagsf_tight, wgt_btagsf_hf_tight_up, wgt_btagsf_hf_tight_dn, wgt_btagsf_lf_tight_up, wgt_btagsf_lf_tight_dn, wgt_btagsf_tight_fs_up, wgt_btagsf_tight_fs_dn ); 
  }
  else{
    wgt_btagsf_tight       = babyAnalyzer.weight_tightbtagsf();
    wgt_btagsf_hf_tight_up = babyAnalyzer.weight_tightbtagsf_heavy_UP();
    wgt_btagsf_hf_tight_dn = babyAnalyzer.weight_tightbtagsf_heavy_DN();
    wgt_btagsf_lf_tight_up = babyAnalyzer.weight_tightbtagsf_light_UP();
    wgt_btagsf_lf_tight_dn = babyAnalyzer.weight_tightbtagsf_light_DN();
    
    if( sample_info->isFastsim ){
      wgt_btagsf_tight_fs_up = babyAnalyzer.weight_tightbtagsf_fastsim_UP();
      wgt_btagsf_tight_fs_dn = babyAnalyzer.weight_tightbtagsf_fastsim_DN();
    }
  }
  
  // Normalization
  getNEvents( nEvents );
  
  if( sample_info->isSignal ){
    getSusyMasses(mStop,mLSP);
  
    wgt_btagsf_tight       *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,37)) );
    wgt_btagsf_hf_tight_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,38)) );
    wgt_btagsf_hf_tight_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,40)) );
    wgt_btagsf_lf_tight_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,39)) );
    wgt_btagsf_lf_tight_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,41)) );

    if( sample_info->isFastsim ){
      wgt_btagsf_tight_fs_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,42)) );
      wgt_btagsf_tight_fs_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,43)) );
    }
  }
  else{
    wgt_btagsf_tight       *= ( nEvents / h_bkg_counter->GetBinContent(37) );
    wgt_btagsf_hf_tight_up *= ( nEvents / h_bkg_counter->GetBinContent(38) );
    wgt_btagsf_hf_tight_dn *= ( nEvents / h_bkg_counter->GetBinContent(40) );
    wgt_btagsf_lf_tight_up *= ( nEvents / h_bkg_counter->GetBinContent(39) );
    wgt_btagsf_lf_tight_dn *= ( nEvents / h_bkg_counter->GetBinContent(41) );

    if( sample_info->isFastsim ){
      wgt_btagsf_tight_fs_up *= ( nEvents / h_bkg_counter->GetBinContent(42) );
      wgt_btagsf_tight_fs_dn *= ( nEvents / h_bkg_counter->GetBinContent(43) );
    }
  }
  
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getBTagWeight_fromFiles( int WP, double &wgt_btagsf, double &wgt_btagsf_hf_up, double &wgt_btagsf_hf_dn, double &wgt_btagsf_lf_up, double &wgt_btagsf_lf_dn, double &wgt_btagsf_fs_up, double &wgt_btagsf_fs_dn ){

  vector< double > jet_pt;
  vector< double > jet_eta;
  vector< double > jet_deepCSV;
  vector< int >    jet_flavour;
  

  for(int iJet=0; iJet<(int)babyAnalyzer.ak4pfjets_p4().size(); iJet++){
    jet_pt.push_back( (double)babyAnalyzer.ak4pfjets_p4().at(iJet).Pt() );
    jet_eta.push_back( (double)babyAnalyzer.ak4pfjets_p4().at(iJet).Eta() );
    jet_deepCSV.push_back( (double)babyAnalyzer.ak4pfjets_deepCSV().at(iJet) );
    jet_flavour.push_back( (int)abs(babyAnalyzer.ak4pfjets_hadron_flavor().at(iJet)) );
  }
  
  bTagSFUtil->getBTagWeight( WP, jet_pt, jet_eta, jet_deepCSV, jet_flavour, wgt_btagsf, wgt_btagsf_hf_up, wgt_btagsf_hf_dn, wgt_btagsf_lf_up, wgt_btagsf_lf_dn, wgt_btagsf_fs_up, wgt_btagsf_fs_dn );

  return;

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getLepSFWeight( double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepFSSF, double &weight_lepFSSF_Up, double &weight_lepFSSF_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn ){

  weight_lepSF = 1.0;
  weight_lepSF_Up = 1.0;
  weight_lepSF_Dn = 1.0;
  weight_lepFSSF = 1.0;
  weight_lepFSSF_Up = 1.0;
  weight_lepFSSF_Dn = 1.0;
  weight_vetoLepSF = 1.0;
  weight_vetoLepSF_Up = 1.0;
  weight_vetoLepSF_Dn = 1.0;

  if( !apply_lep_sf && !apply_vetoLep_sf && !apply_lepFS_sf ) return;
  
  if( useLepSFs_fromFiles ){
    getLepSFWeight_fromFiles( weight_lepSF, weight_lepSF_Up, weight_lepSF_Dn, weight_lepFSSF, weight_lepFSSF_Up, weight_lepFSSF_Dn, weight_vetoLepSF, weight_vetoLepSF_Up, weight_vetoLepSF_Dn );
  }
  else{
    weight_lepSF = babyAnalyzer.weight_lepSF();
    weight_lepSF_Up = babyAnalyzer.weight_lepSF_up();
    weight_lepSF_Dn = babyAnalyzer.weight_lepSF_down();
    
    weight_vetoLepSF = babyAnalyzer.weight_vetoLepSF();
    weight_vetoLepSF_Up = babyAnalyzer.weight_vetoLepSF_up();
    weight_vetoLepSF_Dn = babyAnalyzer.weight_vetoLepSF_down();
    
    if( sample_info->isFastsim ){
      weight_lepFSSF = babyAnalyzer.weight_lepSF_fastSim();
      weight_lepFSSF_Up = babyAnalyzer.weight_lepSF_fastSim_up();
      weight_lepFSSF_Dn = babyAnalyzer.weight_lepSF_fastSim_down();
    }

    // Normalization
    getNEvents( nEvents );
    
    if( sample_info->isSignal ){
      getSusyMasses(mStop,mLSP);
      
      weight_lepSF    *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,27)) );
      weight_lepSF_Up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,28)) );
      weight_lepSF_Dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,29)) );
      
      weight_vetoLepSF    *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,30)) );
      weight_vetoLepSF_Up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,31)) );
      weight_vetoLepSF_Dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,32)) );
      
      if( sample_info->isFastsim ){
	weight_lepFSSF    *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,33)) );
	weight_lepFSSF_Up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,34)) );
	weight_lepFSSF_Dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,35)) );
      }
    }
    else{
      weight_lepSF    *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(28)) );
      weight_lepSF_Up *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(29)) );
      weight_lepSF_Dn *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(30)) );
      
      weight_vetoLepSF    *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(31)) );
      weight_vetoLepSF_Up *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(32)) );
      weight_vetoLepSF_Dn *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(33)) );

      if( sample_info->isFastsim ){
	weight_lepFSSF    *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(34)) );
	weight_lepFSSF_Up *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(35)) );
	weight_lepFSSF_Dn *= ( nEvents / h_bkg_counter->GetBinContent(h_bkg_counter->FindBin(36)) );
      }
    
    }
  }

  
  if( !apply_lep_sf ){
    weight_lepSF = 1.0;
    weight_lepSF_Up = 1.0;
    weight_lepSF_Dn = 1.0;
  }
  if( !apply_vetoLep_sf ){
    weight_vetoLepSF = 1.0;
    weight_vetoLepSF_Up = 1.0;
    weight_vetoLepSF_Dn = 1.0;
  }
  if( !apply_lepFS_sf || !sample_info->isFastsim ){
    weight_lepFSSF = 1.0;
    weight_lepFSSF_Up = 1.0;
    weight_lepFSSF_Dn = 1.0;
  }
  
  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getLepSFWeight_fromFiles( double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepFSSF, double &weight_lepFSSF_Up, double &weight_lepFSSF_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn ){

  weight_lepSF = 1.0;
  weight_lepSF_Up = 1.0;
  weight_lepSF_Dn = 1.0;
  weight_lepFSSF = 1.0;
  weight_lepFSSF_Up = 1.0;
  weight_lepFSSF_Dn = 1.0;
  weight_vetoLepSF = 1.0;
  weight_vetoLepSF_Up = 1.0;
  weight_vetoLepSF_Dn = 1.0;

  if( sample_info->isData ) return;

  std::vector< double > recoLep_pt, recoLep_eta, genLostLep_pt, genLostLep_eta;
  std::vector< int > recoLep_pdgid, genLostLep_pdgid;
  std::vector< bool > recoLep_isSel;

  double matched_dr = 0.1;
  
  if( babyAnalyzer.nvetoleps()>=1 ){
    recoLep_pt.push_back( babyAnalyzer.lep1_p4().Pt() );
    recoLep_eta.push_back( babyAnalyzer.lep1_p4().Eta() );
    recoLep_pdgid.push_back( babyAnalyzer.lep1_pdgid() );
    if( ( (abs(babyAnalyzer.lep1_pdgid())==13 && 
	   babyAnalyzer.lep1_passMediumID()      ) ||
	  (abs(babyAnalyzer.lep1_pdgid())==11 && 
	   babyAnalyzer.lep1_passMediumID()      )    ) &&
	( babyAnalyzer.lep1_p4().Pt()>20.0            ) &&
        ( fabs(babyAnalyzer.lep1_p4().Eta())<2.4      )    ){
      recoLep_isSel.push_back( true );
    }
    else{
      recoLep_isSel.push_back( false );
    }
  
  
    if(babyAnalyzer.nvetoleps()>=2){
      recoLep_pt.push_back( babyAnalyzer.lep2_p4().Pt() );
      recoLep_eta.push_back( babyAnalyzer.lep2_p4().Eta() );
      recoLep_pdgid.push_back( babyAnalyzer.lep2_pdgid() );
      if( ( (abs(babyAnalyzer.lep2_pdgid())==13 && 
	   babyAnalyzer.lep2_passMediumID()      ) ||
	  (abs(babyAnalyzer.lep2_pdgid())==11 && 
	   babyAnalyzer.lep2_passMediumID()      )    ) &&
	( babyAnalyzer.lep2_p4().Pt()>20.0            ) &&
        ( fabs(babyAnalyzer.lep2_p4().Eta())<2.4      )    ){
	recoLep_isSel.push_back( true );
      }
      else{
	recoLep_isSel.push_back( false );
      }

    } // end if >=2 vetoLeptons
  
  } // end if >=1 vetoLeptons


  // Find Gen Lost lepton
  if( babyAnalyzer.is2lep() && babyAnalyzer.nvetoleps()==1 ){

    // Find gen lepton matched to reco lepton
    for(int iGen=0; iGen<(int)babyAnalyzer.genleps_p4().size(); iGen++){

      if( abs(babyAnalyzer.genleps_id().at(iGen))!=11 && abs(babyAnalyzer.genleps_id().at(iGen))!=13 ) continue;
      if( !babyAnalyzer.genleps_fromHardProcessFinalState().at(iGen) ) continue;
      if( !babyAnalyzer.genleps_isLastCopy().at(iGen) ) continue;
      if( ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.genleps_p4().at(iGen), babyAnalyzer.lep1_p4())<matched_dr ) continue;
      if( babyAnalyzer.genleps_p4().at(iGen).Pt()<5 || fabs(babyAnalyzer.genleps_p4().at(iGen).Eta())>2.4 ) continue;
	  
      genLostLep_pt.push_back( babyAnalyzer.genleps_p4().at(iGen).Pt() );
      genLostLep_eta.push_back( babyAnalyzer.genleps_p4().at(iGen).Eta() );
      genLostLep_pdgid.push_back( babyAnalyzer.genleps_id().at(iGen) );
    
    } // end loop over genleps

  } // end if lostLep event

  lepSFUtil->getLepWeight( recoLep_pt, recoLep_eta, recoLep_pdgid, recoLep_isSel, genLostLep_pt, genLostLep_eta, genLostLep_pdgid, weight_lepSF, weight_lepSF_Up, weight_lepSF_Dn, weight_lepFSSF, weight_lepFSSF_Up, weight_lepFSSF_Dn, weight_vetoLepSF, weight_vetoLepSF_Up, weight_vetoLepSF_Dn );
  

  return;

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getTauSFWeight( double &weight_tau, double &weight_tau_up, double &weight_tau_dn ){

  weight_tau = 1.0;
  weight_tau_up = 1.0;
  weight_tau_dn = 1.0;
  
  if( !apply_tau_sf ) return;
  
  if( sample_info->isData ) return;

  if( !babyAnalyzer.is2lep() ) return;

  // Check if there is had tau in event
  for(int iGen=0; iGen<(int)babyAnalyzer.genleps_p4().size(); iGen++){
    if( abs(babyAnalyzer.genleps_id().at(iGen))!=15 ) continue; // Looking for a tau
    if( !babyAnalyzer.genleps_isLastCopy().at(iGen) ) continue; // Must be last copy in truth history
    if( !babyAnalyzer.genleps_fromHardProcessFinalState().at(iGen) && !babyAnalyzer.genleps_fromHardProcessDecayed().at(iGen) ) continue; // Must be from hard process
    if( babyAnalyzer.genleps_gentaudecay().at(iGen)!=3 && babyAnalyzer.genleps_gentaudecay().at(iGen)!=4 ) continue; // Must be hadronically decaying
    if( babyAnalyzer.genleps_p4().at(iGen).Pt()<20.0 ) continue; // Must be in pT acceptance
    if( fabs(babyAnalyzer.genleps_p4().at(iGen).Eta())>2.3 ) continue; // Must be in eta acceptance

    // Get reco tau eff
    int binX = h_recoEff_tau->GetXaxis()->FindBin( babyAnalyzer.genleps_p4().at(iGen).Pt() );
    int binY = h_recoEff_tau->GetYaxis()->FindBin( fabs(babyAnalyzer.genleps_p4().at(iGen).Eta()) );
    double eff = h_recoEff_tau->GetBinContent( binX, binY );

    double sf = 0.91;
    double sf_up = 0.91+0.05;
    double sf_dn = 0.91-0.05;

    if( eff>0.0 ){
      // If passes tau filter, means tau was lost
      if( babyAnalyzer.PassTauVeto() && babyAnalyzer.PassTrackVeto() ){
	weight_tau = (1.0-(eff*sf))/(1.0-eff);
	weight_tau_up = (1.0-(eff*sf_up))/(1.0-eff);
	weight_tau_dn = (1.0-(eff*sf_dn))/(1.0-eff);
      }
      // Else, tau was found
      else if( !babyAnalyzer.PassTauVeto() && babyAnalyzer.PassTrackVeto() ){
	weight_tau = sf;
	weight_tau_up = sf_up;
	weight_tau_dn = sf_dn;
      }
    } // end if eff>0.0	
  } // end loop over gen leps  

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getTopPtWeight( double &weight_topPt, double &weight_topPt_up, double &weight_topPt_dn ){

  weight_topPt    = 1.0;
  weight_topPt_up = 1.0;
  weight_topPt_dn = 1.0;

  if( sample_info->isData ) return;

  if( sample_info->id != sampleInfo::k_ttbar_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_powheg_pythia8_ext4 &&
      sample_info->id != sampleInfo::k_ttbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ) return;
  
  
  double genTopPt    = 0.0;
  double genTopBarPt = 0.0;
  double nTopsFound = 0;
  for(int iTop=0; iTop<(int)babyAnalyzer.genqs_p4().size(); iTop++){
    if(!babyAnalyzer.genqs_isLastCopy().at(iTop)) continue;
    if(babyAnalyzer.genqs_id().at(iTop)==6){
      genTopPt = babyAnalyzer.genqs_p4().at(iTop).Pt();
      nTopsFound++;
    }
    if(babyAnalyzer.genqs_id().at(iTop)==-6){
      genTopBarPt = babyAnalyzer.genqs_p4().at(iTop).Pt();
      nTopsFound++;
    }
  }

  if( !(genTopPt>0.0) )    cout << "    Did not find gen top for top pT reweighting" << endl;
  if( !(genTopBarPt>0.0) ) cout << "    Did not find gen topBar for top pT reweighting" << endl;
  if( nTopsFound!=2 )      cout << "    Did not find 2 tops for top pT reweighting, nFound=" << nTopsFound << endl;


  double weight_temp = topPtWeight(genTopPt, genTopBarPt);

  
  if( apply_topPt_sf ){
    weight_topPt    = weight_temp;
    weight_topPt_up = ( ((weight_temp-1.0)*2.0)+1.0 );
    weight_topPt_dn = 1.0;
  }
  // if !apply_topPt_sf still use as uncertainty
  else{
    weight_topPt    = 1.0;
    weight_topPt_up = weight_temp;
    weight_topPt_dn = 1.0;
  }


  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getMetResWeight( double &weight_metRes, double &weight_metRes_up, double &weight_metRes_dn ){

  weight_metRes    = 1.0;
  weight_metRes_up = 1.0;
  weight_metRes_dn = 1.0;

  if(!apply_metRes_sf) return;


  double sf_val = 1.0;
  double sf_err = 0.0;
  
  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  // ttbar, tW
  if( sample_info->id != sampleInfo::k_ttbar_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_powheg_pythia8_ext4 &&
      sample_info->id != sampleInfo::k_ttbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu &&
      sample_info->id != sampleInfo::k_WJetsToLNu_amcnlo_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WNJetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W1JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_madgraph_pythia8 && 
      sample_info->id != sampleInfo::k_W1JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_NuPt200_madgraph_pythia8
      ) return;
  

  // 2lep events only
  //if( !babyAnalyzer.is2lep() ) return;



  // nJets bin
  int nJets = babyAnalyzer.ngoodjets();  
  //in case of evaluating for JES variatione events, use nominal nJets, is <2, then use 2jet 
  if( nJets<2 ) nJets = 2;

  
  // modTopness bin
  double modTop = babyAnalyzer.topnessMod();
  if( add2ndLepToMet ) modTop = babyAnalyzer.topnessMod_rl();

  
  // mlb bin
  double mlb = babyAnalyzer.Mlb_closestb();
  int nMedBTags = babyAnalyzer.ngoodbtags();
  
  int nTightTags = babyAnalyzer.ntightbtags();

  bool is0b = ( (nMedBTags==0) || (nMedBTags>=1 && nTightTags==0 && mlb>175.0) );
  if( is0b ) mlb = ( babyAnalyzer.lep1_p4() + babyAnalyzer.ak4pfjets_leadbtag_p4() ).M();
 

  // Met bin
  double met = babyAnalyzer.pfmet();
  if(add2ndLepToMet) met = babyAnalyzer.pfmet_rl();
  
  // in case of evaluating for JES variation events, then use nominal pfmet, and if nominal<250, use lowest met bin
  if( met<250.0 ) met = 250.0;
  

  
  
  
  //
  // Find SF
  //

  // Region A
  if( nJets<4 && modTop>=10 && mlb<175 ){
  
    if( met>=250.0 && met<350.0 ){
      sf_val = 0.99;
      sf_err = 0.01;
      //sf_val = 0.98; // SUS-16-051 preapproval
      //sf_err = 0.01;
    }
  
    if( met>=350.0 && met<450.0 ){
      sf_val = 1.04;
      sf_err = 0.01;
      //sf_val = 1.07;
      //sf_err = 0.01;
    }
  
    if( met>=450.0 && met<600.0 ){
      sf_val = 1.11;
      sf_err = 0.01;
      //sf_val = 1.14;
      //sf_err = 0.02;
    }
  
    if( met>=600.0 ){
      sf_val = 1.17;
      sf_err = 0.03;
      //sf_val = 1.24;
      //sf_err = 0.03;
    }
    
  } // end if region A


  // Region B
  if( nJets<4 && modTop>=10 && mlb>=175 ){
  
    if( met>=250.0 && met<450.0 ){
      sf_val = 1.00;
      sf_err = 0.01;
      //sf_val = 0.99;
      //sf_err = 0.00;
    }
    
    if( met>=450.0 && met<600.0 ){
      sf_val = 1.11;
      sf_err = 0.01;
      //sf_val = 1.14;
      //sf_err = 0.02;
    }
  
    if( met>=600.0 ){
      sf_val = 1.17;
      sf_err = 0.02;
      //sf_val = 1.24;
      //sf_err = 0.03;
    }
    
  } // end if region B


  // Region C
  if( nJets>=4 && modTop<0.0 && mlb<175 ){
    
    if( met>=250.0 && met<350.0 ){
      sf_val = 0.99;
      sf_err = 0.01;
      //sf_val = 0.98;
      //sf_err = 0.01;
    }
    
    if( met>=350.0 && met<450.0 ){
      sf_val = 1.05;
      sf_err = 0.01;
      //sf_val = 1.06;
      //sf_err = 0.02;
    }
  
    if( met>=450.0 && met<550.0 ){
      sf_val = 1.07;
      sf_err = 0.04;
      //sf_val = 1.12;
      //sf_err = 0.05;
    }
  
    if( met>=550.0 && met<650.0 ){
      sf_val = 1.10;
      sf_err = 0.04;
      //sf_val = 1.21;
      //sf_err = 0.05;
    }
  
    if( met>=650.0 ){
      sf_val = 1.14;
      sf_err = 0.05;
      //sf_val = 1.18;
      //sf_err = 0.05;
    }
      
  } // end if region C


  // Region D
  if( nJets>=4 && modTop<0.0 && mlb>=175.0 ){
    
    if( met>=250.0 && met<350.0 ){
      sf_val = 0.99;
      sf_err = 0.01;
      //sf_val = 0.98;
      //sf_err = 0.01;
    }
    
    if( met>=350.0 && met<450.0 ){
      sf_val = 1.05;
      sf_err = 0.01;
      //sf_val = 1.06;
      //sf_err = 0.02;
    }

    if( met>=450.0 && met<550.0 ){
      sf_val = 1.07;
      sf_err = 0.04;
      //sf_val = 1.12;
      //sf_err = 0.05;
    }

    if( met>=550.0 ){
      sf_val = 1.11;
      sf_err = 0.03;
      //sf_val = 1.20;
      //sf_err = 0.04;
    }
      
  } // end if region D
       
        
  // Region E
  if( nJets>=4 && modTop>=0.0 && modTop<10.0 && mlb<175 ){

    if( met>=250.0 && met<350.0 ){
      sf_val = 0.98;
      sf_err = 0.01;
      //sf_val = 0.97;
      //sf_err = 0.01;
    }
    
    if( met>=350.0 && met<550.0 ){
      sf_val = 1.06;
      sf_err = 0.01;
      //sf_val = 1.08;
      //sf_err = 0.02;
    }

    if( met>=550.0 ){
      sf_val = 1.10;
      sf_err = 0.03;
      //sf_val = 1.13;
      //sf_err = 0.03;
    }
    
  } // end if region E


  // Region F
  if( nJets>=4 && modTop>=0.0 && modTop<10.0 && mlb>=175 ){

    if( met>=250.0 && met<450.0 ){
      sf_val = 0.99;
      sf_err = 0.01;
      //sf_val = 0.99;
      //sf_err = 0.01;
    }
    
    if( met>=450.0 ){
      sf_val = 1.07;
      sf_err = 0.02;
      //sf_val = 1.12;
      //sf_err = 0.02;
    }
    
  } // end if region F


  // Region G
  if( nJets>=4 && modTop>=10.0 && mlb<175 ){

    if( met>=250.0 && met<350.0 ){
      sf_val = 0.98;
      sf_err = 0.01;
      //sf_val = 0.97;
      //sf_err = 0.01;
    }
    
    if( met>=350.0 && met<450.0 ){
      sf_val = 1.06;
      sf_err = 0.01;
      //sf_val = 1.08;
      //sf_err = 0.02;
    }

    if( met>=450.0 && met<600.0 ){
      sf_val = 1.07;
      sf_err = 0.02;
      //sf_val = 1.12;
      //sf_err = 0.03;
    }

    if( met>=600.0 ){
      sf_val = 1.08;
      sf_err = 0.04;
      //sf_val = 1.11;
      //sf_err = 0.04;
    }
    
  } // end if region G


  // Region H
  if( nJets>=4 && modTop>=10.0 && mlb>=175 ){

    if( met>=250.0 && met<450.0 ){
      sf_val = 0.99;
      sf_err = 0.01;
      //sf_val = 0.99;
      //sf_err = 0.01;
    }
    
    if( met>=450.0 ){
      sf_val = 1.07;
      sf_err = 0.02;
      //sf_val = 1.12;
      //sf_err = 0.02;
    }
    
  } // end if region H


  // 50% uncertainty on difference between no sf and applying it
  sf_err = fabs(0.5*(1.0-sf_val));

  weight_metRes    = sf_val;
  weight_metRes_up = (sf_val + sf_err);
  weight_metRes_dn = (sf_val - sf_err);

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getMetResWeight_corridor( double &weight_metRes, double &weight_metRes_up, double &weight_metRes_dn ){

  weight_metRes    = 1.0;
  weight_metRes_up = 1.0;
  weight_metRes_dn = 1.0;

  if(!apply_metRes_sf) return;


  double sf_val = 1.0;
  double sf_err = 0.0;
  
  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  // ttbar, tW
  if( sample_info->id != sampleInfo::k_ttbar_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_powheg_pythia8_ext4 &&
      sample_info->id != sampleInfo::k_ttbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8 && 
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu &&
      sample_info->id != sampleInfo::k_WJetsToLNu_amcnlo_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WNJetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W1JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_madgraph_pythia8 && 
      sample_info->id != sampleInfo::k_W1JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_NuPt200_madgraph_pythia8
      ) return;
  

  // 2lep events only
  //if( !babyAnalyzer.is2lep() ) return;


  // Met bin
  double met = babyAnalyzer.pfmet();
  if(add2ndLepToMet) met = babyAnalyzer.pfmet_rl();
  
  // in case of evaluating for JES variation events, then use nominal pfmet, and if nominal<250, use lowest met bin
  if( met<250.0 ) met = 250.0;
  
 
  
  //
  // Find SF
  //
  
  if( met>=250.0 && met<350.0 ){
    sf_val = 0.98;
    sf_err = 0.02;
    //sf_val = 0.97; // 2016 SUS-16-051 pre-approval #s
    //sf_err = 0.02;
  }
  
  if( met>=350.0 && met<450.0 ){
    sf_val = 1.04;
    sf_err = 0.02;
    //sf_val = 1.05;
    //sf_err = 0.03;
  }
  
  if( met>=450.0 && met<550.0 ){
    sf_val = 1.07;
    sf_err = 0.04;
    //sf_val = 1.14;
    //sf_err = 0.05;
  }
  
  if( met>=550.0 ){
    sf_val = 1.07;
    sf_err = 0.05;
    //sf_val = 1.14;
    //sf_err = 0.06;
  }
    


  // 50% uncertainty on difference between no sf and applying it
  sf_err = fabs(0.5*(1.0-sf_val));

  weight_metRes    = sf_val;
  weight_metRes_up = (sf_val + sf_err);
  weight_metRes_dn = (sf_val - sf_err);

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getMetTTbarWeight( double &weight_metTTbar, double &weight_metTTbar_up, double &weight_metTTbar_dn ){

  weight_metTTbar    = 1.0;
  weight_metTTbar_up = 1.0;
  weight_metTTbar_dn = 1.0;

  if(!apply_metTTbar_sf) return;

  double sf_val = 1.0;
  double sf_err = 0.0;
  
  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  // ttbar, tW
  if( sample_info->id != sampleInfo::k_ttbar_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_powheg_pythia8_ext4 &&
      sample_info->id != sampleInfo::k_ttbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1 
      ) return;
  

  // 2lep events only
  if( !babyAnalyzer.is2lep() ) return;
  

  int nGoodJets = babyAnalyzer.ngoodjets();
  
  double modTopness = babyAnalyzer.topnessMod();
  if( add2ndLepToMet) modTopness = babyAnalyzer.topnessMod_rl();
  
  double mlb = babyAnalyzer.Mlb_closestb();
  
  int nTightTags = babyAnalyzer.ntightbtags();
  
  double met = babyAnalyzer.pfmet();
  if(add2ndLepToMet) met = babyAnalyzer.pfmet_rl();
  
  

  //
  // Find SF
  //

  // Region B
  if( nGoodJets<4 && modTopness>=10.0 && mlb>=175.0 && nTightTags>=1 ){
    if( met>450.0 && met<600.0 ){
      sf_val = 1.00;
      sf_err = 0.24;
    }
    if( met>600.0 ){
      sf_val = 0.99;
      sf_err = 0.39;
    }
  }

  // Region E
  if( nGoodJets>=4 && modTopness>=0.0 && modTopness<10.0 && mlb<175.0 ){
    if( met>350.0 && met<550.0 ){
      sf_val = 1.04;
      sf_err = 0.10;
    }
    if( met>550.0 ){
      sf_val = 0.62;
      sf_err = 0.18;
    }
  }

  // Region F
  if( nGoodJets>=4 && modTopness>=0.0 && modTopness<10.0 && mlb>=175.0 && nTightTags>=1 ){
    if( met>250.0 && met<450.0 ){
      sf_val = 1.02;
      sf_err = 0.05;
    }
    if( met>450.0 ){
      sf_val = 0.62;
      sf_err = 0.10;
    }
  }

  // Region H
  if( nGoodJets>=4 && modTopness>=10.0 && mlb>=175.0 && nTightTags>=1){
    if( met>250.0 && met<450.0 ){
      sf_val = 1.02;
      sf_err = 0.05;
    }
    if( met>450.0 ){
      sf_val = 0.62;
      sf_err = 0.10;
    }
  }
  
  // 50% uncertainty on difference between no sf and applying it
  //sf_err = fabs(0.5*(1.0-sf_val));

  weight_metTTbar    = sf_val;
  weight_metTTbar_up = (sf_val + sf_err);
  weight_metTTbar_dn = (sf_val - sf_err);

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getTTbarSysPtSF( double &weight_ttbarSysPt, double &weight_ttbarSysPt_up, double &weight_ttbarSysPt_dn ){

  weight_ttbarSysPt    = 1.0;
  weight_ttbarSysPt_up = 1.0;
  weight_ttbarSysPt_dn = 1.0;

  double sf_val = 1.0;
  double sf_err = 0.0;

  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  if( sample_info->id != sampleInfo::k_ttbar_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_powheg_pythia8_ext4 &&
      sample_info->id != sampleInfo::k_ttbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays &&
      sample_info->id != sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1 &&
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1  ) return;

  if( !babyAnalyzer.is2lep() ) return;


  // Get ttbar/tW system pT
  LorentzVector system_LV(0.0,0.0,0.0,0.0);

  // Lep1 LV
  system_LV += babyAnalyzer.lep1_p4();

  // Lep2 LV, if available
  if( babyAnalyzer.nvetoleps()>1 ) system_LV += babyAnalyzer.lep2_p4();

  // Highest DeepCSV Jet
  int jet1_idx = -1;
  double max_deepcsv = -99.9;
  for(int iJet=0; iJet<(int)babyAnalyzer.ak4pfjets_p4().size(); iJet++){
    if( babyAnalyzer.ak4pfjets_deepCSV().at(iJet) > max_deepcsv ){
      jet1_idx = iJet;
      max_deepcsv  = babyAnalyzer.ak4pfjets_deepCSV().at(iJet);
    }
  }
  if(jet1_idx>=0) system_LV += babyAnalyzer.ak4pfjets_p4().at(jet1_idx);
    
  // 2nd Highest DeepCSV Jets
  int jet2_idx = -1;
  max_deepcsv = -99.9;
  for(int iJet=0; iJet<(int)babyAnalyzer.ak4pfjets_p4().size(); iJet++){
    if( iJet==jet1_idx ) continue;
    if( babyAnalyzer.ak4pfjets_deepCSV().at(iJet) > max_deepcsv ){
      jet2_idx = iJet;
      max_deepcsv = babyAnalyzer.ak4pfjets_deepCSV().at(iJet);
    }
  }
  if(jet2_idx>=0) system_LV += babyAnalyzer.ak4pfjets_p4().at(jet2_idx);

  // Met
  LorentzVector met_TLV( babyAnalyzer.pfmet()*cos(babyAnalyzer.pfmet_phi()), babyAnalyzer.pfmet()*sin(babyAnalyzer.pfmet_phi()), 0.0, babyAnalyzer.pfmet() );
  system_LV += met_TLV;

  // Get system Pt
  double system_pt = system_LV.Pt();
  
  // Get Scale Factor
  if( system_pt>=0.0 && system_pt<50.0 ){
    sf_val = 1.02; // 36.46fb
    sf_err = 0.01;
    //sf_val = 1.10; // 29.53fb
    //sf_err = 0.01;
  }

  if( system_pt>=50.0 && system_pt<100.0 ){
    sf_val = 0.99; // 36.46fb
    sf_err = 0.01;
    //sf_val = 0.98; // 29.53fb
    //sf_err = 0.01;
  }

  // Used these from now on with gen ttbar for ICHEP synch
  if( system_pt>=100.0 && system_pt<150.0 ){
    sf_val = 0.98; // 36.46fb
    sf_err = 0.01;
    //sf_val = 1.03; // 29.53fb
    //sf_err = 0.01;
    //sf_val = 1.02; // 12.9fb ICHEP
    //sf_err = 0.02;
  }

  if( system_pt>=150.0 && system_pt<200.0 ){
    sf_val = 0.95; // 36.46fb
    sf_err = 0.01;
    //sf_val = 0.96; // 29.53fb
    //sf_err = 0.02;
    //sf_val = 0.98; // 12.9fb ICHEP
    //sf_err = 0.02;
  }

  if( system_pt>=200.0 && system_pt<250.0 ){
    sf_val = 0.99; // 36.46
    sf_err = 0.02;
    //sf_val = 0.96; // 29.53fb
    //sf_err = 0.02;
    //sf_val = 0.99; // 12.9fb ICHEP
    //sf_err = 0.03;
  }

  if( system_pt>=250.0 && system_pt<350.0 ){
    sf_val = 1.01; // 36.46fb
    sf_err = 0.02;
    //sf_val = 0.98; // 29.53fb
    //sf_err = 0.03;
    //sf_val = 0.97; // 12.9fb ICHEP
    //sf_err = 0.03;
  }

  if( system_pt>=350.0 && system_pt<450.0 ){
    sf_val = 1.07; // 36.46fb
    sf_err = 0.04;
    //sf_val = 1.06; // 29.53fb
    //sf_err = 0.04;
    //sf_val = 0.98; // 12.9fb ICHEP
    //sf_err = 0.05;
  }

  if( system_pt>=450.0 ){
    sf_val = 1.09; // 36.46fb
    sf_err = 0.05;
    //sf_val = 1.01; // 29.53fb
    //sf_err = 0.05;
    //sf_val = 1.08; // 12.9fb ICHEP
    //sf_err = 0.07;
  }


  // true=sf, false=uncertainty only
  if(!apply_ttbarSysPt_sf) sf_val = 1.0;

  weight_ttbarSysPt    = sf_val;
  weight_ttbarSysPt_up = (sf_val + sf_err );
  weight_ttbarSysPt_dn = (sf_val - sf_err );

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getNuPtSF( double &weight_nuPt_up, double &weight_nuPt_dn ){

  weight_nuPt_up = 1.0;
  weight_nuPt_dn = 1.0;

  double sf_val = 1.0;
  double sf_err = 0.0;

  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  if( !babyAnalyzer.is1lepFromW() ) return;

  if( babyAnalyzer.ngoodjets()==2 && 
      babyAnalyzer.topnessMod()>=6.4 ){
    
    if( babyAnalyzer.pfmet()>=250.0 ) sf_err = 0.0654;
    if( babyAnalyzer.pfmet()>=350.0 ) sf_err = 0.1796;

  } // end if nJets==2 modTop>6.4

  if( babyAnalyzer.ngoodjets()==3 &&
      babyAnalyzer.MT2W()>=200.0     ){

    if( babyAnalyzer.pfmet()>=250.0 ) sf_err = 0.1310;
    if( babyAnalyzer.pfmet()>=350.0 ) sf_err = 0.1530;
 
  } // end if nJets==3 && MT2W>200

  if( babyAnalyzer.ngoodjets()>=4 &&
      babyAnalyzer.MT2W()>=200.0     ){
    
    if( babyAnalyzer.pfmet()>=250.0 ) sf_err = 0.1280;
    if( babyAnalyzer.pfmet()>=350.0 ) sf_err = 0.1840;
    if( babyAnalyzer.pfmet()>=450.0 ) sf_err = 0.2220;
    
  } // end if nJets>=4 && MT2W>200

  weight_nuPt_up = (sf_val + sf_err);
  weight_nuPt_dn = (sf_val - sf_err);

  return;

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getWwidthSF( double &weight_Wwidth_up, double &weight_Wwidth_dn ){

  weight_Wwidth_up = 1.0;
  weight_Wwidth_dn = 1.0;

  double sf_val = 1.0;
  double sf_err = 0.0;

  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  if( !babyAnalyzer.is1lepFromW() ) return;

  if( babyAnalyzer.ngoodjets()==2 && 
      babyAnalyzer.topnessMod()>=6.4 ){
    
    sf_err = 0.03;

  } // end if nJets==2 modTop>6.4

  if( babyAnalyzer.ngoodjets()==3 &&
      babyAnalyzer.MT2W()>=200.0     ){

    sf_err = 0.03;

  } // end if nJets==3 && MT2W>200

  if( babyAnalyzer.ngoodjets()>=4 &&
      babyAnalyzer.MT2W()>=200.0     ){
    
    sf_err = 0.03;

  } // end if nJets>=4 && MT2W>200

  weight_Wwidth_up = (sf_val + sf_err);
  weight_Wwidth_dn = (sf_val - sf_err);

  return;

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getWJetsHFXSecSF( double &weight_hfXsec_up, double &weight_hfXsec_dn ){

  weight_hfXsec_up = 1.0;
  weight_hfXsec_dn = 1.0;
  
  double sf_val = 1.0;
  double sf_err = 0.0;

  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  if( sample_info->id != sampleInfo::k_WJetsToLNu &&
      sample_info->id != sampleInfo::k_WJetsToLNu_amcnlo_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_WNJetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W1JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_madgraph_pythia8 && 
      sample_info->id != sampleInfo::k_W1JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_NuPt200_madgraph_pythia8     ) return;
  
  if( !babyAnalyzer.is1lepFromW() ) return;

  bool isWHF = false;
  for(int iJet= 0; iJet<(int)babyAnalyzer.ak4pfjets_p4().size(); iJet++){
    if(abs(babyAnalyzer.ak4pfjets_hadron_flavor().at(iJet))==5){
      isWHF = true;
      break;
    } // end if W+bets
  } // end loop over jets

  if( !isWHF ) return;

  if( babyAnalyzer.ngoodjets()==2 && 
      babyAnalyzer.topnessMod()>=6.4 ){
    
    sf_err = 0.50;

  } // end if nJets==2 modTop>6.4

  if( babyAnalyzer.ngoodjets()==3 &&
      babyAnalyzer.MT2W()>=200.0     ){

    sf_err = 0.50;

  } // end if nJets==3 && MT2W>200

  if( babyAnalyzer.ngoodjets()>=4 &&
      babyAnalyzer.MT2W()>=200.0     ){
    
    sf_err = 0.50;

  } // end if nJets>=4 && MT2W>200

  weight_hfXsec_up = (sf_val + sf_err);
  weight_hfXsec_dn = (sf_val - sf_err);

  return;

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getPDFWeight( double &weight_pdf_up, double &weight_pdf_dn ){

  weight_pdf_up = 1.0;
  weight_pdf_dn = 1.0;

  if( sample_info->isData ) return;

  if( babyAnalyzer.genweights().size() < 110 ) return;

  if( sample_info->isSignal ){
    if( h_sig_counter->GetBinContent(mStop,mLSP,10)<=0 ||
	h_sig_counter->GetBinContent(mStop,mLSP,11)<=0   ) return;
  }
  else{
    if( h_bkg_counter->GetBinContent(10)<=0 ||
	h_bkg_counter->GetBinContent(11)<=0   ) return;
  }

  weight_pdf_up = babyAnalyzer.pdf_up_weight();
  weight_pdf_dn = babyAnalyzer.pdf_down_weight();

  // Normalization
  if( sample_info->isSignal ){
    weight_pdf_up *= (nEvents/h_sig_counter->GetBinContent(mStop,mLSP,10));
    weight_pdf_dn *= (nEvents/h_sig_counter->GetBinContent(mStop,mLSP,11));
  }
  else{
    weight_pdf_up *= (nEvents/h_bkg_counter->GetBinContent(10));
    weight_pdf_dn *= (nEvents/h_bkg_counter->GetBinContent(11));
  }

  /*
  if( weight_pdf_up<0.0 || weight_pdf_dn<0.0 ){
    weight_pdf_up = 1.0;
    weight_pdf_dn = 1.0;
  }
  */
  if( weight_pdf_up<0.0 ) weight_pdf_up = fabs(weight_pdf_up);
  if( weight_pdf_dn<0.0 ) weight_pdf_dn = fabs(weight_pdf_dn);
 

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getAlphasWeight( double &weight_alphas_up, double &weight_alphas_dn ){

  weight_alphas_up = 1.0;
  weight_alphas_dn = 1.0;

  if( sample_info->isData ) return;

  if( babyAnalyzer.genweights().size() < 110 ) return;
  
  weight_alphas_up = babyAnalyzer.genweights().at(109)/babyAnalyzer.genweights().at(0);
  weight_alphas_dn = babyAnalyzer.genweights().at(110)/babyAnalyzer.genweights().at(0);

  // Normalization
  if( sample_info->isSignal ){
    weight_alphas_up *= (  h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,1)) / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,12))  );
    weight_alphas_dn *= (  h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,1)) / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,13))  );
  }
  else{
    weight_alphas_up *= ( h_bkg_counter->GetBinContent(1) / h_bkg_counter->GetBinContent(12) );
    weight_alphas_dn *= ( h_bkg_counter->GetBinContent(1) / h_bkg_counter->GetBinContent(13) );
  }

  if( weight_alphas_up<0.0 || weight_alphas_dn<0.0 ){
    weight_alphas_up = 1.0;
    weight_alphas_dn = 1.0;
  }

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getQ2Weight( double &weight_q2_up, double &weight_q2_dn ){

  weight_q2_up = 1.0;
  weight_q2_dn = 1.0;

  if( sample_info->isData ) return;

  if( babyAnalyzer.genweights().size() < 110 ) return;

  weight_q2_up = babyAnalyzer.genweights().at(4)/babyAnalyzer.genweights().at(0);
  weight_q2_dn = babyAnalyzer.genweights().at(8)/babyAnalyzer.genweights().at(0);

  // Normalization
  if( sample_info->isSignal ){
    
    weight_q2_up *= ( h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,1)) / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,5)) );
    weight_q2_dn *= ( h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,1)) / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,9)) );
  }
  else{
    weight_q2_up *= ( h_bkg_counter->GetBinContent(1) / h_bkg_counter->GetBinContent(5) );
    weight_q2_dn *= ( h_bkg_counter->GetBinContent(1) / h_bkg_counter->GetBinContent(9) );
  }


  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getLumi( double &weight_lumi, double &weight_lumi_up, double &weight_lumi_dn ){

  weight_lumi    = 1.0;
  weight_lumi_up = 1.0;
  weight_lumi_dn = 1.0;

  if( sample_info->isData ) return;
  
  weight_lumi    = lumi;
  weight_lumi_up = (lumi+lumi_err);
  weight_lumi_dn = (lumi-lumi_err);

  return;

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getISRWeight( double &weight_ISR, double &weight_ISR_up, double &weight_ISR_dn ){

  weight_ISR    = 1.0;
  weight_ISR_up = 1.0;
  weight_ISR_dn = 1.0;

  if(!apply_ISR_sf) return;

  if( sample_info->isData ) return;
  //if( !sample_info->isSignal ) return;

  weight_ISR    = babyAnalyzer.weight_ISR();
  weight_ISR_up = babyAnalyzer.weight_ISRup();
  weight_ISR_dn = babyAnalyzer.weight_ISRdown();

  // Normalization
  getNEvents(nEvents);

  weight_ISR    *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,19)) );
  weight_ISR_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,20)) );
  weight_ISR_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,21)) );

  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getISRnJetsWeight( double &weight_ISR, double &weight_ISR_up, double &weight_ISR_dn ){

  weight_ISR    = 1.0;
  weight_ISR_up = 1.0;
  weight_ISR_dn = 1.0;

  if(!apply_ISR_sf) return;

  if( sample_info->isData ) return;
  
  if( sample_info->id != sampleInfo::k_ttbar_powheg_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_powheg_pythia8_ext4 &&
      sample_info->id != sampleInfo::k_ttbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ) return;


  weight_ISR    = babyAnalyzer.weight_ISRnjets();
  weight_ISR_up = babyAnalyzer.weight_ISRnjets_UP();
  weight_ISR_dn = babyAnalyzer.weight_ISRnjets_DN();

  // Normalization
  getNEvents(nEvents);

  if( sample_info->isSignalScan ){
    weight_ISR    *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,24)) );
    weight_ISR_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,25)) );
    weight_ISR_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,26)) );
  }
  else{
    weight_ISR    *= ( nEvents / h_bkg_counter->GetBinContent(25) );
    weight_ISR_up *= ( nEvents / h_bkg_counter->GetBinContent(26) );
    weight_ISR_dn *= ( nEvents / h_bkg_counter->GetBinContent(27) );
  }
  
  return;
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getXSecWeight( double &weight_xsec, double &weight_xsec_up, double &weight_xsec_dn ){

  weight_xsec    = 1.0;
  weight_xsec_up = 1.0;
  weight_xsec_dn = 1.0;

  double xsec_val = 1.0;
  double xsec_err = 0.0;
  
  if( sample_info->isData ) return;

  if( !sample_info->isSignal ){
    xsec_val = babyAnalyzer.xsec();
  }
  else{
    getSusyMasses(mStop,mLSP);
    xsec_val = h_sig_xsec->GetBinContent(h_sig_xsec->FindBin(mStop));
    xsec_err = h_sig_xsec->GetBinError(h_sig_xsec->FindBin(mStop));
  }
  weight_xsec    = xsec_val;
  weight_xsec_up = (xsec_val+xsec_err);
  weight_xsec_dn = (xsec_val-xsec_err);

  return;

}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getPileupWeight( double &weight_pu, double &weight_pu_up, double &weight_pu_dn ){

  weight_pu    = 1.0;
  weight_pu_up = 1.0;
  weight_pu_dn = 1.0;
  
  if(!apply_pu_sf) return;
  
  if( sample_info->isData ) return;

  if( sample_info->isSignal ) return;
  
  //weight_pu    = h_pu_wgt->GetBinContent(h_pu_wgt->FindBin(babyAnalyzer.pu_ntrue()));
  //weight_pu_up = h_pu_wgt_up->GetBinContent(h_pu_wgt_up->FindBin(babyAnalyzer.pu_ntrue()));
  //weight_pu_dn = h_pu_wgt_dn->GetBinContent(h_pu_wgt_dn->FindBin(babyAnalyzer.pu_ntrue()));
  weight_pu    = babyAnalyzer.weight_PU();
  weight_pu_up = babyAnalyzer.weight_PUup();
  weight_pu_dn = babyAnalyzer.weight_PUdown();

  return;

}

//////////////////////////////////////////////////////////////////////

double sysInfo::evtWgtInfo::getSampleWeight( sampleInfo::ID sample ){

  double result = 1.0;

  if(!apply_sample_sf ) return result;

  switch( sample ){

  case(sampleInfo::k_ttbar_diLept_madgraph_pythia8):
    result = (5689986.0)/(23198554.0+5689986.0);
    break;
    
  case(sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1):
    result = (23198554.0)/(23198554.0+5689986.0);
    break;
    
  case(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays):
    result = (4473156.0)/(4473156.0+3145334.0);
    break;
  
  case(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1):
    result = (3145334.0)/(4473156.0+3145334.0);
    break;

  case(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays):
    result = (5029568.0)/(5029568.0+3146940.0);
    break;

  case(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1):
    result = (3146940.0)/(5029568.0+3146940.0);
    break;

  default:
    break;
  };

  return result;
}

//////////////////////////////////////////////////////////////////////
