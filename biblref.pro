#
#    biblref
#    Creation of bibliographic references.
#
#    File: biblref.pro
#
#    Copyright (C) 2012-2014 Artem Petrov <pa2311@gmail.com>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#

QT += core gui widgets printsupport

TARGET = biblref

TEMPLATE = app

VERSION = 1.1.5

SOURCES += sources/main.cpp \
    sources/mainwindow.cpp \
    sources/refbookdialog.cpp \
    sources/refarticledialog.cpp \
    sources/refpatentdialog.cpp \
    sources/refinventsertificatedialog.cpp \
    sources/refdissertationdialog.cpp \
    sources/refdeposmanuscriptdialog.cpp \
    sources/refthesisdialog.cpp \
    sources/refsitedialog.cpp

HEADERS += sources/mainwindow.h \
    sources/constants.h \
    sources/refbookdialog.h \
    sources/refarticledialog.h \
    sources/refpatentdialog.h \
    sources/refinventsertificatedialog.h \
    sources/refdissertationdialog.h \
    sources/refdeposmanuscriptdialog.h \
    sources/refthesisdialog.h \
    sources/refsitedialog.h

FORMS += sources/mainwindow.ui \
    sources/refbookdialog.ui \
    sources/refarticledialog.ui \
    sources/refpatentdialog.ui \
    sources/refinventsertificatedialog.ui \
    sources/refdissertationdialog.ui \
    sources/refdeposmanuscriptdialog.ui \
    sources/refthesisdialog.ui \
    sources/refsitedialog.ui

QMAKE_CXXFLAGS += -std=c++11 -W -pedantic

unix: {
    DESTDIR = build/unix/bin
    MOC_DIR = build/unix/moc
    RCC_DIR = build/unix/rc
    UI_DIR = build/unix/ui_h
    CONFIG (debug, debug|release) {
        OBJECTS_DIR = build/unix/debug
    }
    else {
        OBJECTS_DIR = build/unix/release
    }
    target.path = $$PREFIX/bin
    INSTALLS += target
}

win32: {
    DESTDIR = build/win/bin
    MOC_DIR = build/win/moc
    RCC_DIR = build/win/rc
    UI_DIR = build/win/ui_h
    CONFIG (debug, debug|release) {
        OBJECTS_DIR = build/win/debug
    }
    else {
        OBJECTS_DIR = build/win/release
    }
}

RESOURCES += sources/biblref.qrc

RC_FILE += sources/biblref.rc
