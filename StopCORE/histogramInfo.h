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

//
// Namespace
//
namespace histogramInfo{

  const double EPS = 0.00001;

  //
  // Namespace functions
  //
  std::string getHistoLabel( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, categoryInfo::ID catId, systematicInfo::ID sysId );

  std::string getHistoTitle( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, categoryInfo::ID catId, systematicInfo::ID sysId );

  std::string getYieldHistoLabel( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, systematicInfo::ID sysId );

  std::string getYieldHistoTitle( std::string base, genClassyInfo::ID genClassyId, recoClassyInfo::ID recoClassyId, systematicInfo::ID sysId );


  // 
  // Utility Class for TH1 variables
  //
  class h1_Util{
    public:
      std::map< std::string, TH1D* > histos;
      
      std::string h_label_base;
      std::string h_title_base;

      int    h_nBins;
      double h_min;
      double h_max;
      
      genClassyInfo::vect_id  h_genClassy;
      recoClassyInfo::vect_id h_recoClassy;
      categoryInfo::vect_id   h_categories;
      systematicInfo::vect_id h_systematics;

      h1_Util( TFile *f_out, std::string label, std::string title, int nBins, double min, double max, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys );
      ~h1_Util(){};
      
      void fill( double value, genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts );

  };  


  //
  //  Utility Class for Yields
  //
  class h1_Yield_Util{
    public:
      std::map< std::string, TH1D* > histos;
      
      std::string h_label_base;
      std::string h_title_base;

      genClassyInfo::vect_id  h_genClassy;
      recoClassyInfo::vect_id h_recoClassy;
      categoryInfo::vect_id   h_categories;
      systematicInfo::vect_id h_systematics;

      h1_Yield_Util( TFile *f_out, std::string label, std::string title, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys );
      ~h1_Yield_Util(){};

      void fill( genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts );

  };


  
  // 
  // Utility Class for TH2 variables
  //
  class h2_Util{
    public:
      std::map< std::string, TH2D* > histos;
      
      std::string h_label_base;
      std::string h_title_base;

      int    h_nBins_x;
      double h_min_x;
      double h_max_x;

      int    h_nBins_y;
      double h_min_y;
      double h_max_y;
      
      genClassyInfo::vect_id  h_genClassy;
      recoClassyInfo::vect_id h_recoClassy;
      categoryInfo::vect_id   h_categories;
      systematicInfo::vect_id h_systematics;

      h2_Util( TFile *f_out, std::string label, std::string title, int nBins_x, double h_min_x, double h_max_x, int nBins_y, double h_min_y, double h_max_y, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys );
      ~h2_Util(){};

      void fill( double value_x, double value_y, genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts );

  };


  // 
  // Utility Class for TH3 variables
  //
  class h3_Util{
    public:
      std::map< std::string, TH3D* > histos;
      
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
      
      genClassyInfo::vect_id  h_genClassy;
      recoClassyInfo::vect_id h_recoClassy;
      categoryInfo::vect_id   h_categories;
      systematicInfo::vect_id h_systematics;

      h3_Util( std::string label, std::string title, int nBins_x, double h_min_x, double h_max_x, int nBins_y, double h_min_y, double h_max_y, int nBins_z, double h_min_z, double h_max_z, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys );
      ~h3_Util(){};

      void fill( double value_x, double value_y, double value_z, genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts );

  };  


  //
  //  Utiltility Class for Yields
  //
  class h3_Yield_Util{
    public:
      std::map< std::string, TH3D* > histos;
      
      std::string h_label_base;
      std::string h_title_base;

      int    h_nBins_x;
      double h_min_x;
      double h_max_x;
      
      int    h_nBins_y;
      double h_min_y;
      double h_max_y;
      
      genClassyInfo::vect_id  h_genClassy;
      recoClassyInfo::vect_id h_recoClassy;
      categoryInfo::vect_id   h_categories;
      systematicInfo::vect_id h_systematics;

      h3_Yield_Util( std::string label, std::string title, int nBins_x, double h_min_x, double h_max_x, int nBins_y, double h_min_y, double h_max_y, genClassyInfo::vect_id genClassys, recoClassyInfo::vect_id recoClassys, categoryInfo::vect_id cats, systematicInfo::vect_id sys );
      ~h3_Yield_Util(){};

      void fill( double value_x, double value_y, double value_z, genClassyInfo::vect_id_passBool pass_genClassy, recoClassyInfo::vect_id_passBool pass_recoClassy, categoryInfo::vect_id_passBool pass_cat, systematicInfo::vect_id_wgt sys_wgts );

  };  



}; // end namespace definition

#endif
