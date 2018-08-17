# -------- LIBRARY CONFIGURATION --------

# A link to where the library is hosted. This is used to form the user-agent.
set(QDISCORD_LINK "https://gitlab.com/george99g/QDiscord")

# The library's major version. This is used to form the user-agent and set the
# library's version.
set(QDISCORD_VERSION_MAJOR "0")

# The library's minor version. This is used to form the user-agent and set the
# library's version.
set(QDISCORD_VERSION_MINOR "22")

# The library's patch version. This is used to form the user-agent and set the
# library's version.
set(QDISCORD_VERSION_PATCH "0")

# ---------------------------------------

set(QDISCORD_PRINT_DEBUG ON CACHE BOOL
    "Determines whether this build should contain debug statements."
)

string(CONCAT QDISCORD_VERSION
    "${QDISCORD_VERSION_MAJOR}"
    ".${QDISCORD_VERSION_MINOR}"
    ".${QDISCORD_VERSION_PATCH}"
)

set_target_properties(
    qdiscord
    PROPERTIES
    VERSION ${QDISCORD_VERSION}
)

target_compile_definitions(
    qdiscord
    PRIVATE
    QDISCORD_NAME="${PROJECT_NAME}"
    QDISCORD_LINK="${QDISCORD_LINK}"
    QDISCORD_VERSION="${QDISCORD_VERSION}"
    QDISCORD_VERSION_MAJOR="${QDISCORD_VERSION_MAJOR}"
    QDISCORD_VERSION_MINOR="${QDISCORD_VERSION_MINOR}"
    QDISCORD_VERSION_PATCH="${QDISCORD_VERSION_PATCH}"
)

if(QDISCORD_PRINT_DEBUG)
    message(STATUS "[${PROJECT_NAME}] Compiling with debug statements. Pass `-DQDISCORD_PRINT_DEBUG:BOOL=OFF` to disable.")

    target_compile_definitions(qdiscord PRIVATE QDISCORD_PRINT_DEBUG)
endif(QDISCORD_PRINT_DEBUG)
