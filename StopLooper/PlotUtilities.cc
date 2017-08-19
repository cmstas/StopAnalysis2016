#include "PlotUtilities.h"

#include "TROOT.h"
#include "TFile.h"
#include "TList.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TH2.h"
#include "TKey.h"
#include "TRegexp.h"
#include <TIterator.h>
#include "TClass.h"
#include "TLegend.h"

#include "RooRealVar.h"
#include "RooDataSet.h"

#include <iostream>
#include <cmath>

H cumulate (const H &in, bool increasing)
{
    H h_out(in.GetName() + TString("tmp"), in.GetTitle(), in.GetNbinsX(),
            in.GetBinLowEdge(1), in.GetBinLowEdge(in.GetNbinsX() + 1));
    h_out.Sumw2();
    h_out.SetFillColor(in.GetFillColor());
    h_out.SetFillStyle(in.GetFillStyle());
    h_out.SetLineStyle(in.GetLineStyle());
    h_out.SetLineColor(in.GetLineColor());
    h_out.SetLineWidth(in.GetLineWidth());
    double sum = 0;
    double err2 = 0;
    if (increasing) {
        for (int j = 0; j <= in.GetNbinsX() + 1; ++j) {
            sum += in.GetBinContent(j);
            err2 += in.GetBinError(j)*in.GetBinError(j);
            h_out.SetBinContent(j, sum);
            h_out.SetBinError(j, sqrt(err2));
        }
    } else {
        for (int j = in.GetNbinsX() + 1; j >= 0; --j) {
            sum += in.GetBinContent(j);
            err2 += in.GetBinError(j)*in.GetBinError(j);
            h_out.SetBinContent(j, sum);
            h_out.SetBinError(j, sqrt(err2));
        }
    }
    return h_out;
}

TGraph eff_rej (const H &signal, H &background, bool normalize, bool increasing)
{
    H sig = *(TH1D*)signal.Clone("h_tmp_s");
    if (normalize)
        sig.Scale(1 / sig.Integral(0, sig.GetNbinsX() + 1));
    H bg = *(TH1D*)background.Clone("h_tmp_bg");
    if (normalize)
        bg.Scale(1 / bg.Integral(0, bg.GetNbinsX() + 1));
    H sig_cum = cumulate(sig, increasing);
    H bg_cum = cumulate(bg, increasing);
    TGraph ret(signal.GetNbinsX());
    for (int i = 1; i <= signal.GetNbinsX(); ++i) {
        const double x = sig_cum.GetBinCenter(i);
        const double s = sig_cum.GetBinContent(i);
        const double b = bg_cum.GetBinContent(bg_cum.FindBin(x));
        ret.SetPoint(i - 1, b, s); // gotta love offsets
        //        printf("point %d: %f s, %f b\n", i, s, b);
    }
    return ret;
}

void deleteHistos() {
    // Delete all existing histograms in memory
    TObject* obj;
    TList* list = gDirectory->GetList() ;
    TIterator* iter = list->MakeIterator();
    while ( (obj = (iter->Next())) ) {
        if (obj->IsA()->InheritsFrom(TH1::Class()) ||
                obj->IsA()->InheritsFrom(TH2::Class()) ) {
                delete obj;
            }
    }
}

void saveHist(const char* filename, const char* pat)
{

    TList* list = gDirectory->GetList() ;
    TIterator* iter = list->MakeIterator();
    TRegexp re(pat,kTRUE) ;

    TFile outf(filename,"RECREATE") ;
    printf("[PlotUtilities::saveHist] Saving histograms to %s\n", filename);

    int counter = 0;
    while(TObject* obj=iter->Next()) {

        // don't save TH1Keys objects
        // this is a bug fudge
        if (TString(obj->GetName()).Contains("histokeys")) continue;

        // save other stuff
        if (TString(obj->GetName()).Index(re)>=0) {
            obj->Write() ;
            ++counter;
        }

    }

    printf("[PlotUtilities::saveHist] Saved %i histograms\n", counter);
    outf.Close() ;
    delete iter ;
}

