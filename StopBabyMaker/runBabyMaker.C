#include "TChain.h"
#include "looper.h"
#include "iostream"

using namespace std;

//int main(){
int main(int argc, char **argv){
 if(argc<2){
        cout<<" runBabyMaker takes two arguments: ./runBabyMaker sample_name nevents" << endl;
	cout<<" Need to provide at least sample_name (nevents = -1 by default) "<<endl;
        return 0;
 }
 
  babyMaker *mylooper = new babyMaker();
  //babyMaker::setSkimVariables(int nvtx, float met, int nlep, float leppt, float lepeta, int njets, int jetpt, int jeteta){
   mylooper->setSkimVariables(1, 30., 1, 20., 2.4, 2, 30., 2.4);

  char* dirpath = "../";  
  
  int file=0;
  int nevents = -1;
  if(argc>2) nevents = atoi(argv[2]);  

  const char* filename = (file == 0 ? "merged_ntuple_*.root" : Form("merged_ntuple_%i.root", file));
  cout << filename << endl;
  
  const char* suffix = file == 0 ? "" : Form("_%i", file);

  TChain *sample = new TChain("Events");

  if(strcmp( argv[1], "ttbar") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }

  if(strcmp( argv[1], "stop_850_100") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-850_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "stop_650_325") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-650_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "stop_500_325") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-500_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "stop_425_325") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-425_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }

  if(strcmp( argv[1], "ttwjets") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/TTWJets_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "ttzjets") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/TTZJets_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "dyjets") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_13TeV-madgraph-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "tbar_sch") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "tbar_tch") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/TBarToLeptons_t-channel_Tune4C_CSA14_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "t_sch") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "t_tch") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/TToLeptons_t-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "t_tW") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/T_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "tbar_tW") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/Tbar_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "wjets") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/WJetsToLNu_13TeV-madgraph-pythia8-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "wzjets") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }
  if(strcmp( argv[1], "zz") == 0){
      sample->Add(Form("/hadoop/cms/store/group/snt/phys14/ZZTo4L_Tune4C_13TeV-powheg-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/%s", filename));
  }

  mylooper->looper(sample, Form("%s%s", argv[1],suffix), nevents,dirpath);

  return 0;
}
