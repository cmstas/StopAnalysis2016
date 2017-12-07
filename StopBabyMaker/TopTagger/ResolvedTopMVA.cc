/*
 * ResolvedTopMVA.cc
 *
 *  Created on: Oct 6, 2016
 *  Original author: hqu
 *  Modified on: Oct 23, 2017
 */

#include "ResolvedTopMVA.h"
#include "Math/VectorUtil.h"

using namespace tas;
using vecf = std::vector<float>;
using veci = std::vector<int>;

std::map<TString,float> ResolvedTopMVA::calcTopCandVars(const TopCand& topjet) {
  size_t ib = topjet.ib_;
  size_t ij2 = topjet.ij2_;
  size_t ij3 = topjet.ij3_;

  std::map<TString,float> vars;

  vars["var_b_pt"]         = p4vec->at(ib).pt();
  vars["var_b_mass"]       = p4vec->at(ib).mass();
  vars["var_b_csv"]        = csvvec->at(ib);
  // vars["var_b_ptD"]        = ptDvec->at(ib);
  // vars["var_b_axis1"]      = axis1vec->at(ib);
  // vars["var_b_mult"]       = multvec->at(ib);

  vars["var_j2_pt"]        = p4vec->at(ij2).pt();
  vars["var_j2_mass"]      = p4vec->at(ij2).mass();
  vars["var_j2_csv"]       = csvvec->at(ij2);
  vars["var_j2_cvsl"]      = cvslvec->at(ij2);
  vars["var_j2_ptD"]       = ptDvec->at(ij2);
  vars["var_j2_axis1"]     = axis1vec->at(ij2);
  vars["var_j2_mult"]      = multvec->at(ij2);

  vars["var_j3_pt"]        = p4vec->at(ij3).pt();
  vars["var_j3_mass"]      = p4vec->at(ij3).mass();
  vars["var_j3_csv"]       = csvvec->at(ij3);
  vars["var_j3_cvsl"]      = cvslvec->at(ij3);
  vars["var_j3_ptD"]       = ptDvec->at(ij3);
  vars["var_j3_axis1"]     = axis1vec->at(ij3);
  vars["var_j3_mult"]      = multvec->at(ij3);

  vars["var_topcand_mass"] = topjet.topcand.mass();
  vars["var_topcand_ptDR"] = topjet.topcand.pt() * ROOT::Math::VectorUtil::DeltaR(p4vec->at(ib), topjet.wcand);

  vars["var_wcand_mass"]   = topjet.wcand.mass();
  vars["var_wcand_deltaR"] = ROOT::Math::VectorUtil::DeltaR(p4vec->at(ij2), p4vec->at(ij3));
  vars["var_wcand_ptDR"]   = topjet.wcand.pt() * vars["var_wcand_deltaR"];

  vars["var_sd_0"]         = p4vec->at(ij3).pt() / (p4vec->at(ij2).pt() + p4vec->at(ij3).pt());
  vars["var_sd_n2"]        = vars.at("var_sd_0") / std::pow(vars.at("var_wcand_deltaR"), -2);

  vars["var_b_j2_mass"]    = (p4vec->at(ib) + p4vec->at(ij2)).mass();
  vars["var_b_j3_mass"]    = (p4vec->at(ib) + p4vec->at(ij3)).mass();

  // vars["var_b_qgl"]        = topcand->b->qgl();
  // vars["var_b_cvsb"]       = topcand->b->cvsb();
  // vars["var_b_axis2"]      = topcand->b->axis2();
  // vars["var_j2_cvsb"]      = topcand->j2->cvsb();
  // vars["var_j2_qgl"]       = topcand->j2->qgl();
  // vars["var_j2_axis2"]     = topcand->j2->axis2();
  // vars["var_j3_cvsb"]      = topcand->j3->cvsb();
  // vars["var_j3_qgl"]       = topcand->j3->qgl();
  // vars["var_j3_axis2"]     = topcand->j3->axis2();
  // vars["var_sd_n1p5"]      = vars.at("var_sd_0")/std::pow(vars.at("var_wcand_deltaR"), -1.5);
  // vars["var_topcand_pt"]   = topjet.topcand.pt();
  // vars["var_b_wcand_deltaR"] = DeltaR(p4vec->at(ib), wcand);
  // vars["var_wcand_pt"]     = topjet.wcand.pt();
  // vars["var_wcand_deltaR"] = PhysicsUtilities::deltaR(*topcand->j2, *topcand->j3);

  return vars;
}

