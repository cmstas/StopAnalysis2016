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
int bkgEstimate_diLepton(){


  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  
  //
  // Configuration Variables
  //
  bool usePsuedoData = false;

  bool doRescale = false;
  double rescale = 1.0; // use lumi from stopCORE
  //double rescale = 10.0/3.99; // rescale to new lumi

  TString yield_base = "yields";

  TString texFile = "";

  

  //
  // recoClassy Type
  //
  //recoClassyInfo::recoClassyUtil recoClassyType_CR(recoClassyInfo::k_2lep_2selOrVetoLep);
  recoClassyInfo::recoClassyUtil recoClassyType_CR(recoClassyInfo::k_incl);
  recoClassyInfo::recoClassyUtil recoClassyType_SR(recoClassyInfo::k_incl);
 
 
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
  genClassyInfo::genClassyUtil genClassy_MC_SR( genClassyInfo::k_ge2lep );
      

  //
  // diLepton CR Region
  //
  TFile *f_CR = new TFile(inDir_CR+"h__allBkg_25ns.root", "read");
  genClassyInfo::genClassyUtil genClassy_MC_CR( genClassyInfo::k_incl );
  
  
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
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_lt200mt2w_250to325met ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_lt200mt2w_325toInfmet) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_250to350met ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_350to450met ) );
  sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_450toInfmet) );
  const int nSRs = (int)sr_cats.size();


  //
  // Signal Region to Control Region Cateogries
  //
  categoryInfo::vect_util cr2sr_cats;
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge3jets_ge200mt2w ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge3jets_ge200mt2w ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge3jets_lt200mt2w ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge3jets_lt200mt2w ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge3jets_ge200mt2w ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge3jets_ge200mt2w ) );
  //cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge3jets_ge200mt2w ) );

  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop_250to350met ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee2jets_ge6p4modTop_350toInfmet ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee3jets_ge200mt2w_250to350met ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ee3jets_ge200mt2w_350toInfmet ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_lt200mt2w_250to325met ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_lt200mt2w_325toInfmet ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_250to350met ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_350to450met ) );
  cr2sr_cats.push_back( categoryInfo::categoryUtil( categoryInfo::k_ge4jets_ge200mt2w_450toInfmet ) );

  
  bool oneTF = true;
  for(int iSR=0; iSR<nSRs; iSR++){
    if( sr_cats[iSR].id != cr2sr_cats[iSR].id ){
      oneTF = false;
      break;
    }
  }
    

  //
  // Systematics
  //
  systematicInfo::systematicUtil nominal_sys( systematicInfo::k_nominal );
  
  systematicInfo::vect_util systematicList = systematicInfo::getSystematicList_forLimit_lostLepton();
  const int nSys = (int)systematicList.size();

  
  //
  // Output file for ratio
  //
  TFile  *f_out = new TFile(outDir+"h__bkgEstimate_diLepton.root", "recreate");


  //
  // Histograms for limit setting
  //
  TH1D *h_SR[nSys];
  h_SR[0] = new TH1D("CR2lyield", "CR2lyield", nSRs, 0.0, nSRs); // Nominal
  for(int iCat=0; iCat<(int)nSRs; iCat++){
    h_SR[0]->GetXaxis()->SetBinLabel( iCat+1, sr_cats[iCat].label.c_str() );
  }
  h_SR[0]->SetDirectory(f_out);


  //
  // Systematics for limit setting
  //
  for(int iSys=1; iSys<nSys; iSys++){
    h_SR[iSys] = new TH1D(Form("CR2l_%s", systematicList[iSys].label.c_str()), Form("CR2l_%s",systematicList[iSys].label.c_str()), nSRs, 0.0, nSRs);   
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
  texFile += "bkgEstimate_lostLepton.tex";
  yFile = fopen(texFile.Data(), "w");
  
  cout << "Writing simple file of diLepton Estimates to file; " << endl;
  cout << "    " << texFile << endl;

  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\usepackage{graphicx} \n\n");
  fprintf(yFile, "\\begin{document}\n");
  fprintf(yFile, "\\tiny \n");  
  fprintf(yFile, "\\begin{table} \n");
  fprintf(yFile, "\\caption{ diLepton Background Estimate and Components, for each Signal Region } \n");
  fprintf(yFile, "\\scalebox{1.0}{ \n");
  if(oneTF){
    fprintf(yFile, "\\begin{tabular}{|l|c|c|c|} \\hline \n");
    fprintf(yFile, "Category & $N_{Incl}^{CR}$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR}$ & $N_{2\\ell,estimate}^{SR}$");
  }
  else{
    fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
    fprintf(yFile, "Category & $N_{Incl}^{CR}$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR}$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR}$ & $N_{2\\ell,estimate}^{SR}$");
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");


  
  // ROW=Uncertainties, COL=DiLepton Estimate and Components, Summary
  FILE *uncFileSummary;
  TString uncFileSummaryName = outDir;
  uncFileSummaryName += "bkgEstimate_lostLepton__uncertaintyTable__summary.tex";
  uncFileSummary = fopen(uncFileSummaryName.Data(), "w");
  
  cout << "Writing table of diLepton uncertainties to: " << endl;
  cout << "    " << uncFileSummaryName << endl;

  fprintf(uncFileSummary, "\\documentclass{article}\n");
  fprintf(uncFileSummary, "\\usepackage[landscape]{geometry}\n");
  fprintf(uncFileSummary, "\\usepackage{chngpage}\n\n");
  fprintf(uncFileSummary, "\\usepackage{graphicx} \n\n");
  fprintf(uncFileSummary, "\\begin{document}\n");
  fprintf(uncFileSummary, "\\tiny \n"); 
  fprintf(uncFileSummary, "\\begin{table} \n");
  fprintf(uncFileSummary, "\\caption{ Summary of diLepton Background Estimate Uncertainties } \n");
  fprintf(uncFileSummary, "\\scalebox{0.7}{ \n");
  if(oneTF){
    fprintf(uncFileSummary, "\\begin{tabular}{|l|c|c|c|} \\hline \n");
    fprintf(uncFileSummary, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR},~(\\%%)$ & $N_{2\\ell,estimate}^{SR},~(\\%%)$ ");
  }
  else{
    fprintf(uncFileSummary, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
    fprintf(uncFileSummary, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR},~(\\%%)$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR},~(\\%%)$ & $N_{2\\ell,estimate}^{SR},~(\\%%)$ ");
  }
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \\hline \n");


  const int nSys_unique = ((nSys-1)/2) + 3; // -1 for nominal, +1 for data stats, +1 for mc stats, +1 for total uncertainty
  double uncMax_cr_data_cr2sr[nSys_unique]; 
  double uncMin_cr_data_cr2sr[nSys_unique];
  double uncMax_tf_cr2sr[nSys_unique]; 
  double uncMin_tf_cr2sr[nSys_unique];
  double uncMax_tf_srBin[nSys_unique]; 
  double uncMin_tf_srBin[nSys_unique];
  double uncMax_sr_estimate[nSys_unique]; 
  double uncMin_sr_estimate[nSys_unique];
  for(int iSys=0; iSys<nSys_unique; iSys++){
    uncMax_cr_data_cr2sr[iSys] = 0.0;
    uncMin_cr_data_cr2sr[iSys] = 999.9;
    uncMax_tf_cr2sr[iSys] = 0.0;
    uncMin_tf_cr2sr[iSys] = 999.9;
    uncMax_tf_srBin[iSys] = 0.0;
    uncMin_tf_srBin[iSys] = 999.9;
    uncMax_sr_estimate[iSys] = 0.0;
    uncMin_sr_estimate[iSys] = 999.9;
  }


  //
  // Uncertainty table for each category
  //
  
  // ROW=Uncertainties, COL=DiLepton Estimate and Components
  FILE *uncFile = NULL;
  TString uncFileName = outDir;
  uncFileName += "bkgEstimate_lostLepton__uncertaintyTable__byCategory.tex";
  uncFile = fopen(uncFileName.Data(), "w");

  cout << "Writing table of diLepton uncertainties to: " << endl;
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
    fprintf(uncFile, "\\caption{ diLepton Background Estimate Uncertainties, for %s } \n", sr_cats[iSR].tex.c_str());
    fprintf(uncFile, "\\scalebox{0.6}{ \n");
    if(oneTF){
      fprintf(uncFile, "\\begin{tabular}{|l|c|c|c|c|c|} \\hline \n");
      fprintf(uncFile, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR},~(\\%%)$ & $M_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR},~(\\%%)$ & $N_{2\\ell,estimate}^{SR},~(\\%%)$ ");
    }
    else{
      fprintf(uncFile, "\\begin{tabular}{|l|c|c|c|c|c|c|c|} \\hline \n");
      fprintf(uncFile, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR},~(\\%%)$ & $M_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR},~(\\%%)$ & $M_{MET,nJet~bin}^{SR},~(\\%%)$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR},~(\\%%)$ & $N_{2\\ell,estimate}^{SR},~(\\%%)$ ");
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n");
    
    //
    // Get yields, begin calculation for this cateogry
    //


    //
    // SR, category bin 
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR, recoClassyType_SR, nominal_sys );
    
    h_temp = (TH1D*)f_SR->Get(hName);
    if(!h_temp) cout << "BAD SR CATEGORY BIN HISTO: " << hName << endl;

    double SR_bin_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
    double SR_bin_error = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
    
    if(doRescale){
      SR_bin_error *= rescale;
      SR_bin_yield *= rescale;
    }
    
    
    //
    // SR, mc, cr2sr bin
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR, recoClassyType_SR, nominal_sys );

    h_temp = (TH1D*)f_SR->Get(hName);
    if(!h_temp) cout << "BAD SR CRtoSR bin HISTO: " << hName << endl;
    
    double SR_cr2sr_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
    double SR_cr2sr_error = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
    int SR_cr2sr_nEntries = h_temp->GetEntries();

    if(doRescale){
      SR_cr2sr_error *= rescale;
      SR_cr2sr_yield *= rescale;
    }
    
    
    //
    // CR, mc, cr2sr bin
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR, recoClassyType_CR, nominal_sys );
    
    h_temp = (TH1D*)f_CR->Get(hName);
    if(!h_temp) cout << "BAD MC CR CRtoSR bin HISTO: " << hName << endl;
    
    double CR_cr2sr_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
    double CR_cr2sr_error = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
    
    if(doRescale){
      CR_cr2sr_error *= rescale;
      CR_cr2sr_yield *= rescale;
    }
    

    //
    // CR, data, cr2sr bin
    //
    hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_data_CR, recoClassyType_CR, nominal_sys );
    
    h_temp = (TH1D*)f_data_CR->Get(hName);
    if(!h_temp) cout << "BAD DATA CR CRtoSR bin HISTO: " << hName << endl;
    
    double CR_data_cr2sr_yield = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
    double CR_data_cr2sr_error = sqrt( CR_data_cr2sr_yield );

    if(doRescale){
      CR_data_cr2sr_yield *= rescale;
      CR_data_cr2sr_error = sqrt( CR_data_cr2sr_yield );
      
    }
    


    // Transfer Factor SR/CR
    double tf_cr2sr = 1.0;
    double tf_cr2sr_err = 0.0;
    double tf_cr2sr_statErr = 0.0;
    
    // Transfer Factor SR_bin/SR_cr2sr
    double tf_srBin = 1.0;
    double tf_srBin_err = 0.0;
    double tf_srBin_statErr = 0.0;

    // Signal Region Estimate
    double sr_estimate = 0.0;
    double sr_estimate_error = 0.0;
    double sr_estimate_error_mc_stats = 0.0;


    if(oneTF){

      // Transfer Factor SR/CR
      if(CR_cr2sr_yield>0.0){
	tf_cr2sr = SR_cr2sr_yield/CR_cr2sr_yield;
	tf_cr2sr_err = tf_cr2sr*sqrt( pow(CR_cr2sr_error/CR_cr2sr_yield, 2) + pow(SR_cr2sr_error/SR_cr2sr_yield, 2) ); // avoid double counting mc stats
	tf_cr2sr_statErr = tf_cr2sr_err;
      }
    
      // Signal Region Estimate
      sr_estimate = CR_data_cr2sr_yield*tf_cr2sr;
      sr_estimate_error = sr_estimate*sqrt( pow(CR_data_cr2sr_error/CR_data_cr2sr_yield, 2) + pow(tf_cr2sr_err/tf_cr2sr, 2) );
      sr_estimate_error_mc_stats = sr_estimate*sqrt( pow(tf_cr2sr_err/tf_cr2sr, 2) );


    }
    else{

      // Transfer Factor SR/CR
      if(CR_cr2sr_yield>0.0){
	tf_cr2sr = SR_cr2sr_yield/CR_cr2sr_yield;
	tf_cr2sr_err = tf_cr2sr*sqrt( pow( CR_cr2sr_error/CR_cr2sr_yield, 2 ) ); // avoid double counting mc stats
	tf_cr2sr_statErr = tf_cr2sr_err;
      }
    
      // Transfer Factor SR_bin/SR_cr2sr
      if(SR_cr2sr_yield>0.0){
	tf_srBin = SR_bin_yield/SR_cr2sr_yield;
	tf_srBin_err = sqrt( tf_srBin*(1-tf_srBin)/SR_cr2sr_nEntries ); // binomial errors since SR_bin_yield is a subset of SR_cr2sr_yield
	tf_srBin_statErr = tf_srBin_err;
      }

      //
      // Signal Region Estimate
      //
      sr_estimate = CR_data_cr2sr_yield*tf_cr2sr*tf_srBin;
      sr_estimate_error = sr_estimate*sqrt( pow(CR_data_cr2sr_error/CR_data_cr2sr_yield, 2) + pow(tf_cr2sr_err/tf_cr2sr, 2) + pow(tf_srBin_err/tf_srBin, 2) );
      sr_estimate_error_mc_stats = sr_estimate*sqrt( pow(tf_cr2sr_err/tf_cr2sr, 2) + pow(tf_srBin_err/tf_srBin, 2) );

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
      fprintf(uncFile, "Nominal & %.2f & %.2f & %.2f & %.2f & %.2f ", CR_data_cr2sr_yield, SR_cr2sr_yield, CR_cr2sr_yield, tf_cr2sr, sr_estimate );
    }
    else{
      fprintf(uncFile, "Nominal & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", CR_data_cr2sr_yield, SR_cr2sr_yield, CR_cr2sr_yield, tf_cr2sr, SR_bin_yield, tf_srBin, sr_estimate );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n"); 
 
    
    //
    // Uncertainty File, Data Stats
    //
    if(oneTF){
      fprintf(uncFile, "Data Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield+CR_data_cr2sr_error, (100*CR_data_cr2sr_error/CR_data_cr2sr_yield), SR_cr2sr_yield, 0.0, CR_cr2sr_yield, 0.0, tf_cr2sr, 0.0, (CR_data_cr2sr_yield+CR_data_cr2sr_error)*tf_cr2sr*tf_srBin, (100*(((CR_data_cr2sr_yield+CR_data_cr2sr_error)*tf_cr2sr*tf_srBin)-sr_estimate))/sr_estimate );
    }
    else{
      fprintf(uncFile, "Data Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield+CR_data_cr2sr_error, (100*CR_data_cr2sr_error/CR_data_cr2sr_yield), SR_cr2sr_yield, 0.0, CR_cr2sr_yield, 0.0, tf_cr2sr, 0.0, SR_bin_yield, 0.0, tf_srBin, 0.0, (CR_data_cr2sr_yield+CR_data_cr2sr_error)*tf_cr2sr*tf_srBin, (100*(((CR_data_cr2sr_yield+CR_data_cr2sr_error)*tf_cr2sr*tf_srBin)-sr_estimate))/sr_estimate );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 


    if(oneTF){
      fprintf(uncFile, "Data Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield-CR_data_cr2sr_error, (-100*CR_data_cr2sr_error/CR_data_cr2sr_yield), SR_cr2sr_yield, 0.0, CR_cr2sr_yield, 0.0, tf_cr2sr, 0.0, (CR_data_cr2sr_yield-CR_data_cr2sr_error)*tf_cr2sr*tf_srBin, (100*(((CR_data_cr2sr_yield-CR_data_cr2sr_error)*tf_cr2sr*tf_srBin)-sr_estimate))/sr_estimate );
    }
    else{
      fprintf(uncFile, "Data Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield-CR_data_cr2sr_error, (-100*CR_data_cr2sr_error/CR_data_cr2sr_yield), SR_cr2sr_yield, 0.0, CR_cr2sr_yield, 0.0, tf_cr2sr, 0.0, SR_bin_yield, 0.0, tf_srBin, 0.0, (CR_data_cr2sr_yield-CR_data_cr2sr_error)*tf_cr2sr*tf_srBin, (100*(((CR_data_cr2sr_yield-CR_data_cr2sr_error)*tf_cr2sr*tf_srBin)-sr_estimate))/sr_estimate );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");


    //
    // Calc Min/Max uncertainty for data stats
    //
    uncMax_cr_data_cr2sr[0] = std::max( uncMax_cr_data_cr2sr[0], (100*CR_data_cr2sr_error/CR_data_cr2sr_yield) );
    uncMin_cr_data_cr2sr[0] = std::min( uncMin_cr_data_cr2sr[0], (100*CR_data_cr2sr_error/CR_data_cr2sr_yield) );
    uncMax_tf_cr2sr[0] = std::max( uncMax_tf_cr2sr[0], 0.0 );
    uncMin_tf_cr2sr[0] = std::min( uncMin_tf_cr2sr[0], 0.0 );
    uncMax_tf_srBin[0] = std::max( uncMax_tf_srBin[0], 0.0 );
    uncMin_tf_srBin[0] = std::min( uncMin_tf_srBin[0], 0.0 );
    uncMax_sr_estimate[0] = std::max( uncMax_sr_estimate[0], (100*(((CR_data_cr2sr_yield+CR_data_cr2sr_error)*tf_cr2sr*tf_srBin)-sr_estimate))/sr_estimate );
    uncMin_sr_estimate[0] = std::min( uncMin_sr_estimate[0], (100*(((CR_data_cr2sr_yield+CR_data_cr2sr_error)*tf_cr2sr*tf_srBin)-sr_estimate))/sr_estimate );
    
    
    //
    // Uncertainty File, MC Stats Up
    //
    if(oneTF){
      fprintf(uncFile, "MC Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield, 0.0, SR_cr2sr_yield+SR_cr2sr_error, (100*SR_cr2sr_error/SR_cr2sr_yield), CR_cr2sr_yield+CR_cr2sr_error, (100*CR_cr2sr_error/CR_cr2sr_yield), tf_cr2sr+tf_cr2sr_err, (100*tf_cr2sr_err/tf_cr2sr), sr_estimate+sr_estimate_error_mc_stats, (100*sr_estimate_error_mc_stats/sr_estimate) );
    }
    else{
      fprintf(uncFile, "MC Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield, 0.0, SR_cr2sr_yield+SR_cr2sr_error, (100*SR_cr2sr_error/SR_cr2sr_yield), CR_cr2sr_yield+CR_cr2sr_error, (100*CR_cr2sr_error/CR_cr2sr_yield), tf_cr2sr+tf_cr2sr_err, (100*tf_cr2sr_err/tf_cr2sr), SR_bin_yield+SR_bin_error, (100*SR_bin_error/SR_bin_yield), tf_srBin+tf_srBin_err, (100*tf_srBin_err/tf_srBin), sr_estimate+sr_estimate_error_mc_stats, (100*sr_estimate_error_mc_stats/sr_estimate) );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 

    
    if(oneTF){
      fprintf(uncFile, "MC Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield, 0.0, SR_cr2sr_yield-SR_cr2sr_error, (-100*SR_cr2sr_error/SR_cr2sr_yield), CR_cr2sr_yield-CR_cr2sr_error, (-100*CR_cr2sr_error/CR_cr2sr_yield), tf_cr2sr-tf_cr2sr_err, (-100*tf_cr2sr_err/tf_cr2sr), sr_estimate-sr_estimate_error_mc_stats, (-100*sr_estimate_error_mc_stats/sr_estimate) );
    }
    else{
      fprintf(uncFile, "MC Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", CR_data_cr2sr_yield, 0.0, SR_cr2sr_yield-SR_cr2sr_error, (-100*SR_cr2sr_error/SR_cr2sr_yield), CR_cr2sr_yield-CR_cr2sr_error, (-100*CR_cr2sr_error/CR_cr2sr_yield), tf_cr2sr-tf_cr2sr_err, (-100*tf_cr2sr_err/tf_cr2sr), SR_bin_yield-SR_bin_error, (-100*SR_bin_error/SR_bin_yield), tf_srBin-tf_srBin_err, (-100*tf_srBin_err/tf_srBin), sr_estimate-sr_estimate_error_mc_stats, (-100*sr_estimate_error_mc_stats/sr_estimate) );
    }
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");

    fprintf(uncFile, "\\hline \n");
    
    
    //
    // Calc Min/Max for MC Stats
    //
    uncMax_cr_data_cr2sr[1] = std::max( uncMax_cr_data_cr2sr[1], 0.0 );
    uncMin_cr_data_cr2sr[1] = std::min( uncMin_cr_data_cr2sr[1], 0.0 );
    uncMax_tf_cr2sr[1] = std::max( uncMax_tf_cr2sr[1], (100*tf_cr2sr_err/tf_cr2sr) );
    uncMin_tf_cr2sr[1] = std::min( uncMin_tf_cr2sr[1], (100*tf_cr2sr_err/tf_cr2sr) );
    uncMax_tf_srBin[1] = std::max( uncMax_tf_srBin[1], (100*tf_srBin_err/tf_srBin) );
    uncMin_tf_srBin[1] = std::min( uncMin_tf_srBin[1], (100*tf_srBin_err/tf_srBin) );
    uncMax_sr_estimate[1] = std::max( uncMax_sr_estimate[1], (100*sr_estimate_error_mc_stats/sr_estimate) );
    uncMin_sr_estimate[1] = std::min( uncMin_sr_estimate[1], (100*sr_estimate_error_mc_stats/sr_estimate) );
    
  
    //
    // Loop over systematics
    //
    int unique_sys = 2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      
      //
      // SR, category bin, up
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR, recoClassyType_SR, systematicList[iSys] );

      h_temp = (TH1D*)f_SR->Get(hName);
      if(!h_temp) cout << "BAD SR CATEGORY BIN UP HISTO: " << hName << endl;
      
      double SR_bin_yield_up = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      double SR_bin_error_up = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	SR_bin_error_up *= rescale;
	SR_bin_yield_up *= rescale;
      }
      
      
      //
      // SR, cr2sr bin, up
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR, recoClassyType_SR, systematicList[iSys] );
      
      h_temp = (TH1D*)f_SR->Get(hName);
      if(!h_temp) cout << "BAD SR INCL UP HISTO: " << hName << endl;
    
      double SR_cr2sr_yield_up = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      double SR_cr2sr_error_up = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      int SR_cr2sr_nEntries_up = h_temp->GetEntries();

      if(doRescale){
	SR_cr2sr_error_up *= rescale;
	SR_cr2sr_yield_up *= rescale;
      }
      

      //
      // CR, MC, cr2sr bin, up
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR, recoClassyType_CR, systematicList[iSys] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR CRtoSR UP MC HISTO: " << hName << endl;
    
      double CR_cr2sr_yield_up = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      double CR_cr2sr_error_up = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	CR_cr2sr_error_up *= rescale;
	CR_cr2sr_yield_up *= rescale;
      }


      
      // Transfer Factor SR/CR, up
      double tf_cr2sr_up = 1.0;
      double tf_cr2sr_up_statErr = 0.0;
    
      // Transfer Factor SR_bin/SR_cr2sr
      double tf_srBin_up = 1.0;
      double tf_srBin_up_statErr = 0.0;

      // Signal Region Estimate
      double sr_estimate_up = 0.0;
      double sr_estimate_up_statErr = 0.0;
      
      if(oneTF){
	
	// TF for SR/CR, up
	if(CR_cr2sr_yield_up>0.0){
	  tf_cr2sr_up = SR_cr2sr_yield_up/CR_cr2sr_yield_up;
	  tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(CR_cr2sr_error_up/CR_cr2sr_yield_up, 2) + pow(SR_cr2sr_error_up/SR_cr2sr_yield_up, 2) ); // avoid double counting mc stats
	}

	// SR estimate, up
	sr_estimate_up = CR_data_cr2sr_yield*tf_cr2sr_up;
	sr_estimate_up_statErr = sr_estimate_up*sqrt( pow( CR_data_cr2sr_error/CR_data_cr2sr_yield,2 ) + pow( tf_cr2sr_up_statErr/tf_cr2sr_up,2 ) );

      }
      else{
	
	// TF for SR/CR, up
	if(CR_cr2sr_yield_up>0.0){
	  tf_cr2sr_up = SR_cr2sr_yield_up/CR_cr2sr_yield_up;
	  tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow( CR_cr2sr_error_up/CR_cr2sr_yield_up, 2 ) ); // avoid double counting mc stats
	}

	// TF for SR_bin/SR_cr2sr, up
	if(SR_cr2sr_yield_up>0.0){
	  tf_srBin_up = SR_bin_yield_up/SR_cr2sr_yield_up;
	  tf_srBin_up_statErr = sqrt( tf_srBin_up*(1-tf_srBin_up)/SR_cr2sr_nEntries_up ); // binomial errors since SR_bin_yield is a subset of SR_cr2sr_yield
	}

	// SR estimate, up
	sr_estimate_up = CR_data_cr2sr_yield*tf_cr2sr_up*tf_srBin_up;
	sr_estimate_up_statErr = sr_estimate_up*sqrt( pow( CR_data_cr2sr_error/CR_data_cr2sr_yield,2 ) + pow( tf_cr2sr_up_statErr/tf_cr2sr_up,2 ) + pow( tf_srBin_up_statErr/tf_srBin_up,2 ) );

      }


      if(oneTF){
	fprintf(uncFile, "%s,~Up & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)  ",systematicList[iSys].tex.c_str(),CR_data_cr2sr_yield,0.0,SR_cr2sr_yield_up,(100*(SR_cr2sr_yield_up-SR_cr2sr_yield)/SR_cr2sr_yield),CR_cr2sr_yield_up,(100*(CR_cr2sr_yield_up-CR_cr2sr_yield)/CR_cr2sr_yield), tf_cr2sr_up, (100*(tf_cr2sr_up-tf_cr2sr)/tf_cr2sr), sr_estimate_up, (100*(sr_estimate_up-sr_estimate)/sr_estimate) );
      }
      else{
	fprintf(uncFile, "%s,~Up & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",systematicList[iSys].tex.c_str(),CR_data_cr2sr_yield,0.0,SR_cr2sr_yield_up,(100*(SR_cr2sr_yield_up-SR_cr2sr_yield)/SR_cr2sr_yield),CR_cr2sr_yield_up,(100*(CR_cr2sr_yield_up-CR_cr2sr_yield)/CR_cr2sr_yield), tf_cr2sr_up, (100*(tf_cr2sr_up-tf_cr2sr)/tf_cr2sr), SR_bin_yield_up, (100*(SR_bin_yield_up-SR_bin_yield)/SR_bin_yield), tf_srBin_up, (100*(tf_srBin_up-tf_srBin)/tf_srBin), sr_estimate_up, (100*(sr_estimate_up-sr_estimate)/sr_estimate) );
      }
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 
        
      
      //
      // SR, category bin, dn
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR, recoClassyType_SR, systematicList[iSys+1] );
      
      h_temp = (TH1D*)f_SR->Get(hName);
      if(!h_temp) cout << "BAD SR BIN DN HISTO: " << hName << endl;

      double SR_bin_error_dn = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );
      double SR_bin_yield_dn = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( sr_cats[iSR].label.c_str() ) );

      if(doRescale){
	SR_bin_error_dn *= rescale;
	SR_bin_yield_dn *= rescale;
      }
      
      
      //
      // SR, CRtoSR bin, dn
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_SR, recoClassyType_SR, systematicList[iSys+1] );

      h_temp = (TH1D*)f_SR->Get(hName);
      if(!h_temp) cout << "BAD SR INCL DN HISTO: " << hName << endl;
    
      double SR_cr2sr_yield_dn = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      double SR_cr2sr_error_dn = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      int SR_cr2sr_nEntries_dn = h_temp->GetEntries();

      if(doRescale){
	SR_cr2sr_error_dn *= rescale;
	SR_cr2sr_yield_dn *= rescale;
      }
      
      
      //
      // CR, MC, CRtoSR bin, dn
      //
      hName = histogramInfo::getYieldHistoLabel( "yields", genClassy_MC_CR, recoClassyType_CR, systematicList[iSys+1] );
      
      h_temp = (TH1D*)f_CR->Get(hName);
      if(!h_temp) cout << "BAD CR CRtoSR DN MC HISTO: " << hName << endl;
 
      double CR_cr2sr_yield_dn = h_temp->GetBinContent( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      double CR_cr2sr_error_dn = h_temp->GetBinError( h_temp->GetXaxis()->FindBin( cr2sr_cats[iSR].label.c_str() ) );
      
      if(doRescale){
	CR_cr2sr_error_dn *= rescale;
	CR_cr2sr_yield_dn *= rescale;
      }



      // Transfer Factor SR/CR, dn
      double tf_cr2sr_dn = 1.0;
      double tf_cr2sr_dn_statErr = 0.0;
    
      // Transfer Factor SR_bin/SR_cr2sr, dn
      double tf_srBin_dn = 1.0;
      double tf_srBin_dn_statErr = 0.0;

      // Signal Region Estimate, dn
      double sr_estimate_dn = 0.0;
      double sr_estimate_dn_statErr = 0.0;
      
      if(oneTF){

	// Tf_Cr2sr of SR/CR, dn
	tf_cr2sr_dn = SR_cr2sr_yield_dn/CR_cr2sr_yield_dn;
	tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(CR_cr2sr_error_dn/CR_cr2sr_yield_dn,2) + pow(SR_cr2sr_error_dn/SR_cr2sr_yield_dn,2) ); // avoid double counting MC stats
      
	// SR estimate, dn
	sr_estimate_dn = CR_data_cr2sr_yield*tf_cr2sr_dn;
	sr_estimate_dn_statErr = sr_estimate_dn*sqrt( pow( CR_data_cr2sr_error/CR_data_cr2sr_yield,2 ) + pow( tf_cr2sr_dn_statErr/tf_cr2sr_dn,2 ) );

      }
      else{

	// Tf_Cr2sr of SR/CR, dn
	tf_cr2sr_dn = SR_cr2sr_yield_dn/CR_cr2sr_yield_dn;
	tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow( CR_cr2sr_error_dn/CR_cr2sr_yield_dn,2 ) ); // avoid double counting MC stats
      
	// Transfer Factor SR_bin/SR_cr2sr, dn
	tf_srBin_dn = SR_bin_yield_dn/SR_cr2sr_yield_dn;
	tf_srBin_dn_statErr = sqrt( tf_srBin_dn*(1-tf_srBin_dn)/SR_cr2sr_nEntries_dn ); // binomial errors since SR_bin_yield is a subset of SR_cr2sr_yield
	
	// SR estimate, dn
	sr_estimate_dn = CR_data_cr2sr_yield*tf_cr2sr_dn*tf_srBin_dn;
	sr_estimate_dn_statErr = sr_estimate_dn*sqrt( pow( CR_data_cr2sr_error/CR_data_cr2sr_yield,2 ) + pow( tf_cr2sr_dn_statErr/tf_cr2sr_dn,2 ) + pow( tf_srBin_dn_statErr/tf_srBin_dn,2 ) );

      }


      //
      // Diff in TF Cr2sr
      //
      double tf_cr2sr_max_diff = std::max( fabs(tf_cr2sr_up-tf_cr2sr), fabs(tf_cr2sr_dn-tf_cr2sr) );
      double tf_cr2sr_max_diff_sq = pow( tf_cr2sr_max_diff, 2 );
      tf_cr2sr_err = pow( tf_cr2sr_err, 2 );
      tf_cr2sr_err += tf_cr2sr_max_diff_sq;
      tf_cr2sr_err = sqrt(tf_cr2sr_err);


      //
      // Diff in TF SR bin
      //
      double tf_srBin_max_diff = std::max( fabs(tf_srBin_up-tf_srBin), fabs(tf_srBin_dn-tf_srBin) );
      double tf_srBin_max_diff_sq = pow( tf_srBin_max_diff, 2 );
      tf_srBin_err = pow( tf_srBin_err, 2 );
      tf_srBin_err += tf_srBin_max_diff_sq;
      tf_srBin_err = sqrt(tf_srBin_err);


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
      h_SR[iSys]->SetBinError( iSR+1, sr_estimate_up_statErr );
      h_SR[iSys+1]->SetBinContent( iSR+1, sr_estimate_dn );
      h_SR[iSys+1]->SetBinError( iSR+1, sr_estimate_dn_statErr );
    
      
      //
      // Tables
      //
      if(oneTF){
	fprintf(uncFile, "%s,~Down & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)  ",systematicList[iSys].tex.c_str(),CR_data_cr2sr_yield,0.0,SR_cr2sr_yield_dn,(100*(SR_cr2sr_yield_dn-SR_cr2sr_yield)/SR_cr2sr_yield),CR_cr2sr_yield_dn,(100*(CR_cr2sr_yield_dn-CR_cr2sr_yield)/CR_cr2sr_yield), tf_cr2sr_dn, (100*(tf_cr2sr_dn-tf_cr2sr)/tf_cr2sr), sr_estimate_dn, (100*(sr_estimate_dn-sr_estimate)/sr_estimate) );
      }
      else{
	fprintf(uncFile, "%s,~Down & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",systematicList[iSys].tex.c_str(),CR_data_cr2sr_yield,0.0,SR_cr2sr_yield_dn,(100*(SR_cr2sr_yield_dn-SR_cr2sr_yield)/SR_cr2sr_yield),CR_cr2sr_yield_dn,(100*(CR_cr2sr_yield_dn-CR_cr2sr_yield)/CR_cr2sr_yield), tf_cr2sr_dn, (100*(tf_cr2sr_dn-tf_cr2sr)/tf_cr2sr), SR_bin_yield_dn, (100*(SR_bin_yield_dn-SR_bin_yield)/SR_bin_yield), tf_srBin_dn, (100*(tf_srBin_dn-tf_srBin)/tf_srBin), sr_estimate_dn, (100*(sr_estimate_dn-sr_estimate)/sr_estimate) );
      }
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");
  
      
      //
      // Fill Min/Max Uncertainty
      //
      uncMax_cr_data_cr2sr[unique_sys] = std::max( uncMax_cr_data_cr2sr[unique_sys], 0.0 );
      uncMin_cr_data_cr2sr[unique_sys] = std::min( uncMin_cr_data_cr2sr[unique_sys], 0.0 );
      uncMax_tf_cr2sr[unique_sys] = std::max( uncMax_tf_cr2sr[unique_sys], (100*tf_cr2sr_max_diff/tf_cr2sr) );
      uncMin_tf_cr2sr[unique_sys] = std::min( uncMin_tf_cr2sr[unique_sys], (100*tf_cr2sr_max_diff/tf_cr2sr) );
      uncMax_tf_srBin[unique_sys] = std::max( uncMax_tf_srBin[unique_sys], (100*tf_srBin_max_diff/tf_srBin) );
      uncMin_tf_srBin[unique_sys] = std::min( uncMin_tf_srBin[unique_sys], (100*tf_srBin_max_diff/tf_srBin) );
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
      fprintf(uncFile, "Total Uncertainties & %.2f\\%% & & & %.2f\\%% & %.2f\\%% ",(100*CR_data_cr2sr_error/CR_data_cr2sr_yield), (100*tf_cr2sr_err/tf_cr2sr), (100*sr_estimate_error/sr_estimate) );
    }
    else{
      fprintf(uncFile, "\\hline \n");
      fprintf(uncFile, "Total Uncertainties & %.2f\\%% & & & %.2f\\%% & & & %.2f\\%% ",(100*CR_data_cr2sr_error/CR_data_cr2sr_yield), (100*tf_cr2sr_err/tf_cr2sr), (100*sr_estimate_error/sr_estimate) );
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
    uncMax_cr_data_cr2sr[nSys_unique-1] = std::max( uncMax_cr_data_cr2sr[nSys_unique-1], (100*CR_data_cr2sr_error/CR_data_cr2sr_yield) );
    uncMin_cr_data_cr2sr[nSys_unique-1] = std::min( uncMin_cr_data_cr2sr[nSys_unique-1], (100*CR_data_cr2sr_error/CR_data_cr2sr_yield) );
    uncMax_tf_cr2sr[nSys_unique-1] = std::max( uncMax_tf_cr2sr[nSys_unique-1], (100*tf_cr2sr_err/tf_cr2sr) );
    uncMin_tf_cr2sr[nSys_unique-1] = std::min( uncMin_tf_cr2sr[nSys_unique-1], (100*tf_cr2sr_err/tf_cr2sr) );
    uncMax_tf_srBin[nSys_unique-1] = std::max( uncMax_tf_srBin[nSys_unique-1], (100*tf_srBin_err/tf_srBin) );
    uncMin_tf_srBin[nSys_unique-1] = std::min( uncMin_tf_srBin[nSys_unique-1], (100*tf_srBin_err/tf_srBin) );
    uncMax_sr_estimate[nSys_unique-1] = std::max( uncMax_sr_estimate[nSys_unique-1], (100*sr_estimate_error/sr_estimate) );
    uncMin_sr_estimate[nSys_unique-1] = std::min( uncMin_sr_estimate[nSys_unique-1], (100*sr_estimate_error/sr_estimate) );
    
    
    if(oneTF){
      fprintf(yFile, "%.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f " , CR_data_cr2sr_yield, CR_data_cr2sr_error, tf_cr2sr, tf_cr2sr_err, sr_estimate, sr_estimate_error);
    }
    else{
      fprintf(yFile, "%.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f " , CR_data_cr2sr_yield, CR_data_cr2sr_error, tf_cr2sr, tf_cr2sr_err, tf_srBin, tf_srBin_err, sr_estimate, sr_estimate_error);
    }
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

    

  } // end loop over signal regions

  

  //
  // Summary table of uncertainties
  //
  if(oneTF){
    
    fprintf(uncFileSummary, "Data Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[0], uncMax_cr_data_cr2sr[0], uncMin_tf_cr2sr[0], uncMax_tf_cr2sr[0], uncMin_sr_estimate[0], uncMax_sr_estimate[0]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    
    fprintf(uncFileSummary, "MC Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[1], uncMax_cr_data_cr2sr[1], uncMin_tf_cr2sr[1], uncMax_tf_cr2sr[1], uncMin_sr_estimate[1], uncMax_sr_estimate[1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    
    int unique_sys = 2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      fprintf(uncFileSummary, "%s & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", sys_name.Data(), uncMin_cr_data_cr2sr[unique_sys], uncMax_cr_data_cr2sr[unique_sys], uncMin_tf_cr2sr[unique_sys], uncMax_tf_cr2sr[unique_sys], uncMin_sr_estimate[unique_sys], uncMax_sr_estimate[unique_sys]);
      fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
      unique_sys++;
    }
    
    fprintf(uncFileSummary, "Total & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[nSys_unique-1], uncMax_cr_data_cr2sr[nSys_unique-1], uncMin_tf_cr2sr[nSys_unique-1], uncMax_tf_cr2sr[nSys_unique-1], uncMin_sr_estimate[nSys_unique-1], uncMax_sr_estimate[nSys_unique-1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");

  }
  else{

    fprintf(uncFileSummary, "Data Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[0], uncMax_cr_data_cr2sr[0], uncMin_tf_cr2sr[0], uncMax_tf_cr2sr[0], uncMin_tf_srBin[0], uncMax_tf_srBin[0], uncMin_sr_estimate[0], uncMax_sr_estimate[0]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \n");
    
    fprintf(uncFileSummary, "MC Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[1], uncMax_cr_data_cr2sr[1], uncMin_tf_cr2sr[1], uncMax_tf_cr2sr[1], uncMin_tf_srBin[1], uncMax_tf_srBin[1], uncMin_sr_estimate[1], uncMax_sr_estimate[1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    
    int unique_sys = 2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      fprintf(uncFileSummary, "%s & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", sys_name.Data(), uncMin_cr_data_cr2sr[unique_sys], uncMax_cr_data_cr2sr[unique_sys], uncMin_tf_cr2sr[unique_sys], uncMax_tf_cr2sr[unique_sys], uncMin_tf_srBin[unique_sys], uncMax_tf_srBin[unique_sys], uncMin_sr_estimate[unique_sys], uncMax_sr_estimate[unique_sys]);
      fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \n");
      unique_sys++;
    }
    
    fprintf(uncFileSummary, "\\hline \n");
    fprintf(uncFileSummary, "Total & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[nSys_unique-1], uncMax_cr_data_cr2sr[nSys_unique-1], uncMin_tf_cr2sr[nSys_unique-1], uncMax_tf_cr2sr[nSys_unique-1], uncMin_tf_srBin[nSys_unique-1], uncMax_tf_srBin[nSys_unique-1], uncMin_sr_estimate[nSys_unique-1], uncMax_sr_estimate[nSys_unique-1]);
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
