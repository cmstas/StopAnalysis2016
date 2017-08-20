#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "SR.h"

using namespace std;

void SR::SetName(string sr_name) {
  srName_ = sr_name;
}

void SR::SetVar(string var_name, float lower_bound, float upper_bound) {
  bins_[var_name] = pair<float,float>(lower_bound, upper_bound);
}

void SR::SetAllowingDummyVars(bool val) {
  kAllowDummyVars_ = val;
}

string SR::GetName() const {
  return srName_;
}

float SR::GetLowerBound(string var_name) const {
  return (bins_.at(var_name)).first;
}

float SR::GetUpperBound(string var_name) const {
  return (bins_.at(var_name)).second;
}

unsigned int SR::GetNumberOfVariables() const {
  return (bins_.size());
}

vector<string> SR::GetListOfVariables() const {
  vector<string> vars;
  for(auto it = bins_.begin(); it != bins_.end(); ++it) {
    vars.push_back(it->first);
  }
  return vars;
}

bool SR::PassesSelection(map<string, float> values) const {
  float ep = 0.000001;
  if((kAllowDummyVars_)? GetNumberOfVariables() < values.size() : GetNumberOfVariables() != values.size()) {
    cout << "Number of variables to cut on != number of variables in signal region. Passed " << values.size() << ", expected " << GetNumberOfVariables() << endl;
    throw invalid_argument(srName_ + ": Number of variables to cut on != number of variables in signal region");
  }
  for(auto it = bins_.begin(); it != bins_.end(); it++) {
    if(values.find(it->first) != values.end()) { //check that we actually have bounds set for this variable
      float value = values[it->first];
      float cut_lower = (it->second).first;
      float cut_upper = (it->second).second;
      if (value < cut_lower) return false;
      if (( abs(cut_upper + 1.0) > ep ) && (value >= cut_upper)) return false;
    }
    else if(!kAllowDummyVars_) {
      throw invalid_argument("Cut variable " + it->first + " not found in values");
    }
  }
  return true;
}

void SR::RemoveVar(string var_name) {
  if(bins_.find(var_name) != bins_.end()) bins_.erase(var_name);
  else throw invalid_argument("Variable not added. Cannot remove!");
}

void SR::Clear() {
  srName_ = "";
  bins_.clear();
  kAllowDummyVars_ = false;
}


// --------------------------------------------------------------------------------
//                             Helper Functions                                   
// --------------------------------------------------------------------------------

map<string,SRsets> generateSRsets(const vector<SR>& SRvec)
{
  map<string,SRsets> var_to_SRset;
  map<string,set<tuple<float,float,SR*>>> master_map;

  for (const auto& sr : SRvec) {
    auto varlist = sr.GetListOfVariables();
    for (auto& var : varlist) {
      float lower = sr.GetLowerBound(var), upper = sr.GetUpperBound(var);
      if (!master_map.count(var))
        master_map[var] = { {lower, upper, (SR*) &sr} };
      else 
        master_map[var].emplace(lower, upper, (SR*) &sr);
    }
  }

  for (auto it = master_map.begin(); it != master_map.end(); ++it) {
    set<float> edges; 
    for (auto vlist : it->second) {
      edges.insert(get<0>(vlist));
      edges.insert(get<1>(vlist));
    }
    
    if (edges.erase(-1)) edges.insert(numeric_limits<float>::max());
    vector<float> bins(edges.begin(),edges.end());
    vector<set<SR*>> srsets(edges.size()-1);

    auto ib = bins.begin(), ie = bins.end();
    // sort(ib, ie);
   
    for (auto vlist : it->second) {
      auto il = lower_bound(ib, ie, get<0>(vlist));
      auto ir = lower_bound(ib, ie, get<1>(vlist));
      for (; il != ir; ++il) {
        srsets[il-ib].insert(get<2>(vlist));
      }
    }
    var_to_SRset[it->first] = {bins, srsets};
  }

  return var_to_SRset;
}


vector<SR*> findSatisfiedSRset(const map<string,float>& vars, const map<string,SRsets>& setsMap)
{
  vector<SR*> srset;
  bool firstvar = true;

  for (const auto& v : vars) {
    string var = v.first;
    float value = v.second;

    auto set_pair = setsMap.find(var);
    if (set_pair == setsMap.end()) throw std::invalid_argument("Var " + var + " wasn't found required in any SR of the SRvec");
    auto iset = set_pair->second;

    auto ibin_b = iset.bins.begin(), ibin_e = iset.bins.end();
    auto ibin = upper_bound(ibin_b, ibin_e, value);
    if (ibin == ibin_b || ibin == ibin_e) continue;

    unsigned int i = ibin - ibin_b - 1;
    if (firstvar) {
      srset = vector<SR*>(iset.sets[i].begin(), iset.sets[i].end());
      firstvar = false;
    } else {
      auto ibegin = srset.begin();
      auto iend = set_intersection(ibegin, srset.end(), iset.sets[i].begin(), iset.sets[i].end(), ibegin);
      if (iend == ibegin) break;
      srset.resize(iend - ibegin);
    }
  }

  return srset;
}
