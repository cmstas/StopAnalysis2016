#ifndef GENPARTICLETREE_H
#define GENPARTICLETREE_H

#include <vector>
#include <string>
#include "Math/LorentzVector.h"

class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<std::string> vecs;
typedef std::vector<int> veci;
typedef std::vector<bool> vecb;
enum TauDecay {NoTau, Lep_e, Lep_mu, Had_1prong, Had_3prong, other};

class GenParticleTree
{
public:
    GenParticleTree ();
    GenParticleTree (const std::string &prefix);
    virtual ~GenParticleTree () {}

    void Reset ();
    void SetBranches (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon (int idx);

protected:

    std::string prefix_;

public:
   
 	//commented out variables are available on CMS3 but not stored

	veci gentaudecay;
        //TauDecay gentaudecay;

	/*event level genps info
        float alphaQCD;
	float pthat;
	float qScale;
	float weight;
        unsigned int signalProcessID;*/

	vecLorentzVector p4;
        
//        LorentzVector prod_vtx;
  //      vecLorentzVector lepdaughter_p4;
        vecd charge;
	vecd iso;
	vecd mass;
	veci id;
	veci genpsidx;
        vecb isfromt;
//	veci id_simplegrandma;
//	veci id_simplemother;
//	veci idx_mother;
//	veci idx_simplemother;
	veci status;
	std::vector<veci> lepdaughter_id;
//	veci lepdaughter_idx;
        int gen_nfromt;
        vecLorentzVector motherp4;
        vecd mothercharge;
        veci motherid;
        veci motheridx;
        veci motherstatus;
};

#endif
