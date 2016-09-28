#include "categoryInfo.h"

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_ICHEP(){
  
  int nBins_ICHEP_ = 29;
  TH1D *result = new TH1D("h_yields_SR_ICHEP", "Yields, ICHEP Signal Regions", nBins_ICHEP_, 1.0, (double)nBins_ICHEP_+1.0);

  result->GetXaxis()->SetBinLabel(1, "incl");
  
  result->GetXaxis()->SetBinLabel(2, "ee2jets");
  result->GetXaxis()->SetBinLabel(3, "ee2jets_ge6p4modTop");
  result->GetXaxis()->SetBinLabel(4, "ee2jets_ge6p4modTop_150to250met");
  result->GetXaxis()->SetBinLabel(5, "ee2jets_ge6p4modTop_250to350met");
  result->GetXaxis()->SetBinLabel(6, "ee2jets_ge6p4modTop_350to450met");
  result->GetXaxis()->SetBinLabel(7, "ee2jets_ge6p4modTop_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(8, "ee3jets");
  result->GetXaxis()->SetBinLabel(9, "ee3jets_ge200mt2w");
  result->GetXaxis()->SetBinLabel(10, "ee3jets_ge200mt2w_150to250met");
  result->GetXaxis()->SetBinLabel(11, "ee3jets_ge200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(12, "ee3jets_ge200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(13, "ee3jets_ge200mt2w_450toInfmet");
  result->GetXaxis()->SetBinLabel(14, "ee3jets_ge200mt2w_450to550met");
  result->GetXaxis()->SetBinLabel(15, "ee3jets_ge200mt2w_550toInfmet");

  result->GetXaxis()->SetBinLabel(16, "ge4jets");
  result->GetXaxis()->SetBinLabel(17, "ge4jets_lt200mt2w");
  result->GetXaxis()->SetBinLabel(18, "ge4jets_lt200mt2w_150to250met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_lt200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(20, "ge4jets_lt200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(21, "ge4jets_lt200mt2w_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(22, "ge4jets_ge200mt2w");
  result->GetXaxis()->SetBinLabel(23, "ge4jets_ge200mt2w_150to250met");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge200mt2w_450to550met");
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge200mt2w_550toInfmet");
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge200mt2w_550to650met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge200mt2w_650toInfmet");

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_SR_ICHEP( int jesType, bool add2ndLepToMet ){

  vector<int> result;

  int nGoodJets = babyAnalyzer.ngoodjets();
  if( jesType==1 )  nGoodJets = babyAnalyzer.jup_ngoodjets();
  if( jesType==-1 ) nGoodJets = babyAnalyzer.jdown_ngoodjets();

  double modTopness = babyAnalyzer.topnessMod();
  if( add2ndLepToMet){
    if(jesType==0)  modTopness = babyAnalyzer.topnessMod_rl();
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_rl_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_rl_jdown();
  }
  else{
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_jdown();
  }

  double mt2w = babyAnalyzer.MT2W();
  if( add2ndLepToMet){
    if(jesType==0)  mt2w = babyAnalyzer.MT2W_rl();
    if(jesType==1)  mt2w = babyAnalyzer.MT2W_rl_jup();
    if(jesType==-1) mt2w = babyAnalyzer.MT2W_rl_jdown();
  }
  else{
    if(jesType==1)  mt2w = babyAnalyzer.MT2W_jup();
    if(jesType==-1) mt2w = babyAnalyzer.MT2W_jdown();
  }

  double met = babyAnalyzer.pfmet();
  if( add2ndLepToMet){
    if(jesType==0)  met = babyAnalyzer.pfmet_rl();
    if(jesType==1)  met = babyAnalyzer.pfmet_rl_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_rl_jdown();
  }
  else{
    if(jesType==1)  met = babyAnalyzer.pfmet_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_jdown();
  }
  

  // Incl
  result.push_back(1);

  if( nGoodJets==2 ){
    
    // ==2 jets
    result.push_back(2);

    if( modTopness>=6.4){

      // ==2 jets, modTopness>=6.4, met>=250
      if( met>=250 ) result.push_back(3);

      // ==2 jets, modTopness>=6.4, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(4);

      // ==2 jets, modTopness>=6.4, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(5);
       
      // ==2 jets, modTopness>=6.4, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(6);

      // ==2 jets, modTopness>=6.4, met>=450
      if( met>=450.0 ) result.push_back(7);

    } // end if modTopness>=6.4
  } // end if nGoodJets==2

  if( nGoodJets==3 ){

    // ==3 jets
    result.push_back(8);

    if( mt2w>=200.0){

      // ==3 jets, mt2w>=200.0, met>=250
      if( met>=250 ) result.push_back(9);

      // ==3 jets, mt2w>=200.0, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(10);

      // ==3 jets, mt2w>=200.0, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(11);
       
      // ==3 jets, mt2w>=200.0, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(12);

      // ==3 jets, mt2w>=200.0, met>=450
      if( met>=450.0 ) result.push_back(13);

      // ==3 jets, mt2w>=200.0, 450<=met<550
      if( met>=450.0 && met<550 ) result.push_back(14);

      // ==3 jets, mt2w>=200.0, met>=550
      if( met>=550.0 ) result.push_back(15);

    } // end if mt2w>=200
  } // end if nGoodJets>=3

  if( nGoodJets>=4 ){

    // >=4 jets
    result.push_back(16);

    if( mt2w<200.0){

      // >=4 jets, mt2w<200.0, met>=250
      if( met>=250 ) result.push_back(17);

      // >=4 jets, mt2w<200.0, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(18);

      // >=4 jets, mt2w<200.0, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(19);
       
      // >=4 jets, mt2w<200.0, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(20);

      // >=4 jets, mt2w<200.0, met>=450
      if( met>=450.0 ) result.push_back(21);

    } // end if mt2w<200.0

    if( mt2w>=200.0){

      // >=4 jets, mt2w>=200.0, met>=250
      if( met>=250 ) result.push_back(22);

      // >=4 jets, mt2w>=200.0, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(23);

      // >=4 jets, mt2w>=200.0, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(24);
       
      // >=4 jets, mt2w>=200.0, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(25);

      // >=4 jets, mt2w>=200.0, 450<=met<550
      if( met>=450.0 && met<550 ) result.push_back(26);

      // >=4 jets, mt2w>=200.0, met>=550
      if( met>=550.0 ) result.push_back(27);

      // >=4 jets, mt2w>=200.0, 550<=met<650
      if( met>=550.0 && met<650 ) result.push_back(28);

      // >=4 jets, mt2w>=200.0, met>=650
      if( met>=650.0 ) result.push_back(29);

    } // end if mt2w>=200

  } // end if nGoodJets>=4


  return result;

}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_ICHEP_ext30fb(){

  int nBins_ICHEP_ext30fb_ = 21;
  TH1D *result = new TH1D("h_yields_SR_ICHEP_ext30fb", "Yields, ICHEP Signal Regions, extnded to 30fb", nBins_ICHEP_ext30fb_, 1.0, (double)nBins_ICHEP_ext30fb_+1.0);

  result->GetXaxis()->SetBinLabel(1, "ee2jets_ge6p4modTop_250to350met");
  result->GetXaxis()->SetBinLabel(2, "ee2jets_ge6p4modTop_350to450met");
  result->GetXaxis()->SetBinLabel(3, "ee2jets_ge6p4modTop_450to550met");
  result->GetXaxis()->SetBinLabel(4, "ee2jets_ge6p4modTop_550to650met");
  result->GetXaxis()->SetBinLabel(5, "ee2jets_ge6p4modTop_650toInfmet");
  
  result->GetXaxis()->SetBinLabel(6, "ee3jets_ge200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(7, "ee3jets_ge200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(8, "ee3jets_ge200mt2w_450to550met");
  result->GetXaxis()->SetBinLabel(9, "ee3jets_ge200mt2w_550to650met");
  result->GetXaxis()->SetBinLabel(10, "ee3jets_ge200mt2w_650toInfmet");

  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt200mt2w_450to550met");
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt200mt2w_550to650met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt200mt2w_650toInfmet");
  
  result->GetXaxis()->SetBinLabel(16, "ge4jets_ge200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(17, "ge4jets_ge200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(18, "ge4jets_ge200mt2w_450to550met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_ge200mt2w_550to650met");
  result->GetXaxis()->SetBinLabel(20, "ge4jets_ge200mt2w_650to800met");
  result->GetXaxis()->SetBinLabel(21, "ge4jets_ge200mt2w_800toInfmet");

  return result;

}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_SR_ICHEP_ext30fb( int jesType, bool add2ndLepToMet ){
  
  vector<int> result;
 
  int nGoodJets = babyAnalyzer.ngoodjets();
  if( jesType==1 )  nGoodJets = babyAnalyzer.jup_ngoodjets();
  if( jesType==-1 ) nGoodJets = babyAnalyzer.jdown_ngoodjets();

  double modTopness = babyAnalyzer.topnessMod();
  if( add2ndLepToMet){
    if(jesType==0)  modTopness = babyAnalyzer.topnessMod_rl();
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_rl_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_rl_jdown();
  }
  else{
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_jdown();
  }

  double mt2w = babyAnalyzer.MT2W();
  if( add2ndLepToMet){
    if(jesType==0)  mt2w = babyAnalyzer.MT2W_rl();
    if(jesType==1)  mt2w = babyAnalyzer.MT2W_rl_jup();
    if(jesType==-1) mt2w = babyAnalyzer.MT2W_rl_jdown();
  }
  else{
    if(jesType==1)  mt2w = babyAnalyzer.MT2W_jup();
    if(jesType==-1) mt2w = babyAnalyzer.MT2W_jdown();
  }

  double met = babyAnalyzer.pfmet();
  if( add2ndLepToMet){
    if(jesType==0)  met = babyAnalyzer.pfmet_rl();
    if(jesType==1)  met = babyAnalyzer.pfmet_rl_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_rl_jdown();
  }
  else{
    if(jesType==1)  met = babyAnalyzer.pfmet_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_jdown();
  }
  

  if(nGoodJets==2&&modTopness>6.4) {
    if(     met>650) result.push_back(5);
    else if(met>550) result.push_back(4);
    else if(met>450) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
  }

  if(nGoodJets==3&&mt2w>200) {
    if(     met>650) result.push_back(10);
    else if(met>550) result.push_back(9);
    else if(met>450) result.push_back(8);
    else if(met>350) result.push_back(7);
    else if(met>250) result.push_back(6);
  }

  if(nGoodJets>=4&&mt2w<=200) {
    if(     met>650) result.push_back(15);
    else if(met>550) result.push_back(14);
    else if(met>450) result.push_back(13);
    else if(met>350) result.push_back(12);
    else if(met>250) result.push_back(11);
  }

  if(nGoodJets>=4&&mt2w>200) {
    if(     met>800) result.push_back(21);
    else if(met>650) result.push_back(20);
    else if(met>550) result.push_back(19);
    else if(met>450) result.push_back(18);
    else if(met>350) result.push_back(17);
    else if(met>250) result.push_back(16);
  }

  return result;

}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_mlb_v1(){

  int nBins_dev_ext30fb_mlb_v1_ = 29;
  TH1D *result = new TH1D("h_yields_SR_dev_ext30fb_mlb_v1", "Yields, Signal Regions, extnded to 30fb, binned with Mlb", nBins_dev_ext30fb_mlb_v1_, 1.0, (double)nBins_dev_ext30fb_mlb_v1_+1.0);

  result->GetXaxis()->SetBinLabel(1, "lt4jets_ge7p5modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(2, "lt4jets_ge7p5modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(3, "lt4jets_ge7p5modTop_lt175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(4, "lt4jets_ge7p5modTop_lt175mlb_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(5, "lt4jets_ge7p5modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(6, "lt4jets_ge7p5modTop_ge175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(7, "lt4jets_ge7p5modTop_ge175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(8, "lt4jets_ge7p5modTop_ge175mlb_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt0modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt0modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt0modTop_lt175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt0modTop_lt175mlb_550to650met");
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt0modTop_lt175mlb_650toInfmet");
  
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt0modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt0modTop_ge175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(16, "ge4jets_lt0modTop_ge175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(17, "ge4jets_lt0modTop_ge175mlb_550toInfmet");

  result->GetXaxis()->SetBinLabel(18, "ge4jets_0to7p5modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_0to7p5modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(20, "ge4jets_0to7p5modTop_lt175mlb_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(21, "ge4jets_0to7p5modTop_ge175mlb_250to400met");
  result->GetXaxis()->SetBinLabel(22, "ge4jets_0to7p5modTop_ge175mlb_400toInfmet");

  result->GetXaxis()->SetBinLabel(23, "ge4jets_ge7p5modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge7p5modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge7p5modTop_lt175mlb_450to600met");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge7p5modTop_lt175mlb_600toInfmet");
  
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge7p5modTop_ge175mlb_250to400met");
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge7p5modTop_ge175mlb_400to650met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge7p5modTop_ge175mlb_650toInfmet");
    
  return result;
}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_SR_dev_ext30fb_mlb_v1( int jesType, bool add2ndLepToMet ){

  vector<int> result;

  int nGoodJets = babyAnalyzer.ngoodjets();
  if( jesType==1 )  nGoodJets = babyAnalyzer.jup_ngoodjets();
  if( jesType==-1 ) nGoodJets = babyAnalyzer.jdown_ngoodjets();

  double modTopness = babyAnalyzer.topnessMod();
  if( add2ndLepToMet){
    if(jesType==0)  modTopness = babyAnalyzer.topnessMod_rl();
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_rl_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_rl_jdown();
  }
  else{
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_jdown();
  }


  double mlb = babyAnalyzer.Mlb_closestb();

  double met = babyAnalyzer.pfmet();
  if( add2ndLepToMet){
    if(jesType==0)  met = babyAnalyzer.pfmet_rl();
    if(jesType==1)  met = babyAnalyzer.pfmet_rl_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_rl_jdown();
  }
  else{
    if(jesType==1)  met = babyAnalyzer.pfmet_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_jdown();
  }
  

  //v11 - tmod7p5/Mlb - 29 bins
  if( nGoodJets<=3&&modTopness>=7.5&& mlb<175) {
    if(     met>550) result.push_back(4);
    else if(met>450) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
  }
  if( nGoodJets<=3&&modTopness>=7.5&&mlb>=175) {
    if(     met>550) result.push_back(8);
    else if(met>450) result.push_back(7);
    else if(met>350) result.push_back(6);
    else if(met>250) result.push_back(5);
  }
  if(nGoodJets>=4&&modTopness<0&& mlb<175) {
    if(     met>650) result.push_back(13);
    else if(met>550) result.push_back(12);
    else if(met>450) result.push_back(11);
    else if(met>350) result.push_back(10);
    else if(met>250) result.push_back(9);
  }
  if(nGoodJets>=4&&modTopness<0&&mlb>=175) {
    if(     met>550) result.push_back(17);
    else if(met>450) result.push_back(16);
    else if(met>350) result.push_back(15);
    else if(met>250) result.push_back(14);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<7.5&& mlb<175) {
    if(     met>450) result.push_back(20);
    else if(met>350) result.push_back(19);
    else if(met>250) result.push_back(18);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<7.5&&mlb>=175) {
    if(     met>400) result.push_back(22);
    else if(met>250) result.push_back(21);
  }
  if(nGoodJets>=4&&modTopness>=7.5&& mlb<175) {
    if(     met>600) result.push_back(26);
    else if(met>450) result.push_back(25);
    else if(met>350) result.push_back(24);
    else if(met>250) result.push_back(23);
  }
  if(nGoodJets>=4&&modTopness>=7.5&&mlb>=175) {
    if(     met>650) result.push_back(29);
    else if(met>400) result.push_back(28);
    else if(met>250) result.push_back(27);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_bJetPt_v1(){

  int nBins_dev_ext30fb_bJetPt_v1_ = 29;
  TH1D *result = new TH1D("h_yields_SR_dev_ext30fb_bJetPt_v1", "Yields, Signal Regions, extnded to 30fb, binned with BJetPt", nBins_dev_ext30fb_bJetPt_v1_, 1.0, (double)nBins_dev_ext30fb_bJetPt_v1_+1.0);

  result->GetXaxis()->SetBinLabel(1, "lt4jets_ge7p5modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(2, "lt4jets_ge7p5modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(3, "lt4jets_ge7p5modTop_lt200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(4, "lt4jets_ge7p5modTop_lt200bJetPt_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(5, "lt4jets_ge7p5modTop_ge200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(6, "lt4jets_ge7p5modTop_ge200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(7, "lt4jets_ge7p5modTop_ge200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(8, "lt4jets_ge7p5modTop_ge200bJetPt_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt0modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt0modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt0modTop_lt200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt0modTop_lt200bJetPt_550to650met");
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt0modTop_lt200bJetPt_650toInfmet");
  
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt0modTop_ge200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt0modTop_ge200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(16, "ge4jets_lt0modTop_ge200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(17, "ge4jets_lt0modTop_ge200bJetPt_550toInfmet");

  result->GetXaxis()->SetBinLabel(18, "ge4jets_0to7p5modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_0to7p5modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(20, "ge4jets_0to7p5modTop_lt200bJetPt_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(21, "ge4jets_0to7p5modTop_ge200bJetPt_250to400met");
  result->GetXaxis()->SetBinLabel(22, "ge4jets_0to7p5modTop_ge200bJetPt_400toInfmet");

  result->GetXaxis()->SetBinLabel(23, "ge4jets_ge7p5modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge7p5modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge7p5modTop_lt200bJetPt_450to600met");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge7p5modTop_lt200bJetPt_600toInfmet");
  
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge7p5modTop_ge200bJetPt_250to400met");
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge7p5modTop_ge200bJetPt_400to650met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge7p5modTop_ge200bJetPt_650toInfmet");

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_SR_dev_ext30fb_bJetPt_v1( int jesType, bool add2ndLepToMet ){

  vector<int> result;


  int nGoodJets = babyAnalyzer.ngoodjets();
  if( jesType==1 )  nGoodJets = babyAnalyzer.jup_ngoodjets();
  if( jesType==-1 ) nGoodJets = babyAnalyzer.jdown_ngoodjets();

  double modTopness = babyAnalyzer.topnessMod();
  if( add2ndLepToMet){
    if(jesType==0)  modTopness = babyAnalyzer.topnessMod_rl();
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_rl_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_rl_jdown();
  }
  else{
    if(jesType==1)  modTopness = babyAnalyzer.topnessMod_jup();
    if(jesType==-1) modTopness = babyAnalyzer.topnessMod_jdown();
  }


  double leadBJetPt = babyAnalyzer.ak4pfjets_leadbtag_p4().Pt();
  if(jesType==1) leadBJetPt = babyAnalyzer.jup_ak4pfjets_leadbtag_p4().Pt();
  if(jesType==-1) leadBJetPt = babyAnalyzer.jdown_ak4pfjets_leadbtag_p4().Pt();
    

  double met = babyAnalyzer.pfmet();
  if( add2ndLepToMet){
    if(jesType==0)  met = babyAnalyzer.pfmet_rl();
    if(jesType==1)  met = babyAnalyzer.pfmet_rl_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_rl_jdown();
  }
  else{
    if(jesType==1)  met = babyAnalyzer.pfmet_jup();
    if(jesType==-1) met = babyAnalyzer.pfmet_jdown();
  }

  
  //v12 - tmod7p5/bpt - 29 bins
  if( nGoodJets<=3&&modTopness>=7.5&& leadBJetPt<200) {
    if(     met>550) result.push_back(4);
    else if(met>450) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
  }
  if( nGoodJets<=3&&modTopness>=7.5&&leadBJetPt>=200) {
    if(met>550)      result.push_back(8);
    else if(met>450) result.push_back(7);
    else if(met>350) result.push_back(6);
    else if(met>250) result.push_back(5);
  }
  if(nGoodJets>=4&&modTopness<0&& leadBJetPt<200) {
    if(     met>650) result.push_back(13);
    else if(met>550) result.push_back(12);
    else if(met>450) result.push_back(11);
    else if(met>350) result.push_back(10);
    else if(met>250) result.push_back(9);
  }
  if(nGoodJets>=4&&modTopness<0&&leadBJetPt>=200) {
    if(     met>550) result.push_back(17);
    else if(met>450) result.push_back(16);
    else if(met>350) result.push_back(15);
    else if(met>250) result.push_back(14);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<7.5&& leadBJetPt<200) {
    if(     met>450) result.push_back(20);
    else if(met>350) result.push_back(19);
    else if(met>250) result.push_back(18);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<7.5&&leadBJetPt>=200) {
    if(     met>350) result.push_back(22);
    else if(met>250) result.push_back(21);
  }
  if(nGoodJets>=4&&modTopness>=7.5&& leadBJetPt<200) {
    if(     met>650) result.push_back(26);
    else if(met>500) result.push_back(25);
    else if(met>400) result.push_back(24);
    else if(met>250) result.push_back(23);
  }
  if(nGoodJets>=4&&modTopness>=7.5&&leadBJetPt>=200) {
    if(     met>650) result.push_back(29);
    else if(met>400) result.push_back(28);
    else if(met>250) result.push_back(27);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////
