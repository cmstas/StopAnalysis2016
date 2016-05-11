#include "TList.h"
#include "TMath.h"
#include "TString.h"
#include "TObject.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TH3F.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TH3D.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TMap.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TStopwatch.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <cmath>
//This one is dependent on sourced CMSSW release - needed to convert significance into p-value
#include "RooStats/RooStatsUtils.h"

using namespace std;

TString inputdir = "/hadoop/cms/store/user/haweber/condor/significances/";
TString outputdir = "rootfiles/";
void Make2DSignifHistos(TString signaltype, int analysis=0, bool fakedata=false, bool nosigunc=false, bool nobkgunc=false, bool dropsigcont=false, bool correlated=true, TString inputdir = "/hadoop/cms/store/user/haweber/condor/limits/", TString outputdir = "rootfiles/");
TH2F* InterpolateThisHistogram(TH2F *hold);
TGraph2D* GetInterpolatingGraph(TH2F *hold);
TH2F* PassThisHistogram(TH2F *hold);
TH2F* XsecThisHistogram(TH2F *hold, TH1D *hxsec);
TGraph* GetContour(TGraph2D *g, TString name);
inline TString MakeOutputDir(TString dir);
string analysisname(int analysis=0);

inline TString MakeOutputDir(TString dir){
  if(!dir.EndsWith("/")) dir += "/";
  // Create directory if needed
  //  >> NOTE: This function needs to be called before the booking functions!
  char cmd[100];
  sprintf(cmd,"mkdir -p %s", dir.Data());
  system(cmd);
  return dir;
}

//root [0] RooStats::PValueToSignificance(0.0762011)
//(Double_t) 1.431098e+00
//root [1] RooStats::SignificanceToPValue(1.4311)
//(Double_t) 7.620078e-02

