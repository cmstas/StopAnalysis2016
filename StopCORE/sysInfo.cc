#include "sysInfo.h"

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

sysInfo::evtWgtInfo::evtWgtInfo( sampleInfo::ID sample, bool useBTagUtils, bool useLepSFUtils, bool use2ndLepToMet ){
  
  // Get sample info from enum
  sample_info = new sampleInfo::sampleUtil( sample );

  // Utilty Var Constants
  dr_matched = 0.1;
  lumi       = 36.46; // Current lumi
  //lumi       = 29.53; // lumi for intermediate status update
  //lumi       = 12.9; // ICHEP lumi
  lumi_err   = lumi*0.062; // 6.2% for ICHEP lumi uncertainty

  // Initialize Switches for additional SFs
  apply_diLepTrigger_sf = false;
  apply_cr2lTrigger_sf  = false;
  apply_bTag_sf         = false;
  apply_lep_sf          = false;
  apply_vetoLep_sf      = false;
  apply_lepFS_sf        = false;
  apply_topPt_sf        = false;
  apply_metRes_sf       = false;
  apply_ttbarSysPt_sf   = false;
  apply_ISR_sf          = false;
  apply_sample_sf       = false;

  // Decision to use Utilities vs direct from baby for bTag and lep SFs
  useBTagSFs_fromUtils = useBTagUtils;
  useLepSFs_fromUtils  = useLepSFUtils;
  
  // Decision to use met with 2nd lepton removed (for lost lepton)
  add2ndLepToMet = use2ndLepToMet;

  // Initialize event weights and related variables
  initializeWeights();

  // Initialize baby weights histograms
  h_sig_counter = NULL;
  h_sig_counter_nEvents = NULL;
  h_bkg_counter = NULL;
  h_cr2lTrigger_sf = NULL;

  // Get Signal XSection File
  if( sample_info->isSignal ){
    f_sig_xsec = new TFile("../StopCORE/inputs/signal_xsec/xsec_stop_13TeV.root","read");
    h_sig_xsec = (TH1D*)f_sig_xsec->Get("stop");
  }

  // Get SR trigger histos
  if( !sample_info->isData ){
    f_cr2lTrigger_sf = new TFile("../StopCORE/inputs/trigger/triggerefficiency_2lCR.root","read");
    h_cr2lTrigger_sf = (TH2D*)f_cr2lTrigger_sf->Get("twoDefficiencypass");
  }

  // Initialize bTag SF machinery
  if( !sample_info->isData && useBTagSFs_fromUtils ){
    //bTagSFUtil = new eventWeight_bTagSF( sample_info->isFastsim );
  }

  
  // Initialize Lepton Scale Factors
  if( !sample_info->isData && useLepSFs_fromUtils ){
    lepSFUtil  = new eventWeight_lepSF( sample_info->isFastsim );
  }
   
}

//////////////////////////////////////////////////////////////////////

