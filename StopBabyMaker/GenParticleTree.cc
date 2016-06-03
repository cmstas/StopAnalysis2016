#include "GenParticleTree.h"
#include "Math/GenVector/PtEtaPhiE4D.h"
#include "CMS3.h"
#include "StopSelections.h"
#include "MCSelections.h"

GenParticleTree::GenParticleTree ()
{
}

GenParticleTree::GenParticleTree (const std::string &prefix)
  : prefix_(prefix)
{
}

using namespace tas;

void GenParticleTree::FillCommon (int idx)
{
	if (idx < 0) return;

        if (evt_isRealData()) return;

        if(abs(genps_id_mother().at(genps_idx_mother().at(idx))) == pdg_t) isfromt.push_back(true);
        else if(abs(genps_id_mother().at(idx)) == pdg_t) isfromt.push_back(true);
        else isfromt.push_back(false);
        
	
	p4.push_back(genps_p4().at(idx));
	id.push_back(genps_id().at(idx));
	genpsidx.push_back(idx);
	status.push_back(genps_status().at(idx));
	fromHardProcessDecayed.push_back(genps_fromHardProcessDecayed().at(idx));
	fromHardProcessFinalState.push_back(genps_fromHardProcessFinalState().at(idx));
	isHardProcess.push_back(genps_isHardProcess().at(idx));
	isLastCopy.push_back(genps_isLastCopy().at(idx));

        // mother information p4, charge, id, idx, status
        int motherindex = genps_idx_mother().at(idx);
        motherp4.push_back(genps_p4().at(motherindex));
	//mothercharge.push_back(genps_charge().at(motherindex));
        motherid.push_back(genps_id().at(motherindex));
        motheridx.push_back(motherindex);
        motherstatus.push_back(genps_status().at(motherindex));
	
	int gmindex = -1;
	if(motherindex>=0) {
	  gmindex = genps_idx_mother().at(motherindex);
	  gmotherp4.push_back(genps_p4().at(gmindex));
	  gmotherid.push_back(genps_id().at(gmindex));
	  gmotheridx.push_back(gmindex);
	  gmotherstatus.push_back(genps_status().at(gmindex));
	} else {
	  LorentzVector temp( -99.9, -99.9, -99.9, -99.9 );
	  gmotherp4.push_back(temp);
	  gmotherid.push_back(-9999.);//to keep the same length as other genparticle vectors
	  gmotheridx.push_back(gmindex);
	  gmotherstatus.push_back(-9999);
	}
	

	//if gen taus
	if(abs(genps_id().at(idx)) != pdg_tau){
	 gentaudecay.push_back(NoTau); 
	  return;
	}

        //flag for tau decay leptonic (e, mu), hadronic (1, 3 prongs)
        int nprongs = 0;
	bool leptonic = false;
        //find daughters
        for(unsigned int genx = 0; genx < genps_p4().size() ; genx++){
          if(abs(genps_id().at(genps_idx_mother().at(genx))) == pdg_W){
            if(genps_idx_mother().at(genps_idx_mother().at(genx)) != idx) continue;
	  }else if(genps_idx_mother().at(genx) != idx) continue;
	  if(genps_status().at(genx) != 1 && genps_status().at(genx) != 2) continue;
	  //rhos and pions show up as status 2
	  //cout<<"Daughter particle  "<<abs(genps_id().at(genx))<<"  status "<<genps_status().at(genx)<<endl;
	  if(abs(genps_id().at(genx)) ==pdg_nue || abs(genps_id().at(genx)) ==pdg_numu || abs(genps_id().at(genx)) ==pdg_nutau) continue; //skip neutrinos
          //for now no continues in case theres something funky going on
	  if(abs(genps_id().at(genx)) == pdg_el){
		 gentaudecay.push_back(Lep_e); // tau decaying to electron
	 	 leptonic = true;
	  }
          if(abs(genps_id().at(genx)) == pdg_mu){
		gentaudecay.push_back(Lep_mu); // tau decaying to muon
                 leptonic = true;
          }
          if( abs(genps_id().at(genx)) != pdg_W && abs(genps_id().at(genx)) !=pdg_el && abs(genps_id().at(genx)) !=pdg_mu && genps_charge().at(genx) !=0){
            if(abs(genps_id().at(genx)) == 20213){
              for(unsigned int genx2 = 0; genx2 < genps_p4().size() ; genx2++){
                if(genps_idx_mother().at(genx2) != (int)genx) continue;
                if(genps_charge().at(genx2) !=0) nprongs++;
              }
            }else nprongs++;
          }
 	}

	//if(nprongs>0 && leptonic==false){
	// cout<<"N Prongs = "<<nprongs<<endl;
	// dumpDocLines();
	//}
        
	if(nprongs == 1) gentaudecay.push_back(Had_1prong);
        if(nprongs == 3) gentaudecay.push_back(Had_3prong);
        if((nprongs != 1 && nprongs != 3) && leptonic==false) gentaudecay.push_back(other);

//obsolete branches//
        //charge.push_back(genps_charge().at(idx));                                                                                
        //iso.push_back(genps_iso().at(idx));
        //mass.push_back(genps_mass().at(idx));

        //fromHardProcessBeforeFSR.push_back(genps_fromHardProcessBeforeFSR().at(idx));

        //isDirectHardProcessTauDecayProductFinalState.push_back(genps_isDirectHardProcessTauDecayProductFinalState().at(idx));
        //isDirectPromptTauDecayProductFinalState.push_back(genps_isDirectPromptTauDecayProductFinalState().at(idx));

        //isLastCopyBeforeFSR.push_back(genps_isLastCopyBeforeFSR().at(idx));
        //isMostlyLikePythia6Status3.push_back(genps_isMostlyLikePythia6Status3().at(idx));
        //isPromptDecayed.push_back(genps_isPromptDecayed().at(idx));
        //isPromptFinalState.push_back(genps_isPromptFinalState().at(idx));
        //lepdaughter_id.push_back(genps_lepdaughter_id().at(idx));


        //mothercharge.push_back(genps_charge().at(motherindex));

          //gmothercharge.push_back(genps_charge().at(gmindex));

          //gmothercharge.push_back(-9999);

        //int smotherindex = genps_idx_simplemother().at(idx);
        //simplemotherp4.push_back(genps_p4().at(smotherindex));
        ////simplemothercharge.push_back(genps_charge().at(smotherindex));
        //simplemotherid.push_back(genps_id().at(smotherindex));
        //simplemotheridx.push_back(smotherindex);
        //simplemotherstatus.push_back(genps_status().at(smotherindex));
        
        //int sgmindex = -1;
        //if(smotherindex>=0) {
        //sgmindex = genps_idx_simplemother().at(smotherindex);
        //simplegmotherp4.push_back(genps_p4().at(sgmindex));
        ////simplegmothercharge.push_back(genps_charge().at(sgmindex));
        //simplegmotherid.push_back(genps_id().at(sgmindex));
        //simplegmotheridx.push_back(sgmindex);
        //simplegmotherstatus.push_back(genps_status().at(sgmindex));
        //} else {
        //LorentzVector temp( -99.9, -99.9, -99.9, -99.9 );
        //simplegmotherp4.push_back(temp);
        ////simplegmothercharge.push_back(-9999);
        //simplegmotherid.push_back(-9999.);//to keep the same length as other genparticle vectors
        //simplegmotheridx.push_back(sgmindex);
        //simplegmotherstatus.push_back(-9999);
        //}
//        
}

