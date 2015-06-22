#include "TFitter.h"
#include "TMath.h"
#include <vector>
#include "Math/LorentzVector.h"
#include <math.h>
#include "TLorentzVector.h"
#include "JetUtil.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

// comments, see .C file

float topnessMinimization(TLorentzVector met, TLorentzVector lep, TLorentzVector bjet1, TLorentzVector bjet2, int version=1);

double topnessFunction(double pwx_, double pwy_, double pwz_, double pnz_,
                       double plx_, double ply_, double plz_, double ple_,
                       double pb1x_, double pb1y_, double pb1z_, double pb1e_,
                       double pb2x_, double pb2y_, double pb2z_, double pb2e_,
                       double pmx_, double pmy_, double pmz_, double pme_);

void minuitFunctionWrapper(int& nDim, double* gout, double& result, double* par, int flg) {
  result = topnessFunction(par[0],par[1],par[2],par[3],
                           par[4],par[5],par[6],par[7],
                           par[8],par[9],par[10],par[11],
                           par[12],par[13],par[14],par[15],
                           par[16],par[17],par[18],par[19]
                           );
}

double topnessFunctionV1(double pwx_, double pwy_, double pwz_, double pnz_,
                       double plx_, double ply_, double plz_, double ple_,
                       double pb1x_, double pb1y_, double pb1z_, double pb1e_,
                       double pb2x_, double pb2y_, double pb2z_, double pb2e_,
                       double pmx_, double pmy_, double pmz_, double pme_);

void minuitFunctionWrapperV1(int& nDim, double* gout, double& result, double* par, int flg) {
  result = topnessFunctionV1(par[0],par[1],par[2],par[3],
                           par[4],par[5],par[6],par[7],
                           par[8],par[9],par[10],par[11],
                           par[12],par[13],par[14],par[15],
                           par[16],par[17],par[18],par[19]
                           );
}


//float gettopness(TLorentzVector met, TLorentzVector lep, vector<TLorentzVector > bjets, int version=1);
//float Gettopness(LorentzVector met, LorentzVector lep, vector<LorentzVector > bjets, int version=1);
//float Gettopness_(float met, float metphi, LorentzVector lep, vector<LorentzVector> bjets, int version=1);

//float TopnessVersion(int version, LorentzVector MET, LorentzVector lep, vector<LorentzVector> jets, vector<float> jet_bdiscr, float btagdiscr=0.814, unsigned int addnjets=2, int addjets=2);
//float TopnessVersion_(int version, float met, float metphi, LorentzVector lep, vector<LorentzVector> jets, vector<float> jet_bdiscr, float btagdiscr=0.814, unsigned int addnjets=2, int addjets=2);

float CalcTopness( int version, LorentzVector MET,       LorentzVector lep, vector<LorentzVector> bjets,  vector<LorentzVector> addjets);
float CalcTopness_(int version, float MET, float METphi, LorentzVector lep, vector<LorentzVector> bjets,  vector<LorentzVector> addjets);
