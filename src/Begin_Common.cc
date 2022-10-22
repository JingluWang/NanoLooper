#include "Begin_Common.h"

void Begin_Common()
{
    //==============================================
    // Begin_Common:
    // This function gets called prior to the event looping.
    // This is where one declares variables, histograms, event selections for the category Common.
    //==============================================

    // Create variables used in this category.
    // Please follow the convention of <category>_<varname> structure.
    Begin_Common_Create_Branches();

    // Determine whether it is EFT or not
    Begin_Common_Determine_Is_EFT();

    // Determine whether it is postprocessed NanoAOD or not
    Begin_Common_Determine_Is_Postprocessed(); 
    

    // The framework may run over NanoAOD directly or, it may run over VVVTree.
    // ana.run_VVVTree boolean determines this.
    if (ana.run_VVVTree)
    {
        Begin_Common_VVVTree();
    }
    else
    {
        //setup GRL
        Begin_Common_Set_Run_List();

        // Configure the gconf from NanoTools/NanoCORE/Config.h
        Begin_Common_Set_Config();
        Begin_Common_NanoAOD();
    }

}

void Begin_Common_Create_Branches()
{
    // Event level information
    ana.tx.createBranch<int>                  ("Common_isData");
    ana.tx.createBranch<int>                  ("Common_run");
    ana.tx.createBranch<int>                  ("Common_lumi");
    ana.tx.createBranch<unsigned long long>   ("Common_evt");
    ana.tx.createBranch<float>                ("Common_genWeight");
    ana.tx.createBranch<float>                ("Common_btagWeight_DeepCSVB");
    ana.tx.createBranch<float>                ("Common_wgt");
    ana.tx.createBranch<float>                ("Common_event_puWeight");        //Pile up weight
    ana.tx.createBranch<float>                ("Common_event_puWeightup");      //Pile up weight
    ana.tx.createBranch<float>                ("Common_event_puWeightdn");      //Pile up weight
    ana.tx.createBranch<float>                ("Common_event_prefireWeight");   //Prefiring weight
    ana.tx.createBranch<float>                ("Common_event_prefireWeightup"); //Prefiring weight
    ana.tx.createBranch<float>                ("Common_event_prefireWeightdn"); //Prefiring weight
    ana.tx.createBranch<float>                ("Common_event_triggerWeight");   //trigger weight
    ana.tx.createBranch<float>                ("Common_event_triggerWeightup");   //trigger weight
    ana.tx.createBranch<float>                ("Common_event_triggerWeightdn");   //trigger weight

    // EFT weightings
    ana.tx.createBranch<vector<float>>        ("Common_LHEWeight_mg_reweighting");

    // 2016 only triggers
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"); // Lowest unprescaled
    // The rest of the triggers
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"); // Lowest unprescaled for >= 2017C
    ana.tx.createBranch<bool>                 ("Common_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
    ana.tx.createBranch<bool>                 ("Common_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
    //hadronic triggers
    ana.tx.createBranch<bool>("Common_HLT_PFHT1050"); 
    ana.tx.createBranch<bool>("Common_HLT_AK8PFJet500");
    ana.tx.createBranch<bool>("Common_HLT_AK8PFJet380_TrimMass30");
    ana.tx.createBranch<bool>("Common_HLT_AK8PFJet360_TrimMass30");
    ana.tx.createBranch<bool>("Common_HLT_AK8PFJet400_TrimMass30");
    ana.tx.createBranch<bool>("Common_HLT_AK8PFJet420_TrimMass30" );
    ana.tx.createBranch<bool>("Common_HLT_AK8PFHT750_TrimMass50" );
    ana.tx.createBranch<bool>("Common_HLT_AK8PFHT800_TrimMass50");
    ana.tx.createBranch<bool>("Common_HLT_AK8PFHT850_TrimMass50" );
    ana.tx.createBranch<bool>("Common_HLT_AK8PFHT900_TrimMass50" );
    // Summary triggers
    ana.tx.createBranch<bool>                 ("Common_HLT_DoubleEl");
    ana.tx.createBranch<bool>                 ("Common_HLT_MuEG");
    ana.tx.createBranch<bool>                 ("Common_HLT_DoubleMu");

    ana.tx.createBranch<bool>                 ("Common_pass_duplicate_removal_ee_em_mm"); // Flag to identify whether the event passes duplicate removal
    ana.tx.createBranch<bool>                 ("Common_pass_duplicate_removal_mm_em_ee"); // Flag to identify whether the event passes duplicate removal
    ana.tx.createBranch<bool>                 ("Common_noiseFlag");                       // Flag to identify noise
    ana.tx.createBranch<bool>                 ("Common_noiseFlagMC");                     // Flag to identify noise
    ana.tx.createBranch<bool>                 ("Common_passGoodRun");                     // pass golden json

    // Summary 4 vectors of the objects selected
    ana.tx.createBranch<LorentzVector>        ("Common_met_p4");
    ana.tx.createBranch<LorentzVector>        ("Common_met_p4_jesup");
    ana.tx.createBranch<LorentzVector>        ("Common_met_p4_jesdn");
    ana.tx.createBranch<LorentzVector>        ("Common_met_p4_jerup");
    ana.tx.createBranch<LorentzVector>        ("Common_met_p4_jerdn");

    
    ana.tx.createBranch<float>                ("Common_event_lepSF");      // lepSF
    ana.tx.createBranch<float>                ("Common_event_lepSFelup");  // lepSF
    ana.tx.createBranch<float>                ("Common_event_lepSFeldn");  // lepSF
    ana.tx.createBranch<float>                ("Common_event_lepSFmuup");  // lepSF
    ana.tx.createBranch<float>                ("Common_event_lepSFmudn");  // lepSF
    ana.tx.createBranch<float>                ("Common_event_lepSFTight");      // lepSFTight
    ana.tx.createBranch<float>                ("Common_event_lepSFelupTight");  // lepSFTight
    ana.tx.createBranch<float>                ("Common_event_lepSFeldnTight");  // lepSFTight
    ana.tx.createBranch<float>                ("Common_event_lepSFmuupTight");  // lepSFTight
    ana.tx.createBranch<float>                ("Common_event_lepSFmudnTight");  // lepSFTight

    ana.tx.createBranch<float>                ("Common_event_tightBtagSF");      // btagSF
    ana.tx.createBranch<float>                ("Common_event_tightBtagSFup");    // btagSF
    ana.tx.createBranch<float>                ("Common_event_tightBtagSFdn");    // btagSF
    ana.tx.createBranch<float>                ("Common_event_tightBtagSFHFup");  // btagSF
    ana.tx.createBranch<float>                ("Common_event_tightBtagSFHFdn");  // btagSF
    ana.tx.createBranch<float>                ("Common_event_tightBtagSFLFup");  // btagSF
    ana.tx.createBranch<float>                ("Common_event_tightBtagSFLFdn");  // btagSF
    ana.tx.createBranch<float>                ("Common_event_mediumBtagSF");     // btagSF
    ana.tx.createBranch<float>                ("Common_event_mediumBtagSFup");   // btagSF
    ana.tx.createBranch<float>                ("Common_event_mediumBtagSFdn");   // btagSF
    ana.tx.createBranch<float>                ("Common_event_mediumBtagSFHFup"); // btagSF
    ana.tx.createBranch<float>                ("Common_event_mediumBtagSFHFdn"); // btagSF
    ana.tx.createBranch<float>                ("Common_event_mediumBtagSFLFup"); // btagSF
    ana.tx.createBranch<float>                ("Common_event_mediumBtagSFLFdn"); // btagSF
    ana.tx.createBranch<float>                ("Common_event_looseBtagSF");      // btagSF
    ana.tx.createBranch<float>                ("Common_event_looseBtagSFup");    // btagSF
    ana.tx.createBranch<float>                ("Common_event_looseBtagSFdn");    // btagSF
    ana.tx.createBranch<float>                ("Common_event_looseBtagSFHFup");  // btagSF
    ana.tx.createBranch<float>                ("Common_event_looseBtagSFHFdn");  // btagSF
    ana.tx.createBranch<float>                ("Common_event_looseBtagSFLFup");  // btagSF
    ana.tx.createBranch<float>                ("Common_event_looseBtagSFLFdn");  // btagSF

    ana.tx.createBranch<vector<LorentzVector>>("Common_lep_p4");        // Pt sorted selected lepton p4s (electrons and muons together)
    ana.tx.createBranch<vector<int>>          ("Common_lep_idxs");      // Pt sorted selected lepton idxs (electrons and muons together)
    ana.tx.createBranch<vector<int>>          ("Common_lep_pdgid");     // Pt sorted selected lepton pdgids (so that Common_lep_idxs can be used to access NanoAOD)
    ana.tx.createBranch<vector<int>>          ("Common_lep_tight");     // Pt sorted selected lepton tight (Where a tight version of the lepton isolation is used to reduce bkg a bit further if necessary)
    ana.tx.createBranch<vector<float>>        ("Common_lep_dxy");       // Pt sorted selected lepton dxy (electrons and muons together)
    ana.tx.createBranch<vector<float>>        ("Common_lep_dz");        // Pt sorted selected lepton dz (electrons and muons together)
    ana.tx.createBranch<vector<float>>        ("Common_lep_ip3d");      // Pt sorted selected lepton ip3d (electrons and muons together)
    ana.tx.createBranch<vector<float>>        ("Common_lep_sip3d");     // Pt sorted selected lepton sip3d (electrons and muons together)
    ana.tx.createBranch<vector<float>>        ("Common_lep_SF");        // SF
    ana.tx.createBranch<vector<float>>        ("Common_lep_SFTight");   // SF tight iso
    ana.tx.createBranch<vector<float>>        ("Common_lep_SFdn");      // SF
    ana.tx.createBranch<vector<float>>        ("Common_lep_SFdnTight"); // SF tight iso
    ana.tx.createBranch<vector<float>>        ("Common_lep_SFup");      // SF
    ana.tx.createBranch<vector<float>>        ("Common_lep_SFupTight"); // SF tight iso
 
    // Jet variables
    ana.tx.createBranch<vector<LorentzVector>>("Common_jet_p4");            // Pt sorted selected jet p4s
    ana.tx.createBranch<vector<int>>          ("Common_jet_idxs");          // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<bool>>         ("Common_jet_passBloose");    // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<bool>>         ("Common_jet_passBmedium");   // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<bool>>         ("Common_jet_passBtight");    // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<int>>          ("Common_jet_id");    //  https://twiki.cern.ch/twiki/bin/view/CMS/JetID
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFLoose");      // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFMedium");     // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFTight");      // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFdnLoose");    // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFdnMedium");   // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFdnTight");    // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFupLoose");    // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFupMedium");   // single jet bSF
    //ana.tx.createBranch<vector<float>>        ("Common_jet_bSFupTight");    // single jet bSF
    ana.tx.createBranch<vector<int>>          ("Common_jet_overlapfatjet");   // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_jet_pt_jesup");        // jet pt JEC uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_jet_pt_jesdn");        // jet pt JEC uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_jet_pt_jerup");        // jet pt JER uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_jet_pt_jerdn");        // jet pt JER uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_jet_mass_jesup");        // jet pt JEC uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_jet_mass_jesdn");        // jet pt JEC uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_jet_mass_jerup");        // jet pt JER uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_jet_mass_jerdn");        // jet pt JER uncertainty down shift


//Adding var...
    ana.tx.createBranch<vector<LorentzVector>>("Common_jet_tightp4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_bjet_tightp4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_bjetTruth_tightp4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_bTruth_p4");
    ana.tx.createBranch<vector<int>>          ("Common_jet_tightID");
    ana.tx.createBranch<vector<int>>          ("Common_bjet_tightID");
    ana.tx.createBranch<vector<bool>>         ("Common_jetTight_passBtight");
    ana.tx.createBranch<vector<LorentzVector>>("Common_muTruth_p4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_dTruth_p4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_uTruth_p4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_sTruth_p4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_cTruth_p4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_ZTruth_p4");
    ana.tx.createBranch<vector<int>>("Common_ZTruth_idx");


    // Fat jet variables
    ana.tx.createBranch<vector<LorentzVector>>("Common_fatjet_p4");            // Pt sorted selected fatjet p4s
    ana.tx.createBranch<vector<int>>          ("Common_fatjet_idxs");          // Pt sorted selected fatjet idxs (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<int>>          ("Common_fatjet_id");    //  https://twiki.cern.ch/twiki/bin/view/CMS/JetID
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop");     // Pt sorted selected fatjet msoftdrop (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_W");      // Pt sorted selected fatjet FatJet_deepTagMD_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deep_W");        // Pt sorted selected fatjet FatJet_deepTag_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_Z");      // Pt sorted selected fatjet FatJet_deepTagMD_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deep_Z");        // Pt sorted selected fatjet FatJet_deepTag_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_T");      // Pt sorted selected fatjet FatJet_deepTagMD_TvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deep_T");        // Pt sorted selected fatjet FatJet_deepTag_TvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_bb");     // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNetMD_W");     
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNetMD_Xqq");     
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNetMD_Xcc");     
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNetMD_Xbb");     
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNetMD_QCD");     
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNet_QCD");    
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNet_W");    
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNet_Z");   
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_particleNet_T");  
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau3");          // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau2");          // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau1");          // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau32");         // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau21");         // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_pt");    // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_eta");   // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_phi");   // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_mass");  // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_pt");    // Pt sorted selected fatjet subjet p4 1 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_eta");   // Pt sorted selected fatjet subjet p4 2 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_phi");   // Pt sorted selected fatjet subjet p4 3 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_mass");  // Pt sorted selected fatjet subjet p4 4 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<LorentzVector>>("Common_fatjet_subjet0_p4");    // Pt sorted selected fatjet p4s
    ana.tx.createBranch<vector<LorentzVector>>("Common_fatjet_subjet1_p4");    // Pt sorted selected fatjet p4s
    ana.tx.createBranch<vector<int>>          ("Common_fatjet_WP");            // WP: 0: VLoose (5%), 1: Loose (2.5%), 2: Medium (1%), 3: Tight (0.5%)
    ana.tx.createBranch<vector<int>>          ("Common_fatjet_WP_MD");            
    ana.tx.createBranch<vector<int>>          ("Common_fatjet_WP_antimasscut");// WP: 0: VLoose (5%), 1: Loose (2.5%), 2: Medium (1%), 3: Tight (0.5%)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFVLoose");      // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFLoose");       // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFMedium");      // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFTight");       // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFdnVLoose");    // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFdnLoose");     // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFdnMedium");    // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFdnTight");     // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFupVLoose");    // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFupLoose");     // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFupMedium");    // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_SFupTight");     // single fatjet SF
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_pt_jesup");      // fatjet pt JEC uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_pt_jesdn");      // fatjet pt JEC uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_pt_jerup");      // fatjet pt JER uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_pt_jerdn");      // fatjet pt JER uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jesup");      // fatjet softdrop mass JEC uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jesdn");      // fatjet softdrop mass JEC uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jerup");      // fatjet softdrop mass JER uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jerdn");      // fatjet softdrop mass JER uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jmsup");      // fatjet softdrop mass JMS uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jmsdn");      // fatjet softdrop mass JMS uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jmrup");      // fatjet softdrop mass JMR uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop_jmrdn");      // fatjet softdrop mass JMR uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jesup");     // fatjet mass JEC uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jesdn");     // fatjet mass JEC uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jerup");     // fatjet mass JER uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jerdn");     // fatjet mass JER uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jmsup");     // fatjet mass JMS uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jmsdn");     // fatjet mass JMS uncertainty down shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jmrup");     // fatjet mass JMR uncertainty up shift
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_mass_jmrdn");     // fatjet mass JMR uncertainty down shift


    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFVLoose");      // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFLoose");       // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFMedium");      // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFTight");       // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFdnVLoose");    // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFdnLoose");     // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFdnMedium");    // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFdnTight");     // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFupVLoose");    // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFupLoose");     // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFupMedium");    // event fatjet SF
    ana.tx.createBranch<float>        ("Common_eventweight_fatjet_SFupTight");     // event fatjet SF

    // The n-loose b-tagged jets
    ana.tx.createBranch<int>                  ("Common_nb_loose");    // DeepFlav-B loose nb
    ana.tx.createBranch<int>                  ("Common_nb_medium");   // DeepFlav-B medium nb
    ana.tx.createBranch<int>                  ("Common_nb_tight");    // DeepFlav-B tight nb

    // The gen level information
    ana.tx.createBranch<vector<int>>          ("Common_gen_idx");        // Selected gen-particle idx in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_mother_idx"); // Selected gen-particle mother idx in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_mother_id");  // Selected gen-particle mother id in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_pdgid");      // Selected gen-particle pdgids
    ana.tx.createBranch<vector<LorentzVector>>("Common_gen_p4s");        // Selected gen-particle p4s
    ana.tx.createBranch<vector<int>>          ("Common_gen_status");
    ana.tx.createBranch<vector<int>>          ("Common_gen_statusFlags");

}

