#include "JetTree.h"
#include "CMS3.h"
#include "JetSelections.h"
#include "StopSelections.h"

using namespace tas;
 
JetTree::JetTree () :
    m_ak4_pt_cut(30.),
    m_ak8_pt_cut(100.)
{
}

void JetTree::FillCommon(unsigned int overlep1_idx = -9999, unsigned int overlep2_idx = -9999)
{
    // fill info for ak4pfjets
    int nGoodJets=0.;
    unsigned int jindex=0;
    float HT = 0.;
    float JET_PT = 0.;
    int nbtags_med = 0;
    static const float BTAG_MED = 0.814;
    float dPhiM = 0.;

    float htssm = 0.;
    float htosm = 0.;
    float htratiom = 0.;

    vector<pair <int, LorentzVector> > sortedJets_pt =  sort_pt(pfjets_p4(), JET_PT);
    for (size_t idx = 0; idx < pfjets_p4().size(); ++idx)
    {
        jindex = sortedJets_pt.at(idx).first;
        //deal with the overlaps
        if(jindex == overlep1_idx){
		ak4pfjet_overlep1_p4 = pfjets_p4().at(jindex);
                ak4pfjet_overlep1_btag_disc = pfjets_combinedInclusiveSecondaryVertexV2BJetTag().at(jindex);
            //    ak4pfjet_overlep1_pu_id = pfjets_pileupJetId().at(jindex);
                ak4pfjet_overlep1_chf = pfjets_chargedHadronE().at(jindex);
                ak4pfjet_overlep1_nhf = pfjets_neutralHadronE().at(jindex);
                ak4pfjet_overlep1_cef = pfjets_chargedEmE().at(jindex);
                ak4pfjet_overlep1_nef = pfjets_neutralEmE().at(jindex);
                ak4pfjet_overlep1_cm  = pfjets_chargedMultiplicity().at(jindex);
                ak4pfjet_overlep1_nm  = cms3.pfjets_neutralMultiplicity().at(jindex);
	}
        if(jindex == overlep2_idx){
                ak4pfjet_overlep2_p4 = pfjets_p4().at(jindex);
                ak4pfjet_overlep2_btag_disc = pfjets_combinedInclusiveSecondaryVertexV2BJetTag().at(jindex);
                //ak4pfjet_overlep2_pu_id = pfjets_pileupJetId().at(jindex);
                ak4pfjet_overlep2_chf = pfjets_chargedHadronE().at(jindex);
                ak4pfjet_overlep2_nhf = pfjets_neutralHadronE().at(jindex);
                ak4pfjet_overlep2_cef = pfjets_chargedEmE().at(jindex);
                ak4pfjet_overlep2_nef = pfjets_neutralEmE().at(jindex);
                ak4pfjet_overlep2_cm  = pfjets_chargedMultiplicity().at(jindex);
                ak4pfjet_overlep2_nm  = cms3.pfjets_neutralMultiplicity().at(jindex);
        }

        //remove overlaps & apply preselections
        if(jindex == overlep1_idx || jindex == overlep2_idx) continue; //remove ovelaps from your jet collection
        if(!PassJetPreSelections(jindex,30., 2.4)) continue;
        if (pfjets_p4().at(jindex).pt() < m_ak4_pt_cut) continue;
 
        ak4pfjets_p4.push_back(pfjets_p4().at(jindex));
        ak4pfjets_btag_disc.push_back(pfjets_combinedInclusiveSecondaryVertexV2BJetTag().at(jindex));
      //  ak4pfjets_pu_id.push_back(pfjets_pileupJetId().at(jindex));
        ak4pfjets_parton_flavor.push_back(pfjets_partonFlavour().at(jindex));
        ak4pfjets_loose_puid.push_back(loosePileupJetId(jindex));
        ak4pfjets_loose_pfid.push_back(isLoosePFJet(jindex));
        ak4pfjets_medium_pfid.push_back(isMediumPFJet(jindex));
        ak4pfjets_tight_pfid.push_back(isTightPFJet(jindex));

        ak4pfjets_chf.push_back(pfjets_chargedHadronE().at(jindex));
        ak4pfjets_nhf.push_back(pfjets_neutralHadronE().at(jindex));
        ak4pfjets_cef.push_back(pfjets_chargedEmE().at(jindex));
        ak4pfjets_nef.push_back(pfjets_neutralEmE().at(jindex));
        ak4pfjets_cm.push_back(pfjets_chargedMultiplicity().at(jindex));
        ak4pfjets_nm.push_back(cms3.pfjets_neutralMultiplicity().at(jindex));

	//HTRatio
	dPhiM = getdphi(evt_pfmetPhi(), pfjets_p4().at(jindex).phi() );
	if ( dPhiM  < (TMath::Pi()/2) ) htssm = htssm + pfjets_p4().at(jindex).pt();
        else htosm = htosm + pfjets_p4().at(jindex).pt();	

        HT = HT + pfjets_p4().at(jindex).pt();
        nGoodJets++;
	
	//medium btag
        if(pfjets_combinedInclusiveSecondaryVertexV2BJetTag().at(jindex) > BTAG_MED){
             ak4pfjets_passMEDbtag.push_back(true);
             nbtags_med++;
             if(nbtags_med == 1){
                ak4pfjets_leadMEDbjet_pt = pfjets_p4().at(jindex).pt();  //plot leading bjet pT
                ak4pfjets_leadMEDbjet_p4 = pfjets_p4().at(jindex);
             }
             ak4pfjets_MEDbjet_pt.push_back(pfjets_p4().at(jindex).pt());
        }else{ 
             ak4pfjets_passMEDbtag.push_back(false);
             if(pfjets_p4().at(jindex).pt() > 40. && jindex>0 && pfjets_combinedInclusiveSecondaryVertexV2BJetTag().at(jindex) > pfjets_combinedInclusiveSecondaryVertexV2BJetTag().at(jindex-1)){
               ak4pfjets_leadbtag_p4 = pfjets_p4().at(jindex);
             }
        }
   }

   ak4GoodPFJets = nGoodJets;
   nGoodJets=0;
   ak4_HT = HT;
   HT=0;
   ak4_nBTags_Med = nbtags_med;

   ak4_htssm = htssm;
   ak4_htosm = htosm;
   htratiom   = htssm / (htosm + htssm);
   ak4_htratiom = htratiom; 
 
    // fill info for ak8pfjets
    for (size_t idx = 0; idx < ak8jets_p4().size(); ++idx)
    {
        if(!PassJetPreSelections(idx,30,2.4)) continue;
        if (ak8jets_p4().at(idx).pt() < m_ak8_pt_cut) continue;
 
        ak8pfjets_p4.push_back(ak8jets_p4().at(idx));
        ak8pfjets_tau1.push_back(ak8jets_nJettinessTau1().at(idx));
        ak8pfjets_tau2.push_back(ak8jets_nJettinessTau2().at(idx));
        ak8pfjets_tau3.push_back(ak8jets_nJettinessTau3().at(idx));
        //ak8pfjets_top_mass.push_back(ak8jets_topJetMass().at(idx));
        ak8pfjets_pruned_mass.push_back(ak8jets_prunedMass().at(idx));
        ak8pfjets_trimmed_mass.push_back(ak8jets_trimmedMass().at(idx));
        ak8pfjets_filtered_mass.push_back(ak8jets_filteredMass().at(idx));
      //  ak8pfjets_pu_id.push_back(ak8jets_pileupJetId().at(idx));    
        ak8pfjets_parton_flavor.push_back(ak8jets_partonFlavour().at(idx));

        nGoodJets++;

    }
    ak8GoodPFJets = nGoodJets;
    nGoodJets=0;

    // fill info for genjets
    for (size_t idx = 0; idx < genjets_p4NoMuNoNu().size(); ++idx)
    {
        if (genjets_p4NoMuNoNu().at(idx).pt() < m_ak4_pt_cut) continue;
 
        ak4genjets_p4.push_back(genjets_p4NoMuNoNu().at(idx));
        if(genjets_p4NoMuNoNu().at(idx).pt() > 20.)  nGoodJets++;
    }
    nGoodGenJets = nGoodJets;
    
}
        
