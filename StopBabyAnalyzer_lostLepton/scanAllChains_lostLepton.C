{

  //
  // Load Macro
  //
  gROOT->ProcessLine(".L stopBabyLooper_lostLepton.C++");

  // 
  // Define i/o directories
  //
  
  //TString input_dir = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/";
  TString input_dir = "/nfs-7/userdata/stopRun2/StopBabies_V07_02_08_met30_ge1lep_2jskim__lostLeptonStudies__20150604/";
  //TString input_dir = "/home/users/jgwood/Stop_1Lepton/lostLeptonStudies/localBabies_Incl/";
  
  TString output_dir = "./Histos/";

  //
  // Test
  //
  /*
  TChain *ch = new TChain("t");
  ch->Add("/home/users/jgwood/Stop_1Lepton/lostLeptonStudies/localBabies_Incl/ttbar.root");
  stopBabyLooper_lostLepton(ch, "./test__histos__ttbar.root"); 
  ch->~TChain();  

  TChain *ch = new TChain("t");
  ch->Add("/home/users/jgwood/Stop_1Lepton/lostLeptonStudies/localBabies_Incl/ttbar.root");
  stopBabyLooper_lostLepton(ch, "./test__histos__ttbar_1l.root"); 
  ch->~TChain();  


  TChain *ch = new TChain("t");
  ch->Add("/home/users/jgwood/Stop_1Lepton/lostLeptonStudies/localBabies_Incl/ttbar.root");
  stopBabyLooper_lostLepton(ch, "./test__histos__ttbar_2l.root"); 
  ch->~TChain();  
  */
  
 
  //
  // Scan Signal Samples
  //
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_850_100.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_850_100.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_850_100.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_850_100_1l.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_850_100.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_850_100_2l.root"); 
  ch->~TChain();
  

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_650_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_650_325.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_650_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_650_325_1l.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_650_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_650_325_2l.root"); 
  ch->~TChain();


  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_500_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_500_325.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_500_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_500_325_1l.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_500_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_500_325_2l.root"); 
  ch->~TChain();


  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_425_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_425_325.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_425_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_425_325_1l.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"stop_425_325.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__stop_425_325_2l.root"); 
  ch->~TChain();
  
    
  
  //
  // Scan backgrounds
  //
  /*
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__ttbar.root"); 
  ch->~TChain();
 
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__ttbar_0l.root"); 
  ch->~TChain();
  */
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__ttbar_1l.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttbar.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__ttbar_2l.root"); 
  ch->~TChain();
  /*
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttwjets.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__ttwjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"ttzjets.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__ttzjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"t_sch.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__t_sch.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"t_tch.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__t_tch.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"t_tW.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__t_tW.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"tbar_sch.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__tbar_sch.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"tbar_tch.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__tbar_tch.root"); 
  ch->~TChain();
  
  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"tbar_tW.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__tbar_tW.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"wjets.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__wjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"wzjets.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__wzjets.root"); 
  ch->~TChain();

  TChain *ch = new TChain("t"); 
  ch->Add(input_dir+"zz.root");
  stopBabyLooper_lostLepton(ch, output_dir+"histos__zz.root"); 
  ch->~TChain();
  */
  

}
