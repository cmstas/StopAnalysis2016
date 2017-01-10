// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

// std
#include <string>
#include <vector>

// stopCORE
#include "../StopCORE/sampleInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/sysInfo.h"


//
// Utility Class
//
class bkgEstUtil{

public:
  TString outName_base;
  TString hName_base;

  vector<int> SR_bins;
  vector<int> CR_bins;
  
  vector<TString> regionName;
  vector<TString> regionName_short;
  vector<TString> binName;

  bkgEstUtil(){};
  ~bkgEstUtil(){};
};


//
// Helper Function
//
void printLatexHeader( FILE *file ){
  fprintf(file, "\\documentclass{article}\n");
  fprintf(file, "\\usepackage[landscape]{geometry}\n");
  fprintf(file, "\\usepackage{chngpage}\n");
  fprintf(file, "\\usepackage{graphicx} \n");
  fprintf(file, "\n");
  fprintf(file, "\\begin{document}\n");
  fprintf(file, "\\tiny \n");  
}

//
// Main
//
int bkgEstimate_ZtoNuNu(){


  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  
  //
  // Configuration Variables
  //
  bool doRescale     = false; // also triggers using psuedo-data, ie sum of allBkg
  double rescale     = 1.0; // use lumi from stopCORE
  //double rescale     = 40.0/29.53; // rescale to new lumi

     
  //
  // Open Files
  //
  TString inDir  = "Output/Histos/";
  TString outDir = "Output/BkgEstimate/";

  TFile *f_SR_mc = new TFile(inDir+"allBkg_25ns.root", "read");
  genClassyInfo::Util genClassy_SR_MC( genClassyInfo::k_ZtoNuNu );
  
    
  //
  // Systematics
  //
  sysInfo::Util nominal_sys( sysInfo::k_nominal );
  
  sysInfo::vect_util systematicList;
  systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_JESUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_JESDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_bTagEffHFUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_bTagEffHFDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_bTagEffLFUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_bTagEffLFDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_lepSFUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_lepSFDown) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_metResUp) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_metResDown) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_ttbarSysPtUp) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_ttbarSysPtDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_pdfUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_pdfDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_alphasUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_alphasDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_q2Up) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_q2Down) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_cr2lTriggerUp) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_cr2lTriggerDown) );
  
  const int nSys = (int)systematicList.size();
 


  //
  // List of scenarios for bkg estimates
  //
  std::vector<bkgEstUtil> v_bkgEst;
  
  // ICHEP results
  bkgEstUtil bkgEst_ICHEP;

  bkgEst_ICHEP.outName_base = "bkgEst_ZtoNuNu__ICHEP_bins";
  bkgEst_ICHEP.hName_base = "h_yields_SR_ICHEP";

  bkgEst_ICHEP.SR_bins.push_back(1);  
  bkgEst_ICHEP.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$"); 
  bkgEst_ICHEP.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(2);  
  bkgEst_ICHEP.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$");
  bkgEst_ICHEP.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(3);  
  bkgEst_ICHEP.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$");  
  bkgEst_ICHEP.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>450$");


  bkgEst_ICHEP.SR_bins.push_back(4);  
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(5);  
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(6);  
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP.SR_bins.push_back(7);  
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>550$");
  

  bkgEst_ICHEP.SR_bins.push_back(8);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(9);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(10); 
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>450$");
  

  bkgEst_ICHEP.SR_bins.push_back(11); 
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(12); 
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(13); 
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP.SR_bins.push_back(14); 
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$550<MET<650$");
  
  bkgEst_ICHEP.SR_bins.push_back(15); 
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>650$");
  
  
  v_bkgEst.push_back( bkgEst_ICHEP );



  // ICHEP results, exttened to 30fb
  bkgEstUtil bkgEst_ICHEP_ext30fb;
 
  bkgEst_ICHEP_ext30fb.outName_base = "bkgEst_ZtoNuNu__ICHEP_ext30fb_bins";
  bkgEst_ICHEP_ext30fb.hName_base = "h_yields_SR_ICHEP_ext30fb";

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(1);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$"); 
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(2);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(3);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(4);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(5);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~modifiedTopness$\\ge6.4$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>650$");


  bkgEst_ICHEP_ext30fb.SR_bins.push_back(6);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(7);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(8);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(9);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");
    
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(10); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>650$");
  

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(11); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(12); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(13); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(14); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(15); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>450$");
  

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(16); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(17); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(18); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(19); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(20); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$650<MET<800$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(21); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>800$");
  
  
  v_bkgEst.push_back( bkgEst_ICHEP_ext30fb );
  


  // Dev, ext30fb,  mlb
  bkgEstUtil bkgEst_ext30fb_mlb;
 
  bkgEst_ext30fb_mlb.outName_base = "bkgEst_ZtoNuNu__mlb_v1_bins";
  bkgEst_ext30fb_mlb.hName_base = "h_yields_SR_dev_ext30fb_mlb_v1";

  // Region A
  bkgEst_ext30fb_mlb.SR_bins.push_back(1);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(2);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(3);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>500$");
  
  // Region B
  bkgEst_ext30fb_mlb.SR_bins.push_back(4);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(5);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(6);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<650$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(7);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>650$");


  // Region C
  bkgEst_ext30fb_mlb.SR_bins.push_back(8);  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(9); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(10); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(11); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(12); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>650$");


  // Region D
  bkgEst_ext30fb_mlb.SR_bins.push_back(13); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(14); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(15); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(16); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>550$");


  // Region E
  bkgEst_ext30fb_mlb.SR_bins.push_back(17); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(18); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(19); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>550$");


  // Region F
  bkgEst_ext30fb_mlb.SR_bins.push_back(20); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(21); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(22); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>500$");

  
  // Region G
  bkgEst_ext30fb_mlb.SR_bins.push_back(23); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(24); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(25); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(26); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>600$");


  // Region H
  bkgEst_ext30fb_mlb.SR_bins.push_back(27); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");
 
  bkgEst_ext30fb_mlb.SR_bins.push_back(28); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<650$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(29); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>650$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_mlb );


  // Dev, ext30fb,  mlb with tight bTagging
  bkgEstUtil bkgEst_ext30fb_mlb_v2;
 
  bkgEst_ext30fb_mlb_v2.outName_base = "bkgEst_ZtoNuNu__mlb_v2_bins";
  bkgEst_ext30fb_mlb_v2.hName_base = "h_yields_SR_dev_ext30fb_mlb_v2";

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



  // Dev, ext30fb,  bJetPt
  bkgEstUtil bkgEst_ext30fb_bJetPt;
 
  bkgEst_ext30fb_bJetPt.outName_base = "bkgEst_ZtoNuNu__bJetPt_v1_bins";
  bkgEst_ext30fb_bJetPt.hName_base = "h_yields_SR_dev_ext30fb_bJetPt_v1";

  // Region A
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(1);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(2);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(3);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(4);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>600$");
  

  // Region B
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(5);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(6);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(7);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$500<MET<650$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(8);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>650$");


  // Region C
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(9);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(10); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(11); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(12); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(13); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>650$");


  // Region D
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(14); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(15); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(16); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(17); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>550$");


  // Region E
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(18); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(19); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(20); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>450$");


  // Region F
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(21); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<400$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(22); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(23); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$modifiedTopness$<7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>500$");


  // Region G
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(24); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(25); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(26); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<650$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(27); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>650$");

  
  // Region H
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(28); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("H"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<450$");
 
    bkgEst_ext30fb_bJetPt.SR_bins.push_back(29); 
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~modifiedTopness$\\ge7.5$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("H"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>450$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_bJetPt );



  // corridor results
  bkgEstUtil bkgEst_corridor;
 
  bkgEst_corridor.outName_base = "bkgEst_ZtoNuNu__corridor_bins";
  bkgEst_corridor.hName_base = "h_yields_SR_corridor";

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

    // Get number of signal regions
    const int nSRs = (int)v_bkgEst[iBkgEst].SR_bins.size();
    
    // Root Output File for Bkg Estimate
    TString root_fileName = outDir;
    root_fileName += outNameBase;
    root_fileName += "__histos.root";
    TFile  *f_out = new TFile(root_fileName.Data(), "recreate");


    // Histograms for limit setting
    const int nSys_histos = nSys + 2; // +2 for mc status up/down

    TH1D *h_SR[nSys_histos];
    h_SR[0] = new TH1D("ZtoNuNu_yield",       "ZtoNuNu_yield",       nSRs, 0.0, nSRs); // Nominal
    h_SR[1] = new TH1D("ZtoNuNu_mcStatsUp",   "ZtoNuNu_mcStatsUp",   nSRs, 0.0, nSRs); // mc stats up
    h_SR[2] = new TH1D("ZtoNuNu_mcStatsDn",   "ZtoNuNu_mcStatsDn",   nSRs, 0.0, nSRs); // mc stats dn
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
    
    // Systematics for limit setting
    for(int iSys=1; iSys<nSys; iSys++){
      h_SR[iSys+2] = new TH1D(Form("ZtoNuNu_%s", systematicList[iSys].label.c_str()), Form("ZtoNuNu_%s",systematicList[iSys].label.c_str()), nSRs, 0.0, nSRs);   
      for(int iCat=0; iCat<(int)nSRs; iCat++){

	TString binName = v_bkgEst[iBkgEst].regionName[iCat];
	binName += "__";
	binName += v_bkgEst[iBkgEst].binName[iCat];
	
	h_SR[iSys+2]->GetXaxis()->SetBinLabel( iCat+1, binName );
      }
      h_SR[iSys+2]->SetDirectory(f_out);
    }
    

    // Results Table
    //   ROW=Categories, COL=Lost Lepton Estimate and Components
    FILE *yFile;
    TString texFile = outDir;
    texFile += outNameBase;
    texFile += "__resultsTable.tex";
    yFile = fopen(texFile.Data(), "w");
    
    cout << "Writing Table of Lost Lepton Estimates to file; " << endl;
    cout << "    " << texFile << endl;

    printLatexHeader(yFile);
    fprintf(yFile, "\\tiny \n");  
    fprintf(yFile, "\\begin{table} \n");
    fprintf(yFile, "\\caption{ Lost Lepton Background Estimate and Components, for each Signal Region } \n");
    fprintf(yFile, "\\scalebox{1.0}{ \n");
    fprintf(yFile, "\\begin{tabular}{|l|c|c|} \\hline \n");
    fprintf(yFile, "Region & MET bin & $N_{Z\\rightarrow\\nu\\nu,estimate}^{SR}$");
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");
    

    // Uncertainty table for each category
    //   ROW=Uncertainties, COL=DiLepton Estimate and Components
    FILE *uncFile = NULL;
    TString uncFileName = outDir;
    uncFileName += outNameBase;
    uncFileName += "__uncertaintyTable__byCategory.tex";
    uncFile = fopen(uncFileName.Data(), "w");
    
    cout << "Writing table of diLepton uncertainties to: " << endl;
    cout << "    " << uncFileName << endl;

    printLatexHeader(uncFile);
    

    
    // Uncertainty Table, Summary of components over all Categories
    //   ROW=Uncertainty ranges by %, over all cateogries, COL=DiLepton Estimate and Components
    FILE *uncFileSummary;
    TString uncFileSummaryName = outDir;
    uncFileSummaryName += outNameBase;
    uncFileSummaryName += "__uncertaintyTable__summary.tex";
    uncFileSummary = fopen(uncFileSummaryName.Data(), "w");
    
    cout << "Writing Table of Lost Lepton Uncertainties to: " << endl;
    cout << "    " << uncFileSummaryName << endl;
    
    printLatexHeader(uncFileSummary);
    fprintf(uncFileSummary, "\\begin{table} \n");
    fprintf(uncFileSummary, "\\caption{ Summary of Lost Lepton Background Estimate Uncertainties } \n");
    fprintf(uncFileSummary, "\\scalebox{0.7}{ \n");
    fprintf(uncFileSummary, "\\begin{tabular}{|l|c|} \\hline \n");
    fprintf(uncFileSummary, "Systematic & $N_{Z\\rightarrow\\nu\\nu,estimate}^{SR},~(\\%%)$ ");
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \\hline \n");
    

    // Need an arry of min/max, element for each systematic
    const int nSys_unique = ((nSys-1)/2) + 2; // -1 for nominal, +1 for mc stats, +1 for total uncertainty
    double uncMax_sr_estimate[nSys_unique]; 
    double uncMin_sr_estimate[nSys_unique];
    for(int iSys=0; iSys<nSys_unique; iSys++){
      uncMax_sr_estimate[iSys] = 0.0;
      uncMin_sr_estimate[iSys] = 999.9;
    }
    
      
    // Uncertainty summary table 
    //   ROWS=% Uncertainties on final estimate, COLS=Categories
    double cats_vs_sys[nSRs][nSys_unique];
    for(int iCat=0; iCat<nSRs; iCat++){
      for(int iSys=0; iSys<nSys_unique; iSys++){
	cats_vs_sys[iCat][iSys] = 0.0;
      }
    }
    
    FILE *uncFileSummaryV2 = NULL;
    TString uncFileSummaryV2Name = outDir;
    uncFileSummaryV2Name += outNameBase;
    uncFileSummaryV2Name += "__uncertaintyTable__summary__byCategory.tex";
    uncFileSummaryV2 = fopen(uncFileSummaryV2Name.Data(), "w");
    
    cout << "Writing table of diLepton uncertainties summary by cats to: " << endl;
    cout << "    " << uncFileSummaryV2Name << endl;
    
    printLatexHeader(uncFileSummaryV2);
    fprintf(uncFileSummaryV2, "\\begin{table} \n");
    fprintf(uncFileSummaryV2, "\\scalebox{0.3}{ \n");
    fprintf(uncFileSummaryV2, "\\begin{tabular}{|l|");
    for(int iCat=0; iCat<nSRs; iCat++){
      fprintf(uncFileSummaryV2, "c|");
    }
    fprintf(uncFileSummaryV2, "} \\hline \n");
    
    fprintf(uncFileSummaryV2, "Systematic ");
    for(int iCat=0; iCat<nSRs; iCat++){
      fprintf(uncFileSummaryV2, " & %s ", v_bkgEst[iBkgEst].regionName_short[iCat].Data());
    }
    fprintf(uncFileSummaryV2, "\\"); fprintf(uncFileSummaryV2, "\\  \n");
    for(int iCat=0; iCat<nSRs; iCat++){
      TString modified_metLabel = v_bkgEst[iBkgEst].binName[iCat];
      modified_metLabel.ReplaceAll("<MET<","-");
      modified_metLabel.ReplaceAll("MET>",">");
      fprintf(uncFileSummaryV2, " & %s ", modified_metLabel.Data());
    }
    fprintf(uncFileSummaryV2, "\\"); fprintf(uncFileSummaryV2, "\\ \\hline \\hline  \n");
  
    
        
    //
    // Loop over categories to get yields
    //
    TH1D *h_temp = NULL;
    TString hName = "";
    for(int iSR=0; iSR<nSRs; iSR++){
      
      // Category Name for yield tables
      TString catName = v_bkgEst[iBkgEst].regionName[iSR];
      catName += ",~";
      catName += v_bkgEst[iBkgEst].binName[iSR];

      fprintf(yFile, " %s & ", v_bkgEst[iBkgEst].regionName[iSR].Data() );
      fprintf(yFile, " %s & ", v_bkgEst[iBkgEst].binName[iSR].Data() );
      
      // Cateogry info for uncertainty table, for each category
      fprintf(uncFile, "\\begin{table} \n");
      fprintf(uncFile, "\\caption{ diLepton Background Estimate Uncertainties, for %s } \n", catName.Data());
      fprintf(uncFile, "\\scalebox{0.6}{ \n");
      fprintf(uncFile, "\\begin{tabular}{|l|c|} \\hline \n");
      fprintf(uncFile, "Systematic & $N_{Z\\rightarrow\\nu\\nu,estimate}^{SR},~(\\%%)$ ");
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n");

      
      //
      // Get yields, begin calculation for this cateogry
      //
      int SR_bin = v_bkgEst[iBkgEst].SR_bins[iSR];
      
      // SR, category bin 
      hName = hNameBase;
      hName += "__SR";
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
      h_SR[0]->SetBinError( iSR+1, SR_bin_error );
      
      
      // Uncertainty File, for each category, Nominal Values
      fprintf(uncFile, "Nominal & %.2f ", SR_bin_yield );
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n"); 
      
      
      // Uncertainty File, per category, MC Stats Up
      fprintf(uncFile, "MC Stats Up & %.2f ~(%.2f\\%%) ", SR_bin_yield+SR_bin_error, (100*SR_bin_error/SR_bin_yield) );
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 
      

      // Uncertainty File, per category, MC Stats Down
      fprintf(uncFile, "MC Stats Down & %.2f ~(%.2f\\%%) ", SR_bin_yield-SR_bin_error, (100*SR_bin_error/SR_bin_yield) );
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \n"); 
      
      fprintf(uncFile, "\\hline \n");
    
      
      // Calc Min/Max for MC Stats across all categories
      uncMax_sr_estimate[0] = std::max( uncMax_sr_estimate[0], (100*SR_bin_error/SR_bin_yield) );
      uncMin_sr_estimate[0] = std::min( uncMin_sr_estimate[0], (100*SR_bin_error/SR_bin_yield) );
      
      
      // Calc SR estimate for MC Stats for this cat
      cats_vs_sys[iSR][0] = (100*SR_bin_error/SR_bin_yield);
      
      
      // Fill histograms for limit setting, MC Stats
      h_SR[1]->SetBinContent( iSR+1, (SR_bin_error+SR_bin_yield) );
      h_SR[1]->SetBinError( iSR+1, SR_bin_error );
      h_SR[2]->SetBinContent( iSR+1, (SR_bin_error-SR_bin_yield) );
      h_SR[2]->SetBinError( iSR+1, SR_bin_error );
      
      
      
      //
      // Loop over systematics
      //
      int unique_sys = 1;
      for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
	
	// SR, category bin, up
	hName = hNameBase;
	hName += "__SR";
	hName += "__genClassy_";
	hName += genClassy_SR_MC.label;
	hName += "__systematic_";
	hName += systematicList[iSys].label;
	
	h_temp = (TH1D*)f_SR_mc->Get(hName);
	if(!h_temp) cout << "BAD SR CATEGORY BIN UP HISTO: " << hName << endl;
	
	double SR_bin_yield_up = h_temp->GetBinContent( SR_bin );
	double SR_bin_error_up = h_temp->GetBinError( SR_bin );
      
	if(doRescale){
	  SR_bin_error_up *= rescale;
	  SR_bin_yield_up *= rescale;
	}
      
	
	// SR, category bin, dn
	hName = hNameBase;
	hName += "__SR";
	hName += "__genClassy_";
	hName += genClassy_SR_MC.label;
	hName += "__systematic_";
	hName += systematicList[iSys+1].label;
      
	h_temp = (TH1D*)f_SR_mc->Get(hName);
	if(!h_temp) cout << "BAD SR BIN DN HISTO: " << hName << endl;
	
	double SR_bin_error_dn = h_temp->GetBinError( SR_bin );
	double SR_bin_yield_dn = h_temp->GetBinContent( SR_bin );
	
	if(doRescale){
	  SR_bin_error_dn *= rescale;
	  SR_bin_yield_dn *= rescale;
	}
      
      
	// Diff in SR estimate
	double est_max_diff = std::max( fabs(SR_bin_yield_up-SR_bin_yield), fabs(SR_bin_yield_dn-SR_bin_yield) );
	double est_max_diff_sq = pow( est_max_diff, 2 );
	SR_bin_error = pow( SR_bin_error, 2 );
	SR_bin_error += est_max_diff_sq;
	SR_bin_error = sqrt(SR_bin_error);
	
     
	// Fill histograms for limit setting
	h_SR[iSys+2]->SetBinContent( iSR+1, SR_bin_yield_up );
	h_SR[iSys+2]->SetBinError( iSR+1, SR_bin_error_up );
	h_SR[iSys+3]->SetBinContent( iSR+1, SR_bin_yield_dn );
	h_SR[iSys+3]->SetBinError( iSR+1, SR_bin_error_dn );
	
      
	//
	// Tables
	//
	
	// Up variations
	fprintf(uncFile, "%s,~Up & %.2f ~(%.2f\\%%)  ", systematicList[iSys].tex.c_str(), SR_bin_yield_up, (100*(SR_bin_yield_up-SR_bin_yield)/SR_bin_yield) );
	fprintf(uncFile, "\\"); fprintf(uncFile, "\\  \n"); 
	
	// Down variations
	fprintf(uncFile, "%s,~Down & %.2f ~(%.2f\\%%)  ",systematicList[iSys].tex.c_str(), SR_bin_yield_dn, (100*(SR_bin_yield_dn-SR_bin_yield)/SR_bin_yield) );
	fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");
	
	
	// Fill Min/Max Uncertainty
	uncMax_sr_estimate[unique_sys] = std::max( uncMax_sr_estimate[unique_sys], (100*est_max_diff/SR_bin_yield) );
	uncMin_sr_estimate[unique_sys] = std::min( uncMin_sr_estimate[unique_sys], (100*est_max_diff/SR_bin_yield) );

      
	// Calc SR estimate for this sys for this cat
	cats_vs_sys[iSR][unique_sys] = (100*est_max_diff/SR_bin_yield);
      

	// Increment unique sys counter
	unique_sys++;

      
      } // end loop over systematics


      // Total Uncertainty, for tabales
      fprintf(uncFile, "\\hline \n");
      fprintf(uncFile, "Total Uncertainties & %.2f\\%% ", (100*SR_bin_error/SR_bin_yield) );
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");
      
      h_SR[0]->SetBinError( iSR+1, SR_bin_error );
      
      
      // Formatting for uncertainty tex file for each category
      fprintf(uncFile, "\\end{tabular} \n");
      fprintf(uncFile, "} \n");
      fprintf(uncFile, "\\end{table} \n");
      fprintf(uncFile, "\n \n");
      fprintf(uncFile, "\\clearpage");
      fprintf(uncFile, "\n \n");
    
    
      // Fill Min/Max Uncertainty
      uncMax_sr_estimate[nSys_unique-1] = std::max( uncMax_sr_estimate[nSys_unique-1], (100*SR_bin_error/SR_bin_yield) );
      uncMin_sr_estimate[nSys_unique-1] = std::min( uncMin_sr_estimate[nSys_unique-1], (100*SR_bin_error/SR_bin_yield) );
      
      
      // Calc SR estimate for total error for this cat
      cats_vs_sys[iSR][nSys_unique-1] = (100*SR_bin_error/SR_bin_yield);
    
    
      // Final Results Table
      fprintf(yFile, "%.2f $\\pm$ %.2f " , SR_bin_yield, SR_bin_error);
      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
      
      
    } // end loop over signal regions

  

    //
    // Summary table of uncertainties
    //
    fprintf(uncFileSummary, "MC Stats & $%.1f~-~%.1f~\\%%$ ", uncMin_sr_estimate[0], uncMax_sr_estimate[0]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
      
    int unique_sys = 1;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      fprintf(uncFileSummary, "%s & $%.1f~-~%.1f~\\%%$ ", sys_name.Data(), uncMin_sr_estimate[unique_sys], uncMax_sr_estimate[unique_sys]);
      fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
      unique_sys++;
    }
    
    fprintf(uncFileSummary, "Total & $%.1f~-~%.1f~\\%%$ ", uncMin_sr_estimate[nSys_unique-1], uncMax_sr_estimate[nSys_unique-1]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    

    // Uncertainty Summary File
    fprintf(uncFileSummary, "\\end{tabular} \n");
    fprintf(uncFileSummary, "} \n");
    fprintf(uncFileSummary, "\\end{table} \n");
    fprintf(uncFileSummary, "\\end{document} \n");
    fclose(uncFileSummary);
    
  
    // Uncertainty Summary File
    fprintf(uncFileSummaryV2, "MC Stats");
    for(int iSR=0; iSR<nSRs; iSR++){
      fprintf(uncFileSummaryV2, " & %.1f\\%% ", cats_vs_sys[iSR][0]);
    }
    fprintf(uncFileSummaryV2, "\\"); fprintf(uncFileSummaryV2, "\\ \\hline \n");
    
    int iSys_temp = 1;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      fprintf(uncFileSummaryV2, "%s ", sys_name.Data() );
      for(int iSR=0; iSR<nSRs; iSR++){
	fprintf(uncFileSummaryV2, " & %.1f\\%% ", cats_vs_sys[iSR][iSys_temp]);
      }
      fprintf(uncFileSummaryV2, "\\"); fprintf(uncFileSummaryV2, "\\ \n");
      iSys_temp++;
    }
    fprintf(uncFileSummaryV2, "\\hline \n");
    
    fprintf(uncFileSummaryV2, "Total ");
    for(int iSR=0; iSR<nSRs; iSR++){
      fprintf(uncFileSummaryV2, " & %.1f\\%% ", cats_vs_sys[iSR][nSys_unique-1]);
    }
  
    fprintf(uncFileSummaryV2, "\\"); fprintf(uncFileSummaryV2, "\\ \\hline \n");
    fprintf(uncFileSummaryV2, "\\end{tabular} \n");
    fprintf(uncFileSummaryV2, "} \n");
    fprintf(uncFileSummaryV2, "\\end{table} \n");
    fprintf(uncFileSummaryV2, "\\end{document} \n");
    fclose(uncFileSummaryV2);
  
      
    // Table of background estimate
    fprintf(yFile, "\\end{tabular} \n");
    fprintf(yFile, "} \n");
    fprintf(yFile, "\\end{table} \n");
    fprintf(yFile, "\\end{document} \n");
    fclose(yFile);
    

    // Uncertainty file for each category
    fprintf(uncFile, "\\end{document} \n");
    fclose(uncFile);
  
    // Write and Close Root File for Limit Setting
    f_out->Write();
    f_out->Close();
  
  
  } // end loop over bkgEstimate yields
  
  
  //
  // Clean up
  //
  f_SR_mc->Close();
  
  return 0;
}
