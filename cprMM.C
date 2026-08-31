#include <iostream> 
#include "stree.h"

void cprMM()
{
    TFile* fsim[4] = {nullptr}; 
    TString fNames[4] = {"Cu_5.root", "Cu_65.root", "Cu_75.root", "Cu_85.root"}; 
    TString Qval[4] = {"5", "6.5", "7.5", "8.5"}; 
    double norm_facs[4] = {0.107139E+07, 0.958776E+06 , 0.800897E+06, 0.636030E+06};
    TH1F* mmhists[4] = {nullptr};
    TString root_dir = "simc_root_files/";
    for (int i =0; i < 4; ++i)
    {
        fsim[i] = new TFile(root_dir + fNames[i].Data(), "READ"); 

        TTree* sim_tree = get_tree(fsim[i], "h10");
        mmhists[i] = new TH1F(Form("Cu_%s", Qval[i].Data()), Form("Q2 = %s", Qval[i].Data()), 300, 58, 61 ); 
        Long64_t numEntries =   sim_tree->GetEntries();
        for (Long64_t j = 0 ; j < numEntries; ++j)
        {
            sim_tree->GetEntry(j);
            

            double xathgcer = ssxfp + 156.27 * ssxpfp;
            double yathgcer = ssyfp + 156.27 * ssypfp;
        
            bool central_hole       = (pow(yathgcer-1.33,2) + pow(xathgcer-1.1,2) >= pow(7.0,2));
            
           // bool right_or_left_of_hole = ((yathgcer > 1.33 && (xathgcer < 0. || xathgcer > 3.0)) ||
            //                          (yathgcer < 1.33 && (xathgcer < 0. || xathgcer > 3.0)));
            //bool remove_region      = central_hole && right_or_left_of_hole;
        
       
           bool remove_region = central_hole; 
            if (remove_region) {
             
             mmhists[i]->Fill(mmnuc,  Weight* norm_facs[i] / 50000 );
             

            }

        }
        std::cout << "yield is: " << mmhists[i]->Integral()<< '\n';
    }

    TCanvas* c1 = new TCanvas("c1", "c1", 1000, 1000); 
    TLatex *lat = new TLatex(.4,.95,"Missing Energy - 63Cu");
    c1->Divide(2,2); 
    for (int k =0; k< 4; ++k)
    {
        c1->cd(k + 1); 
        mmhists[k]->Draw("HIST"); 
    } 


}