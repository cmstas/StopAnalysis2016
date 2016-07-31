#ifndef sampleInfo_h
#define sampleInfo_h

// stopCORE
#include "analyzerInfo.h"

// C
#include <string>
#include <vector>
#include <utility>


//
// Namespace 
//
namespace sampleInfo{

  //
  // Namespace utility vars
  //
  const std::string baby_inputDir_nominal = "/nfs-7/userdata/stopRun2/stop_babies__CMS3_V080005__BabyMaker_V0800X_v8__20160729/"; // 12.9/fb with btag, ICHEP lep sfs
  //const std::string baby_inputDir_nominal = "/nfs-7/userdata/stopRun2/stop_babies__CMS3_V080005__BabyMaker_V0800X_v7__20160722/"; // 12.9/fb with btag, lep sfs
  //const std::string baby_inputDir_nominal = "/nfs-7/userdata/stopRun2/stop_babies__CMS3_V080005__BabyMaker_V0800X_v6__20160718__mergedWithHistos/"; // 7.65/fb with btag sfs, and includes vars adding lepton to met
  //const std::string baby_inputDir_nominal  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V080005__BabyMaker_V0800X_v6__20160715/merged_files/";  // 7.65/fb with btag sfs, and includes vars adding lepton to met
  //const std::string baby_inputDir_nominal  = "/nfs-6/userdata/mliu/onelepbabies/V80_7p65_v2/";  // 7.65/fb with btag sfs, from mia
  //const std::string baby_inputDir_nominal  = "/nfs-7/userdata/stopRun2/stop_babies__CMS3_V080005__BabyMaker_V0800X_v4__20160710/"; // 7.65/fb no btag sfs
  const std::string baby_inputDir_jesUp    = "/nfs-7/userdata/stopRun2/stop_babies__JESup__CMS3_V080005__BabyMaker_V0800X_v8__20160729/";
  const std::string baby_inputDir_jesDn    = "/nfs-7/userdata/stopRun2/stop_babies__JESdn__CMS3_V080005__BabyMaker_V0800X_v8__20160729/";

  const std::string baby_outputDir_nominal = "Histos/Nominal/";
  const std::string baby_outputDir_jesUp   = "Histos/JesUp/";
  const std::string baby_outputDir_jesDn   = "Histos/JesDn/";


