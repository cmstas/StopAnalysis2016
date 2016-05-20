#ifndef eventWeightInfo_H
#define eventWeightInfo_H

// SNT CORE
#include "../../CORE/MCSelections.h"

// stopCORE
#include "eventWeight_bTagSF.h"
#include "eventWeight_lepSF.h"
#include "sampleInfo.h"
#include "stop_1l_babyAnalyzer.h"

// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TH3.h"
#include "Math/GenVector/VectorUtil.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// C
#include <string>
#include <vector>


//
// CLASS
//
class eventWeightInfo{

 public:

  // Sample info 
  sampleInfo::sampleUtil *sample_info;

  // Utility Vars
  double DR_MATCHED;
  double LUMI;
  double LUMI_ERR;

  // Counter histograms stored in babies
  TH1D *h_bkg_counter;
  TH2D *h_sig_counter_nEvents;
  TH3D *h_sig_counter;
  
  TFile *f_sig_xsec;
  TH1D *h_sig_xsec;

  // bTag machinery
  bool useBTagSFs_fromUtils;
  eventWeight_bTagSF *bTagSFUtil;

  // Lepton SF machinery
  bool useLepSFs_fromUtils;
  eventWeight_lepSF *lepSFUtil;

  // Variables to form baseline event weight
  double nEvents;
  double xsec;
  double xsec_err;
  
  // Event weights for each systematic
  double sf_nominal;
  
  double sf_bTag;
  double sf_bTagEffHF_up;
  double sf_bTagEffHF_dn;
  double sf_bTagEffLF_up;
  double sf_bTagEffLF_dn;
  double norm_bTagEff;
  double norm_bTagEffHF_up;
  double norm_bTagEffHF_dn;
  double norm_bTagEffLF_up;
  double norm_bTagEffLF_dn;
  
  double sf_lep;
  double sf_lep_up;
  double sf_lep_dn;
  
  double sf_vetoLep;
  double sf_vetoLep_up;
  double sf_vetoLep_dn;
  
  double sf_lepFS;
  double sf_lepFS_up;
  double sf_lepFS_dn;
  
  double sf_topPt;
  double sf_topPt_up;
  double sf_topPt_dn;
  
  double sf_metRes;
  double sf_metRes_up;
  double sf_metRes_dn;
  
  double sf_nJetsK3;
  double sf_nJetsK3_up;
  double sf_nJetsK3_dn;
  
  double sf_nJetsK4;
  double sf_nJetsK4_up;
  double sf_nJetsK4_dn;
  
  double sf_diNuPt;
  double sf_diNuPt_up;
  double sf_diNuPt_dn;
  
  double sf_nuPt;
  double sf_nuPt_up;
  double sf_nuPt_dn;
  
  double sf_Wwidth_up;
  double sf_Wwidth_dn;
  
  double sf_hfXsec_up;
  double sf_hfXsec_dn;
  
  double sf_alphas_up;
  double sf_alphas_dn;
  double norm_alphas;
  double norm_alphas_up;
  double norm_alphas_dn;
  
  double sf_q2_up;
  double sf_q2_dn;
  double norm_q2;
  double norm_q2_up;
  double norm_q2_dn;
  
  double sf_lumi;
  double sf_lumi_up;
  double sf_lumi_dn;
  
  double sf_ISR;
  double sf_ISR_up;
  double sf_ISR_dn;
  double norm_ISR;
  double norm_ISR_up;
  double norm_ISR_dn;

  double sf_xsec_up;
  double sf_xsec_dn;
  
  
  eventWeightInfo( sampleInfo::ID sample, bool useBTagUtils=false, bool useLepSFUtils=false );
  ~eventWeightInfo();

  void getWeightHistogramFromBaby( TFile *sourceFile );

  void initializeWeights();

  void getEventWeights();
  
  void getBTagWeight_fromUtils( double &wgt_btagsf, double &wgt_btagsf_hf_up, double &wgt_btagsf_hf_dn, double &wgt_btagsf_lf_up, double &wgt_btagsf_lf_dn ); 

  void getLepSFWeight_fromUtils( double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepFSSF, double &weight_lepFSSF_Up, double &weight_lepFSSF_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn ); 
  
  void getTopPtWeight( double &weight_topPt, double &weight_topPt_up, double &weight_topPt_dn );

  void getMetResWeight( double &weight_metRes, double &weight_metRes_up, double &weight_metRes_dn );

  void getNJetsSF_K3( double &weight_K3, double &weight_K3_up, double &weight_K3_dn );

  void getNJetsSF_K4( double &weight_K4, double &weight_K4_up, double &weight_K4_dn );
  
  void getDiNuPtSF( double &weight_diNuPt, double &weight_diNuPt_up, double &weight_diNuPt_dn );

  void getNuPtSF( double &weight_nuPt, double &weight_nuPt_up, double &weight_nuPt_dn );

  void getWwidthSF( double &weight_Wwidth_up, double &weight_Wwidth_dn );

  void getWJetsHFXSecSF( double &weight_hfXsec_up, double &weight_hfXsec_dn );

  void getAlphasWeight( double &weight_alphas_up, double &weight_alphas_dn );

  void getQ2Weight( double &weight_q2_up, double &weight_q2_dn );

  void getLumiWeight( double &weight_lumi, double &weight_lumi_up, double &weight_lumi_dn );

  void getISRWeight( double &weight_ISR, double &weight_ISR_up, double &weight_ISR_dn );

  void getSignalXSecWeight( double mStop, double &weight_xsec, double &weight_xsec_up, double &weight_xsec_dn );

}; // end class def


#endif
