int line_width[12] = {2,2,2,2,2,2,2,2,2,2,2,2};
int line_style[12] = {1,1,1,1,1,1,1,1,1,1,1,1};                                                                              
int line_color[9] = {kBlue,kRed,kGreen+2,kViolet+2,kYellow+2,kBlue+2,kGreen -3,kGray+2,kMagenta};
int line_color1[9]= {kBlue,kGreen+2,kGray+1,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2};
int line_color2[9] = {kGreen+2,kBlue,kViolet,kGray,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta};
vector<int> col={kGreen+2,kBlue,kViolet,kGray,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2,kMagenta,kCyan};
vector<int> Style={3008,1001,3008,1001};
void decorate(TH1F*,int);
void decorate(TH1F* hist,int i){
  hist->SetLineWidth(3);                                                                                                                        
}
void setLastBinAsOverFlow(TH1F*);
TH1F* setMyRange(TH1F*,double,double);

TH1F* setMyRange(TH1F *h1,double xLow,double xHigh){
  //call it after setting last bin as overflow                                                                                                                               
  double err=0;
  if(xHigh > 13000) return h1;
  if(xLow < -13000) return h1;                                                                                                                     
  int nMax=h1->FindBin(xHigh);
  h1->SetBinContent(nMax,h1->IntegralAndError(nMax,h1->GetNbinsX(),err));
  h1->SetBinError(nMax,err);                                                                                                                 
  for(int i=nMax+1;i<=h1->GetNbinsX()+1;i++){
    h1->SetBinContent(i,0);
    h1->SetBinError(i,0);
                                                                                                                         
  }
  h1->GetXaxis()->SetRangeUser(xLow,xHigh);
  cout<<xLow<<"\t"<<xHigh<<"\t"<<"set range"<<endl;
   return h1;
}

TH1F* DrawOverflow(TH1F*);
TH1F* DrawOverflow(TH1F* h,int xmin, int xrange){

   UInt_t nx    = h->GetNbinsX()+1;
   Double_t *xbins= new Double_t[nx+1];
   for (UInt_t i=0;i<nx;i++)
     xbins[i]=h->GetBinLowEdge(i+1);
   xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
   char *tempName= new char[strlen(h->GetName())+10];
   sprintf(tempName,"%swtOverFlow",h->GetName());
   h->GetXaxis()->SetLimits(xmin,xrange);
   // Book a temporary histogram having ab extra bin for overflows
   TH1F *htmp = new TH1F(tempName, h->GetTitle(), nx, xbins);
   htmp->GetXaxis()->SetRange(xmin,xrange);
   // Reset the axis labels
   htmp->SetXTitle(h->GetXaxis()->GetTitle());
   htmp->SetYTitle(h->GetYaxis()->GetTitle());
   // Fill the new hitogram including the extra bin for overflows
   for (UInt_t i=1; i<=nx; i++)
     htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
   // Fill the underflows
   htmp->Fill(h->GetBinLowEdge(1)-1, h->GetBinContent(0));
   
   htmp->SetEntries(h->GetEntries());
   
   return htmp;
}
void setLastBinAsOverFlow(TH1F* h_hist){
  double lastBinCt =h_hist->GetBinContent(h_hist->GetNbinsX()),overflCt =h_hist->GetBinContent(h_hist->GetNbinsX()+1);
  double lastBinErr=h_hist->GetBinError(h_hist->GetNbinsX()),  overflErr=h_hist->GetBinError(h_hist->GetNbinsX()+1);

  if(lastBinCt!=0 && overflCt!=0)
    lastBinErr = (lastBinCt+overflCt)* (sqrt( ((lastBinErr/lastBinCt)*(lastBinErr/lastBinCt)) + ((overflErr/overflCt)*(overflErr/overflCt)) ) );

  else if(lastBinCt==0 && overflCt!=0)
    lastBinErr = overflErr;
  else if(lastBinCt!=0 && overflCt==0)
    lastBinErr = lastBinErr;
  else lastBinErr=0;

  lastBinCt = lastBinCt+overflCt;
  h_hist->SetBinContent(h_hist->GetNbinsX(),lastBinCt);
  h_hist->SetBinError(h_hist->GetNbinsX(),lastBinErr);
  cout<<lastBinCt<<"\t"<<"Last bin values"<<endl;

}
const int nfiles=100;                                                                                                                                                             
TFile *f[nfiles];

