QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addflightdialog.cpp \
    admin.cpp \
    adminflightinfo.cpp \
    adminlogin.cpp \
    adminmainwindow.cpp \
    adminre.cpp \
    flight.cpp \
    main.cpp \
    loginwindow.cpp \
    myorderwindow.cpp \
    passinfo.cpp \
    showpassinfowindow.cpp \
    ticket.cpp \
    ticketinfo.cpp \
    user.cpp \
    userflightinfo.cpp \
    userhomepage.cpp \
    userlogin.cpp \
    usermainwindow.cpp \
    userre.cpp

HEADERS += \
    addflightdialog.h \
    admin.h \
    adminflightinfo.h \
    adminlogin.h \
    adminmainwindow.h \
    adminre.h \
    flight.h \
    loginwindow.h \
    myorderwindow.h \
    passinfo.h \
    showpassinfowindow.h \
    ticket.h \
    ticketinfo.h \
    user.h \
    userflightinfo.h \
    userhomepage.h \
    userlogin.h \
    usermainwindow.h \
    userre.h

FORMS += \
    addflightdialog.ui \
    adminflightinfo.ui \
    adminlogin.ui \
    adminmainwindow.ui \
    adminre.ui \
    loginwindow.ui \
    myorderwindow.ui \
    passinfo.ui \
    showpassinfowindow.ui \
    ticketinfo.ui \
    userflightinfo.ui \
    userhomepage.ui \
    userlogin.ui \
    usermainwindow.ui \
    userre.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
