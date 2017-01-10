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

  bool forceOneTF;
  bool useFractionInCR;
  
  vector<int> SR_bins;
  vector<int> CR_bins;

  vector<bool> use_mc;
  vector<double> err_mc;
  
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
int bkgEstimate_diLepton(){


  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  
  //
  // Configuration Variables
  //
  bool doRescale     = false; // also triggers using psuedo-data, ie sum of allBkg
  double rescale     = 1.0; // use lumi from stopCORE
  //double rescale     = 40.0/29.53; // rescale to new lumi

  TString regionName_SR = "SR";
  TString regionName_CR = "CR2l";
  
   
  //
  // Open Files
  //
  TString inDir  = "Output/Histos/";
  TString outDir = "Output/BkgEstimate/";

  TFile *f_SR_mc = new TFile(inDir+"allBkg_25ns.root", "read");
  TFile *f_CR_mc = new TFile(inDir+"allBkg_25ns.root", "read");
  TFile *f_CR_data = NULL;
  if( doRescale ){
    f_CR_data= new TFile(inDir+"allBkg_25ns.root", "read");
  }
  else{
    f_CR_data = new TFile(inDir+"data_single_lepton_met.root", "read");
  }
  
  genClassyInfo::Util genClassy_ge2lep( genClassyInfo::k_ge2lep );
  genClassyInfo::Util genClassy_incl( genClassyInfo::k_incl );
  
  

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
  systematicList.push_back( sysInfo::Util(sysInfo::k_metResUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_metResDown) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_ttbarSysPtUp) );
  //systematicList.push_back( sysInfo::Util(sysInfo::k_ttbarSysPtDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_pdfUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_pdfDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_alphasUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_alphasDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_q2Up) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_q2Down) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_cr2lTriggerUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_cr2lTriggerDown) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_ISRUp) );
  systematicList.push_back( sysInfo::Util(sysInfo::k_ISRDown) );
  
  const int nSys = (int)systematicList.size();


  // Impurity Level, in case of using MC fraction in CR
  double impurity_sys = 0.5; // 50%


  //
  // List of scenarios for bkg estimates
  //
  std::vector<bkgEstUtil> v_bkgEst;
  

  //
  // ICHEP results
  //
  bkgEstUtil bkgEst_ICHEP;

  bkgEst_ICHEP.outName_base = "bkgEst_lostLepton__ICHEP_bins";
  bkgEst_ICHEP.hName_base = "h_yields_SR_ICHEP";
  bkgEst_ICHEP.forceOneTF = false;
  bkgEst_ICHEP.useFractionInCR = false;

  // 2jet, modTopness
  bkgEst_ICHEP.SR_bins.push_back(1);  bkgEst_ICHEP.CR_bins.push_back(1);  
  bkgEst_ICHEP.regionName.push_back("$2$jets,~tmod$\\ge6.4$"); 
  bkgEst_ICHEP.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(2);  bkgEst_ICHEP.CR_bins.push_back(2);  
  bkgEst_ICHEP.regionName.push_back("$2$jets,~tmod$\\ge6.4$");
  bkgEst_ICHEP.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(3);  bkgEst_ICHEP.CR_bins.push_back(3);  
  bkgEst_ICHEP.regionName.push_back("$2$jets,~tmod$\\ge6.4$");  
  bkgEst_ICHEP.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>450$");

  // 3jet, mt2w
  bkgEst_ICHEP.SR_bins.push_back(4);  bkgEst_ICHEP.CR_bins.push_back(4);  
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(5);  bkgEst_ICHEP.CR_bins.push_back(5);  
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(6);  bkgEst_ICHEP.CR_bins.push_back(23); // Extrapolate
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP.SR_bins.push_back(7);  bkgEst_ICHEP.CR_bins.push_back(23); // Extrapolate
  bkgEst_ICHEP.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>550$");
  
  // 4jet, low mt2w
  bkgEst_ICHEP.SR_bins.push_back(8);  bkgEst_ICHEP.CR_bins.push_back(8);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(9);  bkgEst_ICHEP.CR_bins.push_back(9);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(10);  bkgEst_ICHEP.CR_bins.push_back(10);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>450$");
  
  // 4jet, low mt2w
  bkgEst_ICHEP.SR_bins.push_back(11);  bkgEst_ICHEP.CR_bins.push_back(11);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP.SR_bins.push_back(12);  bkgEst_ICHEP.CR_bins.push_back(12);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP.SR_bins.push_back(13);  bkgEst_ICHEP.CR_bins.push_back(13);  
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP.SR_bins.push_back(14);  bkgEst_ICHEP.CR_bins.push_back(29);  // Extrapolate
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$550<MET<650$");
  
  bkgEst_ICHEP.SR_bins.push_back(15);  bkgEst_ICHEP.CR_bins.push_back(29);  // Extrapolate
  bkgEst_ICHEP.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP.binName.push_back("$MET>650$");
  
  
  v_bkgEst.push_back( bkgEst_ICHEP );


  //
  // ICHEP results, extended to 30fb
  //
  bkgEstUtil bkgEst_ICHEP_ext30fb;

  bkgEst_ICHEP_ext30fb.outName_base = "bkgEst_lostLepton__ICHEP_ext30fb_bins";
  bkgEst_ICHEP_ext30fb.hName_base = "h_yields_SR_ICHEP_ext30fb";
  bkgEst_ICHEP_ext30fb.forceOneTF = false;
  bkgEst_ICHEP_ext30fb.useFractionInCR = false;

  // 2jet, modTopness
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(1);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(1);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~tmod$\\ge6.4$"); 
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(2);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(2);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~tmod$\\ge6.4$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(3);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(3);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~tmod$\\ge6.4$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(4);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(22);  // Extrapolate
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~tmod$\\ge6.4$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(5);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(22);  // Extrapolate  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$2$jets,~tmod$\\ge6.4$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$2$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>650$");

  // 3jet, mt2w
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(6);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(6);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(7);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(7);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(8);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(8); 
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(9);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(9); // No Extrapolation, but if so bin=23
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");
    
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(10);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(10); // No Extrapolation, but if so bin=23
  bkgEst_ICHEP_ext30fb.regionName.push_back("$3$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$3$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>650$");
  
  // 4jet, low mt2w
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(11);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(11);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(12);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(12);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(13);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(13);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(14);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(24);  // Extrapolate
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(15);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(24);  // Extrapolate
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$<200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>450$");
  
  // 4jet, high mt2w
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(16);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(16);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$250<MET<350$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(17);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(17);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$350<MET<450$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(18);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(18);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$450<MET<550$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(19);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(19);  
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$550<MET<650$");

  bkgEst_ICHEP_ext30fb.SR_bins.push_back(20);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(25);  // Extrapolate
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$650<MET<800$");
  
  bkgEst_ICHEP_ext30fb.SR_bins.push_back(21);  bkgEst_ICHEP_ext30fb.CR_bins.push_back(25);  // Extrapolate
  bkgEst_ICHEP_ext30fb.regionName.push_back("$\\ge4$jets,~MT2W$\\ge200$");  
  bkgEst_ICHEP_ext30fb.regionName_short.push_back("$4$jets"); 
  bkgEst_ICHEP_ext30fb.binName.push_back("$MET>800$");
  
  
  v_bkgEst.push_back( bkgEst_ICHEP_ext30fb );
  


  //
  // Dev, ext30fb,  mlb
  //
  bkgEstUtil bkgEst_ext30fb_mlb;
 
  // met extrapolation
  bkgEst_ext30fb_mlb.outName_base = "bkgEst_lostLepton__mlb_v1_bins";
  bkgEst_ext30fb_mlb.hName_base = "h_yields_SR_dev_ext30fb_mlb_v1";
  bkgEst_ext30fb_mlb.forceOneTF = false;
  bkgEst_ext30fb_mlb.useFractionInCR = false;

  // Region A
  bkgEst_ext30fb_mlb.SR_bins.push_back(1);  bkgEst_ext30fb_mlb.CR_bins.push_back(1);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(2);  bkgEst_ext30fb_mlb.CR_bins.push_back(2);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<500$");
  
  bkgEst_ext30fb_mlb.SR_bins.push_back(3);  bkgEst_ext30fb_mlb.CR_bins.push_back(3);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>500$");
  
  // Region B
  bkgEst_ext30fb_mlb.SR_bins.push_back(4);  bkgEst_ext30fb_mlb.CR_bins.push_back(4);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(5);  bkgEst_ext30fb_mlb.CR_bins.push_back(5);  
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(6);  bkgEst_ext30fb_mlb.CR_bins.push_back(6);  // No Extrapolation, if so bin=30
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<650$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(7);  bkgEst_ext30fb_mlb.CR_bins.push_back(7);  // No Extrapolation, if so bin=30
  bkgEst_ext30fb_mlb.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>650$");

  // Region C
  bkgEst_ext30fb_mlb.SR_bins.push_back(8);  bkgEst_ext30fb_mlb.CR_bins.push_back(8);  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(9);  bkgEst_ext30fb_mlb.CR_bins.push_back(9);  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(10);  bkgEst_ext30fb_mlb.CR_bins.push_back(10);  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(11);  bkgEst_ext30fb_mlb.CR_bins.push_back(31); // Extrapolate  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(12);  bkgEst_ext30fb_mlb.CR_bins.push_back(31); // Extrapolate  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>650$");

  // Region D
  bkgEst_ext30fb_mlb.SR_bins.push_back(13);  bkgEst_ext30fb_mlb.CR_bins.push_back(13);  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(14);  bkgEst_ext30fb_mlb.CR_bins.push_back(14);  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(15);  bkgEst_ext30fb_mlb.CR_bins.push_back(15); // No Extrapolation, if so bin=32
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(16);  bkgEst_ext30fb_mlb.CR_bins.push_back(16); // No Extrapolation, if so bin=32
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>550$");

  // Region E
  bkgEst_ext30fb_mlb.SR_bins.push_back(17);  bkgEst_ext30fb_mlb.CR_bins.push_back(17);  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(18);  bkgEst_ext30fb_mlb.CR_bins.push_back(33); // Extrapolation, if so, bin=33
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<550$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(19);  bkgEst_ext30fb_mlb.CR_bins.push_back(33); // Extrapolattion, if so, bin=33
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>550$");
  
  // Region F
  bkgEst_ext30fb_mlb.SR_bins.push_back(20);  bkgEst_ext30fb_mlb.CR_bins.push_back(20); 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(21);  bkgEst_ext30fb_mlb.CR_bins.push_back(34);  // Extrapolation, if so, bin=34 
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(22);  bkgEst_ext30fb_mlb.CR_bins.push_back(34); // Extrapolation, if so, bin=34  
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>500$");

  // Region G
  bkgEst_ext30fb_mlb.SR_bins.push_back(23);  bkgEst_ext30fb_mlb.CR_bins.push_back(23);
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(24);  bkgEst_ext30fb_mlb.CR_bins.push_back(24);
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(25);  bkgEst_ext30fb_mlb.CR_bins.push_back(25); // No Extrapolation, if so, bin=35
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(26);  bkgEst_ext30fb_mlb.CR_bins.push_back(26); // No Extrapolation, if so, bin=35
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>600$");
  
  // Region H
  bkgEst_ext30fb_mlb.SR_bins.push_back(27);  bkgEst_ext30fb_mlb.CR_bins.push_back(27);
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb.binName.push_back("$250<MET<350$");
 
  bkgEst_ext30fb_mlb.SR_bins.push_back(28);  bkgEst_ext30fb_mlb.CR_bins.push_back(36); // Extrapolate
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb.binName.push_back("$350<MET<650$");

  bkgEst_ext30fb_mlb.SR_bins.push_back(29);  bkgEst_ext30fb_mlb.CR_bins.push_back(36); // Extrapolate
  bkgEst_ext30fb_mlb.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb.binName.push_back("$MET>650$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_mlb );

  

  //
  // Dev, ext30fb,  mlb, using inclusive mlb bins
  //
  bkgEstUtil bkgEst_ext30fb_mlb_inclMlbBins;
 
  // mlb extrapolation
  bkgEst_ext30fb_mlb_inclMlbBins.outName_base = "bkgEst_lostLepton__mlb_v1_inclMlb_bins";
  bkgEst_ext30fb_mlb_inclMlbBins.hName_base = "h_yields_SR_dev_ext30fb_mlb_v1";
  bkgEst_ext30fb_mlb_inclMlbBins.forceOneTF = false;
  bkgEst_ext30fb_mlb_inclMlbBins.useFractionInCR = false;

  // Region A
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(1);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(44);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(2);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(45);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(3);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(46);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>500$");
  
  // Region B
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(4);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(44);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(5);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(47);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(6);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(48);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$450<MET<650$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(7);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(49);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>650$");

  // Region C
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(8);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(51);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(9);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(52);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(10);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(53);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(11);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(54);   
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(12);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(55);   
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>650$");

  // Region D
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(13);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(51);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(14);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(52);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(15);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(53); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(16);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(56); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>550$");

  // Region E
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(17);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(58);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(18);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(59); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<550$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(19);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(60); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>550$");

  // Region F
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(20);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(58);   
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(21);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(61);   
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(22);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(62);  
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>500$");

  // Region G
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(23);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(64);
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(24);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(65);
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(25);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(66); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(26);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(67); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>600$");

  // Region H
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(27);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(64);
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$250<MET<350$");
 
  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(28);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(68); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$350<MET<650$");

  bkgEst_ext30fb_mlb_inclMlbBins.SR_bins.push_back(29);  bkgEst_ext30fb_mlb_inclMlbBins.CR_bins.push_back(69); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_inclMlbBins.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_inclMlbBins.binName.push_back("$MET>650$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_mlb_inclMlbBins );



  //
  // Dev, ext30fb,  mlb with tight bTagging
  //
  bkgEstUtil bkgEst_ext30fb_mlb_v2;
 
  // met extrapolation
  bkgEst_ext30fb_mlb_v2.outName_base = "bkgEst_lostLepton__mlb_v2_bins";
  bkgEst_ext30fb_mlb_v2.hName_base = "h_yields_SR_dev_ext30fb_mlb_v2";
  bkgEst_ext30fb_mlb_v2.forceOneTF = false;
  bkgEst_ext30fb_mlb_v2.useFractionInCR = false;

  // Region A
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(1);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(1);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(2);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(2);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");
  
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(3);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(3);  // No Extrapolation, if so bin=28
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<600$");
  
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(4);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(4);  // No Extrapolation, if so bin=28
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>600$");
  
  // Region B
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(5);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(29);  // Yes Extrapolation, if so bin=29
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(6);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(29);  // Yes Extrapolation, if so bin=29
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(7);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(29);  // Yes Extrapolation, if so bin=29
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>600$");

  // Region C
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(8);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(8);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(9);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(9);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(10);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(10);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C");   bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(11);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(11); // No Extrapolation, if so bin=30
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(12);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(12); // No Extrapolation, if so bin=30
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>650$");

  // Region D
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(13);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(13);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(14);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(14);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(15);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(15); // No Extrapolation, if so bin=31
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(16);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(16); // No Extrapolation, if so bin=31
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>550$");

  // Region E
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(17);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(17);  
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(18);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(32); // Yes Extrapolation, if so, bin=32
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<550$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(19);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(32); // Yes Extrapolation, if so, bin=32
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>550$");

  // Region F
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(20);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(33); // Yes Extrapolation, if so, bin=33 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(21);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(33); // Yes Extrapolation, if so, bin=33 
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>450$");

  // Region G
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(22);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(22);
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(23);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(23);
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(24);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(24); // No Extrapolation, if so, bin=34
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(25);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(25); // No Extrapolation, if so, bin=34
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>600$");

  // Region H
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(26);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(35);  // Yes Extrapolation, if so, bin=35
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$250<MET<450$");
 
  bkgEst_ext30fb_mlb_v2.SR_bins.push_back(27);  bkgEst_ext30fb_mlb_v2.CR_bins.push_back(35); // Yes Extrapolation, if, bin=35
  bkgEst_ext30fb_mlb_v2.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2.binName.push_back("$MET>450$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_mlb_v2 );


  //
  // Dev, ext30fb,  mlb with tight bTagging
  //
  bkgEstUtil bkgEst_ext30fb_mlb_v2_useCRfrac;
 
  // met extrapolation
  bkgEst_ext30fb_mlb_v2_useCRfrac.outName_base = "bkgEst_lostLepton__mlb_v2_bins_useCRfraction";
  bkgEst_ext30fb_mlb_v2_useCRfrac.hName_base = "h_yields_SR_dev_ext30fb_mlb_v2";
  bkgEst_ext30fb_mlb_v2_useCRfrac.forceOneTF = false;
  bkgEst_ext30fb_mlb_v2_useCRfrac.useFractionInCR = true;

  // Region A
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(1);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(1);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(2);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(2);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$350<MET<450$");
  
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(3);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(3);  // No Extrapolation, if so bin=28
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$450<MET<600$");
  
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(4);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(4);  // No Extrapolation, if so bin=28
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>600$");
  
  // Region B
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(5);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(29);  // Yes Extrapolation, if so bin=29
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(6);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(29);  // Yes Extrapolation, if so bin=29
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(7);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(29);  // Yes Extrapolation, if so bin=29
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>600$");

  // Region C
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(8);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(8);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(9);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(9);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(10);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(10);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("C");   bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(11);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(11); // No Extrapolation, if so bin=30
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(12);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(12); // No Extrapolation, if so bin=30
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>650$");

  // Region D
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(13);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(13);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(14);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(14);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(15);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(15); // No Extrapolation, if so bin=31
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(16);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(16); // No Extrapolation, if so bin=31
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>550$");

  // Region E
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(17);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(17);  
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(18);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(32); // Yes Extrapolation, if so, bin=32
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$350<MET<550$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(19);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(32); // Yes Extrapolattion, if so, bin=32
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>550$");

  // Region F
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(20);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(33); // Yes Extrapolation, if so, bin=33 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(21);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(33); // Yes Extrapolation, if so, bin=33 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>450$");

  // Region G
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(22);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(22);
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(23);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(23);
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(24);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(24); // No Extrapolation, if so, bin=34
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(25);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(25); // No Extrapolation, if so, bin=34
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>600$");

  // Region H
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(26);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(35);  // Yes Extrapolation, if so, bin=35
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$250<MET<450$");
 
  bkgEst_ext30fb_mlb_v2_useCRfrac.SR_bins.push_back(27);  bkgEst_ext30fb_mlb_v2_useCRfrac.CR_bins.push_back(35); // Yes Extrapolation, if, bin=35
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2_useCRfrac.binName.push_back("$MET>450$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_mlb_v2_useCRfrac );



  //
  // Dev, ext30fb,  mlb with tight bTagging
  //
  bkgEstUtil bkgEst_ext30fb_mlb_v2_inclMlbBins;
 
  // mlb extrapolation
  bkgEst_ext30fb_mlb_v2_inclMlbBins.outName_base = "bkgEst_lostLepton__mlb_v2_inclMlb_bins";
  bkgEst_ext30fb_mlb_v2_inclMlbBins.hName_base = "h_yields_SR_dev_ext30fb_mlb_v2";
  bkgEst_ext30fb_mlb_v2_inclMlbBins.forceOneTF = true;
  bkgEst_ext30fb_mlb_v2_inclMlbBins.useFractionInCR = false;

  // Region A
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(1);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(43);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(2);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(44);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$350<MET<450$");
  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(3);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(45);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$450<MET<600$");
  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(4);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(46); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>600$");
  
  // Region B
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(5);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(47);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(6);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(48); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(7);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(49);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>600$");

  // Region C
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(8);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(51);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(9);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(52);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(10);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(53);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("C");   bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(11);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(54); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(12);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(55); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>650$");

  // Region D
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(13);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(51);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(14);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(52);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(15);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(53); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(16);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(56); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>550$");

  // Region E
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(17);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(58);  
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(18);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(59); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$350<MET<550$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(19);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(60); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>550$");

  // Region F
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(20);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(61); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<450$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(21);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(62); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>450$");

  // Region G
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(22);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(64);
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(23);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(65);
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(24);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(66); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(25);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(67); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb<175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>600$");

  // Region H
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(26);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(68); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$250<MET<450$");
 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.SR_bins.push_back(27);  bkgEst_ext30fb_mlb_v2_inclMlbBins.CR_bins.push_back(69); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$mlb\\ge175$"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.regionName_short.push_back("H"); 
  bkgEst_ext30fb_mlb_v2_inclMlbBins.binName.push_back("$MET>450$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_mlb_v2_inclMlbBins );



  //
  // Dev, ext30fb,  bJetPt
  //
  bkgEstUtil bkgEst_ext30fb_bJetPt;
 
  bkgEst_ext30fb_bJetPt.outName_base = "bkgEst_lostLepton__bJetPt_v1_bins";
  bkgEst_ext30fb_bJetPt.hName_base = "h_yields_SR_dev_ext30fb_bJetPt_v1";
  bkgEst_ext30fb_bJetPt.forceOneTF = false;
  bkgEst_ext30fb_bJetPt.useFractionInCR = false;

  // Region A
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(1);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(1);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(2);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(2);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(3);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(3);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(4);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(4);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>600$");
  
  // Region B
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(5);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(5);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(6);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(6);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(7);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(30);  // Extrapolation, if so bin=30
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$500<MET<650$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(8);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(30);  // Extrapolation  , if so bin=30
  bkgEst_ext30fb_bJetPt.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>650$");

  // Region C
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(9);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(9);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(10);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(10);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(11);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(11);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(12);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(12); // No Extrapolation, if so bin=31
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(13);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(13); // No Extrapolation, if so bin=31
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>650$");

  // Region D
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(14);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(14);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(15);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(15);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(16);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(32); // Extrapolate  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(17);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(32); // Extrapolate  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>550$");

  // Region E
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(18);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(18);  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(19);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(19); // No Extrapolation, if so bin=33
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(20);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(20); // No Extrapolation, if so bin=33
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>450$");

  // Region F
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(21);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(21);   
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(22);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(34); // Extrapolate  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(23);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(34); // Extrapolate  
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>500$");

  // Region G
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(24);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(24);
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(25);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(25);
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(26);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(35); // Extrapolate
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$450<MET<650$");

  bkgEst_ext30fb_bJetPt.SR_bins.push_back(27);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(35); // Extrapolate
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>650$");
  
  // Region H
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(28);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(28); // No Extrapolation, if so, bin=36
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("H"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$250<MET<450$");
 
  bkgEst_ext30fb_bJetPt.SR_bins.push_back(29);  bkgEst_ext30fb_bJetPt.CR_bins.push_back(29);  // No Extrapolation, if so, bin=36
  bkgEst_ext30fb_bJetPt.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt.regionName_short.push_back("H"); 
  bkgEst_ext30fb_bJetPt.binName.push_back("$MET>450$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_bJetPt );
  


  //
  // Dev, ext30fb,  bJetPt, using inclusive bJetPt bins
  //
  bkgEstUtil bkgEst_ext30fb_bJetPt_inclBJetPtBins;
 
  // bJetPt Extrapolation
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.outName_base = "bkgEst_lostLepton__bJetPt_v1_inclBJetPt_bins";
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.hName_base = "h_yields_SR_dev_ext30fb_bJetPt_v1";
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.forceOneTF = true;
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.useFractionInCR = false;

  // Region A
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(1);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(44);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(2);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(45);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(3);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(46);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$450<MET<600$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(4);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(47);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("A"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>600$");
  

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(5);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(44);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(6);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(48);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(7);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(49);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$500<MET<650$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(8);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(50);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$<4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("B"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>650$");

  // Region C
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(9);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(52);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(10);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(53);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(11);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(54);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(12);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(55); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$550<MET<650$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(13);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(56); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("C"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>650$");

  // Region D
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(14);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(52);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(15);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(53);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(16);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(54);   
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$450<MET<550$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(17);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(57);   
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$<0.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("D"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>550$");

  // Region E
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(18);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(59);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(19);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(60); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(20);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(61); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("E"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>450$");

  // Region F
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(21);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(59);   
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(22);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(62);   
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$350<MET<500$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(23);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(63);  
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~$0.0<$tmod$<10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("F"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>500$");

  // Region G
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(24);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(65);
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<350$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(25);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(66);
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$350<MET<450$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(26);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(67); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$450<MET<650$");

  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(27);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(68); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt<200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("G"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>650$");
  
  // Region H
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(28);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(69);
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("H"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$250<MET<450$");
 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.SR_bins.push_back(29);  bkgEst_ext30fb_bJetPt_inclBJetPtBins.CR_bins.push_back(70); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName.push_back("$\\ge4$jets,~tmod$\\ge10.0$,~$bJetPt\\ge200$"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.regionName_short.push_back("H"); 
  bkgEst_ext30fb_bJetPt_inclBJetPtBins.binName.push_back("$MET>650$");
 
  
  v_bkgEst.push_back( bkgEst_ext30fb_bJetPt_inclBJetPtBins );
  


  //
  // corridor results
  //
  bkgEstUtil bkgEst_corridor;

  bkgEst_corridor.outName_base = "bkgEst_lostLepton__corridor_bins";
  bkgEst_corridor.hName_base = "h_yields_SR_corridor";
  bkgEst_corridor.forceOneTF = false;
  bkgEst_corridor.useFractionInCR = false;

  bkgEst_corridor.SR_bins.push_back(1);  bkgEst_corridor.CR_bins.push_back(1);  
  bkgEst_corridor.regionName.push_back("top~corridor"); 
  bkgEst_corridor.regionName_short.push_back("corridor"); 
  bkgEst_corridor.binName.push_back("$250<MET<350$");
  
  bkgEst_corridor.SR_bins.push_back(2);  bkgEst_corridor.CR_bins.push_back(2);  
  bkgEst_corridor.regionName.push_back("top~corridor");
  bkgEst_corridor.regionName_short.push_back("corridor"); 
  bkgEst_corridor.binName.push_back("$350<MET<450$");

  bkgEst_corridor.SR_bins.push_back(3);  bkgEst_corridor.CR_bins.push_back(3);  
  bkgEst_corridor.regionName.push_back("top~corridor");
  bkgEst_corridor.regionName_short.push_back("corridor"); 
  bkgEst_corridor.binName.push_back("$450<MET<550$");
  
  bkgEst_corridor.SR_bins.push_back(4);  bkgEst_corridor.CR_bins.push_back(4);  
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

    // Bool to use fraction of data
    bool useFraction = v_bkgEst[iBkgEst].useFractionInCR;

    // Get number of signal regions
    const int nSRs = (int)v_bkgEst[iBkgEst].SR_bins.size();
    
    // Check if there is any extrapolation, to properly format tables
    bool oneTF = true;
    for(int iSR=0; iSR<nSRs; iSR++){
      if( v_bkgEst[iBkgEst].SR_bins[iSR] != v_bkgEst[iBkgEst].CR_bins[iSR] ){
	oneTF = false;
	break;
      }
    }
    if( v_bkgEst[iBkgEst].forceOneTF ) oneTF=true;

    
    //
    // Root File with Histos of Bkg Estimate for Limit Setting
    //
    TString root_fileName = outDir;
    root_fileName += outNameBase;
    root_fileName += "__histos.root";
    TFile  *f_out = new TFile(root_fileName.Data(), "recreate");
    
    // Count Additional Systematics
    int additional_sys = 4; // +2 for data stats up/down, +2 for mc status up/down
    if(useFraction) additional_sys += 2; // +2 for impurity 

    // Total Systematics
    const int nSys_histos = nSys + additional_sys; 

    // Histos for Limit Setting and Additional Systematics
    TH1D *h_SR[nSys_histos];
    h_SR[0] = new TH1D(regionName_CR+"_yield",       regionName_CR+"_yield",       nSRs, 0.0, nSRs); // Nominal
    h_SR[1] = new TH1D(regionName_CR+"_dataStatsUp", regionName_CR+"_dataStatsUp", nSRs, 0.0, nSRs); // data stats up
    h_SR[2] = new TH1D(regionName_CR+"_dataStatsDn", regionName_CR+"_dataStatsDn", nSRs, 0.0, nSRs); // data stats dn
    h_SR[3] = new TH1D(regionName_CR+"_mcStatsUp",   regionName_CR+"_mcStatsUp",   nSRs, 0.0, nSRs); // mc stats up
    h_SR[4] = new TH1D(regionName_CR+"_mcStatsDn",   regionName_CR+"_mcStatsDn",   nSRs, 0.0, nSRs); // mc stats dn
    if(useFraction){
      h_SR[5] = new TH1D(regionName_CR+"_impurityUp",   regionName_CR+"_impurityUp",   nSRs, 0.0, nSRs); // impurity up
      h_SR[6] = new TH1D(regionName_CR+"_impurityDn",   regionName_CR+"_impurityDn",   nSRs, 0.0, nSRs); // impurity dn
    }

    for(int iCat=0; iCat<(int)nSRs; iCat++){
      
      TString binName = v_bkgEst[iBkgEst].regionName[iCat];
      binName += "__";
      binName += v_bkgEst[iBkgEst].binName[iCat];

      h_SR[0]->GetXaxis()->SetBinLabel( iCat+1, binName );
      h_SR[1]->GetXaxis()->SetBinLabel( iCat+1, binName );
      h_SR[2]->GetXaxis()->SetBinLabel( iCat+1, binName );
      h_SR[3]->GetXaxis()->SetBinLabel( iCat+1, binName );
      h_SR[4]->GetXaxis()->SetBinLabel( iCat+1, binName );
      if(useFraction){
	h_SR[5]->GetXaxis()->SetBinLabel( iCat+1, binName );
	h_SR[6]->GetXaxis()->SetBinLabel( iCat+1, binName );
      }
    }

    h_SR[0]->SetDirectory(f_out);
    h_SR[1]->SetDirectory(f_out);
    h_SR[2]->SetDirectory(f_out);
    h_SR[3]->SetDirectory(f_out);
    h_SR[4]->SetDirectory(f_out);
    if(useFraction){
      h_SR[5]->SetDirectory(f_out);
      h_SR[6]->SetDirectory(f_out);
    }

    // Systematics for limit setting from List
    for(int iSys=1; iSys<nSys; iSys++){

      h_SR[iSys+additional_sys] = new TH1D(Form("%s_%s", regionName_CR.Data(), systematicList[iSys].label.c_str()), Form("%s_%s", regionName_CR.Data(), systematicList[iSys].label.c_str()), nSRs, 0.0, nSRs);   

      for(int iCat=0; iCat<(int)nSRs; iCat++){

	TString binName = v_bkgEst[iBkgEst].regionName[iCat];
	binName += "__";
	binName += v_bkgEst[iBkgEst].binName[iCat];
	
	h_SR[iSys+additional_sys]->GetXaxis()->SetBinLabel( iCat+1, binName );
      }
      h_SR[iSys+additional_sys]->SetDirectory(f_out);
    }



    //
    // LaTeX Tables with Results
    //

    // Results, 1 table for all categories
    //   ROW=Categories, COL=Lost Lepton Estimate and Components
    FILE *f_results;
    TString f_results_name = outDir;
    f_results_name += outNameBase;
    f_results_name += "__resultsTable.tex";
    f_results = fopen(f_results_name.Data(), "w");
    
    cout << "Writing Table of Lost Lepton Estimates to file; " << endl;
    cout << "    " << f_results_name << endl;

    printLatexHeader(f_results);
    fprintf(f_results, "\\tiny \n");  
    fprintf(f_results, "\\begin{table} \n");
    fprintf(f_results, "\\caption{ Lost Lepton Background Estimate, for each Signal Region } \n");
    fprintf(f_results, "\\scalebox{1.0}{ \n");

    fprintf(f_results, "\\begin{tabular}{|l|c|c|"); // Region, MET bin, Data Yield CR
    if(useFraction) fprintf(f_results, "c|");       // MC Fraction to apply to data
    fprintf(f_results, "c|");                       // TF_cr2sr
    if(!oneTF) fprintf(f_results, "c|c|");          // TF_srBin, TF_tot
    fprintf(f_results, "c|");                       // SR Estimate
    fprintf(f_results, "} \\hline \n");

    fprintf(f_results, "Region & MET bin & $Observed_{CR}$");
    if(useFraction) fprintf(f_results, " & $MC_{CR}^{2\\ell~frac}$");
    fprintf(f_results, " & $TF_{lepton}$");
    if(!oneTF) fprintf(f_results, " & $TF_{SR~bin}$ & $TF_{Total}$");
    fprintf(f_results, " & $SR~Estimate$");
    fprintf(f_results, " \\"); fprintf(f_results, "\\ \\hline \\hline \n");
    


    // Uncertainty table, with full details of calculation, one table per category
    //   ROW=Uncertainties, COL=DiLepton Estimate and Components
    FILE *f_uncFile_fullCalc = NULL;
    TString f_uncFile_fullCalc_name = outDir;
    f_uncFile_fullCalc_name += outNameBase;
    f_uncFile_fullCalc_name += "__uncertaintyTable__fullCalculation.tex";
    f_uncFile_fullCalc = fopen(f_uncFile_fullCalc_name.Data(), "w");
    
    cout << "Writing table of diLepton uncertainties to: " << endl;
    cout << "    " << f_uncFile_fullCalc_name << endl;

    printLatexHeader(f_uncFile_fullCalc);
    

    
    // Uncertainty Table, Summary of components over all Categories
    //   ROW=Uncertainty ranges by %, over all cateogries, COL=DiLepton Estimate and Components
    FILE *f_uncFile_summary;
    TString f_uncFile_summary_name = outDir;
    f_uncFile_summary_name += outNameBase;
    f_uncFile_summary_name += "__uncertaintyTable__summary.tex";
    f_uncFile_summary = fopen(f_uncFile_summary_name.Data(), "w");
    
    cout << "Writing Summary Table of Lost Lepton Uncertainties to: " << endl;
    cout << "    " << f_uncFile_summary_name << endl;
    
    printLatexHeader(f_uncFile_summary);
    fprintf(f_uncFile_summary, "\\begin{table} \n");
    fprintf(f_uncFile_summary, "\\caption{ Summary of Lost Lepton Background Estimate Uncertainties } \n");
    fprintf(f_uncFile_summary, "\\scalebox{0.7}{ \n");

    fprintf(f_uncFile_summary, "\\begin{tabular}{|l|c|"); // Systematic, Data Yield CR
    if(useFraction) fprintf(f_uncFile_summary, "c|");     // MC Fraction to apply to data
    fprintf(f_uncFile_summary, "c|");                     // TF_cr2sr
    if(!oneTF) fprintf(f_uncFile_summary, "c|c|");        // TF_srBin, TF_tot
    fprintf(f_uncFile_summary, "c|");                     // SR Estimate
    fprintf(f_uncFile_summary, "} \\hline \n");
    
    fprintf(f_uncFile_summary, "Systematic & $Observed_{CR},~(\\%%)$");
    if(useFraction) fprintf(f_uncFile_summary, "& $MC_{CR}^{2\\ell~frac},~(\\%%)$");
    fprintf(f_uncFile_summary, " & $TF_{lepton},~(\\%%)$");
    if(!oneTF) fprintf(f_uncFile_summary, " & $TF_{SR~Bin},~(\\%%)$ & $TF_{Total},~(\\%%)$");
    fprintf(f_uncFile_summary, " & $SR~Estimate,~(\\%%)$");
    fprintf(f_uncFile_summary, " \\"); fprintf(f_uncFile_summary, "\\ \\hline \\hline \n");
    

    // Need an arry of min/max, element for each systematic
    const int nSys_unique = ((nSys_histos-1)/2) + 1; // -1 for nominal, divide by 2 for unique, +1 for total uncertainty
    double uncMax_cr_data_cr2sr[nSys_unique]; 
    double uncMin_cr_data_cr2sr[nSys_unique];
    double uncMax_fraction[nSys_unique]; 
    double uncMin_fraction[nSys_unique];
    double uncMax_tf_cr2sr[nSys_unique]; 
    double uncMin_tf_cr2sr[nSys_unique];
    double uncMax_tf_srBin[nSys_unique]; 
    double uncMin_tf_srBin[nSys_unique];
    double uncMax_tf_tot[nSys_unique]; 
    double uncMin_tf_tot[nSys_unique];
    double uncMax_sr_estimate[nSys_unique]; 
    double uncMin_sr_estimate[nSys_unique];
    for(int iSys=0; iSys<nSys_unique; iSys++){
      uncMax_cr_data_cr2sr[iSys] = 0.0;
      uncMin_cr_data_cr2sr[iSys] = 999.9;
      uncMax_fraction[iSys] = 0.0;
      uncMin_fraction[iSys] = 999.9;
      uncMax_tf_cr2sr[iSys] = 0.0;
      uncMin_tf_cr2sr[iSys] = 999.9;
      uncMax_tf_srBin[iSys] = 0.0;
      uncMin_tf_srBin[iSys] = 999.9;
      uncMax_tf_tot[iSys] = 0.0;
      uncMin_tf_tot[iSys] = 999.9;
      uncMax_sr_estimate[iSys] = 0.0;
      uncMin_sr_estimate[iSys] = 999.9;
    }
    

      
    // Uncertainty summary table, 1 table with all categories
    //   ROWS=% Uncertainties on final estimate, COLS=Categories
    double cats_vs_sys[nSRs][nSys_unique];
    for(int iCat=0; iCat<nSRs; iCat++){
      for(int iSys=0; iSys<nSys_unique; iSys++){
	cats_vs_sys[iCat][iSys] = 0.0;
      }
    }
    
    FILE *f_uncFile_summaryByCat = NULL;
    TString f_uncFile_summaryByCat_name = outDir;
    f_uncFile_summaryByCat_name += outNameBase;
    f_uncFile_summaryByCat_name += "__uncertaintyTable__summary_byCategory.tex";
    f_uncFile_summaryByCat = fopen(f_uncFile_summaryByCat_name.Data(), "w");
    
    cout << "Writing table of diLepton uncertainties summary by cats to: " << endl;
    cout << "    " << f_uncFile_summaryByCat_name << endl;
    
    printLatexHeader(f_uncFile_summaryByCat);
    fprintf(f_uncFile_summaryByCat, "\\begin{table} \n");
    fprintf(f_uncFile_summaryByCat, "\\scalebox{0.3}{ \n");
    fprintf(f_uncFile_summaryByCat, "\\begin{tabular}{|l|");
    for(int iCat=0; iCat<nSRs; iCat++){
      fprintf(f_uncFile_summaryByCat, "c|");
    }
    fprintf(f_uncFile_summaryByCat, "} \\hline \n");
    
    fprintf(f_uncFile_summaryByCat, "Systematic ");
    for(int iCat=0; iCat<nSRs; iCat++){
      fprintf(f_uncFile_summaryByCat, " & %s ", v_bkgEst[iBkgEst].regionName_short[iCat].Data());
    }
    fprintf(f_uncFile_summaryByCat, "\\"); fprintf(f_uncFile_summaryByCat, "\\  \n");
    for(int iCat=0; iCat<nSRs; iCat++){
      TString modified_metLabel = v_bkgEst[iBkgEst].binName[iCat];
      modified_metLabel.ReplaceAll("<MET<","-");
      modified_metLabel.ReplaceAll("MET>",">");
      fprintf(f_uncFile_summaryByCat, " & %s ", modified_metLabel.Data());
    }
    fprintf(f_uncFile_summaryByCat, "\\"); fprintf(f_uncFile_summaryByCat, "\\ \\hline \\hline  \n");
  
    
        
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

      // Cateogry info for uncertainty table, for each category
      fprintf(f_uncFile_fullCalc, "\\begin{table} \n");
      fprintf(f_uncFile_fullCalc, "\\caption{ diLepton Background Estimate Uncertainties, for %s } \n", catName.Data());
      fprintf(f_uncFile_fullCalc, "\\scalebox{0.6}{ \n");
      fprintf(f_uncFile_fullCalc, "\\begin{tabular}{|l|c|c|"); // Systematic; Data Yield CR; MC Yield Incl. genClassy CR
      if(useFraction) fprintf(f_uncFile_fullCalc, "c|c|");     // MC Yield 2lep CR; MC Fraction to apply to data
      fprintf(f_uncFile_fullCalc, "c|c|");                     // MC Yield 2lep SR; TF_cr2sr
      if(!oneTF) fprintf(f_uncFile_fullCalc, "c|c|c|");        // if >1 TF, then SR bin, MC Yield 2lep SR bin; TF_srBin; TF_tot
      fprintf(f_uncFile_fullCalc, "c|");                       // SR Estimate
      fprintf(f_uncFile_fullCalc, "} \\hline \n");

      fprintf(f_uncFile_fullCalc, "Systematic & $Observed_{CR},~(\\%%)$ & $MC_{Incl}^{CR},~(\\%%)$");
      if(useFraction) fprintf(f_uncFile_fullCalc, " & $MC_{2\\ell}^{CR},~(\\%%)$ & $MC_{CR}^{2\\ell~frac},~(\\%%)$");
      if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & $MC_{2\\ell}^{SR~bin},~(\\%%)$ & $TF_{lepton},~(\\%%)$");
      else                             fprintf(f_uncFile_fullCalc, " & $MC_{2\\ell}^{SR},~(\\%%)$ & $TF_{lepton},~(\\%%)$");
      if(!oneTF) fprintf(f_uncFile_fullCalc, " & $MC_{2\\ell}^{SR~bin},~(\\%%)$ & $TF_{SR~Bin},~(\\%%)$ & $TF_{Total},~(\\%%)$");
      fprintf(f_uncFile_fullCalc, " & $SR~Estimate$");
      fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\ \\hline \\hline \n");


      
      //
      // Get yields, begin calculation for this cateogry
      //
      int SR_bin = v_bkgEst[iBkgEst].SR_bins[iSR];
      int CR_bin = v_bkgEst[iBkgEst].CR_bins[iSR];
      

      //
      // SR, category bin 
      //
      hName = hNameBase;
      hName += "__";
      hName += regionName_SR;
      hName += "__genClassy_";
      hName += genClassy_ge2lep.label;
      hName += "__systematic_";
      hName += nominal_sys.label;
      
      h_temp = (TH1D*)f_SR_mc->Get(hName);
      if(!h_temp) cout << "BAD SR CATEGORY BIN HISTO: " << hName << endl;

      double MC_SR_bin_yield = h_temp->GetBinContent( SR_bin );
      double MC_SR_bin_error = h_temp->GetBinError( SR_bin );
      
      if(doRescale){
	MC_SR_bin_error *= rescale;
	MC_SR_bin_yield *= rescale;
      }
      
      
      //
      // SR, mc, cr2sr bin
      //
      hName = hNameBase;
      hName += "__";
      hName += regionName_SR;
      hName += "__genClassy_";
      hName += genClassy_ge2lep.label;
      hName += "__systematic_";
      hName += nominal_sys.label;
      
      h_temp = (TH1D*)f_SR_mc->Get(hName);
      if(!h_temp) cout << "BAD SR CRtoSR bin HISTO: " << hName << endl;
      
      double MC_SR_cr2sr_yield = h_temp->GetBinContent( CR_bin );
      double MC_SR_cr2sr_error = h_temp->GetBinError( CR_bin );
      
      if(doRescale){
	MC_SR_cr2sr_error *= rescale;
	MC_SR_cr2sr_yield *= rescale;
      }
      
      
      //
      // CR, mc, cr2sr bin, ge2lep genClassy
      //
      hName = hNameBase;
      hName += "__";
      hName += regionName_CR;
      hName += "__genClassy_";
      hName += genClassy_ge2lep.label;
      hName += "__systematic_";
      hName += nominal_sys.label;
      
      h_temp = (TH1D*)f_CR_mc->Get(hName);
      if(!h_temp) cout << "BAD MC CR, ge2lep genClassy, CRtoSR bin HISTO: " << hName << endl;
      
      double MC_CR_cr2sr_ge2lep_yield = h_temp->GetBinContent( CR_bin);
      double MC_CR_cr2sr_ge2lep_error = h_temp->GetBinError( CR_bin );
    
      if(doRescale){
	MC_CR_cr2sr_ge2lep_error *= rescale;
	MC_CR_cr2sr_ge2lep_yield *= rescale;
      }


      //
      // CR, mc, cr2sr bin, incl genClassy
      //
      hName = hNameBase;
      hName += "__";
      hName += regionName_CR;
      hName += "__genClassy_";
      hName += genClassy_incl.label;
      hName += "__systematic_";
      hName += nominal_sys.label;
      
      h_temp = (TH1D*)f_CR_mc->Get(hName);
      if(!h_temp) cout << "BAD MC CR, incl genClassy, CRtoSR bin HISTO: " << hName << endl;
      
      double MC_CR_cr2sr_incl_yield = h_temp->GetBinContent( CR_bin);
      double MC_CR_cr2sr_incl_error = h_temp->GetBinError( CR_bin );
    
      if(doRescale){
	MC_CR_cr2sr_incl_error *= rescale;
	MC_CR_cr2sr_incl_yield *= rescale;
      }

      


      //
      // CR, data, cr2sr bin
      //
      hName = hNameBase;
      hName += "__";
      hName += regionName_CR;
      hName += "__genClassy_";
      hName += genClassy_incl.label;
      hName += "__systematic_";
      hName += nominal_sys.label;
      
      h_temp = (TH1D*)f_CR_data->Get(hName);
      if(!h_temp) cout << "BAD DATA CR CRtoSR bin HISTO: " << hName << endl;
      
      double Data_CR_cr2sr_yield = h_temp->GetBinContent( CR_bin );
      double Data_CR_cr2sr_error = sqrt( Data_CR_cr2sr_yield );
      
      if(doRescale){
	Data_CR_cr2sr_yield *= rescale;
	Data_CR_cr2sr_error = sqrt( Data_CR_cr2sr_yield );
      }
      
      
      //
      // CR, mc, cr2sr bin, non-ge2lep genClassy
      //
      double MC_CR_cr2sr_non_ge2lep_yield = 0.0;
      
      
      //
      // CR, mc, cr2sr bin, fraction of ge2lep
      //
      double MC_CR_fraction             = 1.0;
      double MC_CR_fraction_statErr     = 0.0;
      double MC_CR_fraction_err         = 0.0;
      double MC_CR_fraction_impurity_up = 1.0;
      double MC_CR_fraction_impurity_dn = 1.0;

      
      //
      // Transfer Factor SR/CR
      //
      double tf_cr2sr = 1.0;
      double tf_cr2sr_statErr = 0.0;
      double tf_cr2sr_err = 0.0;
      
      
      //
      // Transfer Factor SR_bin/SR_cr2sr
      //
      double tf_srBin = 1.0;
      double tf_srBin_statErr = 0.0;
      double tf_srBin_err = 0.0;
      

      //
      // Transfer Factor Total
      //
      double tf_tot = 1.0;
      double tf_tot_statErr = 0.0;
      double tf_tot_err = 0.0;
      

      //
      // Signal Region Estimate
      //
      double sr_estimate = 0.0;
      double sr_estimate_err_mc_stats = 0.0;
      double sr_estimate_err_data_stats = 0.0;
      double sr_estimate_err = 0.0;
      double sr_estimate_impurity_up = 0.0;
      double sr_estimate_impurity_dn = 0.0;
      
      //
      // Calculation if no extrapolation, ie SR_bin==CR_bin, or if forcing 1 TF
      //
      if( (v_bkgEst[iBkgEst].forceOneTF) || (SR_bin==CR_bin) ){
	
	//
	// Calculation if Using a Fraction Method with CR
	//
	if(useFraction){
	  
	  // If using fraction, get ge2lep CR MC yield
	  if(MC_CR_cr2sr_ge2lep_yield>0.0 && MC_SR_bin_yield>0.0){

	    // Get MC Non-ge2lep Yield
	    MC_CR_cr2sr_non_ge2lep_yield = MC_CR_cr2sr_incl_yield - MC_CR_cr2sr_ge2lep_yield;
	    
	    // Get MC Fraction of ge2lep
	    MC_CR_fraction             = ( MC_CR_cr2sr_ge2lep_yield ) / ( MC_CR_cr2sr_ge2lep_yield + MC_CR_cr2sr_non_ge2lep_yield );
	    MC_CR_fraction_statErr     = sqrt( ( ((1-2*MC_CR_fraction)*pow(MC_CR_cr2sr_ge2lep_error,2)) + (pow(MC_CR_fraction,2)*pow(MC_CR_cr2sr_incl_error,2)) ) / (pow(MC_CR_cr2sr_incl_yield,2)) ); // binomial uncertainty for multiple samples
	    MC_CR_fraction_err         = MC_CR_fraction_statErr;

	    // Get MC Fraction, varying impurity
	    MC_CR_fraction_impurity_up = ( MC_CR_cr2sr_ge2lep_yield ) / ( MC_CR_cr2sr_ge2lep_yield + ((1.0+impurity_sys)*MC_CR_cr2sr_non_ge2lep_yield) );
	    MC_CR_fraction_impurity_dn = ( MC_CR_cr2sr_ge2lep_yield ) / ( MC_CR_cr2sr_ge2lep_yield + ((1.0-impurity_sys)*MC_CR_cr2sr_non_ge2lep_yield) );
	    
	    // Get Transfer Factor SR/CR
	    tf_cr2sr = MC_SR_bin_yield/MC_CR_cr2sr_ge2lep_yield;
	    //tf_cr2sr_statErr = tf_cr2sr*sqrt( pow(MC_CR_cr2sr_ge2lep_error/MC_CR_cr2sr_ge2lep_yield,2) + pow(MC_SR_bin_error/MC_SR_bin_yield,2) );  // Gaussian Errors for each component
	    tf_cr2sr_statErr = tf_cr2sr*sqrt( pow(MC_SR_bin_error/MC_SR_bin_yield,2) );  // Gausisan Errors for MC_SR_bin_yield only to avoid double counting , since MC_CR_cr2sr_error is included in MC fraction error 
	    tf_cr2sr_err = tf_cr2sr_statErr;

	    // In This Case tf_tot=tf_cr2sr
	    tf_tot = tf_cr2sr;
	    tf_tot_statErr = tf_cr2sr_statErr;
	    tf_tot_err = tf_cr2sr_err;

	    // SR Estimate
	    sr_estimate = Data_CR_cr2sr_yield*MC_CR_fraction*tf_tot;
	    sr_estimate_err_mc_stats = sr_estimate*sqrt( pow(MC_CR_fraction_statErr/MC_CR_fraction,2) + pow(tf_tot_statErr/tf_tot,2) );
	    sr_estimate_err_data_stats = sr_estimate*sqrt( pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
	    sr_estimate_err = sr_estimate*sqrt( pow(MC_CR_fraction_statErr/MC_CR_fraction,2) + pow(tf_tot_statErr/tf_tot,2) + pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
	    sr_estimate_impurity_up = Data_CR_cr2sr_yield*MC_CR_fraction_impurity_up*tf_tot;
	    sr_estimate_impurity_dn = Data_CR_cr2sr_yield*MC_CR_fraction_impurity_dn*tf_tot;
            
	  }
	} // end if using fraction


	//
	// Calculation if not using fraction
	//
	else{
	  
	  // If not using fraction, get incl CR MC yield
	  if(MC_CR_cr2sr_incl_yield>0.0 && MC_SR_bin_yield>0.0){
	
	    // Transfer Factor SR/CR
	    tf_cr2sr = MC_SR_bin_yield/MC_CR_cr2sr_incl_yield;
	    tf_cr2sr_statErr = tf_cr2sr*sqrt( pow(MC_CR_cr2sr_incl_error/MC_CR_cr2sr_incl_yield,2) + pow(MC_SR_bin_error/MC_SR_bin_yield,2) ); 
	    tf_cr2sr_err = tf_cr2sr_statErr;
	    
	    // In This Case tf_tot=tf_cr2sr
	    tf_tot = tf_cr2sr;
	    tf_tot_statErr = tf_cr2sr_statErr;
	    tf_tot_err = tf_cr2sr_err;
	    
	    // Signal Region Estimate
	    sr_estimate = Data_CR_cr2sr_yield*tf_tot;
	    sr_estimate_err_mc_stats = sr_estimate*sqrt( pow(tf_tot_statErr/tf_tot,2) );
	    sr_estimate_err_data_stats = sr_estimate*sqrt( pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
	    sr_estimate_err = sr_estimate*sqrt( pow(tf_tot_statErr/tf_tot,2) + pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
	    
	  } // end if yields are positive

	} // end if not using fraction

      } // end if using one transfer fraction

      
      //
      // Calculation if using one TF for SR/CR and another TF SR_bin/SR, ie when extrapolation and SR!=SR_bin
      //
      else{

	//
	// Calculation if using fraction
	//
	if(useFraction){
	  
	  // If using fraction, get ge2lep CR MC yield
	  if(MC_CR_cr2sr_ge2lep_yield>0.0 && MC_SR_cr2sr_yield>0.0 && MC_SR_bin_yield>0.0){

	    // Get MC Non-ge2lep Yield
	    MC_CR_cr2sr_non_ge2lep_yield = MC_CR_cr2sr_incl_yield - MC_CR_cr2sr_ge2lep_yield;
	    
	    // Get MC Fraction of ge2lep
	    MC_CR_fraction             = ( MC_CR_cr2sr_ge2lep_yield ) / ( MC_CR_cr2sr_ge2lep_yield + MC_CR_cr2sr_non_ge2lep_yield );
	    MC_CR_fraction_statErr     = sqrt( ( ((1-2*MC_CR_fraction)*pow(MC_CR_cr2sr_ge2lep_error,2)) + (pow(MC_CR_fraction,2)*pow(MC_CR_cr2sr_incl_error,2)) ) / (pow(MC_CR_cr2sr_incl_yield,2)) ); // binomial uncertainty for multiple samples
	    MC_CR_fraction_err         = MC_CR_fraction_statErr;

	    // Get MC Fraction, varying impurity
	    MC_CR_fraction_impurity_up = ( MC_CR_cr2sr_ge2lep_yield ) / ( MC_CR_cr2sr_ge2lep_yield + ((1.0+impurity_sys)*MC_CR_cr2sr_non_ge2lep_yield) );
	    MC_CR_fraction_impurity_dn = ( MC_CR_cr2sr_ge2lep_yield ) / ( MC_CR_cr2sr_ge2lep_yield + ((1.0-impurity_sys)*MC_CR_cr2sr_non_ge2lep_yield) );
	    
	    // Get Transfer Factor SR/CR
	    tf_cr2sr = MC_SR_cr2sr_yield/MC_CR_cr2sr_ge2lep_yield;
	    //tf_cr2sr_statErr = tf_cr2sr*sqrt( pow(MC_CR_cr2sr_ge2lep_error/MC_CR_cr2sr_ge2lep_yield,2) + pow(MC_SR_cr2sr_error/MC_SR_cr2sr_yield,2) );  // Gaussian Errors for all components
	    //tf_cr2sr_statErr = tf_cr2sr*sqrt( pow(MC_SR_cr2sr_error/MC_SR_cr2sr_yield,2) );  // Removed MC_SR_cr2sr_error since it is included MC fraction
	    tf_cr2sr_statErr = 0.0;  // Removed MC_SR_cr2sr_error since it is included in tf_srBin error
	    tf_cr2sr_err = tf_cr2sr_statErr;

	    // Get Transfer Factor of SR_bin/SR
	    tf_srBin = MC_SR_bin_yield/MC_SR_cr2sr_yield;
	    tf_srBin_statErr = sqrt( ( ((1-2*tf_srBin)*pow(MC_SR_bin_error,2)) + (pow(tf_srBin,2)*pow(MC_SR_cr2sr_error,2)) ) / (pow(MC_SR_cr2sr_yield,2)) ); // binomial errors for multiple samples
	    tf_srBin_err = tf_srBin_statErr;

	    // Get tf_total
	    tf_tot = tf_cr2sr*tf_srBin;
	    tf_tot_statErr = tf_tot*sqrt( pow(tf_cr2sr_statErr/tf_cr2sr,2) + pow(tf_srBin_statErr/tf_srBin,2) );
	    tf_tot_err = tf_tot_statErr;

	    // SR Estimate
	    sr_estimate = Data_CR_cr2sr_yield*MC_CR_fraction*tf_tot;
	    sr_estimate_err_mc_stats = sr_estimate*sqrt( pow(MC_CR_fraction_statErr/MC_CR_fraction,2) + pow(tf_tot_statErr/tf_tot,2) );
	    sr_estimate_err_data_stats = sr_estimate*sqrt( pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
	    sr_estimate_err = sr_estimate*sqrt( pow(MC_CR_fraction_statErr/MC_CR_fraction,2) + pow(tf_tot_statErr/tf_tot,2) + pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
	    sr_estimate_impurity_up = Data_CR_cr2sr_yield*MC_CR_fraction_impurity_up*tf_tot;
	    sr_estimate_impurity_dn = Data_CR_cr2sr_yield*MC_CR_fraction_impurity_dn*tf_tot;
            
      
	  } // end if positive yields
	  
	} // end if using fractions


	//
	// Calculation if not using fraction
	//
	else{

	  // If using fraction, get incl CR MC yield
	  if(MC_CR_cr2sr_incl_yield>0.0 && MC_SR_cr2sr_yield>0.0 && MC_SR_bin_yield>0.0){
	    
	    // Get Transfer Factor SR/CR
	    tf_cr2sr = MC_SR_cr2sr_yield/MC_CR_cr2sr_incl_yield;
	    //tf_cr2sr_statErr = tf_cr2sr*sqrt( pow(MC_CR_cr2sr_incl_error/MC_CR_cr2sr_incl_yield,2) + pow(MC_SR_cr2sr_error/MC_SR_cr2sr_yield,2) );  // Gaussian errors for all components in tf_cr2sr
	    tf_cr2sr_statErr = tf_cr2sr*sqrt( pow(MC_CR_cr2sr_incl_error/MC_CR_cr2sr_incl_yield,2) ); // Avoid double counting MC_SR_cr2sr_error since it is included in tf_srBin
	    tf_cr2sr_err = tf_cr2sr_statErr;

	    // Get Transfer Factor of SR_bin/SR
	    tf_srBin = MC_SR_bin_yield/MC_SR_cr2sr_yield;
	    tf_srBin_statErr = sqrt( ( ((1-2*tf_srBin)*pow(MC_SR_bin_error,2)) + (pow(tf_srBin,2)*pow(MC_SR_cr2sr_error,2)) ) / (pow(MC_SR_cr2sr_yield,2)) ); // binomial errors for multiple samples
	    tf_srBin_err = tf_srBin_statErr;

	    // Get tf_total
	    tf_tot = tf_cr2sr*tf_srBin;
	    tf_tot_statErr = tf_tot*sqrt( pow(tf_cr2sr_statErr/tf_cr2sr,2) + pow(tf_srBin_statErr/tf_srBin,2) );
	    tf_tot_err = tf_tot_statErr;

	    // SR Estimate
	    sr_estimate = Data_CR_cr2sr_yield*tf_tot;
	    sr_estimate_err_mc_stats = sr_estimate*sqrt( pow(tf_tot_statErr/tf_tot,2) );
	    sr_estimate_err_data_stats = sr_estimate*sqrt( pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
	    sr_estimate_err = sr_estimate*sqrt( pow(tf_tot_statErr/tf_tot,2) + pow(Data_CR_cr2sr_error/Data_CR_cr2sr_yield,2) );
      
	  } // end if positive yields

	} // end if not using fraction
	
      } // end if using 2 transfer factors


      
      //
      // Report Results of nominal Calculation
      //

      // Fill histograms for limit setting, 0 is nominal element, 1 is first bin
      h_SR[0]->SetBinContent( iSR+1, sr_estimate );
      h_SR[0]->SetBinError( iSR+1, sr_estimate_err );
      
      // Uncertainty File, for each category, Nominal Values
      fprintf(f_uncFile_fullCalc, "Nominal & %.2f & %.2f", Data_CR_cr2sr_yield, MC_CR_cr2sr_incl_yield);
      if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f & %.2f", MC_CR_cr2sr_ge2lep_yield, MC_CR_fraction);
      if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f & %.2f", MC_SR_bin_yield, tf_cr2sr);
      else                             fprintf(f_uncFile_fullCalc, " & %.2f & %.2f", MC_SR_cr2sr_yield, tf_cr2sr);
      if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f & %.2f & %.2f", MC_SR_bin_yield, tf_srBin, tf_tot);
      fprintf(f_uncFile_fullCalc, " & %.2f ", sr_estimate);
      fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\ \\hline \\hline \n"); 
      

      // 
      // Report Results of data stats variation of calculation
      //
      
      // Fill histograms for limit setting, data stats up/down
      h_SR[1]->SetBinContent( iSR+1, sr_estimate+sr_estimate_err_data_stats );
      h_SR[1]->SetBinError( iSR+1, sr_estimate_err_data_stats );
      h_SR[2]->SetBinContent( iSR+1, sr_estimate-sr_estimate_err_data_stats );
      h_SR[2]->SetBinError( iSR+1, sr_estimate_err_data_stats );
      

      // Uncertainty File, for each category, Data Stats Up
      fprintf(f_uncFile_fullCalc, "Data Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", Data_CR_cr2sr_yield+Data_CR_cr2sr_error, (100*Data_CR_cr2sr_error/Data_CR_cr2sr_yield), MC_CR_cr2sr_incl_yield, 0.0);
      if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield, 0.0, MC_CR_fraction, 0.0);
      if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_cr2sr, 0.0);
      else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield, 0.0, tf_cr2sr, 0.0);
      if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_srBin, 0.0, tf_tot, 0.0);
      fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate, (100*sr_estimate_err_data_stats/sr_estimate));
      fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\  \n"); 

      
      // Uncertainty File, for each category, Data Stats Down
      fprintf(f_uncFile_fullCalc, "Data Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", Data_CR_cr2sr_yield-Data_CR_cr2sr_error, (100*Data_CR_cr2sr_error/Data_CR_cr2sr_yield), MC_CR_cr2sr_incl_yield, 0.0);
      if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield, 0.0, MC_CR_fraction, 0.0);
      if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_cr2sr, 0.0);
      else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield, 0.0, tf_cr2sr, 0.0);
      if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_srBin, 0.0, tf_tot, 0.0);
      fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate, (100*sr_estimate_err_data_stats/sr_estimate));
      fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\ \\hline \n"); 

            
      // Calc Min/Max uncertainty for data stats across all categories
      uncMax_cr_data_cr2sr[0] = std::max( uncMax_cr_data_cr2sr[0], (100*Data_CR_cr2sr_error/Data_CR_cr2sr_yield) );
      uncMin_cr_data_cr2sr[0] = std::min( uncMin_cr_data_cr2sr[0], (100*Data_CR_cr2sr_error/Data_CR_cr2sr_yield) );
      if(useFraction){
	uncMax_fraction[0] = std::max( uncMax_fraction[0], 0.0 );
	uncMin_fraction[0] = std::min( uncMin_fraction[0], 0.0 );
      }
      uncMax_tf_cr2sr[0] = std::max( uncMax_tf_cr2sr[0], 0.0 );
      uncMin_tf_cr2sr[0] = std::min( uncMin_tf_cr2sr[0], 0.0 );
      if(!oneTF){
	uncMax_tf_srBin[0] = std::max( uncMax_tf_srBin[0], 0.0 );
	uncMin_tf_srBin[0] = std::min( uncMin_tf_srBin[0], 0.0 );
	uncMax_tf_tot[0] = std::max( uncMax_tf_tot[0], 0.0 );
	uncMin_tf_tot[0] = std::min( uncMin_tf_tot[0], 0.0 );
      }
      uncMax_sr_estimate[0] = std::max( uncMax_sr_estimate[0], (100*sr_estimate_err_data_stats/sr_estimate) );
      uncMin_sr_estimate[0] = std::min( uncMin_sr_estimate[0], (100*sr_estimate_err_data_stats/sr_estimate) );

      
      // Calc SR estimate for dataStats up systematic for this cat
      cats_vs_sys[iSR][0] = (100*sr_estimate_err_data_stats/sr_estimate);
      
      

      //
      // Report results of calculation for MC Stats variations
      //
      
      // Fill histograms for limit setting, MC Stats
      h_SR[3]->SetBinContent( iSR+1, (sr_estimate+sr_estimate_err_mc_stats) );
      h_SR[3]->SetBinError( iSR+1, sr_estimate_err_mc_stats );
      h_SR[4]->SetBinContent( iSR+1, (sr_estimate-sr_estimate_err_mc_stats) );
      h_SR[4]->SetBinError( iSR+1, sr_estimate_err_mc_stats );
      
      
      // Uncertainty File, per category, MC Stats Up
      fprintf(f_uncFile_fullCalc, "MC Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", Data_CR_cr2sr_yield, 0.0, MC_CR_cr2sr_incl_yield+MC_CR_cr2sr_incl_error, (100.0*MC_CR_cr2sr_incl_error/MC_CR_cr2sr_incl_yield) );
      if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield+MC_CR_cr2sr_ge2lep_error, (100.0*MC_CR_cr2sr_ge2lep_error/MC_CR_cr2sr_ge2lep_yield), MC_CR_fraction+MC_CR_fraction_statErr, (100.0*MC_CR_fraction_statErr/MC_CR_fraction) );
      if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield+MC_SR_bin_error, (100.0*MC_SR_bin_error/MC_SR_bin_yield), tf_cr2sr+tf_cr2sr_statErr, (100.0*tf_cr2sr_statErr/tf_cr2sr) );
      else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield+MC_SR_cr2sr_error, (100.0*MC_SR_cr2sr_error/MC_SR_cr2sr_yield), tf_cr2sr+tf_cr2sr_statErr, (100.0*tf_cr2sr_statErr/tf_cr2sr) );
      if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield+MC_SR_bin_error, (100.0*MC_SR_bin_error/MC_SR_bin_yield), tf_srBin+tf_srBin_statErr, (100.0*tf_srBin_statErr/tf_srBin), tf_tot+tf_tot_statErr, (100.0*tf_tot_statErr/tf_tot) );
      fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate+sr_estimate_err_mc_stats, (100*sr_estimate_err_mc_stats/sr_estimate));
      fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\  \n"); 

      
      // Uncertainty File, per category, MC Stats Down
      fprintf(f_uncFile_fullCalc, "MC Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", Data_CR_cr2sr_yield, 0.0, MC_CR_cr2sr_incl_yield-MC_CR_cr2sr_incl_error, (100.0*MC_CR_cr2sr_incl_error/MC_CR_cr2sr_incl_yield) );
      if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield-MC_CR_cr2sr_ge2lep_error, (100.0*MC_CR_cr2sr_ge2lep_error/MC_CR_cr2sr_ge2lep_yield), MC_CR_fraction-MC_CR_fraction_statErr, (100.0*MC_CR_fraction_statErr/MC_CR_fraction) );
      if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield-MC_SR_bin_error, (100.0*MC_SR_bin_error/MC_SR_bin_yield), tf_cr2sr-tf_cr2sr_statErr, (100.0*tf_cr2sr_statErr/tf_cr2sr) );
      else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield-MC_SR_cr2sr_error, (100.0*MC_SR_cr2sr_error/MC_SR_cr2sr_yield), tf_cr2sr-tf_cr2sr_statErr, (100.0*tf_cr2sr_statErr/tf_cr2sr) );
      if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield-MC_SR_bin_error, (100.0*MC_SR_bin_error/MC_SR_bin_yield), tf_srBin-tf_srBin_statErr, (100.0*tf_srBin_statErr/tf_srBin), tf_tot-tf_tot_statErr, (100.0*tf_tot_statErr/tf_tot) );
      fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate-sr_estimate_err_mc_stats, (100*sr_estimate_err_mc_stats/sr_estimate));
      fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\  \\hline \n"); 
      fprintf(f_uncFile_fullCalc, "\\hline \n"); 

      // Calc Min/Max for MC Stats across all categories
      uncMax_cr_data_cr2sr[1] = std::max( uncMax_cr_data_cr2sr[1], 0.0 );
      uncMin_cr_data_cr2sr[1] = std::min( uncMin_cr_data_cr2sr[1], 0.0 );
      if(useFraction){
	uncMax_fraction[1] = std::max( uncMax_fraction[1], (100.0*MC_CR_fraction_statErr/MC_CR_fraction) );
	uncMin_fraction[1] = std::min( uncMin_fraction[1], (100.0*MC_CR_fraction_statErr/MC_CR_fraction) );
      }
      uncMax_tf_cr2sr[1] = std::max( uncMax_tf_cr2sr[1], (100*tf_cr2sr_err/tf_cr2sr) );
      uncMin_tf_cr2sr[1] = std::min( uncMin_tf_cr2sr[1], (100*tf_cr2sr_err/tf_cr2sr) );
      if(!oneTF){
	uncMax_tf_srBin[1] = std::max( uncMax_tf_srBin[1], (100*tf_srBin_err/tf_srBin) );
	uncMin_tf_srBin[1] = std::min( uncMin_tf_srBin[1], (100*tf_srBin_err/tf_srBin) );
	uncMax_tf_tot[1] = std::max( uncMax_tf_tot[1], (100*tf_tot_err/tf_tot) );
	uncMin_tf_tot[1] = std::min( uncMin_tf_tot[1], (100*tf_tot_err/tf_tot) );
      }
      uncMax_sr_estimate[1] = std::max( uncMax_sr_estimate[1], (100*sr_estimate_err_mc_stats/sr_estimate) );
      uncMin_sr_estimate[1] = std::min( uncMin_sr_estimate[1], (100*sr_estimate_err_mc_stats/sr_estimate) );
      
      
      // Calc SR estimate for MC Stats for this cat
      cats_vs_sys[iSR][1] = (100*sr_estimate_err_mc_stats/sr_estimate);
      
      

      //
      // Report Results of calculation for MC CR purity variation
      //
      if(useFraction){

	double MC_CR_fraction_impurity_max_diff = std::max( fabs(MC_CR_fraction_impurity_up-MC_CR_fraction), fabs(MC_CR_fraction_impurity_dn-MC_CR_fraction) );
	double sr_estimate_impurity_max_diff = std::max( fabs(sr_estimate_impurity_up-sr_estimate), fabs(sr_estimate_impurity_dn-sr_estimate) ); 

	MC_CR_fraction_err = pow( MC_CR_fraction_err,2 );
	MC_CR_fraction_err += pow( MC_CR_fraction_impurity_max_diff,2 );
	MC_CR_fraction_err = sqrt( MC_CR_fraction_err );
	
	// Fill histograms for limit setting, MC CR Purity
	h_SR[5]->SetBinContent( iSR+1, (sr_estimate_impurity_up) );
	h_SR[5]->SetBinError( iSR+1, sr_estimate_err_mc_stats );
	h_SR[6]->SetBinContent( iSR+1, (sr_estimate_impurity_dn) );
	h_SR[6]->SetBinError( iSR+1, sr_estimate_err_mc_stats );
      
      
	// Uncertainty File, per category, MC CR Purity Up
	fprintf(f_uncFile_fullCalc, "CR Impurity Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", Data_CR_cr2sr_yield, 0.0, MC_CR_cr2sr_incl_yield, 0.0 );
	if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield, 0.0, MC_CR_fraction_impurity_up, (100.0*(MC_CR_fraction_impurity_up-MC_CR_fraction)/MC_CR_fraction) );
	if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_cr2sr, 0.0 );
	else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield, 0.0, tf_cr2sr, 0.0 );
	if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_srBin, 0.0, tf_tot, 0.0 );
	fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate_impurity_up, (100*(sr_estimate_impurity_up-sr_estimate)/sr_estimate) );
	fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\  \n"); 

	
	// Uncertainty File, per category, MC CR Purity Down
	fprintf(f_uncFile_fullCalc, "CR Impurity Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", Data_CR_cr2sr_yield, 0.0, MC_CR_cr2sr_incl_yield, 0.0 );
	if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield, 0.0, MC_CR_fraction_impurity_dn, (100.0*(MC_CR_fraction_impurity_dn-MC_CR_fraction)/MC_CR_fraction) );
	if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_cr2sr, 0.0 );
	else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield, 0.0, tf_cr2sr, 0.0 );
	if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield, 0.0, tf_srBin, 0.0, tf_tot, 0.0 );
	fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate_impurity_dn, (100*(sr_estimate_impurity_dn-sr_estimate)/sr_estimate) );
	fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\ \\hline \n"); 

      
	// Calc Min/Max for MC CR Purity across all categories
	uncMax_cr_data_cr2sr[2] = std::max( uncMax_cr_data_cr2sr[2], 0.0 );
	uncMin_cr_data_cr2sr[2] = std::min( uncMin_cr_data_cr2sr[2], 0.0 );
	if(useFraction){
	  uncMax_fraction[2] = std::max( uncMax_fraction[2], (100.0*(MC_CR_fraction_impurity_max_diff)/MC_CR_fraction) );
	  uncMin_fraction[2] = std::min( uncMin_fraction[2], (100.0*(MC_CR_fraction_impurity_max_diff)/MC_CR_fraction) );
	}
	uncMax_tf_cr2sr[2] = std::max( uncMax_tf_cr2sr[2], 0.0 );
	uncMin_tf_cr2sr[2] = std::min( uncMin_tf_cr2sr[2], 0.0 );
	if(!oneTF){
	  uncMax_tf_srBin[2] = std::max( uncMax_tf_srBin[2], 0.0 );
	  uncMin_tf_srBin[2] = std::min( uncMin_tf_srBin[2], 0.0 );
	  uncMax_tf_tot[2] = std::max( uncMax_tf_tot[2], 0.0 );
	  uncMin_tf_tot[2] = std::min( uncMin_tf_tot[2], 0.0 );
	}
	uncMax_sr_estimate[2] = std::max( uncMax_sr_estimate[2], (100*(sr_estimate_impurity_max_diff)/sr_estimate) );
	uncMin_sr_estimate[2] = std::min( uncMin_sr_estimate[2], (100*(sr_estimate_impurity_max_diff)/sr_estimate) );
	
      
	// Calc SR estimate for MC Stats for this cat
	cats_vs_sys[iSR][2] = (100*sr_estimate_impurity_max_diff/sr_estimate);

      } // end if using fraction			       
      
      
      
      //
      // Loop over systematics
      //
      int unique_sys = additional_sys/2;
      for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){


	//
	// Systematic Variation Up
	//


	//
	// SR, category bin, up
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_SR;
	hName += "__genClassy_";
	hName += genClassy_ge2lep.label;
	hName += "__systematic_";
	hName += systematicList[iSys].label;
	
	h_temp = (TH1D*)f_SR_mc->Get(hName);
	if(!h_temp) cout << "BAD SR CATEGORY BIN UP HISTO: " << hName << endl;
	
	double MC_SR_bin_yield_up = h_temp->GetBinContent( SR_bin );
	double MC_SR_bin_error_up = h_temp->GetBinError( SR_bin );
      
	if(doRescale){
	  MC_SR_bin_error_up *= rescale;
	  MC_SR_bin_yield_up *= rescale;
	}
      
      
	//
	// SR, cr2sr bin, up
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_SR;
	hName += "__genClassy_";
	hName += genClassy_ge2lep.label;
	hName += "__systematic_";
	hName += systematicList[iSys].label;
      
	h_temp = (TH1D*)f_SR_mc->Get(hName);
	if(!h_temp) cout << "BAD SR INCL UP HISTO: " << hName << endl;
	
	double MC_SR_cr2sr_yield_up = h_temp->GetBinContent( CR_bin );
	double MC_SR_cr2sr_error_up = h_temp->GetBinError( CR_bin );

	if(doRescale){
	  MC_SR_cr2sr_error_up *= rescale;
	  MC_SR_cr2sr_yield_up *= rescale;
	}


	//
	// CR, MC, cr2sr bin, ge2lep genClassy, sys up
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_CR;
	hName += "__genClassy_";
	hName += genClassy_ge2lep.label;
	hName += "__systematic_";
	hName += systematicList[iSys].label;
	
	h_temp = (TH1D*)f_CR_mc->Get(hName);
	if(!h_temp) cout << "BAD CR CRtoSR UP MC HISTO: " << hName << endl;
	
	double MC_CR_cr2sr_ge2lep_yield_up = h_temp->GetBinContent( CR_bin );
	double MC_CR_cr2sr_ge2lep_error_up = h_temp->GetBinError( CR_bin );
      
	if(doRescale){
	  MC_CR_cr2sr_ge2lep_error_up *= rescale;
	  MC_CR_cr2sr_ge2lep_yield_up *= rescale;
	}


	//
	// CR, MC, cr2sr bin, incl genClassy, sys up
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_CR;
	hName += "__genClassy_";
	hName += genClassy_incl.label;
	hName += "__systematic_";
	hName += systematicList[iSys].label;
	
	h_temp = (TH1D*)f_CR_mc->Get(hName);
	if(!h_temp) cout << "BAD CR CRtoSR UP MC HISTO: " << hName << endl;
	
	double MC_CR_cr2sr_incl_yield_up = h_temp->GetBinContent( CR_bin );
	double MC_CR_cr2sr_incl_error_up = h_temp->GetBinError( CR_bin );
      
	if(doRescale){
	  MC_CR_cr2sr_incl_error_up *= rescale;
	  MC_CR_cr2sr_incl_yield_up *= rescale;
	}

		

	// CR, mc, cr2sr bin, non-ge2lep genClassy
	double MC_CR_cr2sr_non_ge2lep_yield_up = 0.0;
            
	// CR, mc, cr2sr bin, fraction of ge2lep
	double MC_CR_fraction_up = 1.0;
	double MC_CR_fraction_up_statErr = 0.0;
	
	// Transfer Factor SR/CR, up
	double tf_cr2sr_up = 1.0;
	double tf_cr2sr_up_statErr = 0.0;
	
	// Transfer Factor SR_bin/SR_cr2sr
	double tf_srBin_up = 1.0;
	double tf_srBin_up_statErr = 0.0;
	
	// Transfer Factor total
	double tf_tot_up = 1.0;
	double tf_tot_up_statErr = 0.0;
	
	// Signal Region Estimate
	double sr_estimate_up = 0.0;
	double sr_estimate_mc_stats_up = 0.0;

	
	//
	// Calculation if no extrapolation, ie SR_bin==CR_bin, or if forcing 1 TF
	//
	if( (v_bkgEst[iBkgEst].forceOneTF) || (SR_bin==CR_bin) ){
	
	  //
	  // Calculation if Using a Fraction Method with CR
	  //
	  if(useFraction){
	  
	    // If using fraction, get ge2lep CR MC yield
	    if(MC_CR_cr2sr_ge2lep_yield_up>0.0 && MC_SR_bin_yield_up>0.0){

	      // Get MC Non-ge2lep Yield
	      MC_CR_cr2sr_non_ge2lep_yield_up = MC_CR_cr2sr_incl_yield_up - MC_CR_cr2sr_ge2lep_yield_up;
	    
	      // Get MC Fraction of ge2lep
	      MC_CR_fraction_up          = ( MC_CR_cr2sr_ge2lep_yield_up ) / ( MC_CR_cr2sr_ge2lep_yield_up + MC_CR_cr2sr_non_ge2lep_yield_up );
	      MC_CR_fraction_up_statErr  = sqrt( ( ((1-2*MC_CR_fraction_up)*pow(MC_CR_cr2sr_ge2lep_error_up,2)) + (pow(MC_CR_fraction_up,2)*pow(MC_CR_cr2sr_incl_error_up,2)) ) / (pow(MC_CR_cr2sr_incl_yield_up,2)) ); // binomial uncertainty for multiple samples
	    
	      // Get Transfer Factor SR/CR
	      tf_cr2sr_up = MC_SR_bin_yield_up/MC_CR_cr2sr_ge2lep_yield_up;
	      //tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(MC_CR_cr2sr_ge2lep_error_up/MC_CR_cr2sr_ge2lep_yield_up,2) + pow(MC_SR_bin_error_up/MC_SR_bin_yield_up,2) );  // Gaussian errors for all components
	      tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(MC_SR_bin_error_up/MC_SR_bin_yield_up,2) ); // Avoid double counting MC_CR_cr2sr_ge2lep_error, since it is included in MC_CR_fraction_up_statErr
	    
	      // In This Case tf_tot=tf_cr2sr
	      tf_tot_up = tf_cr2sr_up;
	      tf_tot_up_statErr = tf_cr2sr_up_statErr;
	    
	      // SR Estimate
	      sr_estimate_up = Data_CR_cr2sr_yield*MC_CR_fraction_up*tf_tot_up;
	      sr_estimate_mc_stats_up = sr_estimate_up*sqrt( pow(MC_CR_fraction_up_statErr/MC_CR_fraction_up,2) + pow(tf_tot_up_statErr/tf_tot_up,2) );
	    
	    }
	  } // end if using fraction


	  //
	  // Calculation if not using fraction
	  //
	  else{
	  
	    // If not using fraction, get incl CR MC yield
	    if(MC_CR_cr2sr_incl_yield_up>0.0 && MC_SR_bin_yield_up>0.0){
	
	      // Transfer Factor SR/CR
	      tf_cr2sr_up = MC_SR_bin_yield_up/MC_CR_cr2sr_incl_yield_up;
	      tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(MC_CR_cr2sr_incl_error_up/MC_CR_cr2sr_incl_yield_up,2) + pow(MC_SR_bin_error_up/MC_SR_bin_yield_up,2) ); 
	      tf_tot_up = tf_cr2sr_up;
	      tf_tot_up_statErr = tf_cr2sr_up_statErr;
	
	      // Signal Region Estimate
	      sr_estimate_up = Data_CR_cr2sr_yield*tf_tot_up;
	      sr_estimate_mc_stats_up = sr_estimate_up*sqrt( pow(tf_tot_up_statErr/tf_tot_up,2) );
	    
	    } // end if yields are positive

	  } // end if not using fraction

	} // end if using one transfer fraction

      
	//
	// Calculation if using one TF for SR/CR and another TF SR_bin/SR, ie when extrapolation and SR!=SR_bin
	//
	else{

	  //
	  // Calculation if using fraction
	  //
	  if(useFraction){
	  
	    // If using fraction, get ge2lep CR MC yield
	    if(MC_CR_cr2sr_ge2lep_yield_up>0.0 && MC_SR_cr2sr_yield_up>0.0 && MC_SR_bin_yield_up>0.0){

	      // Get MC Non-ge2lep Yield
	      MC_CR_cr2sr_non_ge2lep_yield_up = MC_CR_cr2sr_incl_yield_up - MC_CR_cr2sr_ge2lep_yield_up;
	    
	      // Get MC Fraction of ge2lep
	      MC_CR_fraction_up         = ( MC_CR_cr2sr_ge2lep_yield_up ) / ( MC_CR_cr2sr_ge2lep_yield_up + MC_CR_cr2sr_non_ge2lep_yield_up );
	      MC_CR_fraction_up_statErr  = sqrt( ( ((1-2*MC_CR_fraction_up)*pow(MC_CR_cr2sr_ge2lep_error_up,2)) + (pow(MC_CR_fraction_up,2)*pow(MC_CR_cr2sr_incl_error_up,2)) ) / (pow(MC_CR_cr2sr_incl_yield_up,2)) ); // binomial uncertainty for multiple samples
	    
	      // Get Transfer Factor SR/CR
	      tf_cr2sr_up = MC_SR_cr2sr_yield_up/MC_CR_cr2sr_ge2lep_yield_up;
	      //tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(MC_CR_cr2sr_ge2lep_error_up/MC_CR_cr2sr_ge2lep_yield_up,2) + pow(MC_SR_cr2sr_error_up/MC_SR_cr2sr_yield_up,2) );  // Gaussian errors for all components 
	      //tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(MC_SR_cr2sr_error_up/MC_SR_cr2sr_yield_up,2) );  // Avoid touble counting MC_CR_cr2sr_ge2lep_yield_up, since its error is included in MC_CR_fraction_up
	      tf_cr2sr_up_statErr = 0.0;  // Avoid double counting MC_SR_cr2sr_error_up since it is included in tf_srBin_err
	    
	      // Get Transfer Factor of SR_bin/SR
	      tf_srBin_up = MC_SR_bin_yield_up/MC_SR_cr2sr_yield_up;
	      tf_srBin_up_statErr = sqrt( ( ((1-2*tf_srBin_up)*pow(MC_SR_bin_error_up,2)) + (pow(tf_srBin_up,2)*pow(MC_SR_cr2sr_error_up,2)) ) / (pow(MC_SR_cr2sr_yield_up,2)) ); // binomial errors for multiple samples
	    
	      // Get total transfer factor
	      tf_tot_up = tf_cr2sr_up*tf_srBin_up;
	      tf_tot_up_statErr = tf_tot_up*sqrt( pow(tf_cr2sr_up_statErr/tf_cr2sr_up,2) + pow(tf_srBin_up_statErr/tf_srBin_up,2) );
	    
	      // SR Estimate
	      sr_estimate_up = Data_CR_cr2sr_yield*MC_CR_fraction_up*tf_tot_up;
	      sr_estimate_mc_stats_up = sr_estimate_up*sqrt( pow(MC_CR_fraction_up_statErr/MC_CR_fraction_up,2) + pow(tf_tot_up_statErr/tf_tot_up,2) );
	    
      
	    } // end if positive yields
	  
	  } // end if using fractions


	  //
	  // Calculation if not using fraction
	  //
	  else{

	    // If using fraction, get incl CR MC yield
	    if(MC_CR_cr2sr_incl_yield_up>0.0 && MC_SR_cr2sr_yield_up>0.0 && MC_SR_bin_yield_up>0.0){

	      // Get Transfer Factor SR/CR
	      tf_cr2sr_up = MC_SR_cr2sr_yield_up/MC_CR_cr2sr_incl_yield_up;
	      //tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(MC_CR_cr2sr_incl_error_up/MC_CR_cr2sr_incl_yield_up,2) + pow(MC_SR_cr2sr_error_up/MC_SR_cr2sr_yield_up,2) );  // Gaussian errors for all compontnetns
	      tf_cr2sr_up_statErr = tf_cr2sr_up*sqrt( pow(MC_CR_cr2sr_incl_error_up/MC_CR_cr2sr_incl_yield_up,2) ); // Avoid double counting MC_SR_cr2sr_error_up since it is included in tf_srBin_up
	    
	      // Get Transfer Factor of SR_bin/SR
	      tf_srBin_up = MC_SR_bin_yield_up/MC_SR_cr2sr_yield_up;
	      tf_srBin_up_statErr = sqrt( ( ((1-2*tf_srBin_up)*pow(MC_SR_bin_error_up,2)) + (pow(tf_srBin_up,2)*pow(MC_SR_cr2sr_error_up,2)) ) / (pow(MC_SR_cr2sr_yield_up,2)) ); // binomial errors for multiple samples
	    
	      // Get Total Transer factor
	      tf_tot_up = tf_cr2sr_up*tf_srBin_up;
	      tf_tot_up_statErr = tf_tot_up*sqrt( pow(tf_cr2sr_up_statErr/tf_cr2sr_up,2) + pow(tf_srBin_up_statErr/tf_srBin_up,2) );
	    
	      // SR Estimate
	      sr_estimate_up = Data_CR_cr2sr_yield*tf_tot_up;
	      sr_estimate_mc_stats_up = sr_estimate_up*sqrt( pow(tf_tot_up_statErr/tf_tot_up,2) );
	    
	    } // end if positive yields

	  } // end if not using fraction
	
	} // end if using 2 transfer factors



	//
	// Systematic Variation Down
	//	
	
	//
	// SR, category bin, dn
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_SR;
	hName += "__genClassy_";
	hName += genClassy_ge2lep.label;
	hName += "__systematic_";
	hName += systematicList[iSys+1].label;
      
	h_temp = (TH1D*)f_SR_mc->Get(hName);
	if(!h_temp) cout << "BAD SR BIN DN HISTO: " << hName << endl;
	
	double MC_SR_bin_error_dn = h_temp->GetBinError( SR_bin );
	double MC_SR_bin_yield_dn = h_temp->GetBinContent( SR_bin );
	
	if(doRescale){
	  MC_SR_bin_error_dn *= rescale;
	  MC_SR_bin_yield_dn *= rescale;
	}
      
      
	//
	// SR, CRtoSR bin, dn
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_SR;
	hName += "__genClassy_";
	hName += genClassy_ge2lep.label;
	hName += "__systematic_";
	hName += systematicList[iSys+1].label;
	
	h_temp = (TH1D*)f_SR_mc->Get(hName);
	if(!h_temp) cout << "BAD SR INCL DN HISTO: " << hName << endl;
    
	double MC_SR_cr2sr_yield_dn = h_temp->GetBinContent( CR_bin );
	double MC_SR_cr2sr_error_dn = h_temp->GetBinError( CR_bin );

	if(doRescale){
	  MC_SR_cr2sr_error_dn *= rescale;
	  MC_SR_cr2sr_yield_dn *= rescale;
	}
	
      
	//
	// CR, MC, CRtoSR bin, ge2lep genClassy dn
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_CR;
	hName += "__genClassy_";
	hName += genClassy_ge2lep.label;
	hName += "__systematic_";
	hName += systematicList[iSys+1].label;
      
	h_temp = (TH1D*)f_CR_mc->Get(hName);
	if(!h_temp) cout << "BAD CR CRtoSR DN MC HISTO: " << hName << endl;
	
	double MC_CR_cr2sr_ge2lep_yield_dn = h_temp->GetBinContent( CR_bin );
	double MC_CR_cr2sr_ge2lep_error_dn = h_temp->GetBinError( CR_bin );
	
	if(doRescale){
	  MC_CR_cr2sr_ge2lep_error_dn *= rescale;
	  MC_CR_cr2sr_ge2lep_yield_dn *= rescale;
	}


	//
	// CR, MC, CRtoSR bin, incl genClassy dn
	//
	hName = hNameBase;
	hName += "__";
	hName += regionName_CR;
	hName += "__genClassy_";
	hName += genClassy_incl.label;
	hName += "__systematic_";
	hName += systematicList[iSys+1].label;
      
	h_temp = (TH1D*)f_CR_mc->Get(hName);
	if(!h_temp) cout << "BAD CR CRtoSR DN MC HISTO: " << hName << endl;
	
	double MC_CR_cr2sr_incl_yield_dn = h_temp->GetBinContent( CR_bin );
	double MC_CR_cr2sr_incl_error_dn = h_temp->GetBinError( CR_bin );
	
	if(doRescale){
	  MC_CR_cr2sr_incl_error_dn *= rescale;
	  MC_CR_cr2sr_incl_yield_dn *= rescale;
	}

	


	// CR, mc, cr2sr bin, non-ge2lep genClassy
	double MC_CR_cr2sr_non_ge2lep_yield_dn = 0.0;
            
	// CR, mc, cr2sr bin, fraction of ge2lep
	double MC_CR_fraction_dn = 1.0;
	double MC_CR_fraction_dn_statErr = 0.0;
	
	// Transfer Factor SR/CR, dn
	double tf_cr2sr_dn = 1.0;
	double tf_cr2sr_dn_statErr = 0.0;
	
	// Transfer Factor SR_bin/SR_cr2sr
	double tf_srBin_dn = 1.0;
	double tf_srBin_dn_statErr = 0.0;
	
	// Transfer Factor total
	double tf_tot_dn = 1.0;
	double tf_tot_dn_statErr = 0.0;
	
	// Signal Region Estimate
	double sr_estimate_dn = 0.0;
	double sr_estimate_mc_stats_dn = 0.0;

	
	//
	// Calculation if no extrapolation, ie SR_bin==CR_bin, or if forcing 1 TF
	//
	if( (v_bkgEst[iBkgEst].forceOneTF) || (SR_bin==CR_bin) ){
	
	  //
	  // Calculation if Using a Fraction Method with CR
	  //
	  if(useFraction){
	  
	    // If using fraction, get ge2lep CR MC yield
	    if(MC_CR_cr2sr_ge2lep_yield_dn>0.0 && MC_SR_bin_yield_dn>0.0){

	      // Get MC Non-ge2lep Yield
	      MC_CR_cr2sr_non_ge2lep_yield_dn = MC_CR_cr2sr_incl_yield_dn - MC_CR_cr2sr_ge2lep_yield_dn;
	      
	      // Get MC Fraction of ge2lep
	      MC_CR_fraction_dn          = ( MC_CR_cr2sr_ge2lep_yield_dn ) / ( MC_CR_cr2sr_ge2lep_yield_dn + MC_CR_cr2sr_non_ge2lep_yield_dn );
	      MC_CR_fraction_dn_statErr  = sqrt( ( ((1-2*MC_CR_fraction_dn)*pow(MC_CR_cr2sr_ge2lep_error_dn,2)) + (pow(MC_CR_fraction_dn,2)*pow(MC_CR_cr2sr_incl_error_dn,2)) ) / (pow(MC_CR_cr2sr_incl_yield_dn,2)) ); // binomial uncertainty for multiple samples

	      // Get Transfer Factor SR/CR
	      tf_cr2sr_dn = MC_SR_bin_yield_dn/MC_CR_cr2sr_ge2lep_yield_dn;
	      //tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(MC_CR_cr2sr_ge2lep_error_dn/MC_CR_cr2sr_ge2lep_yield_dn,2) + pow(MC_SR_bin_error_dn/MC_SR_bin_yield_dn,2) ); 
	      tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(MC_SR_bin_error_dn/MC_SR_bin_yield_dn,2) );  // Avoid double counting MC_CR_bin_error sinc eit is inlcuded in MC_CR_fraction_dn
	    
	      // In This Case tf_tot=tf_cr2sr
	      tf_tot_dn = tf_cr2sr_dn;
	      tf_tot_dn_statErr = tf_cr2sr_dn_statErr;
	    
	      // SR Estimate
	      sr_estimate_dn = Data_CR_cr2sr_yield*MC_CR_fraction_dn*tf_tot_dn;
	      sr_estimate_mc_stats_dn = sr_estimate_dn*sqrt( pow(MC_CR_fraction_dn_statErr/MC_CR_fraction_dn,2) + pow(tf_tot_dn_statErr/tf_tot_dn,2) );
	    
	    }
	  } // end if using fraction


	  //
	  // Calculation if not using fraction
	  //
	  else{
	  
	    // If not using fraction, get incl CR MC yield
	    if(MC_CR_cr2sr_incl_yield_dn>0.0 && MC_SR_bin_yield_dn>0.0){
	
	      // Transfer Factor SR/CR
	      tf_cr2sr_dn = MC_SR_bin_yield_dn/MC_CR_cr2sr_incl_yield_dn;
	      tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(MC_CR_cr2sr_incl_error_dn/MC_CR_cr2sr_incl_yield_dn,2) + pow(MC_SR_bin_error_dn/MC_SR_bin_yield_dn,2) ); 
	      tf_tot_dn = tf_cr2sr_dn;
	      tf_tot_dn_statErr = tf_cr2sr_dn_statErr;
	
	      // Signal Region Estimate
	      sr_estimate_dn = Data_CR_cr2sr_yield*tf_tot_dn;
	      sr_estimate_mc_stats_dn = sr_estimate_dn*sqrt( pow(tf_tot_dn_statErr/tf_tot_dn,2) );
	    
	    } // end if yields are positive

	  } // end if not using fraction

	} // end if using one transfer fraction

      
	//
	// Calculation if using one TF for SR/CR and another TF SR_bin/SR, ie when extrapolation and SR!=SR_bin
	//
	else{

	  //
	  // Calculation if using fraction
	  //
	  if(useFraction){
	  
	    // If using fraction, get ge2lep CR MC yield
	    if(MC_CR_cr2sr_ge2lep_yield_dn>0.0 && MC_SR_cr2sr_yield_dn>0.0 && MC_SR_bin_yield_dn>0.0){

	      // Get MC Non-ge2lep Yield
	      MC_CR_cr2sr_non_ge2lep_yield_dn = MC_CR_cr2sr_incl_yield_dn - MC_CR_cr2sr_ge2lep_yield_dn;
	    
	      // Get MC Fraction of ge2lep
	      MC_CR_fraction_dn         = ( MC_CR_cr2sr_ge2lep_yield_dn ) / ( MC_CR_cr2sr_ge2lep_yield_dn + MC_CR_cr2sr_non_ge2lep_yield_dn );
	      MC_CR_fraction_dn_statErr  = sqrt( ( ((1-2*MC_CR_fraction_dn)*pow(MC_CR_cr2sr_ge2lep_error_dn,2)) + (pow(MC_CR_fraction_dn,2)*pow(MC_CR_cr2sr_incl_error_dn,2)) ) / (pow(MC_CR_cr2sr_incl_yield_dn,2)) ); // binomial uncertainty for multiple samples

	      // Get Transfer Factor SR/CR
	      tf_cr2sr_dn = MC_SR_cr2sr_yield_dn/MC_CR_cr2sr_ge2lep_yield_dn;
	      //tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(MC_CR_cr2sr_ge2lep_error_dn/MC_CR_cr2sr_ge2lep_yield_dn,2) + pow(MC_SR_cr2sr_error_dn/MC_SR_cr2sr_yield_dn,2) );  // Gaussian errors for each component
	      //tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(MC_SR_cr2sr_error_dn/MC_SR_cr2sr_yield_dn,2) );  // Avoid double counting MC_CR_cr2sr_error since it is included in MC_CR_fraction
	      tf_cr2sr_dn_statErr = 0.0;  // Avoid double counting MC_SR_cr2sr_error_dn since it is included in tf_srBin_dn
	    
	      // Get Transfer Factor of SR_bin/SR
	      tf_srBin_dn = MC_SR_bin_yield_dn/MC_SR_cr2sr_yield_dn;
	      tf_srBin_dn_statErr = sqrt( ( ((1-2*tf_srBin_dn)*pow(MC_SR_bin_error_dn,2)) + (pow(tf_srBin_dn,2)*pow(MC_SR_cr2sr_error_dn,2)) ) / (pow(MC_SR_cr2sr_yield_dn,2)) ); // binomial errors for multiple samples

	      // Get tf_tot
	      tf_tot_dn = tf_cr2sr_dn*tf_srBin_dn;
	      tf_tot_dn_statErr = tf_tot_dn*sqrt( pow(tf_cr2sr_dn_statErr/tf_cr2sr_dn,2) + pow(tf_srBin_dn_statErr/tf_srBin_dn,2) );
	    
	      // SR Estimate
	      sr_estimate_dn = Data_CR_cr2sr_yield*MC_CR_fraction_dn*tf_tot_dn;
	      sr_estimate_mc_stats_dn = sr_estimate_dn*sqrt( pow(MC_CR_fraction_dn_statErr/MC_CR_fraction_dn,2) + pow(tf_tot_dn_statErr/tf_tot_dn,2) );
	    
      
	    } // end if positive yields
	  
	  } // end if using fractions


	  //
	  // Calculation if not using fraction
	  //
	  else{

	    // If using fraction, get incl CR MC yield
	    if(MC_CR_cr2sr_incl_yield_dn>0.0 && MC_SR_cr2sr_yield_dn>0.0 && MC_SR_bin_yield_dn>0.0){

	      // Get Transfer Factor SR/CR
	      tf_cr2sr_dn = MC_SR_cr2sr_yield_dn/MC_CR_cr2sr_incl_yield_dn;
	      //tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(MC_CR_cr2sr_incl_error_dn/MC_CR_cr2sr_incl_yield_dn,2) + pow(MC_SR_cr2sr_error_dn/MC_SR_cr2sr_yield_dn,2) ); 
	      tf_cr2sr_dn_statErr = tf_cr2sr_dn*sqrt( pow(MC_CR_cr2sr_incl_error_dn/MC_CR_cr2sr_incl_yield_dn,2) ); // Avoid double counting MC_SR_cr2sr_incl_error_dn since it is included in tf_srBin
	      
	    
	      // Get Transfer Factor of SR_bin/SR
	      tf_srBin_dn = MC_SR_bin_yield_dn/MC_SR_cr2sr_yield_dn;
	      tf_srBin_dn_statErr = sqrt( ( ((1-2*tf_srBin_dn)*pow(MC_SR_bin_error_dn,2)) + (pow(tf_srBin_dn,2)*pow(MC_SR_cr2sr_error_dn,2)) ) / (pow(MC_SR_cr2sr_yield_dn,2)) ); // binomial errors for multiple samples

	      // In This Case tf_tot_dn=tf_cr2sr_dn
	      tf_tot_dn = tf_cr2sr_dn*tf_srBin_dn;
	      tf_tot_dn_statErr = tf_tot_dn*sqrt( pow(tf_cr2sr_dn_statErr/tf_cr2sr_dn,2) + pow(tf_srBin_dn_statErr/tf_srBin_dn,2) );
	    
	      // SR Estimate
	      sr_estimate_dn = Data_CR_cr2sr_yield*tf_tot_dn;
	      sr_estimate_mc_stats_dn = sr_estimate_dn*sqrt( pow(tf_tot_dn_statErr/tf_tot_dn,2) );
	    
	    } // end if positive yields

	  } // end if not using fraction
	
	} // end if using 2 transfer factors



	//
	//  Compute Largest Difference in Up/Down Variations
	//
	
     
	// Diff in MC CR Fraction
	double MC_CR_fraction_max_diff = 0.0;
	double MC_CR_fraction_max_diff_sq = 0.0;
	if(useFraction){
	  MC_CR_fraction_max_diff = std::max( fabs(MC_CR_fraction_up-MC_CR_fraction), fabs(MC_CR_fraction_dn-MC_CR_fraction) );
	  MC_CR_fraction_max_diff_sq = pow( MC_CR_fraction_max_diff, 2 );
	}
	MC_CR_fraction_err = pow( MC_CR_fraction_err, 2 );
	MC_CR_fraction_err += MC_CR_fraction_max_diff_sq;
	MC_CR_fraction_err = sqrt(MC_CR_fraction_err);
	

	// Diff in TF Cr2sr
	double tf_cr2sr_max_diff = std::max( fabs(tf_cr2sr_up-tf_cr2sr), fabs(tf_cr2sr_dn-tf_cr2sr) );
	double tf_cr2sr_max_diff_sq = pow( tf_cr2sr_max_diff, 2 );
	tf_cr2sr_err = pow( tf_cr2sr_err, 2 );
	tf_cr2sr_err += tf_cr2sr_max_diff_sq;
	tf_cr2sr_err = sqrt(tf_cr2sr_err);
	
	
	// Diff in TF SR bin
	double tf_srBin_max_diff = std::max( fabs(tf_srBin_up-tf_srBin), fabs(tf_srBin_dn-tf_srBin) );
	double tf_srBin_max_diff_sq = pow( tf_srBin_max_diff, 2 );
	tf_srBin_err = pow( tf_srBin_err, 2 );
	tf_srBin_err += tf_srBin_max_diff_sq;
	tf_srBin_err = sqrt(tf_srBin_err);
	

	// Diff in TF Total bin
	double tf_tot_max_diff = std::max( fabs(tf_tot_up-tf_tot), fabs(tf_tot_dn-tf_tot) );
	double tf_tot_max_diff_sq = pow( tf_tot_max_diff, 2 );
	tf_tot_err = pow( tf_tot_err, 2 );
	tf_tot_err += tf_tot_max_diff_sq;
	tf_tot_err = sqrt(tf_tot_err);
	

	// Diff in SR estimate
	double est_max_diff = std::max( fabs(sr_estimate_up-sr_estimate), fabs(sr_estimate_dn-sr_estimate) );
	double est_max_diff_sq = pow( est_max_diff, 2 );
	sr_estimate_err = pow( sr_estimate_err, 2 );
	sr_estimate_err += est_max_diff_sq;
	sr_estimate_err = sqrt(sr_estimate_err);
	
     
	
	//
	// Limit Histogram and Tables
	//
	
	// Fill Limit Histogram for Up Variations
	h_SR[iSys+additional_sys]->SetBinContent( iSR+1, sr_estimate_up );
	h_SR[iSys+additional_sys]->SetBinError( iSR+1, sr_estimate_mc_stats_up );

	// Fill Limit Histogram for Down Variations
	h_SR[iSys+additional_sys+1]->SetBinContent( iSR+1, sr_estimate_dn );
	h_SR[iSys+additional_sys+1]->SetBinError( iSR+1, sr_estimate_mc_stats_dn );
	

	// Uncertainty File, per category, Sys Variation Up
	fprintf(f_uncFile_fullCalc, "%s,~Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", systematicList[iSys].tex.c_str(), Data_CR_cr2sr_yield, 0.0, MC_CR_cr2sr_incl_yield_up, (100.0*(MC_CR_cr2sr_incl_yield_up-MC_CR_cr2sr_incl_yield)/MC_CR_cr2sr_incl_yield) );
	if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield_up, (100.0*(MC_CR_cr2sr_ge2lep_yield_up-MC_CR_cr2sr_ge2lep_yield)/MC_CR_cr2sr_ge2lep_yield), MC_CR_fraction_up, (100.0*(MC_CR_fraction_up-MC_CR_fraction)/MC_CR_fraction) );
	if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield_up, (100.0*(MC_SR_bin_yield_up-MC_SR_bin_yield)/MC_SR_bin_yield), tf_cr2sr_up, (100.0*(tf_cr2sr_up-tf_cr2sr)/tf_cr2sr) );
	else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield_up, (100.0*(MC_SR_cr2sr_yield_up-MC_SR_cr2sr_yield)/MC_SR_cr2sr_yield), tf_cr2sr_up, (100.0*(tf_cr2sr_up-tf_cr2sr)/tf_cr2sr) );
	if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield_up, (100.0*(MC_SR_bin_yield_up-MC_SR_bin_yield)/MC_SR_bin_yield), tf_srBin_up, (100.0*(tf_srBin_up-tf_srBin)/tf_srBin), tf_tot_up, (100.0*(tf_tot_up-tf_tot)/tf_tot) );
	fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate_up, (100*(sr_estimate_up-sr_estimate)/sr_estimate));
	fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\  \n"); 
	
	
	// Uncertainty File, per category, Sys Variation Dn
	fprintf(f_uncFile_fullCalc, "%s,~Dn & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", systematicList[iSys].tex.c_str(), Data_CR_cr2sr_yield, 0.0, MC_CR_cr2sr_incl_yield_dn, (100.0*(MC_CR_cr2sr_incl_yield_dn-MC_CR_cr2sr_incl_yield)/MC_CR_cr2sr_incl_yield) );
	if(useFraction) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_CR_cr2sr_ge2lep_yield_dn, (100.0*(MC_CR_cr2sr_ge2lep_yield_dn-MC_CR_cr2sr_ge2lep_yield)/MC_CR_cr2sr_ge2lep_yield), MC_CR_fraction_dn, (100.0*(MC_CR_fraction_dn-MC_CR_fraction)/MC_CR_fraction) );
	if(v_bkgEst[iBkgEst].forceOneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield_dn, (100.0*(MC_SR_bin_yield_dn-MC_SR_bin_yield)/MC_SR_bin_yield), tf_cr2sr_dn, (100.0*(tf_cr2sr_dn-tf_cr2sr)/tf_cr2sr) );
	else                             fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_cr2sr_yield_dn, (100.0*(MC_SR_cr2sr_yield_dn-MC_SR_cr2sr_yield)/MC_SR_cr2sr_yield), tf_cr2sr_dn, (100.0*(tf_cr2sr_dn-tf_cr2sr)/tf_cr2sr) );
	if(!oneTF) fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", MC_SR_bin_yield_dn, (100.0*(MC_SR_bin_yield_dn-MC_SR_bin_yield)/MC_SR_bin_yield), tf_srBin_dn, (100.0*(tf_srBin_dn-tf_srBin)/tf_srBin), tf_tot_dn, (100.0*(tf_tot_dn-tf_tot)/tf_tot) );
	fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate_dn, (100*(sr_estimate_dn-sr_estimate)/sr_estimate));
	fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\  \n"); 
	fprintf(f_uncFile_fullCalc, "\\hline \n"); 
		
	// Fill Min/Max Uncertainty
	uncMax_cr_data_cr2sr[unique_sys] = std::max( uncMax_cr_data_cr2sr[unique_sys], 0.0 );
	uncMin_cr_data_cr2sr[unique_sys] = std::min( uncMin_cr_data_cr2sr[unique_sys], 0.0 );
	if(useFraction){
	  uncMax_fraction[unique_sys] = std::max( uncMax_fraction[unique_sys], (100*MC_CR_fraction_max_diff/MC_CR_fraction) );
	  uncMin_fraction[unique_sys] = std::min( uncMin_fraction[unique_sys], (100*MC_CR_fraction_max_diff/MC_CR_fraction) );
	}
	uncMax_tf_cr2sr[unique_sys] = std::max( uncMax_tf_cr2sr[unique_sys], (100*tf_cr2sr_max_diff/tf_cr2sr) );
	uncMin_tf_cr2sr[unique_sys] = std::min( uncMin_tf_cr2sr[unique_sys], (100*tf_cr2sr_max_diff/tf_cr2sr) );
	if(!oneTF){
	  uncMax_tf_srBin[unique_sys] = std::max( uncMax_tf_srBin[unique_sys], (100*tf_srBin_max_diff/tf_srBin) );
	  uncMin_tf_srBin[unique_sys] = std::min( uncMin_tf_srBin[unique_sys], (100*tf_srBin_max_diff/tf_srBin) );
	  uncMax_tf_tot[unique_sys] = std::max( uncMax_tf_tot[unique_sys], (100*tf_tot_max_diff/tf_tot) );
	  uncMin_tf_tot[unique_sys] = std::min( uncMin_tf_tot[unique_sys], (100*tf_tot_max_diff/tf_tot) );
	}
	uncMax_sr_estimate[unique_sys] = std::max( uncMax_sr_estimate[unique_sys], (100*est_max_diff/sr_estimate) );
	uncMin_sr_estimate[unique_sys] = std::min( uncMin_sr_estimate[unique_sys], (100*est_max_diff/sr_estimate) );

      
	// Calc SR estimate for this sys for this cat
	cats_vs_sys[iSR][unique_sys] = (100*est_max_diff/sr_estimate);
      

	// Increment unique sys counter
	unique_sys++;

      
      } // end loop over systematics



      // Set Uncertainty Of Nominal Limit Histo to total uncertainty, for ease of use with table making
      h_SR[0]->SetBinError( iSR+1, sr_estimate_err );


      // Uncertainty File, per category, Sys Variation Up
      fprintf(f_uncFile_fullCalc, "\\hline \n"); 
      fprintf(f_uncFile_fullCalc, "Total Uncertainties & %.2f ~(%.2f\\%%) & ", Data_CR_cr2sr_yield, (100*Data_CR_cr2sr_error/Data_CR_cr2sr_yield) );
      if(useFraction) fprintf(f_uncFile_fullCalc, " &  & %.2f ~(%.2f\\%%)", MC_CR_fraction, (100.0*(MC_CR_fraction_err)/MC_CR_fraction) );
      fprintf(f_uncFile_fullCalc, " &  & %.2f ~(%.2f\\%%)", tf_cr2sr, (100.0*(tf_cr2sr_err)/tf_cr2sr) );
      if(!oneTF) fprintf(f_uncFile_fullCalc, " &  & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%)", tf_srBin, (100.0*(tf_srBin_err)/tf_srBin), tf_tot, (100.0*(tf_tot_err)/tf_tot) );
      fprintf(f_uncFile_fullCalc, " & %.2f ~(%.2f\\%%)", sr_estimate, (100*(sr_estimate_err)/sr_estimate));
      fprintf(f_uncFile_fullCalc, " \\"); fprintf(f_uncFile_fullCalc, "\\ \\hline \n"); 
      

      // Formatting for uncertainty tex file for each category
      fprintf(f_uncFile_fullCalc, "\\end{tabular} \n");
      fprintf(f_uncFile_fullCalc, "} \n");
      fprintf(f_uncFile_fullCalc, "\\end{table} \n");
      fprintf(f_uncFile_fullCalc, "\n \n");
      fprintf(f_uncFile_fullCalc, "\\clearpage");
      fprintf(f_uncFile_fullCalc, "\n \n");
    
    
      // Fill Min/Max Uncertainty
      uncMax_cr_data_cr2sr[nSys_unique-1] = std::max( uncMax_cr_data_cr2sr[nSys_unique-1], (100*Data_CR_cr2sr_error/Data_CR_cr2sr_yield) );
      uncMin_cr_data_cr2sr[nSys_unique-1] = std::min( uncMin_cr_data_cr2sr[nSys_unique-1], (100*Data_CR_cr2sr_error/Data_CR_cr2sr_yield) );
      if(useFraction){
	uncMax_fraction[nSys_unique-1] = std::max( uncMax_fraction[nSys_unique-1], (100*MC_CR_fraction_err/MC_CR_fraction) );
	uncMin_fraction[nSys_unique-1] = std::min( uncMin_fraction[nSys_unique-1], (100*MC_CR_fraction_err/MC_CR_fraction) );
      }
      uncMax_tf_cr2sr[nSys_unique-1] = std::max( uncMax_tf_cr2sr[nSys_unique-1], (100*tf_cr2sr_err/tf_cr2sr) );
      uncMin_tf_cr2sr[nSys_unique-1] = std::min( uncMin_tf_cr2sr[nSys_unique-1], (100*tf_cr2sr_err/tf_cr2sr) );
      if(!oneTF){
	uncMax_tf_srBin[nSys_unique-1] = std::max( uncMax_tf_srBin[nSys_unique-1], (100*tf_srBin_err/tf_srBin) );
	uncMin_tf_srBin[nSys_unique-1] = std::min( uncMin_tf_srBin[nSys_unique-1], (100*tf_srBin_err/tf_srBin) );
	uncMax_tf_tot[nSys_unique-1] = std::max( uncMax_tf_tot[nSys_unique-1], (100*tf_tot_err/tf_tot) );
	uncMin_tf_tot[nSys_unique-1] = std::min( uncMin_tf_tot[nSys_unique-1], (100*tf_tot_err/tf_tot) );
      }
      uncMax_sr_estimate[nSys_unique-1] = std::max( uncMax_sr_estimate[nSys_unique-1], (100*sr_estimate_err/sr_estimate) );
      uncMin_sr_estimate[nSys_unique-1] = std::min( uncMin_sr_estimate[nSys_unique-1], (100*sr_estimate_err/sr_estimate) );
      
      
      // Calc SR estimate for total error for this cat
      cats_vs_sys[iSR][nSys_unique-1] = (100*sr_estimate_err/sr_estimate);
    
    
      // Final Results Table
      fprintf(f_results, " %s & %s ", v_bkgEst[iBkgEst].regionName[iSR].Data(), v_bkgEst[iBkgEst].binName[iSR].Data() );
      fprintf(f_results, " & %.2f $\\pm$ %.2f " , Data_CR_cr2sr_yield, Data_CR_cr2sr_error );
      if(useFraction) fprintf(f_results, " & %.2f $\\pm$ %.2f " , MC_CR_fraction, MC_CR_fraction_err );
      fprintf(f_results, " & %.2f $\\pm$ %.2f " , tf_cr2sr, tf_cr2sr_err);
      if(!oneTF) fprintf(f_results, " & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f " , tf_srBin, tf_srBin_err, tf_tot, tf_tot_err);
      fprintf(f_results, " & %.2f $\\pm$ %.2f " , sr_estimate, sr_estimate_err);
      fprintf(f_results, " \\"); fprintf(f_results, "\\ \n");
      if( iSR==(nSRs-1) ) fprintf(f_results, "\\hline \n");
      else{
	if( v_bkgEst[iBkgEst].regionName_short[iSR] != v_bkgEst[iBkgEst].regionName_short[iSR+1] ){
	  fprintf(f_results, "\\hline \n");
	}
      }
	

    } // end loop over signal regions

  

    //
    // Summary table of uncertainties
    //
    fprintf(f_uncFile_summary, "Data Stats & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[0], uncMax_cr_data_cr2sr[0]);
    if(useFraction) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_fraction[0], uncMax_fraction[0] );
    fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_cr2sr[0], uncMax_tf_cr2sr[0] );
    if(!oneTF) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_srBin[0], uncMax_tf_srBin[0], uncMin_tf_tot[0], uncMax_tf_tot[0] );
    fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_sr_estimate[0], uncMax_sr_estimate[0] );
    fprintf(f_uncFile_summary, " \\"); fprintf(f_uncFile_summary, "\\ \n");

    fprintf(f_uncFile_summary, "MC Stats & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[1], uncMax_cr_data_cr2sr[1]);
    if(useFraction) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_fraction[1], uncMax_fraction[1] );
    fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_cr2sr[1], uncMax_tf_cr2sr[1] );
    if(!oneTF) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_srBin[1], uncMax_tf_srBin[1], uncMin_tf_tot[1], uncMax_tf_tot[1] );
    fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_sr_estimate[1], uncMax_sr_estimate[1] );
    fprintf(f_uncFile_summary, " \\"); fprintf(f_uncFile_summary, "\\ \\hline \\hline \n");

    if(useFraction){
      fprintf(f_uncFile_summary, "CR Impurity & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[2], uncMax_cr_data_cr2sr[2]);
      if(useFraction) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_fraction[2], uncMax_fraction[2] );
      fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_cr2sr[2], uncMax_tf_cr2sr[2] );
      if(!oneTF) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_srBin[2], uncMax_tf_srBin[2], uncMin_tf_tot[2], uncMax_tf_tot[2] );
      fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_sr_estimate[2], uncMax_sr_estimate[2] );
      fprintf(f_uncFile_summary, " \\"); fprintf(f_uncFile_summary, "\\ \n");
    }
    
    int unique_sys = additional_sys/2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      
      fprintf(f_uncFile_summary, "%s & $%.1f~-~%.1f~\\%%$ ", sys_name.Data(), uncMin_cr_data_cr2sr[unique_sys], uncMax_cr_data_cr2sr[unique_sys]);
      if(useFraction) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_fraction[unique_sys], uncMax_fraction[unique_sys] );
      fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_cr2sr[unique_sys], uncMax_tf_cr2sr[unique_sys] );
      if(!oneTF) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_srBin[unique_sys], uncMax_tf_srBin[unique_sys], uncMin_tf_tot[unique_sys], uncMax_tf_tot[unique_sys] );
      fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_sr_estimate[unique_sys], uncMax_sr_estimate[unique_sys] );
      fprintf(f_uncFile_summary, " \\"); fprintf(f_uncFile_summary, "\\ \n");

      unique_sys++;
    }
    fprintf(f_uncFile_summary, "\\hline \\hline \n");

    fprintf(f_uncFile_summary, "Total & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_cr2sr[nSys_unique-1], uncMax_cr_data_cr2sr[nSys_unique-1]);
    if(useFraction) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_fraction[nSys_unique-1], uncMax_fraction[nSys_unique-1] );
    fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_cr2sr[nSys_unique-1], uncMax_tf_cr2sr[nSys_unique-1] );
    if(!oneTF) fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_tf_srBin[nSys_unique-1], uncMax_tf_srBin[nSys_unique-1], uncMin_tf_tot[nSys_unique-1], uncMax_tf_tot[nSys_unique-1] );
    fprintf(f_uncFile_summary, " & $%.1f~-~%.1f~\\%%$ ", uncMin_sr_estimate[nSys_unique-1], uncMax_sr_estimate[nSys_unique-1] );
    fprintf(f_uncFile_summary, " \\"); fprintf(f_uncFile_summary, "\\ \\hline \n");

    // Fromatting for End of Uncertainty Summary File
    fprintf(f_uncFile_summary, "\\end{tabular} \n");
    fprintf(f_uncFile_summary, "} \n");
    fprintf(f_uncFile_summary, "\\end{table} \n");
    fprintf(f_uncFile_summary, "\\end{document} \n");
    fclose(f_uncFile_summary);
    

    //
    // Uncertainty Summary File
    //
    fprintf(f_uncFile_summaryByCat, "Data Stats");
    for(int iSR=0; iSR<nSRs; iSR++){
      fprintf(f_uncFile_summaryByCat, " & %.1f\\%% ", cats_vs_sys[iSR][0]);
    }
    fprintf(f_uncFile_summaryByCat, "\\"); fprintf(f_uncFile_summaryByCat, "\\ \n");
    
    fprintf(f_uncFile_summaryByCat, "MC Stats");
    for(int iSR=0; iSR<nSRs; iSR++){
      fprintf(f_uncFile_summaryByCat, " & %.1f\\%% ", cats_vs_sys[iSR][1]);
    }
    fprintf(f_uncFile_summaryByCat, "\\"); fprintf(f_uncFile_summaryByCat, "\\ \\hline \n");
    
    if(useFraction){
      fprintf(f_uncFile_summaryByCat, "CR Impurity");
      for(int iSR=0; iSR<nSRs; iSR++){
	fprintf(f_uncFile_summaryByCat, " & %.1f\\%% ", cats_vs_sys[iSR][2]);
      }
      fprintf(f_uncFile_summaryByCat, "\\"); fprintf(f_uncFile_summaryByCat, "\\ \n");
    }
    
    
    int iSys_temp = additional_sys/2;
    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
      TString sys_name = systematicList[iSys].tex.c_str();
      sys_name.ReplaceAll(",~Up","");  sys_name.ReplaceAll("~Up","");
      sys_name.ReplaceAll(",~Down","");  sys_name.ReplaceAll("~Down","");
      fprintf(f_uncFile_summaryByCat, "%s ", sys_name.Data() );
      for(int iSR=0; iSR<nSRs; iSR++){
	fprintf(f_uncFile_summaryByCat, " & %.1f\\%% ", cats_vs_sys[iSR][iSys_temp]);
      }
      fprintf(f_uncFile_summaryByCat, "\\"); fprintf(f_uncFile_summaryByCat, "\\ \n");
      iSys_temp++;
    }
    fprintf(f_uncFile_summaryByCat, "\\hline \n");
    
    fprintf(f_uncFile_summaryByCat, "Total ");
    for(int iSR=0; iSR<nSRs; iSR++){
      fprintf(f_uncFile_summaryByCat, " & %.1f\\%% ", cats_vs_sys[iSR][nSys_unique-1]);
    }
  
    fprintf(f_uncFile_summaryByCat, "\\"); fprintf(f_uncFile_summaryByCat, "\\ \\hline \n");
    fprintf(f_uncFile_summaryByCat, "\\end{tabular} \n");
    fprintf(f_uncFile_summaryByCat, "} \n");
    fprintf(f_uncFile_summaryByCat, "\\end{table} \n");
    fprintf(f_uncFile_summaryByCat, "\\end{document} \n");
    fclose(f_uncFile_summaryByCat);
  
      
    // Table of background estimate
    fprintf(f_results, "\\end{tabular} \n");
    fprintf(f_results, "} \n");
    fprintf(f_results, "\\end{table} \n");
    fprintf(f_results, "\\end{document} \n");
    fclose(f_results);
    

    // Uncertainty file for each category
    fprintf(f_uncFile_fullCalc, "\\end{document} \n");
    fclose(f_uncFile_fullCalc);
  
    // Write and Close Root File for Limit Setting
    f_out->Write();
    f_out->Close();
  
  
  } // end loop over bkgEstimate yields
  
  
  //
  // Clean up
  //
  f_SR_mc->Close();
  f_CR_mc->Close();
  f_CR_data->Close();

  return 0;
}
