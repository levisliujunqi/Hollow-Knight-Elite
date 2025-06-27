cmake_minimum_required(VERSION 3.16)

project(game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        uicontroller.h uicontroller.cpp
        customgraphicsview.h customgraphicsview.cpp
        keypresseater.h keypresseater.cpp
        beginscene.cpp
        beginscene.h

        playscene.cpp
        playscene.h
        Level.cpp
        Level.h
        Player.cpp
        Player.h
        character.h character.cpp
        enemy.h enemy.cpp
        res.qrc
        scene.h scene.cpp
        endscene.h endscene.cpp
        busystateinfo.h busystateinfo.cpp
        grounds.h grounds.cpp
        elements.h elements.cpp
        attackeffect.h attackeffect.cpp
        playerattackeffect.h playerattackeffect.cpp
        busymovestateinfo.h busymovestateinfo.cpp
        gate.h gate.cpp
        failscene.cpp
        failscene.h
        enemy1.h enemy1.cpp
        boss.h boss.cpp
        sqlitedb.h sqlitedb.cpp
        hitnum.h hitnum.cpp
        addblood.h addblood.cpp
        playerinfo.h playerinfo.cpp




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET game APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(game SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(game
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(game PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Sql
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.game)
endif()
set_target_properties(game PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game)
endif()
