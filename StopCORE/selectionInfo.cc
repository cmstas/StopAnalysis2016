#include "selectionInfo.h"
#include "stop_1l_babyAnalyzer.h"

// ROOT
#include "Riostream.h"

// C
#include <vector>

//////////////////////////////////////////////////////////////////////

selectionInfo::cutUtil::cutUtil( selectionInfo::ID cut ){

  id = cut;
    
  switch( cut ){

  case( k_duplicateRemoval ):
    label = "duplicate_event_removal";
    title = "Duplicate Event Removal";
    tex   = "Duplicate~Event~Removal";
    break;
  
  case( k_dataFilter ):
    label = "data_filter";
    title = "Data Filter";
    tex   = "Data~Filter";
    break;
 
  case( k_trigger_singleLep ):
    label = "trigger_singleLep";
    title = "Trigger, Single Lepton";
    tex   = "Trigger,~Single~Lepton";
    break;

  case( k_trigger_MET ):
    label = "trigger_MET";
    title = "Trigger, MET";
    tex   = "Trigger,~MET";
    break;

  case( k_trigger_singleLep_or_MET ):
    label = "trigger_singleLep_or_MET";
    title = "Trigger, Single Lepton OR MET";
    tex   = "Trigger,~Single~Lepton~OR~MET";
    break;

  case( k_trigger_diLep ):
    label = "trigger_diLep";
    title = "Trigger, diLepton";
    tex   = "Trigger,~diLepton";
    break;

  case( k_goodVtx ):
    label = "trigger_goodVtx";
    title = "Trigger, Good Vertex";
    tex   = "Trigger,~Good~Vertex";
    break;

  case( k_ee1_selLep ):
    label = "ee1_selLep";
    title = "==1 Selected Lepton";
    tex   = "$==1$~Selected~Lepton";
    break;

  case( k_ee0_vetoLep ):
    label = "ee0_vetoLep";
    title = "==1 Veto Leptons";
    tex   = "$==1$,~Veto~Leptons";
    break;

  case( k_trackVeto ):
    label = "trackVeto";
    title = "Isolated Track Veto";
    tex   = "Isolated~Track~Veto";
    break;

  case( k_tauVeto ):
    label = "tauVeto";
    title = "Tau Veto";
    tex   = "$\\tau$~Veto";
    break;
	
  case( k_diLepton ):
    label = "diLepton";
    title = "Di-Lepton";
    tex   = "diLepton";
    break;

  case( k_diLepton_bulkTTbar ):
    label = "diLepton_bulkTTbar";
    title = "diLepton, Bulk TTbar";
    tex   = "diLepton,~Bulk~$t\\bar{t}$";
    break;

  case( k_oppSignLeptons ):
    label = "oppSignLeptons";
    title = "Opposite Sign Charge Leptons";
    tex   = "Opposite~Sign~Charge~Leptons";
    break;

  case( k_zMassWindow ):
    label = "zMassWindow";
    title = "Z Mass Window";
    tex   = "$Z$~Mass~Window";
    break;

  case( k_ge20_diLepMass ):
    label = "ge20_diLepMass";
    title = "diLepton Invariant Mass >=20 GeV";
    tex   = "diLepton~Invasriant~Mass~$\\ge20$~GeV";
    break;

  case( k_ge2_jets ):
    label = "ge2_jets";
    title = ">=2 Jets";
    tex   = "$\\ge2$~jets";
    break;

  case( k_ee0_bJets ):
    label = "ee0_bJets";
    title = "==0 bTagged Jets";
    tex   = "$==0$~b-Tagged~Jets";
    break;

  case( k_ge1_bJets ):
    label = "ge1_bJets";
    title = ">=1 bTagged Jets";
    tex   = "$\\ge1$~b-Tagged~Jets";
    break;
 
  case( k_ge50_met ):
    label = "ge50_met";
    title = "MET>=50 GeV";
    tex   = "$MET\\ge50$~GeV";
    break;

  case( k_ge250_met ):
    label = "ge250_met";
    title = "MET>=250 GeV";
    tex   = "$MET\\ge50$~GeV";
    break;

  case( k_ge150_mt ):
    label = "ge150_mt";
    title = "MT>=150 GeV";
    tex   = "$M_{T}>=150$~GeV";
    break;

  case( k_ge0p8_minDPhi ):
    label = "ge0p8_minDPhi";
    title = "Min DeltaPhi(MET,j1,j2)>0.8";
    tex   = "Min~$\\Delta\\Phi$(MET,j1,j2)$>0.8$";
    break;

  default:
    std::cout << "Could not find cut info from cut enum provided!" << std::endl;
    label = "NO CUT INFO FOUND FROM ENUM PROVIDED";
    title = "NO CUT INFO FOUND FROM ENUM PROVIDED";
    tex   = "NO CUT INFO FOUND FROM ENUM PROVIDED";
    break;

  } // end switch case for selectionInfo::ID

  
}

