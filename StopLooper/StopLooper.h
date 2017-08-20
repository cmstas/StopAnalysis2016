#ifndef STOPLOOPER_h
#define STOPLOOPER_h

#include "TFile.h"
#include "TChain.h"
#include "SR.h"

class StopLooper {
public:
  StopLooper() : evtweight_(1.) {}
  ~StopLooper() {}

  void SetSignalRegions();
  void looper(TChain* chain, std::string sample, std::string outputdir);
  
  void fillHistosForSR(std::map<std::string,float>& values, std::string suffix = "");
  void fillHistosForCR(std::map<std::string,float>& values, std::string suffix = "");

private:
  TFile* outfile_;
  float evtweight_;

  std::vector<SR> SRVec;
  std::vector<SR> CRVec;
  
};

#endif
