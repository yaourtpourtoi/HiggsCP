#ifndef SETTINGS_FOR_ERAS_H
#define SETTINGS_FOR_ERAS_H

using namespace std;

float DeltaPhi(float phi1, float phi2){
  float deltaphi=fabs(phi1-phi2);
  if(deltaphi>TMath::Pi()) deltaphi=2*TMath::Pi()-deltaphi;
  return deltaphi;
}


// **************************************************************************************************
// Define the subsamples that belong to a certain process
// 2018

const TString BaseTreeName = "TauCheck"; 
vector<TString> SystematicsNames = {"",  
				    "CMS_scale_t_1prong_13TeVUp",
				    "CMS_scale_t_1prong_13TeVDown",
				    "CMS_scale_t_1prong1pizero_13TeVUp",
				    "CMS_scale_t_1prong1pizero_13TeVDown",
				    "CMS_scale_t_3prong_13TeVUp",
				    "CMS_scale_t_3prong_13TeVDown",
				    "CMS_scale_t_3prong1pizero_13TeVUp",
				    "CMS_scale_t_3prong1pizero_13TeVDown",
				    "CMS_scale_met_unclustered_13TeVUp",
				    "CMS_scale_met_unclustered_13TeVDown",
				    "CMS_scale_met_boson_resolution_13TeVUp",
				    "CMS_scale_met_boson_resolution_13TeVDown",
				    "CMS_scale_met_boson_response_13TeVUp",
				    "CMS_scale_met_boson_response_13TeVDown",
				    "CMS_htt_boson_reso_met_13TeVUp",
				    "CMS_htt_boson_reso_met_13TeVDown",
				    "CMS_htt_boson_scale_met_13TeVUp",
				    "CMS_htt_boson_scale_met_13TeVDown",
				    "CMS_htt_ZLShape_1prong_13TeVUp",
				    "CMS_htt_ZLShape_1prong_13TeVDown",
				    "CMS_htt_ZLShape_1prong1pi_13TeVUp",
				    "CMS_htt_ZLShape_1prong1pi_13TeVDown",
				    "CMS_eff_b_13TeVUp",
				    "CMS_eff_b_13TeVDown",
				    "CMS_scale_j_FlavorQCD_13TeVUp",
				    "CMS_scale_j_FlavorQCD_13TeVDown",
				    "CMS_scale_j_RelativeBal_13TeVUp",
				    "CMS_scale_j_RelativeBal_13TeVDown",
				    "CMS_scale_j_HF_13TeVUp",
				    "CMS_scale_j_HF_13TeVDown",
				    "CMS_scale_j_BBEC1_13TeVUp",
				    "CMS_scale_j_BBEC1_13TeVDown",
				    "CMS_scale_j_EC2_13TeVUp",
				    "CMS_scale_j_EC2_13TeVDown",
				    "CMS_scale_j_Absolute_13TeVUp",
				    "CMS_scale_j_Absolute_13TeVDown",
				    "CMS_scale_j_Absolute_2016_13TeVUp",
				    "CMS_scale_j_Absolute_2016_13TeVDown",
				    "CMS_scale_j_HF_2016_13TeVUp",
				    "CMS_scale_j_HF_2016_13TeVDown",
				    "CMS_scale_j_EC2_2016_13TeVUp",
				    "CMS_scale_j_EC2_2016_13TeVDown",
				    "CMS_scale_j_RelativeSample_2016_13TeVUp",
				    "CMS_scale_j_RelativeSample_2016_13TeVDown",
				    "CMS_scale_j_BBEC1_2016_13TeVUp",
				    "CMS_scale_j_BBEC1_2016_13TeVDown",
				    "CMS_scale_j_Absolute_2017_13TeVUp",
				    "CMS_scale_j_Absolute_2017_13TeVDown",
				    "CMS_scale_j_HF_2017_13TeVUp",
				    "CMS_scale_j_HF_2017_13TeVDown",
				    "CMS_scale_j_EC2_2017_13TeVUp",
				    "CMS_scale_j_EC2_2017_13TeVDown",
				    "CMS_scale_j_RelativeSample_2017_13TeVUp",
				    "CMS_scale_j_RelativeSample_2017_13TeVDown",
				    "CMS_scale_j_BBEC1_2017_13TeVUp",
				    "CMS_scale_j_BBEC1_2017_13TeVDown",
				    "CMS_scale_j_Absolute_2018_13TeVUp",
				    "CMS_scale_j_Absolute_2018_13TeVDown",
				    "CMS_scale_j_HF_2018_13TeVUp",
				    "CMS_scale_j_HF_2018_13TeVDown",
				    "CMS_scale_j_EC2_2018_13TeVUp",
				    "CMS_scale_j_EC2_2018_13TeVDown",
				    "CMS_scale_j_RelativeSample_2018_13TeVUp",
				    "CMS_scale_j_RelativeSample_2018_13TeVDown",
				    "CMS_scale_j_BBEC1_2018_13TeVUp",
				    "CMS_scale_j_BBEC1_2018_13TeVDown",
				    "CMS_scale_mu_13TeVUp",
				    "CMS_scale_mu_13TeVDown",
				    "CMS_res_j_13TeVUp",
				    "CMS_res_j_13TeVDown"
};

