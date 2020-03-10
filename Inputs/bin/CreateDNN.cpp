#include <iostream>
#include <map>
#include <algorithm>
#include <experimental/filesystem>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TList.h"
#include "TSystem.h"
#include "RooWorkspace.h"
#include "RooFunctor.h"
#include "TMVA/Reader.h"
#include "HiggsCP/Inputs/interface/settingsDNN.h"
#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"

namespace fs = std::experimental::filesystem;


int main(int argc, char * argv[]) {

  TString FFlocation = "/nfs/dust/cms/user/cardinia/public/FF_from_IC_1p5cut_v2/";

  bool TEST = false;

  TString process(argv[1]);
  TString era(argv[2]);
  TString channel(argv[3]);

  TString Sample = process + "_" + era;

  if (argc!=4) {
    cout << "Usage of the program : CreateDNN sample era channel" << endl;
    exit(EXIT_FAILURE);
  }

  if (era!="2018"&&era!="2017"&&era!="2016") {
    cout << "ERROR : specified era " << era << " is unknown " << endl;
    exit(EXIT_FAILURE);
  }
  bool sampleFound = false;
  for (auto name_sample : map_sample) {
    if (name_sample.first==Sample) {
      sampleFound = true;
      break;
    }
  }
  if (!sampleFound) {
    cout << "ERROR : specified sample " << Sample << " is unknown " << endl;
    cout << "Available samples ===> " << endl;
    for (auto name_sample : map_sample) {
      cout << "     " << name_sample.first << endl;
    }
    exit(EXIT_FAILURE);
  }


  if(channel!="mt"&&channel!="et"){
    cout << "ERROR: macro only for lep tau channels, please specify et or mt" << endl;
    exit(EXIT_FAILURE);
  }

  bool applyPreselection = true;
  bool PropagateSystematics = true;

  // Some definitions
  double luminosity = 0;
  float qcd_ss_os_iso_relaxed_ratio = 0;
  float trigger_filter_efficiency = 1;
  float embedded_trigger_weight = 1.0;
  float embedded_tracking_weight = 1.0;
  TString input_dir;

  // Mapping of subsamples to output root-file
  map< TString , vector<TString> > samples_map;
  const map<TString, double>  *xsec_map    = 0;
  const map<TString, TString> *process_map = 0;
  
  //TString output_dir = "";
  samples_map[channel + "-NOMINAL_ntuple_"+Sample     ] = map_sample.at(Sample);

  TString output_dir="";
  if (era == "2018"){
    xsec_map    = &xsec_map_2018;
    process_map = &process_map_2018;
    luminosity  = 59740;
    trigger_filter_efficiency = 1.0;
    qcd_ss_os_iso_relaxed_ratio = 1.89; //number from Janek's talk in TauPOG meeting (10.04.19)
    embedded_trigger_weight  = 1.00;
    embedded_tracking_weight = 1.00;
    input_dir="/nfs/dust/cms/user/cardinia/HtoTauTau/HiggsCP/DNN/Jan20/CMSSW_10_2_16/src/DesyTauAnalyses/NTupleMaker/test/mutau/2018/";
    //     input_dir = "/nfs/dust/cms/user/rasp/Run/Run2018/CP/sys";
    output_dir="/nfs/dust/cms/user/rasp/storage/cardinia/" + era +"/InputDNN_v3";
  }
  else if(era == "2017"){
    xsec_map    = &xsec_map_2017; 
    process_map = &process_map_2017; 
    luminosity  = 41900;      
    trigger_filter_efficiency = 1.0; 
    qcd_ss_os_iso_relaxed_ratio = 1.; 
    embedded_trigger_weight  = 1.00;
    embedded_tracking_weight = 0.99;
    input_dir="/nfs/dust/cms/user/cardinia/HtoTauTau/HiggsCP/DNN/Jan20/CMSSW_10_2_16/src/DesyTauAnalyses/NTupleMaker/test/mutau/2017/";
    output_dir="/nfs/dust/cms/user/rasp/storage/cardinia/" + era +"/InputDNN_v3";
  }  
  else if(era == "2016"){
    xsec_map    = &xsec_map_2016;
    process_map = &process_map_2016;
    luminosity  = 35866;                   
    trigger_filter_efficiency = 0.979;
    qcd_ss_os_iso_relaxed_ratio = 2.3;
    embedded_trigger_weight  = 1.03;
    embedded_tracking_weight = 0.98;
    input_dir="/nfs/dust/cms/user/cardinia/HtoTauTau/HiggsCP/DNN/Jan20/CMSSW_10_2_16/src/DesyTauAnalyses/NTupleMaker/test/mutau/2016/";
    output_dir="/nfs/dust/cms/user/rasp/storage/cardinia/" + era +"/InputDNN_v3";
  }
  fs::path path(output_dir.Data());
  if (!(fs::exists(path))) {
    cout << "WARNING: Output directory (" << output_dir.Data() << ") not found, it will be created automatically!"
	 << endl;
    //  exit(EXIT_FAILURE);
    fs::create_directory(path);
    if (!(fs::exists(path))) {
      cout << "ERROR: Output directory (" << output_dir.Data() << ") has not been created!" << endl
	   << "At least the parent directory needs to exist, please check!" << endl;
      exit(EXIT_FAILURE);
    }
  }
  //  TString output_dir = "./test/NTuples_"+channel+"_" + era;
  //gSystem -> Exec("mkdir " + output_dir);

  // Needed for stitching
  double xsecWIncl      = xsec_map->at(process_map->at("WJets"));
  double xsecW1Jets     = xsec_map->at(process_map->at("W1Jets"));
  double xsecW2Jets     = xsec_map->at(process_map->at("W2Jets"));
  double xsecW3Jets     = xsec_map->at(process_map->at("W3Jets"));
  double xsecW4Jets     = xsec_map->at(process_map->at("W4Jets"));

  double xsecDYIncl     = xsec_map->at(process_map->at("DYJets"));
  double xsecDY1Jets    = xsec_map->at(process_map->at("DY1Jets"));
  double xsecDY2Jets    = xsec_map->at(process_map->at("DY2Jets"));
  double xsecDY3Jets    = xsec_map->at(process_map->at("DY3Jets"));
  double xsecDY4Jets    = xsec_map->at(process_map->at("DY4Jets"));

  double neventsWIncl   = 0;
  double neventsW1Jets  = 0;
  double neventsW2Jets  = 0;
  double neventsW3Jets  = 0;
  double neventsW4Jets  = 0;

  if (Sample.Contains("WJets")) {
    neventsWIncl   = getNEventsProcessed(input_dir,process_map->at("WJets"),era);
    neventsW1Jets  = getNEventsProcessed(input_dir,process_map->at("W1Jets"),era);
    neventsW2Jets  = getNEventsProcessed(input_dir,process_map->at("W2Jets"),era);
    neventsW3Jets  = getNEventsProcessed(input_dir,process_map->at("W3Jets"),era);
    neventsW4Jets  = getNEventsProcessed(input_dir,process_map->at("W4Jets"),era);
  }

  double neventsDYIncl  = 0;
  double neventsDY1Jets = 0;
  double neventsDY2Jets = 0;
  double neventsDY3Jets = 0;
  double neventsDY4Jets = 0;

  if (Sample.Contains("DYJets")) {
    neventsDYIncl  = getNEventsProcessed(input_dir,process_map->at("DYJets"),era);
    neventsDY1Jets = getNEventsProcessed(input_dir,process_map->at("DY1Jets"),era);
    neventsDY2Jets = getNEventsProcessed(input_dir,process_map->at("DY2Jets"),era);
    neventsDY3Jets = getNEventsProcessed(input_dir,process_map->at("DY3Jets"),era);
    neventsDY4Jets = getNEventsProcessed(input_dir,process_map->at("DY4Jets"),era);
  }

  TMVA::Reader *reader_;
  TH2D *ff_fracs_qcd_;
  TH2D *ff_fracs_wjets_;
  float met_, pt_1_, pt_2_, mva_dm_2_, mt_1_, m_vis_, pt_tt_, mjj_, n_jets_;
  
  reader_ = new TMVA::Reader();
  reader_->AddVariable( "pt_tt", &pt_tt_ );
  reader_->AddVariable( "pt_1", &pt_1_ );
  reader_->AddVariable( "pt_2", &pt_2_ );
  reader_->AddVariable( "met", &met_ );
  reader_->AddVariable( "m_vis", &m_vis_ );
  reader_->AddVariable( "n_jets", &n_jets_ );
  reader_->AddVariable( "mjj", &mjj_ );
  reader_->AddVariable( "mva_dm_2", &mva_dm_2_ );
  reader_->AddVariable( "mt_1", &mt_1_ );
  reader_->BookMVA( "BDT method", FFlocation+"fractions_"+era+"_mt.xml" );

  TFile f_fracs(FFlocation+"mva_fract_mt_"+era+".root");
  ff_fracs_qcd_ = (TH2D*)f_fracs.Get("QCD");
  ff_fracs_wjets_ = (TH2D*)f_fracs.Get("W");
  ff_fracs_qcd_->SetDirectory(0);
  ff_fracs_wjets_->SetDirectory(0);
  f_fracs.Close();




  TFile * ff_file = TFile::Open(FFlocation+"fakefactors_ws_mt_lite_"+era+".root");
  FakeFactor* ff = (FakeFactor*)ff_file->Get("ff_comb");
  
  std::shared_ptr<RooWorkspace> ff_ws_;
  std::map<std::string, std::shared_ptr<RooFunctor>> fns_;
  ff_ws_ = std::shared_ptr<RooWorkspace>((RooWorkspace*)gDirectory->Get("w"));
  fns_["ff_mt_medium_dmbins"] = std::shared_ptr<RooFunctor>(ff_ws_->function("ff_mt_medium_dmbins")->functor(ff_ws_->argSet("pt,dm,njets,m_pt,os,mt,m_iso,pass_single,mvis")));
  fns_["ff_mt_medium_mvadmbins"] = std::shared_ptr<RooFunctor>(ff_ws_->function("ff_mt_medium_mvadmbins")->functor(ff_ws_->argSet("pt,mvadm,ipsig,njets,m_pt,os,m_iso,pass_single,met_var_qcd,met_var_w,WpT,w_frac,qcd_frac,ttbar_frac")));

  for(auto systematicFF : SystematicsFF){
    string functionname="ff_mt_medium_mvadmbins_";
    functionname+=systematicFF.Data();
    fns_[functionname.c_str()] = std::shared_ptr<RooFunctor>(ff_ws_->function(functionname.c_str())->functor(ff_ws_->argSet("pt,mvadm,ipsig,njets,m_pt,os,mt,m_iso,pass_single,met_var_qcd,met_var_w,WpT,w_frac,qcd_frac,ttbar_frac")));
  };

  if (!PropagateSystematics)
    SystematicsNames = {""};
  else
    for(TString & SystematicsName: SystematicsNames)
      if (SystematicsName != "")
        SystematicsName = "_" + SystematicsName;
  unsigned int systematics_count = SystematicsNames.size();

  bool isData = Sample.Contains("SingleMuon") || Sample.Contains("SingleElectron");
  bool isEmbedded = Sample.Contains("Embed");
  bool isTTbar = Sample.Contains("TTbar");
  bool isDY    = Sample.Contains("DYJets");
  bool isW     = Sample.Contains("WJets");

  ///////////////////////////
  ///  Loop over all samples  
  ///////////////////////////
  
  for (auto const& sample : samples_map){
    cout << sample.first << "  :  " << endl ; 
  
    TFile *outFile = new TFile(output_dir + "/" + sample.first + ".root","RECREATE");
      
    for (size_t i = 0; i < systematics_count; i++) {
        TString SystematicsName = SystematicsNames[i];
        if (isData && SystematicsName != "") continue;
        
        TString TreeName = BaseTreeName + SystematicsName;
	cout << "Tree name : " << TreeName << endl;        
	outFile->cd("");
        TTree *outTree = new TTree(TreeName, "tree created as DNN input");
	outTree->SetAutoSave(100000000); // auto save after 100.000.000 of events
	
	uint run; 
	ULong64_t      evt;
	int extraelec_veto; 
	int extramuon_veto; 
	int dilepton_veto;  

	float pt_1;  
	float eta_1;
	float phi_1;
	int gen_match_1;
	float iso_1;   
	float puppimt_1;
	float ipx_1;
	float ipy_1;
	float ipz_1;
	double IP_signif_PV_with_BS_1;
 	double IP_signif_RefitV_with_BS_1;
 	double IP_signif_RefitV_with_BS_uncorr_1;
	  
	float pt_2;
	float eta_2;
	float phi_2;
	int gen_match_2;
	float puppimt_2;
	int tau_decay_mode_2;
	float dmMVA_2;
	float ipx_2;
	float ipy_2;
	float ipz_2;
	double IP_signif_PV_with_BS_2;
 	double IP_signif_RefitV_with_BS_2;
 	double IP_signif_RefitV_with_BS_uncorr_2;
 	
	bool trg_singlemuon;
	bool trg_mutaucross;
	
	int gen_noutgoing;

	float embweight;
	float trigweight;
	float mcweight;
	float effweight;
	float puweight;
	float idisoweight_1;
	float idisoweight_2;
	float topptweight;
	double zptweight;
	double trkeffweight;
	float weight;	  
	// Merijn: vars below used for stxs. 
	// prefiring_weight is set for different stxs bins.. 
	// this will need special attention
	int njets;
	float mjj;
	float jdeta;
	float dijetpt;
	float jpt_1;
	float jpt_2;
	float jeta_1;
	float jeta_2;
	
	//Variables used for FF method
	float m_vis;
	float pt_tt;
	float mt_tot;
	float m_sv;
	float pt_sv;
	float m_fast;
	float pt_fast;
	
	float ff_nom;
	float ff_sys;
	float ff_mva;

	float puppimet;
	float puppimetphi;
	int os;
	int nbtag;
	
	//DeepTau variables
	float byTightDeepTau2017v2p1VSmu_2;
	float byVLooseDeepTau2017v2p1VSe_2;
	float byVVVLooseDeepTau2017v2p1VSe_2;
	float byVLooseDeepTau2017v2p1VSmu_2;
	float byTightDeepTau2017v2p1VSe_2;
	float byVVVLooseDeepTau2017v2p1VSjet_2;
	float byMediumDeepTau2017v2p1VSjet_2;
	
	float acotautau_refitbs_00;
	float acotautau_refitbs_01;
	
	float acotautau_refitbs_uncorr_00;
	float acotautau_refitbs_uncorr_01;
	
	float acotautau_helix_00;
	float acotautau_helix_01;
	
	float acotautau_helix_uncorr_00;
	float acotautau_helix_uncorr_01;

	float acotautau_bs_00;
 	float acotautau_bs_01;
 	
 	//float acotautau_bs_uncorr_00;
 	//float acotautau_bs_uncorr_01;
 	
 	float acotautau_00;
 	float acotautau_01;
 	
 	//float acotautau_uncorr_00;
 	//float acotautau_uncorr_01;


	// New branches
	float xsec_lumi_weight;      
	float qcd_correction;
	float trigger_filter_weight;
	float embedded_stitching_weight;
	float embedded_rate_weight;
	float prefiring_weight;
	int htxs_reco_flag_ggh;
	int htxs_reco_flag_qqh;

	double gen_sm_htt125;
	double gen_ps_htt125;
	double gen_mm_htt125;
	//double TauSpinnerWeightsMinusMaxMix;
	//double TauSpinnerWeightsMix0p375;
	
	//Weights for top and Z pt reweighting
	float weight_CMS_htt_dyShape_13TeVDown;
	float weight_CMS_htt_dyShape_13TeVUp;

	float weight_CMS_htt_ttbarShape_13TeVDown;
	float weight_CMS_htt_ttbarShape_13TeVUp;


	///Weights for FF
	//Stat uncertainties
	float weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltUp;
	float weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltUp;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltUp;
	float weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltUp;
		
	float weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltUp;
	float weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltUp;
	

	float weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtUp;
	float weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtUp;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtUp;
	float weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtUp;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtUp;
	float weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtUp;
	
	float weight_ff_mt_wjets_stat_njets0_mvadm1Up;
	float weight_ff_mt_qcd_stat_njets0_mvadm1Up;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm1Up;
	float weight_ff_mt_qcd_stat_njets1_mvadm1Up;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm1Up;
	float weight_ff_mt_qcd_stat_njets2_mvadm1Up;
	
	
	float weight_ff_mt_wjets_stat_njets0_mvadm2Up;
	float weight_ff_mt_qcd_stat_njets0_mvadm2Up;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm2Up;
	float weight_ff_mt_qcd_stat_njets1_mvadm2Up;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm2Up;
	float weight_ff_mt_qcd_stat_njets2_mvadm2Up;


	float weight_ff_mt_wjets_stat_njets0_mvadm10Up;
	float weight_ff_mt_qcd_stat_njets0_mvadm10Up;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm10Up;
	float weight_ff_mt_qcd_stat_njets1_mvadm10Up;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm10Up;
	float weight_ff_mt_qcd_stat_njets2_mvadm10Up;


	float weight_ff_mt_wjets_stat_njets0_mvadm11Up;
	float weight_ff_mt_qcd_stat_njets0_mvadm11Up;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm11Up;
	float weight_ff_mt_qcd_stat_njets1_mvadm11Up;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm11Up;
	float weight_ff_mt_qcd_stat_njets2_mvadm11Up;

	float weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltDown;
	float weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltDown;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltDown;
	float weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltDown;
		
	float weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltDown;
	float weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltDown;
	

	float weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtDown;
	float weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtDown;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtDown;
	float weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtDown;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtDown;
	float weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtDown;
	
	float weight_ff_mt_wjets_stat_njets0_mvadm1Down;
	float weight_ff_mt_qcd_stat_njets0_mvadm1Down;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm1Down;
	float weight_ff_mt_qcd_stat_njets1_mvadm1Down;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm1Down;
	float weight_ff_mt_qcd_stat_njets2_mvadm1Down;
	
	
	float weight_ff_mt_wjets_stat_njets0_mvadm2Down;
	float weight_ff_mt_qcd_stat_njets0_mvadm2Down;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm2Down;
	float weight_ff_mt_qcd_stat_njets1_mvadm2Down;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm2Down;
	float weight_ff_mt_qcd_stat_njets2_mvadm2Down;


	float weight_ff_mt_wjets_stat_njets0_mvadm10Down;
	float weight_ff_mt_qcd_stat_njets0_mvadm10Down;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm10Down;
	float weight_ff_mt_qcd_stat_njets1_mvadm10Down;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm10Down;
	float weight_ff_mt_qcd_stat_njets2_mvadm10Down;


	float weight_ff_mt_wjets_stat_njets0_mvadm11Down;
	float weight_ff_mt_qcd_stat_njets0_mvadm11Down;
	
	float weight_ff_mt_wjets_stat_njets1_mvadm11Down;
	float weight_ff_mt_qcd_stat_njets1_mvadm11Down;
	
	float weight_ff_mt_wjets_stat_njets2_mvadm11Down;
	float weight_ff_mt_qcd_stat_njets2_mvadm11Down;


	//met_var_qcd and met_var_w non-closure corrections

	float weight_ff_mt_qcd_met_closure_systUp;
	float weight_ff_mt_wjets_met_closure_systUp;
	float weight_ff_mt_ttbar_met_closure_systUp;
	float weight_ff_mt_qcd_met_closure_systDown;
	float weight_ff_mt_wjets_met_closure_systDown;
	float weight_ff_mt_ttbar_met_closure_systDown;

	//m_pt non-closure corrections

	float weight_ff_mt_qcd_l_pt_closure_systUp;
	float weight_ff_mt_qcd_l_pt_closure_systDown;
	float weight_ff_mt_wjets_l_pt_closure_systUp;
	float weight_ff_mt_wjets_l_pt_closure_systDown;

	//extrapolations from DR to SR
	float weight_ff_mt_qcd_systUp;
	float weight_ff_mt_qcd_systDown;
	float weight_ff_mt_wjets_systUp;
	float weight_ff_mt_wjets_systDown;
	float weight_ff_mt_ttbar_systUp;
	float weight_ff_mt_ttbar_systDown;

	//Weights for Tau ES and ID

	float weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVUp;
	float weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVUp;
	float weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVUp;
	float weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVUp;
	float weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVUp;
	float weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVDown;
	float weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVDown;
	float weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVDown;
	float weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVDown;
	float weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVDown;

	float weight_CMS_eff_t_pTlow_MVADM0_13TeVUp; 
	float weight_CMS_eff_t_pTlow_MVADM1_13TeVUp; 
	float weight_CMS_eff_t_pTlow_MVADM2_13TeVUp; 
	float weight_CMS_eff_t_pTlow_MVADM10_13TeVUp;
	float weight_CMS_eff_t_pTlow_MVADM11_13TeVUp;
	float weight_CMS_eff_t_pThigh_MVADM0_13TeVUp;
	float weight_CMS_eff_t_pThigh_MVADM1_13TeVUp;
	float weight_CMS_eff_t_pThigh_MVADM2_13TeVUp;
	float weight_CMS_eff_t_pThigh_MVADM10_13TeVUp; 
	float weight_CMS_eff_t_pThigh_MVADM11_13TeVUp; 
	float weight_CMS_eff_t_pTlow_MVADM0_13TeVDown; 
	float weight_CMS_eff_t_pTlow_MVADM1_13TeVDown; 
	float weight_CMS_eff_t_pTlow_MVADM2_13TeVDown; 
	float weight_CMS_eff_t_pTlow_MVADM10_13TeVDown; 
	float weight_CMS_eff_t_pTlow_MVADM11_13TeVDown; 
	float weight_CMS_eff_t_pThigh_MVADM0_13TeVDown; 
	float weight_CMS_eff_t_pThigh_MVADM1_13TeVDown; 
	float weight_CMS_eff_t_pThigh_MVADM2_13TeVDown; 
	float weight_CMS_eff_t_pThigh_MVADM10_13TeVDown;
	float weight_CMS_eff_t_pThigh_MVADM11_13TeVDown;

	float weight_CMS_scale_gg_13TeVUp;
	float weight_CMS_scale_gg_13TeVDown;





	outTree->Branch("run",&run,"run/i");
	outTree->Branch("evt",&evt,"evt/l");
	//	outTree->Branch("extraelec_veto",&extraelec_veto,"extraelec_veto/O");
	//	outTree->Branch("extramuon_veto",&extramuon_veto,"extramuon_veto/O");
	//	outTree->Branch("dilepton_veto",&dilepton_veto,"dilepton_veto/O");
	
	outTree->Branch("pt_1",&pt_1,"pt_1/F");
	outTree->Branch("eta_1",&eta_1,"eta_1/F");
	outTree->Branch("phi_1",&phi_1,"phi_1/F");
	outTree->Branch("gen_match_1",&gen_match_1,"gen_match_1/I");
	outTree->Branch("iso_1",&iso_1,"iso_1/F"); 
	outTree->Branch("puppimt_1",&puppimt_1,"puppimt_1/F");
	outTree->Branch("ipx_1",&ipx_1,"ipx_1/F");
	outTree->Branch("ipy_1",&ipy_1,"ipy_1/F");
	outTree->Branch("ipz_1",&ipz_1,"ipz_1/F");
	outTree->Branch("IP_signif_PV_with_BS_1",&IP_signif_PV_with_BS_1,"IP_signif_PV_with_BS_1/D");
 	outTree->Branch("IP_signif_RefitV_with_BS_1",&IP_signif_RefitV_with_BS_1,"IP_signif_RefitV_with_BS_1/D");
 	outTree->Branch("IP_signif_RefitV_with_BS_uncorr_1",&IP_signif_RefitV_with_BS_uncorr_1,"IP_signif_RefitV_with_BS_uncorr_1/D");
	
	outTree->Branch("pt_2",&pt_2,"pt_2/F");
	outTree->Branch("eta_2",&eta_2,"eta_2/F");
	outTree->Branch("phi_2",&phi_2,"phi_2/F");
	outTree->Branch("gen_match_2",&gen_match_2,"gen_match_2/I");
	outTree->Branch("puppimt_2",&puppimt_2,"puppimt_2/F");
	outTree->Branch("tau_decay_mode_2",&tau_decay_mode_2,"tau_decay_mode_2/I");
	outTree->Branch("dmMVA_2",&dmMVA_2,"dmMVA_2/F");
	outTree->Branch("ipx_2",&ipx_2,"ipx_2/F");
	outTree->Branch("ipy_2",&ipy_2,"ipy_2/F");
	outTree->Branch("ipz_2",&ipz_2,"ipz_2/F");
	outTree->Branch("IP_signif_PV_with_BS_2",&IP_signif_PV_with_BS_2,"IP_signif_PV_with_BS_2/D");
 	outTree->Branch("IP_signif_RefitV_with_BS_2",&IP_signif_RefitV_with_BS_2,"IP_signif_RefitV_with_BS_2/D");
 	outTree->Branch("IP_signif_RefitV_with_BS_uncorr_2",&IP_signif_RefitV_with_BS_uncorr_2,"IP_signif_RefitV_with_BS_uncorr_2/D");
	
	outTree->Branch("trg_singlemuon",&trg_singlemuon,"trg_singlemuon/O");
	outTree->Branch("trg_mutaucross",&trg_mutaucross,"trg_mutaucross/O");

	//	outTree->Branch("gen_noutgoing",&gen_noutgoing,"gen_noutgoing/I");
	
	//	outTree->Branch("embweight",&embweight,"embweight/F");
	//	outTree->Branch("trigweight",&trigweight,"trigweight/F");
	//	outTree->Branch("mcweight",&mcweight,"mcweight/F");
	//	outTree->Branch("effweight",&effweight,"effweight/F");
	//	outTree->Branch("puweight",&puweight,"puweight/F");
	//	outTree->Branch("topptweight",&topptweight,"topptweight/F");
	//	outTree->Branch("zptweight",&zptweight,"zptweight/D");
	//	outTree->Branch("trkeffweight",&trkeffweight,"trkeffweight/D");
	outTree->Branch("weight",&weight,"weight/F");
	
	outTree->Branch("njets",&njets,"njets/I");
	outTree->Branch("mjj",&mjj,"mjj/F");
	outTree->Branch("jdeta",&jdeta,"jdeta/F");
	outTree->Branch("dijetpt",&dijetpt,"dijetpt/F");
	outTree->Branch("jpt_1",&jpt_1,"jpt_1/F");
	outTree->Branch("jpt_2",&jpt_2,"jpt_2/F");
	outTree->Branch("jeta_1",&jeta_1,"jeta_1/F");
	outTree->Branch("jeta_2",&jeta_2,"jeta_2/F");
	
	outTree->Branch("m_vis",&m_vis,"m_vis/F");      
	outTree->Branch("pt_tt",&pt_tt,"pt_tt/F");
	outTree->Branch("mt_tot",&mt_tot,"mt_tot/F");
	outTree->Branch("m_sv",&m_sv,"m_sv/F");
	outTree->Branch("pt_sv",&pt_sv,"pt_sv/F");
	outTree->Branch("m_fast",&m_fast,"m_fast/F");
	outTree->Branch("pt_fast",&pt_fast,"pt_fast/F");
	
	outTree->Branch("puppimet",&puppimet,"puppimet/F");      
	outTree->Branch("puppimetphi",&puppimetphi,"puppimetphi/F");      
	outTree->Branch("os",&os,"os/I");      
	outTree->Branch("nbtag",&nbtag,"nbtag/I");      
	  
	//DeepTua branches
	//	outTree->Branch("byTightDeepTau2017v2p1VSmu_2",&byTightDeepTau2017v2p1VSmu_2,"byTightDeepTau2017v2p1VSmu_2/F");      
	//	outTree->Branch("byVLooseDeepTau2017v2p1VSe_2",&byVLooseDeepTau2017v2p1VSe_2,"byVLooseDeepTau2017v2p1VSe_2/F");      
	//	outTree->Branch("byVVVLooseDeepTau2017v2p1VSe_2",&byVVVLooseDeepTau2017v2p1VSe_2,"byVVVLooseDeepTau2017v2p1VSe_2/F");
	//	outTree->Branch("byVLooseDeepTau2017v2p1VSmu_2",&byVLooseDeepTau2017v2p1VSmu_2,"byVLooseDeepTau2017v2p1VSmu_2/F");
	//	outTree->Branch("byTightDeepTau2017v2p1VSe_2",&byTightDeepTau2017v2p1VSe_2,"byTightDeepTau2017v2p1VSe_2/F");      
	outTree->Branch("byVVVLooseDeepTau2017v2p1VSjet_2",&byVVVLooseDeepTau2017v2p1VSjet_2,"byVVVLooseDeepTau2017v2p1VSjet_2/F");      
	outTree->Branch("byMediumDeepTau2017v2p1VSjet_2",&byMediumDeepTau2017v2p1VSjet_2,"byMediumDeepTau2017v2p1VSjet_2/F");   
	
	outTree->Branch("acotautau_refitbs_00",&acotautau_refitbs_00,"acotautau_refitbs_00/F");
	outTree->Branch("acotautau_refitbs_01",&acotautau_refitbs_01,"acotautau_refitbs_01/F");
	
	outTree->Branch("acotautau_helix_00",&acotautau_helix_00,"acotautau_helix_00/F");
	outTree->Branch("acotautau_helix_01",&acotautau_helix_01,"acotautau_helix_01/F");

	outTree->Branch("acotautau_bs_00",&acotautau_bs_00,"acotautau_bs_00/F");
 	outTree->Branch("acotautau_bs_01",&acotautau_bs_01,"acotautau_bs_01/F");
 	
 	outTree->Branch("acotautau_00",&acotautau_00,"acotautau_00/F");
 	outTree->Branch("acotautau_01",&acotautau_01,"acotautau_01/F");

	outTree->Branch("acotautau_refitbs_uncorr_00",&acotautau_refitbs_uncorr_00,"acotautau_refitbs_uncorr_00/F");
 	outTree->Branch("acotautau_refitbs_uncorr_01",&acotautau_refitbs_uncorr_01,"acotautau_refitbs_uncorr_01/F");
	
	outTree->Branch("acotautau_helix_uncorr_00",&acotautau_helix_uncorr_00,"acotautau_helix_uncorr_00/F");
 	outTree->Branch("acotautau_helix_uncorr_01",&acotautau_helix_uncorr_01,"acotautau_helix_uncorr_01/F");
 	
 	//outTree->Branch("acotautau_bs_uncorr_00",&acotautau_bs_uncorr_00,"acotautau_bs_uncorr_00/F");
 	//outTree->Branch("acotautau_bs_uncorr_01",&acotautau_bs_uncorr_01,"acotautau_bs_uncorr_01/F");
 	
 	//outTree->Branch("acotautau_uncorr_00",&acotautau_uncorr_00,"acotautau_uncorr_00/F");
 	//outTree->Branch("acotautau_uncorr_01",&acotautau_uncorr_01,"acotautau_uncorr_01/F");
	
	outTree->Branch("xsec_lumi_weight", &xsec_lumi_weight, "xsec_lumi_weight/F");
	//	outTree->Branch("qcd_correction", &qcd_correction, "qcd_correction/F");
	//	outTree->Branch("trigger_filter_weight", &trigger_filter_weight, "trigger_filter_weight/F");
	//	outTree->Branch("embedded_stitching_weight", &embedded_stitching_weight, "embedded_stitching_weight/F");
	//	outTree->Branch("embedded_rate_weight", &embedded_rate_weight, "embedded_rate_weight/F");
	outTree->Branch("prefiring_weight", &prefiring_weight, "prefiring_weight/F");
	outTree->Branch("htxs_reco_flag_ggh", &htxs_reco_flag_ggh, "htxs_reco_flag_ggh/I");
	outTree->Branch("htxs_reco_flag_qqh", &htxs_reco_flag_qqh, "htxs_reco_flag_qqh/I");
	outTree->Branch("ff_nom", &ff_nom, "ff_nom/F");
	outTree->Branch("ff_mva", &ff_mva, "ff_mva/F");
	outTree->Branch("ff_sys", &ff_sys, "ff_sys/F");
	
	outTree->Branch("gen_sm_htt125", &gen_sm_htt125,"gen_sm_htt125/D");
	outTree->Branch("gen_ps_htt125", &gen_ps_htt125,"gen_ps_htt125/D");
	outTree->Branch("gen_mm_htt125", &gen_mm_htt125,"gen_mm_htt125/D");
	//outTree->Branch("gen_minusmm_htt125", &TauSpinnerWeightsMinusMaxMix,"gen_minusmm_htt125/D");
	//outTree->Branch("gen_mix0p375_htt125", &TauSpinnerWeightsMix0p375,"gen_mix0p375_htt125/D");
	
	//Weights for top and Z pt reweighting
	outTree->Branch("weight_CMS_htt_dyShape_13TeVDown",&weight_CMS_htt_dyShape_13TeVDown,"weight_CMS_htt_dyShape_13TeVDown/F");
	outTree->Branch("weight_CMS_htt_dyShape_13TeVUp",&weight_CMS_htt_dyShape_13TeVUp,"weight_CMS_htt_dyShape_13TeVUp/F");

	outTree->Branch("weight_CMS_htt_ttbarShape_13TeVDown",&weight_CMS_htt_ttbarShape_13TeVDown,"weight_CMS_htt_ttbarShape_13TeVDown/F");
	outTree->Branch("weight_CMS_htt_ttbarShape_13TeVUp",&weight_CMS_htt_ttbarShape_13TeVUp,"weight_CMS_htt_ttbarShape_13TeVUp/F");
	///Weights for FF
	//Stat uncertainties
	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltUp",&weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltUp,"weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltUp/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltUp",&weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltUp,"weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltUp/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltUp",&weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltUp,"weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltUp/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltUp",&weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltUp,"weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltUp/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltUp",&weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltUp,"weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltUp/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltUp",&weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltUp,"weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltUp/F");
			                                                                                                                                                                           
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtUp",&weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtUp,"weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtUp/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtUp",&weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtUp,"weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtUp/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtUp",&weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtUp,"weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtUp/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtUp",&weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtUp,"weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtUp/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtUp",&weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtUp,"weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtUp/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtUp",&weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtUp,"weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtUp/F");
	
	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm1Up",&weight_ff_mt_wjets_stat_njets0_mvadm1Up,"weight_ff_mt_wjets_stat_njets0_mvadm1Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm1Up",&weight_ff_mt_qcd_stat_njets0_mvadm1Up,"weight_ff_mt_qcd_stat_njets0_mvadm1Up/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm1Up",&weight_ff_mt_wjets_stat_njets1_mvadm1Up,"weight_ff_mt_wjets_stat_njets1_mvadm1Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm1Up",&weight_ff_mt_qcd_stat_njets1_mvadm1Up,"weight_ff_mt_qcd_stat_njets1_mvadm1Up/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm1Up",&weight_ff_mt_wjets_stat_njets2_mvadm1Up,"weight_ff_mt_wjets_stat_njets2_mvadm1Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm1Up",&weight_ff_mt_qcd_stat_njets2_mvadm1Up,"weight_ff_mt_qcd_stat_njets2_mvadm1Up/F");

	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm2Up",&weight_ff_mt_wjets_stat_njets0_mvadm2Up,"weight_ff_mt_wjets_stat_njets0_mvadm2Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm2Up",&weight_ff_mt_qcd_stat_njets0_mvadm2Up,"weight_ff_mt_qcd_stat_njets0_mvadm2Up/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm2Up",&weight_ff_mt_wjets_stat_njets1_mvadm2Up,"weight_ff_mt_wjets_stat_njets1_mvadm2Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm2Up",&weight_ff_mt_qcd_stat_njets1_mvadm2Up,"weight_ff_mt_qcd_stat_njets1_mvadm2Up/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm2Up",&weight_ff_mt_wjets_stat_njets2_mvadm2Up,"weight_ff_mt_wjets_stat_njets2_mvadm2Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm2Up",&weight_ff_mt_qcd_stat_njets2_mvadm2Up,"weight_ff_mt_qcd_stat_njets2_mvadm2Up/F");


	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm10Up",&weight_ff_mt_wjets_stat_njets0_mvadm10Up,"weight_ff_mt_wjets_stat_njets0_mvadm10Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm10Up",&weight_ff_mt_qcd_stat_njets0_mvadm10Up,"weight_ff_mt_qcd_stat_njets0_mvadm10Up/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm10Up",&weight_ff_mt_wjets_stat_njets1_mvadm10Up,"weight_ff_mt_wjets_stat_njets1_mvadm10Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm10Up",&weight_ff_mt_qcd_stat_njets1_mvadm10Up,"weight_ff_mt_qcd_stat_njets1_mvadm10Up/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm10Up",&weight_ff_mt_wjets_stat_njets2_mvadm10Up,"weight_ff_mt_wjets_stat_njets2_mvadm10Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm10Up",&weight_ff_mt_qcd_stat_njets2_mvadm10Up,"weight_ff_mt_qcd_stat_njets2_mvadm10Up/F");
			                                                                                                      	                                                 
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm11Up",&weight_ff_mt_wjets_stat_njets0_mvadm11Up,"weight_ff_mt_wjets_stat_njets0_mvadm11Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm11Up",&weight_ff_mt_qcd_stat_njets0_mvadm11Up,"weight_ff_mt_qcd_stat_njets0_mvadm11Up/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm11Up",&weight_ff_mt_wjets_stat_njets1_mvadm11Up,"weight_ff_mt_wjets_stat_njets1_mvadm11Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm11Up",&weight_ff_mt_qcd_stat_njets1_mvadm11Up,"weight_ff_mt_qcd_stat_njets1_mvadm11Up/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm11Up",&weight_ff_mt_wjets_stat_njets2_mvadm11Up,"weight_ff_mt_wjets_stat_njets2_mvadm11Up/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm11Up",&weight_ff_mt_qcd_stat_njets2_mvadm11Up,"weight_ff_mt_qcd_stat_njets2_mvadm11Up/F");


	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltDown",&weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltDown,"weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltDown/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltDown",&weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltDown,"weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltDown/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltDown",&weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltDown,"weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltDown/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltDown",&weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltDown,"weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltDown/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltDown",&weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltDown,"weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltDown/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltDown",&weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltDown,"weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltDown/F");
			                                                                                                                                                                           
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtDown",&weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtDown,"weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtDown/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtDown",&weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtDown,"weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtDown/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtDown",&weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtDown,"weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtDown/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtDown",&weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtDown,"weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtDown/F");
			                                                                                                                                                                           
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtDown",&weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtDown,"weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtDown/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtDown",&weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtDown,"weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtDown/F");
	
	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm1Down",&weight_ff_mt_wjets_stat_njets0_mvadm1Down,"weight_ff_mt_wjets_stat_njets0_mvadm1Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm1Down",&weight_ff_mt_qcd_stat_njets0_mvadm1Down,"weight_ff_mt_qcd_stat_njets0_mvadm1Down/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm1Down",&weight_ff_mt_wjets_stat_njets1_mvadm1Down,"weight_ff_mt_wjets_stat_njets1_mvadm1Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm1Down",&weight_ff_mt_qcd_stat_njets1_mvadm1Down,"weight_ff_mt_qcd_stat_njets1_mvadm1Down/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm1Down",&weight_ff_mt_wjets_stat_njets2_mvadm1Down,"weight_ff_mt_wjets_stat_njets2_mvadm1Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm1Down",&weight_ff_mt_qcd_stat_njets2_mvadm1Down,"weight_ff_mt_qcd_stat_njets2_mvadm1Down/F");

	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm2Down",&weight_ff_mt_wjets_stat_njets0_mvadm2Down,"weight_ff_mt_wjets_stat_njets0_mvadm2Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm2Down",&weight_ff_mt_qcd_stat_njets0_mvadm2Down,"weight_ff_mt_qcd_stat_njets0_mvadm2Down/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm2Down",&weight_ff_mt_wjets_stat_njets1_mvadm2Down,"weight_ff_mt_wjets_stat_njets1_mvadm2Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm2Down",&weight_ff_mt_qcd_stat_njets1_mvadm2Down,"weight_ff_mt_qcd_stat_njets1_mvadm2Down/F");
			                                                                                                                                                   
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm2Down",&weight_ff_mt_wjets_stat_njets2_mvadm2Down,"weight_ff_mt_wjets_stat_njets2_mvadm2Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm2Down",&weight_ff_mt_qcd_stat_njets2_mvadm2Down,"weight_ff_mt_qcd_stat_njets2_mvadm2Down/F");


	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm10Down",&weight_ff_mt_wjets_stat_njets0_mvadm10Down,"weight_ff_mt_wjets_stat_njets0_mvadm10Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm10Down",&weight_ff_mt_qcd_stat_njets0_mvadm10Down,"weight_ff_mt_qcd_stat_njets0_mvadm10Down/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm10Down",&weight_ff_mt_wjets_stat_njets1_mvadm10Down,"weight_ff_mt_wjets_stat_njets1_mvadm10Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm10Down",&weight_ff_mt_qcd_stat_njets1_mvadm10Down,"weight_ff_mt_qcd_stat_njets1_mvadm10Down/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm10Down",&weight_ff_mt_wjets_stat_njets2_mvadm10Down,"weight_ff_mt_wjets_stat_njets2_mvadm10Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm10Down",&weight_ff_mt_qcd_stat_njets2_mvadm10Down,"weight_ff_mt_qcd_stat_njets2_mvadm10Down/F");
			                                                                                                      	                                                 
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets0_mvadm11Down",&weight_ff_mt_wjets_stat_njets0_mvadm11Down,"weight_ff_mt_wjets_stat_njets0_mvadm11Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets0_mvadm11Down",&weight_ff_mt_qcd_stat_njets0_mvadm11Down,"weight_ff_mt_qcd_stat_njets0_mvadm11Down/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets1_mvadm11Down",&weight_ff_mt_wjets_stat_njets1_mvadm11Down,"weight_ff_mt_wjets_stat_njets1_mvadm11Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets1_mvadm11Down",&weight_ff_mt_qcd_stat_njets1_mvadm11Down,"weight_ff_mt_qcd_stat_njets1_mvadm11Down/F");
			                                                                                                      	                                                 
	outTree->Branch("weight_ff_mt_wjets_stat_njets2_mvadm11Down",&weight_ff_mt_wjets_stat_njets2_mvadm11Down,"weight_ff_mt_wjets_stat_njets2_mvadm11Down/F");
	outTree->Branch("weight_ff_mt_qcd_stat_njets2_mvadm11Down",&weight_ff_mt_qcd_stat_njets2_mvadm11Down,"weight_ff_mt_qcd_stat_njets2_mvadm11Down/F");


	//met_var_qcd and met_var_w non-closure corrections

	outTree->Branch("weight_ff_mt_qcd_met_closure_systUp",&weight_ff_mt_qcd_met_closure_systUp,"weight_ff_mt_qcd_met_closure_systUp/F");
	outTree->Branch("weight_ff_mt_wjets_met_closure_systUp",&weight_ff_mt_wjets_met_closure_systUp,"weight_ff_mt_wjets_met_closure_systUp/F");
	outTree->Branch("weight_ff_mt_ttbar_met_closure_systUp",&weight_ff_mt_ttbar_met_closure_systUp,"weight_ff_mt_ttbar_met_closure_systUp/F");
	outTree->Branch("weight_ff_mt_qcd_met_closure_systDown",&weight_ff_mt_qcd_met_closure_systDown,"weight_ff_mt_qcd_met_closure_systDown/F");
	outTree->Branch("weight_ff_mt_wjets_met_closure_systDown",&weight_ff_mt_wjets_met_closure_systDown,"weight_ff_mt_wjets_met_closure_systDown/F");
	outTree->Branch("weight_ff_mt_ttbar_met_closure_systDown",&weight_ff_mt_ttbar_met_closure_systDown,"weight_ff_mt_ttbar_met_closure_systDown/F");

	//m_pt non-closure corrections

	outTree->Branch("weight_ff_mt_qcd_l_pt_closure_systUp",&weight_ff_mt_qcd_l_pt_closure_systUp,"weight_ff_mt_qcd_l_pt_closure_systUp/F");
	outTree->Branch("weight_ff_mt_qcd_l_pt_closure_systDown",&weight_ff_mt_qcd_l_pt_closure_systDown,"weight_ff_mt_qcd_l_pt_closure_systDown/F");
	outTree->Branch("weight_ff_mt_wjets_l_pt_closure_systUp",&weight_ff_mt_wjets_l_pt_closure_systUp,"weight_ff_mt_wjets_l_pt_closure_systUp/F");
	outTree->Branch("weight_ff_mt_wjets_l_pt_closure_systDown",&weight_ff_mt_wjets_l_pt_closure_systDown,"weight_ff_mt_wjets_l_pt_closure_systDown/F");

	//extrapolations from DR to SR
	outTree->Branch("weight_ff_mt_qcd_systUp",&weight_ff_mt_qcd_systUp,"weight_ff_mt_qcd_systUp/F");
	outTree->Branch("weight_ff_mt_qcd_systDown",&weight_ff_mt_qcd_systDown,"weight_ff_mt_qcd_systDown/F");
	outTree->Branch("weight_ff_mt_wjets_systUp",&weight_ff_mt_wjets_systUp,"weight_ff_mt_wjets_systUp/F");
	outTree->Branch("weight_ff_mt_wjets_systDown",&weight_ff_mt_wjets_systDown,"weight_ff_mt_wjets_systDown/F");
	outTree->Branch("weight_ff_mt_ttbar_systUp",&weight_ff_mt_ttbar_systUp,"weight_ff_mt_ttbar_systUp/F");
	outTree->Branch("weight_ff_mt_ttbar_systDown",&weight_ff_mt_ttbar_systDown,"weight_ff_mt_ttbar_systDown/F");


	//Weights for Tau ES and ID


   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVUp, "weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVUp/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVUp, "weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVUp/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVUp, "weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVUp/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVUp, "weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVUp/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVUp, "weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVUp/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVDown, "weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVDown/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVDown, "weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVDown/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVDown, "weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVDown/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVDown, "weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVDown/F");
   	outTree->Branch("weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVDown, "weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVDown/F");


  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM0_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM0_13TeVUp, "weight_CMS_eff_t_pTlow_MVADM0_13TeVUp/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM1_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM1_13TeVUp, "weight_CMS_eff_t_pTlow_MVADM1_13TeVUp/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM2_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM2_13TeVUp, "weight_CMS_eff_t_pTlow_MVADM2_13TeVUp/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM10_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM10_13TeVUp, "weight_CMS_eff_t_pTlow_MVADM10_13TeVUp/F");
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM11_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM11_13TeVUp, "weight_CMS_eff_t_pTlow_MVADM11_13TeVUp/F");
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM0_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM0_13TeVUp, "weight_CMS_eff_t_pThigh_MVADM0_13TeVUp/F");
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM1_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM1_13TeVUp, "weight_CMS_eff_t_pThigh_MVADM1_13TeVUp/F");
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM2_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM2_13TeVUp, "weight_CMS_eff_t_pThigh_MVADM2_13TeVUp/F");
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM10_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM10_13TeVUp, "weight_CMS_eff_t_pThigh_MVADM10_13TeVUp/F"); 
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM11_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM11_13TeVUp, "weight_CMS_eff_t_pThigh_MVADM11_13TeVUp/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM0_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM0_13TeVDown, "weight_CMS_eff_t_pTlow_MVADM0_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM1_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM1_13TeVDown, "weight_CMS_eff_t_pTlow_MVADM1_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM2_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM2_13TeVDown, "weight_CMS_eff_t_pTlow_MVADM2_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM10_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM10_13TeVDown, "weight_CMS_eff_t_pTlow_MVADM10_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pTlow_MVADM11_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM11_13TeVDown, "weight_CMS_eff_t_pTlow_MVADM11_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM0_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM0_13TeVDown, "weight_CMS_eff_t_pThigh_MVADM0_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM1_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM1_13TeVDown, "weight_CMS_eff_t_pThigh_MVADM1_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM2_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM2_13TeVDown, "weight_CMS_eff_t_pThigh_MVADM2_13TeVDown/F"); 
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM10_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM10_13TeVDown, "weight_CMS_eff_t_pThigh_MVADM10_13TeVDown/F");
  	outTree->Branch("weight_CMS_eff_t_pThigh_MVADM11_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM11_13TeVDown, "weight_CMS_eff_t_pThigh_MVADM11_13TeVDown/F");



   	outTree->Branch("weight_CMS_scale_gg_13TeVUp", &weight_CMS_scale_gg_13TeVUp, "weight_CMS_scale_gg_13TeVUp/F");
   	outTree->Branch("weight_CMS_scale_gg_13TeVDown", &weight_CMS_scale_gg_13TeVDown, "weight_CMS_scale_gg_13TeVDown/F");


	for(TString const& subsample: sample.second) {
	  cout << "  - " << subsample << " : " << endl;
          
	  TFile *inFile  = new TFile( input_dir + "/" + subsample + ".root" ,"READ");
	  if (inFile->IsZombie()) {
	    cout << "File " << input_dir << "/" << subsample << ".root  is not found" << endl;
	    exit(EXIT_FAILURE);
	  }
 	  TTree *inTree  = (TTree*) inFile -> Get(TreeName);
	  if (inTree==NULL) {
	    cout << "Tree with name " << TreeName << " is not present in subsample " << subsample << endl;
	    continue;
	  }

	  double nevents = getNEventsProcessed( input_dir, subsample,era); 
	  // SetBranchAddress for variables that need are needed for preselection or stitching
	  //variables below are for preselection
	  
	  //branches for variables to be saved in DNN ntuple
	  inTree->SetBranchAddress("run",&run);
	  inTree->SetBranchAddress("evt",&evt);
	  inTree->SetBranchAddress("extraelec_veto",&extraelec_veto);
	  inTree->SetBranchAddress("extramuon_veto",&extramuon_veto);
	  inTree->SetBranchAddress("dilepton_veto",&dilepton_veto);
	  
	  inTree->SetBranchAddress("pt_1",&pt_1);
	  inTree->SetBranchAddress("eta_1",&eta_1);
	  inTree->SetBranchAddress("phi_1",&phi_1);
	  inTree->SetBranchAddress("gen_match_1",&gen_match_1);
	  inTree->SetBranchAddress("iso_1",&iso_1); 
	  inTree->SetBranchAddress("puppimt_1",&puppimt_1);
	  inTree->SetBranchAddress("ipx_1",&ipx_1);
	  inTree->SetBranchAddress("ipy_1",&ipy_1);
	  inTree->SetBranchAddress("ipz_1",&ipz_1);
	  inTree->SetBranchAddress("IP_signif_PV_with_BS_1",&IP_signif_PV_with_BS_1);
 	  inTree->SetBranchAddress("IP_signif_RefitV_with_BS_1",&IP_signif_RefitV_with_BS_1);
 	  inTree->SetBranchAddress("IP_signif_RefitV_with_BS_uncorr_1",&IP_signif_RefitV_with_BS_uncorr_1);

	  inTree->SetBranchAddress("pt_2",&pt_2);
	  inTree->SetBranchAddress("eta_2",&eta_2);
	  inTree->SetBranchAddress("phi_2",&phi_2);
	  inTree->SetBranchAddress("gen_match_2",&gen_match_2);
	  inTree->SetBranchAddress("puppimt_2",&puppimt_2);
	  inTree->SetBranchAddress("tau_decay_mode_2",&tau_decay_mode_2);
	  inTree->SetBranchAddress("dmMVA_2",&dmMVA_2);
	  inTree->SetBranchAddress("ipx_2",&ipx_2);
	  inTree->SetBranchAddress("ipy_2",&ipy_2);
	  inTree->SetBranchAddress("ipz_2",&ipz_2);
	  inTree->SetBranchAddress("IP_signif_PV_with_BS_2",&IP_signif_PV_with_BS_2);
 	  inTree->SetBranchAddress("IP_signif_RefitV_with_BS_2",&IP_signif_RefitV_with_BS_2);
 	  inTree->SetBranchAddress("IP_signif_RefitV_with_BS_uncorr_2",&IP_signif_RefitV_with_BS_uncorr_2);
	  
	  inTree->SetBranchAddress("trg_singlemuon",&trg_singlemuon);
	  inTree->SetBranchAddress("trg_mutaucross",&trg_mutaucross);
	  
	  //branches for stichting
	  inTree->SetBranchAddress("gen_noutgoing",&gen_noutgoing);
	  
	  inTree->SetBranchAddress("embweight",&embweight);
	  inTree->SetBranchAddress("trigweight",&trigweight);
	  inTree->SetBranchAddress("mcweight",&mcweight);
	  inTree->SetBranchAddress("effweight",&effweight);
	  inTree->SetBranchAddress("puweight",&puweight);
	  inTree->SetBranchAddress("topptweight",&topptweight);
	  inTree->SetBranchAddress("zptweight",&zptweight);
	  inTree->SetBranchAddress("trkeffweight",&trkeffweight);
	  inTree->SetBranchAddress("weight",&weight);
	  
	  inTree->SetBranchAddress("njets",&njets);
	  inTree->SetBranchAddress("mjj",&mjj);
	  inTree->SetBranchAddress("jdeta",&jdeta);
	  inTree->SetBranchAddress("dijetpt",&dijetpt);
	  inTree->SetBranchAddress("jpt_1",&jpt_1);
	  inTree->SetBranchAddress("jpt_2",&jpt_2);
	  inTree->SetBranchAddress("jeta_1",&jeta_1);
	  inTree->SetBranchAddress("jeta_2",&jeta_2);
	  
	  inTree->SetBranchAddress("m_vis",&m_vis);      
	  inTree->SetBranchAddress("pt_tt",&pt_tt);
	  inTree->SetBranchAddress("mt_tot",&mt_tot);
	  inTree->SetBranchAddress("m_sv",&m_sv);
	  inTree->SetBranchAddress("pt_sv",&pt_sv);
	  inTree->SetBranchAddress("m_fast",&m_fast);
	  inTree->SetBranchAddress("pt_fast",&pt_fast);
	  
	  inTree->SetBranchAddress("puppimet",&puppimet);      
	  inTree->SetBranchAddress("puppimetphi",&puppimetphi);      
	  inTree->SetBranchAddress("os",&os);      
	  inTree->SetBranchAddress("nbtag",&nbtag);      
	  
	  //DeepTua branches
	  inTree->SetBranchAddress("byTightDeepTau2017v2p1VSmu_2",&byTightDeepTau2017v2p1VSmu_2);      
	  inTree->SetBranchAddress("byVLooseDeepTau2017v2p1VSe_2",&byVLooseDeepTau2017v2p1VSe_2);      
	  inTree->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSe_2",&byVVVLooseDeepTau2017v2p1VSe_2);
	  inTree->SetBranchAddress("byVLooseDeepTau2017v2p1VSmu_2",&byVLooseDeepTau2017v2p1VSmu_2);
	  inTree->SetBranchAddress("byTightDeepTau2017v2p1VSe_2",&byTightDeepTau2017v2p1VSe_2);      
	  inTree->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSjet_2",&byVVVLooseDeepTau2017v2p1VSjet_2);      
	  inTree->SetBranchAddress("byMediumDeepTau2017v2p1VSjet_2",&byMediumDeepTau2017v2p1VSjet_2);   
	  
	  inTree->SetBranchAddress("acotautau_refitbs_00",&acotautau_refitbs_00);
	  inTree->SetBranchAddress("acotautau_refitbs_01",&acotautau_refitbs_01);
	  
	  inTree->SetBranchAddress("acotautau_helix_00",&acotautau_helix_00);
	  inTree->SetBranchAddress("acotautau_helix_01",&acotautau_helix_01);
 	  
	  inTree->SetBranchAddress("acotautau_bs_00",&acotautau_bs_00);
 	  inTree->SetBranchAddress("acotautau_bs_01",&acotautau_bs_01);
 	  
 	  inTree->SetBranchAddress("acotautau_00",&acotautau_00);
 	  inTree->SetBranchAddress("acotautau_01",&acotautau_01);

	  
	  inTree->SetBranchAddress("acotautau_refitbs_uncorr_00",&acotautau_refitbs_uncorr_00);
	  inTree->SetBranchAddress("acotautau_refitbs_uncorr_01",&acotautau_refitbs_uncorr_01);
	  
	  inTree->SetBranchAddress("acotautau_helix_uncorr_00",&acotautau_helix_uncorr_00);
	  inTree->SetBranchAddress("acotautau_helix_uncorr_01",&acotautau_helix_uncorr_01);

 	  //inTree->SetBranchAddress("acotautau_bs_uncorr_00",&acotautau_bs_uncorr_00);
 	  //inTree->SetBranchAddress("acotautau_bs_uncorr_01",&acotautau_bs_uncorr_01);
 	  
 	  //inTree->SetBranchAddress("acotautau_uncorr_00",&acotautau_bs_uncorr_00);
 	  //inTree->SetBranchAddress("acotautau_uncorr_01",&acotautau_bs_uncorr_01);

	  inTree->SetBranchAddress("gen_sm_htt125", &gen_sm_htt125);
	  inTree->SetBranchAddress("gen_ps_htt125", &gen_ps_htt125);
	  inTree->SetBranchAddress("gen_mm_htt125", &gen_mm_htt125);
	  //inTree->SetBranchAddress("gen_minusmm_htt125", &TauSpinnerWeightsMinusMaxMix);
	  //inTree->SetBranchAddress("gen_mix0p375_htt125", &TauSpinnerWeightsMix0p375);



   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVUp);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVUp);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVUp);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVUp);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVUp", &weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVUp);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM0_13TeVDown);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM1_13TeVDown);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM2_13TeVDown);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM10_13TeVDown);
   	inTree->SetBranchAddress("weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVDown", &weight_CMS_eff_Xtrigger_mt_MVADM11_13TeVDown);


  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM0_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM0_13TeVUp); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM1_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM1_13TeVUp); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM2_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM2_13TeVUp); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM10_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM10_13TeVUp);
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM11_13TeVUp", &weight_CMS_eff_t_pTlow_MVADM11_13TeVUp);
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM0_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM0_13TeVUp);
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM1_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM1_13TeVUp);
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM2_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM2_13TeVUp);
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM10_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM10_13TeVUp); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM11_13TeVUp", &weight_CMS_eff_t_pThigh_MVADM11_13TeVUp); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM0_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM0_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM1_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM1_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM2_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM2_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM10_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM10_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pTlow_MVADM11_13TeVDown", &weight_CMS_eff_t_pTlow_MVADM11_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM0_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM0_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM1_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM1_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM2_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM2_13TeVDown); 
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM10_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM10_13TeVDown);
  	inTree->SetBranchAddress("weight_CMS_eff_t_pThigh_MVADM11_13TeVDown", &weight_CMS_eff_t_pThigh_MVADM11_13TeVDown);



   	inTree->SetBranchAddress("weight_CMS_scale_gg_13TeVUp", &weight_CMS_scale_gg_13TeVUp);
   	inTree->SetBranchAddress("weight_CMS_scale_gg_13TeVDown", &weight_CMS_scale_gg_13TeVDown);
	  

	  // lumi-xsec-weight added
	  if( xsec_map->find(subsample) == xsec_map->end() && !isData  && !isEmbedded){
	    cout << endl << endl << "Sample " << subsample << " is missing in xsec_map. Exit code." << endl << endl ;
	    exit(-1);
	  }
	  float xsec = 1;
	  if(!isData && !isEmbedded) xsec = xsec_map->at(subsample);
	  int counter=0;
	  
	  //cout << "Cross section : " << xsec << endl;

	  cout << "    entries in tree = " << inTree->GetEntries() << endl;
	  for (int i=0; i<(TEST ? 10000 : inTree->GetEntries()); i++) {
	    // for (int i=0; i<10000; i++) {
	      inTree->GetEntry(i);
	      if (i%100000==0){
		cout << "processed " << i << " events " << endl;
	      }
	      //Preselection
	      if(applyPreselection){
		bool is_trigger = false;
		bool is_singleLepTrigger = false;
		bool is_crossTrigger = false;
		if(channel=="mt"){
		  if( iso_1 > 0.15 )              continue;
		  if( pt_1 < 20)                  continue; 
		  if( pt_2 < 20)                  continue; 
		  if (abs(eta_1)>2.1)             continue;
		  if (abs(eta_2)>2.3)             continue;
		  if (era=="2016") {
		    is_singleLepTrigger = (trg_singlemuon>0.5&&pt_1>23&&abs(eta_1)<2.1);
		    is_crossTrigger = (trg_mutaucross>0.5&&pt_1>20&&abs(eta_1)<2.1&&pt_2>25);
		    is_trigger = is_singleLepTrigger || is_crossTrigger;
		  }
		  if (era=="2017"||era=="2018") {
		    is_singleLepTrigger = (trg_singlemuon>0.5&&pt_1>25);
                    is_crossTrigger = (trg_mutaucross>0.5&&pt_1>21&&abs(eta_1)<2.1&&pt_2>32&&abs(eta_2)<2.1);
                    is_trigger = is_singleLepTrigger || is_crossTrigger;
		  }
		  if( is_trigger < 0.5 ) continue;
		  if( byTightDeepTau2017v2p1VSmu_2 < 0.5) continue;
		  if( byVVVLooseDeepTau2017v2p1VSe_2 < 0.5 ) continue;
		  if( byVVVLooseDeepTau2017v2p1VSjet_2 < 0.5 ) continue;
		}else{
		  if( iso_1 > 0.10 )              continue;
		  else if( pt_1 < 20 )            continue; 
		  else if( pt_2 < 20 )            continue; 
		  if (abs(eta_1)>2.1)             continue;
		  if (abs(eta_2)>2.3)             continue;
		}
		if( extraelec_veto > 0.5 )       continue;
		if( nbtag!=0 )                   continue;
		if( extramuon_veto > 0.5 )       continue;
		if( dilepton_veto  > 0.5 )       continue;
		if( puppimt_1>50 )               continue;
		if( tau_decay_mode_2==0 && (dmMVA_2==1||dmMVA_2==2) ) continue;
		if( Sample.Contains("Uncorr") ){
		  if ( isnan(gen_sm_htt125) ||
		       isnan(gen_mm_htt125) ||
		       isnan(gen_ps_htt125) ){

		    cout << "Found NaN in TauSpinnerWeight -> event removed" <<endl;
		    continue;//remove events for which the TauSpinnerWeight was not computed correctly
		  }
		}
		if( isEmbedded && mcweight > 1000 ) continue;
	      }
	      //End of preselection


	      //FF method
	      if (byMediumDeepTau2017v2p1VSjet_2<0.5&&SystematicsName==""){

		pt_1_ = pt_1;
		pt_2_ = pt_2;
		m_vis_ = m_vis;
		mt_1_ = puppimt_1;
		pt_tt_ = pt_tt;
		met_ = puppimet;
		n_jets_ = njets;
		if(njets>1)mjj_=mjj;
		else mjj_ = 0;
		mva_dm_2_=dmMVA_2;
		std::vector<float> scores = reader_->EvaluateMulticlass("BDT method");
		double qcd_score = scores[1];
		double w_score = scores[0];
		double w_frac = ff_fracs_wjets_->GetBinContent(ff_fracs_wjets_->FindBin(qcd_score,w_score));
		double qcd_frac = ff_fracs_qcd_->GetBinContent(ff_fracs_qcd_->FindBin(qcd_score,w_score));
		double ttbar_frac = 1. - w_frac - qcd_frac;


		TLorentzVector MET(0.,0.,0.,0.);
		MET.SetPtEtaPhiM(puppimet,0.,puppimetphi,0);
		TLorentzVector MU(0.,0.,0.,0.);
		MU.SetPtEtaPhiM(pt_1,eta_1,phi_1,0);
		TLorentzVector FakeMET=MU+MET;
		float met_var_qcd, met_var_w;
		met_var_qcd=puppimet*TMath::Cos(DeltaPhi(puppimetphi,phi_2))/pt_2;
		met_var_w=FakeMET.Pt()*TMath::Cos(DeltaPhi(FakeMET.Phi(),phi_2))/pt_2;
		auto args = std::vector<double>{pt_2,
						static_cast<double>(tau_decay_mode_2),
						static_cast<double>(njets),
						pt_1,
						static_cast<double>(os),
						puppimt_1,
						iso_1,
						static_cast<double>(trg_singlemuon),
						m_vis};
		ff_nom = fns_["ff_mt_medium_dmbins"]->eval(args.data());

		auto args_mva = std::vector<double>{pt_2,
						    dmMVA_2,
						    IP_signif_RefitV_with_BS_2,
						    static_cast<double>(njets),
						    pt_1,
						    static_cast<double>(os),
						    iso_1,
						    static_cast<double>(trg_singlemuon),
						    met_var_qcd,
						    met_var_w,
						    FakeMET.Pt(),
						    w_frac,
						    qcd_frac,
						    ttbar_frac};
		ff_mva = fns_["ff_mt_medium_mvadmbins"]->eval(args_mva.data());

		///Weights for FF
		//Stat uncertainties
		weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltUp = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm0_sig_lt3_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltUp = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm0_sig_lt3_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltUp = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm0_sig_lt3_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltUp = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm0_sig_lt3_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltUp = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm0_sig_lt3_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltUp = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm0_sig_lt3_up"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtUp = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm0_sig_gt3_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtUp = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm0_sig_gt3_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtUp = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm0_sig_gt3_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtUp = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm0_sig_gt3_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtUp = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm0_sig_gt3_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtUp = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm0_sig_gt3_up"]->eval(args_mva.data());



		weight_ff_mt_wjets_stat_njets0_mvadm1Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm1_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm1Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm1_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm1Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm1_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm1Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm1_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm1Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm1_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm1Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm1_up"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm2Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm2_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm2Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm2_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm2Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm2_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm2Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm2_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm2Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm2_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm2Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm2_up"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm10Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm10_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm10Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm10_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm10Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm10_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm10Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm10_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm10Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm10_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm10Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm10_up"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm11Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm11_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm11Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm11_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm11Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm11_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm11Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm11_up"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm11Up = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm11_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm11Up = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm11_up"]->eval(args_mva.data());



		weight_ff_mt_wjets_stat_njets0_mvadm0_sig_ltDown = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm0_sig_lt3_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm0_sig_ltDown = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm0_sig_lt3_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm0_sig_ltDown = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm0_sig_lt3_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm0_sig_ltDown = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm0_sig_lt3_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm0_sig_ltDown = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm0_sig_lt3_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm0_sig_ltDown = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm0_sig_lt3_down"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm0_sig_gtDown = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm0_sig_gt3_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm0_sig_gtDown = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm0_sig_gt3_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm0_sig_gtDown = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm0_sig_gt3_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm0_sig_gtDown = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm0_sig_gt3_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm0_sig_gtDown = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm0_sig_gt3_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm0_sig_gtDown = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm0_sig_gt3_down"]->eval(args_mva.data());



		weight_ff_mt_wjets_stat_njets0_mvadm1Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm1_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm1Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm1_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm1Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm1_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm1Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm1_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm1Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm1_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm1Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm1_down"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm2Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm2_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm2Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm2_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm2Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm2_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm2Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm2_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm2Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm2_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm2Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm2_down"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm10Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm10_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm10Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm10_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm10Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm10_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm10Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm10_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm10Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm10_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm10Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm10_down"]->eval(args_mva.data());


		weight_ff_mt_wjets_stat_njets0_mvadm11Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet0_mvadm11_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets0_mvadm11Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet0_mvadm11_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets1_mvadm11Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet1_mvadm11_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets1_mvadm11Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet1_mvadm11_down"]->eval(args_mva.data());
		
		weight_ff_mt_wjets_stat_njets2_mvadm11Down = fns_["ff_mt_medium_mvadmbins_wjets_stat_njet2_mvadm11_down"]->eval(args_mva.data());
		weight_ff_mt_qcd_stat_njets2_mvadm11Down = fns_["ff_mt_medium_mvadmbins_qcd_stat_njet2_mvadm11_down"]->eval(args_mva.data());


		//met_var_qcd and met_var_w non-closure corrections

		weight_ff_mt_qcd_met_closure_systUp = fns_["ff_mt_medium_mvadmbins_qcd_met_up"]->eval(args_mva.data());
		weight_ff_mt_wjets_met_closure_systUp = fns_["ff_mt_medium_mvadmbins_wjets_met_up"]->eval(args_mva.data());
		weight_ff_mt_ttbar_met_closure_systUp = fns_["ff_mt_medium_mvadmbins_ttbar_met_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_met_closure_systDown = fns_["ff_mt_medium_mvadmbins_qcd_met_down"]->eval(args_mva.data());
		weight_ff_mt_wjets_met_closure_systDown = fns_["ff_mt_medium_mvadmbins_wjets_met_down"]->eval(args_mva.data());
		weight_ff_mt_ttbar_met_closure_systDown = fns_["ff_mt_medium_mvadmbins_ttbar_met_down"]->eval(args_mva.data());

		//m_pt non-closure corrections

		weight_ff_mt_qcd_l_pt_closure_systUp = fns_["ff_mt_medium_mvadmbins_qcd_l_pt_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_l_pt_closure_systDown = fns_["ff_mt_medium_mvadmbins_qcd_l_pt_down"]->eval(args_mva.data());
		weight_ff_mt_wjets_l_pt_closure_systUp = fns_["ff_mt_medium_mvadmbins_wjets_l_pt_up"]->eval(args_mva.data());
		weight_ff_mt_wjets_l_pt_closure_systDown = fns_["ff_mt_medium_mvadmbins_wjets_l_pt_down"]->eval(args_mva.data());

		//extrapolations from DR to SR
		weight_ff_mt_qcd_systUp = fns_["ff_mt_medium_mvadmbins_qcd_syst_up"]->eval(args_mva.data());
		weight_ff_mt_qcd_systDown = fns_["ff_mt_medium_mvadmbins_qcd_syst_down"]->eval(args_mva.data());
		weight_ff_mt_wjets_systUp = fns_["ff_mt_medium_mvadmbins_wjets_syst_up"]->eval(args_mva.data());
		weight_ff_mt_wjets_systDown = fns_["ff_mt_medium_mvadmbins_wjets_syst_down"]->eval(args_mva.data());
		weight_ff_mt_ttbar_systUp = fns_["ff_mt_medium_mvadmbins_ttbar_syst_up"]->eval(args_mva.data());
		weight_ff_mt_ttbar_systDown = fns_["ff_mt_medium_mvadmbins_ttbar_syst_down"]->eval(args_mva.data());

		//		cout << "ff_nom : " << ff_nom << "   ff_mva : " << ff_mva << endl;

		/// END of weights for FF

	      }else { 
		ff_nom = 1.;
		ff_mva = 1.;
	      }
	      
	      ff_sys = ff_nom; // TO DO: fix systematics

	      xsec_lumi_weight = xsec*luminosity/nevents;
	      qcd_correction = qcd_ss_os_iso_relaxed_ratio;
	      trigger_filter_weight = trigger_filter_efficiency;
	      /*
	      cout << "lumi = " << luminosity << endl;
	      cout << "xsec = " << xsec << endl;
	      cout << "nevents = " << nevents << endl;
	      cout << "XSecLumi = " << xsec_lumi_weight << endl;
	      */
	      // Initialize variables for jet observables to -10 for NN
	      if(njets < 2){
		jdeta   = -10;
		mjj     = -10;
		dijetpt = -10;
		//pt_ttjj = -10; 
		jpt_2   = -10;
		jeta_2  = -10;
		if(njets < 1){
		  jpt_1 = -10;
		  jeta_1= -10;
		}
	      }


	      // Stitching only for wjets MC in n-jet binned samples in gen_noutgoing
	      if( isW ){
		if(gen_noutgoing == 1)      xsec_lumi_weight = luminosity / ( neventsW1Jets/xsecW1Jets + neventsWIncl/xsecWIncl );
		else if(gen_noutgoing == 2) xsec_lumi_weight = luminosity / ( neventsW2Jets/xsecW2Jets + neventsWIncl/xsecWIncl );
		else if(gen_noutgoing == 3) xsec_lumi_weight = luminosity / ( neventsW3Jets/xsecW3Jets + neventsWIncl/xsecWIncl );
		else if(gen_noutgoing == 4) xsec_lumi_weight = luminosity / ( neventsW4Jets/xsecW4Jets + neventsWIncl/xsecWIncl );
		else                   xsec_lumi_weight = luminosity / ( neventsWIncl/xsecWIncl );
	      }
	      else if( isDY ){
		//	  cout<<"Number partons: "<<gen_noutgoing<<endl;
		if(gen_noutgoing == 1)      xsec_lumi_weight = luminosity / ( neventsDY1Jets/xsecDY1Jets + neventsDYIncl/xsecDYIncl );
		else if(gen_noutgoing == 2) xsec_lumi_weight = luminosity / ( neventsDY2Jets/xsecDY2Jets + neventsDYIncl/xsecDYIncl );
		else if(gen_noutgoing == 3) xsec_lumi_weight = luminosity / ( neventsDY3Jets/xsecDY3Jets + neventsDYIncl/xsecDYIncl );
		else if(gen_noutgoing == 4) xsec_lumi_weight = luminosity / ( neventsDY4Jets/xsecDY4Jets + neventsDYIncl/xsecDYIncl );
		else                   xsec_lumi_weight = luminosity / ( neventsDYIncl/xsecDYIncl );
	      }
          	
	      if( isData || isEmbedded ){
		xsec_lumi_weight = 1.;
		trigger_filter_weight = 1.;
	      }
	      if( isEmbedded && era == "2016"){
		embedded_stitching_weight = 
		  ((run >= 272007) && (run < 275657))*(1.0/0.891)
		  +((run >= 275657) && (run < 276315))*(1.0/0.910)
		  +((run >= 276315) && (run < 276831))*(1.0/0.953)
		  +((run >= 276831) && (run < 277772))*(1.0/0.947)
		  +((run >= 277772) && (run < 278820))*(1.0/0.942)
		  +((run >= 278820) && (run < 280919))*(1.0/0.906)
		  +((run >= 280919) && (run < 284045))*(1.0/0.950);
	      }
	      else embedded_stitching_weight = 1.;
	      
	      if (isData)
		weight = 1;
	      else if (isEmbedded) 
		weight = mcweight*effweight*embweight*embedded_stitching_weight;
	      else {
		weight = xsec_lumi_weight*mcweight*effweight*puweight;
		if (isDY){
		  weight *= zptweight;
		  weight_CMS_htt_dyShape_13TeVDown = 1./zptweight;
		  weight_CMS_htt_dyShape_13TeVUp = zptweight;
		}else if (isTTbar){
		  weight *= topptweight;
		  weight_CMS_htt_ttbarShape_13TeVDown = 1./topptweight;
		  weight_CMS_htt_ttbarShape_13TeVUp = topptweight;
		}
	      }

	      embedded_rate_weight = embedded_trigger_weight * embedded_tracking_weight;
	      
	      // add flags for cut categories which correspond to htxs_stage1cats
	      htxs_reco_flag_ggh = 0;
	      htxs_reco_flag_qqh = 0;
	      // reco bins 101 and 102 merged into 2jets categories (sicne hardly populated)
	      if(njets==0)                                    htxs_reco_flag_ggh = 103;
	      else if((njets==1) && (pt_tt>0)  &&(pt_tt<60))  htxs_reco_flag_ggh = 104;
	      else if((njets==1) && (pt_tt>60) &&(pt_tt<120)) htxs_reco_flag_ggh = 105;
	      else if((njets==1) && (pt_tt>120)&&(pt_tt<200)) htxs_reco_flag_ggh = 106;
	      else if((njets==1) && (pt_tt>200))              htxs_reco_flag_ggh = 107;
	      else if((njets>=2) && (pt_tt>0)  &&(pt_tt<60))  htxs_reco_flag_ggh = 108;
	      else if((njets>=2) && (pt_tt>60) &&(pt_tt<120)) htxs_reco_flag_ggh = 109;
	      else if((njets>=2) && (pt_tt>120)&&(pt_tt<200)) htxs_reco_flag_ggh = 110;
	      else if((njets>=2) && (pt_tt>200))              htxs_reco_flag_ggh = 111;
	      
	      //stxs categorization currently not used, kept commented
	      /*
          	if((jpt_1>0)&&(jpt_1<200)&&(njets>=2)&&(mjj>400)&&(jdeta>2.8)&&(pt_ttjj>0)&&(pt_ttjj<25)) htxs_reco_flag_qqh = 201;
          	else if((jpt_1>0)&&(jpt_1<200)&&(njets>=2)&&(mjj>400)&&(jdeta>2.8)&&(pt_ttjj>25)) htxs_reco_flag_qqh = 202;
          	else if((jpt_1>0)&&(jpt_1<200)&&(njets>=2)&&(mjj>60)&&(mjj<120)) htxs_reco_flag_qqh = 203;
          	else if(( (jpt_1>0&&jpt_1<200&&njets<2) || (jpt_1>0&&jpt_1<200&&njets>=2&&mjj>400&&jdeta<2.8) || (jpt_1>0&&jpt_1<200&&njets>=2&&mjj>0&&mjj<60) || (jpt_1>0&&jpt_1<200&&njets>=2&&mjj>120&&mjj<400))) htxs_reco_flag_qqh = 204;
          	else if(jpt_1>200) htxs_reco_flag_qqh = 205;*/
	      
	      // prefiring weights (from AN-18-255)
	      prefiring_weight=1;
	      if( sample.first.Contains("TTBar") && era == "2016")      prefiring_weight = 0.989;
	      else if( sample.first.Contains("TTBar") && era == "2017") prefiring_weight = 0.984;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 201 && era == "2016") prefiring_weight = 0.972;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 201 && era == "2017") prefiring_weight = 0.950;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 202 && era == "2016") prefiring_weight = 0.972;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 202 && era == "2017") prefiring_weight = 0.950;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 203 && era == "2016") prefiring_weight = 0.972;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 203 && era == "2017") prefiring_weight = 0.950;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 204 && era == "2016") prefiring_weight = 0.983;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 204 && era == "2017") prefiring_weight = 0.970;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 205 && era == "2016") prefiring_weight = 0.920;
	      else if( sample.first.Contains("VBFH") && htxs_reco_flag_qqh == 205 && era == "2017") prefiring_weight = 0.850;
	      
	      //stxs categorization currently not used, kept commented
	      /*
	      // Select hadronic and leptonic part of VH sample
	      if( subsample.Contains("VH") || subsample.Contains("WplusH") || subsample.Contains("WminusH") ){
	      if( sample.first.Contains("VBFH") && (htxs_stage1cat>206 || htxs_stage1cat<200) ) continue;
	      if( (sample.first.Contains("WH") || sample.first.Contains("ZH")) && htxs_stage1cat<=206 && htxs_stage1cat>=200 ) continue;
	      }*/
	      
	      outTree->Fill();
          } //
	  //          cout<<currentTree->GetEntries()<<endl;
	  //          treeList->Add(currentTree);
          inFile->Close();
	  delete inFile;
          // //fill xsec_lumi_weight in a histogram for reference, and write to the tree
          // TH1F* xsec_lumi_weightH=new TH1F("xsec_lumi_weightH","xsec_lumi_weightH",1,0,1);
          // xsec_lumi_weightH->Fill(0.5,xsec_lumi_weight);
          // xsec_lumi_weightH->Write();
          // delete xsec_lumi_weightH;          
        }
	if (outTree==NULL) continue; 
	cout<< " entries in out tree : " << outTree->GetEntries() << endl;
	if (outTree->GetEntries()>0) {
	  outFile->cd("");
	  outTree->Write(TreeName,TObject::kOverwrite);
	}
	cout << endl; 
    }
    cout << outFile << endl;
    outFile  -> Close();
    cout << endl; 
    cout << endl; 
    cout << endl; 
  }

}
