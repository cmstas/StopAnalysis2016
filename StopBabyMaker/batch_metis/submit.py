from __future__ import print_function

import time

from metis.Sample import SNTSample
from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask
from metis.StatsParser import StatsParser
from metis.Utils import do_cmd


if __name__ == "__main__":

    dataset_names = [
        # "/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM",
        # "/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3/MINIAODSIM",
        "/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUSummer16Fast_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        "/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUSummer16Fast_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        "/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUSummer16Fast_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    ]

    # Make a directory sample, giving it the location and a dataset name for bookkeeping purposes
    # The globber must be customized (by default, it is *.root) in order to pick up the text files

    # Make a CondorTask (3 in total, one for each input)
    maker_tasks = []
    merge_tasks = []

    for dsname in dataset_names:
        cmsswver = "CMSSW_9_4_0_pre2"
        scramarch = "slc6_amd64_gcc700"
        tarfile = "input.tar.gz"
        tag = "v25_3"
        maker_task = CondorTask(
                sample = SNTSample(dataset=dsname),
                files_per_output = 1,
                tag = tag,
                outdir_name = "stopBaby_" + dsname[5:34].strip("_"),
                output_name = "stopbaby.root",
                executable = "condor_executable.sh",
                cmssw_version = cmsswver,
                scram_arch = scramarch,
                arguments = "1" if dsname[:4] == "/SMS" else "0", # isFastsim
                tarfile = tarfile,
                condor_submit_params = {"sites": "UAF,T2_US_UCSD,UCSB"},
        )
        merge_task = CondorTask(
                sample = DirectorySample( 
                    dataset=dsname.replace("MINIAODSIM","MERGE"),
                    location=maker_task.get_outputdir(),
                ),
                executable = "ProjectMetis/metis/executables/condor_hadd.sh",
                open_dataset = False,
                files_per_output = 12,
                outdir_name = "merged_stopBaby_" + dsname[5:34].strip("_"),
                output_name = dsname[5:34].strip("_") + ".root",
                condor_submit_params = {"sites":"UAF"},
                output_is_tree = True,
                check_expectedevents = True,
                tag = tag,
                cmssw_version = cmsswver,
                scram_arch = scramarch,
        )
        maker_tasks.append(maker_task)
        merge_tasks.append(merge_task)
        

    for i in range(100):
        total_summary = {}
            
        for maker_task, merge_task in zip(maker_tasks,merge_tasks):
            maker_task.process()

            if maker_task.complete():
                merge_task.reset_io_mapping()
                merge_task.update_mapping()
                merge_task.process()

            total_summary[maker_task.get_sample().get_datasetname()] = maker_task.get_task_summary()
            total_summary[merge_task.get_sample().get_datasetname()] = merge_task.get_task_summary()

        # parse the total summary and write out the dashboard
        StatsParser(data=total_summary, webdir="~/public_html/dump/metis_stopbaby/").do()

        # 1 hr power nap
        time.sleep(10.*60)

    # If it's complete, make a dummy sample out of the output directory
    # in order to pick up the files. Then cat out the contents and sum
    # them up. This should be 3*2*10 = 100

