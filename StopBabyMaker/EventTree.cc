#include "EventTree.h"
#include "TString.h"
#include "CMS3.h"
#include "VertexSelections.h"
#include "StopSelections.h"
#include "MetSelections.h"

using namespace tas; 
EventTree::EventTree ()
{
}
 
EventTree::EventTree (const std::string &prefix)
    : prefix_(prefix)
{
}
 
void EventTree::FillCommon (const std::string &root_file_name)
{
    bool signal=false;

    std::string filestr (root_file_name);
    string signalstr ("mStop");

    if (filestr.find(signalstr) != string::npos) signal = true;
    //std::cout << "run "<<evt_run()<<" lumiblock "<<evt_lumiBlock() <<" event "<<evt_event()<<" nvtxs "<<numberOfGoodVertices()<<" pfmet "<<evt_pfmet()<<" pfmetphi "<< evt_pfmetPhi()<< std::endl;
    run = evt_run();
    ls  = evt_lumiBlock();
    evt = evt_event();
    nvtxs = numberOfGoodVertices();

    firstGoodVtxIdx = firstGoodVertex();
    firstVtx_isfake = vtxs_isFake()[0];
    firstVtx_ndof   = vtxs_ndof()[0];
    firstVtx_posRho = vtxs_position()[0].Rho();
    firstVtx_posZ   = vtxs_position()[0].Z();
    firstVtx_posp4  = vtxs_position()[0];
 
    pfmet = evt_pfmet();
    pfmet_phi = evt_pfmetPhi();
    calomet = evt_calomet();
    calomet_phi = evt_calometPhi();

    is_data = evt_isRealData();

///the recommended met filters//
        filt_cscbeamhalo = filt_cscBeamHalo();
        filt_eebadsc = filt_eeBadSc();
        filt_goodvtx = filt_goodVertices(); //not working but same as our 1goodvertex requirement
        filt_hbhenoise = hbheNoiseFilter();
////////////// 
        filt_ecallaser = filt_ecalLaser();
        filt_ecaltp = filt_ecalTP();
        filt_hcallaser = filt_hcalLaser();
        filt_met = filt_metfilter();
        filt_trkfail = filt_trackingFailure();
        filt_trkPOG = filt_trkPOGFilters();
        filt_trkPOG_tmc = filt_trkPOG_logErrorTooManyClusters();
        filt_trkPOG_tms = filt_trkPOG_toomanystripclus53X();
        filt_eff = evt_filt_eff();

    if (!is_data)
    {
        scale1fb = evt_scale1fb();
        xsec     = evt_xsec_incl();
        kfactor  = evt_kfactor();
        pu_nvtxs = puInfo_nPUvertices().at(6);
        pu_ntrue = puInfo_trueNumInteractions().at(0);

        if(signal){
          sparms_values = sparm_values();
          for ( auto name : sparm_names() )
            sparms_names.push_back(name.Data());

          sparms_filterEfficiency = sparm_filterEfficiency();
          sparms_pdfScale         = sparm_pdfScale();
          sparms_pdfWeight1       = sparm_pdfWeight1();
          sparms_pdfWeight2       = sparm_pdfWeight2();
          sparms_weight           = sparm_weight();
          sparms_xsec             = sparm_xsec();
          sparms_subProcessId     = sparm_subProcessId();
        }
        genmet = gen_met();
        genmet_phi = gen_metPhi();

    }
    dataset = evt_dataset().at(0).Data();
    filename = root_file_name;
    cms3tag = evt_CMS3tag().at(0).Data();


    //EA rho
    EA_all_rho                  = evt_fixgrid_all_rho();
    EA_allcalo_rho              = evt_fixgridfastjet_allcalo_rho();
    EA_centralcalo_rho          = evt_fixgridfastjet_centralcalo_rho();
    EA_centralchargedpileup_rho = evt_fixgridfastjet_centralchargedpileup_rho();
    EA_centralneutral_rho       = evt_fixgridfastjet_centralneutral_rho(); 
}
 