const vector<TString>SystematicsFF={
  //stat
    "wjets_stat_unc1_njet0_mvadm0_sig_lt3_up",
    "wjets_stat_unc1_njet0_mvadm0_sig_lt3_down",
    "qcd_stat_unc1_njet0_mvadm0_sig_lt3_up",
    "qcd_stat_unc1_njet0_mvadm0_sig_lt3_down",
    "wjets_stat_unc1_njet1_mvadm0_sig_lt3_up",
    "wjets_stat_unc1_njet1_mvadm0_sig_lt3_down",
    "qcd_stat_unc1_njet1_mvadm0_sig_lt3_up",
    "qcd_stat_unc1_njet1_mvadm0_sig_lt3_down",
    "wjets_stat_unc1_njet2_mvadm0_sig_lt3_up",
    "wjets_stat_unc1_njet2_mvadm0_sig_lt3_down",
    "qcd_stat_unc1_njet2_mvadm0_sig_lt3_up",
    "qcd_stat_unc1_njet2_mvadm0_sig_lt3_down",

    "wjets_stat_unc1_njet0_mvadm0_sig_gt3_up",
    "wjets_stat_unc1_njet0_mvadm0_sig_gt3_down",
    "qcd_stat_unc1_njet0_mvadm0_sig_gt3_up",
    "qcd_stat_unc1_njet0_mvadm0_sig_gt3_down",
    "wjets_stat_unc1_njet1_mvadm0_sig_gt3_up",
    "wjets_stat_unc1_njet1_mvadm0_sig_gt3_down",
    "qcd_stat_unc1_njet1_mvadm0_sig_gt3_up",
    "qcd_stat_unc1_njet1_mvadm0_sig_gt3_down",
    "wjets_stat_unc1_njet2_mvadm0_sig_gt3_up",
    "wjets_stat_unc1_njet2_mvadm0_sig_gt3_down",
    "qcd_stat_unc1_njet2_mvadm0_sig_gt3_up",
    "qcd_stat_unc1_njet2_mvadm0_sig_gt3_down",

    "wjets_stat_unc1_njet0_mvadm1_up",
    "wjets_stat_unc1_njet0_mvadm1_down",
    "qcd_stat_unc1_njet0_mvadm1_up",
    "qcd_stat_unc1_njet0_mvadm1_down",
    "wjets_stat_unc1_njet1_mvadm1_up",
    "wjets_stat_unc1_njet1_mvadm1_down",
    "qcd_stat_unc1_njet1_mvadm1_up",
    "qcd_stat_unc1_njet1_mvadm1_down",
    "wjets_stat_unc1_njet2_mvadm1_up",
    "wjets_stat_unc1_njet2_mvadm1_down",
    "qcd_stat_unc1_njet2_mvadm1_up",
    "qcd_stat_unc1_njet2_mvadm1_down",

    "wjets_stat_unc1_njet0_mvadm2_up",
    "wjets_stat_unc1_njet0_mvadm2_down",
    "qcd_stat_unc1_njet0_mvadm2_up",
    "qcd_stat_unc1_njet0_mvadm2_down",
    "wjets_stat_unc1_njet1_mvadm2_up",
    "wjets_stat_unc1_njet1_mvadm2_down",
    "qcd_stat_unc1_njet1_mvadm2_up",
    "qcd_stat_unc1_njet1_mvadm2_down",
    "wjets_stat_unc1_njet2_mvadm2_up",
    "wjets_stat_unc1_njet2_mvadm2_down",
    "qcd_stat_unc1_njet2_mvadm2_up",
    "qcd_stat_unc1_njet2_mvadm2_down",

    "wjets_stat_unc1_njet0_mvadm10_up",
    "wjets_stat_unc1_njet0_mvadm10_down",
    "qcd_stat_unc1_njet0_mvadm10_up",
    "qcd_stat_unc1_njet0_mvadm10_down",
    "wjets_stat_unc1_njet1_mvadm10_up",
    "wjets_stat_unc1_njet1_mvadm10_down",
    "qcd_stat_unc1_njet1_mvadm10_up",
    "qcd_stat_unc1_njet1_mvadm10_down",
    "wjets_stat_unc1_njet2_mvadm10_up",
    "wjets_stat_unc1_njet2_mvadm10_down",
    "qcd_stat_unc1_njet2_mvadm10_up",
    "qcd_stat_unc1_njet2_mvadm10_down",

    "wjets_stat_unc1_njet0_mvadm11_up",
    "wjets_stat_unc1_njet0_mvadm11_down",
    "qcd_stat_unc1_njet0_mvadm11_up",
    "qcd_stat_unc1_njet0_mvadm11_down",
    "wjets_stat_unc1_njet1_mvadm11_up",
    "wjets_stat_unc1_njet1_mvadm11_down",
    "qcd_stat_unc1_njet1_mvadm11_up",
    "qcd_stat_unc1_njet1_mvadm11_down",
    "wjets_stat_unc1_njet2_mvadm11_up",
    "wjets_stat_unc1_njet2_mvadm11_down",
    "qcd_stat_unc1_njet2_mvadm11_up",
    "qcd_stat_unc1_njet2_mvadm11_down",
    //unc2
    "wjets_stat_unc2_njet0_mvadm0_sig_lt3_up",
    "wjets_stat_unc2_njet0_mvadm0_sig_lt3_down",
    "qcd_stat_unc2_njet0_mvadm0_sig_lt3_up",
    "qcd_stat_unc2_njet0_mvadm0_sig_lt3_down",
    "wjets_stat_unc2_njet1_mvadm0_sig_lt3_up",
    "wjets_stat_unc2_njet1_mvadm0_sig_lt3_down",
    "qcd_stat_unc2_njet1_mvadm0_sig_lt3_up",
    "qcd_stat_unc2_njet1_mvadm0_sig_lt3_down",
    "wjets_stat_unc2_njet2_mvadm0_sig_lt3_up",
    "wjets_stat_unc2_njet2_mvadm0_sig_lt3_down",
    "qcd_stat_unc2_njet2_mvadm0_sig_lt3_up",
    "qcd_stat_unc2_njet2_mvadm0_sig_lt3_down",

    "wjets_stat_unc2_njet0_mvadm0_sig_gt3_up",
    "wjets_stat_unc2_njet0_mvadm0_sig_gt3_down",
    "qcd_stat_unc2_njet0_mvadm0_sig_gt3_up",
    "qcd_stat_unc2_njet0_mvadm0_sig_gt3_down",
    "wjets_stat_unc2_njet1_mvadm0_sig_gt3_up",
    "wjets_stat_unc2_njet1_mvadm0_sig_gt3_down",
    "qcd_stat_unc2_njet1_mvadm0_sig_gt3_up",
    "qcd_stat_unc2_njet1_mvadm0_sig_gt3_down",
    "wjets_stat_unc2_njet2_mvadm0_sig_gt3_up",
    "wjets_stat_unc2_njet2_mvadm0_sig_gt3_down",
    "qcd_stat_unc2_njet2_mvadm0_sig_gt3_up",
    "qcd_stat_unc2_njet2_mvadm0_sig_gt3_down",

    "wjets_stat_unc2_njet0_mvadm1_up",
    "wjets_stat_unc2_njet0_mvadm1_down",
    "qcd_stat_unc2_njet0_mvadm1_up",
    "qcd_stat_unc2_njet0_mvadm1_down",
    "wjets_stat_unc2_njet1_mvadm1_up",
    "wjets_stat_unc2_njet1_mvadm1_down",
    "qcd_stat_unc2_njet1_mvadm1_up",
    "qcd_stat_unc2_njet1_mvadm1_down",
    "wjets_stat_unc2_njet2_mvadm1_up",
    "wjets_stat_unc2_njet2_mvadm1_down",
    "qcd_stat_unc2_njet2_mvadm1_up",
    "qcd_stat_unc2_njet2_mvadm1_down",

    "wjets_stat_unc2_njet0_mvadm2_up",
    "wjets_stat_unc2_njet0_mvadm2_down",
    "qcd_stat_unc2_njet0_mvadm2_up",
    "qcd_stat_unc2_njet0_mvadm2_down",
    "wjets_stat_unc2_njet1_mvadm2_up",
    "wjets_stat_unc2_njet1_mvadm2_down",
    "qcd_stat_unc2_njet1_mvadm2_up",
    "qcd_stat_unc2_njet1_mvadm2_down",
    "wjets_stat_unc2_njet2_mvadm2_up",
    "wjets_stat_unc2_njet2_mvadm2_down",
    "qcd_stat_unc2_njet2_mvadm2_up",
    "qcd_stat_unc2_njet2_mvadm2_down",

    "wjets_stat_unc2_njet0_mvadm10_up",
    "wjets_stat_unc2_njet0_mvadm10_down",
    "qcd_stat_unc2_njet0_mvadm10_up",
    "qcd_stat_unc2_njet0_mvadm10_down",
    "wjets_stat_unc2_njet1_mvadm10_up",
    "wjets_stat_unc2_njet1_mvadm10_down",
    "qcd_stat_unc2_njet1_mvadm10_up",
    "qcd_stat_unc2_njet1_mvadm10_down",
    "wjets_stat_unc2_njet2_mvadm10_up",
    "wjets_stat_unc2_njet2_mvadm10_down",
    "qcd_stat_unc2_njet2_mvadm10_up",
    "qcd_stat_unc2_njet2_mvadm10_down",

    "wjets_stat_unc2_njet0_mvadm11_up",
    "wjets_stat_unc2_njet0_mvadm11_down",
    "qcd_stat_unc2_njet0_mvadm11_up",
    "qcd_stat_unc2_njet0_mvadm11_down",
    "wjets_stat_unc2_njet1_mvadm11_up",
    "wjets_stat_unc2_njet1_mvadm11_down",
    "qcd_stat_unc2_njet1_mvadm11_up",
    "qcd_stat_unc2_njet1_mvadm11_down",
    "wjets_stat_unc2_njet2_mvadm11_up",
    "wjets_stat_unc2_njet2_mvadm11_down",
    "qcd_stat_unc2_njet2_mvadm11_up",
    "qcd_stat_unc2_njet2_mvadm11_down",

    "qcd_met_up",
    "wjets_met_up",
    "ttbar_met_up",

    "qcd_met_down",
    "wjets_met_down",
    "ttbar_met_down",

    "qcd_l_pt_up",
    "wjets_l_pt_up",

    "qcd_l_pt_down",
    "wjets_l_pt_down",

    "qcd_syst_up",
    "wjets_syst_up",
    "ttbar_syst_up",

    "qcd_syst_down",
    "wjets_syst_down",
    "ttbar_syst_down"
};


