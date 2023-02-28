TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += console precompile_header

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

PRECOMPILED_HEADER = Source_Files/pch.h

SOURCES += \
    Components/animationcomponent.cpp \
    Components/attributecomponent.cpp \
    Components/hitboxcomponent.cpp \
    Components/movementcomponent.cpp \
    Entities/enemy.cpp \
    Entities/entity.cpp \
    GUI/pausemenu.cpp \
    GUI/playergui.cpp \
    Map/tilemap.cpp \
    Resource_Files/graphicssettings.cpp \
    Resource_Files/gui.cpp \
    States/editorstate.cpp \
        States/gamestate.cpp \
    States/mainmenustate.cpp \
    States/settingsstate.cpp \
        States/state.cpp \
        Source_Files/game.cpp \
        Source_Files/main.cpp \
    Entities/player.cpp \
    Tile/tile.cpp

HEADERS += \
    Components/animationcomponent.h \
    Components/attributecomponent.h \
    Components/hitboxcomponent.h \
    Components/movementcomponent.h \
    Entities/enemy.h \
    Entities/entity.h \
    GUI/pausemenu.h \
    GUI/playergui.h \
    Map/tilemap.h \
    Resource_Files/graphicssettings.h \
    Resource_Files/gui.h \
    Source_Files/pch.h \
    States/editorstate.h \
    States/gamestate.h \
    States/mainmenustate.h \
    States/settingsstate.h \
    States/state.h \
    Source_Files/game.h \
    Entities/player.h \
    Tile/tile.h
