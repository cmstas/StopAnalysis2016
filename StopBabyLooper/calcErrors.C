#include "stopBabyLooper.h"

void calcErrors(){


  std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sampleList;

  std::pair< sampleInfo::ID, genClassyInfo::ID > sample;


  // All Background
  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_allBkg;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // ttbar
  sample.first  = sampleInfo::k_ttbar;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_ttbar;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);
  
  sample.first  = sampleInfo::k_ttbar;
  sample.second = genClassyInfo::k_ee1lep;
  sampleList.push_back(sample);


  // single t
  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);

  
  // single t, tW
  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_singleT_tW;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);


  // W+Jets
  sample.first  = sampleInfo::k_WJetsToLNu;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);
  
  
  // DY+Jets
  sample.first  = sampleInfo::k_DYJetsToLL;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);
  

  // TTW
  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTW;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);


  // TTZ
  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_TTZ;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // WW
  sample.first  = sampleInfo::k_WW;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WW;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WW;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);


  // WZ
  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_ee1lep_fromW;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_WZ;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // ZZ
  sample.first  = sampleInfo::k_ZZ;
  sample.second = genClassyInfo::k_incl;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_ZZ;
  sample.second = genClassyInfo::k_ge2lep;
  sampleList.push_back(sample);

  sample.first  = sampleInfo::k_ZZ;
  sample.second = genClassyInfo::k_ZtoNuNu;
  sampleList.push_back(sample);


  // tZq
  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_incl;
  //sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ge2lep;
  //sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ee1lep_fromTop;
  //sampleList.push_back(sample);

  sample.first  = sampleInfo::k_tZq;
  sample.second = genClassyInfo::k_ZtoNuNu;
  //sampleList.push_back(sample);
  

  // Do calculation
  calcThis(sampleList);

    
  return;
}


