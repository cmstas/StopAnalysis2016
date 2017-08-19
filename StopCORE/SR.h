#ifndef SR_h
#define SR_h

#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>

// #include "TH1.h"

class SR {

public:

  SR() {}
  SR(std::string s) : srName_(s) {}
  ~SR() {}

  void SetName(std::string sr_name);
  void SetVar(std::string var_name, float lower_bound, float upper_bound);
  void SetAllowingDummyVars(bool val);

  std::string GetName() const;

  float GetLowerBound(std::string var_name) const;
  float GetUpperBound(std::string var_name) const;
  unsigned int GetNumberOfVariables() const;
  std::vector<std::string> GetListOfVariables() const;

  bool PassesSelection(std::map<std::string, float> values) const;
  void RemoveVar(std::string var_name);
  void Clear();

  // used for plotting
  // std::map<std::string, TH1*> hists;

protected:

  std::string srName_;
  std::map<std::string,std::pair<float,float>> bins_;
  bool kAllowDummyVars_;

};


struct SRsets {
  std::vector<float> bins;
  std::vector<std::set<SR*>> sets;
};

// Helper Functions
std::map<std::string,SRsets> generateSRsets(const std::vector<SR>& SRvec);

std::vector<SR*> findSatisfiedSRset(const std::map<std::string,float>& vars, const std::map<std::string,SRsets>& setsMap);


#endif
