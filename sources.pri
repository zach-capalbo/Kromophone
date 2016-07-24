SOURCES += \
  ColorSource.cpp \
  DesktopImageSource.cpp \
  QtCameraSource.cpp \
  QmlCameraSource.cpp \
  LiveImageColorSource.cpp \
  ImageColorSource.cpp \
  StaticImageColorSource.cpp \
    $$PWD/OpenCVImageSource.cpp \    
    $$PWD/V4L2ImageSource.cpp \
    $$PWD/CameraFactory.cpp

unix: SOURCES += $$PWD/v4lcamera_raw.c

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
    $$PWD/CameraFactory.h

unix: SOURCES += $$PWD/v4lcamera_raw.h
