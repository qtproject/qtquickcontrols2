# Generated from chapter2-lists.pro.

cmake_minimum_required(VERSION 3.14)
project(chapter2-lists LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quickcontrols2/chattutorial/chapter2-lists")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Qml)
find_package(Qt6 COMPONENTS Quick)

qt_add_executable(chapter2-lists
    main.cpp
)
set_target_properties(chapter2-lists PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(chapter2-lists PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)


# Resources:
set(qml_resource_files
    "main.qml"
)

qt6_add_resources(chapter2-lists "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)
set(shared_resource_files
    "../shared/Albert_Einstein.png"
    "../shared/Albert_Einstein@2x.png"
    "../shared/Albert_Einstein@3x.png"
    "../shared/Albert_Einstein@4x.png"
    "../shared/Ernest_Hemingway.png"
    "../shared/Ernest_Hemingway@2x.png"
    "../shared/Ernest_Hemingway@3x.png"
    "../shared/Ernest_Hemingway@4x.png"
    "../shared/Hans_Gude.png"
    "../shared/Hans_Gude@2x.png"
    "../shared/Hans_Gude@3x.png"
    "../shared/Hans_Gude@4x.png"
)

qt6_add_resources(chapter2-lists "shared"
    PREFIX
        "/"
    BASE
        "../shared"
    FILES
        ${shared_resource_files}
)

install(TARGETS chapter2-lists
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
