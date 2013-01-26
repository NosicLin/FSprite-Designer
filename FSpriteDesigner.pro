SOURCES += \
    src/ui/DsSpriteDisplay.cc \
    src/ui/DsResourceDisplay.cc \
    src/ui/DsPropertyDisplay.cc \
    src/ui/DsMainFrame.cc \
    src/ui/DsEditView.cc \
    src/ui/DsEditSpace.cc \
    src/operator/DsDataOperator.cc \
    src/model/DsSprite.cc \
    src/model/DsResourceMgr.cc \
    src/model/DsProject.cc \
    src/model/DsFrame.cc \
    src/model/DsData.cc \
    src/model/DsAnimation.cc \
    src/main.cc \
    src/model/DsFrameImage.cc

HEADERS += \
    src/ui/DsSpriteDisplay.h \
    src/ui/DsResourceDisplay.h \
    src/ui/DsQrcMacros.h \
    src/ui/DsPropertyDisplay.h \
    src/ui/DsMainFrame.h \
    src/ui/DsEditView.h \
    src/ui/DsEditSpace.h \
    src/operator/DsDataOperator.h \
    src/model/DsSprite.h \
    src/model/DsResourceMgr.h \
    src/model/DsProject.h \
    src/model/DsFrameImage.h \
    src/model/DsFrame.h \
    src/model/DsData.h \
    src/model/DsAnimation.h

INCLUDEPATH +=src/

RESOURCES += \
    resource/images/res.qrc

OTHER_FILES +=

FORMS += \
    resource/ui/animation_info.ui \
    resource/ui/about.ui \
    resource/ui/scale.ui

QT+=opengl
