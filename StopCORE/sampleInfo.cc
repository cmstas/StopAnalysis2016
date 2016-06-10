#include "sampleInfo.h"

// ROOT
#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TCollection.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

// C
#include <vector>

//////////////////////////////////////////////////////////////////////

sampleInfo::sampleUtil::sampleUtil( sampleInfo::ID sample ){

  id           = sample;
  isData       = false;
  isFastsim    = false;
  isSignal     = false;
  isSignalScan = false;
  isAMCNLO     = false;

  nBins_stop = 37; 
  min_stop   = 87.5; 
  max_stop   = 1012.5;

  nBins_lsp  = 19; 
  min_lsp    = -12.5; 
  max_lsp    = 462.5;
  
  std::pair< std::string, std::string > temp_i_o;
  
  temp_i_o.first  = baby_inputDir_nominal;
  temp_i_o.second = baby_outputDir_nominal;
  baby_i_o.push_back(temp_i_o);
  
  temp_i_o.first  = baby_inputDir_jesUp;
  temp_i_o.second = baby_outputDir_jesUp;
  baby_i_o.push_back(temp_i_o);
  
  temp_i_o.first  = baby_inputDir_jesDn;
  temp_i_o.second = baby_outputDir_jesDn;
  baby_i_o.push_back(temp_i_o);

  massPtList.clear();
  std::pair< double, double > massPt;
  
  switch( sample ){
    
  case( k_T2tt ):
    label = "T2tt_25ns";
    title = "T2tt";
    tex   = "T2tt";
    isSignal     = true;
    isSignalScan = true;
    isFastsim    = true;
    inputBabies.push_back("Signal_T2tt.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160127/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160127_JESup/merged_files/";
    temp_i_o.second = baby_outputDir_jesUp;
    baby_i_o.push_back(temp_i_o);
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_20160127_JESdown/merged_files/";
    temp_i_o.second = baby_outputDir_jesDn;
    baby_i_o.push_back(temp_i_o);
    massPt.first = 800; massPt.second = 100;
    massPtList.push_back(massPt);
    massPt.first = 800; massPt.second = 350;
    massPtList.push_back(massPt);
    massPt.first = 500; massPt.second = 325;
    massPtList.push_back(massPt);
    massPt.first = 400; massPt.second = 225;
    massPtList.push_back(massPt);
    break;

  case( k_single_lepton_met_2015CD ):
    label  = "data_single_lepton_met_2015CD_25ns";
    title  = "Data, single e/mu, MET dataset, 2015CD";
    tex    = "Data,~single~$e/\\mu$,~MET,~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_met*.root");
    inputBabies.push_back("data_single_electron*.root");
    inputBabies.push_back("data_single_muon*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_met_2015CD ):
    label  = "data_met_2015CD_25ns";
    title  = "Data, MET dataset, 2015CD";
    tex    = "Data,~MET,~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_met*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_met_2015C ):
    label  = "data_met_2015C_25ns";
    title  = "Data, MET dataset, 2015C";
    tex    = "Data,~MET,~dataset,~2015C";
    isData = true;
    inputBabies.push_back("data_met_2015C*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_met_2015D_05Oct2015_v1 ):
    label  = "data_met_2015D_05Oct2015_v1_25ns";
    title  = "Data, MET dataset, 2015D 05Oct2015 v1";
    tex    = "Data,~MET,~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("data_met_2015D_05Oct2015_v1*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_met_2015D_promptRecoV4 ):
    label  = "data_met_2015D_promptRecoV4_25ns";
    title  = "Data, MET dataset, 2015D prompt reco V4";
    tex    = "Data,~MET,~dataset,~2015D~prompt~reco~V4";
    isData = true;
    inputBabies.push_back("data_met_2015D_promtRecoV4*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_lepton_2015CD ):
    label  = "data_single_lepton_2015CD_25ns";
    title  = "Data, single e/mu dataset, 2015CD";
    tex    = "Data,~single~$e/\\mu$,~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_single_electron*.root");
    inputBabies.push_back("data_single_muon*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_el_2015CD ):
    label  = "data_single_el_2015CD_25ns";
    title  = "Data, single electron dataset, 2015CD";
    tex    = "Data,~single~$e$,~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_single_electron*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_el_2015C ):
    label  = "data_single_el_2015C_25ns";
    title  = "Data, single electron dataset, 2015C";
    tex    = "Data,~single~$e$,~dataset,~2015C";
    isData = true;
    inputBabies.push_back("data_single_electron_2015C*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_el_2015D_05Oct2015_v1 ):
    label  = "data_single_el_2015D_05Oct2015_v1_25ns";
    title  = "Data, single electron dataset, 2015D 05Oct2015 v1";
    tex    = "Data,~single~$e$,~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("data_single_electron_2015D_05Oct2015_v1*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_el_2015D_promptRecoV4 ):
    label  = "data_single_el_2015D_promptRecoV4_25ns";
    title  = "Data, single electron dataset, 2015D prompt reco V4";
    tex    = "Data,~single~$e$,~dataset,~2015D~prompt~reco~v4";
    isData = true;
    inputBabies.push_back("data_single_electron_promptRecoV4*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_mu_2015CD ):
    label  = "data_single_mu_2015CD_25ns";
    title  = "Data, single muon dataset, 2015CD";
    tex    = "Data,~single~$\\mu$,~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_single_muon*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_mu_2015C ):
    label  = "data_single_mu_2015C_25ns";
    title  = "Data, single muon dataset, 2015C";
    tex    = "Data,~single~$\\mu$,~dataset,~2015C";
    isData = true;
    inputBabies.push_back("data_single_muon_2015C*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_mu_2015D_05Oct2015_v1 ):
    label  = "data_single_mu_2015D_05Oct2015_v1_25ns";
    title  = "Data, single muon dataset, 2015D 05Oct2015 v1";
    tex    = "Data,~single~$\\mu$,~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("data_single_muon_2015D_05Oct2015_v1*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_mu_2015D_promptRecoV4 ):
    label  = "data_single_mu_2015D_promptRecoV4_25ns";
    title  = "Data, single muon dataset, 2015D prompt reco V4";
    tex    = "Data,~single~$\\mu$,~dataset,~2015D~prompt~reco~v4";
    isData = true;
    inputBabies.push_back("data_single_muon_promptRecoV4*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_diLepton_2015CD ):
    label  = "data_diLepton_2015CD_25ns";
    title  = "Data, ee/emu/mumu dataset, 2015CD";
    tex    = "Data,$~ee/e\\mu/\\mu\\mu$~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_muon_eg*.root");
    inputBabies.push_back("data_double_eg*.root");
    inputBabies.push_back("data_double_mu*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;
    
  case( k_muon_eg_2015CD ):
    label  = "data_muon_eg_2015CD_25ns";
    title  = "Data, e/mu dataset, 2015CD";
    tex    = "Data,$~e\\mu$~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_muon_eg*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;
  
  case( k_muon_eg_2015C ):
    label  = "data_muon_eg_2015C_25ns";
    title  = "Data, e/mu dataset, 2015C";
    tex    = "Data,$~e\\mu$~dataset,~2015C";
    isData = true;
    inputBabies.push_back("data_muon_eg_2015C*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;
  
  case( k_muon_eg_2015D_05Oct2015_v1 ):
    label  = "data_muon_eg_2015D_05Oct2015_v1_25ns";
    title  = "Data, e/mu dataset, 2015D 05Oct2015 v1";
    tex    = "Data,$~e\\mu$~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("data_muon_eg_2015D_05Oct2015_v1*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_muon_eg_2015D_05Oct2015_v2 ):
    label  = "data_muon_eg_2015D_05Oct2015_v2_25ns";
    title  = "Data, e/mu dataset, 2015D 05Oct2015 v2";
    tex    = "Data,$~e\\mu$~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("data_muon_eg_2015D_05Oct2015_v2*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_muon_eg_2015D_promptRecoV4 ):
    label  = "data_muon_eg_2015D_promptRecoV4_25ns";
    title  = "Data, e/mu dataset, 2015D prompt reco V4";
    tex    = "Data,$~e\\mu$~dataset,~2015D~prompt~reco~V4";
    isData = true;
    inputBabies.push_back("data_muon_eg_2015D_promptRecoV4*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_double_eg_2015CD ):
    label  = "data_double_eg_2015CD_25ns";
    title  = "Data, ee dataset, 2015CD";
    tex    = "Data,$~ee$~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_double_eg*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_double_eg_2015C ):
    label  = "data_double_eg_2015C_25ns";
    title  = "Data, ee dataset, 2015C";
    tex    = "Data,$~ee$~dataset,~2015C";
    isData = true;
    inputBabies.push_back("data_double_eg_2015C*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_double_eg_2015D_05Oct2015_v1 ):
    label  = "data_double_eg_2015D_05Oct2015_v1_25ns";
    title  = "Data, ee dataset, 2015D 05Oct2015 v1";
    tex    = "Data,$~ee$~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("data_double_eg_2015D_05Oct2015*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_double_eg_2015D_promptRecoV4 ):
    label  = "data_double_eg_2015D_promptRecoV4_25ns";
    title  = "Data, ee dataset, 2015D promptReco v4";
    tex    = "Data,$~ee$~dataset,~2015D~promptReco~v4";
    isData = true;
    inputBabies.push_back("data_double_eg_2015D_promptRecoV4*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_double_muon_2015CD ):
    label  = "data_double_muon_2015CD_25ns";
    title  = "Data, mumu dataset, 2015CD";
    tex    = "Data,$~\\mu\\mu$~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("data_double_mu*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;    

  case( k_double_muon_2015C ):
    label  = "data_double_muon_2015C_25ns";
    title  = "Data, mumu dataset, 2015C";
    tex    = "Data,$~\\mu\\mu$~dataset,~2015C";
    isData = true;
    inputBabies.push_back("data_double_mu_2015C*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;  

  case( k_double_muon_2015D_05Oct2015_v1 ):
    label  = "data_double_muon_2015D_05Oct2015_v1_25ns";
    title  = "Data, mumu dataset, 2015D 05Oct2015 v1";
    tex    = "Data,$~\\mu\\mu$~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("data_double_mu_2015D_05Oct2015_v1*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;    
  
  case( k_double_muon_2015D_promptRecoV4 ):
    label  = "data_double_muon_2015D_promptRecoV4_25ns";
    title  = "Data, mumu dataset, 2015D promptReco v4";
    tex    = "Data,$~\\mu\\mu$~dataset,~2015D~promptReco~v4";
    isData = true;
    inputBabies.push_back("data_double_mu_2015D_promptRecoV4*.root");
    baby_i_o.clear();
    temp_i_o.first  = baby_inputDir_nominal;
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;    

  case( k_single_photon_2015CD ):
    label  = "data_single_photon_2015CD_25ns";
    title  = "Data, single photon dataset, 2015CD";
    tex    = "Data,~single~$\\gamma$,~dataset,~2015CD";
    isData = true;
    inputBabies.push_back("singlephoton_*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_photon_2015C ):
    label  = "data_single_photon_2015C_25ns";
    title  = "Data, single photon dataset, 2015C";
    tex    = "Data,~single~$\\gamma$,~dataset,~2015C";
    isData = true;
    inputBabies.push_back("singlephoton_2015C*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_photon_2015D_05Oct2015_v1 ):
    label  = "data_single_photon_2015D_05Oct2015_v1_25ns";
    title  = "Data, single photon dataset, 2015D 05Oct2015 v1";
    tex    = "Data,~single~$\\gamma$,~dataset,~2015D~05Oct2015~v1";
    isData = true;
    inputBabies.push_back("singlephoton_2015D_05Oct2015_v1*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_single_photon_2015D_promptRecoV4 ):
    label  = "data_single_photon_2015D_promptRecoV4_25ns";
    title  = "Data, single photon dataset, 2015D prompt reco V4";
    tex    = "Data,~single~$\\gamma$,~dataset,~2015D~prompt~reco~v4";
    isData = true;
    inputBabies.push_back("singlephoton_promptRecoV4*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_allBkg ):
    label = "allBkg_25ns";
    title = "All Background";
    tex   = "All~Background";
    inputBabies.push_back("ttbar_powheg_pythia8_ext3_25ns*.root");
    inputBabies.push_back("DYJetsToLL_m10To50_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("DYJetsToLL_m50_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("t_sch_4f_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("t_tch_4f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("tbar_tch_4f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("t_tW_5f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("t_tbarW_5f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("WWTo2l2Nu_powheg_25ns*.root");
    inputBabies.push_back("WWToLNuQQ_powheg_25ns*.root");
    inputBabies.push_back("WZTo3LNu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("WZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1LNu2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1L3Nu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo4L_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Nu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTWJetsToLNu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTWJetsToQQ_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTZToQQ_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("tZq_ll_4f_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("tZq_nunu_4f_amcnlo_pythia8_25ns*.root");
    break;

  case( k_ttbar ):
    label = "ttbar_25ns";
    title = "ttbar";
    tex   = "$t\\bar{t}$";
    inputBabies.push_back("ttbar_powheg_pythia8_ext3_25ns*.root");
    break;

  case( k_ttbar_powheg_pythia8 ):
    label = "ttbar_powheg_pythia8_25ns";
    title = "ttbar, powheg pythia8";
    tex   = "$t\\bar{t}$,~powheg~pythia8";
    inputBabies.push_back("ttbar_powheg_pythia8_25ns*.root");
    break;

  case( k_ttbar_powheg_pythia8_ext3 ):
    label = "ttbar_powheg_pythia8_ext3_25ns";
    title = "ttbar, powheg pythia8, ext3";
    tex   = "$t\\bar{t}$,~powheg~pythia8~ext3";
    inputBabies.push_back("ttbar_powheg_pythia8_ext3_25ns*.root");
    break;

  case( k_ttbar_singleLeptFromT_madgraph_pythia8 ):
    label = "ttbar_singleLeptFromT_madgraph_pythia8_25ns";
    title = "ttbar, single lepFromT, madgraph pythia8";
    tex   = "$t\\bar{t}$,~single~lepFromT,~madgraph~pythia8";
    inputBabies.push_back("ttbar_singleLeptFromT_madgraph_pythia8_25ns*.root");
    break;

  case( k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 ):
    label = "ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns";
    title = "ttbar, single lepFromT, madgraph pythia8, ext1";
    tex   = "$t\\bar{t}$,~single~lepFromT,~madgraph~pythia8,~ext1";
    inputBabies.push_back("ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns*.root");
    break;

  case( k_ttbar_singleLeptFromTbar_madgraph_pythia8 ):
    label = "ttbar_singleLeptFromTbar_madgraph_pythia8_25ns";
    title = "ttbar, single lepFromTbar, madgraph pythia8";
    tex   = "$t\\bar{t}$,~single~lepFromTbar,~madgraph~pythia8";
    inputBabies.push_back("ttbar_singleLeptFromTbar_madgraph_pythia8_25ns*.root");
    break;

  case( k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 ):
    label = "ttbar_singleLeptFromTbar_madgraph_pythia8_ext1_25ns";
    title = "ttbar, single lepFromTbar, madgraph pythia8, ext1";
    tex   = "$t\\bar{t}$,~single~lepFromTbar,~madgraph~pythia8,~ext1";
    inputBabies.push_back("ttbar_singleLeptFromTbar_madgraph_pythia8_ext1_25ns*.root");
    break;

  case( k_ttbar_diLept_madgraph_pythia8 ):
    label = "ttbar_diLept_madgraph_pythia8_25ns";
    title = "ttbar, diLepton, madgraph pythia8";
    tex   = "$t\\bar{t}$,~diLepton,~madgraph~pythia8";
    inputBabies.push_back("ttbar_diLept_madgraph_pythia8_25ns*.root");
    break;

  case( k_ttbar_diLept_madgraph_pythia8_ext1 ):
    label = "ttbar_diLept_madgraph_pythia8_ext1_25ns";
    title = "ttbar, diLepton, madgraph pythia8, ext1";
    tex   = "$t\\bar{t}$,~diLepton,~madgraph~pythia8,~ext1";
    inputBabies.push_back("ttbar_diLept_madgraph_pythia8_ext1_25ns*.root");
    break;

  case( k_VJets ):
    label = "VJets_25ns";
    title = "V+Jets";
    tex   = "$V$+Jets";
    inputBabies.push_back("DYJetsToLL_m10To50_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("DYJetsToLL_m50_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root");
    break;

  case( k_DYJetsToLL ):
    label = "DYJetsToLL_25ns";
    title = "DY+Jets to LL";
    tex   = "DY+Jets$\\rightarrow\\ell\\ell$";
    inputBabies.push_back("DYJetsToLL_m10To50_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("DYJetsToLL_m50_amcnlo_pythia8_25ns*.root");
    break;

  case( k_DYJetsToLL_m10To50_amcnlo_pythia8 ):
    label = "DYJetsToLL_m10To50_amcnlo_pythia8_25ns";
    title = "DY+Jets to LL, M10to50, amcnlo pythia8";
    tex   = "DY+Jets$\\rightarrow\\ell\\ell$,~M10to50,~amcnlo~pythia8";
    inputBabies.push_back("DYJetsToLL_m10To50_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;    

  case( k_DYJetsToLL_m50_amcnlo_pythia8 ):
    label = "DYJetsToLL_m50_amcnlo_pythia8_25ns";
    title = "DY+Jets to LL, M50, amcnlo pythia8";
    tex   = "DY+Jets$\\rightarrow\\ell\\ell$,~M50,~amcnlo~pythia8";
    inputBabies.push_back("DYJetsToLL_m50_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;        
    
  case( k_WJetsToLNu ):
    label = "WJetsToLNu_25ns";
    title = "W+Jets to LNu";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$";
    inputBabies.push_back("WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root");
    break;

  case( k_WJetsToLNu_amcnlo_pythia8 ):
    label = "WJetsToLNu_amcnlo_pythia8_25ns";
    title = "W+Jets to LNu, amcnlo pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~amcnlo~pythia8";
    inputBabies.push_back("WJetsToLNu_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_WJetsToLNu_HT100ToInf_madgraph_pythia8 ):
    label = "WJetsToLNu_HT100ToInf_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 100<HT<Inf, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$100<HT<Inf$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root");
    inputBabies.push_back("WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root");
    break;

  case( k_WJetsToLNu_HT100To200_madgraph_pythia8 ):
    label = "WJetsToLNu_HT100To200_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 100<HT<200, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$100<HT<200$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root");
    break;
    
  case( k_WJetsToLNu_HT200To400_madgraph_pythia8 ):
    label = "WJetsToLNu_HT200To400_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 200<HT<400, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$200<HT<400$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root");
    break;

  case( k_WJetsToLNu_HT400To600_madgraph_pythia8 ):
    label = "WJetsToLNu_HT400To600_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 400<HT<600, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$400<HT<600$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root");
    break;
    
  case( k_WJetsToLNu_HT600ToInf_madgraph_pythia8 ):
    label = "WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 600<HT<Inf, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$600<HT<Inf$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns*.root");
    break;

  case( k_WJetsToLNu_HT600To800_madgraph_pythia8 ):
    label = "WJetsToLNu_HT600To800_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 600<HT<800, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$600<HT<800$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root");
    break;

  case( k_WJetsToLNu_HT800To1200_madgraph_pythia8 ):
    label = "WJetsToLNu_HT800To1200_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 800<HT<1200, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$800<HT<1200$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root");
    break;

  case( k_WJetsToLNu_HT1200To2500_madgraph_pythia8 ):
    label = "WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 1200<HT<2500, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$1200<HT<2500$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root");
    break;

  case( k_WJetsToLNu_HT2500ToInf_madgraph_pythia8 ):
    label = "WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns";
    title = "W+Jets to LNu, 2500<HT<Inf, madgraph pythia8";
    tex   = "W+Jets$\\rightarrow\\ell\\nu$,~$2500<HT<Inf$,~madgraph~pythia8";
    inputBabies.push_back("WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root");
    break;

  case( k_singleT ):
    label = "singleT_25ns";
    title = "single t";
    tex   = "single $t$";
    inputBabies.push_back("t_sch_4f_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("t_tch_4f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("tbar_tch_4f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("t_tW_5f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("t_tbarW_5f_powheg_pythia8_25ns*.root");
    break;

  case( k_t_sch_4f_amcnlo_pythia8 ):
    label = "t_sch_4f_amcnlo_pythia8_25ns";
    title = "single t, s-channel, amcnlo pythia8";
    tex   = "single $t$,~s-channel,~amcnlo~pythia8";
    inputBabies.push_back("t_sch_4f_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_t_tch_4f_powheg_pythia8 ):
    label = "t_tch_4f_powheg_pythia8_25ns";
    title = "single t, t-channel, powheg pythia8";
    tex   = "single $t$,~t-channel,~powheg~pythia8";
    inputBabies.push_back("t_tch_4f_powheg_pythia8_25ns*.root");
    break;

  case( k_tbar_tch_4f_powheg_pythia8 ):
    label = "tbar_tch_4f_powheg_pythia8_25ns";
    title = "single tbar, t-channel, powheg pythia8";
    tex   = "single $\\bar{t}$,~t-channel,~powheg~pythia8";
    inputBabies.push_back("tbar_tch_4f_powheg_pythia8_25ns*.root");
    break;

  case( k_singleT_tW ):
    label = "singleT_tW_25ns";
    title = "single t, tW-channel";
    tex   = "single $t$~$t-W$-channel";
    inputBabies.push_back("t_tW_5f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("t_tbarW_5f_powheg_pythia8_25ns*.root");
    break;

  case( k_singleT_non_tW ):
    label = "singleT_non_tW_25ns";
    title = "single t, non tW-channel";
    tex   = "single $t$~non~$t-W$-channel";
    inputBabies.push_back("t_sch_4f_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("t_tch_4f_powheg_pythia8_25ns*.root");
    inputBabies.push_back("tbar_tch_4f_powheg_pythia8_25ns*.root");
    break;

  case( k_t_tW_5f_powheg_pythia8 ):
    label = "t_tW_5f_powheg_pythia8_25ns";
    title = "single t, W-channel, powheg pythia8";
    tex   = "single $t,~t-W$-channel,~powheg~pythia8";
    inputBabies.push_back("t_tW_5f_powheg_pythia8_25ns*.root");
    break;

  case( k_t_tbarW_5f_powheg_pythia8 ):
    label = "t_tbarW_5f_powheg_pythia8_25ns";
    title = "single tbar, W-channel, powheg pythia8";
    tex   = "single $\\bar{t},~t-W$-channel,~powheg~pythia8";
    inputBabies.push_back("t_tbarW_5f_powheg_pythia8_25ns*.root");
    break;
    
  case( k_rare ):
    label = "rare_25ns";
    title = "Rare";
    tex   = "Rare";
    inputBabies.push_back("WWTo2l2Nu_powheg_25ns*.root");
    inputBabies.push_back("WWToLNuQQ_powheg_25ns*.root");
    inputBabies.push_back("WZTo3LNu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("WZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1LNu2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1L3Nu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo4L_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Nu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTWJetsToLNu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTWJetsToQQ_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTZToQQ_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("tZq_ll_4f_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("tZq_nunu_4f_amcnlo_pythia8_25ns*.root");
    break;

  case( k_diBoson ):
    label = "diBoson_25ns";
    title = "diBoson";
    tex   = "diBoson";
    inputBabies.push_back("WWTo2l2Nu_powheg_25ns*.root");
    inputBabies.push_back("WWToLNuQQ_powheg_25ns*.root");
    inputBabies.push_back("WZTo3LNu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("WZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1LNu2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1L3Nu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo4L_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Nu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root");
    break;

  case( k_WW ):
    label = "WW_25ns";
    title = "WW";
    tex   = "$WW$";
    inputBabies.push_back("WWTo2l2Nu_powheg_25ns*.root");
    inputBabies.push_back("WWToLNuQQ_powheg_25ns*.root");
    break;

  case( k_WWTo2l2Nu_powheg ):
    label = "WWTo2l2Nu_powheg_25ns";
    title = "WW to 2l2nu, powheg";
    tex   = "$WW{\\rightarrow}2\\ell2\\nu$,~powheg";
    inputBabies.push_back("WWTo2l2Nu_powheg_25ns*.root");
    break;

  case( k_WWToLNuQQ_powheg ):
    label = "WWToLNuQQ_powheg_25ns";
    title = "WW to LNuQQ, powheg";
    tex   = "$WW{\\rightarrow}{\\ell}{\\nu}qq$,~powheg";
    inputBabies.push_back("WWToLNuQQ_powheg_25ns*.root");
    break;

  case( k_WZ ):
    label = "WZ_25ns";
    title = "WZ";
    tex   = "$WZ$";
    inputBabies.push_back("WZTo3LNu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("WZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1LNu2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("WZTo1L3Nu_amcnlo_pythia8_25ns*.root");
    break;

  case( k_WZ_pythia8 ):
    label = "WZ_pythia8_25ns";
    title = "WZ, pythia8";
    tex   = "$WZ$,~pythia8";
    inputBabies.push_back("WZ_pythia8_25ns*.root");
    break;

  case( k_WZTo3LNu_powheg_pythia8 ):
    label = "WZTo3LNu_powheg_pythia8_25ns";
    title = "WZ to 3LNu, powheg pythia8";
    tex   = "$WZ{\\rightarrow}3\\ell\\nu$,~powheg~pythia8";
    inputBabies.push_back("WZTo3LNu_powheg_pythia8_25ns*.root");
    break;

  case( k_WZTo2L2Q_amcnlo_pythia8 ):
    label = "WZTo2L2Q_amcnlo_pythia8_25ns";
    title = "WZ to 2L2Q, amcnlo pythia8";
    tex   = "$WZ{\\rightarrow}2{\\ell}2Q$,~amcnlo~pythia8";
    inputBabies.push_back("WZTo2L2Q_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_WZTo1LNu2Q_amcnlo_pythia8 ):
    label = "WZTo1LNu2Q_amcnlo_pythia8_25ns";
    title = "WZ to LNu2Q, amcnlo pythia8";
    tex   = "$WZ{\\rightarrow}{\\ell}{\\nu}2Q$,~amcnlo~pythia8";
    inputBabies.push_back("WZTo1LNu2Q_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_WZTo1L3Nu_amcnlo_pythia8 ):
    label = "WZTo1L3Nu_amcnlo_pythia8_25ns";
    title = "WZ to 1L3Nu, amcnlo pythia8";
    tex   = "$WZ{\\rightarrow}1{\\ell}3{\\nu}$,~amcnlo~pythia8";
    inputBabies.push_back("WZTo1L3Nu_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_ZZ ):
    label = "ZZ_25ns";
    title = "ZZ";
    tex   = "$ZZ$";
    inputBabies.push_back("ZZTo4L_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Q_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2L2Nu_powheg_pythia8_25ns*.root");
    inputBabies.push_back("ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root");
    break;

  case( k_ZZ_pythia8 ):
    label = "ZZ_pythia8_25ns";
    title = "ZZ, pythia8";
    tex   = "$ZZ$,~pythia8";
    inputBabies.push_back("ZZ_pythia8_25ns*.root");
    break;

  case( k_ZZTo4L_powheg_pythia8 ):
    label = "ZZTo4L_powheg_pythia8_25ns";
    title = "ZZ to 4L, powheg pythia8";
    tex   = "$ZZ{\\rightarrow}4\\ell$,~powheg~pythia8";
    inputBabies.push_back("ZZTo4L_powheg_pythia8_25ns*.root");
    break;

  case( k_ZZTo2L2Q_amcnlo_pythia8 ):
    label = "ZZTo2L2Q_amcnlo_pythia8_25ns";
    title = "ZZ to 2L2Q, amcnlo pythia8";
    tex   = "$ZZ{\\rightarrow}2{\\ell}2Q$,~amcnlo~pythia8";
    inputBabies.push_back("ZZTo2L2Q_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_ZZTo2L2Nu_powheg_pythia8 ):
    label = "ZZTo2L2Nu_powheg_pythia8_25ns";
    title = "ZZ to 2L2Nu, powheg pythia8";
    tex   = "$ZZ{\\rightarrow}2{\\ell}2{\\nu}$,~powheg~pythia8";
    inputBabies.push_back("ZZTo2L2Nu_powheg_pythia8_25ns*.root");
    break;

  case( k_ZZTo2Q2Nu_amcnlo_pythia8 ):
    label = "ZZTo2Q2Nu_amcnlo_pythia8_25ns";
    title = "ZZ to 2Q2Nu, amcnlo pythia8";
    tex   = "$ZZ{\\rightarrow}2Q2{\\nu}$,~amcnlo~pythia8";
    inputBabies.push_back("ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_TTV ):
    label = "TTV_25ns";
    title = "TTV";
    tex   = "$t\\bar{t}+V$";
    inputBabies.push_back("TTWJetsToLNu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTWJetsToQQ_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTZToQQ_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root");
    break;

  case( k_TTW ):
    label = "TTW_25ns";
    title = "TTW";
    tex   = "$t\\bar{t}+W$";
    inputBabies.push_back("TTWJetsToLNu_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTWJetsToQQ_amcnlo_pythia8_25ns*.root");
    break;

  case( k_TTWJetsToLNu_amcnlo_pythia8 ):
    label = "TTWJetsToLNu_amcnlo_pythia8_25ns";
    title = "TTW to LNu, amcnlo pythia8";
    tex   = "$t\\bar{t}+W{\\rightarrow}{\\ell}{\\nu}$,~amcnlo~pythia8";
    inputBabies.push_back("TTWJetsToLNu_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_TTWJetsToQQ_amcnlo_pythia8 ):
    label = "TTWJetsToQQ_amcnlo_pythia8_25ns";
    title = "TTW to QQ, amcnlow pythia8";
    tex   = "$t\\bar{t}+W{\\rightarrow}QQ$,~amcnlo~pythia8";
    inputBabies.push_back("TTWJetsToQQ_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;
    
  case( k_TTZ ):
    label = "TTZ_25ns";
    title = "TTZ";
    tex   = "$t\\bar{t}+Z$";
    inputBabies.push_back("TTZToQQ_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root");
    break;

  case( k_TTZToQQ_amcnlo_pythia8 ):
    label = "TTZToQQ_amcnlo_pythia8_25ns";
    title = "TTZ to QQ, amcnlo pythia8";
    tex   = "$t\\bar{t}+Z{\\rightarrow}QQ$,~amcnlo~pythia8";
    inputBabies.push_back("TTZToQQ_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_TTZToLLNuNu_m10_amcnlo_pythia8 ):
    label = "TTZToLLNuNu_M-10_amcnlo_pythia8_25ns";
    title = "TTZ to 2L2Nu, amcnlo pythia8";
    tex   = "$t\\bar{t}+Z{\\rightarrow}2{\\ell}2{\\nu}$,~amcnlo~pythia8";
    inputBabies.push_back("TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_tZq ):
    label = "tZq_25ns";
    title = "tZq";
    tex   = "$tZq$";
    inputBabies.push_back("tZq_ll_4f_amcnlo_pythia8_25ns*.root");
    inputBabies.push_back("tZq_nunu_4f_amcnlo_pythia8_25ns*.root");
    break;

  case( k_tZq_ll_4f_amcnlo_pythia8 ):
    label = "tZq_ll_4f_amcnlo_pythia8_25ns";
    title = "tZq to 2L, amcnlo pythia8";
    tex   = "$tZq{\\rightarrow}2{\\ell}$,~amcnlo~pythia8";
    inputBabies.push_back("tZq_ll_4f_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;

  case( k_tZq_nunu_4f_amcnlo_pythia8 ):
    label = "tZq_nunu_4f_amcnlo_pythia8_25ns";
    title = "tZq to 2Nu, amcnlo pythia8";
    tex   = "$tZq{\\rightarrow}2{\\nu}$,~amcnlo~pythia8";
    inputBabies.push_back("tZq_nunu_4f_amcnlo_pythia8_25ns*.root");
    isAMCNLO = true;
    break;
    
  case( k_GJets_HT40toInf_madgraph_pythia8 ):
    label = "GJets_HT40toInf_madgraph_pythia8,_25ns";
    title = "Gamma+Jets, HT>40, madraph pythia8";
    tex   = "${\\gamma}$+Jets,~$HT>40$,~madgraph~pythia8";
    inputBabies.push_back("GJets_HT40to100*.root");
    inputBabies.push_back("GJets_HT100To200*.root");
    inputBabies.push_back("GJets_HT200To400*.root");
    inputBabies.push_back("GJets_HT400To600*.root");
    inputBabies.push_back("GJets_HT600ToInf*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_GJets_HT40To100_madgraph_pythia8 ):
    label = "GJets_HT40To100_madgraph_pythia8,_25ns";
    title = "Gamma+Jets, 40<HT<100, madraph pythia8";
    tex   = "${\\gamma}$+Jets,~$40<HT<100$,~madgraph~pythia8";
    inputBabies.push_back("GJets_HT40To100*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_GJets_HT100To200_madgraph_pythia8 ):
    label = "GJets_HT100To200_madgraph_pythia8,_25ns";
    title = "Gamma+Jets, 100<HT<200, madraph pythia8";
    tex   = "${\\gamma}$+Jets,~$100<HT<200$,~madgraph~pythia8";
    inputBabies.push_back("GJets_HT100To200*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_GJets_HT200To400_madgraph_pythia8 ):
    label = "GJets_HT200To400_madgraph_pythia8,_25ns";
    title = "Gamma+Jets, 200<HT<400, madraph pythia8";
    tex   = "${\\gamma}$+Jets,~$200<HT<400$,~madgraph~pythia8";
    inputBabies.push_back("GJets_HT200To400*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_GJets_HT400To600_madgraph_pythia8 ):
    label = "GJets_HT400To600_madgraph_pythia8,_25ns";
    title = "Gamma+Jets, 400<HT<600, madraph pythia8";
    tex   = "${\\gamma}$+Jets,~$400<HT<600$,~madgraph~pythia8";
    inputBabies.push_back("GJets_HT400To600*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  case( k_GJets_HT600ToInf_madgraph_pythia8 ):
    label = "GJets_HT600ToInf_madgraph_pythia8,_25ns";
    title = "Gamma+Jets, HT>600, madraph pythia8";
    tex   = "${\\gamma}$+Jets,~$HT>600$,~madgraph~pythia8";
    inputBabies.push_back("GJets_HT600ToInf*.root");
    baby_i_o.clear();
    temp_i_o.first  = "/hadoop/cms/store/user/haweber/condor/stop1l/stopbabies_201510XX_photons/merged_files/";
    temp_i_o.second = baby_outputDir_nominal;
    baby_i_o.push_back(temp_i_o);
    break;

  default:
    std::cout << "Could not find sample info from sample enum provided!" << std::endl;
    label = "NO SAMPLE INFO FOUND FROM ENUM PROVIDED";
    title = "NO SAMPLE INFO FOUND FROM ENUM PROVIDED";
    tex   = "NO SAMPLE INFO FOUND FROM ENUM PROVIDED";
    break;
    
  } // end switch for case of sampleID enum  

}

//////////////////////////////////////////////////////////////////////

sampleInfo::vect_id sampleInfo::getSampleList( analyzerInfo::ID analysis ){

  vect_id result;

  //
  // Get Data
  //
  switch( analysis ){

  case( analyzerInfo::k_SR ):
  case( analyzerInfo::k_CR0b ):
  case( analyzerInfo::k_CR1l_bulkWJets ):
  case( analyzerInfo::k_CR2l ):
    result.push_back( sampleInfo::k_single_lepton_met_2015CD );
    break;
  
  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( sampleInfo::k_diLepton_2015CD );
    break;
  
  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( sampleInfo::k_single_photon_2015CD );
    break;
    
  default:
    result.push_back( sampleInfo::k_single_lepton_met_2015CD );
    break;
  
  }; // end switch to choose data


  //
  // Get MC
  //
  switch( analysis ){

  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( sampleInfo::k_GJets_HT40To100_madgraph_pythia8 );
    result.push_back( sampleInfo::k_GJets_HT100To200_madgraph_pythia8 );
    result.push_back( sampleInfo::k_GJets_HT200To400_madgraph_pythia8 );
    result.push_back( sampleInfo::k_GJets_HT400To600_madgraph_pythia8 );
    result.push_back( sampleInfo::k_GJets_HT600ToInf_madgraph_pythia8 );
    break;
    
  case( analyzerInfo::k_SR ):

  case( analyzerInfo::k_CR0b ):

  case( analyzerInfo::k_CR1l_bulkWJets ):

  case( analyzerInfo::k_CR2l ):

  case( analyzerInfo::k_CR2l_bulkTTbar ):

  default:

    // MC, ttbar
    result.push_back( sampleInfo::k_ttbar_powheg_pythia8_ext3 );
    //result.push_back( sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 );
    //result.push_back( sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 );
    //result.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1);
  
    // MC, DYJets
    result.push_back( sampleInfo::k_DYJetsToLL_m10To50_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_DYJetsToLL_m50_amcnlo_pythia8 );
  
    // MC, WJets
    result.push_back( sampleInfo::k_WJetsToLNu_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT100To200_madgraph_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT200To400_madgraph_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT400To600_madgraph_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT600ToInf_madgraph_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT600To800_madgraph_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT800To1200_madgraph_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT1200To2500_madgraph_pythia8 );
    result.push_back( sampleInfo::k_WJetsToLNu_HT2500ToInf_madgraph_pythia8 );
  
    // MC, single t
    result.push_back( sampleInfo::k_t_sch_4f_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_t_tch_4f_powheg_pythia8 );
    result.push_back( sampleInfo::k_tbar_tch_4f_powheg_pythia8 );
    result.push_back( sampleInfo::k_t_tW_5f_powheg_pythia8 );
    result.push_back( sampleInfo::k_t_tbarW_5f_powheg_pythia8 );
    
    // MC, diBoson
    result.push_back( sampleInfo::k_WWTo2l2Nu_powheg );
    result.push_back( sampleInfo::k_WWToLNuQQ_powheg );
    result.push_back( sampleInfo::k_WZ_pythia8 );
    result.push_back( sampleInfo::k_WZTo3LNu_powheg_pythia8 );
    result.push_back( sampleInfo::k_WZTo2L2Q_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_WZTo1LNu2Q_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_WZTo1L3Nu_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_ZZ_pythia8 );
    result.push_back( sampleInfo::k_ZZTo4L_powheg_pythia8 );
    result.push_back( sampleInfo::k_ZZTo2L2Q_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_ZZTo2L2Nu_powheg_pythia8 );
    result.push_back( sampleInfo::k_ZZTo2Q2Nu_amcnlo_pythia8 );
  
    // MC, TTV
    result.push_back( sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_TTWJetsToQQ_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_TTZToQQ_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_TTZToLLNuNu_m10_amcnlo_pythia8 );
  
    // MC, tZq
    result.push_back( sampleInfo::k_tZq_ll_4f_amcnlo_pythia8 );
    result.push_back( sampleInfo::k_tZq_nunu_4f_amcnlo_pythia8 );

    break;
      
  }; // end switch to choose monte carlo

  return result;
}

//////////////////////////////////////////////////////////////////////

int sampleInfo::scaleSample(std::string f_in_name, std::string f_out_name, double SF){

  std::cout << "Rescaling histos in: " << std::endl;
  std::cout << "    " << f_in_name << ", by SF = " << SF << std::endl;
  std::cout << "Output written to: " << std::endl;
  std::cout << "    " << f_out_name << std::endl;

  TFile *f_in  = new TFile(f_in_name.c_str(), "read");
  TFile *f_out = new TFile(f_out_name.c_str(), "recreate");
  
  TIter nextIter(f_in->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)nextIter())) {
    
    TClass *cl = gROOT->GetClass(key->GetClassName());
    
    if(cl->InheritsFrom("TH1D")){      
      TH1D *h = (TH1D*)key->ReadObj();
      TH1D *h_clone = (TH1D*)h->Clone();
      h_clone->SetDirectory(f_out);
      h_clone->Scale(SF);
    }
    
    if(cl->InheritsFrom("TH2D")){
      TH2D *h = (TH2D*)key->ReadObj();
      TH2D *h_clone = (TH2D*)h->Clone();
      h_clone->SetDirectory(f_out);
      h_clone->Scale(SF);
    }

    if(cl->InheritsFrom("TH3D")){
      TH3D *h = (TH3D*)key->ReadObj();
      TH3D *h_clone = (TH3D*)h->Clone();
      h_clone->SetDirectory(f_out);
      h_clone->Scale(SF);
    }

  }

  f_in->Close();
  f_out->Write();
  f_out->Close();

  return 0;
}

//////////////////////////////////////////////////////////////////////
