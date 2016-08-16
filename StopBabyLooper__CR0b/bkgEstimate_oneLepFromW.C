// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

// std
#include <string>
#include <vector>

// stopCORE
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"


//
// Main
//
int bkgEstimate_oneLepFromW(){


  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  
  //
  // Configuration Variables
  //
  bool usePsuedoData = false;

  bool doRescale = false;
  double rescale = 1.0; // use lumi from stopCORE
  //double rescale = 5.0/eventWeightInfo::LUMI; // rescale to new lumi

  TString yield_base = "yields";

  TString texFile = "";

  

  //
  // recoClassy Type
  //
  recoClassyInfo::recoClassyUtil recoClassyType(recoClassyInfo::k_incl);
 
 
  //
  // Open Files
  //
  TString inDir_SR = "../StopBabyLooper__SR/Histos/Nominal/";
  TString inDir_CR = "Histos/Nominal/";
  
  TString outDir = "Output/BkgEstimate/";
  

  //
  // Signal Region
  //
  TFile *f_SR = new TFile(inDir_SR+"h__allBkg_25ns.root", "read");
  genClassyInfo::genClassyUtil genClassy_MC_SR_1lepFromW( genClassyInfo::k_ee1lep_fromW );
      

  //
  // diLepton CR Region
  //
  TFile *f_CR = new TFile(inDir_CR+"h__allBkg_25ns.root", "read");
  genClassyInfo::genClassyUtil genClassy_MC_CR_Incl( genClassyInfo::k_incl );
  genClassyInfo::genClassyUtil genClassy_MC_CR_1lepFromW( genClassyInfo::k_ee1lep_fromW );
  
  
  //
  // diLepton data
  //
  TFile *f_data_CR = NULL;
  genClassyInfo::genClassyUtil genClassy_data_CR( genClassyInfo::k_incl );
  if( usePsuedoData ){
    f_data_CR= new TFile(inDir_CR+"h__allBkg_25ns.root", "read");
  }
  else{
    f_data_CR = new TFile(inDir_CR+"h__data_single_lepton_met_2016B_25ns.root", "read");
  }
  

 
  //
  // Signal Region Categories
  //
  categoryInfo::vect_util sr_cats;
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop_250to350met ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop_350toInfmet ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee3jets_ge200mt2w_250to350met) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee3jets_ge200mt2w_350toInfmet ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_250to350met ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_350to450met ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_450toInfmet) );
  const int nSRs = (int)sr_cats.size();


  //
  // Signal Region to Control Region Cateogries
  //
  categoryInfo::vect_util cr_cats;
  cr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop ) );
  cr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop ) );
  cr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee3jets_ge200mt2w ) );
  cr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee3jets_ge200mt2w ) );
  cr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w ) );
  cr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w ) );
  cr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w ) );

  
  bool oneTF = true;
  for(int iSR=0; iSR<nSRs; iSR++){
    if( sr_cats[iSR].id != cr_cats[iSR].id ){
      oneTF = false;
      break;
    }
  }
    

  //
  // Systematics
  //
  systematicInfo::systematicUtil nominal_sys( systematicInfo::k_nominal );
  
  systematicInfo::vect_util systematicList = systematicInfo::getSystematicList_forLimit_oneLeptonNotFromTop();
  const int nSys = (int)systematicList.size();

  
  //
  // Output file for ratio
  //
  TFile  *f_out = new TFile(outDir+"h__bkgEstimate_oneLepFromW.root", "recreate");


  //
  // Histograms for limit setting
  //
  TH1D *h_SR[nSys];
  h_SR[0] = new TH1D("CR0byield", "CR0byield", nSRs, 0.0, nSRs); // Nominal
  for(int iCat=0; iCat<(int)nSRs; iCat++){
    h_SR[0]->GetXaxis()->SetBinLabel( iCat+1, sr_cats[iCat].label.c_str() );
  }
  h_SR[0]->SetDirectory(f_out);


  //
  // Systematics for limit setting
  //
  for(int iSys=1; iSys<nSys; iSys++){
    h_SR[iSys] = new TH1D(Form("CR0b_%s", systematicList[iSys].label.c_str()), Form("CR0b_%s",systematicList[iSys].label.c_str()), nSRs, 0.0, nSRs);   
    for(int iCat=0; iCat<(int)nSRs; iCat++){
      h_SR[iSys]->GetXaxis()->SetBinLabel( iCat+1, sr_cats[iCat].label.c_str() );
    }
    h_SR[iSys]->SetDirectory(f_out);
  }
    


  //
  // Make Tables
  //

  // ROW=Categories, COL=DiLepton Estimate and Components, Simple
  FILE *yFile;
  texFile = outDir;
  texFile += "bkgEstimate_oneLepFromW.tex";
  yFile = fopen(texFile.Data(), "w");
  
  cout << "Writing simple file of 1lepFromW Estimates to file; " << endl;
  cout << "    " << texFile << endl;

  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\usepackage{graphicx} \n\n");
  fprintf(yFile, "\\begin{document}\n");
  fprintf(yFile, "\\tiny \n");  
  fprintf(yFile, "\\begin{table} \n");
  fprintf(yFile, "\\caption{ 1lepFromW Background Estimate and Components, for each Signal Region } \n");
  fprintf(yFile, "\\scalebox{0.7}{ \n");
  if(oneTF){
    fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
    fprintf(yFile, "Category & $N_{1lepFromW}^{CR}$ & $N_{1lepFromW}^{CR}$ & $M_{1lepFromW}^{SR}/M_{1lepFromW}^{CR}$ & $N_{1lepFromW,estimate}^{SR}$");
  }
  else{
    fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|c|} \\hline \n");
    fprintf(yFile, "Category & $N_{Incl}^{CR}$ & $N_{1lepFromW}^{CR}$ & $M_{1lepFromW}^{CR,~MET~bin}/M_{1lepFromW}^{CR,~MET>250}$ & $M_{1lepFromW}^{SR,~MET~bin}/M_{1lepFromW}^{CR,~MET~bin}$ & $N_{1lepFromW,estimate}^{SR}$");
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");


  
  // ROW=Uncertainties, COL=DiLepton Estimate and Components, Summary
  FILE *uncFileSummary;
  TString uncFileSummaryName = outDir;
  uncFileSummaryName += "bkgEstimate_oneLepFromW__uncertaintyTable__summary.tex";
  uncFileSummary = fopen(uncFileSummaryName.Data(), "w");
  
  cout << "Writing table of 1lepFromW uncertainties to: " << endl;
  cout << "    " << uncFileSummaryName << endl;

  fprintf(uncFileSummary, "\\documentclass{article}\n");
  fprintf(uncFileSummary, "\\usepackage[landscape]{geometry}\n");
  fprintf(uncFileSummary, "\\usepackage{chngpage}\n\n");
  fprintf(uncFileSummary, "\\usepackage{graphicx} \n\n");
  fprintf(uncFileSummary, "\\begin{document}\n");
  fprintf(uncFileSummary, "\\tiny \n"); 
  fprintf(uncFileSummary, "\\begin{table} \n");
  fprintf(uncFileSummary, "\\caption{ Summary of 1lepFromW Background Estimate Uncertainties } \n");
  fprintf(uncFileSummary, "\\scalebox{0.7}{ \n");
  if(oneTF){
    fprintf(uncFileSummary, "\\begin{tabular}{|l|c|c|c|} \\hline \n");
    fprintf(uncFileSummary, "Systematic & $N_{1lepFromW}^{CR},~(\\%%)$ & $M_{1lepFromW}^{SR}/M_{1lepFromW}^{CR},~(\\%%)$ & $N_{1lepFromW,estimate}^{SR},~(\\%%)$ ");
  }
  else{
    fprintf(uncFileSummary, "\\begin{tabular}{|l|c|c|c|c|c|} \\hline \n");
    fprintf(uncFileSummary, "Systematic & $N_{1lepFromW}^{CR},~(\\%%)$ & $M_{1lepFromW}^{CR,~MET~bin}/M_{1lepFromW}^{CR,~MET>250},~(\\%%)$ & $M_{1lepFromW}^{SR,~MET~bin}/M_{1lepFromW}^{CR,~MET~bin},~(\\%%)$ & $N_{1lepFromW,estimate}^{SR},~(\\%%)$ ");
  }
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \\hline \n");


  const int nSys_unique = ((nSys-1)/2) + 3; // -1 for nominal, +1 for data stats, +1 for mc stats, +1 for total uncertainty
  double uncMax_cr_data[nSys_unique]; 
  double uncMin_cr_data[nSys_unique];
  double uncMax_tf_met[nSys_unique]; 
  double uncMin_tf_met[nSys_unique];
  double uncMax_tf_bTag[nSys_unique]; 
  double uncMin_tf_bTag[nSys_unique];
  double uncMax_sr_estimate[nSys_unique]; 
  double uncMin_sr_estimate[nSys_unique];
  for(int iSys=0; iSys<nSys_unique; iSys++){
    uncMax_cr_data[iSys] = 0.0;
    uncMin_cr_data[iSys] = 999.9;
    uncMax_tf_met[iSys] = 0.0;
    uncMin_tf_met[iSys] = 999.9;
    uncMax_tf_bTag[iSys] = 0.0;
    uncMin_tf_bTag[iSys] = 999.9;
    uncMax_sr_estimate[iSys] = 0.0;
    uncMin_sr_estimate[iSys] = 999.9;
  }


  //
  // Uncertainty table for each category
  //
  
  // ROW=Uncertainties, COL=DiLepton Estimate and Components
  FILE *uncFile = NULL;
  TString uncFileName = outDir;
  uncFileName += "bkgEstimate_oneLepFromW__uncertaintyTable__byCategory.tex";
  uncFile = fopen(uncFileName.Data(), "w");

  cout << "Writing table of 1lepFromW uncertainties to: " << endl;
  cout << "    " << uncFileName << endl;
  
  fprintf(uncFile, "\\documentclass{article}\n");
  fprintf(uncFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(uncFile, "\\usepackage{chngpage}\n\n");
  fprintf(uncFile, "\\usepackage{graphicx} \n\n");
  fprintf(uncFile, "\\begin{document}\n");
  fprintf(uncFile, "\\tiny \n"); 
  

   
  //
  // Loop over categories to get Inclusive CR yields
  //
  TH1D *h_temp = NULL;
  TString hName = "";
  for(int iSR=0; iSR<(int)sr_cats.size(); iSR++){
    
    //
    // Category Name for yield tables
    //
    fprintf(yFile, " %s & ", sr_cats[iSR].tex.c_str() );

    
    //
    // Cateogry infor for uncertainty table
    //
    fprintf(uncFile, "\\begin{table} \n");
    fprintf(uncFile, "\\caption{ 1lepFromW Background Estimate Uncertainties, for %s } \n", sr_cats[iSR].tex.c_str());
    fprintf(uncFile, "\\scalebox{0.6}{ \n");
    if(oneTF){
      fprintf(uncFile, "\\begin{tabular}{|l|c|c|c|c|c|c|} \\hline \n");
      fprintf(uncFile, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $N_{1lepFromW}^{CR},~(\\%%)$ & $M_{1lepFromW}^{CR,~MET~bin},~(\\%%)$ & $M_{1lepFromW}^{SR~MET~bin},~(\\%%)$ & $M_{1lepFroMW}^{SR}/M_{1lepFromW}^{CR},~(\\%%)$ & $N_{2\\ell,estimate}^{SR},~(\\%%)$ ");
    }
    else{
      fprintf(uncFile, "\\begin{tabular}{|l|c|c|c|c|c|c|c|c|} \\hline \n");
      fprintf(uncFile, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $N_{1lepFromW}^{CR},~(\\%%)$ & $M_{1lepFromW}^{CR,~MET>250},~(\\%%)$ & $M_{1lepFromW}^{CR,~MET~bin},~(\\%%)$ & $M_{1lepFromW}^{CR,~MET~bin}/M_{1lepFromW}^{CR,~MET>250},~(\\%%)$ & $M_{1lepFromW}^{SR,~MET~bin},~(\\%%)$ & $M_{1lepFromW}^{SR,~MET~bin}/M_{1lepFromW}^{CR,~MET~bin},~(\\%%)$ & $N_{1lepFromW,estimate}^{SR},~(\\%%)$ ");
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n");

    
    //
    // Get yields, begin calculation for this cateogry
    //


    //
    // SR, category bin 
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR_1lepFromW, recoClassyType, nominal_sys );
    
    h_temp = (TH1D*)f_SR->Get(hName);
    if(!h_temp) cout << "BAD SR CATEGORY BIN HISTO: " << hName << endl;

    double SR_bin_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
    double SR_bin_error = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
    
    if(doRescale){
      SR_bin_error *= rescale;
      SR_bin_yield *= rescale;
    }
    
    
    //
    // CR, mc, category bin
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_1lepFromW, recoClassyType, nominal_sys );

    h_temp = (TH1D*)f_CR->Get(hName);
    if(!h_temp) cout << "BAD CR category bin HISTO: " << hName << endl;
    
    double CR_bin_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
    double CR_bin_error = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
    
    if(doRescale){
      CR_bin_error *= rescale;
      CR_bin_yield *= rescale;
    }
    
    
    //
    // CR, mc, 1lepFromW MET>250
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_1lepFromW, recoClassyType, nominal_sys );
    
    h_temp = (TH1D*)f_CR->Get(hName);
    if(!h_temp) cout << "BAD MC CR metIncl bin HISTO: " << hName << endl;
    
    double CR_metIncl_1lepFromW_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
    double CR_metIncl_1lepFromW_error = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
    int CR_metIncl_1lepFromW_nEntries = h_temp->GetEntries();

    if(doRescale){
      CR_metIncl_1lepFromW_error *= rescale;
      CR_metIncl_1lepFromW_yield *= rescale;
    }


    //
    // CR, mc, Incl MET>250
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_Incl, recoClassyType, nominal_sys );
    
    h_temp = (TH1D*)f_CR->Get(hName);
    if(!h_temp) cout << "BAD MC CR metIncl bin HISTO: " << hName << endl;
    
    double CR_metIncl_incl_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
    double CR_metIncl_incl_error = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
    
    if(doRescale){
      CR_metIncl_incl_error *= rescale;
      CR_metIncl_incl_yield *= rescale;
    }
    

    //
    // CR, mc, non-1lepFromW, MET>250
    //
    double CR_metIncl_non1lepFromW_yield = CR_metIncl_incl_yield - CR_metIncl_1lepFromW_yield;
    double CR_metIncl_non1lepFromW_error = sqrt( pow(CR_metIncl_incl_error,2)-pow(CR_metIncl_1lepFromW_error,2) ); // totErr^2 = 1lepErr^2 + non1lepErr^2


    //
    // CR, data, MET>250
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_data_CR, recoClassyType, nominal_sys );
    
    h_temp = (TH1D*)f_data_CR->Get(hName);
    if(!h_temp) cout << "BAD DATA CR MET>250 HISTO: " << hName << endl;
    
    double CR_data_metIncl_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
    double CR_data_metIncl_error = sqrt( CR_data_metIncl_yield );

    if(doRescale){
      CR_data_metIncl_error *= rescale;
      CR_data_metIncl_yield *= rescale;
    }
    

    //
    // CR, data, 1lepFromW, MET>250
    //
    double CR_data_1lepFromW_metIncl_yield = CR_data_metIncl_yield - CR_metIncl_non1lepFromW_yield;
    double CR_data_1lepFromW_metIncl_error = sqrt( pow(CR_data_metIncl_error,2) + pow(CR_metIncl_non1lepFromW_error,2) );



    // Transfer Factor SR/CR
    double tf_met = 1.0;
    double tf_met_err = 0.0;
    double tf_met_mc_stats = 0.0;
    
    // Transfer Factor SR_bin/SR_cr2sr
    double tf_bTag = 1.0;
    double tf_bTag_err = 0.0;
    double tf_bTag_mc_stats = 0.0;

    // Signal Region Estimate
    double sr_estimate = 0.0;
    double sr_estimate_error = 0.0;
    double sr_estimate_error_mc_stats = 0.0;


    if(oneTF){

      // Transfer Factor SR/CR
      if(CR_bin_yield>0.0){
	tf_bTag = SR_bin_yield/CR_bin_yield;
	tf_bTag_err = tf_bTag*sqrt( pow(CR_bin_error/CR_bin_yield, 2) + pow(SR_bin_error/SR_bin_yield, 2) ); // avoid double counting mc stats
	tf_bTag_mc_stats = tf_bTag_err;
      }
    
      // Signal Region Estimate
      sr_estimate = CR_data_1lepFromW_metIncl_yield*tf_bTag;
      sr_estimate_error = sr_estimate*sqrt( pow(CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield, 2) + pow(tf_bTag_err/tf_bTag, 2) );
      sr_estimate_error_mc_stats = sr_estimate*sqrt( pow(tf_bTag_err/tf_bTag, 2) );


    }
    else{

      // Transfer Factor SR/CR
      if(CR_metIncl_1lepFromW_yield>0.0){
	tf_met = CR_bin_yield/CR_metIncl_1lepFromW_yield;
	tf_met_err = sqrt( tf_met*(1-tf_met)/CR_metIncl_1lepFromW_nEntries ); // binomial errors since CR_bin_yield is subset of CR_metIncl_1lepFromW_yield
	tf_met_mc_stats = tf_met_err;
      }
    
      // Transfer Factor SR_bin/SR_cr2sr
      if(CR_bin_yield>0.0){
	tf_bTag = SR_bin_yield/CR_bin_yield;
	tf_bTag_err = tf_bTag*sqrt( pow( SR_bin_error/SR_bin_yield, 2 ) ); // avoid double counting mc stats
	tf_bTag_mc_stats = tf_bTag_err;
      }

      //
      // Signal Region Estimate
      //
      sr_estimate = CR_data_1lepFromW_metIncl_yield*tf_met*tf_bTag;
      sr_estimate_error = sr_estimate*sqrt( pow(CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield, 2) + pow(tf_met_err/tf_met, 2) + pow(tf_bTag_err/tf_bTag, 2) );
      sr_estimate_error_mc_stats = sr_estimate*sqrt( pow(tf_met_err/tf_met, 2) + pow(tf_bTag_err/tf_bTag, 2) );

    }


    
    //
    // Fill histograms for limit setting
    //
    h_SR[0]->SetBinContent( iSR+1, sr_estimate );
    h_SR[0]->SetBinError( iSR+1, sr_estimate_error );
    
    
    //
    // Uncertainty File, Nominal Values
    //
    if(oneTF){
      fprintf(uncFile, "Nominal & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", CR_data_metIncl_yield, CR_data_1lepFromW_metIncl_yield, CR_metIncl_1lepFromW_yield, SR_bin_yield, tf_bTag, sr_estimate );
    }
    else{
      fprintf(uncFile, "Nominal & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", CR_data_metIncl_yield, CR_data_1lepFromW_metIncl_yield, CR_metIncl_1lepFromW_yield, CR_bin_yield, tf_met, SR_bin_yield, tf_bTag, sr_estimate );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n"); 
 

    

    //
    // Data Stats
    //
    double CR_data_metIncl_yield_dataStatsUp = CR_data_metIncl_yield + CR_data_metIncl_error;
    double CR_data_1lepFromW_metIncl_yield_dataStatsUp = CR_data_metIncl_yield_dataStatsUp - CR_metIncl_non1lepFromW_yield;
    
    double sr_estimate_dataStats_up = CR_data_1lepFromW_metIncl_yield_dataStatsUp*tf_met*tf_bTag;
     
    
    if(oneTF){
      fprintf(uncFile, "Data Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield_dataStatsUp, (100*(CR_data_metIncl_yield_dataStatsUp-CR_data_metIncl_yield)/CR_data_metIncl_yield), CR_data_1lepFromW_metIncl_yield_dataStatsUp, (100*(CR_data_1lepFromW_metIncl_yield_dataStatsUp-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield, 0.0, SR_bin_yield, 0.0, tf_bTag, 0.0, sr_estimate_dataStats_up, (100*(sr_estimate_dataStats_up-sr_estimate)/sr_estimate) );
    }
    else{
      fprintf(uncFile, "Data Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield_dataStatsUp, (100*(CR_data_metIncl_yield_dataStatsUp-CR_data_metIncl_yield)/CR_data_metIncl_yield), CR_data_1lepFromW_metIncl_yield_dataStatsUp, (100*(CR_data_1lepFromW_metIncl_yield_dataStatsUp-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield, 0.0, CR_bin_yield, 0.0, tf_met, 0.0, SR_bin_yield, 0.0, tf_bTag, 0.0, sr_estimate_dataStats_up, (100*(sr_estimate_dataStats_up-sr_estimate)/sr_estimate) );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 


    double CR_data_metIncl_yield_dataStatsDn = CR_data_metIncl_yield - CR_data_metIncl_error;
    double CR_data_1lepFromW_metIncl_yield_dataStatsDn = CR_data_metIncl_yield_dataStatsDn - CR_metIncl_non1lepFromW_yield;
    
    double sr_estimate_dataStats_dn = CR_data_1lepFromW_metIncl_yield_dataStatsDn*tf_met*tf_bTag;


    if(oneTF){
      fprintf(uncFile, "Data Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield_dataStatsDn, (100*(CR_data_metIncl_yield_dataStatsDn-CR_data_metIncl_yield)/CR_data_metIncl_yield), CR_data_1lepFromW_metIncl_yield_dataStatsDn, (100*(CR_data_1lepFromW_metIncl_yield_dataStatsDn-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield, 0.0, SR_bin_yield, 0.0, tf_bTag, 0.0, sr_estimate_dataStats_dn, (100*(sr_estimate_dataStats_dn-sr_estimate)/sr_estimate) );
    }
    else{
      fprintf(uncFile, "Data Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield_dataStatsDn, (100*(CR_data_metIncl_yield_dataStatsDn-CR_data_metIncl_yield)/CR_data_metIncl_yield), CR_data_1lepFromW_metIncl_yield_dataStatsDn, (100*(CR_data_1lepFromW_metIncl_yield_dataStatsDn-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield, 0.0, CR_bin_yield, 0.0, tf_met, 0.0, SR_bin_yield, 0.0, tf_bTag, 0.0, sr_estimate_dataStats_dn, (100*(sr_estimate_dataStats_dn-sr_estimate)/sr_estimate) );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \\hline \n"); 

   

    //
    // Calc Min/Max uncertainty for data stats
    //
    uncMax_cr_data[0] = std::max( uncMax_cr_data[0], (100*CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield) );
    uncMin_cr_data[0] = std::min( uncMin_cr_data[0], (100*CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield) );
    uncMax_tf_met[0] = std::max( uncMax_tf_met[0], 0.0 );
    uncMin_tf_met[0] = std::min( uncMin_tf_met[0], 0.0 );
    uncMax_tf_bTag[0] = std::max( uncMax_tf_bTag[0], 0.0 );
    uncMin_tf_bTag[0] = std::min( uncMin_tf_bTag[0], 0.0 );
    uncMax_sr_estimate[0] = std::max( uncMax_sr_estimate[0], fabs((100*(sr_estimate_dataStats_up-sr_estimate)/sr_estimate)) );
    uncMin_sr_estimate[0] = std::min( uncMin_sr_estimate[0], fabs((100*(sr_estimate_dataStats_dn-sr_estimate)/sr_estimate)) );
    

    
    //
    // Uncertainty File, MC Stats Up
    //

    double CR_data_1lepFromW_metIncl_yield_mcStatsUp = (CR_data_metIncl_yield - (CR_metIncl_non1lepFromW_yield+CR_metIncl_non1lepFromW_error));
    
    double sr_estimate_mcStats_up = CR_data_1lepFromW_metIncl_yield_mcStatsUp*(tf_met+tf_met_mc_stats)*(tf_bTag+tf_bTag_mc_stats);

    if(oneTF){
      fprintf(uncFile, "MC Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_mcStatsUp, (100.0*(CR_data_1lepFromW_metIncl_yield_mcStatsUp-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), (CR_metIncl_1lepFromW_yield+CR_metIncl_1lepFromW_error), (100*(CR_metIncl_1lepFromW_error/CR_metIncl_1lepFromW_yield)), (SR_bin_yield+SR_bin_error), (100.0*(SR_bin_error/SR_bin_yield)), (tf_bTag+tf_bTag_mc_stats), (100*(tf_bTag_mc_stats/tf_bTag)), sr_estimate_mcStats_up, (100*(sr_estimate_mcStats_up-sr_estimate)/sr_estimate) );
    }
    else{
      fprintf(uncFile, "MC Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_dataStatsUp, (100*(CR_data_1lepFromW_metIncl_yield_dataStatsUp-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), (CR_metIncl_1lepFromW_yield+CR_metIncl_1lepFromW_error), (100*(CR_metIncl_1lepFromW_error/CR_metIncl_1lepFromW_yield)), (CR_bin_yield+CR_bin_error), (100.0*(CR_bin_error/CR_bin_yield)), (tf_met+tf_met_mc_stats), (100.0*(tf_met_mc_stats/tf_met)), (SR_bin_yield+SR_bin_error), (100.0*(SR_bin_error/SR_bin_yield)), (tf_bTag+tf_bTag_mc_stats), (100.0*(tf_bTag_mc_stats/tf_bTag)), sr_estimate_mcStats_up, (100*(sr_estimate_mcStats_up-sr_estimate)/sr_estimate) );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 


    double CR_data_1lepFromW_metIncl_yield_mcStatsDn = (CR_data_metIncl_yield - (CR_metIncl_non1lepFromW_yield-CR_metIncl_non1lepFromW_error));
    
    double sr_estimate_mcStats_dn = CR_data_1lepFromW_metIncl_yield_mcStatsDn*(tf_met+tf_met_mc_stats)*(tf_bTag+tf_bTag_mc_stats);

    if(oneTF){
      fprintf(uncFile, "MC Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_mcStatsDn, (100.0*(CR_data_1lepFromW_metIncl_yield_mcStatsDn-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), (CR_metIncl_1lepFromW_yield+CR_metIncl_1lepFromW_error), (100*(CR_metIncl_1lepFromW_error/CR_metIncl_1lepFromW_yield)), (SR_bin_yield+SR_bin_error), (100.0*(SR_bin_error/SR_bin_yield)), (tf_bTag+tf_bTag_mc_stats), (100*(tf_bTag_mc_stats/tf_bTag)), sr_estimate_mcStats_dn, (100*(sr_estimate_mcStats_dn-sr_estimate)/sr_estimate) );
    }
    else{
      fprintf(uncFile, "MC Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_dataStatsDn, (100*(CR_data_1lepFromW_metIncl_yield_dataStatsDn-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), (CR_metIncl_1lepFromW_yield+CR_metIncl_1lepFromW_error), (100*(CR_metIncl_1lepFromW_error/CR_metIncl_1lepFromW_yield)), (CR_bin_yield+CR_bin_error), (100.0*(CR_bin_error/CR_bin_yield)), (tf_met+tf_met_mc_stats), (100.0*(tf_met_mc_stats/tf_met)), (SR_bin_yield+SR_bin_error), (100.0*(SR_bin_error/SR_bin_yield)), (tf_bTag+tf_bTag_mc_stats), (100.0*(tf_bTag_mc_stats/tf_bTag)), sr_estimate_mcStats_dn, (100*(sr_estimate_mcStats_dn-sr_estimate)/sr_estimate) );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 

    fprintf(uncFile, "\\hline \\hline \n");
    
    
    //
    // Calc Min/Max for MC Stats
    //
    uncMax_cr_data[1] = std::max( uncMax_cr_data[1], 0.0 );
    uncMin_cr_data[1] = std::min( uncMin_cr_data[1], 0.0 );
    uncMax_tf_met[1] = std::max( uncMax_tf_met[1], (100*tf_met_mc_stats/tf_met) );
    uncMin_tf_met[1] = std::min( uncMin_tf_met[1], (100*tf_met_mc_stats/tf_met) );
    uncMax_tf_bTag[1] = std::max( uncMax_tf_bTag[1], (100*tf_bTag_mc_stats/tf_bTag) );
    uncMin_tf_bTag[1] = std::min( uncMin_tf_bTag[1], (100*tf_bTag_mc_stats/tf_bTag) );
    uncMax_sr_estimate[1] = std::max( uncMax_sr_estimate[1], fabs((100*(sr_estimate_mcStats_up-sr_estimate)/sr_estimate)) );
    uncMin_sr_estimate[1] = std::min( uncMin_sr_estimate[1], fabs((100*(sr_estimate_mcStats_dn-sr_estimate)/sr_estimate)) );
    


  
    //
    // Loop over systematics
    //
    int unique_sys = 2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      
      //
      // SR, category bin, up
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR_1lepFromW, recoClassyType, systematicList[iSys] );

      h_temp = (TH1D*)f_SR->Get(hName);
      if(!h_temp) cout << "BAD SR CATEGORY BIN UP HISTO: " << hName << endl;
      
      double SR_bin_yield_up = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      double SR_bin_error_up = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	SR_bin_error_up *= rescale;
	SR_bin_yield_up *= rescale;
      }
      
      
      //
      // CR, category bin, up
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_1lepFromW, recoClassyType, systematicList[iSys] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR Bin UP HISTO: " << hName << endl;
    
      double CR_bin_yield_up = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      double CR_bin_error_up = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	CR_bin_error_up *= rescale;
	CR_bin_yield_up *= rescale;
      }
      

      //
      // CR, MC, Incl met>250, up
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_Incl, recoClassyType, systematicList[iSys] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR metIncl, incl genClassy, UP MC HISTO: " << hName << endl;
    
      double CR_metIncl_incl_yield_up = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      double CR_metIncl_incl_error_up = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	CR_metIncl_incl_error_up *= rescale;
	CR_metIncl_incl_yield_up *= rescale;
      }


      //
      // CR, MC, 1lepFromW met>250, up
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_1lepFromW, recoClassyType, systematicList[iSys] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR metIncl, 1lepFRomW UP MC HISTO: " << hName << endl;
    
      double CR_metIncl_1lepFromW_yield_up = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      double CR_metIncl_1lepFromW_error_up = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      int CR_metIncl_1lepFromW_nEntries_up = h_temp->GetEntries();

      if(doRescale){
	CR_metIncl_1lepFromW_error_up *= rescale;
	CR_metIncl_1lepFromW_yield_up *= rescale;
      }


      //
      // CR, MC, non-1lepFromW, MET>250, up
      //
      double CR_metIncl_non1lepFromW_yield_up = CR_metIncl_incl_yield_up - CR_metIncl_1lepFromW_yield_up;
      double CR_metIncl_non1lepFromW_error_up_mcStatErr = sqrt( pow(CR_metIncl_incl_error_up,2)-pow(CR_metIncl_1lepFromW_error_up,2) ); // totErr^2 = 1lepErr^2 + non1lepErr^2
      


      //
      // CR, data, 1lepFromW, MET>250
      //
      double CR_data_1lepFromW_metIncl_yield_up = CR_data_metIncl_yield - CR_metIncl_non1lepFromW_yield_up;
      double CR_data_1lepFromW_metIncl_error_up_mcStatErr = sqrt( pow(CR_metIncl_non1lepFromW_error_up_mcStatErr,2) );
      
      
      // Transfer Factor SR/CR, up
      double tf_met_up = 1.0;
      double tf_met_up_mcStatErr = 0.0;
    
      // Transfer Factor SR_bin/SR_cr2sr
      double tf_bTag_up = 1.0;
      double tf_bTag_up_mcStatErr = 0.0;

      // Signal Region Estimate
      double sr_estimate_up = 0.0;
      double sr_estimate_up_mcStatErr = 0.0;


      if(oneTF){
	
	// Transfer Factor SR/CR
	if(CR_bin_yield_up>0.0){
	  tf_bTag_up = SR_bin_yield_up/CR_bin_yield_up;
	  tf_bTag_up_mcStatErr = tf_bTag_up*sqrt( pow(CR_bin_error_up/CR_bin_yield_up, 2) + pow(SR_bin_error_up/SR_bin_yield_up, 2) ); // avoid double counting mc stats
	}
	
	// Signal Region Estimate
	sr_estimate_up = CR_data_1lepFromW_metIncl_yield_up*tf_bTag_up;
	sr_estimate_up_mcStatErr = sr_estimate_up*sqrt( pow(CR_data_1lepFromW_metIncl_error_up_mcStatErr/CR_data_1lepFromW_metIncl_yield_up, 2) + pow(tf_bTag_up_mcStatErr/tf_bTag_up, 2) );
	

      }
      else{
	
	// Transfer Factor SR/CR
	if(CR_metIncl_1lepFromW_yield_up>0.0){
	  tf_met_up = CR_bin_yield_up/CR_metIncl_1lepFromW_yield_up;
	  tf_met_up_mcStatErr = sqrt( tf_met_up*(1-tf_met_up)/CR_metIncl_1lepFromW_nEntries_up ); // binomial errors since CR_bin_yield is subset of CR_metIncl_1lepFromW_yield
	}
	
	// Transfer Factor SR_bin/SR_cr2sr
	if(CR_bin_yield_up>0.0){
	  tf_bTag_up = SR_bin_yield_up/CR_bin_yield_up;
	  tf_bTag_up_mcStatErr = tf_bTag_up*sqrt( pow( SR_bin_error_up/SR_bin_yield_up, 2 ) ); // avoid double counting mc stats
	}
	
	//
	// Signal Region Estimate
	//
	sr_estimate_up = CR_data_1lepFromW_metIncl_yield_up*tf_met_up*tf_bTag_up;
	sr_estimate_up_mcStatErr = sr_estimate_up*sqrt( pow(tf_met_up_mcStatErr/tf_met_up, 2) + pow(tf_bTag_up_mcStatErr/tf_bTag_up, 2) );
	
      }
      
      
      if(oneTF){
	fprintf(uncFile, "%s & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",systematicList[iSys].tex.c_str(), CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_up, (100.0*(CR_data_1lepFromW_metIncl_yield_up-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield_up, (100*(CR_metIncl_1lepFromW_yield_up-CR_metIncl_1lepFromW_yield)/CR_metIncl_1lepFromW_yield), SR_bin_yield_up, (100.0*(SR_bin_yield_up-SR_bin_yield)/SR_bin_yield), tf_bTag_up, (100*(tf_bTag_up-tf_bTag)/tf_bTag), sr_estimate_up, (100*(sr_estimate_up-sr_estimate)/sr_estimate) );
      }
      else{
	fprintf(uncFile, "%s & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",systematicList[iSys].tex.c_str(), CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_up, (100*(CR_data_1lepFromW_metIncl_yield_up-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield_up, (100*(CR_metIncl_1lepFromW_yield_up-CR_metIncl_1lepFromW_yield)/CR_metIncl_1lepFromW_yield), CR_bin_yield_up, (100.0*(CR_bin_yield_up-CR_bin_yield)/CR_bin_yield), tf_met_up, (100.0*(tf_met_up-tf_met)/tf_met), SR_bin_yield_up, (100.0*(SR_bin_yield_up-SR_bin_yield)/SR_bin_yield), tf_bTag_up, (100.0*(tf_bTag_up-tf_bTag)/tf_bTag), sr_estimate_up, (100*(sr_estimate_up-sr_estimate)/sr_estimate) );
      }
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \n"); 



      //
      // SR, category bin, dn
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR_1lepFromW, recoClassyType, systematicList[iSys] );

      h_temp = (TH1D*)f_SR->Get(hName);
      if(!h_temp) cout << "BAD SR CATEGORY BIN DN HISTO: " << hName << endl;
      
      double SR_bin_yield_dn = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      double SR_bin_error_dn = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	SR_bin_error_dn *= rescale;
	SR_bin_yield_dn *= rescale;
      }
      
      
      //
      // CR, category bin, dn
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_1lepFromW, recoClassyType, systematicList[iSys] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR Bin DN HISTO: " << hName << endl;
    
      double CR_bin_yield_dn = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      double CR_bin_error_dn = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	CR_bin_error_dn *= rescale;
	CR_bin_yield_dn *= rescale;
      }
      

      //
      // CR, MC, Incl met>250, dn
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_Incl, recoClassyType, systematicList[iSys] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR metIncl, incl genClassy, DN MC HISTO: " << hName << endl;
    
      double CR_metIncl_incl_yield_dn = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      double CR_metIncl_incl_error_dn = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	CR_metIncl_incl_error_dn *= rescale;
	CR_metIncl_incl_yield_dn *= rescale;
      }


      //
      // CR, MC, 1lepFromW met>250, dn
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR_1lepFromW, recoClassyType, systematicList[iSys] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR metIncl, 1lepFRomW DN MC HISTO: " << hName << endl;
    
      double CR_metIncl_1lepFromW_yield_dn = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      double CR_metIncl_1lepFromW_error_dn = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr_cats[iSR].label.c_str() ) );
      int CR_metIncl_1lepFromW_nEntries_dn = h_temp->GetEntries();

      if(doRescale){
	CR_metIncl_1lepFromW_error_dn *= rescale;
	CR_metIncl_1lepFromW_yield_dn *= rescale;
      }


      //
      // CR, MC, non-1lepFromW, MET>250, dn
      //
      double CR_metIncl_non1lepFromW_yield_dn = CR_metIncl_incl_yield_dn - CR_metIncl_1lepFromW_yield_dn;
      double CR_metIncl_non1lepFromW_error_dn_mcStatErr = sqrt( pow(CR_metIncl_incl_error_dn,2)-pow(CR_metIncl_1lepFromW_error_dn,2) ); // totErr^2 = 1lepErr^2 + non1lepErr^2
      


      //
      // CR, data, 1lepFromW, MET>250
      //
      double CR_data_1lepFromW_metIncl_yield_dn = CR_data_metIncl_yield - CR_metIncl_non1lepFromW_yield_dn;
      double CR_data_1lepFromW_metIncl_error_dn_mcStatErr = sqrt( pow(CR_metIncl_non1lepFromW_error_dn_mcStatErr,2) );
            
      // Transfer Factor SR/CR, dn
      double tf_met_dn = 1.0;
      double tf_met_dn_mcStatErr = 0.0;
    
      // Transfer Factor SR_bin/SR_cr2sr
      double tf_bTag_dn = 1.0;
      double tf_bTag_dn_mcStatErr = 0.0;

      // Signal Region Estimate
      double sr_estimate_dn = 0.0;
      double sr_estimate_dn_mcStatErr = 0.0;


      if(oneTF){
	
	// Transfer Factor SR/CR
	if(CR_bin_yield_dn>0.0){
	  tf_bTag_dn = SR_bin_yield_dn/CR_bin_yield_dn;
	  tf_bTag_dn_mcStatErr = tf_bTag_dn*sqrt( pow(CR_bin_error_dn/CR_bin_yield_dn, 2) + pow(SR_bin_error_dn/SR_bin_yield_dn, 2) ); 
	}
	
	// Signal Region Estimate
	sr_estimate_dn = CR_data_1lepFromW_metIncl_yield_dn*tf_bTag_dn;
	sr_estimate_dn_mcStatErr = sr_estimate_dn*sqrt(  pow(CR_data_1lepFromW_metIncl_error_dn_mcStatErr/CR_data_1lepFromW_metIncl_yield_dn,2) + pow(tf_bTag_dn_mcStatErr/tf_bTag_dn, 2) );
	

      }
      else{
	
	// Transfer Factor SR/CR
	if(CR_metIncl_1lepFromW_yield_dn>0.0){
	  tf_met_dn = CR_bin_yield_dn/CR_metIncl_1lepFromW_yield_dn;
	  tf_met_dn_mcStatErr = sqrt( tf_met_dn*(1-tf_met_dn)/CR_metIncl_1lepFromW_nEntries_dn ); // binomial errors since CR_bin_yield is subset of CR_metIncl_1lepFromW_yield
	}
	
	// Transfer Factor SR_bin/SR_cr2sr
	if(CR_bin_yield_dn>0.0){
	  tf_bTag_dn = SR_bin_yield_dn/CR_bin_yield_dn;
	  tf_bTag_dn_mcStatErr = tf_bTag_dn*sqrt( pow( SR_bin_error_dn/SR_bin_yield_dn, 2 ) ); // avoid double counting mc stats
	}
	
	//
	// Signal Region Estimate
	//
	sr_estimate_dn = CR_data_1lepFromW_metIncl_yield_dn*tf_met_dn*tf_bTag_dn;
	sr_estimate_dn_mcStatErr = sr_estimate_dn*sqrt(  pow(CR_data_1lepFromW_metIncl_error_dn_mcStatErr/CR_data_1lepFromW_metIncl_yield_dn,2) + pow(tf_met_dn_mcStatErr/tf_met_dn, 2) + pow(tf_bTag_dn_mcStatErr/tf_bTag_dn, 2) );
	
      }
      
      
      if(oneTF){
	fprintf(uncFile, "%s & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",systematicList[iSys].tex.c_str(), CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_dn, (100.0*(CR_data_1lepFromW_metIncl_yield_dn-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield_dn, (100*(CR_metIncl_1lepFromW_yield_dn-CR_metIncl_1lepFromW_yield)/CR_metIncl_1lepFromW_yield), SR_bin_yield_dn, (100.0*(SR_bin_yield_dn-SR_bin_yield)/SR_bin_yield), tf_bTag_dn, (100*(tf_bTag_dn-tf_bTag)/tf_bTag), sr_estimate_dn, (100*(sr_estimate_dn-sr_estimate)/sr_estimate) );
      }
      else{
	fprintf(uncFile, "%s & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",systematicList[iSys].tex.c_str(), CR_data_metIncl_yield, 0.0, CR_data_1lepFromW_metIncl_yield_dn, (100*(CR_data_1lepFromW_metIncl_yield_dn-CR_data_1lepFromW_metIncl_yield)/CR_data_1lepFromW_metIncl_yield), CR_metIncl_1lepFromW_yield_dn, (100*(CR_metIncl_1lepFromW_yield_dn-CR_metIncl_1lepFromW_yield)/CR_metIncl_1lepFromW_yield), CR_bin_yield_dn, (100.0*(CR_bin_yield_dn-CR_bin_yield)/CR_bin_yield), tf_met_dn, (100.0*(tf_met_dn-tf_met)/tf_met), SR_bin_yield_dn, (100.0*(SR_bin_yield_dn-SR_bin_yield)/SR_bin_yield), tf_bTag_dn, (100.0*(tf_bTag_dn-tf_bTag)/tf_bTag), sr_estimate_dn, (100*(sr_estimate_dn-sr_estimate)/sr_estimate) );
      }
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n"); 



      
      //
      // Diff in TF met
      //
      double tf_met_max_diff = std::max( fabs(tf_met_up-tf_met), fabs(tf_met_dn-tf_met) );
      double tf_met_max_diff_sq = pow( tf_met_max_diff, 2 );
      tf_met_err = pow( tf_met_err, 2 );
      tf_met_err += tf_met_max_diff_sq;
      tf_met_err = sqrt(tf_met_err);


      //
      // Diff in TF SR bin
      //
      double tf_bTag_max_diff = std::max( fabs(tf_bTag_up-tf_bTag), fabs(tf_bTag_dn-tf_bTag) );
      double tf_bTag_max_diff_sq = pow( tf_bTag_max_diff, 2 );
      tf_bTag_err = pow( tf_bTag_err, 2 );
      tf_bTag_err += tf_bTag_max_diff_sq;
      tf_bTag_err = sqrt(tf_bTag_err);


      //
      // Diff in SR estimate
      //
      double est_max_diff = std::max( fabs(sr_estimate_up-sr_estimate), fabs(sr_estimate_dn-sr_estimate) );
      double est_max_diff_sq = pow( est_max_diff, 2 );
      sr_estimate_error = pow( sr_estimate_error, 2 );
      sr_estimate_error += est_max_diff_sq;
      sr_estimate_error = sqrt(sr_estimate_error);

      
      //
      // Fill histograms for limit setting
      //
      h_SR[iSys]->SetBinContent( iSR+1, sr_estimate_up );
      h_SR[iSys]->SetBinError( iSR+1, sr_estimate_up_mcStatErr );
      h_SR[iSys+1]->SetBinContent( iSR+1, sr_estimate_dn );
      h_SR[iSys+1]->SetBinError( iSR+1, sr_estimate_dn_mcStatErr );
    
      
      
      //
      // Fill Min/Max Uncertainty
      //
      uncMax_cr_data[unique_sys] = std::max( uncMax_cr_data[unique_sys], 0.0 );
      uncMin_cr_data[unique_sys] = std::min( uncMin_cr_data[unique_sys], 0.0 );
      uncMax_tf_met[unique_sys] = std::max( uncMax_tf_met[unique_sys], (100*tf_met_max_diff/tf_met) );
      uncMin_tf_met[unique_sys] = std::min( uncMin_tf_met[unique_sys], (100*tf_met_max_diff/tf_met) );
      uncMax_tf_bTag[unique_sys] = std::max( uncMax_tf_bTag[unique_sys], (100*tf_bTag_max_diff/tf_bTag) );
      uncMin_tf_bTag[unique_sys] = std::min( uncMin_tf_bTag[unique_sys], (100*tf_bTag_max_diff/tf_bTag) );
      uncMax_sr_estimate[unique_sys] = std::max( uncMax_sr_estimate[unique_sys], (100*est_max_diff/sr_estimate) );
      uncMin_sr_estimate[unique_sys] = std::min( uncMin_sr_estimate[unique_sys], (100*est_max_diff/sr_estimate) );

      
      //
      // Increment unique sys counter
      //
      unique_sys++;


    } // end loop over systematics

    
    //
    // Total Uncertainty
    //
    if(oneTF){
      fprintf(uncFile, "\\hline \n");
      fprintf(uncFile, "Total Uncertainties & %.2f\\%% & %.2f\\%% & & & %.2f\\%% & %.2f\\%% ", (100*CR_data_metIncl_error/CR_data_metIncl_yield), (100*CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield), (100*tf_bTag_err/tf_bTag), (100*sr_estimate_error/sr_estimate) );
    }
    else{
      fprintf(uncFile, "\\hline \n");
      fprintf(uncFile, "Total Uncertainties & %.2f\\%% & %.2f\\%% & & & %.2f\\%% & & %.2f\\%% & %.2f\\%% ",(100*CR_data_metIncl_error/CR_data_metIncl_yield), (100*CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield), (100*tf_met_err/tf_met), (100*tf_bTag_err/tf_bTag), (100*sr_estimate_error/sr_estimate) );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");

    //
    // Formatting for uncertainty tex file
    //
    fprintf(uncFile, "\\end{tabular} \n");
    fprintf(uncFile, "} \n");
    fprintf(uncFile, "\\end{table} \n");
    fprintf(uncFile, "\n \n");
    fprintf(uncFile, "\\pagebreak");
    fprintf(uncFile, "\n \n");
    
    
    //
    // Fill Min/Max Uncertainty
    //
    uncMax_cr_data[nSys_unique-1] = std::max( uncMax_cr_data[nSys_unique-1], (100*CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield) );
    uncMin_cr_data[nSys_unique-1] = std::min( uncMin_cr_data[nSys_unique-1], (100*CR_data_1lepFromW_metIncl_error/CR_data_1lepFromW_metIncl_yield) );
    uncMax_tf_met[nSys_unique-1] = std::max( uncMax_tf_met[nSys_unique-1], (100*tf_met_err/tf_met) );
    uncMin_tf_met[nSys_unique-1] = std::min( uncMin_tf_met[nSys_unique-1], (100*tf_met_err/tf_met) );
    uncMax_tf_bTag[nSys_unique-1] = std::max( uncMax_tf_bTag[nSys_unique-1], (100*tf_bTag_err/tf_bTag) );
    uncMin_tf_bTag[nSys_unique-1] = std::min( uncMin_tf_bTag[nSys_unique-1], (100*tf_bTag_err/tf_bTag) );
    uncMax_sr_estimate[nSys_unique-1] = std::max( uncMax_sr_estimate[nSys_unique-1], (100*sr_estimate_error/sr_estimate) );
    uncMin_sr_estimate[nSys_unique-1] = std::min( uncMin_sr_estimate[nSys_unique-1], (100*sr_estimate_error/sr_estimate) );
    
    
    if(oneTF){
      fprintf(yFile, "%.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f " , CR_data_metIncl_yield, CR_data_metIncl_error, CR_data_1lepFromW_metIncl_yield, CR_data_1lepFromW_metIncl_error, tf_bTag, tf_bTag_err, sr_estimate, sr_estimate_error);
    }
    else{
      fprintf(yFile, "%.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f " , CR_data_metIncl_yield, CR_data_metIncl_error, CR_data_1lepFromW_metIncl_yield, CR_data_1lepFromW_metIncl_error, tf_met, tf_met_err, tf_bTag, tf_bTag_err, sr_estimate, sr_estimate_error);
    }
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

    

  } // end loop over signal regions

  

  //
  // Summary table of uncertainties
  //
  if(oneTF){
    
    fprintf(uncFileSummary, "Data Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data[0], uncMax_cr_data[0], uncMin_tf_bTag[0], uncMax_tf_bTag[0], uncMin_sr_estimate[0], uncMax_sr_estimate[0]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \n");
    
    fprintf(uncFileSummary, "MC Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data[1], uncMax_cr_data[1], uncMin_tf_bTag[1], uncMax_tf_bTag[1], uncMin_sr_estimate[1], uncMax_sr_estimate[1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    
    int unique_sys = 2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      fprintf(uncFileSummary, "%s & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", sys_name.Data(), uncMin_cr_data[unique_sys], uncMax_cr_data[unique_sys], uncMin_tf_bTag[unique_sys], uncMax_tf_bTag[unique_sys], uncMin_sr_estimate[unique_sys], uncMax_sr_estimate[unique_sys]);
      fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \n");
      unique_sys++;
    }

    fprintf(uncFileSummary, "\\hline \n");
    fprintf(uncFileSummary, "Total & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data[nSys_unique-1], uncMax_cr_data[nSys_unique-1], uncMin_tf_bTag[nSys_unique-1], uncMax_tf_bTag[nSys_unique-1], uncMin_sr_estimate[nSys_unique-1], uncMax_sr_estimate[nSys_unique-1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");

  }
  else{

    fprintf(uncFileSummary, "Data Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data[0], uncMax_cr_data[0], uncMin_tf_met[0], uncMax_tf_met[0], uncMin_tf_bTag[0], uncMax_tf_bTag[0], uncMin_sr_estimate[0], uncMax_sr_estimate[0]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \n");
    
    fprintf(uncFileSummary, "MC Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data[1], uncMax_cr_data[1], uncMin_tf_met[1], uncMax_tf_met[1], uncMin_tf_bTag[1], uncMax_tf_bTag[1], uncMin_sr_estimate[1], uncMax_sr_estimate[1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    
    int unique_sys = 2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      fprintf(uncFileSummary, "%s & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", sys_name.Data(), uncMin_cr_data[unique_sys], uncMax_cr_data[unique_sys], uncMin_tf_met[unique_sys], uncMax_tf_met[unique_sys], uncMin_tf_bTag[unique_sys], uncMax_tf_bTag[unique_sys], uncMin_sr_estimate[unique_sys], uncMax_sr_estimate[unique_sys]);
      fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \n");
      unique_sys++;
    }
    
    fprintf(uncFileSummary, "\\hline \n");
    fprintf(uncFileSummary, "Total & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data[nSys_unique-1], uncMax_cr_data[nSys_unique-1], uncMin_tf_met[nSys_unique-1], uncMax_tf_met[nSys_unique-1], uncMin_tf_bTag[nSys_unique-1], uncMax_tf_bTag[nSys_unique-1], uncMin_sr_estimate[nSys_unique-1], uncMax_sr_estimate[nSys_unique-1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    

  }

  //
  // Uncertainty Summary File
  //
  fprintf(uncFileSummary, "\\end{tabular} \n");
  fprintf(uncFileSummary, "} \n");
  fprintf(uncFileSummary, "\\end{table} \n");
  fprintf(uncFileSummary, "\\end{document} \n");
  fclose(uncFileSummary);

  
  //
  // Table of background estimate
  //
  fprintf(yFile, "\\end{tabular} \n");
  fprintf(yFile, "} \n");
  fprintf(yFile, "\\end{table} \n");
  fprintf(yFile, "\\end{document} \n");
  fclose(yFile);


  //
  // Uncertainty file for each category
  //
  fprintf(uncFile, "\\end{document} \n");
  fclose(uncFile);
  
  
  
  //
  // Clean up
  //
  f_out->Write();
  f_out->Close();
  f_SR->Close();
  f_CR->Close();
  f_data_CR->Close();

  return 0;
}
