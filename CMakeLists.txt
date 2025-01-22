cmake_minimum_required(VERSION 3.16)

project(SodarkCalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wunreachable-code -Werror)

# add dependencies
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.1.2")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        utility.h
        sodark.h
)

qt_add_executable(SodarkCalc MANUAL_FINALIZATION ${SOURCES})

target_link_libraries(SodarkCalc PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    fmt::fmt
)

set_target_properties(SodarkCalc PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SodarkCalc)
endif()
