#include "analyzer.h"


// Constructor
analyzer::analyzer()
{
	add2ndLep = false;
	includeTaus = false;
	isCorridor = false;
	jesType = analyzer::kNominal;
}


void analyzer::AddGenClassifications( std::vector<genClassyInfo::Util> new_classies ) {
	for( genClassyInfo::Util thisClassy : new_classies ) classifications.push_back( thisClassy );
}

void analyzer::AddSelection( std::string label, bool (*new_selection)() ) {
	selections.push_back( std::make_pair( label, new_selection ) );
}

void analyzer::AddSelections( std::vector<std::pair<std::string,bool(*)()> > new_selections ) {
	for( std::pair<std::string,bool(*)()> thisSelection : new_selections ) selections.push_back( thisSelection );
}

void analyzer::AddCategories( std::vector<int> (*new_categories)(int,bool) ) { categories_function = new_categories; }

void analyzer::AddSystematics( std::vector<sysInfo::Util> new_systematics ) {
	for( sysInfo::Util thisSyst : new_systematics ) systematics.push_back( thisSyst );
}

std::vector<genClassyInfo::Util> analyzer::GetGenClassifications() { return classifications; }
std::vector<std::pair<std::string,bool(*)()> > analyzer::GetSelections() { return selections; }

std::vector<int> analyzer::GetCategoriesPassed() {
	categoryInfo::SetJesType( jesType );
	categoryInfo::SetAdd2ndLep( add2ndLep );
	return categories_function;
}

std::vector<sysInfo::Util> analyzer::GetSystematics() { return systematics; }

double analyzer::GetEventWeight( sysInfo::Util whichSystematic ) {

	// This function to be filled in when the appropriate changes have been made to sysInfo

	if( isCorridor ) return 1.0;
	return 1.0;
}

bool analyzer::GetAdd2ndLep() { return add2ndLep; }
bool analyzer::GetIncludeTaus() { return includeTaus; }
bool analyzer::GetIsCorridor() { return isCorridor; }
int analyzer::GetJesType() { return jesType; }

TH1D* analyzer::GetYieldHistogram( int idx ) { return h_yield[idx]; }
TH3D* analyzer::GetYieldHistogramSig( int idx ) { return h_yield_sig[idx]; }

bool analyzer::PassSelections() {
	selectionInfo::SetAdd2ndLep( add2ndLep );
	selectionInfo::SetJesType( jesType );
	selectionInfo::SetIncludeTaus( includeTaus );
	for( std::pair<std::string,bool(*)()> selection : selections ) {
		if( selection.second == false ) return false;
	}
	return true;
}

void analyzer::SetAdd2ndLep( bool use_lep2 ) { add2ndLep = use_lep2; }
void analyzer::SetIncludeTaus( bool use_taus ) {includeTaus = use_taus; }
void analyzer::SetIsCorridor( bool is_corridor ) {isCorridor = is_corridor; }
void analyzer::SetJesType( int jestype ) { jesType = jestype; }
