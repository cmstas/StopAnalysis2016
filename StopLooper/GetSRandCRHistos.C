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
#include "Tools/goodrun.h"
#include "Tools/goodrun.cc"
#include "Tools/dorky/dorky.h"
#include "Tools/dorky/dorky.cc"
#include "Tools/badEventFilter.h"
#include "Tools/badEventFilter.cc"

using namespace std;
//using namespace tas;


int ScanChain( TChain* chain, string samplename, int JES = 0, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  //keep that hardcoded??
  int maxSR = 9;
  int maxCR2l = 3;
  int maxCR0b = 3;

  //MET filters
  eventFilter metFilterTxt; 
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_MET_csc2015.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SingleElectron_csc2015.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SingleMuon_csc2015.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MET_csc2015.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleElectron_csc2015.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleMuon_csc2015.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MET_ecalscn1043093.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleElectron_ecalscn1043093.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleMuon_ecalscn1043093.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/csc2015_Dec01.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/ecalscn1043093_Dec01.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/badResolutionTrack_Jan13.txt");
  metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/muonBadTrack_Jan13.txt");
  
  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  
  //Define all histograms
  map<string, TH1F*> histos;
  vector<string> histonames; histonames.clear();

  histonames.push_back("SR_yield");//data/MC yields in SR
  histonames.push_back("SR2l_yield");//reweighting diNuPt - for 2l estimation
  histonames.push_back("SR0b_yield");//reweighting METres - for 0b estimation
  //variations in SR - all w.r.t. "normal reweighting"
  //variations for 2l - apply diNuPt & METres reweighting
  histonames.push_back("SR2l_JESup");
  histonames.push_back("SR2l_JESdown");
  histonames.push_back("SR2l_K34up");
  histonames.push_back("SR2l_K34down");
  histonames.push_back("SR2l_muRFup");
  histonames.push_back("SR2l_muRFdown");
  histonames.push_back("SR2l_LepEffup");
  histonames.push_back("SR2l_LepEffdown");
  histonames.push_back("SR2l_BHFup");
  histonames.push_back("SR2l_BHFdown");
  histonames.push_back("SR2l_BLFup");
  histonames.push_back("SR2l_BLFdown");
  histonames.push_back("SR2l_METresup");
  histonames.push_back("SR2l_METresdown");
  histonames.push_back("SR2l_diNuPtup");
  histonames.push_back("SR2l_diNuPtdown");
  //variations for 0b - apply METres reweighting
  histonames.push_back("SR0b_JESup");
  histonames.push_back("SR0b_JESdown");
  histonames.push_back("SR0b_muRFup");
  histonames.push_back("SR0b_muRFdown");
  histonames.push_back("SR0b_LepEffup");
  histonames.push_back("SR0b_LepEffdown");
  histonames.push_back("SR0b_BHFup");
  histonames.push_back("SR0b_BHFdown");
  histonames.push_back("SR0b_BLFup");
  histonames.push_back("SR0b_BLFdown");
  histonames.push_back("SR0b_METresup");
  histonames.push_back("SR0b_METresdown");
  histonames.push_back("SR0b_NuPtup");
  histonames.push_back("SR0b_NuPtdown");
  histonames.push_back("SR0b_Wwidthup");
  histonames.push_back("SR0b_Wwidthdown");
  histonames.push_back("SR0b_HFXsecup");
  histonames.push_back("SR0b_HFXsecdown");
  //CR2l
  histonames.push_back("CR2l_yield");//data/MC yields in CR
  histonames.push_back("CR2l_yield_raw");//no reweighting on METres/diNuPt
  histonames.push_back("CR2l_JESup");
  histonames.push_back("CR2l_JESdown");
  histonames.push_back("CR2l_K34up");
  histonames.push_back("CR2l_K34down");
  histonames.push_back("CR2l_muRFup");
  histonames.push_back("CR2l_muRFdown");
  histonames.push_back("CR2l_LepEffup");
  histonames.push_back("CR2l_LepEffdown");
  histonames.push_back("CR2l_BHFup");
  histonames.push_back("CR2l_BHFdown");
  histonames.push_back("CR2l_BLFup");
  histonames.push_back("CR2l_BLFdown");
  histonames.push_back("CR2l_METresup");
  histonames.push_back("CR2l_METresdown");
  histonames.push_back("CR2l_diNuPtup");
  histonames.push_back("CR2l_diNuPtdown");
  //CR0b
  histonames.push_back("CR0b_yield");//data/MC yields in CR
  histonames.push_back("CR0b_yield_raw");//no reweighting on METres
  histonames.push_back("CR0b_JESup");
  histonames.push_back("CR0b_JESdown");
  histonames.push_back("CR0b_muRFup");
  histonames.push_back("CR0b_muRFdown");
  histonames.push_back("CR0b_LepEffup");
  histonames.push_back("CR0b_LepEffdown");
  histonames.push_back("CR0b_BHFup");
  histonames.push_back("CR0b_BHFdown");
  histonames.push_back("CR0b_BLFup");
  histonames.push_back("CR0b_BLFdown");
  histonames.push_back("CR0b_METresup");
  histonames.push_back("CR0b_METresdown");
  histonames.push_back("CR0b_NuPtup");
  histonames.push_back("CR0b_NuPtdown");
  histonames.push_back("CR0b_Wwidthup");
  histonames.push_back("CR0b_Wwidthdown");
  histonames.push_back("CR0b_HFXsecup");
  histonames.push_back("CR0b_HFXsecdown");

  const unsigned int Nthissample = 8;
  string thissample[Nthissample] = {samplename,samplename + "_1ltop",samplename + "_1lnottop",samplename + "_1lW",samplename + "_1lnotW",samplename + "_eq1l",samplename + "_ge2l",samplename + "_Znunu"};
  string sampleext[Nthissample] = {"","1ltop","1lnottop","1lW","1lnotW","eq1l","ge2l","Znunu"};
  bool passsample[Nthissample]={true,false,false,false,false,false,false,false};
  //currently we have SR and CR histograms bins - in future, might have multiple
  //to keep name short, do use SR bins, and not the binning variables
  string ttbar = "TTbar";
  for(unsigned int i = 0; i<histonames.size(); ++i){
    string mysample = samplename;
    for(unsigned int j = 0; j<Nthissample+1; ++j){
      //split ttbar into 1l,2l. Safely can drop 0l
      if(samplename.find(ttbar)!=string::npos){//check if we want to expand this
	if(j==0)      mysample = thissample[0] + "2l";
	else if(j==1) mysample = thissample[0] + "1l";
      }
      else if(j==1) continue;//no need to split other samples
      if(j>=2) mysample = thissample[j-1];
      //adding "mysample" to histogram name is only temporary for bookkeeping purposes
      //in the end all histograms will be separated into separate rootfiles, and histogram names
      //will be only "histonames[i]"
      string mapname = histonames[i] + "_" + mysample;
      string sSR = "SR"; string sCR2l = "CR2l"; string sCR0b = "CR0b";
      if(mapname.find(sSR)!=string::npos && histos.count(mapname) == 0){
	histos[mapname] = new TH1F(mapname.c_str(), "", maxSR, 1,maxSR+1);
	histos[mapname]->Sumw2(); histos[mapname]->SetDirectory(rootdir);
      }
      if(mapname.find(sCR2l)!=string::npos && histos.count(mapname) == 0){
	histos[mapname] = new TH1F(mapname.c_str(), "", maxCR2l, 1,maxCR2l+1);
	histos[mapname]->Sumw2(); histos[mapname]->SetDirectory(rootdir);
      }
      if(mapname.find(sCR0b)!=string::npos && histos.count(mapname) == 0){
	histos[mapname] = new TH1F(mapname.c_str(), "", maxCR0b, 1,maxCR0b+1);
	histos[mapname]->Sumw2(); histos[mapname]->SetDirectory(rootdir);
      }
    }//j
  }//histonames


  //hardcoded stuff
  //load the text files with a) external SF and uncertainties
  //b) varying numbers (currently only lumi)
  float lumi = Util::loadSF("Luminosity", "inputs/Weights.dat");
  float tt1lerr   = Util::loadSF("Reltt1l", "inputs/Weights.dat");
  float K3err, K4err;
  float K3 = Util::loadSFwUnc("K3", "inputs/Weights.dat", K3err);
  float K4 = Util::loadSFwUnc("K4", "inputs/Weights.dat", K4err);
  float DiNuPt250err, DiNuPt350err, DiNuPt450err;
  float DiNuPt250 = Util::loadSFwUnc("DiNuPtMET250", "inputs/Weights.dat", DiNuPt250err);
  float DiNuPt350 = Util::loadSFwUnc("DiNuPtMET350", "inputs/Weights.dat", DiNuPt350err);
  float DiNuPt450 = Util::loadSFwUnc("DiNuPtMET450", "inputs/Weights.dat", DiNuPt450err);
  float METres[9], METreserr[9];
  float NuPterr[9];
  for(unsigned int i = 0; i<9; ++i){
    string helper = "METresSR"+Util::intToString(i+1);
    METres[i] = Util::loadSFwUnc(helper, "inputs/Weights.dat", METreserr[i]);
    helper = "RelNuPtSR"+Util::intToString(i+1);
    NuPterr[i] = Util::loadSF(helper, "inputs/Weights.dat");
  }
  float WHFxserr  = Util::loadSF("RelWHFxsec", "inputs/Weights.dat");
  float Wwidtherr = Util::loadSF("RelWwidth", "inputs/Weights.dat");  
  
  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  TH1D* counterhist;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() );
    counterhist = (TH1D*)file->Get("h_counter");
    counterhist->SetDirectory(0); 
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
      int Nevts = counterhist->GetBinContent(22);
      double nevts = double(Nevts);
      //define some renormalization numbers, such that overall normalization of samples does not change
      double BSFnorm(1.), BSFnormHup(1.), BSFnormLup(1.), BSFnormHdown(1.), BSFnormLdown(1.), muRFnorm(1.), muRFnormup(1.), muRFnormdown(1.);
      if( !tas::is_data() ){
	BSFnorm      = counterhist->GetBinContent(14);
	BSFnormHup   = counterhist->GetBinContent(15);
	BSFnormLup   = counterhist->GetBinContent(16);
	BSFnormHdown = counterhist->GetBinContent(17);
	BSFnormLdown = counterhist->GetBinContent(18);
	muRFnorm     = counterhist->GetBinContent(1);
	muRFnormup   = counterhist->GetBinContent(5);
	muRFnormdown = counterhist->GetBinContent(9);
      }
      //event weight calculation
      double BSFweight = tas::weight_btagsf();
      if(BSFnorm>0) BSFweight *=nevts/BSFnorm;
      if(BSFnorm<=0||BSFnormHup<=0||BSFnormLup<=0||BSFnormHdown<=0||BSFnormLdown<=0){
	BSFnorm=1; BSFnormHup=1; BSFnormLup=1; BSFnormHdown=1; BSFnormLdown=1;
      }
      if(muRFnorm<=0||muRFnormup<=0||muRFnormdown<=0){ muRFnormdown=1; muRFnormup=1; muRFnorm=1; }
      //lepSF is done below
      double rawweight = tas::scale1fb()*lumi;
      double weight = rawweight;
      if( !tas::is_data() ) weight *= BSFweight;
      //double weight = rawweight*BSFweight*tas::weight_lepSF();//not yet in babies
      if(event==0) cout << "weight " << weight << " nEvents " << nEventsTree << " filename " << currentFile->GetTitle() << endl;

      //get SR and CR bins
      if(StF::isSignalOrControlRegion()==false) continue;
      int SR = StF::SRIdentifier();
      int CR2l = StF::CR2lIdentifier();
      int CR0b = StF::CR0bIdentifier();
      if(SR<0&&CR2l<0&&CR0b<0) continue;
      //treatment on data:
      //duplicate removal, trigger application, MET filter
      if( tas::is_data() ) {//remove duplicates
	duplicate_removal::DorkyEventIdentifier id(tas::run(), tas::evt(), tas::ls());
	if (is_duplicate(id) ) continue;
	if(!StF::passSignalTriggers()) continue;//trigger requirement
	if(!StF::passMETfiltersNoTxt()) continue;//no txt-file MET filters
	if(metFilterTxt.eventFails(tas::run(), tas::ls(), tas::evt())) continue; //txt-file MET filters
      }

      //the sample name is actually only important for ttbar, else the TFile name would be enough
      thissample[0] = samplename;
      //extra treatment for ttbar
      if(samplename.find(ttbar)!=string::npos){//check if we want to expand this
	if(tas::is2lep() ) thissample[0] = "TTbar2l";
	else if(tas::is1lepFromTop() ) thissample[0] = "TTbar1l";
	else continue;//drop hadronic ttbar
      }
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
      
      //get HF
      bool isWHF = false;
      if(samplename=="WJets"){
	if(tas::is1lepFromW()){
	  for(unsigned int i = 0; i<= tas::ak4pfjets_parton_flavor().size(); ++i){//or is it ak4pfjets_hadron_flavor()
	    if(TMath::Abs(tas::ak4pfjets_parton_flavor()[i])==5) {
	      isWHF = true;
	      break;
	    }
	  }
	}
      }
      if(!isWHF) WHFxserr = 0;//no error due to HF xsec

      //get all uncertainties
      float K(1.), Kerr(0.);
      if(     tas::ngoodjets()==3) { K = K3; Kerr = K3err; }
      else if(tas::ngoodjets()>=4) { K = K4; Kerr = K4err; }
      float dinupt(1.), dinupterr(1.);
      if(     tas::pfmet()>450){ dinupt = DiNuPt450; dinupterr = DiNuPt450err; }
      else if(tas::pfmet()>350){ dinupt = DiNuPt350; dinupterr = DiNuPt450err; }
      else if(tas::pfmet()>250){ dinupt = DiNuPt250; dinupterr = DiNuPt450err; }
      float metres(1.), metreserr(0.);
      if(tas::ngoodjets()>=4){
	if(tas::MT2W()>200){
	  if(     tas::pfmet()>450) { metres = METres[8]; metreserr = METreserr[8]; }
	  else if(tas::pfmet()>350) { metres = METres[7]; metreserr = METreserr[7]; }
	  else if(tas::pfmet()>250) { metres = METres[6]; metreserr = METreserr[6]; }
	} else {
	  if(     tas::pfmet()>325) { metres = METres[5]; metreserr = METreserr[5]; }
	  else if(tas::pfmet()>250) { metres = METres[4]; metreserr = METreserr[4]; }
	}
      } else if(tas::ngoodjets()==3&&tas::MT2W()>200){
	if(       tas::pfmet()>359) { metres = METres[3]; metreserr = METreserr[3]; }
	else if(  tas::pfmet()>250) { metres = METres[2]; metreserr = METreserr[2]; }
      } else if(tas::ngoodjets()==2&&tas::topnessMod()>6.4){
	if(       tas::pfmet()>359) { metres = METres[1]; metreserr = METreserr[1]; }
	else if(  tas::pfmet()>250) { metres = METres[0]; metreserr = METreserr[0]; }
      }
      float nupterr(0.);
      if(tas::ngoodjets()>=4&&tas::MT2W()>200){
	if(     tas::pfmet()>450) { nupterr = NuPterr[8]; }
	else if(tas::pfmet()>350) { nupterr = NuPterr[7]; }
	else if(tas::pfmet()>250) { nupterr = NuPterr[6]; }
      } else if(tas::ngoodjets()==3&&tas::MT2W()>200){
	if(     tas::pfmet()>359) { nupterr = NuPterr[3]; }
	else if(tas::pfmet()>250) { nupterr = NuPterr[2]; }
      } else if(tas::ngoodjets()==2&&tas::topnessMod()>6.4){
	if(     tas::pfmet()>359) { nupterr = NuPterr[1]; }
	else if(tas::pfmet()>250) { nupterr = NuPterr[0]; }
      }
      float weight2l = weight * K * dinupt * metres;
      float weight0b = weight * metres;

      if( tas::is_data() ){
	weight   = 1.;
	weight2l = 1.;
	weight0b = 1.;
      }

      //do we need lepSF norm?? - how to test (given that most samples have a genlep selection)
      float BSFHup(1.), BSFLup(1.), BSFHdown(1.), BSFLdown(1.), muRFup(1.), muRFdown(1.);
      if( !tas::is_data() ){
	BSFHup   = tas::weight_btagsf_heavy_UP()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
	BSFLup   = tas::weight_btagsf_light_UP()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
	BSFHdown = tas::weight_btagsf_heavy_DN()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
	BSFLdown = tas::weight_btagsf_light_DN()/tas::weight_btagsf()*BSFnorm/BSFnormHup;
	if(samplename!="tW"){//apparently tW does not have Q2 variations
	  muRFup   = tas::genweights().at(4)/tas::genweights().at(0)*muRFnorm/muRFnormup;
	  muRFdown = tas::genweights().at(8)/tas::genweights().at(0)*muRFnorm/muRFnormdown;
	} else {
	  muRFup   = 1.;
	  muRFdown = 1.;
	}
      }
      //now I got everything - fill histograms
      for(unsigned int j = 0; j<Nthissample; ++j){
	if(!passsample[j]) continue;//not that this is true for j==0 always
	if(abs(JES)!=1){
	  if(SR>0){
	    histos["SR_yield_"  +thissample[j] ]->Fill(SR,weight);
	    histos["SR2l_yield_"+thissample[j] ]->Fill(SR,weight2l);
	    histos["SR0b_yield_"+thissample[j] ]->Fill(SR,weight0b);

	    histos["SR2l_K34up_"     +thissample[j] ]->Fill(SR,weight2l*(K+Kerr)/K);
	    histos["SR2l_K34down_"   +thissample[j] ]->Fill(SR,weight2l*(K-Kerr)/K);
	    histos["SR2l_muRFup_"    +thissample[j] ]->Fill(SR,weight2l*muRFup);
	    histos["SR2l_muRFdown_"  +thissample[j] ]->Fill(SR,weight2l*muRFdown);
	    //if(tas::weight_lepSF()>0){//current babies miss this branch
	    //histos["SR2l_LepEffup_"  +thissample[j] ]->Fill(SR,weight2l*tas::weight_lepSF_up()/tas::weight_lepSF());
	    //histos["SR2l_LepEffdown_"+thissample[j] ]->Fill(SR,weight2l*tas::weight_lepSF_down()/tas::weight_lepSF()));
	    //}
	    histos["SR2l_BHFup_"     +thissample[j] ]->Fill(SR,weight2l*BSFHup);
	    histos["SR2l_BHFdown_"   +thissample[j] ]->Fill(SR,weight2l*BSFHdown);
	    histos["SR2l_BLFup_"     +thissample[j] ]->Fill(SR,weight2l*BSFLup);
	    histos["SR2l_BLFdown_"   +thissample[j] ]->Fill(SR,weight2l*BSFLdown);
	    histos["SR2l_METresup_"  +thissample[j] ]->Fill(SR,weight2l*(metres+metreserr)/metres);
	    histos["SR2l_METresdown_"+thissample[j] ]->Fill(SR,weight2l*(metres-metreserr)/metres);
	    histos["SR2l_diNuPtup_"  +thissample[j] ]->Fill(SR,weight2l*(dinupt+dinupterr)/dinupt);
	    histos["SR2l_diNuPtdown_"+thissample[j] ]->Fill(SR,weight2l*(dinupt-dinupterr)/dinupt);

	    histos["SR0b_Wwidthup_"  +thissample[j] ]->Fill(SR,weight0b*(1.+Wwidtherr));
	    histos["SR0b_Wwidthdown_"+thissample[j] ]->Fill(SR,weight0b*(1.-Wwidtherr));
	    histos["SR0b_HFXsecup_"  +thissample[j] ]->Fill(SR,weight0b*(1.+WHFxserr));//WHFxserr=0 if no HF
	    histos["SR0b_HFXsecdown_"+thissample[j] ]->Fill(SR,weight0b*(1.-WHFxserr));//WHFxserr=0 if no HF
	    histos["SR0b_muRFup_"    +thissample[j] ]->Fill(SR,weight0b*muRFup);
	    histos["SR0b_muRFdown_"  +thissample[j] ]->Fill(SR,weight0b*muRFdown);
	    //if(tas::weight_lepSF()>0){//current babies miss this branch
	    //histos["SR0b_LepEffup_"  +thissample[j] ]->Fill(SR,weight0b*tas::weight_lepSF_up()/tas::weight_lepSF());
	    //histos["SR0b_LepEffdown_"+thissample[j] ]->Fill(SR,weight0b*tas::weight_lepSF_down()/tas::weight_lepSF()));
	    //}
	    histos["SR0b_BHFup_"     +thissample[j] ]->Fill(SR,weight0b*BSFHup);
	    histos["SR0b_BHFdown_"   +thissample[j] ]->Fill(SR,weight0b*BSFHdown);
	    histos["SR0b_BLFup_"     +thissample[j] ]->Fill(SR,weight0b*BSFLup);
	    histos["SR0b_BLFdown_"   +thissample[j] ]->Fill(SR,weight0b*BSFLdown);
	    histos["SR0b_METresup_"  +thissample[j] ]->Fill(SR,weight0b*(metres+metreserr)/metres);
	    histos["SR0b_METresdown_"+thissample[j] ]->Fill(SR,weight0b*(metres-metreserr)/metres);
	    histos["SR0b_NuPtup_"    +thissample[j] ]->Fill(SR,weight0b*(1.+nupterr));
	    histos["SR0b_NuPtdown_"  +thissample[j] ]->Fill(SR,weight0b*(1.-nupterr));
	  }
	  if(CR2l>0){
	    histos["CR2l_yield_raw_"+thissample[j] ]->Fill(CR2l,weight);
	    histos["CR2l_yield_"    +thissample[j] ]->Fill(CR2l,weight2l);

	    histos["CR2l_K34up_"     +thissample[j] ]->Fill(CR2l,weight2l*(K+Kerr)/K);
	    histos["CR2l_K34down_"   +thissample[j] ]->Fill(CR2l,weight2l*(K-Kerr)/K);
	    histos["CR2l_muRFup_"    +thissample[j] ]->Fill(CR2l,weight2l*muRFup);
	    histos["CR2l_muRFdown_"  +thissample[j] ]->Fill(CR2l,weight2l*muRFdown);
	    //if(tas::weight_lepSF()>0){//current babies miss this branch
	    //histos["CR2l_LepEffup_"  +thissample[j] ]->Fill(CR0b,weight2l*tas::weight_lepSF_up()/tas::weight_lepSF());
	    //histos["CR2l_LepEffdown_"+thissample[j] ]->Fill(CR0b,weight2l*tas::weight_lepSF_down()/tas::weight_lepSF()));
	    //}
	    histos["CR2l_BHFup_"     +thissample[j] ]->Fill(CR2l,weight2l*BSFHup);
	    histos["CR2l_BHFdown_"   +thissample[j] ]->Fill(CR2l,weight2l*BSFHdown);
	    histos["CR2l_BLFup_"     +thissample[j] ]->Fill(CR2l,weight2l*BSFLup);
	    histos["CR2l_BLFdown_"   +thissample[j] ]->Fill(CR2l,weight2l*BSFLdown);
	    histos["CR2l_METresup_"  +thissample[j] ]->Fill(CR2l,weight2l*(metres+metreserr)/metres);
	    histos["CR2l_METresdown_"+thissample[j] ]->Fill(CR2l,weight2l*(metres-metreserr)/metres);
	    histos["CR2l_diNuPtup_"  +thissample[j] ]->Fill(CR2l,weight2l*(dinupt+dinupterr)/dinupt);
	    histos["CR2l_diNuPtdown_"+thissample[j] ]->Fill(CR2l,weight2l*(dinupt-dinupterr)/dinupt);
	  }
	  if(CR0b>0){
	    histos["CR0b_yield_raw_"+thissample[j] ]->Fill(CR0b,weight);
	    histos["CR0b_yield_"    +thissample[j] ]->Fill(CR0b,weight0b);

	    histos["CR0b_Wwidthup_"  +thissample[j] ]->Fill(CR0b,weight0b*(1.+Wwidtherr));
	    histos["CR0b_Wwidthdown_"+thissample[j] ]->Fill(CR0b,weight0b*(1.-Wwidtherr));
	    histos["CR0b_HFXsecup_"  +thissample[j] ]->Fill(CR0b,weight0b*(1.+WHFxserr));//WHFxserr=0 if no HF
	    histos["CR0b_HFXsecdown_"+thissample[j] ]->Fill(CR0b,weight0b*(1.-WHFxserr));//WHFxserr=0 if no HF
	    histos["CR0b_muRFup_"    +thissample[j] ]->Fill(CR0b,weight0b*muRFup);
	    histos["CR0b_muRFdown_"  +thissample[j] ]->Fill(CR0b,weight0b*muRFdown);
	    //if(tas::weight_lepSF()>0){//current babies miss this branch
	    //histos["CR0b_LepEffup_"  +thissample[j] ]->Fill(CR0b,weight0b*tas::weight_lepSF_up()/tas::weight_lepSF());
	    //histos["CR0b_LepEffdown_"+thissample[j] ]->Fill(CR0b,weight0b*tas::weight_lepSF_down()/tas::weight_lepSF()));
	    //}
	    histos["CR0b_BHFup_"     +thissample[j] ]->Fill(CR0b,weight0b*BSFHup);
	    histos["CR0b_BHFdown_"   +thissample[j] ]->Fill(CR0b,weight0b*BSFHdown);
	    histos["CR0b_BLFup_"     +thissample[j] ]->Fill(CR0b,weight0b*BSFLup);
	    histos["CR0b_BLFdown_"   +thissample[j] ]->Fill(CR0b,weight0b*BSFLdown);
	    histos["CR0b_METresup_"  +thissample[j] ]->Fill(CR0b,weight0b*(metres+metreserr)/metres);
	    histos["CR0b_METresdown_"+thissample[j] ]->Fill(CR0b,weight0b*(metres-metreserr)/metres);
	    histos["CR0b_NuPtup_"    +thissample[j] ]->Fill(CR0b,weight0b*(1.+nupterr));
	    histos["CR0b_NuPtdown_"  +thissample[j] ]->Fill(CR0b,weight0b*(1.-nupterr));
	  }
	}//jes!=1
	if(JES==1){
	  if(SR  >0) histos["SR2l_JESup_"  +thissample[j] ]->Fill(SR  ,weight2l);
	  if(SR  >0) histos["SR0b_JESup_"  +thissample[j] ]->Fill(SR  ,weight0b);
	  if(CR2l>0) histos["CR2l_JESup_"  +thissample[j] ]->Fill(CR2l,weight2l);
	  if(CR0b>0) histos["CR0b_JESup_"  +thissample[j] ]->Fill(CR0b,weight0b);
	}
	if(JES==-1){
	  if(SR  >0) histos["SR2l_JESdown_"    +thissample[j] ]->Fill(SR  ,weight2l);
	  if(SR  >0) histos["SR0b_JESdown_"    +thissample[j] ]->Fill(SR  ,weight0b);
	  if(CR2l>0) histos["CR2l_JESdown_"    +thissample[j] ]->Fill(CR2l,weight2l);
	  if(CR0b>0) histos["CR0b_JESdown_"    +thissample[j] ]->Fill(CR0b,weight0b);
	}
      }//Nthissample

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
      if(h->second->GetBinContent(jx)<0){
	h->second->SetBinContent(jx,0);
	h->second->SetBinError(jx,0);
      }
    }
  }

  //save histograms
  if(samplename.find(ttbar)!=string::npos){
    string filename = "rootfiles/SRandCRHistos_"+samplename+"2l.root";
    TFile *f2l = new TFile(filename.c_str(),"RECREATE");
    f2l->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename + "2l";
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    f2l->Close();
    //for(map<string,TH1F*>::iterator h=    histos.begin(); h!=    histos.end();++h) h->second->Write();//rename sample - don't use this
    cout << "Saved histos in " << f2l->GetName() << endl;
    filename = "rootfiles/SRandCRHistos_"+samplename+"1l.root";
    TFile *f1l = new TFile(filename.c_str(),"RECREATE");
    f1l->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename + "1l";
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    f1l->Close();
    //for(map<string,TH1F*>::iterator h=    histos.begin(); h!=    histos.end();++h) h->second->Write();//rename sample - don't use this
    cout << "Saved histos in " << f1l->GetName() << endl;
  } else {
    string filename = "rootfiles/SRandCRHistos_"+samplename+".root";
    TFile *f = new TFile(filename.c_str(),"RECREATE");
    f->cd();
    for(unsigned int i = 0; i<histonames.size(); ++i){
      string mapname = histonames[i] + "_" + samplename;
      histos[mapname]->Write(histonames[i].c_str(),TObject::kOverwrite);
    }
    //for(map<string,TH1F*>::iterator h=    histos.begin(); h!=    histos.end();++h) h->second->Write();//rename sample - don't use this
    f->Close();
    cout << "Saved histos in " << f->GetName() << endl;
  }
  //finally store lepsplit histos
  string filename = "rootfiles/SRandCRHistos_"+samplename+"_lepbinned.root";
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
