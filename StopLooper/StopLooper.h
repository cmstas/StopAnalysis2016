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
  void GenerateAllSRptrSets();

  void looper(TChain* chain, std::string sample, std::string outputdir);

  std::vector<SR*> FindSR(std::map<std::string,float>& values);
  void fillHistosForSR(std::map<std::string,float>& values, std::string suffix = "");
  void fillHistosForCR2l(std::map<std::string,float>& values, std::string suffix = "");
  void fillHistosForCR0b(std::map<std::string,float>& values, std::string suffix = "");

  void newFillHistosForCR(std::map<std::string,float>& values, std::string suffix = "");

protected:
  std::vector<SR> SRVec;
  std::vector<SR> CR2lVec;
  std::vector<SR> CR0bVec;
  std::map<std::string,SRptrSet> allSRptrSets;

private:
  TFile* outfile_;
  float evtweight_;

};

#endif
