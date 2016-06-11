#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TCollection.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

#include <algorithm>
#include <string>
#include <vector>

#include "../StopCORE/analyzerInfo.h"
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/recoClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/systematicInfo.h"
#include "../StopCORE/histogramInfo.h"

void combineSystematics(){

  std::vector< std::pair< std::string, systematicInfo::ID > > sysList;
  std::pair< std::string, systematicInfo::ID > sys_i_o;

  std::string nominal_dir = "Histos/Nominal/";
  systematicInfo::systematicUtil nominal_sys(systematicInfo::k_nominal);
  
  sys_i_o.first  = "Histos/JesUp/";
  sys_i_o.second = systematicInfo::k_JESUp;
  sysList.push_back( sys_i_o );

  sys_i_o.first  = "Histos/JesDn/";
  sys_i_o.second = systematicInfo::k_JESDown;
  sysList.push_back( sys_i_o );

  analyzerInfo::ID analysis = analyzerInfo::k_CR2l;

  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList( analysis );

  for(int iSys=0; iSys<(int)sysList.size(); iSys++){
    
    std::string source_dir = sysList[iSys].first;
    systematicInfo::systematicUtil source_sys(sysList[iSys].second );
    
    for(int iSample=0; iSample<(int)sampleList.size(); iSample++){
      
      sampleInfo::sampleUtil sample( sampleList[iSample] );

      if( sample.isData ) continue;
      
      std::string f_nominal_name = "";
      f_nominal_name += nominal_dir;
      f_nominal_name += "h__";
      f_nominal_name += sample.label;
      f_nominal_name += ".root";

      std::string f_source_name = "";
      f_source_name += source_dir;
      f_source_name += "h__";
      f_source_name += sample.label;
      f_source_name += ".root";

      TFile *f_nominal = new TFile( f_nominal_name.c_str(), "update");
      TFile *f_source  = new TFile( f_source_name.c_str(), "read");

      cout << "Nominal Baby Name = " << f_nominal_name << endl;
      cout << "Source Baby Name  = " << f_source_name << endl;

      TIter nextIter(f_source->GetListOfKeys());
      TKey *key;
      while ((key = (TKey*)nextIter())) {
	TClass *cl = gROOT->GetClass(key->GetClassName());
	
	if(cl->InheritsFrom("TH1D")){
	  TH1D *h = (TH1D*)key->ReadObj();

	  TString h_name = h->GetName();
	  if( h_name.Contains(nominal_sys.label) ){
	    
	    TString h_name_clone = h_name;
	    h_name_clone.ReplaceAll(nominal_sys.label,source_sys.label);
	    
	    TH1D *h_clone = (TH1D*)h->Clone(h_name_clone);
	    h_clone->SetDirectory(f_nominal);

	  } // end if found nominal histogram in jes file
	} // end if TH1D

	if(cl->InheritsFrom("TH2D")){
	  TH2D *h = (TH2D*)key->ReadObj();

	  TString h_name = h->GetName();
	  if( h_name.Contains(nominal_sys.label) ){

	    TString h_name_clone = h_name;
	    h_name_clone.ReplaceAll(nominal_sys.label,source_sys.label);
	    
	    TH2D *h_clone = (TH2D*)h->Clone(h_name_clone);
	    h_clone->SetDirectory(f_nominal);

	  } // end if found nominal histogram in jes file
	} // end if TH2D
  
	if(cl->InheritsFrom("TH3D")){
	  TH3D *h = (TH3D*)key->ReadObj();

	  TString h_name = h->GetName();
	  if( h_name.Contains(nominal_sys.label) ){

	    TString h_name_clone = h_name;
	    h_name_clone.ReplaceAll(nominal_sys.label,source_sys.label);
	    
	    TH3D *h_clone = (TH3D*)h->Clone(h_name_clone);
	    h_clone->SetDirectory(f_nominal);

	  } // end if found nominal histogram in jes file
	} // end if TH3D
	
      } // end loop over keys
      
      f_nominal->Write();
      f_nominal->Close();
      f_nominal->~TFile();

      f_source->Close();
      f_source->~TFile();

    } // end loop over samples

  } // end loop over systematic directories


  return;
}