ResolvedTopMVA::ResolvedTopMVA(TString weightfile, TString mvaname)
    : mvaReader(weightfile, mvaname)
{
  initTopMVA();
}

ResolvedTopMVA::~ResolvedTopMVA() {}

void ResolvedTopMVA::initTopMVA() {
  // variable order must match the order in XML file

  vars = {
    "var_b_mass",
    "var_b_csv",
    "var_j2_csv",
    "var_j2_cvsl",
    "var_j2_ptD",
    "var_j2_axis1",
    "var_j3_csv",
    "var_j3_cvsl",
    "var_j3_ptD",
    "var_j3_axis1",
    "var_topcand_mass",
    "var_topcand_ptDR",
    "var_wcand_mass",
    "var_wcand_ptDR",
    "var_b_j2_mass",
    "var_b_j3_mass",
    "var_sd_n2",

    // "var_j2_pt",
    // "var_j2_axis2",
    // "var_j3_pt",
    // "var_j3_axis2",
    // "var_b_pt",
    // "var_topcand_pt",
    // "var_b_wcand_deltaR",
    // "var_wcand_pt",
    // "var_wcand_deltaR",

    "var_j2_mult",
    "var_j3_mult",
  };

  mvaReader.addVariables(vars);

}

void ResolvedTopMVA::setJetVecPtrs(std::vector<LorentzVector>* in_p4vec, std::vector<float>* in_csvvec, std::vector<float>* in_cvslvec,
                                   std::vector<float>* in_ptDvec, std::vector<float>* in_axis1vec, std::vector<int>* in_multvec) {
  p4vec = in_p4vec;
  csvvec = in_csvvec;
  cvslvec = in_cvslvec;
  ptDvec = in_ptDvec;
  axis1vec = in_axis1vec;
  multvec = in_multvec;
}

std::vector<TopCand> ResolvedTopMVA::getTopCandidates(const double WP, const size_t max_ntopcand) {
  // need at least three jets to form a top
  if (p4vec->size() < 3) return std::vector<TopCand>();

  // sort jets by CSV
  std::vector<size_t> jetidx( p4vec->size() );
  std::iota(jetidx.begin(), jetidx.end(), 0);
  std::sort(jetidx.begin(), jetidx.end(), [&](size_t i, size_t j) { 
      return csvvec->at(i) > csvvec->at(j);
    });

  std::vector<TopCand> allCands;
  for (size_t ib = 0; ib < max_ntopcand; ++ib) {
    // if(csvJets.at(iB)->csv() < defaults::CSV_LOOSE) break; // b must pass CSVL
    for (size_t ij2 = 0; ij2 < jetidx.size()-1; ++ij2) {
      if (ij2 == ib) continue;
      for (size_t ij3 = ij2+1; ij3 < jetidx.size(); ++ij3) {
        if (ij3 == ib) continue;
        TopCand tmpCand(jetidx[ib], jetidx[ij2], jetidx[ij3], p4vec);
        if (tmpCand.passMassW() && tmpCand.passMassTop()) {
          auto varMap = calcTopCandVars(tmpCand);
          for (const auto &v: vars) {
            mvaReader.setValue(v, varMap.at(v));
          }
          tmpCand.disc = mvaReader.eval();
          allCands.push_back(tmpCand);
        }
      }
    }
  }

  auto cands = removeOverlap(allCands, WP);
  return cands;
}

std::vector<TopCand> ResolvedTopMVA::removeOverlap(std::vector<TopCand>& cands, double threshold) {
  std::sort(cands.begin(), cands.end(), [](const TopCand &a, const TopCand &b) { return a.disc > b.disc; });

  std::vector<TopCand> cleanedCands;
  for (const auto &c : cands) {
    if (c.disc < threshold) break;
    bool isOverlap = false;
    for (const auto &cleaned : cleanedCands) {
      if (c.overlaps(cleaned)) {
        isOverlap = true; break;
      }
    }
    if(!isOverlap) cleanedCands.push_back(c);
  }

  return cleanedCands;
}
