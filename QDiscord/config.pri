#-------------------------------------------------------------------------------
#---------------------------LIBRARY CONFIGURATION-------------------------------
#-------------------------------------------------------------------------------

#QDISCORD_BOT_NAME: The current bot's name. This is used to form the user-agent.
QDISCORD_BOT_NAME=QDiscordBot

#QDISCORD_LIBRARY_NAME: The library's name. Change if you fork this project and
#rename it. This is used to form the user-agent.
QDISCORD_LIBRARY_NAME=QDiscord

#QDISCORD_LIBRARY_LINK: A link to where the library is hosted. This is used to
#form the user-agent.
QDISCORD_LIBRARY_LINK=https://github.com/george99g/QDiscord/

#QDISCORD_LIBRARY_MAJOR: The library's major version. This is used to form the
#user-agent.
QDISCORD_LIBRARY_MAJOR=0

#QDISCORD_LIBRARY_MINOR: The library's minor version. This is used to form the
#user-agent.
QDISCORD_LIBRARY_MINOR=12

#QDISCORD_LIBRARY_DEBUG: Determines whether the library should output debug
#information.
QDISCORD_LIBRARY_DEBUG=true

#QDISCORD_DISCORD_API_VERSION: Sets the Discord API version to use.
QDISCORD_DISCORD_API_VERSION=6

#QDISCORD_LIBRARY_BUILD_TESTS: Determines whether the library should build tests
QDISCORD_LIBRARY_BUILD_TESTS=true

#QDISCORD_LIBRARY_GEN_DOCS: Deteremines whether the library's documentation
#should be generated.
QDISCORD_LIBRARY_GEN_DOCS=true


DEFINES += QDISCORD_BOT_NAME=\\\"$${QDISCORD_BOT_NAME}\\\"
DEFINES += QDISCORD_LIBRARY_NAME=\\\"$${QDISCORD_LIBRARY_NAME}\\\"
DEFINES += QDISCORD_LIBRARY_LINK=\\\"$${QDISCORD_LIBRARY_LINK}\\\"
DEFINES += QDISCORD_LIBRARY_MAJOR=\\\"$${QDISCORD_LIBRARY_MAJOR}\\\"
DEFINES += QDISCORD_LIBRARY_MINOR=\\\"$${QDISCORD_LIBRARY_MINOR}\\\"
DEFINES += QDISCORD_DISCORD_API_VERSION=\\\"$${QDISCORD_DISCORD_API_VERSION}\\\"
equals(QDISCORD_LIBRARY_DEBUG, "true") {
    DEFINES += QDISCORD_LIBRARY_DEBUG
}
