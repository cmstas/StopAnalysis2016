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

  case( k_nJetsSFK3Up ):
    id          = systematic;
    label       = "nJetsSFK3Up";
    title       = "nJets SF, K3, Up";
    tex         = "nJets~SF,~K3,~Up";
    hasOwnBabies = false;
    break;

  case( k_nJetsSFK3Down ):
    id          = systematic;
    label       = "nJetsSFK3Dn";
    title       = "nJets SF, K3, Down";
    tex         = "nJets~SF,~K3,~Down";
    hasOwnBabies = false;
    break;
    
  case( k_nJetsSFK4Up ):
    id          = systematic;
    label       = "nJetsSFK4Up";
    title       = "nJets SF, K4, Up";
    tex         = "nJets~SF,~K4,~Up";
    hasOwnBabies = false;
    break;

  case( k_nJetsSFK4Down ):
    id          = systematic;
    label       = "nJetsSFK4Dn";
    title       = "nJets SF, K4, Down";
    tex         = "nJets~SF,~K4,~Down";
    hasOwnBabies = false;
    break;

  case( k_diNuPtSF_Up ):
    id          = systematic;
    label       = "diNuPtUp";
    title       = "diNuetrino pT, Up";
    tex         = "${\\nu}{\\nu}p_{T}$,~Up";
    hasOwnBabies = false;
    break;

  case( k_diNuPtSF_Down ):
    id          = systematic;
    label       = "diNuPtDn";
    title       = "diNuetrino pT, Down";
    tex         = "${\\nu}{\\nu}p_{T}$,~Down";
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

  // Intialize weights
  evt_wgt->initializeWeights();

  // Get Event weights
  evt_wgt->getEventWeights();

  // This is scale1fb*lumi = lumi*1000*xsec/nEvents
  result *= evt_wgt->sf_nominal; 
  
  // Apply bTag scale factor
  double wgt_bTag = evt_wgt->sf_bTag*(evt_wgt->nEvents/evt_wgt->norm_bTagEff);
  result *= wgt_bTag;
  
  // Apply lepton scale factor
  double wgt_lep = evt_wgt->sf_lep*evt_wgt->sf_vetoLep*evt_wgt->sf_lepFS;
  result *= wgt_lep;

  // Apply met resolution sf
  double wgt_metRes = evt_wgt->sf_metRes;
  result *= wgt_metRes;

  // Apply nJets SF, K3 (will be 1 if not ttbar 2l)
  double wgt_k3 = evt_wgt->sf_nJetsK3;
  result *= wgt_k3;

  // Apply nJets SF, K4 (will be 1 if not ttbar 2l)
  double wgt_k4 = evt_wgt->sf_nJetsK4;
  result *= wgt_k4;

  // Apply diNu pT SF (will be 1 if not ttbar 2l) 
  double wgt_diNuPt = evt_wgt->sf_diNuPt;
  result *= wgt_diNuPt;

  // Apply nu pT SF (will be 1 if not WJets) 
  double wgt_nuPt = evt_wgt->sf_nuPt;
  result *= wgt_nuPt;

  // Apply ISR SF( will be 1 if not Signal)
  double wgt_ISR = evt_wgt->sf_ISR/evt_wgt->norm_ISR;
  result *= wgt_ISR;
  

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
  double wgt_k3Up = 1.0;
  double wgt_k3Dn = 1.0;
  double wgt_k4Up = 1.0;
  double wgt_k4Dn = 1.0;
  double wgt_diNuPtUp = 1.0;
  double wgt_diNuPtDn = 1.0;
  double wgt_nuPtUp = 1.0;
  double wgt_nuPtDn = 1.0;
  double wgt_WwidthUp = 1.0;
  double wgt_WwidthDn = 1.0;
  double wgt_hfXSecUp = 1.0;
  double wgt_hfXSecDn = 1.0;
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

  case( k_bTagEffHFUp ):
    wgt_bTagEffHFUp = (evt_wgt->sf_bTagEffHF_up/evt_wgt->norm_bTagEffHF_up)/wgt_bTag;
    result *= wgt_bTagEffHFUp;
    break;

  case( k_bTagEffHFDown ):
    wgt_bTagEffHFDn = (evt_wgt->sf_bTagEffHF_dn/evt_wgt->norm_bTagEffHF_dn)/wgt_bTag;
    result *= wgt_bTagEffHFDn;
    break;

  case( k_bTagEffLFUp ):
    wgt_bTagEffLFUp = (evt_wgt->sf_bTagEffLF_up/evt_wgt->norm_bTagEffLF_up)/wgt_bTag;
    result *= wgt_bTagEffLFUp;
    break;

  case( k_bTagEffLFDown ):
    wgt_bTagEffLFDn = (evt_wgt->sf_bTagEffLF_dn/evt_wgt->norm_bTagEffLF_dn)/wgt_bTag;
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
    wgt_topPtUp = evt_wgt->sf_topPt_up;
    result *= wgt_topPtUp;
    break;

  case( k_topPtSFDown ):
    wgt_topPtDn = evt_wgt->sf_topPt_dn;
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

  case( k_nJetsSFK3Up ):
    wgt_k3Up = evt_wgt->sf_nJetsK3_up/wgt_k3;
    result *= wgt_k3Up;
    break;

  case( k_nJetsSFK3Down ):
    wgt_k3Dn = evt_wgt->sf_nJetsK3_dn/wgt_k3;
    result *= wgt_k3Dn;
    break;
    
  case( k_nJetsSFK4Up ):
    wgt_k4Up = evt_wgt->sf_nJetsK4_up/wgt_k4;
    result *= wgt_k4Up;
    break;

  case( k_nJetsSFK4Down ):
    wgt_k4Dn = evt_wgt->sf_nJetsK4_dn/wgt_k4;
    result *= wgt_k4Dn;
    break;

  case( k_diNuPtSF_Up ):
    wgt_diNuPtUp = evt_wgt->sf_diNuPt_up/wgt_diNuPt;
    result *= wgt_diNuPtUp;
    break;

  case( k_diNuPtSF_Down ):
    wgt_diNuPtDn = evt_wgt->sf_diNuPt_dn/wgt_diNuPt;
    result *= wgt_diNuPtDn;
    break;

  case( k_nuPtSF_Up ):
    wgt_nuPtUp = evt_wgt->sf_nuPt_up/wgt_nuPt;
    result *= wgt_nuPtUp;
    break;

  case( k_nuPtSF_Down ):
    wgt_nuPtDn = evt_wgt->sf_nuPt_dn/wgt_nuPt;
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
    break;

  case( k_pdfDown ):
    break;
    
  case( k_alphasUp ):
    wgt_alphasUp = (evt_wgt->sf_alphas_up/evt_wgt->norm_alphas)*(evt_wgt->nEvents/evt_wgt->norm_alphas_up);
    result *= wgt_alphasUp;
    break;

  case( k_alphasDown ):
    wgt_alphasDn = (evt_wgt->sf_alphas_dn/evt_wgt->norm_alphas)*(evt_wgt->nEvents/evt_wgt->norm_alphas_dn);
    result *= wgt_alphasDn;
    break;
    
  case( k_q2Up ):
    wgt_q2Up = (evt_wgt->sf_q2_up/evt_wgt->norm_q2)*(evt_wgt->nEvents/evt_wgt->norm_q2_up);
    result *= wgt_q2Up;
    break;    

  case( k_q2Down ):
    wgt_q2Dn = (evt_wgt->sf_q2_dn/evt_wgt->norm_q2)*(evt_wgt->nEvents/evt_wgt->norm_q2_dn);
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
    wgt_ISRUp = (evt_wgt->sf_ISR_up/evt_wgt->norm_ISR_up)/wgt_ISR;
    result *= wgt_ISRUp;
    break; 

  case( k_ISRDown ):
    wgt_ISRDn = (evt_wgt->sf_ISR_dn/evt_wgt->norm_ISR_dn)/wgt_ISR;
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

