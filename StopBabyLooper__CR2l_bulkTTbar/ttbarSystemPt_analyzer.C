#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

#include <vector>

#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"


int ttbarSystemPt_analyzer(){

  //
  // Get SFs and make plots and tables for ttbar system pT systematic
  //


  //
  // Utility Vars
  //
  TString h_name_base = "lep1lep2bbMet_pt";
  
  TH1D *h_temp = NULL;
  TH1D *h_data = NULL;
  TH1D *h_allBkg = NULL;

  const int nRebins = 8;
  double xRebins[nRebins+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF[nRebins]{   1.0,   1.0,   1.0,   1.0,   1.0,   0.5,  0.5,  0.33333  };

  
  int bin_beginUncertainty = 3;

  //
  // Tex File Output
  //
  FILE *f_out;
  TString f_out_name = "Output/Tables/ttbarSystemPt_uncertainties.tex";
  std::cout << "    Output written to: " << std::endl;
  std::cout << "      " << f_out_name << std::endl << std::endl;
  f_out = fopen( f_out_name.Data(), "w" );

  // Print header info
  fprintf(f_out, "\\documentclass{article}\n");
  fprintf(f_out, "\\usepackage[landscape]{geometry}\n");
  fprintf(f_out, "\\usepackage{multirow}\n");
  fprintf(f_out, "\\usepackage{color}\n");
  fprintf(f_out, "\\usepackage{longtable}\n\n");
  fprintf(f_out, "\\begin{document}\n");
  fprintf(f_out, "\\tiny\n");
  fprintf(f_out, "\n\n\n\n");



  //
  // Analyzer Type
  //
  analyzerInfo::ID analysis = analyzerInfo::k_CR2l_bulkTTbar;

  
  //
  // Sample List
  //
  sampleInfo::sampleUtil data_util( sampleInfo::k_diLepton_2016B );
  TString f_data_name = "Histos/Nominal/h__";
  f_data_name += data_util.label;
  f_data_name += ".root";
  TFile *f_data = new TFile( f_data_name, "read" );

  sampleInfo::sampleUtil allBkg_util( sampleInfo::k_allBkg );
  TString f_allBkg_name = "Histos/Nominal/h__";
  f_allBkg_name += allBkg_util.label;
  f_allBkg_name += ".root";
  TFile *f_allBkg = new TFile( f_allBkg_name, "read" );


  //
  // Gen Classification
  //
  genClassyInfo::genClassyUtil genClassy( genClassyInfo::k_incl );

  
  // 
  // Reco Classifications
  //
  recoClassyInfo::vect_util recoClassyList;
  recoClassyList = recoClassyInfo::getRecoClassyList( analysis );

  
  //
  // Category List
  //
  categoryInfo::vect_util catList;
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge1btags_ge50met) );
  catList.push_back( categoryInfo::categoryUtil(categoryInfo::k_ge2btags_ge50met) );


  //
  // Systematic
  //
  systematicInfo::systematicUtil nominal_sys( systematicInfo::k_nominal );



  // Loop over reco classifications
  for(int iReco=0; iReco<(int)recoClassyList.size(); iReco++){
    
    // Loop over categories
    for(int iCat=0; iCat<(int)catList.size(); iCat++){

      // Tex table title
      TString table_title = "";
      table_title += recoClassyList[iReco].tex;
      table_title += ",~";
      table_title += catList[iCat].tex;      

      fprintf(f_out, "\n \n \n \n");
      fprintf(f_out, "\\begin{table} \n");
      fprintf(f_out, "\\caption{ %s } \n", table_title.Data() );
      fprintf(f_out, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
      fprintf(f_out, "Bin & Data & MC & Data/MC Norm & Scale Factor ");
      fprintf(f_out, "\\"); fprintf(f_out, "\\ \\hline \\hline \n");


      // histogram name
      TString h_name = histogramInfo::getHistoLabel( h_name_base.Data(), genClassy, recoClassyList[iReco], catList[iCat], nominal_sys );

      h_temp = (TH1D*)f_data->Get(h_name);
      h_data = (TH1D*)h_temp->Clone(h_name+"_data");
      
      h_temp = (TH1D*)f_allBkg->Get(h_name);
      h_allBkg = (TH1D*)h_temp->Clone(h_name+"_mc");

      
      // Grab overflow bin
      double overflow_data = h_data->GetBinContent(h_data->GetNbinsX()+1);
      double overflow_err_data = sqrt( overflow_data );
      h_data->SetBinContent( h_data->GetNbinsX(), overflow_data + h_data->GetBinContent(h_data->GetNbinsX()) );
      h_data->SetBinError( h_data->GetNbinsX(), sqrt( pow(overflow_err_data,2)+pow(h_data->GetBinError(h_data->GetNbinsX()),2) ) );
      
      double overflow_allBkg = h_allBkg->GetBinContent(h_allBkg->GetNbinsX()+1);
      double overflow_err_allBkg = h_allBkg->GetBinError(h_allBkg->GetNbinsX()+1);
      h_allBkg->SetBinContent( h_allBkg->GetNbinsX(), overflow_allBkg + h_allBkg->GetBinContent(h_allBkg->GetNbinsX()) );
      h_allBkg->SetBinError( h_allBkg->GetNbinsX(), sqrt( pow(overflow_err_allBkg,2)+pow(h_allBkg->GetBinError(h_allBkg->GetNbinsX()),2) ) );
      

      // Rebin
      h_data = (TH1D*)h_data->Rebin( nRebins, h_name+"_data_rebin", xRebins );
      h_allBkg = (TH1D*)h_allBkg->Rebin( nRebins, h_name+"_allBkg_rebin", xRebins );
      //for(int iBin=1; iBin<=(int)h_data->GetNbinsX(); iBin++){
      //h_data->SetBinContent(iBin, h_data->GetBinContent(iBin)*xRebinsSF[iBin-1]);
      //h_allBkg->SetBinContent(iBin, h_allBkg->GetBinContent(iBin)*xRebinsSF[iBin-1]);
      //}


      // Get Overall Data/MC Norm
      double data_norm = h_data->Integral( bin_beginUncertainty, h_data->GetNbinsX() );
      double data_norm_err = sqrt( data_norm );

      double allBkg_norm_err = 0.0;
      double allBkg_norm = h_allBkg->IntegralAndError( bin_beginUncertainty, h_allBkg->GetNbinsX(), allBkg_norm_err );

      double sf_norm = data_norm/allBkg_norm;
      double sf_norm_err = sf_norm*sqrt( pow(data_norm_err/data_norm,2) + pow(allBkg_norm_err/allBkg_norm,2) );

      double norm_lowEdge = h_data->GetXaxis()->GetBinLowEdge(bin_beginUncertainty);
      double norm_upEdge = h_data->GetXaxis()->GetBinUpEdge(h_data->GetNbinsX());

      fprintf( f_out, " $%.1f~<~p_{T}~<~%.1f$ & $%.0f~\\pm~%.1f$ & $%.1f~\\pm~%.1f$ & $%.2f~\\pm~%.2f$ & $---$", norm_lowEdge, norm_upEdge, data_norm, data_norm_err, allBkg_norm, allBkg_norm_err, sf_norm, sf_norm_err );
      fprintf(f_out, "\\"); fprintf(f_out, "\\ \\hline \\hline \n");
      
      // Loop over bins to get data/mc
      for(int iBin=bin_beginUncertainty; iBin<=(int)h_data->GetNbinsX(); iBin++){

	double data_bin = h_data->GetBinContent(iBin);
	double data_bin_err = sqrt( data_bin );

	double allBkg_bin = h_allBkg->GetBinContent(iBin);
	double allBkg_bin_err = h_allBkg->GetBinError(iBin);
	

	double sf = ( (data_bin/allBkg_bin) / sf_norm );
	double sf_err = sf*sqrt( pow(data_bin_err/data_bin,2) + pow(allBkg_bin_err/allBkg_bin,2) + pow(sf_norm_err/sf_norm,2) );
   
	double bin_lowEdge = h_data->GetXaxis()->GetBinLowEdge(iBin);
	double bin_upEdge  = h_data->GetXaxis()->GetBinUpEdge(iBin);
	
	fprintf( f_out, " $%.1f~<~p_{T}~<~%.1f$ & $%.0f~\\pm~%.1f$ & $%.1f~\\pm~%.1f$ & $%.2f~\\pm~%.2f$ & $%.2f~\\pm~%.2f$ ", bin_lowEdge, bin_upEdge, data_bin, data_bin_err, allBkg_bin, allBkg_bin_err, sf_norm, sf_norm_err, sf, sf_err );
	fprintf(f_out, "\\"); fprintf(f_out, "\\ \\hline \n");

      } // end loop over bins	

      // End table
      fprintf(f_out, "\\end{tabular} \n");
      fprintf(f_out, "\\end{table} \n");
      
      fprintf(f_out, "\n \n \n \n");
      fprintf(f_out, "\\clearpage");


    } // end loop over categories

  } // end loop over reco classifications


   // print end of tex document
  fprintf(f_out, "\\end{document} \n");
  fclose(f_out);



  return 0;
}

