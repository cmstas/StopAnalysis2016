// ROOT
#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

// C
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


//
// Function Declarations
//
void calcThis(std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sampleList );


//
// Main
//
void calcErrors(){


  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sampleList;

  std::pair< sampleInfo::ID, genClassyInfo::ID > sample;


  // All Background
  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // ttbar
  sample.first  = sampleInfo::k_ttbar;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_ttbar;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);
  
  sample.first  = sampleInfo::k_ttbar;
  sample.second = genClassyInfo::k_ee1lep;
  sampleList.push_back(sample);


  // single t
  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);

  
  // single t, tW
  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);


  // W+Jets
  sample.first  = sampleInfo::k_WJetsToLNu;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);
  
  
  // DY+Jets
  sample.first  = sampleInfo::k_DYJetsToLL;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);
  

  // TTW
  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);


  // TTZ
  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // WW
  sample.first  = sampleInfo::k_WW;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WW;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WW;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);


  // WZ
  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // ZZ
  sample.first  = sampleInfo::k_ZZ;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_ZZ;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_ZZ;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // tZq
  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);
  

  // Do calculation
  calcThis(sampleList);

    
  return;
}


//
// Functions
// 
void calcThis(std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sampleList ){  

  // User parameters
  bool verbose = false;

  TString input_dir      = "Histos/Nominal/";
  TString ouput_dir_hist = "Histos/Nominal/";
  TString ouput_dir_tex  = "Output/Tables/";

  TString yield_name = "yields";

  analyzerInfo::ID analysis = analyzerInfo::k_CR0b;


  // pointer for tex file output
  FILE *yFile = NULL;
  
  TString texFile_name = ouput_dir_tex;
  texFile_name += "systematicsTable.tex";
  yFile = fopen(texFile_name.Data(), "w");
  
  cout << "  Making tex file: " << endl;
  cout << "    " << texFile_name << endl;
  
  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\begin{document}\n");
  fprintf(yFile, "\\tiny\n");


  // Loop over samples
  for(int iSample=0; iSample<(int)sampleList.size(); iSample++){

    
    // Get utils from input id's
    sampleInfo::sampleUtil sample( sampleList[iSample].first );
    
    genClassyInfo::genClassyUtil genClassy( sampleList[iSample].second );

    recoClassyInfo::vect_util recoClassyList;
    recoClassyList = recoClassyInfo::getRecoClassyList( analysis );
    
    categoryInfo::vect_util catList;
    catList = categoryInfo::getCategoryList( analysis );

    systematicInfo::vect_util systematicList;
    systematicList = systematicInfo::getSystematicList( analysis, sample.isFastsim, sample.isSignal );
  
  
    // Open input file
    TString inFile_name = input_dir;
    inFile_name += "h__";
    inFile_name += sample.label;
    inFile_name += ".root";
    
    cout << "Analyzing File: " << inFile_name << endl;
    
    TFile *in_file = new TFile(inFile_name, "read");
    
  
    // Loop over recoClassifications
    for(int iReco=0; iReco<(int)recoClassyList.size(); iReco++){
  
       
      // Loop over cateogry List
      for(int iCat=0; iCat<(int)catList.size(); iCat++){
      
	fprintf(yFile, "\n \n \n \n");
	fprintf(yFile, "\\begin{table} \n");
	fprintf(yFile, "\\caption{ %s,~genClassy:~%s,~recoClassy:~%s,~cateogry:~%s } \n", sample.tex.c_str(), genClassy.tex.c_str(), recoClassyList[iReco].tex.c_str(), catList[iCat].tex.c_str());
	fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
	fprintf(yFile, "Systematic & Nominal & Sys Up, (\\%%) & Sys Down, (\\%%) & \\%% Uncertainty");
	fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");
      
	  
	// Nominal histogram name
	TString hName = histogramInfo::getYieldHistoLabel( yield_name.Data(), genClassy, recoClassyList[iReco], systematicList[0] );
	
	TH1F *h_nom = (TH1F*)in_file->Get(hName);
	if(!h_nom) cout << "BAD HISTO: " << hName << endl;
	
	double yield_nom  = h_nom->GetBinContent( h_nom->GetXaxis()->FindBin( catList[iCat].label.c_str() ) );
	double error_nom  = h_nom->GetBinError( h_nom->GetXaxis()->FindBin( catList[iCat].label.c_str() ) );
	  
	double statError = error_nom;
	double sysError = pow( statError, 2 );
	
	// Loop over systematics
	for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
	  
	  TString hNameUp = histogramInfo::getYieldHistoLabel( yield_name.Data(), genClassy, recoClassyList[iReco], systematicList[iSys] );
	  
	  TH1F *h_up = (TH1F*)in_file->Get(hNameUp);
	  if(!h_up) cout << "BAD HISTO: " << hNameUp << endl;
	  
	  double yield_up   = h_up->GetBinContent( h_up->GetXaxis()->FindBin( catList[iCat].label.c_str() ) );
	  double error_up   = h_up->GetBinError( h_up->GetXaxis()->FindBin( catList[iCat].label.c_str() ) );
	  double percent_up = (100*(yield_up-yield_nom))/yield_nom;
 
	  
	  TString hNameDown = histogramInfo::getYieldHistoLabel( yield_name.Data(), genClassy, recoClassyList[iReco], systematicList[iSys+1] );
	  
	  TH1F *h_down = (TH1F*)in_file->Get(hNameDown);
	  if(!h_down) cout << "BAD HISTO: " << hNameDown << endl;
	  
	  double yield_dn   = h_down->GetBinContent( h_down->GetXaxis()->FindBin( catList[iCat].label.c_str() ) );
	  double error_dn   = h_down->GetBinError( h_down->GetXaxis()->FindBin( catList[iCat].label.c_str() ) );
	  double percent_dn = (100*(yield_dn-yield_nom))/yield_nom;
	  
	  
	  double maxDiff = fabs(yield_nom - yield_up);
	  maxDiff = std::max( maxDiff, fabs(yield_nom - yield_dn) );
	  double maxPercentDiff = (100*maxDiff)/yield_nom;
	  
	  
	  sysError += pow( maxDiff, 2 );
	  

	  TString sys_label_tex = systematicList[iSys+1].tex;

	  sys_label_tex.ReplaceAll(",~Up","");
	  sys_label_tex.ReplaceAll(",~Down","");

	  sys_label_tex.ReplaceAll("~Up","");
	  sys_label_tex.ReplaceAll("~Down","");
	  

	  if(iSys==1){
	    fprintf(yFile, " Statistical~Error & " );
	    fprintf(yFile, " %.2f & ", yield_nom);
	    fprintf(yFile, " %.2f (%.2f) & ", yield_nom+statError, (100*(statError/yield_nom)) );
	    fprintf(yFile, " %.2f (%.2f) & ", yield_nom-statError, (-100*(statError/yield_nom)) );
	    fprintf(yFile, " %.2f ", (100*(statError/yield_nom)) );
	    
	    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	  }
	      
	  fprintf(yFile, " %s & ", sys_label_tex.Data() );
	  fprintf(yFile, " %.2f & ", yield_nom);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_up, percent_up);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_dn, percent_dn);
	  fprintf(yFile, " %.2f ", maxPercentDiff);
	  
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	
	  	  
	} // end loop over systematics

	
	sysError = sqrt( sysError );
	
	
	//
	// Total Error
	//
	fprintf(yFile, "\\hline \n");
	fprintf(yFile, " Total Uncertainty & " );
	fprintf(yFile, " %.2f & ", yield_nom);
	fprintf(yFile, " %.2f (%.2f) & ", yield_nom+sysError, (100*(sysError))/yield_nom);
	fprintf(yFile, " %.2f (%.2f) & ", yield_nom-sysError, (100*(sysError))/yield_nom);
	fprintf(yFile, " %.2f ", (100*(sysError))/yield_nom);
	
	fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	
	fprintf(yFile, "\\end{tabular} \n");
	fprintf(yFile, "\\end{table} \n");
	
	fprintf(yFile, "\n \n \n \n");
	fprintf(yFile, "\\clearpage");

      } // end loop over categories

      if(verbose) cout << endl;

    } // end loop over reco classifications

    if(verbose) cout << endl << endl;


    // Clean up
    in_file->Close();
  
  } // end loop over samples


  // print end of tex document
  fprintf(yFile, "\\end{document} \n");
  fclose(yFile);
   
  return;
}
