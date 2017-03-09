#include "stopBabyLooper.h"

int main () {
  
  // Run Looper
  stopBabyLooper();
  

  // Scale Output Samples (should be done in sysInfo::getSampleWeight)
  //scaleSamples("Output/Histos/", "Output/Histos/");


  // Merge Babies, before zero-ing aMC@NLO samples, to create tables
  //mergeStopBabies("Output/Histos/", "Output/Histos/",false);
  

  // Make table of yields for merged and component samples, before zeroing
  //tableMaker_allInputs("Output/Histos/","Output/Tables/yields_allInputs_beforeZeroing",false);


  // Zero Negative Yields from aMC@NLO Samples
  zeroOutNegativeYields("Output/Histos/");


  // Merge Babies, after zeroing aMC@NLO samples
  mergeStopBabies("Output/Histos/", "Output/Histos/",true);


  // Make table of yields for merged and component samples, after zeroing
  //tableMaker_allInputs("Output/Histos/","Output/Tables/yields_allInputs");


  // Make table of yields for final merged samples
  tableMaker_summedInputs("Output/Histos/","Output/Tables/yields_summedInputs");


  // Make table of systematic uncertainties for final samples
  //calcErrors();

  
  // Make plots by gen decay mode
  plotMaker();

  
  // Make plots by production mode
  //plotMaker(false);


  // Make pie charts for backgrounds
  pieCharts();

  
  // Perform background estimates
  bkgEstimate_diLepton();
  bkgEstimate_1lepFromW();
  bkgEstimate_1lepFromTop();
  bkgEstimate_ZtoNuNu();
  

  // Done!
  return 0;
}
