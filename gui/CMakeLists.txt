###########################################
# qdaccogui					  #
###########################################

set (qdaccogui_SRC configure.cpp main.cpp
	   qdacco.cpp about.cpp
	   suggeriment.cpp 
	   mylineedit.cpp 
	   mylistwidget.cpp auxiliargui.cpp connection.cpp)

set (qdaccogui_MOCS configure.h main.h 
		about.h suggeriment.h 
	   textbrowser.h mylineedit.h 
	   mylistwidget.h auxiliargui.h connection.h)

set (qdaccogui_UIS configure.ui main.ui about.ui suggeriment.ui)

set(QT_USE_QTXML true)
set(QT_USE_QTNETWORK true) 

INCLUDE(   ${QT_USE_FILE}   )

include_directories(
    ${QT_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_BINARY_DIR}/core/
	${CMAKE_SOURCE_DIR}/core/
	${CMAKE_BINARY_DIR}/gui/
	${CMAKE_SOURCE_DIR}/gui/)

# generate rules for building source files from the resources
#
set(qdaccogui_RCCS icons.qrc translation.qrc)
# generate rules for building source files that moc generates
QT4_WRAP_UI(qdaccogui_UIS_H ${qdaccogui_UIS})
QT4_WRAP_CPP(qdaccogui_MOC_SRCS ${qdaccogui_MOCS})

QT4_ADD_RESOURCES(qdaccogui_RCC_SRCS ${qdaccogui_RCCS})


#ADD_DEFINITIONS(${QT_DEFINITIONS})
#ADD_DEFINITIONS(-DQT_SHARED)
# build sources, moc'd sources, and rcc'd sources
# # generate rules for building source files from the resources
# build sources, moc'd sources, and rcc'd sources
add_executable(qdacco  ${qdaccogui_MOCS} ${qdaccogui_MOC_SRCS} ${qdaccogui_UIS_H}
	${qdaccogui_SRC} ${qdaccogui_SRCS} )

target_link_libraries( qdacco qdaccolib ${QT_LIBRARIES})

add_dependencies(qdacco qdaccolib)

install_targets(/bin qdacco)	

