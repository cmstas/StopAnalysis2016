#include "JetTree.h"
#include "CMS3.h"
#include "JetSelections.h"
#include "btagsf/BTagCalibrationStandalone.h"

using namespace tas;
 
JetTree::JetTree() : doResolveTopMVA(false) {}

JetTree::JetTree(const std::string &prefix) : prefix_(prefix), doResolveTopMVA(false) {}

JetTree::~JetTree () {
  // delete resTopMVA;
}

void JetTree::InitTopMVA(ResolvedTopMVA* resTopMVAptr) {
  doResolveTopMVA = true;
  resTopMVA = resTopMVAptr;
}

void JetTree::InitBtagSFTool(bool isFastsim_) {
    isFastsim = isFastsim_;
    //calib = calib_;
    calib         = new BTagCalibration("DeepCSV", "btagsf/DeepCSV_Moriond17_B_H.csv"); // DeepCSV version of SFs
    calib_fastsim = new BTagCalibration("deepcsv", "btagsf/fastsim_deepcsv_ttbar_26_1_2017.csv"); // DeepCSV fastsim version of SFs
    reader_heavy      = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central"); // central
    reader_heavy_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up");  // sys up
    reader_heavy_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down");  // sys down
    reader_light      = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "central");  // central
    reader_light_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "up");  // sys up
    reader_light_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "down");  // sys down
    reader_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "central"); // central
    reader_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "up");  // sys up
    reader_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "down");  // sys down
    reader_loose_heavy      = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "central"); // central
    reader_loose_heavy_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "up");  // sys up
    reader_loose_heavy_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "down");  // sys down
    reader_loose_light      = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "central");  // central
    reader_loose_light_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "up");  // sys up
    reader_loose_light_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "down");  // sys down
    reader_loose_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_LOOSE, "fastsim", "central"); // central
    reader_loose_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_LOOSE, "fastsim", "up");  // sys up
    reader_loose_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_LOOSE, "fastsim", "down");  // sys down
    reader_tight_heavy      = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "comb", "central"); // central
    reader_tight_heavy_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "comb", "up");  // sys up
    reader_tight_heavy_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "comb", "down");  // sys down
    reader_tight_light      = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "incl", "central");  // central
    reader_tight_light_UP   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "incl", "up");  // sys up
    reader_tight_light_DN   = new BTagCalibrationReader(calib, BTagEntry::OP_TIGHT, "incl", "down");  // sys down
    reader_tight_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_TIGHT, "fastsim", "central"); // central
    reader_tight_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_TIGHT, "fastsim", "up");  // sys up
    reader_tight_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_TIGHT, "fastsim", "down");  // sys down
    TH2D* h_btag_eff_b_temp = NULL;
    TH2D* h_btag_eff_c_temp = NULL;
    TH2D* h_btag_eff_udsg_temp = NULL;
    TH2D* h_tight_btag_eff_b_temp = NULL;
    TH2D* h_tight_btag_eff_c_temp = NULL;
    TH2D* h_tight_btag_eff_udsg_temp = NULL;
    TH2D* h_loose_btag_eff_b_temp = NULL;
    TH2D* h_loose_btag_eff_c_temp = NULL;
    TH2D* h_loose_btag_eff_udsg_temp = NULL;
    if(isFastsim){
      // Created using https://github.com/cmstas/bTagEfficiencyTools. Todo: change to deepCSV later
      feff =  new TFile("btagsf/btageff__SMS-T1bbbb-T1qqqq_25ns_Moriond17.root");
    } else {
      // Todo: create efficiency in the phase space of the stop analysis
      feff =  new TFile("btagsf/btageff__ttbar_powheg_pythia8_25ns_Moriond17_deepCSV.root");
    }
    if (!feff) throw std::invalid_argument("JetTree.cc: btagsf file does not exist!");
    h_btag_eff_b_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_med_Eff_b");
    h_btag_eff_c_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_med_Eff_c");
    h_btag_eff_udsg_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_med_Eff_udsg");
    h_tight_btag_eff_b_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_tight_Eff_b");
    h_tight_btag_eff_c_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_tight_Eff_c");
    h_tight_btag_eff_udsg_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_tight_Eff_udsg");
    h_loose_btag_eff_b_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_loose_Eff_b");
    h_loose_btag_eff_c_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_loose_Eff_c");
    h_loose_btag_eff_udsg_temp = (TH2D*) feff->Get("h2_BTaggingEff_csv_loose_Eff_udsg");

    if (!h_btag_eff_b_temp) throw std::invalid_argument("JetTree.cc: can't find the btagging efficiency histogram!");
    h_btag_eff_b = (TH2D*) h_btag_eff_b_temp->Clone("h_btag_eff_b");
    h_btag_eff_c = (TH2D*) h_btag_eff_c_temp->Clone("h_btag_eff_c");
    h_btag_eff_udsg = (TH2D*) h_btag_eff_udsg_temp->Clone("h_btag_eff_udsg");
    h_tight_btag_eff_b = (TH2D*) h_tight_btag_eff_b_temp->Clone("h_tight_btag_eff_b");
    h_tight_btag_eff_c = (TH2D*) h_tight_btag_eff_c_temp->Clone("h_tight_btag_eff_c");
    h_tight_btag_eff_udsg = (TH2D*) h_tight_btag_eff_udsg_temp->Clone("h_tight_btag_eff_udsg");
    h_loose_btag_eff_b = (TH2D*) h_loose_btag_eff_b_temp->Clone("h_loose_btag_eff_b");
    h_loose_btag_eff_c = (TH2D*) h_loose_btag_eff_c_temp->Clone("h_loose_btag_eff_c");
    h_loose_btag_eff_udsg = (TH2D*) h_loose_btag_eff_udsg_temp->Clone("h_loose_btag_eff_udsg");

    //cout << h_btag_eff_b->Integral() << " " << h_btag_eff_c->Integral() << " " << h_btag_eff_udsg->Integral() << " " << endl; 
    //cout << h_tight_btag_eff_b->Integral() << " " << h_tight_btag_eff_c->Integral() << " " << h_tight_btag_eff_udsg->Integral() << " " << endl;
    //cout << h_loose_btag_eff_b->Integral() << " " << h_loose_btag_eff_c->Integral() << " " << h_loose_btag_eff_udsg->Integral() << " " << endl;
    //feff->Close();
    //h_btag_eff_b = h_btag_eff_b_;
    //h_btag_eff_c = h_btag_eff_c_;
    //h_btag_eff_udsg = h_btag_eff_udsg_;
    std::cout << "loaded btag SFs" << std::endl;
    return;
}

