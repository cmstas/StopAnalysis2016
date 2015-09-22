#ifndef PHOTONTREE_H
#define PHOTONTREE_H

#include <string>
#include <vector>
#include "Math/LorentzVector.h"

// forward declaration
class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<std::string> vecs;
typedef std::vector<int> veci;
typedef std::vector<bool> vecb;

class PhotonTree
{
public:
    PhotonTree ();
    PhotonTree (const std::string &prefix);
    virtual ~PhotonTree () {}

    void Reset ();
    void SetBranches (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon ();
    int  genbestMatch(int idx);
    void SetPhotonSelection (float pt_cut,float eta);
protected:

    std::string prefix_;

public:    

    // photon reco info
    vecLorentzVector p4;

    vecd pt;
    vecd eta;
    vecd phi;
    vecd mass; 

    vecd sigmaIEtaEta_fill5x5;
    vecd hOverE;
    vecd r9;
    vecb idCutBased;
   
    vecd chiso;
    vecd nhiso;
    vecd phiso;

    veci overlapJetId;

    //
    // photon gen info
    //

    vecLorentzVector mcp4;
    veci mcMatchId;
    vecd genIso04; 
    vecd drMinParton;

private:

    float m_ph_pt_cut;
    float m_ph_eta_cut;
    
};

#endif
