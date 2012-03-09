#ifndef RCPDF_INTERFACE_MODEL_HH
# define RCPDF_INTERFACE_MODEL_HH
# include <string>
# include <vector>
# include <boost/shared_ptr.hpp>


namespace rcpdf_interface
{
  typedef ::urdf::Geometry Geometry;

  class ModelInterface
  {
  public:
    explicit Model ()
      : name_(),
	contacts_()
    {}
    ~ Model ()
    {}

    std::string name_;
    std::vector<boost::shared_ptr<Contact> > contacts_;
  };
} // end of namespace rcpdf_interface.

#endif //! RCPDF_INTERFACE_MODEL_HH
