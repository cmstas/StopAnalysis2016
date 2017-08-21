#ifndef SR_h
#define SR_h

#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>

#include "TH1.h"

// class: SR [Stop Region]
// some more descriptions here...

class SR {

public:

  SR() : yield_(0) {}
  SR(std::string name) : yield_(0), srname_(name) {}
  SR(const SR& sr) = default;

  ~SR() {}

  void SetName(std::string sr_name);
  void SetVar(std::string var_name, float lower_bound, float upper_bound);
  void CheckNumOfVarsMatch(bool val);

  std::string GetName() const;
  unsigned int GetYield() const;
  float GetLowerBound(std::string var_name) const;
  float GetUpperBound(std::string var_name) const;
  unsigned int GetNumberOfVariables() const;
  std::vector<std::string> GetListOfVariables() const;

  bool PassesSelection(std::map<std::string, float> values);
  void RemoveVar(std::string var_name);
  void Clear();

  // used for plotting
  std::map<std::string, TH1*> histMap;

private:

  unsigned int yield_;
  std::string srname_;
  std::map<std::string,std::pair<float,float>> bins_;
  std::vector<std::string> defaultplots_;
  bool kAllowDummyVars_;

};


struct SRptrSet {
  std::vector<float> bins;
  std::vector<std::set<SR*>> sets;
};

// Helper Functions
std::map<std::string,SRptrSet> generateSRptrSet(const std::vector<SR*>& SRptrVec);

std::vector<SR*> findSatisfiedSRset(const std::map<std::string,float>& vars, const std::map<std::string,SRptrSet>& setsMap);


#endif
