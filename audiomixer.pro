include(audiomixer.pri)

TEMPLATE = subdirs

# Ensure that library is built before application
CONFIG  += ordered

!contains(DEFINES, DISABLE_FFT): SUBDIRS += 3rdparty/fftreal
SUBDIRS += app
SUBDIRS += plugin

TARGET = audiomixer

EXAMPLE_FILES += \
    README.md \
    TODO.md
