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


TString input_dir       = "Histos/Nominal/";
TString input_dir_JESup = "Histos/JESup/";
TString input_dir_JESdn = "Histos/JESdown/";

//
// Function Declarations
//
void calcThis(TString inFileName, TString file_label, TString file_tex);


//
// Main
//
void calcErrors(){

  
  calcThis("histos__ttbar_25ns.root", "ttbar", "$t\\bar{t}$");
  calcThis("histos__singleT_25ns.root", "singleT", "$single~T$");
  calcThis("histos__DYJets_25ns.root", "dyjets", "$DY+Jets$");
  calcThis("histos__WJets_25ns.root", "wjets", "$W+Jets$");
  calcThis("histos__rare_25ns.root", "rare", "$Rare$");
  calcThis("histos__nonTTbarBkg_25ns.root", "nonTTbar", "$non-t\\bar{t}$");
  calcThis("histos__allBkg_25ns.root", "allBkg", "$All~Backgrounds$");  
  
  return;
}


//
// Functions
//
void calcThis(TString inFileName, TString file_label, TString file_tex){  

  cout << "Analyzing File: " << input_dir+inFileName << endl;

  bool verbose = false;

  // Open input file
  TFile *in_file       = new TFile(input_dir+inFileName, "read");
  TFile *in_file_jesUp = new TFile(input_dir_JESup+inFileName, "read");
  TFile *in_file_jesDn = new TFile(input_dir_JESdn+inFileName, "read");

  // Open output file
  TString outFileExt = "_summedErrors.root";
  TString outFileName = input_dir;
  outFileName += inFileName;
  outFileName.ReplaceAll(".root", outFileExt);
  TFile *out_file = new TFile(outFileName, "recreate");

  TString texFileOutPath = "Plots/";

  // pointer for tex file output
  FILE *yFile = NULL;
  
  // Delcare histoHelper
  histoHelper h_helper;

  // Get nominal systematic name
  TString hName_nominal_sys = "";
  for(int iSys=0; iSys<(int)h_helper.systematics.size(); iSys++){
    if( h_helper.systematics[iSys]->id == k_nominal ){
      hName_nominal_sys = h_helper.systematics[iSys]->label;
    }
  }
  
  // Additional PDF,QCD,Q2 systematics, that are stored in nominal loop
  vector<TString> genSys_var_labels;
  TString genSys_var_labels_nom = "genweights_nom";
  genSys_var_labels.push_back("genweights_alphaS_scaleUp");
  genSys_var_labels.push_back("genweights_alphaS_scaleDown");
  genSys_var_labels.push_back("genweights_q2_scaleUp");
  genSys_var_labels.push_back("genweights_q2_scaleDown");
  genSys_var_labels.push_back("genweights_pdf_scaleUp");
  genSys_var_labels.push_back("genweights_pdf_scaleDown");

  vector<TString> genSys_var_tex;
  genSys_var_tex.push_back("\\alpha_{S},~Scale~Up");
  genSys_var_tex.push_back("\\alpha_{S},~Scale~Down");
  genSys_var_tex.push_back("Q^{2},~Scale~Up");
  genSys_var_tex.push_back("Q^{2},~Scale~Down");
  genSys_var_tex.push_back("PDF,~Scale~Up");
  genSys_var_tex.push_back("PDF,~Scale~Down");
  

  // Loop over variables
  for(int iVar=0; iVar<(int)h_helper.vars_1D.size(); iVar++){

    if(verbose) cout << "  Variable: " << h_helper.vars_1D[iVar]->title << endl; 

    // Variable label
    TString var_label = h_helper.vars_1D[iVar]->label;

    bool makeTexFiles = false;
    if(var_label=="yields") makeTexFiles = true;

    //if(!makeTexFiles) continue;
    
    // Loop over classifications
    for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){

      if(verbose) cout << "     Classification: " << h_helper.classifications[iClassy]->title << endl;

      // Classification label
      TString classy_label = h_helper.classifications[iClassy]->label;

      // Loop over categories
      for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){

	// Category label
	TString cat_label = h_helper.categories[iCat]->label;

	if(verbose) cout << "      Category: " << h_helper.categories[iCat]->title << endl;

	if(makeTexFiles){

	  TString texFile = texFileOutPath;
	  texFile += "systematicsTable_stop_1l_SR__";
	  texFile += file_label;
	  texFile += "__";
	  texFile += classy_label;
	  texFile += "__";
	  texFile += cat_label;
	  texFile += ".tex";
	  yFile = fopen(texFile.Data(), "w");

	  cout << "  Making tex file: " << endl;
	  cout << "    " << texFile << endl;

	  // Tex File Formatting
	  fprintf(yFile, "\\documentclass{article}\n");
	  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
	  fprintf(yFile, "\\usepackage{chngpage}\n\n");
	  fprintf(yFile, "\\begin{document}\n");
	  //fprintf(yFile, "\\small\n");
	  fprintf(yFile, "\\tiny\n");
	  
	  fprintf(yFile, "\\begin{table} \n");
	  fprintf(yFile, "\\caption{ %s, %s, %s } \n", file_tex.Data(),  h_helper.classifications[iClassy]->tex.Data(), h_helper.categories[iCat]->tex.Data());
	  fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
	  fprintf(yFile, "Systematic & Nominal & Sys Up, (\\%%) & Sys Down, (\\%%) & \\%% Uncertainty");
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	}
	  
	// Nominal histogram name
	TString hName = "h__";
	hName += var_label;
	hName += "__";
	hName += classy_label;
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += cat_label;

	TH1F *h_temp = (TH1F*)in_file->Get(hName);
	if(!h_temp) cout << "BAD HISTO: " << hName << endl;
	
	// Clone name
	TString hName_clone = hName;
	hName_clone += "__statError";

	TH1F *h_stat = (TH1F*)h_temp->Clone(hName_clone);
	h_stat->SetDirectory(out_file);

	// Clone name
	hName_clone = hName;
	hName_clone += "__sysError";
	TH1F *h_sys = (TH1F*)h_temp->Clone(hName_clone);
	h_sys->SetDirectory(out_file);

	for(int iSys=1; iSys<(int)h_helper.systematics.size(); iSys+=2){
	  
	  TString hNameUp = "h__";
	  hNameUp += var_label;
	  hNameUp += "__";
	  hNameUp += classy_label;
	  hNameUp += "__";
	  hNameUp += h_helper.systematics[iSys]->label;
	  hNameUp += "__";
	  hNameUp += cat_label;
	  
	  TH1F *h_up = (TH1F*)in_file->Get(hNameUp);
	  if(!h_up) cout << "BAD HISTO: " << hNameUp << endl;

	  TString hNameDown = "h__";
	  hNameDown += var_label;
	  hNameDown += "__";
	  hNameDown += classy_label;
	  hNameDown += "__";
	  hNameDown += h_helper.systematics[iSys+1]->label;
	  hNameDown += "__";
	  hNameDown += cat_label;

	  TH1F *h_down = (TH1F*)in_file->Get(hNameDown);
	  if(!h_down) cout << "BAD HISTO: " << hNameDown << endl;

	  double error_nom  = 0.0;
	  double yield_nom  = h_stat->IntegralAndError(0,-1,error_nom);
	  
	  double error_up   = 0.0;
	  double yield_up   = h_up->IntegralAndError(0,-1,error_up);
	  double percent_up = (100*(yield_up-yield_nom))/yield_nom;
	  
	  double error_dn   = 0.0;
	  double yield_dn   = h_down->IntegralAndError(0,-1,error_dn);
	  double percent_dn = (100*(yield_dn-yield_nom))/yield_nom;
	  
	  double maxDiff = fabs(yield_nom - yield_up);
	  maxDiff = std::max( maxDiff, fabs(yield_nom - yield_dn) );
	  double maxPercentDiff = (100*maxDiff)/yield_nom;
	  
	  TString sys_label_tex = h_helper.systematics[iSys+1]->tex;
	  sys_label_tex.ReplaceAll(",~Scale~Up","");
	  sys_label_tex.ReplaceAll(",~Scale~Down","");
	  
	  if(makeTexFiles){
	    if(iSys==1){
	      fprintf(yFile, " $MC~Stats$ & " );
	      fprintf(yFile, " %.2f & ", yield_nom);
	      fprintf(yFile, " %.2f (%.2f) & ", yield_nom+error_nom, (100*(error_nom/yield_nom)) );
	      fprintf(yFile, " %.2f (%.2f) & ", yield_nom-error_nom, (-100*(error_nom/yield_nom)) );
	      fprintf(yFile, " %.2f ", (100*(error_nom/yield_nom)) );
	    	      
	      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	    }
	      
	    fprintf(yFile, " $%s$ & ", sys_label_tex.Data() );
	    fprintf(yFile, " %.2f & ", yield_nom);
	    fprintf(yFile, " %.2f (%.2f) & ", yield_up, percent_up);
	    fprintf(yFile, " %.2f (%.2f) & ", yield_dn, percent_dn);
	    fprintf(yFile, " %.2f ", maxPercentDiff);

	    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	  }

	  // Bin by Bin Systematic
	  for(int iBin=0; iBin<=(int)h_sys->GetNbinsX()+1; iBin++){

	    double nom = h_sys->GetBinContent(iBin);
	    if( !(nom>0.0) ) continue;

	    double up  = h_up->GetBinContent(iBin);
	    double dn  = h_down->GetBinContent(iBin);
	    
	    double maxDiff = fabs(up-nom);
	    maxDiff = std::max( maxDiff, fabs(dn-nom) );
	    double maxDiffSq = pow( maxDiff, 2 );

	    double currentErr = h_sys->GetBinError(iBin);
	    double currentErrSq = pow( currentErr, 2 );
	    
	    double errSq = currentErrSq + maxDiffSq;
	    double err = sqrt( errSq );

	    h_sys->SetBinError( iBin, err );

	    if(verbose){
	      if(var_label.Contains("nJets") ||
		 var_label.Contains("yields")    ){
		cout << "        iBin=" << iBin << ", nom=" << nom << ", " << h_helper.systematics[iSys]->title << "=" << up << ", " << h_helper.systematics[iSys+1]->title << "=" << dn << ", maxDiff=" << maxDiff << ", relErr=" << maxDiff/nom << ", currentErr=" << currentErr << ", err=" << err << endl;
	      } // end if nJets or yields
	    } // end if verbose

	  } // end loop over bins
	  
	} // end loop over systematics




	//
	// Uncertainties, that have change in acceptance, JES up/down
	//
	TH1F *h_jesUp = (TH1F*)in_file_jesUp->Get(hName);
	if(!h_jesUp) cout << "BAD HISTO, JESup: " << hName << endl;
	
	TH1F *h_jesDn = (TH1F*)in_file_jesDn->Get(hName);
	if(!h_jesDn) cout << "BAD HISTO, JESdn: " << hName << endl;

	double yield_nom   = h_stat->Integral(0,-1);
	double yield_jesUp = h_jesUp->Integral(0,-1);
	double yield_jesDn = h_jesDn->Integral(0,-1);
	
	double percent_jesUp = 0.0;
	if(yield_nom>0.0) percent_jesUp = (100*(yield_jesUp-yield_nom))/yield_nom;
	double percent_jesDn = 0.0;
	if(yield_nom>0.0) percent_jesDn = (100*(yield_jesDn-yield_nom))/yield_nom;

	double maxDiffJES = fabs(yield_nom - yield_jesUp);
	maxDiffJES = std::max( maxDiffJES, fabs(yield_nom - yield_jesDn) );
	double maxPercentDiffJES = (100*maxDiffJES)/yield_nom;
	  
	if(makeTexFiles){
	  fprintf(yFile, " JES & " );
	  fprintf(yFile, " %.2f & ", yield_nom);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_jesUp, percent_jesUp);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_jesDn, percent_jesDn);
	  fprintf(yFile, " %.2f ", maxPercentDiffJES);
	  
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	}
	
	// Bin by Bin Systematic
	for(int iBin=0; iBin<=(int)h_sys->GetNbinsX()+1; iBin++){
	  
	  double nom = h_sys->GetBinContent(iBin);
	  if( !(nom>0.0) ) continue;
	  
	  double up  = h_jesUp->GetBinContent(iBin);
	  double dn  = h_jesDn->GetBinContent(iBin);
	  
	  double maxDiff = fabs(up-nom);
	  maxDiff = std::max( maxDiff, fabs(dn-nom) );
	  double maxDiffSq = pow( maxDiff, 2 );

	  double currentErr = h_sys->GetBinError(iBin);
	  double currentErrSq = pow( currentErr, 2 );
	  
	  double errSq = currentErrSq + maxDiffSq;
	  double err = sqrt( errSq );
	  
	  h_sys->SetBinError( iBin, err );

	} // end loop over bins
	 
	
	/*
	//
	// XSection Uncertainties
	//

	// Nominal genweights histogram name
	TString hName_genWgtNom = "h__";
	hName_genWgtNom += genSys_var_labels_nom;
	hName_genWgtNom += "__";
	hName_genWgtNom += classy_label;
	hName_genWgtNom += "__";
	hName_genWgtNom += hName_nominal_sys;
	hName_genWgtNom += "__";
	hName_genWgtNom += cat_label;
	
	TH1F *h_genWgtNom = (TH1F*)in_file->Get(hName_genWgtNom);
	if(!h_genWgtNom) cout << "BAD HISTO: " << hName_genWgtNom << endl;

	if( h_genWgtNom->GetEntries()>0.0 ){
	  for(int iSys=0; iSys<(int)genSys_var_labels.size(); iSys+=2){

	    TString hNameUp = "h__";
	    hNameUp += genSys_var_labels[iSys];
	    hNameUp += "__";
	    hNameUp += classy_label;
	    hNameUp += "__";
	    hNameUp += hName_nominal_sys;
	    hNameUp += "__";
	    hNameUp += cat_label;
	  
	    TH1F *h_up = (TH1F*)in_file->Get(hNameUp);
	    if(!h_up) cout << "BAD HISTO: " << hNameUp << endl;

	    TString hNameDown = "h__";
	    hNameDown += genSys_var_labels[iSys+1];
	    hNameDown += "__";
	    hNameDown += classy_label;
	    hNameDown += "__";
	    hNameDown += hName_nominal_sys;
	    hNameDown += "__";
	    hNameDown += cat_label;

	    TH1F *h_down = (TH1F*)in_file->Get(hNameDown);
	    if(!h_down) cout << "BAD HISTO: " << hNameDown << endl;

	    double yield_nom  = h_stat->Integral(0,-1);
	  
	    double yield_up   = yield_nom*( 1.0 + ( (h_up->Integral(0,-1)-h_genWgtNom->Integral(0,-1))/h_genWgtNom->Integral(0,-1)) );
	    double percent_up = (100*(yield_up-yield_nom))/yield_nom;
	  
	    double yield_dn   = yield_nom*( 1.0 + ( (h_down->Integral(0,-1)-h_genWgtNom->Integral(0,-1))/h_genWgtNom->Integral(0,-1)) );
	    double percent_dn = (100*(yield_dn-yield_nom))/yield_nom;
	  
	    double maxDiff = fabs(yield_nom - yield_up);
	    maxDiff = std::max( maxDiff, fabs(yield_nom - yield_dn) );
	    double maxPercentDiff = (100*maxDiff)/yield_nom;
	  
	    TString sys_label_tex = genSys_var_tex.at(iSys);
	    sys_label_tex.ReplaceAll(",~Scale~Up","");
	    sys_label_tex.ReplaceAll(",~Scale~Down","");
	  
	    if(makeTexFiles){
	      fprintf(yFile, " $%s$ & ", sys_label_tex.Data() );
	      fprintf(yFile, " %.2f & ", yield_nom);
	      fprintf(yFile, " %.2f (%.2f) & ", yield_up, percent_up);
	      fprintf(yFile, " %.2f (%.2f) & ", yield_dn, percent_dn);
	      fprintf(yFile, " %.2f ", maxPercentDiff);
	     
	      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	    }

	    // Bin by Bin Systematic
	    for(int iBin=0; iBin<=(int)h_sys->GetNbinsX()+1; iBin++){
	     
	      double nom = h_sys->GetBinContent(iBin);
	      if( !(nom>0.0) ) continue;
	     
	      double currentErr = h_sys->GetBinError(iBin);
	      double currentErrSq = pow( currentErr, 2 );
	     
	      double thisErrSq = pow( fabs((nom*(1.0+(maxPercentDiff/100)))-nom), 2 );
	     
	      double errSq = currentErrSq + thisErrSq;
	      double err = sqrt( errSq );
	     
	      h_sys->SetBinError( iBin, err );
	     
	    } // end loop over bins
	   
	  } // end loop over additional systematics

	} // end if genweights exists for this sample 	
	*/

	//
	// Total Error
	//
	double err=0.0;
	double integral=h_stat->IntegralAndError(0,-1,err);
	if(verbose) cout << "        Integral +/- statErr, totErr = " << integral << " +/- " << err << ", ";
	err=0.0;
	integral = h_sys->IntegralAndError(0,-1,err);
	if(verbose) cout << err << endl << endl;
	
	if(makeTexFiles){  
	  fprintf(yFile, " Total Uncertainty & " );
	  fprintf(yFile, " %.2f & ", integral);
	  fprintf(yFile, " %.2f (%.2f) & ", integral+err, (100*(err))/integral);
	  fprintf(yFile, " %.2f (%.2f) & ", integral-err, (100*(err))/integral);
	  fprintf(yFile, " %.2f ", (100*(err))/integral);
	  
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

	  fprintf(yFile, "\\end{tabular} \n");
	  fprintf(yFile, "\\end{table} \n");
	  fprintf(yFile, "\\end{document} \n");
	  
	  fclose(yFile);
	}
	

      } // end loop over categories

      if(verbose) cout << endl;

    } // end loop over classifications

    if(verbose) cout << endl << endl;

  } // end loop over variables

  
  out_file->Write();
  out_file->Close();
  in_file->Close();
  
  return;
}
