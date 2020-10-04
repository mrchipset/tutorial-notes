cmake_minimum_required(VERSION 3.0.0)
project(D2DWidget VERSION 0.1.0)

# include(CTest)
# enable_testing()

# include text specifications
include(Specifications.txt)
set(CMAKE_BUILD_TYPE "Debug")


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_definitions(-w)

find_package(Qt5 COMPONENTS Core Concurrent Widgets Script REQUIRED)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

aux_source_directory(. DIR_SRCS)
aux_source_directory(Widgets DIR_WIDGET_SRCS)
qt5_wrap_ui(UI_FILES UI/mainwindow.ui)

add_executable(${PROJECT_NAME} 
    ${DIR_SRCS} 
    ${DIR_WIDGET_SRCS}
    ${UI_FILES})
    
target_link_libraries(${PROJECT_NAME}
                        Qt5::Core
                        Qt5::Concurrent
                        Qt5::Widgets
                        Qt5::Script
                        d2d1)
