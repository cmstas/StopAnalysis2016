#ifndef categoryInfo_H
#define categoryInfo_H

// stopCORE
#include "stop_1l_babyAnalyzer.h"

// ROOT
#include "TH1D.h"
#include "TH3D.h"
#include "TLorentzVector.h"

// C
#include <string>
#include <utility>
#include <vector>


//
// NAMESPACE
//
namespace categoryInfo{
  
  //
  // NAMESPACE FUNCTIONS
  //
  void SetJesType( int type );
  void SetAdd2ndLep( bool addlep2 );
	void SetTightTagHighMlb( bool usetight );


  TH1D* getYieldHistoTemplate_SR_ICHEP();
  vector<int> passCategory_SR_ICHEP( int jesType=0, bool add2ndLepToMet=false );

  TH1D* getYieldHistoTemplate_SR_ICHEP_ext30fb();
  vector<int> passCategory_SR_ICHEP_ext30fb( int jesType=0, bool add2ndLepToMet=false );

  TH1D* getYieldHistoTemplate_SR_dev_ext30fb_mlb_v1();
  vector<int> passCategory_SR_dev_ext30fb_mlb_v1( int jesType=0, bool add2ndLepToMet=false );

	void SetAxisLabels_SR_dev_ext30fb_mlb_v2( TAxis* axis );
  TH1D* getYieldHistoTemplate_SR_dev_ext30fb_mlb_v2();
	TH3D* getYieldHistoTemplate_signal_SR_dev_ext30fb_mlb_v2();
  vector<int> passCategory_SR_dev_ext30fb_mlb_v2( int jesType=0, bool add2ndLepToMet=false );

  TH1D* getYieldHistoTemplate_SR_dev_ext30fb_bJetPt_v1();
  vector<int> passCategory_SR_dev_ext30fb_bJetPt_v1( int jesType=0, bool add2ndLepToMet=false );

	void SetAxisLabels_SR_corridor( TAxis* axis );
  TH1D* getYieldHistoTemplate_SR_corridor();
	TH3D* getYieldHistoTemplate_signal_SR_corridor();
  vector<int> passCategory_SR_corridor( int jesType=0, bool add2ndLepToMet=false );

  TH1D* getYieldHistoTemplate_CR2l_bulkTTbar();
  vector<int> passCategory_CR2l_bulkTTbar( int jesType=0, bool add2ndLepToMet=false );
  
}; // end class def


//////////////////////////////////////////////////////////////////////


#endif
