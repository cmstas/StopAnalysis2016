#include "LeptonTree.h"
#include <algorithm>
#include <cmath>
#include "Math/GenVector/PtEtaPhiE4D.h"
#include "CMS3.h"
#include "ElectronSelections.h"
#include "MuonSelections.h"
#include "MCSelections.h"
#include "VertexSelections.h"
#include "StopSelections.h"
#include "IsolationTools.h"

LeptonTree::LeptonTree ()
{
}

LeptonTree::LeptonTree (const std::string &prefix)
  : prefix_(prefix)
{
}

using namespace tas;

void LeptonTree::FillCommon (int id, int idx)
{
    if (idx < 0) return;
    int vtxidx = firstGoodVertex();
   // is_fromw = not evt_isRealData() ? leptonIsFromW(idx, id, true) : -999999;
  //
  //enum prodType {fromB, fromC, fromLight, fromZ, fromW};
   if( isFromB(id,idx) )production_type.push_back(fromB);
   else if( isFromC(id,idx) )production_type.push_back(fromC);
   else if( isFromLight(id,idx) )production_type.push_back(fromLight);
   else if( isFromZ(id,idx) )production_type.push_back(fromZ);
   else if( isFromW(id,idx) )production_type.push_back(fromW);
   else production_type.push_back(none);

//general stuff
    p4		= abs(id)==11 ? els_p4().at(idx) : mus_p4().at(idx);
    charge	= abs(id)==11 ? els_charge().at(idx) : abs(id)==13 ? mus_charge().at(idx) : -9999;
    pdgid	= charge * -1 * abs(id);
    pt 		= abs(id)==11 ? els_p4().at(idx).pt() : abs(id)==13 ? mus_p4().at(idx).pt() : -9999.;
    eta		= abs(id)==11 ? els_p4().at(idx).eta() : abs(id)==13 ? mus_p4().at(idx).eta() : -9999.;     
    type	= abs(id)==11 ? els_type().at(idx) : abs(id)==13 ? mus_type().at(idx) : -9999;
//mc stuff
    if (!evt_isRealData()) {
            mcp4      = abs(id)==11 ? els_mc_p4().at(idx) : mus_mc_p4().at(idx);
            mcid      = abs(id)==11 ? els_mc_id().at(idx) : abs(id)==13 ? mus_mc_id().at(idx) : -9999 ;

            mcidx       = abs(id)==11 ? els_mcidx().at(idx) : abs(id)==13 ? mus_mcidx().at(idx) : -9999;
            mc_motherid = abs(id)==11 ? els_mc_motherid().at(idx) : abs(id)==13 ? mus_mc_motherid().at(idx) : -9999;
   }
    
//electrons
    if (abs(id) == 11)
    {
        is_el  		= true;

	if (vtxidx >= 0) {
            d0 = els_d0().at(idx);
            dz = els_dzPV().at(idx);
            d0err = els_d0Err().at(idx);
            dzerr = els_z0Err().at(idx);
    	}
        ip3d    = els_ip3d().at(idx);
        ip3derr = els_ip3derr().at(idx);

	//ID
        is_eleid_loose  = electronID(idx, STOP_loose_v1);
        is_eleid_medium	= electronID(idx, STOP_medium_v1);
        is_eleid_tight  = electronID(idx, STOP_tight_v1);
        
        //Phys14 IDs
        is_phys14_loose_noIso = isLooseElectronPOGphys14noIso_v2(idx);
        is_phys14_medium_noIso = isMediumElectronPOGphys14noIso_v2(idx);
        is_phys14_tight_noIso = isTightElectronPOGphys14noIso_v2(idx);


        eoverpin        = els_eOverPIn().at(idx); 

        //id variables
        sigmaIEtaEta_fill5x5 = els_sigmaIEtaIEta_full5x5().at(idx);
        dEtaIn = els_dEtaIn().at(idx);
        dPhiIn = els_dPhiIn().at(idx);
        hOverE = els_hOverE().at(idx);
        ooEmooP = (1.0/els_ecalEnergy().at(idx)) - (els_eOverPIn().at(idx)/els_ecalEnergy() .at(idx));
        expectedMissingInnerHits = els_exp_innerlayers().at(idx);
        conversionVeto = els_conv_vtx_flag().at(idx);
        etaSC = els_etaSC().at(idx);
        ChiSqr = els_chi2().at(idx);

        //iso variables
        chiso     = els_pfChargedHadronIso().at(idx);
        nhiso     = els_pfNeutralHadronIso().at(idx);
        emiso     = els_pfPhotonIso().at(idx);
        deltaBeta = els_pfPUIso().at(idx);               
 
	//ISO
	relIso03DB = eleRelIso03(idx, STOP);
        relIso03EA = eleRelIso03EA(idx);

       //elMiniRelIso(unsigned int idx, bool useVetoCones, float ptthresh, bool useDBcor)
       miniRelIsoDB = elMiniRelIso(idx, true, 0., true, false);
       miniRelIsoEA = elMiniRelIso(idx, true, 0., false, true);

    } // end electron block

//and now muons....
    if (abs(id) == 13)
    {
        is_mu = true;
        
        int trkidx = mus_trkidx().at(idx);
        if (trkidx >= 0 && vtxidx >= 0) {
	    d0 = mus_d0().at(idx);
            dz = mus_dzPV().at(idx);
            d0err = mus_d0Err().at(idx);
            dzerr = mus_z0Err().at(idx);
        }
        ip3d    = mus_ip3d().at(idx);;
        ip3derr = mus_ip3derr().at(idx);;

        is_pfmu    = ((mus_type().at(idx) & (1<<5)) != 0);

        if (vtxidx >= 0) {
   	    is_muoid_loose  = muonID(idx, STOP_loose_v1); 
            is_muoid_medium = muonID(idx, STOP_medium_v1);
            is_muoid_tight  = muonID(idx, STOP_tight_v1);
        }

        //iso variables
        chiso     = mus_isoR04_pf_ChargedHadronPt().at(idx);
        nhiso     = mus_isoR04_pf_NeutralHadronEt().at(idx);
        emiso     = mus_isoR04_pf_PhotonEt().at(idx);
        deltaBeta = mus_isoR04_pf_PUPt().at(idx);

   	//ISO
    	relIso03DB = muRelIso03(idx, STOP);
    	relIso03EA = muRelIso03EA(idx);
    	relIso04DB = muRelIso04DB(idx);

         //muMiniRelIso(unsigned int idx, bool useVetoCones=true, float ptthresh = 0.5, bool useDBcor=false);
           miniRelIsoDB = muMiniRelIso(idx, true, 0.5, true, false);
           miniRelIsoEA = muMiniRelIso(idx, true, 0.5, false, true); 
    } // end muon block
}

