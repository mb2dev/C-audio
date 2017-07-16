include(../audiomixer.pri)

TEMPLATE = app

TARGET = audiomixer

QT       += multimedia widgets

SOURCES += main.cpp \
    gvmainwindow.cpp \
    fxsection.cpp \
    eqsection.cpp \
    shazamsection.cpp \
    player.cpp \
    eqwidget.cpp \
    audiosection.cpp \
    levelsection.cpp \
    filebrowser.cpp \
    soundmanager.cpp \
    soundplayer.cpp \

HEADERS += \
    gvmainwindow.h \
    fxsection.h \
    fxinterface.h \
    eqsection.h \
    shazamsection.h \
    player.h \
    eqwidget.h \
    audiosection.h \
    levelsection.h \
    filebrowser.h \
    soundmanager.h \
    soundplayer.h

# From Spectrum Example
SOURCES += \
    ../spectrum/engine.cpp \
    ../spectrum/frequencyspectrum.cpp \
    ../spectrum/levelmeter.cpp \
    ../spectrum/progressbar.cpp \
    ../spectrum/settingsdialog.cpp \
    ../spectrum/spectrograph.cpp \
    ../spectrum/spectrumanalyser.cpp \
    ../spectrum/tonegenerator.cpp \
    ../spectrum/tonegeneratordialog.cpp \
    ../spectrum/utils.cpp \
    ../spectrum/waveform.cpp \
    ../spectrum/wavfile.cpp

HEADERS += \
    ../spectrum/engine.h \
    ../spectrum/frequencyspectrum.h \
    ../spectrum/levelmeter.h \
    ../spectrum/progressbar.h \
    ../spectrum/settingsdialog.h \
    ../spectrum/spectrograph.h \
    ../spectrum/spectrum.h \
    ../spectrum/spectrumanalyser.h \
    ../spectrum/tonegenerator.h \
    ../spectrum/tonegeneratordialog.h \
    ../spectrum/utils.h \
    ../spectrum/waveform.h \
    ../spectrum/wavfile.h

win32:CONFIG(release, debug|release): LIBS += -L'E:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/lib/' -lfmod64_vc
else:win32:CONFIG(debug, debug|release): LIBS += -L'E:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/lib/' -lfmod64_vc
else:unix: LIBS += -L'E:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/lib/' -lfmod64

INCLUDEPATH += 'E:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/inc'
DEPENDPATH += 'E:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/inc'

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

fftreal_dir = ../3rdparty/fftreal

INCLUDEPATH += $${fftreal_dir}

#spectrum_dir = ../spectrum
# https://stackoverflow.com/questions/10034825/how-do-i-build-a-static-library-and-executable-with-qt
# https://wiki.qt.io/How_to_create_a_library_with_Qt_and_use_it_in_an_application
#INCLUDEPATH += $${spectrum_dir}
#LIBS += -L$${spectrum_dir}/debug -lspectrum

RESOURCES = audiomixer.qrc

# Dynamic linkage against FFTReal DLL
!contains(DEFINES, DISABLE_FFT) {
    macx {
        # Link to fftreal framework
        LIBS += -F$${fftreal_dir}
        LIBS += -framework fftreal
    } else {
        LIBS += -L..$${audiomix_build_dir}
        LIBS += -lfftreal
    }
}

#target.path = $$[QT_INSTALL_EXAMPLES]/multimedia/spectrum
#INSTALLS += target

#CONFIG += install_ok  # Do not cargo-cult this!

# Deployment

DESTDIR = ..$${audiomix_build_dir}
macx {
    !contains(DEFINES, DISABLE_FFT) {
        # Relocate fftreal.framework into audiomixer.app bundle
        framework_dir = ../audiomixer.app/Contents/Frameworks
        framework_name = fftreal.framework/Versions/1/fftreal
        QMAKE_POST_LINK = \
            mkdir -p $${framework_dir} &&\
            rm -rf $${framework_dir}/fftreal.framework &&\
            cp -R $${fftreal_dir}/fftreal.framework $${framework_dir} &&\
            install_name_tool -id @executable_path/../Frameworks/$${framework_name} \
                                $${framework_dir}/$${framework_name} &&\
            install_name_tool -change $${framework_name} \
                                @executable_path/../Frameworks/$${framework_name} \
                                ../audiomixer.app/Contents/MacOS/spectrum
    }
} else {
    linux-g++*: {
        # Provide relative path from application to fftreal library
        QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
    }
}
