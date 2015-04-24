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

        isfromt.push_back(abs(genps_id_mother().at(genps_idx_mother().at(idx))) == pdg_t);
       // if(abs(genps_id().at(idx)) == pdg_tau && abs(genps_id_mother().at(genps_idx_mother().at(idx))) !=pdg_t){
         // cout<<"Mother "<<abs(genps_id_mother().at(genps_idx_mother().at(idx)))<<endl;
         // dumpDocLines();
      //  }
//cout<<"Mother "<<abs(genps_id_mother().at(genps_idx_mother().at(idx)))<<endl;
	  p4.push_back(genps_p4().at(idx));
          charge.push_back(genps_charge().at(idx));
  	  iso.push_back(genps_iso().at(idx));
          mass.push_back(genps_mass().at(idx));
          id.push_back(genps_id().at(idx));
          genpsidx.push_back(idx);
 	 // id_mother.push_back(genps_id_mother().at(idx));          
 	  status.push_back(genps_status().at(idx));
          lepdaughter_id.push_back(genps_lepdaughter_id().at(idx));

        //mother information p4, charge, id, idx, status
        int motherindex = genps_idx_mother().at(idx);
        motherp4.push_back(genps_p4().at(motherindex));
        mothercharge.push_back(genps_charge().at(motherindex));
        motherid.push_back(genps_id().at(motherindex));
        motheridx.push_back(motherindex);
        motherstatus.push_back(genps_status().at(motherindex));


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
//          cout<<"Daughter particle  "<<abs(genps_id().at(genx))<<"  status "<<genps_status().at(genx)<<endl;
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
                if(genps_idx_mother().at(genx2) != genx) continue;
                if(genps_charge().at(genx2) !=0) nprongs++;
              }
            }else nprongs++;
          }
 	}

//       if(nprongs>0 && leptonic==false){
  //         cout<<"N Prongs = "<<nprongs<<endl;
    //       dumpDocLines();
      // }
        
	if(nprongs == 1) gentaudecay.push_back(Had_1prong);
        if(nprongs == 3) gentaudecay.push_back(Had_3prong);
        if((nprongs != 1 && nprongs != 3) && leptonic==false) gentaudecay.push_back(other);
        
}

void GenParticleTree::Reset()
{
        isfromt.clear();
	p4.clear();
	charge.clear();
	iso.clear();
        mass.clear();
	id.clear();
        genpsidx.clear();
	status.clear();
	lepdaughter_id.clear();
	gentaudecay.clear();
        gen_nfromt = -9999;

        motherp4.clear();
        mothercharge.clear();
        motherid.clear();
        motheridx.clear();
        motherstatus.clear();
}

void GenParticleTree::SetBranches(TTree* tree)
{
        tree->Branch(Form("gen%sisfromt" , prefix_.c_str()) , &isfromt);
	tree->Branch(Form("gen%sp4"      , prefix_.c_str()) , "LorentzVector" , &p4      );
	tree->Branch(Form("gen%scharge"  , prefix_.c_str()) , 	     &charge          );
        tree->Branch(Form("gen%siso"  , prefix_.c_str()) ,           &iso          );
        tree->Branch(Form("gen%smass"  , prefix_.c_str()) ,           &mass          );
        tree->Branch(Form("gen%sid"  , prefix_.c_str()) ,           &id          );
        tree->Branch(Form("gen%s_genpsidx"  , prefix_.c_str()) ,           &genpsidx          );
        tree->Branch(Form("gen%sstatus"  , prefix_.c_str()) ,           &status          );
        tree->Branch(Form("gen%slepdaughter_id"  , prefix_.c_str()) ,           &lepdaughter_id          );
        tree->Branch(Form("gen%sgentaudecay"  , prefix_.c_str()) ,           &gentaudecay          );
        tree->Branch(Form("gen_nfromt%s"  , prefix_.c_str()) ,           &gen_nfromt);
        tree->Branch(Form("gen%smotherp4",  prefix_.c_str()) ,           &motherp4);
        tree->Branch(Form("gen%smothercharge", prefix_.c_str()) ,           &mothercharge);
        tree->Branch(Form("gen%smotherid", prefix_.c_str()) ,           &motherid);
        tree->Branch(Form("gen%smotheridx", prefix_.c_str()) ,           &motheridx);
        tree->Branch(Form("gen%smotherstatus", prefix_.c_str()) ,           &motherstatus);
}
