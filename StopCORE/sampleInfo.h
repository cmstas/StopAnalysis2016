#ifndef sampleInfo_h
#define sampleInfo_h

// C
#include <string>
#include <vector>
#include <utility>


//
// Namespace 
//
namespace sampleInfo{

  //
  // NAMESPACE VARS
  //

  const std::string baby_inputDir = "/nfs-7/userdata/stopRun2/analysis2016_SUS-16-051_35p9fbinv/v22/skim/"; // 2017Moriond MC, updated sfs, fixed bugs again

  //const std::string baby_inputDir = "/nfs-7/userdata/haweber/tupler_babies/merged/Stop_1l/v21/skim/"; // 2017Moriond MC, updated sfs, fixed bugs

  //const std::string baby_inputDir = "/nfs-7/userdata/jgwood/tupler_babies/merged/Stop_1l/v20/skim/"; // 2017Moriond MC, updated sfs

  //const std::string baby_inputDir = "/nfs-7/userdata/isuarez/tupler_babies/merged/Stop_1l/v18/skim/"; // 2017Moriond MC, frozen PAS fro pre-approval

  //const std::string baby_inputDir = "/nfs-6/userdata/dsklein/stop-babies/skims_minDPhi05_v11/"; // First stable skim for main + corridor
  
  //const std::string baby_inputDir = "/nfs-7/userdata/isuarez/tupler_babies/merged/Stop_1l/v11/skim/"; // First draft of AN
    
  //const std::string baby_inputDir = "/nfs-7/userdata/stopRun2/analysis2016__SUS-16-028__12p9fb/stopBabies__v8.0.x_v8__20160729/Nominal/"; // 12.9/fb ICHEP results
  
  const std::string baby_outputDir = "Output/Histos/";
  

  //
  // ENUMS
  //
  enum ID{ k_T2tt,
           k_single_lepton_met,
           k_met,
	   k_single_lepton,
	   k_single_el,
	   k_single_mu,
	   k_diLepton,
	   k_muon_eg,
	   k_double_eg,
	   k_double_muon,
	   k_single_photon,
	   k_allBkg,
	   k_ttbar,
	   k_ttbar_powheg_pythia8,
	   k_ttbar_powheg_pythia8_ext4,
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
	   k_WNJetsToLNu_madgraph_pythia8,
	   k_W1JetsToLNu_madgraph_pythia8,
	   k_W2JetsToLNu_madgraph_pythia8,
	   k_W3JetsToLNu_madgraph_pythia8,
	   k_W4JetsToLNu_madgraph_pythia8,
	   k_W1JetsToLNu_NuPt200_madgraph_pythia8,
	   k_W2JetsToLNu_NuPt200_madgraph_pythia8,
	   k_W3JetsToLNu_NuPt200_madgraph_pythia8,
	   k_W4JetsToLNu_NuPt200_madgraph_pythia8,
	   k_singleT,
	   k_t_sch_4f_amcnlo_pythia8,
	   k_t_tch_4f_powheg_pythia8,
	   k_tbar_tch_4f_powheg_pythia8,
	   k_singleT_tW,
	   k_singleT_non_tW,
	   k_t_tW_5f_powheg_pythia8,
	   k_t_tbarW_5f_powheg_pythia8,
	   k_t_tW_5f_powheg_pythia8_noHadDecays,
	   k_t_tbarW_5f_powheg_pythia8_noHadDecays,
	   k_t_tW_5f_powheg_pythia8_noHadDecays_ext1,
	   k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1,
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
	   k_ttWJets_13TeV_madgraphMLM,
	   k_TTZ,
	   k_TTZToQQ_amcnlo_pythia8,
	   k_TTZToLLNuNu_m10_amcnlo_pythia8,
	   k_ttZJets_13TeV_madgraphMLM,
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
  // UTILITY CLASS
  //
  class sampleUtil{

    public:
    
      sampleInfo::ID id;

      std::pair< std::string, std::string > baby_i_o;
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
  

  //
  // TYPEDEFs
  //
  typedef std::vector< sampleInfo::ID > vect_id;
  typedef std::vector< sampleInfo::sampleUtil > vect_util;


  //
  // FUNCTIONS
  //
  vect_id getSampleList_SR();
  vect_id getSampleList_CR2l_bulkTTbar();
  vect_id getSampleList_CRGammaJets();

  int scaleSample(std::string f_in_name, std::string f_out_name, double SF);

}; // end namespace def


#endif
