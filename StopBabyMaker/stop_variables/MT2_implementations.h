#include "Davismt2.h"
#include "TMath.h"
#include <vector>
#include "Math/LorentzVector.h"
#include <math.h>
#include "JetUtil.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

//for comments see .C

//Use LorentzVector
float CalcMT2(LorentzVector MET, LorentzVector visible1, LorentzVector visible2, bool massive=false, float testmass=0);
//float MT2_b_b(   LorentzVector MET, vector<LorentzVector> bjet, bool massive=false, float testmass=0);
//float MT2_lb_b(  LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, bool massive=false, float testmass=0);
//float MT2_lb_bq( LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive=false, float testmass=0);
//float MT2_lb_bqq(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive=false, float testmass=0);
//float MT2version(int version, LorentzVector MET, LorentzVector lep, vector<LorentzVector> jets, vector<float> btagdiscr, float btagvalue=0.814, float testmass=0, bool massive=false, unsigned int addnjets=2, int addjets=2);
//float MT2Version(int version, LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jets, float testmass=0, bool massive=false);

//MET as MET and METPhi
float CalcMT2_(float MET, float METPhi, LorentzVector visible1, LorentzVector visible2, bool massive=false, float testmass=0);
//float MT2_b_b_(   float MET, float METPhi, vector<LorentzVector> bjet, bool massive=false, float testmass=0);
//float MT2_lb_b_(  float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, bool massive=false, float testmass=0);
//float MT2_lb_bq_( float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive=false, float testmass=0);
//float MT2_lb_bqq_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive=false, float testmass=0);
//float MT2version_(int version, float MET, float METPhi, LorentzVector lep, vector<LorentzVector> jets, vector<float> btagdiscr, float btagvalue=0.814, float testmass=0, bool massive=false, unsigned int addnjets=2, int addjets=2);
//float MT2Version_(int version, float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jets, float testmass=0, bool massive=false);

float CalcMT2_b_b(   LorentzVector MET, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass=0, bool massive=true);
float CalcMT2_lb_b(  LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass=0, bool massive=true);
float CalcMT2_lb_bq( LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass=0, bool massive=true);
float CalcMT2_lb_bqq(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass=0, bool massive=true);
float CalcMT2_b_b_(   float MET, float METPhi, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass=0, bool massive=true);
float CalcMT2_lb_b_(  float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass=0, bool massive=true);
float CalcMT2_lb_bq_( float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass=0, bool massive=true);
float CalcMT2_lb_bqq_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass=0, bool massive=true);
