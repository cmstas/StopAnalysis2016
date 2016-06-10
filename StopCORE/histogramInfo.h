#ifndef histogramInfo_H
#define histogramInfo_H

// stopCORE
#include "genClassyInfo.h"
#include "recoClassyInfo.h"
#include "categoryInfo.h"
#include "systematicInfo.h"

// C
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>

//
// Namespace
//
namespace histogramInfo{

  const int nSys_        = systematicInfo::k_nSys;
  const int nGenClassy_  = genClassyInfo::k_nGenClassy;
  const int nRecoClassy_ = recoClassyInfo::k_nRecoClassy;
  const int nCats_       = categoryInfo::k_nCats;

  const int nHists_      = nSys_ * nGenClassy_ * nRecoClassy_ * nCats_;
  const int nYieldHists_ = nSys_ * nGenClassy_ * nRecoClassy_;

  const double EPS = 0.00001;

  //
  // Namespace functions
  //
  std::string getHistoLabel( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, categoryInfo::categoryUtil cat, systematicInfo::systematicUtil sys );

  std::string getHistoTitle( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, categoryInfo::categoryUtil cat, systematicInfo::systematicUtil sys );

  std::string getYieldHistoLabel( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, systematicInfo::systematicUtil sys );

  std::string getYieldHistoTitle( std::string base, genClassyInfo::genClassyUtil genClassy, recoClassyInfo::recoClassyUtil recoClassy, systematicInfo::systematicUtil sys );

  int getHistoIndex( systematicInfo::ID sys, genClassyInfo::ID genClassy, recoClassyInfo::ID recoClassy, categoryInfo::ID cat );
  
  int getYieldHistoIndex( systematicInfo::ID sys, genClassyInfo::ID genClassy, recoClassyInfo::ID recoClassy );

  TH1D* getProjectionZ( double valX, double valY, TH3D *h3 );


  // 
  // Utility Class for TH1 variables
  //
  class h1_Util{
    public:
      TH1D* histos[ nHists_ ];
      
      std::string h_label_base;
      std::string h_title_base;

      int    h_nBins;
      double h_min;
      double h_max;
      
      genClassyInfo::vect_util  h_genClassy;
      recoClassyInfo::vect_util h_recoClassy;
      categoryInfo::vect_util   h_categories;
      systematicInfo::vect_util h_systematics;
      
      h1_Util( TFile *f_out, std::string label, std::string title, int nBins, double min, double max, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys );
      ~h1_Util(){};
           
  };  


  //
  //  Utility Class for Yields
  //
  class h1_Yield_Util{
    public:
      TH1D* histos[ nYieldHists_ ];

      std::string h_label_base;
      std::string h_title_base;

      genClassyInfo::vect_util  h_genClassy;
      recoClassyInfo::vect_util h_recoClassy;
      categoryInfo::vect_util   h_categories;
      systematicInfo::vect_util h_systematics;
      
      h1_Yield_Util( TFile *f_out, std::string label, std::string title, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys );
      ~h1_Yield_Util(){};

  };


  
  // 
  // Utility Class for TH2 variables
  //
  class h2_Util{
    public:
      TH2D* histos[ nHists_ ];

      std::string h_label_base;
      std::string h_title_base;

      int    h_nBins_x;
      double h_min_x;
      double h_max_x;

      int    h_nBins_y;
      double h_min_y;
      double h_max_y;
      
      genClassyInfo::vect_util  h_genClassy;
      recoClassyInfo::vect_util h_recoClassy;
      categoryInfo::vect_util   h_categories;
      systematicInfo::vect_util h_systematics;

      h2_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double h_min_x, double h_max_x, int nBins_y, double h_min_y, double h_max_y, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys );
      ~h2_Util(){};

  };


  // 
  // Utility Class for TH3 variables
  //
  class h3_Util{
    public:
      TH3D* histos[ nHists_ ];

      std::string h_label_base;
      std::string h_title_base;

      int    h_nBins_x;
      double h_min_x;
      double h_max_x;
      
      int    h_nBins_y;
      double h_min_y;
      double h_max_y;

      int    h_nBins_z;
      double h_min_z;
      double h_max_z;
      
      genClassyInfo::vect_util  h_genClassy;
      recoClassyInfo::vect_util h_recoClassy;
      categoryInfo::vect_util   h_categories;
      systematicInfo::vect_util h_systematics;

      h3_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double h_min_x, double h_max_x, int nBins_y, double h_min_y, double h_max_y, int nBins_z, double h_min_z, double h_max_z, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys );
      ~h3_Util(){};
      
  };  


  //
  //  Utiltility Class for Yields
  //
  class h3_Yield_Util{
    public:
      TH3D* histos[ nYieldHists_ ];

      std::string h_label_base;
      std::string h_title_base;

      int    h_nBins_x;
      double h_min_x;
      double h_max_x;
      
      int    h_nBins_y;
      double h_min_y;
      double h_max_y;
      
      genClassyInfo::vect_util  h_genClassy;
      recoClassyInfo::vect_util h_recoClassy;
      categoryInfo::vect_util   h_categories;
      systematicInfo::vect_util h_systematics;

      h3_Yield_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double h_min_x, double h_max_x, int nBins_y, double h_min_y, double h_max_y, genClassyInfo::vect_util genClassys, recoClassyInfo::vect_util recoClassys, categoryInfo::vect_util cats, systematicInfo::vect_util sys );
      ~h3_Yield_Util(){};

  };  



}; // end namespace definition

#endif
