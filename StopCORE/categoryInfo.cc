#include "categoryInfo.h"

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_ICHEP(){
  
  int nBins_ICHEP_ = 29;
  TH1D *result = new TH1D("h_yields_SR_ICHEP", "Yields, ICHEP Signal Regions", nBins_ICHEP_, 1.0, (double)nBins_ICHEP_+1.0);

  result->GetXaxis()->SetBinLabel(1, "ee2jets_ge6p4modTop_250to350met");
  result->GetXaxis()->SetBinLabel(2, "ee2jets_ge6p4modTop_350to450met");
  result->GetXaxis()->SetBinLabel(3, "ee2jets_ge6p4modTop_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(4, "ee3jets_ge200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(5, "ee3jets_ge200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(6, "ee3jets_ge200mt2w_450to550met");
  result->GetXaxis()->SetBinLabel(7, "ee3jets_ge200mt2w_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(8, "ge4jets_lt200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt200mt2w_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(11, "ge4jets_ge200mt2w_250to350met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_ge200mt2w_350to450met");
  result->GetXaxis()->SetBinLabel(13, "ge4jets_ge200mt2w_450to550met");
  result->GetXaxis()->SetBinLabel(14, "ge4jets_ge200mt2w_550to650met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_ge200mt2w_650toInfmet");

  // Inclusive Bins
  result->GetXaxis()->SetBinLabel(16, "incl");
  result->GetXaxis()->SetBinLabel(17, "ee2jets");
  result->GetXaxis()->SetBinLabel(18, "ee2jets_ge6p4modTop");
  result->GetXaxis()->SetBinLabel(19, "ee2jets_ge6p4modTop_150to250met");
  result->GetXaxis()->SetBinLabel(20, "ee3jets");
  result->GetXaxis()->SetBinLabel(21, "ee3jets_ge200mt2w");
  result->GetXaxis()->SetBinLabel(22, "ee3jets_ge200mt2w_150to250met");
  result->GetXaxis()->SetBinLabel(23, "ee3jets_ge200mt2w_450toInfmet");
  result->GetXaxis()->SetBinLabel(24, "ge4jets");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_lt200mt2w");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_lt200mt2w_150to250met");
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge200mt2w");
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge200mt2w_150to250met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge200mt2w_550toInfmet");
  
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
  result.push_back(16);

  if( nGoodJets==2 ){
    
    // ==2 jets
    result.push_back(17);

    if( modTopness>=6.4){

      // ==2 jets, modTopness>=6.4, met>=250
      if( met>=250 ) result.push_back(18);

      // ==2 jets, modTopness>=6.4, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(19);

      // ==2 jets, modTopness>=6.4, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(1);
       
      // ==2 jets, modTopness>=6.4, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(2);

      // ==2 jets, modTopness>=6.4, met>=450
      if( met>=450.0 ) result.push_back(3);

    } // end if modTopness>=6.4
  } // end if nGoodJets==2

  if( nGoodJets==3 ){

    // ==3 jets
    result.push_back(20);

    if( mt2w>=200.0){

      // ==3 jets, mt2w>=200.0, met>=250
      if( met>=250 ) result.push_back(21);

      // ==3 jets, mt2w>=200.0, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(22);

      // ==3 jets, mt2w>=200.0, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(4);
       
      // ==3 jets, mt2w>=200.0, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(5);

      // ==3 jets, mt2w>=200.0, met>=450
      if( met>=450.0 ) result.push_back(23);

      // ==3 jets, mt2w>=200.0, 450<=met<550
      if( met>=450.0 && met<550 ) result.push_back(6);

      // ==3 jets, mt2w>=200.0, met>=550
      if( met>=550.0 ) result.push_back(7);

    } // end if mt2w>=200
  } // end if nGoodJets>=3

  if( nGoodJets>=4 ){

    // >=4 jets
    result.push_back(24);

    if( mt2w<200.0){

      // >=4 jets, mt2w<200.0, met>=250
      if( met>=250 ) result.push_back(25);

      // >=4 jets, mt2w<200.0, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(26);

      // >=4 jets, mt2w<200.0, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(8);
       
      // >=4 jets, mt2w<200.0, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(9);

      // >=4 jets, mt2w<200.0, met>=450
      if( met>=450.0 ) result.push_back(10);

    } // end if mt2w<200.0

    if( mt2w>=200.0){

      // >=4 jets, mt2w>=200.0, met>=250
      if( met>=250 ) result.push_back(27);

      // >=4 jets, mt2w>=200.0, 150<=met<250
      if( met>=150.0 && met<250 ) result.push_back(28);

      // >=4 jets, mt2w>=200.0, 250<=met<350
      if( met>=250.0 && met<350 ) result.push_back(11);
       
      // >=4 jets, mt2w>=200.0, 350<=met<450
      if( met>=350.0 && met<450 ) result.push_back(12);

      // >=4 jets, mt2w>=200.0, 450<=met<550
      if( met>=450.0 && met<550 ) result.push_back(13);

      // >=4 jets, mt2w>=200.0, met>=550
      if( met>=550.0 ) result.push_back(29);

      // >=4 jets, mt2w>=200.0, 550<=met<650
      if( met>=550.0 && met<650 ) result.push_back(14);

      // >=4 jets, mt2w>=200.0, met>=650
      if( met>=650.0 ) result.push_back(15);

    } // end if mt2w>=200

  } // end if nGoodJets>=4


  return result;

}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_ICHEP_ext30fb(){

  int nBins_ICHEP_ext30fb_ = 25;
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

  // Inclusive bins for bkg estimates
  result->GetXaxis()->SetBinLabel(22, "ee2jets_ge6p4modTop_550toInfmet");
  result->GetXaxis()->SetBinLabel(23, "ee3jets_ge200mt2w_550toInfmet");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_lt200mt2w_550toInfmet");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge200mt2w_650toInfmet");
  

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
    
    if(met>550) result.push_back(22);
  }

  if(nGoodJets==3&&mt2w>200) {
    if(     met>650) result.push_back(10);
    else if(met>550) result.push_back(9);
    else if(met>450) result.push_back(8);
    else if(met>350) result.push_back(7);
    else if(met>250) result.push_back(6);
    
    if(met>550) result.push_back(23);
  }

  if(nGoodJets>=4&&mt2w<=200) {
    if(     met>650) result.push_back(15);
    else if(met>550) result.push_back(14);
    else if(met>450) result.push_back(13);
    else if(met>350) result.push_back(12);
    else if(met>250) result.push_back(11);

    if(met>550) result.push_back(24);
  }

  if(nGoodJets>=4&&mt2w>200) {
    if(     met>800) result.push_back(21);
    else if(met>650) result.push_back(20);
    else if(met>550) result.push_back(19);
    else if(met>450) result.push_back(18);
    else if(met>350) result.push_back(17);
    else if(met>250) result.push_back(16);

    if(met>650) result.push_back(25);
  }

  return result;

}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_mlb_v1(){

  int nBins_dev_ext30fb_mlb_v1_ = 76;
  TH1D *result = new TH1D("h_yields_SR_dev_ext30fb_mlb_v1", "Yields, Signal Regions, extnded to 30fb, binned with Mlb", nBins_dev_ext30fb_mlb_v1_, 1.0, (double)nBins_dev_ext30fb_mlb_v1_+1.0);

  result->GetXaxis()->SetBinLabel(1, "lt4jets_ge10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(2, "lt4jets_ge10modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(3, "lt4jets_ge10modTop_lt175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(4, "lt4jets_ge10modTop_lt175mlb_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(5, "lt4jets_ge10modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(6, "lt4jets_ge10modTop_ge175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(7, "lt4jets_ge10modTop_ge175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(8, "lt4jets_ge10modTop_ge175mlb_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt0modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt0modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt0modTop_lt175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt0modTop_lt175mlb_550to650met");
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt0modTop_lt175mlb_650toInfmet");
  
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt0modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt0modTop_ge175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(16, "ge4jets_lt0modTop_ge175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(17, "ge4jets_lt0modTop_ge175mlb_550toInfmet");

  result->GetXaxis()->SetBinLabel(18, "ge4jets_0to10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_0to10modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(20, "ge4jets_0to10modTop_lt175mlb_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(21, "ge4jets_0to10modTop_ge175mlb_250to400met");
  result->GetXaxis()->SetBinLabel(22, "ge4jets_0to10modTop_ge175mlb_400toInfmet");

  result->GetXaxis()->SetBinLabel(23, "ge4jets_ge10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge10modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge10modTop_lt175mlb_450to600met");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge10modTop_lt175mlb_600toInfmet");
  
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge10modTop_ge175mlb_250to400met");
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge10modTop_ge175mlb_400to650met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge10modTop_ge175mlb_650toInfmet");

  // Inclusive bins for bkg estimates
  result->GetXaxis()->SetBinLabel(30, "lt4jets_ge10modTop_ge175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(31, "ge4jets_lt0modTop_lt175mlb_550toInfmet");
  result->GetXaxis()->SetBinLabel(32, "ge4jets_lt0modTop_ge175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(33, "ge4jets_0to10modTop_lt175mlb_350toInfmet");
  result->GetXaxis()->SetBinLabel(34, "ge4jets_0to10modTop_ge175mlb_250toInfmet");
  result->GetXaxis()->SetBinLabel(35, "ge4jets_ge10modTop_lt175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(36, "ge4jets_ge10modTop_ge175mlb_400toInfmet");
  
  result->GetXaxis()->SetBinLabel(37, "lt4jets");
  result->GetXaxis()->SetBinLabel(38, "lt4jets_ge10modTop");
  result->GetXaxis()->SetBinLabel(39, "lt4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(40, "lt4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(41, "lt4jets_ge10modTop_450to550met");
  result->GetXaxis()->SetBinLabel(42, "lt4jets_ge10modTop_550toInfmet");

  result->GetXaxis()->SetBinLabel(43, "ge4jets");
  result->GetXaxis()->SetBinLabel(44, "ge4jets_lt0modTop");
  result->GetXaxis()->SetBinLabel(45, "ge4jets_lt0modTop_250to350met");
  result->GetXaxis()->SetBinLabel(46, "ge4jets_lt0modTop_350to450met");
  result->GetXaxis()->SetBinLabel(47, "ge4jets_lt0modTop_450to550met");
  result->GetXaxis()->SetBinLabel(48, "ge4jets_lt0modTop_550to650met");
  result->GetXaxis()->SetBinLabel(49, "ge4jets_lt0modTop_550toInfmet");
  result->GetXaxis()->SetBinLabel(50, "ge4jets_lt0modTop_650toInfmet");

  result->GetXaxis()->SetBinLabel(51, "ge4jets_0to10modTop");
  result->GetXaxis()->SetBinLabel(52, "ge4jets_0to10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(53, "ge4jets_0to10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(54, "ge4jets_0to10modTop_450toInfmet");
  result->GetXaxis()->SetBinLabel(55, "ge4jets_0to10modTop_250to400met");
  result->GetXaxis()->SetBinLabel(56, "ge4jets_0to10modTop_400toInfmet");

  result->GetXaxis()->SetBinLabel(57, "ge4jets_ge10modTop");
  result->GetXaxis()->SetBinLabel(58, "ge4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(59, "ge4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(60, "ge4jets_ge10modTop_450to600met");
  result->GetXaxis()->SetBinLabel(61, "ge4jets_ge10modTop_600toInfmet");
  
  result->GetXaxis()->SetBinLabel(62, "ge4jets_ge10modTop_250to400met");
  result->GetXaxis()->SetBinLabel(63, "ge4jets_ge10modTop_400to650met");
  result->GetXaxis()->SetBinLabel(64, "ge4jets_ge10modTop_650toInfmet");

  // 150<met<250 CR bins
  result->GetXaxis()->SetBinLabel(65, "lt4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(66, "lt4jets_ge10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(67, "lt4jets_ge10modTop_ge175mlb_150to250met");

  result->GetXaxis()->SetBinLabel(68, "ge4jets_lt0modTop_150to250met");
  result->GetXaxis()->SetBinLabel(69, "ge4jets_lt0modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(70, "ge4jets_lt0modTop_ge175mlb_150to250met");

  result->GetXaxis()->SetBinLabel(71, "ge4jets_0to10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(72, "ge4jets_0to10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(73, "ge4jets_0to10modTop_ge175mlb_150to250met");
  
  result->GetXaxis()->SetBinLabel(74, "ge4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(75, "ge4jets_ge10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(76, "ge4jets_ge10modTop_ge175mlb_150to250met");
  

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
  

  // lt4jets
  if( nGoodJets<=3 ){
    result.push_back(37); // "lt4jets"
    if(modTopness>=10.0){
      result.push_back(38); // "lt4jets_ge10modTop"
      if(met>=150.0 && met<250.0) result.push_back(65); // "lt4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(39); // "lt4jets_ge10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(40); // "lt4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<550.0) result.push_back(41); // "lt4jets_ge10modTop_450to550met"
      if(met>=550.0)              result.push_back(42); // "lt4jets_ge10modTop_550toInfmet"
    }
  }

  
  //v11 - tmod10/Mlb - 29 bins
  if( nGoodJets<=3&&modTopness>=10.0&& mlb<175) {
    if(     met>550) result.push_back(4);
    else if(met>450) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
    else if(met>150) result.push_back(66); // "lt4jets_ge10modTop_lt175mlb_150to250met"
  }
  if( nGoodJets<=3&&modTopness>=10.0&&mlb>=175) {
    if(     met>550) result.push_back(8);
    else if(met>450) result.push_back(7);
    else if(met>350) result.push_back(6);
    else if(met>250) result.push_back(5);
    else if(met>150) result.push_back(67); // "lt4jets_ge10modTop_ge175mlb_150to250met"

    if(met>450) result.push_back(30);
  }


  // ge4jet inclusive mlb bins
  if( nGoodJets>=4 ){
    result.push_back(43);  // "ge4jets"
    if(modTopness<0.0){
      result.push_back(44);  // "ge4jets_lt0modTop"
      if(met>=150.0 && met<250.0) result.push_back(68);  // "ge4jets_lt0modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(45);  // "ge4jets_lt0modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(46);  // "ge4jets_lt0modTop_350to450met"
      if(met>=450.0 && met<550.0) result.push_back(47);  // "ge4jets_lt0modTop_450to550met"
      if(met>=550.0 && met<650.0) result.push_back(48);  // "ge4jets_lt0modTop_550to650met"
      if(met>=550.0)              result.push_back(49);  // "ge4jets_lt0modTop_550toInfmet"
      if(met>=650.0)              result.push_back(50);  // "ge4jets_lt0modTop_650toInfmet"
    }
    if(modTopness>=0.0 && modTopness<10.0){
      result.push_back(51);  // "ge4jets_0to10modTop"
      if(met>=150.0 && met<250.0) result.push_back(71);  // "ge4jets_0to10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(52);  // "ge4jets_0to10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(53);  // "ge4jets_0to10modTop_350to450met"
      if(met>=450.0)              result.push_back(54);  // "ge4jets_0to10modTop_450toInfmet"
      if(met>=250.0 && met<400.0) result.push_back(55);  // "ge4jets_0to10modTop_250to400met"
      if(met>=400.0)              result.push_back(56);  // "ge4jets_0to10modTop_400toInfmet"
    }
    if(modTopness>=10.0){
      result.push_back(57);  // "ge4jets_ge10modTop"
      if(met>=150.0 && met<250.0) result.push_back(74);  // "ge4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(58);  // "ge4jets_ge10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(59);  // "ge4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<600.0) result.push_back(60);  // "ge4jets_ge10modTop_450to600met"
      if(met>=600.0)              result.push_back(61);  // "ge4jets_ge10modTop_600toInfmet"
    
      if(met>=250.0 && met<400.0) result.push_back(62);  // "ge4jets_ge10modTop_250to400met"
      if(met>=400.0 && met<650.0) result.push_back(63);  // "ge4jets_ge10modTop_400to650met"
      if(met>=650.0)              result.push_back(64);  // "ge4jets_ge10modTop_650toInfmet"
    }
  } // inclusive nJets>=4 bins
  
  
  if(nGoodJets>=4&&modTopness<0&& mlb<175) {
    if(     met>650) result.push_back(13);
    else if(met>550) result.push_back(12);
    else if(met>450) result.push_back(11);
    else if(met>350) result.push_back(10);
    else if(met>250) result.push_back(9);
    else if(met>150) result.push_back(69); // "ge4jets_lt0modTop_lt175mlb_150to250met"

    if(met>550) result.push_back(31);
  }
  if(nGoodJets>=4&&modTopness<0&&mlb>=175) {
    if(     met>550) result.push_back(17);
    else if(met>450) result.push_back(16);
    else if(met>350) result.push_back(15);
    else if(met>250) result.push_back(14);
    else if(met>150) result.push_back(70); // "ge4jets_lt0modTop_ge175mlb_150to250met"

    if(met>450) result.push_back(32);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<10.0&& mlb<175) {
    if(     met>450) result.push_back(20);
    else if(met>350) result.push_back(19);
    else if(met>250) result.push_back(18);
    else if(met>150) result.push_back(72); // "ge4jets_0to10modTop_lt175mlb_150to250met"

    if(met>350) result.push_back(33);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<10.0&&mlb>=175) {
    if(     met>400) result.push_back(22);
    else if(met>250) result.push_back(21);
    else if(met>150) result.push_back(73); // "ge4jets_0to10modTop_ge175mlb_150to250met"

    if(met>250) result.push_back(34);
  }
  if(nGoodJets>=4&&modTopness>=10.0&& mlb<175) {
    if(     met>600) result.push_back(26);
    else if(met>450) result.push_back(25);
    else if(met>350) result.push_back(24);
    else if(met>250) result.push_back(23);
    else if(met>150) result.push_back(75); // "ge4jets_ge10modTop_lt175mlb_150to250met"

    if(met>450) result.push_back(35);
  }
  if(nGoodJets>=4&&modTopness>=10.0&&mlb>=175) {
    if(     met>650) result.push_back(29);
    else if(met>400) result.push_back(28);
    else if(met>250) result.push_back(27);
    else if(met>150) result.push_back(76); // "ge4jets_ge10modTop_ge175mlb_150to250met"

    if(met>400) result.push_back(36);
  }

  
  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_bJetPt_v1(){

  int nBins_dev_ext30fb_bJetPt_v1_ = 76;
  TH1D *result = new TH1D("h_yields_SR_dev_ext30fb_bJetPt_v1", "Yields, Signal Regions, extnded to 30fb, binned with BJetPt", nBins_dev_ext30fb_bJetPt_v1_, 1.0, (double)nBins_dev_ext30fb_bJetPt_v1_+1.0);

  result->GetXaxis()->SetBinLabel(1, "lt4jets_ge10modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(2, "lt4jets_ge10modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(3, "lt4jets_ge10modTop_lt200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(4, "lt4jets_ge10modTop_lt200bJetPt_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(5, "lt4jets_ge10modTop_ge200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(6, "lt4jets_ge10modTop_ge200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(7, "lt4jets_ge10modTop_ge200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(8, "lt4jets_ge10modTop_ge200bJetPt_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt0modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt0modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt0modTop_lt200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt0modTop_lt200bJetPt_550to650met");
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt0modTop_lt200bJetPt_650toInfmet");
  
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt0modTop_ge200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt0modTop_ge200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(16, "ge4jets_lt0modTop_ge200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(17, "ge4jets_lt0modTop_ge200bJetPt_550toInfmet");

  result->GetXaxis()->SetBinLabel(18, "ge4jets_0to10modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_0to10modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(20, "ge4jets_0to10modTop_lt200bJetPt_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(21, "ge4jets_0to10modTop_ge200bJetPt_250to400met");
  result->GetXaxis()->SetBinLabel(22, "ge4jets_0to10modTop_ge200bJetPt_400toInfmet");

  result->GetXaxis()->SetBinLabel(23, "ge4jets_ge10modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge10modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge10modTop_lt200bJetPt_450to600met");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge10modTop_lt200bJetPt_600toInfmet");
  
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge10modTop_ge200bJetPt_250to400met");
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge10modTop_ge200bJetPt_400to650met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge10modTop_ge200bJetPt_650toInfmet");

  // Inclusive bins for bkg estimates
  result->GetXaxis()->SetBinLabel(30, "lt4jets_ge10modTop_ge200bJetPt_450toInfmet");
  result->GetXaxis()->SetBinLabel(31, "ge4jets_lt0modTop_lt200bJetPt_550toInfmet");
  result->GetXaxis()->SetBinLabel(32, "ge4jets_lt0modTop_ge200bJetPt_450toInfmet");
  result->GetXaxis()->SetBinLabel(33, "ge4jets_0to10modTop_lt200bJetPt_350toInfmet");
  result->GetXaxis()->SetBinLabel(34, "ge4jets_0to10modTop_ge200bJetPt_250toInfmet");
  result->GetXaxis()->SetBinLabel(35, "ge4jets_ge10modTop_lt200bJetPt_450toInfmet");
  result->GetXaxis()->SetBinLabel(36, "ge4jets_ge10modTop_ge200bJetPt_400toInfmet");

  result->GetXaxis()->SetBinLabel(37, "lt4jets");
  result->GetXaxis()->SetBinLabel(38, "lt4jets_ge10modTop");
  result->GetXaxis()->SetBinLabel(39, "lt4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(40, "lt4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(41, "lt4jets_ge10modTop_450to550met");
  result->GetXaxis()->SetBinLabel(42, "lt4jets_ge10modTop_550toInfmet");

  result->GetXaxis()->SetBinLabel(43, "ge4jets");
  result->GetXaxis()->SetBinLabel(44, "ge4jets_lt0modTop");
  result->GetXaxis()->SetBinLabel(45, "ge4jets_lt0modTop_250to350met");
  result->GetXaxis()->SetBinLabel(46, "ge4jets_lt0modTop_350to450met");
  result->GetXaxis()->SetBinLabel(47, "ge4jets_lt0modTop_450to550met");
  result->GetXaxis()->SetBinLabel(48, "ge4jets_lt0modTop_550to650met");
  result->GetXaxis()->SetBinLabel(49, "ge4jets_lt0modTop_550toInfmet");
  result->GetXaxis()->SetBinLabel(50, "ge4jets_lt0modTop_650toInfmet");

  result->GetXaxis()->SetBinLabel(51, "ge4jets_0to10modTop");
  result->GetXaxis()->SetBinLabel(52, "ge4jets_0to10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(53, "ge4jets_0to10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(54, "ge4jets_0to10modTop_450toInfmet");
  result->GetXaxis()->SetBinLabel(55, "ge4jets_0to10modTop_250to400met");
  result->GetXaxis()->SetBinLabel(56, "ge4jets_0to10modTop_400toInfmet");

  result->GetXaxis()->SetBinLabel(57, "ge4jets_ge10modTop");
  result->GetXaxis()->SetBinLabel(58, "ge4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(59, "ge4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(60, "ge4jets_ge10modTop_450to600met");
  result->GetXaxis()->SetBinLabel(61, "ge4jets_ge10modTop_600toInfmet");
  
  result->GetXaxis()->SetBinLabel(62, "ge4jets_ge10modTop_250to400met");
  result->GetXaxis()->SetBinLabel(63, "ge4jets_ge10modTop_400to650met");
  result->GetXaxis()->SetBinLabel(64, "ge4jets_ge10modTop_650toInfmet");

  // 150<met<250 CR bins
  result->GetXaxis()->SetBinLabel(65, "lt4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(66, "lt4jets_ge10modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(67, "lt4jets_ge10modTop_ge200bJetPt_150to250met");

  result->GetXaxis()->SetBinLabel(68, "ge4jets_lt0modTop_150to250met");
  result->GetXaxis()->SetBinLabel(69, "ge4jets_lt0modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(70, "ge4jets_lt0modTop_ge200bJetPt_150to250met");

  result->GetXaxis()->SetBinLabel(71, "ge4jets_0to10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(72, "ge4jets_0to10modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(73, "ge4jets_0to10modTop_ge200bJetPt_150to250met");
  
  result->GetXaxis()->SetBinLabel(74, "ge4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(75, "ge4jets_ge10modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(76, "ge4jets_ge10modTop_ge200bJetPt_150to250met");
  

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


  // lt4jets
  if( nGoodJets<=3 ){
    result.push_back(37); // "lt4jets"
    if(modTopness>=10.0){
      result.push_back(38); // "lt4jets_ge10modTop"
      if(met>=150.0 && met<250.0) result.push_back(65); // "lt4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(39); // "lt4jets_ge10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(40); // "lt4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<550.0) result.push_back(41); // "lt4jets_ge10modTop_450to550met"
      if(met>=550.0)              result.push_back(42); // "lt4jets_ge10modTop_550toInfmet"
    }
  }

  
  //v12 - tmod10/bpt - 29 bins
  if( nGoodJets<=3&&modTopness>=10.0&& leadBJetPt<200) {
    if(     met>550) result.push_back(4);
    else if(met>450) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
    else if(met>150) result.push_back(66); // "lt4jets_ge10modTop_lt200bJetPt_150to250met"
  }
  if( nGoodJets<=3&&modTopness>=10.0&&leadBJetPt>=200) {
    if(met>550)      result.push_back(8);
    else if(met>450) result.push_back(7);
    else if(met>350) result.push_back(6);
    else if(met>250) result.push_back(5);
    else if(met>150) result.push_back(67); // "lt4jets_ge10modTop_ge200bJetPt_150to250met"

    if(met>450) result.push_back(30);
  }

  
  // ge4jet inclusive mlb bins
  if( nGoodJets>=4 ){
    result.push_back(43);  // "ge4jets"
    if(modTopness<0.0){
      result.push_back(44);  // "ge4jets_lt0modTop"
      if(met>-150.0 && met<250.0) result.push_back(68);  // "ge4jets_lt0modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(45);  // "ge4jets_lt0modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(46);  // "ge4jets_lt0modTop_350to450met"
      if(met>=450.0 && met<550.0) result.push_back(47);  // "ge4jets_lt0modTop_450to550met"
      if(met>=550.0 && met<650.0) result.push_back(48);  // "ge4jets_lt0modTop_550to650met"
      if(met>=550.0)              result.push_back(49);  // "ge4jets_lt0modTop_550toInfmet"
      if(met>=650.0)              result.push_back(50);  // "ge4jets_lt0modTop_650toInfmet"
    }
    if(modTopness>=0.0 && modTopness<10.0){
      result.push_back(51);  // "ge4jets_0to10modTop"
      if(met>=150.0 && met<250.0) result.push_back(71);  // "ge4jets_0to10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(52);  // "ge4jets_0to10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(53);  // "ge4jets_0to10modTop_350to450met"
      if(met>=450.0)              result.push_back(54);  // "ge4jets_0to10modTop_450toInfmet"
      if(met>=250.0 && met<400.0) result.push_back(55);  // "ge4jets_0to10modTop_250to400met"
      if(met>=400.0)              result.push_back(56);  // "ge4jets_0to10modTop_400toInfmet"
    }
    if(modTopness>=10.0){
      result.push_back(57);  // "ge4jets_ge10modTop"
      if(met>=150.0 && met<250.0) result.push_back(74);  // "ge4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(58);  // "ge4jets_ge10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(59);  // "ge4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<600.0) result.push_back(60);  // "ge4jets_ge10modTop_450to600met"
      if(met>=600.0)              result.push_back(61);  // "ge4jets_ge10modTop_600toInfmet"
    
      if(met>=250.0 && met<400.0) result.push_back(62);  // "ge4jets_ge10modTop_250to400met"
      if(met>=400.0 && met<650.0) result.push_back(63);  // "ge4jets_ge10modTop_400to650met"
      if(met>=650.0)              result.push_back(64);  // "ge4jets_ge10modTop_650toInfmet"
    }
  } // inclusive nJets>=4 bins
  

  if(nGoodJets>=4&&modTopness<0&& leadBJetPt<200) {
    if(     met>650) result.push_back(13);
    else if(met>550) result.push_back(12);
    else if(met>450) result.push_back(11);
    else if(met>350) result.push_back(10);
    else if(met>250) result.push_back(9);
    else if(met>150) result.push_back(69);  // "ge4jets_lt0modTop_lt200bJetPt_150to250met"

    if(met>550) result.push_back(31);
  }
  if(nGoodJets>=4&&modTopness<0&&leadBJetPt>=200) {
    if(     met>550) result.push_back(17);
    else if(met>450) result.push_back(16);
    else if(met>350) result.push_back(15);
    else if(met>250) result.push_back(14);
    else if(met>150) result.push_back(70);  // "ge4jets_lt0modTop_ge200bJetPt_150to250met"

    if(met>450) result.push_back(32);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<10.0&& leadBJetPt<200) {
    if(     met>450) result.push_back(20);
    else if(met>350) result.push_back(19);
    else if(met>250) result.push_back(18);
    else if(met>150) result.push_back(72);  // "ge4jets_0to10modTop_lt200bJetPt_150to250met"
    if(met>350) result.push_back(33);
  }
  if(nGoodJets>=4&&modTopness>=0&&modTopness<10.0&&leadBJetPt>=200) {
    if(     met>350) result.push_back(22);
    else if(met>250) result.push_back(21);
    else if(met>150) result.push_back(73);  // "ge4jets_0to10modTop_ge200bJetPt_150to250met"

    if(met>250) result.push_back(34);
  }
  if(nGoodJets>=4&&modTopness>=10.0&& leadBJetPt<200) {
    if(     met>600) result.push_back(26);
    else if(met>450) result.push_back(25);
    else if(met>350) result.push_back(24);
    else if(met>250) result.push_back(23);
    else if(met>150) result.push_back(75);  // "ge4jets_ge10modTop_lt200bJetPt_150to250met"

    if(met>450) result.push_back(35);
  }
  if(nGoodJets>=4&&modTopness>=10.0&&leadBJetPt>=200) {
    if(     met>650) result.push_back(29);
    else if(met>400) result.push_back(28);
    else if(met>250) result.push_back(27);
    else if(met>150) result.push_back(76);  // "ge4jets_ge10modTop_ge200bJetPt_150to250met"

    if(met>400) result.push_back(36);
  }

  
  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_corridor(){
  
  int nBins_SR_corridor_ = 7;
  TH1D *result = new TH1D("h_yields_SR_corridor", "Yields, SR Top Corridor", nBins_SR_corridor_, 1.0, (double)nBins_SR_corridor_+1.0);
  
  result->GetXaxis()->SetBinLabel(1, "top_corridor_250to350met");
  result->GetXaxis()->SetBinLabel(2, "top_corridor_350to450met");
  result->GetXaxis()->SetBinLabel(3, "top_corridor_450toInfmet");
  result->GetXaxis()->SetBinLabel(4, "top_corridor_450to550met");
  result->GetXaxis()->SetBinLabel(5, "top_corridor_550toInfmet");

  // Inclusive
  result->GetXaxis()->SetBinLabel(6, "top_corridor");
  result->GetXaxis()->SetBinLabel(7, "top_corridor_150to250met");

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_SR_corridor( int jesType, bool add2ndLepToMet ){

  vector<int> result;
  result.clear();

  int nGoodJets = babyAnalyzer.ngoodjets();
  if( jesType==1 )  nGoodJets = babyAnalyzer.jup_ngoodjets();
  if( jesType==-1 ) nGoodJets = babyAnalyzer.jdown_ngoodjets();
  
  // Require at least 5 jets
  if( nGoodJets < 5 ) return result;


  double leadJetPt = babyAnalyzer.ak4pfjets_p4().at(0).Pt();
  if( jesType==1 )  leadJetPt = babyAnalyzer.jup_ak4pfjets_p4().at(0).Pt();
  if( jesType==-1 ) leadJetPt = babyAnalyzer.jdown_ak4pfjets_p4().at(0).Pt();
  
  // Require leading jet to have pT > 200
  if( leadJetPt <= 200.0 ) return result;  

  
  bool leadJet_isBTag = babyAnalyzer.ak4pfjets_passMEDbtag().at(0);
  if( jesType==1 )  leadJet_isBTag = babyAnalyzer.jup_ak4pfjets_passMEDbtag().at(0);
  if( jesType==-1 ) leadJet_isBTag = babyAnalyzer.jdown_ak4pfjets_passMEDbtag().at(0);

  // Require leading jet to NOT be b-tagged
  if( leadJet_isBTag ) return result;      


  // Met Bins
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
  
   

  //  Inclusive Bin
  result.push_back(6);

  if( met>=150.0 && met<250.0 ) result.push_back(7); // CR bin
  
  if( met>=250.0 && met<350.0 ) result.push_back(1); // SR bin 1
  if( met>=350.0 && met<450.0 ) result.push_back(2); // SR bin 2
  if( met>=450.0 )              result.push_back(3); // SR bin 3
  if( met>=450.0 && met<550.0 ) result.push_back(4); // SR bin 4
  if( met>=550.0 )              result.push_back(5); // SR bin 5


  return result;

}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_CR2l_bulkTTbar(){
  
  int nBins_CR2l_bulkTTbar_ = 15;
  TH1D *result = new TH1D("h_yields_CR2l_bulkTTbar", "Yields, CR2l bulk TTbar", nBins_CR2l_bulkTTbar_, 1.0, (double)nBins_CR2l_bulkTTbar_+1.0);
  
  result->GetXaxis()->SetBinLabel(1, "ge0tags_ge50met");
  result->GetXaxis()->SetBinLabel(2, "ge0tags_ge100met");
  result->GetXaxis()->SetBinLabel(3, "ge0tags_ge150met");
  result->GetXaxis()->SetBinLabel(4, "ge0tags_ge200met");
  result->GetXaxis()->SetBinLabel(5, "ge0tags_ge250met");
 
  result->GetXaxis()->SetBinLabel(6, "ge1tags_ge50met");
  result->GetXaxis()->SetBinLabel(7, "ge1tags_ge100met");
  result->GetXaxis()->SetBinLabel(8, "ge1tags_ge150met");
  result->GetXaxis()->SetBinLabel(9, "ge1tags_ge200met");
  result->GetXaxis()->SetBinLabel(10, "ge1tags_ge250met");
 
  result->GetXaxis()->SetBinLabel(11, "ge2tags_ge50met");
  result->GetXaxis()->SetBinLabel(12, "ge2tags_ge100met");
  result->GetXaxis()->SetBinLabel(13, "ge2tags_ge150met");
  result->GetXaxis()->SetBinLabel(14, "ge2tags_ge200met");
  result->GetXaxis()->SetBinLabel(15, "ge2tags_ge250met");
 
    
  return result;
}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_CR2l_bulkTTbar( int jesType, bool add2ndLepToMet ){

  vector<int> result;

  int nGoodBTags = babyAnalyzer.ngoodbtags(); 
  if( jesType==1)  nGoodBTags = babyAnalyzer.jup_ngoodbtags();
  if( jesType==-1) nGoodBTags = babyAnalyzer.jdown_ngoodbtags();

  
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
  

  if( nGoodBTags>=0 ){
    
    // >=0 bTags
    if( met>50  ) result.push_back(1);
    if( met>100 ) result.push_back(2);
    if( met>150 ) result.push_back(3);
    if( met>200 ) result.push_back(4);
    if( met>250 ) result.push_back(5);

  } // >=0 nGoodBTags


  if( nGoodBTags>=1 ){
    
    // >=1 bTags
    if( met>50  ) result.push_back(6);
    if( met>100 ) result.push_back(7);
    if( met>150 ) result.push_back(8);
    if( met>200 ) result.push_back(9);
    if( met>250 ) result.push_back(10);
  
  } // >=1 nGoodBTags

  if( nGoodBTags>=2 ){
    
    // >=2 bTags
    if( met>50  ) result.push_back(11);
    if( met>100 ) result.push_back(12);
    if( met>150 ) result.push_back(13);
    if( met>200 ) result.push_back(14);
    if( met>250 ) result.push_back(15);

  } // >=0 nGoodBTags


  return result;

}

//////////////////////////////////////////////////////////////////////
