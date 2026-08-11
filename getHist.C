void getHist()
{
    TH1F* hist = new TH1F("hist", "hist", 200, -20, 20) ; 
    TH1F* hist2 = new TH1F("hist2", "hist2", 200, -20, 20); 
    for (Int_t i = 0; i < 10000; i++) hist->Fill(gRandom->Gaus(0, 1));
    for (Int_t i = 0; i < 10000; i++) hist2->Fill(gRandom->Gaus(0, 2));
    TH1F* hist3 = new TH1F("hist3", "hist3", 200, -20, 20); 
    hist3->FillRandom("gaus", 1000); 
    TH1F* hist2_norm = (TH1F*)(hist2->Clone("hist2_norm"));
    hist2_norm->Scale(1./hist2_norm->Integral()); 
     TH1F* hist3_norm = (TH1F*)(hist3->Clone("hist3_norm"));
    hist3_norm->Scale(1./hist3_norm->Integral()); 



    TCanvas* c1 = new TCanvas("c1", "c1", 600, 800); 
    c1->Divide(1,2 ); 
    c1->cd(1); 
    hist->Draw(); 
    c1->cd(2); 
    hist2_norm->Draw(); 
    hist3_norm->Draw("SAME");

}