void EventTree::Reset ()
{
    run = 0;
    ls = 0;
    evt = 0;

    ngoodleps      =  -9999;
    nvetoleps      =  -9999;
    genlepsfromtop = -9999;
     
    nvtxs 	=  -9999;
    pu_nvtxs 	=  -9999;

    firstGoodVtxIdx   = -9999;//not necessarily first vertex
    firstVtx_isfake   = -9999;
    firstVtx_ndof     = -9999.;
    firstVtx_posRho   = -9999.;
    firstVtx_posZ     = -9999.;
    firstVtx_posp4    = LorentzVector(0,0, 0,0);
    pfmet             = -9999.;
    pfmet_phi         = -9999.;
    calomet           = -9999.;
    calomet_phi       = -9999.;
    scale1fb          = -9999.;
    xsec              = -9999.;
    kfactor           = -9999.;
    pu_ntrue          = -9999.;
    dR_lep_leadb      = -9999.;
    dR_lep2_leadb     = -9999.;
    MT2W              = -9999.;
    MT2W_lep2         = -9999.;
    mindphi_met_j1_j2 = -9999.;
    mt_met_lep        = -9999.;
    mt_met_lep2       = -9999.;
    hadronic_top_chi2 = -9999.; 
    is_data = false;
 
    topness              = -9999.; 
    topness_lep2         = -9999.; 
    topnessMod           = -9999.; 
    topnessMod_lep2      = -9999.; 
    MT2_lb_b             = -9999.; 
    MT2_lb_b_lep2        = -9999.; 
    MT2_lb_b_mass        = -9999.; 
    MT2_lb_b_mass_lep2   = -9999.; 
    MT2_lb_bqq           = -9999.; 
    MT2_lb_bqq_lep2      = -9999.; 
    MT2_lb_bqq_mass      = -9999.; 
    MT2_lb_bqq_mass_lep2 = -9999.; 
    Mlb_closestb         = -9999.; 
    Mlb_lead_bdiscr      = -9999.; 
    Mlb_closestb_lep2    = -9999.; 
    Mlb_lead_bdiscr_lep2 = -9999.; 
    Mjjj                 = -9999.; 
    Mjjj_lep2            = -9999.; 

    dphi_Wlep       = -9999.;
    MET_over_sqrtHT = -9999.;
    ak4pfjets_rho   = -9999.;

    dataset  = "";
    filename = "";
    cms3tag  = "";

    sparms_comment.clear();
    sparms_names.clear();
    sparms_filterEfficiency	= -9999.;
    sparms_pdfScale		= -9999.;
    sparms_pdfWeight1		= -9999.;
    sparms_pdfWeight2		= -9999.;
    sparms_weight		= -9999.;
    sparms_xsec			= -9999.;
    sparms_values.clear();
    sparms_subProcessId 	= -9999;
    mass_stop                   = -9999;
    mass_lsp                    = -9999;
    mass_chargino               = -9999;

    genmet 	= -9999.;
    genmet_phi 	= -9999.;
    PassTrackVeto    = false;
    PassTrackVeto_v2 = false;
    PassTrackVeto_v3 = false;
    PassTauVeto      = false;

    HLT_MET170             = -9999.;
    HLT_SingleMu           = -9999.; 
    HLT_SingleEl           = -9999.;
    HLT_MET120Btag         = -9999.;      
    HLT_MET120Mu5          = -9999.;      
    HLT_HT350MET120        = -9999.;
    HLT_DiEl               = -9999.;
    HLT_DiMu               = -9999.;
    HLT_Mu8El17            = -9999.;
    HLT_Mu8El23            = -9999.;
    HLT_Mu17El12           = -9999.;
    HLT_Mu23El12           = -9999.;
    HLT_SingleEl27         = -9999.;
    HLT_SingleEl27Tight    = -9999.;
    HLT_SingleElTight      = -9999.;
    HLT_SingleElHT200      = -9999.;
    HLT_SingleMuNoEta      = -9999.;
    HLT_SingleMuNoIso      = -9999.;
    HLT_SingleMuNoIsoNoEta = -9999.;
    HLT_Mu6HT200MET125     = -9999.;
    HLT_HT350MET100	   = -9999.;
    HLT_SingleMu17         = -9999.;
    HLT_SingleMu20         = -9999.;
    HLT_SingleMu24         = -9999.;
    HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight = -9999.;
    HLT_MET90_MHT90_IDTight                         = -9999.;
    HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight    = -9999.; 

    
    EA_all_rho                  = -9999.;
    EA_allcalo_rho              = -9999.; 
    EA_centralcalo_rho          = -9999.; 
    EA_centralchargedpileup_rho = -9999.; 
    EA_centralneutral_rho       = -9999.;

    pu_weight        =  -9999;
    lep_sf           =  -9999;
    btag_sf          =  -9999;
    HLT_SingleMu_eff =  -9999;
    HLT_SingleEl_eff =  -9999;

        filt_cscbeamhalo = false;
        filt_ecallaser = false;
        filt_ecaltp = false;
        filt_eebadsc = false;
        filt_goodvtx = false;
        filt_hbhenoise = false;
        filt_hcallaser = false;
        filt_met = false;
        filt_trkfail = false;
        filt_trkPOG = false;
        filt_trkPOG_tmc = false;
        filt_trkPOG_tms = false;
        filt_eff = -9999.;



}
 
