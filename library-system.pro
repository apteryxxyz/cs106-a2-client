QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
    addbook.cpp \
    adminmenu.cpp \
    booksearch.cpp \
=======
    login.cpp \
>>>>>>> main
    main.cpp \
    worker.cpp

HEADERS += \
<<<<<<< HEAD
    addbook.h \
    adminmenu.h \
    booksearch.h \
    mainwindow.h \
=======
    login.h \
>>>>>>> main
    models/author.h \
    models/book.h \
    models/borrow.h \
    models/user.h \
    worker.h

FORMS += \
<<<<<<< HEAD
    addbook.ui \
    adminmenu.ui \
    booksearch.ui \
    mainwindow.ui
=======
    login.ui
>>>>>>> main

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    CS106.pro \
    CS106.pro \
    CS106.pro

RESOURCES += \
    Resources.qrc
