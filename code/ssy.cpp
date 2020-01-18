#include "ssy.h"
#include "ui_ssy.h"
#include<thread>
#include<mutex>
#include"putText.h"
#include<fstream>
#include <time.h>
#include "DuplicationManager.h"

using namespace std;


static QVariant boxValue(const QComboBox* box)
{
	int idx = box->currentIndex();
	if (idx == -1)
		return QVariant();

	return box->itemData(idx);
}


ssy::ssy(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	msTimer = new QTimer(this);
	timer3 = new QTimer(this);
	timer3->setSingleShot(true); 
	timerzm = new QTimer(this);
	timericon = new QTimer(this);
	colors = new QButtonGroup(this);

	///////////////////////////
	
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.bmp" << "*.jpeg";
	//zcr
	const QSize zcrIMAGE_SIZE(240, 50);
	const QSize zcrITEM_SIZE(240, 80);
	zcr_strPath = "./Resources/zcr";
	QDir zcrdir(zcr_strPath);
	zcrdir.setFilter(QDir::Files | QDir::NoSymLinks);
	zcrdir.setNameFilters(filters);
	zcr_imgList = zcrdir.entryList();
	
	ui.zcrlw->setIconSize(zcrIMAGE_SIZE);
	ui.zcrlw->setResizeMode(QListView::Adjust);
	ui.zcrlw->setViewMode(QListView::IconMode);
	ui.zcrlw->setMovement(QListView::Static);
	ui.zcrlw->setSpacing(8);

	for (int inx = 0; inx < zcr_imgList.count() ; ++inx) {
		QPixmap pixmap(zcr_strPath + "/" + zcr_imgList.at(inx));
		QListWidgetItem* listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(zcrIMAGE_SIZE)), zcr_imgList.at(inx));
		listWidgetItem->setSizeHint(zcrITEM_SIZE);
		ui.zcrlw->insertItem(inx, listWidgetItem);
	}
	//taibiao
	const QSize tbIMAGE_SIZE(100, 100);
	const QSize tbITEM_SIZE(100, 130);
	tb_strPath = "./Resources/tb";
	QDir tbdir(tb_strPath);
	tbdir.setFilter(QDir::Files | QDir::NoSymLinks);
	tbdir.setNameFilters(filters);
	tb_imgList = tbdir.entryList();

	ui.tblw->setIconSize(tbIMAGE_SIZE);
	ui.tblw->setResizeMode(QListView::Adjust);
	ui.tblw->setViewMode(QListView::IconMode);
	ui.tblw->setMovement(QListView::Static);
	ui.tblw->setSpacing(8);
	ui.tblw->setFlow(QListView::TopToBottom);

	for (int inx = 0; inx < tb_imgList.count(); ++inx) {
		QPixmap pixmap(tb_strPath + "/" + tb_imgList.at(inx));
		QListWidgetItem* listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(tbIMAGE_SIZE)), tb_imgList.at(inx));
		listWidgetItem->setSizeHint(tbITEM_SIZE);
		ui.tblw->insertItem(inx, listWidgetItem);
	}
	//zm
	const QSize zmIMAGE_SIZE(240, 50);
	const QSize zmITEM_SIZE(240, 80);
	zm_strPath = "./Resources/zm";
	QDir zmdir(zm_strPath);
	zmdir.setFilter(QDir::Files | QDir::NoSymLinks);
	zmdir.setNameFilters(filters);
	zm_imgList = zmdir.entryList();

	ui.zmlw->setIconSize(zmIMAGE_SIZE);
	ui.zmlw->setResizeMode(QListView::Adjust);
	ui.zmlw->setViewMode(QListView::IconMode);
	ui.zmlw->setMovement(QListView::Static);
	ui.zmlw->setSpacing(8);

	for (int inx =0; inx < zm_imgList.count(); ++inx) {
		QPixmap pixmap(zm_strPath + "/" + zm_imgList.at(inx));
		QListWidgetItem* listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(zmIMAGE_SIZE)), zm_imgList.at(inx));
		listWidgetItem->setSizeHint(zmITEM_SIZE);
		ui.zmlw->insertItem(inx, listWidgetItem);
	}
	//beijing
	const QSize bgIMAGE_SIZE(120, 80);
	const QSize bgITEM_SIZE(120, 110);
	bg_strPath = "./bg";
	QDir bgdir(bg_strPath);
	bgdir.setFilter(QDir::Files | QDir::NoSymLinks);
	bgdir.setNameFilters(filters);
	bg_imgList = bgdir.entryList();

	ui.bgp->setIconSize(bgIMAGE_SIZE);
	ui.bgp->setResizeMode(QListView::Adjust);
	ui.bgp->setViewMode(QListView::IconMode);
	ui.bgp->setMovement(QListView::Static);
	ui.bgp->setSpacing(8);
	ui.bgp->setFlow(QListView::TopToBottom);

	for (int inx =  0; inx < bg_imgList.count(); ++inx) {
		QPixmap pixmap(bg_strPath + "/" + bg_imgList.at(inx));
		QListWidgetItem* listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(bgIMAGE_SIZE)), bg_imgList.at(inx));
		listWidgetItem->setSizeHint(bgITEM_SIZE);
		ui.bgp->insertItem(inx, listWidgetItem);
	}

	//
	connect(ui.zcrlw, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(cz(QListWidgetItem*)));
	connect(ui.tblw, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(ct(QListWidgetItem*)));
	connect(ui.zmlw, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(czm(QListWidgetItem*)));
	connect(ui.bgp, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(cbjtp(QListWidgetItem*)));
	////////////////////////////
	ui.tabWidget->setStyleSheet("QTabWidget:pane{border: 1px solid gray; top: -1px; background:  transparent; }");
	ui.start->setVisible(false);
	audioRecorder = new QAudioRecorder;

	colors->addButton(ui.radioButton, 0);
	colors->addButton(ui.radioButton_2, 1);
	colors->addButton(ui.radioButton_3, 2);
	colors->addButton(ui.radioButton_4, 3);
	colors->addButton(ui.radioButton_5, 4);
	ui.radioButton_4->setChecked(true);

	connect(ui.s4, SIGNAL(clicked()), this, SLOT(flagrct()));
	connect(ui.s6, SIGNAL(clicked()), this, SLOT(flagrcf()));
	connect(ui.s7, SIGNAL(clicked()), this, SLOT(flagco()));
	connect(ui.s9, SIGNAL(clicked()), this, SLOT(flagct()));
	connect(ui.s2, SIGNAL(clicked()), this, SLOT(zcrshow()));
	connect(ui.s3, SIGNAL(clicked()), this, SLOT(zcrinv()));

	connect(ui.radioButton, SIGNAL(clicked()), this, SLOT(yanser()));
	connect(ui.radioButton_2, SIGNAL(clicked()), this, SLOT(yanser()));
	connect(ui.radioButton_3, SIGNAL(clicked()), this, SLOT(yanser()));
	connect(ui.radioButton_4, SIGNAL(clicked()), this, SLOT(yanser()));
	connect(ui.radioButton_5, SIGNAL(clicked()), this, SLOT(yanser()));

	
	//onnect(ui.luzhibeijing, SIGNAL(clicked()), this, SLOT(cbjtp()));

	connect(ui.invi, SIGNAL(clicked()), this, SLOT(invi()));
	connect(ui.sl, SIGNAL(clicked()), this, SLOT(showl()));
	connect(ui.youc, SIGNAL(clicked()), this, SLOT(invir()));
	connect(ui.you, SIGNAL(clicked()), this, SLOT(showr()));

	connect(timer3, SIGNAL(timeout()), this, SLOT(initialize()));
	connect(timer, SIGNAL(timeout()), this, SLOT(sshow()));
	connect(timericon, SIGNAL(timeout()), this, SLOT(icon()));
	connect(ui.end, SIGNAL(clicked()), this, SLOT(end));
	connect(ui.start, SIGNAL(clicked()), this, SLOT(start));
	connect(ui.otai, SIGNAL(clicked()), this, SLOT(qdtb()));
	connect(ui.ctai, SIGNAL(clicked()), this, SLOT(gbtb()));
	connect(ui.czhuchiren, SIGNAL(clicked()), this, SLOT(gbzc()));
	connect(ui.ozhuchiren, SIGNAL(clicked()), this, SLOT(qdzc()));
	connect(ui.cgun, SIGNAL(clicked()), this, SLOT(gbzm()));
	connect(ui.ogun, SIGNAL(clicked()), this, SLOT(qdzm()));
	//connect(msTimer, SIGNAL(timeout()), this, SLOT(TimeSlot()));
	connect(timerzm, SIGNAL(timeout()), this, SLOT(gundo()));

	/*	connect(ui.chosetai, SIGNAL(clicked()), this, SLOT(ct()));
		connect(ui.chosezhu, SIGNAL(clicked()), this, SLOT(cz()));*/

	connect(ui.tbwzs, SIGNAL(clicked()), this, SLOT(t_s()));
	connect(ui.tbwzx, SIGNAL(clicked()), this, SLOT(t_x()));
	connect(ui.tbwzz, SIGNAL(clicked()), this, SLOT(t_z()));
	connect(ui.tbwzy, SIGNAL(clicked()), this, SLOT(t_y()));
	connect(ui.zmwzs, SIGNAL(clicked()), this, SLOT(zm_s()));
	connect(ui.zmwzx, SIGNAL(clicked()), this, SLOT(zm_x()));
	connect(ui.zcwzx, SIGNAL(clicked()), this, SLOT(zc_x()));
	connect(ui.zcwzs, SIGNAL(clicked()), this, SLOT(zc_s()));
	connect(ui.zcwzy, SIGNAL(clicked()), this, SLOT(zc_y()));
	connect(ui.zcwzz, SIGNAL(clicked()), this, SLOT(zc_z()));
	connect(ui.zmji, SIGNAL(clicked()), this, SLOT(jiansu()));
	connect(ui.zmjs, SIGNAL(clicked()), this, SLOT(jiasu()));

	ui.lineEdit->setText("43");
	ui.lineEdit_2->setText("255");
	ui.horizontalSlider->setHandleMovementMode(QxtSpanSlider::NoOverlapping);//设置两个滑块的模式
	ui.horizontalSlider->setMinimum(0);
	ui.horizontalSlider->setMaximum(255);//最大值设置
	ui.horizontalSlider->setLowerValue(43);//初始化小滑块的值
	ui.horizontalSlider->setUpperValue(255);//初始化大滑块的值
	connect(ui.horizontalSlider, SIGNAL(lowerValueChanged(int)), this, SLOT(lowerValueChangedSlot(int)));
	connect(ui.horizontalSlider, SIGNAL(upperValueChanged(int)), this, SLOT(upperValueChangedSlot(int)));
	connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lowerTextChangedSlot(QString)));
	connect(ui.lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(upperTextChangedSlot(QString)));

	ui.lineEdit_3->setText("43");
	ui.lineEdit_4->setText("255");
	ui.horizontalSlider_2->setHandleMovementMode(QxtSpanSlider::NoOverlapping);//设置两个滑块的模式
	ui.horizontalSlider_2->setMinimum(0);
	ui.horizontalSlider_2->setMaximum(255);//最大值设置
	ui.horizontalSlider_2->setLowerValue(46);//初始化小滑块的值
	ui.horizontalSlider_2->setUpperValue(255);//初始化大滑块的值
	connect(ui.horizontalSlider_2, SIGNAL(lowerValueChanged(int)), this, SLOT(lowerValueChangedSlot2(int)));
	connect(ui.horizontalSlider_2, SIGNAL(upperValueChanged(int)), this, SLOT(upperValueChangedSlot2(int)));
	connect(ui.lineEdit_3, SIGNAL(textChanged(QString)), this, SLOT(lowerTextChangedSlot2(QString)));
	connect(ui.lineEdit_4, SIGNAL(textChanged(QString)), this, SLOT(upperTextChangedSlot2(QString)));

	ui.lineEdit_5->setText("35");
	ui.lineEdit_6->setText("99");
	ui.horizontalSlider_3->setHandleMovementMode(QxtSpanSlider::NoOverlapping);//设置两个滑块的模式
	ui.horizontalSlider_3->setMinimum(0);
	ui.horizontalSlider_3->setMaximum(180);//最大值设置
	ui.horizontalSlider_3->setLowerValue(35);//初始化小滑块的值
	ui.horizontalSlider_3->setUpperValue(99);//初始化大滑块的值
	connect(ui.horizontalSlider_3, SIGNAL(lowerValueChanged(int)), this, SLOT(lowerValueChangedSlot3(int)));
	connect(ui.horizontalSlider_3, SIGNAL(upperValueChanged(int)), this, SLOT(upperValueChangedSlot3(int)));
	connect(ui.lineEdit_5, SIGNAL(textChanged(QString)), this, SLOT(lowerTextChangedSlot3(QString)));
	connect(ui.lineEdit_6, SIGNAL(textChanged(QString)), this, SLOT(upperTextChangedSlot3(QString)));
	connect(ui.lineEdit_7, SIGNAL(textChanged(QString)), this, SLOT(taiTextChanged(QString)));
	connect(ui.lineEdit_8, SIGNAL(textChanged(QString)), this, SLOT(gdTextChanged(QString)));
	connect(ui.lineEdit_9, SIGNAL(textChanged(QString)), this, SLOT(zhuchiTextChanged(QString)));
	connect(ui.weitiao, SIGNAL(clicked()), this, SLOT(setwei()));
	connect(ui.weitiao_2, SIGNAL(clicked()), this, SLOT(nsetwei()));

	connect(ui.behi, SIGNAL(currentIndexChanged(int)),this,SLOT(saveText()));
	connect(ui.fron, SIGNAL(currentIndexChanged(int)),this,SLOT(saveText()));

	ifstream bhd("behind.txt");
	bhd >> indbh;

	ifstream frt("front.txt");
	frt >> indfr;

	for (auto& device : audioRecorder->audioInputs()) {
		ui.fron->addItem(device, QVariant(device));
	}
	
	for (auto& device : audioRecorder->audioInputs()) {
		ui.behi->addItem(device, QVariant(device));
	}
	ui.behi->setCurrentIndex(indbh);
	ui.fron->setCurrentIndex(indfr);

	ui.volume->setMinimum(0);
	ui.volume->setMaximum(100);//最大值设置
	ui.volume->setSingleStep(1);
	ui.volume->setTickPosition(QSlider::TicksAbove);
	ui.volume->setValue(50);
	connect(ui.volume, SIGNAL(valueChanged(int)), this, SLOT(applyVolume(int)));

	timericon->start(1);
}

