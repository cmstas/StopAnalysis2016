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

if [ $# -eq 0 ]
then
    echo Run analysis 0. If you wish to set something set
    echo CombineCardsAllScans.sh ANALYSIS CORRELATED DROPSIGCONT NOSIGSYST NOBGSYST FAKEDATA
fi

if [ $# -gt 0 ]
then
    analysis=$1
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
if [ $# -gt 1 ]
then
    correlated=$2
fi
if [ $# -gt 2 ]
then
    dropsigcont=$3
fi
if [ $# -gt 3 ]
then
    nosigsyst=$4
fi
if [ $# -gt 4 ]
then
    nobgsyst=$5
fi
if [ $# -gt 5 ]
then
    fakedata=$6
fi

bash CombineCardsScan.sh T2tt ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tt_lefthanded ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tt_righthanded ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2bW ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb_0_100 ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb_25_75 ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb_33_67 ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb_50_50 ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb_67_33 ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb_75_25 ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
bash CombineCardsScan.sh T2tb_100_0 ${analysis} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