TCanvas *ComparePlots(TFile *f, const char *hist1, const char *hist2, const char *label1, const char *label2, unsigned int rebin, bool norm, bool log, unsigned int opt)
{

    // get hists
    TH1D *h1 = (TH1D*)f->Get(hist1)->Clone(hist1);
    TH1D *h2 = (TH1D*)f->Get(hist2)->Clone(hist2);

    // overflow
    h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX()) + h1->GetBinContent(h1->GetNbinsX()+1));
    h1->SetBinContent(h1->GetNbinsX()+1, 0.0);
    h2->SetBinContent(h2->GetNbinsX(), h2->GetBinContent(h2->GetNbinsX()) + h2->GetBinContent(h2->GetNbinsX()+1));
    h2->SetBinContent(h2->GetNbinsX()+1, 0.0);

    // rebin
    h1->Rebin(rebin);
    h2->Rebin(rebin);

    // normalize
    if (norm) h1->Scale(h2->Integral(0, h2->GetNbinsX() + 1) / h1->Integral(0, h1->GetNbinsX() + 1));

    // format
    if (opt == 1) {
        h1->SetLineWidth(2);
        h1->SetLineColor(kRed);
        h2->SetLineColor(kBlue);
        h2->SetFillColor(kBlue);
        h2->SetFillStyle(0);
        h2->SetLineWidth(2);
        h2->SetMarkerStyle(20);
        h2->SetMarkerColor(kBlue);
    } 
    if (opt == 2) {
        h1->SetLineWidth(2);
        h1->SetLineColor(kRed);
        h1->SetFillColor(kRed);
        h1->SetFillStyle(3004);
        h2->SetFillStyle(0);
        h2->SetLineWidth(2);
        h2->SetMarkerStyle(20);
        h2->SetMarkerColor(kBlack);
        h2->SetLineColor(kBlack);
    }

    // legend
    TLegend *l1 = new TLegend(0.70, 0.85, 0.98, 0.98);
    l1->SetLineColor(kWhite);
    l1->SetFillColor(kWhite);
    l1->SetShadowColor(kWhite);
    l1->AddEntry(h1, label1, "f");
    l1->AddEntry(h2, label2, "f");

    // draw
    TCanvas *c1 = new TCanvas();
    if (log) c1->SetLogy();
    c1->cd();
    h1->Draw("HIST");
    h2->Draw("SAME E1");
    double yMax = TMath::Max(h1->GetMaximum(), h2->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0.0, TMath::Max(yMax + 2*sqrt(yMax), yMax + 0.3*yMax));
    if (log) h1->GetYaxis()->SetRangeUser(0.1, yMax * 1000);
    l1->Draw();

    return c1;

}

TGraph GetROC(TFile *f, const char *hist1, const char *hist2, bool increasing)
{

    // get hists
    TH1D *sig = (TH1D*)f->Get(hist1)->Clone(hist1);
    TH1D *bkg = (TH1D*)f->Get(hist2)->Clone(hist2);
    
    // overflow
    sig->SetBinContent(sig->GetNbinsX(), sig->GetBinContent(sig->GetNbinsX()) + sig->GetBinContent(sig->GetNbinsX()+1));
    sig->SetBinContent(sig->GetNbinsX()+1, 0.0);
    bkg->SetBinContent(bkg->GetNbinsX(), bkg->GetBinContent(bkg->GetNbinsX()) + bkg->GetBinContent(bkg->GetNbinsX()+1));
    bkg->SetBinContent(bkg->GetNbinsX()+1, 0.0);

    TGraph gr_roc = eff_rej(*sig, *bkg, true, increasing);
    return gr_roc;
}


TGraph GetEff(TFile *f, const char *hist1, bool increasing)
{

    // get hists
    TH1D *sig = (TH1D*)f->Get(hist1)->Clone(hist1);

    // overflow
    sig->SetBinContent(sig->GetNbinsX(), sig->GetBinContent(sig->GetNbinsX()) + sig->GetBinContent(sig->GetNbinsX()+1));
    sig->SetBinContent(sig->GetNbinsX()+1, 0.0);

    TGraph ret(sig->GetNbinsX());
    for (int i = 1; i <= sig->GetNbinsX(); ++i) {
        float val = sig->GetBinLowEdge(i);
        float ntotal = sig->Integral(1, sig->GetNbinsX());
        float npass = sig->Integral(i, sig->GetNbinsX());
        if (increasing) npass = ntotal - npass;
        ret.SetPoint(i - 1, val, npass/ntotal);
    }

    return ret;
}


