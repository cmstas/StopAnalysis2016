{
  string COREpath = "../../../CORE";//need to think how to do this better
  string temp = " -I"+COREpath;
  gSystem->AddIncludePath(temp.c_str());
  temp = ".include "+COREpath;
  gROOT->ProcessLine(temp.c_str());
  int type = 3; //1 Data, 2: MC, 3: Signal
  int jes = -1;
  int whichsignal = 2;//1 T2tt, 2 T2bW, 3 T2tb
  
  unsigned int chainsize = 1;
  if(type==2) chainsize = 5;
  const int maxchainsize = 5;
  TChain *ch[maxchainsize];
  string dataset[maxchainsize];
  string chfile;
  string babylocation;
  for(unsigned int i = 0; i<chainsize; ++i) ch[i] = new TChain("t");     
  if(type==1){
    gROOT->ProcessLine(".L GetSRandCRHistos.C+");
    babylocation = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";
    dataset[0] = "Data";
    chfile = babylocation+"data_met_2015C_25ns.root";                          ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_met_2015D_05Oct2015_v1_25ns.root";             ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_met_2015D_promptRecoV4_25ns.root";             ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_single_electron_2015C_25ns.root";              ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_single_electron_2015D_05Oct2015_v1_25ns.root"; ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_single_electron_2015D_promptRecoV4_25ns.root"; ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_single_muon_2015C_25ns.root";                  ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_single_muon_2015D_05Oct2015_v1_25ns.root";     ch[0]->Add(chfile.c_str());
    chfile = babylocation+"data_single_muon_2015D_promptRecoV4_25ns.root";     ch[0]->Add(chfile.c_str());
  }
  if(type==2){
    gROOT->ProcessLine(".L GetSRandCRHistos.C+");
    if(jes==-1){
      //whatever
    }
    else if(jes==1){
      //whatever
    } else {
      string babylocation = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";
      dataset[0] = "TTbar";//TTbar file will contain 2l/1l separated histograms
      chfile = babylocation+"ttbar_powheg_pythia8_ext3_25ns*.root";               ch[0]->Add(chfile.c_str());
      dataset[1] = "tW";//need to ask John/Indara how they separated tW
      chfile = babylocation+"t_tW_5f_powheg_pythia8_25ns.root";                   ch[1]->Add(chfile.c_str());
      chfile = babylocation+"t_tbarW_5f_powheg_pythia8_25ns.root";                ch[1]->Add(chfile.c_str());
      dataset[2] = "WJets";
      chfile = babylocation+"WJetsToLNu_HT100To200_madgraph_pythia8_25ns.root";   ch[2]->Add(chfile.c_str());
      chfile = babylocation+"WJetsToLNu_HT200To400_madgraph_pythia8_25ns.root";   ch[2]->Add(chfile.c_str());
      chfile = babylocation+"WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root";   ch[2]->Add(chfile.c_str());
      //chfile = babylocation+"WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns.root";   ch[2]->Add(chfile.c_str());
      chfile = babylocation+"WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root";  ch[2]->Add(chfile.c_str());
      chfile = babylocation+"WJetsToLNu_HT800To1200_madgraph_pythia8_25ns.root";  ch[2]->Add(chfile.c_str());
      chfile = babylocation+"WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns.root"; ch[2]->Add(chfile.c_str());
      chfile = babylocation+"WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root";  ch[2]->Add(chfile.c_str());
      dataset[3] = "Zinv";
      chfile = babylocation+"WZTo1L3Nu_amcnlo_pythia8_25ns.root";                 ch[3]->Add(chfile.c_str());
      chfile = babylocation+"ZZTo2L2Nu_powheg_pythia8_25ns.root";                 ch[3]->Add(chfile.c_str());
      chfile = babylocation+"tZq_nunu_4f_amcnlo_pythia8_25ns.root";               ch[3]->Add(chfile.c_str());
      chfile = babylocation+"TTZToLLNuNu_M-10_amcnlo_pythia8_25ns.root";          ch[3]->Add(chfile.c_str());
      dataset[4] = "NonZRare";
      chfile = babylocation+"WWTo2l2Nu_powheg_25ns.root";                         ch[4]->Add(chfile.c_str());
      chfile = babylocation+"TTWJetsToLNu_amcnlo_pythia8_25ns.root";              ch[4]->Add(chfile.c_str());
    }
  }//type MC
  
  //normal
  if(type==3){
    gROOT->ProcessLine(".L GetSignalHistos.C+");
    if(whichsignal==1){
      if(abs(jes)!=  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160127/merged_files/";
      else if(jes==  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160127_JESup/merged_files/";
      else if(jes== -1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160127_JESdown/merged_files/";
      dataset[0] = "Signal_T2tt";
      chfile = babylocation+"Signal_T2tt.root"; ch[0]->Add(chfile.c_str());
    } else if(whichsignal==2){
      if(abs(jes)!=  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218/merged_files/";
      else if(jes==  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218_JESup/merged_files/";
      else if(jes== -1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218_JESdown/merged_files/";
      dataset[0] = "Signal_T2bW";
      chfile = babylocation+"Signal_T2bW.root"; ch[0]->Add(chfile.c_str());
    }
     else if(whichsignal==-2){
      if(abs(jes)!=  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218/merged_files/";
      else if(jes==  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218_JESup/merged_files/";
      else if(jes== -1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218_JESdown/merged_files/";
      dataset[0] = "Signal_T2bW_private";
      chfile = babylocation+"Signal_T2bW_private.root"; ch[0]->Add(chfile.c_str());
    }
     else if(whichsignal==3){
      if(abs(jes)!=  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218/merged_files/";
      else if(jes==  1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218_JESup/merged_files/";
      else if(jes== -1) babylocation = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160218_JESdown/merged_files/";
      dataset[0] = "Signal_T2tb";
      chfile = babylocation+"Signal_T2tb.root"; ch[0]->Add(chfile.c_str());
    }
  }//type 3
  
  for(int i = 0; i<chainsize; ++i){
    TChain *mych = ch[i];
    string mydataset = dataset[i];
    if(jes==1)  mydataset = dataset[i] + "_JESup";
    if(jes==-1) mydataset = dataset[i] + "_JESdown";
    if(type!=2) ScanChain(mych,mydataset,jes);
    else ScanChain(mych,mydataset,jes);
  }


}
