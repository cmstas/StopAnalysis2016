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
  char buffer[500];
  char StringValue[1000];
  ifstream IN(input);
  while( IN.getline(buffer, 500, '\n') ){
    // ok = false;
    if (buffer[0] == '#') {
      continue; // Skip lines commented with '#'
    }
    if( !strcmp(buffer, "SAMPLE")){
      bool add = false;
      IN.getline(buffer, 500, '\n');
      sscanf(buffer, "Name\t%s", StringValue);
      if((string)StringValue==(string)type) add=true;
      IN.getline(buffer, 500, '\n');
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


int main(int argc, char **argv){

  //
  // Input sanitation
  //
  //isFastsim = true does not work, need to use = 1
  if(argc<2){
    cout<<" runBabyMaker takes six arguments: ./runBabyMaker sample_name nevents file_number outpath samplelist isFastSim" << endl;
    cout<<" Need to provide at least sample_name; nevents=-1 (-1=all events), file_number=-1 (-1=merged_ntuple_*.root), output=/nfs-7/userdata/stopRun2/, samplelist=sample_2017.dat, isFastSim=false by default"<<endl;
    return 0;
  }

  //
  // Use arguments to set run parameters
  //
  int nevents = -1;
  if(argc>2) nevents = atoi(argv[2]);

  int file=-1;
  if(argc>3) file = atoi(argv[3]);

  char* dirpath = ".";
  if(argc>4) dirpath = argv[4];

  //const char* filename = (file == -1 ? "*postprocess.root" : Form("%spostprocess.root"));
  const char* filename = (file == -1 ? "merged_ntuple_*.root" : Form("merged_ntuple_%i.root", file));
  //const char* filename = "ntuple_TTJets_HT-1200to2500_new.root";
  cout << filename << endl;

  const char* suffix = file == -1 ? "" : Form("_%i", file);

  char *input = "sample_2017.dat";
  if(argc>5) input = argv[5];

  bool isFastsim = false;
  if(argc>6) isFastsim = atoi(argv[6]);
  //isFastsim = true does not work, need to use = 1

  //
  // Initialize looper
  //
  babyMaker *mylooper = new babyMaker();

  //
  // Skim Parameters
  //
  mylooper->skim_nvtx            = 1;
  mylooper->skim_met             = 100;

  mylooper->skim_nGoodLep        = 1;
  mylooper->skim_goodLep_el_pt   = 20.0;
  mylooper->skim_goodLep_el_eta  = 1.4442;
  mylooper->skim_goodLep_mu_pt   = 20.0;
  mylooper->skim_goodLep_mu_eta  = 2.4;

  mylooper->skim_looseLep_el_pt  = 10.0;
  mylooper->skim_looseLep_el_eta = 2.4;
  mylooper->skim_looseLep_mu_pt  = 10.0;
  mylooper->skim_looseLep_mu_eta = 2.4;

  mylooper->skim_vetoLep_el_pt   = 5.0;
  mylooper->skim_vetoLep_el_eta  = 2.4;
  mylooper->skim_vetoLep_mu_pt   = 5.0;
  mylooper->skim_vetoLep_mu_eta  = 2.4;

  mylooper->skim_nJets           = 2;
  mylooper->skim_jet_pt          = 30.0;
  mylooper->skim_jet_eta         = 2.4;

  mylooper->skim_nBJets          = 0;

  //temporarily set to false in order to take JECs from miniAOD directly for 2017 early data
  // mylooper->applyJECfromFile   = false; //THIS FLAG DECIDES NOW TOO IF JESUP/DOWN VALUES ARE CALCULATED
  mylooper->applyJECfromFile   = true;
  mylooper->JES_type           = 0;  //0 central, 1 up, -1 down; // not needed anymore

  mylooper->applyBtagSFs       = true;
  mylooper->applyLeptonSFs     = true;
  mylooper->applyVetoLeptonSFs = true;
  mylooper->apply2ndLepVeto    = false;
  mylooper->isFastsim          = isFastsim;

  mylooper->skim_jet_ak8_pt    = 100.0;
  mylooper->skim_jet_ak8_eta   = 2.4;

  mylooper->skim_nPhotons      = 0;
  mylooper->skim_ph_pt         = 20.0;
  mylooper->skim_ph_eta        = 2.4;

  mylooper->filltaus        =  true;
  mylooper->filltracks      =  true;
  mylooper->fillZll         =  false;
  mylooper->fillPhoton      =  false;
  mylooper->fillMETfilt     =  true;
  mylooper->fill2ndlep      =  false;
  mylooper->fillExtraEvtVar =  false;

  mylooper->fillAK8         =  true;
  mylooper->fillTopTag      =  true;
  mylooper->fillAK4EF       =  false;
  mylooper->fillAK4_Other   =  false;
  mylooper->fillOverleps    =  false;
  mylooper->fillAK4Synch    =  false;
  mylooper->fillElID        =  false;
  mylooper->fillIso         =  false;
  mylooper->fillLepSynch    =  false;

  // Input sanitation
  if( !(mylooper->skim_goodLep_mu_pt > mylooper->skim_looseLep_mu_pt &&
        mylooper->skim_looseLep_mu_pt > mylooper->skim_vetoLep_mu_pt) ){
    cout << "   Problem with muon pT hierachy for good, loose, and veto pT!" << endl;
    cout << "     Exiting..." << endl;
    return 0;
  }

  if( !(mylooper->skim_goodLep_el_pt > mylooper->skim_looseLep_el_pt &&
        mylooper->skim_looseLep_el_pt > mylooper->skim_vetoLep_el_pt) ){
    cout << "   Problem with electron pT hierarchy for good, loose, and veto pT!" << endl;
    cout << "     Exiting..." << endl;
    return 0;
  }

  //
  // Intialize TChain, load samples
  //
  TChain *sample = new TChain("Events");

  vector<TString> samplelist = load(argv[1], filename, input);//new
  bool fileexists = true;
  for(unsigned int i = 0; i<samplelist.size(); ++i){
    if(file>=0){
      //check if file exists - works not for *
      ifstream infile(samplelist[i].Data());
      fileexists = infile.good();
    }
    if(fileexists){
      cout << "Add sample " << samplelist[i] << " to files to be processed." << endl;
      sample->Add(samplelist[i].Data());
    }
  }


  //
  // Run Looper
  //
  mylooper->looper(sample, Form("%s%s", argv[1],suffix), nevents,dirpath);


  //
  // Return
  //
  return 0;
}