systematicInfo::vect_id_wgt systematicInfo::getSystematicWeightsFromList( vect_id systematicList, eventWeightInfo *evt_wgt ){

  vect_id_wgt result;

  for(int iSys=0; iSys<(int)systematicList.size(); iSys++){

    pair_id_wgt temp_result;
    temp_result.first  = systematicList[iSys];
    temp_result.second = getSystematicWeight( temp_result.first, evt_wgt );

    result.push_back( temp_result );

  } // end loop over list

  return result;

}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_id systematicInfo::getSystematicList_all(){

  vect_id result;

  result.push_back( k_nominal );
  result.push_back( k_JESUp );
  result.push_back( k_JESDown );
  result.push_back( k_bTagEffHFUp );
  result.push_back( k_bTagEffHFDown );
  result.push_back( k_bTagEffLFUp );
  result.push_back( k_bTagEffLFDown );
  result.push_back( k_lepSFUp );
  result.push_back( k_lepSFDown );
  result.push_back( k_lepFSSFUp );
  result.push_back( k_lepFSSFDown );
  result.push_back( k_topPtSFUp );
  result.push_back( k_topPtSFDown );
  result.push_back( k_metResUp );
  result.push_back( k_metResDown );
  result.push_back( k_nJetsSFK3Up );
  result.push_back( k_nJetsSFK3Down );
  result.push_back( k_nJetsSFK4Up );
  result.push_back( k_nJetsSFK4Down );
  result.push_back( k_diNuPtSF_Up );
  result.push_back( k_diNuPtSF_Down );
  result.push_back( k_nuPtSF_Up );
  result.push_back( k_nuPtSF_Down );
  result.push_back( k_WwidthSF_Up );
  result.push_back( k_WwidthSF_Down );
  result.push_back( k_hfXsec_Up );
  result.push_back( k_hfXsec_Down );
  result.push_back( k_pdfUp );
  result.push_back( k_pdfDown );
  result.push_back( k_alphasUp );
  result.push_back( k_alphasDown );
  result.push_back( k_q2Up );
  result.push_back( k_q2Down );
  result.push_back( k_lumiUp );
  result.push_back( k_lumiDown );
  result.push_back( k_ISRUp );
  result.push_back( k_ISRDown );
  result.push_back( k_xsecUp );
  result.push_back( k_xsecDown );

  return result;

}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_id systematicInfo::getSystematicList( analyzerInfo::ID analysis, bool sample_isFastsim, bool sample_isSignal ){

  vect_id result;

  switch( analysis ){
    
  case( analyzerInfo::k_SR ):
    result.push_back( k_nominal );
    result.push_back( k_bTagEffHFUp );
    result.push_back( k_bTagEffHFDown );
    result.push_back( k_bTagEffLFUp );
    result.push_back( k_bTagEffLFDown );
    result.push_back( k_lepSFUp );
    result.push_back( k_lepSFDown );
    result.push_back( k_pdfUp );
    result.push_back( k_pdfDown );
    result.push_back( k_alphasUp );
    result.push_back( k_alphasDown );
    result.push_back( k_q2Up );
    result.push_back( k_q2Down );
    result.push_back( k_lumiUp );
    result.push_back( k_lumiDown );
    
    if( sample_isSignal ){
      result.push_back( k_ISRUp );
      result.push_back( k_ISRDown );
      result.push_back( k_xsecUp );
      result.push_back( k_xsecDown );
    }
    else{
      result.push_back( k_nJetsSFK3Up );
      result.push_back( k_nJetsSFK3Down );
      result.push_back( k_nJetsSFK4Up );
      result.push_back( k_nJetsSFK4Down );
      result.push_back( k_diNuPtSF_Up );
      result.push_back( k_diNuPtSF_Down );
      result.push_back( k_topPtSFUp );
      result.push_back( k_topPtSFDown );
      result.push_back( k_metResUp );
      result.push_back( k_metResDown );
      result.push_back( k_nuPtSF_Up );
      result.push_back( k_nuPtSF_Down );
      result.push_back( k_WwidthSF_Up );
      result.push_back( k_WwidthSF_Down );
      result.push_back( k_hfXsec_Up );
      result.push_back( k_hfXsec_Down );
    }
    
    if( sample_isFastsim ){
      result.push_back( k_lepFSSFUp );
      result.push_back( k_lepFSSFDown );
    }
    
    break;
  
  case( analyzerInfo::k_CR0b ):
    result.push_back( k_nominal );
    result.push_back( k_bTagEffHFUp );
    result.push_back( k_bTagEffHFDown );
    result.push_back( k_bTagEffLFUp );
    result.push_back( k_bTagEffLFDown );
    result.push_back( k_lepSFUp );
    result.push_back( k_lepSFDown );
    result.push_back( k_pdfUp );
    result.push_back( k_pdfDown );
    result.push_back( k_alphasUp );
    result.push_back( k_alphasDown );
    result.push_back( k_q2Up );
    result.push_back( k_q2Down );
    result.push_back( k_lumiUp );
    result.push_back( k_lumiDown );
    
    if( sample_isSignal ){
      result.push_back( k_ISRUp );
      result.push_back( k_ISRDown );
      result.push_back( k_xsecUp );
      result.push_back( k_xsecDown );
    }
    else{
      result.push_back( k_topPtSFUp );
      result.push_back( k_topPtSFDown );
      result.push_back( k_metResUp );
      result.push_back( k_metResDown );
      result.push_back( k_nuPtSF_Up );
      result.push_back( k_nuPtSF_Down );
      result.push_back( k_WwidthSF_Up );
      result.push_back( k_WwidthSF_Down );
      result.push_back( k_hfXsec_Up );
      result.push_back( k_hfXsec_Down );
    }
    
    if( sample_isFastsim ){
      result.push_back( k_lepFSSFUp );
      result.push_back( k_lepFSSFDown );
    }
    
    break;

  case( analyzerInfo::k_CR1l_bulkWJets ):
    result.push_back( k_nominal );
    result.push_back( k_bTagEffHFUp );
    result.push_back( k_bTagEffHFDown );
    result.push_back( k_bTagEffLFUp );
    result.push_back( k_bTagEffLFDown );
    result.push_back( k_lepSFUp );
    result.push_back( k_lepSFDown );
    result.push_back( k_pdfUp );
    result.push_back( k_pdfDown );
    result.push_back( k_alphasUp );
    result.push_back( k_alphasDown );
    result.push_back( k_q2Up );
    result.push_back( k_q2Down );
    result.push_back( k_lumiUp );
    result.push_back( k_lumiDown );
    
    if( sample_isSignal ){
      result.push_back( k_ISRUp );
      result.push_back( k_ISRDown );
      result.push_back( k_xsecUp );
      result.push_back( k_xsecDown );
    }
    else{
      result.push_back( k_topPtSFUp );
      result.push_back( k_topPtSFDown );
    }
    
    if( sample_isFastsim ){
      result.push_back( k_lepFSSFUp );
      result.push_back( k_lepFSSFDown );
    }
    
    break;

  case( analyzerInfo::k_CR2l ):
    result.push_back( k_nominal );
    result.push_back( k_bTagEffHFUp );
    result.push_back( k_bTagEffHFDown );
    result.push_back( k_bTagEffLFUp );
    result.push_back( k_bTagEffLFDown );
    result.push_back( k_lepSFUp );
    result.push_back( k_lepSFDown );
    result.push_back( k_pdfUp );
    result.push_back( k_pdfDown );
    result.push_back( k_alphasUp );
    result.push_back( k_alphasDown );
    result.push_back( k_q2Up );
    result.push_back( k_q2Down );
    result.push_back( k_lumiUp );
    result.push_back( k_lumiDown );
    
    if( sample_isSignal ){
      result.push_back( k_ISRUp );
      result.push_back( k_ISRDown );
      result.push_back( k_xsecUp );
      result.push_back( k_xsecDown );
    }
    else{
      result.push_back( k_nJetsSFK3Up );
      result.push_back( k_nJetsSFK3Down );
      result.push_back( k_nJetsSFK4Up );
      result.push_back( k_nJetsSFK4Down );
      result.push_back( k_diNuPtSF_Up );
      result.push_back( k_diNuPtSF_Down );
      result.push_back( k_topPtSFUp );
      result.push_back( k_topPtSFDown );
      result.push_back( k_metResUp );
      result.push_back( k_metResDown );
    }
    
    if( sample_isFastsim ){
      result.push_back( k_lepFSSFUp );
      result.push_back( k_lepFSSFDown );
    }

    break;

  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( k_nominal );
    result.push_back( k_bTagEffHFUp );
    result.push_back( k_bTagEffHFDown );
    result.push_back( k_bTagEffLFUp );
    result.push_back( k_bTagEffLFDown );
    result.push_back( k_lepSFUp );
    result.push_back( k_lepSFDown );
    result.push_back( k_pdfUp );
    result.push_back( k_pdfDown );
    result.push_back( k_alphasUp );
    result.push_back( k_alphasDown );
    result.push_back( k_q2Up );
    result.push_back( k_q2Down );
    result.push_back( k_lumiUp );
    result.push_back( k_lumiDown );
    
    if( sample_isSignal ){
      result.push_back( k_ISRUp );
      result.push_back( k_ISRDown );
      result.push_back( k_xsecUp );
      result.push_back( k_xsecDown );
    }
    else{
      result.push_back( k_topPtSFUp );
      result.push_back( k_topPtSFDown );
      result.push_back( k_metResUp );
      result.push_back( k_metResDown );
    }
    
    if( sample_isFastsim ){
      result.push_back( k_lepFSSFUp );
      result.push_back( k_lepFSSFDown );
    }

    break;
    
  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( k_nominal );
    result.push_back( k_bTagEffHFUp );
    result.push_back( k_bTagEffHFDown );
    result.push_back( k_bTagEffLFUp );
    result.push_back( k_bTagEffLFDown );
    result.push_back( k_lepSFUp );
    result.push_back( k_lepSFDown );
    result.push_back( k_pdfUp );
    result.push_back( k_pdfDown );
    result.push_back( k_alphasUp );
    result.push_back( k_alphasDown );
    result.push_back( k_q2Up );
    result.push_back( k_q2Down );
    result.push_back( k_lumiUp );
    result.push_back( k_lumiDown );
    
    if( sample_isSignal ){
      result.push_back( k_ISRUp );
      result.push_back( k_ISRDown );
      result.push_back( k_xsecUp );
      result.push_back( k_xsecDown );
    }
    else{
      result.push_back( k_topPtSFUp );
      result.push_back( k_topPtSFDown );
    }

    if( sample_isFastsim ){
      result.push_back( k_lepFSSFUp );
      result.push_back( k_lepFSSFDown );
    }
    
    break;
  
  
  default:
    result.push_back( k_nominal );
    break;

  }; // end switch


  return result;
}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_id systematicInfo::getSystematicList_forLimit_lostLepton(){
  
  vect_id result;
  
  result.push_back( k_nominal );
  result.push_back( k_JESUp );
  result.push_back( k_JESDown );
  result.push_back( k_bTagEffHFUp );
  result.push_back( k_bTagEffHFDown );
  result.push_back( k_bTagEffLFUp );
  result.push_back( k_bTagEffLFDown );
  result.push_back( k_lepSFUp );
  result.push_back( k_lepSFDown );
  result.push_back( k_metResUp );
  result.push_back( k_metResDown );
  result.push_back( k_nJetsSFK3Up );
  result.push_back( k_nJetsSFK3Down );
  result.push_back( k_nJetsSFK4Up );
  result.push_back( k_nJetsSFK4Down );
  result.push_back( k_diNuPtSF_Up );
  result.push_back( k_diNuPtSF_Down );
  result.push_back( k_pdfUp );
  result.push_back( k_pdfDown );
  result.push_back( k_alphasUp );
  result.push_back( k_alphasDown );
  result.push_back( k_q2Up );
  result.push_back( k_q2Down );
  result.push_back( k_lumiUp );
  result.push_back( k_lumiDown );

  return result;
}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_id systematicInfo::getSystematicList_forLimit_oneLeptonNotFromTop(){

  vect_id result;

  result.push_back( k_nominal );
  result.push_back( k_JESUp );
  result.push_back( k_JESDown );
  result.push_back( k_bTagEffHFUp );
  result.push_back( k_bTagEffHFDown );
  result.push_back( k_bTagEffLFUp );
  result.push_back( k_bTagEffLFDown );
  result.push_back( k_lepSFUp );
  result.push_back( k_lepSFDown );
  result.push_back( k_lepFSSFUp );
  result.push_back( k_lepFSSFDown );
  result.push_back( k_metResUp );
  result.push_back( k_metResDown );
  result.push_back( k_nuPtSF_Up );
  result.push_back( k_nuPtSF_Down );
  result.push_back( k_WwidthSF_Up );
  result.push_back( k_WwidthSF_Down );
  result.push_back( k_hfXsec_Up );
  result.push_back( k_hfXsec_Down );
  result.push_back( k_pdfUp );
  result.push_back( k_pdfDown );
  result.push_back( k_alphasUp );
  result.push_back( k_alphasDown );
  result.push_back( k_q2Up );
  result.push_back( k_q2Down );
  result.push_back( k_lumiUp );
  result.push_back( k_lumiDown );

  return result;
}

