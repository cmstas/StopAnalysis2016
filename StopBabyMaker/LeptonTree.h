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
enum prodType {fromW, fromZ, fromB, fromC, fromLight, fromLightFake, none};

class LeptonTree
{
public:
    LeptonTree ();
    LeptonTree (const std::string &prefix);
    virtual ~LeptonTree () {}

    void Reset ();
    void SetBranches (TTree* tree);
    void SetBranches_electronID(TTree* tree);
    void SetBranches_Iso(TTree* tree);
    void SetBranches_SynchTools (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon (int id, int idx);

protected:

    std::string prefix_;

public:    

    // lepton reco info
    LorentzVector p4;
    //LorentzVector pfp4;
    int pdgid;
    float pt;
    float eta;
    float phi;
    float mass; 
    int   charge;

    int isFrom;

    float d0;
    float d0err;
    float dz;
    float dzerr;

    float sigmaIEtaEta_fill5x5;
    float dEtaIn;
    float dPhiIn;
    float hOverE;
    float ooEmooP;
    int   expectedMissingInnerHits ;
    bool  conversionVeto;
    float etaSC ;
    float ChiSqr;
    float eoverpin; 

    float chiso;
    float nhiso;
    float emiso;
    float deltaBeta;

    //float pfiso04;  //2012 only available for electrons
    //float pfiso03;  //2012 only available for electrons
    float relIso03DB; //ss
    float relIso03EA;
    float relIso04DB;
    float miniRelIsoDB;
    float miniRelIsoEA;
    
    float MiniIso;
    float relIso;

    //
    // lepton gen info
    //
    LorentzVector mcp4;
    int mc_motherid;

    bool passVeto;    //currently contains miniIso
    bool passLooseID;
    bool passMediumID;//currently contains miniIso
    bool passTightID;

    bool is_lepid_loose_noiso;
    bool is_lepid_medium_noiso;
    bool is_lepid_tight_noiso;

  //  int mus_pfcands_idx;
    int production_type;
/*obsolete
    bool  is_mu;
    bool  is_el;
    int   type;
    float ip3d;
    float ip3derr;
    bool  is_pfmu;

    int mcstatus;
    int mcidx;
    int mc_motherid;
    int mc_motheridx;
    int mc3dr;
    int mc3id;
    int mc3idx;
    int mc3motherid;
    int mc3motheridx;

    // electron specific info
    //
    bool is_eleid_loose;
    bool is_eleid_medium;
    bool is_eleid_tight;
    bool is_phys14_loose_noIso;
    bool is_phys14_medium_noIso;
    bool is_phys14_tight_noIso;
    //veci els_pfcands_idx;
    //
    // muon specific info
    bool is_muoid_medium;
    bool is_muoid_loose;
    bool is_muoid_tight;
*/

    float dphiMET;
    float dphiMET_jup;
    float dphiMET_jdown;
    float dphiMET_rl;
    float dphiMET_rl_jup;
    float dphiMET_rl_jdown;


};

#endif
