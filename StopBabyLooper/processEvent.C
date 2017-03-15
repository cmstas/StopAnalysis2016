// Script that process an event through all of the analyzers present


// C++
#include <string>
#include <vector>
#include <iostream>

// Stop Analysis
#include "../StopCORE/analyzer.h"
#include "../StopCORE/categoryInfo.h"
#include "../StopCORE/genClassyInfo.h"
#include "../StopCORE/selectionInfo.h"
#include "../StopCORE/sysInfo.h"


void processEvent( std::vector<analyzer*> analyzerList ) {


	// Loop over all analyzers
	for( analyzer* thisAnalyzer : analyzerList ) {


		// Make an array of which genClassy's this event passes
		bool passedGenClassies[genClassyInfo::k_nGenClassy];
		for( genClassyInfo::Util thisGenClassy : thisAnalyzer->GetGenClassifications() ) { passGenClassies[thisGenClassy.id] = thisGenClassy.eval_GenClassy; }
		// Should analyzer maybe store a vector of pointers to genClassy's, to avoid overhead from copy operations? ////////////////////////////////////////////////

		// Check if this event passes selections with JES set to nominal
		//  (saves us having to evaluate this for every systematic)
		thisAnalyzer->SetJesType( 0 );
		bool pass_JESnominal = thisAnalyzer->PassSelections();


		// Loop over all systematics in the analyzer
		for( sysInfo::Util thisSystematic : thisAnalyzer->GetSystematics() ) {

			// Check if this event passes selections, and also set the appropriate JES type for future use
			if( thisSystematic.id == sysInfo::k_JESUp ) {
				thisAnalysis->SetJesType( 1 );
				if( !thisAnalysis->PassSelections() ) continue;
			}
			else if( thisSystematic.id == sysInfo::k_JESDown ) {
				thisAnalysis->SetJesType( -1 );
				if( !thisAnalysis->PassSelections() ) continue;
			}
			else {
				thisAnalysis->SetJesType( 0 );
				if( !pass_JESnominal ) continue;
			}


			double weight = thisAnalyzer->GetEventWeight( thisSystematic );
			std::vector<int> categories_passed = thisAnalyzer->GetCategoriesPassed();

			// Loop over all the gen classifications that we passed
			for( genClassyInfo::Util thisGenClassy : thisAnalyzer->GetGenClassifications() ) {
				if( !passedGenClassies[thisGenClassy.id] ) continue;

				// Get the index for the histogram corresponding to this genClassy and systematic
				int histIndex = thisGenClassy.id * sysInfo::k_nSys + thisSystematic.id;

				// Fill yield histograms
				for( int category : categories_passed ) {
					thisAnalyzer->GetYieldHistogram( histIndex )->Fill( category, weight );
				}

				// Do any other histogram filling that needs doing


			} // End loop over genClassy's

		} // End loop over systematics

	} // End loop over analyzers

} // End of function
