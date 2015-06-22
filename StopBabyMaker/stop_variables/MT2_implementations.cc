#include "MT2_implementations.h"

//function to compute MT2, given Math::LorentzVectors
//massive: if false force E = p, or M = 0 (default = false)
//testmass: mass for LSP (default = 0)
//note: verbose set to -1, to suppress warnings for the so-called 'unbalanced' solutions
float CalcMT2(LorentzVector MET, LorentzVector visible1, LorentzVector visible2, bool massive, float testmass){
  
  double pa[3];
  double pb[3];
  double pmiss[3];
  
  pmiss[0] = 0;
  pmiss[1] = static_cast<double> (MET.Px());
  pmiss[2] = static_cast<double> (MET.Py());
  
  pa[0]    = static_cast<double> (massive ? visible1.M() : 0);
  pa[1]    = static_cast<double> (visible1.Px());
  pa[2]    = static_cast<double> (visible1.Py());
  
  pb[0]    = static_cast<double> (massive ? visible2.M() : 0);
  pb[1]    = static_cast<double> (visible2.Px());
  pb[2]    = static_cast<double> (visible2.Py());

  int mydigit = 3;
  pmiss[0] = JetUtil::round(pmiss[0],mydigit);
  pmiss[1] = JetUtil::round(pmiss[1],mydigit);
  pmiss[2] = JetUtil::round(pmiss[1],mydigit);
  pa[0]    = JetUtil::round(pa[0],   mydigit);
  pa[1]    = JetUtil::round(pa[1],   mydigit);
  pa[2]    = JetUtil::round(pa[2],   mydigit);
  pb[0]    = JetUtil::round(pb[0],   mydigit);
  pb[1]    = JetUtil::round(pb[1],   mydigit);
  pb[2]    = JetUtil::round(pb[2],   mydigit);
  
  Davismt2 *mt2 = new Davismt2();
  mt2->set_verbose(-1);
  mt2->set_momenta(pa, pb, pmiss);
  mt2->set_mn(testmass);
  float MT2=mt2->get_mt2();
  delete mt2;
  return MT2;

}

//function to compute MT2, given Math::LorentzVectors, but MET given in Pt,Phi
float CalcMT2_(float MET, float METPhi, LorentzVector visible1, LorentzVector visible2, bool massive, float testmass){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return CalcMT2(metlv,visible1,visible2,massive,testmass);
}

//helper function to get MT2(b,b) [without lepton in MET] - deprecated
//takes minimum MT2 function looping through all bjets
//massive (default = false), testmass (default = 0)
/*float MT2_b_b(LorentzVector MET, vector<LorentzVector> bjet, bool massive, float testmass){
  float MT2 = 99999;
  if(bjet.size()<2) {
    cout << "You have " << bjet.size() << " bjets, however need at least two. return -999.99" << endl;
    return -999.99;
  }
  for(unsigned int i = 0; i<bjet.size(); ++i){
    for(unsigned int j = 0; j<bjet.size(); ++j){
      if(j==i) continue;
      float tMT2 = CalcMT2(MET,bjet[i],bjet[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
  }
  return MT2;
}*/

//see MT2_b_b, MET given with Pt,Phi - deprecated
//massive (default = false), testmass (default = 0)
/*float MT2_b_b_(float MET, float METPhi, vector<LorentzVector> bjet, bool massive, float testmass){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return MT2_b_b(metlv,bjet,massive,testmass);
}*/

//helper function to get MT2(lb,b) - deprecated
//takes minimum MT2 function looping through all bjets
//massive (default = false), testmass (default = 0)
/*float MT2_lb_b(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, bool massive, float testmass){
  float MT2 = 99999;
  if(bjet.size()<2) {
    cout << "You have " << bjet.size() << " bjets, however need at least two. return -999.99" << endl;
    return -999.99;
  }  for(unsigned int i = 0; i<bjet.size(); ++i){
    for(unsigned int j = 0; j<bjet.size(); ++j){
      if(j==i) continue;
      float tMT2 = CalcMT2(MET,lep+bjet[i],bjet[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
  }
  return MT2;
}*/

//see MT2_lb_b, MET given with Pt,Phi - deprecated
//massive (default = false), testmass (default = 0)
/*float MT2_lb_b_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, bool massive, float testmass){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return MT2_lb_b(metlv,lep,bjet,massive,testmass);
}*/

