set(SOURCES
    src/discordtoken.cpp
    src/discorduseragent.cpp
    src/qdiscordqml.cpp
)

set(HEADERS
    include/discordtoken.hpp
    include/discorduseragent.hpp
    include/qdiscordqml.hpp
)

set(QMLDIR_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/qmldir"
)

set(QML_FILES
)

find_package(Qt5 COMPONENTS Qml REQUIRED)

add_library(qdiscord-qml SHARED ${SOURCES} ${HEADERS})

set_target_properties(qdiscord-qml PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)

set_target_properties(qdiscord-qml PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/imports/QDiscord"
)

add_custom_command(TARGET qdiscord-qml POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${QMLDIR_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/imports/QDiscord/qmldir"
)

target_include_directories(
    qdiscord-qml PUBLIC include
)

target_link_libraries(qdiscord-qml PUBLIC Qt5::Qml qdiscord)


