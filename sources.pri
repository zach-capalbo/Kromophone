SOURCES += \
  ColorSource.cpp \
  DesktopImageSource.cpp \
  QtCameraSource.cpp \
  QmlCameraSource.cpp \
  LiveImageColorSource.cpp \
  ImageColorSource.cpp \
  StaticImageColorSource.cpp \
    $$PWD/OpenCVImageSource.cpp \
    $$PWD/v4lcamera_raw.c \
    $$PWD/V4L2ImageSource.cpp \
    $$PWD/CameraFactory.cpp

HEADERS += \
  ColorSource.h \
  DesktopImageSource.h \
  QtCameraSource.h \
  QmlCameraSource.h \
  LiveImageColorSource.h \
  ImageColorSource.h \
  StaticImageColorSource.h \ 
    $$PWD/OpenCVImageSource.h \
    $$PWD/V4L2ImageSource.h \
    $$PWD/v4lcamera_raw.h \
    $$PWD/CameraFactory.h
