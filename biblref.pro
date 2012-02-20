#
#    biblref
#    Creation of bibliographic references.
#
#    File: biblref.pro
#
#    Copyright (C) 2012 Artem Petrov <pa2311@gmail.com>
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

QT += core gui
TARGET = biblref
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    refbookdialog.cpp \
    refarticledialog.cpp \
    refpatentdialog.cpp \
    refinventsertificatedialog.cpp \
    refdissertationdialog.cpp \
    refdeposmanuscriptdialog.cpp
HEADERS += mainwindow.h \
    constants.h \
    refbookdialog.h \
    refarticledialog.h \
    refpatentdialog.h \
    refinventsertificatedialog.h \
    refdissertationdialog.h \
    refdeposmanuscriptdialog.h
FORMS += mainwindow.ui \
    refbookdialog.ui \
    refarticledialog.ui \
    refpatentdialog.ui \
    refinventsertificatedialog.ui \
    refdissertationdialog.ui \
    refdeposmanuscriptdialog.ui
unix: {
    DESTDIR = build/unix/bin
    MOC_DIR = build/unix/moc
    RCC_DIR = build/unix/rc
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
    DESTDIR = build\\win\\bin
    MOC_DIR = build\\win\\moc
    RCC_DIR = build\\win\\rc
    CONFIG (debug, debug|release) {
        OBJECTS_DIR = build\\win\\debug
    }
    else {
        OBJECTS_DIR = build\\win\\release
    }
}
