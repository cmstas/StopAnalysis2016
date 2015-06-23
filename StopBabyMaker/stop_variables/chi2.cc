#include "chi2.h"

//--------------------------------------------------------------------
double fc2 (double c1, double m12, double m22, double m02, bool verbose)
{
  if (verbose) {
    printf("c1: %4.2f\n", c1);
    printf("m12: %4.2f\n", m12);
    printf("m22: %4.2f\n", m22);
    printf("m02: %4.2f\n", m02);
  }

  double a = m22;
  double b = (m02 - m12 - m22) * c1;
  double c = m12 * c1 * c1 - PDG_W_MASS * PDG_W_MASS;

  if (verbose) {
    printf("a: %4.2f\n", a);
    printf("b: %4.2f\n", b);
    printf("c: %4.2f\n", c);
  }

  double num = -1. * b + sqrt(b * b - 4 * a * c);
  double den = 2 * a;

  if (verbose) {
    printf("num: %4.2f\n", num);
    printf("den: %4.2f\n", den);
    printf("num/den: %4.2f\n", num/den);
  }

  return (num/den);
}

//--------------------------------------------------------------------
double fchi2 (double c1, double pt1, double sigma1, double pt2, double sigma2,
              double m12, double m22, double m02){
  double rat1 = pt1 * (1 - c1) / sigma1;
  double rat2 = pt2 * (1 - fc2(c1, m12, m22, m02)) / sigma2;

  return ( rat1 * rat1 + rat2 * rat2);
}

//--------------------------------------------------------------------
void minuitFunction(int&, double* , double &result, double par[], int){
  result=fchi2(par[0], par[1], par[2], par[3], par[4], par[5], par[6], par[7]);
}

// This function calculates the hadronic chi2 - SNT version
double calculateChi2(vector<LorentzVector>& jets, vector<float>& sigma_jets, vector<bool>& btag){

        cout.precision(11);
	assert(jets.size() == sigma_jets.size());
	assert(jets.size() == btag.size());

	//check at most first 6 jets
	int n_jets = jets.size();
	if (n_jets>6) n_jets = 6;
	//consider at least 3 jets
	if (n_jets<3) return 999999.;

	vector<int> v_i, v_j;
	vector<double> v_k1, v_k2;
	for ( int i=0; i<n_jets; ++i )
		for ( int j=i+1; j<n_jets; ++j ){

			//
			//  W
			//
			LorentzVector hadW = jets[i] + jets[j];

			//
			//  W Mass Constraint.
			//
			TFitter *minimizer = new TFitter();
			double p1 = -1;

			minimizer->ExecuteCommand("SET PRINTOUT", &p1, 1);
			minimizer->SetFCN(minuitFunction);
			minimizer->SetParameter(0 , "c1"     , 1.1             , 1 , 0 , 0);
			minimizer->SetParameter(1 , "pt1"    , 1.0             , 1 , 0 , 0);
			minimizer->SetParameter(2 , "sigma1" , sigma_jets[i]   , 1 , 0 , 0);
			minimizer->SetParameter(3 , "pt2"    , 1.0             , 1 , 0 , 0);
			minimizer->SetParameter(4 , "sigma2" , sigma_jets[j]   , 1 , 0 , 0);
			minimizer->SetParameter(5 , "m12"    , jets[i].mass2() , 1 , 0 , 0);
			minimizer->SetParameter(6 , "m22"    , jets[j].mass2() , 1 , 0 , 0);
			minimizer->SetParameter(7 , "m02"    , hadW.mass2()    , 1 , 0 , 0);

			for (unsigned int k = 1; k < 8; k++)
				minimizer->FixParameter(k);

			minimizer->ExecuteCommand("SIMPLEX", 0, 0);
			minimizer->ExecuteCommand("MIGRAD", 0, 0);

			double c1 = minimizer->GetParameter(0);
			if (c1!=c1) {
				cout<<"[PartonCombinatorics::recoHadronicTop] ERROR: c1 parameter is NAN! Skipping this parton combination"
					<<endl;
				continue;
			}
			double c2 = fc2(c1, jets[i].mass2(), jets[j].mass2(), hadW.mass2());

			delete minimizer;


			//     * W Mass check :)
			//     *  Never trust a computer you can't throw out a window.
			//      *  - Steve Wozniak

			// cout << "c1 = " <<  c1 << "  c1 = " << c2 << "   M_jj = "
			// 	   << ((jets[i] * c1) + (jets[j] * c2)).mass() << endl;

			v_i.push_back(i);
			v_j.push_back(j);
			v_k1.push_back(c1);
			v_k2.push_back(c2);
		}

	//Apply b-consistency requirement
	int n_btag = 0;
	for( int i = 0 ; i < n_jets ; i++ )
		if( btag.at(i) ) n_btag++;

	double chi2min = 99999.;

	//consider b-jet in leading 3 jets
	for ( int b=0; b<n_jets; ++b ) {    

		//if not tagged, consider only 3 leading jets
		if( (!btag.at(b)) && b>2 ) continue;

		//require b-tagging if have more than 1 b-tag
		if( n_btag>1 && (!btag.at(b)) ) continue;
		double pt_b = jets[b].Pt();

		for (unsigned int w = 0; w < v_i.size() ; ++w ) {
			int i = v_i[w];
			int j = v_j[w];
			if ( i==b || j==b ) continue;
			//count number of b-tagged Ws
			int nwb = 0;
			if (btag.at(i)) nwb++;
			if (btag.at(j)) nwb++;
			//no btagged jets in W if have few btags
			if ( n_btag<3  && nwb>0 ) continue;
			//In 3 b-tag case, allow for 1 W jet to be tagged
			// If have more b-tags then btagging information not useful
			if ( n_btag==3 && nwb>1 ) continue;

			double pt_w1 = jets[i].Pt();
			double pt_w2 = jets[j].Pt();

			///
			//  W Mass.
			///
			LorentzVector hadW = jets[i] + jets[j];
			double massW = hadW.mass();

			double c1 = v_k1[w];
			double c2 = v_k2[w];

			///
			// Top Mass.
			///
			LorentzVector hadT = (jets[i] * c1) + (jets[j] * c2) + jets[b];
			double massT = hadT.mass();

			double pt_w = hadW.Pt();
			double sigma_w2 = pow(pt_w1*sigma_jets[i], 2)
				+ pow(pt_w2*sigma_jets[j], 2);
			double smw2 = (1. + 2.*pow(pt_w,2)/pow(massW,2))*sigma_w2;
			double pt_t = hadT.Pt();
			double sigma_t2 = pow(c1*pt_w1*sigma_jets[i],2)
				+ pow(c2*pt_w2*sigma_jets[j],2)
				+ pow(pt_b*sigma_jets[b],2);
			double smtop2 = (1. + 2.*pow(pt_t,2)/pow(massT,2))*sigma_t2;

			double c_chi2 = pow(massT-PDG_TOP_MASS, 2)/smtop2
				+ pow(massW-PDG_W_MASS, 2)/smw2;
			if (c_chi2<chi2min) chi2min = c_chi2;
			//cout << "chi2 " << c_chi2 << " with Wjet1 " << jets[i].Pt() << " Wjet2 " << jets[j].Pt() << " c1 " << c1 << " c2 " << c2
			//     << " TopB " << jets[b].Pt() << endl << "      sigma_w2 " << sigma_w2 << " sigma_t2 " << sigma_t2 << " smw2 " << smw2 << " smtop2 " << smtop2 << endl; 

		}
	}

	return chi2min;
}

