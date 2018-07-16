cmake_minimum_required(VERSION 3.0)

project(QDiscord)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 5.8 COMPONENTS Core Network WebSockets REQUIRED)

set(SOURCES
    src/qdiscord.cpp
    src/qdiscordabstractstate.cpp
    src/qdiscordattachment.cpp
    src/qdiscordbucket.cpp
    src/qdiscordchannel.cpp
    src/qdiscorddiscriminator.cpp
    src/qdiscordgame.cpp
    src/qdiscordguild.cpp
    src/qdiscordid.cpp
    src/qdiscordjsondecoder.cpp
    src/qdiscordmember.cpp
    src/qdiscordmessage.cpp
    src/qdiscordpermission.cpp
    src/qdiscordpermissionoverwrite.cpp
    src/qdiscordrest.cpp
    src/qdiscordrole.cpp
    src/qdiscordroute.cpp
    src/qdiscordstate.cpp
    src/qdiscordtoken.cpp
    src/qdiscorduser.cpp
    src/qdiscorduseragent.cpp
    src/qdiscordutilities.cpp
    src/qdiscordws.cpp
)

set(HEADERS
    include/QDiscord
    include/QDiscordRest
    include/QDiscordState
    include/QDiscordWs
    include/qdiscord.d/qdiscord.hpp
    include/qdiscord.d/qdiscordabstractstate.hpp
    include/qdiscord.d/qdiscordattachment.hpp
    include/qdiscord.d/qdiscordbucket.hpp
    include/qdiscord.d/qdiscordchannel.hpp
    include/qdiscord.d/qdiscorddiscriminator.hpp
    include/qdiscord.d/qdiscordgame.hpp
    include/qdiscord.d/qdiscordguild.hpp
    include/qdiscord.d/qdiscordid.hpp
    include/qdiscord.d/qdiscordjsondecoder.hpp
    include/qdiscord.d/qdiscordmember.hpp
    include/qdiscord.d/qdiscordmessage.hpp
    include/qdiscord.d/qdiscordpermission.hpp
    include/qdiscord.d/qdiscordpermissionoverwrite.hpp
    include/qdiscord.d/qdiscordrest.hpp
    include/qdiscord.d/qdiscordrole.hpp
    include/qdiscord.d/qdiscordroute.hpp
    include/qdiscord.d/qdiscordstate.hpp
    include/qdiscord.d/qdiscordtoken.hpp
    include/qdiscord.d/qdiscorduser.hpp
    include/qdiscord.d/qdiscorduseragent.hpp
    include/qdiscord.d/qdiscordutilities.hpp
    include/qdiscord.d/qdiscordws.hpp
    include/qdiscord.d/external/optional/optional.hpp
)

add_library(qdiscord STATIC ${SOURCES} ${HEADERS})

target_include_directories(qdiscord PRIVATE include)

target_include_directories(qdiscord PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(qdiscord PUBLIC Qt5::Core Qt5::Network Qt5::WebSockets)

set_target_properties(qdiscord PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)

include(config.cmake)

include(doc/doc.cmake)

install(TARGETS qdiscord EXPORT qdiscord-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(
    DIRECTORY include/
    DESTINATION include
)

include(cmake/config-package.cmake)

include(cmake/cpack-package.cmake)
