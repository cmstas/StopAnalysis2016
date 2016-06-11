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

selectionInfo::selectionUtil::selectionUtil( vect_util cuts, sampleInfo::ID sample_id ){
  
  v_cuts.clear();
  v_cuts = cuts;

  h_cutflow     = NULL;
  h_cutflow_wgt = NULL;
  vect_cutflow_nMinus1.clear();
  
  h_cutflow_sig     = NULL;
  h_cutflow_sig_wgt = NULL;
  vect_cutflow_nMinus1_sig.clear();

  sample_info = new sampleInfo::sampleUtil( sample_id );
  
  if( sample_info->isData ){
    //std::cout << "    Loading bad event files" << std::endl;
    //metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/csc2015_Dec01.txt");
    //metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/ecalscn1043093_Dec01.txt");
    //metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/badResolutionTrack_Jan13.txt");
    //metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/muonBadTrack_Jan13.txt");
    //std::cout << "      finished!" << std::endl << std::endl;
  }
  
}

//////////////////////////////////////////////////////////////////////

selectionInfo::selectionUtil::~selectionUtil(){

  if( sample_info->isData ){
    duplicate_removal::clear_list();
  }
  
  v_cuts.clear();
  vect_cutflow_nMinus1.clear();
  vect_cutflow_nMinus1_sig.clear();

  sample_info->~sampleUtil();

}

//////////////////////////////////////////////////////////////////////

