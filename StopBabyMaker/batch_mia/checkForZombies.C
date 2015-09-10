#include "Riostream.h"
#include "TFile.h"

int checkForZombies(char *fileName){

  TFile *file = new TFile(fileName, "read");
  bool isZombie = (bool)file->IsZombie();

  ofstream zombieFiles;
  zombieFiles.open("listOfZombies.txt");
  if(isZombie){
    zombieFiles << fileName << endl;
  }
  
  zombieFiles.close();
  file->Close();

  return isZombie;
}
  
