#ifndef RCPDF_INTERFACE_CONTACT_HH
# define RCPDF_INTERFACE_CONTACT_HH
# include <string>
# include <boost/shared_ptr.hpp>

# include <ros/ros.h>
# include <urdf_interface/link.h>
# include <urdf_interface/pose.h>

namespace rcpdf_interface
{
  typedef ::urdf::Geometry Geometry;
  typedef ::urdf::Pose Pose;

  class Limit
  {
  public:
    explicit Limit ()
      : normal_force_(0.)
    {}
    ~Limit()
    {}

    double normal_force_;
  };

  class Contact
  {
  public:
    explicit Contact()
      : name_(),
	link_(),
	origin_(),
	geometry_(),
	limit_()
    {}
    ~Contact()
    {}

    std::string name_;
    std::string link_;

    Pose origin_;

    boost::shared_ptr<Geometry> geometry_;
    boost::shared_ptr<Limit> limit_;

    void clear()
    {
      geometry_.reset();
    }
  };
} // end of namespace rcpdf_interface.

#endif //! RCPDF_INTERFACE_CONTACT_HH
