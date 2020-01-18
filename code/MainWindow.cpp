#include "MainWindow.h"
#include "ui_MainWindow.h"

using namespace std;
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库
int key[] = { 1,2,3,4,5,6,7 };

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	f1 = new ssy;
	hdmi.open(1);
	
	ui.pp1->setVisible(false);
	ui.ppf->setVisible(false);
	ui.pph->setVisible(false);
	ui.opentai->setVisible(false);
	ui.label_3->setVisible(false);
	ui.lineEdit->setVisible(false);


	connect(ui.rekai, SIGNAL(clicked()), this, SLOT(chongqi()));
	connect(f1, SIGNAL(sendsignal()), this, SLOT(reshow()));
	t = new QTimer(this);
	connect(t, SIGNAL(timeout()), this, SLOT(changes()));
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	//记录网卡数量
	int netCardNum = 0;
	//记录每张网卡上的IP地址数量
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		//释放原来的内存空间
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}

	char* wkcode = new char[1024];
	char* codee = new char[1024];
	wkcode = pIpAdapterInfo->AdapterName;
	QString strc = QString(QLatin1String(wkcode));
	codee = Getresult(wkcode);

	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}

	ifstream myFile(".\\license.bin");
	if (myFile.is_open()) {

		char sks;
		char* codcc = new char[10001];
		int itera = 0;
		int out = 0;
		if (myFile.is_open())
		{
			while (!myFile.eof())

			{

				myFile >> sks;

				//cout << sks << endl;
				codcc[itera] = sks;
				itera += 1;
			}
		}

		codcc[10001] = '\0';
		myFile.close();
		string s = codcc;
		decode(s, key);

		int month = atoi(s.substr(600, 2).c_str());
		int year = atoi(s.substr(700, 2).c_str());
		char* solved = (char*)s.substr(637, 38).data();

		//printf("%s", codee);

		int scores = 0;
		string c1 = codee;
		string c2 = solved;

		if (c1 == c2) {
			scores = 8;
		}

		time(&tpii);
		pii = localtime(&tpii);
		int nyea = pii->tm_year - 100;
		int nmon = 1 + pii->tm_mon;

		if (nyea > year) {
			scores = 0;
		}
		else if (nyea == year && nmon > month) {
			scores = 0;
		}

		//printf("%d-%d\n%d-%d", ynum, mnum, nyea, nmon);

		if (scores == 8) {
			ui.pp1->setVisible(true);
			ui.ppf->setVisible(true);
			ui.pph->setVisible(true);
			ui.opentai->setVisible(true);
			t->start(1);
		}
		else {
			ui.label_3->setVisible(true);
			ui.lineEdit->setText(strc);
			ui.lineEdit->setVisible(true);
		}
	}
	else {
		ui.label_3->setVisible(true);
		ui.lineEdit->setText(strc);
		ui.lineEdit->setVisible(true);
	}

}

MainWindow::~MainWindow()

{
	delete f1;
}

void MainWindow::changes() {
	if (ui.opentai->geometry().contains(this->mapFromGlobal(QCursor::pos()))) {
		ui.opentai->setGeometry(710, 530, 541, 310);

	}
	else {
		ui.opentai->setGeometry(720, 540, 521, 290);

	}
	if (ui.pp1->geometry().contains(this->mapFromGlobal(QCursor::pos()))) {
		ui.pp1->setGeometry(340, 220, 370, 620);

	}
	else {
		ui.pp1->setGeometry(350, 230, 350, 600);

	}
	if (ui.pph->geometry().contains(this->mapFromGlobal(QCursor::pos()))) {
		ui.pph->setGeometry(710, 220, 541, 310);

	}
	else {
		ui.pph->setGeometry(720, 230, 521, 290);

	}
	if (ui.ppf->geometry().contains(this->mapFromGlobal(QCursor::pos()))) {
		ui.ppf->setGeometry(1251,220, 370, 620);

	}
	else {
		ui.ppf->setGeometry(1261, 230, 350, 600);

	}
	if (ui.rekai->geometry().contains(this->mapFromGlobal(QCursor::pos()))) {
		ui.rekai->setGeometry(1655, 150, 161, 51);

	}
	else {
		ui.rekai->setGeometry(1660, 155, 151, 41);

	}
	if (ui.end->geometry().contains(this->mapFromGlobal(QCursor::pos()))) {
		ui.end->setGeometry(1655, 85, 160, 71);

	}
	else {
		ui.end->setGeometry(1660, 90, 151, 61);
	}
}

void MainWindow::openv() {
	f1->showFullScreen();

	//this->close();
	t->stop();
}


void MainWindow::reshow() {
	t->start(1);
	//this->show();
}

void MainWindow::end() {
	t->stop();
	this->close();
	WinExec("shutdown -s -t 0", SW_HIDE);
	//system("shutdown -s -t 0");
}
void MainWindow::openf() {

	//WinExec("explorer D:\\testresult", SW_NORMAL);
	QDesktopServices::openUrl(QUrl::fromLocalFile("D:/testresult/"));

}

void MainWindow::opent() {

	//WinExec("explorer C:\\ssy\\Resources\\tb", SW_NORMAL);
	QDesktopServices::openUrl(QUrl::fromLocalFile("./Resources/tb/"));

}

void MainWindow::chongqi() {
	t->stop();
	this->close();
	WinExec("shutdown -r -t 0", SW_HIDE);
	//system("shutdown -r -t 0");
}

void MainWindow::openh() {
	hdmi.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	hdmi.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
	while (1) {
		hdmi >> Hd;
		if (Hd.rows != 1080) {
			Hd = imread("./icon/ns.jpg");
		}
		imshow("教师电脑信号源", Hd);
		waitKey(1);
		if (!cvGetWindowHandle("教师电脑信号源"))
		{
			break;
		}
	}
}

char* MainWindow::Getresult(char* id) {
	//Confidential
}

void MainWindow::decode(string& c, int key[])
{
	//Confidential
}