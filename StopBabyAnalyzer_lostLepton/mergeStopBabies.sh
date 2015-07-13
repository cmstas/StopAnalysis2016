#! /bin/sh

BASE_DIR=./Histos

# Merge Rare decay samples
hadd -f $BASE_DIR/histos__rare.root $BASE_DIR/histos__ttwjets.root $BASE_DIR/histos__ttzjets.root $BASE_DIR/histos__wzjets.root $BASE_DIR/histos__zz.root

hadd -f $BASE_DIR/histos__singleT.root $BASE_DIR/histos__t_sch.root  $BASE_DIR/histos__t_tch.root $BASE_DIR/histos__t_tW.root $BASE_DIR/histos__tbar_sch.root $BASE_DIR/histos__tbar_tch.root $BASE_DIR/histos__tbar_tW.root
