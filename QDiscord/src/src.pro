QT       += network websockets
QT       -= gui

TARGET = QDiscord
TEMPLATE = lib
CONFIG += c++11

DEFINES += QDISCORD_LIBRARY
CONFIG(static) {
    DEFINES += QDISCORD_STATIC
    CONFIG += staticlib
}

SOURCES += qdiscord.d/qdiscord.cpp \
    qdiscord.d/qdiscordrestcomponent.cpp \
    qdiscord.d/qdiscordutilities.cpp \
    qdiscord.d/qdiscordwscomponent.cpp \
    qdiscord.d/qdiscordstatecomponent.cpp \
    qdiscord.d/qdiscordguild.cpp \
    qdiscord.d/qdiscorduser.cpp \
    qdiscord.d/qdiscordchannel.cpp \
    qdiscord.d/qdiscordmember.cpp \
    qdiscord.d/qdiscordmessage.cpp \
    qdiscord.d/qdiscordgame.cpp
    
TOPHEADERS += QDiscord

DIRHEADERS += qdiscord.d/qdiscord.hpp \
    qdiscord.d/qdiscord_global.hpp \
    qdiscord.d/qdiscordrestcomponent.hpp \
    qdiscord.d/qdiscordutilities.hpp \
    qdiscord.d/qdiscordwscomponent.hpp \
    qdiscord.d/qdiscordstatecomponent.hpp \
    qdiscord.d/qdiscordguild.hpp \
    qdiscord.d/qdiscorduser.hpp \
    qdiscord.d/qdiscordchannel.hpp \
    qdiscord.d/qdiscordmember.hpp \
    qdiscord.d/qdiscordmessage.hpp \
    qdiscord.d/qdiscordgame.hpp
    
HEADERS += $$TOPHEADERS \
    $$DIRHEADERS 

isEmpty(PREFIX) {
    PREFIX=/usr
} else {
    equals(PREFIX, "/") {
        PREFIX=""
    }
}

unix | mingw {
    target.path = $$PREFIX/lib
    topheaders.files = $$TOPHEADERS
    topheaders.path = $$PREFIX/include
    dirheaders.files = $$DIRHEADERS
    dirheaders.path = $$PREFIX/include/qdiscord.d
    INSTALLS += target topheaders dirheaders
}
