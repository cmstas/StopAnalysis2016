
SAMPLE1=`echo rootfiles/SRandCRHistos_TTbar_lepbinned.root`
SAMPLE2=`echo rootfiles/SRandCRHistos_tW_lepbinned.root`
SAMPLE3=`echo rootfiles/SRandCRHistos_WJets_lepbinned.root`
SAMPLE4=`echo rootfiles/SRandCRHistos_Zinv_lepbinned.root`
SAMPLE5=`echo rootfiles/SRandCRHistos_NonZRare_lepbinned.root`
SAMPLE6=`echo rootfiles/SRandCRHistos_Rest_lepbinned.root`
SAMPLE0=`echo rootfiles/SRandCRHistos_lepbinned.root`

if [ -f ${SAMPLE1} ] && [ -f ${SAMPLE2} ] && [ -f ${SAMPLE3} ] && [ -f ${SAMPLE4} ] && [ -f ${SAMPLE5} ] && [ -f ${SAMPLE6} ]
then
    Size1=`stat -c %s "${SAMPLE1}"`
    Size2=`stat -c %s "${SAMPLE2}"`
    Size3=`stat -c %s "${SAMPLE3}"`
    Size4=`stat -c %s "${SAMPLE4}"`
    Size5=`stat -c %s "${SAMPLE5}"`
    Size6=`stat -c %s "${SAMPLE6}"`
    if [ ${Size1} -lt 5120 ] || [ ${Size2} -lt 5120 ] || [ ${Size3} -lt 5120 ] || [ ${Size4} -lt 5120 ] || [ ${Size5} -lt 5120 ] || [ ${Size6} -lt 5120 ]
    then
	echo "One file seems not to be really filled (<5kb): ${SAMPLE1} - ${Size1}, ${SAMPLE2} - ${Size2}, ${SAMPLE3} - ${Size3}, ${SAMPLE4} - ${Size4}, ${SAMPLE5} - ${Size5}, ${SAMPLE6} - ${Size6} : stopping."
	return 1
    fi
    if [ ${SAMPLE0} -nt ${SAMPLE1} ] && [ ${SAMPLE0} -nt ${SAMPLE2} ] && [ ${SAMPLE0} -nt ${SAMPLE3} ] && [ ${SAMPLE0} -nt ${SAMPLE4} ] && [ ${SAMPLE0} -nt ${SAMPLE5} ] && [ ${SAMPLE0} -nt ${SAMPLE5} ]
    then
	echo "Target file ${SAMPLE0} is newer than any of the input files - stop."
	return 1
    fi
    rm ${SAMPLE0}
    hadd -f ${SAMPLE0} ${SAMPLE1} ${SAMPLE2} ${SAMPLE3} ${SAMPLE4} ${SAMPLE5} ${SAMPLE6}
else    
    echo "one of these does not exist ${SAMPLE1} ${SAMPLE2} ${SAMPLE3} ${SAMPLE4} ${SAMPLE5} ${SAMPLE6}"
    return 1
fi
