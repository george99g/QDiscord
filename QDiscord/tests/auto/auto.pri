QT += testlib network websockets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG += no_testcase_installs
CONFIG -= app_bundle

include(../tests.pri)
