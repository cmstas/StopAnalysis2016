#ifndef TAUTREE_H
#define TAUTREE_H

#include <vector>
#include <string>
#include "Math/LorentzVector.h"
#include "TString.h"

class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<std::string> vecs;
typedef std::vector<TString>  vects;
typedef std::vector<int> veci;
typedef std::vector<bool> vecb;

class TauTree
{
public:
    TauTree ();
    virtual ~TauTree () {}

    void Reset ();
    void SetBranches (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon (int idx, float tau_pt_cut, float tau_eta_cut);

    vects tau_IDnames;
    vecLorentzVector tau_leadtrack_p4;
    vecLorentzVector tau_leadneutral_p4;
    vecLorentzVector tau_p4;
    std::vector<vecLorentzVector> tau_isocand_p4;
    std::vector<vecLorentzVector> tau_sigcand_p4;
    std::vector<vecd> tau_ID;
    vecd tau_passID;
    int ngoodtaus;
    vecd tau_againstMuonTight;
    vecd tau_againstElectronLoose;
    vecb tau_isVetoTau;
};

#endif
