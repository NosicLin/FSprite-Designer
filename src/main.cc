#ifndef MAIN_CC
#define MAIN_CC
#include <QApplication>
<<<<<<< HEAD
#include "ui/DsMainFrame.h"
#include "ui/DsQrcMacros.h"
=======
#include "DsMainFrame.h"
#include "DsQrcMacros.h"
>>>>>>> a28b1041518d7c00038c1ba311e74126e353c757

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
