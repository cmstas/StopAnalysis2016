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
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/sysInfo.h"


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
  //sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ge2lep;
  //sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  //sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ZtoNuNu;
  //sampleList.push_back(sample);
  

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

  TString input_dir      = "Output/Histos/";
  TString ouput_dir_hist = "Output/Histos/";
  TString ouput_dir_tex  = "Output/Tables/";

  TString yield_name = "yields";

  
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

  //
  // HistoName Base
  //
  TString hNameBase = "h_yields_SR_ICHEP";

  //
  // Signal and Control Regions
  //
  std::vector<std::string> regionList;
  regionList.push_back("SR");
  regionList.push_back("CR0b");
  regionList.push_back("CR2l");

  
  vector<TString> catList;
  catList.push_back( "ee2jets_ge6p4modTop_250to350met" ); // 1
  catList.push_back( "ee2jets_ge6p4modTop_350to450met" ); // 2
  catList.push_back( "ee2jets_ge6p4modTop_450toInfmet" ); // 3
  catList.push_back( "ee3jets_ge200mt2w_250to350met" );   // 4
  catList.push_back( "ee3jets_ge200mt2w_350to450met" );   // 5
  catList.push_back( "ee3jets_ge200mt2w_450to550met" );   // 6
  catList.push_back( "ee3jets_ge200mt2w_550toInfmet" );   // 7
  catList.push_back( "ge4jets_lt200mt2w_250to350met" );   // 8
  catList.push_back( "ge4jets_lt200mt2w_350to450met" );   // 9
  catList.push_back( "ge4jets_lt200mt2w_450toInfmet" );   // 10
  catList.push_back( "ge4jets_ge200mt2w_250to350met" );   // 11
  catList.push_back( "ge4jets_ge200mt2w_350to450met" );   // 12
  catList.push_back( "ge4jets_ge200mt2w_450to550met" );   // 13
  catList.push_back( "ge4jets_ge200mt2w_550to650met" );   // 14
  catList.push_back( "ge4jets_ge200mt2w_650toInfmet" );   // 15
  

  // Loop over samples
  for(int iSample=0; iSample<(int)sampleList.size(); iSample++){

    
    // Get utils from input id's
    sampleInfo::sampleUtil sample( sampleList[iSample].first );
    
    genClassyInfo::Util genClassy( sampleList[iSample].second );

    sysInfo::Util nominal_sys( sysInfo::k_nominal );
    sysInfo::vect_util systematicList;
    systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) );
    if( !sample.isData ){
      for(int iSys=1; iSys<sysInfo::k_nSys; iSys++){
	if( iSys==sysInfo::k_pdfUp ) continue;
	if( iSys==sysInfo::k_pdfDown ) continue;
	systematicList.push_back( sysInfo::Util(sysInfo::ID(iSys)) );
      }
    }
  
    
    // Open input file
    TString inFile_name = input_dir;
    inFile_name += sample.label;
    inFile_name += ".root";
    
    cout << "        Analyzing File: " << inFile_name << endl;
    
    TFile *in_file = new TFile(inFile_name, "read");
    
    
    // Loop over Signal and Control Regions
    for(int iReg=0; iReg<(int)regionList.size(); iReg++){
  
      // Loop over cateogry List
      for(int iCat=0; iCat<(int)catList.size(); iCat++){
      
	fprintf(yFile, "\n \n \n \n");
	fprintf(yFile, "\\begin{table} \n");
	fprintf(yFile, "\\caption{ %s,~%s,~genClassy:~%s,~cateogry:~$%s$ } \n", sample.tex.c_str(), regionList[iReg].c_str(), genClassy.tex.c_str(), catList[iCat].Data());
	fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
	fprintf(yFile, "Systematic & Nominal & Sys Up, (\\%%) & Sys Down, (\\%%) & \\%% Uncertainty");
	fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");
      
      
	// Nominal histogram name
	//TString hName = histogramInfo::getYieldHistoLabel( yield_name.Data(), genClassy, recoClassyList[iReco], systematicList[0] );
	TString hName = hNameBase;
	hName += "__";
	hName += regionList[iReg];
	hName += "__genClassy_";
	hName += genClassy.label;
	hName += "__systematic_";
	hName += nominal_sys.label;

	TH1F *h_nom = (TH1F*)in_file->Get(hName);
	if(!h_nom) cout << "BAD HISTO: " << hName << endl;
      
	double yield_nom  = h_nom->GetBinContent( h_nom->GetXaxis()->FindBin( catList[iCat].Data() ) );
	double error_nom  = h_nom->GetBinError( h_nom->GetXaxis()->FindBin( catList[iCat].Data() ) );
      
	double statError = error_nom;
	double sysError = pow( statError, 2 );
      
	// Loop over systematics
	for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
	
	  //TString hNameUp = histogramInfo::getYieldHistoLabel( yield_name.Data(), genClassy, recoClassyList[iReco], systematicList[iSys] );
	  TString hNameUp = hNameBase;
	  hNameUp += "__";
	  hNameUp += regionList[iReg];
	  hNameUp += "__genClassy_";
	  hNameUp += genClassy.label;
	  hNameUp += "__systematic_";
	  hNameUp += systematicList[iSys].label;

	  TH1F *h_up = (TH1F*)in_file->Get(hNameUp);
	  if(!h_up) cout << "BAD HISTO: " << hNameUp << endl;
	  
	  double yield_up   = h_up->GetBinContent( h_up->GetXaxis()->FindBin( catList[iCat].Data() ) );
	  double error_up   = h_up->GetBinError( h_up->GetXaxis()->FindBin( catList[iCat].Data() ) );
	  double percent_up = (100*(yield_up-yield_nom))/yield_nom;
 
	  
	  //TString hNameDown = histogramInfo::getYieldHistoLabel( yield_name.Data(), genClassy, recoClassyList[iReco], systematicList[iSys+1] );
	  TString hNameDown = hNameBase;
	  hNameDown += "__";
	  hNameDown += regionList[iReg];
	  hNameDown += "__genClassy_";
	  hNameDown += genClassy.label;
	  hNameDown += "__systematic_";
	  hNameDown += systematicList[iSys+1].label;


	  TH1F *h_down = (TH1F*)in_file->Get(hNameDown);
	  if(!h_down) cout << "BAD HISTO: " << hNameDown << endl;
	  
	  double yield_dn   = h_down->GetBinContent( h_down->GetXaxis()->FindBin( catList[iCat].Data() ) );
	  double error_dn   = h_down->GetBinError( h_down->GetXaxis()->FindBin( catList[iCat].Data() ) );
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
      
    } // end loop over regionList
  
    if(verbose) cout << endl << endl;


    // Clean up
    in_file->Close();
  
  } // end loop over samples


  // print end of tex document
  fprintf(yFile, "\\end{document} \n");
  fclose(yFile);
   
  return;
}
