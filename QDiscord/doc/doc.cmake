set(DOC_FILES
    doc/mainpage.dox
    doc/installing.dox
    doc/usage.dox
    doc/versioning.dox
    doc/examples.dox
)

get_target_property(QMAKE_LOCATION Qt5::qmake LOCATION)

# Massive hack, but Qt doesn't expose this.
execute_process(
    COMMAND "${QMAKE_LOCATION}" "-query" "QT_INSTALL_DOCS"
    RESULT_VARIABLE QMAKE_QUERY_RESULT
    OUTPUT_VARIABLE Qt5_INSTALL_DOCS
    ERROR_VARIABLE QMAKE_QUERY_ERROR_VARIABLE
)

if(QMAKE_QUERY_RESULT)
    message(WARNING "[${PROJECT_NAME}] qmake returned ${QMAKE_QUERY_RESULT}: ${QMAKE_QUERY_ERROR_VARIABLE}")
    message(WARNING "[${PROJECT_NAME}] docs target disabled")
else(QMAKE_QUERY_RESULT)
    string(REGEX REPLACE "\n$" "" Qt5_INSTALL_DOCS "${Qt5_INSTALL_DOCS}")

    string(CONCAT DOXYGEN_ENV
        "QT_INSTALL_DOCS=\"${Qt5_INSTALL_DOCS}\";"
        "QDISCORD_VERSION=\"${QDISCORD_VERSION}\";"
        "SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\""
    )

    set(DOXYFILE "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")

    add_custom_target(docs
        COMMAND ${CMAKE_COMMAND} -E env ${DOXYGEN_ENV} doxygen "${DOXYFILE}"
        SOURCES ${DOC_FILES}
    )
endif(QMAKE_QUERY_RESULT)