void Begin_Common_Determine_Is_EFT()
{
    if (ana.run_VVVTree)
    {
        // Determine whether the sample being run over is a EFT sample or not by checking whether a branch exist with the name "LHEWeight_mg_reweighting"
        ana.is_EFT_sample = vvv.Common_LHEWeight_mg_reweighting().size() > 0; // If there are weights it's is EFT
    }
    else
    {
        // Determine whether the sample being run over is a EFT sample or not by checking whether a branch exist with the name "LHEWeight_mg_reweighting"
        ana.is_EFT_sample = false; // default is false
        TObjArray* brobjArray = ana.events_tchain->GetListOfBranches();
        for (unsigned int ibr = 0; ibr < (unsigned int) brobjArray->GetEntries(); ++ibr)
        {
            TString brname = brobjArray->At(ibr)->GetName();
            if (brname.EqualTo("LHEWeight_mg_reweighting"))
                ana.is_EFT_sample = true; // if it has the branch it is set to true
        }
    }

}

void Begin_Common_Determine_Is_Postprocessed()
{
    if (ana.run_VVVTree)
    {
        // TODO: update VVVTree situation
        ana.is_postprocessed = true;
    }
    else
    {
        ana.is_postprocessed = false; //default is false
	TObjArray* brobjArray = ana.events_tchain->GetListOfBranches();
        for (unsigned int ibr = 0; ibr < (unsigned int) brobjArray->GetEntries(); ++ibr)
        {
            TString brname = brobjArray->At(ibr)->GetName();
            if (brname.EqualTo("FatJet_pt_nom"))
                ana.is_postprocessed = true; // if it has the branch it is set to true
        }
    }
}
void Begin_Common_Set_Run_List()
{
    std::string list = "";
    if (ana.run_VVVTree && vvv.Common_isData())
    {
        if (ana.input_file_list_tstring.Contains("Run2016"))
        {
            list = "config/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON_formatted.txt"; // 19.52+16.81 ifb
        }
        if (ana.input_file_list_tstring.Contains("Run2017"))
        {
            list = "config/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON_formatted.txt"; // 41.48 ifb
        }
        if (ana.input_file_list_tstring.Contains("Run2018"))
        {
            list = "config/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON_formatted.txt"; // 59.83 ifb
        }
        set_goodrun_file(list.c_str());
    }
    else if (not ana.run_VVVTree && nt.isData())
    {
        if (nt.year() == 2016)
        {
            list = "config/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON_formatted.txt"; // 19.52+16.81 ifb
        }
        if (nt.year() == 2017)
        {
            list = "config/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON_formatted.txt"; // 41.48 ifb
        }
        if (nt.year() == 2018)
        {
            list = "config/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON_formatted.txt"; // 59.83 ifb
        }
        set_goodrun_file(list.c_str());
    }
}