void JetTree::SetJetPtSelection (std::string cone_size, float pt_cut)
{
    if (cone_size == "ak4") m_ak4_pt_cut = pt_cut;
    else if (cone_size == "ak8") m_ak4_pt_cut = pt_cut;
    else {std::cout << "Invalid cone size." << std::endl;}
    return;
}
 
void JetTree::GetJetPtSelections (std::string cone_size)
{
    if (cone_size == "ak4") std::cout << "ak4 jet pt > " << m_ak4_pt_cut << std::endl;
    else if (cone_size == "ak8") std::cout << "ak8 jet pt > " << m_ak8_pt_cut << std::endl;
    else
    {
        std::cout << "ak4 jet pt > " << m_ak4_pt_cut << std::endl;        
        std::cout << "ak8 jet pt > " << m_ak8_pt_cut << std::endl;
    }
}
 
void JetTree::Reset ()
{
    ak4pfjets_p4.clear();
    ak4pfjets_qg_disc.clear();    
    ak4pfjets_btag_disc.clear();
    ak4pfjets_pu_id.clear();
    ak4pfjets_parton_flavor.clear();
    ak4pfjets_loose_puid.clear();
    ak4pfjets_loose_pfid.clear();
    ak4pfjets_medium_pfid.clear();
    ak4pfjets_tight_pfid.clear();

    ak4pfjets_chf.clear();
    ak4pfjets_nhf.clear();
    ak4pfjets_cef.clear();
    ak4pfjets_nef.clear();
    ak4pfjets_cm.clear();
    ak4pfjets_nm.clear();
    
    ak4_htssm = -9999.;
    ak4_htosm = -9999.;
    ak4_htratiom = -9999.; 

   //overlaps
    ak4pfjet_overlep1_p4 = LorentzVector(0,0, 0,0);
    ak4pfjet_overlep1_btag_disc = -9999;
    ak4pfjet_overlep1_pu_id = -9999;
    ak4pfjet_overlep1_chf = -9999;
    ak4pfjet_overlep1_nhf = -9999;
    ak4pfjet_overlep1_cef = -9999;
    ak4pfjet_overlep1_nef = -9999;
    ak4pfjet_overlep1_cm = -9999;
    ak4pfjet_overlep1_nm = -9999;

    ak4pfjet_overlep2_p4 = LorentzVector(0,0, 0,0);
    ak4pfjet_overlep2_btag_disc = -9999;
    ak4pfjet_overlep2_pu_id = -9999;
    ak4pfjet_overlep2_chf = -9999;
    ak4pfjet_overlep2_nhf = -9999;
    ak4pfjet_overlep2_cef = -9999;
    ak4pfjet_overlep2_nef = -9999;
    ak4pfjet_overlep2_cm = -9999;
    ak4pfjet_overlep2_nm = -9999;
  
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
  
    ak4GoodPFJets = -9999;  
    ak4_HT 	  = -9999.; 
    ak8GoodPFJets = -9999;
    nGoodGenJets = -9999;
    ak4_nBTags_Med = -9999;
}
 
