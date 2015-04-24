#include "EventTree.h"
#include "TString.h"
#include "CMS3.h"
#include "VertexSelections.h"
#include "StopSelections.h"

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
    ls = evt_lumiBlock();
    evt = evt_event();
    nvtxs = numberOfGoodVertices();
 
    pfmet = evt_pfmet();
    pfmet_phi = evt_pfmetPhi();
     
    is_data = evt_isRealData();

    if (!is_data)
    {
        scale1fb = evt_scale1fb();
        xsec = evt_xsec_incl();
        kfactor = evt_kfactor();
        pu_nvtxs    = puInfo_nPUvertices().at(6);
        pu_ntrue = puInfo_trueNumInteractions().at(0);

        if(signal){
          sparms_values = sparm_values();
          for ( auto name : sparm_names() )
            sparms_names.push_back(name.Data());

          sparms_filterEfficiency = sparm_filterEfficiency();
          sparms_pdfScale = sparm_pdfScale();
          sparms_pdfWeight1 = sparm_pdfWeight1();
          sparms_pdfWeight2 = sparm_pdfWeight2();
          sparms_weight = sparm_weight();
          sparms_xsec = sparm_xsec();
          sparms_subProcessId = sparm_subProcessId();
        }
        genmet = gen_met();
        genmet_phi = gen_metPhi();

    }
    dataset = evt_dataset().at(0).Data();
    filename = root_file_name;
    cms3tag = evt_CMS3tag().at(0).Data();
    
}
 
void EventTree::Reset ()
{
    run = 0;
    ls = 0;
    evt = 0;

    ngoodlep	=  -9999;
     
    nvtxs 	=  -9999;
    pu_nvtxs 	=  -9999;
 
    pfmet 	=  -9999.;
    pfmet_phi 	=  -9999.;
    scale1fb 	=  -9999.;
    xsec 	=  -9999.;
    kfactor 	=  -9999.;
    pu_ntrue 	=  -9999.;
    dR_lep1_leadb = -9999.;
    dR_lep2_leadb = -9999.;
    MT2W_lep1 	=  -9999.;
    MT2W_lep2 	=  -9999.;
    mindphi_met_j1_j2 = -9999.;
    MT_MET_lep1 = -9999.;
    MT_MET_lep2 = -9999.;
    chi2 	= -9999.; 
    is_data = false;
 
    dataset = "";
    filename = "";
    cms3tag = "";

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

    genmet 	= -9999.;
    genmet_phi 	= -9999.;
    PassTrackVeto = false;
    PassTauVeto = false;
 
}
 
void EventTree::SetBranches (TTree* tree)
{
    tree->Branch("run", &run);
    tree->Branch("ls", &ls);
    tree->Branch("evt", &evt);   
    tree->Branch("nvtxs", &nvtxs);
    tree->Branch("pu_nvtxs", &pu_nvtxs);
    tree->Branch("pfmet", &pfmet);
    tree->Branch("pfmet_phi", &pfmet_phi);
    tree->Branch("scale1fb", &scale1fb);
    tree->Branch("xsec", &xsec);
    tree->Branch("kfactor", &kfactor);
    tree->Branch("pu_ntrue", &pu_ntrue);    
    tree->Branch("ngoodlep",&ngoodlep);
    tree->Branch("is_data", &is_data);
    tree->Branch("dataset", &dataset);
    tree->Branch("filename", &filename);
    tree->Branch("cms3tag", &cms3tag);
    tree->Branch("nEvents", &nEvents);
    tree->Branch("nEvents_goodvtx", &nEvents_goodvtx);
    tree->Branch("nEvents_MET30", &nEvents_MET30);
    tree->Branch("nEvents_1goodlep", &nEvents_1goodlep);
    tree->Branch("nEvents_2goodjets", &nEvents_2goodjets);
    tree->Branch("MT2W_lep1",&MT2W_lep1);
    tree->Branch("MT2W_lep2",&MT2W_lep2);
    tree->Branch("mindphi_met_j1_j2", &mindphi_met_j1_j2);
    tree->Branch("MT_MET_lep1", &MT_MET_lep1);
    tree->Branch("MT_MET_lep2", &MT_MET_lep2);
    tree->Branch("dR_lep1_leadb", &dR_lep1_leadb);
    tree->Branch("dR_lep2_leadb", &dR_lep2_leadb);
    tree->Branch("chi2", &chi2);
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
    tree->Branch("genmet", &genmet);
    tree->Branch("genmet_phi", &genmet_phi);
    tree->Branch("PassTrackVeto",&PassTrackVeto);
    tree->Branch("PassTauVeto",&PassTauVeto);
}
