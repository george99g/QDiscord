include(../config.pri)

SOURCES += $$PWD/qdiscord.d/qdiscord.cpp \
    $$PWD/qdiscord.d/qdiscordrestcomponent.cpp \
    $$PWD/qdiscord.d/qdiscordutilities.cpp \
    $$PWD/qdiscord.d/qdiscordwscomponent.cpp \
    $$PWD/qdiscord.d/qdiscordstatecomponent.cpp \
    $$PWD/qdiscord.d/qdiscordguild.cpp \
    $$PWD/qdiscord.d/qdiscorduser.cpp \
    $$PWD/qdiscord.d/qdiscordchannel.cpp \
    $$PWD/qdiscord.d/qdiscordmember.cpp \
    $$PWD/qdiscord.d/qdiscordmessage.cpp \
    $$PWD/qdiscord.d/qdiscordgame.cpp \
    $$PWD/qdiscord.d/qdiscordroute.cpp \
    $$PWD/qdiscord.d/qdiscordtoken.cpp \
    $$PWD/qdiscord.d/qdiscordid.cpp \
    $$PWD/qdiscord.d/qdiscorddiscriminator.cpp

TOPHEADERS += $$PWD/QDiscord

DIRHEADERS += $$PWD/qdiscord.d/qdiscord.hpp \
    $$PWD/qdiscord.d/qdiscordrestcomponent.hpp \
    $$PWD/qdiscord.d/qdiscordutilities.hpp \
    $$PWD/qdiscord.d/qdiscordwscomponent.hpp \
    $$PWD/qdiscord.d/qdiscordstatecomponent.hpp \
    $$PWD/qdiscord.d/qdiscordguild.hpp \
    $$PWD/qdiscord.d/qdiscorduser.hpp \
    $$PWD/qdiscord.d/qdiscordchannel.hpp \
    $$PWD/qdiscord.d/qdiscordmember.hpp \
    $$PWD/qdiscord.d/qdiscordmessage.hpp \
    $$PWD/qdiscord.d/qdiscordgame.hpp \
    $$PWD/qdiscord.d/qdiscordroute.hpp \
    $$PWD/qdiscord.d/qdiscordtoken.hpp \
    $$PWD/qdiscord.d/qdiscordid.hpp \
    $$PWD/qdiscord.d/qdiscorddiscriminator.hpp

HEADERS += $$TOPHEADERS \
    $$DIRHEADERS