//////////////////////////////////////////////////////////////////////

selectionInfo::selectionUtil::selectionUtil( vect_id cuts, bool isData ){
  
  v_cuts.clear();
  v_cuts = cuts;

  h_cutflow     = NULL;
  h_cutflow_wgt = NULL;
  vect_cutflow_nMinus1.clear();

  sample_is_data = isData;

  if( sample_is_data ){
    std::cout << "    Loading bad event files" << std::endl;
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/csc2015_Dec01.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/ecalscn1043093_Dec01.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/badResolutionTrack_Jan13.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/muonBadTrack_Jan13.txt");
    std::cout << "      finished!" << std::endl << std::endl;
  }
  
}

//////////////////////////////////////////////////////////////////////

selectionInfo::selectionUtil::~selectionUtil(){

  if( sample_is_data ){
    duplicate_removal::clear_list();
  }
  
  v_cuts.clear();
  vect_cutflow_nMinus1.clear();
   
}

//////////////////////////////////////////////////////////////////////

void selectionInfo::selectionUtil::setupCutflowHistos( TFile *f_out ){
 
  // Cutflow, unweighted
  std::string h_name  = "h__cutflow";
  std::string h_title = "Cutflow, Unweighted Events";

  h_cutflow = new TH1D( h_name.c_str(), h_title.c_str(), (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
  h_cutflow->SetDirectory( f_out );

  for(int iBin=1; iBin<=(int)h_cutflow->GetNbinsX(); iBin++){
    selectionInfo::cutUtil cut_info( v_cuts[iBin-1] );
    h_cutflow->GetXaxis()->SetBinLabel( iBin, cut_info.label.c_str() );
  }


  // Cutflow, weighted
  h_name  = "h__cutflow_wgt";
  h_title = "Cutflow";

  h_cutflow_wgt = new TH1D( h_name.c_str(), h_title.c_str(), (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
  h_cutflow_wgt->SetDirectory( f_out );

  for(int iBin=1; iBin<=(int)h_cutflow_wgt->GetNbinsX(); iBin++){
    selectionInfo::cutUtil cut_info( v_cuts[iBin-1] );
    h_cutflow_wgt->GetXaxis()->SetBinLabel( iBin, cut_info.label.c_str() );
  }

  
  // N-1 Cutflow
  const int nCuts = (int)v_cuts.size();
  TH1D *h_cutflow_Nminus1[nCuts];

  for(int iCut=0; iCut<(int)v_cuts.size(); iCut++){

    selectionInfo::cutUtil cut_info( v_cuts[iCut] );

    h_name  = "h__cutflow_nMinus1__" + cut_info.label;
    h_title = "Cutflow, N-1, " + cut_info.title;

    h_cutflow_Nminus1[iCut] = new TH1D( h_name.c_str(), h_title.c_str(), (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
    h_cutflow_Nminus1[iCut]->SetDirectory( f_out );

    int bin=1;
    for(int jCut=0; jCut<(int)v_cuts.size(); jCut++){
      if( jCut==iCut ) continue;
      selectionInfo::cutUtil cut_info_j( v_cuts[jCut] );
      h_cutflow_Nminus1[iCut]->GetXaxis()->SetBinLabel( bin, cut_info_j.label.c_str() );
      bin++;
    }
    
    h_cutflow_Nminus1[iCut]->GetXaxis()->SetBinLabel( bin, cut_info.label.c_str() );

    vect_cutflow_nMinus1.push_back( h_cutflow_Nminus1[iCut] );

  } // end loop over cuts

    
  return;

}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::selectionUtil::passCut( selectionInfo::ID cut ){

  bool result = false;

  switch( cut ){

  case( k_duplicateRemoval ):
    if( !babyAnalyzer.is_data() ) result = true;
    else{
      duplicate_removal::DorkyEventIdentifier id(babyAnalyzer.run(), babyAnalyzer.evt(), babyAnalyzer.ls());
      if( !(is_duplicate(id)) ) result = true;
    }
    break;
  
  case( k_dataFilter ):
    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if( !(metFilterTxt.eventFails( babyAnalyzer.run(), babyAnalyzer.ls(), babyAnalyzer.evt() )) &&
	  babyAnalyzer.filt_cscbeamhalo() &&
	  babyAnalyzer.filt_eebadsc() &&
	  babyAnalyzer.filt_goodvtx() &&
	  babyAnalyzer.filt_hbhenoise() ) result = true;
    }
    break;
 
  case( k_trigger_singleLep ):

    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if( babyAnalyzer.HLT_SingleEl27() ||
	  babyAnalyzer.HLT_SingleMu20()    ) result = true;
    }
    break;

  case( k_trigger_MET ):
    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if( babyAnalyzer.HLT_MET170() ) result = true;
    }
    break;

  case( k_trigger_singleLep_or_MET ):
    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if( babyAnalyzer.HLT_SingleEl27() ||
	  babyAnalyzer.HLT_SingleMu20() ||
	  babyAnalyzer.HLT_MET170()        ) result = true;
    }
    break;

  case( k_trigger_diLep ):
    if( babyAnalyzer.HLT_DiEl()    || 
	babyAnalyzer.HLT_DiMu()    || 
	babyAnalyzer.HLT_Mu8El17() || 
	babyAnalyzer.HLT_Mu17El12()   ) result = true;
    break;

  case( k_goodVtx ):
    if( babyAnalyzer.nvtxs()>=1 ) result = true;
    break;

  case( k_ee1_selLep ):
    if( babyAnalyzer.ngoodleps()==1 ) result = true;
    break;

  case( k_ee0_vetoLep ):
    if( babyAnalyzer.nvetoleps()==1 ) result = true;
    break;

  case( k_trackVeto ):
    if( babyAnalyzer.PassTrackVeto_v3() ) result = true;
    break;

  case( k_tauVeto ):
    if( babyAnalyzer.PassTauVeto() ) result = true;
    break;
	
  case( k_diLepton ):
    if( (babyAnalyzer.ngoodleps()>=2) ||
	(babyAnalyzer.ngoodleps()==1 && babyAnalyzer.nvetoleps()>=2 && babyAnalyzer.lep2_p4().Pt()>10.0) ||
	(babyAnalyzer.ngoodleps()==1 && !babyAnalyzer.PassTrackVeto_v3()) ||
	(babyAnalyzer.ngoodleps()==1 && !babyAnalyzer.PassTauVeto()) ) result = true;
    break;

  case( k_diLepton_bulkTTbar ):
    if( babyAnalyzer.nlooseleps()>=2     &&
	babyAnalyzer.lep1_p4().Pt()>30.0 && 
	babyAnalyzer.lep2_p4().Pt()>15.0    ) result = true;
    break;

  case( k_oppSignLeptons ):
    if( babyAnalyzer.lep1_charge()*babyAnalyzer.lep2_charge()<0.0 ) result = true;
    break;

  case( k_zMassWindow ):
    if(abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid())==24 ) result = true;
    else if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).Pt()>(91.1876+15.0) || 
	     (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).Pt()<(91.1876-15.0)    ) result = true; 
    break;

  case( k_ge20_diLepMass ):
    if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()>=20.0 ) result = true;
    break;

  case( k_ge2_jets ):
    if( babyAnalyzer.ngoodjets()>=2 ) result = true;
    break;

  case( k_ee0_bJets ):
    if( babyAnalyzer.ngoodbtags()==0 ) result = true;
    break;

  case( k_ge1_bJets ):
    if( babyAnalyzer.ngoodbtags()>=1 ) result = true;
    break;
 
  case( k_ge50_met ):
    if( babyAnalyzer.pfmet()>=50.0 ) result = true;
    break;

  case( k_ge250_met ):
    if( babyAnalyzer.pfmet()>=250.0 ) result = true;
    break;

  case( k_ge150_mt ):
    if( babyAnalyzer.mt_met_lep()>=150.0 ) result = true;
    break;

  case( k_ge0p8_minDPhi ):
    if( babyAnalyzer.mindphi_met_j1_j2()>=0.8 ) result = true;
    break;

  default:
    std::cout << "Could not find cut info from cut enum provided!" << std::endl;
    result = false;
    break;

  } // end switch case for cutInfo_id


  return result;

}