void LeptonTree::Reset()
{
    is_mu           = false;
    is_el           = false;
    is_fromw        = -9999;
    charge          = -9999;
    pdgid           = -9999;
    type            = -9999;
    production_type.clear();
    d0              = -9999.;
    d0err           = -9999.;
    dz              = -9999.;
    dzerr           = -9999.;

    sigmaIEtaEta_fill5x5            = -9999.; 
    dEtaIn            = -9999.;
    dPhiIn            = -9999.;
    hOverE            = -9999.;
    ooEmooP           = -9999.;
    expectedMissingInnerHits        = -9999.;
    conversionVeto    = -9999.;
    etaSC             = -9999.;
    ChiSqr            = -9999.;

    chiso           = -9999.;     	   
    nhiso           = -9999.;
    emiso           = -9999.;
    deltaBeta       = -9999.;

    pfiso04         = -9999.;
    pfiso03         = -9999.;
    relIso03DB      = -9999.;
    relIso03EA      = -9999.;    
    relIso04DB      = -9999.;
    miniRelIsoDB = -9999.;
    miniRelIsoEA  = -9999.;

    mcid            = -9999;
    mcstatus        = -9999;

    is_eleid_loose  = false;
    is_eleid_medium = false;
    is_eleid_tight  = false;
    eoverpin        = -9999.;

    is_phys14_loose_noIso = false;
    is_phys14_medium_noIso = false;
    is_phys14_tight_noIso = false;

    is_muoid_loose  = false;
    is_muoid_medium = false;
    is_muoid_tight  = false;
    ip3d            = -9999.;
    ip3derr         = -9999.;
    is_pfmu         = false;
   // mus_pfcands_idx = -99999;    

    p4           = LorentzVector(0, 0, 0, 0);
    mcp4         = LorentzVector(0, 0, 0, 0);
    pfp4         = LorentzVector(0, 0, 0, 0);

    pt		= -9999.;
    eta		= -9999.;

   
}

