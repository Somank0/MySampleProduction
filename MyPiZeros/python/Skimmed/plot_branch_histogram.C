#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>

void plot_branch_histogram(const char* filename, const char* branchname) {
    // Open the ROOT file
    const char* directoryname="nTuplelize";
    const char* treename="T";
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    // Navigate to the TDirectory
    TDirectory *dir = (TDirectory *)file->Get(directoryname);
    if (!dir) {
        std::cerr << "Error: Cannot find directory '" << directoryname << "' in the file." << std::endl;
        file->Close();
        return;
    }

    // Access the tree
    TTree *tree = (TTree *)dir->Get(treename);
    if (!tree) {
        std::cerr << "Error: Cannot find tree '" << treename << "' in the directory '" << directoryname << "'." << std::endl;
        file->Close();
        return;
    }

    // Access the branch (assuming it's a float or double type)
    //Float_t branchValue;
    //tree->SetBranchAddress(branchname, &branchValue);
    std::vector<float> *branchValue = nullptr;
    tree->SetBranchAddress(branchname, &branchValue);
    // Create a histogram
    TH1F *hist = new TH1F("hist", Form("Histogram of %s;%s;Entries", branchname, branchname), 1000, -0.4,2.1);

    // Fill the histogram
Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        for (float value : *branchValue) {
            hist->Fill(value);
        }
    }

    // Create a canvas and draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600);
    hist->SetLineWidth(2);
    hist->Draw();

    // Save the histogram as a PNG
    canvas->SaveAs(Form("%s_histogram.png", branchname));

    // Clean up
    file->Close();
    delete file;
    delete canvas;
    delete hist;
}
