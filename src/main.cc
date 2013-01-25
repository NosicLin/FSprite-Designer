#ifndef MAIN_CC
#define MAIN_CC
#include <QApplication>
#include "DsMainFrame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	DsMainFrame main_frame;
	main_frame.resize(1024,800);
	main_frame.setWindowTitle("FSpriteDesigner");
	main_frame.show();
	return app.exec();
}


#endif // MAIN_CC