//
// Functions
// 
void calcThis(std::vector< std::pair< sampleInfo::ID, genClassyInfo::ID > > sampleList ){  

  // User parameters
  bool verbose = false;

  TString input_dir       = "Output/Histos/";
  TString output_dir_tex  = "Output/Tables/";

  
  // Signal and Control Regions
  std::vector<std::string> regionList;
  regionList.push_back("SR");
  regionList.push_back("CR0b");
  regionList.push_back("CR0b_tightBTagHighMlb");
  regionList.push_back("CR2l");


  // Systematics List, currently using entire list 
  sysInfo::Util nominal_sys( sysInfo::k_nominal );
  sysInfo::vect_util systematicList;
  systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) );
  for(int iSys=1; iSys<sysInfo::k_nSys; iSys++){
      //
      // Example Method To Exclude Specific Systematics
      //
      //if( iSys==sysInfo::k_pdfUp ) continue;
      //if( iSys==sysInfo::k_pdfDown ) continue;
      systematicList.push_back( sysInfo::Util(sysInfo::ID(iSys)) );
  }
   

  // Category List
  std::vector< std::vector<yieldHelper> > fileList;
  std::vector<yieldHelper> catList;
  yieldHelper cat;
  /*
  //
  // Yields, 2016 ICHEP, 12.9fb
  //

  // 2jets
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 1; cat.tex = "2jets,~modTopness$\\ge6.4$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 2; cat.tex = "2jets,~modTopness$\\ge6.4$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 3; cat.tex = "2jets,~modTopness$\\ge6.4$,~$MET>450$";
  catList.push_back( cat );
  
  // 3jets
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 4; cat.tex = "3jets,~MT2W$\\ge$200,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 5; cat.tex = "3jets,~MT2W$\\ge$200,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 6; cat.tex = "3jets,~MT2W$\\ge$200,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 7; cat.tex = "3jets,~MT2W$\\ge$200,~$MET>550$";
  catList.push_back( cat );
  
  // 4jets lowDM
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 8; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 9; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 10; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$MET>450$";
  catList.push_back( cat );
  
  // 4jets highDM
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 11; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 12; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 13; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 14; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP"; cat.binNumber = 15; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$MET>650$";
  catList.push_back( cat );

  fileList.push_back( catList );

  catList.clear();


  //
  // Yields, ICHEP ext30fb
  //
  
  // 2jet
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 1; cat.tex = "2jets,~modTopness$\\ge6.4$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 2; cat.tex = "2jets,~modTopness$\\ge6.4$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 3; cat.tex = "2jets,~modTopness$\\ge6.4$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 4; cat.tex = "2jets,~modTopness$\\ge6.4$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 5; cat.tex = "2jets,~modTopness$\\ge6.4$,~$MET>650$";
  catList.push_back( cat );
  
  // 3jet
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 6; cat.tex = "3jets,~MT2W$\\ge$200,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 7; cat.tex = "3jets,~MT2W$\\ge$200,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 8; cat.tex = "3jets,~MT2W$\\ge$200,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 9; cat.tex = "3jets,~MT2W$\\ge$200,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 10; cat.tex = "3jets,~MT2W$\\ge$200,~$MET>650$";
  catList.push_back( cat );
  
  // 4jet, lowDm
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 11; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 12; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 13; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 14; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 15; cat.tex = "$\\ge$4jets,~MT2W$<200$,~$MET>650$";
  catList.push_back( cat );
  
  // 4jet, highDm
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 16; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 17; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 18; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 19; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 20; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$650<MET<800$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_ICHEP_ext30fb"; cat.binNumber = 21; cat.tex = "$\\ge$4jets,~MT2W$\\ge200$,~$MET>800$";
  catList.push_back( cat );
  
  fileList.push_back( catList );
  catList.clear();


  //
  // Yields, dev ext30fb, mlb
  //
  catList.clear();

  // Region A, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 1; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 2; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$350<MET<500$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 3; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$MET>500$";
  catList.push_back( cat );
  
  // Region B, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 4; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 5; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 6; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$450<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 7; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$MET>650$";
  catList.push_back( cat );
  
  // Region C, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 8; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 9; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 10; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 11; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 12; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$MET>650$";
  catList.push_back( cat );
  
  // Region D, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 13; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 14; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 15; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 16; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$MET>550$";
  catList.push_back( cat );
  
  // Region E, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 17; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 18; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$350<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 19; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$MET>550$";
  catList.push_back( cat );
  
  // Region F, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 20; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 21; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$350<MET<500$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 22; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$MET>500$";
  catList.push_back( cat );
  
  // Region G, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 23; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 24; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 25; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 26; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$MET>600$";
  catList.push_back( cat );
  
  // Region H, mlb
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 27; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 28; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$350<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v1"; cat.binNumber = 29; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$MET>650$";
  catList.push_back( cat );
    
  fileList.push_back( catList );
  catList.clear();
  */

  //
  // Yields, dev ext30fb, mlb with tight bTagging
  //
  catList.clear();
  
  // Region A, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 1; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 2; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 3; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 4; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$MET>600$";
  catList.push_back( cat );
  
  // Region B, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 5; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 6; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$450<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 7; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$MET>600$";
  catList.push_back( cat );
  
  // Region C, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 8; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 9; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 10; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 11; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 12; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}<175$,~$MET>650$";
  catList.push_back( cat );
  
  // Region D, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 13; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 14; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 15; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 16; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$M_{lb}\\ge175$,~$MET>550$";
  catList.push_back( cat );
  
  // Region E, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 17; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 18; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$350<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 19; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}<175$,~$MET>550$";
  catList.push_back( cat );
  
  // Region F, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 20; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 21; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$M_{lb}\\ge175$,~$MET>450$";
  catList.push_back( cat );
  
  // Region G, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 22; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 23; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 24; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 25; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}<175$,~$MET>600$";
  catList.push_back( cat );
  
  // Region H, mlb and tight bTagging
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 26; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_mlb_v2"; cat.binNumber = 27; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$M_{lb}\\ge175$,~$MET>450$";
  catList.push_back( cat );
  
  fileList.push_back( catList );
  catList.clear();

  
  /*
  //
  // Yields, dev ext30fb, lead bJet pT
  //
  catList.clear();
  
  // Region A, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 1; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 2; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 3; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$450<MET<600$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 4; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$MET>600$";
  catList.push_back( cat );
  
  // Region B, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 5; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt\\ge200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 6; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt\\ge200$,~$350<MET<500$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 7; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt\\ge200$,~$500<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 8; cat.tex = "$<4$jets,~modTopness$\\ge10$,~$leadBJetPt\\ge200$,~$MET>650$";
  catList.push_back( cat );
  
  // Region C, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 9; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt<200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 10; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt<200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 11; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt<200$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 12; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt<200$,~$550<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 13; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt<200$,~$MET>650$";
  catList.push_back( cat );
  
  // Region D, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 14; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt\\ge200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 15; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt\\ge200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 16; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt\\ge200$,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 17; cat.tex = "$\\ge4$jets,~modTopness$<0.0$,~$leadBJetPt\\ge200$,~$MET>550$";
  catList.push_back( cat );
  
  // Region E, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 18; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$leadBJetPt<200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 19; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$leadBJetPt<200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 20; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$leadBJetPt<200$,~$MET>450$";
  catList.push_back( cat );
  
  // Region F, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 21; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$leadBJetPt\\ge200$,~$250<MET<400$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 22; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$leadBJetPt\\ge200$,~$350<MET<500$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 23; cat.tex = "$\\ge4$jets,~$0.0<$modTopness$<10$,~$leadBJetPt\\ge200$,~$MET>500$";
  catList.push_back( cat );
  
  // Region G, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 24; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 25; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 26; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$450<MET<650$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 27; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$leadBJetPt<200$,~$MET>650$";
  catList.push_back( cat );
  
  // Region H, bJetPt
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 28; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$leadBJetPt\\ge200$,~$250<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_dev_ext30fb_bJetPt_v1"; cat.binNumber = 29; cat.tex = "$\\ge4$jets,~modTopness$\\ge10$,~$leadBJetPt\\ge200$,~$MET>450$";
  catList.push_back( cat );
    
  fileList.push_back( catList );
  catList.clear();
  */

  //
  // Yields, Top Corridor
  //
  cat.histName = "h_yields_SR_corridor"; cat.binNumber = 1; cat.tex = "top~corridor,~$250<MET<350$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_corridor"; cat.binNumber = 2; cat.tex = "top~corridor,~$350<MET<450$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_corridor"; cat.binNumber = 3; cat.tex = "top~corridor,~$450<MET<550$";
  catList.push_back( cat );
  cat.histName = "h_yields_SR_corridor"; cat.binNumber = 4; cat.tex = "top~corridor,~$MET>550$";
  catList.push_back( cat );
  
  fileList.push_back( catList );
  catList.clear();

  
  
  for(int iReg=0; iReg<(int)regionList.size(); iReg++){
  
    for(int iFile=0; iFile<(int)fileList.size(); iFile++){

      // Get category list for this table
      std::vector<yieldHelper> iCatList = fileList[iFile];

      // Get Name of yield Histo
      TString hNameBase = iCatList[0].histName;

      // pointer for tex file output
      FILE *yFile = NULL;
  
      TString texFile_name = output_dir_tex;
      texFile_name += "systematicsTable__";
      texFile_name += hNameBase;
      texFile_name += "__"; 
      texFile_name += regionList[iReg];
      texFile_name += ".tex";
      yFile = fopen(texFile_name.Data(), "w");
  
      cout << "  Making tex file: " << endl;
      cout << "    " << texFile_name << endl;
      
      // Tex File Formatting
      fprintf(yFile, "\\documentclass{article}\n");
      fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
      fprintf(yFile, "\\usepackage{chngpage}\n\n");
      fprintf(yFile, "\\begin{document}\n");
      fprintf(yFile, "\\tiny\n");


      // Loop over samples
      for(int iSample=0; iSample<(int)sampleList.size(); iSample++){

    
	// Get utils from input id's
	sampleInfo::sampleUtil sample( sampleList[iSample].first );
    	
	// And which genClassification for the sample
	genClassyInfo::Util genClassy( sampleList[iSample].second );

	
	// Open input file
	TString inFile_name = input_dir;
	inFile_name += sample.label;
	inFile_name += ".root";
	
	cout << "        Analyzing File: " << inFile_name << endl;
	
	TFile *in_file = new TFile(inFile_name, "read");
	
	// Loop over cateogry List
	for(int iCat=0; iCat<(int)iCatList.size(); iCat++){
	  
	  TString regionListTitle = regionList[iReg];
          regionListTitle.ReplaceAll("_", " ");

	  fprintf(yFile, "\n \n \n \n");
	  fprintf(yFile, "\\begin{table} \n");
	  fprintf(yFile, "\\caption{ %s,~%s,~genClassy:~%s,~cateogry:~%s } \n", sample.tex.c_str(), regionListTitle.Data(), genClassy.tex.c_str(), iCatList[iCat].tex.c_str());
	  fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
	  fprintf(yFile, "Systematic & Nominal & Sys Up, (\\%%) & Sys Down, (\\%%) & \\%% Uncertainty");
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");
	  
      
	  // Nominal histogram name
	  TString hName = hNameBase;
	  hName += "__";
	  hName += regionList[iReg];
	  hName += "__genClassy_";
	  hName += genClassy.label;
	  hName += "__systematic_";
	  hName += nominal_sys.label;

	  TH1F *h_nom = (TH1F*)in_file->Get(hName);
	  if(!h_nom) cout << "BAD HISTO: " << hName << endl;
	  
	  double yield_nom  = h_nom->GetBinContent( catList[iCat].binNumber );
	  double error_nom  = h_nom->GetBinError( catList[iCat].binNumber );
      
	  double statError = error_nom;
	  double sysError = pow( statError, 2 );

	  fprintf(yFile, " Statistical~Error & " );
	  fprintf(yFile, " %.2f & ", yield_nom);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_nom+statError, (100*(statError/yield_nom)) );
	  fprintf(yFile, " %.2f (%.2f) & ", yield_nom-statError, (-100*(statError/yield_nom)) );
	  fprintf(yFile, " %.2f ", (100*(statError/yield_nom)) );
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	      
	    
	  if( !sample.isData ){

	    // Loop over systematics
	    for(int iSys=1; iSys<(int)systematicList.size(); iSys+=2){
	
	      TString hNameUp = hNameBase;
	      hNameUp += "__";
	      hNameUp += regionList[iReg];
	      hNameUp += "__genClassy_";
	      hNameUp += genClassy.label;
	      hNameUp += "__systematic_";
	      hNameUp += systematicList[iSys].label;

	      TH1F *h_up = (TH1F*)in_file->Get(hNameUp);
	      if(!h_up) cout << "BAD HISTO: " << hNameUp << endl;
	  
	      double yield_up   = h_up->GetBinContent( catList[iCat].binNumber );
	      //double error_up   = h_up->GetBinError( catList[iCat].binNumber );
	      double percent_up = (100*(yield_up-yield_nom))/yield_nom;
 
	  
	      TString hNameDown = hNameBase;
	      hNameDown += "__";
	      hNameDown += regionList[iReg];
	      hNameDown += "__genClassy_";
	      hNameDown += genClassy.label;
	      hNameDown += "__systematic_";
	      hNameDown += systematicList[iSys+1].label;


	      TH1F *h_down = (TH1F*)in_file->Get(hNameDown);
	      if(!h_down) cout << "BAD HISTO: " << hNameDown << endl;
	  
	      double yield_dn   = h_down->GetBinContent( catList[iCat].binNumber );
	      //double error_dn   = h_down->GetBinError( catList[iCat].binNumber );
	      double percent_dn = (100*(yield_dn-yield_nom))/yield_nom;
	  
	  
	      double maxDiff = fabs(yield_nom - yield_up);
	      maxDiff = std::max( maxDiff, fabs(yield_nom - yield_dn) );
	      double maxPercentDiff = (100*maxDiff)/yield_nom;
	  
	  
	      sysError += pow( maxDiff, 2 );
	  

	      TString sys_label_tex = systematicList[iSys+1].tex;

	      sys_label_tex.ReplaceAll(",~Up","");
	      sys_label_tex.ReplaceAll(",~Down","");

	      sys_label_tex.ReplaceAll("~Up","");
	      sys_label_tex.ReplaceAll("~Down","");
	  

	      fprintf(yFile, " %s & ", sys_label_tex.Data() );
	      fprintf(yFile, " %.2f & ", yield_nom);
	      fprintf(yFile, " %.2f (%.2f) & ", yield_up, percent_up);
	      fprintf(yFile, " %.2f (%.2f) & ", yield_dn, percent_dn);
	      fprintf(yFile, " %.2f ", maxPercentDiff);
	  
	      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	
	  	  
	    } // end loop over systematics

	  } // end if sample is data
	
	  sysError = sqrt( sysError );
	
	
	  //
	  // Total Error
	  //
	  fprintf(yFile, "\\hline \n");
	  fprintf(yFile, " Total Uncertainty & " );
	  fprintf(yFile, " %.2f & ", yield_nom);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_nom+sysError, (100*(sysError))/yield_nom);
	  fprintf(yFile, " %.2f (%.2f) & ", yield_nom-sysError, (100*(sysError))/yield_nom);
	  fprintf(yFile, " %.2f ", (100*(sysError))/yield_nom);
	
	  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
	
	  fprintf(yFile, "\\end{tabular} \n");
	  fprintf(yFile, "\\end{table} \n");
	
	  fprintf(yFile, "\n \n \n \n");
	  fprintf(yFile, "\\clearpage");

	} // end loop over categories

	if(verbose) cout << endl;
      
	// Clean up
	in_file->Close();
  	
      } // end loop over samples
  
      if(verbose) cout << endl << endl;

      // print end of tex document
      fprintf(yFile, "\\end{document} \n");
      fclose(yFile);
    
    } // end loop over files
    
  } // end loop over regions
   
  return;
}
