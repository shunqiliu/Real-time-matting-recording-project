#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <WinSock2.h>
#include <Iphlpapi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<string>
#include <fstream>
#include <QtWidgets/QWidget>
#include "QTimer"
#include "ui_MainWindow.h"
#include "QImage"
#include <QLabel>
#include <QEvent>
#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include<qmainwindow.h>
#include "ssy.h"
#include"QAudioDeviceInfo"

using namespace std;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();

private slots:
	void openv();
	void openf();
	void openh();
	void end();
	void opent();
	char* Getresult(char* id);
	void decode(string& c, int key[]);
	void chongqi();
	void changes();
	void reshow();

private:
	Ui::MainWindow ui;
	ssy* f1;
	cv::VideoCapture hdmi;
	cv::Mat Hd;
	time_t tpii;
	struct tm* pii;
	QTimer* t;

};
#endif