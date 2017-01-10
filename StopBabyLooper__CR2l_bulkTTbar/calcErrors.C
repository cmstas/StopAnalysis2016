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


struct yieldHelper{
  std::string histName;
  std::string tex;
  int binNumber;
};


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

  TString input_dir       = "Output/Histos/";
  TString output_dir_tex  = "Output/Tables/";

  
  // Signal and Control Regions
  std::vector<std::string> regionList;
  //regionList.push_back("ee");
  regionList.push_back("emu");
  //regionList.push_back("mumu");
  //regionList.push_back("incl");


  // Systematics List, currently using entire list 
  sysInfo::Util nominal_sys( sysInfo::k_nominal );
  sysInfo::vect_util systematicList;
  systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) );
  for(int iSys=1; iSys<sysInfo::k_nSys; iSys++){
    //
    // Example Method To Exclude Specific Systematics
    //
    //if( iSys==sysInfo::k_pdfUp ) continue;
    //if( iSys==sysInfo::k_pdfDown ) continue;
    
    // Currently skip all systematics
    continue;

    //systematicList.push_back( sysInfo::Util(sysInfo::ID(iSys)) );
  }
  
  
  // Category List
  std::vector< std::vector<yieldHelper> > fileList;
  std::vector<yieldHelper> catList;
  yieldHelper cat;

  //
  // Yields, CR2l buk TTbar
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 1; cat.tex = "$\\ge0b-$Tagged~Jets,~$\\ge50$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 2; cat.tex = "$\\ge0b-$Tagged~Jets,~$\\ge100$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 3; cat.tex = "$\\ge0b-$Tagged~Jets,~$\\ge150$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 4; cat.tex = "$\\ge0b-$Tagged~Jets,~$\\ge200$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 5; cat.tex = "$\\ge0b-$Tagged~Jets,~$\\ge250$MET";
  catList.push_back( cat );
  
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 6; cat.tex = "$\\ge1b-$Tagged~Jets,~$\\ge50$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 7; cat.tex = "$\\ge1b-$Tagged~Jets,~$\\ge100$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 8; cat.tex = "$\\ge1b-$Tagged~Jets,~$\\ge150$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 9; cat.tex = "$\\ge1b-$Tagged~Jets,~$\\ge200$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 10; cat.tex = "$\\ge1b-$Tagged~Jets,~$\\ge250$MET";
  catList.push_back( cat );
  
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 11; cat.tex = "$\\ge2b-$Tagged~Jets,~$\\ge50$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 12; cat.tex = "$\\ge2b-$Tagged~Jets,~$\\ge100$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 13; cat.tex = "$\\ge2b-$Tagged~Jets,~$\\ge150$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 14; cat.tex = "$\\ge2b-$Tagged~Jets,~$\\ge200$MET";
  catList.push_back( cat );
  cat.histName = "h_yields_CR2l_bulkTTbar"; cat.binNumber = 15; cat.tex = "$\\ge2b-$Tagged~Jets,~$\\ge250$MET";
  catList.push_back( cat );

  fileList.push_back( catList );

  catList.clear();

 
  
  for(int iReg=0; iReg<(int)regionList.size(); iReg++){
  
    for(int iFile=0; iFile<(int)fileList.size(); iFile++){

      // Get category list for this table
      std::vector<yieldHelper> iCatList = fileList[iFile];

      // Get Name of yield Histo
      TString hNameBase = iCatList[0].histName;

      // pointer for tex file output
      FILE *yFile = NULL;
  
      TString texFile_name = output_dir_tex;
      texFile_name += "systematicsTable__";
      texFile_name += hNameBase;
      texFile_name += "__lepFlav_"; 
      texFile_name += regionList[iReg];
      texFile_name += ".tex";
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
    	
	// And which genClassification for the sample
	genClassyInfo::Util genClassy( sampleList[iSample].second );

	
	// Open input file
	TString inFile_name = input_dir;
	inFile_name += sample.label;
	inFile_name += ".root";
	
	cout << "        Analyzing File: " << inFile_name << endl;
	
	TFile *in_file = new TFile(inFile_name, "read");
	
	// Loop over cateogry List
	for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	  
	  fprintf(yFile, "\n \n \n \n");
	  fprintf(yFile, "\\begin{table} \n");
	  fprintf(yFile, "\\caption{ %s,~%s,~genClassy:~%s,~cateogry:~%s } \n", sample.tex.c_str(), regionList[iReg].c_str(), genClassy.tex.c_str(), iCatList[iCat].tex.c_str());
	  fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
	  fprintf(yFile, "Systematic & Nominal & Sys Up, (\\%%) & Sys Down, (\\%%) & \\%% Uncertainty");
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");
	  
      
	  // Nominal histogram name
	  TString hName = hNameBase;
	  hName += "__lepFlav_";
	  hName += regionList[iReg];
	  hName += "__genClassy_";
	  hName += genClassy.label;
	  hName += "__systematic_";
	  hName += nominal_sys.label;

	  TH1F *h_nom = (TH1F*)in_file->Get(hName);
	  if(!h_nom) cout << "BAD HISTO: " << hName << endl;
	  
	  double yield_nom  = h_nom->GetBinContent( catList[iCat].binNumber );
	  double error_nom  = h_nom->GetBinError( catList[iCat].binNumber );
      
	  double statError = error_nom;
	  double sysError = pow( statError, 2 );

	  fprintf(yFile, " Statistical~Error & " );
	  fprintf(yFile, " %.2f & ", yield_nom);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_nom+statError, (100*(statError/yield_nom)) );
	  fprintf(yFile, " %.2f (%.2f) & ", yield_nom-statError, (-100*(statError/yield_nom)) );
	  fprintf(yFile, " %.2f ", (100*(statError/yield_nom)) );
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	      
	    
	  if( !sample.isData ){

	    // Loop over systematics
	    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
	
	      TString hNameUp = hNameBase;
	      hNameUp += "__lepFlav_";
	      hNameUp += regionList[iReg];
	      hNameUp += "__genClassy_";
	      hNameUp += genClassy.label;
	      hNameUp += "__systematic_";
	      hNameUp += systematicList[iSys].label;

	      TH1F *h_up = (TH1F*)in_file->Get(hNameUp);
	      if(!h_up) cout << "BAD HISTO: " << hNameUp << endl;
	  
	      double yield_up   = h_up->GetBinContent( catList[iCat].binNumber );
	      double error_up   = h_up->GetBinError( catList[iCat].binNumber );
	      double percent_up = (100*(yield_up-yield_nom))/yield_nom;
 
	  
	      TString hNameDown = hNameBase;
	      hNameDown += "__lepFlav_";
	      hNameDown += regionList[iReg];
	      hNameDown += "__genClassy_";
	      hNameDown += genClassy.label;
	      hNameDown += "__systematic_";
	      hNameDown += systematicList[iSys+1].label;


	      TH1F *h_down = (TH1F*)in_file->Get(hNameDown);
	      if(!h_down) cout << "BAD HISTO: " << hNameDown << endl;
	  
	      double yield_dn   = h_down->GetBinContent( catList[iCat].binNumber );
	      double error_dn   = h_down->GetBinError( catList[iCat].binNumber );
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
	  

	      fprintf(yFile, " %s & ", sys_label_tex.Data() );
	      fprintf(yFile, " %.2f & ", yield_nom);
	      fprintf(yFile, " %.2f (%.2f) & ", yield_up, percent_up);
	      fprintf(yFile, " %.2f (%.2f) & ", yield_dn, percent_dn);
	      fprintf(yFile, " %.2f ", maxPercentDiff);
	  
	      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	
	  	  
	    } // end loop over systematics

	  } // end if sample is data
	
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
      
	// Clean up
	in_file->Close();
  	
      } // end loop over samples
  
      if(verbose) cout << endl << endl;

      // print end of tex document
      fprintf(yFile, "\\end{document} \n");
      fclose(yFile);
    
    } // end loop over files
    
  } // end loop over regions
   
  return;
}
