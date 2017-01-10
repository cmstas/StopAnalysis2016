#include "selectionInfo.h"

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
  result->GetXaxis()->SetBinLabel(12, "ge0p8_minDPhi" );

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

  bool temp_result=false;

  // 1) Data Filter
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result=true;
  else{
    if( babyAnalyzer.filt_met() &&
	babyAnalyzer.filt_badChargedCandidateFilter() &&
	babyAnalyzer.filt_badMuonFilter()                ) temp_result=true;
  }
  result.push_back(temp_result);


  // 2) Trigger
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result = true;
  else{
    if( (babyAnalyzer.HLT_SingleEl() && abs(babyAnalyzer.lep1_pdgid())==11) ||
	(babyAnalyzer.HLT_SingleMu() && abs(babyAnalyzer.lep1_pdgid())==13) ||
	(babyAnalyzer.HLT_MET())        ) temp_result = true;
  }
  result.push_back(temp_result);


  // 3) Good Vertex
  temp_result=false;
  if( babyAnalyzer.nvtxs()>=1 ) temp_result = true;
  result.push_back(temp_result);

  
  // 4) ==1 selected lepton
  temp_result=false;
  if( babyAnalyzer.ngoodleps()==1 ) temp_result = true;
  result.push_back(temp_result);


  // 5) ==0 veto leptons
  temp_result=false;
  if( babyAnalyzer.nvetoleps()==1 ) temp_result = true;
  result.push_back(temp_result);
  
  /*
  // 4) ==1 selected lepton
  temp_result=false;
  if( (babyAnalyzer.ngoodleps()==1) ||
      (babyAnalyzer.ngoodleps()>1 &&
       ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())<=0.01) ) temp_result = true;
  result.push_back(temp_result);


  // 5) ==0 veto leptons
  temp_result=false;
  if( (babyAnalyzer.nvetoleps()==1) ||
    (babyAnalyzer.nvetoleps()>1 &&
     ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())<=0.01) ) temp_result = true;
  result.push_back(temp_result);
  */
  
  // 6) Track Veto
  temp_result=false;
  if( babyAnalyzer.PassTrackVeto() ) temp_result = true;
  result.push_back(temp_result);


  // 7) Tau Veto
  temp_result=false;
  if( babyAnalyzer.PassTauVeto() ) temp_result = true;
  result.push_back(temp_result);


  // 8) nGoodJets>=2
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodjets()>=2 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodjets()>=2 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodjets()>=2 ) temp_result = true;
  }
  result.push_back(temp_result);

  
  // 9) nTagJets>=1
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodbtags()>=1 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodbtags()>=1 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodbtags()>=1 ) temp_result = true;
  }
  result.push_back(temp_result);


  // 10) met>150.0
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.pfmet_jup()>=150.0 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.pfmet_jdown()>=150.0 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.pfmet()>=150.0 ) temp_result = true;
  }
  result.push_back(temp_result);
 

  // 11) mt>150.0
  temp_result=false;
  if( jesType==1 ){
    if( babyAnalyzer.mt_met_lep_jup()>=150.0 ) temp_result = true;
  }
  else if( jesType==-1 ){
    if( babyAnalyzer.mt_met_lep_jdown()>=150.0 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.mt_met_lep()>=150.0 ) temp_result = true;
  }
  result.push_back(temp_result);


  // 12) minDPhi(met,j1/j2)>0.5
  temp_result=false;
  if( jesType==1 ){
    if( babyAnalyzer.mindphi_met_j1_j2_jup()>=0.5 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.mindphi_met_j1_j2_jdown()>=0.5 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.mindphi_met_j1_j2()>=0.5 ) temp_result = true;
  }
  result.push_back(temp_result);


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
  result->GetXaxis()->SetBinLabel(12, "ge0p8_minDPhi" );

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

  bool temp_result=false;

  // 1) Data Filter
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result=true;
  else{
    if( babyAnalyzer.filt_met() &&
	babyAnalyzer.filt_badChargedCandidateFilter() &&
	babyAnalyzer.filt_badMuonFilter()                 ) temp_result=true;
  }
  result.push_back(temp_result);


  // 2) Trigger
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result = true;
  else{
    if( (babyAnalyzer.HLT_SingleEl() && abs(babyAnalyzer.lep1_pdgid())==11) ||
	(babyAnalyzer.HLT_SingleMu() && abs(babyAnalyzer.lep1_pdgid())==13) ||
	(babyAnalyzer.HLT_MET())        ) temp_result = true;
  }
  result.push_back(temp_result);


  // 3) Good Vertex
  temp_result=false;
  if( babyAnalyzer.nvtxs()>=1 ) temp_result = true;
  result.push_back(temp_result);

  
  // 4) ==1 selected lepton
  temp_result=false;
  if( babyAnalyzer.ngoodleps()==1 ) temp_result = true;
  result.push_back(temp_result);


  // 5) ==0 veto leptons
  temp_result=false;
  if( babyAnalyzer.nvetoleps()==1 ) temp_result = true;
  result.push_back(temp_result);
  
  /*
  // 4) ==1 selected lepton
  temp_result=false;
  if( (babyAnalyzer.ngoodleps()==1) ||
      (babyAnalyzer.ngoodleps()>1 &&
       ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())<=0.01) ) temp_result = true;
  result.push_back(temp_result);


  // 5) ==0 veto leptons
  temp_result=false;
  if( (babyAnalyzer.nvetoleps()==1) ||
    (babyAnalyzer.nvetoleps()>1 &&
     ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())<=0.01) ) temp_result = true;
  result.push_back(temp_result);
  */

  // 6) Track Veto
  temp_result=false;
  if( babyAnalyzer.PassTrackVeto() ) temp_result = true;
  result.push_back(temp_result);


  // 7) Tau Veto
  temp_result=false;
  if( babyAnalyzer.PassTauVeto() ) temp_result = true;
  result.push_back(temp_result);


  // 8) nGoodJets>=2
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodjets()>=2 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodjets()>=2 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodjets()>=2 ) temp_result = true;
  }
  result.push_back(temp_result);

  
  // 9) nTagJets==0
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodbtags()==0 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodbtags()==0 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodbtags()==0 ) temp_result = true;
  }
  result.push_back(temp_result);


  // 10) met>150.0
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.pfmet_jup()>=150.0 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.pfmet_jdown()>=150.0 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.pfmet()>=150.0 ) temp_result = true;
  }
  result.push_back(temp_result);
 

  // 11) mt>150.0
  temp_result=false;
  if( jesType==1 ){
    if( babyAnalyzer.mt_met_lep_jup()>=150.0 ) temp_result = true;
  }
  else if( jesType==-1 ){
    if( babyAnalyzer.mt_met_lep_jdown()>=150.0 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.mt_met_lep()>=150.0 ) temp_result = true;
  }
  result.push_back(temp_result);


  // 12) minDPhi(met,j1/j2)>0.5
  temp_result=false;
  if( jesType==1 ){
    if( babyAnalyzer.mindphi_met_j1_j2_jup()>=0.5 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.mindphi_met_j1_j2_jdown()>=0.5 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.mindphi_met_j1_j2()>=0.5 ) temp_result = true;
  }
  result.push_back(temp_result);


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
  result->GetXaxis()->SetBinLabel(12, "ge0p8_minDPhi" );

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

  bool temp_result=false;

  // 1) Data Filter
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result=true;
  else{
    if( babyAnalyzer.filt_met() &&
	babyAnalyzer.filt_badChargedCandidateFilter() &&
	babyAnalyzer.filt_badMuonFilter()                 ) temp_result=true;
  }
  result.push_back(temp_result);


  // 2) Trigger
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result = true;
  else{
    if( (babyAnalyzer.HLT_SingleEl() && abs(babyAnalyzer.lep1_pdgid())==11) ||
	(babyAnalyzer.HLT_SingleMu() && abs(babyAnalyzer.lep1_pdgid())==13) ||
	(babyAnalyzer.HLT_MET())        ) temp_result = true;
  }
  result.push_back(temp_result);


  // 3) Good Vertex
  temp_result=false;
  if( babyAnalyzer.nvtxs()>=1 ) temp_result = true;
  result.push_back(temp_result);

  
  // 4) ==1 selected lepton
  temp_result=false;
  if( babyAnalyzer.ngoodleps()==1 ) temp_result = true;
  result.push_back(temp_result);


  // 5) ==0 veto leptons
  temp_result=false;
  if( babyAnalyzer.nvetoleps()==1 ) temp_result = true;
  result.push_back(temp_result);
  
  /*
  // 4) ==1 selected lepton
  temp_result=false;
  if( (babyAnalyzer.ngoodleps()==1) ||
      (babyAnalyzer.ngoodleps()>1 &&
       ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())<=0.01) ) temp_result = true;
  result.push_back(temp_result);


  // 5) ==0 veto leptons
  temp_result=false;
  if( (babyAnalyzer.nvetoleps()==1) ||
    (babyAnalyzer.nvetoleps()>1 &&
     ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())<=0.01) ) temp_result = true;
  result.push_back(temp_result);
  */

  // 6) Track Veto
  temp_result=false;
  if( babyAnalyzer.PassTrackVeto() ) temp_result = true;
  result.push_back(temp_result);


  // 7) Tau Veto
  temp_result=false;
  if( babyAnalyzer.PassTauVeto() ) temp_result = true;
  result.push_back(temp_result);


  // 8) nGoodJets>=2
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodjets()>=2 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodjets()>=2 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodjets()>=2 ) temp_result = true;
  }
  result.push_back(temp_result);

  
  // 9) nTagJets==0, include tight tagging requirement for high mlb bins
  temp_result=false;

  int nTightTags = 0;
  double tight_wp = 0.935;
  vector<float> jet_csvv2 = babyAnalyzer.ak4pfjets_CSV();
  if( jesType==1 )  jet_csvv2 = babyAnalyzer.jup_ak4pfjets_CSV();
  if( jesType==-1 ) jet_csvv2 = babyAnalyzer.jdown_ak4pfjets_CSV();
  for(int iJet=0; iJet<(int)jet_csvv2.size(); iJet++){
    if( jet_csvv2[iJet] >= tight_wp ) nTightTags++;
  }

  int nMedTags = babyAnalyzer.ngoodbtags();
  if(jesType==1)  nMedTags = babyAnalyzer.jup_ngoodbtags();
  if(jesType==-1) nMedTags = babyAnalyzer.jdown_ngoodbtags();
 
  double mlb = babyAnalyzer.Mlb_closestb();

  if( (nMedTags==0) || 
      (nMedTags>=1 && nTightTags==0 && mlb>175.0) ) temp_result = true;

  result.push_back(temp_result);


  // 10) met>150.0
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.pfmet_jup()>=150.0 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.pfmet_jdown()>=150.0 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.pfmet()>=150.0 ) temp_result = true;
  }
  result.push_back(temp_result);
 

  // 11) mt>150.0
  temp_result=false;
  if( jesType==1 ){
    if( babyAnalyzer.mt_met_lep_jup()>=150.0 ) temp_result = true;
  }
  else if( jesType==-1 ){
    if( babyAnalyzer.mt_met_lep_jdown()>=150.0 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.mt_met_lep()>=150.0 ) temp_result = true;
  }
  result.push_back(temp_result);


  // 12) minDPhi(met,j1/j2)>0.5
  temp_result=false;
  if( jesType==1 ){
    if( babyAnalyzer.mindphi_met_j1_j2_jup()>=0.5 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.mindphi_met_j1_j2_jdown()>=0.5 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.mindphi_met_j1_j2()>=0.5 ) temp_result = true;
  }
  result.push_back(temp_result);


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
  result->GetXaxis()->SetBinLabel(9, "ge0p8_minDPhi" );
 
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

  bool temp_result=false;

  // 1) Data Filter
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result=true;
  else{
    if( babyAnalyzer.filt_met() &&
	babyAnalyzer.filt_badChargedCandidateFilter() &&
	babyAnalyzer.filt_badMuonFilter()                 ) temp_result=true;
  }
  result.push_back(temp_result);


  // 2) Trigger
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result = true;
  else{
    if( ( babyAnalyzer.HLT_SingleEl() && (abs(babyAnalyzer.lep1_pdgid())==11 || abs(babyAnalyzer.lep2_pdgid())==11) ) ||
	( babyAnalyzer.HLT_SingleMu() && (abs(babyAnalyzer.lep1_pdgid())==13 || abs(babyAnalyzer.lep2_pdgid())==13) ) ||
	( babyAnalyzer.HLT_MET())        ) temp_result = true;
  }
  result.push_back(temp_result);


  // 3) Good Vertex
  temp_result=false;
  if( babyAnalyzer.nvtxs()>=1 ) temp_result = true;
  result.push_back(temp_result);

  
  // 4) diLepton
  temp_result=false;
  if( inclTau ){
    if( (babyAnalyzer.ngoodleps()>=2)        ||
	(babyAnalyzer.ngoodleps()==1 && 
	 babyAnalyzer.nvetoleps()>=2 && 
	 babyAnalyzer.lep2_p4().Pt()>10.0 )  ||
	(babyAnalyzer.ngoodleps()==1 && 
	 (!babyAnalyzer.PassTrackVeto() || 
	  !babyAnalyzer.PassTauVeto())     )     ) temp_result = true;
    
  }
  else{
    if( (babyAnalyzer.ngoodleps()>=2)        ||
	(babyAnalyzer.ngoodleps()==1 && 
	 babyAnalyzer.nvetoleps()>=2 && 
	 babyAnalyzer.lep2_p4().Pt()>10.0 )      ) temp_result = true;
  }
  result.push_back(temp_result);
  
  /*
  // 4) diLepton
  temp_result=false;
  if( inclTau ){
    if( (babyAnalyzer.ngoodleps()>=2 &&
	 ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())>0.01) ||
	(babyAnalyzer.ngoodleps()==1 && babyAnalyzer.nvetoleps()>=2 && babyAnalyzer.lep2_p4().Pt()>10.0 &&
	 ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())>0.01) ||
	(babyAnalyzer.ngoodleps()==1 && 
	 (!babyAnalyzer.PassTrackVeto() || 
	  !babyAnalyzer.PassTauVeto())     )     ) temp_result = true;
    
  }
  else{
    if( (babyAnalyzer.ngoodleps()>=2 &&
	 ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())>0.01) ||
	(babyAnalyzer.ngoodleps()==1 && babyAnalyzer.nvetoleps()>=2 && babyAnalyzer.lep2_p4().Pt()>10.0 &&
	 ROOT::Math::VectorUtil::DeltaR(babyAnalyzer.lep1_p4(),babyAnalyzer.lep2_p4())>0.01) ) temp_result = true;
  }
  result.push_back(temp_result);
  */

  // 5) nGoodJets>=2
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodjets()>=2 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodjets()>=2 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodjets()>=2 ) temp_result = true;
  }
  result.push_back(temp_result);

  
  // 6) nTagJets>=1
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodbtags()>=1 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodbtags()>=1 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodbtags()>=1 ) temp_result = true;
  }
  result.push_back(temp_result);


  // 7) met>150.0
  temp_result=false;
  if( add2ndLepToMet ){
    if( jesType==1){
      if( babyAnalyzer.pfmet_rl_jup()>=150.0 ) temp_result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_rl_jdown()>=150.0 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.pfmet_rl()>=150.0 ) temp_result = true;
    }
  } // end if add2ndLepToMet
  else{
    if( jesType==1){
      if( babyAnalyzer.pfmet_jup()>=150.0 ) temp_result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_jdown()>=150.0 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.pfmet()>=150.0 ) temp_result = true;
    }
  } // end if !add2ndLepToMet
  result.push_back(temp_result);
    

  // 8) mt>150.0
  temp_result=false;
  if( add2ndLepToMet ){
    if( jesType==1 ){
      if( babyAnalyzer.mt_met_lep_rl_jup()>=150.0 ) temp_result = true;
    }
    else if( jesType==-1 ){
      if( babyAnalyzer.mt_met_lep_rl_jdown()>=150.0 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.mt_met_lep_rl()>=150.0 ) temp_result = true;
    }
  }
  else{
    if( jesType==1 ){
      if( babyAnalyzer.mt_met_lep_jup()>=150.0 ) temp_result = true;
    }
    else if( jesType==-1 ){
      if( babyAnalyzer.mt_met_lep_jdown()>=150.0 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.mt_met_lep()>=150.0 ) temp_result = true;
    }
  }
  result.push_back(temp_result);


  // 9) minDPhi(met,j1/j2)>0.5
  temp_result=false;
  if( add2ndLepToMet ){
    if( jesType==1 ){
      if( babyAnalyzer.mindphi_met_j1_j2_rl_jup()>=0.5 ) temp_result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.mindphi_met_j1_j2_rl_jdown()>=0.5 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.mindphi_met_j1_j2_rl()>=0.5 ) temp_result = true;
    }
  }
  else{
    if( jesType==1 ){
      if( babyAnalyzer.mindphi_met_j1_j2_jup()>=0.5 ) temp_result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.mindphi_met_j1_j2_jdown()>=0.5 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.mindphi_met_j1_j2()>=0.5 ) temp_result = true;
    }
  }
  result.push_back(temp_result);


  return result;
}

