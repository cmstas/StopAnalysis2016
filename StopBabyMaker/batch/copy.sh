#!/bin/bash

echo "************************************"
echo "Assemble CONDOR FILES for submission"
echo "************************************"


#
# Check that condor submission envionment is setup
#
if [ -z $CONDOR_ENV_READY ]; then
    echo ""
    echo "Condor_ENV_READY not set :(, exiting..."
    echo "do source setup.sh!"
    echo ""
    return 1;
fi


#
# Create tarball for condor jobs
#
echo ""
echo "  Copying files for tarball to transfer to condor node..."
echo ""

cd $SCRATCH_DIR
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


#
# Compile code in advance
#
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

cd $SCRATCH_DIR

#
# Finally make the tarball
#

echo ""
echo "  Compiling code complete, creating tarball..."
echo ""
tar czf $CONDOR_DIR_NAME.tar.gz $CONDOR_DIR_NAME/


cd $START_DIR


#
# Make logfile directory 
#
echo ""
echo "  Tarball complete, creating dir for logfiles"
echo ""
if [ ! -d $SCRATCH_DIR/logs ] 
then
  mkdir $SCRATCH_DIR/logs
fi


#
# Shit for Lorentz Vectors, etc.
#
#sed -i "/struct val_err_t { float value; float error; };/i #include\ \"Math/Vector4D.h\" \n#include\ \"Math/LorentzVector.h\" \n\n\#ifdef\ __MAKECINT__\n\#pragma\ link\ C++\ class\ ROOT::Math::PxPyPzE4D<float>+;\n\#pragma\ link\ C++\ class\ ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>\ >+;\n\#pragma\ link\ C++\ typedef ROOT::Math::XYZTVectorF;\n\#endif" fakeratelooper.h


#
# Final instructions for user
#
echo ""
echo "***************************** :) *********************************************"
echo "  Condor preparation complete! Now edit some more scripts for condor!"
echo "-----------------------------------------------------------------------"
echo "  Things batch.sh needs to know:"
echo "  * sampleList_in"
echo "-----------------------------------------------------------------------"
echo "  Things condorFileTemplate needs to know:"
echo "  * notify_user"
echo "-----------------------------------------------------------------------"
echo "  done? now submit jobs with . batch.sh to test your jobs! "
echo "  Condor log files will be availble in $SCRATCH_DIR/logs, and you can debug with them "
echo "***************************** :) the end of test job :) *********************************************"
echo ""