float JetTree::getBtagEffFromFile(float pt, float eta, int mcFlavour, int WP, bool isFastsim){
    if(WP<0||WP>2){
      std::cout << "babyMaker::getBtagEffFromFile: ERROR: wrong WP" << std::endl;
      return 1.;
    }
    if(WP==1 && (!h_btag_eff_b || !h_btag_eff_c || !h_btag_eff_udsg)) {
      std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists for medium WP" << std::endl;
      return 1.;
    }
    if(WP==0 && (!h_loose_btag_eff_b || !h_loose_btag_eff_c || !h_loose_btag_eff_udsg)) {
      std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists for loose WP" << std::endl;
      return 1.;
    }
    if(WP==2 && (!h_tight_btag_eff_b || !h_tight_btag_eff_c || !h_tight_btag_eff_udsg)) {
      std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists for tight WP" << std::endl;
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
    if(WP==1){
      if (abs(mcFlavour) == 5) {
	h = h_btag_eff_b;
	pt_cutoff = std::max(20.,std::min(599.,double(pt)));
      }
      else if (abs(mcFlavour) == 4) {
	h = h_btag_eff_c;
      }
      else {
	h = h_btag_eff_udsg;
      }
    }
    if(WP==0){
      if (abs(mcFlavour) == 5) {
	h = h_loose_btag_eff_b;
	pt_cutoff = std::max(20.,std::min(599.,double(pt)));
      }
      else if (abs(mcFlavour) == 4) {
	h = h_loose_btag_eff_c;
      }
      else {
	h = h_loose_btag_eff_udsg;
      }
    }
    if(WP==2){
      if (abs(mcFlavour) == 5) {
	h = h_tight_btag_eff_b;
	pt_cutoff = std::max(20.,std::min(599.,double(pt)));
      }
      else if (abs(mcFlavour) == 4) {
	h = h_tight_btag_eff_c;
      }
      else {
	h = h_tight_btag_eff_udsg;
      }
    }
    int binx = h->GetXaxis()->FindBin(pt_cutoff);
    int biny = h->GetYaxis()->FindBin(fabs(eta));
    return h->GetBinContent(binx,biny);
}

void JetTree::FillCommon(std::vector<unsigned int> alloverlapjets_idx, FactorizedJetCorrector* corrector, float& btagprob_data, float &btagprob_mc, float& btagprob_heavy_UP, float& btagprob_heavy_DN, float& btagprob_light_UP, float& btagprob_light_DN, float& btagprob_FS_UP, float& btagprob_FS_DN, float& loosebtagprob_data, float &loosebtagprob_mc, float &loosebtagprob_heavy_UP, float& loosebtagprob_heavy_DN, float& loosebtagprob_light_UP, float& loosebtagprob_light_DN, float& loosebtagprob_FS_UP, float& loosebtagprob_FS_DN, float& tightbtagprob_data, float& tightbtagprob_mc, float& tightbtagprob_heavy_UP, float& tightbtagprob_heavy_DN, float& tightbtagprob_light_UP, float& tightbtagprob_light_DN, float& tightbtagprob_FS_UP, float& tightbtagprob_FS_DN, unsigned int overlep1_idx, unsigned int overlep2_idx, bool applynewcorr, JetCorrectionUncertainty* jetcorr_uncertainty, int JES_type, bool applyBtagSFs, bool isFastsim)
{
    // fill info for ak4pfjets
    int nGoodJets=0.;
    int nFailJets=0.;
    unsigned int jindex=0;
    float HT = 0.;
    float JET_PT = 0.;
    int nbtags_med = 0;
    int nbtags_tight = 0;
    int nbtags_loose = 0;
    static const float BTAG_MED = 0.6324;  // DeepCSV working points
    static const float BTAG_LSE = 0.2219;
    static const float BTAG_TGT = 0.9432;
    float dPhiM = 0.;
    float btagdisc = 0.;   
    unsigned int leadbtag_idx = 0;

    float htssm = 0.;
    float htosm = 0.;
    float htratiom = 0.;

    nskimjets = 0;
    nskimbtagmed = 0;
    nskimbtagtight = 0;
    nskimbtagloose = 0;

    // Figure out which convention is in use for DeepCSV discriminator names
    // and store it statically so we don't have to re-find it for every event
    static TString deepCSV_prefix = "NULL";
    if( deepCSV_prefix == "NULL" ) {
      for( TString discName : pfjets_bDiscriminatorNames() ) {
        if( discName.Contains("pfDeepCSV") ) { // 2017 convention
          deepCSV_prefix = "pfDeepCSV";
          break;
        }
        else if( discName.Contains("deepFlavour") ) { // 2016 convention
          deepCSV_prefix = "deepFlavour";
          break;
        }
      } // end loop over b discriminator names

      if( deepCSV_prefix == "NULL" ) {
        cout << "Error in JetTree.cc: Can't find DeepCSV discriminator names!" << endl;
        exit(1);
      }
    } // end if prefix == "NULL"

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

	double corr = 1;
 	if(applynewcorr){
          // get L1FastL2L3Residual total correction
          corrector->setRho   ( cms3.evt_fixgridfastjet_all_rho() );
          corrector->setJetA  ( cms3.pfjets_area().at(iJet)       );
          corrector->setJetPt ( pfjet_p4_uncor.pt()               );
          corrector->setJetEta( pfjet_p4_uncor.eta()              );
          corr = corrector->getCorrection();
	}

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
                ak4pfjet_overlep1_CSV = pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag().at(jindex);
                ak4pfjet_overlep1_deepCSV = getbtagvalue(deepCSV_prefix+"JetTags:probb",jindex) + getbtagvalue(deepCSV_prefix+"JetTags:probbb",jindex);
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
                ak4pfjet_overlep2_CSV = pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag().at(jindex);
                ak4pfjet_overlep2_deepCSV = getbtagvalue(deepCSV_prefix+"JetTags:probb",jindex) + getbtagvalue(deepCSV_prefix+"JetTags:probbb",jindex);
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
        nskimjets++;
        bool is_jetpt30 = (p4sCorrJets.at(jindex).pt() >= 30);
        if (is_jetpt30) nGoodJets++;

        ak4pfjets_p4.push_back(p4sCorrJets.at(jindex));
        ak4pfjets_pt.push_back(p4sCorrJets.at(jindex).pt());
        ak4pfjets_eta.push_back(p4sCorrJets.at(jindex).eta());
        ak4pfjets_phi.push_back(p4sCorrJets.at(jindex).phi());
        ak4pfjets_mass.push_back(p4sCorrJets.at(jindex).mass());

        float value_deepCSV = getbtagvalue(deepCSV_prefix+"JetTags:probb",jindex) + getbtagvalue(deepCSV_prefix+"JetTags:probbb",jindex);
        dphi_ak4pfjet_met.push_back(getdphi(p4sCorrJets.at(jindex).phi(), evt_pfmetPhi()));//this can be false - due to correction to pfmet, but it gets corrected later
        ak4pfjets_CSV.push_back(pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag().at(jindex));
        ak4pfjets_deepCSV.push_back(value_deepCSV);
        ak4pfjets_mva.push_back(getbtagvalue("pfCombinedMVAV2BJetTags", jindex));
        ak4pfjets_puid.push_back(loosePileupJetId(jindex));
        ak4pfjets_parton_flavor.push_back(pfjets_partonFlavour().at(jindex));
	ak4pfjets_hadron_flavor.push_back(pfjets_hadronFlavour().at(jindex));
        ak4pfjets_loose_puid.push_back(loosePileupJetId(jindex));
        ak4pfjets_loose_pfid.push_back(isLoosePFJetV2(jindex));
        //ak4pfjets_medium_pfid.push_back(isMediumPFJetV2(jindex));
        ak4pfjets_tight_pfid.push_back(isTightPFJetV2(jindex));

        if (doResolveTopMVA) {
          ak4pfjets_cvsl.push_back(getbtagvalue("pfCombinedCvsLJetTags", jindex));
          ak4pfjets_ptD.push_back(pfjets_ptDistribution().at(jindex));
          ak4pfjets_axis1.push_back(pfjets_axis1().at(jindex));
          ak4pfjets_mult.push_back(pfjets_totalMultiplicity().at(jindex));
        }
        ak4pfjets_chf.push_back(pfjets_chargedHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_nhf.push_back(pfjets_neutralHadronE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_cef.push_back(pfjets_chargedEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_nef.push_back(pfjets_neutralEmE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
	ak4pfjets_muf.push_back(pfjets_muonE().at(jindex)/ (pfjets_undoJEC().at(jindex)*p4sCorrJets[jindex].energy()) );
        ak4pfjets_cm.push_back(pfjets_chargedMultiplicity().at(jindex));
        ak4pfjets_nm.push_back(cms3.pfjets_neutralMultiplicity().at(jindex));
	
	if (!evt_isRealData() && pfjets_mc3dr().size()>0) {
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

	float eff(1.), effloose(1.), efftight(1.);
	BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
	if (abs(pfjets_hadronFlavour().at(jindex)) == 5) flavor = BTagEntry::FLAV_B;
	else if (abs(pfjets_hadronFlavour().at(jindex)) == 4) flavor = BTagEntry::FLAV_C;
	float pt_cutoff = std::max(30.,std::min(669.,double(p4sCorrJets[jindex].pt())));
	float eta_cutoff = std::min(2.39,fabs(double(p4sCorrJets[jindex].eta())));
	float weight_cent(1.), weight_UP(1.), weight_DN(1.), weight_FS_UP(1.), weight_FS_DN(1.);
	float weight_loose_cent(1.), weight_loose_UP(1.), weight_loose_DN(1.), weight_loose_FS_UP(1.), weight_loose_FS_DN(1.);
	float weight_tight_cent(1.), weight_tight_UP(1.), weight_tight_DN(1.), weight_tight_FS_UP(1.), weight_tight_FS_DN(1.);
	if(applyBtagSFs){
	  //put all b-tag issues outside what is possible
	  effloose = getBtagEffFromFile(p4sCorrJets[jindex].pt(),p4sCorrJets[jindex].eta(), pfjets_hadronFlavour().at(jindex), 0, isFastsim);
	  eff      = getBtagEffFromFile(p4sCorrJets[jindex].pt(),p4sCorrJets[jindex].eta(), pfjets_hadronFlavour().at(jindex), 1, isFastsim);
	  efftight = getBtagEffFromFile(p4sCorrJets[jindex].pt(),p4sCorrJets[jindex].eta(), pfjets_hadronFlavour().at(jindex), 2, isFastsim);
          if (eff == 0 || efftight == 0)
            cerr << "JetTree.cc: Error: 0 btag eff from file found! :" << eff << " " << effloose << " " << efftight << ", pt = " << p4sCorrJets[jindex].pt() << endl;
	  // cout<<"read uncertainty from btagsf reader:"<<endl;
	  if (flavor == BTagEntry::FLAV_UDSG) {
	    weight_cent = reader_light   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_UP   = reader_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_DN   = reader_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_loose_cent = reader_loose_light   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_loose_UP   = reader_loose_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_loose_DN   = reader_loose_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_tight_cent = reader_tight_light   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_tight_UP   = reader_tight_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_tight_DN   = reader_tight_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
	  } else {
	    weight_cent = reader_heavy   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_UP   = reader_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_DN   = reader_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_loose_cent = reader_loose_heavy   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_loose_UP   = reader_loose_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_loose_DN   = reader_loose_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_tight_cent = reader_tight_heavy   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_tight_UP   = reader_tight_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_tight_DN   = reader_tight_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
	  }
	  if (isFastsim) {
	    weight_FS_UP = reader_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff) * weight_cent;
	    weight_FS_DN = reader_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff) * weight_cent;
	    weight_cent *= reader_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_UP   *= reader_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);//this is still just btagSF
	    weight_DN   *= reader_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);//this is still just btagSF
	    weight_loose_FS_UP = reader_loose_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff) * weight_loose_cent;
	    weight_loose_FS_DN = reader_loose_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff) * weight_loose_cent;
	    weight_loose_cent *= reader_loose_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_loose_UP   *= reader_loose_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);//this is still just btagSF
	    weight_loose_DN   *= reader_loose_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);//this is still just btagSF
	    weight_tight_FS_UP = reader_tight_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff) * weight_tight_cent;
	    weight_tight_FS_DN = reader_tight_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff) * weight_tight_cent;
	    weight_tight_cent *= reader_tight_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);
	    weight_tight_UP   *= reader_tight_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);//this is still just btagSF
	    weight_tight_DN   *= reader_tight_fastsim   ->eval(flavor, eta_cutoff, pt_cutoff);//this is still just btagSF
	  }
	}
	//medium btag
	if (value_deepCSV > BTAG_MED) {
             ak4pfjets_passMEDbtag.push_back(true);
             nskimbtagmed++;
             if (is_jetpt30) nbtags_med++;
             if(nbtags_med == 1){
                ak4pfjets_leadMEDbjet_pt = p4sCorrJets.at(jindex).pt();  //plot leading bjet pT
                ak4pfjets_leadMEDbjet_p4 = p4sCorrJets.at(jindex);
             }
                ak4pfjets_MEDbjet_pt.push_back(p4sCorrJets.at(jindex).pt());
               //bool isFastsim = false; 
              // btag SF - not final yet
              if (!evt_isRealData()&&applyBtagSFs) {
  //              cout<<"got uncertainty from btagsf reader:"<<endl;
                btagprob_data *= weight_cent * eff;
                btagprob_mc *= eff;
		if (flavor == BTagEntry::FLAV_UDSG) {
		  btagprob_light_UP *= weight_UP * eff;
		  btagprob_light_DN *= weight_DN * eff;
		  btagprob_heavy_UP *= weight_cent * eff;
		  btagprob_heavy_DN *= weight_cent * eff;
		} else {
		  btagprob_light_UP *= weight_cent * eff;
		  btagprob_light_DN *= weight_cent * eff;
		  btagprob_heavy_UP *= weight_UP * eff;
		  btagprob_heavy_DN *= weight_DN * eff;
                }
		if(isFastsim){
		  btagprob_FS_UP *= weight_FS_UP * eff;
		  btagprob_FS_DN *= weight_FS_DN * eff;
		}
//                cout<<"btagprob_err_heavy_UP"<<btagprob_err_heavy_UP<<endl;
               }
            }else{ 
             ak4pfjets_passMEDbtag.push_back(false);
             if (!evt_isRealData()&&applyBtagSFs) { // fail med btag -- needed for SF event weights
              btagprob_data *= (1. - weight_cent * eff);
              btagprob_mc *= (1. - eff);
	      if (flavor == BTagEntry::FLAV_UDSG) {
		btagprob_light_UP *= (1. - weight_UP * eff);
		btagprob_light_DN *= (1. - weight_DN * eff);
		btagprob_heavy_UP *= (1. - weight_cent * eff);
		btagprob_heavy_DN *= (1. - weight_cent * eff);
              } else {
		btagprob_light_UP *= (1. - weight_cent * eff);
		btagprob_light_DN *= (1. - weight_cent * eff);
		btagprob_heavy_UP *= (1. - weight_UP * eff);
		btagprob_heavy_DN *= (1. - weight_DN * eff);
              }
	      if(isFastsim){
		btagprob_FS_UP *= (1. - weight_FS_UP * eff);
		btagprob_FS_DN *= (1. - weight_FS_DN * eff);
	      }
           }
        }//finish medium
        if (value_deepCSV > btagdisc) {
          btagdisc = value_deepCSV;
	  leadbtag_idx = jindex;
	}
	//loose btag
	if (value_deepCSV > BTAG_LSE) {
              nskimbtagloose++;
              if (is_jetpt30) nbtags_loose++;
              if (!evt_isRealData()&&applyBtagSFs) {
                loosebtagprob_data *= weight_loose_cent * effloose;
                loosebtagprob_mc *= effloose;
		if (flavor == BTagEntry::FLAV_UDSG) {
		  loosebtagprob_light_UP *= weight_loose_UP * effloose;
		  loosebtagprob_light_DN *= weight_loose_DN * effloose;
		  loosebtagprob_heavy_UP *= weight_loose_cent * effloose;
		  loosebtagprob_heavy_DN *= weight_loose_cent * effloose;
		} else {
		  loosebtagprob_light_UP *= weight_loose_cent * effloose;
		  loosebtagprob_light_DN *= weight_loose_cent * effloose;
		  loosebtagprob_heavy_UP *= weight_loose_UP * effloose;
		  loosebtagprob_heavy_DN *= weight_loose_DN * effloose;
                }
		if(isFastsim){
		  loosebtagprob_FS_UP *= weight_loose_FS_UP * effloose;
		  loosebtagprob_FS_DN *= weight_loose_FS_DN * effloose;
		}
               }
            }else{ 
             if (!evt_isRealData()&&applyBtagSFs) { // fail loose btag -- needed for SF event weights
              loosebtagprob_data *= (1. - weight_loose_cent * effloose);
              loosebtagprob_mc *= (1. - effloose);
	      if (flavor == BTagEntry::FLAV_UDSG) {
		loosebtagprob_light_UP *= (1. - weight_loose_UP * effloose);
		loosebtagprob_light_DN *= (1. - weight_loose_DN * effloose);
		loosebtagprob_heavy_UP *= (1. - weight_loose_cent * effloose);
		loosebtagprob_heavy_DN *= (1. - weight_loose_cent * effloose);
              } else {
		loosebtagprob_light_UP *= (1. - weight_loose_cent * effloose);
		loosebtagprob_light_DN *= (1. - weight_loose_cent * effloose);
		loosebtagprob_heavy_UP *= (1. - weight_loose_UP * effloose);
		loosebtagprob_heavy_DN *= (1. - weight_loose_DN * effloose);
              }
	      if(isFastsim){
		loosebtagprob_FS_UP *= (1. - weight_loose_FS_UP * effloose);
		loosebtagprob_FS_DN *= (1. - weight_loose_FS_DN * effloose);
	      }
           }
        }//finish loose
	//tight btag
	if (value_deepCSV > BTAG_TGT) {
             nskimbtagtight++;
             if (is_jetpt30) nbtags_tight++;
              if (!evt_isRealData()&&applyBtagSFs) {
                tightbtagprob_data *= weight_tight_cent * efftight;
                tightbtagprob_mc *= efftight;
		if (flavor == BTagEntry::FLAV_UDSG) {
		  tightbtagprob_light_UP *= weight_tight_UP * efftight;
		  tightbtagprob_light_DN *= weight_tight_DN * efftight;
		  tightbtagprob_heavy_UP *= weight_tight_cent * efftight;
		  tightbtagprob_heavy_DN *= weight_tight_cent * efftight;
		} else {
		  tightbtagprob_light_UP *= weight_tight_cent * efftight;
		  tightbtagprob_light_DN *= weight_tight_cent * efftight;
		  tightbtagprob_heavy_UP *= weight_tight_UP * efftight;
		  tightbtagprob_heavy_DN *= weight_tight_DN * efftight;
                }
		if(isFastsim){
		  tightbtagprob_FS_UP *= weight_tight_FS_UP * efftight;
		  tightbtagprob_FS_DN *= weight_tight_FS_DN * efftight;
		}
               }
        } else { 
          if (!evt_isRealData()&&applyBtagSFs) { // fail tight btag -- needed for SF event weights
              tightbtagprob_data *= (1. - weight_tight_cent * efftight);
              tightbtagprob_mc *= (1. - efftight);
	      if (flavor == BTagEntry::FLAV_UDSG) {
		tightbtagprob_light_UP *= (1. - weight_tight_UP * efftight);
		tightbtagprob_light_DN *= (1. - weight_tight_DN * efftight);
		tightbtagprob_heavy_UP *= (1. - weight_tight_cent * efftight);
		tightbtagprob_heavy_DN *= (1. - weight_tight_cent * efftight);
              } else {
		tightbtagprob_light_UP *= (1. - weight_tight_cent * efftight);
		tightbtagprob_light_DN *= (1. - weight_tight_cent * efftight);
		tightbtagprob_heavy_UP *= (1. - weight_tight_UP * efftight);
		tightbtagprob_heavy_DN *= (1. - weight_tight_DN * efftight);
              }
	      if(isFastsim){
		tightbtagprob_FS_UP *= (1. - weight_tight_FS_UP * efftight);
		tightbtagprob_FS_DN *= (1. - weight_tight_FS_DN * efftight);
	      }
           }
        }//finish tight
    }

    ak4pfjets_leadbtag_p4 = p4sCorrJets.at(leadbtag_idx);//highest discriminator jet

    ngoodjets = nGoodJets;
    nfailjets = nFailJets;
    ak4_HT = HT;
    HT=0;
    ngoodbtags = nbtags_med;
    nloosebtags = nbtags_loose;
    ntightbtags = nbtags_tight;

    ak4_htssm = htssm;
    ak4_htosm = htosm;
    htratiom   = htssm / (htosm + htssm);
    ak4_htratiom = htratiom; 

    nGoodJets = 0;

    // fill info for genjets
    if (!evt_isRealData()){
      for (size_t idx = 0; idx < genjets_p4NoMuNoNu().size(); ++idx){
        if (genjets_p4NoMuNoNu().at(idx).pt() < m_ak4_pt_cut) continue;
 
        ak4genjets_p4.push_back(genjets_p4NoMuNoNu().at(idx));
        if(genjets_p4NoMuNoNu().at(idx).pt() > 20.)  nGoodJets++;
      }
    }
    nGoodGenJets = nGoodJets;

    nGoodJets = 0;
    if (doResolveTopMVA && ngoodbtags > 0) {
      resTopMVA->setJetVecPtrs(&ak4pfjets_p4, &ak4pfjets_CSV, &ak4pfjets_cvsl, &ak4pfjets_ptD, &ak4pfjets_axis1, &ak4pfjets_mult);
      std::vector<TopCand> resMVATopCands = resTopMVA->getTopCandidates(-1);
      for (auto tcand : resMVATopCands) {
        topcands_ak4idx.emplace_back( std::vector<int>{tcand.getIdxForb(), tcand.getIdxForj2(), tcand.getIdxForj3()} );
        topcands_disc.push_back( tcand.disc );
        topcands_p4.push_back( tcand.topcand );
        topcands_Wp4.push_back( tcand.wcand );
      }
    }
}
        
