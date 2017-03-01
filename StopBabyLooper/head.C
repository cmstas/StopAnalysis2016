{
 
  // Load stopCORE
  gROOT->ProcessLine(".I ../../CORE/");
  gROOT->ProcessLine(".I ../../CORE/Tools/");
  //gSystem->Load("libCondToolsBTau.so");
  gSystem->Load("libCondFormatsBTauObjects.so");
  gSystem->Load("../StopCORE/BTagCalibrationStandalone.so");
  gSystem->Load("../StopCORE/stopCORE.so");
  gSystem->Load("../StopBabyMaker/stop_variables/StopVariables.so");

}
