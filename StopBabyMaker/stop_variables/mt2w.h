#include "mt2w_bisect.h"
#include <vector>
#include "Math/LorentzVector.h"
#include "TMath.h"
#include "JetUtil.h"

using namespace std;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

double calculateMT2w(vector<LorentzVector>& jets, vector<bool>& btag, LorentzVector& lep, float met, float metphi);
double mt2wWrapper(LorentzVector& lep, LorentzVector& jet_o, LorentzVector& jet_b, float met, float metphi);

//float CalculateMT2w_(vector<LorentzVector> jets, vector<float> btag, float btagdiscr, LorentzVector lep, float met, float metphi, unsigned int addnjets=3, int addjets=2);
//float CalculateMT2w( vector<LorentzVector> jets, vector<float> btag, float btagdiscr, LorentzVector lep, LorentzVector metlv,     unsigned int addnjets=3, int addjets=2);
//float CalculateMT2W_(vector<LorentzVector> bjet, LorentzVector lep, float met, float metphi);
//float CalculateMT2W (vector<LorentzVector> bjet, LorentzVector lep, LorentzVector metlv    );
float CalcMT2W( vector<LorentzVector> bjets, vector<LorentzVector> addjets,  LorentzVector lep, LorentzVector metlv    );
float CalcMT2W_(vector<LorentzVector> bjets, vector<LorentzVector> addjets,  LorentzVector lep, float met, float metphi);
