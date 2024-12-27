int line_width[12] = {2,2,2,2,2,2,2,2,2,2,2,2};
int line_style[12] = {1,1,1,1,1,1,1,1,1,1,1,1};                                                                              
int line_color[9] = {kBlue,kRed,kGreen+2,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2};
int line_color1[9]= {kBlue,kGreen+2,kGray+1,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2};
int line_color2[9] = {kGreen+2,kBlue,kViolet,kGray,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta};
vector<int> col={kGreen+2,kBlue,kViolet,kGray,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2,kMagenta,kCyan};
vector<int> Style={3008,1001,3008,1001};
void decorate(TH2F*,int);
void decorate(TH2F* hist,int i){
  hist->SetLineWidth(3);                                                                                                                        
}

void generate_2Dplot(vector<TH2F*> hist,char const *tag_name="",char const *xlabel="",char const *ylabel="",  int rebin=-1,double ymin=0,double ymax=0,double xmin=-1,double xmax=-1,
bool normalize=false, bool log_flag=false, bool DoRebin=false, bool Text =false, bool save_canvas=true, char const *title=""/*, vector<string> legend_texts={"nil"}*/)
{  
     TCanvas *canvas_n1 = new TCanvas(tag_name, tag_name,950,850);
       canvas_n1->Range(-60.25,-0.625,562.25,0.625);
       canvas_n1->SetFillColor(0);
       canvas_n1->SetBorderMode(0);
       canvas_n1->SetBorderSize(1);
       canvas_n1->SetLeftMargin(0.124);
       canvas_n1->SetRightMargin(0.125);
       canvas_n1->SetTopMargin(0.08);
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
  gStyle->SetPaintTextFormat("4.3f");
  gROOT->ForceStyle();
  //gStyle->SetOptFit(0);
  vector<TString> legName;
  //TLegend *legend = new TLegend(0.65,0.95,0.99,0.75);
  //std::string leg_head_str = leg_head;
  double x = 0.15;
  double y = 0.90;
  TLegend *legend;
  //legend = new TLegend(0.60,0.88,0.98,0.72);  
  legend = new TLegend(0.21,0.82,0.65,0.95);  
  legend->SetTextSize(0.055);
  legend->SetLineColor(kWhite);
  legend->SetNColumns(4);
  char* lhead = new char[100];

  sprintf(lhead,"#bf{%s} ",title);
  legend->SetHeader(lhead);
  legend->SetLineColor(kWhite);

  TLegendEntry* leg_entry[11];
  float x_label_size = 0.04;
  double xrange = xmax;
  
  vector<TH2F*> hist_list_temp;
  cout<<" hist.size() = "<<hist.size()<<endl;
  
  for(int i =0;i<(int)hist.size(); i ++) {
    
   
    hist.at(i)->GetYaxis()->SetTitle(ylabel);
    hist.at(i)->SetLineWidth(line_width[i]);
    hist.at(i)->SetLineStyle(line_style[i]);
    hist.at(i)->SetLineColor(line_color[i]);
    hist.at(i)->SetTitle(" ");
    hist.at(i)->GetXaxis()->SetTitleSize(0.05);
    hist.at(i)->GetXaxis()->SetLabelSize(0.05);
    hist.at(i)->GetYaxis()->SetTitleSize(0.05);
    hist.at(i)->GetYaxis()->SetLabelSize(0.05);
    hist.at(i)->GetYaxis()->SetTitleOffset(0.9);
    hist.at(i)->GetYaxis()->SetLabelSize(x_label_size);
    hist.at(i)->SetLineColor(line_color[i]);
    hist.at(i)->SetTitle(title);
    //
    hist.at(i)->GetXaxis()->SetTitleSize(0.04);
    hist.at(i)->GetXaxis()->SetTitle(xlabel);
    hist.at(i)->GetYaxis()->SetTitleSize(0.04);
    hist.at(i)->GetYaxis()->SetLabelSize(0.040);
    hist.at(i)->GetYaxis()->SetTitleOffset(1);
   //  decorate(hist.at(i),i);
    hist.at(i)->SetMarkerSize(1.5);
    hist.at(i)->SetMarkerStyle(20);
    hist.at(i)->SetMarkerColor(line_color[i]);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.5);
    hist.at(i)->GetXaxis()->SetLabelSize(0.04);
    hist.at(i)->GetXaxis()->SetLabelOffset(0.02);
    hist.at(i)->GetXaxis()->SetTitleOffset(1.2);

    legName.push_back(hist.at(i)->GetName());
    //leg_entry[i] = legend->AddEntry(hist.at(i),legend_texts[i].c_str(),"e2p");
    //leg_entry[i]->SetTextColor(hist.at(i)->GetLineColor());
    
    hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);
    hist.at(i)->GetYaxis()->SetRangeUser(ymin,ymax);
    cout<< xmin <<"\t"<<xmax<<endl;
    cout <<ymin << "\t" <<ymax<<endl; 
    //if(hist.at(i)->GetMaximum() > ymax) ymax = hist.at(i)->GetMaximum();
    //if(hist.at(i)->GetMinimum() < ymin) ymin = hist.at(i)->GetMinimum();

    

  }
  //if(ymin == 0.0) ymin = 1e-3;
  //if(ymin<0.0) ymin = 1e-4;
  //  if(ymax<=10) ymax=10;
  for(int i = 0;i<(int)hist.size(); i++) {
    if(!normalize & !log_flag) {int zmax=hist.at(i)->GetMaximum();
    hist.at(i)->GetZaxis()->SetRangeUser(0.0001,1.1*zmax);hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);hist.at(i)->GetYaxis()->SetRangeUser(ymin,ymax);
//===================================
/*if(Text){
int nbinsX = hist.at(i)->GetNbinsX();
int nbinsY = hist.at(i)->GetNbinsY();
double totalEntries = hist.at(i)->GetEntries();
for (int k = 1; k <= nbinsX; ++k) {
        for (int j = 1; j <= nbinsY; ++j) {
            double binContent = hist.at(i)->GetBinContent(k, j);
            if (binContent != 0) {
                // Calculate the fraction
                double fraction = binContent / totalEntries;

                // Round to 2 decimal places
                double roundedFraction = std::round(fraction * 100.0) / 100.0;  // Round to 2 decimal places

                // Set the rounded value back to the bin content
                hist.at(i)->SetBinContent(k, j, roundedFraction);
            }
        }
    }
}*/
//=======================================
}
    else if (!normalize && log_flag) {int zmax=hist.at(i)->GetMaximum();
    hist.at(i)->GetZaxis()->SetRangeUser(1,10*zmax);hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);hist.at(i)->GetYaxis()->SetRangeUser(ymin,ymax);}
    else
      {  
hist.at(i)->Scale(1.0 / hist.at(i)->Integral());
double zmax = hist.at(i)->GetMaximum();
hist.at(i)->GetZaxis()->SetRangeUser(0.00001,zmax);
       hist.at(i)->GetYaxis()->SetRangeUser(ymin,ymax);hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);
      }
    cout<<"i"<<i<<endl;
    if(Text){
    hist.at(i)->SetMarkerColor(kBlack); 
    if(i==0) {hist.at(i)->SetMinimum(0.001);
hist.at(i)->Draw("TEXT colz");}

    else hist.at(i)->Draw("colz+text same0");
    }	
    else {
      if(i==0) hist.at(i)->Draw("colz ");
    else hist.at(i)->Draw("colz sames");
    }
  }
  //legend->Draw();
  if(log_flag) {
      gPad->SetLogz();
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
const int nfiles=100;                                                                                                                                                             
TFile *f[nfiles];

struct MixedData {
     string str1;
     string str2;
     string str3;
     string str4;
     int intData;
     double double1;
     double double2;
     double double3;
     double double4;
 };


void generate2Dplot()
{
  char* hname = new char[200];
  
  char* hist_name = new char[200];
  
  char* title= new char[2000];
 
 // char *leg_head = new char[200];
 
  int n=0;
  int n_files=1;
 
    //f[0] = new TFile("plot.root");
    f[0] = new TFile("EB_plot.root");
    
  // vector<string> filetag=  {"Sample size = 112K"};
   //vector<vector<string>> legend_texts;  
    //legend_texts ={{"EE_XY_occupancy"}};
   vector<string> filetag=  {""};

MixedData varName[] = {
{"A gen mass vs pt","M_{a} vs p_{Ta}","M_{a} (GeV)", "p_{Ta} (GeV)",10,0,120,-0.5,2.5},
//{"A gen eta vs phi", "#eta_{a} vs #phi_{a}", "|#eta_{a}|","#phi_{a}", 10, -4,4, 1.4,2.6},
{"A gen eta vs phi", "#eta_{a} vs #phi_{a}", "#eta_{a}","#phi_{a}", 8, -4,4, -1.6,1.6},
{"Gen_eta1_vs_eta2","Gen #eta1 vs #eta2", "#eta1", "#eta2",10,-3,3,-3,3},
{"E_pho1_vs_E_pho2"," Energy of photons" ,"E_pho1 (GeV)", "E_pho2 (GeV)",10,0,800,0,800},
{"Angle vs gamma (240<= Ma <=260)","Angle vs Lorentz boost (240<= Ma <=260 MeV)" , "Lorentz boost (#gamma)","Angle",10,0,0.22,1,3000},
{"Angle vs gamma (490<= Ma <=510)","Angle vs Lorentz boost (490<= Ma <=510 MeV)","Lorentz boost (#gamma)","Angle",10,0,0.22,1,3000},
{"Angle vs gamma (740<= Ma <=760)","Angle vs Lorentz boost (740<= Ma <=760 MeV)","Lorentz boost (#gamma)","Angle",10,0,0.22,1,3000},
{"Angle vs gamma (990<= Ma <=1010)","Angle vs Lorentz boost (990<= Ma <=1010 MeV)","Lorentz boost (#gamma)","Angle",10,0,0.22,1,3000},
{"EE_XY_occupancy","ECAL Rechits (X-Y plane)", "X (in cm)", "Y (in cm)",10,-160,160,-160,160},
{"EE_XY_rechits_En_weighed", "ECAL rechits (X-Y plane) weighed by energy","X (in cm)", "Y (in cm)",10,-160,160,-160,160},
{"EE_eta_phi_occu","ECAL rechits (#eta-#phi plane)","|#eta|","#phi",10,-3.5,3.5,1,3.5},
{"EE_eta_phi_occu_En_weigh","ECAL rechits (#eta-#phi plane) weighed by energy","|#eta|","#phi",10,-3.5,3.5,1,3.5},
{"gen_dR", "Gen #Delta R between photons","#Delta #eta", "#Delta #phi", 200, 0,5,0,5},
{"gen_dr_pt_20_50","20 GeV <= p_{Ta} < 50 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dr_pt_50_80","50 GeV <= p_{Ta} < 80 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dr_pt_80_100","80 GeV <= p_{Ta} <= 100 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dR_ma_100","0.08 GeV < M_{a} < 0.12 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dR_ma_200","0.18 GeV < M_{a} < 0.22 GeV", "#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dR_ma_400","0.38 GeV < M_{a} < 0.42 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dR_ma_800","0.78 GeV < M_{a} < 0.82 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dR_ma_1000","0.98 GeV < M_{a} < 1.02 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dR_ma_1600","1.58 GeV < M_{a} < 1.62 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"gen_dR_ma_1800","1.78 GeV < M_{a} < 1.82 GeV","#Delta #eta_{#gamma1 #gamma2}","#Delta #phi_{#gamma1 #gamma2}",1,0,6,0,6},
{"Hit_noise_vs_Eta_Ma_100","0.08 GeV < M_{a} < 0.12 GeV","|#eta_{rechit}|","Rechit noise (GeV)",10,0,3,-2,5},
{"Hit_noise_vs_Eta_Ma_200","0.18 GeV < M_{a} < 0.22 GeV","|#eta_{rechit}|","Rechit noise (GeV)",10,0,3,-2,5},
{"Hit_noise_vs_Eta_Ma_400","0.38 GeV < M_{a} < 0.42 GeV","|#eta_{rechit}|","Rechit noise (GeV)",10,0,3,-2,5},
{"Hit_noise_vs_Eta_Ma_800","0.78 GeV < M_{a} < 0.82 GeV","|#eta_{rechit}|","Rechit noise (GeV)",10,0,3,-2,5},
{"Hit_noise_vs_Eta_Ma_1600","1.58 GeV < M_{a} < 1.62 GeV","|#eta_{rechit}|","Rechit noise (GeV)",10,0,3,-2,5},
{"Hit_noise_vs_Eta_Ma_1800","1.78 GeV < M_{a} < 1.82 GeV","|#eta_{rechit}|","Rechit noise (GeV)",10,0,3,-2,5},
};
/*  vector<string> varName;
 
*/
   vector<string> GEN ={"A gen mass vs pt","A gen eta vs phi","Gen #eta1 vs #eta2","E_pho1_vs_E_pho2","Angle vs gamma (240<= Ma <=260)","Angle vs gamma (490<= Ma <=510)","Gen_eta1_vs_eta2",
   "Angle vs gamma (740<= Ma <=760)","Angle vs gamma (990<= Ma <=1010)","gen_dR","gen_dr_pt_20_50","gen_dr_pt_50_80",
"gen_dr_pt_80_100","gen_dR_ma_100","gen_dR_ma_200", "gen_dR_ma_400","gen_dR_ma_800","gen_dR_ma_1000","gen_dR_ma_1600","gen_dR_ma_1800",} ;                 
  /* vector <string>  xLabel;

   "Ma = 0.99-1.01 GeV","EE XY occupancy","EE XY rechits weighed by energy","EE rechits (#eta-#phi)","EE rechits(#eta-#phi) weighed by energy"}; */
  /*vector <int> rebin;
  cout <<xLabel[0]<<endl;*/
vector<string> loghist={""};
 // vector<string> loghist  ={"Hit_noise_vs_Eta_Ma_100","Hit_noise_vs_Eta_Ma_200","Hit_noise_vs_Eta_Ma_400","Hit_noise_vs_Eta_Ma_800","Hit_noise_vs_Eta_Ma_1600","Hit_noise_vs_Eta_Ma_1800"} ;        
  vector<string> text = {"gen_dR","gen_dr_pt_20_50","gen_dr_pt_50_80","gen_dr_pt_80_100","gen_dR_ma_100","gen_dR_ma_200", "gen_dR_ma_400","gen_dR_ma_800","gen_dR_ma_1000","gen_dR_ma_1600","gen_dR_ma_1800"};                                                                                                     

  bool flag=false;
 
  sprintf(hname,"temp.root");
  TFile* fout = new TFile(hname,"RECREATE");
 
    n_files=1;  
    
  for(int i_file=0; i_file<n_files;i_file++)
    {      
     
      for(int i_cut=0; i_cut<size(varName);i_cut++)
	{
	  vector<TH2F*> hist_list;
          string Title = varName[i_cut].str2;
          string xLabel = varName[i_cut].str3;
          string yLabel = varName[i_cut].str4;
	  int rebin = varName[i_cut].intData;
          double ymin = varName[i_cut].double1;
          double ymax = varName[i_cut].double2;
          double xmin = varName[i_cut].double3;
          double xmax = varName[i_cut].double4;

	  sprintf(hist_name,"%s",varName[i_cut].str1.c_str());
	  cout<<hist_name<<"\t"<<i_cut<<"\t"<<i_file<<"\t"<<f[i_file]->GetName()<<endl;
          
	  TH2F* h_resp2 = (TH2F*)f[i_file]->Get(hist_name); // SR
	  h_resp2->GetXaxis()->SetTitle(xLabel.c_str());
	  h_resp2->GetYaxis()->SetTitle(yLabel.c_str());
	  //cout<<"resp2 "<<h_resp2->Integral()<<"\t"<<rebin[i_cut]<<"\t"<<xmin[i_cut]<<"\t"<<xmax[i_cut]<<endl;
	  cout<<"I_cut"<<"\t"<<i_cut<<endl;
	  h_resp2->RebinX(rebin);
	  h_resp2->RebinY(rebin);
	 
	  
	  //h_resp2= setMyRange(h_resp2,xmin[i_cut],xmax[i_cut]+0.01*xmax[i_cut]);
	  //setLastBinAsOverFlow(h_resp2);
	 	  
	  hist_list.push_back(h_resp2); 
	
	  	 
	  cout<<h_resp2->Integral()<<"\t"<<f[i_file]->GetName()<<endl;	 
	  cout<<" hist_list.size() "<<hist_list.size()<<"\t "<<endl;
 
string hname = hist_name;
         
    int gen = count(GEN.begin(),GEN.end(),varName[i_cut].str1);
	  int LOG = count(loghist.begin(), loghist.end(),varName[i_cut].str1);
    int text_ = count(text.begin(),text.end(), varName[i_cut].str1);
    string hst_name = to_string(2000 + i_cut) +"_" + hname;
    if(gen){hst_name = "GEN_"+ hst_name;}
    else{hst_name= "RECO_"+hst_name;}
	  if(LOG){ 
	  generate_2Dplot(hist_list,(hst_name + "_log").c_str(),xLabel.c_str(),yLabel.c_str(),rebin,ymin,ymax,xmin,xmax,false,true,false,false,true,Title.c_str());
	  }
	  else {
          if(text_){string hst_name1 = hst_name + "_txt";
generate_2Dplot(hist_list,hst_name1.c_str(),xLabel.c_str(),yLabel.c_str(),rebin,ymin,ymax,xmin,xmax,true,false,false,true,true,Title.c_str());} else 
generate_2Dplot(hist_list,hst_name.c_str(),xLabel.c_str(),yLabel.c_str(),rebin,ymin,ymax,xmin,xmax,false,false,false,false,true,Title.c_str());
          }
	}
      //fout->Close();
      
    }
    }
    
