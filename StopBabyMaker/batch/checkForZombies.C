#include "Riostream.h"
#include "TFile.h"

int checkForZombies(const char *rootFileName, const char *notZombieFileName){

  TFile *rootFile = new TFile(rootFileName, "read");
  bool isZombie = (bool)rootFile->IsZombie();

  ofstream zombieFiles;
  zombieFiles.open(notZombieFileName, std::ofstream::app);
  if(!isZombie){
    zombieFiles << rootFileName << endl;
  }
  
  zombieFiles.close();
  rootFile->Close();

  return isZombie;
}
  
