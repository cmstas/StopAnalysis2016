#include "categoryInfo.h"
#include "../StopBabyMaker/stop_variables/mt2w.h"
#include "../StopBabyMaker/stop_variables/topness.h"

//////////////////////////////////////////////////////////////////////

categoryInfo::categoryUtil::categoryUtil( categoryInfo::ID category ){

  switch( category ){

  case( k_incl ):
    id    = category;
    label = "incl";
    title = "Post-Selection";
    tex   = "Post~Selection";
    break;  

  case( k_ge2jets ):
    id    = category;
    label = "ge2jets";
    title = ">=2 jets";
    tex   = "$\\ge2$~jets";
    break;

  case( k_ge2jets_ge6p4modTop ):
    id    = category;
    label = "ge2jets_ge6p4modTop";
    title = ">=2 jets, modTopness>=6.4";
    tex   = "$\\ge2$~jets,~modTopness$\\ge6.4$";
    break;  

  case( k_ge2jets_lt200mt2w ):
    id    = category;
    label = "ge2jets_lt200mt2w";
    title = ">=2 jets, MT2W<200";
    tex   = "$\\ge2$~jets,~MT2W$<200$";
    break;

  case( k_ge2jets_ge200mt2w ):
    id    = category;
    label = "ge2jets_ge200mt2w";
    title = ">=2 jets, MT2W>=200";
    tex   = "$\\ge2$~jets,~MT2W$\\ge200$";
    break;  

  case( k_ee2jets ):
    id    = category;
    label = "ee2jets";
    title = "2 jets";
    tex   = "$2$~jets";
    break;  

  case( k_ee2jets_250to350met ):
    id    = category;
    label = "ee2jets_250to350met";
    title = "2 jets, 250<MET<350";
    tex   = "$2$~jets,~$250<MET<350$";
    break;
    
  case( k_ee2jets_350toInfmet ):
    id    = category;
    label = "ee2jets_350toInfmet";
    title = "2 jets, MET>350";
    tex   = "$2$~jets,~$MET>350$";
    break;

  case( k_ee2jets_ge6p4modTop ):
    id    = category;
    label = "ee2jets_ge6p4modTop";
    title = "2 jets, modTopness>=6.4";
    tex   = "$2$~jets,~modTopness$\\ge6.4$";
    break;

  case( k_ee2jets_ge6p4modTop_150to250met ):
    id    = category;
    label = "ee2jets_ge6p4modTop_150to250met";
    title = "2 jets, modTopness>=6.4, 150<MET<250";
    tex   = "$2$~jets,~modTopness$\\ge6.4$,~$150<MET<250$";
    break;

  case( k_ee2jets_ge6p4modTop_250to350met ):
    id    = category;
    label = "ee2jets_ge6p4modTop_250to350met";
    title = "2 jets, modTopness>=6.4, 250<MET<350";
    tex   = "$2$~jets,~modTopness$\\ge6.4$,~$250<MET<350$";
    break;

  case( k_ee2jets_ge6p4modTop_350toInfmet ):
    id    = category;
    label = "ee2jets_ge6p4modTop_350toInfmet";
    title = "2 jets, modTopness>=6.4, MET>350";
    tex   = "$2$~jets,~modTopness$\\ge6.4$,~$MET>350$";
    break;

  case( k_ee2jets_ge6p4modTop_350to450met ):
    id    = category;
    label = "ee2jets_ge6p4modTop_350to450met";
    title = "2 jets, modTopness>=6.4, 350<MET<450";
    tex   = "$2$~jets,~modTopness$\\ge6.4$,~$350<MET<450$";
    break;

  case( k_ee2jets_ge6p4modTop_450toInfmet ):
    id    = category;
    label = "ee2jets_ge6p4modTop_450toInfmet";
    title = "2 jets, modTopness>=6.4, MET>450";
    tex   = "$2$~jets,~modTopness$\\ge6.4$,~$MET>450$";
    break;

  case( k_ge3jets ):
    id    = category;
    label = "ge3jets";
    title = ">=3 jets";
    tex   = "$\\ge3$~jets";
    break;

  case( k_ge3jets_lt200mt2w ):
    id    = category;
    label = "ge3jets_lt200mt2w";
    title = ">=3 jets, MT2W<200";
    tex   = "$\\ge3$~jets,~MT2W$<200$";
    break;

  case( k_ge3jets_ge200mt2w ):
    id    = category;
    label = "ge3jets_ge200mt2w";
    title = ">=3 jets, MT2W>=200";
    tex   = "$\\ge3$~jets,~MT2W$\\ge200$";
    break;  

  case( k_ee3jets ):
    id    = category;
    label = "ee3jets";
    title = "3 jets";
    tex   = "$3$~jets";
    break;

  case( k_ee3jets_250to350met ):
    id    = category;
    label = "ee3jets_250to350met";
    title = "3 jets, 250<MET<350";
    tex   = "$3$~jets,~$250<MET<350$";
    break;

  case( k_ee3jets_350toInfmet ):
    id    = category;
    label = "ee3jets_350toInfmet";
    title = "3 jets, MET>350";
    tex   = "$3$~jets,~$MET>350$";
    break;

  case( k_ee3jets_lt200mt2w ):
    id    = category;
    label = "ee3jets_lt200mt2w";
    title = "3 jets, MT2W<200";
    tex   = "$3$~jets,~MT2W$<200$";
    break;

  case( k_ee3jets_ge200mt2w ):
    id    = category;
    label = "ee3jets_ge200mt2w";
    title = "3 jets, MT2W>=200";
    tex   = "$3$~jets,~MT2W$\\ge200$";
    break;

  case( k_ee3jets_ge200mt2w_150to250met ):
    id    = category;
    label = "ee3jets_ge200mt2w_150to250met";
    title = "3 jets, MT2W>=200, 150<MET<250";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$150<MET<250$";
    break;

  case( k_ee3jets_ge200mt2w_250to350met ):
    id    = category;
    label = "ee3jets_ge200mt2w_250to350met";
    title = "3 jets, MT2W>=200, 250<MET<350";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$250<MET<350$";
    break;

  case( k_ee3jets_ge200mt2w_350toInfmet ):
    id    = category;
    label = "ee3jets_ge200mt2w_350toInfmet";
    title = "3 jets, MT2W>=200, MET>350";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$MET>350$";
    break;

  case( k_ee3jets_ge200mt2w_350to450met ):
    id    = category;
    label = "ee3jets_ge200mt2w_350to450met";
    title = "3 jets, MT2W>=200, 350<MET<450";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$350<MET<450$";
    break;

  case( k_ee3jets_ge200mt2w_450toInfmet ):
    id    = category;
    label = "ee3jets_ge200mt2w_450toInfmet";
    title = "3 jets, MT2W>=200, MET>450";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$MET>450$";
    break;
  
  case( k_ee3jets_ge200mt2w_450to550met ):
    id    = category;
    label = "ee3jets_ge200mt2w_450to550met";
    title = "3 jets, MT2W>=200, 450<MET<550";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$450<MET<550$";
    break;
  
  case( k_ee3jets_ge200mt2w_550toInfmet ):
    id    = category;
    label = "ee3jets_ge200mt2w_550toInfmet";
    title = "3 jets, MT2W>=200, MET>550";
    tex   = "$3$~jets,~MT2W$\\ge200$,~$MET>550$";
    break;

  case( k_ge4jets ):
    id    = category;
    label = "ge4jets";
    title = ">=4 jets";
    tex   = "$\\ge4$~jets";
    break;

  case( k_ge4jets_250toInfmet ):
    id    = category;
    label = "ge4jets_250toInfmet";
    title = ">=4 jets, MET>250";
    tex   = "$\\ge4$~jets,~$MET>250$";
    break;
    
  case( k_ge4jets_250to325met ):
    id    = category;
    label = "ge4jets_250to325met";
    title = ">=4 jets, 250<MET<325";
    tex   = "$\\ge4$~jets,~$250<MET<325$";
    break;

  case( k_ge4jets_325toInfmet ):
    id    = category;
    label = "ge4jets_325toInfmet";
    title = ">=4 jets, MET>325";
    tex   = "$\\ge4$~jets,~$MET>325$";
    break;

  case( k_ge4jets_250to350met ):
    id    = category;
    label = "ge4jets_250to350met";
    title = ">=4 jets, 250<MET<350";
    tex   = "$\\ge4$~jets,~$250<MET<350$";
    break;

  case( k_ge4jets_350to450met ):
    id    = category;
    label = "ge4jets_350to450met";
    title = ">=4 jets, 350<MET<450";
    tex   = "$\\ge4$~jets,~$350<MET<450$";
    break;

  case( k_ge4jets_450toInfmet ):
    id    = category;
    label = "ge4jets_450toInfmet";
    title = ">=4 jets, MET>450";
    tex   = "$\\ge4$~jets,~$MET>450$";
    break;

  case( k_ge4jets_lt200mt2w ):
    id    = category;
    label = "ge4jets_lt200mt2w";
    title = ">=4 jets, MT2W<200";
    tex   = "$\\ge4$~jets,~MT2W$<200$";
    break;

  case( k_ge4jets_lt200mt2w_150to250met ):
    id    = category;
    label = "ge4jets_lt200mt2w_150to250met";
    title = ">=4 jets, MT2W<200, 150<MET<250";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$150<MET<250$";
    break;

  case( k_ge4jets_lt200mt2w_250to325met ):
    id    = category;
    label = "ge4jets_lt200mt2w_250to325met";
    title = ">=4 jets, MT2W<200, 250<MET<325";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$250<MET<325$";
    break;

  case( k_ge4jets_lt200mt2w_325toInfmet ):
    id    = category;
    label = "ge4jets_lt200mt2w_325toInfmet";
    title = ">=4 jets, MT2W<200, MET>325";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$MET>325$";
    break;

  case( k_ge4jets_lt200mt2w_250to350met ):
    id    = category;
    label = "ge4jets_lt200mt2w_250to350met";
    title = ">=4 jets, MT2W<200, 250<MET<350";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$250<MET<350$";
    break;

  case( k_ge4jets_lt200mt2w_350to450met ):
    id    = category;
    label = "ge4jets_lt200mt2w_350to450met";
    title = ">=4 jets, MT2W<200, 350<MET<450";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$350<MET<450$";
    break;

  case( k_ge4jets_lt200mt2w_450toInfmet ):
    id    = category;
    label = "ge4jets_lt200mt2w_450toInfmet";
    title = ">=4 jets, MT2W<200, MET>450";
    tex   = "$\\ge4$~jets,~MT2W$<200$,~$MET>450$";
    break;

  case( k_ge4jets_ge200mt2w ):
    id    = category;
    label = "ge4jets_ge200mt2w";
    title = ">=4 jets, MT2W>=200";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$";
    break;  

  case( k_ge4jets_ge200mt2w_150to250met ):
    id    = category;
    label = "ge4jets_ge200mt2w_150to250met";
    title = ">=4 jets, MT2W>=200, 150<MET<250";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$150<MET<250$";
    break;

  case( k_ge4jets_ge200mt2w_250to350met ):
    id    = category;
    label = "ge4jets_ge200mt2w_250to350met";
    title = ">=4 jets, MT2W>=200, 250<MET<350";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$250<MET<350$";
    break;

  case( k_ge4jets_ge200mt2w_350to450met ):
    id    = category;
    label = "ge4jets_ge200mt2w_350to450met";
    title = ">=4 jets, MT2W>=200, 350<MET<450";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$350<MET<450$";
    break;

  case( k_ge4jets_ge200mt2w_350toInfmet ):
    id    = category;
    label = "ge4jets_ge200mt2w_350toInfmet";
    title = ">=4 jets, MT2W>=200, MET>350";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$MET>350$";
    break;

  case( k_ge4jets_ge200mt2w_450toInfmet ):
    id    = category;
    label = "ge4jets_ge200mt2w_450toInfmet";
    title = ">=4 jets, MT2W>=200, MET>450";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$MET>450$";
    break;

  case( k_ge4jets_ge200mt2w_450to550met ):
    id    = category;
    label = "ge4jets_ge200mt2w_450to550met";
    title = ">=4 jets, MT2W>=200, 450<MET<550";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$450<MET<550$";
    break;

  case( k_ge4jets_ge200mt2w_550toInfmet ):
    id    = category;
    label = "ge4jets_ge200mt2w_550toInfmet";
    title = ">=4 jets, MT2W>=200, MET>550";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$MET>550$";
    break;

  case( k_ge4jets_ge200mt2w_550to650met ):
    id    = category;
    label = "ge4jets_ge200mt2w_550to650met";
    title = ">=4 jets, MT2W>=200, 550<MET<650";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$550<MET<650$";
    break;
  
  case( k_ge4jets_ge200mt2w_650toInfmet ):
    id    = category;
    label = "ge4jets_ge200mt2w_650toInfmet";
    title = ">=4 jets, MT2W>=200, MET>650";
    tex   = "$\\ge4$~jets,~MT2W$\\ge200$,~$MET>650$";
    break;

  case( k_ge5jets ):
    id    = category;
    label = "ge5jets";
    title = ">=5 jets";
    tex   = "$\\ge5$~jets";
    break;

  case( k_ge5jets_compM ):
    id    = category;
    label = "ge5jets_compM";
    title = ">=5 jets, compressedM";
    tex   = "$\\ge5$~jets,~compressedM";
    break;

  case( k_ge5jets_compM_150to250met ):
    id    = category;
    label = "ge5jets_compM_150to250met";
    title = ">=5 jets, compressedM, 150<MET<250";
    tex   = "$\\ge5$~jets,~compressedM,~$150<MET<250$";
    break;

  case( k_ge5jets_compM_250to350met ):
    id    = category;
    label = "ge5jets_compM_250to350met";
    title = ">=5 jets, compressedM, 250<MET<350";
    tex   = "$\\ge5$~jets,~compressedM,~$250<MET<350$";
    break;

  case( k_ge5jets_compM_350to450met ):
    id    = category;
    label = "ge5jets_compM_350to450met";
    title = ">=5 jets, compressedM, 350<MET<450";
    tex   = "$\\ge5$~jets,~compressedM,~$350<MET<450$";
    break;

  case( k_ge5jets_compM_450toInfmet ):
    id    = category;
    label = "ge5jets_compM_450toInfmet";
    title = ">=5 jets, compressedM, MET>450";
    tex   = "$\\ge5$~jets,~compressedM,~$MET>450$";
    break;

  case( k_ge1btags_ge50met ):
    id    = category;
    label = "ge1btags_ge50met";
    title = ">=1 b-tagged jets, MET>50";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>50$";
    break;

  case( k_ge1btags_ge100met ):
    id    = category;
    label = "ge1btags_ge100met";
    title = ">=1 b-tagged jets, MET>100";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>100$";
    break;

  case( k_ge1btags_ge150met ):
    id    = category;
    label = "ge1btags_ge150met";
    title = ">=1 b-tagged jets, MET>150";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>150$";
    break;
    
  case( k_ge1btags_ge200met ):
    id    = category;
    label = "ge1btags_ge200met";
    title = ">=1 b-tagged jets, MET>200";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>200$";
    break;

  case( k_ge1btags_ge250met ):
    id    = category;
    label = "ge1btags_ge250met";
    title = ">=1 b-tagged jets, MET>250";
    tex   = "$\\ge1$~b-tagged~jets,~$MET>250$";
    break;

  case( k_ge2btags_ge50met ):
    id    = category;
    label = "ge2btags_ge50met";
    title = ">=2 b-tagged jets, MET>50";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>50$";
    break;

  case( k_ge2btags_ge100met ):
    id    = category;
    label = "ge2btags_ge100met";
    title = ">=2 b-tagged jets, MET>100";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>100$";
    break;

  case( k_ge2btags_ge150met ):
    id    = category;
    label = "ge2btags_ge150met";
    title = ">=2 b-tagged jets, MET>150";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>150$";
    break;
    
  case( k_ge2btags_ge200met ):
    id    = category;
    label = "ge2btags_ge200met";
    title = ">=2 b-tagged jets, MET>200";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>200$";
    break;

  case( k_ge2btags_ge250met ):
    id    = category;
    label = "ge2btags_ge250met";
    title = ">=2 b-tagged jets, MET>250";
    tex   = "$\\ge2$~b-tagged~jets,~$MET>250$";
    break;

  case( k_ge4jets_ge1btags_ge50met ):
    id    = category;
    label = "ge4jets_ge1btags_ge50met";
    title = ">=4jets, >=1 b-tagged jets, MET>50";
    tex   = "$\\ge4$jets,~$\\ge1$~b-tagged~jets,~$MET>50$";
    break;

  case( k_ge4jets_ge1btags_ge250met ):
    id    = category;
    label = "ge4jets_ge1btags_ge250met";
    title = ">=4jets, >=1 b-tagged jets, MET>250";
    tex   = "$\\ge4$jets,~$\\ge1$~b-tagged~jets,~$MET>250$";
    break;

  default:
    std::cout << "Could not find category info from category enum provided!" << std::endl;
    id    = category;
    label = "NO CATEGORY INFO FOUND FROM ENUM PROVIDED";
    title = "NO CATEGORY INFO FOUND FROM ENUM PROVIDED";
    tex   = "NO CATEGORY INFO FOUND FROM ENUM PROVIDED";
    break;

  }; // end switch

}

