#include "StopFunctions.h"


namespace StF {
  bool isSignalOrControlRegion() {
    if(cms3.nvtxs()<0)               return false;
    if(cms3.ngoodleps()<1)           return false;
    if(cms3.ngoodjets()<2)           return false;
    if(cms3.ngoodbtags()<0)          return false;
    if(cms3.pfmet()<250)             return false;
    if(cms3.mt_met_lep()<150)        return false;
    if(cms3.mindphi_met_j1_j2()<0.8) return false;
    return true;
  }
  bool isSignalRegion() {
    if(!isSignalOrControlRegion())   return false;
    if(cms3.ngoodleps()!=1)          return false;
    if(cms3.nvetoleps()!=1)          return false;
    if(!cms3.PassTrackVeto_v3())     return false;
    if(!cms3.PassTauVeto())          return false;
    if(cms3.ngoodbtags()<1)          return false;
    return true;
  }
  bool isDileptonControlRegion() {
    if(!isSignalOrControlRegion())   return false;
    if(cms3.ngoodbtags()<1)          return false;
    if(cms3.ngoodleps()==2) return true;
    if(cms3.ngoodleps()==1&&cms3.nvetoleps()>=2&&cms3.lep2_pt()>=10) return true;
    if(cms3.ngoodleps()==1&&cms3.nvetoleps()==1&&(!cms3.PassTrackVeto_v3()||!cms3.PassTauVeto())) return true;
    return false;
  }
  bool isNoBTagControlRegion(){
    if(!isSignalOrControlRegion())   return false;
    if(cms3.ngoodleps()!=1)          return false;
    if(cms3.nvetoleps()!=1)          return false;
    if(!cms3.PassTrackVeto_v3())     return false;
    if(!cms3.PassTauVeto())          return false;
    if(cms3.ngoodbtags()!=0)         return false;
    return true;
  }
  int SRIdentifier(){
    if(!isSignalRegion())   return -1;//has MET>250 in it
    if(cms3.ngoodjets()>=4){
      if(cms3.MT2W()<=200){
	if(cms3.pfmet()>325) return 6;
	return 5;
      } else { //high MT2W
	if(cms3.pfmet()>450) return 9;
	if(cms3.pfmet()>350) return 8;
	return 7;
      }
    } else if(cms3.ngoodjets()==3 && cms3.MT2W()>200) {
      if(cms3.pfmet()>350) return 4;
      return 3;
    } else if(cms3.ngoodjets()==2 && cms3.topnessMod()>6.4) {
      if(cms3.pfmet()>350) return 2;
      return 1;
    }
    return -2;//should happen for lowMT2W/tMod for njet 3/2
  }
  int CR2lIdentifier(){
    if(!isDileptonControlRegion())   return -1;//has MET>250 in it
    if(cms3.ngoodjets()==2&&cms3.topnessMod()>6.4){
      return 1;
    }
    if(cms3.ngoodjets()>=3){
      if(cms3.MT2W()<=200) return 2;
      return 3;
    }
    return -2;
  }
  int CR0bIdentifier(){
    if(!isNoBTagControlRegion())   return -1;//has MET>250 in it
    if(cms3.ngoodjets()==2&&cms3.topnessMod()>6.4){
      return 1;
    } else if(cms3.ngoodjets()==3&&cms3.MT2W()>200){
      return 2;
    } else if(cms3.ngoodjets()>=4&&cms3.MT2W()>200){
      return 3;
    }
    return -2;
  }
  bool passSignalTriggers(){
    //no matching done
    if(cms3.HLT_MET170()>0) return true;
    if(cms3.lep1_is_el() && cms3.HLT_SingleEl23()>0) return true;
    if(cms3.lep1_is_mu() && cms3.HLT_SingleMu20()>0) return true;
    return false;
  }
  bool passMETfiltersNoTxt(){
    if(!cms3.filt_hbhenoise())   return false;
    if(!cms3.filt_cscbeamhalo()) return false;
    if(!cms3.filt_goodvtx())     return false;
    if(!cms3.filt_eebadsc())     return false;
    return true;
  }
  int whichT2tbdecay(){
    int tLSP = 0;
    int bCharg = 0;
    for(unsigned int i = 0; i<cms3.gensusy_id().size(); ++i){
      if(abs(cms3.gensusy_id()[i])!=1000022) continue;
      if(cms3.gensusy_status()[i]!=1) continue;
      if(abs(cms3.gensusy_motherid()[i])==1000024) ++bCharg;
      if(abs(cms3.gensusy_motherid()[i])==1000006) ++tLSP;
    }
    if((tLSP+bCharg)!=2) return -99;
    if(tLSP==2) return 1;
    if(tLSP==1&&bCharg==1) return 2;
    if(bCharg==2) return 3;
    return -1;//should never happen
  }
  int PolarizationWeights(float &wL, float &wR){
    wL = 1.0;
    wR = 1.0;
    LorentzVector tl1, tl2;
    LorentzVector tt1, tt2;
    LorentzVector tst1, tst2;
    for(unsigned int i = 0; i<cms3.gensusy_id().size(); ++i){
      if(cms3.gensusy_status()[i]!=1) continue;
      if((cms3.gensusy_id()[i])==1000022&&(cms3.gensusy_motherid()[i])== 1000006) { tst1 = cms3.gensusy_motherp4()[i]; }//mother of LSP
      if((cms3.gensusy_id()[i])==1000022&&(cms3.gensusy_motherid()[i])==-1000006) { tst2 = cms3.gensusy_motherp4()[i]; }
    }
    for(unsigned int i = 0; i<cms3.genleps_id().size(); ++i){
      if(cms3.genleps_status()[i] != 23 && cms3.genleps_status()[i] != 22 && cms3.genleps_status()[i] != 1) continue;
      if(abs(cms3.genleps_motherid()[i])!=24) continue;
      if((cms3.genleps_gmotherid()[i])== 6&&cms3.genleps_gmotherid()[i]*cms3.genleps_id()[i]<0) { tt1 = cms3.genleps_gmotherp4()[i]; tl1 = cms3.genleps_p4()[i]; }
      if((cms3.genleps_gmotherid()[i])==-6&&cms3.genleps_gmotherid()[i]*cms3.genleps_id()[i]<0) { tt2 = cms3.genleps_gmotherp4()[i]; tl2 = cms3.genleps_p4()[i]; }
    }
    for(unsigned int i = 0; i<cms3.gennus_id().size(); ++i){
      if(cms3.gennus_status()[i] != 23 && cms3.gennus_status()[i] != 22 && cms3.gennus_status()[i] != 1) continue;
      if(abs(cms3.gennus_motherid()[i])!=24) continue;
      if((cms3.gennus_gmotherid()[i])== 6&&cms3.gennus_gmotherid()[i]*cms3.gennus_id()[i]<0) { tt1 = cms3.gennus_gmotherp4()[i]; tl1 = cms3.gennus_p4()[i]; }
      if((cms3.gennus_gmotherid()[i])==-6&&cms3.gennus_gmotherid()[i]*cms3.gennus_id()[i]<0) { tt2 = cms3.gennus_gmotherp4()[i]; tl2 = cms3.gennus_p4()[i]; }

    }
    for(unsigned int i = 0; i<cms3.genqs_id().size(); ++i){
      if(cms3.genqs_status()[i] != 23 && cms3.genqs_status()[i] != 22 && cms3.genqs_status()[i] != 1) continue;
      if(abs(cms3.genqs_motherid()[i])!=24) continue;
      if((cms3.genqs_gmotherid()[i])== 6&&cms3.genqs_gmotherid()[i]*cms3.genqs_id()[i]<0) { tt1 = cms3.genqs_gmotherp4()[i]; tl1 = cms3.genqs_p4()[i]; }
      if((cms3.genqs_gmotherid()[i])==-6&&cms3.genqs_gmotherid()[i]*cms3.genqs_id()[i]<0) { tt2 = cms3.genqs_gmotherp4()[i]; tl2 = cms3.genqs_p4()[i]; }
    }
    TLorentzVector st1; st1.SetPxPyPzE(tst1.Px(),tst1.Py(),tst1.Pz(),tst1.E());
    TLorentzVector st2; st2.SetPxPyPzE(tst2.Px(),tst2.Py(),tst2.Pz(),tst2.E());
    TVector3 bV1(-st1.Px()/st1.Energy(),-st1.Py()/st1.Energy(),-st1.Pz()/st1.Energy());
    TVector3 bV2(-st2.Px()/st2.Energy(),-st2.Py()/st2.Energy(),-st2.Pz()/st2.Energy());
    TLorentzVector t1; t1.SetPxPyPzE(tt1.Px(),tt1.Py(),tt1.Pz(),tt1.E());
    TLorentzVector t2; t2.SetPxPyPzE(tt2.Px(),tt2.Py(),tt2.Pz(),tt2.E());
    TLorentzVector l1; l1.SetPxPyPzE(tl1.Px(),tl1.Py(),tl1.Pz(),tl1.E());
    TLorentzVector l2; l2.SetPxPyPzE(tl2.Px(),tl2.Py(),tl2.Pz(),tl2.E());
    t1.Boost(bV1);
    t2.Boost(bV2);
    l1.Boost(bV1);
    l2.Boost(bV2);
    if(t1.P()>0&&l1.P()>0){
      double costh = (t1.Px()*l1.Px()+t1.Py()*l1.Py()+t1.Pz()*l1.Pz())/t1.P()/l1.P();
      double weight_L = (t1.Energy()+t1.P())*(1-costh);
      double weight_R = (t1.Energy()-t1.P())*(1+costh);
      wL *= 2*weight_L/(weight_R+weight_L);
      wR *= 2*weight_R/(weight_R+weight_L);
    }
    if(t2.P()>0&&l2.P()>0){
      double costh = (t2.Px()*l2.Px()+t2.Py()*l2.Py()+t2.Pz()*l2.Pz())/t2.P()/l2.P();
      double weight_L = (t2.Energy()+t2.P())*(1-costh);
      double weight_R = (t2.Energy()-t2.P())*(1+costh);
      wL *= 2*weight_L/(weight_R+weight_L);
      wR *= 2*weight_R/(weight_R+weight_L);
    }
    return 1;
  }//polarization weight
 
}//namespace
