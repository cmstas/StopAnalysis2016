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
	vecLorentzVector p4;
        
	veci id;
	veci genpsidx;
        vecb isfromt;
	veci status;
	vecb fromHardProcessDecayed;
	vecb fromHardProcessFinalState;
	vecb isHardProcess;
	vecb isLastCopy;
	int gen_nfromt;
        vecLorentzVector motherp4;
        veci motherid;
        veci motheridx;
        veci motherstatus;
	vecLorentzVector gmotherp4;
	veci gmotherid;
        veci gmotheridx;
	veci gmotherstatus;

// obsolete branches //
        //TauDecay gentaudecay;

        /*event level genps info
        float alphaQCD;
        float pthat;
        float qScale;
        float weight;
        unsigned int signalProcessID;*/
        //LorentzVector prod_vtx;
        //vecLorentzVector lepdaughter_p4;
        //vecd charge;
        //vecd iso;
        //vecd mass;
        //vecb fromHardProcessBeforeFSR;
        //vecb isDirectHardProcessTauDecayProductFinalState;
        //vecb isDirectPromptTauDecayProductFinalState;
        //vecb isLastCopyBeforeFSR;
        //vecb isMostlyLikePythia6Status3;
        //vecb isPromptDecayed;
        //vecb isPromptFinalState;
        //std::vector<veci> lepdaughter_id;
        //vecd mothercharge;
        //veci gmothercharge;
        //TauDecay gentaudecay;

	//vecLorentzVector simplemotherp4;
	////veci simplemothercharge;
	//veci simplemotherid;
	//veci simplemotheridx;
	//veci simplemotherstatus;
	//vecLorentzVector simplegmotherp4;
	////veci simplegmothercharge;
	//veci simplegmotherid;
	//veci simplegmotheridx;
	//veci simplegmotherstatus;

};

#endif
