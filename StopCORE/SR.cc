#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>

#include "SR.h"


void SR::SetName(std::string sr_name) {
  srName_ = sr_name;
}

void SR::SetVar(std::string var_name, float lower_bound, float upper_bound) {
  bins_[var_name] = std::pair<float,float>(lower_bound, upper_bound);
}

void SR::SetAllowingDummyVars(bool val) {
  kAllowDummyVars_ = val;
}

std::string SR::GetName() const {
  return srName_;
}

float SR::GetLowerBound(std::string var_name) const {
  return (bins_.at(var_name)).first;
}

float SR::GetUpperBound(std::string var_name) const {
  return (bins_.at(var_name)).second;
}

unsigned int SR::GetNumberOfVariables() const {
  return (bins_.size());
}

std::vector<std::string> SR::GetListOfVariables() const {
  std::vector<std::string> vars;
  for(auto it = bins_.begin(); it != bins_.end(); ++it) {
    vars.push_back(it->first);
  }
  return vars;
}

bool SR::PassesSelection(std::map<std::string, float> values) const {
  float ep = 0.000001;
  if((kAllowDummyVars_)? GetNumberOfVariables() < values.size() : GetNumberOfVariables() != values.size()) {
    std::cout << "Number of variables to cut on != number of variables in signal region. Passed " << values.size() << ", expected " << GetNumberOfVariables() << std::endl;
    throw std::invalid_argument(srName_ + ": Number of variables to cut on != number of variables in signal region");
  }
  for(auto it = bins_.begin(); it != bins_.end(); it++) {
    if(values.find(it->first) != values.end()) { //check that we actually have bounds set for this variable
      float value = values[it->first];
      float cut_lower = (it->second).first;
      float cut_upper = (it->second).second;
      if(value < cut_lower) return false;
      if(( std::abs(cut_upper + 1.0) > ep ) && (value >= cut_upper)) return false;
    }
    else if(!kAllowDummyVars_) {
      throw std::invalid_argument("Cut variable " + it->first + " not found in values");
    }
  }
  return true;
}

void SR::RemoveVar(std::string var_name) {
  if(bins_.find(var_name) != bins_.end()) bins_.erase(var_name);
  else throw std::invalid_argument("Variable not added. Cannot remove!");
}

void SR::Clear() {
  srName_ = "";
  bins_.clear();
  kAllowDummyVars_ = false;
}


// --------------------------------------------------------------------------------
//                             Helper Functions                                   
// --------------------------------------------------------------------------------

std::map<std::string,SRsets> generateSRsets(const std::vector<SR>& SRvec)
{
  std::map<std::string,SRsets> var_to_SRset;
  std::map<std::string,std::set<std::tuple<float,float,SR*>>> master_map;

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
    std::set<float> edges; 
    for (auto vlist : it->second) {
      edges.insert(std::get<0>(vlist));
      edges.insert(std::get<1>(vlist));
    }
    
    if (edges.erase(-1)) edges.insert(std::numeric_limits<float>::max());
    std::vector<float> bins(edges.begin(),edges.end());
    std::vector<std::set<SR*>> srsets(edges.size()-1);

    auto ib = bins.begin(), ie = bins.end();
    // std::sort(ib, ie);
   
    for (auto vlist : it->second) {
      auto il = std::lower_bound(ib, ie, std::get<0>(vlist));
      auto ir = std::lower_bound(ib, ie, std::get<1>(vlist));
      for (; il != ir; ++il) {
        srsets[il-ib].insert(std::get<2>(vlist));
      }
    }
    var_to_SRset[it->first] = {bins, srsets};
  }

  return var_to_SRset;
}


std::vector<SR*> findSatisfiedSRset(const std::map<std::string,float>& vars, const std::map<std::string,SRsets>& setsMap)
{
  std::vector<SR*> srset;
  bool firstvar = true;

  for (const auto& v : vars) {
    std::string var = v.first;
    float value = v.second;

    auto set_pair = setsMap.find(var);
    if (set_pair == setsMap.end()) throw std::invalid_argument("Var " + var + " wasn't found required in any SR of the SRvec");
    auto iset = set_pair->second;

    auto ibin_b = iset.bins.begin(), ibin_e = iset.bins.end();
    auto ibin = std::upper_bound(ibin_b, ibin_e, value);
    if (ibin == ibin_b || ibin == ibin_e) continue;

    unsigned int i = ibin - ibin_b - 1;
    if (firstvar) {
      srset = std::vector<SR*>(iset.sets[i].begin(), iset.sets[i].end());
      firstvar = false;
    } else {
      auto ibegin = srset.begin();
      auto iend = std::set_intersection(ibegin, srset.end(), iset.sets[i].begin(), iset.sets[i].end(), ibegin);
      if (iend == ibegin) break;
      srset.resize(iend - ibegin);
    }
  }

  return srset;
}
