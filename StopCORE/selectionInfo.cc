#include "selectionInfo.h"

// These variables can only be used within selectionInfo.cc, but they can be set from outside using the functions below
static int localJesType = 0;
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
	babyAnalyzer.filt_badMuonFilter()     ) result = true;
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

bool selectionInfo::pass_diLep(){ return selectionInfo::pass_diLep( localIncludeTaus ); }

bool selectionInfo::pass_diLep(bool inclTau){
  bool result = false;
  if( inclTau ){
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

bool selectionInfo::pass_ge20_diLepMass(){
  bool result = false;
  if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()>=20.0 ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge2_jets(){ return selectionInfo::pass_ge2_jets( localJesType ); }
bool selectionInfo::pass_ge2_jets(int jesType){
  bool result = false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodjets()>=2 ) result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodjets()>=2 ) result = true;
  }
  else{
    if( babyAnalyzer.ngoodjets()>=2 ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge1_bJets(){ return selectionInfo::pass_ge1_bJets( localJesType ); }
bool selectionInfo::pass_ge1_bJets(int jesType){
  bool result = false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodbtags()>=1 ) result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodbtags()>=1 ) result = true;
  }
  else{
    if( babyAnalyzer.ngoodbtags()>=1 ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ee0_bJets(){ return selectionInfo::pass_ee0_bJets( localJesType ); }
bool selectionInfo::pass_ee0_bJets(int jesType){
  bool result = false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodbtags()==0 ) result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodbtags()==0 ) result = true;
  }
  else{
    if( babyAnalyzer.ngoodbtags()==0 ) result = true;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ee0_bJets_tightBTagHighMlb(){ return selectionInfo::pass_ee0_bJets_tightBTagHighMlb( localJesType ); }
bool selectionInfo::pass_ee0_bJets_tightBTagHighMlb(int jesType){
  bool result = false;
  int nTightTags = babyAnalyzer.ntightbtags();
  if(jesType==1)  nTightTags = babyAnalyzer.jup_ntightbtags();
  if(jesType==-1) nTightTags = babyAnalyzer.jdown_ntightbtags();
  int nMedTags = babyAnalyzer.ngoodbtags();
  if(jesType==1)  nMedTags = babyAnalyzer.jup_ngoodbtags();
  if(jesType==-1) nMedTags = babyAnalyzer.jdown_ngoodbtags();
  double mlb = babyAnalyzer.Mlb_closestb();
  if( (nMedTags==0) || 
      (nMedTags>=1 && nTightTags==0 && mlb>175.0) ) result = true;
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge50_met(){ return selectionInfo::pass_ge50_met( localJesType, localAddLep2 ); }
bool selectionInfo::pass_ge50_met(int jesType, bool add2ndLepToMet){
  bool result = false;
  double metCut = 50.0;
  if( add2ndLepToMet ){
    if( jesType==1){
      if( babyAnalyzer.pfmet_rl_jup()>=metCut ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_rl_jdown()>=metCut ) result = true;
    }
    else{
      if( babyAnalyzer.pfmet_rl()>=metCut ) result = true;
    }
  } // end if add2ndLepToMet
  else{
    if( jesType==1){
      if( babyAnalyzer.pfmet_jup()>=metCut ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_jdown()>=metCut ) result = true;
    }
    else{
      if( babyAnalyzer.pfmet()>=metCut ) result = true;
    }
  } // end if !add2ndLepToMet
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge150_met(){ return selectionInfo::pass_ge150_met( localJesType, localAddLep2 ); }
bool selectionInfo::pass_ge150_met(int jesType, bool add2ndLepToMet){
  bool result = false;
  double metCut = 150.0;
  if( add2ndLepToMet ){
    if( jesType==1){
      if( babyAnalyzer.pfmet_rl_jup()>=metCut ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_rl_jdown()>=metCut ) result = true;
    }
    else{
      if( babyAnalyzer.pfmet_rl()>=metCut ) result = true;
    }
  } // end if add2ndLepToMet
  else{
    if( jesType==1){
      if( babyAnalyzer.pfmet_jup()>=metCut ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_jdown()>=metCut ) result = true;
    }
    else{
      if( babyAnalyzer.pfmet()>=metCut ) result = true;
    }
  } // end if !add2ndLepToMet
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge150_mt(){ return selectionInfo::pass_ge150_mt( localJesType, localAddLep2 ); }
bool selectionInfo::pass_ge150_mt(int jesType, bool add2ndLepToMet){
  bool result = false;
  double mtCut = 150.0;
  if( add2ndLepToMet ){
    if( jesType==1 ){
      if( babyAnalyzer.mt_met_lep_rl_jup()>=mtCut ) result = true;
    }
    else if( jesType==-1 ){
      if( babyAnalyzer.mt_met_lep_rl_jdown()>=mtCut ) result = true;
    }
    else{
      if( babyAnalyzer.mt_met_lep_rl()>=mtCut ) result = true;
    }
  }
  else{
    if( jesType==1 ){
      if( babyAnalyzer.mt_met_lep_jup()>=mtCut ) result = true;
    }
    else if( jesType==-1 ){
      if( babyAnalyzer.mt_met_lep_jdown()>=mtCut ) result = true;
    }
    else{
      if( babyAnalyzer.mt_met_lep()>=mtCut ) result = true;
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_ge0p5_minDPhi(){ return selectionInfo::pass_ge0p5_minDPhi( localJesType, localAddLep2 ); }
bool selectionInfo::pass_ge0p5_minDPhi(int jesType, bool add2ndLepToMet){
  bool result = false;
  double minDPhiCut = 0.5;
  if( add2ndLepToMet ){
    if( jesType==1 ){
      if( babyAnalyzer.mindphi_met_j1_j2_rl_jup()>=minDPhiCut ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.mindphi_met_j1_j2_rl_jdown()>=minDPhiCut ) result = true;
    }
    else{
      if( babyAnalyzer.mindphi_met_j1_j2_rl()>=minDPhiCut ) result = true;
    }
  }
  else{
    if( jesType==1 ){
      if( babyAnalyzer.mindphi_met_j1_j2_jup()>=minDPhiCut ) result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.mindphi_met_j1_j2_jdown()>=minDPhiCut ) result = true;
    }
    else{
      if( babyAnalyzer.mindphi_met_j1_j2()>=minDPhiCut ) result = true;
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate_SR(){

  TH1D* result = new TH1D("h_cutflow_SR", "Cutflow, Signal Region", 12, 0.0, 12.0); 
  result->GetXaxis()->SetBinLabel(1, "data_filter" );
  result->GetXaxis()->SetBinLabel(2, "trigger_singleLep_OR_MET" );
  result->GetXaxis()->SetBinLabel(3, "good_vertex" );
  result->GetXaxis()->SetBinLabel(4, "ee1_selected_lepton" );
  result->GetXaxis()->SetBinLabel(5, "ee0_veto_leptons" );
  result->GetXaxis()->SetBinLabel(6, "iso_track_veto" );
  result->GetXaxis()->SetBinLabel(7, "tau_veto" );
  result->GetXaxis()->SetBinLabel(8, "ge2_jets" );
  result->GetXaxis()->SetBinLabel(9, "ge1_bJets" );
  result->GetXaxis()->SetBinLabel(10, "ge150_met" );
  result->GetXaxis()->SetBinLabel(11, "ge150_mt" );
  result->GetXaxis()->SetBinLabel(12, "ge0p5_minDPhi" );

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<TH1D*> selectionInfo::get_cutflowHistoTemplate_nMinus1_SR(){

  vector<TH1D*> result;
  
  TH1D *h_temp = get_cutflowHistoTemplate_SR();
  
  for(int i=1; i<=(int)h_temp->GetNbinsX(); i++){
    std::string name = h_temp->GetName();
    name += "_";
    name += h_temp->GetXaxis()->GetBinLabel(i);
    
    std::string title = h_temp->GetTitle();
    title += ", nMinus1, ";
    title += h_temp->GetXaxis()->GetBinLabel(i);
    
    int nBins  = h_temp->GetNbinsX(); 
    double min = h_temp->GetXaxis()->GetBinLowEdge(1);
    double max = h_temp->GetXaxis()->GetBinUpEdge(h_temp->GetNbinsX());
    TH1D *h_nMinus1 = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    result.push_back(h_nMinus1);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_SR(){ return selectionInfo::pass_SR( localJesType ); }
bool selectionInfo::pass_SR(int jesType){

  bool result = false;

  std::vector<bool> result_chain = get_selectionResults_SR(jesType);

  for(int i=0; i<(int)result_chain.size(); i++){
    if(result_chain[i]) result=true;
    else{
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<bool> selectionInfo::get_selectionResults_SR(int jesType){

  std::vector<bool> result;

  // 1) Data Filter
  result.push_back( pass_metFilter() );

  // 2) Trigger
  result.push_back( pass_trigger_SR() );
  
  // 3) Good Vertex
  result.push_back( pass_goodVtx() );

  // 4) ==1 selected lepton
  result.push_back( pass_ee1_sel_lep() );

  // 5) ==0 veto leptons
  result.push_back( pass_ee0_veto_lep() );
    
  // 6) Track Veto
  result.push_back( pass_trackVeto() );
  
  // 7) Tau Veto
  result.push_back( pass_tauVeto() );
  
  // 8) nGoodJets>=2
  result.push_back( pass_ge2_jets(jesType) );
  
  // 9) nTagJets>=1
  result.push_back( pass_ge1_bJets(jesType) );
  
  // 10) met>150.0
  result.push_back( pass_ge150_met(jesType) );
  
  // 11) mt>150.0
  result.push_back( pass_ge150_mt(jesType) );
  
  // 12) minDPhi(met,j1/j2)>0.5
  result.push_back( pass_ge0p5_minDPhi(jesType) );
  
  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate_CR0b(){

  TH1D *result = new TH1D("h_cutflow_CR0b", "Cutflow, Control Region, 0b", 12, 0.0, 12.0); 
  result->GetXaxis()->SetBinLabel(1, "data_filter" );
  result->GetXaxis()->SetBinLabel(2, "trigger_singleLep_OR_MET" );
  result->GetXaxis()->SetBinLabel(3, "good_vertex" );
  result->GetXaxis()->SetBinLabel(4, "ee1_selected_lepton" );
  result->GetXaxis()->SetBinLabel(5, "ee0_veto_leptons" );
  result->GetXaxis()->SetBinLabel(6, "iso_track_veto" );
  result->GetXaxis()->SetBinLabel(7, "tau_veto" );
  result->GetXaxis()->SetBinLabel(8, "ge2_jets" );
  result->GetXaxis()->SetBinLabel(9, "ee0_bJets" );
  result->GetXaxis()->SetBinLabel(10, "ge150_met" );
  result->GetXaxis()->SetBinLabel(11, "ge150_mt" );
  result->GetXaxis()->SetBinLabel(12, "ge0p5_minDPhi" );

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<TH1D*> selectionInfo::get_cutflowHistoTemplate_nMinus1_CR0b(){

  vector<TH1D*> result;
  
  TH1D *h_temp = get_cutflowHistoTemplate_CR0b();
  
  for(int i=1; i<=(int)h_temp->GetNbinsX(); i++){
    std::string name = h_temp->GetName();
    name += "_";
    name += h_temp->GetXaxis()->GetBinLabel(i);
    
    std::string title = h_temp->GetTitle();
    title += ", nMinus1, ";
    title += h_temp->GetXaxis()->GetBinLabel(i);
    
    int nBins  = h_temp->GetNbinsX(); 
    double min = h_temp->GetXaxis()->GetBinLowEdge(1);
    double max = h_temp->GetXaxis()->GetBinUpEdge(h_temp->GetNbinsX());
    TH1D *h_nMinus1 = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    result.push_back(h_nMinus1);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR0b(){ return selectionInfo::pass_CR0b( localJesType ); }
bool selectionInfo::pass_CR0b(int jesType){

  bool result = false;

  std::vector<bool> result_chain = get_selectionResults_CR0b(jesType);

  for(int i=0; i<(int)result_chain.size(); i++){
    if(result_chain[i]) result=true;
    else{
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<bool> selectionInfo::get_selectionResults_CR0b(int jesType){

  std::vector<bool> result;
  
  // 1) Data Filter
  result.push_back( pass_metFilter() );
  
  // 2) Trigger
  result.push_back( pass_trigger_SR() );
  
  // 3) Good Vertex
  result.push_back( pass_goodVtx() );
  
  // 4) ==1 selected lepton
  result.push_back( pass_ee1_sel_lep() );

  // 5) ==0 veto leptons
  result.push_back( pass_ee0_veto_lep() );
  
  // 6) Track Veto
  result.push_back( pass_trackVeto() );
  
  // 7) Tau Veto
  result.push_back( pass_tauVeto() );
  
  // 8) nGoodJets>=2
  result.push_back( pass_ge2_jets(jesType) );
    
  // 9) nTagJets==0
  result.push_back( pass_ee0_bJets(jesType) );
  
  // 10) met>150.0
  result.push_back( pass_ge150_met(jesType) );
  
  // 11) mt>150.0
  result.push_back( pass_ge150_mt(jesType) );

  // 12) minDPhi(met,j1/j2)>0.5
  result.push_back( pass_ge0p5_minDPhi(jesType) );
  
  return result;
}


//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate_CR0b_tightBTagHighMlb(){

  TH1D *result = new TH1D("h_cutflow_CR0b_tightBTagHighMlb", "Cutflow, Control Region, 0b, with tight b-tagging for high mlb", 12, 0.0, 12.0); 
  result->GetXaxis()->SetBinLabel(1, "data_filter" );
  result->GetXaxis()->SetBinLabel(2, "trigger_singleLep_OR_MET" );
  result->GetXaxis()->SetBinLabel(3, "good_vertex" );
  result->GetXaxis()->SetBinLabel(4, "ee1_selected_lepton" );
  result->GetXaxis()->SetBinLabel(5, "ee0_veto_leptons" );
  result->GetXaxis()->SetBinLabel(6, "iso_track_veto" );
  result->GetXaxis()->SetBinLabel(7, "tau_veto" );
  result->GetXaxis()->SetBinLabel(8, "ge2_jets" );
  result->GetXaxis()->SetBinLabel(9, "ee0_bJets_tightBTagHighMlb" );
  result->GetXaxis()->SetBinLabel(10, "ge150_met" );
  result->GetXaxis()->SetBinLabel(11, "ge150_mt" );
  result->GetXaxis()->SetBinLabel(12, "ge0p5_minDPhi" );

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<TH1D*> selectionInfo::get_cutflowHistoTemplate_nMinus1_CR0b_tightBTagHighMlb(){

  vector<TH1D*> result;
  
  TH1D *h_temp = get_cutflowHistoTemplate_CR0b_tightBTagHighMlb();
  
  for(int i=1; i<=(int)h_temp->GetNbinsX(); i++){
    std::string name = h_temp->GetName();
    name += "_";
    name += h_temp->GetXaxis()->GetBinLabel(i);
    
    std::string title = h_temp->GetTitle();
    title += ", nMinus1, ";
    title += h_temp->GetXaxis()->GetBinLabel(i);
    
    int nBins  = h_temp->GetNbinsX(); 
    double min = h_temp->GetXaxis()->GetBinLowEdge(1);
    double max = h_temp->GetXaxis()->GetBinUpEdge(h_temp->GetNbinsX());
    TH1D *h_nMinus1 = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    result.push_back(h_nMinus1);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR0b_tightBTagHighMlb(){ return selectionInfo::pass_CR0b_tightBTagHighMlb( localJesType ); }
bool selectionInfo::pass_CR0b_tightBTagHighMlb(int jesType){

  bool result = false;

  std::vector<bool> result_chain = get_selectionResults_CR0b_tightBTagHighMlb(jesType);

  for(int i=0; i<(int)result_chain.size(); i++){
    if(result_chain[i]) result=true;
    else{
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<bool> selectionInfo::get_selectionResults_CR0b_tightBTagHighMlb(int jesType){

  std::vector<bool> result;

  // 1) Data Filter
  result.push_back( pass_metFilter() );
  
  // 2) Trigger
  result.push_back( pass_trigger_SR() );
  
  // 3) Good Vertex
  result.push_back( pass_goodVtx() );
  
  // 4) ==1 selected lepton
  result.push_back( pass_ee1_sel_lep() );
  
  // 5) ==0 veto leptons
  result.push_back( pass_ee0_veto_lep() );
  
  // 6) Track Veto
  result.push_back( pass_trackVeto() );
  
  // 7) Tau Veto
  result.push_back( pass_tauVeto() );
  
  // 8) nGoodJets>=2
  result.push_back( pass_ge2_jets(jesType) );
  
  // 9) nTagJets==0, include tight tagging requirement for high mlb bins
  result.push_back( pass_ee0_bJets_tightBTagHighMlb(jesType) );
  
  // 10) met>150.0
  result.push_back( pass_ge150_met(jesType) );
  
  // 11) mt>150.0
  result.push_back( pass_ge150_mt(jesType) );
  
  // 12) minDPhi(met,j1/j2)>0.5
  result.push_back( pass_ge0p5_minDPhi(jesType) );
  
  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate_CR2l(){

  TH1D *result = new TH1D("h_cutflow_CR2l", "Cutflow, Control Region, 2l", 9, 0.0, 9.0); 
  result->GetXaxis()->SetBinLabel(1, "data_filter" );
  result->GetXaxis()->SetBinLabel(2, "trigger_singleLep_OR_MET" );
  result->GetXaxis()->SetBinLabel(3, "good_vertex" );
  result->GetXaxis()->SetBinLabel(4, "ge2_leptons" );
  result->GetXaxis()->SetBinLabel(5, "ge2_jets" );
  result->GetXaxis()->SetBinLabel(6, "ge1_bJets" );
  result->GetXaxis()->SetBinLabel(7, "ge150_met" );
  result->GetXaxis()->SetBinLabel(8, "ge150_mt" );
  result->GetXaxis()->SetBinLabel(9, "ge0p5_minDPhi" );
 
  return result;
}

//////////////////////////////////////////////////////////////////////

vector<TH1D*> selectionInfo::get_cutflowHistoTemplate_nMinus1_CR2l(){

  vector<TH1D*> result;
  
  TH1D *h_temp = get_cutflowHistoTemplate_CR2l();
  
  for(int i=1; i<=(int)h_temp->GetNbinsX(); i++){
    std::string name = h_temp->GetName();
    name += "_";
    name += h_temp->GetXaxis()->GetBinLabel(i);
    
    std::string title = h_temp->GetTitle();
    title += ", nMinus1, ";
    title += h_temp->GetXaxis()->GetBinLabel(i);
    
    int nBins  = h_temp->GetNbinsX(); 
    double min = h_temp->GetXaxis()->GetBinLowEdge(1);
    double max = h_temp->GetXaxis()->GetBinUpEdge(h_temp->GetNbinsX());
    TH1D *h_nMinus1 = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    result.push_back(h_nMinus1);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR2l(){ return selectionInfo::pass_CR2l( localJesType, localIncludeTaus, localAddLep2 ); }
bool selectionInfo::pass_CR2l(int jesType, bool inclTau, bool add2ndLepToMet){

  bool result = false;

  std::vector<bool> result_chain = get_selectionResults_CR2l(jesType, inclTau, add2ndLepToMet);

  for(int i=0; i<(int)result_chain.size(); i++){
    if(result_chain[i]) result=true;
    else{
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////


std::vector<bool> selectionInfo::get_selectionResults_CR2l(int jesType, bool inclTau, bool add2ndLepToMet){

  std::vector<bool> result;
  
  // 1) Data Filter
  result.push_back( pass_metFilter() );
  
  // 2) Trigger
  result.push_back( pass_trigger_CR2l() );
  
  // 3) Good Vertex
  result.push_back( pass_goodVtx() );
  
  // 4) diLepton
  result.push_back( pass_diLep(inclTau) );
    
  // 5) nGoodJets>=2
  result.push_back( pass_ge2_jets(jesType) );
    
  // 6) nTagJets>=1
  result.push_back( pass_ge1_bJets(jesType) );
  
  // 7) met>150.0
  result.push_back( pass_ge150_met(jesType,add2ndLepToMet) );
  
  // 8) mt>150.0
  result.push_back( pass_ge150_mt(jesType,add2ndLepToMet) );
  
  // 9) minDPhi(met,j1/j2)>0.5
  result.push_back( pass_ge0p5_minDPhi(jesType,add2ndLepToMet) );
  
  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate_CR2l_bulkTTbar(){

  TH1D *result = new TH1D("h_cutflow_CR2l_bulkTTbar", "Cutflow, Control Region, 2l bulk ttbar", 9, 0.0, 9.0); 
  result->GetXaxis()->SetBinLabel(1, "data_filter" );
  result->GetXaxis()->SetBinLabel(2, "trigger_diLepton" );
  result->GetXaxis()->SetBinLabel(3, "good_vertex" );
  result->GetXaxis()->SetBinLabel(4, "ge2_leptons" );
  result->GetXaxis()->SetBinLabel(5, "oppSign_leptons" );
  result->GetXaxis()->SetBinLabel(6, "zMassWindow" );
  result->GetXaxis()->SetBinLabel(7, "diLeptonMass" );
  result->GetXaxis()->SetBinLabel(8, "ge2_jets" );
  result->GetXaxis()->SetBinLabel(9, "ge50_met" );
  
  return result;
}

//////////////////////////////////////////////////////////////////////

vector<TH1D*> selectionInfo::get_cutflowHistoTemplate_nMinus1_CR2l_bulkTTbar(){

  vector<TH1D*> result;
  
  TH1D *h_temp = get_cutflowHistoTemplate_CR2l_bulkTTbar();
  
  for(int i=1; i<=(int)h_temp->GetNbinsX(); i++){
    std::string name = h_temp->GetName();
    name += "_";
    name += h_temp->GetXaxis()->GetBinLabel(i);
    
    std::string title = h_temp->GetTitle();
    title += ", nMinus1, ";
    title += h_temp->GetXaxis()->GetBinLabel(i);
    
    int nBins  = h_temp->GetNbinsX(); 
    double min = h_temp->GetXaxis()->GetBinLowEdge(1);
    double max = h_temp->GetXaxis()->GetBinUpEdge(h_temp->GetNbinsX());
    TH1D *h_nMinus1 = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    result.push_back(h_nMinus1);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_CR2l_bulkTTbar(){ return selectionInfo::pass_CR2l_bulkTTbar( localJesType, localAddLep2 ); }
bool selectionInfo::pass_CR2l_bulkTTbar(int jesType, bool add2ndLepToMet){

  bool result = false;

  std::vector<bool> result_chain = get_selectionResults_CR2l_bulkTTbar(jesType, add2ndLepToMet);

  for(int i=0; i<(int)result_chain.size(); i++){
    if(result_chain[i]) result=true;
    else{
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////


std::vector<bool> selectionInfo::get_selectionResults_CR2l_bulkTTbar(int jesType, bool add2ndLepToMet){

  std::vector<bool> result;

  // 1) Data Filter
  result.push_back( pass_metFilter() );
  
  // 2) Trigger
  result.push_back( pass_trigger_CR2l_bulkTTbar() );
  
  // 3) Good Vertex
  result.push_back( pass_goodVtx() );
  
  // 4) diLepton
  result.push_back( pass_diLep_bulkTTbar() );
  
  // 5) Opposite sign charge leptons
  result.push_back( pass_oppSign_leps() );
  
  // 6) zMass Window
  result.push_back( pass_ZWindow_diLepMass() );
  
  // 8) DiLepton Mass>20.0
  result.push_back( pass_ge20_diLepMass() );
  
  // 9) nGoodJets>=2
  result.push_back( pass_ge2_jets(jesType) );
  
  // 10) met>50.0
  result.push_back( pass_ge50_met(jesType,add2ndLepToMet) );
      

  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate_SR_loose(){

  TH1D* result = new TH1D("h_cutflow_SR_loose", "Cutflow, Loose Signal Region", 8, 0.0, 8.0); 
  result->GetXaxis()->SetBinLabel(1, "data_filter" );
  result->GetXaxis()->SetBinLabel(2, "trigger_singleLep_OR_MET" );
  result->GetXaxis()->SetBinLabel(3, "good_vertex" );
  result->GetXaxis()->SetBinLabel(4, "ge2_jets" );
  result->GetXaxis()->SetBinLabel(5, "ge1_bJets" );
  result->GetXaxis()->SetBinLabel(6, "ge150_met" );
  result->GetXaxis()->SetBinLabel(7, "ge150_mt" );
  result->GetXaxis()->SetBinLabel(8, "ge0p5x_minDPhi" );

  return result;
}

//////////////////////////////////////////////////////////////////////

vector<TH1D*> selectionInfo::get_cutflowHistoTemplate_nMinus1_SR_loose(){

  vector<TH1D*> result;
  
  TH1D *h_temp = get_cutflowHistoTemplate_SR_loose();
  
  for(int i=1; i<=(int)h_temp->GetNbinsX(); i++){
    std::string name = h_temp->GetName();
    name += "_";
    name += h_temp->GetXaxis()->GetBinLabel(i);
    
    std::string title = h_temp->GetTitle();
    title += ", nMinus1, ";
    title += h_temp->GetXaxis()->GetBinLabel(i);
    
    int nBins  = h_temp->GetNbinsX(); 
    double min = h_temp->GetXaxis()->GetBinLowEdge(1);
    double max = h_temp->GetXaxis()->GetBinUpEdge(h_temp->GetNbinsX());
    TH1D *h_nMinus1 = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    result.push_back(h_nMinus1);
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::pass_SR_loose(){ return selectionInfo::pass_SR_loose( localJesType ); }
bool selectionInfo::pass_SR_loose(int jesType){

  bool result = false;

  std::vector<bool> result_chain = get_selectionResults_SR_loose(jesType);

  for(int i=0; i<(int)result_chain.size(); i++){
    if(result_chain[i]) result=true;
    else{
      result=false;
      break;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////////////////

std::vector<bool> selectionInfo::get_selectionResults_SR_loose(int jesType){

  std::vector<bool> result;

  // 1) Data Filter
  result.push_back( pass_metFilter() );
  
  // 2) Trigger
  result.push_back( pass_trigger_SR() );
  
  // 3) Good Vertex
  result.push_back( pass_goodVtx() );
  
  // 4) nGoodJets>=2
  result.push_back( pass_ge2_jets(jesType) );
    
  // 5) nTagJets>=1
  result.push_back( pass_ge1_bJets(jesType) );
  
  // 6) met>150.0
  result.push_back( pass_ge150_met(jesType) );
  
  // 7) mt>150.0
  result.push_back( pass_ge150_mt(jesType) );
  
  // 8) minDPhi(met,j1/j2)>0.5
  result.push_back( pass_ge0p5_minDPhi(jesType) );
  
  return result;
}

//////////////////////////////////////////////////////////////////////