void generate_1Dplot(vector<TH1F*> hist,char const *tag_name="",char const *xlabel="",char const *ylabel="",  int rebin=-1,double ymin=0,double ymax=0,int xmin=-1,int xmax=-1,char const *leg_head="",bool normalize=false, bool log_flag=false, bool DoRebin=false, bool save_canvas=true, char const *title="", vector<string> legend_texts={"nil"})
{  
     TCanvas *canvas_n1 = new TCanvas(tag_name, tag_name,950,850);
       canvas_n1->Range(-60.25,-0.625,562.25,0.625);
       canvas_n1->SetFillColor(0);
       canvas_n1->SetBorderMode(0);
       canvas_n1->SetBorderSize(1);
       canvas_n1->SetLeftMargin(0.135);
       canvas_n1->SetRightMargin(0.035);
       canvas_n1->SetTopMargin(0.04);
       canvas_n1->SetBottomMargin(0.1);
       //THStack *hs_var=new THStack("var_Stack","");
       gStyle->SetOptStat(1111111);
       //   gStyle->SetOptStat(0);
       //double pvt_x_min = 0.6;
  double pvt_x_min = 0.75;
  double pvt_x_max = 0.99;
  double pvt_y_min = 0.9;
  //double pvt_dely = 0.18;
  double pvt_dely = 0.15;
  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  //gStyle->SetOptFit(0);
  vector<TString> legName;
  //TLegend *legend = new TLegend(0.65,0.95,0.99,0.75);
  std::string leg_head_str = leg_head;
  double x = 0.15;
  double y = 0.90;
  TLegend *legend;
  //legend = new TLegend(0.60,0.88,0.98,0.72);  
  legend = new TLegend(0.21,0.82,0.65,0.95);  
  legend->SetTextSize(0.035);
  legend->SetLineColor(kWhite);
  legend->SetNColumns(2);
  legend->SetColumnSeparation(0.7);
  legend->SetEntrySeparation(0.1);
  char* lhead = new char[100];

  sprintf(lhead,"#bf{%s} ",title);
  legend->SetHeader(lhead);
  legend->SetLineColor(kWhite);

  TLegendEntry* leg_entry[11];
  float x_label_size = 0.04;
  double xrange = xmax;
  
  vector<TH1F*> hist_list_temp;
  cout<<" hist.size() = "<<hist.size()<<endl;
  
  for(int i =0;i<(int)hist.size(); i ++) {
    
    if(normalize) {
       hist.at(i)->Scale(1.0/hist.at(i)->Integral());
      hist.at(i)->GetYaxis()->SetTitle("Normalized");
    }
    else {
      hist.at(i)->GetYaxis()->SetTitle("Entries");
      
    }
    
    hist.at(i)->SetLineWidth(line_width[i]);
    hist.at(i)->SetLineStyle(line_style[i]);
    hist.at(i)->SetLineColor(line_color[i]);
    hist.at(i)->SetTitle(" ");
    hist.at(i)->GetXaxis()->SetTitleSize(0.05);
    hist.at(i)->GetXaxis()->SetLabelSize(0.05);
    hist.at(i)->GetYaxis()->SetTitleSize(0.05);
    hist.at(i)->GetYaxis()->SetLabelSize(0.05);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.15);
    hist.at(i)->GetYaxis()->SetLabelSize(x_label_size);
    hist.at(i)->SetLineColor(line_color[i]);
    hist.at(i)->SetTitle("");
    //
    hist.at(i)->GetXaxis()->SetTitleSize(0.04);
    hist.at(i)->GetXaxis()->SetTitle(xlabel);
    hist.at(i)->GetYaxis()->SetTitleSize(0.05);
    hist.at(i)->GetYaxis()->SetLabelSize(0.040);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.2);
     decorate(hist.at(i),i);
    hist.at(i)->SetMarkerSize(0.8);
    hist.at(i)->SetMarkerStyle(20);
    hist.at(i)->SetMarkerColor(line_color[i]);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.4);
    hist.at(i)->GetXaxis()->SetLabelSize(0.04);

    legName.push_back(hist.at(i)->GetName());
    leg_entry[i] = legend->AddEntry(hist.at(i),legend_texts[i].c_str(),"l");
    leg_entry[i]->SetTextColor(hist.at(i)->GetLineColor());
    
    if(hist.at(i)->GetMaximum() > ymax) ymax = hist.at(i)->GetMaximum();
    if(hist.at(i)->GetMinimum() < ymin) ymin = hist.at(i)->GetMinimum();

    

  }
  if(ymin == 0.0) ymin = 1e-3;
  if(ymin<0.0) ymin = 1e-4;
  //  if(ymax<=10) ymax=10;
  for(int i = 0;i<(int)hist.size(); i++) {
    if(!normalize) {
    if (log_flag){ hist.at(i)->GetYaxis()->SetRangeUser(0.1,10*ymax);}
    else {
    hist.at(i)->GetYaxis()->SetRangeUser(0.00001,1.5*ymax);hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);}
    }
    
    else
      {  hist.at(i)->GetYaxis()->SetRangeUser(0.00001,5);

      }
    cout<<"i"<<i<<endl;
    if(i==0) hist.at(i)->Draw("hist ");
    else hist.at(i)->Draw("hist sames");
	
  }
  legend->Draw();
  if(log_flag) {
      gPad->SetLogy();
    }
