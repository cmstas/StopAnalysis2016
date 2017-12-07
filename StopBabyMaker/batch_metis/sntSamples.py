from __future__ import print_function

import time

from metis.Sample import SNTSample
from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask
from metis.StatsParser import StatsParser
from metis.Utils import do_cmd


if __name__ == "__main__":

    snt_samples = {
        # "stopbaby" : "/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM",
        # "stopbaby" : "/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3/MINIAODSIM",
        # "stopbaby" : "/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUSummer16Fast_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        # "stopbaby" : "/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUSummer16Fast_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        # "stopbaby" : "/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUSummer16Fast_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",

        # SingleMuon samples
        "data_2017Bv1_singlemu" : "/SingleMuon/Run2017B-PromptReco-v1/MINIAOD",
        "data_2017Bv2_singlemu" : "/SingleMuon/Run2017B-PromptReco-v2/MINIAOD",
        "data_2017Cv1_singlemu" : "/SingleMuon/Run2017C-PromptReco-v1/MINIAOD",
        "data_2017Cv2_singlemu" : "/SingleMuon/Run2017C-PromptReco-v2/MINIAOD",
        "data_2017Cv3_singlemu" : "/SingleMuon/Run2017C-PromptReco-v3/MINIAOD",
        "data_2017Dv1_singlemu" : "/SingleMuon/Run2017D-PromptReco-v1/MINIAOD",
        "data_2017Ev1_singlemu" : "/SingleMuon/Run2017E-PromptReco-v1/MINIAOD",
        "data_2017Fv1_singlemu" : "/SingleMuon/Run2017F-PromptReco-v1/MINIAOD",

        # SingleElectron samples
        "data_2017Bv1_singleel" : "/SingleElectron/Run2017B-PromptReco-v1/MINIAOD",
        "data_2017Bv2_singleel" : "/SingleElectron/Run2017B-PromptReco-v2/MINIAOD",
        "data_2017Cv1_singleel" : "/SingleElectron/Run2017C-PromptReco-v1/MINIAOD",
        "data_2017Cv2_singleel" : "/SingleElectron/Run2017C-PromptReco-v2/MINIAOD",
        "data_2017Cv3_singleel" : "/SingleElectron/Run2017C-PromptReco-v3/MINIAOD",
        "data_2017Dv1_singleel" : "/SingleElectron/Run2017D-PromptReco-v1/MINIAOD",
        "data_2017Ev1_singleel" : "/SingleElectron/Run2017E-PromptReco-v1/MINIAOD",
        "data_2017Fv1_singleel" : "/SingleElectron/Run2017F-PromptReco-v1/MINIAOD",

        # MET samples
        "data_2017Bv1_met" : "/MET/Run2017B-PromptReco-v1/MINIAOD",
        "data_2017Bv2_met" : "/MET/Run2017B-PromptReco-v2/MINIAOD",
        "data_2017Cv1_met" : "/MET/Run2017C-PromptReco-v1/MINIAOD",
        "data_2017Cv2_met" : "/MET/Run2017C-PromptReco-v2/MINIAOD",
        "data_2017Cv3_met" : "/MET/Run2017C-PromptReco-v3/MINIAOD",
        "data_2017Dv1_met" : "/MET/Run2017D-PromptReco-v1/MINIAOD",
        "data_2017Ev1_met" : "/MET/Run2017E-PromptReco-v1/MINIAOD",
        "data_2017Fv1_met" : "/MET/Run2017F-PromptReco-v1/MINIAOD",

        # DoubleMuon samples
        "data_2017Bv1_doublemu" : "/DoubleMuon/Run2017B-PromptReco-v1/MINIAOD",
        "data_2017Bv2_doublemu" : "/DoubleMuon/Run2017B-PromptReco-v2/MINIAOD",
        "data_2017Cv1_doublemu" : "/DoubleMuon/Run2017C-PromptReco-v1/MINIAOD",
        "data_2017Cv2_doublemu" : "/DoubleMuon/Run2017C-PromptReco-v2/MINIAOD",
        "data_2017Cv3_doublemu" : "/DoubleMuon/Run2017C-PromptReco-v3/MINIAOD",
        "data_2017Dv1_doublemu" : "/DoubleMuon/Run2017D-PromptReco-v1/MINIAOD",
        "data_2017Ev1_doublemu" : "/DoubleMuon/Run2017E-PromptReco-v1/MINIAOD",
        "data_2017Fv1_doublemu" : "/DoubleMuon/Run2017F-PromptReco-v1/MINIAOD",
        
        # DoubleEG samples
        "data_2017Bv1_doubleeg" : "/DoubleEG/Run2017B-PromptReco-v1/MINIAOD",
        "data_2017Bv2_doubleeg" : "/DoubleEG/Run2017B-PromptReco-v2/MINIAOD",
        "data_2017Cv1_doubleeg" : "/DoubleEG/Run2017C-PromptReco-v1/MINIAOD",
        "data_2017Cv2_doubleeg" : "/DoubleEG/Run2017C-PromptReco-v2/MINIAOD",
        "data_2017Cv3_doubleeg" : "/DoubleEG/Run2017C-PromptReco-v3/MINIAOD",
        "data_2017Dv1_doubleeg" : "/DoubleEG/Run2017D-PromptReco-v1/MINIAOD",
        "data_2017Ev1_doubleeg" : "/DoubleEG/Run2017E-PromptReco-v1/MINIAOD",
        "data_2017Fv1_doubleeg" : "/DoubleEG/Run2017F-PromptReco-v1/MINIAOD",

        # MuonEG samples
        "data_2017Bv1_muoneg" : "/MuonEG/Run2017B-PromptReco-v1/MINIAOD",
        "data_2017Cv1_muoneg" : "/MuonEG/Run2017C-PromptReco-v1/MINIAOD",
        "data_2017Bv2_muoneg" : "/MuonEG/Run2017B-PromptReco-v2/MINIAOD",
        "data_2017Cv2_muoneg" : "/MuonEG/Run2017C-PromptReco-v2/MINIAOD",
        "data_2017Cv3_muoneg" : "/MuonEG/Run2017C-PromptReco-v3/MINIAOD",
        "data_2017Dv1_muoneg" : "/MuonEG/Run2017D-PromptReco-v1/MINIAOD",
        "data_2017Ev1_muoneg" : "/MuonEG/Run2017E-PromptReco-v1/MINIAOD",
        "data_2017Fv1_muoneg" : "/MuonEG/Run2017F-PromptReco-v1/MINIAOD",

    }

    # Make a directory sample, giving it the location and a dataset name for bookkeeping purposes
    # The globber must be customized (by default, it is *.root) in order to pick up the text files

    # Make a CondorTask (3 in total, one for each input)
    maker_tasks = []
    merge_tasks = []

    for babyname, dsname in snt_samples.items():
        cmsswver = "CMSSW_9_4_1"
        scramarch = "slc6_amd64_gcc630"
        tarfile = "input.tar.gz"
        tag = "v25_7"
        maker_task = CondorTask(
            sample = SNTSample(dataset=dsname),
            files_per_output = 50 if "data" in babyname else 1,
            tag = tag,
            outdir_name = "stopBaby_" + babyname,
            output_name = "stopbaby.root",
            executable = "condor_executable.sh",
            cmssw_version = cmsswver,
            scram_arch = scramarch,
            arguments = "1" if "SMS" in dsname else "0", # isFastsim
            tarfile = tarfile,
            condor_submit_params = {"sites": "UAF,T2_US_UCSD,UCSB"},
        )
        merge_task = CondorTask(
            sample = DirectorySample( 
                dataset="merge_"+babyname,
                location=maker_task.get_outputdir(),
            ),
            # open_dataset = True, flush = True,
            executable = "merge_executable.sh",
            tarfile = "merge_scripts.tar.gz",
            files_per_output = 100000,
            output_dir = maker_task.get_outputdir() + "/merged",
            output_name = babyname + ".root",
            condor_submit_params = {"sites":"UAF"},
            output_is_tree = True,
            # check_expectedevents = True,
            tag = tag,
            cmssw_version = "CMSSW_9_2_8",
            scram_arch = "slc6_amd64_gcc530",
            no_load_from_backup = True,
        )
        maker_tasks.append(maker_task)
        merge_tasks.append(merge_task)
        

    for i in range(100):
        total_summary = {}
            
        for maker_task, merge_task in zip(maker_tasks,merge_tasks):
            maker_task.process()

            if maker_task.complete():
                do_cmd("mkdir -p {}/merged".format(maker_task.get_outputdir()))
                do_cmd("mkdir -p {}/skimmed".format(maker_task.get_outputdir()))
                merge_task.reset_io_mapping()
                merge_task.update_mapping()
                merge_task.process()

            total_summary[maker_task.get_sample().get_datasetname()] = maker_task.get_task_summary()
            total_summary[merge_task.get_sample().get_datasetname()] = merge_task.get_task_summary()

        # parse the total summary and write out the dashboard
        StatsParser(data=total_summary, webdir="~/public_html/dump/metis_stopbaby/").do()

        # 1 hr power nap
        time.sleep(15.*60)

    # If it's complete, make a dummy sample out of the output directory
    # in order to pick up the files. Then cat out the contents and sum
    # them up. This should be 3*2*10 = 100

