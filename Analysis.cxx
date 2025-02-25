#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TString.h"
#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>

void Analize(int genLoops = 1e5) {


       std::cout<<"\n";
       TFile *file = new TFile("analysis.root", "UPDATE");

       // resuming histograms from ROOT file
       TH1F *hPTypes = (TH1F *)file->Get("hPTypes");
       TH1F *hTheta = (TH1F *)file->Get("hTheta");
       TH1F *hPhi = (TH1F *)file->Get("hPhi");
       TH1F *hImpulse = (TH1F *)file->Get("hImpulse");
       TH1F *hTImpulse = (TH1F *)file->Get("hTImpulse");
       TH1F *hEnergy = (TH1F *)file->Get("hEnergy");
       TH1F *hInvMass = (TH1F *)file->Get("hInvMass");
       TH1F *hSameCharge = (TH1F *)file->Get("hSameCharge");
       TH1F *hOddCharge = (TH1F *)file->Get("hOddCharge");
       TH1F *hPKconcordant = (TH1F *)file->Get("hPKconcordant");
       TH1F *hPKdiscordant = (TH1F *)file->Get("hPKdiscordant");
       TH1F *hKDecay = (TH1F *)file->Get("hKDecay");
       TH1F *hDiff1 = (TH1F *)file->Get("hDiff1");
       TH1F *hDiff2 = (TH1F *)file->Get("hDiff2");

       hKDecay->Sumw2();

       /////////////////////////////////////////////////////
       // Analizing particle types histograms
       std::cout << "Particle Types distribution stats:\n";
       for (int i = 1; i < 8; i++)
       {
       std::cout << "Bin " << i << " Entries fraction = " << hPTypes->GetBinContent(i) / (genLoops * 100) << " ± "
                 << hPTypes->GetBinError(i) / (genLoops * 100) << "\n";
       }

       std::cout<<"\n";


       /////////////////////////////////////////////////////
       // analizing angles distributions
       std::cout << "Polar angle uniform distribution fit: \n";
       hTheta->Fit("pol0", "Q"); // uniform distribution fit
       hTheta->GetFunction("pol0")->SetLineColor(kRed);
       gStyle->SetOptStat(1111);
       gStyle->SetOptFit(111);
       hTheta->GetFunction("pol0")->Draw("SAME");
       std::cout << "Chi Square = " << hTheta->GetFunction("pol0")->GetChisquare() << "\n";
       std::cout << "NDF = " << hTheta->GetFunction("pol0")->GetNDF() << "\n";
       std::cout << "Reduced Chi Square = "<< hTheta->GetFunction("pol0")->GetChisquare() / hTheta->GetFunction("pol0")->GetNDF()<< "\n\n";


       ////////////////////////////////////////////////////////

       std::cout << "Azimuthal angle uniform distribution fit: \n";
       hPhi->Fit("pol0", "Q"); // uniform distribution fit
       gStyle->SetOptStat(1111);
       gStyle->SetOptFit(111);
       hPhi->GetFunction("pol0")->SetLineColor(kRed);
       std::cout << "Chi Square = " << hPhi->GetFunction("pol0")->GetChisquare()<< "\n";
       std::cout << "NDF = " << hPhi->GetFunction("pol0")->GetNDF() << "\n";
       std::cout << "Reduced Chi Square = "<< hPhi->GetFunction("pol0")->GetChisquare() / hPhi->GetFunction("pol0")->GetNDF() << "\n\n";

       //////////////////////////////////////////////////////////
       // analizing Impulse distribution

       std::cout << "Impulse exponential fit: \n";
       hImpulse->Fit("expo", "Q"); // exponential dist. fit
       gStyle->SetOptStat(1111);
       gStyle->SetOptFit(111);
       hImpulse->GetFunction("expo")->SetLineColor(kRed);
       std::cout << "Chi Square = " << hImpulse->GetFunction("expo")->GetChisquare() << "\n";
       std::cout << "NDF = " << hImpulse->GetFunction("expo")->GetNDF() << "\n";
       std::cout << "Reduced Chi Square = "<< hImpulse->GetFunction("expo")->GetChisquare() / hImpulse->GetFunction("expo")->GetNDF() << "\n";
       std::cout << "Mean = " << hImpulse->GetMean() << " ± " << hImpulse->GetMeanError() << "(GeV)\n";

       
       std::cout << "Decay of K* gaussian fit: \n";
       hKDecay->Fit("gaus", "", "", 0, 5);
       hKDecay->GetFunction("gaus")->SetLineColor(kRed);
       gStyle->SetOptStat(1111);
       gStyle->SetOptFit(111);
       std::cout << "Chi Square = " << hKDecay->GetFunction("gaus")->GetChisquare()<< "\n";
       std::cout << "NDF = " << hKDecay->GetFunction("gaus")->GetNDF() << "\n";
       std::cout << "Reduced Chi Square = " << hKDecay->GetFunction("gaus")->GetChisquare() / hKDecay->GetFunction("gaus")->GetNDF()<< "\n\n";


       std::cout << "Opposite and Same charge particles difference gaussian fit: \n";
       hDiff1->Fit("gaus", "", "", 0, 5);
       hDiff1->Fit("fit1");
       gStyle->SetOptStat(1111);
       gStyle->SetOptFit(111);

       std::cout << "Chi Square = " << hDiff1->GetFunction("gaus")->GetChisquare()
              << "\n";
       std::cout << "NDF = " << hDiff1->GetFunction("gaus")->GetNDF() << "\n";
       std::cout << "Reduced Chi Square = "
              << hDiff1->GetFunction("gaus")->GetChisquare() / hDiff1->GetFunction("gaus")->GetNDF()<< "\n\n";

       std::cout << "Opposite and Same charge Pions and Kaons difference gaussian fit: \n";
       hDiff2->Fit("gaus", "", "", 0, 5);
       hDiff2->GetFunction("gaus")->SetLineColor(kRed);
       gStyle->SetOptStat(1111);
       gStyle->SetOptFit(111);
       std::cout << "Chi Square = " << hDiff2->GetFunction("gaus")->GetChisquare()
              << "\n";
       std::cout << "NDF = " << hDiff2->GetFunction("gaus")->GetNDF() << "\n";
       std::cout << "Reduced Chi Square = "
              << hDiff2->GetFunction("gaus")->GetChisquare() / hDiff2->GetFunction("gaus")->GetNDF()<< "\n\n";


       // histograms cosmetics

       TCanvas *c1 = new TCanvas("c1", "Detector statistics");
       c1->Divide(2, 3);

       c1->cd(1);
       hPTypes->SetMinimum(0);
       hPTypes->SetFillColor(kBlue);
       hPTypes->GetXaxis()->SetTitle("Particle types");
       hPTypes->GetYaxis()->SetTitle("Number of occurrences");
       hPTypes->GetXaxis()->SetBinLabel(1, "Pions +");
       hPTypes->GetXaxis()->SetBinLabel(2, "Pions -");
       hPTypes->GetXaxis()->SetBinLabel(3, "Kaons +");
       hPTypes->GetXaxis()->SetBinLabel(4, "Kaons +");
       hPTypes->GetXaxis()->SetBinLabel(5, "Protons+");
       hPTypes->GetXaxis()->SetBinLabel(6, "Protons-");
       hPTypes->GetXaxis()->SetBinLabel(7, "K*");
       hPTypes->Draw("H");
       hPTypes->Draw("E,SAME");

       c1->cd(2);
       hTheta->SetFillColor(kBlue);
       hTheta->GetXaxis()->SetTitle("Theta (radiants)");
       hTheta->GetYaxis()->SetTitle("Number of occurrences");
       TLegend* Leg1 = new TLegend(.1,.7,.3,.9,"");
       Leg1->SetFillColor(0);
       Leg1->AddEntry(hTheta,"Data");
       Leg1->AddEntry(hTheta->GetFunction("pol0"),"Fit");
       hTheta->Draw("H");
       hTheta->Draw("E,SAME");
       Leg1->Draw("SAME");

       c1->cd(3);
       hPhi->SetFillColor(kBlue);
       hPhi->GetXaxis()->SetTitle("Phi (radiants)");
       hPhi->GetYaxis()->SetTitle("Number of occurrences");
       TLegend* Leg2 = new TLegend(.1,.7,.3,.9,"");
       Leg2->SetFillColor(0);
       Leg2->AddEntry(hPhi,"Data");
       Leg2->AddEntry(hPhi->GetFunction("pol0"),"Fit");
       hPhi->Draw("H");
       hPhi->Draw("E,SAME");
       Leg2->Draw("SAME");

       c1->cd(4);
       hImpulse->SetFillColor(kBlue);
       hImpulse->GetXaxis()->SetTitle("Impulse (GeV)");
       hImpulse->GetYaxis()->SetTitle("Number of occurrences");
       TLegend* Leg3 = new TLegend(.1,.7,.3,.9,"");
       Leg3->SetFillColor(0);
       Leg3->AddEntry(hImpulse,"Data");
       Leg3->AddEntry(hImpulse->GetFunction("expo"),"Fit");
       hImpulse->Draw("H");
       hImpulse->Draw("E,SAME");
       Leg3->Draw("SAME");

       c1->cd(5);
       hTImpulse->SetFillColor(kBlue);
       hTImpulse->GetXaxis()->SetTitle("Transverse Impulse (GeV)");
       hTImpulse->GetYaxis()->SetTitle("Number of occurrences");
       hTImpulse->Draw("H");
       hTImpulse->Draw("E,SAME");

       c1->cd(6);
       hEnergy->SetFillColor(kBlue);
       hEnergy->GetXaxis()->SetTitle("Energy (GeV)");
       hEnergy->GetYaxis()->SetTitle("Number of occurrences");
       hEnergy->Draw("H");
       hEnergy->Draw("E,SAME");

       TCanvas *massCanvas = new TCanvas("massCanvas", "Invariant mass histograms");
       massCanvas->Divide(2, 3);


       massCanvas->cd(1);
       hInvMass->SetFillColor(kBlue);
       hInvMass->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hInvMass->GetYaxis()->SetTitle("Number of occurrences");
       hInvMass->Draw("H");

       massCanvas->cd(2);
       hSameCharge->SetFillColor(kBlue);
       hSameCharge->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hSameCharge->GetYaxis()->SetTitle("Number of Occurrences");
       hSameCharge->Draw("H");
       hSameCharge->Draw("E,SAME");

       massCanvas->cd(3);
       hOddCharge->SetFillColor(kBlue);
       hOddCharge->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hOddCharge->GetYaxis()->SetTitle("Number of Occurrences");
       hOddCharge->Draw("H");
       hOddCharge->Draw("E,SAME");

       massCanvas->cd(4);
       hPKconcordant->SetFillColor(kBlue);
       hPKconcordant->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hPKconcordant->GetYaxis()->SetTitle("Number of Occurrences");
       hPKconcordant->Draw("H");
       hPKconcordant->Draw("E,SAME");

       massCanvas->cd(5);
       hPKdiscordant->SetFillColor(kBlue);
       hPKdiscordant->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hPKdiscordant->GetYaxis()->SetTitle("Number of Occurrences");
       hPKdiscordant->Draw("H");
       hPKdiscordant->Draw("E,SAME");

       TCanvas *c2 = new TCanvas("c2", "K* decay statistics");
       c2->Divide(2, 2);

       c2->cd(1);
       hKDecay->SetFillColor(kBlue);
       hKDecay->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hKDecay->GetYaxis()->SetTitle("Number of Occurrences");
       hKDecay->Draw("H");
       hKDecay->Draw("E,SAME");
       TLegend *Leg4=new TLegend(.1,.7,.3,.9,"");
       Leg4->SetFillColor(0);
       Leg4->AddEntry(hKDecay,"Data");
       Leg4->AddEntry(hKDecay->GetFunction("gaus"),"Fit");
       Leg4->Draw("SAME");
       

       c2->cd(2);
  
       hDiff1->SetFillColor(kBlue);
       hDiff1->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hDiff1->GetYaxis()->SetTitle("Number of Occurrences");
       hDiff1->Draw("H");
       hDiff1->Draw("E,SAME");
       TLegend *Leg5=new TLegend(.1,.7,.3,.9,"");
       Leg5->SetFillColor(0);
       Leg5->AddEntry(hDiff1,"Data");
       Leg5->AddEntry(hDiff1->GetFunction("gaus"),"Fit");
       Leg5->Draw("SAME");


       c2->cd(3);
       hDiff2->SetFillColor(kBlue);
       hDiff2->GetXaxis()->SetTitle("Invariant mass (GeV/c^{2})");
       hDiff2->GetYaxis()->SetTitle("Number of Occurrences");
       hDiff2->Draw("H");
       hDiff2->Draw("E,SAME");
       TLegend *Leg6=new TLegend(.1,.7,.3,.9,"");
       Leg6->SetFillColor(0);
       Leg6->AddEntry(hDiff2,"Data");
       Leg6->AddEntry(hDiff2->GetFunction("gaus"),"Fit");
       Leg6->Draw("SAME");


       c1->SaveAs("types-Impulse-angles.pdf");
       c2->SaveAs("Kstar-stats.pdf");
       massCanvas->SaveAs("invariant-masses.pdf");
       c1->SaveAs("types-Impulse-angles.root");
       c2->SaveAs("Kstar-stats.root");
       massCanvas->SaveAs("invariant-masses.root");

}