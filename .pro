QT += core gui widgets
CONFIG += c++11 qt warn_on sdk_no_version_check

TARGET = myapp
SOURCES += gui.cpp NamePromptDialog.cpp
HEADERS += NamePromptDialog.h

QMAKE_FRAMEWORKPATH += /opt/homebrew/Cellar/qt@5/5.15.16_2/lib
INCLUDEPATH += /opt/homebrew/Cellar/qt@5/5.15.16_2/lib/QtWidgets.framework/Headers \
               /opt/homebrew/Cellar/qt@5/5.15.16_2/lib/QtGui.framework/Headers \
               /opt/homebrew/Cellar/qt@5/5.15.16_2/lib/QtCore.framework/Headers