const vector<TString> SingleMuon_2018       = { "SingleMuon_Run2018A",
						"SingleMuon_Run2018B", 
						"SingleMuon_Run2018C",
						"SingleMuon_Run2018D"};

const vector<TString> SingleElectron_2018       = { "EGamma_Run2018A",
						    "EGamma_Run2018B", 
						    "EGamma_Run2018C",
						    "EGamma_Run2018D"};

const vector<TString> EmbeddedMuTau_2018        = { 
  //  "Embedded_Run2018"
  "EmbeddedMuTau_Run2018A",
  "EmbeddedMuTau_Run2018B",
  "EmbeddedMuTau_Run2018C",
  "EmbeddedMuTau_Run2018D"
};
const vector<TString> EmbeddedElTau_2018        = { "EmbeddingElTau_Run2018A",
						    "EmbeddingElTau_Run2018B",
						    "EmbeddingElTau_Run2018C",
						    "EmbeddingElTau_Run2018D"};
const vector<TString> DYJets_2018          = { "DY1JetsToLL_M-50" ,
					       "DY2JetsToLL_M-50" ,
                                               "DY3JetsToLL_M-50" ,
                                               "DY4JetsToLL_M-50" ,
                                               "DYJetsToLL_M-50"};
const vector<TString> WJets_2018           = { "W1JetsToLNu" ,
                                               "W2JetsToLNu" ,
                                               "W3JetsToLNu" ,
                                               "W4JetsToLNu" ,
                                               "WJetsToLNu",
					       "EWKWPlus2Jets_WToLNu_M-50",
					       "EWKWMinus2Jets_WToLNu_M-50",
					       };
const vector<TString> TTbar_2018           = { "TTTo2L2Nu" ,
                                               "TTToHadronic" ,
                                               "TTToSemiLeptonic" };
const vector<TString> SingleTop_2018       = { "ST_t-channel_antitop_4f" ,
                                               "ST_t-channel_top_4f" ,
                                               "ST_tW_antitop_5f" ,
                                               "ST_tW_top_5f" };
const vector<TString> Diboson_2018         = { "VVTo2L2Nu",
					       "WZTo2L2Q",
					       "WZTo3LNu",
					       "ZZTo2L2Q",
					       "ZZTo4L",
					       "ST_t-channel_antitop_4f" ,
                                               "ST_t-channel_top_4f" ,
                                               "ST_tW_antitop_5f" ,
                                               "ST_tW_top_5f" };
const vector<TString> EWKZ_2018            = {"EWKZ2Jets_ZToLL_M-50",
					      "EWKZ2Jets_ZToNuNu"};

const vector<TString> GluGluHToTauTau_2018 = { "GluGluHToTauTau_M125" };
const vector<TString> VBFHToTauTau_2018    = { "VBFHToTauTau_M125"}; 
const vector<TString> GluGluHToUncorrTauTau_2018 = { "GluGluHToTauTauUncorrDecays_M125" };
const vector<TString> VBFHToUncorrTauTau_2018 = { "VBFHToTauTauUncorrDecays_M125"};
const vector<TString> WHToUncorrTauTau_2018   = {"WplusHToTauTauUncorrDecays_M125","WminusHToTauTauUncorrDecays_M125"};
const vector<TString> ZHToUncorrTauTau_2018       = {"ZHToTauTauUncorrDecays_M125" };

const vector<TString> HToWW_2018         = { "GluGluHToWWTo2L2Nu_M125",
					     "VBFHToWWTo2L2Nu_M125",
					     "GluGluZH_HToWW_M125",
					     "HWminusJ_HToWW_M125",
					     "HWplusJ_HToWW_M125",
					     "HZJ_HToWW_M125"};

// 2017
const vector<TString> SingleMuon_2017       = {"SingleMuon_Run2017B",
					       "SingleMuon_Run2017C",
					       "SingleMuon_Run2017D",
					       "SingleMuon_Run2017E",
					       "SingleMuon_Run2017F"};
const vector<TString> SingleElectron_2017       = {"SingleElectron_Run2017B",
						   "SingleElectron_Run2017C",
						   "SingleElectron_Run2017D",
						   "SingleElectron_Run2017E",
						   "SingleElectron_Run2017F"};
const vector<TString> EmbeddedMuTau_2017        = { "EmbeddedMuTau_Run2017B",
						    "EmbeddedMuTau_Run2017C",
						    "EmbeddedMuTau_Run2017D",
						    "EmbeddedMuTau_Run2017E",
						    "EmbeddedMuTau_Run2017F"};
const vector<TString> EmbeddedElTau_2017        = { "EmbeddingElTau_Run2017B",
						    "EmbeddingElTau_Run2017C",
						    "EmbeddingElTau_Run2017D",
						    "EmbeddingElTau_Run2017E",
						    "EmbeddingElTau_Run2017F"};
const vector<TString> Embedded_2017        = { "Embedding_Run2017" };
const vector<TString> DYJets_2017          = { "DY1JetsToLL_M-50" ,
					       "DY2JetsToLL_M-50" ,
					       "DY3JetsToLL_M-50" ,
					       "DY4JetsToLL_M-50" ,
					       "DYJetsToLL_M-50"/*,
								  "EWKZ2Jets_ZToLL_M-50_TuneCP5_13TeV-madgraph-pythia8",
								  "EWKZ2Jets_ZToNuNu_TuneCP5_13TeV-madgraph-pythia8"*/};