sysInfo::evtWgtInfo::~evtWgtInfo(){
  
  sample_info->~sampleUtil();
  
  if( !sample_info->isData && useBTagSFs_fromUtils){
    //delete bTagSFUtil;
  }
  
  if( !sample_info->isData && useLepSFs_fromUtils){
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
  
  sf_lep = 1.0;
  sf_lep_up = 1.0;
  sf_lep_dn = 1.0;
  
  sf_vetoLep = 1.0;
  sf_vetoLep_up = 1.0;
  sf_vetoLep_dn = 1.0;
  
  sf_lepFS = 1.0;
  sf_lepFS_up = 1.0;
  sf_lepFS_dn = 1.0;
  
  sf_topPt = 1.0;
  sf_topPt_up = 1.0;
  sf_topPt_dn = 1.0;
  
  sf_metRes = 1.0;
  sf_metRes_up = 1.0;
  sf_metRes_dn = 1.0;
  
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
  
  sf_xsec_up = 1.0;
  sf_xsec_dn = 1.0;

  sf_sample = 1.0;

  for(int iSys=0; iSys<sysInfo::k_nSys; iSys++) sys_wgts[iSys]=1.0;
  
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
  getBTagWeight( sf_bTag, sf_bTagEffHF_up, sf_bTagEffHF_dn, sf_bTagEffLF_up, sf_bTagEffLF_dn ); 
  
  // lepSFs
  getLepSFWeight( sf_lep, sf_lep_up, sf_lep_dn, sf_lepFS, sf_lepFS_up, sf_lepFS_dn, sf_vetoLep, sf_vetoLep_up, sf_vetoLep_dn );
 
  // top pT Reweighting
  getTopPtWeight( sf_topPt, sf_topPt_up, sf_topPt_dn );

  // MET resolution scale factors
  getMetResWeight( sf_metRes, sf_metRes_up, sf_metRes_dn );
  
  // ttbar system pT scale factor 
  getTTbarSysPtSF( sf_ttbarSysPt, sf_ttbarSysPt_up, sf_ttbarSysPt_dn );

  // Lumi Variation
  getLumi( sf_lumi, sf_lumi_up, sf_lumi_dn );

  // ISR Correction
  //if( sample_info->isSignal ) getISRWeight( sf_ISR, sf_ISR_up, sf_ISR_dn );
  getISRnJetsWeight( sf_ISR, sf_ISR_up, sf_ISR_dn );
  
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
     

    // Fill Array Element
    sys_wgts[iSys] = sys_wgt;


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
  if( abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep1_pdgid())==22 ){
    sf_val = 0.869669; // 36.46fb
    sf_err = 0.00456458;
    //sf_val = 0.884591; // 29.53fb
    //sf_err = 0.00811308;
    //sf_val = 0.883481; // 12.9fb ICHEP
    //sf_err = 0.012322;
  }

  // MuE Trigger
  if( abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep1_pdgid())==24 ){
    sf_val = 0.86165; // 36.46fb
    sf_err = 0.00255978;
    //sf_val = 0.908511; // 29.53fb
    //sf_err = 0.00420534;
    //sf_val = 0.893801; // 12.9fb ICHEP
    //sf_err = 0.00657751;
  }

  // DiMuon Trigger
  if( abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep1_pdgid())==26 ){
    sf_val = 0.819581; // 36.46fb
    sf_err = 0.00406059;
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

void sysInfo::evtWgtInfo::getBTagWeight( double &wgt_btagsf, double &wgt_btagsf_hf_up, double &wgt_btagsf_hf_dn, double &wgt_btagsf_lf_up, double &wgt_btagsf_lf_dn ){

  wgt_btagsf       = 1.0;
  wgt_btagsf_hf_up = 1.0;
  wgt_btagsf_hf_dn = 1.0;
  wgt_btagsf_lf_up = 1.0;
  wgt_btagsf_lf_dn = 1.0;

  if( !apply_bTag_sf ) return;

  if( useBTagSFs_fromUtils ){
    //getBTagWeight_fromUtils( wgt_btagsf, wgt_btagsf_hf_up, wgt_btagsf_hf_dn, wgt_btagsf_lf_up, wgt_btagsf_lf_dn ); 
  }
  else{
    wgt_btagsf       = babyAnalyzer.weight_btagsf();
    wgt_btagsf_hf_up = babyAnalyzer.weight_btagsf_heavy_UP();
    wgt_btagsf_hf_dn = babyAnalyzer.weight_btagsf_heavy_DN();
    wgt_btagsf_lf_up = babyAnalyzer.weight_btagsf_light_UP();
    wgt_btagsf_lf_dn = babyAnalyzer.weight_btagsf_light_DN();
  }
  
  // Normalization
  getNEvents( nEvents );
  
  if( sample_info->isSignal ){
    getSusyMasses(mStop,mLSP);
  
    wgt_btagsf       *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,14)) );
    wgt_btagsf_hf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,15)) );
    wgt_btagsf_hf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,17)) );
    wgt_btagsf_lf_up *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,16)) );
    wgt_btagsf_lf_dn *= ( nEvents / h_sig_counter->GetBinContent(h_sig_counter->FindBin(mStop,mLSP,18)) );
  }
  else{
    wgt_btagsf       *= ( nEvents / h_bkg_counter->GetBinContent(14) );
    wgt_btagsf_hf_up *= ( nEvents / h_bkg_counter->GetBinContent(15) );
    wgt_btagsf_hf_dn *= ( nEvents / h_bkg_counter->GetBinContent(17) );
    wgt_btagsf_lf_up *= ( nEvents / h_bkg_counter->GetBinContent(16) );
    wgt_btagsf_lf_dn *= ( nEvents / h_bkg_counter->GetBinContent(18) );
  }
  
}

