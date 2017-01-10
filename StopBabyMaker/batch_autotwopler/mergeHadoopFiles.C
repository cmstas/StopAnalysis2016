#include "Riostream.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TString.h"

#include <vector>

void mergeHadoopFiles(const TString& indir, const TString& outpath) {

  // Print user commands
  cout << "Merging files from dir: " << indir << endl;
  cout << "Ouputting to: " << outpath << endl;

  // Declare new TChain
  TChain *chain = new TChain("t");
  chain->SetMaxTreeSize(5000000000LL); //default is 100000000000LL = 100Gb

  // Get number of files from input directory
  int nFiles_in = (int)chain->Add( Form("%s/*.root", indir.Data() ) );

  // Merge chain
  int nFiles_out = chain->Merge(outpath, "fast");
  
  // Create list of names of histograms to add as well
  std::vector<TString> histNames;
  histNames.push_back( "h_counter" );

  // Get number of histograms
  const int nHistos = (int) histNames.size();

  // Get first output file
  TFile *f_output = new TFile(outpath, "update");

  // Initialize pointers for each histogram
  TH1D *histos[nHistos];
  bool h1Dexists[nHistos];
  for(int iHist=0; iHist<nHistos; iHist++){
    histos[iHist]=NULL;
    h1Dexists[iHist]=false;
  }
  TH3D *histos3D=NULL;
  TH2F *histos2D=NULL;
  bool h3Dexists = false;
  bool h2Dexists = false;
  // Loop over input files, adding histograms
  bool firstFile=true;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  while ( (currentFile = (TFile*)fileIter.Next()) ) { 
    
    // Open input file
    TFile file(  currentFile->GetTitle() );
    
    // Check if input file exists
    if( file.IsZombie() ) continue;
    
    // Loop over histograms in file to add them
    for(int iHist=0; iHist<nHistos; iHist++){
      
      // If this is the first file, then clone the histos
      if( firstFile ){
	if(file.GetListOfKeys()->Contains(histNames[iHist])) {
	  cout << "1D file exists" << endl;
	  h1Dexists[iHist] = true;
	  TH1D *h_temp = (TH1D*)file.Get( histNames[iHist] );
	  histos[iHist] = (TH1D*)h_temp->Clone();
	  histos[iHist]->SetDirectory(f_output);
	}
      }
      // If not the first file, then add the histos
      else if(h1Dexists[iHist]){
	TH1D *h_temp = (TH1D*)file.Get( histNames[iHist] );
	histos[iHist]->Add( h_temp );
      }
      
    } // end loop over histograms
    
    if( firstFile ){
      if(file.GetListOfKeys()->Contains("h_counterSMS")) {
	cout << "3D file exists" << endl;
	h3Dexists = true;
	TH3D *h_temp3D = (TH3D*)file.Get("h_counterSMS");
	histos3D = (TH3D*)h_temp3D->Clone();
	histos3D->SetDirectory(f_output);
      }
    } else if(h3Dexists) {
      TH3D *h_temp3D = (TH3D*)file.Get("h_counterSMS");
      histos3D->Add(h_temp3D);
    }

    if( firstFile ){
      if(file.GetListOfKeys()->Contains("histNEvts")) {
	cout << "2D file exists" << endl;
	h2Dexists = true;
	TH2F *h_temp2F = (TH2F*)file.Get("histNEvts");
	histos2D = (TH2F*)h_temp2F->Clone();
	histos2D->SetDirectory(f_output);
      }
    } else if(h2Dexists) {
      TH2F *h_temp2F = (TH2F*)file.Get("histNEvts");
      histos2D->Add(h_temp2F);
    }
    // Close input file
    file.Close();

    firstFile=false;

  } // end loop over input files

  f_output->Write();


  // Copy histograms to output files
  if(nFiles_out>1){

    TString outpath_base = outpath;
    outpath_base.ReplaceAll(".root","");
    
    for(int iFile=1; iFile<nFiles_out; iFile++){

      TString iOutPath = Form( "%s_%d.root", outpath_base.Data(), iFile );
      TFile *outFile = new TFile(iOutPath, "update");

      TH1D *h_temp[nHistos];
      if(h3Dexists){
	TH3D *h_temp_3D=NULL;
	h_temp_3D = (TH3D*)histos3D->Clone();
	h_temp_3D->SetDirectory(outFile);
      }
      if(h2Dexists){
	TH2F *h_temp_2D=NULL;
	h_temp_2D = (TH2F*)histos2D->Clone();
	h_temp_2D->SetDirectory(outFile);
      }
      for(int iHist=0; iHist<nHistos; iHist++) h_temp[iHist]=NULL;

      for(int iHist=0; iHist<nHistos; iHist++){
	if(h1Dexists[iHist]){
	  h_temp[iHist] = (TH1D*)histos[iHist]->Clone();
	  h_temp[iHist]->SetDirectory(outFile);
	}
      } // end loop over histograms

      // Clean up outfile
      outFile->Write();
      outFile->Close();
      delete outFile;

    } // end loop over output files

  } // end if nFiles_out>1

  // Clean up
  f_output->Close();
  delete f_output;

  return;
}
