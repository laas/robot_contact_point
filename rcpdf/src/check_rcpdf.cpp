#include <iostream>
#include <fstream>

#include <rcpdf/parser.hh>

using namespace rcpdf;
using namespace rcpdf_interface;

void displayPose(const Pose& pose)
{
  double roll = 0.;
  double pitch = 0.;
  double yaw = 0.;

  pose.rotation.getRPY(roll, pitch, yaw);

  std::cout << pose.position.x << " "
	    << pose.position.y << " "
	    << pose.position.z << " / "
	    << roll << " "
	    << pitch << " "
	    << yaw << std::endl;
}

void displayLimit(boost::shared_ptr<Limit> limit)
{
  if (!limit)
    {
      std::cout << "   - Limit: none" << std::endl;
      return;
    }
  std::cout << "   - Limit: " << std::endl
	    << "      - Normal force: "
	    << limit->normal_force_ << std::endl;
}

void displayGeometry(boost::shared_ptr<Geometry> geometry)
{
  if (!geometry)
    {
      std::cout << "   - Geometry: none" << std::endl;
      return;
    }

  if (geometry->type == Geometry::SPHERE)
    std::cout << "sphere" << std::endl;
  else if (geometry->type == Geometry::BOX)
    std::cout << "box" << std::endl;
  else if (geometry->type == Geometry::CYLINDER)
    std::cout << "cylinder" << std::endl;
  else if (geometry->type == Geometry::MESH)
    std::cout << "mesh" << std::endl;
  else
    std::cout << "unkown" << std::endl;
}

void displayContact(boost::shared_ptr<Contact> contact)
{
  if (!contact)
    {
      std::cout << "   - null pointer in contact list" << std::endl;
      return;
    }
  std::cout << "   - Name: " << contact->name_ << std::endl;
  std::cout << "   - Link: " << contact->link_ << std::endl;
  std::cout << "   - Origin: ";
  displayPose(contact->origin_);
  std::cout << "   - Geometry: ";
  displayGeometry(contact->geometry_);
  displayLimit(contact->limit_);
}

void display(boost::shared_ptr<ModelInterface> model)
{
  if (!model)
    {
      std::cerr << "model pointer is null" << std::endl;
      return;
    }
  std::cout << "Name: " << model->name_ << std::endl;

  for (std::vector<boost::shared_ptr<Contact> >::const_iterator
	 it = model->contacts_.begin();
       it != model->contacts_.end(); ++it)
    displayContact(*it);
}

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cerr << "Expect RCPDF xml file to parse" << std::endl;
      return -1;
    }

  std::string xml_string;
  std::fstream xml_file (argv[1], std::fstream::in);
  while ( xml_file.good() )
    {
      std::string line;
      std::getline (xml_file, line);
      xml_string += (line + "\n");
    }
  xml_file.close();

  boost::shared_ptr<ModelInterface> model = parseRCPDF(xml_string);
  if (!model)
    {
      std::cerr << "ERROR: Model Parsing the xml failed" << std::endl;
      return -1;
    }
  std::cout << "---------- Successfully Parsed XML ---------------"
	    << std::endl;
  display(model);
  return 0;
}
