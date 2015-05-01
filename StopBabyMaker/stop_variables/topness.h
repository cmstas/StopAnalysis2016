#include "TFitter.h"
#include "TMath.h"
#include <vector>
#include "Math/LorentzVector.h"
#include <math.h>
#include "TLorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

float topnessMinimization(TLorentzVector lep, TLorentzVector bjet1, TLorentzVector bjet2, TLorentzVector met);

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


float gettopness(TLorentzVector lep, TLorentzVector met, vector<TLorentzVector > bjets);
float get_topness(TLorentzVector lep, float met, float metphi, vector<TLorentzVector > bjets);
float getTopness(TLorentzVector lep, TLorentzVector met, vector<TLorentzVector > jets, vector<float> jet_bdiscr, float btagdiscr=0.814);
float get_Topness(TLorentzVector lep, float met, float metphi, vector<TLorentzVector > jets, vector<float> jet_bdiscr, float btagdiscr=0.814);


float Gettopness(LorentzVector lep, LorentzVector met, vector<LorentzVector > bjets);
float Get_topness(LorentzVector lep, float met, float metphi, vector<LorentzVector > bjets);
float GetTopness(LorentzVector lep, LorentzVector met, vector<LorentzVector > jets, vector<float> jet_bdiscr, float btagdiscr=0.814);
float Get_Topness(LorentzVector lep, float met, float metphi, vector<LorentzVector > jets, vector<float> jet_bdiscr, float btagdiscr=0.814);

