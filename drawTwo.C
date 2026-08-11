void drawTwo()
{

    // open output.root 

    TFile* fsim = new TFile("output.root", "READ"); 

     TH1F* MMC_1 = (TH1F*)fsim->Get("C_8.5");
    TH1F* MMC_2 = (TH1F*)fsim->Get("C_7.5");

    TCanvas* c1 = new TCanvas("c1", "c1", 600, 800); 

    MMC_1->Draw("HIST"); 
    MMC_2->Draw("HIST SAME"); 
    
          

}