//////////////////////////////////////////////////////////////////////

void sysInfo::evtWgtInfo::getBTagWeight_fromUtils( double &wgt_btagsf, double &wgt_btagsf_hf_up, double &wgt_btagsf_hf_dn, double &wgt_btagsf_lf_up, double &wgt_btagsf_lf_dn ){

  vector< double > jet_pt, jet_eta;
  vector< int > jet_flavour;
  vector< bool > jet_passCSV;

  for(int iJet=0; iJet<(int)babyAnalyzer.ak4pfjets_p4().size(); iJet++){
    jet_pt.push_back( (double)babyAnalyzer.ak4pfjets_p4().at(iJet).Pt() );
    jet_eta.push_back( (double)babyAnalyzer.ak4pfjets_p4().at(iJet).Eta() );
    jet_flavour.push_back( (int)abs(babyAnalyzer.ak4pfjets_hadron_flavor().at(iJet)) );
    jet_passCSV.push_back( (bool)babyAnalyzer.ak4pfjets_passMEDbtag().at(iJet) );
  }
  //bTagSFUtil->getBTagWeight( jet_pt, jet_eta, jet_flavour, jet_passCSV, wgt_btagsf, wgt_btagsf_hf_up, wgt_btagsf_hf_dn, wgt_btagsf_lf_up, wgt_btagsf_lf_dn );

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
  
  if( useLepSFs_fromUtils ){
    getLepSFWeight_fromUtils( weight_lepSF, weight_lepSF_Up, weight_lepSF_Dn, weight_lepFSSF, weight_lepFSSF_Up, weight_lepFSSF_Dn, weight_vetoLepSF, weight_vetoLepSF_Up, weight_vetoLepSF_Dn );
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

void sysInfo::evtWgtInfo::getLepSFWeight_fromUtils( double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepFSSF, double &weight_lepFSSF_Up, double &weight_lepFSSF_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn ){

  weight_lepSF = 1.0;
  weight_lepSF_Up = 1.0;
  weight_lepSF_Dn = 1.0;
  weight_lepFSSF = 1.0;
  weight_lepFSSF_Up = 1.0;
  weight_lepFSSF_Dn = 1.0;
  weight_vetoLepSF = 1.0;
  weight_vetoLepSF_Up = 1.0;
  weight_vetoLepSF_Dn = 1.0;

  std::vector< double > recoLep_pt, recoLep_eta, genLostLep_pt, genLostLep_eta;
  std::vector< int > recoLep_pdgid, genLostLep_pdgid;
  std::vector< bool > recoLep_isSel;
  
  if( babyAnalyzer.nvetoleps()==1 ){
    recoLep_pt.push_back( babyAnalyzer.lep1_p4().Pt() );
    recoLep_eta.push_back( babyAnalyzer.lep1_p4().Eta() );
    recoLep_pdgid.push_back( babyAnalyzer.lep1_pdgid() );
    if( (abs(babyAnalyzer.lep1_pdgid())==13 && 
	 babyAnalyzer.lep1_passTightID() ) ||
	(abs(babyAnalyzer.lep1_pdgid())==11 && 
	 babyAnalyzer.lep1_passMediumID() )   ){
      recoLep_isSel.push_back( true );
    }
    else{
      recoLep_isSel.push_back( false );
    }
  }
  
  if( babyAnalyzer.nvetoleps()>=2 ){
    recoLep_pt.push_back( babyAnalyzer.lep1_p4().Pt() );
    recoLep_eta.push_back( babyAnalyzer.lep1_p4().Eta() );
    recoLep_pdgid.push_back( babyAnalyzer.lep1_pdgid() );
    if( (abs(babyAnalyzer.lep1_pdgid())==13 && 
	 babyAnalyzer.lep1_passTightID())  ||
	(abs(babyAnalyzer.lep1_pdgid())==11 && 
	 babyAnalyzer.lep1_passMediumID())    ){
      recoLep_isSel.push_back( true );
    }
    else{
      recoLep_isSel.push_back( false );
    }
    
    recoLep_pt.push_back( babyAnalyzer.lep2_p4().Pt() );
    recoLep_eta.push_back( babyAnalyzer.lep2_p4().Eta() );
    recoLep_pdgid.push_back( babyAnalyzer.lep2_pdgid() );
    if( (abs(babyAnalyzer.lep2_pdgid())==13 && 
	 babyAnalyzer.lep2_passTightID())  ||
	(abs(babyAnalyzer.lep2_pdgid())==11 && 
	 babyAnalyzer.lep2_passMediumID())    ){
      recoLep_isSel.push_back( true );
    }
    else{
      recoLep_isSel.push_back( false );
    }

  }
 


  if( babyAnalyzer.is2lep() && babyAnalyzer.nvetoleps()==1 ){

    // Find gen lepton matched to reco lepton
    int matched_idx = -1;
    double min_dr   = 99.9;
    for(int iGen=0; iGen<(int)babyAnalyzer.genleps_p4().size(); iGen++){
      if( !babyAnalyzer.genleps_isLastCopy().at(iGen) ) continue;
      
      // Preferentially match to same flavour lepton before tau
      if( (abs(babyAnalyzer.genleps_id().at(iGen))==11 && 
	   abs(babyAnalyzer.lep1_pdgid())==11                      ) ||
	  (abs(babyAnalyzer.genleps_id().at(iGen))==13 &&
	   abs(babyAnalyzer.lep1_pdgid())==13                      )    ){

	double min_dr_temp = ROOT::Math::VectorUtil::DeltaR( babyAnalyzer.genleps_p4().at(iGen), babyAnalyzer.lep1_p4() );
	if( min_dr_temp < min_dr ){
	  min_dr = min_dr_temp;
	  if( min_dr < dr_matched ){
	    matched_idx = iGen;
	  }
	}
	
      } // end if dr matched to same flavour lepton
    

    } // end loop over gen leptons

    
    if( matched_idx < 0 ){
      for(int iGen=0; iGen<(int)babyAnalyzer.genleps_p4().size(); iGen++){
	if( !babyAnalyzer.genleps_isLastCopy().at(iGen) ) continue;
	if( abs(babyAnalyzer.genleps_id().at(iGen))==15 ){
	 
	  double min_dr_temp = ROOT::Math::VectorUtil::DeltaR( babyAnalyzer.genleps_p4().at(iGen), babyAnalyzer.lep1_p4() );
	  if( min_dr_temp < min_dr ){
	    min_dr = min_dr_temp;
	    if( min_dr < dr_matched ){
	      matched_idx = iGen;
	    }
	  }
	  
	} // end if gen/reco matched to tau
      } // end loop over gen leptons
    } // end if reco lepton not matched

    if( matched_idx >= 0 ){
      // Find gen lost lepton
      double genLostPt  = -99.9;
      double genLostEta = -99.9;
      int genLostPdgid  = -99;
      bool foundLostLep = false;
      for(int iGen=0; iGen<(int)babyAnalyzer.genleps_p4().size(); iGen++){
	if( iGen == matched_idx ) continue;
	if( !babyAnalyzer.genleps_isLastCopy().at(iGen) ) continue;
	if( !babyAnalyzer.genleps_fromHardProcessFinalState().at(iGen) ) continue;
	if( abs(babyAnalyzer.genleps_id().at(iGen))!=11 && 
	    abs(babyAnalyzer.genleps_id().at(iGen))!=13    ) continue;
	
	genLostPt    = babyAnalyzer.genleps_p4().at(iGen).Pt();
	genLostEta   = babyAnalyzer.genleps_p4().at(iGen).Eta();
	genLostPdgid = babyAnalyzer.genleps_id().at(iGen);
	foundLostLep = true;
	
      } // end loop over gen leptons
    
      if( foundLostLep ){
	genLostLep_pt.push_back( genLostPt );
	genLostLep_eta.push_back( genLostEta );
	genLostLep_pdgid.push_back( genLostPdgid );
      }

    } // end if selected lepton is matched

  } // end if is gen 2lep event with ==1 reco lepton 

  lepSFUtil->getLepWeight( recoLep_pt, recoLep_eta, recoLep_pdgid, recoLep_isSel, genLostLep_pt, genLostLep_eta, genLostLep_pdgid, weight_lepSF, weight_lepSF_Up, weight_lepSF_Dn, weight_lepFSSF, weight_lepFSSF_Up, weight_lepFSSF_Dn, weight_vetoLepSF, weight_vetoLepSF_Up, weight_vetoLepSF_Dn );


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
  
  double met = babyAnalyzer.pfmet();
  if(add2ndLepToMet) met = babyAnalyzer.pfmet_rl();

  double mt2w = babyAnalyzer.MT2W();
  if(add2ndLepToMet) mt2w = babyAnalyzer.MT2W_rl();

  double sf_val = 1.0;
  double sf_err = 0.0;

  if( sample_info->isData ) return;
  if( sample_info->isSignal ) return;

  // ttbar, tW, and wJets only
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
      sample_info->id != sampleInfo::k_WNJetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W1JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_madgraph_pythia8 && 
      sample_info->id != sampleInfo::k_W1JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W2JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W3JetsToLNu_NuPt200_madgraph_pythia8 &&
      sample_info->id != sampleInfo::k_W4JetsToLNu_NuPt200_madgraph_pythia8    ) return;
  

  if( babyAnalyzer.ngoodjets()==2 ){

    if( met>=250.0 && met<350.0 ){
      sf_val = 1.080;
      sf_err = 0.007;
    }

    if( met>=350.0 && met<450.0 ){
      sf_val = 0.895;
      sf_err = 0.011;
    }

    if( met>=450.0 ){
      sf_val = 0.679;
      sf_err = 0.046;
    }

  } // end if nJets==2

  if( babyAnalyzer.ngoodjets()==3 ){

    if( met>=250.0 && met<350.0 ){
      sf_val = 1.066;
      sf_err = 0.024;
    }

    if( met>=350.0 && met<450.0 ){
      sf_val = 0.976;
      sf_err = 0.073;
    }

    if( met>=450.0 && met<550.0 ){
      sf_val = 0.784;
      sf_err = 0.022;
    }
    
    if( met>=550.0 ){
      sf_val = 0.664;
      sf_err = 0.024;
    }

  } // end if nJets==3

  if( babyAnalyzer.ngoodjets()>=4 ){

    if( mt2w<200.0 ){

      if( met>=250.0 && met<350.0 ){
	sf_val = 1.080;
	sf_err = 0.015;
      }

      if( met>=350.0 && met<450.0  ){
	sf_val = 0.935;
	sf_err = 0.018;
      }

      if( met>=450.0 ){
	sf_val = 0.766;
	sf_err = 0.020;
      }

    } // end if MT2W<200.0
    
    if( mt2w>=200.0 ){
      
      if( met>=250.0 && met<350.0 ){
	sf_val = 1.080;
	sf_err = 0.015;
      }

      if( met>=350.0 && met<450.0  ){
	sf_val = 0.935;
	sf_err = 0.018;
      }

      if( met>=450.0 && met<550.0  ){
	sf_val = 0.866;
	sf_err = 0.028;
      }

      if( met>=550.0 && met<650.0  ){
	sf_val = 0.766;
	sf_err = 0.020;
      }

      if( met>=650.0 ){
	sf_val = 0.590;
	sf_err = 0.047;
      }

    } // end if MT2W>=200.0
    

  } // end if nJets>=4
  

  // 50% uncertainty on difference between no sf and applying it
  sf_err = fabs(0.5*(1.0-sf_val));

  weight_metRes    = sf_val;
  weight_metRes_up = (sf_val + sf_err);
  weight_metRes_dn = (sf_val - sf_err);

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
      sample_info->id != sampleInfo::k_t_tbarW_5f_powheg_pythia8  ) return;

  if( !babyAnalyzer.is2lep() ) return;


  // Get ttbar/tW system pT
  LorentzVector system_LV(0.0,0.0,0.0,0.0);

  /*
  // Grab top quarks
  for(int iGen=0; iGen<(int)babyAnalyzer.genqs_p4().size(); iGen++){
    if( abs(babyAnalyzer.genqs_id().at(iGen))==6 &&
	babyAnalyzer.genqs_isLastCopy().at(iGen) ){
      system_LV += babyAnalyzer.genqs_p4().at(iGen);
    }
  }

  // If tW grab the W
  if( sample_info->id == sampleInfo::k_t_tW_5f_powheg_pythia8 ||
      sample_info->id == sampleInfo::k_t_tbarW_5f_powheg_pythia8 ){
    for(int iGen=0; iGen<(int)babyAnalyzer.genbosons_p4().size(); iGen++){
      if( abs(babyAnalyzer.genbosons_id().at(iGen))==24 &&
	  babyAnalyzer.genbosons_isHardProcess().at(iGen) &&
	  babyAnalyzer.genbosons_isLastCopy().at(iGen) ){
	system_LV += babyAnalyzer.genbosons_p4().at(iGen);
      }
    }
  }

  // Get system Pt
  double system_pt = system_LV.Pt();
  */

  // Lep1 LV
  system_LV += babyAnalyzer.lep1_p4();

  // Lep2 LV, if available
  if( babyAnalyzer.nvetoleps()>1 ) system_LV += babyAnalyzer.lep2_p4();

  // Highest CSV Jet
  int jet1_idx = -1;
  double max_csv = -99.9;
  for(int iJet=0; iJet<(int)babyAnalyzer.ak4pfjets_p4().size(); iJet++){
    if( babyAnalyzer.ak4pfjets_CSV().at(iJet) > max_csv ){
      jet1_idx = iJet;
      max_csv  = babyAnalyzer.ak4pfjets_CSV().at(iJet);
    }
  }
  if(jet1_idx>=0) system_LV += babyAnalyzer.ak4pfjets_p4().at(jet1_idx);
    
  // 2nd Highest CSV Jets
  int jet2_idx = -1;
  max_csv = -99.9;
  for(int iJet=0; iJet<(int)babyAnalyzer.ak4pfjets_p4().size(); iJet++){
    if( iJet==jet1_idx ) continue;
    if( babyAnalyzer.ak4pfjets_CSV().at(iJet) > max_csv ){
      jet2_idx = iJet;
      max_csv = babyAnalyzer.ak4pfjets_CSV().at(iJet);
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

  if( weight_pdf_up<0.0 || weight_pdf_dn<0.0 ){
    weight_pdf_up = 1.0;
    weight_pdf_dn = 1.0;
  }

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
  if( !sample_info->isSignal ) return;

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

double sysInfo::evtWgtInfo::getSampleWeight( sampleInfo::ID sample ){

  double result = 1.0;

  if(!apply_sample_sf ) return result;

  switch( sample ){

  default:
    break;
  };

  return result;
}

//////////////////////////////////////////////////////////////////////