//////////////////////////////////////////////////////////////////////

TH1D* selectionInfo::get_cutflowHistoTemplate_CR2l_bulkTTbar(){

  TH1D *result = new TH1D("h_cutflow_CR2l_bulkTTbar", "Cutflow, Control Region, 2l bulk ttbar", 10, 0.0, 10.0); 
  result->GetXaxis()->SetBinLabel(1, "data_filter" );
  result->GetXaxis()->SetBinLabel(2, "trigger_diLepton" );
  result->GetXaxis()->SetBinLabel(3, "good_vertex" );
  result->GetXaxis()->SetBinLabel(4, "ge2_leptons" );
  result->GetXaxis()->SetBinLabel(5, "oppSign_leptons" );
  result->GetXaxis()->SetBinLabel(6, "leptonFlavour" );
  result->GetXaxis()->SetBinLabel(7, "zMassWindow" );
  result->GetXaxis()->SetBinLabel(8, "diLeptonMass" );
  result->GetXaxis()->SetBinLabel(9, "ge2_jets" );
  result->GetXaxis()->SetBinLabel(10, "ge50_met" );
  
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

bool selectionInfo::pass_CR2l_bulkTTbar(int jesType, int lepFlavour, bool add2ndLepToMet){

  bool result = false;

  std::vector<bool> result_chain = get_selectionResults_CR2l_bulkTTbar(jesType, lepFlavour, add2ndLepToMet);

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


std::vector<bool> selectionInfo::get_selectionResults_CR2l_bulkTTbar(int jesType, int lepFlavour, bool add2ndLepToMet){

  std::vector<bool> result;

  bool temp_result=false;

  // 1) Data Filter
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result=true;
  else{
    if( babyAnalyzer.filt_met() &&
	babyAnalyzer.filt_badChargedCandidateFilter() &&
	babyAnalyzer.filt_badMuonFilter()                 ) temp_result=true;
  }
  result.push_back(temp_result);


  // 2) Trigger
  temp_result=false;
  if( !babyAnalyzer.is_data() ) temp_result = true;
  else{
    if( (babyAnalyzer.HLT_DiEl() &&
	 abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==22) ||
	(babyAnalyzer.HLT_DiMu() &&
	 abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==26) ||
	(babyAnalyzer.HLT_MuE()  &&
	 abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==24)    ) temp_result = true;
  }
  result.push_back(temp_result);


  // 3) Good Vertex
  temp_result=false;
  if( babyAnalyzer.nvtxs()>=1 ) temp_result = true;
  result.push_back(temp_result);


  // 4) diLepton
  temp_result=false;
  if( babyAnalyzer.lep1_p4().Pt()>30.0 && 
      babyAnalyzer.lep2_p4().Pt()>15.0 &&
      babyAnalyzer.lep1_MiniIso()<0.1 &&
      babyAnalyzer.lep2_MiniIso()<0.1 &&
      ( (abs(babyAnalyzer.lep1_pdgid())==13 && 
	 babyAnalyzer.lep1_passTightID()        ) || 
	(abs(babyAnalyzer.lep1_pdgid())==11 && 
	 fabs(babyAnalyzer.lep1_p4().Eta())<1.4442 && 
	 babyAnalyzer.lep1_passMediumID()             ) ) &&
      ( (abs(babyAnalyzer.lep2_pdgid())==13 && 
	 babyAnalyzer.lep2_passTightID()       ) || 
	(abs(babyAnalyzer.lep2_pdgid())==11 && 
	 fabs(babyAnalyzer.lep2_p4().Eta())<1.4442 && 
	 babyAnalyzer.lep2_passMediumID()             ) )    ) temp_result = true;
  result.push_back(temp_result);


  // 5) Opposite sign charge leptons
  temp_result=false;
  if( babyAnalyzer.lep1_pdgid()*babyAnalyzer.lep2_pdgid()<0.0 ) temp_result = true;
  result.push_back(temp_result);


  // 6) Lepton Flavour
  temp_result=false;
  if( lepFlavour==-1 ) temp_result = true;
  else if( (abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid()))==lepFlavour ) temp_result = true;
  result.push_back(temp_result);


  // 7) zMass Window
  temp_result=false;
  if( (abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid()))==24 ) temp_result = true;
  else if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()>(91.1876+15.0) || 
	   (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()<(91.1876-15.0)    ) temp_result = true; 
  result.push_back(temp_result);

  
  // 8) DiLepton Mass>20.0
  temp_result=false;
  if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()>=20.0 ) temp_result = true;
  result.push_back(temp_result);

  // 9) nGoodJets>=2
  temp_result=false;
  if( jesType==1){
    if( babyAnalyzer.jup_ngoodjets()>=2 ) temp_result = true;
  }
  else if( jesType==-1){
    if( babyAnalyzer.jdown_ngoodjets()>=2 ) temp_result = true;
  }
  else{
    if( babyAnalyzer.ngoodjets()>=2 ) temp_result = true;
  }
  result.push_back(temp_result);

  
  // 10) met>50.0
  temp_result=false;
  if( add2ndLepToMet ){
    if( jesType==1){
      if( babyAnalyzer.pfmet_rl_jup()>=50.0 ) temp_result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_rl_jdown()>=50.0 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.pfmet_rl()>=50.0 ) temp_result = true;
    }
  } // end if add2ndLepToMet
  else{
    if( jesType==1){
      if( babyAnalyzer.pfmet_jup()>=50.0 ) temp_result = true;
    }
    else if( jesType==-1){
      if( babyAnalyzer.pfmet_jdown()>=50.0 ) temp_result = true;
    }
    else{
      if( babyAnalyzer.pfmet()>=50.0 ) temp_result = true;
    }
  } // end if !add2ndLepToMet
  result.push_back(temp_result);
    


  return result;
}

//////////////////////////////////////////////////////////////////////
