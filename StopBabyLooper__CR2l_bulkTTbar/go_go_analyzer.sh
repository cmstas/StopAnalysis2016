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

# Compiling Looper Code
make clean
make

# Running Analyzer
./runBabyLooper__CR2l_bulkTTbar

# If necessary, calculate pileup weights
#echo "Calculating Pileup Weights..."
#echo ""
#root -l -b -q getPileupWeights.C++ >& Output/Log/getPielupWeights.log 

# Create pdfs of latex files
echo "Converting Tex to PDF..."
echo ""
cd Output/Tables/
for x in `/bin/ls *.tex`; do echo $x; pdflatex -interaction=nonstopmode $x >& pass1.log; pdflatex -interaction=nonstopmode $x >& ../Log/pdf2tex_$x.log; rm *.aux; rm *.log; done
cd ../../

# Clean up 
echo "Cleaning Up..."
echo ""
make clean

# Done!
echo ""
echo "----------------------------------"
echo " Analysis Results Written To: "
echo "   Output/ " 
echo "---------------------------------"
