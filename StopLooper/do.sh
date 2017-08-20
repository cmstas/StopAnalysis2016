#!/bin/bash

make -j 12 || return $?


INDIR=/nfs-7/userdata/haweber/stopbabiesInteractive/2017_5p8fbinv

OUTDIR=output/temp
LOGDIR=logs
mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

declare -a Samples=(data_singlemu)

for SAMPLE in ${Samples[@]}; do
    echo ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
    ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
    # echo nice -n 10 ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
    # eval "nohup nice -n 10 ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} >& ${LOGDIR}/log_${SAMPLE}.txt &"
    # echo ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
    # eval "nohup ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} >& ${LOGDIR}/log_${SAMPLE}.txt &"
done

