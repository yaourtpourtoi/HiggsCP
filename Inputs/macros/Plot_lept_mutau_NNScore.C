#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include "HiggsCP/Inputs/macros/Plot_lept_mutau_NNNTuples.C"


void   Plot_lept_mutau_NNScore(TString directory = "/nfs/dust/cms/user/filatovo/HTT/CMSSW_10_2_16/src/mlFramework/In_Tuples_2016/et/17June/",
			       TString prediction_directory = "/nfs/dust/cms/user/filatovo/HTT/CMSSW_10_2_16/src/mlFramework/Out_Tuples_2016/et/17June/predictions_2016/",
			       TString outputDir = "/nfs/dust/cms/user/filatovo/HTT/CMSSW_10_2_16/src/HiggsCP/Inputs/macros/figures_17June/et/2016/friends/",
			       int year=2016,
						 TString channel = "et",
			       bool FFmethod = true,  
			       bool useEmbedded = true,
			       bool LargeScale = true,  
			       bool logY = false,
			       bool showSignal = true,
			       bool compareCP = true,
			       int scaleSignal = 10.,
			       bool blindData = false,
			       bool FORCE = false
			       )
{
  
	TString cuts = "(iso_1<0.15&&pt_1>25&&pt_2>30&&abs(eta_1)<2.1&&abs(eta_2)<2.3)*(is_SingleLepTrigger)*"; // m_vis>40
	TString weights = "weight*"; //trigweight_1/trigweight*

  const int nCategories = 3;
  const int nSigCategories = 1;
  
	const map<TString, TString > map_DM_label = {
	  {"0", "_mupi"},
	  {"1", "_murho"},
	  {"2", "_mu0a1"},
		{"10", "_mua1"}
	};
	  
	const map<TString, TString > map_DM_observable = {
	  {"0", "acotautau_bs_00"},
	  {"1", "acotautau_bs_01"},
	  {"2", "acotautau_bs_01"},
		{"10", "acotautau_bs_01"}
	};
	
	const map<TString, TString > map_DM_cut = {
	  {"0", "(IP_signif_PV_with_BS_1>1.5&&IP_signif_PV_with_BS_2>1.5)*(dmMVA_2==0)*"},
	  {"1", "(IP_signif_PV_with_BS_1>1.5)*(dmMVA_2==1)*"},
	  {"2", "(IP_signif_PV_with_BS_1>1.5)*(dmMVA_2==2)*"},
		{"10", "(IP_signif_PV_with_BS_1>1.5)*(dmMVA_2==10)*"}
	};
	  
	TString DM_observable = "";
	TString DM_cut = "";
	TString DM_label = "";
	
  for(int categoryIndex=0;categoryIndex<nSigCategories;categoryIndex++){
		for (auto DM_label : map_DM_label) {
			DM_label = DM_label.second;
			DM_observable = map_DM_observable.at(DM_label.first);
			DM_cut = map_DM_cut.at(DM_label.first);
	    Plot_lept_mutau_NNNTuples("predicted_prob:" + DM_observable,
				      "#phi_{CP} vs DNN score",
				      8,0.,2*TMath::Pi(),
				      weights,
				      cuts + DM_cut, //&&IP_signif_RefitV_with_BS_1>1.5&&IP_signif_RefitV_with_BS_2>1.5
				      "Events",
				      categoryIndex,
				      directory,
				      prediction_directory,
				      outputDir,
				      year,
							channel,
				      FFmethod,
				      useEmbedded,
				      true,  
				      true,
				      showSignal,
				      compareCP,
				      scaleSignal,
				      blindData,
				      DM_label,
				      FORCE
				      );
  }
}

  // for(int categoryIndex=0;categoryIndex<nSigCategories;categoryIndex++){
  //   Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_bs_01",
	// 		      "#phi_{CP} vs DNN score",
	// 		      8,0.,2*TMath::Pi(),
	// 		      "weight*",
	// 		      cuts + "(IP_signif_PV_with_BS_1>1.5)*(dmMVA_2==1)*",
	// 		      "Events",
	// 		      categoryIndex,
	// 		      directory,
	// 					prediction_directory,
	// 		      outputDir,
	// 		      year,
	// 					channel,
	// 		      FFmethod,
	// 		      useEmbedded,  
	// 		      true,  
	// 		      true,
	// 		      showSignal,
	// 		      compareCP,
	// 		      scaleSignal,
	// 		      blindData,
	// 					"_murho",
	// 		      FORCE
	// 		      );
  // }
	// 
	// for(int categoryIndex=0;categoryIndex<nSigCategories;categoryIndex++){
  //   Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_bs_01",
	// 		      "#phi_{CP} vs DNN score",
	// 		      8,0.,2*TMath::Pi(),
	// 		      "weight*",
	// 		      cuts + "(IP_signif_PV_with_BS_1>1.5)*(dmMVA_2==2)*",
	// 		      "Events",
	// 		      categoryIndex,
	// 		      directory,
	// 					prediction_directory,
	// 		      outputDir,
	// 		      year,
	// 					channel,
	// 		      FFmethod,
	// 		      useEmbedded,  
	// 		      true,  
	// 		      true,
	// 		      showSignal,
	// 		      compareCP,
	// 		      scaleSignal,
	// 		      blindData,
	// 					"_mu0a1",
	// 		      FORCE
	// 		      );
  // }
	// 
	// for(int categoryIndex=0;categoryIndex<nSigCategories;categoryIndex++){
	// 	Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_bs_01",
	// 					"#phi_{CP} vs DNN score",
	// 					8,0.,2*TMath::Pi(),
	// 					"weight*",
	// 					cuts + "(IP_signif_PV_with_BS_1>1.5)*(dmMVA_2==10)*",
	// 					"Events",
	// 					categoryIndex,
	// 					directory,
	// 					prediction_directory,
	// 					outputDir,
	// 					year,
	// 					channel,
	// 					FFmethod,
	// 					useEmbedded,  
	// 					true,  
	// 					true,
	// 					showSignal,
	// 					compareCP,
	// 					scaleSignal,
	// 					blindData,
	// 					"_mua1",
	// 					FORCE
	// 					);
	// }
	  
  bool _logY = false;
  bool _largeScale = false;
  for(int categoryIndex=0;categoryIndex<nCategories;categoryIndex++){
    if(categoryIndex<nSigCategories){
      blindData=true;
      _logY=true;
      _largeScale=true;
    }
    else {
      _logY=logY;
      _largeScale=LargeScale;
    }
    // if (categoryIndex==0) cuts+= "(IP_signif_RefitV_with_BS_1>1.5)*";
    Plot_lept_mutau_NNNTuples("predicted_prob",
			      "NN Score",
			      50,0.,1.,
			      weights,
			      cuts,
			      "Events",
			      categoryIndex,
			      directory,
			      prediction_directory,
			      outputDir,
			      year,
						channel,
			      FFmethod,
			      useEmbedded,  
			      _largeScale,  
			      _logY,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "",
			      FORCE
			      );
    
}
 