//////////////////////////////////////////////////////////////////////

bool categoryInfo::passCategory( categoryInfo::ID category, bool add2ndLepToMet ){

  bool result = false;

  // If adding 2nd lepton to met, recalculate appropriate vars
  double met = babyAnalyzer.pfmet();
  //double met_phi = babyAnalyzer.pfmet_phi();
  double mt2w = babyAnalyzer.MT2W();
  double topness = babyAnalyzer.topnessMod();
  if( add2ndLepToMet ){
    /*
    if( (babyAnalyzer.ngoodleps()>=2) ||
    	(babyAnalyzer.ngoodleps()==1 && babyAnalyzer.nvetoleps()>=2 && babyAnalyzer.lep2_p4().Pt()>10.0 ) ){
      
      double metX = met*std::cos(met_phi);
      double metY = met*std::sin(met_phi);

      metX += babyAnalyzer.lep2_p4().Px();
      metY += babyAnalyzer.lep2_p4().Py();

      met = sqrt( metX*metX + metY*metY );
      met_phi = std::atan2(metY, metX);
      
      //
      // first, we need to sort jets by CSV value
      //
      std::vector<std::pair<int, double> > v_idx_csv;
      for (unsigned int idx = 0; idx < babyAnalyzer.ak4pfjets_p4().size(); idx++) {
        v_idx_csv.push_back(std::make_pair(idx, babyAnalyzer.ak4pfjets_CSV().at(idx)));
      }
      std::sort(v_idx_csv.begin(), v_idx_csv.end(), categoryInfo::sortByCSV);
      
      //
      // now get vector<LV> of b-jets and add-jets
      //
      std::vector<LorentzVector> mybjets;
      std::vector<LorentzVector> addjets;        
      for (auto p : v_idx_csv) {
        if (babyAnalyzer.ak4pfjets_passMEDbtag().at(p.first))
          mybjets.push_back(babyAnalyzer.ak4pfjets_p4().at(p.first));
        else if (mybjets.size() <=1 && (mybjets.size() + addjets.size()) < 3)
          addjets.push_back(babyAnalyzer.ak4pfjets_p4().at(p.first));                       
      }
      
      //
      // if == 2 jets, recalculate modified topness with new met
      //
      if (babyAnalyzer.ngoodjets() == 2)
        topness = CalcTopness_(1, met, met_phi, babyAnalyzer.lep1_p4(), mybjets, addjets);
      
      //
      // if >=3 jets, recalculate mt2w with new met
      //
      if (babyAnalyzer.ngoodjets() >= 3)   
        mt2w = CalcMT2W_(mybjets, addjets, babyAnalyzer.lep1_p4(), met, met_phi);
      
    } // end if 2nd lepton to add met to
    */
    
    met = babyAnalyzer.pfmet_rl();
    //met_phi = babyAnalyzer.pfmet_phi_rl();
    mt2w = babyAnalyzer.MT2W_rl();
    topness = babyAnalyzer.topnessMod_rl();

  } // end if add 2nd lepton to emt

  

  // Switch case
  switch( category ){

  case( k_incl ):
    result = true;
    break;

  case( k_ge2jets ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	met>=250.0 ) result = true;
    break;

  case( k_ge2jets_ge6p4modTop ):
    if( babyAnalyzer.ngoodjets()>=2 && 
	topness>=6.4 &&
	met>=250.0 ) result = true;
    break;  

  case( k_ge2jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()>=2 && 
	mt2w<200.0 &&
	met>=250.0      ) result = true;
    break;

  case( k_ge2jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()>=2 && 
	mt2w>=200.0 &&
	met>=250.0      ) result = true;
    break;  

  case( k_ee2jets ):
    if( babyAnalyzer.ngoodjets()==2 &&
	met>=250.0 ) result = true;
    break;  

  case( k_ee2jets_250to350met ):
    if( babyAnalyzer.ngoodjets()==2 &&
	met>=250.0 &&
	met<350       ) result = true;
    break;

  case( k_ee2jets_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==2 &&
	met>=350.0     ) result = true;
    break; 

  case( k_ee2jets_ge6p4modTop ):
    if( babyAnalyzer.ngoodjets()==2 && 
	topness>=6.4 &&
	met>=250.0 ) result = true;
    break;

  case( k_ee2jets_ge6p4modTop_150to250met ):
    if( babyAnalyzer.ngoodjets()==2 &&
	topness>=6.4 &&
	met>=150.0 &&
	met<250           ) result = true;
    break;

  case( k_ee2jets_ge6p4modTop_250to350met ):
    if( babyAnalyzer.ngoodjets()==2 &&
	topness>=6.4 &&
	met>=250.0 &&
	met<350           ) result = true;
    break;

  case( k_ee2jets_ge6p4modTop_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==2 &&
	topness>=6.4 &&
	met>=350.0        ) result = true;
    break;

  case( k_ee2jets_ge6p4modTop_350to450met ):
    if( babyAnalyzer.ngoodjets()==2 &&
	topness>=6.4 &&
	met>=350.0 &&
	met<450           ) result = true;
    break;

  case( k_ee2jets_ge6p4modTop_450toInfmet ):
    if( babyAnalyzer.ngoodjets()==2 &&
	topness>=6.4 &&
	met>=450.0        ) result = true;
    break;

  case( k_ge3jets ):
    if( babyAnalyzer.ngoodjets()>=3 &&
	met>=250.0 ) result = true;
    break;

  case( k_ge3jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()>=3 && 
	mt2w<200.0 &&
	met>=250.0      ) result = true;
    break;

  case( k_ge3jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()>=3 && 
	mt2w>=200.0 &&
	met>=250.0      ) result = true;
    break;  

  case( k_ee3jets ):
    if( babyAnalyzer.ngoodjets()==3 &&
	met>=250.0 ) result = true;
    break;

  case( k_ee3jets_250to350met ):
    if( babyAnalyzer.ngoodjets()==3 &&
	met>=250.0 &&
	met<350           ) result = true;
    break;

  case( k_ee3jets_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==3 &&
	met>=350.0    ) result = true;
    break;

  case( k_ee3jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()==3 && 
	mt2w<200.0 &&
	met>=250.0      ) result = true;
    break;

  case( k_ee3jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()==3 && 
	mt2w>=200.0 &&
	met>=250.0      ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_150to250met ):
    if( babyAnalyzer.ngoodjets()==3 &&
	mt2w>=200.0 && 
	met>=150.0 &&
	met<250        ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_250to350met ):
    if( babyAnalyzer.ngoodjets()==3 &&
	mt2w>=200.0 && 
	met>=250.0 &&
	met<350        ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_350toInfmet ):
    if( babyAnalyzer.ngoodjets()==3 &&
	mt2w>=200.0 && 
	met>=350.0    ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_350to450met ):
    if( babyAnalyzer.ngoodjets()==3 &&
	mt2w>=200.0 && 
	met>=350.0 &&
	met<450        ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_450toInfmet ):
    if( babyAnalyzer.ngoodjets()==3 &&
	mt2w>=200.0 && 
	met>=450.0    ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_450to550met ):
    if( babyAnalyzer.ngoodjets()==3 &&
	mt2w>=200.0 && 
	met>=450.0 &&
	met<550        ) result = true;
    break;

  case( k_ee3jets_ge200mt2w_550toInfmet ):
    if( babyAnalyzer.ngoodjets()==3 &&
	mt2w>=200.0 && 
	met>=550.0    ) result = true;
    break;

  case( k_ge4jets ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	met>=250.0 ) result = true;
    break;

  case( k_ge4jets_250toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	met>=250.0 ) result = true;
    break;
    
  case( k_ge4jets_250to325met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	met>=250.0 &&
	met<325.0       ) result = true;
    break;

  case( k_ge4jets_325toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	met>=325.0    ) result = true;
    break;

  case( k_ge4jets_250to350met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	met>=250.0 &&
	met<350.0       ) result = true;
    break;

  case( k_ge4jets_350to450met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	met>=350.0 &&
	met<450.0       ) result = true;
    break;

  case( k_ge4jets_450toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	met>=450.0    ) result = true;
    break;

  case( k_ge4jets_lt200mt2w ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w<200.0 &&
	met>=250.0      ) result = true;
    break;


  case( k_ge4jets_lt200mt2w_150to250met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w<200.0 &&
	met>=150.0 &&
	met<250.0     ) result = true;
    break;

  case( k_ge4jets_lt200mt2w_250to325met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w<200.0 &&
	met>=250.0 &&
	met<325.0     ) result = true;
    break;

  case( k_ge4jets_lt200mt2w_325toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w<200.0 &&
	met>=325.0    ) result = true;
    break;

  case( k_ge4jets_lt200mt2w_250to350met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w<200.0 &&
	met>=250.0 &&
	met<350.0     ) result = true;
    break;

  case( k_ge4jets_lt200mt2w_350to450met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w<200.0 &&
	met>=350.0 &&
	met<450.0     ) result = true;
    break;

  case( k_ge4jets_lt200mt2w_450toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w<200.0 &&
	met>=450.0    ) result = true;
    break;

  case( k_ge4jets_ge200mt2w ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=250.0      ) result = true;
    break;  

  case( k_ge4jets_ge200mt2w_150to250met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=150.0 &&
	met<250.0     ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_250to350met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=250.0 &&
	met<350.0     ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_350to450met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=350.0 &&
	met<450.0     ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_350toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=350.0    ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_450toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=450.0    ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_450to550met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=450.0 &&
	met<550.0     ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_550toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=550.0    ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_550to650met ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=550.0 &&
	met<650.0     ) result = true;
    break;

  case( k_ge4jets_ge200mt2w_650toInfmet ):
    if( babyAnalyzer.ngoodjets()>=4 && 
	mt2w>=200.0 &&
	met>=650.0    ) result = true;
    break;
    
  case( k_ge5jets ):
    if( babyAnalyzer.ngoodjets()>=5 &&
	met>=250.0 ) result = true;
    break;

  case( k_ge5jets_compM ):
    if( babyAnalyzer.ngoodjets()>=5 &&
	met>=250.0 &&
	babyAnalyzer.ak4pfjets_p4().at(0).Pt()>200.0 &&
	!babyAnalyzer.ak4pfjets_passMEDbtag().at(0)      ) result = true;
    break;

  case( k_ge5jets_compM_150to250met ):
    if( babyAnalyzer.ngoodjets()>=5 &&
	met>=150.0 &&
	met<250.0 &&
	babyAnalyzer.ak4pfjets_p4().at(0).Pt()>200.0 &&
	!babyAnalyzer.ak4pfjets_passMEDbtag().at(0)      ) result = true;
    break;

  case( k_ge5jets_compM_250to350met ):
    if( babyAnalyzer.ngoodjets()>=5 &&
	met>=250.0 &&
	met<350.0 &&
	babyAnalyzer.ak4pfjets_p4().at(0).Pt()>200.0 &&
	!babyAnalyzer.ak4pfjets_passMEDbtag().at(0)      ) result = true;
    break;

  case( k_ge5jets_compM_350to450met ):
    if( babyAnalyzer.ngoodjets()>=5 &&
	met>=350.0 &&
	met<450.0 &&
	babyAnalyzer.ak4pfjets_p4().at(0).Pt()>200.0 &&
	!babyAnalyzer.ak4pfjets_passMEDbtag().at(0)      ) result = true;
    break;

  case( k_ge5jets_compM_450toInfmet ):
    if( babyAnalyzer.ngoodjets()>=5 &&
	met>=450.0 &&
	babyAnalyzer.ak4pfjets_p4().at(0).Pt()>200.0 &&
	!babyAnalyzer.ak4pfjets_passMEDbtag().at(0)      ) result = true;
    break;

  case( k_ge1btags_ge50met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	met>=50.0      ) result = true;
    break;

  case( k_ge1btags_ge100met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	met>=100.0     ) result = true;
    break;

  case( k_ge1btags_ge150met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	met>=150.0     ) result = true;
    break;
    
  case( k_ge1btags_ge200met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	met>=200.0     ) result = true;
    break;

  case( k_ge1btags_ge250met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	met>=250.0     ) result = true;
    break;

  case( k_ge2btags_ge50met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	met>=50.0     ) result = true;
    break;

  case( k_ge2btags_ge100met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	met>=100.0     ) result = true;
    break;

  case( k_ge2btags_ge150met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	met>=150.0     ) result = true;
    break;
    
  case( k_ge2btags_ge200met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	met>=200.0     ) result = true;
    break;

  case( k_ge2btags_ge250met ):
    if( babyAnalyzer.ngoodjets()>=2 &&
	babyAnalyzer.ngoodbtags()>=2 &&
	met>=250.0     ) result = true;
    break;


  case( k_ge4jets_ge1btags_ge50met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	met>=50.0      ) result = true;
    break;

  case( k_ge4jets_ge1btags_ge250met ):
    if( babyAnalyzer.ngoodjets()>=4 &&
	babyAnalyzer.ngoodbtags()>=1 &&
	met>=250.0      ) result = true;
    break;
    

  default:
    std::cout << "Could not find category info from category enum provided!" << std::endl;
    break;

  }; // end switch

  return result;
  
}

