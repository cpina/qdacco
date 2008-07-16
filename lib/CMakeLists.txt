#qdaccolib
SET( QDACCO_LIB_VERSION 0.7.0 )

#qdaccolib needs QtXml
set(QT_USE_QTXML true)

set(QT_DONT_USE_QTNETWORK true)
set(QT_DONT_USE_QTGUI  true)


STRING( REGEX MATCHALL "[0-9]+" QDACCO_LIB_VERSIONS ${QDACCO_LIB_VERSION} )
LIST( GET QDACCO_LIB_VERSIONS 0 QDACCO_LIB_VERSION_MAJOR)
LIST( GET QDACCO_LIB_VERSIONS 1 QDACCO_LIB_VERSION_MINOR)
LIST( GET QDACCO_LIB_VERSIONS 2 QDACCO_LIB_VERSION_PATCH)



INCLUDE(${QT_USE_FILE})

set(qdaccolib_SRCS auxiliar.cpp 
			StructureList.cpp  StructureParser.cpp
			worddata.cpp)

set(qdacco_HDRS qdacco/auxiliar.h qdacco/StructureList.h
qdacco/StructureParser.h qdacco/worddata.h)


set(qdaccolib_MOCS)

#not moc'ed 
#auxiliar.h StructureList.h StructureParser.h worddata.h


#set(qdaccolib_RCCS ../../qdaccolib.qrc)
#set(qdaccolib_UIS )

include_directories(
    ${QT_INCLUDE_DIR}
	${QT_QTXML_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/core/
	${CMAKE_CURRENT_BINARY_DIR}/core/)
	
# generate rules for building source files from the resources
#QT4_WRAP_UI(qdaccolib_UIS_H ${qdaccolib_UIS})
QT4_WRAP_CPP(qdaccolib_MOC_SRCS ${qdaccolib_MOCS})
#QT4_ADD_RESOURCES(qdaccolib_RCC_SRCS ${qdaccolib_RCCS})

# generate rules for building source files that moc generates

#ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_SHARED)
# build sources, moc'd sources, and rcc'd sources

add_library(qdaccolib SHARED ${qdaccolib_MOC_SRCS} ${qdaccolib_UIS_H}
	${qdaccolib_SRCS} ${qdaccolib_MOCS} ${qdaccolib_RCC_SRCS})

set_target_properties( qdaccolib PROPERTIES 
  SOVERSION "${QDACCO_LIB_VERSION_MAJOR}.${QDACCO_LIB_VERSION_MINOR}"
  VERSION "${QDACCO_LIB_VERSION}")

#Remember to correct this to have a libqdacco
#  OUTPUT_NAME qdacco )


target_link_libraries( qdaccolib ${QT_LIBRARIES})

install_targets(/lib qdaccolib)
install (FILES ${qdacco_HDRS} DESTINATION include/qdacco)

