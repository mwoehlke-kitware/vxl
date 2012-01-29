#ifndef sdet_atmospheric_image_classifier_h_
#define sdet_atmospheric_image_classifier_h_
//:
// \file
// \brief A subclass of sdet_texture_classifier to determine image quality based on atmospheric effects such as clouds and haze
//
// \author J.L. Mundy
// \date   January 28, 2012
//-----------------------------------------------------------------------------
#include <sdet/sdet_texture_classifier.h>
//
// This classifier is based on learning textures for images with and without 
// significant atmospheric effects such as clouds and haze
// The class assumes a set of categories associated with atmospheric-free
// conditions such as urban, water, shadow, and two atmospheric categories:
// cloud  and haze. This classifier then produces a color image quality 
// blocked image. The color pixel values in the output are assigned as:
// red - belief the high atmospheric effects occur in the block
// green - belief the the block is free of atmospheric effects
// blue - degree of uncertainty based on subjective logic theory
//
class sdet_atmospheric_image_classifier : public sdet_texture_classifier
{
 public:
  sdet_atmospheric_image_classifier(sdet_texture_classifier_params const& params) : sdet_texture_classifier(params){}

  ~sdet_atmospheric_image_classifier(){};
  //: typically the atmospheric categories are "cld" and "haz"
  void set_atmospheric_categories(vcl_vector<vcl_string> const& atmos_cats)
    {atmos_categories_ = atmos_cats;}
  //: image of atmospheric quality expressed as colors
  vil_image_view<float> classify_image_blocks_qual(vcl_string const& img_path);
  vil_image_view<float> classify_image_blocks_qual(vil_image_view<float> const& image);

 protected:
  void  category_quality_color_mix(vcl_map<vcl_string, float>& probs,
                                   vnl_vector_fixed<float, 3> const& uncert,
                                   vnl_vector_fixed<float, 3>& color_mix);
  vcl_vector<vcl_string> atmos_categories_;
  bool atmos_cat(vcl_string const& cat);
};

#endif // sdet_atmospheric_image_classifier_h_