//helper function to get MT2(lb,bq) - deprecated
//takes minimum MT2 function looping through all bjets and jets
//note: function assumes that bjets are subset of jets
//massive (default = false), testmass (default = 0)
/*float MT2_lb_bq(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive, float testmass){
  float MT2 = 99999;
  if(bjet.size()<2) {
    cout << "You have " << bjet.size() << " bjets, however need at least two. return -999.99" << endl;
    return -999.99;
  }
  if(jet.size()<3){
    //cout << "You have " << jet.size() << " jets, however need at least three. Note, that 'bjet' should be subset of 'jet'. return -9999.99" << endl;
    return -99.99 - 100.*jet.size();
  }
  for(unsigned int i = 0; i<bjet.size(); ++i){
    for(unsigned int j = 0; j<bjet.size(); ++j){
      if(j==i) continue;
      for(unsigned int k = 0; k<jet.size(); ++k){
	if(JetUtil::CompareLV(bjet[i],jet[k])==true) continue;
	if(JetUtil::CompareLV(bjet[j],jet[k])==true) continue;
	float tMT2 = CalcMT2(MET,lep+bjet[i],bjet[j]+jet[k],massive,testmass);
	if(tMT2<MT2) MT2 = tMT2;
      }
    }
  }
  return MT2;
}*/

//see MT2_lb_bq, MET given with Pt,Phi - deprecated
//massive (default = false), testmass (default = 0)
/*float MT2_lb_bq_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive, float testmass){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return MT2_lb_bq(metlv,lep,bjet,jet,massive,testmass);
}*/

//helper function to get MT2(lb,bqq) - deprecated
//takes minimum MT2 function looping through all bjets and jets
//note: function assumes that bjets are subset of jets
//massive (default = false), testmass (default = 0)
/*float MT2_lb_bqq(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive, float testmass){
  float MT2 = 99999;
  if(bjet.size()<2) {
    //cout << "You have " << bjet.size() << " bjets, however need at least two. return -999.99" << endl;
    return -999.99;
  }
  if(jet.size()<4){
    //cout << "You have " << jet.size() << " jets, however need at least four. Note, that 'bjet' should be subset of 'jet'. return -9999.99" << endl;
    return -99.99 - 100.*jet.size();
  }
  for(unsigned int i = 0; i<bjet.size(); ++i){
    for(unsigned int j = 0; j<bjet.size(); ++j){
      if(j==i) continue;
      for(unsigned int k = 0; k<jet.size(); ++k){
	if(JetUtil::CompareLV(bjet[i],jet[k])==true) continue;
	if(JetUtil::CompareLV(bjet[j],jet[k])==true) continue;
	for(unsigned int l = 0; l<jet.size(); ++l){
	  if(l==k) continue;
	  if(JetUtil::CompareLV(bjet[i],jet[l])==true) continue;
	  if(JetUtil::CompareLV(bjet[j],jet[l])==true) continue;
	  float tMT2 = CalcMT2(MET,lep+bjet[i],bjet[j]+jet[k]+jet[l],massive,testmass);
	  if(tMT2<MT2) MT2 = tMT2;
	}
      }
    }
  }
  return MT2;
}*/

//see MT2_lb_bqq, MET given with Pt,Phi - deprecated
//massive (default = false), testmass (default = 0)
/*float MT2_lb_bqq_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jet, bool massive, float testmass){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return MT2_lb_bqq(metlv,lep,bjet,jet,massive,testmass);
}*/

//wrapper function to get any MT2 (calls specific function) - deprecated
//version: ==1: MT2(b,b); ==2: MT2(lb,b); ==3: MT2(lb,bq); ==4: MT2(lb,bqq)
//massive (default = false), testmass (default = 0)
//addnjets: if <2 bjets found, add jets until addnjets(jets) are reached, unless addnjets<N(jets) (default = 2, recommended = 2,3)
//addjets: = 1: according to highest b-tag discriminator value; = 2: according to highest jet pT
/*float MT2version(int version, LorentzVector MET, LorentzVector lep, vector<LorentzVector> jets, vector<float> btagdiscr, float btagvalue, float testmass, bool massive, unsigned int addnjets, int addjets){
  if(jets.size()!=btagdiscr.size() ) {
    cout << "the vectors jets("<<jets.size()<<") and jet_bdiscr("<<btagdiscr.size()<<") have different lengths, please fix. return -99" << endl;
    return -99;
  }

  vector<LorentzVector> bjet = JetUtil::BJetSelector(jets,btagdiscr,btagvalue,2,addnjets,addjets);

  if(version==1) return MT2_b_b(MET,bjet,massive,testmass);
  if(version==2) return MT2_lb_b(MET,lep,bjet,massive,testmass);
  if(version==3) return MT2_lb_bq(MET,lep,bjet,jets,massive,testmass);
  if(version==4) return MT2_lb_bqq(MET,lep,bjet,jets,massive,testmass);
  return -5;
}*/

//wrapper function to get any MT2 - deprecated
//see MT2version, with MET given by Pt,Phi
/*float MT2version_(int version, float MET, float METPhi, LorentzVector lep, vector<LorentzVector> jets, vector<float> btagdiscr, float btagvalue, float testmass, bool massive, unsigned int addnjets, int addjets){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return MT2version(version,metlv,lep,jets,btagdiscr,btagvalue,testmass,massive,addnjets,addjets);
}*/

