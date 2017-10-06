#include "mt2w.h"

// 
//--------------------------------------------------------------------
// original 8 TeV function
double calculateMT2w(vector<LorentzVector>& jets, vector<bool>& btag, LorentzVector& lep, float met, float metphi){

    // I am asumming that jets is sorted by Pt
    assert ( jets.size() == btag.size() );
    // require at least 2 jets
    if ( jets.size()<2 ) return -999.; 

    // First we count the number of b-tagged jets, and separate those non b-tagged
    std::vector<int> bjets;
    std::vector<int> non_bjets;
    for( unsigned int i = 0 ; i < jets.size() ; i++ ){
        if( btag.at(i) ) {
            bjets.push_back(i);
        } else {
            non_bjets.push_back(i);
        }
    }	

    int n_btag = (int) bjets.size();
    //	cout << "n_btag = " << n_btag << endl;

    // We do different things depending on the number of b-tagged jets
    // arXiv:1203.4813 recipe

    int nMax=-1;
    if(jets.size()<=3) nMax=non_bjets.size();
    else nMax=3;

    if (n_btag == 0){                  //  0 b-tags
        // If no b-jets select the minimum of the mt2w from all combinations with 
        // the three leading jets
        float min_mt2w = 9999;

        for (int i=0; i<nMax; i++)
            for (int j=0; j<nMax; j++){
                if (i == j) continue;
                float c_mt2w = mt2wWrapper(lep, 
                        jets[non_bjets[i]],
                        jets[non_bjets[j]], met, metphi);
                if (c_mt2w < min_mt2w)
                    min_mt2w = c_mt2w;
            }
        return min_mt2w;

    } else if (n_btag == 1 ){          //  1 b-tags
        // if only one b-jet choose the three non-b leading jets and choose the smaller
        float min_mt2w = 9999;

        for (int i=0; i<nMax; i++){
            float c_mt2w = mt2wWrapper(lep, jets[bjets[0]], jets[non_bjets[i]], met, metphi);
            if (c_mt2w < min_mt2w)
                min_mt2w = c_mt2w;
        }
        for (int i=0; i<nMax; i++){
            float c_mt2w = mt2wWrapper(lep, jets[non_bjets[i]], jets[bjets[0]], met, metphi);
            if (c_mt2w < min_mt2w)
                min_mt2w = c_mt2w;
        }
        return min_mt2w;

    } else if (n_btag >= 2) {          // >=2 b-tags
        // if 3 or more b-jets the paper says ignore b-tag and do like 0-bjets 
        // but we are going to make the combinations with the b-jets
        float min_mt2w = 9999;
        for (int i=0; i<n_btag; i++)
            for (int j=0; j<n_btag; j++){
                if (i == j) continue;
                float c_mt2w = mt2wWrapper(lep, 
                        jets[bjets[i]],
                        jets[bjets[j]], met, metphi);
                if (c_mt2w < min_mt2w)
                    min_mt2w = c_mt2w;
            }
        return min_mt2w;
    }

    return -1.;
}

// This funcion is a wrapper for mt2w_bisect etc that takes LorentzVectors instead of doubles
// original 8 TeV function
double mt2wWrapper(LorentzVector& lep, LorentzVector& jet_o, LorentzVector& jet_b, float met, float metphi){

    // same for all MT2x variables
    double metx = met * cos( metphi );
    double mety = met * sin( metphi );

    double pl[4];     // Visible lepton
    double pb1[4];    // bottom on the same side as the visible lepton
    double pb2[4];    // other bottom, paired with the invisible W
    double pmiss[3];  // <unused>, pmx, pmy   missing pT

    int mydigit = 3;
    pl[0]    = JetUtil::round(lep.E(),   mydigit);
    pl[1]    = JetUtil::round(lep.Px(),  mydigit);
    pl[2]    = JetUtil::round(lep.Py(),  mydigit);
    pl[3]    = JetUtil::round(lep.Pz(),  mydigit);
    pb1[1]   = JetUtil::round(jet_o.Px(),mydigit);
    pb1[2]   = JetUtil::round(jet_o.Py(),mydigit);
    pb1[3]   = JetUtil::round(jet_o.Pz(),mydigit);
    pb2[1]   = JetUtil::round(jet_b.Px(),mydigit);
    pb2[2]   = JetUtil::round(jet_b.Py(),mydigit);
    pb2[3]   = JetUtil::round(jet_b.Pz(),mydigit);
    pmiss[0] = JetUtil::round(0.,        mydigit);
    pmiss[1] = JetUtil::round(metx,      mydigit);
    pmiss[2] = JetUtil::round(mety,      mydigit);

    pb1[0]   = JetUtil::round(jet_o.E(), mydigit);
    pb2[0]   = JetUtil::round(jet_b.E(), mydigit);

    mt2w_bisect::mt2w mt2w_event;
    mt2w_event.set_momenta(pl, pb1, pb2, pmiss);

    return mt2w_event.get_mt2w();
}

