{
 
  // Load stopCORE
  //gSystem->AddIncludePath("../../CORE/");
  //gSystem->AddIncludePath("../../CORE/Tools/");
  //gSystem->AddIncludePath("../../CORE/Tools/btagsf/");
  gROOT->ProcessLine(".I ../../CORE/");
  gROOT->ProcessLine(".I ../../CORE/Tools/");
  //gROOT->ProcessLine(".I ../../CORE/Tools/btagsf/");
  //gROOT->ProcessLine(".L ../StopCORE/");
  //gROOT->ProcessLine(".L BTagCalibrationStandalone.cc+");
  //gSystem->Load("../../CORE/CMS3_CORE.so");
  gSystem->Load("../StopCORE/stopCORE.so");
  gSystem->Load("../StopBabyMaker/stop_variables/StopVariables.so");

}
