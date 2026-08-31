#include <iostream> 
#include "stree.h"
void allcpr()
{
    TH1F* hists_old[4] ={nullptr};
    TH1F* hists_new[4] = {nullptr}; 
    TString fnames_old[4] = {"Cu_5.root", "Cu_65.root", "Cu_75.root", "Cu_85.root"};
    TString fnames_new[4] = {"Cu_5r.root", "Cu_65r.root", "Cu_75r.root", "Cu_85r.root"};
    TFile* fsim_old[4] = {nullptr};
    TFile* fsim_new[4] = {nullptr}; 
    THStack* stacks[4] = {nullptr};
    TLegend* legs[4] = {nullptr};
    TString Qvals[4] = {"5", "6.5", "7.5" , "8.5"};
    double norm_facs_old[4] = {0.107139E+07, 0.958776E+06, 0.800897E+06, 0.636030E+06};
    double norm_facs_new[4] = {0.109743E+07, 0.989659E+06, 0.819971E+06, 0.658885E+06};

    for (int i =0 ; i< 4; ++i)
    {
        
        // 1- open old files, read them and fil hists_old
        fsim_old[i] = new TFile(Form("simc_root_files/%s", fnames_old[i].Data()), "READ");
        TTree* sim_tree_old = get_tree(fsim_old[i], "h10");
        Long64_t numEntries =   sim_tree_old->GetEntries();
        hists_old[i] = new TH1F(Form("old_%s", Qvals[i].Data()), "", 200, 0, 4);
        for (Long64_t j = 0 ; j < numEntries; ++j)
        {
            sim_tree_old->GetEntry(j);
            

            double xathgcer = ssxfp + 156.27 * ssxpfp;
            double yathgcer = ssyfp + 156.27 * ssypfp;
        
            bool central_hole       = (pow(yathgcer-1.33,2) + pow(xathgcer-1.1,2) >= pow(7.0,2));
            
           // bool right_or_left_of_hole = ((yathgcer > 1.33 && (xathgcer < 0. || xathgcer > 3.0)) ||
            //                          (yathgcer < 1.33 && (xathgcer < 0. || xathgcer > 3.0)));
            //bool remove_region      = central_hole && right_or_left_of_hole;
        
       
           bool remove_region = central_hole; 
            if (remove_region) {
             
             hists_old[i]->Fill(Em - 0.939,  Weight* norm_facs_old[i] / 50000 );
             

            }
        
        }



        //2-open new files, read them and fill hists_new
          // 1- open old files, read them and fil hists_old
        fsim_new[i] = new TFile(Form("simc_root_files/%s", fnames_new[i].Data()), "READ");
        TTree* sim_tree_new = get_tree(fsim_new[i], "h10");
        Long64_t numEntries2 =   sim_tree_new->GetEntries();
        hists_new[i] = new TH1F(Form("new_%s", Qvals[i].Data()), "", 200, 0, 4);
        for (Long64_t j = 0 ; j < numEntries2; ++j)
        {
            sim_tree_new->GetEntry(j);
            

            double xathgcer = ssxfp + 156.27 * ssxpfp;
            double yathgcer = ssyfp + 156.27 * ssypfp;
        
            bool central_hole       = (pow(yathgcer-1.33,2) + pow(xathgcer-1.1,2) >= pow(7.0,2));
            
           // bool right_or_left_of_hole = ((yathgcer > 1.33 && (xathgcer < 0. || xathgcer > 3.0)) ||
            //                          (yathgcer < 1.33 && (xathgcer < 0. || xathgcer > 3.0)));
            //bool remove_region      = central_hole && right_or_left_of_hole;
        
       
           bool remove_region = central_hole; 
            if (remove_region) {
             
             hists_new[i]->Fill(Em - 0.939,  Weight* norm_facs_new[i] / 50000 );
             

            }
        
        }
        hists_old[i]->SetLineColor(kBlue);
        hists_new[i]->SetLineColor(kRed);
        stacks[i] = new THStack(Form("h%d", i), Form("Q2 = %s ", Qvals[i].Data())); 
        stacks[i]->Add(hists_old[i]);
        stacks[i]->Add(hists_new[i]);
        legs[i]= new TLegend(0.7, 0.6, 0.9, 0.9);
        legs[i]->AddEntry(hists_old[i], "Old SF");
        legs[i]->AddEntry(hists_new[i],"New SF");
    }
//gStyle->SetPadTopMargin(0.25);
TCanvas* c1 = new TCanvas("c1", "Missing Energy", 1000, 1000); 
//c1->SetTopMargin(0.1); 
//c1->SetBottomMargin(0.1);
//c1->SetLeftMargin(0.05);
//c1->SetRightMargin(0.05);
TLatex *lat = new TLatex(.4,.95,"Missing Mass - 63Cu");
lat->Draw();
c1->Divide(2,2); 
for (int k = 0; k < 4; ++k)
{
    c1->cd(k + 1); 
    stacks[k]->Draw("nostack HIST"); 
    legs[k]->Draw();
}

}