void EventTree::SetBranches (TTree* tree)
{
    tree->Branch("run", &run);
    tree->Branch("ls", &ls);
    tree->Branch("evt", &evt);   
    tree->Branch("nvtxs", &nvtxs);
    tree->Branch("firstGoodVtxIdx", &firstGoodVtxIdx);
    tree->Branch("firstVtx_isfake", &firstVtx_isfake);
    tree->Branch("firstVtx_ndof", &firstVtx_ndof);
    tree->Branch("firstVtx_posRho", &firstVtx_posRho);
    tree->Branch("firstVtx_posZ", &firstVtx_posZ);
    tree->Branch("firstVtx_posp4", &firstVtx_posp4);
    tree->Branch("pu_nvtxs", &pu_nvtxs);
    tree->Branch("pfmet", &pfmet);
    tree->Branch("pfmet_phi", &pfmet_phi);
    tree->Branch("calomet", &calomet);
    tree->Branch("calomet_phi", &calomet_phi);
    tree->Branch("filt_cscbeamhalo", &filt_cscbeamhalo);
    tree->Branch("filt_ecallaser", &filt_ecallaser);
    tree->Branch("filt_ecaltp", &filt_ecaltp);
    tree->Branch("filt_eebadsc", &filt_eebadsc);
    tree->Branch("filt_goodvtx", &filt_goodvtx);
    tree->Branch("filt_hbhenoise", &filt_hbhenoise);
    tree->Branch("filt_hcallaser", &filt_hcallaser);
    tree->Branch("filt_met", &filt_met);
    tree->Branch("filt_trkfail", &filt_trkfail);
    tree->Branch("filt_trkPOG", &filt_trkPOG);
    tree->Branch("filt_trkPOG_tmc", &filt_trkPOG_tmc);
    tree->Branch("filt_trkPOG_tms", &filt_trkPOG_tms);
    tree->Branch("filt_eff", &filt_eff);
    tree->Branch("scale1fb", &scale1fb);
    tree->Branch("xsec", &xsec);
    tree->Branch("kfactor", &kfactor);
    tree->Branch("pu_ntrue", &pu_ntrue);    
    tree->Branch("ngoodleps",&ngoodleps);
    tree->Branch("nvetoleps",&nvetoleps);
    tree->Branch("is_data", &is_data);
    tree->Branch("dataset", &dataset);
    tree->Branch("filename", &filename);
    tree->Branch("cms3tag", &cms3tag);
    tree->Branch("nEvents", &nEvents);
    tree->Branch("nEvents_goodvtx", &nEvents_goodvtx);
    tree->Branch("nEvents_MET30", &nEvents_MET30);
    tree->Branch("nEvents_1goodlep", &nEvents_1goodlep);
    tree->Branch("nEvents_2goodjets", &nEvents_2goodjets);
    tree->Branch("genlepsfromtop", &genlepsfromtop);
    tree->Branch("MT2W",&MT2W);
    tree->Branch("MT2W_lep2",&MT2W_lep2);
    tree->Branch("mindphi_met_j1_j2", &mindphi_met_j1_j2);
    tree->Branch("mt_met_lep", &mt_met_lep);
    tree->Branch("mt_met_lep2", &mt_met_lep2);
    tree->Branch("dR_lep_leadb", &dR_lep_leadb);
    tree->Branch("dR_lep2_leadb", &dR_lep2_leadb);
    tree->Branch("hadronic_top_chi2", &hadronic_top_chi2);
    tree->Branch("dphi_Wlep", &dphi_Wlep);
    tree->Branch("MET_over_sqrtHT", &MET_over_sqrtHT);
    tree->Branch("ak4pfjets_rho", &ak4pfjets_rho);
    tree->Branch("sparms_comment", &sparms_comment);
    tree->Branch("sparms_names", &sparms_names);
    tree->Branch("sparms_filterEfficiency", &sparms_filterEfficiency);
    tree->Branch("sparms_pdfScale", &sparms_pdfScale);
    tree->Branch("sparms_pdfWeight1", &sparms_pdfWeight1);
    tree->Branch("sparms_pdfWeight2", &sparms_pdfWeight2);
    tree->Branch("sparms_weight", &sparms_weight);
    tree->Branch("sparms_xsec", &sparms_xsec);
    tree->Branch("sparms_values", &sparms_values);
    tree->Branch("sparms_subProcessId", &sparms_subProcessId);
    tree->Branch("mass_lsp", &mass_lsp);
    tree->Branch("mass_chargino", &mass_chargino);
    tree->Branch("mass_stop", &mass_stop);
    tree->Branch("genmet", &genmet);
    tree->Branch("genmet_phi", &genmet_phi);
    tree->Branch("PassTrackVeto",&PassTrackVeto);
    tree->Branch("PassTrackVeto_v2",&PassTrackVeto_v2);
    tree->Branch("PassTrackVeto_v3",&PassTrackVeto_v3);
    tree->Branch("PassTauVeto",&PassTauVeto);
    tree->Branch("EA_all_rho", &EA_all_rho);   
    tree->Branch("EA_allcalo_rho", &EA_allcalo_rho); 
    tree->Branch("EA_centralcalo_rho", &EA_centralcalo_rho); 
    tree->Branch("EA_centralchargedpileup_rho", &EA_centralchargedpileup_rho); 
    tree->Branch("EA_centralneutral_rho", &EA_centralneutral_rho); 
    tree->Branch("topness", &topness); 
    tree->Branch("topness_lep2", &topness_lep2); 
    tree->Branch("topnessMod", &topnessMod); 
    tree->Branch("topnessMod_lep2", &topnessMod_lep2); 
    tree->Branch("MT2_lb_b", &MT2_lb_b); 
    tree->Branch("MT2_lb_b_lep2", &MT2_lb_b_lep2); 
    tree->Branch("MT2_lb_b_mass", &MT2_lb_b_mass); 
    tree->Branch("MT2_lb_b_mass_lep2", &MT2_lb_b_mass_lep2); 
    tree->Branch("MT2_lb_bqq", &MT2_lb_bqq); 
    tree->Branch("MT2_lb_bqq_lep2", &MT2_lb_bqq_lep2); 
    tree->Branch("MT2_lb_bqq_mass", &MT2_lb_bqq_mass); 
    tree->Branch("MT2_lb_bqq_mass_lep2", &MT2_lb_bqq_mass_lep2); 
    tree->Branch("Mlb_closestb", &Mlb_closestb); 
    tree->Branch("Mlb_lead_bdiscr", &Mlb_lead_bdiscr);
    tree->Branch("Mlb_closestb_lep2", &Mlb_closestb_lep2); 
    tree->Branch("Mlb_lead_bdiscr_lep2", &Mlb_lead_bdiscr_lep2);
    tree->Branch("Mjjj", &Mjjj); 
    tree->Branch("Mjjj_lep2", &Mjjj_lep2); 
    tree->Branch("HLT_SingleEl", &HLT_SingleEl );
    tree->Branch("HLT_SingleMu", &HLT_SingleMu );
    tree->Branch("HLT_MET170", &HLT_MET170 );
    tree->Branch("HLT_MET120Btag", &HLT_MET120Btag );
    tree->Branch("HLT_MET120Mu5", &HLT_MET120Mu5 );
    tree->Branch("HLT_HT350MET120", &HLT_HT350MET120 );
    tree->Branch("HLT_DiEl", &HLT_DiEl );
    tree->Branch("HLT_DiMu", &HLT_DiMu );
    tree->Branch("HLT_Mu8El17", &HLT_Mu8El17 );
    tree->Branch("HLT_Mu8El23", &HLT_Mu8El23 );
    tree->Branch("HLT_Mu17El12", &HLT_Mu17El12 );
    tree->Branch("HLT_Mu23El12", &HLT_Mu23El12 );
    tree->Branch("HLT_SingleEl27", &HLT_SingleEl27 );
    tree->Branch("HLT_SingleEl27Tight", &HLT_SingleEl27Tight );
    tree->Branch("HLT_SingleElTight", &HLT_SingleElTight );
    tree->Branch("HLT_SingleElHT200", &HLT_SingleElHT200 );
    tree->Branch("HLT_SingleMuNoEta", &HLT_SingleMuNoEta );
    tree->Branch("HLT_SingleMuNoIso", &HLT_SingleMuNoIso );
    tree->Branch("HLT_SingleMuNoIsoNoEta", &HLT_SingleMuNoIsoNoEta );
    tree->Branch("HLT_Mu6HT200MET100", &HLT_Mu6HT200MET125 );
    tree->Branch("HLT_HT350MET100", &HLT_HT350MET100);
    tree->Branch("HLT_SingleMu17", &HLT_SingleMu17);
    tree->Branch("HLT_SingleMu20", &HLT_SingleMu20);
    tree->Branch("HLT_SingleMu24", &HLT_SingleMu24);
    tree->Branch("HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight", &HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight);
    tree->Branch("HLT_MET90_MHT90_IDTight", &HLT_MET90_MHT90_IDTight);
    tree->Branch("HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight", &HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight); 
    tree->Branch("pu_weight", &pu_weight); 
    tree->Branch("lep_sf", &lep_sf); 
    tree->Branch("btag_sf", &btag_sf); 
    tree->Branch("HLT_SingleEl_eff", &HLT_SingleEl_eff); 
    tree->Branch("HLT_SingleMu_eff", &HLT_SingleMu_eff); 

}
