#include "StopSelections.h"

const float fInf = std::numeric_limits<float>::max();

std::vector<SR> getStopSignalRegions() {
  SR base;

  SR srbase;
  srbase.SetVar("mt", 50, -1);
  srbase.SetVar("met", 50, -1);
  srbase.SetVar("mt2w", 100, -1);
  srbase.SetVar("mlb", 0, -1);
  srbase.SetVar("tmod", 0, 2);
  srbase.SetVar("nlep", 1, 2);
  srbase.SetVar("njet", 2, -1);
  srbase.SetVar("nbjet", 1, -1);
  srbase.SetVar("dphijmet", 0.8, 3.14);

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // SR 2-3j
  sr = srbase;
  sr.SetName("sr1");
  sr.SetVar("njet", 2, 3);
  sr.SetVar("tmod", 10, -1);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("met", 250, 350);
  SRvec.emplace_back(sr);

  sr.SetName("sr2");
  sr.SetVar("met", 350, 450);
  SRvec.emplace_back(sr);

  sr.SetName("sr3");
  sr.SetVar("met", 450, 600);
  SRvec.emplace_back(sr);

  sr.SetName("sr4");
  sr.SetVar("met", 600, -1);
  SRvec.emplace_back(sr);

  sr.SetName("sr7");
  sr.SetVar("mlb", 175, -1);
  SRvec.emplace_back(sr);

  sr.SetName("sr6");
  sr.SetVar("met", 450, 600);
  SRvec.emplace_back(sr);

  sr.SetName("sr5");
  sr.SetVar("met", 250, 450);
  SRvec.emplace_back(sr);

  sr.SetName("sr8");

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTags() {
  SR base;

  SR crbase;
  crbase.SetVar("mt", 50, -1);
  crbase.SetVar("met", 50, -1);
  crbase.SetVar("mt2w", 100, -1);
  crbase.SetVar("mlb", 0, -1);
  crbase.SetVar("tmod", 0, 2);
  crbase.SetVar("nlep", 1, 2);
  crbase.SetVar("njet", 2, -1);
  crbase.SetVar("nbjet", 0, -1);
  crbase.SetVar("dphijmet", 0.8, 3.14);
  crbase.SetVar("ntightb", 0, -1);
  // crbase.CheckNumOfVarsMatch(true);

  SR cr;
  std::vector<SR> CRvec;

  // CR 0b
  crbase.SetName("cr0b");
  crbase.SetVar("nbjet", 0, 1);

  cr = crbase;
  cr.SetName(crbase.GetName()+"_base");
  CRvec.emplace_back(cr);

  cr = crbase;
  cr.SetName(crbase.GetName()+"_4jets_highmlb_lowdm");
  CRvec.emplace_back(cr);

  cr.SetName(crbase.GetName()+"_4jets_highmlb_meddm");
  CRvec.emplace_back(cr);

  cr.SetName(crbase.GetName()+"_4jets_highmlb_highdm");
  crbase.SetVar("ntightb", 0, 1);
  CRvec.emplace_back(cr);

  return CRvec;
}

std::vector<SR> getStopControlRegionsDilepton() {
  SR base;

  SR crbase;
  crbase.SetVar("mt", 150, -1);
  crbase.SetVar("mt2w", 100, -1);
  crbase.SetVar("nlep", 2, 3);
  crbase.SetVar("isdilep", 1, 2);
  crbase.SetVar("nbjet", 1, -1);
  crbase.SetVar("dphijmet", 0.8, 3.14);
  crbase.SetVar("ntightb", 0, -1);
  // crbase.CheckNumOfVarsMatch(true);

  SR cr;
  std::vector<SR> CRvec;

  cr = crbase;
  cr.SetName("cr2l_2to3j_tmod10_mlb175toInf_met250to450");
  cr.SetVar("njet", 2, 3);
  cr.SetVar("tmod", 10, -1);
  cr.SetVar("mlb", 175, -1);
  cr.SetVar("met", 250, 450);
  CRvec.emplace_back(cr);

  cr.SetName("cr2l_2to3j_tmod10toInf_mlb175toInf_met450to600");
  cr.SetVar("met", 450, 600);
  CRvec.emplace_back(cr);

  cr.SetName("cr2l_2to3j_tmod10toInf_mlb175toInf_met600toInf");
  cr.SetVar("met", 600, -1);
  CRvec.emplace_back(cr);


  cr.SetName("cr2l_4j_tmod10toInf_mlb175toInf_met250to450");
  cr.SetVar("njet", 4, -1);
  cr.SetVar("met", 250, 450);
  CRvec.emplace_back(cr);

  cr.SetName("cr2l_4j_tmod10toInf_mlb175toInf_met450toInf");
  cr.SetVar("met", 450, -1);
  CRvec.emplace_back(cr);


  cr.SetName("cr2l_4j_tmod0to10_mlb0to175_met350to550");
  cr.SetVar("tmod", 0, 10);
  cr.SetVar("mlb", 0, 175);
  cr.SetVar("met", 350, 550);
  CRvec.emplace_back(cr);

  cr.SetName("cr2l_4j_tmod0to10_mlb0to175_met550toInf");
  cr.SetVar("met", 550, -1);
  CRvec.emplace_back(cr);


  cr.SetName("cr2l_4j_tmod0to10_mlb175toInf_met250to450");
  cr.SetVar("mlb", 175, -1);
  cr.SetVar("met", 250, 450);
  CRvec.emplace_back(cr);

  cr.SetName("cr2l_4j_tmod0to10_mlb175toInf_met450toInf");
  cr.SetVar("met", 450, -1);
  CRvec.emplace_back(cr);


  return CRvec;
}
