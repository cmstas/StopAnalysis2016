#!/bin/bash

echo "************************************"
echo "Assemble CONDOR FILES for submission"
echo "************************************"

# Check that CMSSW base,babymaker location and core location is set
if [ -z $CMSSW_BASE ]; then
    echo "CMSSW_BASE var not set, run cmsenv, exiting..."
    return 1;
fi
if [ -z $MAKER_NAME ]; then
    echo "MAKER_NAME not set, don't know which babymaker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $MAKER_PATH ]; then
    echo "MAKER_PATH not set, don't know which babymaker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $MAKER_DIR ]; then
    echo "MAKER_DIR not set, don't know which babymaker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CORE_NAME ]; then
    echo "CORE_NAME not set, don't know which CORE to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CORE_PATH ]; then
    echo "CORE_PATH not set, don't know which CORE to use :(, exiting..."
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
cd $HOME
if [ -d $CONDOR_DIR_NAME ]; then
    rm -rf $CONDOR_DIR_NAME
fi
mkdir $CONDOR_DIR_NAME
mkdir $CONDOR_DIR_NAME/$MAKER_NAME/
mkdir $CONDOR_DIR_NAME/$CORE_NAME/

cp -r $MAKER_DIR/*.cc $CONDOR_DIR_NAME/$MAKER_NAME/
cp -r $MAKER_DIR/*.h $CONDOR_DIR_NAME/$MAKER_NAME/
cp -r $MAKER_DIR/Makefile $CONDOR_DIR_NAME/$MAKER_NAME/

#modify makefile so it knows where is the CORE on condor relative to the untarred directory location.
sed -i '/^COREPATH/d' $CONDOR_DIR_NAME/$MAKER_NAME/Makefile
sed -i '1i COREPATH = ../CORE/' $CONDOR_DIR_NAME/$MAKER_NAME/Makefile
cp -r $MAKER_DIR/*.dat $CONDOR_DIR_NAME/$MAKER_NAME/
cp -r $MAKER_DIR/*.C $CONDOR_DIR_NAME/$MAKER_NAME/

cp -r $CORE_DIR/* $CONDOR_DIR_NAME/$CORE_NAME/

cp -r $MAKER_DIR/stop_variables/ $CONDOR_DIR_NAME/$MAKER_NAME/

cp -r $MAKER_DIR/json_files/ $CONDOR_DIR_NAME/$MAKER_NAME/



cd $CONDOR_DIR_NAME/$CORE_NAME/
make clean
make


cd ../$MAKER_NAME/stop_variables/
make clean
make

cd ../
make clean
make

cd $HOME

tar czf $CONDOR_DIR_NAME.tar.gz $CONDOR_DIR_NAME/

cd $START_DIR

echo "  Tarball complete, creating dir for logfiles"
#Make dir for logs
if [ ! -d logs ] 
then
  mkdir logs
fi

#Shit for Lorentz Vectors, etc.
#sed -i "/struct val_err_t { float value; float error; };/i #include\ \"Math/Vector4D.h\" \n#include\ \"Math/LorentzVector.h\" \n\n\#ifdef\ __MAKECINT__\n\#pragma\ link\ C++\ class\ ROOT::Math::PxPyPzE4D<float>+;\n\#pragma\ link\ C++\ class\ ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>\ >+;\n\#pragma\ link\ C++\ typedef ROOT::Math::XYZTVectorF;\n\#endif" fakeratelooper.h

echo "***************************** :) *********************************************"
echo "  Condor preparation complete! Now edit some more scripts for condor!"
echo "-----------------------------------------------------------------------"
echo "  Things batch.sh needs to know:"
echo "  * sampleList_in"
echo "  * copy_dir"
echo "-----------------------------------------------------------------------"
echo "  Things condorFileTemplate needs to know:"
echo "  * notify_user"
echo "-----------------------------------------------------------------------"
echo "  done? now submit jobs with . batch.sh to test your jobs! "
echo "  Condor log files will be availble in ./logs, and you can debug with them "
echo "***************************** :) the end of test job :) *********************************************"
