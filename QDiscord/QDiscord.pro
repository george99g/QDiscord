#-------------------------------------------------
#
# Project created by QtCreator 2016-05-01T17:55:58
#
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG += ordered

include(config.pri)

SUBDIRS += src
equals(QDISCORD_LIBRARY_BUILD_TESTS, "true") {
    SUBDIRS += tests
    tests.depends = src
}

equals(QDISCORD_LIBRARY_GEN_DOCS, "true") {
    OTHER_FILES += Doxyfile
    include(doc/doc.pri)
}
