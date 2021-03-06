

#include "FillTreeVariables.h"


FillTreeVariables::FillTreeVariables() :
  fmc(false),
  frmcm_bool(false),
  fwire_plane(2),
  fverbose(false),
  fvertex_tree(nullptr),
  fflash_start(3.2),
  fflash_end(4.8)
 {}


FillTreeVariables::~FillTreeVariables() {

  delete fvertex_tree;

}

void FillTreeVariables::SetFlashTimings(double flash_start, double flash_end){
	fflash_start = flash_start;
	fflash_end = flash_end;

}


void FillTreeVariables::SetProducers(Storage const * storage,
                                     std::string const & track_producer,
                                     std::string const & shower_producer,
                                     std::string const & hit_producer,
                                     std::string const & opflash_producer,
                                     std::string const & trigger_product) {

  fstorage = storage;
  ftpc_volume = geoalgo::AABox(0,
			       -fstorage->fDetHalfHeight,
			       0,
			       2*fstorage->fDetHalfWidth,
			       fstorage->fDetHalfHeight,
			       fstorage->fDetLength);
  foffset = 10;
  ffiducial_volume = geoalgo::AABox(foffset,
				    foffset-fstorage->fDetHalfHeight,
				    foffset,
				    -foffset+2*fstorage->fDetHalfWidth,
				    -foffset+fstorage->fDetHalfHeight,
				    -foffset+fstorage->fDetLength);

  fmc = fstorage->fmc;
  frmcm_bool = fstorage->frmcm_bool;
  ftrack_producer = track_producer;
  fshower_producer = shower_producer;
  fhit_producer = hit_producer;
  fopflash_producer = opflash_producer;
  fswtrigger_product = trigger_product;

}



