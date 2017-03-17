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


const int nYieldBins_ = genClassyInfo::k_nGenClassy * sysInfo::k_nSys;

class analyzer {

public:
	analyzer();
	// ~analyzer();

	void AddGenClassifications( std::vector<genClassyInfo::Util> new_classies );
	void AddSelection( std::string label, bool (*new_selection)() );
	void AddSelections( std::vector<std::pair<std::string,bool(*)()> > new_selections );
	void AddCategories( std::vector<int> (*new_categories)(int,double) );
	void AddSystematics( std::vector<sysInfo::Util> new_systematics );

	std::vector<genClassyInfo::Util> GetGenClassifications();
	std::vector<std::pair<std::string,bool(*)()> > GetSelections();
	std::vector<int> GetCategoriesPassed();
	std::vector<sysInfo::Util> GetSystematics();
	double GetEventWeight( sysInfo::ID whichSystematic );
	bool GetAdd2ndLep();
	bool GetIncludeTaus();
	bool GetIsCorridor();
	int GetJesType();
	TH1D* GetYieldHistogram( int idx );
	TH3D* GetYieldHistogramSig( int idx );
	TH1D* GetYieldTemplate();

	bool PassSelections();

	void SetAdd2ndLep( bool use_lep2 );
	void SetIncludeTaus( bool use_taus );
	void SetIsCorridor( bool is_corridor );
	void SetJesType( int jestype );

private:
	std::vector<genClassyInfo::Util> classifications;
	std::vector< std::pair<std::string,bool(*)()> > selections;
	std::vector<int>(*categories_function)(int,double);
	std::vector<sysInfo::Util> systematics;

	bool add2ndLep;
	bool includeTaus;
	bool isCorridor;
	int  jesType;
	
	TH1D *h_yield_template;
	TH3D *h_yield_template_sigScan;
	
	TH1D *h_yield[nYieldBins_];
	TH3D *h_yield_sig[nYieldBins_];
	
};



#endif
