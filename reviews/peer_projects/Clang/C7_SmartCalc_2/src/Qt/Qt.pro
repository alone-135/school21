QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_bonus_calc.c \
    ../s21_calc.c \
    credit_calc.cpp \
    deposit_calc.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    secondwindow.cpp

HEADERS += \
    ../s21_calc.h \
    config.h \
    config.h \
    credit_calc.h \
    deposit_calc.h \
    mainwindow.h \
    qcustomplot.h \
    secondwindow.h

FORMS += \
    credit_calc.ui \
    deposit_calc.ui \
    mainwindow.ui \
    secondwindow.ui

ICON = icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    file.rc

RESOURCES += icon.icns


