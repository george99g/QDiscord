QT       += network websockets
QT       -= gui

TARGET = QDiscord
TEMPLATE = lib
CONFIG += staticlib c++11

isEmpty(PREFIX) {
    PREFIX=/usr
} else {
    equals(PREFIX, "/") {
        PREFIX=""
    }
}

include(../config.pri)

SOURCES += $$PWD/qdiscord.d/qdiscord.cpp \
    $$PWD/qdiscord.d/qdiscordutilities.cpp \
    $$PWD/qdiscord.d/qdiscordguild.cpp \
    $$PWD/qdiscord.d/qdiscorduser.cpp \
    $$PWD/qdiscord.d/qdiscordchannel.cpp \
    $$PWD/qdiscord.d/qdiscordmember.cpp \
    $$PWD/qdiscord.d/qdiscordmessage.cpp \
    $$PWD/qdiscord.d/qdiscordgame.cpp \
    $$PWD/qdiscord.d/qdiscordroute.cpp \
    $$PWD/qdiscord.d/qdiscordtoken.cpp \
    $$PWD/qdiscord.d/qdiscordid.cpp \
    $$PWD/qdiscord.d/qdiscorddiscriminator.cpp \
    $$PWD/qdiscord.d/qdiscordstate.cpp \
    $$PWD/qdiscord.d/qdiscordabstractstate.cpp \
    $$PWD/qdiscord.d/qdiscordws.cpp \
    $$PWD/qdiscord.d/qdiscordrest.cpp \
    $$PWD/qdiscord.d/qdiscorduseragent.cpp \
    $$PWD/qdiscord.d/qdiscordbucket.cpp \
    $$PWD/qdiscord.d/qdiscordjsondecoder.cpp \
    $$PWD/qdiscord.d/qdiscordattachment.cpp \
    $$PWD/qdiscord.d/qdiscordpermission.cpp

TOPHEADERS += $$PWD/QDiscord \
              $$PWD/QDiscordRest \
              $$PWD/QDiscordState \
              $$PWD/QDiscordWs

DIRHEADERS += $$PWD/qdiscord.d/qdiscord.hpp \
    $$PWD/qdiscord.d/qdiscordutilities.hpp \
    $$PWD/qdiscord.d/qdiscordguild.hpp \
    $$PWD/qdiscord.d/qdiscorduser.hpp \
    $$PWD/qdiscord.d/qdiscordchannel.hpp \
    $$PWD/qdiscord.d/qdiscordmember.hpp \
    $$PWD/qdiscord.d/qdiscordmessage.hpp \
    $$PWD/qdiscord.d/qdiscordgame.hpp \
    $$PWD/qdiscord.d/qdiscordroute.hpp \
    $$PWD/qdiscord.d/qdiscordtoken.hpp \
    $$PWD/qdiscord.d/qdiscordid.hpp \
    $$PWD/qdiscord.d/qdiscorddiscriminator.hpp \
    $$PWD/qdiscord.d/qdiscordstate.hpp \
    $$PWD/qdiscord.d/qdiscordabstractstate.hpp \
    $$PWD/qdiscord.d/qdiscordws.hpp \
    $$PWD/qdiscord.d/qdiscordrest.hpp \
    $$PWD/qdiscord.d/qdiscorduseragent.hpp \
    $$PWD/qdiscord.d/qdiscordbucket.hpp \
    $$PWD/qdiscord.d/qdiscordjsondecoder.hpp \
    $$PWD/qdiscord.d/qdiscordattachment.hpp \
    $$PWD/qdiscord.d/qdiscordpermission.hpp

LIBOPTIONALHEADERS += $$PWD/qdiscord.d/external/Optional/optional.hpp

HEADERS += $$TOPHEADERS \
    $$DIRHEADERS \
    $$EXTERNALHEADERS \
    $$LIBOPTIONALHEADERS

unix {
    target.path = $$PREFIX/lib
    topheaders.files = $$TOPHEADERS
    topheaders.path = $$PREFIX/include
    dirheaders.files = $$DIRHEADERS
    dirheaders.path = $$PREFIX/include/qdiscord.d
    externalheaders.files = $$EXTERNALHEADERS
    externalheaders.path = $$PREFIX/include/qdiscord.d/external
    liboptionalheaders.files = $$LIBOPTIONALHEADERS
    liboptionalheaders.path = $$PREFIX/include/qdiscord.d/external/Optional
    INSTALLS += target topheaders dirheaders externalheaders liboptionalheaders
}
