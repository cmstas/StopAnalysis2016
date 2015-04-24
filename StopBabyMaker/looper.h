#include "EventTree.h"
#include "GenParticleTree.h"
#include "LeptonTree.h"
#include "JetTree.h"
#include "TauTree.h"
#include "IsoTracksTree.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TF1.h"
#include "Math/VectorUtil.h"
#include "TChain.h"
#include "Math/LorentzVector.h"

// // typedefs
 typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

#ifndef LOOPER_H
#define LOOPER_H

#pragma GCC diagnostic ignored "-Wwrite-strings"

using namespace std;

class babyMaker {

  public:
    //constructor/destructor
    babyMaker ();
    babyMaker (const std::string &prefix);
    virtual ~babyMaker (){}

    void MakeBabyNtuple(const char* output_name);
    void InitBabyNtuple();
    int looper(TChain* chain, char* output_name, int nEvents = -1, char* path = "./");
    char* babypath;
    
    //vaariables for baby skim
    int skim_nvtx;
    float skim_met;

    int skim_nlep;
    float skim_leppt;
    float skim_lepeta;

    int skim_njets;
    float skim_jetpt;
    float skim_jeteta;

    void setSkimVariables(int nvtx, float met, int nlep, float leppt, float lepeta, int njets, int jetpt, int jeteta);

  protected:
    TFile* BabyFile;
    TTree* BabyTree;

  private:

    //for tree
    EventTree StopEvt;
    LeptonTree lep1;
    LeptonTree lep2;
    JetTree jets;
    GenParticleTree gen_els;
    GenParticleTree gen_mus;
    GenParticleTree gen_leptau_els;
    GenParticleTree gen_leptau_mus;
    GenParticleTree gen_taus;
    GenParticleTree gen_nus;
    GenParticleTree gen_bs;
    GenParticleTree gen_tops;
    GenParticleTree gen_qs;
    GenParticleTree gen_lsp;
    GenParticleTree gen_stop;
    TauTree Taus;
    IsoTracksTree Tracks;
// = new EventTree(); //dont make a pointer
};

struct val_err_t { float value; float error; };

#endif
