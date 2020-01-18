#pragma once

#include <QtWidgets>
#include "QTimer"
#include "ui_ssy.h"
#include "QImage"
#include"opencv2/opencv.hpp"
#include <QLabel>
#include <QEvent>
#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include<thread>
#include<mutex>
#include <QFile>
#include <QAudioRecorder>
#include <QTime>  
#include <QButtonGroup>
#include<qmediarecorder.h>
#include"QAudioDeviceInfo"
#include <qdebug.h>

using namespace cv;
using namespace std;
class ssy : public QWidget
{
	Q_OBJECT

public:
	ssy(QWidget* parent = 0);
	~ssy();
	void StartStopwatch();
	void ResetStopwatch();
	void StopStopwatch();
	Mat process_pc();
	Mat process_sc();
	Mat process_s();
	Mat process_p();

protected:
	void showEvent(QShowEvent*);
	void mousePressEvent(QMouseEvent* event);
	//鼠标移动事件
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);


private slots:
	void sshow();
	void end();
	void initialize();
	void cmd();
	void start();
	void lowerValueChangedSlot(int);
	void upperValueChangedSlot(int);
	void lowerTextChangedSlot(const QString& text);
	void upperTextChangedSlot(const QString& text);
	void lowerValueChangedSlot2(int);
	void upperValueChangedSlot2(int);
	void lowerTextChangedSlot2(const QString& text);
	void upperTextChangedSlot2(const QString& text);
	void lowerValueChangedSlot3(int);
	void upperValueChangedSlot3(int);
	void lowerTextChangedSlot3(const QString& text);
	void upperTextChangedSlot3(const QString& text);
	void TimeSlot();
	void taiTextChanged(const QString& text);
	void gdTextChanged(const QString& text);
	void zhuchiTextChanged(const QString& text);
	void gundo();
	void gundooo();
	void yanser();
	void qdtb();
	void gbtb();
	void qdzc();
	void gbzc();
	void qdzm();
	void gbzm();
	void t_s();
	void t_x();
	void t_z();
	void t_y();
	void zm_s();
	void zm_x();
	void zc_y();
	void zc_s();
	void zc_z();
	void zc_x();
	void jiasu();
	void jiansu();

	void invi();
	void showl();

	void invir();
	void showr();
	void ct(QListWidgetItem* item);
	void cz(QListWidgetItem* item);
	void applyVolume(int v);
	void setiniv();
	void czm(QListWidgetItem* item);
	void cbjtp(QListWidgetItem* item);
	void icon();
	void setwei();
	void nsetwei();
	void saveText();
	//void timeshows();
	void flagco();
	void flagct();
	void flagrct();
	void flagrcf();
	void zcrinv();
	void zcrshow();

signals:

	void sendsignal();


private:
	Ui::ssyClass ui;
	VideoCapture camera;
	VideoCapture screen;
	VideoWriter we;
	QTimer* timer;
	QTimer* timer2;
	QTimer* timer3;
	QTimer* timerzm;
	QTimer* timericon;
	QLabel* label;
	Mat I1 = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat I2 = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat cam = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat scr = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat pic = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	//Mat record = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255)); 
	Mat mask_inv = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat mask = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat I = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat tai = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat host = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat zm = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat svd = Mat(800, 400, CV_8UC3, Scalar(255, 255, 255));
	Mat framee = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat ns = Mat(1920, 1280, CV_8UC3, Scalar(0, 0, 0));
	Mat picshow = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat fm = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat fop = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat pc = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat sc = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat pi = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat n = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat nc = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat setpic = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat camx = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	
	
	mutex mu;
	mutex m;
	QImage image;
	QString filename;
	int i = 0;
	time_t timep;
	struct tm* p;
	char name[1000] = { " " };
	QAudioRecorder* audioRecorderf;
	QAudioRecorder* audioRecorderb;
	QAudioRecorder* audioRecorder;

	Mat x = Mat(1920, 1280, CV_8UC3, Scalar(255, 255, 255));
	Mat pause = Mat(512, 512, CV_8UC3, Scalar(255, 255, 255));
	volatile int baos = 255;
	volatile int baox = 43;
	volatile int ls = 255;
	volatile int lx = 46;
	volatile int ss = 99;
	volatile int sx = 35;

	volatile int hourTemp = 0;           //Hour
	volatile int minuteTemp = 0;         //Minute
	volatile int secondTemp = 0;         //Second
	volatile int countTemp = 0;
	volatile int countt = 0;
	QTimer* msTimer;   //定义一个定时器
	string timee;
	string tb = " ";
	string gd = " ";
	string zhuchi = " ";

	int wz = 1920;
	int wztbw = 120;
	int wztbh = 200;
	int wzzmh = 990;
	int wzzcw = 700;
	int wzzch = 840;
	int speed = 1;

	int fontFace = FONT_HERSHEY_SCRIPT_COMPLEX;
	double fontScale = 2;
	int thickness = 3;
	int baseline = 0;
	int wdzm = 0;

	QButtonGroup* colors;

	volatile BOOL taibiao = false;
	volatile BOOL zhuchiren = false;
	volatile BOOL gundongzimu = false;

	volatile BOOL flagr = true;
	volatile int flags = 1;

	Rect roi_rect;
	Rect roi2;
	Rect rot;
	Rect roh;
	Rect roz;
	Rect sv;

	const char* pp;
	const char* gg;
	const char* zcc;
	const char* mb;

	QPoint m_lastPoint;
	volatile int xt = 100;
	volatile int yt = 100;
	volatile int xh = 450;
	volatile int yh = 800;

	QRect trect;
	QRect hrect;

	volatile BOOL tsb = false;
	volatile BOOL hsb = false;

	volatile int txix;
	volatile int txiy;
	volatile int hxix;
	volatile int hxiy;

	volatile int tcols;
	volatile int trows;
	volatile int hcols;
	volatile int hrows;

	QString filenamet;
	QString filenamez;
	QString filenamezm;
	QString filenamebg;
	QString filenamex;

	qreal linearVolume;

	int framerate;

	clock_t strec, firec;

	LONGLONG diff;
	LONGLONG tim;
	LONGLONG fcount;

	int indbh=0;
	int indfr=0;

	int sect = 0;
	int mint = 0;
	int hout = 0;
	long ms = 0;

	QStringList zcr_imgList;      // 文件目录下所有的图像文件名
	QStringList tb_imgList;      // 文件目录下所有的图像文件名
	QStringList zm_imgList;      // 文件目录下所有的图像文件名
	QStringList bg_imgList;      // 文件目录下所有的图像文件名
	QString zcr_strPath;          // 文件夹路径
	QString tb_strPath;          // 文件夹路径
	QString zm_strPath;          // 文件夹路径
	QString bg_strPath;          // 文件夹路径
};