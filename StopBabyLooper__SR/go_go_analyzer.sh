#!/bin/bash

# Welcome
echo "----------------------------------"
echo "Go Go Analyzer!"
echo ""

# Check that necesarry file structure existis
echo "Checking for valid directory structure..." 
echo ""
if [ ! -d Histos/Nominal ]; then mkdir -p Histos/Nominal; fi
if [ ! -d Histos/JesUp ]; then mkdir -p Histos/JesUp; fi
if [ ! -d Histos/JesDn ]; then mkdir -p Histos/JesDn; fi

if [ ! -d Output/Plots ]; then mkdir -p Output/Plots; fi
if [ ! -d Output/Tables ]; then mkdir -p Output/Tables; fi
if [ ! -d Output/Log ]; then mkdir -p Output/Log; fi

# Create Histograms of all samples
echo "Creating Histograms..."
echo ""
root -l -b -q head.C stopBabyLooper.C++ >& Output/Log/stopBabyLooper.log 

# Merge JESUp/Down with nominal
echo "Combining JES Up/Down with nominal..."
echo ""
root -l -b -q head.C combineSystematics.C++ >& Output/Log/combineSystematics.log

# If, necessary, scale samples (should be done in looper
#echo "Scaling Samples..."
#echo ""
#root -l -b -q head.C scaleSamples.C++'("Histos/Nominal/", "Histos/Nominal/")' >& Output/Log/scaleSamples.log

# Merge Samples, to print cutflow before zeroing negative yields
echo "Merging Samples to print yields, before zeroing negative yields.."
echo ""
root -l -b -q head.C mergeStopBabies.C++'("Histos/Nominal/", "Histos/Nominal/",false)' >& Output/Log/mergeStopBabies_beforeZeroingAMCNLO.log

# Print yields of all inputs
echo "Printing yields of all inputs before zeroing amcnlo samples..."
echo ""
root -l -b -q head.C tableMaker_allInputs.C++'("Histos/Nominal/","Output/Tables/yields_allInputs_beforeZeroing.tex",false)' >& Output/Log/tableMaker_allInputs_beforeZeroingAMCNLO.log 

# For aMC@NLO samples, zero yields if final weight is negative
echo "Zeroing negative Yields..."
echo ""
root -l -b -q head.C zeroOutNegativeYields.C++'("Histos/Nominal/")' >& Output/Log/zeroOutNegativeYields.log

# Merge Samples
echo "Merging Samples..."
echo ""
root -l -b -q head.C mergeStopBabies.C++'("Histos/Nominal/", "Histos/Nominal/",true)' >& Output/Log/mergeStopBabies.log

# Print yields of all inputs
echo "Printing yields of all inputs..."
echo ""
root -l -b -q head.C tableMaker_allInputs.C++'("Histos/Nominal/","Output/Tables/yields_allInputs.tex")' >& Output/Log/tableMaker_allInputs.log 

# Print yields of summed inputs
echo "Printing yields of summmed inputs..."
echo ""
root -l -b -q head.C tableMaker_summedInputs.C++'("Histos/Nominal/","Output/Tables/yields_summedInputs.tex")' >& Output/Log/tableMaker_summedInputs.log 
root -l -b -q head.C tableMaker_summedInputs_newBinning.C++'("Histos/Nominal/","Output/Tables/yields_summedInputs_newBinning__SR.tex")' >& Output/Log/tableMaker_summedInputs_newBinning__SR.log 

# Calculate Uncertainties
echo "Calculating Uncertainties..."
echo ""
root -l -b -q head.C calcErrors.C++ >& Output/Log/calcErrors.log

# Make plots
echo "Making Plots..."
echo ""
root -l -b -q head.C plotMaker.C++ >& Output/Log/plotMaker_byGenDecay.log
root -l -b -q head.C plotMaker.C++'(false)' >& Output/Log/plotMaker_byProduction.log


# Create pdfs of latex files
echo "Converting Tex to PDF"
echo ""
cd Output/Tables/
for x in `/bin/ls *.tex`; do pdflatex $x; pdflatex $x; done
cd ../../

# Done!
echo ""
echo "----------------------------------"
echo " Analysis Results Written To: "
echo "   Histos/ "
echo "   Output/ " 
echo "---------------------------------"