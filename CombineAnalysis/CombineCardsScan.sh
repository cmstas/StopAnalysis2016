#check cmssw and if it contains HiggsCombine
if [ -z $CMSSW_BASE ]; then
    echo "CMSSW_BASE var not set, run cmsenv, exiting..."
    exit 0;
fi
DIRECTORY=`echo $CMSSW_BASE/src/HiggsAnalysis`
if [ ! -d "$DIRECTORY" ]; then
    echo "Your CMSSW release does not have HiggsCombined installed. Please do."
    echo "Please read https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit"
    echo "You should have ${DIRECTORY}. Exiting..."
    exit 0;
fi

analysis=0

dropsigcont=false
correlated=true
fakedata=false
nosigsyst=false
nobgsyst=false

declare -i stopmasslow=100
declare -i stopmasshigh=975
declare -i stopmassstep=25
declare -i lspmasslow=0
declare -i lspmasshigh=500
declare -i lspmassstep=25

if [ $# -eq 0 ]
then
    echo You should provide at least the SIGNAL.
    echo To run you use
    echo CombineCardsScan.sh SIGNAL ANALYSIS CORRELATED DROPSIGCONT NOSIGSYST NOBGSYST FAKEDATA
    echo Use \'true\' if you want a boolean to be true - 1 does not work.
    return
fi
    
signal=$1

if [ $# -gt 1 ]
then
    analysis=$2
else
    echo You did not specify the analysis using standard one.
    echo Analysis 0 is standard one.
    echo No other analysis implemented so far.
fi

if [[ $analysis -lt 0 ]] || [[ $analysis -gt 0 ]]
then
    echo Your specified analysis has not been implemented.
    echo Analysis 0 is standard one.
    return
fi

if [ $# -gt 2 ]
then
    correlated=$3
fi
if [ $# -gt 3 ]
then
    dropsigcont=$4
fi
if [ $# -gt 4 ]
then
    nosigsyst=$5
fi
if [ $# -gt 5 ]
then
    nobgsyst=$6
fi
if [ $# -gt 6 ]
then
    fakedata=$7
fi

if [[ $signal == *"T2tt"* ]]
then
    stopmasslow=100
    stopmasshigh=950
    lspmasslow=0
    lspmasshigh=450
elif [[ $signal == *"T2tb"* ]]
then
    stopmasslow=200
    stopmasshigh=1000
    lspmasslow=0
    lspmasshigh=450
elif [[ $signal == *"T2bW"* ]]
then
    stopmasslow=150
    stopmasshigh=950
    lspmasslow=0
    lspmasshigh=375
fi

#echo Signal $signal has stop = $stopmasslow - $stopmasshigh, lsp = $lspmasslow - $lspmasshigh
#return

for (( t=0; t<=${stopmasshigh}; t+=$stopmassstep ))
do
    for (( l=$lspmasslow; l<=$lspmasshigh; l+=$lspmassstep ))
    do
	if [ $l -gt $t ]
	then
	    continue
	fi	   
	bash CombineCards.sh ${signal} ${analysis} ${t} ${l} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
    done
done
