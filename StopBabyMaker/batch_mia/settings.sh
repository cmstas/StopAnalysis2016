#! /bin/bash

export analysis_version="V08-00-01"
echo "Analysis version = $analysis_version"
localdirectory=`pwd`

BABYMAKER_DIR_NAME=$PWD/../
CORE_DIR=$HOME/CORE

CONDOR_DIR_NAME=forCondor_stopBabyMaker
START_DIR=`pwd`
TAG=${analysis_version}

export HADOOPDIR=/hadoop/cms/store/user/mliu/onelepbabies/
export OUTPUTDIR=/nfs-6/userdata/mliu/onelepbabies/$TAG # where do you want to put your merged files?

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






function link_output
{
	if [ ! -L "$localdirectory/output" ]; then
		echo "Linking to output directory: /nfs-7/userdata/mliu/output"
		ln -s /nfs-7/userdata/mliu/output
	else
		echo "Saving output to: /nfs-7/userdata/mliu/output"
	fi
}

function create_photon_output
{
	if [ ! -d $localdirectory/output/photon/$analysis_version ]; then
		echo "Creating directory, $localdirectory/output/photon/$analysis_version"
		mkdir -p $localdirectory/output/photon/$analysis_version
		sleep 1
	else
		echo "Saving photon output to $localdirectory/output/photon/$analysis_version"
		sleep 1
	fi
}

function create_analysis_output
{
	if [ ! -d $localdirectory/output/$analysis_version ]; then
		echo "Creating directory, $localdirectory/output/$analysis_version"
		mkdir $localdirectory/output/$analysis_version
		sleep 1
	else
		echo "Saving looper output to $localdirectory/output/$analysis_version"
		sleep 1
	fi
}

function create_plot_output
{
	if [ ! -d output/ZMET2015/$analysis_version/plots/Closure ]; then
		echo "Creating directory, output/ZMET2015/$analysis_version/plots/Closure"
		mkdir -p output/ZMET2015/$analysis_version/plots/Closure
		sleep 1
	else
		echo "Saving plots to output/ZMET2015/$analysis_version/plots/Closure"
		sleep 1
	fi

	if [ ! -e output/ZMET2015/$analysis_version/plots/Closure/index.php ]; then
		cp index.php output/ZMET2015/$analysis_version/plots/Closure/
	fi
}

function compile_looper
{
	echo "Compiling code."
	make -j5
	if [ ! "$?" -eq "0" ]; then
		echo "Code did not compile, exiting."
		exit
	fi
}

function make_gtemplates
{
	selection_region=$1
	iteration=$analysis_version
	sample=$2
	echo "running templateLooper."
	root -b -q "runPhotonTemplates.cc( \"$selection_region\", \"$iteration\", \"$sample\")"
}

function run_template_looper
{
	selection_region=$1
    iteration=$analysis_version
    sample_region=$2
	echo "running templateLooper."
	root -b -q "runTemplateLooper.cc( \"$selection_region\", \"$iteration\", \"$sample_region\")"
}


