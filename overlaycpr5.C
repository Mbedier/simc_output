#include <iostream> 
#include "stree.h"

void overlaycpr5()
{

TFile* fout = new TFile("cprout.root", "RECREATE");
THStack* hstac = new THStack("stack", "Old vs Updated 63Cu SF"); 
TLegend* leg = new TLegend(0.7, 0.6, 0.9, 0.9); 
// first define the two hists here so they belong to global (?) gDirectory
//TH1F* hold = new TH1F("MM_old", "Old spec. fun", 300, 56, 62); 
//TH1F* hnew = new TH1F("MM_new", "New spec. fun", 300, 56, 62); 

TH1F* hold = new TH1F("Em_old", "Old spec. fun", 300, 0, 4); 
TH1F* hnew = new TH1F("Em_new", "New spec. fun", 300, 0, 4); 
// detach from any file directory so they survive fsim[i]->Close()
hold->SetDirectory(0);
hnew->SetDirectory(0);

// open old cpr for Q2=5

//TFile* fold = new TFile("simc_root_files/Cu_5.root", "READ"); 
//TFile* fnew = new TFile("simc_root_files/Cu_5n.root", "READ"); 
TFile* fsim[2] = {nullptr}; 
TString fnames[2] = {"Cu_85.root", "Cu_85r.root"}; 

TH1F* mmhists[2] = {hold, hnew}; 
double norm_facs[2] = {0.636030E+06  , 0.658885E+06   };


for (int i = 0; i < 2; ++i )
{
    
    fsim[i] = new TFile(Form("simc_root_files/%s", fnames[i].Data()), "READ"); 
    if (!fsim[i]){std::cout << "Could not open file " << fnames[i] << " .. aboring .. " << '\n'; break;}
    TTree* sim_tree = get_tree(fsim[i], "h10"); 
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
             
             mmhists[i]->Fill(Em,  Weight* norm_facs[i] / 50000 );
             

            }
        
            mmhists[i]->SetDirectory(fout);
        }
    std::cout << i <<"th hist filled successfully.\n";
     
    
   fsim[i]->Close();
}
fout->cd(); 
mmhists[0]->Write("newSF", TObject::kOverwrite); 
mmhists[1]->Write("newSF", TObject::kOverwrite); 
hstac->Add(mmhists[0]);
hstac->Add(mmhists[1]);
leg->AddEntry(mmhists[0], "Old SF"); 
leg->AddEntry(mmhists[1], "New SF"); 
// set distinct line colors/styles for the overlay (marker style kept in case you want "P" draw option)
hold->SetLineColor(kBlue);
//hold->SetMarkerStyle(21);
hold->SetMarkerColor(kBlue);

hnew->SetLineColor(kRed);
//hnew->SetMarkerStyle(22);
hnew->SetMarkerColor(kRed);

TCanvas* c1 = new TCanvas("c1", "c1", 1000, 1000); 
hstac->Draw("nostack HIST");
//hstac->Draw();
leg->Draw();
//c1->Divide(1,2);
// make sure the y-axis range accommodates both histograms
//double ymax = std::max(hnew->GetMaximum(), hold->GetMaximum());
//hnew->SetMaximum(1.1 * ymax);
//c1->cd(1);
//hnew->Draw("hist ");
//c1->cd(2);
//hold->Draw("hist");
std::cout << "Old yeild: " << hold->Integral()<< '\n';
std::cout << "new yeild: " << hnew->Integral()<< '\n';

//TLegend* leg = new TLegend(0.7, 0.75, 0.9, 0.9);
//leg->AddEntry(hnew, "New spec. fun", "l");
//leg->AddEntry(hold, "Old spec. fun", "l");
//leg->Draw();

}
