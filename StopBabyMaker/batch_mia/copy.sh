#!/bin/bash

echo "************************************"
echo "Assemble CONDOR FILES for submission"
echo "************************************"

# Check that CMSSW base,babymaker location and core location is set
if [ -z $CMSSW_BASE ]; then
    echo "CMSSW_BASE var not set, run cmsenv, exiting..."
    return 1;
fi
if [ -z $BABYMAKER_DIR_NAME ]; then
    echo "BABYMAKER_DIR_NAME not set, don't know which babymaker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CORE_DIR ]; then
    echo "CORE_DIR not set, don't know which CORE to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CONDOR_DIR_NAME ]; then
    echo "Do not know what name to use for your tarball :(, exiting..."
    echo "Please set it in setup.sh! and do source setup.sh"
    return 1;
fi


echo ""
echo "  Creating tarball to transfer to condor node..."
cd $PWD
if [ -d $CONDOR_DIR_NAME ]; then
    rm -rf $CONDOR_DIR_NAME
fi
mkdir $CONDOR_DIR_NAME
mkdir $CONDOR_DIR_NAME/StopBabyMaker/
mkdir $CONDOR_DIR_NAME/CORE/

cp -r $BABYMAKER_DIR_NAME/*.cc $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $BABYMAKER_DIR_NAME/*.h $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $BABYMAKER_DIR_NAME/Makefile $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $BABYMAKER_DIR_NAME/*.o $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $BABYMAKER_DIR_NAME/runBabyMaker $CONDOR_DIR_NAME/StopBabyMaker/

#modify makefile so it knows where is the CORE on condor relative to the untarred directory location.
sed -i '/^COREPATH/d' $CONDOR_DIR_NAME/StopBabyMaker/Makefile
sed -i '1i COREPATH = ../CORE/' $CONDOR_DIR_NAME/StopBabyMaker/Makefile
cp -r $BABYMAKER_DIR_NAME/*.dat $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $BABYMAKER_DIR_NAME/*.C $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $BABYMAKER_DIR_NAME/stop_variables/ $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $BABYMAKER_DIR_NAME/json_files/ $CONDOR_DIR_NAME/StopBabyMaker/
cp -r $CORE_DIR/* $CONDOR_DIR_NAME/CORE/

tar czf $CONDOR_DIR_NAME.tar.gz $CONDOR_DIR_NAME/

cd $START_DIR

echo "  Tarball complete, creating dir for logfiles"
#Make dir for logs
#if [ ! -d logs ] 
#then
#  mkdir logs
#fi

#Shit for Lorentz Vectors, etc.
#sed -i "/struct val_err_t { float value; float error; };/i #include\ \"Math/Vector4D.h\" \n#include\ \"Math/LorentzVector.h\" \n\n\#ifdef\ __MAKECINT__\n\#pragma\ link\ C++\ class\ ROOT::Math::PxPyPzE4D<float>+;\n\#pragma\ link\ C++\ class\ ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>\ >+;\n\#pragma\ link\ C++\ typedef ROOT::Math::XYZTVectorF;\n\#endif" fakeratelooper.h

echo "***************************** :) ***********************************************************"
echo "  Condor preparation complete! Edit writeAllConfig.sh to generate condor submission files"
echo "***************************** :) the end of test job :) *********************************************"
