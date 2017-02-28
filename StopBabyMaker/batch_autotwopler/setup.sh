#! /bin/bash


#
# CONFIGURATION VARS
#
ANALYSIS_NAME=Stop_1l

BABY_VERSION=v24

TARBALL_NAME=forCondor_stopBabyMaker_80x

INSTRUCTIONS_FILE=instructions_2017.txt
#INSTRUCTIONS_FILE=instructions.txt
#INSTRUCTIONS_FILE=instructions_test.txt

EXECUTABLE_NAME=condor_executable.sh

BATCH_DIR=`pwd`

MAKER_NAME=StopBabyMaker
MAKER_PATH=/home/users/jgwood/Stop_1Lepton/analysis2016__fullYear/CMSSW_8_0_5_patch1/src/StopAnalysis/
MAKER_DIR=$MAKER_PATH/$MAKER_NAME/

CORE_NAME=CORE
CORE_PATH=/home/users/jgwood/Stop_1Lepton/analysis2016__fullYear/CMSSW_8_0_5_patch1/src/
CORE_DIR=$CORE_PATH/$CORE_NAME


#
# Move to same level as StopAnalysis
#
cd ../../../


#
# Checkout NtupleTools from git
#
if [ ! -d NtupleTools/ ]; then
    git clone ssh://git@github.com/cmstas/NtupleTools
fi

cd NtupleTools/AutoTwopler/


#
# Update params.py with configuration
#
sed -i 's/campaign = "80X"/campaign = "80X_stopBabyMaker"/g' params.py


#
# Copy over relevant scripts for batch
#
cp -r $BATCH_DIR/$INSTRUCTIONS_FILE ./
sed -i s/ANALYSIS/$ANALYSIS_NAME/g $INSTRUCTIONS_FILE
sed -i s/VERSION/$BABY_VERSION/g $INSTRUCTIONS_FILE
sed -i s/TARBALL/$TARBALL_NAME/g $INSTRUCTIONS_FILE
sed -i s/EXECUTABLE/$EXECUTABLE_NAME/g $INSTRUCTIONS_FILE

cp -r $BATCH_DIR/$EXECUTABLE_NAME ./

cp -r $BATCH_DIR/batch.py ./
cp -r $BATCH_DIR/sweepRoot.C ./
cp -r $BATCH_DIR/sweepRoot.sh ./
cp -r $BATCH_DIR/mergeHadoopFiles.C ./
cp -r $BATCH_DIR/mergeScript.sh ./


#
# copy and compile tarball for babyMaker
#
if [ ! -d $TARBALL_NAME ]; then

    mkdir $TARBALL_NAME/
    mkdir $TARBALL_NAME/$CORE_NAME/
    mkdir $TARBALL_NAME/$MAKER_NAME/
    
    CONDOR_DIR_NAME=`pwd`/$TARBALL_NAME
    
    cp -r $MAKER_DIR/*.cc $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/*.h $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/Makefile $CONDOR_DIR_NAME/$MAKER_NAME/
    
    # modify makefile so it knows where CORE is on condor node, 
    #  relative to the untarred directory location.
    sed -i '/^COREPATH/d' $CONDOR_DIR_NAME/$MAKER_NAME/Makefile
    sed -i '1i COREPATH = ../CORE/' $CONDOR_DIR_NAME/$MAKER_NAME/Makefile
    
    cp -r $MAKER_DIR/xsec_stop_13TeV.root $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/puWeights_2016data_36p6fbinv.root $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/*.dat $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/*.C $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/stop_variables/ $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/json_files/ $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/jecfiles/ $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/btagsf/ $CONDOR_DIR_NAME/$MAKER_NAME/
    cp -r $MAKER_DIR/lepsf/ $CONDOR_DIR_NAME/$MAKER_NAME/

    cp -r $BATCH_DIR/sweepRoot.C $CONDOR_DIR_NAME/$MAKER_NAME/

    cp -r $CORE_DIR/* $CONDOR_DIR_NAME/$CORE_NAME/
    
    echo ""
    echo "  All files copied, compiling code..."
    echo ""
    
    cd $CONDOR_DIR_NAME/$CORE_NAME/
    make clean
    make
    
    cd ../$MAKER_NAME/stop_variables/
    make clean
    make
    
    cd ../
    make clean
    make

    echo ""
    echo "  Compiling code complete, creating tarball..."
    echo ""
    cd ../../
    tar czf $TARBALL_NAME.tar.gz $TARBALL_NAME/
fi


#
# Exectue NtupleTools/Autotwopler/setup.sh
#
. setup.sh


#
# Move back to batch_autotwopler
#
cd $BATCH_DIR


#
# Print details about job submission to screen
#
echo ""
echo ""
echo "[setup] Merged Babies and Log Files Written to: "
echo "[setup]   /nfs-7/userdata/$USER/tupler_babies/"
echo "[setup] Unmerged Babies Written to: "
echo "[setup]   /hadoop/cms/store/user/$USER/AutoTwopler_babies/"
echo "[setup] To launch jobs do: "
echo "[setup]  . makeBabies.sh"


#
# Flag for successful environment setup
#
CONDOR_ENV_READY=true
