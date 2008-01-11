 ########## Project setup ##########
PROJECT(qdacco)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

SET( QDACCO_VERSION 0.7.0 )
#a--> 1, b-->2, ....d-->4

STRING( REGEX MATCHALL "[0-9]+" QDACCO_VERSIONS ${QDACCO_VERSION} )
LIST( GET QDACCO_VERSIONS 0 QDACCO_VERSION_MAJOR)
LIST( GET QDACCO_VERSIONS 1 QDACCO_VERSION_MINOR)
LIST( GET QDACCO_VERSIONS 2 QDACCO_VERSION_PATCH)

# ######### General setup ##########
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
find_package(Qt4 REQUIRED) 

########### qdacco core ##########
message(STATUS "Working on qdacco lib")
add_subdirectory(core)

########### qdacco gui ##########
message(STATUS "Working on qdacco gui")
add_subdirectory(gui)

########### qdacco text ##########
message(STATUS "Working on qdacco text")
add_subdirectory(text)


