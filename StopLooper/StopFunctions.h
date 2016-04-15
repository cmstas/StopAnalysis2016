#include "StopNTuple.h"
#include <vector> 
#include <unistd.h>
#include "TVector3.h"
#include "TLorentzVector.h"

#ifndef CMS3_H
#define CMS3_H

#ifndef __CINT__
extern StopNTuple cms3;
#endif

namespace StF {

  bool isSignalOrControlRegion();//does not contain triggers/filters
  bool isSignalRegion();         //does not contain triggers/filters
  bool isDileptonControlRegion();//does not contain triggers/filters
  bool isNoBTagControlRegion();  //does not contain triggers/filters
  int  SRIdentifier();//SR number 1-9
  int  CR2lIdentifier(); 
  int  CR0bIdentifier();
  bool passSignalTriggers();
  bool passMETfiltersNoTxt();
  int whichT2tbdecay();
  int PolarizationWeights(float &wL, float &wR);

}//namespace

#endif
