#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <tinyxml.h>

#include <ros/console.h>

#include "urdf_interface/link.h"
#include "rcpdf_interface/contact.hh"
#include "rcpdf_interface/model.hh"
#include "rcpdf/parser.hh"

namespace rcpdf
{
  using rcpdf_interface::Geometry;
  using urdf::Sphere;
  using urdf::Box;
  using urdf::Cylinder;
  using urdf::Mesh;
  
  namespace
  {
    boost::shared_ptr<Geometry> parseGeometry(TiXmlElement *g)
    {
      boost::shared_ptr<Geometry> geom;
      if (!g) return geom;

      TiXmlElement *shape = g->FirstChildElement();
      if (!shape)
	{
	  ROS_ERROR("Geometry tag contains no child element.");
	  return geom;
	}

      std::string type_name = shape->ValueStr();
      if (type_name == "sphere")
	geom.reset(new Sphere);
      else if (type_name == "box")
	geom.reset(new Box);
      else if (type_name == "cylinder")
	geom.reset(new Cylinder);
      else if (type_name == "mesh")
	geom.reset(new Mesh);
      else
	{
	  ROS_ERROR("Unknown geometry type '%s'", type_name.c_str());
	  return geom;
	}

      // clear geom object when fails to initialize
      if (!geom->initXml(shape)){
	ROS_ERROR("Geometry failed to parse");
	geom.reset();
      }

      return geom;
    }


    boost::shared_ptr<rcpdf_interface::Limit>
    parseLimit(TiXmlElement* limit_element)
    {
      boost::shared_ptr<rcpdf_interface::Limit> limit =
	boost::make_shared<rcpdf_interface::Limit>();

      // Get maximum normal force.
      const char* normal_force = limit_element->Attribute("normal_force");
      limit->normal_force_ = boost::lexical_cast<double>(normal_force);
      return limit;
    }

    boost::shared_ptr<rcpdf_interface::Contact>
    parseContact(TiXmlElement* contact_xml)
    {
      boost::shared_ptr<rcpdf_interface::Contact> contact =
	boost::make_shared<rcpdf_interface::Contact>();

      // Get contact name
      const char *name = contact_xml->Attribute("name");
      if (!name)
	{
	  ROS_ERROR("No name given for the contact.");
	  contact.reset();
	  return contact;
	}
      contact->name_ = std::string(name);

      // Get associated link
      const char *link = contact_xml->Attribute("link");
      if (!link)
	{
	  ROS_ERROR("No associated link given for the contact.");
	  contact.reset();
	  return contact;
	}
      contact->link_ = std::string(link);

      // Parse origin.
      TiXmlElement* origin_xml = contact_xml->FirstChildElement("origin");
      if (!origin_xml)
	{
	  ROS_ERROR("No origin for the contact.");
	  contact.reset();
	  return contact;
	}
      if (!contact->origin_.initXml(origin_xml))
	{
	  ROS_ERROR("Contact has a malformed origin tag");
	  contact.reset();
	  return contact;
	}

      // Parse geometry.
      TiXmlElement* geometry_xml = contact_xml->FirstChildElement("geometry");
      if (!geometry_xml)
	{
	  ROS_ERROR("No geometry for the contact.");
	  contact.reset();
	  return contact;
	}
      contact->geometry_ = parseGeometry(geometry_xml);

      // Parse limit.
      TiXmlElement* limit_xml = contact_xml->FirstChildElement("limit");
      if (limit_xml)
	contact->limit_ = parseLimit(limit_xml);

      return contact;
    }
  } // end of anonymous namespace.

  boost::shared_ptr<rcpdf_interface::ModelInterface>
  parseRCPDF(const std::string& xml_string)
  {
    boost::shared_ptr<rcpdf_interface::ModelInterface> model =
      boost::make_shared<rcpdf_interface::ModelInterface>();

    TiXmlDocument xml_doc;
    xml_doc.Parse(xml_string.c_str());

    TiXmlElement* robot_xml = xml_doc.FirstChildElement("robot");
    if (!robot_xml)
      {
	ROS_ERROR("Could not find the 'robot' element in the xml file");
	model.reset();
	return model;
      }

    // Get robot name
    const char *name = robot_xml->Attribute("name");
    if (!name)
      {
	ROS_ERROR("No name given for the robot.");
	model.reset();
	return model;
      }
    model->name_ = std::string(name);

    // Get all contact elements
    for (TiXmlElement* contact_xml = robot_xml->FirstChildElement("contact");
	 contact_xml;
	 contact_xml = contact_xml->NextSiblingElement("contact"))
      {
	boost::shared_ptr<rcpdf_interface::Contact> contact =
	  parseContact(contact_xml);
	if (contact)
	  model->contacts_.push_back(contact);
      }
    return model;
  }
} // end of namespace rcpdf.