void Begin_Common_Set_Config()
{

    bool isAPV = ana.input_file_list_tstring.Contains("NanoAODAPVv9")
        or ana.input_file_list_tstring.Contains("NanoAODAPVv2")
        or ana.input_file_list_tstring.Contains("HIPM_UL2016")
        or ana.input_file_list_tstring.Contains("Run2016C-UL2016")
        or ana.input_file_list_tstring.Contains("Run2016D-UL2016")
        or ana.input_file_list_tstring.Contains("Run2016E-UL2016");

    bool isUL = ana.input_file_list_tstring.Contains("UL18")
        or ana.input_file_list_tstring.Contains("UL2018")
        or ana.input_file_list_tstring.Contains("UL17")
        or ana.input_file_list_tstring.Contains("UL2017")
        or ana.input_file_list_tstring.Contains("UL16")
        or ana.input_file_list_tstring.Contains("UL2016");

    if (not isUL)
        RooUtil::error("non-UL sample btagging not implemented. This branch is for Ultra-Legacy!!");

    // Set up the NanoCORE's common configuration service tool
    gconf.nanoAOD_ver = isUL ? 8 : 0;
    gconf.isAPV = isAPV ? 1 : 0;
    gconf.GetConfigs(nt.year());

    if (nt.year() == 2016 and isAPV)
        assert(gconf.WP_DeepFlav_tight - 0.6502 < 0.0001);
    else if (nt.year() == 2016 and not isAPV)
        assert(gconf.WP_DeepFlav_tight - 0.6377 < 0.0001);
    else if (nt.year() == 2017)
        assert(gconf.WP_DeepFlav_tight - 0.7476 < 0.0001);
    else if (nt.year() == 2018)
        assert(gconf.WP_DeepFlav_tight - 0.7100 < 0.0001);
    else
        RooUtil::error("Year and isAPV parsing is messed up!", __FILE__);

    // Setting up btagging scale factors
    if (nt.year() == 2016 and isAPV)
    {
        ana.btagCalib_v2 = new BTagCalibration_v2("DeepJet", "config/DeepJet_106XUL16preVFPSF_v1.csv");
    }
    else if (nt.year() == 2016 and not isAPV)
    {
        ana.btagCalib_v2 = new BTagCalibration_v2("DeepJet", "config/DeepJet_106XUL16postVFPSF_v2.csv");
    }
    else if (nt.year() == 2017)
    {
        ana.btagCalib = new BTagCalibration("DeepJet", "config/DeepJet_106XUL17SF_WPonly_V2p1.csv");
    }
    else if (nt.year() == 2018)
    {
        ana.btagCalib = new BTagCalibration("DeepJet", "config/DeepJet_106XUL18SF_WPonly.csv");
    }
    else
    {
        RooUtil::error(TString::Format("While setting b-tag scale factors, found year = %d that is not recognized.", nt.year()));
    }

    ana.btagReaderTight = new BTagCalibrationReader(BTagEntry::OP_TIGHT, "central", {"up", "down"});
    ana.btagReaderMedium = new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"});
    ana.btagReaderLoose = new BTagCalibrationReader(BTagEntry::OP_LOOSE, "central", {"up", "down"});

    ana.btagReaderTight_v2 = new BTagCalibrationReader_v2(BTagEntry_v2::OP_TIGHT, "central", {"up", "down"});
    ana.btagReaderMedium_v2 = new BTagCalibrationReader_v2(BTagEntry_v2::OP_MEDIUM, "central", {"up", "down"});
    ana.btagReaderLoose_v2 = new BTagCalibrationReader_v2(BTagEntry_v2::OP_LOOSE, "central", {"up", "down"});

    if (nt.year() == 2016 and isAPV)
    {
        ana.btagReaderTight_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_B, "comb");
        ana.btagReaderTight_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_C, "comb");
        ana.btagReaderTight_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_UDSG, "incl");
        ana.btagReaderMedium_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_B, "comb");
        ana.btagReaderMedium_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_C, "comb");
        ana.btagReaderMedium_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_UDSG, "incl");
        ana.btagReaderLoose_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_B, "comb");
        ana.btagReaderLoose_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_C, "comb");
        ana.btagReaderLoose_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_UDSG, "incl");
    }
    else if (nt.year() == 2016 and not isAPV)
    {
        ana.btagReaderTight_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_B, "comb");
        ana.btagReaderTight_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_C, "comb");
        ana.btagReaderTight_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_UDSG, "incl");
        ana.btagReaderMedium_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_B, "comb");
        ana.btagReaderMedium_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_C, "comb");
        ana.btagReaderMedium_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_UDSG, "incl");
        ana.btagReaderLoose_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_B, "comb");
        ana.btagReaderLoose_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_C, "comb");
        ana.btagReaderLoose_v2->load(*ana.btagCalib_v2, BTagEntry_v2::FLAV_UDSG, "incl");
    }
    else
    {
        ana.btagReaderTight->load(*ana.btagCalib, BTagEntry::FLAV_B, "comb");
        ana.btagReaderTight->load(*ana.btagCalib, BTagEntry::FLAV_C, "comb");
        ana.btagReaderTight->load(*ana.btagCalib, BTagEntry::FLAV_UDSG, "incl");
        ana.btagReaderMedium->load(*ana.btagCalib, BTagEntry::FLAV_B, "comb");
        ana.btagReaderMedium->load(*ana.btagCalib, BTagEntry::FLAV_C, "comb");
        ana.btagReaderMedium->load(*ana.btagCalib, BTagEntry::FLAV_UDSG, "incl");
        ana.btagReaderLoose->load(*ana.btagCalib, BTagEntry::FLAV_B, "comb");
        ana.btagReaderLoose->load(*ana.btagCalib, BTagEntry::FLAV_C, "comb");
        ana.btagReaderLoose->load(*ana.btagCalib, BTagEntry::FLAV_UDSG, "incl");
    }

    if (nt.year() == 2016 and isAPV)
    {
        ana.btagEffTight_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_b");
        ana.btagEffTight_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_c");
        ana.btagEffTight_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_udsg");
        ana.btagEffMedium_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_med_Eff_b");
        ana.btagEffMedium_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_med_Eff_c");
        ana.btagEffMedium_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_med_Eff_udsg");
        ana.btagEffLoose_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_b");
        ana.btagEffLoose_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_c");
        ana.btagEffLoose_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016APV_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_udsg");
    }
    else if (nt.year() == 2016 and not isAPV)
    {
        ana.btagEffTight_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_b");
        ana.btagEffTight_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_c");
        ana.btagEffTight_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_udsg");
        ana.btagEffMedium_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_med_Eff_b");
        ana.btagEffMedium_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_med_Eff_c");
        ana.btagEffMedium_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_med_Eff_udsg");
        ana.btagEffLoose_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_b");
        ana.btagEffLoose_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_c");
        ana.btagEffLoose_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2016_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_udsg");
    }
    else if (nt.year() == 2017)
    {
        ana.btagEffTight_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_b");
        ana.btagEffTight_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_c");
        ana.btagEffTight_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_udsg");
        ana.btagEffMedium_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_med_Eff_b");
        ana.btagEffMedium_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_med_Eff_c");
        ana.btagEffMedium_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_med_Eff_udsg");
        ana.btagEffLoose_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_b");
        ana.btagEffLoose_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_c");
        ana.btagEffLoose_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2017_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_udsg");
    }
    else if (nt.year() == 2018)
    {
        ana.btagEffTight_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_b");
        ana.btagEffTight_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_c");
        ana.btagEffTight_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_tight_Eff_udsg");
        ana.btagEffMedium_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_med_Eff_b");
        ana.btagEffMedium_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_med_Eff_c");
        ana.btagEffMedium_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_med_Eff_udsg");
        ana.btagEffLoose_b = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_b");
        ana.btagEffLoose_c = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_c");
        ana.btagEffLoose_l = new RooUtil::HistMap("config/eff_DeepFlav_106X_2018_ttbar_1lep.root:h2_BTaggingEff_loose_Eff_udsg");
    }
    else
    {
        RooUtil::error(TString::Format("While setting b-tag efficiencies, found year = %d that is not recognized.", nt.year()));
    }

    // Muon SF
    if (nt.year() == 2016 and isAPV)
    {
        ana.muonRECOSF     = new RooUtil::HistMap("config/Efficiency_muon_generalTracks_Run2016preVFP_UL_trackerMuon.root:NUM_TrackerMuons_DEN_genTracks");
        ana.muonIDSFMedium = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ID.root:NUM_MediumID_DEN_TrackerMuons_abseta_pt");
        ana.muonISOSFLoose = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root:NUM_LooseRelIso_DEN_MediumID_abseta_pt");
        ana.muonISOSFTight = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root:NUM_TightRelIso_DEN_MediumID_abseta_pt");
    }
    else if (nt.year() == 2016 and not isAPV)
    {
        ana.muonRECOSF     = new RooUtil::HistMap("config/Efficiency_muon_generalTracks_Run2016postVFP_UL_trackerMuon.root:NUM_TrackerMuons_DEN_genTracks");
        ana.muonIDSFMedium = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2016_UL_ID.root:NUM_MediumID_DEN_TrackerMuons_abseta_pt");
        ana.muonISOSFLoose = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2016_UL_ISO.root:NUM_LooseRelIso_DEN_MediumID_abseta_pt");
        ana.muonISOSFTight = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2016_UL_ISO.root:NUM_TightRelIso_DEN_MediumID_abseta_pt");
    }
    else if (nt.year() == 2017)
    {
        ana.muonRECOSF     = new RooUtil::HistMap("config/Efficiency_muon_generalTracks_Run2017_UL_trackerMuon.root:NUM_TrackerMuons_DEN_genTracks");
        ana.muonIDSFMedium = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root:NUM_MediumID_DEN_TrackerMuons_abseta_pt");
        ana.muonISOSFLoose = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root:NUM_LooseRelIso_DEN_MediumID_abseta_pt");
        ana.muonISOSFTight = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root:NUM_TightRelIso_DEN_MediumID_abseta_pt");
    }
    else if (nt.year() == 2018)
    {
        ana.muonRECOSF     = new RooUtil::HistMap("config/Efficiency_muon_generalTracks_Run2018_UL_trackerMuon.root:NUM_TrackerMuons_DEN_genTracks");
        ana.muonIDSFMedium = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root:NUM_MediumID_DEN_TrackerMuons_abseta_pt");
        ana.muonISOSFLoose = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root:NUM_LooseRelIso_DEN_MediumID_abseta_pt");
        ana.muonISOSFTight = new RooUtil::HistMap("config/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root:NUM_TightRelIso_DEN_MediumID_abseta_pt");
    }
    else
    {
        RooUtil::error(TString::Format("While setting muon scale factors, found year = %d that is not recognized.", nt.year()));
    }

    // Electron SF
    if (nt.year() == 2016 and isAPV)
    {
        ana.electronRECOSFlt20 = new RooUtil::HistMap("config/egammaEffi_ptBelow20.txt_EGM2D_UL2016preVFP.root:EGamma_SF2D");
        ana.electronRECOSFgt20 = new RooUtil::HistMap("config/egammaEffi_ptAbove20.txt_EGM2D_UL2016preVFP.root:EGamma_SF2D");
        ana.electronMVAID90SF  = new RooUtil::HistMap("config/egammaEffi.txt_Ele_wp90iso_preVFP_EGM2D.root:EGamma_SF2D");
        ana.electronMVAID80SF  = new RooUtil::HistMap("config/egammaEffi.txt_Ele_wp80iso_preVFP_EGM2D.root:EGamma_SF2D");
    }
    else if (nt.year() == 2016 and not isAPV)
    {
        ana.electronRECOSFlt20 = new RooUtil::HistMap("config/egammaEffi_ptBelow20.txt_EGM2D_UL2016postVFP.root:EGamma_SF2D");
        ana.electronRECOSFgt20 = new RooUtil::HistMap("config/egammaEffi_ptAbove20.txt_EGM2D_UL2016postVFP.root:EGamma_SF2D");
        ana.electronMVAID90SF  = new RooUtil::HistMap("config/egammaEffi.txt_Ele_wp90iso_postVFP_EGM2D.root:EGamma_SF2D");
        ana.electronMVAID80SF  = new RooUtil::HistMap("config/egammaEffi.txt_Ele_wp80iso_postVFP_EGM2D.root:EGamma_SF2D");
    }
    else if (nt.year() == 2017)
    {
        ana.electronRECOSFlt20 = new RooUtil::HistMap("config/egammaEffi_ptBelow20.txt_EGM2D_UL2017.root:EGamma_SF2D");
        ana.electronRECOSFgt20 = new RooUtil::HistMap("config/egammaEffi_ptAbove20.txt_EGM2D_UL2017.root:EGamma_SF2D");
        ana.electronMVAID90SF  = new RooUtil::HistMap("config/egammaEffi.txt_EGM2D_MVA90iso_UL17.root:EGamma_SF2D");
        ana.electronMVAID80SF  = new RooUtil::HistMap("config/egammaEffi.txt_EGM2D_MVA80iso_UL17.root:EGamma_SF2D");
    }
    else if (nt.year() == 2018)
    {
        ana.electronRECOSFlt20 = new RooUtil::HistMap("config/egammaEffi_ptBelow20.txt_EGM2D_UL2018.root:EGamma_SF2D");
        ana.electronRECOSFgt20 = new RooUtil::HistMap("config/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root:EGamma_SF2D");
        ana.electronMVAID90SF  = new RooUtil::HistMap("config/egammaEffi.txt_Ele_wp90iso_EGM2D.root:EGamma_SF2D");
        ana.electronMVAID80SF  = new RooUtil::HistMap("config/egammaEffi.txt_Ele_wp80iso_EGM2D.root:EGamma_SF2D");
    }
    else
    {
        RooUtil::error(TString::Format("While setting electron scale factors, found year = %d that is not recognized.", nt.year()));
    }
    
    // Trigger SF
    if (nt.year() == 2016 and isAPV)
    {
	ana.triggereeSF   = new RooUtil::HistMap("config/TriggerSF_2016preVFP_UL.root:h2D_SF_ee_lepABpt_FullError");
	ana.triggeremuSF  = new RooUtil::HistMap("config/TriggerSF_2016preVFP_UL.root:h2D_SF_emu_lepABpt_FullError");
	ana.triggermumuSF = new RooUtil::HistMap("config/TriggerSF_2016preVFP_UL.root:h2D_SF_mumu_lepABpt_FullError");
    }
    else if (nt.year() == 2016 and not isAPV)
    {
        ana.triggereeSF   = new RooUtil::HistMap("config/TriggerSF_2016postVFP_UL.root:h2D_SF_ee_lepABpt_FullError");
        ana.triggeremuSF  = new RooUtil::HistMap("config/TriggerSF_2016postVFP_UL.root:h2D_SF_emu_lepABpt_FullError");
        ana.triggermumuSF = new RooUtil::HistMap("config/TriggerSF_2016postVFP_UL.root:h2D_SF_mumu_lepABpt_FullError");

    }
    else if (nt.year() == 2017)
    {
        ana.triggereeSF   = new RooUtil::HistMap("config/TriggerSF_2017_UL.root:h2D_SF_ee_lepABpt_FullError");
        ana.triggeremuSF  = new RooUtil::HistMap("config/TriggerSF_2017_UL.root:h2D_SF_emu_lepABpt_FullError");
        ana.triggermumuSF = new RooUtil::HistMap("config/TriggerSF_2017_UL.root:h2D_SF_mumu_lepABpt_FullError");

    }
    else if (nt.year() == 2018)
    {
        ana.triggereeSF   = new RooUtil::HistMap("config/TriggerSF_2018_UL.root:h2D_SF_ee_lepABpt_FullError");
        ana.triggeremuSF  = new RooUtil::HistMap("config/TriggerSF_2018_UL.root:h2D_SF_emu_lepABpt_FullError");
        ana.triggermumuSF = new RooUtil::HistMap("config/TriggerSF_2018_UL.root:h2D_SF_mumu_lepABpt_FullError");
    }
    else
    {
        RooUtil::error(TString::Format("While setting trigger scale factors, found year = %d that is not recognized.", nt.year()));
    }


}