void selectionInfo::selectionUtil::setupCutflowHistos( TFile *f_out ){
 
  // Cutflow, unweighted
  std::string h_name  = "h__cutflow";
  std::string h_title = "Cutflow, Unweighted Events";

  if( sample_info->isSignalScan ){
    h_cutflow_sig = new TH3D( h_name.c_str(), h_title.c_str(), sample_info->nBins_stop, sample_info->min_stop, sample_info->max_stop, sample_info->nBins_lsp, sample_info->min_lsp, sample_info->max_lsp, (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
    h_cutflow_sig->SetDirectory( f_out );
 
    for(int iBin=1; iBin<=(int)h_cutflow_sig->GetNbinsZ(); iBin++){
      h_cutflow_sig->GetZaxis()->SetBinLabel( iBin, v_cuts[iBin-1].label.c_str() );
    }
  }
  else{
    h_cutflow = new TH1D( h_name.c_str(), h_title.c_str(), (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
    h_cutflow->SetDirectory( f_out );
 
    for(int iBin=1; iBin<=(int)h_cutflow->GetNbinsX(); iBin++){
      h_cutflow->GetXaxis()->SetBinLabel( iBin, v_cuts[iBin-1].label.c_str() );
    }
  }


  // Cutflow, weighted
  h_name  = "h__cutflow_wgt";
  h_title = "Cutflow";

  if( sample_info->isSignalScan ){
    h_cutflow_sig_wgt = new TH3D( h_name.c_str(), h_title.c_str(), sample_info->nBins_stop, sample_info->min_stop, sample_info->max_stop, sample_info->nBins_lsp, sample_info->min_lsp, sample_info->max_lsp, (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
    h_cutflow_sig_wgt->SetDirectory( f_out );
    
    for(int iBin=1; iBin<=(int)h_cutflow_sig_wgt->GetNbinsZ(); iBin++){
      h_cutflow_sig_wgt->GetZaxis()->SetBinLabel( iBin, v_cuts[iBin-1].label.c_str() );
    }
  }
  else{
    h_cutflow_wgt = new TH1D( h_name.c_str(), h_title.c_str(), (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
    h_cutflow_wgt->SetDirectory( f_out );
  
    for(int iBin=1; iBin<=(int)h_cutflow_wgt->GetNbinsX(); iBin++){
      h_cutflow_wgt->GetXaxis()->SetBinLabel( iBin, v_cuts[iBin-1].label.c_str() );
    }
  }
  

  // N-1 Cutflow
  const int nCuts = (int)v_cuts.size();

  if( sample_info->isSignalScan ){
    TH3D *h_cutflow_Nminus1[nCuts];
    
    for(int iCut=0; iCut<(int)v_cuts.size(); iCut++){
      
      h_name  = "h__cutflow_nMinus1__" + v_cuts[iCut].label;
      h_title = "Cutflow, N-1, " + v_cuts[iCut].title;

      h_cutflow_Nminus1[iCut] = new TH3D( h_name.c_str(), h_title.c_str(), sample_info->nBins_stop, sample_info->min_stop, sample_info->max_stop, sample_info->nBins_lsp, sample_info->min_lsp, sample_info->max_lsp, (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
      h_cutflow_Nminus1[iCut]->SetDirectory( f_out );
      
      int bin=1;
      for(int jCut=0; jCut<(int)v_cuts.size(); jCut++){
	if( jCut==iCut ) continue;
	h_cutflow_Nminus1[iCut]->GetZaxis()->SetBinLabel( bin, v_cuts[jCut].label.c_str() );
	bin++;
      }
      
      h_cutflow_Nminus1[iCut]->GetZaxis()->SetBinLabel( bin, v_cuts[iCut].label.c_str() );
      
      vect_cutflow_nMinus1_sig.push_back( h_cutflow_Nminus1[iCut] );
      
    } // end loop over cuts

  } // end if signal
  else{
    TH1D *h_cutflow_Nminus1[nCuts];

    for(int iCut=0; iCut<(int)v_cuts.size(); iCut++){
      
      h_name  = "h__cutflow_nMinus1__" + v_cuts[iCut].label;
      h_title = "Cutflow, N-1, " + v_cuts[iCut].title;

      h_cutflow_Nminus1[iCut] = new TH1D( h_name.c_str(), h_title.c_str(), (int)v_cuts.size(), 0.0, (double)v_cuts.size() );
      h_cutflow_Nminus1[iCut]->SetDirectory( f_out );
      
      int bin=1;
      for(int jCut=0; jCut<(int)v_cuts.size(); jCut++){
	if( jCut==iCut ) continue;
	h_cutflow_Nminus1[iCut]->GetXaxis()->SetBinLabel( bin, v_cuts[jCut].label.c_str() );
	bin++;
      }
      
      h_cutflow_Nminus1[iCut]->GetXaxis()->SetBinLabel( bin, v_cuts[iCut].label.c_str() );
      
      vect_cutflow_nMinus1.push_back( h_cutflow_Nminus1[iCut] );
      
    } // end loop over cuts

  } // end if not signal
    

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
      if( babyAnalyzer.filt_met() ) result = true;
    }
    break;
 
  case( k_trigger_singleLep ):

    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if( babyAnalyzer.HLT_SingleEl() ||
	  babyAnalyzer.HLT_SingleMu()    ) result = true;
    }
    break;

  case( k_trigger_MET ):
    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if( babyAnalyzer.HLT_MET() ) result = true;
    }
    break;

  case( k_trigger_singleLep_or_MET ):
    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if( babyAnalyzer.HLT_SingleEl() ||
	  babyAnalyzer.HLT_SingleMu() ||
	  babyAnalyzer.HLT_MET()        ) result = true;
    }
    break;

  case( k_trigger_diLep ):
    if( !babyAnalyzer.is_data() ) result = true;
    else{
      if ( babyAnalyzer.HLT_DiEl() || 
	   babyAnalyzer.HLT_DiMu() || 
	   babyAnalyzer.HLT_MuE()     ) result = true;
    }
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
    if( babyAnalyzer.PassTrackVeto() ) result = true;
    break;

  case( k_tauVeto ):
    if( babyAnalyzer.PassTauVeto() ) result = true;
    break;
	
  case( k_diLepton ):
    if( (babyAnalyzer.ngoodleps()>=2) ||
	(babyAnalyzer.ngoodleps()==1 && babyAnalyzer.nvetoleps()>=2 && babyAnalyzer.lep2_p4().Pt()>10.0) ||
	(babyAnalyzer.ngoodleps()==1 && !babyAnalyzer.PassTrackVeto()) ||
	(babyAnalyzer.ngoodleps()==1 && !babyAnalyzer.PassTauVeto()) ) result = true;
    break;

  case( k_diLepton_bulkTTbar ):
    if( babyAnalyzer.lep1_p4().Pt()>30.0 && 
	babyAnalyzer.lep2_p4().Pt()>15.0 &&
	babyAnalyzer.lep1_MiniIso()<0.1 &&
	babyAnalyzer.lep2_MiniIso()<0.1 &&
	( (abs(babyAnalyzer.lep1_pdgid())==13 && babyAnalyzer.lep1_passTightID()) || (abs(babyAnalyzer.lep1_pdgid())==11 && fabs(babyAnalyzer.lep1_p4().Eta())<1.442 && babyAnalyzer.lep1_passMediumID()) ) &&
	( (abs(babyAnalyzer.lep2_pdgid())==13 && babyAnalyzer.lep2_passTightID()) || (abs(babyAnalyzer.lep2_pdgid())==11 && fabs(babyAnalyzer.lep2_p4().Eta())<1.442 && babyAnalyzer.lep2_passMediumID()) )    ) result = true;
    break;

  case( k_oppSignLeptons ):
    if( babyAnalyzer.lep1_pdgid()*babyAnalyzer.lep2_pdgid()<0.0 ) result = true;
    break;

  case( k_zMassWindow ):
    if((abs(babyAnalyzer.lep1_pdgid())+abs(babyAnalyzer.lep2_pdgid()))==24 ) result = true;
    else if( (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()>(91.1876+15.0) || 
	     (babyAnalyzer.lep1_p4()+babyAnalyzer.lep2_p4()).M()<(91.1876-15.0)    ) result = true; 
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
    if( !passCut( v_cuts[iCut].id ) ) return false;
  }
  return true;

}

//////////////////////////////////////////////////////////////////////

void selectionInfo::selectionUtil::fillCutflowHistos( double wgt ){  
  
  int nCuts = (int)v_cuts.size();

  vector<bool> passCuts;
  for(int iCut=0; iCut<nCuts; iCut++){
    passCuts.push_back( passCut( v_cuts[iCut].id ) );
  }


  if( sample_info->isSignalScan ){

    // Intput Sanitation
    if( !h_cutflow_sig ){
      std::cout << "      Error, must call setupCutflowHistos( TFile *f_out ) before attempting to fill cutflow histogram" << std::endl;
      return;
    }

    // Cutflow, Unweighted
    for(int iCut=0; iCut<nCuts; iCut++){
      if( passCuts[iCut] ){
	h_cutflow_sig->Fill( babyAnalyzer.mass_stop(), babyAnalyzer.mass_lsp(), v_cuts[iCut].label.c_str(), 1.0 );
      }
      else break;
    }
    
    // Cutflow, Weighted
    for(int iCut=0; iCut<nCuts; iCut++){
      if( passCuts[iCut] ){
	h_cutflow_sig_wgt->Fill( babyAnalyzer.mass_stop(), babyAnalyzer.mass_lsp(), v_cuts[iCut].label.c_str(), wgt );
      }
      else break;
    }
  
    // N-1 Cutflow
    for(int iCut=0; iCut<nCuts; iCut++){
      
      bool pass_nMinus1 = true;
      for(int jCut=0; jCut<nCuts; jCut++){
	
	if( jCut==iCut ) continue;
	if( passCuts[jCut] ){
	  vect_cutflow_nMinus1_sig[iCut]->Fill( babyAnalyzer.mass_stop(), babyAnalyzer.mass_lsp(), v_cuts[jCut].label.c_str(), wgt );
	}
	else{
	  pass_nMinus1 = false;
	  break;
	}
      }
      
      if( pass_nMinus1 ){
	vect_cutflow_nMinus1_sig[iCut]->Fill( babyAnalyzer.mass_stop(), babyAnalyzer.mass_lsp(), v_cuts[iCut].label.c_str(), wgt );
      }

    }


  }
  else{

    // Intput Sanitation
    if( !h_cutflow ){
      std::cout << "      Error, must call setupCutflowHistos( TFile *f_out ) before attempting to fill cutflow histogram" << std::endl;
      return;
    }

    // Cutflow, Unweighted
    for(int iCut=0; iCut<nCuts; iCut++){
      if( passCuts[iCut] ){
	h_cutflow->Fill( v_cuts[iCut].label.c_str(), 1.0 );
      }
      else break;
    }
    
    // Cutflow, Weighted
    for(int iCut=0; iCut<nCuts; iCut++){
      if( passCuts[iCut] ){
	h_cutflow_wgt->Fill( v_cuts[iCut].label.c_str(), wgt );
      }
      else break;
    }
  
    // N-1 Cutflow
    for(int iCut=0; iCut<nCuts; iCut++){
      
      bool pass_nMinus1 = true;
      for(int jCut=0; jCut<nCuts; jCut++){
	
	if( jCut==iCut ) continue;
	if( passCuts[jCut] ){
	  vect_cutflow_nMinus1[iCut]->Fill( v_cuts[jCut].label.c_str(), wgt );
	}
	else{
	  pass_nMinus1 = false;
	  break;
	}
      }
      
      if( pass_nMinus1 ){
	vect_cutflow_nMinus1[iCut]->Fill( v_cuts[iCut].label.c_str(), wgt );
      }

    }

  } // end if not signalScan
  
  return;

}

//////////////////////////////////////////////////////////////////////

void selectionInfo::selectionUtil::printCutflow(double mStop, double mLSP){

  if( sample_info->isSignalScan ){
    // Input Sanitation
    if( !h_cutflow_sig ){
      std::cout << "      Error, must call setupCutflowHistos( TFile *f_out ) before attempting to access cutflow histogram" << std::endl;
      return;
    }

    int binX = h_cutflow_sig->GetXaxis()->FindBin(mStop);
    int binY = h_cutflow_sig->GetYaxis()->FindBin(mLSP);

    // Get width of cuts
    int label_width = 1;
    for(int iBin=1; iBin<=(int)h_cutflow_sig->GetNbinsZ(); iBin++){
      std::string temp_label =  h_cutflow_sig->GetZaxis()->GetBinLabel(iBin);
      label_width = std::max( label_width, (int)temp_label.length() );
    }
    
    std::cout << "    Printing Cutflow, for mStop=" << mStop << ", mLSP=" << mLSP << ": " << std::endl;
    for(int iBin=1; iBin<=(int)h_cutflow_sig->GetNbinsZ(); iBin++){
      std::cout << "      ";
      std::cout << setw(label_width);
      std::cout << h_cutflow_sig->GetZaxis()->GetBinLabel(iBin);
      std::cout << ": ";
      std::cout << setw(12);
      std::cout << h_cutflow_sig->GetBinContent(binX,binY,iBin);
      std::cout << ", ";
      std::cout << h_cutflow_sig_wgt->GetBinContent(binX,binY,iBin);
      if( iBin>1 ) std::cout << ", Efficiency = " << h_cutflow_sig_wgt->GetBinContent(binX,binY,iBin)/h_cutflow_sig_wgt->GetBinContent(binX,binY,iBin-1);
      std::cout << std::endl;
    }
    
    
  }
  else{
    // Input Sanitation
    if( !h_cutflow ){
      std::cout << "      Error, must call setupCutflowHistos( TFile *f_out ) before attempting to access cutflow histogram" << std::endl;
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
      std::cout << h_cutflow_wgt->GetBinContent(iBin);
      if( iBin>1 ) std::cout << ", Efficiency = " << h_cutflow_wgt->GetBinContent(iBin)/h_cutflow_wgt->GetBinContent(iBin-1);
      std::cout << std::endl;
    }
    
  } // end if not signal scan


  return;
}

//////////////////////////////////////////////////////////////////////

selectionInfo::vect_util selectionInfo::getCutList( analyzerInfo::ID analysis ){

  vect_util result;

  switch( analysis ){

  case( analyzerInfo::k_SR ):
    result.push_back( cutUtil(k_dataFilter) );
    result.push_back( cutUtil(k_trigger_singleLep_or_MET) );
    result.push_back( cutUtil(k_goodVtx) );
    result.push_back( cutUtil(k_ee1_selLep) );
    result.push_back( cutUtil(k_ee0_vetoLep) );
    result.push_back( cutUtil(k_trackVeto) );
    result.push_back( cutUtil(k_tauVeto) );
    result.push_back( cutUtil(k_ge2_jets) );
    result.push_back( cutUtil(k_ge1_bJets) );
    result.push_back( cutUtil(k_ge250_met) );
    result.push_back( cutUtil(k_ge150_mt) );
    result.push_back( cutUtil(k_ge0p8_minDPhi) );
    break;

  case( analyzerInfo::k_CR0b ):
    result.push_back( cutUtil(k_dataFilter) );
    result.push_back( cutUtil(k_trigger_singleLep_or_MET) );
    result.push_back( cutUtil(k_goodVtx) );
    result.push_back( cutUtil(k_ee1_selLep) );
    result.push_back( cutUtil(k_ee0_vetoLep) );
    result.push_back( cutUtil(k_trackVeto) );
    result.push_back( cutUtil(k_tauVeto) );
    result.push_back( cutUtil(k_ge2_jets) );
    result.push_back( cutUtil(k_ee0_bJets) );
    result.push_back( cutUtil(k_ge250_met) );
    result.push_back( cutUtil(k_ge150_mt) );
    result.push_back( cutUtil(k_ge0p8_minDPhi) );
    break;

  case( analyzerInfo::k_CR1l_bulkWJets ):
    result.push_back( cutUtil(k_dataFilter) );
    result.push_back( cutUtil(k_trigger_singleLep_or_MET) );
    result.push_back( cutUtil(k_goodVtx) );
    result.push_back( cutUtil(k_ee1_selLep) );
    result.push_back( cutUtil(k_ee0_vetoLep) );
    result.push_back( cutUtil(k_trackVeto) );
    result.push_back( cutUtil(k_tauVeto) );
    result.push_back( cutUtil(k_ge2_jets) );
    result.push_back( cutUtil(k_ge1_bJets) );
    result.push_back( cutUtil(k_ge0p8_minDPhi) );
    break;

  case( analyzerInfo::k_CR2l ):
    result.push_back( cutUtil(k_dataFilter) );
    result.push_back( cutUtil(k_trigger_singleLep_or_MET) );
    result.push_back( cutUtil(k_goodVtx) );
    result.push_back( cutUtil(k_diLepton) );
    result.push_back( cutUtil(k_ge2_jets) );
    result.push_back( cutUtil(k_ge1_bJets) );
    result.push_back( cutUtil(k_ge250_met) );
    result.push_back( cutUtil(k_ge150_mt) );
    result.push_back( cutUtil(k_ge0p8_minDPhi) );
    break;

  case( analyzerInfo::k_CR2l_bulkTTbar ):
    result.push_back( cutUtil(k_dataFilter) );
    //result.push_back( cutUtil(k_trigger_diLep) );
    result.push_back( cutUtil(k_goodVtx) );
    result.push_back( cutUtil(k_diLepton_bulkTTbar) );
    result.push_back( cutUtil(k_oppSignLeptons) );
    result.push_back( cutUtil(k_ge20_diLepMass) );
    result.push_back( cutUtil(k_zMassWindow) );
    result.push_back( cutUtil(k_ge2_jets) );
    result.push_back( cutUtil(k_ge50_met) );
    break;

  case( analyzerInfo::k_CRGammaJets ):
    result.push_back( cutUtil(k_dataFilter) );
    result.push_back( cutUtil(k_goodVtx) );
    result.push_back( cutUtil(k_ge2_jets) );
    result.push_back( cutUtil(k_ge50_met) );
    break;

  default:
    result.push_back( cutUtil(k_dataFilter) );
    result.push_back( cutUtil(k_goodVtx) );
    result.push_back( cutUtil(k_ge2_jets) );
    break;

  }; // end analyzer switch

  return result;

}

//////////////////////////////////////////////////////////////////////