//new MT2W function (gives btag values, and has additional functionality) // deprecated
//allows for non-massive bjets (not tested)
//addnjets: if <2 b-jets, add non-bjets up to total addnjets 'b-jets' (default = 3, recommended = 1,2)
//addjets: ==1: add additional jets according to highest b-tag discriminant, ==2: add additional jets according to highest jet-pt
/*float CalculateMT2w_(vector<LorentzVector> jets, vector<float> btag, float btagdiscr, LorentzVector lep, float met, float metphi, unsigned int addnjets, int addjets){

  if(jets.size()!=btag.size()) return -99.;
  vector<LorentzVector> bjet = JetUtil::BJetSelector(jets,btag,btagdiscr,2,addnjets,addjets);
  if(bjet.size()<2) return -999.;
  float min_mt2w = 9999;
  for (unsigned int i=0; i<bjet.size(); ++i){
    for (unsigned int j=0; j<bjet.size(); ++j){
      if (i == j) continue;
      float c_mt2w = mt2wWrapper(lep, bjet[i], bjet[j], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
    }
  }
  return min_mt2w;
}*/

//new MT2W function (gives btag values, and has additional functionality) // deprecated
//see CalculateMT2w_
//uses LorentzVector for MET
/*float CalculateMT2w(vector<LorentzVector> jets, vector<float> btag, float btagdiscr, LorentzVector lep, LorentzVector metlv, unsigned int addnjets, int addjets){
  float met = metlv.Pt();
  float metphi = metlv.Phi();
  return CalculateMT2w_(jets,btag,btagdiscr,lep,met,metphi,addnjets,addjets);
}*/

//new MT2W function (give directly bjets, and has additional functionality) // deprecated
//allows for non-massive bjets (not tested)
/*float CalculateMT2W_(vector<LorentzVector> bjet, LorentzVector lep, float met, float metphi){
  if(bjet.size()<2) return -999.;
  float min_mt2w = 9999;
  for (unsigned int i=0; i<bjet.size(); ++i){
    for (unsigned int j=0; j<bjet.size(); ++j){
      if (i == j) continue;
      float c_mt2w = mt2wWrapper(lep, bjet[i], bjet[j], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
    }
  }
  return min_mt2w;
}*/

//new MT2W function (give directly bjets, and has additional functionality) // deprecated
//see CalculateMT2W_
//uses LorentzVector for MET
/*float CalculateMT2W(vector<LorentzVector> bjet, LorentzVector lep, LorentzVector metlv){
  float met = metlv.Pt();
  float metphi = metlv.Phi();
  return CalculateMT2W_(bjet,lep,met,metphi);
}*/

// 13 TeV implementation - full calculation needs JetUtil b-discriminator ordering, see looper
float CalcMT2W(vector<LorentzVector> bjets, vector<LorentzVector> addjets,  LorentzVector lep, LorentzVector metlv){
  float met = metlv.Pt();
  float metphi = metlv.Phi();
  return CalcMT2W_(bjets,addjets,lep,met,metphi);
}

// 13 TeV implementation - full calculation needs JetUtil b-discriminator ordering, see looper
float CalcMT2W_(vector<LorentzVector> bjets, vector<LorentzVector> addjets,  LorentzVector lep, float met, float metphi){
  if((bjets.size()+addjets.size())<2) return -999.;
  float min_mt2w = 9999;
  for (unsigned int i=0; i<bjets.size(); ++i){
    for (unsigned int j=i+1; j<bjets.size(); ++j){
      float c_mt2w = mt2wWrapper(lep, bjets[i], bjets[j], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
      //cout << "MT2W " << c_mt2w << " for b1 " << bjets[i].Pt() << " and b2 " << bjets[j].Pt() << endl;
      c_mt2w = mt2wWrapper(lep, bjets[j], bjets[i], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
      //cout << "MT2W " << c_mt2w << " for b1 " << bjets[j].Pt() << " and b2 " << bjets[i].Pt() << endl;
    }
    for (unsigned int j=0; j<addjets.size(); ++j){
      float c_mt2w = mt2wWrapper(lep, bjets[i], addjets[j], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
      //cout << "MT2W " << c_mt2w << " for b1 " << bjets[i].Pt() << " and a2 " << addjets[j].Pt() << endl;
      c_mt2w = mt2wWrapper(lep, addjets[j], bjets[i], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
      //cout << "MT2W " << c_mt2w << " for a1 " << addjets[j].Pt() << " and b2 " << bjets[i].Pt() << endl;
    }
  }
  if(bjets.size()==0){
    for (unsigned int j=1; j<addjets.size(); ++j){
      float c_mt2w = mt2wWrapper(lep, addjets[0], addjets[j], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
      c_mt2w = mt2wWrapper(lep, addjets[j], addjets[0], met, metphi);
      if (c_mt2w < min_mt2w)  min_mt2w = c_mt2w;
    }
  }
  return min_mt2w;
}
