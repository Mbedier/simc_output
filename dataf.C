#include <string>
#include <ROOT/RDataFrame.hxx>
#include <TH1D.h>
#include <TFile.h>

void dataf()
{
    ROOT::EnableImplicitMT();

    std::string siminput = "simc_root_files/C_rp2.root";
    const double normfactor = 0.932229E+07;
    const double nEvents = 50000.0;

    ROOT::RDataFrame rdf("h10", siminput.c_str());

    auto df_weighted = rdf.Define(
        "mmnuc_weighted",
        [normfactor, nEvents](float mmnuc, float weight) {
            return mmnuc * weight * normfactor / nEvents;
        },
        {"mmnuc", "Weight"}
    );

    auto hist_f = df_weighted.Histo1D({"mmnuc_H", "mmnuc_H", 100, 0.0, 0.006}, "mmnuc_weighted");
    auto h = hist_f.GetValue();
    h.SetTitle("mmnuc_weighted;mmnuc * Weight * normfactor / nEvents;Entries");

    TFile* f = TFile::Open("trial.root", "RECREATE");
    h.SetName("mmnuc_C");
    h.Write("mmnuc_C", TObject::kOverwrite);
    f->Close();

    h.Draw();
}