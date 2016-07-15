#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH3.h"
#include "TString.h"

#include <algorithm>
#include <string>
#include <vector>

#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"

int tableMaker_results( std::string f_input_dir="Histos/Nominal/", std::string f_out_name="Output/Tables/yields_results.tex", bool useZeroedAMCNLO=true ){

  // Make a tex document where each page will have a table
  //   This table will be for a given systematic. 
  //   It will show the yields for a set of catogries in rows
  //      and columns will be the input samples split by gen and reco
  //      classifications

  
  //
  // Configuration Variables
  //
  bool usePsuedoData = false;

  bool doRescale = false;
  double rescale = 1.0; // use lumi from stopCORE
  //double rescale = 10.0/3.99; // rescale to new lumi

  
  //
  // Analyzer Type
  //
  analyzerInfo::ID analysis = analyzerInfo::k_SR;

  //
  // Sample List
  //
  TFile *f_input = NULL;

  std::pair< std::string, std::string > sample;
  
  std::vector< std::pair< std::string, std::string > > bkgList;
  
  sample.first = "Histos/Nominal/h_limit__lostLep.root"; 
  sample.second = "CR2l_yield";
  bkgList.push_back(sample);

  sample.first = "Histos/Nominal/h_limit__1lepFromW.root"; 
  sample.second = "ee1lepFromW_yield";
  bkgList.push_back(sample);

  sample.first = "Histos/Nominal/h_limit__1lepFromT.root"; 
  sample.second = "ee1lepFromT_yield";
  bkgList.push_back(sample);

  sample.first = "Histos/Nominal/h_limit__ZtoNuNu.root"; 
  sample.second = "ZtoNuNu_yield";
  bkgList.push_back(sample);
  
  std::pair< std::string, std::string > sample_data;
  sample_data.first = "Histos/Nominal/h_limit__data.root";
  sample_data.second = "Observed_yield";


  //
  // Category List
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
  // Open output file
  //
  FILE *f_out;
  std::cout << "    Output written to: " << std::endl;
  std::cout << "      " << f_out_name << std::endl << std::endl;
  f_out = fopen( f_out_name.c_str(), "w" );

  //
  // Print header info
  //
  fprintf(f_out, "\\documentclass{article}\n");
  fprintf(f_out, "\\usepackage[landscape]{geometry}\n");
  fprintf(f_out, "\\usepackage{multirow}\n");
  fprintf(f_out, "\\usepackage{color}\n");
  //fprintf(f_out, "\\usepackage{longtable}\n\n");
  fprintf(f_out, "\\begin{document}\n");
  fprintf(f_out, "\n\n\n\n");

  
  // First Header
  fprintf(f_out, "\\begin{table}[htb] \n");
  fprintf(f_out, "\\begin{center} \n");
  fprintf(f_out, "\\tiny \n");
  fprintf(f_out, "\\caption{ \\label{ tab:results} Results table } \n");


  // nColumns
  fprintf(f_out, "\\begin{tabular}{|l|c|c|c|c|c|c|} ");
  fprintf(f_out, "\\"); fprintf(f_out, "\\ \\hline \n");
  
  fprintf(f_out, " Signal Region & Lost Lepton & 1lep from W & 1lep from top & $Z\\rightarrow\\nu\\nu$ & Sum of all Backgrounds & Observed ");
  fprintf(f_out, "\\"); fprintf(f_out, "\\ \\hline \n");
  

  //
  // Loop over category list
  //
  for(int iCat=0; iCat<(int)catList.size(); iCat++){

    fprintf(f_out, "%s", catList[iCat].tex.c_str());
    
    //
    // Loop over Bkg samples
    //
    double sum_bkg = 0.0;
    double err_bkg = 0.0;
    for(int iBkg=0; iBkg<(int)bkgList.size(); iBkg++){
      
      TString f_input_name = bkgList[iBkg].first;
      f_input = new TFile( f_input_name.Data(), "read");
      
      std::string h_name = bkgList[iBkg].second;
      
      double yield = 0.0;
      double error = 0.0;
      
      TH1D *h_yield_bkg = (TH1D*)f_input->Get(h_name.c_str());
      yield = h_yield_bkg->GetBinContent( h_yield_bkg->GetXaxis()->FindBin(catList[iCat].label.c_str()) );
      error = h_yield_bkg->GetBinError( h_yield_bkg->GetXaxis()->FindBin(catList[iCat].label.c_str()) );
      
      if(doRescale){
	yield *= rescale;
	error *= rescale;
      }
      
      if( yield == 0.0 ){
	fprintf(f_out, " & --- ");
      }
      else if( yield < 0.0 ){
	fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", yield, error);
      }
      else{
	fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
      }

      sum_bkg += yield;
      err_bkg += pow(error,2);

      f_input->Close();
      f_input->~TFile();
    
    } // end loop over bkgs    
    
    err_bkg = sqrt(err_bkg);

    if( sum_bkg == 0.0 ){
      fprintf(f_out, " & --- ");
    }
    else if( sum_bkg < 0.0 ){
      fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", sum_bkg, err_bkg);
    }
    else{
      fprintf(f_out, " & %.2f $\\pm$ %.2f ", sum_bkg, err_bkg);
    }

    
    //
    // Data
    //
    TString f_input_name = sample_data.first;
    f_input = new TFile( f_input_name.Data(), "read");
    
    double yield = 0.0;
    double error = 0.0;
    
    TH1D *h_yield_data = (TH1D*)f_input->Get(sample_data.second.c_str());
    yield = h_yield_data->GetBinContent( h_yield_data->GetXaxis()->FindBin(catList[iCat].label.c_str()) );
    error = sqrt(yield);
	  
    if(doRescale){
      yield *= rescale;
      error = sqrt(yield);
    }
    
    if( yield == 0.0 ){
      fprintf(f_out, " & --- ");
    }
    else if( yield < 0.0 ){
      fprintf(f_out, " & \\textcolor{red}{ %.2f $\\pm$ %.2f } ", yield, error);
    }
    else{
      fprintf(f_out, " & %.2f $\\pm$ %.2f ", yield, error);
    }
    
    fprintf(f_out, "\\");fprintf(f_out, "\\ "); 
    fprintf(f_out, "\\hline \n");
    
    f_input->Close();
    f_input->~TFile();
  
  } // end loop over categories
    
    
  // End table
  fprintf(f_out, "\\end{tabular} \n");
  fprintf(f_out, "\\end{center} \n");
  fprintf(f_out, "\\end{table} \n");
  fprintf(f_out, "\\end{document} \n");

  
  fclose(f_out);


  return 0;
}
