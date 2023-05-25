{
TCanvas *c1 = new TCanvas("c1","c1",800,800);  //instantiate a canvas.

TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1.0, 1.0);  //instantiate the first pad.
pad1->SetBottomMargin(0.1);
pad1->SetGridx();
pad1->Draw();
pad1->cd();

gStyle->SetOptStat(0);
//////////////////////////////////////////////

TGraph2D* sigs = new TGraph2D("significance_NJL_ee_0123j_pid23.txt");

TH2D* sigsHist = sigs->GetHistogram();
double contours[4];
  contours[0] = 5;
sigsHist->SetContour(1, contours);
sigsHist->Draw("CONT3");

TGraph2D* sigsOld = new TGraph2D("significance_NJL_ee_0J_pi53.txt");

TH2D* sigsOldHist = sigsOld->GetHistogram();
double contours2[4];
   contours2[0] = 5;
sigsOldHist->SetContour(1, contours2);
sigsOldHist->SetLineColor(2);


sigsHist->Draw("CONT3");
sigsOldHist->Draw("SAMECONT3");

}
