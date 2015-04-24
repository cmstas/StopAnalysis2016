#ifndef LEPTONTREE_H
#define LEPTONTREE_H

#include <string>
#include <vector>
#include "Math/LorentzVector.h"

// forward declaration
class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<int> veci;
enum prodType {fromB, fromC, fromLight, fromZ, fromW, none}; 

class LeptonTree
{
public:
    LeptonTree ();
    LeptonTree (const std::string &prefix);
    virtual ~LeptonTree () {}

    void Reset ();
    void SetBranches (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon (int id, int idx);

protected:

    std::string prefix_;

public:    

    // lepton reco info
    LorentzVector p4;
    LorentzVector pfp4;
    float pt;
    float eta; 
    bool is_mu;
    bool is_el;
    int is_fromw;
    int charge;
    int pdgid;
    int type;
    float d0;
    float d0err;
    float dz;
    float dzerr;

    float pfiso04;  //2012 only available for electrons
    float pfiso03;  //2012 only available for electrons
    float relIso03DB; //ss
    float relIso03EA;
    float relIso04DB;

    float ip3d;
    float ip3derr;
    bool is_pfmu;

    //
    // lepton gen info
    //
    LorentzVector mcp4;
    int mcid;
    int mcstatus;
    int mcidx;
    int mc_motherid;
    int mc_motheridx;
    //
    // electron specific info
    //
    bool is_eleid_loose;
    bool is_eleid_medium;
    bool is_eleid_tight;
    float eoverpin; 
//    veci els_pfcands_idx;
 
    //
    // muon specific info
    //
    bool is_muoid_loose;
    bool is_muoid_tight;
  //  int mus_pfcands_idx;
    veci production_type;
};

#endif
