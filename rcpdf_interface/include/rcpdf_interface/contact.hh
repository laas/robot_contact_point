#ifndef RCPDF_INTERFACE_CONTACT_HH
# define RCPDF_INTERFACE_CONTACT_HH
# include <string>
# include <boost/shared_ptr.hpp>

# include <ros/ros.h>
# include <urdf_interface/link.h>
# include <urdf_interface/pose.h>

namespace rcpdf_interface
{
  /// \brief Geometry node imported from the URDF package.
  typedef ::urdf::Geometry Geometry;
  /// \brief Pose node imported from the URDF package.
  typedef ::urdf::Pose Pose;

  /// \brief Limitations to consider when this contact is active.
  ///
  /// The only limit for now is the maximum normal force which is
  /// allowed when the robot is sustained by this contact.
  class Limit
  {
  public:
    explicit Limit ()
      : normal_force_(0.)
    {}
    ~Limit()
    {}

    /// \brief Maximum allowed normal force.
    ///
    /// The contact stability and/or the robot integrity is not
    /// guaranteed if a larger force is applied.
    double normal_force_;
  };

  /// \brief Define a contact zone on the robot body.
  ///
  /// A contact zone is a zone which can sustain a reaction force from
  /// the environment.
  ///
  /// For instance, the robot can, at least partially, be sustained by
  /// lying on this part of its body.
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

    /// \brief Contact name.
    ///
    /// Must be unique among all robot contacts.
    /// It is used to identify a particular contact.
    std::string name_;

    /// \brief Link on which the contact is attached.
    ///
    /// This link must exist in the associated robot description.
    /// This package do not require a robot description.
    std::string link_;

    /// \brief Contact zone origin with respect to the link origin
    /// frame.
    ///
    /// See URDF documentation for more information.
    Pose origin_;

    /// \brief Geometry of the contact zone.
    ///
    /// See documentation of the geometry node in the URDF
    /// documentation.
    boost::shared_ptr<Geometry> geometry_;
    /// \brief Optional contact limitations.
    ///
    /// Define under which conditions this contact can be used safely.
    boost::shared_ptr<Limit> limit_;

    void clear()
    {
      geometry_.reset();
    }
  };
} // end of namespace rcpdf_interface.

#endif //! RCPDF_INTERFACE_CONTACT_HH
