void rootlogon() {
  //gSystem->SetIncludePath(" -I../MT2Code/include/ -I../TESCO/include/");
  gSystem->Load("libPhysics");
  gSystem->Load("libFWCoreFWLite.so");
  FWLiteEnabler::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  //gSystem->Load("../MT2Code/shlib/libDiLeptonAnalysis.so");
  gROOT->LoadMacro("/home/users/haweber/vecUtils.h");
  
}
