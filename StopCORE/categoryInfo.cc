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
  
  // Require dPhi(met,j1,2)>=0.8
  double dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2();
  if( add2ndLepToMet ){
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jdown();
    else dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl();
  }
  else{
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jdown();
  }
  
  if( dPhiMetJet<0.8 ) return result;



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
  

  // Require dPhi(met,j1,2)>=0.8
  double dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2();
  if( add2ndLepToMet ){
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jdown();
    else dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl();
  }
  else{
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jdown();
  }
  
  if( dPhiMetJet<0.8 ) return result;


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

  int nBins_dev_ext30fb_mlb_v1_ = 77;
  TH1D *result = new TH1D("h_yields_SR_dev_ext30fb_mlb_v1", "Yields, Signal Regions, extnded to 30fb, binned with Mlb", nBins_dev_ext30fb_mlb_v1_, 1.0, (double)nBins_dev_ext30fb_mlb_v1_+1.0);

  // Region A, nJets<4, modTop>=10, mlb<175
  result->GetXaxis()->SetBinLabel(1, "lt4jets_ge10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(2, "lt4jets_ge10modTop_lt175mlb_350to500met");
  result->GetXaxis()->SetBinLabel(3, "lt4jets_ge10modTop_lt175mlb_500toInfmet");

  // Region B, nJets<4, modTop>=10, mlb>=175
  result->GetXaxis()->SetBinLabel(4, "lt4jets_ge10modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(5, "lt4jets_ge10modTop_ge175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(6, "lt4jets_ge10modTop_ge175mlb_450to650met");
  result->GetXaxis()->SetBinLabel(7, "lt4jets_ge10modTop_ge175mlb_650toInfmet");

  // Region C, nJets>=4, modTop<0, mlb<175
  result->GetXaxis()->SetBinLabel(8, "ge4jets_lt0modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt0modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt0modTop_lt175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt0modTop_lt175mlb_550to650met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt0modTop_lt175mlb_650toInfmet");

  // Region D, nJets>=4, modTop<0, mlb>=175 
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt0modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt0modTop_ge175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt0modTop_ge175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(16, "ge4jets_lt0modTop_ge175mlb_550toInfmet");

  // Region E, nJets>=4, 0<=modTop<10, mlb<175
  result->GetXaxis()->SetBinLabel(17, "ge4jets_0to10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(18, "ge4jets_0to10modTop_lt175mlb_350to550met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_0to10modTop_lt175mlb_550toInfmet");

  // Region F, nJets>=4, 0<=modTop<10, mlb>=175
  result->GetXaxis()->SetBinLabel(20, "ge4jets_0to10modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(21, "ge4jets_0to10modTop_ge175mlb_350to500met");
  result->GetXaxis()->SetBinLabel(22, "ge4jets_0to10modTop_ge175mlb_500toInfmet");

  // Region G, nJets>=4, modTop>=10, mlb<175
  result->GetXaxis()->SetBinLabel(23, "ge4jets_ge10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge10modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge10modTop_lt175mlb_450to600met");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge10modTop_lt175mlb_600toInfmet");

  // Region H, nJets>=4, modTop>=10, mlb>=175
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge10modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge10modTop_ge175mlb_350to650met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge10modTop_ge175mlb_650toInfmet");


  // Coarser MET bins for bkg estimates
  result->GetXaxis()->SetBinLabel(30, "lt4jets_ge10modTop_ge175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(31, "ge4jets_lt0modTop_lt175mlb_550toInfmet");
  result->GetXaxis()->SetBinLabel(32, "ge4jets_lt0modTop_ge175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(33, "ge4jets_0to10modTop_lt175mlb_350toInfmet");
  result->GetXaxis()->SetBinLabel(34, "ge4jets_0to10modTop_ge175mlb_350toInfmet");
  result->GetXaxis()->SetBinLabel(35, "ge4jets_ge10modTop_lt175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(36, "ge4jets_ge10modTop_ge175mlb_350toInfmet");
  
  // nJet Bins 
  result->GetXaxis()->SetBinLabel(37, "lt4jets");
  result->GetXaxis()->SetBinLabel(38, "ge4jets");
  
  // nJet, modTopness Bins
  result->GetXaxis()->SetBinLabel(39, "lt4jets_ge10modTop");
  result->GetXaxis()->SetBinLabel(40, "ge4jets_lt0modTop");
  result->GetXaxis()->SetBinLabel(41, "ge4jets_0to10modTop");
  result->GetXaxis()->SetBinLabel(42, "ge4jets_ge10modTop");
  
  // nJet, modTopness, met Bins, Inclusive in Mlb
  result->GetXaxis()->SetBinLabel(43, "lt4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(44, "lt4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(45, "lt4jets_ge10modTop_350to500met");
  result->GetXaxis()->SetBinLabel(46, "lt4jets_ge10modTop_500toInfmet");
  result->GetXaxis()->SetBinLabel(47, "lt4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(48, "lt4jets_ge10modTop_450to650met");
  result->GetXaxis()->SetBinLabel(49, "lt4jets_ge10modTop_650toInfmet");

  result->GetXaxis()->SetBinLabel(50, "ge4jets_lt0modTop_150to250met");
  result->GetXaxis()->SetBinLabel(51, "ge4jets_lt0modTop_250to350met");
  result->GetXaxis()->SetBinLabel(52, "ge4jets_lt0modTop_350to450met");
  result->GetXaxis()->SetBinLabel(53, "ge4jets_lt0modTop_450to550met");
  result->GetXaxis()->SetBinLabel(54, "ge4jets_lt0modTop_550to650met");
  result->GetXaxis()->SetBinLabel(55, "ge4jets_lt0modTop_650toInfmet");
  result->GetXaxis()->SetBinLabel(56, "ge4jets_lt0modTop_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(57, "ge4jets_0to10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(58, "ge4jets_0to10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(59, "ge4jets_0to10modTop_350to550met");
  result->GetXaxis()->SetBinLabel(60, "ge4jets_0to10modTop_550toInfmet");
  result->GetXaxis()->SetBinLabel(61, "ge4jets_0to10modTop_350to500met");
  result->GetXaxis()->SetBinLabel(62, "ge4jets_0to10modTop_500toInfmet");
  
  result->GetXaxis()->SetBinLabel(63, "ge4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(64, "ge4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(65, "ge4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(66, "ge4jets_ge10modTop_450to600met");
  result->GetXaxis()->SetBinLabel(67, "ge4jets_ge10modTop_600toInfmet");
  result->GetXaxis()->SetBinLabel(68, "ge4jets_ge10modTop_350to650met");
  result->GetXaxis()->SetBinLabel(69, "ge4jets_ge10modTop_650toInfmet");
  
  // 150<met<250 CR bins
  result->GetXaxis()->SetBinLabel(70, "lt4jets_ge10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(71, "lt4jets_ge10modTop_ge175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(72, "ge4jets_lt0modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(73, "ge4jets_lt0modTop_ge175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(74, "ge4jets_0to10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(75, "ge4jets_0to10modTop_ge175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(76, "ge4jets_ge10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(77, "ge4jets_ge10modTop_ge175mlb_150to250met");
  

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

  int nMedBTags = babyAnalyzer.ngoodbtags(); 
  if( jesType==1)  nMedBTags = babyAnalyzer.jup_ngoodbtags();
  if( jesType==-1) nMedBTags = babyAnalyzer.jdown_ngoodbtags();

  if(nMedBTags==0){
    if( jesType==1  ) mlb = ( babyAnalyzer.lep1_p4() + babyAnalyzer.jup_ak4pfjets_leadbtag_p4() ).M();
    if( jesType==-1 ) mlb = ( babyAnalyzer.lep1_p4() + babyAnalyzer.jdown_ak4pfjets_leadbtag_p4() ).M();
    else              mlb = ( babyAnalyzer.lep1_p4() + babyAnalyzer.ak4pfjets_leadbtag_p4() ).M();
  } // end if 0 bTags


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


  // Require dPhi(met,j1,2)>=0.8
  double dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2();
  if( add2ndLepToMet ){
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jdown();
    else dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl();
  }
  else{
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jdown();
  }
  
  if( dPhiMetJet<0.8 ) return result;


  //
  // 29 Signal Region Bins
  //

  // Region A
  if( nGoodJets<4 && modTopness>=10.0 && mlb<175 ){
    if(     met>500) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
  }

  // Region B
  if( nGoodJets<4 && modTopness>=10.0 && mlb>=175 ){
    if(     met>650) result.push_back(7);
    else if(met>450) result.push_back(6);
    else if(met>350) result.push_back(5);
    else if(met>250) result.push_back(4);
  }

  // Region C
  if( nGoodJets>=4 && modTopness<0 && mlb<175 ){
    if(     met>650) result.push_back(12);
    else if(met>550) result.push_back(11);
    else if(met>450) result.push_back(10);
    else if(met>350) result.push_back(9);
    else if(met>250) result.push_back(8);
  }

  // Region D
  if( nGoodJets>=4 && modTopness<0 && mlb>=175 ){
    if(     met>550) result.push_back(16);
    else if(met>450) result.push_back(15);
    else if(met>350) result.push_back(14);
    else if(met>250) result.push_back(13);
  }

  // Region E
  if( nGoodJets>=4 && modTopness>=0 && modTopness<10.0 && mlb<175 ){
    if(     met>550) result.push_back(19);
    else if(met>350) result.push_back(18);
    else if(met>250) result.push_back(17);
  }
  
  // Region F
  if( nGoodJets>=4 && modTopness>=0 && modTopness<10.0 && mlb>=175 ){
    if(     met>500) result.push_back(22);
    else if(met>350) result.push_back(21);
    else if(met>250) result.push_back(20);
  }

  // Region G
  if( nGoodJets>=4 && modTopness>=10.0 && mlb<175 ){
    if(     met>600) result.push_back(26);
    else if(met>450) result.push_back(25);
    else if(met>350) result.push_back(24);
    else if(met>250) result.push_back(23);
  }

  // Region H
  if( nGoodJets>=4 && modTopness>=10.0 && mlb>=175 ){
    if(     met>650) result.push_back(29);
    else if(met>350) result.push_back(28);
    else if(met>250) result.push_back(27);
  }



  // Coarser MET bins for bkg estimates
  if( nGoodJets<4 ){
    if(modTopness>=10.0){
      if(mlb>=175 && met>450) result.push_back(30); // "lt4jets_ge10modTop_ge175mlb_450toInfmet" 
    }
  }
  if( nGoodJets>=4 ){
    if( modTopness<0.0 ){
      if( mlb<175  && met>550 ) result.push_back(31); // "ge4jets_lt0modTop_lt175mlb_550toInfmet"
      if( mlb>=175 && met>450 ) result.push_back(32); // "ge4jets_lt0modTop_ge175mlb_450toInfmet"
    }
    if( modTopness>=0.0 && modTopness<10.0 ){
      if( mlb<175  && met>350 ) result.push_back(33); // "ge4jets_0to10modTop_lt175mlb_350toInfmet"
      if( mlb>=175 && met>350 ) result.push_back(34); // "ge4jets_0to10modTop_ge175mlb_350toInfmet"
    }
    if( modTopness>=10.0 ){
      if( mlb<175  && met>450 ) result.push_back(35); // "ge4jets_ge10modTop_lt175mlb_450toInfmet"
      if( mlb>=175 && met>350 ) result.push_back(36); // "ge4jets_ge10modTop_ge175mlb_350toInfmet"
    }
  }
      
  
  // nJets Bins
  if( nGoodJets<4  ) result.push_back(37);  // "lt4jets"
  if( nGoodJets>=4 ) result.push_back(38);  // "ge4jets"
  

  // nJets and modTopness Bins
  if( nGoodJets<4  && modTopness>=10.0 ) result.push_back(39); // "lt4jets_ge10modTop"
  if( nGoodJets>=4 ){
    if(      modTopness>=10.0 ) result.push_back(42);  // "ge4jets_ge10modTop"
    else if( modTopness<10.0  ) result.push_back(41);  // "ge4jets_0to10modTop"
    else if( modTopness<0.0   ) result.push_back(40);  // "ge4jets_lt0modTop"
  }
    
  
  // nJet, modTopness, met bins, inclusive in Mlb
  if( nGoodJets<4 ){
    if(modTopness>=10.0){
      if(met>=150.0 && met<250.0) result.push_back(43); // "lt4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(44); // "lt4jets_ge10modTop_250to350met"

      if(met>=350.0 && met<500.0) result.push_back(45); // "lt4jets_ge10modTop_350to450met"
      if(met>=500.0)              result.push_back(46); // "lt4jets_ge10modTop_550toInfmet"

      if(met>=350.0 && met<450.0) result.push_back(47); // "lt4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<650.0) result.push_back(48); // "lt4jets_ge10modTop_450to650met"
      if(met>=650.0)              result.push_back(49); // "lt4jets_ge10modTop_650toInfmet"
    }
  }
 
  if( nGoodJets>=4 ){
    if(modTopness<0.0){
      if(met>=150.0 && met<250.0) result.push_back(50);  // "ge4jets_lt0modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(51);  // "ge4jets_lt0modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(52);  // "ge4jets_lt0modTop_350to450met"
      if(met>=450.0 && met<550.0) result.push_back(53);  // "ge4jets_lt0modTop_450to550met"
      if(met>=550.0 && met<650.0) result.push_back(54);  // "ge4jets_lt0modTop_550to650met"

      if(met>=650.0)              result.push_back(55);  // "ge4jets_lt0modTop_650toInfmet"
      
      if(met>=550.0)              result.push_back(56);  // "ge4jets_lt0modTop_550toInfmet"
    }
    if(modTopness>=0.0 && modTopness<10.0){
      if(met>=150.0 && met<250.0) result.push_back(57);  // "ge4jets_0to10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(58);  // "ge4jets_0to10modTop_250to350met"

      if(met>=350.0 && met<550.0) result.push_back(59);  // "ge4jets_0to10modTop_350to550met"
      if(met>=550.0)              result.push_back(60);  // "ge4jets_0to10modTop_550toInfmet"
      
      if(met>=350.0 && met<500.0) result.push_back(61);  // "ge4jets_0to10modTop_350to500met"
      if(met>=500.0)              result.push_back(62);  // "ge4jets_0to10modTop_500toInfmet"
    }
    if(modTopness>=10.0){
      if(met>=150.0 && met<250.0) result.push_back(63);  // "ge4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(64);  // "ge4jets_ge10modTop_250to350met"

      if(met>=350.0 && met<450.0) result.push_back(65);  // "ge4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<600.0) result.push_back(66);  // "ge4jets_ge10modTop_450to600met"
      if(met>=600.0)              result.push_back(67);  // "ge4jets_ge10modTop_600toInfmet"
    
      if(met>=350.0 && met<650.0) result.push_back(68);  // "ge4jets_ge10modTop_400to650met"
      if(met>=650.0)              result.push_back(69);  // "ge4jets_ge10modTop_650toInfmet"
    }
  } // inclusive nJets>=4 bins
  

  // 150<met<250 CR bins
  if( nGoodJets<4 && modTopness>=10.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(70); // "lt4jets_ge10modTop_lt175mlb_150to250met"
    if(mlb>=175 && met>150 && met<=250) result.push_back(71); // "lt4jets_ge10modTop_ge175mlb_150to250met"
  }
  if( nGoodJets>=4 && modTopness<0.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(72); // "ge4jets_lt0modTop_lt175mlb_150to250met"
    if(mlb>=175 && met>150 && met<=250) result.push_back(73); // "ge4jets_lt0modTop_ge175mlb_150to250met"
  }
  if( nGoodJets>=4 && modTopness>=0.0 && modTopness<10.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(74); // "ge4jets_0to10modTop_lt175mlb_150to250met"
    if(mlb>=175 && met>150 && met<=250) result.push_back(75); // "ge4jets_0to10modTop_ge175mlb_150to250met"
  }
  if( nGoodJets>=4 && modTopness>=10.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(76); // "ge4jets_ge10modTop_lt175mlb_150to250met"
    if(mlb>=175 && met>150 && met<=250) result.push_back(77); // "ge4jets_ge10modTop_ge175mlb_150to250met"
  }
  
     
  return result;
}


//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_mlb_v2(){

  int nBins_dev_ext30fb_mlb_v2_ = 77;
  TH1D *result = new TH1D("h_yields_SR_dev_ext30fb_mlb_v2", "Yields, Signal Regions, extnded to 30fb, binned with Mlb, and using tight bTagging", nBins_dev_ext30fb_mlb_v2_, 1.0, (double)nBins_dev_ext30fb_mlb_v2_+1.0);

  // Region A, nJets<4, modTop>=10, mlb<175
  result->GetXaxis()->SetBinLabel(1, "lt4jets_ge10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(2, "lt4jets_ge10modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(3, "lt4jets_ge10modTop_lt175mlb_450to600met");
  result->GetXaxis()->SetBinLabel(4, "lt4jets_ge10modTop_lt175mlb_600toInfmet");

  // Region B, nJets<4, modTop>=10, mlb>=175, nTightTags>=1
  result->GetXaxis()->SetBinLabel(5, "lt4jets_ge10modTop_ge175mlb_250to450met");
  result->GetXaxis()->SetBinLabel(6, "lt4jets_ge10modTop_ge175mlb_450to600met");
  result->GetXaxis()->SetBinLabel(7, "lt4jets_ge10modTop_ge175mlb_600toInfmet");

  // Region C, nJets>=4, modTop<0, mlb<175
  result->GetXaxis()->SetBinLabel(8, "ge4jets_lt0modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt0modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt0modTop_lt175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt0modTop_lt175mlb_550to650met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt0modTop_lt175mlb_650toInfmet");

  // Region D, nJets>=4, modTop<0, mlb>=175, nTightTags>=1 
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt0modTop_ge175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt0modTop_ge175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt0modTop_ge175mlb_450to550met");
  result->GetXaxis()->SetBinLabel(16, "ge4jets_lt0modTop_ge175mlb_550toInfmet");

  // Region E, nJets>=4, 0<=modTop<10, mlb<175
  result->GetXaxis()->SetBinLabel(17, "ge4jets_0to10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(18, "ge4jets_0to10modTop_lt175mlb_350to550met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_0to10modTop_lt175mlb_550toInfmet");

  // Region F, nJets>=4, 0<=modTop<10, mlb>=175, nTightTags>=1
  result->GetXaxis()->SetBinLabel(20, "ge4jets_0to10modTop_ge175mlb_250to450met");
  result->GetXaxis()->SetBinLabel(21, "ge4jets_0to10modTop_ge175mlb_450toInfmet");

  // Region G, nJets>=4, modTop>=10, mlb<175
  result->GetXaxis()->SetBinLabel(22, "ge4jets_ge10modTop_lt175mlb_250to350met");
  result->GetXaxis()->SetBinLabel(23, "ge4jets_ge10modTop_lt175mlb_350to450met");
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge10modTop_lt175mlb_450to600met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge10modTop_lt175mlb_600toInfmet");

  // Region H, nJets>=4, modTop>=10, mlb>=175, nTightTags>=1
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge10modTop_ge175mlb_250to450met");
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge10modTop_ge175mlb_450toInfmet");


  // Coarser MET bins for bkg estimates
  result->GetXaxis()->SetBinLabel(28, "lt4jets_ge10modTop_lt175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(29, "lt4jets_ge10modTop_ge175mlb_250toInfmet");
  result->GetXaxis()->SetBinLabel(30, "ge4jets_lt0modTop_lt175mlb_550toInfmet");
  result->GetXaxis()->SetBinLabel(31, "ge4jets_lt0modTop_ge175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(32, "ge4jets_0to10modTop_lt175mlb_350toInfmet");
  result->GetXaxis()->SetBinLabel(33, "ge4jets_0to10modTop_ge175mlb_250toInfmet");
  result->GetXaxis()->SetBinLabel(34, "ge4jets_ge10modTop_lt175mlb_450toInfmet");
  result->GetXaxis()->SetBinLabel(35, "ge4jets_ge10modTop_ge175mlb_250toInfmet");
  
  // nJet Bins 
  result->GetXaxis()->SetBinLabel(36, "lt4jets");
  result->GetXaxis()->SetBinLabel(37, "ge4jets");
  
  // nJet, modTopness Bins
  result->GetXaxis()->SetBinLabel(38, "lt4jets_ge10modTop");
  result->GetXaxis()->SetBinLabel(39, "ge4jets_lt0modTop");
  result->GetXaxis()->SetBinLabel(40, "ge4jets_0to10modTop");
  result->GetXaxis()->SetBinLabel(41, "ge4jets_ge10modTop");
  
  // nJet, modTopness, met Bins, Inclusive in Mlb
  result->GetXaxis()->SetBinLabel(42, "lt4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(43, "lt4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(44, "lt4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(45, "lt4jets_ge10modTop_450to600met");
  result->GetXaxis()->SetBinLabel(46, "lt4jets_ge10modTop_600toInfmet");
  result->GetXaxis()->SetBinLabel(47, "lt4jets_ge10modTop_250to450met");
  result->GetXaxis()->SetBinLabel(48, "lt4jets_ge10modTop_450to600met_");
  result->GetXaxis()->SetBinLabel(49, "lt4jets_ge10modTop_600toInfmet_");

  result->GetXaxis()->SetBinLabel(50, "ge4jets_lt0modTop_150to250met");
  result->GetXaxis()->SetBinLabel(51, "ge4jets_lt0modTop_250to350met");
  result->GetXaxis()->SetBinLabel(52, "ge4jets_lt0modTop_350to450met");
  result->GetXaxis()->SetBinLabel(53, "ge4jets_lt0modTop_450to550met");
  result->GetXaxis()->SetBinLabel(54, "ge4jets_lt0modTop_550to650met");
  result->GetXaxis()->SetBinLabel(55, "ge4jets_lt0modTop_650toInfmet");
  result->GetXaxis()->SetBinLabel(56, "ge4jets_lt0modTop_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(57, "ge4jets_0to10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(58, "ge4jets_0to10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(59, "ge4jets_0to10modTop_350to550met");
  result->GetXaxis()->SetBinLabel(60, "ge4jets_0to10modTop_550toInfmet");
  result->GetXaxis()->SetBinLabel(61, "ge4jets_0to10modTop_250to450met");
  result->GetXaxis()->SetBinLabel(62, "ge4jets_0to10modTop_450toInfmet");
  
  result->GetXaxis()->SetBinLabel(63, "ge4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(64, "ge4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(65, "ge4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(66, "ge4jets_ge10modTop_450to600met");
  result->GetXaxis()->SetBinLabel(67, "ge4jets_ge10modTop_600toInfmet");
  result->GetXaxis()->SetBinLabel(68, "ge4jets_ge10modTop_250to450met");
  result->GetXaxis()->SetBinLabel(69, "ge4jets_ge10modTop_450toInfmet");
  
  // 150<met<250 CR bins
  result->GetXaxis()->SetBinLabel(70, "lt4jets_ge10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(71, "lt4jets_ge10modTop_ge175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(72, "ge4jets_lt0modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(73, "ge4jets_lt0modTop_ge175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(74, "ge4jets_0to10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(75, "ge4jets_0to10modTop_ge175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(76, "ge4jets_ge10modTop_lt175mlb_150to250met");
  result->GetXaxis()->SetBinLabel(77, "ge4jets_ge10modTop_ge175mlb_150to250met");
  

  return result;
  
}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2( int jesType, bool add2ndLepToMet ){

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
  
  int nMedBTags = babyAnalyzer.ngoodbtags(); 
  if( jesType==1)  nMedBTags = babyAnalyzer.jup_ngoodbtags();
  if( jesType==-1) nMedBTags = babyAnalyzer.jdown_ngoodbtags();
  
  int nTightTags = 0;
  double tight_wp = 0.935;
  vector<float> jet_csvv2 = babyAnalyzer.ak4pfjets_CSV();
  if( jesType==1 )  jet_csvv2 = babyAnalyzer.jup_ak4pfjets_CSV();
  if( jesType==-1 ) jet_csvv2 = babyAnalyzer.jdown_ak4pfjets_CSV();
  for(int iJet=0; iJet<(int)jet_csvv2.size(); iJet++){
    if( jet_csvv2[iJet] >= tight_wp ) nTightTags++;
  }
  
  bool is0b = ( (nMedBTags==0) || (nMedBTags>=1 && nTightTags==0 && mlb>175.0) );
  
  if( is0b ){
    if( jesType==1  ) mlb = ( babyAnalyzer.lep1_p4() + babyAnalyzer.jup_ak4pfjets_leadbtag_p4() ).M();
    if( jesType==-1 ) mlb = ( babyAnalyzer.lep1_p4() + babyAnalyzer.jdown_ak4pfjets_leadbtag_p4() ).M();
    else              mlb = ( babyAnalyzer.lep1_p4() + babyAnalyzer.ak4pfjets_leadbtag_p4() ).M();
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


  // Require dPhi(met,j1,2)>=0.8
  double dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2();
  if( add2ndLepToMet ){
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jdown();
    else dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl();
  }
  else{
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jdown();
  }
  
  if( dPhiMetJet<0.8 ) return result;


  //
  // 27 Signal Region Bins
  //

  // Region A
  if( nGoodJets<4 && modTopness>=10.0 && mlb<175 ){
    if(     met>600) result.push_back(4);
    else if(met>450) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
  }

  // Region B
  if( nGoodJets<4 && modTopness>=10.0 && mlb>=175  ){
    if(     met>600) result.push_back(7);
    else if(met>450) result.push_back(6);
    else if(met>250) result.push_back(5);
  }
  
  // Region C
  if( nGoodJets>=4 && modTopness<0 && mlb<175 ){
    if(     met>650) result.push_back(12);
    else if(met>550) result.push_back(11);
    else if(met>450) result.push_back(10);
    else if(met>350) result.push_back(9);
    else if(met>250) result.push_back(8);
  }

  // Region D
  if( nGoodJets>=4 && modTopness<0 && mlb>=175  ){
    if(     met>550) result.push_back(16);
    else if(met>450) result.push_back(15);
    else if(met>350) result.push_back(14);
    else if(met>250) result.push_back(13);
  }

  // Region E
  if( nGoodJets>=4 && modTopness>=0 && modTopness<10.0 && mlb<175 ){
    if(     met>550) result.push_back(19);
    else if(met>350) result.push_back(18);
    else if(met>250) result.push_back(17);
  }
  
  // Region F
  if( nGoodJets>=4 && modTopness>=0 && modTopness<10.0 && mlb>=175  ){
    if(     met>450) result.push_back(21);
    else if(met>250) result.push_back(20);
  }

  // Region G
  if( nGoodJets>=4 && modTopness>=10.0 && mlb<175 ){
    if(     met>600) result.push_back(25);
    else if(met>450) result.push_back(24);
    else if(met>350) result.push_back(23);
    else if(met>250) result.push_back(22);
  }

  // Region H
  if( nGoodJets>=4 && modTopness>=10.0 && mlb>=175  ){
    if(     met>450) result.push_back(27);
    else if(met>250) result.push_back(26);
  }



  // Coarser MET bins for bkg estimates
  if( nGoodJets<4 ){
    if(modTopness>=10.0){
      if(mlb<175 && met>450) result.push_back(28); 
      if(mlb>=175  && met>250) result.push_back(29); 
    }
  }
  if( nGoodJets>=4 ){
    if( modTopness<0.0 ){
      if( mlb<175  && met>550 ) result.push_back(30); 
      if( mlb>=175  && met>450 ) result.push_back(31); 
    }
    if( modTopness>=0.0 && modTopness<10.0 ){
      if( mlb<175  && met>350 ) result.push_back(32); 
      if( mlb>=175  && met>250 ) result.push_back(33); 
    }
    if( modTopness>=10.0 ){
      if( mlb<175  && met>450 ) result.push_back(34); 
      if( mlb>=175  && met>250 ) result.push_back(35); 
    }
  }
      
  
  // nJets Bins
  if( nGoodJets<4  ) result.push_back(36); 
  if( nGoodJets>=4 ) result.push_back(37); 
  

  // nJets and modTopness Bins
  if( nGoodJets<4  && modTopness>=10.0 ) result.push_back(38); 
  if( nGoodJets>=4 ){
    if(      modTopness>=10.0 ) result.push_back(39); 
    else if( modTopness<10.0  ) result.push_back(40); 
    else if( modTopness<0.0   ) result.push_back(41); 
  }
    
  
  // nJet, modTopness, met bins, inclusive in Mlb
  if( nGoodJets<4 ){
    if(modTopness>=10.0){
      if(met>=150.0 && met<250.0) result.push_back(42); 
      if(met>=250.0 && met<350.0) result.push_back(43);
      if(met>=350.0 && met<450.0) result.push_back(44); 
      if(met>=450.0 && met<600.0) result.push_back(45); 
      if(met>=600.0)              result.push_back(46); 

      if(met>=250.0 && met<450.0) result.push_back(47); 
      if(met>=450.0 && met<600.0) result.push_back(48); 
      if(met>=600.0)              result.push_back(49); 
    }
  }
 
  if( nGoodJets>=4 ){
    if(modTopness<0.0){
      if(met>=150.0 && met<250.0) result.push_back(50);  
      if(met>=250.0 && met<350.0) result.push_back(51);  
      if(met>=350.0 && met<450.0) result.push_back(52);  
      if(met>=450.0 && met<550.0) result.push_back(53);  
      if(met>=550.0 && met<650.0) result.push_back(54);  
      if(met>=650.0)              result.push_back(55);  
      if(met>=550.0)              result.push_back(56);  
    }
    if(modTopness>=0.0 && modTopness<10.0){
      if(met>=150.0 && met<250.0) result.push_back(57);  
      if(met>=250.0 && met<350.0) result.push_back(58);  
      if(met>=350.0 && met<550.0) result.push_back(59);  
      if(met>=550.0)              result.push_back(60);  
      
      if(met>=250.0 && met<450.0) result.push_back(61);  
      if(met>=450.0)              result.push_back(62); 
    }
    if(modTopness>=10.0){
      if(met>=150.0 && met<250.0) result.push_back(63);  
      if(met>=250.0 && met<350.0) result.push_back(64);  
      if(met>=350.0 && met<450.0) result.push_back(65);  
      if(met>=450.0 && met<600.0) result.push_back(66);  
      if(met>=600.0)              result.push_back(67);  
    
      if(met>=250.0 && met<450.0) result.push_back(68);  
      if(met>=450.0)              result.push_back(69);  
    }
  } // inclusive nJets>=4 bins
  

  // 150<met<250 CR bins
  if( nGoodJets<4 && modTopness>=10.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(70); 
    if(mlb>=175  && met>150 && met<=250) result.push_back(71); 
  }
  if( nGoodJets>=4 && modTopness<0.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(72); 
    if(mlb>=175  && met>150 && met<=250) result.push_back(73); 
  }
  if( nGoodJets>=4 && modTopness>=0.0 && modTopness<10.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(74); 
    if(mlb>=175  && met>150 && met<=250) result.push_back(75); 
  }
  if( nGoodJets>=4 && modTopness>=10.0 ){
    if(mlb<175  && met>150 && met<=250) result.push_back(76); 
    if(mlb>=175  && met>150 && met<=250) result.push_back(77); 
  }
  
     
  return result;
}


//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_bJetPt_v1(){

  int nBins_dev_ext30fb_bJetPt_v1_ = 78;
  TH1D *result = new TH1D("h_yields_SR_dev_ext30fb_bJetPt_v1", "Yields, Signal Regions, extnded to 30fb, binned with BJetPt", nBins_dev_ext30fb_bJetPt_v1_, 1.0, (double)nBins_dev_ext30fb_bJetPt_v1_+1.0);

  // Region A, nJet<4, modTop>=10, bJetPt<200
  result->GetXaxis()->SetBinLabel(1, "lt4jets_ge10modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(2, "lt4jets_ge10modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(3, "lt4jets_ge10modTop_lt200bJetPt_450to600met");
  result->GetXaxis()->SetBinLabel(4, "lt4jets_ge10modTop_lt200bJetPt_600toInfmet");
  
  // Region B, nJet<4, modTop>=10, bJetPt>=200
  result->GetXaxis()->SetBinLabel(5, "lt4jets_ge10modTop_ge200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(6, "lt4jets_ge10modTop_ge200bJetPt_350to500met");
  result->GetXaxis()->SetBinLabel(7, "lt4jets_ge10modTop_ge200bJetPt_500to650met");
  result->GetXaxis()->SetBinLabel(8, "lt4jets_ge10modTop_ge200bJetPt_650toInfmet");
  
  // Region C, nJet>=4, modTop<0, bJetPt<200
  result->GetXaxis()->SetBinLabel(9, "ge4jets_lt0modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(10, "ge4jets_lt0modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(11, "ge4jets_lt0modTop_lt200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(12, "ge4jets_lt0modTop_lt200bJetPt_550to650met");
  result->GetXaxis()->SetBinLabel(13, "ge4jets_lt0modTop_lt200bJetPt_650toInfmet");

  // Region D, nJet>=4, modTop<0, bJetPt>=200
  result->GetXaxis()->SetBinLabel(14, "ge4jets_lt0modTop_ge200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(15, "ge4jets_lt0modTop_ge200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(16, "ge4jets_lt0modTop_ge200bJetPt_450to550met");
  result->GetXaxis()->SetBinLabel(17, "ge4jets_lt0modTop_ge200bJetPt_550toInfmet");

  // Region E, nJet>=4, 0<=modTop<10, bJetPt<200
  result->GetXaxis()->SetBinLabel(18, "ge4jets_0to10modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(19, "ge4jets_0to10modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(20, "ge4jets_0to10modTop_lt200bJetPt_450toInfmet");
  
  // Region F, nJet>=4, 0<=modTop<10, bJetPt>=200
  result->GetXaxis()->SetBinLabel(21, "ge4jets_0to10modTop_ge200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(22, "ge4jets_0to10modTop_ge200bJetPt_350to500met");
  result->GetXaxis()->SetBinLabel(23, "ge4jets_0to10modTop_ge200bJetPt_500toInfmet");

  // Region G, nJet>=4, modTop>=10, bJetPt<200
  result->GetXaxis()->SetBinLabel(24, "ge4jets_ge10modTop_lt200bJetPt_250to350met");
  result->GetXaxis()->SetBinLabel(25, "ge4jets_ge10modTop_lt200bJetPt_350to450met");
  result->GetXaxis()->SetBinLabel(26, "ge4jets_ge10modTop_lt200bJetPt_450to650met");
  result->GetXaxis()->SetBinLabel(27, "ge4jets_ge10modTop_lt200bJetPt_650toInfmet");
  
  // Region H, nJet>=4, modTop>=10, bJetPt>=200
  result->GetXaxis()->SetBinLabel(28, "ge4jets_ge10modTop_ge200bJetPt_250to450met");
  result->GetXaxis()->SetBinLabel(29, "ge4jets_ge10modTop_ge200bJetPt_450toInfmet");


  // Coarser MET bins for bkg estimates
  result->GetXaxis()->SetBinLabel(30, "lt4jets_ge10modTop_ge200bJetPt_500toInfmet");
  result->GetXaxis()->SetBinLabel(31, "ge4jets_lt0modTop_lt200bJetPt_550toInfmet");
  result->GetXaxis()->SetBinLabel(32, "ge4jets_lt0modTop_ge200bJetPt_450toInfmet");
  result->GetXaxis()->SetBinLabel(33, "ge4jets_0to10modTop_lt200bJetPt_350toInfmet");
  result->GetXaxis()->SetBinLabel(34, "ge4jets_0to10modTop_ge200bJetPt_350toInfmet");
  result->GetXaxis()->SetBinLabel(35, "ge4jets_ge10modTop_lt200bJetPt_450toInfmet");
  result->GetXaxis()->SetBinLabel(36, "ge4jets_ge10modTop_ge200bJetPt_250toInfmet");

  // nJet Bins 
  result->GetXaxis()->SetBinLabel(37, "lt4jets");
  result->GetXaxis()->SetBinLabel(38, "ge4jets");
  
  // nJet, modTopness Bins
  result->GetXaxis()->SetBinLabel(39, "lt4jets_ge10modTop");
  result->GetXaxis()->SetBinLabel(40, "ge4jets_lt0modTop");
  result->GetXaxis()->SetBinLabel(41, "ge4jets_0to10modTop");
  result->GetXaxis()->SetBinLabel(42, "ge4jets_ge10modTop");
  
  // nJet, modTopness, met Bins, inclusive in bJetPt
  result->GetXaxis()->SetBinLabel(43, "lt4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(44, "lt4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(45, "lt4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(46, "lt4jets_ge10modTop_450to600met");
  result->GetXaxis()->SetBinLabel(47, "lt4jets_ge10modTop_600toInfmet");

  result->GetXaxis()->SetBinLabel(48, "lt4jets_ge10modTop_350to500met");
  result->GetXaxis()->SetBinLabel(49, "lt4jets_ge10modTop_500to650met");
  result->GetXaxis()->SetBinLabel(50, "lt4jets_ge10modTop_650toInfmet");
  
  result->GetXaxis()->SetBinLabel(51, "ge4jets_lt0modTop_150to250met");
  result->GetXaxis()->SetBinLabel(52, "ge4jets_lt0modTop_250to350met");
  result->GetXaxis()->SetBinLabel(53, "ge4jets_lt0modTop_350to450met");
  result->GetXaxis()->SetBinLabel(54, "ge4jets_lt0modTop_450to550met");
  result->GetXaxis()->SetBinLabel(55, "ge4jets_lt0modTop_550to650met");
  result->GetXaxis()->SetBinLabel(56, "ge4jets_lt0modTop_650toInfmet");

  result->GetXaxis()->SetBinLabel(57, "ge4jets_lt0modTop_550toInfmet");
  
  result->GetXaxis()->SetBinLabel(58, "ge4jets_0to10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(59, "ge4jets_0to10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(60, "ge4jets_0to10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(61, "ge4jets_0to10modTop_450toInfmet");

  result->GetXaxis()->SetBinLabel(62, "ge4jets_0to10modTop_350to500met");
  result->GetXaxis()->SetBinLabel(63, "ge4jets_0to10modTop_500toInfmet");

  result->GetXaxis()->SetBinLabel(64, "ge4jets_ge10modTop_150to250met");
  result->GetXaxis()->SetBinLabel(65, "ge4jets_ge10modTop_250to350met");
  result->GetXaxis()->SetBinLabel(66, "ge4jets_ge10modTop_350to450met");
  result->GetXaxis()->SetBinLabel(67, "ge4jets_ge10modTop_450to650met");
  result->GetXaxis()->SetBinLabel(68, "ge4jets_ge10modTop_650toInfmet");

  result->GetXaxis()->SetBinLabel(69, "ge4jets_ge10modTop_250to450met");
  result->GetXaxis()->SetBinLabel(70, "ge4jets_ge10modTop_450toInfmet");


  // 150<met<250 CR bins
  result->GetXaxis()->SetBinLabel(71, "lt4jets_ge10modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(72, "lt4jets_ge10modTop_ge200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(73, "ge4jets_lt0modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(74, "ge4jets_lt0modTop_ge200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(75, "ge4jets_0to10modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(76, "ge4jets_0to10modTop_ge200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(77, "ge4jets_ge10modTop_lt200bJetPt_150to250met");
  result->GetXaxis()->SetBinLabel(78, "ge4jets_ge10modTop_ge200bJetPt_150to250met");
  

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


  // Require dPhi(met,j1,2)>=0.8
  double dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2();
  if( add2ndLepToMet ){
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jdown();
    else dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl();
  }
  else{
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jdown();
  }
  
  if( dPhiMetJet<0.8 ) return result;



  //
  // 29 Signal Region Bins
  //

  // Region A
  if( nGoodJets<4 && modTopness>=10.0 && leadBJetPt<200 ){
    if(     met>600) result.push_back(4);
    else if(met>450) result.push_back(3);
    else if(met>350) result.push_back(2);
    else if(met>250) result.push_back(1);
  }

  // Region B
  if( nGoodJets<4 && modTopness>=10.0 && leadBJetPt>=200 ){
    if(     met>650) result.push_back(8);
    else if(met>500) result.push_back(7);
    else if(met>350) result.push_back(6);
    else if(met>250) result.push_back(5);
  }

  // Region C
  if( nGoodJets>=4 && modTopness<0 && leadBJetPt<200 ){
    if(     met>650) result.push_back(13);
    else if(met>550) result.push_back(12);
    else if(met>450) result.push_back(11);
    else if(met>350) result.push_back(10);
    else if(met>250) result.push_back(9);
  }

  // Region D
  if( nGoodJets>=4 && modTopness<0 && leadBJetPt>=200 ){
    if(     met>550) result.push_back(17);
    else if(met>450) result.push_back(16);
    else if(met>350) result.push_back(15);
    else if(met>250) result.push_back(14);
  }

  // Region E
  if( nGoodJets>=4 && modTopness>=0 && modTopness<10.0 && leadBJetPt<200 ){
    if(     met>450) result.push_back(20);
    else if(met>350) result.push_back(19);
    else if(met>250) result.push_back(18);
  }
 
  // Region F
  if( nGoodJets>=4 && modTopness>=0 && modTopness<10.0 && leadBJetPt>=200 ){
    if(     met>500) result.push_back(23);
    else if(met>350) result.push_back(22);
    else if(met>250) result.push_back(21);
  }
  
  // Region G
  if( nGoodJets>=4 && modTopness>=10.0 && leadBJetPt<200 ){
    if(     met>650) result.push_back(27);
    else if(met>450) result.push_back(26);
    else if(met>350) result.push_back(25);
    else if(met>250) result.push_back(24);
  }

  // Region H
  if(nGoodJets>=4 && modTopness>=10.0 && leadBJetPt>=200 ){
    if(     met>450) result.push_back(29);
    else if(met>250) result.push_back(28);
  }


  // Coarser MET bins for bkg estimates
  if( nGoodJets<4 ){
    if( modTopness>=10.0 ){
      if( leadBJetPt>=200 && met>500 ) result.push_back(30);
    }
  }
  if( nGoodJets>=4 ){
    if( modTopness<0 ){
      if( leadBJetPt<200  && met>550) result.push_back(31);
      if( leadBJetPt>=200 && met>450) result.push_back(32);
    }
    if( modTopness>=0 && modTopness<10.0 ){
      if( leadBJetPt<200  && met>350) result.push_back(33);
      if( leadBJetPt>=200 && met>350) result.push_back(34);
    }
    if( modTopness>=10.0 ){
      if( leadBJetPt<200  && met>450) result.push_back(35);
      if( leadBJetPt>=200 && met>250) result.push_back(36);
    }
  }


  // nJets Bins
  if( nGoodJets<4  ) result.push_back(37);  // "lt4jets"
  if( nGoodJets>=4 ) result.push_back(38);  // "ge4jets"
  

  // nJets and modTopness Bins
  if( nGoodJets<4 && modTopness>=10.0) result.push_back(39); // "lt4jets_ge10modTop"
  if( nGoodJets>=4 ){
    if(      modTopness>=10.0 ) result.push_back(42);  // "ge4jets_ge10modTop"
    else if( modTopness<10.0  ) result.push_back(41);  // "ge4jets_0to10modTop"
    else if( modTopness<0.0   ) result.push_back(40);  // "ge4jets_lt0modTop"
  }
    

  // nJet, modTopness, met bins, inclusive in bJetPt
  if( nGoodJets<4 ){
    if(modTopness>=10.0){
      if(met>=150.0 && met<250.0) result.push_back(43); // "lt4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(44); // "lt4jets_ge10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(45); // "lt4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<600.0) result.push_back(46); // "lt4jets_ge10modTop_450to600met"
      if(met>=600.0)              result.push_back(47); // "lt4jets_ge10modTop_600toInfmet"

      if(met>=350.0 && met<500.0) result.push_back(48); // "lt4jets_ge10modTop_350to450met"
      if(met>=500.0 && met<650.0) result.push_back(49); // "lt4jets_ge10modTop_500to650met"
      if(met>=650.0)              result.push_back(50); // "lt4jets_ge10modTop_650toInfmet"
    }
  }

  if( nGoodJets>=4 ){
    if(modTopness<0.0){
      if(met>=150.0 && met<250.0) result.push_back(51);  // "ge4jets_lt0modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(52);  // "ge4jets_lt0modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(53);  // "ge4jets_lt0modTop_350to450met"
      if(met>=450.0 && met<550.0) result.push_back(54);  // "ge4jets_lt0modTop_450to550met"
      if(met>=550.0 && met<650.0) result.push_back(55);  // "ge4jets_lt0modTop_550to650met"
      if(met>=650.0)              result.push_back(56);  // "ge4jets_lt0modTop_650toInfmet"

      if(met>=550.0)              result.push_back(57);  // "ge4jets_lt0modTop_550toInfmet"
    }
    
    if(modTopness>=0.0 && modTopness<10.0){
      if(met>=150.0 && met<250.0) result.push_back(58);  // "ge4jets_0to10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(59);  // "ge4jets_0to10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(60);  // "ge4jets_0to10modTop_350to450met"
      if(met>=450.0)              result.push_back(61);  // "ge4jets_0to10modTop_450toInfmet"

      if(met>=350.0 && met<500.0) result.push_back(62);  // "ge4jets_0to10modTop_350to500met"
      if(met>=500.0)              result.push_back(63);  // "ge4jets_0to10modTop_500toInfmet"
    }

    if(modTopness>=10.0){
      if(met>=150.0 && met<250.0) result.push_back(64);  // "ge4jets_ge10modTop_150to250met"
      if(met>=250.0 && met<350.0) result.push_back(65);  // "ge4jets_ge10modTop_250to350met"
      if(met>=350.0 && met<450.0) result.push_back(66);  // "ge4jets_ge10modTop_350to450met"
      if(met>=450.0 && met<650.0) result.push_back(67);  // "ge4jets_ge10modTop_450to650met"
      if(met>=650.0)              result.push_back(68);  // "ge4jets_ge10modTop_650toInfmet"
    
      if(met>=250.0 && met<450.0) result.push_back(69);  // "ge4jets_ge10modTop_250to450met"
      if(met>=450.0)              result.push_back(70);  // "ge4jets_ge10modTop_450toInfmet"
    }
  } // inclusive nJets>=4 bins
  

  // 150<met<250 CR bins
  if( nGoodJets<4 && modTopness>=10.0 ){
    if(leadBJetPt<200.0  && met>150.0 && met<=250.0) result.push_back(71); // "lt4jets_ge10modTop_lt200bJetPt_150to250met"
    if(leadBJetPt>=200.0 && met>150.0 && met<=250.0) result.push_back(72); // "lt4jets_ge10modTop_ge200bJetPt_150to250met"
  }
  if( nGoodJets>=4 && modTopness<0.0 ){
    if(leadBJetPt<200.0  && met>150.0 && met<=250.0) result.push_back(73); // "lt4jets_ge10modTop_lt200bJetPt_150to250met"
    if(leadBJetPt>=200.0 && met>150.0 && met<=250.0) result.push_back(74); // "lt4jets_ge10modTop_ge200bJetPt_150to250met"
  }
  if( nGoodJets>=4 && modTopness>=0.0 && modTopness<10.0 ){
    if(leadBJetPt<200.0  && met>150.0 && met<=250.0) result.push_back(75); // "lt4jets_ge10modTop_lt200bJetPt_150to250met"
    if(leadBJetPt>=200.0 && met>150.0 && met<=250.0) result.push_back(76); // "lt4jets_ge10modTop_ge200bJetPt_150to250met"
  }
  if( nGoodJets>=4 && modTopness>=10.0 ){
    if(leadBJetPt<200.0  && met>150.0 && met<=250.0) result.push_back(77); // "lt4jets_ge10modTop_lt200bJetPt_150to250met"
    if(leadBJetPt>=200.0 && met>150.0 && met<=250.0) result.push_back(78); // "lt4jets_ge10modTop_ge200bJetPt_150to250met"
  }
  

  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* categoryInfo::getYieldHistoTemplate_SR_corridor(){
  
  int nBins_SR_corridor_ = 7;
  TH1D *result = new TH1D("h_yields_SR_corridor", "Yields, SR Top Corridor", nBins_SR_corridor_, 1.0, (double)nBins_SR_corridor_+1.0);
  
  result->GetXaxis()->SetBinLabel(1, "top_corridor_250to350met");
  result->GetXaxis()->SetBinLabel(2, "top_corridor_350to450met");
  result->GetXaxis()->SetBinLabel(3, "top_corridor_450to550met");
  result->GetXaxis()->SetBinLabel(4, "top_corridor_550toInfmet");

  // Region for background estimate
  result->GetXaxis()->SetBinLabel(5, "top_corridor_450toInfmet");
  
  // Inclusive
  result->GetXaxis()->SetBinLabel(6, "top_corridor");
  result->GetXaxis()->SetBinLabel(7, "top_corridor_150to250met");

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<int> categoryInfo::passCategory_SR_corridor( int jesType, bool add2ndLepToMet ){

  vector<int> result;
  result.clear();

  // Met 
  double met = babyAnalyzer.pfmet();
  double met_phi = babyAnalyzer.pfmet_phi();
  if( add2ndLepToMet){
    if(jesType==0){
      met = babyAnalyzer.pfmet_rl();
      met_phi = babyAnalyzer.pfmet_phi_rl();
    }
    if(jesType==1){
      met = babyAnalyzer.pfmet_rl_jup();
      met_phi = babyAnalyzer.pfmet_phi_rl_jup();
    }
    if(jesType==-1){
      met = babyAnalyzer.pfmet_rl_jdown();
      met_phi = babyAnalyzer.pfmet_phi_rl_jdown();
    }
  }
  else{
    if(jesType==1){
      met = babyAnalyzer.pfmet_jup();
      met_phi = babyAnalyzer.pfmet_phi_jup();
    }
    if(jesType==-1){ 
      met = babyAnalyzer.pfmet_jdown();
      met_phi = babyAnalyzer.pfmet_phi_jdown();
    }
  }
  
  
  // NJets
  int nGoodJets = babyAnalyzer.ngoodjets();
  if( jesType==1 )  nGoodJets = babyAnalyzer.jup_ngoodjets();
  if( jesType==-1 ) nGoodJets = babyAnalyzer.jdown_ngoodjets();
  
  // Require at least 5 jets
  if( nGoodJets < 5 ) return result;


  // Lead Jet pT
  //double leadJetPt = babyAnalyzer.ak4pfjets_p4().at(0).Pt();
  //if( jesType==1 )  leadJetPt = babyAnalyzer.jup_ak4pfjets_p4().at(0).Pt();
  //if( jesType==-1 ) leadJetPt = babyAnalyzer.jdown_ak4pfjets_p4().at(0).Pt();
  
  // Require leading jet to have pT > 200
  //if( leadJetPt <= 200.0 ) return result;  


  // Lead Jet is bTagged
  //bool leadJet_isBTag = babyAnalyzer.ak4pfjets_passMEDbtag().at(0);
  //if( jesType==1 )  leadJet_isBTag = babyAnalyzer.jup_ak4pfjets_passMEDbtag().at(0);
  //if( jesType==-1 ) leadJet_isBTag = babyAnalyzer.jdown_ak4pfjets_passMEDbtag().at(0);

  // Require leading jet to NOT be b-tagged
  //if( leadJet_isBTag ) return result;      


  double lepPt = babyAnalyzer.lep1_p4().Pt();

  // Require lepton pT < 150
  if( lepPt>=150.0 ) return result;


  // dPhi(lep,met)
  double dPhiLepMet = 99.9;
  TLorentzVector lep_TLV( 0.0, 0.0, 0.0, 0.0);
  lep_TLV.SetPxPyPzE( babyAnalyzer.lep1_p4().Px(), babyAnalyzer.lep1_p4().Py(), babyAnalyzer.lep1_p4().Pz(), babyAnalyzer.lep1_p4().E() ); 
  TLorentzVector met_TLV( 0.0, 0.0, 0.0, 0.0 );
  met_TLV.SetPxPyPzE( met*cos(met_phi), met*sin(met_phi), 0.0, met );
  dPhiLepMet = lep_TLV.DeltaPhi(met_TLV);
  
  // Require dPhi(lep,met)< 2.0
  if( fabs(dPhiLepMet) >= 2.0 ) return result;

  // Require dPhi(met,j1,2)>=0.5
  double dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2();
  if( add2ndLepToMet ){
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl_jdown();
    else dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_rl();
  }
  else{
    if( jesType==1 ) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jup();
    else if( jesType==-1) dPhiMetJet = babyAnalyzer.mindphi_met_j1_j2_jdown();
  }

  if( dPhiMetJet<0.5 ) return result;


  //  Inclusive Bin
  result.push_back(6);

  if( met>=150.0 && met<250.0 ) result.push_back(7); // CR bin
  
  if( met>=250.0 && met<350.0 ) result.push_back(1); // SR bin 1
  if( met>=350.0 && met<450.0 ) result.push_back(2); // SR bin 2
  if( met>=450.0 && met<550.0 ) result.push_back(3); // SR bin 3
  if( met>=550.0 )              result.push_back(4); // SR bin 4

  if( met>=450.0 )              result.push_back(5); // For CR2l bkgEstimate
  

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

  int nMedBTags = babyAnalyzer.ngoodbtags(); 
  if( jesType==1)  nMedBTags = babyAnalyzer.jup_ngoodbtags();
  if( jesType==-1) nMedBTags = babyAnalyzer.jdown_ngoodbtags();

  
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
  

  if( nMedBTags>=0 ){
    
    // >=0 bTags
    if( met>50  ) result.push_back(1);
    if( met>100 ) result.push_back(2);
    if( met>150 ) result.push_back(3);
    if( met>200 ) result.push_back(4);
    if( met>250 ) result.push_back(5);

  } // >=0 nMedBTags


  if( nMedBTags>=1 ){
    
    // >=1 bTags
    if( met>50  ) result.push_back(6);
    if( met>100 ) result.push_back(7);
    if( met>150 ) result.push_back(8);
    if( met>200 ) result.push_back(9);
    if( met>250 ) result.push_back(10);
  
  } // >=1 nMedBTags

  if( nMedBTags>=2 ){
    
    // >=2 bTags
    if( met>50  ) result.push_back(11);
    if( met>100 ) result.push_back(12);
    if( met>150 ) result.push_back(13);
    if( met>200 ) result.push_back(14);
    if( met>250 ) result.push_back(15);

  } // >=0 nMedBTags


  return result;

}

//////////////////////////////////////////////////////////////////////
