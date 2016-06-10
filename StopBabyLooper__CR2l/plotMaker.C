// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TColor.h"

// std
#include <algorithm>
#include <string>
#include <vector>

#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"

// dataMCplotMaker
#include "../../Software/dataMCplotMaker/dataMCplotMaker.cc"

//
// Main
//
void plotMaker( bool plotByGenDecay=true ){

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  //
  // Intialize User Inputs
  //
  bool plotData  = true;
  
  TString inDir  = "Histos/Nominal/";
  TString outDir = "Output/Plots/";

  TString outExt = ".pdf";
  
  //double lumi    = 5.0; // for studies
  double lumi    = 2.26; // 2015, final lumi
  
  double sig_SF  = 1.0;


  //
  // Analyzer Type
  //
  analyzerInfo::ID analysis = analyzerInfo::k_CR2l;

  
  //
  // Gen Classifications
  //
  genClassyInfo::genClassyUtil gen_incl( genClassyInfo::k_incl );
  TString hName_incl = gen_incl.label;

  genClassyInfo::genClassyUtil gen_ee1lep( genClassyInfo::k_ee1lep );
  TString hName_1lep = gen_ee1lep.label;

  genClassyInfo::genClassyUtil gen_ge2lep( genClassyInfo::k_ge2lep );
  TString hName_2lep = gen_ge2lep.label;

  genClassyInfo::genClassyUtil gen_ZtoNuNu( genClassyInfo::k_ZtoNuNu );
  TString hName_ZtoNuNu = gen_ZtoNuNu.label;

  
  //
  // Reco Classification
  //
  recoClassyInfo::recoClassyUtil reco_incl( recoClassyInfo::k_incl );
  TString hName_reco_incl = reco_incl.label;

  
  //
  // Nominal Systematic Label
  //
  systematicInfo::systematicUtil sys_nominal( systematicInfo::k_nominal );
  TString hName_nominal_sys = sys_nominal.label;
  
   
  //
  // Utility Vars
  //
  std::pair< sampleInfo::ID, genClassyInfo::ID > sample;

  std::vector<Color_t> colors; // order as bkg, then signal


  //
  // data
  //
  std::pair< sampleInfo::ID, genClassyInfo::ID > sample_data;
  sample_data.first  = sampleInfo::k_single_lepton_met_2015CD;
  sample_data.second = genClassyInfo::k_incl;
 

  //
  // Bkgs
  //
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > bkgList;

  if(plotByGenDecay){
    
    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ZtoNuNu;
    bkgList.push_back(sample);
    colors.push_back( kMagenta-5 );

    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ee1lep_fromTop;
    bkgList.push_back(sample);
    colors.push_back( kRed-7 );

    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ee1lep_fromW;
    bkgList.push_back(sample);
    colors.push_back( kOrange-2 );

    sample.first  = sampleInfo::k_allBkg; 
    sample.second = genClassyInfo::k_ge2lep;
    bkgList.push_back(sample);
    colors.push_back( kCyan-3 );

  } // end if plot by genDecay
  else{
    
    sample.first  = sampleInfo::k_rare; 
    sample.second = genClassyInfo::k_incl;
    bkgList.push_back(sample);
    colors.push_back( kMagenta-5 );

    sample.first  = sampleInfo::k_VJets; 
    sample.second = genClassyInfo::k_incl;
    bkgList.push_back(sample);
    colors.push_back( kGreen-3 );

    sample.first  = sampleInfo::k_singleT; 
    sample.second = genClassyInfo::k_incl;
    bkgList.push_back(sample);
    colors.push_back(kOrange-2);
   
    sample.first  = sampleInfo::k_ttbar; 
    sample.second = genClassyInfo::k_ee1lep;
    bkgList.push_back(sample);
    colors.push_back( kRed-7 );

    sample.first  = sampleInfo::k_ttbar; 
    sample.second = genClassyInfo::k_ge2lep;
    bkgList.push_back(sample);
    colors.push_back( kCyan-3 );

  }


  //
  // Signals
  //
  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sigList;
 
  sample.first  = sampleInfo::k_T2tt;
  sample.second = genClassyInfo::k_incl;
  sigList.push_back( sample );

  // T2tt mass points
  std::vector< std::pair< double, double > > T2tt_list;
  std::pair< double, double > T2tt_mass_point;
    
  T2tt_mass_point.first  = 400;
  T2tt_mass_point.second = 225;
  T2tt_list.push_back( T2tt_mass_point );
  colors.push_back( kGreen );

  T2tt_mass_point.first  = 500;
  T2tt_mass_point.second = 325;
  T2tt_list.push_back( T2tt_mass_point );
  colors.push_back( kMagenta+2 );

  T2tt_mass_point.first  = 800;
  T2tt_mass_point.second = 350;
  T2tt_list.push_back( T2tt_mass_point );
  colors.push_back( kOrange+7 );

  T2tt_mass_point.first  = 800;
  T2tt_mass_point.second = 100;
  T2tt_list.push_back( T2tt_mass_point );
  colors.push_back( kBlue );

  
  // Dummy file, since there exists a weird problem where the integral
  // of the histograms from the last file are all 0
  //TFile *f_dummy = new TFile(outDir+"f_dummy.root", "recreate");
 
  
  //
  // Variables to plot
  //
  std::vector< std::vector< systematicInfo::systematicUtil > > sysList;
  std::vector< systematicInfo::systematicUtil > sysListPerPlot;  // Must add Up and Down Variations for a single systematic

  std::vector< std::vector< categoryInfo::categoryUtil > > catList;
  std::vector< categoryInfo::categoryUtil > catListPerPlot;
  
  std::vector<std::string> var_list_label;
  std::vector<std::string> var_list_title;
  std::vector<std::string> var_list_xaxis;


  // Plot Yields
  var_list_label.push_back( "yields" );
  var_list_title.push_back( "Yields" );
  var_list_xaxis.push_back( "Yields" );

  sysListPerPlot.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();


  // Plot nJets
  var_list_label.push_back( "nJets" );
  var_list_title.push_back( "Number of Jets" );
  var_list_xaxis.push_back( "nJets" );
  
  sysListPerPlot.push_back( systematicInfo::systematicUtil(systematicInfo::k_nominal) );
  sysList.push_back( sysListPerPlot );
  sysListPerPlot.clear();
  
  catListPerPlot.push_back( categoryInfo::categoryUtil(categoryInfo::k_incl) );
  catList.push_back( catListPerPlot );
  catListPerPlot.clear();


  
  //
  // Loop over files and grab histograms
  //
  TString hName = "";
  TString hName_clone = "";
  
  TH1F *h_data      = new TH1F("","",1,0,1);
  TH1F *h_temp      = NULL;
  TH1F *h_temp_up   = NULL;
  TH1F *h_temp_dn   = NULL;
  TH1F *h_clone     = NULL;
  TH1F *h_clone_unc = NULL;
  TH3D *h3_temp     = NULL;
  
  for(int iVar=0; iVar<(int)var_list_label.size(); iVar++){
    
    bool isYieldPlot = false;
    std::size_t foundYield = var_list_label[iVar].find("yields");
    if( foundYield!=std::string::npos ) isYieldPlot=true;

    for(int iCat=0; iCat<(int)catList[iVar].size(); iCat++){

      categoryInfo::categoryUtil category( catList[iVar][iCat] );
      std::string cat_title_for_subtitle = "";

      if( !isYieldPlot ) cat_title_for_subtitle += category.title;
      

      // Get Data Data;
      TFile *f_data = NULL;
      if(plotData){
	sampleInfo::sampleUtil data_util( sample_data.first );

	TString f_name = inDir;
	f_name += "h__";
	f_name += data_util.label;
	f_name += ".root";
	f_data = new TFile( f_name.Data(), "read" );
	
	if( isYieldPlot ){
	  hName = histogramInfo::getYieldHistoLabel( var_list_label[iVar], genClassyInfo::genClassyUtil(sample_data.second), reco_incl, sys_nominal );
	}
	else{
	  hName = histogramInfo::getHistoLabel( var_list_label[iVar], genClassyInfo::genClassyUtil(sample_data.second), reco_incl, category, sys_nominal );
	}

	hName_clone = hName;
	hName_clone += "__data";

	h_temp = (TH1F*)f_data->Get(hName);
	if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;

	h_data = (TH1F*)h_temp->Clone(hName_clone);
      }

      // Backgrounds
      std::vector<TFile*> bkg_files;
      std::pair<TH1F*,TH1F*> bkg_and_unc;
      std::vector< std::pair<TH1F*,TH1F*> > bkg_histos;
      std::vector<std::string> bkg_titles;
      for(int iBkg=0; iBkg<(int)bkgList.size(); iBkg++){

	sampleInfo::sampleUtil background( bkgList[iBkg].first );
	genClassyInfo::genClassyUtil genClassification( bkgList[iBkg].second );

	TString f_name = inDir;
	f_name += "h__";
	f_name += background.label;
	f_name += ".root";
	TFile *f_bkg = new TFile( f_name.Data(), "read" );
	bkg_files.push_back(f_bkg);

	if( isYieldPlot ){
	  hName = histogramInfo::getYieldHistoLabel( var_list_label[iVar], genClassification, reco_incl, sys_nominal );
	}
	else{
	  hName = histogramInfo::getHistoLabel( var_list_label[iVar], genClassification, reco_incl, category, sys_nominal );
	}

	hName_clone = hName;
	hName_clone += "__";
	hName_clone += background.label;

	
	h_temp = (TH1F*)f_bkg->Get(hName);
	if(!h_temp) cout << "BAD BKG HISTO: " << hName << endl;
	h_clone = (TH1F*)h_temp->Clone(hName_clone);
	
	bkg_and_unc.first = h_clone;
	
	h_clone_unc = (TH1F*)h_clone->Clone(hName_clone+"__unc");
	if( (int)sysList[iVar].size()==1 ){
	  bkg_and_unc.second = h_clone_unc;
	}
	else{
	  
	  for(int iSys=0; iSys<(int)sysList[iVar].size(); iSys+=2){
	    
	    // Get Up Variation
	    if( isYieldPlot ){
	      hName = histogramInfo::getYieldHistoLabel( var_list_label[iVar], genClassification, reco_incl, sysList[iVar][iSys] );
	    }
	    else{
	      hName = histogramInfo::getHistoLabel( var_list_label[iVar], genClassification, reco_incl, category, sysList[iVar][iSys] );
	    }
	    h_temp_up = (TH1F*)f_bkg->Get(hName);

	    // Get Down Variation
	    if( isYieldPlot ){
	      hName = histogramInfo::getYieldHistoLabel( var_list_label[iVar], genClassification, reco_incl, sysList[iVar][iSys+1] );
	    }
	    else{
	      hName = histogramInfo::getHistoLabel( var_list_label[iVar], genClassification, reco_incl, category, sysList[iVar][iSys+1] );
	    }
	    h_temp_dn = (TH1F*)f_bkg->Get(hName);
	    
	    for(int iBin=1; iBin<=(int)h_temp_up->GetNbinsX(); iBin++){
	      double nom_val    = h_clone_unc->GetBinContent(iBin);
	      double nom_err    = h_clone_unc->GetBinError(iBin);
	      double nom_err_sq = pow( nom_err, 2 );

	      double up_val = h_temp_up->GetBinContent(iBin);
	      double dn_val = h_temp_dn->GetBinContent(iBin);
	      
	      double max_diff = fabs(nom_val-up_val);
	      max_diff = std::max( max_diff, fabs(nom_val-dn_val) );

	      nom_err_sq += max_diff;
	      nom_err     = sqrt(nom_err_sq);

	      h_clone_unc->SetBinError(iBin,nom_err);
	    } // end loop over bins
		
	  } // end loop over sys
	  
	  bkg_and_unc.second = h_clone_unc;

	} // end if more than 1 systematic

	bkg_histos.push_back(bkg_and_unc);

	if(plotByGenDecay) bkg_titles.push_back(genClassification.title);
	else{
	  std::string bkg_title = "";
	  bkg_title += background.title;
	  if( genClassification.id!=genClassyInfo::k_incl ){
	    bkg_title += ", ";
	    bkg_title += genClassification.title;
	  }
	  bkg_titles.push_back(bkg_title);
	}

      } // end loop over files

      
      // Signal
      std::vector<TFile*> sig_files;
      std::vector<TH1F*> sig_histos;
      std::vector<std::string> sig_titles;
      for(int iSig=0; iSig<(int)sigList.size(); iSig++){

	sampleInfo::sampleUtil signal( sigList[iSig].first );

	TString f_name = inDir;
	f_name += "h__";
	f_name += signal.label;
	f_name += ".root";
	TFile *f_sig = new TFile( f_name.Data(), "read" );
	sig_files.push_back(f_sig);

	if( isYieldPlot ){
	  hName = histogramInfo::getYieldHistoLabel( var_list_label[iVar], genClassyInfo::genClassyUtil(sigList[iSig].second), reco_incl, sys_nominal );
	}
	else{
	  hName = histogramInfo::getHistoLabel( var_list_label[iVar], genClassyInfo::genClassyUtil(sigList[iSig].second), reco_incl, category, sys_nominal );
	}
	
	if( signal.isSignalScan ){

	  std::vector< std::pair< double, double > > massPtList;
	  if( signal.id==sampleInfo::k_T2tt ) massPtList = T2tt_list;

	  for(int iMassPt=0; iMassPt<(int)massPtList.size(); iMassPt++){
	    
	    int mStop = massPtList[iMassPt].first;
	    int mLSP  = massPtList[iMassPt].second;
	
	    hName_clone = hName;
	    hName_clone += "__mStop_";
	    hName_clone += mStop;
	    hName_clone += "__mLSP_";
	    hName_clone += mLSP;

	    h3_temp = (TH3D*)f_sig->Get(hName);
	    if(!h3_temp) cout << "BAD SIG HISTO: " << hName << endl;
	    TH1D *h1_temp  = histogramInfo::getProjectionZ( mStop, mLSP, h3_temp );
	    
	    if(!h1_temp) cout << "BAD SIG HISTO: " << hName << endl;
	    h_clone = (TH1F*)h1_temp->Clone(hName_clone);
	    sig_histos.push_back(h_clone);

	    TString sig_title_temp = "";
	    sig_title_temp += signal.title;
	    sig_title_temp += " ";
	    sig_title_temp += mStop;
	    sig_title_temp += ", ";
	    sig_title_temp += mLSP;
	    std::string sig_title = sig_title_temp.Data();
	    sig_titles.push_back( sig_title );

	  } // end loop over mass points

	} // end if signal scan
	else{

	  hName_clone = hName;
	  hName_clone += "__";
	  hName_clone += signal.label;
	
	  h_temp = (TH1F*)f_sig->Get(hName);
	  if(!h_temp) cout << "BAD SIG HISTO: " << hName << endl;
	  h_clone = (TH1F*)h_temp->Clone(hName_clone);
	  sig_histos.push_back(h_clone);
	  sig_titles.push_back(signal.title);
	}
		
      } // end loop over signal samples
      
      
      // Option String, Log Scale Plot
      std::string options = "";

      options += "--outputName ";
      options += outDir;
      options += "data_MC_plot";
      if(plotByGenDecay) options  += "__byGenDecayMode__";
      else                options += "__byProductionMode__";
      options += var_list_label[iVar];
      options += "__";
      options += category.label;
      options += "__logScale";
      options += outExt;
      options += "  ";

      options += "--xAxisLabel ";
      options += var_list_xaxis[iVar];
      options += "  ";

      options += "--noXaxisUnit  ";
      
      options += "--legendRight -0.12  ";
      options += "--legendUp 0.05  ";

      options += "--energy 13  ";

      options += "--lumiPrec 1  ";

      options += "--lumi ";
      options += Form("%.1f  ", lumi);
      
      options += "--preserveBackgroundOrder  ";
      options += "--preserveSignalOrder  ";

      options += "--errHistAtBottom  ";

      options += "--outOfFrame ";
      
      options += "--type Preliminary  ";
      //options += "--type Simulation  ";


      dataMCplotMaker(h_data, bkg_histos, bkg_titles, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_titles, colors);
      

      // Option String, Linear Scale Plot
      options = "";
      
      options += "--outputName ";
      options += outDir;
      options += "data_MC_plot";
      if(plotByGenDecay) options  += "__byGenDecayMode__";
      else                options += "__byProductionMode__";
      options += var_list_label[iVar];
      options += "__";
      options += category.label;
      options += "__linScale";
      options += outExt;
      options += "  ";
      
      options += "--xAxisLabel ";
      options += var_list_xaxis[iVar];
      options += "  ";

      options += "--noXaxisUnit ";
      
      options += "--legendRight -0.12  ";
      options += "--legendUp 0.05  ";

      options += "--energy 13  ";

      options += "--lumiPrec 1  ";
      
      options += "--lumi ";
      options += Form("%.1f  ", lumi);
      
      options += "--preserveBackgroundOrder  ";
      options += "--preserveSignalOrder  ";

      options += "--errHistAtBottom  ";

      options += "--outOfFrame ";

      options += "--isLinear ";

      options += "--yTitleOffset -0.3  ";
      
      options += "--type Preliminary  ";
      //options += "--type Simulation  ";
      
      dataMCplotMaker(h_data, bkg_histos, bkg_titles, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_titles, colors);



      //
      // Clean up
      //
      if(plotData){
	f_data->Close();
	f_data->~TFile();
      }
      
      for(int iBkg=0; iBkg<(int)bkg_files.size(); iBkg++){
	bkg_files[iBkg]->Close();
	bkg_files[iBkg]->~TFile();
      }
      
      for(int iSig=0; iSig<(int)sig_files.size(); iSig++){
	sig_files[iSig]->Close();
	sig_files[iSig]->~TFile();
      }

      //f_dummy->Close();

     
    } // end loop over categories

    
  } // end loop over vars
      


  return;
}
