#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"

// std
#include <algorithm>
#include <string>
#include <vector>

// stopCORE
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"


void getHistosForLimitSetting(){


  //
  // Options
  //
  bool getSystematicsFromFile = false;

  
  //
  // Open input files
  //
  TFile *f_in_lostLep   = new TFile("../StopBabyLooper__CR2l/Output/BkgEstimate/h__bkgEstimate_diLepton.root", "read");

  TFile *f_in_1lepFromW = new TFile("Histos/Nominal/h__allBkg_25ns.root", "read");

  TFile *f_in_1lepFromT = new TFile("Histos/Nominal/h__allBkg_25ns.root", "read");
  
  TFile *f_in_ZtoNuNu   = new TFile("Histos/Nominal/h__allBkg_25ns.root", "read");
  
  TFile *f_in_data      = new TFile("Histos/Nominal/h__data_single_lepton_met_2016B_25ns.root", "read");

  
  //
  // Open output files
  //
  TFile *f_out_lostLep   = new TFile("Histos/Nominal/h_limit__lostLep.root", "recreate");

  TFile *f_out_1lepFromW = new TFile("Histos/Nominal/h_limit__1lepFromW.root", "recreate");

  TFile *f_out_1lepFromT = new TFile("Histos/Nominal/h_limit__1lepFromT.root", "recreate");
  
  TFile *f_out_ZtoNuNu   = new TFile("Histos/Nominal/h_limit__ZtoNuNu.root", "recreate");

  TFile *f_out_data      = new TFile("Histos/Nominal/h_limit__data.root", "recreate");
  
  

  //
  // Get list of categories
  //
  categoryInfo::vect_util catList;
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop_250to350met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop_350toInfmet) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w_250to350met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w_350toInfmet) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w_250to325met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w_325toInfmet) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w_250to350met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w_350to450met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w_450toInfmet) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee2jets_ge6p4modTop_150to250met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ee3jets_ge200mt2w_150to250met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_lt200mt2w_150to250met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge4jets_ge200mt2w_150to250met) );
  
  
 
  //
  // Make output histos
  //
  TH1D *h_temp = NULL;

  
  //
  // Lost Lepton
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  TH1D *h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
  // Get some lostLep systematics from file
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_dataStatsUp");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_dataStatsDn");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);

  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_mcStatsUp");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_mcStatsDn");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
  //h_temp = (TH1D*)f_in_lostLep->Get("CR2l_pdfUp");
  //h_lostLep = (TH1D*)h_temp->Clone();
  //h_lostLep->SetDirectory(f_out_lostLep);
  
  //h_temp = (TH1D*)f_in_lostLep->Get("CR2l_pdfDn");
  //h_lostLep = (TH1D*)h_temp->Clone();
  //h_lostLep->SetDirectory(f_out_lostLep);
  
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_alphasUp");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_alphasDn");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_q2Up");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_q2Dn");
  h_lostLep = (TH1D*)h_temp->Clone();
  h_lostLep->SetDirectory(f_out_lostLep);
  
   
  // use 2015 relative errors for remaining

  //
  // JES up
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_JESUp");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*1.0356 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*1.0230 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*1.0168 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*0.9952 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*1.0059 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*0.9834 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*1.0984 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*0.9749 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*1.0476 );

  

  //
  // JES Down
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_JESDn");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*1.0463 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*0.9715 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*1.0043 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*1.0890 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*0.9803 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*1.0201 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*1.0109 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*0.9693 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*1.0114 );

  
  //
  // bTag HF up
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_bTagEffHFUp");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*0.9935 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*0.9933 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*1.0044 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*0.9900 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*0.9979 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*0.9929 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*1.0009 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*0.9947 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*1.0006 );

  
  //
  // bTag HF dn
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_bTagEffHFDn");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*1.0072 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*1.0069 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*0.9958 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*0.9897 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*1.0022 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*1.0073 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*0.9997 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*1.0055 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*0.9996 );


  
  //
  // bTag LF up
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_bTagEffLFUp");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*0.9935 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*0.9972 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*0.9993 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*0.9901 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*1.0021 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*0.9992 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*1.0021 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*0.9981 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*0.9914 );



  //
  // bTag LF dn
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_bTagEffLFDn");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*1.0068 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*1.0027 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*1.0012 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*1.0104 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*0.9979 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*1.0007 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*0.9981 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*1.0017 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*1.0091 );




  //
  // lepton SF up
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_lepSFUp");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*0.9844 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*0.9831 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*0.9860 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*0.9885 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*0.9814 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*0.9819 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*0.9788 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*0.9809 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*0.9526 );



  //
  // lepton SF dn
  //
  h_temp = (TH1D*)f_in_lostLep->Get("CR2l_yield");
  h_lostLep = (TH1D*)h_temp->Clone("CR2l_lepSFDn");
  h_lostLep->SetDirectory(f_out_lostLep);

  // ee2j, 250<MET<350
  h_lostLep->SetBinContent( 1, h_lostLep->GetBinContent(1)*1.0438 );

  // ee2j, MET>350
  h_lostLep->SetBinContent( 2, h_lostLep->GetBinContent(2)*1.0452 );

  // ee3j, 250<MET<350
  h_lostLep->SetBinContent( 3, h_lostLep->GetBinContent(3)*1.0376 );

  // ee3j, MET>350
  h_lostLep->SetBinContent( 4, h_lostLep->GetBinContent(4)*1.0352 );

  // ge4j, mt2w<200, 250<MET<325
  h_lostLep->SetBinContent( 5, h_lostLep->GetBinContent(5)*1.0416 );

  // ge4j, mt2w<200, MET>325
  h_lostLep->SetBinContent( 6, h_lostLep->GetBinContent(6)*1.0410 );

  // ge4j, mt2w>200, 250<MET<350
  h_lostLep->SetBinContent( 7, h_lostLep->GetBinContent(7)*1.0344 );

  // ge4j, mt2w>200, 350<MET<450
  h_lostLep->SetBinContent( 8, h_lostLep->GetBinContent(8)*1.0428 );

  // ge4j, mt2w>200, MET>450
  h_lostLep->SetBinContent( 9, h_lostLep->GetBinContent(9)*1.0920 );


 

  //
  // 1lep from W (W+jets)
  //
  TH1D *h_1lepFromW = (TH1D*)h_lostLep->Clone("ee1lepFromW_yield");
  h_1lepFromW->Reset();
  h_1lepFromW->SetTitle("1 lep from W (not from top)");
  h_1lepFromW->SetDirectory(f_out_1lepFromW);

  h_temp = (TH1D*)f_in_1lepFromW->Get("yields__genClassy_ee1lep_fromW__recoClassy_incl__sys_nominal");
  for(int iCat=0; iCat<(int)catList.size(); iCat++){
    h_1lepFromW->SetBinContent(iCat+1, h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
    h_1lepFromW->SetBinError(iCat+1, h_temp->GetBinError( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
  }

  

  //
  // 1lep from t (tt1l)
  //
  TH1D *h_1lepFromT = (TH1D*)h_lostLep->Clone("ee1lepFromT_yield");
  h_1lepFromT->Reset();
  h_1lepFromT->SetTitle("1 lep from top");
  h_1lepFromT->SetDirectory(f_out_1lepFromT);

  h_temp = (TH1D*)f_in_1lepFromT->Get("yields__genClassy_ee1lep_fromTop__recoClassy_incl__sys_nominal");
  for(int iCat=0; iCat<(int)catList.size(); iCat++){
    h_1lepFromT->SetBinContent(iCat+1, h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
    h_1lepFromT->SetBinError(iCat+1, h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
  }
  
  
  //
  // ZtoNuNu
  //
  TH1D *h_ZtoNuNu = (TH1D*)h_lostLep->Clone("ZtoNuNu_yield");
  h_ZtoNuNu->Reset();
  h_ZtoNuNu->SetTitle("Z to NuNu");
  h_ZtoNuNu->SetDirectory(f_out_ZtoNuNu);

  h_temp = (TH1D*)f_in_ZtoNuNu->Get("yields__genClassy_ZtoNuNu__recoClassy_incl__sys_nominal");
  for(int iCat=0; iCat<(int)catList.size(); iCat++){
    h_ZtoNuNu->SetBinContent(iCat+1, h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
    h_ZtoNuNu->SetBinError(iCat+1, h_temp->GetBinError( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
  }


  
  //
  // Observed
  //
  TH1D *h_obs = (TH1D*)h_lostLep->Clone("Observed_yield");
  h_obs->Reset();
  h_obs->SetTitle("Observed Yields");
  h_obs->SetDirectory(f_out_data);

  h_temp = (TH1D*)f_in_data->Get("yields__genClassy_incl__recoClassy_incl__sys_nominal");
  for(int iCat=0; iCat<(int)catList.size(); iCat++){
    h_obs->SetBinContent(iCat+1, h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
    h_obs->SetBinError(iCat+1, h_temp->GetBinError( h_temp->GetXaxis()->FindBin( catList[iCat].label.c_str() ) ) );
  }


  
  f_out_lostLep->Write();
  f_out_1lepFromW->Write();
  f_out_1lepFromT->Write();
  f_out_ZtoNuNu->Write();
  f_out_data->Write();

  f_out_lostLep->Close();
  f_out_1lepFromW->Close();
  f_out_1lepFromT->Close();
  f_out_ZtoNuNu->Close();
  f_out_data->Close();

  f_in_lostLep->Close();
  f_in_1lepFromW->Close();
  f_in_1lepFromT->Close();
  f_in_ZtoNuNu->Close();
  f_in_data->Close();


  return;

}
