#include "JetTree.h"
#include "CMS3.h"
#include "JetSelections.h"
#include "btagsf/BTagCalibrationStandalone.h"

using namespace tas;
 
JetTree::JetTree ()
{
}

JetTree::JetTree (const std::string &prefix)
  : prefix_(prefix)
{
}

void JetTree::InitBtagSFTool(TH2D* h_btag_eff_b_, TH2D* h_btag_eff_c_, TH2D* h_btag_eff_udsg_, bool isFastsim_) {
    isFastsim = isFastsim_;
    //calib = calib_;
    calib = new BTagCalibration("csvv2", "btagsf/CSVv2.csv"); // 25s version of SFs
    reader_heavy = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "central"); // central
    reader_heavy_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "up");  // sys up
    reader_heavy_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "down");  // sys down
    reader_light = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central");  // central
    reader_light_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up");  // sys up
    reader_light_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down");  // sys down
    calib_fastsim = new BTagCalibration("CSV", "btagsf/CSV_13TEV_Combined_20_11_2015.csv"); // 25ns fastsim version of SFs
    reader_fastsim = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "central"); // central
    reader_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "up");  // sys up
    reader_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "down");  // sys down
    h_btag_eff_b = h_btag_eff_b_;
    h_btag_eff_c = h_btag_eff_c_;
    h_btag_eff_udsg = h_btag_eff_udsg_;
    std::cout << "loaded fullsim btag SFs" << std::endl;
    return;
}

float JetTree::getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim){
    if(!h_btag_eff_b || !h_btag_eff_c || !h_btag_eff_udsg) {
      std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists" << std::endl;
      return 1.;
    }
    //have fastsim already done in looper
//    if(isFastsim && (!h_btag_eff_b_fastsim || !h_btag_eff_c_fastsim || !h_btag_eff_udsg_fastsim)) {
//      std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists" << std::endl;
//      return 1.;
    //}
    // only use pt bins up to 400 GeV for charm and udsg
    float pt_cutoff = std::max(20.,std::min(399.,double(pt)));
    TH2D* h(0);
    if (abs(mcFlavour) == 5) {
      //h = isFastsim ? h_btag_eff_b_fastsim : h_btag_eff_b;
      h = h_btag_eff_b;
      // use pt bins up to 600 GeV for b
      pt_cutoff = std::max(20.,std::min(599.,double(pt)));
    }
    else if (abs(mcFlavour) == 4) {
      //h = isFastsim ? h_btag_eff_c_fastsim : h_btag_eff_c;
      h = h_btag_eff_c;
    }
    else {
      //h = isFastsim ? h_btag_eff_udsg_fastsim : h_btag_eff_udsg;
      h = h_btag_eff_udsg;
    }
    
    int binx = h->GetXaxis()->FindBin(pt_cutoff);
    int biny = h->GetYaxis()->FindBin(fabs(eta));
    return h->GetBinContent(binx,biny);
}

