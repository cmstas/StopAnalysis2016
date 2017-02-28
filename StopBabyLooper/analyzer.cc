#include "analyzer.h"


// Constructor
analyzer::analyzer()
{
	add2ndLep = true;
	includeTaus = false;
	jesType = analyzer::kNominal;
}


void analyzer::AddGenClassifications( std::vector<genClassyInfo::ID> new_classies ) {
	for( genClassyInfo::ID thisID : new_classies ) classifications.push_back( thisID );
};

void analyzer::AddSelections( std::vector<something> new_selections ) {
	for( something thisThing : new_selections ) selections.push_back( thisThing );
};

void analyzer::AddCategories( std::vector<something> new_categories ) {
	for( something thisThing : new_categories ) categories.push_back( thisThing );
};

void analyzer::AddSystematics( std::vector<sysInfo::ID> new_systematics ) {
	for( sysInfo::ID thisSyst : new_systematics ) systematics.push_back( thisSyst );
};

std::vector<genClassyInfo::ID> analyzer::GetGenClassifications() { return classifications; }
std::vector<something> analyzer::GetSelections() { return selections; }
std::vector<something> analyzer::GetCategories() { return categories; }
std::vector<sysInfo::ID> analyzer::GetSystematics() { return systematics; }
bool analyzer::GetAdd2ndLep() { return add2ndLep; }
bool analyzer::GetIncludeTaus() { return includeTaus; }
direction analyzer::GetJesType() { return jesType; }

void analyzer::SetAdd2ndLep( bool use_lep2 ) { add2ndLep = use_lep2; }
void analyzer::SetIncludeTaus( bool use_taus ) {includeTaus = use_taus; }
void analyzer::SetJesType( direction jestype ) { jesType = jestype; }