ssy::~ssy()
{

}

void ssy::initialize() {
	ifstream fpstxt("fps.txt");
	fpstxt >> framerate;
	ui.lineEdit->setReadOnly(true);
	ui.lineEdit_2->setReadOnly(true);
	ui.lineEdit_3->setReadOnly(true);
	ui.lineEdit_4->setReadOnly(true);
	ui.lineEdit_5->setReadOnly(true);
	ui.lineEdit_6->setReadOnly(true);
	ui.ozhuchiren->setVisible(true);
	ui.otai->setVisible(true);
	ui.ogun->setVisible(true);
	ui.ctai->setVisible(false);
	ui.czhuchiren->setVisible(false);
	ui.cgun->setVisible(false);

	ui.left->setVisible(true);
	ui.right->setVisible(true);
	taibiao = false;
	zhuchiren = false;
	gundongzimu = false;
	ui.zmjs->setVisible(false);
	ui.zmji->setVisible(false);
	ui.tbwzs->setVisible(false);
	ui.tbwzx->setVisible(false);
	ui.tbwzz->setVisible(false);
	ui.tbwzy->setVisible(false);
	ui.zcwzs->setVisible(false);
	ui.zcwzx->setVisible(false);
	ui.zcwzz->setVisible(false);
	ui.zcwzy->setVisible(false);
	ui.zmwzs->setVisible(false);
	ui.zmwzx->setVisible(false);
	ui.sl->setVisible(false);
	ui.you->setVisible(false);

	ui.lineEdit_7->setVisible(false);
	ui.lineEdit_8->setVisible(false);
	ui.lineEdit_9->setVisible(false);
	ui.label_6->setVisible(false);
	ui.label_7->setVisible(false);
	ui.label_8->setVisible(false);

	yanser();


	

	pic = imread("./bg/3.jpg");
	ns = imread("./icon/ns.jpg");
	filenamex = "./bg/3.jpg";
	//record = imread("F:\\ssy\\icon\\record.jpg");
	//cv::resize(record, record, Size(20, 20));
	pause = imread("./icon/pause.jpg");
	cv::resize(pause, pause, Size(300, 300));
	tai = imread("./Resources/tb/23.png");
	host = imread("./Resources/zcr/image_2.jpg");
	zm = imread("./Resources/zm/1.png");
	svd = imread("./Resources/save.png");

	camera.open(0);//打开摄像头
	screen.open(1);
	camera.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
	camera.set(CV_CAP_PROP_FOURCC, CV_FOURCC('F', 'L', 'V', '1'));
	screen.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	screen.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
	screen.set(CV_CAP_PROP_FOURCC, CV_FOURCC('F', 'L', 'V', '1'));

	//roi_rect = cv::Rect(1710, 30, record.cols, record.rows);
	roi2 = cv::Rect(780, 380, pause.cols, pause.rows);
	roz = cv::Rect(0, 980, zm.cols, zm.rows);
	sv = cv::Rect(560, 440, 800, 200);

	setiniv();
	ui.label_27->setVisible(false);
	ui.label_28->setVisible(false);
	timer->start(20);
	timerzm->start(15);
}

