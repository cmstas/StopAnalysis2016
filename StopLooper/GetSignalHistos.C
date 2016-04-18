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

  //in principle we don't need the lepton-binned samples - however if we want to know purities, etc it might be helpful - store in separate file
  const unsigned int Nthissample = 8;
  string thissample[Nthissample] = {samplename,samplename + "_1ltop",samplename + "_1lnottop",samplename + "_1lW",samplename + "_1lnotW",samplename + "_eq1l",samplename + "_ge2l",samplename + "_Znunu"};
  string sampleext[Nthissample] = {"","1ltop","1lnottop","1lW","1lnotW","eq1l","ge2l","Znunu"};
  bool passsample[Nthissample]={true,false,false,false,false,false,false,false};
  string T2tt = "T2tt";
  string T2tb = "T2tb";
  for(unsigned int i = 0; i<histonames.size(); ++i){
    string mysample = samplename;
    for(unsigned int j = 0; j<Nthissample+2; ++j){
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
      else if(j==1||j==2) continue;
      if(j>=3) mysample = thissample[j-2];
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

      thissample[0] = samplename;
      if(samplename.find(T2tb)!=string::npos){
	int T2tb_what = StF::whichT2tbdecay();
	if(     T2tb_what==1) thissample[0] = samplename + "_tLSP";
	else if(T2tb_what==2) thissample[0] = samplename + "_mixed";
	else if(T2tb_what==3) thissample[0] = samplename + "_bCharg";
	else continue;
      }
      bool dopolarization = false;
      if(samplename.find(T2tt)!=string::npos) dopolarization = true;
      float weight_pol_L(1.), weight_pol_R(1.);
      if(dopolarization&&((mStop-mLSP)>172)) StF::PolarizationWeights(weight_pol_L,weight_pol_R);
      string thissampleL = samplename + "_lefthanded";
      string thissampleR = samplename + "_righthanded";
      float weightL = weight * weight_pol_L;
      float weightR = weight * weight_pol_R;

      //lepton splitting
      if(tas::is1lep() && tas::is1lepFromTop() ) { passsample[1] =  true; passsample[2] = false; }//is1lep needed in case of Znunu events
      else if(tas::is1lep() )                    { passsample[1] = false; passsample[2] =  true; }
      else                                       { passsample[1] = false; passsample[2] = false; }
      if(tas::is1lep() && tas::is1lepFromW()   ) { passsample[3] =  true; passsample[4] = false; }
      else if(tas::is1lep() )                    { passsample[3] = false; passsample[4] =  true; }
      else                                       { passsample[3] = false; passsample[4] = false; }
      if(tas::is1lep() )    passsample[5] = true;
      else                  passsample[5] = false;
      if(tas::is2lep() )    passsample[6] = true;
      else                  passsample[6] = false;
      if(tas::isZtoNuNu() ) passsample[7] = true;
      else                  passsample[7] = false;
      
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

      for(unsigned int j = 0; j<Nthissample+2; ++j){
	if(j<Nthissample &&   !passsample[j]) continue;//not that this is true for j==0 always
	if(j>=Nthissample && !dopolarization) continue;
	string thesample;
	if(j<Nthissample)           thesample = thissample[j];
	else if(j==Nthissample)     thesample = thissampleL;
	else if(j==(Nthissample+1)) thesample = thissampleR;
	else { cout << "How can this happen" << endl; continue; }
	if(abs(JES)!=1){
	  if(CR0b>0){
	    if(CR0b==1){
	      histos["CR0b_sigcontamination_"+thesample]->Fill(mStop,mLSP,1,weight*CR0b_1_1);
	      histos["CR0b_sigcontamination_"+thesample]->Fill(mStop,mLSP,2,weight*CR0b_1_2);
	    } else if(CR0b==2){
	      histos["CR0b_sigcontamination_"+thesample]->Fill(mStop,mLSP,3,weight*CR0b_2_3);
	      histos["CR0b_sigcontamination_"+thesample]->Fill(mStop,mLSP,4,weight*CR0b_2_4);
	    } else if(CR0b==3){
	      histos["CR0b_sigcontamination_"+thesample]->Fill(mStop,mLSP,7,weight*CR0b_3_7);
	      histos["CR0b_sigcontamination_"+thesample]->Fill(mStop,mLSP,8,weight*CR0b_3_8);
	      histos["CR0b_sigcontamination_"+thesample]->Fill(mStop,mLSP,9,weight*CR0b_3_9);
	    }
	  } else if(CR2l>0){
	    if(CR2l==1){
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,1,weight*CR2l_1_1);
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,2,weight*CR2l_1_2);
	    } else if(CR2l==2){
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,5,weight*CR2l_2_5);
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,6,weight*CR2l_2_6);
	    } else if(CR2l==3){
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,7,weight*CR2l_3_7);
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,8,weight*CR2l_3_8);
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,9,weight*CR2l_3_9);
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,3,weight*CR2l_3_3);
	      histos["CR2l_sigcontamination_"+thesample]->Fill(mStop,mLSP,4,weight*CR2l_3_4);
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
	    histos["SR_yield_"       +thesample] ->Fill(mStop,mLSP,SR,weight);
	    histos["SR_ISRup_"       +thesample] ->Fill(mStop,mLSP,SR,weight*ISRup);
	    histos["SR_ISRdown_"     +thesample] ->Fill(mStop,mLSP,SR,weight*ISRdown);
	    histos["SR_Xsecup_"      +thesample] ->Fill(mStop,mLSP,SR,weight*XSup);
	    histos["SR_Xsecdown_"    +thesample] ->Fill(mStop,mLSP,SR,weight*XSdown);
	    //histos["SR_PUup_"        +thesample] ->Fill(mStop,mLSP,SR,weight*PUup);
	    //histos["SR_PUdown_"      +thesample] ->Fill(mStop,mLSP,SR,weight*PUdown);
	    histos["SR_BHFup_"       +thesample] ->Fill(mStop,mLSP,SR,weight*BSFHup);
	    histos["SR_BLFup_"       +thesample] ->Fill(mStop,mLSP,SR,weight*BSFLup);
	    histos["SR_BHFdown_"     +thesample] ->Fill(mStop,mLSP,SR,weight*BSFHdown);
	    histos["SR_BLFdown_"     +thesample] ->Fill(mStop,mLSP,SR,weight*BSFLdown);
	    //histos["SR_LepEffup_"    +thesample] ->Fill(mStop,mLSP,SR,weight*lEffup);//lepSF not yet in babies
	    //histos["SR_LepEffdown_"  +thesample] ->Fill(mStop,mLSP,SR,weight*lEffdown);
	    //histos["SR_LepEffFSup_"  +thesample] ->Fill(mStop,mLSP,SR,weight*lEffFSup);
	    //histos["SR_LepEffFSdown_"+thesample] ->Fill(mStop,mLSP,SR,weight*lEffFSdown);
	    histos["SR_muRFup_"      +thesample] ->Fill(mStop,mLSP,SR,weight*muRFup);
	    histos["SR_muRFdown_"    +thesample] ->Fill(mStop,mLSP,SR,weight*muRFdown);
	  }//SR
	}//JES!=1
	if(JES==1){
	  if(SR  >0){
	    histos["SR_JESup_"  +thesample]->Fill(mStop,mLSP,SR,weight);
	  }
	}
	if(JES==-1){
	  if(SR  >0) {
	    histos["SR_JESdown_"+thesample]->Fill(mStop,mLSP,SR,weight);
	  }
	}
      }//thesample

    }//event loop
  
    // Clean Up
    delete tree;
    file->Close();
    delete file;
  }//file loop
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

  //zero out negative entries
  for(map<string,TH1F*>::iterator h=    histos.begin(); h!=    histos.end();++h){
    for(int jx = 1; jx<=h->second->GetNbinsX(); ++jx){
      for(int jy = 1; jy<=h->second->GetNbinsY(); ++jy){
	for(int jz = 1; jz<=h->second->GetNbinsY(); ++jz){
	  if(h->second->GetBinContent(jx,jy,jz)<0){
	    h->second->SetBinContent(jx,jy,jz,0);
	    h->second->SetBinError(jx,jy,jz,0);
	  }
	}
      }
    }
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
  //finally store lepsplit histos
  filename = "rootfiles/Histos_"+samplename+"_lepbinned.root";
  TFile *fl = new TFile(filename.c_str(),"RECREATE");
  fl->cd();
  for(unsigned int i = 0; i<histonames.size(); ++i){
    for(unsigned int j = 1; j<Nthissample; ++j){
      string mapname = histonames[i] + "_" + thissample[j];
      string savename = histonames[i] + "_" + sampleext[j];//using this we can simply hadd samples
      histos[mapname]->Write(savename.c_str(),TObject::kOverwrite);
    }
  }
  //for(map<string,TH1F*>::iterator h=    histos.begin(); h!=    histos.end();++h) h->second->Write();//rename sample - don't use this
  fl->Close();
  cout << "Saved histos in " << fl->GetName() << endl;

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