  //
  // ENUMS
  //
  enum ID{ k_T2tt,
           k_single_lepton_met_2016B,
           k_met_2016B,
	   k_single_lepton_2016B,
	   k_single_el_2016B_promptRecoV2,
	   k_single_mu_2016B_promptRecoV2,
	   k_diLepton_2016B,
	   k_muon_eg_2016B_promptRecoV2,
	   k_double_eg_2016B_promptRecoV2,
	   k_double_muon_2016B_promptRecoV2,
	   k_single_photon_2016B_promptRecoV2,
	   k_allBkg,
	   k_ttbar,
	   k_ttbar_powheg_pythia8,
	   k_ttbar_powheg_pythia8_ext3,
	   k_ttbar_madgraph_pythia8,
	   k_ttbar_singleLeptFromT_madgraph_pythia8,
	   k_ttbar_singleLeptFromT_madgraph_pythia8_ext1,
	   k_ttbar_singleLeptFromTbar_madgraph_pythia8,
	   k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1,
	   k_ttbar_diLept_madgraph_pythia8,
	   k_ttbar_diLept_madgraph_pythia8_ext1,
	   k_VJets,
	   k_DYJetsToLL,
	   k_DYJetsToLL_m10To50_amcnlo_pythia8,
	   k_DYJetsToLL_m50_amcnlo_pythia8,
	   k_WJetsToLNu,
	   k_WJetsToLNu_amcnlo_pythia8,
	   k_WJetsToLNu_HT100ToInf_madgraph_pythia8,
	   k_WJetsToLNu_HT100To200_madgraph_pythia8,
	   k_WJetsToLNu_HT200To400_madgraph_pythia8,
	   k_WJetsToLNu_HT400To600_madgraph_pythia8,
	   k_WJetsToLNu_HT600ToInf_madgraph_pythia8,
	   k_WJetsToLNu_HT600To800_madgraph_pythia8,
	   k_WJetsToLNu_HT800To1200_madgraph_pythia8,
	   k_WJetsToLNu_HT1200To2500_madgraph_pythia8,
	   k_WJetsToLNu_HT2500ToInf_madgraph_pythia8,
	   k_WJetsToLNu_HT100To200_madgraph_pythia8_ext1,
	   k_WJetsToLNu_HT200To400_madgraph_pythia8_ext1,
	   k_WJetsToLNu_HT400To600_madgraph_pythia8_ext1,
	   k_WJetsToLNu_HT600To800_madgraph_pythia8_ext1,
	   k_WJetsToLNu_HT800To1200_madgraph_pythia8_ext1,
	   k_WJetsToLNu_HT1200To2500_madgraph_pythia8_ext1,
	   k_WJetsToLNu_HT2500ToInf_madgraph_pythia8_ext1,
	   k_W1JetsToLNu,
	   k_W2JetsToLNu,
	   k_W3JetsToLNu,
	   k_W4JetsToLNu,
	   k_W1JetsToLNu_NuPt200,
	   k_W2JetsToLNu_NuPt200,
	   k_W3JetsToLNu_NuPt200,
	   k_W4JetsToLNu_NuPt200,
	   k_singleT,
	   k_t_sch_4f_amcnlo_pythia8,
	   k_t_tch_4f_powheg_pythia8,
	   k_tbar_tch_4f_powheg_pythia8,
	   k_singleT_tW,
	   k_singleT_non_tW,
	   k_t_tW_5f_powheg_pythia8,
	   k_t_tbarW_5f_powheg_pythia8,
	   k_rare,
	   k_diBoson,
	   k_WW,
	   k_WWTo2l2Nu_powheg,
	   k_WWToLNuQQ_powheg,
	   k_WZ,
	   k_WZ_pythia8,
	   k_WZTo3LNu_powheg_pythia8,
	   k_WZTo2L2Q_amcnlo_pythia8,
	   k_WZTo1LNu2Q_amcnlo_pythia8,
	   k_WZTo1L3Nu_amcnlo_pythia8,
	   k_ZZ,
	   k_ZZ_pythia8,
	   k_ZZTo4L_powheg_pythia8,
	   k_ZZTo2L2Q_amcnlo_pythia8,
	   k_ZZTo2L2Nu_powheg_pythia8,
	   k_ZZTo2Q2Nu_amcnlo_pythia8,
	   k_TTV,
	   k_TTW,
	   k_TTWJetsToLNu_amcnlo_pythia8,
	   k_TTWJetsToQQ_amcnlo_pythia8,
	   k_TTZ,
	   k_TTZToQQ_amcnlo_pythia8,
	   k_TTZToLLNuNu_m10_amcnlo_pythia8,
	   k_tZq,
	   k_tZq_ll_4f_amcnlo_pythia8,
	   k_tZq_nunu_4f_amcnlo_pythia8,
	   k_GJets_HT40toInf_madgraph_pythia8,
	   k_GJets_HT40To100_madgraph_pythia8,
	   k_GJets_HT100To200_madgraph_pythia8,
	   k_GJets_HT200To400_madgraph_pythia8,
	   k_GJets_HT400To600_madgraph_pythia8,
	   k_GJets_HT600ToInf_madgraph_pythia8,
	   k_nSample
  };

  
  //
  // TYPEDEFs
  //
  typedef std::vector< sampleInfo::ID > vect_id;

  
  //
  // UTILITY CLASS
  //
  class sampleUtil{

    public:
    
      sampleInfo::ID id;

      std::vector< std::pair< std::string, std::string > > baby_i_o;
      std::vector< std::string > inputBabies;

      std::string label;
      std::string title;
      std::string tex;

      bool isData;
      bool isFastsim;
      bool isSignal;
      bool isSignalScan;
      bool isAMCNLO;

      int nBins_stop;
      double min_stop;
      double max_stop;
      
      int nBins_lsp;
      double min_lsp;
      double max_lsp;

      std::vector< std::pair< int, int > >  massPtList;
          
      sampleUtil( sampleInfo::ID sample );
      ~sampleUtil(){};
      
  }; // end class def
  

  vect_id getSampleList( analyzerInfo::ID analysis );

  int scaleSample(std::string f_in_name, std::string f_out_name, double SF);

}; // end namespace def


#endif
