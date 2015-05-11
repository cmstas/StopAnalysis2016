#include "topness.h"

//version 1: without 'reco top' and 'CM' term
//all other version: full topness (including 'reco W')
float topnessMinimization(TLorentzVector met, TLorentzVector lep, TLorentzVector bjet1, TLorentzVector bjet2, int version) {
    
  TFitter *minimizer=new TFitter(4) ;
  double p1 = -1;
  minimizer->ExecuteCommand("SET PRINTOUT",&p1,1);
  if(version==1) minimizer->SetFCN(minuitFunctionWrapperV1);
  else minimizer->SetFCN(minuitFunctionWrapper);
  // get variables for Topness
  double iLpx = lep.Px();
  double iLpy = lep.Py();
  double iLpz = lep.Pz();
  double iLpe = lep.E();
  double iB1px = bjet1.Px();
  double iB1py = bjet1.Py();
  double iB1pz = bjet1.Pz();
  double iB1pe = bjet1.E();
  double iB2px = bjet2.Px();
  double iB2py = bjet2.Py();
  double iB2pz = bjet2.Pz();
  double iB2pe = bjet2.E();
  double iMpx = met.Px();
  double iMpy = met.Py();
  double iMpz = met.Pz();
  double iMpe = met.E();
  // Define parameters [param number, param name, init val, estimated distance to min, bla, bla] // 300,3000,-3000,3000
  minimizer->SetParameter(0,"pwx",0,500,-3000,3000);
  minimizer->SetParameter(1,"pwy",0,500,-3000,3000);
  minimizer->SetParameter(2,"pwz",0,500,-3000,3000);
  minimizer->SetParameter(3,"pnz",0,500,-3000,3000);
  // fixed parameters
  minimizer->SetParameter(4,"plx",iLpx,0,iLpx-0.001,iLpx+0.001);
  minimizer->SetParameter(5,"ply",iLpy,0,iLpy-0.001,iLpy+0.001);
  minimizer->SetParameter(6,"plz",iLpz,0,iLpz-0.001,iLpz+0.001);
  minimizer->SetParameter(7,"ple",iLpe,0,iLpe-0.001,iLpe+0.001);
  minimizer->SetParameter(8,"pb1x",iB1px,0,iB1px-0.001,iB1px+0.001);
  minimizer->SetParameter(9,"pb1y",iB1py,0,iB1py-0.001,iB1py+0.001);
  minimizer->SetParameter(10,"pb1z",iB1pz,0,iB1pz-0.001,iB1pz+0.001);
  minimizer->SetParameter(11,"pb1e",iB1pe,0,iB1pe-0.001,iB1pe+0.001);
  minimizer->SetParameter(12,"pb2x",iB2px,0,iB2px-0.001,iB2px+0.001);
  minimizer->SetParameter(13,"pb2y",iB2py,0,iB2py-0.001,iB2py+0.001);
  minimizer->SetParameter(14,"pb2z",iB2pz,0,iB2pz-0.001,iB2pz+0.001);
  minimizer->SetParameter(15,"pb2e",iB2pe,0,iB2pe-0.001,iB2pe+0.001);
  minimizer->SetParameter(16,"pmx",iMpx,0,iMpx-0.001,iMpx+0.001);
  minimizer->SetParameter(17,"pmy",iMpy,0,iMpy-0.001,iMpy+0.001);
  minimizer->SetParameter(18,"pmz",iMpz,0,iMpz-0.001,iMpz+0.001);
  minimizer->SetParameter(19,"pme",iMpe,0,iMpe-0.001,iMpe+0.001);
  minimizer->FixParameter(4);
  minimizer->FixParameter(5);
  minimizer->FixParameter(6);
  minimizer->FixParameter(7);
  minimizer->FixParameter(8);
  minimizer->FixParameter(9);
  minimizer->FixParameter(10);
  minimizer->FixParameter(11);
  minimizer->FixParameter(12);
  minimizer->FixParameter(13);
  minimizer->FixParameter(14);
  minimizer->FixParameter(15);
  minimizer->FixParameter(16);
  minimizer->FixParameter(17);
  minimizer->FixParameter(18);
  minimizer->FixParameter(19);
  // Run the simplex minimizer to get close to the minimum [no good precision, but robust]
  // For signal regions, no difference seen with migrad, but more stable
  minimizer->ExecuteCommand("SIMPLEX",0,0);
  //Get the best fit values
  double pwx_fit = minimizer->GetParameter(0);
  double pwy_fit = minimizer->GetParameter(1);
  double pwz_fit = minimizer->GetParameter(2);
  double pnz_fit = minimizer->GetParameter(3);
  delete minimizer;
  // get the function value at best fit
  if(version==1){
    return log(topnessFunctionV1(pwx_fit,pwy_fit,pwz_fit,pnz_fit,
				 iLpx,iLpy,iLpz,iLpe,
				 iB1px,iB1py,iB1pz,iB1pe,
				 iB2px,iB2py,iB2pz,iB2pe,
				 iMpx,iMpy,iMpz,iMpe
				 ));
  }
  else {
    return log(topnessFunction(pwx_fit,pwy_fit,pwz_fit,pnz_fit,
                               iLpx,iLpy,iLpz,iLpe,
                               iB1px,iB1py,iB1pz,iB1pe,
                               iB2px,iB2py,iB2pz,iB2pe,
                               iMpx,iMpy,iMpz,iMpe
                               ));
  }
} // ~ end of Topness Minimization()

