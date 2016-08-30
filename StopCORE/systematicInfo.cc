#include "systematicInfo.h"

//////////////////////////////////////////////////////////////////////

systematicInfo::systematicUtil::systematicUtil( systematicInfo::ID systematic ){
  
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

double systematicInfo::getSystematicWeight( systematicInfo::ID systematic, eventWeightInfo *evt_wgt ){

  double result = 1.0;

  if( babyAnalyzer.is_data() ) return result;

  // This is scale1fb*lumi = lumi*1000*xsec/nEvents
  result *= evt_wgt->sf_nominal; 


  //
  // Switches, set in looper, in eventWeightInfo.cc/h, determine if 
  //   these additional SFs are != 1.0
  //
 
  // Apply diLepton Trigger scale factor
  double wgt_diLepTrigger = evt_wgt->sf_diLepTrigger;
  result *= wgt_diLepTrigger;

  // Apply CR2l Trigger scale factor
  double wgt_cr2lTrigger = evt_wgt->sf_cr2lTrigger;
  result *= wgt_cr2lTrigger;
  
  // Apply bTag scale factor
  double wgt_bTag = evt_wgt->sf_bTag;
  result *= wgt_bTag;
  
  // Apply lepton scale factor
  double wgt_lep = evt_wgt->sf_lep*evt_wgt->sf_vetoLep*evt_wgt->sf_lepFS;
  result *= wgt_lep;

  // Apply top pT sf
  double wgt_topPt = evt_wgt->sf_topPt;
  result *= wgt_topPt;

  // Apply met resolution sf
  double wgt_metRes = evt_wgt->sf_metRes;
  result *= wgt_metRes;

  // Apply ttbar system pT SF (will be 1 if not ttbar/tW 2l) 
  double wgt_ttbarSysPt = evt_wgt->sf_ttbarSysPt;
  result *= wgt_ttbarSysPt;

  // Apply ISR SF( will be 1 if not Signal)
  double wgt_ISR = evt_wgt->sf_ISR;
  result *= wgt_ISR;
  
  // Apply sample weight (for WJets stitching)
  double wgt_sample = evt_wgt->sf_sample;
  result *= wgt_sample;

  double wgt_diLepTriggerUp = 1.0;
  double wgt_diLepTriggerDn = 1.0;
  double wgt_cr2lTriggerUp = 1.0;
  double wgt_cr2lTriggerDn = 1.0;
  double wgt_bTagEffHFUp = 1.0;
  double wgt_bTagEffHFDn = 1.0;
  double wgt_bTagEffLFUp = 1.0;
  double wgt_bTagEffLFDn = 1.0;
  double wgt_lepSFUp = 1.0;
  double wgt_lepSFDn = 1.0;
  double wgt_lepFSUp = 1.0;
  double wgt_lepFSDn = 1.0;
  double wgt_topPtUp = 1.0;
  double wgt_topPtDn = 1.0;
  double wgt_metResUp = 1.0;
  double wgt_metResDn = 1.0;
  double wgt_ttbarSysPtUp = 1.0;
  double wgt_ttbarSysPtDn = 1.0;
  double wgt_nuPtUp = 1.0;
  double wgt_nuPtDn = 1.0;
  double wgt_WwidthUp = 1.0;
  double wgt_WwidthDn = 1.0;
  double wgt_hfXSecUp = 1.0;
  double wgt_hfXSecDn = 1.0;
  double wgt_pdfUp = 1.0;
  double wgt_pdfDn = 1.0;
  double wgt_alphasUp = 1.0;
  double wgt_alphasDn = 1.0;
  double wgt_q2Up = 1.0;
  double wgt_q2Dn = 1.0;
  double wgt_lumiUp = 1.0;
  double wgt_lumiDn = 1.0;
  double wgt_ISRUp = 1.0;
  double wgt_ISRDn = 1.0;
  double wgt_xsecUp = 1.0;
  double wgt_xsecDn = 1.0;

  switch( systematic ){

  case( k_nominal ):
    break;

  case( k_JESUp ):
    break;

  case( k_JESDown ):
    break;

  case( k_diLepTriggerUp ):
    wgt_diLepTriggerUp = (evt_wgt->sf_diLepTrigger_up/evt_wgt->sf_diLepTrigger);
    result *= wgt_diLepTriggerUp;
    break;

  case( k_diLepTriggerDown ):
    wgt_diLepTriggerDn = (evt_wgt->sf_diLepTrigger_dn/evt_wgt->sf_diLepTrigger);
    result *= wgt_diLepTriggerDn;
    break;

  case( k_cr2lTriggerUp ):
    wgt_cr2lTriggerUp = (evt_wgt->sf_cr2lTrigger_up/evt_wgt->sf_cr2lTrigger);
    result *= wgt_cr2lTriggerUp;
    break;

  case( k_cr2lTriggerDown ):
    wgt_cr2lTriggerDn = (evt_wgt->sf_cr2lTrigger_dn/evt_wgt->sf_cr2lTrigger);
    result *= wgt_cr2lTriggerDn;
    break;

  case( k_bTagEffHFUp ):
    wgt_bTagEffHFUp = (evt_wgt->sf_bTagEffHF_up/wgt_bTag);
    result *= wgt_bTagEffHFUp;
    break;

  case( k_bTagEffHFDown ):
    wgt_bTagEffHFDn = (evt_wgt->sf_bTagEffHF_dn/wgt_bTag);
    result *= wgt_bTagEffHFDn;
    break;

  case( k_bTagEffLFUp ):
    wgt_bTagEffLFUp = (evt_wgt->sf_bTagEffLF_up/wgt_bTag);
    result *= wgt_bTagEffLFUp;
    break;

  case( k_bTagEffLFDown ):
    wgt_bTagEffLFDn = (evt_wgt->sf_bTagEffLF_dn/wgt_bTag);
    result *= wgt_bTagEffLFDn;
    break;

  case( k_lepSFUp ):
    wgt_lepSFUp = (evt_wgt->sf_lep_up*evt_wgt->sf_vetoLep_up*evt_wgt->sf_lepFS)/wgt_lep;
    result *= wgt_lepSFUp;
    break;

  case( k_lepSFDown ):
    wgt_lepSFDn = (evt_wgt->sf_lep_dn*evt_wgt->sf_vetoLep_dn*evt_wgt->sf_lepFS)/wgt_lep;
    result *= wgt_lepSFDn;
    break;

  case( k_lepFSSFUp ):
    wgt_lepFSUp = (evt_wgt->sf_lep*evt_wgt->sf_vetoLep*evt_wgt->sf_lepFS_up)/wgt_lep;
    result *= wgt_lepFSUp;
    break;

  case( k_lepFSSFDown ):
    wgt_lepFSDn = (evt_wgt->sf_lep*evt_wgt->sf_vetoLep*evt_wgt->sf_lepFS_dn)/wgt_lep;
    result *= wgt_lepFSDn;
    break;

  case( k_topPtSFUp ):
    wgt_topPtUp = (evt_wgt->sf_topPt_up/wgt_topPt);
    result *= wgt_topPtUp;
    break;

  case( k_topPtSFDown ):
    wgt_topPtDn = (evt_wgt->sf_topPt_dn/wgt_topPt);
    result *= wgt_topPtDn;
    break;

  case( k_metResUp ):
    wgt_metResUp = evt_wgt->sf_metRes_up/wgt_metRes;
    result *= wgt_metResUp;
    break;

  case( k_metResDown ):
    wgt_metResDn = evt_wgt->sf_metRes_dn/wgt_metRes;
    result *= wgt_metResDn;
    break;

  case( k_ttbarSysPtUp ):
    wgt_ttbarSysPtUp = (evt_wgt->sf_ttbarSysPt_up/wgt_ttbarSysPt);
    result *= wgt_ttbarSysPtUp;
    break;

  case( k_ttbarSysPtDown ):
    wgt_ttbarSysPtDn = (evt_wgt->sf_ttbarSysPt_dn/wgt_ttbarSysPt);
    result *= wgt_ttbarSysPtDn;
    break;

  case( k_nuPtSF_Up ):
    wgt_nuPtUp = evt_wgt->sf_nuPt_up;
    result *= wgt_nuPtUp;
    break;

  case( k_nuPtSF_Down ):
    wgt_nuPtDn = evt_wgt->sf_nuPt_dn;
    result *= wgt_nuPtDn;
    break;

  case( k_WwidthSF_Up ):
    wgt_WwidthUp = evt_wgt->sf_Wwidth_up;
    result *= wgt_WwidthUp;
    break;

  case( k_WwidthSF_Down ):
    wgt_WwidthDn = evt_wgt->sf_Wwidth_dn;
    result *= wgt_WwidthDn;
    break;

  case( k_hfXsec_Up ):
    wgt_hfXSecUp = evt_wgt->sf_hfXsec_up;
    result *= wgt_hfXSecUp;
    break;

  case( k_hfXsec_Down ):
    wgt_hfXSecDn = evt_wgt->sf_hfXsec_dn;
    result *= wgt_hfXSecDn;
    break;

  case( k_pdfUp ):
    if(evt_wgt->sample_info->isSignal){
      wgt_pdfUp = (babyAnalyzer.pdf_up_weight())/(evt_wgt->h_sig_counter->GetBinContent(evt_wgt->mStop,evt_wgt->mLSP,10)/evt_wgt->nEvents);
    }
    else{
      wgt_pdfUp = (babyAnalyzer.pdf_up_weight())/(evt_wgt->h_bkg_counter->GetBinContent(10)/evt_wgt->nEvents);
    }
    result *= wgt_pdfUp;
    break;

  case( k_pdfDown ):
    if(evt_wgt->sample_info->isSignal){
      wgt_pdfUp = (babyAnalyzer.pdf_up_weight())/(evt_wgt->h_sig_counter->GetBinContent(evt_wgt->mStop,evt_wgt->mLSP,11)/evt_wgt->nEvents);
    }
    else{
      wgt_pdfDn = (babyAnalyzer.pdf_down_weight())/(evt_wgt->h_bkg_counter->GetBinContent(11)/evt_wgt->nEvents);
    }
    result *= wgt_pdfDn;
    break;
    
  case( k_alphasUp ):
    wgt_alphasUp = evt_wgt->sf_alphas_up;
    result *= wgt_alphasUp;
    break;

  case( k_alphasDown ):
    wgt_alphasDn = evt_wgt->sf_alphas_dn;
    result *= wgt_alphasDn;
    break;
    
  case( k_q2Up ):
    wgt_q2Up = evt_wgt->sf_q2_up;
    result *= wgt_q2Up;
    break;    

  case( k_q2Down ):
    wgt_q2Dn = evt_wgt->sf_q2_dn;
    result *= wgt_q2Dn;
    break;    

  case( k_lumiUp ):
    wgt_lumiUp = evt_wgt->sf_lumi_up/evt_wgt->sf_lumi;
    result *= wgt_lumiUp;
    break; 

  case( k_lumiDown ):
    wgt_lumiDn = evt_wgt->sf_lumi_dn/evt_wgt->sf_lumi;
    result *= wgt_lumiDn;
    break;    
    
  case( k_ISRUp ):
    wgt_ISRUp = (evt_wgt->sf_ISR_up/wgt_ISR);
    result *= wgt_ISRUp;
    break; 

  case( k_ISRDown ):
    wgt_ISRDn = (evt_wgt->sf_ISR_dn/wgt_ISR);
    result *= wgt_ISRDn;
    break; 
    
  case( k_xsecUp ):
    wgt_xsecUp = (evt_wgt->sf_xsec_up/evt_wgt->xsec);
    result *= wgt_xsecUp;
    break; 

  case( k_xsecDown ):
    wgt_xsecDn = (evt_wgt->sf_xsec_dn/evt_wgt->xsec);
    result *= wgt_xsecDn;
    break; 
    
  default:
    std::cout << "Could not find systematic info from systematic enum provided!" << std::endl;
    break;

  }; // end systematic switch


  return result;

}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_util_wgt systematicInfo::getSystematicWeightsFromList( vect_util systematicList, eventWeightInfo *evt_wgt ){

  vect_util_wgt result;

  for(int iSys=0; iSys<(int)systematicList.size(); iSys++){

    pair_util_wgt temp_result;
    temp_result.first  = systematicList[iSys];
    temp_result.second = getSystematicWeight( temp_result.first.id, evt_wgt );

    result.push_back( temp_result );

  } // end loop over list

  return result;

}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_util systematicInfo::getSystematicList_all(){

  vect_util result;

  result.push_back( systematicUtil(k_nominal) );
  result.push_back( systematicUtil(k_JESUp) );
  result.push_back( systematicUtil(k_JESDown) );
  result.push_back( systematicUtil(k_bTagEffHFUp) );
  result.push_back( systematicUtil(k_bTagEffHFDown) );
  result.push_back( systematicUtil(k_bTagEffLFUp) );
  result.push_back( systematicUtil(k_bTagEffLFDown) );
  result.push_back( systematicUtil(k_lepSFUp) );
  result.push_back( systematicUtil(k_lepSFDown) );
  result.push_back( systematicUtil(k_lepFSSFUp) );
  result.push_back( systematicUtil(k_lepFSSFDown) );
  result.push_back( systematicUtil(k_topPtSFUp) );
  result.push_back( systematicUtil(k_topPtSFDown) );
  result.push_back( systematicUtil(k_metResUp) );
  result.push_back( systematicUtil(k_metResDown) );
  result.push_back( systematicUtil(k_ttbarSysPtUp) );
  result.push_back( systematicUtil(k_ttbarSysPtDown) );
  result.push_back( systematicUtil(k_nuPtSF_Up) );
  result.push_back( systematicUtil(k_nuPtSF_Down) );
  result.push_back( systematicUtil(k_WwidthSF_Up) );
  result.push_back( systematicUtil(k_WwidthSF_Down) );
  result.push_back( systematicUtil(k_hfXsec_Up) );
  result.push_back( systematicUtil(k_hfXsec_Down) );
  result.push_back( systematicUtil(k_pdfUp) );
  result.push_back( systematicUtil(k_pdfDown) );
  result.push_back( systematicUtil(k_alphasUp) );
  result.push_back( systematicUtil(k_alphasDown) );
  result.push_back( systematicUtil(k_q2Up) );
  result.push_back( systematicUtil(k_q2Down) );
  result.push_back( systematicUtil(k_lumiUp) );
  result.push_back( systematicUtil(k_lumiDown) );
  result.push_back( systematicUtil(k_ISRUp) );
  result.push_back( systematicUtil(k_ISRDown) );
  result.push_back( systematicUtil(k_xsecUp) );
  result.push_back( systematicUtil(k_xsecDown) );

  return result;

}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_util systematicInfo::getSystematicList( analyzerInfo::ID analysis, bool sample_isFastsim, bool sample_isSignal ){

  vect_util result;

  switch( analysis ){
    
  case( analyzerInfo::k_SR ):
    result.push_back( systematicUtil(k_nominal) );
    result.push_back( systematicUtil(k_cr2lTriggerUp) );
    result.push_back( systematicUtil(k_cr2lTriggerDown) );
    result.push_back( systematicUtil(k_bTagEffHFUp) );
    result.push_back( systematicUtil(k_bTagEffHFDown) );
    result.push_back( systematicUtil(k_bTagEffLFUp) );
    result.push_back( systematicUtil(k_bTagEffLFDown) );
    result.push_back( systematicUtil(k_lepSFUp) );
    result.push_back( systematicUtil(k_lepSFDown) );
    result.push_back( systematicUtil(k_pdfUp) );
    result.push_back( systematicUtil(k_pdfDown) );
    result.push_back( systematicUtil(k_alphasUp) );
    result.push_back( systematicUtil(k_alphasDown) );
    result.push_back( systematicUtil(k_q2Up) );
    result.push_back( systematicUtil(k_q2Down) );
    result.push_back( systematicUtil(k_lumiUp) );
    result.push_back( systematicUtil(k_lumiDown) );
    
    if( sample_isSignal ){
      result.push_back( systematicUtil(k_ISRUp) );
      result.push_back( systematicUtil(k_ISRDown) );
      result.push_back( systematicUtil(k_xsecUp) );
      result.push_back( systematicUtil(k_xsecDown) );
    }
    else{
      result.push_back( systematicUtil(k_ttbarSysPtUp) );
      result.push_back( systematicUtil(k_ttbarSysPtDown) );
      result.push_back( systematicUtil(k_topPtSFUp) );
      result.push_back( systematicUtil(k_topPtSFDown) );
      result.push_back( systematicUtil(k_metResUp) );
      result.push_back( systematicUtil(k_metResDown) );
      result.push_back( systematicUtil(k_nuPtSF_Up) );
      result.push_back( systematicUtil(k_nuPtSF_Down) );
      result.push_back( systematicUtil(k_WwidthSF_Up) );
      result.push_back( systematicUtil(k_WwidthSF_Down) );
      result.push_back( systematicUtil(k_hfXsec_Up) );
      result.push_back( systematicUtil(k_hfXsec_Down) );
    }
    
    if( sample_isFastsim ){
      result.push_back( systematicUtil(k_lepFSSFUp) );
      result.push_back( systematicUtil(k_lepFSSFDown) );
    }
    
    break;
  
  case( analyzerInfo::k_CR0b ):
    result.push_back( systematicUtil(k_nominal) );
    result.push_back( systematicUtil(k_bTagEffHFUp) );
    result.push_back( systematicUtil(k_bTagEffHFDown) );
    result.push_back( systematicUtil(k_bTagEffLFUp) );
    result.push_back( systematicUtil(k_bTagEffLFDown) );
    result.push_back( systematicUtil(k_lepSFUp) );
    result.push_back( systematicUtil(k_lepSFDown) );
    result.push_back( systematicUtil(k_pdfUp) );
    result.push_back( systematicUtil(k_pdfDown) );
    result.push_back( systematicUtil(k_alphasUp) );
    result.push_back( systematicUtil(k_alphasDown) );
    result.push_back( systematicUtil(k_q2Up) );
    result.push_back( systematicUtil(k_q2Down) );
    result.push_back( systematicUtil(k_lumiUp) );
    result.push_back( systematicUtil(k_lumiDown) );
    
    if( sample_isSignal ){
      result.push_back( systematicUtil(k_ISRUp) );
      result.push_back( systematicUtil(k_ISRDown) );
      result.push_back( systematicUtil(k_xsecUp) );
      result.push_back( systematicUtil(k_xsecDown) );
    }
    else{
      result.push_back( systematicUtil(k_topPtSFUp) );
      result.push_back( systematicUtil(k_topPtSFDown) );
      result.push_back( systematicUtil(k_metResUp) );
      result.push_back( systematicUtil(k_metResDown) );
      result.push_back( systematicUtil(k_nuPtSF_Up) );
      result.push_back( systematicUtil(k_nuPtSF_Down) );
      result.push_back( systematicUtil(k_WwidthSF_Up) );
      result.push_back( systematicUtil(k_WwidthSF_Down) );
      result.push_back( systematicUtil(k_hfXsec_Up) );
      result.push_back( systematicUtil(k_hfXsec_Down) );
    }
    
    if( sample_isFastsim ){
      result.push_back( systematicUtil(k_lepFSSFUp) );
      result.push_back( systematicUtil(k_lepFSSFDown) );
    }
    
    break;

  case( analyzerInfo::k_CR1l_bulkWJets ):
    result.push_back( systematicUtil(k_nominal) );
    result.push_back( systematicUtil(k_bTagEffHFUp) );
    result.push_back( systematicUtil(k_bTagEffHFDown) );
    result.push_back( systematicUtil(k_bTagEffLFUp) );
    result.push_back( systematicUtil(k_bTagEffLFDown) );
    result.push_back( systematicUtil(k_lepSFUp) );
    result.push_back( systematicUtil(k_lepSFDown) );
    result.push_back( systematicUtil(k_pdfUp) );
    result.push_back( systematicUtil(k_pdfDown) );
    result.push_back( systematicUtil(k_alphasUp) );
    result.push_back( systematicUtil(k_alphasDown) );
    result.push_back( systematicUtil(k_q2Up) );
    result.push_back( systematicUtil(k_q2Down) );
    result.push_back( systematicUtil(k_topPtSFUp) );
    result.push_back( systematicUtil(k_topPtSFDown) );
        
    if( sample_isFastsim ){
      result.push_back( systematicUtil(k_lepFSSFUp) );
      result.push_back( systematicUtil(k_lepFSSFDown) );
    }
    
    break;

  case( analyzerInfo::k_CR2l ):
    result.push_back( systematicUtil(k_nominal) );
    result.push_back( systematicUtil(k_cr2lTriggerUp) );
    result.push_back( systematicUtil(k_cr2lTriggerDown) );
    result.push_back( systematicUtil(k_bTagEffHFUp) );
    result.push_back( systematicUtil(k_bTagEffHFDown) );
    result.push_back( systematicUtil(k_bTagEffLFUp) );
    result.push_back( systematicUtil(k_bTagEffLFDown) );
    result.push_back( systematicUtil(k_lepSFUp) );
    result.push_back( systematicUtil(k_lepSFDown) );
    result.push_back( systematicUtil(k_pdfUp) );
    result.push_back( systematicUtil(k_pdfDown) );
    result.push_back( systematicUtil(k_alphasUp) );
    result.push_back( systematicUtil(k_alphasDown) );
    result.push_back( systematicUtil(k_q2Up) );
    result.push_back( systematicUtil(k_q2Down) );
    result.push_back( systematicUtil(k_lumiUp) );
    result.push_back( systematicUtil(k_lumiDown) );
    
    if( sample_isSignal ){
      result.push_back( systematicUtil(k_ISRUp) );
      result.push_back( systematicUtil(k_ISRDown) );
      result.push_back( systematicUtil(k_xsecUp) );
      result.push_back( systematicUtil(k_xsecDown) );
    }
    else{
      result.push_back( systematicUtil(k_ttbarSysPtUp) );
      result.push_back( systematicUtil(k_ttbarSysPtDown) );
      result.push_back( systematicUtil(k_topPtSFUp) );
      result.push_back( systematicUtil(k_topPtSFDown) );
      result.push_back( systematicUtil(k_metResUp) );
      result.push_back( systematicUtil(k_metResDown) );
    }
    
    if( sample_isFastsim ){
      result.push_back( systematicUtil(k_lepFSSFUp) );
      result.push_back( systematicUtil(k_lepFSSFDown) );
    }

    break;

  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( systematicUtil(k_nominal) );
    result.push_back( systematicUtil(k_diLepTriggerUp) );
    result.push_back( systematicUtil(k_diLepTriggerDown) );
    result.push_back( systematicUtil(k_bTagEffHFUp) );
    result.push_back( systematicUtil(k_bTagEffHFDown) );
    result.push_back( systematicUtil(k_bTagEffLFUp) );
    result.push_back( systematicUtil(k_bTagEffLFDown) );
    result.push_back( systematicUtil(k_lepSFUp) );
    result.push_back( systematicUtil(k_lepSFDown) );
    result.push_back( systematicUtil(k_pdfUp) );
    result.push_back( systematicUtil(k_pdfDown) );
    result.push_back( systematicUtil(k_alphasUp) );
    result.push_back( systematicUtil(k_alphasDown) );
    result.push_back( systematicUtil(k_q2Up) );
    result.push_back( systematicUtil(k_q2Down) );
    result.push_back( systematicUtil(k_topPtSFUp) );
    result.push_back( systematicUtil(k_topPtSFDown) );
    result.push_back( systematicUtil(k_metResUp) );
    result.push_back( systematicUtil(k_metResDown) );
    result.push_back( systematicUtil(k_ttbarSysPtUp) );
    result.push_back( systematicUtil(k_ttbarSysPtDown) );
       
    if( sample_isFastsim ){
      result.push_back( systematicUtil(k_lepFSSFUp) );
      result.push_back( systematicUtil(k_lepFSSFDown) );
    }

    break;
    
  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( systematicUtil(k_nominal) );
    result.push_back( systematicUtil(k_bTagEffHFUp) );
    result.push_back( systematicUtil(k_bTagEffHFDown) );
    result.push_back( systematicUtil(k_bTagEffLFUp) );
    result.push_back( systematicUtil(k_bTagEffLFDown) );
    result.push_back( systematicUtil(k_pdfUp) );
    result.push_back( systematicUtil(k_pdfDown) );
    result.push_back( systematicUtil(k_alphasUp) );
    result.push_back( systematicUtil(k_alphasDown) );
    result.push_back( systematicUtil(k_q2Up) );
    result.push_back( systematicUtil(k_q2Down) );
    result.push_back( systematicUtil(k_lumiUp) );
    result.push_back( systematicUtil(k_lumiDown) );
    result.push_back( systematicUtil(k_topPtSFUp) );
    result.push_back( systematicUtil(k_topPtSFDown) );
            
    break;
  
  
  default:
    result.push_back( systematicUtil(k_nominal) );
    break;

  }; // end switch


  return result;
}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_util systematicInfo::getSystematicList_forLimit_lostLepton(){
  
  vect_util result;
  
  result.push_back( systematicUtil(k_nominal) );
  //result.push_back( systematicUtil(k_JESUp) );
  //result.push_back( systematicUtil(k_JESDown) );
  result.push_back( systematicUtil(k_bTagEffHFUp) );
  result.push_back( systematicUtil(k_bTagEffHFDown) );
  result.push_back( systematicUtil(k_bTagEffLFUp) );
  result.push_back( systematicUtil(k_bTagEffLFDown) );
  result.push_back( systematicUtil(k_lepSFUp) );
  result.push_back( systematicUtil(k_lepSFDown) );
  result.push_back( systematicUtil(k_metResUp) );
  result.push_back( systematicUtil(k_metResDown) );
  result.push_back( systematicUtil(k_ttbarSysPtUp) );
  result.push_back( systematicUtil(k_ttbarSysPtDown) );
  //result.push_back( systematicUtil(k_pdfUp) );
  //result.push_back( systematicUtil(k_pdfDown) );
  result.push_back( systematicUtil(k_alphasUp) );
  result.push_back( systematicUtil(k_alphasDown) );
  result.push_back( systematicUtil(k_q2Up) );
  result.push_back( systematicUtil(k_q2Down) );
  //result.push_back( systematicUtil(k_lumiUp) );
  //result.push_back( systematicUtil(k_lumiDown) );
  result.push_back( systematicUtil(k_cr2lTriggerUp) );
  result.push_back( systematicUtil(k_cr2lTriggerDown) );
    
  return result;
}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_util systematicInfo::getSystematicList_forLimit_oneLeptonNotFromTop(){

  vect_util result;

  result.push_back( systematicUtil(k_nominal) );
  result.push_back( systematicUtil(k_JESUp) );
  result.push_back( systematicUtil(k_JESDown) );
  result.push_back( systematicUtil(k_bTagEffHFUp) );
  result.push_back( systematicUtil(k_bTagEffHFDown) );
  result.push_back( systematicUtil(k_bTagEffLFUp) );
  result.push_back( systematicUtil(k_bTagEffLFDown) );
  result.push_back( systematicUtil(k_lepSFUp) );
  result.push_back( systematicUtil(k_lepSFDown) );
  result.push_back( systematicUtil(k_lepFSSFUp) );
  result.push_back( systematicUtil(k_lepFSSFDown) );
  result.push_back( systematicUtil(k_metResUp) );
  result.push_back( systematicUtil(k_metResDown) );
  result.push_back( systematicUtil(k_nuPtSF_Up) );
  result.push_back( systematicUtil(k_nuPtSF_Down) );
  result.push_back( systematicUtil(k_WwidthSF_Up) );
  result.push_back( systematicUtil(k_WwidthSF_Down) );
  result.push_back( systematicUtil(k_hfXsec_Up) );
  result.push_back( systematicUtil(k_hfXsec_Down) );
  result.push_back( systematicUtil(k_pdfUp) );
  result.push_back( systematicUtil(k_pdfDown) );
  result.push_back( systematicUtil(k_alphasUp) );
  result.push_back( systematicUtil(k_alphasDown) );
  result.push_back( systematicUtil(k_q2Up) );
  result.push_back( systematicUtil(k_q2Down) );
  result.push_back( systematicUtil(k_lumiUp) );
  result.push_back( systematicUtil(k_lumiDown) );

  return result;
}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_util systematicInfo::getSystematicList_forLimit_oneLeptonFromTop(){

  vect_util result;

  result.push_back( systematicUtil(k_nominal) );
  result.push_back( systematicUtil(k_JESUp) );
  result.push_back( systematicUtil(k_JESDown) );
  result.push_back( systematicUtil(k_bTagEffHFUp) );
  result.push_back( systematicUtil(k_bTagEffHFDown) );
  result.push_back( systematicUtil(k_bTagEffLFUp) );
  result.push_back( systematicUtil(k_bTagEffLFDown) );
  result.push_back( systematicUtil(k_lepSFUp) );
  result.push_back( systematicUtil(k_lepSFDown) );
  result.push_back( systematicUtil(k_lepFSSFUp) );
  result.push_back( systematicUtil(k_lepFSSFDown) );
  result.push_back( systematicUtil(k_metResUp) );
  result.push_back( systematicUtil(k_metResDown) );
  result.push_back( systematicUtil(k_pdfUp) );
  result.push_back( systematicUtil(k_pdfDown) );
  result.push_back( systematicUtil(k_alphasUp) );
  result.push_back( systematicUtil(k_alphasDown) );
  result.push_back( systematicUtil(k_q2Up) );
  result.push_back( systematicUtil(k_q2Down) );
  result.push_back( systematicUtil(k_lumiUp) );
  result.push_back( systematicUtil(k_lumiDown) );

  return result;
}

/////////////////////////////////////////////////////////////////////

systematicInfo::vect_util systematicInfo::getSystematicList_forLimit_ZtoNuNu(){

  vect_util result;

  result.push_back( systematicUtil(k_nominal) );
  result.push_back( systematicUtil(k_JESUp) );
  result.push_back( systematicUtil(k_JESDown) );
  result.push_back( systematicUtil(k_bTagEffHFUp) );
  result.push_back( systematicUtil(k_bTagEffHFDown) );
  result.push_back( systematicUtil(k_bTagEffLFUp) );
  result.push_back( systematicUtil(k_bTagEffLFDown) );
  result.push_back( systematicUtil(k_lepSFUp) );
  result.push_back( systematicUtil(k_lepSFDown) );
  result.push_back( systematicUtil(k_lepFSSFUp) );
  result.push_back( systematicUtil(k_lepFSSFDown) );
  result.push_back( systematicUtil(k_metResUp) );
  result.push_back( systematicUtil(k_metResDown) );
  result.push_back( systematicUtil(k_pdfUp) );
  result.push_back( systematicUtil(k_pdfDown) );
  result.push_back( systematicUtil(k_alphasUp) );
  result.push_back( systematicUtil(k_alphasDown) );
  result.push_back( systematicUtil(k_q2Up) );
  result.push_back( systematicUtil(k_q2Down) );
  result.push_back( systematicUtil(k_lumiUp) );
  result.push_back( systematicUtil(k_lumiDown) );

  return result;
}

/////////////////////////////////////////////////////////////////////

systematicInfo::vect_util systematicInfo::getSystematicList_forLimit_sig(){

  vect_util result;

  result.push_back( systematicUtil(k_nominal) );
  result.push_back( systematicUtil(k_JESUp) );
  result.push_back( systematicUtil(k_JESDown) );
  result.push_back( systematicUtil(k_bTagEffHFUp) );
  result.push_back( systematicUtil(k_bTagEffHFDown) );
  result.push_back( systematicUtil(k_bTagEffLFUp) );
  result.push_back( systematicUtil(k_bTagEffLFDown) );
  result.push_back( systematicUtil(k_lepSFUp) );
  result.push_back( systematicUtil(k_lepSFDown) );
  result.push_back( systematicUtil(k_lepFSSFUp) );
  result.push_back( systematicUtil(k_lepFSSFDown) );
  result.push_back( systematicUtil(k_pdfUp) );
  result.push_back( systematicUtil(k_pdfDown) );
  result.push_back( systematicUtil(k_alphasUp) );
  result.push_back( systematicUtil(k_alphasDown) );
  result.push_back( systematicUtil(k_q2Up) );
  result.push_back( systematicUtil(k_q2Down) );
  result.push_back( systematicUtil(k_lumiUp) );
  result.push_back( systematicUtil(k_lumiDown) );
  result.push_back( systematicUtil(k_ISRUp) );
  result.push_back( systematicUtil(k_ISRDown) );
  result.push_back( systematicUtil(k_xsecUp) );
  result.push_back( systematicUtil(k_xsecDown) );

  return result;
}

/////////////////////////////////////////////////////////////////////

