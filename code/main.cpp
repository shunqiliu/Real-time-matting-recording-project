#include"MainWindow.h"
#include <QtWidgets/QApplication>
#include "ssy.h"
#include<qapplication.h>
#include<qsplashscreen.h>
#include<qelapsedtimer.h>
#include<qmovie.h>
#include<qlabel.h>

int main(int argc, char* argv[])
{


	QApplication a(argc, argv);

	QSplashScreen splash(QPixmap("./Resources/open.gif"));
	QLabel lbl(&splash);
	QMovie mv("./Resources/open.gif");
	lbl.setMovie(&mv);
	mv.start();
	splash.show();

	QElapsedTimer tmr;
	tmr.start();

	while (tmr.elapsed() < 2500)
	{
		a.processEvents();
	}
	splash.close();

	MainWindow w;
	w.showFullScreen();
	return a.exec();
}