// full function
double topnessFunction(double pwx_, double pwy_, double pwz_, double pnz_,
                       double plx_, double ply_, double plz_, double ple_,
                       double pb1x_, double pb1y_, double pb1z_, double pb1e_,
                       double pb2x_, double pb2y_, double pb2z_, double pb2e_,
                       double pmx_, double pmy_, double pmz_, double pme_) {
  const double mW = 81.;
  const double mT = 172.;
  const double aW = 5.;
  const double aT = 15.;
  const double aCM = 1000.;
    
  // construct the lorentz vectors
  TLorentzVector vW; vW.SetPxPyPzE(pwx_,pwy_,pwz_,(sqrt((mW*mW)+(pwx_*pwx_)+(pwy_*pwy_)+(pwz_*pwz_)))) ;
  TLorentzVector vL; vL.SetPxPyPzE(plx_,ply_,plz_,ple_);
  TLorentzVector vB1; vB1.SetPxPyPzE(pb1x_,pb1y_,pb1z_,pb1e_);
  TLorentzVector vB2; vB2.SetPxPyPzE(pb2x_,pb2y_,pb2z_,pb2e_);
  TLorentzVector vMET; vMET.SetPxPyPzE(pmx_,pmy_,pmz_,pme_);
  TLorentzVector vN; vN.SetPxPyPzE((pmx_-pwx_),(pmy_-pwy_),pnz_,(sqrt(pow((pmx_-pwx_),2)+pow((pmy_-pwy_),2)+pow(pnz_,2))));
  // construct the w-term (lost)
  //double tWM = ( pow( ((mW*mW) - (vW.M2())),2) ) / (pow(aW,4));//zero by construction
  // construct the w-term (lep)
  double tWL = ( pow( ((mW*mW) - ((vL+vN).M2())),2) ) / (pow(aW,4));
  // construct the tL-term [seen lepton]
  double tTL = ( pow( ((mT*mT) - ((vL+vB1+vN).M2())),2) ) / (pow(aT,4));
  // construct the tM-term [miss lepton]
  double tTM = ( pow( ((mT*mT) - ((vB2+vW).M2())),2) ) / (pow(aT,4));
  // construct the CM-term
  double tCM = ( pow( ((4*(mT*mT)) - ((vL+vN+vW+vB1+vB2).M2())),2) ) / (pow(aCM,4));
  // calculate Topness
  double Topness = tWL + tTL + tTM + tCM;
  return Topness;
}

//version 1: without 'reco top' and 'CM' term
double topnessFunctionV1(double pwx_, double pwy_, double pwz_, double pnz_,
			 double plx_, double ply_, double plz_, double ple_,
			 double pb1x_, double pb1y_, double pb1z_, double pb1e_,
			 double pb2x_, double pb2y_, double pb2z_, double pb2e_,
			 double pmx_, double pmy_, double pmz_, double pme_) {
  const double mW = 81.;
  const double mT = 172.;
  const double aW = 5.;
  const double aT = 15.;
  //const double aCM = 1000.;
    
  // construct the lorentz vectors
  TLorentzVector vW; vW.SetPxPyPzE(pwx_,pwy_,pwz_,(sqrt((mW*mW)+(pwx_*pwx_)+(pwy_*pwy_)+(pwz_*pwz_)))) ;
  TLorentzVector vL; vL.SetPxPyPzE(plx_,ply_,plz_,ple_);
  TLorentzVector vB1; vB1.SetPxPyPzE(pb1x_,pb1y_,pb1z_,pb1e_);
  TLorentzVector vB2; vB2.SetPxPyPzE(pb2x_,pb2y_,pb2z_,pb2e_);
  TLorentzVector vMET; vMET.SetPxPyPzE(pmx_,pmy_,pmz_,pme_);
  TLorentzVector vN; vN.SetPxPyPzE((pmx_-pwx_),(pmy_-pwy_),pnz_,(sqrt(pow((pmx_-pwx_),2)+pow((pmy_-pwy_),2)+pow(pnz_,2))));
  // construct the w-term (lost)
  //double tWM = ( pow( ((mW*mW) - (vW.M2())),2) ) / (pow(aW,4));//zero by construction
  // construct the w-term (lep)
  double tWL = ( pow( ((mW*mW) - ((vL+vN).M2())),2) ) / (pow(aW,4));
  // construct the tL-term [seen lepton]
  //double tTL = ( pow( ((mT*mT) - ((vL+vB1+vN).M2())),2) ) / (pow(aT,4));
  // construct the tM-term [miss lepton]
  double tTM = ( pow( ((mT*mT) - ((vB2+vW).M2())),2) ) / (pow(aT,4));
  // construct the CM-term
  //double tCM = ( pow( ((4*(mT*mT)) - ((vL+vN+vW+vB1+vB2).M2())),2) ) / (pow(aCM,4));
  // calculate Topness
  double Topness = tWL + tTM;
  return Topness;
}

