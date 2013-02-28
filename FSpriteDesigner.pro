SOURCES += \
    src/ui/DsSpriteDisplay.cc \
    src/ui/DsResourceDisplay.cc \
    src/ui/DsPropertyDisplay.cc \
    src/ui/DsMainFrame.cc \
    src/ui/DsEditView.cc \
    src/ui/DsEditSpace.cc \
    src/ui/DsEditState.cc \
    src/ui/DsAnmationEdit.cc \
    src/model/DsResourceMgr.cc \
    src/model/DsProject.cc \
    src/model/DsFrame.cc \
    src/model/DsData.cc \
    src/model/DsAnimation.cc \
    src/model/DsFrameImage.cc \
    src/model/DsSprite.cc \
    src/operator/DsDataOperator.cc \
    src/operator/DsOperator.cc \
    src/operator/DsAnimationOperator.cc \
    src/operator/DsIoOperator.cc \
    src/operator/DsAuxOperator.cc \
    src/util/DsUtilLoader.cc \
    src/util/DsUtil.cc \
    src/main.cc \

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
    src/model/DsFrameImage.h \
    src/model/DsFrame.h \
    src/model/DsData.h \
    src/model/DsAnimation.h \
    src/ui/DsEditState.h \
    src/operator/DsOperator.h \
    src/operator/DsDataOperator.h \
    src/ui/DsAnimationEdit.h \
    src/util/DsDebug.h \
    src/operator/DsAnimationOperator.h \
    src/util/DsUtil.h \
    src/operator/DsIoOperator.h \
    src/model/DsProject.h \
    src/util/DsUtilLoader.h \
    src/model/DsModel.h \
    src/operator/DsAuxOperator.h

INCLUDEPATH +=src/

RESOURCES += \
    resource/images/res.qrc

OTHER_FILES +=

FORMS += \
    resource/ui/animation_info.ui \
    resource/ui/about.ui \
    resource/ui/scale.ui \
    resource/ui/pisition.ui \
    resource/ui/frame.ui

QT+=opengl
QT+=xml
