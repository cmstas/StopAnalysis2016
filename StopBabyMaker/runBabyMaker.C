#include "looper.h"
#include "TChain.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<TString> load(char *type, const char *filename, char *input){

  vector<TString> output;
  char buffer[200];
  char StringValue[1000];
  ifstream IN(input);
  while( IN.getline(buffer, 200, '\n') ){
    // ok = false;
    if (buffer[0] == '#') {
      continue; // Skip lines commented with '#'
    }
    if( !strcmp(buffer, "SAMPLE")){
      bool add = false;
      IN.getline(buffer, 200, '\n');
      sscanf(buffer, "Name\t%s", StringValue);
      if((string)StringValue==(string)type) add=true;
      IN.getline(buffer, 200, '\n');
      sscanf(buffer, "Path\t%s", StringValue);
      if(add){
	std::ostringstream addStream;
	addStream << StringValue << filename;
	TString addString = addStream.str().c_str();
	output.push_back(addString);
      }
    }
  }
  return output;
}
  

//int main(){
int main(int argc, char **argv){
 if(argc<2){
   cout<<" runBabyMaker takes four arguments: ./runBabyMaker sample_name nevents file_number outpath" << endl;
   cout<<" Need to provide at least sample_name; nevents=-1 (-1=all events), file_number=0 (0=merged_ntuple_*.root), output=/nfs-7/userdata/stopRun2/  by default"<<endl;
   return 0;
 }
  babyMaker *mylooper = new babyMaker();

  //void setSkimVariables(int nvtx, float met, int nlep, float el_pt, float el_eta, float mu_pt, float mu_eta, int njets, float jetpt, float jeteta);
  mylooper->setSkimVariables(1, 30., 1, 15., 2.1, 15., 2.1, 2, 30., 2.4);

  int nevents = -1;
  if(argc>2) nevents = atoi(argv[2]);  
  
  int file=0;
  if(argc>3) file = atoi(argv[3]);

  char* dirpath = "/nfs-7/userdata/stopRun2/";  
  if(argc>4) dirpath = argv[4];

  const char* filename = (file == 0 ? "merged_ntuple_*.root" : Form("merged_ntuple_%i.root", file));
  cout << filename << endl;
  
  const char* suffix = file == 0 ? "" : Form("_%i", file);

  char *input = "sample.dat";
  if(argc>5) input = argv[5];

  TChain *sample = new TChain("Events");

  vector<TString> samplelist = load(argv[1], filename, input);//new
  for(unsigned int i = 0; i<samplelist.size(); ++i){
    cout << "Add sample " << samplelist[i] << " to files to be processed." << endl;
    sample->Add(samplelist[i].Data());
  }

  mylooper->looper(sample, Form("%s%s", argv[1],suffix), nevents,dirpath);

  return 0;
}
