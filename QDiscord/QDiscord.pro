#-------------------------------------------------
#
# Project created by QtCreator 2016-05-01T17:55:58
#
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG += ordered

lessThan(QT_MAJOR_VERSION, 5) {
    error("Qt version 5.8 or higher is required due to a bug with" \
            "QNetworkAccessManager's sendCustomRequest method.")
}

lessThan(QT_MINOR_VERSION, 8) {
    error("Qt version 5.8 or higher is required due to a bug with" \
            "QNetworkAccessManager's sendCustomRequest method.")
}

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

OTHER_FILES += .clang-format
