#ifndef MAIN_CC
#define MAIN_CC
#include <QApplication>
#include "ui/DsMainFrame.h"
#include "ui/DsQrcMacros.h"

#include "model/DsModel.h"
#include "operator/DsOperator.h"
#include "util/DsSpriteUtil.h"
#include "util/DsDebug.h"

#include <QDesktopWidget>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;

    DsMainFrame main_frame;

    int x = 0;
    int y = 0;
    int screenWidth = 1;
    int screenHeight = 1;
    QDesktopWidget *desktop = QApplication::desktop();
    screenWidth = desktop->width();
    screenHeight = desktop->height();
    x = (screenWidth - 1024) / 2;
    y = (screenHeight - 800) / 2;

    main_frame.resize(1024,800);
    main_frame.move(x, y); // center the main_frame
    main_frame.setWindowTitle("FSprite Designer");
    main_frame.setWindowIcon(QIcon(DS_MS_WINDOW_ICON));
    main_frame.showMaximized();

    DsData::shareData()->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
    return app.exec();
}


#endif // MAIN_CC



















