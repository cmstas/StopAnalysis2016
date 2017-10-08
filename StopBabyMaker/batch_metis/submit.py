from __future__ import print_function

import time
import itertools
import json
import traceback

from metis.Sample import SNTSample
from metis.StatsParser import StatsParser
from metis.Utils import send_email


if __name__ == "__main__":

    dataset_names = [
        # "/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM",
        "/Dummy_test_StopBabyMaker_v25/CMS4",
    ]

    for i in range(10000):

        total_summary = {}
        for dsname in dataset_names:

            try:
                task = CondorTask(
                    sample = SNTSample(
                        dataset=dsname,
                    ),
                    events_per_output = 350e3,
                    output_name = "merged_ntuple.root",
                    tag = "v25",
                    scram_arch = "slc6_amd64_gcc700",
                    executable = "condor_executable.sh",
                    tarfile = "stopBabyMaker_v25.tar.gz",
                    condor_submit_params = {"sites": "UAF,T2_US_UCSD,UCSB"},
                )

                task.process()
            except:
                traceback_string = traceback.format_exc()
                print("Runtime error:\n{0}".format(traceback_string))
                # send_email(subject="metis error", body=traceback_string)

            total_summary[dsname] = task.get_task_summary()

        StatsParser(data=total_summary, webdir="~/public_html/dump/metis/").do()

        time.sleep(60.*60)
