#ifndef ANALYZER_H
#define ANALYZER_H

// C++
#include <string>
#include <vector>
#include <iostream>

// ROOT
#include "TString.h"

// Stop Analysis
#include "../StopCORE/stop_1l_babyAnalyzer.h"
#include "../StopCORE/genClassyInfo.h"


enum direction{ kNominal, kUp, kDown };


class analyzer {

public:
	analyzer();
	// ~analyzer();

	void AddGenClassifications( std::vector<genClassyInfo::ID> new_classies );
	void AddSelections( std::vector<something> new_selections );
	void AddCategories( std::vector<something> new_categories );
	void AddSystematics( std::vector<sysInfo::ID> new_systematics );

	std::vector<genClassyInfo::ID> GetGenClassifications();
	std::vector<something> GetSelections();
	std::vector<something> GetCategories();
	std::vector<sysInfo::ID> GetSystematics();
	bool GetAdd2ndLep();
	bool GetIncludeTaus();
	direction GetJesType();

	void SetAdd2ndLep( bool use_lep2 );
	void SetIncludeTaus( bool use_taus );
	void SetJesType( direction jestype );

private:
	std::vector<genClassyInfo::ID> classifications;
	std::vector< something > selections;
	std::vector< something > categories;
	std::vector<sysInfo::ID> systematics;

	bool add2ndLep;
	bool includeTaus;
	direction jesType;


};



#endif
