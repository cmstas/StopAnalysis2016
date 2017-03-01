#!/bin/bash

# Welcome
echo "----------------------------------"
echo "Go Go Analyzer!"
echo ""

# Check that necesarry file structure existis
echo "Checking for valid directory structure..." 
echo ""
if [ ! -d Output/Histos ]; then mkdir -p Output/Histos; fi
if [ ! -d Output/Plots ]; then mkdir -p Output/Plots; fi
if [ ! -d Output/Tables ]; then mkdir -p Output/Tables; fi
if [ ! -d Output/Log ]; then mkdir -p Output/Log; fi

# Create Histograms of all samples
echo "Creating Histograms..."
echo ""
#root -l -b -q head.C stopBabyLooper__CR2l_bulkTTbar.C++ >& Output/Log/stopBabyLooper__CR2l_bulkTTbar.log 

# If, necessary, scale samples (should be done in looper)
#echo "Scaling Samples..."
#echo ""
#root -l -b -q head.C scaleSamples.C++'("Output/Histos/", "Output/Histos/")' >& Output/Log/scaleSamples.log

# Merge Samples, to print cutflow before zeroing negative yields
echo "Merging Samples to print yields, before zeroing negative yields.."
echo ""
#root -l -b -q head.C mergeStopBabies.C++'("Output/Histos/", "Output/Histos/",false)' >& Output/Log/mergeStopBabies_beforeZeroingAMCNLO.log

# Print yields of all inputs
echo "Printing yields of all inputs before zeroing amcnlo samples..."
echo ""
#root -l -b -q head.C tableMaker_allInputs.C++'("Output/Histos/","Output/Tables/yields_allInputs_beforeZeroing",false)' >& Output/Log/tableMaker_allInputs_beforeZeroingAMCNLO.log 

# For aMC@NLO samples, zero yields if final weight is negative
echo "Zeroing negative Yields..."
echo ""
#root -l -b -q head.C zeroOutNegativeYields.C++'("Output/Histos/")' >& Output/Log/zeroOutNegativeYields.log

# Merge Samples
echo "Merging Samples..."
echo ""
#root -l -b -q head.C mergeStopBabies.C++'("Output/Histos/", "Output/Histos/",true)' >& Output/Log/mergeStopBabies.log

# Print yields of all inputs
echo "Printing yields of all inputs..."
echo ""
#root -l -b -q head.C tableMaker_allInputs.C++'("Output/Histos/","Output/Tables/yields_allInputs")' >& Output/Log/tableMaker_allInputs.log 

# Print yields of summed inputs
echo "Printing yields of summmed inputs..."
echo ""
#root -l -b -q head.C tableMaker_summedInputs.C++'("Output/Histos/","Output/Tables/yields_summedInputs")' >& Output/Log/tableMaker_summedInputs.log 

# Calculate Uncertainties 
echo "Calculating Uncertainties..."
echo ""
#root -l -b -q head.C calcErrors.C++ >& Output/Log/calcErrors.log

# Make plots 
echo "Making Plots..."
echo ""
root -l -b -q head.C plotMaker.C++ >& Output/Log/plotMaker_byGenDecay.log
root -l -b -q head.C plotMaker.C++'(false)' >& Output/Log/plotMaker_byProduction.log

# Making Plots for data trigger efficiency studies
echo "Making plots for trigger efficiency studies..."
echo ""
root -l -b -q head.C diLepTriggerEfficiency_analyzer.C++ >& Output/Log/diLeptriggerEfficiency_analyzer.log

# Making Tables for ttbarSystem pT SFs
echo "Calculating ttbarSystemPt SF..."
echo ""
root -l -b -q head.C ttbarSystemPt_analyzer.C++ >& Output/Log/ttbarSystemPt_analyzer.log
root -l -b -q head.C ttbarSystemPt_plotMaker.C++ >& Output/Log/ttbarSystemPt_plotMaker_byGenDecay.log
root -l -b -q head.C ttbarSystemPt_plotMaker.C++'(false)' >& Output/Log/ttbarSystemPt_plotMaker_byProduction.log

# Create pdfs of latex files
echo "Converting Tex to PDF..."
echo ""
cd Output/Tables/
for x in `/bin/ls *.tex`; do pdflatex $x >& pass1.log; pdflatex $x >& ../Log/pdf2tex_$x.log; rm *.aux; rm *.log; done
cd ../../

# Clean up 
echo "Cleaning Up..."
echo ""
. clean.sh

# Done!
echo ""
echo "----------------------------------"
echo " Analysis Results Written To: "
echo "   Output/ " 
echo "---------------------------------"