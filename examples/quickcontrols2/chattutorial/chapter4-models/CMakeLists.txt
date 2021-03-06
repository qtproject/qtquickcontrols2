# Generated from chapter4-models.pro.

cmake_minimum_required(VERSION 3.14)
project(chapter4-models LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quickcontrols2/chattutorial/chapter4-models")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Qml)
find_package(Qt6 COMPONENTS Quick)
find_package(Qt6 COMPONENTS Sql)

qt_add_executable(chapter4-models
    main.cpp
    sqlcontactmodel.cpp sqlcontactmodel.h
    sqlconversationmodel.cpp sqlconversationmodel.h
)
set_target_properties(chapter4-models PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(chapter4-models PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::Sql
)


# Resources:
set(qml_resource_files
    "ContactPage.qml"
    "ConversationPage.qml"
    "main.qml"
)

qt6_add_resources(chapter4-models "qml"
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

qt6_add_resources(chapter4-models "shared"
    PREFIX
        "/"
    BASE
        "../shared"
    FILES
        ${shared_resource_files}
)

install(TARGETS chapter4-models
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
