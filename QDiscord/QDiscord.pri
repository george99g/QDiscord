include(config.pri)

SOURCES += $$PWD/src/qdiscord.d/qdiscord.cpp \
    $$PWD/src/qdiscord.d/qdiscordutilities.cpp \
    $$PWD/src/qdiscord.d/qdiscordguild.cpp \
    $$PWD/src/qdiscord.d/qdiscorduser.cpp \
    $$PWD/src/qdiscord.d/qdiscordchannel.cpp \
    $$PWD/src/qdiscord.d/qdiscordmember.cpp \
    $$PWD/src/qdiscord.d/qdiscordmessage.cpp \
    $$PWD/src/qdiscord.d/qdiscordgame.cpp \
    $$PWD/src/qdiscord.d/qdiscordroute.cpp \
    $$PWD/src/qdiscord.d/qdiscordtoken.cpp \
    $$PWD/src/qdiscord.d/qdiscordid.cpp \
    $$PWD/src/qdiscord.d/qdiscorddiscriminator.cpp \
    $$PWD/src/qdiscord.d/qdiscordstate.cpp \
    $$PWD/src/qdiscord.d/qdiscordabstractstate.cpp \
    $$PWD/src/qdiscord.d/qdiscordws.cpp \
    $$PWD/src/qdiscord.d/qdiscordrest.cpp \
    $$PWD/src/qdiscord.d/qdiscorduseragent.cpp \
    $$PWD/src/qdiscord.d/qdiscordbucket.cpp \
    $$PWD/src/qdiscord.d/qdiscordjsondecoder.cpp \
    $$PWD/src/qdiscord.d/qdiscordattachment.cpp \
    $$PWD/src/qdiscord.d/qdiscordpermission.cpp \
    $$PWD/src/qdiscord.d/qdiscordpermissionoverwrite.cpp \
    $$PWD/src/qdiscord.d/qdiscordrole.cpp

TOPHEADERS += $$PWD/src/QDiscord \
              $$PWD/src/QDiscordRest \
              $$PWD/src/QDiscordState \
              $$PWD/src/QDiscordWs

DIRHEADERS += $$PWD/src/qdiscord.d/qdiscord.hpp \
    $$PWD/src/qdiscord.d/qdiscordutilities.hpp \
    $$PWD/src/qdiscord.d/qdiscordguild.hpp \
    $$PWD/src/qdiscord.d/qdiscorduser.hpp \
    $$PWD/src/qdiscord.d/qdiscordchannel.hpp \
    $$PWD/src/qdiscord.d/qdiscordmember.hpp \
    $$PWD/src/qdiscord.d/qdiscordmessage.hpp \
    $$PWD/src/qdiscord.d/qdiscordgame.hpp \
    $$PWD/src/qdiscord.d/qdiscordroute.hpp \
    $$PWD/src/qdiscord.d/qdiscordtoken.hpp \
    $$PWD/src/qdiscord.d/qdiscordid.hpp \
    $$PWD/src/qdiscord.d/qdiscorddiscriminator.hpp \
    $$PWD/src/qdiscord.d/qdiscordstate.hpp \
    $$PWD/src/qdiscord.d/qdiscordabstractstate.hpp \
    $$PWD/src/qdiscord.d/qdiscordws.hpp \
    $$PWD/src/qdiscord.d/qdiscordrest.hpp \
    $$PWD/src/qdiscord.d/qdiscorduseragent.hpp \
    $$PWD/src/qdiscord.d/qdiscordbucket.hpp \
    $$PWD/src/qdiscord.d/qdiscordjsondecoder.hpp \
    $$PWD/src/qdiscord.d/qdiscordattachment.hpp \
    $$PWD/src/qdiscord.d/qdiscordpermission.hpp \
    $$PWD/src/qdiscord.d/qdiscordpermissionoverwrite.hpp \
    $$PWD/src/qdiscord.d/qdiscordrole.hpp

LIBOPTIONALHEADERS += $$PWD/src/qdiscord.d/external/Optional/optional.hpp

HEADERS += $$TOPHEADERS \
    $$DIRHEADERS \
    $$EXTERNALHEADERS \
    $$LIBOPTIONALHEADERS

INCLUDEPATH += $$PWD/src