// fill info for ak8pfjets
void JetTree::FillAK8Jets(bool applynewcorr, FactorizedJetCorrector* corrector, JetCorrectionUncertainty* jetcorr_uncertainty, int JES_type)
{
  int nGoodJets = 0;

  for (size_t idx = 0; idx < ak8jets_p4().size(); ++idx) {
    if (ak8jets_p4()[idx].pt() < m_ak8_pt_cut) continue;
    if (fabs(ak8jets_p4()[idx].eta()) > m_ak8_eta_cut) continue;
    if (!isFastsim && m_ak8_passid && !isLoosePFJetV2(idx)) continue;
    nGoodJets++;

    float corr = 1;
    if(applynewcorr){
      // get L1FastL2L3Residual total correction
      corrector->setRho   ( evt_fixgridfastjet_all_rho() );
      corrector->setJetA  ( ak8jets_area().at(idx)       );
      corrector->setJetPt ( ak8jets_p4()[idx].pt()       );
      corrector->setJetEta( ak8jets_p4()[idx].eta()      );
      corr = corrector->getCorrection();

      // check for negative correction
      if (corr < 0. && fabs(ak8jets_p4()[idx].eta()) < 4.7) {
        std::cout << "ScanChain::Looper: WARNING: negative ak8jet correction: " << corr
                  << ", raw jet pt: " << ak8jets_p4()[idx].pt() << ", eta: " << ak8jets_p4()[idx].eta() << std::endl;
      }

      // include protections here on jet kinematics to prevent rare warnings/crashes
      double var = 1.;
      if (!evt_isRealData() && JES_type != 0 && ak8jets_p4()[idx].pt()*corr > 0. && fabs(ak8jets_p4()[idx].eta()) < 5.4) {
        jetcorr_uncertainty->setJetPt (ak8jets_p4()[idx].pt() * corr); // must use CORRECTED pt
        jetcorr_uncertainty->setJetEta(ak8jets_p4()[idx].eta());
        double unc = jetcorr_uncertainty->getUncertainty(true);
        var = (1. + JES_type * unc);
      }

      // apply new JEC to p4
      // newjecorr.push_back(corr);
      ak8pfjets_p4.push_back(ak8jets_p4()[idx] * corr * var);
    } else {
      ak8pfjets_p4.push_back(ak8jets_p4().at(idx));
    }

    ak8pfjets_tau1.push_back(ak8jets_nJettinessTau1().at(idx));
    ak8pfjets_tau2.push_back(ak8jets_nJettinessTau2().at(idx));
    ak8pfjets_tau3.push_back(ak8jets_nJettinessTau3().at(idx));
    ak8pfjets_pruned_mass.push_back(ak8jets_prunedMass().at(idx));
    ak8pfjets_softdrop_mass.push_back(ak8jets_softdropMass().at(idx));
    ak8pfjets_parton_flavor.push_back(ak8jets_partonFlavour().at(idx));

    // Branches no longer in cms4
    // ak8pfjets_top_mass.push_back(ak8jets_topJetMass().at(idx));
    // ak8pfjets_trimmed_mass.push_back(ak8jets_trimmedMass().at(idx));
    // ak8pfjets_filtered_mass.push_back(ak8jets_filteredMass().at(idx));

    // ak8pfjets_pu_id.push_back(ak8jets_pileupJetId().at(idx));
  }

  nGoodAK8PFJets = nGoodJets;
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
    delete reader_loose_heavy;
    delete reader_loose_heavy_UP;
    delete reader_loose_heavy_DN;
    delete reader_loose_light;
    delete reader_loose_light_UP;
    delete reader_loose_light_DN;
    delete reader_loose_fastsim;
    delete reader_loose_fastsim_UP;
    delete reader_loose_fastsim_DN;
    delete reader_tight_heavy;
    delete reader_tight_heavy_UP;
    delete reader_tight_heavy_DN;
    delete reader_tight_light;
    delete reader_tight_light_UP;
    delete reader_tight_light_DN;
    delete reader_tight_fastsim;
    delete reader_tight_fastsim_UP;
    delete reader_tight_fastsim_DN;
    
    delete feff;
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
    ak4pfjets_deepCSV.clear();
    ak4pfjets_mva.clear();
    ak4pfjets_puid.clear();
    ak4pfjets_parton_flavor.clear();
    ak4pfjets_hadron_flavor.clear();
    ak4pfjets_loose_puid.clear();
    ak4pfjets_loose_pfid.clear();
    ak4pfjets_medium_pfid.clear();
    ak4pfjets_tight_pfid.clear();

    ak4pfjets_cvsl.clear();
    ak4pfjets_ptD.clear();
    ak4pfjets_axis1.clear();
    ak4pfjets_mult.clear();

    topcands_ak4idx.clear();
    topcands_disc.clear();
    topcands_p4.clear();
    topcands_Wp4.clear();

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
    ak4pfjet_overlep1_deepCSV = -9999;
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
    ak4pfjet_overlep2_deepCSV = -9999;
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
    ak8pfjets_softdrop_mass.clear();
    ak8pfjets_filtered_mass.clear();
    ak8pfjets_pu_id.clear();    
    ak8pfjets_parton_flavor.clear();
 
    ak4genjets_p4.clear();
 
    ak4pfjets_MEDbjet_pt.clear();
    ak4pfjets_passMEDbtag.clear();
    ak4pfjets_leadMEDbjet_pt = -9999; 
    ak4pfjets_leadMEDbjet_p4 = LorentzVector(0,0, 0,0);
    ak4pfjets_leadbtag_p4 = LorentzVector(0,0, 0,0);
  
    nskimjets      = -9999;
    nskimbtagmed   = -9999;
    nskimbtagloose = -9999;
    nskimbtagtight = -9999;
    ngoodjets     = -9999;  
    nfailjets     = -9999;  
    ak4_HT 	  = -9999.; 
    nGoodAK8PFJets = -9999;
    nGoodGenJets  = -9999;
    ngoodbtags    = -9999;
    nloosebtags    = -9999;
    ntightbtags    = -9999;
    nanalysisbtags = -9999;
}
 
