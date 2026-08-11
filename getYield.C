#include <iostream> 
#include <fstream> 
void getYield()
{
    TString trg[4] = {"H", "ld2", "C", "Cu"};
    TString QVals[4] = {"8.5", "7.5", "6.5", "5"};

    // 1- open output.root 
    TFile* fin = new TFile("output.root", "READ"); 

    TH1F* hists[4][4] = {nullptr}; 
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j )
        {
            // retireve hists 
            hists[i][j] = (TH1F*)fin->Get(Form("%s_%s_MM", trg[i].Data(), QVals[j].Data()  )); 
            std::cout << hists[i][j]->Integral() << " " ; 
        }
        std::cout << "\n"; 
    }


}