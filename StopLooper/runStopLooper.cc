#include <iostream>
#include <string>
#include "TChain.h"
#include "TString.h"

#include "StopLooper.h"

using namespace std;

int main(int argc, char** argv)
{

  if (argc < 4) {
    cout << "USAGE: runStopLooper <input_dir> <sample> <output_dir>" << endl;
    return 1;
  }

  string input_dir(argv[1]); 
  string sample(argv[2]); 
  string output_dir(argv[3]);

  TChain *ch = new TChain("t");

  TString infile = Form("%s/%s*.root", input_dir.c_str(), sample.c_str());
  ch->Add(infile);
  if (ch->GetEntries() == 0) {
    cout << "ERROR: no entries in chain. filename was: " << infile << endl;
    return 2;
  }

  StopLooper stop;
  stop.looper(ch, sample, output_dir); 

  return 0;
}