void Begin_Common_VVVTree()
{

    // Define basic selections
    // CommonCut will contain selections that should be common to all categories, starting from this cut, add cuts for this category of the analysis.
    ana.cutflow.addCut("Wgt", [&]() { return 1; }, [&]() { if (not vvv.Common_isData()) return (vvv.Common_genWeight() > 0) - (vvv.Common_genWeight() < 0); else return 1; } );
    ana.cutflow.addCutToLastActiveCut("SelectVH", [&]() { return (ana.vhvvv_channel < 0 ? true: ana.vhvvv_channel == vvv.Common_gen_VH_channel());}, UNITY );
    ana.cutflow.addCutToLastActiveCut("CommonCut", [&]() {
        
        //check golden json -- branch is true if MC
        if(! ana.tx.getBranchLazy<bool>("Common_passGoodRun")) return false;

        //check basic filters 
        if ( vvv.Common_isData() && ana.tx.getBranchLazy<bool>("Common_noiseFlag") ) return true;
        else if ( !vvv.Common_isData() && ana.tx.getBranchLazy<bool>("Common_noiseFlagMC") ) return true;
        else return false;
        }, [&]() { return 1; } );

}

void Begin_Common_NanoAOD()
{

    // Define basic selections
    // CommonCut will contain selections that should be common to all categories, starting from this cut, add cuts for this category of the analysis.
    ana.cutflow.addCut("Wgt", [&]() { return 1; }, [&]() { if (not nt.isData()) return (nt.genWeight() > 0) - (nt.genWeight() < 0); else return 1; } );
    ana.cutflow.addCutToLastActiveCut("SelectVH", [&]() { return (ana.vhvvv_channel < 0 ? true: ana.vhvvv_channel == ana.tx.getBranchLazy<int>("Common_gen_VH_channel"));}, UNITY );
    ana.cutflow.addCutToLastActiveCut("CommonCut", [&]() { 
        //check golden json -- branch is true if MC
        if(! ana.tx.getBranchLazy<bool>("Common_passGoodRun")) return false;
        
        
        //check basic filters 
        if ( nt.isData() and !ana.tx.getBranchLazy<bool>("Common_noiseFlag") ) return false;
        
        if ( !nt.isData() and !ana.tx.getBranchLazy<bool>("Common_noiseFlagMC") ) return false;
        
       /* std::cout << std::endl << "still here??? " << std::endl;
        std::cout << "noise data? "<< ( nt.isData() and !ana.tx.getBranchLazy<bool>("Common_noiseFlag") )<< std::endl;
        std::cout << "noise MC? "<< ( !nt.isData() and !ana.tx.getBranchLazy<bool>("Common_noiseFlagMC") ) << std::endl;
        std::cout << "pass golden json? " << ana.tx.getBranchLazy<bool>("Common_passGoodRun") << std::endl;
       */ 
        return true;
        
        }, [&]() { return 1; } );

//DY
/*
    ana.cutflow.addCutToLastActiveCut("Drell-Yan",[&](){

	if ( ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").size() != 2 ) return false;

	if ( (ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(0) + ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(1)) != 0 ) return false;

        if ( ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(0) != 13 && ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(0) != -13) return false;

	return true;

	},UNITY);
*/

//Top
/*
    ana.cutflow.addCutToLastActiveCut("2Leptons",[&](){

        if ( ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").size() != 2 ) return false;

        if ( (ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(0) + ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(1)) != 0 ) return false;


        return true;

        },UNITY);
*/


    // Various book keeping variables are included here.
    // TODO: Define some diagnostic basic plots

    Begin_Common_Book_NEvent_Histograms();

    // Create histograms used in this category.
    // Please follow the convention of h_<category>_<varname> structure.
    // N.B. Using nbins of size 180 or 360 can provide flexibility as it can be rebinned easily, as 180, 360 are highly composite numbers.
    RooUtil::Histograms hists_Common;
    hists_Common.addHistogram("h_Common_nLep", 10, 0, 10, [&]() { return ana.tx.getBranchLazy<vector<int>>("Common_lep_idxs").size(); } );
    hists_Common.addHistogram("h_Common_nJet", 10, -0.5, 9.5, [&]() { return ana.tx.getBranchLazy<vector<int>>("Common_jet_idxs").size(); } );
    hists_Common.addHistogram("h_Common_nFatJet", 10, 0, 10, [&]() { return ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size(); } );


//Adding plots...
/*
    hists_Common.addHistogram("Zmass", 100, 60, 120, [&]() { 

        return (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(0) + ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(1)).M(); } );


    hists_Common.addHistogram("ZpT", 400, 0, 400, [&]() { 

        return (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(0) + ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(1)).Pt(); } );


    ana.cutflow.bookHistogramsForCut(hists_Common, "Drell-Yan");
*/



/*

    hists_Common.addHistogram("nJetTight", 10, -0.5, 9.5, [&]() { 
        return ana.tx.getBranchLazy<vector<int>>("Common_jet_tightID").size(); } );


    hists_Common.addHistogram("nbJetTight", 3, 1.5, 4.5, [&]() {//b-tagging 
        return ana.tx.getBranchLazy<vector<int>>("Common_bjet_tightID").size(); } );


    hists_Common.addHistogram("Mass2b", 140, 20, 160, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {
            LorentzVector b1, b2;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(1);
            return (b1 + b2).M();
        }
        return float(0); } );

    
    hists_Common.addHistogram("Mass2bTruth", 140, 20, 160, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").size() == 2)
        {
            LorentzVector b1, b2;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(1);
            return (b1 + b2).M();
        }
        return float(0); } );


    hists_Common.addHistogram("M_b1Truth", 60, 60, 120, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").size() == 2)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(0).M();
        return float(0); } );


    hists_Common.addHistogram("M_b2Truth", 60, 60, 120, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").size() == 2)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(1).M();
        return float(0); } );


    hists_Common.addHistogram("pT_b1Truth", 500, 0, 500, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").size() == 2)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(0).Pt();
        return float(-1); } );


    hists_Common.addHistogram("pT_b2Truth", 500, 0, 500, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").size() == 2)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(1).Pt();
        return float(-1); } );
*/


/*
    hists_Common.addHistogram("dR_2bTruth_Zboost", 100, 0, 2, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").size() == 2)
        {
            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjetTruth_tightp4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                return RooUtil::Calc::DeltaR(b1, b2);
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_2bTruth_ZTruthboost", 100, 0, 2, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2)
        {
            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                if (b1.Pt() > 20 && abs(b1.Eta()) < 2.5 && b2.Pt() > 20 && abs(b2.Eta()) < 2.5)
                {
                    return RooUtil::Calc::DeltaR(b1, b2);
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_Z-Fjet_ZTruthboost", 100, 0, 2, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                return RooUtil::Calc::DeltaR(Z2b, ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0));
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_AK4b1-AK8_ZTruthboost", 100, 0, 2, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {
            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                return RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0), ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0));
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_AK4b2-AK8_ZTruthboost", 100, 0, 2, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {
            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                return RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(1), ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0));
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("N_muAK8_ZTruthboost", 5, 0.5, 5.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {
            int N_mu = 0;

            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
	        if (RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0), ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0)) < 0.6)
                {
                    unsigned int Nmax = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").size();
                    for (unsigned int i = 0; i < Nmax; i++)
                    {
                        if (ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(i) == 13 || ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(i) == -13)
                        {
                            float pT_mu = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(i).Pt();
                            float dR_muAK8 = RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(i), ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0));
                            if (pT_mu > 5 && dR_muAK8 < 0.8)
                            {
                                N_mu += 1;
                            }
                        }
                    }
                } 
            }
            return N_mu; 
        }
        return int(-1); } );
    

    hists_Common.addHistogram("N_muTruthAK8_ZTruthboost", 5, 0.5, 5.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {
            int N_mu = 0;

            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                if (RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0), ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0)) < 0.6)
                {
                    unsigned int Nmax = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_muTruth_p4").size();
                    for (unsigned int i = 0; i < Nmax; i++)
                    {
                        float pT_mu = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_muTruth_p4").at(i).Pt();
                        float dR_muAK8 = RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_muTruth_p4").at(i), ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0));
                        if (pT_mu > 5 && dR_muAK8 < 0.8)
                        {
                            N_mu += 1;
                        }
                    }
                }
            }
            return N_mu;
        }
        return int(-1); } );
*/

//Count trigger jets
    hists_Common.addHistogram("N_triggerAK4_ZTruthboost", 9, -0.5, 8.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0)
        {
            LorentzVector b1, b2, Z2b;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                int N_AK4 = 0;
                for (unsigned int i = 0; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                {
                    LorentzVector AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                    if (AK4.Vect().Dot(Z2b.Vect()) < 0)
                    {
                        if (AK4.Pt() > 100)
                        {
                            N_AK4 += 1;
                        }
                    }
                }
                return N_AK4;
            }
        }
        return int(-1); } );

