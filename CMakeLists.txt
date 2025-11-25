cmake_minimum_required(VERSION 3.16)

project(mlolv2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Network REQUIRED)

qt_add_executable(appmlolv2
    main.cpp
)

qt_add_qml_module(appmlolv2
    URI "Mastery"
    VERSION 1.0
    QML_FILES
        "Main.qml"

    SOURCES
        riotapi.h
        riotapi.cpp
)

set_target_properties(appmlolv2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appmlolv2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appmlolv2
    PRIVATE Qt6::Quick Qt6::Network)

include(GNUInstallDirs)
install(TARGETS appmlolv2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