const vector<TString> WJets_2017           = { "W1JetsToLNu" ,
					       "W2JetsToLNu" ,
					       "W3JetsToLNu" ,
					       "W4JetsToLNu" ,
					       "WJetsToLNu"  ,
					       "EWKWPlus2Jets_WToLNu_M-50",
					       "EWKWMinus2Jets_WToLNu_M-50",
					      
					       /*"WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8",
					       "EWKWMinus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8" ,
					       "EWKWPlus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8"*/};
const vector<TString> TTbar_2017           = { "TTTo2L2Nu" ,
					       "TTToHadronic" ,
					       "TTToSemiLeptonic" };
const vector<TString> SingleTop_2017       = { "ST_t-channel_antitop_4f" ,
					       "ST_t-channel_top_4f" ,
					       "ST_tW_antitop_5f" ,
					       "ST_tW_top_5f" };
const vector<TString> Diboson_2017         = { "VVTo2L2Nu",
					       "WZTo2L2Q",
					       "WZTo3LNu",
					       "ZZTo2L2Q",
					       "ZZTo4L",
					       "ST_t-channel_antitop_4f" ,
					       "ST_t-channel_top_4f" ,
					       "ST_tW_antitop_5f" ,
					       "ST_tW_top_5f" };
const vector<TString> EWKZ_2017            = {"EWKZ2Jets_ZToLL_M-50",
					      "EWKZ2Jets_ZToNuNu"};
const vector<TString> GluGluHToTauTau_2017 = { "GluGluHToTauTau_M125" };
const vector<TString> SUSYGluGluToHToTauTau_2017 = { "SUSYGluGluToHToTauTau" };
const vector<TString> VBFHToTauTau_2017    = { "VBFHToTauTau_M125"
					       /* "ZHToTauTau_M125_13TeV_powheg_pythia8",
					       "WplusHToTauTau_M125_13TeV_powheg_pythia8",
					       "WminusHToTauTau_M125_13TeV_powheg_pythia8"*/}; 
const vector<TString> GluGluHToUncorrTauTau_2017 = { "GluGluHToTauTauUncorrDecays_M125" };
const vector<TString> VBFHToUncorrTauTau_2017 = { "VBFHToTauTauUncorrDecays_M125" };
const vector<TString> VHToUncorrTauTau_2017      = { "WminusHToTauTauUncorrDecays_M125","WplusHToTauTauUncorrDecays_M125","ZHToTauTauUncorrDecays_M125" };

const vector<TString> WHToUncorrTauTau_2017   = {"WplusHToTauTauUncorrDecays_M125","WminusHToTauTauUncorrDecays_M125"};
const vector<TString> ZHToUncorrTauTau_2017       = {"ZHToTauTauUncorrDecays_M125" };
const vector<TString> HToWW_2017         = { "GluGluHToWWTo2L2Nu_M125",
					       "VBFHToWWTo2L2Nu_M125",
					       "GluGluZH_HToWW_M125",
					       "HWminusJ_HToWW_M125",
					       "HWplusJ_HToWW_M125",
					       "HZJ_HToWW_M125"};

//the 2017 samples below seem not needed for mu-tau
const vector<TString> ZHToTauTau_2017      = { "ZHToTauTau_M125" };//seems absent for mutau
const vector<TString> WHToTauTau_2017      = { "WplusHToTauTau_M125" , "WminusHToTauTau_M125" };//seems absent for mutau
const vector<TString> ggHToWW_2017         = { "GluGluHToWWTo2L2Nu" }; //seems absent for mu-tau
const vector<TString> VBFHToWW_2017        = { "VBFHToWWTo2L2Nu_M125" };//seems absent for mu-tau
const vector<TString> ttH_2017             = { "ttHToTauTau_M125" };//seems absent for mu-tau

// 2016
const vector<TString> SingleMuon_2016       = { "SingleMuon_Run2016B" ,
						"SingleMuon_Run2016C" ,
						"SingleMuon_Run2016D" ,
						"SingleMuon_Run2016E" ,
						"SingleMuon_Run2016F" ,
						"SingleMuon_Run2016G" ,
						   "SingleMuon_Run2016H" };

const vector<TString> SingleElectron_2016       = { "SingleElectron_Run2016B" ,
						    "SingleElectron_Run2016C" ,
						    "SingleElectron_Run2016D" ,
						    "SingleElectron_Run2016E" ,
						    "SingleElectron_Run2016F" ,
						    "SingleElectron_Run2016G" ,
						    "SingleElectron_Run2016H" };

const vector<TString> EmbeddedElTau_2016       = { "EmbeddedElTau_Run2016B" ,
						   "EmbeddedElTau_Run2016C" ,
						   "EmbeddedElTau_Run2016D" ,
						   "EmbeddedElTau_Run2016E" ,
						   "EmbeddedElTau_Run2016F" ,
						   "EmbeddedElTau_Run2016G" ,
						   "EmbeddedElTau_Run2016H" };
const vector<TString> EmbeddedMuTau_2016       = { "EmbeddedMuTau_Run2016B" ,
						   "EmbeddedMuTau_Run2016C" ,
						   "EmbeddedMuTau_Run2016D" ,
						   "EmbeddedMuTau_Run2016E" ,
						   "EmbeddedMuTau_Run2016F" ,
						   "EmbeddedMuTau_Run2016G" ,
						   "EmbeddedMuTau_Run2016H" };
const vector<TString> Embedded_2016        = { "Embedding_Run2016" };
const vector<TString> DYJets_2016          = { "DY1JetsToLL_M-50",
					       "DY2JetsToLL_M-50",
					       "DY3JetsToLL_M-50",
					       "DY4JetsToLL_M-50",
					       "DYJetsToLL_M-50"};
					       //"DYJetsToLL_M-10to50";
const vector<TString> WJets_2016           = { "W1JetsToLNu",
					       "W2JetsToLNu", 
					       "W3JetsToLNu", 
					       "W4JetsToLNu", 
					       "WJetsToLNu" ,
					       "EWKWPlus2Jets_WToLNu_M-50",
					       "EWKWMinus2Jets_WToLNu_M-50",
					      };
const vector<TString> TTbar_2016           = { "TTTo2L2Nu" ,
                                               "TTToHadronic" ,
                                               "TTToSemiLeptonic" };
const vector<TString> SingleTop_2016       = { "ST_t-channel_antitop_4f", 
					       "ST_t-channel_top_4f", 
					       "ST_tW_antitop_5f", 
					       "ST_tW_top_5f" };
//const vector<TString> Diboson_2016         = { "VVTo2L2Nu" , "WZJToLLLNu" , "WZTo1L1Nu2Q" , "WZTo1L3Nu" , "WZTo2L2Q" , "ZZTo2L2Q" , "ZZTo4L" , "WWToLNuQQ" };
const vector<TString> Diboson_2016         = { "VVTo2L2Nu",
					       "WZTo2L2Q",
					       "WZTo3LNu",
					       "ZZTo2L2Q",
					       "ZZTo4L",
					       "ST_t-channel_antitop_4f", 
					       "ST_t-channel_top_4f", 
					       "ST_tW_antitop_5f", 
					       "ST_tW_top_5f" };