void JetTree::SetAK4Branches (TTree* tree)
{
    tree->Branch(Form("%snskimjets", prefix_.c_str()) , &nskimjets);
    tree->Branch(Form("%snskimbtagmed", prefix_.c_str()) , &nskimbtagmed);
    tree->Branch(Form("%snskimbtagloose", prefix_.c_str()) , &nskimbtagloose);
    tree->Branch(Form("%snskimbtagtight", prefix_.c_str()) , &nskimbtagtight);
    tree->Branch(Form("%sngoodjets", prefix_.c_str()) , &ngoodjets);
    tree->Branch(Form("%sngoodbtags", prefix_.c_str()) , &ngoodbtags);
    tree->Branch(Form("%snloosebtags", prefix_.c_str()) , &nloosebtags);
    tree->Branch(Form("%sntightbtags", prefix_.c_str()) , &ntightbtags);
    tree->Branch(Form("%snanalysisbtags", prefix_.c_str()) , &nanalysisbtags);
    tree->Branch(Form("%sak4_HT", prefix_.c_str()) , &ak4_HT);
    tree->Branch(Form("%sak4_htratiom", prefix_.c_str()) , &ak4_htratiom);
    tree->Branch(Form("%sdphi_ak4pfjet_met", prefix_.c_str()) , &dphi_ak4pfjet_met);

    tree->Branch(Form("%sak4pfjets_p4", prefix_.c_str()) , &ak4pfjets_p4);

    tree->Branch(Form("%sak4pfjets_passMEDbtag", prefix_.c_str()) , &ak4pfjets_passMEDbtag);
    tree->Branch(Form("%sak4pfjets_deepCSV", prefix_.c_str()) , &ak4pfjets_deepCSV);
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
    tree->Branch(Form("%sak8pfjets_softdrop_mass", prefix_.c_str()) , &ak8pfjets_softdrop_mass);
    tree->Branch(Form("%sak8pfjets_pu_id", prefix_.c_str()) , &ak8pfjets_pu_id);    
    tree->Branch(Form("%sak8pfjets_parton_flavor", prefix_.c_str()) , &ak8pfjets_parton_flavor);
    tree->Branch(Form("%snGoodAK8PFJets", prefix_.c_str()) , &nGoodAK8PFJets);
}

