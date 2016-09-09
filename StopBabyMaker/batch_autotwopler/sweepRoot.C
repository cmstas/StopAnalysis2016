#include "Riostream.h"
#include "TFile.h"

int sweepRoot(const char *rootFileName){

  TFile *rootFile = new TFile(rootFileName, "read");
  bool isZombie = (bool)rootFile->IsZombie();
  rootFile->Close();
  
  // Return 0 if good, 1 if bad
  cout << "result=" << isZombie << endl;
  return (int)isZombie;

}
  