void plotRooDataSet(string name, RooRealVar* x_, RooRealVar* w_, double weight, std::map<string, RooDataSet*> &allRooDatasets, string title)
{
  if (title=="") title=name; 
  std::map<string, RooDataSet*>::iterator iter= allRooDatasets.find(name);
  if(iter == allRooDatasets.end()) //no RooDataSet for this yet, so make a new one
    {
      RooDataSet* currentDataset= new RooDataSet(name.c_str(), title.c_str(), RooArgSet(*x_,*w_), w_->GetName() );
      currentDataset->add( RooArgList(*x_, *w_), weight );
      allRooDatasets.insert(std::pair<string, RooDataSet*> (name,currentDataset) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->add( RooArgList(*x_, *w_), weight );
    }
}

void plot1D(string name, float xval, double weight, std::map<string, TH1*> &allhistos, 
	    string title, int numbinsx, float xmin, float xmax)  
{
  if (title=="") title=name; 
  std::map<string, TH1*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH1D* currentHisto= new TH1D(name.c_str(), title.c_str(), numbinsx, xmin, xmax);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, weight);
      allhistos.insert(std::pair<string, TH1D*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, weight);
    }
  
}

void plot1D(string name, float xval, double weight, std::map<string, TH1*> &allhistos, 
	    string title, int numbinsx, const float * xbins)  
{
  if (title=="") title=name; 
  std::map<string, TH1*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH1D* currentHisto= new TH1D(name.c_str(), title.c_str(), numbinsx, xbins);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, weight);
      allhistos.insert(std::pair<string, TH1D*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, weight);
    }
  
}

void plot1DUnderOverFlow(string title, double xval, double weight, std::map<string, TH1*> &allhistos, 
      int numbinsx, double xmin, double xmax)  
{
  if (xval >= xmax) xval = xmax - (xmax-xmin)/double(numbinsx)/1000.;
  if (xval <= xmin) xval = xmin + (xmax-xmin)/double(numbinsx)/1000.;

  std::map<string, TH1*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH1D* currentHisto= new TH1D(title.c_str(), title.c_str(), numbinsx, xmin, xmax);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, weight);
      allhistos.insert(std::pair<string, TH1D*> (title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, weight);
    }
  
}

