#include "stopBabyLooper__CR2l_bulkTTbar.h"

void mergeStopBabies( std::string f_input_dir, std::string f_output_dir, bool use_zeroed_samp ){

  // Get list of input samples
  std::vector< std::pair< sampleInfo::ID, std::vector< mergeUtil > > > addList;
  std::pair< sampleInfo::ID, std::vector< mergeUtil > > addSet;
  
  // ttbar
  addSet.first = sampleInfo::k_ttbar;
  //addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_powheg_pythia8_ext4) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_diLept_madgraph_pythia8) );
  addList.push_back(addSet);
  addSet.second.clear();


  // single t
  addSet.first = sampleInfo::k_singleT;
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_sch_4f_amcnlo_pythia8,use_zeroed_samp,false) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tch_4f_powheg_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_tbar_tch_4f_powheg_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8) );
  addList.push_back(addSet);
  addSet.second.clear();

  // single t, tW
  addSet.first = sampleInfo::k_singleT_tW;
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8) );
  addList.push_back(addSet);
  addSet.second.clear();

  // single t, non tW
  addSet.first = sampleInfo::k_singleT_non_tW;
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_sch_4f_amcnlo_pythia8,use_zeroed_samp,false) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tch_4f_powheg_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_tbar_tch_4f_powheg_pythia8) );
  addList.push_back(addSet);
  addSet.second.clear();
 

  // DYJets
  addSet.first = sampleInfo::k_DYJetsToLL;
  addSet.second.push_back( mergeUtil(sampleInfo::k_DYJetsToLL_m10To50_amcnlo_pythia8,use_zeroed_samp,false) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_DYJetsToLL_m50_amcnlo_pythia8,use_zeroed_samp,false) );
  addList.push_back(addSet);
  addSet.second.clear();
 

  // WJets, Madgraph Ht Summed Samples
  //addSet.first = sampleInfo::k_WJetsToLNu_HT100ToInf_madgraph_pythia8;
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8_ext1) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8_ext1) );
  //addList.push_back(addSet);
  //addSet.second.clear();

  // WJets, Madgraph NParton Summed Samples
  addSet.first = sampleInfo::k_WNJetsToLNu_madgraph_pythia8;
  addSet.second.push_back( mergeUtil(sampleInfo::k_W1JetsToLNu_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_W2JetsToLNu_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_W3JetsToLNu_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_W4JetsToLNu_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_W1JetsToLNu_NuPt200_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_W2JetsToLNu_NuPt200_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_W3JetsToLNu_NuPt200_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_W4JetsToLNu_NuPt200_madgraph_pythia8) );
  addList.push_back(addSet);
  addSet.second.clear();

  // WJets
  addSet.first = sampleInfo::k_WJetsToLNu;
  //addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu_HT100ToInf_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_WNJetsToLNu_madgraph_pythia8) );
  addList.push_back(addSet);
  addSet.second.clear();

  // VJets
  addSet.first = sampleInfo::k_VJets;
  addSet.second.push_back( mergeUtil(sampleInfo::k_WJetsToLNu) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_DYJetsToLL) );
  addList.push_back(addSet);
  addSet.second.clear();


  // TTW
  addSet.first = sampleInfo::k_TTW;
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttWJets_13TeV_madgraphMLM) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8,use_zeroed_samp,false) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_TTWJetsToQQ_amcnlo_pythia8,use_zeroed_samp,false) );
  addList.push_back(addSet);
  addSet.second.clear();

  // TTZ
  addSet.first = sampleInfo::k_TTZ;
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttZJets_13TeV_madgraphMLM) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_TTZToQQ_amcnlo_pythia8,use_zeroed_samp,false) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_TTZToLLNuNu_m10_amcnlo_pythia8,use_zeroed_samp,false) );
  addList.push_back(addSet);
  addSet.second.clear();

  // TTV
  addSet.first = sampleInfo::k_TTV;
  addSet.second.push_back( mergeUtil(sampleInfo::k_TTZ) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_TTW) );
  addList.push_back(addSet);
  addSet.second.clear();


  // tZq
  addSet.first = sampleInfo::k_tZq;
  //addSet.second.push_back( mergeUtil(sampleInfo::k_tZq_ll_4f_amcnlo_pythia8,use_zeroed_samp,false) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_tZq_nunu_4f_amcnlo_pythia8,use_zeroed_samp,false) );
  //addList.push_back(addSet);
  addSet.second.clear();
  
  
  // WW
  addSet.first = sampleInfo::k_WW;
  addSet.second.push_back( mergeUtil(sampleInfo::k_WWTo2l2Nu_powheg) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_WWToLNuQQ_powheg) );
  addList.push_back(addSet);
  addSet.second.clear();
  
  // WZ
  addSet.first = sampleInfo::k_WZ;
  addSet.second.push_back( mergeUtil(sampleInfo::k_WZTo3LNu_powheg_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_WZTo2L2Q_amcnlo_pythia8,use_zeroed_samp,false) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_WZTo1LNu2Q_amcnlo_pythia8,use_zeroed_samp,false) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_WZTo1L3Nu_amcnlo_pythia8,use_zeroed_samp,false) );
  addList.push_back(addSet);
  addSet.second.clear();

  // ZZ
  addSet.first = sampleInfo::k_ZZ;
  addSet.second.push_back( mergeUtil(sampleInfo::k_ZZTo4L_powheg_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ZZTo2L2Q_amcnlo_pythia8,use_zeroed_samp,false) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ZZTo2L2Nu_powheg_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ZZTo2Q2Nu_amcnlo_pythia8,use_zeroed_samp,false) );
  addList.push_back(addSet);
  addSet.second.clear();

  // diBoson
  addSet.first = sampleInfo::k_diBoson;
  addSet.second.push_back( mergeUtil(sampleInfo::k_WW) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_WZ) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ZZ) );
  addList.push_back(addSet);
  addSet.second.clear();
 

  // Rare
  addSet.first = sampleInfo::k_rare;
  addSet.second.push_back( mergeUtil(sampleInfo::k_TTV) );
  //addSet.second.push_back( mergeUtil(sampleInfo::k_tZq) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_diBoson) );
  addList.push_back(addSet);
  addSet.second.clear();


  // All background
  addSet.first = sampleInfo::k_allBkg;
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_singleT) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_VJets) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_rare) );
  addList.push_back(addSet);
  addSet.second.clear();
 
  

  //
  // Merge Em!
  //
  for(int iMerger=0; iMerger<(int)addList.size(); iMerger++){
    
    mergeEm( addList[iMerger].first, addList[iMerger].second, f_input_dir, f_output_dir );

  }
  
  return;
}


