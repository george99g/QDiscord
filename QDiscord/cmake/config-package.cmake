set(CONFIG_PACKAGE_LOCATION "lib/cmake/${PROJECT_NAME}")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/qdiscord-config-version.cmake"
    VERSION ${QDISCORD_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(cmake/qdiscord-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/qdiscord-config.cmake"
    INSTALL_DESTINATION "${CONFIG_PACKAGE_LOCATION}"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

export(EXPORT qdiscord-targets
    NAMESPACE QDiscord::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/qdiscord-targets.cmake"
)

install(EXPORT qdiscord-targets
    FILE "qdiscord-targets.cmake"
    NAMESPACE QDiscord::
    DESTINATION "${CONFIG_PACKAGE_LOCATION}"
)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/qdiscord-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/qdiscord-config-version.cmake"
    DESTINATION
    "${CONFIG_PACKAGE_LOCATION}"
)
