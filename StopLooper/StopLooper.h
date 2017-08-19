#ifndef STOPLOOPER_h
#define STOPLOOPER_h

#include "TFile.h"
#include "TChain.h"
#include "SR.h"

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
