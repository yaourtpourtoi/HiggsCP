ERA=$1
CHANNEL=$2
FAKES_METHOD=$3
ZTT_METHOD=$4

PATH_TO_TUPLES="/nfs/dust/cms/user/filatovo/HTT/CMSSW_10_2_16/src/mlFramework/In_Tuples_${ERA}/${CHANNEL}/17June/"
PATH_FOR_OUTPUT="./figures_17June/${ERA}/${FAKES_METHOD}_${ZTT_METHOD}/"

WEIGHT="weight*" # trigweight_1/trigweight*
CUTS="(iso_1<0.15&&pt_1>25&&pt_2>30&&abs(eta_1)<2.1&&abs(eta_2)<2.3)*(is_SingleLepTrigger)*" #&&byMediumDeepTau2017v2p1VSjet_2>0.5
CUTSIPMU="${CUTS}"
CUTSIPTAU="${CUTS}(dmMVA_2==0)*"
CUTS_ACOTAUTAU_00="${CUTS}(dmMVA_2==0)*"
CUTS_ACOTAUTAU_01="${CUTS}((dmMVA_2==1)||(dmMVA_2==2)||(dmMVA_2==10))*"

SHOW_SIGNAL="true"
COMPARE_CP="true"

if [[ $CHANNEL == "et" ]]; then
  CHANNEL_LABEL="e"
else 
  if [[ $CHANNEL == "mt" ]]; then
    CHANNEL_LABEL="#mu"
  else 
    echo
    echo "To produce some plots this script is to be run with the command:"
    echo
    echo "  ./plotDNNvariables.sh <era={2016,2017,2018}> <channel={et,mt}> <fakes_method={FF,QCD}> <ZTT_METHOD={emb, DY}>"
    echo
    echo "channel is not et or mt - exiting"
    exit  
  fi
fi
if [[ $FAKES_METHOD == "FF" ]]; then
  APPLY_FF="true"
else 
  if [[ $FAKES_METHOD == "QCD" ]]; then
    APPLY_FF="false"
  else 
    echo
    echo "To produce some plots this script is to be run with the command:"
    echo
    echo "  ./plotDNNvariables.sh <era={2016,2017,2018}> <channel={et,mt}> <fakes_method={FF,QCD}> <ZTT_METHOD={emb, DY}>"
    echo
    echo "fakes_method is not FF or QCD - exiting"
    exit
  fi
fi

if [[ $ZTT_METHOD == "emb" ]]; then
  USE_EMBEDDED="true"
else 
  if [[ $ZTT_METHOD == "DY" ]]; then
    USE_EMBEDDED="false"
  else 
    echo
    echo "To produce some plots this script is to be run with the command:"
    echo
    echo "  ./plotDNNvariables.sh <era={2016,2017,2018}> <channel={et,mt}> <fakes_method={FF,QCD}> <ZTT_METHOD={emb, DY}>"
    echo
    echo "ztt_method is not emb or DY - exiting"
    exit
  fi
fi

# some older attempts:
# eval "root -l -b -q 'Plot_lept_mutau_NNNTuples.C(${"pt_1","p_{T,#mu}[GeV]"},30,20.,80.,"%s",%s,"Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)'" 
# eval "root -l -b -q 'Plot_lept_mutau_NNNTuples.C(${"pt_1","p_{T,#mu}[GeV]"},30,20.,80.,"%s","(puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)'" 

### beware of spaces inside of parameter brackets! they might crush things 

# general
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("m_vis","m_{vis}[GeV]",30,0.,300.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_1","p_{T,%s}[GeV]",30,20.,80.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $CHANNEL_LABEL $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("eta_1","#eta_{%s}",30,-3.,3.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $CHANNEL_LABEL $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("phi_1","#phi_{%s}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $CHANNEL_LABEL $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_2","p_{T,#tau}[GeV]",30,25.,85.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("eta_2","#eta_{#tau}",30,-3.,3.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("phi_2","#phi_{#tau}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP`
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("tau_decay_mode_2","HPS-DM",13,0.,13.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("dmMVA_2","MVA-DM",13,0.,13.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

# # IP
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("IP_signif_RefitV_with_BS_1","#muIPsig",20,0.,10.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTSIPMU $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("IP_signif_RefitV_with_BS_2","#tauIPsig",20,0.,10.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTSIPTAU $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("IP_signif_PV_with_BS_1","IPsignif(%s)",20,0.,10.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $CHANNEL_LABEL $WEIGHT $CUTSIPMU $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("IP_signif_PV_with_BS_2","IPsignif(#tau)",20,0.,10.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTSIPTAU $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("IP_signif_RefitV_with_BS_uncorr_1","#muIPsigUncorr",20,0.,10.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTSIPMU $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("IP_signif_RefitV_with_BS_uncorr_2","#tauIPsigUncorr",20,0.,10.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTSIPTAU $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

# CP observables
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("acotautau_bs_00","#phi_{CP}",11,0.,2*TMath::Pi(),"%s","%s","Events",-1,"%s","%s",%s,%s,%s,true,false,%s,%s)' $WEIGHT $CUTS_ACOTAUTAU_00 $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("acotautau_bs_01","#phi_{CP}",11,0.,2*TMath::Pi(),"%s","%s","Events",-1,"%s","%s",%s,%s,%s,true,false,%s,%s)' $WEIGHT $CUTS_ACOTAUTAU_01 $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

 # jets
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("njets","njets",6,0,6,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jdeta","#Delta#eta_{jj}[GeV]",12,0,6,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("mjj","m_{jj}[GeV]",50,0,400.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("dijetpt","p_{T,jj}[GeV]",30,0.,300.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jpt_1","p_{T,lead.j}[GeV]",30,26.,146.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jeta_1","#eta_{lead.j}",45,-4.5,4.5,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jpt_2","p_{T,trail.j}[GeV]",30,26.,146.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP`  
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jeta_2","#eta_{trail.j}",45,-4.5,4.5,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

# b-jets #
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("nbtag","nbtags",2,0,2,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bpt_1","p_{T,lead.bj}[GeV]",30,16.,136.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bpt_2","p_{T,trail.bj}[GeV]",30,16.,136.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("beta_1","#eta_{lead.bj}",30,-3.,3.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bphi_1","#phi_{lead.bj}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("beta_2","#eta_{trail.bj}",30,-3.,3.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bphi_2","#phi_{trail.bj}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bcsv_1","DeepFlavour_probb_1",40,0.,1.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bcsv_2","DeepFlavour_probb_2",40,0.,1.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

# ditau 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("m_fast","m_{#tau#tau}[GeV]",35,0,350.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_fast","p_{T,#tau#tau}[GeV]",30,0.,300.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_tt","p_{T,#tau#tau}[GeV]",30,0.,300.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

# puppi
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("puppimet","PUPPI-MET[GeV]",30,0.,150.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("puppimt_1","PUPPI-m_{T}[GeV]",30,0.,150.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("puppimt_2","PUPPI-mT_2[GeV]",30,0.,150.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

# DeepTau 
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("deepTauVsEleRaw_2","deepTauVsEleRaw_2",20,0.,1.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
# root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("deepTauVsJetRaw_2","deepTauVsJetRaw_2",20,0.,1.,"%s","%s","Events",-1,"%s","%s",%s,%s,%s,false,false,%s,%s)' $WEIGHT $CUTS $PATH_TO_TUPLES $PATH_FOR_OUTPUT $ERA $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
