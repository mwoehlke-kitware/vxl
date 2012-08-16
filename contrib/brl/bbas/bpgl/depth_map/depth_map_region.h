//This is brl/bbas/bpgl/depth_map/depth_map_region.h
#ifndef depth_map_region_h_
#define depth_map_region_h_
//:
// \file
// \brief A class to represent a symbolic depth region
//
// \author J. L. Mundy
// \date July 31, 2012
// \verbatim
//  Modifications
// \endverbatim
// units are in meters
#include <vbl/vbl_ref_count.h>
#include <vcl_limits.h>
#include <vsol/vsol_point_2d_sptr.h>
#include <vsol/vsol_polygon_2d_sptr.h>
#include <vsol/vsol_polygon_3d_sptr.h>
#include <vpgl/vpgl_perspective_camera.h>
#include <vil/vil_image_view.h>
#include <vgl/vgl_vector_3d.h>
#include <vgl/vgl_plane_3d.h>
#include <vcl_string.h>
#include <vsl/vsl_binary_io.h>


class depth_map_region : public vbl_ref_count
{
 public:
  enum orientation{GROUND_PLANE, VERTICAL, INFINT, NOT_DEF};
  //: default constructor
  depth_map_region();
  //: standard constructor for a plane that can be moved along the camera ray
  depth_map_region(vsol_polygon_2d_sptr const& region, 
                   vgl_plane_3d<double> const& region_plane,
                   double min_depth, double max_depth,
                   vcl_string name,
                   depth_map_region::orientation orient);

  //: constructor for a fixed plane, e.g. the ground plane
  depth_map_region(vsol_polygon_2d_sptr const& region, 
                   vgl_plane_3d<double> const& region_plane,
                   vcl_string name,
                   depth_map_region::orientation orient);

  //: constructor for a region of infinite distance
  depth_map_region(vsol_polygon_2d_sptr const& region,
                   vcl_string name);

  //: unique name
  vcl_string name() const {return name_;}
  //: region orientation
  orientation orient_type() const{return orient_type_;}

 
  void set_region_3d(vpgl_perspective_camera<double> const& cam);
  void set_region_3d(double depth, vpgl_perspective_camera<double> const& cam);

  void set_min_depth(double min_depth){min_depth_ = min_depth;}
  void set_max_depth(double max_depth){max_depth_ = max_depth;}
  void set_depth_inc(double depth_inc){depth_inc_ = depth_inc;}
  void set_order(unsigned order){order_ = order;}
  //:accessors
  double min_depth() const {return min_depth_;}
  double max_depth() const {return max_depth_;}
  vsol_polygon_3d_sptr region_3d() const {return region_3d_;}
  vsol_polygon_2d_sptr region_2d() const {return region_2d_;}
  double depth() const {return depth_;}
  double depth_inc() const {return  depth_inc_;}
  unsigned order() const {return order_;}
  vsol_point_2d_sptr centroid_2d() const;
  //:
  //  depth is defined as distance on  the x-y plane in the direction
  //  of the camera ray through the region centroid. An assertion is
  //  thrown if the camera ray is perpendicular to the 3-d region normal
  static vsol_polygon_3d_sptr 
    region_2d_to_3d(vsol_polygon_2d_sptr const& region_2d, 
                    vgl_vector_3d<double> const& region_normal,
                    double depth, // plane is moved along ray to depth
                    vpgl_perspective_camera<double> const& cam);

  //: The 3-d region is fixed as in the case of the ground plane.
  // The 3-d vertices are the intersection of the camera rays with the plane.
  static vsol_polygon_3d_sptr 
    region_2d_to_3d(vsol_polygon_2d_sptr const& region_2d, 
                    vgl_plane_3d<double> const& region_plane,
                    vpgl_perspective_camera<double> const& cam);

  //: The direction vector that is parallel to the ground plane and lies in the plane of the camera principal ray and the z axis. 
  //  Provides the normal to the plane perpendicular to the gound plane
  //  and orthogonal to the camera principal ray.
  static vgl_vector_3d<double> 
    perp_ortho_dir(vpgl_perspective_camera<double> const& cam);

  //: changes the 2-d region so that points near the horizon move to the specified max depth.
  //  The proximity scale factor defines
  //  a threshold on "near" as a factor times the distance to the 
  //  point closest to the horizon. This approach is likely to be 
  //  fragile if the ground plane region has a convex shape.
  bool set_ground_plane_max_depth(double max_depth, 
                                  vpgl_perspective_camera<double> const& cam,
                                  double proximity_scale_factor);

  //: update the input depth image with *this* region
  // Currently assumes disjoint regions so that sorting on depth
  // is not required.
  bool update_depth_image(vil_image_view<float>& depth_image,
                          vpgl_perspective_camera<double> const& cam,
                          double downsample_ratio = 1.0) const;

  //: binary IO write
  void b_write(vsl_b_ostream& os);

  //: binary IO read
  void b_read(vsl_b_istream& is);

 protected:
  unsigned order_;//depth order
  orientation orient_type_;
  vcl_string name_;
  // depth value for region centroid
  double depth_; //current depth estimate
  double min_depth_; // closest possible centroid depth
  double max_depth_; // furthest possible centroid depth
  double depth_inc_; // step size from min to max depth
  vgl_plane_3d<double> region_plane_;
  vsol_polygon_2d_sptr region_2d_;
  vsol_polygon_3d_sptr region_3d_;//:cached
};

#include <depth_map/depth_map_region_sptr.h>
void vsl_b_write(vsl_b_ostream& os, const depth_map_region* rptr);

void vsl_b_read(vsl_b_istream &is, depth_map_region*& rptr);

void vsl_b_write(vsl_b_ostream& os, const depth_map_region_sptr& rptr);

void vsl_b_read(vsl_b_istream &is, depth_map_region_sptr& rptr);
#endif //depth_map_region_h_
