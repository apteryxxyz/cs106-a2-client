QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmenu.cpp \
    authorsearch.cpp \
    booksearch.cpp \
    borrowsearch.cpp \
    login.cpp \
    main.cpp \
    manageauthor.cpp \
    managebook.cpp \
    managemember.cpp \
    membermenu.cpp \
    membersearch.cpp \
    messagelog.cpp \
    viewmember.cpp \
    worker.cpp

HEADERS += \
    adminmenu.h \
    authorsearch.h \
    booksearch.h \
    borrowsearch.h \
    login.h \
    manageauthor.h \
    managebook.h \
    managemember.h \
    membermenu.h \
    membersearch.h \
    messagelog.h \
    models/author.h \
    models/book.h \
    models/borrow.h \
    models/message.h \
    models/user.h \
    viewmember.h \
    worker.h

FORMS += \
    adminmenu.ui \
    authorsearch.ui \
    booksearch.ui \
    borrowsearch.ui \
    login.ui \
    manageauthor.ui \
    managebook.ui \
    managemember.ui \
    membermenu.ui \
    membersearch.ui \
    messagelog.ui \
    viewmember.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