TH1D* getHist1D(string title, std::map<string, TH1*> &allhistos, 
	    int numbinsx, float xmin, float xmax)  
{

  TH1D* currentHisto = 0;

  std::map<string, TH1*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      currentHisto= new TH1D(title.c_str(), title.c_str(), numbinsx, xmin, xmax);
      currentHisto->Sumw2();
      allhistos.insert(std::pair<string, TH1D*> (title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      currentHisto = (TH1D*) (*iter).second;
    }
  
  return currentHisto;
}

TH2D* getHist2D(string title, std::map<string, TH1*> &allhistos, 
		int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax)  
{

  TH2D* currentHisto = 0;

  std::map<string, TH1*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      currentHisto= new TH2D(title.c_str(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax);
      currentHisto->Sumw2();
      allhistos.insert(std::pair<string, TH2D*> (title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      currentHisto = (TH2D*) (*iter).second;
    }
  
  return currentHisto;
}

void insertHist1D(TH1D* hist, std::map<string, TH1*> &allhistos)
{

  string title(hist->GetName());

  std::map<string, TH1*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, insert into map
    {
      allhistos.insert(std::pair<string, TH1D*> (title,hist) );
    }
  else // exists already, give warning and overwrite
    {
      printf("[PlotUtilities::insertHist1D] WARNING: overwriting histogram %s\n", title.c_str());
      (*iter).second = hist;
    }
  
  return;
}

void insertHist2D(TH2D* hist, std::map<string, TH1*> &allhistos)
{

  string title(hist->GetName());

  std::map<string, TH1*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, insert into map
    {
      allhistos.insert(std::pair<string, TH2D*> (title,hist) );
    }
  else // exists already, give warning and overwrite
    {
      printf("[PlotUtilities::insertHist2D] WARNING: overwriting histogram %s\n", title.c_str());
      (*iter).second = hist;
    }
  
  return;
}

void savePlots(std::map<string, TH1*> &h_1d, const char* outfilename){
  TFile outfile(outfilename,"RECREATE") ;

  printf("[PlotUtilities::savePlots] Saving histograms to %s\n", outfilename);

  std::map<std::string, TH1*>::iterator it1d;
  for(it1d=h_1d.begin(); it1d!=h_1d.end(); it1d++) {
    it1d->second->Write();
    delete it1d->second;
  }

  outfile.Write();
  outfile.Close();
}

void savePlots2(std::map<string, TH2D*> &h_1d, const char* outfilename){
  TFile outfile(outfilename,"RECREATE") ;

  printf("[PlotUtilities::savePlots] Saving histograms to %s\n", outfilename);

  std::map<std::string, TH2D*>::iterator it1d;
  for(it1d=h_1d.begin(); it1d!=h_1d.end(); it1d++) {
    it1d->second->Write();
    delete it1d->second;
  }

  outfile.Write();
  outfile.Close();
}

void saveRooDataSetsDir(std::map<string, RooDataSet*>& datasets, TFile* outfile, const char* dirname){

  printf("[PlotUtilities::saveRooDataSets] Saving RooDataSets to dir: %s\n", dirname);

  TDirectory* dir = 0;

  // base dir: just cd to output file
  if (strcmp(dirname,"") == 0) {
    outfile->cd();
  } else {
    // first check for directory, create if it doesn't exist
    dir = (TDirectory*)outfile->Get(dirname);
    if (dir == 0) {
      dir = outfile->mkdir(dirname);
    } 
    dir->cd();
  }

  std::map<std::string, RooDataSet*>::iterator iter;
  for(iter=datasets.begin(); iter!=datasets.end(); iter++) {
    iter->second->Write();
    delete iter->second;
  }

}

void savePlotsDir(std::map<string, TH1*> &h_1d, TFile* outfile, const char* dirname){

  printf("[PlotUtilities::savePlots] Saving 1d histograms to dir: %s\n", dirname);

  TDirectory* dir = 0;

  // base dir: just cd to output file
  if (strcmp(dirname,"") == 0) {
    outfile->cd();
  } else {
    // first check for directory, create if it doesn't exist
    dir = (TDirectory*)outfile->Get(dirname);
    if (dir == 0) {
      dir = outfile->mkdir(dirname);
    } 
    dir->cd();
  }

  std::map<std::string, TH1*>::iterator it1d;
  for(it1d=h_1d.begin(); it1d!=h_1d.end(); it1d++) {
    it1d->second->Write();
    delete it1d->second;
  }

}

void savePlots2Dir(std::map<string, TH2D*> &h_2d, TFile* outfile, const char* dirname){

  printf("[PlotUtilities::savePlots2Dir] Saving 2d histograms to dir: %s\n", dirname);

  TDirectory* dir = 0;

  // base dir: just cd to output file
  if (strcmp(dirname,"") == 0) {
    outfile->cd();
  } else {
    // first check for directory, create if it doesn't exist
    dir = (TDirectory*)outfile->Get(dirname);
    if (dir == 0) {
      dir = outfile->mkdir(dirname);
    } 
    dir->cd();
  }

  std::map<std::string, TH2D*>::iterator it2d;
  for(it2d=h_2d.begin(); it2d!=h_2d.end(); it2d++) {
    it2d->second->Write();
    delete it2d->second;
  }

}

void savePlots12(std::map<string, TH1D*> &h_1d, std::map<string, TH2D*> &h_2d, const char* outfilename){
  TFile outfile(outfilename,"RECREATE") ;

  printf("[PlotUtilities::savePlots12] Saving histograms to %s\n", outfilename);

  std::map<std::string, TH1D*>::iterator it1d;
  for(it1d=h_1d.begin(); it1d!=h_1d.end(); it1d++) {
    it1d->second->Write();
    delete it1d->second;
  }

  std::map<std::string, TH2D*>::iterator it2d;
  for(it2d=h_2d.begin(); it2d!=h_2d.end(); it2d++) {
    it2d->second->Write();
    delete it2d->second;
  }

  outfile.Write();
  outfile.Close();
}


void plot2D(string name, float xval, float yval, double weight, std::map<string, TH1*> &allhistos, 
	    string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax){

  if (title=="") title=name; 
  std::map<string, TH1*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<string, TH1*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      ((TH2D*) (*iter).second)->Fill(xval, yval, weight);
    }

  return;

}

void plot2D(string name, float xval, float yval, double weight, std::map<string, TH1*> &allhistos, 
	    string title, int numbinsx, const float * xbins, int numbinsy, const float * ybins){

  if (title=="") title=name; 
  std::map<string, TH1*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xbins, numbinsy, ybins);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<string, TH1*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      ((TH2D*) (*iter).second)->Fill(xval, yval, weight);
    }

  return;

}
void plot2D(string name, float xval, float yval, double weight, std::map<string, TH2D*> &allhistos, 
	    string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax){

  if (title=="") title=name; 
  std::map<string, TH2D*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<string, TH2D*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, yval, weight);
    }

  return;

}

