cmake_minimum_required(VERSION 2.8)

SET(PROJECT_NAME rcpdf_interface)
SET(PROJECT_VERSION 0.2)
SET(PROJECT_DESCRIPTION
  "Robot Contact Point Description Format interfaces definition"
  )
SET(PROJECT_URL github.com/laas/robot_contact_point)

SET(CUSTOM_HEADER_DIR rcpdf_interface)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/cpack.cmake)
INCLUDE(cmake/boost.cmake)

SET(${PROJECT_NAME}_HEADERS
  include/rcpdf_interface/contact.hh
  include/rcpdf_interface/model.hh
  )
SETUP_PROJECT()

SEARCH_FOR_BOOST()
ADD_REQUIRED_DEPENDENCY("roscpp >= 1.9")
ADD_REQUIRED_DEPENDENCY("urdf_interface >= 1.9")

SETUP_PROJECT_FINALIZE()
SETUP_PROJECT_CPACK()
