#include "analyzer.h"


// Constructor
analyzer::analyzer( std::string new_label )
	: label(new_label)
{
	add2ndLep = false;
	includeTaus = false;
	isCorridor = false;
	useMetTTbarWgts = false;
	useTightTagHighMlb = false;
	jesType = 0;
}


void analyzer::AddGenClassification( genClassyInfo::Util new_classy ) { classifications.push_back( new_classy ); }

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

void analyzer::AddSystematic( sysInfo::Util new_systematic ) { systematics.push_back( new_systematic ); }

void analyzer::AddSystematics( std::vector<sysInfo::Util> new_systematics ) {
	for( sysInfo::Util thisSyst : new_systematics ) systematics.push_back( thisSyst );
}

std::vector<genClassyInfo::Util> analyzer::GetGenClassifications() { return classifications; }
std::vector<std::pair<std::string,bool(*)()> > analyzer::GetSelections() { return selections; }

std::vector<int> analyzer::GetCategoriesPassed() {
	categoryInfo::SetJesType( jesType );
	categoryInfo::SetAdd2ndLep( add2ndLep );
	categoryInfo::SetTightTagHighMlb( useTightTagHighMlb );
	return categories_function( jesType, add2ndLep );
}

std::vector<sysInfo::Util> analyzer::GetSystematics() { return systematics; }

double analyzer::GetEventWeight( sysInfo::ID whichSystematic ) {

	if( isCorridor ) return sysInfo::GetEventWeight_corridor( whichSystematic );
	else if( useTightTagHighMlb &&  useMetTTbarWgts ) return sysInfo::GetEventWeight_SRbulk( whichSystematic );
	else if( useTightTagHighMlb && !useMetTTbarWgts ) return sysInfo::GetEventWeight_CR2lbulk( whichSystematic );
	return sysInfo::GetEventWeight( whichSystematic );
}

bool analyzer::GetAdd2ndLep() { return add2ndLep; }
bool analyzer::GetIncludeTaus() { return includeTaus; }
bool analyzer::GetIsCorridor() { return isCorridor; }
int analyzer::GetJesType() { return jesType; }
std::string analyzer::GetLabel() { return label; }
bool analyzer::GetUseMetTTbarWeights() { return useMetTTbarWgts; }

TH1* analyzer::GetYieldHistogram( int idx ) { return h_yield[idx]; }
TH1D* analyzer::GetYieldTemplate() { return h_yield_template; }
TH3D* analyzer::GetYieldTemplateSignal() { return h_yield_template_signal; }

bool analyzer::PassSelections() {
	selectionInfo::SetAdd2ndLep( add2ndLep );
	selectionInfo::SetJesType( jesType );
	selectionInfo::SetIncludeTaus( includeTaus );
	for( std::pair<std::string,bool(*)()> selection : selections ) {
		if( selection.second() == false ) return false;
	}
	return true;
}

void analyzer::ResetGenClassifications() { classifications.clear(); }
void analyzer::ResetSystematics() { systematics.clear(); }

void analyzer::SetAdd2ndLep( bool use_lep2 ) { add2ndLep = use_lep2; }
void analyzer::SetIncludeTaus( bool use_taus ) {includeTaus = use_taus; }
void analyzer::SetIsCorridor( bool is_corridor ) {isCorridor = is_corridor; }
void analyzer::SetJesType( int jestype ) { jesType = jestype; }
void analyzer::SetUseMetTTbarWeights( bool use_metttbar ) { useMetTTbarWgts = use_metttbar; }
void analyzer::SetUseTightTagHighMlb( bool use_tighttag ) { useTightTagHighMlb = use_tighttag; }
void analyzer::SetYieldHistogram( int idx, TH1* histo ) { h_yield[idx] = histo; }
void analyzer::SetYieldTemplate( TH1D* yield_template ) { h_yield_template = yield_template; }
void analyzer::SetYieldTemplateSignal( TH3D* yield_template ) { h_yield_template_signal = yield_template; }