/*
    hists_Common.addHistogram("Phi_triggerAK4", 20, -2*M_PI, 2*M_PI, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0)
        {   
            LorentzVector AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            if (AK4.Pt() > 30)
            {   
                return AK4.Phi();
            }
        }
        return float(-10); } );


    hists_Common.addHistogram("dR_muAK8_2_ZTruthboost", 200, 0, 4, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() > 1 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {
            LorentzVector b1, b2, Z2b, AK8;
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(1);
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                if (RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0), AK8) < 0.6)
                {
                    unsigned int Nmax = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").size();
                    for (unsigned int i = 0; i < Nmax; i++)
                    {
                        if (ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(i) == 13 || ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(i) == -13)
                        {
                            return RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(i), AK8);
                            break;
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_muAK8_1_ZTruthboost", 200, 0, 4, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {
            LorentzVector b1, b2, Z2b, AK8;
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (Z2b.Pt() > 200)
            {
                if (RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0), AK8) < 0.6)
                {
                    unsigned int Nmax = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").size();
                    for (unsigned int i = 0; i < Nmax; i++)
                    {
                        if (ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(i) == 13 || ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(i) == -13)
                        {
                            return RooUtil::Calc::DeltaR(ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(i), AK8);
                            break;
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("pT_AK4_1_ZTruthboost", 300, 200, 800, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0)
        {  
            LorentzVector b1, b2, Z2b, AK4;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(Z2b.Vect()) < 0)
                {
                    return AK4.Pt();
                }
            }
        }
        return float(-1); } );

*/
//****************************************************************************************************************//
//Adding
//Only RECO
/*
    hists_Common.addHistogram("pT_AK4_1", 350, 100, 800, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0)
        {   
            LorentzVector AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            if (AK4.Pt() > 200)
            {   
                return AK4.Pt();
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("pT_AK8_1", 350, 100, 800, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {   
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {       
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        return AK8.Pt();
                    }
                }
            }
        }
        return float(-1); } );
*/

