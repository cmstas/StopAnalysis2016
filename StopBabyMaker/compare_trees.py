#!/usr/bin/env python

import ROOT as r
import root_utils
import sys
import os

r.gROOT.SetBatch(1)

# treename = "Events"
# fname1 = "slim.root"
# fname2 = "orig.root"
# plotdir = "plots/"
# verbose = False

treename = "t"
#fname1 = "output_tt_new.root"
#fname2 = "output_tt_orig.root"
fname1 = "ttbar_CMS4_test_NEW.root"
fname2 = "ttbar_CMS4_test_OLD.root"
plotdir = "plots_baby/"
verbose = False

os.system("mkdir -p {0}".format(plotdir))

f1 = r.TFile(fname1)
f2 = r.TFile(fname2)

t1 = f1.Get(treename)
t2 = f2.Get(treename)

print t1, t2

info1 = root_utils.get_branch_info(t1)
info2 = root_utils.get_branch_info(t2)

keys_1_not_2 = set(info1.keys()) - set(info2.keys())
keys_2_not_1 = set(info2.keys()) - set(info1.keys())
keys_both = set(info1.keys()) - keys_1_not_2

print "Number of branches only in file 1:", len(keys_1_not_2)
if verbose: print "\t"+"\n\t".join(sorted(map(lambda x: info1[x].get("alias",x), keys_1_not_2)))
print "Number of branches only in file 2:", len(keys_2_not_1)
if verbose: print "\t"+"\n\t".join(sorted(map(lambda x: info2[x].get("alias",x), keys_2_not_1)))
print "Number of branches common to both:", len(keys_both)
if verbose: print "\t"+"\n\t".join(sorted(map(lambda x: info1[x].get("alias",x), keys_both)))

max_nevts = 1000
c1 = r.TCanvas("c1")
# for b in list(keys_both)[:10]:
for b in list(keys_both):
# for b in list(keys_both)[:1]:
    try:
        i1 = info1[b]
        i2 = info2[b]
        is_p4 = "LorentzVector" in i1.get("type","")
        alias = i1["alias"]

        todraw = alias + (".pt()" if is_p4 else "")
        t1.Draw("{0}>>h1_{1}".format(todraw,alias),"","goff",max_nevts)
        h1 = r.gDirectory.Get("h1_{0}".format(alias))

        h2 = h1.Clone("h2_{0}".format(alias))
        h2.Reset()

        t2.Draw("{0}>>h2_{1}".format(todraw,alias),"","goff",max_nevts)

        # print h1.GetEntries(), h2.GetEntries(), h1.GetMean(), h2.GetMean()

        h1.SetLineColor(r.kRed)
        h2.SetLineColor(r.kBlue)

        pchi = h1.Chi2Test(h2)
        print pchi, alias

        pchistr = ("%.2f" % (pchi)).replace(".","p")

        h1.SetTitle(h1.GetTitle() + (" #color[2]{[file 1]} #color[4]{[file 2]} -- p_{#chi} = %.2f" % pchi))


        h1.Draw("hist")
        h2.Draw("samepe")

        c1.SaveAs("{0}/h_{1}_{2}.png".format(plotdir,pchistr,alias))
    except:
        pass

    # print h1.GetEntries()
    # print h1.GetNbinsX()
    # print h1.GetXaxis().GetBinLowEdge(1)
    # print h1.GetXaxis().GetBinHighEdge(h1.GetNbinsX())



# print keys_1_not_2
# for 

# for b in info2:
#     print b, info2[b]

# def get_branch_info(tree):
#     """
#     Returns dictionary where keys are the branch names in the ttree and values are dictionaries
#     with the type, class, and alias
#     """

# def get_treename_from_file(tfile):
#     """
#     Given a tfile, this returns the name of the (only) ttree in the file, or
#     "Events" in the case of MINIAOD
#     """
#     keys = tfile.GetListOfKeys()
#     treenames = [key.GetName() for key in keys if key.ReadObj().InheritsFrom(TTree.Class())]
#     if len(treenames) > 0 and "Events" in treenames: treename = "Events"
#     else: treename = treenames[0]
#     return treename

