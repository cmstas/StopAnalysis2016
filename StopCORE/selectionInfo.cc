#include "selectionInfo.h"

// These variables can only be used within selectionInfo.cc, but they can be set from outside using the functions below
static int  localJesType = 0;
static bool localAddLep2 = false;
static bool localIncludeTaus = false;

void selectionInfo::SetJesType( int type ) { localJesType = type; }
void selectionInfo::SetAdd2ndLep( bool addlep2 ) { localAddLep2 = addlep2; }
void selectionInfo::SetIncludeTaus( bool usetaus ) { localIncludeTaus = usetaus; }

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_metFilter(){
  bool result = false;
  // Only applies to data
  if( !babyAnalyzer.is_data() ) result = true;
  else{
    if( babyAnalyzer.filt_met() && 
	babyAnalyzer.filt_badChargedCandidateFilter() && 
	babyAnalyzer.filt_jetWithBadMuon() &&
	babyAnalyzer.filt_pfovercalomet() &&
	babyAnalyzer.filt_badMuonFilter() &&
	!babyAnalyzer.filt_duplicatemuons() &&
	!babyAnalyzer.filt_badmuons() &&
	babyAnalyzer.filt_nobadmuons()          ) result = true;
    /*
    if( babyAnalyzer.filt_met() && 
	babyAnalyzer.filt_badChargedCandidateFilter() && 
	babyAnalyzer.filt_jetWithBadMuon() &&
	babyAnalyzer.filt_pfovercalomet() &&
	babyAnalyzer.filt_badMuonFilter()     ) result = true;
    */
  } 
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_trigger_SR(){
  bool result = false;
  // Only applies to data
  if( !babyAnalyzer.is_data() ) result = true;
  else{
    if( (babyAnalyzer.HLT_SingleEl() && abs(babyAnalyzer.lep1_pdgid())==11) ||
	(babyAnalyzer.HLT_SingleMu() && abs(babyAnalyzer.lep1_pdgid())==13) ||
	(babyAnalyzer.HLT_MET())           ||
	(babyAnalyzer.HLT_MET110_MHT110()) ||
	(babyAnalyzer.HLT_MET120_MHT120())    ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_trigger_CR2l(){
  bool result = false;
  // Only applies to data
  if( !babyAnalyzer.is_data() ) result = true;
  else{
    if( ( babyAnalyzer.HLT_SingleEl() && (abs(babyAnalyzer.lep1_pdgid())==11 || abs(babyAnalyzer.lep2_pdgid())==11) ) ||
	( babyAnalyzer.HLT_SingleMu() && (abs(babyAnalyzer.lep1_pdgid())==13 || abs(babyAnalyzer.lep2_pdgid())==13) ) ||
	( babyAnalyzer.HLT_MET()) ||
	( babyAnalyzer.HLT_MET110_MHT110()) ||
	( babyAnalyzer.HLT_MET120_MHT120())    ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_trigger_CR2l_bulkTTbar(){
  bool result = false;
  // Only applies to data
  if( !babyAnalyzer.is_data() ) result = true;
  else{
    if( (babyAnalyzer.HLT_DiEl() &&
	 abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==22) ||
	(babyAnalyzer.HLT_DiMu() &&
	 abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==26) ||
	(babyAnalyzer.HLT_MuE()  &&
	 abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==24)    ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_goodVtx(){
  bool result = false;
  if( babyAnalyzer.nvtxs()>=1 ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ee1_sel_lep(){
  bool result = false;
  if( babyAnalyzer.ngoodleps()==1 ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ee0_veto_lep(){
  bool result = false;
  if( babyAnalyzer.nvetoleps()==1 ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_trackVeto(){
  bool result = false;
  if( babyAnalyzer.PassTrackVeto() ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_tauVeto(){
  bool result = false;
  if( babyAnalyzer.PassTauVeto() ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_diLep(){
  bool result = false;
  if( localIncludeTaus ){
    if( (babyAnalyzer.ngoodleps()>=2)        ||
	(babyAnalyzer.ngoodleps()==1 && 
	 babyAnalyzer.nvetoleps()>=2 && 
	 babyAnalyzer.lep2_p4().Pt()>10.0 )  ||
	(babyAnalyzer.ngoodleps()==1 && 
	 (!babyAnalyzer.PassTrackVeto() || 
	  !babyAnalyzer.PassTauVeto())     )     ) result = true;
  }
  else{
    if( (babyAnalyzer.ngoodleps()>=2)        ||
	(babyAnalyzer.ngoodleps()==1 && 
	 babyAnalyzer.nvetoleps()>=2 && 
	 babyAnalyzer.lep2_p4().Pt()>10.0 )      ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_diLep_bulkTTbar(){
  bool result = false;
  if( babyAnalyzer.lep1_p4().Pt()>30.0 && 
      babyAnalyzer.lep2_p4().Pt()>15.0 &&
      babyAnalyzer.lep1_MiniIso()<0.1 &&
      babyAnalyzer.lep2_MiniIso()<0.1 &&
      ( (abs(babyAnalyzer.lep1_pdgid())==13 && 
	 babyAnalyzer.lep1_passMediumID()        ) || 
	(abs(babyAnalyzer.lep1_pdgid())==11 && 
	 fabs(babyAnalyzer.lep1_p4().Eta())<1.4442 && 
	 babyAnalyzer.lep1_passMediumID()             ) ) &&
      ( (abs(babyAnalyzer.lep2_pdgid())==13 && 
	 babyAnalyzer.lep2_passMediumID()       ) || 
	(abs(babyAnalyzer.lep2_pdgid())==11 && 
	 fabs(babyAnalyzer.lep2_p4().Eta())<1.4442 && 
	 babyAnalyzer.lep2_passMediumID()             ) )    ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_oppSign_leps(){
  bool result = false;
  if( babyAnalyzer.lep1_pdgid()*babyAnalyzer.lep2_pdgid()<0.0 ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ZWindow_diLepMass(){
  bool result = false;
  // Only for ee/mumu pairs
  if( (abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid()))==24 ) result = true;
  else if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()>(91.1876+15.0) || 
	   (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()<(91.1876-15.0)    ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge20_diLepMass(){ return selectionInfo::pass_geX_diLepMass(20.0); }

bool selectionInfo::pass_geX_diLepMass(double cut_diLepMass){
  bool result = false;
  if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()>=cut_diLepMass ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ee_diLepFlavor() { return (abs(babyAnalyzer.lep1_pdgid()) == 11 && abs(babyAnalyzer.lep2_pdgid()) == 11); }
bool selectionInfo::pass_emu_diLepFlavor() { return (abs(babyAnalyzer.lep1_pdgid()) * abs(babyAnalyzer.lep2_pdgid()) == 11*13); }
bool selectionInfo::pass_mumu_diLepFlavor() { return (abs(babyAnalyzer.lep1_pdgid()) == 13 && abs(babyAnalyzer.lep2_pdgid()) == 13); }

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge2_jets(){ return selectionInfo::pass_geX_jets( 2, localJesType ); }
bool selectionInfo::pass_ge5_jets(){ return selectionInfo::pass_geX_jets( 5, localJesType ); }

bool selectionInfo::pass_geX_jets(int cut_nJets, int jesType){
  bool result = false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodjets()>=cut_nJets ) result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodjets()>=cut_nJets ) result = true;
  }
  else{
    if( babyAnalyzer.ngoodjets()>=cut_nJets ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge1_bJets(){ return selectionInfo::pass_geX_bJets( 1, localJesType ); }

bool selectionInfo::pass_geX_bJets(int cut_nBJets, int jesType){
  bool result = false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodbtags()>=cut_nBJets ) result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodbtags()>=cut_nBJets ) result = true;
  }
  else{
    if( babyAnalyzer.ngoodbtags()>=cut_nBJets ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ee0_bJets(){ return selectionInfo::pass_eeX_bJets( 0, localJesType ); }

bool selectionInfo::pass_eeX_bJets(int cut_nBJets, int jesType){
  bool result = false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodbtags()==cut_nBJets ) result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodbtags()==cut_nBJets ) result = true;
  }
  else{
    if( babyAnalyzer.ngoodbtags()==cut_nBJets ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ee0_bJets_tightBTagHighMlb(){ return selectionInfo::pass_eeX_bJets_tightBTagHighMlb( 0, localJesType ); }

bool selectionInfo::pass_eeX_bJets_tightBTagHighMlb(int cut_nBJets, int jesType){
  bool result = false;
  int nTightTags = babyAnalyzer.ntightbtags();
  if(jesType==1)  nTightTags = babyAnalyzer.jup_ntightbtags();
  if(jesType==-1) nTightTags = babyAnalyzer.jdown_ntightbtags();
  int nMedTags = babyAnalyzer.ngoodbtags();
  if(jesType==1)  nMedTags = babyAnalyzer.jup_ngoodbtags();
  if(jesType==-1) nMedTags = babyAnalyzer.jdown_ngoodbtags();
  double mlb = babyAnalyzer.Mlb_closestb();
  if( (nMedTags==0) || 
      (nMedTags>=1 && nTightTags==cut_nBJets && mlb>175.0) ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge50_met(){  return selectionInfo::pass_geX_met(  50.0, localJesType, localAddLep2 ); }
bool selectionInfo::pass_ge150_met(){ return selectionInfo::pass_geX_met( 150.0, localJesType, localAddLep2 ); }
bool selectionInfo::pass_ge250_met(){ return selectionInfo::pass_geX_met( 250.0, localJesType, localAddLep2 ); }

bool selectionInfo::pass_geX_met(double cut_met, int jesType, bool add2ndLepToMet){
  bool result = false;
  if( add2ndLepToMet ){
    if( jesType==1){
      if( babyAnalyzer.pfmet_rl_jup()>=cut_met ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_rl_jdown()>=cut_met ) result = true;
    }
    else{
      if( babyAnalyzer.pfmet_rl()>=cut_met ) result = true;
    }
  } // end if add2ndLepToMet
  else{
    if( jesType==1){
      if( babyAnalyzer.pfmet_jup()>=cut_met ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_jdown()>=cut_met ) result = true;
    }
    else{
      if( babyAnalyzer.pfmet()>=cut_met ) result = true;
    }
  } // end if !add2ndLepToMet
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge150_mt(){ return selectionInfo::pass_geX_mt( 150.0, localJesType, localAddLep2 ); }

bool selectionInfo::pass_geX_mt(double cut_mt, int jesType, bool add2ndLepToMet){
  bool result = false;
  if( add2ndLepToMet ){
    if( jesType==1 ){
      if( babyAnalyzer.mt_met_lep_rl_jup()>=cut_mt ) result = true;
    }
    else if( jesType==-1 ){
      if( babyAnalyzer.mt_met_lep_rl_jdown()>=cut_mt ) result = true;
    }
    else{
      if( babyAnalyzer.mt_met_lep_rl()>=cut_mt ) result = true;
    }
  }
  else{
    if( jesType==1 ){
      if( babyAnalyzer.mt_met_lep_jup()>=cut_mt ) result = true;
    }
    else if( jesType==-1 ){
      if( babyAnalyzer.mt_met_lep_jdown()>=cut_mt ) result = true;
    }
    else{
      if( babyAnalyzer.mt_met_lep()>=cut_mt ) result = true;
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge0p5_minDPhi(){ return selectionInfo::pass_geX_minDPhi( 0.5, localJesType, localAddLep2 ); }

bool selectionInfo::pass_ge0p8_minDPhi(){ return selectionInfo::pass_geX_minDPhi( 0.8, localJesType, localAddLep2 ); }

bool selectionInfo::pass_geX_minDPhi(double cut_minDPhi, int jesType, bool add2ndLepToMet){
  bool result = false;
  if( add2ndLepToMet ){
    if( jesType==1 ){
      if( babyAnalyzer.mindphi_met_j1_j2_rl_jup()>=cut_minDPhi ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.mindphi_met_j1_j2_rl_jdown()>=cut_minDPhi ) result = true;
    }
    else{
      if( babyAnalyzer.mindphi_met_j1_j2_rl()>=cut_minDPhi ) result = true;
    }
  }
  else{
    if( jesType==1 ){
      if( babyAnalyzer.mindphi_met_j1_j2_jup()>=cut_minDPhi ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.mindphi_met_j1_j2_jdown()>=cut_minDPhi ) result = true;
    }
    else{
      if( babyAnalyzer.mindphi_met_j1_j2()>=cut_minDPhi ) result = true;
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

// bool selectionInfo::pass_ge250_j1pt() { return pass_geX_j1pt( 250., localJesType ); }

// bool selectionInfo::pass_geX_j1pt( double cut_pt, int jesType ) {
// 	if(      jesType==1  ) return babyAnalyzer.jup_ak4pfjets_p4().at(0).pt() >= cut_pt;
// 	else if( jesType==-1 ) return babyAnalyzer.jdown_ak4pfjets_p4().at(0).pt() >= cut_pt;
// 	return babyAnalyzer.ak4pfjets_p4().at(0).pt() >= cut_pt;
// }

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_j1NotBtag() { return !pass_j1MedBtag( localJesType ); }

bool selectionInfo::pass_j1MedBtag( int jesType ) {
	if( jesType==1 ) {
		if( babyAnalyzer.jup_ngoodjets() == 0 ) return false;
		return babyAnalyzer.jup_ak4pfjets_passMEDbtag().at(0);
	}
	else if( jesType==-1 ) {
		if( babyAnalyzer.jdown_ngoodjets() == 0 ) return false;
		return babyAnalyzer.jdown_ak4pfjets_passMEDbtag().at(0);
	}
	if( babyAnalyzer.ngoodjets() == 0 ) return false;
	return babyAnalyzer.ak4pfjets_passMEDbtag().at(0);
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_lt150_lep1pt() { return !pass_geX_lep1pt( 150. ); }

bool selectionInfo::pass_geX_lep1pt( double cut_pt ) { return babyAnalyzer.lep1_p4().pt() >= cut_pt; }

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_lt2_dPhiLepMet() { return !pass_geX_dPhiLepMet( 2.0, localJesType, localAddLep2 ); }

bool selectionInfo::pass_geX_dPhiLepMet( double cut_phi, int jesType, bool add2ndLepToMet ) {
	if( add2ndLepToMet ) {
		if(      jesType==1  ) return babyAnalyzer.lep1_dphiMET_rl_jup() >= cut_phi;
		else if( jesType==-1 ) return babyAnalyzer.lep1_dphiMET_rl_jdown() >= cut_phi;
		return babyAnalyzer.lep1_dphiMET_rl() >= cut_phi;
	}
	else {
		if(      jesType==1  ) return babyAnalyzer.lep1_dphiMET_jup() >= cut_phi;
		else if( jesType==-1 ) return babyAnalyzer.lep1_dphiMET_jdown() >= cut_phi;
	}
	return babyAnalyzer.lep1_dphiMET() >= cut_phi;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate( std::vector<selectionInfo::cut> cutList, std::string name, std::string title ) {

	TH1D* result = get_cutflowHistoTemplate( cutList );
	result->SetNameTitle( name.c_str(), title.c_str() );

	return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate( std::vector<selectionInfo::cut> cutList ) {

	int nbins = cutList.size();

	TH1D* result = new TH1D( "h_cutflow_tmp", "Cutflow histogram", nbins, 0.5, float(nbins)+0.5 );
	TAxis* axis = result->GetXaxis();

	for( int i=1; i<=nbins; i++ ) {
		axis->SetBinLabel( i, cutList.at(i-1).first.c_str() );
	}

	return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<TH1D*> selectionInfo::get_cutflowHistoTemplate_nMinus1( TH1D* original ) {

	std::vector<TH1D*> result;

	int nbins = original->GetNbinsX();

	for( int i=1; i<=nbins; i++ ) {
		std::string variable = original->GetXaxis()->GetBinLabel( i );
		std::string newname = original->GetName() + std::string("_") + variable;
		std::string newtitle = original->GetTitle() + std::string(", nMinus1, ") + variable;

		TH1D* h_tmp = (TH1D*)original->Clone( newname.c_str() );
		h_tmp->SetTitle( newtitle.c_str() );
		result.push_back( h_tmp );
	}

	return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<bool> selectionInfo::get_selectionResults( std::vector<selectionInfo::cut> cutList ) {

	std::vector<bool> result;
	for( selectionInfo::cut thisCut : cutList ) {
		result.push_back( thisCut.second() );
	}

	return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_SR(int jesType){

  bool result = true;
  
  SetJesType( jesType );

  selectionInfo::v_cut selection_cuts = get_selection_SR();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_SR(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_SR) ));   // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "ee1SelLepton",  (*pass_ee1_sel_lep) ));  // 4) ==1 selected lepton
	result.push_back( cut( "ee0VetoLepton", (*pass_ee0_veto_lep) )); // 5) ==0 veto leptons
	result.push_back( cut( "isoTrackVeto",  (*pass_trackVeto) ));    // 6) Track Veto
	result.push_back( cut( "tauVeto",       (*pass_tauVeto) ));      // 7) Tau Veto
	result.push_back( cut( "ge2Jets",       (*pass_ge2_jets) ));     // 8) nGoodJets>=2
	result.push_back( cut( "ge1BJets",      (*pass_ge1_bJets) ));    // 9) nTagJets>=1
	result.push_back( cut( "ge150met",      (*pass_ge150_met) ));    // 10) met>150.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 11) mt>150.0
	result.push_back( cut( "ge0p8minDPhi",  (*pass_ge0p8_minDPhi) ));// 12) minDPhi(met,j1/j2)>0.8

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_SR_corridor(int jesType) {

  bool result = true;
  
  SetJesType( jesType );

  selectionInfo::v_cut selection_cuts = get_selection_SR_corridor();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;

}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_SR_corridor(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_SR) ));   // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "ee1SelLepton",  (*pass_ee1_sel_lep) ));  // 4) ==1 selected lepton
	result.push_back( cut( "ee0VetoLepton", (*pass_ee0_veto_lep) )); // 5) ==0 veto leptons
	result.push_back( cut( "isoTrackVeto",  (*pass_trackVeto) ));    // 6) Track Veto
	result.push_back( cut( "tauVeto",       (*pass_tauVeto) ));      // 7) Tau Veto
	result.push_back( cut( "ge5Jets",       (*pass_ge5_jets) ));     // 8) nGoodJets>=5
	result.push_back( cut( "ge1BJets",      (*pass_ge1_bJets) ));    // 9) nTagJets>=1
	result.push_back( cut( "ge250met",      (*pass_ge250_met) ));    // 10) met>250.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 11) mt>150.0
	result.push_back( cut( "ge0p5minDPhi",  (*pass_ge0p5_minDPhi) ));// 12) minDPhi(met,j1/j2)>0.5
	result.push_back( cut( "j1noBtag",      (*pass_j1NotBtag) ));    // 13) Leading jet is not b-tagged
	result.push_back( cut( "lt150LepPt",    (*pass_lt150_lep1pt) )); // 14) Leading lepton pT < 150
	result.push_back( cut( "lt2dPhiLepMet", (*pass_lt2_dPhiLepMet)));// 15) dPhi(lep1,MET) < 2.0

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR0b(int jesType){

  bool result = true;

	SetJesType( jesType );

  selectionInfo::v_cut selection_cuts = get_selection_CR0b();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_CR0b(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_SR) ));   // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "ee1SelLepton",  (*pass_ee1_sel_lep) ));  // 4) ==1 selected lepton
	result.push_back( cut( "ee0VetoLepton", (*pass_ee0_veto_lep) )); // 5) ==0 veto leptons
	result.push_back( cut( "isoTrackVeto",  (*pass_trackVeto) ));    // 6) Track Veto
	result.push_back( cut( "tauVeto",       (*pass_tauVeto) ));      // 7) Tau Veto
	result.push_back( cut( "ge2Jets",       (*pass_ge2_jets) ));     // 8) nGoodJets>=2
	result.push_back( cut( "ee0BJets",      (*pass_ee0_bJets) ));    // 9) nMediumBtags==0
	result.push_back( cut( "ge150met",      (*pass_ge150_met) ));    // 10) met>150.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 11) mt>150.0
	result.push_back( cut( "ge0p8minDPhi",  (*pass_ge0p8_minDPhi) ));// 12) minDPhi(met,j1/j2)>0.8

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR0b_tightBTagHighMlb(int jesType){

  bool result = true;

  SetJesType( jesType );

  selectionInfo::v_cut selection_cuts = get_selection_CR0b_tightBTagHighMlb();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_CR0b_tightBTagHighMlb(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_SR) ));   // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "ee1SelLepton",  (*pass_ee1_sel_lep) ));  // 4) ==1 selected lepton
	result.push_back( cut( "ee0VetoLepton", (*pass_ee0_veto_lep) )); // 5) ==0 veto leptons
	result.push_back( cut( "isoTrackVeto",  (*pass_trackVeto) ));    // 6) Track Veto
	result.push_back( cut( "tauVeto",       (*pass_tauVeto) ));      // 7) Tau Veto
	result.push_back( cut( "ge2Jets",       (*pass_ge2_jets) ));     // 8) nGoodJets>=2
	result.push_back( cut( "ee0BJets",      (*pass_ee0_bJets_tightBTagHighMlb) ));    // 9) nTightTags==0
	result.push_back( cut( "ge150met",      (*pass_ge150_met) ));    // 10) met>150.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 11) mt>150.0
	result.push_back( cut( "ge0p8minDPhi",  (*pass_ge0p8_minDPhi) ));// 12) minDPhi(met,j1/j2)>0.8

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR0b_corridor(int jesType){

  bool result = true;

  SetJesType( jesType );

  selectionInfo::v_cut selection_cuts = get_selection_CR0b_corridor();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_CR0b_corridor(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_SR) ));   // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "ee1SelLepton",  (*pass_ee1_sel_lep) ));  // 4) ==1 selected lepton
	result.push_back( cut( "ee0VetoLepton", (*pass_ee0_veto_lep) )); // 5) ==0 veto leptons
	result.push_back( cut( "isoTrackVeto",  (*pass_trackVeto) ));    // 6) Track Veto
	result.push_back( cut( "tauVeto",       (*pass_tauVeto) ));      // 7) Tau Veto
	result.push_back( cut( "ge5Jets",       (*pass_ge5_jets) ));     // 8) nGoodJets>=5
	result.push_back( cut( "ee0BJets",      (*pass_ee0_bJets) ));    // 9) nMediumBtags==0
	result.push_back( cut( "ge250met",      (*pass_ge250_met) ));    // 10) met>250.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 11) mt>150.0
	result.push_back( cut( "ge0p5minDPhi",  (*pass_ge0p5_minDPhi) ));// 12) minDPhi(met,j1/j2)>0.5
	// (In CR0b, it can be safely assumed that the leading jet is not b-tagged)
	result.push_back( cut( "lt150LepPt",    (*pass_lt150_lep1pt) )); // 13) Leading lepton pT < 150
	result.push_back( cut( "lt2dPhiLepMet", (*pass_lt2_dPhiLepMet)));// 14) dPhi(lep1,MET) < 2.0

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR2l(int jesType){ return selectionInfo::pass_CR2l( jesType, localIncludeTaus, localAddLep2 ); }
bool selectionInfo::pass_CR2l(int jesType, bool inclTau, bool add2ndLepToMet){

  bool result = true;

  SetJesType( jesType );
	SetIncludeTaus( inclTau );
	SetAdd2ndLep( add2ndLepToMet );

  selectionInfo::v_cut selection_cuts = get_selection_CR2l();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_CR2l(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_CR2l) )); // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "passDilep",     (*pass_diLep) ));        // 4) Dilepton selection
	result.push_back( cut( "ge2Jets",       (*pass_ge2_jets) ));     // 5) nGoodJets>=2
	result.push_back( cut( "ge1BJets",      (*pass_ge1_bJets) ));    // 6) nTagJets>=1
	result.push_back( cut( "ge150met",      (*pass_ge150_met) ));    // 7) met>150.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 8) mt>150.0
	result.push_back( cut( "ge0p8minDPhi",  (*pass_ge0p8_minDPhi) ));// 9) minDPhi(met,j1/j2)>0.8

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR2l_corridor(int jesType){ return selectionInfo::pass_CR2l( jesType, localIncludeTaus, localAddLep2 ); }
bool selectionInfo::pass_CR2l_corridor(int jesType, bool inclTau, bool add2ndLepToMet){

  bool result = true;

  SetJesType( jesType );
	SetIncludeTaus( inclTau );
	SetAdd2ndLep( add2ndLepToMet );

  selectionInfo::v_cut selection_cuts = get_selection_CR2l_corridor();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_CR2l_corridor(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_CR2l) )); // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "passDilep",     (*pass_diLep) ));        // 4) Dilepton selection
	result.push_back( cut( "ge5Jets",       (*pass_ge5_jets) ));     // 5) nGoodJets>=5
	result.push_back( cut( "ge1BJets",      (*pass_ge1_bJets) ));    // 6) nTagJets>=1
	result.push_back( cut( "ge250met",      (*pass_ge250_met) ));    // 7) met>250.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 8) mt>150.0
	result.push_back( cut( "ge0p5minDPhi",  (*pass_ge0p5_minDPhi) ));// 9) minDPhi(met,j1/j2)>0.5
	result.push_back( cut( "j1noBtag",      (*pass_j1NotBtag) ));    // 10) Leading jet is not b-tagged
	result.push_back( cut( "lt150LepPt",    (*pass_lt150_lep1pt) )); // 11) Leading lepton pT < 150
	result.push_back( cut( "lt2dPhiLepMet", (*pass_lt2_dPhiLepMet)));// 12) dPhi(lep1,MET) < 2.0

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR2l_bulkTTbar(int jesType){ return selectionInfo::pass_CR2l_bulkTTbar( jesType, localAddLep2 ); }
bool selectionInfo::pass_CR2l_bulkTTbar(int jesType, bool add2ndLepToMet){

  bool result = true;

  SetJesType( jesType );
	SetAdd2ndLep( add2ndLepToMet );

  selectionInfo::v_cut selection_cuts = get_selection_CR2l_bulkTTbar();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_CR2l_bulkTTbar(){

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_CR2l_bulkTTbar) )); // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "passDilep",     (*pass_diLep_bulkTTbar) ));  // 4) Dilepton selection
	result.push_back( cut( "passOSleps",    (*pass_oppSign_leps) )); // 5) Opposite sign leptons
	result.push_back( cut( "zWindow",       (*pass_ZWindow_diLepMass) )); // 6) Mll Z-window
	result.push_back( cut( "dilepMass",     (*pass_ge20_diLepMass) )); // 7) Dilepton mass > 20
	result.push_back( cut( "ge2Jets",       (*pass_ge2_jets) ));     // 8) nGoodJets>=2
	result.push_back( cut( "ge50met",       (*pass_ge50_met) ));     // 9) met>50.0

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_SR_loose(int jesType){

  bool result = false;

	SetJesType( jesType );

	selectionInfo::v_cut selection_cuts = get_selection_SR_loose();

  for(selectionInfo::cut thiscut : selection_cuts){
    if(!thiscut.second){ 
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<selectionInfo::cut> selectionInfo::get_selection_SR_loose() {

	std::vector<cut> result;

	result.push_back( cut( "dataFilter",    (*pass_metFilter) ));    // 1) Data Filter
	result.push_back( cut( "trigger",       (*pass_trigger_SR) ));   // 2) Trigger
	result.push_back( cut( "goodVertex",    (*pass_goodVtx) ));      // 3) Good Vertex
	result.push_back( cut( "ge2Jets",       (*pass_ge2_jets) ));     // 4) nGoodJets>=2
	result.push_back( cut( "ge1BJets",      (*pass_ge1_bJets) ));    // 5) nTagJets>=1
	result.push_back( cut( "ge150met",      (*pass_ge150_met) ));    // 6) met>150.0
	result.push_back( cut( "ge150MT",       (*pass_ge150_mt) ));     // 7) mt>150.0
	result.push_back( cut( "ge0p5minDPhi",  (*pass_ge0p5_minDPhi) ));// 8) minDPhi(met,j1/j2)>0.5

	return result;
}

//////////////////////////////////////////////////////////////////////