//////////////////////////////////////////////////////////////////////

bool selectionInfo::selectionUtil::passSelection(){

  for(int iCut=0; iCut<(int)v_cuts.size(); iCut++){
    if( !passCut( v_cuts[iCut] ) ) return false;
  }
  return true;

}

//////////////////////////////////////////////////////////////////////

void selectionInfo::selectionUtil::fillCutflowHistos( double wgt ){  
  
  if( !h_cutflow ){
    std::cout << "      Error, must call setupCutflowHistos( TFile *f_out ) before attempting to fill cutflow histogram" << std::endl;
    return;
  }

  // Cutflow, Unweighted
  for(int iCut=0; iCut<(int)v_cuts.size(); iCut++){
    if( passCut( v_cuts[iCut] ) ){
      selectionInfo::cutUtil cut_info( v_cuts[iCut] );
      h_cutflow->Fill( cut_info.label.c_str(), 1.0 );
    }
    else break;
  }
  
  // Cutflow, Weighted
  for(int iCut=0; iCut<(int)v_cuts.size(); iCut++){
    if( passCut( v_cuts[iCut] ) ){
      selectionInfo::cutUtil cut_info( v_cuts[iCut] );
      h_cutflow_wgt->Fill( cut_info.label.c_str(), wgt );
    }
    else break;
  }
  
  // N-1 Cutflow
  for(int iCut=0; iCut<(int)v_cuts.size(); iCut++){

    bool pass_nMinus1 = true;
    for(int jCut=0; jCut<(int)v_cuts.size(); jCut++){
      
      if( jCut==iCut ) continue;
      if( passCut( v_cuts[jCut] ) ){
	selectionInfo::cutUtil cut_info_j( v_cuts[jCut] );
	vect_cutflow_nMinus1[iCut]->Fill( cut_info_j.label.c_str(), wgt );
      }
      else{
	pass_nMinus1 = false;
	break;
      }
    }
    
    if( pass_nMinus1 ){
      selectionInfo::cutUtil cut_info( v_cuts[iCut] );
      vect_cutflow_nMinus1[iCut]->Fill( cut_info.label.c_str(), wgt );
    }

  }
  
  return;

}

