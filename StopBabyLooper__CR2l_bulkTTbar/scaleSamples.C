#include "stopBabyLooper__CR2l_bulkTTbar.h"

void scaleSamples(std::string f_input_dir, std::string f_output_dir){

  std::vector< std::pair< sampleInfo::ID, double > > targetList;
  std::pair< sampleInfo::ID, double > target;

  target.first  = sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8;
  target.second = 1.041;
  //targetList.push_back(target);

  target.first = sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8;
  target.second = 0.9321;
  //targetList.push_back(target);

  target.first = sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8;
  target.second = 1.0384;
  //targetList.push_back(target);

  target.first = sampleInfo::k_WJetsToLNu_HT600ToInf_madgraph_pythia8;
  target.second = 0.9532;
  //targetList.push_back(target);


  for(int iTarget=0; iTarget<(int)targetList.size(); iTarget++){

    sampleInfo::sampleUtil sample( targetList[iTarget].first );

    std::string f_input_name = "";
    f_input_name += f_input_dir;
    f_input_name += "h__";
    f_input_name += sample.label;
    f_input_name += ".root";

    std::string f_output_name = "";
    f_output_name += f_output_dir;
    f_output_name += "h__";
    f_output_name += sample.label;
    f_output_name += "_reScaled";
    f_output_name += ".root";

    sampleInfo::scaleSample( f_input_name, f_output_name, targetList[iTarget].second );
    
  } // end loop over targetList

  return;
}


