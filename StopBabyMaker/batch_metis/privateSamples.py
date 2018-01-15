from __future__ import print_function

import time

from metis.Sample import SNTSample
from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask
from metis.StatsParser import StatsParser
from metis.Utils import do_cmd


if __name__ == "__main__":

    cms4_samples = {
        "TTJets_amcnlo" : "/hadoop/cms/store/user/sicheng/ProjectMetis/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3_MINIAODSIM_CMS4_V00-00-07_test",
        "ttbar_powheg" : "/hadoop/cms/store/user/sicheng/ProjectMetis/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1_MINIAODSIM_CMS4_V00-00-07_test2",
        "SMS_T2tt_mStop-400to1200_madgraph" : "/hadoop/cms/store/user/sicheng/ProjectMetis/SMS-T2tt_mStop-400to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1_MINIAODSIM_CMS4_V00-00-02_test",
        "SMS_T2bt_madgraph" : "/hadoop/cms/store/user/sicheng/ProjectMetis/SMS-T2bt_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1_MINIAODSIM_CMS4_V00-00-02_test",
        "SMS_T2bW_madgraph" : "/hadoop/cms/store/user/sicheng/ProjectMetis/SMS-T2bW_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1_MINIAODSIM_CMS4_V00-00-02_test",
        "W4JetsToLNu_madgraph" : "/hadoop/cms/store/user/sicheng/ProjectMetis/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1_MINIAODSIM_CMS4_V00-00-07_test2",
        "W3JetsToLNu_madgraph" : "/hadoop/cms/store/user/sicheng/ProjectMetis/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1_MINIAODSIM_CMS4_V00-00-07_test2",
        "W2JetsToLNu_madgraph" : "/hadoop/cms/store/user/sicheng/ProjectMetis/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1_MINIAODSIM_CMS4_V00-00-07_test2",
    }


    # Make a directory sample, giving it the location and a dataset name for bookkeeping purposes
    # The globber must be customized (by default, it is *.root) in order to pick up the text files

    # Make a CondorTask (3 in total, one for each input)
    maker_tasks = []
    merge_tasks = []

    for dsname, samploc in cms4_samples.items():
        cmsswver = "CMSSW_9_4_0"
        scramarch = "slc6_amd64_gcc630"
        tarfile = "input.tar.gz"
        tag = "v26_2"
        maker_task = CondorTask(
            sample = DirectorySample(
                dataset=dsname,
                location=samploc,
            ),
            # open_dataset = True,
            files_per_output = 1,
            tag = tag,
            cmssw_version = cmsswver,
            scram_arch = scramarch,
            tarfile = tarfile,
            executable = "condor_executable.sh",
            outdir_name = "stopBaby_" + dsname,
            output_name = "stopbaby.root",
            arguments = "1" if "SMS" in dsname else "0", # isFastsim
            condor_submit_params = {"sites": "UAF,T2_US_UCSD,UCSB"},
            # no_load_from_backup = True,
        )
        merge_task = CondorTask(
            sample = DirectorySample( 
                dataset="merge_"+dsname,
                location=maker_task.get_outputdir(),
            ),
            # open_dataset = True, flush = True,
            executable = "merge_executable.sh",
            tarfile = "merge_scripts.tar.gz",
            files_per_output = 100000,
            output_dir = maker_task.get_outputdir() + "/merged",
            output_name = "merged_" + dsname + ".root",
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