void ssy::start() {

	WinExec("cmd.exe /c del d:\\vasource\\audio.wav /q", SW_HIDE);
	ui.start->setDisabled(true);
	timerzm->stop();
	timer->stop();
	timericon->stop();
	ui.label->clear();

	int thr = 0;
	//int t,fps,frame,tt;

	pp = tb.c_str();
	if (strlen(pp) == 0) {
		pp = " ";
	}

	gg = gd.c_str();
	if (strlen(gg) == 0) {
		gg = " ";
	}

	zcc = zhuchi.c_str();
	if (strlen(zcc) == 0) {
		zcc = " ";
	}
	int iter = 1;

	QTime recordt;
	//timee = "00:00:00";

	volatile BOOL cm = true;
	volatile BOOL o_writer = false;
	volatile BOOL rec;
	volatile BOOL stt = true;

	audioRecorderf = new QAudioRecorder;
	audioRecorderb = new QAudioRecorder;

	QAudioEncoderSettings audioSettings;
	audioSettings.setCodec("audio/amr");
	audioSettings.setQuality(QMultimedia::HighQuality);

	audioRecorderf->setEncodingSettings(audioSettings);
	audioRecorderf->setOutputLocation(QUrl::fromLocalFile("D:/vasource/bf/audiof"));
	audioRecorderf->setAudioInput(boxValue(ui.fron).toString());

	audioRecorderb->setEncodingSettings(audioSettings);
	audioRecorderb->setOutputLocation(QUrl::fromLocalFile("D:/vasource/bf/audiob"));
	audioRecorderb->setAudioInput(boxValue(ui.behi).toString());

	audioRecorderb->setVolume(qRound(linearVolume * 100));
	audioRecorderf->setVolume(qRound(linearVolume * 100));
	fcount = 0;

	// Make duplication manager
	FILE* log_file;
	DUPLICATIONMANAGER DuplMgr;
	DUPL_RETURN Ret;
	UINT Output = 0;
	fopen_s(&log_file, "logY.txt", "w");
	Ret = DuplMgr.InitDupl(log_file, Output);
	BYTE* pBuf = new BYTE[10000000];

	we.open("D:\\vasource\\video.avi", CV_FOURCC('F', 'L', 'V', '1'), framerate, Size(1920, 1080), true);
	cv::destroyAllWindows();

	namedWindow("录制窗口", CV_WINDOW_NORMAL);
	setWindowProperty("录制窗口", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	
	//窗口置前
	HWND hWnd = (HWND)cvGetWindowHandle("录制窗口"); 
	HWND hRawWnd = ::GetParent(hWnd); 
	if (hRawWnd != NULL) { 
		BOOL bRet = ::SetWindowPos(hRawWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);  
		assert(bRet);
	}
	
	std::thread t0([&] {
		while (cm) {
			if ((GetAsyncKeyState(0x60) & 0x8000f)) {//ctrl+小键盘0开始/暂停录制
				o_writer = !o_writer;
				
				Sleep(800);
			}
			if ((GetAsyncKeyState(0x61) & 0x8000f)) {
				cm = !cm;

			}
			if ((GetAsyncKeyState(0x65) & 0x8000f)) {//ctrl+小键盘4 人消失
				flagr = true;

			}
			if ((GetAsyncKeyState(0x66) & 0x8000f)) {//ctrl+小键盘6 人消失
				flagr = false;

			}

			if ((GetAsyncKeyState(0x68) & 0x8000f)) {//ctrl+小键盘7 图
				flags = 1;

			}

			if ((GetAsyncKeyState(0x69) & 0x8000f)) {//ctrl+小键盘9 电脑
				flags = 2;

			}
			if ((GetAsyncKeyState(0x62) & 0x8000f)) {
				zhuchiren = true;
			}
			if ((GetAsyncKeyState(0x63) & 0x8000f)) {
				zhuchiren = false;
			}
		}
		});
	t0.detach();

	std::thread t1([&] {
		mu.lock();
		while (cm) {
			if (o_writer) {
				firec = clock();
				//cout << (LONGLONG)(firec - strec) << "-" << fcount * 20 << endl;
				if ((LONGLONG)(firec - strec)-fcount*20 > 0) {
					Ret = DuplMgr.GetFrame(pBuf);
					cvtColor(Mat(1080, 1920, CV_8UC4, pBuf), fop, COLOR_RGBA2RGB);
					we << fop;
					fcount += 1;
				}
			}
					
		}
		thr += 1;
		mu.unlock();
		});
	t1.detach();

	while ((!(GetAsyncKeyState(0x61) & 0x8000f))) {//ctrl+小键盘1退出

		switch (flags) {
		case 1:
			if (flagr) {
				fm = process_pc();
			}
			else {
				fm = process_p();
			}
			break;
		case 2:
			if (flagr) {
				fm = process_sc();
			}
			else {
				fm = process_s();
			}
			break;
		}


		if (!o_writer) {
			pause.copyTo(fm(roi2), pause);
			rec = true;
			if (stt) {
				if (iter == 1) {
					iter += 1;
					stt = false;
				}
				else {
					audioRecorderf->pause();
					audioRecorderb->pause();
					//StopStopwatch();
					stt = false;
				}
			}
		}

		if (o_writer) {
			//record.copyTo(fm(roi_rect));
			stt = true;
			if (rec) {
				strec = clock();
				fcount = 0;
				audioRecorderb->record();
				audioRecorderf->record();
				//StartStopwatch();
				rec = false;
			}
		}

		//timeshows();
		//cv::putText(fm, timee, Point(1700, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 3, 1, 0);
		cv::imshow("录制窗口", fm);
		gundooo();
		cv::waitKey(1);

	}
	
	audioRecorderf->stop();
	audioRecorderb->stop();

	while (thr == 0) {
		Sleep(1);
	}

	svd.copyTo(fm(sv));
	cv::imshow("录制窗口", fm);
	cv::waitKey(1);
	we.release();
	ResetStopwatch();
	delete pBuf;
	fclose(log_file);
	i = i++;
	cmd();
	
	cv::destroyAllWindows();
	timericon->start();
	ui.start->setEnabled(true);
	timerzm->start();
	timer->start();
}

void ssy::sshow()
{
	pp = tb.c_str();
	if ((xt > 0) && (yt > 0) && ((xt + tai.cols) < 1920) && ((yt + tai.rows) < 1080)) {
		rot = cv::Rect(xt, yt, tai.cols, tai.rows);
	}
	if ((xh > 0) && (yh > 0) && ((xh + host.cols) < 1920) && ((yh + host.rows) < 1080)) {
		roh = cv::Rect(xh, yh, host.cols, host.rows);
	}

	std::thread s1([&] {
		mu.lock();
		if (strlen(pp) == 0) {
			pp = " ";
		}

		gg = gd.c_str();
		if (strlen(gg) == 0) {
			gg = " ";
		}

		zcc = zhuchi.c_str();
		if (strlen(zcc) == 0) {
			zcc = " ";
		}
		mu.unlock();
		});
	s1.join();

	std::thread s2([&] {
		mu.lock();
		if ((GetAsyncKeyState(0x65) & 0x8000f)) {
			flagr = true;
		}

		if ((GetAsyncKeyState(0x66) & 0x8000f)) {
			flagr = false;
		}

		if ((GetAsyncKeyState(0x68) & 0x8000f)) {
			flags = 1;

		}

		if ((GetAsyncKeyState(0x69) & 0x8000f)) {
			flags = 2;

		}
		if ((GetAsyncKeyState(0x62) & 0x8000f)) {
			zhuchiren = true;
		}
		if ((GetAsyncKeyState(0x63) & 0x8000f)) {
			zhuchiren = false;
		}
		mu.unlock();
		});
	s2.join();

	switch (flags) {
	//Confidential

	}

}

void ssy::showEvent(QShowEvent*) {
	timer3->start(1);
}


void ssy::end()
{
	ui.label_27->setVisible(true);
	ui.label_28->setVisible(true);
	emit sendsignal();
	this->close();
}

void ssy::cmd() {
	time(&timep);
	p = localtime(&timep);
	system("ffmpeg -i D:\\vasource\\bf\\audiof.wav -i D:\\vasource\\bf\\audiob.wav -filter_complex amix=inputs=2:duration=longest:dropout_transition=2 -f wav D:\\vasource\\audio.wav");
	sprintf(name, "ffmpeg -i D:\\vasource\\video.avi -i D:\\vasource\\audio.wav -vcodec copy -acodec copy -b:v 9000k D:\\testresult\\%d年%d月%d日%d.%02d.%02d-%d.avi", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, i);
	
	system(name);
}

void ssy::lowerValueChangedSlot(int value)
{
	ui.lineEdit->setText(QString("%1").arg(value));
}

void ssy::upperValueChangedSlot(int value)
{
	ui.lineEdit_2->setText(QString("%1").arg(value));
}

void ssy::lowerTextChangedSlot(const QString& text)
{
	baox = text.toInt();
	ui.horizontalSlider->setLowerValue(baox);
}

void ssy::upperTextChangedSlot(const QString& text)
{
	baos = text.toInt();
	ui.horizontalSlider->setUpperValue(baos);
}

void ssy::lowerValueChangedSlot2(int value)
{
	ui.lineEdit_3->setText(QString("%1").arg(value));
}

void ssy::upperValueChangedSlot2(int value)
{
	ui.lineEdit_4->setText(QString("%1").arg(value));
}

void ssy::lowerTextChangedSlot2(const QString& text)
{
	lx = text.toInt();
	ui.horizontalSlider_2->setLowerValue(lx);
}

void ssy::upperTextChangedSlot2(const QString& text)
{
	ls = text.toInt();
	ui.horizontalSlider_2->setUpperValue(ls);
}

void ssy::lowerValueChangedSlot3(int value)
{
	ui.lineEdit_5->setText(QString("%1").arg(value));
}

void ssy::upperValueChangedSlot3(int value)
{
	ui.lineEdit_6->setText(QString("%1").arg(value));
}

void ssy::lowerTextChangedSlot3(const QString& text)
{
	sx = text.toInt();
	ui.horizontalSlider_3->setLowerValue(sx);
}

void ssy::upperTextChangedSlot3(const QString& text)
{
	ss = text.toInt();
	ui.horizontalSlider_3->setUpperValue(ss);
}

void ssy::taiTextChanged(const QString& text)
{
	tb = string((const char*)text.toLocal8Bit());
}

void ssy::gdTextChanged(const QString& text)
{
	gd = string((const char*)text.toLocal8Bit());
	Size textSize = getTextSize(gd, fontFace, fontScale, thickness, &baseline);
	wdzm = textSize.width;
}

void ssy::zhuchiTextChanged(const QString& text)
{
	zhuchi = string((const char*)text.toLocal8Bit());

}

void ssy::TimeSlot()
{
	countTemp += 1;
	if (wz < -wdzm) {
		wz = 1920;
	}
	if (speed < 0) {
		speed = 0;
	}
	wz -= speed;

	if (countTemp == 102)
	{
		countTemp = 0;
		secondTemp += 1;
		wz += 1;
		if (secondTemp == 60)
		{
			secondTemp = 0;
			minuteTemp += 1;
			if (minuteTemp == 60)
			{
				minuteTemp = 0;
				hourTemp += 1;
			}
		}
	}
	//把整数转换成字符串  
	
	/*QString hourstr = QString::number(hourTemp);
	QString minutestr = QString::number(minuteTemp);
	QString secondstr = QString::number(secondTemp);
	string hour = hourstr.toStdString();
	string min = minutestr.toStdString();
	string second = secondstr.toStdString();
	timee = hour + ":" + min + ":" + second;*/
}

Mat ssy::process_pc() {

	//Confidential
}

Mat ssy::process_sc() {

	//Confidential
}

Mat ssy::process_p() {
	//Confidential
}

Mat ssy::process_s() {
	//Confidential
}

void ssy::StartStopwatch()
{

	msTimer->start(1); //10ms  
}

void ssy::ResetStopwatch()
{
	countTemp = 0;
	secondTemp = 0;
	minuteTemp = 0;
	hourTemp = 0;

}

void ssy::StopStopwatch()
{
	msTimer->stop();
}

void ssy::gundo() {
	//countt += 1;
	if (wz < -wdzm) {
		wz = 1920;
	}
	if (speed < 0) {
		speed = 0;
	}
	wz -= speed;
}

void ssy::gundooo() {
	if (wz < -wdzm) {
		wz = 1920;
	}
	if (speed < 0) {
		speed = 0;
	}
	wz -= speed;
}

void ssy::yanser() {



	switch (colors->checkedId())

	{

	case 0:

		ui.lineEdit_5->setText(QString("%1").arg(0));
		ui.lineEdit_6->setText(QString("%1").arg(180));
		ui.lineEdit->setText(QString("%1").arg(0));
		ui.lineEdit_2->setText(QString("%1").arg(255));
		ui.lineEdit_3->setText(QString("%1").arg(0));
		ui.lineEdit_4->setText(QString("%1").arg(46));

		break;

	case 1:

		ui.lineEdit_5->setText(QString("%1").arg(0));
		ui.lineEdit_6->setText(QString("%1").arg(180));
		ui.lineEdit->setText(QString("%1").arg(0));
		ui.lineEdit_2->setText(QString("%1").arg(30));
		ui.lineEdit_3->setText(QString("%1").arg(221));
		ui.lineEdit_4->setText(QString("%1").arg(255));

		break;

	case 2:

		ui.lineEdit_5->setText(QString("%1").arg(0));
		ui.lineEdit_6->setText(QString("%1").arg(10));
		ui.lineEdit->setText(QString("%1").arg(43));
		ui.lineEdit_2->setText(QString("%1").arg(255));
		ui.lineEdit_3->setText(QString("%1").arg(46));
		ui.lineEdit_4->setText(QString("%1").arg(255));
		break;
	case 3:
		ui.lineEdit_5->setText(QString("%1").arg(35));
		ui.lineEdit_6->setText(QString("%1").arg(99));
		ui.lineEdit->setText(QString("%1").arg(43));
		ui.lineEdit_2->setText(QString("%1").arg(255));
		ui.lineEdit_3->setText(QString("%1").arg(46));
		ui.lineEdit_4->setText(QString("%1").arg(255));
		break;
	case 4:
		ui.lineEdit_5->setText(QString("%1").arg(100));
		ui.lineEdit_6->setText(QString("%1").arg(124));
		ui.lineEdit->setText(QString("%1").arg(43));
		ui.lineEdit_2->setText(QString("%1").arg(255));
		ui.lineEdit_3->setText(QString("%1").arg(46));
		ui.lineEdit_4->setText(QString("%1").arg(255));
		break;
	}
}

void ssy::qdtb() {
	ui.otai->setVisible(false);
	ui.ctai->setVisible(true);
	ui.lineEdit_7->setVisible(true);
	ui.label_6->setVisible(true);
	ui.tbwzs->setVisible(true);
	ui.tbwzx->setVisible(true);
	ui.tbwzz->setVisible(true);
	ui.tbwzy->setVisible(true);
	taibiao = true;
}

void ssy::gbtb() {
	ui.ctai->setVisible(false);
	ui.otai->setVisible(true);
	ui.lineEdit_7->setVisible(false);
	ui.label_6->setVisible(false);
	ui.tbwzs->setVisible(false);
	ui.tbwzx->setVisible(false);
	ui.tbwzz->setVisible(false);
	ui.tbwzy->setVisible(false);
	taibiao = false;
}

void ssy::qdzc() {
	ui.ozhuchiren->setVisible(false);
	ui.czhuchiren->setVisible(true);
	ui.lineEdit_9->setVisible(true);
	ui.label_8->setVisible(true);
	ui.zcwzs->setVisible(true);
	ui.zcwzx->setVisible(true);
	ui.zcwzz->setVisible(true);
	ui.zcwzy->setVisible(true);
	zhuchiren = true;
}

void ssy::gbzc() {
	ui.czhuchiren->setVisible(false);
	ui.ozhuchiren->setVisible(true);
	ui.lineEdit_9->setVisible(false);
	ui.label_8->setVisible(false);
	ui.zcwzs->setVisible(false);
	ui.zcwzx->setVisible(false);
	ui.zcwzz->setVisible(false);
	ui.zcwzy->setVisible(false);
	zhuchiren = false;
}

void ssy::qdzm() {
	ui.ogun->setVisible(false);
	ui.cgun->setVisible(true);
	ui.lineEdit_8->setVisible(true);
	ui.label_7->setVisible(true);
	ui.zmwzs->setVisible(true);
	ui.zmwzx->setVisible(true);
	ui.zmjs->setVisible(true);
	ui.zmji->setVisible(true);
	gundongzimu = true;
}

void ssy::gbzm() {
	ui.cgun->setVisible(false);
	ui.ogun->setVisible(true);
	ui.lineEdit_8->setVisible(false);
	ui.label_7->setVisible(false);
	ui.zmwzs->setVisible(false);
	ui.zmwzx->setVisible(false);
	ui.zmjs->setVisible(false);
	ui.zmji->setVisible(false);
	gundongzimu = false;
}

void ssy::t_s() {
	if (0 < wztbh && wztbh < 1080) {
		wztbh -= 2;
	}
}
void ssy::t_x() {
	if (0 < wztbh && wztbh < 1080) {
		wztbh += 2;
	}
}
void ssy::t_z() {
	if (0 < wztbw && wztbw < 1920) {
		wztbw -= 2;
	}
}
void ssy::t_y() {
	if (0 < wztbw && wztbw < 1920) {
		wztbw += 2;
	}
}

void ssy::zm_s() {
	if (0 < wzzmh && wzzmh < 1080) {
		wzzmh -= 2;
	}
}
void ssy::zm_x() {
	if (0 < wzzmh && wzzmh < 1080) {
		wzzmh += 2;
	}
}

void ssy::zc_s() {
	if (0 < wzzch && wzzch < 1080) {
		wzzch -= 2;
	}
}
void ssy::zc_x() {
	if (0 < wzzch && wzzch < 1080) {
		wzzch += 2;
	}
}
void ssy::zc_z() {
	if (0 < wzzcw && wzzcw < 1920) {
		wzzcw -= 10;
	}
}
void ssy::zc_y() {
	if (0 < wzzcw && wzzcw < 1920) {
		wzzcw += 10;
	}
}

void ssy::jiasu() {
	speed += 2;
}
void ssy::jiansu() {
	speed -= 2;
}

void ssy::invi() {
	ui.left->setVisible(false);
	ui.sl->setVisible(true);
}

void ssy::showl() {
	ui.left->setVisible(true);
	ui.sl->setVisible(false);
}

void ssy::invir() {
	ui.right->setVisible(false);
	ui.you->setVisible(true);
}

void ssy::showr() {
	ui.right->setVisible(true);
	ui.you->setVisible(false);
}

void ssy::mousePressEvent(QMouseEvent* event)
{
	//读取坐鼠标点击坐标点
	trect = QRect(xt, yt, tai.cols, tai.rows);
	hrect = QRect(xh, yh, host.cols, host.rows);

	txix = wztbw - xt;
	txiy = wztbh - yt;

	hxix = wzzcw - xh;
	hxiy = wzzch - yh;



	if (trect.contains(event->globalPos())) {
		tsb = true;
		m_lastPoint = event->globalPos();
		if (xt < 0) {
			xt = 0;
		}
		if (yt < 0) {
			yt = 0;
		}
	}
	else {
		tsb = false;
	}

	if (hrect.contains(event->globalPos())) {
		hsb = true;
		m_lastPoint = event->globalPos();
		if (xh < 0) {
			xh = 0;
		}
		if (yh < 0) {
			yh = 0;
		}
	}
	else {
		hsb = false;
	}
}

void ssy::mouseMoveEvent(QMouseEvent* event)
{
	//把移动的点记录下来
	if (tsb) {
		int dx = event->globalX() - m_lastPoint.x();
		int dy = event->globalY() - m_lastPoint.y();

		m_lastPoint = event->globalPos(); //更新记录点

		xt = xt + dx;
		yt = yt + dy;
		wztbw = xt + txix;
		wztbh = yt + txiy;
	}

	if (hsb) {
		int dx = event->globalX() - m_lastPoint.x();
		int dy = event->globalY() - m_lastPoint.y();

		m_lastPoint = event->globalPos(); //更新记录点

		xh = xh + dx;
		yh = yh + dy;
		wzzcw = xh + hxix;
		wzzch = yh + hxiy;
	}
}

void ssy::mouseReleaseEvent(QMouseEvent* event) {
	tsb = false;
	hsb = false;
}

void ssy::ct(QListWidgetItem* item) {
	
	//filenamet = QFileDialog::getOpenFileName(this, tr("LOGO"), "./Resources/tb/", tr("Images (*.*)"));
	filenamet=tb_strPath + "/" + tb_imgList.at(ui.tblw->row(item));
	setpic = imread(filenamet.toStdString());
	if (!setpic.empty()) {
		tai = setpic;
	}
	
}
void ssy::cz(QListWidgetItem* item) {
	
	//filenamez = QFileDialog::getOpenFileName(this, tr("Host"), "./Resources/zcr/", tr("Images (*.*)"));
	filenamez = zcr_strPath + "/" + zcr_imgList.at(ui.zcrlw->row(item));
	setpic = imread(filenamez.toStdString());
	if (!setpic.empty()) {
		host = setpic;
	}
}

void ssy::applyVolume(int v) {
	linearVolume = QAudio::convertVolume(v / qreal(100.0),
		QAudio::LogarithmicVolumeScale,
		QAudio::LinearVolumeScale);
}

void ssy::setiniv() {
	linearVolume = QAudio::convertVolume(50 / qreal(100.0),
		QAudio::LogarithmicVolumeScale,
		QAudio::LinearVolumeScale);
}

void ssy::czm(QListWidgetItem* item) {
	//filenamezm = QFileDialog::getOpenFileName(this, tr("Background Color"), "./Resources/zm/", tr("Images (*.*)"));
	filenamezm=zm_strPath + "/" + zm_imgList.at(ui.zmlw->row(item));
	setpic = imread(filenamezm.toStdString());
	if (!setpic.empty()) {
		zm = setpic;
	}
}

void ssy::cbjtp(QListWidgetItem* item) {
	//ui.luzhibeijing->setVisible(false);
	//filenamebg = QFileDialog::getOpenFileName(this, tr("Background"), "./bg/", tr("Images (*.*)"));
	filenamebg= bg_strPath + "/" + bg_imgList.at(ui.bgp->row(item));
	setpic = imread(filenamebg.toStdString());
	if (!setpic.empty()) {
		pic = setpic;
		filenamex = filenamebg;
	}
	//ui.luzhibeijing->setVisible(true);
}

void ssy::icon() {
	if (ui.start_2->geometry().contains(this->mapFromGlobal(QCursor::pos() - ui.left->pos()))) {
		ui.start_2->setVisible(false);
		ui.start->setVisible(true);
	}
	else {
		ui.start_2->setVisible(true);
		ui.start->setVisible(false);
	}
	if (ui.end_2->geometry().contains(this->mapFromGlobal(QCursor::pos() - ui.right->pos()))) {
		ui.end_2->setVisible(false);
		ui.end->setVisible(true);
	}
	else {
		ui.end_2->setVisible(true);
		ui.end->setVisible(false);
	}
}

void ssy::setwei() {
	ui.lineEdit->setReadOnly(false);
	ui.lineEdit_2->setReadOnly(false);
	ui.lineEdit_3->setReadOnly(false);
	ui.lineEdit_4->setReadOnly(false);
	ui.lineEdit_5->setReadOnly(false);
	ui.lineEdit_6->setReadOnly(false);
	ui.weitiao->setVisible(false);
}
void ssy::nsetwei() {
	ui.lineEdit->setReadOnly(true);
	ui.lineEdit_2->setReadOnly(true);
	ui.lineEdit_3->setReadOnly(true);
	ui.lineEdit_4->setReadOnly(true);
	ui.lineEdit_5->setReadOnly(true);
	ui.lineEdit_6->setReadOnly(true);
	ui.weitiao->setVisible(true);
}


void ssy::saveText() {
	QFile bhdd("behind.txt");
	QFile frtt("front.txt");

	if (bhdd.open(QIODevice::WriteOnly)) {
		QString behint = QString::number(ui.behi->currentIndex());
		bhdd.write(behint.toUtf8());
	}

	if (frtt.open(QIODevice::WriteOnly)) {
		QString froint = QString::number(ui.fron->currentIndex());
		frtt.write(froint.toUtf8());
	}
	
	bhdd.close();
	frtt.close();
}

/*void ssy::timeshows() {
	//(fcount * 20)
	ms = (fcount * 20);
	hout = ms / 3600000;
	mint = (ms % 3600000) / 60000;
	sect = (ms % 60000) / 1000;
	String strHour = hout < 10 ? "0" + std::to_string(hout) : "" + std::to_string(hout);//小时
	String strMinute = mint < 10 ? "0" + std::to_string(mint) : "" + std::to_string(mint);//分钟
	String strSecond = sect < 10 ? "0" + std::to_string(sect) : "" + std::to_string(sect);//秒
	timee = strHour + ":" + strMinute + ":" + strSecond;
}*/

void ssy::flagco() {
	flags = 1;
}

void ssy::flagct() {
	flags = 2;
}

void ssy::flagrct() {
	flagr = true;
}

void ssy::flagrcf() {
	flagr = false;
}

void ssy::zcrshow() {
	zhuchiren = true;
}

void ssy::zcrinv() {
	zhuchiren = false;
}