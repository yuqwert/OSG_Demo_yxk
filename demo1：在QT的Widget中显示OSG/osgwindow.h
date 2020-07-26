#ifndef OSGWINDOW_H
#define OSGWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_osgwindow.h"

#include <QTimer>
#include <osgViewer/Viewer>

class OSGWindow : public QMainWindow
{
	Q_OBJECT

public:
	OSGWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OSGWindow();

private:
	Ui::OSGWindowClass ui;


private:
	QTimer* _timer;		// ��ʱ����ÿ25ms����һ���¼�
	osgViewer::Viewer* viewer;


	// ��ʼ������osg
	void initOSG();

private slots:
	// ��ʱ����֡�Ĳۺ���
	void updateFrame();	

};

#endif // OSGWINDOW_H
