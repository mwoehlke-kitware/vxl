#ifndef sdet_processes_h_
#define sdet_processes_h_

#include <bprb/bprb_macros.h>
#include <bprb/bprb_func_process.h>

// execute and const functions
DECLARE_FUNC_CONS(sdet_detect_edges_process);
DECLARE_FUNC_CONS(sdet_detect_edge_tangent_process);
DECLARE_FUNC_CONS(sdet_detect_edge_tangent_interp_process);
DECLARE_FUNC_CONS(sdet_write_edge_file_process);
DECLARE_FUNC_CONS(sdet_detect_edge_line_fitted_process);
DECLARE_FUNC_CONS(sdet_detect_third_order_edges_process);
DECLARE_FUNC_CONS(sdet_detect_third_order_edges_dt_process);
DECLARE_FUNC_CONS(sdet_texture_classifier_process);
DECLARE_FUNC_CONS(sdet_texture_classifier_kernel_margin_process);
DECLARE_FUNC_CONS_FIN(sdet_texture_training_process);
DECLARE_FUNC_CONS(sdet_create_texture_classifier_process);
DECLARE_FUNC_CONS(sdet_print_texton_dict_process);
DECLARE_FUNC_CONS(sdet_exp_img_classifier_process);
DECLARE_FUNC_CONS(sdet_save_texture_classifier_process);
DECLARE_FUNC_CONS(sdet_load_texture_classifier_process);
DECLARE_FUNC_CONS(sdet_segment_image_process);
DECLARE_FUNC_CONS(sdet_segment_image_using_edge_map_process);
DECLARE_FUNC_CONS(sdet_segment_image_using_height_map_process);
DECLARE_FUNC_CONS(sdet_segment_image_using_height_map_process2);
DECLARE_FUNC_CONS(sdet_texture_classifier_process2);
DECLARE_FUNC_CONS(sdet_extract_filter_bank_process);
DECLARE_FUNC_CONS_FIN(sdet_texture_training_process2);
DECLARE_FUNC_CONS(sdet_load_texture_dictionary_process);
DECLARE_FUNC_CONS(sdet_add_to_filter_bank_process);
DECLARE_FUNC_CONS(sdet_texture_classifier_roc_process);
DECLARE_FUNC_CONS(sdet_texture_classifier_roc_process2);
DECLARE_FUNC_CONS(sdet_texture_classifier_roc_process3);
DECLARE_FUNC_CONS(sdet_add_to_filter_bank_process2);
DECLARE_FUNC_CONS(sdet_texture_classify_satellite_clouds_process);
DECLARE_FUNC_CONS(sdet_texture_classify_satellite_clouds_process2);
DECLARE_FUNC_CONS(sdet_dump_vsol_binary_data_process);
DECLARE_FUNC_CONS(sdet_add_responses_to_filter_bank_process);
DECLARE_FUNC_CONS(sdet_extract_filter_bank_img_process);
DECLARE_FUNC_CONS(sdet_selective_search_process);
DECLARE_FUNC_CONS(sdet_fit_oriented_boxes_process);
DECLARE_FUNC_CONS(sdet_fit_oriented_boxes_from_geotiff_process);
DECLARE_FUNC_CONS(sdet_texture_unsupervised_classifier_process);

#endif
