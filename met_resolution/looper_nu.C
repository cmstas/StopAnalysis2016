#include "met-resolution.h"

//////////////////////////////
//                          //
// Configuration Parameters //
//                          //
//////////////////////////////

// bool analyzeFast_ = false;

bool applyjson = true;

// bool add2ndLepToMet_ = true;
// bool inclTaus_CR2l_  = false;

// bool useBTagSFs_fromFiles_ = true;
// bool useLepSFs_fromFiles_  = true;

// bool apply_cr2lTrigger_sf_  = true; // only !=1 if pfmet!=pfmet_rl ie no weight for ==1lepton events in SR and CR0b
// bool apply_bTag_sf_         = true; // event weight, product of all jet wgts
// bool apply_lep_sf_          = true; // both lep1 and lep2 (if available) are multiplied together
// bool apply_vetoLep_sf_      = true; // this is actually the lost lepton sf, only !=1 if there is >=2 genLeptons and ==1 recoLeptons in the event
// bool apply_tau_sf_          = true;
// bool apply_lepFS_sf_        = false;
// bool apply_topPt_sf_        = false; // true=sf, false=uncertainty
// bool apply_metRes_sf_       = true;
// bool apply_metTTbar_sf_     = true;
// bool apply_ttbarSysPt_sf_   = false;  // true=sf, false=uncertainty, only !=1.0 for madgraph tt2l, tW2l
// bool apply_ISR_sf_          = true; // only !=1.0 for signal
// bool apply_pu_sf_           = true;
// bool apply_sample_sf_       = true; // only !=1.0 for some WJetsHT samps


