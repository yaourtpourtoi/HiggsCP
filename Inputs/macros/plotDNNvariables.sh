PATH_TO_TUPLES="/nfs/dust/cms/user/cardinia/HtoTauTau/HiggsCP/DNN/Jan20/CMSSW_10_2_16/src/HiggsCP/Inputs/NTuples_mt_2017_v2/"
#PATH_TO_TUPLES="/nfs/dust/cms/user/filatovo/HTT/CMSSW_10_2_16/src/HiggsCP/Inputs/v2_VBF_norm_commented/NTuples_mt_2017/"
PATH_FOR_OUTPUT="./figures/"

WEIGHT="weight*"
APPLY_FF="true"
USE_EMBEDDED="true"
SHOW_SIGNAL="true"
COMPARE_CP="true"

# eval "root -l -b -q 'Plot_lept_mutau_NNNTuples.C(${"pt_1","p_{T,#mu}[GeV]"},30,20.,80.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)'" 
# eval "root -l -b -q 'Plot_lept_mutau_NNNTuples.C(${"pt_1","p_{T,#mu}[GeV]"},30,20.,80.,"%s","(puppimt_1<50&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)'" 

### beware of spaces inside of parameter brackets! they might crush things 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("m_vis","m_{vis}[GeV]",30,0.,300.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_1","p_{T,#mu}[GeV]",30,20.,80.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("eta_1","#eta_{#mu}",30,-3.,3.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("phi_1","#phi_{#mu}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_2","p_{T,#tau}[GeV]",30,25.,85.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("eta_2","#eta_{#tau}",30,-3.,3.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("phi_2","#phi_{#tau}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("njets","njets",6,0,6,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jdeta","#Delta#eta_{jj}[GeV]",12,0,6,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("mjj","m_{jj}[GeV]",50,0,250.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("dijetpt","p_{T,jj}[GeV]",50,0.,250.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jpt_1","p_{T,lead.j}[GeV]",30,26.,146.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jeta_1","#eta_{lead.j}",45,-4.5,4.5,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jpt_2","p_{T,trail.j}[GeV]",30,26.,146.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP`  
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("jeta_2","#eta_{trail.j}",45,-4.5,4.5,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_tt","p_{T,#tau#tau}[GeV]",30,0.,150.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("m_sv*(m_sv>0)+(m_sv<=0)","m_{#tau#tau}[GeV]",50,0.,250.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("m_sv","m_{#tau#tau}[GeV]",50,0.,250.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("mt_1","m_{T}[GeV]",30,0.,150.,"%s","(pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("acotautau_01","#phi_{CP}",11,0.,2*TMath::Pi(),"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,true,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

### b-jets ###
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("nbtag","nbtags",2,0,2,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bpt_1","p_{T,lead.bj}[GeV]",30,16.,136.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bpt_2","p_{T,trail.bj}[GeV]",30,16.,136.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("beta_1","#eta_{lead.bj}",30,-3.,3.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bphi_1","#phi_{lead.bj}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("beta_2","#eta_{trail.bj}",30,-3.,3.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bphi_2","#phi_{trail.bj}[rad]",30,-TMath::Pi(),TMath::Pi(),"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bcsv_1","DeepFlavour_probb_1",40,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("bcsv_2","DeepFlavour_probb_2",40,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

### NEW ###
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("ipx_1","IP_helix_x_1",30,-0.025,0.035,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("ipy_1","IP_helix_y_1",30,-0.025,0.035,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("ipz_1","IP_helix_z_1",30,-0.025,0.035,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("mt_fast*(mt_fast>0)-10*(mt_fast<=0)","mt_fast[GeV]",35,-10.,340.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("m_fast","m_{#tau#tau}[GeV]",35,0,350.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("pt_fast","p_{T,#tau#tau}[GeV]",30,0.,300.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("deepTauVsEleRaw_2","deepTauVsEleRaw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("deepTauVsJetRaw_2","deepTauVsJetRaw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("deepTauVsMuRaw_2","deepTauVsMuRaw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("MVADM2017v1DM10raw_2","MVADM2017v1DM10raw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("MVADM2017v1DM11raw_2","MVADM2017v1DM11raw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("MVADM2017v1DM0raw_2","MVADM2017v1DM1raw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("MVADM2017v1DM2raw_2","MVADM2017v1DM2raw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
#root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("MVADM2017v1DM1raw_2","MVADM2017v1DM0raw_2",20,0.,1.,"%s","(puppimt_1<50&&pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 

root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("puppimt_1","PUPPI-m_{T}[GeV]",30,0.,150.,"%s","(pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("puppimt_2","PUPPI-mT_2[GeV]",30,0.,150.,"%s","(pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 
root -l -b -q `printf 'Plot_lept_mutau_NNNTuples.C("puppimet","PUPPI-MET[GeV]",30,0.,150.,"%s","(pt_1>21&&byVVVLooseDeepTau2017v2p1VSjet_2>0.5)*","Events",-1,"%s","%s",2017,%s,%s,false,false,%s,%s)' $WEIGHT $PATH_TO_TUPLES $PATH_FOR_OUTPUT $APPLY_FF $USE_EMBEDDED $SHOW_SIGNAL $COMPARE_CP` 