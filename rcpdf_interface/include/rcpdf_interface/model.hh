#ifndef RCPDF_INTERFACE_MODEL_HH
# define RCPDF_INTERFACE_MODEL_HH
# include <string>
# include <vector>
# include <boost/shared_ptr.hpp>

# include <rcpdf_interface/contact.hh>

namespace rcpdf_interface
{
  class ModelInterface
  {
  public:
    explicit ModelInterface ()
      : name_(),
	contacts_()
    {}
    ~ ModelInterface ()
    {}

    std::string name_;
    std::vector<boost::shared_ptr<Contact> > contacts_;
  };
} // end of namespace rcpdf_interface.

#endif //! RCPDF_INTERFACE_MODEL_HH
