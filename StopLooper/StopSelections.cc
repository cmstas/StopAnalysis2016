#include "StopSelections.h"


std::vector<SR> getStopControlRegions() {
  SR base;
  
  SR crbase;
  crbase.SetVar("met", 50, -1);
  crbase.SetVar("mt2w", 100, -1);
  crbase.SetVar("mlb", 0, -1);
  crbase.SetVar("tmod", 0, 2);
  crbase.SetVar("nlep", 1, 2);
  crbase.SetVar("njet", 2, -1);
  crbase.SetVar("nbjet", 0, -1);
  crbase.SetVar("dphijmet", 0.8, 3.14);

  SR cr;
  std::vector<SR> CRvec;
  crbase.SetName("cr0b");

  cr = crbase;
  cr.SetName(crbase.GetName()+"1");
  cr.SetVar("tmod", 0, 1);
  CRvec.push_back(cr);
  
  cr = crbase;
  cr.SetName(crbase.GetName()+"2");
  cr.SetVar("tmod", 1, 2);
  CRvec.push_back(cr);

  return CRvec;
}