void GenParticleTree::Reset()
{
  isfromt.clear();
  p4.clear();
  id.clear();
  genpsidx.clear();
  status.clear();
  fromHardProcessDecayed.clear();
  fromHardProcessFinalState.clear();
  isHardProcess.clear();
  isLastCopy.clear();
  gentaudecay.clear();
  gen_nfromt = -9999;
  motherp4.clear();
  motherid.clear();
  motheridx.clear();
  motherstatus.clear();
  gmotherp4.clear();
  gmotherid.clear();
  gmotheridx.clear();
  gmotherstatus.clear();

//obsolete branches//
  //charge.clear();
  //iso.clear();
  //mass.clear();
  //fromHardProcessBeforeFSR.clear();
  //isDirectHardProcessTauDecayProductFinalState.clear();
  //isDirectPromptTauDecayProductFinalState.clear();
  //isLastCopyBeforeFSR.clear();
  //isMostlyLikePythia6Status3.clear();
  //isPromptDecayed.clear();
  //isPromptFinalState.clear();
  //lepdaughter_id.clear();
  //mothercharge.clear();
  //gmothercharge.clear();

  //simplemotherp4.clear();
  //simplemothercharge.clear();
  //simplemotherid.clear();
  //simplemotheridx.clear();
  //simplemotherstatus.clear();
  //simplegmotherp4.clear();
  //simplegmothercharge.clear();
  //simplegmotherid.clear();
  //simplegmotheridx.clear();
  //simplegmotherstatus.clear();

}