//////////////////////////////////////////////////////////////////////

void selectionInfo::selectionUtil::printCutflow(){

  // Input Sanitation
  if( !h_cutflow ){
    std::cout << "      Error, must call setupCutflowHistos( TFile *f_out ) before attempting to fill cutflow histogram" << std::endl;
    return;
  }

  // Get width of cuts
  int label_width = 1;
  for(int iBin=1; iBin<=(int)h_cutflow->GetNbinsX(); iBin++){
    std::string temp_label =  h_cutflow->GetXaxis()->GetBinLabel(iBin);
    label_width = std::max( label_width, (int)temp_label.length() );
  }

  std::cout << "    Printing Cutflow: " << std::endl;
  for(int iBin=1; iBin<=(int)h_cutflow->GetNbinsX(); iBin++){
    std::cout << "      ";
    std::cout << setw(label_width);
    std::cout << h_cutflow->GetXaxis()->GetBinLabel(iBin);
    std::cout << ": ";
    std::cout << setw(12);
    std::cout << h_cutflow->GetBinContent(iBin);
    std::cout << ", ";
    std::cout << h_cutflow_wgt->GetBinContent(iBin) << std::endl;
  }
  
  return;
}

//////////////////////////////////////////////////////////////////////

selectionInfo::vect_id selectionInfo::getCutList( analyzerInfo::ID analysis ){

  vect_id result;

  switch( analysis ){

  case( analyzerInfo::k_SR ):
    result.push_back( k_dataFilter );
    result.push_back( k_trigger_singleLep_or_MET );
    result.push_back( k_goodVtx );
    result.push_back( k_ee1_selLep );
    result.push_back( k_ee0_vetoLep );
    result.push_back( k_trackVeto );
    result.push_back( k_tauVeto );
    result.push_back( k_ge2_jets );
    result.push_back( k_ge1_bJets );
    result.push_back( k_ge250_met );
    result.push_back( k_ge150_mt );
    result.push_back( k_ge0p8_minDPhi );
    break;

  case( analyzerInfo::k_CR0b ):
    result.push_back( k_dataFilter );
    result.push_back( k_trigger_singleLep_or_MET );
    result.push_back( k_goodVtx );
    result.push_back( k_ee1_selLep );
    result.push_back( k_ee0_vetoLep );
    result.push_back( k_trackVeto );
    result.push_back( k_tauVeto );
    result.push_back( k_ge2_jets );
    result.push_back( k_ee0_bJets );
    result.push_back( k_ge250_met );
    result.push_back( k_ge150_mt );
    result.push_back( k_ge0p8_minDPhi );
    break;

  case( analyzerInfo::k_CR1l_bulkWJets ):
    result.push_back( k_dataFilter );
    result.push_back( k_trigger_singleLep_or_MET );
    result.push_back( k_goodVtx );
    result.push_back( k_ee1_selLep );
    result.push_back( k_ee0_vetoLep );
    result.push_back( k_trackVeto );
    result.push_back( k_tauVeto );
    result.push_back( k_ge2_jets );
    result.push_back( k_ge1_bJets );
    result.push_back( k_ge0p8_minDPhi );
    break;

  case( analyzerInfo::k_CR2l ):
    result.push_back( k_dataFilter );
    result.push_back( k_trigger_singleLep_or_MET );
    result.push_back( k_goodVtx );
    result.push_back( k_diLepton );
    result.push_back( k_ge2_jets );
    result.push_back( k_ge1_bJets );
    result.push_back( k_ge250_met );
    result.push_back( k_ge150_mt );
    result.push_back( k_ge0p8_minDPhi );
    break;

  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( k_dataFilter );
    result.push_back( k_trigger_diLep );
    result.push_back( k_goodVtx );
    result.push_back( k_diLepton_bulkTTbar );
    result.push_back( k_oppSignLeptons );
    result.push_back( k_zMassWindow );
    result.push_back( k_ge20_diLepMass );
    result.push_back( k_ge2_jets );
    result.push_back( k_ge50_met );
    result.push_back( k_ge150_mt );
    result.push_back( k_ge0p8_minDPhi );
    break;

  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( k_dataFilter );
    result.push_back( k_goodVtx );
    result.push_back( k_ge2_jets );
    result.push_back( k_ge50_met );
    break;

  default:
    result.push_back( k_dataFilter );
    result.push_back( k_goodVtx );
    result.push_back( k_ge2_jets );
    break;

  }; // end analyzer switch

  return result;

}

//////////////////////////////////////////////////////////////////////
