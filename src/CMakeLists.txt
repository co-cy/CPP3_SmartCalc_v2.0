cmake_minimum_required(VERSION 3.0)
project(SmartCalc_v2.0 VERSION 2 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core PrintSupport)

include_directories(libs/qcustomplot)

add_library(libQCustomPlot
    libs/qcustomplot/qcustomplot.cpp
    libs/qcustomplot/qcustomplot.h
    )
target_link_libraries(libQCustomPlot PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::PrintSupport)

set(PROJECT_SOURCES
    view/calculator2.ui
    main.cpp
    view/calculator2.cpp
    view/calculator2.h
    controllers/controller.h models/expression.cpp models/expression.h models/polish.cpp models/polish.h models/lexeme.h models/deposit.h)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(SmartCalc_v2.0
      MANUAL_FINALIZATION
      ${PROJECT_SOURCES}
      )
  # Define target properties for Android with Qt 6 as:
  #    set_property(TARGET SmartCalc_v2.0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
  # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
  if (ANDROID)
    add_library(SmartCalc_v2.0 SHARED
        ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else ()
    add_executable(SmartCalc_v2.0
        ${PROJECT_SOURCES}
        )
  endif ()
endif ()

target_link_libraries(SmartCalc_v2.0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets libQCustomPlot)

set_target_properties(SmartCalc_v2.0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    )

if (QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(SmartCalc_v2.0)
endif ()
