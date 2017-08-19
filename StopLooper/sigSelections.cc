#include "sigSelections.h"


std::vector<SR> getStopControlRegions() {
  SR base;
  
  SR crbase;
  crbase.SetVar("mt", 150, -1);
  crbase.SetVar("met", 200, -1);
  crbase.SetVar("mlb", 200, -1);
  crbase.SetVar("tmod", 0, 2);
  crbase.SetVar("nlep", 1, 2);
  crbase.SetVar("njet", 2, -1);
  crbase.SetVar("nbjet", 0, -1);

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

