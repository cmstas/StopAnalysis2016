#ifndef STOPLOOPER_h
#define STOPLOOPER_h

#include "TFile.h"
#include "TChain.h"
#include "SR.h"

stop_1l_babyAnalyzer babyAnalyzer;

class StopLooper {
public:
  StopLooper() {}
  ~StopLooper() {}

  void SetSignalRegions();
  void looper(TChain* chain, std::string sample, std::string outputdir);
  
private:
  TFile* outfile_;

  std::vector<SR> SRVec;
  std::vector<SR> CRVec;
  
};

#endif