//Selection for real process
    hists_Common.addHistogram("pT_AK8_1_boost", 350, 100, 800, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;       
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            return AK8.Pt();
                        }
                    }
                }
            }
        }
        return float(-1); } );

    
    hists_Common.addHistogram("b_score_AK8_1_boost_btag", 50, 0, 1, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            return nt.FatJet_deepTagMD_bbvsLight()[AK8idx];
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_ZTruthAK8_1_boost", 100, 0, 4, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector Z, AK4, AK8;
            Z = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").at(0);
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            return RooUtil::Calc::DeltaR(AK8, Z);
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_ZTruthAK8_1_boost_btag", 100, 0, 4, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector Z, AK4, AK8;
            Z = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").at(0);
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                return RooUtil::Calc::DeltaR(AK8, Z);
                            }
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("Msd_AK8_1_boost_btag", 180, 0, 180, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {   
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {   
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {   
                    if (AK8.Pt() > 100)
                    {   
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)                       
                        {   
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {   
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {   
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {   
                                return nt.FatJet_msoftdrop()[AK8idx];
                            }
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("Msd_AK8_1_boost_btag_Z4bTruth", 180, 0, 180, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() >= 2 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                return nt.FatJet_msoftdrop()[AK8idx];
                            }
                        }
                    }
                }
            }
        }
        return float(-1); } );