void JetTree::FillCommon(std::vector<unsigned int> alloverlapjets_idx,  FactorizedJetCorrector* corrector, float& btagprob_data, float &btagprob_mc, float &btagprob_err_heavy_UP, float & btagprob_err_heavy_DN,float & btagprob_err_light_UP, float & btagprob_err_light_DN ,unsigned int overlep1_idx, unsigned int overlep2_idx, bool applynewcorr, JetCorrectionUncertainty* jetcorr_uncertainty, int JES_type, bool applyBtagSFs, bool isFastsim)
{
    
    // fill info for ak4pfjets
    int nGoodJets=0.;
    int nFailJets=0.;
    unsigned int jindex=0;
    float HT = 0.;
    float JET_PT = 0.;
    int nbtags_med = 0;
    static const float BTAG_MED = 0.800;
    float dPhiM = 0.;
    float btagdisc = 0.;   
    unsigned int leadbtag_idx = 0;

    float htssm = 0.;
    float htosm = 0.;
    float htratiom = 0.;

    //apply JEC
    LorentzVector pfjet_p4_cor;
    LorentzVector pfjet_p4_uncor;
    vector<float> newjecorr;
    newjecorr.clear();
    vector<pair <int, LorentzVector> > sortedJets_pt;

      vector<LorentzVector> p4sCorrJets; // store corrected p4 for ALL jets, so indices match CMS3 ntuple
      vector<LorentzVector> p4sUCorrJets;
      p4sCorrJets.clear();
      p4sUCorrJets.clear();
      for(unsigned int iJet = 0; iJet < cms3.pfjets_p4().size(); iJet++){
        LorentzVector pfjet_p4_cor = cms3.pfjets_p4().at(iJet);
          // get uncorrected jet p4 to use as input for corrections
        LorentzVector pfjet_p4_uncor = pfjets_p4().at(iJet) * cms3.pfjets_undoJEC().at(iJet);

          // get L1FastL2L3Residual total correction
          corrector->setRho   ( cms3.evt_fixgridfastjet_all_rho() );
          corrector->setJetA  ( cms3.pfjets_area().at(iJet)       );
          corrector->setJetPt ( pfjet_p4_uncor.pt()               );
          corrector->setJetEta( pfjet_p4_uncor.eta()              );
          double corr = corrector->getCorrection();

          // check for negative correction
          if (corr < 0. && fabs(pfjet_p4_uncor.eta()) < 4.7) {
            std::cout << "ScanChain::Looper: WARNING: negative jet correction: " << corr
                      << ", raw jet pt: " << pfjet_p4_uncor.pt() << ", eta: " << pfjet_p4_uncor.eta() << std::endl;
          }

          // include protections here on jet kinematics to prevent rare warnings/crashes
          double var = 1.;
          if (!evt_isRealData() && JES_type != 0 && pfjet_p4_uncor.pt()*corr > 0. && fabs(pfjet_p4_uncor.eta()) < 5.4) {
            jetcorr_uncertainty->setJetEta(pfjet_p4_uncor.eta());
            jetcorr_uncertainty->setJetPt(pfjet_p4_uncor.pt() * corr); // must use CORRECTED pt
            double unc = jetcorr_uncertainty->getUncertainty(true);
            var = (1. + JES_type * unc);
          }

          // apply new JEC to p4
          pfjet_p4_cor = pfjet_p4_uncor * corr*var;
          newjecorr.push_back(corr);
          if(applynewcorr) p4sCorrJets.push_back(pfjet_p4_cor);
          else p4sCorrJets.push_back(pfjets_p4().at(iJet));
          p4sUCorrJets.push_back(pfjet_p4_uncor);
      }
      sortedJets_pt =  sort_pt(p4sCorrJets,JET_PT);

    for (size_t idx = 0; idx < pfjets_p4().size(); ++idx)
    {
        jindex = sortedJets_pt.at(idx).first;
        //deal with the overlaps
        if(jindex == overlep1_idx){
		ak4pfjet_overlep1_p4  = p4sCorrJets.at(jindex);
                ak4pfjet_overlep1_CSV = getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", jindex);
		//ak4pfjet_overlep1_pu_id = pfjets_pileupJetId().at(jindex);
                ak4pfjet_overlep1_chf = pfjets_chargedHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep1_nhf = pfjets_neutralHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep1_cef = pfjets_chargedEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep1_nef = pfjets_neutralEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep1_muf = pfjets_muonE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep1_cm  = pfjets_chargedMultiplicity().at(jindex);
                ak4pfjet_overlep1_nm  = cms3.pfjets_neutralMultiplicity().at(jindex);
	}
        if(jindex == overlep2_idx){
                ak4pfjet_overlep2_p4  = p4sCorrJets.at(jindex);
                ak4pfjet_overlep2_CSV = getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", jindex);
                //ak4pfjet_overlep2_pu_id = pfjets_pileupJetId().at(jindex);
                ak4pfjet_overlep2_chf = pfjets_chargedHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep2_nhf = pfjets_neutralHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep2_cef = pfjets_chargedEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep2_nef = pfjets_neutralEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep2_muf = pfjets_muonE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy());
                ak4pfjet_overlep2_cm  = pfjets_chargedMultiplicity().at(jindex);
                ak4pfjet_overlep2_nm  = cms3.pfjets_neutralMultiplicity().at(jindex);
        }

        //remove overlaps & apply preselections
        if(jindex == overlep1_idx || jindex == overlep2_idx) continue; //remove ovelaps from your jet collection

	bool skipthis = false;
	for(size_t jdx = 0; jdx < alloverlapjets_idx.size(); ++jdx){
	  if(alloverlapjets_idx.at(jdx)==jindex) {
	    skipthis = true;
	    break;
	  }
	}
	if(skipthis) continue; //remove all overlaps from jet collection

        //Jet selections
        if(p4sCorrJets.at(jindex).pt() < m_ak4_pt_cut) continue;
        if(fabs(p4sCorrJets.at(jindex).eta()) > m_ak4_eta_cut) continue;
	if(!isLoosePFJetV2(jindex)) ++nFailJets;
        if(!isFastsim && m_ak4_passid && !isLoosePFJetV2(jindex)) continue;
        nGoodJets++;
        ak4pfjets_p4.push_back(p4sCorrJets.at(jindex));
        ak4pfjets_pt.push_back(p4sCorrJets.at(jindex).pt());
        ak4pfjets_eta.push_back(p4sCorrJets.at(jindex).eta());
        ak4pfjets_phi.push_back(p4sCorrJets.at(jindex).phi());
        ak4pfjets_mass.push_back(p4sCorrJets.at(jindex).mass());

        //dphi_ak4pfjet_met.push_back(getdphi(p4sCorrJets.at(jindex).phi(), evt_pfmetPhi()));
        ak4pfjets_CSV.push_back(getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", jindex));
        ak4pfjets_mva.push_back(getbtagvalue("pfCombinedMVAV2BJetTags", jindex));
        ak4pfjets_puid.push_back(loosePileupJetId(jindex));
        ak4pfjets_parton_flavor.push_back(pfjets_partonFlavour().at(jindex));
	ak4pfjets_hadron_flavor.push_back(pfjets_hadronFlavour().at(jindex));
        ak4pfjets_loose_puid.push_back(loosePileupJetId(jindex));
        ak4pfjets_loose_pfid.push_back(isLoosePFJetV2(jindex));
        ak4pfjets_medium_pfid.push_back(isMediumPFJet(jindex));
        ak4pfjets_tight_pfid.push_back(isTightPFJet(jindex));

        ak4pfjets_chf.push_back(pfjets_chargedHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_nhf.push_back(pfjets_neutralHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_cef.push_back(pfjets_chargedEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_nef.push_back(pfjets_neutralEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
	ak4pfjets_muf.push_back(pfjets_muonE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_cm.push_back(pfjets_chargedMultiplicity().at(jindex));
        ak4pfjets_nm.push_back(cms3.pfjets_neutralMultiplicity().at(jindex));
	
	if (!evt_isRealData()) {
          ak4pfjets_mc3dr.push_back(pfjets_mc3dr().at(jindex));
          ak4pfjets_mc3id.push_back(pfjets_mc3_id().at(jindex));
          ak4pfjets_mc3idx.push_back(pfjets_mc3idx().at(jindex));
          ak4pfjets_mcmotherid.push_back(pfjets_mc_motherid().at(jindex));
	}

	//HTRatio
	dPhiM = getdphi(evt_pfmetPhi(), p4sCorrJets.at(jindex).phi() );
	if ( dPhiM  < (TMath::Pi()/2) ) htssm = htssm + p4sCorrJets.at(jindex).pt();
        else htosm = htosm + p4sCorrJets.at(jindex).pt();	

        HT = HT + p4sCorrJets.at(jindex).pt();
	
	//medium btag
        if(getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", jindex) > BTAG_MED){
             ak4pfjets_passMEDbtag.push_back(true);
             nbtags_med++;
             if(nbtags_med == 1){
                ak4pfjets_leadMEDbjet_pt = p4sCorrJets.at(jindex).pt();  //plot leading bjet pT
                ak4pfjets_leadMEDbjet_p4 = p4sCorrJets.at(jindex);
             }
                ak4pfjets_MEDbjet_pt.push_back(p4sCorrJets.at(jindex).pt());
               //bool isFastsim = false; 
              // btag SF - not final yet
              if (!evt_isRealData()&&applyBtagSFs) {
                float eff = getBtagEffFromFile(p4sCorrJets[jindex].pt(),p4sCorrJets[jindex].eta(), pfjets_hadronFlavour().at(jindex), isFastsim);
		BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;

		if (abs(pfjets_hadronFlavour().at(jindex)) == 5) flavor = BTagEntry::FLAV_B;
		else if (abs(pfjets_hadronFlavour().at(jindex)) == 4) flavor = BTagEntry::FLAV_C;

	        float pt_cutoff = std::max(30.,std::min(669.,double(p4sCorrJets[jindex].pt())));
	        float eta_cutoff = std::min(2.39,fabs(double(p4sCorrJets[jindex].eta())));
		float weight_cent(1.), weight_UP(1.), weight_DN(1.);

//                cout<<"read uncertainty from btagsf reader:"<<endl;
		if (flavor == BTagEntry::FLAV_UDSG) {
		  weight_cent = reader_light->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_UP = reader_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_DN = reader_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
		} else {
		  weight_cent = reader_heavy->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_UP = reader_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_DN = reader_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
		}
		if (isFastsim) {
		  weight_cent *= reader_fastsim->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_UP *= reader_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_DN *= reader_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff);
		}
  //              cout<<"got uncertainty from btagsf reader:"<<endl;
                btagprob_data *= weight_cent * eff;
                btagprob_mc *= eff;
                float abserr_UP = weight_UP - weight_cent;
                float abserr_DN = weight_cent - weight_DN;
		if (flavor == BTagEntry::FLAV_UDSG) {
                  btagprob_err_light_UP += abserr_UP/weight_cent;
                  btagprob_err_light_DN += abserr_DN/weight_cent;
		} else {
                  btagprob_err_heavy_UP += abserr_UP/weight_cent;
                  btagprob_err_heavy_DN += abserr_DN/weight_cent;
                }
//                cout<<"btagprob_err_heavy_UP"<<btagprob_err_heavy_UP<<endl;
               }
             }else{ 
             ak4pfjets_passMEDbtag.push_back(false);
             if (!evt_isRealData()&&applyBtagSFs) { // fail med btag -- needed for SF event weights
              float eff = getBtagEffFromFile(p4sCorrJets[jindex].pt(),p4sCorrJets[jindex].eta(), pfjets_hadronFlavour().at(jindex), isFastsim);
	      BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
	      if (abs(pfjets_hadronFlavour().at(jindex)) == 5) flavor = BTagEntry::FLAV_B;
	      else if (abs(pfjets_hadronFlavour().at(jindex)) == 4) flavor = BTagEntry::FLAV_C;
	      float pt_cutoff = std::max(30.,std::min(669.,double(p4sCorrJets[jindex].eta())));
	      float eta_cutoff = std::min(2.39,fabs(double(p4sCorrJets[jindex].eta())));
	      float weight_cent(1.), weight_UP(1.), weight_DN(1.);
	      if (flavor == BTagEntry::FLAV_UDSG) {
		weight_cent = reader_light->eval(flavor, eta_cutoff, pt_cutoff);
		weight_UP = reader_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
		weight_DN = reader_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
	      } else {
		weight_cent = reader_heavy->eval(flavor, eta_cutoff, pt_cutoff);
		weight_UP = reader_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
		weight_DN = reader_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
	      }
	      if (isFastsim) {
		weight_cent *= reader_fastsim->eval(flavor, eta_cutoff, pt_cutoff);
		weight_UP *= reader_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff);
		weight_DN *= reader_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff);
	      }

              btagprob_data *= (1. - weight_cent * eff);
              btagprob_mc *= (1. - eff);
              float abserr_UP = weight_UP - weight_cent;
              float abserr_DN = weight_cent - weight_DN;
	      if (flavor == BTagEntry::FLAV_UDSG) {
                btagprob_err_light_UP += (-eff * abserr_UP)/(1 - eff * weight_cent);
                btagprob_err_light_DN += (-eff * abserr_DN)/(1 - eff * weight_cent);
              } else {
                btagprob_err_heavy_UP += (-eff * abserr_UP)/(1 - eff * weight_cent);
                btagprob_err_heavy_DN += (-eff * abserr_DN)/(1 - eff * weight_cent);
              }
           }
         }
	if(getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", jindex)> btagdisc){
	  btagdisc = getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", jindex);
	  leadbtag_idx = jindex;
	}
   }

    ak4pfjets_leadbtag_p4 = p4sCorrJets.at(leadbtag_idx);//highest CSV jet

   ngoodjets = nGoodJets;
   nfailjets = nFailJets;
   ak4_HT = HT;
   HT=0;
   ngoodbtags = nbtags_med;

   ak4_htssm = htssm;
   ak4_htosm = htosm;
   htratiom   = htssm / (htosm + htssm);
   ak4_htratiom = htratiom; 

   nGoodJets = 0;

    // fill info for ak8pfjets
    for (size_t idx = 0; idx < ak8jets_p4().size(); ++idx)
    {
        if(pfjets_p4().at(idx).pt() < m_ak8_pt_cut) continue;
        if(fabs(pfjets_p4().at(idx).eta()) > m_ak8_eta_cut) continue;
        if(!isFastsim && m_ak8_passid && !isLoosePFJetV2(idx)) continue;

        ak8pfjets_p4.push_back(ak8jets_p4().at(idx));
        ak8pfjets_tau1.push_back(ak8jets_nJettinessTau1().at(idx));
        ak8pfjets_tau2.push_back(ak8jets_nJettinessTau2().at(idx));
        ak8pfjets_tau3.push_back(ak8jets_nJettinessTau3().at(idx));
        //ak8pfjets_top_mass.push_back(ak8jets_topJetMass().at(idx));
        ak8pfjets_pruned_mass.push_back(ak8jets_prunedMass().at(idx));
        ak8pfjets_trimmed_mass.push_back(ak8jets_trimmedMass().at(idx));
        ak8pfjets_filtered_mass.push_back(ak8jets_filteredMass().at(idx));
	//ak8pfjets_pu_id.push_back(ak8jets_pileupJetId().at(idx));    
        ak8pfjets_parton_flavor.push_back(ak8jets_partonFlavour().at(idx));

        nGoodJets++;

    }
    ak8GoodPFJets = nGoodJets;
    nGoodJets=0;

    // fill info for genjets
    if (!evt_isRealData()){
      for (size_t idx = 0; idx < genjets_p4NoMuNoNu().size(); ++idx){
        if (genjets_p4NoMuNoNu().at(idx).pt() < m_ak4_pt_cut) continue;
 
        ak4genjets_p4.push_back(genjets_p4NoMuNoNu().at(idx));
        if(genjets_p4NoMuNoNu().at(idx).pt() > 20.)  nGoodJets++;
      }
    }
    nGoodGenJets = nGoodJets;
    
}
        
void JetTree::SetJetSelection (std::string cone_size, float pt_cut,float eta, bool id)
{
  if (cone_size == "ak4") { m_ak4_pt_cut = pt_cut; m_ak4_eta_cut = eta; m_ak4_passid = id; }
  else if (cone_size == "ak8") { m_ak8_pt_cut = pt_cut; m_ak8_eta_cut = eta; m_ak8_passid = id; }
  else {std::cout << "Invalid cone size." << std::endl;}

  return;
}
 
void JetTree::GetJetSelections (std::string cone_size)
{
    if (cone_size == "ak4") std::cout << "ak4 jet pt > " << m_ak4_pt_cut << std::endl;
    else if (cone_size == "ak8") std::cout << "ak8 jet pt > " << m_ak8_pt_cut << std::endl;
    else
    {
        std::cout << "ak4 jet pt > " << m_ak4_pt_cut << std::endl;        
        std::cout << "ak8 jet pt > " << m_ak8_pt_cut << std::endl;
    }
}
void JetTree::deleteBtagSFTool()
{
   
    delete calib;
    delete reader_heavy;
    delete reader_heavy_UP;
    delete reader_heavy_DN;
    delete reader_light;
    delete reader_light_UP;
    delete reader_light_DN;
    delete calib_fastsim;
    delete reader_fastsim;
    delete reader_fastsim_UP;
    delete reader_fastsim_DN;
   return;
} 
void JetTree::Reset ()
{
    ak4pfjets_p4.clear();
    ak4pfjets_pt.clear();
    ak4pfjets_eta.clear();
    ak4pfjets_phi.clear();
    ak4pfjets_mass.clear();

    dphi_ak4pfjet_met.clear();
    ak4pfjets_qg_disc.clear();    
    ak4pfjets_CSV.clear();
    ak4pfjets_mva.clear();
    ak4pfjets_puid.clear();
    ak4pfjets_parton_flavor.clear();
    ak4pfjets_hadron_flavor.clear();
    ak4pfjets_loose_puid.clear();
    ak4pfjets_loose_pfid.clear();
    ak4pfjets_medium_pfid.clear();
    ak4pfjets_tight_pfid.clear();

    ak4pfjets_chf.clear();
    ak4pfjets_nhf.clear();
    ak4pfjets_cef.clear();
    ak4pfjets_nef.clear();
    ak4pfjets_muf.clear();
    ak4pfjets_cm.clear();
    ak4pfjets_nm.clear();

    ak4pfjets_mc3dr.clear();
    ak4pfjets_mc3id.clear();
    ak4pfjets_mc3idx.clear();
    ak4pfjets_mcmotherid.clear();
 
    ak4_htssm    = -9999.;
    ak4_htosm    = -9999.;
    ak4_htratiom = -9999.; 

   //overlaps
    ak4pfjet_overlep1_p4 = LorentzVector(0,0, 0,0);
    ak4pfjet_overlep1_CSV   = -9999;
    ak4pfjet_overlep1_pu_id = -9999;
    ak4pfjet_overlep1_chf   = -9999;
    ak4pfjet_overlep1_nhf   = -9999;
    ak4pfjet_overlep1_cef   = -9999;
    ak4pfjet_overlep1_nef   = -9999;
    ak4pfjet_overlep1_muf   = -9999;
    ak4pfjet_overlep1_cm    = -9999;
    ak4pfjet_overlep1_nm    = -9999;

    ak4pfjet_overlep2_p4 = LorentzVector(0,0, 0,0);
    ak4pfjet_overlep2_CSV   = -9999;
    ak4pfjet_overlep2_pu_id = -9999;
    ak4pfjet_overlep2_chf   = -9999;
    ak4pfjet_overlep2_nhf   = -9999;
    ak4pfjet_overlep2_cef   = -9999;
    ak4pfjet_overlep2_nef   = -9999;
    ak4pfjet_overlep2_muf   = -9999;
    ak4pfjet_overlep2_cm    = -9999;
    ak4pfjet_overlep2_nm    = -9999;
  
    //ak8 
    ak8pfjets_p4.clear();
    ak8pfjets_tau1.clear();
    ak8pfjets_tau2.clear();
    ak8pfjets_tau3.clear();
    ak8pfjets_top_mass.clear();
    ak8pfjets_pruned_mass.clear();
    ak8pfjets_trimmed_mass.clear();
    ak8pfjets_filtered_mass.clear();
    ak8pfjets_pu_id.clear();    
    ak8pfjets_parton_flavor.clear();
 
    ak4genjets_p4.clear();
 
    ak4pfjets_MEDbjet_pt.clear();
    ak4pfjets_passMEDbtag.clear();
    ak4pfjets_leadMEDbjet_pt = -9999; 
    ak4pfjets_leadMEDbjet_p4 = LorentzVector(0,0, 0,0);
    ak4pfjets_leadbtag_p4 = LorentzVector(0,0, 0,0);
  
    ngoodjets     = -9999;  
    nfailjets     = -9999;  
    ak4_HT 	  = -9999.; 
    ak8GoodPFJets = -9999;
    nGoodGenJets  = -9999;
    ngoodbtags    = -9999;
}
 
void JetTree::SetAK4Branches (TTree* tree)
{
    tree->Branch(Form("%sngoodjets", prefix_.c_str()) , &ngoodjets);
    tree->Branch(Form("%sngoodbtags", prefix_.c_str()) , &ngoodbtags);
    tree->Branch(Form("%sak4_HT", prefix_.c_str()) , &ak4_HT);
    tree->Branch(Form("%sak4_htratiom", prefix_.c_str()) , &ak4_htratiom);
    tree->Branch(Form("%sdphi_ak4pfjet_met", prefix_.c_str()) , &dphi_ak4pfjet_met);

    tree->Branch(Form("%sak4pfjets_p4", prefix_.c_str()) , &ak4pfjets_p4);

    tree->Branch(Form("%sak4pfjets_passMEDbtag", prefix_.c_str()) , &ak4pfjets_passMEDbtag);
    tree->Branch(Form("%sak4pfjets_CSV", prefix_.c_str()) , &ak4pfjets_CSV);
    tree->Branch(Form("%sak4pfjets_mva", prefix_.c_str()) , &ak4pfjets_mva);
    tree->Branch(Form("%sak4pfjets_parton_flavor", prefix_.c_str()) , &ak4pfjets_parton_flavor);
    tree->Branch(Form("%sak4pfjets_hadron_flavor", prefix_.c_str()) , &ak4pfjets_hadron_flavor);
    tree->Branch(Form("%sak4pfjets_loose_puid", prefix_.c_str()) , &ak4pfjets_loose_puid);
    tree->Branch(Form("%sak4pfjets_loose_pfid", prefix_.c_str()) , &ak4pfjets_loose_pfid);

    tree->Branch(Form("%sak4pfjets_leadMEDbjet_p4", prefix_.c_str()) , &ak4pfjets_leadMEDbjet_p4);
    tree->Branch(Form("%sak4pfjets_leadbtag_p4", prefix_.c_str()) , &ak4pfjets_leadbtag_p4);
    tree->Branch(Form("%sak4genjets_p4", prefix_.c_str()) , &ak4genjets_p4); 
}

void JetTree::SetAK8Branches (TTree* tree)
{
    tree->Branch(Form("%sak8pfjets_p4", prefix_.c_str()) , &ak8pfjets_p4);
    tree->Branch(Form("%sak8pfjets_tau1", prefix_.c_str()) , &ak8pfjets_tau1);
    tree->Branch(Form("%sak8pfjets_tau2", prefix_.c_str()) , &ak8pfjets_tau2);
    tree->Branch(Form("%sak8pfjets_tau3", prefix_.c_str()) , &ak8pfjets_tau3);
    tree->Branch(Form("%sak8pfjets_top_mass", prefix_.c_str()) , &ak8pfjets_top_mass);
    tree->Branch(Form("%sak8pfjets_pruned_mass", prefix_.c_str()) , &ak8pfjets_pruned_mass);
    tree->Branch(Form("%sak8pfjets_trimmed_mass", prefix_.c_str()) , &ak8pfjets_trimmed_mass);
    tree->Branch(Form("%sak8pfjets_filtered_mass", prefix_.c_str()) , &ak8pfjets_filtered_mass);
    tree->Branch(Form("%sak8pfjets_pu_id", prefix_.c_str()) , &ak8pfjets_pu_id);    
    tree->Branch(Form("%sak8pfjets_parton_flavor", prefix_.c_str()) , &ak8pfjets_parton_flavor);
    tree->Branch(Form("%sak8GoodPFJets", prefix_.c_str()) , &ak8GoodPFJets);  
}

void JetTree::SetAK4Branches_Overleps (TTree* tree)
{
    tree->Branch(Form("%sak4pfjet_overlep1_p4", prefix_.c_str()) , &ak4pfjet_overlep1_p4);                                                                                    
    tree->Branch(Form("%sak4pfjet_overlep1_CSV", prefix_.c_str()) , &ak4pfjet_overlep1_CSV);
    tree->Branch(Form("%sak4pfjet_overlep1_pu_id",prefix_.c_str()) , &ak4pfjet_overlep1_pu_id);
    tree->Branch(Form("%sak4pfjet_overlep1_chf", prefix_.c_str()) , &ak4pfjet_overlep1_chf);
    tree->Branch(Form("%sak4pfjet_overlep1_nhf", prefix_.c_str()) , &ak4pfjet_overlep1_nhf);
    tree->Branch(Form("%sak4pfjet_overlep1_cef", prefix_.c_str()) , &ak4pfjet_overlep1_cef);
    tree->Branch(Form("%sak4pfjet_overlep1_nef", prefix_.c_str()) , &ak4pfjet_overlep1_nef);
    tree->Branch(Form("%sak4pfjet_overlep1_muf", prefix_.c_str()) , &ak4pfjet_overlep1_muf);
    tree->Branch(Form("%sak4pfjet_overlep1_cm", prefix_.c_str()) , &ak4pfjet_overlep1_cm);
    tree->Branch(Form("%sak4pfjet_overlep1_nm", prefix_.c_str()) , &ak4pfjet_overlep1_nm);

    tree->Branch(Form("%sak4pfjet_overlep2_p4", prefix_.c_str()) , &ak4pfjet_overlep2_p4);
    tree->Branch(Form("%sak4pfjet_overlep2_CSV", prefix_.c_str()) , &ak4pfjet_overlep2_CSV);
    tree->Branch(Form("%sak4pfjet_overlep2_pu_id",prefix_.c_str()) , &ak4pfjet_overlep2_pu_id);
    tree->Branch(Form("%sak4pfjet_overlep2_chf", prefix_.c_str()) , &ak4pfjet_overlep2_chf);
    tree->Branch(Form("%sak4pfjet_overlep2_nhf", prefix_.c_str()) , &ak4pfjet_overlep2_nhf);
    tree->Branch(Form("%sak4pfjet_overlep2_cef", prefix_.c_str()) , &ak4pfjet_overlep2_cef);
    tree->Branch(Form("%sak4pfjet_overlep2_nef", prefix_.c_str()) , &ak4pfjet_overlep2_nef);
    tree->Branch(Form("%sak4pfjet_overlep2_muf", prefix_.c_str()) , &ak4pfjet_overlep2_muf);
    tree->Branch(Form("%sak4pfjet_overlep2_cm", prefix_.c_str()) , &ak4pfjet_overlep2_cm);
    tree->Branch(Form("%sak4pfjet_overlep2_nm", prefix_.c_str()) , &ak4pfjet_overlep2_nm);
}

void JetTree::SetAK4Branches_SynchTools (TTree* tree)
{
    tree->Branch(Form("%sak4pfjets_pt", prefix_.c_str()) , &ak4pfjets_pt);
    tree->Branch(Form("%sak4pfjets_eta", prefix_.c_str()) , &ak4pfjets_eta);
    tree->Branch(Form("%sak4pfjets_phi", prefix_.c_str()) , &ak4pfjets_phi);
    tree->Branch(Form("%sak4pfjets_mass", prefix_.c_str()) , &ak4pfjets_mass);
}

void JetTree::SetAK4Branches_EF(TTree* tree)
{
    tree->Branch(Form("%sak4pfjets_chf", prefix_.c_str()) , &ak4pfjets_chf);
    tree->Branch(Form("%sak4pfjets_nhf", prefix_.c_str()) , &ak4pfjets_nhf);
    tree->Branch(Form("%sak4pfjets_cef", prefix_.c_str()) , &ak4pfjets_cef);
    tree->Branch(Form("%sak4pfjets_nef", prefix_.c_str()) , &ak4pfjets_nef);
    tree->Branch(Form("%sak4pfjets_muf", prefix_.c_str()) , &ak4pfjets_muf);
    tree->Branch(Form("%sak4pfjets_cm", prefix_.c_str()) , &ak4pfjets_cm);
    tree->Branch(Form("%sak4pfjets_nm", prefix_.c_str()) , &ak4pfjets_nm);
}

void JetTree::SetAK4Branches_Other(TTree* tree)
{
//these are not completely useless but could go?
    tree->Branch(Form("%snGoodGenJets", prefix_.c_str()) , &nGoodGenJets); 
    tree->Branch(Form("%snfailjets", prefix_.c_str()) , &nfailjets);
    tree->Branch(Form("%sak4_htssm", prefix_.c_str()) , &ak4_htssm);                                                                 
    tree->Branch(Form("%sak4_htosm", prefix_.c_str()) , &ak4_htosm);
    tree->Branch(Form("%sak4pfjets_qg_disc", prefix_.c_str()) , &ak4pfjets_qg_disc);
    tree->Branch(Form("%sak4pfjets_MEDbjet_pt",prefix_.c_str()) , &ak4pfjets_MEDbjet_pt);                                            
    tree->Branch(Form("%sak4pfjets_leadMEDbjet_pt",prefix_.c_str()) , &ak4pfjets_leadMEDbjet_pt);   
    tree->Branch(Form("%sak4pfjets_medium_pfid", prefix_.c_str()) , &ak4pfjets_medium_pfid);
    tree->Branch(Form("%sak4pfjets_tight_pfid", prefix_.c_str()) , &ak4pfjets_tight_pfid);
    tree->Branch(Form("%sak4pfjets_puid", prefix_.c_str()) , &ak4pfjets_puid); 
    tree->Branch(Form("%sak4pfjets_mc3dr", prefix_.c_str()) , &ak4pfjets_mc3dr);
    tree->Branch(Form("%sak4pfjets_mc3id", prefix_.c_str()) , &ak4pfjets_mc3id);                                        
    tree->Branch(Form("%sak4pfjets_mc3idx", prefix_.c_str()) , &ak4pfjets_mc3idx);
    tree->Branch(Form("%sak4pfjets_mcmotherid", prefix_.c_str()) , &ak4pfjets_mcmotherid);
}
