#ifndef histoHelper_H
#define histoHelper_H

// ROOT
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"

// std
#include <vector>

// stop analysis
#include "stop_1l_babyAnalyzer.h"


//
// Globals
//
const int nCats = 15;

//
// Utility Class
//

class histoHelper{
 
public:
 
  //
  // Event Categories
  //
  std::vector<TString> cat_titles;
  std::vector<TString> cat_labels;
  
  //
  // Bin Information
  //
  int nBins_nJets;
  double min_nJets;
  double max_nJets;
  
  int nBins_nTags;
  double min_nTags;
  double max_nTags;

  int nBins_met;
  double min_met;
  double max_met;

  int nBins_mt;
  double min_mt;
  double max_mt;

  int nBins_minDPhi;
  double min_minDPhi;
  double max_minDPhi;
  
  int nBins_chi2;
  double min_chi2;
  double max_chi2;

  int nBins_mt2w; 
  double min_mt2w; 
  double max_mt2w;

  int nBins_htRatio; 
  double min_htRatio; 
  double max_htRatio;

  // 
  // Declare Histogram Pointers
  //
  TH1D *h_nJets_[nCats];
  TH1D *h_nTags_[nCats];
  
  // Selection Vars
  TH1D *h_met_[nCats];
  TH1D *h_mt_[nCats];
  TH1D *h_minDPhi_lep_j1_j2_[nCats];
  TH1D *h_chi2_[nCats];
  TH1D *h_mt2w_[nCats];
 
