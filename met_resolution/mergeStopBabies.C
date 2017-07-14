#include "met-resolution.h"

void mergeStopBabies( std::string f_input_dir, std::string f_output_dir, bool use_zeroed_samp ){

  // Get list of input samples
  std::vector< std::pair< sampleInfo::ID, std::vector< mergeUtil > > > addList;
  std::pair< sampleInfo::ID, std::vector< mergeUtil > > addSet;
  
  // // ttbar
  // addSet.first = sampleInfo::k_ttbar;
  // //addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_powheg_pythia8_ext4) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_diLept_madgraph_pythia8) );
  // addList.push_back(addSet);
  // addSet.second.clear();


  // // single t
  // addSet.first = sampleInfo::k_singleT;
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_sch_4f_amcnlo_pythia8,use_zeroed_samp,false) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tch_4f_powheg_pythia8) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_tbar_tch_4f_powheg_pythia8) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1) );
  // //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8) );
  // //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8) );
  // addList.push_back(addSet);
  // addSet.second.clear();

  // // single t, tW
  // addSet.first = sampleInfo::k_singleT_tW;
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays_ext1) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays_ext1) );
  // //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8) );
  // //addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8) );
  // addList.push_back(addSet);
  // addSet.second.clear();

  // // single t, non tW
  // addSet.first = sampleInfo::k_singleT_non_tW;
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_sch_4f_amcnlo_pythia8,use_zeroed_samp,false) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_t_tch_4f_powheg_pythia8) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_tbar_tch_4f_powheg_pythia8) );
  // addList.push_back(addSet);
  // addSet.second.clear();


  // // All background
  // addSet.first = sampleInfo::k_allBkg;
  // addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_singleT) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_VJets) );
  // addSet.second.push_back( mergeUtil(sampleInfo::k_rare) );
  // addList.push_back(addSet);
  // addSet.second.clear();

  // All background
  addSet.first = sampleInfo::k_allBkg;
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_diLept_madgraph_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tbarW_5f_powheg_pythia8_noHadDecays) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_tW_5f_powheg_pythia8_noHadDecays) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_t_sch_4f_amcnlo_pythia8) );
  addSet.second.push_back( mergeUtil(sampleInfo::k_tbar_tch_4f_powheg_pythia8_inclDecays) );
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

