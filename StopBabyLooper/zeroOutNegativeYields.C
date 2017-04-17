#include "stopBabyLooper.h"

int zeroOutNegativeYields(std::string f_input_dir){

  // Extenstion for zeroed samples
  TString nonZeroExt = "_noNegYield.root";

  // Get sample list
  sampleInfo::vect_id sampleList;
  sampleList.push_back( sampleInfo::k_DYJetsToLL_m10To50_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_DYJetsToLL_m50_amcnlo_pythia8 );
  // sampleList.push_back( sampleInfo::k_WJetsToLNu_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_t_sch_4f_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_WZTo2L2Q_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_WZTo1LNu2Q_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_WZTo1L3Nu_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2L2Q_amcnlo_pythia8 );
  sampleList.push_back( sampleInfo::k_ZZTo2Q2Nu_amcnlo_pythia8 );
  // sampleList.push_back( sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8 );
  // sampleList.push_back( sampleInfo::k_TTWJetsToQQ_amcnlo_pythia8 );
  // sampleList.push_back( sampleInfo::k_TTZToQQ_amcnlo_pythia8 );
  // sampleList.push_back( sampleInfo::k_TTZToLLNuNu_m10_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_tZq_ll_4f_amcnlo_pythia8 );
  //sampleList.push_back( sampleInfo::k_tZq_nunu_4f_amcnlo_pythia8 );


  // Get Inclusive genClassyInfo
  genClassyInfo::Util gen_incl( genClassyInfo::k_incl );
  TString inclClassy_name = "";
  inclClassy_name += "__genClassy_";
  inclClassy_name += gen_incl.label;

  // Get ee1lep genClassyInfo
  genClassyInfo::Util gen_ee1lep( genClassyInfo::k_ee1lep );
  TString ee1lepClassy_name = "";
  ee1lepClassy_name += "__genClassy_";
  ee1lepClassy_name += gen_ee1lep.label;

  // Get ee1lep_fromW genClassyInfo
  genClassyInfo::Util gen_ee1lep_fromW( genClassyInfo::k_ee1lep_fromW );
  TString ee1lepFromWClassy_name = "";
  ee1lepFromWClassy_name += "__genClassy_";
  ee1lepFromWClassy_name += gen_ee1lep_fromW.label;
  
  // Get eel1ep_fromT genClassyInfo
  genClassyInfo::Util gen_ee1lep_fromT( genClassyInfo::k_ee1lep_fromTop );
  TString ee1lepFromTClassy_name = "";
  ee1lepFromTClassy_name += "__genClassy_";
  ee1lepFromTClassy_name += gen_ee1lep_fromT.label;

  // Get ge2lep genClassyInfo
  genClassyInfo::Util gen_ge2lep( genClassyInfo::k_ge2lep );
  TString ge2lepClassy_name = "";
  ge2lepClassy_name += "__genClassy_";
  ge2lepClassy_name += gen_ge2lep.label;

  // Get ZtoNuNu genClassyInfo
  genClassyInfo::Util gen_ZtoNuNu( genClassyInfo::k_ZtoNuNu );
  TString ZtoNuNuClassy_name = "";
  ZtoNuNuClassy_name += "__genClassy_";
  ZtoNuNuClassy_name += gen_ZtoNuNu.label;


  // Get list of genClassy components to resum inclusive
  genClassyInfo::vect_id genComponentList;
  genComponentList.push_back( genClassyInfo::k_ee1lep_fromW );
  genComponentList.push_back( genClassyInfo::k_ee1lep_fromTop );
  genComponentList.push_back( genClassyInfo::k_ge2lep );
  genComponentList.push_back( genClassyInfo::k_ZtoNuNu );
  
  // loop over sampleList
  for(int iSample=0; iSample<(int)sampleList.size(); iSample++){

    sampleInfo::sampleUtil sample( sampleList[iSample] );

    TString f_in_name = "";
    f_in_name += f_input_dir;
    f_in_name += sample.label;
    f_in_name += ".root";

    std::cout << "  Testing the following for zeros: " << std::endl;
    std::cout << "    " << f_in_name << std::endl << std::endl;
      
    TString f_out_name = f_in_name;
    f_out_name.ReplaceAll(".root", nonZeroExt);

    TFile *f_in  = new TFile(f_in_name, "read");
    TFile *f_out = new TFile(f_out_name, "recreate");

    std::vector<TString> h1_inclResumList;
    std::vector<TString> h2_inclResumList;

    TIter nextIter(f_in->GetListOfKeys());
    TKey *key;
    int nHists=0;
    int nZeros=0;
    while ((key = (TKey*)nextIter())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      
      if(cl->InheritsFrom("TH1D")){
	nHists++;
	TH1D *h = (TH1D*)key->ReadObj();
	TH1D *h_clone = (TH1D*)h->Clone();
	h_clone->SetDirectory(f_out);

	TString h_name = h_clone->GetName();
	
	// Special Case for yields histogram
	if( h_name.Contains("yields") ){
	  
	  bool foundNegCategory=false;
	  for(int iBin=1; iBin<=(int)h_clone->GetNbinsX(); iBin++){
	    if( h_clone->GetBinContent(iBin)<0.0 ){
	      h_clone->SetBinContent(iBin,0.0);
	      h_clone->SetBinError(iBin,0.0);
	      foundNegCategory=true;
	    }
	  }

	  // if ee1lep replace name with inclusive name
	  if(foundNegCategory){
	    nZeros++;

	    if(h_name.Contains(ee1lepClassy_name) && !h_name.Contains(ee1lepFromWClassy_name) && !h_name.Contains(ee1lepFromTClassy_name)){
	      TString replace_str = ee1lepClassy_name;
	      TString h_name_incl = h_name;
	      h_name_incl.ReplaceAll(ee1lepClassy_name,inclClassy_name);
	      h1_inclResumList.push_back(h_name_incl);
	    } // end if ee1lep

	    // if ee1lepFromW replace name with inclusive name
	    if(h_name.Contains(ee1lepFromWClassy_name)){
	      TString replace_str = ee1lepFromWClassy_name;
	      TString h_name_incl = h_name;
	      h_name_incl.ReplaceAll(ee1lepFromWClassy_name,inclClassy_name);
	      h1_inclResumList.push_back(h_name_incl);
	    } // end if ee1lep_fromW

	    // if ee1lepFromT replace name with inclusive name
	    if(h_name.Contains(ee1lepFromTClassy_name)){
	      TString replace_str = ee1lepFromTClassy_name;
	      TString h_name_incl = h_name;
	      h_name_incl.ReplaceAll(ee1lepFromTClassy_name,inclClassy_name);
	      h1_inclResumList.push_back(h_name_incl);
	    } // end if ee1lep_fromT
	    
	    // if ge2lep replace name with inclusive name
	    if(h_name.Contains(ge2lepClassy_name)){
	      TString replace_str = ge2lepClassy_name;
	      TString h_name_incl = h_name;
	      h_name_incl.ReplaceAll(ge2lepClassy_name,inclClassy_name);
	      h1_inclResumList.push_back(h_name_incl);
	    } // end if ge2lep

	    // if ZtoNuNu replace name with inclusive name
	    if(h_name.Contains(ZtoNuNuClassy_name)){
	      TString replace_str = ZtoNuNuClassy_name;
	      TString h_name_incl = h_name;
	      h_name_incl.ReplaceAll(ZtoNuNuClassy_name,inclClassy_name);
	      h1_inclResumList.push_back(h_name_incl);
	    } // end if ZtoNuNu
	  
	  } // end if foundNeg Category

	} // end if yields

	// Else if normal histogram, check if integral is negative
	else if(h_clone->Integral(0,-1)<0.0){
	  h_clone->Reset();
	  nZeros++;

	  // if ee1lep repalce name wiht inclusive name
	  if(h_name.Contains(ee1lepClassy_name) && !h_name.Contains(ee1lepFromWClassy_name) && !h_name.Contains(ee1lepFromTClassy_name)){
	    TString replace_str = ee1lepClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ee1lepClassy_name,inclClassy_name);
	    h1_inclResumList.push_back(h_name_incl);
	  } // end if ee1lep
	  
	  // if ee1lepFromW replace name with inclusive name
	  if(h_name.Contains(ee1lepFromWClassy_name)){
	    TString replace_str = ee1lepFromWClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ee1lepFromWClassy_name,inclClassy_name);
	    h1_inclResumList.push_back(h_name_incl);
	  } // end if ee1lep_fromW
	  
	  // if ee1lepFromT replace name with inclusive name
	  if(h_name.Contains(ee1lepFromTClassy_name)){
	    TString replace_str = ee1lepFromTClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ee1lepFromTClassy_name,inclClassy_name);
	    h1_inclResumList.push_back(h_name_incl);
	  } // end if ee1lep_fromT
	    
	  // if ge2lep replace name with inclusive name
	  if(h_name.Contains(ge2lepClassy_name)){
	    TString replace_str = ge2lepClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ge2lepClassy_name,inclClassy_name);
	    h1_inclResumList.push_back(h_name_incl);
	  } // end if ge2lep

	  // if ZtoNuNu replace name with inclusive name
	  if(h_name.Contains(ZtoNuNuClassy_name)){
	    TString replace_str = ZtoNuNuClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ZtoNuNuClassy_name,inclClassy_name);
	    h1_inclResumList.push_back(h_name_incl);
	  } // end if ZtoNuNu

	  
	} // end if integral <0.0
	
      } // end if TH1D

      if(cl->InheritsFrom("TH2D")){
	nHists++;
	TH2D *h = (TH2D*)key->ReadObj();
	TH2D *h_clone = (TH2D*)h->Clone();
	h_clone->SetDirectory(f_out);
	
	TString h_name = h_clone->GetName();
	
	// Check if integral is negative
	if(h_clone->Integral(0,-1)<0.0){
	  h_clone->Reset();
	  nZeros++;

	  // if ee1lep repalce name wiht inclusive name
	  if(h_name.Contains(ee1lepClassy_name) && !h_name.Contains(ee1lepFromWClassy_name) && !h_name.Contains(ee1lepFromTClassy_name)){
	    TString replace_str = ee1lepClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ee1lepClassy_name,inclClassy_name);
	    h2_inclResumList.push_back(h_name_incl);
	  } // end if ee1lep
	  
	  // if ee1lepFromW replace name with inclusive name
	  if(h_name.Contains(ee1lepFromWClassy_name)){
	    TString replace_str = ee1lepFromWClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ee1lepFromWClassy_name,inclClassy_name);
	    h2_inclResumList.push_back(h_name_incl);
	  } // end if ee1lep_fromW
	  
	  // if ee1lepFromT replace name with inclusive name
	  if(h_name.Contains(ee1lepFromTClassy_name)){
	    TString replace_str = ee1lepFromTClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ee1lepFromTClassy_name,inclClassy_name);
	    h2_inclResumList.push_back(h_name_incl);
	  } // end if ee1lep_fromT
	    
	  // if ge2lep replace name with inclusive name
	  if(h_name.Contains(ge2lepClassy_name)){
	    TString replace_str = ge2lepClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ge2lepClassy_name,inclClassy_name);
	    h2_inclResumList.push_back(h_name_incl);
	  } // end if ge2lep

	  // if ZtoNuNu replace name with inclusive name
	  if(h_name.Contains(ZtoNuNuClassy_name)){
	    TString replace_str = ZtoNuNuClassy_name;
	    TString h_name_incl = h_name;
	    h_name_incl.ReplaceAll(ZtoNuNuClassy_name,inclClassy_name);
	    h2_inclResumList.push_back(h_name_incl);
	  } // end if ZtoNuNu


	 
	} // end if negative integral

      } // end if TH2D
      
    } // end while loop over TKeys
    
    f_out->Write();
    f_out->Close();
    f_in->Close();
    
    
    if( nZeros==0 ){
      std::cout << "  Out of " << nHists << " histos tested, " << nZeros << " histos with negative yield were found and set to zero " << std::endl;
      std::cout << "  Output written to: " << f_out_name << std::endl;
      std::cout << std::endl << std::endl << std::endl << std::endl;

      continue;
    }

    
    // Re-sum inclusive histos
    f_out = new TFile(f_out_name, "update");
    
    // TH1D
    for(int iH1=0; iH1<(int)h1_inclResumList.size(); iH1++){
      
      // Grab inclusive histogram
      TH1D *h_incl = (TH1D*)f_out->Get(h1_inclResumList[iH1]);
      h_incl->Reset();
      h_incl->SetDirectory(f_out);
      
      // Grab components
      for(int iComp=0; iComp<(int)genComponentList.size(); iComp++){
	genClassyInfo::Util genClassy( genComponentList[iComp] );
	TString replace_str = "__genClassy_";
	replace_str += genClassy.label;

	TString h_name_component = h_incl->GetName();
	h_name_component.ReplaceAll(inclClassy_name, replace_str);
	
	TH1D *h_component = (TH1D*)f_out->Get(h_name_component);
	
	h_incl->Add(h_component);
      } // end loop over components

    } // end loop over h1 to resum

    
    // TH2D
    for(int iH2=0; iH2<(int)h2_inclResumList.size(); iH2++){
      
      // Grab inclusive histogram
      TH2D *h_incl = (TH2D*)f_out->Get(h2_inclResumList[iH2]);
      h_incl->Reset();
      h_incl->SetDirectory(f_out);
	
      // Grab components
      for(int iComp=0; iComp<(int)genComponentList.size(); iComp++){
	genClassyInfo::Util genClassy( genComponentList[iComp] );
	TString replace_str = "__genClassy_";
	replace_str += genClassy.label;

	TString h_name_component = h_incl->GetName();
	h_name_component.ReplaceAll(inclClassy_name, replace_str);

	TH2D *h_component = (TH2D*)f_out->Get(h_name_component);
		
	h_incl->Add(h_component);
      } // end loop over components

    } // end loop over h2 to resum
    
    
    f_out->Write();
    f_out->Close();

    
    std::cout << "  Out of " << nHists << " histos tested, " << nZeros << " histos with negative yield were found and set to zero " << std::endl;
    std::cout << "  Output written to: " << f_out_name << std::endl;
    std::cout << std::endl << std::endl << std::endl << std::endl;


  } // end loop over samples  

  return 0;
}
