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
int stopBabyLooper() {

	// Use sumw2 for all histograms
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	TH3::SetDefaultSumw2();


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
	analyzer CR2l_MlbBinned( "CR2l_bulk" );
	analyzer CR2l_corridor( "CR2l_corridor" );
	analyzer CR0b_MlbBinned( "CR0b_bulk" );
	analyzer CR0b_tightBTagHighMlb( "CR0b_highMlb_bulk" );
	analyzer CR0b_corridor( "CR0b_corridor" );

	std::vector<analyzer*> analyzer_list = {&SR_MlbBinned, &SR_corridor, &CR2l_MlbBinned, &CR2l_corridor, &CR0b_MlbBinned, &CR0b_tightBTagHighMlb, &CR0b_corridor};

	// Set the attributes for each analyzer
	CR2l_MlbBinned.SetAdd2ndLep( true );
	CR2l_corridor.SetAdd2ndLep( true );

	SR_corridor.SetIsCorridor( true );
	CR2l_corridor.SetIsCorridor( true );
	CR0b_corridor.SetIsCorridor( true );

	SR_MlbBinned.SetUseMetTTbarWeights( true );

	SR_MlbBinned.SetUseTightTagHighMlb( true );
	CR2l_MlbBinned.SetUseTightTagHighMlb( true );

	// Set selections and categories for the analyzers
	SR_MlbBinned.AddSelections(   selectionInfo::get_selection_SR() );
	SR_corridor.AddSelections(    selectionInfo::get_selection_SR_corridor() );
	CR2l_MlbBinned.AddSelections( selectionInfo::get_selection_CR2l() );
	CR2l_corridor.AddSelections(  selectionInfo::get_selection_CR2l_corridor() );
	CR0b_MlbBinned.AddSelections( selectionInfo::get_selection_CR0b() );
	CR0b_tightBTagHighMlb.AddSelections( selectionInfo::get_selection_CR0b_tightBTagHighMlb() );
	CR0b_corridor.AddSelections(  selectionInfo::get_selection_CR0b_corridor() );

	SR_MlbBinned.AddCategories(   categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	SR_corridor.AddCategories(    categoryInfo::passCategory_SR_corridor);
	CR2l_MlbBinned.AddCategories( categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	CR2l_corridor.AddCategories(  categoryInfo::passCategory_SR_corridor);
	CR0b_MlbBinned.AddCategories( categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	CR0b_tightBTagHighMlb.AddCategories(categoryInfo::passCategory_SR_dev_ext30fb_mlb_v2);
	CR0b_corridor.AddCategories(  categoryInfo::passCategory_SR_corridor);

	TH1D* h_template_MlbBinned = categoryInfo::getYieldHistoTemplate_SR_dev_ext30fb_mlb_v2();
	TH1D* h_template_corridor  = categoryInfo::getYieldHistoTemplate_SR_corridor();

	TH3D* h_template_MlbBinned_signal = categoryInfo::getYieldHistoTemplate_signal_SR_dev_ext30fb_mlb_v2();
	TH3D* h_template_corridor_signal  = categoryInfo::getYieldHistoTemplate_signal_SR_corridor();

	SR_MlbBinned.SetYieldTemplate(   h_template_MlbBinned );
	SR_corridor.SetYieldTemplate(    h_template_corridor );
	CR2l_MlbBinned.SetYieldTemplate( h_template_MlbBinned );
	CR2l_corridor.SetYieldTemplate(  h_template_corridor );
	CR0b_MlbBinned.SetYieldTemplate( h_template_MlbBinned );
	CR0b_tightBTagHighMlb.SetYieldTemplate(h_template_MlbBinned );
	CR0b_corridor.SetYieldTemplate(  h_template_corridor );

	SR_MlbBinned.SetYieldTemplateSignal(   h_template_MlbBinned_signal );
	SR_corridor.SetYieldTemplateSignal(    h_template_corridor_signal );
	CR2l_MlbBinned.SetYieldTemplateSignal( h_template_MlbBinned_signal );
	CR2l_corridor.SetYieldTemplateSignal(  h_template_corridor_signal );
	CR0b_MlbBinned.SetYieldTemplateSignal( h_template_MlbBinned_signal );
	CR0b_tightBTagHighMlb.SetYieldTemplateSignal(h_template_MlbBinned_signal );
	CR0b_corridor.SetYieldTemplateSignal(  h_template_corridor_signal );


  //
  // Loop over samples
  //
  for( int iSample=0; iSample<(int)sampleList.size(); iSample++) {

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
      sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ) {
    sampleIsTTbar = true;
  }
  
  //
  // Input chain
  //
  TChain *chain = new TChain("t");
  
  cout << "    Processing the following: " << endl;  
  for(int iFile=0; iFile<(int)sample.inputBabies.size(); iFile++) {
    
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
  if( sample.isData ) {
    genClassyList.push_back(genClassyInfo::Util(genClassyInfo::k_incl));
  }
  else{
    for(int iGenClassy=0; iGenClassy<genClassyInfo::k_nGenClassy; iGenClassy++) {
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
  if( sample.isData || analyzeFast_ ) {
    systematicList.push_back(sysInfo::Util(sysInfo::k_nominal));
  }
  else{
    for(int iSys=0; iSys<sysInfo::k_nSys; iSys++) {
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


	//
	// Declare yield histograms
	//
  f_output->cd(); // All yield histos will belong to the output file
	for( analyzer* thisAnalyzer : analyzers ) {

		TH1D* h_template = thisAnalyzer->GetYieldTemplate();
		TH3D* h_template_signal = thisAnalyzer->GetYieldTemplateSignal();

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

				TH1* h_tmp = 0;

				TString yieldname = "h_yields";
				yieldname += reg_gen_sys_name;
				if( sample.isSignalScan ) h_tmp = (TH3D*)h_template_signal->Clone( yieldname );
				else                      h_tmp = (TH1D*)h_template->Clone( yieldname );
				thisAnalyzer->SetYieldHistogram( histIndex, h_tmp );

			} // End loop over systematics
		} // End loop over genClassys
	} // End loop over analyzers

  
  
  

  //
  // Declare non-yield histograms
  //

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
  
  // DeepCSV jet1 pT
  TH1D *h_deepcsvJet1Pt_incl[nHistosVars];
  
  // DeepCSV jet2 pT
  TH1D *h_deepcsvJet2Pt_incl[nHistosVars];
  
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

  f_output->cd(); // All non-yield histos will belong to the output file
  
  for(int iReg=0; iReg<nAnalyzers; iReg++) {
    for(int iGen=0; iGen<nGenClassy; iGen++) {
      for(int iMassPt=0; iMassPt<nMassPts; iMassPt++) {

				// Histo Index
				int iHisto = iReg*nGenClassy*nMassPts + iGen*nMassPts + iMassPt;

				int mStop = 0;
				int mLSP  = 0;
				if(sample.isSignalScan) {
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
				if( sample.isSignalScan ) {
					reg_gen_sys_name += "__mStop_";
					reg_gen_sys_name += mStop;
					reg_gen_sys_name += "__mLSP_";
					reg_gen_sys_name += mLSP;
				}

      
				//
				// Njets
				//
				hName = "h_nJets" + reg_gen_sys_name;
				h_nJets[iHisto] = new TH1D( hName, "Number of Selected Jets;nJets", 11, -0.5, 10.5);

				//
				// nBTags
				//
				hName = "h_nBTags" + reg_gen_sys_name;
				h_nBTags[iHisto] = new TH1D( hName, "Number of b-Tagged Jets;nBTags", 5, -0.5, 4.5);


				//
				// lep1Pt
				//

				// Incl Selection
				hName = "h_lep1Pt__inclSelection" + reg_gen_sys_name;
				h_lep1Pt_incl[iHisto] = new TH1D( hName, "Lepton p_{T};p_{T} [GeV]", 20.0, 0.0, 200.0 );
      
	

				//
				// lep2Pt
				//

				// Incl Selection
				hName = "h_lep2Pt__inclSelection" + reg_gen_sys_name;
				h_lep2Pt_incl[iHisto] = new TH1D( hName, "Trailing Lepton p_{T};p_{T} [GeV]", 20.0, 0.0, 200.0 );
      
				//
				// jetPt
				//

				// Incl Selection
				hName = "h_jetPt__inclSelection" + reg_gen_sys_name;
				h_jetPt_incl[iHisto] = new TH1D( hName, "Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	
				//
				// jet1Pt
				//

				// Incl Selection
				hName = "h_jet1Pt__inclSelection" + reg_gen_sys_name;
				h_jet1Pt_incl[iHisto] = new TH1D( hName, "Leading Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	
	

				//
				// jet2Pt
				//

				// Incl Selection
				hName = "h_jet2Pt__inclSelection" + reg_gen_sys_name;
				h_jet2Pt_incl[iHisto] = new TH1D( hName, "2nd Leading Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      
	
				//
				// DeepCSVJet1Pt
				//

				// Incl Selection
				hName = "h_deepcsvJet1Pt__inclSelection" + reg_gen_sys_name;
				h_deepcsvJet1Pt_incl[iHisto] = new TH1D( hName, "Leading DeepCSV Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      
	

				//
				// DeepCSVJet2Pt
				//

				// Incl Selection
				hName = "h_deepcsvJet2Pt__inclSelection" + reg_gen_sys_name;
				h_deepcsvJet2Pt_incl[iHisto] = new TH1D( hName, "2nd Leading DeepCSV Jet p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
      
	

				//
				// met
				//

				// Incl Selection
				hName = "h_met__inclSelection" + reg_gen_sys_name;
				h_met_incl[iHisto] = new TH1D( hName, "MET;MET [GeV]", 32, 0.0, 800.0 );
      
				// <4j Selection
				hName = "h_met__lt4jSelection" + reg_gen_sys_name;
				h_met_lt4j[iHisto] = new TH1D( hName, "MET;MET [GeV]", 32, 0.0, 800.0 );

				// >=4j Selection
				hName = "h_met__ge4jSelection" + reg_gen_sys_name;
				h_met_ge4j[iHisto] = new TH1D( hName, "MET;MET [GeV]", 32, 0.0, 800.0 );


	

				//
				// lep1lep2bbMetPt
				//

				// Incl Selection
				hName = "h_lep1lep2bbMetPt__inclSelection" + reg_gen_sys_name;
				h_lep1lep2bbMetPt_incl[iHisto] = new TH1D( hName, "lep1(lep2)bbMet system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	
				// <4j Selection
				hName = "h_lep1lep2bbMetPt__lt4jSelection" + reg_gen_sys_name;
				h_lep1lep2bbMetPt_lt4j[iHisto] = new TH1D( hName, "lep1(lep2)bbMet system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );

				// >=4j Selection
				hName = "h_lep1lep2bbMetPt__ge4jSelection" + reg_gen_sys_name;
				h_lep1lep2bbMetPt_ge4j[iHisto] = new TH1D( hName, "lep1(lep2)bbMet system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );


				//
				// mt
				//

				// Incl Selection
				hName = "h_mt__inclSelection" + reg_gen_sys_name;
				h_mt_incl[iHisto] = new TH1D( hName, "M_{T};M_{T} [GeV]", 24, 0.0, 600.0 );
      
	
				//
				// modTopness
				//

				// Incl Selection
				hName = "h_modTopness__inclSelection" + reg_gen_sys_name;
				h_modTopness_incl[iHisto] = new TH1D( hName, "Modified Topness;Modified Topness", 20, -20.0, 20.0 );
      
				// <4j Selection
				hName = "h_modTopness__lt4jSelection" + reg_gen_sys_name;
				h_modTopness_lt4j[iHisto] = new TH1D( hName, "Modified Topness;Modified Topness", 20, -20.0, 20.0 );

				// >=4j Selection
				hName = "h_modTopness__ge4jSelection" + reg_gen_sys_name;
				h_modTopness_ge4j[iHisto] = new TH1D( hName, "Modified Topness;Modified Topness", 20, -20.0, 20.0 );

      
				//
				// mlb
				//

				// Incl Selection
				hName = "h_mlb__inclSelection" + reg_gen_sys_name;
				h_mlb_incl[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
      
				// <4j Selection
				hName = "h_mlb__lt4jSelection" + reg_gen_sys_name;
				h_mlb_lt4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );

				// >=4j Selection
				hName = "h_mlb__ge4jSelection" + reg_gen_sys_name;
				h_mlb_ge4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );

      

				//
				// mlb, inclusive nJets, modTopness bins
				//

				// <0 modTopness Selection
				hName = "h_mlb__lt0modTopnessSelection" + reg_gen_sys_name;
				h_mlb_lt0modTopness[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );

				// >=0 modTopness Selection
				hName = "h_mlb__ge0modTopnessSelection" + reg_gen_sys_name;
				h_mlb_ge0modTopness[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
      
				// >=10 modTopness Selection
				hName = "h_mlb__ge10modTopnessSelection" + reg_gen_sys_name;
				h_mlb_ge10modTopness[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );


				//
				// mlb, met sideband CR
				//

				// Incl Selection
				hName = "h_mlb_150to250met__inclSelection" + reg_gen_sys_name;
				h_mlb_150to250met_incl[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );
      
				// <4j Selection
				hName = "h_mlb_150to250met__lt4jSelection" + reg_gen_sys_name;
				h_mlb_150to250met_lt4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );

				// >=4j Selection
				hName = "h_mlb_150to250met__ge4jSelection" + reg_gen_sys_name;
				h_mlb_150to250met_ge4j[iHisto] = new TH1D( hName, "M_{lb};M_{lb} [GeV]", 24, 0.0, 600.0 );


				//
				// mlb_lep2
				//

				// Incl Selection
				hName = "h_mlb_lep2__inclSelection" + reg_gen_sys_name;
				h_mlb_lep2_incl[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
      
				// <4j Selection
				hName = "h_mlb_lep2__lt4jSelection" + reg_gen_sys_name;
				h_mlb_lep2_lt4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );

				// >=4j Selection
				hName = "h_mlb_lep2__ge4jSelection" + reg_gen_sys_name;
				h_mlb_lep2_ge4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );



				//
				// mlb_lep2, met CR sideband
				//

				// Incl Selection
				hName = "h_mlb_lep2_150to250met__inclSelection" + reg_gen_sys_name;
				h_mlb_lep2_150to250met_incl[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );
      
				// <4j Selection
				hName = "h_mlb_lep2_150to250met__lt4jSelection" + reg_gen_sys_name;
				h_mlb_lep2_150to250met_lt4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );

				// >=4j Selection
				hName = "h_mlb_lep2_150to250met__ge4jSelection" + reg_gen_sys_name;
				h_mlb_lep2_150to250met_ge4j[iHisto] = new TH1D( hName, "M_{l2b};M_{l2b} [GeV]", 24, 0.0, 600.0 );



	

				//
				// Gen ttbar pT
				//
				if( !sample.isData ) {
    
					// Incl Selection
					hName = "h_gen_ttbarPt__inclSelection" + reg_gen_sys_name;
					h_gen_ttbarPt_incl[iHisto] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );
	
					// <4j Selection
					hName = "h_gen_ttbarPt__lt4jSelection" + reg_gen_sys_name;
					h_gen_ttbarPt_lt4j[iHisto] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );

					// >=4j Selection
					hName = "h_gen_ttbarPt__ge4jSelection" + reg_gen_sys_name;
					h_gen_ttbarPt_ge4j[iHisto] = new TH1D( hName, "Gen t#bar{t} system p_{T};p_{T} [GeV]", 24, 0.0, 600.0 );



					//
					// Gen Lep2 ID
					//
      
					// Incl Selection
					hName = "h_gen_lep2_id__inclSelection" + reg_gen_sys_name;
					h_gen_lep2_id_incl[iHisto] = new TH1D( hName, "Gen 2nd Lepton ID;ID", 7, 1.0, 8.0 );
					h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(1, "ele");
					h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(2, "mu");
					h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(3, "lep tau, ele");
					h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(4, "lep tau, mu");
					h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
					h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
					h_gen_lep2_id_incl[iHisto]->GetXaxis()->SetBinLabel(7, "\"other\" tau");
	
					// <4j Selection
					hName = "h_gen_lep2_id__lt4jSelection" + reg_gen_sys_name;
					h_gen_lep2_id_lt4j[iHisto] = new TH1D( hName, "Gen 2nd Lepton ID;ID", 7, 1.0, 8.0 );
					h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(1, "ele");
					h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(2, "mu");
					h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(3, "lep tau, ele");
					h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(4, "lep tau, mu");
					h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
					h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
					h_gen_lep2_id_lt4j[iHisto]->GetXaxis()->SetBinLabel(7, "\"other\" tau");

					// >=4j Selection
					hName = "h_gen_lep2_id__ge4jSelection" + reg_gen_sys_name;
					h_gen_lep2_id_ge4j[iHisto] = new TH1D( hName, "Gen 2nd Lepton ID;ID", 7, 1.0, 8.0 );
					h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(1, "ele");
					h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(2, "mu");
					h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(3, "lep tau, ele");
					h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(4, "lep tau, mu");
					h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
					h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
					h_gen_lep2_id_ge4j[iHisto]->GetXaxis()->SetBinLabel(7, "\"other\" tau");

	
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
      if( sample.isData && applyjson ) {
	if( !goodrun(run(),ls()) ) continue;
      }
	
      // Check duplicate event
      if( sample.isData ) {
	duplicate_removal::DorkyEventIdentifier id(run(), evt(), ls());
	if( is_duplicate(id) ) continue;
      }

      // Check WNJets genPt
      if( sample.id == sampleInfo::k_W1JetsToLNu_madgraph_pythia8 ||
					sample.id == sampleInfo::k_W2JetsToLNu_madgraph_pythia8 ||
					sample.id == sampleInfo::k_W3JetsToLNu_madgraph_pythia8 ||
					sample.id == sampleInfo::k_W4JetsToLNu_madgraph_pythia8    ) {
				if( nupt()>200.0 ) continue;
      }

			// Pre-calculate all the event weights
      wgtInfo.getEventWeights();



      /////////////////////////////
      //                         //
      // Compute Event Variables //
      //                         //
      /////////////////////////////

      // Find the gen pT of the ttbar system
      double ttbarPt = -99.9;
      LorentzVector genTTbar_LV;
      int nFoundGenTop=0;
      if( sampleIsTTbar ) {
	
				for(int iGen=0; iGen<(int)genqs_p4().size(); iGen++) {
					if( abs(genqs_id().at(iGen))==6 && genqs_isLastCopy().at(iGen) ) {
						genTTbar_LV += genqs_p4().at(iGen);
						nFoundGenTop++;
					} // end if last copy of top
				} // end loop over gen quarks

				if( nFoundGenTop == 2 ) ttbarPt = genTTbar_LV.Pt();

      } // end if sample is ttbar

      
      // Find the gen ID of the 2nd lepton
      double matched_lep_dr = 0.1;

      int gen2ndLep__idx = -1;
      int gen2ndLep__id = -99;
      int gen2ndLep__tauDecay = -1;
      int fill_bin_genLep2ID = -1;
      if( !sample.isData && is2lep() ) {
	
				// match leading lepton first
				int genLep_matchedTo_selLep__idx = -1;
				for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++) {
					if( abs(genleps_id().at(iGen)) != abs(lep1_pdgid()) ) continue;
					if( !genleps_isLastCopy().at(iGen) ) continue;
					if( !genleps_fromHardProcessFinalState().at(iGen) &&
							!genleps_fromHardProcessDecayed().at(iGen)       ) continue;
					if( ROOT::Math::VectorUtil::DeltaR(genleps_p4().at(iGen), lep1_p4()) < matched_lep_dr ) {
						genLep_matchedTo_selLep__idx = iGen;
						break;
					}
				}

				// If matched selected lepton, find lost gen lepton
				if( genLep_matchedTo_selLep__idx>0 ) {

					for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++) {
						if( iGen == genLep_matchedTo_selLep__idx ) continue;
						if( !genleps_isLastCopy().at(iGen) ) continue;
						if( !genleps_fromHardProcessFinalState().at(iGen) &&
								!genleps_fromHardProcessDecayed().at(iGen)       ) continue;
						gen2ndLep__idx = iGen;
						gen2ndLep__id = genleps_id().at(iGen);
						gen2ndLep__tauDecay = genleps_gentaudecay().at(iGen);
					}

					// If found second lep
					if( gen2ndLep__idx>=0 ) {
	      
						if( abs(gen2ndLep__id)==11 ) fill_bin_genLep2ID = 1;  // "ele";
						if( abs(gen2ndLep__id)==13 ) fill_bin_genLep2ID = 2;  // "mu";
						if( abs(gen2ndLep__id)==15 ) {
							if( gen2ndLep__tauDecay==1 ) fill_bin_genLep2ID = 3;  // "lep tau, ele";
							if( gen2ndLep__tauDecay==2 ) fill_bin_genLep2ID = 4;  // "lep tau, mu";
							if( gen2ndLep__tauDecay==3 ) fill_bin_genLep2ID = 5;  // "had tau, 1 prong";
							if( gen2ndLep__tauDecay==4 ) fill_bin_genLep2ID = 6;  // "had tau, 3 prong";
							if( gen2ndLep__tauDecay==5 ) fill_bin_genLep2ID = 7;  // "\"other\" tau";
						} // end if 2nd lep is tau


					} // end if found 2nd gen lep
				} // end if found first gen lep, matched to selected lepton
      } // end if 2lep event and not data

      // Calculate p4 of (lep1 lep2 b b) system
      LorentzVector lep1lep2bb_TLV(0.0,0.0,0.0,0.0);

      LorentzVector lep1lep2bbMet_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bbMet_pt = -99.9;

      lep1lep2bb_TLV += lep1_p4();
      if(nvetoleps()>1) lep1lep2bb_TLV += lep2_p4();
      
      int jet1_idx = -1;
      double max_deepcsv = -99.9;
      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++) {
				if( ak4pfjets_deepCSV().at(iJet) > max_deepcsv ) {
					jet1_idx = iJet;
					max_deepcsv  = ak4pfjets_deepCSV().at(iJet);
				}
      }
      if(jet1_idx>=0) lep1lep2bb_TLV += ak4pfjets_p4().at(jet1_idx);
      
      int jet2_idx = -1;
      max_deepcsv = -99.9;
      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++) {
				if( iJet==jet1_idx ) continue;
				if( ak4pfjets_deepCSV().at(iJet) > max_deepcsv ) {
					jet2_idx = iJet;
					max_deepcsv = ak4pfjets_deepCSV().at(iJet);
				}
      }
      if(jet2_idx>=0) lep1lep2bb_TLV += ak4pfjets_p4().at(jet2_idx);
      
      // Calculate p4 of (lep1 lep2 b b MET) system
      lep1lep2bbMet_TLV = lep1lep2bb_TLV;
      LorentzVector met_TLV( pfmet()*cos(pfmet_phi()), pfmet()*sin(pfmet_phi()), 0.0, pfmet() );
      lep1lep2bbMet_TLV += met_TLV;
    
      lep1lep2bbMet_pt = lep1lep2bbMet_TLV.Pt();

      // Calculate mlb using lep2 instead of lep1
      LorentzVector lep2b_TLV(0.0,0.0,0.0,0.0);
      double minDr = 99.9;
      int minBJetIdx = -99;
      if(nvetoleps()>1) {
				lep2b_TLV += lep2_p4();
				for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++) {
					if(!ak4pfjets_passMEDbtag().at(iJet)) continue;
					if(ROOT::Math::VectorUtil::DeltaR(ak4pfjets_p4().at(iJet),lep2_p4())<minDr) {
						minDr = ROOT::Math::VectorUtil::DeltaR(ak4pfjets_p4().at(iJet),lep2_p4());
						minBJetIdx = iJet;
					}
				} // end loop over jets
				if(minBJetIdx>=0) lep2b_TLV += ak4pfjets_p4().at(minBJetIdx);
      } // end if nvetoleps>1

      int mStop = mass_stop();
      int mLSP  = mass_lsp();



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
						int iGen = thisGenClassy.id;
						if( !passedGenClassies[iGen] ) continue;

						// Get the index for the histogram corresponding to this genClassy and systematic
						int histIndex = iGen*nSystematics + thisSystematic.id;

						// Fill yield histograms
						for( int category : categories_passed ) {
							if( sample.isSignalScan ) {
								TH3D* yieldHisto = (TH3D*)thisAnalyzer->GetYieldHistogram( histIndex );
								yieldHisto->Fill( mStop, mLSP, category, weight );
							}
							else thisAnalyzer->GetYieldHistogram( histIndex )->Fill( category, weight );
						}

						/////////////////////////////////////
						//                                 //
						// Fill other non-yield histograms //
						//                                 //
						/////////////////////////////////////

						if( thisSystematic.id == sysInfo::k_nominal ) {

							for(int iMassPt=0; iMassPt<nMassPts; iMassPt++) {

								if( sample.isSignalScan && mStop!=sample.massPtList[iMassPt].first && mLSP!=sample.massPtList[iMassPt].second ) continue;
								//if(!isnormal(wgt_nominal)) cout << "NaN/inf weight: nEntries=" << wgtInfo.nEvents << ", lepSF=" << wgtInfo.sf_lep << ", vetoLep="<< wgtInfo.sf_vetoLep << ", btagSF=" << wgtInfo.sf_bTag << endl;
								// Histo Index
								int iHisto = iAna*nGenClassy*nMassPts + iGen*nMassPts + iMassPt;

								// Vars
								double nGoodJets = ngoodjets();

								bool add2ndLepToMet = thisAnalyzer->GetAdd2ndLep();

								double mt =         add2ndLepToMet ? mt_met_lep_rl() : mt_met_lep();
								double modTopness = add2ndLepToMet ? topnessMod_rl() : topnessMod();
								double met =        add2ndLepToMet ? pfmet_rl() : pfmet();

								double mlb = Mlb_closestb();
								if( TString(thisAnalyzer->GetLabel()).Contains("CR0b") ) mlb = ( lep1_p4() + ak4pfjets_leadbtag_p4() ).M();

								// Met Sideband CR area, met>=150

								if( met>=150 && met<250 ) {
									// mlb, met sideband CR
									h_mlb_150to250met_incl[iHisto]->Fill( mlb, weight );
									if( nGoodJets<4 )  h_mlb_150to250met_lt4j[iHisto]->Fill( mlb, weight );
									if( nGoodJets>=4 ) h_mlb_150to250met_ge4j[iHisto]->Fill( mlb, weight );
	      
									// mlb_lep2, met sideband CR
									if(nvetoleps()>1 && minBJetIdx>=0) {
										h_mlb_lep2_150to250met_incl[iHisto]->Fill( lep2b_TLV.M(), weight );
										if( nGoodJets<4 )  h_mlb_lep2_150to250met_lt4j[iHisto]->Fill( lep2b_TLV.M(), weight );
										if( nGoodJets>=4 ) h_mlb_lep2_150to250met_ge4j[iHisto]->Fill( lep2b_TLV.M(), weight );
									}

								} // end if 150<met<250

								// Signal Region Area, met>=250
								if( met<250.0 ) continue;
	    
								// nJets
								h_nJets[iHisto]->Fill( nGoodJets, weight );

								// nBTags
								h_nBTags[iHisto]->Fill( ngoodbtags(), weight );
	    
								// lep1 pT
								h_lep1Pt_incl[iHisto]->Fill( lep1_p4().Pt(), weight );

								// lep2 pT
								if( nvetoleps()>1 ) h_lep2Pt_incl[iHisto]->Fill( lep2_p4().Pt(), weight );

								// jet pT
								for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++) h_jetPt_incl[iHisto]->Fill( ak4pfjets_p4().at(iJet).Pt(), weight );

								// jet1 pT
								h_jet1Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(0).Pt(), weight );

								// jet2 pT
								h_jet2Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(1).Pt(), weight );

								// DeepCSV jet1 pT
								if(jet1_idx>=0) h_deepcsvJet1Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(jet1_idx).Pt(), weight );

								// DeepCSV jet2 pT
								if(jet2_idx>=0) h_deepcsvJet2Pt_incl[iHisto]->Fill( ak4pfjets_p4().at(jet2_idx).Pt(), weight );

								// met
								h_met_incl[iHisto]->Fill( met, weight );
								if( nGoodJets<4  ) h_met_lt4j[iHisto]->Fill( met, weight );
								if( nGoodJets>=4 ) h_met_ge4j[iHisto]->Fill( met, weight );

								// lep1lep2bbMetPt
								h_lep1lep2bbMetPt_incl[iHisto]->Fill( lep1lep2bbMet_pt, weight );
								if( nGoodJets<4  ) h_lep1lep2bbMetPt_lt4j[iHisto]->Fill( lep1lep2bbMet_pt, weight );
								if( nGoodJets>=4 ) h_lep1lep2bbMetPt_ge4j[iHisto]->Fill( lep1lep2bbMet_pt, weight );

								// mt
								h_mt_incl[iHisto]->Fill( mt, weight );

								// modTopness
								h_modTopness_incl[iHisto]->Fill( modTopness, weight );
								if( nGoodJets<4  ) h_modTopness_lt4j[iHisto]->Fill( modTopness, weight );
								if( nGoodJets>=4 ) h_modTopness_ge4j[iHisto]->Fill( modTopness, weight );

								// mlb
								h_mlb_incl[iHisto]->Fill( mlb, weight );
								if( nGoodJets<4 )  h_mlb_lt4j[iHisto]->Fill( mlb, weight );
								if( nGoodJets>=4 ) h_mlb_ge4j[iHisto]->Fill( mlb, weight );

								// mlb, modTopness bins
								if(modTopness<0.0)   h_mlb_lt0modTopness[iHisto]->Fill( mlb, weight );
								if(modTopness>=0.0)  h_mlb_ge0modTopness[iHisto]->Fill( mlb, weight );
								if(modTopness>=10.0) h_mlb_ge10modTopness[iHisto]->Fill( mlb, weight );

								// mlb_lep2
								if(nvetoleps()>1 && minBJetIdx>=0) {
									h_mlb_lep2_incl[iHisto]->Fill( lep2b_TLV.M(), weight );
									if( nGoodJets<4 )  h_mlb_lep2_lt4j[iHisto]->Fill( lep2b_TLV.M(), weight );
									if( nGoodJets>=4 ) h_mlb_lep2_ge4j[iHisto]->Fill( lep2b_TLV.M(), weight );
								}

								// Gen TTBar System
								if( sampleIsTTbar ) {
									h_gen_ttbarPt_incl[iHisto]->Fill( ttbarPt, weight );
									if( nGoodJets<4 )  h_gen_ttbarPt_lt4j[iHisto]->Fill( ttbarPt, weight );
									if( nGoodJets>=4 ) h_gen_ttbarPt_ge4j[iHisto]->Fill( ttbarPt, weight );
								}

								// Gen 2nd Lep ID
								if( !sample.isData && is2lep() && gen2ndLep__idx>=0 ) {
									h_gen_lep2_id_incl[iHisto]->Fill( fill_bin_genLep2ID, weight );
									if( ngoodjets()<4 )  h_gen_lep2_id_lt4j[iHisto]->Fill( fill_bin_genLep2ID, weight );
									if( ngoodjets()>=4 ) h_gen_lep2_id_ge4j[iHisto]->Fill( fill_bin_genLep2ID, weight );
								}

							} // end loop over mass points (1 if not signal scan)

						} // End filling of non-yield histograms

					} // End loop over genClassy's

				} // End loop over systematics

			} // End loop over analyzers

		} // End loop over events in tree


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
  for(int iAna=0; iAna<nAnalyzers; iAna++) {
	  cout << "    " << analyzers.at(iAna)->GetLabel() << " Cutflow: " << endl;
	  for(int iCut=1; iCut<=(int)h_cutflow[iAna]->GetNbinsX(); iCut++) {
		  cout << "      nEvents pass " << h_cutflow[iAna]->GetXaxis()->GetBinLabel(iCut) << " = " << h_cutflow[iAna]->GetBinContent(iCut) << endl;
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


