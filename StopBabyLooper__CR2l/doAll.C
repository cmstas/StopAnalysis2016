{
  gSystem->Load("../StopCORE/stopCORE.so");
  gSystem->Load("../../CORE/CMS3_CORE.so");
  gSystem->Load("../StopBabyMaker/stop_variables/StopVariables.so");
  gROOT->ProcessLine(".L ScanChain.C+");

  TChain *ch = new TChain("t"); 
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/t_tW_5f_powheg_pythia8_25ns.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/t_tbarW_5f_powheg_pythia8_25ns.root");  
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WWTo2l2Nu_powheg*.root");     
  ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/ttbar_diLept_madgraph_pythia8_ext1*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/ttbar_singleLeptFromT_madgraph_pythia8_25ns*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/ttbar_singleLeptFromTbar_madgraph_pythia8_25ns*.root");
  //ch->Add("/nfs-7/userdata/isuarez/stop_babies_met1501btag_CMS3_V080005__BabyMaker_V0800X_v2__20160617/ttbar_diLept_madgraph_pythia8_ext1*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/TTWJetsToLNu*.root");  
  
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/TTZToLLNuNu*.root");  
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WZTo1L3Nu*.root");
  
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT100To200_madgraph_pythia8_ext1_25ns.root"); 
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT200To400_madgraph_pythia8_ext1*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT600To800_madgraph_pythia8_25ns.root");      
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT800To1200_madgraph_pythia8_ext1*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns.root");    
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root");       

  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/W1JetsToLNu_madgraph_pythia8_25ns.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/W2JetsToLNu_madgraph_pythia8_25ns.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/W3JetsToLNu_madgraph_pythia8_25ns.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/W4JetsToLNu_madgraph_pythia8_25ns.root");  
  // ch->Add("/nfs-7/userdata/stopRun2/Lumi_3p99ifb_JECs/W1JetsToLNu_madgraph_pythia8_25ns_nupT200*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/Lumi_3p99ifb_JECs/W2JetsToLNu_madgraph_pythia8_25ns_nupT200*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/Lumi_3p99ifb_JECs/W3JetsToLNu_madgraph_pythia8_25ns_nupT200*.root");
  // ch->Add("/nfs-7/userdata/stopRun2/Lumi_3p99ifb_JECs/W4JetsToLNu_madgraph_pythia8_25ns_nupT200*.root");
  
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/data_met_Run2016B_MINIAOD_PromptReco-v2.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/data_single_electron_Run2016B_MINIAOD_PromptReco-v2.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/data_single_muon_Run2016B_MINIAOD_PromptReco-v2.root");    

  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V08-00-05-XX/StopBabyMaker_V8p0X_v1/data_met_Run2016B_MINIAOD_PromptReco-v2.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V08-00-05-XX/StopBabyMaker_V8p0X_v1/data_single_electron_Run2016B_MINIAOD_PromptReco-v2.root");
  // ch->Add("/nfs-7/userdata/stopRun2/StopBabies__CMS3_V08-00-05-XX/StopBabyMaker_V8p0X_v1/data_single_muon_Run2016B_MINIAOD_PromptReco-v2.root");
  
  ScanChain(ch,true); 
}
