///////////////////////////////////////////////////////////////////////////////////////////////////
///
///    Plotting macro for NN NTuples
///    Features: FF method, NN output categorization, unrolled distribution for acoplanarity angle
///    Author: Andrea Cardini ( andrea.cardini@desy.de , andrea.cardini@cern.ch )
///
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include "DesyTauAnalyses/NTupleMaker/test/Plotting.h"
#include "DesyTauAnalyses/NTupleMaker/test/Plotting_Style.h"
#include "DesyTauAnalyses/NTupleMaker/test/HttStylesNew.cc"
#include "TPad.h"
#include "TROOT.h"
#include "TColor.h"
#include "TEfficiency.h"
#include "TMath.h"


bool DeepTau = true;

void Plot_lept_mutau_NNNTuples(TString Variable = "m_fast",
			       TString xtitle = "m_{#tau#tau} [GeV]",
			       int nBins  =   25,
			       float xmin =    0,
			       float xmax =  250,
			       TString Weight = "weight*",
			       TString Cut="(pt_1>21&&os>0.5&&puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5&&abs(eta_1)<2.1&&((trg_singlemuon&&pt_1>25)))*",
			       TString ytitle = "Events",
			       int categoryIndex=-1,
			       TString directory = "/nfs/dust/cms/user/cardinia/HtoTauTau/HiggsCP/DNN/Jan20/CMSSW_10_2_16/src/HiggsCP/Inputs/test/NTuples_mt_2018_v2/",
			       TString outputDir = "./figures_March5/",
			       int era=2018,
			       bool FFmethod = true,
			       bool useEmbedded = true,
			       bool LargeScale = false,  
			       bool logY = false,
			       bool showSignal = true,
			       bool compareCP = false,
			       int scaleSignal = 100.,
			       bool blindData = true,
			       bool FORCE = false
			       )
{
  using namespace std;
  //if(era!=2017)compareCP=false;
  if(categoryIndex>=0){
    Cut+="(predicted_class=="+TString::Itoa(categoryIndex,10)+")*";
  }
	
  TString VariableName=Variable;
  TString yVar,xVar;
  bool var2D=false;
  if(Variable.Contains(":")){
    TObjArray *array = Variable.Tokenize(":");
    yVar=array->At(0)->GetName();
    xVar=array->At(1)->GetName();
    TString range=to_string(xmax-xmin).c_str();
    if(categoryIndex==1){
      nBins=nBins*5;
      xmax+=4*(xmax-xmin);
      Variable=xVar+"*("+yVar+"<0.3)+(("+range+"+"+xVar+")*("+yVar+">=0.3&&"+yVar+"<0.5))+((2*"+range+"+"+xVar+")*("+yVar+">=0.5&&"+yVar+"<0.65))+((3*"+range+"+"+xVar+")*("+yVar+">=0.65&&"+yVar+"<0.85))+((4*"+range+"+"+xVar+")*("+yVar+">=0.85))";
    }else{
      nBins=nBins*3;
      xmax+=2*(xmax-xmin);
      Variable=xVar+"*("+yVar+"<0.3)+(("+range+"+"+xVar+")*("+yVar+">=0.3&&"+yVar+"<0.5))+((2*"+range+"+"+xVar+")*("+yVar+">=0.5))";//&&"+yVar+"<0.6))+((3*"+range+"+"+xVar+")*("+yVar+">=0.6))";
    }
    VariableName="Unrolled_"+xVar;
    var2D=true;
  }else if(Variable.Contains("*")){
    TObjArray *array = Variable.Tokenize("*");
    VariableName=array->At(0)->GetName();
  }
  TString TauIso="mva17_2";
  if(DeepTau)TauIso="byMediumDeepTau2017v2p1VSjet_2";
  TString FFweight="ff_nom";
  if(DeepTau)FFweight="ff_mva";
  TString IsoCut=Cut+"("+TauIso+">0.5)*";
  TString AntiIsoCut=Cut+"("+TauIso+"<0.5)*";
  // directory="$CMSSW_BASE/src/"+directory;
  TH1::SetDefaultSumw2();
  SetStyle();

  // Simple check to prevent accidental unblinding in SR, to unblind set FORCE to True
  if(!FORCE&&(categoryIndex==0||categoryIndex==1)){
    blindData=true;
  }

  // weights
  TString topweight("*1");
  TString Wjets_weight("*0.96");
  TString qcdweight("1.06*");
  TString zptmassweight="*1.0";                  //TO DO: CHANGE WEIGHTs
 
  vector<TString> sampleNames;
  if(directory.Contains("Out")){
    sampleNames = {
      "mt-NOMINAL_ntuple_data", // data (0)
      "mt-NOMINAL_ntuple_DY",// (1)Drell-Yan Z->TT  or Embedded
      "mt-NOMINAL_ntuple_DY", // (2)Drell-Yan Z->LL
      "mt-NOMINAL_ntuple_W",// (3)WJets
      "mt-NOMINAL_ntuple_TT",//(4)TTbar leptonic, hadronic, + semileptonic
      "mt-NOMINAL_ntuple_ST", // (5) SingleTop tW tbar, SingleTop tW t, SingleTop t antitop, SingleTop t top
      "mt-NOMINAL_ntuple_VV",// (6) WW, WZ, ZZ
      "mt-NOMINAL_ntuple_ggH125", // (7) Scalar ggH
      "mt-NOMINAL_ntuple_qqH125", // (8) Scalar VBF H
      "mt-NOMINAL_ntuple_ggH125", // (9) Pseudoscalar ggH
      "mt-NOMINAL_ntuple_qqH125" // (10) Pseudoscalar VBF
    };
  }else{
    sampleNames = {
      "mt-NOMINAL_ntuple_SingleMuon", // data (0)
      "mt-NOMINAL_ntuple_DYJets",// (1)Drell-Yan Z->TT
      "mt-NOMINAL_ntuple_DYJets", // (2)Drell-Yan Z->LL
      "mt-NOMINAL_ntuple_WJets",// (3)WJets
      "mt-NOMINAL_ntuple_TTbar",//(4)TTbar leptonic, hadronic, + semileptonic
      "mt-NOMINAL_ntuple_SingleTop", // (5) SingleTop tW tbar, SingleTop tW t, SingleTop t antitop, SingleTop t top
      "mt-NOMINAL_ntuple_Diboson",// (6) WW, WZ, ZZ
      "mt-NOMINAL_ntuple_GluGluHToUncorrTauTau", // (7) Scalar ggH
      "mt-NOMINAL_ntuple_VBFHToUncorrTauTau", // (8) Scalar VBF H
      "mt-NOMINAL_ntuple_GluGluHToUncorrTauTau", // (9) Pseudoscalar 
      "mt-NOMINAL_ntuple_VBFHToUncorrTauTau" // (10) Scalar VBF H
    }; 
  }
  if(useEmbedded&&!directory.Contains("Out"))sampleNames[1]="mt-NOMINAL_ntuple_EmbeddedMuTau";
  else if(useEmbedded&&directory.Contains("Out"))sampleNames[1]="mt-NOMINAL_ntuple_EMB";
  const int nSamples = sampleNames.size(); //DY is used twice, for Zll and Ztt
  cout<<"this are the samples"<<endl;
  if(!directory.Contains("Out")) for (int i=0; i<nSamples; ++i) {
      sampleNames[i]+="_";
      sampleNames[i]+=era;
      cout << endl << sampleNames[i] << ":" << endl;}

  // *******************************
  // ***** Selection Cuts    *******
  // *******************************

  TString cuts[nSamples];
  TString cutsSS[nSamples];
  TString cutsaIso[nSamples];

  // MC specific cuts to select certain type of particle
  TString isZTT="*(gen_match_2==5&&gen_match_1==4)";
  TString isZLL="*!(gen_match_2==5&&gen_match_1==4)";

  // Selection cuts applied to all samples
  for (int i=1; i<nSamples; ++i){
    cuts[i]   = IsoCut+Weight+"(os>0.5)";
    cutsSS[i] = IsoCut+Weight+qcdweight+"(os<0.5)";
    cutsaIso[i] = AntiIsoCut+Weight+"(os>0.5)*"+FFweight+"*(gen_match_2!=6)";
  }

  //specific selection weights for data, DY and top
  cuts[0] = IsoCut+"(os>0.5)"; //DATA
  if(useEmbedded){
    cuts[1] = IsoCut+"(os>0.5)*weight*(weight<1000)"; //Embedded, i.e. data
    cuts[2] += zptmassweight;

  }else{
    cuts[1] += zptmassweight+isZTT;
    cuts[2] += zptmassweight+isZLL;
  }
  cuts[3] += Wjets_weight;
  cuts[4] += topweight; 
  cuts[7] += "*"+TString::Itoa(scaleSignal,10);
  cuts[8] += "*"+TString::Itoa(scaleSignal,10);
  cuts[9] += "*"+TString::Itoa(scaleSignal,10);
  cuts[10]+= "*"+TString::Itoa(scaleSignal,10);
  if(compareCP){
    cuts[7] +="*gen_sm_htt125*(gen_sm_htt125>=0)";
    cuts[8] +="*gen_sm_htt125*(gen_sm_htt125>=0)";
    cuts[9] +="*gen_ps_htt125*(gen_ps_htt125>=0)";
    cuts[10] +="*gen_ps_htt125*(gen_ps_htt125>=0)";
  }    
  if(FFmethod) for(int i=2; i<7; ++i) cuts[i] += "*(gen_match_2!=6)";
  if(useEmbedded) for(int i=2; i<7; ++i) cuts[i] += "*!(gen_match_2==5 &&gen_match_1==4)";

   
  cutsSS[0] = IsoCut+qcdweight+"(os<0.5)";
  if(useEmbedded){
    cutsSS[1] = IsoCut+qcdweight+"(os<0.5)*weight*(weight<1000)";
    cutsSS[2] += zptmassweight;
  }else{
    cutsSS[1] += zptmassweight+isZTT;
    cutsSS[2] += zptmassweight+isZLL;
  }
  cutsSS[2] += zptmassweight+isZLL;
  cutsSS[3] += Wjets_weight; 
  cutsSS[4] += topweight; 
  cutsSS[7] += "*"+TString::Itoa(scaleSignal,10);
  cutsSS[8] += "*"+TString::Itoa(scaleSignal,10);
  cutsSS[9] += "*"+TString::Itoa(scaleSignal,10);
  cutsSS[10]+= "*"+TString::Itoa(scaleSignal,10);
 if(compareCP){
    cutsSS[7] +="*gen_sm_htt125*(gen_sm_htt125>=0)";
    cutsSS[8] +="*gen_sm_htt125*(gen_sm_htt125>=0)";
    cutsSS[9] +="*gen_ps_htt125*(gen_ps_htt125>=0)";
    cutsSS[10] +="*gen_ps_htt125*(gen_ps_htt125>=0)";
  }  
  if(useEmbedded) for(int i=2; i<7; ++i)cutsSS[i] += "*!(gen_match_2==5 &&gen_match_1==4)";

  cutsaIso[0] = AntiIsoCut+"(os>0.5)*"+FFweight;
  if(useEmbedded){
    cutsaIso[1] = AntiIsoCut+"(os>0.5)*weight*(weight<1000)*"+FFweight;
    cutsaIso[2] += zptmassweight;
 }else{
    cutsaIso[1] += zptmassweight+isZTT;
    cutsaIso[2] += zptmassweight+isZLL;
  }
  cutsaIso[2] += zptmassweight+isZLL;
  cutsaIso[3] += Wjets_weight; 
  cutsaIso[4] += topweight; 
  cutsaIso[7] += "*"+TString::Itoa(scaleSignal,10);
  cutsaIso[8] += "*"+TString::Itoa(scaleSignal,10);
  cutsaIso[9] += "*"+TString::Itoa(scaleSignal,10);
  cutsaIso[10]+= "*"+TString::Itoa(scaleSignal,10);
  if(compareCP){
    cutsaIso[7] +="*gen_sm_htt125*(gen_sm_htt125>=0&&gen_sm_htt125<7)";
    cutsaIso[8] +="*gen_sm_htt125*(gen_sm_htt125>=0)";
    cutsaIso[9] +="*gen_ps_htt125*(gen_ps_htt125>=0)";
    cutsaIso[10] +="*gen_ps_htt125*(gen_ps_htt125>=0)";
  }  
  if(useEmbedded) for(int i=2; i<7; ++i)cutsaIso[i] += "*!(gen_match_2==5 && gen_match_1==4)";
  // *******************************
  // ***** Filling Histograms ******
  // *******************************

  TH1D * hist[nSamples];
  TH1D * histSS[nSamples];
  TH1D * hist_AntiIso[nSamples];
  TCanvas * dummyCanv = new TCanvas("dummy","",500,500);

  // Draw main selection for all histograms in sampleNames
  for (int i=0; i<nSamples; ++i) {
    //if(!compareCP||i>=9)continue;		
    // Reading input file
    TFile * file = new TFile( directory + sampleNames[i] + ".root");
    TTree * tree = (TTree*)file->Get("TauCheck"); 
    
    // Name and initialize histograms
    TString histName   = sampleNames[i] + VariableName + "_os";
    TString histNameSS = sampleNames[i] + VariableName + "_ss";
    TString histNameaIso   = sampleNames[i] + VariableName + "_aIso";
		
    hist[i]   = new TH1D(histName,"",nBins,xmin,xmax);
    histSS[i] = new TH1D(histNameSS,"",nBins,xmin,xmax);
    hist_AntiIso[i] = new TH1D(histNameaIso,"",nBins,xmin,xmax);
		
    cout << "Drawing ..." << endl;
    tree->Draw(Variable+">>"+histName,cuts[i]);
    cout << cuts[i] <<endl;
    tree->Draw(Variable+">>"+histNameSS,cutsSS[i]);
    tree->Draw(Variable+">>"+histNameaIso,cutsaIso[i]);
    cout << sampleNames[i] << " : Entries = " << hist[i]->GetEntries() << " : Integral = " << hist[i]->Integral(0,nBins+1) << endl;
  }


  cout << endl;
  delete dummyCanv;



  // ********************************************
  // ***** Adding similar backgrounds     *******
  // ********************************************

  // Adding up single top and VV backgrounds
  hist[5]->Add(hist[5],hist[6]);
  
  // Adding SS backgrounds
  for (int iH=2; iH<6; iH++) histSS[1]->Add(histSS[iH]);

  // Adding antiIso backgrounds
  for (int iH=2; iH<6; iH++) hist_AntiIso[1]->Add(hist_AntiIso[iH]);
  
  // ********************************************
  // ***** QCD background estimation      *******
  // ********************************************

  float dataSS     = histSS[0]->GetSumOfWeights();
  float dataSSfull = histSS[0]->Integral(0,nBins+1);
  
  // Subtracting background from SS
  histSS[0]->Add(histSS[0],histSS[1],1,-1);

  // Subtracting true taus from anti-Iso data
  hist_AntiIso[0]->Add(hist_AntiIso[0],hist_AntiIso[1],1,-1);

  float nonQCD             = histSS[1]->GetSumOfWeights();
  float nonQCDfull         = histSS[1]->Integral(0,nBins+1);
  float nonQCDfraction     = nonQCD/dataSS;
  float nonQCDfractionFull = nonQCDfull/dataSSfull;

  cout << endl;
  cout << "SS region :    " << endl;
  cout << "W  (MC)      : " << histSS[4]->GetSumOfWeights() << " : "<< histSS[4]->Integral(0,nBins+1) << endl;
  cout << "non-QCD (MC) : " << nonQCD << " : " << nonQCDfull << endl;
  cout << "data         : " << dataSS << " : " << dataSSfull << endl;
  cout << "non-QCD fraction : " << nonQCDfraction << " : " << nonQCDfractionFull << endl; 
  cout << endl;

  // ************************************
  // ***** Summarize backgrounds  *******
  // ************************************

  TH1D * histData   = (TH1D*)hist[0]         -> Clone("data_obs");
  TH1D * QCD        = (TH1D*)histSS[0]       -> Clone("QCD");
  TH1D * ZTT        = (TH1D*)hist[1]         -> Clone("ZTT");
  TH1D * ZLL        = (TH1D*)hist[2]         -> Clone("ZLL");
  TH1D * W          = (TH1D*)hist[3]         -> Clone("W");
  TH1D * TT         = (TH1D*)hist[4]         -> Clone("TT"); 
  TH1D * VV         = (TH1D*)hist[5]         -> Clone("VV"); 
  TH1D * ggH        = (TH1D*)hist[7]         -> Clone("ggH");
  TH1D * qqH        = (TH1D*)hist[8]         -> Clone("qqH");
  TH1D * CPoddH     = NULL;
  TH1D * CPoddqqH   = NULL;
  if(compareCP){
    CPoddH     = (TH1D*)hist[9]         -> Clone("CPoddH");
    CPoddqqH   = (TH1D*)hist[10]        -> Clone("CPoddqqH");
  }
  TH1D * Fakes      = (TH1D*)hist_AntiIso[0] -> Clone("Fakes");
  
  for(int i=0;i<nSamples;i++){
    //if(!compareCP&&i>=9)continue;
    cout << setw(nSamples) << sampleNames[i] << " : Entries = " << hist[i]->GetEntries() << " : Integral = " << hist[i]->Integral(0,nBins+1) << endl;
  }

  cout << endl;
  cout << "QCD : Sum of weights = " << QCD->GetSumOfWeights() << " : Integral = " << QCD->Integral(1,nBins+1) << endl;
  cout << "VV  : Sum of weights = " << VV->GetSumOfWeights()  << " : Integral = " << VV->Integral(1,nBins+1)  << endl;
  cout << "W   : Sum of weights = " << W->GetSumOfWeights()   << " : Integral = " << W->Integral(1,nBins+1)   << endl;
  cout << "TT  : Sum of weights = " << TT->GetSumOfWeights()  << " : Integral = " << TT->Integral(1,nBins+1)  << endl;
  cout << "ZLL : Sum of weights = " << ZLL->GetSumOfWeights() << " : Integral = " << ZLL->Integral(1,nBins+1) << endl;
  cout << "ZTT : Sum of weights = " << ZTT->GetSumOfWeights() << " : Integral = " << ZTT->Integral(1,nBins+1) << endl;
  cout << "Fakes : Sum of weights = " << Fakes->GetSumOfWeights() << " : Integral = " << Fakes->Integral(1,nBins+1) << endl;


  if(FFmethod){
    cout << endl;
  cout << "************************" << endl;
  cout << "True Taus = " << VV->Integral(1,nBins+1)+W->Integral(1,nBins+1)+TT->Integral(1,nBins+1)+ZLL->Integral(1,nBins+1)+ZTT->Integral(1,nBins+1) << endl;
  cout << "True Taus + Fakes = " << VV->Integral(1,nBins+1)+W->Integral(1,nBins+1)+TT->Integral(1,nBins+1)+ZLL->Integral(1,nBins+1)+ZTT->Integral(1,nBins+1)+Fakes->Integral(1,nBins+1) << endl;
  cout << "************************" << endl;
  cout << endl;

  }else {
    cout << endl;
  cout << "************************" << endl;
  cout << "MC = " << VV->Integral(1,nBins+1)+W->Integral(1,nBins+1)+TT->Integral(1,nBins+1)+ZLL->Integral(1,nBins+1)+ZTT->Integral(1,nBins+1) << endl;
  cout << "MC + QCD = " << VV->Integral(1,nBins+1)+W->Integral(1,nBins+1)+TT->Integral(1,nBins+1)+ZLL->Integral(1,nBins+1)+ZTT->Integral(1,nBins+1)+QCD->Integral(1,nBins+1) << endl;
  cout << "************************" << endl;
  cout << endl;


  }


  cout << endl;
  cout << "************************" << endl;
  cout << "Fake taus = " << VV->Integral(1,nBins+1)+W->Integral(1,nBins+1)+QCD->Integral(1,nBins+1) << endl;
  cout << "************************" << endl;
  cout << endl;

  float nData    = histData->GetSumOfWeights();
  float nTT      = TT->GetSumOfWeights();
  float nW       = W->GetSumOfWeights();
  float eData    = TMath::Sqrt(nData);
  float nNonTT   = VV->GetSumOfWeights() + ZTT->GetSumOfWeights() + ZLL->GetSumOfWeights() + QCD->GetSumOfWeights() + W->GetSumOfWeights();
  float nNonW    = VV->GetSumOfWeights() + ZTT->GetSumOfWeights() + ZLL->GetSumOfWeights() + QCD->GetSumOfWeights() + TT->GetSumOfWeights();
  float ttScale  = (nData-nNonTT)/nTT;
  float ttScaleE = eData/nTT;
  float bkgE     = 0.3*nNonTT/nTT;
  float WScale   = (nData-nNonW)/nW;
  float WScaleE  = eData/nW;
  float WbkgE    = 0.3*nNonW/nW;

  cout << endl;
  cout << "************************" << endl;
  cout << "TT scale factor = " << ttScale << " +/- " << ttScaleE << " +/- " << bkgE << endl;
  cout << "W scale factor = " << WScale << " +/- " << WScaleE << " +/- " << WbkgE << endl;
  cout << "************************" << endl;
  cout << endl;

  ///////////////////////////////////////////////////////////////////////////////////////////////
  // FINAL PLOTTING 
  ///////////////////////////////////////////////////////////////////////////////////////////////

  ModTDRStyle();
  TCanvas* canv1;
  if(LargeScale)canv1 = new TCanvas("c1", "c1", 2000,800);
  else canv1 = new TCanvas("c1", "c1", 1200,1000);
  canv1->cd();
  vector<TPad*> pads = TwoPadSplit(0.29, 0.00, 0.00);
  pads[0]->SetLogy(logY);

  vector<TH1*> h = CreateAxisHists(2, histData, histData->GetXaxis()->GetXmin(), histData->GetXaxis()->GetXmax()-0.01);
  //h[0]->GetYaxis()->SetMaxDigits(3);
  h[0] -> Draw();

  string units="";
  string xtitle_ = (string) xtitle;
  size_t pos = xtitle_.find("[");
  if(pos!=string::npos) {
    units = xtitle_.substr(pos+1, xtitle_.find("]") - pos -1 );
    xtitle_ = xtitle_.substr(0, pos);
  }

  pads[1] -> cd();
  h[1]    -> Draw();
  SetupTwoPadSplitAsRatio(pads, "Obs/Exp", true, 0.65, 1.35);
  StandardAxes(h[1]->GetXaxis(), h[0]->GetYaxis(),xtitle_ ,units);
  h[1] -> GetYaxis()->SetNdivisions(4);
  h[1] -> GetXaxis()->SetTitleOffset(0.95);
  h[1] -> GetXaxis()->SetNdivisions(505);
  h[1] -> GetYaxis()->SetTitleOffset(1.1);
  if(LargeScale)h[1] -> GetYaxis()->SetTitleOffset(0.9);
  pads[0] -> cd();
  h[0] -> GetYaxis()->SetTitleOffset(1.6);
  if(LargeScale)h[0] -> GetYaxis()->SetTitleOffset(1);
  pads[1] -> SetGrid(0,1);
  //it complains if the minimum is set to 0 and you try to set log y scale
  if(logY) h[0] -> SetMinimum(1);
  pads[0] -> cd();

  // Setup legend
  TLegend *legend;
  if(categoryIndex==5)legend = PositionedLegend(0.35, 0.20, 2, 0.03);
  else legend = PositionedLegend(0.35, 0.20, 3, 0.03);
  legend -> SetTextFont(42);
  legend->SetNColumns(2);
  histData -> SetMarkerColor(1);
  histData -> SetLineColor(1);
  histData -> SetFillColor(1);
  histData -> SetFillStyle(0);
  histData -> SetLineWidth(2);
  histData -> SetMarkerStyle(20);
  histData -> SetMarkerSize(1.1);
  /*
  InitHist(QCD,TColor::GetColor("#FFCCFF"));
  InitHist(ZLL,TColor::GetColor("#DE5A6A"));
  InitHist(TT,TColor::GetColor("#9999CC"));
  InitHist(VV,TColor::GetColor("#6F2D35"));
  InitHist(ZTT,TColor::GetColor("#FFCC66"));
  InitHist(W,TColor::GetColor("#4496C8"));
  InitHist(Fakes,TColor::GetColor("#c6f74a"));
  */
  InitHist(QCD,TColor::GetColor("#FFCCFF"));
  InitHist(ZLL,TColor::GetColor(100,192,232));
  InitHist(TT,TColor::GetColor(155,152,204));
  InitHist(VV,TColor::GetColor(222,90,106));
  InitHist(ZTT,TColor::GetColor(248,206,104));
  InitHist(W,TColor::GetColor("#4496C8"));
  InitHist(Fakes,TColor::GetColor(192,232,100));

  legend -> AddEntry(histData, "Observed", "ple");
  if(useEmbedded) legend -> AddEntry(ZTT,"Embedded","f");
  else legend -> AddEntry(ZTT,"Z#rightarrow #tau#tau","f");
  legend -> AddEntry(TT,"t#bar{t}","f");
  legend -> AddEntry(ZLL,"Z#rightarrow #mu#mu/ee","f");
  if(FFmethod)legend -> AddEntry(Fakes,"j#rightarrow #tau_{h}","f");
  else{
  legend -> AddEntry(QCD,"QCD","f");
  
  legend -> AddEntry(W,"W+jets","f");
  }
  legend -> AddEntry(VV,"EWK","f");
  
  // Add all bkg contributions to one stack plot
  THStack *stack = new THStack("Background","");
  if(FFmethod)stack->Add(Fakes);
  else{
    stack -> Add(QCD);
    stack -> Add(W);
  }
  stack -> Add(VV);
  stack -> Add(ZLL);
  stack -> Add(TT);
  stack -> Add(ZTT);
  stack -> Draw("hist same");

  canv1->Update();

  InitSignal(ggH ,2);
  InitSignal(qqH ,3);
  if(compareCP){
    InitSignal(CPoddH,4); 
    InitSignal(CPoddqqH,5); 
  }
  if (showSignal){
    if(compareCP){
      legend->AddEntry(ggH,"SM ggH H(125) #times "+TString::Itoa(scaleSignal,10),"f");
      ggH->Draw("hist same");
      legend->AddEntry(CPoddH,"PS ggH H(125) #times "+TString::Itoa(scaleSignal,10),"f");
      CPoddH->Draw("hist same");
      if(nSamples==11){
	legend->AddEntry(qqH,"SM qqH H(125) #times "+TString::Itoa(scaleSignal,10),"f");
	qqH->Draw("hist same");
	legend->AddEntry(CPoddqqH,"PS qqH H(125) #times "+TString::Itoa(scaleSignal,10),"f");
	CPoddqqH->Draw("hist same");
      
      }
    }else{
      legend->AddEntry(ggH,"SM ggH H(125) #times "+TString::Itoa(scaleSignal,10),"f");
      ggH->Draw("hist same");
      legend->AddEntry(qqH,"SM qqH H(125) #times "+TString::Itoa(scaleSignal,10),"f");
      qqH->Draw("hist same");
    }
  }

  canv1->Update();

  // ***********************************
  // **** Systematic uncertainties *****
  // ***********************************

  TH1D * dummy = (TH1D*)ZTT->Clone("dummy");
  // Initialize a histogram which adds all error up
  TH1D * bkgdErr = (TH1D*)stack->GetStack()->Last()->Clone("bkgdErr");
  float errLumi = 0.03;
  float errMuon = 0.03;
  float errElectron = 0.04;
  float errFake = 0.15; // ad-hoc sys uncertainty of Fakes background
  float errQCD = 0.15; // ad-hoc sys uncertainty of QCD background
  float errVV  = 0.15; // ad-hoc sys uncertainty of VV background
  float errW   = 0.10; // ad-hoc sys uncertainty of W+Jets background
  float errTT  = 0.07; // ad-hoc sys uncertainty of TT background
  float errDY  = 0.06; // ad-hoc sys uncertainty of DY background
  float errEmb  = 0.04; // ad-hoc sys uncertainty of DY background
  float errtau_ID   = 0.05; //  tau ID            :  5%
  float errZLL_mtau = 0.10; //  mu->tau fake rate ZLL : 10%

  for (int iB=1; iB<=nBins; ++iB) {   // Add general systematic uncertainties to each bin as error
    //stat error and general systematics
    float eStat =  bkgdErr->GetBinError(iB);
    float X = bkgdErr->GetBinContent(iB);
    float eLumi = errLumi * X;
    float eMuon = errMuon * X;
    float eElectron = errElectron * X;
    float eBkg = dummy->GetBinError(iB);
    //sample specific systematics
    float eQCD   = errFake*Fakes->GetBinContent(iB);
    float eFake   = errQCD*QCD->GetBinContent(iB);
    float eVV    = errVV*VV->GetBinContent(iB);
    float eW     = errW*W->GetBinContent(iB);
    float eTT    = errTT*TT->GetBinContent(iB);
    float eDY    = TMath::Sqrt(errDY*errDY+errtau_ID*errtau_ID)*ZTT->GetBinContent(iB);
    float eZLL    = errZLL_mtau*ZLL->GetBinContent(iB);
    if(useEmbedded) eDY = TMath::Sqrt(errEmb*errEmb+errtau_ID*errtau_ID)*ZTT->GetBinContent(iB);
    float err2   ;
    if(FFmethod)err2= eVV*eVV + eTT*eTT + eDY*eDY + eFake*eFake + eZLL*eZLL + eStat*eStat+eLumi*eLumi+eBkg*eBkg+eMuon*eMuon;     
    else err2= eQCD*eQCD+eVV*eVV + eW*eW + eTT*eTT + eDY*eDY + eStat*eStat+eLumi*eLumi+eBkg*eBkg+eMuon*eMuon;     

    float errTot = TMath::Sqrt(err2);
    bkgdErr->SetBinError(iB,errTot);

    cout << "eQCD: " << eQCD << "  eVV: " << eVV << "  eW: " << eW << "  eTT: " << eTT << "  eDY: " << eDY << "  eTotal: " << errTot << endl;
    cout << "eStat = " << eStat << " : eLumi = "<< eLumi <<" : eBkg = " << eBkg << endl;
    //dummy -> SetBinError(iB,errTot);
    //ggH   -> SetBinError(iB,0);

    Fakes->SetBinError(iB,0);
    QCD->SetBinError(iB,0);
    VV->SetBinError(iB,0);
    TT->SetBinError(iB,0);
    W->SetBinError(iB,0);
    ZLL->SetBinError(iB,0);
    ZTT->SetBinError(iB,0);

    if(compareCP)CPoddH  -> SetBinError(iB,0);
  }
  cout << endl;

  bkgdErr -> SetMarkerSize(0);
  int new_idx = 923;//CreateTransparentColor(13,1.0);
  bkgdErr -> SetFillColor(new_idx);
  bkgdErr -> SetFillStyle(3004);
  bkgdErr -> SetLineWidth(1);
  bkgdErr -> Draw("e2same");
  legend  -> AddEntry(bkgdErr, "Bkg. uncertainty" , "F" );
  canv1   -> Update();


  if (blindData&&showSignal)
    {
      for (int iB=0; iB<=nBins; ++iB)
        {
	  float bkgYield = bkgdErr->GetBinContent(iB);
	  float errbkg = max(0.1,bkgdErr->GetBinError(iB)/bkgYield);
	  float signalYield = ggH->GetBinContent(iB)/scaleSignal;
	  float ye = signalYield / sqrt(bkgYield+pow(bkgYield*errbkg,2));
	  if(ye>=0.2||(categoryIndex==0||categoryIndex==1)){
	    histData->SetBinContent(iB,-1);
	    histData->SetBinError(iB,0);
	  }
        }
    }


  TH1D * ratioH    = (TH1D*)histData -> Clone("ratioH");
  TH1D * ratioErrH = (TH1D*)bkgdErr  -> Clone("ratioErrH");
  TH1D * ratioggH = (TH1D*)ggH  -> Clone("ratioggH");
  TH1D * ratioqqH = (TH1D*)qqH  -> Clone("ratioqqH");
  ratioH -> Divide((TH1D*)stack->GetStack()->Last()); // Divide by the sum of the THStack

  // Set error of MC bkg correctly in ratio
  for (int iB=1; iB<=nBins; ++iB) {
    ratioErrH -> SetBinContent(iB,1.0);
    ratioErrH -> SetBinError(iB,0.0);
    float xBkg   = bkgdErr -> GetBinContent(iB);
    float errBkg = bkgdErr -> GetBinError(iB);
    float xggH = ratioggH->GetBinContent(iB)/scaleSignal;
    float xqqH = ratioqqH->GetBinContent(iB)/scaleSignal;
    ratioggH->SetBinContent(iB,1.0);
    ratioggH->SetBinError(iB,0.0);
    ratioqqH->SetBinContent(iB,1.0);
    ratioqqH->SetBinError(iB,0.0);
    if (xBkg>0) {
      float relErr = errBkg/xBkg;
      ratioErrH->SetBinError(iB,relErr);
      ratioggH->SetBinContent(iB,1+(xggH/xBkg));
      ratioqqH->SetBinContent(iB,1+(xqqH/xBkg));
    }

  }

  pads[1]->cd();
  ratioErrH->Draw("e2same");
  ratioH->Draw("pe0same");
  if(showSignal){
    ratioggH->Draw("hist same");
    ratioqqH->Draw("hist same");
  }
  pads[0]->cd();
  if(categoryIndex==5) histData -> GetYaxis()->SetRangeUser(0.,10000.);

  histData->Draw("pesame");

  FixTopRange(pads[0], GetPadYMax(pads[0]), 0.115);
  //DrawCMSLogo(pads[0], "CMS", "Preliminary", 11, 0.045, 0.035, 1.2);

  if (era== 2016) DrawTitle(pads[0], "35.9 fb^{-1} (13 TeV, 2016)", 3);
  else if (era== 2017) DrawTitle(pads[0], "41.9 fb^{-1} (13 TeV, 2017)", 3);
  else if (era== 2018) DrawTitle(pads[0], "59.9 fb^{-1} (13 TeV, 2018)", 3);
  
  DrawTitle(pads[0], "#scale[1.2]{         #bf{CMS} Work in progress}", 1);
  FixBoxPadding(pads[0], legend, 0.05);
  //legend->SetNColumns(2);
  legend->Draw();
  FixOverlay();
  canv1->Update();
  pads[0]->GetFrame()->Draw();
  canv1 -> Print( outputDir + "MuTau"+TString::Itoa(era,10)+"_" + VariableName + (categoryIndex>=0 ? ((TString)"_Cat"+TString::Itoa(categoryIndex,10)+"_") : (TString)"_") +(useEmbedded ? (TString)"Emb-" : (TString)"") + (FFmethod ? (TString)"fakes" : (TString)"MC") + ".pdf" );
  canv1 -> Print( outputDir + "MuTau"+TString::Itoa(era,10)+"_" + VariableName + (categoryIndex>=0 ? ((TString)"_Cat"+TString::Itoa(categoryIndex,10)+"_") : (TString)"_") +(useEmbedded ? (TString)"Emb-" : (TString)"") + (FFmethod ? (TString)"fakes" : (TString)"MC") + ".png" );
}
