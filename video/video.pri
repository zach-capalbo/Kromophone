
INCLUDEPATH += video
DEPENDPATH += video


HEADERS += \
    video/qvideoframeconversionhelper_p.h \
    video/qsimd_p.h \
    video/qvideoframe.h

SOURCES += \
    video/qvideoframeconversionhelper.cpp \
#    video/qvideoframeconversionhelper_sse2.cpp \
#    video/qvideoframeconversionhelper_ssse3.cpp \
#    video/qvideoframeconversionhelper_avx2.cpp
