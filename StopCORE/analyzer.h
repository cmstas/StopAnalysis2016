#ifndef ANALYZER_H
#define ANALYZER_H

// C++
#include <string>
#include <vector>
#include <iostream>


// Stop Analysis
#include "stop_1l_babyAnalyzer.h"
#include "genClassyInfo.h"
#include "sysInfo.h"
#include "selectionInfo.h"
#include "categoryInfo.h"


enum kJES{ kNominal=0, kUp=1, kDown=-1 };

const int nYieldBins_ = genClassyInfo::k_nGenClassy*sysInfo::k_nSys;

class analyzer {

public:
	analyzer();
	// ~analyzer();

	void AddGenClassifications( std::vector<genClassyInfo::Util> new_classies );
	void AddSelection( std::string label, bool (*new_selection)() );
	void AddSelections( std::vector<std::pair<std::string,bool(*)()> > new_selections );
	void AddCategories( std::vector<int> new_categories );
	void AddSystematics( std::vector<sysInfo::ID> new_systematics );

	std::vector<genClassyInfo::Util> GetGenClassifications();
	std::vector<std::pair<std::string,bool(*)()> > GetSelections();
	std::vector<int> GetCategories();
	TH1D* GetYieldTemplate();
	std::vector<sysInfo::ID> GetSystematics();
	bool GetAdd2ndLep();
	bool GetIncludeTaus();
	kJES GetJesType();

	bool PassSelections();

	void SetAdd2ndLep( bool use_lep2 );
	void SetIncludeTaus( bool use_taus );
	void SetJesType( kJES jestype );

private:
	std::vector<genClassyInfo::Util> classifications;
	std::vector< std::pair<std::string,bool(*)()> > selections;
	std::vector<int> categories;
	std::vector<sysInfo::ID> systematics;

	bool add2ndLep;
	bool includeTaus;
	kJES jesType;
	
	TH1D *h_yield_template;
	TH3D *h_yield_template_sigScan;
	
	TH1D *h_yield[nYieldBins_];
	TH3D *h_yield_sig[nYieldBins_];
	
};



#endif
