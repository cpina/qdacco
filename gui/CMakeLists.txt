###########################################
# qdaccogui					  #
###########################################

set (qdaccogui_SRC configure.cpp main.cpp
	   qdacco.cpp about.cpp suggeriment.cpp mylineedit.cpp 
	   mylistwidget.cpp AuxiliarGUI.cpp connection.cpp oneinstance.cpp
	   trayicon.cpp loadconfig.cpp
       ../nongui/auxiliar.cpp
       ../nongui/StructureList.cpp
       ../nongui/StructureParser.cpp
       ../nongui/worddata.cpp
    )

set (qdaccogui_MOCS configure.h main.h 
	   about.h suggeriment.h textbrowser.h mylineedit.h 
	   mylistwidget.h connection.h oneinstance.h
	   trayicon.h loadconfig.h)

set (qdaccogui_H AuxiliarGUI.h
     ../nongui/auxiliar.h
     ../nongui/StructureList.h
     ../nongui/StructureParser.h
     ../nongui/worddata.h
   )

set (qdaccogui_UIS configure.ui main.ui about.ui suggeriment.ui)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus REQUIRED)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR})

# generate rules for building source files from the resources
#
set(qdaccogui_RCCS icons.qrc translation.qrc)
# generate rules for building source files that moc generates

QT5_WRAP_UI(qdaccogui_UIS_H ${qdaccogui_UIS})
#QT5_WRAP_CPP(${qdaccogui_MOCS})

QT5_ADD_RESOURCES(qdaccogui_RCC_SRCS ${qdaccogui_RCCS})

# Suggeriment CMake 2.6
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

configure_file(
	CMakeOptions.h.cmake
	CMakeOptions.h
)

# build sources, moc'd sources, and rcc'd sources
# # generate rules for building source files from the resources
# build sources, moc'd sources, and rcc'd sources
add_executable(qdacco  ${qdaccogui_H} ${qdaccogui_MOCS} ${qdaccogui_MOC_SRCS} ${qdaccogui_UIS_H}
	${qdaccogui_SRC} ${qdaccogui_SRCS} ${qdaccogui_RCC_SRCS})

qt5_use_modules(qdacco Widgets)

target_link_libraries( qdacco ${Qt5Xml_LIBRARIES} ${Qt5DBus_LIBRARIES})

install_targets(/bin qdacco)	