//
// Main
//
int looper_nu() {

	// Use sumw2 for all histograms
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	TH3::SetDefaultSumw2();


  // 
  // SampleList
  //
  sampleInfo::vect_id sampleList;
  sampleList = sampleInfo::getSampleList_nuPt();  /// Need to create a new sampleList in stopCORE and use it here


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
	analyzer nupt_bulk(     "nupt_bulk" );
	analyzer nupt_corridor( "nupt_corridor" );

	std::vector<analyzer*> analyzer_list = {&nupt_bulk, &nupt_corridor};

	// Set the attributes for each analyzer

	// Set selections, categories, and genClassies for the analyzers
	nupt_bulk.AddSelections(     selectionInfo::get_selection_nupt() );
	nupt_corridor.AddSelections( selectionInfo::get_selection_nupt_corridor() );

	nupt_bulk.AddCategories(     categoryInfo::passCategory_nuPt_bulk);
	nupt_corridor.AddCategories( categoryInfo::passCategory_nuPt_corridor);

	for( int i=0; i<genClassyInfo::k_nGenClassy; i++ ) {
		nupt_bulk.AddGenClassification(     genClassyInfo::Util(genClassyInfo::ID(i)) );
		nupt_corridor.AddGenClassification( genClassyInfo::Util(genClassyInfo::ID(i)) );
	}

	TH1D* h_template = categoryInfo::getYieldHistoTemplate_nuPt();
	nupt_bulk.SetYieldTemplate( h_template );
	nupt_corridor.SetYieldTemplate( h_template );


  //
  // Loop over samples
  //
  for( int iSample=0; iSample<(int)sampleList.size(); iSample++) {

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

  // bool sampleIsTTbar = false;
  // if( sample.id == sampleInfo::k_ttbar_powheg_pythia8 ||
  //     sample.id == sampleInfo::k_ttbar_powheg_pythia8_ext4 ||
  //     sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8 ||
  //     sample.id == sampleInfo::k_ttbar_singleLeptFromT_madgraph_pythia8_ext1 ||
  //     sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8 ||
  //     sample.id == sampleInfo::k_ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 ||
  //     sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8 ||
  //     sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ) {
  //   sampleIsTTbar = true;
  // }
  
  //
  // Input chain
  //
  TChain *chain = new TChain("t");
  
  cout << "    Processing the following: " << endl;  
  for(int iFile=0; iFile<(int)sample.inputBabies.size(); iFile++) {
    
    // input directory
    string input = "/nfs-7/userdata/haweber/tupler_babies/merged/Stop_1l/v21/output/";
      
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
  // cout << "    Loading eventWeight Utilities..." << endl << endl;
  // wgtInfo.setUp( sample.id, useBTagSFs_fromFiles_, useLepSFs_fromFiles_, add2ndLepToMet_ );  
  // wgtInfo.apply_cr2lTrigger_sf  = (apply_cr2lTrigger_sf_ && add2ndLepToMet_);
  // wgtInfo.apply_bTag_sf         = apply_bTag_sf_;
  // wgtInfo.apply_lep_sf          = apply_lep_sf_;
  // wgtInfo.apply_vetoLep_sf      = apply_vetoLep_sf_;
  // wgtInfo.apply_tau_sf          = apply_tau_sf_;
  // wgtInfo.apply_lepFS_sf        = apply_lepFS_sf_;
  // wgtInfo.apply_topPt_sf        = apply_topPt_sf_;
  // wgtInfo.apply_metRes_sf       = apply_metRes_sf_;
  // wgtInfo.apply_metTTbar_sf     = apply_metTTbar_sf_;
  // wgtInfo.apply_ttbarSysPt_sf   = apply_ttbarSysPt_sf_;
  // wgtInfo.apply_ISR_sf          = apply_ISR_sf_;
  // wgtInfo.apply_pu_sf           = apply_pu_sf_;
  // wgtInfo.apply_sample_sf       = apply_sample_sf_;


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

  // Count number of categories
  TH1D* h_yield_template = analyzers[0]->GetYieldTemplate();
  int nCategories = h_yield_template->GetNbinsX();
  vector<TString> categoryList;
  for( int i=1; i<=nCategories; i++ ) categoryList.push_back( h_yield_template->GetXaxis()->GetBinLabel(i) );
  cout << "    " << nCategories << " categories" << endl << endl;

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

		for( int iClassy=0; iClassy<nGenClassy; iClassy++ ) {

			// int histIndex = iClassy*nSystematics + iSys;

			// Gen and Systematic String
			TString reg_gen_sys_name = "__";
			reg_gen_sys_name += thisAnalyzer->GetLabel();
			reg_gen_sys_name += "__genClassy_";
			reg_gen_sys_name += genClassyList[iClassy].label;
			// reg_gen_sys_name += "__systematic_";
			// reg_gen_sys_name += systematicList[iSys].label;

			TString yieldname = "h_yields";
			yieldname += reg_gen_sys_name;
			TH1D* h_tmp = (TH1D*)h_template->Clone( yieldname );
			thisAnalyzer->SetYieldHistogram( iClassy, h_tmp );

		} // End loop over genClassys
	} // End loop over analyzers
  
  

  //
  // Declare non-yield histograms
  //


  const int nHistosVars = nGenClassy*nCategories;

  // The only histo we really care about, neutrino pT
  TH1D *h_nuPt[nHistosVars];


  f_output->cd(); // All non-yield histos will belong to the output file
  
  for(int iReg=0; iReg<nAnalyzers; iReg++) {
    for(int iGen=0; iGen<nGenClassy; iGen++) {
	    for( int iCat=0; iCat<nCategories; iCat++) {

		    // Histo Index
		    int iHisto = /*iReg*nGenClassy*nCategories +*/ iGen*nCategories + iCat;

		    TString hName = "";

		    TString reg_gen_sys_name = "__";
		    reg_gen_sys_name += analyzers.at(iReg)->GetLabel();
		    reg_gen_sys_name += "__genClassy_";
		    reg_gen_sys_name += genClassyList[iGen].label;
		    reg_gen_sys_name += "__category_";
		    reg_gen_sys_name += categoryList[iCat];

		    // Prevent meaningless histograms from being created
		    if( reg_gen_sys_name.Contains("bulk") && reg_gen_sys_name.Contains("5j") ) continue;
		    if( reg_gen_sys_name.Contains("corridor") &&
		        (reg_gen_sys_name.Contains("23j") || reg_gen_sys_name.Contains("4j")) ) continue;


		    //
		    // Neutrino pT
		    //
		    hName = "h_nuPt" + reg_gen_sys_name;
		    h_nuPt[iHisto] = new TH1D( hName, "Neutrino p_{T};p_{T} (GeV)", 100, 0., 1000. );

	    } // end loop over categories
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
    // wgtInfo.getWeightHistogramFromBaby( file );
    
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
      // wgtInfo.getEventWeights();

      // Reweight events to merge ttbar samples
      double wgt_stitching = 1.;
      if( sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8      ) wgt_stitching *= 5.77109e+06/(5.77109e+06 + 2.34556e+07);
      if( sample.id == sampleInfo::k_ttbar_diLept_madgraph_pythia8_ext1 ) wgt_stitching *= 2.34556e+07/(5.77109e+06 + 2.34556e+07);


      /////////////////////////////
      //                         //
      // Compute Event Variables //
      //                         //
      /////////////////////////////

      // HJ's code for gen-reco matching

      // This bit just precalculates the number of reco leptons - 1 or 2
      bool reco1l = ngoodleps()==1 && nvetoleps()==1 && PassTrackVeto() && PassTauVeto();
      bool reco2l = ngoodleps()==2 || nvetoleps()==2;

      // Writes an error message if an event belongs to multiple genClassies
      bool onelw = is1lepFromW();
      bool oneltop = is1lepFromTop();
      bool dilep = is2lep();
      if( (dilep && oneltop) ||
          (dilep && onelw) ||
          (onelw && oneltop) ) cout << __LINE__ << " " << onelw << " " << oneltop << " " << dilep << endl;

      // Skip events where genClassy and recoClassy don't agree
      if( ((onelw || oneltop) && reco2l) ||
          (dilep && reco1l) ) {
	      // cout << "Skipping an event due to gen/reco classy mismatch." << endl;
	      continue;
      }

      // NOTE: this still allows through events that have 1 good lep + >2 veto leps,
      // and events with 1 good lep + fail tau/isoTrack veto

      // Skip and print error message if event has no genClassy (or genClassy is just ZtoNuNu)
      if( !onelw && !oneltop && !dilep ) {
	      // cout << " " << currentFile->GetTitle() << endl;
	      continue;
      }

      if(genmet()<=0) cout << "WTF" << endl;


      /////////////////////////////


      // Find the pT of the two gen neutrinos
      LorentzVector genNu1_p4(0., 0., 0., 0.);
      LorentzVector genNu2_p4(0., 0., 0., 0.);

      int numNus = 0;

      for( uint i=0; i<gennus_id().size(); i++ ) {
	      if( gennus_status().at(i) != 1 ) continue; // Status = 1
	      if( abs(gennus_id().at(i)) != 12 &&
	          abs(gennus_id().at(i)) != 14 &&    // Must actually be a neutrino
	          abs(gennus_id().at(i)) != 16 ) continue;
	      if( abs(gennus_motherid().at(i)) != 24 ) continue; // Mother must be a W

	      if(      numNus == 0 ) genNu1_p4 = gennus_p4().at(i);
	      else if( numNus == 1 ) genNu2_p4 = gennus_p4().at(i);
	      else cout << "Too many gen neutrinos!" << endl;

	      numNus++;
      }

      LorentzVector NuTotal_p4 = genNu1_p4 + genNu2_p4;
      const double nuPt = NuTotal_p4.Pt();
      if( nuPt < 55. ) continue; // Lower pT cutoff.



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
				}


				// Fill cutflow histogram
				std::vector<bool> cutflow_results = selectionInfo::get_selectionResults( thisAnalyzer->GetSelections() );
				for( uint i=0; i<cutflow_results.size(); i++ ) {
					if( !cutflow_results.at(i) ) break;
					h_cutflow[iAna]->Fill( i+1 );
				}

				thisAnalyzer->SetJesType( 0 );
				if( !thisAnalyzer->PassSelections() ) continue;

				// If we've passed selections, then get the event weight and the categories passed
				// double weight = thisAnalyzer->GetEventWeight( thisSystematic.id );
				double weight = scale1fb() * 36.8; // For consistency with HJ's code
				weight *= wgt_stitching;
				std::vector<int> categories_passed = thisAnalyzer->GetCategoriesPassed();

				// Loop over all the gen classifications that we passed
				for( genClassyInfo::Util thisGenClassy : thisAnalyzer->GetGenClassifications() ) {
					int iGen = thisGenClassy.id;
					if( !passedGenClassies[iGen] ) continue;

					/////////////////////////
					//                     //
					// Fill all histograms //
					//                     //
					/////////////////////////

					for( int iCat : categories_passed ) {

						// Fill yield histogram
						thisAnalyzer->GetYieldHistogram( iGen )->Fill( iCat, weight );


						// Histo Index
						int iHisto = /*iAna*nGenClassy*nCategories +*/ iGen*nCategories + (iCat-1);

						// Neutrino pT
						h_nuPt[iHisto]->Fill( nuPt, weight );

					} // End filling of non-yield histograms

				} // End loop over genClassy's

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
  // wgtInfo.cleanUp();


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


