{

  //
  // Load Macro
  //
  gROOT->ProcessLine(".L stopBabyLooper.C++");

  // 
  // Define i/o directories
  //
  TString input_dir = "/nfs-7/userdata/stopRun2/StopBabies_V07_02_08_met30_ge1lep_2jskim__fullLepSelection__20150527/";
  //TString input_dir = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/";
  
  TString output_dir = "./Histos/";
  //TString output_dir = "./Histos__nJets_gte_2/";

  //TChain *ch = new TChain("t"); 
  //ch->Add("/nfs-7/userdata/mliu/ttbar_skim15.root");
  //stopBabyLooper(ch, "./forMia__histos__ttbar_skim15.root"); 
  //ch->~TChain();

  //TChain *ch = new TChain("t"); 
  //ch->Add("/nfs-7/userdata/mliu/ttbar_skim30.root");
  //stopBabyLooper(ch, "./forMia__histos__ttbar_skim30.root"); 
  //ch->~TChain();

  
  //
  // Scan Signal Samples
  //
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_850_100.root");
  stopBabyLooper(ch, output_dir+"histos__stop_850_100.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_650_325.root");
  stopBabyLooper(ch, output_dir+"histos__stop_650_325.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_500_325.root");
  stopBabyLooper(ch, output_dir+"histos__stop_500_325.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_425_325.root");
  stopBabyLooper(ch, output_dir+"histos__stop_425_325.root"); 
  ch->~TChain();

  
  //
  // Scan backgrounds
  //
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper(ch, output_dir+"histos__ttbar.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper(ch, output_dir+"histos__ttbar_0l.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper(ch, output_dir+"histos__ttbar_1l.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper(ch, output_dir+"histos__ttbar_2l.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttwjets.root");
  stopBabyLooper(ch, output_dir+"histos__ttwjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttzjets.root");
  stopBabyLooper(ch, output_dir+"histos__ttzjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"t_sch.root");
  stopBabyLooper(ch, output_dir+"histos__t_sch.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"t_tch.root");
  stopBabyLooper(ch, output_dir+"histos__t_tch.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"t_tW.root");
  stopBabyLooper(ch, output_dir+"histos__t_tW.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"tbar_sch.root");
  stopBabyLooper(ch, output_dir+"histos__tbar_sch.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"tbar_tch.root");
  stopBabyLooper(ch, output_dir+"histos__tbar_tch.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"tbar_tW.root");
  stopBabyLooper(ch, output_dir+"histos__tbar_tW.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"wjets.root");
  stopBabyLooper(ch, output_dir+"histos__wjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"wzjets.root");
  stopBabyLooper(ch, output_dir+"histos__wzjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"zz.root");
  stopBabyLooper(ch, output_dir+"histos__zz.root"); 
  ch->~TChain();
  
  

}
