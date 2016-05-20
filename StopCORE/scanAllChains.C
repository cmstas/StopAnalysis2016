{

  gSystem->Load("../../CORE/CMS3_CORE.so");
  gROOT->ProcessLine(".L stopBabyLooper_ttbar_diLepton_CR.C++");

  
  std::vector<TString> inDirs;
  std::vector<TString> outDirs;

  // Nominal
  //TString input_dir_nom  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/Skims_CR_emu__20151211/";  
  //TString input_dir_nom  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";  
  TString input_dir_nom  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/Skims_CR_emu__20160202/";  
  TString output_dir_nom = "Histos/Nominal/";

  inDirs.push_back(input_dir_nom);
  outDirs.push_back(output_dir_nom);

  // JESup
  //TString input_dir_jesUp  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECup__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/Skims_CR_emu__JECup__20151211/";  
  TString input_dir_jesUp  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECup__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";  
  TString output_dir_jesUp = "Histos/JESup/";
  
  //inDirs.push_back(input_dir_jesUp);
  //outDirs.push_back(output_dir_jesUp);

  // JESdown
  //TString input_dir_jesDn  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECdown__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/Skims_CR_emu__JECdown__20151211/";  
  TString input_dir_jesDn  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECdown__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";  
  TString output_dir_jesDn = "Histos/JESdown/";

  //inDirs.push_back(input_dir_jesDn);
  //outDirs.push_back(output_dir_jesDn);

  // Declare TChain ptr
  TChain *ch;

  //
  // Data
  //
  
  ch = new TChain("t"); 
  ch->Add(input_dir_nom+"data_muon_eg*");
  ch->Add(input_dir_nom+"data_double_eg*");
  ch->Add(input_dir_nom+"data_double_mu*");
  
  stopBabyLooper_ttbar_diLepton_CR(ch, output_dir_nom+"histos__data_diLep_2015CD_25ns.root"); 
  ch->~TChain();
  
  
  ch = new TChain("t"); 
  ch->Add(input_dir_nom+"data_muon_eg_2015D_promptRecoV4_25ns*.root");
  ch->Add(input_dir_nom+"data_muon_eg_2015D_05Oct2015_v2_25ns*.root");
  ch->Add(input_dir_nom+"data_muon_eg_2015D_05Oct2015_v1_25ns*.root");
  //ch->Add(input_dir_nom+"data_muon_eg_2015D_promptRecoV3_25ns*.root");
  ch->Add(input_dir_nom+"data_muon_eg_2015C_25ns*.root");
  stopBabyLooper_ttbar_diLepton_CR(ch, output_dir_nom+"histos__data_muon_eg_2015CD_25ns.root"); 
  ch->~TChain();
  
  
  //
  // Loop over sets of babies to analze
  //
  bool doMC = true;
  if(doMC){
    for(int iBaby=0; iBaby<(int)inDirs.size(); iBaby++){

      TString input_dir  = inDirs[iBaby];
      TString output_dir = outDirs[iBaby];
    
      //
      // Background samples
      //
      /*
      ch = new TChain("t"); 
      ch->Add(input_dir+"ttbar_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ttbar_powheg_pythia8_25ns.root"); 
      ch->~TChain();
      */
      
      ch = new TChain("t"); 
      //ch->Add(input_dir+"ttbar_powheg_pythia8_ext3_25ns_1.root");
      //stopBabyLooper_ttbar_diLepton_CR(ch, "histos__ttbar_powheg_pythia8_ext3_25ns__test.root"); 
      ch->Add(input_dir+"ttbar_powheg_pythia8_ext3_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ttbar_powheg_pythia8_ext3_25ns.root"); 
      ch->~TChain();
      
      /*
      ch = new TChain("t"); 
      ch->Add(input_dir+"ttbar_singleLeptFromT_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ttbar_singleLeptFromT_madgraph_pythia8_25ns.root"); 
      ch->~TChain();
      
      ch = new TChain("t"); 
      ch->Add(input_dir+"ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns.root"); 
      ch->~TChain();
      
      ch = new TChain("t"); 
      ch->Add(input_dir+"ttbar_singleLeptFromTbar_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ttbar_singleLeptFromTbar_madgraph_pythia8_25ns.root"); 
      ch->~TChain();
      
      ch = new TChain("t"); 
      ch->Add(input_dir+"ttbar_diLept_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ttbar_diLept_madgraph_pythia8_25ns.root"); 
      ch->~TChain();
      
      ch = new TChain("t"); 
      ch->Add(input_dir+"ttbar_diLept_madgraph_pythia8_ext1_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ttbar_diLept_madgraph_pythia8_ext1_25ns.root"); 
      ch->~TChain();
      */
      
      
      //
      // DYJets
      //
      ch = new TChain("t"); 
      ch->Add(input_dir+"DYJetsToLL_m50_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__DYJetsToLL_m50_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"DYJetsToLL_m10To50_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__DYJetsToLL_m10to50_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();


      //
      // WJets
      //
      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();


      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT100To200_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT200To400_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT600To800_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT800To1200_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root"); 
      ch->~TChain();

  
  


      //
      // Single t
      //
      ch = new TChain("t"); 
      ch->Add(input_dir+"t_sch_4f_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__T_sch_4f_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"tbar_tch_4f_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__Tbar_tch_4f_powheg_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"t_tch_4f_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__T_tch_4f_powheg_pythia8_25ns.root"); 
      ch->~TChain();
      
      ch = new TChain("t"); 
      ch->Add(input_dir+"t_tbarW_5f_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__T_tbarW_5f_powheg_pythia8_25ns.root"); 
      ch->~TChain();
  
      ch = new TChain("t"); 
      ch->Add(input_dir+"t_tW_5f_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__T_tW_5f_powheg_pythia8_25ns.root"); 
      ch->~TChain();
      
  
      //
      // diBoson
      //
      ch = new TChain("t"); 
      ch->Add(input_dir+"WWTo2l2Nu_powheg_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WW_2l2nu_powheg_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WWToLNuQQ_powheg_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WW_lnuqq_powheg_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WZ_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WZ_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WZTo3LNu_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WZTo3LNu_powheg_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WZTo2L2Q_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WZTo2L2Q_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WZTo1LNu2Q_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WZTo1Lnu2Q_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"WZTo1L3Nu_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__WZTo1L3Nu_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"ZZ_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ZZ_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"ZZTo4L_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ZZTo4L_powheg_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"ZZTo2L2Q_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ZZTo2L2Q_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"ZZTo2L2Nu_powheg_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ZZTo2L2Nu_powheg_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__ZZTo2Q2Nu_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();


      //
      // TTV
      //
      ch = new TChain("t"); 
      ch->Add(input_dir+"TTWJetsToLNu_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__TTWJetsToLNu_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"TTWJetsToQQ_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__TTWJetsToQQ_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"TTZToQQ_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__TTZToQQ_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__TTZToLLNuNu_M-10_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();


      //
      // tZq
      //
      ch = new TChain("t"); 
      ch->Add(input_dir+"tZq_ll_4f_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__tZq_ll_4f_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();

      ch = new TChain("t"); 
      ch->Add(input_dir+"tZq_nunu_4f_amcnlo_pythia8_25ns*.root");
      stopBabyLooper_ttbar_diLepton_CR(ch, output_dir+"histos__tZq_nunu_4f_amcnlo_pythia8_25ns.root"); 
      ch->~TChain();
      
    } // end loop over babies
  } // end if run over mc
}
