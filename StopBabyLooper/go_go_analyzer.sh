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
if [ ! -d Output/BkgEstimate ]; then mkdir -p Output/BkgEstimate; fi
if [ ! -d Output/Log ]; then mkdir -p Output/Log; fi

# Create Histograms of all samples
echo "Creating Histograms..."
echo ""
root -l -b -q head.C stopBabyLooper.C++ >& Output/Log/stopBabyLooper.log 

# If, necessary, scale samples (should be done in looper)
#echo "Scaling Samples..."
#echo ""
#root -l -b -q head.C scaleSamples.C++'("Output/Histos/", "Output/Histos/")' >& Output/Log/scaleSamples.log

# Merge Samples, to print cutflow before zeroing negative yields
echo "Merging Samples to print yields, before zeroing negative yields.."
echo ""
root -l -b -q head.C mergeStopBabies.C++'("Output/Histos/", "Output/Histos/",false)' >& Output/Log/mergeStopBabies_beforeZeroingAMCNLO.log

# Print yields of all inputs
echo "Printing yields of all inputs before zeroing amcnlo samples..."
echo ""
root -l -b -q head.C tableMaker_allInputs.C++'("Output/Histos/","Output/Tables/yields_allInputs_beforeZeroing",false)' >& Output/Log/tableMaker_allInputs_beforeZeroingAMCNLO.log 

# For aMC@NLO samples, zero yields if final weight is negative
echo "Zeroing negative Yields..."
echo ""
root -l -b -q head.C zeroOutNegativeYields.C++'("Output/Histos/")' >& Output/Log/zeroOutNegativeYields.log

# Merge Samples
echo "Merging Samples..."
echo ""
root -l -b -q head.C mergeStopBabies.C++'("Output/Histos/", "Output/Histos/",true)' >& Output/Log/mergeStopBabies.log

# Print yields of all inputs
echo "Printing yields of all inputs..."
echo ""
root -l -b -q head.C tableMaker_allInputs.C++'("Output/Histos/","Output/Tables/yields_allInputs")' >& Output/Log/tableMaker_allInputs.log 

# Print yields of summed inputs
echo "Printing yields of summmed inputs..."
echo ""
root -l -b -q head.C tableMaker_summedInputs.C++'("Output/Histos/","Output/Tables/yields_summedInputs")' >& Output/Log/tableMaker_summedInputs.log 

# Calculate Uncertainties 
echo "Calculating Uncertainties..."
echo ""
root -l -b -q head.C calcErrors.C++ >& Output/Log/calcErrors.log

# Make plots 
echo "Making Plots..."
echo ""
root -l -b -q head.C plotMaker.C++ >& Output/Log/plotMaker_byGenDecay.log
root -l -b -q head.C plotMaker.C++'(false)' >& Output/Log/plotMaker_byProduction.log
root -l -b -q head.C pieCharts.C++ >& Output/Log/pieCharts.log

# Background Estimates 
echo "Calculating DiLepton Background Estimate..."
echo ""
root -l -b -q head.C bkgEstimate_diLepton.C++ >& Output/Log/bkgEstimate_diLepton.log
sed -i 's/0\.0~-~0\.0~\\%/--/g' Output/BkgEstimate/bkgEst_lostLepton__*__uncertaintyTable__summary.tex

echo "Calculating 1lep from W Background Estimate..."
echo ""
#root -l -b -q head.C bkgEstimate_1lepFromW.C++ >& Output/Log/bkgEstimate_1lepFromW.log

echo "Calculating 1lep from Top Background Estimate..."
echo ""
root -l -b -q head.C bkgEstimate_1lepFromTop.C++ >& Output/Log/bkgEstimate_1lepFromTop.log

echo "Calculating Z->NuNu Background Estimate..."
echo ""
root -l -b -q head.C bkgEstimate_ZtoNuNu.C++ >& Output/Log/bkgEstimate_ZtoNuNu.log

# Create pdfs of latex files
echo "Converting Tex to PDF..."
echo ""
cd Output/Tables/
for x in `/bin/ls *.tex`; do pdflatex $x >& pass1.log; pdflatex $x >& ../Log/pdf2tex_$x.log; rm *.aux; rm *.log; done
cd ../BkgEstimate/
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