gPad->Update(); 
  TLatex* textOnTop = new TLatex();
  //new
    textOnTop->SetTextSize(0.054);
  //textOnTop->DrawLatexNDC(0.146,0.925,"CMS #it{#bf{Simulation Preliminary}}");
  char* en_lat = new char[500];
  textOnTop->SetTextSize(0.054);
  //textOnTop->DrawLatexNDC(0.72,0.925,en_lat);


  gPad->Modified();
                                                                                       
    
 char* canvas_name = new char[1000];
  //c->Print(canvas_name);
  
  if(save_canvas) {
    sprintf(canvas_name,"%s.png",tag_name);
     canvas_n1->SaveAs(canvas_name);   
     sprintf(canvas_name,"%s.pdf",tag_name);
    canvas_n1->SaveAs(canvas_name);  
  } 
}
struct MixedData {
     vector<string> str1;
     string str4;
     string str2;
     int intData;
     double double1;
     double double2;
     double double3;
     double double4;
     vector<string> str3;
 };

void Overlay1D(){

    char* hname = new char[200];
  
  char* hist_name = new char[200];
  
  char* title= new char[2000];
 
  char *leg_head = new char[200];
 
  int n=0;
  int n_files=1;
 
    //f[0] = new TFile("plot.root");
    //f[0] = new TFile("EB_plot.root");
    f[0] = new TFile("testplot.root");

    //vector<string> filetag=  {"Sample size:112K"};
    vector<string> filetag={""};
    //vector<vector<string>> varName;
    //vector<vector<string>> legend_texts;
    //vector<string> xLabel;
    vector<string> loghist;
    vector<string> norm;
MixedData varName[]= {  // {{Array of names of plots},Title of plot, xlabel, rebin, ymin, ymax , xmin, xmax, {legend}}

{{"Angle_240<=Ma<=260","Angle_490<=Ma<=510","Angle_740<=Ma<=760","Angle_990<=Ma<=1010"},"Angle between gen photons","Angle",10,0,200,0,0.22,{"240<=Ma<=260","490<=Ma<=510","740<=Ma<=760","990<=Ma<=1010"}},

{{"N_EE_rechits_Ma_250","N_EE_rechits_Ma_500","N_EE_rechits_Ma_750","N_EE_rechits_Ma_1000"},"No. of ECAL rechits","No. of rechits",10,0,20,0,300,{"240<=Ma<=260","490<=Ma<=510","740<=Ma<=760","990<=Ma<=1010"}},

{{"Tot_clu_RH_E_Ma_200_300","Tot_clu_RH_E_Ma_400_500","Tot_clu_RH_E_Ma_600_700","Tot_clu_RH_E_Ma_800_900","Tot_clu_RH_E_Ma_1000_1100","Tot_clu_RH_E_Ma_1400_1500","Tot_clu_RH_E_Ma_1800_1900"},"Total clustered rechits energy","Total clustered energy (GeV)",10,0,20,0,1000,{"M_{a} = 0.2-0.3 GeV","M_{a} = 0.4-0.5 GeV","M_{a} = 0.6-0.7 GeV","M_{a} = 0.8-0.9 GeV","M_{a} = 1.0-1.1 GeV","M_{a} = 1.4-1.5 GeV","M_{a} = 1.8-1.9 GeV"} },

{{"Tot_unc_RH_E_Ma_200_300","Tot_unc_RH_E_Ma_400_500","Tot_unc_RH_E_Ma_600_700","Tot_unc_RH_E_Ma_800_900","Tot_unc_RH_E_Ma_1000_1100","Tot_unc_RH_E_Ma_1400_1500", "Tot_unc_RH_E_Ma_1800_1900"},"Total unclustered rechit energy", "Total unclustered energy (GeV)",10,0,20,0,1000,{"M_{a} = 0.2-0.3 GeV","M_{a} = 0.4-0.5 GeV","M_{a} = 0.6-0.7 GeV","M_{a} = 0.8-0.9 GeV","M_{a} = 1.0-1.1 GeV","M_{a} = 1.4-1.5 GeV","M_{a} = 1.8-1.9 GeV"}},
{{"Tot_unc_RH_E_0p2_Ma_200_300","Tot_unc_RH_E_0p2_Ma_400_500","Tot_unc_RH_E_0p2_Ma_600_700","Tot_unc_RH_E_0p2_Ma_800_900","Tot_unc_RH_E_0p2_Ma_1000_1100","Tot_unc_RH_E_0p2_Ma_1400_1500","Tot_unc_RH_E_0p2_Ma_1800_1900"},"Total unclustered rechit energy","Total unclustered energy (GeV) (E_{rechit} > 0.2 GeV)",10,0,20,0,1000,{"M_{a} = 0.2-0.3 GeV","M_{a} = 0.4-0.5 GeV","M_{a} = 0.6-0.7 GeV","M_{a} = 0.8-0.9 GeV","M_{a} = 1.0-1.1 GeV","M_{a} = 1.4-1.5 GeV","M_{a} = 1.8-1.9 GeV"}},
{{"Tot_clu_RH_E_Ma_250","Tot_clu_RH_E_Ma_500","Tot_clu_RH_E_Ma_750","Tot_clu_RH_E_Ma_1000" },"Total energy of clustered rechits","Energy (GeV)",10,0,20,0,1000,{"Ma = 0.24-0.26 GeV","Ma = 0.49-0.51 GeV", "Ma = 0.74-0.76 GeV" , "Ma = 0.99-1.01 GeV"}},

{{"Tot_unc_RH_E_Ma_250","Tot_unc_RH_E_Ma_500","Tot_unc_RH_E_Ma_750", "Tot_unc_RH_E_Ma_1000"},"Total energy of unclustered rechits","Energy (GeV)",10,0,20,0,300,{"Ma = 0.24-0.26 GeV","Ma = 0.49-0.51 GeV", "Ma     = 0.74-0.76 GeV" , "Ma = 0.99-1.01 GeV"}},

{{"ES Layer 1 hits","ES Layer 2 hits"},"ES hits","No. of hits per event",10,0,200,0,300,{"ES Layer1","ES Layer2"}},

{{"Pho_sig_iEiE_Ma_200_300","Pho_sig_iEiE_Ma_400_500","Pho_sig_iEiE_Ma_600_700","Pho_sig_iEiE_Ma_800_900","Pho_sig_iEiE_Ma_900_1000"},"sigma_iE_iE","#sigma_{i#eta i#eta}",10,0,200,0,0.1,{"Ma = 0.2-0.3 GeV","Ma = 0.4-0.5 GeV","Ma = 0.6-0.7 GeV","Ma = 0.8-0.9 GeV","Ma = 0.9-1.0 GeV"}},

{{"Pho_sig_iPhiiPhi_Ma_200_300","Pho_sig_iPhiiPhi_Ma_400_500","Pho_sig_iPhiiPhi_Ma_600_700","Pho_sig_iPhiiPhi_Ma_800_900","Pho_sig_iPhiiPhi_Ma_900_1000"},"sigma_iphi_iphi","#sigma_{i#phi_i#phi}",10,0,200,0,0.1,{"Ma = 0.2-0.3 GeV","Ma = 0.4-0.5 GeV","Ma = 0.6-0.7 GeV","Ma = 0.8-0.9 GeV","Ma = 0.9-1.0 GeV"}},
{{"Unc_RH_E_ma_400","Unc_RH_E_ma_1800"},"Unc_RH_E_ma_400","Unclustered rechit energy (GeV)",2,0,200,-2,2,{"M_{a} = 0.38-0.42 GeV","Ma = 1.78-1.82 GeV"}},
{{"Unc_rec_E_ma_400_500","Unc_rec_E_ma_1700_1800"},"Unc_rec_E_ma","Unclustered rechit energy (GeV)",2,0,200,-2,2,{"M_{a} = 0.4-0.5 GeV","M_{a} = 1.7-1.8 GeV"}},

{{"Tot_unc_RH_E_noise_Ma_200_300","Tot_unc_RH_E_noise_Ma_400_500","Tot_unc_RH_E_noise_Ma_600_700","Tot_unc_RH_E_noise_Ma_800_900","Tot_unc_RH_E_noise_Ma_1000_1100","Tot_unc_RH_E_noise_Ma_1400_1500","Tot_unc_RH_E_noise_Ma_1800_1900"},"Tot_unc_rec_E-noise","Total unclustered energy (GeV) (E_{rechit} - E_{noise})",10,0,20,0,300,{"M_{a} = 0.2-0.3 GeV","M_{a} = 0.4-0.5 GeV","M_{a} = 0.6-0.7 GeV","M_{a} = 0.8-0.9 GeV","M_{a} = 1.0-1.1 GeV","M_{a} = 1.4-1.5 GeV","M_{a} = 1.8-1.9 GeV"}},

{{"N_supcl_hits0_100","N_supclu_dRhits_0_100","N_raw_hits_0_100"},"N_rechit_Ma_0_100","No. of rechits (0 < M_{a} < 0.1 GeV)",10,0,20,0,300,{"Sup.Clu hits","Sup.Clu. + dR(0.3) hits","Raw rechtis (dR=0.3)" }},

{{"N_supcl_hits400_500","N_supclu_dRhits_400_500","N_raw_hits_400_500"},"N_rechit_Ma_400_500","No. of rechits (0.4 < M_{a} < 0.5 GeV)",10,0,20,0,300,{"Sup.Clu hits","Sup.Clu. + dR(0.3) hits","Raw rechtis (dR=0.3)" }},

{{"N_supcl_hits1700_1800","N_supclu_dRhits_1700_1800","N_raw_hits_1700_1800"},"N_rechit_Ma_1700_1800","No. of rechits (1.7 < M_{a} < 1.8 GeV)",10,0,20,0,300,{"Sup.Clu hits","Sup.Clu. + dR(0.3) hits","Raw rechtis (dR=0.3)" }},

{{"Tot_clu_RH_E_Ma_400_500","Tot_unc_RH_E_Ma_400_500","Tot_raw_Energy_400_500"},"E_rechits_Ma_400_500","Rechit energy (GeV)",10,0,20,0,1000,{"Supercluster energy", "Total unclustered energy","Total energy in raw rechits"}},

{{"Tot_clu_RH_E_Ma_1700_1800","Tot_unc_RH_E_Ma_1700_1800","Tot_raw_Energy_1700_1800"},"E_rechits_Ma_1700_1800","Rechit energy (GeV)",10,0,20,0,1000,{"Supercluster energy", "Total unclustered energy","Total energy in raw rechits"}},
{{"Tot_raw_Energy_200_300","Tot_raw_Energy_400_500","Tot_raw_Energy_600_700","Tot_raw_Energy_800_900","Tot_raw_Energy_1000_1100","Tot_raw_Energy_1400_1500","Tot_raw_Energy_1800_1900"},"Total_raw_energy","Energy (GeV)",10,0,20,0,1000,{"M_{a} = 0.2-0.3 GeV","M_{a} = 0.4-0.5 GeV","M_{a} = 0.6-0.7 GeV","M_{a} = 0.8-0.9 GeV","M_{a} = 1.0-1.1 GeV","M_{a} = 1.4-1.5 GeV","M_{a} = 1.8-1.9 GeV"}},
{{"Tot_raw_Energy_200_300","Tot_raw_Energy_600_700","Tot_raw_Energy_1000_1100","Tot_raw_Energy_1400_1500","Tot_raw_Energy_1800_1900"},"Total_raw_energy","Energy (GeV)",10,0,20,0,1000,{"M_{a} = 0.2-0.3 GeV","M_{a} = 0.6-0.7 GeV","M_{a} = 1.0-1.1 GeV","M_{a} = 1.4-1.5 GeV","M_{a} = 1.8-1.9 GeV"}},
{{"Tot_raw_Energy_200_300","Tot_raw_Energy_600_700"},"Total_raw_energy","Energy (GeV)",10,0,20,0,1000,{"M_{a} = 0.2-0.3 GeV","M_{a} = 0.6-0.7 GeV"}},
};
 vector<string> GEN = {"Angle between gen photons"};

loghist = {"Angle between gen photons","Total clustered rechits energy","Total unclustered rechit energy","Total energy of clustered rechits","Total energy of unclustered rechits","sigma_iE_iE","sigma_iphi_iphi","Tot_unc_rec_E-noise","Unc_rec_E_ma","N_rechit_Ma_1700_1800","N_rechit_Ma_400_500","E_rechits_Ma_1700_1800","Total_raw_energy",};
norm ={"Angle between gen photons",/*"Total clustered rechits energy",*/"Total unclustered rechit enrergy","Total energy of clustered rechits" , "Total energy of unclustered rechits","sigma_iE_iE","sigma_iphi_iphi"};
  sprintf(hname,"temp.root");
  TFile* fout = new TFile(hname,"RECREATE");
 
    n_files=1;  
    
  for(int i_file=0; i_file<n_files;i_file++)
    {      
    for(int i=0; i<size(varName); i++){
        
        int rebin = varName[i].intData; 
        string xLabel = varName[i].str2;
        double ymin = varName[i].double1;
        double ymax = varName[i].double2;
        double xmin = varName[i].double3;
        double xmax = varName[i].double4;
        vector<string> legend_texts = varName[i].str3;
        string Name = varName[i].str4;
        vector<string> VarName = varName[i].str1;
        cout << VarName.size() << endl;
        vector<TH1F*> hist_list;
        for (int j=0; j<VarName.size();j++){
           
	  sprintf(hist_name,"%s",VarName[j].c_str());
	  cout<<hist_name<<"\t"<<i<<"\t"<<i_file<<"\t"<<f[i_file]->GetName()<<endl;
	  
          TH1F* h_orig = (TH1F*)f[i_file]->Get(hist_name); // SR
          string hist_name_ = VarName[j] + "_";
           
	  TH1F* h_resp2 = (TH1F*)h_orig->Clone(hist_name_.c_str()); // SR
	  h_resp2->GetXaxis()->SetTitle(xLabel.c_str());
	  cout<<"resp2 "<<h_resp2->Integral()<<"\t"<<rebin<<"\t"<<xmin<<"\t"<<xmax<<endl;
	  
	  h_resp2->Rebin(rebin);
	 
	  
	  h_resp2= setMyRange(h_resp2,xmin,xmax+0.01*xmax);
	  setLastBinAsOverFlow(h_resp2);
	  
	  
	  hist_list.push_back(h_resp2); 
        }
      string  Savename;
    int gen = count(GEN.begin(),GEN.end(),Name);
    int LOG = count(loghist.begin(), loghist.end(),Name);
    int NORM= count(norm.begin(), norm.end(),Name);
    if(gen){Savename = "GEN_";}
    else {Savename = "RECO_";}
         string Savename2=Savename+to_string(1000 + i)+"_" +Name + "_overlay";

generate_1Dplot(hist_list,Savename2.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,false,false,false,true,filetag[i_file].c_str(),legend_texts);
if(LOG && NORM){
         string Savename1=Savename +to_string(1000 + i) +"_"+Name + "_overlay_logy_norm";
generate_1Dplot(hist_list,Savename1.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,true,true,false,true,filetag[i_file].c_str(),legend_texts);
}

          else if(LOG && !NORM){
          string Savename1=Savename+to_string(1000 + i)+"_" +Name + "_overlay_logy";
generate_1Dplot(hist_list,Savename1.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,false,true,false,true,filetag[i_file].c_str(),legend_texts);
	  }
          else if(!LOG && NORM){
          string Savename1=Savename+to_string(1000 + i)+"_" +Name + "_overlay_norm"; 
generate_1Dplot(hist_list,Savename1.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,true,false,false,true,filetag[i_file].c_str(),legend_texts);
}
	 
          
        
    }
}
}
