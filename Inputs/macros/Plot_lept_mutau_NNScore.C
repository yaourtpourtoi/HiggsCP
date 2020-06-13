#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include "HiggsCP/Inputs/macros/Plot_lept_mutau_NNNTuples.C"


void   Plot_lept_mutau_NNScore(TString directory = "/nfs/dust/cms/user/rasp/storage/cardinia/2016/OutputDNN/March28/predictions_2016/",
			       TString outputDir = "./figures_April27/2016/",
			       int year=2016,
			       bool FFmethod = true,  
			       bool useEmbedded = true,
			       bool LargeScale = true,  
			       bool logY = false,
			       bool showSignal = true,
			       bool compareCP = true,
			       int scaleSignal = 1.,
			       bool blindData = true,
			       bool FORCE = false
			       )
{
  
  const int nCategories = 3;
  const int nSigCategories = 1;
  /*
  for(int categoryIndex=0;categoryIndex<nCategories;categoryIndex++){
    Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_refitbs_00",
			      "#phi_{CP} vs DNN score",
			      12,0.,2*TMath::Pi(),
			      "weight*",
			      "(pt_1>21&&puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5&&abs(eta_1)<2.1&&m_vis>40&&IP_signif_RefitV_with_BS_1>1.5&&IP_signif_RefitV_with_BS_2>1.5)*(dmMVA_2==0)*",//&&IP_signif_RefitV_with_BS_1>1.5&&IP_signif_RefitV_with_BS_2>1.5
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      FFmethod,
			      useEmbedded,
			      true,  
			      true,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "_mupi",
			      FORCE
			      );
  }

  for(int categoryIndex=0;categoryIndex<nCategories;categoryIndex++){
    Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_refitbs_01",
			      "#phi_{CP} vs DNN score",
			      16,0.,2*TMath::Pi(),
			      "weight*",
			      "(pt_1>21&&puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5&&abs(eta_1)<2.1&&m_vis>40&&IP_signif_RefitV_with_BS_1>1.5)*(dmMVA_2==1)*",
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      FFmethod,
			      useEmbedded,  
			      true,  
			      true,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      FORCE
			      );
  }
	
  for(int categoryIndex=0;categoryIndex<nCategories;categoryIndex++){
    Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_refitbs_01",
			      "#phi_{CP} vs NN score",
			      8,0.,2*TMath::Pi(),
			      "weight*",
			      "(pt_1>21&&pt_2>20&&m_vis>40&&TMath::Abs(eta_1)<2.1&&puppimt_1<50)*(IP_signif_RefitV_with_BS_1>1.5)*(dmMVA_2==10)*",
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      FFmethod,
			      useEmbedded,  
			      true,  
			      true,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "_murho",
			      FORCE
			      );
  }
  for(int categoryIndex=0;categoryIndex<nCategories;categoryIndex++){
    Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_refitbs_01",
			      "#phi_{CP} vs DNN score",
			      9,0.,2*TMath::Pi(),
			      "weight*",
			      "(pt_1>21&&puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5&&abs(eta_1)<2.1&&m_vis>40&&IP_signif_RefitV_with_BS_1>1.5)*(dmMVA_2==10)*",
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      FFmethod,
			      useEmbedded,  
			      true,  
			      true,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "_mua1",
			      FORCE
			      );
  }

  for(int categoryIndex=0;categoryIndex<nCategories;categoryIndex++){
    Plot_lept_mutau_NNNTuples("predicted_prob:acotautau_refitbs_01",
			      "#phi_{CP} vs DNN score",
			      4,0.,2*TMath::Pi(),
			      "weight*",
			      "(pt_1>21&&puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5&&abs(eta_1)<2.1&&m_vis>40&&IP_signif_RefitV_with_BS_1>1.5)*(dmMVA_2==2)*",
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      FFmethod,
			      useEmbedded,  
			      true,  
			      true,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "_mu0a1",
			      FORCE
			      );
  }
  */
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
    TString cuts = "(pt_1>21&&puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5&&abs(eta_1)<2.1&&m_vis>40)*";
    // if (categoryIndex==0) cuts+= "(IP_signif_RefitV_with_BS_1>1.5)*";
    Plot_lept_mutau_NNNTuples("predicted_prob",
			      "NN Score",
			      50,0.,1.,
			      "weight*",
			      cuts,
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      //false,
			      FFmethod,
			      //false,  
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
    /*
  Plot_lept_mutau_NNNTuples("predicted_prob",
			      "DNN Score",
			      50,0.,1.,
			      "weight*",
			      cuts,
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      false,
			      //FFmethod,
			      false,  
			      //useEmbedded,  
			      _largeScale,  
			      _logY,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "",
			      FORCE
			      );
  
  Plot_lept_mutau_NNNTuples("predicted_prob",
			      "DNN Score",
			      50,0.,1.,
			      "weight*",
			      cuts,
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			    //false,
			      FFmethod,
			      false,  
			      //useEmbedded,  
			      _largeScale,  
			      _logY,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "",
			      FORCE
			      );
  
  Plot_lept_mutau_NNNTuples("predicted_prob",
			      "DNN Score",
			      50,0.,1.,
			      "weight*",
			      cuts,
			      "Events",
			      categoryIndex,
			      directory,
			      outputDir,
			      year,
			      false,
			    //FFmethod,
			    //false,  
			      useEmbedded,  
			      _largeScale,  
			      _logY,
			      showSignal,
			      compareCP,
			      scaleSignal,
			      blindData,
			      "",
			      FORCE
			      );*/
  }
}
 
