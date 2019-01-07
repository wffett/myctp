TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    custommdspi.cpp \

HEADERS += \
    CTP_API_64/ThostFtdcMdApi.h \
    CTP_API_64/ThostFtdcTraderApi.h \
    CTP_API_64/ThostFtdcUserApiDataType.h \
    CTP_API_64/ThostFtdcUserApiStruct.h \
    custommdspi.h

INCLUDEPATH += ./CTP_API_64




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/CTP_API_64/release/ -lthostmduserapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/CTP_API_64/debug/ -lthostmduserapi
else:unix: LIBS += -L$$PWD/CTP_API_64/ -lthostmduserapi

INCLUDEPATH += $$PWD/CTP_API_64
DEPENDPATH += $$PWD/CTP_API_64
