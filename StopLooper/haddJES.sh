SAMPLE=$1

if [ $# -eq 0 ]
then
    echo "No argument supplied - define your sample"
    return 1
fi
SAMPLENOJES=`echo rootfiles/SRandCRHistos_${SAMPLE}.root`
SAMPLEJESUP=`echo rootfiles/SRandCRHistos_${SAMPLE}_JESup.root`
SAMPLEJESDN=`echo rootfiles/SRandCRHistos_${SAMPLE}_JESdown.root`
SAMPLEALL=`echo rootfiles/SRandCRHistos_${SAMPLE}_all.root`
if [[ $SAMPLE == *"T2"* ]]
then
    SAMPLENOJES=`echo rootfiles/Histos_Signal_${SAMPLE}.root`
    SAMPLEJESUP=`echo rootfiles/Histos_Signal_${SAMPLE}_JESup.root`
    SAMPLEJESDN=`echo rootfiles/Histos_Signal_${SAMPLE}_JESdown.root`
    SAMPLEALL=`echo rootfiles/Histos_Signal_${SAMPLE}_all.root`
fi
if [ -f ${SAMPLENOJES} ] && [ -f ${SAMPLEJESUP} ] && [ -f ${SAMPLEJESUP} ]
then
    Size1=`stat -c %s "${SAMPLENOJES}"`
    Size2=`stat -c %s "${SAMPLEJESUP}"`
    Size3=`stat -c %s "${SAMPLEJESDN}"`
    if [ ${Size1} -lt 5120 ] || [ ${Size2} -lt 5120 ] || [ ${Size3} -lt 5120 ]
    then
	echo "One file seems not to be really filled (<5kb): ${SAMPLENOJES} - ${Size1},  ${SAMPLEJESUP} - ${Size2},  ${SAMPLEJESDN} - ${Size3} : stopping."
	return 1
    fi
    if [ ${SAMPLEALL} -nt ${SAMPLENOJES} ] && [ ${SAMPLEALL} -nt ${SAMPLEJESUP} ] && [ ${SAMPLEALL} -nt ${SAMPLEJESDN} ]
    then
	echo "Target file ${SAMPLEALL} is newer than any of the input files - stop."
	return 1
    fi
    rm ${SAMPLEALL}
    hadd -f ${SAMPLEALL} ${SAMPLENOJES} ${SAMPLEJESUP} ${SAMPLEJESDN}
else    
    echo "one of these does not exist ${SAMPLENOJES} ${SAMPLEJESUP} ${SAMPLEJESDN}"
    return 1
fi