const vector<TString> EWKZ_2016            = {"EWKZ2Jets_ZToLL_M-50",
					      "EWKZ2Jets_ZToNuNu"};

const vector<TString> GluGluHToUncorrTauTau_2016 = { "GluGluHToTauTauUncorrDecays_M125" };
const vector<TString> VBFHToUncorrTauTau_2016 = { "VBFHToTauTauUncorrDecays_M125" };
const vector<TString> VHToUncorrTauTau_2016      = { "WminusHToTauTauUncorrDecays_M125","WplusHToTauTauUncorrDecays_M125","ZHToTauTauUncorrDecays_M125" };

const vector<TString> WHToUncorrTauTau_2016   = {"WplusHToTauTauUncorrDecays_M125","WminusHToTauTauUncorrDecays_M125"};
const vector<TString> ZHToUncorrTauTau_2016       = {"ZHToTauTauUncorrDecays_M125" };
const vector<TString> HToWW_2016 = { "GluGluHToWWTo2L2Nu_M125",
				     "VBFHToWWTo2L2Nu_M125",
				     "GluGluZH_HToWW_M125",
				     "HWminusJ_HToWW_M125",
				     "HWplusJ_HToWW_M125",
				     "HZJ_HToWW_M125"};

const vector<TString> ZHToTauTau_2016      = { "ZHToTauTau_M125" };
const vector<TString> WHToTauTau_2016      = { "WplusHToTauTau_M125" , "WminusHToTauTau_M125" };
const vector<TString> ggHToWW_2016         = { "GluGluHToWWTo2L2Nu_M125" };
const vector<TString> VBFHToWW_2016        = { "VBFHToWWTo2L2Nu_M125" };
const vector<TString> ttH_2016             = { "ttHJetToTT_M125" };

const map<TString, vector<TString> > map_sample = {
  {"SingleMuon_2018", SingleMuon_2018},
  {"SingleMuon_2017", SingleMuon_2017},
  {"SingleMuon_2016", SingleMuon_2016},
  
  {"SingleElectron_2018", SingleElectron_2018},
  {"SingleElectron_2017", SingleElectron_2017},
  {"SingleElectron_2016", SingleElectron_2016},

  {"EmbeddedMuTau_2018", EmbeddedMuTau_2018},
  {"EmbeddedMuTau_2017", EmbeddedMuTau_2017},
  {"EmbeddedMuTau_2016", EmbeddedMuTau_2016},

  {"EmbeddedElTau_2018", EmbeddedElTau_2018},
  {"EmbeddedElTau_2017", EmbeddedElTau_2017},
  {"EmbeddedElTau_2016", EmbeddedElTau_2016},

  {"DYJets_2018",DYJets_2018},
  {"DYJets_2017",DYJets_2017},
  {"DYJets_2016",DYJets_2016},

  {"WJets_2018",WJets_2018},
  {"WJets_2017",WJets_2017},
  {"WJets_2016",WJets_2016},

  {"TTbar_2018",TTbar_2018},
  {"TTbar_2017",TTbar_2017},
  {"TTbar_2016",TTbar_2016},

  {"SingleTop_2018",SingleTop_2018},
  {"SingleTop_2017",SingleTop_2017},
  {"SingleTop_2016",SingleTop_2016},

  {"EWKZ_2018",EWKZ_2018},
  {"EWKZ_2017",EWKZ_2017},
  {"EWKZ_2016",EWKZ_2016},

  {"Diboson_2018",Diboson_2018},
  {"Diboson_2017",Diboson_2017},
  {"Diboson_2016",Diboson_2016},

  {"HToWW_2018",HToWW_2018},
  {"HToWW_2017",HToWW_2017},
  {"HToWW_2016",HToWW_2016},

  {"GluGluHToUncorrTauTau_2018",GluGluHToUncorrTauTau_2018},
  {"GluGluHToUncorrTauTau_2017",GluGluHToUncorrTauTau_2017},
  {"GluGluHToUncorrTauTau_2016",GluGluHToUncorrTauTau_2016},

  {"VBFHToUncorrTauTau_2018",VBFHToUncorrTauTau_2018},
  {"VBFHToUncorrTauTau_2017",VBFHToUncorrTauTau_2017},
  {"VBFHToUncorrTauTau_2016",VBFHToUncorrTauTau_2016},

  {"WHToUncorrTauTau_2018",WHToUncorrTauTau_2018},
  {"WHToUncorrTauTau_2017",WHToUncorrTauTau_2017},
  {"WHToUncorrTauTau_2016",WHToUncorrTauTau_2016},

  {"ZHToUncorrTauTau_2018",ZHToUncorrTauTau_2018},
  {"ZHToUncorrTauTau_2017",ZHToUncorrTauTau_2017},
  {"ZHToUncorrTauTau_2016",ZHToUncorrTauTau_2016},

};

// **************************************************************************************************
// **************************************************************************************************
// Cross-section map
// 2018 (taken from 2018, have to be checked!)
const map<TString, double> xsec_map_2018 = {
   { "DYJetsToLL_M-50"  , 6077.22 },
   { "DY1JetsToLL_M-50" , 877.8*1.137 },
   { "DY2JetsToLL_M-50" , 304.4*1.137 },
   { "DY3JetsToLL_M-50" , 111.5*1.137 },
   { "DY4JetsToLL_M-50" , 44.03*1.137 },
   { "WJetsToLNu"  , 61526.7 },
   { "W1JetsToLNu" , 8104.0*1.162 },
   { "W2JetsToLNu" , 2793.0*1.162 },
   { "W3JetsToLNu" , 992.5*1.162 },
   { "W4JetsToLNu" , 544.3*1.162 },
   { "TTTo2L2Nu"        , 88.29 },
   { "TTToHadronic"     , 377.96 },
   { "TTToSemiLeptonic" , 365.35 },
   { "ST_t-channel_antitop_4f" , 80.95 },
   { "ST_t-channel_top_4f"     , 136.02 },
   { "ST_tW_antitop_5f"        , 35.85 },
   { "ST_tW_top_5f"            , 35.85 },
   { "WW" , 75.88 },
   { "WZ" , 27.57 },
   { "ZZ" , 12.14 },
    { "VVTo2L2Nu"                , 11.95 },
    { "WWToLNuQQ"                , 49.997 },
    { "WZTo2L2Q"                 , 5.595 },
    { "WZTo1L1Nu2Q"              , 10.71 },
    { "WZTo1L3Nu"                , 3.05 },
    { "WZJToLLLNu"               , 4.708 },
    { "WZTo3LNu"                , 4.43 },
    { "ZZTo4L"                   , 1.212 },
    { "EWKWPlus2Jets"            , 25.62 },
  { "EWKWMinus2Jets_WToLNu_M-50" , 23.24 },
  { "EWKWPlus2Jets_WToLNu_M-50" , 29.59 },
  { "WGToLNuG"    , 464.4 },
  { "EWKZ2Jets_ZToLL_M-50" , 4.321 },
  { "EWKZ2Jets_ZToNuNu" , 10.66 },
    { "ZZTo2L2Q"                 , 3.22 },
   { "GluGluHToTauTau_M125" , 48.58*0.0627 },
   { "VBFHToTauTau_M125"    , 3.782*0.0627 },
   {"GluGluHToWWTo2L2Nu_M125",     1.09},
   {"VBFHToWWTo2L2Nu_M125",        0.0850},
   {"GluGluZH_HToWW_M125",         0.0262},
   {"HWminusJ_HToWW_M125",         0.114},
   {"HWplusJ_HToWW_M125",          0.18},
   {"HZJ_HToWW_M125",              0.163},
   { "GluGluHToTauTauUncorrDecays_M125" , 48.58*0.0627*0.2446 },
   { "VBFHToTauTauUncorrDecays_M125"    , 3.782*0.0627*0.2695 },
  { "VBFHToTauTauUncorrDecays_M125_1"    , 3.782*0.0627*0.2697 },
  { "VBFHToTauTauUncorrDecays_M125_2"    , 3.782*0.0627*0.2697 },
   { "WplusHToTauTauUncorrDecays_M125",   0.0527*0.2397},
   { "WminusHToTauTauUncorrDecays_M125",  0.0334*0.2563},
   { "ZHToTauTauUncorrDecays_M125",       0.0477*0.2513}
};
// 2017 (checked ! - reference is https://twiki.cern.ch/twiki/bin/view/CMS/HiggsToTauTauWorking2017 )

