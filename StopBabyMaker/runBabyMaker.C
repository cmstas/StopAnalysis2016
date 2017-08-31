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
  int nVtx              = 1;

  float met             = 100;

  int nGoodLeptons      = 1;
  float goodLep_el_pt   = 20.0;
  float goodLep_el_eta  = 1.4442;
  float goodLep_mu_pt   = 20.0;
  float goodLep_mu_eta  = 2.4;

  float looseLep_el_pt  = 10.0;
  float looseLep_el_eta = 2.4;
  float looseLep_mu_pt  = 10.0;
  float looseLep_mu_eta = 2.4;

  float vetoLep_el_pt   = 5.0;
  float vetoLep_el_eta  = 2.4;
  float vetoLep_mu_pt   = 5.0;
  float vetoLep_mu_eta  = 2.4;

  int nJets             = 2;
  float jet_pt          = 30.0;
  float jet_eta         = 2.4;

  int nBJets            = 0; 

  //temporarily set to false in order to take JECs from miniAOD directly for 2017 early data
  bool applyJECfromFile = false; //THIS FLAG DECIDES NOW TOO IF JESUP/DOWN VALUES ARE CALCULATED
  int JES_central_up_down = 0;  //0 central, 1 up, -1 down; // not needed anymore
  bool applyBtagSFs = true; 
  bool applyLeptonSFs = true;
  bool applyVetoLeptonSFs = true;
  bool apply2ndlepVeto =  false;

  float jet_ak8_pt      = 100.0;
  float jet_ak8_eta     = 2.4;

  int   nphs            = 0;
  float phs_pt          = 20.0;
  float phs_eta         = 2.4;

  bool filltaus_  =  true;
  bool filltracks_  =  true;
  bool fillZll_  =  false;
  bool fillPhoton_  =  false;
  bool fillMETfilt_  =  true;
  bool fill2ndlep_  =  false;
  bool fillExtraEvtVar_  =  false;

  bool fillAK4EF_  =  false;
  bool fillAK4_Other_  =  false;
  bool fillOverleps_  =  false;
  bool fillAK4Synch_  =  false;
  bool fillElID_  =  false;
  bool fillIso_  =  false;
  bool fillLepSynch_  =  false;
  
  // Input sanitation
  if( !( goodLep_mu_pt>looseLep_mu_pt && looseLep_mu_pt>vetoLep_mu_pt) ){
    cout << "   Problem with muon pT hierachy for good, loose, and veto pT!" << endl;
    cout << "     Exiting..." << endl;
    return 0;
  }

  if( !(goodLep_el_pt>looseLep_el_pt && looseLep_el_pt>vetoLep_el_pt) ){
    cout << "   Problem with electron pT hierarchy for good, loose, and veto pT!" << endl;
    cout << "     Exiting..." << endl;
    return 0;
  }


  //
  // Set Skim Variables
  //
  mylooper->setSkimVariables( nVtx, met, nGoodLeptons, goodLep_el_pt,  goodLep_el_eta,  goodLep_mu_pt,  goodLep_mu_eta, looseLep_el_pt, looseLep_el_eta, looseLep_mu_pt, looseLep_mu_eta, vetoLep_el_pt, vetoLep_el_eta, vetoLep_mu_pt, vetoLep_mu_eta, apply2ndlepVeto,nJets, jet_pt, jet_eta, jet_ak8_pt, jet_ak8_eta, nBJets,  nphs, phs_pt, phs_eta, applyJECfromFile, JES_central_up_down, applyLeptonSFs, applyVetoLeptonSFs, applyBtagSFs, isFastsim, filltaus_,  filltracks_,  fillZll_,  fillPhoton_, fillMETfilt_,  fill2ndlep_,  fillExtraEvtVar_,  fillAK4EF_,  fillAK4_Other_,  fillOverleps_,  fillAK4Synch_,  fillElID_,  fillIso_,  fillLepSynch_);

  
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