void JetTree::SetAK4Branches_Overleps (TTree* tree)
{
    tree->Branch(Form("%sak4pfjet_overlep1_p4", prefix_.c_str()) , &ak4pfjet_overlep1_p4);                                                                                    
    tree->Branch(Form("%sak4pfjet_overlep1_deepCSV", prefix_.c_str()) , &ak4pfjet_overlep1_deepCSV);
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
    tree->Branch(Form("%sak4pfjet_overlep2_deepCSV", prefix_.c_str()) , &ak4pfjet_overlep2_deepCSV);
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

void JetTree::SetAK4Branches_TopTag(TTree* tree)
{
    tree->Branch(Form("%sak4pfjets_cvsl", prefix_.c_str()) , &ak4pfjets_cvsl);
    tree->Branch(Form("%sak4pfjets_ptD", prefix_.c_str()) , &ak4pfjets_ptD);
    tree->Branch(Form("%sak4pfjets_axis1", prefix_.c_str()) , &ak4pfjets_axis1);
    tree->Branch(Form("%sak4pfjets_mult", prefix_.c_str()) , &ak4pfjets_mult);

    tree->Branch(Form("%stopcands_ak4idx", prefix_.c_str()) , &topcands_ak4idx);
    tree->Branch(Form("%stopcands_disc", prefix_.c_str()) , &topcands_disc);
    tree->Branch(Form("%stopcands_p4", prefix_.c_str()) , &topcands_p4);
    tree->Branch(Form("%stopcands_Wp4", prefix_.c_str()) , &topcands_Wp4);
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
