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

void generate_2Dplot(vector<TH2F*> hist,char const *tag_name="",char const *xlabel="",char const *ylabel="",  int rebin=-1,double ymin=0,double ymax=0,int xmin=-1,int xmax=-1,
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
    hist.at(i)->SetMarkerSize(0.8);
    hist.at(i)->SetMarkerStyle(20);
    hist.at(i)->SetMarkerColor(line_color[i]);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.5);
    hist.at(i)->GetXaxis()->SetLabelSize(0.04);

    legName.push_back(hist.at(i)->GetName());
    //leg_entry[i] = legend->AddEntry(hist.at(i),legend_texts[i].c_str(),"e2p");
    //leg_entry[i]->SetTextColor(hist.at(i)->GetLineColor());
    
     hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);
    hist.at(i)->GetYaxis()->SetRangeUser(ymin,ymax); 
    //if(hist.at(i)->GetMaximum() > ymax) ymax = hist.at(i)->GetMaximum();
    //if(hist.at(i)->GetMinimum() < ymin) ymin = hist.at(i)->GetMinimum();

    

  }
  //if(ymin == 0.0) ymin = 1e-3;
  //if(ymin<0.0) ymin = 1e-4;
  //  if(ymax<=10) ymax=10;
  for(int i = 0;i<(int)hist.size(); i++) {
    if(!normalize) {int zmax=hist.at(i)->GetMaximum();
    hist.at(i)->GetZaxis()->SetRangeUser(0.0001,1.1*zmax);hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);hist.at(i)->GetYaxis()->SetRangeUser(ymin,ymax);}
    else
      {  hist.at(i)->GetZaxis()->SetRangeUser(0.00001,1.1);
       hist.at(i)->GetYaxis()->SetRangeUser(ymin,ymax);hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);
      }
    cout<<"i"<<i<<endl;
    if(Text){
    if(i==0) hist.at(i)->Draw("colz+text ");
    else hist.at(i)->Draw("colz+text sames");
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

void generate2Dplot()
{
  char* hname = new char[200];
  
  char* hist_name = new char[200];
  
  char* title= new char[2000];
 
 // char *leg_head = new char[200];
 
  int n=0;
  int n_files=1;
 
    f[0] = new TFile("plot.root");
    
   vector<string> filetag=  {"Sample size = 112K"};
   //vector<vector<string>> legend_texts;  
    //legend_texts ={{"EE_XY_occupancy"}};

  vector<string> varName;
 
   varName = {"A gen mass vs pt","A gen eta vs phi","Gen #eta1 vs #eta2","E_pho1_vs_E_pho2","Angle vs gamma (240<= Ma <=260)","Angle vs gamma (490<= Ma <=510)",
   "Angle vs gamma (740<= Ma <=760)","Angle vs gamma (990<= Ma <=1010)","EE_XY_occupancy","EE_XY_rechits_En_weighed","EE_eta_phi_occu","EE_eta_phi_occu_En_weigh" };    

   vector<string> GEN ={"A gen mass vs pt","A gen eta vs phi","Gen #eta1 vs #eta2","E_pho1_vs_E_pho2","Angle vs gamma (240<= Ma <=260)","Angle vs gamma (490<= Ma <=510)",
   "Angle vs gamma (740<= Ma <=760)","Angle vs gamma (990<= Ma <=1010)"} ;                 
   vector <string>  xLabel;

  xLabel={"Mass (GeV)","|#eta|","#eta1","Energy (GeV)","Lorentz boost (#gamma)","Lorentz boost (#gamma)","Lorentz boost (#gamma)","Lorentz boost (#gamma)","X (in cm)","X (in cm)","|#eta|","|#eta|" };  
  vector<string> yLabel;
  yLabel={"pT (GeV)","#phi","#eta2","Energy","Angle","Angle","Angle","Angle","Y (in cm)","Y (in cm)","#phi", "#phi"};
   vector<string> Title;
   Title = {"Mass vs pT of A","#eta vs #phi of A","#eta1 vs #eta2","E_pho1 vs E_pho2","Ma = 0.24-0.26 GeV","Ma = 0.49-0.51 GeV","Ma = 0.74-0.76 GeV",
   "Ma = 0.99-1.01 GeV","EE XY occupancy","EE XY rechits weighed by energy","EE rechits (#eta-#phi)","EE rechits(#eta-#phi) weighed by energy"}; 
  vector<string> loghist  ={""} ;                                                                                                              
  vector <int> rebin;
  rebin={10,10,10,5,5,5,5,10,9,9,10,10};

  vector<double> ymin ={0,  -4,   -3,       0,   0,    0,    0,       0,    -160,   -160,   -3.5 ,  3.5};
  vector<double> ymax={120  ,4,    3,     800,   0.2,  0.2,  0.2,     0.2,   160,    160,    3.5 ,  3.5};
  vector<double> xmin ={0,  1.1,  -3,       0,   0,    0,    0,       0,     -160,   -160,     1 ,  1};
  vector<double> xmax={3,   3,     3,     800,   2500, 2500, 2500,    2500,   160,    160,    4,  4};

  cout<<"different vector sizes "<<endl;
  cout<<varName.size()<<"\t"<<xLabel.size()<<"\t"<<rebin.size()<<"\t"<<xmax.size()<<"\t"<<xmin.size()<<endl;
  cout <<xLabel[0]<<endl;
  bool flag=false;
 
  sprintf(hname,"temp.root");
  TFile* fout = new TFile(hname,"RECREATE");
 
    n_files=1;  
    
  for(int i_file=0; i_file<n_files;i_file++)
    {      
     
      for(int i_cut=0; i_cut<varName.size();i_cut++)
	{
	  vector<TH2F*> hist_list;
	  
	  sprintf(hist_name,"%s",varName[i_cut].c_str());
	  cout<<hist_name<<"\t"<<i_cut<<"\t"<<i_file<<"\t"<<f[i_file]->GetName()<<endl;
          
	  TH2F* h_resp2 = (TH2F*)f[i_file]->Get(hist_name); // SR
	  h_resp2->GetXaxis()->SetTitle(xLabel[i_cut].c_str());
	  h_resp2->GetYaxis()->SetTitle(yLabel[i_cut].c_str());
	  //cout<<"resp2 "<<h_resp2->Integral()<<"\t"<<rebin[i_cut]<<"\t"<<xmin[i_cut]<<"\t"<<xmax[i_cut]<<endl;
	  cout<<"I_cut"<<"\t"<<i_cut<<endl;
	  h_resp2->RebinX(rebin[i_cut]);
	  h_resp2->RebinY(rebin[i_cut]);
	 
	  
	  //h_resp2= setMyRange(h_resp2,xmin[i_cut],xmax[i_cut]+0.01*xmax[i_cut]);
	  //setLastBinAsOverFlow(h_resp2);
	 	  
	  hist_list.push_back(h_resp2); 
	
	  	 
	  cout<<h_resp2->Integral()<<"\t"<<f[i_file]->GetName()<<endl;	 
	  cout<<" hist_list.size() "<<hist_list.size()<<"\t "<<endl;
 
string hname = hist_name;
         
    int gen = count(GEN.begin(),GEN.end(),varName[i_cut]);
	  int LOG = count(loghist.begin(), loghist.end(),varName[i_cut]);
    string hst_name = to_string(2000 + i_cut) +"_" + hname;
    if(gen){hst_name = "GEN_"+ hst_name;}
    else{hst_name= "RECO_"+hst_name;}
	  if(LOG){
	  generate_2Dplot(hist_list,hst_name.c_str(),xLabel[i_cut].c_str(),yLabel[i_cut].c_str(),rebin[i_cut],ymin[i_cut],ymax[i_cut],xmin[i_cut],xmax[i_cut],false,true,false,false,true,Title[i_cut].c_str());
	  }
	  else {
generate_2Dplot(hist_list,hst_name.c_str(),xLabel[i_cut].c_str(),yLabel[i_cut].c_str(),rebin[i_cut],ymin[i_cut],ymax[i_cut],xmin[i_cut],xmax[i_cut],false,false,false,false,true,Title[i_cut].c_str());
          }
	}
      //fout->Close();
      
    }
    }
    