void LeptonTree::SetBranches(TTree* tree)
{
    tree->Branch(Form("%sis_mu"           , prefix_.c_str()) , &is_mu           ); 
    tree->Branch(Form("%sis_el"           , prefix_.c_str()) , &is_el           ); 
    tree->Branch(Form("%sis_fromw"        , prefix_.c_str()) , &is_fromw        ); 
    tree->Branch(Form("%scharge"          , prefix_.c_str()) , &charge          ); 
    tree->Branch(Form("%spdgid"           , prefix_.c_str()) , &pdgid           ); 
    tree->Branch(Form("%stype"            , prefix_.c_str()) , &type            ); 
    tree->Branch(Form("%sproduction_type" , prefix_.c_str()) , &production_type );
    tree->Branch(Form("%sd0"              , prefix_.c_str()) , &d0              ); 
    tree->Branch(Form("%sd0err"           , prefix_.c_str()) , &d0err           ); 
    tree->Branch(Form("%sdz"              , prefix_.c_str()) , &dz              ); 
    tree->Branch(Form("%sdzerr"           , prefix_.c_str()) , &dzerr           ); 

    tree->Branch(Form("%ssigmaIEtaEta_fill5x5"        , prefix_.c_str()) , &sigmaIEtaEta_fill5x5);
    tree->Branch(Form("%sdEtaIn"        , prefix_.c_str()) , &dEtaIn);
    tree->Branch(Form("%sdPhiIn"        , prefix_.c_str()) , &dPhiIn);
    tree->Branch(Form("%shOverE"        , prefix_.c_str()) , &hOverE);
    tree->Branch(Form("%sooEmooP"       , prefix_.c_str()) , &ooEmooP);
    tree->Branch(Form("%sexpectedMissingInnerHits"    , prefix_.c_str()) , &expectedMissingInnerHits);
    tree->Branch(Form("%sconversionVeto", prefix_.c_str()) , &conversionVeto);
    tree->Branch(Form("%setaSC"         , prefix_.c_str()) , &etaSC);
    tree->Branch(Form("%sChiSqr"        , prefix_.c_str()) , &ChiSqr);

    tree->Branch(Form("%schiso"       , prefix_.c_str()) , &chiso);
    tree->Branch(Form("%snhiso"       , prefix_.c_str()) , &nhiso);
    tree->Branch(Form("%semiso"       , prefix_.c_str()) , &emiso);
    tree->Branch(Form("%sdeltaBeta"   , prefix_.c_str()) , &deltaBeta);

     tree->Branch(Form("%spfiso04"	 , prefix_.c_str()) , &pfiso04         );
     tree->Branch(Form("%spfiso03"        , prefix_.c_str()) , &pfiso03         );
     tree->Branch(Form("%srelIso03DB"       , prefix_.c_str()) , &relIso03DB       );
     tree->Branch(Form("%srelIso03EA"       , prefix_.c_str()) , &relIso03EA       );
     tree->Branch(Form("%srelIso04DB"       , prefix_.c_str()) , &relIso04DB       );

     tree->Branch(Form("%sminiRelIsoDB"       , prefix_.c_str()) , &miniRelIsoDB);
     tree->Branch(Form("%sminiRelIsoEA"       , prefix_.c_str()) , &miniRelIsoEA);

    tree->Branch(Form("%smcid"            , prefix_.c_str()) , &mcid            ); 
    tree->Branch(Form("%smcstatus"        , prefix_.c_str()) , &mcstatus        ); 
    
    tree->Branch(Form("%sis_eleid_loose" , prefix_.c_str()) , &is_eleid_loose);
    tree->Branch(Form("%sis_eleid_medium" , prefix_.c_str()) , &is_eleid_medium ); 
    tree->Branch(Form("%sis_eleid_tight"  , prefix_.c_str()) , &is_eleid_tight  ); 
    tree->Branch(Form("%sis_phys14_loose_noIso", prefix_.c_str()) , &is_phys14_loose_noIso);
    tree->Branch(Form("%sis_phys14_medium_noIso", prefix_.c_str()) , &is_phys14_medium_noIso);
    tree->Branch(Form("%sis_phys14_tight_noIso", prefix_.c_str()) , &is_phys14_tight_noIso);

    tree->Branch(Form("%seoverpin"        , prefix_.c_str()) , &eoverpin        ); 

    tree->Branch(Form("%sis_muoid_loose"  , prefix_.c_str()) , &is_muoid_loose  ); 
    tree->Branch(Form("%sis_muoid_tight"  , prefix_.c_str()) , &is_muoid_tight  ); 
    tree->Branch(Form("%sip3d"  		 , prefix_.c_str()) , &ip3d);
    tree->Branch(Form("%sip3derr"	 , prefix_.c_str()) , &ip3derr);
    tree->Branch(Form("%sis_pfmu"	 , prefix_.c_str()) , &is_pfmu);

    tree->Branch(Form("%sp4"      , prefix_.c_str()) , "LorentzVector" , &p4      );
    tree->Branch(Form("%smcp4"    , prefix_.c_str()) , "LorentzVector" , &mcp4    );
    tree->Branch(Form("%spfp4"    , prefix_.c_str()) , "LorentzVector" , &pfp4   );

   tree->Branch(Form("%spt"	 , prefix_.c_str()) , &pt);
   tree->Branch(Form("%seta"      , prefix_.c_str()) , &eta);

   
}
