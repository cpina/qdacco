###########################################
# textqdacco					  #
###########################################

set (textqdacco_SRC textdacco.cpp)
#file(GLOB textqdacco_MOCS *.hpp *.h)
#file(GLOB textqdacco_UIS *.ui)

set(textqdacco_MOCS textdacco.h)

set(QT_USE_QTXML true)
set(QT_USE_GUI false)

INCLUDE(   ${QT_USE_FILE}   )

include_directories(
    ${QT_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_BINARY_DIR}/core/
	${CMAKE_SOURCE_DIR}/core/
	${CMAKE_BINARY_DIR}/text/
	${CMAKE_SOURCE_DIR}/text/)

# generate rules for building source files from the resources
#

# generate rules for building source files that moc generates
#QT4_WRAP_UI(textqdacco_UIS_H ${textqdacco_UIS})
QT4_WRAP_CPP(textqdacco_MOC_SRCS ${textqdacco_MOCS})

#QT4_ADD_RESOURCES(plugin_RCC_SRCS ${plugin_RCCS})


#ADD_DEFINITIONS(${QT_DEFINITIONS})
#ADD_DEFINITIONS(-DQT_SHARED)
# build sources, moc'd sources, and rcc'd sources
# # generate rules for building source files from the resources
# build sources, moc'd sources, and rcc'd sources
add_executable(textqdacco   ${textqdacco_MOCS} ${textqdacco_MOC_SRCS} ${textqdacco_UIS_H}
	${textqdacco_SRC} ${textqdacco_SRCS} )

target_link_libraries( textqdacco qdaccolib ${QT_LIBRARIES})

add_dependencies(textqdacco qdaccolib)

install_targets(/bin textqdacco)	

