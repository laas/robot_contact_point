#ifndef RCPDF_PARSER_HH
# define RCPDF_PARSER_HH
# include <rcpdf_interface/model.hh>

namespace rcpdf
{
  boost::shared_ptr<rcpdf_interface::ModelInterface>
  parseRCPDF(const std::string& xml_string);
} // end of namespace rcpdf.

#endif //! RCPDF_PARSER_HH
