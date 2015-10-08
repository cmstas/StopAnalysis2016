
void mergeHadoopFiles(const TString& indir, const TString& outpath) {
  gSystem->Load("../libMiniFWLite.so");
  TChain *chain = new TChain("t");
  chain->SetMaxTreeSize(5000000000LL); //default is 100000000000LL

  std::cout << "Merging files from dir: " << indir << std::endl
	    << "Ouputting to: " << outpath << std::endl;

  chain->Add(indir + "/*.root");
  chain->Merge(outpath, "fast");
}
