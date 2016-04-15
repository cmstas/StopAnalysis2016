// Usage:
// > root -b doAll.C

// C++
#include <iostream>
#include <vector>
#include <map>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLorentzVector.h"
#include "TH3D.h"
#include "TH2F.h"

// CMS3
#include "StopNTuple.cc"
#include "StopFunctions.cc"
#include "Utilities.hh"

using namespace std;
using namespace tas;


int ScanChain( TChain* chain, string samplename, int JES = 0, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  int maxSR = 9;
  int nST  = 37; double STl  =  87.5; double STu  = 1012.5;
  int nLSP = 19; double LSPl = -12.5; double LSPu =  462.5;
  
  TFile *fxsec = new TFile("inputs/xsec_stop_13TeV.root","READ");
  TH1D *hxsec     = (TH1D*)fxsec->Get("stop");
  
  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");


  map<string, TH3D*> histos;//use D histos as weights can vary a lot among the signal
  vector<string> histonames; histonames.clear();
  map<string, TH3D*> histos2;//use D histos as weights can vary a lot among the signal
  vector<string> histonames2; histonames2.clear();
  //  vector<int> hbins; hbins.clear();
  //  vector<float> hlow; hlow.clear();
  //  vector<float> hup; hup.clear();

  //lumi, trigger, stats done
  histonames.push_back("SR_yield");
  histonames.push_back("SR_BHFup");
  histonames.push_back("SR_BHFdown");
  histonames.push_back("SR_BLFup");
  histonames.push_back("SR_BLFdown");
  histonames.push_back("SR_JESup");
  histonames.push_back("SR_JESdown");
  histonames.push_back("SR_muRFup");
  histonames.push_back("SR_muRFdown");
  histonames.push_back("SR_ISRup");
  histonames.push_back("SR_ISRdown");
  histonames.push_back("SR_LepEffup");//done - I guess we need no renormalization - no fastsim in, no vetoSF
  histonames.push_back("SR_LepEffdown");
  histonames.push_back("SR_LepEffFSup");//done - I guess we need no renormalization - no fastsim in, no vetoSF
  histonames.push_back("SR_LepEffFSdown");
  histonames.push_back("SR_Xsecup");//done
  histonames.push_back("SR_Xsecdown");
  histonames.push_back("CR0b_sigcontamination");//scaled to signalreg yield
  histonames.push_back("CR2l_sigcontamination");//scaled to signalreg yield
  
  histonames2.push_back("eventsum");
  histonames2.push_back("rawweightsum");
  histonames2.push_back("totweightsum");
  histonames2.push_back("ISRsum");
  histonames2.push_back("BSFsum");
  histonames2.push_back("PUweightsum");
  histonames2.push_back("xsecsum");
  histonames2.push_back("nevtsum");
  histonames2.push_back("lepsum");
  histonames2.push_back("lepSFsum");
  string T2tt = "T2tt";
  string T2tb = "T2tb";
  for(unsigned int i = 0; i<histonames.size(); ++i){
    string mysample = samplename;
    for(unsigned int j = 0; j<3; ++j){
      //add polarization or split mixed decay
      if(samplename.find(T2tt)!=string::npos){
	if(j==1)      mysample = samplename + "_lefthanded";
	else if(j==2) mysample = samplename + "_righthanded";
      }
      else if(samplename.find(T2tb)!=string::npos){
	if(j==0)      mysample = samplename + "_tLSP";
	else if(j==1) mysample = samplename + "_mixed";
	else if(j==2) mysample = samplename + "_bCharg";
      }
      else if(j!=0) continue;
      string mapname = histonames[i] + "_" + mysample;
      if(histos.count(mapname) == 0 ) histos[mapname] = new TH3D(mapname.c_str(), "", nST,STl,STu, nLSP,LSPl,LSPu, maxSR, 1.,1.+maxSR);
      //mStop 100-1000, mLSP 0-450, SR 1-12, 9200 bins, SR 0 is non-SR - in case it it needed!!
      histos[mapname]->Sumw2(); histos[mapname]->SetDirectory(rootdir);
    }
  }
  for(unsigned int i = 0; i<histonames2.size(); ++i){
    string mapname = histonames2[i];
    if(histos2.count(mapname) == 0 ) histos2[mapname] = new TH3D(mapname.c_str(), "", nST,STl,STu, nLSP,LSPl,LSPu, maxSR, 1.,1.+maxSR);
    //mStop 100-1000, mLSP 0-450, SR 1-12, 9200 bins, SR 0 is non-SR - in case it it needed!!
    histos2[mapname]->Sumw2(); histos2[mapname]->SetDirectory(rootdir);
  }

  float lumi = Util::loadSF("Luminosity", "inputs/Weights.dat");
  //SF CR-->SR
  float CR0b_1_1 = Util::loadSF("CR0b_1_1", "inputs/Weights.dat");
  float CR0b_1_2 = Util::loadSF("CR0b_1_2", "inputs/Weights.dat");
  float CR0b_2_3 = Util::loadSF("CR0b_2_3", "inputs/Weights.dat");
  float CR0b_2_4 = Util::loadSF("CR0b_2_4", "inputs/Weights.dat");
  float CR0b_3_7 = Util::loadSF("CR0b_3_7", "inputs/Weights.dat");
  float CR0b_3_8 = Util::loadSF("CR0b_3_8", "inputs/Weights.dat");
  float CR0b_3_9 = Util::loadSF("CR0b_3_9", "inputs/Weights.dat");
  float CR2l_1_1 = Util::loadSF("CR2l_1_1", "inputs/Weights.dat");
  float CR2l_1_2 = Util::loadSF("CR2l_1_2", "inputs/Weights.dat");
  float CR2l_2_5 = Util::loadSF("CR2l_2_5", "inputs/Weights.dat");
  float CR2l_2_6 = Util::loadSF("CR2l_2_6", "inputs/Weights.dat");
  float CR2l_3_3 = Util::loadSF("CR2l_3_3", "inputs/Weights.dat");
  float CR2l_3_4 = Util::loadSF("CR2l_3_4", "inputs/Weights.dat");
  float CR2l_3_7 = Util::loadSF("CR2l_3_7", "inputs/Weights.dat");
  float CR2l_3_8 = Util::loadSF("CR2l_3_8", "inputs/Weights.dat");
  float CR2l_3_9 = Util::loadSF("CR2l_3_9", "inputs/Weights.dat");
  
  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //get the reweighting histograms
  TH3D* counterhistSig;
  TH2F* histNEvts;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() );
    counterhistSig = (TH3D*)file->Get("h_counterSMS");//this should be fine, unless two rootfiles have the same mass point
    counterhistSig->SetDirectory(0); 
    histNEvts = (TH2F*)file->Get("histNEvts");
    histNEvts->SetDirectory(0);
    TTree *tree = (TTree*)file->Get("t");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    cms3.Init(tree);
    
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {
 
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      cms3.GetEntry(event);
      ++nEventsTotal;
    
      // Progress
      StopNTuple::progress( nEventsTotal, nEventsChain );

      // Analysis Code

      float mStop  = tas::mass_stop();
      float mLSP   = tas::mass_lsp();
      float mCharg = tas::mass_chargino();
      int   Nevts  = histNEvts->GetBinContent(histNEvts->FindBin(mStop,mLSP));
      double nevts = double(Nevts);
      //float weight = cms3.scale1fb()*2.11;
      double ISRnorm      = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,19));
      double ISRnormup    = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,20));
      double ISRnormdown  = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,21));
      double ISRweight    = tas::weight_ISR();
      double BSFnorm      = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,14));
      double BSFnormHup   = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,15));
      double BSFnormLup   = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,16));
      double BSFnormHdown = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,17));
      double BSFnormLdown = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,18));
      double BSFweight    = tas::weight_btagsf();
      double muRFnorm     = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,1));
      double muRFnormup   = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,5));
      double muRFnormdown = counterhistSig->GetBinContent(counterhistSig->FindBin(mStop,mLSP,9));
      if(ISRnorm>0) ISRweight*=nevts/ISRnorm;
      if(ISRnorm<=0||ISRnormup<=0||ISRnormdown<=0){ ISRnormdown=1.; ISRnormup=1.; ISRnorm=1.;}
      if(BSFnorm>0) BSFweight *=nevts/BSFnorm;
      if(BSFnorm<=0||BSFnormHup<=0||BSFnormLup<=0||BSFnormHdown<=0||BSFnormLdown<=0){//in 2015 had no meaning, but still keep it for safety reasons
	BSFnorm=1; BSFnormHup=1; BSFnormLup=1; BSFnormHdown=1; BSFnormLdown=1;
      }
      if(muRFnorm<=0||muRFnormup<=0||muRFnormdown<=0){ muRFnormdown=1; muRFnormup=1; muRFnorm=1; }
      //lepSF is done below
      double xsection = hxsec->GetBinContent(hxsec->FindBin(mStop));
      double xsectionerr = hxsec->GetBinError(hxsec->FindBin(mStop));
      double rawweight = xsection*lumi/nevts;
      double weight = rawweight*ISRweight*BSFweight;//xsec given in pb
      //double weight = rawweight*ISRweight*BSFweight*tas::weight_lepSF();//babies not ready
      if(event==0) cout << "weight " << weight << " nEvents " << nEventsTree << " filename " << currentFile->GetTitle() << endl;

      //get SR and CR bins
      if(StF::isSignalOrControlRegion()==false) continue;
      int SR = StF::SRIdentifier();
      int CR2l = StF::CR2lIdentifier();
      int CR0b = StF::CR0bIdentifier();
      if(SR<0&&CR2l<0&&CR0b<0) continue;

      string thissample = samplename;
      if(thissample.find(T2tb)!=string::npos){
	int T2tb_what = StF::whichT2tbdecay();
	if(     T2tb_what==1) thissample = samplename + "_tLSP";
	else if(T2tb_what==2) thissample = samplename + "_mixed";
	else if(T2tb_what==3) thissample = samplename + "_bCharg";
	else continue;
      }
      bool dopolarization = false;
      if(thissample.find(T2tt)!=string::npos) dopolarization = true;
      float weight_pol_L(1.), weight_pol_R(1.);
      if(dopolarization&&((mStop-mLSP)>172)) StF::PolarizationWeights(weight_pol_L,weight_pol_R);
      string thissampleL = thissample + "_lefthanded";
      string thissampleR = thissample + "_righthanded";
      float weightL = weight * weight_pol_L;
      float weightR = weight * weight_pol_R;
      
      double ISRup = tas::weight_ISRup()/tas::weight_ISR()*ISRnorm/ISRnormup;
      double ISRdown = tas::weight_ISRdown()/tas::weight_ISR()*ISRnorm/ISRnormdown;
      double XSup = (xsection+xsectionerr)/xsection;
      double XSdown = (xsection-xsectionerr)/xsection;
      //double lEffup = lepSF_Up/lepSF;//not available yet in babies
      //double lEffdown = lepSF_Dn/lepSF;
      //double lEffFSup = lepSF_FS_Up/lepSF_FS;
      //double lEffFSdown = lepSF_FS_Dn/lepSF_FS;
      double BSFHup = tas::weight_btagsf_heavy_UP()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
      double BSFLup = tas::weight_btagsf_light_UP()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
      double BSFHdown = tas::weight_btagsf_heavy_DN()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
      double BSFLdown = tas::weight_btagsf_light_DN()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
      double muRFup = tas::genweights().at(4)/tas::genweights().at(0)*muRFnorm/muRFnormup;
      double muRFdown = tas::genweights().at(8)/tas::genweights().at(0)*muRFnorm/muRFnormdown;

      if(abs(JES)!=1){
	if(CR0b>0){
	  if(CR0b==1){
	    histos["CR0b_sigcontamination_"+thissample]->Fill(mStop,mLSP,1,weight*CR0b_1_1);
	    histos["CR0b_sigcontamination_"+thissample]->Fill(mStop,mLSP,2,weight*CR0b_1_2);
	  } else if(CR0b==2){
	    histos["CR0b_sigcontamination_"+thissample]->Fill(mStop,mLSP,3,weight*CR0b_2_3);
	    histos["CR0b_sigcontamination_"+thissample]->Fill(mStop,mLSP,4,weight*CR0b_2_4);
	  } else if(CR0b==3){
	    histos["CR0b_sigcontamination_"+thissample]->Fill(mStop,mLSP,7,weight*CR0b_3_7);
	    histos["CR0b_sigcontamination_"+thissample]->Fill(mStop,mLSP,8,weight*CR0b_3_8);
	    histos["CR0b_sigcontamination_"+thissample]->Fill(mStop,mLSP,9,weight*CR0b_3_9);
	  }
	  if(dopolarization){
	    if(CR0b==1){
	      histos["CR0b_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,1,weightL*CR0b_1_1);
	      histos["CR0b_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,2,weightL*CR0b_1_2);
	    } else if(CR0b==2){
	      histos["CR0b_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,3,weightL*CR0b_2_3);
	      histos["CR0b_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,4,weightL*CR0b_2_4);
	    } else if(CR0b==3){
	      histos["CR0b_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,7,weightL*CR0b_3_7);
	      histos["CR0b_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,8,weightL*CR0b_3_8);
	      histos["CR0b_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,9,weightL*CR0b_3_9);
	    }
	    if(CR0b==1){
	      histos["CR0b_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,1,weightR*CR0b_1_1);
	      histos["CR0b_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,2,weightR*CR0b_1_2);
	    } else if(CR0b==2){
	      histos["CR0b_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,3,weightR*CR0b_2_3);
	      histos["CR0b_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,4,weightR*CR0b_2_4);
	    } else if(CR0b==3){
	      histos["CR0b_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,7,weightR*CR0b_3_7);
	      histos["CR0b_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,8,weightR*CR0b_3_8);
	      histos["CR0b_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,9,weightR*CR0b_3_9);
	    }
	  }
	} else if(CR2l>0){
	  if(CR2l==1){
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,1,weight*CR2l_1_1);
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,2,weight*CR2l_1_2);
	  } else if(CR2l==2){
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,5,weight*CR2l_2_5);
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,6,weight*CR2l_2_6);
	  } else if(CR2l==3){
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,7,weight*CR2l_3_7);
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,8,weight*CR2l_3_8);
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,9,weight*CR2l_3_9);
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,3,weight*CR2l_3_3);
	    histos["CR2l_sigcontamination_"+thissample]->Fill(mStop,mLSP,4,weight*CR2l_3_4);
	  }
	  if(dopolarization){
	    if(CR2l==1){
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,1,weightL*CR2l_1_1);
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,2,weightL*CR2l_1_2);
	    } else if(CR2l==2){
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,5,weightL*CR2l_2_5);
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,6,weightL*CR2l_2_6);
	    } else if(CR2l==3){
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,7,weightL*CR2l_3_7);
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,8,weightL*CR2l_3_8);
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,9,weightL*CR2l_3_9);
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,3,weightL*CR2l_3_3);
	      histos["CR2l_sigcontamination_"+thissampleL]->Fill(mStop,mLSP,4,weightL*CR2l_3_4);
	    }
	    if(CR2l==1){
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,1,weightR*CR2l_1_1);
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,2,weightR*CR2l_1_2);
	    } else if(CR2l==2){
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,5,weightR*CR2l_2_5);
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,6,weightR*CR2l_2_6);
	    } else if(CR2l==3){
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,7,weightR*CR2l_3_7);
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,8,weightR*CR2l_3_8);
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,9,weightR*CR2l_3_9);
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,3,weightR*CR2l_3_3);
	      histos["CR2l_sigcontamination_"+thissampleR]->Fill(mStop,mLSP,4,weightR*CR2l_3_4);
	    }
	  }
	} else if(SR>0){

	  histos2["eventsum"]    ->Fill(mStop,mLSP,SR,1.);
	  histos2["rawweightsum"]->Fill(mStop,mLSP,SR,rawweight);
	  histos2["totweightsum"]->Fill(mStop,mLSP,SR,weight);
	  histos2["ISRsum"]      ->Fill(mStop,mLSP,SR,ISRweight);
	  histos2["BSFsum"]      ->Fill(mStop,mLSP,SR,BSFweight);
	  //histos2["PUweightsum"] ->Fill(mStop,mLSP,SR,PUweight);
	  histos2["xsecsum"]     ->Fill(mStop,mLSP,SR,xsection);
	  histos2["nevtsum"]     ->Fill(mStop,mLSP,SR,nevts);
	  //histos2["lepsum"]      ->Fill(mStop,mLSP,SR,lepSF);//lepSF not yet in babies
	  //histos2["lepSFsum"]    ->Fill(mStop,mLSP,SR,lepSF_FS);
	
	  //finally - do signal regions!
	  histos["SR_yield_"       +thissample] ->Fill(mStop,mLSP,SR,weight);
	  histos["SR_ISRup_"       +thissample] ->Fill(mStop,mLSP,SR,weight*ISRup);
	  histos["SR_ISRdown_"     +thissample] ->Fill(mStop,mLSP,SR,weight*ISRdown);
	  histos["SR_Xsecup_"      +thissample] ->Fill(mStop,mLSP,SR,weight*XSup);
	  histos["SR_Xsecdown_"    +thissample] ->Fill(mStop,mLSP,SR,weight*XSdown);
	  //histos["SR_PUup_"        +thissample] ->Fill(mStop,mLSP,SR,weight*PUup);
	  //histos["SR_PUdown_"      +thissample] ->Fill(mStop,mLSP,SR,weight*PUdown);
	  histos["SR_BHFup_"       +thissample] ->Fill(mStop,mLSP,SR,weight*BSFHup);
	  histos["SR_BLFup_"       +thissample] ->Fill(mStop,mLSP,SR,weight*BSFLup);
	  histos["SR_BHFdown_"     +thissample] ->Fill(mStop,mLSP,SR,weight*BSFHdown);
	  histos["SR_BLFdown_"     +thissample] ->Fill(mStop,mLSP,SR,weight*BSFLdown);
	  //histos["SR_LepEffup_"    +thissample] ->Fill(mStop,mLSP,SR,weight*lEffup);//lepSF not yet in babies
	  //histos["SR_LepEffdown_"  +thissample] ->Fill(mStop,mLSP,SR,weight*lEffdown);
	  //histos["SR_LepEffFSup_"  +thissample] ->Fill(mStop,mLSP,SR,weight*lEffFSup);
	  //histos["SR_LepEffFSdown_"+thissample] ->Fill(mStop,mLSP,SR,weight*lEffFSdown);
	  histos["SR_muRFup_"      +thissample] ->Fill(mStop,mLSP,SR,weight*muRFup);
	  histos["SR_muRFdown_"    +thissample] ->Fill(mStop,mLSP,SR,weight*muRFdown);
	  if(dopolarization){
	    histos["SR_yield_"       +thissampleR] ->Fill(mStop,mLSP,SR,weightR);
	    histos["SR_ISRup_"       +thissampleR] ->Fill(mStop,mLSP,SR,weightR*ISRup);
	    histos["SR_ISRdown_"     +thissampleR] ->Fill(mStop,mLSP,SR,weightR*ISRdown);
	    histos["SR_Xsecup_"      +thissampleR] ->Fill(mStop,mLSP,SR,weightR*XSup);
	    histos["SR_Xsecdown_"    +thissampleR] ->Fill(mStop,mLSP,SR,weightR*XSdown);
	    //histos["SR_PUup_"        +thissampleR] ->Fill(mStop,mLSP,SR,weightR*PUup);
	    //histos["SR_PUdown_"      +thissampleR] ->Fill(mStop,mLSP,SR,weightR*PUdown);
	    histos["SR_BHFup_"       +thissampleR] ->Fill(mStop,mLSP,SR,weightR*BSFHup);
	    histos["SR_BLFup_"       +thissampleR] ->Fill(mStop,mLSP,SR,weightR*BSFLup);
	    histos["SR_BHFdown_"     +thissampleR] ->Fill(mStop,mLSP,SR,weightR*BSFHdown);
	    histos["SR_BLFdown_"     +thissampleR] ->Fill(mStop,mLSP,SR,weightR*BSFLdown);
	    //histos["SR_LepEffup_"    +thissampleR] ->Fill(mStop,mLSP,SR,weightR*lEffup);//lepSF not yet in babies
	    //histos["SR_LepEffdown_"  +thissampleR] ->Fill(mStop,mLSP,SR,weightR*lEffdown);
	    //histos["SR_LepEffFSup_"  +thissampleR] ->Fill(mStop,mLSP,SR,weightR*lEffFSup);
	    //histos["SR_LepEffFSdown_"+thissampleR] ->Fill(mStop,mLSP,SR,weightR*lEffFSdown);
	    histos["SR_muRFup_"      +thissampleR] ->Fill(mStop,mLSP,SR,weightR*muRFup);
	    histos["SR_muRFdown_"    +thissampleR] ->Fill(mStop,mLSP,SR,weightR*muRFdown);
	  
	    histos["SR_yield_"       +thissampleL] ->Fill(mStop,mLSP,SR,weightL);
	    histos["SR_ISRup_"       +thissampleL] ->Fill(mStop,mLSP,SR,weightL*ISRup);
	    histos["SR_ISRdown_"     +thissampleL] ->Fill(mStop,mLSP,SR,weightL*ISRdown);
	    histos["SR_Xsecup_"      +thissampleL] ->Fill(mStop,mLSP,SR,weightL*XSup);
	    histos["SR_Xsecdown_"    +thissampleL] ->Fill(mStop,mLSP,SR,weightL*XSdown);
	    //histos["SR_PUup_"        +thissampleL] ->Fill(mStop,mLSP,SR,weightL*PUup);
	    //histos["SR_PUdown_"      +thissampleL] ->Fill(mStop,mLSP,SR,weightL*PUdown);
	    histos["SR_BHFup_"       +thissampleL] ->Fill(mStop,mLSP,SR,weightL*BSFHup);
	    histos["SR_BLFup_"       +thissampleL] ->Fill(mStop,mLSP,SR,weightL*BSFLup);
	    histos["SR_BHFdown_"     +thissampleL] ->Fill(mStop,mLSP,SR,weightL*BSFHdown);
	    histos["SR_BLFdown_"     +thissampleL] ->Fill(mStop,mLSP,SR,weightL*BSFLdown);
	    //histos["SR_LepEffup_"    +thissampleL] ->Fill(mStop,mLSP,SR,weightL*lEffup);//lepSF not yet in babies
	    //histos["SR_LepEffdown_"  +thissampleL] ->Fill(mStop,mLSP,SR,weightL*lEffdown);
	    //histos["SR_LepEffFSup_"  +thissampleL] ->Fill(mStop,mLSP,SR,weightL*lEffFSup);
	    //histos["SR_LepEffFSdown_"+thissampleL] ->Fill(mStop,mLSP,SR,weightL*lEffFSdown);
	    histos["SR_muRFup_"      +thissampleL] ->Fill(mStop,mLSP,SR,weightL*muRFup);
	    histos["SR_muRFdown_"    +thissampleL] ->Fill(mStop,mLSP,SR,weightL*muRFdown);
	  }
	  
	}//SR
      }//JES!=1
      if(JES==1){
	if(SR  >0){
	  histos["SR_JESup_"  +thissample]->Fill(mStop,mLSP,SR,weight);
	  if(dopolarization){
	    histos["SR_JESup_"  +thissampleR]->Fill(mStop,mLSP,SR,weight);
	    histos["SR_JESup_"  +thissampleL]->Fill(mStop,mLSP,SR,weight);
	  }
	}
      }
      if(JES==-1){
	if(SR  >0) {
	  histos["SR_JESdown_"+thissample]->Fill(mStop,mLSP,SR,weight);
	  if(dopolarization){
	    histos["SR_JESdown_"+thissampleR]->Fill(mStop,mLSP,SR,weight);
	    histos["SR_JESdown_"+thissampleL]->Fill(mStop,mLSP,SR,weight);
	  }
	}
      }


    }//event loop
  
    // Clean Up
    delete tree;
    file->Close();
    delete file;
  }//file loop
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

  string filename;
  filename = "rootfiles/CheckHistos_"+samplename+".root";
  TFile *ff = new TFile(filename.c_str(),"RECREATE");
  ff->cd();
  for(map<string,TH3D*>::iterator h=    histos2.begin(); h!=    histos2.end();++h) h->second->Write();
  ff->Close();
  cout << "Saved histos in " << ff->GetName() << endl;
  //save histograms
  if(samplename.find(T2tt)!=string::npos){
    filename = "rootfiles/Histos_"+samplename+".root";
    TFile *f = new TFile(filename.c_str(),"RECREATE");
    f->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename;
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    f->Close();
    cout << "Saved histos in " << f->GetName() << endl;
    filename = "rootfiles/Histos_"+samplename+"_lefthanded.root";
    TFile *fL = new TFile(filename.c_str(),"RECREATE");
    fL->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename + "_lefthanded";
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    fL->Close();
    cout << "Saved histos in " << fL->GetName() << endl;
    filename = "rootfiles/Histos_"+samplename+"_righthanded.root";
    TFile *fR = new TFile(filename.c_str(),"RECREATE");
    fR->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename + "_righthanded";
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    fR->Close();
    cout << "Saved histos in " << fR->GetName() << endl;
  }//T2tt
  else if(samplename.find(T2tb)!=string::npos){
    filename = "rootfiles/Histos_"+samplename+"_tLSP.root";
    TFile *ft = new TFile(filename.c_str(),"RECREATE");
    ft->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename + "_tLSP";
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    ft->Close();
    cout << "Saved histos in " << ft->GetName() << endl;
    filename = "rootfiles/Histos_"+samplename+"_mixed.root";
    TFile *fm = new TFile(filename.c_str(),"RECREATE");
    fm->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename + "_mixed";
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    fm->Close();
    cout << "Saved histos in " << fm->GetName() << endl;
    filename = "rootfiles/Histos_"+samplename+"_bCharg.root";
    TFile *fb = new TFile(filename.c_str(),"RECREATE");
    fb->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename + "_bCharg";
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    fb->Close();
    cout << "Saved histos in " << fb->GetName() << endl;
  }//T2tb
  else {
    filename = "rootfiles/Histos_"+samplename+".root";
    TFile *f = new TFile(filename.c_str(),"RECREATE");
    f->cd();
    //for(map<string,TH1F*>::iterator h=    histos.begin(); h!=    histos.end();++h) h->second->Write();//rename sample - don't use this
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename;
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    f->Close();
    cout << "Saved histos in " << f->GetName() << endl;
  }

  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}