void Make2DSignifHistos(TString signaltype, int analysis, bool fakedata, bool nosigunc, bool nobkgunc, bool dropsigcont, bool correlated, TString inputdir, TString outputdir){

  string anname = analysisname(analysis);
  if(anname=="BS") {
    cout << "Your analysis does not exist. exiting..." << endl;
    return;
  }
  TH1D *hxsec;
  TFile *fxsec = new TFile("xsec_stop_13TeV.root","READ");
  if(fxsec->IsZombie()) {
    std::cout << "Somehow xsec_stop_13TeV.root is corrupted. Exit..." << std::endl;
    return;
  }
  hxsec = (TH1D*)fxsec->Get("stop");
  
  int mStopLow  = 100;
  int mStopHigh = 1000;
  int mStopStep = 25;
  int mLSPLow   = 0;
  int mLSPHigh  = 500;
  int mLSPStep  = 25;
  int nbinsx = (mStopHigh - mStopLow)/mStopStep;
  int nbinsy = (mLSPHigh - mLSPLow)/mLSPStep;
  
  TString myoutputdir = outputdir;
  if(correlated) myoutputdir = myoutputdir + "correlated/";
  if(nosigunc&&nobkgunc) myoutputdir = myoutputdir + "nounc/";
  else if(nosigunc) myoutputdir = myoutputdir + "nosigunc/";
  else if(nobkgunc) myoutputdir = myoutputdir + "nobkgunc/";
  if(dropsigcont) myoutputdir = myoutputdir + "dropsigcont/";
  if(fakedata)   myoutputdir = myoutputdir + "fakedata/";
  cout << "make directory " << myoutputdir << endl;
  MakeOutputDir(myoutputdir);
  TString myinputdir = inputdir;
   if(correlated) myinputdir = myinputdir + "correlated/";
  if(nosigunc&&nobkgunc) myinputdir = myinputdir + "nounc/";
  else if(nosigunc) myinputdir = myinputdir + "nosigunc/";
  else if(nobkgunc) myinputdir = myinputdir + "nobkgunc/";
  if(dropsigcont) myinputdir = myinputdir + "dropsigcont/";
  if(fakedata)   myinputdir = myinputdir + "fakedata/";
  cout << "inputs from " << myinputdir << endl;

  TString outfilename = myoutputdir + "Significances2DHistograms_"+anname+"_"+signaltype+".root";
  TFile *file = new TFile(outfilename, "recreate");
  file->cd();
  TH2F *hExpPosterioriOrg   = new TH2F("hExpPosterioriOrg",  "hExpPosterioriOrg" , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hExpPrioriOrg       = new TH2F("hExpPrioriOrg",      "hExpPrioriOrg"     , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hObsOrg             = new TH2F("hObsOrg",            "hObsOrg"           , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hpExpPosterioriOrg  = new TH2F("hpExpPosterioriOrg", "hpExpPosterioriOrg", nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hpExpPrioriOrg      = new TH2F("hpExpPrioriOrg",     "hpExpPrioriOrg"    , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hpObsOrg            = new TH2F("hpObsOrg",           "hpObsOrg"          , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hExpPosteriori   = new TH2F("hExpPosteriori",  "hExpPosteriori" , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hExpPriori       = new TH2F("hExpPriori",      "hExpPriori"     , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hObs             = new TH2F("hObs",            "hObs"           , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hpExpPosteriori  = new TH2F("hpExpPosteriori", "hpExpPosteriori", nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hpExpPriori      = new TH2F("hpExpPriori",     "hpExpPriori"    , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);
  TH2F *hpObs            = new TH2F("hpObs",           "hpObs"          , nbinsx, mStopLow, mStopHigh, nbinsy, mLSPLow, mLSPHigh);



  cout << "First create 2d limit histograms" << endl;
  for(int stop = mStopLow; stop<=mStopHigh; stop += mStopStep){
    for(int lsp = mLSPLow; lsp<=mLSPHigh; lsp += mLSPStep){
      TString limitfilebase = "Signif_ProfileLikelihood_";
      TString signalname = signaltype + "_" + std::to_string(stop) + "_" + std::to_string(lsp);
      TString limitfileObs  = myinputdir + limitfilebase + "Obs_" + anname + "_" + signalname + ".root";
      TString limitfileExp1 = myinputdir + limitfilebase + "ExpPriori_" + anname + "_" + signalname + ".root";
      TString limitfileExp2 = myinputdir + limitfilebase + "ExpPosteriori_" + anname + "_" + signalname + ".root";
      //cout << limitfile << endl;
      ifstream infile1(limitfileObs.Data());
      bool exists = infile1.good();
      if(!exists) {
	//cout << "No limit name for " << signalname << " - exit: " << limitfileObs.Data() << endl;
	continue;
      }
      ifstream infile2(limitfileExp1.Data());
      if(!(infile2.good())) continue;
      ifstream infile3(limitfileExp2.Data());
      if(!(infile3.good())) continue;
      
      cout << "Significances files exist for " << signalname << endl;
      double obsS    = -1.0; //observed limit
      double obsp    = -1.0; //observed limit
      double exp1S   = -1.0; //expected limit - priori
      double exp1p   = -1.0; //expected limit - priori
      double exp2S   = -1.0; //expected limit - posteriori
      double exp2p   = -1.0; //expected limit - posteriori
      
      double value = -1.0;
      TFile *flimitO;
      flimitO = new TFile(limitfileObs,"READ");
      if(flimitO->IsZombie()) {
	flimitO->Close();
	delete flimitO;
	cout << "No limit file for " << signalname << " - exit" << endl;
	continue;
      }
      flimitO->cd();
      TTree *tlimit1 = (TTree*)flimitO->Get("limit");
      tlimit1->SetBranchAddress("limit", &value);
      tlimit1->GetEntry(0);
      obsS = value;
      delete tlimit1;
      flimitO->Close();
      delete flimitO;
      value = -1.0;      
      TFile *flimitE;
      flimitE = new TFile(limitfileExp1,"READ");
      if(flimitE->IsZombie()) {
	flimitE->Close();
	delete flimitE;
	cout << "No limit file for " << signalname << " - exit" << endl;
	continue;
      }
      flimitE->cd();
      TTree *tlimit2 = (TTree*)flimitE->Get("limit");
      tlimit2->SetBranchAddress("limit", &value);
      tlimit2->GetEntry(0);
      exp1S = value;
      delete tlimit2;
      flimitE->Close();
      delete flimitE;
      value = -1.0;            
      TFile *flimitF;
      flimitF = new TFile(limitfileExp2,"READ");
      if(flimitF->IsZombie()) {
	flimitF->Close();
	delete flimitO;
	cout << "No limit file for " << signalname << " - exit" << endl;
	continue;
      }
      flimitF->cd();
      TTree *tlimit3 = (TTree*)flimitF->Get("limit");
      tlimit3->SetBranchAddress("limit", &value);
      tlimit3->GetEntry(0);
      exp2S = value;
      delete tlimit3;
      flimitF->Close();
      delete flimitF;

      obsp  = RooStats::SignificanceToPValue(obsS);
      exp1p = RooStats::SignificanceToPValue(exp1S);
      exp2p = RooStats::SignificanceToPValue(exp2S);
 
      file->cd();

      hpExpPrioriOrg     ->Fill(stop,lsp,exp1p  );
      hpExpPosterioriOrg ->Fill(stop,lsp,exp2p  );
      hpObsOrg           ->Fill(stop,lsp,obsp   );
      hExpPrioriOrg      ->Fill(stop,lsp,exp1S  );
      hExpPosterioriOrg  ->Fill(stop,lsp,exp2S  );
      hObsOrg            ->Fill(stop,lsp,obsS   );

    }//lsp
  }//stop
  cout << "Now interpolate these histograms" << endl;  
  hpExpPriori     = (TH2F*)InterpolateThisHistogram(hpExpPrioriOrg);
  hpExpPosteriori = (TH2F*)InterpolateThisHistogram(hpExpPosterioriOrg);
  hpObs           = (TH2F*)InterpolateThisHistogram(hpObsOrg);
  hExpPriori      = (TH2F*)InterpolateThisHistogram(hExpPrioriOrg);
  hExpPosteriori  = (TH2F*)InterpolateThisHistogram(hExpPosterioriOrg);
  hObs            = (TH2F*)InterpolateThisHistogram(hObsOrg);

  file->cd();

  hpExpPriori       ->Write();
  hpExpPosteriori   ->Write();
  hpObs             ->Write();
  hExpPriori        ->Write();
  hExpPosteriori    ->Write();
  hObs              ->Write();
  hpExpPrioriOrg    ->Write();
  hpExpPosterioriOrg->Write();
  hpObsOrg          ->Write();
  hExpPrioriOrg     ->Write();
  hExpPosterioriOrg ->Write();
  hObsOrg           ->Write();


  file->Close();
  cout << "Saved all histos in  " << file->GetName() << endl;

  fxsec->Close();
  delete fxsec;
  
}

TH2F* InterpolateThisHistogram(TH2F *hold/*, TH2F* hnew*/){
  float binsize = hold->GetXaxis()->GetBinWidth(1)/2.;
  TString name = hold->GetName();
  name.ReplaceAll("Org","");
  TGraph2D *g = new TGraph2D(hold);
  //cout << g->GetXmax() << " " << g->GetXmin() << " " << g->GetYmax() << " " << g->GetYmin() << " " << binsize << endl;
  g->SetNpx(int(g->GetXmax()-g->GetXmin())/binsize);
  g->SetNpy(int(g->GetYmax()-g->GetYmin())/binsize);
  TH2F *hnew = (TH2F*)g->GetHistogram();
  //TH2F *htemp = (TH2F*)hnew->Clone(name);
  //name.ReplaceAll("YXZ","");
  TH2F *h = new TH2F(name.Data(),hold->GetTitle(),hnew->GetNbinsX(),g->GetXmin()-binsize,g->GetXmax()-binsize,hnew->GetNbinsY(),g->GetYmin()-binsize,g->GetYmax()-binsize);
  for(unsigned int x = 1; x<=hnew->GetNbinsX(); ++x){
    for(unsigned int y = 1; y<=hnew->GetNbinsY(); ++y){
      h->SetBinContent(x,y,hnew->GetBinContent(x,y));
    }
  }
  delete g;
  return h;
}

TGraph2D* GetInterpolatingGraph(TH2F *hold){
  float binsize = hold->GetXaxis()->GetBinWidth(1)/2.;
  TString name = hold->GetName();
  name.ReplaceAll("Org","");
  TGraph2D *g = new TGraph2D(hold);
  g->SetNpx(int(g->GetXmax()-g->GetXmin())/binsize);
  g->SetNpy(int(g->GetYmax()-g->GetYmin())/binsize);
  return g;
}

TH2F* PassThisHistogram(TH2F *hold){
  TString name = hold->GetName() + (TString)"Pass";
  TH2F *hnew = (TH2F*)hold->Clone(name);
  for(int x = 1; x<=hnew->GetNbinsX(); ++x){
    for(int y = 1; y<=hnew->GetNbinsY(); ++y){
      float val = hnew->GetBinContent(x,y);
      float pass = 0;
      if(val>1) pass = 0.001;
      else if(val>0) pass = 1;
      hnew->SetBinContent(x,y,pass);
    }
  }
  return hnew;
}

TH2F* XsecThisHistogram(TH2F *hold, TH1D *hxsec){
  TString name = hold->GetName() + (TString)"Xsec";
  TH2F *hnew = (TH2F*)hold->Clone(name);
  for(int x = 1; x<=hnew->GetNbinsX(); ++x){
    for(int y = 1; y<=hnew->GetNbinsY(); ++y){
      float val = hnew->GetBinContent(x,y);
      float mstop = hnew->GetXaxis()->GetBinLowEdge(x);
      float xsec = hxsec->GetBinContent(hxsec->FindBin(mstop));
      hnew->SetBinContent(x,y,val*xsec);
    }
  }
  return hnew;
}

TGraph* GetContour(TGraph2D *g, TString name){
  TGraph *gnew;
  TH2D *temp = (TH2D*)g->GetHistogram();//need this for list to work?
  //g->Draw("alp");//need this for list to work?
  TList *glist = (TList*)g->GetContourList(1.0);
  if(glist == nullptr) return gnew;
  int max_points = -1;
  int nn = glist->GetSize();
  for(int i = 0; i<glist->GetSize(); ++i){
    TGraph *gtemp = (TGraph*)glist->At(i);
    int Npoints = gtemp->GetN();
    if(Npoints>max_points){
      gnew = (TGraph*)gtemp->Clone(name);
      max_points = Npoints;
    }
  }
  return gnew;
}

string analysisname(int analysis){
  if(analysis==0) return "std";//standard 
  else return "BS";
}
