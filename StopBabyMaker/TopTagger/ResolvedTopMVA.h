/*
 * ResolvedTopMVA.h
 *
 *  Created on: Oct 6, 2016
 *  Original author: hqu
 *  Modified on: Oct 23, 2017
 */

#ifndef STOPBABYMAKER_TOPTAGGER_RESOLVEDTOPMVA_H
#define STOPBABYMAKER_TOPTAGGER_RESOLVEDTOPMVA_H

#include "CMS3.h"
#include "TMVAReader.h"

class TopCand {
 public:
  TopCand() = delete;
  TopCand(const size_t inb, const size_t inj2, const size_t inj3, const std::vector<LorentzVector>* jetp4vec)
      : disc(-1), ib_(inb), ij2_(inj2), ij3_(inj3)
  {
    wcand = jetp4vec->at(ij2_) + jetp4vec->at(ij3_);
    topcand = jetp4vec->at(ib_) + wcand;
  }

  int getIdxForb()  const { return ib_; }
  int getIdxForj2() const { return ij2_; }
  int getIdxForj3() const { return ij3_; }

  bool passMassW(double range=40)   const { return std::abs(wcand.mass()-80)    <= range; }
  bool passMassTop(double range=80) const { return std::abs(topcand.mass()-175) <= range; }
  bool sameAs(const TopCand &c) const { return ib_==c.ib_ && ij2_==c.ij2_ && ij3_==c.ij3_; }
  bool overlaps(const TopCand &c) const {
    return (ib_==c.ib_ || ib_==c.ij2_ || ib_==c.ij3_ || ij2_==c.ib_ || ij2_==c.ij2_ ||
            ij2_==c.ij3_ || ij3_==c.ib_ || ij3_==c.ij2_ || ij3_==c.ij3_);
  }

  LorentzVector wcand;
  LorentzVector topcand;
  double disc;

  friend class ResolvedTopMVA;

 private:
  size_t ib_;
  size_t ij2_;
  size_t ij3_;

};

class ResolvedTopMVA {
 public:
  ResolvedTopMVA(TString weightfile, TString mvaname);
  virtual ~ResolvedTopMVA();

  static constexpr double WP_ALL    = -1.0; // used for candidate studies
  static constexpr double WP_LOOSE  = 0.83;
  static constexpr double WP_MEDIUM = 0.98;
  static constexpr double WP_TIGHT  = 0.99;

  std::map<TString,float> calcTopCandVars(const TopCand& topjet);
  std::vector<TopCand> getTopCandidates(const double WP = WP_TIGHT, const size_t max_ntopcand = 2);

  void setJetVecPtrs(std::vector<LorentzVector>* p4vec, std::vector<float>* csvvec, std::vector<float>* cvslvec,
                     std::vector<float>* ptDvec, std::vector<float>* axis1vec, std::vector<int>* multvec);

  std::vector<LorentzVector>* p4vec;
  std::vector<float>* csvvec;
  std::vector<float>* cvslvec;
  std::vector<float>* ptDvec;
  std::vector<float>* axis1vec;
  std::vector<int>* multvec;

 private:
  void initTopMVA();
  std::vector<TopCand> removeOverlap(std::vector<TopCand> &cands, double threshold);

  TMVAReader mvaReader;
  std::vector<TString> vars;

};

#endif /* STOPBABYMAKER_TOPTAGGER_RESOLVEDTOPMVA_H */