void FillTreeVariables::SetupTreeBranches() {

  fvertex_tree = new TTree("vertex_tree", "");

  fvertex_tree->Branch("run_number", &run_number, "run_number/I");
  fvertex_tree->Branch("subrun_number", &subrun_number, "subrun_number/I"); 
  fvertex_tree->Branch("event_number", &event_number, "event_number/I");
  fvertex_tree->Branch("tracknumber", &tracknumber, "tracknumber/I");
  fvertex_tree->Branch("showernumber", &showernumber, "showernumber/I");

  fvertex_tree->Branch("passed_swtrigger", &passed_swtrigger, "passed_swtrigger/I");
  fvertex_tree->Branch("totalpe_sum", &totalpe_sum, "totalpe_sum/D");
  fvertex_tree->Branch("totalpe_ibg_sum", &totalpe_ibg_sum, "totalpe_ibg_sum/D");
  fvertex_tree->Branch("totalpe_bbg_sum", &totalpe_bbg_sum, "totalpe_bbg_sum/D");

  fvertex_tree->Branch("reco_nuvertx", &reco_nuvertx, "reco_nuvertx/D");
  fvertex_tree->Branch("reco_nuverty", &reco_nuverty, "reco_nuverty/D");
  fvertex_tree->Branch("reco_nuvertz", &reco_nuvertz, "reco_nuvertz/D");

  fvertex_tree->Branch("reco_nu_vtx_dist_to_closest_tpc_wall", &reco_nu_vtx_dist_to_closest_tpc_wall, "reco_nu_vtx_dist_to_closest_tpc_wall/D");

  fvertex_tree->Branch("reco_nu_vtx_fid_contained", &reco_nu_vtx_fid_contained, "reco_nu_vtx_fid_contained/I");

  fvertex_tree->Branch("reco_asso_tracks", &reco_asso_tracks, "reco_asso_tracks/I");
  fvertex_tree->Branch("reco_asso_showers", &reco_asso_showers, "reco_asso_showers/I");

  fvertex_tree->Branch("longest_asso_track_index", &longest_asso_track_index, "longest_asso_track_index/I");
  /*
  fvertex_tree->Branch("reco_track_displacement", &reco_track_length);
  fvertex_tree->Branch("reco_track_dirx", &reco_track_dirx);
  fvertex_tree->Branch("reco_track_diry", &reco_track_diry);
  fvertex_tree->Branch("reco_track_dirz", &reco_track_dirz);
  fvertex_tree->Branch("reco_track_thetayx", &reco_track_thetayx);
  fvertex_tree->Branch("reco_track_thetaxz", &reco_track_thetaxz);
  fvertex_tree->Branch("reco_track_thetayz", &reco_track_thetayz);
  fvertex_tree->Branch("reco_track_phi", &reco_track_phi);
  fvertex_tree->Branch("reco_track_theta", &reco_track_theta);
  */
  
  fvertex_tree->Branch("reco_track_displacement", &reco_track_length, "reco_track_displacement[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_energy", &reco_track_energy, "reco_track_energy[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_energy_new_legacy", &reco_track_energy_new_legacy, "reco_track_energy_new_legacy[reco_asso_tracks]/D");

  fvertex_tree->Branch("reco_track_is_flipped", &reco_track_is_flipped, "reco_track_is_flipped[reco_asso_tracks]/I");
  fvertex_tree->Branch("reco_track_startx", &reco_track_startx, "reco_track_startx[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_starty", &reco_track_starty, "reco_track_starty[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_startz", &reco_track_startz, "reco_track_startz[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_endx", &reco_track_endx, "reco_track_endx[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_endy", &reco_track_endy, "reco_track_endy[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_endz", &reco_track_endz, "reco_track_endz[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_dirx", &reco_track_dirx, "reco_track_dirx[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_diry", &reco_track_diry, "reco_track_diry[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_dirz", &reco_track_dirz, "reco_track_dirz[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_vertdirx", &reco_track_vertdirx, "reco_track_vertdirx[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_vertdiry", &reco_track_vertdiry, "reco_track_vertdiry[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_vertdirz", &reco_track_vertdirz, "reco_track_vertdirz[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_thetayx", &reco_track_thetayx, "reco_track_thetayx[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_thetaxz", &reco_track_thetaxz, "reco_track_thetaxz[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_thetayz", &reco_track_thetayz, "reco_track_thetayz[reco_asso_tracks]/D");
  //fvertex_tree->Branch("reco_track_phi", &reco_track_phi, "reco_track_phi[reco_asso_tracks]/D");
  //fvertex_tree->Branch("reco_track_theta", &reco_track_theta, "reco_track_theta[reco_asso_tracks]/D");
  fvertex_tree->Branch("reco_track_calo_dEdx", &reco_track_calo_dEdx);
  fvertex_tree->Branch("reco_track_calo_dEdxnew", &reco_track_calo_dEdxnew);
  fvertex_tree->Branch("reco_track_calo_resrange", &reco_track_calo_resrange);
  
  fvertex_tree->Branch("reco_track_X", &reco_track_X);
  fvertex_tree->Branch("reco_track_Y", &reco_track_Y);
  fvertex_tree->Branch("reco_track_Z", &reco_track_Z);

  fvertex_tree->Branch("reco_track_energy_new", &reco_track_energy_new);
  fvertex_tree->Branch("reco_track_energy_from_dEdx", &reco_track_energy_from_dEdx);

  fvertex_tree->Branch("all_reco_tracks_dist_from_vertex", &all_reco_tracks_dist_from_vertex);
  fvertex_tree->Branch("all_reco_showers_dist_from_vertex", &all_reco_showers_dist_from_vertex);

  fvertex_tree->Branch("all_reco_tracks_bp_dist_from_vertex", &all_reco_tracks_bp_dist_from_vertex);
  fvertex_tree->Branch("all_reco_showers_bp_dist_from_vertex", &all_reco_showers_bp_dist_from_vertex);

  fvertex_tree->Branch("closest_asso_shower_dist_to_flashzcenter", &closest_asso_shower_dist_to_flashzcenter, "closest_asso_shower_dist_to_flashzcenter/D");

  fvertex_tree->Branch("most_energetic_shower_index", &most_energetic_shower_index);
  fvertex_tree->Branch("second_most_energetic_shower_index", &second_most_energetic_shower_index);
  /*
  fvertex_tree->Branch("reco_shower_startx", &reco_shower_startx);
  fvertex_tree->Branch("reco_shower_starty", &reco_shower_starty);
  fvertex_tree->Branch("reco_shower_startz", &reco_shower_startz);
  fvertex_tree->Branch("reco_shower_dist", &reco_shower_dist);
  fvertex_tree->Branch("reco_shower_distx", &reco_shower_distx);
  fvertex_tree->Branch("reco_shower_disty", &reco_shower_disty);
  fvertex_tree->Branch("reco_shower_distz", &reco_shower_distz);
  fvertex_tree->Branch("reco_shower_thetayx", &reco_shower_thetayx);
  fvertex_tree->Branch("reco_shower_thetaxz", &reco_shower_thetaxz);
  fvertex_tree->Branch("reco_shower_thetayz", &reco_shower_thetayz);
  //fvertex_tree->Branch("reco_shower_width0", &reco_shower_width0);
  //fvertex_tree->Branch("reco_shower_width1", &reco_shower_width1);
  fvertex_tree->Branch("reco_shower_opening_angle", &reco_shower_opening_angle);
  fvertex_tree->Branch("reco_shower_length", &reco_shower_length);
  fvertex_tree->Branch("reco_shower_dirx", &reco_shower_dirx);
  fvertex_tree->Branch("reco_shower_diry", &reco_shower_diry);
  fvertex_tree->Branch("reco_shower_dirz", &reco_shower_dirz);
  fvertex_tree->Branch("reco_shower_helper_energy", &reco_shower_helper_energy);
  fvertex_tree->Branch("reco_shower_bp_dist_to_tpc", &reco_shower_bp_dist_to_tpc);
  fvertex_tree->Branch("reco_shower_dedx_plane0", &reco_shower_dedx_plane0);
  fvertex_tree->Branch("reco_shower_dedx_plane1", &reco_shower_dedx_plane1);
  fvertex_tree->Branch("reco_shower_dedx_plane2", &reco_shower_dedx_plane2);
  fvertex_tree->Branch("reco_shower_dist_to_closest_flashzcenter", &reco_shower_dist_to_closest_flashzcenter);
  */
  fvertex_tree->Branch("reco_shower_startx", &reco_shower_startx, "reco_shower_startx[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_starty", &reco_shower_starty, "reco_shower_starty[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_startz", &reco_shower_startz, "reco_shower_startz[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_endx", &reco_shower_endx, "reco_shower_endx[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_endy", &reco_shower_endy, "reco_shower_endy[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_endz", &reco_shower_endz, "reco_shower_endz[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dist", &reco_shower_dist, "reco_shower_dist[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_distx", &reco_shower_distx, "reco_shower_distx[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_disty", &reco_shower_disty, "reco_shower_disty[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_distz", &reco_shower_distz, "reco_shower_distz[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_thetayx", &reco_shower_thetayx, "reco_shower_thetayx[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_thetaxz", &reco_shower_thetaxz, "reco_shower_thetaxz[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_thetayz", &reco_shower_thetayz, "reco_shower_thetayz[reco_asso_showers]/D");
  //fvertex_tree->Branch("reco_shower_width0", &reco_shower_width0, "reco_shower_width0[reco_asso_showers]/D");
  //fvertex_tree->Branch("reco_shower_width1", &reco_shower_width1, "reco_shower_width1[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_opening_angle", &reco_shower_opening_angle, "reco_shower_opening_angle[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_length", &reco_shower_length, "reco_shower_length[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dirx", &reco_shower_dirx, "reco_shower_dirx[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_diry", &reco_shower_diry, "reco_shower_diry[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dirz", &reco_shower_dirz, "reco_shower_dirz[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_helper_energy", &reco_shower_helper_energy, "reco_shower_helper_energy[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_helpernew_energy", &reco_shower_helpernew_energy, "reco_shower_helpernew_energy[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_bp_dist_to_tpc", &reco_shower_bp_dist_to_tpc, "reco_shower_bp_dist_to_tpc[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dedx_plane0", &reco_shower_dedx_plane0, "reco_shower_dedx_plane0[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dedx_plane1", &reco_shower_dedx_plane1, "reco_shower_dedx_plane1[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dedx_plane2", &reco_shower_dedx_plane2, "reco_shower_dedx_plane2[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dedxnew_plane0", &reco_shower_dedxnew_plane0, "reco_shower_dedxnew_plane0[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dedxnew_plane1", &reco_shower_dedxnew_plane1, "reco_shower_dedxnew_plane1[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dedxnew_plane2", &reco_shower_dedxnew_plane2, "reco_shower_dedxnew_plane2[reco_asso_showers]/D");
  fvertex_tree->Branch("reco_shower_dist_to_closest_flashzcenter", &reco_shower_dist_to_closest_flashzcenter, "reco_shower_dist_to_closest_flashzcenter[reco_asso_showers]/D");

  fvertex_tree->Branch("shortest_asso_shower_to_vert_dist", &shortest_asso_shower_to_vert_dist, "shortest_asso_shower_to_vert_dist/D");
  fvertex_tree->Branch("summed_associated_helper_shower_energy", &summed_associated_helper_shower_energy, "summed_associated_helper_shower_energy/D");

  if(fmc) {

    fvertex_tree->Branch("nu_pdg", &nu_pdg, "nu_pdg/I");
    fvertex_tree->Branch("nu_energy", &nu_energy, "nu_energy/D");
    fvertex_tree->Branch("lep_pdg", &lep_pdg, "lep_pdg/I");
    fvertex_tree->Branch("lep_energy", &lep_energy, "lep_energy/D");
    fvertex_tree->Branch("ccnc", &ccnc, "ccnc/I");
    fvertex_tree->Branch("mode", &mode, "mode/I");
    fvertex_tree->Branch("interaction_type", &interaction_type, "interaction_type/I");

    fvertex_tree->Branch("exiting_photon_number", &exiting_photon_number, "exiting_photon_number/I");
    fvertex_tree->Branch("exiting_proton_number", &exiting_proton_number, "exiting_proton_number/I");
    fvertex_tree->Branch("exiting_neutron_number", &exiting_neutron_number, "exiting_neutron_number/I");
    fvertex_tree->Branch("exiting_electron_number", &exiting_electron_number, "exiting_electron_number/I");
    fvertex_tree->Branch("exiting_antielectron_number", &exiting_antielectron_number, "exiting_antielectron_number/I");
    fvertex_tree->Branch("exiting_muon_number", &exiting_muon_number, "exiting_muon_number/I");
    fvertex_tree->Branch("exiting_antimuon_number", &exiting_antimuon_number, "exiting_antimuon_number/I");
    fvertex_tree->Branch("exiting_piplus_number", &exiting_piplus_number, "exiting_piplus_number/I");
    fvertex_tree->Branch("exiting_piminus_number", &exiting_piminus_number, "exiting_piminus_number/I");
    fvertex_tree->Branch("exiting_pi0_number", &exiting_pi0_number, "exiting_pi0_number/I");
    fvertex_tree->Branch("exiting_pi0_px", &exiting_pi0_px);
    fvertex_tree->Branch("exiting_pi0_py", &exiting_pi0_py);
    fvertex_tree->Branch("exiting_pi0_pz", &exiting_pi0_pz);
    fvertex_tree->Branch("total_exiting_particles", &total_exiting_particles, "total_exiting_particles/I"); 
    fvertex_tree->Branch("exiting_particle_vector", &exiting_particle_vector);

    fvertex_tree->Branch("is_single_photon", &is_single_photon, "is_single_photon/I");
    fvertex_tree->Branch("is_delta_rad", &is_delta_rad, "is_delta_rad/I");
    fvertex_tree->Branch("delta_true_pdg", &delta_true_pdg, "delta_true_pdg/I");
    fvertex_tree->Branch("delta_true_energy", &delta_true_energy, "delta_true_energy/D");
    fvertex_tree->Branch("delta_photon_energy", &delta_photon_energy, "delta_photon_energy/D");
    fvertex_tree->Branch("delta_proton_energy", &delta_proton_energy, "delta_proton_energy/D");
    fvertex_tree->Branch("delta_mcshower_true_pdg", &delta_mcshower_true_pdg, "delta_mcshower_true_pdg/I");
    fvertex_tree->Branch("delta_mcshower_true_energy", &delta_mcshower_true_energy, "delta_mcshower_true_energy/D");
    fvertex_tree->Branch("delta_mcshower_detprofile_energy", &delta_mcshower_detprofile_energy, "delta_mcshower_detprofile_energy/D");
    fvertex_tree->Branch("delta_mctrack_true_pdg", &delta_mctrack_true_pdg, "delta_mctrack_true_pdg/I");
    fvertex_tree->Branch("delta_mctrack_true_energy", &delta_mctrack_true_energy, "delta_mctrack_true_energy/D");
    fvertex_tree->Branch("delta_mctrack_true_length", &delta_mctrack_true_length, "delta_mctrack_true_length/D");    

    fvertex_tree->Branch("pi0_class_number", &pi0_class_number, "pi0_class_number/I");    

    fvertex_tree->Branch("mctracknumber", &mctracknumber, "mctracknumber/I");
    fvertex_tree->Branch("mcshowernumber", &mcshowernumber, "mcshowernumber/I");

    fvertex_tree->Branch("true_nuvertx", &true_nuvertx, "true_nuvertx/D");
    fvertex_tree->Branch("true_nuverty", &true_nuverty, "true_nuverty/D");
    fvertex_tree->Branch("true_nuvertz", &true_nuvertz, "true_nuvertz/D");    

    fvertex_tree->Branch("true_nu_E", &true_nu_E, "true_nu_E/D");

    fvertex_tree->Branch("reco_true_nuvert_dist", &reco_true_nuvert_dist, "reco_true_nuvert_dist/D");    
    fvertex_tree->Branch("reco_true_nuvert_distx", &reco_true_nuvert_distx, "reco_true_nuvert_distx/D");    
    fvertex_tree->Branch("reco_true_nuvert_disty", &reco_true_nuvert_disty, "reco_true_nuvert_disty/D");    
    fvertex_tree->Branch("reco_true_nuvert_distz", &reco_true_nuvert_distz, "reco_true_nuvert_distz/D");    

    fvertex_tree->Branch("true_nu_vtx_tpc_contained", &true_nu_vtx_tpc_contained, "true_nu_vtx_tpc_contained/I"); 
    fvertex_tree->Branch("true_nu_vtx_fid_contained", &true_nu_vtx_fid_contained, "true_nu_vtx_fid_contained/I"); 

    fvertex_tree->Branch("true_track_matching_ratio", &true_track_matching_ratio);
    fvertex_tree->Branch("true_track_index", &true_track_index);
    fvertex_tree->Branch("true_track_matched_to", &true_track_matched_to);
    fvertex_tree->Branch("true_track_pdg", &true_track_pdg);
    fvertex_tree->Branch("true_track_parent_pdg", &true_track_parent_pdg);
    fvertex_tree->Branch("true_track_ancestor_pdg", &true_track_ancestor_pdg);
    fvertex_tree->Branch("true_track_origin", &true_track_origin);
    fvertex_tree->Branch("true_track_startx", &true_track_startx); 
    fvertex_tree->Branch("true_track_starty", &true_track_starty); 
    fvertex_tree->Branch("true_track_startz", &true_track_startz);    
    fvertex_tree->Branch("true_track_endx", &true_track_endx); 
    fvertex_tree->Branch("true_track_endy", &true_track_endy); 
    fvertex_tree->Branch("true_track_endz", &true_track_endz);    
    fvertex_tree->Branch("track_matched_to_ncdeltarad_photon", &track_matched_to_ncdeltarad_photon);
    fvertex_tree->Branch("track_matched_to_ncdeltarad_proton", &track_matched_to_ncdeltarad_proton);
    fvertex_tree->Branch("true_track_energy", &true_track_energy);

    fvertex_tree->Branch("true_shower_matching_ratio", &true_shower_matching_ratio);
    fvertex_tree->Branch("true_shower_index", &true_shower_index);
    fvertex_tree->Branch("true_shower_matched_to", &true_shower_matched_to);
    fvertex_tree->Branch("true_shower_pdg", &true_shower_pdg);
    fvertex_tree->Branch("true_shower_parent_pdg", &true_shower_parent_pdg);
    fvertex_tree->Branch("true_shower_ancestor_pdg", &true_shower_ancestor_pdg);
    fvertex_tree->Branch("true_shower_origin", &true_shower_origin);
    fvertex_tree->Branch("true_shower_startx", &true_shower_startx); 
    fvertex_tree->Branch("true_shower_starty", &true_shower_starty); 
    fvertex_tree->Branch("true_shower_startz", &true_shower_startz);    
    fvertex_tree->Branch("true_shower_endx", &true_shower_endx); 
    fvertex_tree->Branch("true_shower_endy", &true_shower_endy); 
    fvertex_tree->Branch("true_shower_endz", &true_shower_endz);    
    fvertex_tree->Branch("shower_matched_to_ncdeltarad_photon", &shower_matched_to_ncdeltarad_photon);
    fvertex_tree->Branch("shower_matched_to_ncdeltarad_proton", &shower_matched_to_ncdeltarad_proton);
    fvertex_tree->Branch("true_shower_energy", &true_shower_energy);
    fvertex_tree->Branch("true_shower_detprofile_energy", &true_shower_detprofile_energy);

    fvertex_tree->Branch("fweight_genie_ncelaxial_p1sigma", &fweight_genie_ncelaxial_p1sigma, "fweight_genie_ncelaxial_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_ncelaxial_m1sigma", &fweight_genie_ncelaxial_m1sigma, "fweight_genie_ncelaxial_m1sigma/D");
    weight_branch_map.emplace("genie_NCELaxial_Genie", std::vector<double *>{&fweight_genie_ncelaxial_p1sigma, &fweight_genie_ncelaxial_m1sigma});

    fvertex_tree->Branch("fweight_genie_nceleta_p1sigma", &fweight_genie_nceleta_p1sigma, "fweight_genie_nceleta_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_nceleta_m1sigma", &fweight_genie_nceleta_m1sigma, "fweight_genie_nceleta_m1sigma/D");
    weight_branch_map.emplace("genie_NCELeta_Genie", std::vector<double *>{&fweight_genie_nceleta_p1sigma, &fweight_genie_nceleta_m1sigma});

    fvertex_tree->Branch("fweight_genie_qema_p1sigma", &fweight_genie_qema_p1sigma, "fweight_genie_qema_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_qema_m1sigma", &fweight_genie_qema_m1sigma, "fweight_genie_qema_m1sigma/D");
    weight_branch_map.emplace("genie_QEMA_Genie", std::vector<double *>{&fweight_genie_qema_p1sigma, &fweight_genie_qema_m1sigma});

    fvertex_tree->Branch("fweight_genie_qevec_p1sigma", &fweight_genie_qevec_p1sigma, "fweight_genie_qevec_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_qevec_m1sigma", &fweight_genie_qevec_m1sigma, "fweight_genie_qevec_m1sigma/D");
    weight_branch_map.emplace("genie_QEVec_Genie", std::vector<double *>{&fweight_genie_qevec_p1sigma, &fweight_genie_qevec_m1sigma});

    fvertex_tree->Branch("fweight_genie_ccresaxial_p1sigma", &fweight_genie_ccresaxial_p1sigma, "fweight_genie_ccresaxial_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_ccresaxial_m1sigma", &fweight_genie_ccresaxial_m1sigma, "fweight_genie_ccresaxial_m1sigma/D");
    weight_branch_map.emplace("genie_CCResAxial_Genie", std::vector<double *>{&fweight_genie_ccresaxial_p1sigma, &fweight_genie_ccresaxial_m1sigma});

    fvertex_tree->Branch("fweight_genie_ccresvector_p1sigma", &fweight_genie_ccresvector_p1sigma, "fweight_genie_ccresvector_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_ccresvector_m1sigma", &fweight_genie_ccresvector_m1sigma, "fweight_genie_ccresvector_m1sigma/D");
    weight_branch_map.emplace("genie_CCResVector_Genie", std::vector<double *>{&fweight_genie_ccresvector_p1sigma, &fweight_genie_ccresvector_m1sigma});

    fvertex_tree->Branch("fweight_genie_resganged_p1sigma", &fweight_genie_resganged_p1sigma, "fweight_genie_resganged_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_resganged_m1sigma", &fweight_genie_resganged_m1sigma, "fweight_genie_resganged_m1sigma/D");
    weight_branch_map.emplace("genie_ResGanged_Genie", std::vector<double *>{&fweight_genie_resganged_p1sigma, &fweight_genie_resganged_m1sigma});

    fvertex_tree->Branch("fweight_genie_ncresaxial_p1sigma", &fweight_genie_ncresaxial_p1sigma, "fweight_genie_ncresaxial_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_ncresaxial_m1sigma", &fweight_genie_ncresaxial_m1sigma, "fweight_genie_ncresaxial_m1sigma/D");
    weight_branch_map.emplace("genie_NCResAxial_Genie", std::vector<double *>{&fweight_genie_ncresaxial_p1sigma, &fweight_genie_ncresaxial_m1sigma});

    fvertex_tree->Branch("fweight_genie_ncresvector_p1sigma", &fweight_genie_ncresvector_p1sigma, "fweight_genie_ncresvector_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_ncresvector_m1sigma", &fweight_genie_ncresvector_m1sigma, "fweight_genie_ncresvector_m1sigma/D");
    weight_branch_map.emplace("genie_NCResVector_Genie", std::vector<double *>{&fweight_genie_ncresvector_p1sigma, &fweight_genie_ncresvector_m1sigma});

    fvertex_tree->Branch("fweight_genie_cohma_p1sigma", &fweight_genie_cohma_p1sigma, "fweight_genie_cohma_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_cohma_m1sigma", &fweight_genie_cohma_m1sigma, "fweight_genie_cohma_m1sigma/D");
    weight_branch_map.emplace("genie_CohMA_Genie", std::vector<double *>{&fweight_genie_cohma_p1sigma, &fweight_genie_cohma_m1sigma});

    fvertex_tree->Branch("fweight_genie_cohr0_p1sigma", &fweight_genie_cohr0_p1sigma, "fweight_genie_cohr0_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_cohr0_m1sigma", &fweight_genie_cohr0_m1sigma, "fweight_genie_cohr0_m1sigma/D");
    weight_branch_map.emplace("genie_CohR0_Genie", std::vector<double *>{&fweight_genie_cohr0_p1sigma, &fweight_genie_cohr0_m1sigma});

    fvertex_tree->Branch("fweight_genie_nonresrvp1pi_p1sigma", &fweight_genie_nonresrvp1pi_p1sigma, "fweight_genie_nonresrvp1pi_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_nonresrvp1pi_m1sigma", &fweight_genie_nonresrvp1pi_m1sigma, "fweight_genie_nonresrvp1pi_m1sigma/D");
    weight_branch_map.emplace("genie_NonResRvp1pi_Genie", std::vector<double *>{&fweight_genie_nonresrvp1pi_p1sigma, &fweight_genie_nonresrvp1pi_m1sigma});

    fvertex_tree->Branch("fweight_genie_nonresrvbarp1pi_p1sigma", &fweight_genie_nonresrvbarp1pi_p1sigma, "fweight_genie_nonresrvbarp1pi_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_nonresrvbarp1pi_m1sigma", &fweight_genie_nonresrvbarp1pi_m1sigma, "fweight_genie_nonresrvbarp1pi_m1sigma/D");
    weight_branch_map.emplace("genie_NonResRvbarp1pi_Genie", std::vector<double *>{&fweight_genie_nonresrvbarp1pi_p1sigma, &fweight_genie_nonresrvbarp1pi_m1sigma});

    fvertex_tree->Branch("fweight_genie_nonresrvp2pi_p1sigma", &fweight_genie_nonresrvp2pi_p1sigma, "fweight_genie_nonresrvp2pi_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_nonresrvp2pi_m1sigma", &fweight_genie_nonresrvp2pi_m1sigma, "fweight_genie_nonresrvp2pi_m1sigma/D");
    weight_branch_map.emplace("genie_NonResRvp2pi_Genie", std::vector<double *>{&fweight_genie_nonresrvp2pi_p1sigma, &fweight_genie_nonresrvp2pi_m1sigma});

    fvertex_tree->Branch("fweight_genie_nonresrvbarp2pi_p1sigma", &fweight_genie_nonresrvbarp2pi_p1sigma, "fweight_genie_nonresrvbarp2pi_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_nonresrvbarp2pi_m1sigma", &fweight_genie_nonresrvbarp2pi_m1sigma, "fweight_genie_nonresrvbarp2pi_m1sigma/D");
    weight_branch_map.emplace("genie_NonResRvbarp2pi_Genie", std::vector<double *>{&fweight_genie_nonresrvbarp2pi_p1sigma, &fweight_genie_nonresrvbarp2pi_m1sigma});

    fvertex_tree->Branch("fweight_genie_resdecaygamma_p1sigma", &fweight_genie_resdecaygamma_p1sigma, "fweight_genie_resdecaygamma_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_resdecaygamma_m1sigma", &fweight_genie_resdecaygamma_m1sigma, "fweight_genie_resdecaygamma_m1sigma/D");
    weight_branch_map.emplace("genie_ResDecayGamma_Genie", std::vector<double *>{&fweight_genie_resdecaygamma_p1sigma, &fweight_genie_resdecaygamma_m1sigma});

    fvertex_tree->Branch("fweight_genie_resdecayeta_p1sigma", &fweight_genie_resdecayeta_p1sigma, "fweight_genie_resdecayeta_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_resdecayeta_m1sigma", &fweight_genie_resdecayeta_m1sigma, "fweight_genie_resdecayeta_m1sigma/D");
    weight_branch_map.emplace("genie_ResDecayEta_Genie", std::vector<double *>{&fweight_genie_resdecayeta_p1sigma, &fweight_genie_resdecayeta_m1sigma});

    fvertex_tree->Branch("fweight_genie_resdecaytheta_p1sigma", &fweight_genie_resdecaytheta_p1sigma, "fweight_genie_resdecaytheta_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_resdecaytheta_m1sigma", &fweight_genie_resdecaytheta_m1sigma, "fweight_genie_resdecaytheta_m1sigma/D");
    weight_branch_map.emplace("genie_ResDecayTheta_Genie", std::vector<double *>{&fweight_genie_resdecaytheta_p1sigma, &fweight_genie_resdecaytheta_m1sigma});

    fvertex_tree->Branch("fweight_genie_nc_p1sigma", &fweight_genie_nc_p1sigma, "fweight_genie_nc_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_nc_m1sigma", &fweight_genie_nc_m1sigma, "fweight_genie_nc_m1sigma/D");
    weight_branch_map.emplace("genie_NC_Genie", std::vector<double *>{&fweight_genie_nc_p1sigma, &fweight_genie_nc_m1sigma});

    fvertex_tree->Branch("fweight_genie_disath_p1sigma", &fweight_genie_disath_p1sigma, "fweight_genie_disath_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_disath_m1sigma", &fweight_genie_disath_m1sigma, "fweight_genie_disath_m1sigma/D");
    weight_branch_map.emplace("genie_DISAth_Genie", std::vector<double *>{&fweight_genie_disath_p1sigma, &fweight_genie_disath_m1sigma});

    fvertex_tree->Branch("fweight_genie_disbth_p1sigma", &fweight_genie_disbth_p1sigma, "fweight_genie_disbth_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_disbth_m1sigma", &fweight_genie_disbth_m1sigma, "fweight_genie_disbth_m1sigma/D");
    weight_branch_map.emplace("genie_DISBth_Genie", std::vector<double *>{&fweight_genie_disbth_p1sigma, &fweight_genie_disbth_m1sigma});

    fvertex_tree->Branch("fweight_genie_discv1u_p1sigma", &fweight_genie_discv1u_p1sigma, "fweight_genie_discv1u_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_discv1u_m1sigma", &fweight_genie_discv1u_m1sigma, "fweight_genie_discv1u_m1sigma/D");
    weight_branch_map.emplace("genie_DISCv1u_Genie", std::vector<double *>{&fweight_genie_discv1u_p1sigma, &fweight_genie_discv1u_m1sigma});

    fvertex_tree->Branch("fweight_genie_discv2u_p1sigma", &fweight_genie_discv2u_p1sigma, "fweight_genie_discv2u_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_discv2u_m1sigma", &fweight_genie_discv2u_m1sigma, "fweight_genie_discv2u_m1sigma/D");
    weight_branch_map.emplace("genie_DISCv2u_Genie", std::vector<double *>{&fweight_genie_discv2u_p1sigma, &fweight_genie_discv2u_m1sigma});

    fvertex_tree->Branch("fweight_genie_disnucl_p1sigma", &fweight_genie_disnucl_p1sigma, "fweight_genie_disnucl_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_disnucl_m1sigma", &fweight_genie_disnucl_m1sigma, "fweight_genie_disnucl_m1sigma/D");
    weight_branch_map.emplace("genie_DISnucl_Genie", std::vector<double *>{&fweight_genie_disnucl_p1sigma, &fweight_genie_disnucl_m1sigma});

    fvertex_tree->Branch("fweight_genie_agkyxf_p1sigma", &fweight_genie_agkyxf_p1sigma, "fweight_genie_agkyxf_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_agkyxf_m1sigma", &fweight_genie_agkyxf_m1sigma, "fweight_genie_agkyxf_m1sigma/D");
    weight_branch_map.emplace("genie_AGKYxF_Genie", std::vector<double *>{&fweight_genie_agkyxf_p1sigma, &fweight_genie_agkyxf_m1sigma});

    fvertex_tree->Branch("fweight_genie_agkypt_p1sigma", &fweight_genie_agkypt_p1sigma, "fweight_genie_agkypt_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_agkypt_m1sigma", &fweight_genie_agkypt_m1sigma, "fweight_genie_agkypt_m1sigma/D");
    weight_branch_map.emplace("genie_AGKYpT_Genie", std::vector<double *>{&fweight_genie_agkypt_p1sigma, &fweight_genie_agkypt_m1sigma});

    fvertex_tree->Branch("fweight_genie_formzone_p1sigma", &fweight_genie_formzone_p1sigma, "fweight_genie_formzone_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_formzone_m1sigma", &fweight_genie_formzone_m1sigma, "fweight_genie_formzone_m1sigma/D");
    weight_branch_map.emplace("genie_FormZone_Genie", std::vector<double *>{&fweight_genie_formzone_p1sigma, &fweight_genie_formzone_m1sigma});

    fvertex_tree->Branch("fweight_genie_fermigasmodelkf_p1sigma", &fweight_genie_fermigasmodelkf_p1sigma, "fweight_genie_fermigasmodelkf_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_fermigasmodelkf_m1sigma", &fweight_genie_fermigasmodelkf_m1sigma, "fweight_genie_fermigasmodelkf_m1sigma/D");
    weight_branch_map.emplace("genie_FermiGasModelKf_Genie", std::vector<double *>{&fweight_genie_fermigasmodelkf_p1sigma, &fweight_genie_fermigasmodelkf_m1sigma});

    fvertex_tree->Branch("fweight_genie_fermigasmodelsf_p1sigma", &fweight_genie_fermigasmodelsf_p1sigma, "fweight_genie_fermigasmodelsf_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_fermigasmodelsf_m1sigma", &fweight_genie_fermigasmodelsf_m1sigma, "fweight_genie_fermigasmodelsf_m1sigma/D");
    weight_branch_map.emplace("genie_FermiGasModelSf_Genie", std::vector<double *>{&fweight_genie_fermigasmodelsf_p1sigma, &fweight_genie_fermigasmodelsf_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukenmfp_p1sigma", &fweight_genie_intranukenmfp_p1sigma, "fweight_genie_intranukenmfp_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukenmfp_m1sigma", &fweight_genie_intranukenmfp_m1sigma, "fweight_genie_intranukenmfp_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukeNmfp_Genie", std::vector<double *>{&fweight_genie_intranukenmfp_p1sigma, &fweight_genie_intranukenmfp_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukencex_p1sigma", &fweight_genie_intranukencex_p1sigma, "fweight_genie_intranukencex_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukencex_m1sigma", &fweight_genie_intranukencex_m1sigma, "fweight_genie_intranukencex_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukeNcex_Genie", std::vector<double *>{&fweight_genie_intranukencex_p1sigma, &fweight_genie_intranukencex_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukenel_p1sigma", &fweight_genie_intranukenel_p1sigma, "fweight_genie_intranukenel_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukenel_m1sigma", &fweight_genie_intranukenel_m1sigma, "fweight_genie_intranukenel_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukeNel_Genie", std::vector<double *>{&fweight_genie_intranukenel_p1sigma, &fweight_genie_intranukenel_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukeninel_p1sigma", &fweight_genie_intranukeninel_p1sigma, "fweight_genie_intranukeninel_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukeninel_m1sigma", &fweight_genie_intranukeninel_m1sigma, "fweight_genie_intranukeninel_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukeNinel_Genie", std::vector<double *>{&fweight_genie_intranukeninel_p1sigma, &fweight_genie_intranukeninel_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukenabs_p1sigma", &fweight_genie_intranukenabs_p1sigma, "fweight_genie_intranukenabs_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukenabs_m1sigma", &fweight_genie_intranukenabs_m1sigma, "fweight_genie_intranukenabs_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukeNabs_Genie", std::vector<double *>{&fweight_genie_intranukenabs_p1sigma, &fweight_genie_intranukenabs_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukenpi_p1sigma", &fweight_genie_intranukenpi_p1sigma, "fweight_genie_intranukenpi_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukenpi_m1sigma", &fweight_genie_intranukenpi_m1sigma, "fweight_genie_intranukenpi_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukeNpi_Genie", std::vector<double *>{&fweight_genie_intranukenpi_p1sigma, &fweight_genie_intranukenpi_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukepimfp_p1sigma", &fweight_genie_intranukepimfp_p1sigma, "fweight_genie_intranukepimfp_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukepimfp_m1sigma", &fweight_genie_intranukepimfp_m1sigma, "fweight_genie_intranukepimfp_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukePImfp_Genie", std::vector<double *>{&fweight_genie_intranukepimfp_p1sigma, &fweight_genie_intranukepimfp_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukepicex_p1sigma", &fweight_genie_intranukepicex_p1sigma, "fweight_genie_intranukepicex_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukepicex_m1sigma", &fweight_genie_intranukepicex_m1sigma, "fweight_genie_intranukepicex_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukePIcex_Genie", std::vector<double *>{&fweight_genie_intranukepicex_p1sigma, &fweight_genie_intranukepicex_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukepiel_p1sigma", &fweight_genie_intranukepiel_p1sigma, "fweight_genie_intranukepiel_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukepiel_m1sigma", &fweight_genie_intranukepiel_m1sigma, "fweight_genie_intranukepiel_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukePIel_Genie", std::vector<double *>{&fweight_genie_intranukepiel_p1sigma, &fweight_genie_intranukepiel_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukepiinel_p1sigma", &fweight_genie_intranukepiinel_p1sigma, "fweight_genie_intranukepiinel_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukepiinel_m1sigma", &fweight_genie_intranukepiinel_m1sigma, "fweight_genie_intranukepiinel_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukePIinel_Genie", std::vector<double *>{&fweight_genie_intranukepiinel_p1sigma, &fweight_genie_intranukepiinel_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukepiabs_p1sigma", &fweight_genie_intranukepiabs_p1sigma, "fweight_genie_intranukepiabs_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukepiabs_m1sigma", &fweight_genie_intranukepiabs_m1sigma, "fweight_genie_intranukepiabs_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukePIabs_Genie", std::vector<double *>{&fweight_genie_intranukepiabs_p1sigma, &fweight_genie_intranukepiabs_m1sigma});

    fvertex_tree->Branch("fweight_genie_intranukepipi_p1sigma", &fweight_genie_intranukepipi_p1sigma, "fweight_genie_intranukepipi_p1sigma/D");
    fvertex_tree->Branch("fweight_genie_intranukepipi_m1sigma", &fweight_genie_intranukepipi_m1sigma, "fweight_genie_intranukepipi_m1sigma/D");
    weight_branch_map.emplace("genie_IntraNukePIpi_Genie", std::vector<double *>{&fweight_genie_intranukepipi_p1sigma, &fweight_genie_intranukepipi_m1sigma});

  }      

}


void FillTreeVariables::ResetEvent() {

  run_number = -1;
  subrun_number = -1;
  event_number = -1;
  nu_pdg = 0;
  nu_energy = -1;
  lep_pdg = -1;
  lep_energy = 0;
  ccnc = -1;
  mode = -1;
  interaction_type = -1;

  exiting_photon_number = 0;
  exiting_proton_number = 0;
  exiting_neutron_number = 0;
  exiting_electron_number = 0;
  exiting_antielectron_number = 0;
  exiting_muon_number = 0;
  exiting_antimuon_number = 0;
  exiting_piplus_number = 0;
  exiting_piminus_number = 0;
  exiting_pi0_number = 0;
  exiting_pi0_px.clear();
  exiting_pi0_py.clear();
  exiting_pi0_pz.clear();
  total_exiting_particles = 0;
  exiting_particle_vector.clear();

  is_single_photon = -1;
  is_delta_rad = -1;
  delta_true_pdg = 0;
  delta_true_energy = -1;
  delta_photon_energy = -1;
  delta_proton_energy = -1;
  delta_mcshower_true_pdg = 0;
  delta_mcshower_true_energy = -1;
  delta_mcshower_detprofile_energy = -1;
  delta_mctrack_true_pdg = 0;
  delta_mctrack_true_energy = -1;
  delta_mctrack_true_length = -1;  

  mctracknumber = -1;
  mcshowernumber = -1;
  tracknumber = -1;
  showernumber = -1;

  passed_swtrigger = -1;
  totalpe_sum = -1;
  totalpe_ibg_sum = -1;
  totalpe_bbg_sum = -1;

  true_nuvertx = -1;
  true_nuverty = -120;
  true_nuvertz = -1;

  true_nu_E = -1;

  true_nu_vtx_tpc_contained = -1;
  true_nu_vtx_fid_contained = -1;

  fweight_genie_ncelaxial_p1sigma = -1;
  fweight_genie_ncelaxial_m1sigma = -1;
  fweight_genie_nceleta_p1sigma = -1;
  fweight_genie_nceleta_m1sigma = -1;
  fweight_genie_qema_p1sigma = -1;
  fweight_genie_qema_m1sigma = -1;
  fweight_genie_qevec_p1sigma = -1;
  fweight_genie_qevec_m1sigma = -1;
  fweight_genie_ccresaxial_p1sigma = -1;
  fweight_genie_ccresaxial_m1sigma = -1;
  fweight_genie_ccresvector_p1sigma = -1;
  fweight_genie_ccresvector_m1sigma = -1;
  fweight_genie_resganged_p1sigma = -1;
  fweight_genie_resganged_m1sigma = -1;
  fweight_genie_ncresaxial_p1sigma = -1;
  fweight_genie_ncresaxial_m1sigma = -1;
  fweight_genie_ncresvector_p1sigma = -1;
  fweight_genie_ncresvector_m1sigma = -1;
  fweight_genie_cohma_p1sigma = -1;
  fweight_genie_cohma_m1sigma = -1;
  fweight_genie_cohr0_p1sigma = -1;
  fweight_genie_cohr0_m1sigma = -1;
  fweight_genie_nonresrvp1pi_p1sigma = -1;
  fweight_genie_nonresrvp1pi_m1sigma = -1;
  fweight_genie_nonresrvbarp1pi_p1sigma = -1;
  fweight_genie_nonresrvbarp1pi_m1sigma = -1;
  fweight_genie_nonresrvp2pi_p1sigma = -1;
  fweight_genie_nonresrvp2pi_m1sigma = -1;
  fweight_genie_nonresrvbarp2pi_p1sigma = -1;
  fweight_genie_nonresrvbarp2pi_m1sigma = -1;
  fweight_genie_resdecaygamma_p1sigma = -1;
  fweight_genie_resdecaygamma_m1sigma = -1;
  fweight_genie_resdecayeta_p1sigma = -1;
  fweight_genie_resdecayeta_m1sigma = -1;
  fweight_genie_resdecaytheta_p1sigma = -1;
  fweight_genie_resdecaytheta_m1sigma = -1;
  fweight_genie_nc_p1sigma = -1;
  fweight_genie_nc_m1sigma = -1;
  fweight_genie_disath_p1sigma = -1;
  fweight_genie_disath_m1sigma = -1;
  fweight_genie_disbth_p1sigma = -1;
  fweight_genie_disbth_m1sigma = -1;
  fweight_genie_discv1u_p1sigma = -1;
  fweight_genie_discv1u_m1sigma = -1;
  fweight_genie_discv2u_p1sigma = -1;
  fweight_genie_discv2u_m1sigma = -1;
  fweight_genie_disnucl_p1sigma = -1;
  fweight_genie_disnucl_m1sigma = -1;
  fweight_genie_agkyxf_p1sigma = -1;
  fweight_genie_agkyxf_m1sigma = -1;
  fweight_genie_agkypt_p1sigma = -1;
  fweight_genie_agkypt_m1sigma = -1;
  fweight_genie_formzone_p1sigma = -1;
  fweight_genie_formzone_m1sigma = -1;
  fweight_genie_fermigasmodelkf_p1sigma = -1;
  fweight_genie_fermigasmodelkf_m1sigma = -1;
  fweight_genie_fermigasmodelsf_p1sigma = -1;
  fweight_genie_fermigasmodelsf_m1sigma = -1;
  fweight_genie_intranukenmfp_p1sigma = -1;
  fweight_genie_intranukenmfp_m1sigma = -1;
  fweight_genie_intranukencex_p1sigma = -1;
  fweight_genie_intranukencex_m1sigma = -1;
  fweight_genie_intranukenel_p1sigma = -1;
  fweight_genie_intranukenel_m1sigma = -1;
  fweight_genie_intranukeninel_p1sigma = -1;
  fweight_genie_intranukeninel_m1sigma = -1;
  fweight_genie_intranukenabs_p1sigma = -1;
  fweight_genie_intranukenabs_m1sigma = -1;
  fweight_genie_intranukenpi_p1sigma = -1;
  fweight_genie_intranukenpi_m1sigma = -1;
  fweight_genie_intranukepimfp_p1sigma = -1;
  fweight_genie_intranukepimfp_m1sigma = -1;
  fweight_genie_intranukepicex_p1sigma = -1;
  fweight_genie_intranukepicex_m1sigma = -1;
  fweight_genie_intranukepiel_p1sigma = -1;
  fweight_genie_intranukepiel_m1sigma = -1;
  fweight_genie_intranukepiinel_p1sigma = -1;
  fweight_genie_intranukepiinel_m1sigma = -1;
  fweight_genie_intranukepiabs_p1sigma = -1;
  fweight_genie_intranukepiabs_m1sigma = -1;
  fweight_genie_intranukepipi_p1sigma = -1;
  fweight_genie_intranukepipi_m1sigma = -1;

}


void FillTreeVariables::ResetVertex() {

  //should be XX reco_nu vars
  reco_nuvertx = -1;
  reco_nuverty = -120;
  reco_nuvertz = -1;
  reco_nu_vtx_dist_to_closest_tpc_wall = -1;
  reco_nu_vtx_fid_contained = -1;

  reco_asso_tracks = 0;
  reco_asso_showers = 0;

  pi0_class_number = 0;

  reco_true_nuvert_dist = -1;
  reco_true_nuvert_distx = -10000;
  reco_true_nuvert_disty = -10000;
  reco_true_nuvert_distz = -10000;

  // Should be 21+xx "longest" vars 
  longest_asso_track_index = -1;
  /*
  reco_track_length.clear();
  reco_track_dirx.clear();
  reco_track_diry.clear();
  reco_track_dirz.clear();
  reco_track_thetayx.clear();
  reco_track_thetaxz.clear();
  reco_track_thetayz.clear();
  reco_track_phi.clear();
  reco_track_theta.clear();
  */
  reco_track_energy_new.clear();
  reco_track_energy_from_dEdx.clear();
  
  reco_track_calo_dEdx.clear();
  reco_track_calo_dEdxnew.clear();
  reco_track_calo_resrange.clear();
  
 reco_track_X.clear();
  reco_track_Y.clear();
  reco_track_Z.clear();

  all_reco_showers_bp_dist_from_vertex.clear();
  all_reco_tracks_bp_dist_from_vertex.clear();


  all_reco_showers_dist_from_vertex.clear();
  all_reco_tracks_dist_from_vertex.clear();

  true_track_matching_ratio.clear();
  true_track_index.clear();
  true_track_matched_to.clear();
  true_track_pdg.clear();
  true_track_parent_pdg.clear();
  true_track_ancestor_pdg.clear();
  true_track_origin.clear();
  true_track_startx.clear(); 
  true_track_starty.clear(); 
  true_track_startz.clear();    
  true_track_endx.clear(); 
  true_track_endy.clear(); 
  true_track_endz.clear();    
  track_matched_to_ncdeltarad_photon.clear();
  track_matched_to_ncdeltarad_proton.clear();
  true_track_energy.clear();

  true_shower_matching_ratio.clear();
  true_shower_index.clear();
  true_shower_matched_to.clear();
  true_shower_pdg.clear();
  true_shower_parent_pdg.clear();
  true_shower_ancestor_pdg.clear();
  true_shower_origin.clear();
  true_shower_startx.clear(); 
  true_shower_starty.clear(); 
  true_shower_startz.clear();    
  true_shower_endx.clear(); 
  true_shower_endy.clear(); 
  true_shower_endz.clear();
  shower_matched_to_ncdeltarad_photon.clear();
  
  shower_matched_to_ncdeltarad_proton.clear();
  true_shower_energy.clear();
  true_shower_detprofile_energy.clear();

  closest_asso_shower_dist_to_flashzcenter = -1;

  most_energetic_shower_index = -1;
  second_most_energetic_shower_index = -1;

  //exiting_pi0_px.clear();
  //exiting_pi0_py.clear();
  //exiting_pi0_pz.clear();

  /*
  reco_shower_startx.clear();
  reco_shower_starty.clear();
  reco_shower_startz.clear();
  reco_shower_dist.clear();
  reco_shower_distx.clear();
  reco_shower_disty.clear();
  reco_shower_distz.clear();
  reco_shower_thetayx.clear();
  reco_shower_thetaxz.clear();
  reco_shower_thetayz.clear();
  reco_shower_width0.clear();
  reco_shower_width1.clear();
  reco_shower_opening_angle.clear();
  reco_shower_length.clear();
  reco_shower_dirx.clear();
  reco_shower_diry.clear();
  reco_shower_dirz.clear();
  reco_shower_helper_energy.clear();
  reco_shower_bp_dist_to_tpc.clear();
  reco_shower_dedx_plane0.clear();
  reco_shower_dedx_plane1.clear();
  reco_shower_dedx_plane2.clear();
  reco_shower_dist_to_closest_flashzcenter.clear();
  */

  shortest_asso_shower_to_vert_dist = -1;

  summed_associated_helper_shower_energy = -1;

}


void FillTreeVariables::FillDeltaInfo() {
  
  int const delta_mct_index = fstorage->fdelta_mct_index;
  if(delta_mct_index == -1) return;
  int const delta_index = fstorage->fdelta_index->at(delta_mct_index);

  delta_true_pdg = fstorage->fgenie_particle_PdgCode->at(delta_mct_index).at(delta_index);
  delta_true_energy = fstorage->fgenie_particle_E->at(delta_mct_index).at(delta_index);
  delta_photon_energy = fstorage->fgenie_particle_E->at(delta_mct_index).at(fstorage->fdelta_photon_index->at(delta_mct_index));
  int const proton_index = fstorage->fdelta_proton_index->at(delta_mct_index);
  if(proton_index != -1) delta_proton_energy = fstorage->fgenie_particle_E->at(delta_mct_index).at(proton_index);
  int const mcshower_index = fstorage->fdelta_mcshower_index->at(delta_mct_index);
  if(mcshower_index != -1) {
    delta_mcshower_true_pdg = fstorage->fmcshower_PdgCode->at(mcshower_index);
    delta_mcshower_true_energy = fstorage->fmcshower_Start_E->at(mcshower_index);
    delta_mcshower_detprofile_energy = fstorage->fmcshower_DetProfile_E->at(mcshower_index);
  }
  int const mctrack_index = fstorage->fdelta_mctrack_index->at(delta_mct_index);
  if(mctrack_index != -1) {
    delta_mctrack_true_pdg = fstorage->fmctrack_PdgCode->at(mctrack_index);
    delta_mctrack_true_energy = fstorage->fmctrack_Start_E->at(mctrack_index);
    geoalgo::Point_t const start(fstorage->fmctrack_Start_X->at(mctrack_index),
				 fstorage->fmctrack_Start_Y->at(mctrack_index),
				 fstorage->fmctrack_Start_Z->at(mctrack_index));
    geoalgo::Point_t const end(fstorage->fmctrack_End_X->at(mctrack_index),
			       fstorage->fmctrack_End_Y->at(mctrack_index),
			       fstorage->fmctrack_End_Z->at(mctrack_index));
    delta_mctrack_true_length = start.Dist(end);    
  }

}


void FillTreeVariables::FillTruth(size_t const mct_index) {

  nu_pdg = fstorage->fnu_pdg->at(mct_index);
  nu_energy = fstorage->fnu_energy->at(mct_index);
  lep_pdg = fstorage->flep_pdg->at(mct_index);
  lep_energy = fstorage->flep_energy->at(mct_index);
  ccnc = fstorage->fccnc->at(mct_index);
  mode = fstorage->fmode->at(mct_index);
  interaction_type = fstorage->finteraction_type->at(mct_index);

  exiting_photon_number = 0;
  exiting_proton_number = 0;
  exiting_neutron_number = 0;
  exiting_electron_number = 0;
  exiting_antielectron_number = 0;
  exiting_muon_number = 0;
  exiting_antimuon_number = 0;
  exiting_piplus_number = 0;
  exiting_piminus_number = 0;
  exiting_pi0_number = 0;
  total_exiting_particles = 0;

  std::vector<int> const & genie_particle_PdgCode = fstorage->fgenie_particle_PdgCode->at(mct_index);
  std::vector<int> const & genie_particle_StatusCode = fstorage->fgenie_particle_StatusCode->at(mct_index);
  for(int i = 0; i < genie_particle_PdgCode.size(); ++i) {
    if(genie_particle_StatusCode.at(i) != 1) continue; 
    exiting_particle_vector.push_back(genie_particle_PdgCode.at(i));
    switch(genie_particle_PdgCode.at(i)) {
    case 22:
      ++exiting_photon_number;
      break;
    case 2212:
      ++exiting_proton_number;
      break;
    case 2112:
      ++exiting_neutron_number;
      break;
    case 11:
      ++exiting_electron_number;
      break;
    case -11:
      ++exiting_antielectron_number;
      break;
    case 13:
      ++exiting_muon_number;
      break;
    case -13:
      ++exiting_antimuon_number;
      break;
    case 211:
      ++exiting_piplus_number;
      break;
    case -211:
      ++exiting_piminus_number;
      break;
    case 111: { 
      ++exiting_pi0_number; 
      
      double this_pi0_px = fstorage->fgenie_particle_Px->at(mct_index).at(i);
      double this_pi0_py = fstorage->fgenie_particle_Py->at(mct_index).at(i);
      double this_pi0_pz = fstorage->fgenie_particle_Pz->at(mct_index).at(i);
      
      exiting_pi0_px.push_back(this_pi0_px);
      exiting_pi0_py.push_back(this_pi0_py);
      exiting_pi0_pz.push_back(this_pi0_pz);

      break;
      }
    
    }
    ++total_exiting_particles;
  }
  if(exiting_photon_number == 1) is_single_photon = 1;
  else is_single_photon = 0;
  if(fstorage->fis_delta_rad->at(mct_index) == 1) is_delta_rad = 1;
  else is_delta_rad = 0;
  FillDeltaInfo();

  true_nu_vtx_tpc_contained = fstorage->ftrue_nu_vtx_tpc_contained->at(mct_index);
  true_nu_vtx_fid_contained = fstorage->ftrue_nu_vtx_fid_contained->at(mct_index);

  true_nuvertx = fstorage->ftrue_nuvertx->at(mct_index);
  true_nuverty = fstorage->ftrue_nuverty->at(mct_index);
  true_nuvertz = fstorage->ftrue_nuvertz->at(mct_index);

  true_nu_E = fstorage->ftrue_nu_E->at(mct_index);

}


bool FillTreeVariables::PassedSWTrigger() const {

  std::vector<std::string> const & algo_v = *fstorage->fswtrigger_getListOfAlgorithms;

  std::string const int_str = "BNB_FEMBeamTriggerAlgo";
  std::string const ext_str = "EXT_BNBwin_FEMBeamTriggerAlgo";

  auto const int_it = std::find(algo_v.begin(), algo_v.end(), int_str);
  auto const ext_it = std::find(algo_v.begin(), algo_v.end(), ext_str);

  if(int_it == algo_v.end() && ext_it == algo_v.end()) {
    	//	std::cout << "function: " << __PRETTY_FUNCTION__ << " line: " << __LINE__ << std::endl
	 //    << "Found neither swtrigger\n";
    return false;
  }
  else if(int_it != algo_v.end()) {
    return fstorage->fswtrigger_passedAlgo->at(int_it - algo_v.begin());
  }
  else if(ext_it != algo_v.end()) {
    return fstorage->fswtrigger_passedAlgo->at(ext_it - algo_v.begin());
  }

  std::cout << "ERROR in: " << __PRETTY_FUNCTION__ << "\n";

  return false;

}


double FillTreeVariables::DistToClosestTPCWall(geoalgo::Point_t const & pos) {

  double dist = fabs(pos.at(0));
  if(fabs(pos.at(0) - 2*fstorage->fDetHalfWidth) < dist) dist = fabs(pos.at(0) - 2*fstorage->fDetHalfWidth);
  if(fabs(pos.at(1) + fstorage->fDetHalfHeight) < dist) dist = fabs(pos.at(1) + fstorage->fDetHalfHeight);
  if(fabs(pos.at(1) - fstorage->fDetHalfHeight) < dist) dist = fabs(pos.at(1) - fstorage->fDetHalfHeight); 
  if(fabs(pos.at(2)) < dist) dist = fabs(pos.at(2));
  if(fabs(pos.at(2) - fstorage->fDetLength) < dist) dist = fabs(pos.at(2) - fstorage->fDetLength);

  return dist;

}


void FillTreeVariables::FillTrackTruth(int const original_index) {

  true_track_matching_ratio.push_back(fstorage->freco_track_largest_ratio->at(original_index));
  int const mc_index = fstorage->freco_track_largest_mc_index->at(original_index);
  true_track_index.push_back(mc_index);
  int const mc_type = fstorage->freco_track_largest_mc_type->at(original_index);
  true_track_matched_to.push_back(mc_type);
  int const delta_mct_index = fstorage->fdelta_mct_index;

  if(mc_type == 1) {
    true_track_pdg.push_back(fstorage->fmcshower_PdgCode->at(mc_index));
    true_track_parent_pdg.push_back(fstorage->fmcshower_MotherPdgCode->at(mc_index));
    true_track_ancestor_pdg.push_back(fstorage->fmcshower_AncestorPdgCode->at(mc_index));
    true_track_origin.push_back(fstorage->fmcshower_Origin->at(mc_index));
    true_track_startx.push_back(fstorage->fmcshower_Start_X->at(mc_index));
    true_track_starty.push_back(fstorage->fmcshower_Start_Y->at(mc_index)); 
    true_track_startz.push_back(fstorage->fmcshower_Start_Z->at(mc_index));
    true_track_endx.push_back(fstorage->fmcshower_End_X->at(mc_index));
    true_track_endy.push_back(fstorage->fmcshower_End_Y->at(mc_index)); 
    true_track_endz.push_back(fstorage->fmcshower_End_Z->at(mc_index));
    true_track_energy.push_back(fstorage->fmcshower_Start_E->at(mc_index) * 1e-3);
    if(delta_mct_index != -1 && mc_index == fstorage->fdelta_mcshower_index->at(delta_mct_index)) {
      track_matched_to_ncdeltarad_photon.push_back(1);
      track_matched_to_ncdeltarad_proton.push_back(0);
    }
    else {
      track_matched_to_ncdeltarad_photon.push_back(-1);
      track_matched_to_ncdeltarad_proton.push_back(-1);
    }

  }

  else if(mc_type == 2) {
    true_track_pdg.push_back(fstorage->fmctrack_PdgCode->at(mc_index));
    true_track_parent_pdg.push_back(fstorage->fmctrack_MotherPdgCode->at(mc_index));
    true_track_ancestor_pdg.push_back(fstorage->fmctrack_AncestorPdgCode->at(mc_index));
    true_track_origin.push_back(fstorage->fmctrack_Origin->at(mc_index));
    true_track_startx.push_back(fstorage->fmctrack_Start_X->at(mc_index));
    true_track_starty.push_back(fstorage->fmctrack_Start_Y->at(mc_index)); 
    true_track_startz.push_back(fstorage->fmctrack_Start_Z->at(mc_index));
    true_track_endx.push_back(fstorage->fmctrack_End_X->at(mc_index));
    true_track_endy.push_back(fstorage->fmctrack_End_Y->at(mc_index)); 
    true_track_endz.push_back(fstorage->fmctrack_End_Z->at(mc_index));
    true_track_energy.push_back(fstorage->fmctrack_Start_E->at(mc_index) * 1e-3);
    if(delta_mct_index != -1 && mc_index == fstorage->fdelta_mctrack_index->at(delta_mct_index)) {
      track_matched_to_ncdeltarad_photon.push_back(0);
      track_matched_to_ncdeltarad_proton.push_back(1);
    }    
    else {
      track_matched_to_ncdeltarad_photon.push_back(-1);
      track_matched_to_ncdeltarad_proton.push_back(-1);
    }
  }

  else if(mc_type == 3) {
    true_track_pdg.push_back(fstorage->fmcparticle_PdgCode->at(mc_index));
    true_track_parent_pdg.push_back(0);
    true_track_ancestor_pdg.push_back(0);
    true_track_origin.push_back(-1);
    true_track_startx.push_back(-1);
    true_track_starty.push_back(-1);
    true_track_startz.push_back(-1);
    true_track_endx.push_back(-1);
    true_track_endy.push_back(-1);
    true_track_endz.push_back(-1);
    true_track_energy.push_back(-1);
    track_matched_to_ncdeltarad_photon.push_back(-1);
    track_matched_to_ncdeltarad_proton.push_back(-1);
  }

  else {
    true_track_pdg.push_back(0);
    true_track_parent_pdg.push_back(0);
    true_track_ancestor_pdg.push_back(0);
    true_track_origin.push_back(-1);
    true_track_startx.push_back(-1);
    true_track_starty.push_back(-1);
    true_track_startz.push_back(-1);
    true_track_endx.push_back(-1);
    true_track_endy.push_back(-1);
    true_track_endz.push_back(-1);
    true_track_energy.push_back(-1);
    track_matched_to_ncdeltarad_photon.push_back(-1);
    track_matched_to_ncdeltarad_proton.push_back(-1);
  }

}


void FillTreeVariables::FillShowerTruth(int const original_index) {

  true_shower_matching_ratio.push_back(fstorage->freco_shower_largest_ratio->at(original_index));
  int const mc_index = fstorage->freco_shower_largest_mc_index->at(original_index);
  true_shower_index.push_back(mc_index);
  int const mc_type = fstorage->freco_shower_largest_mc_type->at(original_index);
  true_shower_matched_to.push_back(mc_type);
  int const delta_mct_index = fstorage->fdelta_mct_index;

  pi0_class_number = 0;

  if(mc_type == 1) {
    true_shower_pdg.push_back(fstorage->fmcshower_PdgCode->at(mc_index));
    true_shower_parent_pdg.push_back(fstorage->fmcshower_MotherPdgCode->at(mc_index));
    true_shower_ancestor_pdg.push_back(fstorage->fmcshower_AncestorPdgCode->at(mc_index));
    true_shower_origin.push_back(fstorage->fmcshower_Origin->at(mc_index));
    true_shower_startx.push_back(fstorage->fmcshower_Start_X->at(mc_index));
    true_shower_starty.push_back(fstorage->fmcshower_Start_Y->at(mc_index)); 
    true_shower_startz.push_back(fstorage->fmcshower_Start_Z->at(mc_index));
    true_shower_endx.push_back(fstorage->fmcshower_End_X->at(mc_index));
    true_shower_endy.push_back(fstorage->fmcshower_End_Y->at(mc_index)); 
    true_shower_endz.push_back(fstorage->fmcshower_End_Z->at(mc_index));
    true_shower_energy.push_back(fstorage->fmcshower_Start_E->at(mc_index) * 1e-3);
    true_shower_detprofile_energy.push_back(fstorage->fmcshower_DetProfile_E->at(mc_index) * 1e-3);
    if(delta_mct_index != -1 && mc_index == fstorage->fdelta_mcshower_index->at(delta_mct_index)) {
      shower_matched_to_ncdeltarad_photon.push_back(1);
      shower_matched_to_ncdeltarad_proton.push_back(0);
    }
    else {
      shower_matched_to_ncdeltarad_photon.push_back(-1);
      shower_matched_to_ncdeltarad_proton.push_back(-1);
    }

    if(true_shower_parent_pdg.back() == 111){	
	pi0_class_number = -1;
	int shower_mother_trackID =fstorage->fmcshower_MotherTrackID->at(mc_index);

	geoalgo::Point_t main_start(fstorage->fmcshower_Start_X->at(mc_index),fstorage->fmcshower_Start_Y->at(mc_index),fstorage->fmcshower_Start_Z->at(mc_index)     );
	geoalgo::Point_t main_end(fstorage->fmcshower_End_X->at(mc_index),fstorage->fmcshower_End_Y->at(mc_index),fstorage->fmcshower_End_Z->at(mc_index)     );




    	for(int i=0; i< fstorage->fmcshower_MotherPdgCode->size(); i++){
		if(i==mc_index) continue;
		
			//std::cout<<fstorage->fmcshower_MotherPdgCode->size()<<" "<<fstorage->fmcshower_MotherTrackID->size()<<" "<<fstorage->fmcshower_Start_E->size()<<" "<<fstorage->fmcshower_Start_X->size()<<" "<<fstorage->fmcshower_Start_Y->size()<<" "<<fstorage->fmcshower_Start_Z->size()<<std::endl;
		if( fstorage->fmcshower_MotherTrackID->at(i) == shower_mother_trackID && fstorage->fmcshower_MotherPdgCode->at(i) == 111 ){
			//This is a shower from same pion
			geoalgo::Point_t s_start(fstorage->fmcshower_Start_X->at(i),fstorage->fmcshower_Start_Y->at(i),fstorage->fmcshower_Start_Z->at(i)     );
			geoalgo::Point_t s_end(fstorage->fmcshower_End_X->at(i),fstorage->fmcshower_End_Y->at(i),fstorage->fmcshower_End_Z->at(i)     );

			
			bool is_recod = false;
			int reco_track_or_shower=-1;
			int reco_index = -1;
			double reco_strength=-1;
			//Was the shower reco'd as a shower?
			// Need to have reco_shower_mc_index in the FillLightTree then
				for(int k=0; k<fstorage->freco_shower_largest_mc_index->size(); k++){
					if(fstorage->freco_shower_largest_mc_index->at(k) == i) {
						is_recod = true;
						reco_index = k;
						reco_track_or_shower = fstorage->freco_shower_largest_mc_type->at(k);
						reco_strength = fstorage->freco_shower_largest_ratio->at(k);		
					}
				}


			if(  	!ffiducial_volume.Contain(s_start) && 	!ffiducial_volume.Contain(s_end)){
				pi0_class_number = 10;
			} else 	if(!ftpc_volume.Contain(s_start) && 	!ftpc_volume.Contain(s_end)){
				pi0_class_number = 11;
			}else if(is_recod && reco_track_or_shower == 2 ){
				pi0_class_number  = 30;
			}else if(is_recod && reco_track_or_shower == 1){
				if( s_start.Dist(main_start) < 5 && s_end.Dist(main_end) < 10){
					pi0_class_number = 40;
				} else if(fstorage->fmcshower_DetProfile_E->at(i)*1e-3 < 0.05){
					pi0_class_number = 41;
				}else {
					pi0_class_number =42;
				}

			}
		}		
	
				
   	 }
    }
  }

  else if(mc_type == 2) {
    true_shower_pdg.push_back(fstorage->fmctrack_PdgCode->at(mc_index));
    true_shower_parent_pdg.push_back(fstorage->fmctrack_MotherPdgCode->at(mc_index));
    true_shower_ancestor_pdg.push_back(fstorage->fmctrack_AncestorPdgCode->at(mc_index));
    true_shower_origin.push_back(fstorage->fmctrack_Origin->at(mc_index));
    true_shower_startx.push_back(fstorage->fmctrack_Start_X->at(mc_index));
    true_shower_starty.push_back(fstorage->fmctrack_Start_Y->at(mc_index)); 
    true_shower_startz.push_back(fstorage->fmctrack_Start_Z->at(mc_index));
    true_shower_endx.push_back(fstorage->fmctrack_End_X->at(mc_index));
    true_shower_endy.push_back(fstorage->fmctrack_End_Y->at(mc_index)); 
    true_shower_endz.push_back(fstorage->fmctrack_End_Z->at(mc_index));
    true_shower_energy.push_back(fstorage->fmctrack_Start_E->at(mc_index) * 1e-3);
    true_shower_detprofile_energy.push_back(-10000);
    if(delta_mct_index != -1 && mc_index == fstorage->fdelta_mctrack_index->at(delta_mct_index)) {
      shower_matched_to_ncdeltarad_photon.push_back(0);
      shower_matched_to_ncdeltarad_proton.push_back(1);
    }    
    else {
      shower_matched_to_ncdeltarad_photon.push_back(-1);
      shower_matched_to_ncdeltarad_proton.push_back(-1);
    }
  }

  else if(mc_type == 3) {
    true_shower_pdg.push_back(fstorage->fmcparticle_PdgCode->at(mc_index));
    true_shower_parent_pdg.push_back(0);
    true_shower_ancestor_pdg.push_back(0);
    true_shower_origin.push_back(-1);
    true_shower_startx.push_back(-10000);
    true_shower_starty.push_back(-10000);
    true_shower_startz.push_back(-10000);
    true_shower_endx.push_back(-10000);
    true_shower_endy.push_back(-10000);
    true_shower_endz.push_back(-10000);
    true_shower_energy.push_back(-10000);
    true_shower_detprofile_energy.push_back(-10000);
    shower_matched_to_ncdeltarad_photon.push_back(-1);
    shower_matched_to_ncdeltarad_proton.push_back(-1);
  }

  else {
    true_shower_pdg.push_back(-1);
    true_shower_parent_pdg.push_back(0);
    true_shower_ancestor_pdg.push_back(0);
    true_shower_origin.push_back(-1);
    true_shower_startx.push_back(-10000);
    true_shower_starty.push_back(-10000);
    true_shower_startz.push_back(-10000);
    true_shower_endx.push_back(-10000);
    true_shower_endy.push_back(-10000);
    true_shower_endz.push_back(-10000);
    true_shower_energy.push_back(-10000);
    true_shower_detprofile_energy.push_back(-10000);
    shower_matched_to_ncdeltarad_photon.push_back(-1);
    shower_matched_to_ncdeltarad_proton.push_back(-1);
  }

}


double FillTreeVariables::ShowerZDistToClosestFlash(int const shower_index) {

  if(fverbose) std::cout << "ShowerZDistToClosestFlash\n";

  double const shower_start_Z = fstorage->freco_shower_ShowerStart_Z->at(shower_index);
  double const shower_direction_Z = fstorage->freco_shower_Direction_Z->at(shower_index);
  double const shower_length = fstorage->freco_shower_Length->at(shower_index);

  double zmin = shower_start_Z;
  double zmax = zmin + shower_direction_Z * shower_length;
  if(zmin > zmax) {
    std::swap(zmin, zmax);
    if(fverbose) std::cout << "\t\tSwap - Shower zmin: " << zmin << " " << zmax << "\n";
  }

  int opf_ibg_counter = 0;
  double shortest_dist = DBL_MAX;
  std::vector<double> const & opf_time = *fstorage->freco_opflash_Time;
  std::vector<double> const & opf_zcenter = *fstorage->freco_opflash_ZCenter;
  
  auto & opf_indices = fstorage->GetOpFlashIndices(fopflash_producer);
  for(int i = opf_indices.first; i < opf_indices.second; ++i) {
    double const time = opf_time.at(i);
    double const zcenter = opf_zcenter.at(i);
    if(fverbose) std::cout << "\topf time: " << time << " (opf.Time() > 3.2 && opf.Time() < 4.8)\n";
    if(!(time > fflash_start && time < fflash_end)) continue;
    if(fverbose) std::cout << "\tWithin time range\n";
    ++opf_ibg_counter;
    if(fverbose) std::cout << "\tShower index: " << shower_index << " zmin: " << zmin << " zmax: " << zmax << "\n";
    if(fverbose) std::cout << "\tflashzcenter: " << zcenter << "\n";
    double dist = DBL_MAX;
    if(zcenter < zmin) {
      dist = zmin - zcenter;
      if(fverbose) std::cout << "\tfzc - zmin dist: " << dist << "\n";
    }
    else if(zcenter > zmax) {
      dist = zcenter - zmax;
      if(fverbose) std::cout << "\tfzc - zmax dist: " << dist << "\n";
    } 
    else {
      dist = 0;
      if(fverbose) std::cout << "\tflazcenter inside shower\n";
    }
    if(dist < shortest_dist) shortest_dist = dist;
  }

  if(fverbose) std::cout << "\tshortest_dist: " << shortest_dist << "\n";

  if(opf_ibg_counter == 0) shortest_dist = -2;
  return shortest_dist;

}


double FillTreeVariables::FindBPDist(geoalgo::Cone_t const & cone) {

  double result = -1;

  geoalgo::Point_t const & start = cone.Start();
  geoalgo::Point_t const & dir = cone.Dir();

  if(ftpc_volume.Contain(start) && start.at(0) != 0 && start.at(1) != 0 && start.at(2) != 0) {
    std::vector<geoalgo::Point_t> const pv = falgo.Intersection(ftpc_volume, geoalgo::HalfLine(start, dir * -1), true);
    if(pv.empty()) {
      std::cout << __LINE__ << " " << __PRETTY_FUNCTION__ << "\nERROR: shower backwards projection does not intersect with tpc boundary:\n"
		<< "start: " << start << " dir: " << dir * -1 << "\n";
      exit(1);
    }
    else if(pv.size() == 2){
	if (pv.front().at(0) == start.at(0) && pv.front().at(0) == start.at(0) && pv.front().at(0) == start.at(0)){
		result = pv.back().Dist(start);
	} 
    }
    else if(pv.size() >2 ) {
      std::cout << __LINE__ << " " << __PRETTY_FUNCTION__ << "\nERROR: shower backwards projection intersects tpc boundary more than once:\n"
		<< "start: " << start << " dir: " << dir * -1 << "\n"
		<< "intersections: ";
      for(geoalgo::Point_t const & p : pv) {
	std::cout << p << " ";
      }
      std::cout << "\n";
      exit(1);
    }
    else result = pv.front().Dist(start);
  }  
  
  return result;

}


void FillTreeVariables::FindAllObjectsNearby(DetectorObjects const & detos, ParticleAssociation const & pa){

  geoalgo::Point_t const & reco_vertex = pa.GetRecoVertex();

 for(size_t const i : detos.GetTrackIndices()) {

      bool is_associated = false;	
     for(size_t const n : pa.GetObjectIndices()){
		if (n == i) is_associated = true;
      }
      if(!is_associated){	

	geoalgo::Trajectory const & traj = detos.GetTrack(i).ftrajectory;
        double const dist_to_reco_vertex = std::min( traj.front().Dist(reco_vertex), traj.back().Dist(reco_vertex));
	all_reco_tracks_dist_from_vertex.push_back(dist_to_reco_vertex);

	geoalgo::Line_t const trk_infinite_line(traj.front(), traj.back());
	
	double bpdist = falgo.SqDist(trk_infinite_line, reco_vertex);
	
	all_reco_tracks_bp_dist_from_vertex.push_back(bpdist);
	}
 }
 
 for(size_t const i : detos.GetShowerIndices()){

      bool is_associated = false;	
      for(size_t const n : pa.GetObjectIndices()){
		if (n == i) is_associated = true;
      }
      if( !is_associated){	
    	  geoalgo::Cone_t const & shower_cone = detos.GetShower(i).fcone;
    	  geoalgo::Point_t const & shower_start = shower_cone.Start();
          geoalgo::Point_t const & shower_dir = shower_cone.Dir();
	  geoalgo::Point_t const & shower_end = shower_start + (shower_dir * shower_cone.Length());


     	  double const dist_to_reco_vertex = shower_start.Dist(reco_vertex);
    	  all_reco_showers_dist_from_vertex.push_back(dist_to_reco_vertex);

	  geoalgo::Line_t const shr_infinite_line(shower_start, shower_end);

	  double bpdist = falgo.SqDist(shr_infinite_line, reco_vertex);

	  all_reco_showers_bp_dist_from_vertex.push_back(bpdist);
      }
   }


}



void FillTreeVariables::FindRecoObjectVariables(DetectorObjects const & detos,
						ParticleAssociation const & pa) {

  geoalgo::Point_t const & reco_vertex = pa.GetRecoVertex();
  std::vector<double> const & reco_shower_energy = *fstorage->freco_shower_EnergyHelper_energy_legacy;
  std::vector<double> const & reco_shower_newenergy = *fstorage->freco_shower_EnergyHelperNew_energy_legacy;

  double most_shower_energy = 0;
  double second_most_shower_energy = 0;
  double longest_asso_track_length = 0;

  summed_associated_helper_shower_energy = 0;
  closest_asso_shower_dist_to_flashzcenter = DBL_MAX;

  shortest_asso_shower_to_vert_dist = DBL_MAX;

  geoalgo::Point_t const & vertex = pa.GetRecoVertex();

  for(size_t const n : pa.GetObjectIndices()) {

    if(fverbose) std::cout << "\tObject index: " << n << "\n";

    size_t const original_index = detos.GetDetectorObject(n).foriginal_index;

    if(fverbose) std::cout << "\tOriginal index: " << n << "\n";

    if(detos.GetRecoType(n) == detos.ftrack_reco_type) {

      geoalgo::Trajectory const & traj = detos.GetTrack(n).ftrajectory;
      double const track_length = traj.front().Dist(traj.back());

      if(track_length > longest_asso_track_length) {
	longest_asso_track_index = reco_asso_tracks;
	longest_asso_track_length = track_length;
      }

      if(reco_asso_tracks < 100) {
	
	geoalgo::Point_t track_start(fstorage->freco_track_X->at(original_index).front(),
				     fstorage->freco_track_Y->at(original_index).front(),
				     fstorage->freco_track_Z->at(original_index).front());
	geoalgo::Point_t track_end(fstorage->freco_track_X->at(original_index).back(),
				   fstorage->freco_track_Y->at(original_index).back(),
				   fstorage->freco_track_Z->at(original_index).back());

	int flipped = 0;
	double dists = track_start.Dist(vertex);
	if(track_end.Dist(vertex) < dists) {
	  flipped = 1;
	  std::swap(track_start, track_end);
	}

	geoalgo::Vector_t track_dir = (track_end - track_start);
	track_dir.Normalize();
	
	reco_track_length[reco_asso_tracks] = track_length;
	reco_track_energy[reco_asso_tracks] = fstorage->freco_track_EnergyHelper_energy->at(original_index);
	reco_track_energy_new_legacy[reco_asso_tracks] = fstorage->freco_track_EnergyHelperNew_energy_legacy->at(original_index);

	reco_track_is_flipped[reco_asso_tracks] = flipped;
 	reco_track_startx[reco_asso_tracks] = track_start.at(0);
	reco_track_starty[reco_asso_tracks] = track_start.at(1);
	reco_track_startz[reco_asso_tracks] = track_start.at(2);
	reco_track_endx[reco_asso_tracks] = track_end.at(0);
	reco_track_endy[reco_asso_tracks] = track_end.at(1);
	reco_track_endz[reco_asso_tracks] = track_end.at(2);
	reco_track_dirx[reco_asso_tracks] = track_dir.at(0);
	reco_track_diry[reco_asso_tracks] = track_dir.at(1);
	reco_track_dirz[reco_asso_tracks] = track_dir.at(2);
	reco_track_vertdirx[reco_asso_tracks] = fstorage->freco_track_VertexDirection_X->at(original_index);
	reco_track_vertdiry[reco_asso_tracks] = fstorage->freco_track_VertexDirection_Y->at(original_index);
	reco_track_vertdirz[reco_asso_tracks] = fstorage->freco_track_VertexDirection_Z->at(original_index);
	reco_track_thetayx[reco_asso_tracks] = atan2(reco_track_diry[reco_asso_tracks], reco_track_dirx[reco_asso_tracks]);
	reco_track_thetaxz[reco_asso_tracks] = atan2(reco_track_dirx[reco_asso_tracks], reco_track_dirz[reco_asso_tracks]);
	reco_track_thetayz[reco_asso_tracks] = atan2(reco_track_diry[reco_asso_tracks], reco_track_dirz[reco_asso_tracks]);
	//reco_track_theta[reco_asso_tracks] = fstorage->freco_track_Theta->at(original_index);
	//reco_track_phi[reco_asso_tracks] = fstorage->freco_track_Phi->at(original_index);
      }

      else {
	std::cout << __PRETTY_FUNCTION__ << "\nWARNING: more than 100 associated tracks\n";
      }

      reco_track_energy_from_dEdx.push_back(fstorage->freco_track_EnergyHelperNew_energy_from_dedx->at(original_index));
      reco_track_energy_new.push_back(fstorage->freco_track_EnergyHelperNew_energy->at(original_index));
      reco_track_calo_dEdx.push_back(fstorage->freco_track_EnergyHelper_dedx->at(original_index));
      reco_track_calo_dEdxnew.push_back(fstorage->freco_track_EnergyHelperNew_dedx->at(original_index));
      reco_track_calo_resrange.push_back(fstorage->freco_track_EnergyHelper_resrange->at(original_index));

      reco_track_X.push_back(fstorage->freco_track_X->at(original_index));
      reco_track_Y.push_back(fstorage->freco_track_Y->at(original_index));
      reco_track_Z.push_back(fstorage->freco_track_Z->at(original_index));


      if(fmc && frmcm_bool) FillTrackTruth(original_index);

      ++reco_asso_tracks;
      
    }

    if(detos.GetRecoType(n) == detos.fshower_reco_type) {

      double const helper_energy = reco_shower_energy.at(original_index);
      summed_associated_helper_shower_energy += helper_energy;

      if(fverbose) {
	std::cout << "\tCurrent shower energy: " << helper_energy << "\n"
		  << "\tIs current energy: " << helper_energy << " > most shower energy: " << most_shower_energy << "?\n";
      }
      if(helper_energy > most_shower_energy) {
	if(fverbose) std::cout << "\t\tYes\n";
	second_most_shower_energy = most_shower_energy;
	second_most_energetic_shower_index = most_energetic_shower_index;
	most_shower_energy = helper_energy;
	most_energetic_shower_index = reco_asso_showers;
      }
      else if(helper_energy > second_most_shower_energy) {
	second_most_shower_energy = helper_energy;
	second_most_energetic_shower_index = reco_asso_showers;	
      }
      else if(most_energetic_shower_index == -1) {
	most_shower_energy = -1;
	most_energetic_shower_index = reco_asso_showers;
      }
      else if(second_most_energetic_shower_index == -1) {
	second_most_shower_energy = -1;
	second_most_energetic_shower_index = reco_asso_showers;
      }

      double const flash_dist = ShowerZDistToClosestFlash(original_index);
      if(flash_dist < closest_asso_shower_dist_to_flashzcenter) closest_asso_shower_dist_to_flashzcenter = flash_dist;

      double const shower_dist = detos.GetShower(n).fcone.Start().Dist(reco_vertex);
      if(shower_dist < shortest_asso_shower_to_vert_dist) {
	shortest_asso_shower_to_vert_dist = shower_dist;
      }

      if(reco_asso_showers < 100) {

	geoalgo::Cone_t const & shower_cone = detos.GetShower(n).fcone;
	geoalgo::Point_t const & shower_start = shower_cone.Start();
	geoalgo::Point_t const & shower_dir = shower_cone.Dir();
	geoalgo::Point_t const & shower_end = shower_start + (shower_dir * shower_cone.Length());

	reco_shower_startx[reco_asso_showers] = shower_start.at(0);
	reco_shower_starty[reco_asso_showers] = shower_start.at(1);
	reco_shower_startz[reco_asso_showers] = shower_start.at(2);
	reco_shower_endx[reco_asso_showers] = shower_end.at(0);
	reco_shower_endy[reco_asso_showers] = shower_end.at(1);
	reco_shower_endz[reco_asso_showers] = shower_end.at(2);
	reco_shower_dist[reco_asso_showers] = shower_start.Dist(reco_vertex);
	reco_shower_distx[reco_asso_showers] = shower_start.at(0) - reco_nuvertx;
	reco_shower_disty[reco_asso_showers] = shower_start.at(1) - reco_nuverty;
	reco_shower_distz[reco_asso_showers] = shower_start.at(2) - reco_nuvertz;
	reco_shower_thetayx[reco_asso_showers] = atan(shower_dir.at(1)/shower_dir.at(0));
	reco_shower_thetaxz[reco_asso_showers] = atan(shower_dir.at(0)/shower_dir.at(2));
	reco_shower_thetayz[reco_asso_showers] = atan(shower_dir.at(1)/shower_dir.at(2)); 
	//reco_shower_width0[reco_asso_showers] = sh.Width()[0]);
	//reco_shower_width1[reco_asso_showers] = sh.Width()[1]);
	reco_shower_opening_angle[reco_asso_showers] = fstorage->freco_shower_OpenAngle->at(original_index);
	reco_shower_length[reco_asso_showers] = fstorage->freco_shower_Length->at(original_index);
	reco_shower_dirx[reco_asso_showers] = shower_dir.at(0);
	reco_shower_diry[reco_asso_showers] = shower_dir.at(1);
	reco_shower_dirz[reco_asso_showers] = shower_dir.at(2);
	reco_shower_helper_energy[reco_asso_showers] = reco_shower_energy.at(original_index);
	reco_shower_helpernew_energy[reco_asso_showers] = reco_shower_newenergy.at(original_index);
	reco_shower_bp_dist_to_tpc[reco_asso_showers] = FindBPDist(shower_cone);
	std::vector<double> const & dedx = fstorage->freco_shower_EnergyHelper_dedx->at(original_index);
	reco_shower_dedx_plane0[reco_asso_showers] = dedx.at(0);
	reco_shower_dedx_plane1[reco_asso_showers] = dedx.at(1);
	reco_shower_dedx_plane2[reco_asso_showers] = dedx.at(2);
	std::vector<double> const & dedxnew = fstorage->freco_shower_EnergyHelperNew_dedx->at(original_index);
	reco_shower_dedxnew_plane0[reco_asso_showers] = dedxnew.at(0);
	reco_shower_dedxnew_plane1[reco_asso_showers] = dedxnew.at(1);
	reco_shower_dedxnew_plane2[reco_asso_showers] = dedxnew.at(2);
	reco_shower_dist_to_closest_flashzcenter[reco_asso_showers] = flash_dist;
      }	

      if(fmc && frmcm_bool) FillShowerTruth(original_index);

      ++reco_asso_showers;

    }
    
  }
  if(shortest_asso_shower_to_vert_dist == DBL_MAX) shortest_asso_shower_to_vert_dist = -1;
  if(closest_asso_shower_dist_to_flashzcenter == DBL_MAX) closest_asso_shower_dist_to_flashzcenter = -1;

}


void FillTreeVariables::FillVertexTree(ParticleAssociations const & pas,
				       size_t const pn,
				       size_t const mct_index) {
  ResetVertex();

  DetectorObjects const & detos = pas.GetDetectorObjects();
  ParticleAssociation const & pa = pas.GetAssociations().at(pn);
  geoalgo::Point_t const & reco_vertex = pa.GetRecoVertex();

  reco_nuvertx = reco_vertex.at(0);
  reco_nuverty = reco_vertex.at(1);
  reco_nuvertz = reco_vertex.at(2);

  if(fmc) {
    reco_true_nuvert_distx = reco_nuvertx - true_nuvertx;
    reco_true_nuvert_disty = reco_nuverty - true_nuverty;
    reco_true_nuvert_distz = reco_nuvertz - true_nuvertz;
    reco_true_nuvert_dist = sqrt(reco_true_nuvert_distx*reco_true_nuvert_distx + 
				 reco_true_nuvert_disty*reco_true_nuvert_disty + 
				 reco_true_nuvert_distz*reco_true_nuvert_distz);
  }

  reco_nu_vtx_dist_to_closest_tpc_wall = DistToClosestTPCWall(reco_vertex);
  if(ffiducial_volume.Contain(reco_vertex)) reco_nu_vtx_fid_contained = 1;
  else reco_nu_vtx_fid_contained = 0;

  if(fverbose) std::cout << "Find various track and shower variables\n";
  FindRecoObjectVariables(detos, pa);
  FindAllObjectsNearby(detos, pa);
  if(fverbose) std::cout << "Most energetic shower index: " << most_energetic_shower_index << "\n";

  fvertex_tree->Fill();

}


void FillTreeVariables::Fill(ParticleAssociations const & pas) {

  ResetEvent();

  size_t mct_index = SIZE_MAX;
  if(fmc) {
    std::vector<int> const & is_delta_rad = *fstorage->fis_delta_rad;
    if(!is_delta_rad.empty()) mct_index = 0;
    for(size_t i = 0; i < is_delta_rad.size(); ++i) {
      if(is_delta_rad.at(i) == 1) {
	mct_index = i;
	break;
      }
    }
    if(mct_index != SIZE_MAX) FillTruth(mct_index);
    mctracknumber = fstorage->fmctrack_Origin->size();
    mcshowernumber = fstorage->fmcshower_Origin->size();
  }

  run_number = fstorage->frun_number;
  subrun_number = fstorage->fsubrun_number;
  event_number = fstorage->fevent_number;

  auto & track_indices = fstorage->GetTrackIndices(ftrack_producer);
  tracknumber = track_indices.second - track_indices.first;
  auto & shower_indices = fstorage->GetShowerIndices(fshower_producer);
  showernumber = shower_indices.second - shower_indices.first;

  if(PassedSWTrigger()) passed_swtrigger = 1;
  else passed_swtrigger = 0;

  totalpe_sum = 0;
  totalpe_ibg_sum = 0;
  totalpe_bbg_sum = 0;

  std::vector<double> const & opf_totalpe = *fstorage->freco_opflash_TotalPE;
  std::vector<double> const & opf_time = *fstorage->freco_opflash_Time;
  auto & opf_indices = fstorage->GetOpFlashIndices(fopflash_producer);
  for(int i = opf_indices.first; i < opf_indices.second; ++i) {
    double const totalpe = opf_totalpe.at(i);
    double const time = opf_time.at(i);
    totalpe_sum += totalpe;
    if(time > fflash_start && time < fflash_end) {
      totalpe_ibg_sum += totalpe;
    }
    else if(time < fflash_start){
      totalpe_bbg_sum += totalpe;
    }
  }

  for(size_t const pn : pas.GetSelectedAssociations()) {
    FillVertexTree(pas, pn, mct_index);
  } 

}