//wrapper function using TLorentzVector
// double precision needed for minimization
float gettopness(TLorentzVector met, TLorentzVector lep, vector<TLorentzVector> bjets, int version){
  double topness = 9e9;
  if(bjets.size()<2) {
    cout << "You have " << bjets.size() << " bjets, but need at least 2, return -999" << endl;
    return -999.;
  }
  for(unsigned int n = 0; n<bjets.size(); ++n){
    for(unsigned int m = 0; m<bjets.size(); ++m){
      if(n==m) continue;
      double tmptop = topnessMinimization(met,lep,bjets[n],bjets[m],version);
      if(tmptop<topness) topness = tmptop;
    }
  }
  return topness;
}

//wrapper function to get topness using b-tagged jets as input
//helper function using Math::LorentzVector
float Gettopness(LorentzVector met, LorentzVector lep, vector<LorentzVector> bjets, int version){
  TLorentzVector metlv; metlv.SetPxPyPzE(met.Px(),met.Py(),met.Pz(),met.E());
  TLorentzVector leplv; leplv.SetPxPyPzE(lep.Px(),lep.Py(),lep.Pz(),lep.E());
  TLorentzVector temp(0.,0.,0.,0.); vector<TLorentzVector> jetslv;
  for(unsigned int i = 0; i<bjets.size(); ++i){
    temp.SetPxPyPzE(bjets[i].Px(),bjets[i].Py(),bjets[i].Pz(),bjets[i].E());
    jetslv.push_back(temp);
  }
  return gettopness(metlv,leplv,jetslv,version);
}

//wrapper function to get topness using b-tagged jets as input (MET as Pt,Phi given)
//helper function using Math::LorentzVector, using Met.Pt and MET.Phi
float Gettopness_(float met, float metphi, LorentzVector lep, vector<LorentzVector> bjets, int version){
  float metx = met*TMath::Cos(metphi);
  float mety = met*TMath::Sin(metphi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,met);
  return Gettopness(metlv, lep, bjets, version);
}

//wrapper function to get topness using jets as input
//addnjets: if <=1 bjets found, have total of addnjets for bjet looper adding jets to bjet vector using addjets (default=2, recommended=2,3)
//addjets: ==1: according to highest b-tag discriminant, ==2: according to highest jet-pt (default=2)
//version: ==1: reduced topness (recommended), else: full topness
float TopnessVersion(int version, LorentzVector MET, LorentzVector lep, vector<LorentzVector> jets, vector<float> jet_bdiscr, float btagdiscr, unsigned int addnjets, int addjets){
  if(jets.size()!=jet_bdiscr.size() ) {
    cout << "the vectors jets("<<jets.size()<<") and jet_bdiscr("<<jet_bdiscr.size()<<") have different lengths, please fix. return -99" << endl;
    return -99;
  }
  vector<LorentzVector> bjet = JetUtil::BJetSelector(jets,jet_bdiscr,btagdiscr,2,addnjets,addjets);

  return Gettopness(MET,lep,bjet,version);
}

//wrapper function to get topness using jets as input (MET as Pt,Phi given)
//addnjets: if <=1 bjets found, have total of addnjets for bjet looper adding jets to bjet vector using addjets (default=2, recommended=2,3)
//addjets: ==1: according to highest b-tag discriminant, ==2: according to highest jet-pt (default=2)
//version: ==1: reduced topness (recommended), else: full topness
float TopnessVersion_(int version, float met, float metphi, LorentzVector lep, vector<LorentzVector> jets, vector<float> jet_bdiscr, float btagdiscr, unsigned int addnjets, int addjets){
  float metx = met*TMath::Cos(metphi);
  float mety = met*TMath::Sin(metphi);
  LorentzVector metlv; metlv.SetPxPyPzE(metx,mety,0,met);
  return TopnessVersion(version,metlv,lep,jets,jet_bdiscr,btagdiscr,addnjets,addjets);
}