const map<TString, double> xsec_map_2017 = {
  { "DYJetsToLL_M-50"  , 6077.22 }, 
  { "DY1JetsToLL_M-50" , 877.8*1.137 }, 
  { "DY2JetsToLL_M-50" , 304.4*1.137 }, 
  { "DY3JetsToLL_M-50" , 111.5*1.137 }, 
  { "DY4JetsToLL_M-50" , 44.03*1.137 }, 
  { "WJetsToLNu"  , 61526.7 }, 
  { "W1JetsToLNu" , 8104.0*1.162 }, 
  { "W2JetsToLNu" , 2793.0*1.162 }, 
  { "W3JetsToLNu" , 992.5*1.162 },
  { "W4JetsToLNu" , 544.3*1.162 },
  { "TTTo2L2Nu"        , 88.29 }, 
  { "TTToHadronic"     , 377.96 },
  { "TTToSemiLeptonic" , 365.35 }, 
  { "ST_t-channel_antitop_4f" , 80.95 },
  { "ST_t-channel_top_4f"     , 136.02 },
  { "ST_tW_antitop_5f"        , 35.85 },
  { "ST_tW_top_5f"            , 35.85 },
  { "WW" , 75.88 },
  { "WZ" , 27.57 },
  { "ZZ" , 12.14 }, 
    { "VVTo2L2Nu"                , 11.95 },
    { "WWToLNuQQ"                , 49.997 },
    { "WZTo2L2Q"                 , 5.595 },
    { "WZTo1L1Nu2Q"              , 10.71 },
    { "WZTo1L3Nu"                , 3.05 },
    { "WZJToLLLNu"               , 4.708 },
    { "WZTo3LNu"                , 4.43 },
    { "ZZTo4L"                   , 1.212 },
    { "ZZTo2L2Q"                 , 3.22 },
  { "GluGluHToTauTau_M125" , 48.58*0.0627 },
  { "SUSYGluGluToHToTauTau" , 48.58*0.0627 },
  { "VBFHToTauTau_M125"    , 3.782*0.0627 },
  { "GluGluHToTauTauUncorrDecays_M125" , 48.58*0.0627*0.2447 },
  { "VBFHToTauTauUncorrDecays_M125"    , 3.782*0.0627*0.2697 },
  { "VBFHToTauTauUncorrDecays_M125_1"    , 3.782*0.0627*0.2697 },
  { "VBFHToTauTauUncorrDecays_M125_2"    , 3.782*0.0627*0.2697 },
   { "WplusHToTauTauUncorrDecays_M125",   0.0527*0.2394},
   { "WminusHToTauTauUncorrDecays_M125",  0.0334*0.2567},
   { "ZHToTauTauUncorrDecays_M125",       0.0477*0.2514},
  { "EWKWMinus2Jets_WToLNu_M-50" , 23.24 },
  { "EWKWPlus2Jets_WToLNu_M-50" , 29.59 },
  { "WGToLNuG"    , 464.4 },
  { "EWKZ2Jets_ZToLL_M-50" , 4.321 },
  { "EWKZ2Jets_ZToNuNu" , 10.66 },
  { "ZHToTauTau_M125"      , 0.0594 },
  { "WplusHToTauTau_M125"  , 0.0527 },
  { "WminusHToTauTau_M125" , 0.0358 },
  { "GluGluHToWWTo2L2Nu"                        , 48.6*0.02374 },  // from: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHXSWG#Higgs_cross_sections_and_decay_b and https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBR#H_llll_ll
  { "VBFHToWWTo2L2Nu_M125" , 3.78*0.02374 }, // from: see links above
  { "ttHToTauTau_M125"         , 0.5071*0.0627 },  // from: see links above
  {"GluGluHToWWTo2L2Nu_M125",     1.09},
  {"VBFHToWWTo2L2Nu_M125",        0.0850},
  {"GluGluZH_HToWW_M125",         0.0262},
  {"HWminusJ_HToWW_M125",         0.114},
  {"HWplusJ_HToWW_M125",          0.18},
  {"HZJ_HToWW_M125",              0.163},
};


