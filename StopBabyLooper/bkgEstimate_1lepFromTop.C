#include "stopBabyLooper.h"

int bkgEstimate_1lepFromTop(){


  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  
  //
  // Configuration Variables
  //
  bool doRescale     = false; // also triggers using psuedo-data, ie sum of allBkg
  double rescale     = 1.0; // use lumi from stopCORE
  //double rescale     = 40.0/35.867; // rescale to new lumi

     
  //
  // Open Files
  //
  TString inDir  = "Output/Histos/";
  TString outDir = "Output/BkgEstimate/";

  TFile *f_SR_mc = new TFile(inDir+"allBkg_25ns.root", "read");
  genClassyInfo::Util genClassy_SR_MC( genClassyInfo::k_ee1lep_fromTop );
  
    
  //
  // Systematics
  //
  sysInfo::Util nominal_sys( sysInfo::k_nominal );
  
  sysInfo::vect_util systematicList;
  systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) );
  
  const int nSys = (int)systematicList.size();
 


  //
  // List of scenarios for bkg estimates
  //
  std::vector<bkgEstUtil> v_bkgEst;
  

  // Dev, ext30fb,  mlb with tight bTagging
  bkgEstUtil bkgEst_ext30fb_mlb_v2;
 
  bkgEst_ext30fb_mlb_v2.outName_base = "bkgEst_1lepFromTop__mlb_v2_bins";
  bkgEst_ext30fb_mlb_v2.hName_base = "h_yields";
	bkgEst_ext30fb_mlb_v2.name_SR = "SR_bulk";

  // Region A
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(1);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(2);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(3);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(4);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>600$");
  
  // Region B
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(5);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(6);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(7);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>600$");


  // Region C
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(8);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(9); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(10); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(11); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(12); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>650$");


  // Region D
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(13); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(14); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(15); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(16); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>550$");


  // Region E
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(17); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(18); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<550$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(19); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>550$");


  // Region F
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(20); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(21); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>450$");

  
  // Region G
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(22); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(23); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(24); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(25); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>600$");


  // Region H
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(26); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<450$");
 
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(27); 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>550$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_mlb_v2 );




  // corridor results
  bkgEstUtil bkgEst_corridor;
 
  bkgEst_corridor.outName_base = "bkgEst_1lepFromTop__corridor_bins";
  bkgEst_corridor.hName_base = "h_yields";
	bkgEst_corridor.name_SR = "SR_corridor";

  bkgEst_corridor.SR_bins.push_back(1);  
  bkgEst_corridor.regionName.push_back("top~corridor"); 
  bkgEst_corridor.regionName_short.push_back("corridor"); 
  bkgEst_corridor.binName.push_back("$250<MET<350$");
  
  bkgEst_corridor.SR_bins.push_back(2);  
  bkgEst_corridor.regionName.push_back("top~corridor");
  bkgEst_corridor.regionName_short.push_back("corridor"); 
  bkgEst_corridor.binName.push_back("$350<MET<450$");
  
  bkgEst_corridor.SR_bins.push_back(3);  
  bkgEst_corridor.regionName.push_back("top~corridor");
  bkgEst_corridor.regionName_short.push_back("corridor"); 
  bkgEst_corridor.binName.push_back("$450<MET<550$");
  
  bkgEst_corridor.SR_bins.push_back(4);  
  bkgEst_corridor.regionName.push_back("top~corridor");  
  bkgEst_corridor.regionName_short.push_back("corridor"); 
  bkgEst_corridor.binName.push_back("$MET>550$");

  v_bkgEst.push_back( bkgEst_corridor );
  



  //
  // Loop over vector of bkg estimates
  //
  for(int iBkgEst=0; iBkgEst<(int)v_bkgEst.size(); iBkgEst++){

    // Get output base name
    TString outNameBase = v_bkgEst[iBkgEst].outName_base;

    // Get yield histo base name
    TString hNameBase = v_bkgEst[iBkgEst].hName_base;

    // Get region name
    TString regionName_SR = v_bkgEst.at(iBkgEst).name_SR;

    // Get number of signal regions
    const int nSRs = (int)v_bkgEst[iBkgEst].SR_bins.size();
    
    // Root Output File for Bkg Estimate
    TString root_fileName = outDir;
    root_fileName += outNameBase;
    root_fileName += "__histos.root";
    TFile  *f_out = new TFile(root_fileName.Data(), "recreate");


    // Histograms for limit setting
    const int nSys_histos = nSys + 2; // +2 for +/- 100% unc

    TH1D *h_SR[nSys_histos];
    h_SR[0] = new TH1D("ee1lep_fromTop_yield",   "ee1lep_fromTop_yield",   nSRs, 0.0, nSRs); // Nominal
    h_SR[1] = new TH1D("ee1lep_fromTop_totUp",   "ee1lep_fromTop_totUp",   nSRs, 0.0, nSRs); // mc stats up
    h_SR[2] = new TH1D("ee1lep_fromTop_totDn",   "ee1lep_fromTop_totDn",   nSRs, 0.0, nSRs); // mc stats dn
    for(int iCat=0; iCat<(int)nSRs; iCat++){
      
      TString binName = v_bkgEst[iBkgEst].regionName[iCat];
      binName += "__";
      binName += v_bkgEst[iBkgEst].binName[iCat];

      h_SR[0]->GetXaxis()->SetBinLabel( iCat+1, binName );
      h_SR[1]->GetXaxis()->SetBinLabel( iCat+1, binName );
      h_SR[2]->GetXaxis()->SetBinLabel( iCat+1, binName );
    }

    h_SR[0]->SetDirectory(f_out);
    h_SR[1]->SetDirectory(f_out);
    h_SR[2]->SetDirectory(f_out);
    
        
        
    //
    // Loop over categories to get yields
    //
    TH1D *h_temp = NULL;
    TString hName = "";
    for(int iSR=0; iSR<nSRs; iSR++){
      
      //
      // Get yields, begin calculation for this cateogry
      //
      int SR_bin = v_bkgEst[iBkgEst].SR_bins[iSR];
      
      // SR, category bin 
      hName = hNameBase;
      hName += "__";
      hName += regionName_SR;
      hName += "__genClassy_";
      hName += genClassy_SR_MC.label;
      hName += "__systematic_";
      hName += nominal_sys.label;
      
      h_temp = (TH1D*)f_SR_mc->Get(hName);
      if(!h_temp) cout << "BAD SR CATEGORY BIN HISTO: " << hName << endl;

      double SR_bin_yield = h_temp->GetBinContent( SR_bin );
      double SR_bin_error = h_temp->GetBinError( SR_bin );
      
      if(doRescale){
	SR_bin_error *= rescale;
	SR_bin_yield *= rescale;
      }
      
      
      // Fill histograms for limit setting, 0 is nominal element, 1 is first bin
      h_SR[0]->SetBinContent( iSR+1, SR_bin_yield );
      h_SR[0]->SetBinError( iSR+1, SR_bin_yield ); // 100% uncertainty
      
      
      // Fill histograms for limit setting, MC Stats
      h_SR[1]->SetBinContent( iSR+1, (SR_bin_yield+SR_bin_yield) );
      h_SR[1]->SetBinError( iSR+1, SR_bin_yield );
      h_SR[2]->SetBinContent( iSR+1, (SR_bin_yield-SR_bin_yield) );
      h_SR[2]->SetBinError( iSR+1, SR_bin_yield );

      
    } // end loop over signal regions

        
    // Write and Close Root File for Limit Setting
    cout << "Saving table of 1l-from-Top estimates to file " << f_out->GetName() << endl;
    f_out->Write();
    f_out->Close();
  
  
  } // end loop over bkgEstimate yields
  
  
  //
  // Clean up
  //
  f_SR_mc->Close();

  cout << endl;
  
  return 0;
}
