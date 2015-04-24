#ifndef EVENTTREE_H
#define EVENTTREE_H
 
#include <string>
#include <vector>
#include "Math/LorentzVector.h"
 
// forward declarations
class TTree;
 
// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<std::string> vecs;
typedef std::vector<int> veci; 
typedef std::vector<bool> vecb;
 
class EventTree
{
public:
    // constructor/destructor
    EventTree ();
    EventTree (const std::string &prefix);
    virtual ~EventTree (){}
 
    void Reset ();
    void SetBranches (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon (const std::string &root_file_name = "");
 
private:
    std::string prefix_;
 
public:
    // branch objects
    unsigned int run;
    unsigned int ls;
    unsigned int evt;
    int nvtxs;

    unsigned int nEvents;
    unsigned int nEvents_goodvtx;
    unsigned int nEvents_MET30;
    unsigned int nEvents_1goodlep;
    unsigned int nEvents_2goodjets;    

    int ngoodlep;
    
    double MT2W_lep1;
    double MT2W_lep2;
    double chi2;
 
    float pfmet;
    float pfmet_phi;

    float dR_lep1_leadb;
    float dR_lep2_leadb;    
    float mindphi_met_j1_j2;
    float MT_MET_lep1;
    float MT_MET_lep2;
 
    bool is_data;
 
    std::string dataset;
    std::string filename;    
    std::string cms3tag;

    //gen info//
    float scale1fb;
    float xsec;
    float kfactor;
    float pu_ntrue;
    int pu_nvtxs;

    //sparms
    vecs sparms_comment;
    vecs sparms_names;
    float sparms_filterEfficiency;
    float sparms_pdfScale;
    float sparms_pdfWeight1;
    float sparms_pdfWeight2;
    float sparms_weight;
    float sparms_xsec;
    vecd sparms_values;
    int sparms_subProcessId;
        
    //gen met
    float genmet;
    float genmet_phi;

   //veto
   bool PassTrackVeto;
   bool PassTauVeto;
};
 
#endif