  TH1D *h_htRatio_[nCats];
  //TH1D *h_pt_b1_[nCats];
  //TH1D *h_dR_lb_[nCats];
  //TH1D *h_met_over_sqrt_ht_[nCats];
  //TH1D *h_minDPhi_lW_[nCats];
  
  
  histoHelper(){

    cat_titles.push_back( "babyMaker Selection" ); // iCat==0
    cat_labels.push_back( "babyMakerSelection" ); // iCat==0

    cat_titles.push_back( "PreSelection" ); // iCat==1
    cat_labels.push_back( "preSelection" ); // iCat==1

    cat_titles.push_back( "PreSelection, MET>100" ); // iCat==2
    cat_labels.push_back( "preSelection__met_gt_100" ); // iCat==2

    cat_titles.push_back( "PreSelection, MET>100, M_{T}>120" ); // iCat==3
    cat_labels.push_back( "preSelection__met_gt_100__mt_gt_120" ); // iCat==3
 
    cat_titles.push_back( "PreSelection, MET>100, M_{T}>120, min#Delta#phi>0.8" ); // iCat==4
    cat_labels.push_back( "preSelection__met_gt_100__mt_gt_120__minDPhi_gt_0p8" ); // iCat==4

    cat_titles.push_back( "PreSelection, MET>100, M_{T}>120, min#Delta#phi>0.8, chi2<5.0" ); // iCat==5
    cat_labels.push_back( "preSelection__met_gt_100__mt_gt_120__minDPhi_gt_0p8__chi2_lt_5" ); // iCat==5

    cat_titles.push_back( "Baseline" ); // iCat==6
    cat_labels.push_back( "baseline" ); // iCat==6

    cat_titles.push_back( "Baseline, MET>150" ); // iCat==7
    cat_labels.push_back( "baseline__met_gt_150" ); // iCat==7

    cat_titles.push_back( "Baseline, MET>200" ); // iCat==8
    cat_labels.push_back( "baseline__met_gt_200" ); // iCat==8

    cat_titles.push_back( "Baseline, MET>250" ); // iCat==9
    cat_labels.push_back( "baseline__met_gt_250" ); // iCat==9

    cat_titles.push_back( "Baseline, MET>300" ); // iCat==10
    cat_labels.push_back( "baseline__met_gt_300" ); // iCat==10

    cat_titles.push_back( "Baseline, MET>150, MTW>200" ); // iCat==11
    cat_labels.push_back( "baseline__met_gt_150__mtw_gt_200" ); // iCat==11

    cat_titles.push_back( "Baseline, MET>200, MTW>200" ); // iCat==12
    cat_labels.push_back( "baseline__met_gt_200__mtw_gt_200" ); // iCat==12

    cat_titles.push_back( "Baseline, MET>250, MTW>200" ); // iCat==13
    cat_labels.push_back( "baseline__met_gt_250__mtw_gt_200" ); // iCat==13

    cat_titles.push_back( "Baseline, MET>300, MTW>200" ); // iCat==14
    cat_labels.push_back( "baseline__met_gt_300__mtw_gt_200" ); // iCat==14


    if( (int)cat_titles.size() != (int)cat_labels.size() ){
      cout << "ERROR IN CATEGORY LABELING!" << endl;
    }
    
    nBins_nJets = 11;
    min_nJets = -0.5;
    max_nJets = 10.5;
    
    nBins_nTags = 7;
    min_nTags = -0.5;
    max_nTags = 6.5;
    
    nBins_met = 100;
    min_met = 0.0;
    max_met = 500.0;
    
    nBins_mt = 100;
    min_mt = 0.0;
    max_mt = 500.0;
    
    nBins_minDPhi = 100;
    min_minDPhi = 0.0;
    max_minDPhi = 6.5;
    
    nBins_chi2 = 100;
    min_chi2 = 0.0;
    max_chi2 = 100;
    
    nBins_mt2w = 200; 
    min_mt2w = 0.0; 
    max_mt2w = 700.0;

    nBins_htRatio = 50; 
    min_htRatio = 0.0; 
    max_htRatio = 1.0;

    //
    // Histogram Contructors
    //
    for(int iCat=0; iCat<nCats; iCat++){

      // Event Vars
      h_nJets_[iCat] = new TH1D("h_nJets__"+cat_labels[iCat], "Number of Selected Jets, "+cat_titles[iCat]+";nJets;Events", nBins_nJets, min_nJets, max_nJets); 
      h_nTags_[iCat] = new TH1D("h_nTags__"+cat_labels[iCat], "Number of Selected Tags, "+cat_titles[iCat]+";nTags;Events", nBins_nTags, min_nTags, max_nTags); 

      // Selection Vars
      h_met_[iCat]= new TH1D("h_met__"+cat_labels[iCat], "Missing Transverse Energy, "+cat_titles[iCat]+";MET [GeV];Events", nBins_met, min_met, max_met);
      h_mt_[iCat]= new TH1D("h_mt__"+cat_labels[iCat], "Transverse W mass, "+cat_titles[iCat]+";M_{T} [GeV];Events", nBins_mt, min_mt, max_mt);
      h_minDPhi_lep_j1_j2_[iCat]= new TH1D("h_minDPhi_lep_j1_j2__"+cat_labels[iCat], "Minimum of #Delta#phi(MET, leading 2 jets), "+cat_titles[iCat]+";#Delta#phi [Rad];Events", nBins_minDPhi, min_minDPhi, max_minDPhi);
      h_chi2_[iCat]= new TH1D("h_chi2__"+cat_labels[iCat], "Minimum #Chi^{2}, Hadronic Top, "+cat_titles[iCat]+";min#Chi^{2};Events", nBins_chi2, min_chi2, max_chi2);
      h_mt2w_[iCat]= new TH1D("h_MT2W__"+cat_labels[iCat], "MT2W, "+cat_titles[iCat]+";MT2W;Events", nBins_mt2w, min_mt2w, max_mt2w);

      // Additional Discriminating Vars
      h_htRatio_[iCat] = new TH1D("h_htRatio__"+cat_labels[iCat], "H_{T} Ratio, "+cat_titles[iCat]+";H_{T} Ratio;Events", nBins_htRatio, min_htRatio, max_htRatio);

      
    } // end loop over categories
    
    
  } // end consturctor


  
  void fillHistos(int iCat=0, double wgt=1.0, double nJets=-99, double nTags=-99){

    //
    // Event vars
    //
    h_nJets_[iCat]->Fill( nJets, wgt );
    h_nTags_[iCat]->Fill( nTags, wgt );

    //
    // Selection vars
    //
    h_met_[iCat]->Fill(stop_1l::pfmet(), wgt );
    h_mt_[iCat]->Fill( stop_1l::mt_met_lep(), wgt );
    h_minDPhi_lep_j1_j2_[iCat]->Fill( stop_1l::mindphi_met_j1_j2(), wgt );
    h_chi2_[iCat]->Fill( stop_1l::chi2(), wgt );
    h_mt2w_[iCat]->Fill( stop_1l::MT2W(), wgt );

    //
    // Addtional discriminating vars
    //
    h_htRatio_[iCat]->Fill( stop_1l::ak4_htratiom(), wgt );


    return;

  } // end fillHistos    
    
  
};

#endif
