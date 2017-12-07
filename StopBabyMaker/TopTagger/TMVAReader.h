/*
 * TMVAReader.h
 *
 *  Created on: Sep 30, 2016
 *      Author: hqu
 */

#ifndef STOPBABYMAKER_TOPTAGGER_TMVAREADER_H
#define STOPBABYMAKER_TOPTAGGER_TMVAREADER_H

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

class TMVAReader{
 public:
  TMVAReader() {}
  TMVAReader(TString weightfile, TString mvaName) : weightfile_(weightfile), mvaName_(mvaName) {
    TMVA::Tools::Instance();
    reader = new TMVA::Reader( "!Color:!Silent" );
    std::cout << "Loading MVA from file: " << weightfile_ << std::endl;
  }
  virtual ~TMVAReader(){
    if(reader) delete reader;
  }

  void addVariables(const std::vector<TString> &vars){
    for (const auto &v : vars) {
      varMap_[v]=0;
      reader->AddVariable(v, &varMap_[v]);
    }
  }

  void setValue(const TString &var, Float_t value){
    varMap_.at(var) = value;
  }

  double eval(){
    if (firstCall_){
      reader->BookMVA( mvaName_, weightfile_ );
      firstCall_ = false;
    }
    return reader->EvaluateMVA(mvaName_);
  }

  std::vector<float> evalMulti(){
    if (firstCall_){
      reader->BookMVA( mvaName_, weightfile_ );
      firstCall_ = false;
    }
    return reader->EvaluateMulticlass(mvaName_);
  }

 private:
  std::map<TString, Float_t> varMap_;

  TMVA::Reader *reader = nullptr;
  TString weightfile_;
  TString mvaName_;

  bool firstCall_ = true;
};

#endif /* STOPBABYMAKER_TOPTAGGER_TMVAREADER_H */
