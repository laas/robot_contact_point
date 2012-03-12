#ifndef RCPDF_INTERFACE_MODEL_HH
# define RCPDF_INTERFACE_MODEL_HH
# include <string>
# include <vector>
# include <boost/shared_ptr.hpp>

# include <rcpdf_interface/contact.hh>

namespace rcpdf_interface
{
  /// \brief Model of the robot contact zones.
  ///
  /// The model is composed of the robot name
  /// and of a list of contacts.
  class ModelInterface
  {
  public:
    explicit ModelInterface ()
      : name_(),
	contacts_()
    {}
    ~ ModelInterface ()
    {}

    /// \brief Robot name.
    ///
    /// This identify the robot uniquely in order to link this model
    /// with the URDF description.
    std::string name_;

    /// \brief List of allowed contact zones.
    std::vector<boost::shared_ptr<Contact> > contacts_;
  };
} // end of namespace rcpdf_interface.

#endif //! RCPDF_INTERFACE_MODEL_HH