//////////////////////////////////////////////////////////////////////

categoryInfo::vect_util_passBool categoryInfo::passCategoriesFromList( vect_util categoryList, bool onlyReturnTrue, bool add2ndLepToMet ){

  vect_util_passBool result;

  for(int iCat=0; iCat<(int)categoryList.size(); iCat++){

    pair_util_passBool temp_result;
    temp_result.first  = categoryList[iCat];
    temp_result.second = passCategory( temp_result.first.id, add2ndLepToMet ) ? true : false;
    if( onlyReturnTrue ){
      if( temp_result.second ) result.push_back( temp_result );
    }
    else result.push_back( temp_result );

  }

  return result;

}

//////////////////////////////////////////////////////////////////////

categoryInfo::vect_util categoryInfo::getCategoryList( analyzerInfo::ID analysis ){

  vect_util result;

  switch( analysis ){
    
  case( analyzerInfo::k_SR ):
  case( analyzerInfo::k_CR0b ):
  case( analyzerInfo::k_CR2l ):
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge2jets) );
    result.push_back( categoryUtil(k_ge2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ge2jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge2jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee2jets) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop_150to250met) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop_250to350met) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop_350toInfmet) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop_350to450met) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop_450toInfmet) );
    result.push_back( categoryUtil(k_ge3jets) );
    result.push_back( categoryUtil(k_ge3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee3jets) );
    result.push_back( categoryUtil(k_ee3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_150to250met) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_250to350met) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_350toInfmet) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_350to450met) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_450toInfmet) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_450to550met) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w_550toInfmet) );
    result.push_back( categoryUtil(k_ge4jets) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_150to250met) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_250to325met) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_325toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_250to350met) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_350to450met) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w_450toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_150to250met) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_250to350met) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_350to450met) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_350toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_450toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_450to550met) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_550toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_550to650met) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w_650toInfmet) );
    result.push_back( categoryUtil(k_ge5jets) );
    result.push_back( categoryUtil(k_ge5jets_compM) );
    result.push_back( categoryUtil(k_ge5jets_compM_150to250met) );
    result.push_back( categoryUtil(k_ge5jets_compM_250to350met) );
    result.push_back( categoryUtil(k_ge5jets_compM_350to450met) );
    result.push_back( categoryUtil(k_ge5jets_compM_450toInfmet) );
    break;

  case( analyzerInfo::k_CR1l_bulkWJets ):
    result.push_back( categoryUtil(k_incl) );
    break;
  
  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge1btags_ge50met) );
    result.push_back( categoryUtil(k_ge1btags_ge100met) );
    result.push_back( categoryUtil(k_ge1btags_ge150met) );
    result.push_back( categoryUtil(k_ge1btags_ge200met) );
    result.push_back( categoryUtil(k_ge1btags_ge250met) );
    result.push_back( categoryUtil(k_ge2btags_ge50met) );
    result.push_back( categoryUtil(k_ge2btags_ge100met) );
    result.push_back( categoryUtil(k_ge2btags_ge150met) );
    result.push_back( categoryUtil(k_ge2btags_ge200met) );
    result.push_back( categoryUtil(k_ge2btags_ge250met) );
    result.push_back( categoryUtil(k_ge4jets_250toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_ge1btags_ge50met) );
    result.push_back( categoryUtil(k_ge4jets_ge1btags_ge250met) );
    break;

  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge2jets) );
    result.push_back( categoryUtil(k_ee2jets) );
    result.push_back( categoryUtil(k_ee2jets_250to350met) );
    result.push_back( categoryUtil(k_ee2jets_350toInfmet) );
    result.push_back( categoryUtil(k_ge3jets) );
    result.push_back( categoryUtil(k_ee3jets) );
    result.push_back( categoryUtil(k_ee3jets_250to350met) );
    result.push_back( categoryUtil(k_ee3jets_350toInfmet) );
    result.push_back( categoryUtil(k_ge4jets) );
    result.push_back( categoryUtil(k_ge4jets_250to325met) );
    result.push_back( categoryUtil(k_ge4jets_325toInfmet) );
    result.push_back( categoryUtil(k_ge4jets_250to350met) );
    result.push_back( categoryUtil(k_ge4jets_350to450met) );
    result.push_back( categoryUtil(k_ge4jets_450toInfmet) );
    result.push_back( categoryUtil(k_ge5jets) );
    break;
  
  default:
    result.push_back( categoryUtil(k_incl) );
    result.push_back( categoryUtil(k_ge2jets) );
    result.push_back( categoryUtil(k_ge2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ge2jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge2jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee2jets) );
    result.push_back( categoryUtil(k_ee2jets_ge6p4modTop) );
    result.push_back( categoryUtil(k_ge3jets) );
    result.push_back( categoryUtil(k_ge3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ee3jets) );
    result.push_back( categoryUtil(k_ee3jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ee3jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ge4jets) );
    result.push_back( categoryUtil(k_ge4jets_lt200mt2w) );
    result.push_back( categoryUtil(k_ge4jets_ge200mt2w) );
    result.push_back( categoryUtil(k_ge5jets) );
    break;
    
  }; // end analysis switch


  return result;

}

bool categoryInfo::sortByCSV(std::pair<int, double>& p1, std::pair<int, double>& p2) {
  return (p1.second > p2.second);
}

//////////////////////////////////////////////////////////////////////