/*
    hists_Common.addHistogram("Nb_checkAK8", 7, -0.5, 6.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() >= 2 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {   
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {   
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {   
                    if (AK8.Pt() > 100)
                    {   
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)                       
                        {   
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {   
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && (Id == 5 || Id == -5) && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                return Nb;
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );


    hists_Common.addHistogram("Msd_checkAK8_4b", 180, 0, 180, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() >= 2 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && (Id == 5 || Id == -5) && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    return nt.FatJet_msoftdrop()[AK8idx];
                                }
                            }
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("Msd_checkAK8_2b", 180, 0, 180, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() >= 2 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && (Id == 5 || Id == -5) && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 2)
                                {
                                    return nt.FatJet_msoftdrop()[AK8idx];
                                }
                            }
                        }
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("N_emu_Z4bTruth", 6, -0.5, 5.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_emu = 0;
                                    unsigned int Nmax = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").size();
                                    for (unsigned int i = 0; i < Nmax; i++)
                                    {
                                        int Id = ana.tx.getBranchLazy<vector<int>>("Common_lep_pdgid").at(i);
                                        if (abs(Id) == 13 || abs(Id) == 11)
                                        {
                                            LorentzVector Lep = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_lep_p4").at(i);
                                            float pT = Lep.Pt();
                                            float dR_AK8 = RooUtil::Calc::DeltaR(AK8, Lep);
                                            if (pT > 5 && dR_AK8 < 0.8)
                                            {
                                                N_emu += 1;
                                            }
                                        }
                                    }
                                    return N_emu;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );
*/

    hists_Common.addHistogram("N_SV_Z4bTruth", 12, -0.5, 11.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_SV = 0;
                                    for (unsigned int i = 0; i < nt.SV_mass().size(); i++)
                                    {
                                        float etaSV = nt.SV_eta()[i];
                                        float phiSV = nt.SV_phi()[i];
                                        float dR_AK8 = sqrt((etaSV-AK8.Eta())*(etaSV-AK8.Eta())+(phiSV-AK8.Phi())*(phiSV-AK8.Phi()));
                                        if (dR_AK8 < 0.8)
                                        {
                                            N_SV += 1;
                                        }
                                    }
                                    return N_SV;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } ); 


    hists_Common.addHistogram("N_SV_massCut_Z4bTruth", 12, -0.5, 11.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_SV = 0;
                                    for (unsigned int i = 0; i < nt.SV_mass().size(); i++)
                                    {
                                        float etaSV = nt.SV_eta()[i];
                                        float phiSV = nt.SV_phi()[i];
                                        float dR_AK8 = sqrt((etaSV-AK8.Eta())*(etaSV-AK8.Eta())+(phiSV-AK8.Phi())*(phiSV-AK8.Phi()));
                                        if (dR_AK8 < 0.8)
                                        {
                                            float massSV = nt.SV_mass()[i];
                                            if (massSV > 3) N_SV += 1;
                                        }
                                    }
                                    return N_SV;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );



    hists_Common.addHistogram("N_SV_mdCut_Z4bTruth", 12, -0.5, 11.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_SV = 0;
                                    for (unsigned int i = 0; i < nt.SV_mass().size(); i++)
                                    {
                                        float etaSV = nt.SV_eta()[i];
                                        float phiSV = nt.SV_phi()[i];
                                        float dR_AK8 = sqrt((etaSV-AK8.Eta())*(etaSV-AK8.Eta())+(phiSV-AK8.Phi())*(phiSV-AK8.Phi()));
                                        if (dR_AK8 < 0.8)
                                        {
                                            float massSV = nt.SV_mass()[i];
                                            float dlenSV = nt.SV_dlen()[i];
                                            if (massSV > 3 && dlenSV > 0.1) N_SV += 1;
                                        }
                                    }
                                    return N_SV;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );


    hists_Common.addHistogram("N_SV_mdnCut_Z4bTruth", 12, -0.5, 11.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_SV = 0;
                                    for (unsigned int i = 0; i < nt.SV_mass().size(); i++)
                                    {
                                        float etaSV = nt.SV_eta()[i];
                                        float phiSV = nt.SV_phi()[i];
                                        float dR_AK8 = sqrt((etaSV-AK8.Eta())*(etaSV-AK8.Eta())+(phiSV-AK8.Phi())*(phiSV-AK8.Phi()));
                                        if (dR_AK8 < 0.8)
                                        {
                                            float massSV = nt.SV_mass()[i];
                                            float dlenSV = nt.SV_dlen()[i];
                                            float ndofSV = nt.SV_ndof()[i];
                                            if (massSV > 3 && dlenSV > 0.1 && ndofSV >= 3) N_SV += 1;
                                        }
                                    }
                                    return N_SV;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );


    hists_Common.addHistogram("N_SV_dlenCut_Z4bTruth", 12, -0.5, 11.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_SV = 0;
                                    for (unsigned int i = 0; i < nt.SV_mass().size(); i++)
                                    {
                                        float etaSV = nt.SV_eta()[i];
                                        float phiSV = nt.SV_phi()[i];
                                        float dR_AK8 = sqrt((etaSV-AK8.Eta())*(etaSV-AK8.Eta())+(phiSV-AK8.Phi())*(phiSV-AK8.Phi()));
                                        if (dR_AK8 < 0.8)
                                        {
                                            float dlenSV = nt.SV_dlen()[i];
                                            if (dlenSV > 0.1) N_SV += 1;
                                        }
                                    }
                                    return N_SV;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );


    hists_Common.addHistogram("N_SV_ndofCut_Z4bTruth", 12, -0.5, 11.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {   
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {   
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_SV = 0;
                                    for (unsigned int i = 0; i < nt.SV_mass().size(); i++)
                                    {
                                        float etaSV = nt.SV_eta()[i];
                                        float phiSV = nt.SV_phi()[i];
                                        float dR_AK8 = sqrt((etaSV-AK8.Eta())*(etaSV-AK8.Eta())+(phiSV-AK8.Phi())*(phiSV-AK8.Phi()));
                                        if (dR_AK8 < 0.8)
                                        {
                                            float ndofSV = nt.SV_ndof()[i];
                                            if (ndofSV >= 3) N_SV += 1;
                                        }
                                    }
                                    return N_SV;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );

/*
    hists_Common.addHistogram("N_SV_bHadron_Z4bTruth", 12, -0.5, 11.5, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int Nb = 0;
                                for (unsigned int i = 0; i < nt.GenPart_p4().size(); i++)
                                {
                                    float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[i]);
                                    int Id = nt.GenPart_pdgId()[i];
                                    int Status = nt.GenPart_status()[i];
                                    if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                    {
                                        int mi = nt.GenPart_genPartIdxMother()[i];
                                        int count = 0;
                                        while (nt.GenPart_pdgId()[mi] != 23 && count < 10)
                                        {
                                            mi = nt.GenPart_genPartIdxMother()[mi];
                                            count++;
                                        }
                                        if (nt.GenPart_pdgId()[mi] == 23)
                                        {
                                            Nb++;
                                        }
                                    }
                                }
                                if (Nb == 4)
                                {
                                    int N_SV = 0;
                                    for (unsigned int i = 0; i < nt.SV_mass().size(); i++)
                                    {
                                        float etaSV = nt.SV_eta()[i];
                                        float phiSV = nt.SV_phi()[i];
                                        float dR_AK8 = sqrt((etaSV-AK8.Eta())*(etaSV-AK8.Eta())+(phiSV-AK8.Phi())*(phiSV-AK8.Phi()));
                                        if (dR_AK8 < 0.8)
                                        {
                                            for (unsigned int j = 0; j < nt.GenPart_p4().size(); j++)
                                            {
                                                float dR = RooUtil::Calc::DeltaR(AK8, nt.GenPart_p4()[j]);
                                                int Id = nt.GenPart_pdgId()[j];
                                                int Status = nt.GenPart_status()[j];
                                                if (dR < 0.8 && abs(Id) == 5 && Status > 20 && Status < 30)
                                                {
                                                    int mj = nt.GenPart_genPartIdxMother()[j];
                                                    int count = 0;
                                                    while (nt.GenPart_pdgId()[mj] != 23 && count < 10)
                                                    {   
                                                        mj = nt.GenPart_genPartIdxMother()[mj];
                                                        count++;
                                                    }
                                                    if (nt.GenPart_pdgId()[mj] == 23)
                                                    {
                                                        float etaP = nt.GenPart_eta()[j];
                                                        float phiP = nt.GenPart_phi()[j];
                                                        float dR_P = sqrt((etaSV-etaP)*(etaSV-etaP)+(phiSV-phiP)*(phiSV-phiP));
                                                        if (dR_P < 0.8) 
                                                        {
                                                            N_SV += 1;
                                                            break;
                                                        }
                                                    }
                                                }                                                
                                            }
                                        }
                                    }
                                    return N_SV;
                                }
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );
*/    

/*
    hists_Common.addHistogram("daughter_ZTruth", 14, 0.5, 14.5, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_ZTruth_idx").size() != 0 && ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector Z, AK4, AK8;
            Z = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_ZTruth_p4").at(0);
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);           
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                if (RooUtil::Calc::DeltaR(AK8, Z) < 0.6)
                                {
                                    for (unsigned int i = 0; i < nt.GenPart_pdgId().size(); i++)
                                    {
                                        //if (ana.tx.getBranchLazy<vector<int>>("Common_ZTruth_idx").at(0) == nt.GenPart_genPartIdxMother()[i])
                                        int midx = nt.GenPart_genPartIdxMother()[i];
                                        if (nt.GenPart_pdgId()[i] != 23 && nt.GenPart_pdgId()[midx] == 23)
                                        {
                                            return abs(nt.GenPart_pdgId()[i]);
                                            break;
                                        }
                                    }
                                }    
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );   
*/

/*
// HT
    hists_Common.addHistogram("HT", 1000, 0, 1000, [&]() {
	if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            float HT = 0;
            for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size(); i++)
            {
                LorentzVector fatjet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(i);
                HT += fatjet.Pt();
            }   

            if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_p4").size() != 0)
            {
                for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_p4").size(); i++) 
                { 
                    if (ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                    {
                        LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_p4").at(i);
                        HT += jet.Pt();
                    }
                }
            }

            if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_met_p4").size() != 0)
            {
                for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_met_p4").size(); i++)
                {
                    LorentzVector met = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_met_p4").at(i);
                    HT += met.Pt();
                }
            }

            return HT;
        }
        return float(-1); } );
*/
//Adding
// Num of jets
    hists_Common.addHistogram("N_jets_total", 9, -0.5, 8.5, [&]() {
	if (ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            if (AK4.Pt() > 200)
            {
                if (AK4.Vect().Dot(AK8.Vect()) < 0)
                {
                    if (AK8.Pt() > 100)
                    {
                        int JetOver60 = 0;
                        for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                        {
                            LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                            if (jet.Pt() > 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                            {
                                JetOver60 += 1;
                            }
                        }
                        if (JetOver60 == 0)
                        {
                            int AK8idx = ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").at(0);
                            if (nt.FatJet_deepTagMD_bbvsLight()[AK8idx] > 0.9)
                            {
                                int NJets = 1;
                                for (unsigned int i = 1; i < ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size(); i++)
                                {
                                    LorentzVector jet = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(i);
                                    if (jet.Pt() < 60 && ana.tx.getBranchLazy<vector<int>>("Common_jet_overlapfatjet").at(i) == -1)
                                    {
                                        NJets += 1;
                                    }
                                }
                                return NJets;
                            }
                        }
                    }
                }
            }
        }
        return int(-1); } );

//****************************************************************************************************//
/*
    hists_Common.addHistogram("pT_AK8_1_ZTruthboost", 300, 200, 800, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector b1, b2, Z2b, AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (AK4.Vect().Dot(Z2b.Vect()) < 0)
            {
                if (AK4.Pt() > 200)
                {
                    if (AK4.Vect().Dot(AK8.Vect()) < 0)
                    {
                        return AK8.Pt();
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("dR_ZTruthAK8_1_ZTruthboost", 200, 0, 4, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").size() != 0 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0)
        {
            LorentzVector b1, b2, Z2b, AK4, AK8;
            AK4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0);
            AK8 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").at(0);
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").at(1);
            Z2b = b1 + b2;
            if (AK4.Vect().Dot(Z2b.Vect()) < 0)
            {
                if (AK4.Pt() > 200)
                {
                    if (AK4.Vect().Dot(AK8.Vect()) < 0)
                    {
                        return RooUtil::Calc::DeltaR(AK8, Z2b);
                    }
                }
            }
        }
        return float(-1); } );


    hists_Common.addHistogram("bbscore_btagCSVV2", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagCSVV2()[0]; } return float(-10); } );
    hists_Common.addHistogram("ddscore_btagCSVV2", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_dTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagCSVV2()[0]; } return float(-10); } );
    hists_Common.addHistogram("ccscore_btagCSVV2", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_cTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagCSVV2()[0]; } return float(-10); } );
    hists_Common.addHistogram("uuscore_btagCSVV2", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_uTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagCSVV2()[0]; } return float(-10); } );
    hists_Common.addHistogram("ssscore_btagCSVV2", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_sTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagCSVV2()[0]; } return float(-10); } );


    hists_Common.addHistogram("bbscore_btagDeepB", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagDeepB()[0]; } return float(-10); } );
    hists_Common.addHistogram("ddscore_btagDeepB", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_dTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagDeepB()[0]; } return float(-10); } );
    hists_Common.addHistogram("ccscore_btagDeepB", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_cTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagDeepB()[0]; } return float(-10); } );
    hists_Common.addHistogram("uuscore_btagDeepB", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_uTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagDeepB()[0]; } return float(-10); } );
    hists_Common.addHistogram("ssscore_btagDeepB", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_sTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_btagDeepB()[0]; } return float(-10); } );


    hists_Common.addHistogram("bbscore_deepTagMD_ZbbvsQCD", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_ZbbvsQCD()[0]; } return float(-10); } );
    hists_Common.addHistogram("ddscore_deepTagMD_ZbbvsQCD", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_dTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_ZbbvsQCD()[0]; } return float(-10); } );
    hists_Common.addHistogram("ccscore_deepTagMD_ZbbvsQCD", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_cTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_ZbbvsQCD()[0]; } return float(-10); } );
    hists_Common.addHistogram("uuscore_deepTagMD_ZbbvsQCD", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_uTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_ZbbvsQCD()[0]; } return float(-10); } );
    hists_Common.addHistogram("ssscore_deepTagMD_ZbbvsQCD", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_sTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_ZbbvsQCD()[0]; } return float(-10); } );


    hists_Common.addHistogram("bbscore_deepTagMD_bbvsLight", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_bbvsLight()[0]; } return float(-10); } );
    hists_Common.addHistogram("ddscore_deepTagMD_bbvsLight", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_dTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_bbvsLight()[0]; } return float(-10); } );
    hists_Common.addHistogram("ccscore_deepTagMD_bbvsLight", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_cTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_bbvsLight()[0]; } return float(-10); } );
    hists_Common.addHistogram("uuscore_deepTagMD_bbvsLight", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_uTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_bbvsLight()[0]; } return float(-10); } );
    hists_Common.addHistogram("ssscore_deepTagMD_bbvsLight", 50, 0, 1, [&]() { if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_sTruth_p4").size() == 2 && ana.tx.getBranchLazy<vector<LorentzVector>>("Common_fatjet_p4").size() != 0){ return nt.FatJet_deepTagMD_bbvsLight()[0]; } return float(-10); } );
*/

//***************************************************************************************************//

/*
    hists_Common.addHistogram("Mass4b", 200, 50, 600, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 4)
        {
            LorentzVector b1, b2, b3, b4;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(1);
            b3 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(2);
            b4 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(3);
            return (b1 + b2 + b3 + b4).M();
        }
        return float(0); } );


    hists_Common.addHistogram("Massb1", 120, 0.1, 120, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 4)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0).M();
        return float(0); } );


    hists_Common.addHistogram("Massb2", 120, 0.1, 120, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 4)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(1).M();
        return float(0); } );


    hists_Common.addHistogram("Massb3", 120, 0.1, 120, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 4)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(2).M();
        return float(0); } );


    hists_Common.addHistogram("Massb4", 120, 0.1, 120, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 4)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(3).M();
        return float(0); } );


    hists_Common.addHistogram("JetpT_1", 500, 0, 500, [&]() { 
        if (ana.tx.getBranchLazy<vector<int>>("Common_jet_tightID").size() != 0) 
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0).Pt(); 
        return float(-1); } );


    hists_Common.addHistogram("JetpT_2", 500, 0, 500, [&]() { 
        if (ana.tx.getBranchLazy<vector<int>>("Common_jet_tightID").size() > 1) 
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(1).Pt(); 
        return float(-1);} );


    hists_Common.addHistogram("JetEta_1", 100, -3, 3, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_jet_tightID").size() != 0)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0).Eta();
        return float(-10); } );


    hists_Common.addHistogram("JetEta_2", 100, -3, 3, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_jet_tightID").size() > 1)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(1).Eta();
        return float(-10);} );


//b-tagging
    hists_Common.addHistogram("bJetpT_1", 500, 0, 500, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_bjet_tightID").size() != 0) 
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0).Pt();
        return float(-1); } );


    hists_Common.addHistogram("bJetpT_2", 500, 0, 500, [&]() { 
        if (ana.tx.getBranchLazy<vector<int>>("Common_bjet_tightID").size() > 1) 
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(1).Pt(); 
        return float(-1);} );


    hists_Common.addHistogram("bJetEta_1", 60, -3, 3, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_bjet_tightID").size() != 0)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(0).Eta();
        return float(-10); } );


    hists_Common.addHistogram("bJetEta_2", 60, -3, 3, [&]() {
        if (ana.tx.getBranchLazy<vector<int>>("Common_bjet_tightID").size() > 1)
            return ana.tx.getBranchLazy<vector<LorentzVector>>("Common_jet_tightp4").at(1).Eta();
        return float(-10);} );


    hists_Common.addHistogram("Z2bJetpT", 500, 0, 500, [&]() {
        if (ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").size() == 2)
        {   
            LorentzVector b1, b2;
            b1 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(0);
            b2 = ana.tx.getBranchLazy<vector<LorentzVector>>("Common_bjet_tightp4").at(1);
            return (b1 + b2).Pt();
        }
        return float(-1); } );
*/

     // Book histograms to cuts that user wants for this category.
    ana.cutflow.bookHistogramsForCut(hists_Common, "CommonCut");





    // EFT reweighting histogram
    RooUtil::Histograms n_lhe_weight;
    if (ana.is_EFT_sample)
    {
        n_lhe_weight.addVecHistogram("h_Common_LHEWeight_mg_reweighting", 60, 0, 60, [&]() { std::vector<float> rtn; for (unsigned int i = 0; i < nt.LHEWeight_mg_reweighting().size(); ++i) rtn.push_back(i); return rtn; }, [&]() { std::vector<float> rtn(nt.LHEWeight_mg_reweighting().begin(), nt.LHEWeight_mg_reweighting().end()); return rtn; } );
        n_lhe_weight.addVecHistogram("h_Common_LHEWeight_mg_reweighting_times_genWeight", 60, 0, 60, [&]() { std::vector<float> rtn; for (unsigned int i = 0; i < nt.LHEWeight_mg_reweighting().size(); ++i) rtn.push_back(i); return rtn; }, [&]() { std::vector<float> rtnx; for (unsigned int i = 0; i < nt.LHEWeight_mg_reweighting().size(); ++i) rtnx.push_back(nt.LHEWeight_mg_reweighting()[i]*nt.genWeight()); return rtnx; } );
    }
    if (not nt.isData())
    {
        n_lhe_weight.addVecHistogram("h_Common_genWeight", 1, 0, 1, [&]() { std::vector<float> rtn; rtn.push_back(0); return rtn; }, [&]() { std::vector<float> rtnx; rtnx.push_back(nt.genWeight()); return rtnx; } );
    }

    // Book the EFT reweighting histogram counter
    ana.cutflow.bookHistogramsForCut(n_lhe_weight, "Root");

}

void Begin_Common_Book_NEvent_Histograms()
{
    if (ana.input_file_list_tstring.Contains("NanoSkim") and not ana.input_file_list_tstring.Contains("_EFT_"))
    {
        ana.output_tfile->cd();
        TH1F* Root__h_nevents = new TH1F("Root__h_nevents", "Root__h_nevents", 1, 0, 1);
        TH1F* Wgt__h_nevents = new TH1F("Wgt__h_nevents", "Wgt__h_nevents", 1, 0, 1);

        TObjArray* input_files = ana.input_file_list_tstring.Tokenize(",");
        int total = 0;
        int pos_total = 0;
        int neg_total = 0;
        for (int ifile = 0; ifile < input_files->GetEntries(); ++ifile)
        {
            TString filepath = ((TObjString*)input_files->At(ifile))->GetString();
            TString nevents_file_path = filepath;
            nevents_file_path.ReplaceAll(".root", "_nevents.txt");

            if (gSystem->AccessPathName(nevents_file_path.Data()))
            {
                TFile* tmpfile = new TFile(filepath);
                TH1D* h_nevents = (TH1D*) tmpfile->Get("h_nevents");
                total += h_nevents->GetBinContent(1);
                pos_total += h_nevents->GetBinContent(2);
                neg_total += h_nevents->GetBinContent(3);
            }
            else
            {
                // Accessing n events
                std::ifstream ifs(nevents_file_path.Data());
                std::string content( (std::istreambuf_iterator<char>(ifs) ),
                                    (std::istreambuf_iterator<char>()    ) );
                TString content_tstr = content.c_str();
                TObjArray* lines = content_tstr.Tokenize("\n");
                int index_total = lines->GetEntries() - 3;
                int index_pos_total = lines->GetEntries() - 2;
                int index_neg_total = lines->GetEntries() - 1;
                total += ((TObjString*)lines->At(index_total))->GetString().Atoi();
                pos_total += ((TObjString*)lines->At(index_pos_total))->GetString().Atoi();
                neg_total += ((TObjString*)lines->At(index_neg_total))->GetString().Atoi();
            }
        }
        int eff_total = pos_total != neg_total ? pos_total - neg_total : pos_total;
        ana.output_tfile->cd();
        Root__h_nevents->SetBinContent(1, total);
        Wgt__h_nevents->SetBinContent(1, eff_total);
        Root__h_nevents->Write();
        Wgt__h_nevents->Write();
    }
    else
    {
        // Book histograms to Root to count total number of events processed
        RooUtil::Histograms n_event_hist;
        n_event_hist.addHistogram("h_nevents", 1, 0, 1, [&]() { return 0; } );

        // Book the counter histogram to the Root
        ana.cutflow.bookHistogramsForCut(n_event_hist, "Root");
        ana.cutflow.bookHistogramsForCut(n_event_hist, "Wgt");
    }
}