//wrapper function to get any MT2 - deprecated
//bjet selection already given
//version: ==1: MT2(b,b); ==2: MT2(lb,b); ==3: MT2(lb,bq); ==4: MT2(lb,bqq)
//massive (default = false), testmass (default = 0)
/*float MT2Version(int version, LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jets, float testmass, bool massive){
  if(version==1) return MT2_b_b(MET,bjet,massive,testmass);
  if(version==2) return MT2_lb_b(MET,lep,bjet,massive,testmass);
  if(version==3) return MT2_lb_bq(MET,lep,bjet,jets,massive,testmass);
  if(version==4) return MT2_lb_bqq(MET,lep,bjet,jets,massive,testmass);
  return -5;
}*/

//wrapper function to get any MT2 - deprecated
//see MT2Version, MET given by Pt,Phi
/*float MT2Version_(int version, float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjet, vector<LorentzVector> jets, float testmass, bool massive){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return MT2Version(version,metlv,lep,bjet,jets,testmass,massive);
}*/

float CalcMT2_b_b(LorentzVector MET, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass, bool massive){
  if(bjets.size()+addjets.size()<2) return -999.99;
  float MT2 = 99999;
  for(unsigned int i = 0; i<bjets.size(); ++i){
    for(unsigned int j = i+1; j<bjets.size(); ++j){
      float tMT2 = CalcMT2(MET,bjets[i],bjets[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
    for(unsigned int j = 0; j<addjets.size(); ++j){
      float tMT2 = CalcMT2(MET,bjets[i],addjets[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
  }
  if(bjets.size()==0){
    for(unsigned int j = 1; j<addjets.size(); ++j){
      float tMT2 = CalcMT2(MET,addjets[0],addjets[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
  }
  return MT2;
}
float CalcMT2_b_b_(float MET, float METPhi, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass, bool massive){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return CalcMT2_b_b(metlv, bjets, addjets, testmass, massive);
}

float CalcMT2_lb_b(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass, bool massive){
  if(bjets.size()+addjets.size()<2) return -999.99;
  float MT2 = 99999;
  for(unsigned int i = 0; i<bjets.size(); ++i){
    for(unsigned int j = i+1; j<bjets.size(); ++j){
      float tMT2 = CalcMT2(MET,bjets[i]+lep,bjets[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
      tMT2 = CalcMT2(MET,bjets[j]+lep,bjets[i],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
    for(unsigned int j = 0; j<addjets.size(); ++j){
      float tMT2 = CalcMT2(MET,bjets[i]+lep,addjets[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
      tMT2 = CalcMT2(MET,addjets[j]+lep,bjets[i],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
  }
  if(bjets.size()==0){
    for(unsigned int j = 1; j<addjets.size(); ++j){
      float tMT2 = CalcMT2(MET,addjets[0]+lep,addjets[j],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
      tMT2 = CalcMT2(MET,addjets[j]+lep,addjets[0],massive,testmass);
      if(tMT2<MT2) MT2 = tMT2;
    }
  }
  return MT2;
}
float CalcMT2_lb_b_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, float testmass, bool massive){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return CalcMT2_lb_b(metlv, lep, bjets, addjets, testmass, massive);
}

float CalcMT2_lb_bq(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass, bool massive){
  if(bjets.size()+addjets.size()<2) return -999.99;
  if(jets.size()<3) return -199.99*jets.size();
  float MT2 = 99999;
  for(unsigned int i = 0; i<bjets.size(); ++i){
    for(unsigned int j = i+1; j<bjets.size(); ++j){
      for(unsigned int k = 0; k<jets.size(); ++k){
	if(JetUtil::CompareLV(bjets[i],jets[k])==true) continue;
	if(JetUtil::CompareLV(bjets[j],jets[k])==true) continue;
	float tMT2 = CalcMT2(MET,lep+bjets[i],bjets[j]+jets[k],massive,testmass);
	if(tMT2<MT2) MT2 = tMT2;
	tMT2 = CalcMT2(MET,lep+bjets[j],bjets[i]+jets[k],massive,testmass);
	if(tMT2<MT2) MT2 = tMT2;
      }
    }
    for(unsigned int j = 0; j<addjets.size(); ++j){
      for(unsigned int k = 0; k<jets.size(); ++k){
	if(JetUtil::CompareLV(bjets[i],jets[k])==true) continue;
	if(JetUtil::CompareLV(addjets[j],jets[k])==true) continue;
	float tMT2 = CalcMT2(MET,lep+bjets[i],addjets[j]+jets[k],massive,testmass);
	if(tMT2<MT2) MT2 = tMT2;
	tMT2 = CalcMT2(MET,lep+addjets[j],bjets[i]+jets[k],massive,testmass);
	if(tMT2<MT2) MT2 = tMT2;
      }
    }
  }
  if(bjets.size()==0){
    for(unsigned int j = 1; j<addjets.size(); ++j){
      for(unsigned int k = 0; k<jets.size(); ++k){
	if(JetUtil::CompareLV(addjets[0],jets[k])==true) continue;
	if(JetUtil::CompareLV(addjets[j],jets[k])==true) continue;
	float tMT2 = CalcMT2(MET,lep+addjets[0],addjets[j]+jets[k],massive,testmass);
	if(tMT2<MT2) MT2 = tMT2;
	tMT2 = CalcMT2(MET,lep+addjets[j],addjets[0]+jets[k],massive,testmass);
	if(tMT2<MT2) MT2 = tMT2;
      }
    }
  }
  return MT2;
}
float CalcMT2_lb_bq_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass, bool massive){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return CalcMT2_lb_bq(metlv, lep, bjets, addjets, jets, testmass, massive);
}

float CalcMT2_lb_bqq(LorentzVector MET, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass, bool massive){
  if(bjets.size()+addjets.size()<2) return -999.99;
  if(jets.size()<4) return -199.99*jets.size();
  float MT2 = 99999;
  for(unsigned int i = 0; i<bjets.size(); ++i){
    for(unsigned int j = i+1; j<bjets.size(); ++j){
      for(unsigned int k = 0; k<jets.size(); ++k){
	if(JetUtil::CompareLV(bjets[i],jets[k])==true) continue;
	if(JetUtil::CompareLV(bjets[j],jets[k])==true) continue;
	for(unsigned int l = k+1; l<jets.size(); ++l){
	  if(JetUtil::CompareLV(bjets[i],jets[l])==true) continue;
	  if(JetUtil::CompareLV(bjets[j],jets[l])==true) continue;
	  float tMT2 = CalcMT2(MET,lep+bjets[i],bjets[j]+jets[k]+jets[l],massive,testmass);
	  if(tMT2<MT2) MT2 = tMT2;
	  tMT2 = CalcMT2(MET,lep+bjets[j],bjets[i]+jets[k]+jets[l],massive,testmass);
	  if(tMT2<MT2) MT2 = tMT2;
	}
      }
    }
    for(unsigned int j = 0; j<addjets.size(); ++j){
      for(unsigned int k = 0; k<jets.size(); ++k){
	if(JetUtil::CompareLV(bjets[i],jets[k])==true) continue;
	if(JetUtil::CompareLV(addjets[j],jets[k])==true) continue;
	for(unsigned int l = k+1; l<jets.size(); ++l){
	  if(JetUtil::CompareLV(bjets[i],jets[l])==true) continue;
	  if(JetUtil::CompareLV(bjets[j],jets[l])==true) continue;
	  float tMT2 = CalcMT2(MET,lep+bjets[i],addjets[j]+jets[k]+jets[l],massive,testmass);
	  if(tMT2<MT2) MT2 = tMT2;
	  tMT2 = CalcMT2(MET,lep+addjets[j],bjets[i]+jets[k]+jets[l],massive,testmass);
	  if(tMT2<MT2) MT2 = tMT2;
	}
      }
    }
  }
  if(bjets.size()==0){
    for(unsigned int j = 1; j<addjets.size(); ++j){
      for(unsigned int k = 0; k<jets.size(); ++k){
	if(JetUtil::CompareLV(addjets[0],jets[k])==true) continue;
	if(JetUtil::CompareLV(addjets[j],jets[k])==true) continue;
	for(unsigned int l = k+1; l<jets.size(); ++l){
	  if(JetUtil::CompareLV(addjets[0],jets[l])==true) continue;
	  if(JetUtil::CompareLV(addjets[j],jets[l])==true) continue;
	  float tMT2 = CalcMT2(MET,lep+addjets[0],addjets[j]+jets[k]+jets[l],massive,testmass);
	  if(tMT2<MT2) MT2 = tMT2;
	  tMT2 = CalcMT2(MET,lep+addjets[j],addjets[0]+jets[k]+jets[l],massive,testmass);
	  if(tMT2<MT2) MT2 = tMT2;
	}
      }
    }
  }
  return MT2;
}

float CalcMT2_lb_bqq_(float MET, float METPhi, LorentzVector lep, vector<LorentzVector> bjets, vector<LorentzVector> addjets, vector<LorentzVector> jets, float testmass, bool massive){
  float metx = MET*TMath::Cos(METPhi);
  float mety = MET*TMath::Sin(METPhi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,MET);
  return CalcMT2_lb_bqq(metlv, lep, bjets, addjets, jets, testmass, massive);
}