void JetTree::SetBranches (TTree* tree)
{
    tree->Branch("nGoodGenJets", &nGoodGenJets);
    tree->Branch("ak4GoodPFJets", &ak4GoodPFJets);
    tree->Branch("ak8GoodPFJets", &ak8GoodPFJets);
    tree->Branch("ak4_nBTags_Med", &ak4_nBTags_Med);
    tree->Branch("ak4_HT", &ak4_HT);
    tree->Branch("ak4_htssm", &ak4_htssm);
    tree->Branch("ak4_htosm", &ak4_htosm);
    tree->Branch("ak4_htratiom", &ak4_htratiom);
    tree->Branch("ak4pfjets_p4", &ak4pfjets_p4);
    tree->Branch("ak4pfjets_qg_disc", &ak4pfjets_qg_disc);
    tree->Branch("ak4pfjets_btag_disc", &ak4pfjets_btag_disc);
    tree->Branch("ak4pfjets_pu_id", &ak4pfjets_pu_id);
    tree->Branch("ak4pfjets_parton_flavor", &ak4pfjets_parton_flavor);
    tree->Branch("ak4pfjets_loose_puid", &ak4pfjets_loose_puid);
    tree->Branch("ak4pfjets_loose_pfid", &ak4pfjets_loose_pfid);
    tree->Branch("ak4pfjets_medium_pfid", &ak4pfjets_medium_pfid);
    tree->Branch("ak4pfjets_tight_pfid", &ak4pfjets_tight_pfid);

    tree->Branch("ak4pfjets_MEDbjet_pt",&ak4pfjets_MEDbjet_pt);
    tree->Branch("ak4pfjets_leadMEDbjet_pt",&ak4pfjets_leadMEDbjet_pt); 
    tree->Branch("ak4pfjets_leadMEDbjet_p4", &ak4pfjets_leadMEDbjet_p4);
    tree->Branch("ak4pfjets_leadbtag_p4", &ak4pfjets_leadbtag_p4);

    tree->Branch("ak4pfjets_chf", &ak4pfjets_chf);
    tree->Branch("ak4pfjets_nhf", &ak4pfjets_nhf);
    tree->Branch("ak4pfjets_cef", &ak4pfjets_cef);
    tree->Branch("ak4pfjets_nef", &ak4pfjets_nef);
    tree->Branch("ak4pfjets_cm", &ak4pfjets_cm);
    tree->Branch("ak4pfjets_nm", &ak4pfjets_nm);

    tree->Branch("ak4pfjet_overlep1_p4", &ak4pfjet_overlep1_p4);
    tree->Branch("ak4pfjet_overlep1_btag_disc", &ak4pfjet_overlep1_p4);
    tree->Branch("ak4pfjet_overlep1_pu_id",&ak4pfjet_overlep1_pu_id);
    tree->Branch("ak4pfjet_overlep1_chf", &ak4pfjet_overlep1_chf);
    tree->Branch("ak4pfjet_overlep1_nhf", &ak4pfjet_overlep1_nhf);
    tree->Branch("ak4pfjet_overlep1_cef", &ak4pfjet_overlep1_cef);
    tree->Branch("ak4pfjet_overlep1_nef", &ak4pfjet_overlep1_nef);
    tree->Branch("ak4pfjet_overlep1_cm", &ak4pfjet_overlep1_cm);
    tree->Branch("ak4pfjet_overlep1_nm", &ak4pfjet_overlep1_nm);

    tree->Branch("ak4pfjet_overlep2_p4", &ak4pfjet_overlep2_p4);
    tree->Branch("ak4pfjet_overlep2_btag_disc", &ak4pfjet_overlep2_p4);
    tree->Branch("ak4pfjet_overlep2_pu_id",&ak4pfjet_overlep2_pu_id);
    tree->Branch("ak4pfjet_overlep2_chf", &ak4pfjet_overlep2_chf);
    tree->Branch("ak4pfjet_overlep2_nhf", &ak4pfjet_overlep2_nhf);
    tree->Branch("ak4pfjet_overlep2_cef", &ak4pfjet_overlep2_cef);
    tree->Branch("ak4pfjet_overlep2_nef", &ak4pfjet_overlep2_nef);
    tree->Branch("ak4pfjet_overlep2_cm", &ak4pfjet_overlep2_cm);
    tree->Branch("ak4pfjet_overlep2_nm", &ak4pfjet_overlep2_nm);

    tree->Branch("ak8pfjets_p4", &ak8pfjets_p4);
    tree->Branch("ak8pfjets_tau1", &ak8pfjets_tau1);
    tree->Branch("ak8pfjets_tau2", &ak8pfjets_tau2);
    tree->Branch("ak8pfjets_tau3", &ak8pfjets_tau3);
    tree->Branch("ak8pfjets_top_mass", &ak8pfjets_top_mass);
    tree->Branch("ak8pfjets_pruned_mass", &ak8pfjets_pruned_mass);
    tree->Branch("ak8pfjets_trimmed_mass", &ak8pfjets_trimmed_mass);
    tree->Branch("ak8pfjets_filtered_mass", &ak8pfjets_filtered_mass);
    tree->Branch("ak8pfjets_pu_id", &ak8pfjets_pu_id);    
    tree->Branch("ak8pfjets_parton_flavor", &ak8pfjets_parton_flavor);
 
    tree->Branch("ak4genjets_p4", &ak4genjets_p4);    
    tree->Branch("ak4pfjets_passMEDbtag", &ak4pfjets_passMEDbtag);
}
