#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TString.h"

int skimBaby(TString inFileName="output.root", TString outFileName="skim.root"){


  //
  // Input File i/o
  //

  // Open input file
  TFile *inFile = new TFile(inFileName.Data(), "read");

  bool isSignalScan=false;
  if(inFileName.Contains("SMS") || 
     inFileName.Contains("Signal") ) isSignalScan=true;

  // Grab histogram counters
  TH1D *h_counter=NULL;
  TH2D *h_scan_nEvents=NULL;
  TH3D *h_scan_counter=NULL;
  if(isSignalScan){
    h_scan_nEvents = (TH2D*)inFile->Get("histNEvts");
    h_scan_counter = (TH3D*)inFile->Get("h_counterSMS");
  }
  else{
    h_counter = (TH1D*)inFile->Get("h_counter");
  }

  // Grab ttree
  TTree *t = (TTree*)inFile->Get("t");



  //
  // Set variables that need to be accessed in skim
  //

  // Met
  float cut_met = 150.0;
  int nEvents_pass_met=0;
  
  float met=0.0;
  float met_jup=0.0;
  float met_jdown=0.0;

  t->SetBranchAddress("pfmet", &met);
  t->SetBranchAddress("pfmet_jup", &met_jup);
  t->SetBranchAddress("pfmet_jdown", &met_jdown);

  float met_rl=0.0;
  float met_rl_jup=0.0;
  float met_rl_jdown=0.0;

  t->SetBranchAddress("pfmet_rl", &met_rl);
  t->SetBranchAddress("pfmet_rl_jup", &met_rl_jup);
  t->SetBranchAddress("pfmet_rl_jdown", &met_rl_jdown);

  // MT
  float cut_mt = 150.0;
  int nEvents_pass_mt=0;
      
  float mt=0.0;
  float mt_jup=0.0;
  float mt_jdown=0.0;
  
  t->SetBranchAddress("mt_met_lep", &mt);
  t->SetBranchAddress("mt_met_lep_jup", &mt_jup);
  t->SetBranchAddress("mt_met_lep_jdown", &mt_jdown);

  float mt_rl=0.0;
  float mt_rl_jup=0.0;
  float mt_rl_jdown=0.0;

  t->SetBranchAddress("mt_met_lep_rl", &mt_rl);
  t->SetBranchAddress("mt_met_lep_rl_jup", &mt_rl_jup);
  t->SetBranchAddress("mt_met_lep_rl_jdown", &mt_rl_jdown);

  // MinDPhi(met,j1/j2)
  float cut_minDPhi = 0.5;
  int nEvents_pass_minDPhi=0;

  float minDPhi=0.0;
  float minDPhi_jup=0.0;
  float minDPhi_jdown=0.0;

  t->SetBranchAddress("mindphi_met_j1_j2", &minDPhi);
  t->SetBranchAddress("mindphi_met_j1_j2_jup", &minDPhi_jup);
  t->SetBranchAddress("mindphi_met_j1_j2_jdown", &minDPhi_jdown);

  float minDPhi_rl=0.0;
  float minDPhi_rl_jup=0.0;
  float minDPhi_rl_jdown=0.0;

  t->SetBranchAddress("mindphi_met_j1_j2_rl", &minDPhi_rl);
  t->SetBranchAddress("mindphi_met_j1_j2_rl_jup", &minDPhi_rl_jup);
  t->SetBranchAddress("mindphi_met_j1_j2_rl_jdown", &minDPhi_rl_jdown);



  //
  // Output File i/o
  //
  
  // Open ouput file
  TFile *outFile = new TFile(outFileName.Data(), "recreate");

  // Clone histograms
  TH1D *h_counter_out=NULL;
  TH2D *h_scan_nEvents_out=NULL;
  TH3D *h_scan_counter_out=NULL;
  if(isSignalScan){
    h_scan_nEvents_out = (TH2D*)h_scan_nEvents->Clone();
    h_scan_nEvents_out->SetDirectory(outFile);

    h_scan_counter_out = (TH3D*)h_scan_counter->Clone();
    h_scan_counter_out->SetDirectory(outFile);
  }
  else{
    h_counter_out = (TH1D*)inFile->Get("h_counter");
    h_counter_out->SetDirectory(outFile);
  }

  // Clone Tree
  TTree *t_out = (TTree*)t->CloneTree(0);



  //
  // Loop over events and check if they pass selection
  //

  int nEvents = t->GetEntries();
  for(int iEvt=0; iEvt<nEvents; iEvt++){

    // Grab entry
    t->GetEntry(iEvt);


    // Progress
    if(iEvt!=0){
      int period = 1000;
      if(iEvt%1000 == 0) {
	// xterm magic from L. Vacavant and A. Cerri
	if (isatty(1)) {
	  if( ( nEvents - iEvt ) > period ){
	    float frac = (float)iEvt/(nEvents*0.01);
	    printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
		   "\033[0m\033[32m <---\033[0m\015", frac);
	    fflush(stdout);
	  }
	  else {
	    printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
		   "\033[0m\033[32m <---\033[0m\015", 100.);
	    cout << endl;
	  }
	}
      }
    }


    // Selection

    // MET
    if( met<cut_met &&
	met_jup<cut_met &&
	met_jdown<cut_met &&
	met_rl<cut_met &&
	met_rl_jup<cut_met &&
	met_rl_jdown<cut_met  ) continue;
    
    nEvents_pass_met++;
    
    // MT
    if( mt<cut_mt && 
	mt_jup<cut_mt &&
	mt_jdown<cut_mt &&
	mt_rl<cut_mt && 
	mt_rl_jup<cut_mt &&
	mt_rl_jdown<cut_mt  ) continue;

    nEvents_pass_mt++;

    // MinDphi(met,j1/j2)
    if( minDPhi<cut_minDPhi &&
	minDPhi_jup<cut_minDPhi &&
	minDPhi_jdown<cut_minDPhi &&
	minDPhi_rl<cut_minDPhi &&
	minDPhi_rl_jup<cut_minDPhi &&
	minDPhi_rl_jdown<cut_minDPhi   ) continue;

    nEvents_pass_minDPhi++;

    // Fill new tree
    t_out->Fill();

  } // end loop over events



  //
  // Print Results
  //
  cout << "=====================================================" << endl;
  cout << "    NEvents scanned = " << nEvents << endl;
  cout << "    NEvents pass met>" << cut_met << " = " << nEvents_pass_met << " (" << 100.0*(double)nEvents_pass_met/(double)nEvents << "%)" << endl;
  cout << "    NEvents pass mt>" << cut_mt << " = " << nEvents_pass_mt << " (" << 100.0*(double)nEvents_pass_mt/(double)nEvents_pass_met << "%)" << endl;
  cout << "    NEvents pass minDphi>" << cut_minDPhi << " = " << nEvents_pass_minDPhi << " (" << 100.0*(double)nEvents_pass_minDPhi/(double)nEvents_pass_mt << "%)" << endl;
  cout << "=====================================================" << endl;
  cout << endl;


  //
  // Write output
  //
  t_out->AutoSave();
  outFile->Write();
  outFile->Close();
  inFile->Close();


  return 0;
}