void GenParticleTree::SetBranches(TTree* tree)
{
  tree->Branch(Form("gen%sisfromt" , prefix_.c_str()) , &isfromt);
  tree->Branch(Form("gen%sp4"      , prefix_.c_str()) , "LorentzVector" , &p4      );
  tree->Branch(Form("gen%sid"  , prefix_.c_str()) ,           &id          );
  tree->Branch(Form("gen%s_genpsidx"  , prefix_.c_str()) ,           &genpsidx          );
  tree->Branch(Form("gen%sstatus"  , prefix_.c_str()) ,           &status          );
  tree->Branch(Form("gen%sfromHardProcessDecayed"  , prefix_.c_str()) ,           &fromHardProcessDecayed          );
  tree->Branch(Form("gen%sfromHardProcessFinalState"  , prefix_.c_str()) ,           &fromHardProcessFinalState          );
  tree->Branch(Form("gen%sisHardProcess"  , prefix_.c_str()) ,           &isHardProcess          );
  tree->Branch(Form("gen%sisLastCopy"  , prefix_.c_str()) ,           &isLastCopy          );
  tree->Branch(Form("gen%sgentaudecay"  , prefix_.c_str()) ,           &gentaudecay          );
  tree->Branch(Form("gen_nfromt%s"  , prefix_.c_str()) ,           &gen_nfromt);
  tree->Branch(Form("gen%smotherp4",  prefix_.c_str()) ,           &motherp4);
  tree->Branch(Form("gen%smotherid", prefix_.c_str()) ,           &motherid);
  tree->Branch(Form("gen%smotheridx", prefix_.c_str()) ,           &motheridx);
  tree->Branch(Form("gen%smotherstatus", prefix_.c_str()) ,           &motherstatus);
  tree->Branch(Form("gen%sgmotherp4",  prefix_.c_str()) ,           &gmotherp4);
  tree->Branch(Form("gen%sgmotherid", prefix_.c_str()) ,           &gmotherid);
  tree->Branch(Form("gen%sgmotheridx", prefix_.c_str()) ,           &gmotheridx);
  tree->Branch(Form("gen%sgmotherstatus", prefix_.c_str()) ,           &gmotherstatus);

//obsolete branches//
  //tree->Branch(Form("gen%scharge"  , prefix_.c_str()) ,            &charge          );
  //tree->Branch(Form("gen%siso"  , prefix_.c_str()) ,           &iso          );
  //tree->Branch(Form("gen%smass"  , prefix_.c_str()) ,           &mass          );
  //tree->Branch(Form("gen%sfromHardProcessBeforeFSR"  , prefix_.c_str()) ,           &fromHardProcessBeforeFSR          );
  //tree->Branch(Form("gen%sisDirectHardProcessTauDecayProductFinalState"  , prefix_.c_str()) ,           &isDirectHardProcessTauDecayProductFinalState          );
  //tree->Branch(Form("gen%sisDirectPromptTauDecayProductFinalState"  , prefix_.c_str()) ,           &isDirectPromptTauDecayProductFinalState          );
  //tree->Branch(Form("gen%sisLastCopyBeforeFSR"  , prefix_.c_str()) ,           &isLastCopyBeforeFSR          );
  //tree->Branch(Form("gen%sisMostlyLikePythia6Status3"  , prefix_.c_str()) ,           &isMostlyLikePythia6Status3          );
  //tree->Branch(Form("gen%sisPromptDecayed"  , prefix_.c_str()) ,           &isPromptDecayed          );
  //tree->Branch(Form("gen%sisPromptFinalState"  , prefix_.c_str()) ,           &isPromptFinalState          );
  //tree->Branch(Form("gen%slepdaughter_id"  , prefix_.c_str()) ,           &lepdaughter_id          );
  //tree->Branch(Form("gen%smothercharge", prefix_.c_str()) ,           &mothercharge);
  //tree->Branch(Form("gen%sgmothercharge", prefix_.c_str()) ,           &gmothercharge);

  //tree->Branch(Form("gen%ssimplemotherp4",  prefix_.c_str()) ,           &simplemotherp4);
  //tree->Branch(Form("gen%ssimplemothercharge", prefix_.c_str()) ,           &simplemothercharge);
  //tree->Branch(Form("gen%ssimplemotherid", prefix_.c_str()) ,           &simplemotherid);
  //tree->Branch(Form("gen%ssimplemotheridx", prefix_.c_str()) ,           &simplemotheridx);
  //tree->Branch(Form("gen%ssimplemotherstatus", prefix_.c_str()) ,           &simplemotherstatus);
  //tree->Branch(Form("gen%ssimplegmotherp4",  prefix_.c_str()) ,           &simplegmotherp4);
  ////tree->Branch(Form("gen%ssimplegmothercharge", prefix_.c_str()) ,           &simplegmothercharge);
  //tree->Branch(Form("gen%ssimplegmotherid", prefix_.c_str()) ,           &simplegmotherid);
  //tree->Branch(Form("gen%ssimplegmotheridx", prefix_.c_str()) ,           &simplegmotheridx);
  //tree->Branch(Form("gen%ssimplegmotherstatus", prefix_.c_str()) ,           &simplegmotherstatus);  

}