//////////////////////////////////////////////////////////////////////

systematicInfo::vect_id systematicInfo::getSystematicList_forLimit_oneLeptonFromTop(){

  vect_id result;

  result.push_back( k_nominal );
  result.push_back( k_JESUp );
  result.push_back( k_JESDown );
  result.push_back( k_bTagEffHFUp );
  result.push_back( k_bTagEffHFDown );
  result.push_back( k_bTagEffLFUp );
  result.push_back( k_bTagEffLFDown );
  result.push_back( k_lepSFUp );
  result.push_back( k_lepSFDown );
  result.push_back( k_lepFSSFUp );
  result.push_back( k_lepFSSFDown );
  result.push_back( k_metResUp );
  result.push_back( k_metResDown );
  result.push_back( k_pdfUp );
  result.push_back( k_pdfDown );
  result.push_back( k_alphasUp );
  result.push_back( k_alphasDown );
  result.push_back( k_q2Up );
  result.push_back( k_q2Down );
  result.push_back( k_lumiUp );
  result.push_back( k_lumiDown );

  return result;
}

/////////////////////////////////////////////////////////////////////

systematicInfo::vect_id systematicInfo::getSystematicList_forLimit_ZtoNuNu(){

  vect_id result;

  result.push_back( k_nominal );
  result.push_back( k_JESUp );
  result.push_back( k_JESDown );
  result.push_back( k_bTagEffHFUp );
  result.push_back( k_bTagEffHFDown );
  result.push_back( k_bTagEffLFUp );
  result.push_back( k_bTagEffLFDown );
  result.push_back( k_lepSFUp );
  result.push_back( k_lepSFDown );
  result.push_back( k_lepFSSFUp );
  result.push_back( k_lepFSSFDown );
  result.push_back( k_metResUp );
  result.push_back( k_metResDown );
  result.push_back( k_pdfUp );
  result.push_back( k_pdfDown );
  result.push_back( k_alphasUp );
  result.push_back( k_alphasDown );
  result.push_back( k_q2Up );
  result.push_back( k_q2Down );
  result.push_back( k_lumiUp );
  result.push_back( k_lumiDown );

  return result;
}

/////////////////////////////////////////////////////////////////////

systematicInfo::vect_id systematicInfo::getSystematicList_forLimit_sig(){

  vect_id result;

  result.push_back( k_nominal );
  result.push_back( k_JESUp );
  result.push_back( k_JESDown );
  result.push_back( k_bTagEffHFUp );
  result.push_back( k_bTagEffHFDown );
  result.push_back( k_bTagEffLFUp );
  result.push_back( k_bTagEffLFDown );
  result.push_back( k_lepSFUp );
  result.push_back( k_lepSFDown );
  result.push_back( k_lepFSSFUp );
  result.push_back( k_lepFSSFDown );
  result.push_back( k_pdfUp );
  result.push_back( k_pdfDown );
  result.push_back( k_alphasUp );
  result.push_back( k_alphasDown );
  result.push_back( k_q2Up );
  result.push_back( k_q2Down );
  result.push_back( k_lumiUp );
  result.push_back( k_lumiDown );
  result.push_back( k_ISRUp );
  result.push_back( k_ISRDown );
  result.push_back( k_xsecUp );
  result.push_back( k_xsecDown );

  return result;
}

/////////////////////////////////////////////////////////////////////

