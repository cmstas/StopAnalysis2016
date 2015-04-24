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
 //           mcstatus  = genps_status().at(idx); // PLACEHOLDER, NEEDS FIXING vector<int> &genps_status()??? double check

            mcidx       = abs(id)==11 ? els_mcidx().at(idx) : abs(id)==13 ? mus_mcidx().at(idx) : -9999;
            mc_motherid = abs(id)==11 ? els_mc_motherid().at(idx) : abs(id)==13 ? mus_mc_motherid().at(idx) : -9999;
   }
    
//electrons
    if (abs(id) == 11)
    {
        is_el  		= true;

	//d0 and dz
    	//int gsfidx  = els_gsftrkidx().at(idx);
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
        eoverpin        = els_eOverPIn().at(idx); 
        
	//ISO
	relIso03DB = eleRelIso03(idx, STOP);
        relIso03EA = eleRelIso03EA(idx);

        //pfcands
       // els_pfcands_idx = els_PFCand_idx().at(idx);
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
            is_muoid_tight  = muonID(idx, STOP_tight_v1);
        }
   	//ISO
    	relIso03DB = muRelIso03(idx, STOP);
    	relIso03EA = muRelIso03EA(idx);
    	relIso04DB = muRelIso04DB(idx);

        //pf cands
     //   mus_pfcands_idx = mus_pfidx().at(idx);
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

    pfiso04         = -9999.;
    pfiso03         = -9999.;
    relIso03DB      = -9999.;
    relIso03EA      = -9999.;    
    relIso04DB      = -9999.;

    mcid            = -9999;
    mcstatus        = -9999;

    is_eleid_loose  = false;
    is_eleid_medium = false;
    is_eleid_tight  = false;
    eoverpin        = -9999.;
   // els_pfcands_idx.clear();

    is_muoid_loose  = false;
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

     tree->Branch(Form("%spfiso04"	 , prefix_.c_str()) , &pfiso04         );
     tree->Branch(Form("%spfiso03"        , prefix_.c_str()) , &pfiso03         );
     tree->Branch(Form("%srelIso03DB"       , prefix_.c_str()) , &relIso03DB       );
     tree->Branch(Form("%srelIso03EA"       , prefix_.c_str()) , &relIso03EA       );
     tree->Branch(Form("%srelIso04DB"       , prefix_.c_str()) , &relIso04DB       );

    tree->Branch(Form("%smcid"            , prefix_.c_str()) , &mcid            ); 
    tree->Branch(Form("%smcstatus"        , prefix_.c_str()) , &mcstatus        ); 
    
    tree->Branch(Form("%sis_eleid_loose" , prefix_.c_str()) , &is_eleid_loose);
    tree->Branch(Form("%sis_eleid_medium" , prefix_.c_str()) , &is_eleid_medium ); 
    tree->Branch(Form("%sis_eleid_tight"  , prefix_.c_str()) , &is_eleid_tight  ); 
    tree->Branch(Form("%seoverpin"        , prefix_.c_str()) , &eoverpin        ); 
    //tree->Branch(Form("%sels_pfcands_idx", prefix_.c_str()), &els_pfcands_idx);

    tree->Branch(Form("%sis_muoid_loose"  , prefix_.c_str()) , &is_muoid_loose  ); 
    tree->Branch(Form("%sis_muoid_tight"  , prefix_.c_str()) , &is_muoid_tight  ); 
    tree->Branch(Form("%sip3d"  		 , prefix_.c_str()) , &ip3d);
    tree->Branch(Form("%sip3derr"	 , prefix_.c_str()) , &ip3derr);
    tree->Branch(Form("%sis_pfmu"	 , prefix_.c_str()) , &is_pfmu);
   // tree->Branch(Form("%smus_pfcands_idx", prefix_.c_str()), &mus_pfcands_idx);

    tree->Branch(Form("%sp4"      , prefix_.c_str()) , "LorentzVector" , &p4      );
    tree->Branch(Form("%smcp4"    , prefix_.c_str()) , "LorentzVector" , &mcp4    );
    tree->Branch(Form("%spfp4"    , prefix_.c_str()) , "LorentzVector" , &pfp4   );

   tree->Branch(Form("%spt"	 , prefix_.c_str()) , &pt);
   tree->Branch(Form("%seta"      , prefix_.c_str()) , &eta);

   
}