void plot2D(string name, float xval, float yval, double weight, std::map<string, TH2D*> &allhistos, 
	    string title, int numbinsx, const float * xbins, int numbinsy, const float * ybins){

  if (title=="") title=name; 
  std::map<string, TH2D*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xbins, numbinsy, ybins);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<string, TH2D*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, yval, weight);
    }

  return;

}

void plot2DUnderOverFlow(string name, double xval, double yval, double weight, std::map<string, TH1*> &allhistos, 
      string title, int numbinsx, double xmin, double xmax, int numbinsy, double ymin, double ymax){

  if (title=="") title=name; 

  if (xval >= xmax) xval = xmax - (xmax-xmin)/double(numbinsx)/1000.;
  if (xval <= xmin) xval = xmin + (xmax-xmin)/double(numbinsx)/1000.;
  if (yval >= ymax) yval = ymax - (ymax-ymin)/double(numbinsy)/1000.;
  if (yval <= ymin) yval = ymin + (ymax-ymin)/double(numbinsy)/1000.;
 
  std::map<string, TH1*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH2D* currentHisto= new TH2D(title.c_str(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<string, TH1*> (title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      ((TH2D*) (*iter).second)->Fill(xval, yval, weight);
    }

  return;

}

void plot3D(string name, float xval, float yval, float zval, double weight, std::map<string, TH1*> &allhistos, 
	    string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax,
	    int numbinsz, float zmin, float zmax){

  if (title=="") title=name; 
  std::map<string, TH1*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH3D* currentHisto= new TH3D(name.c_str(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax, numbinsz, zmin, zmax);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, zval, weight);
      allhistos.insert(std::pair<string, TH1*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      ((TH3D*) (*iter).second)->Fill(xval, yval, zval, weight);
    }

  return;

}

void plot3D(string name, float xval, float yval, float zval, double weight, std::map<string, TH1*> &allhistos, 
	    string title, int numbinsx, const float * xbins, int numbinsy, const float * ybins, int numbinsz, const float * zbins){

  if (title=="") title=name; 
  std::map<string, TH1*>::iterator iter= allhistos.find(name);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH3D* currentHisto= new TH3D(name.c_str(), title.c_str(), numbinsx, xbins, numbinsy, ybins, numbinsz, zbins);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, zval, weight);
      allhistos.insert(std::pair<string, TH1*> (name,currentHisto) );
    }
  else // exists already, so just fill it
    {
      ((TH3D*) (*iter).second)->Fill(xval, yval, zval, weight);
    }

  return;

}
