#ifndef Utilities_hh
#define Utilities_hh

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <cmath>
#include <unistd.h>

#include "TROOT.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1.h"
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TEfficiency.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

namespace Util {
  //__________________________________________________________________________
  inline TString MakeOutputDir(TString dir){
    if(!dir.EndsWith("/")) dir += "/";
    // Create directory if needed
    char cmd[100];
    sprintf(cmd,"mkdir -p %s", dir.Data());
    system(cmd);
    return dir;
  }
  
  //general purpose utilities
  inline string intToString(int i){
    std::string s;
    std::stringstream out;
    out << i;
    s= out.str();
    return s;
  }
  
  inline string floatToString(float i){
    std::string s;
    std::stringstream out;
    out << i;
    s= out.str();
    return s;
  }
  inline void PrintAs(TCanvas *cin, TString name, TString dir, TString format){
    // Prints a ROOT TCanvas Object to a .png file
    //  name is the bare output filename, e.g. "fit_4_8",
    //  dir is the output directory (inside the overall output dir.)
    // Create sub directories if needed
    dir = MakeOutputDir(dir);
    
    dir += name;
    dir += "." + format;
    cin->SaveAs(dir);
  }
  inline float DeltaPhi(float phi1, float phi2){
    float result = phi1 - phi2;
    while( result >   TMath::Pi() ) result -= TMath::TwoPi();
    while( result <= -TMath::Pi() ) result += TMath::TwoPi();
    return TMath::Abs(result);
  }
  inline float deltaPhi(LorentzVector l1, LorentzVector l2){
    return DeltaPhi(l1.Phi(), l2.Phi());
  }
  inline float DeltaR(float eta1, float eta2, float phi1, float phi2){
    float deta = eta1 - eta2;
    float dphi = Util::DeltaPhi(phi1, phi2);
    return sqrt( deta*deta + dphi*dphi );
  }
  inline float deltaR(LorentzVector l1, LorentzVector l2){
    return DeltaR(l1.Eta(), l2.Eta(), l1.Phi(), l2.Phi());
  }

  inline void getEfficiency(TH1F* num, TH1F*den, float &eff, float &errlow, float &errup, int bin=-1){
    TH1F *num_c, *den_c;
    num_c = (TH1F*) num->Clone();
    TString hname = num->GetName();
    num_c->SetName( hname+"_clone");
    hname = den->GetName();
    den_c = (TH1F*) den->Clone();
    den_c->SetName( hname+"_clone");
    if(bin<0||bin>num_c->GetNbinsX()){
      num_c->Rebin( num_c->GetNbinsX() );
      den_c->Rebin( den_c->GetNbinsX() );
      bin = 1;
    }
    TEfficiency *teff = new TEfficiency((*num_c),(*den_c));
    eff = teff->GetEfficiency(bin);
    errlow = teff->GetEfficiencyErrorLow(bin);
    errup = teff->GetEfficiencyErrorUp(bin);
    delete num_c;
    delete den_c;
    delete teff;
  }
  inline void getEfficiency2D(TH2F* num, TH2F*den, float &eff, float &errlow, float &errup, int binX=-1, int binY=-1){
    TH2F *num_c, *den_c;
    num_c = (TH2F*) num->Clone();
    TString hname = num->GetName();
    num_c->SetName( hname+"_clone");
    hname = den->GetName();
    den_c = (TH2F*) den->Clone();
    den_c->SetName( hname+"_clone");
    if(binX<0||binX>num_c->GetNbinsX()){
      num_c->RebinX( num_c->GetNbinsX() );
      den_c->RebinX( den_c->GetNbinsX() );
      binX = 1;
    }
    if(binY<0||binY>num_c->GetNbinsY()){
      num_c->RebinY( num_c->GetNbinsY() );
      den_c->RebinY( den_c->GetNbinsY() );
      binY = 1;
    }
    int bin = num_c->GetBin(binX,binY);
    TEfficiency *teff = new TEfficiency((*num_c),(*den_c));
    eff = teff->GetEfficiency(bin);
    errlow = teff->GetEfficiencyErrorLow(bin);
    errup = teff->GetEfficiencyErrorUp(bin);
    delete num_c;
    delete den_c;
    delete teff;
  }
  float loadSFwUncUpDown(string type, string input, float &errl, float &erru){
    char buffer[500];
    char StringValue[500];
    float numberValue;
    float numberValueU;
    float numberValueD;
    ifstream IN(input.c_str());
    while( IN.getline(buffer, 500, '\n') ){
      if (buffer[0] == '#') {
	continue; // Skip lines commented with '#'
      }
      sscanf(buffer, "%s\t%f\t%f\t%f", StringValue, &numberValue, &numberValueU, &numberValueD);
      stringstream ss;
      string s;
      ss << StringValue;
      ss >> s;
      if(s.find(type)!=string::npos) {
	errl = numberValueU;
	erru = numberValueD;
	return numberValue;
      }
    }
    errl = -99.;
    erru = -99.;
    return -99.;
  }
  float loadSFwUnc(string type, string input, float &err){
    float dummy;
    return loadSFwUncUpDown(type, input, err, dummy);
  }
  float loadSF(string type, string input){
    float dummy1, dummy2;
    return loadSFwUncUpDown(type, input, dummy1, dummy2);
  }

}//end of Util namespace

#endif