// 2016 (taken from AN2016_355_v10 with minor unrelevant deviations - everything was checked)
const map<TString, double> xsec_map_2016 = {
    { "DYJetsToLL_M-10to50"      , 18610 },
    { "DYJetsToLL_M-50"          , 6077.22 },
    { "DY1JetsToLL_M-50"         , 1.225*1012.5 },
    { "DY2JetsToLL_M-50"         , 1.225*332.8 },
    { "DY3JetsToLL_M-50"         , 1.225*101.8 },
    { "DY4JetsToLL_M-50"         , 1.225*54.8 },
    { "WJetsToLNu"               , 61526.7 },
    { "W1JetsToLNu"              , 1.224*9644.5 },
    { "W2JetsToLNu"              , 1.224*3144.5 },
    { "W3JetsToLNu"              , 1.224*954.8 },
    { "W4JetsToLNu"              , 1.224*485.6 },
    { "TT"                    , 831.76 },
   { "TTTo2L2Nu"        , 88.29 },
   { "TTToHadronic"     , 377.96 },
   { "TTToSemiLeptonic" , 365.35 },
    { "ST_t-channel_antitop_4f"     , 80.95 },
    { "ST_t-channel_top_4f"         , 136.02 },
    { "ST_tW_antitop_5f"            , 35.6 },
    { "ST_tW_top_5f"                , 35.6 },
    { "VVTo2L2Nu"                , 11.95 },
    { "WWToLNuQQ"                , 49.997 },
    { "WZTo2L2Q"                 , 5.595 },
    { "WZTo1L1Nu2Q"              , 10.71 },
    { "WZTo1L3Nu"                , 3.05 },
    { "WZJToLLLNu"               , 4.708 },
    { "WZTo3LNu"                , 4.43 },
    { "ZZTo4L"                   , 1.212 },
    { "ZZTo2L2Q"                 , 3.22 },
    {"ZZ" , 12.14},
    {"WW" , 75.88},
    {"WZ" , 27.6},
    { "GluGluHToTauTauUncorrDecays_M125" , 48.58*0.0627*0.2455 },
    { "VBFHToTauTauUncorrDecays_M125"    , 3.782*0.0627*0.2727 },
   { "WplusHToTauTauUncorrDecays_M125",   0.0527*0.2425},
   { "WminusHToTauTauUncorrDecays_M125",  0.0334*0.2596},
   { "ZHToTauTauUncorrDecays_M125",       0.0477*0.2546},
    { "WGToLNuG"                 , 178.4 }, // xsdb
    { "WGstarToLNuMuMu"          , 2.793 },
    { "WGstarToLNuEE"            , 3.526 },
    { "EWKWPlus2Jets"            , 25.62 },
    { "EWKWMinus2Jet"            , 20.20 },
    { "EWKZ2Jets"                , 3.987 },
  { "EWKWMinus2Jets_WToLNu_M-50" , 23.24 },
  { "EWKWPlus2Jets_WToLNu_M-50" , 29.59 },
  { "WGToLNuG"    , 464.4 },
  { "EWKZ2Jets_ZToLL_M-50" , 4.321 },
  { "EWKZ2Jets_ZToNuNu" , 10.66 },
    { "ZZTo2L2Q"                 , 3.22 },
    { "GluGluHToTauTau_M125"     , 48.58*0.0627 },
    { "VBFHToTauTau_M125"        , 3.782*0.0627 },
    { "ZHToTauTau_M125"          , 0.0594 },
    { "WplusHToTauTau_M125"      , 0.0527 },
    { "WminusHToTauTau_M125"     , 0.0358 },
    { "GluGluHToWWTo2L2Nu_M125"  , 48.6*0.02374 }, // see 2017
    { "VBFHToWWTo2L2Nu_M125"     , 3.78*0.02374 }, // see 2017
    { "ttHJetToTT_M125"          , 0.5071*0.0627 }, // see 2017
    {"GluGluHToWWTo2L2Nu_M125",     1.09},
    {"VBFHToWWTo2L2Nu_M125",        0.0850},
    {"GluGluZH_HToWW_M125",         0.0262},
    {"HWminusJ_HToWW_M125",         0.114},
    {"HWplusJ_HToWW_M125",          0.18},
    {"HZJ_HToWW_M125",              0.163},
};
// **************************************************************************************************
// **************************************************************************************************
// maps short name to filenames - needed for stitching
const map<TString , TString> process_map_2018 = {
  { "WJets"   , "WJetsToLNu"},
  { "W1Jets"  , "W1JetsToLNu"},
  { "W2Jets"  , "W2JetsToLNu"},
  { "W3Jets"  , "W3JetsToLNu"},
  { "W4Jets"  , "W4JetsToLNu"},
  { "DYJets"  , "DYJetsToLL_M-50"},
  { "DY1Jets" , "DY1JetsToLL_M-50"},
  { "DY2Jets" , "DY2JetsToLL_M-50"},
  { "DY3Jets" , "DY3JetsToLL_M-50"},
  { "DY4Jets" , "DY4JetsToLL_M-50"},
  { "VBFHToTauTauUncorrDecays_M125" , "VBFHToTauTauUncorrDecays_M125"},
  // { "VBFHToTauTauUncorrDecays_M125_2" , "VBFHToTauTauUncorrDecays_M125_2"}
};


const map<TString , TString> process_map_2017 = {
  { "WJets"   , "WJetsToLNu"}, //all present in dir klundert
  { "W1Jets"  , "W1JetsToLNu"},
  { "W2Jets"  , "W2JetsToLNu"},
  { "W3Jets"  , "W3JetsToLNu"},
  { "W4Jets"  , "W4JetsToLNu"},
  { "DYJets"  , "DYJetsToLL_M-50"},
  { "DY1Jets" , "DY1JetsToLL_M-50"},
  { "DY2Jets" , "DY2JetsToLL_M-50"},
  { "DY3Jets" , "DY3JetsToLL_M-50"},
  { "DY4Jets" , "DY4JetsToLL_M-50"},
  { "VBFHToTauTauUncorrDecays_M125" , "VBFHToTauTauUncorrDecays_M125"},
  // { "VBFHToTauTauUncorrDecays_M125_2" , "VBFHToTauTauUncorrDecays_M125_2"}
};

const map<TString , TString> process_map_2016 = {
  { "WJets"   , "WJetsToLNu"},
  { "W1Jets"  , "W1JetsToLNu"},
  { "W2Jets"  , "W2JetsToLNu"},
  { "W3Jets"  , "W3JetsToLNu"},
  { "W4Jets"  , "W4JetsToLNu"},
  { "DYJets"  , "DYJetsToLL_M-50"},
  { "DY1Jets" , "DY1JetsToLL_M-50"},
  { "DY2Jets" , "DY2JetsToLL_M-50"},
  { "DY3Jets" , "DY3JetsToLL_M-50"},
  { "DY4Jets" , "DY4JetsToLL_M-50"},
};

