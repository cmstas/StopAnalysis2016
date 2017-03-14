// Main program to run stop loopers

// C++
#include <string>
#include <vector>
#include <iostream>

// Stop Analysis
#include "analyzer.h"


void runLoopers() {

	// Declare all the analyzers we'll need
	analyzer SR_MlbBinned;
	analyzer SR_corridor;
	analyzer CR2L_MlbBinned;
	analyzer CR2L_corridor;
	analyzer CR0b_MlbBinned;
	analyzer CR0b_tightBTagHighMlb;
	analyzer CR0b_corridor;

	// Set the attributes for each analyzer
	CR2L_MlbBinned.SetAdd2ndLep( true );
	CR2L_corridor.SetAdd2ndLep( true );

	// Give each analyzer the basic/common gen classifications, selections, etc. it'll need
	for( analyzer iter : {SR_MlbBinned, SR_corridor, CR2L_MlbBinned, CR2L_corridor, CR0b_MlbBinned, CR0b_tightBTagHighMlb, CR0b_corridor} ) {

		using namespace genClassyInfo;
		using namespace sysInfo;

		iter.AddGenClassifications( {k_ge2lep, k_ee1lep_fromW, k_ee1lep_fromTop, k_ZtoNuNu} );

		iter.AddSystematics( {k_nominal, k_JESUp, k_JESDown, k_lumiUp, k_lumiDown} );
		iter.AddSystematics( {k_bTagEffHFUp, k_bTagEffHFDown, k_bTagEffLFUp, k_bTagEffLFDown, k_lepSFUp, k_lepSFDown, } );
		iter.AddSystematics( {k_alphasUp, k_alphasDown, k_q2Up, k_q2Down} );
	}

	// Add the unique attributes to each analyzer
	// i.e. the systematics, selections, etc. that aren't universal across all analyzers
	SR_MlbBinned.AddSelections(   selectionInfo::get_selection_SR() );
	SR_corridor.AddSelections(    selectionInfo::get_selection_SR_corridor() );
	CR2L_MlbBinned.AddSelections( selectionInfo::get_selection_CR2l() );
	CR2L_corridor.AddSelections(  selectionInfo::get_selection_CR2l_corridor() );
	CR0b_MlbBinned.AddSelections( selectionInfo::get_selection_CR0b() );
	CR0b_tightBTagHighMlb.AddSelections( selectionInfo::get_selection_CR0b_tightBTagHighMlb() );
	CR0b_corridor.AddSelections(  selectionInfo::get_selection_CR0b_corridor() );

	SR_MlbBinned.AddCategories();
	SR_corridor.AddCategories();
	CR2L_MlbBinned.AddCategories();
	CR2L_corridor.AddCategories();
	CR0b_MlbBinned.AddCategories();
	CR0b_tightBTagHighMlb.AddCategories();
	CR0b_corridor.AddCategories();

	SR_MlbBinned.AddSystematics();
	SR_corridor.AddSystematics();
	CR2L_MlbBinned.AddSystematics();
	CR2L_corridor.AddSystematics();
	CR0b_MlbBinned.AddSystematics();
	CR0b_tightBTagHighMlb.AddSystematics();
	CR0b_corridor.AddSystematics();

	// Do any other setup we need to do for these analyzers
	//
	//
	//

	// Finally, run the loopers!
	doLooper( SR_MlbBinned );
	doLooper( SR_corridor );
	doLooper( CR2L_MlbBinned );
	doLooper( CR2L_corridor );
	doLooper( CR0b_MlbBinned );
	doLooper( CR0b_tightBTagHighMlb );
	doLooper( CR0b_corridor );


}


int main() {  // Just in case we want to run compiled at some point
	runLoopers();
	return 0;
}
