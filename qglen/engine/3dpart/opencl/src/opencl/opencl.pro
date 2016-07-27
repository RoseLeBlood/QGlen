TEMPLATE = lib
TARGET = QtOpenCLgl
QT += concurrent opengl
CONFIG += dll
CONFIG += warn_on

win32 { 
    DESTDIR = ../../bin
    !static:DEFINES += QT_MAKEDLL
}
else:DESTDIR = ../../lib

macx:!opencl_configure {
    LIBS += -framework OpenCL
}

opencl_1_1 {
    DEFINES += QT_OPENCL_1_1
}


win32: LIBS += -L$$PWD/win32/ -lOpenCL

INCLUDEPATH += $$PWD/win32/
DEPENDPATH += $$PWD/win32/


HEADERS += \
    qclbuffer.h \
    qclcommandqueue.h \
    qclcontext.h \
    qcldevice.h \
    qclevent.h \
    qclglobal.h \
    qclimage.h \
    qclimageformat.h \
    qclkernel.h \
    qclmemoryobject.h \
    qclplatform.h \
    qclprogram.h \
    qclsampler.h \
    qcluserevent.h \
    qclvector.h \
    qclworksize.h \
    qclcontextgl.h

SOURCES += \
    qclbuffer.cpp \
    qclcommandqueue.cpp \
    qclcontext.cpp \
    qcldevice.cpp \
    qclevent.cpp \
    qclimage.cpp \
    qclimageformat.cpp \
    qclkernel.cpp \
    qclmemoryobject.cpp \
    qclplatform.cpp \
    qclprogram.cpp \
    qclsampler.cpp \
    qcluserevent.cpp \
    qclvector.cpp \
    qclworksize.cpp \
    qclcontextgl.cpp

PRIVATE_HEADERS += \
    qclext_p.h

HEADERS += $$PRIVATE_HEADERS
DEFINES += QT_BUILD_CL_LIB

