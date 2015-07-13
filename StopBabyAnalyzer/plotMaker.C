// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TColor.h"

// std
#include <vector>

// histoHelper
#include "histoHelper.h"

// dataMCplotMaker
#include "../../Software/dataMCplotMaker/dataMCplotMaker.cc"

//
// Main
//
void plotMaker(){

  //
  // Open Files
  //

  // vector for kColors, list backgrounds first then signal
  std::vector<Color_t> colors; 

  std::vector<TFile*> bkg_files;
  std::vector<std::string> bkg_file_names;
  std::vector<std::string> bkg_file_names_tex;

  std::vector<TFile*> sig_files;
  std::vector<std::string> sig_file_names;
  std::vector<std::string> sig_file_names_tex;
  
  //
  // data
  //


  //
  // backgrounds
  //
  TString inDir = "Histos/";
  
  TString outDir = "Plots/";
  
  // ttbar_1l
  TFile *f_ttbar_1l = new TFile(inDir+"histos__ttbar_1l.root", "read");
  bkg_file_names.push_back("t#bar{t}, 1l");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 1l");
  bkg_files.push_back(f_ttbar_1l);
  colors.push_back(kRed-7);

  // ttbar_2l
  TFile *f_ttbar_2l = new TFile(inDir+"histos__ttbar_2l.root", "read");
  bkg_file_names.push_back("t#bar{t}, 2l");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 2l");
  bkg_files.push_back(f_ttbar_2l);
  colors.push_back(kCyan-3);
 
  // singleT
  TFile *f_singleT = new TFile(inDir+"histos__singleT.root", "read");
  bkg_file_names.push_back("Single t");
  bkg_file_names_tex.push_back("Single $t$");
  bkg_files.push_back(f_singleT);
  colors.push_back(kYellow+1);

  // W+Jets
  TFile *f_wJets = new TFile(inDir+"histos__wjets.root", "read");
  bkg_file_names.push_back("W+Jets");
  bkg_file_names_tex.push_back("$W$+Jets");
  bkg_files.push_back(f_wJets);
  colors.push_back(kOrange-2);

  // Rare (all others)
  TFile *f_rare = new TFile(inDir+"histos__rare.root", "read");
  bkg_file_names.push_back("Rare");
  bkg_file_names_tex.push_back("$Rare$");
  bkg_files.push_back(f_rare);
  colors.push_back(kMagenta-5);

  //
  // signals
  //
  double sig_SF = 100.0;

  TFile *f_stop_850_100 = new TFile(inDir+"histos__stop_850_100.root", "read");
  sig_file_names.push_back("T2tt(850,100)x100");
  sig_file_names_tex.push_back("T2tt(850,100)");
  sig_files.push_back(f_stop_850_100);
  colors.push_back(kBlue);
  

  TFile *f_stop_425_325 = new TFile(inDir+"histos__stop_425_325.root", "read");
  sig_file_names.push_back("T2tt(425,325)x100");
  sig_file_names_tex.push_back("T2tt(425,325)");
  sig_files.push_back(f_stop_425_325);
  colors.push_back(kGreen);

  TFile *f_stop_500_325 = new TFile(inDir+"histos__stop_500_325.root", "read");
  sig_file_names.push_back("T2tt(500,325)x100");
  sig_file_names_tex.push_back("T2tt(500,325)");
  sig_files.push_back(f_stop_500_325);
  colors.push_back(kMagenta+2);

  TFile *f_stop_650_325 = new TFile(inDir+"histos__stop_650_325.root", "read");
  sig_file_names.push_back("T2tt(650,325)x100");
  sig_file_names_tex.push_back("T2tt(650,325)");
  sig_files.push_back(f_stop_650_325);
  colors.push_back(kOrange+7);
  
  // Dummy file, since there exists a weird problem where the integral
  // of the histograms from the last file are all 0
  TFile *f_dummy = new TFile("Plots/f_dummy.root", "recreate");
 
  //
  // Variables to plot
  //
  std::vector<std::string> var_list_label;
  std::vector<std::string> var_list_title;
  std::vector<std::string> var_list_xaxis;

  // nJets
  var_list_label.push_back("nJets");
  var_list_title.push_back("Number of Jets");
  var_list_xaxis.push_back("nJets");
  
  // nTags
  var_list_label.push_back("nTags");
  var_list_title.push_back("Number of Tags");
  var_list_xaxis.push_back("nTags");

  // MET
  var_list_label.push_back("met");
  var_list_title.push_back("MET");
  var_list_xaxis.push_back("MET");

  // MT
  var_list_label.push_back("mt");
  var_list_title.push_back("M_{T}");
  var_list_xaxis.push_back("M_{T}");
  
  // minChi2
  var_list_label.push_back("chi2");
  var_list_title.push_back("min #Chi^{2}, Hadronic Top");
  var_list_xaxis.push_back("min #Chi^{2}");

  // MT2W
  var_list_label.push_back("MT2W");
  var_list_title.push_back("MT2W");
  var_list_xaxis.push_back("MT2W");

  

  //
  // histoHelper for categories
  //
  histoHelper histoHelper_forCats;
  
  //
  // Loop over files and grab histograms
  //
  for(int iVar=0; iVar<(int)var_list_label.size(); iVar++){

    for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
      std::string cat_title_for_subtitle = "";
      cat_title_for_subtitle += histoHelper_forCats.cat_titles[iCat];

      // Backgrounds
      std::vector<TH1F*> bkg_histos;
      for(int iFile=0; iFile<(int)bkg_files.size(); iFile++){
	
	TString hName = "h_";
	hName += var_list_label[iVar];
	hName += "__";
	hName += histoHelper_forCats.cat_labels[iCat];

	TString hName_clone = hName;
	hName_clone += "__bkg_";
	hName_clone += iFile;
	
	TH1F* h_temp = (TH1F*)bkg_files[iFile]->Get(hName);
	if(!h_temp) cout << "BAD BKG HISTO: " << hName << endl;
	TH1F *h = (TH1F*)h_temp->Clone(hName_clone);
	bkg_histos.push_back(h);
		
      } // end loop over files
    
       // Signal
      std::vector<TH1F*> sig_histos;
      for(int iFile=0; iFile<(int)sig_files.size(); iFile++){
     
	TString hName = "h_";
	hName += var_list_label[iVar];
	hName += "__";
	hName += histoHelper_forCats.cat_labels[iCat];
	
	TString hName_clone = hName;
	hName_clone +="__sig_";
	hName_clone += iFile;

	TH1F* h_temp = (TH1F*)sig_files[iFile]->Get(hName);
	if(!h_temp) cout << "BAD SIG HISTO: " << hName << endl;
	TH1F *h = (TH1F*)h_temp->Clone(hName_clone);
	h->Scale(sig_SF);
	sig_histos.push_back(h);
	
      } // end loop over files
      

      // data
      TH1F *h_null = new TH1F("","",1,0,1);

      
      // Option String 
     std::string options = "";

      options += "--outputName ";
      options += outDir;
      options += "data_MC_plot__";
      options += var_list_label[iVar];
      options += "__";
      options += histoHelper_forCats.cat_labels[iCat];
      options += ".pdf  ";
      
      options += "--xAxisLabel ";
      options += var_list_xaxis[iVar];
      options += "  ";
      
      options += "--legendRight -0.10  ";

      options += "--energy 13  ";

      options += "--lumi 10.0  ";

      options += "--preserveBackgroundOrder  ";
      options += "--preserveSignalOrder  ";

      options += "--noOverflow ";


      dataMCplotMaker(h_null, bkg_histos, bkg_file_names, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_file_names, colors);
      

      // Clean up
      h_null->~TH1F();

    } // end loop over categories

  } // end loop over vars
      

  //
  // Make Tables
  //
  FILE *yFile;
  TString texFile = "Plots/yieldTable_stop_1l.tex";
  yFile = fopen(texFile.Data(), "w");

  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\begin{document}\n");
  //fprintf(yFile, "\\small\n");
  fprintf(yFile, "\\tiny\n");

  // Get number of collumns for table - ie categories
  fprintf(yFile, "\\begin{tabular}{|l|");
  for(int iSig=0; iSig<(int)sig_file_names_tex.size(); iSig++){
    fprintf(yFile,"c|");
  }
  for(int iBkg=0; iBkg<(int)bkg_file_names_tex.size(); iBkg++){
    fprintf(yFile,"c|");
  }
  fprintf(yFile, "} \\hline \n");

  // Title for signals and backgrounds
  for(int iSig=0; iSig<(int)sig_file_names_tex.size(); iSig++){
    fprintf(yFile,"& %s", sig_file_names_tex[iSig].c_str());
  }
  for(int iBkg=0; iBkg<(int)bkg_file_names_tex.size(); iBkg++){
    fprintf(yFile,"& %s", bkg_file_names_tex[iBkg].c_str());
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");


  // Loop over catogories
  for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
      std::string cat_title_for_subtitle = "";
      cat_title_for_subtitle += histoHelper_forCats.cat_titles[iCat];
      
      TString cat_title_tex =  histoHelper_forCats.cat_titles[iCat];
      cat_title_tex.ReplaceAll("#", "\\");
      fprintf(yFile,"$%s$ & ",cat_title_tex.Data());

      // Signal Yields
      for(int iSig=0; iSig<(int)sig_files.size(); iSig++){
	TString hName = "h_MT2W__";
	hName += histoHelper_forCats.cat_labels[iCat];

	TString hName_clone = hName;
	hName_clone += "__sig_";
	hName_clone += iSig;
	
	TH1D* h_temp = (TH1D*)sig_files[iSig]->Get(hName);
	if(!h_temp) cout << "BAD SIG HISTO: " << hName << endl;
	
	// Signal Yields
	fprintf(yFile, " %.4f & ", h_temp->Integral() );
	
      } // end loop over signals

      // Background Yields
      for(int iBkg=0; iBkg<(int)bkg_files.size(); iBkg++){
	TString hName = "h_MT2W__";
	hName += histoHelper_forCats.cat_labels[iCat];

	TString hName_clone = hName;
	hName_clone += "__bkg_";
	hName_clone += iBkg;
	
	TH1D* h_temp = (TH1D*)bkg_files[iBkg]->Get(hName);
	if(!h_temp) cout << "BAD BKG HISTO: " << hName << endl;
	
	// Background Yields
	if( iBkg+1 == (int)bkg_files.size() ){ 
	  fprintf(yFile, " %.4f ", h_temp->Integral() );
	}
	else fprintf(yFile, " %.4f & ", h_temp->Integral() );
	  
      } // end loop over bkgs
            
      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
      
  } // end loop over categories
  
  fprintf(yFile, "\\end{tabular} \n");
  fprintf(yFile, "\\end{document} \n");

  fclose(yFile);

      
  
  //
  // Clean up
  //
  for(int iBkg=0; iBkg<(int)bkg_files.size(); iBkg++){
    bkg_files[iBkg]->Close();
  }
  for(int iSig=0; iSig<(int)sig_files.size(); iSig++){
    sig_files[iSig]->Close();
  }
  f_dummy->Close();
  
  return;
}