int mergeEm( sampleInfo::ID target, std::vector< mergeUtil > sources, std::string f_input_dir, std::string f_output_dir ){

  // Get name of target file
  sampleInfo::sampleUtil target_sample( target );
  std::string target_name = f_output_dir;
  target_name += target_sample.label;
  target_name += ".root";

  // Get name of input files
  std::string sources_name = "";
  for(int iSource=0; iSource<(int)sources.size(); iSource++){

    sampleInfo::sampleUtil source_sample( sources[iSource].id );

    std::string temp_name = "";
    temp_name += f_input_dir;
    temp_name += source_sample.label;
    temp_name += ".root";
      
    if(sources[iSource].useZeroed){
      std::string replace_str = "amcnlo_pythia8_25ns.root";
      std::string noNeg_str   = "amcnlo_pythia8_25ns_noNegYield.root";
      size_t idx=0;
      idx = temp_name.find( replace_str );
      if( idx!=std::string::npos ){
	temp_name.erase( idx, replace_str.size() );
	temp_name += noNeg_str;
      } // end if found amcnlo string
    }
    
    if(sources[iSource].useRescaled){
      std::string replace_str = ".root";
      std::string scaled_str  = "_reScaled.root";
      size_t idx=0;
      idx = temp_name.find( replace_str );
      if( idx!=std::string::npos ){
	temp_name.erase( idx, replace_str.size() );
	temp_name += scaled_str;
      } // ned if found scaled string
    }

    sources_name += temp_name;
    sources_name += " ";

  } // end loop over sources

  std::string process = ".! hadd -f ";
  process += target_name;
  process += " ";
  process += sources_name;

  cout << "  hadd -f " << target_name << " " << sources_name << endl;

  gROOT->ProcessLine( process.c_str() );
  
  cout << endl << endl;

  return 0;
}

