#ifndef JETUTIL_H
#define JETUTIL_H


#include "TMath.h"
#include <vector>
#include "Math/LorentzVector.h"
#include <math.h>

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

namespace JetUtil
{

  // comments, see .C file

  inline bool CompareLV(LorentzVector lv1, LorentzVector lv2);
  inline float DeltaPhi(float phi1, float phi2);
  inline float deltaPhi(LorentzVector jet1, LorentzVector jet2);
  inline float DeltaR(float phi1, float phi2, float eta1, float eta2);
  inline float deltaR(LorentzVector jet1, LorentzVector jet2);

  vector<LorentzVector > BJetSelector(vector<LorentzVector > jets, vector<float> btagvalues, float bjetdiscr=0.814, unsigned int minbjets=2, unsigned int minaddbjets=2, int versionAddjets=2);

}//end namespace 

#endif
