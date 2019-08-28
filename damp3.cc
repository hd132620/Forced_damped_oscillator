#include "TStyle.h" // All T*h files are for ROOT
#include "TCanvas.h"
#include "TF2.h"
#include "TTimer.h"
#include "TMath.h"
#include "TAxis.h"
#include "TROOT.h"
#include "TSystem.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "TF1.h"
#include "TH1.h"
#include "TLatex.h"
#include "TGraph.h"
#include "./CRK4.hh" // my Class

void init(){ 
	gROOT->SetStyle("Plain");
	gStyle->SetTitleAlign(23);
	gStyle->SetTitleX(0.54);
	gStyle->SetTitleY(0.97);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetTitleColor(1);
	gStyle->SetLabelFont(132,"xy");
	gStyle->SetTitleFont(132,"xy");
	gStyle->SetTitleFont(132,"");
	gStyle->SetTextFont(132);
	gStyle->SetStatFont(132);
	gStyle->SetNdivisions(105,"xy");
	gStyle->SetLabelSize(0.055,"xy");
	gStyle->SetTitleSize(0.055,"xy");
	gStyle->SetTitleSize(0.06,"");
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadRightMargin(0.10);
	gStyle->SetPadLeftMargin(0.20);
	gStyle->SetPadBottomMargin(0.18);
}

int main(){
	init(); // Set ROOT display styles : Refer to void init()

	double Ti,Tf,X10,X20;
	int   Nt;
    double iomega0, iomega, igam;
    double ia0[7]={0.5, 1.0, 2.0, 4.0, 8.0, 16.0, 32.0};

	CRK4 rkta4;

    iomega0=1.0; iomega=2.0; igam=0.2;
	Ti=0.0; Tf=40; X10=1.0; X20 = 0.0, Nt = 1000;

    for(int i = 0; i < 7; i += 1)
    {
        rkta4.InitVal(iomega0, iomega, igam, ia0[i]);
        rkta4.RK(Ti,Tf,X10,X20,Nt);

        static const int Ndim=1000;
        double tt[Ndim], xx[Ndim], vv[Ndim], ee[Ndim];

        rkta4.getResult(tt, xx, vv, ee);

        TString filename;
        filename.Form("damp3_a0_%lf.pdf", ia0[i]);

        TCanvas *c1 = new TCanvas(filename.Data(), filename.Data(),1200,600);
        c1->Divide(2,1);
        c1->Print(filename + "[", "pdf");

        TGraph *gr1 = new TGraph(Ndim,tt,xx);
        TGraph *gr2 = new TGraph(Ndim,xx,vv);

        c1->cd(1);
        gr1->SetLineColor(2);
        gr1->GetXaxis()->SetLimits(0.,Tf);
        gr1->GetHistogram()->GetXaxis()->SetTitle("time");
        gr1->GetHistogram()->GetYaxis()->SetTitle("#theta(t)");
        gr1->Draw("ACP");

        c1->cd(2);
        gr2->SetLineColor(2);
        //gr2->GetXaxis()->SetLimits(4,10);
        gr2->GetHistogram()->GetXaxis()->SetTitle("#theta(t)");
        gr2->GetHistogram()->GetYaxis()->SetTitle("#omega(t)");
        gr2->Draw("ACP");

        c1->Print(filename, "pdf");
        c1->Print(filename + "]", "pdf");
    }
}

