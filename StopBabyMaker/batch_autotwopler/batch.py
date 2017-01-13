import os, sys

import run

# Configure Paramters
import params as p
p.scram_arch = "slc6_amd64_gcc530"
p.cmssw_ver = "CMSSW_8_0_5"
#p.sweepRoot_scripts = [ "sweepRoot.sh", "sweepRoot.C" ]
p.sweepRoot_scripts = []
p.merging_scripts = [ "mergeScript.sh", "mergeHadoopFiles.C" ]
p.exit_when_done = True

# Main
run.main(instructions="instructions_2017.txt",params=p)
