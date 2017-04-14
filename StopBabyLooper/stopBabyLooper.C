#include "stopBabyLooper.h"

//////////////////////////////
//                          //
// Configuration Parameters //
//                          //
//////////////////////////////

bool analyzeFast_ = false;

bool applyjson = true;

bool add2ndLepToMet_ = true;
bool inclTaus_CR2l_  = false;

bool useBTagSFs_fromFiles_ = true;
bool useLepSFs_fromFiles_  = true;
        
bool apply_cr2lTrigger_sf_  = true; // only !=1 if pfmet!=pfmet_rl ie no weight for ==1lepton events in SR and CR0b
bool apply_bTag_sf_         = true; // event weight, product of all jet wgts
bool apply_lep_sf_          = true; // both lep1 and lep2 (if available) are multiplied together
bool apply_vetoLep_sf_      = true; // this is actually the lost lepton sf, only !=1 if there is >=2 genLeptons and ==1 recoLeptons in the event
bool apply_tau_sf_          = true;
bool apply_lepFS_sf_        = false;
bool apply_topPt_sf_        = false; // true=sf, false=uncertainty
bool apply_metRes_sf_       = true;
bool apply_metTTbar_sf_     = true;
bool apply_ttbarSysPt_sf_   = false;  // true=sf, false=uncertainty, only !=1.0 for madgraph tt2l, tW2l
bool apply_ISR_sf_          = true; // only !=1.0 for signal
bool apply_pu_sf_           = true;
bool apply_sample_sf_       = true; // only !=1.0 for some WJetsHT samps


