###########################################
# qdaccogui					  #
###########################################

set (qdaccogui_SRC Configure.cpp main.cpp
	   qdacco.cpp About.cpp LineEdit.cpp 
	   ListWidget.cpp AuxiliarGUI.cpp OneInstance.cpp
	   TrayIcon.cpp LoadConfig.cpp TextBrowser.cpp
       ../nongui/Auxiliar.cpp
       ../nongui/StructureList.cpp
       ../nongui/StructureParser.cpp
       ../nongui/WordData.cpp
    )

set (qdaccogui_MOCS Configure.h main.h 
	   About.h TextBrowser.h LineEdit.h 
	   ListWidget.h OneInstance.h
	   TrayIcon.h LoadConfig.h TextBrowser.h)

set (qdaccogui_H AuxiliarGUI.h
     ../nongui/Auxiliar.h
     ../nongui/StructureList.h
     ../nongui/StructureParser.h
     ../nongui/WordData.h
   )

set (qdaccogui_UIS Configure.ui main.ui About.ui)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6Gui REQUIRED)
find_package(Qt6Network REQUIRED)
find_package(Qt6Xml REQUIRED)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR})

# generate rules for building source files from the resources
#
set(qdaccogui_RCCS icons.qrc translation.qrc)
# generate rules for building source files that moc generates

QT6_WRAP_UI(qdaccogui_UIS_H ${qdaccogui_UIS})
#QT5_WRAP_CPP(${qdaccogui_MOCS})

QT6_ADD_RESOURCES(qdaccogui_RCC_SRCS ${qdaccogui_RCCS})

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

#qt6_use_modules(qdacco Widgets)

target_link_libraries( qdacco ${QT6_LIBRARIES})

install_targets(/bin qdacco)	

