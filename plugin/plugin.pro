TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../app
HEADERS         = fxplugin.h
#    verbplugin.h \
#   echoplugin.h
SOURCES         = fxplugin.cpp
#   verbplugin.cpp \
#    echoplugin.cpp

fmod_path = 'C:\Users\Gabriel\Documents\Qt\audiomixer\3rdparty\fmod'
fmod_dir = $${fmod_path}/inc
fmod_lib = $${fmod_path}/lib

win32:CONFIG(release, debug|release): LIBS += -L$${fmod_lib} -lfmod64_vc
else:win32:CONFIG(debug, debug|release): LIBS += -L$${fmod_lib} -lfmod64_vc
else:unix: LIBS += -L$${fmod_lib} -lfmod64

INCLUDEPATH += $${fmod_dir}
DEPENDPATH += $${fmod_dir}

TARGET          = $$qtLibraryTarget(audiomixer)
DESTDIR         = ../plugins
