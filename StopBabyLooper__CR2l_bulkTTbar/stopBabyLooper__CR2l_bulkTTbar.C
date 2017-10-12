#include "stopBabyLooper__CR2l_bulkTTbar.h"

//////////////////////////////
//                          //
// Configuration Parameters //
//                          //
//////////////////////////////

bool analyzeFast_           = false;  // skips systematics

bool applyjson              = true;

bool add2ndLepToMet_        = false;

bool useBTagSFs_fromUtils_  = true;
bool useLepSFs_fromUtils_   = true;
        
bool apply_diLepTrigger_sf_ = true;  // for ee/emu/mumu triggers only
bool apply_bTag_sf_         = true;  // event weight, product of all jet wgts
bool apply_lep_sf_          = true;  // both lep1 and lep2 (if available) are multiplied together
bool apply_vetoLep_sf_      = true;  // this is actually the lost lepton sf, only !=1 if there is >=2 genLeptons and ==1 recoLeptons in the event
bool apply_lepFS_sf_        = false;
bool apply_topPt_sf_        = false; // true=sf, false=uncertainty
bool apply_metRes_sf_       = true;
bool apply_ttbarSysPt_sf_   = false; // true=sf, false=uncertainty, only !=1.0 for madgraph tt2l, tW2l
bool apply_ISR_sf_          = true; // only !=1.0 for signal
bool apply_pu_sf_           = true; 
bool apply_sample_sf_       = true; // only !=1.0 for some WJetsHT samps
  



