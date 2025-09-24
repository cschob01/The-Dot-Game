cmake_minimum_required(VERSION 3.16)

project(dotGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to Qt 6 installation if needed
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@6/lib/cmake/Qt6")

# Find Qt6 modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia Quick)

message(STATUS "Found Qt6 version: ${Qt6_VERSION}")

# Define sources and headers
set(SOURCES
    main.cpp
    mainwindow.cpp
    savegame.cpp
    music.cpp
    tittlepage.cpp
    tutorialpage.cpp
    levelselect.cpp
    levelmap.cpp
    creditspage.cpp
    settingspage.cpp
    dotfield.cpp
    dotfield_essencials.cpp
    dotfield_display.cpp
    map.cpp
    effects.cpp
    map_maker.cpp
    beam.cpp
    overlay.cpp
    map1.cpp
)

set(HEADERS
    mainwindow.h
    savegame.h
    music.h
    tittlepage.h
    tutorialpage.h
    levelselect.h
    levelmap.h
    creditspage.h
    settingspage.h
    settings.h
    dotfield.h
    map.h
    effects.h
    beam.h
    overlay.h
    map1.h
    maps/mapsorter.h
    maps/map1_1.h
    maps/map1_2.h
    maps/map1_3.h
    maps/map1_4.h
    maps/map1_5.h
    maps/map2_1.h
    maps/map2_2.h
    maps/map2_3.h
    maps/map2_4.h
    maps/map2_5.h
    maps/map3_1.h
    maps/map3_2.h
    maps/map3_3.h
    maps/map3_4.h
    maps/map3_5.h
    maps/map4_1.h
    maps/map4_2.h
    maps/map4_3.h
    maps/map4_4.h
    maps/map4_5.h
    maps/map5_1.h
    maps/map5_2.h
    maps/map5_3.h
    maps/map5_4.h
    maps/map5_5.h
    maps/map6_1.h
)

set(RESOURCES
    resources.qrc
)

# Add the Qt resource file (this will automatically handle adding it to SOURCES)
qt6_add_resources(RESOURCES resources.qrc)

qt6_add_executable(dotGame MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
    resources/icons/DotGameIcon.icns
)

# Link required Qt libraries
target_link_libraries(dotGame
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
)

set_source_files_properties(resources/icons/DotGameIcon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

set_target_properties(dotGame PROPERTIES
    AUTOMOC ON
    MACOSX_BUNDLE_BUNDLE_NAME "The Dot Game"
    OUTPUT_NAME "The Dot Game"
    MACOSX_BUNDLE_GUI_IDENTIFIER com.carlos.dotgame
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/Info.plist
    MACOSX_BUNDLE_ICON_FILE DotGameIcon.icns
)
