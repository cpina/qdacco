#qdaccolib

#qdaccolib needs QtXml
set(QT_USE_QTXML true)

set(QT_DONT_USE_QTNETWORK true)
set(QT_DONT_USE_QTGUI  true)

INCLUDE(${QT_USE_FILE})

set(qdaccolib_SRCS auxiliar.cpp 
			StructureList.cpp  StructureParser.cpp
			worddata.cpp)

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
QT4_ADD_RESOURCES(qdaccolib_RCC_SRCS ${qdaccolib_RCCS})

# generate rules for building source files that moc generates

#ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_SHARED)
# build sources, moc'd sources, and rcc'd sources

add_library(qdaccolib SHARED ${qdaccolib_MOC_SRCS} ${qdaccolib_UIS_H}
	${qdaccolib_SRCS} ${qdaccolib_MOCS} ${qdaccolib_RCC_SRCS})

set_target_properties( qdaccolib PROPERTIES 
  SOVERSION "${QDACCO_VERSION_MAJOR}.${QDACCO_VERSION_MINOR}"
  VERSION "${QDACCO_VERSION}")

target_link_libraries( qdaccolib ${QT_LIBRARIES})

install_targets(/lib qdaccolib)
