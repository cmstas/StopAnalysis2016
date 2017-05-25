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
	analyzer( std::string new_label );
	// ~analyzer();

	void AddGenClassification( genClassyInfo::Util new_classy );
	void AddGenClassifications( std::vector<genClassyInfo::Util> new_classies );
	void AddSelection( std::string label, bool (*new_selection)() );
	void AddSelections( std::vector<std::pair<std::string,bool(*)()> > new_selections );
	void AddCategories( std::vector<int> (*new_categories)(int,bool) );
	void AddSystematic( sysInfo::Util new_systematic );
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
	std::string GetLabel();
	bool GetUseMetTTbarWeights();
	TH1* GetYieldHistogram( int idx );
	TH1D* GetYieldTemplate();
	TH3D* GetYieldTemplateSignal();

	bool PassSelections();

	void ResetGenClassifications();
	void ResetSystematics();

	void SetAdd2ndLep( bool use_lep2 );
	void SetIncludeTaus( bool use_taus );
	void SetIsCorridor( bool is_corridor );
	void SetJesType( int jestype );
	void SetUseMetTTbarWeights( bool use_metttbar );
	void SetUseTightTagHighMlb( bool use_tighttag );
	void SetYieldHistogram( int idx, TH1* histo );
	void SetYieldTemplate( TH1D* yield_template );
	void SetYieldTemplateSignal( TH3D* yield_template );

private:
	std::vector<genClassyInfo::Util> classifications;
	std::vector< std::pair<std::string,bool(*)()> > selections;
	std::vector<int>(*categories_function)(int,bool);
	std::vector<sysInfo::Util> systematics;

	std::string label;

	bool add2ndLep;
	bool includeTaus;
	bool isCorridor;
	int  jesType;
	bool useMetTTbarWgts;
	bool useTightTagHighMlb;
	
	TH1D *h_yield_template;
	TH3D *h_yield_template_signal;
	
	TH1 *h_yield[nYieldBins_];
	
};



#endif