//
// Main
//
int stopBabyLooper(){


  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList_SR(); 


  //
  // Examples for Quick Tests
  //
  //sampleList.clear();
  //sampleList.push_back( sampleInfo::k_single_lepton_met );
  //sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_ttWJets_13TeV_madgraphMLM ); 
  //sampleList.push_back( sampleInfo::k_T2tt );

	//
	// Set up all the analyzer objects we'll need
	//
	analyzer SR_MlbBinned( "SR_bulk" );
	analyzer SR_corridor( "SR_corridor" );
	analyzer CR2L_MlbBinned( "CR2L_bulk" );
	analyzer CR2L_corridor( "CR2L_corridor" );
	analyzer CR0b_MlbBinned( "CR0b_bulk" );
	analyzer CR0b_tightBTagHighMlb( "CR0b_highMlb_bulk" );
	analyzer CR0b_corridor( "CR0b_corridor" );

	std::vector<analyzer*> analyzer_list = {&SR_MlbBinned, &SR_corridor, &CR2L_MlbBinned, &CR2L_corridor, &CR0b_MlbBinned, &CR0b_tightBTagHighMlb, &CR0b_corridor};

	// Set the attributes for each analyzer
	CR2L_MlbBinned.SetAdd2ndLep( true );
	CR2L_corridor.SetAdd2ndLep( true );

	SR_corridor.SetIsCorridor( true );
	CR2L_corridor.SetIsCorridor( true );
	CR0b_corridor.SetIsCorridor( true );

	SR_MlbBinned.SetUseMetTTbarWeights( true );

	SR_MlbBinned.SetUseTightTagHighMlb( true );
	CR2L_MlbBinned.SetUseTightTagHighMlb( true );

	// Set selections and categories for the analyzers
	SR_MlbBinned.AddSelections(   selectionInfo::get_selection_SR() );
	SR_corridor.AddSelections(    selectionInfo::get_selection_SR_corridor() );
	CR2L_MlbBinned.AddSelections( selectionInfo::get_selection_CR2l() );
	CR2L_corridor.AddSelections(  selectionInfo::get_selection_CR2l_corridor() );
	CR0b_MlbBinned.AddSelections( selectionInfo::get_selection_CR0b() );
	CR0b_tightBTagHighMlb.AddSelections( selectionInfo::get_selection_CR0b_tightBTagHighMlb() );
	CR0b_corridor.AddSelections(  selectionInfo::get_selection_CR0b_corridor() );

	SR_MlbBinned.AddCategories(   categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	SR_corridor.AddCategories(    categoryInfo::passCategory_SR_corridor);
	CR2L_MlbBinned.AddCategories( categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	CR2L_corridor.AddCategories(  categoryInfo::passCategory_SR_corridor);
	CR0b_MlbBinned.AddCategories( categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	CR0b_tightBTagHighMlb.AddCategories(categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	CR0b_corridor.AddCategories(  categoryInfo::passCategory_SR_corridor);

	TH1D* h_template_MlbBinned = categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_mlb_v2();
	TH1D* h_template_corridor  = categoryInfo::getYieldHistoTemplate_SR_corridor();

	SR_MlbBinned.SetYieldTemplate(   h_template_MlbBinned );
	SR_corridor.SetYieldTemplate(    h_template_corridor );
	CR2L_MlbBinned.SetYieldTemplate( h_template_MlbBinned );
	CR2L_corridor.SetYieldTemplate(  h_template_corridor );
	CR0b_MlbBinned.SetYieldTemplate( h_template_MlbBinned );
	CR0b_tightBTagHighMlb.SetYieldTemplate(h_template_MlbBinned );
	CR0b_corridor.SetYieldTemplate(  h_template_corridor );


  //
  // Loop over samples
  //
  for( int iSample=0; iSample<(int)sampleList.size(); iSample++){

		sampleInfo::ID currentSample = sampleList.at(iSample);

		// Give each analyzer the gen classifications and systematics appropriate to the current sample
		for( analyzer* iter : analyzer_list ) {
			iter->ResetGenClassifications();
			iter->ResetSystematics();
			if( sampleInfo::sampleUtil(currentSample).isData ) {
				iter->AddGenClassification( genClassyInfo::Util(genClassyInfo::k_incl) );
				iter->AddSystematic( sysInfo::Util(sysInfo::k_nominal) );
			}
			else {
				for( int i=0; i<genClassyInfo::k_nGenClassy; i++ ) iter->AddGenClassification( genClassyInfo::Util(genClassyInfo::ID(i)) );
				for( int i=0; i<sysInfo::k_nSys; i++ ) iter->AddSystematic( sysInfo::Util(sysInfo::ID(i)) );
			}
		} // End loop over analyzers

    looper( sampleList[iSample], analyzer_list );
  }


  //
  // Done
  //
  return 0;

}

/////////////////////////////////////////////////////////////////////////


//
// Functions
//
int looper( sampleInfo::ID sampleID, std::vector<analyzer*> analyzers, int nEvents, bool readFast ) {


  //
  // Intro
  //
  cout << "====================================================" << endl;
  cout << endl;
  cout << "  WELCOME TO STOP BABY ANALYZER! " << endl;
  cout << endl;
  cout << "====================================================" << endl;
  cout << endl;


  //
  // Benchmark
  //
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
  

  //
  // Input SampleInfo
  //
  sampleInfo::sampleUtil sample( sampleID );

  bool sampleIsTTbar = false;
  if( sample.id == sampleInfo::k_ttbar_powheg_pythia8 ||
      sample.id == sampleInfo::k_ttbar_powheg_pythia8_ext4 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 ||
      sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 ||
      sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8 ||
      sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ){
    sampleIsTTbar = true;
  }
  
  //
  // Input chain
  //
  TChain *chain = new TChain("t");
  
  cout << "    Processing the following: " << endl;  
  for(int iFile=0; iFile<(int)sample.inputBabies.size(); iFile++){
    
    // input directory
    string input = sample.baby_i_o.first;
      
    // input file
    input += sample.inputBabies[iFile];
      
    chain->Add( input.c_str() );
    cout << "      " << input << endl; 
  }
  cout << endl;
  
  
  //
  // Output File
  //

  // output dir
  string f_output_name = "";
  f_output_name += sample.baby_i_o.second;

  // output name
  f_output_name += sample.label;
  f_output_name += ".root";

  // output file
  TFile *f_output = new TFile( f_output_name.c_str(), "recreate" );

  // print output location
  cout << "    Output Written to: " << endl;
  cout << "      " << f_output_name << endl;
  cout << endl;


  //
  // JSON File Tools
  //
  const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"; // 35.876fb final 2016 run
  if( sample.isData ) set_goodrun_file_json(json_file);
  

  //
  // Event Weight Utilities
  //
  cout << "    Loading eventWeight Utilities..." << endl << endl;
  wgtInfo.setUp( sample.id, useBTagSFs_fromFiles_, useLepSFs_fromFiles_, add2ndLepToMet_ );  
  wgtInfo.apply_cr2lTrigger_sf  = (apply_cr2lTrigger_sf_ && add2ndLepToMet_);
  wgtInfo.apply_bTag_sf         = apply_bTag_sf_;
  wgtInfo.apply_lep_sf          = apply_lep_sf_;
  wgtInfo.apply_vetoLep_sf      = apply_vetoLep_sf_;
  wgtInfo.apply_tau_sf          = apply_tau_sf_;
  wgtInfo.apply_lepFS_sf        = apply_lepFS_sf_;
  wgtInfo.apply_topPt_sf        = apply_topPt_sf_;
  wgtInfo.apply_metRes_sf       = apply_metRes_sf_;
  wgtInfo.apply_metTTbar_sf     = apply_metTTbar_sf_;
  wgtInfo.apply_ttbarSysPt_sf   = apply_ttbarSysPt_sf_;
  wgtInfo.apply_ISR_sf          = apply_ISR_sf_;
  wgtInfo.apply_pu_sf           = apply_pu_sf_;
  wgtInfo.apply_sample_sf       = apply_sample_sf_;


  //
  // Declare genClassification list
  //
  cout << "    Loading genClassyList: ";
  std::vector< genClassyInfo::Util > genClassyList;
  if( sample.isData ){
    genClassyList.push_back(genClassyInfo::Util(genClassyInfo::k_incl));
  }
  else{
    for(int iGenClassy=0; iGenClassy<genClassyInfo::k_nGenClassy; iGenClassy++){
      genClassyList.push_back( genClassyInfo::Util(genClassyInfo::ID(iGenClassy)) );
    }
  }
  const int nGenClassy=(int)genClassyList.size();
  cout << nGenClassy << " genClassifications" << endl << endl;

  
  //
  // Declare Systematics
  //
  cout << "    Loading systematicList: ";
  std::vector< sysInfo::Util > systematicList;
  if( sample.isData || analyzeFast_ ){
    systematicList.push_back(sysInfo::Util(sysInfo::k_nominal));
  }
  else{
    for(int iSys=0; iSys<sysInfo::k_nSys; iSys++){
      systematicList.push_back( sysInfo::Util(sysInfo::ID(iSys)) );
    }
  }  
  const int nSystematics = (int)systematicList.size();
  cout << nSystematics << " systematics" << endl << endl;


	// Count number of analyzers in the list
	const int nAnalyzers = analyzers.size();



  ////////////////////////
  //                    //
  // Declare Histograms //
  //                    //
  ////////////////////////
  //
  //
  //  For Using DownStream Scripts, please adhere to the conventions:
  //
  //
  //    histogram_name = "your_name_here"+"__"+regionList[i]+"__genClassy_"+genClassyObject.label+"__systematic_"+sysInfoObject.label;
  //
  //
  //  Where regionList is the list of "SR", "CR0b", "CR0b_tightBTagHighMlb" or "CR2l"
  //
  //    And systematicList[0] is the nominal selection
  //
  //    And if there is andditional selection involved in this histogram, please refer to it in "you name here"
  //

  cout << "    Preparing histograms" << endl << endl;
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();


	//
	// Yield histograms
	//
	for( analyzer* thisAnalyzer : analyzers ) {
		for( int iClassy=0; iClassy<nGenClassy; iClassy++ ) {
			for( int iSys=0; iSys<nSystematics; iSys++ ) {

				int histIndex = iClassy*nSystematics + iSys;

				// Gen and Systematic String
				TString reg_gen_sys_name = "__";
				reg_gen_sys_name += thisAnalyzer->GetLabel();
				reg_gen_sys_name += "__genClassy_";
				reg_gen_sys_name += genClassyList[iClassy].label;
				reg_gen_sys_name += "__systematic_";
				reg_gen_sys_name += systematicList[iSys].label;

				TH1D* h_template = thisAnalyzer->GetYieldTemplate();
				TH1D* h_tmp = 0;

				// TString yieldname = h_template->GetName();
				TString yieldname = "h_yields";
				yieldname += reg_gen_sys_name;
				h_tmp = (TH1D*)h_template->Clone( yieldname );
				h_tmp->SetDirectory(f_output);
				thisAnalyzer->SetYieldHistogram( histIndex, h_tmp );

				// Need to do signal yield histograms too

			} // End loop over systematics
		} // End loop over genClassys
	} // End loop over analyzers

  
  
  
  //////////////////////////
  //                      //
  // Non-yield Histograms //
  //                      //
  //////////////////////////

  int nMassPts = 1;
  if( sample.isSignalScan ) nMassPts = (int)sample.massPtList.size();

  const int nHistosVars = nAnalyzers*nGenClassy*nMassPts;

  // nJets
  TH1D *h_nJets[nHistosVars];
  
  // nBTags
  TH1D *h_nBTags[nHistosVars];
  
  // lep1 pT
  TH1D *h_lep1Pt_incl[nHistosVars];
  
  // lep2 pT
  TH1D *h_lep2Pt_incl[nHistosVars];
  
  // jet pT
  TH1D *h_jetPt_incl[nHistosVars];
  
  // jet1 pT
  TH1D *h_jet1Pt_incl[nHistosVars];
  
  // jet2 pT
  TH1D *h_jet2Pt_incl[nHistosVars];
  
  // csv jet1 pT
  TH1D *h_csvJet1Pt_incl[nHistosVars];
  
  // csv jet2 pT
  TH1D *h_csvJet2Pt_incl[nHistosVars];
  
  // met
  TH1D *h_met_incl[nHistosVars];
  TH1D *h_met_lt4j[nHistosVars];
  TH1D *h_met_ge4j[nHistosVars];

  // lep1lep2bbMetPt
  TH1D *h_lep1lep2bbMetPt_incl[nHistosVars];
  TH1D *h_lep1lep2bbMetPt_lt4j[nHistosVars];
  TH1D *h_lep1lep2bbMetPt_ge4j[nHistosVars];

  // mt
  TH1D *h_mt_incl[nHistosVars];
  
  // modTopness
  TH1D *h_modTopness_incl[nHistosVars];
  TH1D *h_modTopness_lt4j[nHistosVars];
  TH1D *h_modTopness_ge4j[nHistosVars];

  // mlb
  TH1D *h_mlb_incl[nHistosVars];
  TH1D *h_mlb_lt4j[nHistosVars];
  TH1D *h_mlb_ge4j[nHistosVars];

  // mlb
  TH1D *h_mlb_lt0modTopness[nHistosVars];
  TH1D *h_mlb_ge0modTopness[nHistosVars];
  TH1D *h_mlb_ge10modTopness[nHistosVars];
  
  // mlb, met sideband CR
  TH1D *h_mlb_150to250met_incl[nHistosVars];
  TH1D *h_mlb_150to250met_lt4j[nHistosVars];
  TH1D *h_mlb_150to250met_ge4j[nHistosVars];

  // ml2b
  TH1D *h_mlb_lep2_incl[nHistosVars];
  TH1D *h_mlb_lep2_ee2j[nHistosVars];
  TH1D *h_mlb_lep2_ee3j[nHistosVars];
  TH1D *h_mlb_lep2_lt4j[nHistosVars];
  TH1D *h_mlb_lep2_ge4j[nHistosVars];
  
  // ml2b
  TH1D *h_mlb_lep2_150to250met_incl[nHistosVars];
  TH1D *h_mlb_lep2_150to250met_lt4j[nHistosVars];
  TH1D *h_mlb_lep2_150to250met_ge4j[nHistosVars];

  // Gen ttbar system pT
  TH1D *h_gen_ttbarPt_incl[nHistosVars];
  TH1D *h_gen_ttbarPt_lt4j[nHistosVars];
  TH1D *h_gen_ttbarPt_ge4j[nHistosVars];

  // Gen 2nd lepton ID
  TH1D *h_gen_lep2_id_incl[nHistosVars];
  TH1D *h_gen_lep2_id_lt4j[nHistosVars];
  TH1D *h_gen_lep2_id_ge4j[nHistosVars];
  
  for(int iReg=0; iReg<nAnalyzers; iReg++){
    for(int iGen=0; iGen<nGenClassy; iGen++){
      for(int iMassPt=0; iMassPt<nMassPts; iMassPt++){

				// Histo Index
				int iHisto = iReg*nGenClassy*nMassPts + iGen*nMassPts + iMassPt;

				int mStop = 0;
				int mLSP  = 0;
				if(sample.isSignalScan){
					mStop = sample.massPtList[iMassPt].first;
					mLSP  = sample.massPtList[iMassPt].second;
				}

				TString hName = "";
	
				TString reg_gen_sys_name = "__";
				reg_gen_sys_name += analyzers.at(iReg)->GetLabel();
				reg_gen_sys_name += "__genClassy_";
				reg_gen_sys_name += genClassyList[iGen].label;
				reg_gen_sys_name += "__systematic_";
				reg_gen_sys_name += systematicList[0].label;
				if( sample.isSignalScan ){
					reg_gen_sys_name += "__mStop_";
					reg_gen_sys_name += mStop;
					reg_gen_sys_name += "__mLSP_";
					reg_gen_sys_name += mLSP;
				}

      
	//
	// Njets
	//
	hName = "h_nJets";
	hName += reg_gen_sys_name;
	h_nJets[iHisto] = new TH1D( hName, "Number of Selected Jets;nJets", 11, -0.5, 10.5);
	h_nJets[iHisto]->SetDirectory(f_output);

	//
	// nBTags
	//
	hName = "h_nBTags";
	hName += reg_gen_sys_name;
	h_nBTags[iHisto] = new TH1D( hName, "Number of b-Tagged Jets;nBTags", 5, -0.5, 4.5);
	h_nBTags[iHisto]->SetDirectory(f_output);


	//
	// lep1Pt
	//

	// Incl Selection
	hName = "h_lep1Pt__inclSelection";
	hName += reg_gen_sys_name;
	h_lep1Pt_incl[iHisto] = new TH1D( hName, "Lepton p_{T};p_{T} [GeV]", 20.0, 0.0, 200.0 );
	h_lep1Pt_incl[iHisto]->SetDirectory(f_output);
      
	

	//
	// lep2Pt
	//

	// Incl Selection
	hName = "h_lep2Pt__inclSelection";
	hName += reg_gen_sys_name;
	h_lep2Pt_incl[iHisto] = new TH1D( hName, "Trailing Lepton p_{T};p_{T} [GeV]", 20.0, 0.0, 200.0 );
	h_lep2Pt_incl[iHisto]->SetDirectory(f_output);
      
		//
	// jetPt
	//

	// Incl Selection
	hName = "h_jetPt__inclSelection";
	hName += reg_gen_sys_name;
	h_jetPt_incl[iHisto] = new TH1D( hName, "Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_jetPt_incl[iHisto]->SetDirectory(f_output);
	
	//
	// jet1Pt
	//

	// Incl Selection
	hName = "h_jet1Pt__inclSelection";
	hName += reg_gen_sys_name;
	h_jet1Pt_incl[iHisto] = new TH1D( hName, "Leading Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_jet1Pt_incl[iHisto]->SetDirectory(f_output);
	
	

	//
	// jet2Pt
	//

	// Incl Selection
	hName = "h_jet2Pt__inclSelection";
	hName += reg_gen_sys_name;
	h_jet2Pt_incl[iHisto] = new TH1D( hName, "2nd Leading Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_jet2Pt_incl[iHisto]->SetDirectory(f_output);
      
	
	//
	// csvJet1Pt
	//

	// Incl Selection
	hName = "h_csvJet1Pt__inclSelection";
	hName += reg_gen_sys_name;
	h_csvJet1Pt_incl[iHisto] = new TH1D( hName, "Leading CSV Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_csvJet1Pt_incl[iHisto]->SetDirectory(f_output);
      
	

	//
	// csvJet2Pt
	//

	// Incl Selection
	hName = "h_csvJet2Pt__inclSelection";
	hName += reg_gen_sys_name;
	h_csvJet2Pt_incl[iHisto] = new TH1D( hName, "2nd Leading CSV Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_csvJet2Pt_incl[iHisto]->SetDirectory(f_output);
      
	

	//
	// met
	//

	// Incl Selection
	hName = "h_met__inclSelection";
	hName += reg_gen_sys_name;
	h_met_incl[iHisto] = new TH1D( hName, "MET;MET [GeV]", 32, 0.0, 800.0 );
	h_met_incl[iHisto]->SetDirectory(f_output);
      
	// <4j Selection
	hName = "h_met__lt4jSelection";
	hName += reg_gen_sys_name;
	h_met_lt4j[iHisto] = new TH1D( hName, "MET;MET [GeV]", 32, 0.0, 800.0 );
	h_met_lt4j[iHisto]->SetDirectory(f_output);

	// >=4j Selection
	hName = "h_met__ge4jSelection";
	hName += reg_gen_sys_name;
	h_met_ge4j[iHisto] = new TH1D( hName, "MET;MET [GeV]", 32, 0.0, 800.0 );
	h_met_ge4j[iHisto]->SetDirectory(f_output);


	

	//
	// lep1lep2bbMetPt
	//

	// Incl Selection
	hName = "h_lep1lep2bbMetPt__inclSelection";
	hName += reg_gen_sys_name;
	h_lep1lep2bbMetPt_incl[iHisto] = new TH1D( hName, "lep1(lep2)bbMet system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_lep1lep2bbMetPt_incl[iHisto]->SetDirectory(f_output);
	
	// <4j Selection
	hName = "h_lep1lep2bbMetPt__lt4jSelection";
	hName += reg_gen_sys_name;
	h_lep1lep2bbMetPt_lt4j[iHisto] = new TH1D( hName, "lep1(lep2)bbMet system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_lep1lep2bbMetPt_lt4j[iHisto]->SetDirectory(f_output);

	// >=4j Selection
	hName = "h_lep1lep2bbMetPt__ge4jSelection";
	hName += reg_gen_sys_name;
	h_lep1lep2bbMetPt_ge4j[iHisto] = new TH1D( hName, "lep1(lep2)bbMet system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	h_lep1lep2bbMetPt_ge4j[iHisto]->SetDirectory(f_output);


	//
	// mt
	//

	// Incl Selection
	hName = "h_mt__inclSelection";
	hName += reg_gen_sys_name;
	h_mt_incl[iHisto] = new TH1D( hName, "M_{T};M_{T} [GeV]", 24, 0.0, 600.0 );
	h_mt_incl[iHisto]->SetDirectory(f_output);
      
	
	//
	// modTopness
	//

	// Incl Selection
	hName = "h_modTopness__inclSelection";
	hName += reg_gen_sys_name;
	h_modTopness_incl[iHisto] = new TH1D( hName, "Modified Topness;Modified Topness", 20, -20.0, 20.0 );
	h_modTopness_incl[iHisto]->SetDirectory(f_output);
      
	// <4j Selection
	hName = "h_modTopness__lt4jSelection";
	hName += reg_gen_sys_name;
	h_modTopness_lt4j[iHisto] = new TH1D( hName, "Modified Topness;Modified Topness", 20, -20.0, 20.0 );
	h_modTopness_lt4j[iHisto]->SetDirectory(f_output);

	// >=4j Selection
	hName = "h_modTopness__ge4jSelection";
	hName += reg_gen_sys_name;
	h_modTopness_ge4j[iHisto] = new TH1D( hName, "Modified Topness;Modified Topness", 20, -20.0, 20.0 );
	h_modTopness_ge4j[iHisto]->SetDirectory(f_output);

      
	//
	// mlb
	//

	// Incl Selection
	hName = "h_mlb__inclSelection";
	hName += reg_gen_sys_name;
	h_mlb_incl[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_incl[iHisto]->SetDirectory(f_output);
      
	// <4j Selection
	hName = "h_mlb__lt4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_lt4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lt4j[iHisto]->SetDirectory(f_output);

	// >=4j Selection
	hName = "h_mlb__ge4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_ge4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_ge4j[iHisto]->SetDirectory(f_output);

      

	//
	// mlb, inclusive nJets, modTopness bins
	//

	// <0 modTopness Selection
	hName = "h_mlb__lt0modTopnessSelection";
	hName += reg_gen_sys_name;
	h_mlb_lt0modTopness[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lt0modTopness[iHisto]->SetDirectory(f_output);

	// >=0 modTopness Selection
	hName = "h_mlb__ge0modTopnessSelection";
	hName += reg_gen_sys_name;
	h_mlb_ge0modTopness[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_ge0modTopness[iHisto]->SetDirectory(f_output);
      
	// >=10 modTopness Selection
	hName = "h_mlb__ge10modTopnessSelection";
	hName += reg_gen_sys_name;
	h_mlb_ge10modTopness[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_ge10modTopness[iHisto]->SetDirectory(f_output);


	//
	// mlb, met sideband CR
	//

	// Incl Selection
	hName = "h_mlb_150to250met__inclSelection";
	hName += reg_gen_sys_name;
	h_mlb_150to250met_incl[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_150to250met_incl[iHisto]->SetDirectory(f_output);
      
	// <4j Selection
	hName = "h_mlb_150to250met__lt4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_150to250met_lt4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_150to250met_lt4j[iHisto]->SetDirectory(f_output);

	// >=4j Selection
	hName = "h_mlb_150to250met__ge4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_150to250met_ge4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
	h_mlb_150to250met_ge4j[iHisto]->SetDirectory(f_output);


	//
	// mlb_lep2
	//

	// Incl Selection
	hName = "h_mlb_lep2__inclSelection";
	hName += reg_gen_sys_name;
	h_mlb_lep2_incl[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lep2_incl[iHisto]->SetDirectory(f_output);
      
	// <4j Selection
	hName = "h_mlb_lep2__lt4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_lep2_lt4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lep2_lt4j[iHisto]->SetDirectory(f_output);

	// >=4j Selection
	hName = "h_mlb_lep2__ge4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_lep2_ge4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lep2_ge4j[iHisto]->SetDirectory(f_output);



	//
	// mlb_lep2, met CR sideband
	//

	// Incl Selection
	hName = "h_mlb_lep2_150to250met__inclSelection";
	hName += reg_gen_sys_name;
	h_mlb_lep2_150to250met_incl[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lep2_150to250met_incl[iHisto]->SetDirectory(f_output);
      
	// <4j Selection
	hName = "h_mlb_lep2_150to250met__lt4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_lep2_150to250met_lt4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lep2_150to250met_lt4j[iHisto]->SetDirectory(f_output);

	// >=4j Selection
	hName = "h_mlb_lep2_150to250met__ge4jSelection";
	hName += reg_gen_sys_name;
	h_mlb_lep2_150to250met_ge4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
	h_mlb_lep2_150to250met_ge4j[iHisto]->SetDirectory(f_output);



	

	//
	// Gen ttbar pT
	//
	if( !sample.isData ){
    
	  // Incl Selection
	  hName = "h_gen_ttbarPt__inclSelection";
	  hName += reg_gen_sys_name;
	  h_gen_ttbarPt_incl[iHisto] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	  h_gen_ttbarPt_incl[iHisto]->SetDirectory(f_output);
	
	  // <4j Selection
	  hName = "h_gen_ttbarPt__lt4jSelection";
	  hName += reg_gen_sys_name;
	  h_gen_ttbarPt_lt4j[iHisto] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	  h_gen_ttbarPt_lt4j[iHisto]->SetDirectory(f_output);

	  // >=4j Selection
	  hName = "h_gen_ttbarPt__ge4jSelection";
	  hName += reg_gen_sys_name;
	  h_gen_ttbarPt_ge4j[iHisto] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	  h_gen_ttbarPt_ge4j[iHisto]->SetDirectory(f_output);



	  //
	  // Gen Lep2 ID
	  //
      
	  // Incl Selection
	  hName = "h_gen_lep2_id__inclSelection";
	  hName += reg_gen_sys_name;
	  h_gen_lep2_id_incl[iHisto] = new TH1D( hName, "Gen 2nd Lepton ID;ID", 7, 1.0, 8.0 );
	  h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(1, "ele");
	  h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(2, "mu");
	  h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(3, "lep tau, ele");
	  h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(4, "lep tau, mu");
	  h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
	  h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
	  h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(7, "\"other\" tau");
	  h_gen_lep2_id_incl[iHisto]->SetDirectory(f_output);
	
	  	  // <4j Selection
	  hName = "h_gen_lep2_id__lt4jSelection";
	  hName += reg_gen_sys_name;
	  h_gen_lep2_id_lt4j[iHisto] = new TH1D( hName, "Gen 2nd Lepton ID;ID", 7, 1.0, 8.0 );
	  h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(1, "ele");
	  h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(2, "mu");
	  h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(3, "lep tau, ele");
	  h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(4, "lep tau, mu");
	  h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
	  h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
	  h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(7, "\"other\" tau");
	  h_gen_lep2_id_lt4j[iHisto]->SetDirectory(f_output);

	  // >=4j Selection
	  hName = "h_gen_lep2_id__ge4jSelection";
	  hName += reg_gen_sys_name;
	  h_gen_lep2_id_ge4j[iHisto] = new TH1D( hName, "Gen 2nd Lepton ID;ID", 7, 1.0, 8.0 );
	  h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(1, "ele");
	  h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(2, "mu");
	  h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(3, "lep tau, ele");
	  h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(4, "lep tau, mu");
	  h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
	  h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
	  h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(7, "\"other\" tau");
	  h_gen_lep2_id_ge4j[iHisto]->SetDirectory(f_output);

	
	} // end if sample is ttbar
      

      } // end loop over mass pts (1 pt only if not signal scan)
    } // end loop over genClassifications for histogram arrays
  } // end loop over analyzers/regions for histogram arrays


	// Set up cutflow histograms
	TH1D* h_cutflow[nAnalyzers];
	for( int iAna=0; iAna<nAnalyzers; iAna++ ) {

		analyzer* thisAnalyzer = analyzers.at(iAna);
		std::string histName  = "h_cutflow_";
		std::string histTitle = "Cutflow histogram ";
		histName  += thisAnalyzer->GetLabel();
		histTitle += thisAnalyzer->GetLabel();

		h_cutflow[iAna] = selectionInfo::get_cutflowHistoTemplate( thisAnalyzer->GetSelections(), histName, histTitle );
	}

 
  //FILE* f_evtList;
  //TString f_evtList_name = "evtList_CR2l_";
  //f_evtList_name += sample.label;
  //f_evtList_name += ".txt";
  //f_evtList = fopen(f_evtList_name.Data(), "w");

  //////////////////////
  //                  //
  // Loop Over Events //
  //                  //
  //////////////////////
    
  // Event Counters
  cout << "    Loading files to loop over" << endl << endl;
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  
  // Grab list of files
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    
    
    //////////////////////
    //                  //
    // Get File Content //
    //                  //
    //////////////////////
    
    // Open File and Get Tree
    TFile *file = new TFile( currentFile->GetTitle(), "read" );
    TTree *tree = (TTree*)file->Get("t");
    if(readFast) TTreeCache::SetLearnEntries(10);
    if(readFast) tree->SetCacheSize(128*1024*1024);
    babyAnalyzer.Init(tree);
    
    // Get weight histogram from baby
    wgtInfo.getWeightHistogramFromBaby( file );
    
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {

      
      ///////////////////////
      //                   //
      // Get Event Content //
      //                   //
      ///////////////////////
   
      // Read Tree
      if( nEventsTotal >= nEventsChain ) continue;
      if(readFast) tree->LoadTree(event);
      babyAnalyzer.GetEntry(event);
      ++nEventsTotal;

      // Progress
      stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );

      
      /////////////////////
      //                 //
      // Check Selection //
      //                 //
      /////////////////////


      // Check JSON
      if( sample.isData && applyjson ){
	if( !goodrun(run(),ls()) ) continue;
      }
	
      // Check duplicate event
      if( sample.isData ){
	duplicate_removal::DorkyEventIdentifier id(run(), evt(), ls());
	if( is_duplicate(id) ) continue;
      }

      // Check WNJets genPt
      if( sample.id == sampleInfo::k_W1JetsToLNu_madgraph_pythia8 ||
					sample.id == sampleInfo::k_W2JetsToLNu_madgraph_pythia8 ||
					sample.id == sampleInfo::k_W3JetsToLNu_madgraph_pythia8 ||
					sample.id == sampleInfo::k_W4JetsToLNu_madgraph_pythia8    ){
				if( nupt()>200.0 ) continue;
      }

			// Calculate all the event weights
      wgtInfo.getEventWeights();


			/////////////////////////////////////////////////////////////
			//                                                         //
			// Loop over all analyzers, genClassy's, systematics, etc. //
			//                                                         //
			/////////////////////////////////////////////////////////////

			// Loop over all analyzers
			for( int iAna=0; iAna<nAnalyzers; iAna++ ) {
				analyzer* thisAnalyzer = analyzers.at(iAna);


				// Make an array of which genClassy's this event passes
				bool passedGenClassies[genClassyInfo::k_nGenClassy];
				for( genClassyInfo::Util thisGenClassy : thisAnalyzer->GetGenClassifications() ) {
					passedGenClassies[thisGenClassy.id] = thisGenClassy.eval_GenClassy();

					// Manually correct the ZZto2L2Nu sample
					if( sample.id==sampleInfo::k_ZZTo2L2Nu_powheg_pythia8 ) {
						if( thisGenClassy.id == genClassyInfo::k_ge2lep ||
								thisGenClassy.id == genClassyInfo::k_incl ) passedGenClassies[thisGenClassy.id] = true;
						else passedGenClassies[thisGenClassy.id] = false;
					}
				}

				// Check if this event passes selections with JES set to nominal
				//  (saves us having to evaluate this for every systematic)
				thisAnalyzer->SetJesType( 0 );
				bool pass_JESnominal = thisAnalyzer->PassSelections();

				// Fill cutflow histogram
				std::vector<bool> cutflow_results = selectionInfo::get_selectionResults( thisAnalyzer->GetSelections() );
				for( uint i=0; i<cutflow_results.size(); i++ ) {
					if( !cutflow_results.at(i) ) break;
					h_cutflow[iAna]->Fill( i+1 );
				}


				// Loop over all systematics in the analyzer
				for( sysInfo::Util thisSystematic : thisAnalyzer->GetSystematics() ) {

					// Check if this event passes selections, and also set the appropriate JES type for future use
					if( thisSystematic.id == sysInfo::k_JESUp ) {
						thisAnalyzer->SetJesType( 1 );
						if( !thisAnalyzer->PassSelections() ) continue;
					}
					else if( thisSystematic.id == sysInfo::k_JESDown ) {
						thisAnalyzer->SetJesType( -1 );
						if( !thisAnalyzer->PassSelections() ) continue;
					}
					else {
						thisAnalyzer->SetJesType( 0 );
						if( !pass_JESnominal ) continue;
					}

					// If we've passed selections, then get the event weight and the categories passed
					double weight = thisAnalyzer->GetEventWeight( thisSystematic.id );
					std::vector<int> categories_passed = thisAnalyzer->GetCategoriesPassed();

					// Loop over all the gen classifications that we passed
					for( genClassyInfo::Util thisGenClassy : thisAnalyzer->GetGenClassifications() ) {
						if( !passedGenClassies[thisGenClassy.id] ) continue;

						// Get the index for the histogram corresponding to this genClassy and systematic
						int histIndex = thisGenClassy.id*nSystematics + thisSystematic.id;

						// Fill yield histograms
						for( int category : categories_passed ) {
							thisAnalyzer->GetYieldHistogram( histIndex )->Fill( category, weight );
						}

						// Do any other histogram filling that needs doing


					} // End loop over genClassy's

				} // End loop over systematics

			} // End loop over analyzers


  

			/*



      

      /////////////////////////////
      //                         //
      // Compute Event Variables //
      //                         //
      /////////////////////////////
      
      
      // gen ttbar system pT
      double ttbarPt = -99.9;
      LorentzVector genTTbar_LV;
      int nFoundGenTop=0;
      if( sampleIsTTbar ){
	
				for(int iGen=0; iGen<(int)genqs_p4().size(); iGen++){
					if( abs(genqs_id().at(iGen))==6 &&
							genqs_isLastCopy().at(iGen)    ){
						genTTbar_LV += genqs_p4().at(iGen);
						nFoundGenTop++;
					} // end if last copy of top
				} // end loop over gen quarks

				if( nFoundGenTop == 2 ) ttbarPt = genTTbar_LV.Pt();

      } // end if sample is ttbar


      
      // Gen 2nd lep ID
      double matched_lep_dr = 0.1;

      int gen2ndLep__idx = -1;
      int gen2ndLep__id = -99;
      int gen2ndLep__tauDecay = -1;
      int fill_bin_genLep2ID = -1;
      if( !sample.isData && is2lep() ){
	
				// match leading lepton first
				int genLep_matchedTo_selLep__idx = -1;
				for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
					if( abs(genleps_id().at(iGen)) != abs(lep1_pdgid()) ) continue;
					if( !genleps_isLastCopy().at(iGen) ) continue;
					if( !genleps_fromHardProcessFinalState().at(iGen) &&
							!genleps_fromHardProcessDecayed().at(iGen)       ) continue;
					if( ROOT::Math::VectorUtil::DeltaR(genleps_p4().at(iGen), lep1_p4()) < matched_lep_dr ){
						genLep_matchedTo_selLep__idx = iGen;
						break;
					}
				}

				// If matched selected lepton, find lost gen lepton
				if( genLep_matchedTo_selLep__idx>0 ){

					for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
						if( iGen == genLep_matchedTo_selLep__idx ) continue;
						if( !genleps_isLastCopy().at(iGen) ) continue;
						if( !genleps_fromHardProcessFinalState().at(iGen) &&
								!genleps_fromHardProcessDecayed().at(iGen)       ) continue;
						gen2ndLep__idx = iGen;
						gen2ndLep__id = genleps_id().at(iGen);
						gen2ndLep__tauDecay = genleps_gentaudecay().at(iGen);
					}

					// If found second lep
					if( gen2ndLep__idx>=0 ){
	      
						if( abs(gen2ndLep__id)==11 ) fill_bin_genLep2ID = 1;  // "ele";
						if( abs(gen2ndLep__id)==13 ) fill_bin_genLep2ID = 2;  // "mu";
						if( abs(gen2ndLep__id)==15 ){
							if( gen2ndLep__tauDecay==1 ) fill_bin_genLep2ID = 3;  // "lep tau, ele";
							if( gen2ndLep__tauDecay==2 ) fill_bin_genLep2ID = 4;  // "lep tau, mu";
							if( gen2ndLep__tauDecay==3 ) fill_bin_genLep2ID = 5;  // "had tau, 1 prong";
							if( gen2ndLep__tauDecay==4 ) fill_bin_genLep2ID = 6;  // "had tau, 3 prong";
							if( gen2ndLep__tauDecay==5 ) fill_bin_genLep2ID = 7;  // "\"other\" tau";
						} // end if 2nd lep is tau


					} // end if found 2nd gen lep
				} // end if found first gen lep, matched to selected lepton
      } // end if 2lep event and not data

      
     

      // lep1 lep2 b b TLV
      LorentzVector lep1lep2bb_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bb_pt = -99.9;

      LorentzVector lep1lep2bbMet_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bbMet_pt = -99.9;

      lep1lep2bb_TLV += lep1_p4();
      if(nvetoleps()>1) lep1lep2bb_TLV += lep2_p4();
      
      int jet1_idx = -1;
      double max_csv = -99.9;
      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
				if( ak4pfjets_CSV().at(iJet) > max_csv ){
					jet1_idx = iJet;
					max_csv  = ak4pfjets_CSV().at(iJet);
				}
      }
      if(jet1_idx>=0) lep1lep2bb_TLV += ak4pfjets_p4().at(jet1_idx);
      
      int jet2_idx = -1;
      max_csv = -99.9;
      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
				if( iJet==jet1_idx ) continue;
				if( ak4pfjets_CSV().at(iJet) > max_csv ){
					jet2_idx = iJet;
					max_csv = ak4pfjets_CSV().at(iJet);
				}
      }
      if(jet2_idx>=0) lep1lep2bb_TLV += ak4pfjets_p4().at(jet2_idx);
      
      lep1lep2bb_pt = lep1lep2bb_TLV.Pt();
     
      
      // lep1 lep2 b b MET TLV
      lep1lep2bbMet_TLV = lep1lep2bb_TLV;
      LorentzVector met_TLV( pfmet()*cos(pfmet_phi()), pfmet()*sin(pfmet_phi()), 0.0, pfmet() );
      lep1lep2bbMet_TLV += met_TLV;
    
      lep1lep2bbMet_pt = lep1lep2bbMet_TLV.Pt();

      
      
      // mlb lep2
      LorentzVector lep2b_TLV(0.0,0.0,0.0,0.0);
      double minDr = 99.9;
      int minBJetIdx = -99;
      if(nvetoleps()>1){
				lep2b_TLV += lep2_p4();
				for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
					if(!ak4pfjets_passMEDbtag().at(iJet)) continue;
					if(ROOT::Math::VectorUtil::DeltaR(ak4pfjets_p4().at(iJet),lep2_p4())<minDr){
						minDr = ROOT::Math::VectorUtil::DeltaR(ak4pfjets_p4().at(iJet),lep2_p4());
						minBJetIdx = iJet;
					}
				} // end loop over jets
				if(minBJetIdx>=0) lep2b_TLV += ak4pfjets_p4().at(minBJetIdx);
      } // end if nvetoleps>1


      // nTightTags
      int nTightTags_nominal = babyAnalyzer.ntightbtags();
      int nTightTags_jesup   = babyAnalyzer.jup_ntightbtags();
      int nTightTags_jesdown = babyAnalyzer.jdown_ntightbtags();
      
      
      /////////////////////
      //                 //
      // Fill Histograms //
      //                 //
      /////////////////////

      int mStop = mass_stop();
      int mLSP  = mass_lsp();


			//
			// Non-yield Histograms
			//
	for(int iGen=0; iGen<nGenClassy; iGen++) {

	  if( !passGenClassy[iGen] ) continue;
	  
	  if( pass_evtSel[iReg] ) {

	    int nTightTags = nTightTags_nominal;
	    if( ( (analyzers.at(iReg)=="SR" || analyzers.at(iReg)=="CR2l") && ( (Mlb_closestb()>=175.0 && nTightTags>=1) || (Mlb_closestb()<175.0) ) ) ||
		( (analyzers.at(iReg)!="SR" && analyzers.at(iReg)!="CR2l") )    ){
	      
	      double wgt_histos = wgt_nominal;
	      wgt_histos *= metResSF;
	      if( (analyzers.at(iReg)=="SR" || analyzers.at(iReg)=="CR2l") && (Mlb_closestb()>=175.0 && nTightTags>=1) ){
		wgt_histos *= (wgtInfo.sf_bTag_tight/wgtInfo.sf_bTag); 
	      }

	      if( analyzers.at(iReg)=="SR" ) wgt_histos *= metTTbarSF;


	      for(int iMassPt=0; iMassPt<nMassPts; iMassPt++){

		if( sample.isSignalScan && mStop!=sample.massPtList[iMassPt].first && mLSP!=sample.massPtList[iMassPt].second ) continue;
		//if(!isnormal(wgt_nominal)) cout << "NaN/inf weight: nEntries=" << wgtInfo.nEvents << ", lepSF=" << wgtInfo.sf_lep << ", vetoLep="<< wgtInfo.sf_vetoLep << ", btagSF=" << wgtInfo.sf_bTag << endl;
		// Histo Index
		int iHisto = iReg*nGenClassy*nMassPts + iGen*nMassPts + iMassPt;

		// Vars 
		double nGoodJets = ngoodjets();

		double mt = mt_met_lep();
		if( add2ndLepToMet_ ) mt = mt_met_lep_rl();

		double modTopness = topnessMod();
		if( add2ndLepToMet_ ) modTopness = topnessMod();

		double mt2w = MT2W();
		if( add2ndLepToMet_ ) mt2w = MT2W_rl();
	    
		double met = pfmet();
		if( add2ndLepToMet_ ) met = pfmet_rl();

		double mlb = Mlb_closestb();
		if( analyzers.at(iReg)=="CR0b" || analyzers.at(iReg)=="CR0b_tightBTagHighMlb" ) mlb = ( lep1_p4() + ak4pfjets_leadbtag_p4() ).M();

		// Met Sideband CR area, met>=150

		if( met>=150 && met<250 ){
		  // mlb, met sideband CR
		  h_mlb_150to250met_incl[iHisto]->Fill( mlb, wgt_histos );
		  if( nGoodJets==2 ) h_mlb_150to250met_ee2j[iHisto]->Fill( mlb, wgt_histos );
		  if( nGoodJets==3 ) h_mlb_150to250met_ee3j[iHisto]->Fill( mlb, wgt_histos );
		  if( nGoodJets<4 )  h_mlb_150to250met_lt4j[iHisto]->Fill( mlb, wgt_histos );
		  if( nGoodJets>=4 ) h_mlb_150to250met_ge4j[iHisto]->Fill( mlb, wgt_histos );
	      
		  // mlb_lep2, met sideband CR
		  if(nvetoleps()>1 && minBJetIdx>=0){
		    h_mlb_lep2_150to250met_incl[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );
		    if( nGoodJets==2 ) h_mlb_lep2_150to250met_ee2j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );
		    if( nGoodJets==3 ) h_mlb_lep2_150to250met_ee3j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );
		    if( nGoodJets<4 )  h_mlb_lep2_150to250met_lt4j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );	    
		    if( nGoodJets>=4 ) h_mlb_lep2_150to250met_ge4j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );	    
		  }

		  // bJetPt, met sideband CR
		  h_bJetPt_150to250met_incl[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		  if( nGoodJets==2 ) h_bJetPt_150to250met_ee2j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		  if( nGoodJets==3 ) h_bJetPt_150to250met_ee3j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		  if( nGoodJets<4 )  h_bJetPt_150to250met_lt4j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		  if( nGoodJets>=4 ) h_bJetPt_150to250met_ge4j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
	      
		} // end if 150<met<250

		// Signal Region Area, met>=250
		if( met<250.0 ) continue;
	    
		// nJets
		h_nJets[iHisto]->Fill( nGoodJets, wgt_histos );
	    
		// nBTags
		h_nBTags[iHisto]->Fill( ngoodbtags(), wgt_histos );
	    
		// lep1 pT
		h_lep1Pt_incl[iHisto]->Fill( lep1_p4().Pt(), wgt_histos );
		if( nGoodJets==2 ) h_lep1Pt_ee2j[iHisto]->Fill( lep1_p4().Pt(), wgt_histos );
		if( nGoodJets==3 ) h_lep1Pt_ee3j[iHisto]->Fill( lep1_p4().Pt(), wgt_histos );
		if( nGoodJets>=4 ) h_lep1Pt_ge4j[iHisto]->Fill( lep1_p4().Pt(), wgt_histos );
	    
		// lep2 pT
		if( nvetoleps()>1 ){
		  h_lep2Pt_incl[iHisto]->Fill( lep2_p4().Pt(), wgt_histos );
		  if( nGoodJets==2 ) h_lep2Pt_ee2j[iHisto]->Fill( lep2_p4().Pt(), wgt_histos );
		  if( nGoodJets==3 ) h_lep2Pt_ee3j[iHisto]->Fill( lep2_p4().Pt(), wgt_histos );
		  if( nGoodJets>=4 ) h_lep2Pt_ge4j[iHisto]->Fill( lep2_p4().Pt(), wgt_histos );
		}
	    
		// jet pT
		for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
		  h_jetPt_incl[iHisto]->Fill( ak4pfjets_p4().at(iJet).Pt(), wgt_histos );
		  if( nGoodJets==2 ) h_jetPt_ee2j[iHisto]->Fill( ak4pfjets_p4().at(iJet).Pt(), wgt_histos );
		  if( nGoodJets==3 ) h_jetPt_ee3j[iHisto]->Fill( ak4pfjets_p4().at(iJet).Pt(), wgt_histos );
		  if( nGoodJets>=4 ) h_jetPt_ge4j[iHisto]->Fill( ak4pfjets_p4().at(iJet).Pt(), wgt_histos );
		}
	    
		// jet1 pT
		h_jet1Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(0).Pt(), wgt_histos );
		if( nGoodJets==2 ) h_jet1Pt_ee2j[iHisto]->Fill( ak4pfjets_p4().at(0).Pt(), wgt_histos );
		if( nGoodJets==3 ) h_jet1Pt_ee3j[iHisto]->Fill( ak4pfjets_p4().at(0).Pt(), wgt_histos );
		if( nGoodJets>=4 ) h_jet1Pt_ge4j[iHisto]->Fill( ak4pfjets_p4().at(0).Pt(), wgt_histos );
	    
		// jet2 pT
		h_jet2Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(1).Pt(), wgt_histos );
		if( nGoodJets==2 ) h_jet2Pt_ee2j[iHisto]->Fill( ak4pfjets_p4().at(1).Pt(), wgt_histos );
		if( nGoodJets==3 ) h_jet2Pt_ee3j[iHisto]->Fill( ak4pfjets_p4().at(1).Pt(), wgt_histos );
		if( nGoodJets>=4 ) h_jet2Pt_ge4j[iHisto]->Fill( ak4pfjets_p4().at(1).Pt(), wgt_histos );
	    
		// csv jet1 pT
		if(jet1_idx>=0){
		  h_csvJet1Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(jet1_idx).Pt(), wgt_histos );
		  if( nGoodJets==2 ) h_csvJet1Pt_ee2j[iHisto]->Fill( ak4pfjets_p4().at(jet1_idx).Pt(), wgt_histos );
		  if( nGoodJets==3 ) h_csvJet1Pt_ee3j[iHisto]->Fill( ak4pfjets_p4().at(jet1_idx).Pt(), wgt_histos );
		  if( nGoodJets>=4 ) h_csvJet1Pt_ge4j[iHisto]->Fill( ak4pfjets_p4().at(jet1_idx).Pt(), wgt_histos );
		}
	    
		// csv jet2 pT
		if(jet2_idx>=0){
		  h_csvJet2Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(jet2_idx).Pt(), wgt_histos );
		  if( nGoodJets==2 ) h_csvJet2Pt_ee2j[iHisto]->Fill( ak4pfjets_p4().at(jet2_idx).Pt(), wgt_histos );
		  if( nGoodJets==3 ) h_csvJet2Pt_ee3j[iHisto]->Fill( ak4pfjets_p4().at(jet2_idx).Pt(), wgt_histos );
		  if( nGoodJets>=4 ) h_csvJet2Pt_ge4j[iHisto]->Fill( ak4pfjets_p4().at(jet2_idx).Pt(), wgt_histos );
		}
	    
		// met
		h_met_incl[iHisto]->Fill( met, wgt_histos );
		if( nGoodJets==2 ) h_met_ee2j[iHisto]->Fill( met, wgt_histos );
		if( nGoodJets==3 ) h_met_ee3j[iHisto]->Fill( met, wgt_histos );
		if( nGoodJets<4 )  h_met_lt4j[iHisto]->Fill( met, wgt_histos );
		if( nGoodJets>=4 ) h_met_ge4j[iHisto]->Fill( met, wgt_histos );
	    
		// lep1lep2bbPt
		h_lep1lep2bbPt_incl[iHisto]->Fill( lep1lep2bb_pt, wgt_histos );
		if( nGoodJets==2 ) h_lep1lep2bbPt_ee2j[iHisto]->Fill( lep1lep2bb_pt, wgt_histos );
		if( nGoodJets==3 ) h_lep1lep2bbPt_ee3j[iHisto]->Fill( lep1lep2bb_pt, wgt_histos );
		if( nGoodJets>=4 ) h_lep1lep2bbPt_ge4j[iHisto]->Fill( lep1lep2bb_pt, wgt_histos );
	    
		// lep1lep2bbMetPt
		h_lep1lep2bbMetPt_incl[iHisto]->Fill( lep1lep2bbMet_pt, wgt_histos );
		if( nGoodJets==2 ) h_lep1lep2bbMetPt_ee2j[iHisto]->Fill( lep1lep2bbMet_pt, wgt_histos );
		if( nGoodJets==3 ) h_lep1lep2bbMetPt_ee3j[iHisto]->Fill( lep1lep2bbMet_pt, wgt_histos );
		if( nGoodJets>=4 ) h_lep1lep2bbMetPt_ge4j[iHisto]->Fill( lep1lep2bbMet_pt, wgt_histos );
	    
		// mt
		h_mt_incl[iHisto]->Fill( mt, wgt_histos );
		if( nGoodJets==2 ) h_mt_ee2j[iHisto]->Fill( mt, wgt_histos );
		if( nGoodJets==3 ) h_mt_ee3j[iHisto]->Fill( mt, wgt_histos );
		if( nGoodJets>=4 ) h_mt_ge4j[iHisto]->Fill( mt, wgt_histos );
	    
		// modTopness
		h_modTopness_incl[iHisto]->Fill( modTopness, wgt_histos );
		if( nGoodJets==2 ) h_modTopness_ee2j[iHisto]->Fill( modTopness, wgt_histos );
		if( nGoodJets==3 ) h_modTopness_ee3j[iHisto]->Fill( modTopness, wgt_histos );
		if( nGoodJets>=4 ) h_modTopness_ge4j[iHisto]->Fill( modTopness, wgt_histos );
	    
		// mt2w
		h_mt2w_incl[iHisto]->Fill( mt2w, wgt_histos );
		if( nGoodJets==2 ) h_mt2w_ee2j[iHisto]->Fill( mt2w, wgt_histos );
		if( nGoodJets==3 ) h_mt2w_ee3j[iHisto]->Fill( mt2w, wgt_histos );
		if( nGoodJets>=4 ) h_mt2w_ge4j[iHisto]->Fill( mt2w, wgt_histos );
	    
		// mlb
		h_mlb_incl[iHisto]->Fill( mlb, wgt_histos );
		if( nGoodJets==2 ) h_mlb_ee2j[iHisto]->Fill( mlb, wgt_histos );
		if( nGoodJets==3 ) h_mlb_ee3j[iHisto]->Fill( mlb, wgt_histos );
		if( nGoodJets<4 )  h_mlb_lt4j[iHisto]->Fill( mlb, wgt_histos );
		if( nGoodJets>=4 ) h_mlb_ge4j[iHisto]->Fill( mlb, wgt_histos );

		// mlb, modTopness bins
		if(modTopness<0.0)   h_mlb_lt0modTopness[iHisto]->Fill( mlb, wgt_histos );
		if(modTopness>=0.0)  h_mlb_ge0modTopness[iHisto]->Fill( mlb, wgt_histos );
		if(modTopness>=10.0) h_mlb_ge10modTopness[iHisto]->Fill( mlb, wgt_histos );
	    
		// mlb_lep2
		if(nvetoleps()>1 && minBJetIdx>=0){
		  h_mlb_lep2_incl[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );
		  if( nGoodJets==2 ) h_mlb_lep2_ee2j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );
		  if( nGoodJets==3 ) h_mlb_lep2_ee3j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );
		  if( nGoodJets<4 )  h_mlb_lep2_lt4j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );	    
		  if( nGoodJets>=4 ) h_mlb_lep2_ge4j[iHisto]->Fill( lep2b_TLV.M(), wgt_histos );	    
		}

		// bJetPt
		h_bJetPt_incl[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		if( nGoodJets==2 ) h_bJetPt_ee2j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		if( nGoodJets==3 ) h_bJetPt_ee3j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		if( nGoodJets<4 )  h_bJetPt_lt4j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		if( nGoodJets>=4 ) h_bJetPt_ge4j[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );

		// bJetPt, modTopness bins
		if(modTopness<0.0)   h_bJetPt_lt0modTopness[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		if(modTopness>=0.0)  h_bJetPt_ge0modTopness[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
		if(modTopness>=10.0) h_bJetPt_ge10modTopness[iHisto]->Fill( ak4pfjets_leadbtag_p4().Pt(), wgt_histos );
	    	    
		// Gen TTBar System
		if( sampleIsTTbar ){
		  h_gen_ttbarPt_incl[iHisto]->Fill( ttbarPt, wgt_histos );
		  if( nGoodJets==2 ) h_gen_ttbarPt_ee2j[iHisto]->Fill( ttbarPt, wgt_histos );
		  if( nGoodJets==3 ) h_gen_ttbarPt_ee3j[iHisto]->Fill( ttbarPt, wgt_histos );
		  if( nGoodJets<4 )  h_gen_ttbarPt_lt4j[iHisto]->Fill( ttbarPt, wgt_histos );
		  if( nGoodJets>=4 ) h_gen_ttbarPt_ge4j[iHisto]->Fill( ttbarPt, wgt_histos );
		}

		// Gen 2nd Lep ID
		if( !sample.isData && is2lep() && gen2ndLep__idx>=0 ){
		  h_gen_lep2_id_incl[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  if( ngoodjets()==2 ) h_gen_lep2_id_ee2j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  if( ngoodjets()==3 ) h_gen_lep2_id_ee3j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  if( ngoodjets()<4 )  h_gen_lep2_id_lt4j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  if( ngoodjets()>=4 ) h_gen_lep2_id_ge4j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );

		  //h_gen_lep2_id_incl[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  //if( ngoodjets()==2 && modTopness>6.4) h_gen_lep2_id_ee2j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  //if( ngoodjets()==3 && mt2w>=200.0) h_gen_lep2_id_ee3j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  //if( ngoodjets()>=4 && mt2w<200.0 )  h_gen_lep2_id_lt4j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		  //if( ngoodjets()>=4 && mt2w>=200.0) h_gen_lep2_id_ge4j[iHisto]->Fill( fill_bin_genLep2ID, wgt_histos );
		}
	    

	      } // end loop over mass points (1 if not signal scan)

	    } // end if pass additional tight tagging requirement for high mlb

	  } // end if pass event selection for nominal sys


	} // end loop over genClassifications

     
			*/
    
		} // end loop over events in tree
      
      
    //
    // Clean Up
    //
    delete tree;
    file->Close();
    delete file;
    
  } // end loop over file list
  
    
  //
  // Output Sanitation
  //
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
    
    
  //
  // Print Selection Cutflow
  //
  cout << "====================================================" << endl;
  cout << endl;
  for(int iReg=0; iReg<nAnalyzers; iReg++){
    cout << "    " << analyzers.at(iReg)->GetLabel() << " Cutflow: " << endl;
    for(int iCut=1; iCut<=(int)h_cutflow[iReg]->GetNbinsX(); iCut++){
      cout << "      nEvents pass " << h_cutflow[iReg]->GetXaxis()->GetBinLabel(iCut) << " = " << h_cutflow[iReg]->GetBinContent(iCut) << endl;
    }
    cout << endl;
    cout << endl;
  }
  cout << "====================================================" << endl;

  
  //
  // Clean stopCORE objects
  //
  wgtInfo.cleanUp(); 


  //
  // Close Output File
  //
  f_output->Write();
  f_output->Close();

    
  //
  // Clean input chain
  // 
  chain->~TChain();
  if( sample.isData ) duplicate_removal::clear_list();
       
  //
  // Benchmark Reporting
  //
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  cout << "====================================================" << endl;
    
  //fclose(f_evtList);

  //
  // Return!
  //
  return 0;

} // End of function "looper"


/////////////////////////////////////////////////////////////////////////

void fillHistos( TH1D *histo, vector<int> passCats, double wgt ){   ////////// can replace these with simple one-line range-based for loops

  for(int iCat=0; iCat<(int)passCats.size(); iCat++){
    histo->Fill( passCats[iCat], wgt );
  }

}
 
/////////////////////////////////////////////////////////////////////////

void fillHistosScan( TH3D *histo, vector<int> passCats, int mStop, int mLSP, double wgt ){

  for(int iCat=0; iCat<(int)passCats.size(); iCat++){
    histo->Fill( mStop, mLSP, passCats[iCat], wgt );
  }

}
 
/////////////////////////////////////////////////////////////////////////