//
// Main
//
int stopBabyLooper__CR2l_bulkTTbar(){

	// Use sumw2 for all histograms
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	TH3::SetDefaultSumw2();


  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList_CR2l_bulkTTbar(); 


  //
  // Examples for Quick Tests
  //
  //sampleList.clear();
  //sampleList.push_back( sampleInfo::k_met );
  //sampleList.push_back( sampleInfo::k_diLepton );
  //sampleList.push_back( sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 );
  //sampleList.push_back( sampleInfo::k_TTWJetsToLNu_amcnlo_pythia8 );

  //
  // Set up all the analyzer objects we'll need. One for each dilepton flavor we want to look at.
  //
  analyzer CR2l_bulkTTbar_emu( "CR2l_bulkTTbar_emu" );
  CR2l_bulkTTbar_emu.AddSelections( selectionInfo::get_selection_CR2l_bulkTTbar() );
  CR2l_bulkTTbar_emu.AddSelection( "emuFlavor", selectionInfo::pass_emu_diLepFlavor );
  CR2l_bulkTTbar_emu.AddCategories(  categoryInfo::passCategory_CR2l_bulkTTbar );
  CR2l_bulkTTbar_emu.SetYieldTemplate(  categoryInfo::getYieldHistoTemplate_CR2l_bulkTTbar() );


  // analyzer CR2l_bulkTTbar_ee( "CR2l_bulkTTbar_ee" );
  // CR2l_bulkTTbar_ee.AddSelections( selectionInfo::get_selection_CR2l_bulkTTbar() );
  // CR2l_bulkTTbar_ee.AddSelection( "eeFlavor", selectionInfo::pass_ee_diLepFlavor );
  // CR2l_bulkTTbar_ee.AddCategories( categoryInfo::passCategory_CR2l_bulkTTbar );
  // CR2l_bulkTTbar_ee.SetYieldTemplate( categoryInfo::getYieldHistoTemplate_CR2l_bulkTTbar() );


  // analyzer CR2l_bulkTTbar_mumu( "CR2l_bulkTTbar_mumu" );
  // CR2l_bulkTTbar_mumu.AddSelections( selectionInfo::get_selection_CR2l_bulkTTbar() );
  // CR2l_bulkTTbar_mumu.AddSelection( "mumuFlavor", selectionInfo::pass_mumu_diLepFlavor );
  // CR2l_bulkTTbar_mumu.AddCategories( categoryInfo::passCategory_CR2l_bulkTTbar );
  // CR2l_bulkTTbar_mumu.SetYieldTemplate( categoryInfo::getYieldHistoTemplate_CR2l_bulkTTbar() );


  // analyzer CR2l_bulkTTbar_incl( "CR2l_bulkTTbar_incl" );
  // CR2l_bulkTTbar_incl.AddSelections( selectionInfo::get_selection_CR2l_bulkTTbar() );
  // CR2l_bulkTTbar_incl.AddCategories( categoryInfo::passCategory_CR2l_bulkTTbar );
  // CR2l_bulkTTbar_incl.SetYieldTemplate( categoryInfo::getYieldHistoTemplate_CR2l_bulkTTbar() );

  std::vector<analyzer*> analyzer_list = {&CR2l_bulkTTbar_emu};


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
			  // Custom list of systematics for ttbar2l bulk CR
			  iter->AddSystematics( {sysInfo::Util(sysInfo::k_nominal),
						  sysInfo::Util(sysInfo::k_JESUp),
						  sysInfo::Util(sysInfo::k_JESDown),
						  sysInfo::Util(sysInfo::k_ISRUp),
						  sysInfo::Util(sysInfo::k_ISRDown),
						  sysInfo::Util(sysInfo::k_metResUp),
						  sysInfo::Util(sysInfo::k_metResDown),
						  sysInfo::Util(sysInfo::k_lepSFUp),
						  sysInfo::Util(sysInfo::k_lepSFDown),
						  sysInfo::Util(sysInfo::k_pdfUp),
						  sysInfo::Util(sysInfo::k_pdfDown),
						  sysInfo::Util(sysInfo::k_alphasUp),
						  sysInfo::Util(sysInfo::k_alphasDown),
						  sysInfo::Util(sysInfo::k_q2Up),
						  sysInfo::Util(sysInfo::k_q2Down) } );

		  }
	  } // End loop over analyzers

	  looper( sampleList[iSample], analyzer_list );
  }


  //
  // Done
  //
  return 0;

}




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

  //
  // Input chain
  //
  TChain *chain = new TChain("t");
  
  cout << "    Processing the following: " << endl;  
  for(int iFile=0; iFile<(int)sample.inputBabies.size(); iFile++){
    
    // input directory
    TString input = sample.baby_i_o.first;
    
    // input file
    input += sample.inputBabies[iFile];
    
    input.ReplaceAll("/skim/","/output/"); // Take normal list of baby files, but use the unskimmed versions
    
    chain->Add( input );
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
  const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"; // 36.46fb final 2016 run 
  //const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-282037_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"; // 29.53fb golden json, intermediate status
  //const char* json_file = "../StopCORE/inputs/json_files/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"; // ICHEP 12.9fb SUS-16-028
  if( sample.isData ) set_goodrun_file_json(json_file);
  

  //
  // Event Weight Utilities
  //
  cout << "    Loading eventWeight Utilities..." << endl << endl;
  wgtInfo.setUp( sample.id, useBTagSFs_fromUtils_, useLepSFs_fromUtils_, add2ndLepToMet_ );
  wgtInfo.apply_diLepTrigger_sf = apply_diLepTrigger_sf_;
  wgtInfo.apply_bTag_sf         = apply_bTag_sf_;
  wgtInfo.apply_lep_sf          = apply_lep_sf_;
  wgtInfo.apply_vetoLep_sf      = apply_vetoLep_sf_;
  wgtInfo.apply_lepFS_sf        = apply_lepFS_sf_;
  wgtInfo.apply_topPt_sf        = apply_topPt_sf_;
  wgtInfo.apply_metRes_sf       = apply_metRes_sf_;
  wgtInfo.apply_ttbarSysPt_sf   = apply_ttbarSysPt_sf_;
  wgtInfo.apply_ISR_sf          = apply_ISR_sf_;
  wgtInfo.apply_pu_sf           = apply_pu_sf_;
  wgtInfo.apply_sample_sf       = apply_sample_sf_;
  
  
  //
  // Declare Systematics
  //
  cout << "    Loading systematicList: ";
  std::vector< sysInfo::Util > systematicList;
  if( sample.isData || analyzeFast_ ){
    systematicList.push_back(sysInfo::Util(sysInfo::k_nominal));
  }
  else{
    // Custom List
    systematicList.clear();
    systematicList.push_back( sysInfo::Util(sysInfo::k_nominal) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_JESUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_JESDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_ISRUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_ISRDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_metResUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_metResDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_lepSFUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_lepSFDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_pdfUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_pdfDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_alphasUp) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_alphasDown) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_q2Up) );
    systematicList.push_back( sysInfo::Util(sysInfo::k_q2Down) );
  }  
  const int nSystematics = (int)systematicList.size();
  cout << nSystematics << " systematics" << endl << endl;
  
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
  //    histogram_name = "your_name_here"+"__emu"+"__genClassy_"+genClassyObject.label+"__systematic_"+sysInfoObject.label;
  //
  //
  //  Where "__emu" can be replaced by "__ee", or "__mumu", or "__incl"
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
				thisAnalyzer->SetYieldHistogram( histIndex, h_tmp );

				// Need to do signal yield histograms too?

			} // End loop over systematics
		} // End loop over genClassys
	} // End loop over analyzers


  // const int nHistos = nLepFlav*nGenClassy*nSystematics;
  const int nHistos = nAnalyzers*nGenClassy*nSystematics;



  //
  // Histograms with all systematics
  //
  TH1D *h_met_ge1bTags[nHistos];
  TH1D *h_met_ge1bTags_ge50ttbarSysPt[nHistos];
  TH1D *h_met_ge1bTags_ge100ttbarSysPt[nHistos];
  TH1D *h_met_ge1bTags_ge150ttbarSysPt[nHistos];
  
  TH1D *h_diLepPt_ge1bTags[nHistos];
  TH1D *h_diLepPt_ge1bTags_ge100met[nHistos];
  TH1D *h_diLepPt_ge1bTags_ge150met[nHistos];
  
  TH1D *h_lep1lep2bbMetPt_ge1bTags[nHistos];
  TH1D *h_lep1lep2bbMetPt_ge1bTags_ge100met[nHistos];
  TH1D *h_lep1lep2bbMetPt_ge1bTags_ge150met[nHistos];

  TH1D *h_lep1lep2bbMetPt_ge1bTags_0to12nVtx[nHistos];
  TH1D *h_lep1lep2bbMetPt_ge1bTags_12to24nVtx[nHistos];
  TH1D *h_lep1lep2bbMetPt_ge1bTags_ge24nVtx[nHistos];
  
  // Loop over lepFlavs, genClassifications and systematics
  for(int iAna=0; iAna<nAnalyzers; iAna++){
    for(int iGen=0; iGen<nGenClassy; iGen++){
      for(int iSys=0; iSys<nSystematics; iSys++){
	
	      // Histo Index
	      int iHisto = iAna*nGenClassy*nSystematics + iGen*nSystematics + iSys;
	      //int iHisto = iGen*nSystematics + iSys;
	
	      TString hName = "";

	      // Flav, Gen and Systematic String
	      TString flav_gen_sys_name = "__";
	      flav_gen_sys_name += analyzers.at(iAna)->GetLabel(); 
	      flav_gen_sys_name += "__genClassy_";
	      flav_gen_sys_name += genClassyList[iGen].label;
	      flav_gen_sys_name += "__systematic_";
	      flav_gen_sys_name += systematicList[iSys].label;


	      // CR2l bulk TTbar Singal Regions

	      // Baseline Name
	      TString h_name_CR2l_bulkTTbar_base = "__";


	      // MET, ge1bTags
	      hName = "h_met__ge1bTags" + flav_gen_sys_name;
	      h_met_ge1bTags[iHisto] = new TH1D( hName, "MET, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

	      // MET, ge1bTags, ge50ttbarSysPt
	      hName = "h_met__ge1bTags_ge50ttbarSysPt" + flav_gen_sys_name;
	      h_met_ge1bTags_ge50ttbarSysPt[iHisto] = new TH1D( hName, "MET, >=1 bTags, ttbar system pT>50;pT [GeV]", 32, 0.0, 800.0);

	      // MET, ge1bTags, ge100ttbarSysPt
	      hName = "h_met__ge1bTags_ge100ttbarSysPt" + flav_gen_sys_name;
	      h_met_ge1bTags_ge100ttbarSysPt[iHisto] = new TH1D( hName, "MET, >=1 bTags, ttbar system pT>100;pT [GeV]", 32, 0.0, 800.0);

	      // MET, ge1bTags, ge150ttbarSysPt
	      hName = "h_met__ge1bTags_ge150ttbarSysPt" + flav_gen_sys_name;
	      h_met_ge1bTags_ge150ttbarSysPt[iHisto] = new TH1D( hName, "MET, >=1 bTags, ttbar system pT>150;pT [GeV]", 32, 0.0, 800.0);

	      // diLep pT, ge1bTags
	      hName = "h_diLepPt__ge1bTags" + flav_gen_sys_name;
	      h_diLepPt_ge1bTags[iHisto] = new TH1D( hName, "diLepton System pT, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

	      // diLep pT, ge1bTags, ge100met
	      hName = "h_diLepPt__ge1bTags_ge100met" + flav_gen_sys_name;
	      h_diLepPt_ge1bTags_ge100met[iHisto] = new TH1D( hName, "diLepton System pT, >=1 bTags, MET>100;pT [GeV]", 32, 0.0, 800.0);

	      // diLep pT, ge1bTags, ge150met
	      hName = "h_diLepPt__ge1bTags_ge150met" + flav_gen_sys_name;
	      h_diLepPt_ge1bTags_ge150met[iHisto] = new TH1D( hName, "diLepton System pT, >=1 bTags, MET>150;pT [GeV]", 32, 0.0, 800.0);

	      // lep1lep2bbMet pT, ge1bTags
	      hName = "h_lep1lep2bbMetPt__ge1bTags" + flav_gen_sys_name;
	      h_lep1lep2bbMetPt_ge1bTags[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags;p_{T} [GeV]", 32, 0.0, 800.0 );

	      // lep1lep2bbMet pT, ge1bTags, ge100met
	      hName = "h_lep1lep2bbMetPt__ge1bTags_ge100met" + flav_gen_sys_name;
	      h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags, MET>100;p_{T} [GeV]", 32, 0.0, 800.0 );

	      // lep1lep2bbMet pT, ge1bTags, ge150met
	      hName = "h_lep1lep2bbMetPt__ge1bTags_ge150met" + flav_gen_sys_name;
	      h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags, MET>150;p_{T} [GeV]", 32, 0.0, 800.0 );

	      // lep1lep2bbMet pT, ge1bTags, nVtx 0to12
	      hName = "h_lep1lep2bbMetPt__ge1bTags_0to12nVtx" + flav_gen_sys_name;
	      h_lep1lep2bbMetPt_ge1bTags_0to12nVtx[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags, 0<nVtx<12;p_{T} [GeV]", 32, 0.0, 800.0 );

	      // lep1lep2bbMet pT, ge1bTags, nVtx 12to24
	      hName = "h_lep1lep2bbMetPt__ge1bTags_12to24nVtx" + flav_gen_sys_name;
	      h_lep1lep2bbMetPt_ge1bTags_12to24nVtx[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags, 12<nVtx<24;p_{T} [GeV]", 32, 0.0, 800.0 );

	      // lep1lep2bbMet pT, ge1bTags, nVtx >=24
	      hName = "h_lep1lep2bbMetPt__ge1bTags_ge24nVtx" + flav_gen_sys_name;
	      h_lep1lep2bbMetPt_ge1bTags_ge24nVtx[iHisto] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags, nVtx>=24;p_{T} [GeV]", 32, 0.0, 800.0 );
       
      } // end loop over systematics
    } // end loop over gen classifications
  } // end loop over analyzers

  
  //////////////////////////
  //                      //
  // Non-yield Histograms //
  //                      //
  //////////////////////////

  // nVtx
  TH1D *h_nVtx[nAnalyzers][nGenClassy];
  TH1D *h_nVtx_noPUwgt[nAnalyzers][nGenClassy];
  TH1D *h_nTrueVtx[nAnalyzers][nGenClassy];
  
  // nBTags
  TH1D *h_nBTags[nAnalyzers][nGenClassy];
  
  // nJets
  TH1D *h_nJets_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_nJets_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_nJets_ge2bTags[nAnalyzers][nGenClassy];
  
  // nISRJets
  TH1D *h_nISRJets_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_nISRJets_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_nISRJets_ge2bTags[nAnalyzers][nGenClassy];
  
  // lep1 pT
  TH1D *h_lep1Pt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_lep1Pt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_lep1Pt_ge2bTags[nAnalyzers][nGenClassy];

  // lep2 pT
  TH1D *h_lep2Pt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_lep2Pt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_lep2Pt_ge2bTags[nAnalyzers][nGenClassy];

  // el pT
  TH1D *h_elPt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_elPt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_elPt_ge2bTags[nAnalyzers][nGenClassy];

  // mu pT
  TH1D *h_muPt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_muPt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_muPt_ge2bTags[nAnalyzers][nGenClassy];

  
  // diLep pT
  TH1D *h_diLepPt_ge0bTags[nAnalyzers][nGenClassy];
  //TH1D *h_diLepPt_ge1bTags[nAnalyzers][nGenClassy]; // moved to section with all systematics
  TH1D *h_diLepPt_ge2bTags[nAnalyzers][nGenClassy];

  // jet pT
  TH1D *h_jetPt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_jetPt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_jetPt_ge2bTags[nAnalyzers][nGenClassy];

  // jet 1 pT
  TH1D *h_jet1Pt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_jet1Pt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_jet1Pt_ge2bTags[nAnalyzers][nGenClassy];

  // jet 2 pT
  TH1D *h_jet2Pt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_jet2Pt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_jet2Pt_ge2bTags[nAnalyzers][nGenClassy];

  // DeepCSV jet 1 pT
  TH1D *h_deepcsvJet1Pt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_deepcsvJet1Pt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_deepcsvJet1Pt_ge2bTags[nAnalyzers][nGenClassy];

  // DeepCSV jet 2 pT
  TH1D *h_deepcsvJet2Pt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_deepcsvJet2Pt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_deepcsvJet2Pt_ge2bTags[nAnalyzers][nGenClassy];
  
  // met
  TH1D *h_met_ge0bTags[nAnalyzers][nGenClassy];
  //TH1D *h_met_ge1bTags[nAnalyzers][nGenClassy]; // moved to section for all systematics
  TH1D *h_met_ge2bTags[nAnalyzers][nGenClassy];

  // lep1lep2bbMet, ttbar visible system pT
  TH1D *h_lep1lep2bbPt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_lep1lep2bbPt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_lep1lep2bbPt_ge2bTags[nAnalyzers][nGenClassy];
 
  // lep1lep2bbMet, ttbar system pT
  TH1D *h_lep1lep2bbMetPt_ge0bTags[nAnalyzers][nGenClassy];
  //TH1D *h_lep1lep2bbMetPt_ge1bTags[nAnalyzers][nGenClassy]; moved to section for all systematics
  TH1D *h_lep1lep2bbMetPt_ge2bTags[nAnalyzers][nGenClassy];
  
  // mt
  TH1D *h_mt_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_mt_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_mt_ge2bTags[nAnalyzers][nGenClassy];

  // modifiedTopness
  TH1D *h_modTopness_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_modTopness_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_modTopness_ge2bTags[nAnalyzers][nGenClassy];

  // mt2w
  TH1D *h_mt2w_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_mt2w_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_mt2w_ge2bTags[nAnalyzers][nGenClassy];

  // Mlb
  TH1D *h_mlb_ge0bTags[nAnalyzers][nGenClassy];
  TH1D *h_mlb_ge1bTags[nAnalyzers][nGenClassy];
  TH1D *h_mlb_ge2bTags[nAnalyzers][nGenClassy];

  f_output->cd(); // All non-yield histos will belong to the output file

  for(int iAna=0; iAna<nAnalyzers; iAna++){
    for(int iGen=0; iGen<nGenClassy; iGen++){

      TString hName = "";
      
      TString flav_gen_name = "__";
      flav_gen_name += analyzers.at(iAna)->GetLabel(); 
      flav_gen_name += "__genClassy_";
      flav_gen_name += genClassyList[iGen].label;

      TString flav_gen_sys_name = flav_gen_name;
      flav_gen_sys_name += "__systematic_";
      flav_gen_sys_name += systematicList[0].label;


      // NVtx
      hName = "h_nVtx" + flav_gen_sys_name;
      h_nVtx[iAna][iGen] = new TH1D( hName, "Number of Primary Vertices;nVtx", 60, 0.0, 60.0);

      // NVtx, no pileup wgt
      hName = "h_nVtx_noPUwgt" + flav_gen_sys_name;
      h_nVtx_noPUwgt[iAna][iGen] = new TH1D( hName, "Number of Primary Vertices, without pileup weight;nVtx", 60, 0.0, 60.0);

      // NVtx
      hName = "h_nTrueVtx" + flav_gen_sys_name;
      h_nTrueVtx[iAna][iGen] = new TH1D( hName, "Number of True Primary Vertices;nVtx", 60, 0.0, 60.0);


      // NBTags
      hName = "h_nBTags" + flav_gen_sys_name;
      h_nBTags[iAna][iGen] = new TH1D( hName, "Number of bTagged Jets;nBTags", 5, -0.5, 4.5);


      // Njets, g0bTags
      hName = "h_nJets__ge0bTags" + flav_gen_sys_name;
      h_nJets_ge0bTags[iAna][iGen] = new TH1D( hName, "Number of Selected Jets, >=0 bTags;nJets", 11, -0.5, 10.5);

      // Njets, g1bTags
      hName = "h_nJets__ge1bTags" + flav_gen_sys_name;
      h_nJets_ge1bTags[iAna][iGen] = new TH1D( hName, "Number of Selected Jets, >=1 bTags;nJets", 11, -0.5, 10.5);

      // Njets, g2bTags
      hName = "h_nJets__ge2bTags" + flav_gen_sys_name;
      h_nJets_ge2bTags[iAna][iGen] = new TH1D( hName, "Number of Selected Jets, >=2 bTags;nJets", 11, -0.5, 10.5);

      // Njets, g0bTags
      hName = "h_nISRJets__ge0bTags" + flav_gen_sys_name;
      h_nISRJets_ge0bTags[iAna][iGen] = new TH1D( hName, "Number of Selected Jets, >=0 bTags;nISRJets", 11, -0.5, 10.5);

      // Njets, g1bTags
      hName = "h_nISRJets__ge1bTags" + flav_gen_sys_name;
      h_nISRJets_ge1bTags[iAna][iGen] = new TH1D( hName, "Number of Selected Jets, >=1 bTags;nISRJets", 11, -0.5, 10.5);

      // Njets, g2bTags
      hName = "h_nISRJets__ge2bTags" + flav_gen_sys_name;
      h_nISRJets_ge2bTags[iAna][iGen] = new TH1D( hName, "Number of Selected Jets, >=2 bTags;nISRJets", 11, -0.5, 10.5);


      // lep1 pT, ge0bTags
      hName = "h_lep1Pt__ge0bTags" + flav_gen_sys_name;
      h_lep1Pt_ge0bTags[iAna][iGen] = new TH1D( hName, "Leading Lepton pT, >=0 bTags;pT [GeV]", 20, 0.0, 200.0);

      // lep1 pT, ge1bTags
      hName = "h_lep1Pt__ge1bTags" + flav_gen_sys_name;
      h_lep1Pt_ge1bTags[iAna][iGen] = new TH1D( hName, "Leading Lepton pT, >=1 bTags;pT [GeV]", 20, 0.0, 200.0);

      // lep1 pT, ge2bTags
      hName = "h_lep1Pt__ge2bTags" + flav_gen_sys_name;
      h_lep1Pt_ge2bTags[iAna][iGen] = new TH1D( hName, "Leading Lepton pT, >=2 bTags;pT [GeV]", 20, 0.0, 200.0);

     
      // lep2 pT, ge0bTags
      hName = "h_lep2Pt__ge0bTags" + flav_gen_sys_name;
      h_lep2Pt_ge0bTags[iAna][iGen] = new TH1D( hName, "Trailing Lepton pT, >=0 bTags;pT [GeV]", 20, 0.0, 200.0);

      // lep2 pT, ge1bTags
      hName = "h_lep2Pt__ge1bTags" + flav_gen_sys_name;
      h_lep2Pt_ge1bTags[iAna][iGen] = new TH1D( hName, "Trailing Lepton pT, >=1 bTags;pT [GeV]", 20, 0.0, 200.0);

      // lep2 pT, ge2bTags
      hName = "h_lep2Pt__ge2bTags" + flav_gen_sys_name;
      h_lep2Pt_ge2bTags[iAna][iGen] = new TH1D( hName, "Trailing Lepton pT, >=2 bTags;pT [GeV]", 20, 0.0, 200.0);


      // el pT, ge0bTags
      hName = "h_elPt__ge0bTags" + flav_gen_sys_name;
      h_elPt_ge0bTags[iAna][iGen] = new TH1D( hName, "Electron pT, >=0 bTags;pT [GeV]", 20, 0.0, 200.0);

      // el pT, ge1bTags
      hName = "h_elPt__ge1bTags" + flav_gen_sys_name;
      h_elPt_ge1bTags[iAna][iGen] = new TH1D( hName, "Electron pT, >=1 bTags;pT [GeV]", 20, 0.0, 200.0);

      // el pT, ge2bTags
      hName = "h_elPt__ge2bTags" + flav_gen_sys_name;
      h_elPt_ge2bTags[iAna][iGen] = new TH1D( hName, "Electron pT, >=2 bTags;pT [GeV]", 20, 0.0, 200.0);


      // mu pT, ge0bTags
      hName = "h_muPt__ge0bTags" + flav_gen_sys_name;
      h_muPt_ge0bTags[iAna][iGen] = new TH1D( hName, "Muon pT, >=0 bTags;pT [GeV]", 20, 0.0, 200.0);

      // mu pT, ge1bTags
      hName = "h_muPt__ge1bTags" + flav_gen_sys_name;
      h_muPt_ge1bTags[iAna][iGen] = new TH1D( hName, "Muon pT, >=1 bTags;pT [GeV]", 20, 0.0, 200.0);

      // mu pT, ge2bTags
      hName = "h_muPt__ge2bTags" + flav_gen_sys_name;
      h_muPt_ge2bTags[iAna][iGen] = new TH1D( hName, "Muon pT, >=2 bTags;pT [GeV]", 20, 0.0, 200.0);

      
      // diLep pT, ge0bTags
      hName = "h_diLepPt__ge0bTags" + flav_gen_sys_name;
      h_diLepPt_ge0bTags[iAna][iGen] = new TH1D( hName, "diLepton System pT, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // diLep pT, ge1bTags
      //hName = "h_diLepPt__ge1bTags" + flav_gen_sys_name;
      //h_diLepPt_ge1bTags[iAna][iGen] = new TH1D( hName, "diLepton System pT, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // diLep pT, ge2bTags
      hName = "h_diLepPt__ge2bTags" + flav_gen_sys_name;
      h_diLepPt_ge2bTags[iAna][iGen] = new TH1D( hName, "diLepton System pT, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // jet pT, ge0bTags
      hName = "h_jetPt__ge0bTags" + flav_gen_sys_name;
      h_jetPt_ge0bTags[iAna][iGen] = new TH1D( hName, "Selected Jet pT, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // jet pT, ge1bTags
      hName = "h_jetPt__ge1bTags" + flav_gen_sys_name;
      h_jetPt_ge1bTags[iAna][iGen] = new TH1D( hName, "Selected Jet pT, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // jet pT, ge2bTags
      hName = "h_jetPt__ge2bTags" + flav_gen_sys_name;
      h_jetPt_ge2bTags[iAna][iGen] = new TH1D( hName, "Selected Jet pT, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // jet1 pT, ge0bTags
      hName = "h_jet1Pt__ge0bTags" + flav_gen_sys_name;
      h_jet1Pt_ge0bTags[iAna][iGen] = new TH1D( hName, "Leading Jet pT, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // jet1 pT, ge1bTags
      hName = "h_jet1Pt__ge1bTags" + flav_gen_sys_name;
      h_jet1Pt_ge1bTags[iAna][iGen] = new TH1D( hName, "Leading Jet pT, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // jet1 pT, ge2bTags
      hName = "h_jet1Pt__ge2bTags" + flav_gen_sys_name;
      h_jet1Pt_ge2bTags[iAna][iGen] = new TH1D( hName, "Leading Jet pT, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // jet2 pT, ge0bTags
      hName = "h_jet2Pt__ge0bTags" + flav_gen_sys_name;
      h_jet2Pt_ge0bTags[iAna][iGen] = new TH1D( hName, "Trailing Jet pT, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // jet2 pT, ge1bTags
      hName = "h_jet2Pt__ge1bTags" + flav_gen_sys_name;
      h_jet2Pt_ge1bTags[iAna][iGen] = new TH1D( hName, "Trailing Jet pT, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // jet2 pT, ge2bTags
      hName = "h_jet2Pt__ge2bTags" + flav_gen_sys_name;
      h_jet2Pt_ge2bTags[iAna][iGen] = new TH1D( hName, "Trailing Jet pT, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // DeepCSVJet1 pT, ge0bTags
      hName = "h_deepcsvJet1Pt__ge0bTags" + flav_gen_sys_name;
      h_deepcsvJet1Pt_ge0bTags[iAna][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // DeepCSVJet1 pT, ge1bTags
      hName = "h_deepcsvJet1Pt__ge1bTags" + flav_gen_sys_name;
      h_deepcsvJet1Pt_ge1bTags[iAna][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // DeepCSVJet1 pT, ge2bTags
      hName = "h_deepcsvJet1Pt__ge2bTags" + flav_gen_sys_name;
      h_deepcsvJet1Pt_ge2bTags[iAna][iGen] = new TH1D( hName, "Highest bTag Disc. Jet pT, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // DeepCSVJet2 pT, ge0bTags
      hName = "h_deepcsvJet2Pt__ge0bTags" + flav_gen_sys_name;
      h_deepcsvJet2Pt_ge0bTags[iAna][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // DeepCSVJet2 pT, ge1bTags
      hName = "h_deepcsvJet2Pt__ge1bTags" + flav_gen_sys_name;
      h_deepcsvJet2Pt_ge1bTags[iAna][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // DeepCSVJet2 pT, ge2bTags
      hName = "h_deepcsvJet2Pt__ge2bTags" + flav_gen_sys_name;
      h_deepcsvJet2Pt_ge2bTags[iAna][iGen] = new TH1D( hName, "2nd Highest bTag Disc. Jet pT, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // MET, ge0bTags
      hName = "h_met__ge0bTags" + flav_gen_sys_name;
      h_met_ge0bTags[iAna][iGen] = new TH1D( hName, "MET, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // MET, ge1bTags
      //hName = "h_met__ge1bTags" + flav_gen_sys_name;
      //h_met_ge1bTags[iAna][iGen] = new TH1D( hName, "MET, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // MET, ge2bTags
      hName = "h_met__ge2bTags" + flav_gen_sys_name;
      h_met_ge2bTags[iAna][iGen] = new TH1D( hName, "MET, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // lep1lep2bb pT, ge0bTags
      hName = "h_lep1lep2bbPt__ge0bTags" + flav_gen_sys_name;
      h_lep1lep2bbPt_ge0bTags[iAna][iGen] = new TH1D( hName, "lep1lep2bb, t#bar{t} visible system, p_{T}, >=0 bTags;p_{T} [GeV]", 32, 0.0, 800.0 );
      
      // lep1lep2bb pT, ge1bTags
      hName = "h_lep1lep2bbPt__ge1bTags" + flav_gen_sys_name;
      h_lep1lep2bbPt_ge1bTags[iAna][iGen] = new TH1D( hName, "lep1lep2bb, t#bar{t} visible system, p_{T}, >=1 bTags;p_{T} [GeV]", 32, 0.0, 800.0 );

      // lep1lep2bb pT, ge2bTags
      hName = "h_lep1lep2bbPt__ge2bTags" + flav_gen_sys_name;
      h_lep1lep2bbPt_ge2bTags[iAna][iGen] = new TH1D( hName, "lep1lep2bb, t#bar{t} visible system, p_{T}, >=2 bTags;p_{T} [GeV]", 32, 0.0, 800.0 );

      
      // lep1lep2bbMet pT, ge0bTags
      hName = "h_lep1lep2bbMetPt__ge0bTags" + flav_gen_sys_name;
      h_lep1lep2bbMetPt_ge0bTags[iAna][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=0 bTags;p_{T} [GeV]", 32, 0.0, 800.0 );
      
      // lep1lep2bbMet pT, ge1bTags
      //hName = "h_lep1lep2bbMetPt__ge1bTags" + flav_gen_sys_name;
      //h_lep1lep2bbMetPt_ge1bTags[iAna][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=1 bTags;p_{T} [GeV]", 32, 0.0, 800.0 );

      // lep1lep2bbMet pT, ge2bTags
      hName = "h_lep1lep2bbMetPt__ge2bTags" + flav_gen_sys_name;
      h_lep1lep2bbMetPt_ge2bTags[iAna][iGen] = new TH1D( hName, "lep1lep2bbMet, t#bar{t} system, p_{T}, >=2 bTags;p_{T} [GeV]", 32, 0.0, 800.0 );

      
      // MT, ge0bTags
      hName = "h_mt__ge0bTags" + flav_gen_sys_name;
      h_mt_ge0bTags[iAna][iGen] = new TH1D( hName, "MT, >=0 bTags;M_{T} [GeV]", 32, 0.0, 800.0);

      // MT, ge1bTags
      hName = "h_mt__ge1bTags" + flav_gen_sys_name;
      h_mt_ge1bTags[iAna][iGen] = new TH1D( hName, "MT, >=1 bTags;M_{T} [GeV]", 32, 0.0, 800.0);

      // MT, ge2bTags
      hName = "h_mt__ge2bTags" + flav_gen_sys_name;
      h_mt_ge2bTags[iAna][iGen] = new TH1D( hName, "MT, >=2 bTags;M_{T} [GeV]", 32, 0.0, 800.0);


      // modified topness, ge0bTags
      hName = "h_modTopness__ge0bTags" + flav_gen_sys_name;
      h_modTopness_ge0bTags[iAna][iGen] = new TH1D( hName, "modified topness, >=0 bTags;pT [GeV]", 20, -20.0, 20.0);

      // modified topness, ge1bTags
      hName = "h_modTopness__ge1bTags" + flav_gen_sys_name;
      h_modTopness_ge1bTags[iAna][iGen] = new TH1D( hName, "modified topness, >=1 bTags;pT [GeV]", 20, -20.0, 20.0);

      // modified topness, ge2bTags
      hName = "h_modTopness__ge2bTags" + flav_gen_sys_name;
      h_modTopness_ge2bTags[iAna][iGen] = new TH1D( hName, "modified topness, >=2 bTags;pT [GeV]", 20, -20.0, 20.0);


      // MT2W, ge0bTags
      hName = "h_mt2w__ge0bTags" + flav_gen_sys_name;
      h_mt2w_ge0bTags[iAna][iGen] = new TH1D( hName, "MT2W, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // MT2W, ge1bTags
      hName = "h_mt2w__ge1bTags" + flav_gen_sys_name;
      h_mt2w_ge1bTags[iAna][iGen] = new TH1D( hName, "MT2W, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // MT2W, ge2bTags
      hName = "h_mt2w__ge2bTags" + flav_gen_sys_name;
      h_mt2w_ge2bTags[iAna][iGen] = new TH1D( hName, "MT2W, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


      // Mlb, ge0bTags
      hName = "h_mlb__ge0bTags" + flav_gen_sys_name;
      h_mlb_ge0bTags[iAna][iGen] = new TH1D( hName, "Mlb, >=0 bTags;pT [GeV]", 32, 0.0, 800.0);

      // Mlb, ge1bTags
      hName = "h_mlb__ge1bTags" + flav_gen_sys_name;
      h_mlb_ge1bTags[iAna][iGen] = new TH1D( hName, "Mlb, >=1 bTags;pT [GeV]", 32, 0.0, 800.0);

      // Mlb, ge2bTags
      hName = "h_mlb__ge2bTags" + flav_gen_sys_name;
      h_mlb_ge2bTags[iAna][iGen] = new TH1D( hName, "Mlb, >=2 bTags;pT [GeV]", 32, 0.0, 800.0);


    } // end loop over genClassifications for histogram arrays
  } // end loop over leptonFlavs (analyzers) for histogram arrays

        

  ////////////////////////////////
  //                            //
  // Trigger Efficiency Studies //
  //                            //
  ////////////////////////////////

  // OR of all diLepton triggers
  int nEvents_pass_diLepSel_and_metTrig = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_diLepTrig = 0;
  
  TH1D *h1_diLep_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_diLep_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_diLep_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_diLep_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_diLep_trigger_eff_num = NULL;
  TH2D *h2_diLep_trigger_eff_den = NULL;

  // MuE Triggers
  int nEvents_pass_diLepSel_and_singleElTrig = 0;
  int nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig = 0;
  int nEvents_pass_diLepSel_and_singleMuTrig = 0;
  int nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig = 0;
  int nEvents_pass_diLepSel_and_metTrig_emuEvents = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_emuTrig = 0;
  
  TH1D *h1_emu_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_emu_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_emu_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_emu_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_emu_trigger_eff_num = NULL;
  TH2D *h2_emu_trigger_eff_den = NULL;

  // DiEl Trigger
  int nEvents_pass_diLepSel_and_metTrig_diElEvents = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_diElTrig = 0;

  TH1D *h1_diEl_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_diEl_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_diEl_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_diEl_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_diEl_trigger_eff_num = NULL;
  TH2D *h2_diEl_trigger_eff_den = NULL;

  // DiMu Triggers
  int nEvents_pass_diLepSel_and_metTrig_diMuEvents = 0;
  int nEvents_pass_diLepSel_and_metTrig_and_diMuTrig = 0;
  
  TH1D *h1_diMu_trigger_eff_vs_lep1Pt_num = NULL;
  TH1D *h1_diMu_trigger_eff_vs_lep1Pt_den = NULL;
  TH1D *h1_diMu_trigger_eff_vs_lep2Pt_num = NULL;
  TH1D *h1_diMu_trigger_eff_vs_lep2Pt_den = NULL;
  TH2D *h2_diMu_trigger_eff_num = NULL;
  TH2D *h2_diMu_trigger_eff_den = NULL;

  if( sample.isData && sample.id==sampleInfo::k_met ){

    h1_diLep_trigger_eff_vs_lep1Pt_num = new TH1D( "h_diLep_trigger_eff_vs_lep1Pt_num", "ee/emu/mumu trigger efficiency vs leading lepton pT, numerator;diLep trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diLep_trigger_eff_vs_lep1Pt_den = new TH1D( "h_diLep_trigger_eff_vs_lep1Pt_den", "ee/emu/mumu trigger efficiency vs leading lepton pT, denominator;diLep trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    
    h1_diLep_trigger_eff_vs_lep2Pt_num = new TH1D( "h_diLep_trigger_eff_vs_lep2Pt_num", "ee/emu/mumu trigger efficiency vs trailing lepton pT, numerator;diLep trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_diLep_trigger_eff_vs_lep2Pt_den = new TH1D( "h_diLep_trigger_eff_vs_lep2Pt_den", "ee/emu/mumu trigger efficiency vs trailing lepton pT, denominator;diLep trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    
    h2_diLep_trigger_eff_num = new TH2D( "h_diLep_trigger_eff_num", "ee/emu/mumu trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_diLep_trigger_eff_den = new TH2D( "h_diLep_trigger_eff_den", "ee/emu/mumu trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );

    
    h1_emu_trigger_eff_vs_lep1Pt_num = new TH1D( "h_emu_trigger_eff_vs_lep1Pt_num", "emu trigger efficiency vs leading lepton pT, numerator;emu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_emu_trigger_eff_vs_lep1Pt_den = new TH1D( "h_emu_trigger_eff_vs_lep1Pt_den", "emu trigger efficiency vs leading lepton pT, denominator;emu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_emu_trigger_eff_vs_lep2Pt_num = new TH1D( "h_emu_trigger_eff_vs_lep2Pt_num", "emu trigger efficiency vs trailing lepton pT, numerator;emu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_emu_trigger_eff_vs_lep2Pt_den = new TH1D( "h_emu_trigger_eff_vs_lep2Pt_den", "emu trigger efficiency vs trailing lepton pT, denominator;emu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    h2_emu_trigger_eff_num = new TH2D( "h_emu_trigger_eff_num", "e/mu trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_emu_trigger_eff_den = new TH2D( "h_emu_trigger_eff_den", "e/mu trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
  
        
    h1_diEl_trigger_eff_vs_lep1Pt_num = new TH1D( "h_diEl_trigger_eff_vs_lep1Pt_num", "ee trigger efficiency vs leading lepton pT, numerator;diEl trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diEl_trigger_eff_vs_lep1Pt_den = new TH1D( "h_diEl_trigger_eff_vs_lep1Pt_den", "ee trigger efficiency vs leading lepton pT, denominator;diEl trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
  
    h1_diEl_trigger_eff_vs_lep2Pt_num = new TH1D( "h_diEl_trigger_eff_vs_lep2Pt_num", "ee trigger efficiency vs trailing lepton pT, numerator;diEl trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_diEl_trigger_eff_vs_lep2Pt_den = new TH1D( "h_diEl_trigger_eff_vs_lep2Pt_den", "ee trigger efficiency vs trailing lepton pT, denominator;diEl trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    h2_diEl_trigger_eff_num = new TH2D( "h_diEl_trigger_eff_num", "ee trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_diEl_trigger_eff_den = new TH2D( "h_diEl_trigger_eff_den", "ee trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
  
    
    h1_diMu_trigger_eff_vs_lep1Pt_num = new TH1D( "h_diMu_trigger_eff_vs_lep1Pt_num", "mumu trigger efficiency vs leading lepton pT, numerator;diMu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diMu_trigger_eff_vs_lep1Pt_den = new TH1D( "h_diMu_trigger_eff_vs_lep1Pt_den", "mumu trigger efficiency vs leading lepton pT, denominator;diMu trigger efficiency;lep1 pT", 20, 0.0, 200.0 );
    h1_diMu_trigger_eff_vs_lep2Pt_num = new TH1D( "h_diMu_trigger_eff_vs_lep2Pt_num", "mumu trigger efficiency vs trailing lepton pT, numerator;diMu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );
    h1_diMu_trigger_eff_vs_lep2Pt_den = new TH1D( "h_diMu_trigger_eff_vs_lep2Pt_den", "mumu trigger efficiency vs trailing lepton pT, denominator;diMu trigger efficiency;lep2 pT", 20, 0.0, 200.0 );    
    h2_diMu_trigger_eff_num = new TH2D( "h_diMu_trigger_eff_num", "mumu trigger efficiency, numerator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );
    h2_diMu_trigger_eff_den = new TH2D( "h_diMu_trigger_eff_den", "mumu trigger efficiency, denominator;lep2 pT;lep1 pT", 20, 0.0, 200.0, 20, 0.0, 200.0 );

  } // end if data for trigger efficiency histogram declarations


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

      // Pre-calculate all the event weights
      wgtInfo.getEventWeights();




      //
      // If the current sample is data, look at trigger efficiency before continuing with selections
      //

      if( sample.isData && sample.id==sampleInfo::k_met ) {

	      double wgt_nominal = sysInfo::GetEventWeight( sysInfo::k_nominal );

	      // Check if the event passes all selections (except skip the trigger selection)
	      std::vector<selectionInfo::cut> selections = selectionInfo::get_selection_CR2l_bulkTTbar();
	      bool pass_selection_noTrigger = true;
	      for( selectionInfo::cut thisCut : selections ) {
		      if( thisCut.first == "trigger" ) continue; // ignore diLepton trigger cut
		      if( !thisCut.second() ) {
			      pass_selection_noTrigger = false;
			      break;
		      }
	      }
	
	      // Check if event passes triggers
	      bool pass_trigger_singleEl = HLT_SingleEl();
	      bool pass_trigger_singleMu = HLT_SingleMu(); 
	      bool pass_trigger_met      = HLT_MET() || HLT_MET100_MHT100();
	      bool pass_trigger_emu      = HLT_MuE();
	      bool pass_trigger_diEl     = HLT_DiEl();
	      bool pass_trigger_diMu     = HLT_DiMu();
	      bool pass_trigger_diLep    = HLT_DiEl() || HLT_MuE() || HLT_DiMu();
	
	      // DiLep Triggers (OR'd of all 3), MET trigger method
	      if( pass_selection_noTrigger && pass_trigger_met ) {
		      h1_diLep_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
		      h1_diLep_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
		      h2_diLep_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
		      nEvents_pass_diLepSel_and_metTrig++;
		      if( pass_trigger_diLep ) {
			      nEvents_pass_diLepSel_and_metTrig_and_diLepTrig++;
			      h1_diLep_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
			      h1_diLep_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
			      h2_diLep_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
		      }
	      }

	      // E/Mu Triggers
	      if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==24 ){

		      // E/mu Trigger, SingleLep factorized method, Test trailing electron leg
		      if( pass_selection_noTrigger && pass_trigger_singleEl && abs(lep1_pdgid())==11 ){
			      nEvents_pass_diLepSel_and_singleElTrig++;
			      if( pass_trigger_emu ){
				      nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig++;
			      }
		      }

		      // E/mu Trigger, SingleLep factorized method, Test trailing muon leg
		      if( pass_selection_noTrigger && pass_trigger_singleMu && abs(lep1_pdgid())==13 ){
			      nEvents_pass_diLepSel_and_singleMuTrig++;
			      if( pass_trigger_diLep ){
				      nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig++;
			      }
		      }

		      // E/mu Trigger, MET Trigger method
		      if( pass_selection_noTrigger && pass_trigger_met ){
			      nEvents_pass_diLepSel_and_metTrig_emuEvents++;
			      h1_emu_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
			      h1_emu_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
			      h2_emu_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
			      if( pass_trigger_emu ){
				      nEvents_pass_diLepSel_and_metTrig_and_emuTrig++;
				      h1_emu_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
				      h1_emu_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
				      h2_emu_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
			      }
		      }

	      } // end if e/mu

	
	      // DiEl Triggers, MET Trigger method
	      if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==22 ){
		      if( pass_selection_noTrigger && pass_trigger_met ){
			      nEvents_pass_diLepSel_and_metTrig_diElEvents++;
			      h1_diEl_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
			      h1_diEl_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
			      h2_diEl_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
			      if( pass_trigger_diEl ){
				      nEvents_pass_diLepSel_and_metTrig_and_diElTrig++;
				      h1_diEl_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
				      h1_diEl_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
				      h2_diEl_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
			      }
		      }
	      } // end if elel


	      // DiMu Triggers, MET Trigger method
	      if( (abs(lep1_pdgid())+abs(lep2_pdgid()))==26 ){
		      if( pass_selection_noTrigger && pass_trigger_met ){
			      nEvents_pass_diLepSel_and_metTrig_diMuEvents++;
			      h1_diMu_trigger_eff_vs_lep1Pt_den->Fill( lep1_p4().Pt(), wgt_nominal );
			      h1_diMu_trigger_eff_vs_lep2Pt_den->Fill( lep2_p4().Pt(), wgt_nominal );
			      h2_diMu_trigger_eff_den->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
			      if( pass_trigger_diMu ){
				      nEvents_pass_diLepSel_and_metTrig_and_diMuTrig++;
				      h1_diMu_trigger_eff_vs_lep1Pt_num->Fill( lep1_p4().Pt(), wgt_nominal );
				      h1_diMu_trigger_eff_vs_lep2Pt_num->Fill( lep2_p4().Pt(), wgt_nominal );
				      h2_diMu_trigger_eff_num->Fill( lep2_p4().Pt(), lep1_p4().Pt(), wgt_nominal );
			      }
		      }
	      } // end if mumu


      } // end if sample is data





      /////////////////////////////
      //                         //
      // Compute Event Variables //
      //                         //
      /////////////////////////////


      // lep1 lep2 b b TLV
      LorentzVector deepcsvJet1_TLV(0.0,0.0,0.0,0.0);
      double deepcsvJet1_pt = -99.9;

      LorentzVector deepcsvJet2_TLV(0.0,0.0,0.0,0.0);
      double deepcsvJet2_pt = -99.9;

      LorentzVector lep1lep2bb_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bb_pt = -99.9;

      LorentzVector lep1lep2bbMet_TLV(0.0,0.0,0.0,0.0);
      double lep1lep2bbMet_pt = -99.9;

      LorentzVector lep1lep2bbMet_TLV_jup(0.0,0.0,0.0,0.0);
      //double lep1lep2bbMet_pt_jup = -99.9;

      LorentzVector lep1lep2bbMet_TLV_jdown(0.0,0.0,0.0,0.0);
      //double lep1lep2bbMet_pt_jdown = -99.9;

      lep1lep2bb_TLV += lep1_p4();
      lep1lep2bb_TLV += lep2_p4();

      lep1lep2bbMet_TLV_jup = lep1lep2bb_TLV;
      lep1lep2bbMet_TLV_jdown = lep1lep2bb_TLV;


      // Nominal
      int jet1_idx = -1;
      int jet2_idx = -1;
      double max_deepcsv = -99.9;
      double second_deepcsv = -99.9;
      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
	      if( ak4pfjets_deepCSV().at(iJet) > max_deepcsv ){
		      jet1_idx = iJet;
		      max_deepcsv  = ak4pfjets_deepCSV().at(iJet);
	      }
      }
      for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
	      if( iJet==jet1_idx ) continue;
	      if( ak4pfjets_deepCSV().at(iJet) > second_deepcsv ){
		      jet2_idx = iJet;
		      second_deepcsv = ak4pfjets_deepCSV().at(iJet);
	      } 
      }
      if(jet1_idx>=0){
	      lep1lep2bb_TLV += ak4pfjets_p4().at(jet1_idx);
	      deepcsvJet1_TLV += ak4pfjets_p4().at(jet1_idx);
	      deepcsvJet1_pt = deepcsvJet1_TLV.Pt();
      }
      if(jet2_idx>=0){
	      lep1lep2bb_TLV += ak4pfjets_p4().at(jet2_idx);
	      deepcsvJet2_TLV += ak4pfjets_p4().at(jet2_idx);
	      deepcsvJet2_pt = deepcsvJet2_TLV.Pt();
      }

      lep1lep2bb_pt = lep1lep2bb_TLV.Pt();

      // lep1 lep2 b b MET TLV
      lep1lep2bbMet_TLV = lep1lep2bb_TLV;

      LorentzVector met_TLV( pfmet()*cos(pfmet_phi()), pfmet()*sin(pfmet_phi()), 0.0, pfmet() );
      lep1lep2bbMet_TLV += met_TLV;

      lep1lep2bbMet_pt = lep1lep2bbMet_TLV.Pt();


      // lep1 lep2 bb MET TLV JEC Up
      jet1_idx = -1;
      jet2_idx = -1;
      max_deepcsv = -99.9;
      second_deepcsv = -99.9;
      for(int iJet=0; iJet<(int)jup_ak4pfjets_p4().size(); iJet++){
	      if( jup_ak4pfjets_deepCSV().at(iJet) > max_deepcsv ){
		      jet1_idx = iJet;
		      max_deepcsv  = jup_ak4pfjets_deepCSV().at(iJet);
	      }
      }
      for(int iJet=0; iJet<(int)jup_ak4pfjets_p4().size(); iJet++){
	      if( iJet==jet1_idx ) continue;
	      else if( jup_ak4pfjets_deepCSV().at(iJet) > second_deepcsv ){
		      jet2_idx = iJet;
		      second_deepcsv  = jup_ak4pfjets_deepCSV().at(iJet);
	      } 
      }
      if(jet1_idx>=0) lep1lep2bbMet_TLV_jup += jup_ak4pfjets_p4().at(jet1_idx);
      if(jet2_idx>=0) lep1lep2bbMet_TLV_jup += jup_ak4pfjets_p4().at(jet2_idx);

      LorentzVector met_TLV_jup( pfmet_jup()*cos(pfmet_phi_jup()), pfmet_jup()*sin(pfmet_phi_jup()), 0.0, pfmet_jup() );
      lep1lep2bbMet_TLV_jup += met_TLV_jup;

      // lep1 lep2 bb MET TLV JEC Down
      jet1_idx = -1;
      jet2_idx = -1;
      max_deepcsv = -99.9;
      second_deepcsv = -99.9;
      for(int iJet=0; iJet<(int)jdown_ak4pfjets_p4().size(); iJet++){
	      if( jdown_ak4pfjets_deepCSV().at(iJet) > max_deepcsv ){
		      jet1_idx = iJet;
		      max_deepcsv  = jdown_ak4pfjets_deepCSV().at(iJet);
	      }
      }
      for(int iJet=0; iJet<(int)jdown_ak4pfjets_p4().size(); iJet++){
	      if( iJet==jet1_idx ) continue;
	      if( jdown_ak4pfjets_deepCSV().at(iJet) > second_deepcsv ){
		      jet2_idx = iJet;
		      second_deepcsv  = jdown_ak4pfjets_deepCSV().at(iJet);
	      } 
      }
      if(jet1_idx>=0) lep1lep2bbMet_TLV_jdown += jdown_ak4pfjets_p4().at(jet1_idx);
      if(jet2_idx>=0) lep1lep2bbMet_TLV_jdown += jdown_ak4pfjets_p4().at(jet2_idx);

      LorentzVector met_TLV_jdown( pfmet_jdown()*cos(pfmet_phi_jdown()), pfmet_jdown()*sin(pfmet_phi_jdown()), 0.0, pfmet_jdown() );
      lep1lep2bbMet_TLV_jdown += met_TLV_jdown;




			/////////////////////////////////////////////////////////////
			//                                                         //
			// Loop over all analyzers, genClassy's, systematics, etc. //
			//                                                         //
			/////////////////////////////////////////////////////////////

			// Loop over all analyzers
			for( int iAna=0; iAna<nAnalyzers; iAna++ ) {
				analyzer* thisAnalyzer = analyzers.at(iAna);


				// Make an array of which genClassies this event passes
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
				for( int iSys=0; iSys < nSystematics; iSys++ ) {
					sysInfo::Util thisSystematic = systematicList.at(iSys);

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
						int histIndex = iGen*nSystematics + iSys;

						// Fill yield histograms
						for( int category : categories_passed ) {
							thisAnalyzer->GetYieldHistogram( histIndex )->Fill( category, weight );
						}

						/////////////////////////////////////
						//                                 //
						// Fill other non-yield histograms //
						//                                 //
						/////////////////////////////////////


						// Histo Index
						int iHisto = iAna*nGenClassy*nSystematics + iGen*nSystematics + iSys;

						bool add2ndLepToMet = thisAnalyzer->GetAdd2ndLep();

						double met = pfmet();
						if(add2ndLepToMet_) met = pfmet_rl();

						double mt = mt_met_lep();
						if(add2ndLepToMet_) mt = mt_met_lep_rl();

						double tMod = topnessMod();
						if(add2ndLepToMet_) tMod = topnessMod_rl();

						double mt2w = MT2W();
						if(add2ndLepToMet_) mt2w = MT2W_rl();
	      

						// Systematic variations for variables
						if(systematicList[iSys].id==sysInfo::k_JESUp){
							if(add2ndLepToMet) met = pfmet_rl_jup();
							else               met = pfmet_jup();
						}
						else if(systematicList[iSys].id==sysInfo::k_JESDown){
							if(add2ndLepToMet) met = pfmet_rl_jdown();
							else               met = pfmet_jdown();
						}
						else{
							if(add2ndLepToMet) met = pfmet_rl();
							else               met = pfmet();
						}

	      // met
	      if(systematicList[iSys].id==sysInfo::k_JESUp){
		if( jup_ngoodbtags()>=1 ){
		  h_met_ge1bTags[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>50)  h_met_ge1bTags_ge50ttbarSysPt[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>100) h_met_ge1bTags_ge100ttbarSysPt[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>150) h_met_ge1bTags_ge150ttbarSysPt[iHisto]->Fill( met, weight );
		}
	      }
	      else if(systematicList[iSys].id==sysInfo::k_JESDown){
		if( jdown_ngoodbtags()>=1 ){
		  h_met_ge1bTags[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>50)  h_met_ge1bTags_ge50ttbarSysPt[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>100) h_met_ge1bTags_ge100ttbarSysPt[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>150) h_met_ge1bTags_ge150ttbarSysPt[iHisto]->Fill( met, weight );
		}
	      }
	      else{
		if( ngoodbtags()>=1 ){
		  h_met_ge1bTags[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>50)  h_met_ge1bTags_ge50ttbarSysPt[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>100) h_met_ge1bTags_ge100ttbarSysPt[iHisto]->Fill( met, weight );
		  if(lep1lep2bbMet_pt>150) h_met_ge1bTags_ge150ttbarSysPt[iHisto]->Fill( met, weight );
		}
	      }

	      
	      // diLepPt
	      if(systematicList[iSys].id==sysInfo::k_JESUp){
		if( jup_ngoodbtags()>=1 ){
		  h_diLepPt_ge1bTags[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		  if(met>100) h_diLepPt_ge1bTags_ge100met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		  if(met>150) h_diLepPt_ge1bTags_ge150met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		}
	      }
	      else if(systematicList[iSys].id==sysInfo::k_JESDown){
		if( jdown_ngoodbtags()>=1 ){
		  h_diLepPt_ge1bTags[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		  if(met>100) h_diLepPt_ge1bTags_ge100met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		  if(met>150) h_diLepPt_ge1bTags_ge150met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		}
	      }
	      else{
		if( ngoodbtags()>=1 ){
		  h_diLepPt_ge1bTags[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		  if(met>100) h_diLepPt_ge1bTags_ge100met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		  if(met>150) h_diLepPt_ge1bTags_ge150met[iHisto]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
		}
	      }


	      // lep1lep2bbMet
	      if(systematicList[iSys].id==sysInfo::k_JESUp){
		if( jup_ngoodbtags()>=1 ){
		  h_lep1lep2bbMetPt_ge1bTags[iHisto]->Fill( lep1lep2bbMet_TLV_jup.Pt(), weight );
		  if(met>100) h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto]->Fill( lep1lep2bbMet_TLV_jup.Pt(), weight );
		  if(met>150) h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto]->Fill( lep1lep2bbMet_TLV_jup.Pt(), weight );
		  if(nvtxs()>=0.0 && nvtxs()<12.0)  h_lep1lep2bbMetPt_ge1bTags_0to12nVtx[iHisto]->Fill( lep1lep2bbMet_TLV_jup.Pt(), weight );
		  if(nvtxs()>=12.0 && nvtxs()<24.0) h_lep1lep2bbMetPt_ge1bTags_12to24nVtx[iHisto]->Fill( lep1lep2bbMet_TLV_jup.Pt(), weight );
		  if(nvtxs()>=24.0)                 h_lep1lep2bbMetPt_ge1bTags_ge24nVtx[iHisto]->Fill( lep1lep2bbMet_TLV_jup.Pt(), weight );
		}
	      }
	      else if(systematicList[iSys].id==sysInfo::k_JESDown){
		if( jdown_ngoodbtags()>=1 ){
		  h_lep1lep2bbMetPt_ge1bTags[iHisto]->Fill( lep1lep2bbMet_TLV_jdown.Pt(), weight );
		  if(met>100) h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto]->Fill( lep1lep2bbMet_TLV_jdown.Pt(), weight );
		  if(met>150) h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto]->Fill( lep1lep2bbMet_TLV_jdown.Pt(), weight );
		  if(nvtxs()>=0.0 && nvtxs()<12.0)  h_lep1lep2bbMetPt_ge1bTags_0to12nVtx[iHisto]->Fill( lep1lep2bbMet_TLV_jdown.Pt(), weight );
		  if(nvtxs()>=12.0 && nvtxs()<24.0) h_lep1lep2bbMetPt_ge1bTags_12to24nVtx[iHisto]->Fill( lep1lep2bbMet_TLV_jdown.Pt(), weight );
		  if(nvtxs()>=24.0)                 h_lep1lep2bbMetPt_ge1bTags_ge24nVtx[iHisto]->Fill( lep1lep2bbMet_TLV_jdown.Pt(), weight );
		}
	      }
	      else{
		if( ngoodbtags()>=1 ){
		  h_lep1lep2bbMetPt_ge1bTags[iHisto]->Fill( lep1lep2bbMet_pt, weight );
		  if(met>100) h_lep1lep2bbMetPt_ge1bTags_ge100met[iHisto]->Fill( lep1lep2bbMet_pt, weight );
		  if(met>150) h_lep1lep2bbMetPt_ge1bTags_ge150met[iHisto]->Fill( lep1lep2bbMet_pt, weight );
		  if(nvtxs()>=0.0 && nvtxs()<12.0)  h_lep1lep2bbMetPt_ge1bTags_0to12nVtx[iHisto]->Fill( lep1lep2bbMet_pt, weight );
		  if(nvtxs()>=12.0 && nvtxs()<24.0) h_lep1lep2bbMetPt_ge1bTags_12to24nVtx[iHisto]->Fill( lep1lep2bbMet_pt, weight );
		  if(nvtxs()>=24.0)                 h_lep1lep2bbMetPt_ge1bTags_ge24nVtx[iHisto]->Fill( lep1lep2bbMet_pt, weight );
		}
	      }


	      // These histograms only get filled for the nominal systematic
	      if( thisSystematic.id == sysInfo::k_nominal ) {

		      double weight_noPU = weight / wgtInfo.sf_pu;


							// nVtx
							h_nVtx[iAna][iGen]->Fill( nvtxs(), weight );
	      
							// nVtx, no pileup weight
							if( sample.isData ) h_nVtx_noPUwgt[iAna][iGen]->Fill( nvtxs(), weight );
							else                h_nVtx_noPUwgt[iAna][iGen]->Fill( nvtxs(), weight_noPU );

							// nTruVtx
							if( !sample.isData ) h_nTrueVtx[iAna][iGen]->Fill( pu_ntrue(), weight );

							// nBTags
							h_nBTags[iAna][iGen]->Fill( ngoodbtags(), weight );

							// nJets
							if( ngoodbtags()>=0 ) h_nJets_ge0bTags[iAna][iGen]->Fill( ngoodjets(), weight );
							if( ngoodbtags()>=1 ) h_nJets_ge1bTags[iAna][iGen]->Fill( ngoodjets(), weight );
							if( ngoodbtags()>=2 ) h_nJets_ge2bTags[iAna][iGen]->Fill( ngoodjets(), weight );

							// nISRJets
							if(!sample.isData){
								if( ngoodbtags()>=0 ) h_nISRJets_ge0bTags[iAna][iGen]->Fill( NISRjets(), weight );
								if( ngoodbtags()>=1 ) h_nISRJets_ge1bTags[iAna][iGen]->Fill( NISRjets(), weight );
								if( ngoodbtags()>=2 ) h_nISRJets_ge2bTags[iAna][iGen]->Fill( NISRjets(), weight );
							}

							// lep1 pT
							if( ngoodbtags()>=0 ) h_lep1Pt_ge0bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
							if( ngoodbtags()>=1 ) h_lep1Pt_ge1bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
							if( ngoodbtags()>=2 ) h_lep1Pt_ge2bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );

							// lep2 pT
							if( ngoodbtags()>=0 ) h_lep2Pt_ge0bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
							if( ngoodbtags()>=1 ) h_lep2Pt_ge1bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
							if( ngoodbtags()>=2 ) h_lep2Pt_ge2bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );

							// el pT
							if( abs(lep1_pdgid())==11){
								if( ngoodbtags()>=0 ) h_elPt_ge0bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
								if( ngoodbtags()>=1 ) h_elPt_ge1bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
								if( ngoodbtags()>=2 ) h_elPt_ge2bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
							}
							if( abs(lep2_pdgid())==11){
								if( ngoodbtags()>=0 ) h_elPt_ge0bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
								if( ngoodbtags()>=1 ) h_elPt_ge1bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
								if( ngoodbtags()>=2 ) h_elPt_ge2bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
							}

							// mu pT
							if( abs(lep1_pdgid())==13){
								if( ngoodbtags()>=0 ) h_muPt_ge0bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
								if( ngoodbtags()>=1 ) h_muPt_ge1bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
								if( ngoodbtags()>=2 ) h_muPt_ge2bTags[iAna][iGen]->Fill( lep1_p4().Pt(), weight );
							}
							if( abs(lep2_pdgid())==13){
								if( ngoodbtags()>=0 ) h_muPt_ge0bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
								if( ngoodbtags()>=1 ) h_muPt_ge1bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
								if( ngoodbtags()>=2 ) h_muPt_ge2bTags[iAna][iGen]->Fill( lep2_p4().Pt(), weight );
							}

							// diLep pT
							if( ngoodbtags()>=0 ) h_diLepPt_ge0bTags[iAna][iGen]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
							//if( ngoodbtags()>=1 ) h_diLepPt_ge1bTags[iAna][iGen]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );
							if( ngoodbtags()>=2 ) h_diLepPt_ge2bTags[iAna][iGen]->Fill( (lep1_p4()+lep2_p4()).Pt(), weight );

							// jet pT
							for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
								if( ngoodbtags()>=0 ) h_jetPt_ge0bTags[iAna][iGen]->Fill( ak4pfjets_p4()[iJet].Pt(), weight );
								if( ngoodbtags()>=1 ) h_jetPt_ge1bTags[iAna][iGen]->Fill( ak4pfjets_p4()[iJet].Pt(), weight );
								if( ngoodbtags()>=2 ) h_jetPt_ge2bTags[iAna][iGen]->Fill( ak4pfjets_p4()[iJet].Pt(), weight );
							}

							// jet1 pt
							if( ngoodbtags()>=0 ) h_jet1Pt_ge0bTags[iAna][iGen]->Fill( ak4pfjets_p4()[0].Pt(), weight );
							if( ngoodbtags()>=1 ) h_jet1Pt_ge1bTags[iAna][iGen]->Fill( ak4pfjets_p4()[0].Pt(), weight );
							if( ngoodbtags()>=2 ) h_jet1Pt_ge2bTags[iAna][iGen]->Fill( ak4pfjets_p4()[0].Pt(), weight );

							// jet 2 pt
							if( ngoodbtags()>=0 ) h_jet2Pt_ge0bTags[iAna][iGen]->Fill( ak4pfjets_p4()[1].Pt(), weight );
							if( ngoodbtags()>=1 ) h_jet2Pt_ge1bTags[iAna][iGen]->Fill( ak4pfjets_p4()[1].Pt(), weight );
							if( ngoodbtags()>=2 ) h_jet2Pt_ge2bTags[iAna][iGen]->Fill( ak4pfjets_p4()[1].Pt(), weight );

							// DeepCSVJet1 pt
							if( ngoodbtags()>=0 ) h_deepcsvJet1Pt_ge0bTags[iAna][iGen]->Fill( deepcsvJet1_pt, weight );
							if( ngoodbtags()>=1 ) h_deepcsvJet1Pt_ge1bTags[iAna][iGen]->Fill( deepcsvJet1_pt, weight );
							if( ngoodbtags()>=2 ) h_deepcsvJet1Pt_ge2bTags[iAna][iGen]->Fill( deepcsvJet1_pt, weight );

							// DeepCSVJet 2 pt
							if( ngoodbtags()>=0 ) h_deepcsvJet2Pt_ge0bTags[iAna][iGen]->Fill( deepcsvJet2_pt, weight );
							if( ngoodbtags()>=1 ) h_deepcsvJet2Pt_ge1bTags[iAna][iGen]->Fill( deepcsvJet2_pt, weight );
							if( ngoodbtags()>=2 ) h_deepcsvJet2Pt_ge2bTags[iAna][iGen]->Fill( deepcsvJet2_pt, weight );

							// met
							if( ngoodbtags()>=0 ) h_met_ge0bTags[iAna][iGen]->Fill( met, weight );
							//if( ngoodbtags()>=1 ) h_met_ge1bTags[iAna][iGen]->Fill( met, weight );
							if( ngoodbtags()>=2 ) h_met_ge2bTags[iAna][iGen]->Fill( met, weight );


							// lep1lep2bb pT
							if( ngoodbtags()>=0 ) h_lep1lep2bbPt_ge0bTags[iAna][iGen]->Fill( lep1lep2bb_pt, weight );
							if( ngoodbtags()>=1 ) h_lep1lep2bbPt_ge1bTags[iAna][iGen]->Fill( lep1lep2bb_pt, weight );
							if( ngoodbtags()>=2 ) h_lep1lep2bbPt_ge2bTags[iAna][iGen]->Fill( lep1lep2bb_pt, weight );


							// lep1lep2bbMet pT
							if( ngoodbtags()>=0 ) h_lep1lep2bbMetPt_ge0bTags[iAna][iGen]->Fill( lep1lep2bbMet_pt, weight );
							//if( ngoodbtags()>=1 ) h_lep1lep2bbMetPt_ge1bTags[iAna][iGen]->Fill( lep1lep2bbMet_pt, weight );
							if( ngoodbtags()>=2 ) h_lep1lep2bbMetPt_ge2bTags[iAna][iGen]->Fill( lep1lep2bbMet_pt, weight );


							// mt
							if( ngoodbtags()>=0 ) h_mt_ge0bTags[iAna][iGen]->Fill( mt, weight );
							if( ngoodbtags()>=1 ) h_mt_ge1bTags[iAna][iGen]->Fill( mt, weight );
							if( ngoodbtags()>=2 ) h_mt_ge2bTags[iAna][iGen]->Fill( mt, weight );


							// modified topness
							if( ngoodbtags()>=0 ) h_modTopness_ge0bTags[iAna][iGen]->Fill( tMod, weight );
							if( ngoodbtags()>=1 ) h_modTopness_ge1bTags[iAna][iGen]->Fill( tMod, weight );
							if( ngoodbtags()>=2 ) h_modTopness_ge2bTags[iAna][iGen]->Fill( tMod, weight );


							// mt2w
							if( ngoodbtags()>=0 ) h_mt2w_ge0bTags[iAna][iGen]->Fill( mt2w, weight );
							if( ngoodbtags()>=1 ) h_mt2w_ge1bTags[iAna][iGen]->Fill( mt2w, weight );
							if( ngoodbtags()>=2 ) h_mt2w_ge2bTags[iAna][iGen]->Fill( mt2w, weight );


							// mlb
							if( ngoodbtags()>=0 ) h_mlb_ge0bTags[iAna][iGen]->Fill( Mlb_closestb(), weight );
							if( ngoodbtags()>=1 ) h_mlb_ge1bTags[iAna][iGen]->Fill( Mlb_closestb(), weight );
							if( ngoodbtags()>=2 ) h_mlb_ge2bTags[iAna][iGen]->Fill( Mlb_closestb(), weight );



						} // End filling non-yield nominal-only histograms


					} // End loop over genClassy's

				} // End loop over systematics

			} // End loop over analyzers

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
  // Trigger Efficiency Printouts
  //
  if( sample.isData && sample.id==sampleInfo::k_met ){
    
    cout << "  Trigger Efficiency Results: " << endl;

    double trigger_eff_diLep = (double)nEvents_pass_diLepSel_and_metTrig_and_diLepTrig/(double)nEvents_pass_diLepSel_and_metTrig;
    double trigger_eff_diLep_err = sqrt( (trigger_eff_diLep*(1-trigger_eff_diLep))/(double)nEvents_pass_diLepSel_and_metTrig );
    cout << "    OR of all diLep Triggers, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_diLepTrig << " / " << nEvents_pass_diLepSel_and_metTrig << " ) = " << trigger_eff_diLep << " +/- " << trigger_eff_diLep_err << endl;
    

    double trigger_eff_diEl = (double)nEvents_pass_diLepSel_and_metTrig_and_diElTrig/(double)nEvents_pass_diLepSel_and_metTrig_diElEvents;
    double trigger_eff_diEl_err = sqrt( (trigger_eff_diEl*(1-trigger_eff_diEl))/(double)nEvents_pass_diLepSel_and_metTrig_diElEvents );
    cout << "    diEl Trigger, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_diElTrig << " / " << nEvents_pass_diLepSel_and_metTrig_diElEvents << " ) = " << trigger_eff_diEl << " +/- " << trigger_eff_diEl_err << endl;
    

    double trigger_eff_diMu = (double)nEvents_pass_diLepSel_and_metTrig_and_diMuTrig/(double)nEvents_pass_diLepSel_and_metTrig_diMuEvents;
    double trigger_eff_diMu_err = sqrt( (trigger_eff_diMu*(1-trigger_eff_diMu))/(double)nEvents_pass_diLepSel_and_metTrig_diMuEvents );
    cout << "    diMu Trigger, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_diMuTrig << " / " << nEvents_pass_diLepSel_and_metTrig_diMuEvents << " ) = " << trigger_eff_diMu << " +/- " << trigger_eff_diMu_err << endl;
  

    double trigger_eff_emu = (double)nEvents_pass_diLepSel_and_metTrig_and_emuTrig/(double)nEvents_pass_diLepSel_and_metTrig_emuEvents;
    double trigger_eff_emu_err = sqrt( (trigger_eff_emu*(1-trigger_eff_emu))/(double)nEvents_pass_diLepSel_and_metTrig_emuEvents );
    cout << "    e/mu Trigger, using MET monitoring trigger " << endl;
    cout << "        Efficiency = (" << nEvents_pass_diLepSel_and_metTrig_and_emuTrig << " / " << nEvents_pass_diLepSel_and_metTrig_emuEvents << " ) = " << trigger_eff_emu << " +/- " << trigger_eff_emu_err << endl;
  

    double trigger_eff_emu_trailingLep_el = (double)nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig/(double)nEvents_pass_diLepSel_and_singleElTrig;
    double trigger_eff_emu_trailingLep_el_err = sqrt( (trigger_eff_emu_trailingLep_el*(1-trigger_eff_emu_trailingLep_el))/(double)nEvents_pass_diLepSel_and_singleElTrig );
    cout << "    e/mu Trigger, using SingleLep monitoring triggers " << endl;
    cout << "        Trailing Mu Leg Efficiency, using singleEl triggers = " << "( " << (double)nEvents_pass_diLepSel_and_singleElTrig_and_emuTrig << " / " << (double)nEvents_pass_diLepSel_and_singleElTrig << " ) = " << trigger_eff_emu_trailingLep_el << " +/- " << trigger_eff_emu_trailingLep_el_err << endl;

    
    double trigger_eff_emu_trailingLep_mu = (double)nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig/(double)nEvents_pass_diLepSel_and_singleMuTrig;
    double trigger_eff_emu_trailingLep_mu_err = sqrt( (trigger_eff_emu_trailingLep_mu*(1-trigger_eff_emu_trailingLep_mu))/(double)nEvents_pass_diLepSel_and_singleMuTrig );
    cout << "        Trailing El Leg Efficiency, using singleMu triggers = " << "( " << (double)nEvents_pass_diLepSel_and_singleMuTrig_and_emuTrig << " / " << (double)nEvents_pass_diLepSel_and_singleMuTrig << " ) = " << trigger_eff_emu_trailingLep_mu << " +/- " << trigger_eff_emu_trailingLep_mu_err << endl;

    double trigger_eff_emu_singleLepMethod = trigger_eff_emu_trailingLep_mu*trigger_eff_emu_trailingLep_el;
    double trigger_eff_emu_singleLepMethod_err = trigger_eff_emu_singleLepMethod*sqrt( pow(trigger_eff_emu_trailingLep_mu_err/trigger_eff_emu_trailingLep_mu,2) + pow(trigger_eff_emu_trailingLep_el_err/trigger_eff_emu_trailingLep_el,2) );
    cout << "        Factorized Trigger Efficiency = (" << trigger_eff_emu_trailingLep_mu << " * " << trigger_eff_emu_trailingLep_el << " ) = " << trigger_eff_emu_singleLepMethod << " +/- " << trigger_eff_emu_singleLepMethod_err << endl;
 
    cout << "====================================================" << endl;
  }


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
    


  //
  // Return!
  //
  return 0;

}

