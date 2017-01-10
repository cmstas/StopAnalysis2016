#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

#include <vector>

#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/sysInfo.h"


int ttbarSystemPt_analyzer(){

  //
  // Get SFs and make plots and tables for ttbar system pT systematic
  //


  // Histogram Information
  TString h_name_base = "h_lep1lep2bbMetPt";
  
  TH1D *h_temp = NULL;
  TH1D *h_data = NULL;
  TH1D *h_allBkg = NULL;

  const int nRebins = 8;
  double xRebins[nRebins+1]{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 600.0 };
  double xRebinsSF[nRebins]{   1.0,   1.0,   1.0,   1.0,   1.0,   0.5,  0.5,  0.33333  };

  int bin_beginUncertainty = 1; // which bin to begin at, full range=1, =0GeV
  //int bin_beginUncertainty = 3; // which bin to begin at, ICHEP=3, =100GeV


  // Get Data File
  sampleInfo::sampleUtil data_util( sampleInfo::k_diLepton );
  TString f_data_name = "Output/Histos/";
  f_data_name += data_util.label;
  f_data_name += ".root";
  TFile *f_data = new TFile( f_data_name, "read" );

  // Get Bkg File
  sampleInfo::sampleUtil allBkg_util( sampleInfo::k_allBkg );
  TString f_allBkg_name = "Output/Histos/";
  f_allBkg_name += allBkg_util.label;
  f_allBkg_name += ".root";
  TFile *f_allBkg = new TFile( f_allBkg_name, "read" );


  // Category List
  std::vector<std::string> catList;
  catList.push_back("ge0bTags");
  catList.push_back("ge1bTags");
  catList.push_back("ge2bTags");

  std::vector<std::string> catList_tex;
  catList_tex.push_back("$\\ge0$~bTags");
  catList_tex.push_back("$\\ge1$~bTags");
  catList_tex.push_back("$\\ge2$~bTags");
  

  // Region List
  std::vector<std::string> regionList;
  //regionList.push_back("ee");
  regionList.push_back("emu");
  //regionList.push_back("mumu");
  //regionList.push_back("incl");

  std::vector<std::string> regionList_tex;
  //regionList_tex.push_back("$ee$");
  regionList_tex.push_back("$e\\mu$");
  //regionList_tex.push_back("$\\mu\\mu$");
  //regionList_tex.push_back("$ee/e\\mu/\\mu\\mu$");


  // Gen Classification
  genClassyInfo::Util genClassy( genClassyInfo::k_incl );

    
  // Systematic
  sysInfo::Util nominal_sys( sysInfo::k_nominal );


  // Tex File Output
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


  
  // Loop over reco classifications
  for(int iReg=0; iReg<(int)regionList.size(); iReg++){
    
    // Loop over categories
    for(int iCat=0; iCat<(int)catList.size(); iCat++){

      // Tex table title
      TString table_title = "";
      table_title += regionList_tex[iReg];
      table_title += ",~";
      table_title += catList_tex[iCat];      

      fprintf(f_out, "\n \n \n \n");
      fprintf(f_out, "\\begin{table} \n");
      fprintf(f_out, "\\caption{ %s } \n", table_title.Data() );
      fprintf(f_out, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
      fprintf(f_out, "Bin & Data & MC & Data/MC Norm & Scale Factor ");
      fprintf(f_out, "\\"); fprintf(f_out, "\\ \\hline \\hline \n");


      // histogram name
      TString h_name = h_name_base;
      h_name += "__";
      h_name += catList[iCat];
      h_name += "__lepFlav_";
      h_name += regionList[iReg];
      h_name += "__genClassy_";
      h_name += genClassy.label;
      h_name += "__systematic_";
      h_name += nominal_sys.label;

      h_temp = (TH1D*)f_data->Get(h_name);
      h_data = (TH1D*)h_temp->Clone(h_name+"_data");
      
      h_temp = (TH1D*)f_allBkg->Get(h_name);
      h_allBkg = (TH1D*)h_temp->Clone(h_name+"_mc");


      //cout << endl;
      //cout << "Overall: data = " << h_data->Integral(0,-1) << endl;
      //cout << "           mc = " << h_allBkg->Integral(0,-1) << endl;
      //cout << "      data/mc = " << h_data->Integral(0,-1)/h_allBkg->Integral(0,-1) << endl; 
      //cout << endl;

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

  } // end loop over regions


  // print end of tex document
  fprintf(f_out, "\\end{document} \n");
  fclose(f_out);


  return 0;
}