const map<TString, int> n_events_per_sample_2017 = {
  {"WJetsToLNu"  , 74635450},
  {"W1JetsToLNu" , 54988117},
  {"W2JetsToLNu" , 32368249},
  {"W3JetsToLNu" , 19700377},
  {"W4JetsToLNu" , 11333705},
  {"W1JetsToLNu_LHEWpT_100-150" , 61651108},
  {"W1JetsToLNu_LHEWpT_150-250" , 126166905},
  {"W1JetsToLNu_LHEWpT_250-400" , 20841145},
  {"W1JetsToLNu_LHEWpT_400-inf" , 4465538},
  {"W2JetsToLNu_LHEWpT_100-150" , 36719823},
  {"W2JetsToLNu_LHEWpT_150-250" , 170437978},
  {"W2JetsToLNu_LHEWpT_250-400" , 81630276},
  {"W2JetsToLNu_LHEWpT_400-inf" , 30340311},
  {"ZJetsToNuNu_HT-100To200"    , 22737266},
  {"ZJetsToNuNu_HT-200To400"    , 21675916},
  {"ZJetsToNuNu_HT-400To600"    , 9134120},
  {"ZJetsToNuNu_HT-600To800"    , 5697594},
  {"ZJetsToNuNu_HT-800To1200"   , 2058077},
  {"ZJetsToNuNu_HT-1200To2500"  , 338948},
  {"ZJetsToNuNu_HT-2500ToInf"   , 6734},
  {"ZZ" , 1949768},
  {"WW" , 7791498},
  {"WZ" , 3928630},
  {"DYJetsToLL_M-10to50" , 39521230},
  {"DYJetsToLL_M-50"     , 97800939},
  {"DY1JetsToLL_M-50"    , 34859434},
  {"DY2JetsToLL_M-50"    , 9790490},
  {"DY3JetsToLL_M-50"    , 6897933},
  {"DY4JetsToLL_M-50"    , 4346952},
//  {"TTTo2L2Nu"        , 960752},
//  {"TTToHadronic"     , 41729120},
//  {"TTToSemiLeptonic" , 41221873},
//  {"ST_t-channel_top_4f"     , 3675910},
//  {"ST_t-channel_antitop_4f" , 5982064},
//  {"ST_tW_top_5f"            , 7977430},
//  {"ST_tW_antitop_5f"        , 7794186},
  {"WToTauNu_M-200"         , 2000000},
  {"WToTauNu_M-200_jesUp"   , 2000000},
  {"WToTauNu_M-200_jesDown" , 2000000},
  {"WToTauNu_M-200_taues_1prong0pizerosUp"       , 2000000},
  {"WToTauNu_M-200_taues_1prong0pizerosDown"     , 2000000},
  {"WToTauNu_M-200_taues_1prongUpTo4pizerosUp"   , 2000000},
  {"WToTauNu_M-200_taues_1prongUpTo4pizerosDown" , 2000000},
  {"WToTauNu_M-200_taues_3prong0pizerosUp"       , 2000000},
  {"WToTauNu_M-200_taues_3prong0pizerosDown"     , 2000000},
  {"WToTauNu_M-200_uesUp"   , 2000000},
  {"WToTauNu_M-200_uesDown" , 2000000},
  {"WToMuNu_M-200"          , 1953601},
  {"WToMuNu_M-200_jesUp"    , 1953601},
  {"WToMuNu_M-200_jesDown"  , 1953601},
  {"WToMuNu_M-200_muUp"     , 1953601},
  {"WToMuNu_M-200_muDown"   , 1953601},
  {"WToMuNu_M-200_uesUp"    , 1953601},
  {"WToMuNu_M-200_uesDown"  , 1953601},
//  {"GluGluHToTauTau_M125", 12180180},
//  {"VBFHToTauTau_M125", 2977152},
};
const map<TString, int> n_events_per_sample_2016 = {
{"WJetsToLNu"  , 86916455},
{"W1JetsToLNu" , 45283121},
{"W2JetsToLNu" , 30374504},
{"W3JetsToLNu" , 39501912},
{"W4JetsToLNu" , 20824737},
{"WJetsToLNu_HT-70To100"    , 10020533},
{"WJetsToLNu_HT-100To200"   , 78043017},
{"WJetsToLNu_HT-200To400"   , 38984322},
{"WJetsToLNu_HT-400To600"   , 7759701},
{"WJetsToLNu_HT-600To800"   , 18687480},
{"WJetsToLNu_HT-800To1200"  , 7830536},
{"WJetsToLNu_HT-1200To2500" , 6872441},
{"WJetsToLNu_HT-2500ToInf"  , 2637821},
{"ZJetsToNuNu_HT-100To200"   , 24272858},
{"ZJetsToNuNu_HT-200To400"   , 24761211},
{"ZJetsToNuNu_HT-400To600"   , 9862869},
{"ZJetsToNuNu_HT-600To800"   , 5766322},
{"ZJetsToNuNu_HT-800To1200"  , 2170137},
{"ZJetsToNuNu_HT-1200To2500" , 513471},
{"ZJetsToNuNu_HT-2500ToInf"  , 405030},
{"ZZ" , 1988098},
{"WW" , 7982180},
{"WZ" , 3997571},
{"DYJetsToLL_M-10to50" , 35114961},
{"DYJetsToLL_M-50"     , 146280395},
{"DY1JetsToLL_M-50"    , 63730337},
{"DY2JetsToLL_M-50"    , 19879279},
{"DY3JetsToLL_M-50"    , 5857441},
{"DY4JetsToLL_M-50"    , 4197868},
{"TT" , 76915549},
{"ST_t-channel_top_4f"     , 67105876},
{"ST_t-channel_antitop_4f" , 38811017},
{"ST_tW_top_5f"            , 6952830},
{"ST_tW_antitop_5f"        , 6933094},
{"WToTauNu_M-200"         , 999130},
{"WToTauNu_M-200_jesUp"   , 999130},
{"WToTauNu_M-200_jesDown" , 999130},
{"WToTauNu_M-200_uesUp"   , 999130},
{"WToTauNu_M-200_uesDown" , 999130},
{"WToTauNu_M-200_taues_1prong0pizerosUp"       , 999130},
{"WToTauNu_M-200_taues_1prong0pizerosDown"     , 999130},
{"WToTauNu_M-200_taues_1prongUpTo4pizerosUp"   , 999130},
{"WToTauNu_M-200_taues_1prongUpTo4pizerosDown" , 999130},
{"WToTauNu_M-200_taues_3prong0pizerosUp"       , 999130},
{"WToTauNu_M-200_taues_3prong0pizerosDown"     , 999130},
{"WToMuNu_M-200"          , 996128},
{"WToMuNu_M-200_jesUp"    , 996128},
{"WToMuNu_M-200_jesDown"  , 996128},
{"WToMuNu_M-200_muUp"     , 996128},
{"WToMuNu_M-200_muDown"   , 996128},
{"WToMuNu_M-200_uesUp"    , 996128},
{"WToMuNu_M-200_uesDown"  , 996128},
{"GluGluHToTauTau_M125", 11171000},
//{"VBFHToTauTau_M125", 1499400},
};

template<typename KeyTemp, typename ValTemp>
std::vector<KeyTemp> extract_keys(std::map<KeyTemp, ValTemp> const& input_map) {
  std::vector<KeyTemp> keys;
  for (auto const& element : input_map) {
    keys.push_back(element.first);
  }
  return keys;
}

double getNEventsProcessed(TString input_dir, TString sample, TString Year="2017")
{
  double nevents;
  /*
  vector<TString> keys_list;
  if(Year=="2017") keys_list = extract_keys(n_events_per_sample_2017);
  else keys_list = extract_keys(n_events_per_sample_2016);
  if((std::find(keys_list.begin(), keys_list.end(), sample) != keys_list.end())&&Year!="2018"){
    if(Year=="2017") nevents = n_events_per_sample_2017.at(sample);
    else nevents = n_events_per_sample_2016.at(sample);
  }else
  */
  if(!sample.Contains("Run")){
    TFile * file = new TFile(input_dir+"/"+sample+".root");
    TH1D * histWeightsH = (TH1D*)file->Get("nWeightedEvents");
    if(!histWeightsH){
      cout << endl << endl << "Histogram nWeightedEvents doesn't exist in the file "<< input_dir+"/"+sample+".root" <<". Quit program." << endl << endl;
      exit(-1);
    }
    nevents = histWeightsH->GetSumOfWeights();
    //if(Year!="2018")cout << "WARNING: normalization taken from nWeightedEvents, please check! ";
    file -> Close();
    delete file;
  }else nevents=0;

  return nevents;
}



#endif
