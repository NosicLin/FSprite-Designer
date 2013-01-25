#ifndef MAIN_CC
#define MAIN_CC
#include <QApplication>
#include "DsMainFrame.h"
#include "DsQrcMacros.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;

	DsMainFrame main_frame;


	main_frame.resize(1024,800);
    main_frame.setWindowTitle("FSprite Designer");
    main_frame.setWindowIcon(QIcon(DS_MS_WINDOW_ICON));
	main_frame.show();
	return app.exec();
}


#endif // MAIN_CC
