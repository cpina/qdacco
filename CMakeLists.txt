 ########## Project setup ##########
CMAKE_MINIMUM_REQUIRED(VERSION 3.25.1)
PROJECT(qdacco)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET( QDACCO_VERSION 1.2.4 )

STRING( REGEX MATCHALL "[0-9]+" QDACCO_VERSIONS ${QDACCO_VERSION} )
LIST( GET QDACCO_VERSIONS 0 QDACCO_VERSION_MAJOR)
LIST( GET QDACCO_VERSIONS 1 QDACCO_VERSION_MINOR)
LIST( GET QDACCO_VERSIONS 2 QDACCO_VERSION_PATCH)

# ######### Cmake ##########
option(CPACK_SOURCE_TGZ OFF)
option(CPACK_SOURCE_TZ OFF)

# AFAIK CPACK_PACKAGE_VERSION_* not used at the moment because
# CPACK_SOURCE_PACKAGE_FILE_NAME is overwritten. Left for
# compatibility and just in case.
set( CPACK_PACKAGE_VERSION_MAJOR ${QDACCO_VERSION_MAJOR})
set( CPACK_PACKAGE_VERSION_MINOR ${QDACCO_VERSION_MINOR})
set( CPACK_PACKAGE_VERSION_PATCH ${QDACCO_VERSION_PATCH})

set( CPACK_SOURCE_PACKAGE_FILE_NAME "qdacco-${QDACCO_VERSION}")

# Assumes that ${CMAKE_BINARY_DIR} != ${CMAKE_SOURCE_DIR}
set(CPACK_SOURCE_IGNORE_FILES ${CMAKE_BINARY_DIR} /\\\\.git/)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
	message(STATUS "WARNING: build and source directory is the same. make package_source will not work. Read INSTALL.ca/INSTALL.en file.")
endif()

# ######### General setup ##########
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
find_package(Qt6Network REQUIRED) 
find_package(Qt6Widgets REQUIRED)
find_package(Qt6DBus REQUIRED)

set(QT6_LIBRARIES Qt6::Widgets Qt6::Network Qt6::Xml Qt6::DBus)

#include_directories(${Qt5Widgets_INCLUDES} ${Qt5Xml_INCLUDES})
#add_definitions(${Qt5Widgets_DEFINITIONS} ${Qt5Xml_DEFINITIONS})

########### qdacco gui ##########
message(STATUS "Working on qdacco gui")
add_subdirectory(gui)

########### cpack capabilites ##########
INCLUDE(CPack)

